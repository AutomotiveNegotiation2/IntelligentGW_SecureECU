/*
 *
 * Copyright (c) 2018 Texas Instruments Incorporated
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

#include <utils/console_io/include/app_log.h>
#include <ti/drv/sciclient/sciclient.h>
#include <ti/drv/sciclient/sciserver_tirtos.h>
#include <stdio.h>

#if defined(SOC_AM62A)
#include <ti/board/board.h>
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#endif

/* High Priority for SCI Server - must be higher than Low priority task */
#define SETUP_SCISERVER_TASK_PRI_HIGH   (5)
/*
 * Low Priority for SCI Server - must be higher than IPC echo test tasks
 * to prevent delay in handling Sciserver requests when test is performing
 * multicore ping/pong.
 */
#define SETUP_SCISERVER_TASK_PRI_LOW    (4)

int32_t appSciserverSciclientInit()
{
    int32_t retVal = CSL_PASS;
    Sciclient_ConfigPrms_t  clientParams;

#if defined(SOC_AM62A)
    Board_initCfg   boardCfg;
#endif

    retVal = Sciclient_configPrmsInit(&clientParams);

    if(retVal==CSL_PASS)
    {
        retVal = Sciclient_boardCfgParseHeader(
                (uint8_t *) SCISERVER_COMMON_X509_HEADER_ADDR,
                &clientParams.inPmPrms, &clientParams.inRmPrms);
    }

#if defined(SOC_AM62A)
    if(retVal==CSL_PASS)
    {
        boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_UART_STDIO;
        Board_init(boardCfg);
    }
#endif

    if(retVal==CSL_PASS)
    {
        retVal = Sciclient_init(&clientParams);
    }

    return retVal;
}

int32_t appSciserverSciclientDeInit()
{
    int32_t retVal = 0;

    retVal = Sciclient_deinit();
    if(retVal!=0)
    {
        #if defined(SOC_AM62A)
        UART_printf("SCICLIENT: ERROR: Sciclient deinit failed !!!\n");
        #else
        appLogPrintf("SCICLIENT: ERROR: Sciclient deinit failed !!!\n");
        #endif
    }

    return retVal;
}

void appSciserverInit(void* arg0, void* arg1)
{
    int32_t retVal = CSL_PASS;
    Sciserver_TirtosCfgPrms_t serverParams;

    #if defined(SOC_AM62A)
    char *version_str = NULL;
    char *rmpmhal_version_str = NULL;
    #endif

    retVal = Sciserver_tirtosInitPrms_Init(&serverParams);

    serverParams.taskPriority[SCISERVER_TASK_USER_LO] = SETUP_SCISERVER_TASK_PRI_LOW;
    serverParams.taskPriority[SCISERVER_TASK_USER_HI] = SETUP_SCISERVER_TASK_PRI_HIGH;

    if(retVal==CSL_PASS)
    {
        retVal = Sciserver_tirtosInit(&serverParams);
    }

    #if defined(SOC_AM62A)
    version_str = Sciserver_getVersionStr();
    rmpmhal_version_str = Sciserver_getRmPmHalVersionStr();
    UART_printf("##DM Built On: %s %s\n", __DATE__, __TIME__);
    UART_printf("##Sciserver Version: %s\n", version_str);
    UART_printf("##RM_PM_HAL Version: %s\n", rmpmhal_version_str);

    if (retVal == CSL_PASS)
    {
        UART_printf("##Starting Sciserver..... PASSED\n");
    }
    else
    {
        UART_printf("Starting Sciserver..... FAILED\n");
    }
    #endif
}

void appSciserverDeInit()
{
    Sciserver_tirtosDeinit();

    return;
}
