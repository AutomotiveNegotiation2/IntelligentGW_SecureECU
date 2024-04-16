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
 *  \file     Eth_Types.h
 *
 *  \brief    This file contains Eth type declarations.
 */

/**
 *  \ingroup MCAL_ETH_API
 *  @{
 */

#ifndef ETH_TYPES_H_
#define ETH_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \name Eth Controller names
 *
 *  Symbolic names for the EthControllerId.
 *  @{
 */
/** \brief MAC address length in bytes */
#define ETH_MAC_ADDR_LEN                ((uint32) 6U)

/** \brief Total octets in header */
#define ETH_HEADER_LEN                  ((uint16) 14U)

/** \brief Total prioroty queue number */
#define ETH_PRIORITY_QUEUE_NUM          (8U)

/** \brief Invalid stats value (stat not available) */
#define ETH_STATCNT_INVALID             (0xFFFFFFFFU)

/** \brief Invalid Ring Id value */
#define ETH_INVALID_RING_ID             (0xFFFFU)

/** \brief Invalid Event Id value */
#define ETH_INVALID_EVENT_ID            (0xFFFFU)

/** \brief Invalid channel Id */
#define ETH_INVALID_CHAN_ID             (0xFFFFU)

/** \brief Invalid Flow Id */
#define ETH_INVALID_FLOW_ID             (0xFFFFU)

/** \brief Invalid IRQ value */
#define ETH_INVALID_IRQ_ID              (0xFFFFU)

/** \brief Eth invalid DEM event ID  */
#define ETH_DEM_NO_EVENT                (0xFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef enum
{
    ETH_PORT_HOST_PORT      = 0x00U,
    /**< Host port */
    ETH_MAC_PORT_FIRST      = 0x01U,
    /**< First Eth port */
    ETH_PORT_MAC_PORT_1     = 0x01U,
    /**< MAC port 0 */
    ETH_PORT_MAC_PORT_2     = 0x02U,
    /**< MAC port 1 */
    ETH_PORT_MAC_PORT_3    = 0x03U,
    /**< MAC port 2 */
    ETH_PORT_MAC_PORT_4   = 0x04U,
    /**< MAC port 3 */
    ETH_PORT_MAC_PORT_5     = 0x05U,
    /**< MAC port 4 */
    ETH_PORT_MAC_PORT_6     = 0x06U,
    /**< MAC port 5 */
    ETH_PORT_MAC_PORT_7     = 0x07U,
    /**< MAC port 6 */
    ETH_PORT_MAC_PORT_8     = 0x08U,
    /**< MAC port 7 */
    ETH_PORT_MAC_PORT_LAST     = ETH_PORT_MAC_PORT_8,
    /**< Enum indicating last mac port  */
} Eth_PortType;

/** Number of CPSW Type supported */
#define ETH_PORT_COUNT                              (ETH_PORT_MAC_PORT_LAST + 1)


/**
 *  \brief  Type/Speed/Duplex connection type
 *
 *  Ethernet connections based on the type (MII, RMII, RGMII), speed
 *  (10Mbps, 100Mbps, 1Gbps) and duplexity (half, full).
 */
typedef enum
{
    ETH_MAC_CONN_TYPE_RMII_10               = 0x01U,
    /**< MAC connection type for 10Mbps RMII mode */
    ETH_MAC_CONN_TYPE_RMII_100              = 0x02U,
    /**< MAC connection type for 100Mbps RMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF  = 0x03U,
    /**< MAC connection type for forced half-duplex 100Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL  = 0x04U,
    /**< MAC connection type for forced full-duplex 100Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_1000_FULL = 0x05U,
    /**< MAC connection type for forced full-duplex 1000Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND   = 0x06U,
    /**< MAC connection type for RGMII inband detection mode
     *   (speed determined based on received RGMII Rx clock) */
} Eth_MacConnectionType;


/**
 *  \brief Ethernet buffer state
 *
 *  The state of the Ethernet buffer.
 */
typedef enum
{
    ETH_BUF_STATE_FREE   = 0U,
    /**< Buffer is free for allocation */
    ETH_BUF_STATE_IN_USE = 1U,
    /**< Buffer is in use */
    ETH_BUF_STATE_QUEUED = 2U,
    /**< Buffer has been queued for transmit */
    ETH_BUF_STATE_CONFIRMATION = 3U,
    /**< Buffer has mark that need to confirmation for upper layer */
} Eth_BufStateType;

/**
 *  \brief Ethernet transmit proccess status
 */
typedef enum
{
    ETH_TRANSMITED_BUFFER_DONE = 0U,
    /**< Eth transmited buffer has done */
    ETH_TRANSMITED_BUFFER_PENDING = 1U
    /**< Eth transmited buffer are pending  */
} Eth_TxStatusType;

/**
 *  \brief MII Access State
 *
 *  State of the current MII read/write operation.
 */
typedef struct
{
    boolean isActive;
    /**< MII operation is in progress */
    boolean isRead;
    /**< Read or write operation */
    uint8 ctrlIdx;
    /**< Ethernet controller index */
    uint8 trcvIdx;
    /**< Ethernet transceiver index (PHY address) */
    uint8 regIdx;
    /**< PHY register address */
} Eth_MiiAccessType;

/**
 *  \brief Controller errors
 *
 *  Counters of different types of controller errors.
 */
typedef struct
{
    uint32 rxCRC;
    /**< RX packets with CRC errors */
    uint32 rxOverrun;
    /**< Receive overruns */
    uint32 rxUndersized;
    /**< RX packets that were undersized */
    uint32 rxOversized;
    /**< RX packets that were oversized */
    uint32 rxAlignCode;
    /**< RX packets with align/code errors */
    uint32 txSingleColl;
    /**< TX packets that experienced a single collision */
    uint32 txMultiColl;
    /**< TX packets that experienced multiple colisions */
    uint32 txLateColl;
    /**< TX packets that experienced a late collision */
} Eth_CtrlErrorsType;

/**
 *  \brief Cache write-back invalidate function
 *
 *  Pointer to a function that performs the cache write-back invalidate
 *  operation.  This function is to be called on TX buffers before they
 *  are given to the Ethernet controller hardware.
 */
typedef void (*Eth_CacheWbInv)(uint8 *BufPtr,
                               uint16 LenByte);

/**
 *  \brief Cache write-back function
 *
 *  Pointer to a function that performs the cache write-back operation.
 *  This function is to be called on TX buffers before they are given to
 *  the Ethernet controller hardware.
 */
typedef void (*Eth_CacheWb)(uint8 *BufPtr,
                            uint16 LenByte);

/**
 *  \brief Cache invalidate function
 *
 *  Pointer to a function that performs the cache invalidate operation.
 *  This function is to be called on RX buffers after they have been
 *  retrieved from the Ethernet controller hardware.
 */
typedef void (*Eth_CacheInv)(uint8 *BufPtr,
                             uint16 LenByte);

/**
 *  \brief Application callback to indicate Rpc dispatch command completion
 *
 *  Pointer to a function that is invoked to indicate completion of
 *  RPC dispatch call.
 *  The RPC command is identified by the sid
 */
typedef void (*Eth_RpcCmdComplete)(uint8 CtrlIdx,
                                   uint8 sid,
                                   Std_ReturnType status);


/**
 *  \brief Application callback to indicate Ethernet firmware registered with
 *         the Eth RPC client
 */
typedef void (*Eth_RpcFwRegistered)(uint8 CtrlIdx);

/**
 *  \brief Enet Cpsw Type identifier
 *
 *  Enet CPSW Type enumeration.
 */
/*
 * Design:
 * Requirements:
 */
typedef enum
{
    ETH_ENETTYPE_CPSW2G     = 0x00U,
    /**< CPSW 2-port switch with one host port and 1 external port */
    ETH_ENETTYPE_CPSW9G     = 0x01U,
    /**< CPSW 9-port switch with one host port and 8 external port */
    ETH_ENETTYPE_CPSW5G     = 0x02U,
    /**< CPSW 5-port switch with one host port and 4 external port */
    ETH_ENETTYPE_CPSW3G     = 0x03U,
    /**< CPSW 3-port switch with one host port and 4 external port */
    ETH_ENETTYPE_CPSWLAST,
    /**< Enum used to identify the last supported CPSW Type. Used internally */
} Eth_EnetType;

/**
 *  \brief Data Structure listing list of ports.
 *
 *  Variables of this type are used identify port membership for things like
 *  multicast address membership
 */
typedef struct Eth_PortListType_s
{
    uint32  numPorts;
    /**< Number of MAC ports in the port list */
    Eth_PortType ports[ETH_PORT_COUNT];
    /**< MAC ports included in the port list */
} Eth_PortListType;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* ETH_TYPES_H_ */

/* @} */
