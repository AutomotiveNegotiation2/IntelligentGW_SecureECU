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
 * \file timeSync_ptp_priv.h
 *
 * \brief This file contains the private APIs to PTP stack.
 *
 */

#ifndef TIMESYNC_PTP_PRIV_H_
#define TIMESYNC_PTP_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/* OSAL Header files */
#include <ti/osal/osal.h>
#include <ti/osal/HwiP.h>
#include <ti/osal/TimerP.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/EventP.h>
#include <ti/osal/SemaphoreP.h>

#include <ti/drv/enet/examples/timesync/timeSync.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * @def TIMESYNC_PTP_DEFAULT_PDELAY_REQ_LOG_INTERVAL
 *      Default PDelay Request packet interval. Actual value is 2^value seconds
 */
#define TIMESYNC_PTP_DEFAULT_PDELAY_REQ_LOG_INTERVAL         (3U)

/**
 * @def TIMESYNC_PTP_DEFAULT_SYNC_SEND_LOG_INTERVAL
 *      Default Sync transmit interval. Actual value is 2^value seconds
 */
#define TIMESYNC_PTP_DEFAULT_SYNC_SEND_LOG_INTERVAL          (0U)

/**
 * @def TIMESYNC_PTP_DEFAULT_ANNOUNCE_SEND_LOG_INTERVAL
 *      Default Announce packet transmit interval. Actual value is 2^value seconds
 */
#define TIMESYNC_PTP_DEFAULT_ANNOUNCE_SEND_LOG_INTERVAL      (1U)

/**
 * @def TIMESYNC_PTP_DEFAULT_ANNOUNCE_TIMEOUT_LOG_INTERVAL
 *      Default Announce packet timeout. Actual value is 2^value seconds
 */
#define TIMESYNC_PTP_DEFAULT_ANNOUNCE_TIMEOUT_LOG_INTERVAL   (3U)

/**
 * @def TIMESYNC_PTP_SYNC_MSG_ID
 *      Sync message ID value
 */
#define TIMESYNC_PTP_SYNC_MSG_ID                             (0x00U)

/**
 * @def TIMESYNC_PTP_DLY_REQ_MSG_ID
 *      Delay request message ID value
 */
#define TIMESYNC_PTP_DLY_REQ_MSG_ID                          (0x01U)

/**
 * @def TIMESYNC_PTP_PDLY_REQ_MSG_ID
 *      PDelay request message ID value
 */
#define TIMESYNC_PTP_PDLY_REQ_MSG_ID                         (0x02U)

/**
 * @def TIMESYNC_PTP_PDLY_RSP_MSG_ID
 *      PDelay response message ID value
 */
#define TIMESYNC_PTP_PDLY_RSP_MSG_ID                         (0x03U)

/**
 * @def TIMESYNC_PTP_FOLLOW_UP_MSG_ID
 *      Follow up message ID value
 */
#define TIMESYNC_PTP_FOLLOW_UP_MSG_ID                        (0x08U)

/**
 * @def TIMESYNC_PTP_DLY_RESP_MSG_ID
 *      Delay response message ID value
 */
#define TIMESYNC_PTP_DLY_RESP_MSG_ID                         (0x09U)

/**
 * @def TIMESYNC_PTP_PDLY_RESP_FLW_UP_MSG_ID
 *      PDelay response follow up message ID value
 */
#define TIMESYNC_PTP_PDLY_RESP_FLW_UP_MSG_ID                 (0x0AU)

/**
 * @def TIMESYNC_PTP_ANNOUNCE_MSG_ID
 *      Announce message ID value
 */
#define TIMESYNC_PTP_ANNOUNCE_MSG_ID                         (0x0BU)

/**
 * @def TIMESYNC_PTP_MGMT_MSG_ID
 *      Management message ID value
 */
#define TIMESYNC_PTP_MGMT_MSG_ID                             (0x0DU)

/**
 * @def TIMESYNC_PTP_FLW_UP_CTRL_MSG_ID
 *      Control message ID value for Follow Up
 */
#define TIMESYNC_PTP_FLW_UP_CTRL_MSG_ID                      (0x02U)

/**
 * @def TIMESYNC_PTP_FILTER_ALPHA_COEFF
 *      Alpha coefficient for sync interval exponential filter and other filters
 */
#define TIMESYNC_PTP_FILTER_ALPHA_COEFF                      (0.85)

/**
 * @def TIMESYNC_PTP_FILTER_ALPHA_COEFF_TOD
 *      Alpha coefficient for the filter used in Time of Day synchronization
 */

#define TIMESYNC_PTP_FILTER_ALPHA_COEFF_TOD                  (0.75)

/**
 * @def TIMESYNC_PTP_SYNC_FOLLOW_UP_BUFFER_SIZE
 *      Buffer size used for Follow Up frames
 */
#define TIMESYNC_PTP_SYNC_FOLLOW_UP_BUFFER_SIZE              (64U)

/**
 * @def TIMESYNC_PTP_SYNC0_PERIOD_DIVIDER
 *      CMP1 period divided by this number makes the width of the Sync pulse
 */
#define TIMESYNC_PTP_SYNC0_PERIOD_DIVIDER                    (4U)

/**
 * @def TIMESYNC_PTP_OFFSET_THRESHOLD_FOR_RESET
 *      If offset from Master goes above this threshold it will
 *      trigger a reset. Value is in nanoseconds
 */
#define TIMESYNC_PTP_OFFSET_THRESHOLD_FOR_RESET              (250U)

/**
 * @def TIMESYNC_PTP_STABLE_FILTER_THRESHOLD
 *      When clock drift goes below this value it indicates drift has
 *      stabilized and SMA filter can kick in
 */
#define TIMESYNC_PTP_STABLE_FILTER_THRESHOLD                 (100U)

/**
 * @def TIMESYNC_PTP_PEER_DELAY_ERROR_THRESHOLD
 *      When peer delay exceeds this value it gets reset to 0
 *      Sometimes wrong values are calculated when doing peer delay
 *      calculation when clock on peer changes in between peer delay
 *      messages and because of the filter this value stays for a long time
 *      This helps in fixing it. This is set to a value much higher than
 *      max peer delay (of a 100 mtr cable)
 */
#define TIMESYNC_PTP_PEER_DELAY_ERROR_THRESHOLD              (10000U)

/**
 * @def TIMESYNC_PTP_PEER_DELAY_ERROR_THRESHOLD
 *      When line delay exceeds this value it gets reset to 0
 *      Sometimes wrong values are calculated when doing line delay
 *      calculation when master and slave clocks are synchronizing,
 *      this check prevents going into a state which results in runaway drift
 *      value is set much higher than max cable delay (of a 100 mtr cable)
 */
#define TIMESYNC_PTP_LINE_DELAY_ERROR_THRESHOLD              (10000U)

/**
 * @def TIMESYNC_PTP_NUM_SYNC_MISSED_THRESHOLD
 *      If this many consecutive sync frames are missed
 *      the DUT gets reset
 */
#define TIMESYNC_PTP_NUM_SYNC_MISSED_THRESHOLD               (3U)

/**
 * @def TIMESYNC_PTP_AVG_NUM_DELAY_MEASUREMENTS
 *      Number of values in the running average
 */
#define TIMESYNC_PTP_AVG_NUM_DELAY_MEASUREMENTS              (3U)

/*Hex Offsets for different fields in PTP Delay Req/Res Packet. Annex E*/
/*To get Annex F offsets subtract TIMESYNC_PTP_ANNEX_D_ANNEX_F_DIFF from it*/

/**
 * @def TIMESYNC_PTP_SRC_MAC_OFFSET
 *      Source MAC address offset
 */
#define TIMESYNC_PTP_SRC_MAC_OFFSET                          (6U)

/**
 * @def TIMESYNC_PTP_SRC_IP_OFFSET
 *      Source IP address offset in IP4/UDP
 */
#define TIMESYNC_PTP_SRC_IP_OFFSET                           (26U)

/**
 * @def TIMESYNC_PTP_DST_IP_OFFSET
 *      Destination IP address offset in IP4/UDP
 */
#define TIMESYNC_PTP_DST_IP_OFFSET                           (30U)

/**
 * @def TIMESYNC_PTP_IP_CHKSUM_OFFSET
 *      IP4 checksum offset in IP4/UDP
 */
#define TIMESYNC_PTP_IP_CHKSUM_OFFSET                        (40U)

/**
 * @def TIMESYNC_PTP_MSG_ID_OFFSET
 *      PTP message ID offset
 */
#define TIMESYNC_PTP_MSG_ID_OFFSET                           (42U)

/**
 * @def TIMESYNC_PTP_DOMAIN_NUM_OFFSET
 *      PTP domain number offset
 */
#define TIMESYNC_PTP_DOMAIN_NUM_OFFSET                       (46U)

/**
 *
 * Offset for PTP flags (including 2 step)
 */
#define TIMESYNC_PTP_FLAG_OFFSET                             (48U)

/**
 *  @def TIMESYNC_PTP_CORRECTION_OFFSET
 *      Offset for PTP correction field
 */
#define TIMESYNC_PTP_CORRECTION_OFFSET                       (50U)

/**
 * @def TIMESYNC_PTP_SRC_CLK_IDENTITY
 *      Offset for PTP source clock identity (MAC + protocol id)
 */
#define TIMESYNC_PTP_SRC_CLK_IDENTITY                        (62U)

/**
 * @def TIMESYNC_PTP_SRC_PORT_ID_OFFSET
 *      Offset source port id
 */
#define TIMESYNC_PTP_SRC_PORT_ID_OFFSET                      (70U)

/**
 * @def TIMESYNC_PTP_SEQ_ID_OFFSET
 *      Offset for sequence identifier (incremented every frame)
 */
#define TIMESYNC_PTP_SEQ_ID_OFFSET                           (72U)

/**
 * @def TIMESYNC_PTP_CONTROL_MSG_ID_OFFSET
 *      Offset for message id. This categorizes frames into two groups
 *      time critical and non time critical
 */
#define TIMESYNC_PTP_CONTROL_MSG_ID_OFFSET                   (74U)

/**
 * @def TIMESYNC_PTP_LOG_MSG_PERIOD
 *      Log message interval offset
 */
#define TIMESYNC_PTP_LOG_MSG_PERIOD                          (75U)

/**
 * @def TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET
 *      Offset for seconds timestamp
 */
#define TIMESYNC_PTP_REQ_RCPT_TS_SEC_OFFSET                  (76U)

/**
 * @def TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET
 *      Offset for nanoseconds timestamp
 */
#define TIMESYNC_PTP_REQ_RCPT_TS_NSEC_OFFSET                 (82U)

/**
 * @def TIMESYNC_PTP_REQ_SRC_PORT_IDENTITY
 *      Offset for requestor clock identity
 */
#define TIMESYNC_PTP_REQ_SRC_PORT_IDENTITY                   (86U)

/**
 * @def TIMESYNC_PTP_REQ_SRC_PORT_ID
 *      Offset for requestor port identity
 */
#define TIMESYNC_PTP_REQ_SRC_PORT_ID                         (94U)

/**
 * @def TIMESYNC_PTP_UTC_OFFSET
 *      Offset for UTC offset in Announce frame
 */
#define TIMESYNC_PTP_UTC_OFFSET                              (86U)

/**
 * @def TIMESYNC_PTP_PRIORITY1_OFFSET
 *      Offset for Priority 1 field in Announce frame
 */
#define TIMESYNC_PTP_PRIORITY1_OFFSET                        (89U)

/**
 * @def TIMESYNC_PTP_GM_CLK_CLASS_OFFSET
 *      Offset for GM clock class field in Announce frame
 */
#define TIMESYNC_PTP_GM_CLK_CLASS_OFFSET                     (90U)

/**
 * @def TIMESYNC_PTP_GM_CLK_ACCU_OFFSET
 *      Offset for GM clock accuracy field in Announce frame
 */
#define TIMESYNC_PTP_GM_CLK_ACCU_OFFSET                      (91U)

/**
 * @def TIMESYNC_PTP_GM_CLK_VARIANCE_OFFSET
 *      Offset for GM clock variance field in Announce frame
 */
#define TIMESYNC_PTP_GM_CLK_VARIANCE_OFFSET                  (92U)

/**
 * @def TIMESYNC_PTP_PRIORITY2_OFFSET
 *      Offset for priority 2 field in Announce frame
 */
#define TIMESYNC_PTP_PRIORITY2_OFFSET                        (94U)

/**
 * @def TIMESYNC_PTP_GM_CLK_IDENTITY_OFFSET
 *      Offset for GM clock identity field in Announce frame
 */
#define TIMESYNC_PTP_GM_CLK_IDENTITY_OFFSET                  (95U)

/**
 * @def TIMESYNC_PTP_STEPS_REMOVED_OFFSET
 *      Offset for steps removed field in Announce frame
 */
#define TIMESYNC_PTP_STEPS_REMOVED_OFFSET                    (103U)

/**
 * @def TIMESYNC_PTP_TIME_SRC_OFFSET
 *      Offset for GM time source field in Announce frame
 */
#define TIMESYNC_PTP_TIME_SRC_OFFSET                         (04U)

/**
 * @def TIMESYNC_PTP_E2E_BUFFER_OFFSET
 *      Offset for start of PTP data in UDP/IP4 frame
 */
#define TIMESYNC_PTP_E2E_BUFFER_OFFSET                       (42U)

/**
 * @def TIMESYNC_PTP_P2P_BUFFER_OFFSET
 *      Offset for start of PTP data in 802.3 frame
 */
#define TIMESYNC_PTP_P2P_BUFFER_OFFSET                       (14U)

/**
 * @def TIMESYNC_PTP_ANNEX_D_ANNEX_F_DIFF
 *      Number of Extra bytes from Annex F(802.1) to Annex E(UDP)
 */
#define TIMESYNC_PTP_ANNEX_D_ANNEX_F_DIFF                    (28U)

/**
 * @def TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE
 *      Number of extra bytes for single tagged VLAN
 */
#define TIMESYNC_PTP_SINGLE_TAG_VLAN_HDR_SIZE                (4U)

/**
 * @def TIMESYNC_PTP_DOUBLE_TAG_VLAN_HDR_SIZE
 *      Number of extra bytes for double tagged VLAN
 */
#define TIMESYNC_PTP_DOUBLE_TAG_VLAN_HDR_SIZE                (8U)

/**
 * @def TIMESYNC_PTP_HSR_CORRECTION
 *      Number of bytes in HSR Header
 */
#define TIMESYNC_PTP_HSR_CORRECTION                          (6U)

/**
 * @def TIMESYNC_PTP_SRC_DST_MAC_SIZE
 *      Num bytes in source plus destination MAC
 */
#define TIMESYNC_PTP_SRC_DST_MAC_SIZE                        (12U)

/**
 * @def TIMESYNC_PTP_TWO_STEP_MASK
 *      Mask used to extract two step bit value
 */
#define TIMESYNC_PTP_TWO_STEP_MASK                           (0x200U)

/**
 * @def TIMESYNC_PTP_RX_MAX_MTU
 *      Rx MTU value for received packets
 */
#define TIMESYNC_PTP_RX_MAX_MTU                              (1518U)

/**
 * @def TIMESYNC_PTP_SYNC_INTERVAL_PERIOD_CHANGE_THRESHOLD
 *      If current sync interval varies from previously measured sync
 *      interval by this much percentage then it triggers a PTP reset
 */
#define TIMESYNC_PTP_SYNC_INTERVAL_PERIOD_CHANGE_THRESHOLD   (60U)

/**
 * @def TIMESYNC_PTP_GPTP_NUM_DOMAINS
 *      Number of domains supported by GPTP implementation
 */
#define TIMESYNC_PTP_GPTP_NUM_DOMAINS                        (2U)

/**
 * @def TIMESYNC_PTP_HSR_ETHERTYPE
 *      Ethertype value for HSR frame
 */
#define TIMESYNC_PTP_HSR_ETHERTYPE                           (0x892F)

/**
 * @def TIMESYNC_PTP_VLAN_ETHERTYPE
 *      Ethertype value for VLAN frame
 */
#define TIMESYNC_PTP_VLAN_ETHERTYPE                          (0x8100)

/**
 * @def TIMESYNC_PTP_SYNT_DEPTH
 *      Syntonization depth.
 *      No. of timestamps stored to do RCF & NRR calculation
 */
#define TIMESYNC_PTP_SYNT_DEPTH                              (3U)

/** Below are the masks used for PTP state machine */

/**
 * @def TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE
 *      Bit 0. Indicates that driver has copied TS value
 *      directly to IEP registers*/
#define  TIMESYNC_PTP_STATE_MACHINE_FIRST_ADJUSTMENT_DONE    (1U)
/**
 * @def TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED
 *      Bit 1. Indicates that Peer delay or
 *       Line delay (in case of E2E) has been computed
 */
#define  TIMESYNC_PTP_STATE_MACHINE_LINE_DELAY_COMPUTED      (2U)
/**
 * @def TIMESYNC_PTP_STATE_MACHINE_SYNC_INTERVAL_COMPUTED
 *      Bit 2. Sync interval computed
 */
#define  TIMESYNC_PTP_STATE_MACHINE_SYNC_INTERVAL_COMPUTED   (4U)
/**
 * @def TIMESYNC_PTP_STATE_MACHINE_READY_FOR_SYNC
 *      Mask for all three bits.
 *      Indicates that driver is now ready to do synchronization
 */
#define  TIMESYNC_PTP_STATE_MACHINE_READY_FOR_SYNC           (7U)

/**
 * @def TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC
 *      Bit 3. Device is in sync with master
 *      This is continuously monitored
 */
#define  TIMESYNC_PTP_STATE_MACHINE_DEVICE_IN_SYNC           (8U)

/**
 * @def TIMESYNC_PTP_OFFSET_ALGO_BIN_SIZE
 *      Bin size used for stabilization algo
 *      See design doc for details
 */
#define TIMESYNC_PTP_OFFSET_ALGO_BIN_SIZE                    (5U)

/**
 * @def TIMESYNC_PTP_OFFSET_ALGO_CLUSTER_SIZE
 *      Number of entries used for clustering
 *      See design doc for details
 */
#define TIMESYNC_PTP_OFFSET_ALGO_CLUSTER_SIZE                (3U)

/**
 * @defgroup TIMESYNC_PTP_API PTP/1588 APIs
 */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * @brief Time synchronization configuration structure
 */
typedef struct
{
    /*Rx buffers*/
    uint8_t *pdelayReqRxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];
    uint8_t *pdelayResRxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];
    uint8_t *pdelayResFlwUpRxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /*For E2E master. Not supported right now*/
    uint8_t *delayReqRxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /*Tx buffers*/
    uint8_t *pdelayReqTxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];
    uint8_t *pdelayResTxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];
    uint8_t *pdelayResFlwUpTxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];
    uint8_t *syncTxBuf;
    uint8_t *announceTxBuf;
    uint8_t *followUpTxBuf[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];
    uint8_t *delayReqTxBuf;

    /*Buffer sizes. These change based on whether
     * it's Annex E or Annex F. Pdelay buffer size and
     * delay request (E2E) buffer sizes are fixed
     * because we only support fixed modes*/
    uint8_t syncBufSize;
    uint8_t flwUpBufSize;
    uint8_t announceBufSize;
} TimeSyncPtp_FrameBuffers;

/**
 * @brief Runtime variables for Time Sync implementation
 */
typedef struct
{
    /**Enable/Disable status*/
    uint8_t enabled;

    /**PTP State machine. This is a bitmask*/

    /**
     * @brief PTP State machine used internally by driver
     * This is a bitmap
     * Bit 0 : Set 1 if First adjustment done
     * Bit 1 : Set 1 if delay has been computed
     * Bit 2 : Set 1 if sync interval has been computed
     * Bit 3 : Set 1 if device is in sync with master
     * if first 3 bits are set then clock adjustment is performed
     */
    uint8_t stateMachine;

    /**Sequence ID to be sent for Delay Request/Pdelay Request packets*/
    uint16_t pDelReqSequenceID[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Sequence ID of received peer delay request packet*/
    uint16_t rxPDelReqSequenceID[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Sequence ID used for Delay request frames*/
    uint16_t delReqSequenceID;

    /**Sequence ID used for Sync frames*/
    uint16_t syncSequenceID[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Sequence ID used for announce frames*/
    uint16_t announceSequenceID[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Current sequence id from Sync frame*/
    uint16_t curSyncSeqId[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Sync interval between last two sync frames*/
    uint64_t currSyncInterval;

    /**Long term average calculated using an exponential filter*/
    uint64_t ltaSyncInterval;

    /**First sync interval value*/
    uint64_t firstSyncInterval;

    /**Offset from master : current value*/
    int64_t currOffset;

    /**Offset from master : present value*/
    int32_t prevOffset;

    /**Initial offset. Taken when adjustment settles down.*/
    int64_t initialOffset;

    /*Once drift stabilizes, this is set to 1*/
    uint8_t driftStable;

    /*Once offset becomes zero, this is set to 1*/
    uint8_t offsetStable;

    /**Port number on which master is connected*/
    uint8_t syncPortNum;

    /**Line delay or Peer Delay for each port*/
    uint32_t pathDelay[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /*Place holder to calculate line delay.
     * Since line delay can sometimes be negative, we need a persistent variable*/
    int64_t meanPathDelay;

    /**Difference between current and previous offset*/
    uint32_t clockDrift;

    /*long term average of offset. Compare with initial offset to find drift*/
    int64_t ltaOffset;

    /**Running average of correction field in Sync frame*/
    uint32_t avgCorrectionField;

    /**background tick counter, increments inside
     * TimeSyncPtp_backgroundTask()  */
    uint64_t tickCounter;

    /**Ageing counter to detect missed Sync frames*/
    uint32_t syncLastSeenCounter;

    /**Ageing counter is compared against this value
     * to detect missed sync frames. 1.5x the sync interval*/
    uint64_t syncTimeoutInterval;

    /**Flag to indicate that forced 2-step mode is active*/
    uint8_t forced2step[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /*debug*/
    uint8_t bmcaDone;
} TimeSyncPtp_RuntimeVar;

/**
 * @brief Variables used for offset stabilization
 * algorithm
 */
typedef struct
{
    /**Count for last sync which had drift
     * lower than threshold. This index keeps incrementing
     * for every sync frame and gets reset to 0 if it
     * crosses a threshold.
     */
    uint8_t lastSeenGoodDriftIndex;

    /**Only offsets lower than this threshold are
     * recorded for purpose of stabilization
     */
    uint8_t driftThreshold;

    /**Counter for recording the offsets*/
    uint8_t numEntriesIndex;

    /**Indicating to the averaging algo to process
     * the data in the array
     */
    uint8_t binFull;

    /**Array of correction values with
     * low drift which are clustered together
     */
    int32_t correction[TIMESYNC_PTP_OFFSET_ALGO_BIN_SIZE];
} TimeSyncPtp_OffsetStableAlgo;

/**
 * @brief Parameters required for calculating Cable Delay
 */
typedef struct
{
    /**Set to 1 if Two step sync frame*/
    uint8_t ifTwoStep;

    /**Correction Field. Nanoseconds. Contains sum of sync and followup correction fields
     * in case master is a two step clock*/
    uint64_t correctionField;

    /**Timestamp (seconds). If it's a followup packet then it's precise origin timestamp of follow up*/
    uint64_t originTsSec;
    /**Timestamp in nanoseconds.If it's a followup packet then it's precise origin timestamp of follow up*/
    uint32_t originTsNs;

    /**Input timestamp of Sync Frame*/
    uint32_t rxTs;

    /**Input timestamp of Sync Frame in seconds*/
    uint64_t rxTsSec;

    /**Transmit timestamp of Sync frame on other port in nanoseconds*/
    uint32_t txTs;

    /**Transmit timestamp of Sync frame on other port in Seconds*/
    uint64_t txTsSec;
} TimeSyncPtp_SyncParam;

/**
 * @brief Parameters required for clock syntonization
 */
typedef struct
{
    /**Sync RX TS*/
    uint64_t syncIngressTs[TIMESYNC_PTP_SYNT_DEPTH];

    /**Corrected master TS*/
    uint64_t correctedMasterTs[TIMESYNC_PTP_SYNT_DEPTH];

    /**Syntonization factor*/
    double rcf;

    /**Internal index for book keeping*/
    uint8_t index;

    /** enable syntonization flag*/
    uint8_t syntEnable;

    /**Internal index for book keeping*/
    uint32_t syntIndex;
} TimeSyncPtp_SyntInfo;

/**
 * @brief Parameters required for doing Time of Day synchronization
 */
typedef struct
{
    /**PPS timestamp in nanoseconds*/
    uint32_t pPsTsNS;

    /**PPS timestamp in seconds*/
    uint64_t pPsTsSec;

    /**Time of day timestamp in nanoseconds*/
    uint32_t toDTsNS;

    /**Time of day timestamp in seconds*/
    uint64_t toDTsSec;
} TimeSyncPtp_ToDParams;

/**
 * @brief Parameters required for calculating Nighbor Rate Ratio
 */
typedef struct
{
    /**Rx TS of Peer Delay response*/
    uint64_t deviceRxTS[TIMESYNC_PTP_SYNT_DEPTH];

    /**Origin timestamp of Peer Delay response received in Follow Up*/
    uint64_t correctedPeerTS[TIMESYNC_PTP_SYNT_DEPTH];

    /**Neighbor rate ratio*/
    double nrr;

    /**Internal index for book keeping*/
    uint8_t curIndex;

    /** enable syntonization flag*/
    uint8_t nrrEnable;

    /**Internal index for book keeping*/
    uint32_t nrrIndex;
} TimeSyncPtp_NrrInfo;

/**
 * @brief Parameters required for calculating Cable Delay
 */
typedef struct
{
    /**Correction Field. Nanoseconds*/
    uint64_t correctionField;

    /**Delay Response Rx Timestamp on master in (seconds)*/
    uint64_t timeStampSec;
    /**Delay Response Rx Timestamp on master in nanoseconds*/
    uint32_t timeStampNS;

    /**Delay Request Tx Timestamp in Seconds*/
    uint32_t delReqTxTsSec;
    /**Delay Request Tx Timestamp in Nanoseconds*/
    uint32_t delReqTxTsNS;
} TimeSyncPtp_DelayReqRespParams;

/**
 * @brief Parameters required for calculating Cable Delay
 */
typedef struct
{
    /**Set to 1 if Two step Peer delay response*/
    uint8_t ifTwoStep;

    /**Delay Request TX timestamp or T1. In Seconds*/
    uint32_t T1Sec;

    /**Delay Request TX timestamp or T1. In Nanoseconds*/
    uint32_t T1Nsec;

    /**Delay Request Receipt Timestamp T2. In Seconds*/
    uint64_t T2Sec;

    /**Delay Request Receipt Timestamp T2. In Nanoseconds*/
    uint32_t T2Nsec;

    /**Original Delay Response Tx TS (On Peer). In Seconds*/
    uint64_t T3Sec;

    /**Original Delay Response Tx TS (On Peer). In Nanoseconds*/
    uint32_t T3Nsec;

    /**Delay Response receipt Rx TS. In Seconds*/
    uint64_t T4Sec;

    /**Delay Response receipt Rx TS. In Nanoseconds*/
    uint32_t T4Nsec;

    /**Rx timestamp of Peer delay request received. In seconds
     * Used for replying with a peer delay response*/
    uint64_t pDelayReqRcvdTSSec;

    /**Rx timestamp of Peer delay request received. In nanoseconds
     * Used for replying with a peer delay response*/
    uint32_t pDelayReqRcvdTSNsec;

    /**Delay Response Correction Field. T3 - T2. In NS*/
    uint64_t delayResCorrField;

    /**Delay Response Follow Up Correction Field. In NS*/
    uint64_t delayResFwUpCorrField;
} TimeSyncPtp_PeerDelayParams;

/**
 * @brief Used to populate IP/UDP Parameters. These must be populated from Switch params
 */
typedef struct
{
    /**Source IP Address*/
    uint32_t srcIP;

    /**Destination IP Address*/
    uint32_t dstIP;

    /**DSCP Field. Not used right now*/
    uint8_t dscp;

    /**TTL Value, copy from Switch config params or Stack params*/
    uint8_t ttlVal;
} TimeSyncPtp_IpParams;

/**
 * @brief PTPd stack parameters
 */
typedef struct
{
    /**Set this to indicate to PTPd that new frame is available*/
    uint8_t generalFrameFlag;
    /**PTPd stack frame buffer*/
    uint8_t ptpGeneralFrame[1518];
    /**Size of frame to be copied by PTPd*/
    uint16_t ptpGeneralSize;

    /**MAC id of Announce frame, PTPd has no way of knowing the MAC ID without this
     * Revisit the design
     */
    uint8_t ptpSrcMacID[6];
} TimeSyncPtp_PtpDparams;

/**
 * @brief Time synchronization PTP parameter handle structure
 */
typedef struct TimeSyncPtp_Obj_s
{
    /**PTP Enable/Disable status*/
    uint8_t enabled;

    /** Copy of PTP configuration */
    TimeSyncPtp_Config ptpConfig;

    /* TimeSync HAL configuration */
    TimeSync_Config timeSyncCfg;

    /** Handle to TimeSync HAL driver */
    TimeSync_Handle timeSyncHandle;

    /** Sync interval(nanoseconds) */
    uint32_t syncInterval;

    /**PTPd stack parameters*/
    TimeSyncPtp_PtpDparams stackParams;

    /**Line delay or Peer Delay for each port*/
    uint32_t pathDelay[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /*Syntonization index mapping.
     * This is a fixed mapping with a gap of 1 index for syntonization */
    uint8_t syntIndexMap[3];

    /*Syntonization previus index mapping.
     * This is a fixed mapping with a gap of 1 index for syntonization */
    uint8_t prevIndexMap[3];

    /**Clock Identity = MAC ID + Protocol Identifier*/
    uint8_t clockIdentity[8];

    /** Port number to which master clock is connected */
    uint8_t masterPortNum;

    /**Time Sync Task handle for Delay Request Task which sends task periodically*/
    TaskP_Handle pDelayReqSendTask;

    /**Time Sync Task handle for sending a delay request to Master on receiving a Sync*/
    TaskP_Handle delayReqSendTask;

    /**-----------------Slave tasks, semaphores and events----------------*/
    /**PTP Task for storing Tx timestamps */
    TaskP_Handle txTsTask[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**For processing frames like
     * Pdelay Request, Pdelay Response
     * and Pdelay Response Follow Up which
     * don't require real time response
     */
    TaskP_Handle nRTTask;

    /**Used to do resource intensive but non-critical tasks
     * like doing floating point calculations, algorithms,
     * status monitoring etc
     */
    TaskP_Handle backgroundTask;

    /**Event handle for indicating that a Tx Timestamp interrupt
     * has been generated and needs to be serviced. index 0 contains
     * handle for Port 1.
     */
    EventP_Handle txTSAvailableEvtHandle[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Two event handlers for two ports
     * for processing Pdelay response
     * and Pdelay response follow up
     */
    EventP_Handle ptpPdelayResEvtHandle[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Two event handlers for two ports
     * for processing Pdelay request frames
     */
    EventP_Handle ptpPdelayReqEvtHandle[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Two event handlers for two ports
     * for sending out follow up frame in case of forced 2-step
     */
    EventP_Handle ptpSendFollowUpEvtHandle[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Event ID for Sync frame*/
    uint32_t eventIdSync;

    /**Event ID for Pdelay Request frame*/
    uint32_t eventIdPdelayReq;

    /**Event ID for Pdelay Response frame*/
    uint32_t eventIdPdelayResp;

    /**Event ID for Pdelay Response Follow Up frame*/
    uint32_t eventIdPdelayRespFlwUp;

    /**Event ID for Delay Request frame*/
    uint32_t eventIdDelayReq;

    /**Event ID to indicate follow up frame generated*/
    uint32_t eventIdFlwUpGenerated;

    /*Semaphore for sending Delay Request frames*/
    SemaphoreP_Handle delayReqTxSemHandle;

    /*Semaphore handle used to post packet transmission notification */
    SemaphoreP_Handle pktTxSemHandle;

    /*Semaphore for indicating packet reception */
    SemaphoreP_Handle pktRxSemHandle;

    /**-----------------Master tasks, semaphores and events----------------*/
    /** Handle for timer which posts the semaphore which in turn sends Sync frames */
    ClockP_Handle syncTxTimer;

    /** Tx packet notify task handle*/
    TaskP_Handle pktTxNotifyTask;

    /** Rx packet notify task handle*/
    TaskP_Handle pktRxNotifyTask;

    /**Actual PTP Task handle which sends Sync frames*/
    TaskP_Handle syncTxTask;

    /**PTP Task for sending Announce frames*/
    TaskP_Handle announceTxTask;

    /*Semaphore for sending Sync frames as master*/
    SemaphoreP_Handle syncTxSemHandle;

    /**Task is used to synchronize with the 1PPS output*/
    TaskP_Handle ppsTask;

    /*Semaphore for synchronizing to 1PPS out*/
    SemaphoreP_Handle ppsSemHandle;

    /*Number of sync frames missed*/
    uint32_t numSyncMissed;

    TimeSyncPtp_OffsetStableAlgo offsetAlgo;

    /**IP/UDP Params*/
    TimeSyncPtp_IpParams udpParams;

    /**Peer Delay params*/
    TimeSyncPtp_PeerDelayParams pDelayParams[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Delay params for Delay Response*/
    TimeSyncPtp_DelayReqRespParams delayParams;

    /*Rx and Tx frame buffers*/
    TimeSyncPtp_FrameBuffers timeSyncBuff;

    /**Data for Syntonization*/
    TimeSyncPtp_SyntInfo tsSyntInfo;

    /**Parameters for doing time of day synchronization*/
    TimeSyncPtp_ToDParams tsToDParams;

    /**Data for calculating NRR on both ports*/
    TimeSyncPtp_NrrInfo tsNrrInfo[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Delay params for Sync Frame*/
    TimeSyncPtp_SyncParam syncParam[TIMESYNC_PTP_MAX_PORTS_SUPPORTED];

    /**Time Sync Runtime variables*/
    TimeSyncPtp_RuntimeVar tsRunTimeVar;
} TimeSyncPtp_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * @brief Do initial adjustment for the IEP based on sync timestamp
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param portNum ICSS_EMAC_PORT_1 or ICSS_EMAC_PORT_2
 * @return None
 */
void TimeSyncPtp_doFirstAdjustment(TimeSyncPtp_Handle timeSyncPtpHandle,
                                   uint8_t portNum);

/**
 * @brief Processes a PTP Announce message and extract fields
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param pktBuffer pointer to packet data
 * @param portNum port number on which the packet was received
 * @param size size of the packet
 * @param isLinkLocal
 *
 * @return none
 */
void TimeSyncPtp_processPtpFrame(TimeSyncPtp_Handle hTimeSyncPtp,
                                 uint8_t *pktBuffer,
                                 uint8_t portNum,
                                 uint32_t size,
                                 uint8_t isLinkLocal);

/**
 * @brief Retuns the previous master's MAC ID. BMC Algorithm calls this.
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param prevMac Pointer to MAC ID of previous master.
 * @return none
 */
void TimeSyncPtp_getPrevAddress(TimeSyncPtp_Handle timeSyncPtpHandle,
                                uint8_t *prevMac);

/**
 * @brief Copies the PTP announce message data to PTP stack buffer.
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param buff Pointer to buffer of PTP Stack.
 * @return none
 */
void TimeSyncPtp_getGeneralMessage(TimeSyncPtp_Handle timeSyncPtpHandle,
                                   int8_t *buff);

/**
 * @brief When application receives the Time of Day information, it calls this API
 * with the seconds and nanoseconds fields. This starts the time of day synchronization
 * mechanism.
 * Assumption : Latch0 input is also enabled and is being fed by 1PPS output
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param nanoseconds Nanoseconds component of time of day
 * @param seconds Seconds component of time of day
 * @return Error value
 */
int8_t TimeSyncPtp_processTimeOfDay(TimeSyncPtp_Handle timeSyncPtpHandle,
                                    uint32_t nanoseconds,
                                    uint64_t seconds);

/**
 * @internal
 * @brief Get the timestamp of transmitted frame and process if required
 * This is called by both TIMESYNC_PTP_TxTSTask_P1 and TIMESYNC_PTP_TxTSTask_P2 tasks with port number as input
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @param  portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @param frameType Whether Sync, Delay req or Delay response
 * @return none
 */
void TimeSyncPtp_getTxTs(TimeSyncPtp_Handle timeSyncPtpHandle,
                         uint8_t portNum,
                         TimeSync_FrameType frameType);

/**
 * @internal
 * @brief Calculate Line Delay given the parameters from Delay Response
 * This is called from inside the interrupt context
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @return none
 */
void TimeSyncPtp_lineDelayCalc(TimeSyncPtp_Handle timeSyncPtpHandle);

/**
 * @internal
 * @brief Calculate Peer Delay given the parameters from Peer Delay Req/Res
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param twoStep Indicates if calculation is through 2 step mechanism
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_peerDelayCalc(TimeSyncPtp_Handle timeSyncPtpHandle,
                               uint8_t twoStep,
                               uint8_t portNum);

/**
 * @internal
 * @brief Process Sync/Follow Up frames and do synchronization
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param buff pointer to the sync and follow up frame
 * @param followUp Set to 1 if it's a follow up frame else 0
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @param size size of the frame
 * @return none
 */
void TimeSyncPtp_processSyncFrame(TimeSyncPtp_Handle timeSyncPtpHandle,
                                  uint8_t *buff,
                                  uint8_t followUp,
                                  uint8_t portNum,
                                  uint32_t size);

/**
 * @internal
 * @brief Process Pdelay response frame
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param buff pointer to the Pdelay Response Frame
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_processDelayResFrame(TimeSyncPtp_Handle timeSyncPtpHandle,
                                      uint8_t *buff,
                                      uint8_t portNum);

/**
 * @internal
 * @brief Process Pdelay request frame
 * @param timeSyncPtpHandle pointer to PTP Handle structure
 * @param buff pointer to the Pdelay Request Frame
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_processPdelayReqFrame(TimeSyncPtp_Handle timeSyncPtpHandle,
                                       uint8_t *buff,
                                       uint8_t portNum);

/**
 * @internal
 * @brief Process Pdelay response and Pdelay response followUp frame
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @param buff pointer to the Pdelay Response/Response Follow Up Frame
 * @param followUp 0 if it's a response frame, 1 if response follow up
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_processPdelayRespFrame(TimeSyncPtp_Handle timeSyncPtpHandle,
                                        uint8_t *buff,
                                        uint8_t followUp,
                                        uint8_t portNum);

/**
 * @internal
 * @brief Called for forced 2-step mode. Sends out follow up frame with bridge delay
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_forced2StepBDCalc(TimeSyncPtp_Handle timeSyncPtpHandle,
                                   uint8_t portNum);

/**
 * @internal
 * @brief Synchronize clock upon receipt of Sync Frame. Applicable for OC
 * This is called from inside the interrupt context
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @return none
 */
void TimeSyncPtp_synchronizeClock(TimeSyncPtp_Handle timeSyncPtpHandle);

/**
 * @internal
 * @brief Calculate Neighbor rate ratio for adjacent nodes
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_calcNRR(TimeSyncPtp_Handle timeSyncPtpHandle,
                         uint8_t portNum);

/**
 * @internal
 * @brief Updates NRR info which is subsequently used to calculate
 * the final NRR value
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @param portNum port number. ICSS_EMAC_PORT_1/ICSS_EMAC_PORT_2
 * @return none
 */
void TimeSyncPtp_updateNRRParams(TimeSyncPtp_Handle timeSyncPtpHandle,
                                 uint8_t portNum);

/**
 * @internal
 * @brief Calculate rcf for syntonization from line delay parameters
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @return none
 */
void TimeSyncPtp_calcRcfAndSyncInterval(TimeSyncPtp_Handle timeSyncPtpHandle);

/**
 * @internal
 * @brief Called internally to process latch0 timestamp and synchronize internal clock
 * to the rising edge of 1PPS signal
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @return none
 */
void TimeSyncPtp_synchronizeToD(TimeSyncPtp_Handle timeSyncPtpHandle);

/**
 * @internal
 * @brief This is similar to TimeSyncPtp_calcRcfAndSyncInterval, instead
 * of sync packet interval it calculates interval between latch0 triggers.
 * And there is no RCF calculation.
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @return none
 */
void TimeSyncPtp_calcSyncIntervalToD(TimeSyncPtp_Handle timeSyncPtpHandle);

/**
 * @internal
 * @brief Dummy BMCA which takes first sync frame sender as master.
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 * @param  pktBuffer pointer to first sync frame
 * @param  portNum port number in which first sync was received
 *
 * @return none
 */
void TimeSyncPtp_BMCA(TimeSyncPtp_Handle timeSyncPtpHandle,
                      uint8_t *pktBuffer,
                      uint8_t portNum);

/**
 * @internal
 * @brief Enable boundary clock mode. This starts periodic task to
 * send sync messages.
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 *
 * @return none
 */
void TimeSyncPtp_enableBoundaryClock(TimeSyncPtp_Handle hTimeSyncPtp);

/**
 * @internal
 * @brief Disable boundary clock mode. This stops periodic task to
 * send sync messages.
 * @param  timeSyncPtpHandle pointer to PTP Handle structure
 *
 * @return none
 */
void TimeSyncPtp_disableBoundaryClock(TimeSyncPtp_Handle hTimeSyncPtp);

#endif /* TIMESYNC_PTP_PRIV_H_ */
