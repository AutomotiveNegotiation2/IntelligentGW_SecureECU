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
 *  \file boot_app_mmcsd.c
 *
 *  \brief supporting file for main file for mmcsd
 */

#include "boot_app_priv.h"
#include "boot_app_mmcsd.h"

int32_t BootApp_MMCBootImageInit()
{
    int32_t retVal = E_PASS;
    MMCSD_v2_HwAttrs hwAttrsConfig;

    if (MMCSD_socGetInitCfg(FATFS_initCfg[0].drvInst,&hwAttrsConfig) != 0)
    {
        UART_printf("\nUnable to get config.Exiting. TEST FAILED.\r\n");
        retVal = E_FAIL;
    }

    hwAttrsConfig.enableInterrupt = ((uint32_t)(0U));
    hwAttrsConfig.configSocIntrPath=NULL;

    if (MMCSD_socSetInitCfg(FATFS_initCfg[0].drvInst,&hwAttrsConfig) != 0)
    {
        UART_printf("\nUnable to set config.Exiting. TEST FAILED.\r\n");
        retVal = E_FAIL;
    }

    /* Initialization of the driver. */
    FATFS_init();

    /* MMCSD FATFS initialization */
    FATFS_open(0U, NULL, &sbl_fatfsHandle);

    return (retVal);
}

void BootApp_MMCBootImageDeInit()
{
    FATFS_close(sbl_fatfsHandle);
    sbl_fatfsHandle = NULL;
}

int32_t BootApp_MMCBootImageLate(sblEntryPoint_t *pEntry, TCHAR *fileName)
{
    int32_t  retVal = E_PASS;
    FIL      fp     = {0};
    FRESULT  fresult;

    fresult = f_open(&fp, fileName, ((BYTE)FA_READ));
    if (fresult != FR_OK)
    {
        UART_printf("\n SD Boot - File open fails \n");
        retVal = E_FAIL;
    }
    else
    {
        UART_printf("\n BootApp_MMCBootImageLate: fp 0x 0x%x, fileName is %s\n",
                    (unsigned int)((void *) &fp), fileName);
            fp_readData = &SBL_FileRead;
            fp_seek     = &SBL_FileSeek;

            retVal = SBL_MulticoreImageParse((void *) &fp, 0, pEntry,
                                                SBL_SKIP_BOOT_AFTER_COPY);

        UART_printf("\n Called SBL_MulticoreImageParse, status = %d\n", retVal);

        f_close(&fp);
    }

    return retVal;
}

int32_t BootApp_MMCSDBootStageImage(sblEntryPoint_t *pEntry, TCHAR *fileName)
{
    int32_t status      = E_FAIL;
    #if defined(MPU1_HLOS_BOOT_ENABLED)
        TCHAR  *fileNameAtf = "0:/atf_optee.appimage";
    #ifdef HLOS_BOOT_QNX_OS
        TCHAR  *fileHLOS    = "0:/ifs_qnx.appimage";
    #else
        TCHAR  *fileNameDtb = "0:/tidtb_linux.appimage";
        TCHAR  *fileHLOS    = "0:/tikernelimage_linux.appimage";
    #endif
    #endif

    if ((NULL != fileName) && (NULL != pEntry))
    {
        if (strcmp(fileName, MAIN_DOMAIN_HLOS_NAME) != 0)
        {
            status = BootApp_MMCBootImageLate(&gK3xx_evmEntry, fileName);
        }
        #if defined(MPU1_HLOS_BOOT_ENABLED)
        else
        {
            /* Read & Parse images for MPU1 HLOS boot from other files */
            status = BootApp_MMCBootImageLate(&gK3xx_evmEntry, fileNameAtf);
            if (status != CSL_PASS)
            {
                UART_printf("Error copying and parsing A72 appimage #1 for HLOS boot\n");
            }
            else
            {
                status = BootApp_MMCBootImageLate(&gK3xx_evmEntry, fileHLOS);
                if (status != CSL_PASS)
                {
                    UART_printf("Error copying and parsing A72 appimage #2 for HLOS boot\n");
                }
                #if defined(HLOS_BOOT_LINUX_OS)
                    else
                    {
                        status = BootApp_MMCBootImageLate(&gK3xx_evmEntry, fileNameDtb);
                        if (status != CSL_PASS)
                        {
                            UART_printf("Error copying and parsing A72 appimage #3 for HLOS boot\n");
                        }
                    }
                #endif
            }
            if (status == CSL_PASS)
            {
                /* Set the A72 entry point at the ATF address */
                (&gK3xx_evmEntry)->CpuEntryPoint[MPU1_CPU0_ID] = ATF_START_RAM_ADDR;
                BootApp_McuDCacheClean((void *)0x70000000, 0x20000);
            }
        } /* if (address == MAIN_DOMAIN_HLOS) */
    #endif /* #if defined(MPU1_HLOS_BOOT_ENABLED)*/
    } /* if ((NULL != fileName) && (NULL != pEntry)) */

    return status;
}
