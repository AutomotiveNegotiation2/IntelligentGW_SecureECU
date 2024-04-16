/*
*
* Copyright (c) 2022 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/**
 *  \file boot_app_ospi.c
 *
 *  \brief supporting file for main file for ospi
 */

#include "boot_app_priv.h"
#include "boot_app_ospi.h"

int32_t BootApp_OSPILeaveConfigSPI()
{
    int32_t retVal = E_PASS;
    Board_flashHandle flashHandle;
    Board_FlashInfo *flashInfo;

#if defined(UART_PRINT_DEBUG)
    UART_printf("Entered BootApp_OSPILeaveConfigSPI function...\n");
#endif

    /* Get default OSPI cfg */
    OSPI_socGetInitCfg(BOARD_OSPI_DOMAIN, BOARD_OSPI_NOR_INSTANCE, &gOspiCfg);

    gOspiCfg.funcClk = OSPI_MODULE_CLK_133M;
    /* Configure the flash for SPI mode */
    gOspiCfg.xferLines = OSPI_XFER_LINES_SINGLE;
    /* Put controller in DAC mode so flash ID can be read directly */
    gOspiCfg.dacEnable = true;
    /* Disable PHY in legacy SPI mode (1-1-1) */
    gOspiCfg.phyEnable = false;
    gOspiCfg.dtrEnable = false;
    gOspiCfg.xipEnable = false;

    /* Set the default SPI init configurations */
    OSPI_socSetInitCfg(BOARD_OSPI_DOMAIN, BOARD_OSPI_NOR_INSTANCE, &gOspiCfg);

    flashHandle = Board_flashOpen(BOARD_FLASH_ID_MT35XU512ABA1G12,
                            BOARD_OSPI_NOR_INSTANCE, NULL);

    if (flashHandle)
    {
        UART_printf("OSPI flash left configured in Legacy SPI mode.\n");
        flashInfo = (Board_FlashInfo *)flashHandle;
        UART_printf("\n OSPI NOR device ID: 0x%x, manufacturer ID: 0x%x \n",
                flashInfo->device_id, flashInfo->manufacturer_id);
        Board_flashClose(flashHandle);
    }
    else
    {
        UART_printf("Board_flashOpen failed in SPI mode!!\n");
        retVal = E_FAIL;
    }

    return(retVal);
}

/* Boot all the OSPI images defined in the array */

int32_t BootApp_OSPIBootStageImage(sblEntryPoint_t *pEntry, uint32_t address)
{
    int32_t status = E_FAIL;

    if ((0U != address) && (NULL != pEntry))
    {
        if (address != MAIN_DOMAIN_HLOS)
        {
            status = BootApp_OSPIBootImageLate(&gK3xx_evmEntry, address);
        }
        #if defined(MPU1_HLOS_BOOT_ENABLED)
        else
        {
            /* Load the HLOS appimages */
            status = BootApp_OSPIBootImageLate(&gK3xx_evmEntry, OSPI_OFFSET_A72IMG1);
            if (status != E_PASS)
            {
                UART_printf("Error parsing A72 appimage #1 for HLOS boot\n");
            }
            else
            {
                status = BootApp_OSPIBootImageLate(&gK3xx_evmEntry, OSPI_OFFSET_A72IMG2);
                if (status != E_PASS)
                {
                    UART_printf("Error parsing A72 appimage #2 for HLOS boot\n");
                }
                #if defined(HLOS_BOOT_LINUX_OS)
                else
                {
                    status = BootApp_OSPIBootImageLate(&gK3xx_evmEntry, OSPI_OFFSET_A72IMG3);
                    if (status != E_PASS)
                        UART_printf("Error parsing A72 appimage #3 for HLOS boot\n");
                }
                #endif
            }

            if (status == E_PASS)
            {
                /* Set the A72 entry point at the ATF address */
                pEntry->CpuEntryPoint[MPU1_CPU0_ID] = ATF_START_RAM_ADDR;
                BootApp_McuDCacheClean((void *)0x70000000, 0x20000);
            }
        } /* if (address == MAIN_DOMAIN_HLOS) */
        #endif /* #if defined(MPU1_HLOS_BOOT_ENABLED)*/
    } /* if ((NULL != address) && (NULL != pEntry)) */

    return status;
}

int32_t BootApp_OSPIBootImageLate(sblEntryPoint_t *pEntry, uint32_t imageOffset)
{
    int32_t retVal = E_FAIL;

    uint32_t offset = 0;

    /* Load the MAIN domain remotecore images included in the appimage */
    offset = imageOffset;

    fp_readData = &BootApp_XIPReadMem;
    fp_seek     = &BootApp_XIPSeekMem;

    retVal = SBL_MulticoreImageParse((void *) &offset,
                                      imageOffset,
                                      pEntry,
                                      SBL_SKIP_BOOT_AFTER_COPY);

    if (retVal != E_PASS)
        UART_printf("Error parsing Main Domain appimage\n");

    return retVal;
}

/* read of block of data from buffer */
int32_t BootApp_XIPReadMem(void    *buff,
                    void    *srcOffsetAddr,
                    uint32_t size)
{

    uint32_t imgOffset;
    int32_t  retVal = E_PASS;

    imgOffset = *((uint32_t*)srcOffsetAddr);

    memcpy(buff, (void*)((uint8_t*)gXipMemBase + imgOffset), size);

    /* Advance srcOffsetAddr for the next section to be read */
    *((uint32_t *) srcOffsetAddr) += size;

    return retVal;
}

/* move the buffer pointer */
void BootApp_XIPSeekMem(void *srcAddr, uint32_t location)
{
    *((uint32_t *) srcAddr) = location;
}