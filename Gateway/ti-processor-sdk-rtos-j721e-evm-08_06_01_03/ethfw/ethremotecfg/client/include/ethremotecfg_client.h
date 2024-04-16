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

#ifndef __ETHREMOTECFG_CLIENT_H__
#define __ETHREMOTECFG_CLIENT_H__

#include <ethremotecfg/server/include/ethremotecfg_server.h>

/**
 * \defgroup ETHSWITCH_REMOTE_DEVICE_CLIENT_API Ethernet Switch Remote Device Client APIs
 *
 * \brief This section contains APIs for Ethernet Switch Remote Device Client APIs
 *
 * The ethernet switch remote device client resides on different remote cores.
 * The client attach to the ethernet switch remote device server using the remote device framework
 * Once connected to the server the client can configure the ethernet switch using the
 * client APIs
 *
 *  @{
 */
/* @} */
/*!
 * \addtogroup ETHSWITCH_REMOTE_DEVICE_CLIENT_API
 * @{
 */

/*! 
 * \brief Ethernet Switch Remote Device Client Device Connect params
 */
typedef struct rdevEthSwitchClientInitPrms_s
{
    /*! Remote Device Server Name to which client running on local core will connect to */
    char device_name[ETHREMOTECFG_SERVER_MAX_NAME_LEN];
    /*! Unique device id returned by the server on connect */
    uint32_t device_id;
    /*! Device Type returned by the server on connect */
    uint32_t device_type;
    /*! Application callback handler invoke by the remote device framework client  */
    uint32_t (*cbHandler)(void *priv_data,
                          void *msg);
    /*! Ethernet Switch Remote Device Data populated by the server on device connect  */
    struct rpmsg_kdrv_ethswitch_device_data eth_device_data;
} rdevEthSwitchClientInitPrms_t;

/*!
 * \brief Connect to Ethernet Switch Remote Device
 *
 * The client must first connect to the Ethernet Switch Remote Device server
 * After connect the client can invoke the Ethernet Switch Remote Device Client
 * APIs to configure the remote ethernet switch device
 *
 * \param initPrms Server Connect params
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of incorrect init parameters or
 *                                                 any failure connecting to remote server side.
 */
int32_t rdevEthSwitchClient_connect(rdevEthSwitchClientInitPrms_t *initPrms);

/*!
 * \brief Disconnect to Ethernet Switch Remote Device
 *
 * The client can disconnect from the Ethernet Switch Remote Device server.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any failure disconnecting from server side.
 */
int32_t rdevEthSwitchClient_disconnect(uint32_t device_id);

/*!
 * \brief Send Ping to Ethernet Switch Remote Device
 *
 * The server will respond to ping request
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param ping_msg  Ping message sent by client app
 * \param ping_len  Length of ping msg
 * \param respMsg   Response to ping message received from server
 * \param respMaxLen Length of response ping msg
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_sendping(uint32_t device_id,
                                     char *ping_msg,
                                     uint32_t ping_len,
                                     char *respMsg,
                                     uint32_t respMaxLen);

/*!
 * \brief Unregister association of IPv4 address with MAC address by removing ARP entry in the master core
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param ipv4_address  IPV4 address to be unregistered
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_ipv4macunregister(uint32_t device_id,
                                              uint64_t id,
                                              uint32_t core_key,
                                              uint8_t *ipv4_address);

/*!
 * \brief Register association of IPv6 address with MAC address by adding ARP entry in the master core
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param mac_address   MAC address with which the IPv4 address will be associated
 * \param ipv6_address  IPV4 address to be added to ARP database
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_ipv6macregister(uint32_t device_id,
                                            uint64_t id,
                                            uint32_t core_key,
                                            uint8_t *mac_address,
                                            uint8_t *ipv6_address);

/*!
 * \brief Register association of IPv4 address with MAC address by adding ARP entry in the master core
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param mac_address   MAC address with which the IPv4 address will be associated
 * \param ipv4_address  IPV4 address to be added to ARP database
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_ipv4macregister(uint32_t device_id,
                                            uint64_t id,
                                            uint32_t core_key,
                                            uint8_t *mac_address,
                                            uint8_t *ipv4_address);

/*!
 * \brief Register Read Function
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param regaddr   Register Address to be read from
 * \param pregval   Pointer to register value which will be populated by this function
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_regrd(uint32_t device_id,
                                  uint32_t regaddr,
                                  uint32_t *pregval);
/*!
 * \brief Register Write Function
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param regaddr   Register Address to be read from
 * \param regval    Register value to be written
 * \param post_wr_regval    Pointer to register value after register write populated by this function
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_regwr(uint32_t device_id,
                                  uint32_t regaddr,
                                  uint32_t regval,
                                  uint32_t *post_wr_regval);

/*!
 * \brief Invoke Cpsw IOCTL
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param cmd       CPSW IOCTL CMD id. Refer CPSW LLD documentation for list of CPSW LLD IOCTLs
 * \param inargs      CPSW IOCTL CMD input arguments .Byte array is typecast to the inArgs structure associated with the IOCTL
 * \param inargs_len  CPSW IOCTL CMD input arguments length
 * \param outargs     CPSW IOCTL CMD input arguments .Byte array is typecast to the outArgs structure associated with the IOCTL. Populated by this function
 * \param outargs_len CPSW IOCTL CMD output arguments length
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_ioctl(uint32_t device_id,
                                  uint64_t id,
                                  uint32_t core_key,
                                  uint32_t cmd,
                                  const void *inargs,
                                  uint32_t inargs_len,
                                  void *outargs,
                                  uint32_t outargs_len);

/*!
 * \brief Detach from Ethernet Switch Remote Device
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_detach(uint32_t device_id,
                                   uint64_t id,
                                   uint32_t core_key);

/*!
 * \brief Free Rx Flow Id
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param alloc_flow_idx Rx Flow Id to be freed
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_freerx(uint32_t device_id,
                                   uint64_t id,
                                   uint32_t core_key,
                                   uint32_t alloc_flow_idx);

/*!
 * \brief Free Tx Channel CPSW PSIL Destination thread id
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param tx_cpsw_psil_dst_id Tx Channel CPSW PSIL Destination thread id to be freed
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_freetx(uint32_t device_id,
                                   uint64_t id,
                                   uint32_t core_key,
                                   uint32_t tx_cpsw_psil_dst_id);

/*!
 * \brief Free Tx Channel CPSW PSIL Destination thread id
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param mac_address Destination mac address to be freed
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_freemac(uint32_t device_id,
                                    uint64_t id,
                                    uint32_t core_key,
                                    uint8_t *mac_address);

/*!
 * \brief Unregister Default Flow from the given flow index.
 *
 * This function disables routing of default traffic (traffic not matching any classifier with thread id configured)
 * to the given rx flow_idx. Once disabled, all default traffic will be routed to the reserved flow resulting in 
 * all packets of default flow being dropped
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param default_flow_idx Default Flow Id from to which the default flow will no longer be directed
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_unregisterrxdefault(uint32_t device_id,
                                                uint64_t id,
                                                uint32_t core_key,
                                                uint32_t default_flow_idx);

/*!
 * \brief Unregister Destination MAC address from the given flow index.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param flow_idx  Flow Id from to which the traffic with the given DST mac address will no longer be directed
 * \param mac_address Destination mac address to be unregistered
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_unregistermac(uint32_t device_id,
                                          uint64_t id,
                                          uint32_t core_key,
                                          uint32_t flow_idx,
                                          uint8_t *mac_address);

/*!
 * \brief Register Destination MAC address with the given flow index.
 *
 * This function registers the destination mac to the given rx flow index.
 * This causes all packets with the given destination mac address to be 
 * routed to the given rx flow index.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param flow_idx  Flow Id to which the traffic with the given DST mac address will directed
 * \param mac_address Destination mac address to be registered
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_registermac(uint32_t device_id,
                                        uint64_t id,
                                        uint32_t core_key,
                                        uint32_t flow_idx,
                                        uint8_t *mac_address);

/*!
 * \brief Alloc Destination MAC address
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param mac_address Destination mac address .Populated by this function with allocated DST MAC address
 * \param mac_address_len Destination mac address buffer length
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_allocmac(uint32_t device_id,
                                     uint64_t id,
                                     uint32_t core_key,
                                     uint8_t *mac_address,
                                     uint32_t mac_address_len);

/*!
 * \brief Register Default Flow to the given flow index.
 *
 * This function enables routing of default traffic (traffic not matching any classifier with thread id configured)
 * to the given rx flow_idx.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param default_flow_idx Default Flow Id from to which the default flow will no longer be directed
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_registerrxdefault(uint32_t device_id,
                                              uint64_t id,
                                              uint32_t core_key,
                                              uint32_t default_flow_idx);

/*!
 * \brief Alloc Rx Flow Id
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param rx_flow_allocidx Allocated Rx Flow Index populated by this function
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_allocrx(uint32_t device_id,
                                    uint64_t id,
                                    uint32_t core_key,
                                    uint32_t *rx_flow_allocidx);

/*!
 * \brief Alloc Tx Channel CPSW PSIL Destination thread id
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param tx_cpsw_psil_dst_id Allocated Tx Channel CPSW PSIL Destination thread id populated by this function
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_alloctx(uint32_t device_id,
                                    uint64_t id,
                                    uint32_t core_key,
                                    uint32_t *tx_cpsw_psil_dst_id);

/*!
 * \brief Attach to Ethernet Switch Remote Device
 *
 * Clients must first attach to the ethernet switch remote device.Attach returns 
 * the core_key and id which are used as params for all further client fucntions
 * except regrd / regwr functions
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param enetType CPSW TYPE of type enum rpmsg_kdrv_ethswitch_cpsw_type
 * \param id Pointer to Unique Opaque Handle populated by this function 
 * \param core_key Pointer to Core key populated by this function
 * \param rx_mtu   Pointer to Maximum receive packet length . Populated by this function
 * \param tx_mtu   Array of Maximum transmit packet length per priority supported by ethernet switch
 * \param tx_mtu_array_size Size of tx_mtu array.Must be sufficient to store MTU size for all priorities supported by the CPSW
 * \param features Pointer to feature bitmap. Bitmask of type RPMSG_KDRV_TP_ETHSWITCH_FEATURE_xxx
 * \param mac_only_port Pointer to MAC-only port. 1-relative MAC-only port number, 0 for non MAC-only ports
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_attach(uint32_t device_id,
                                   uint8_t enetType,
                                   uint64_t *id,
                                   uint32_t *core_key,
                                   uint32_t *rx_mtu,
                                   uint32_t tx_mtu[],
                                   uint32_t tx_mtu_array_size,
                                   uint32_t *features,
                                   uint32_t *mac_only_port);

/*!
 * \brief Attach to Ethernet Switch Remote Device with extended response
 *
 * Clients must first attach to the ethernet switch remote device.Attach returns 
 * the core_key and id which are used as params for all further client fucntions
 * except regrd / regwr functions
 * For remote core clients that require only one rx/one tx and one  dst mac address,
 * rdevEthSwitchClient_attachext allows a single attach call to return all the required params
 * Client can avoid further calls to alloctx/allocrx etc.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param enetType CPSW TYPE of type enum rpmsg_kdrv_ethswitch_cpsw_type
 * \param id Pointer to Unique Opaque Handle populated by this function 
 * \param core_key Pointer to Core key populated by this function
 * \param rx_mtu   Pointer to Maximum receive packet length . Populated by this function
 * \param tx_mtu   Array of Maximum transmit packet length per priority supported by ethernet switch
 * \param tx_mtu_array_size Size of tx_mtu array.Must be sufficient to store MTU size for all priorities supported by the CPSW
 * \param features Pointer to feature bitmap. Bitmask of type RPMSG_KDRV_TP_ETHSWITCH_FEATURE_xxx
 * \param tx_cpsw_psil_dst_id Pointer to allocated Tx Channel CPSW PSIL destination thread id populated by this function
 * \param rx_flow_allocidx Pointer to allocated Rx Flow Index populated by this function
 * \param mac_address  Pointer to allocated destination mac address allocated to remote core populated by this function
 * \param mac_address_len Destination mac address buffer length
 * \param mac_only_port Pointer to MAC-only port. 1-relative MAC-only port number, 0 for non MAC-only ports
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_attachext(uint32_t device_id,
                                      uint8_t enetType,
                                      uint64_t *id,
                                      uint32_t *core_key,
                                      uint32_t *rx_mtu,
                                      uint32_t tx_mtu[],
                                      uint32_t tx_mtu_array_size,
                                      uint32_t *features,
                                      uint32_t *tx_cpsw_psil_dst_id,
                                      uint32_t *rx_flow_allocidx,
                                      uint8_t *mac_address,
                                      uint32_t mac_address_len,
                                      uint32_t *mac_only_port);

/*!
 * \brief Send Notify From Client to server
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param notify_id Client to server notify id of type enum rpmsg_kdrv_ethswitch_client_notify_type
 * \param notify_info Notify info associated with the notify id
 * \param notify_info_len Notify info length
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_sendNotify(uint32_t device_id,
                                       u64 id,
                                       u32 core_key,
                                       enum rpmsg_kdrv_ethswitch_client_notify_type notify_id,
                                       uint8_t *notify_info,
                                       uint32_t notify_info_len);

/*!
 * \brief Remote Device Framework print function callback
 *
 * This function is for internal use of the remote device framework which
 * expects all its clients to provide a printText callback
 *
 * \param priv      Context Pointer associated with printText call
 * \param data      Formatted string buffer to be printed
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 */
uint32_t rdevEthSwitchClient_printText(void *priv,
                                       void *data);


/*!
 * \brief Register Ethertype with the given flow index.
 *
 * This function registers the ethertype to the given rx flow index.
 * This causes all packets with the given ethertype to be 
 * routed to the given rx flow index.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param flow_idx  Flow Id to which the traffic with the given DST mac address will directed
 * \param ether_type Ethertype to be registered
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_registerethtype(uint32_t device_id,
                                        uint64_t id,
                                        uint32_t core_key,
                                        uint32_t flow_idx,
                                        uint16_t ether_type);

/*!
 * \brief Unregister Ethertype from the given flow index.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param flow_idx  Flow Id from to which the traffic with the given DST mac address will no longer be directed
 * \param ether_type Ethertype to be unregistered
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_unregisterethtype(uint32_t device_id,
                                          uint64_t id,
                                          uint32_t core_key,
                                          uint32_t flow_idx,
                                          uint16_t ether_type);

/*!
 * \brief Register remote timer with CPTS using timerid
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param timerid   Timer Id used for configuring timesync router
 * \param hwPushNum Hardware push number of CPTS
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_registerremotetimer(uint32_t device_id,
                                                uint64_t id,
                                                uint32_t core_key,
                                                uint8_t timerid,
                                                uint8_t hwPushNum);

/*!
 * \brief Unregister remote timer from CPTS using timerid
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param hwPushNum Hardware push number of CPTS
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_unregisterremotetimer(uint32_t device_id,
                                                  uint64_t id,
                                                  uint32_t core_key,
                                                  uint8_t hwPushNum);

/*!
 * \brief Set promiscuous mode
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach/rdevEthSwitchClient_attachext
 * \param enable    Promiscuous mode (enable or disable)
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_setPromiscMode(uint32_t device_id,
                                           uint64_t id,
                                           uint32_t core_key,
                                           uint32_t enable);

/*!
 * \brief Add multicast address to receive filter.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach
 *                  or rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach or
 *                  rdevEthSwitchClient_attachext
 * \param flow_idx  Flow Id to which the traffic with the given MAC address will
 *                  be directed.  Applicable only for multicast addresses with
 *                  exclusive access
 * \param mac_address Multicast MAC address to be added
 * \param vlan_id   VLAN id
 *
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_filterAddMac(uint32_t device_id,
                                         uint64_t id,
                                         uint32_t core_key,
                                         uint32_t flow_idx,
                                         uint8_t *mac_address,
                                         uint16_t vlan_id);

/*!
 * \brief Delete multicast address from receive filter.
 *
 * \param device_id Device id returned by rdevEthSwitchClient_connect
 * \param id        Unique Opaque Handle returned by rdevEthSwitchClient_attach
 *                  or rdevEthSwitchClient_attachext
 * \param core_key  Unique core_key returned by rdevEthSwitchClient_attach or
 *                  rdevEthSwitchClient_attachext
 * \param flow_idx  Flow Id to which the traffic with the given MAC address will
 *                  no longer be directed.  Applicable only for multicast addresses
 *                  with exclusive access
 * \param mac_address Multicast MAC address to be deleted
 * \param vlan_id   VLAN id
 *
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK    Success.
 * \retval RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL In case of any error while executing the command
 *                                                 on the server side or an argument mismatch.
 */
int32_t rdevEthSwitchClient_filterDelMac(uint32_t device_id,
                                         uint64_t id,
                                         uint32_t core_key,
                                         uint32_t flow_idx,
                                         uint8_t *mac_address,
                                         uint16_t vlan_id);

/* @} */

#endif
