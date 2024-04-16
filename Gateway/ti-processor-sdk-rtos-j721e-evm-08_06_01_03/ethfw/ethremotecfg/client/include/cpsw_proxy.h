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

#ifndef __CPSWPROXY_H__
#define __CPSWPROXY_H__

#include <stdint.h>
#include <ethremotecfg/client/include/ethremotecfg_client.h>
#include <ethremotecfg/protocol/cpsw_remote_notify_service.h>
#include <ethremotecfg/protocol/ethremotecfg_virtport.h>
#include <ti/drv/enet/enet.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup CPSW_PROXY_API Ethernet Switch Proxy Client APIs
 *
 * \brief This section contains APIs for CPSW Proxy Client APIs
 *
 * The CPSW proxy client resides on the remote cores and enables
 * clients on remote cores to configure the Ethernet Switch via RPC
 *
 * The Cpsw Proxy APIs for switch configuration are RPC APIs
 * @{
 */        
/* @} */

/*!
 * \addtogroup CPSW_PROXY_API
 * @{
 */

/*!
 * \anchor CpswProxy_ErrorCodes
 * \name CpswProxy Error Codes
 *
 * Error codes returned by the CPSW Proxy client APIs.
 *
 * @{
 */

/* Below error codes are aligned with CSL's and Enet LLD's to maintain
 * consistency and avoid error code conversion */

/*! \brief Success. */
#define CPSWPROXY_SOK                              (0)

/*! \brief Operation in progress. */
#define CPSWPROXY_SINPROGRESS                      (1)

/*! \brief Generic failure error condition (typically caused by hardware). */
#define CPSWPROXY_EFAIL                            (-1)

/*! \brief Bad arguments (i.e. NULL pointer). */
#define CPSWPROXY_EBADARGS                         (-2)

/*! \brief Invalid parameters (i.e. value out-of-range). */
#define CPSWPROXY_EINVALIDPARAMS                   (-3)

/*! \brief Time out while waiting for a given condition to happen. */
#define CPSWPROXY_ETIMEOUT                         (-4)

/*! \brief Allocation failure. */
#define CPSWPROXY_EALLOC                           (-8)

/*! \brief Unexpected condition occurred (sometimes unrecoverable). */
#define CPSWPROXY_EUNEXPECTED                      (-9)

/*! \brief The resource is currently busy performing an operation. */
#define CPSWPROXY_EBUSY                            (-10)

/*! \brief Already open error. */
#define CPSWPROXY_EALREADYOPEN                     (-11)

/*! \brief Operation not permitted. */
#define CPSWPROXY_EPERM                            (-12)

/*! \brief Operation not supported. */
#define CPSWPROXY_ENOTSUPPORTED                    (-13)

/*! \brief Resource not found. */
#define CPSWPROXY_ENOTFOUND                        (-14)

/*! \brief Unknown IOCTL. */
#define CPSWPROXY_EUNKNOWNIOCTL                    (-15)

/*! \brief Malformed IOCTL (args pointer or size not as expected). */
#define CPSWPROXY_EMALFORMEDIOCTL                  (-16)

/*! @} */

/*!
 * \brief Application Callback function pointers to notify when remote
 *        ethernet device data is received on remote core
 *
 * The client will attach to the server and the server will send the ethernet
 * device data to the server. This data is passed onto the application by means
 * of this callback.
 *
 * \param eth_dev_data Pointer to device data
 */
typedef void (*CpswProxy_deviceDataNotifyCbFxn)(struct rpmsg_kdrv_ethswitch_device_data *eth_dev_data);

/*!
 * \brief Cpsw Proxy Client Configuration structure
 */
typedef struct CpswProxy_Config_s
{
    /*! Virtual port id */
    EthRemoteCfg_VirtPort virtPort;

    /*! Application provided callback function to notify ethernet remote device data */
    CpswProxy_deviceDataNotifyCbFxn deviceDataNotifyCb;
} CpswProxy_Config;

/*!
 * \brief CPSW Proxy handle
 *
 * CPSW Proxy opaque handle.
 */
typedef struct CpswProxy_ClientObj_s *CpswProxy_Handle;

/*!
 * \brief Initialize CPSW Proxy on a given core
 *
 * Performs one-time initialization of the CPSW Proxy layer. It needs to be called
 * only once per core and it must be the very first CpswProxy API to be called.
 *
 * This API will initialize the underlying client-side EthSwitch remote device and
 * will block until server-side EthSwitch remote device is initialized.
 *
 * \param masterCoreId  Master core id on which the Cpsw Remote Device Server exists
 * \param masterEndpt   Master core's Cpsw Remote Device endpoint
 */
void CpswProxy_init(uint32_t masterCoreId,
                    uint32_t masterEndpt);

/*!
 * \brief Deinitialize CPSW Proxy on a given core
 *
 * Performs one-time deinitialization of the CPSW Proxy layer. It needs to be called
 * only once per core and it must be the very last CpswProxy API to be called.
 */
void CpswProxy_deinit(void);

/*!
 * \brief Connect to the Cpsw Proxy server
 *
 * Connect with the server side if it has been initialized. Client side then continues
 * its initialization steps which are dependent on server.
 *
 * Application should call this function until connection is established before calling
 * CpswProxy_open() or any other CpswProxy API.
 *
 * \return       IPC_SOK in case of success. Negative IPC error otherwise.
 */
int32_t CpswProxy_connect(void);

/*!
 * \brief Open CPSW proxy client instance with the given configuration
 *
 * Application will get a handle to Cpsw Proxy which will be used in all CPSW
 * Proxy APIs. Only a single proxy instance per remote core is supported
 * currently.
 *
 * \param cfg    Configuration of the CPSW Proxy client
 *
 * \return       Cpsw Proxy Handle which will be used in all Cpsw Proxy APIs.
 *               NULL value indicates CpswProxy_open() failed
 */
CpswProxy_Handle CpswProxy_open(const CpswProxy_Config *cfg);

/*!
 * \brief Close CPSW proxy client.
 *
 * Close and free the CPSW proxy client instance.
 *
 * \param hProxy   Cpsw Proxy Handle
 */
void CpswProxy_close(CpswProxy_Handle hProxy);

/*!
 * \brief Attach to Ethernet Switch Remote Device
 *
 * Clients must first attach to the ethernet switch remote device.
 * CpswProxy_attach() returns the core_key and id which are used as params for
 * all further client fucntions.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy      Handle to Cpsw Proxy
 * \param enetType    Enet instance type
 * \param pCpswHandle Pointer to unique opaque handle populated by this function 
 * \param coreKey     Pointer to Core key populated by this function
 * \param rxMtu       Pointer to maximum receive packet length. Populated by
 *                    this function
 * \param txMtu       Array of maximum transmit packet length per priority
 *                    supported by ethernet switch
 * \param macPort     Underlying MAC port.  `ENET_MAC_PORT_INV` for <em>virtual
 *                    switch ports</em>, or a valid MAC port id for <em>virtual
 *                    MAC ports</em>.  This MAC port number can be used as is
 *                    in Enet DMA APIs for directed or non-directed packets.
 */
void CpswProxy_attach(CpswProxy_Handle hProxy,
                      Enet_Type enetType,
                      Enet_Handle *pCpswHandle,
                      uint32_t *coreKey,
                      uint32_t *rxMtu,
                      uint32_t *txMtu,
                      Enet_MacPort *macPort);

/*!
 * \brief Attach to Ethernet Switch Remote Device with extended response
 *
 * Clients must first attach to the ethernet switch remote device.
 * CpswProxy_attachExtended() returns the core_key and id which are used as
 * params for all further client functions.
 *
 * For remote core clients that require only one rx/one tx and one dst MAC
 * address, CpswProxy_attachExtended() allows a single attach call to return all
 * the required params. Client can avoid further calls to alloctx/allocrx, etc.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy      Handle to Cpsw Proxy
 * \param enetType    Enet instance type
 * \param pCpswHandle Pointer to unique opaque handle populated by this function 
 * \param coreKey     Pointer to Core key populated by this function
 * \param rxMtu       Pointer to maximum receive packet length. Populated by
                      this function
 * \param txMtu       Array of maximum transmit packet length per priority
 *                    supported by ethernet switch
 * \param txPSILThreadId Pointer to allocated Tx Channel CPSW PSIL destination
 *                       thread id populated by this function
 * \param rxFlowStartIdx Pointer to allocated Rx Flow Index Base value populated
 *                       by this function:
 *                       Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowIdx      Pointer to allocated allocated Rx Flow Index offset
 *                       value populated by this function
 * \param macAddress     Pointer to allocated destination MAC address allocated
 *                       to remote core populated by this function
 * \param macPort     Underlying MAC port.  `ENET_MAC_PORT_INV` for <em>virtual
 *                    switch ports</em>, or a valid MAC port id for <em>virtual
 *                    MAC ports</em>.  This MAC port number can be used as is
 *                    in Enet DMA APIs for directed or non-directed packets.
 */
void CpswProxy_attachExtended(CpswProxy_Handle hProxy,
                              Enet_Type enetType,
                              Enet_Handle *pCpswHandle,
                              uint32_t *coreKey,
                              uint32_t *rxMtu,
                              uint32_t *txMtu,
                              uint32_t *txPSILThreadId,
                              uint32_t *rxFlowStartIdx,
                              uint32_t *rxFlowIdx,
                              uint8_t *macAddress,
                              Enet_MacPort *macPort);

/*!
 * \brief Detach from Ethernet Switch Remote Device
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 */
void CpswProxy_detach(CpswProxy_Handle hProxy,
                      Enet_Handle hEnet,
                      uint32_t coreKey);

/*!
 * \brief Alloc Tx Channel CPSW PSIL Destination thread id
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param txPSILThreadId Allocated Tx Channel CPSW PSIL Destination thread id
 *                       populated by this function
 */
void CpswProxy_allocTxCh(CpswProxy_Handle hProxy,
                         Enet_Handle hEnet,
                         uint32_t coreKey,
                         uint32_t *txPSILThreadId);

/*!
 * \brief Free Tx Channel CPSW PSIL Destination thread id
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param txChNum   Tx Channel CPSW PSIL Destination thread id to be freed
 */
void CpswProxy_freeTxCh(CpswProxy_Handle hProxy,
                        Enet_Handle hEnet,
                        uint32_t coreKey,
                        uint32_t txChNum);

/*!
 * \brief Alloc Rx flow Id
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx  Pointer to allocated Rx Flow Index Base value populated
 *                        by this function.
 *                        Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowIdx       Pointer to allocated allocated Rx flow Index offset
 *                        value  populated by this function
 */
void CpswProxy_allocRxFlow(CpswProxy_Handle hProxy,
                           Enet_Handle hEnet,
                           uint32_t coreKey,
                           uint32_t *rxFlowStartIdx,
                           uint32_t *rxFlowIdx);

/*!
 * \brief Free Rx flow Id
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx  Allocated Rx Flow Index Base value populated
 *                        by this function.
 *                        Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowIdx       Allocated Rx flow Index offset
 *                        value  populated by this function
 */
void CpswProxy_freeRxFlow(CpswProxy_Handle hProxy,
                          Enet_Handle hEnet,
                          uint32_t coreKey,
                          uint32_t rxFlowStartIdx,
                          uint32_t rxFlowIdx);

/*!
 * \brief Alloc Destination MAC address
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy     Handle to Cpsw Proxy
 * \param hEnet      Unique opaque handle returned by CpswProxy_attach() or
 *                   CpswProxy_attachExtended()
 * \param coreKey    Unique core_key returned by CpswProxy_attach() or
 *                   CpswProxy_attachExtended()
 * \param macAddress Destination MAC address. Populated by this function with
 *                   allocated DST MAC address
 */
void CpswProxy_allocMac(CpswProxy_Handle hProxy,
                        Enet_Handle hEnet,
                        uint32_t coreKey,
                        uint8_t *macAddress);

/*!
 * \brief Free Tx Channel CPSW PSIL Destination thread id
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy     Handle to Cpsw Proxy
 * \param hEnet      Unique opaque handle returned by CpswProxy_attach() or
 *                   CpswProxy_attachExtended()
 * \param coreKey    Unique core_key returned by CpswProxy_attach() or
 *                   CpswProxy_attachExtended()
 * \param macAddress Destination MAC address to be freed
 */
void CpswProxy_freeMac(CpswProxy_Handle hProxy,
                       Enet_Handle hEnet,
                       uint32_t coreKey,
                       const uint8_t *macAddress);

/*!
 * \brief Register Destination MAC address with the given flow index
 *
 * This function registers the destination MAC to the given rx flow index.
 * This causes all packets with the given destination MAC address to be 
 * routed to the given rx flow index.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  Flow Id from to which the traffic with the given
 *                         DST MAC address will be directed
 * \param macAddress Destination MAC address to be registered
 */
void CpswProxy_registerDstMacRxFlow(CpswProxy_Handle hProxy,
                                    Enet_Handle hEnet,
                                    uint32_t coreKey,
                                    uint32_t rxFlowStartIdx,
                                    uint32_t rxFlowOffsetIdx,
                                    const uint8_t *macAddress);

/*!
 * \brief Unregister Destination MAC address from the given flow index
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx Flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  Flow Id from to which the traffic with the given
 *                         DST MAC address will no longer be directed
 * \param macAddress   Destination MAC address to be unregistered
 */
void CpswProxy_unregisterDstMacRxFlow(CpswProxy_Handle hProxy,
                                      Enet_Handle hEnet,
                                      uint32_t coreKey,
                                      uint32_t rxFlowStartIdx,
                                      uint32_t rxFlowOffsetIdx,
                                      const uint8_t *macAddress);

/*!
 * \brief Register the given EtherType to the given rx flow id
 *
 * Any packets received with given EtherType mac will have the specific flow id.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx Flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  rxFlowOffsetIdx to which the EtherType packets be
 *                         directed
 * \param etherType Ethertype to be associated with the given rx flow id
 */
void CpswProxy_registerEthertypeRxFlow(CpswProxy_Handle hProxy,
                                       Enet_Handle hEnet,
                                       uint32_t coreKey,
                                       uint32_t rxFlowStartIdx,
                                       uint32_t rxFlowOffsetIdx,
                                       uint16_t etherType);

/*!
 * \brief Unregister the given EtherType to the given rx flow id
 *
 * Any packets received with given EtherType MAC will be directed to the
 * default flow.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx Flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  rxFlowOffsetIdx to which the EtherType packets
 *                         were directed
 * \param etherType Ethertype to be disassociated from the given rx flow id
 */
void CpswProxy_unregisterEthertypeRxFlow(CpswProxy_Handle hProxy,
                                         Enet_Handle hEnet,
                                         uint32_t coreKey,
                                         uint32_t rxFlowStartIdx,
                                         uint32_t rxFlowOffsetIdx,
                                         uint16_t etherType);

/*!
 * \brief Register Default Flow to the given flow index
 *
 * This function enables routing of default traffic (traffic not matching any
 * classifier with thread id configured) to the given rx flow_idx.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx Flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  Default Flow Id from to which the default flow will
 *                         no longer be directed
 */
void CpswProxy_registerDefaultRxFlow(CpswProxy_Handle hProxy,
                                     Enet_Handle hEnet,
                                     uint32_t coreKey,
                                     uint32_t rxFlowStartIdx,
                                     uint32_t rxFlowOffsetIdx);

/*!
 * \brief Unregister Default Flow from the given flow index.
 *
 * This function disables routing of default traffic (traffic not matching any
 * classifier with thread id configured) to the given rx flow_idx. Once disabled,
 * all default traffic will be routed to the reserved flow resulting in all
 * packets of default flow being dropped
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx    Rx Flow Index Base value.
 *                          Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx   Default Flow Id from to which the default flow will
 *                          no longer be directed
 */
void CpswProxy_unregisterDefaultRxFlow(CpswProxy_Handle hProxy,
                                       Enet_Handle hEnet,
                                       uint32_t coreKey,
                                       uint32_t rxFlowStartIdx,
                                       uint32_t rxFlowOffsetIdx);




/*!
 * \brief Register association of IPv4 address with MAC address by adding ARP
 *        entry in the master core
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param macAddr   MAC address with which the IPv4 address will be associated
 * \param ipv4Addr  IPv4 address to be added to ARP database
 */
void CpswProxy_registerIPV4Addr(CpswProxy_Handle hProxy,
                                Enet_Handle hEnet,
                                uint32_t coreKey,
                                uint8_t *macAddr,
                                uint8_t *ipv4Addr);

/*!
 * \brief Unregister association of IPv4 address with MAC address by removing
 *        ARP entry in the master core
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param ipv4Addr  IPv4 address to be unregistered
 */
void CpswProxy_unregisterIPV4Addr(CpswProxy_Handle hProxy,
                                  Enet_Handle hEnet,
                                  uint32_t coreKey,
                                  uint8_t *ipv4Addr);

/*!
 * \brief Add the given unicast macAddr as host port MAC address
 *
 * Any packets received with destination mac will be switched to the host port.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param macAddr   Unicast MAC address to be added to the switch address
 *                  resolution table as host port entry
 */
void CpswProxy_addHostPortEntry(CpswProxy_Handle hProxy,
                                Enet_Handle hEnet,
                                uint32_t coreKey,
                                const uint8_t *macAddr);


/*!
 * \brief Remove macAddress from the switch address resolution table
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param macAddr   MAC address to be deleted from the switch address resolution
 *                  table
 */
void CpswProxy_delAddrEntry(CpswProxy_Handle hProxy,
                            Enet_Handle hEnet,
                            uint32_t coreKey,
                            const uint8_t *macAddr);

/*!
 * \brief Add multicast address to receive filter.
 *
 * This function adds a multicast address to the receive filter.  Ethernet Firmware
 * differentiates multicast addresses as shared or exclusive.
 *
 * - Exclusive multicast address - Use is allowed only on a single remote client,
 *   the first one to request it.  Traffic received with exclusive address is
 *   routed to the remote client in hardware to the given RX flow index.
 * - Shared multicast address - Traffic received with shared address is fanned out
 *   to all remote clients that request it via virtual intercore interface. RX
 *   flow index is not relevant in this case.
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx Flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  Default Flow Id from to which the default flow will
 *                         no longer be directed
 * \param macAddress Multicast MAC address to be added to receive filter
 * \param vlanId     VLAN id
 *
 * \return Refer to \ref CpswProxy_ErrorCodes.
 */
int32_t CpswProxy_filterAddMac(CpswProxy_Handle hProxy,
                               Enet_Handle hEnet,
                               uint32_t coreKey,
                               uint32_t rxFlowStartIdx,
                               uint32_t rxFlowOffsetIdx,
                               const uint8_t *macAddress,
                               uint16_t vlanId);

/*!
 * \brief Delete multicast address from receive filter.
 *
 * This function deletes a multicast address to the receive filter which was
 * previous added via CpswProxy_addFilterAdddr().
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param rxFlowStartIdx   Rx Flow Index Base value.
 *                         Absolute RxFlowIdx = (rxFlowStartIdx + rxFlowIdx)
 * \param rxFlowOffsetIdx  Default Flow Id from to which the default flow will
 *                         no longer be directed
 * \param macAddress Multicast MAC address to be deleted from receive filter
 * \param vlanId     VLAN id
 *
 * \return Refer to \ref CpswProxy_ErrorCodes.
 */
int32_t CpswProxy_filterDelMac(CpswProxy_Handle hProxy,
                               Enet_Handle hEnet,
                               uint32_t coreKey,
                               uint32_t rxFlowStartIdx,
                               uint32_t rxFlowOffsetIdx,
                               const uint8_t *macAddress,
                               uint16_t vlanId);

/*!
 * \brief Invoke Cpsw IOCTL
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * NOTE: Due to limitation in IPC, maximum size of inArgs and outArgs is 128 bytes
 * If Cpsw IOCTL iargs_len/outargs_len is greater than 128 bytes for a specific 
 * IOCTL cmd then CpswProxy_ioctl will fail
 *
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param cmd       CPSW IOCTL CMD id. Refer CPSW LLD documentation for list of
 *                  CPSW LLD IOCTLs
 * \param prms      CPSW IOCTL params. Refer CPSW LLD documentation for details
 *                  of this structure
 */
void CpswProxy_ioctl(CpswProxy_Handle hProxy,
                     Enet_Handle hEnet,
                     uint32_t coreKey,
                     uint32_t cmd,
                     Enet_IoctlPrms *prms);

/*!
 * \brief Query if the link for PHY associated with the given MAC Port is up
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param portNum   MAC port for which PHY link status is queried
 */
bool CpswProxy_isPhyLinked(CpswProxy_Handle hProxy,
                           Enet_Handle hEnet,
                           uint32_t coreKey,
                           Enet_MacPort portNum);

/*!
 * \brief Send custom notification info from client to server
 *
 * The buffer notifyInfo of notifyInfoLength will be sent to the server
 * The client and server application interpretation of the notify info should
 * match. The proxy just passes the info to the remote core
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param notifyId         Notify id
 * \param notifyInfo       Notify info to be sent to server
 * \param notifyInfoLength Notify info length
 */
void CpswProxy_sendNotify(CpswProxy_Handle hProxy,
                          Enet_Handle hEnet,
                          uint32_t coreKey,
                          uint8_t notifyId,
                          uint8_t *notifyInfo,
                          uint32_t notifyInfoLength);

/*!
 * \brief Register remote core's timer for synchronization
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * The timerId is used to indicate Ethfw about which timer's event is to be routed
 * to CPTS hardware push via Timesync router(TSR).
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param timerId   Input Id number of timer in TSR
 * \param hwPushNum Hardware push number of CPTS
 */
void CpswProxy_registerRemoteTimer(CpswProxy_Handle hProxy,
                                   Enet_Handle hEnet,
                                   uint32_t coreKey,
                                   uint8_t timerId,
                                   uint8_t hwPushNum);

/*!
 * \brief Unregister remote core's timer for synchronization
 *
 * Note: The API will send the RPC msg, block for response and if the response
 * status is not success will abort execution.
 * The API will be modified to return error status to allow the application to
 * handle the error in next version.
 *
 * The timerId is used to indicate Ethfw to stop routing done
 * via Timesync router(TSR).
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param hwPushNum Hardware push number of CPTS
 */
void CpswProxy_unregisterRemoteTimer(CpswProxy_Handle hProxy,
                                     Enet_Handle hEnet,
                                     uint32_t coreKey,
                                     uint8_t hwPushNum);

/*!
 * \brief Register hardware push notification callback
 *
 * \param cbFxn     Callback function to be called when event occurs
 * \param cbArg     Callback arguments
 *
 * \return status   CPSWPROXY_SOK if registered callback successfully
 *                  CPSWPROXY_EALREADYOPEN if callback is already registered.
 *                  CPSWPROXY_EBADARGS if invalid input arguments
 */
int32_t CpswProxy_registerHwPushNotifyCb(CpswRemoteNotifyService_hwPushNotifyCbFxn cbFxn,
                                         void *cbArg);

/*!
 * \brief Unregister hardware push notification callback
 */
void CpswProxy_unregisterHwPushNotifyCb(void);

/*!
 * \brief Set promiscuous mode.
 *
 * \param hProxy    Handle to Cpsw Proxy
 * \param hEnet     Unique opaque handle returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param coreKey   Unique core_key returned by CpswProxy_attach() or
 *                  CpswProxy_attachExtended()
 * \param enable    Promiscuous mode (enable or disable)
 */
void CpswProxy_setPromiscMode(CpswProxy_Handle hProxy,
                              Enet_Handle hEnet,
                              uint32_t coreKey,
                              bool enable);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __CPSWPROXY_H__ */
