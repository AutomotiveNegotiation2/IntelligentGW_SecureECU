/*
*
* Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     EthApp.c
 *
 *  \brief    This file contains the target-side Eth test application code.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "string.h"
#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"

#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
#include "Os.h"

#include "Eth_GeneralTypes.h"
#include "Eth.h"
#include "Eth_Irq.h"
#include "Eth_Cfg.h"
#include "EthIf_Cbk.h"
#include "EcuM_Cbk.h"
#include "EthTrcv.h"
#include "Eth_IrqPacing.h"

#include <EthUtils.h>

#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/osal/osal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if (STD_ON == ETH_VIRTUALMAC_SUPPORT)
#error "ETH_VIRTUALMAC_SUPPORT is not supported by this Ethernet test app"
#endif
#if (STD_ON == ETH_ZERO_COPY_TX)
#error "ETH_ZERO_COPY_TX is not supported by this Ethernet test app"
#endif
#if (STD_ON == ETH_USE_Q_APIS)
#error "ETH_USE_Q_APIS is not supported by this Ethernet test app"
#endif

/* \brief ENET offset value for enet control register */
#define CTRL_MMR0_CFG0_ENET_OFFSET(macPort)     (((macPort)-1)*0x4u)

/** \brief Unlock value for lock kick 0 */
#define MMR_KICK0_UNLOCK_VAL            (0x68EF3490U)

/** \brief Unlock value for lock kick 1 */
#define MMR_KICK1_UNLOCK_VAL            (0xD172BC5AU)

/** \brief RGMII_ID_MODE shift value in CTRLMMR_MCU_ENET_CTRL register */
#define ENET_CTRL_RGMII_ID_SHIFT        (4U)

/** \brief No internal TX delay in RGMII interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_RGMII_ID_INTTXDLY     ((boolean)0U)

/** \brief Internal TX delay in RGMII interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_RGMII_ID_NODELAY      ((boolean)1U)

/** \brief RMII port interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_MODE_RMII             (1U)

/** \brief RGMII port interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_MODE_RGMII            (2U)

/** \brief Packet transmit retry in non-confirmation mode */
#define ETHAPP_TRANSMIT_RETRY_COUNT     (2U)

#define PIN_MODE(mode)                  ((mode) & 0xFU)
#define PIN_PULL_DISABLE                (0x1U << 16U)
#define PIN_PULL_DIRECTION              (0x1U << 17U)
#define PIN_INPUT_ENABLE                (0x1U << 18U)
#define PIN_OUTPUT_DISABLE              (0x1U << 21U)
#define PIN_WAKEUP_ENABLE               (0x1U << 29U)
#define PIN_INPUT                       (PIN_PULL_DISABLE | PIN_INPUT_ENABLE)
#define PIN_OUTPUT                      (PIN_PULL_DISABLE)

#define CPSW_STATS_BLOCK_ELEM_NUM       (128U)

#define ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM              (39U)
#define ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM              (40U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef boolean (*TestFunc)(void);

/** \brief Ethernet test statistics (not to be confused with Ethernet statistics) */
typedef struct EthApp_Stats_s
{
    volatile uint32 txPktCnt;
    /**< Number of data transmitted packets (Eth_Transmit()) */

    volatile uint32 txConfPktCnt;
    /**< Number of confirmed transmit packets (Eth_TxConfirmation()) */

    volatile uint32 txBufLenErr;
    /**< Number of buffer requests with BUFREQ_E_OVFL error (Eth_ProvideTxBuffer()) */

    volatile uint32 txBufProvErr;
    /**< Number of buffer requests with BUFREQ_E_NOT_OK error (Eth_ProvideTxBuffer()) */

    volatile uint32 txPktErr;
    /**< Number of data transmit errors (Eth_Transmit()) */

    volatile uint32 rxPktCnt;
    /**< Number of data received packets (Eth_Receive() or EthIf_RxIndication()) */

    volatile uint32 rxExp3PktCnt;
    /**< Number of data received packets with experimental 3 type (EthIf_RxIndication()) */

    volatile uint32 rxExp3BytesCnt;
    /**< Number of data received packets (Eth_Receive() or EthIf_RxIndication()) */

    volatile uint32 rxExp1PktCnt;
    /**< Number of data received packets with experimental 1 type (EthIf_RxIndication()) */

    volatile uint32 rxExp2PktCnt;
    /**< Number of data received packets with experimental 2 type (EthIf_RxIndication()) */

    volatile uint32 rxVlanPktCnt;
    /**< Number of data received packets with VLAN tag (EthIf_RxIndication()) */

    volatile uint32 rxPktNotRecv;
    /**< Number of times Eth_Receive() returned packet not received */

    volatile uint32 rxPktIndCnt;
    /**< Number of indicated receive packets (EthIf_RxIndication()) */

    volatile uint32 rxEtherTypeErr;
    /**< Number of packets with an unexpected EtherType field (EthIf_RxIndication()) */

    volatile uint32 rxPayloadErr;
    /**< Number of packets with unexpected payload (EthIf_RxIndication()) */

    volatile uint32 rxCtrlIdxErr;
    /**< Number of packets with unexpected controller index (EthIf_RxIndication()) */

    volatile uint32 rxBcastErr;
    /**< Number of packets with unexpected broadcast flag */

    volatile uint32 rxLenErr;
    /**< Number of packets with invalid buffer length */

    volatile uint32 ctrlModeActCnt;
    /**< Number of controller mode changes to ETH_MODE_ACTIVE (Eth_SetControllerMode()) */

    volatile uint32 ctrlModeDownCnt;
    /**< Number of controller mode changes to ETH_MODE_ACTIVE (Eth_SetControllerMode()) */

    volatile uint32 ctrlModeErr;
    /**< Number of controller mode changes with error (Eth_SetControllerMode()) */

    volatile uint32 ctrlModeIndActCnt;
    /**< Number of controller mode changes to ETH_MODE_ACTIVE (EthIf_CtrlModeIndication()) */

    volatile uint32 ctrlModeIndDownCnt;
    /**< Number of controller mode changes to ETH_MODE_DOWN (EthIf_CtrlModeIndication()) */

    volatile uint32 ctrlModeIndErr;
    /**< Invalid controller mode errors (EthIf_CtrlModeIndication()) */

    volatile uint32 filterUcastAddErr;
    /** Number of filter "add" action errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterUcastRemErr;
    /** Number of filter "add" action (unicast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterUcastRxErr;
    /** Number of errors while receiving unicast packets */

    volatile uint32 filterMcastAddErr;
    /** Number of filter "remove" action (multicast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterMcastRemErr;
    /** Number of filter "remove" action (multicast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterMcastRxErr;
    /** Number of errors while receiving multicast packets */

    volatile uint32 filterBcastErr;
    /** Number of filter "add" action (broadcast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterBcastRxErr;
    /** Number of errors while receiving broadcast packets */

    volatile uint32 filterBcastTxErr;
    /** Number of errors while transmitting broadcast packets */

    volatile uint32 filterNullErr;
    /** Number of filter "add" action (null) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterNullRxErr;
    /** Number of errors while receiving unicast packets */

    volatile uint32 etherGetCountValuesErr;
    /**< Ethernet get counter values errors (Eth_GetCounterValues()) */

    volatile uint32 etherGetRxStasErr;
    /**< Ethernet get Rx statistics errors (Eth_GetRxStats()) */

    volatile uint32 etherGetTxStasErr;
    /**< Ethernet get Tx statistics errors (Eth_GetTxStats()) */

    volatile uint32 etherGetTxErrStasErr;
    /**< Ethernet get Tx error statistics errors (Eth_GetTxErrorCounterValues()) */

    volatile uint32 demErr;
    /**< DEM errors (Dem_SetEventStatus()) */

    volatile uint32 detErr;
    /**< DET errors (Det_ReportError()) */
} EthApp_Stats;

/** \brief Ethernet test state */
typedef struct EthApp_State_s
{
    uint8 ctrlIdx;
    /**< Controller index */

    uint8 macAddr[ETH_MAC_ADDR_LEN];
    /**< MAC address of the controller */

    volatile boolean runTest;
    /**< Whether test should be running or not */

    boolean saveRxFrame;
    /**< Whether or not the received frame should be saved */

    EthFrame rxFrame;
    /**< Receive frame to copy receive data into in some tests */

    EthApp_Stats stats;
    /**< Test statistics (not to be confused with Ethernet statistics) */

    boolean verbose;
    /**< Enable verbose */

    boolean veryVerbose;
    /**< Enable very verbose logs */

    boolean saveRxTime;
    /* Enable save Rx Time flags */

    uint16 rxFrameCnt;
    /* Rx frame counter */

    Eth_TimeStampType saveRxTimeStamp[ETH_TEST_ITER_S_COUNT];
    /* Rx frame timestamp */

    boolean saveTxTime;
    /* Enable save Tx Time flags */

    uint16 txFrameCnt;
    /* Tx frame counter */

    Eth_TimeStampType saveTxTimeStamp[ETH_TEST_ITER_S_COUNT];
    /* Tx frame timestamp */

    uint8 rxIrqDisable;
    /* Disable or enable Rx irq */

    uint8 txIrqDisable;
    /* Disable or enable Tx irq */
} EthApp_State;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void EthApp_delay(uint32 msecs);

static void EthApp_Startup(void);

static void EthApp_interruptConfig(void);

static void EthApp_setCpsw0Pinmux(void);

static void EthApp_setConnectionType(uint32 macPortNum, Eth_MacConnectionType type, boolean delay);

/* Main Eth / EthTrcv initialization/deinitialization functions */

static Std_ReturnType EthApp_init(uint8 ctrlIdx);

static Std_ReturnType EthApp_deinit(uint8 ctrlIdx);

static Std_ReturnType EthApp_trcvInit(const EthTrcv_ConfigType *cfg);

/* Callbacks */

void EthIf_TxConfirmation(uint8 ctrlIdx,
                          Eth_BufIdxType bufIdx,
                          Std_ReturnType result);

void EthIf_RxIndication(uint8 ctrlIdx,
                        Eth_FrameType FrameType,
                        boolean IsBroadcast,
                        uint8 *PhysAddrPtr,
                        Eth_DataType *DataPtr,
                        uint16 lenByte);

void EthIf_CtrlModeIndication(uint8 ControllerId,
                              Eth_ModeType ControllerMode);

void EthIf_TrcvModeIndication(uint8 Dem_SetEventStatus,
                              EthTrcv_ModeType TrcvMode);

/* Test helper functions */

static BufReq_ReturnType EthApp_provideTxBuffer(uint8 ctrlIdx,
                                                uint8 priority,
                                                Eth_BufIdxType* bufIdxPtr,
                                                uint8** bufPtr,
                                                uint16* lenBytePtr);

static void EthApp_send(uint8 ctrlIdx,
                        EthFrame *frame,
                        uint16 len);

static void EthApp_sendCmd(uint8 ctrlIdx,
                           uint8 cmd);

static boolean EthApp_transmit(uint8 ctrlIdx,
                               uint32 num,
                               uint16 len,
                               boolean txConfirmation,
                               boolean vlan,
                               uint8 *dstAddr);

static boolean EthApp_receive(uint8 ctrlIdx,
                              uint32 num);

static Std_ReturnType EthApp_showStats(uint8 ctrlIdx);

static const char *EthApp_errorIdToString(uint8 moduleId, uint8 errorId);

static const char *EthApp_apiIdToString(uint8 moduleId, uint8 apiId);

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
static Std_ReturnType EthApp_getTranceiverLinkState(uint8 trcvIdx);
#endif

void EthApp_wbInvCache(uint8 *buf, uint16 len);

void EthApp_invCache(uint8 *buf, uint16 len);


/* Test cases */

/**
 * \brief Test basic frame reception
 *
 * Basic DUT frame reception test.  The target side performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0001(void);

/**
 * \brief Test basic frame transmission
 *
 * Basic DUT frame transmission test.  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged frames without confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0002(void);

/**
 * \brief Test external loopback
 *
 * External loopback test.  The target side sends frames to the host, the host
 * receives the frames and sends them back to the target.  The following operations
 * are performed on the target side:
 * - Send START command
 * - Send and receive ETH_TEST_ITER_M_COUNT frames, for each of them:
 *   o A different payload is set
 *   o EtherType and payload are verified on the received frame
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0003(void);

/**
 * \brief Test default filter operation
 *
 * Test the operation of the default DUT's filter configuration (only frames with
 * DUT's MAC address are accepted, all others are rejected).  The target side
 * performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT / 2 as
 * only one half of the total frames sent by the host have the DUT's MAC address.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0004(void);

#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
/**
 * \brief Test different filter configurations
 *
 * Test the different modes of the DUT's filter configuration.  The target side performs
 * these operations:
 * - Send START command
 * - Part 1
 *   o Filter is reset to accept only frames with DUT's MAC address
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be rejected
 *     - Expected to receive ETH_TEST_ITER_M_COUNT / 2 frames
 * - Part 2
 *   o A second unicast MAC address is added to the DUT's filter
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is second valid MAC address. It should be accepted
 *     - Expected to receive ETH_TEST_ITER_M_COUNT frames
 * - Part 3
 *   o A multicast address is added to the DUT's filter
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is multicast address. It should be accepted
 *     - Expected to receive ETH_TEST_ITER_M_COUNT frames
 * - Part 4
 *   o The multicast address is removed from the DUT's filter
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is multicast address. It should be rejected
 *     - Expected to receive ETH_TEST_ITER_M_COUNT / 2 frames
 * - Part 5
 *   o The filter is opened up (promiscuous mode)
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be accepted
 *     - Expected to receive ETH_TEST_ITER_M_COUNT frames
 * - Part 6
 *   o The filter is reset back to accept only DUT's unicast address
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be rejected
 *     - Expected to receive ETH_TEST_ITER_M_COUNT / 2 frames
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0005(void);
#endif /* (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API) */

/**
 * \brief Test frame transmission with confirmation
 *
 * DUT frame transmission test with TX confirmation.  The target side performs
 * these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged frames with confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0006(void);

/**
 * \brief Test frame transmission of VLAN tagged frames
 *
 * DUT frame transmission test of VLAN tagged frames.  The target side performs
 * these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT VLAN tagged frames with confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0007(void);

/**
 * \brief Test frame transmission of different lengths
 *
 * DUT frame transmission test of different frame lengths, including short frames
* (less than 64 octets).  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_S_COUNT frames for lengths starting at 10 octets in
 *   increments of 10 octets until 1500 octets.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0008(void);

/**
 * \brief Test VLAN tagged frame reception
 *
 * DUT VLAN tagged frame reception test.  The target side performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0009(void);

/**
 * \brief Test controller mode change
 *
 * Controller mode change test.  The target performs the following operations:
 * - Send START command
 * - Run ETH_TEST_ITER_S_COUNT iterations of:
 *   o Set controller mode to DOWN state
 *   o Set controller mode to ACTIVE state
 *   o Transmit frames (run test 0002)
 *   o Receive frames (run test 0001)
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0010(void);

/**
 * \brief Test multicast frame transmission
 *
 * Multicast frame transmission test.  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged multicast frames without
 *   confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0011(void);

/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput over "frames" frames with frame size is "size"
 * . The target performs the following operations:
 * - Get the initial timestamp corresponding to the first frame received
 * - Receive frames until the STOP is detected and get the final timestamp
 * - Compute the transmit throughput from the number of received frames and the
 *   time difference between the two captured timestamps
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0100(uint32 frames, uint32 size);

/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput for multiple frame size. The target
 * performs the following operations:
 * - with each frame size and frame number call EthApp_test_0010
 *   to calculate throughput for that frame szie
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0110(void);

/**
 * \brief Measure DUT receive throughput
 *
 * Measure DUT receive throughput.
 * . The target performs the following operations:
 * - Get the initial timestamp corresponding to the first frame received
 * - Receive frames until the STOP is detected and get the final timestamp
 * - Compute the receive throughput from the number of received frames and the
 *   time difference between the two captured timestamps
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0101(void);

/**
 * \brief Test internal loopback
 *
 * Internal loopback test (MAC).
 * - Send and receive ETH_TEST_ITER_M_COUNT frames, for each of them:
 *   o A different payload is set
 *   o EtherType and payload are verified on the received frame
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0200(void);

/* Egress timestamp test */
boolean EthApp_test_0300(void);

/* Ingress timestamp test */
boolean EthApp_test_0301(void);

/* Get current time test */
boolean EthApp_test_0302(void);

/* Traffic shaping test */
#if (STD_ON == ETH_WRAPPER_ENABLED)
boolean EthApp_test_0400(void);
#endif /* (STD_ON == ETH_WRAPPER_ENABLED) */

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
/**
 * \brief Test MDIO Operation
 *
 * Stress testing of MDIO Read Operation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0500(void);
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static TestFunc testFuncs[] =
{
    &EthApp_test_0001,
    &EthApp_test_0002,
    &EthApp_test_0003,
    &EthApp_test_0004,
#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
    &EthApp_test_0005,
#endif
    &EthApp_test_0006,
    &EthApp_test_0007,
    &EthApp_test_0008,
    &EthApp_test_0009,
    &EthApp_test_0010,
    &EthApp_test_0011,
    &EthApp_test_0300,
    &EthApp_test_0301,
    &EthApp_test_0302,
    &EthApp_test_0110,
    &EthApp_test_0101,
#if (STD_ON == ETH_WRAPPER_ENABLED)
    &EthApp_test_0400,
#endif
#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
    &EthApp_test_0500,
#endif
};

/* Broadcast MAC address */
static uint8 BcastAddr[ETH_HW_ADDR_LEN] =
{
    0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU
};

#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
static uint8 TargetMcastAddr[ETH_HW_ADDR_LEN] =
{
    0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U
};

/* Null MAC address */
static uint8 NullAddr[ETH_HW_ADDR_LEN] =
{
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

/* Unicast MAC address */
static uint8 UcastAddr[ETH_HW_ADDR_LEN] =
{
    0x0aU, 0x0bU, 0x0cU, 0x0dU, 0x0eU, 0x0fU
};

/* Multicast MAC address */
static uint8 McastAddr[ETH_HW_ADDR_LEN] =
{
    0x01U, 0x00U, 0x5eU, 0x0dU, 0x0eU, 0x0fU
};

/* Transmit Multicast MAC address */
static uint8 TxMcastAddr[ETH_HW_ADDR_LEN] =
{
    0x33U, 0x33U, 0x00U, 0x00U, 0x00U, 0x01U
};
#endif

/* CtrOffs to Stat Name Mapping */
const char *CtrOffsToName[CPSW_STATS_BLOCK_ELEM_NUM+1] =
{
    "RxGoodFrames",
    /**< Total number of good frames received */
    "RxBCastFrames",
    /**< Total number of good broadcast frames received */
    "RxMCastFrames",
    /**< Total number of good multicast frames received */
    "RxPauseFrames",
    /**< Total number of pause frames received */
    "RxCRCErrors",
    /**< Total number of CRC errors frames received */
    "RxAlignCodeErrors",
    /**< Total number of alignment/code error frames received */
    "RxOversized",
    /**< Total number of oversized frames received */
    "RxJabber",
    /**< Total number of jabber frames received */
    "RxUndersized",
    /**< Total number of undersized frames received */
    "RxFragments",
    /**< Total number of fragmented frames received */
    "RxAleDrop",
    /**< Total number of frames dropped by the ALE */
    "RxAleOverrunDrop",
    /**< Total number of overrun frames dropped by the ALE */
    "RxOctets",
    /**< Total number of received bytes in good frames */
    "TxGoodFrames",
    /**< Total number of good frames transmitted */
    "TxBCastFrames",
    /**< Total number of good broadcast frames transmitted */
    "TxMCastFrames",
    /**< Total number of good multicast frames transmitted */
    "TxPauseFrames",
    /**< Total number of bytes in all good frames transmitted */
    "TxDeferred",
    /**< Total number of deferred frames transmitted */
    "TxCollision",
    /**< Total number of transmitted frames experiencing a collision */
    "TxSingleColl",
    /**< Total number of transmitted frames experiencing a single
     *   collision */
    "TxMultiColl",
    /**< Total number of transmitted frames experiencing multiple
     *   collisions */
    "TxExcessiveColl",
    /**< Total number of transmitted frames abandoned due to excessive
     *   collisions */
    "TxLateColl",
    /**< Total number of transmitted frames abandoned due to a late
     *   collision */
    "RxIpgError",
    /**< Total number of receive inter-packet gap errors */
    "TxCarrierSLoss",
    /**< Total number of transmitted frames that experienced a
     *   carrier loss */
    "TxOctets",
    /**< Total number of bytes in all good frames transmitted */
    "Frame64",
    /**< Total number of 64-byte frames received and transmitted */
    "Frame65t127",
    /**< Total number of frames of size 65 to 127 bytes received and
     *   transmitted */
    "Frame128t255",
    /**< Total number of frames of size 128 to 255 bytes received and
     *   transmitted */
    "Frame256t511",
    /**< Total number of frames of size 256 to 511 bytes received and
     *   transmitted */
    "Frame512t1023",
    /**< Total number of frames of size 512 to 1023 bytes received and
     *   transmitted */
    "Frame1024tUp",
    /**< Total number of frames of size 1024 to rx_maxlen bytes received
     *   and 1024 bytes or greater transmitted */
    "NetOctets",
    /**< Total number of bytes received and transmitted */
    "RxDropBottom",
    /**< Total number of received frames dropped due to Receive Bottom
     *   of FIFO */
    "PortmaskDrop",
    /**< Total number of received frames dropped due to portmask */
    "RxDropTop",
    /**< Total number of received frames dropped due to Top of FIFO */
    "AleRateLimitDrop",
    /**< Total number of dropped frames due to ALE rate limiting */
    "AleVidDrop",
    /**< Total number of dropped frames due to ALE VID ingress */
    "AleAddrEqDrop",
    /**< Total number of dropped frames due to DA = SA */
    "AleBlockDrop",
    /**< Total number of dropped frames due to ALE Block Mode */
    "AleSecureDrop",
    /**< Total number of dropped frames due to ALE Secure Mode */
    "AleAuthDrop",
    /**< Total number of dropped frames due to ALE Authentication */
    "AleUnKnUni",
    /**< ALE receive unknown unicast */
    "AleUnKnUniBytes",
    /**< ALE receive unknown unicast bytecount */
    "AleUnKnMulti",
    /**< ALE receive unknown multicast */
    "AleUnKnMultiBytes",
    /**< ALE receive unknown multicast bytecount */
    "AleUnKnBCast",
    /**< ALE receive unknown brodcast */
    "AleUnKnBCastBytes",
    /**< ALE receive unknown broadcast bytecount */
    "AlePolMatch",
    /**< ALE Policer matched */
    "AlePolMatchRed",
    /**< ALE Policer Matched and Condition Red */
    "AlePolMatchYellow",
    /**< ALE Policer Matched and Condition Yellow */
    "AleMultSrcAddrDrop",
    /**< ALE Multicast Source Address Drop */
    "AleDualVlanDrop",
    /**< ALE Dual VLAN Drop */
    "AleLenErrDrop",
    /**< ALE Length Error Drop */
    "AleNextHdrDrop",
    /**< ALE IP Next Header Drop */
    "AleIPv4FragDrop",
    /**< ALE IPV4 Frag Drop */
    "Reserve1[00]",
    "Reserve1[01]",
    "Reserve1[02]",
    "Reserve1[03]",
    "Reserve1[04]",
    "Reserve1[05]",
    "Reserve1[06]",
    "Reserve1[07]",
    "Reserve1[08]",
    "Reserve1[09]",
    "Reserve1[10]",
    "Reserve1[11]",
    "Reserve1[12]",
    "Reserve1[13]",
    "Reserve1[14]",
    "Reserve1[15]",
    "Reserve1[16]",
    "Reserve1[17]",
    "Reserve1[18]",
    "Reserve1[19]",
    "Reserve1[20]",
    "Reserve1[21]",
    "Reserve1[22]",
    "Reserve1[23]",
    /**< Reserved area (24 words) */
    "IETRxAssemblyErr",
    /**< IET Receive Assembly Error */
    "IETRxAssemblyOK",
    /**< IET Receive Assembly OK */
    "IETRxSmdErr",
    /**< IET Receive Smd Error */
    "IETRxFrag",
    /**< IET Receive Frag */
    "IETTxHold",
    /**< IET Transmit Hold */
    "IETTxFrag",
    /**< IET Transmit Frag */
    "Reserve2[0]",
    "Reserve2[1]",
    "Reserve2[2]",
    "Reserve2[3]",
    "Reserve2[4]",
    "Reserve2[5]",
    "Reserve2[6]",
    "Reserve2[7]",
    "Reserve2[8]",
    /**< Reserved area (9 words) */
    "TxMemProtectErr",
    /**< Transmit Memory Protect CRC Error */
    "TxPriPktCnt[0]",
    "TxPriPktCnt[1]",
    "TxPriPktCnt[2]",
    "TxPriPktCnt[3]",
    "TxPriPktCnt[4]",
    "TxPriPktCnt[5]",
    "TxPriPktCnt[6]",
    "TxPriPktCnt[7]",
    /**< Tx Priority [0-7] Packet Count */
    "TxPriByteCnt[0]",
    "TxPriByteCnt[1]",
    "TxPriByteCnt[2]",
    "TxPriByteCnt[3]",
    "TxPriByteCnt[4]",
    "TxPriByteCnt[5]",
    "TxPriByteCnt[6]",
    "TxPriByteCnt[7]",
    /**< Tx Priority [0-7] Packet Byte Count */
    "TxPriDropPktCnt[0]",
    "TxPriDropPktCnt[1]",
    "TxPriDropPktCnt[2]",
    "TxPriDropPktCnt[3]",
    "TxPriDropPktCnt[4]",
    "TxPriDropPktCnt[5]",
    "TxPriDropPktCnt[6]",
    "TxPriDropPktCnt[7]",
    /**< Tx Priority [0-7] Packet Drop Count */
    "TxPriDropByteCnt[0]",
    "TxPriDropByteCnt[1]",
    "TxPriDropByteCnt[2]",
    "TxPriDropByteCnt[3]",
    "TxPriDropByteCnt[4]",
    "TxPriDropByteCnt[5]",
    "TxPriDropByteCnt[6]",
    "TxPriDropByteCnt[7]",
    /**< Tx Priority [0-7] Packet Drop Byte Count */
    "<END>"
};

/* Eth application state */
EthApp_State gEthApp;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32 i,ti;
    boolean status;
    boolean globalStatus = TRUE;
    Std_ReturnType retVal;
#if (STD_OFF == ETH_PRE_COMPILE_VARIANT)
    /* this time configuration is not ready yet */
    extern CONST(Eth_ConfigType, ETH_VAR_NO_INIT) EthConfigSet_0;
    extern P2CONST(Eth_ConfigType, ETH_VAR_NO_INIT, ETH_APPL_CONST) Eth_CfgPtr;
    Eth_CfgPtr = (Eth_ConfigType *)&EthConfigSet_0;
#endif

#ifdef UART_ENABLED
    AppUtils_Init();
#endif
    /* Initialize the global app structure */
    gEthApp.ctrlIdx = EthConf_EthCtrlConfig_EthConfig_0;
    gEthApp.verbose = FALSE;
    gEthApp.veryVerbose = FALSE;
    gEthApp.txIrqDisable = FALSE; /* default is using TX IRQ */
    gEthApp.rxIrqDisable = FALSE; /* default is using RX IRQ */

    if (Eth_GetTxEnableInterrupt(gEthApp.ctrlIdx) == FALSE)
    {
        gEthApp.txIrqDisable = TRUE;
    }

    if (Eth_GetRxEnableInterrupt(gEthApp.ctrlIdx) == FALSE)
    {
        gEthApp.rxIrqDisable = TRUE;
    }

    memset(&gEthApp.macAddr, 0U, ETH_MAC_ADDR_LEN);
    memset(&gEthApp.stats, 0U, sizeof(EthApp_Stats));

    /* Print date and time */
    EthUtils_printf("Eth Application build date/time: %s, %s\n", __DATE__, __TIME__);

    EthUtils_printf("Eth Application Starts\n");

    /* System initialization */
    EthApp_Startup();

#if (STD_OFF == ETH_PRE_COMPILE_VARIANT)
    Eth_CfgPtr = (Eth_ConfigType *)NULL_PTR;
#endif

    /* Initialize the Eth driver and controller */
    retVal = EthApp_init(gEthApp.ctrlIdx);
    if (E_OK != retVal)
    {
        EthUtils_printf("Failed to initialize: %d\n", retVal);
        return retVal;
    }

    /* Main test section */
    if (E_OK == retVal)
    {
        if (Eth_GetLoopBackMode(gEthApp.ctrlIdx))
        {
            status = EthApp_test_0200();
            globalStatus &= status;
            EthUtils_printf("Test 0200: %s\n", status?"Pass":"Fail");
        }
        else
        {
            for(ti = 0u; ti < ETH_APP_TEST_ROUND; ti++)
            {
                /* Send command indicating that we're ready to start the test stage */
                EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_READY);


                for (i = 0U; i < ARRAY_SIZE(testFuncs); i++)
                {
                    EthUtils_printf("\n\n-----------------------------------------------------------\n");
                    memset(&gEthApp.stats, 0U, sizeof(EthApp_Stats));
                    status = testFuncs[i]();
                    globalStatus &= status;
                    EthUtils_printf("Test Result: %s %d\n", status?"Pass":"Fail", ti);
                    EthUtils_printf("-----------------------------------------------------------\n");
                    if(status != 1)
                        break;
                }
                if(status != 1)
                    break;

                EthApp_delay(2000);
            }
        }
    }
    EthUtils_printf("\n");

    /* Show statistics */
    if (E_OK == retVal)
    {
        retVal = EthApp_showStats(gEthApp.ctrlIdx);
        if (E_OK != retVal)
        {
            EthUtils_printf("main: failed to show statistics\n");
        }
    }

    /* Deinitialize the Ethernet controller */
    if (E_OK == retVal)
    {
        retVal = EthApp_deinit(gEthApp.ctrlIdx);
        if (E_OK != retVal)
        {
            EthUtils_printf("Failed to deinitialize: %d\n", retVal);
        }
    }

    EthUtils_printf("ETH Stack Usage: %d bytes\n", AppUtils_GetStackUsage());
    if (AppUtils_EthCheckStackAndSectionCorruption() != E_OK)
    {
        retVal = E_NOT_OK;
        EthUtils_printf("ETH Stack/section corruption!!!\n");
    }

    EthUtils_printf("Tests Results: %s\n",
                    (globalStatus == TRUE) ? "PASS" : "FAIL");

    if (E_OK == retVal)
    {
        EthUtils_printf("Eth Application Completed\n");
    }
    else
    {
        EthUtils_printf("Eth Application Failed\n");
    }

    return 0;
}

static void EthApp_delay(uint32 msecs)
{
    TickType count = 1000000U * msecs;
    TickType start = 0U;
    TickType elapsed = 0U;
    StatusType status;

    status = GetCounterValue(ETH_OS_COUNTER_ID, &start);

    while ((E_OK == status) && (count >= elapsed))
    {
        status = GetElapsedValue(ETH_OS_COUNTER_ID, &start, &elapsed);
    }
}

static void EthApp_Startup(void)
{
    EthApp_setCpsw0Pinmux();
    EthApp_setConnectionType(Eth_GetMacPortNum(gEthApp.ctrlIdx),
        Eth_GetMiiConnectionType(gEthApp.ctrlIdx),
        ENET_CTRL_RGMII_ID_NODELAY);

    /* Equivalent to EcuM_AL_SetProgrammableInterrupts */
    Intc_Init();

    EthApp_interruptConfig();
    Intc_SystemEnable();

    /* Initialize counters, that would be required for timed operations */
    AppUtils_ProfileInit(0);

    /* Initialize memory sections  */
    AppUtils_EthSectionInit();
}

#define ETH_START_SEC_ISR_CODE
#include "Eth_MemMap.h"

ETH_ISR_TEXT_SECTION void Eth_MdioIrqHdlr_0_wrapper(uintptr_t arg)
{
#if (STD_ON == ETH_ENABLE_MII_API)
    Eth_MdioIrqHdlr_0();
#endif
}

ETH_ISR_TEXT_SECTION void Eth_TxIrqHdlr_0_wrapper(uintptr_t arg)
{
    Eth_TxIrqHdlr_0();
}

ETH_ISR_TEXT_SECTION void Eth_RxIrqHdlr_0_wrapper(uintptr_t arg)
{
    Eth_RxIrqHdlr_0();
}

ETH_ISR_TEXT_SECTION void Eth_TxIrqPacingHdlr_0_wrapper(uintptr_t arg)
{
    Eth_TxIrqPacingHdlr_0();
}

ETH_ISR_TEXT_SECTION void Eth_RxIrqPacingHdlr_0_wrapper(uintptr_t arg)
{
    Eth_RxIrqPacingHdlr_0();
}

#define ETH_STOP_SEC_ISR_CODE
#include "Eth_MemMap.h"

static void EthApp_interruptConfig(void)
{
    OsalRegisterIntrParams_t intrPrms;
    OsalInterruptRetCode_e retVal;
    HwiP_Handle hwiHandle;

    /* MDIO interrupt */
    Osal_RegisterInterrupt_initParams(&intrPrms);
    intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
    intrPrms.corepacConfig.isrRoutine      = &Eth_MdioIrqHdlr_0_wrapper;
    intrPrms.corepacConfig.priority        = 1U;
    intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
    intrPrms.corepacConfig.intVecNum       = CSLR_MCU_R5FSS0_CORE0_INTR_MCU_CPSW0_MDIO_PEND_0;
    retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
    if (OSAL_INT_SUCCESS != retVal)
    {
        EthUtils_printf("interruptConfig: failed to register MDIO int: %d\n", retVal);
    }

    if(gEthApp.txIrqDisable == FALSE)
    {
        /* TX DMA completion interrupt */
        if (OSAL_INT_SUCCESS == retVal)
        {
            Osal_RegisterInterrupt_initParams(&intrPrms);
            intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
            intrPrms.corepacConfig.isrRoutine      = &Eth_TxIrqHdlr_0_wrapper;
            intrPrms.corepacConfig.priority        = 1U;
            intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
            intrPrms.corepacConfig.intVecNum       =  Eth_GetTxEventCoreIntrNum(gEthApp.ctrlIdx);

            retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
            if (OSAL_INT_SUCCESS != retVal)
            {
                EthUtils_printf("interruptConfig: failed to register TX DMA int: %d\n", retVal);
            }
        }
    }

    if(gEthApp.rxIrqDisable == FALSE)
    {
        /* RX DMA completion interrupt */
        if (OSAL_INT_SUCCESS == retVal)
        {
            Osal_RegisterInterrupt_initParams(&intrPrms);
            intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
            intrPrms.corepacConfig.isrRoutine      = &Eth_RxIrqHdlr_0_wrapper;
            intrPrms.corepacConfig.priority        = 1U;
            intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
            intrPrms.corepacConfig.intVecNum       = Eth_GetRxEventCoreIntrNum(gEthApp.ctrlIdx);

            retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
            if (OSAL_INT_SUCCESS != retVal)
            {
                EthUtils_printf("interruptConfig: failed to register RX DMA int: %d\n", retVal);
            }
        }
    }

    if(TRUE == Eth_GetRxIrqPacingEnable(gEthApp.ctrlIdx))
    {
        Osal_RegisterInterrupt_initParams(&intrPrms);
        intrPrms.corepacConfig.arg          = (uintptr_t)NULL_PTR;
        intrPrms.corepacConfig.isrRoutine   = &Eth_RxIrqPacingHdlr_0_wrapper;
        intrPrms.corepacConfig.priority     = 1U;
        intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
        intrPrms.corepacConfig.intVecNum    = ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM;

        retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
        if(OSAL_INT_SUCCESS != retVal)
        {
            EthUtils_printf("interruptConfig: failed to register GPT int: %d\n", retVal);
        }
    }

    if(TRUE == Eth_GetTxIrqPacingEnable(gEthApp.ctrlIdx))
    {
        Osal_RegisterInterrupt_initParams(&intrPrms);
        intrPrms.corepacConfig.arg          = (uintptr_t)NULL_PTR;
        intrPrms.corepacConfig.isrRoutine   = &Eth_TxIrqPacingHdlr_0_wrapper;
        intrPrms.corepacConfig.priority     = 1U;
        intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
        intrPrms.corepacConfig.intVecNum    = ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM;

        retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
        if(OSAL_INT_SUCCESS != retVal)
        {
            EthUtils_printf("interruptConfig: failed to register GPT int: %d\n", retVal);
        }
    }
}

static void EthApp_setCpsw0Pinmux(void)
{
    CSL_wkup_ctrl_mmr_cfg0Regs *regs =
        (CSL_wkup_ctrl_mmr_cfg0Regs *)(uintptr_t)CSL_WKUP_CTRL_MMR0_CFG0_BASE;

    CSL_REG32_WR(&regs->LOCK2_KICK0, MMR_KICK0_UNLOCK_VAL);
    CSL_REG32_WR(&regs->LOCK2_KICK1, MMR_KICK1_UNLOCK_VAL);
    CSL_REG32_WR(&regs->LOCK7_KICK0, MMR_KICK0_UNLOCK_VAL);
    CSL_REG32_WR(&regs->LOCK7_KICK1, MMR_KICK1_UNLOCK_VAL);

#if defined (SOC_J784S4)
    /* MCU_CPSW -> MCU_RGMII1_TX_CTL -> C38 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG26, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RX_CTL -> C37 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG27, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD3 -> E38 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG28, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD2 -> E37 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG29, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD1 -> D38 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG30, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD0 -> D37 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG31, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TXC -> E36 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG32, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RXC -> B37 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG33, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD3 -> D36 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG34, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD2 -> C36 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG35, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD1 -> B36 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG36, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD0 -> A35 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG37, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDIO -> B35 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG38, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDC -> A36 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG39, PIN_MODE(0U) | PIN_OUTPUT);

    /* WKUP_GPIO0 -> WKUP_GPIO0_3 -> J36 (J784S4X) */
    CSL_REG32_WR(&regs->PADCONFIG51, PIN_MODE(7U) | PIN_INPUT);
#elif defined (SOC_J721E)
    /* MCU_CPSW -> MCU_RGMII1_TX_CTL -> B27 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG22, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RX_CTL -> C25 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG23, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD3 -> A28 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG24, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD2 -> A27 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG25, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD1 -> A26 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG26, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD0 -> B25 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG27, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TXC -> B26 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG28, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RXC -> C24 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG29, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD3 -> A25 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG30, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD2 -> D24 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG31, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD1 -> A24 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG32, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD0 -> B24 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG33, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDIO -> E23 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG34, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDC -> F23 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG35, PIN_MODE(0U) | PIN_OUTPUT);

    /* WKUP_GPIO0 -> WKUP_GPIO0_3 -> F27 (DRA721E) */
    CSL_REG32_WR(&regs->PADCONFIG47, PIN_MODE(7U) | PIN_INPUT);
#elif defined (SOC_J7200)
    /* MCU_CPSW -> MCU_RGMII1_TX_CTL -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG26, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RX_CTL -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG27, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD3 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG28, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD2 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG29, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD1 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG30, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD0 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG31, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TXC -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG32, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RXC -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG33, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD3 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG34, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD2 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG35, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD1 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG36, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD0 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG37, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDIO -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG38, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDC -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG39, PIN_MODE(0U) | PIN_OUTPUT);

    /* WKUP_GPIO0 -> WKUP_GPIO0_3 -> X (J7200) */
    CSL_REG32_WR(&regs->PADCONFIG51, PIN_MODE(7U) | PIN_INPUT);
#elif defined (SOC_J721S2)
    /* MCU_CPSW -> MCU_RGMII1_TX_CTL -> F22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG26, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RX_CTL -> E23 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG27, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD3 -> E22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG28, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD2 -> E21 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG29, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD1 -> G22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG30, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TD0 -> F23 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG31, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_TXC -> F21 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG32, PIN_MODE(0U) | PIN_OUTPUT);

    /* MCU_CPSW -> MCU_RGMII1_RXC -> D22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG33, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD3 -> D23 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG34, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD2 -> C22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG35, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD1 -> B21 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG36, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_CPSW -> MCU_RGMII1_RD0 -> B22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG37, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDIO -> A22 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG38, PIN_MODE(0U) | PIN_INPUT);

    /* MCU_MDIO0 -> MCU_MDIO0_MDC -> A21 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG39, PIN_MODE(0U) | PIN_OUTPUT);

    /* WKUP_GPIO0 -> WKUP_GPIO0_56 -> G27 (J721S2) */
    CSL_REG32_WR(&regs->PADCONFIG72, PIN_MODE(7U) | PIN_INPUT);
#else
#error "Unsupported SoC"
#endif
}

static void EthApp_setConnectionType(uint32 macPortNum, Eth_MacConnectionType type, boolean delay)
{
    CSL_mcu_ctrl_mmr_cfg0Regs *regs =
        (CSL_mcu_ctrl_mmr_cfg0Regs *)(uintptr_t)CSL_MCU_CTRL_MMR0_CFG0_BASE;
    uint32 val;

    val = ENET_CTRL_RGMII_ID_NODELAY << ENET_CTRL_RGMII_ID_SHIFT;

    switch (type)
    {
    case ETH_MAC_CONN_TYPE_RMII_10:
    case ETH_MAC_CONN_TYPE_RMII_100:
        val |= ENET_CTRL_MODE_RMII;
        break;
    case ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF:
    case ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL:
    case ETH_MAC_CONN_TYPE_RGMII_FORCE_1000_FULL:
    case ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND:
        val |= ENET_CTRL_MODE_RGMII;
        break;
    default:
        break;
    }

    /* Set MAC port interface in MMR */
    CSL_REG32_WR(&regs->LOCK1_KICK0, MMR_KICK0_UNLOCK_VAL);
    CSL_REG32_WR(&regs->LOCK1_KICK1, MMR_KICK1_UNLOCK_VAL);
    CSL_REG32_WR(&regs->MCU_ENET_CTRL, val);
}

static Std_ReturnType EthApp_init(uint8 ctrlIdx)
{
    const Eth_ConfigType *ethCfg = (const Eth_ConfigType *)NULL_PTR;
    const EthTrcv_ConfigType *ethTrcvCfg = (const EthTrcv_ConfigType *)NULL_PTR;
    Std_ReturnType retVal;

    /* Eth driver initialization */
#if (STD_OFF == ETH_PRE_COMPILE_VARIANT)
    extern CONST(Eth_ConfigType, ETH_VAR_NO_INIT) EthConfigSet_0;
    ethCfg = (const Eth_ConfigType *)&EthConfigSet_0;
#endif

    Eth_Init(ethCfg);

    /* Set controller to active mode */
    retVal = Eth_SetControllerMode(ctrlIdx, ETH_MODE_ACTIVE);
    if (E_OK != retVal)
    {
        EthUtils_printf("init: failed to set the controller to active mode\n");
    }

    /* Print initial physical address */
    if (E_OK == retVal)
    {
        Eth_GetPhysAddr(ctrlIdx, gEthApp.macAddr);
        EthUtils_printf("MAC Port %d Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
                        ctrlIdx + 1,
                        gEthApp.macAddr[0U], gEthApp.macAddr[1U], gEthApp.macAddr[2U],
                        gEthApp.macAddr[3U], gEthApp.macAddr[4U], gEthApp.macAddr[5U]);
    }

    /* Initialize the transceiver */
    if ((FALSE == Eth_GetLoopBackMode(gEthApp.ctrlIdx)) && (E_OK == retVal))
    {
#if (STD_OFF == ETHTRCV_PRE_COMPILE_VARIANT)
        ethTrcvCfg = ETHTRCV_DRV_CONFIG_0;
#else
        ethTrcvCfg = (const EthTrcv_ConfigType *)NULL_PTR;
#endif
        retVal = EthApp_trcvInit(ethTrcvCfg);
        if (E_OK != retVal)
        {
            EthUtils_printf("init: failed to initialize transceiver\n");
        }
    }

    /* Subscribe to spl mcast address used by host app to send mcast frames.
     * HostApp sends mcast frames with non-broadcast address so that
     * broadcast frames in network from Host PC/other machines on network
     * get routed to target test app inadvertently
     */
#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
    if (E_OK == retVal)
    {
        retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);
    }
#endif

    return retVal;
}

static Std_ReturnType EthApp_deinit(uint8 ctrlIdx)
{
    Std_ReturnType retVal;

    /* Set controller to down mode */
    retVal = Eth_SetControllerMode(ctrlIdx, ETH_MODE_DOWN);
    if (E_OK != retVal)
    {
        EthUtils_printf("deinit: failed to set the controller to down mode\n");
    }

    return retVal;
}

static Std_ReturnType EthApp_trcvInit(const EthTrcv_ConfigType *cfg)
{
#if ((STD_ON == ETHTRCV_SETTRANSCEIVERMODE_API) || \
     (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API) || \
     (STD_ON == ETHTRCV_GETLINKSTATE_API) ||       \
     (STD_ON == ETHTRCV_GETBAUDRATE_API) ||        \
     (STD_ON == ETHTRCV_GETDUPLEXMODE_API))
    uint8 trcvIdx = ETHTRCV_DRV_CONFIG_0->trcvIdx;
#endif
    Std_ReturnType retVal = E_OK;

    /* Initialize the EthTrcv driver */
    EthTrcv_Init(cfg);

    /* Set the transceiver mode to ACTIVE */
#if (STD_ON == ETHTRCV_SETTRANSCEIVERMODE_API)
    if (E_OK == retVal)
    {
        retVal = EthTrcv_SetTransceiverMode(trcvIdx, ETHTRCV_MODE_ACTIVE);
        if (E_OK != retVal)
        {
            EthUtils_printf("Failed to set trcv mode: %d\n", retVal);
        }
    }
#else
    EthUtils_printf("EthTrcv_SetTransceiverMode API is not enabled\n");
#endif

    /* Read the mode to make sure the change took effect */
#if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API)
    if (E_OK == retVal)
    {
        EthTrcv_ModeType trcvMode;

        retVal = EthTrcv_GetTransceiverMode(trcvIdx, &trcvMode);
        if (E_OK == retVal)
        {
            EthUtils_printf("EthTrcv mode: %s\n",
                            (trcvMode == ETHTRCV_MODE_ACTIVE) ? "ACTIVE" : "DOWN");
        }
        else
        {
            EthUtils_printf("Failed to get trcv mode: %d\n", retVal);
        }
    }
#else
    EthUtils_printf("EthTrcv_GetTransceiverMode API is not enabled\n");
#endif

    /* Get the link state */
#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
    if (E_OK == retVal)
    {
        EthTrcv_LinkStateType linkState;

        retVal = EthTrcv_GetLinkState(trcvIdx, &linkState);
        if (E_OK == retVal)
        {
            EthUtils_printf("EthTrcv link state: %s\n",
                            (linkState == ETHTRCV_LINK_STATE_ACTIVE) ? "Up" : "Down");
        }
        else
        {
            EthUtils_printf("Failed to get link state: %d\n", retVal);
        }
    }
#else
    EthUtils_printf("EthTrcv_GetLinkState API is not enabled\n");
#endif

    /* Get the baud rate */
#if (STD_ON == ETHTRCV_GETBAUDRATE_API)
    if (E_OK == retVal)
    {
        EthTrcv_BaudRateType baudRate;

        retVal = EthTrcv_GetBaudRate(trcvIdx, &baudRate);
        if (E_OK == retVal)
        {
            if (ETHTRCV_BAUD_RATE_10MBIT == baudRate)
            {
                EthUtils_printf("EthTrcv baud rate: 10Mbps\n");
            }
            else if (ETHTRCV_BAUD_RATE_100MBIT == baudRate)
            {
                EthUtils_printf("EthTrcv baud rate: 100Mbps\n");
            }
            else if (ETHTRCV_BAUD_RATE_1000MBIT == baudRate)
            {
                EthUtils_printf("EthTrcv baud rate: 1000Mbps\n");
            }
        }
        else
        {
            EthUtils_printf("Failed to get baud rate: %d\n", retVal);
        }
    }
#else
    EthUtils_printf("EthTrcv_GetBaudRate API is not enabled\n");
#endif

    /* Get duplexity */
#if (STD_ON == ETHTRCV_GETDUPLEXMODE_API)
    if (E_OK == retVal)
    {
        EthTrcv_DuplexModeType duplexMode;

        retVal = EthTrcv_GetDuplexMode(trcvIdx, &duplexMode);
        if (E_OK == retVal)
        {
            EthUtils_printf("EthTrcv duplexity: %s\n",
                            (duplexMode == ETHTRCV_DUPLEX_MODE_FULL) ? "Full" : "Half");
        }
        else
        {
            EthUtils_printf("Failed to get duplexity: %d\n", retVal);
        }
    }
#else
    EthUtils_printf("EthTrcv_GetDuplexMode API is not enabled\n");
#endif

    EthTrcv_MainFunction();

    return retVal;
}

static Std_ReturnType EthApp_showStats(uint8 ctrlIdx)
{
    Std_ReturnType retVal;
#if (STD_ON == ETH_GET_COUNTER_VALUES_API)
    Eth_CounterType ethCounter;
    retVal = Eth_GetCounterValues(ctrlIdx, &ethCounter);
    if (E_OK == retVal)
    {
        EthUtils_printf("----------------------------\n");
        EthUtils_printf("Controller %d Counters\n", ctrlIdx);
        EthUtils_printf("----------------------------\n");
        EthUtils_printf("Buffer overruns   : %d\n", ethCounter.DropPktBufOverrun);
        EthUtils_printf("CRC errors        : %d\n", ethCounter.DropPktCrc);
        EthUtils_printf("Undersize packets : %d\n", ethCounter.UndersizePkt);
        EthUtils_printf("Oversized packets : %d\n", ethCounter.OversizePkt);
        EthUtils_printf("Alignment errors  : %d\n", ethCounter.AlgnmtErr);
        EthUtils_printf("SQE errors        : %d\n", ethCounter.SqeTestErr);
        EthUtils_printf("Discarded inbound : %d\n", ethCounter.DiscInbdPkt);
        EthUtils_printf("Erroneous inbound : %d\n", ethCounter.ErrInbdPkt);
        EthUtils_printf("Discarded outbound: %d\n", ethCounter.DiscOtbdPkt);
        EthUtils_printf("Erroneous outbound: %d\n", ethCounter.ErrOtbdPkt);
        EthUtils_printf("Single collision  : %d\n", ethCounter.SnglCollPkt);
        EthUtils_printf("Multiple collision: %d\n", ethCounter.MultCollPkt);
        EthUtils_printf("Deferred transm   : %d\n", ethCounter.DfrdPkt);
        EthUtils_printf("Late collisions   : %d\n", ethCounter.LatCollPkt);
        EthUtils_printf("Excessive colls   : %d\n", ethCounter.HwDepCtr0);
        EthUtils_printf("Carrier loss      : %d\n", ethCounter.HwDepCtr1);
    }
    else
    {
        EthUtils_printf("showCountValues: failed to get counters: %d\n", retVal);
        gEthApp.stats.etherGetCountValuesErr++;
    }
#else
    EthUtils_printf("showCountValues: Eth_GetCounterValues() API not enabled\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GET_RX_STATS_API)
    Eth_RxStatsType rxStats;
    retVal = Eth_GetRxStats(ctrlIdx, &rxStats);
    if (E_OK == retVal)
    {
        EthUtils_printf("----------------------------\n");
        EthUtils_printf("Controller %d Rx Statistics\n", ctrlIdx);
        EthUtils_printf("----------------------------\n");
        EthUtils_printf("Rx Drop Events       : %d\n", rxStats.RxStatsDropEvents);
        EthUtils_printf("Rx Octets            : %d\n", rxStats.RxStatsOctets);
        EthUtils_printf("Rx Packets           : %d\n", rxStats.RxStatsPkts);
        EthUtils_printf("Rx Bcast Packets     : %d\n", rxStats.RxStatsBroadcastPkts);
        EthUtils_printf("Rx Mcast Packets     : %d\n", rxStats.RxStatsMulticastPkts);
        EthUtils_printf("Rx CRC/Align Errors  : %d\n", rxStats.RxStatsCrcAlignErrors);
        EthUtils_printf("Rx Undersized Packets: %d\n", rxStats.RxStatsUndersizePkts);
        EthUtils_printf("Rx Oversized Packets : %d\n", rxStats.RxStatsOversizePkts);
        EthUtils_printf("Rx Fragments         : %d\n", rxStats.RxStatsFragments);
        EthUtils_printf("Rx Jabbers           : %d\n", rxStats.RxStatsJabbers);
        EthUtils_printf("Rx Collisions        : %d\n", rxStats.RxStatsCollisions);
        EthUtils_printf("Rx 64 bytes or less Packets   : %d\n", rxStats.RxStatsPkts64Octets);
        EthUtils_printf("Rx 65 to 127 bytes Packets    : %d\n", rxStats.RxStatsPkts65to127Octets);
        EthUtils_printf("Rx 128 to 255 bytes Packets   : %d\n", rxStats.RxStatsPkts128to255Octets);
        EthUtils_printf("Rx 256 to 511 bytes Packets   : %d\n", rxStats.RxStatsPkts256to511Octets);
        EthUtils_printf("Rx 512 to 1023 bytes Packets  : %d\n", rxStats.RxStatsPkts512to1023Octets);
        EthUtils_printf("Rx 1024 to 1518 bytes Packets : %d\n", rxStats.RxStatsPkts1024to1518Octets);
        EthUtils_printf("Rx Unicast Packets            : %d\n", rxStats.RxUnicastFrames);
    }
    else
    {
        EthUtils_printf("getRxStats: failed to get counters: %d\n", retVal);
        gEthApp.stats.etherGetRxStasErr++;
    }
#else
    EthUtils_printf("getRxStats: Eth_GetRxStats() API not enabled\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GET_TX_STATS_API)
    Eth_TxStatsType txStats;
    retVal = Eth_GetTxStats(ctrlIdx, &txStats);
    if (E_OK == retVal)
    {
        EthUtils_printf("----------------------------\n");
        EthUtils_printf("Controller %d Tx Statistics \n", ctrlIdx);
        EthUtils_printf("----------------------------\n");
        EthUtils_printf("Tx Num octets          : %d\n", txStats.TxNumberOfOctets);
        EthUtils_printf("Tx No Unicast Packets  : %d\n", txStats.TxNUcastPkts);
        EthUtils_printf("Tx Unicast Packets     : %d\n", txStats.TxUniCastPkts);
    }
    else
    {
        EthUtils_printf("getTxStats: failed to get TX stats: %d\n", retVal);
        gEthApp.stats.etherGetTxStasErr++;
    }
#else
    EthUtils_printf("getTxStats: Eth_GetTxStats() API not enabled\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GET_TX_ERROR_COUNTERSVALUES_API)
    Eth_TxErrorCounterValuesType txErrorCounterValues;
    retVal = Eth_GetTxErrorCounterValues(ctrlIdx, &txErrorCounterValues);
    if (E_OK == retVal)
    {
        EthUtils_printf("--------------------------------\n");
        EthUtils_printf("Controller %d Tx Error Counters \n", ctrlIdx);
        EthUtils_printf("--------------------------------\n");
        EthUtils_printf("Tx Deferred transm      : %d\n", txErrorCounterValues.TxDeferredTrans);
        EthUtils_printf("Tx Single collisions    : %d\n", txErrorCounterValues.TxSingleCollision);
        EthUtils_printf("Tx Multiple collisions  : %d\n", txErrorCounterValues.TxMultipleCollision);
        EthUtils_printf("Tx Late collisions      : %d\n", txErrorCounterValues.TxLateCollision);
        EthUtils_printf("Tx Excessive collisions : %d\n", txErrorCounterValues.TxExcessiveCollison);
    }
    else
    {
        EthUtils_printf("showTxErrStatsCount: failed to get counters: %d\n", retVal);
        gEthApp.stats.etherGetTxErrStasErr++;
    }
#else
    EthUtils_printf("showTxErrStatsCount: Eth_GetTxErrorCounterValues() API not enabled\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GET_COUNTER_VALUES_API)
    for (uint16 i = 0; i < CPSW_STATS_BLOCK_ELEM_NUM; i++)
    {
        uint32 CtrValue = 0U;

        retVal = Eth_GetCounterState(ctrlIdx, i, &CtrValue);
        if (E_OK == retVal)
        {
            if (i == 0)
            {
                EthUtils_printf("-------------------------------------\n");
                EthUtils_printf("Controller %d Counter Register States\n", ctrlIdx);
                EthUtils_printf("-------------------------------------\n");
            }

            EthUtils_printf("CtrOffs: %3d %20s: %d\n", i, CtrOffsToName[i], CtrValue);
        }
        else
        {
            EthUtils_printf("CtrOffs: %3d %20s: <Err>\n", i, CtrOffsToName[i]);
        }
    }
#else
    EthUtils_printf("showCountState: Eth_GetCounterState() API not enabled\n");
    retVal = E_NOT_OK;
#endif
    return retVal;
}

void EthIf_TxConfirmation(uint8 ctrlIdx,
                          Eth_BufIdxType bufIdx,
                          Std_ReturnType result)
{
    Eth_TimeStampQualType timeQual;
    Eth_TimeStampType tsVal;

    if (E_OK == result)
    {
        gEthApp.stats.txConfPktCnt++;
    }
    else if (E_NOT_OK == result)
    {
        EthUtils_printf("TxConfirmation: transmission of buffer %d failed\n", bufIdx);
        gEthApp.stats.txPktErr++;
    }
    else
    {
        EthUtils_printf("TxConfirmation: invalid confirmation result %d for buffer %d\n",
                        result, bufIdx);
    }

    if(gEthApp.saveTxTime)
    {
        Eth_GetEgressTimeStamp(ctrlIdx, bufIdx, &timeQual, &tsVal);
        if(timeQual == ETH_VALID)
        {
            gEthApp.saveTxTimeStamp[gEthApp.txFrameCnt] = tsVal;
            gEthApp.txFrameCnt = (gEthApp.txFrameCnt + 1) % ETH_TEST_ITER_S_COUNT;
        }
    }
}

void EthIf_RxIndication(uint8 ctrlIdx,
                        Eth_FrameType FrameType,
                        boolean IsBroadcast,
                        uint8 *PhysAddrPtr,
                        Eth_DataType *DataPtr,
                        uint16 lenByte)
{
    uint8 pcp = ETH_TEST_VLAN_PCP;
    uint16 vid = ETH_TEST_VLAN_VID;
    uint8 *buf = (uint8 *)DataPtr;
    uint8 cmd;
    sint32 ret;
    Eth_TimeStampQualType timeQual;
    Eth_TimeStampType tsVal;

    if (TRUE == gEthApp.veryVerbose)
    {
        EthUtils_printf("EthIf_RxIndication: len: %d, bcast: %s, EtherType: 0x%04x\n",
                        lenByte,
                        IsBroadcast ? "yes" : "no",
                        FrameType & 0xFFFFU);
    }

    /* Check that the correct controller index is being reported */
    if (ctrlIdx != gEthApp.ctrlIdx)
    {
        EthUtils_printf("EthIf_RxIndication: incorrect controller index "
                        "(got %d, exp %d)\n",
                        ctrlIdx, gEthApp.ctrlIdx);
        gEthApp.stats.rxCtrlIdxErr++;
    }

    /* Validate packet content according to its EtherType */
    switch (FrameType)
    {
    case ETHERTYPE_EXP_CONTROL:
        cmd = buf[0];
        switch (cmd)
        {
        case CTRL_FRAME_CMD_START:
            gEthApp.runTest = TRUE;
            break;
        case CTRL_FRAME_CMD_STOP:
            gEthApp.runTest = FALSE;
            break;
        default:
            EthUtils_printf("EthIf_RxIndication: invalid control command: %d\n", cmd);
            break;
        }
        gEthApp.stats.rxPktCnt++;
        break;

    case ETHERTYPE_VLAN_TAG:
        ret = EthUtils_checkVlanTagAndPayload((VlanDataFramePayload *)DataPtr,
                                              pcp, vid, ETHERTYPE_EXPERIMENTAL1);
        if (ETH_TEST_PKT_SOK != ret)
        {
            EthUtils_printf("EthIf_RxIndication: VLAN tagged payload error: %d\n", ret);
            gEthApp.stats.rxPayloadErr++;
        }
        else
        {
            gEthApp.stats.rxPktCnt++;
            gEthApp.stats.rxVlanPktCnt++;
        }
        break;

    case ETHERTYPE_EXPERIMENTAL1:
        ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
        if (ETH_TEST_PKT_SOK != ret)
        {
            EthUtils_printf("EthIf_RxIndication: packet validation failed: %d\n", ret);
            gEthApp.stats.rxPayloadErr++;
        }
        else
        {
            gEthApp.stats.rxPktCnt++;
            gEthApp.stats.rxExp1PktCnt++;
        }
        break;

    case ETHERTYPE_EXPERIMENTAL2:
        ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
        if (ETH_TEST_PKT_SOK != ret)
        {
            EthUtils_printf("EthIf_RxIndication: packet validation failed: %d\n", ret);
            gEthApp.stats.rxPayloadErr++;
        }
        else
        {
            gEthApp.stats.rxPktCnt++;
            gEthApp.stats.rxExp2PktCnt++;
        }
        break;

    case ETHERTYPE_EXPERIMENTAL3:
        {
            gEthApp.stats.rxPktCnt++;
            gEthApp.stats.rxExp3PktCnt++;
            gEthApp.stats.rxExp3BytesCnt += (lenByte + 14u);
        }
        break;

    default:
        gEthApp.stats.rxEtherTypeErr++;
        break;
    }

    if (gEthApp.saveRxFrame)
    {
        if (IsBroadcast)
        {
            memset(gEthApp.rxFrame.hdr.dstMac, 0xff, ETH_MAC_ADDR_LEN);
        }
        else
        {
            memset(gEthApp.rxFrame.hdr.dstMac, 0x00U, ETH_MAC_ADDR_LEN);
        }

        memcpy(gEthApp.rxFrame.hdr.srcMac, PhysAddrPtr, ETH_MAC_ADDR_LEN);
        gEthApp.rxFrame.hdr.etherType = (uint16)FrameType;
        memcpy(gEthApp.rxFrame.payload, DataPtr, lenByte);
        gEthApp.saveRxFrame = FALSE;
    }

    if(gEthApp.saveRxTime)
    {
        if(FrameType == ETHERTYPE_EXPERIMENTAL1)
        {
            Eth_GetIngressTimeStamp(ctrlIdx, DataPtr, &timeQual, &tsVal);
            if(timeQual == ETH_VALID)
            {
                gEthApp.saveRxTimeStamp[gEthApp.rxFrameCnt] = tsVal;
                gEthApp.rxFrameCnt = (gEthApp.rxFrameCnt + 1) % ETH_TEST_ITER_S_COUNT;
            }
        }
    }

    gEthApp.stats.rxPktIndCnt++;
}

void EthIf_CtrlModeIndication(uint8 ControllerId,
                              Eth_ModeType ControllerMode)
{
    if (ETH_MODE_DOWN == ControllerMode)
    {
        EthUtils_printf("EthIf_CtrlModeIndication: DOWN\n");
        gEthApp.stats.ctrlModeIndDownCnt++;
    }
    else if (ETH_MODE_ACTIVE == ControllerMode)
    {
        EthUtils_printf("EthIf_CtrlModeIndication: ACTIVE\n");
        gEthApp.stats.ctrlModeIndActCnt++;
    }
    else
    {
        EthUtils_printf("EthIf_CtrlModeIndication: invalid mode\n");
        gEthApp.stats.ctrlModeIndErr++;
    }
}

void EthIf_TrcvModeIndication(uint8 CtrlIdx,
                              EthTrcv_ModeType TrcvMode)
{
    EthUtils_printf("EthIf_TrcvModeIndication: %s\n",
                  (ETHTRCV_MODE_ACTIVE == TrcvMode) ? "Active" : "Down");
}

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
                VAR(Dem_EventIdType, AUTOMATIC) EventId,
                VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
    if ((DEM_EVENT_STATUS_FAILED | DEM_EVENT_STATUS_PREFAILED) == EventStatus)
    {
        EthUtils_printf("Dem_SetEventStatus: %d\n", (uint16)EventId);
        gEthApp.stats.demErr++;
    }
    return (E_OK);
}

static BufReq_ReturnType EthApp_provideTxBuffer(uint8 ctrlIdx,
                                                uint8 priority,
                                                Eth_BufIdxType* bufIdxPtr,
                                                uint8** bufPtr,
                                                uint16* lenBytePtr)
{
    BufReq_ReturnType bufStatus;
    boolean retry;

    /* Request one buffer, retry if not available */
    do
    {
        bufStatus = Eth_ProvideTxBuffer(ctrlIdx,
                                        priority,
                                        bufIdxPtr,
                                        bufPtr,
                                        lenBytePtr);
        if (BUFREQ_E_BUSY == bufStatus)
        {
            /* Temporarily no buffer available. As per spec, it's up to the
             * requester to retry request for a certain time */
            retry = TRUE;

            if(gEthApp.txIrqDisable)
            {
                /* Free TX packets are recycled during Eth_TxConfirmation(),
                 * which would normally be called periodically by EthIf, but since
                 * we don't have an actual EthIf implemented in this test app,
                 * we just call it here to let descriptor recycling happen. */
                Eth_TxConfirmation(ctrlIdx);
            }
        }
        else
        {
            retry = FALSE;
        }
    }
    while (retry == TRUE);

    return bufStatus;
}

static void EthApp_send(uint8 ctrlIdx,
                        EthFrame *frame,
                        uint16 len)
{
    Eth_FrameType frameType = frame->hdr.etherType;
    Eth_BufIdxType bufIdx;
    BufReq_ReturnType bufStatus;
    boolean txConfirmation = FALSE;
    uint8 *bufPtr;
    Std_ReturnType retVal;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 priority = 0U;

    bufStatus = EthApp_provideTxBuffer(ctrlIdx,
                                       priority,
                                       &bufIdx,
                                       &bufPtr,
                                       &len);

    if (BUFREQ_OK == bufStatus)
    {
        memcpy(bufPtr, frame->payload, len);

        retVal = Eth_Transmit(ctrlIdx,
                              bufIdx,
                              frameType,
                              txConfirmation,
                              len,
                              frame->hdr.dstMac);
        if (E_OK != retVal)
        {
            EthUtils_printf("send: failed to send buffer\n");
        }
    }
    else
    {
        EthUtils_printf("send: failed to get TX buffer: %d\n", (int)bufStatus);
    }

    if(gEthApp.txIrqDisable)
    {
        Eth_TxConfirmation(ctrlIdx);
    }
}

static void EthApp_sendCmd(uint8 ctrlIdx,
                           uint8 cmd)
{
    CtrlFramePayload *control;
    Eth_FrameType frameType = ETHERTYPE_EXP_CONTROL;
    Eth_BufIdxType bufIdx;
    BufReq_ReturnType bufStatus;
    boolean txConfirmation = FALSE;
    uint16 len = sizeof(CtrlFramePayload);
    uint8 *bufPtr;
    Std_ReturnType retVal;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 priority = 0U;

    bufStatus = EthApp_provideTxBuffer(ctrlIdx,
                                       priority,
                                       &bufIdx,
                                       &bufPtr,
                                       &len);
    if (BUFREQ_OK == bufStatus)
    {
        control = (CtrlFramePayload *)bufPtr;
        control->cmd = cmd;

        retVal = Eth_Transmit(ctrlIdx,
                              bufIdx,
                              frameType,
                              txConfirmation,
                              len,
                              BcastAddr);
        if (E_OK != retVal)
        {
            EthUtils_printf("sendCmd: failed to send STOP cmd\n");
        }
    }
    else
    {
        EthUtils_printf("sendCmd: failed to get TX buffer: %d\n", (int)bufStatus);
    }

    if(gEthApp.txIrqDisable)
    {
        Eth_TxConfirmation(ctrlIdx);
    }
}

static boolean EthApp_transmit(uint8 ctrlIdx,
                               uint32 num,
                               uint16 len,
                               boolean txConfirmation,
                               boolean vlan,
                               uint8 *dstAddr)
{
    Eth_FrameType frameType;
    Eth_BufIdxType bufIdx;
    BufReq_ReturnType bufStatus;
    uint16 grantedLen = len;
    uint8 *bufPtr;
    uint32 retryCnt;
    uint32 i;
    sint32 fillStatus;
    boolean randomBufLen;
    boolean status = PASS;
    uint32 delayTime = 2u;
    Std_ReturnType retVal;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 priority = 0U;

    randomBufLen = (len == 0U) ? TRUE : FALSE;

    /* Reset test counters */
    gEthApp.stats.txPktCnt     = 0U;
    gEthApp.stats.txConfPktCnt = 0U;
    gEthApp.stats.txBufLenErr  = 0U;
    gEthApp.stats.txBufProvErr = 0U;
    gEthApp.stats.txPktErr     = 0U;
    gEthApp.stats.detErr       = 0U;
    gEthApp.stats.demErr       = 0U;

    if (TRUE == Eth_GetTxIrqPacingEnable(gEthApp.ctrlIdx))
    {
        /* Incase IRQ pacing enable need more time to wait */
        delayTime *= (2u * Eth_GetHwTimerIntervalMs(gEthApp.ctrlIdx,
                Eth_GetTxHwTimerIdx(gEthApp.ctrlIdx)));
    }

    /* Transmit the requested number of buffers */
    for (i = 0U; i < num; i++)
    {
        if (randomBufLen)
        {
            grantedLen = EthUtils_rand(ETH_TEST_BUF_LEN_MIN,
                                       ETH_TEST_BUF_LEN_MAX);
        }
        else
        {
            grantedLen = len;
        }

        if (vlan)
        {
            grantedLen += ETH_VLAN_TAG_LEN;
        }

        /* Request TX buffer */
        bufStatus = EthApp_provideTxBuffer(ctrlIdx,
                                           priority,
                                           &bufIdx,
                                           &bufPtr,
                                           &grantedLen);
        if (BUFREQ_E_OVFL == bufStatus)
        {
            EthUtils_printf("transmit: failed to get exact size (req=%d got=%d)\n",
                            len, grantedLen);
            gEthApp.stats.txBufLenErr++;
            status = FAIL;
        }
        else if (BUFREQ_E_NOT_OK == bufStatus)
        {
            EthUtils_printf("transmit: failed to get buffer\n");
            gEthApp.stats.txBufProvErr++;
            status = FAIL;
        }
        else if (bufPtr == NULL_PTR)
        {
            EthUtils_printf("transmit: invalid buffer pointer\n");
            gEthApp.stats.txBufProvErr++;
            status = FAIL;
        }

        /* Exit test if error is too critical */
        if (FAIL == status)
        {
            break;
        }

        /* Fill buffer with test pattern */
        if (vlan)
        {
            frameType = ETHERTYPE_VLAN_TAG;
            fillStatus = EthUtils_fillVlanPayload((VlanDataFramePayload *)bufPtr,
                                                  i % ETH_TEST_NUM_TYPES,
                                                  grantedLen,
                                                  ETH_TEST_VLAN_PCP,
                                                  ETH_TEST_VLAN_VID,
                                                  ETHERTYPE_EXPERIMENTAL1);
        }
        else
        {
            frameType = ETHERTYPE_EXPERIMENTAL1;
            fillStatus = EthUtils_fillPayload((DataFramePayload *)bufPtr,
                                              i % ETH_TEST_NUM_TYPES,
                                              grantedLen);
        }

        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthUtils_printf("transmit: failed to fill test packet\n");
            status = FAIL;
            break;
        }

        /* Transmit the packet */
        retryCnt = txConfirmation ? 0U : ETHAPP_TRANSMIT_RETRY_COUNT;
        do
        {
            retVal = Eth_Transmit(ctrlIdx,
                                  bufIdx,
                                  frameType,
                                  txConfirmation,
                                  grantedLen,
                                  dstAddr);
            if (E_OK == retVal)
            {
                break;
            }

            if (retryCnt > 0U)
            {
                EthApp_delay(1U);
                retryCnt--;
            }
            else
            {
                break;
            }
        }
        while (TRUE);

        if (E_OK != retVal)
        {
            EthUtils_printf("transmit: failed to transmit buffer with idx %d\n",
                            (sint32)bufIdx);
            gEthApp.stats.txPktErr++;
        }
        else
        {
            gEthApp.stats.txPktCnt++;
        }

        if(gEthApp.txIrqDisable)
        {
            Eth_TxConfirmation(ctrlIdx);
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(ctrlIdx, CTRL_FRAME_CMD_STOP);

    /* Short wait to allow for TX confirmation to come */
    if (txConfirmation && !gEthApp.txIrqDisable /* only need wait if we are in interupt mode */)
    {
        EthApp_delay(delayTime);
    }

    /* Check error conditions */
    if ((txConfirmation && (gEthApp.stats.txConfPktCnt != gEthApp.stats.txPktCnt)) ||
        (gEthApp.stats.txPktCnt < num) ||
        (gEthApp.stats.txPktErr > 0U) ||
        (gEthApp.stats.txBufProvErr > 0U) ||
        (gEthApp.stats.txBufLenErr > 0U) ||
        (gEthApp.stats.detErr > 0U) ||
        (gEthApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthApp.verbose))
    {
        EthUtils_printf("Transmit Test Results:\n");
        EthUtils_printf("  Status:                 %s\n", status?"Pass":"Fail");
        EthUtils_printf("  Requested:              %d\n", num);
        EthUtils_printf("  Confirmation requested: %s\n", txConfirmation?"Yes":"No");
        EthUtils_printf("  Transmitted:            %d\n", gEthApp.stats.txPktCnt);
        EthUtils_printf("  Confirmed:              %d\n", gEthApp.stats.txConfPktCnt);
        EthUtils_printf("  Buffer length errors:   %d\n", gEthApp.stats.txBufLenErr);
        EthUtils_printf("  Buffer request errors:  %d\n", gEthApp.stats.txBufProvErr);
        EthUtils_printf("  Transmission errors:    %d\n", gEthApp.stats.txPktErr);
        EthUtils_printf("  DEM errors:             %d\n", gEthApp.stats.demErr);
        EthUtils_printf("  DET errors:             %d\n", gEthApp.stats.detErr);
        EthUtils_printf("\n");
    }

    return status;
}

static boolean EthApp_receive(uint8 ctrlIdx,
                              uint32 num)
{
    boolean forever;
    boolean status = PASS;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 fifoIdx = 0U;
    Eth_RxStatusType rxStatus;

    /* Reset test counters */
    gEthApp.stats.rxPktCnt       = 0U;
    gEthApp.stats.rxExp1PktCnt   = 0U;
    gEthApp.stats.rxExp2PktCnt   = 0U;
    gEthApp.stats.rxVlanPktCnt   = 0U;
    gEthApp.stats.rxPktNotRecv   = 0U;
    gEthApp.stats.rxPktIndCnt    = 0U;
    gEthApp.stats.rxEtherTypeErr = 0U;
    gEthApp.stats.rxPayloadErr   = 0U;
    gEthApp.stats.rxCtrlIdxErr   = 0U;
    gEthApp.stats.detErr         = 0U;
    gEthApp.stats.demErr         = 0U;

    forever = (num == 0U) ? TRUE : FALSE;

    gEthApp.runTest = TRUE;

    /* Wait for Rx frames */
    while (gEthApp.runTest)
    {
        if(gEthApp.rxIrqDisable)
        {
            Eth_Receive(ctrlIdx, fifoIdx, &rxStatus);
        }
        if (!forever && (gEthApp.stats.rxPktIndCnt >= num))
        {
            break;
        }
    }

    if ((gEthApp.stats.rxPktIndCnt != gEthApp.stats.rxPktCnt) ||
        (gEthApp.stats.rxEtherTypeErr > 0U) ||
        (gEthApp.stats.rxPayloadErr > 0U) ||
        (gEthApp.stats.rxCtrlIdxErr > 0U) ||
        (gEthApp.stats.detErr > 0U) ||
        (gEthApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthApp.verbose))
    {
        EthUtils_printf("Receive Test Results:\n");
        EthUtils_printf("  Status:                %s\n", status?"Pass":"Fail");
        EthUtils_printf("  Requested:             %d\n", num);
        EthUtils_printf("  Received:              %d\n", gEthApp.stats.rxPktCnt);
        EthUtils_printf("  Indicated:             %d\n", gEthApp.stats.rxPktIndCnt);
        EthUtils_printf("  Experimental 1:        %d\n", gEthApp.stats.rxExp1PktCnt);
        EthUtils_printf("  Experimental 2:        %d\n", gEthApp.stats.rxExp2PktCnt);
        EthUtils_printf("  VLAN tagged:           %d\n", gEthApp.stats.rxVlanPktCnt);
        EthUtils_printf("  Not received:          %d\n", gEthApp.stats.rxPktNotRecv);
        EthUtils_printf("  EtherType errors:      %d\n", gEthApp.stats.rxEtherTypeErr);
        EthUtils_printf("  Payload errors:        %d\n", gEthApp.stats.rxPayloadErr);
        EthUtils_printf("  Controller idx errors: %d\n", gEthApp.stats.rxCtrlIdxErr);
        EthUtils_printf("  DEM errors:            %d\n", gEthApp.stats.demErr);
        EthUtils_printf("  DET errors:            %d\n", gEthApp.stats.detErr);
        EthUtils_printf("\n");
    }

    return status;
}

static const char *EthApp_ethErrorIdToString(uint8 errorId)
{
    switch (errorId)
    {
    case ETHTRCV_E_INV_TRCV_IDX:
        return "Invalid controller index error";
    case ETHTRCV_E_UNINIT:
        return "Module or controller not initialized";
    case ETHTRCV_E_PARAM_POINTER:
        return "Invalid pointer in parameter list";
    case ETHTRCV_E_INIT_FAILED:
        return "Invalid parameter";
    case ETH_E_INV_MODE:
        return "Invalid mode";
    default:
        return "Unknown error";
   }
}

static const char *EthApp_ethTrcvErrorIdToString(uint8 errorId)
{
    switch (errorId)
    {
    case ETH_E_INV_CTRL_IDX:
        return "Invalid controller index error";
    case ETH_E_UNINIT:
        return "Module or controller not initialized";
    case ETH_E_PARAM_POINTER:
        return "Invalid pointer in parameter list";
    case ETH_E_INV_PARAM:
        return "Invalid parameter";
    case ETH_E_INV_MODE:
        return "Invalid mode";
    default:
        return "Unknown error";
   }
}

static const char *EthApp_errorIdToString(uint8 moduleId, uint8 errorId)
{
    switch(moduleId)
    {
        case ETH_MODULE_ID:
            return EthApp_ethErrorIdToString(errorId);
        case ETHTRCV_MODULE_ID:
            return EthApp_ethTrcvErrorIdToString(errorId);
        default:
            return "Unknown module";
    }
}

static const char *EthApp_ethApiIdToString(uint8 apiId)
{
    switch (apiId)
    {
        case ETH_SID_INIT:
            return "Eth_Init";
        case ETH_SID_SET_CONTROLLER_MODE:
            return "Eth_SetControllerMode";
        case ETH_SID_GET_CONTROLLER_MODE:
            return "Eth_GetControllerMode";
        case ETH_SID_WRITE_MII:
            return "Eth_WriteMii";
        case ETH_SID_READ_MII:
            return "Eth_ReadMii";
        case ETH_SID_GET_PHYS_ADDR:
            return "Eth_GetPhysAddr";
        case ETH_SID_PROVIDE_TX_BUFFER:
            return "Eth_ProvideTxBuffer";
        case ETH_SID_TRANSMIT:
        /* REVISIT: There are two services with the same ID in 4.2.1 spec */
        /* case ETH_SID_MAIN_FUNCTION:  */
            return "Eth_MainFunction or Eth_Transmit";
        case ETH_SID_RECEIVE:
            return "Eth_Receive";
        case ETH_SID_TX_CONFIRMATION:
            return "Eth_TxConfirmation";
        case ETH_SID_GET_VERSION_INFO:
            return "Eth_GetVersionInfo";
        case ETH_SID_RX_IRQ_HDLR:
            return "Eth_RxIrqHdlr_<CtrlIdx>";
        case ETH_SID_TX_IRQ_HDLR:
            return "Eth_TxIrqHdlr_<CtrlIdx>";
        case ETH_SID_UPDATE_PHYS_ADDR_FILTER:
            return "Eth_UpdatePhysAddrFilter";
        case ETH_SID_SET_PHYS_ADDR:
            return "Eth_SetPhysAddr";
        case ETH_SID_GET_COUNTER_VALUES:
            return "Eth_GetCounterValues";
        case ETH_SID_GET_RX_STATS:
            return "Eth_GetRxStats";
        case ETH_SID_GET_TX_STATS:
            return "Eth_GetTxStats";
        case ETH_SID_GET_TXERROR_COUNTERVALUES:
            return "Eth_GetTxErrorCounterValues";
        case ETH_SID_GET_CURRENT_TIME:
            return "Eth_GetCurrentTime";
        case ETH_SID_ENABLE_EGRESS_TIMESTAMP:
            return "Eth_EnableEgressTimeStamp";
        case ETH_SID_GET_EGRESS_TIMESTAMP:
            return "Eth_GetEgressTimeStamp";
        case ETH_SID_GET_INGRESS_TIMESTAMP:
            return "Eth_GetIngressTimeStamp";
        case ETH_SID_SET_CORRECTION_TIME:
            return "Eth_SetCorrectionTime";
        case ETH_SID_SET_GLOBAL_TIME:
            return "Eth_SetGlobalTime";
        default:
            return "Unknown service";
    }
}

static const char *EthApp_ethTrcvApiIdToString(uint8 apiId)
{
    switch (apiId)
    {
        case ETHTRCV_MAINFCT_WRITE_ID:
            return "EthTrcv_MainFunction";
        case ETHTRCV_VERSION_ID:
            return "EthTrcv_GetVersionInfo";
        case ETHTRCV_WRITEMIIIND_ID:
            return "EthTrcv_WriteMiiIndication";
        case ETHTRCV_READMIIIND_ID:
            return "EthTrcv_ReadMiiIndication";
        case ETHTRCV_GETDPLXMODE_ID:
            return "EthTrcv_GetDuplexMode";
        case ETHTRCV_GETBAUD_ID:
            return "EthTrcv_GetBaudRate";
        case ETHTRCV_GETLNKSTATE_ID:
            return "EthTrcv_GetLinkState or Eth_Transmit";
        case ETHTRCV_SRTAUTONEGOTIA_ID:
            return "EthTrcv_StartAutoNegotiation";
        case ETHTRCV_GETTRCVMODE_ID:
            return "EthTrcv_GetTransceiverMode";
        case ETHTRCV_SETTRCVMODE_ID:
            return "EthTrcv_SetTransceiverMode";
        case ETHTRCV_INIT_ID:
            return "EthTrcv_Init";
        default:
            return "Unknown service";
    }
}

static const char *EthApp_apiIdToString(uint8 moduleId, uint8 apiId)
{
    switch(moduleId)
    {
        case ETH_MODULE_ID:
            return EthApp_ethApiIdToString(apiId);
        case ETHTRCV_MODULE_ID:
            return EthApp_ethTrcvApiIdToString(apiId);
        default:
            return "Unknown API ID";
    }
}

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
static Std_ReturnType EthApp_getTranceiverLinkState(uint8 trcvIdx)
{
    Std_ReturnType retVal = E_OK;

    /* Get the link state */
    if (E_OK == retVal)
    {
        EthTrcv_LinkStateType linkState;

        retVal = EthTrcv_GetLinkState(trcvIdx, &linkState);
        if (E_OK == retVal)
        {
            EthUtils_printf("EthTrcv link state: %s\n",
                      (linkState == ETHTRCV_LINK_STATE_ACTIVE) ? "Up" : "Down");
        }
        else
        {
            EthUtils_printf("Failed to get link state: %d\n", retVal);
        }
    }

    return retVal;
}
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

void EthApp_wbInvCache(uint8 *buf, uint16 len)
{
    CacheP_wbInv(buf, len);
}

void EthApp_wbCache(uint8 *buf, uint16 len)
{
    CacheP_wb(buf, len);
}

void EthApp_invCache(uint8 *buf, uint16 len)
{
    CacheP_Inv(buf, len);
}

boolean EthApp_test_0001(void)
{
    uint32 num = 0U;
    boolean status;

    EthUtils_printf("test_0001: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0001: failed while receiving frames\n");
    }

    EthUtils_printf("test_0001: received %d of %d frames\n",
                    gEthApp.stats.rxExp1PktCnt, ETH_TEST_ITER_M_COUNT);

    if (gEthApp.stats.rxExp1PktCnt != ETH_TEST_ITER_M_COUNT)
    {
        EthUtils_printf("test_0001: received frame count mismatch (exp=%d, got=%lu)\n",
               ETH_TEST_ITER_M_COUNT, gEthApp.stats.rxExp1PktCnt);
        status = FAIL;
    }

    EthUtils_printf("test_0001: END\n");

    return status;
}

boolean EthApp_test_0002(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean status;

    EthUtils_printf("test_0002: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames */
    status = EthApp_transmit(gEthApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan,
                             &BcastAddr[0U]);

    EthUtils_printf("test_0002: END\n");

    return status;
}

boolean EthApp_test_0003(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint32 i;
    sint32 fillStatus;
    uint16 len = 1500U;
    boolean status = TRUE;
    EthFrame frame;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 fifoIdx = 0U;
    Eth_RxStatusType rxStatus;

    EthUtils_printf("test_0003: START\n");

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    memcpy(frame.hdr.srcMac, gEthApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Send and receive frames */
    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthApp.verbose)
        {
            EthUtils_printf("test_0003: iteration %d\n", i);
        }

        gEthApp.saveRxFrame = TRUE;
        gEthApp.stats.rxPktCnt = 0U;
        gEthApp.stats.rxPktIndCnt = 0U;

        fillStatus = EthUtils_fillPayload((DataFramePayload *)frame.payload,
                                          i % ETH_TEST_NUM_TYPES,
                                          len);
        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthUtils_printf("test_0003: failed to fill test packet\n");
            status = FAIL;
            break;
        }

        /* Send the frame */
        EthApp_send(gEthApp.ctrlIdx, &frame, len);

        /* Wait for Rx frames */
        while (0 == gEthApp.stats.rxPktIndCnt)
        {
            if(gEthApp.rxIrqDisable)
            {
                Eth_Receive(gEthApp.ctrlIdx, fifoIdx, &rxStatus);
            }
        }

        /* End the test if STOP cmd is detected */
        if (TRUE == EthFrame_isStopCmd(&gEthApp.rxFrame))
        {
            break;
        }

        /* Check if EtherType field matches */
        if (frame.hdr.etherType != gEthApp.rxFrame.hdr.etherType)
        {
            EthUtils_printf("test_0003: EtherType mismatch (exp=0x%04x, got=0x%04x)\n",
                            frame.hdr.etherType & 0xFFFFU,
                            gEthApp.rxFrame.hdr.etherType & 0xFFFFU);
            status = FAIL;
            break;
        }

        /* Check if payload matches */
        if (0 != memcmp(&frame.payload, gEthApp.rxFrame.payload, len))
        {
            EthUtils_printf("test_0003: payload mismatch\n");
            status = FAIL;
            break;
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthUtils_printf("test_0003: END\n");

    return status;
}

boolean EthApp_test_0004(void)
{
    uint32 num = 0U;
    boolean status;

    EthUtils_printf("test_0004: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0004: failed while receiving frames\n");
    }

    EthUtils_printf("test_0004: received %d of %d frames\n",
                    gEthApp.stats.rxExp1PktCnt, ETH_TEST_ITER_M_COUNT / 2);

    if (gEthApp.stats.rxExp1PktCnt != ETH_TEST_ITER_M_COUNT / 2)
    {
        status = FAIL;
    }

    EthUtils_printf("test_0004: END\n");

    return status;
}

#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)

boolean EthApp_test_0005(void)
{
    uint32 num = ETH_TEST_ITER_M_COUNT;
    uint32 acceptCnt = num / 2;
    boolean itStatus;
    boolean status = PASS;
    Std_ReturnType retVal;

    EthUtils_printf("test_0005: START\n");

    /* Part 1: Reset filter and receive frames with controller's address */
    retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, NullAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthApp.stats.filterNullErr++;
    }
    /* Subscribe to spl mcast address used by host app to send mcast frames.
     * HostApp sends mcast frames with non-broadcast address so that
     * broadcast frames in network from Host PC/other machines on network
     * get routed to target test app inadvertently
     */
    if (E_OK == retVal)
    {
        retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);
    }


    gEthApp.stats.rxExp1PktCnt = 0U;
    gEthApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthApp.stats.rxExp2PktCnt != 0U))
    {
        gEthApp.stats.filterNullRxErr++;
    }

    EthUtils_printf("test_0005:  Null: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005:  Null: Exp2: exp %3d, got %3d\n",
                    0U, gEthApp.stats.rxExp2PktCnt);

    /* Part 2: Add unicast address and receive frames with that address */
    retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, UcastAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthApp.stats.filterUcastAddErr++;
    }

    gEthApp.stats.rxExp1PktCnt = 0U;
    gEthApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthApp.stats.filterUcastRxErr++;
    }

    EthUtils_printf("test_0005: Ucast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005: Ucast: Exp2: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp2PktCnt);

    /* Part 3: Add multicast address and receive frames with that address */
    retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, McastAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthApp.stats.filterMcastAddErr++;
    }

    gEthApp.stats.rxExp1PktCnt = 0U;
    gEthApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthApp.stats.filterMcastRxErr++;
    }

    EthUtils_printf("test_0005: Mcast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005: Mcast: Exp2: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp2PktCnt);

    /* Part 4: Remove multicast address and receive frames with that address */
    retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, McastAddr, ETH_REMOVE_FROM_FILTER);
    if (E_OK != retVal)
    {
        gEthApp.stats.filterMcastRemErr++;
    }

    gEthApp.stats.rxExp1PktCnt = 0U;
    gEthApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthApp.stats.rxExp2PktCnt != 0U))
    {
        gEthApp.stats.filterMcastRxErr++;
    }

    EthUtils_printf("test_0005: Mcast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005: Mcast: Exp2: exp %3d, got %3d\n",
                    0U, gEthApp.stats.rxExp2PktCnt);

    /* Part 5: Add broadcast address and receive/send frames with any address */
    retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, BcastAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthApp.stats.filterBcastErr++;
    }

    gEthApp.stats.rxExp1PktCnt = 0U;
    gEthApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthApp.stats.filterBcastRxErr++;
    }

    EthUtils_printf("test_0005: Bcast: Exp1: exp %3d, got %3d\n",
                    gEthApp.stats.rxExp1PktCnt, acceptCnt);
    EthUtils_printf("test_0005: Bcast: Exp2: exp %3d, got %3d\n",
                    gEthApp.stats.rxExp2PktCnt, acceptCnt);

    /* Part 6: Reset filter and receive frames with controller's address */
    retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, NullAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthApp.stats.filterNullErr++;
    }
    /* Subscribe to spl mcast address used by host app to send mcast frames.
     * HostApp sends mcast frames with non-broadcast address so that
     * broadcast frames in network from Host PC/other machines on network
     * get routed to target test app inadvertently
     */
    if (E_OK == retVal)
    {
        retVal = Eth_UpdatePhysAddrFilter(gEthApp.ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);
    }
    if (E_OK != retVal)
    {
        gEthApp.stats.filterNullErr++;
    }


    gEthApp.stats.rxExp1PktCnt = 0U;
    gEthApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthApp.stats.rxExp2PktCnt != 0U))
    {
        gEthApp.stats.filterNullRxErr++;
    }

    EthUtils_printf("test_0005:  Null: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005:  Null: Exp2: exp %3d, got %3d\n",
                    0U, gEthApp.stats.rxExp2PktCnt);

    /* Check error conditions */
    if ((gEthApp.stats.filterUcastAddErr > 0U) ||
        (gEthApp.stats.filterUcastRemErr > 0U) ||
        (gEthApp.stats.filterUcastRxErr > 0U) ||
        (gEthApp.stats.filterMcastAddErr > 0U) ||
        (gEthApp.stats.filterMcastRemErr > 0U) ||
        (gEthApp.stats.filterMcastRxErr > 0U) ||
        (gEthApp.stats.filterBcastErr > 0U) ||
        (gEthApp.stats.filterBcastRxErr > 0U) ||
        (gEthApp.stats.filterNullErr > 0U) ||
        (gEthApp.stats.filterNullRxErr > 0U) ||
        (gEthApp.stats.detErr > 0U) ||
        (gEthApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthApp.verbose))
    {
        EthUtils_printf("Filter Test Results:\n");
        EthUtils_printf("  Status:                %s\n", status?"Pass":"Fail");
        EthUtils_printf("  Sent from host:        %d\n", num);
        EthUtils_printf("  Unicast ADD errors:    %d\n", gEthApp.stats.filterUcastAddErr);
        EthUtils_printf("  Ucast REMOVE errors:   %d\n", gEthApp.stats.filterUcastRemErr);
        EthUtils_printf("  Ucast receive errors:  %d\n", gEthApp.stats.filterUcastRxErr);
        EthUtils_printf("  Mcast ADD errors:      %d\n", gEthApp.stats.filterMcastAddErr);
        EthUtils_printf("  Mcast REMOVE errors:   %d\n", gEthApp.stats.filterMcastRemErr);
        EthUtils_printf("  Mcast receive errors:  %d\n", gEthApp.stats.filterMcastRxErr);
        EthUtils_printf("  Bcast ADD errors:      %d\n", gEthApp.stats.filterBcastErr);
        EthUtils_printf("  Bcast receive errors:  %d\n", gEthApp.stats.filterBcastRxErr);
        EthUtils_printf("  Null ADD errors:       %d\n", gEthApp.stats.filterNullErr);
        EthUtils_printf("  Null receive errors:   %d\n", gEthApp.stats.filterNullRxErr);
        EthUtils_printf("  DEM errors:            %d\n", gEthApp.stats.demErr);
        EthUtils_printf("  DET errors:            %d\n", gEthApp.stats.detErr);
        EthUtils_printf("\n");
    }

    EthUtils_printf("test_0005: END\n");

    return status;
}
#endif /* (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API) */

boolean EthApp_test_0006(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean status;

    EthUtils_printf("test_0006: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames with txConfirmation enabled */
    status = EthApp_transmit(gEthApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan,
                             &BcastAddr[0U]);

    EthUtils_printf("test_0006: END\n");

    return status;
}

boolean EthApp_test_0007(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = TRUE;
    boolean status;

    EthUtils_printf("test_0007: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit VLAN tagged frames with txConfirmation enabled */
    status = EthApp_transmit(gEthApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan,
                             &BcastAddr[0U]);

    EthUtils_printf("test_0007: END\n");

    return status;
}

boolean EthApp_test_0008(void)
{
    uint32 iterations = ETH_TEST_ITER_S_COUNT;
    uint16 len;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean st;
    boolean status = PASS;

    EthUtils_printf("test_0008: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames of different lengths */
    for (len = 10U; len <= 1500U; len += 10U)
    {
        st = EthApp_transmit(gEthApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan,
                             &BcastAddr[0U]);
        if (st == FAIL)
        {
            EthUtils_printf("test_0008: failed to transmit frames of length %u\n",
                            len);
            status = FAIL;
        }
    }

    EthUtils_printf("test_0008: END\n");

    return status;
}

boolean EthApp_test_0009(void)
{
    uint32 num = 0U;
    boolean status;

    EthUtils_printf("test_0009: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0009: failed while receiving frames\n");
    }

    EthUtils_printf("test_0009: received %d of %d frames\n",
                    gEthApp.stats.rxVlanPktCnt, ETH_TEST_ITER_M_COUNT);

    if (gEthApp.stats.rxVlanPktCnt != ETH_TEST_ITER_M_COUNT)
    {
        EthUtils_printf("test_0009: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, gEthApp.stats.rxVlanPktCnt);
        status = FAIL;
    }

    EthUtils_printf("test_0009: END\n");

    return status;
}

boolean EthApp_test_0010(void)
{
    uint32 iterations = ETH_TEST_ITER_S_COUNT;
    uint32 i;
    boolean status = PASS;
    Std_ReturnType retVal;

    EthUtils_printf("test_0010: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthApp.verbose)
        {
            EthUtils_printf("test_0010: iteration %d\n", i+1);
        }

        /* Set controller to down state */
        retVal = Eth_SetControllerMode(gEthApp.ctrlIdx, ETH_MODE_DOWN);
        if (E_OK != retVal)
        {
            EthUtils_printf("test_0010: failed to set down mode\n");
            gEthApp.stats.ctrlModeErr++;
        }
        else
        {
            gEthApp.stats.ctrlModeActCnt++;
        }

        Eth_MainFunction();

        /* Set controller back to active state */
        retVal = Eth_SetControllerMode(gEthApp.ctrlIdx, ETH_MODE_ACTIVE);
        if (E_OK != retVal)
        {
            EthUtils_printf("test_0010: failed to set active mode\n");
            gEthApp.stats.ctrlModeErr++;
        }
        else
        {
            gEthApp.stats.ctrlModeDownCnt++;
        }

        Eth_MainFunction();

        /* Check error conditions */
        if ((gEthApp.stats.ctrlModeDownCnt == 0U) ||
            (gEthApp.stats.ctrlModeActCnt == 0U) ||
            (gEthApp.stats.ctrlModeErr > 0U) ||
            (gEthApp.stats.ctrlModeIndDownCnt != gEthApp.stats.ctrlModeDownCnt) ||
            (gEthApp.stats.ctrlModeIndActCnt != gEthApp.stats.ctrlModeActCnt) ||
            (gEthApp.stats.ctrlModeIndErr > 0U) ||
            (gEthApp.stats.detErr > 0U) ||
            (gEthApp.stats.demErr > 0U))
        {
            status = FAIL;
        }

        if ((FAIL == status) || (TRUE == gEthApp.verbose))
        {
            EthUtils_printf("Controller Mode Test Results:\n");
            EthUtils_printf("  Status:                   %s\n", status?"Pass":"Fail");
            EthUtils_printf("  Requested:                %d\n", iterations);
            EthUtils_printf("  Changes to DOWN mode:     %d\n", gEthApp.stats.ctrlModeDownCnt);
            EthUtils_printf("  Changes to ACTIVE mode:   %d\n", gEthApp.stats.ctrlModeActCnt);
            EthUtils_printf("  Mode change errors:       %d\n", gEthApp.stats.ctrlModeErr);
            EthUtils_printf("  Indicated DOWN changes:   %d\n", gEthApp.stats.ctrlModeIndDownCnt);
            EthUtils_printf("  Indicated ACTIVE changes: %d\n", gEthApp.stats.ctrlModeIndActCnt);
            EthUtils_printf("  Indication errors:        %d\n", gEthApp.stats.ctrlModeIndErr);
            EthUtils_printf("\n");
        }

        if (FAIL == status)
        {
            EthUtils_printf("test_0010: failed to change controller mode\n");
            break;
        }

        /* Transmit frames */
        status = EthApp_test_0002();
        if (FAIL == status)
        {
            EthUtils_printf("test_0010: failed to transmit frames\n");
        }

        /* Receive frames */
        status = EthApp_test_0001();
        if (FAIL == status)
        {
            EthUtils_printf("test_0010: failed to receive frames\n");
        }
    }

    EthUtils_printf("test_0010: completed %d of %d iterations\n", i, iterations);
    EthUtils_printf("test_0010: END\n");

    return status;
}

boolean EthApp_test_0011(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean status = true;

    EthUtils_printf("test_0011: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames */
    status = EthApp_transmit(gEthApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan,
                             &TxMcastAddr[0U]);

    EthUtils_printf("test_0011: END\n");

    return status;
}

boolean EthApp_test_0100(uint32 frames, uint32 size)
{
    Eth_BufIdxType bufIdx;
    BufReq_ReturnType bufStatus;
    boolean txConfirmation = FALSE;
    uint8 *bufPtr;
    uint32 iterations = frames;
    uint32 retryCnt;
    uint32 i;
    uint16 len = size;
    Std_ReturnType retVal;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 priority = 0U;

    EthUtils_printf("test_0100 frames %d size %d: START\n", frames, size);

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Send frames */
    for (i = 0U; i < iterations; i++)
    {
        /* Request one buffer */
        bufStatus = EthApp_provideTxBuffer(gEthApp.ctrlIdx,
                                           priority,
                                           &bufIdx,
                                           &bufPtr,
                                           &len);

        /* Transmit it as is (only header is updated) */
        if (BUFREQ_OK == bufStatus)
        {
            retryCnt = txConfirmation ? 0U : ETHAPP_TRANSMIT_RETRY_COUNT;

            do
            {
                retVal = Eth_Transmit(gEthApp.ctrlIdx,
                                      bufIdx,
                                      (Eth_FrameType)ETHERTYPE_EXPERIMENTAL1,
                                      txConfirmation,
                                      len,
                                      BcastAddr);
                if (E_OK == retVal)
                {
                    break;
                }

                if (retryCnt > 0U)
                {
                    EthApp_delay(1U);
                    retryCnt--;
                }
                else
                {
                    break;
                }
            }
            while (TRUE);

            if (E_OK != retVal)
            {
                EthUtils_printf("test_0100: failed to send buffer\n");
            }
            else
            {
                if(gEthApp.txIrqDisable)
                {
                    Eth_TxConfirmation(gEthApp.ctrlIdx);
                }
            }
        }
        else
        {
            EthUtils_printf("test_0100: failed to get TX buffer: %d\n",
                            (int)bufStatus);
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthUtils_printf("test_0100: %d frames size %d\n", i, size);
    EthUtils_printf("test_0100: END\n");

    return PASS;
}

boolean EthApp_test_0110(void)
{
    uint16  txPktSizeMesure[] = { 1500u,   512u,    256u,    128u,    64u };
    uint32  iterator_num[]   =  { 150000u, 150000u, 150000u, 150000u, 150000u };
    boolean status = PASS;
    int i;

    EthUtils_printf("test_0110: START\n");
    for(i = 0; i< sizeof(txPktSizeMesure)/sizeof(uint16); ++i)
    {
        EthApp_delay(2000u); /* 2 second for each test */
        (void)EthApp_test_0100(iterator_num[i], txPktSizeMesure[i]);
    }

    EthUtils_printf("test_0110: DONE\n");
    return status;
}

boolean EthApp_test_0200(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint32 i;
    sint32 fillStatus;
    uint16 len = 1500U;
    boolean status = TRUE;
    EthFrame frame;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 fifoIdx = 0U;
    Eth_RxStatusType rxStatus;

    EthUtils_printf("test_0200: START\n");

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    memcpy(frame.hdr.srcMac, gEthApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send and receive frames */
    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthApp.verbose)
        {
            EthUtils_printf("test_0200: iteration %d\n", i);
        }

        gEthApp.saveRxFrame = TRUE;
        gEthApp.stats.rxPktCnt = 0U;
        gEthApp.stats.rxPktIndCnt = 0U;

        fillStatus = EthUtils_fillPayload((DataFramePayload *)frame.payload,
                                          i % ETH_TEST_NUM_TYPES,
                                          len);
        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthUtils_printf("test_0200: failed to fill test packet\n");
            status = FAIL;
            break;
        }

        /* Send the frame */
        EthApp_send(gEthApp.ctrlIdx, &frame, len);

        /* Wait for Rx frames */
        while (0 == gEthApp.stats.rxPktIndCnt)
        {
            if(gEthApp.rxIrqDisable)
            {
                Eth_Receive(gEthApp.ctrlIdx, fifoIdx, &rxStatus);
            }
        }

        /* Check if EtherType field matches */
        if (frame.hdr.etherType != gEthApp.rxFrame.hdr.etherType)
        {
            EthUtils_printf("test_0200: EtherType mismatch (exp=0x%04x, got=0x%04x)\n",
                            frame.hdr.etherType & 0xFFFFU,
                            gEthApp.rxFrame.hdr.etherType & 0xFFFFU);
            status = FAIL;
            break;
        }

        /* Check if payload matches */
        if (0 != memcmp(&frame.payload, gEthApp.rxFrame.payload, len))
        {
            EthUtils_printf("test_0200: payload mismatch\n");
            status = FAIL;
            break;
        }
    }

    EthUtils_printf("test_0200: completed %d of %d iterations\n", i, iterations);
    EthUtils_printf("test_0200: END\n");

    return status;
}

boolean EthApp_test_0300(void)
{
    uint32 i,iterations = ETH_TEST_ITER_S_COUNT;
    uint16 len = 1500;
    boolean status = PASS;
    BufReq_ReturnType bufStatus;
    Eth_BufIdxType bufIdx;
    uint8 *bufPtr;

    EthUtils_printf("test_0300: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    gEthApp.saveTxTime = 1u;
    gEthApp.txFrameCnt = 0u;
    memset(gEthApp.saveTxTimeStamp, 0, sizeof(gEthApp.saveTxTimeStamp));


    for(i = 0; i < iterations; ++i)
    {
        bufStatus = EthApp_provideTxBuffer(gEthApp.ctrlIdx,
                                               0u,
                                               &bufIdx,
                                               &bufPtr,
                                               &len);

        if(BUFREQ_OK == bufStatus)
        {
            EthUtils_fillPayload((DataFramePayload *)bufPtr,
                                    i % ETH_TEST_NUM_TYPES,
                                    len);

            Eth_EnableEgressTimeStamp(gEthApp.ctrlIdx, bufIdx);

            (void)Eth_Transmit(gEthApp.ctrlIdx,
                                          bufIdx,
                                          (Eth_FrameType)ETHERTYPE_EXPERIMENTAL1,
                                          TRUE,
                                          len,
                                          BcastAddr);

            EthApp_delay(1000u);
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    for(i = 0; i < iterations; ++i)
    {
        EthUtils_printf("Egress timestamp %d Ts: %lu %lu %u\n", i,
                gEthApp.saveTxTimeStamp[i].nanoseconds,
                gEthApp.saveTxTimeStamp[i].seconds, gEthApp.saveTxTimeStamp[i].secondsHi);
    }

    gEthApp.saveTxTime = 0u;
    EthUtils_printf("test_0300: END\n");

    return status;
}

boolean EthApp_test_0301(void)
{
    uint32 num = 0U;
    boolean status;
    int i;

    EthUtils_printf("test_0301: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    gEthApp.saveRxTime = 1u;
    gEthApp.rxFrameCnt = 0u;
    memset(gEthApp.saveRxTimeStamp, 0, sizeof(gEthApp.saveRxTimeStamp));


    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0301: failed while receiving frames\n");
    }

    EthUtils_printf("test_0301: received %d of %d frames\n",
                    gEthApp.stats.rxExp1PktCnt, ETH_TEST_ITER_S_COUNT);

    if (gEthApp.stats.rxExp1PktCnt != ETH_TEST_ITER_S_COUNT)
    {
        EthUtils_printf("test_0301: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_S_COUNT, gEthApp.stats.rxExp1PktCnt);
        status = FAIL;
    }

    for(i = 0; i < ETH_TEST_ITER_S_COUNT; ++i)
    {
        EthUtils_printf("Ingress timestamp %d Ts: %lu %lu %u\n", i,
                gEthApp.saveRxTimeStamp[i].nanoseconds,
                gEthApp.saveRxTimeStamp[i].seconds, gEthApp.saveRxTimeStamp[i].secondsHi);
    }
    gEthApp.saveRxTime = 0u;


    EthUtils_printf("test_0301: END\n");

    return status;
}

boolean EthApp_test_0302(void)
{
    uint32 i,iterations = ETH_TEST_ITER_S_COUNT;
    uint16 len = 1500;
    boolean status = PASS;
    BufReq_ReturnType bufStatus;
    Eth_BufIdxType bufIdx;
    uint8 *bufPtr;
    Eth_TimeStampQualType timeQual = ETH_INVALID;
    Eth_TimeStampType tsVal;

    EthUtils_printf("test_0302: START\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

    for(i = 0; i < iterations; ++i)
    {
        bufStatus = EthApp_provideTxBuffer(gEthApp.ctrlIdx,
                                               0u,
                                               &bufIdx,
                                               &bufPtr,
                                               &len);

        if(BUFREQ_OK == bufStatus)
        {
            EthUtils_fillPayload((DataFramePayload *)bufPtr,
                                    i % ETH_TEST_NUM_TYPES,
                                    len);
            (void)Eth_Transmit(gEthApp.ctrlIdx,
                                          bufIdx,
                                          (Eth_FrameType)ETHERTYPE_EXPERIMENTAL1,
                                          TRUE,
                                          len,
                                          BcastAddr);

            EthApp_delay(1000u);

            Eth_GetCurrentTime(gEthApp.ctrlIdx, &timeQual, &tsVal);

            EthUtils_printf("Current timestamp %d Ts: %lu %lu %u\n", timeQual,
                tsVal.nanoseconds,
                tsVal.seconds,
                tsVal.secondsHi);
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthUtils_printf("test_0302: END\n");

    return status;
}


static inline void fillVlanPayload(VlanDataFramePayload *payload,
                                 uint16_t type,
                                 uint16_t len,
                                 uint8_t pcp,
                                 uint16_t vid,
                                 uint16_t etherType)
{
    payload->tci = htons((pcp << 13) | vid);
    payload->etherType = htons(etherType);

    len -= ETH_VLAN_TAG_LEN;
    len -= ETH_TEST_DATA_HDR_LEN;
    payload->payload.type = type;
    payload->payload.len = htons(len);
}

#if (STD_ON == ETH_WRAPPER_ENABLED)
boolean EthApp_test_0400_Helper(uint16_t type,
                                 uint8_t pcp,
                                 uint16_t vid,
                                 uint16_t etherType)
{
    Eth_BufIdxType bufIdx;
    BufReq_ReturnType bufStatus;
    boolean txConfirmation = FALSE;
    uint8 *bufPtr;
    uint32 iterations = 15000;
    uint32 retryCnt;
    uint32 i;
    uint16 len = 1500U;
    Std_ReturnType retVal;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 priority = 0U;

    /* Send frames */
    for (i = 0U; i < iterations; i++)
    {
        /* Request one buffer */
        bufStatus = EthApp_provideTxBuffer(gEthApp.ctrlIdx,
                                           priority,
                                           &bufIdx,
                                           &bufPtr,
                                           &len);

        /* Transmit it as is (only header is updated) */
        if (BUFREQ_OK == bufStatus)
        {
            fillVlanPayload((VlanDataFramePayload *)bufPtr, type, len, pcp, vid, etherType);

            retryCnt = txConfirmation ? 0U : ETHAPP_TRANSMIT_RETRY_COUNT;

            do
            {
                retVal = Eth_Transmit(gEthApp.ctrlIdx,
                                      bufIdx,
                                      (Eth_FrameType)ETHERTYPE_VLAN_TAG,
                                      txConfirmation,
                                      len,
                                      BcastAddr);
                if (E_OK == retVal)
                {
                    break;
                }

                if (retryCnt > 0U)
                {
                    EthApp_delay(1U);
                    retryCnt--;
                }
                else
                {
                    break;
                }
            }
            while (TRUE);

            if (E_OK != retVal)
            {
                EthUtils_printf("test_0400: failed to send buffer\n");
            }
            else
            {
                if(gEthApp.txIrqDisable)
                {
                    Eth_TxConfirmation(gEthApp.ctrlIdx);
                }
            }
        }
        else
        {
            EthUtils_printf("test_0400: failed to get TX buffer: %d\n",
                            (int)bufStatus);
        }
    }

    return PASS;
}

#define TEST_PRIO_NUM                   (8u)
#define TEST_BANDWIDTH_PRIO_0_BPS       (10000000) /*10mbps*/
#define TEST_BANDWIDTH_PRIO_1_BPS       (20000000) /*20mbps*/
#define TEST_BANDWIDTH_PRIO_2_BPS       (30000000) /*30mbps*/
#define TEST_BANDWIDTH_PRIO_3_BPS       (40000000) /*40mbps*/
#define TEST_BANDWIDTH_PRIO_4_BPS       (50000000) /*50mbps*/
#define TEST_BANDWIDTH_PRIO_5_BPS       (60000000) /*60mbps*/
#define TEST_BANDWIDTH_PRIO_6_BPS       (70000000) /*70mbps*/
#define TEST_BANDWIDTH_PRIO_7_BPS       (80000000) /*80mbps*/

uint32 Test_RateLimit[TEST_PRIO_NUM] = {
    TEST_BANDWIDTH_PRIO_0_BPS,
    TEST_BANDWIDTH_PRIO_1_BPS,
    TEST_BANDWIDTH_PRIO_2_BPS,
    TEST_BANDWIDTH_PRIO_3_BPS,
    TEST_BANDWIDTH_PRIO_4_BPS,
    TEST_BANDWIDTH_PRIO_5_BPS,
    TEST_BANDWIDTH_PRIO_6_BPS,
    TEST_BANDWIDTH_PRIO_7_BPS,
};

boolean EthApp_test_0400(void)
{
    int i = 0;
    uint32 bandwidth;

    for(i = 0; i < TEST_PRIO_NUM; ++i)
    {
        Eth_SetBandwidthLimit(gEthApp.ctrlIdx, i, Test_RateLimit[i]);
    }

    for(i = TEST_PRIO_NUM-1; i >= 0; i--)
    {
        EthUtils_printf("test_0400: START %d\n", i);

        /* Send START cmd */
        EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

        EthApp_test_0400_Helper(ETH_TEST_TYPE_PATTERN_1, i, ETH_TEST_VLAN_VID, ETHERTYPE_EXPERIMENTAL1);

        /* Send STOP cmd */
        EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_STOP);


        Eth_GetBandwidthLimit(gEthApp.ctrlIdx, i, &bandwidth);
        EthUtils_printf("test_0400 bandwidth %d: END\n", bandwidth);
        EthApp_delay(2000);
    }

    return PASS;
}
#endif

static boolean EthApp_receiveTputHelper(uint8 ctrlIdx, uint32 num)
{
    boolean forever;
    boolean status = PASS;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 fifoIdx = 0U;
    Eth_RxStatusType rxStatus;

    /* Reset test counters */
    gEthApp.stats.rxPktCnt       = 0U;
    gEthApp.stats.rxExp3BytesCnt     = 0U;
    gEthApp.stats.rxExp3PktCnt   = 0U;
    gEthApp.stats.rxExp1PktCnt   = 0U;
    gEthApp.stats.rxExp2PktCnt   = 0U;
    gEthApp.stats.rxVlanPktCnt   = 0U;
    gEthApp.stats.rxPktNotRecv   = 0U;
    gEthApp.stats.rxPktIndCnt    = 0U;
    gEthApp.stats.rxEtherTypeErr = 0U;
    gEthApp.stats.rxPayloadErr   = 0U;
    gEthApp.stats.rxCtrlIdxErr   = 0U;
    gEthApp.stats.detErr         = 0U;
    gEthApp.stats.demErr         = 0U;

    forever = (num == 0U) ? TRUE : FALSE;

    gEthApp.runTest = TRUE;

    /* Wait for Rx frames */
    while (gEthApp.runTest)
    {
        if(gEthApp.rxIrqDisable)
        {
            Eth_Receive(ctrlIdx, fifoIdx, &rxStatus);
        }
    }

    return status;
}

boolean EthApp_receiveTput(uint32 frames, uint16 pktLen)
{
    TickType t0;
    TickType elapsed_tick;
    float32 elapsed;
    float32 pps;
    float32 mbps;
    uint32 rxframes;
    uint32 rxbytecnt;

    GetCounterValue(0, &t0);

    (void)EthApp_receiveTputHelper(gEthApp.ctrlIdx, frames);

    /* Get the "end" timestamp after DUT is done sending frames */
    GetElapsedValue(0, &t0, &elapsed_tick);
    elapsed = (float32)elapsed_tick/(1000U*1000000U);

    rxframes =  gEthApp.stats.rxExp3PktCnt;
    rxbytecnt =  gEthApp.stats.rxExp3BytesCnt;

    /* Compute elapsed time, packets per second and Mbps */
    pps = (float32)rxframes / elapsed;
    mbps = (float32)rxbytecnt * 8 / elapsed / 1000000;

    EthUtils_printf("receiveTput-%d: received %d frames in %.2f secs (%.2f frames/s, %.2f Mbps) Lost %d\n",
           pktLen, rxframes, elapsed, pps, mbps, (frames-rxframes));;

    return PASS;
}

boolean EthApp_test_0101(void)
{
    uint32 frames = 150000;
    uint16_t rxPktSizeMesure[] = { 1500u,   512u,    256u,    128u,    64u };
    uint32_t iterator_num[]    = { 150000u, 150000u, 150000u, 300000u, 300000u };
    boolean status;
    uint32 i;

    EthUtils_printf("test_0101: START\n");
    for(i = 0; i< sizeof(rxPktSizeMesure)/sizeof(uint16); ++i)
    {
        EthApp_delay(2000u); /* 2 second for each test */

        frames = iterator_num[i];

        /* Send START cmd */
        EthApp_sendCmd(gEthApp.ctrlIdx, CTRL_FRAME_CMD_START);

        /* Receive packets and measure the throughput */
        status = EthApp_receiveTput(frames, rxPktSizeMesure[i]);
        if (status == FAIL)
            EthUtils_printf("test_0101: failed to get receive throughput\n");
    }
    EthUtils_printf("test_0101: END\n");

    return status;
}

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
boolean EthApp_test_0500(void)
{
    Std_ReturnType retVal = E_OK;
    uint8 trcvIdx = ETHTRCV_DRV_CONFIG_0->trcvIdx;
    uint32 iterations = 100;
    uint32 i;

    EthUtils_printf("test_0300: START\n");

    for (i = 0U; i < iterations; i++)
    {
            /* Get Tranceiver Link State */
        retVal = EthApp_getTranceiverLinkState(trcvIdx);
        if (E_OK == retVal)
        {
            /* check Link State every 1 sec */
            EthApp_delay(1000U);
        }
        else
        {
            EthUtils_printf("test_0300: Read Transceiver Link State Failed\n");
            break;
        }
    }

    EthUtils_printf("test_0300: END\n");
    return (E_OK == retVal) ? PASS : FAIL;
}
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */
