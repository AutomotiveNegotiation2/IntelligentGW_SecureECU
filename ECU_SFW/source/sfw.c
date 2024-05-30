/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sfw.h"
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/*
#include <stddef.h>
#include "rsa.h"
#include "aursa.h"
#include "sha1.h"
#include "sha2.h"
#include "md_wrap.h"
#include "aursatype.h"
*/
#include "board.h"
#include "fsl_gpio.h"

#ifdef OTA_SUPPORT
#include "sbl_ota_flag.h"
#ifdef SOC_LPC55S69_SERIES
#include "iap_flash_ops.h"
#else
#include "fsl_flexspi.h"
#include "fsl_debug_console.h"
#include "fsl_cache.h"
#include "flexspi_flash.h"
#include "flexspi_flash_config.h"
#endif
#endif

#include "fsl_debug_console.h"
#include "mflash_drv.h"
#include "flash_info.h"

#include "test_src.h"

extern const char* mypub_N;
extern const char* mypub_E;

#define KEY_LEN            256

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define IMAGE_OK_UNSET                  0xFF
#define IMAGE_OK_SET                    0x01
#define IMAGE_OK_REVERT                 0x04

#define PAGE_SZ                         0x100
#define SECTOR_SZ                       0x1000
#define SLOT_SZ                         0x00400000
#define PAGES_PER_SECTOR                16
#define SECTORS_PER_SLOT                (SLOT_SZ/SECTOR_SZ)

#define REMAP_FLAG_SECTOR_OFFSET        (FLASH_AREA_IMAGE_1_OFFSET - SECTOR_SZ)
#define REMAP_FLAG_OFFSET_IN_SECTOR     (SECTOR_SZ - 32U)
#define REMAP_MAGIC                     "\x77\xc2\x95\xf3\x60\xd2\xef\x7f\x35\x52\x50\x0f\x2c\xb6\x79\x80"

#define REMAP_MAGIC_SIZE				16
#define REMAP_IMAGE_OK_SIZE				8
#define REMAP_IMAGE_POSITION_SIZE		8

#define FLASH_PORT          kFLEXSPI_PortA1

/* Task priorities. */
#define hello_keti_PRIORITY (configMAX_PRIORITIES - 4)
#define hello_autocrypt_PRIORITY (configMAX_PRIORITIES - 5)
#define hello_dhauto_PRIORITY (configMAX_PRIORITIES - 6)

#define IMG_VERIFY_NONE     0
#define IMG_VERIFY_DENYED   1
#define IMG_VERIFY_PASSED   2
#define IMG_VERIFY_FAILED   3
#define IMG_VERIFY_UNKNOWN  4

uint8_t     f_img_downloaded;
uint8_t     f_img_verify_result;

int do_firmware_update(void)
{
    unsigned char           *pimg_leng  = (unsigned char *)BOOT_FLASH_SCRATCH_BASE;
    int                     img_leng    = 0;
    unsigned int            ix;
    unsigned int            offset;

    unsigned char           md_sum[SHA256_SZ];
    mypublic_t              my_pub = {
                                .len    = KEY_LEN,
                                .n      = mypub_N,
                                .e      = mypub_E };
    unsigned char           chr;

    int                     status      = kStatus_Fail;
    uint8_t                 runSlot;
    uint32_t                dstBase;
    uint32_t                srcBase;
    uint8_t                 buf[PAGE_SZ];
    volatile uint32_t       primask;
    struct image_version    *run_img_ver;
    struct image_version    *ota_img_ver;
    uint8_t                 run_img_version[8];
    uint8_t                 ota_img_version[8];
    int 					err_return;
    int i;
    uint8_t* buffer;

    boot_flash_area_read(REMAP_FLAG_ADDRESS, &runSlot, sizeof(runSlot));

    if( runSlot == SLOT_1 )
    {
        boot_flash_area_read(FLASH_AREA_IMAGE_1_OFFSET + IMAGE_VERSION_OFFSET, run_img_version, sizeof(struct image_version));
        run_img_ver = (struct image_version *)run_img_version;
    }
    else if( runSlot == SLOT_2 )
    {
        boot_flash_area_read(FLASH_AREA_IMAGE_2_OFFSET + IMAGE_VERSION_OFFSET, run_img_version, sizeof(struct image_version));
        run_img_ver = (struct image_version *)run_img_version;
    }
    else
    {
        boot_flash_area_read(FLASH_AREA_IMAGE_1_OFFSET + IMAGE_VERSION_OFFSET, run_img_version, sizeof(struct image_version));
        run_img_ver = (struct image_version *)run_img_version;
    }
    PRINTF("run image verison: %c.%c.%c\r\n", run_img_ver->iv_major, run_img_ver->iv_minor, run_img_ver->iv_revision);

    boot_flash_area_read(FLASH_AREA_IMAGE_3_OFFSET + IMAGE_VERSION_OFFSET, ota_img_version, 8);
    ota_img_ver = (struct image_version *)ota_img_version;
    PRINTF("ota image verison: %c.%c.%c\r\n", ota_img_ver->iv_major, ota_img_ver->iv_minor, ota_img_ver->iv_revision);

    if(  (run_img_ver->iv_major  < ota_img_ver->iv_major) ||
            ((run_img_ver->iv_major == ota_img_ver->iv_major) && (run_img_ver->iv_minor  < ota_img_ver->iv_minor)) ||
            ((run_img_ver->iv_major == ota_img_ver->iv_major) && (run_img_ver->iv_minor == ota_img_ver->iv_minor)  && (run_img_ver->iv_revision < ota_img_ver->iv_revision)) )
    {
    	for( ix = 0; ix < 15; ix++ )
    	{

            chr = *pimg_leng++;

            if(  ('0' <= chr) && (chr <= '9') )
            {
                img_leng    *= 10;
                img_leng    += chr - '0';
            }
            else
            {
                break;
            }
        }

        if( ( 0 < img_leng) && (img_leng <= (SLOT_SZ - 2 * PAGE_SZ)) )
        {
    		err_return = test_check_secureboot((uint8_t*)(BOOT_FLASH_SCRATCH_APP), img_leng, (uint8_t*)(BOOT_FLASH_SCRATCH_BASE + IITP_HEADER_IMAGE_SIZE_INFO_SIZE));

    		if( AURSARET_OK == err_return )
            {
                PRINTF("sign verify pass \r\n");

                srcBase = FLASH_AREA_IMAGE_3_OFFSET;

                if( runSlot == SLOT_1 )
                {
                    dstBase = FLASH_AREA_IMAGE_2_OFFSET;
                }
                else if( runSlot == SLOT_2 )
                {
                    dstBase = FLASH_AREA_IMAGE_1_OFFSET;
                }
                else
                {
                    dstBase = FLASH_AREA_IMAGE_2_OFFSET;
                }
                PRINTF("srcBase : %08x \r\n", srcBase);
                PRINTF("dstBase : %08x \r\n", dstBase);

                primask = DisableGlobalIRQ();

                img_leng += IITP_HEADER_SIZE;

                PRINTF("flash erase start \r\n");
                if( (status = boot_flash_area_erase(dstBase, SLOT_SZ)) == kStatus_Success ) {
                    PRINTF("flash erase end \r\n");
                    EnableGlobalIRQ(primask);

                    for( offset = 0; offset < img_leng; offset += PAGE_SZ ) {
                        (void)memset(buf, 0xFF, PAGE_SZ);
                        primask = DisableGlobalIRQ();
                        boot_flash_area_read(srcBase + offset, buf, ((offset + PAGE_SZ) < img_leng) ? PAGE_SZ : img_leng - offset);      // Bcoz sfw_img_inc_iitp_hdr has extra 4K bytes header

                        if( (status = boot_flash_area_write(dstBase + offset, (uint32_t *)buf, PAGE_SZ)) == kStatus_Success ) {
                            EnableGlobalIRQ(primask);
                            continue;
                        }
                        else
                        {
                            PRINTF("flash write fail! \r\n");
                            break;
                        }
                    }

                    EnableGlobalIRQ(primask);
                }
                else
                {
                    EnableGlobalIRQ(primask);
                }

                if( status == kStatus_Success )
                {
                    PRINTF("Signature Verification passed\r\n");
                    PRINTF("Img Verification Successed. press power reset button to start new version-up Img.\r\n");
                    GPIO_PinWrite(GPIO13, 3u, 0u);      // 1st  Red  LED Off
                    GPIO_PinWrite(GPIO13, 4u, 1u);      // 1st Green LED On
                    f_img_verify_result = IMG_VERIFY_PASSED;
                }
                else
                {
                    PRINTF("Error happened during FlexSPI NOR Flash handling.\r\n");
                    GPIO_PinWrite(GPIO13, 3u, 1u);      // 1st  Red  LED On
                    GPIO_PinWrite(GPIO13, 4u, 1u);      // 1st Green LED On
                    f_img_verify_result = IMG_VERIFY_DENYED;
                }
            }
            else
            {
                PRINTF("Signature Verification failed\r\n");
                GPIO_PinWrite(GPIO13, 3u, 0u);      // 1st  Red  LED Off
                GPIO_PinWrite(GPIO13, 4u, 0u);      // 1st Green LED Off
                f_img_verify_result = IMG_VERIFY_FAILED;
            }
        }
        else
        {
            PRINTF("Bad IITP-propritary secure firmware image formate.\r\n");
            GPIO_PinWrite(GPIO13, 3u, 1u);      // 1st  Red  LED On
            GPIO_PinWrite(GPIO13, 4u, 1u);      // 1st Green LED On
            f_img_verify_result = IMG_VERIFY_DENYED;
        }
    }
    else
    {
        PRINTF("OTA image version is same or lower than current running image version.\r\n");
        PRINTF("Current running image verison: %c.%c.%c\r\n", run_img_ver->iv_major, run_img_ver->iv_minor, run_img_ver->iv_revision);
        PRINTF("OTA downloadeded image verison: %c.%c.%c\r\n", ota_img_ver->iv_major, ota_img_ver->iv_minor, ota_img_ver->iv_revision);
        PRINTF("Downloaded OTA image is denyed.\r\n");
        GPIO_PinWrite(GPIO13, 3u, 1u);      // 1st  Red  LED On
        GPIO_PinWrite(GPIO13, 4u, 1u);      // 1st Green LED On
        f_img_verify_result = IMG_VERIFY_DENYED;
    }

    return status;
}

int set_magic_field_on_remap_flag(void)
{
    uint8_t                 sector_incl_remap_flag[SECTOR_SZ] = {0U};
    int                     status  = kStatus_Fail;
    volatile uint32_t       primask = 0U;

    primask = DisableGlobalIRQ();
    boot_flash_area_read(REMAP_FLAG_SECTOR_OFFSET, sector_incl_remap_flag, SECTOR_SZ);
    EnableGlobalIRQ(primask);

    primask = DisableGlobalIRQ();

    PRINTF("Remap Erase Start \r\n");
    if( (status = boot_flash_area_erase(REMAP_FLAG_SECTOR_OFFSET, SECTOR_SZ)) == kStatus_Success ) {
        EnableGlobalIRQ(primask);
        PRINTF("Remap Erase End \r\n");

        if( (sector_incl_remap_flag[REMAP_FLAG_OFFSET_IN_SECTOR] == SLOT_1) ||     // consider Exceptional Case
            (sector_incl_remap_flag[REMAP_FLAG_OFFSET_IN_SECTOR] == SLOT_2) )
        {
            ;
        }
        else
        {
            sector_incl_remap_flag[REMAP_FLAG_OFFSET_IN_SECTOR] = SLOT_1;
        }

        sector_incl_remap_flag[REMAP_FLAG_OFFSET_IN_SECTOR + REMAP_IMAGE_OK_SIZE] = IMAGE_OK_SET;

        (void)memcpy(sector_incl_remap_flag + REMAP_FLAG_OFFSET_IN_SECTOR + REMAP_IMAGE_OK_SIZE + REMAP_IMAGE_POSITION_SIZE, REMAP_MAGIC, REMAP_MAGIC_SIZE);

        primask = DisableGlobalIRQ();

        PRINTF("Remap Update Start \r\n");
        if( (status = boot_flash_area_write(REMAP_FLAG_SECTOR_OFFSET, sector_incl_remap_flag, SECTOR_SZ)) == kStatus_Success ) {
            EnableGlobalIRQ(primask);
            PRINTF("Remap Update End \r\n");
        }
        else
        {
            EnableGlobalIRQ(primask);
        }
    }
    else
    {
        EnableGlobalIRQ(primask);
    }

    return status;
}

#define IMAGE_OK_UNSET                  0xFF
#define IMAGE_OK_SET                    0x01
#define IMAGE_OK_REVERT                 0x04

int clear_imageOK_and_magic_if_set(void)
{
    uint8_t                 sector_incl_remap_flag[SECTOR_SZ] = {0U};
    int                     status  = kStatus_Fail;
    volatile uint32_t       primask = 0U;

    primask = DisableGlobalIRQ();
    boot_flash_area_read(REMAP_FLAG_SECTOR_OFFSET, sector_incl_remap_flag, SECTOR_SZ);
    EnableGlobalIRQ(primask);

    if( sector_incl_remap_flag[REMAP_FLAG_OFFSET_IN_SECTOR + REMAP_IMAGE_POSITION_SIZE] == IMAGE_OK_REVERT ) {
        primask = DisableGlobalIRQ();

        PRINTF("IMAGE_OK_REVERT \r\n");

        if( (status = boot_flash_area_erase(REMAP_FLAG_SECTOR_OFFSET, SECTOR_SZ)) == kStatus_Success ) {
            EnableGlobalIRQ(primask);

            *(uint8_t*)(sector_incl_remap_flag + REMAP_FLAG_OFFSET_IN_SECTOR + REMAP_IMAGE_POSITION_SIZE)   = IMAGE_OK_UNSET;
            (void)memset(sector_incl_remap_flag + REMAP_FLAG_OFFSET_IN_SECTOR + REMAP_IMAGE_POSITION_SIZE + REMAP_IMAGE_OK_SIZE, 0xFF, REMAP_MAGIC_SIZE);

            primask = DisableGlobalIRQ();

            if( (status = boot_flash_area_write(REMAP_FLAG_SECTOR_OFFSET, sector_incl_remap_flag, SECTOR_SZ)) == kStatus_Success ) {
                EnableGlobalIRQ(primask);
            }
            else
            {
                EnableGlobalIRQ(primask);
            }
        }
        else
        {
            EnableGlobalIRQ(primask);
        }
    }
    else
    {
        EnableGlobalIRQ(primask);
    }

    return kStatus_Success;
}

__attribute__((optimize(0))) void time_delay_ms(uint32_t dtime)
{

        while( dtime-- )
        {
                __asm("NOP");
        }
}

/*!
 * @brief Periodic job doing Image downloading or printing of "Hello KETI." message.
 */
static void test_periodic_job_keti()
{
    static uint32_t    cnt              = 0U;
    static uint32_t    f_oneshot_fired  = 0U;

    PRINTF("Hello KETI.\r\n");

    /*
     * develop your own source code ...
     */

    if( !f_oneshot_fired && (cnt++ == 10U) ) {
        f_img_downloaded    = 1U;
        f_oneshot_fired     = 1U;
    }
}

static void periodic_job_autocrypt()
{
    static uint32_t         red_led_blink   = 0;

    if( f_img_downloaded )
    {
        do_firmware_update();

        if( f_img_verify_result == IMG_VERIFY_PASSED ) {
            set_magic_field_on_remap_flag();
        }
        else if( f_img_verify_result == IMG_VERIFY_FAILED ) {
            ;
        }
        else if( f_img_verify_result == IMG_VERIFY_DENYED ) {
            ;
        }
        else {
            ;
        }

        f_img_downloaded    = 0U;
    }
    else if( f_img_verify_result == IMG_VERIFY_NONE )
    {
        PRINTF("Hello Autocrypt.\r\n");
    }
    else if( f_img_verify_result == IMG_VERIFY_DENYED )
    {
        PRINTF("Hello Autocrypt.\r\n");
    }
    else if( f_img_verify_result == IMG_VERIFY_PASSED )
    {
        PRINTF("Hello Autocrypt.\r\n");
    }
    else if( f_img_verify_result == IMG_VERIFY_FAILED )
    {
        PRINTF("Img Verification Failed.\r\n");

        if( red_led_blink & 0x00000001 ) {
            GPIO_PinWrite(GPIO13, 3u, 0u);      // 1st  Red  Off
            red_led_blink   &= 0x00000000;
        }
        else
        {
            GPIO_PinWrite(GPIO13, 3u, 1u);      // 1st  Red  On
            red_led_blink   |= 0x00000001;
        }
    }
    else
    {
        PRINTF("Hello Autocrypt.\r\n");
    }
}

static void test_periodic_job_dhautoware()
{
    if( f_img_verify_result == IMG_VERIFY_PASSED ) {
        // develop your own source code
        // f_img_verify_result = IMG_VERIFY_NONE;
    }
    else if( f_img_verify_result == IMG_VERIFY_FAILED ) {
        // develop your own source code
        // f_img_verify_result = IMG_VERIFY_NONE;
    }
    else if( f_img_verify_result == IMG_VERIFY_DENYED ) {
        // develop your own source code
        // f_img_verify_result = IMG_VERIFY_NONE;
    }
    else {
        // develop your own source code
        f_img_verify_result = IMG_VERIFY_NONE;
    }

    PRINTF("Hello DH AUTOWARE.\r\n");
}

static void test_periodic_job_koreaUniv()
{
    // develop your own source code

    PRINTF("Hello Korea University.\r\n");
}

#define IOMUXC_GPR_GPR30_REG 0x400CC420 /* Flash remapping start address  */
#define IOMUXC_GPR_GPR31_REG 0x400CC424 /* Flash remapping end address    */
#define IOMUXC_GPR_GPR32_REG 0x400CC428 /* Flash remapping offset address */

void SBL_EnableRemap(uint32_t start_addr, uint32_t end_addr, uint32_t off)
{
    uint32_t *remap_start  = (uint32_t *)IOMUXC_GPR_GPR30_REG;
    uint32_t *remap_end    = (uint32_t *)IOMUXC_GPR_GPR31_REG;
    uint32_t *remap_offset = (uint32_t *)IOMUXC_GPR_GPR32_REG;

    *remap_start  = start_addr | 0x1;
    *remap_end    = end_addr;
    *remap_offset = off;
}

void SBL_DisableRemap(void)
{
    uint32_t *remap_start  = (uint32_t *)IOMUXC_GPR_GPR30_REG;
    uint32_t *remap_end    = (uint32_t *)IOMUXC_GPR_GPR31_REG;
    uint32_t *remap_offset = (uint32_t *)IOMUXC_GPR_GPR32_REG;

    /* Disable offset first! */
    *remap_offset = 0;
    *remap_start  = 0;
    *remap_end    = 0;
}

#define DLY_ITER    (1666UL)
#define DLY_TIME    (10000UL)

/*!
 * @brief Application main task entry point called by the main() in os abstract layer.
 */
//int sfw_main(void)
//void sfw_main(void *arg)
void sfw_main(void)
{
	uint8_t run_slot = 0U;
	uint8_t image_ok = 0U;
	struct image_version    *run_img_ver = NULL;
	uint8_t                 run_img_version[8] = {0U};
    int         ix          = 0;
     gpio_pin_config_t gpio13_pinM13_config = {
        .direction = kGPIO_DigitalOutput,
        .outputLogic = 0U,
        .interruptMode = kGPIO_NoIntmode
    };

    GPIO_PinInit(GPIO13,  3U, &gpio13_pinM13_config);       // 1st  Red  LED off
    GPIO_PinInit(GPIO13,  4U, &gpio13_pinM13_config);       // 1st Green LED off
    GPIO_PinInit(GPIO13,  5U, &gpio13_pinM13_config);       // 2nd  Red  LED off
    GPIO_PinInit(GPIO13,  6u, &gpio13_pinM13_config);       // 2nd Green LED off
    GPIO_PinInit(GPIO13,  7u, &gpio13_pinM13_config);       // 3rd  Red  LED off
    GPIO_PinInit(GPIO13,  8u, &gpio13_pinM13_config);       // 3rd Green LED off
    GPIO_PinInit(GPIO13,  9u, &gpio13_pinM13_config);       // 4th  Red  LED off
    GPIO_PinInit(GPIO13, 10u, &gpio13_pinM13_config);       // 4th Green LED off
    GPIO_PinInit(GPIO13, 11u, &gpio13_pinM13_config);       // 5th  Red  LED off
    GPIO_PinInit(GPIO13, 12u, &gpio13_pinM13_config);       // 5th Green LED off

    GPIO_PinWrite(GPIO13, 12, 1u);                          // 5th Green LED On

    boot_flash_area_read(REMAP_FLAG_ADDRESS, &run_slot, sizeof(run_slot));
    PRINTF("Run Slot : %d \r\n", run_slot);
    boot_flash_area_read(REMAP_FLAG_ADDRESS + REMAP_IMAGE_POSITION_SIZE, &image_ok, sizeof(image_ok));
    PRINTF("Image Ok (%d) : %s \r\n", image_ok, image_ok == IMAGE_OK_REVERT ? "REVERT":"NONE");

    if( run_slot == SLOT_1 )
    {
        boot_flash_area_read(FLASH_AREA_IMAGE_1_OFFSET + IMAGE_VERSION_OFFSET, run_img_version, sizeof(struct image_version));
        run_img_ver = (struct image_version *)run_img_version;
    }
    else if( run_slot == SLOT_2 )
    {
        boot_flash_area_read(FLASH_AREA_IMAGE_2_OFFSET + IMAGE_VERSION_OFFSET, run_img_version, sizeof(struct image_version));
        run_img_ver = (struct image_version *)run_img_version;
    }
    else
    {
        boot_flash_area_read(FLASH_AREA_IMAGE_1_OFFSET + IMAGE_VERSION_OFFSET, run_img_version, sizeof(struct image_version));
        run_img_ver = (struct image_version *)run_img_version;
    }
    PRINTF("run image verison: %c.%c.%c\r\n", run_img_ver->iv_major, run_img_ver->iv_minor, run_img_ver->iv_revision);

    while( 1 ) {
        test_periodic_job_keti();
        periodic_job_autocrypt();
        test_periodic_job_dhautoware();
        test_periodic_job_koreaUniv();
        PRINTF("\r\n");

        //vTaskDelay(SWF_MAIN_TASK_DELAY_TIME);
        for( ix = 0; ix < (DLY_ITER * 25UL); ix++ )
        {
            time_delay_ms(DLY_TIME);
        }
    }
}
