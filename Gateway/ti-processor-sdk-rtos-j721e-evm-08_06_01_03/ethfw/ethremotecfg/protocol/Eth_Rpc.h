/*
 *
 * Copyright (c) 2019 Texas Instruments Incorporated
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

#ifndef ETH_RPC_H_
#define ETH_RPC_H_

#include <stdint.h>

/*! Ethernet Switch Remote Device API version major version */
#define ETH_RPC_API_VERSION_MAJOR                         (0)
/*! Ethernet Switch Remote Device API version minor version */
#define ETH_RPC_API_VERSION_MINOR                         (2)
/*! Ethernet Switch Remote Device API version minor revision */
#define ETH_RPC_API_VERSION_REVISION                      (0)

/*! Ethernet Switch Remote Device rpmsg service name  */
#define ETH_RPC_REMOTE_SERVICE  "ti.autosar.ethdevice"

/*! Ethernet Switch Remote Device max msg size  */
#define ETH_RPC_MSG_SIZE           (496U)

/*!
 * \brief Ethernet RPC commands
 */
typedef enum 
{
    ETH_RPC_CMD_TYPE_FWINFO_RES                     = 0x00,
    ETH_RPC_CMD_TYPE_ATTACH_EXT_REQ                 = 0x01,
    ETH_RPC_CMD_TYPE_ATTACH_EXT_RES                 = 0x02,
    ETH_RPC_CMD_TYPE_DETACH_REQ                     = 0x03,
    ETH_RPC_CMD_TYPE_DETACH_RES                     = 0x04,
    ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_REQ       = 0x05,
    ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_RES       = 0x06,
    ETH_RPC_CMD_TYPE_REGISTER_MAC_REQ               = 0x07,
    ETH_RPC_CMD_TYPE_REGISTER_MAC_RES               = 0x08,
    ETH_RPC_CMD_TYPE_UNREGISTER_MAC_REQ             = 0x09,
    ETH_RPC_CMD_TYPE_UNREGISTER_MAC_RES             = 0x0A,
    ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_REQ     = 0x0B,
    ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_RES     = 0x0C,
    ETH_RPC_CMD_TYPE_IOCTL_REQ                      = 0x0D,
    ETH_RPC_CMD_TYPE_IOCTL_RES                      = 0x0E,
    ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_REQ          = 0x0F,
    ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_RES          = 0x10,
    ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_REQ        = 0x11,
    ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_RES        = 0x12,
    ETH_RPC_CMD_TYPE_C2S_NOTIFY                     = 0x13,
    ETH_RPC_CMD_TYPE_S2C_NOTIFY                     = 0x14,
    ETH_RPC_CMD_TYPE_SET_PROMISC_MODE_REQ           = 0x15,
    ETH_RPC_CMD_TYPE_SET_PROMISC_MODE_RES           = 0x16,
    ETH_RPC_CMD_TYPE_FILTER_ADD_MAC_REQ             = 0x17,
    ETH_RPC_CMD_TYPE_FILTER_ADD_MAC_RES             = 0x18,
    ETH_RPC_CMD_TYPE_FILTER_DEL_MAC_REQ             = 0x19,
    ETH_RPC_CMD_TYPE_FILTER_DEL_MAC_RES             = 0x1A,
    ETH_RPC_CMD_TYPE_LAST                           = ETH_RPC_CMD_TYPE_FILTER_DEL_MAC_RES,
} Eth_RpcCmdType;

#define ETH_RPC_CMD_TYPE_COUNT                    (ETH_RPC_CMD_TYPE_LAST + 1)

/*!
 * \brief CPSW Type supported by Ethernet Switch Remote Device
 */
typedef enum 
{
    /*! Ethernet Remote Device for MCU domain CPSW type (e.g. ENET_CPSW_2G in J721E and J7200) */
    ETH_RPC_CPSWTYPE_MCU                          = 0x00,
    /*! Ethernet Remote Device for Main domain CPSW type (e.g. ENET_CPSW_5G in J7200, ENET_CPSW_9G in J721E) */
    ETH_RPC_CPSWTYPE_MAIN                         = 0x01,
    /*! Max Ethernet Remote Device CPSW type. For internal use */
    ETH_RPC_CPSWTYPE_LAST                         = (ETH_RPC_CPSWTYPE_MAIN)
} Eth_RpcCpswType;

#define ETH_RPC_CPSWTYPE_COUNT                    (ETH_RPC_CPSWTYPE_LAST + 1)


/*!
 * \brief Etheret Remote Device Client to Server notify types
 */
typedef enum 
{
    /*! Client to server notify command to dump CPSW stats on master core UART console */
    ETH_RPC_CLIENTNOTIFY_DUMPSTATS,
    /*! Client to server notify command that is app specific.
     *  Application on server will receive callback and can
     *  typecast the notify info to handle the notify 
     */
    ETH_RPC_CLIENTNOTIFY_CUSTOM,
    /*! Client to server notify command max. For internal use */
    ETH_RPC_CLIENTNOTIFY_LAST                  = (ETH_RPC_CLIENTNOTIFY_CUSTOM)

} Eth_RpcClientNotifyType;

#define ETH_RPC_CLIENTNOTIFY_COUNT               (ETH_RPC_CLIENTNOTIFY_LAST + 1)

/*!
 * \brief Etheret Remote Device Client to Server notify types
 */
typedef enum 
{
    /*! Client to server notify command to dump CPSW stats on master core UART console */
    ETH_RPC_SERVERNOTIFY_UNKNOWNCMD,
    ETH_RPC_SERVERNOTIFY_LAST                  = (ETH_RPC_SERVERNOTIFY_UNKNOWNCMD)

} Eth_RpcServerNotifyType;

#define ETH_RPC_SERVERNOTIFY_COUNT               (ETH_RPC_SERVERNOTIFY_LAST + 1)


/*! Ethernet Switch Remote Device CMD response code : Success */
#define ETH_RPC_CMDSTATUS_OK       (0)
/*! Ethernet Switch Remote Device CMD response code : Try again 
 *
 *  Reponse indicates temporary failure of cmd and client can retry
 *  the cmd again
 */
#define ETH_RPC_CMDSTATUS_EAGAIN   (-1)
/*! Ethernet Switch Remote Device CMD response code : Failure */
#define ETH_RPC_CMDSTATUS_EFAIL    (-2)
/*! Ethernet Switch Remote Device CMD response code : Failure to insufficient permission 
 *
 *  Reponse indicates the command failed because remote core does not have sufficient privileges
 */
#define ETH_RPC_CMDSTATUS_EACCESS  (-3)




/*!
 * Maximum length of ethernet switch remote device message data in rpmsg_kdrv_ethswitch_ping_request
 */
#define ETH_RPC_MESSAGE_DATA_LEN    (384)

/*!
 * Number of priorities supported by CPSW
 */
#define ETH_RPC_CPSW_PRIORITY_NUM   (8)

/*!
 * Maximum length of input arguments for RPMSG_KDRV_TP_ETHSWITCH_IOCTL
 */
#define ETH_RPC_IOCTL_INARGS_LEN    (384)

/*!
 * Maximum length of output arguments for RPMSG_KDRV_TP_ETHSWITCH_IOCTL
 */
#define ETH_RPC_IOCTL_OUTARGS_LEN   (384)

/*!
 * MAC Address length in octets
 */
#define ETH_RPC_MACADDRLEN          (6)

/*!
 * IPV4 Address length in octets
 */
#define ETH_RPC_IPV4ADDRLEN         (4)

/**
 *  \name Ethernet Switch Remote Device CPSW IP Supported Feature Bitmask
 *
 *  @{
 */
/*! Feature: Tx Checksum Offload Enabled  */
#define ETH_RPC_FEATURE_TXCSUM      (1 << 0)

/* Note: Feature bit 1 is intentionally not used, Linux already using it */

/*! Feature: MAC-only mode enabled */
#define ETH_RPC_FEATURE_MAC_ONLY    (1 << 2)
/*  @} */

/*!
 * Number of octets in year
 */
#define ETH_RPC_FWDATE_YEARLEN     (4)

/*!
 * Number of octets in month
 */
#define ETH_RPC_FWDATE_MONTHLEN    (3)

/*!
 * Number of octets in date
 */
#define ETH_RPC_FWDATE_DATELEN     (2)

/*!
 * GIT Commit SHA length in octets
 */
#define ETH_RPC_FW_COMMITSHALEN    (8)

/*!
 * Common message header for all ethernet switch remote  device cmds
 */
typedef struct Eth_RpcMessageHeader_s
{
    /*! Message Type enum: Eth_RpcCmdType */
    uint8_t  messageId;
    /*! Message length */
    uint32_t messageLen;
} Eth_RpcMessageHeader;

/*!
 * Common structure used for all ethernet switch remote device command request msgs except attach
 */
typedef struct Eth_RpcCommonRequestInfo_s
{
    /*! opaque unique handle returned by ATTACH  */
    uint64_t id;
    /*! Core specific key returned by attach */
    uint32_t coreKey;
} Eth_RpcCommonRequestInfo;

/*!
 * Common header used for all ethernet switch remote device command response msgs
 */
typedef struct Eth_RpcCommonResponseInfo_s
{
    /*! Status of request. Refer Ethernet Switch Remote Device CMD response code */
    int32_t status;
} Eth_RpcCommonResponseInfo;


/*!
 * ETH_RPC_CMD_TYPE_ATTACH_EXT_REQ cmd client request
 */
typedef struct Eth_RpcAttachExtendedRequest_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! CPSW TYPE  enum: Eth_RpcCpswType  */
    uint8_t enetType;
} Eth_RpcAttachExtendedRequest;

/*!
 * ETH_RPC_CMD_TYPE_ATTACH_EXT_RES cmd server response
 */
typedef struct Eth_RpcAttachExtendedResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
    /*! unique handle used by all further CMDs  */
    uint64_t id;
    /*! Core specific key to indicate attached core */
    uint32_t coreKey;
    /*! MTU of rx packet */
    uint32_t rxMtu;
    /*! MTU of tx packet per priority */
    uint32_t txMtu[ETH_RPC_CPSW_PRIORITY_NUM];
    /*! Feature bitmask based on defines RPMSG_KDRV_TP_ETHSWITCH_FEATURE_xxx */
    uint32_t features;
    /* Rx flow index base */
    uint32_t allocFlowIdxBase;
    /*! Allocated flow index offset */
    uint32_t allocFlowIdxOffset;
    /*! Tx PSIL Peer destination thread id which should be paired with the
     * Tx UDMA channel
     */
    uint32_t txCpswPsilDstId;
    /*! Mac address allocated */
    uint8_t macAddress[ETH_RPC_MACADDRLEN];
    /*! 1-relative MAC-only port number. 0 for non MAC-only ports */
    uint32_t macOnlyPort;
} Eth_RpcAttachExtendedResponse;

/*!
 * \brief Register Rx Default flow CMD request params
 */
typedef struct Eth_RpcRegisterRxDefaultRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! Default flow will be associated with the given index */
    uint32_t    defaultFlowIdx;
} Eth_RpcRegisterRxDefaultRequest;

/*!
 * \brief Register Rx Default flow CMD response params
 */
typedef struct Eth_RpcRegisterRxDefaultResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcRegisterRxDefaultResponse;

/*!
 * \brief Register MAC address CMD request params
 */
typedef struct Eth_RpcRegisterMacRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! mac address to be associated with flow */
    uint8_t macAddress[ETH_RPC_MACADDRLEN];
    /*! Flow's index associated with the mac address to be registered in ALE */
    uint32_t flowIdx;
} Eth_RpcRegisterMacRequest;

/*!
 * \brief Register MAC address CMD response params
 */
typedef struct Eth_RpcRegisterMacResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcRegisterMacResponse;


/*!
 * \brief UnRegister MAC address CMD request params
 */
typedef struct Eth_RpcUnregisterMacRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! mac address to be unregistered from the rx flow  */
    uint8_t macAddress[ETH_RPC_MACADDRLEN];
    /*! rx flow index from which the mac_address association will be removed  */
    uint32_t flowIdx;
} Eth_RpcUnregisterMacRequest;

/*!
 * \brief UnRegister MAC address CMD response params
 */
typedef struct Eth_RpcUnregisterMacResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcUnregisterMacResponse;


/*!
 * \brief Detach CMD request params
 */
typedef struct Eth_RpcDetachRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
}  Eth_RpcDetachRequest;

/*!
 * \brief Detach CMD response params
 */
typedef struct Eth_RpcDetachResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
}  Eth_RpcDetachResponse;


/*!
 * \brief Register IPv4:MAC Address mapping CMD request params
 */
typedef struct Eth_RpcIpv4RegisterMacRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;

    /*! Mac address associated with the IP address which should be added to
     *  the ARP table
     */
    uint8_t macAddress[ETH_RPC_MACADDRLEN];
    /*! IPv4 address  */
    uint8_t ipv4Addr[ETH_RPC_IPV4ADDRLEN];
}  Eth_RpcIpv4RegisterMacRequest;

/*!
 * \brief Register IPv4:MAC Address mapping CMD response params
 */
typedef struct Eth_RpcIpv4RegisterMacResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
}  Eth_RpcIpv4RegisterMacResponse;

/*!
 * \brief Unregister IPv4:MAC Address mapping CMD request params
 */
typedef struct Eth_RpcIpv4UnregisterMacRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! IPv4 address  */
    uint8_t ipv4Addr[ETH_RPC_IPV4ADDRLEN];
}  Eth_RpcIpv4UnregisterMacRequest;

/*!
 * \brief Unregister IPv4:MAC Address mapping CMD response params
 */
typedef struct Eth_RpcIpv4UnregisterMacResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
}  Eth_RpcIpv4UnregisterMacResponse;

/*!
 * \brief Unregister Default Flow CMD request params
 */
typedef struct Eth_RpcUnregisterRxDefaultRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! Default flow index to be unregistered */
    uint32_t defaultFlowIdx;
} Eth_RpcUnregisterRxDefaultRequest;

/*!
 * \brief Unregister Default Flow CMD response params
 */
typedef struct Eth_RpcUnregisterRxDefaultResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcUnregisterRxDefaultResponse;


/*!
 * \brief Firmware version info returned by remote device attach to the ethernet switch device
 */
typedef struct Eth_RpcFirmwareVersionInfo_s
{
    /*! Remote Ethernet Switch Device API Major version number */
    uint32_t major;
    /*! Remote Ethernet Switch Device API Minor version number */
    uint32_t minor;
    /*! Remote Ethernet Switch Device API Revision version number */
    uint32_t rev;
    /*! Remote Ethernet Switch Device Firmware Build year : char string in the form YYYY eg: 2019 */
    char year[ETH_RPC_FWDATE_YEARLEN];
    /*! Remote Ethernet Switch Device Firmware Build month : char string in the form MON eg: Dec */
    char month[ETH_RPC_FWDATE_MONTHLEN];
    /*! Remote Ethernet Switch Device Firmware Build month : char string in the form DD eg: 12 */
    char date[ETH_RPC_FWDATE_DATELEN];
    /*! GIT commit SHA of the firmware: char string in the form fd52c34f */
    char commitHash[ETH_RPC_FW_COMMITSHALEN];
} Eth_RpcFirmwareVersionInfo;

/*!
 * \brief Ethernet Switch Remote Device Data
 *
 * The remote device framework will return the below device data to the remote
 * client when it attaches to the remote ethernet switch device
 */
typedef struct Eth_RpcDeviceData_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Ethernet Switch Remote Device Firmware version info */
    Eth_RpcFirmwareVersionInfo fwVer;
    /*! Flag indicating permission enabled for each
     * enum rpmsg_kdrv_ethswitch_message_type command for the connecting
     * client
     */
    uint32_t permissionFlags;
    /*! Flag indicating if UART is connected: 1 indicates UART connected , 0 indicates UART not connected  */
    uint32_t uartConnected;
    /*! UART ID used by firmware for log prints */
    uint32_t uartId;
} Eth_RpcDeviceData;

/*!
 * \brief Ethernet Switch Remote Device Server to Client Notify
 *
 * Remote Device Framework notify messages are class of messages that 
 * are one directional. The receiver does not respond with response msg or
 * ack.
 * Notify msgs are typically used to notify events
 */
typedef struct Eth_RpcS2CNotify_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Notify data.Presently no S2C notify are supported .
     * API will be updated to support S2C notify events such as 
     * PHY link down and this API param is expected to change 
     */
    /*! Notify Id. Of type enum rpmsg_kdrv_ethswitch_client_notify_type */
    uint8_t notifyid;
    /*! Filled length of notify info */
    uint32_t notifyInfoLen;
    /*! Notify Message data */
    uint64_t notifyInfo[(ETH_RPC_MESSAGE_DATA_LEN / sizeof(uint64_t))];
} Eth_RpcS2CNotify;

/*!
 * \brief Ethernet Switch Remote Device Client to Server Notify
 *
 * Remote Device Framework notify messages are class of messages that 
 * are one directional. The receiver does not respond with response msg or
 * ack.
 * Notify msgs are typically used to notify events
 */
typedef struct Eth_RpcC2SNotify_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! Notify Id. Of type enum rpmsg_kdrv_ethswitch_client_notify_type */
    uint8_t notifyid;
    /*! Filled length of notify info */
    uint32_t notifyInfoLen;
    /*! Notify Message data */
    uint64_t notifyInfo[(ETH_RPC_MESSAGE_DATA_LEN / sizeof(uint64_t))];
} Eth_RpcC2SNotify;

/*!
 * \brief IOCTL CMD request params
 */
typedef struct Eth_RpcIoctlRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! CPSW IOCTL CMD id. Refer CPSW LLD documentation for list of CPSW LLD IOCTLs */
    uint32_t    cmd;
    /*! CPSW IOCTL CMD input arguments length */
    uint32_t    inargsLen;
    /*! CPSW IOCTL CMD input arguments .Byte array is typecast to the inArgs structure associated with the IOCTL */
    uint64_t     inargs[(ETH_RPC_IOCTL_INARGS_LEN / sizeof(uint64_t))];
    /*! CPSW IOCTL CMD output arguments length */
    uint32_t    outargsLen;
} Eth_RpcIoctlRequest;

/*!
 * \brief IOCTL CMD response params
 */
typedef struct Eth_RpcIoctlResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
    /*! CPSW IOCTL CMD id. Refer CPSW LLD documentation for list of CPSW LLD IOCTLs */
    uint32_t    cmd;
    /*! CPSW IOCTL CMD output arguments length */
    uint32_t    outargsLen;
    /*! CPSW IOCTL CMD output arguments .Byte array is typecast to the outArgs structure associated with the IOCTL */
    uint64_t     outargs[(ETH_RPC_IOCTL_OUTARGS_LEN / sizeof(uint64_t))];
} Eth_RpcIoctlResponse;

/*!
 * \brief Set promiscuous mode CMD request params
 */
typedef struct Eth_RpcSetPromiscModeRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! Promiscuous mode: enable or disable */
    uint32_t enable;
} Eth_RpcSetPromiscModeRequest;

/*!
 * \brief Set promiscuous CMD response params
 */
typedef struct Eth_RpcSetPromiscModeResponse_s
{
    /*! common message header */
    Eth_RpcMessageHeader header;
    /*! common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcSetPromiscModeResponse;

/*!
 * \brief Add multicast MAC address to receive filter CMD request params
 */
typedef struct Eth_RpcFilterAddMacRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! Multicast MAC address to be added */
    uint8_t macAddress[ETH_RPC_MACADDRLEN];
    /*! VLAN id */
    uint16_t vlanId;
    /*! RX flow index from which the mac_address association will be added */
    uint32_t flowIdx;
} Eth_RpcFilterAddMacRequest;

/*!
 * \brief Add multicast MAC address to receive filter CMD response params
 */
typedef struct Eth_RpcFilterAddMacResponse_s
{
    /*! Common message header */
    Eth_RpcMessageHeader header;
    /*! Common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcFilterAddMacResponse;

/*!
 * \brief Delete multicast MAC address from receive filter CMD request params
 */
typedef struct Eth_RpcFilterDelMacRequest_s
{
    /*! Common CMD header */
    Eth_RpcMessageHeader header;
    /*! Common info associated with all CMDs other than ATTACH */
    Eth_RpcCommonRequestInfo info;
    /*! Multicast MAC address to be deleted */
    uint8_t macAddress[ETH_RPC_MACADDRLEN];
    /*! VLAN id */
    uint16_t vlanId;
    /*! RX flow index from which the mac_address association will be deleted */
    uint32_t flowIdx;
} Eth_RpcFilterDelMacRequest;

/*!
 * \brief Delete multicast MAC address from receive filter CMD response params
 */
typedef struct Eth_RpcFilterDelMacResponse_s
{
    /*! Common message header */
    Eth_RpcMessageHeader header;
    /*! Common response info */
    Eth_RpcCommonResponseInfo info;
} Eth_RpcFilterDelMacResponse;

#endif
