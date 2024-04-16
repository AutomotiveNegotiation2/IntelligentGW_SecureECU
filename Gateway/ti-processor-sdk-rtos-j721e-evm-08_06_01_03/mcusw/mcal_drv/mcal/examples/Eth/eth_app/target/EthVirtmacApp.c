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
 *  \file     EthVirtmacApp.c
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
#include "Eth_VirtMac.h"

#include <EthUtils.h>

#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/osal/osal.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/TimerP.h>

#include <CddIpc/ipc_baremetal_hw/ipc.h>
#include <CddIpc/ipc_baremetal_hw/soc/ipc_soc.h>
#include <hw_include/lldr.h>
#include <hw_include/lld_mailbox.h>

#include "Cdd_Ipc.h"
#include "Cdd_IpcIrq.h"

#if defined (SOC_J721E)
#include "IntRtr_Cfg.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if (STD_OFF == ETH_VIRTUALMAC_SUPPORT)
#error "ETH_VIRTUALMAC_SUPPORT is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_SUBSCRIBEDSTMAC_API)
#error "ETH_VIRTUALMAC_SUBSCRIBEDSTMAC_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_UNSUBSCRIBEDSTMAC_API)
#error "ETH_VIRTUALMAC_UNSUBSCRIBEDSTMAC_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_NOTIFYMSGRECEIVED_API)
#error "ETH_VIRTUALMAC_NOTIFYMSGRECEIVED_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_ADD_UNICAST_MACADDR_API)
#error "ETH_VIRTUALMAC_ADD_UNICAST_MACADDR_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_DEL_MACADDR_API)
#error "ETH_VIRTUALMAC_DEL_MACADDR_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_ADD_MCAST_MACADDR_API)
#error "ETH_VIRTUALMAC_ADD_MCAST_MACADDR_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_ADD_VLAN_API)
#error "ETH_VIRTUALMAC_ADD_VLAN_API is required for Ethernet Virtual MAC test app"
#endif
#if (STD_OFF == ETH_VIRTUALMAC_DEL_VLAN_API)
#error "ETH_VIRTUALMAC_DEL_VLAN_API is required for Ethernet Virtual MAC test app"
#endif

#define VQ_BUF_SIZE             (2048)
#define IPC_RPMESSAGE_OBJ_SIZE  (256)
#define RPMSG_DATA_SIZE         (256 * 512 + IPC_RPMESSAGE_OBJ_SIZE)
#if defined (SOC_J7200)
#define IPC_VRING_MEM_SIZE      (0x00800000u)
#elif defined (SOC_J784S4)
#define IPC_VRING_MEM_SIZE      (0x03000000u)
#else
#define IPC_VRING_MEM_SIZE      (0x02000000u)
#endif
/** \brief Packet transmit retry in non-confirmation mode */
#define ETHVIRTMACAPP_TRANSMIT_RETRY_COUNT     (2U)
#define ETHVIRTMACAPP_REMOTEETHDEVICE_COMCHID  (CddIpcConf_IpcComChanId_Cdd_IpcMcu20_EthDevice)
#define ETHVIRTMACAPP_ETHMAIN_SCHEDULE_PERIOD_MS  (100U)

#define UTILS_ARRAYSIZE(x) sizeof(x)/sizeof (x[0U])
#define UTILS_ALIGN(x,align)  ((((x) + ((align) - 1))/(align)) * (align))

#define EthVirtmacAppUtils_assert(cond)                                     \
    (EthVirtmacAppUtils_assertLocal((boolean) (cond), (const char *) # cond, \
                    (const char *) __FILE__, (sint32) __LINE__))

#define EthVirtmac_printf        printf

#if defined(SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4) || defined (SOC_AM62X)
#define ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM              (290U)
#define ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM              (291U)
#elif defined (SOC_J721E)
#define ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM              (INTRTR_CFG_MAIN_DOMAIN_TIMER_3_OUT_INT_NO + INTRTR_CFG_START_LEVEL_INT_NUMBER) /* GP timer 2 */
#define ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM              (INTRTR_CFG_MAIN_DOMAIN_TIMER_4_OUT_INT_NO + INTRTR_CFG_START_LEVEL_INT_NUMBER) /* GP timer 3 */
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef boolean (*TestFunc)(void);

/** \brief Ethernet test statistics (not to be confused with Ethernet statistics) */
typedef struct EthVirtmacApp_Stats_s
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

    volatile uint32 rxExp1PktCnt;
    /**< Number of data received packets with experimental 1 type (EthIf_RxIndication()) */

    volatile uint32 rxExp2PktCnt;
    /**< Number of data received packets with experimental 2 type (EthIf_RxIndication()) */

    volatile uint32 rxVlanPktCnt;
    /**< Number of data received packets with VLAN tag (EthIf_RxIndication()) */

    volatile uint32 rxPktErr;
    /**< Number of receive errors (Eth_Receive()) */

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

    volatile uint32 etherStatsErr;
    /**< Ethernet statistics errors (Eth_GetEtherStats()) */

    volatile uint32 etherDropCountErr;
    /**< Ethernet statistics errors (Eth_GetEtherStats()) */

    volatile uint32 demErr;
    /**< DEM errors (Dem_SetEventStatus()) */

    volatile uint32 detErr;
    /**< DET errors (Det_ReportError()) */
} EthVirtmacApp_Stats;

/** \brief Ethernet test state */
typedef struct EthVirtmacApp_State_s
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

    EthVirtmacApp_Stats stats;
    /**< Test statistics (not to be confused with Ethernet statistics) */

    boolean verbose;
    /**< Enable verbose */

    boolean veryVerbose;
    /**< Enable very verbose logs */

    SemaphoreP_Handle ethNotifySem;
    /**< Semaphore Handle to indicate rpc msg processing complete */

    uint8 expectedSid;
    /**< Semaphore Handle to indicate rpc msg processing complete */

    TimerP_Handle hEthMainPollTimer;
    /**< Handle to timer instance used to regularly invoke Eth_Main() */

    uint8 rxIrqDisable;
    /* Disable or enable Rx irq */

    uint8 txIrqDisable;
    /* Disable or enable Tx irq */
} EthVirtmacApp_State;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void EthVirtmacApp_delay(uint32 msecs);

static void EthVirtmacApp_ethStartup(void);

/* Main Eth / EthTrcv initialization/deinitialization functions */

static Std_ReturnType EthVirtmacApp_init(uint8 ctrlIdx);

static Std_ReturnType EthVirtmacApp_deinit(uint8 ctrlIdx);


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

void EthIf_TrcvModeIndication(uint8 CtrlIdx,
                              EthTrcv_ModeType TrcvMode);

/* Test helper functions */

static BufReq_ReturnType EthVirtmacApp_provideTxBuffer(uint8 ctrlIdx,
                                                       uint8 priority,
                                                       Eth_BufIdxType* bufIdxPtr,
                                                       uint8** bufPtr,
                                                       uint16* lenBytePtr);
static void EthVirtmacApp_send(uint8 ctrlIdx,
                        EthFrame *frame,
                        uint16 len);

static void EthVirtmacApp_sendCmd(uint8 ctrlIdx,
                           uint8 cmd);

static boolean EthVirtmacApp_transmit(uint8 ctrlIdx,
                               uint32 num,
                               uint16 len,
                               boolean txConfirmation,
                               boolean vlan);

static boolean EthVirtmacApp_receive(uint8 ctrlIdx,
                              uint32 num);

static const char *EthVirtmacApp_errorIdToString(uint8 errorId);

static const char *EthVirtmacApp_apiIdToString(uint8 apiId);

void EthVirtmacApp_wbInvCache(uint8 *buf, uint16 len);

void EthVirtmacApp_invCache(uint8 *buf, uint16 len);

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
boolean EthVirtmacApp_test_0001(void);

/**
 * \brief Test basic frame transmission
 *
 * Basic DUT frame transmission test.  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged frames without confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthVirtmacApp_test_0002(void);

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
boolean EthVirtmacApp_test_0003(void);

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
boolean EthVirtmacApp_test_0004(void);

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
boolean EthVirtmacApp_test_0005(void);


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
boolean EthVirtmacApp_test_0006(void);

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
boolean EthVirtmacApp_test_0007(void);

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
boolean EthVirtmacApp_test_0008(void);

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
boolean EthVirtmacApp_test_0009(void);

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
boolean EthVirtmacApp_test_0010(void);

/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput over ETH_TEST_ITER_L_COUNT frames. The target
 * performs the following operations:
 * - Get the initial timestamp corresponding to the first frame received
 * - Receive frames until the STOP is detected and get the final timestamp
 * - Compute the transmit throughput from the number of received frames and the
 *   time difference between the two captured timestamps
 *
 * \return PASS or FAIL  Test result
 */
boolean EthVirtmacApp_test_0100(void);

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
boolean EthVirtmacApp_test_0200(void);

void EthVirtmacApp_initMainFunctionPoll(void);
static void EthVirtmacApp_clockFxn (uintptr_t arg);
static Std_ReturnType EthVirtmacApp_ipcInit(void);
static void EthVirtmacApp_initIpcCddCfg(struct Cdd_IpcConfigType_s *ipcCddCfg);
static void EthVirtmacApp_ipcStartup(void);
static void EthVirtmacApp_ipcMbIntRegForMcu20(void);
static sint32 EthVirtmacApp_sciclientIrqSet(uint16 coreId, uint32 clusterId, uint32 userId, uint32 intNumber);
static sint32 EthVirtmacApp_sciclientIrqRelease(uint16 coreId, uint32 clusterId, uint32 userId, uint32 intNumber);
static uint32 EthVirtmacApp_ipcMailboxClear(uint32 baseAddr, uint32 queueId);
static void EthVirtmacApp_ipcMsgFromMcu20Isr(uintptr_t notUsed);
static void EthVirtmacApp_ipcInterruptConfig(void);
static void EthVirtmacApp_ipcPrintVersion(void);
static void EthVirtmacApp_addUnicastAddr(uint8 *macAddr, Eth_PortType port);
static void EthVirtmacApp_virtmacInit(Eth_ConfigType *ethConfig);
static void EthVirtmacApp_getEthConfig(Eth_ConfigType *ethConfig);
static void EthVirtmacApp_recvMsgNotify(void);
void EthVirtmacApp_rpcFwRegistered (uint8 controllerIdx);
void EthVirtmacApp_rpcCmdComplete (uint8 controllerIdx, uint8 sid, Std_ReturnType status);
static void EthVirtmacApp_subscribeDefaultAddr(uint8 *macAddress);
static void EthVirtmacApp_ethInterruptConfig(void);
static void EthVirtmacApp_addSubHostUcastAddr(uint8 *macAddress);
static void EthVirtmacApp_delUnsubAddr(uint8 *macAddress);
static void EthVirtmacApp_registerMacAddr(uint8 *macAddress);
static void EthVirtmacApp_unregisterMacAddr(uint8 *macAddress);
void EthVirtmacApp_delAddr(uint8 *macAddr);
static void EthVirtmacApp_addMcastAddr(uint8 *macAddr, boolean addHostPort);
static void EthVirtmacApp_addSubMcastAddr(uint8 *macAddr);
void EthVirtmacApp_freeEthResources(void);
static void EthVirtmacApp_addVlanId(uint32 vlanId);
static void EthVirtmacApp_delVlanId(uint32 vlanId);


static inline void EthVirtmacAppUtils_assertLocal(boolean condition,
                                            const char *str,
                                            const char *fileName,
                                            sint32 lineNum)
{
    volatile static boolean gEthVirtmacAppAssertWaitInLoop = TRUE;

    if (!(condition))
    {
        EthVirtmac_printf("Assertion @ Line: %d in %s: %s : failed !!!\n",
                           lineNum, fileName, str);
        while (gEthVirtmacAppAssertWaitInLoop)
        {
        }
    }

    return;
}


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static TestFunc testFuncs[] =
{
    &EthVirtmacApp_test_0001,
    &EthVirtmacApp_test_0002,
    &EthVirtmacApp_test_0003,
    &EthVirtmacApp_test_0004,
    &EthVirtmacApp_test_0005,
    &EthVirtmacApp_test_0006,
    &EthVirtmacApp_test_0007,
    &EthVirtmacApp_test_0008,
    &EthVirtmacApp_test_0009,
    &EthVirtmacApp_test_0010,
    &EthVirtmacApp_test_0100,
};

/* Broadcast MAC address */
static uint8 BcastAddr[ETH_HW_ADDR_LEN] =
{
    0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU
};

static uint8 TargetMcastAddr[ETH_HW_ADDR_LEN] =
{
    0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U
};

/* Null MAC address */
uint8 NullAddr[ETH_HW_ADDR_LEN] =
{
    0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};

/* Unicast MAC address */
static uint8 UcastAddr[ETH_HW_ADDR_LEN] =
{
    0x0aU, 0x0bU, 0x0cU, 0x0dU, 0x0eU, 0x0fU
};

/* Unicast MAC address */
static uint8 UcastOpenFilterAddr[ETH_HW_ADDR_LEN] =
{
    0x08U, 0x00U, 0x28U, 0x01U, 0xf6U, 0x7cU
};

/* Multicast MAC address */
static uint8 McastAddr[ETH_HW_ADDR_LEN] =
{
    0x01U, 0x00U, 0x5eU, 0x0dU, 0x0eU, 0x0fU
};


/* Eth application state */
EthVirtmacApp_State gEthVirtmacApp;

static uint8 sysVqBuf[VQ_BUF_SIZE]  __attribute__ ((section("ipc_data_buffer"), aligned(8)));
static uint8 gCntrlBuf[RPMSG_DATA_SIZE] __attribute__ ((section("ipc_data_buffer"), aligned(8)));

static uint8 g_vringMemBuf[IPC_VRING_MEM_SIZE] __attribute__ ((section(".bss:ipc_vring_mem"), aligned(8192)));

static uint32 selfProcId = IPC_MCU2_1;
static uint32 gRemoteProc[] =
{
    IPC_MPU1_0,
    IPC_MCU1_0,
    IPC_MCU1_1,
    IPC_MCU2_0,
#if defined (SOC_J721E)
    IPC_MCU3_0,
    IPC_MCU3_1,
    IPC_C66X_1,
    IPC_C66X_2,
    IPC_C7X_1,
#elif defined (SOC_J784S4)
    IPC_MCU3_0,
    IPC_MCU3_1,
    IPC_MCU4_0,
    IPC_MCU4_1,
    IPC_C7X_1,
    IPC_C7X_2,
    IPC_C7X_3,
    IPC_C7X_4,
#endif
};
static uint32 gNumRemoteProc = sizeof(gRemoteProc) / sizeof(uint32);

/* Indexed list of src ids */
static const uint16 ipc_map_src_id[] =
{
    TISCI_DEV_NAVSS0_MAILBOX_0,
    TISCI_DEV_NAVSS0_MAILBOX_1,
    TISCI_DEV_NAVSS0_MAILBOX_2,
    TISCI_DEV_NAVSS0_MAILBOX_3,
    TISCI_DEV_NAVSS0_MAILBOX_4,
    TISCI_DEV_NAVSS0_MAILBOX_5,
    TISCI_DEV_NAVSS0_MAILBOX_6,
    TISCI_DEV_NAVSS0_MAILBOX_7,
    TISCI_DEV_NAVSS0_MAILBOX_8,
    TISCI_DEV_NAVSS0_MAILBOX_9,
    TISCI_DEV_NAVSS0_MAILBOX_10,
    TISCI_DEV_NAVSS0_MAILBOX_11,
};

/* Indexed list of host ids */
static const uint16 ipc_map_host_id[] =
{
    TISCI_HOST_ID_A72_0,
    TISCI_HOST_ID_MCU_0_R5_0,
    TISCI_HOST_ID_MCU_0_R5_2,
    TISCI_HOST_ID_MAIN_0_R5_0,
    TISCI_HOST_ID_MAIN_0_R5_2,
#if defined (SOC_J721E)
    TISCI_HOST_ID_MAIN_1_R5_0,
    TISCI_HOST_ID_MAIN_1_R5_2,
    TISCI_HOST_ID_C6X_0_1,
    TISCI_HOST_ID_C6X_1_1,
    TISCI_HOST_ID_C7X_1,
#elif defined (SOC_J784S4)
    TISCI_HOST_ID_MAIN_1_R5_0,
    TISCI_HOST_ID_MAIN_1_R5_2,
    TISCI_HOST_ID_MAIN_2_R5_0,
    TISCI_HOST_ID_MAIN_2_R5_2,
    TISCI_HOST_ID_C7X_0_0,
    TISCI_HOST_ID_C7X_1_0,
    TISCI_HOST_ID_C7X_2_0,
    TISCI_HOST_ID_C7X_3_0,
#endif
};

/* Indexed list of dst ids */
static const uint16 ipc_map_dst_id[] =
{
    TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
    TISCI_DEV_MCU_R5FSS0_CORE0,
    TISCI_DEV_MCU_R5FSS0_CORE1,
    TISCI_DEV_R5FSS0_CORE0,
    TISCI_DEV_R5FSS0_CORE1,
#if defined (SOC_J721E)
    TISCI_DEV_R5FSS1_CORE0,
    TISCI_DEV_R5FSS1_CORE1,
    TISCI_DEV_C66SS0_CORE0,
    TISCI_DEV_C66SS1_CORE0,
    TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
#elif defined (SOC_J784S4)
    TISCI_DEV_R5FSS1_CORE0,
    TISCI_DEV_R5FSS1_CORE1,
    TISCI_DEV_R5FSS2_CORE0,
    TISCI_DEV_R5FSS2_CORE1,
#endif
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32 i;
    boolean status;
    boolean globalStatus = TRUE;
    Std_ReturnType retVal;
#if (STD_OFF == ETH_PRE_COMPILE_VARIANT)
    /* this time configuration is not ready yet */
    extern CONST(Eth_ConfigType, ETH_VAR_NO_INIT) EthConfigSet_0;
    extern P2CONST(Eth_ConfigType, ETH_VAR_NO_INIT, ETH_APPL_CONST) Eth_CfgPtr;
    Eth_CfgPtr = (Eth_ConfigType *)&EthConfigSet_0;
#endif

    /* Initialize the global app structure */
    gEthVirtmacApp.ctrlIdx = 0U;
    gEthVirtmacApp.verbose = FALSE;
    gEthVirtmacApp.veryVerbose = FALSE;
    gEthVirtmacApp.txIrqDisable = FALSE; /* default is using TX IRQ */
    gEthVirtmacApp.rxIrqDisable = FALSE; /* default is using RX IRQ */

    if(Eth_GetTxEnableInterrupt(gEthVirtmacApp.ctrlIdx) == FALSE)
    {
        gEthVirtmacApp.txIrqDisable = TRUE;
    }

    if(Eth_GetTxEnableInterrupt(gEthVirtmacApp.ctrlIdx) == FALSE)
    {
        gEthVirtmacApp.rxIrqDisable = TRUE;
    }

    memset(&gEthVirtmacApp.macAddr, 0U, ETH_MAC_ADDR_LEN);
    memset(&gEthVirtmacApp.stats, 0U, sizeof(EthVirtmacApp_Stats));

    /* Print date and time */
    EthVirtmac_printf("Eth Application build date/time: %s, %s\n", __DATE__, __TIME__);

    EthVirtmac_printf("Eth Application Starts\n");

    /* System initialization */
    EthVirtmacApp_ethStartup();

    /* System initialization */
    EthVirtmacApp_ipcStartup();

#if (STD_OFF == ETH_PRE_COMPILE_VARIANT)
    Eth_CfgPtr = (Eth_ConfigType *)NULL_PTR;
#endif

    /* Initialize the Eth driver and controller */
    retVal = EthVirtmacApp_ipcInit();
    if (E_OK != retVal)
    {
        EthVirtmac_printf("Failed to initialize: %d\n", retVal);
        return retVal;
    }


    /* Initialize the Eth driver and controller */
    retVal = EthVirtmacApp_init(gEthVirtmacApp.ctrlIdx);
    if (E_OK != retVal)
    {
        EthVirtmac_printf("Failed to initialize: %d\n", retVal);
        return retVal;
    }

    /* Main test section */
    if (E_OK == retVal)
    {
        if (Eth_GetLoopBackMode(gEthVirtmacApp.ctrlIdx))
        {
            status = EthVirtmacApp_test_0200();
            globalStatus &= status;
            EthVirtmac_printf("Test 0200: %s\n", status?"Pass":"Fail");
        }
        else
        {
            /* Send command indicating that we're ready to start the test stage */
            EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_READY);

            for (i = 0U; i < ARRAY_SIZE(testFuncs); i++)
            {
                EthVirtmac_printf("\n\n-----------------------------------------------------------\n");
                memset(&gEthVirtmacApp.stats, 0U, sizeof(EthVirtmacApp_Stats));
                status = testFuncs[i]();
                globalStatus &= status;
                EthVirtmac_printf("Test Result: %s\n", status?"Pass":"Fail");
                EthVirtmac_printf("-----------------------------------------------------------\n");
            }
        }
    }
    EthVirtmac_printf("\n");

    /* Deinitialize the Ethernet controller */
    if (E_OK == retVal)
    {
        retVal = EthVirtmacApp_deinit(gEthVirtmacApp.ctrlIdx);
        if (E_OK != retVal)
        {
            EthVirtmac_printf("Failed to deinitialize: %d\n", retVal);
        }
    }

    EthVirtmac_printf("ETH Stack Usage: %d bytes\n", AppUtils_GetStackUsage());
    if (AppUtils_EthCheckStackAndSectionCorruption() != E_OK)
    {
        retVal = E_NOT_OK;
        EthVirtmac_printf("ETH Stack/section corruption!!!\n");
    }

    EthVirtmac_printf("Tests Results: %s\n",
                      (globalStatus == TRUE) ? "PASS" : "FAIL");

    if (E_OK == retVal)
    {
        EthVirtmac_printf("Eth Application Completed\n");
    }
    else
    {
        EthVirtmac_printf("Eth Application Failed\n");
    }

    return 0;
}

static void EthVirtmacApp_delay(uint32 msecs)
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

static void EthVirtmacApp_ethStartup(void)
{
    /* Equivalent to EcuM_AL_SetProgrammableInterrupts */
    Intc_Init();

    EthVirtmacApp_ethInterruptConfig();

    Intc_SystemEnable();

    /* Initialize counters, that would be required for timed operations */
    AppUtils_ProfileInit(0);

    /* Initialize memory sections  */
    AppUtils_EthSectionInit();
}

#define ETH_START_SEC_ISR_CODE
#include "Eth_MemMap.h"

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

static void EthVirtmacApp_ethInterruptConfig(void)
{
    OsalRegisterIntrParams_t intrPrms;
    OsalInterruptRetCode_e retVal = OSAL_INT_SUCCESS;
    HwiP_Handle hwiHandle;

    if(gEthVirtmacApp.txIrqDisable == FALSE)
    {
        /* TX DMA completion interrupt */
        if (OSAL_INT_SUCCESS == retVal)
        {
            Osal_RegisterInterrupt_initParams(&intrPrms);
            intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
            intrPrms.corepacConfig.isrRoutine      = &Eth_TxIrqHdlr_0_wrapper;
            intrPrms.corepacConfig.priority        = 1U;
            intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
            intrPrms.corepacConfig.intVecNum       = Eth_GetTxEventCoreIntrNum(gEthVirtmacApp.ctrlIdx);

            retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
            if (OSAL_INT_SUCCESS != retVal)
            {
                EthVirtmac_printf("interruptConfig: failed to register TX DMA int: %d\n", retVal);
            }
        }
    }

    if(gEthVirtmacApp.rxIrqDisable == FALSE)
    {
        /* RX DMA completion interrupt */
        if (OSAL_INT_SUCCESS == retVal)
        {
            Osal_RegisterInterrupt_initParams(&intrPrms);
            intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
            intrPrms.corepacConfig.isrRoutine      = &Eth_RxIrqHdlr_0_wrapper;
            intrPrms.corepacConfig.priority        = 1U;
            intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
            intrPrms.corepacConfig.intVecNum       = Eth_GetRxEventCoreIntrNum(gEthVirtmacApp.ctrlIdx);

            retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
            if (OSAL_INT_SUCCESS != retVal)
            {
                EthVirtmac_printf("interruptConfig: failed to register RX DMA int: %d\n", retVal);
            }
        }
    }

    if(TRUE == Eth_GetRxIrqPacingEnable(gEthVirtmacApp.ctrlIdx) && E_OK == retVal)
    {
        if (OSAL_INT_SUCCESS == retVal)
        {
#if defined (SOC_J721E)
            {
                struct tisci_msg_rm_irq_set_req     rmIrqReq;
                struct tisci_msg_rm_irq_set_resp    rmIrqResp;
                rmIrqReq.valid_params           = TISCI_MSG_VALUE_RM_DST_ID_VALID;
                rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
                rmIrqReq.src_id                 = TISCI_DEV_TIMER2;
                rmIrqReq.global_event           = 0U;
                rmIrqReq.src_index              = 0U;
                rmIrqReq.dst_id                 = TISCI_DEV_R5FSS0_CORE1;
                rmIrqReq.dst_host_irq           = ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM;
                rmIrqReq.ia_id                  = 0U;
                rmIrqReq.vint                   = 0U;
                rmIrqReq.vint_status_bit_index  = 0U;
                rmIrqReq.secondary_host         = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
                (void)Sciclient_rmIrqSet(
                             &rmIrqReq, &rmIrqResp, APP_SCICLIENT_TIMEOUT);
            }
#endif

            Osal_RegisterInterrupt_initParams(&intrPrms);
            intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
            intrPrms.corepacConfig.isrRoutine      = &Eth_RxIrqPacingHdlr_0_wrapper;
            intrPrms.corepacConfig.priority        = 1U;
            intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
            intrPrms.corepacConfig.intVecNum       = ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM;

            retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
            if (OSAL_INT_SUCCESS != retVal)
            {
                EthVirtmac_printf("interruptConfig: failed to register RX DMA int: %d\n", retVal);
            }
        }
    }

    if(TRUE == Eth_GetTxIrqPacingEnable(gEthVirtmacApp.ctrlIdx) && E_OK == retVal)
    {
        if (OSAL_INT_SUCCESS == retVal)
        {
#if defined (SOC_J721E)
            {
                struct tisci_msg_rm_irq_set_req     rmIrqReq;
                struct tisci_msg_rm_irq_set_resp    rmIrqResp;
                rmIrqReq.valid_params           = TISCI_MSG_VALUE_RM_DST_ID_VALID;
                rmIrqReq.valid_params          |= TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID;
                rmIrqReq.src_id                 = TISCI_DEV_TIMER3;
                rmIrqReq.global_event           = 0U;
                rmIrqReq.src_index              = 0U;
                rmIrqReq.dst_id                 = TISCI_DEV_R5FSS0_CORE1;
                rmIrqReq.dst_host_irq           = ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM;
                rmIrqReq.ia_id                  = 0U;
                rmIrqReq.vint                   = 0U;
                rmIrqReq.vint_status_bit_index  = 0U;
                rmIrqReq.secondary_host         = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
                (void)Sciclient_rmIrqSet(
                             &rmIrqReq, &rmIrqResp, APP_SCICLIENT_TIMEOUT);
            }
#endif
            Osal_RegisterInterrupt_initParams(&intrPrms);
            intrPrms.corepacConfig.arg             = (uintptr_t)NULL_PTR;
            intrPrms.corepacConfig.isrRoutine      = &Eth_TxIrqPacingHdlr_0_wrapper;
            intrPrms.corepacConfig.priority        = 1U;
            intrPrms.corepacConfig.corepacEventNum = 0U; /* not used? */
            intrPrms.corepacConfig.intVecNum       = ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM;

            retVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
            if (OSAL_INT_SUCCESS != retVal)
            {
                EthVirtmac_printf("interruptConfig: failed to register RX DMA int: %d\n", retVal);
            }
        }     
    }    
}

static Std_ReturnType EthVirtmacApp_init(uint8 ctrlIdx)
{
    const Eth_ConfigType *ethCfg = (const Eth_ConfigType *)NULL_PTR;
    uint8 addr[ETH_MAC_ADDR_LEN];
    Std_ReturnType retVal;

    /* Eth driver initialization */
#if (STD_OFF == ETH_PRE_COMPILE_VARIANT)
    extern CONST(Eth_ConfigType, ETH_VAR_NO_INIT) EthConfigSet_0;
    ethCfg = (const Eth_ConfigType *)&EthConfigSet_0;
#endif
    EthVirtmacApp_getEthConfig((Eth_ConfigType *) ethCfg);

    retVal = Eth_VirtMacRpcInit((Eth_ConfigType *) ethCfg);
    if (E_OK != retVal)
    {
        EthVirtmac_printf("init: failed to initialize Eth RPC \n");
    }

    //EthVirtmacApp_initMainFunctionPoll();
    /* Wait for ethFw registration */
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);

    EthVirtmacApp_virtmacInit((Eth_ConfigType *) ethCfg);

    /* Eth controller initialization */
    Eth_Init(ethCfg);

    /* Set controller to active mode */
    if (E_OK == retVal)
    {
        retVal = Eth_SetControllerMode(ctrlIdx, ETH_MODE_ACTIVE);
        if (E_OK != retVal)
        {
            EthVirtmac_printf("init: failed to set the controller to active mode\n");
        }
    }

    if (E_OK == retVal)
    {
        Eth_ConfigType *ethConfig = (Eth_ConfigType *) ethCfg;
        uint8 macAddress[ETH_MAC_ADDR_LEN];

        Eth_GetPhysAddr(ctrlIdx, macAddress);
        EthVirtmacApp_subscribeDefaultAddr(macAddress);
    }

    /* Print initial physical address */
    if (E_OK == retVal)
    {
        Eth_GetPhysAddr(ctrlIdx, addr);
        EthVirtmac_printf("MAC Port %d Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
                        ctrlIdx + 1,
                        addr[0U], addr[1U], addr[2U],
                        addr[3U], addr[4U], addr[5U]);
    }

    return retVal;
}

static Std_ReturnType EthVirtmacApp_deinit(uint8 ctrlIdx)
{
    Std_ReturnType retVal;

    /* Set controller to down mode */
    retVal = Eth_SetControllerMode(ctrlIdx, ETH_MODE_DOWN);
    if (E_OK != retVal)
    {
        EthVirtmac_printf("deinit: failed to set the controller to down mode\n");
    }

    return retVal;
}



void EthIf_TxConfirmation(uint8 ctrlIdx,
                          Eth_BufIdxType bufIdx,
                          Std_ReturnType result)
{
    if (E_OK == result)
    {
        gEthVirtmacApp.stats.txConfPktCnt++;
    }
    else if (E_NOT_OK == result)
    {
        EthVirtmac_printf("TxConfirmation: transmission of buffer %d failed\n", bufIdx);
        gEthVirtmacApp.stats.txPktErr++;
    }
    else
    {
        EthVirtmac_printf("TxConfirmation: invalid confirmation result %d for buffer %d\n",
                          result, bufIdx);
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

    if (TRUE == gEthVirtmacApp.veryVerbose)
    {
        EthVirtmac_printf("EthIf_RxIndication: len: %d, bcast: %s, EtherType: 0x%04x\n",
                        lenByte,
                        IsBroadcast ? "yes" : "no",
                        FrameType & 0xFFFFU);
    }

    /* Check that the correct controller index is being reported */
    if (ctrlIdx != gEthVirtmacApp.ctrlIdx)
    {
        EthVirtmac_printf("EthIf_RxIndication: incorrect controller index "
                        "(got %d, exp %d)\n",
                        ctrlIdx, gEthVirtmacApp.ctrlIdx);
        gEthVirtmacApp.stats.rxCtrlIdxErr++;
    }

    /* Validate packet content according to its EtherType */
    switch (FrameType)
    {
    case ETHERTYPE_EXP_CONTROL:
        cmd = buf[0];
        switch (cmd)
        {
        case CTRL_FRAME_CMD_START:
            gEthVirtmacApp.runTest = TRUE;
            break;
        case CTRL_FRAME_CMD_STOP:
            gEthVirtmacApp.runTest = FALSE;
            break;
        default:
            EthVirtmac_printf("EthIf_RxIndication: invalid control command: %d\n", cmd);
            break;
        }
        gEthVirtmacApp.stats.rxPktCnt++;
        break;

    case ETHERTYPE_VLAN_TAG:
        ret = EthUtils_checkVlanTagAndPayload((VlanDataFramePayload *)DataPtr,
                                              pcp, vid, ETHERTYPE_EXPERIMENTAL1);
        if (ETH_TEST_PKT_SOK != ret)
        {
            EthVirtmac_printf("EthIf_RxIndication: VLAN tagged payload error: %d\n", ret);
            gEthVirtmacApp.stats.rxPayloadErr++;
        }
        else
        {
            gEthVirtmacApp.stats.rxPktCnt++;
            gEthVirtmacApp.stats.rxVlanPktCnt++;
        }
        break;

    case ETHERTYPE_EXPERIMENTAL1:
        ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
        if (ETH_TEST_PKT_SOK != ret)
        {
            EthVirtmac_printf("EthIf_RxIndication: packet validation failed: %d\n", ret);
            gEthVirtmacApp.stats.rxPayloadErr++;
        }
        else
        {
            gEthVirtmacApp.stats.rxPktCnt++;
            gEthVirtmacApp.stats.rxExp1PktCnt++;
        }
        break;

    case ETHERTYPE_EXPERIMENTAL2:
        ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
        if (ETH_TEST_PKT_SOK != ret)
        {
            EthVirtmac_printf("EthIf_RxIndication: packet validation failed: %d\n", ret);
            gEthVirtmacApp.stats.rxPayloadErr++;
        }
        else
        {
            gEthVirtmacApp.stats.rxPktCnt++;
            gEthVirtmacApp.stats.rxExp2PktCnt++;
        }
        break;

    default:
        gEthVirtmacApp.stats.rxEtherTypeErr++;
        break;
    }

    if (gEthVirtmacApp.saveRxFrame)
    {
        if (IsBroadcast)
        {
            memset(gEthVirtmacApp.rxFrame.hdr.dstMac, 0xff, ETH_MAC_ADDR_LEN);
        }
        else
        {
            memset(gEthVirtmacApp.rxFrame.hdr.dstMac, 0x00U, ETH_MAC_ADDR_LEN);
        }

        memcpy(gEthVirtmacApp.rxFrame.hdr.srcMac, PhysAddrPtr, ETH_MAC_ADDR_LEN);
        gEthVirtmacApp.rxFrame.hdr.etherType = (uint16)FrameType;
        memcpy(gEthVirtmacApp.rxFrame.payload, DataPtr, lenByte);
        gEthVirtmacApp.saveRxFrame = FALSE;
    }

    gEthVirtmacApp.stats.rxPktIndCnt++;
}

void EthIf_CtrlModeIndication(uint8 ControllerId,
                              Eth_ModeType ControllerMode)
{
    if (ETH_MODE_DOWN == ControllerMode)
    {
        EthVirtmac_printf("EthIf_CtrlModeIndication: DOWN\n");
        gEthVirtmacApp.stats.ctrlModeIndDownCnt++;
    }
    else if (ETH_MODE_ACTIVE == ControllerMode)
    {
        EthVirtmac_printf("EthIf_CtrlModeIndication: ACTIVE\n");
        gEthVirtmacApp.stats.ctrlModeIndActCnt++;
    }
    else
    {
        EthVirtmac_printf("EthIf_CtrlModeIndication: invalid mode\n");
        gEthVirtmacApp.stats.ctrlModeIndErr++;
    }
}

void EthIf_TrcvModeIndication(uint8 CtrlIdx,
                              EthTrcv_ModeType TrcvMode)
{
    EthVirtmac_printf("EthIf_TrcvModeIndication: %s\n",
                  (ETHTRCV_MODE_ACTIVE == TrcvMode) ? "Active" : "Down");
}

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
                VAR(Dem_EventIdType, AUTOMATIC) EventId,
                VAR(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
    if ((DEM_EVENT_STATUS_FAILED | DEM_EVENT_STATUS_PREFAILED) == EventStatus)
    {
        EthVirtmac_printf("Dem_SetEventStatus: %d\n", (uint16)EventId);
        gEthVirtmacApp.stats.demErr++;
    }
    return (E_OK);
}

Std_ReturnType Det_ReportError(uint16 moduleId,
                               uint8 instanceId,
                               uint8 apiId,
                               uint8 errorId)
{
    EthVirtmac_printf("Det_ReportError: %s: %s\n",
                    EthVirtmacApp_apiIdToString(apiId),
                    EthVirtmacApp_errorIdToString(errorId));
    gEthVirtmacApp.stats.detErr++;

    return E_OK;
}

static BufReq_ReturnType EthVirtmacApp_provideTxBuffer(uint8 ctrlIdx,
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
        }
        else
        {
            retry = FALSE;
        }
    }
    while (retry == TRUE);

    return bufStatus;
}

static void EthVirtmacApp_send(uint8 ctrlIdx,
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

    bufStatus = EthVirtmacApp_provideTxBuffer(ctrlIdx,
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
            EthVirtmac_printf("send: failed to send buffer\n");
        }
    }
    else
    {
        EthVirtmac_printf("send: failed to get TX buffer: %d\n", (int)bufStatus);
    }

    if(gEthVirtmacApp.txIrqDisable)
    {
        Eth_TxConfirmation(ctrlIdx);
    }
}

static void EthVirtmacApp_sendCmd(uint8 ctrlIdx,
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

    bufStatus = EthVirtmacApp_provideTxBuffer(ctrlIdx,
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
            EthVirtmac_printf("sendCmd: failed to send STOP cmd\n");
        }
    }
    else
    {
        EthVirtmac_printf("sendCmd: failed to get TX buffer: %d\n", (int)bufStatus);
    }

    if(gEthVirtmacApp.txIrqDisable)
    {
        Eth_TxConfirmation(ctrlIdx);
    }
}

static boolean EthVirtmacApp_transmit(uint8 ctrlIdx,
                               uint32 num,
                               uint16 len,
                               boolean txConfirmation,
                               boolean vlan)
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
    gEthVirtmacApp.stats.txPktCnt     = 0U;
    gEthVirtmacApp.stats.txConfPktCnt = 0U;
    gEthVirtmacApp.stats.txBufLenErr  = 0U;
    gEthVirtmacApp.stats.txBufProvErr = 0U;
    gEthVirtmacApp.stats.txPktErr     = 0U;
    gEthVirtmacApp.stats.detErr       = 0U;
    gEthVirtmacApp.stats.demErr       = 0U;

    if (TRUE == Eth_GetTxIrqPacingEnable(gEthVirtmacApp.ctrlIdx))
    {
        /* Incase IRQ pacing enable need more time to wait */
        delayTime *= (2u * Eth_GetHwTimerIntervalMs(gEthVirtmacApp.ctrlIdx,
                Eth_GetTxHwTimerIdx(gEthVirtmacApp.ctrlIdx)));
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
        bufStatus = EthVirtmacApp_provideTxBuffer(ctrlIdx,
                                                  priority,
                                                  &bufIdx,
                                                  &bufPtr,
                                                  &grantedLen);
        if (BUFREQ_E_OVFL == bufStatus)
        {
            EthVirtmac_printf("transmit: failed to get exact size (req=%d got=%d)\n",
                              len, grantedLen);
            gEthVirtmacApp.stats.txBufLenErr++;
            status = FAIL;
        }
        else if (BUFREQ_E_NOT_OK == bufStatus)
        {
            EthVirtmac_printf("transmit: failed to get buffer\n");
            gEthVirtmacApp.stats.txBufProvErr++;
            status = FAIL;
        }
        else if (bufPtr == NULL_PTR)
        {
            EthVirtmac_printf("transmit: invalid buffer pointer\n");
            gEthVirtmacApp.stats.txBufProvErr++;
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
            EthVirtmac_printf("transmit: failed to fill test packet\n");
            status = FAIL;
            break;
        }

        /* Transmit the packet */
        retryCnt = txConfirmation ? 0U : ETHVIRTMACAPP_TRANSMIT_RETRY_COUNT;
        do
        {
            retVal = Eth_Transmit(ctrlIdx,
                                  bufIdx,
                                  frameType,
                                  txConfirmation,
                                  grantedLen,
                                  BcastAddr);
            if (E_OK == retVal)
            {
                break;
            }

            if (retryCnt > 0U)
            {
                EthVirtmacApp_delay(1U);
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
            EthVirtmac_printf("transmit: failed to transmit buffer with idx %d\n",
                            (sint32)bufIdx);
            gEthVirtmacApp.stats.txPktErr++;
        }
        else
        {
            gEthVirtmacApp.stats.txPktCnt++;
        }

        if(gEthVirtmacApp.txIrqDisable)
        {
            Eth_TxConfirmation(ctrlIdx);
        }
    }

    /* Send STOP cmd */
    EthVirtmacApp_sendCmd(ctrlIdx, CTRL_FRAME_CMD_STOP);

    /* Short wait to allow for TX confirmation to come */
    if (txConfirmation)
    {
        EthVirtmacApp_delay(delayTime);
    }

    /* Check error conditions */
    if ((txConfirmation && (gEthVirtmacApp.stats.txConfPktCnt != gEthVirtmacApp.stats.txPktCnt)) ||
        (gEthVirtmacApp.stats.txPktCnt < num) ||
        (gEthVirtmacApp.stats.txPktErr > 0U) ||
        (gEthVirtmacApp.stats.txBufProvErr > 0U) ||
        (gEthVirtmacApp.stats.txBufLenErr > 0U) ||
        (gEthVirtmacApp.stats.detErr > 0U) ||
        (gEthVirtmacApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthVirtmacApp.verbose))
    {
        EthVirtmac_printf("Transmit Test Results:\n");
        EthVirtmac_printf("  Status:                 %s\n", status?"Pass":"Fail");
        EthVirtmac_printf("  Requested:              %d\n", num);
        EthVirtmac_printf("  Confirmation requested: %s\n", txConfirmation?"Yes":"No");
        EthVirtmac_printf("  Transmitted:            %d\n", gEthVirtmacApp.stats.txPktCnt);
        EthVirtmac_printf("  Confirmed:              %d\n", gEthVirtmacApp.stats.txConfPktCnt);
        EthVirtmac_printf("  Buffer length errors:   %d\n", gEthVirtmacApp.stats.txBufLenErr);
        EthVirtmac_printf("  Buffer request errors:  %d\n", gEthVirtmacApp.stats.txBufProvErr);
        EthVirtmac_printf("  Transmission errors:    %d\n", gEthVirtmacApp.stats.txPktErr);
        EthVirtmac_printf("  DEM errors:             %d\n", gEthVirtmacApp.stats.demErr);
        EthVirtmac_printf("  DET errors:             %d\n", gEthVirtmacApp.stats.detErr);
        EthVirtmac_printf("\n");
    }

    return status;
}

static boolean EthVirtmacApp_receive(uint8 ctrlIdx,
                              uint32 num)
{
    boolean forever;
    boolean status = PASS;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 fifoIdx = 0U;
    Eth_RxStatusType rxStatus;

    /* Reset test counters */
    gEthVirtmacApp.stats.rxPktCnt       = 0U;
    gEthVirtmacApp.stats.rxExp1PktCnt   = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt   = 0U;
    gEthVirtmacApp.stats.rxVlanPktCnt   = 0U;
    gEthVirtmacApp.stats.rxPktErr       = 0U;
    gEthVirtmacApp.stats.rxPktIndCnt    = 0U;
    gEthVirtmacApp.stats.rxEtherTypeErr = 0U;
    gEthVirtmacApp.stats.rxPayloadErr   = 0U;
    gEthVirtmacApp.stats.rxCtrlIdxErr   = 0U;
    gEthVirtmacApp.stats.detErr         = 0U;
    gEthVirtmacApp.stats.demErr         = 0U;

    forever = (num == 0U) ? TRUE : FALSE;

    gEthVirtmacApp.runTest = TRUE;

    /* Wait for Rx frames */
    while (gEthVirtmacApp.runTest)
    {
        if(gEthVirtmacApp.rxIrqDisable)
        {
            Eth_Receive(ctrlIdx, fifoIdx, &rxStatus);
        }

        if (!forever && (gEthVirtmacApp.stats.rxPktIndCnt >= num))
        {
            break;
        }
    }

    if ((gEthVirtmacApp.stats.rxPktIndCnt != (gEthVirtmacApp.stats.rxPktCnt + gEthVirtmacApp.stats.rxEtherTypeErr)) ||
        (gEthVirtmacApp.stats.rxPktErr > 0U) ||
        (gEthVirtmacApp.stats.rxPayloadErr > 0U) ||
        (gEthVirtmacApp.stats.rxCtrlIdxErr > 0U) ||
        (gEthVirtmacApp.stats.detErr > 0U) ||
        (gEthVirtmacApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthVirtmacApp.verbose))
    {
        EthVirtmac_printf("Receive Test Results:\n");
        EthVirtmac_printf("  Status:                %s\n", status?"Pass":"Fail");
        EthVirtmac_printf("  Requested:             %d\n", num);
        EthVirtmac_printf("  Received:              %d\n", gEthVirtmacApp.stats.rxPktCnt);
        EthVirtmac_printf("  Indicated:             %d\n", gEthVirtmacApp.stats.rxPktIndCnt);
        EthVirtmac_printf("  Experimental 1:        %d\n", gEthVirtmacApp.stats.rxExp1PktCnt);
        EthVirtmac_printf("  Experimental 2:        %d\n", gEthVirtmacApp.stats.rxExp2PktCnt);
        EthVirtmac_printf("  VLAN tagged:           %d\n", gEthVirtmacApp.stats.rxVlanPktCnt);
        EthVirtmac_printf("  Receive errors:        %d\n", gEthVirtmacApp.stats.rxPktErr);
        EthVirtmac_printf("  EtherType errors:      %d\n", gEthVirtmacApp.stats.rxEtherTypeErr);
        EthVirtmac_printf("  Payload errors:        %d\n", gEthVirtmacApp.stats.rxPayloadErr);
        EthVirtmac_printf("  Controller idx errors: %d\n", gEthVirtmacApp.stats.rxCtrlIdxErr);
        EthVirtmac_printf("  DEM errors:            %d\n", gEthVirtmacApp.stats.demErr);
        EthVirtmac_printf("  DET errors:            %d\n", gEthVirtmacApp.stats.detErr);
        EthVirtmac_printf("\n");
    }

    return status;
}

static const char *EthVirtmacApp_errorIdToString(uint8 errorId)
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

static const char *EthVirtmacApp_apiIdToString(uint8 apiId)
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

void EthVirtmacApp_wbCache(uint8 *buf, uint16 len)
{
    CacheP_wb(buf, len);
}

void EthVirtmacApp_wbInvCache(uint8 *buf, uint16 len)
{
    CacheP_wbInv(buf, len);
}

void EthVirtmacApp_invCache(uint8 *buf, uint16 len)
{
    CacheP_Inv(buf, len);
}

boolean EthVirtmacApp_test_0001(void)
{
    uint32 num = 0U;
    boolean status;

    EthVirtmac_printf("test_0001: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthVirtmac_printf("test_0001: failed while receiving frames\n");
    }

    EthVirtmac_printf("test_0001: received %d of %d frames\n",
                    gEthVirtmacApp.stats.rxExp1PktCnt, ETH_TEST_ITER_M_COUNT);

    if (gEthVirtmacApp.stats.rxExp1PktCnt != ETH_TEST_ITER_M_COUNT)
    {
        printf("test_0001: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, gEthVirtmacApp.stats.rxExp1PktCnt);
        status = FAIL;
    }

    EthVirtmac_printf("test_0001: END\n");

    return status;
}

boolean EthVirtmacApp_test_0002(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean status;

    EthVirtmac_printf("test_0002: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames */
    status = EthVirtmacApp_transmit(gEthVirtmacApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan);

    EthVirtmac_printf("test_0002: END\n");

    return status;
}

boolean EthVirtmacApp_test_0003(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    sint32 i;
    sint32 fillStatus;
    uint16 len = 1500U;
    boolean status = TRUE;
    EthFrame frame;
    Eth_RxStatusType rxStatus;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 fifoIdx = 0U;

    EthVirtmac_printf("test_0003: START\n");

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    Eth_GetPhysAddr(gEthVirtmacApp.ctrlIdx, gEthVirtmacApp.macAddr);

    memcpy(frame.hdr.srcMac, gEthVirtmacApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Send and receive frames */
    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthVirtmacApp.verbose)
        {
            EthVirtmac_printf("test_0003: iteration %d\n", i);
        }

        gEthVirtmacApp.saveRxFrame = TRUE;
        gEthVirtmacApp.stats.rxPktCnt = 0U;
        gEthVirtmacApp.stats.rxPktIndCnt = 0U;

        fillStatus = EthUtils_fillPayload((DataFramePayload *)frame.payload,
                                          i % ETH_TEST_NUM_TYPES,
                                          len);
        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthVirtmac_printf("test_0003: failed to fill test packet\n");
            status = FAIL;
            break;
        }

        /* Send the frame */
        EthVirtmacApp_send(gEthVirtmacApp.ctrlIdx, &frame, len);

        /* Wait for Rx frames */
        while (0 == gEthVirtmacApp.stats.rxPktIndCnt)
        {
            if(gEthVirtmacApp.rxIrqDisable == TRUE)
            {
                Eth_Receive(gEthVirtmacApp.ctrlIdx, fifoIdx, &rxStatus);
                if (ETH_NOT_RECEIVED == rxStatus)
                {
                    EthVirtmac_printf("test_0003: failed to receive packet\n");
                    status = FAIL;
                    break;
                }
            }
        }
        /* End the test if STOP cmd is detected */
        if (TRUE == EthFrame_isStopCmd(&gEthVirtmacApp.rxFrame))
        {
            break;
        }

        /* Check if EtherType field matches */
        if (frame.hdr.etherType == gEthVirtmacApp.rxFrame.hdr.etherType)
        {
            /* Check if payload matches */
            if (0 != memcmp(&frame.payload, gEthVirtmacApp.rxFrame.payload, len))
            {
                EthVirtmac_printf("test_0003: payload mismatch\n");
                status = FAIL;
                break;
            }
        }
    }

    /* Send STOP cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthVirtmac_printf("test_0003: END\n");

    return status;
}

boolean EthVirtmacApp_test_0004(void)
{
    uint32 num = 0U;
    boolean status;

    EthVirtmac_printf("test_0004: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthVirtmac_printf("test_0004: failed while receiving frames\n");
    }

    EthVirtmac_printf("test_0004: received %d of %d frames\n",
                    gEthVirtmacApp.stats.rxExp1PktCnt, ETH_TEST_ITER_M_COUNT / 2);

    if (gEthVirtmacApp.stats.rxExp1PktCnt != ETH_TEST_ITER_M_COUNT / 2)
    {
        status = FAIL;
    }

    EthVirtmac_printf("test_0004: END\n");

    return status;
}

boolean EthVirtmacApp_test_0005(void)
{
    uint32 num = ETH_TEST_ITER_M_COUNT;
    uint32 acceptCnt = num / 2;
    boolean itStatus;
    boolean status = PASS;

    EthVirtmac_printf("test_0005: START\n");

    /* Part 1: Receive frames with controller's address, broadcast address */
    gEthVirtmacApp.stats.rxExp1PktCnt = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt = 0U;
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthVirtmacApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthVirtmacApp.stats.rxExp2PktCnt != 0U))
    {
        gEthVirtmacApp.stats.filterNullRxErr++;
    }

    EthVirtmac_printf("test_0005:  Null: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp1PktCnt);
    EthVirtmac_printf("test_0005:  Null: Exp2: exp %3d, got %3d\n",
                    0U, gEthVirtmacApp.stats.rxExp2PktCnt);

    /* Part 2: Add unicast address and receive frames with that address */
    EthVirtmacApp_addSubHostUcastAddr(UcastAddr);

    gEthVirtmacApp.stats.rxExp1PktCnt = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt = 0U;
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthVirtmacApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthVirtmacApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthVirtmacApp.stats.filterUcastRxErr++;
    }

    EthVirtmac_printf("test_0005: Ucast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp1PktCnt);
    EthVirtmac_printf("test_0005: Ucast: Exp2: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp2PktCnt);

    /* Part 3: Add multicast address and receive frames with that address */
    EthVirtmacApp_addSubMcastAddr(McastAddr);

    gEthVirtmacApp.stats.rxExp1PktCnt = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt = 0U;
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthVirtmacApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthVirtmacApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthVirtmacApp.stats.filterMcastRxErr++;
    }

    EthVirtmac_printf("test_0005: Mcast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp1PktCnt);
    EthVirtmac_printf("test_0005: Mcast: Exp2: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp2PktCnt);

    /* Part 4: Remove multicast address and receive frames with that address */
    EthVirtmacApp_delUnsubAddr(McastAddr);

    gEthVirtmacApp.stats.rxExp1PktCnt = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt = 0U;
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthVirtmacApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthVirtmacApp.stats.rxExp2PktCnt != 0U))
    {
        gEthVirtmacApp.stats.filterMcastRxErr++;
    }

    EthVirtmac_printf("test_0005: Mcast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp1PktCnt);
    EthVirtmac_printf("test_0005: Mcast: Exp2: exp %3d, got %3d\n",
                    0U, gEthVirtmacApp.stats.rxExp2PktCnt);

    /* Part 5: Add broadcast address and receive/send frames with any address */
    EthVirtmacApp_addSubHostUcastAddr(UcastOpenFilterAddr);

    gEthVirtmacApp.stats.rxExp1PktCnt = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt = 0U;
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthVirtmacApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthVirtmacApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthVirtmacApp.stats.filterBcastRxErr++;
    }

    EthVirtmac_printf("test_0005: Bcast: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp1PktCnt);
    EthVirtmac_printf("test_0005: Bcast: Exp2: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp2PktCnt);

    /* Part 6: Reset filter and receive frames with controller's address */
    EthVirtmacApp_delUnsubAddr(UcastAddr);
    EthVirtmacApp_delUnsubAddr(UcastOpenFilterAddr);

    gEthVirtmacApp.stats.rxExp1PktCnt = 0U;
    gEthVirtmacApp.stats.rxExp2PktCnt = 0U;
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) ||
        (gEthVirtmacApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthVirtmacApp.stats.rxExp2PktCnt != 0U))
    {
        gEthVirtmacApp.stats.filterNullRxErr++;
    }

    EthVirtmac_printf("test_0005:  Null: Exp1: exp %3d, got %3d\n",
                    acceptCnt, gEthVirtmacApp.stats.rxExp1PktCnt);
    EthVirtmac_printf("test_0005:  Null: Exp2: exp %3d, got %3d\n",
                    0U, gEthVirtmacApp.stats.rxExp2PktCnt);

    /* Check error conditions */
    if ((gEthVirtmacApp.stats.filterUcastAddErr > 0U) ||
        (gEthVirtmacApp.stats.filterUcastRemErr > 0U) ||
        (gEthVirtmacApp.stats.filterUcastRxErr > 0U) ||
        (gEthVirtmacApp.stats.filterMcastAddErr > 0U) ||
        (gEthVirtmacApp.stats.filterMcastRemErr > 0U) ||
        (gEthVirtmacApp.stats.filterMcastRxErr > 0U) ||
        (gEthVirtmacApp.stats.filterBcastErr > 0U) ||
        (gEthVirtmacApp.stats.filterBcastRxErr > 0U) ||
        (gEthVirtmacApp.stats.filterNullErr > 0U) ||
        (gEthVirtmacApp.stats.filterNullRxErr > 0U) ||
        (gEthVirtmacApp.stats.detErr > 0U) ||
        (gEthVirtmacApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthVirtmacApp.verbose))
    {
        EthVirtmac_printf("Filter Test Results:\n");
        EthVirtmac_printf("  Status:                %s\n", status?"Pass":"Fail");
        EthVirtmac_printf("  Sent from host:        %d\n", num);
        EthVirtmac_printf("  Unicast ADD errors:    %d\n", gEthVirtmacApp.stats.filterUcastAddErr);
        EthVirtmac_printf("  Ucast REMOVE errors:   %d\n", gEthVirtmacApp.stats.filterUcastRemErr);
        EthVirtmac_printf("  Ucast receive errors:  %d\n", gEthVirtmacApp.stats.filterUcastRxErr);
        EthVirtmac_printf("  Mcast ADD errors:      %d\n", gEthVirtmacApp.stats.filterMcastAddErr);
        EthVirtmac_printf("  Mcast REMOVE errors:   %d\n", gEthVirtmacApp.stats.filterMcastRemErr);
        EthVirtmac_printf("  Mcast receive errors:  %d\n", gEthVirtmacApp.stats.filterMcastRxErr);
        EthVirtmac_printf("  Bcast ADD errors:      %d\n", gEthVirtmacApp.stats.filterBcastErr);
        EthVirtmac_printf("  Bcast receive errors:  %d\n", gEthVirtmacApp.stats.filterBcastRxErr);
        EthVirtmac_printf("  Null ADD errors:       %d\n", gEthVirtmacApp.stats.filterNullErr);
        EthVirtmac_printf("  Null receive errors:   %d\n", gEthVirtmacApp.stats.filterNullRxErr);
        EthVirtmac_printf("  DEM errors:            %d\n", gEthVirtmacApp.stats.demErr);
        EthVirtmac_printf("  DET errors:            %d\n", gEthVirtmacApp.stats.detErr);
        EthVirtmac_printf("\n");
    }

    EthVirtmac_printf("test_0005: END\n");

    return status;
}

boolean EthVirtmacApp_test_0006(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean status;

    EthVirtmac_printf("test_0006: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames with txConfirmation enabled */
    status = EthVirtmacApp_transmit(gEthVirtmacApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan);

    EthVirtmac_printf("test_0006: END\n");

    return status;
}

boolean EthVirtmacApp_test_0007(void)
{
    uint32 iterations = ETH_TEST_ITER_M_COUNT;
    uint16 len = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan = TRUE;
    boolean status;

    EthVirtmac_printf("test_0007: START\n");

    EthVirtmacApp_addVlanId(ETH_TEST_VLAN_VID);
    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit VLAN tagged frames with txConfirmation enabled */
    status = EthVirtmacApp_transmit(gEthVirtmacApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan);

    EthVirtmacApp_delVlanId(ETH_TEST_VLAN_VID);
    EthVirtmac_printf("test_0007: END\n");

    return status;
}

boolean EthVirtmacApp_test_0008(void)
{
    uint32 iterations = ETH_TEST_ITER_S_COUNT;
    uint16 len;
    boolean txConfirmation = TRUE;
    boolean vlan = FALSE;
    boolean st;
    boolean status = PASS;

    EthVirtmac_printf("test_0008: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames of different lengths */
    for (len = 10U; len <= 1500U; len += 10U)
    {
        st = EthVirtmacApp_transmit(gEthVirtmacApp.ctrlIdx,
                             iterations,
                             len,
                             txConfirmation,
                             vlan);
        if (st == FAIL)
        {
            EthVirtmac_printf("test_0008: failed to transmit frames of length %u\n",
                            len);
            status = FAIL;
        }
    }

    EthVirtmac_printf("test_0008: END\n");

    return status;
}

boolean EthVirtmacApp_test_0009(void)
{
    uint32 num = 0U;
    boolean status;

    EthVirtmac_printf("test_0009: START\n");

    EthVirtmacApp_addVlanId(ETH_TEST_VLAN_VID);
    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthVirtmacApp_receive(gEthVirtmacApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthVirtmac_printf("test_0009: failed while receiving frames\n");
    }

    EthVirtmac_printf("test_0009: received %d of %d frames\n",
                    gEthVirtmacApp.stats.rxVlanPktCnt, ETH_TEST_ITER_M_COUNT);

    if (gEthVirtmacApp.stats.rxVlanPktCnt != ETH_TEST_ITER_M_COUNT)
    {
        printf("test_0009: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, gEthVirtmacApp.stats.rxVlanPktCnt);
        status = FAIL;
    }

    EthVirtmacApp_delVlanId(ETH_TEST_VLAN_VID);
    EthVirtmac_printf("test_0009: END\n");

    return status;
}

boolean EthVirtmacApp_test_0010(void)
{
    uint32 iterations = ETH_TEST_ITER_S_COUNT;
    uint32 i;
    boolean status = PASS;
    Std_ReturnType retVal = E_OK;

    EthVirtmac_printf("test_0010: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthVirtmacApp.verbose)
        {
            EthVirtmac_printf("test_0010: iteration %d\n", i+1);
        }

        if (E_OK == retVal)
        {
            uint8 macAddress[ETH_MAC_ADDR_LEN];

            Eth_GetPhysAddr(gEthVirtmacApp.ctrlIdx, macAddress);
            EthVirtmacApp_delUnsubAddr(macAddress);
        }

        /* Set controller to down state */
        retVal = Eth_SetControllerMode(gEthVirtmacApp.ctrlIdx, ETH_MODE_DOWN);
        if (E_OK != retVal)
        {
            EthVirtmac_printf("test_0010: failed to set down mode\n");
            gEthVirtmacApp.stats.ctrlModeErr++;
        }
        else
        {
            gEthVirtmacApp.stats.ctrlModeActCnt++;
        }

        Eth_MainFunction();

        /* Set controller back to active state */
        retVal = Eth_SetControllerMode(gEthVirtmacApp.ctrlIdx, ETH_MODE_ACTIVE);
        if (E_OK != retVal)
        {
            EthVirtmac_printf("test_0010: failed to set active mode\n");
            gEthVirtmacApp.stats.ctrlModeErr++;
        }
        else
        {
            gEthVirtmacApp.stats.ctrlModeDownCnt++;
        }

        Eth_MainFunction();

        /* Check error conditions */
        if ((gEthVirtmacApp.stats.ctrlModeDownCnt == 0U) ||
            (gEthVirtmacApp.stats.ctrlModeActCnt == 0U) ||
            (gEthVirtmacApp.stats.ctrlModeErr > 0U) ||
            (gEthVirtmacApp.stats.ctrlModeIndDownCnt != gEthVirtmacApp.stats.ctrlModeDownCnt) ||
            (gEthVirtmacApp.stats.ctrlModeIndActCnt != gEthVirtmacApp.stats.ctrlModeActCnt) ||
            (gEthVirtmacApp.stats.ctrlModeIndErr > 0U) ||
            (gEthVirtmacApp.stats.detErr > 0U) ||
            (gEthVirtmacApp.stats.demErr > 0U))
        {
            status = FAIL;
        }

        if ((FAIL == status) || (TRUE == gEthVirtmacApp.verbose))
        {
            EthVirtmac_printf("Controller Mode Test Results:\n");
            EthVirtmac_printf("  Status:                   %s\n", status?"Pass":"Fail");
            EthVirtmac_printf("  Requested:                %d\n", iterations);
            EthVirtmac_printf("  Changes to DOWN mode:     %d\n", gEthVirtmacApp.stats.ctrlModeDownCnt);
            EthVirtmac_printf("  Changes to ACTIVE mode:   %d\n", gEthVirtmacApp.stats.ctrlModeActCnt);
            EthVirtmac_printf("  Mode change errors:       %d\n", gEthVirtmacApp.stats.ctrlModeErr);
            EthVirtmac_printf("  Indicated DOWN changes:   %d\n", gEthVirtmacApp.stats.ctrlModeIndDownCnt);
            EthVirtmac_printf("  Indicated ACTIVE changes: %d\n", gEthVirtmacApp.stats.ctrlModeIndActCnt);
            EthVirtmac_printf("  Indication errors:        %d\n", gEthVirtmacApp.stats.ctrlModeIndErr);
            EthVirtmac_printf("\n");
        }

        if (FAIL == status)
        {
            EthVirtmac_printf("test_0010: failed to change controller mode\n");
        }

        if (E_OK == retVal)
        {
            uint8 macAddress[ETH_MAC_ADDR_LEN];

            Eth_GetPhysAddr(gEthVirtmacApp.ctrlIdx, macAddress);
            EthVirtmacApp_subscribeDefaultAddr(macAddress);
        }

        /* Transmit frames */
        status = EthVirtmacApp_test_0002();
        if (FAIL == status)
        {
            EthVirtmac_printf("test_0010: failed to transmit frames\n");
        }

        /* Receive frames */
        status = EthVirtmacApp_test_0001();
        if (FAIL == status)
        {
            EthVirtmac_printf("test_0010: failed to receive frames\n");
        }
    }

    EthVirtmac_printf("test_0010: completed %d of %d iterations\n", i, iterations);
    EthVirtmac_printf("test_0010: END\n");

    return status;
}

boolean EthVirtmacApp_test_0100(void)
{
    Eth_BufIdxType bufIdx;
    BufReq_ReturnType bufStatus;
    boolean txConfirmation = FALSE;
    uint8 *bufPtr;
    uint32 iterations = ETH_TEST_ITER_L_COUNT;
    uint32 retryCnt;
    uint32 i;
    uint16 len = 1500U;
    Std_ReturnType retVal;
    /* QoS is not supported in current MCAL Eth, so set to 0 */
    uint8 priority = 0U;

    EthVirtmac_printf("test_0100: START\n");

    /* Send START cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Send frames */
    for (i = 0U; i < iterations; i++)
    {
        /* Request one buffer */
        bufStatus = EthVirtmacApp_provideTxBuffer(gEthVirtmacApp.ctrlIdx,
                                                  priority,
                                                  &bufIdx,
                                                  &bufPtr,
                                                  &len);

        /* Transmit it as is (only header is updated) */
        if (BUFREQ_OK == bufStatus)
        {
            retryCnt = txConfirmation ? 0U : ETHVIRTMACAPP_TRANSMIT_RETRY_COUNT;

            do
            {
                retVal = Eth_Transmit(gEthVirtmacApp.ctrlIdx,
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
                    EthVirtmacApp_delay(1U);
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
                EthVirtmac_printf("test_0100: failed to send buffer\n");
            }
        }
        else
        {
            EthVirtmac_printf("test_0100: failed to get TX buffer: %d\n",
                            (int)bufStatus);
        }
    }

    /* Send STOP cmd */
    EthVirtmacApp_sendCmd(gEthVirtmacApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthVirtmac_printf("test_0100: %d frames sent\n", i);
    EthVirtmac_printf("test_0100: END\n");

    return PASS;
}

boolean EthVirtmacApp_test_0200(void)
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

    EthVirtmac_printf("test_0200: START\n");

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    Eth_GetPhysAddr(gEthVirtmacApp.ctrlIdx, gEthVirtmacApp.macAddr);
    memcpy(frame.hdr.srcMac, gEthVirtmacApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send and receive frames */
    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthVirtmacApp.verbose)
        {
            EthVirtmac_printf("test_0200: iteration %d\n", i);
        }

        gEthVirtmacApp.saveRxFrame = TRUE;
        gEthVirtmacApp.stats.rxPktCnt = 0U;
        gEthVirtmacApp.stats.rxPktIndCnt = 0U;

        fillStatus = EthUtils_fillPayload((DataFramePayload *)frame.payload,
                                          i % ETH_TEST_NUM_TYPES,
                                          len);
        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthVirtmac_printf("test_0200: failed to fill test packet\n");
            status = FAIL;
            break;
        }

        /* Send the frame */
        EthVirtmacApp_send(gEthVirtmacApp.ctrlIdx, &frame, len);

        /* Wait for Rx frames */
        while (0 == gEthVirtmacApp.stats.rxPktIndCnt)
        {
            if(gEthVirtmacApp.rxIrqDisable)
            {
                Eth_Receive(gEthVirtmacApp.ctrlIdx, fifoIdx, &rxStatus);
                if (ETH_NOT_RECEIVED == rxStatus)
                {
                    EthVirtmac_printf("test_0200: failed to receive packet\n");
                    status = FAIL;
                    break;
                }
            }
        }

        /* Check if EtherType field matches */
        if (frame.hdr.etherType != gEthVirtmacApp.rxFrame.hdr.etherType)
        {
            EthVirtmac_printf("test_0200: EtherType mismatch (exp=0x%04x, got=0x%04x)\n",
                            frame.hdr.etherType & 0xFFFFU,
                            gEthVirtmacApp.rxFrame.hdr.etherType & 0xFFFFU);
            status = FAIL;
            break;
        }

        /* Check if payload matches */
        if (0 != memcmp(&frame.payload, gEthVirtmacApp.rxFrame.payload, len))
        {
            EthVirtmac_printf("test_0200: payload mismatch\n");
            status = FAIL;
            break;
        }
    }

    EthVirtmac_printf("test_0200: completed %d of %d iterations\n", i, iterations);
    EthVirtmac_printf("test_0200: END\n");

    return status;
}

static void EthVirtmacApp_registerMacAddr(uint8 *macAddress)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_SUBSCRIBE_DSTMAC;
    status = Eth_DispatchVirtmacSubscribeDstMac(gEthVirtmacApp.ctrlIdx, macAddress);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_unregisterMacAddr(uint8 *macAddress)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_UNSUBSCRIBE_DSTMAC;
    status = Eth_DispatchVirtmacUnsubscribeDstMac(gEthVirtmacApp.ctrlIdx, macAddress);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_addSubHostUcastAddr(uint8 *macAddress)
{
    /* Add host port unicast address */
    EthVirtmacApp_addUnicastAddr(macAddress, ETH_PORT_HOST_PORT);

    /* Register host port unicast address to rx flow */
    EthVirtmacApp_registerMacAddr(macAddress);
}

static void EthVirtmacApp_delUnsubAddr(uint8 *macAddress)
{
    /* Register host port unicast address to rx flow */
    EthVirtmacApp_unregisterMacAddr(macAddress);

   /* No need to delete address from ARL as EthVirtmacApp_unregisterMacAddr
    * does it implicitly
    */
}


static void EthVirtmacApp_subscribeDefaultAddr(uint8 *macAddress)
{
    /* Add given ucast address to switch ARL table and register to Driver Rx flow */
    EthVirtmacApp_addSubHostUcastAddr(macAddress);

    /* Add spl mcast address to switch ARL table and register to Driver Rx flow */
    EthVirtmacApp_addSubMcastAddr(TargetMcastAddr);

    /* Add broadcast address to switch ARL table .
     * Host port should not be member of bcast to avoid stray network packets
     * being routed to host port and breaking the hostApp <-> targetApp sync
     */
    EthVirtmacApp_addMcastAddr(BcastAddr, FALSE);
}

void EthVirtmacApp_rpcCmdComplete (uint8 controllerIdx,
                                          uint8 sid,
                                          Std_ReturnType status)
{
    if ((status == E_OK) && (gEthVirtmacApp.expectedSid == sid))
    {
        SemaphoreP_post(gEthVirtmacApp.ethNotifySem);
    }
}

void EthVirtmacApp_rpcFwRegistered (uint8 controllerIdx)
{
    SemaphoreP_post(gEthVirtmacApp.ethNotifySem);
}

static void EthVirtmacApp_recvMsgNotify(void)
{
    Eth_NotifyVirtmacMsgReceived(gEthVirtmacApp.ctrlIdx);

}

static void EthVirtmacApp_getEthConfig(Eth_ConfigType *ethConfig)
{
    SemaphoreP_Params semaphoreParams;

    SemaphoreP_Params_init(&semaphoreParams);
    semaphoreParams.mode = SemaphoreP_Mode_BINARY;
    gEthVirtmacApp.ethNotifySem = SemaphoreP_create(0, &semaphoreParams);
    EthVirtmacAppUtils_assert (NULL != gEthVirtmacApp.ethNotifySem);
#if 0
#if defined (SOC_J721E)
    EthVirtmacAppUtils_assert(ethConfig->enetType == ETH_ENETTYPE_CPSW9G);
#elif defined (SOC_J7200)
    EthVirtmacAppUtils_assert(ethConfig->enetType == ETH_ENETTYPE_CPSW5G);
#endif
    EthVirtmacAppUtils_assert(ethConfig->enableVirtualMac == TRUE);
    EthVirtmacAppUtils_assert(ethConfig->virtualMacCfg.ethfwRpcComChId == ETHVIRTMACAPP_REMOTEETHDEVICE_COMCHID);
    EthVirtmacAppUtils_assert(ethConfig->virtualMacCfg.pollRecvMsgInEthMain == FALSE);
    EthVirtmacAppUtils_assert(ethConfig->virtualMacCfg.rpcCmdComplete == &EthVirtmacApp_rpcCmdComplete);
    EthVirtmacAppUtils_assert(ethConfig->virtualMacCfg.fwRegisteredCb == &EthVirtmacApp_rpcFwRegistered);
#endif
}

static void EthVirtmacApp_virtmacInit(Eth_ConfigType *ethConfig)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_INIT;
    status = Eth_DispatchVirtmacInit(gEthVirtmacApp.ctrlIdx);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}


void EthVirtmacApp_freeEthResources(void)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_DEINIT;
    status = Eth_DispatchVirtmacDeinit(gEthVirtmacApp.ctrlIdx);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_addUnicastAddr(uint8 *macAddr, Eth_PortType port)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_ADD_UNICAST_MACADDR;
    status = Eth_DispatchVirtmacAddUnicastAddr(gEthVirtmacApp.ctrlIdx, macAddr, port, 0);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

void EthVirtmacApp_delAddr(uint8 *macAddr)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_DEL_MACADDR;
    status = Eth_DispatchVirtmacDelAddr(gEthVirtmacApp.ctrlIdx, macAddr, 0);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_addMcastAddr(uint8 *macAddr, boolean addHostPort)
{
    Std_ReturnType status;
    Eth_PortListType portList;

    portList.numPorts = 0;
#if defined (SOC_J721E)
    portList.numPorts += 6;
    portList.ports[0] = ETH_PORT_MAC_PORT_2;
    portList.ports[1] = ETH_PORT_MAC_PORT_3;
    portList.ports[2] = ETH_PORT_MAC_PORT_5;
    portList.ports[3] = ETH_PORT_MAC_PORT_6;
    portList.ports[4] = ETH_PORT_MAC_PORT_7;
    portList.ports[5] = ETH_PORT_MAC_PORT_8;
#elif defined (SOC_J784S4)
    portList.numPorts += 2;
    portList.ports[0] = ETH_PORT_MAC_PORT_3;
    portList.ports[1] = ETH_PORT_MAC_PORT_5;
#else
    portList.numPorts += 2;
    portList.ports[0] = ETH_PORT_MAC_PORT_2;
    portList.ports[1] = ETH_PORT_MAC_PORT_3;
#endif

    if (addHostPort)
    {
        portList.ports[portList.numPorts] = ETH_PORT_HOST_PORT;
        portList.numPorts++;
    }
    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_ADD_MCAST_MACADDR;
    status = Eth_DispatchVirtmacAddMcastAddr(gEthVirtmacApp.ctrlIdx, macAddr, 0, 0, &portList);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_addVlanId(uint32 vlanId)
{
    Std_ReturnType status;
    Eth_PortListType portList;

    portList.numPorts = 1;
    portList.ports[0] = ETH_PORT_HOST_PORT;
#if defined (SOC_J721E)
    portList.numPorts += 6;
    portList.ports[1] = ETH_PORT_MAC_PORT_2;
    portList.ports[2] = ETH_PORT_MAC_PORT_3;
    portList.ports[3] = ETH_PORT_MAC_PORT_5;
    portList.ports[4] = ETH_PORT_MAC_PORT_6;
    portList.ports[5] = ETH_PORT_MAC_PORT_7;
    portList.ports[6] = ETH_PORT_MAC_PORT_8;
#elif defined (SOC_J784S4)
    portList.numPorts += 2;
    portList.ports[1] = ETH_PORT_MAC_PORT_3;
    portList.ports[2] = ETH_PORT_MAC_PORT_5;
#else
    portList.numPorts += 2;
    portList.ports[1] = ETH_PORT_MAC_PORT_2;
    portList.ports[2] = ETH_PORT_MAC_PORT_3;
#endif

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_ADD_VLAN;
    status = Eth_DispatchVirtmacAddVlan(gEthVirtmacApp.ctrlIdx, vlanId, &portList);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_delVlanId(uint32 vlanId)
{
    Std_ReturnType status;

    gEthVirtmacApp.expectedSid = ETH_SID_DISPATCH_VIRTMAC_DEL_VLAN;
    status = Eth_DispatchVirtmacDelVlan(gEthVirtmacApp.ctrlIdx, vlanId);
    EthVirtmacAppUtils_assert(status == E_OK);
    SemaphoreP_pend(gEthVirtmacApp.ethNotifySem, SemaphoreP_WAIT_FOREVER);
}

static void EthVirtmacApp_addSubMcastAddr(uint8 *macAddr)
{
    EthVirtmacApp_addMcastAddr(macAddr, TRUE);
    EthVirtmacApp_registerMacAddr(macAddr);

}

/** \brief prints of the version of this implementation */
static void EthVirtmacApp_ipcPrintVersion(void)
{
    Std_VersionInfoType versioninfo;

    Cdd_IpcGetVersionInfo(&versioninfo);
    EthVirtmac_printf( " \n");
    EthVirtmac_printf(" CDD IPC MCAL Version Info\n");
    EthVirtmac_printf("---------------------\n");
    EthVirtmac_printf(" Vendor ID           : %d\n",
                                                versioninfo.vendorID);
    EthVirtmac_printf(" Module ID           : %d\n",
                                                versioninfo.moduleID);
    EthVirtmac_printf(" SW Major Version    : %d\n",
                                                versioninfo.sw_major_version);
    EthVirtmac_printf(" SW Minor Version    : %d\n",
                                                versioninfo.sw_minor_version);
    EthVirtmac_printf(" SW Patch Version    : %d\n",
                                                versioninfo.sw_patch_version);
    EthVirtmac_printf( " \n");

}

/** \brief Interrupt from mailbox for all cores registrations */
static void EthVirtmacApp_ipcInterruptConfig(void)
{
    EthVirtmacApp_ipcMbIntRegForMcu20 ();

    return;
}

static void EthVirtmacApp_ipcMsgFromMcu20Isr(uintptr_t notUsed)
{
    /* Invoke MCU 20 Isr handler */
    Cdd_IpcIrqMbxFromMcu_20();
}

static uint32 EthVirtmacApp_ipcMailboxClear(uint32 baseAddr, uint32 queueId)
{
    uint32 retVal = 0;
    uint32 msg[4];

    retVal = MailboxGetMessage(baseAddr, queueId, msg);

    return retVal;
}


static sint32 EthVirtmacApp_sciclientIrqRelease(uint16 coreId, uint32 clusterId,
        uint32 userId, uint32 intNumber)
{
    sint32                               retVal = IPC_SOK;
    struct tisci_msg_rm_irq_release_req   rmIrqRel;

    rmIrqRel.ia_id                  = 0U;
    rmIrqRel.vint                   = 0U;
    rmIrqRel.global_event           = 0U;
    rmIrqRel.vint_status_bit_index  = 0U;

    rmIrqRel.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID |
                              TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                              TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
    rmIrqRel.src_id         = ipc_map_src_id[clusterId];
    rmIrqRel.src_index      = (uint16)userId;
    rmIrqRel.dst_id         = (uint16)ipc_map_dst_id[coreId];
#if defined(BUILD_C7X_1)
    rmIrqRel.dst_host_irq   = (uint16)(intNumber +  IPC_C7X_COMPUTE_CLUSTER_OFFSET);
#else
    rmIrqRel.dst_host_irq   = (uint16)intNumber;
#endif
    rmIrqRel.secondary_host = (uint8)ipc_map_host_id[coreId];

    retVal = Sciclient_rmIrqRelease(&rmIrqRel, IPC_SCICLIENT_TIMEOUT);

    return retVal;
}

static sint32 EthVirtmacApp_sciclientIrqSet(uint16 coreId, uint32 clusterId,
        uint32 userId, uint32 intNumber)
{
    sint32                           retVal = IPC_SOK;
    struct tisci_msg_rm_irq_set_req   rmIrqReq;
    struct tisci_msg_rm_irq_set_resp  rmIrqResp;

    rmIrqReq.ia_id                  = 0U;
    rmIrqReq.vint                   = 0U;
    rmIrqReq.global_event           = 0U;
    rmIrqReq.vint_status_bit_index  = 0U;

    rmIrqReq.valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID |
                              TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                              TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID;
    rmIrqReq.src_id         = ipc_map_src_id[clusterId];
    rmIrqReq.src_index      = (uint16)userId;
    rmIrqReq.dst_id         = (uint16)ipc_map_dst_id[coreId];
#if defined(BUILD_C7X_1)
    rmIrqReq.dst_host_irq   = (uint16)(intNumber +  IPC_C7X_COMPUTE_CLUSTER_OFFSET);
#else
    rmIrqReq.dst_host_irq   = (uint16)intNumber;
#endif
    rmIrqReq.secondary_host = (uint8)ipc_map_host_id[coreId];

    /* Config event */
    retVal = Sciclient_rmIrqSet(&rmIrqReq, &rmIrqResp, IPC_SCICLIENT_TIMEOUT);

    return retVal;
}

static void EthVirtmacApp_ipcMbIntRegForMcu20(void)
{
    OsalRegisterIntrParams_t    intrPrms;
    OsalInterruptRetCode_e      osalRetVal;
    Int32 retVal;
    HwiP_Handle hwiHandle;
    uint32 selfId, remoteProcId;
    uint32 clusterId;
    uint32 userId;
    uint32 queueId;
    Ipc_MbConfig cfg;
    uint32 baseAddr;

    selfId = Ipc_getCoreId();
    remoteProcId = IPC_MCU2_0;
    Ipc_getMailboxInfoRx(selfId, remoteProcId, &clusterId, &userId, &queueId);
    baseAddr = Ipc_getMailboxBaseAddr(clusterId);

    /* Clear Mailbox cluster queue */
    EthVirtmacApp_ipcMailboxClear(baseAddr, queueId);
    MailboxClrNewMsgStatus(baseAddr, userId, queueId);

    /* Get the Interrupt Configuration */
    Ipc_getMailboxIntrRouterCfg(selfId, clusterId, userId, &cfg, 0);

    /* Release the resource first */
    retVal = EthVirtmacApp_sciclientIrqRelease(selfId, clusterId, userId, cfg.eventId);

    uint32 timeout_cnt = 10;
    do
    {
        retVal = EthVirtmacApp_sciclientIrqSet(selfId, clusterId, userId, cfg.eventId);
        if(retVal != 0)
        {
            EthVirtmac_printf("Failed to register irq through sciclient...%x\n", retVal);
        }
        timeout_cnt--;
    }while((retVal != 0) && (timeout_cnt > 0));

    if(timeout_cnt == 0)
    {
        retVal = IPC_EFAIL;
    }

    /* Interrupt hookup */
    Osal_RegisterInterrupt_initParams(&intrPrms);
    intrPrms.corepacConfig.arg          = (uintptr_t)NULL;
    intrPrms.corepacConfig.isrRoutine   = &EthVirtmacApp_ipcMsgFromMcu20Isr;
    intrPrms.corepacConfig.priority     = cfg.priority;
    intrPrms.corepacConfig.corepacEventNum = 0U;
    intrPrms.corepacConfig.intVecNum    = cfg.eventId;

    osalRetVal = Osal_RegisterInterrupt(&intrPrms, &hwiHandle);
    if(OSAL_INT_SUCCESS != osalRetVal)
    {
        EthVirtmac_printf(
                         "Error Could not register ISR to receive"
                        " from MCU 2 0 !!!\n");
    }
    return;
}

/** \brief Start up sequence : Program the interrupt muxes / priorities */
static void EthVirtmacApp_ipcStartup(void)
{

    EthVirtmacApp_ipcPrintVersion();

    EthVirtmacApp_ipcInterruptConfig();

    /* Initialize memory sections  */
    AppUtils_CddIpcSectionInit();

}

static void EthVirtmacApp_initIpcCddCfg(struct Cdd_IpcConfigType_s *ipcCddCfg)
{
    uint32 numProc = gNumRemoteProc;
    uint32 i;

    ipcCddCfg->coreIds.numProcs = gNumRemoteProc;
    ipcCddCfg->coreIds.ownProcID = selfProcId;
    for (i = 0; i < UTILS_ARRAYSIZE(gRemoteProc); i++)
    {
        ipcCddCfg->coreIds.remoteProcID[i] = gRemoteProc[i];
    }
    ipcCddCfg->vertIoCfg.vertIoRingAddr = (void *)g_vringMemBuf;
    ipcCddCfg->vertIoCfg.vertIoRingSize = sizeof(g_vringMemBuf);
    ipcCddCfg->vertIoCfg.vertIoObjSize = numProc * Ipc_getVqObjMemoryRequiredPerCore();
    EthVirtmacAppUtils_assert(ipcCddCfg->channelCount > ETHVIRTMACAPP_REMOTEETHDEVICE_COMCHID);
}

static Std_ReturnType EthVirtmacApp_ipcInit(void)
{
    struct Cdd_IpcConfigType_s *ipcCddCfg = (struct Cdd_IpcConfigType_s *)&CddIpcConfiguraions_PC;

    EthVirtmacApp_initIpcCddCfg(ipcCddCfg);

    Cdd_IpcInit();

    return E_OK;
}

static void EthVirtmacApp_clockFxn (uintptr_t arg)
{
    Eth_MainFunction();
}

void EthVirtmacApp_initMainFunctionPoll(void)
{
    TimerP_Params timerPrms;

    TimerP_Params_init(&timerPrms);
    timerPrms.periodType = TimerP_PeriodType_MICROSECS;
    timerPrms.period     = ETHVIRTMACAPP_ETHMAIN_SCHEDULE_PERIOD_MS;
    timerPrms.runMode    = TimerP_RunMode_CONTINUOUS;
    timerPrms.startMode  = TimerP_StartMode_AUTO;
    timerPrms.arg        = &gEthVirtmacApp;

    gEthVirtmacApp.hEthMainPollTimer =  TimerP_create(TimerP_ANY,
                                            EthVirtmacApp_clockFxn,
                                            &timerPrms);
    EthVirtmacAppUtils_assert(gEthVirtmacApp.hEthMainPollTimer != NULL);
}


/**
 * \brief CDD IPC New message available notification
 *
 *  Would be invoked by the driver on reception of message from remote core.
 *  Name of this function is configurable, please refer configurator.
 */
void Cdd_IpcNewMessageNotify(uint32 comId)
{
    if (ETHVIRTMACAPP_REMOTEETHDEVICE_COMCHID == comId)
    {
        EthVirtmacApp_recvMsgNotify();
    }

    return;
}

void Cdd_IpcNewCtrlMessageNotify(uint32 remoteProcId)
{

}

#if 0
/**< Sections defined in linker command file for ADC module */
extern uint32 __linker_cdd_ipc_text_start, __linker_cdd_ipc_text_end,
              __linker_cdd_ipc_const_start, __linker_cdd_ipc_const_end,
              __linker_cdd_ipc_init_start, __linker_cdd_ipc_init_end,
              __linker_cdd_ipc_no_init_start, __linker_cdd_ipc_no_init_end,
              __linker_cdd_ipc_no_init_align_8b_start,
              __linker_cdd_ipc_no_init_align_8b_end;
/**< Address list of sections defined in linker command file for ADC module */
static uint32 CddIpcApp_SecHoleAddrList[] =
{
    ((uint32) & __linker_cdd_ipc_text_start),
    ((uint32) & __linker_cdd_ipc_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32) & __linker_cdd_ipc_const_start),
    ((uint32) & __linker_cdd_ipc_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32) & __linker_cdd_ipc_init_start),
    ((uint32) & __linker_cdd_ipc_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32) & __linker_cdd_ipc_no_init_start),
    ((uint32) & __linker_cdd_ipc_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32) & __linker_cdd_ipc_no_init_align_8b_start),
    ((uint32) & __linker_cdd_ipc_no_init_align_8b_end) -
                                                APP_UTILS_LINKER_FILL_LENGTH,
};

static void AppUtils_CddIpcSectionInit(void)
{
    /* Initialize memory sections  */
    AppUtils_SectionInit(&CddIpcApp_SecHoleAddrList[0U],
        MODULEAPP_NUM_SEC_HOLES(CddIpcApp_SecHoleAddrList));
}
#endif
