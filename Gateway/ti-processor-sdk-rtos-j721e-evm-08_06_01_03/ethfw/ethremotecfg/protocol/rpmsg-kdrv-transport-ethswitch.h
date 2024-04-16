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

#ifndef __RPMSG_KDRV_TRANSPORT_ETHSWITCH_H__
#define __RPMSG_KDRV_TRANSPORT_ETHSWITCH_H__

#include <protocol/rpmsg-kdrv-transport-common.h>

/**
 * \defgroup ETHSWITCH_REMOTE_DEVICE_API Ethernet Switch Remote Device
 *
 * The remote device framework enables access to devices from remote cores
 * One core is designated as master core with exclusive register access.
 * Remote cores may configure the device using the remote device framework
 *
 * The ethernet switch device (CPSW9G) is available as a remote device 
 * This module defines the Ethernet Switch Remote Device interface
 *
 *  @{
 */
/* @} */
/*!
 * \addtogroup ETHSWITCH_REMOTE_DEVICE_API
 * @{
 */

 
/**
 *  \name Ethernet Switch Remote Device Version Info
 *
 *  API version info for the ethernet switch remote device
 *  Any remote core client should check API version is compatible with this
 *  API version
 *  @{
 */
/*! Ethernet Switch Remote Device API version major version */
#define RPMSG_KDRV_TP_ETHSWITCH_VERSION_MAJOR             (0)
/*! Ethernet Switch Remote Device API version minor version */
#define RPMSG_KDRV_TP_ETHSWITCH_VERSION_MINOR             (2)
/*! Ethernet Switch Remote Device API version minor revision */
#define RPMSG_KDRV_TP_ETHSWITCH_VERSION_REVISION          (0)
/*  @} */

/*!
 * \brief Ethernet Switch Remote Device commands
 *
 * The remote device supports a set of commands. Associated with each
 * CMD is a request_params structure that the remote device client populates
 * The master core which  hosts the remote device server processes the command
 * and responds with response params structure associated with the command
 * 
 * Notify CMDs are one way messages and do not have a response param structure
 * associated with them
 */
enum rpmsg_kdrv_ethswitch_message_type
{
    /*!
     * \brief CMD to attach to the ethernet switch remote device.
     *
     *  All remote core clients should first attach before issuing any further
     *  commands to the ethernet switch device
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_attach_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_attach_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_ATTACH                  = 0x00,
    /*!
     * \brief CMD to attach to the ethernet switch remote device which returns extended attach info.
     *
     *  All remote core clients should first attach before issuing any further
     *  commands to the ethernet switch device
     *  Remote core clients that require only a single data path can use a 
     *  single RPMSG_KDRV_TP_ETHSWITCH_ATTACH_EXT command which will return
     *  all the params required to establish data path including dst mac,
     *  rx flow, tx channel. This is typically used by linux virtual mac netdev
     *  as there are no client instances on the core running linux virtual mac netdev
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_attach_extended_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_attach_extended_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_ATTACH_EXT              = 0x01,
    /*!
     * \brief CMD to allocate Tx channel
     *
     *  The remote core should use the allocated TX channel as Tx DMA channel
     *  CPSW PSIL destination thread id when configuring the Tx DMA channel
     *  
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_alloc_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_alloc_tx_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_ALLOC_TX                = 0x02,
    /*!
     * \brief CMD to allocate Rx flow
     *
     *  The remote core should use the allocated Rx flow id to configure the
     *  Udma Rx flow to establish Rx data flow path on remote core
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_alloc_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_alloc_rx_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_ALLOC_RX                = 0x03,
    /*!
     * \brief CMD to register default flow from remote core
     *
     *  Commands allows remote core to receive traffic directed to the default
     *  flow. Default flow is the flow to which CPSW will direct traffic if 
     *  it does not match any classifier which has a thread id configured.
     *  Default flow registration is possible only if no core including master
     *  core has registered for the default flow. 
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_register_rx_default_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_register_rx_default_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_REGISTER_DEFAULTFLOW    = 0x04,
    /*!
     * \brief CMD to allocate a DST MAC addr to the remote core client
     *
     *  Commands allows remote core client to allocate a host port destination
     *  mac address which it can register using RPMSG_KDRV_TP_ETHSWITCH_REGISTER_MAC
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_alloc_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_alloc_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_ALLOC_MAC               = 0x05,
    /*!
     * \brief CMD to register a DST MAC addr by the remote core client to a specific rx flow id
     *
     *  Commands allows remote core client to register all traffic received on
     *  the host port with a specific destination mac address to be routed to 
     *  the given rx flow id 
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_register_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_register_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_REGISTER_MAC            = 0x06,
    /*!
     * \brief CMD to unregister a DST MAC addr by the remote core client 
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_REGISTER_MAC and
     *  disables the routing of traffic with given destination mac addr to a 
     *  specific rx flow id.
     *  Once unregistered further traffic with the given destination mac addr
     *  will be routed to default rx flow
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_unregister_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_unregister_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_MAC          = 0x07,
    /*!
     * \brief CMD to unregister default flow routing to the remote core 
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_REGISTER_DEFAULTFLOW and
     *  disables the routing of default flow traffic to the given rx flow id
     *  Once default flow is unregistered all traffic destined to default flow 
     *  will be routed to reserved flow and will be dropped 
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_unregister_rx_default_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_unregister_rx_default_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_DEFAULTFLOW  = 0x08,
    /*!
     * \brief CMD to free previously allocated mac addr
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_ALLOC_MAC and
     *  frees the previously allocated MAC addr
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_free_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_free_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_FREE_MAC                = 0x09,
    /*!
     * \brief CMD to free previously allocated tx channel CPSW  PSIL destination thread
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_ALLOC_TX and
     *  frees the previously allocated TX Channels PSIL destination thread
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_free_tx_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_free_tx_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_FREE_TX                 = 0x0A,
    /*!
     * \brief CMD to free previously allocated rx flow id
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_ALLOC_RX and
     *  frees the previously allocated Rx flow id
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_free_rx_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_free_rx_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_FREE_RX                 = 0x0B,
    /*!
     * \brief CMD to detach remote core from the ethernet switch device
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_ATTACH/RPMSG_KDRV_TP_ETHSWITCH_ATTACH_EXT
     *  All resources allocated to the remote core like Tx Ch, Rx Flow, Mac Addr are freed by the master core
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_detach_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_detach_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_DETACH                  = 0x0C,
    /*!
     * \brief CMD to invoke CPSW LLD IOCTL from remote core
     *
     *  Command allows invocation of any CPSW LLD IOCTL from the remote core
     *  The master core will check if the remote core has permission to invoke
     *  the specific IOCTL CMD and IOCTL cmd may fail if remote core does not
     *  have the required permission
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_ioctl_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_ioctl_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_IOCTL                   = 0x0D,
    /*!
     * \brief CMD to write to a specific register from remote core
     *
     *  Command allows remote core to write a specific register.
     *  Master core will check if remote core is permitted to perform register
     *  write and will allow register write only if permitted
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_regwr_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_regwr_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_REGWR                   = 0x0E,
    /*!
     * \brief CMD to read from a specific register from remote core
     *
     *  Command allows remote core to read a specific register.
     *  Master core will check if remote core is permitted to perform register
     *  read and will allow register write only if permitted
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_regrd_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_regrd_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_REGRD                   = 0x0F,
    /*!
     * \brief CMD to associate IPv4 address with MAC address
     *
     *  Command allows remote core to register IPV4 address with a mac address
     *  ARP queries from external nodes will be received on host port. The
     *  ARP queries can be routed to only a single core .This is typically the
     *  master core which maintains ARP database of all the IP entries: MAC address
     *  mapping used by all clients in all remote cores.
     *  The remote client must explicitly registers its IP address: MAC address
     *  with the master core using this CMD
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_ipv4_register_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_ipv4_register_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_IPV4_MAC_REGISTER       = 0x10,
    /*!
     * \brief CMD to associate IPv6 address with MAC address
     *
     *  Command allows remote core to register IPV6 address with a mac address
     *  ARP queries from external nodes will be received on host port. The
     *  ARP queries can be routed to only a single core .This is typically the
     *  master core which maintains ARP database of all the <IP entries: MAC address>
     *  mapping used by all clients in all remote cores.
     *  The remote client must explicitly registers its <IP address: MAC address>
     *  with the master core using this CMD
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_ipv6_register_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_ipv6_register_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_IPV6_MAC_REGISTER       = 0x11,
    /*!
     * \brief CMD to remove IPv4 address: MAC address mapping
     *
     *  Command removes ARP entry of IP address: MAC addres mapping.
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_IPV4_MAC_REGISTER
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_ipv4_unregister_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_ipv4_unregister_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_IPV4_MAC_UNREGISTER     = 0x12,
    /*!
     * \brief CMD to remove IPv6 address: MAC address mapping
     *
     *  Command removes ARP entry of IP address: MAC addres mapping.
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_IPV6_MAC_REGISTER
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_ipv6_unregister_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_ipv6_unregister_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_IPV6_MAC_UNREGISTER     = 0x13,
    /*!
     * \brief CMD to request remote device to respond to ping request from client
     *
     *  Command to request remote device server running on master core to
     *  respond to ping request. The server will copy the ping msg sent by 
     *  client and send back ping response. 
     *  This cmd is primarily used for debug/heartbeat check purpose
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_ping_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_ping_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_PING_REQUEST            = 0x14,
    /*!
     * \brief Notify CMD from remote device server to client
     *
     *  Notify commands are remote device commands that do not require 
     *  acknowledgement. This is a notify cmd from server to client.
     *  The server runs on master core and client runs on remote cores
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_s2c_notify
     *   Response Message (Sent from server to client): NONE (Notify commands do nto have any response)
     */
    RPMSG_KDRV_TP_ETHSWITCH_S2C_NOTIFY              = 0x15,
    /*!
     * \brief Notify CMD from remote device client to server
     *
     *  Notify commands are remote device commands that do not require 
     *  acknowledgement. This is a notify cmd from client to server.
     *  The server runs on master core and client runs on remote cores
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_c2s_notify
     *   Response Message (Sent from server to client): NONE (Notify commands do nto have any response)
     */
    RPMSG_KDRV_TP_ETHSWITCH_C2S_NOTIFY              = 0x16,
    /*!
     * \brief CMD to register a Ethertype by the remote core client to a specific rx flow id
     *
     *  Commands allows remote core client to register all traffic received on
     *  the host port with a specific ethertype to be routed to 
     *  the given rx flow id 
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_register_ethertype_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_register_ethertype_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_REGISTER_ETHTYPE            = 0x17,
    /*!
     * \brief CMD to unregister a Ethertype by the remote core client 
     *
     *  This is inverse operation of RPMSG_KDRV_TP_ETHSWITCH_REGISTER_ETHTYPE and
     *  disables the routing of traffic with given ethertype to a 
     *  specific rx flow id.
     *  Once unregistered further traffic with the given ethertype
     *  will be routed to default rx flow
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_unregister_ethertype_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_unregister_ethertype_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_ETHTYPE          = 0x18,
    /*!
     * \brief CMD to register a remote timer with ethfw for time synchronization
     *
     *  Commands allows remote core client to register a timer used by it
     *  to be synchronized with CPTS timer using timer sync router and hardware push
     *  events
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_register_remotetimer_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_register_remotetimer_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_REGISTER_REMOTEIMER         = 0x19,
    /*!
     * \brief CMD to unregister remote timer with ethfw for time synchronization
     *
     *  Commands allows remote core client to unregister a timer used by for synchronization with CPTS timer
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_unregister_remotetimer_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_unregister_remotetimer_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_REMOTEIMER       = 0x1A,

    /*!
     * \brief CMD to set promiscuous mode
     *
     *  Commands allows remote core client to set promiscuous mode
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_set_promisc_mode_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_set_promisc_mode_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_SET_PROMISC_MODE            = 0x1B,

    /*!
     * \brief CMD to add multicast MAC address to receive filter
     *
     *  Commands allows remote core client to add a multicast address to receive filter
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_filter_add_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_filter_add_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_FILTER_ADD_MAC              = 0x1C,

    /*!
     * \brief CMD to delete multicast MAC address to receive filter
     *
     *  Commands allows remote core client to delete a multicast address from receive filter
     *
     *  Command parameters:
     *   Request Message (Sent from client to server): struct rpmsg_kdrv_ethswitch_filter_del_mac_request
     *   Response Message (Sent from server to client): struct rpmsg_kdrv_ethswitch_filter_del_mac_response
     */
    RPMSG_KDRV_TP_ETHSWITCH_FILTER_DEL_MAC              = 0x1D,

    /*!
     * \brief Max value of Ethernet Switch Remote Device. For internal use only
     */
    RPMSG_KDRV_TP_ETHSWITCH_MAX                         = 0x1E,
};

/*!
 * \brief CPSW Type supported by Ethernet Switch Remote Device
 */
enum rpmsg_kdrv_ethswitch_cpsw_type
{
    /*! Etheret Remote Device CPSW Type : CPSW2G (2 port switch) */
    RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MCU,
    /*! Etheret Remote Device CPSW Type : CPSW5G or 9G (5 or 9 port switch) */
    RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAIN,
    /*! Max Etheret Remote Device CPSW Type. For internal use */
    RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAX,
};

/*!
 * \brief Etheret Remote Device Client to Server notify types
 */
enum rpmsg_kdrv_ethswitch_client_notify_type
{
    /*! Client to server notify command to dump CPSW stats on master core UART console */
    RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_DUMPSTATS,
    /*! Client to server notify command that is app specific.
     *  Application on server will receive callback and can
     *  typecast the notify info to handle the notify 
     */
    RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_CUSTOM,
    /*! Client to server notify command max. For internal use */
    RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_MAX,
};

/**
 *  \name Ethernet Switch Remote Device CMD response code
 *
 *  @{
 */
/*! Ethernet Switch Remote Device CMD response code : Success */
#define RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK       (0)
/*! Ethernet Switch Remote Device CMD response code : Try again 
 *
 *  Reponse indicates temporary failure of cmd and client can retry
 *  the cmd again
 */
#define RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EAGAIN   (-1)
/*! Ethernet Switch Remote Device CMD response code : Failure */
#define RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL    (-2)
/*! Ethernet Switch Remote Device CMD response code : Failure to insufficient permission 
 *
 *  Reponse indicates the command failed because remote core does not have sufficient privileges
 */
#define RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EACCESS  (-3)
/*  @} */



/*!
 * Maximum length of ethernet switch remote device message data in rpmsg_kdrv_ethswitch_ping_request
 */
#define RPMSG_KDRV_TP_ETHSWITCH_MESSAGE_DATA_LEN    (192)

/*!
 * Maximum length of input arguments for RPMSG_KDRV_TP_ETHSWITCH_IOCTL
 */
#define RPMSG_KDRV_TP_ETHSWITCH_IOCTL_INARGS_LEN    (192)

/*!
 * Maximum length of output arguments for RPMSG_KDRV_TP_ETHSWITCH_IOCTL
 */
#define RPMSG_KDRV_TP_ETHSWITCH_IOCTL_OUTARGS_LEN    (192)


/*!
 * Number of priorities supported by CPSW
 */
#define RPMSG_KDRV_TP_ETHSWITCH_CPSW_PRIORITY_NUM   (8)

/*!
 * MAC Address length in octets
 */
#define RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN          (6)

/*!
 * IPv4 Address length in octets
 */
#define RPMSG_KDRV_TP_ETHSWITCH_IPV4ADDRLEN         (4)

/*!
 * IPv6 Address length in octets
 */
#define RPMSG_KDRV_TP_ETHSWITCH_IPV6ADDRLEN         (16)

/**
 *  \name Ethernet Switch Remote Device CPSW IP Supported Feature Bitmask
 *
 *  @{
 */
/*! Feature: Tx Checksum Offload Enabled  */
#define RPMSG_KDRV_TP_ETHSWITCH_FEATURE_TXCSUM      (1 << 0)

/* Note: Feature bit 1 is intentionally not used, Linux already using it */

/*! Feature: MAC-only mode enabled */
#define RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MAC_ONLY    (1 << 2)

/*! Feature: Multicast filter enabled */
#define RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MC_FILTER   (1 << 3)
/*  @} */

/*!
 * Indicates to the Ethernet Firmware to use the default VLAN id for
 * the type of port associated with the caller, i.e. virtual MAC or virtual
 * switch.
 */
#define RPMSG_KDRV_TP_ETHSWITCH_VLAN_USE_DFLT      (0xFFFF)

/*!
 * Number of octets in year
 */
#define RPMSG_KDRV_TP_ETHSWITCH_YEARLEN             (4)

/*!
 * Number of octets in month
 */
#define RPMSG_KDRV_TP_ETHSWITCH_MONTHLEN            (3)

/*!
 * Number of octets in date
 */
#define RPMSG_KDRV_TP_ETHSWITCH_DATELEN             (2)

/*!
 * GIT Commit SHA length in octets
 */
#define RPMSG_KDRV_TP_ETHSWITCH_COMMITSHALEN        (8)

/*!
 * Common message header for all ethernet switch remote  device cmds
 */
struct rpmsg_kdrv_ethswitch_message_header
{
    /*! Message Type enum: rpmsg_kdrv_ethswitch_message_type */
    u8 message_type;
} __attribute__((packed));

/*!
 * Common structure used for all ethernet switch remote device command request msgs except attach
 */
struct rpmsg_kdrv_ethswitch_common_request_info
{
    /*! opaque unique handle returned by ATTACH  */
    u64 id;
    /*! Core specific key returned by attach */
    u32 core_key;
} __attribute__((packed));

/*!
 * Common header used for all ethernet switch remote device command response msgs
 */
struct rpmsg_kdrv_ethswitch_common_response_info
{
    /*! Status of request. Refer Ethernet Switch Remote Device CMD response code */
    s32 status;
} __attribute__((packed));

/*!
 * RPMSG_KDRV_TP_ETHSWITCH_ATTACH cmd client request
 */
struct rpmsg_kdrv_ethswitch_attach_request
{
    /*! common message header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! CPSW TYPE enum: rpmsg_kdrv_ethswitch_cpsw_type  */
    u8 cpsw_type;
} __attribute__((packed));

/*!
 * RPMSG_KDRV_TP_ETHSWITCH_ATTACH cmd server response
 */
struct rpmsg_kdrv_ethswitch_attach_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! unique handle used by all further CMDs. All further commands
     *  are required to use the id as a param  
     */
    u64 id;
    /*! Core specific key to indicate attached core. All further commands
     *  are required to use the core_key as a param 
     */
    u32 core_key;
    /*! MTU of rx packet */
    u32 rx_mtu;
    /*! MTU of tx packet per priority */
    u32 tx_mtu[RPMSG_KDRV_TP_ETHSWITCH_CPSW_PRIORITY_NUM];
    /*! Feature bitmask based on defines RPMSG_KDRV_TP_ETHSWITCH_FEATURE_xxx */
    u32 features;
    /*! 1-relative MAC-only port number. 0 for non MAC-only ports */
    u32 mac_only_port;
} __attribute__((packed));

/*!
 * RPMSG_KDRV_TP_ETHSWITCH_ATTACH_EXT cmd client request
 */
struct rpmsg_kdrv_ethswitch_attach_extended_request
{
    /*! common message header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! CPSW TYPE  enum: rpmsg_kdrv_ethswitch_cpsw_type  */
    u8 cpsw_type;
} __attribute__((packed));

/*!
 * RPMSG_KDRV_TP_ETHSWITCH_ATTACH_EXT cmd server response
 */
struct rpmsg_kdrv_ethswitch_attach_extended_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! unique handle used by all further CMDs  */
    u64 id;
    /*! Core specific key to indicate attached core */
    u32 core_key;
    /*! MTU of rx packet */
    u32 rx_mtu;
    /*! MTU of tx packet per priority */
    u32 tx_mtu[RPMSG_KDRV_TP_ETHSWITCH_CPSW_PRIORITY_NUM];
    /*! Feature bitmask based on defines RPMSG_KDRV_TP_ETHSWITCH_FEATURE_xxx */
    u32 features;
    /*! Allocated flow's index */
    u32 alloc_flow_idx;

    /*! Tx PSIL Peer destination thread id which should be paired with the
     * Tx UDMA channel
     */
    u32 tx_cpsw_psil_dst_id;
    /*! Mac address allocated */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /*! 1-relative MAC-only port number. 0 for non MAC-only ports */
    u32 mac_only_port;
} __attribute__((packed));

/*!
 * \brief Alloc request CMD params
 *
 * Common command params associated with the following ALLOC_xxx commands
 * RPMSG_KDRV_TP_ETHSWITCH_ALLOC_RX,
 * RPMSG_KDRV_TP_ETHSWITCH_ALLOC_TX,
 * RPMSG_KDRV_TP_ETHSWITCH_ALLOC_MAC,
 * RPMSG_KDRV_TP_ETHSWITCH_ALLOC_RX_DEFAULT
 * cmd
 */
struct rpmsg_kdrv_ethswitch_alloc_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Alloc Request common info  */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
} __attribute__((packed));

/*!
 * \brief Alloc request CMD params
 */
struct rpmsg_kdrv_ethswitch_alloc_rx_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! Allocated flow's index */
    u32 alloc_flow_idx;
} __attribute__((packed));

/*!
 * \brief Alloc Tx channel CMD response msg
 */
struct rpmsg_kdrv_ethswitch_alloc_tx_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;

    /*! Tx PSIL Peer destination thread id which should be paired with the
     * Tx UDMA channel
     */
    u32 tx_cpsw_psil_dst_id;
} __attribute__((packed));

/*!
 * \brief Alloc MAC CMD response msg
 */
struct rpmsg_kdrv_ethswitch_alloc_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! Mac address allocated */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
} __attribute__((packed));

/*!
 * \brief Register Rx Default flow CMD request params
 */
struct rpmsg_kdrv_ethswitch_register_rx_default_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Default flow will be associated with the given index */
    u32    default_flow_idx;
} __attribute__((packed));

/*!
 * \brief Register Rx Default flow CMD response params
 */
struct rpmsg_kdrv_ethswitch_register_rx_default_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Register MAC address CMD request params
 */
struct rpmsg_kdrv_ethswitch_register_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! mac address to be associated with flow */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /*! Flow's index associated with the mac address to be registered in ALE */
    u32 flow_idx;
} __attribute__((packed));

/*!
 * \brief Register MAC address CMD response params
 */
struct rpmsg_kdrv_ethswitch_register_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));


/*!
 * \brief UnRegister MAC address CMD request params
 */
struct rpmsg_kdrv_ethswitch_unregister_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! mac address to be unregistered from the rx flow  */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /*! rx flow index from which the mac_address association will be removed  */
    u32 flow_idx;
} __attribute__((packed));

/*!
 * \brief UnRegister MAC address CMD response params
 */
struct rpmsg_kdrv_ethswitch_unregister_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Free MAC address CMD request params
 */
struct rpmsg_kdrv_ethswitch_free_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Mac address to be freed */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
} __attribute__((packed));

/*!
 * \brief Free MAC address CMD response params
 */
struct rpmsg_kdrv_ethswitch_free_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Free Tx Channel CMD request params
 */
struct rpmsg_kdrv_ethswitch_free_tx_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Tx Channel CPSW PSIL Destination thread id to be freed */
    u32 tx_cpsw_psil_dst_id;
} __attribute__((packed));

/*!
 * \brief Free Tx Channel CMD response params
 */
struct rpmsg_kdrv_ethswitch_free_tx_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Unregister Default Flow CMD request params
 */
struct rpmsg_kdrv_ethswitch_unregister_rx_default_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Default flow index to be unregistered */
    u32 default_flow_idx;
} __attribute__((packed));

/*!
 * \brief Unregister Default Flow CMD response params
 */
struct rpmsg_kdrv_ethswitch_unregister_rx_default_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Free Rx  Flow CMD request params
 */
struct rpmsg_kdrv_ethswitch_free_rx_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Rx flow id to be freed */
    u32 alloc_flow_idx;
} __attribute__((packed));

/*!
 * \brief Free Rx  Flow CMD response params
 */
struct rpmsg_kdrv_ethswitch_free_rx_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Detach CMD request params
 */
struct rpmsg_kdrv_ethswitch_detach_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
} __attribute__((packed));

/*!
 * \brief Detach CMD response params
 */
struct rpmsg_kdrv_ethswitch_detach_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief IOCTL CMD request params
 */
struct rpmsg_kdrv_ethswitch_ioctl_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! CPSW IOCTL CMD id. Refer CPSW LLD documentation for list of CPSW LLD IOCTLs */
    u32    cmd;
    /*! CPSW IOCTL CMD input arguments length */
    u32    inargs_len;
    /*! CPSW IOCTL CMD input arguments .Byte array is typecast to the inArgs structure associated with the IOCTL */
    u8     inargs[RPMSG_KDRV_TP_ETHSWITCH_IOCTL_INARGS_LEN];
    /*! CPSW IOCTL CMD output arguments length */
    u32    outargs_len;
}  __attribute__((packed));

/*!
 * \brief IOCTL CMD response params
 */
struct rpmsg_kdrv_ethswitch_ioctl_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! CPSW IOCTL CMD output arguments .Byte array is typecast to the outArgs structure associated with the IOCTL */
    u8     outargs[RPMSG_KDRV_TP_ETHSWITCH_IOCTL_OUTARGS_LEN];
} __attribute__((packed));

/*!
 * \brief Register Write  CMD request params
 */
struct rpmsg_kdrv_ethswitch_regwr_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Register Address */
    u32    regaddr;
    /*! Register Value to be written */
    u32    regval;
} __attribute__((packed));

/*!
 * \brief Register Write  CMD response params
 */
struct rpmsg_kdrv_ethswitch_regwr_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! Updated register value */
    u32 regval;
} __attribute__((packed));

/*!
 * \brief Register Read  CMD request params
 */
struct rpmsg_kdrv_ethswitch_regrd_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Register Address */
    u32    regaddr;
} __attribute__((packed));

/*!
 * \brief Register Read  CMD response params
 */
struct rpmsg_kdrv_ethswitch_regrd_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
    /*! Register Read Value */
    u32    regval;
} __attribute__((packed));

/*!
 * \brief Register IPv4:MAC Address mapping CMD request params
 */
struct rpmsg_kdrv_ethswitch_ipv4_register_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;

    /*! Mac address associated with the IP address which should be added to
     *  the ARP table
     */
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /*! IPv4 address  */
    uint8_t ipv4_addr[RPMSG_KDRV_TP_ETHSWITCH_IPV4ADDRLEN];
} __attribute__((packed));

/*!
 * \brief Register IPv6:MAC Address mapping CMD request params
 */
struct rpmsg_kdrv_ethswitch_ipv6_register_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Mac address associated with the IP address which should be added to
     *  the ARP table
     */
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /*! IPv6 address */
    uint8_t ipv6_addr[RPMSG_KDRV_TP_ETHSWITCH_IPV6ADDRLEN];
} __attribute__((packed));

/*!
 * \brief Register IPv4:MAC Address mapping CMD response params
 */
struct rpmsg_kdrv_ethswitch_ipv4_register_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Register IPv6:MAC Address mapping CMD response params
 */
struct rpmsg_kdrv_ethswitch_ipv6_register_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Unregister IPv4:MAC Address mapping CMD request params
 */
struct rpmsg_kdrv_ethswitch_ipv4_unregister_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! IPv4 address  */
    uint8_t ipv4_addr[RPMSG_KDRV_TP_ETHSWITCH_IPV4ADDRLEN];
} __attribute__((packed));

/*!
 * \brief Unregister IPv6:MAC Address mapping CMD request params
 */
struct rpmsg_kdrv_ethswitch_ipv6_unregister_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! IPv6 address */
    uint8_t ipv6_addr[RPMSG_KDRV_TP_ETHSWITCH_IPV6ADDRLEN];
} __attribute__((packed));

/*!
 * \brief Unregister IPv4:MAC Address mapping CMD response params
 */
struct rpmsg_kdrv_ethswitch_ipv4_unregister_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Unregister IPv6:MAC Address mapping CMD response params
 */
struct rpmsg_kdrv_ethswitch_ipv6_unregister_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));


/*!
 * \brief Register Ethertype CMD request params
 */
struct rpmsg_kdrv_ethswitch_register_ethertype_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Ether type to be associated with flow */
    u16 ether_type;
    /*! Flow's index associated with the mac address to be registered in ALE */
    u32 flow_idx;
} __attribute__((packed));

/*!
 * \brief Register Ethertype CMD response params
 */
struct rpmsg_kdrv_ethswitch_register_ethertype_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));


/*!
 * \brief UnRegister Ethertype CMD request params
 */
struct rpmsg_kdrv_ethswitch_unregister_ethertype_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Ether type to be unregistered from the rx flow  */
    u16 ether_type;
    /*! rx flow index from which the mac_address association will be removed  */
    u32 flow_idx;
} __attribute__((packed));

/*!
 * \brief UnRegister Ethertype CMD response params
 */
struct rpmsg_kdrv_ethswitch_unregister_ethertype_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Register Remote timer CMD request params
 */
struct rpmsg_kdrv_ethswitch_register_remotetimer_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Timer id to be used for timesync router configuration */
    u8 timer_id;
    /*! CPTS hardware push number to be used for timesync router configuration */
    u8 hwPushNum;
} __attribute__((packed));

/*!
 * \brief Register Remote timer CMD response params
 */
struct rpmsg_kdrv_ethswitch_register_remotetimer_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
}  __attribute__((packed));

/*!
 * \brief UnRegister Remote timer CMD request params
 */
struct rpmsg_kdrv_ethswitch_unregister_remotetimer_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! CPTS hardware push number used for timesync router configuration */
    u8 hwPushNum;
} __attribute__((packed));

/*!
 * \brief UnRegister Remote timer CMD response params
 */
struct rpmsg_kdrv_ethswitch_unregister_remotetimer_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Set promiscuous mode CMD request params
 */
struct rpmsg_kdrv_ethswitch_set_promisc_mode_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Promiscuous mode: enable or disable */
    u32 enable;
} __attribute__((packed));

/*!
 * \brief Set promiscuous mode CMD response params
 */
struct rpmsg_kdrv_ethswitch_set_promisc_mode_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Add multicast MAC address to receive filter CMD request params
 */
struct rpmsg_kdrv_ethswitch_filter_add_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Multicast MAC address to be added to receive filter */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /* VLAN id. Pass \ref RPMSG_KDRV_TP_ETHSWITCH_VLAN_USE_DFLT to let
     * Ethernet Firmware use the default VLAN id for the port type
     * (virtual MAC or virtual switch) */
    u16 vlan_id;
    /*! Flow's index associated with the MAC address to be registered in ALE */
    u32 flow_idx;
} __attribute__((packed));

/*!
 * \brief Add multicast MAC address to receive filter CMD response params
 */
struct rpmsg_kdrv_ethswitch_filter_add_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Delete multicast MAC address from receive filter CMD request params
 */
struct rpmsg_kdrv_ethswitch_filter_del_mac_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Multicast MAC address to be deleted from receive filter */
    u8 mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    /* VLAN id */
    u16 vlan_id;
    /*! Flow's index associated with the MAC address to be unregistered in ALE */
    u32 flow_idx;
} __attribute__((packed));

/*!
 * \brief Delete multicast MAC address from receive filter CMD response params
 */
struct rpmsg_kdrv_ethswitch_filter_del_mac_response
{
    /*! common response info */
    struct rpmsg_kdrv_ethswitch_common_response_info info;
} __attribute__((packed));

/*!
 * \brief Firmware version info returned by remote device attach to the ethernet switch device
 */
struct rpmsg_kdrv_ethswitch_firmware_version_info
{
    /*! Remote Ethernet Switch Device API Major version number */
    u32 major;
    /*! Remote Ethernet Switch Device API Minor version number */
    u32 minor;
    /*! Remote Ethernet Switch Device API Revision version number */
    u32 rev;
    /*! Remote Ethernet Switch Device Firmware Build year : char string in the form YYYY eg: 2019 */
    char year[RPMSG_KDRV_TP_ETHSWITCH_YEARLEN];
    /*! Remote Ethernet Switch Device Firmware Build month : char string in the form MON eg: Dec */
    char month[RPMSG_KDRV_TP_ETHSWITCH_MONTHLEN];
    /*! Remote Ethernet Switch Device Firmware Build month : char string in the form DD eg: 12 */
    char date[RPMSG_KDRV_TP_ETHSWITCH_DATELEN];
    /*! GIT commit SHA of the firmware: char string in the form fd52c34f */
    char commit_hash[RPMSG_KDRV_TP_ETHSWITCH_COMMITSHALEN];
} __attribute__((packed));

/*!
 * \brief Ethernet Switch Remote Device Data
 *
 * The remote device framework will return the below device data to the remote
 * client when it attaches to the remote ethernet switch device
 */
struct rpmsg_kdrv_ethswitch_device_data
{
    /*! Ethernet Switch Remote Device Firmware version info */
    struct rpmsg_kdrv_ethswitch_firmware_version_info fw_ver;
    /*! Flag indicating permission enabled for each
     * enum rpmsg_kdrv_ethswitch_message_type command for the connecting
     * client
     */
    u32 permission_flags;
    /*! Flag indicating if UART is connected: 1 indicates UART connected , 0 indicates UART not connected  */
    u32 uart_connected;
    /*! UART ID used by firmware for log prints */
    u32 uart_id;
} __attribute__((packed));

/*!
 * \brief Ethernet Switch Remote Device Ping Request
 *
 * Ping requests is always from client to server and is used for debug/heartbeat check
 * The client intiates a ping request
 * The remote device server will respond to ping request by copying the ping
 * message passed by client . 
 */
struct rpmsg_kdrv_ethswitch_ping_request
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Ping data.Client populates this which serves copies in its reponse message */
    u8 data[RPMSG_KDRV_TP_ETHSWITCH_MESSAGE_DATA_LEN];
} __attribute__((packed));

/*!
 * \brief Ethernet Switch Remote Device Ping Response
 */
struct rpmsg_kdrv_ethswitch_ping_response
{
    /*! Ping data response */
    u8 data[RPMSG_KDRV_TP_ETHSWITCH_MESSAGE_DATA_LEN];
} __attribute__((packed));

/*!
 * \brief Ethernet Switch Remote Device Server to Client Notify
 *
 * Remote Device Framework notify messages are class of messages that 
 * are one directional. The receiver does not respond with response msg or
 * ack.
 * Notify msgs are typically used to notify events
 */
struct rpmsg_kdrv_ethswitch_s2c_notify
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Notify data.Presently no S2C notify are supported .
     * API will be updated to support S2C notify events such as 
     * PHY link down and this API param is expected to change 
     */
    u8 data[RPMSG_KDRV_TP_ETHSWITCH_MESSAGE_DATA_LEN];
} __attribute__((packed));

/*!
 * \brief Ethernet Switch Remote Device Client to Server Notify
 *
 * Remote Device Framework notify messages are class of messages that 
 * are one directional. The receiver does not respond with response msg or
 * ack.
 * Notify msgs are typically used to notify events
 */
struct rpmsg_kdrv_ethswitch_c2s_notify
{
    /*! Common CMD header */
    struct rpmsg_kdrv_ethswitch_message_header header;
    /*! Common info associated with all CMDs other than ATTACH */
    struct rpmsg_kdrv_ethswitch_common_request_info info;
    /*! Notify Id. Of type enum rpmsg_kdrv_ethswitch_client_notify_type */
    u8 notifyid;
    /*! Filled length of notify info */
    u32 notify_info_len;
    /*! Notify Message data */
    u8 notify_info[RPMSG_KDRV_TP_ETHSWITCH_MESSAGE_DATA_LEN];
} __attribute__((packed));

/* @} */

#endif
