/*
 *  Copyright (c) Texas Instruments Incorporated 2018
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file ipc_osal_qnx.c
 *
 *  \brief Implementation of ipc QNX osal
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "ipc_osal.h"
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <stdlib.h>
#include <stdarg.h>
#include <semaphore.h>

#include <ti/drv/ipc/ipc.h>
#include <ti/drv/ipc/src/ipc_priv.h>
#include <ti/drv/ipc/soc/ipc_soc.h>
#include <ti/drv/ipc/include/ipc_types.h>

#ifndef IPC_SUPPORT_SCICLIENT
#include <ti/drv/ipc/src/ipc_utils.h>
#define NVSS_INTRTR_SIZE    0x1000
uintptr_t g_navssIntRtrBaseVirtAddr = 0;
#endif

void *Mailbox_plugInterrupt(Ipc_MbConfig *cfg, Ipc_OsalIsrFxn func, uintptr_t arg)
{
    OsalRegisterIntrParams_t    intrPrms;
    OsalInterruptRetCode_e      osalRetVal;
    HwiP_Handle                 hwiHandle = NULL;
    uint32_t                    coreIntrNum = 0U;
#ifndef IPC_SUPPORT_SCICLIENT
    CSL_IntrRouterCfg           irRegs;
#endif

#ifdef DEBUG_PRINT
    SystemP_printf("Mailbox_plugInterrupt: Navss Rtr input %d, output %d\n",
        cfg->inputIntrNum, cfg->outputIntrNum);
#endif

#ifndef IPC_SUPPORT_SCICLIENT
    /* Configure Main NavSS512 interrupt router */
    if(g_navssIntRtrBaseVirtAddr == 0)
    {
        g_navssIntRtrBaseVirtAddr = IpcUtils_getMemoryAddress(IPC_MCU_NAVSS0_INTR0_CFG_BASE,
                NVSS_INTRTR_SIZE );
    }
    irRegs.pIntrRouterRegs = (CSL_intr_router_cfgRegs *)g_navssIntRtrBaseVirtAddr;
    irRegs.pIntdRegs       = (CSL_intr_router_intd_cfgRegs *) NULL;
    irRegs.numInputIntrs   = MAIN_NAVSS_MAILBOX_INPUTINTR_MAX;
    irRegs.numOutputIntrs  = MAIN_NAVSS_MAILBOX_OUTPUTINTR_MAX;
    CSL_intrRouterCfgMux(&irRegs, cfg->inputIntrNum, cfg->outputIntrNum);

#if defined (SOC_AM65XX)
#if defined(BUILD_MCU1_0) || defined(BUILD_MCU1_1)
    Ipc_main2mcu_intRouter(cfg);
#endif
#endif

    /* Configure C66x Interrupt Router now */
#if defined(BUILD_C66X)
    Ipc_configC66xIntrRouter(cfg->eventId );
#endif

#endif  /* IPC_SUPPORT_SCICLIENT */

    coreIntrNum = cfg->eventId;

    /*
     * CLEC needs to be configured for all modes - CSL and Sciclient
     **/
#if defined(BUILD_C7X)
    /* Pass the corePackEvent and the base (which was derived from the NAVSS IR o/p 
     * range returned from BoardCfg) to route the corressponding CLEC i/p Event to 
     * a C7x IRQ. The returned IRQ num is used to register Interrupt with OSAL. */
    coreIntrNum = Ipc_configClecRouter(cfg->eventId, cfg->eventIdBase);
#endif

#if 1 //def DEBUG_PRINT
    SystemP_printf("Mailbox_plugInterrupt: interrupt Number %d, arg 0x%X\n",
        cfg->eventId, (uint32_t)arg);
#endif

    /* Register interrupts */
    Osal_RegisterInterrupt_initParams(&intrPrms);
    intrPrms.corepacConfig.arg              = arg;
    intrPrms.corepacConfig.isrRoutine       = func;
    intrPrms.corepacConfig.priority         = cfg->priority;

#if defined(BUILD_C66X)
    intrPrms.corepacConfig.corepacEventNum  = coreIntrNum;
    intrPrms.corepacConfig.intVecNum        = OSAL_REGINT_INTVEC_EVENT_COMBINER;
#else
    intrPrms.corepacConfig.intVecNum        = coreIntrNum;
    intrPrms.corepacConfig.corepacEventNum  = 0;
#endif
    intrPrms.corepacConfig.intAutoEnable  = 1;

    osalRetVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
    if(OSAL_INT_SUCCESS != osalRetVal)
    {
        SystemP_printf("Mailbox_plugInterrupt : Failed to register ISR...\n");
    }

    return (hwiHandle);
}

static int32_t Ipc_qnxIsrCreate(Ipc_OsalHIsrHandle *handle,
                                    Ipc_OsalHIsrFxn fxn, void *arg)
{
    int32_t rtnVal = IPC_EBADARGS;

    /* No HISR, HISR would be invoked in ISR context itself */
    if ((NULL != handle) && ((NULL != fxn) && (NULL != arg)))
    {
        handle->arg0    = (uintptr_t) arg;
        handle->arg1    = (uintptr_t) NULL;
        handle->hIsrFxn = fxn;
        handle->hLosHisrHandle = NULL;
        rtnVal = IPC_SOK;
    }

    return (rtnVal);
}

static void Ipc_qnxIsrDelete(Ipc_OsalHIsrHandle *handle)
{
    if (NULL != handle)
    {
        handle->arg0    = 0;
        handle->arg1    = 0;
        handle->hIsrFxn = NULL;
        handle->hLosHisrHandle = NULL;
    }
}

static int32_t Ipc_qnxIsrPost(Ipc_OsalHIsrHandle *handle)
{
    int32_t rtnVal = IPC_EBADARGS;

    if (NULL != handle)
    {
        handle->hIsrFxn(handle->arg0, 0);
        rtnVal = IPC_SOK;
    }
    return (rtnVal);
}

static void* Ipc_qnxMutexCreate(void)
{
    pthread_mutex_t *mutexHandle = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));

    if (EOK == pthread_mutex_init((pthread_mutex_t *) mutexHandle, NULL))
    {
        return ((void *) mutexHandle);
    }
    else
    {
        return (NULL);
    }
}

static void Ipc_qnxMutexDestroy(Ipc_OsalHIsrGateHandle *handle)
{
    if(handle != NULL)
    {
        pthread_mutex_destroy((pthread_mutex_t*) handle);
    }
    return;
}



static int32_t Ipc_qnxMutexLock(void* handle)
{
    int32_t rtnVal = IPC_EFAIL;
    if(handle != NULL)
    {
        if (EOK == pthread_mutex_lock((pthread_mutex_t *) handle))
        {
            rtnVal = IPC_SOK;
        }
    }
    return rtnVal;
}


static void Ipc_qnxMutexUnlock(void* handle, int32_t key)
{
    if(handle != NULL)
    {
        pthread_mutex_unlock((pthread_mutex_t *) handle);
    }
    return;
}

/* We need only mutex in IPC driver. Use semaphore in binary mode */
static void *Ipc_qnxSemCreate(void)
{
    sem_t *handle = (sem_t *)calloc(1, sizeof(sem_t));

    if (EOK == sem_init(handle, 0, 0))
    {
        return ((void *) handle);
    }
    else
    {
        return (NULL);
    }

    return ((void*) handle);
}

static void Ipc_qnxSemDestroy(void *handle)
{
    if(handle != NULL)
    {
        sem_destroy((sem_t *)handle);
    }
}

static int32_t Ipc_qnxSemWait(void *handle, uint32_t timeout)
{
    int ret = 0;
    int32_t rtnVal = IPC_SOK;
    struct timespec ts;
    uint64_t timeout_ns = timeout*1000;

    if(handle != NULL)
    {
        if (timeout == IPC_RPMESSAGE_TIMEOUT_FOREVER)
        {
            ret = sem_wait((sem_t *)handle);
        }
        else
        {
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += (timeout_ns)/1000000000;
            ts.tv_nsec += timeout_ns%1000000000;

            ret = sem_timedwait((sem_t *)handle, &ts);
        }
        if (ret < 0) {
            if (errno == ETIMEDOUT)
            {
                    rtnVal = IPC_ETIMEOUT;
            }
            else
            {
                    rtnVal = IPC_EFAIL;
            }
        }
        else
        {
            rtnVal = IPC_SOK;
        }
    }
    else
    {
        rtnVal = IPC_EBADARGS;
    }

    return rtnVal;
}

static void Ipc_qnxSemPost(void *handle)
{
    if(handle != NULL)
    {
        sem_post((sem_t *)handle);
    }
}
static uintptr_t Ipc_qnxInterruptDisable(void)
{
    InterruptDisable();
    return (uintptr_t)NULL;
}

static void Ipc_qnxInterruptEnable(uintptr_t keyNotUsed)
{
    InterruptEnable();
}

void IpcOsalPrms_init (Ipc_OsalPrms *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->disableAllIntr = &Ipc_qnxInterruptDisable;
        initPrms->restoreAllIntr = &Ipc_qnxInterruptEnable;

        initPrms->createHIsr    = &Ipc_qnxIsrCreate;
        initPrms->deleteHIsr    = &Ipc_qnxIsrDelete;
        initPrms->postHIsr      = &Ipc_qnxIsrPost;

        /* RTOS GateSwi is replaced with QNX Mutex */
        initPrms->createHIsrGate = &Ipc_qnxMutexCreate;
        initPrms->deleteHIsrGate = &Ipc_qnxMutexDestroy;
        initPrms->lockHIsrGate   = &Ipc_qnxMutexLock;
        initPrms->unLockHIsrGate = &Ipc_qnxMutexUnlock;

        /* QNX Semaphore wrapper to match RTOS APIs */
        initPrms->createMutex   = &Ipc_qnxSemCreate;
        initPrms->deleteMutex   = &Ipc_qnxSemDestroy;
        initPrms->lockMutex     = &Ipc_qnxSemWait;
        initPrms->unlockMutex   = &Ipc_qnxSemPost;

        initPrms->registerIntr = &Mailbox_plugInterrupt;
    }

    return;
}
