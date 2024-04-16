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
 * \file timeSync_icssg.c
 *
 * \brief This file contains the implemenation of ICSSG specific
 *        funcions for PTP stack
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

#include <ti/drv/sciclient/sciclient.h>


#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/include/dma/udma/enet_udma.h>
/* Include enet_dma.h after enet_udma.h as enet_udma.h contains type definations
 * for type contained in the enet_dma.h */
#include <ti/drv/enet/include/core/enet_dma.h>

#include <ti/drv/enet/examples/utils/include/enet_appmemutils_cfg.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>
#include <ti/drv/enet/examples/utils/include/enet_ethutils.h>
#include <ti/drv/enet/examples/utils/include/enet_mcm.h>

#include <ti/drv/enet/include/core/enet_mod_timesync.h>
#include <ti/drv/enet/include/per/icssg.h>

#include <ti/drv/enet/examples/timesync/timeSync.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_tools.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

#define TIMESYNC_TX_PKTINFO_COUNT           (64U)

/**
 * @def TIMESYNC_PTP_MSG_ID_OFFSET
 *      PTP message ID offset
 */
#define TIMESYNC_PTP_MSG_ID_OFFSET          (14U)

/**
 * @def TIMESYNC_PTP_SEQ_ID_OFFSET
 *      Offset for sequence identifier (incremented every frame)
 */
#define TIMESYNC_PTP_SEQ_ID_OFFSET          (44U)

/**
 * @def TIMESYNC_ANNEX_F_HEADER_SIZE
 *      Number of bytes in Annex F(bare Ethernet) header
 */
#define TIMESYNC_ANNEX_F_HEADER_SIZE        (14U)

/**
 * @def TIMESYNC_ANNEX_D_ANNEX_F_DIFF
 *      Number of extra bytes for Annex D(IPv4) from Annex F(802.3)
 */
#define TIMESYNC_ANNEX_D_ANNEX_F_DIFF       (28U)

/**
 * @def TIMESYNC_ANNEX_E_ANNEX_F_DIFF
 *      Number of extra bytes for Annex E(IPv6) from Annex F(802.3)
 */
#define TIMESYNC_ANNEX_E_ANNEX_F_DIFF       (48U)

/**
 * @def TIMESYNC_SINGLE_TAG_VLAN_HDR_SIZE
 *      Number of extra bytes for single tagged VLAN
 */
#define TIMESYNC_SINGLE_TAG_VLAN_HDR_SIZE   (4U)

/**
 * @def TIMESYNC_DOUBLE_TAG_VLAN_HDR_SIZE
 *      Number of extra bytes for double tagged VLAN
 */
#define TIMESYNC_DOUBLE_TAG_VLAN_HDR_SIZE   (8U)

/**
 * @def TIMESYNC_MILLION_PARTS
 *      Value of million useful in PPM calculations
 */
#define TIMESYNC_PPM_VALUE                  (1000000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct TimeSync_TxPktInfoEle_s
{
    uint8_t portNum;

    uint8_t frameType;

    uint16_t seqId;
} TimeSync_TxPktInfoEle;

typedef struct TimeSync_TxPktInfo_s
{
    TimeSync_TxPktInfoEle txTsPktInfoArr[TIMESYNC_TX_PKTINFO_COUNT];

    uint32_t rdIdx;

    uint32_t wrIdx;
}TimeSync_TxPktInfo;

typedef struct TimeSync_Obj_s
{
    TimeSync_Config timeSyncConfig;

    Enet_Type enetType;

    uint32_t instId;

    Enet_Handle hEnet;

    Udma_DrvHandle hUdmaDrv;

    EnetDma_RxChHandle hRxFlow;

    uint32_t rxFlowStartIdx;

    uint32_t rxFlowIdx;

    EnetDma_TxChHandle hTxCh;

    uint32_t txChNum;

    uint32_t coreId;

    uint32_t coreKey;

    EnetMcm_CmdIf hMcmCmdIf;

    EnetDma_PktQ rxFreeQ;

    EnetDma_PktQ rxReadyQ;

    EnetDma_PktQ txFreePktInfoQ;

    TimeSync_TxPktInfo txTsPktInfo;

    uint64_t lastTxTs;

    uint64_t lastRxTs;

    volatile bool txTsDone;

    /* Sequence number used as cookie for timestamp events. This value is passed
     * to the DMA packet when submitting a packet for transmission. Driver will
     * pass this same value when timestamp for that packet is ready. */
    uint32_t txTsSeqId;
} TimeSync_Obj;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t TimeSync_openDma(void);

static void TimeSync_closeDma(void);

static void TimeSync_initTxFreePktQ(void);

static void TimeSync_initRxReadyPktQ(void);

static int32_t TimeSync_setIcssgSpecialFrame(void);

static uint32_t TimeSync_retrieveTxDonePkts(void);

static uint32_t TimeSync_receiveRxReadyPkts(void);

static void TimeSync_getMsgId(uint8_t *msgId,
                              uint8_t *frame);

static void TimeSync_getSeqId(uint16_t *seqId,
                              uint8_t *frame);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static TimeSync_Obj gTimeSyncIcssgObj;

/**PTP Multicast addresses for comparison*/
static const uint8_t peerDlyMsgMAC[TIMESYNC_MAC_ADDR_LEN] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x0E};
static const uint8_t nonPeerDlyMsgMAC[TIMESYNC_MAC_ADDR_LEN] = {0x01, 0x1b, 0x19, 0x00, 0x00, 0x00};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void timeSync_txTsCb(Enet_Event evt,
                            uint32_t evtNum,
                            void *evtCbArgs,
                            void *arg1,
                            void *arg2)
{
    TimeSync_Obj *timeSyncObj = (TimeSync_Obj *)evtCbArgs;
    Icssg_TxTsEvtCbInfo *txTsInfo;

    txTsInfo = (Icssg_TxTsEvtCbInfo *)arg1;

    timeSyncObj->lastTxTs = txTsInfo->ts;
    timeSyncObj->txTsDone = true;
}

void TimeSync_rxNotifyFxn(void *appData)
{
    TimeSync_Handle timeSyncHandle = NULL;
    TimeSync_FrameNotifyConfig *frameNotifyCfg = NULL;
    uint32_t rxReadyCnt;
    uint32_t i = 0U;

    if (appData != NULL)
    {
        timeSyncHandle = (TimeSync_Handle)appData;
        frameNotifyCfg = &timeSyncHandle->timeSyncConfig.frameNotifyCfg;

        rxReadyCnt = TimeSync_receiveRxReadyPkts();
        for (i = 0U; i < rxReadyCnt; i++)
        {
            /* Notify PTP Rx callback */
            if (frameNotifyCfg->rxNotifyCb != NULL)
            {
                frameNotifyCfg->rxNotifyCb(frameNotifyCfg->rxNotifyCbArg);
            }
        }
    }
}

void TimeSync_txNotifyFxn(void *appData)
{
    uint32_t pktCount;
    TimeSync_TxPktInfo *pTxTsPktInfo = NULL;
    TimeSync_TxPktInfoEle *pTxTsPktInfoEle = NULL;
    TimeSync_Handle timeSyncHandle = NULL;
    TimeSync_FrameNotifyConfig *frameNotifyCfg = NULL;

    if (appData != NULL)
    {
        timeSyncHandle = (TimeSync_Handle)appData;
        frameNotifyCfg = &timeSyncHandle->timeSyncConfig.frameNotifyCfg;

        pktCount = TimeSync_retrieveTxDonePkts();
        EnetAppUtils_assert(pktCount != 0U);

        pTxTsPktInfo = &timeSyncHandle->txTsPktInfo;
        pTxTsPktInfoEle = &pTxTsPktInfo->txTsPktInfoArr[pTxTsPktInfo->rdIdx++];
        pTxTsPktInfo->rdIdx %= TIMESYNC_TX_PKTINFO_COUNT;

        /* Notify PTP Tx callback */
        if (frameNotifyCfg->txNotifyCb != NULL)
        {
            frameNotifyCfg->txNotifyCb(frameNotifyCfg->txNotifyCbArg,
                                       pTxTsPktInfoEle->portNum,
                                       pTxTsPktInfoEle->frameType,
                                       pTxTsPktInfoEle->seqId);
        }
    }
}

TimeSync_Handle TimeSync_open(TimeSync_Config *timeSyncConfig)
{
    int32_t status = TIMESYNC_OK;
    EnetMcm_HandleInfo handleInfo;
    EnetPer_AttachCoreOutArgs attachInfo;

    if (timeSyncConfig != NULL)
    {
        memset(&gTimeSyncIcssgObj, 0, sizeof(gTimeSyncIcssgObj));

        /*Copy timeSyncConfig to handle */
        gTimeSyncIcssgObj.timeSyncConfig = *timeSyncConfig;

        if (timeSyncConfig->socConfig.ipVersion == TIMESYNC_IP_VER_ICSSG_DUALMAC)
        {
            gTimeSyncIcssgObj.enetType = ENET_ICSSG_DUALMAC;
            gTimeSyncIcssgObj.instId   = timeSyncConfig->socConfig.instId;
        }
        else
        {
            status = TIMESYNC_PARAM_INVALID;
        }

        EnetAppUtils_assert(status == TIMESYNC_OK);

        gTimeSyncIcssgObj.coreId = EnetSoc_getCoreId();

        EnetMcm_getCmdIf(gTimeSyncIcssgObj.enetType, &gTimeSyncIcssgObj.hMcmCmdIf);
        EnetAppUtils_assert(gTimeSyncIcssgObj.hMcmCmdIf.hMboxCmd != NULL);
        EnetAppUtils_assert(gTimeSyncIcssgObj.hMcmCmdIf.hMboxResponse != NULL);

        EnetMcm_acquireHandleInfo(&gTimeSyncIcssgObj.hMcmCmdIf,
                                  &handleInfo);
        EnetMcm_coreAttach(&gTimeSyncIcssgObj.hMcmCmdIf,
                           gTimeSyncIcssgObj.coreId,
                           &attachInfo);

        gTimeSyncIcssgObj.hEnet = handleInfo.hEnet;
        gTimeSyncIcssgObj.hUdmaDrv = handleInfo.hUdmaDrv;
        gTimeSyncIcssgObj.coreKey  = attachInfo.coreKey;
        gTimeSyncIcssgObj.txTsSeqId = 0U;
        Enet_registerEventCb(gTimeSyncIcssgObj.hEnet,
                                 ENET_EVT_TIMESTAMP_TX,
                                 0U,
                                 timeSync_txTsCb,
                                 (void *)&gTimeSyncIcssgObj);

        if (gTimeSyncIcssgObj.hEnet == NULL)
        {
            EnetAppUtils_print("Failed to open ICSSG\n");
            EnetAppUtils_assert(gTimeSyncIcssgObj.hEnet == NULL);
        }

        if (gTimeSyncIcssgObj.hUdmaDrv == NULL)
        {
            EnetAppUtils_print("Failed to Get UDMA Handle\n");
            EnetAppUtils_assert(gTimeSyncIcssgObj.hUdmaDrv == NULL);
        }

        if (status == TIMESYNC_OK)
        {
            status = TimeSync_openDma();
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("Failed to open ICSSG DMA: %d\n", status);
            }
        }

        if (status == TIMESYNC_OK)
        {
            /* Add MAC addresses that need to be treated as special frames */
            status = TimeSync_setIcssgSpecialFrame();
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("Failed to set special frame: %d\n", status);
            }
        }

        /* If open failed, call close() to release resources */
        if (status != TIMESYNC_OK)
        {
            TimeSync_close(&gTimeSyncIcssgObj);
        }
    }
    else
    {
        status = TIMESYNC_PARAM_INVALID;
    }

    return (status == TIMESYNC_OK ? (&gTimeSyncIcssgObj) : NULL);
}

int32_t TimeSync_getRxTimestamp(TimeSync_Handle timeSyncHandle,
                                TimeSync_FrameType rxFrameType,
                                uint8_t rxPort,
                                uint16_t seqId,
                                uint32_t *nanoseconds,
                                uint64_t *seconds)
{
    int32_t status = TIMESYNC_OK;
    uint64_t tsVal = 0;

    if (timeSyncHandle != NULL)
    {
        tsVal = gTimeSyncIcssgObj.lastRxTs;
        *nanoseconds = (uint32_t)(tsVal % (uint64_t)TIMESYNC_SEC_TO_NS);
        *seconds = tsVal / (uint64_t)TIMESYNC_SEC_TO_NS;
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

int32_t TimeSync_getTxTimestamp(TimeSync_Handle timeSyncHandle,
                                TimeSync_FrameType txFrameType,
                                uint8_t txPort,
                                uint16_t seqId,
                                uint32_t *nanoseconds,
                                uint64_t *seconds)
{
    int32_t status = TIMESYNC_OK;
    uint64_t tsVal = 0ULL;

    if (timeSyncHandle != NULL)
    {
        gTimeSyncIcssgObj.txTsDone = false;
        while (!gTimeSyncIcssgObj.txTsDone)
        {
            Enet_MacPort macPort = ENET_MACPORT_DENORM(txPort);

            Enet_poll(gTimeSyncIcssgObj.hEnet, ENET_EVT_TIMESTAMP_TX, &macPort, sizeof(macPort));
        }

        tsVal = gTimeSyncIcssgObj.lastTxTs;
        *nanoseconds = (uint32_t)(tsVal % (uint64_t)TIMESYNC_SEC_TO_NS);
        *seconds = tsVal / (uint64_t)TIMESYNC_SEC_TO_NS;
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

int32_t TimeSync_adjTimeSlowComp(TimeSync_Handle timeSyncHandle,
                                 int32_t adjOffset,
                                 uint32_t interval)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    EnetTimeSync_TimestampAdj adjTsInArgs;

    if (timeSyncHandle != NULL)
    {
        adjTsInArgs.adjValInNsecs = adjOffset;
        adjTsInArgs.intervalInNsecs = interval;

        ENET_IOCTL_SET_IN_ARGS(&prms, &adjTsInArgs);
        status = Enet_ioctl(timeSyncHandle->hEnet,
                            timeSyncHandle->coreId,
                            ENET_TIMESYNC_IOCTL_ADJUST_TIMESTAMP,
                            &prms);
        EnetAppUtils_assert(status == TIMESYNC_OK);
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

int32_t TimeSync_setClockTime(TimeSync_Handle timeSyncHandle,
                              uint32_t nanoseconds,
                              uint64_t seconds)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    uint64_t tsVal = 0U;

    if (timeSyncHandle != NULL)
    {
        tsVal = (uint64_t)(((uint64_t)seconds * (uint64_t)TIMESYNC_SEC_TO_NS) + nanoseconds);
        ENET_IOCTL_SET_IN_ARGS(&prms, &tsVal);
        status = Enet_ioctl(timeSyncHandle->hEnet,
                            timeSyncHandle->coreId,
                            ENET_TIMESYNC_IOCTL_SET_TIMESTAMP,
                            &prms);
        EnetAppUtils_assert(status == TIMESYNC_OK);
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

void TimeSync_getCurrentTime(TimeSync_Handle timeSyncHandle,
                             uint32_t *nanoseconds,
                             uint64_t *seconds)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    uint64_t tsVal = 0U;

    if (timeSyncHandle != NULL)
    {
        /* Software Time stamp Push event */
        ENET_IOCTL_SET_OUT_ARGS(&prms, &tsVal);
        status = Enet_ioctl(timeSyncHandle->hEnet,
                            timeSyncHandle->coreId,
                            ENET_TIMESYNC_IOCTL_GET_CURRENT_TIMESTAMP,
                            &prms);
        EnetAppUtils_assert(status == TIMESYNC_OK);

        *nanoseconds = (uint32_t)(tsVal % (uint64_t)TIMESYNC_SEC_TO_NS);
        *seconds = tsVal / (uint64_t)TIMESYNC_SEC_TO_NS;
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
        *nanoseconds = 0U;
        *seconds = 0U;
    }
}

int32_t TimeSync_getPtpFrame(TimeSync_Handle timeSyncHandle,
                             uint8_t *frame,
                             uint32_t *size,
                             uint8_t *rxPort)
{
    int32_t status = TIMESYNC_OK;
    EnetDma_Pkt *pktInfo;
    EthFrame *rxFrame;
    uint32_t rxReadyCnt;

    if (timeSyncHandle != NULL)
    {
        rxReadyCnt = EnetQueue_getQCount(&gTimeSyncIcssgObj.rxReadyQ);
        if (rxReadyCnt > 0U)
        {
            /* Consume the received packets and release them */
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncIcssgObj.rxReadyQ);
            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_READYQ,
                                    ENET_PKTSTATE_APP_WITH_FREEQ);

            rxFrame = (EthFrame *)pktInfo->bufPtr;
            *size = pktInfo->userBufLen;
            memcpy(frame, rxFrame, *size);

            /* Port number is reported as 0xFF in UDMA descriptor, use fixed value
             * as Dual-MAC peripherals always use ENET_MAC_PORT_1 */
            *rxPort = (uint8_t)ENET_MACPORT_NORM(ENET_MAC_PORT_1);

            gTimeSyncIcssgObj.lastRxTs = pktInfo->tsInfo.rxPktTs;

            /* Release the received packet */
            EnetQueue_enq(&gTimeSyncIcssgObj.rxFreeQ, &pktInfo->node);

            EnetAppUtils_validatePacketState(&gTimeSyncIcssgObj.rxFreeQ,
                                             ENET_PKTSTATE_APP_WITH_FREEQ,
                                             ENET_PKTSTATE_APP_WITH_DRIVER);

            EnetDma_submitRxPktQ(gTimeSyncIcssgObj.hRxFlow,
                                         &gTimeSyncIcssgObj.rxFreeQ);
        }
        else
        {
            *size = 0U;
            status = TIMESYNC_FRAME_NOT_AVAILABLE;
        }
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

int32_t TimeSync_sendPtpFrame(TimeSync_Handle timeSyncHandle,
                              uint8_t *frame,
                              uint32_t size,
                              uint8_t txPort)
{
    int32_t status = TIMESYNC_OK;
    EnetDma_PktQ txSubmitQ;
    EnetDma_Pkt *pktInfo;
    uint8_t *txFrame;
    TimeSync_TxPktInfo *pTxTsPktInfo = NULL;
    TimeSync_TxPktInfoEle *pTxTsPktInfoEle = NULL;

    if (timeSyncHandle != NULL)
    {
        EnetQueue_initQ(&txSubmitQ);
        pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncIcssgObj.txFreePktInfoQ);
        if (NULL != pktInfo)
        {
            txFrame = (uint8_t *)pktInfo->bufPtr;
            memcpy(txFrame, frame, size);

            pktInfo->userBufLen = size;
            pktInfo->appPriv    = (void *)timeSyncHandle;

            pktInfo->tsInfo.enableHostTxTs = true;
            pktInfo->tsInfo.txPktSeqId     = gTimeSyncIcssgObj.txTsSeqId++;
            pktInfo->tsInfo.txPktMsgType   = 0U; /* Don't care for ICSSG */
            pktInfo->tsInfo.txPktDomain    = 0U; /* Don't care for ICSSG */

            /* Save tx pkt info to re-use during notify callback */
            pTxTsPktInfo = &timeSyncHandle->txTsPktInfo;
            pTxTsPktInfoEle = &pTxTsPktInfo->txTsPktInfoArr[pTxTsPktInfo->wrIdx++];
            pTxTsPktInfoEle->portNum = txPort;
            TimeSync_getMsgId(&pTxTsPktInfoEle->frameType, frame);
            TimeSync_getSeqId(&pTxTsPktInfoEle->seqId, frame);
            pTxTsPktInfo->wrIdx %= TIMESYNC_TX_PKTINFO_COUNT;

            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_FREEQ,
                                    ENET_PKTSTATE_APP_WITH_DRIVER);
            EnetQueue_enq(&txSubmitQ, &pktInfo->node);

            if (0U != EnetQueue_getQCount(&txSubmitQ))
            {
                status = EnetDma_submitTxPktQ(gTimeSyncIcssgObj.hTxCh, &txSubmitQ);
            }
        }
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

int32_t TimeSync_getPpsTs(TimeSync_Handle timeSyncHandle,
                          uint32_t *nanoseconds,
                          uint64_t *seconds)
{
    int32_t status;

    if (timeSyncHandle != NULL)
    {
        status = TIMESYNC_OK;
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

void TimeSync_recalibratePps(TimeSync_Handle timeSyncHandle)
{
}

int8_t TimeSync_isPortLinkUp(TimeSync_Handle timeSyncHandle,
                             uint8_t portNum)
{
    int8_t isLinkUp = FALSE;
    bool isLinkUpFlag = false;

    if (timeSyncHandle != NULL)
    {
        isLinkUpFlag = EnetAppUtils_isPortLinkUp(timeSyncHandle->hEnet,
                                                 timeSyncHandle->coreId,
                                                 (Enet_MacPort)(ENET_MACPORT_NORM(portNum)));
    }

    if (isLinkUpFlag == true)
    {
        isLinkUp = TRUE;
    }

    return isLinkUp;
}

int32_t TimeSync_isSingleStepSupported(TimeSync_Handle timeSyncHandle)
{
    return FALSE;
}

void TimeSync_reset(TimeSync_Handle timeSyncHandle)
{
    int32_t status = TIMESYNC_OK;
    EnetDma_Pkt *pktInfo;

    if (timeSyncHandle != NULL)
    {
        /* Disable Rx & Tx Events */
        status = EnetDma_disableRxEvent(timeSyncHandle->hRxFlow);
        if (status != TIMESYNC_OK)
        {
            EnetAppUtils_print("EnetDma_disableRxEvent() failed: %d\n", status);
        }

        status = EnetDma_disableTxEvent(timeSyncHandle->hTxCh);
        if (status != TIMESYNC_OK)
        {
            EnetAppUtils_print("EnetDma_disableTxEvent() failed: %d\n", status);
        }

        /* Clean the SW queues */
        if (status == TIMESYNC_OK)
        {
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncIcssgObj.rxReadyQ);
            while (pktInfo != NULL)
            {
                /* Consume the received packets and release them */
                EnetDma_checkPktState(&pktInfo->pktState,
                                        ENET_PKTSTATE_MODULE_APP,
                                        ENET_PKTSTATE_APP_WITH_READYQ,
                                        ENET_PKTSTATE_APP_WITH_FREEQ);

                EnetQueue_enq(&gTimeSyncIcssgObj.rxFreeQ, &pktInfo->node);

                pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncIcssgObj.rxReadyQ);
            }

            EnetAppUtils_validatePacketState(&gTimeSyncIcssgObj.rxFreeQ,
                                             ENET_PKTSTATE_APP_WITH_FREEQ,
                                             ENET_PKTSTATE_APP_WITH_DRIVER);

            EnetDma_submitRxPktQ(gTimeSyncIcssgObj.hRxFlow,
                                         &gTimeSyncIcssgObj.rxFreeQ);

            TimeSync_retrieveTxDonePkts();
        }

        /* Clear local book-keeping of Tx Info */
        if (status == TIMESYNC_OK)
        {
            memset(&timeSyncHandle->txTsPktInfo, 0, sizeof(timeSyncHandle->txTsPktInfo));
        }

        /* Enable Rx & Tx Events */
        if (status == TIMESYNC_OK)
        {
            status = EnetDma_enableRxEvent(timeSyncHandle->hRxFlow);
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("EnetDma_enableRxEvent() failed: %d\n", status);
            }

            status = EnetDma_enableTxEvent(timeSyncHandle->hTxCh);
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("EnetDma_enableTxEvent() failed: %d\n", status);
            }
        }
    }

}

void TimeSync_close(TimeSync_Handle timeSyncHandle)
{
    if (timeSyncHandle != NULL)
    {
        /* Close DMA */
        TimeSync_closeDma();

        /* Detach core from MCM */
        EnetMcm_coreDetach(&timeSyncHandle->hMcmCmdIf,
                           timeSyncHandle->coreId,
                           timeSyncHandle->coreKey);
        /* Release handle info */
        EnetMcm_releaseHandleInfo(&timeSyncHandle->hMcmCmdIf);

    }
}

/* ========================================================================== */
/*                        IP-specific function declarations                  */
/* ========================================================================== */

void TimeSync_updateParentAddress(TimeSync_Handle timeSyncHandle,
                                  uint8_t *parentMac)
{
    /* Nothing to be done for ICSSG */
}

void TimeSync_setRcf(TimeSync_Handle timeSyncHandle,
                     uint32_t rcfValue)
{
    /* Nothing to be done for ICSSG */
}

void TimeSync_setPathDelay(TimeSync_Handle timeSyncHandle,
                           uint32_t pathDelay,
                           uint8_t portNum)
{
    /* Nothing to be done for ICSSG */
}

void TimeSync_writeTsSingleStepSync(TimeSync_Handle timeSyncHandle,
                                    uint8_t portNum)
{
    /* Nothing to be done for ICSSG */
}

/* ========================================================================== */
/*                          Internal Function Definitions                     */
/* ========================================================================== */

static int32_t TimeSync_openDma(void)
{
    int32_t status = TIMESYNC_OK;
    EnetDma_Handle hDma;
    EnetUdma_OpenRxFlowPrms icssgRxFlowCfg;
    EnetUdma_OpenTxChPrms icssgTxChCfg;

    hDma = Enet_getDmaHandle(gTimeSyncIcssgObj.hEnet);
    EnetAppUtils_assert(hDma != NULL);

    /* Open the icssg TX channel  */
    if (status == TIMESYNC_OK)
    {
        EnetDma_initTxChParams(&icssgTxChCfg);

        icssgTxChCfg.hUdmaDrv = gTimeSyncIcssgObj.hUdmaDrv;
        icssgTxChCfg.cbArg = &gTimeSyncIcssgObj;
        icssgTxChCfg.notifyCb = TimeSync_txNotifyFxn;

        EnetAppUtils_setCommonTxChPrms(&icssgTxChCfg);

        EnetAppUtils_openTxCh(gTimeSyncIcssgObj.hEnet,
                              gTimeSyncIcssgObj.coreKey,
                              gTimeSyncIcssgObj.coreId,
                              &gTimeSyncIcssgObj.txChNum,
                              &gTimeSyncIcssgObj.hTxCh,
                              &icssgTxChCfg);

        TimeSync_initTxFreePktQ();

        if (NULL != gTimeSyncIcssgObj.hTxCh)
        {
            status = EnetDma_enableTxEvent(gTimeSyncIcssgObj.hTxCh);
            if (TIMESYNC_OK != status)
            {
                /* Free the Ch Num if enable event failed */
                EnetAppUtils_freeTxCh(gTimeSyncIcssgObj.hEnet,
                                      gTimeSyncIcssgObj.coreKey,
                                      gTimeSyncIcssgObj.coreId,
                                      gTimeSyncIcssgObj.txChNum);
                EnetAppUtils_print("EnetDma_enableTxEvent() failed: %d\n", status);
                status = ENET_EFAIL;
            }
        }
        else
        {
            /* Free the Ch Num if open Tx Ch failed */
            EnetAppUtils_freeTxCh(gTimeSyncIcssgObj.hEnet,
                                  gTimeSyncIcssgObj.coreKey,
                                  gTimeSyncIcssgObj.coreId,
                                  gTimeSyncIcssgObj.txChNum);
            EnetAppUtils_print("EnetAppUtils_openTxCh() failed to open: %d\n", status);
            status = ENET_EFAIL;
        }
    }

    /* Open the icssg RX flow  */
    if (status == TIMESYNC_OK)
    {
        EnetDma_initRxChParams(&icssgRxFlowCfg);
        icssgRxFlowCfg.notifyCb     = TimeSync_rxNotifyFxn;
        icssgRxFlowCfg.hUdmaDrv     = gTimeSyncIcssgObj.hUdmaDrv;
        icssgRxFlowCfg.cbArg        = &gTimeSyncIcssgObj;
        icssgRxFlowCfg.useGlobalEvt = true;

        EnetAppUtils_setCommonRxFlowPrms(&icssgRxFlowCfg);

        status = EnetAppUtils_allocRxFlow(gTimeSyncIcssgObj.hEnet,
                                          gTimeSyncIcssgObj.coreKey,
                                          gTimeSyncIcssgObj.coreId,
                                          &gTimeSyncIcssgObj.rxFlowStartIdx,
                                          &gTimeSyncIcssgObj.rxFlowIdx);
        if (status == TIMESYNC_OK)
        {
            icssgRxFlowCfg.startIdx = gTimeSyncIcssgObj.rxFlowStartIdx;
            icssgRxFlowCfg.flowIdx  = gTimeSyncIcssgObj.rxFlowIdx;

            gTimeSyncIcssgObj.hRxFlow = EnetDma_openRxCh(hDma, &icssgRxFlowCfg);
            if (NULL == gTimeSyncIcssgObj.hRxFlow)
            {
                EnetAppUtils_freeRxFlow(gTimeSyncIcssgObj.hEnet,
                                        gTimeSyncIcssgObj.coreKey,
                                        gTimeSyncIcssgObj.coreId,
                                        gTimeSyncIcssgObj.rxFlowIdx);
                EnetAppUtils_print("EnetDma_openRxCh() failed to open: %d\n", status);
            }
            else
            {
                /* Submit all ready RX buffers to DMA.*/
                TimeSync_initRxReadyPktQ();
            }
        }
        else
        {
            EnetAppUtils_print("EnetAppUtils_allocRxFlow() failed to open: %d\n", status);
        }

        /* Close Tx channel if Rx flow open failed */
        if (status != TIMESYNC_OK)
        {
            status = EnetDma_disableTxEvent(gTimeSyncIcssgObj.hTxCh);
            EnetAppUtils_freeTxCh(gTimeSyncIcssgObj.hEnet,
                                  gTimeSyncIcssgObj.coreKey,
                                  gTimeSyncIcssgObj.coreId,
                                  gTimeSyncIcssgObj.txChNum);
        }
    }

    return status;
}

static void TimeSync_closeDma(void)
{
    int32_t status = TIMESYNC_OK;
    EnetDma_PktQ fqPktInfoQ;
    EnetDma_PktQ cqPktInfoQ;

    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);

    /* Close RX Flow */
    if (gTimeSyncIcssgObj.hRxFlow != NULL)
    {
        status = EnetDma_closeRxCh(gTimeSyncIcssgObj.hRxFlow,
                                     &fqPktInfoQ,
                                     &cqPktInfoQ);
        if (status == TIMESYNC_OK)
        {
            EnetAppUtils_freeRxFlow(gTimeSyncIcssgObj.hEnet,
                                    gTimeSyncIcssgObj.coreKey,
                                    gTimeSyncIcssgObj.coreId,
                                    gTimeSyncIcssgObj.rxFlowIdx);
            EnetAppUtils_freePktInfoQ(&fqPktInfoQ);
            EnetAppUtils_freePktInfoQ(&cqPktInfoQ);
        }
        else
        {
            EnetAppUtils_print("EnetDma_closeRxCh() failed to open: %d\n", status);
        }

    }

    /* Close TX channel */
    if (gTimeSyncIcssgObj.hTxCh != NULL)
    {
        if (status == TIMESYNC_OK)
        {
            EnetQueue_initQ(&fqPktInfoQ);
            EnetQueue_initQ(&cqPktInfoQ);

            EnetAppUtils_closeTxCh(gTimeSyncIcssgObj.hEnet,
                                   gTimeSyncIcssgObj.coreKey,
                                   gTimeSyncIcssgObj.coreId,
                                   &fqPktInfoQ,
                                   &cqPktInfoQ,
                                   gTimeSyncIcssgObj.hTxCh,
                                   gTimeSyncIcssgObj.txChNum);
            EnetAppUtils_freePktInfoQ(&fqPktInfoQ);
            EnetAppUtils_freePktInfoQ(&cqPktInfoQ);

            EnetAppUtils_freePktInfoQ(&gTimeSyncIcssgObj.rxFreeQ);
            EnetAppUtils_freePktInfoQ(&gTimeSyncIcssgObj.txFreePktInfoQ);
        }
    }

}

static void TimeSync_initTxFreePktQ(void)
{
    EnetDma_Pkt *pPktInfo;
    uint32_t i;

    /* Initialize all queues */
    EnetQueue_initQ(&gTimeSyncIcssgObj.txFreePktInfoQ);

    /* Initialize TX EthPkts and queue them to txFreePktInfoQ */
    for (i = 0U; i < ENET_MEM_NUM_TX_PKTS; i++)
    {
        pPktInfo = EnetMem_allocEthPkt(&gTimeSyncIcssgObj,
                                                  ENET_MEM_LARGE_POOL_PKT_SIZE,
                                                  UDMA_CACHELINE_ALIGNMENT);
        EnetAppUtils_assert(pPktInfo != NULL);
        ENET_UTILS_SET_PKT_APP_STATE(&pPktInfo->pktState, ENET_PKTSTATE_APP_WITH_FREEQ);

        EnetQueue_enq(&gTimeSyncIcssgObj.txFreePktInfoQ, &pPktInfo->node);
    }
}

static void TimeSync_initRxReadyPktQ(void)
{
    EnetDma_PktQ rxReadyQ;
    EnetDma_Pkt *pPktInfo;
    int32_t status;
    uint32_t i;

    EnetQueue_initQ(&gTimeSyncIcssgObj.rxFreeQ);
    EnetQueue_initQ(&gTimeSyncIcssgObj.rxReadyQ);
    EnetQueue_initQ(&rxReadyQ);

    for (i = 0U; i < ENET_MEM_NUM_RX_PKTS; i++)
    {
        pPktInfo = EnetMem_allocEthPkt(&gTimeSyncIcssgObj,
                                                  ENET_MEM_LARGE_POOL_PKT_SIZE,
                                                  UDMA_CACHELINE_ALIGNMENT);
        EnetAppUtils_assert(pPktInfo != NULL);
        ENET_UTILS_SET_PKT_APP_STATE(&pPktInfo->pktState, ENET_PKTSTATE_APP_WITH_FREEQ);
        EnetQueue_enq(&gTimeSyncIcssgObj.rxFreeQ, &pPktInfo->node);
    }

    /* Retrieve any ICSSG packets which are ready */
    status = EnetDma_retrieveRxPktQ(gTimeSyncIcssgObj.hRxFlow, &rxReadyQ);
    EnetAppUtils_assert(status == TIMESYNC_OK);
    /* There should not be any packet with DMA during init */
    EnetAppUtils_assert(EnetQueue_getQCount(&rxReadyQ) == 0U);

    EnetAppUtils_validatePacketState(&gTimeSyncIcssgObj.rxFreeQ,
                                     ENET_PKTSTATE_APP_WITH_FREEQ,
                                     ENET_PKTSTATE_APP_WITH_DRIVER);

    EnetDma_submitRxPktQ(gTimeSyncIcssgObj.hRxFlow,
                                 &gTimeSyncIcssgObj.rxFreeQ);

    /* Assert here as during init no. of DMA descriptors should be equal to
     * no. of free Ethernet buffers available with app */
    EnetAppUtils_assert(0U == EnetQueue_getQCount(&gTimeSyncIcssgObj.rxFreeQ));
}

static int32_t TimeSync_setIcssgSpecialFrame(void)
{
    Enet_IoctlPrms prms;
    Icssg_FdbEntry fdbEntry;
    uint32_t flags;
    int32_t status = TIMESYNC_OK;

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_IEEE_802_3)
    {
        flags = (ICSSG_FDB_ENTRY_P0_MEMBERSHIP |
                 ICSSG_FDB_ENTRY_P1_MEMBERSHIP |
                 ICSSG_FDB_ENTRY_P2_MEMBERSHIP |
                 ICSSG_FDB_ENTRY_VALID |
                 ICSSG_FDB_ENTRY_BLOCK);

        /* FDB entry for peerDlyMsgMAC address to be treated as a special frame */
        fdbEntry.vlanId = -1;
        fdbEntry.fdbEntry[0U] = flags;
        fdbEntry.fdbEntry[1U] = flags;
        EnetUtils_copyMacAddr(&fdbEntry.macAddr[0U], &peerDlyMsgMAC[0U]);

        ENET_IOCTL_SET_IN_ARGS(&prms, &fdbEntry);
        status = EnetMcm_ioctl(&gTimeSyncIcssgObj.hMcmCmdIf, ICSSG_FDB_IOCTL_ADD_ENTRY, &prms);
        if (status != ENET_SOK)
        {
            EnetAppUtils_print("TimeSync_setIcssgSpecialFrame() failed to add FDB entry\n", status);
        }

        /* FDB entry for nonPeerDlyMsgMAC address to be treated as a special frame */
        if (status == ENET_SOK)
        {
            fdbEntry.vlanId = -1;
            fdbEntry.fdbEntry[0U] = flags;
            fdbEntry.fdbEntry[1U] = flags;
            EnetUtils_copyMacAddr(&fdbEntry.macAddr[0U], &nonPeerDlyMsgMAC[0U]);

            ENET_IOCTL_SET_IN_ARGS(&prms, &fdbEntry);
            status = EnetMcm_ioctl(&gTimeSyncIcssgObj.hMcmCmdIf, ICSSG_FDB_IOCTL_ADD_ENTRY, &prms);
            if (status != ENET_SOK)
            {
                EnetAppUtils_print("TimeSync_setIcssgSpecialFrame() failed to add FDB entry\n", status);
            }
        }
    }
    else
    {
        status = TIMESYNC_UNSUPPORTED_FORMAT;
    }

    return status;
}

static uint32_t TimeSync_retrieveTxDonePkts(void)
{
    EnetDma_PktQ txFreeQ;
    EnetDma_Pkt *pktInfo;
    int32_t status;
    uint32_t txFreeQCnt = 0U;

    EnetQueue_initQ(&txFreeQ);

    /* Retrieve any ICSSG packets that may be free now */
    status = EnetDma_retrieveTxPktQ(gTimeSyncIcssgObj.hTxCh, &txFreeQ);
    if (status == TIMESYNC_OK)
    {
        txFreeQCnt = EnetQueue_getQCount(&txFreeQ);

        pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&txFreeQ);
        while (NULL != pktInfo)
        {
            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_DRIVER,
                                    ENET_PKTSTATE_APP_WITH_FREEQ);

            EnetQueue_enq(&gTimeSyncIcssgObj.txFreePktInfoQ, &pktInfo->node);
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&txFreeQ);
        }
    }
    else
    {
        EnetAppUtils_print("EnetDma_retrieveTxPktQ() failed to retrieve pkts: %d\n", status);
    }

    return txFreeQCnt;
}

static uint32_t TimeSync_receiveRxReadyPkts(void)
{
    EnetDma_PktQ rxReadyQ;
    EnetDma_Pkt *pktInfo;
    int32_t status;
    uint32_t rxReadyCnt = 0U;

    EnetQueue_initQ(&rxReadyQ);

    /* Retrieve any ICSSG packets which are ready */
    status = EnetDma_retrieveRxPktQ(gTimeSyncIcssgObj.hRxFlow, &rxReadyQ);
    rxReadyCnt = EnetQueue_getQCount(&rxReadyQ);
    if (status == TIMESYNC_OK)
    {
        /* Queue the received packet to rxReadyQ and pass new ones from rxFreeQ */
        pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&rxReadyQ);
        while (pktInfo != NULL)
        {
            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_DRIVER,
                                    ENET_PKTSTATE_APP_WITH_READYQ);

            EnetQueue_enq(&gTimeSyncIcssgObj.rxReadyQ, &pktInfo->node);
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&rxReadyQ);
        }
    }
    else
    {
        EnetAppUtils_print("TimeSync_receiveRxReadyPkts() failed to retrieve pkts: %d\n", status);
    }

    return rxReadyCnt;
}

static void TimeSync_getMsgId(uint8_t *msgId,
                              uint8_t *frame)
{
    uint32_t offset = TIMESYNC_PTP_MSG_ID_OFFSET;

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV4)
    {
        offset += TIMESYNC_ANNEX_D_ANNEX_F_DIFF;
    }

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV6)
    {
        offset += TIMESYNC_ANNEX_E_ANNEX_F_DIFF;
    }

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_SINGLE_TAG)
    {
        offset += TIMESYNC_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_DOUBLE_TAG)
    {
        offset += TIMESYNC_DOUBLE_TAG_VLAN_HDR_SIZE;
    }

    *msgId = *(frame + offset);
    *msgId = *msgId & 0xF;
}

static void TimeSync_getSeqId(uint16_t *seqId,
                              uint8_t *frame)
{
    uint32_t offset = TIMESYNC_PTP_SEQ_ID_OFFSET;

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV4)
    {
        offset += TIMESYNC_ANNEX_D_ANNEX_F_DIFF;
    }

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV6)
    {
        offset += TIMESYNC_ANNEX_E_ANNEX_F_DIFF;
    }

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_SINGLE_TAG)
    {
        offset += TIMESYNC_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    if (gTimeSyncIcssgObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_DOUBLE_TAG)
    {
        offset += TIMESYNC_DOUBLE_TAG_VLAN_HDR_SIZE;
    }

    *seqId = *(uint16_t *)(frame + offset);
    *seqId = Enet_ntohs(*seqId);
}
