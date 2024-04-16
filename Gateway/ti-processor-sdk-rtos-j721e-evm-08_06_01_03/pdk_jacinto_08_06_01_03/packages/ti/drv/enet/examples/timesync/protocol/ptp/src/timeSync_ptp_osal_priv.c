/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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

/*!
 * \file timeSync_ptp_osal_priv.c
 *
 * \brief This file contains the implementation of OSAL functions
 *        of PTP stack
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <assert.h>

/* OSAL Header files */
#include <ti/osal/osal.h>
#include <ti/osal/soc/osal_soc.h>

#include <ti/drv/enet/examples/timesync/timeSync.h>

#include <ti/drv/enet/examples/timesync/protocol/ptp/include/timeSync_ptp.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_ptp_priv.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_ptp_init_priv.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_ptp_osal_priv.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_tools.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Global array to pass port number as an argument to task functions.
 *  Workaround to fix "uint8_t cannot be assigned to an entity of type "void *"
 */
static uint8_t gPortNum[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

/**< Task Stack memory */
static uint8_t gTimeSyncPtp_processTxNotifyTaskStackBuf[TIMESYNC_PTP_TX_NOTIFY_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_TX_NOTIFY_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_processRxNotifyTaskStackBuf[TIMESYNC_PTP_RX_NOTIFY_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_RX_NOTIFY_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_pdelayReqSendTaskStackBuf[TIMESYNC_PTP_DELAY_REQ_SEND_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_DELAY_REQ_SEND_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_delayReqSendTaskStackBuf[TIMESYNC_PTP_DELAY_REQ_SEND_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_DELAY_REQ_SEND_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_txTsTaskStackBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED][TIMESYNC_PTP_TX_TS_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_TX_TS_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_syncTxTaskStackBuf[TIMESYNC_PTP_SYNC_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_SYNC_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_announceTxTaskStackBuf[TIMESYNC_PTP_ANNOUNCE_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_ANNOUNCE_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_nRTTaskStackBuf[TIMESYNC_PTP_NRT_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_NRT_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_backgroundTaskStackBuf[TIMESYNC_PTP_BACKGROUND_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_BACKGROUND_TASK_STACK_ALIGN)));
static uint8_t gTimeSyncPtp_ppsTaskStackBuf[TIMESYNC_PTP_PPS_TASK_STACKSIZE] __attribute__ ((aligned(TIMESYNC_PTP_PPS_TASK_STACK_ALIGN)));

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * @brief This is used for
 * 1. Extracting Tx Timestamp information when a callback interrupt is triggered from firmware
 * 2. Checks for the type of packet and calls relevant Tx API
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is port number
 * @return none
 */
static void TimeSyncPtp_txTsTask(void* a0,
                                 void* a1);

/**
 * @brief This is used for
 * 1. Sending Peer delay request messages used to calculate peer delay
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is NULL
 * @return none
 */
static void TimeSyncPtp_pdelayReqSendTask(void* a0,
                                          void* a1);

/**
 * @brief This is used for
 *  Sending delay request messages to master to calculate line delay
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is NULL
 * @return none
 */
static void TimeSyncPtp_delayReqSendTask(void* a0,
                                         void* a1);

/**
 * @brief This is used for
 * 1. Checking for missed Sync frames
 * 2. Running part of offset stabilization algorithm
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is NULL
 * @return none
 */
static void TimeSyncPtp_backgroundTask(void* a0,
                                       void* a1);

/**
 * @brief This is used for synchronizing to time of day
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is NULL
 * @return none
 */
static void TimeSyncPtp_ppsTask(void* arg0,
                                void* arg1);

/**
 * @brief NRT stands for non-real time
 * This task is responsible for processing Peer delay messages and
 * calculating peer delay
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is NULL
 * @return none
 */
static void TimeSyncPtp_nRTTask(void* a0,
                                void* a1);

/**
 * @brief This is the main master task which sends a pre-formatted Sync frame at
 *  designated Sync interval. This is triggered upon DM Timer expiry and
 *  is actually a timer interrupt
 * @param  arg0 generic argument. PTP Handle is passed through this
 * @param  arg1 is NULL
 * @return none
 */
static void TimeSyncPtp_syncTxTask(void* arg0,
                                   void* arg1);

/**
 * @brief This is task which sends pre-formatted Announce frames when
 * device is configured as a master or boundary clock.
 * @param  a0 generic argument. PTP Handle is passed through this
 * @param  a1 is NULL
 * @return none
 */
static void TimeSyncPtp_announceTxTask(void* a0,
                                       void* a1);

/**
 * @brief This is the ISR for DMTimer which is configured to sync send interval. It posts
 * a semaphore which in turn triggers the sending of sync frames
 * @param  arg generic argument PTP Handle is passed through this
 * @return none
 */
static void TimeSyncPtp_syncTxIsr(void* arg);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int8_t TimeSyncPtp_createPtpTasks(TimeSyncPtp_Handle hTimeSyncPtp)
{
    ClockP_Params clkParams;
    TaskP_Params taskParams;
    SemaphoreP_Params semaphoreParams;
    EventP_Params eventParams;
    uint8_t portNum = 0;
    int8_t status = TIMESYNC_OK;
    uint32_t period = 0U;

    /* Clock setup */
    ClockP_Params_init(&clkParams);
    period = hTimeSyncPtp->ptpConfig.syncSendInterval / 1000U;
    clkParams.startMode = ClockP_StartMode_USER;
    clkParams.period    = period;
    clkParams.runMode   = ClockP_RunMode_CONTINUOUS;
    clkParams.arg       = (void*)hTimeSyncPtp;

    /* Creating clock and setting clock callback function*/
    hTimeSyncPtp->syncTxTimer = ClockP_create((void *)TimeSyncPtp_syncTxIsr,
                                             &clkParams);
    if (hTimeSyncPtp->syncTxTimer == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_CLOCK;
    }

    /*Create semaphore for sending Sync frames*/
    SemaphoreP_Params_init(&semaphoreParams);
    semaphoreParams.mode = SemaphoreP_Mode_BINARY;
    hTimeSyncPtp->syncTxSemHandle = SemaphoreP_create(0, &semaphoreParams);

    if (hTimeSyncPtp->syncTxSemHandle == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_SEMAPHORE;
    }

    if (hTimeSyncPtp->ptpConfig.processToDSync2PPS)
    {
        /*Create semaphore which is posted by PPS ISR, which in turn triggers
         * the task used to synchronize the clock*/
        SemaphoreP_Params_init(&semaphoreParams);
        semaphoreParams.mode = SemaphoreP_Mode_BINARY;
        hTimeSyncPtp->ppsSemHandle = SemaphoreP_create(0, &semaphoreParams);

        if (hTimeSyncPtp->ppsSemHandle == NULL)
        {
            return TIMESYNC_UNABLE_TO_CREATE_SEMAPHORE;
        }
    }

    if (hTimeSyncPtp->ptpConfig.type == TIMESYNC_PTP_DELAY_E2E)
    {
        /*Create semaphore for sending delay request frames*/
        SemaphoreP_Params_init(&semaphoreParams);
        semaphoreParams.mode = SemaphoreP_Mode_BINARY;
        hTimeSyncPtp->delayReqTxSemHandle = SemaphoreP_create(0, &semaphoreParams);

        if (hTimeSyncPtp->delayReqTxSemHandle == NULL)
        {
            return TIMESYNC_UNABLE_TO_CREATE_SEMAPHORE;
        }
    }

    /*Create semaphore for transmitted packet notification*/
    SemaphoreP_Params_init(&semaphoreParams);
    semaphoreParams.mode = SemaphoreP_Mode_BINARY;
    hTimeSyncPtp->pktTxSemHandle = SemaphoreP_create(0, &semaphoreParams);

    if (hTimeSyncPtp->pktTxSemHandle == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_SEMAPHORE;
    }

    /*Create semaphore for received packet notification*/
    SemaphoreP_Params_init(&semaphoreParams);
    semaphoreParams.mode = SemaphoreP_Mode_BINARY;
    hTimeSyncPtp->pktRxSemHandle = SemaphoreP_create(0, &semaphoreParams);

    if (hTimeSyncPtp->pktRxSemHandle == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_SEMAPHORE;
    }

    /*Assign event ID's*/
    hTimeSyncPtp->eventIdSync = EventP_ID_02;
    hTimeSyncPtp->eventIdPdelayReq  = EventP_ID_03;
    hTimeSyncPtp->eventIdPdelayResp = EventP_ID_04;
    hTimeSyncPtp->eventIdPdelayRespFlwUp = EventP_ID_05;
    hTimeSyncPtp->eventIdDelayReq = EventP_ID_06;
    hTimeSyncPtp->eventIdFlwUpGenerated = EventP_ID_07;

    for (portNum = 0; portNum < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; portNum++)
    {
        if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, portNum))
        {
            hTimeSyncPtp->ptpPdelayResEvtHandle[portNum] = EventP_create(&eventParams);
            if (hTimeSyncPtp->ptpPdelayResEvtHandle[portNum] == NULL)
            {
                return TIMESYNC_UNABLE_TO_CREATE_EVENT;
            }
        }
    }

    for (portNum = 0; portNum < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; portNum++)
    {
        if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, portNum))
        {
            hTimeSyncPtp->txTSAvailableEvtHandle[portNum] = EventP_create(&eventParams);
            if (hTimeSyncPtp->txTSAvailableEvtHandle[portNum] == NULL)
            {
                return TIMESYNC_UNABLE_TO_CREATE_EVENT;
            }
        }
    }

    for (portNum = 0; portNum < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; portNum++)
    {
        if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, portNum))
        {
            hTimeSyncPtp->ptpPdelayReqEvtHandle[portNum] = EventP_create(&eventParams);
            if (hTimeSyncPtp->ptpPdelayReqEvtHandle[portNum] == NULL)
            {
                return TIMESYNC_UNABLE_TO_CREATE_EVENT;
            }
        }
    }

    for (portNum = 0; portNum < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; portNum++)
    {
        if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, portNum))
        {
            hTimeSyncPtp->ptpSendFollowUpEvtHandle[portNum] = EventP_create(&eventParams);
            if (hTimeSyncPtp->ptpSendFollowUpEvtHandle[portNum] == NULL)
            {
                return TIMESYNC_UNABLE_TO_CREATE_EVENT;
            }
        }
    }

    /*-----------Create Tasks------------*/

    /* Packet Tx process Task*/
    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_TX_NOTIFY_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    taskParams.stack = &gTimeSyncPtp_processTxNotifyTaskStackBuf[0];
    taskParams.stacksize = TIMESYNC_PTP_TX_NOTIFY_TASK_STACKSIZE;
    hTimeSyncPtp->pktTxNotifyTask = TaskP_create(&TimeSyncPtp_processTxNotifyTask,
                                                 &taskParams);

    if (hTimeSyncPtp->pktTxNotifyTask == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    /* Packet Rx process Task*/
    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_RX_NOTIFY_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    taskParams.stack = &gTimeSyncPtp_processRxNotifyTaskStackBuf[0];
    taskParams.stacksize = TIMESYNC_PTP_RX_NOTIFY_TASK_STACKSIZE;
    hTimeSyncPtp->pktRxNotifyTask = TaskP_create(&TimeSyncPtp_processRxNotifyTask,
                                                 &taskParams);

    if (hTimeSyncPtp->pktRxNotifyTask == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    if (hTimeSyncPtp->ptpConfig.type == TIMESYNC_PTP_DELAY_P2P)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority = TIMESYNC_PTP_DELAY_REQ_SEND_TASK_PRIORITY;
        taskParams.arg0 = (void *)hTimeSyncPtp;
        taskParams.stack = &gTimeSyncPtp_pdelayReqSendTaskStackBuf[0];
        taskParams.stacksize = TIMESYNC_PTP_DELAY_REQ_SEND_TASK_STACKSIZE;
        hTimeSyncPtp->pDelayReqSendTask = TaskP_create(&TimeSyncPtp_pdelayReqSendTask,
                                                       &taskParams);

        if (hTimeSyncPtp->pDelayReqSendTask == NULL)
        {
            return TIMESYNC_UNABLE_TO_CREATE_TASK;
        }
    }

    if (hTimeSyncPtp->ptpConfig.type == TIMESYNC_PTP_DELAY_E2E)
    {
        TaskP_Params_init(&taskParams);
        taskParams.priority = TIMESYNC_PTP_DELAY_REQ_SEND_TASK_PRIORITY;
        taskParams.arg0 = (void *)hTimeSyncPtp;
        taskParams.stack = &gTimeSyncPtp_delayReqSendTaskStackBuf[0];
        taskParams.stacksize = TIMESYNC_PTP_DELAY_REQ_SEND_TASK_STACKSIZE;
        hTimeSyncPtp->delayReqSendTask = TaskP_create(&TimeSyncPtp_delayReqSendTask,
                                                      &taskParams);

        if (hTimeSyncPtp->delayReqSendTask == NULL)
        {
            return TIMESYNC_UNABLE_TO_CREATE_TASK;
        }
    }

    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_TX_TS_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    for (portNum = 0; portNum < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; portNum++)
    {
        if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, portNum))
        {
            /* Assign port number value to global variable as a workaround to
             * avoid compilation error */
            gPortNum[portNum] = portNum;
            taskParams.arg1 = (void *)&gPortNum[portNum];
            taskParams.stack = &gTimeSyncPtp_txTsTaskStackBuf[portNum][0];
            taskParams.stacksize = TIMESYNC_PTP_TX_TS_TASK_STACKSIZE;
            hTimeSyncPtp->txTsTask[portNum] = TaskP_create(&TimeSyncPtp_txTsTask,
                                                           &taskParams);
            if (hTimeSyncPtp->txTsTask[portNum] == NULL)
            {
                status += TIMESYNC_UNABLE_TO_CREATE_TASK;
            }
        }
    }

    if (status != TIMESYNC_OK)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    /* Sync Tx Task*/
    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_SYNC_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    taskParams.stack = &gTimeSyncPtp_syncTxTaskStackBuf[0];
    taskParams.stacksize = TIMESYNC_PTP_SYNC_TASK_STACKSIZE;
    hTimeSyncPtp->syncTxTask = TaskP_create(&TimeSyncPtp_syncTxTask,
                                            &taskParams);

    if (hTimeSyncPtp->syncTxTask == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    /* Announce Tx Task*/
    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_ANNOUNCE_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    taskParams.stack = &gTimeSyncPtp_announceTxTaskStackBuf[0];
    taskParams.stacksize = TIMESYNC_PTP_ANNOUNCE_TASK_STACKSIZE;
    hTimeSyncPtp->announceTxTask = TaskP_create(&TimeSyncPtp_announceTxTask,
                                                &taskParams);

    if (hTimeSyncPtp->announceTxTask == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    /* NRT Task to process peer delay frames*/
    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_NRT_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    taskParams.stack = &gTimeSyncPtp_nRTTaskStackBuf[0];
    taskParams.stacksize = TIMESYNC_PTP_NRT_TASK_STACKSIZE;
    hTimeSyncPtp->nRTTask = TaskP_create(&TimeSyncPtp_nRTTask,
                                         &taskParams);

    if (hTimeSyncPtp->nRTTask == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    /* Background Task to do computation*/
    TaskP_Params_init(&taskParams);
    taskParams.priority = TIMESYNC_PTP_BACKGROUND_TASK_PRIORITY;
    taskParams.arg0 = (void *)hTimeSyncPtp;
    taskParams.stack = &gTimeSyncPtp_backgroundTaskStackBuf[0];
    taskParams.stacksize = TIMESYNC_PTP_BACKGROUND_TASK_STACKSIZE;
    hTimeSyncPtp->backgroundTask = TaskP_create(&TimeSyncPtp_backgroundTask,
                                                &taskParams);

    if (hTimeSyncPtp->backgroundTask == NULL)
    {
        return TIMESYNC_UNABLE_TO_CREATE_TASK;
    }

    if (hTimeSyncPtp->ptpConfig.processToDSync2PPS)
    {
        /* Task where local clock is synchronized to latch0 timestamp*/
        TaskP_Params_init(&taskParams);
        taskParams.priority = TIMESYNC_PTP_PPS_TASK_PRIORITY;
        taskParams.arg0 = (void *)hTimeSyncPtp;
        taskParams.stack = &gTimeSyncPtp_ppsTaskStackBuf[0];
        taskParams.stacksize = TIMESYNC_PTP_PPS_TASK_STACKSIZE;
        hTimeSyncPtp->ppsTask = TaskP_create(&TimeSyncPtp_ppsTask,
                                             &taskParams);

        if (hTimeSyncPtp->ppsTask == NULL)
        {
            return TIMESYNC_UNABLE_TO_CREATE_TASK;
        }
    }

    return TIMESYNC_OK;
}

/* ========================================================================== */
/*                           Task Definitions                                 */
/* ========================================================================== */

static void TimeSyncPtp_pdelayReqSendTask(void* a0,
                                          void* a1)
{
    TimeSyncPtp_Handle hTimeSyncPtp;
    uint8_t linkStatus = 0U;
    uint8_t frameCount = 0U;
    uint8_t offset  = 0U;
    int32_t retVal  = 0U;
    uint8_t portNum = 0U;

    hTimeSyncPtp = (TimeSyncPtp_Handle)a0;
    offset = hTimeSyncPtp->ptpConfig.frameOffset;

    while (1)
    {
        if (TIMESYNC_PTP_DELAY_P2P == hTimeSyncPtp->ptpConfig.type)
        {
            if (hTimeSyncPtp->enabled == TRUE)
            {
                /*Construct a Delay Request packet and send it on all ports */
                /*Send delay request frames in a burst*/
                for (frameCount = 0; frameCount < hTimeSyncPtp->ptpConfig.pdelayBurstNumPkts; frameCount++)
                {
                    for (portNum = 0; portNum < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; portNum++)
                    {
                        if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, portNum))
                        {
                            linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, portNum);
                            if (linkStatus)
                            {
                                /*write sequence id into memory*/
                                TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.pdelayReqTxBuf[portNum] + TIMESYNC_PTP_SEQ_ID_OFFSET - offset,
                                                     hTimeSyncPtp->tsRunTimeVar.pDelReqSequenceID[portNum]);

                                /**Add Source Port ID*/
                                TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.pdelayReqTxBuf[portNum] + TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset,
                                                     (portNum + 1U));

                                retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                               hTimeSyncPtp->timeSyncBuff.pdelayReqTxBuf[portNum],
                                                               TIMESYNC_PTP_PDELAY_BUF_SIZE,
                                                               portNum);
                                if (retVal == TIMESYNC_OK)
                                {
                                    hTimeSyncPtp->tsRunTimeVar.pDelReqSequenceID[portNum]++;
                                }
                            }

                            /*Add small delay between two requests on two ports
                             * to avoid collision scenarios
                             */
                            TaskP_sleep(10);
                        }
                    }

                    TaskP_sleep(hTimeSyncPtp->ptpConfig.pdelayBurstInterval);
                }
            }

            TaskP_sleep(hTimeSyncPtp->ptpConfig.pDelReqPktInterval);
        }
    }
}

static void TimeSyncPtp_delayReqSendTask(void* a0,
                                         void* a1)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)a0;
    int32_t retVal;
    uint8_t offset = hTimeSyncPtp->ptpConfig.frameOffset;

    while (1)
    {
        /*Wait for sync frame to post the semaphore
         * and then send a delay request frame on the port on which
         * master is connected
         */
        SemaphoreP_pend(hTimeSyncPtp->delayReqTxSemHandle, SemaphoreP_WAIT_FOREVER);
        /*Use registered callback to send packet on Port connected to master*/

        /*Add port number*/
        TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.delayReqTxBuf +
                             TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset,
                             (hTimeSyncPtp->tsRunTimeVar.syncPortNum + 1U));

        /*Add sequence ID*/
        TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.delayReqTxBuf + TIMESYNC_PTP_SEQ_ID_OFFSET - offset,
                             hTimeSyncPtp->tsRunTimeVar.delReqSequenceID);

        retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                       hTimeSyncPtp->timeSyncBuff.delayReqTxBuf,
                                       TIMESYNC_PTP_DELAY_REQ_BUF_SIZE,
                                       hTimeSyncPtp->tsRunTimeVar.syncPortNum);
        if (retVal == 0U)
        {
            hTimeSyncPtp->tsRunTimeVar.delReqSequenceID++;
        }
    }
}

static void TimeSyncPtp_txTsTask(void* a0,
                                 void* a1)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)a0;
    uint8_t portNum = *((uint8_t *)a1);
    uint32_t events = 0;

    while (1)
    {
        /*Pend on event to process Tx timestamp interrupt*/
        events = EventP_wait(hTimeSyncPtp->txTSAvailableEvtHandle[portNum],
                             (hTimeSyncPtp->eventIdPdelayReq + hTimeSyncPtp->eventIdSync +
                              hTimeSyncPtp->eventIdPdelayResp),
                             EventP_WaitMode_ANY,
                             EventP_WAIT_FOREVER);

        if (events & hTimeSyncPtp->eventIdSync)
        {
            TimeSyncPtp_getTxTs(hTimeSyncPtp, portNum, TIMESYNC_SYNC_FRAME);
        }

        if (events & hTimeSyncPtp->eventIdPdelayReq)
        {
            TimeSyncPtp_getTxTs(hTimeSyncPtp, portNum, TIMESYNC_DELAY_REQ_FRAME);
        }

        if (events & hTimeSyncPtp->eventIdPdelayResp)
        {
            TimeSyncPtp_getTxTs(hTimeSyncPtp, portNum, TIMESYNC_DELAY_RESP_FRAME);
        }
    }
}

static void TimeSyncPtp_nRTTask(void* a0,
                                void* a1)
{
    uint32_t events = 0U;
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)a0;
    uint8_t port = 0U;
    int8_t linkStatus = 0;

    while (1)
    {
        for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
        {
            if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port))
            {
                linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                if (linkStatus)
                {
                    /*Wait 1ms then move on to other tasks*/
                    events = EventP_wait(hTimeSyncPtp->ptpPdelayResEvtHandle[port],
                                         (hTimeSyncPtp->eventIdPdelayResp + hTimeSyncPtp->eventIdPdelayRespFlwUp),
                                         EventP_WaitMode_ALL,
                                         1);

                    /*Calculate Peer Delay on port*/
                    if (events)
                    {
                        TimeSyncPtp_processPdelayRespFrame(hTimeSyncPtp,
                                                           hTimeSyncPtp->timeSyncBuff.pdelayResRxBuf[port],
                                                           FALSE,
                                                           port);

                        if (hTimeSyncPtp->pDelayParams[port].ifTwoStep)
                        {
                            TimeSyncPtp_processPdelayRespFrame(hTimeSyncPtp,
                                                               hTimeSyncPtp->timeSyncBuff.pdelayResFlwUpRxBuf[port],
                                                               TRUE,
                                                               port);
                        }
                    }

                    /*Wait 1ms then move on to other tasks*/
                    /*Send Pdelay response on port*/
                    events = EventP_wait(hTimeSyncPtp->ptpPdelayReqEvtHandle[port],
                                         (hTimeSyncPtp->eventIdPdelayReq),
                                         EventP_WaitMode_ALL,
                                         1);

                    if (events)
                    {
                        TimeSyncPtp_processPdelayReqFrame(hTimeSyncPtp,
                                                          hTimeSyncPtp->timeSyncBuff.pdelayReqRxBuf[port],
                                                          port);
                    }

                    /*Wait 1ms then move on to other tasks*/
                    events = EventP_wait(hTimeSyncPtp->ptpSendFollowUpEvtHandle[port],
                                         (hTimeSyncPtp->eventIdSync + hTimeSyncPtp->eventIdFlwUpGenerated),
                                         EventP_WaitMode_ALL,
                                         1);

                    if (events)
                    {
                        TimeSyncPtp_forced2StepBDCalc(hTimeSyncPtp, port);
                    }
                }
                else
                {
                    /* linkStatus being false is not an issue, wait for sometime and retry.
                     * Note: Do not remove this sleep, this is required to prevent the task from
                     * becoming while(1); when only one port is used and the link is down for that port.*/
                    TaskP_sleep(1);
                }
            }
        }
    }
}

static void TimeSyncPtp_backgroundTask(void* a0,
                                       void* a1)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)a0;
    uint8_t count = 0;
    int32_t avgCorrection = 0;

    while (1)
    {
        /*Increment the tick counter*/
        hTimeSyncPtp->tsRunTimeVar.tickCounter++;

        /*check for sync timeout*/
        if (hTimeSyncPtp->tsRunTimeVar.syncLastSeenCounter++ >
            hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval)
        {
            hTimeSyncPtp->numSyncMissed++;
            /*If we continuously miss sync frames then reset*/
            if ((hTimeSyncPtp->numSyncMissed % TIMESYNC_PTP_NUM_SYNC_MISSED_THRESHOLD) == 0)
            {
                if (hTimeSyncPtp->ptpConfig.isMaster)
                {
                    /* No action for master mode as there is no Sync frame to
                       receive, Master sends the Sync Frame */
                }
                else
                {
                    TimeSyncPtp_reset(hTimeSyncPtp);
                }
            }

            /*reset so that we don't keep getting this error*/
            hTimeSyncPtp->tsRunTimeVar.syncLastSeenCounter = 0;
        }

        /*Check if we have to process the data*/
        if (hTimeSyncPtp->offsetAlgo.binFull == 1)
        {
            /*get average of all offsets*/
            avgCorrection = 0;

            for (count = 0; count < 5; count++)
            {
                avgCorrection += hTimeSyncPtp->offsetAlgo.correction[count];
            }

            avgCorrection /= 5;
            /*add the new correction value to initial offset or the PPM value*/
            hTimeSyncPtp->tsRunTimeVar.initialOffset += avgCorrection;
            /*Reset the variables so another round of measurements can begin*/
            hTimeSyncPtp->offsetAlgo.binFull = 0;
            hTimeSyncPtp->offsetAlgo.numEntriesIndex = 0;
        }

        TaskP_sleep(TIMESYNC_PTP_BG_TASK_TICK_PERIOD);
    }
}

static void TimeSyncPtp_syncTxTask(void* arg0,
                                   void* arg1)
{
    TimeSyncPtp_Handle hTimeSyncPtp = NULL;
    uint8_t offset = 0;
    uint64_t sec = 0;
    uint32_t n_sec = 0;
    int32_t retVal;
    int32_t isSingleStepSupported = FALSE;
    uint8_t port = 0U;
    int8_t linkStatus = 0;
    volatile bool runFlag = false;

    /* void* is typedef-ed from uint */
    if (arg0 != 0x0U)
    {
        hTimeSyncPtp = (TimeSyncPtp_Handle)arg0;
        offset = hTimeSyncPtp->ptpConfig.frameOffset;
        isSingleStepSupported = TimeSync_isSingleStepSupported(hTimeSyncPtp->timeSyncHandle);
        while (1)
        {
            /*Pend on semaphore*/
            SemaphoreP_pend(hTimeSyncPtp->syncTxSemHandle, SemaphoreP_WAIT_FOREVER);

            for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
            {
                if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port))
                {
                    linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                    if (linkStatus)
                    {
                        runFlag = false;

                        if (hTimeSyncPtp->ptpConfig.isMaster)
                        {
                            runFlag = true;
                        }

                        if ((hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_BOUNDARY_CLOCK) &&
                            (port != hTimeSyncPtp->masterPortNum) &&
                            (hTimeSyncPtp->tsRunTimeVar.bmcaDone == 1U))
                        {
                            runFlag = true;
                        }

                        if (runFlag == true)
                        {
                            if (!hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX])
                            {
                                /*Use API to get current time*/
                                TimeSync_getCurrentTime(hTimeSyncPtp->timeSyncHandle, &n_sec, &sec);

                                /*Write seconds into packet*/
                                TimeSync_convEndianess(&sec, hTimeSyncPtp->timeSyncBuff.syncTxBuf + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                                                       6);
                                /*Write nanoseconds into packet*/
                                TimeSync_convEndianess(&n_sec, hTimeSyncPtp->timeSyncBuff.syncTxBuf + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                                                       4);
                            }

                            /*write sequence id into frame*/
                            TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.syncTxBuf + TIMESYNC_PTP_SEQ_ID_OFFSET - offset,
                                                 hTimeSyncPtp->tsRunTimeVar.syncSequenceID[port]);

                            /*if 2-step then write same sequence id into follow up frame*/
                            if (hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX])
                            {
                                TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.followUpTxBuf[port] + TIMESYNC_PTP_SEQ_ID_OFFSET - offset,
                                                     hTimeSyncPtp->tsRunTimeVar.syncSequenceID[port]);
                            }

                            /**Add Source Port ID*/
                            TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.syncTxBuf + TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset,
                                                 (port + 1U));

                            if ((!hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX]) &&
                                (isSingleStepSupported))
                            {
                                TimeSync_writeTsSingleStepSync(hTimeSyncPtp->timeSyncHandle, port);
                            }

                            retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                           hTimeSyncPtp->timeSyncBuff.syncTxBuf,
                                                           hTimeSyncPtp->timeSyncBuff.syncBufSize,
                                                           port);
                            /*If frame was sent out, increment counter*/
                            if (retVal == TIMESYNC_OK)
                            {
                                hTimeSyncPtp->tsRunTimeVar.syncSequenceID[port]++;
                            }
                        }
                    }
                }
            }
        }
    }
}

static void TimeSyncPtp_announceTxTask(void* a0,
                                       void* a1)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)a0;
    uint64_t sec = 0;
    uint32_t n_sec = 0;
    uint8_t offset = hTimeSyncPtp->ptpConfig.frameOffset;
    int32_t retVal;
    uint8_t port = 0U;
    int8_t linkStatus = 0;
    volatile bool runFlag = false;

    while (1)
    {
        for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
        {
            if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port))
            {
                linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                if (linkStatus)
                {
                    runFlag = false;

                    if (hTimeSyncPtp->ptpConfig.isMaster)
                    {
                        runFlag = true;
                    }

                    if ((hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_BOUNDARY_CLOCK) &&
                        (port != hTimeSyncPtp->masterPortNum) &&
                        (hTimeSyncPtp->tsRunTimeVar.bmcaDone == 1U))
                    {
                        runFlag = true;
                    }

                    if (runFlag == true)
                    {
                        /*Use API to get current time*/
                        TimeSync_getCurrentTime(hTimeSyncPtp->timeSyncHandle, &n_sec, &sec);

                        /*Write seconds into packet*/
                        TimeSync_convEndianess(&sec,
                                               hTimeSyncPtp->timeSyncBuff.announceTxBuf + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                                               6);
                        /*Write nanoseconds into packet*/
                        TimeSync_convEndianess(&n_sec,
                                               hTimeSyncPtp->timeSyncBuff.announceTxBuf + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                                               4);

                        /*write sequence id into memory*/
                        TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.announceTxBuf + TIMESYNC_PTP_SEQ_ID_OFFSET -
                                             offset,
                                             hTimeSyncPtp->tsRunTimeVar.announceSequenceID[port]);

                        /**Add Source Port ID*/
                        TimeSync_addHalfWord(hTimeSyncPtp->timeSyncBuff.announceTxBuf + TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset,
                                             (port + 1U));

                        retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                       hTimeSyncPtp->timeSyncBuff.announceTxBuf,
                                                       hTimeSyncPtp->timeSyncBuff.announceBufSize,
                                                       port);
                        if (retVal == 0)
                        {
                            hTimeSyncPtp->tsRunTimeVar.announceSequenceID[port]++;
                        }
                    }
                }
            }
        }

        TaskP_sleep(hTimeSyncPtp->ptpConfig.announceSendInterval);
    }
}

static void TimeSyncPtp_ppsTask(void* arg0,
                                void* arg1)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)arg0;
    int32_t retVal = TIMESYNC_OK;

    while (1)
    {
        /*Pend on semaphore*/
        SemaphoreP_pend(hTimeSyncPtp->ppsSemHandle, SemaphoreP_WAIT_FOREVER);

        if (hTimeSyncPtp->ptpConfig.processToDSync2PPS)
        {
            /*Get the latch time stamp*/
            retVal = TimeSync_getPpsTs(hTimeSyncPtp->timeSyncHandle,
                                       &(hTimeSyncPtp->tsToDParams.pPsTsNS),
                                       &(hTimeSyncPtp->tsToDParams.pPsTsSec));
            if (retVal == TIMESYNC_OK)
            {
                /*Synchronize the clock*/
                TimeSyncPtp_synchronizeToD(hTimeSyncPtp);
                /*Calculate sync interval*/
                TimeSyncPtp_calcSyncIntervalToD(hTimeSyncPtp);
            }
        }
    }
}

void TimeSyncPtp_notifyPps(void *arg)
{
    if (arg != NULL)
    {
        TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)arg;
        if (hTimeSyncPtp->ptpConfig.processToDSync2PPS)
        {
            /*Post semaphore for PPS sync task*/
            SemaphoreP_post(hTimeSyncPtp->ppsSemHandle);
        }
    }
}

static void TimeSyncPtp_syncTxIsr(void* arg)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)arg;

    SemaphoreP_post(hTimeSyncPtp->syncTxSemHandle);
}

void TimeSyncPtp_enableMaster(TimeSyncPtp_Handle hTimeSyncPtp)
{
    /*Enable mode*/
    hTimeSyncPtp->ptpConfig.isMaster = 1;

    /*Populate parameters of DUT into the follow up frame*/
    TimeSyncPtp_initializeFollowUp(hTimeSyncPtp);

    /*Start the clock*/
    ClockP_start(hTimeSyncPtp->syncTxTimer);
}

void TimeSyncPtp_disableMaster(TimeSyncPtp_Handle hTimeSyncPtp)
{
    /*Disable mode*/
    hTimeSyncPtp->ptpConfig.isMaster = 0;

    /*Stop the timer*/
    ClockP_stop(hTimeSyncPtp->syncTxTimer);
}

void TimeSyncPtp_enableBoundaryClock(TimeSyncPtp_Handle hTimeSyncPtp)
{
    TimeSyncPtp_initializeFollowUp(hTimeSyncPtp);

    /*Start the clock*/
    ClockP_start(hTimeSyncPtp->syncTxTimer);
}

void TimeSyncPtp_disableBoundaryClock(TimeSyncPtp_Handle hTimeSyncPtp)
{
    /*Stop the timer*/
    ClockP_stop(hTimeSyncPtp->syncTxTimer);
}
