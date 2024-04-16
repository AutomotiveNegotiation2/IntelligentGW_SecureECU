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
 * \file timeSync_ptp.c
 *
 * \brief This file contains the implementation of PTP stack functions.
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

#include <math.h>

#include <ti/drv/enet/examples/timesync/timeSync.h>

#include <ti/drv/enet/examples/timesync/protocol/ptp/include/timeSync_ptp.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_ptp_priv.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_ptp_init_priv.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_ptp_osal_priv.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/src/timeSync_tools.h>

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

static void TimeSyncPtp_setTimeSyncConfig(TimeSyncPtp_Handle hTimeSyncPtp,
                                          TimeSync_Config *pTimeSyncConfig);

static void TimeSyncPtp_stripVlanTag(TimeSyncPtp_Handle hTimeSyncPtp,
                                     uint8_t *pktBuffer,
                                     uint32_t *size);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

TimeSyncPtp_Obj gTimeSyncPtpObj;

/**PTP MAC ID for comparison*/
uint8_t timeSyncMAC[6] = {0x1, 0x1b, 0x19, 0x0, 0x0, 0x0};
uint8_t linkLocalMAC[6] = {0x1, 0x80, 0xc2, 0x0, 0x0, 0xE};

TimeSyncPtp_TxNotifyMsg txNotifyMsg;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void TimeSyncPtp_setDefaultPtpConfig(TimeSyncPtp_Config *ptpConfig)
{
    int8_t i = 0;

    ptpConfig->nwDrvHandle = NULL;

    /* SoC configuration */
    ptpConfig->socConfig.socVersion = TIMESYNC_SOC_UNKNOWN;
    ptpConfig->socConfig.ipVersion  = TIMESYNC_IP_VER_UNKNOWN;
    ptpConfig->socConfig.instId     = 0U;

    /* VLAN configuration */
    ptpConfig->vlanCfg.vlanType = TIMESYNC_VLAN_TYPE_NONE;
    ptpConfig->vlanCfg.iVlanTag = 0U;
    ptpConfig->vlanCfg.oVlanTag = 0U;

    /* Port configuration */
    ptpConfig->portMask = 0U;

    ptpConfig->hsrEnabled = FALSE;
    ptpConfig->ll_has_hsrTag = FALSE;

    /*Configure PTP. These variables must be configured before doing anything else*/
    ptpConfig->deviceMode = TIMESYNC_OC_AND_TC;
    ptpConfig->type = TIMESYNC_PTP_DELAY_P2P;
    ptpConfig->protocol = TIMESYNC_PROT_IEEE_802_3;
    ptpConfig->frameOffset = 0U;
    ptpConfig->processToDSync2PPS = FALSE;
    ptpConfig->tickPeriod = 1000U;
    ptpConfig->domainNumber[0] = 0U;
    ptpConfig->domainNumber[1] = 0U;

    ptpConfig->logAnnounceRcptTimeoutInterval = TIMESYNC_PTP_DEFAULT_ANNOUNCE_TIMEOUT_LOG_INTERVAL;
    ptpConfig->logAnnounceSendInterval = TIMESYNC_PTP_DEFAULT_ANNOUNCE_SEND_LOG_INTERVAL;
    ptpConfig->logPDelReqPktInterval = TIMESYNC_PTP_DEFAULT_PDELAY_REQ_LOG_INTERVAL;
    ptpConfig->logSyncInterval = TIMESYNC_PTP_DEFAULT_SYNC_SEND_LOG_INTERVAL;

    /*No asymmetry*/
    for (i = 0U; i < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; i++)
    {
        ptpConfig->asymmetryCorrection[i] = 0U;
    }

    /*3 frames sent in a burst*/
    ptpConfig->pdelayBurstNumPkts = 3U;
    /*gap between each frame is 100ms*/
    ptpConfig->pdelayBurstInterval = 200U;
    /*1 second value*/
    ptpConfig->ppsPulseIntervalNs = 1000000000U;
    /*Register callback*/
    ptpConfig->syncLossNotifyFxn = NULL;

    /*Configure Master params*/
    ptpConfig->isMaster = 0;
    ptpConfig->masterParams.priority1 = TIMESYNC_PTP_DEFAULT_PRIO_1;
    ptpConfig->masterParams.priority2 = TIMESYNC_PTP_DEFAULT_PRIO_2;
    /*greater than 10s */
    ptpConfig->masterParams.clockAccuracy = TIMESYNC_PTP_DEFAULT_CLOCK_ACCURACY;
    ptpConfig->masterParams.clockClass = TIMESYNC_PTP_DEFAULT_CLOCK_CLASS;
    ptpConfig->masterParams.clockVariance = TIMESYNC_PTP_DEFAULT_CLOCK_VARIANCE;
    ptpConfig->masterParams.stepRemoved = TIMESYNC_PTP_DEFAULT_STEPS_REMOVED;
    ptpConfig->masterParams.UTCOffset = TIMESYNC_PTP_DEFAULT_UTC_OFFSET;
    /*Internal oscillator*/
    ptpConfig->masterParams.timeSource = TIMESYNC_PTP_DEFAULT_TIME_SOURCE;

    ptpConfig->masterParams.ptpFlags[TIMESYNC_PTP_TIMESCALE_INDEX] = 1U;
    ptpConfig->masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX]  = 1U;
}

TimeSyncPtp_Handle TimeSyncPtp_init(TimeSyncPtp_Config *ptpConfig)
{
    /*Timer initialization variables*/
    int32_t status = TIMESYNC_OK;
    TimeSyncPtp_Handle hTimeSyncPtp = NULL;

    if (ptpConfig != NULL)
    {
        if ((TIMESYNC_PROT_UDP_IPV4 == ptpConfig->protocol) &&
            (TIMESYNC_PTP_DELAY_P2P == ptpConfig->type))
        {
            status = TIMESYNC_UNSUPPORTED_FORMAT;
        }

        if ((TIMESYNC_PROT_IEEE_802_3 == ptpConfig->protocol) &&
            (TIMESYNC_PTP_DELAY_E2E == ptpConfig->type))
        {
            status = TIMESYNC_UNSUPPORTED_FORMAT;
        }

        if (status == TIMESYNC_OK)
        {
            hTimeSyncPtp = &gTimeSyncPtpObj;
            memset(hTimeSyncPtp, 0U, sizeof(TimeSyncPtp_Obj));
            hTimeSyncPtp->ptpConfig = *(ptpConfig);

            /*Allocate Rx and Tx packet buffers*/
            TimeSyncPtp_allocPktBuffer(hTimeSyncPtp);

            TimeSyncPtp_setDefaultValue(hTimeSyncPtp);

            TimeSyncPtp_setTimeSyncConfig(hTimeSyncPtp,
                                          &hTimeSyncPtp->timeSyncCfg);
            hTimeSyncPtp->timeSyncHandle = TimeSync_open(&hTimeSyncPtp->timeSyncCfg);
            if (hTimeSyncPtp->timeSyncHandle == NULL)
            {
                status = TIMESYNC_UNABLE_TO_INIT_HAL;
            }

            if (status == TIMESYNC_OK)
            {
                /*Create PTP Interrupts and Tasks*/
                status = TimeSyncPtp_createPtpTasks(hTimeSyncPtp);
            }
        }
    }
    else
    {
        status = TIMESYNC_PARAM_INVALID;
    }

    /* Reset PTP object and close HAL if initialization failed */
    if (status != TIMESYNC_OK)
    {
        if ((hTimeSyncPtp != NULL) &&
            (hTimeSyncPtp->timeSyncHandle != NULL))
        {
            TimeSync_close(hTimeSyncPtp->timeSyncHandle);
        }

        memset(&gTimeSyncPtpObj, 0U, sizeof(TimeSyncPtp_Obj));
    }

    return ((status == TIMESYNC_OK) ? (&gTimeSyncPtpObj) : NULL);
}

void TimeSyncPtp_processTxNotify(void *arg,
                                 uint8_t portNum,
                                 uint8_t frameType,
                                 uint16_t seqId)
{
    if (arg != NULL)
    {
        TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)arg;
        if (hTimeSyncPtp->pktTxSemHandle != NULL)
        {
            txNotifyMsg.portNum   = portNum;
            txNotifyMsg.frameType = frameType;
            txNotifyMsg.seqId     = seqId;
            SemaphoreP_post(hTimeSyncPtp->pktTxSemHandle);
        }
    }
}

void TimeSyncPtp_processTxNotifyTask(void *arg0, 
                                     void *arg1)
{
    int32_t status = TIMESYNC_OK;
    uint8_t portNum = 0U;
    uint8_t frameType = 0U;
    uint16_t seqId = 0U;
    uint32_t nanoseconds = 0;
    uint64_t seconds = 0;
    TimeSyncPtp_Handle hTimeSyncPtp = NULL;
    volatile bool taskRunFlag = true;

    if (arg0 != NULL)
    {
        hTimeSyncPtp = (TimeSyncPtp_Handle)arg0;
        if (hTimeSyncPtp->timeSyncHandle != NULL)
        {
            while (taskRunFlag == true)
            {
                SemaphoreP_pend(hTimeSyncPtp->pktTxSemHandle, SemaphoreP_WAIT_FOREVER);

                portNum   = txNotifyMsg.portNum;
                frameType = txNotifyMsg.frameType;
                seqId     = txNotifyMsg.seqId;

                /*sync frame*/
                if (frameType == TIMESYNC_SYNC_FRAME)
                {
                    status = TimeSync_getTxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                                     TIMESYNC_SYNC_FRAME,
                                                     portNum,
                                                     seqId,
                                                     &nanoseconds,
                                                     &seconds);
                    if (status == TIMESYNC_OK)
                    {
                        hTimeSyncPtp->syncParam[portNum].txTsSec = seconds;
                        hTimeSyncPtp->syncParam[portNum].txTs = nanoseconds;

                        /*If master then post event to send out follow up frame*/
                        if (((hTimeSyncPtp->ptpConfig.isMaster) ||
                             (hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_BOUNDARY_CLOCK)) &&
                            (hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX]))
                        {
                            EventP_post(hTimeSyncPtp->txTSAvailableEvtHandle[portNum],
                                        hTimeSyncPtp->eventIdSync);
                        }
                    }
                }

                /*delay request frame*/
                if (frameType == TIMESYNC_DELAY_REQ_FRAME || frameType == TIMESYNC_PDELAY_REQ_FRAME)
                {
                    if (hTimeSyncPtp->ptpConfig.type == TIMESYNC_PTP_DELAY_P2P)
                    {
                        status = TimeSync_getTxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                                         TIMESYNC_PDELAY_REQ_FRAME,
                                                         portNum,
                                                         seqId,
                                                         &nanoseconds,
                                                         &seconds);
                        if (status == TIMESYNC_OK)
                        {
                            hTimeSyncPtp->pDelayParams[portNum].T1Sec = seconds;
                            /*Copy nanoseconds*/
                            hTimeSyncPtp->pDelayParams[portNum].T1Nsec = nanoseconds;
                        }
                    }
                    else
                    {
                        status = TimeSync_getTxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                                         TIMESYNC_DELAY_REQ_FRAME,
                                                         portNum,
                                                         seqId,
                                                         &nanoseconds,
                                                         &seconds);
                        if (status == TIMESYNC_OK)
                        {
                            hTimeSyncPtp->delayParams.delReqTxTsNS  = nanoseconds;
                            hTimeSyncPtp->delayParams.delReqTxTsSec = seconds;
                        }
                    }
                }

                /*Pdelay response frame*/
                if (frameType == TIMESYNC_PDELAY_RESP_FRAME)
                {
                    EventP_post(hTimeSyncPtp->txTSAvailableEvtHandle[portNum],
                                hTimeSyncPtp->eventIdPdelayResp);
                }
            }
        }
    }
}

void TimeSyncPtp_processRxNotify(void *arg)
{
    if (arg != NULL)
    {
        TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)arg;
        if (hTimeSyncPtp->pktRxSemHandle != NULL)
        {
            SemaphoreP_post(hTimeSyncPtp->pktRxSemHandle);
        }
    }
}

void TimeSyncPtp_processRxNotifyTask(void *arg0, 
                                     void *arg1)
{
    uint32_t size  = 0;
    uint8_t rxPort = 0;
    uint8_t *dstMacId;
    uint8_t rxFrame[TIMESYNC_PTP_RX_MAX_MTU];
    TimeSyncPtp_Handle hTimeSyncPtp = NULL;
    volatile bool taskRunFlag = true;
    int32_t status;

    if (arg0 != NULL)
    {
        hTimeSyncPtp = (TimeSyncPtp_Handle)arg0;
        if (hTimeSyncPtp->timeSyncHandle != NULL)
        {
            while (taskRunFlag == true)
            {
                SemaphoreP_pend(hTimeSyncPtp->pktRxSemHandle, SemaphoreP_WAIT_FOREVER);

                do
                {
                    status = TimeSync_getPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                  &rxFrame[0U],
                                                  &size,
                                                  &rxPort);
                    if (status == TIMESYNC_OK)
                    {
                        dstMacId = rxFrame;

                        if (TIMESYNC_COMPARE_MAC(dstMacId, timeSyncMAC))
                        {
                            TimeSyncPtp_processPtpFrame(hTimeSyncPtp, rxFrame, rxPort, size, 0);
                        }
                        else if (TIMESYNC_COMPARE_MAC(dstMacId, linkLocalMAC))
                        {
                            TimeSyncPtp_processPtpFrame(hTimeSyncPtp, rxFrame, rxPort, size, 1);
                        }
                    }
                } while (status == TIMESYNC_OK);
            }
        }
    }
}

void TimeSyncPtp_doFirstAdjustment(TimeSyncPtp_Handle hTimeSyncPtp,
                                   uint8_t portNum)
{
    uint64_t doubleWord  = 0U;
    uint64_t syncRxTime  = 0U;
    uint64_t currentTime = 0U;
    uint32_t nanoSeconds = 0U;
    uint64_t seconds = 0U;
    uint64_t timeElapsed = 0U;

    /*Get origin time stamp in 64 bit format*/
    doubleWord = hTimeSyncPtp->syncParam[portNum].originTsSec *
                 (uint64_t)TIMESYNC_SEC_TO_NS +
                 (uint64_t)hTimeSyncPtp->syncParam[portNum].originTsNs;

    /*Now calculate time elapsed since sync was received*/
    syncRxTime = hTimeSyncPtp->syncParam[portNum].rxTsSec *
                 (uint64_t)TIMESYNC_SEC_TO_NS +
                 hTimeSyncPtp->syncParam[portNum].rxTs;

    TimeSync_getCurrentTime(hTimeSyncPtp->timeSyncHandle,
                            &nanoSeconds,
                            &seconds);
    currentTime = seconds * (uint64_t)TIMESYNC_SEC_TO_NS + nanoSeconds;

    timeElapsed = currentTime - syncRxTime;

    /*Add correction field and peer delay*/
    doubleWord += (timeElapsed +
                   hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] +
                   hTimeSyncPtp->syncParam[portNum].correctionField);

    nanoSeconds = (uint32_t)(doubleWord % (uint64_t)TIMESYNC_SEC_TO_NS);
    seconds = doubleWord / (uint64_t)TIMESYNC_SEC_TO_NS;

    /* Set adjusted clock time to timer */
    TimeSync_setClockTime(hTimeSyncPtp->timeSyncHandle,
                          nanoSeconds,
                          seconds);

    /* Recalibrate PPS compare value after first adjustment is done */
    if (hTimeSyncPtp->ptpConfig.processToDSync2PPS)
    {
        TimeSync_recalibratePps(hTimeSyncPtp->timeSyncHandle);
    }

}

void TimeSyncPtp_getTxTs(TimeSyncPtp_Handle hTimeSyncPtp,
                         uint8_t portNum,
                         TimeSync_FrameType frameType)
{
    uint8_t *ptpFlwUpPacket = NULL;
    uint8_t *ptpPDelayResFlwUpPacket = NULL;
    uint32_t nanoseconds = 0U;
    uint64_t seconds = 0U;
    uint8_t offset = 0U;
    int32_t retVal = TIMESYNC_OK;

    offset = hTimeSyncPtp->ptpConfig.frameOffset;

    /*This gets called only in case of 2-step master and forced 2-step slave*/
    /*Sync frame*/
    if (TIMESYNC_SYNC_FRAME == frameType)
    {
        ptpFlwUpPacket = hTimeSyncPtp->timeSyncBuff.followUpTxBuf[portNum];

        /*Write seconds into packet*/
        TimeSync_convEndianess(&(hTimeSyncPtp->syncParam[portNum].txTsSec),
                               ptpFlwUpPacket + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                               6);
        /*Write nanoseconds into packet*/
        TimeSync_convEndianess(&(hTimeSyncPtp->syncParam[portNum].txTs),
                               ptpFlwUpPacket +
                               TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                               4);

        /*Add Source Port ID*/
        TimeSync_addHalfWord(ptpFlwUpPacket + TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset,
                             (portNum + 1));

        retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                       ptpFlwUpPacket,
                                       hTimeSyncPtp->timeSyncBuff.flwUpBufSize,
                                       portNum);

        /* If send frame failed exit out of this function */
        if (retVal != TIMESYNC_OK)
        {
            return;
        }
    }

    /*Pdelay response*/
    if (TIMESYNC_DELAY_RESP_FRAME == frameType)
    {
        ptpPDelayResFlwUpPacket = hTimeSyncPtp->timeSyncBuff.pdelayResFlwUpTxBuf[portNum];

        retVal = TimeSync_getTxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                         TIMESYNC_PDELAY_RESP_FRAME,
                                         portNum,
                                         hTimeSyncPtp->tsRunTimeVar.rxPDelReqSequenceID[portNum],
                                         &nanoseconds,
                                         &seconds);
        if (retVal == TIMESYNC_OK)
        {
            /*Encode actual Tx time in Pdelay response frame and send*/
            TimeSync_convEndianess(&seconds,
                                   ptpPDelayResFlwUpPacket + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                                   6);
            TimeSync_convEndianess(&nanoseconds,
                                   ptpPDelayResFlwUpPacket + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                                   4);

            retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                           ptpPDelayResFlwUpPacket,
                                           TIMESYNC_PTP_PDELAY_BUF_SIZE,
                                           portNum);

            /* If send frame failed exit out of this function */
            if (retVal != TIMESYNC_OK)
            {
                return;
            }
        }
    }
}

void TimeSyncPtp_lineDelayCalc(TimeSyncPtp_Handle hTimeSyncPtp)
{
    /*The formula for calculation is
     * Mean Path Delay = (Master Delay - Slave Delay - Correction Path)/2.
     * Correction Path = Correction Path of (Delay Req + Sync + Follow Up(if present)*/

    /*Slave Delay = Tx timestamp of Delay Req packet - Rcv Timestamp of Sync Packet
     * Master Delay = Rcv Timestamp of Delay Resp - Precise origin timestamp of Follow Up Packet
     */

    uint64_t correctionField = 0, slaveDelay = 0, masterDelay = 0;
    uint64_t doubleWord = 0;
    uint8_t syncPortNum = hTimeSyncPtp->tsRunTimeVar.syncPortNum;

    /*find total correction*/
    correctionField = hTimeSyncPtp->syncParam[syncPortNum].correctionField +
                      hTimeSyncPtp->delayParams.correctionField;

    /*slave delay calculation*/
    slaveDelay = (hTimeSyncPtp->syncParam[syncPortNum].rxTsSec *
                  (uint64_t)TIMESYNC_SEC_TO_NS) +
                 (uint64_t)hTimeSyncPtp->syncParam[syncPortNum].rxTs;

    doubleWord = (hTimeSyncPtp->delayParams.delReqTxTsSec * (uint64_t)TIMESYNC_SEC_TO_NS +
                  (uint64_t)hTimeSyncPtp->delayParams.delReqTxTsNS);

    slaveDelay = doubleWord - slaveDelay;

    /*Do adjustment for MII Rx and Tx delay.
     * Here is the calculation :
     * delReqTxTS = delReqTxTS - Tx adjustment, rxTs = rxTs - Rx adjustment
     *  => delReqTxTS - rxTs = delReqTxTS - rxTs + Rx Adjustment - Tx Adjustment*/

    slaveDelay = (uint32_t)((double)slaveDelay * hTimeSyncPtp->tsSyntInfo.rcf);

    masterDelay = ((uint64_t)hTimeSyncPtp->delayParams.timeStampSec *
                   (uint64_t)TIMESYNC_SEC_TO_NS) +
                  (uint64_t)hTimeSyncPtp->delayParams.timeStampNS;
    masterDelay = masterDelay - (((uint64_t)
                                  hTimeSyncPtp->syncParam[syncPortNum].originTsSec *
                                  (uint64_t)TIMESYNC_SEC_TO_NS) + (uint64_t)
                                 hTimeSyncPtp->syncParam[syncPortNum].originTsNs);

    if (masterDelay > (slaveDelay + correctionField))
    {
        /*Add path delay minus correction divided by 2*/
        hTimeSyncPtp->tsRunTimeVar.meanPathDelay = (masterDelay - slaveDelay - correctionField) >> 1;
    }
    else
    {
        hTimeSyncPtp->tsRunTimeVar.meanPathDelay = 0;
    }

    /*check for illegal value*/
    if (hTimeSyncPtp->tsRunTimeVar.meanPathDelay > TIMESYNC_PTP_LINE_DELAY_ERROR_THRESHOLD)
    {
        hTimeSyncPtp->tsRunTimeVar.meanPathDelay = 0;
    }

    /*First time so assign directly*/
    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine & TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED) == 0)
    {
        hTimeSyncPtp->tsRunTimeVar.pathDelay[syncPortNum] = hTimeSyncPtp->tsRunTimeVar.meanPathDelay;
        /*Once delay has been computed notify the state machine*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED;
    }
    else
    {
        /*Use exponential averaging filter to get the line delay*/
        hTimeSyncPtp->tsRunTimeVar.pathDelay[syncPortNum] = (uint32_t)((double)hTimeSyncPtp->tsRunTimeVar.pathDelay[syncPortNum] *
                                                                        (double)TIMESYNC_PTP_FILTER_ALPHA_COEFF +
                                                                        (double)hTimeSyncPtp->tsRunTimeVar.meanPathDelay *
                                                                        (double)(1 - TIMESYNC_PTP_FILTER_ALPHA_COEFF));
    }
}

/*Shown below is the Peer delay logic*/

/*
    Self           Peer         |
 *    T1            |           T
 *    |             T2          i
 *    |             |           m
 *    |             |           e
 *    |             T3          |
 *    T4            |           |
 *    |             |          \|/
 */

/* delay on self (device) is T4 - T1 and delay on peer is T3-T2
 * peer delay = ((T4 - T1) - (T3 - T2)) / 2
 *
 * Assumption: Entire transaction is completed within a second, so only nanoseconds fields are used.
 */
void TimeSyncPtp_peerDelayCalc(TimeSyncPtp_Handle hTimeSyncPtp,
                               uint8_t twoStep,
                               uint8_t portNum)
{
    uint64_t T3_T2_diff = 0;
    uint64_t T4_T1_diff = 0;
    uint64_t correctionFieldSum = 0;

    /*compute T4 - T1. Time difference on our device, take care of wrap around
     *Only nanoseconds used */

    if (hTimeSyncPtp->pDelayParams[portNum].T4Nsec < hTimeSyncPtp->pDelayParams[portNum].T1Nsec)
    {
        T4_T1_diff = ((uint64_t)TIMESYNC_SEC_TO_NS +
                      (uint64_t)hTimeSyncPtp->pDelayParams[portNum].T4Nsec) -
                     (uint64_t)hTimeSyncPtp->pDelayParams[portNum].T1Nsec;
    }
    else
    {
        T4_T1_diff = hTimeSyncPtp->pDelayParams[portNum].T4Nsec -
                     hTimeSyncPtp->pDelayParams[portNum].T1Nsec;
    }

    /*Multiply device time with NRR*/
    T4_T1_diff = (uint32_t)((double)T4_T1_diff *
                            hTimeSyncPtp->tsNrrInfo[portNum].nrr);

    /*Special processing if 2-step*/
    if (twoStep == 1)
    {
        /*compute T3-T2*. Time difference on Peer*/
        if (hTimeSyncPtp->pDelayParams[portNum].T3Nsec < hTimeSyncPtp->pDelayParams[portNum].T2Nsec)
        {
            T3_T2_diff = ((uint64_t)TIMESYNC_SEC_TO_NS +
                          (uint64_t)hTimeSyncPtp->pDelayParams[portNum].T3Nsec) -
                         (uint64_t)hTimeSyncPtp->pDelayParams[portNum].T2Nsec;
        }
        else
        {
            T3_T2_diff = hTimeSyncPtp->pDelayParams[portNum].T3Nsec -
                         hTimeSyncPtp->pDelayParams[portNum].T2Nsec;
        }

        /*Compute sum of correction fields*/
        correctionFieldSum = hTimeSyncPtp->pDelayParams[portNum].delayResCorrField +
                             hTimeSyncPtp->pDelayParams[portNum].delayResFwUpCorrField;

        if (T4_T1_diff >= (T3_T2_diff + correctionFieldSum))
        {
            hTimeSyncPtp->tsRunTimeVar.meanPathDelay = T4_T1_diff - T3_T2_diff - correctionFieldSum;
            /*Average the delay*/
            hTimeSyncPtp->tsRunTimeVar.meanPathDelay >>= 1;
        }
        else
        {
            hTimeSyncPtp->tsRunTimeVar.meanPathDelay = 0;
        }
    }
    else
    {
        /*compute T3-T2*. Time difference on Peer*/
        T3_T2_diff = hTimeSyncPtp->pDelayParams[portNum].delayResCorrField;

        if (T4_T1_diff > T3_T2_diff)
        {
            hTimeSyncPtp->tsRunTimeVar.meanPathDelay = T4_T1_diff - T3_T2_diff;
            /*Average the delay*/
            hTimeSyncPtp->tsRunTimeVar.meanPathDelay >>= 1;
        }
        else
        {
            hTimeSyncPtp->tsRunTimeVar.meanPathDelay = 0;
        }
    }

    if (hTimeSyncPtp->tsRunTimeVar.meanPathDelay > TIMESYNC_PTP_PEER_DELAY_ERROR_THRESHOLD)
    {
        hTimeSyncPtp->tsRunTimeVar.meanPathDelay = 0;
    }

    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine & TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED) == 0)
    {
        hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] = hTimeSyncPtp->tsRunTimeVar.meanPathDelay;

        /*Once delay has been computed notify the state machine*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED;
    }
    else
    {
        /*Use exponential averaging filter to get the peer delay*/
        hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] =
            (uint32_t)((double)hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] *
                       (double)TIMESYNC_PTP_FILTER_ALPHA_COEFF +
                       (double)hTimeSyncPtp->tsRunTimeVar.meanPathDelay *
                       (double)(1 - TIMESYNC_PTP_FILTER_ALPHA_COEFF));
    }

    /*For 1-step TC delay asymmetry also gets added to the Sync frame correction
     * This is done by adding it to the path delay written in shared RAM*/
    hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] += hTimeSyncPtp->ptpConfig.asymmetryCorrection[portNum];

    TimeSync_setPathDelay(hTimeSyncPtp->timeSyncHandle,
                          hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum],
                          portNum);
}

int8_t TimeSyncPtp_processTimeOfDay(TimeSyncPtp_Handle hTimeSyncPtp,
                                    uint32_t nanoseconds,
                                    uint64_t seconds)
{
    if (hTimeSyncPtp == NULL)
    {
        return TIMESYNC_HANDLE_NOT_INITIALIZED;
    }

    if (!hTimeSyncPtp->ptpConfig.processToDSync2PPS)
    {
        return TIMESYNC_FEATURE_NOT_ENABLED;
    }

    hTimeSyncPtp->tsToDParams.toDTsSec = seconds;
    hTimeSyncPtp->tsToDParams.toDTsNS  = nanoseconds;

    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
         TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE) == 0)
    {
        /*write value as it is*/
        TimeSync_setClockTime(hTimeSyncPtp->timeSyncHandle,
                              nanoseconds,
                              seconds);

        /*Recalibrate PPS*/
        TimeSync_recalibratePps(hTimeSyncPtp->timeSyncHandle);

        /*Indicate that first adjustment is done*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE;
    }

    return TIMESYNC_OK;
}

void TimeSyncPtp_synchronizeClock(TimeSyncPtp_Handle hTimeSyncPtp)
{
    uint8_t syncPortNum = 0;
    uint32_t meanPathDelay = 0;
    int64_t tempVar1  = 0;
    int64_t tempVar2  = 0;
    int64_t adjOffset = 0;

    syncPortNum = hTimeSyncPtp->tsRunTimeVar.syncPortNum;
    /*Once initial adjustment is done, calculate the offset*/
    /*Get mean path delay*/
    meanPathDelay =
        hTimeSyncPtp->tsRunTimeVar.pathDelay[syncPortNum];

    if (hTimeSyncPtp->syncParam[syncPortNum].originTsSec ==
        hTimeSyncPtp->syncParam[syncPortNum].rxTsSec)
    {
        hTimeSyncPtp->tsRunTimeVar.currOffset =
            (int64_t)hTimeSyncPtp->syncParam[syncPortNum].rxTs -
            hTimeSyncPtp->syncParam[syncPortNum].originTsNs -
            meanPathDelay - hTimeSyncPtp->syncParam[syncPortNum].correctionField;
    }
    else
    {
        tempVar1 = ((int64_t)hTimeSyncPtp->syncParam[syncPortNum].rxTsSec - (int64_t)
                    hTimeSyncPtp->syncParam[syncPortNum].originTsSec)
                   * (int64_t)TIMESYNC_SEC_TO_NS;
        tempVar1 += (int64_t)hTimeSyncPtp->syncParam[syncPortNum].rxTs;
        tempVar2  = (int64_t)(hTimeSyncPtp->syncParam[syncPortNum].originTsNs +
                              meanPathDelay +
                              hTimeSyncPtp->syncParam[syncPortNum].correctionField);

        hTimeSyncPtp->tsRunTimeVar.currOffset = (int64_t)(tempVar1 - tempVar2);
    }

    /*Take running average of the offset*/
    hTimeSyncPtp->tsRunTimeVar.ltaOffset = (int64_t)((double)(TIMESYNC_PTP_FILTER_ALPHA_COEFF)*
                                                      (double)hTimeSyncPtp->tsRunTimeVar.ltaOffset +
                                                      (double)(1 - TIMESYNC_PTP_FILTER_ALPHA_COEFF) *
                                                      (double)hTimeSyncPtp->tsRunTimeVar.currOffset);

    if (hTimeSyncPtp->tsRunTimeVar.driftStable)
    {
        adjOffset = hTimeSyncPtp->tsRunTimeVar.currOffset +
                    hTimeSyncPtp->tsRunTimeVar.ltaOffset +
                    hTimeSyncPtp->tsRunTimeVar.initialOffset;
    }
    else
    {
        adjOffset = hTimeSyncPtp->tsRunTimeVar.currOffset;
    }

    TimeSync_adjTimeSlowComp(hTimeSyncPtp->timeSyncHandle,
                             adjOffset,
                             hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval);

    /*Check this condition only if device is in sync*/
    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
         TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC) ==
        TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC)
    {
        /*This is to track any large change in the timebase*/
        if (abs(hTimeSyncPtp->tsRunTimeVar.currOffset) > TIMESYNC_PTP_OFFSET_THRESHOLD_FOR_RESET)
        {
            /*Reset state machine*/
            TimeSyncPtp_reset(hTimeSyncPtp);
            return;
        }
    }

    /*The code below is part of Statistics collection
     * some of which is used to implement the stabilization algo
     */

    /*Find clock drift*/
    if (hTimeSyncPtp->tsRunTimeVar.prevOffset != 0)
    {
        hTimeSyncPtp->tsRunTimeVar.clockDrift += abs(
                                                      hTimeSyncPtp->tsRunTimeVar.currOffset -
                                                      hTimeSyncPtp->tsRunTimeVar.prevOffset);
        hTimeSyncPtp->tsRunTimeVar.clockDrift =
            hTimeSyncPtp->tsRunTimeVar.clockDrift / 2;
    }

    /*set prevoffset to current once drift is computed*/
    hTimeSyncPtp->tsRunTimeVar.prevOffset =
        hTimeSyncPtp->tsRunTimeVar.currOffset;

    /*Wait for the drift to stabilize*/
    if (hTimeSyncPtp->tsRunTimeVar.clockDrift <= TIMESYNC_PTP_STABLE_FILTER_THRESHOLD &&
        (hTimeSyncPtp->tsRunTimeVar.driftStable == 0))
    {
        hTimeSyncPtp->tsRunTimeVar.driftStable = 1;
        hTimeSyncPtp->tsRunTimeVar.initialOffset =
            hTimeSyncPtp->tsRunTimeVar.currOffset;
    }

    /*Wait for offset to become zero*/
    if (abs(hTimeSyncPtp->tsRunTimeVar.ltaOffset) <= TIMESYNC_PTP_STABLE_FILTER_THRESHOLD &&
        (hTimeSyncPtp->tsRunTimeVar.offsetStable == 0) &&
        (hTimeSyncPtp->tsRunTimeVar.driftStable))
    {
        hTimeSyncPtp->tsRunTimeVar.offsetStable = 1;
        /*Indicate that the device is in sync now*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC;
    }

    /*The stabilization logic collects offsets which have a low drift and are
     * clustered together. The idea is that the PPM of the crystal might have shifted
     * and since we are relying on the initial offset measurement to do zero offset correction
     * we need to constantly track this zero offset value or else the PPM might settle into a zone
     * with high value and low drift.
     *
     * To take an example let's say we sync to a master with a fixed offset of 1000 ns.
     * The DUT as a slave will detect this value in the variable hTimeSyncPtp->tsRunTimeVar.initialOffset
     * After some time, let's say this offset has become 1100 ns. In the absence of this logic the
     * slave will settle into a zone with 100ns offset. If later the offset becomes 1200 ns then DUT
     * will settle into a zone with 200ns offset*/

    /*Run the logic only once we are stable*/
    if (hTimeSyncPtp->tsRunTimeVar.offsetStable)
    {
        hTimeSyncPtp->offsetAlgo.lastSeenGoodDriftIndex++;

        /*If the drift is below our threshold and we have a close cluster
         * then we use this value for our averaging purpose
         */
        if ((hTimeSyncPtp->tsRunTimeVar.clockDrift <
             hTimeSyncPtp->offsetAlgo.driftThreshold) &&
            (hTimeSyncPtp->offsetAlgo.lastSeenGoodDriftIndex < TIMESYNC_PTP_OFFSET_ALGO_CLUSTER_SIZE))
        {
            hTimeSyncPtp->offsetAlgo.lastSeenGoodDriftIndex = 0;

            if (hTimeSyncPtp->offsetAlgo.numEntriesIndex < TIMESYNC_PTP_OFFSET_ALGO_BIN_SIZE)
            {
                /*Store the value for averaging later*/
                hTimeSyncPtp->offsetAlgo.correction[hTimeSyncPtp->offsetAlgo.numEntriesIndex++]
                    = hTimeSyncPtp->tsRunTimeVar.currOffset;
            }
            else
            {
                hTimeSyncPtp->offsetAlgo.binFull = 1;
            }
        }
        /*If cluster is broken then we reset the counters*/
        else if ((hTimeSyncPtp->offsetAlgo.lastSeenGoodDriftIndex >= TIMESYNC_PTP_OFFSET_ALGO_CLUSTER_SIZE) &&
                 (hTimeSyncPtp->offsetAlgo.binFull != 1))
        {
            /*reset the count if we can't find a good match in our window*/
            hTimeSyncPtp->offsetAlgo.lastSeenGoodDriftIndex = 0;
            hTimeSyncPtp->offsetAlgo.numEntriesIndex = 0;
        }
    }
}

void TimeSyncPtp_updateNRRParams(TimeSyncPtp_Handle hTimeSyncPtp,
                                 uint8_t portNum)
{
    uint8_t curIndex = 0;

    TimeSyncPtp_NrrInfo *nrrInfo = NULL;

    /*point to the nrr for correct port*/
    nrrInfo = &hTimeSyncPtp->tsNrrInfo[portNum];

    curIndex = (nrrInfo->nrrIndex++) % 3;

    /*Please note that the RCF calculated here is inverse of the RCF described in spec
     * This is because we multiply our time adjustments with this value
     */
    if (curIndex == TIMESYNC_PTP_SYNT_DEPTH)
    {
        curIndex = 0;
    }

    /*This is used later*/
    nrrInfo->curIndex = curIndex;

    /*Populate the array with TS*/
    nrrInfo->deviceRxTS[curIndex] = (uint64_t)
                                    hTimeSyncPtp->pDelayParams[portNum].T4Sec *
                                    (uint64_t)TIMESYNC_SEC_TO_NS + hTimeSyncPtp->pDelayParams[portNum].T4Nsec;

    nrrInfo->correctedPeerTS[curIndex] =
        (uint64_t)hTimeSyncPtp->pDelayParams[portNum].T3Sec * (uint64_t)TIMESYNC_SEC_TO_NS
        + hTimeSyncPtp->pDelayParams[portNum].T3Nsec +
        hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] +
        hTimeSyncPtp->pDelayParams[portNum].delayResCorrField +
        hTimeSyncPtp->pDelayParams[portNum].delayResFwUpCorrField;

    /*Wait for TS array to be full before starting syntonization*/
    if ((!nrrInfo->nrrEnable) &&
        (nrrInfo->nrrIndex == (TIMESYNC_PTP_SYNT_DEPTH + 2)))
    {
        nrrInfo->nrrEnable = 1;
    }
}

void TimeSyncPtp_calcNRR(TimeSyncPtp_Handle hTimeSyncPtp,
                         uint8_t portNum)
{
    uint64_t num = 0;
    uint64_t den = 0;

    uint8_t curIndex  = 0;
    uint8_t prevIndex = 0;

    TimeSyncPtp_NrrInfo *nrrInfo = NULL;

    /*point to the nrr for correct port*/
    nrrInfo = &hTimeSyncPtp->tsNrrInfo[portNum];

    curIndex = nrrInfo->curIndex;

    /*calculate nrr */
    if (nrrInfo->nrrEnable)
    {
        prevIndex = hTimeSyncPtp->syntIndexMap[curIndex];
        num = nrrInfo->correctedPeerTS[curIndex] -
              nrrInfo->correctedPeerTS[prevIndex];

        den = nrrInfo->deviceRxTS[curIndex] -
              nrrInfo->deviceRxTS[prevIndex];

        /*calculate rcf*/
        nrrInfo->nrr = ((double)num) / den;
    }
}

void TimeSyncPtp_calcRcfAndSyncInterval(TimeSyncPtp_Handle hTimeSyncPtp)
{
    uint64_t num = 0;
    uint64_t den = 0;
    uint32_t scaledRCF = 0;
    uint8_t curIndex  = 0;
    uint8_t prevIndex = 0;
    uint8_t tempIndex = 0;
    uint8_t count = 0;
    uint8_t syncPortNum = 0;
    uint64_t syncIntervalAverage = 0;
    double scalingFactor = 0;

    curIndex = (hTimeSyncPtp->tsSyntInfo.syntIndex++) % 3;

    syncPortNum = hTimeSyncPtp->tsRunTimeVar.syncPortNum;

    /*Please note that the RCF calculated here is inverse of the RCF described in spec
     * This is because we multiply our time adjustments with this value
     */
    if (curIndex == TIMESYNC_PTP_SYNT_DEPTH)
    {
        curIndex = 0;
    }

    /*Populate the array with TS*/
    hTimeSyncPtp->tsSyntInfo.syncIngressTs[curIndex] = (uint64_t)
                                                        hTimeSyncPtp->syncParam[syncPortNum].rxTsSec *
                                                        (uint64_t)TIMESYNC_SEC_TO_NS + hTimeSyncPtp->syncParam[syncPortNum].rxTs;

    hTimeSyncPtp->tsSyntInfo.correctedMasterTs[curIndex] =
        (uint64_t)hTimeSyncPtp->syncParam[syncPortNum].originTsSec *
        (uint64_t)TIMESYNC_SEC_TO_NS +
        hTimeSyncPtp->syncParam[syncPortNum].originTsNs +
        hTimeSyncPtp->tsRunTimeVar.pathDelay[hTimeSyncPtp->tsRunTimeVar.syncPortNum] +
        hTimeSyncPtp->syncParam[syncPortNum].correctionField;

    /*Wait for TS array to be full before starting syntonization*/
    if ((!hTimeSyncPtp->tsSyntInfo.syntEnable) &&
        (hTimeSyncPtp->tsSyntInfo.syntIndex == (TIMESYNC_PTP_SYNT_DEPTH + 2)))
    {
        hTimeSyncPtp->tsSyntInfo.syntEnable = 1;
    }

    /*calculate rcf */
    if (hTimeSyncPtp->tsSyntInfo.syntEnable)
    {
        prevIndex = hTimeSyncPtp->syntIndexMap[curIndex];
        num = hTimeSyncPtp->tsSyntInfo.correctedMasterTs[curIndex] -
              hTimeSyncPtp->tsSyntInfo.correctedMasterTs[prevIndex];

        den = hTimeSyncPtp->tsSyntInfo.syncIngressTs[curIndex] -
              hTimeSyncPtp->tsSyntInfo.syncIngressTs[prevIndex];

        /*calculate rcf*/
        hTimeSyncPtp->tsSyntInfo.rcf = ((double)num) / den;
        scaledRCF = (uint32_t)(hTimeSyncPtp->tsSyntInfo.rcf * 1024);

        /* Set Rcf value to hardware/ low level driver */
        TimeSync_setRcf(hTimeSyncPtp->timeSyncHandle, scaledRCF);

        /*calculate average of difference between two successive sync frames*/
        for (count = 0; count < 3; count++)
        {
            tempIndex = (curIndex + count) % TIMESYNC_PTP_SYNT_DEPTH;
            prevIndex = hTimeSyncPtp->prevIndexMap[tempIndex];

            if (hTimeSyncPtp->tsSyntInfo.correctedMasterTs[tempIndex] >
                hTimeSyncPtp->tsSyntInfo.correctedMasterTs[prevIndex])
            {
                syncIntervalAverage += (hTimeSyncPtp->tsSyntInfo.correctedMasterTs[tempIndex] -
                                        hTimeSyncPtp->tsSyntInfo.correctedMasterTs[prevIndex]);
            }
        }

        syncIntervalAverage = syncIntervalAverage / 2;

        hTimeSyncPtp->tsRunTimeVar.currSyncInterval = syncIntervalAverage;

        if (hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval == 0)
        {
            hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval =
                hTimeSyncPtp->tsRunTimeVar.currSyncInterval;
            hTimeSyncPtp->tsRunTimeVar.firstSyncInterval =
                hTimeSyncPtp->tsRunTimeVar.currSyncInterval;

            /*Add 50% extra so minor variations in master don't cause a timeout*/
            hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval =
                hTimeSyncPtp->tsRunTimeVar.currSyncInterval;
            hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval +=
                hTimeSyncPtp->tsRunTimeVar.currSyncInterval >> 1;

            scalingFactor = ((double)1000 / (double)(
                                                     hTimeSyncPtp->ptpConfig.tickPeriod));

            /*Multiply/Divide by clock scaling factor*/
            hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval =
                (uint32_t)((double)hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval *
                           scalingFactor);

            /*convert in terms of PTP BG ticks*/
            hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval =
                (uint32_t)((double)hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval /
                           (double)(TIMESYNC_PTP_BG_TASK_TICK_PERIOD * 1000000));
        }
        else
        {
            hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval =
                (uint32_t)(((double)(hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval) * TIMESYNC_PTP_FILTER_ALPHA_COEFF) +
                           ((double)(1 - TIMESYNC_PTP_FILTER_ALPHA_COEFF) *
                            (double)(hTimeSyncPtp->tsRunTimeVar.currSyncInterval)));
        }

        hTimeSyncPtp->syncInterval = hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval;

        /*Once sync interval has been calculated notify the state machine*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |=
            TIMESYNC_PTP_STATE_MACHINE_SYNC_INTERVAL_COMPUTED;
    }
}

void TimeSyncPtp_processPtpFrame(TimeSyncPtp_Handle hTimeSyncPtp,
                                 uint8_t *pktBuffer,
                                 uint8_t portNum,
                                 uint32_t size,
                                 uint8_t isLinkLocal)
{
    int32_t status = TIMESYNC_OK;
    uint8_t pktType = 0U;
    uint8_t ifTwoStep = 0U;
    uint8_t offset = 0U;
    uint32_t nanoseconds = 0U;
    uint64_t seconds = 0U;
    uint16_t etherType = 0U;
    uint16_t seqId = 0U;
    uint8_t port = 0;
    int8_t linkStatus = 0;

    offset = hTimeSyncPtp->ptpConfig.frameOffset;

    if (TRUE == hTimeSyncPtp->ptpConfig.hsrEnabled)
    {
        if (isLinkLocal)
        {
            etherType = TimeSync_convBigEndianToLittleEndianHalfWord(pktBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE);
            if (etherType == TIMESYNC_PTP_HSR_ETHERTYPE)
            {
                hTimeSyncPtp->ptpConfig.ll_has_hsrTag = TRUE;
            }

            if (hTimeSyncPtp->ptpConfig.ll_has_hsrTag)
            {
                offset -= TIMESYNC_PTP_HSR_CORRECTION;
            }
        }
        else
        {
            offset -= TIMESYNC_PTP_HSR_CORRECTION;
        }
    }

    if (TIMESYNC_VLAN_TYPE_NONE == hTimeSyncPtp->ptpConfig.vlanCfg.vlanType)
    {
        /* Strip VLAN tag if PTP operates in non-VLAN mode, but packet has VLAN tag */
        TimeSyncPtp_stripVlanTag(hTimeSyncPtp, pktBuffer, &size);
    }

    if (TIMESYNC_VLAN_TYPE_SINGLE_TAG == hTimeSyncPtp->ptpConfig.vlanCfg.vlanType)
    {
        offset -= TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    if (TIMESYNC_VLAN_TYPE_DOUBLE_TAG == hTimeSyncPtp->ptpConfig.vlanCfg.vlanType)
    {
        offset -= TIMESYNC_PTP_DOUBLE_TAG_VLAN_HDR_SIZE;
    }

    pktType = (uint8_t)(*(pktBuffer + TIMESYNC_PTP_MSG_ID_OFFSET - offset));
    ifTwoStep  = (uint8_t)(*(pktBuffer + TIMESYNC_PTP_FLAG_OFFSET - offset));
    ifTwoStep &= 2;
    TimeSync_convEndianess(pktBuffer + TIMESYNC_PTP_SEQ_ID_OFFSET - offset, &seqId, 2);

    /*PTPd stack handles announce and management messages*/
    if ((TIMESYNC_PTP_ANNOUNCE_MSG_ID == pktType) || (TIMESYNC_PTP_MGMT_MSG_ID == pktType))
    {
        if (TIMESYNC_PTP_ANNOUNCE_MSG_ID == pktType)
        {
            /*Just parse the Announce frame for MAC ID
             * and make it master
             */
            TimeSyncPtp_BMCA(hTimeSyncPtp, pktBuffer, portNum);

            /* If operated in Transparent clock mode, forward Announce frame to other ports */
            if (((hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_TRANSPARENT_CLOCK) ||
                 (hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_OC_AND_TC)) &&
                (hTimeSyncPtp->masterPortNum == portNum))
            {
                for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
                {
                    if ((TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port)) &&
                        (port != portNum))
                    {
                        linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                        if (linkStatus)
                        {
                            status = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                           pktBuffer,
                                                           size,
                                                           port);
                            /* If send frame failed exit out of this function */
                            if (status != TIMESYNC_OK)
                            {
                                return;
                            }
                        }
                    }
                }
            }
            return;
        }

        /*Should we use the port number???*/
        if (!(hTimeSyncPtp->stackParams.generalFrameFlag)) /*Make sure the previous packet is trnasfered to PTP Stack*/
        {
            hTimeSyncPtp->stackParams.ptpGeneralSize = size;

            if (TRUE == hTimeSyncPtp->ptpConfig.hsrEnabled)
            {
                hTimeSyncPtp->stackParams.ptpGeneralSize -= TIMESYNC_PTP_HSR_CORRECTION;
                memcpy(hTimeSyncPtp->stackParams.ptpGeneralFrame,
                       pktBuffer,
                       TIMESYNC_PTP_SRC_DST_MAC_SIZE);
                memcpy(hTimeSyncPtp->stackParams.ptpGeneralFrame + TIMESYNC_PTP_SRC_DST_MAC_SIZE,
                       pktBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE + TIMESYNC_PTP_HSR_CORRECTION,
                       hTimeSyncPtp->stackParams.ptpGeneralSize - TIMESYNC_PTP_SRC_DST_MAC_SIZE);
            }
            else
            {
                memcpy(hTimeSyncPtp->stackParams.ptpGeneralFrame, pktBuffer,
                       hTimeSyncPtp->stackParams.ptpGeneralSize);
            }

            hTimeSyncPtp->stackParams.generalFrameFlag = 1;
        }
    }
    else
    {
        if (TIMESYNC_PTP_PDLY_REQ_MSG_ID == pktType)         /*Pdelay request frame*/
        {
            status = TimeSync_getRxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                             TIMESYNC_PDELAY_REQ_FRAME,
                                             portNum,
                                             seqId,
                                             &nanoseconds,
                                             &seconds);
            if (status == TIMESYNC_OK)
            {
                hTimeSyncPtp->pDelayParams[portNum].pDelayReqRcvdTSSec = seconds;
                hTimeSyncPtp->pDelayParams[portNum].pDelayReqRcvdTSNsec = nanoseconds;

                /*Copy into buffer and post event*/

                /*Remove additional HSR tag */
                if (hTimeSyncPtp->ptpConfig.ll_has_hsrTag)
                {
                    memcpy(hTimeSyncPtp->timeSyncBuff.pdelayReqRxBuf[portNum], pktBuffer,
                           TIMESYNC_PTP_SRC_DST_MAC_SIZE);
                    memcpy(hTimeSyncPtp->timeSyncBuff.pdelayReqRxBuf[portNum] +
                           TIMESYNC_PTP_SRC_DST_MAC_SIZE,
                           pktBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE + TIMESYNC_PTP_HSR_CORRECTION,
                           TIMESYNC_PTP_PDELAY_BUF_SIZE - TIMESYNC_PTP_SRC_DST_MAC_SIZE);
                }
                else
                {
                    memcpy(hTimeSyncPtp->timeSyncBuff.pdelayReqRxBuf[portNum],
                           pktBuffer, TIMESYNC_PTP_PDELAY_BUF_SIZE);
                }

                EventP_post(hTimeSyncPtp->ptpPdelayReqEvtHandle[portNum],
                            hTimeSyncPtp->eventIdPdelayReq);
            }
        }
        else if (TIMESYNC_PTP_PDLY_RSP_MSG_ID == pktType)        /*Pdelay response frame*/
        {
            status = TimeSync_getRxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                             TIMESYNC_PDELAY_RESP_FRAME,
                                             portNum,
                                             seqId,
                                             &nanoseconds,
                                             &seconds);
            if (status == TIMESYNC_OK)
            {

                /*T4 timestamp*/
                hTimeSyncPtp->pDelayParams[portNum].T4Sec = seconds;
                hTimeSyncPtp->pDelayParams[portNum].T4Nsec = nanoseconds;

                /*set two step flag. Used in another task*/
                hTimeSyncPtp->pDelayParams[portNum].ifTwoStep = ifTwoStep;

                if (hTimeSyncPtp->ptpConfig.ll_has_hsrTag)
                {
                    memcpy(hTimeSyncPtp->timeSyncBuff.pdelayResRxBuf[portNum],
                           pktBuffer,
                           TIMESYNC_PTP_SRC_DST_MAC_SIZE);
                    memcpy(hTimeSyncPtp->timeSyncBuff.pdelayResRxBuf[portNum] +
                           TIMESYNC_PTP_SRC_DST_MAC_SIZE,
                           pktBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE + TIMESYNC_PTP_HSR_CORRECTION,
                           TIMESYNC_PTP_PDELAY_BUF_SIZE - TIMESYNC_PTP_SRC_DST_MAC_SIZE);
                }
                else
                {
                    /*Copy into buffer and post event*/
                    memcpy(hTimeSyncPtp->timeSyncBuff.pdelayResRxBuf[portNum],
                           pktBuffer, TIMESYNC_PTP_PDELAY_BUF_SIZE);
                }

                EventP_post(hTimeSyncPtp->ptpPdelayResEvtHandle[portNum],
                            hTimeSyncPtp->eventIdPdelayResp);

                /*Another task pends on both Pdelay Resp and
                 * Pdelay Resp Follow Up frame. If this is a single step
                 * Pdelay response then we don't want that task to
                 * pend forever
                 */
                if (!ifTwoStep)
                {
                    EventP_post(hTimeSyncPtp->ptpPdelayResEvtHandle[portNum],
                                hTimeSyncPtp->eventIdPdelayRespFlwUp);
                }
            }
        }
        else if (TIMESYNC_PTP_PDLY_RESP_FLW_UP_MSG_ID == pktType)        /*Pdelay response follow up frame*/
        {
            /*Copy into buffer and post event*/
            if (hTimeSyncPtp->ptpConfig.ll_has_hsrTag)
            {
                memcpy(hTimeSyncPtp->timeSyncBuff.pdelayResFlwUpRxBuf[portNum],
                       pktBuffer,
                       TIMESYNC_PTP_SRC_DST_MAC_SIZE);
                memcpy(hTimeSyncPtp->timeSyncBuff.pdelayResFlwUpRxBuf[portNum] +
                       TIMESYNC_PTP_SRC_DST_MAC_SIZE,
                       pktBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE + TIMESYNC_PTP_HSR_CORRECTION,
                       TIMESYNC_PTP_PDELAY_BUF_SIZE - TIMESYNC_PTP_SRC_DST_MAC_SIZE);
            }
            else
            {
                memcpy(hTimeSyncPtp->timeSyncBuff.pdelayResFlwUpRxBuf[portNum],
                       pktBuffer, TIMESYNC_PTP_PDELAY_BUF_SIZE);
            }

            EventP_post(hTimeSyncPtp->ptpPdelayResEvtHandle[portNum],
                        hTimeSyncPtp->eventIdPdelayRespFlwUp);
        }
        else if (TIMESYNC_PTP_SYNC_MSG_ID == pktType)
        {
            status = TimeSync_getRxTimestamp(hTimeSyncPtp->timeSyncHandle,
                                             TIMESYNC_SYNC_FRAME,
                                             portNum,
                                             seqId,
                                             &nanoseconds,
                                             &seconds);
            if (status == TIMESYNC_OK)
            {
                /*Store Rx timestamp*/
                hTimeSyncPtp->syncParam[portNum].rxTsSec = seconds;
                hTimeSyncPtp->syncParam[portNum].rxTs = nanoseconds;

                /*set two step flag. Used in another task*/
                hTimeSyncPtp->syncParam[portNum].ifTwoStep = ifTwoStep;
                TimeSyncPtp_processSyncFrame(hTimeSyncPtp, pktBuffer, FALSE, portNum, size);
            }

        }
        else if (TIMESYNC_PTP_FOLLOW_UP_MSG_ID == pktType)
        {
            TimeSyncPtp_processSyncFrame(hTimeSyncPtp, pktBuffer, TRUE, portNum, size);
        }
        else if (TIMESYNC_PTP_DLY_RESP_MSG_ID == pktType)  /*PTP_DLY_RSP_MSG_ID*/
        {
            TimeSyncPtp_processDelayResFrame(hTimeSyncPtp, pktBuffer, portNum);
        }
        else
        {
            return;
        }
    }
}

void TimeSyncPtp_processSyncFrame(TimeSyncPtp_Handle hTimeSyncPtp,
                                  uint8_t *buff,
                                  uint8_t followUp,
                                  uint8_t portNum,
                                  uint32_t size)
{
    uint8_t *bytePtr = NULL;
    uint8_t offset = 0;
    uint16_t halfWord = 0;
    uint64_t doubleWord = 0;
    uint64_t followUpCorrectionField = 0;
    uint64_t timeElapsed = 0;
    int32_t retVal;
    uint8_t port = 0;
    int8_t linkStatus = 0;

    /*packet offset*/
    offset = hTimeSyncPtp->ptpConfig.frameOffset;

    /*Since we are processing tagged HSR frames, we need to account for it*/
    if (TRUE == hTimeSyncPtp->ptpConfig.hsrEnabled)
    {
        offset -= TIMESYNC_PTP_HSR_CORRECTION;
    }

    if (TIMESYNC_VLAN_TYPE_SINGLE_TAG == hTimeSyncPtp->ptpConfig.vlanCfg.vlanType)
    {
        offset -= TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    /*Take timestamps and calculate BD since this is common to sync
     * frames from both ports. Synchronization OTOH is done only for
     * sync frames from master port*/

    /*For sync frame*/
    if (!followUp)
    {
        if (hTimeSyncPtp->masterPortNum == portNum)
        {
            hTimeSyncPtp->tsRunTimeVar.syncPortNum = portNum;
            /*Reset the last seen counter*/
            hTimeSyncPtp->tsRunTimeVar.syncLastSeenCounter = 0;
        }

        /*Copy correction field*/
        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset);
        TimeSync_convEnd6to8(bytePtr, &(hTimeSyncPtp->syncParam[portNum].correctionField));

        /*Do asymmetry correction*/
        hTimeSyncPtp->syncParam[portNum].correctionField +=
            hTimeSyncPtp->ptpConfig.asymmetryCorrection[portNum];

        /*Copy sequence ID*/
        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_SEQ_ID_OFFSET - offset);
        TimeSync_convEndianess(bytePtr, &(hTimeSyncPtp->tsRunTimeVar.curSyncSeqId[portNum]), 2);

        /* If received sync frame is in two step mode, and device is configured in TC mode,
         * forward sync frame to other ports */
        if ((hTimeSyncPtp->syncParam[portNum].ifTwoStep) &&
            (hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX]) &&
            ((hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_TRANSPARENT_CLOCK) ||
             (hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_OC_AND_TC)) &&
            (hTimeSyncPtp->masterPortNum == portNum))
        {
            for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
            {
                if ((TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port)) &&
                    (port != portNum))
                {
                    linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                    if (linkStatus)
                    {
                        retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                       buff,
                                                       size,
                                                       port);
                        /* If send frame failed exit out of this function.
                         * Workaround for retVal  was set but never used. */
                        if (retVal != TIMESYNC_OK)
                        {
                            return;
                        }
                    }
                }
            }
        }

        /*If forced mode is on and it's a 1-step then we send the frame out
         * of the opposite port after setting the 2-step bit*/
        if ((!hTimeSyncPtp->syncParam[portNum].ifTwoStep) &&
            (hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX]) &&
            ((hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_TRANSPARENT_CLOCK) ||
             (hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_OC_AND_TC)))
        {
            for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
            {
                if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port))
                {
                    linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                    if ((linkStatus) && (port != portNum))
                    {
                        hTimeSyncPtp->tsRunTimeVar.forced2step[port] = TRUE;
                        /*set 2-step bit*/
                        bytePtr   = (uint8_t *)((buff + TIMESYNC_PTP_FLAG_OFFSET - offset));
                        *bytePtr |= 0x2;

                        retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                       buff,
                                                       size,
                                                       port);
                    }
                }
            }

            for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
            {
                if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port))
                {
                    linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                    if ((linkStatus) && (port != portNum))
                    {
                        /*Create the follow up frame by changing the frame type field*/
                        bytePtr  = (uint8_t *)((buff + TIMESYNC_PTP_MSG_ID_OFFSET - offset));
                        *bytePtr = TIMESYNC_PTP_FOLLOW_UP_MSG_ID;

                        bytePtr  = (uint8_t *)((buff + TIMESYNC_PTP_CONTROL_MSG_ID_OFFSET - offset));
                        *bytePtr = TIMESYNC_PTP_FLW_UP_CTRL_MSG_ID;

                        /*Strip the HSR tag before copying the follow up frame
                           since we will add a different HSR tag*/
                        if (hTimeSyncPtp->ptpConfig.hsrEnabled)
                        {
                            memcpy(hTimeSyncPtp->timeSyncBuff.followUpTxBuf[port], buff, 12);
                            memcpy(hTimeSyncPtp->timeSyncBuff.followUpTxBuf[port] + 12, buff + 18, size - 18);
                        }
                        else
                        {
                            memcpy(hTimeSyncPtp->timeSyncBuff.followUpTxBuf[port], buff, size);
                        }

                        /*Set event flag to indicate follow up frame generation*/
                        EventP_post(hTimeSyncPtp->ptpSendFollowUpEvtHandle[port],
                                    hTimeSyncPtp->eventIdFlwUpGenerated);
                    }
                }
            }
        }
        else
        {
            hTimeSyncPtp->tsRunTimeVar.forced2step[portNum] = FALSE;
        }

        if ((hTimeSyncPtp->syncParam[portNum].ifTwoStep) || (hTimeSyncPtp->masterPortNum != portNum))
        {
            return;
        }

        /*Get origin timestamp*/
        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset);
        TimeSync_convEnd6to8(bytePtr, &(hTimeSyncPtp->syncParam[portNum].originTsSec));

        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset);
        TimeSync_convEndianess(bytePtr, &(hTimeSyncPtp->syncParam[portNum].originTsNs), 4);
    }
    else
    {
        /*Check for Sync mismatch*/
        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_SEQ_ID_OFFSET - offset);
        TimeSync_convEndianess(bytePtr, &(halfWord), 2);

        if (hTimeSyncPtp->tsRunTimeVar.curSyncSeqId[portNum] != halfWord)
        {
            return;
        }

        /*get correction field in follow up frame*/
        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset);
        TimeSync_convEnd6to8(bytePtr, &(followUpCorrectionField));

        /*Correction field contains correction field value in sync frame
         * It needs to be added to the correction field value inside follow up*/
        hTimeSyncPtp->syncParam[portNum].correctionField += followUpCorrectionField;

        /*Get origin timestamp*/
        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset);
        TimeSync_convEnd6to8(bytePtr, &(hTimeSyncPtp->syncParam[portNum].originTsSec));

        bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset);
        TimeSync_convEndianess(bytePtr, &(hTimeSyncPtp->syncParam[portNum].originTsNs), 4);

        /*---If link is up on opposite port then
         * calculate Bridge delay and send out follow up frame---*/

        /*If PTP is configured in ordinary clock mode then don't do Bridge delay computation*/
        if ((hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_TRANSPARENT_CLOCK) ||
            (hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_OC_AND_TC))
        {
            for (port = 0; port < TIMESYNC_PTP_MAX_PORTS_SUPPORTED; port++)
            {
                if (TIMESYNC_IS_BIT_SET(hTimeSyncPtp->ptpConfig.portMask, port))
                {
                    linkStatus = TimeSync_isPortLinkUp(hTimeSyncPtp->timeSyncHandle, port);
                    if ((linkStatus) && (port != portNum))
                    {
                        doubleWord = hTimeSyncPtp->syncParam[port].txTsSec *
                                     (uint64_t)TIMESYNC_SEC_TO_NS +
                                     hTimeSyncPtp->syncParam[port].txTs;
                        timeElapsed = hTimeSyncPtp->syncParam[portNum].rxTsSec *
                                      (uint64_t)TIMESYNC_SEC_TO_NS +
                                      hTimeSyncPtp->syncParam[portNum].rxTs;
                        /*This is the BD or bridge delay*/
                        timeElapsed = doubleWord - timeElapsed;

                        /*Multiply BD with RCF. For 802.1 AB this should be the accumulated rate ratio*/
                        timeElapsed = (uint32_t)((double)timeElapsed * hTimeSyncPtp->tsSyntInfo.rcf);

                        /*Add Peer delay for P2P mode*/
                        if (TIMESYNC_PTP_DELAY_P2P == hTimeSyncPtp->ptpConfig.type)
                        {
                            timeElapsed += hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum];
                        }

                        /*Finally add the BD to existing correction field*/
                        timeElapsed += followUpCorrectionField;

                        /*timeElapsed now contains the corrected BD.
                         * Encode into frame and send out*/
                        TimeSync_convEndianess(&timeElapsed, (buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset), 6);

                        retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                                       buff,
                                                       size,
                                                       port);
                    }
                }
            }
        }
    }

    /*First time*/
    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
         TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE) == 0)
    {
        /* Check to make sure we don't latch on to a sync message before we
           select the master */
        if (hTimeSyncPtp->tsRunTimeVar.bmcaDone == 1)
        {
            /*Do first adjustment */
            TimeSyncPtp_doFirstAdjustment(hTimeSyncPtp, portNum);

            /*indicate that first adjustment is done*/
            hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE;
        }
    }
    else    /*if not first time sync frame*/
    {
        if (hTimeSyncPtp->tsRunTimeVar.syncPortNum == portNum)
        {
            if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
                 TIMESYNC_PTP_STATE_MACHINE_READY_FOR_SYNC) == TIMESYNC_PTP_STATE_MACHINE_READY_FOR_SYNC)
            {
                /*Synchronize clock*/
                TimeSyncPtp_synchronizeClock(hTimeSyncPtp);
            }
        }
    }

    if (hTimeSyncPtp->tsRunTimeVar.syncPortNum == portNum)
    {
        /*Post interrupt to send a delay request frame*/
        if (hTimeSyncPtp->ptpConfig.type == TIMESYNC_PTP_DELAY_E2E)
        {
            SemaphoreP_post(hTimeSyncPtp->delayReqTxSemHandle);
        }

        TimeSyncPtp_calcRcfAndSyncInterval(hTimeSyncPtp);
    }
}

void TimeSyncPtp_processDelayResFrame(TimeSyncPtp_Handle hTimeSyncPtp,
                                      uint8_t *buff,
                                      uint8_t portNum)
{
    uint8_t *bytePtr  = NULL;
    uint16_t halfWord = 0;
    uint8_t offset = hTimeSyncPtp->ptpConfig.frameOffset;

    if (TIMESYNC_VLAN_TYPE_SINGLE_TAG == hTimeSyncPtp->ptpConfig.vlanCfg.vlanType)
    {
        offset -= TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    /*check if the delay response has the correct sequence ID*/
    bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_SEQ_ID_OFFSET - offset);
    TimeSync_convEndianess(bytePtr, &(halfWord), 2);

    if ((hTimeSyncPtp->tsRunTimeVar.delReqSequenceID - 1) != halfWord)
    {
        return;
    }

    /*Get the correction field*/
    bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset);
    TimeSync_convEnd6to8(bytePtr, &(hTimeSyncPtp->delayParams.correctionField));

    /*Get origin timestamp and calculate line delay*/
    bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset);
    TimeSync_convEnd6to8(bytePtr, &(hTimeSyncPtp->delayParams.timeStampSec));

    bytePtr = (uint8_t *)(buff + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset);
    TimeSync_convEndianess(bytePtr, &(hTimeSyncPtp->delayParams.timeStampNS), 4);

    /*We have all the data now, calculate the line delay*/
    TimeSyncPtp_lineDelayCalc(hTimeSyncPtp);
}

void TimeSyncPtp_processPdelayReqFrame(TimeSyncPtp_Handle hTimeSyncPtp,
                                       uint8_t *buff,
                                       uint8_t portNum)
{
    /*Copy contents and echo back on the same port*/
    uint8_t *ptpPDelayResPacket = NULL;
    uint8_t *ptpPDelayResFlwUpPacket = NULL;
    uint8_t *bytePtrSrc = NULL;
    uint8_t *bytePtrPdelReq = NULL;
    uint8_t *bytePtrPdelRes = NULL;
    uint8_t offset = hTimeSyncPtp->ptpConfig.frameOffset;
    int32_t retVal;

    ptpPDelayResPacket = hTimeSyncPtp->timeSyncBuff.pdelayResTxBuf[portNum];
    ptpPDelayResFlwUpPacket = hTimeSyncPtp->timeSyncBuff.pdelayResFlwUpTxBuf[portNum];

    /*Add Request port clock Identity*/
    bytePtrSrc = (uint8_t *)(buff + TIMESYNC_PTP_SRC_CLK_IDENTITY - offset);
    bytePtrPdelReq = (uint8_t *)(ptpPDelayResPacket + TIMESYNC_PTP_REQ_SRC_PORT_IDENTITY - offset);
    bytePtrPdelRes = (uint8_t *)(ptpPDelayResFlwUpPacket + TIMESYNC_PTP_REQ_SRC_PORT_IDENTITY - offset);
    memcpy(bytePtrPdelReq, bytePtrSrc, 8);
    memcpy(bytePtrPdelRes, bytePtrSrc, 8);

    /*Add Correction Field from delay request*/
    bytePtrSrc = (uint8_t *)(buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset);
    bytePtrPdelReq = (uint8_t *)(ptpPDelayResPacket + TIMESYNC_PTP_CORRECTION_OFFSET - offset);
    bytePtrPdelRes = (uint8_t *)(ptpPDelayResFlwUpPacket + TIMESYNC_PTP_CORRECTION_OFFSET - offset);
    memcpy(bytePtrPdelReq, bytePtrSrc, 8);
    memcpy(bytePtrPdelRes, bytePtrSrc, 8);

    /**Add requested source port identity*/
    bytePtrSrc = (uint8_t *)(buff + TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset);
    bytePtrPdelReq = (uint8_t *)(ptpPDelayResPacket + TIMESYNC_PTP_REQ_SRC_PORT_ID - offset);
    bytePtrPdelRes = (uint8_t *)(ptpPDelayResFlwUpPacket + TIMESYNC_PTP_REQ_SRC_PORT_ID - offset);
    memcpy(bytePtrPdelReq, bytePtrSrc, 2);
    memcpy(bytePtrPdelRes, bytePtrSrc, 2);

    /**Copy sequence ID from Delay Req packet*/
    bytePtrSrc = (uint8_t *)(buff + TIMESYNC_PTP_SEQ_ID_OFFSET - offset);
    bytePtrPdelReq = (uint8_t *)(ptpPDelayResPacket + TIMESYNC_PTP_SEQ_ID_OFFSET - offset);
    bytePtrPdelRes = (uint8_t *)(ptpPDelayResFlwUpPacket + TIMESYNC_PTP_SEQ_ID_OFFSET - offset);
    memcpy(bytePtrPdelReq, bytePtrSrc, 2);
    memcpy(bytePtrPdelRes, bytePtrSrc, 2);
    TimeSync_convEndianess(buff + TIMESYNC_PTP_SEQ_ID_OFFSET - offset,
                           &hTimeSyncPtp->tsRunTimeVar.rxPDelReqSequenceID[portNum],
                           2);

    /*Copy domain number*/
    bytePtrSrc = (uint8_t *)(buff + TIMESYNC_PTP_DOMAIN_NUM_OFFSET - offset);
    bytePtrPdelReq = (uint8_t *)(ptpPDelayResPacket + TIMESYNC_PTP_DOMAIN_NUM_OFFSET - offset);
    bytePtrPdelRes = (uint8_t *)(ptpPDelayResFlwUpPacket + TIMESYNC_PTP_DOMAIN_NUM_OFFSET - offset);
    memcpy(bytePtrPdelReq, bytePtrSrc, 2);
    memcpy(bytePtrPdelRes, bytePtrSrc, 2);

    /*Add Source port ID*/
    TimeSync_addHalfWord(ptpPDelayResPacket + TIMESYNC_PTP_SRC_PORT_ID_OFFSET - offset,
                         (portNum + 1));
    TimeSync_addHalfWord(ptpPDelayResFlwUpPacket + TIMESYNC_PTP_SRC_PORT_ID_OFFSET -
                         offset,
                         (portNum + 1));

    TimeSync_convEndianess(&(hTimeSyncPtp->pDelayParams[portNum].pDelayReqRcvdTSSec),
                           ptpPDelayResPacket + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                           6);
    TimeSync_convEndianess(&(hTimeSyncPtp->pDelayParams[portNum].pDelayReqRcvdTSNsec),
                           ptpPDelayResPacket + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                           4);

    retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                   ptpPDelayResPacket,
                                   TIMESYNC_PTP_PDELAY_BUF_SIZE,
                                   portNum);

    /* If send frame failed exit out of this function.
     * Workaround for retVal  was set but never used. */
    if (retVal != TIMESYNC_OK)
    {
        return;
    }
}

void TimeSyncPtp_processPdelayRespFrame(TimeSyncPtp_Handle hTimeSyncPtp,
                                        uint8_t *buff,
                                        uint8_t followUp,
                                        uint8_t portNum)
{
    uint8_t offset = hTimeSyncPtp->ptpConfig.frameOffset;

    /*generic buffer used for comparison and storing*/
    uint8_t buf_for_comp[8] = {0};
    uint16_t halfWord = 0;

    if (TIMESYNC_VLAN_TYPE_SINGLE_TAG == hTimeSyncPtp->ptpConfig.vlanCfg.vlanType)
    {
        offset -= TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE;
    }

    /*check if this is a valid response frame to our delay request
     * extract parameters and calculate peer delay if so*/

    /*Check for source port identity*/
    memcpy(buf_for_comp, buff + TIMESYNC_PTP_REQ_SRC_PORT_IDENTITY - offset, 8);

    if (0 != memcmp(buf_for_comp, hTimeSyncPtp->clockIdentity, 8))
    {
        return;
    }

    /*check with the sequence id that was sent out*/
    TimeSync_convEndianess(buff + TIMESYNC_PTP_SEQ_ID_OFFSET - offset, &halfWord, 2);

    if (halfWord != (hTimeSyncPtp->tsRunTimeVar.pDelReqSequenceID[portNum] - 1))
    {
        return;
    }

    if (!followUp)
    {
        /*Extract correction field*/
        TimeSync_convEnd6to8(buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset,
                             &(hTimeSyncPtp->pDelayParams[portNum].delayResCorrField));

        /*Now check if it's a two step, if yes then exit*/
        TimeSync_convEndianess(buff + TIMESYNC_PTP_FLAG_OFFSET - offset, &halfWord, 2);

        if (halfWord & TIMESYNC_PTP_TWO_STEP_MASK)
        {
            /*Extract T2 timestamp in seconds*/
            TimeSync_convEnd6to8(buff + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                                 &(hTimeSyncPtp->pDelayParams[portNum].T2Sec));

            /*Extract T2 timestamp in nanoseconds*/
            TimeSync_convEndianess(buff + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                                   &(hTimeSyncPtp->pDelayParams[portNum].T2Nsec), 4);

            return;
        }
    }
    else
    {
        /*Extract correction field*/
        TimeSync_convEnd6to8(buff + TIMESYNC_PTP_CORRECTION_OFFSET - offset,
                             &(hTimeSyncPtp->pDelayParams[portNum].delayResFwUpCorrField));
        /*Extract T2 timestamp in seconds*/
        TimeSync_convEnd6to8(buff + TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET - offset,
                             &(hTimeSyncPtp->pDelayParams[portNum].T3Sec));

        /*Extract T2 timestamp in nanoseconds.*/
        TimeSync_convEndianess(buff + TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET - offset,
                               &(hTimeSyncPtp->pDelayParams[portNum].T3Nsec),
                               4);
    }

    /*Calculate peer delay*/
    TimeSyncPtp_peerDelayCalc(hTimeSyncPtp, followUp, portNum);
    /*Update params here, NRR gets calculated in the background*/
    TimeSyncPtp_updateNRRParams(hTimeSyncPtp, portNum);
    TimeSyncPtp_calcNRR(hTimeSyncPtp, portNum);

    return;
}

void TimeSyncPtp_forced2StepBDCalc(TimeSyncPtp_Handle hTimeSyncPtp,
                                   uint8_t portNum)
{
    uint8_t *ptpFlwUpPacket = NULL;
    uint64_t doubleWord  = 0;
    uint64_t timeElapsed = 0;
    uint8_t syncPortNum;
    int32_t retVal;

    syncPortNum = hTimeSyncPtp->tsRunTimeVar.syncPortNum;
    ptpFlwUpPacket = hTimeSyncPtp->timeSyncBuff.followUpTxBuf[portNum];

    /*calculate bridge delay and write into the follow up frame
     * time stamp is already available in syncParam*/
    doubleWord = hTimeSyncPtp->syncParam[portNum].txTsSec *
                 (uint64_t)TIMESYNC_SEC_TO_NS +
                 hTimeSyncPtp->syncParam[portNum].txTs;
    timeElapsed = hTimeSyncPtp->syncParam[syncPortNum].rxTsSec *
                  (uint64_t)TIMESYNC_SEC_TO_NS +
                  hTimeSyncPtp->syncParam[syncPortNum].rxTs;
    /*This is the BD or bridge delay*/
    timeElapsed = doubleWord - timeElapsed;

    /*Multiply BD with RCF. For 802.1 AB this should be the accumulated rate ratio*/
    timeElapsed = (uint32_t)((double)timeElapsed * hTimeSyncPtp->tsSyntInfo.rcf);

    /*Add Peer delay for P2P mode*/
    if (TIMESYNC_PTP_DELAY_P2P == hTimeSyncPtp->ptpConfig.type)
    {
        timeElapsed += hTimeSyncPtp->tsRunTimeVar.pathDelay[syncPortNum];
    }

    /*timeElapsed now contains the corrected BD.
     * Encode into frame and send out*/
    TimeSync_convEndianess(&timeElapsed,
                           (ptpFlwUpPacket + TIMESYNC_PTP_CORRECTION_OFFSET - hTimeSyncPtp->ptpConfig.frameOffset),
                           6);

    retVal = TimeSync_sendPtpFrame(hTimeSyncPtp->timeSyncHandle,
                                   ptpFlwUpPacket,
                                   hTimeSyncPtp->timeSyncBuff.flwUpBufSize,
                                   portNum);

    /* If send frame failed exit out of this function.
     * Workaround for retVal  was set but never used. */
    if (retVal != TIMESYNC_OK)
    {
        return;
    }
}

void TimeSyncPtp_getGeneralMessage(TimeSyncPtp_Handle hTimeSyncPtp,
                                   int8_t *buff)
{
    uint8_t *macId = NULL;
    uint8_t count  = 0;

    if (hTimeSyncPtp->stackParams.generalFrameFlag)
    {
        if (TIMESYNC_PTP_DELAY_E2E == hTimeSyncPtp->ptpConfig.type)
        {
            memcpy(buff,
                   hTimeSyncPtp->stackParams.ptpGeneralFrame + TIMESYNC_PTP_E2E_BUFFER_OFFSET,
                   hTimeSyncPtp->stackParams.ptpGeneralSize - TIMESYNC_PTP_E2E_BUFFER_OFFSET);
        }

        if (TIMESYNC_PTP_DELAY_P2P == hTimeSyncPtp->ptpConfig.type)
        {
            memcpy(buff,
                   hTimeSyncPtp->stackParams.ptpGeneralFrame + TIMESYNC_PTP_P2P_BUFFER_OFFSET,
                   hTimeSyncPtp->stackParams.ptpGeneralSize - TIMESYNC_PTP_P2P_BUFFER_OFFSET);
        }

        macId = (uint8_t *)(hTimeSyncPtp->stackParams.ptpGeneralFrame + TIMESYNC_PTP_SRC_MAC_OFFSET);

        for (count = 0; count < 6; count++)
        {
            hTimeSyncPtp->stackParams.ptpSrcMacID[count] = macId[count];
        }

        hTimeSyncPtp->stackParams.generalFrameFlag = 0;
    }
}

void TimeSyncPtp_synchronizeToD(TimeSyncPtp_Handle hTimeSyncPtp)
{
    uint64_t latch0TS = 0;
    uint64_t doubleWord = 0;
    uint64_t expected_value_ToD_seconds = 0;
    int32_t offset = 0;
    uint32_t nanoSeconds = 0U;
    uint64_t seconds = 0U;

    /*Calculate 64-bit latch and expected time of day timestamp*/
    latch0TS = (uint64_t)hTimeSyncPtp->tsToDParams.pPsTsSec * (uint64_t)TIMESYNC_SEC_TO_NS +
               hTimeSyncPtp->tsToDParams.pPsTsNS;

    expected_value_ToD_seconds = (uint64_t)(hTimeSyncPtp->tsToDParams.toDTsSec + 1) *
                                 (uint64_t)TIMESYNC_SEC_TO_NS;

    /*Do a finer adjustment the first time we get a pulse after
     * first adjustment is complete*/
    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
         TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE) ==
        TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE)
    {
        /*Get the current timer value to get the ISR delay*/
        TimeSync_getCurrentTime(hTimeSyncPtp->timeSyncHandle,
                                &nanoSeconds,
                                &seconds);
        doubleWord = seconds * (uint64_t)TIMESYNC_SEC_TO_NS + nanoSeconds;

        /*The ISR delay is current timer count minus the PPS timestamp*/
        offset = doubleWord - latch0TS;

        /*
         * The expected value of time stamp is the seconds value that was previously received
         * and a nanoseconds value of 0
         */
        doubleWord = expected_value_ToD_seconds + offset;

        nanoSeconds = (uint32_t)(doubleWord % (uint64_t)TIMESYNC_SEC_TO_NS);
        seconds = doubleWord / (uint64_t)TIMESYNC_SEC_TO_NS;

        /*Update the timer with the more accurate value*/
        TimeSync_setClockTime(hTimeSyncPtp->timeSyncHandle,
                              nanoSeconds,
                              seconds);

        /*Line delay is irrelevant here*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED;
    }

    /*Do synchronization when all parameters are available*/
    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
         TIMESYNC_PTP_STATE_MACHINE_READY_FOR_SYNC) == TIMESYNC_PTP_STATE_MACHINE_READY_FOR_SYNC)
    {
        /*
         * The expected value of time stamp is the seconds value that was previously received
         * plus 1 and a nanoseconds value of 0
         */
        hTimeSyncPtp->tsRunTimeVar.currOffset = latch0TS - expected_value_ToD_seconds;

        if (hTimeSyncPtp->tsRunTimeVar.ltaOffset != 0)
        {
            hTimeSyncPtp->tsRunTimeVar.ltaOffset = (int32_t)((double)(TIMESYNC_PTP_FILTER_ALPHA_COEFF_TOD)*
                                                              (double)hTimeSyncPtp->tsRunTimeVar.ltaOffset +
                                                              (double)(1 - TIMESYNC_PTP_FILTER_ALPHA_COEFF_TOD) *
                                                              (double)hTimeSyncPtp->tsRunTimeVar.currOffset);
        }
        else
        {
            hTimeSyncPtp->tsRunTimeVar.ltaOffset = hTimeSyncPtp->tsRunTimeVar.currOffset;
        }

        if (hTimeSyncPtp->tsRunTimeVar.driftStable)
        {
            offset = hTimeSyncPtp->tsRunTimeVar.ltaOffset +
                     2 * hTimeSyncPtp->tsRunTimeVar.initialOffset;
        }
        else
        {
            offset = hTimeSyncPtp->tsRunTimeVar.ltaOffset;
        }

        offset = hTimeSyncPtp->tsRunTimeVar.ltaOffset;

        TimeSync_adjTimeSlowComp(hTimeSyncPtp->timeSyncHandle,
                                 offset,
                                 hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval);

        /*Check this condition only if device is in sync*/
        if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
             TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC) ==
            TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC)
        {
            /*This is to track any large change in the timebase*/
            if (abs(hTimeSyncPtp->tsRunTimeVar.currOffset) > TIMESYNC_PTP_OFFSET_THRESHOLD_FOR_RESET)
            {
                /*Reset state machine*/
                TimeSyncPtp_reset(hTimeSyncPtp);
                return;
            }
        }

        /*The code below is part of statistics collection
         * some of which is used to implement the stabilization algo
         */

        /*Find clock drift*/
        if (hTimeSyncPtp->tsRunTimeVar.prevOffset != 0)
        {
            hTimeSyncPtp->tsRunTimeVar.clockDrift += abs(hTimeSyncPtp->tsRunTimeVar.currOffset -
                                                            hTimeSyncPtp->tsRunTimeVar.prevOffset);
            hTimeSyncPtp->tsRunTimeVar.clockDrift =
                hTimeSyncPtp->tsRunTimeVar.clockDrift / 2;
        }

        /*set prevoffset to current once drift is computed*/
        hTimeSyncPtp->tsRunTimeVar.prevOffset = hTimeSyncPtp->tsRunTimeVar.currOffset;

        /*Wait for the drift to stabilize*/
        if (hTimeSyncPtp->tsRunTimeVar.clockDrift <= TIMESYNC_PTP_STABLE_FILTER_THRESHOLD &&
            (hTimeSyncPtp->tsRunTimeVar.driftStable == 0))
        {
            hTimeSyncPtp->tsRunTimeVar.driftStable = 1;
            hTimeSyncPtp->tsRunTimeVar.initialOffset = hTimeSyncPtp->tsRunTimeVar.currOffset;
        }

        /*Wait for offset to become zero*/
        if (abs(hTimeSyncPtp->tsRunTimeVar.ltaOffset) <= TIMESYNC_PTP_STABLE_FILTER_THRESHOLD &&
            (hTimeSyncPtp->tsRunTimeVar.offsetStable == 0) &&
            (hTimeSyncPtp->tsRunTimeVar.driftStable))
        {
            hTimeSyncPtp->tsRunTimeVar.offsetStable = 1;
            /*Indicate that the device is in sync now*/
            hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC;
        }
    }
}

void TimeSyncPtp_calcSyncIntervalToD(TimeSyncPtp_Handle hTimeSyncPtp)
{
    uint8_t curIndex  = 0;
    uint8_t prevIndex = 0;
    uint8_t tempIndex = 0;
    uint8_t count = 0;

    uint64_t syncIntervalAverage = 0;

    if ((hTimeSyncPtp->tsRunTimeVar.stateMachine &
         TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED) !=
        TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED)
    {
        return;
    }

    curIndex = (hTimeSyncPtp->tsSyntInfo.syntIndex++) % 3;

    /*Please note that the RCF calculated here is inverse of the RCF described in spec
     * This is because we multiply our time adjustments with this value
     */
    if (curIndex == TIMESYNC_PTP_SYNT_DEPTH)
    {
        curIndex = 0;
    }

    hTimeSyncPtp->tsSyntInfo.correctedMasterTs[curIndex] = (uint64_t)hTimeSyncPtp->tsToDParams.pPsTsSec *
                                                              (uint64_t)TIMESYNC_SEC_TO_NS +
                                                              hTimeSyncPtp->tsToDParams.pPsTsNS;

    /*Wait for TS array to be full before starting syntonization*/
    if ((!hTimeSyncPtp->tsSyntInfo.syntEnable) &&
        (hTimeSyncPtp->tsSyntInfo.syntIndex == (TIMESYNC_PTP_SYNT_DEPTH + 2)))
    {
        hTimeSyncPtp->tsSyntInfo.syntEnable = 1;
    }

    /*calculate pulse interval */
    if (hTimeSyncPtp->tsSyntInfo.syntEnable)
    {
        prevIndex = hTimeSyncPtp->syntIndexMap[curIndex];

        /*calculate average of difference between two successive sync frames*/
        for (count = 0; count < 3; count++)
        {
            tempIndex = (curIndex + count) % TIMESYNC_PTP_SYNT_DEPTH;
            prevIndex = hTimeSyncPtp->prevIndexMap[tempIndex];

            if (hTimeSyncPtp->tsSyntInfo.correctedMasterTs[tempIndex] >
                hTimeSyncPtp->tsSyntInfo.correctedMasterTs[prevIndex])
            {
                syncIntervalAverage += (hTimeSyncPtp->tsSyntInfo.correctedMasterTs[tempIndex] -
                                        hTimeSyncPtp->tsSyntInfo.correctedMasterTs[prevIndex]);
            }
        }

        syncIntervalAverage = syncIntervalAverage / 2;

        hTimeSyncPtp->tsRunTimeVar.currSyncInterval = syncIntervalAverage;

        if (hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval == 0)
        {
            hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval = hTimeSyncPtp->tsRunTimeVar.currSyncInterval;
        }
        else
        {
            hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval =
                (uint32_t)(((double)(hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval) * TIMESYNC_PTP_FILTER_ALPHA_COEFF) +
                           ((double)(1 - TIMESYNC_PTP_FILTER_ALPHA_COEFF) *
                            (double)(hTimeSyncPtp->tsRunTimeVar.currSyncInterval)));
        }

        hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval = TIMESYNC_SEC_TO_NS;
        hTimeSyncPtp->syncInterval = hTimeSyncPtp->tsRunTimeVar.ltaSyncInterval;

        /*Once sync interval has been calculated notify the state machine*/
        hTimeSyncPtp->tsRunTimeVar.stateMachine |= TIMESYNC_PTP_STATE_MACHINE_SYNC_INTERVAL_COMPUTED;
    }
}

uint8_t TimeSyncPtp_isEnabled(TimeSyncPtp_Handle hTimeSyncPtp)
{
    return hTimeSyncPtp->enabled;
}

void TimeSyncPtp_getPrevAddress(TimeSyncPtp_Handle hTimeSyncPtp,
                                uint8_t *prevMac)
{
    uint8_t count = 0;

    for (count = 0; count < 6; count++)
    {
        prevMac[count] = hTimeSyncPtp->stackParams.ptpSrcMacID[count];
    }
}

void TimeSyncPtp_PortLinkResetCallBack(void *arg,
                                       uint8_t portNum,
                                       uint8_t linkStatus)
{
    TimeSyncPtp_Handle hTimeSyncPtp = (TimeSyncPtp_Handle)arg;

    /*Reset Port 0 NRR Info*/
    memset(&hTimeSyncPtp->tsNrrInfo[portNum], 0x0, sizeof(TimeSyncPtp_NrrInfo));
    hTimeSyncPtp->tsNrrInfo[portNum].nrr = 1.0;

    /*reset sequence id on that port*/
    hTimeSyncPtp->tsRunTimeVar.pDelReqSequenceID[portNum] = 0;
    /*Reset peer delay params*/
    memset(&(hTimeSyncPtp->pDelayParams[portNum]), 0x0, sizeof(TimeSyncPtp_PeerDelayParams));
    /*make peer delay history 0*/
    hTimeSyncPtp->tsRunTimeVar.pathDelay[portNum] = 0;

    /*If link loss on port connected to Master then reset the
     *  Syntonization and Sync params*/
    if (hTimeSyncPtp->tsRunTimeVar.syncPortNum == portNum)
    {
        /*Do a full reset*/
        TimeSyncPtp_reset(hTimeSyncPtp);
    }
}

void TimeSyncPtp_reset(TimeSyncPtp_Handle hTimeSyncPtp)
{
    /* Call sync loss callback*/
    if (hTimeSyncPtp->ptpConfig.syncLossNotifyFxn != NULL)
    {
        hTimeSyncPtp->ptpConfig.syncLossNotifyFxn();
    }

    /*first disable PTP so firmware is not running*/
    TimeSyncPtp_disable(hTimeSyncPtp);

    /*Now reset all values*/
    TimeSync_reset(hTimeSyncPtp->timeSyncHandle);

    /*Reset structures*/
    memset(&hTimeSyncPtp->syncParam[0], 0x0, sizeof(TimeSyncPtp_SyncParam));
    memset(&hTimeSyncPtp->syncParam[1], 0x0, sizeof(TimeSyncPtp_SyncParam));
    memset(&hTimeSyncPtp->delayParams, 0x0, sizeof(TimeSyncPtp_DelayReqRespParams));
    memset(&hTimeSyncPtp->pDelayParams[0], 0x0, sizeof(TimeSyncPtp_PeerDelayParams));
    memset(&hTimeSyncPtp->pDelayParams[1], 0x0, sizeof(TimeSyncPtp_PeerDelayParams));
    memset(&hTimeSyncPtp->tsSyntInfo, 0x0, sizeof(TimeSyncPtp_SyntInfo));
    memset(&hTimeSyncPtp->tsRunTimeVar, 0x0, sizeof(TimeSyncPtp_RuntimeVar));
    memset(&hTimeSyncPtp->tsNrrInfo[0], 0x0, sizeof(TimeSyncPtp_NrrInfo));
    memset(&hTimeSyncPtp->tsNrrInfo[1], 0x0, sizeof(TimeSyncPtp_NrrInfo));

    hTimeSyncPtp->tsRunTimeVar.stateMachine = 0;
    hTimeSyncPtp->tsSyntInfo.rcf = 1.0;
    hTimeSyncPtp->tsNrrInfo[0].nrr = 1.0;
    hTimeSyncPtp->tsNrrInfo[1].nrr = 1.0;
    hTimeSyncPtp->tsRunTimeVar.clockDrift = 10000;
    hTimeSyncPtp->tsRunTimeVar.syncTimeoutInterval = 10000;
    hTimeSyncPtp->offsetAlgo.driftThreshold = TIMESYNC_PTP_OFFSET_STABLE_ALGO_THRESHOLD;

    /*Finally enable PTP*/
    TimeSyncPtp_enable(hTimeSyncPtp);
}

void TimeSyncPtp_BMCA(TimeSyncPtp_Handle hTimeSyncPtp,
                      uint8_t *pktBuffer,
                      uint8_t portNum)
{
    /*Extract MAC ID and write parent address*/

    if (!hTimeSyncPtp->tsRunTimeVar.bmcaDone)
    {
        /*pass the source MAC ID*/
        TimeSync_updateParentAddress(hTimeSyncPtp->timeSyncHandle, pktBuffer + 6);
        /* Update master port number */
        hTimeSyncPtp->masterPortNum = portNum;
        /* Mark BMCA as done */
        hTimeSyncPtp->tsRunTimeVar.bmcaDone = 1;

        /* Once BMCA is done and master is identified, start boundary clock */
        if (hTimeSyncPtp->ptpConfig.deviceMode == TIMESYNC_BOUNDARY_CLOCK)
        {
            TimeSyncPtp_enableBoundaryClock(hTimeSyncPtp);
        }
    }
}

bool TimeSyncPtp_isPtpInSync(TimeSyncPtp_Handle hTimeSyncPtp)
{
    bool inSync = false;

    if (hTimeSyncPtp != NULL)
    {
        inSync = (hTimeSyncPtp->tsRunTimeVar.stateMachine & TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC) ? (true) : (false);
    }

    return inSync;
}

int32_t TimeSyncPtp_getCurrentOffset(TimeSyncPtp_Handle hTimeSyncPtp)
{
    int32_t offset = 0;

    if (hTimeSyncPtp != NULL)
    {
        offset = hTimeSyncPtp->tsRunTimeVar.currOffset;
    }

    return offset;
}

static void TimeSyncPtp_setTimeSyncConfig(TimeSyncPtp_Handle hTimeSyncPtp,
                                          TimeSync_Config *pTimeSyncConfig)
{
    pTimeSyncConfig->protoCfg.protocol  = hTimeSyncPtp->ptpConfig.protocol;
    pTimeSyncConfig->protoCfg.deviceCfg = hTimeSyncPtp->ptpConfig.deviceMode;

    if (hTimeSyncPtp->ptpConfig.masterParams.ptpFlags[TIMESYNC_PTP_TWO_STEP_INDEX])
    {
        pTimeSyncConfig->protoCfg.stepMode = TIMESYNC_DOUBLE_STEP;
    }
    else
    {
        pTimeSyncConfig->protoCfg.stepMode = TIMESYNC_SINGLE_STEP;
    }

    pTimeSyncConfig->protoCfg.vlanCfg = hTimeSyncPtp->ptpConfig.vlanCfg;
    pTimeSyncConfig->protoCfg.portMask = hTimeSyncPtp->ptpConfig.portMask;

    pTimeSyncConfig->protoCfg.ppsConfig.ppsPulseIntervalNs = hTimeSyncPtp->ptpConfig.ppsPulseIntervalNs;
    pTimeSyncConfig->protoCfg.ppsConfig.ppsNotifyCb = &TimeSyncPtp_notifyPps;
    pTimeSyncConfig->protoCfg.ppsConfig.ppsNotifyCbArg = (void *)hTimeSyncPtp;

    memcpy(&pTimeSyncConfig->protoCfg.domainNumber[0U],
           &hTimeSyncPtp->ptpConfig.domainNumber[0U],
           sizeof(hTimeSyncPtp->ptpConfig.domainNumber));

    memcpy(&pTimeSyncConfig->protoCfg.clockIdentity[0U],
           &hTimeSyncPtp->clockIdentity[0U],
           sizeof(hTimeSyncPtp->clockIdentity));

    pTimeSyncConfig->frameNotifyCfg.nwDrvHandle = hTimeSyncPtp->ptpConfig.nwDrvHandle;
    pTimeSyncConfig->frameNotifyCfg.txNotifyCb  = &TimeSyncPtp_processTxNotify;
    pTimeSyncConfig->frameNotifyCfg.txNotifyCbArg = (void *)hTimeSyncPtp;
    pTimeSyncConfig->frameNotifyCfg.rxNotifyCb = &TimeSyncPtp_processRxNotify;
    pTimeSyncConfig->frameNotifyCfg.rxNotifyCbArg = (void *)hTimeSyncPtp;

    pTimeSyncConfig->socConfig = hTimeSyncPtp->ptpConfig.socConfig;
}

static void TimeSyncPtp_stripVlanTag(TimeSyncPtp_Handle hTimeSyncPtp,
                                     uint8_t *pktBuffer,
                                     uint32_t *size)
{
    uint8_t *oldBuffer, *newBuffer;
    uint16_t etherType;

    oldBuffer = pktBuffer;
    newBuffer = pktBuffer;
    etherType = TimeSync_convBigEndianToLittleEndianHalfWord(pktBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE);

    if (etherType == TIMESYNC_PTP_VLAN_ETHERTYPE)
    {
        *size = *size - TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE;
        memcpy(newBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE,
               oldBuffer + TIMESYNC_PTP_SRC_DST_MAC_SIZE + TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE,
               ((*size) - TIMESYNC_PTP_SRC_DST_MAC_SIZE));
    }

}

