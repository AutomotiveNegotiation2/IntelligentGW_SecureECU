/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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
 *  \file ipc_mailbox_lld.c
 *
 *  \brief Implementation of ipc Mailbox interaction
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/ipc/ipc.h>
#include <ti/drv/ipc/soc/ipc_soc.h>
#include <ti/drv/ipc/src/ipc_mailbox_lld.h>
#include <ti/drv/mailbox/mailbox.h>

#ifndef IPC_EXCLUDE_POLLED_RX
#include <ti/osal/TaskP.h>
#endif

#include <string.h>

#include "ipc_osal.h"
#include "ipc_priv.h"

/* ========================================================================== */
/*                             Local Types                                    */
/* ========================================================================== */
/* mboxData */
typedef struct Ipc_MailboxData_s
{
    Mbox_Handle          handle;
    uint32_t             mboxId;
    Mailbox_hwiCallback  func;
    uint32_t             arg;
    uint32_t             noMsgCnt;
} Ipc_MailboxData;

/* ========================================================================== */
/*                             Globals                                        */
/* ========================================================================== */
Ipc_MailboxData        g_ipc_mBoxData[IPC_MAX_PROCS];

/* ========================================================================== */
/*                           Function Prototypes                              */
/* ========================================================================== */
void Ipc_mailboxInternalCallback(Mbox_Handle handle, Mailbox_Instance remoteEndpoint);

/**
 *  When IPC is built for bare metal and interrupt mode is not desired,
 *  Don't use the task to poll the mailboxes, rely on apps to poll
 */

/* ========================================================================== */
/*                             Local Functions                                */
/* ========================================================================== */

#ifndef IPC_EXCLUDE_POLLED_RX
#define IPC_POLL_TIMER  10

uint32_t     g_pollTaskExit = FALSE;
TaskP_Handle g_pollTask     = NULL;

void Mailbox_Poll_Task(void* argNotUsed)
{
    uint32_t                n    = 0U;
    uint32_t                msg;

    while(FALSE == g_pollTaskExit)
    {
        for (n = 0; n < IPC_MAX_PROCS; n++)
	{
            if (g_ipc_mBoxData[n].handle != NULL)
            {
                if (Mailbox_GetMessageCount(g_ipc_mBoxData[n].handle) > 0)
		{
                    retVal = Mailbox_read(g_ipc_mBoxData[n].handle, &msg, sizeof(uint32_t));
		}

		(g_ipc_mBoxData[n].func)(&msg, g_ipc_mBoxData[n].arg);
	}
        /* Temporarily we use Task_yield() */
        TaskP_yield();
    }
}

void Mailbox_Poll_TaskExit()
{
    g_pollTaskExit = TRUE;
}

#if defined(BUILD_C7X) && !defined(MAILBOX_INTERRUPT_MODE)
static uint8_t g_pollTaskStack[IPC_TASK_STACKSIZE]
__attribute__ ((section(".bss:taskStackSection")))
__attribute__ ((aligned(8192)))
    ;
#endif

void StartmailboxPollingTask()
{
    TaskP_Params param;

    TaskP_Params_init(&param);
    param.priority = 2;
#if defined(BUILD_C7X) && !defined(MAILBOX_INTERRUPT_MODE)
    param.stack = g_pollTaskStack;
#endif
    param.stacksize = IPC_TASK_STACKSIZE;
    g_pollTask = TaskP_create(&Mailbox_Poll_Task, &param);
}

#endif /* IPC_EXCLUDE_POLLED_RX */

/* ========================================================================== */
/*                             Functions                                      */
/* ========================================================================== */

static void Mailbox_osalMutexUnlock(void *mutexHandle, bool isISRContext)
{
    Ipc_Object           *pObj  = NULL;
    Ipc_OsalPrms         *pOsal = NULL;

    pObj = getIpcObjInst(0U);
    pOsal = &pObj->initPrms.osalPrms;

    pOsal->unlockMutex(mutexHandle);
}

static void *Mailbox_osalRegisterIntr(Mbox_OsalIsrFxn isrFxn,
                                          uint32_t coreIntrNum,
                                          uint32_t intrPriority,
                                          void *arg,
                                          char *name)
{
    Ipc_MbConfig         mbConfig;
    Ipc_Object           *pObj  = NULL;
    Ipc_OsalPrms         *pOsal = NULL;

    pObj = getIpcObjInst(0U);
    pOsal = &pObj->initPrms.osalPrms;

    mbConfig.priority = intrPriority;
    mbConfig.eventId = coreIntrNum;
    mbConfig.inputIntrNum = 0; /* Only used without sciclient support */
    mbConfig.outputIntrNum = 0; /* Only used without sciclient support */
    return (pOsal->registerIntr(&mbConfig, isrFxn, (uintptr_t)arg));
}

static uint64_t Mailbox_osalVirtToPhyFxn(const void *virtAddr)
{
    Ipc_Object           *pObj  = NULL;

    pObj = getIpcObjInst(0U);

    return (uint32_t)(pObj->initPrms.virtToPhyFxn(virtAddr));
}

static void *Mailbox_osalPhyToVirtFxn(uint64_t phyAddr)
{
    Ipc_Object           *pObj  = NULL;

    pObj = getIpcObjInst(0U);

    return (pObj->initPrms.phyToVirtFxn((uint32_t)phyAddr));
}

static void Mailbox_osalUnregisterIntr(void *hwiHandle, uint32_t coreIntrNum)
{
    Ipc_Object           *pObj  = NULL;
    Ipc_OsalPrms         *pOsal = NULL;

    pObj = getIpcObjInst(0U);
    pOsal = &pObj->initPrms.osalPrms;

    pOsal->unRegisterIntr(hwiHandle);
}

int32_t Ipc_mailboxModuleStartup (void)
{
    int32_t  retVal = IPC_SOK;
    Mailbox_initParams initParam;
    Ipc_Object           *pObj  = NULL;
    Ipc_OsalPrms         *pOsal = NULL;

    pObj = getIpcObjInst(0U);
    pOsal = &pObj->initPrms.osalPrms;

    /* Setup the default Mailbox init Parameters */
    Mailbox_initParams_init(&initParam);
    initParam.localEndpoint = Ipc_getCoreId();

    /* Pass our osal functions to mailbox lld */
    initParam.osalPrms.disableAllIntr = pOsal->disableAllIntr;
    initParam.osalPrms.restoreAllIntr = pOsal->restoreAllIntr;
    initParam.osalPrms.enableIntr = NULL;
    initParam.osalPrms.disableIntr = NULL;
    initParam.osalPrms.createMutex = pOsal->createMutex;
    initParam.osalPrms.deleteMutex = pOsal->deleteMutex;
    initParam.osalPrms.lockMutex = pOsal->lockMutex;
    if (pOsal->unlockMutex != NULL)
    {
        initParam.osalPrms.unlockMutex = &Mailbox_osalMutexUnlock;
    }
    else
    {
        initParam.osalPrms.unlockMutex = NULL;
    }
    if (pOsal->registerIntr != NULL)
    {
        initParam.osalPrms.registerIntr = &Mailbox_osalRegisterIntr;
    }
    else
    {
        initParam.osalPrms.registerIntr = NULL;
    }
    if (pOsal->unRegisterIntr != NULL)
    {
        initParam.osalPrms.unRegisterIntr = &Mailbox_osalUnregisterIntr;
    }
    else
    {
        initParam.osalPrms.unRegisterIntr = NULL;
    }

    if (pObj->initPrms.virtToPhyFxn != NULL)
    {
        initParam.virtToPhyFxn = &Mailbox_osalVirtToPhyFxn;
    }
    else
    {
        initParam.virtToPhyFxn = NULL;
    }
    if (pObj->initPrms.phyToVirtFxn != NULL)
    {
        initParam.phyToVirtFxn = &Mailbox_osalPhyToVirtFxn;
    }
    else
    {
        initParam.phyToVirtFxn = NULL;
    }

    /* Initialize the Mailbox */
    Mailbox_init(&initParam);

    memset(g_ipc_mBoxData, 0, sizeof(g_ipc_mBoxData));

    return retVal;
}

/**
 *  \brief Clear interrupt and return the message.
 */
uint32_t Ipc_mailboxClear(uint32_t baseAddr, uint32_t queueId)
{
    uint32_t retVal = 0;
    uint32_t msg[4];

    retVal = MailboxGetMessage(baseAddr, queueId, msg);

    return retVal;
}

/**
 *  \brief Send interrupt to the remote processor
 */
int32_t Ipc_mailboxSend(uint32_t selfId, uint32_t remoteProcId, uint32_t val,
                        uint32_t timeoutCnt)
{
    int32_t   status = 0;
    uint32_t  cnt = timeoutCnt;
    uint32_t    retVal;

    do
    {
        retVal = Mailbox_write(g_ipc_mBoxData[remoteProcId].handle,
                               (uint8_t *)&val, sizeof(uint32_t));
        cnt--;
    } while( (cnt != 0U) && (retVal == MESSAGE_INVALID));

    if(MESSAGE_INVALID == retVal)
    {
#ifdef DEBUG_PRINT
        SystemP_printf("Ipc_mailboxSend : BaseAddr 0x%x queue %d value %d failed\n",
                       baseAddr,  queueId, val);
#endif
        status = IPC_EFAIL;
    }

#if DEBUG_PRINT
    SystemP_printf("Ipc_mailboxSend : BaseAddr 0x%x queue %d value %d\n",
                   baseAddr,  queueId, val);
#endif

    return status;
}

int32_t Ipc_mailboxRegister(uint16_t selfId, uint16_t remoteProcId,
           Mailbox_hwiCallback func, uint32_t arg, uint32_t timeoutCnt)
{
    int32_t               retVal = IPC_SOK;
    Mailbox_openParams openParam;
    Mbox_Handle        handle;
    int32_t            errCode;

    Mailbox_openParams_init(&openParam);

    openParam.cfg.writeMode = MAILBOX_MODE_POLLING;
    openParam.cfg.writeTimeout = timeoutCnt;
    openParam.cfg.readMode = MAILBOX_MODE_CALLBACK;
    openParam.cfg.readTimeout = timeoutCnt;
    openParam.cfg.readCallback = Ipc_mailboxInternalCallback;
    /*
     * Set enableInterrupts to false, we want to enable later after
     * control endpoint callback is configured
     */
    openParam.cfg.enableInterrupts = false;

    openParam.remoteEndpoint = Ipc_rprocIdToMboxId(remoteProcId);

    handle = Mailbox_open(&openParam, &errCode);

    if (handle != NULL)
    {
        /* Save the data */
        g_ipc_mBoxData[remoteProcId].handle = handle;
        g_ipc_mBoxData[remoteProcId].mboxId = Ipc_rprocIdToMboxId(remoteProcId);
        g_ipc_mBoxData[remoteProcId].func = func;
        g_ipc_mBoxData[remoteProcId].arg = arg;
    }
    else
    {
        retVal = IPC_EFAIL;
    }

#ifdef DEBUG_PRINT
        SystemP_printf("Ipc_MB(%d): Self %d Remote %d (c%d,u%d,q%d) arg %d,total %d\n",
                mbox->fifoCnt, selfId, remoteProcId, clusterId, userId, queueId, arg,
                g_ipc_mBoxCnt);
#endif

    return retVal;
}

/** \brief Low Level Mailbox ISR for a given remote processor */
void Ipc_mailboxIsr(uint32_t remoteProcId)
{
    if (IPC_MAX_PROCS > remoteProcId)
    {
        if (g_ipc_mBoxData[remoteProcId].handle != NULL)
	{
            Ipc_mailboxInternalCallback(g_ipc_mBoxData[remoteProcId].handle,
                                        g_ipc_mBoxData[remoteProcId].mboxId);
        }
    }

    return;
}

/*!
 *  ======== Ipc_mailboxInternalCallback ========
 */
void Ipc_mailboxInternalCallback(Mbox_Handle handle, Mailbox_Instance remoteEndpoint)
{
    int32_t               ret;
    uint32_t              msg;
    uint32_t              remoteProcId;

    remoteProcId = Ipc_mboxIdToRprocId(remoteEndpoint);

    ret = Mailbox_read(handle, (uint8_t *)&msg, sizeof(uint32_t));

    if (ret == MAILBOX_SOK)
    {
        if ((remoteProcId < IPC_MAX_PROCS) && (g_ipc_mBoxData[remoteProcId].func))
        {
            (g_ipc_mBoxData[remoteProcId].func)(&msg, g_ipc_mBoxData[remoteProcId].arg);
        }
        else
        {
            SystemP_printf("Ipc_mailboxInternalCallback: callback for procId %d with NULL func!\n", remoteProcId);
        }
    }
    else if (remoteProcId < IPC_MAX_PROCS)
    {
        g_ipc_mBoxData[remoteProcId].noMsgCnt++;
    }
}

void Ipc_mailboxEnableNewMsgInt(uint16_t selfId, uint16_t remoteProcId)
{
    if (g_ipc_mBoxData[remoteProcId].handle != NULL)
    {
        Mailbox_enableInterrupts(g_ipc_mBoxData[remoteProcId].handle);
    }

    return;
}

void Ipc_mailboxDisableNewMsgInt(uint16_t selfId, uint16_t remoteProcId)
{
    if (g_ipc_mBoxData[remoteProcId].handle != NULL)
    {
        Mailbox_disableInterrupts(g_ipc_mBoxData[remoteProcId].handle);
    }

    return;
}
