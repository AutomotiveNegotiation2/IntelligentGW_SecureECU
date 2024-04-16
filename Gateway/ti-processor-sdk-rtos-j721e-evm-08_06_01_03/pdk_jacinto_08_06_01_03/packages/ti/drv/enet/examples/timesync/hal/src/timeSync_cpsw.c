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
 * \file timeSync_cpsw.c
 *
 * \brief This file contains the implemenation of CPSW specific
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

    /** CPTS hardware push instance used for PPS */
    CpswCpts_HwPush hwPush;
} TimeSync_Obj;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t TimeSync_openDma(void);

static void TimeSync_closeDma(void);

static void TimeSync_initTxFreePktQ(void);

static void TimeSync_initRxReadyPktQ(void);

static int32_t TimeSync_setCpswAleClassifier(void);

static int32_t TimeSync_setMacPortConfig(void);

static void TimeSync_setPortTsEventPrms(CpswMacPort_TsEventCfg *tsPortEventCfg);

static uint32_t TimeSync_retrieveTxDonePkts(void);

static uint32_t TimeSync_receiveRxReadyPkts(void);

static void TimeSync_getMsgId(uint8_t *msgId,
                              uint8_t *frame);

static void TimeSync_getSeqId(uint16_t *seqId,
                              uint8_t *frame);

static int32_t TimeSync_configPps(Enet_Type enetType, uint32_t instId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static TimeSync_Obj gTimeSyncCpswObj;

/**PTP Multicast addresses for comparison*/
static const uint8_t peerDlyMsgMAC[TIMESYNC_MAC_ADDR_LEN] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x0E};
static const uint8_t nonPeerDlyMsgMAC[TIMESYNC_MAC_ADDR_LEN] = {0x01, 0x1b, 0x19, 0x00, 0x00, 0x00};

static const uint8_t peerDlyMsgIpv4[TIMESYNC_IPV4_ADDR_LEN] = {224U, 0U, 0U, 107U};
static const uint8_t nonPeerDlyMsgIpv4[TIMESYNC_IPV4_ADDR_LEN] = {224U, 0U, 1U, 129U};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

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

void TimeSync_ppsHwPushNotifyFxn(void *cbArg,
                                 CpswCpts_HwPush hwPushNum)
{
    TimeSync_Handle timeSyncHandle = NULL;
    TimeSync_PpsConfig *pPpsConfig = NULL;

    if (cbArg != NULL)
    {
        timeSyncHandle = (TimeSync_Handle)cbArg;

        if (hwPushNum == gTimeSyncCpswObj.hwPush)
        {
            /* Call PPS callback */
            pPpsConfig = &timeSyncHandle->timeSyncConfig.protoCfg.ppsConfig;
            if (pPpsConfig->ppsNotifyCb != NULL)
            {
                pPpsConfig->ppsNotifyCb(pPpsConfig->ppsNotifyCbArg);
            }
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
        memset(&gTimeSyncCpswObj, 0, sizeof(gTimeSyncCpswObj));

        /*Copy timeSyncConfig to handle */
        gTimeSyncCpswObj.timeSyncConfig = *timeSyncConfig;

        if (timeSyncConfig->socConfig.ipVersion == TIMESYNC_IP_VER_CPSW_2G)
        {
            if (timeSyncConfig->socConfig.instId == 0U)
            {
                gTimeSyncCpswObj.enetType = ENET_CPSW_2G;
                gTimeSyncCpswObj.instId   = 0U;
                gTimeSyncCpswObj.hwPush   = CPSW_CPTS_HWPUSH_3;
            }
#if defined(SOC_J721S2) || defined(SOC_J784S4)
            else if (timeSyncConfig->socConfig.instId == 1)
            {
                gTimeSyncCpswObj.enetType = ENET_CPSW_2G;
                gTimeSyncCpswObj.instId   = 1U;
                gTimeSyncCpswObj.hwPush   = CPSW_CPTS_HWPUSH_3;
            }
#endif
            else
            {
                status = TIMESYNC_PARAM_INVALID;
            }
        }
#if defined(SOC_J721E) || defined(SOC_J784S4)
        else if (timeSyncConfig->socConfig.ipVersion == TIMESYNC_IP_VER_CPSW_9G)
        {
            gTimeSyncCpswObj.enetType = ENET_CPSW_9G;
            gTimeSyncCpswObj.instId   = 0U;
            gTimeSyncCpswObj.hwPush   = CPSW_CPTS_HWPUSH_1;
        }
#endif
#if defined(SOC_J7200)
        else if (timeSyncConfig->socConfig.ipVersion == TIMESYNC_IP_VER_CPSW_5G)
        {
            gTimeSyncCpswObj.enetType = ENET_CPSW_5G;
            gTimeSyncCpswObj.instId   = 0U;
            gTimeSyncCpswObj.hwPush   = CPSW_CPTS_HWPUSH_1;
        }
#endif
        else
        {
            status = TIMESYNC_PARAM_INVALID;
        }

        EnetAppUtils_assert(status == TIMESYNC_OK);

        gTimeSyncCpswObj.coreId = EnetSoc_getCoreId();

        EnetMcm_getCmdIf(gTimeSyncCpswObj.enetType, &gTimeSyncCpswObj.hMcmCmdIf);
        EnetAppUtils_assert(gTimeSyncCpswObj.hMcmCmdIf.hMboxCmd != NULL);
        EnetAppUtils_assert(gTimeSyncCpswObj.hMcmCmdIf.hMboxResponse != NULL);

        EnetMcm_acquireHandleInfo(&gTimeSyncCpswObj.hMcmCmdIf,
                                  &handleInfo);
        EnetMcm_coreAttach(&gTimeSyncCpswObj.hMcmCmdIf,
                           gTimeSyncCpswObj.coreId,
                           &attachInfo);

        gTimeSyncCpswObj.hEnet = handleInfo.hEnet;
        gTimeSyncCpswObj.hUdmaDrv = handleInfo.hUdmaDrv;
        gTimeSyncCpswObj.coreKey  = attachInfo.coreKey;

        if (gTimeSyncCpswObj.hEnet == NULL)
        {
            EnetAppUtils_print("Failed to open CPSW\n");
            EnetAppUtils_assert(gTimeSyncCpswObj.hEnet == NULL);
        }

        if (gTimeSyncCpswObj.hUdmaDrv == NULL)
        {
            EnetAppUtils_print("Failed to Get UDMA Handle\n");
            EnetAppUtils_assert(gTimeSyncCpswObj.hUdmaDrv == NULL);
        }

        if (status == TIMESYNC_OK)
        {
            /* MAC port config */
            status = TimeSync_setMacPortConfig();

            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("Failed to configure MAC for timestampping: %d\n", status);
            }
        }

        if (status == TIMESYNC_OK)
        {
            status = TimeSync_openDma();
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("Failed to open CPSW DMA: %d\n", status);
            }
        }

        if (status == TIMESYNC_OK)
        {
            /* Based on network protocol type set classifier */
            status = TimeSync_setCpswAleClassifier();
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("Failed to set Classifier: %d\n", status);
            }
        }

        if (status == TIMESYNC_OK)
        {
            status = TimeSync_configPps(gTimeSyncCpswObj.enetType, gTimeSyncCpswObj.instId);
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("Failed to configure PPS generation: %d\n", status);
            }
        }

        /* If open failed, call close() to release resources */
        if (status != TIMESYNC_OK)
        {
            TimeSync_close(&gTimeSyncCpswObj);
        }
    }
    else
    {
        status = TIMESYNC_PARAM_INVALID;
    }

    return (status == TIMESYNC_OK ? (&gTimeSyncCpswObj) : NULL);
}

int32_t TimeSync_getRxTimestamp(TimeSync_Handle timeSyncHandle,
                                TimeSync_FrameType rxFrameType,
                                uint8_t rxPort,
                                uint16_t seqId,
                                uint32_t *nanoseconds,
                                uint64_t *seconds)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    EnetTimeSync_GetEthTimestampInArgs inArgs;
    uint64_t tsVal;

    if (timeSyncHandle != NULL)
    {
        inArgs.msgType = (EnetTimeSync_MsgType)rxFrameType;
        inArgs.seqId   = seqId;
        inArgs.portNum = rxPort;
        inArgs.domain  = 0U;

        if (status == TIMESYNC_OK)
        {
            ENET_IOCTL_SET_INOUT_ARGS(&prms, &inArgs, &tsVal);
            status = Enet_ioctl(timeSyncHandle->hEnet,
                                timeSyncHandle->coreId,
                                ENET_TIMESYNC_IOCTL_GET_ETH_RX_TIMESTAMP,
                                &prms);
            if (status == ENET_ENOTFOUND)
            {
                tsVal = 0U;
            }
            *nanoseconds = (uint32_t)(tsVal % (uint64_t)TIMESYNC_SEC_TO_NS);
            *seconds = tsVal / (uint64_t)TIMESYNC_SEC_TO_NS;
        }
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
    Enet_IoctlPrms prms;
    EnetTimeSync_GetEthTimestampInArgs inArgs;
    uint64_t tsVal;

    if (timeSyncHandle != NULL)
    {
        inArgs.msgType = (EnetTimeSync_MsgType)txFrameType;
        inArgs.seqId = seqId;
        inArgs.portNum = txPort;
        inArgs.domain  = 0U;

        if (status == TIMESYNC_OK)
        {
            ENET_IOCTL_SET_INOUT_ARGS(&prms, &inArgs, &tsVal);
            status = Enet_ioctl(timeSyncHandle->hEnet,
                                timeSyncHandle->coreId,
                                ENET_TIMESYNC_IOCTL_GET_ETH_TX_TIMESTAMP,
                                &prms);
            if (status == ENET_ENOTFOUND)
            {
                tsVal = 0U;
            }
            *nanoseconds = (uint32_t)(tsVal % (uint64_t)TIMESYNC_SEC_TO_NS);
            *seconds = tsVal / (uint64_t)TIMESYNC_SEC_TO_NS;
        }
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

int32_t TimeSync_adjTimeSlowComp(TimeSync_Handle timeSyncHandle,
                                 int64_t adjOffset,
                                 uint32_t interval)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    EnetTimeSync_TimestampAdj adjTsInArgs;

    if (timeSyncHandle != NULL)
    {
        adjTsInArgs.adjValInNsecs   = (-1 * adjOffset);
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
        rxReadyCnt = EnetQueue_getQCount(&gTimeSyncCpswObj.rxReadyQ);
        if (rxReadyCnt > 0U)
        {
            /* Consume the received packets and release them */
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncCpswObj.rxReadyQ);
            EnetDma_checkPktState(&pktInfo->pktState,
                                    ENET_PKTSTATE_MODULE_APP,
                                    ENET_PKTSTATE_APP_WITH_READYQ,
                                    ENET_PKTSTATE_APP_WITH_FREEQ);

            EnetAppUtils_assert(pktInfo->sgList.numScatterSegments == 1);
            rxFrame = (EthFrame *)pktInfo->sgList.list[0].bufPtr;
            *size = pktInfo->sgList.list[0].segmentFilledLen;
            memcpy(frame, rxFrame, *size);
            *rxPort = (uint8_t)pktInfo->rxPortNum;

            /* Release the received packet */
            EnetQueue_enq(&gTimeSyncCpswObj.rxFreeQ, &pktInfo->node);

            EnetAppUtils_validatePacketState(&gTimeSyncCpswObj.rxFreeQ,
                                             ENET_PKTSTATE_APP_WITH_FREEQ,
                                             ENET_PKTSTATE_APP_WITH_DRIVER);

            EnetDma_submitRxPktQ(gTimeSyncCpswObj.hRxFlow,
                                         &gTimeSyncCpswObj.rxFreeQ);
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
        pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncCpswObj.txFreePktInfoQ);
        if (NULL != pktInfo)
        {
            EnetAppUtils_assert(pktInfo->sgList.list[0].segmentAllocLen >= size);
            txFrame = (uint8_t *)pktInfo->sgList.list[0].bufPtr;
            memcpy(txFrame, frame, size);
            pktInfo->sgList.list[0].segmentFilledLen = size;
            pktInfo->appPriv = (void *)timeSyncHandle;
            pktInfo->txPortNum = (Enet_MacPort)ENET_MACPORT_NORM(txPort);
            pktInfo->txPktTc = ENET_TRAFFIC_CLASS_INV;

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
                status = EnetDma_submitTxPktQ(gTimeSyncCpswObj.hTxCh,
                                                      &txSubmitQ);
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
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    CpswCpts_Event lookupEventInArgs;
    CpswCpts_Event lookupEventOutArgs;

    if (timeSyncHandle != NULL)
    {
        lookupEventInArgs.eventType = CPSW_CPTS_EVENTTYPE_HW_TS_PUSH;
        lookupEventInArgs.hwPushNum = gTimeSyncCpswObj.hwPush;
        lookupEventInArgs.portNum = 0U;
        lookupEventInArgs.seqId = 0U;
        lookupEventInArgs.domain  = 0U;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &lookupEventInArgs, &lookupEventOutArgs);
        status = Enet_ioctl(timeSyncHandle->hEnet,
                            timeSyncHandle->coreId,
                            CPSW_CPTS_IOCTL_LOOKUP_EVENT,
                            &prms);
        if (status == ENET_ENOTFOUND)
        {
            lookupEventOutArgs.tsVal = 0U;
        }
        *nanoseconds = (uint32_t)(lookupEventOutArgs.tsVal % (uint64_t)TIMESYNC_SEC_TO_NS);
        *seconds = lookupEventOutArgs.tsVal / (uint64_t)TIMESYNC_SEC_TO_NS;
    }
    else
    {
        status = TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    return status;
}

void TimeSync_recalibratePps(TimeSync_Handle timeSyncHandle)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    CpswCpts_SetFxnGenInArgs setGenFInArgs;
    uint64_t currentTime = 0U;
    uint64_t remainder = 0U;

    if (timeSyncHandle != NULL)
    {
        /*Disable GENF0 used for PPS */
        setGenFInArgs.index  = 0U;
        setGenFInArgs.length = 0U;
        ENET_IOCTL_SET_IN_ARGS(&prms, &setGenFInArgs);
        status = Enet_ioctl(timeSyncHandle->hEnet,
                            timeSyncHandle->coreId,
                            CPSW_CPTS_IOCTL_SET_GENF,
                            &prms);

        /* Not supported is not an error, so set the status
         * to TIMESYNC_OK */
        if (status == ENET_ENOTSUPPORTED)
        {
            status = TIMESYNC_OK;
        }

        EnetAppUtils_assert(status == TIMESYNC_OK);

        /* Get current time */
        ENET_IOCTL_SET_OUT_ARGS(&prms, &currentTime);
        status = Enet_ioctl(timeSyncHandle->hEnet,
                            timeSyncHandle->coreId,
                            ENET_TIMESYNC_IOCTL_GET_CURRENT_TIMESTAMP,
                            &prms);
        EnetAppUtils_assert(status == TIMESYNC_OK);

        /*We need to make sure that PPS aligns with the start of second boundary
         * This is done by finding the distance to second boundary and setting GENF compare
         * to that value. An extra second is added as a margin of safety*/
        remainder = currentTime % (uint64_t)TIMESYNC_SEC_TO_NS;
        currentTime += (TIMESYNC_SEC_TO_NS - remainder) + TIMESYNC_SEC_TO_NS;

        /* Configure GENF compare value and re-enable GENF */
        setGenFInArgs.index   = 0U;
        setGenFInArgs.length  = gTimeSyncCpswObj.timeSyncConfig.protoCfg.ppsConfig.ppsPulseIntervalNs;
        setGenFInArgs.compare = currentTime;
        setGenFInArgs.polarityInv = true;
        setGenFInArgs.ppmVal  = 0U;
        setGenFInArgs.ppmDir  = ENET_TIMESYNC_ADJDIR_INCREASE;
        setGenFInArgs.ppmMode = ENET_TIMESYNC_ADJMODE_DISABLE;

        ENET_IOCTL_SET_IN_ARGS(&prms, &setGenFInArgs);
        status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                            gTimeSyncCpswObj.coreId,
                            CPSW_CPTS_IOCTL_SET_GENF,
                            &prms);

        /* Not supported is not an error, so set the status
         * to TIMESYNC_OK */
        if (status == ENET_ENOTSUPPORTED)
        {
            status = TIMESYNC_OK;
        }

        EnetAppUtils_assert(status == TIMESYNC_OK);
    }

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
    Enet_IoctlPrms prms;

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
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncCpswObj.rxReadyQ);
            while (pktInfo != NULL)
            {
                /* Consume the received packets and release them */
                EnetDma_checkPktState(&pktInfo->pktState,
                                        ENET_PKTSTATE_MODULE_APP,
                                        ENET_PKTSTATE_APP_WITH_READYQ,
                                        ENET_PKTSTATE_APP_WITH_FREEQ);

                EnetQueue_enq(&gTimeSyncCpswObj.rxFreeQ, &pktInfo->node);

                pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&gTimeSyncCpswObj.rxReadyQ);
            }

            EnetAppUtils_validatePacketState(&gTimeSyncCpswObj.rxFreeQ,
                                             ENET_PKTSTATE_APP_WITH_FREEQ,
                                             ENET_PKTSTATE_APP_WITH_DRIVER);

            EnetDma_submitRxPktQ(gTimeSyncCpswObj.hRxFlow,
                                         &gTimeSyncCpswObj.rxFreeQ);

            TimeSync_retrieveTxDonePkts();

            /* Clear Timestamp pools */
            ENET_IOCTL_SET_NO_ARGS(&prms);
            status = Enet_ioctl(timeSyncHandle->hEnet,
                                timeSyncHandle->coreId,
                                ENET_TIMESYNC_IOCTL_RESET,
                                &prms);
            if (status != TIMESYNC_OK)
            {
                EnetAppUtils_print("ENET_TIMESYNC_IOCTL_RESET IOCTL failed: %d\n", status);
            }
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
    /* Nothing to be done for CPSW Ethfw */
}

void TimeSync_setRcf(TimeSync_Handle timeSyncHandle,
                     uint32_t rcfValue)
{
    /* Nothing to be done for CPSW Ethfw */
}

void TimeSync_setPathDelay(TimeSync_Handle timeSyncHandle,
                           uint32_t pathDelay,
                           uint8_t portNum)
{
    /* Nothing to be done for CPSW Ethfw */
}

void TimeSync_writeTsSingleStepSync(TimeSync_Handle timeSyncHandle,
                                    uint8_t portNum)
{
    /* Nothing to be done for CPSW Ethfw */
}

/* ========================================================================== */
/*                          Internal Function Definitions                     */
/* ========================================================================== */

static int32_t TimeSync_openDma(void)
{
    int32_t status = TIMESYNC_OK;
    EnetDma_Handle hDma;
    EnetUdma_OpenRxFlowPrms cpswRxFlowCfg;
    EnetUdma_OpenTxChPrms cpswTxChCfg;

    hDma = Enet_getDmaHandle(gTimeSyncCpswObj.hEnet);
    EnetAppUtils_assert(hDma != NULL);

    /* Open the CPSW TX channel  */
    if (status == TIMESYNC_OK)
    {
        EnetDma_initTxChParams(&cpswTxChCfg);

        cpswTxChCfg.hUdmaDrv = gTimeSyncCpswObj.hUdmaDrv;
        cpswTxChCfg.cbArg = &gTimeSyncCpswObj;
        cpswTxChCfg.notifyCb = TimeSync_txNotifyFxn;

        EnetAppUtils_setCommonTxChPrms(&cpswTxChCfg);

        EnetAppUtils_openTxCh(gTimeSyncCpswObj.hEnet,
                              gTimeSyncCpswObj.coreKey,
                              gTimeSyncCpswObj.coreId,
                              &gTimeSyncCpswObj.txChNum,
                              &gTimeSyncCpswObj.hTxCh,
                              &cpswTxChCfg);

        TimeSync_initTxFreePktQ();

        if (NULL != gTimeSyncCpswObj.hTxCh)
        {
            status = EnetDma_enableTxEvent(gTimeSyncCpswObj.hTxCh);
            if (TIMESYNC_OK != status)
            {
                /* Free the Ch Num if enable event failed */
                EnetAppUtils_freeTxCh(gTimeSyncCpswObj.hEnet,
                                      gTimeSyncCpswObj.coreKey,
                                      gTimeSyncCpswObj.coreId,
                                      gTimeSyncCpswObj.txChNum);
                EnetAppUtils_print("EnetDma_enableTxEvent() failed: %d\n", status);
                status = ENET_EFAIL;
            }
        }
        else
        {
            /* Free the Ch Num if open Tx Ch failed */
            EnetAppUtils_freeTxCh(gTimeSyncCpswObj.hEnet,
                                  gTimeSyncCpswObj.coreKey,
                                  gTimeSyncCpswObj.coreId,
                                  gTimeSyncCpswObj.txChNum);
            EnetAppUtils_print("EnetAppUtils_openTxCh() failed to open: %d\n",
                               status);
            status = ENET_EFAIL;
        }
    }

    /* Open the CPSW RX flow  */
    if (status == TIMESYNC_OK)
    {
        EnetDma_initRxChParams(&cpswRxFlowCfg);
        cpswRxFlowCfg.notifyCb = TimeSync_rxNotifyFxn;
        cpswRxFlowCfg.hUdmaDrv = gTimeSyncCpswObj.hUdmaDrv;
        cpswRxFlowCfg.cbArg = &gTimeSyncCpswObj;

        EnetAppUtils_setCommonRxFlowPrms(&cpswRxFlowCfg);

        status = EnetAppUtils_allocRxFlow(gTimeSyncCpswObj.hEnet,
                                          gTimeSyncCpswObj.coreKey,
                                          gTimeSyncCpswObj.coreId,
                                          &gTimeSyncCpswObj.rxFlowStartIdx,
                                          &gTimeSyncCpswObj.rxFlowIdx);
        if (status == TIMESYNC_OK)
        {
            cpswRxFlowCfg.startIdx = gTimeSyncCpswObj.rxFlowStartIdx;
            cpswRxFlowCfg.flowIdx  = gTimeSyncCpswObj.rxFlowIdx;

            gTimeSyncCpswObj.hRxFlow = EnetDma_openRxCh(hDma, &cpswRxFlowCfg);
            if (NULL == gTimeSyncCpswObj.hRxFlow)
            {
                EnetAppUtils_freeRxFlow(gTimeSyncCpswObj.hEnet,
                                        gTimeSyncCpswObj.coreKey,
                                        gTimeSyncCpswObj.coreId,
                                        gTimeSyncCpswObj.rxFlowIdx);
                EnetAppUtils_print("EnetDma_openRxCh() failed to open: %d\n",
                                   status);
            }
            else
            {
                /* Submit all ready RX buffers to DMA.*/
                TimeSync_initRxReadyPktQ();
            }
        }
        else
        {
            EnetAppUtils_print("EnetAppUtils_allocRxFlow() failed to open: %d\n",
                               status);
        }

        /* Close Tx channel if Rx flow open failed */
        if (status != TIMESYNC_OK)
        {
            status = EnetDma_disableTxEvent(gTimeSyncCpswObj.hTxCh);
            EnetAppUtils_freeTxCh(gTimeSyncCpswObj.hEnet,
                                  gTimeSyncCpswObj.coreKey,
                                  gTimeSyncCpswObj.coreId,
                                  gTimeSyncCpswObj.txChNum);
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
    if (gTimeSyncCpswObj.hRxFlow != NULL)
    {
        status = EnetDma_closeRxCh(gTimeSyncCpswObj.hRxFlow,
                                     &fqPktInfoQ,
                                     &cqPktInfoQ);
        if (status == TIMESYNC_OK)
        {
            EnetAppUtils_freeRxFlow(gTimeSyncCpswObj.hEnet,
                                    gTimeSyncCpswObj.coreKey,
                                    gTimeSyncCpswObj.coreId,
                                    gTimeSyncCpswObj.rxFlowIdx);
            EnetAppUtils_freePktInfoQ(&fqPktInfoQ);
            EnetAppUtils_freePktInfoQ(&cqPktInfoQ);
        }
        else
        {
            EnetAppUtils_print("EnetDma_closeRxCh() failed to open: %d\n",
                               status);
        }

    }

    /* Close TX channel */
    if (gTimeSyncCpswObj.hTxCh != NULL)
    {
        if (status == TIMESYNC_OK)
        {
            EnetQueue_initQ(&fqPktInfoQ);
            EnetQueue_initQ(&cqPktInfoQ);

            EnetAppUtils_closeTxCh(gTimeSyncCpswObj.hEnet,
                                   gTimeSyncCpswObj.coreKey,
                                   gTimeSyncCpswObj.coreId,
                                   &fqPktInfoQ,
                                   &cqPktInfoQ,
                                   gTimeSyncCpswObj.hTxCh,
                                   gTimeSyncCpswObj.txChNum);
            EnetAppUtils_freePktInfoQ(&fqPktInfoQ);
            EnetAppUtils_freePktInfoQ(&cqPktInfoQ);

            EnetAppUtils_freePktInfoQ(&gTimeSyncCpswObj.rxFreeQ);
            EnetAppUtils_freePktInfoQ(&gTimeSyncCpswObj.txFreePktInfoQ);
        }
    }

}

static void TimeSync_initTxFreePktQ(void)
{
    EnetDma_Pkt *pPktInfo;
    uint32_t i;
    uint32_t scatterSegments[1];

    /* Initialize all queues */
    EnetQueue_initQ(&gTimeSyncCpswObj.txFreePktInfoQ);

    scatterSegments[0] = ENET_MEM_LARGE_POOL_PKT_SIZE;
    /* Initialize TX EthPkts and queue them to txFreePktInfoQ */
    for (i = 0U; i < ENET_MEM_NUM_TX_PKTS; i++)
    {
        pPktInfo = EnetMem_allocEthPkt(&gTimeSyncCpswObj,
                                       UDMA_CACHELINE_ALIGNMENT,
                                       ENET_ARRAYSIZE(scatterSegments),
                                       scatterSegments);
        EnetAppUtils_assert(pPktInfo != NULL);
        ENET_UTILS_SET_PKT_APP_STATE(&pPktInfo->pktState, ENET_PKTSTATE_APP_WITH_FREEQ);

        EnetQueue_enq(&gTimeSyncCpswObj.txFreePktInfoQ, &pPktInfo->node);
    }
}

static void TimeSync_initRxReadyPktQ(void)
{
    EnetDma_PktQ rxReadyQ;
    EnetDma_Pkt *pPktInfo;
    int32_t status;
    uint32_t i;
    uint32_t scatterSegments[1];

    EnetQueue_initQ(&gTimeSyncCpswObj.rxFreeQ);
    EnetQueue_initQ(&gTimeSyncCpswObj.rxReadyQ);
    EnetQueue_initQ(&rxReadyQ);

    scatterSegments[0] = ENET_MEM_LARGE_POOL_PKT_SIZE;
    for (i = 0U; i < ENET_MEM_NUM_RX_PKTS; i++)
    {
        pPktInfo = EnetMem_allocEthPkt(&gTimeSyncCpswObj,
                                       UDMA_CACHELINE_ALIGNMENT,
                                       ENET_ARRAYSIZE(scatterSegments),
                                       scatterSegments);
        EnetAppUtils_assert(pPktInfo != NULL);
        ENET_UTILS_SET_PKT_APP_STATE(&pPktInfo->pktState, ENET_PKTSTATE_APP_WITH_FREEQ);
        EnetQueue_enq(&gTimeSyncCpswObj.rxFreeQ, &pPktInfo->node);
    }

    /* Retrieve any CPSW packets which are ready */
    status = EnetDma_retrieveRxPktQ(gTimeSyncCpswObj.hRxFlow, &rxReadyQ);
    EnetAppUtils_assert(status == TIMESYNC_OK);
    /* There should not be any packet with DMA during init */
    EnetAppUtils_assert(EnetQueue_getQCount(&rxReadyQ) == 0U);

    EnetAppUtils_validatePacketState(&gTimeSyncCpswObj.rxFreeQ,
                                     ENET_PKTSTATE_APP_WITH_FREEQ,
                                     ENET_PKTSTATE_APP_WITH_DRIVER);

    EnetDma_submitRxPktQ(gTimeSyncCpswObj.hRxFlow,
                                 &gTimeSyncCpswObj.rxFreeQ);

    /* Assert here as during init no. of DMA descriptors should be equal to
     * no. of free Ethernet buffers available with app */
    EnetAppUtils_assert(0U == EnetQueue_getQCount(&gTimeSyncCpswObj.rxFreeQ));
}

static int32_t TimeSync_setCpswAleClassifier(void)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    CpswAle_SetPolicerEntryOutArgs setPolicerEntryOutArgs;
    CpswAle_SetPolicerEntryInArgs setPolicerEntryInArgs;

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_IEEE_802_3)
    {
        memset(&setPolicerEntryInArgs, 0, sizeof (setPolicerEntryInArgs));
        setPolicerEntryInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_MACDST;
        setPolicerEntryInArgs.policerMatch.dstMacAddrInfo.portNum = 0U;
        setPolicerEntryInArgs.policerMatch.dstMacAddrInfo.addr.vlanId = 0U;
        memcpy(&setPolicerEntryInArgs.policerMatch.dstMacAddrInfo.addr.addr[0U],
               &peerDlyMsgMAC[0U],
               ENET_MAC_ADDR_LEN);

        setPolicerEntryInArgs.threadIdEn = true;
        setPolicerEntryInArgs.threadId = gTimeSyncCpswObj.rxFlowIdx;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &setPolicerEntryInArgs, &setPolicerEntryOutArgs);
        status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                            gTimeSyncCpswObj.coreId,
                            CPSW_ALE_IOCTL_SET_POLICER,
                            &prms);
        if (status != TIMESYNC_OK)
        {
            EnetAppUtils_print("TimeSync_setCpswAleClassifier() failed CPSW_ALE_IOCTL_SET_POLICER: %d\n",
                               status);
        }

        memset(&setPolicerEntryInArgs, 0, sizeof (setPolicerEntryInArgs));
        setPolicerEntryInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_MACDST;
        setPolicerEntryInArgs.policerMatch.dstMacAddrInfo.portNum = 0U;
        setPolicerEntryInArgs.policerMatch.dstMacAddrInfo.addr.vlanId = 0U;
        memcpy(&setPolicerEntryInArgs.policerMatch.dstMacAddrInfo.addr.addr[0U],
               &nonPeerDlyMsgMAC[0U],
               ENET_MAC_ADDR_LEN);

        setPolicerEntryInArgs.threadIdEn = true;
        setPolicerEntryInArgs.threadId = gTimeSyncCpswObj.rxFlowIdx;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &setPolicerEntryInArgs, &setPolicerEntryOutArgs);
        status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                            gTimeSyncCpswObj.coreId,
                            CPSW_ALE_IOCTL_SET_POLICER,
                            &prms);
        if (status != TIMESYNC_OK)
        {
            EnetAppUtils_print("TimeSync_setCpswAleClassifier() failed CPSW_ALE_IOCTL_SET_POLICER: %d\n",
                               status);
        }
    }
    else if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV4)
    {
        memset(&setPolicerEntryInArgs, 0, sizeof (setPolicerEntryInArgs));
        setPolicerEntryInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_IPDST;
        setPolicerEntryInArgs.policerMatch.dstIpInfo.ipAddrType = CPSW_ALE_IPADDR_CLASSIFIER_IPV4;
        memcpy(&setPolicerEntryInArgs.policerMatch.dstIpInfo.ipv4Info.ipv4Addr[0U],
               &peerDlyMsgIpv4[0U],
               ENET_IPv4_ADDR_LEN);
        setPolicerEntryInArgs.policerMatch.dstIpInfo.ipv4Info.numLSBIgnoreBits = 0U;

        setPolicerEntryInArgs.threadIdEn = true;
        setPolicerEntryInArgs.threadId = gTimeSyncCpswObj.rxFlowIdx;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &setPolicerEntryInArgs, &setPolicerEntryOutArgs);
        status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                            gTimeSyncCpswObj.coreId,
                            CPSW_ALE_IOCTL_SET_POLICER,
                            &prms);
        if (status != TIMESYNC_OK)
        {
            EnetAppUtils_print(
                               "TimeSync_setCpswAleClassifier() failed CPSW_ALE_IOCTL_SET_POLICER: %d\n", status);
        }

        memset(&setPolicerEntryInArgs, 0, sizeof (setPolicerEntryInArgs));
        setPolicerEntryInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_IPDST;
        setPolicerEntryInArgs.policerMatch.dstIpInfo.ipAddrType = CPSW_ALE_IPADDR_CLASSIFIER_IPV4;
        memcpy(&setPolicerEntryInArgs.policerMatch.dstIpInfo.ipv4Info.ipv4Addr[0U],
               &nonPeerDlyMsgIpv4[0U],
               ENET_IPv4_ADDR_LEN);
        setPolicerEntryInArgs.policerMatch.dstIpInfo.ipv4Info.numLSBIgnoreBits = 0U;

        setPolicerEntryInArgs.threadIdEn = true;
        setPolicerEntryInArgs.threadId = gTimeSyncCpswObj.rxFlowIdx;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &setPolicerEntryInArgs, &setPolicerEntryOutArgs);
        status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                            gTimeSyncCpswObj.coreId,
                            CPSW_ALE_IOCTL_SET_POLICER,
                            &prms);
        if (status != TIMESYNC_OK)
        {
            EnetAppUtils_print(
                               "TimeSync_setCpswAleClassifier() failed CPSW_ALE_IOCTL_SET_POLICER: %d\n", status);
        }
    }
    else
    {
        status = TIMESYNC_UNSUPPORTED_FORMAT;
    }

    return status;
}

static int32_t TimeSync_setMacPortConfig(void)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    CpswMacPort_EnableTsEventInArgs enableTsEventInArgs;
    uint8_t i = 0U;
    uint32_t maxMacPorts = 0U;

    maxMacPorts = Enet_getMacPortMax(gTimeSyncCpswObj.enetType, gTimeSyncCpswObj.instId);
    TimeSync_setPortTsEventPrms(&enableTsEventInArgs.tsEventCfg);

    for (i = 0U; i < maxMacPorts; i++)
    {
        if (TIMESYNC_IS_BIT_SET(gTimeSyncCpswObj.timeSyncConfig.protoCfg.portMask, i))
        {
            enableTsEventInArgs.macPort = (Enet_MacPort)(ENET_MACPORT_NORM(i));
            ENET_IOCTL_SET_IN_ARGS(&prms, &enableTsEventInArgs);
            status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                                gTimeSyncCpswObj.coreId,
                                CPSW_MACPORT_IOCTL_ENABLE_CPTS_EVENT,
                                &prms);
            EnetAppUtils_assert(status == TIMESYNC_OK);
        }
    }

    return status;
}

static void TimeSync_setPortTsEventPrms(CpswMacPort_TsEventCfg *tsPortEventCfg)
{
    tsPortEventCfg->commonPortIpCfg.ttlNonzeroEn = true;
    tsPortEventCfg->commonPortIpCfg.tsIp107En = false;
    tsPortEventCfg->commonPortIpCfg.tsIp129En = false;
    tsPortEventCfg->commonPortIpCfg.tsIp130En = false;
    tsPortEventCfg->commonPortIpCfg.tsIp131En = false;
    tsPortEventCfg->commonPortIpCfg.tsIp132En = false;
    tsPortEventCfg->commonPortIpCfg.tsPort319En = true;
    tsPortEventCfg->commonPortIpCfg.tsPort320En = true;
    tsPortEventCfg->commonPortIpCfg.unicastEn = false;
    tsPortEventCfg->domainOffset = 4U;
    tsPortEventCfg->ltype2En = false;
    tsPortEventCfg->rxAnnexDEn = true;
    tsPortEventCfg->rxAnnexEEn = true;
    tsPortEventCfg->rxAnnexFEn = true;
    tsPortEventCfg->txAnnexDEn = true;
    tsPortEventCfg->txAnnexEEn = true;
    tsPortEventCfg->txAnnexFEn = true;
    tsPortEventCfg->txHostTsEn = true;
    tsPortEventCfg->mcastType = 0U;
    tsPortEventCfg->messageType = 0xFFFFU;
    tsPortEventCfg->seqIdOffset = 30U;
    tsPortEventCfg->rxVlanType  = ENET_MACPORT_VLAN_TYPE_NONE;
    tsPortEventCfg->txVlanType  = ENET_MACPORT_VLAN_TYPE_NONE;
    tsPortEventCfg->vlanLType1  = 0U;
    tsPortEventCfg->vlanLType2  = 0U;

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_SINGLE_TAG)
    {
        tsPortEventCfg->rxVlanType = ENET_MACPORT_VLAN_TYPE_SINGLE_TAG;
        tsPortEventCfg->txVlanType = ENET_MACPORT_VLAN_TYPE_SINGLE_TAG;
        tsPortEventCfg->vlanLType1 = gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.iVlanTag;
        tsPortEventCfg->vlanLType2 = 0U;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_DOUBLE_TAG)
    {
        tsPortEventCfg->rxVlanType = ENET_MACPORT_VLAN_TYPE_STACKED_TAGS;
        tsPortEventCfg->txVlanType = ENET_MACPORT_VLAN_TYPE_STACKED_TAGS;
        tsPortEventCfg->vlanLType1 = gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.iVlanTag;
        tsPortEventCfg->vlanLType2 = gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.oVlanTag;
    }
}

static uint32_t TimeSync_retrieveTxDonePkts(void)
{
    EnetDma_PktQ txFreeQ;
    EnetDma_Pkt *pktInfo;
    int32_t status;
    uint32_t txFreeQCnt = 0U;

    EnetQueue_initQ(&txFreeQ);

    /* Retrieve any CPSW packets that may be free now */
    status = EnetDma_retrieveTxPktQ(gTimeSyncCpswObj.hTxCh, &txFreeQ);
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

            EnetQueue_enq(&gTimeSyncCpswObj.txFreePktInfoQ, &pktInfo->node);
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&txFreeQ);
        }
    }
    else
    {
        EnetAppUtils_print("EnetDma_retrieveTxPktQ() failed to retrieve pkts: %d\n",
                           status);
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

    /* Retrieve any CPSW packets which are ready */
    status = EnetDma_retrieveRxPktQ(gTimeSyncCpswObj.hRxFlow, &rxReadyQ);
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

            EnetQueue_enq(&gTimeSyncCpswObj.rxReadyQ, &pktInfo->node);
            pktInfo = (EnetDma_Pkt *)EnetQueue_deq(&rxReadyQ);
        }
    }
    else
    {
        EnetAppUtils_print("TimeSync_receiveRxReadyPkts() failed to retrieve pkts: %d\n",
                           status);
    }

    return rxReadyCnt;
}

static void TimeSync_getMsgId(uint8_t *msgId,
                              uint8_t *frame)
{
    uint32_t offset = TIMESYNC_PTP_MSG_ID_OFFSET;

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV4)
    {
        offset += TIMESYNC_ANNEX_D_ANNEX_F_DIFF;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV6)
    {
        offset += TIMESYNC_ANNEX_E_ANNEX_F_DIFF;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_SINGLE_TAG)
    {
        offset += TIMESYNC_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_DOUBLE_TAG)
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

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV4)
    {
        offset += TIMESYNC_ANNEX_D_ANNEX_F_DIFF;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.protocol == TIMESYNC_PROT_UDP_IPV6)
    {
        offset += TIMESYNC_ANNEX_E_ANNEX_F_DIFF;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_SINGLE_TAG)
    {
        offset += TIMESYNC_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    if (gTimeSyncCpswObj.timeSyncConfig.protoCfg.vlanCfg.vlanType == TIMESYNC_VLAN_TYPE_DOUBLE_TAG)
    {
        offset += TIMESYNC_DOUBLE_TAG_VLAN_HDR_SIZE;
    }

    *seqId = *(uint16_t *)(frame + offset);
    *seqId = Enet_ntohs(*seqId);
}

static int32_t TimeSync_configPps(Enet_Type enetType, uint32_t instId)
{
    int32_t status = TIMESYNC_OK;
    Enet_IoctlPrms prms;
    CpswCpts_RegisterHwPushCbInArgs hwPushCbInArgs;
    CpswCpts_SetFxnGenInArgs setGenFInArgs;
    uint64_t tsVal = 0U;
    uint32_t tsrIn = 0U;
    uint32_t tsrOut = 0U;

    /* Configure Time Sync Router to route GENF0 signal to hardware push 1 */
#if defined(SOC_AM65XX)
    tsrIn = 12U;  /* SYNCEVENT_INTRTRIN_12 (MCU_CPSW_GENF0_EVT) */
    tsrOut = 24U; /* SYNCEVT_RTR_SYNC24_EVT (MPU_CPSW0_CPTS_HW3_PUSH) */

    /* Explicit register call as AM65xx doesn't have TimeSync router inputs/output macros */
    CSL_REG32_WR(CSL_TIMESYNC_INTRTR0_INTR_ROUTER_CFG_BASE + 0x4U + (0x4U * tsrOut), tsrIn);
#else
    if ((enetType == ENET_CPSW_2G) && (instId == 0U))
    {
        tsrIn  = CSLR_TIMESYNC_INTRTR0_IN_MCU_CPSW0_CPTS_GENF0_0;
        tsrOut = ENET_TIMESYNCRTR_OUT_MCU_CPSW0_CPTS_HW3_PUSH;
    }
#if defined(SOC_J721S2) || defined(SOC_J784S4)
    else if ((enetType == ENET_CPSW_2G) && (instId == 1U))
    {
        tsrIn  = CSLR_TIMESYNC_INTRTR0_IN_CPSW1_CPTS_GENF0_0;
        tsrOut = ENET_TIMESYNCRTR_OUT_CPSW1_CPTS_HW3_PUSH;
    }
#endif
#if defined(SOC_J721E) || defined(SOC_J7200)
    else if ((enetType == ENET_CPSW_5G) || (enetType == ENET_CPSW_9G))
    {
        tsrIn  = CSLR_TIMESYNC_INTRTR0_IN_CPSW0_CPTS_GENF0_0;
        tsrOut = ENET_TIMESYNCRTR_OUT_CPSW0_CPTS_HW1_PUSH;
    }
#elif defined(SOC_J784S4)
    else if (enetType == ENET_CPSW_9G)
    {
        tsrIn  = CSLR_TIMESYNC_INTRTR0_IN_CPSW_9XUSSM0_CPTS_GENF0_0;
        tsrOut = ENET_TIMESYNCRTR_OUT_CPSW0_CPTS_HW1_PUSH;
    }
#endif
    else
    {
        EnetAppUtils_assert(false);
    }

    status = EnetAppUtils_setTimeSyncRouter(enetType, instId, tsrIn, tsrOut);
    EnetAppUtils_assert(status == TIMESYNC_OK);
#endif

    /* Register hardware push 1 callback */
    hwPushCbInArgs.hwPushNum = gTimeSyncCpswObj.hwPush;
    hwPushCbInArgs.hwPushNotifyCb = TimeSync_ppsHwPushNotifyFxn;
    hwPushCbInArgs.hwPushNotifyCbArg = (void *)&gTimeSyncCpswObj;
    ENET_IOCTL_SET_IN_ARGS(&prms, &hwPushCbInArgs);
    status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                        gTimeSyncCpswObj.coreId,
                        CPSW_CPTS_IOCTL_REGISTER_HWPUSH_CALLBACK,
                        &prms);
    EnetAppUtils_assert(status == TIMESYNC_OK);

    /* Reset CPTS timer to zero, to ensure GENF compare value hits on first run */
    tsVal = 0U;
    ENET_IOCTL_SET_IN_ARGS(&prms, &tsVal);
    status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                        gTimeSyncCpswObj.coreId,
                        ENET_TIMESYNC_IOCTL_SET_TIMESTAMP,
                        &prms);
    EnetAppUtils_assert(status == TIMESYNC_OK);

    /* Configure GENF0 to generate pulse signal */
    setGenFInArgs.index  = 0U;
    setGenFInArgs.length = gTimeSyncCpswObj.timeSyncConfig.protoCfg.ppsConfig.ppsPulseIntervalNs;

    /* Add one second to compare value to ensure GENF compare happens
     *  and PPS gets generated then after */
    setGenFInArgs.compare = gTimeSyncCpswObj.timeSyncConfig.protoCfg.ppsConfig.ppsPulseIntervalNs +
                            TIMESYNC_SEC_TO_NS;
    setGenFInArgs.polarityInv = true;
    setGenFInArgs.ppmVal  = 0U;
    setGenFInArgs.ppmDir  = ENET_TIMESYNC_ADJDIR_INCREASE;
    setGenFInArgs.ppmMode = ENET_TIMESYNC_ADJMODE_DISABLE;

    ENET_IOCTL_SET_IN_ARGS(&prms, &setGenFInArgs);
    status = Enet_ioctl(gTimeSyncCpswObj.hEnet,
                        gTimeSyncCpswObj.coreId,
                        CPSW_CPTS_IOCTL_SET_GENF,
                        &prms);
    EnetAppUtils_assert(status == TIMESYNC_OK);

    return status;
}
