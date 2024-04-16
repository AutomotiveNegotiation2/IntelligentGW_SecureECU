/*
*
* Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     CddIpcApp.c
 *
 *  \brief    This file contains the demo application for CDD IPC
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */



#include "CddIpcAppRProcLinux.h"

#include "app_utils.h"
#include <hw_include/lld_intr_router.h> /* CSL for interrupt router */
#include "IntRtr_Cfg.h" /* Defines the map / cfg for
                         * interrupt router, for this example
                         */
#include "SchM_Cdd_Ipc.h" /* Exclusive area */

#include <hw_include/soc.h>
/* Interrupts, Clear MCU Timer 0 */
#include <hw_include/arch/lld_arch.h>
#include <hw_include/hw_types.h>

/* SCI Client */
#include <ti/drv/sciclient/sciclient.h>
/* PM Lib */
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/dmsc/pmlib_sysconfig.h>
#include <ti/drv/pm/include/dmsc/pmlib_clkrate.h>

/* Interrupt Registrations */
#include <ti/osal/osal.h>

/* resource table for Linux */
#include "IpcRscTable.h"
#include <ti/drv/ipc/include/ipc_virtio.h>

#define System_printf Ipc_Trace_printf


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MSG_NORMAL      (APP_UTILS_PRINT_MSG_NORMAL)
/**< Message type */
#define MSG_STATUS      (APP_UTILS_PRINT_MSG_STATUS)
/**< Message type */
#define CDD_IPC_APP_MSG_DATA_SIZE   (256U)
/**< Size of message buffer to be transmitted */
#define CDD_IPC_APP_MSG_TX_RX_CNT   (10U)
/**< Number of times the messages that has to be transmitted and received */
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Cdd_IpcApp_PrintVersion(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32  Cdd_IpcAppDemoStatus = E_OK;
/**< Flag used for Demo status */
uint32 Cdd_IpcAppIterCntMpu10;
/**< Counter to track number of messages to be transmitted & received */
volatile uint32 Cdd_IpcAppNmsgCntMpu10;
/**< Counter to to indicate availability of messages from remote cores */

#if (STD_ON == CDD_IPC_ANNOUNCE_API)
volatile uint32 Cdd_IpcAppCtrlMsgMpu10;
/**< Flag to indicate which core has announced its availability */
#endif /* CDD_IPC_ANNOUNCE_API */

#ifdef CDD_IPC_REMOTE_CORE_MPU1_0_USED
static uint8 Cdd_IpcAppMpu10Buffer[CDD_IPC_APP_MSG_DATA_SIZE];
/**< Buffer used to transmit and receive messages, to/from MPU 10 */
#endif /* CDD_IPC_REMOTE_CORE_MPU1_0_USED */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 * \brief CDD IPC New message available notification
 *
 *  Would be invoked by the driver on reception of message from remote core.
 *  Name of this function is configurable, please refer configurator.
 */
void Cdd_IpcNewMessageNotify(uint32 comId)
{
#ifdef CDD_IPC_REMOTE_CORE_MPU1_0_USED
    if (CddIpcConf_IpcComChanId_Cdd_IpcMpu10 == comId)
    {
        Cdd_IpcAppNmsgCntMpu10++;
    }
#endif

    return;
}

#if (STD_ON == CDD_IPC_ANNOUNCE_API)
void Cdd_IpcNewCtrlMessageNotify(uint32 remoteProcId)
{
}
#endif /* (STD_ON == CDD_IPC_ANNOUNCE_API) */


/** \brief Main Entry point for demo application
 *
 *  Application flow
 *      1. Register interrupt and other common steps
 *      2. Initialize IPC
 *      3. If Announcement is disabled
 *          Send a message "Ping x" to all cores, where x is iteration
 *      4. If announcement is enabled
 *          Wait for control message and then send "Ping x"
 *      5. Wait infinitely for "Ping x" from all remote cores
 *      6. Print the received message CAUTION Received message should be NULL
 *          terminated
 */
int main(void)
{
    uint32 idx = 0U;
    const Cdd_IpcChannelType *pCommChCfg = CddIpcConfiguraions_PC.pChCfg;
    uint32 chanCount = CddIpcConfiguraions_PC.channelCount;
    volatile uint32 tempVar;
    Std_ReturnType rtnVal = E_NOT_OK;

#if (STD_ON == CDD_IPC_ANNOUNCE_API)
    uint32 coreIdx, comId, rCoreId;
#endif

#ifdef CDD_IPC_REMOTE_CORE_MPU1_0_USED
    uint32 mpu10Bufsize = CDD_IPC_APP_MSG_DATA_SIZE;
#endif

#if (STD_ON == CDD_IPC_ANNOUNCE_API)
    const char announceMsg[32U] = "ti.ipc4.ping-pong";
#endif

    /* Step 1 */
    Cdd_IpcAppDemoStatus = E_NOT_OK;
#ifdef UART_ENABLED
    AppUtils_Init();
#endif
    AppUtils_LogResult(APP_UTILS_TEST_STATUS_INIT);

    Cdd_IpcApp_PrintVersion();

    Cdd_IpcApp_Startup();

    AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux " Sample Application - STARTS !!! \n");

    Cdd_IpcAppIterCntMpu10 = CDD_IPC_APP_MSG_TX_RX_CNT;

#ifndef CDD_IPC_REMOTE_CORE_MPU1_0_USED
    Cdd_IpcAppIterCntMpu10 = 0U;
#endif
    Cdd_IpcAppNmsgCntMpu10 = 0U;

#if (STD_ON == CDD_IPC_ANNOUNCE_API)
    Cdd_IpcAppCtrlMsgMpu10 = 0U;
#endif /* CDD_IPC_ANNOUNCE_API */

    /* If A72 remote core is running Linux OS, then
     * load resource table
     */
    Ipc_loadResourceTable((void*)&ti_ipc_remoteproc_ResourceTable);
    AppUtils_Printf(MSG_NORMAL," Resource Table loaded, chanCount %d \n",
                        chanCount);

    /* Wait for Linux VDev ready... */
    for(idx = 0; idx < chanCount; idx++)
    {
       while(!Ipc_isRemoteReady(pCommChCfg[idx].remoteProcId))
        {
        }
    }

   AppUtils_Printf(MSG_NORMAL, "Linux VDEV ready now .....\n");

    /* Step 2 */
    Cdd_IpcInit();

   AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux "CDD Ipc Inited now .....\n");

#if (STD_ON == CDD_IPC_ANNOUNCE_API)
    /* For every remote core, Announce once */
    for (coreIdx = 0U; coreIdx < CddIpcConfiguraions_PC.coreIds.numProcs;
         coreIdx++)
    {
        rCoreId = CddIpcConfiguraions_PC.coreIds.remoteProcID[coreIdx];
        for (comId = 0U; comId < CddIpcConfiguraions_PC.channelCount; comId++)
        {
            if (rCoreId == CddIpcConfiguraions_PC.pChCfg[comId].remoteProcId)
            {
                Cdd_IpcAnnounce(announceMsg,
                                    CddIpcConfiguraions_PC.pChCfg[comId].id);
            }
        }
    }
#else
    /* Step 3 */
    Cdd_IpcApp_SendItrCntAndPingForAllCores();
#endif

	while (0U != Cdd_IpcAppIterCntMpu10)
    {
        
        /* Step 4 */
#ifdef CDD_IPC_REMOTE_CORE_MPU1_0_USED
    const Cdd_IpcChannelType *pChanCfg = CddIpcConfiguraions_PC.pChCfg;
	while ((0U != Cdd_IpcAppNmsgCntMpu10) && (0U != Cdd_IpcAppIterCntMpu10))
    {
		AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux  \
                            "waiting for message from MPU 1 0, EP[%d], ProcId[%d]\n", \
                              pChanCfg[CddIpcConf_IpcComChanId_Cdd_IpcMpu10].remoteEp, \
                              pChanCfg[CddIpcConf_IpcComChanId_Cdd_IpcMpu10].remoteProcId);
        AppUtils_Printf(MSG_NORMAL, "\n");
        rtnVal = Cdd_IpcReceiveMsg(CddIpcConf_IpcComChanId_Cdd_IpcMpu10,
                                &Cdd_IpcAppMpu10Buffer[0U], &mpu10Bufsize);

		if (rtnVal != E_OK)
		{
			AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux"IPC Receive message timedout!!!");
		}
        SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
        Cdd_IpcAppNmsgCntMpu10--;
        SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

       AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux  " Received %s Iteration %d from MPU 1 0\n",
                      &Cdd_IpcAppMpu10Buffer[0U], Cdd_IpcAppIterCntMpu10);

        Cdd_IpcAppIterCntMpu10--;
        Cdd_IpcSendMsg(CddIpcConf_IpcComChanId_Cdd_IpcMpu10,
                            &Cdd_IpcAppMpu10Buffer[0U], mpu10Bufsize);
        }
#endif /* CDD_IPC_REMOTE_CORE_MPU1_0_USED */
    }

    AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux
                                        " Transmitted and Received %d times\n",
                                        CDD_IPC_APP_MSG_TX_RX_CNT);                                   
    AppUtils_Printf(MSG_NORMAL, cdd_ipc_app_rc_linux
                                        " Sample Application - Completes !!!\n");

    Cdd_IpcAppDemoStatus = E_OK;
    return (0);
}

/* ========================================================================== */
/*                        Application Local Functions                         */
/* ========================================================================== */
/** \brief prints of the version of this implementation */
static void Cdd_IpcApp_PrintVersion(void)
{
#if (STD_ON == CDD_IPC_VERSION_INFO_API)
    Std_VersionInfoType versioninfo;

    Cdd_IpcGetVersionInfo(&versioninfo);
    AppUtils_Printf(MSG_NORMAL," CDD IPC MCAL Version Info\n");
    AppUtils_Printf(MSG_NORMAL,"---------------------\n");
    AppUtils_Printf(MSG_NORMAL," Vendor ID           : %d\n",
                                               versioninfo.vendorID);
    AppUtils_Printf(MSG_NORMAL," Module ID           : %d\n",
                                                versioninfo.moduleID);
    AppUtils_Printf(MSG_NORMAL," SW Major Version    : %d\n",
                                                versioninfo.sw_major_version);
    AppUtils_Printf(MSG_NORMAL," SW Minor Version    : %d\n",
                                                versioninfo.sw_minor_version);
    AppUtils_Printf(MSG_NORMAL," SW Patch Version    : %d\n",
                                                versioninfo.sw_patch_version);
#endif

}

/*EoF*/
