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
 * \file timeSync.h
 *
 * \brief This file contains the interface to IP abstracted functions
 *        for PTP stack
 */

/**
 * \defgroup DRV_TIMESYNC_MODULE TimeSync Driver
 *
 * The TimeSync driver provides time synchronization support to
 * CPSW and ICSS using HAL and PTP stack.
 *
 *  @{
 */

/*!
 * \defgroup TIMESYNC_HAL_API TIMESYNC HAL API
 */

/*!
 * \defgroup TIMESYNC_PTP_API TIMESYNC PTP API
 */

/* @} */

/*!
 * \addtogroup TIMESYNC_HAL_API
 * @{
 */

#ifndef TIMESYNC_H_
#define TIMESYNC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>

/* ========================================================================== */
/*                                Error Codes                                 */
/* ========================================================================== */

/**
 *  @brief Success
 */
#define TIMESYNC_OK                                                    (0)

/**
 * @brief Time Sync feature not supported
 */
#define TIMESYNC_UNABLE_TO_INIT_HAL                                    (-1)

/**
 * @brief Time Sync module is unable to create a Task
 */
#define TIMESYNC_UNABLE_TO_CREATE_TASK                                 (-2)

/**
 * @brief Time Sync module is unable to create a Semaphore
 */
#define TIMESYNC_UNABLE_TO_CREATE_SEMAPHORE                            (-3)

/**
 * @brief Time Sync module is unable to create an interrupt
 */
#define TIMESYNC_UNABLE_TO_CREATE_INTERRUPT                            (-4)

/**
 * @brief Time Sync module is unable to allocate memory
 */
#define TIMESYNC_UNABLE_TO_ALLOC_MEM                                   (-5)

/**
 * @brief Time Sync module is unable to create timer
 */
#define TIMESYNC_UNABLE_TO_CREATE_CLOCK                                (-6)

/**
 * @brief Time Sync module is unable to create a mailbox
 */
#define TIMESYNC_UNABLE_TO_CREATE_MAILBOX                              (-7)

/**
 * @brief Time Sync module is unable to create an event
 */
#define TIMESYNC_UNABLE_TO_CREATE_EVENT                                (-8)

/**
 * @brief Time Sync unsupported format
 */
#define TIMESYNC_UNSUPPORTED_FORMAT                                    (-9)

/**
   @brief Time Sync not able to initialize DMA
 */
#define TIMESYNC_DMA_INIT_FAILED                                       (-10)

/**
 * @brief Time Sync feature disabled
 */
#define TIMESYNC_FEATURE_NOT_ENABLED                                   (-11)

/**
 * @brief Time Sync handle uninitialized
 */
#define TIMESYNC_HANDLE_NOT_INITIALIZED                                (-12)

/**
 * @brief Time Sync Tx frame type invalid
 */
#define TIMESYNC_TX_FRAMETYPE_NOTVALID                                 (-13)

/**
 * @brief Time Sync Tx port number invalid
 */
#define TIMESYNC_TX_PORTNUMBER_NOTVALID                                (-14)

/**
 * @brief Time Sync Rx frame type invalid
 */
#define TIMESYNC_RX_FRAMETYPE_NOTVALID                                 (-15)

/**
 * @brief Time Sync Rx port number invalid
 */
#define TIMESYNC_RX_PORTNUMBER_NOTVALID                                (-16)

/**
 * @brief Time Sync invalid parameter
 */
#define TIMESYNC_PARAM_INVALID                                         (-17)

/**
 * @brief Time Sync feature not supported
 */
#define TIMESYNC_FEATURE_NOT_SUPPORTED                                 (-18)

/**
 * @brief Time Sync frame not available
 */
#define TIMESYNC_FRAME_NOT_AVAILABLE                                   (-19)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * @def TIMESYNC_NUM_DOMAINS
 *      Number of domains supported by this PTP implementation
 */
#define TIMESYNC_NUM_DOMAINS                                           (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * @brief Transmit callback function
 * @param[in] cbArg     Pointer to callback argument
 * @param[in] portNum   Port number to which frame was transmitted
 * @param[in] frameType PTP frame type of transmitted frame
 * @param[in] seqId     PTP sequence ID of transmitted frame
 * @return None
 */
typedef void (*TimeSync_txNotifyCb)(void *cbArg,
                                    uint8_t portNum,
                                    uint8_t frameType,
                                    uint16_t seqId);

/**
 * @brief Receive callback function
 * @param[in] cbArg     Pointer to callback argument
 * @return None
 */
typedef void (*TimeSync_rxNotifyCb)(void *cbArg);

/**
 * @brief PTP PPS callback function
 * @param[in] cbArg     Pointer to callback argument
 * @return None
 */
typedef void (*TimeSync_ppsNotifyCb)(void *cbArg);

/**
 * @brief PTP Device configuration
 */
typedef enum
{
    /** Master Clock */
    TIMESYNC_MASTER_CLOCK      = 1U,

    /** Only Transparent Clock */
    TIMESYNC_TRANSPARENT_CLOCK = 2U,

    /** Only Ordinary Clock */
    TIMESYNC_ORDINARY_CLOCK    = 3U,

    /** Both Ordinary and Transparent clock */
    TIMESYNC_OC_AND_TC         = 4U,

    /** Boundary clock */
    TIMESYNC_BOUNDARY_CLOCK    = 5U,
} TimeSync_DeviceConfig;

/**
 * @brief Network Protocol Type
 */
typedef enum
{
    /** IPv4 */
    TIMESYNC_PROT_UDP_IPV4    = 1U,

    /** IPv6 */
    TIMESYNC_PROT_UDP_IPV6    = 2U,

    /** Ethernet without TCP/IP */
    TIMESYNC_PROT_IEEE_802_3  = 3U,

    /** Device Net */
    TIMESYNC_PROT_DEVICE_NET  = 4U,

    /** Control Net */
    TIMESYNC_PROT_CONTROL_NET = 5U,

    /** PROFINET */
    TIMESYNC_PROT_PROFINET    = 6U,

    /** Unknown protocol type */
    TIMESYNC_PROT_UNKNOWN     = 0xFFFEU
} TimeSync_NetworkProtType;

/*!
 *  @brief Enum of VLAN usage type
 */
typedef enum
{
    /** No VLAN tag */
    TIMESYNC_VLAN_TYPE_NONE       = 0x00U,

    /** Single VLAN tag */
    TIMESYNC_VLAN_TYPE_SINGLE_TAG = 0x01U,

    /** Double VLAN tag */
    TIMESYNC_VLAN_TYPE_DOUBLE_TAG = 0x02U,
} TimeSync_VlanType;

/**
 * @brief PTP frame types
 */
typedef enum
{
    /** Sync frame Id */
    TIMESYNC_SYNC_FRAME                  = 0x00U,

    /** Delay request frame Id */
    TIMESYNC_DELAY_REQ_FRAME             = 0x01U,

    /** Peer delay request frame Id */
    TIMESYNC_PDELAY_REQ_FRAME            = 0x02U,

    /** Peer delay response frame Id */
    TIMESYNC_PDELAY_RESP_FRAME           = 0x03U,

    /** Followup frame Id */
    TIMESYNC_FOLLOW_UP_FRAME             = 0x08U,

    /** Delay response frame Id */
    TIMESYNC_DELAY_RESP_FRAME            = 0x09U,

    /** Peer delay response followup frame Id */
    TIMESYNC_PDELAY_RESP_FOLLOW_UP_FRAME = 0x0AU,

    /** Announce frame Id */
    TIMESYNC_ANNOUNCE_FRAME              = 0x0BU,

    /** Signaling frame Id */
    TIMESYNC_SIGNALING_FRAME             = 0x0CU,

    /** Management frame Id */
    TIMESYNC_MANAGEMENT_FRAME            = 0x0DU,
} TimeSync_FrameType;

/**
 * @brief Enum of supported SoCs
 */
typedef enum
{
   /** AM65xx SoC */
    TIMESYNC_SOC_AM65xx  = 1U,

    /** J721E SoC */
    TIMESYNC_SOC_J721E   = 2U,

    /** J7200 SoC */
    TIMESYNC_SOC_J7200   = 3U,

    /** J721S2 SoC */
    TIMESYNC_SOC_J721S2  = 4U,

    /** J784S4 SoC */
    TIMESYNC_SOC_J784S4  = 5U,

    /** Unknown SoC */
    TIMESYNC_SOC_UNKNOWN = 0xFFFE
} TimeSync_SocType;

/**
 * @brief Enum of supported IP versions
 */
typedef enum
{
    /** CPSW 2G */
    TIMESYNC_IP_VER_CPSW_2G = 1U,

    /** CPSW 9G */
    TIMESYNC_IP_VER_CPSW_9G = 2U,

    /** CPSW 5G */
    TIMESYNC_IP_VER_CPSW_5G = 3U,

    /** ICSSG Dual-MAC */
    TIMESYNC_IP_VER_ICSSG_DUALMAC = 4U,

    /** Unknown IP */
    TIMESYNC_IP_VER_UNKNOWN = 0xFFFE
} TimeSync_EthIpVer;

/**
 * @brief Enum of PTP step modes
 */
typedef enum
{
    /** PTP in single step mode */
    TIMESYNC_SINGLE_STEP = 1U,

    /** PTP in double step mode */
    TIMESYNC_DOUBLE_STEP = 2U,
} TimeSync_StepMode;

/**
 * @brief TimeSync VLAN configuration structure
 */
typedef struct
{
    /** VLAN type */
    TimeSync_VlanType vlanType;

    /** Inner VLAN tag */
    uint32_t iVlanTag;

    /** Outer VLAN tag */
    uint32_t oVlanTag;
} TimeSync_VlanConfig;

/**
 * @brief TimeSync PPS configuration structure
 */
typedef struct
{
    /** Hardware timer generates a periodic pulse, which can be used by application.
     *  When the interval(in ns) is configured to 1 second (1000000000 ns),
     *  it becomes the 1PPS signal */
    uint32_t ppsPulseIntervalNs;

    /** PTP PPS callback */
    TimeSync_ppsNotifyCb ppsNotifyCb;

    /** PTP PPS callback argument */
    void *ppsNotifyCbArg;
} TimeSync_PpsConfig;

/**
 * @brief TimeSync protocol configuration structure
 */
typedef struct
{
    /** Packet type in which PTP is encapsulated*/
    TimeSync_NetworkProtType protocol;

    /** Device's PTP mode of operation*/
    TimeSync_DeviceConfig deviceCfg;

    /** List of 802.1AS-rev domainNumbers*/
    uint8_t domainNumber[TIMESYNC_NUM_DOMAINS];

    /** Clock Identity = MAC ID + Protocol Identifier*/
    uint8_t clockIdentity[8];

    /** PTP step mode */
    TimeSync_StepMode stepMode;

    /** VLAN comfiguration*/
    TimeSync_VlanConfig vlanCfg;

    /** PTP PPS comfiguration*/
    TimeSync_PpsConfig ppsConfig;

    /** Port mask indicating ports to be used for PTP*/
    uint8_t portMask;
}TimeSync_ProtocolConfig;

/**
 * @brief TimeSync frame notify configuration structure
 */
typedef struct
{
    /** Network driver handle */
    void *nwDrvHandle;

    /** Tx callback function */
    TimeSync_txNotifyCb txNotifyCb;

    /** Tx callback argument */
    void *txNotifyCbArg;

    /** Rx callback function */
    TimeSync_rxNotifyCb rxNotifyCb;

    /** Rx callback argument */
    void *rxNotifyCbArg;
} TimeSync_FrameNotifyConfig;

/**
 * @brief TimeSync SoC configuration structure
 */
typedef struct
{
    /** SOC version */
    TimeSync_SocType socVersion;

    /** IP version */
    TimeSync_EthIpVer ipVersion;

    /** Instance Id.  Set to 0 if there is ginel instance of the Ethernet peripheral */
    uint32_t instId;
}TimeSync_SocConfig;

/**
 * @brief Time synchronization configuration structure
 */
typedef struct
{
    /** TimeSync protocol configuration */
    TimeSync_ProtocolConfig protoCfg;

    /** TimeSync frame notification configuration */
    TimeSync_FrameNotifyConfig frameNotifyCfg;

    /** TimeSync SoC configuration */
    TimeSync_SocConfig socConfig;
} TimeSync_Config;

/**
 * @brief TimeSync handle
 *
 * TimeSync opaque handle
 */
typedef struct TimeSync_Obj_s *TimeSync_Handle;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * @brief Function to configure low-level network driver
 *
 * @param[in] timeSyncConfig Pointer to time sync configuration structure
 * @return    timeSyncHandle Handle to TimeSync HAL object
 */
TimeSync_Handle TimeSync_open(TimeSync_Config *timeSyncConfig);

/**
 * @brief Reads and provides timestamp of a received event message.
 *
 * @param[in]  timeSyncHandle      Pointer to TimeSync object
 * @param[in]  rxFrameType         Frame type of received packet
 * @param[in]  rxPort              Port used for receiving packet
 * @param[in]  seqId               Sequence ID of the packet
 * @param[out] nanoseconds         Pointer to 32 bit nanoseconds field
 * @param[out] seconds             Pointer to 64 bit(48 used) seconds field
 * @return     TimeSync error code
 */
int32_t TimeSync_getRxTimestamp(TimeSync_Handle timeSyncHandle,
                                TimeSync_FrameType rxFrameType,
                                uint8_t rxPort,
                                uint16_t seqId,
                                uint32_t *nanoseconds,
                                uint64_t *seconds);

/**
 * @brief Reads and provides timestamp of a transmitted event message.
 *
 * @param[in]  timeSyncHandle      Pointer to TimeSync object
 * @param[in]  txFrameType         Frame type transmitted packet
 * @param[in]  txPort              Port used for transmit
 * @param[in]  seqId               Sequence ID of the packet
 * @param[out] nanoseconds         Pointer to 32 bit nanoseconds field
 * @param[out] seconds             Pointer to 64 bit(48 used) seconds field
 * @return     TimeSync error code
 *
 */
int32_t TimeSync_getTxTimestamp(TimeSync_Handle timeSyncHandle,
                                TimeSync_FrameType txFrameType,
                                uint8_t txPort,
                                uint16_t seqId,
                                uint32_t *nanoseconds,
                                uint64_t *seconds);

/**
 * @brief Adjusts the clock by the drift value over one Sync interval.
 *
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @param[in] adjOffset      Filtered offset from master in nanoseconds
 * @param[in] syncInterval   Sync interval
 * @return    TimeSync error code
 */
int32_t TimeSync_adjTimeSlowComp(TimeSync_Handle timeSyncHandle,
                                 int64_t adjOffset,
                                 uint32_t syncInterval);

/**
 * @brief Changes the timer value
 *
 * @param[in] timeSyncHandle      Pointer to TimeSync object
 * @param[in] nanoseconds         32 bit nanoseconds value
 * @param[in] seconds             64 bit seconds value
 * @return    TimeSync error code
 */
int32_t TimeSync_setClockTime(TimeSync_Handle timeSyncHandle,
                              uint32_t nanoseconds,
                              uint64_t seconds);

/**
 *  @brief Returns the current time on device.
 *
 * Returns the current time in
 * 1. Seconds : Seconds as on master.
 * 2. Nanoseconds : Current nanoseconds as on master.
 * The format is identical to the one followed in PTP frames for origin timestamp.
 *
 *  @param[in]  timeSyncHandle Pointer to TimeSync object
 *  @param[out] nanoseconds    Pointer to nanoseconds field
 *  @param[out] seconds        Pointer to seconds field
 *  @return     None
 */
void TimeSync_getCurrentTime(TimeSync_Handle timeSyncHandle,
                             uint32_t *nanoseconds,
                             uint64_t *seconds);

/**
 *  @brief Receive the PTP frame from hardware queue
 *
 *  @param[in]  timeSyncHandle Pointer to TimeSync object
 *  @param[out] frame          Pointer to PTP frame buffer
 *  @param[out] size           Size of received frame
 *  @param[out] rxPort         Port number frame was received
 *  @return     TimeSync error code
 */
int32_t TimeSync_getPtpFrame(TimeSync_Handle timeSyncHandle,
                             uint8_t *frame,
                             uint32_t *size,
                             uint8_t *rxPort);

/**
 *  @brief Transmit the PTP frame to the directed port
 *
 *  @param[in] timeSyncHandle Pointer to TimeSync object
 *  @param[in] frame          Pointer to PTP frame buffer
 *  @param[in] size           Size of received frame
 *  @param[in] txPort         Port number to which frame is to be sent
 *  @return    TimeSync error code
 */
int32_t TimeSync_sendPtpFrame(TimeSync_Handle timeSyncHandle,
                              uint8_t *frame,
                              uint32_t size,
                              uint8_t txPort);

/**
 *  @brief Helper function to check if single step mode is supported or not.
 *
 *  @param[in] timeSyncHandle Pointer to TimeSync object
 *  @return    TIMESYNC_OK if supported, otherwise returns TIMESYNC_FEATURE_NOT_SUPPORTED
 */
int32_t TimeSync_isSingleStepSupported(TimeSync_Handle timeSyncHandle);

/**
 * @brief Get PPS timestamp value
 *
 * Note: In case of ICSS, there are FIFO for PPS timestamps. So, based on
 *       consumption rate of timestamps by stack, maximum frequency(or minimum ppsPulseIntervalNs)
 *       will have to be fixed.
 * @param[in]  timeSyncHandle Pointer to TimeSync object
 * @param[out] nanoseconds    Pointer to nanoseconds field
 * @param[out] seconds        Pointer to seconds field
 * @return     TimeSync error code
 */
int32_t TimeSync_getPpsTs(TimeSync_Handle timeSyncHandle,
                          uint32_t *nanoseconds,
                          uint64_t *seconds);

/**
 * @brief Re-calibrate PPS compare values to align with timer's second
 *        increment. This recalibration is required when there is a huge
 *        jump in timer's value because of correction/adjustment.
 *
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @return    None
 */
void TimeSync_recalibratePps(TimeSync_Handle timeSyncHandle);

/**
 * @brief Time sync port link status helper function.
 *
 * @param[in]  timeSyncHandle Pointer to TimeSync object
 * @param[in]  portNum        Port number
 * @return     TRUE -  if link is up
 *             FALSE - if link is down.
 */
int8_t TimeSync_isPortLinkUp(TimeSync_Handle timeSyncHandle,
                             uint8_t portNum);

/**
 * @brief Time sync module reset
 *
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @return None
 */
void TimeSync_reset(TimeSync_Handle timeSyncHandle);

/**
 * @brief Time sync module close
 *
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @return None
 */
void TimeSync_close(TimeSync_Handle timeSyncHandle);

/* ========================================================================== */
/*                        IP-specific function declarations                  */
/* ========================================================================== */

/** Below functions are IP-specific. IPs without these features will return without
 *  doing anything. */

/**
 * @brief Write the MAC ID of PTP master to Firmware. BMC Algorithm calls this API.
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @param[in] parentMac      Pointer to MAC ID of master.
 * @return None
 */
void TimeSync_updateParentAddress(TimeSync_Handle timeSyncHandle,
                                  uint8_t *parentMac);

/**
 * @brief Set rate compensation factor value.
 *        This is used to communicate path rate compensation factor value
 *        to ICSS firmware, for other devices this function
 *        returns without doing anything.
 *
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @param[in] rcfValue       Rate compensation factor value
 * @return None
 */
void TimeSync_setRcf(TimeSync_Handle timeSyncHandle,
                     uint32_t rcfValue);

/**
 * @brief Set path delay for port.
 *        This is used to communicate path delay to ICSS firmware,
 *        for other devices this function returns without doing anything.
 *
 * @param[in] timeSyncHandle  Pointer to TimeSync object
 * @param[in] pathDelay       Path delay value
 * @param[in] portNum         Port number
 * @return None
 */
void TimeSync_setPathDelay(TimeSync_Handle timeSyncHandle,
                           uint32_t pathDelay,
                           uint8_t portNum);

/**
 * @brief For single step master, computation of Tx seconds and nanoseconds timestamp requires
 * some techniques to avoid a long division in firmware.
 *
 * @param[in] timeSyncHandle Pointer to TimeSync object
 * @param[in] portNum        Port number
 * @return None
 */
void TimeSync_writeTsSingleStepSync(TimeSync_Handle timeSyncHandle,
                                    uint8_t portNum);

#ifdef __cplusplus
}
#endif

#endif /* TIMESYNC_H_ */

/* @} */

