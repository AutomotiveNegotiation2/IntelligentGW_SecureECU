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
 *  \file     Eth_Priv.c
 *
 *  \brief    This file contains the implementation of internal helper
 *            functions of the Ethernet driver.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Dem.h"
#include "SchM_Eth.h"
#include "Eth_Cfg.h"
#include "Eth_Priv.h"
#include "cpsw/include/cpsw/Cpsw.h"
#include "Eth_LL.h"
#include "Eth_IrqPacing.h"
#if (STD_ON == ETH_ENABLE_MII_API)
#include "EthTrcv.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Eth cache size alignment
 */
#define ETH_DMA_CACHE_ALIGN_SIZE            (128U)

/**
 *  \brief Convert second to nano second
 */
#define ETH_SEC_TO_NS                       (1000000000LL)

/**
 *  \brief uint32 max value
 */
#define ETH_UINT32_MAX                      (0xFFFFFFFFU)

/**
 *  \brief Message type for egress packet use to retrive egress timestamp
 */
#define ETH_EGRESS_TIMESTAMP_MSG_TYPE       (1U)

/**
 *  \brief Domain ID for egress packet use to retrive egress timestamp
 */
#define ETH_EGRESS_TIMESTAMP_DOMAIN_ID      (5U)

/**
 *  \brief Mac port offset
 */
#define ETH_MAC_PORT_OFFSET                 (1u)

/**
 *  \brief Convert mac port id from user port
 */
#define ETH_GET_MAC_PHY_PORT_ID(PortId)     ((PortId) - ETH_MAC_PORT_OFFSET)

/**
 *  \brief Maximum buffer number in a FIFO
 */
#define ETH_MAX_BUFFER_NUM_IN_FIFO          (128U)

/**
 *  \brief Maximum buffer number in a FIFO
 */
#define ETH_INVALID_BUFFER_ID               (0xFFFFU)

/**
 *  \anchor Ethernet Protocol ID's
 *  \name Ethernet Protocol ID's
 *
 *  @{
 */
/** \brief Internet Protocol Version 4 (IPv4)   */
#define ETH_P_IP                            (0x0800U)
/** \brief Internet Protocol Version 6 (IPv6)   */
#define ETH_P_IPV6                          (0x86DDU)
/** \brief 802.1Q VLAN Extended Header          */
#define ETH_P_8021Q                         (0x8100U)
/* @} */

/**
 *  \anchor Standard IP Protocols
 *  \name Standard IP Protocols
 *
 *  @{
 */
/** \brief User Datagram Protocol (UDP)         */
#define IPPROTO_UDP                         (17U)
/** \brief Transmission Control Protocol (TCP)  */
#define IPPROTO_TCP                         (6U)
/* @} */

/** \brief Size of 802.1Q VLAN Extended Header  */
#define SIZEOF_VLAN_HDR                     (4U)

/** \brief IPv6 Header Length */
#define IPV6_HDR_LEN                        (40U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief Eth VLAN Frame Header
 */
typedef struct
{
    uint8 dstMac[ETH_MAC_ADDR_LEN];
    /**< Destination MAC address */
    uint8 srcMac[ETH_MAC_ADDR_LEN];
    /**< Source MAC address */
    uint16 tpid;
    /**< Tag Protocol Identifier */
    uint16 tci;
    /**< Tag Control Information */
    uint16 etherType;
    /**< EtherType field */
} __attribute__((packed)) Eth_vlanFrameHdr;

/**
 *  \brief IPv4 Header
 */
typedef struct
{
    uint8 v_hl;
    /**< IP version and Header Length */
    uint8 tos;
    /**< Type Of Service */
    uint16 len;
    /**< Total Length */
    uint16 id;
    /**< Identification */
    uint16 offset;
    /**< Flags + Fragment offset field */
    uint8 ttl;
    /**< Time to live */
    uint8 protocol;
    /**< Protocol */
    uint16 checksum;
    /**< IP Header Checksum */
    uint32 src_addr;
    /**< Source address */
    uint32 dst_addr;
    /**< Destination address */
} __attribute__((packed)) Eth_Ip4Hdr;

/**
 *  \brief IPv6 Header
 */
typedef struct
{
    uint32 v_tc_fl;
    /**< IP version + Traffic Class + Flow Label */
    uint16 pay_len;
    /**< Payload Length */
    uint8 next_hdr;
    /**< Next Header */
    uint8 hop_limit;
    /**< Hop Limit */
    uint32 src_addr[4];
    /**< Source address */
    uint32 dst_addr[4];
    /**< Destination address */
} __attribute__((packed)) Eth_Ip6Hdr;

/**
 *  \brief UDP Header
 */
typedef struct
{
    uint16 src_port;
    /**< UDP Source Port */
    uint16 dst_port;
    /**< UDP Destination Port */
    uint16 len;
    /**< Length (Header + Payload) */
    uint16 checksum;
    /**< UDP Frame Checksum of IP Header + UDP Header + Payload */
} __attribute__((packed)) Eth_UdpHdr;

/**
 *  \brief TCP Header
 */
typedef struct
{
    uint16 src_port;
    /**< TCP Source Port */
    uint16 dst_port;
    /**< TCP Destination Port */
    uint32 seq_num;
    /**< Sequence Number */
    uint32 ack_num;
    /**< Acknowledgment number */
    uint16 hl_flags;
    /**< TCP Header Lengh + Flags */
    uint16 window_size;
    /**< Window Size */
    uint16 checksum;
    /**< TCP Frame Checksum of IP Header + TCP Header + Payload */
    uint16 urgent_pointer;
    /**< Urgent Pointer */
} __attribute__((packed)) Eth_TcpHdr;

/* ========================================================================== */
/*                         Global Variable Definitions                        */
/* ========================================================================== */
#define  ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

Eth_CtrlErrorsType Eth_CtrlErrorsStats[ETH_CTRL_ID_MAX];
volatile Eth_MiiAccessType Eth_MiiAccess[ETH_CTRL_ID_MAX];

#define  ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_8
#include "Eth_MemMap.h"

extern VAR(uint8, ETH_VAR_CLEARED) Eth_CtrlMacAddress[ETH_CTRL_ID_MAX][ETH_MAC_ADDR_LEN];

#define ETH_STOP_SEC_VAR_NO_INIT_8
#include "Eth_MemMap.h"


#define  ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

VAR(CpswStats_Stats, ETH_VAR_CLEARED) Eth_Stats;

#define  ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"
#define ETH_START_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"

VAR(Eth_BufIdxType, ETH_VAR_NO_INIT) Eth_CurrentRxBufferIdx[ETH_CTRL_ID_MAX];

#define ETH_STOP_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Validate alignment Desc, Ring and data buffer memory
 *
 *  \param ctrlIdx  Eth controller idx
 *
 *  \return E_OK if all memory are aligned else E_NOT_OK;
 */
static Std_ReturnType Eth_validateDescRingAndBufferAlignment(uint8 ctrlIdx);

/**
 *  \brief Set Eth Dem event status
 *
 * This function will check Eth Dem event is valid or not to call Dem service API
 *
 * \param eventId     Eth Dem event Id
 * \param eventStatus event status
 *
 * \return none
 */
static void Eth_setDemEventStatus(Dem_EventIdType eventId, Dem_EventStatusType eventStatus);

/**
 *  \brief Init for Tx descriptor
 *
 *  \return none
 */
static void Eth_initTxDesc(uint8 ctrlIdx);

/**
 *  \brief Init for Rx descriptor
 *
 *  \param ctrlIdx  Eth controller idx
 *
 *  \return none
 */
static void Eth_initRxDesc(uint8 ctrlIdx);

/**
 *  \brief Retrive all Tx pending descriptor
 *
 *  \param ctrlIdx  Eth controller idx
 *
 *  \return none
 */
static void Eth_retrievePendingTxDesc(uint8 ctrlIdx);

/**
 *  \brief Retrive all Rx pending descriptor
 *
 *  \param ctrlIdx  Eth controller idx
 *
 *  \return none
 */
static void Eth_retrievePendingRxDesc(uint8 ctrlIdx);

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || \
     (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))

/**
 *  \brief Generate Pseudo IPv4 Header Checksum
 *
 *  \param ipPktStart   Pointer to the Start of IP Packet.
 *  \param ipPktPayLen  Length of IP Packet Payload
 *                      (i.e. UDP/TCP Header + Data Payload)
 *
 *  \return none
 */
static uint16 Eth_genPseudoCheckSumIPv4(uint8 *ipPktStart, uint16 ipPktPayLen);

/**
 *  \brief Generate Pseudo IPv6 Header Checksum
 *
 *  \param ipPktStart   Pointer to the Start of IP Packet.
 *  \param ipPktPayLen  Length of IP Packet Payload
 *                      (i.e. UDP/TCP Header + Data Payload)
 *
 *  \return none
 */
static uint16 Eth_genPseudoCheckSumIPv6(uint8 *ipPktStart, uint16 ipPktPayLen);

/**
 *  \brief Set the Pseudo Checksum to the UDP/TCP Header Checksum Field
 *
 *  \param pEthPkt      Pointer to the Start of Eth Packet.
 *  \param frameType    Ethernet Frame Type
 *  \param ipPktPayLen  Length of IP Packet Payload
 *                      (i.e. UDP/TCP Header + Data Payload)
 *  \param startIdx     returns the index to the start of checksum calculation.
 *  \param resultIdx    returns the index where the checksum result will be placed.
 *
 *  Note: For both startIdx and resultIdx first byte is index 1.
 *
 *  \return E_OK Pseudo Checksum generated successfully else E_NOT_OK
 */
static Std_ReturnType Eth_setPseudoCheckSum(Eth_Frame *pEthPkt,
                                            Eth_FrameType frameType,
                                            uint16 *ipPktPayLen,
                                            uint8 *startIdx,
                                            uint8 *resultIdx);

/**
 *  \brief Set Checksum Control Data
 *
 *  \param llDescPtr Pointer to Eth low level descriptor
 *  \param frame     Eth Frame Buffer that contains the data to be transmitted
 *
 *  \return none
 */
static void Eth_setCheckSumCtrl(Eth_DescType *llDescPtr, Eth_Frame *frame);

/**
 *  \brief Get the start to IP Frame
 *
 *  \param frameBuffer  Pointer to Eth Frame Buffer
 *
 *  \return pointer to the start of ip frame
 */
static inline uint8 *Eth_getIpPktStart(uint8 *frameBuffer);

#endif /* ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || \
           (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP)) */

/**
 *  \brief Convert uin64 timestamp to Eth timestamp
 *
 *  \param timeStampPtr  pointer to uint64 timestamp
 *  \param ethTimeStampPtr  pointer to Eth timestamp
 *
 *  \return none
 */
static inline void Eth_timeStampConvert(uint64 *timeStampPtr, Eth_TimeStampType *ethTimeStampPtr);

/**
 *  \brief Get fifo index and fifo buffer index from input bufferIdx
 *
 *  \param bufferIdx     input buffer index
 *  \param FifoIdx       pointer to fifo index
 *  \param fifoBuffIdx   pointer to fifo buffer index
 *
 *  \return none
 */
static inline void Eth_getFifoFromBufferIdx(Eth_BufIdxType bufferIdx, uint8 *FifoIdx, uint8 *fifoBuffIdx);

/**
 *  \brief Get bufferIdx from fifo index and fifo buffer index
 *
 *  \param FifoIdx       fifo index
 *  \param fifoBuffIdx   fifo buffer index
 *
 *  \return buffer index
 */
static inline Eth_BufIdxType Eth_getBufferIdxFromFifo(uint8 fifoIdx, uint16 fifoBuffIdx);

/**
 *  \brief Get value of uint8 left bit shift
 *
 *  \param bitNum       bit shift number
 *
 *  \return value of left shilf
 */
static inline uint8 Eth_GetLeftBitShiftValue(uint8 bitNum);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Std_ReturnType Eth_openCpsw(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;

    Eth_CtrlErrorsStats[ctrlIdx].rxCRC        = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].rxOverrun    = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].rxUndersized = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].rxOversized  = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].rxAlignCode  = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].txSingleColl = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].txMultiColl  = 0u;
    Eth_CtrlErrorsStats[ctrlIdx].txLateColl   = 0u;

    Eth_MiiAccess[ctrlIdx].isActive = FALSE;

    retVal |= Eth_validateDescRingAndBufferAlignment(ctrlIdx);

    if(E_OK == retVal)
    {
        if(Eth_IsVirtualMacModeEnable(ctrlIdx) == FALSE)
        {
            retVal = CpswMac_open(ETH_GET_MAC_PHY_PORT_ID(Eth_GetMacPortNum(ctrlIdx)),
                Eth_GetMiiConnectionType(ctrlIdx), MAC_FLAG_PASSCONTROL);

            if(E_OK == retVal)
            {
                CpswPort_hostPortopen();
                CpswStats_open();
                CpswAle_open(Eth_GetEnetType(ctrlIdx));
                CpswMdio_open(ctrlIdx);
                CpswCpts_open();

                CpswPort_setMaxLen(CPSW_PORT0, Eth_GetRxMtuLength(ctrlIdx));
                CpswPort_enableCpts(Eth_GetMacPortNum(ctrlIdx));

                CpswMac_setMaxLen(ETH_GET_MAC_PHY_PORT_ID(Eth_GetMacPortNum(ctrlIdx)),
                    Eth_GetRxMtuLength(ctrlIdx));

                CpswAle_setPortState(CPSW_PORT0,
                    CPSWMCAL_ALE_PORTSTATE_FORWARD);
                CpswAle_setPortState(Eth_GetMacPortNum(ctrlIdx),
                    CPSWMCAL_ALE_PORTSTATE_FORWARD);

                if(Eth_GetLoopBackMode(ctrlIdx))
                {
                    CpswMac_enableLoopback(ETH_GET_MAC_PHY_PORT_ID(Eth_GetMacPortNum(ctrlIdx)));
                }

                CpswStats_setPort(Eth_GetMacPortNum(ctrlIdx), TRUE);
                CpswPort_enable(CPSW_PORT0);
            }
        }

        if(TRUE == Eth_GetIrqPacingEnable(ctrlIdx))
        {
            retVal |= Eth_IrqPacingInit(ctrlIdx);
        }
    }

    return retVal;
}

Std_ReturnType Eth_closeCpsw(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;

    if(Eth_IsVirtualMacModeEnable(ctrlIdx) == FALSE)
    {
        CpswPort_disable(CPSW_PORT0);
        CpswAle_setPortState(CPSW_PORT0,
            CPSWMCAL_ALE_PORTSTATE_DISABLED);
        CpswAle_setPortState(Eth_GetMacPortNum(ctrlIdx),
            CPSWMCAL_ALE_PORTSTATE_DISABLED);

        CpswStats_setPort(Eth_GetMacPortNum(ctrlIdx), FALSE);
        CpswPort_disableCpts(Eth_GetMacPortNum(ctrlIdx));

        CpswAle_close();
        CpswStats_close();

        retVal |= CpswMac_close(ETH_GET_MAC_PHY_PORT_ID(Eth_GetMacPortNum(ctrlIdx)));
    }

    if(TRUE == Eth_GetIrqPacingEnable(ctrlIdx))
    {
        Eth_IrqPacingStopTimer(ctrlIdx);
    }

    return retVal;
}

Std_ReturnType Eth_disableCpsw(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    retVal |= CpswDma_disable(ctrlIdx);

    Eth_retrievePendingTxDesc(ctrlIdx);
    Eth_retrievePendingRxDesc(ctrlIdx);

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    retVal |= CpswDma_close(ctrlIdx);

    return retVal;
}

Std_ReturnType Eth_enableCpsw(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;

    retVal |= CpswDma_open(ctrlIdx);

    if(E_OK == retVal)
    {
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

        Eth_initTxDesc(ctrlIdx);
        Eth_initRxDesc(ctrlIdx);

        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

        if(Eth_IsVirtualMacModeEnable(ctrlIdx) == FALSE)
        {
            /* Set ALE policer default thread */
            CpswAle_setDefThread(Eth_GetRxChanFlowStartNum(ctrlIdx, 0u));
        }
    }

    retVal |= CpswDma_enable(ctrlIdx);

    return retVal;
}

Eth_RxStatusType Eth_receiveProcess(uint8 ctrlIdx, uint8 fifoIdx)
{
    Eth_RxStatusType status = ETH_NOT_RECEIVED;
    Eth_DescType *descPtr = (Eth_DescType *)NULL_PTR;
    Eth_Frame *frame = (Eth_Frame *)NULL_PTR;
    uint8 *payload = (uint8 *)NULL_PTR;
    uint64 descAddr;
    boolean isBroadcast;
    uint16 len;
    Eth_FrameType etherType;
    uint16 userLen;
    uint8 pendingPktNum;
    uint8 Idx;

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    pendingPktNum = CpswDma_retrieveReadPendingDescNumber(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx));

    for(Idx = 0u; Idx < pendingPktNum; ++Idx)
    {
        if(E_OK == CpswDma_retrieveDesc(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx), &descAddr))
        {
            descPtr = (Eth_DescType*)descAddr;
            userLen = Eth_GetLLDescBufferLen(Eth_GetIngressFifoDescAddress(ctrlIdx, fifoIdx, descPtr->bufferInfo.Idx));

            if(userLen > sizeof(Eth_FrameHeader))
            {
                descPtr = (Eth_DescType*)descAddr;

                if(Eth_GetCacheInvalidateFuncPtr(ctrlIdx))
                {
                    Eth_GetCacheInvalidateFuncPtr(ctrlIdx)(Eth_GetIngressFifoBufferDataAddress(ctrlIdx,
                        fifoIdx, descPtr->bufferInfo.Idx), userLen);
                }

                frame = (Eth_Frame *)Eth_GetIngressFifoBufferDataAddress(ctrlIdx, fifoIdx, descPtr->bufferInfo.Idx);
                etherType = ntohs(frame->hdr.etherType);
                len = userLen - (uint16)sizeof(Eth_FrameHeader);
                payload = frame->payload;
                isBroadcast = Eth_isBcastMacAddr(frame->hdr.dstMac);

                Eth_CurrentRxBufferIdx[ctrlIdx] = Eth_getBufferIdxFromFifo(fifoIdx, descPtr->bufferInfo.Idx);

                EthIf_RxIndication(ctrlIdx, etherType, isBroadcast, frame->hdr.srcMac,
                    (Eth_DataType *)payload, len);

                Eth_CurrentRxBufferIdx[ctrlIdx] = ETH_INVALID_BUFFER_ID;

                Eth_SetLLDescBufferAddressAndLength(descPtr,
                    Eth_GetIngressFifoBufferDataAddress(ctrlIdx, fifoIdx, descPtr->bufferInfo.Idx),
                    Eth_GetIngressFifoPacketSize(ctrlIdx, fifoIdx));

                if(Eth_DescriptorGetCacheInvalidateFuncPtr(ctrlIdx))
                {
                    Eth_DescriptorGetCacheInvalidateFuncPtr(ctrlIdx)((uint8*)descPtr, sizeof(Eth_DescType));
                }

                CpswDma_submitDesc(ctrlIdx, Eth_GetIngressFifoFqIdx(ctrlIdx, fifoIdx), descAddr);

                status = ETH_RECEIVED;
            }
        }
    }

    if(CpswDma_retrieveReadPendingDescNumber(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx)) > 0u)
    {
        status = ETH_RECEIVED_MORE_DATA_AVAILABLE;
    }

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    return status;
}

Eth_TxStatusType Eth_txProcess(uint8 ctrlIdx, uint8 fifoIdx)
{
    uint64 descAddr;
    Eth_DescType *descPtr;
    uint8 pendingPktNum;
    uint8 Idx;
    Eth_TxStatusType status = ETH_TRANSMITED_BUFFER_DONE;

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    pendingPktNum = CpswDma_retrieveReadPendingDescNumber(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx));

    for(Idx = 0u; Idx < pendingPktNum; Idx++)
    {
        if(E_OK == CpswDma_retrieveDesc(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx), &descAddr))
        {
            descPtr = (Eth_DescType*)descAddr;

            if(Eth_GetLeftBitShiftValue(ETH_BUF_STATE_CONFIRMATION) &
                Eth_GetEgressFifoBufferState(ctrlIdx, fifoIdx, descPtr->bufferInfo.Idx))
            {
                EthIf_TxConfirmation(ctrlIdx,
                    Eth_getBufferIdxFromFifo(fifoIdx, descPtr->bufferInfo.Idx),
                    E_OK);
            }

            Eth_SetEgressFifoBufferState(ctrlIdx, fifoIdx, descPtr->bufferInfo.Idx, ETH_BUF_STATE_FREE);
            Eth_Queue_add(Eth_GetEgressFifoQueueAddress(ctrlIdx, fifoIdx),
                Eth_GetEgressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descPtr->bufferInfo.Idx));
        }
    }

    if(CpswDma_retrieveReadPendingDescNumber(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx)) > 0u)
    {
        status = ETH_TRANSMITED_BUFFER_PENDING;
    }

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    return status;
}

BufReq_ReturnType Eth_provideTxBuffer(uint8 CtrlIdx,
        uint8 FifoIdx,
        Eth_BufIdxType *BufIdxPtr,
        uint8 **BufPtr,
        uint16 *LenBytePtr)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    Eth_BufferInforType *queueNode = (Eth_BufferInforType *)NULL_PTR;

    if((*LenBytePtr) > (Eth_GetEgressFifoPacketSize(CtrlIdx, FifoIdx) - ETH_HEADER_LEN))
    {
        retVal = BUFREQ_E_OVFL;
    }
    else
    {
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

        queueNode = Eth_Queue_remove(Eth_GetEgressFifoQueueAddress(CtrlIdx, FifoIdx));

        if(queueNode != NULL_PTR)
        {
            *BufIdxPtr = Eth_getBufferIdxFromFifo(FifoIdx, queueNode->Idx);
            *BufPtr = (uint8 *)Eth_GetEgressFifoBufferDataAddress(CtrlIdx, FifoIdx, queueNode->Idx) + ETH_HEADER_LEN;
            Eth_SetEgressFifoBufferState(CtrlIdx, FifoIdx, queueNode->Idx, Eth_GetLeftBitShiftValue(ETH_BUF_STATE_IN_USE));
            retVal = BUFREQ_OK;
        }
        else
        {
            retVal = BUFREQ_E_BUSY;
        }

        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
    }

    return retVal;
}

Std_ReturnType Eth_transmit(uint8 CtrlIdx,
        Eth_BufIdxType BufIdx,
        Eth_FrameType FrameType,
        boolean TxConfirmation,
        uint16 LenByte,
        const uint8* PhysAddrPtr)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 fifoIdx;
    uint8 fifoBuffIdx;
    uint8 buffState;
    Eth_Frame *frame;

    Eth_getFifoFromBufferIdx(BufIdx, &fifoIdx, &fifoBuffIdx);

    if((fifoIdx < Eth_GetEgressFifoTotalNum(CtrlIdx)) &&
        (fifoBuffIdx < Eth_GetEgressFifoPacketNum(CtrlIdx, fifoIdx)))
    {
        if(Eth_GetLeftBitShiftValue(ETH_BUF_STATE_IN_USE) & Eth_GetEgressFifoBufferState(CtrlIdx, fifoIdx, fifoBuffIdx))
        {
            frame = (Eth_Frame *)Eth_GetEgressFifoBufferDataAddress(CtrlIdx, fifoIdx, fifoBuffIdx);

            frame->hdr.dstMac[0u] = PhysAddrPtr[0u];
            frame->hdr.dstMac[1u] = PhysAddrPtr[1u];
            frame->hdr.dstMac[2u] = PhysAddrPtr[2u];
            frame->hdr.dstMac[3u] = PhysAddrPtr[3u];
            frame->hdr.dstMac[4u] = PhysAddrPtr[4u];
            frame->hdr.dstMac[5u] = PhysAddrPtr[5u];

            frame->hdr.srcMac[0u] = Eth_CtrlMacAddress[CtrlIdx][0u];
            frame->hdr.srcMac[1u] = Eth_CtrlMacAddress[CtrlIdx][1u];
            frame->hdr.srcMac[2u] = Eth_CtrlMacAddress[CtrlIdx][2u];
            frame->hdr.srcMac[3u] = Eth_CtrlMacAddress[CtrlIdx][3u];
            frame->hdr.srcMac[4u] = Eth_CtrlMacAddress[CtrlIdx][4u];
            frame->hdr.srcMac[5u] = Eth_CtrlMacAddress[CtrlIdx][5u];

            frame->hdr.etherType = htons(FrameType);

            Eth_SetLLDescBufferAddressAndLength(Eth_GetEgressFifoDescAddress(CtrlIdx, fifoIdx, fifoBuffIdx),
                Eth_GetEgressFifoBufferDataAddress(CtrlIdx, fifoIdx, fifoBuffIdx),
                (ETH_HEADER_LEN + LenByte));

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || \
     (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
            Eth_setCheckSumCtrl(Eth_GetEgressFifoDescAddress(CtrlIdx, fifoIdx, fifoBuffIdx), frame);
#endif

            if(Eth_GetCacheWritebackFuncPtr(CtrlIdx))
            {
                Eth_GetCacheWritebackFuncPtr(CtrlIdx)(
                    Eth_GetEgressFifoBufferDataAddress(CtrlIdx, fifoIdx, fifoBuffIdx),
                    (ETH_HEADER_LEN + LenByte));
            }

            if(Eth_DescriptorGetCacheWritebackInvalidateFuncPtr(CtrlIdx))
            {
                Eth_DescriptorGetCacheWritebackInvalidateFuncPtr(CtrlIdx)(
                    (uint8 *)Eth_GetEgressFifoDescAddress(CtrlIdx, fifoIdx, fifoBuffIdx),
                    sizeof(Eth_DescType));
            }

            SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

            CpswDma_submitDesc(CtrlIdx,
                Eth_GetEgressFifoFqIdx(CtrlIdx, fifoIdx),
                (uint64)Eth_GetEgressFifoDescAddress(CtrlIdx, fifoIdx, fifoBuffIdx));

            buffState = Eth_GetLeftBitShiftValue(ETH_BUF_STATE_QUEUED);

            if(TRUE == TxConfirmation)
            {
                buffState |= Eth_GetLeftBitShiftValue(ETH_BUF_STATE_CONFIRMATION);
            }

            Eth_SetEgressFifoBufferState(CtrlIdx, fifoIdx, fifoBuffIdx, buffState);

            SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

            retVal = E_OK;
        }
    }

    return retVal;
}

Std_ReturnType Eth_getCurrentTime(uint8 CtrlIdx,
    Eth_TimeStampQualType *timeQualPtr, Eth_TimeStampType *timeStampPtr)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint64 tsVal;

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    retVal = CpswCpts_getCurrentTimeStamp(&tsVal);

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    if(E_OK == retVal)
    {
        Eth_timeStampConvert(&tsVal, timeStampPtr);
        *timeQualPtr = ETH_VALID;
    }
    else
    {
        *timeQualPtr = ETH_INVALID;
    }

    return retVal;
}

void Eth_getIngressTimeStamp(uint8 ctrlIdx,
    Eth_DataType *dataPtr,
    Eth_TimeStampQualType *timeQualPtr,
    Eth_TimeStampType *timeStampPtr)
{
    uint8 fifoIdx;
    uint8 fifoBuffIdx;
    uint64 tsVal;

    *timeQualPtr = ETH_INVALID;

    Eth_getFifoFromBufferIdx(Eth_CurrentRxBufferIdx[ctrlIdx], &fifoIdx, &fifoBuffIdx);

    if((fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx)) &&
        (fifoBuffIdx < Eth_GetIngressFifoPacketNum(ctrlIdx, fifoIdx)))
    {
        if(fifoBuffIdx < Eth_GetIngressFifoPacketNum(ctrlIdx, fifoIdx))
        {
            tsVal = Eth_GetLLIngressTimeStamp(Eth_GetIngressFifoDescAddress(ctrlIdx,
                fifoIdx, fifoBuffIdx));
            Eth_timeStampConvert(&tsVal, timeStampPtr);
            *timeQualPtr = ETH_VALID;
        }
    }
}

void Eth_enableEgressTimeStamp(uint8 ctrlIdx, Eth_BufIdxType bufIdx)
{
    uint8 fifoIdx;
    uint8 fifoBuffIdx;

    Eth_getFifoFromBufferIdx(bufIdx, &fifoIdx, &fifoBuffIdx);

    if((fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx)) &&
        (fifoBuffIdx < Eth_GetEgressFifoPacketNum(ctrlIdx, fifoIdx)))
    {
        Eth_SetLLDescTimeStamp(Eth_GetEgressFifoDescAddress(ctrlIdx, fifoIdx, fifoBuffIdx),
            ETH_EGRESS_TIMESTAMP_DOMAIN_ID,
            ETH_EGRESS_TIMESTAMP_MSG_TYPE,
            bufIdx,
            TRUE);
    }
}

void Eth_getEgressTimeStamp(uint8 ctrlIdx,
    Eth_BufIdxType bufIdx,
    Eth_TimeStampQualType *timeQualPtr,
    Eth_TimeStampType *timeStampPtr)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8 fifoIdx;
    uint8 fifoBuffIdx;
    uint64 tsVal;

    Eth_getFifoFromBufferIdx(bufIdx, &fifoIdx, &fifoBuffIdx);

    if((fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx)) &&
        (fifoBuffIdx < Eth_GetEgressFifoPacketNum(ctrlIdx, fifoIdx)))
    {
        retVal = CpswCpts_getHostEgressTimeStamp(ETH_EGRESS_TIMESTAMP_DOMAIN_ID,
            ETH_EGRESS_TIMESTAMP_MSG_TYPE,
            bufIdx,
            &tsVal);

        if(E_OK == retVal)
        {
            Eth_timeStampConvert(&tsVal, timeStampPtr);
            *timeQualPtr = ETH_VALID;
        }
        else
        {
            *timeQualPtr = ETH_INVALID;
        }

        Eth_SetLLDescTimeStamp(Eth_GetEgressFifoDescAddress(ctrlIdx, fifoIdx, fifoBuffIdx),
            ETH_EGRESS_TIMESTAMP_DOMAIN_ID,
            ETH_EGRESS_TIMESTAMP_MSG_TYPE,
            bufIdx,
            FALSE);
    }
}

Std_ReturnType Eth_setBandwidthLimit(uint8 ctrlIdx,
    uint8   queuePrio,
    uint32  bandwidthLimit)
{
    Std_ReturnType retVal = E_OK;

    CpswPort_setBandwidthLimit(Eth_GetMacPortNum(ctrlIdx),
        queuePrio,
        bandwidthLimit);

    return retVal;
}

Std_ReturnType Eth_getBandwidthLimit(uint8 ctrlIdx,
    uint8  queuePrio,
    uint32 *bandwidthLimitPtr)
{
    Std_ReturnType retVal = E_OK;

    CpswPort_getBandwidthLimit(Eth_GetMacPortNum(ctrlIdx),
        queuePrio,
        bandwidthLimitPtr);

    return retVal;
}

Std_ReturnType Eth_checkControllerAccess(uint8 ctrlIdx)
{
    Std_ReturnType retVal;
    ETH_CSL_CPSW_VERSION info;

    ETH_CSL_CPSW_getCpswVersionInfo((CSL_Xge_cpswRegs *)Eth_Cpsw_GetCtrlRegAddr(), &info);

    /* Requirements: SWS_Eth_00173 */
    if (info.majorVer >= 1U)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_ACCESS(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
        retVal = E_OK;
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_ACCESS(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
        retVal = E_NOT_OK;
    }

    return retVal;
}

void Eth_checkControllerErrors(uint8 ctrlIdx)
{
    Eth_CtrlErrorsType *errors = &Eth_CtrlErrorsStats[ctrlIdx];
    CpswPort_Num port;

    CpswStats_getStats(Eth_GetMacPortNum(ctrlIdx), &Eth_Stats);

    if (Eth_Stats.RxCRCErrors > errors->rxCRC)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_CRC(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_CRC(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.RxDropBottom > errors->rxOverrun)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_RX_FRAMES_LOST(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_RX_FRAMES_LOST(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.RxUndersized > errors->rxUndersized)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_UNDERSIZEFRAME(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_UNDERSIZEFRAME(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.RxOversized > errors->rxOversized)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_OVERSIZEFRAME(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_OVERSIZEFRAME(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.RxAlignCodeErrors > errors->rxAlignCode)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_ALIGNMENT(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_ALIGNMENT(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.TxSingleColl > errors->txSingleColl)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_SINGLECOLLISION(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_SINGLECOLLISION(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.TxMultiColl > errors->txMultiColl)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_MULTIPLECOLLISION(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_MULTIPLECOLLISION(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    if (Eth_Stats.TxLateColl > errors->txLateColl)
    {
        Eth_setDemEventStatus(Eth_GetDem_E_LATECOLLISION(ctrlIdx), DEM_EVENT_STATUS_PREFAILED);
    }
    else
    {
        Eth_setDemEventStatus(Eth_GetDem_E_LATECOLLISION(ctrlIdx), DEM_EVENT_STATUS_PREPASSED);
    }

    errors->rxCRC        = Eth_Stats.RxCRCErrors;
    errors->rxOverrun    = Eth_Stats.RxDropBottom;
    errors->rxUndersized = Eth_Stats.RxUndersized;
    errors->rxOversized  = Eth_Stats.RxOversized;
    errors->rxAlignCode  = Eth_Stats.RxAlignCodeErrors;
    errors->txSingleColl = Eth_Stats.TxSingleColl;
    errors->txMultiColl  = Eth_Stats.TxMultiColl;
    errors->txLateColl   = Eth_Stats.TxLateColl;
}

void Eth_getRxStatsRFC2819(uint8 ctrlIdx, Eth_RxStatsType *RxStats)
{
    CpswStats_getStats(Eth_GetMacPortNum(ctrlIdx), &Eth_Stats);

    RxStats->RxStatsDropEvents           = Eth_Stats.RxAleDrop +
                                           Eth_Stats.RxAleOverrunDrop +
                                           Eth_Stats.RxDropBottom +
                                           Eth_Stats.PortmaskDrop +
                                           Eth_Stats.RxDropTop +
                                           Eth_Stats.AleRateLimitDrop +
                                           Eth_Stats.AleVidDrop +
                                           Eth_Stats.AleAddrEqDrop;
    RxStats->RxStatsOctets               = Eth_Stats.RxOctets;
    RxStats->RxStatsPkts                 = Eth_Stats.RxGoodFrames +
                                           Eth_Stats.RxBCastFrames +
                                           Eth_Stats.RxMCastFrames;
    RxStats->RxStatsBroadcastPkts        = Eth_Stats.RxBCastFrames;
    RxStats->RxStatsMulticastPkts        = Eth_Stats.RxMCastFrames;
    RxStats->RxStatsCrcAlignErrors       = Eth_Stats.RxCRCErrors +
                                           Eth_Stats.RxAlignCodeErrors;
    RxStats->RxStatsUndersizePkts        = Eth_Stats.RxUndersized;
    RxStats->RxStatsOversizePkts         = Eth_Stats.RxOversized;
    RxStats->RxStatsFragments            = Eth_Stats.RxFragments;
    RxStats->RxStatsJabbers              = Eth_Stats.RxJabber;
    RxStats->RxStatsCollisions           = ETH_STATCNT_INVALID;
    RxStats->RxStatsPkts64Octets         = ETH_STATCNT_INVALID;
    RxStats->RxStatsPkts65to127Octets    = ETH_STATCNT_INVALID;
    RxStats->RxStatsPkts128to255Octets   = ETH_STATCNT_INVALID;
    RxStats->RxStatsPkts256to511Octets   = ETH_STATCNT_INVALID;
    RxStats->RxStatsPkts512to1023Octets  = ETH_STATCNT_INVALID;
    RxStats->RxStatsPkts1024to1518Octets = ETH_STATCNT_INVALID;
    RxStats->RxUnicastFrames             = Eth_Stats.RxGoodFrames -
                                           Eth_Stats.RxBCastFrames -
                                           Eth_Stats.RxMCastFrames;
}

void Eth_getTxStatsRFC1213(uint8 ctrlIdx, Eth_TxStatsType *TxStats)
{
    CpswStats_getStats(Eth_GetMacPortNum(ctrlIdx), &Eth_Stats);

    TxStats->TxNumberOfOctets = Eth_Stats.TxOctets;
    TxStats->TxNUcastPkts     = Eth_Stats.TxBCastFrames +
                                Eth_Stats.TxMCastFrames;
    TxStats->TxUniCastPkts    = Eth_Stats.TxGoodFrames -
                                Eth_Stats.TxBCastFrames -
                                Eth_Stats.TxMCastFrames;
}

void Eth_getTxErrorCounterValues(uint8 ctrlIdx, Eth_TxErrorCounterValuesType *TxErrorCounterValues)
{
    uint32 i;

    CpswStats_getStats(Eth_GetMacPortNum(ctrlIdx), &Eth_Stats);

    /* Check drop count for all 8 priorities levels */
    for (i = 0U; i < ETH_PRIORITY_QUEUE_NUM; i++)
    {
        TxErrorCounterValues->TxDroppedErrorPkts = Eth_Stats.TxPriDropPktCnt[i];
    }

    TxErrorCounterValues->TxDeferredTrans      = Eth_Stats.TxDeferred;
    TxErrorCounterValues->TxSingleCollision    = Eth_Stats.TxSingleColl;
    TxErrorCounterValues->TxMultipleCollision  = Eth_Stats.TxMultiColl;
    TxErrorCounterValues->TxLateCollision      = Eth_Stats.TxLateColl;
    TxErrorCounterValues->TxExcessiveCollison  = Eth_Stats.TxExcessiveColl;
    TxErrorCounterValues->TxDroppedNoErrorPkts = ETH_STATCNT_INVALID;
}

void Eth_getCounterValues(uint8 ctrlIdx, Eth_CounterType* CounterPtr)
{
    CpswStats_getStats(Eth_GetMacPortNum(ctrlIdx), &Eth_Stats);

    CounterPtr->DropPktBufOverrun = Eth_Stats.RxDropBottom;
    CounterPtr->DropPktCrc        = Eth_Stats.RxCRCErrors;
    CounterPtr->UndersizePkt      = Eth_Stats.RxUndersized;
    CounterPtr->OversizePkt       = Eth_Stats.RxOversized;
    CounterPtr->AlgnmtErr         = Eth_Stats.RxAlignCodeErrors;
    CounterPtr->SqeTestErr        = ETH_STATCNT_INVALID;
    CounterPtr->DiscInbdPkt       = ETH_STATCNT_INVALID;
    CounterPtr->ErrInbdPkt        = Eth_Stats.RxAlignCodeErrors +
                                    Eth_Stats.RxOversized +
                                    Eth_Stats.RxUndersized +
                                    Eth_Stats.RxCRCErrors;
    CounterPtr->DiscOtbdPkt       = ETH_STATCNT_INVALID;
    CounterPtr->ErrOtbdPkt        = Eth_Stats.TxDeferred +
                                    Eth_Stats.TxCollision +
                                    Eth_Stats.TxCarrierSLoss;
    CounterPtr->SnglCollPkt       = Eth_Stats.TxSingleColl;
    CounterPtr->MultCollPkt       = Eth_Stats.TxMultiColl;
    CounterPtr->DfrdPkt           = Eth_Stats.TxDeferred;
    CounterPtr->LatCollPkt        = Eth_Stats.TxLateColl;
    CounterPtr->HwDepCtr0         = Eth_Stats.TxExcessiveColl;
    CounterPtr->HwDepCtr1         = Eth_Stats.TxCarrierSLoss;
    CounterPtr->HwDepCtr2         = ETH_STATCNT_INVALID;
    CounterPtr->HwDepCtr3         = ETH_STATCNT_INVALID;
}

Std_ReturnType Eth_getCounterState(uint8 ctrlIdx, uint16 CtrOffs, uint32 *CtrValPtr)
{
    Std_ReturnType retVal = E_OK;
    uint32 *accStats = (uint32 *)&Eth_Stats;
    uint16 maxOffset = sizeof(CpswStats_Stats)/sizeof(uint32);

    /* Check if CtrOffs is within our supported offset */
    if (CtrOffs < maxOffset)
    {
        /* return error if CtrOffs belongs to reserved offsets */
        if ((CtrOffs >= CPSW_STATS_RSV1_OFFSET_START(&Eth_Stats) &&
             CtrOffs < CPSW_STATS_RSV1_OFFSET_END(&Eth_Stats)) ||
            (CtrOffs >= CPSW_STATS_RSV2_OFFSET_START(&Eth_Stats) &&
             CtrOffs < CPSW_STATS_RSV2_OFFSET_END(&Eth_Stats)))
        {
            retVal = E_NOT_OK;
        }
        else
        {
            CpswStats_getStats(Eth_GetMacPortNum(ctrlIdx), &Eth_Stats);
            *CtrValPtr = accStats[CtrOffs];
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }
    return retVal;
}

boolean Eth_isBcastMacAddr(const uint8 *addr)
{
    uint32 i;
    boolean retVal = TRUE;

    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        if (addr[i] != 0xFFU)
        {
            retVal = FALSE;
            break;
        }
    }

    return retVal;
}

boolean Eth_isMcastMacAddr(const uint8 *addr)
{
    boolean retVal;

    /* MSbit (right most bit) of the MSB (first byte) is 1, then
     * the address is multicast, otherwise it's unicast */
    if (0U != (addr[0U] & 1))
    {
        retVal = TRUE;
    }
    else
    {
        retVal = FALSE;
    }

    return retVal;
}

boolean Eth_isNullMacAddr(const uint8 *addr)
{
    uint32 i;
    boolean retVal = TRUE;

    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        if (addr[i] != 0x00U)
        {
            retVal = FALSE;
            break;
        }
    }

    return retVal;
}

Std_ReturnType Eth_setMacAddr(uint8 ctrlIdx, const uint8 *addr)
{
    Std_ReturnType ret = E_NOT_OK;

    if (Eth_IsVirtualMacModeEnable(ctrlIdx) == FALSE)
    {
        /* Set the address to the MAC port */
        ret = CpswPort_setMacAddr(Eth_GetMacPortNum(ctrlIdx), addr);
    }
    return ret;
}

Std_ReturnType Eth_setPromiscuousMode(uint8 ctrlIdx)
{
    /* Clear ALE table and enable bypass */
    CpswAle_clearTable();
    CpswAle_setBypass(TRUE);

    return E_OK;
}

Std_ReturnType Eth_setNonPromiscuousMode(uint8 ctrlIdx, uint8 *addr)
{
    Std_ReturnType ret = E_NOT_OK;
    uint32 pn = Eth_GetMacPortNum(ctrlIdx);
    uint32 portMask = ALE_PORT_MASK_BIT(CPSW_PORT0) |
                          ALE_PORT_MASK_BIT(pn);
    uint32 vlanId = 0U;
    const uint8 bcastAddr[ETH_MAC_ADDR_LEN] = {
            0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
        };

    /* Clear ALE table and disable bypass */
    CpswAle_clearTable();
    CpswAle_setBypass(FALSE);

    /* Add broadcast address entry in ALE for ports 0 and n */
    ret = CpswAle_addMcastAddr(bcastAddr, vlanId, portMask, FALSE, CPSWMCAL_ALE_PORTSTATE_FORWARD);

    /* Add unicast entry in ALE for Port 0 */
    if (E_OK == ret)
    {
        ret = CpswAle_addUcastAddr(CPSW_PORT0, addr, vlanId, FALSE, FALSE);
    }

    /* Set VLAN list and flood mask */
    if (E_OK == ret)
    {
        CpswAle_setUnknownVlan(portMask);
        CpswAle_setUnknownRegMcastFlood(portMask);
        /* Unregistered multicast are flooded to MAC port only.
         * Multicast packets are forwarded to host port only if the address
         * is added via Eth_UpdatePhysAddrFilter(), not via flooding. */
        CpswAle_setUnknownMcastFlood(ALE_PORT_MASK_BIT(pn));
    }

    if (E_OK != ret)
    {
        CpswAle_clearTable();
    }
    return ret;
}

Std_ReturnType Eth_replaceUcastAddr(uint8 ctrlIdx, const uint8 *oldAddr, const uint8 *newAddr)
{
    uint32 vlanId = 0U;
    Std_ReturnType ret = E_NOT_OK;

    /* Delete ALE entries for the old unicast address */
    CpswAle_removeUcastAddr(oldAddr, vlanId);

    /* Add unicast entry in ALE for Port 0 */
    ret = CpswAle_addUcastAddr(CPSW_PORT0, newAddr, vlanId, FALSE, FALSE);

    return ret;
}

Std_ReturnType Eth_addFilterAddr(uint8 ctrlIdx, const uint8 *addr)
{
    uint32 pn = Eth_GetMacPortNum(ctrlIdx);
    uint32 vlanId = 0U;
    Std_ReturnType ret = E_NOT_OK;

    if (TRUE == Eth_isMcastMacAddr(addr))
    {
        ret = CpswAle_addMcastAddr(addr, vlanId,
                                   ALE_PORT_MASK_BIT(CPSW_PORT0) |
                                   ALE_PORT_MASK_BIT(pn),
                                   FALSE,
                                   CPSWMCAL_ALE_PORTSTATE_FORWARD);
    }
    else
    {
        ret = CpswAle_addUcastAddr(CPSW_PORT0, addr, vlanId, FALSE, FALSE);
    }

    return ret;
}

Std_ReturnType Eth_delFilterAddr(uint8 ctrlIdx, const uint8 *addr)
{
    uint32 pn = Eth_GetMacPortNum(ctrlIdx);
    uint32 vlanId = 0U;
    Std_ReturnType ret = E_NOT_OK;

    if (TRUE == Eth_isMcastMacAddr(addr))
    {
        ret = CpswAle_removeMcastAddr(addr, vlanId,
                                      ALE_PORT_MASK_BIT(CPSW_PORT0) |
                                      ALE_PORT_MASK_BIT(pn));
    }
    else
    {
        ret = CpswAle_removeUcastAddr(addr, vlanId);
    }

    return ret;
}

#if (STD_ON == ETH_ENABLE_MII_API)

Std_ReturnType Eth_triggerMiiRead(uint8 ctrlIdx, uint8 trcvIdx, uint8 regIdx)
{
    Std_ReturnType ret = E_OK;
    uint32 timeoutCnt = 0u;
    uint16 regVal;

    /* Initiate MDIO register read operation if the PHY is alive */
    if (TRUE == CpswMdio_isPhyAlive(ctrlIdx, trcvIdx))
    {
        Eth_MiiAccess[ctrlIdx].isActive = TRUE;
        Eth_MiiAccess[ctrlIdx].isRead = TRUE;
        Eth_MiiAccess[ctrlIdx].trcvIdx = trcvIdx;
        Eth_MiiAccess[ctrlIdx].regIdx = regIdx;

        if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
        {
            /* In Manual Mode, read trigger is not needed.
             * Read Phy register directly */
            ret = CpswMdio_readPhyReg(ctrlIdx, trcvIdx, regIdx, &regVal);
            if (CPSW_SOK == ret)
            {
                EthTrcv_ReadMiiIndication(ctrlIdx, trcvIdx, regIdx, regVal);
            }

            Eth_MiiAccess[ctrlIdx].isActive = FALSE;
            Eth_MiiAccess[ctrlIdx].isRead = FALSE;
        }
        else
        {
            while (E_NOT_OK == CpswMdio_initiatePhyRegRead(trcvIdx, regIdx))
            {
                if (timeoutCnt > Eth_GetHardwareLoopTimeout(ctrlIdx))
                {
                    ret = E_NOT_OK;
                    break;
                }
                timeoutCnt++;
            }

            if (E_OK != ret)
            {
                Eth_MiiAccess[ctrlIdx].isActive = FALSE;
                Eth_MiiAccess[ctrlIdx].isRead = FALSE;
            }
        }
    }

    return ret;
}

Std_ReturnType Eth_triggerMiiWrite(uint8 ctrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 regVal)
{
    Std_ReturnType ret = E_OK;
    uint32 timeoutCnt = 0u;

    /* Initiate MDIO register write operation if the PHY is alive */
    if (TRUE == CpswMdio_isPhyAlive(ctrlIdx, trcvIdx))
    {
        if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
        {
            /* In Manual Mode, write trigger is not needed.
             * Write to Phy register directly */
            CpswMdio_writePhyReg(ctrlIdx, trcvIdx, regIdx, regVal);

            /* Call EthTrcv MII Indication here to update flags */
            Eth_MiiAccess[ctrlIdx].isActive = TRUE;
            EthTrcv_WriteMiiIndication(ctrlIdx, trcvIdx, regIdx);
            Eth_MiiAccess[ctrlIdx].isActive = FALSE;
        }
        else
        {
            while (E_NOT_OK == CpswMdio_initiatePhyRegWrite(trcvIdx, regIdx, regVal))
            {
                if (timeoutCnt > Eth_GetHardwareLoopTimeout(ctrlIdx))
                {
                    ret = E_NOT_OK;
                    break;
                }
                timeoutCnt++;
            }

            if (E_OK == ret)
            {
                Eth_MiiAccess[ctrlIdx].isActive = TRUE;
                Eth_MiiAccess[ctrlIdx].isRead = FALSE;
                Eth_MiiAccess[ctrlIdx].trcvIdx = trcvIdx;
                Eth_MiiAccess[ctrlIdx].regIdx = regIdx;
            }
        }
    }

    return ret;
}

#if (STD_ON == ETH_WRAPPER_ENABLED)
Std_ReturnType Eth_triggerMiiReadSync(uint8 ctrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 *regVal)
{
    Std_ReturnType ret = E_NOT_OK;
    uint32 timeoutCnt = 0u;

    /* Initiate MDIO register read operation if the PHY is alive */
    if (TRUE == CpswMdio_isPhyAlive(ctrlIdx, trcvIdx))
    {
        if (E_OK == CpswMdio_initiatePhyRegRead(trcvIdx, regIdx))
        {
            while (TRUE == CpswMdio_isPhyRegReadWritePending())
            {
                if(timeoutCnt > Eth_GetHardwareLoopTimeout(ctrlIdx))
                {
                    break;
                }
                timeoutCnt++;
            }

            if (timeoutCnt <= Eth_GetHardwareLoopTimeout(ctrlIdx))
            {
                ret = Eth_getMiiReadVal(ctrlIdx, regVal);
                if (E_OK == ret)
                {
                    EthTrcv_ReadMiiIndication(ctrlIdx, trcvIdx, regIdx, (*regVal));
                }
            }
        }
    }

    return ret;
}

Std_ReturnType Eth_triggerMiiWriteSync(uint8 ctrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 regVal)
{
    Std_ReturnType ret = E_NOT_OK;
    uint32 timeoutCnt = 0u;

    /* Initiate MDIO register write operation if the PHY is alive */
    if (TRUE == CpswMdio_isPhyAlive(ctrlIdx, trcvIdx))
    {
        if (E_OK == CpswMdio_initiatePhyRegWrite(trcvIdx, regIdx, regVal))
        {
            while (TRUE == CpswMdio_isPhyRegReadWritePending())
            {
                if (timeoutCnt > Eth_GetHardwareLoopTimeout(ctrlIdx))
                {
                    break;
                }
                timeoutCnt++;
            }

            if (timeoutCnt <= Eth_GetHardwareLoopTimeout(ctrlIdx))
            {
                EthTrcv_WriteMiiIndication(ctrlIdx, trcvIdx, regIdx);
                ret = E_OK;
            }
        }
    }

    return ret;
}
#endif /* (STD_ON == ETH_WRAPPER_ENABLED) */

Std_ReturnType Eth_getMiiReadVal(uint8 ctrlIdx, uint16 *regVal)
{
    /* Get value read from PHY register */
    return CpswMdio_getPhyRegVal(ctrlIdx,
                                 Eth_MiiAccess[ctrlIdx].trcvIdx,
                                 Eth_MiiAccess[ctrlIdx].regIdx,
                                 regVal);
}

void Eth_clearMdioInt(uint8 ctrlIdx)
{
    CpswMdio_clearUserInt();
    (void)ctrlIdx;
}

#endif /* (STD_ON == ETH_ENABLE_MII_API) */

void Eth_readMacAddr(uint8 ctrlIdx, uint8 *addr)
{
#if (STD_OFF == ETH_VIRTUALMAC_SUPPORT)
    uint32 MacAddrUpper16Bits = *(uint32*)(Eth_Cpsw_GetPhyMacRegAddr() + 4U);
    uint32 MacAddrLower32Bits = *(uint32*)(Eth_Cpsw_GetPhyMacRegAddr());

    addr[0] = (uint8)(MacAddrUpper16Bits >> 8u);
    addr[1] = (uint8)(MacAddrUpper16Bits);
    addr[2] = (uint8)(MacAddrLower32Bits >> 24u);
    addr[3] = (uint8)(MacAddrLower32Bits >> 16u);
    addr[4] = (uint8)(MacAddrLower32Bits >> 8u);
    addr[5] = (uint8)(MacAddrLower32Bits);

    (void)ctrlIdx;
#else
    addr[0] = Eth_VirtMacInfo[ctrlIdx].macAddress[0u];
    addr[1] = Eth_VirtMacInfo[ctrlIdx].macAddress[1u];
    addr[2] = Eth_VirtMacInfo[ctrlIdx].macAddress[2u];
    addr[3] = Eth_VirtMacInfo[ctrlIdx].macAddress[3u];
    addr[4] = Eth_VirtMacInfo[ctrlIdx].macAddress[4u];
    addr[5] = Eth_VirtMacInfo[ctrlIdx].macAddress[5u];
#endif
}

/* ========================================================================== */
/*                  Internal Function Definitions                             */
/* ========================================================================== */
static Std_ReturnType Eth_validateDescRingAndBufferAlignment(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;
    uint32 index;
    uint8 descIdx;

    for(index = 0u; index < Eth_GetRingTotalNum(ctrlIdx); ++index)
    {
        if(((uint32)Eth_GetRingMemBaseAddress(ctrlIdx, index) % ETH_DMA_CACHE_ALIGN_SIZE) != 0u)
        {
            retVal |= E_NOT_OK;
            break;
        }
    }

    for(index = 0u; index < Eth_GetEgressFifoTotalNum(ctrlIdx); ++index)
    {
        if(Eth_GetEgressFifoPacketNum(ctrlIdx, index) > 0u)
        {
            if(((uint32)Eth_GetEgressFifoBufferDataAddress(ctrlIdx, index, 0u) %
                ETH_DMA_CACHE_ALIGN_SIZE) != 0u)
            {
                retVal |= E_NOT_OK;
                break;
            }

            for(descIdx = 0u; descIdx < Eth_GetEgressFifoPacketNum(ctrlIdx, index); ++descIdx)
            {
                if(((uint32)Eth_GetEgressFifoDescAddress(ctrlIdx, index, descIdx) %
                    ETH_DMA_CACHE_ALIGN_SIZE) != 0u)
                {
                    retVal |= E_NOT_OK;
                    break;
                }
            }
        }
    }

    for(index = 0u; index < Eth_GetIngressFifoTotalNum(ctrlIdx); ++index)
    {
        if(Eth_GetIngressFifoPacketNum(ctrlIdx, index) > 0u)
        {
            if(((uint32)Eth_GetIngressFifoBufferDataAddress(ctrlIdx, index, 0u) %
                ETH_DMA_CACHE_ALIGN_SIZE) != 0u)
            {
                retVal |= E_NOT_OK;
                break;
            }

            for(descIdx = 0u; descIdx < Eth_GetIngressFifoPacketNum(ctrlIdx, index); ++descIdx)
            {
                if(((uint32)Eth_GetIngressFifoDescAddress(ctrlIdx, index, descIdx) %
                    ETH_DMA_CACHE_ALIGN_SIZE) != 0u)
                {
                    retVal |= E_NOT_OK;
                    break;
                }
            }
        }
    }

    return retVal;
}

static void Eth_setDemEventStatus(Dem_EventIdType eventId, Dem_EventStatusType eventStatus)
{
    if(eventId != ETH_DEM_NO_EVENT)
    {
        (void)Dem_SetEventStatus(eventId, eventStatus);
    }
}

static void Eth_initTxDesc(uint8 ctrlIdx)
{
    uint8 descIdx;
    uint8 fifoIdx;

    for(fifoIdx = 0u; fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        Eth_Queue_init(Eth_GetEgressFifoQueueAddress(ctrlIdx, fifoIdx));

        for(descIdx = 0u; descIdx < Eth_GetEgressFifoPacketNum(ctrlIdx, fifoIdx); ++descIdx)
        {
            Eth_InitLLDesc(Eth_GetEgressFifoDescAddress(ctrlIdx, fifoIdx, descIdx));
            Eth_SetLLDescCqRing(Eth_GetEgressFifoDescAddress(ctrlIdx, fifoIdx, descIdx),
                Eth_GetRingHwId(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx)));

            Eth_GetEgressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx)->Idx    = descIdx;
            Eth_GetEgressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx)->Length = 0u;
            Eth_GetEgressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx)->FifoIdx = fifoIdx;

            Eth_Queue_add(Eth_GetEgressFifoQueueAddress(ctrlIdx, fifoIdx),
                Eth_GetEgressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx));

            Eth_SetEgressFifoBufferState(ctrlIdx, fifoIdx, descIdx, ETH_BUF_STATE_FREE);
        }
    }
}

static void Eth_initRxDesc(uint8 ctrlIdx)
{
    uint8 descIdx;
    uint8 fifoIdx;

    for(fifoIdx = 0u; fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        Eth_Queue_init(Eth_GetIngressFifoQueueAddress(ctrlIdx, fifoIdx));

        for(descIdx = 0u; descIdx < Eth_GetIngressFifoPacketNum(ctrlIdx, fifoIdx); ++descIdx)
        {
            Eth_InitLLDesc(Eth_GetIngressFifoDescAddress(ctrlIdx, fifoIdx, descIdx));

            Eth_SetLLDescBufferAddressAndLength(Eth_GetIngressFifoDescAddress(ctrlIdx, fifoIdx, descIdx),
                Eth_GetIngressFifoBufferDataAddress(ctrlIdx, fifoIdx, descIdx),
                Eth_GetIngressFifoPacketSize(ctrlIdx, fifoIdx));

            Eth_GetIngressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx)->Idx = descIdx;
            Eth_GetIngressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx)->Length =
                Eth_GetIngressFifoPacketSize(ctrlIdx, fifoIdx);
            Eth_GetIngressFifoDescUserInfoAddress(ctrlIdx, fifoIdx, descIdx)->FifoIdx = fifoIdx;

            if(Eth_DescriptorGetCacheWritebackInvalidateFuncPtr(ctrlIdx))
            {
                Eth_DescriptorGetCacheWritebackInvalidateFuncPtr(ctrlIdx)(
                    (uint8*)Eth_GetIngressFifoDescAddress(ctrlIdx, fifoIdx, descIdx),
                    sizeof(Eth_DescType));
            }

            (void)CpswDma_submitDesc(ctrlIdx,
                Eth_GetIngressFifoFqIdx(ctrlIdx, fifoIdx),
                (uint64)Eth_GetIngressFifoDescAddress(ctrlIdx, fifoIdx, descIdx));
        }
    }
}

static void Eth_retrievePendingTxDesc(uint8 ctrlIdx)
{
    uint8 pendingDescNum;
    uint8 Idx;
    uint8 fifoIdx;
    Eth_DescType *descPtr;
    uint64 descAddr;

    for(fifoIdx = 0u; fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        pendingDescNum = CpswDma_retrieveReadPendingDescNumber(ctrlIdx,
           Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx));

        for(Idx = 0u; Idx < pendingDescNum; Idx++)
        {
            if(E_OK == CpswDma_retrieveDesc(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx), &descAddr))
            {
                descPtr = (Eth_DescType*)descAddr;
                Eth_Queue_add(Eth_GetEgressFifoQueueAddress(ctrlIdx,
                    descPtr->bufferInfo.FifoIdx), &descPtr->bufferInfo);
            }
        }

        pendingDescNum = CpswDma_retrieveWritePendingDescNumber(ctrlIdx,
            Eth_GetEgressFifoFqIdx(ctrlIdx, fifoIdx));

        for(Idx = 0u; Idx < pendingDescNum; Idx++)
        {
            if(E_OK == CpswDma_flushDesc(ctrlIdx, Eth_GetEgressFifoFqIdx(ctrlIdx, fifoIdx), &descAddr))
            {
                descPtr = (Eth_DescType*)descAddr;
                Eth_Queue_add(Eth_GetEgressFifoQueueAddress(ctrlIdx,
                    descPtr->bufferInfo.FifoIdx), &descPtr->bufferInfo);
            }
        }
    }
}

static void Eth_retrievePendingRxDesc(uint8 ctrlIdx)
{
    uint8 pendingDescNum;
    uint8 Idx;
    uint8 fifoIdx;
    Eth_DescType *descPtr;
    uint64 descAddr;

    for(fifoIdx = 0u; fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        pendingDescNum = CpswDma_retrieveReadPendingDescNumber(ctrlIdx,
           Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx));

        for(Idx = 0u; Idx < pendingDescNum; Idx++)
        {
            if(E_OK == CpswDma_retrieveDesc(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx), &descAddr))
            {
                descPtr = (Eth_DescType*)descAddr;
                Eth_Queue_add(Eth_GetIngressFifoQueueAddress(ctrlIdx,
                    descPtr->bufferInfo.FifoIdx), &descPtr->bufferInfo);
            }
        }

        pendingDescNum = CpswDma_retrieveWritePendingDescNumber(ctrlIdx,
            Eth_GetIngressFifoFqIdx(ctrlIdx, fifoIdx));

        for(Idx = 0u; Idx < pendingDescNum; Idx++)
        {
            if(E_OK == CpswDma_flushDesc(ctrlIdx, Eth_GetIngressFifoFqIdx(ctrlIdx, fifoIdx), &descAddr))
            {
                descPtr = (Eth_DescType*)descAddr;
                Eth_Queue_add(Eth_GetIngressFifoQueueAddress(ctrlIdx,
                    descPtr->bufferInfo.FifoIdx), &descPtr->bufferInfo);
            }
        }
    }
}

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || \
     (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))

static uint16 Eth_genPseudoCheckSumIPv4(uint8 *ipPktStart, uint16 ipPktPayLen)
{
    Eth_Ip4Hdr *pIp4Hdr = (Eth_Ip4Hdr *)ipPktStart;
    uint32 sum = ((pIp4Hdr->src_addr & 0XFFFFUL)         +
                 ((pIp4Hdr->src_addr >> 16) & 0XFFFFUL)  +
                 (pIp4Hdr->dst_addr & 0XFFFFUL)          +
                 ((pIp4Hdr->dst_addr >> 16) & 0XFFFFUL)  +
                 (htons((uint16)(pIp4Hdr->protocol)))    +
                 (htons(ipPktPayLen)));

    /* Split the 32-bit sum into two 16-bit num and add them up
     * until the sum is reduced to 16bits */
    while (sum >> 16) {
        sum = (sum & 0XFFFFUL) + (sum >> 16);
    }

    return (uint16)~(sum & 0XFFFFUL);
}

static uint16 Eth_genPseudoCheckSumIPv6(uint8 *ipPktStart, uint16 ipPktPayLen)
{
    Eth_Ip6Hdr *pIp6Hdr = (Eth_Ip6Hdr *)ipPktStart;
    uint32 sum = 0;
    uint32 idx;

    for (idx = 0; idx < 4; idx++)
    {
        sum += ((pIp6Hdr->src_addr[idx] & 0XFFFFUL)         +
                ((pIp6Hdr->src_addr[idx] >> 16) & 0XFFFFUL) +
                (pIp6Hdr->dst_addr[idx] & 0XFFFFUL)         +
                ((pIp6Hdr->dst_addr[idx] >> 16) & 0XFFFFUL));

    }
    sum += ((htons((uint16)(pIp6Hdr->next_hdr))) + (htons(ipPktPayLen)));

    /* Split the 32-bit sum into two 16-bit num and add them up
     * until the sum is reduced to 16bits */
    while (sum >> 16) {
        sum = (sum & 0XFFFFUL) + (sum >> 16);
    }

    return (uint16)~(sum & 0XFFFFUL);
}

static Std_ReturnType Eth_setPseudoCheckSum(Eth_Frame *pEthPkt,
                                            Eth_FrameType frameType,
                                            uint16 *ipPktPayLen,
                                            uint8 *startIdx,
                                            uint8 *resultIdx)
{
    Std_ReturnType retVal = E_OK;
    uint8 *ipPktStart = Eth_getIpPktStart((uint8*)pEthPkt);
    uint16 (*pseudo_chksum)(uint8 *, uint16);
    Eth_UdpHdr *pUdpHdr;
    Eth_TcpHdr *pTcpHdr;
    uint8 ipPktHdrLen;
    uint8 protocol;

    if (ETH_P_IPV6 == frameType)
    {
        ipPktHdrLen = IPV6_HDR_LEN;
        *ipPktPayLen = htons(((Eth_Ip6Hdr *)ipPktStart)->pay_len);
        pseudo_chksum = &Eth_genPseudoCheckSumIPv6;
        protocol = ((Eth_Ip6Hdr *)ipPktStart)->next_hdr;
    }
    else
    {
        ipPktHdrLen = ((((Eth_Ip4Hdr *)ipPktStart)->v_hl & 0x0FU) << 2U);
        *ipPktPayLen = htons(((Eth_Ip4Hdr *)ipPktStart)->len) - ipPktHdrLen;
        pseudo_chksum = &Eth_genPseudoCheckSumIPv4;
        protocol = ((Eth_Ip4Hdr *)ipPktStart)->protocol;
    }

    switch (protocol)
    {
#if (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP)
        case IPPROTO_TCP:
            pTcpHdr = (Eth_TcpHdr *)(ipPktStart + ipPktHdrLen);
            *startIdx = (uint8 *)pTcpHdr - (uint8 *)pEthPkt + 1;
            *resultIdx = (uint8 *)(&(pTcpHdr->checksum)) - (uint8 *)pEthPkt + 1;
            pTcpHdr->checksum = ~(pseudo_chksum(ipPktStart, *ipPktPayLen));
            break;
#endif /* (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) */
#if (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP)
        case IPPROTO_UDP:
            pUdpHdr = (Eth_UdpHdr *)(ipPktStart + ipPktHdrLen);
            *startIdx = (uint8 *)pUdpHdr - (uint8 *)pEthPkt + 1;
            *resultIdx = (uint8 *)(&(pUdpHdr->checksum)) - (uint8 *)pEthPkt + 1;
            pUdpHdr->checksum = ~(pseudo_chksum(ipPktStart, *ipPktPayLen));
            break;
#endif /* (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP) */
        default:
            retVal = E_NOT_OK;
            break;
    }
    return retVal;
}

static void Eth_setCheckSumCtrl(Eth_DescType *llDescPtr, Eth_Frame *frame)
{
    Eth_FrameType frameType = ntohs(frame->hdr.etherType);
    uint16 ipPktPayloadLen = 0U;
    uint8 csumCoverageStartByte = 0U;
    uint8 csumResultByte = 0U;
    Std_ReturnType retVal = E_OK;

    /* For VLAN Tagged packet, get the payload ethertype */
    if (ETH_P_8021Q == frameType)
    {
        frameType = ntohs(((Eth_vlanFrameHdr *)frame)->etherType);
    }

    /* HW Checksum Offload is only supported on IP frames */
    if (ETH_P_IP == frameType || ETH_P_IPV6 == frameType)
    {
        retVal = Eth_setPseudoCheckSum(frame, frameType,
                &ipPktPayloadLen,
                &csumCoverageStartByte,
                &csumResultByte);
        if (E_OK == retVal)
        {
            Eth_SetLLDescCheckSum(llDescPtr,
                    ipPktPayloadLen,
                    csumCoverageStartByte,
                    csumResultByte);
        }
    }
}

static inline uint8 *Eth_getIpPktStart(uint8 *frameBuffer)
{
    Eth_Frame *frame = (Eth_Frame *)frameBuffer;
    const uint32 ipPacketStartOffset =
                 (frame->hdr.etherType == htons(ETH_P_8021Q)) ?
                 (ETH_HEADER_LEN + SIZEOF_VLAN_HDR) : (ETH_HEADER_LEN);

    return &frameBuffer[ipPacketStartOffset];
}

#endif /* ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || \
           (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP)) */

static inline void Eth_timeStampConvert(uint64 *timeStampPtr, Eth_TimeStampType *ethTimeStampPtr)
{
    ethTimeStampPtr->nanoseconds = (uint32)((*timeStampPtr % ETH_SEC_TO_NS));
    ethTimeStampPtr->seconds     = (uint32)((*timeStampPtr /
        (uint64)ETH_SEC_TO_NS) % ((uint64)ETH_UINT32_MAX + 1u));
    ethTimeStampPtr->secondsHi   = (uint16)((*timeStampPtr /
        (uint64)ETH_SEC_TO_NS) / ((uint64)ETH_UINT32_MAX + 1u));
}

static inline void Eth_getFifoFromBufferIdx(Eth_BufIdxType bufferIdx, uint8 *fifoIdx, uint8 *fifoBuffIdx)
{
    *fifoIdx =  bufferIdx / ETH_MAX_BUFFER_NUM_IN_FIFO;
    *fifoBuffIdx = bufferIdx % ETH_MAX_BUFFER_NUM_IN_FIFO;
}

static inline Eth_BufIdxType Eth_getBufferIdxFromFifo(uint8 fifoIdx, uint16 fifoBuffIdx)
{
    return (fifoIdx * ETH_MAX_BUFFER_NUM_IN_FIFO + fifoBuffIdx);
}

static inline uint8 Eth_GetLeftBitShiftValue(uint8 bitNum)
{
    return (1U << bitNum);
}

