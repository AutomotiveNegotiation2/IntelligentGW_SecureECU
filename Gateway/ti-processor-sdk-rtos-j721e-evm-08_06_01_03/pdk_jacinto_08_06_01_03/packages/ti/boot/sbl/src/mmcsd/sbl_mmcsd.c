/**
 *  \file    sbl_mmcsd.c
 *
 *  \brief   This file contains functions for MMCSD File read operations for SBL
 *
 */

/*
 * Copyright (C) 2015 - 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>

/* TI-RTOS Header files */
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/mmcsd/MMCSD.h>
#include <ti/drv/mmcsd/soc/MMCSD_soc.h>
#include <ti/drv/mmcsd/src/MMCSD_osal.h>

/* SBL Header files. */
#include "sbl_rprc_parse.h"
#include "sbl_mmcsd.h"

/* K3 Header files */
#ifdef BUILD_MCU
#include <sbl_sci_client.h>
#endif

/**
 * \brief    SBL_FileRead function reads N bytes from SD card and
 *           advances the cursor.
 *
 * \param     buff - Pointer to data buffer
 * \param     fileptr - Read head pointer
 * \param     size - Number of bytes to read
 *
 * \return    Error code on file error
 */
int32_t SBL_FileRead(void  *buff,
                     void *fileptr,
                     uint32_t size);

/**
 *  \brief    SBL_FileSeek function to move the read head by n bytes
 *
 *  \param    srcAddr - Read head pointer
 *  \param    location - Move the read head pointer by n bytes
 *
 * \return  none
 */
void SBL_FileSeek(void *fileptr, uint32_t location);



int32_t SBL_loadMMCSDBootFile(FIL * fp);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* MMCSD function table for MMCSD implementation */
FATFS_DrvFxnTable FATFS_drvFxnTable = {
    &MMCSD_close,
    &MMCSD_control,
    &MMCSD_init,
    &MMCSD_open,
    &MMCSD_write,
    &MMCSD_read
};

/* FATFS configuration structure */
FATFS_HwAttrs FATFS_initCfg[_VOLUMES] =
{
    {
#if defined(j721e_evm) || defined(j7200_evm) || defined(j721s2_evm) || defined(j784s4_evm)
        1U
#else
        0U
#endif
    },
    {
#if defined(j721e_evm) || defined(j7200_evm) || defined(j721s2_evm) || defined(j784s4_evm)
        0U
#else
        1U
#endif
    },
    {
#if defined(j721e_evm) || defined(j7200_evm) || defined(j721s2_evm) || defined(j784s4_evm)
        0U
#else
        1U
#endif
    },
    {
#if defined(j721e_evm) || defined(j7200_evm) || defined(j721s2_evm) || defined(j784s4_evm)
        0U
#else
        1U
#endif
    }
};

/* FATFS objects */
FATFS_Object FATFS_objects[_VOLUMES];

/* FATFS Handle */
FATFS_Handle sbl_fatfsHandle = NULL;

/* FATFS configuration structure */
const FATFS_Config FATFS_config[_VOLUMES + 1] = {
    {
        &FATFS_drvFxnTable,
        &FATFS_objects[0],
        &FATFS_initCfg[0]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[1],
         &FATFS_initCfg[1]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[2],
         &FATFS_initCfg[2]
    },

    {NULL, NULL, NULL},

    {NULL, NULL, NULL}
};

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
#define SBL_WKUP_DEVSTAT_PRIMARY_BOOT_MASK      (0x78U)
#define SBL_WKUP_DEVSTAT_PRIMARY_BOOT_MMCSD     (0x0U)
#define SBL_MAIN_DEVSTAT_PRIMARY_BUS_WIDTH_MASK (0x20U)
#define SBL_MAIN_DEVSTAT_BACKUP_BOOT_MASK       (0xEU)
#define SBL_MAIN_DEVSTAT_BACKUP_BOOT_MMCSD      (0xAU)
#define SBL_MAIN_DEVSTAT_PRIMARY_BOOT_B_MASK    (0x1U)
#endif

#ifdef BUILD_MCU
int32_t SBL_ReadSysfwImage(void **pBuffer, uint32_t num_bytes)
{
    int32_t retVal = CSL_PASS;
#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    const TCHAR *fileName = "0:/tifs.bin";
#else
    const TCHAR *fileName = "0:/sysfw.bin";
#endif
    FIL     fp = {0};
    FRESULT  fresult;
    uint32_t bytes_read = 0;
    void *sysfw_ptr = *pBuffer;
    MMCSD_v2_HwAttrs hwAttrsConfig;

     if(MMCSD_socGetInitCfg(FATFS_initCfg[0].drvInst,&hwAttrsConfig)!=0) {
       UART_printf("\nUnable to get config.Exiting. TEST FAILED.\r\n");
       retVal = E_FAIL;
     }

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    uint32_t wkupCtrlDevstat = (*((volatile uint32_t *)(CSL_WKUP_CTRL_MMR0_CFG0_BASE + CSL_WKUP_CTRL_MMR_CFG0_WKUP_DEVSTAT)));
    uint32_t mainCtrlDevstat = (*((volatile uint32_t *)(CSL_CTRL_MMR0_CFG0_BASE + CSL_MAIN_CTRL_MMR_CFG0_MAIN_DEVSTAT)));

    if(((wkupCtrlDevstat & SBL_WKUP_DEVSTAT_PRIMARY_BOOT_MASK) == SBL_WKUP_DEVSTAT_PRIMARY_BOOT_MMCSD) &&
       ((mainCtrlDevstat & SBL_MAIN_DEVSTAT_PRIMARY_BOOT_B_MASK) == SBL_MAIN_DEVSTAT_PRIMARY_BOOT_B_MASK))
    {
        /* MMCSD as primary bootmode */
        /* Check MAIN CTRL MMR DEVSTAT register for Primary boot mode Bus Width */
        if((mainCtrlDevstat & SBL_MAIN_DEVSTAT_PRIMARY_BUS_WIDTH_MASK) == SBL_MAIN_DEVSTAT_PRIMARY_BUS_WIDTH_MASK)
        {
            hwAttrsConfig.supportedBusWidth = MMCSD_BUS_WIDTH_1BIT;
        }
        else
        {
            hwAttrsConfig.supportedBusWidth = MMCSD_BUS_WIDTH_4BIT;
        }
    }
    else if((mainCtrlDevstat & SBL_MAIN_DEVSTAT_BACKUP_BOOT_MASK) == SBL_MAIN_DEVSTAT_BACKUP_BOOT_MMCSD)
    {
        /* MMCSD as backup bootmode only supports 1-bit bus width, as set by ROM code */
        hwAttrsConfig.supportedBusWidth = MMCSD_BUS_WIDTH_1BIT;
    }
    else
    {
        hwAttrsConfig.supportedBusWidth = MMCSD_BUS_WIDTH_4BIT;
    }
#endif

    hwAttrsConfig.enableInterrupt = ((uint32_t)(0U));
    hwAttrsConfig.configSocIntrPath=NULL;

    /* Disabling DMA if enabled already while reading SYSFW since SBL loaded memory 
       is firewalled for DMA access. Enable the DMA after reading SYSFW */
    #if defined(BUILD_HS)
        hwAttrsConfig.enableDma = 0;
    #endif

    if(MMCSD_socSetInitCfg(FATFS_initCfg[0].drvInst,&hwAttrsConfig)!=0) {
       UART_printf("\nUnable to set config.Exiting. TEST FAILED.\r\n");
       retVal = E_FAIL;
     }

    /* Initialization of the driver. */
    FATFS_init();

    /* MMCSD FATFS initialization */
    FATFS_open(0U, NULL, &sbl_fatfsHandle);

    fresult = f_open(&fp, fileName, ((BYTE)FA_READ));
    if (fresult != FR_OK)
    {
#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
        UART_printf("\n SD Boot - tifs File open fails \n");
#else
        UART_printf("\n SD Boot - sysfw File open fails \n");
#endif
        retVal = E_FAIL;
    }
    else
    {
        fresult  = f_read(&fp, sysfw_ptr, num_bytes, &bytes_read);
        if (fresult != FR_OK)
        {
#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
            UART_printf("\n SD Boot - tifs read fails \n");
#else
            UART_printf("\n SD Boot - sysfw read fails \n");
#endif
            retVal = E_FAIL;
        }

        f_close(&fp);
    }

    /* Re-Enabling DMA since TIFS is already copied to OCMC by this time */
    #if defined(BUILD_HS)
        hwAttrsConfig.enableDma = 1;
        if(MMCSD_socSetInitCfg(FATFS_initCfg[0].drvInst,&hwAttrsConfig)!=0) 
        {
            UART_printf("\nUnable to set MMCSD config, exiting. Test Failed.\r\n");
            retVal = E_FAIL;
        }
    #endif

    FATFS_close(sbl_fatfsHandle);
    sbl_fatfsHandle = NULL;

    return retVal;
}
#endif

int32_t SBL_MMCBootImage(sblEntryPoint_t *pEntry)
{
    int32_t retVal = E_PASS;
    const TCHAR *fileName = "0:/app";
    FIL     fp = {0};
    FRESULT  fresult;

    /* Initialization of the driver. */
    FATFS_init();

    /* MMCSD FATFS initialization */
    FATFS_open(0U, NULL, &sbl_fatfsHandle);

    fresult = f_open(&fp, fileName, ((BYTE)FA_READ));
    if (fresult != FR_OK)
    {
        UART_printf("\n SD Boot - File open fails \n");
        retVal = E_FAIL;
    }
    else
    {
        fp_readData = &SBL_FileRead;
        fp_seek     = &SBL_FileSeek;

#if defined(SBL_ENABLE_HLOS_BOOT) && (defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4))
        retVal = SBL_MulticoreImageParse((void *) &fp, 0, pEntry, SBL_SKIP_BOOT_AFTER_COPY);
#else
        retVal = SBL_MulticoreImageParse((void *) &fp, 0, pEntry, SBL_BOOT_AFTER_COPY);
#endif

        f_close(&fp);
    }

    FATFS_close(sbl_fatfsHandle);
    sbl_fatfsHandle = NULL;

    return retVal;
}

int32_t SBL_FileRead(void       *buff,
                      void *fileptr,
                      uint32_t    size)
{
    FIL     *fp         = (FIL *) (fileptr);
    uint8_t *tmp_buff_ptr = (uint8_t *)buff;
    uint32_t i          = 0;
    uint32_t bytes_read = 0;
    uint32_t Max_read   = 0x400U; /*setting a fatfs read size of 1k */
    FRESULT  fresult    = FR_OK;
    int32_t retVal = E_FAIL;

    for (i = ((uint32_t)0U); i < (size / Max_read); ++i)
    {
        fresult  = f_read(fp, (void *)tmp_buff_ptr, Max_read, &bytes_read);
        tmp_buff_ptr = tmp_buff_ptr + bytes_read;
        if (fresult != FR_OK)
        {
            break;
        }
    }
    if (fresult == FR_OK)
    {
        fresult = f_read(fp, (void *)tmp_buff_ptr, (UINT) (size % Max_read), &bytes_read);
    }

    if (fresult == FR_OK)
    {
        retVal = E_PASS;
    }

    return retVal;
}

void SBL_FileSeek(void *fileptr, uint32_t location)
{
    FIL *fp = (FIL *) (fileptr);
    f_lseek(fp, location);
}

