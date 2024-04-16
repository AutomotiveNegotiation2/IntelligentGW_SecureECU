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
 *  \file     CddIpcAppStartup.c
 *
 *  \brief    This file implements the start up code specific to SoC / core that
 *              application is hosted on.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "cddIpc_linux_rproc_profile.h"

#include "app_utils.h"
#include <ti/csl/csl_intr_router.h> /* CSL for interrupt router */
#include "IntRtr_Cfg.h" /* Defines the map / cfg for
                         * interrupt router, for this example
                         */
#include "SchM_Cdd_Ipc.h" /* Exclusive area */

#include <ti/csl/soc.h>
/* Interrupts, Clear MCU Timer 0 */
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>

/* SCI Client */
#include <ti/drv/sciclient/sciclient.h>
/* PM Lib */
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/dmsc/pmlib_sysconfig.h>
#include <ti/drv/pm/include/dmsc/pmlib_clkrate.h>

/* Interrupt Registrations */
#include <ti/osal/osal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MSG_NORMAL      (APP_UTILS_PRINT_MSG_NORMAL)
/**< Message type */
#define MSG_STATUS      (APP_UTILS_PRINT_MSG_STATUS)
/**< Message type */
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Cdd_IpcApp_BuildIntList(void);
static void Cdd_IpcApp_PowerAndClkSrc(void);
static void Cdd_IpcApp_InterruptConfig(void);

#if defined(CDD_IPC_REMOTE_CORE_MPU1_0_USED)
extern void Cdd_IpcProfile_MsgFromMpu10Isr(uintptr_t notUsed);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** \brief Start up sequence : Program the interrupt muxes / priorities */
void Cdd_IpcProfile_Startup(void)
{
    /* CLK and power to the device */
    Cdd_IpcApp_PowerAndClkSrc();

    /* Equivalent to EcuM_AL_SetProgrammableInterrupts */

    Cdd_IpcApp_BuildIntList();
#ifndef UART_ENABLED
    Intc_Init();    /* Interrupt handler initialized, here as other functions
                     * can use API's to clear pending interrupts if any
                     */
    /* The board initialization, initializes interrupt. Not required here */
#endif

    Cdd_IpcApp_InterruptConfig();
    /* Initialize counters, that would be required for timed operations */
    AppUtils_ProfileInit(0);

    /* Initialize memory sections  */
    AppUtils_CddIpcSectionInit();

}

/** \brief Build interrupt list */
static void Cdd_IpcApp_BuildIntList(void)
{
    /* None at this point */
    return;
}

/** \brief None, SBL/GEL powers up the timers and clock sources */
static void Cdd_IpcApp_PowerAndClkSrc(void)
{
    return;
}

#if defined(CDD_IPC_REMOTE_CORE_MPU1_0_USED)
/** \brief Register interrupt handler for new message notification from
 *          core MPU 10
 */
static void Cdd_IpcApp_MbIntRegForMpu10(void)
{
    struct tisci_msg_rm_irq_set_req     rmIrqReq;
    struct tisci_msg_rm_irq_set_resp    rmIrqResp;
    OsalRegisterIntrParams_t    intrPrms;
    OsalInterruptRetCode_e      osalRetVal;
    Int32 retVal;
    HwiP_Handle hwiHandle;

    rmIrqReq.valid_params           = TISCI_MSG_VALUE_RM_DST_ID_VALID;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
    rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;

    rmIrqReq.src_id                 = TISCI_DEV_NAVSS0_MAILBOX_0;
    rmIrqReq.src_index              = 1U; /* 0 for User 0, 1 for user 1... */
    rmIrqReq.dst_id                 = TISCI_DEV_MCU_R5FSS0_CORE0;
    rmIrqReq.secondary_host         = TISCI_HOST_ID_MCU_0_R5_0;
    rmIrqReq.dst_host_irq           = INTRTR_CFG_MBX_CLST0_USR1_437_MPU_1_0_TO_MCU_1_0_376;

    retVal = Sciclient_rmIrqSet(
                 &rmIrqReq, &rmIrqResp, APP_SCICLIENT_TIMEOUT);
    if(CSL_PASS != retVal)
    {
        AppUtils_Printf(MSG_NORMAL,MSG_APP_NAME
        ": Error in SciClient Interrupt Params Configuration!!!\n");
    }

    /* Interrupt hookup */
    Osal_RegisterInterrupt_initParams(&intrPrms);
    intrPrms.corepacConfig.arg          = (uintptr_t)NULL;
    intrPrms.corepacConfig.isrRoutine   = &Cdd_IpcProfile_MsgFromMpu10Isr;
    intrPrms.corepacConfig.priority     = 1U;
    intrPrms.corepacConfig.corepacEventNum = 0U;
    intrPrms.corepacConfig.intVecNum    = INTRTR_CFG_MBX_CLST0_USR1_437_MPU_1_0_TO_MCU_1_0_376;

    osalRetVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
    if(OSAL_INT_SUCCESS != osalRetVal)
    {
        AppUtils_Printf(MSG_NORMAL,
                        MSG_APP_NAME ": Error Could not register ISR to receive"
                        " from MPU 1 0 !!!\n");
    }
    return;
}
#endif /* CDD_IPC_REMOTE_CORE_MPU1_0_USED */

/** \brief Interrupt from mailbox for all cores registrations */
static void Cdd_IpcApp_InterruptConfig(void)
{
#if defined(CDD_IPC_REMOTE_CORE_MPU1_0_USED)
    Cdd_IpcApp_MbIntRegForMpu10 ();
#endif

    return;
}

/*EoF*/
