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

#ifndef __CPSWPROXYSERVER_H__
#define __CPSWPROXYSERVER_H__

#include <stdint.h>
#include <ethremotecfg/server/include/ethremotecfg_server.h>
#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/examples/utils/include/enet_mcm.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup CPSW_PROXY_SERVER_API Ethernet Switch Proxy Server APIs
 *
 * \brief This section contains APIs for CPSW Proxy Server APIs
 *
 * The CPSW Proxy Server resides on the master core and enables clients on
 * remote cores to configure the Ethernet Switch. The CPSW Proxy Server is the
 * application interface to the ethernet remote device server.
 *
 * The application configures and instantiates a CPSW Proxy Server instance.
 * Once instantiated the CPSW will listen to, process and respond to
 * CPSW_PROXY_CLIENT messages from remote cores.
 *
 *  @{
 */
/* @} */

/*!
 * \addtogroup CPSW_PROXY_SERVER_API
 * @{
 */

/*!
 * \anchor CpswProxyServer_ErrorCodes
 * \name CpswProxyServer Error Codes
 *
 * Error codes returned by the CPSW Proxy server APIs.
 *
 * @{
 */

/* Below error codes are aligned with CSL's and Enet LLD's to maintain
 * consistency and avoid error code conversion */

/*! \brief Success. */
#define CPSWPROXYSERVER_SOK                           (0)

/*! \brief Operation in progress. */
#define CPSWPROXYSERVER_SINPROGRESS                   (1)

/*! \brief Generic failure error condition (typically caused by hardware). */
#define CPSWPROXYSERVER_EFAIL                         (-1)

/*! \brief Bad arguments (i.e. NULL pointer). */
#define CPSWPROXYSERVER_EBADARGS                      (-2)

/*! \brief Invalid parameters (i.e. value out-of-range). */
#define CPSWPROXYSERVER_EINVALIDPARAMS                (-3)

/*! \brief Time out while waiting for a given condition to happen. */
#define CPSWPROXYSERVER_ETIMEOUT                      (-4)

/*! \brief Allocation failure. */
#define CPSWPROXYSERVER_EALLOC                        (-8)

/*! \brief Unexpected condition occurred (sometimes unrecoverable). */
#define CPSWPROXYSERVER_EUNEXPECTED                   (-9)

/*! \brief The resource is currently busy performing an operation. */
#define CPSWPROXYSERVER_EBUSY                         (-10)

/*! \brief Already open error. */
#define CPSWPROXYSERVER_EALREADYOPEN                  (-11)

/*! \brief Operation not permitted. */
#define CPSWPROXYSERVER_EPERM                         (-12)

/*! \brief Operation not supported. */
#define CPSWPROXYSERVER_ENOTSUPPORTED                 (-13)

/*! \brief Resource not found. */
#define CPSWPROXYSERVER_ENOTFOUND                     (-14)

/*! \brief Unknown IOCTL. */
#define CPSWPROXYSERVER_EUNKNOWNIOCTL                 (-15)

/*! \brief Malformed IOCTL (args pointer or size not as expected). */
#define CPSWPROXYSERVER_EMALFORMEDIOCTL               (-16)

/*! @} */

/*! Maximum number of MAC ports */
#define CPSWPROXYSERVER_MAC_PORT_MAX                  (8U)

/*! Size of shared multicast address table */
#define CPSWPROXYSERVER_SHARED_MCAST_LIST_LEN         (8U)

/*! Size of reserved multicast address table */
#define CPSWPROXYSERVER_RSVD_MCAST_LIST_LEN           (4U)

/*!
 * \brief Application callback function pointer to initialize Ethernet Firmware data
 *
 * When a client connection from remote core to  cpsw proxy server is
 * established, the server will invoke this application callback to populate
 * firmware info which is exported as remote device data to the remote core
 * client.
 *
 * \param host_id       Remote Core Id
 * \param eth_dev_data  Firmware device data to be populated
 */
typedef void  (*CpswProxyServer_InitEthfwDeviceDataCb)(uint32_t host_id,
                                                       struct rpmsg_kdrv_ethswitch_device_data *eth_dev_data);

/*!
 * \brief Application callback function pointer to get Multiclient Manager (MCM)
 *        command mailbox.
 *
 * The MCM manages access to single CPSW LLD handle across multiple clients on 
 * both remote core and local core.
 *
 * The CPSW Proxy server needs the MCM command interface to perform ATTACH.
 * The MCM command interface is obtained by invoking this application callback.
 *
 * \param enetType         Enet instance type
 * \param pMcmCmdIfHandle  Pointer to MCM command interface structure which will
 *                         be populated by application
 */
typedef void  (*CpswProxyServer_GetMcmCmdIfCb)(Enet_Type  enetType, EnetMcm_CmdIf  **pMcmCmdIfHandle);

/*!
 * \brief Application Callback function pointer to handle custom notification
 *        from remote client
 *
 * This is application handler for custom client to server notification from
 * remote cores.
 * The proxy layer just passes the notify info and notify_info_len.
 * The client and server application interpretation of the custom notify info
 * should match.
 *
 * \param host_id      Remote Core IPC core id
 * \param hEnet        Handle to CPSW
 * \param enetType     Enet instance type
 * \param notifyid     Custom notify id. Will be #RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_CUSTOM
 * \param notify_info  Notify info
 * \param notify_info_len Notify info length
 */
typedef void  (*CpswProxyServer_NotifyCb)(uint32_t host_id,
                                          Enet_Handle hEnet,
                                          Enet_Type enetType,
                                          uint32_t core_key,
                                          enum rpmsg_kdrv_ethswitch_client_notify_type notifyid,
                                          uint8_t *notify_info,
                                          uint32_t notify_info_len);

/*!
 * \brief Cpsw Proxy Server Virtual Port Configuration structure
 */
typedef struct CpswProxyServer_VirtPortCfg_s
{
    /*! Remote Core Id that can attach */
    uint32_t remoteCoreId;

    /*! Virtual port id */
    EthRemoteCfg_VirtPort portId;
} CpswProxyServer_VirtPortCfg;

/*!
 * \brief Filter add shared multicast callback.
 *
 * Application callback function called when a remote client requests the addition of
 * a shared multicast address to the filter.
 *
 * \param macAddr    Multicast address being added
 * \param coreId     Remote core id which originated the multicast 'add' request
 */
typedef void (*CpswProxyServer_FilterAddMacSharedCb)(const uint8_t *macAddr,
                                                     const uint8_t coreId);

/*!
 * \brief Filter delete shared multicast callback.
 *
 * Application callback function called when a remote client requests the deletion of
 * a shared multicast address from the filter.
 *
 * \param macAddr    Multicast address being added
 * \param coreId     Remote core id which originated the multicast 'remove' request
 */
typedef void (*CpswProxyServer_FilterDelMacSharedCb)(const uint8_t *macAddr,
                                                     const uint8_t coreId);

/*!
 * \brief Ethernet Firmware shared multicast fanout configuration.
 *
 * Ethernet Firmware configuration parameters for shared multicast fanout.
 */
typedef struct CpswProxyServer_SharedMcastCfg_s
{
    /*! Shared multicast address table */
    uint8_t macAddrList[CPSWPROXYSERVER_SHARED_MCAST_LIST_LEN][ENET_MAC_ADDR_LEN];

    /*! Number of multicast address actually populated in the shared table.
     *  Must be < \ref CPSWPROXYSERVER_SHARED_MCAST_LIST_LEN */
    uint32_t numMacAddr;

    /*! Notification function called when a remote client adds a multicast to the filter. */
    CpswProxyServer_FilterAddMacSharedCb filterAddMacSharedCb;

    /*! Notification function called when a remote client deletes a multicast from the filter. */
    CpswProxyServer_FilterDelMacSharedCb filterDelMacSharedCb;
} CpswProxyServer_SharedMcastCfg;

/*!
 * \brief Ethernet Firmware reserved multicast configuration.
 *
 * Ethernet Firmware configuration parameters for reserved multicast addresses, that is,
 * multicast addresses that are restricted to Ethernet Firmware only.  Requests from
 * remote clients to add any of these multicast addresses to the filter will be rejected.
 */
typedef struct CpswProxyServer_RsvdMcastCfg_s
{
    /*! Reserved multicast address table */
    uint8_t macAddrList[CPSWPROXYSERVER_RSVD_MCAST_LIST_LEN][ENET_MAC_ADDR_LEN];

    /*! Number of multicast address actually populated in the reserved address table.
     *  Must be < \ref CPSWPROXYSERVER_RSVD_MCAST_LIST_LEN */
    uint32_t numMacAddr;
} CpswProxyServer_RsvdMcastCfg;

/*!
 * \brief Cpsw Proxy Server Remote Configuration structure
 *
 * Structure passed by application to configure the CPSW Proxy server.
 */
typedef struct CpswProxyServer_Config_s
{
    /*! Application callback to populate Ethernet Remote Device data */
    CpswProxyServer_InitEthfwDeviceDataCb initEthfwDeviceDataCb;

    /*! Application callback to get MCM command interface */
    CpswProxyServer_GetMcmCmdIfCb         getMcmCmdIfCb;

    /*! Application callback to handle custom notify from client */
    CpswProxyServer_NotifyCb              notifyCb;

    /*! IPC RpMsg endpoint id. This is the local endpoint at which proxy
     *  server will listen for msgs */
    uint32_t rpmsgEndPointId;

    /*! AUTOSAR Ethernet Device RpMsg endpoint id */
    uint32_t autosarEthDeviceEndPointId;

    /*! Remote Core Id for AUTOSAR core */
    uint32_t autosarEthDriverRemoteCoreId;

    /*! Virtual port configuration */
    EthRemoteCfg_VirtPort autosarEthDriverVirtPort;

    /*! CPSW type for which notify service is enabled */
    Enet_Type notifyServiceCpswType;

    /*! Remote Core Id for Notification service */
    uint32_t notifyServiceRemoteCoreId[ETHREMOTECFG_SERVER_MAX_INSTANCES];

    /*! Virtual port configuration */
    CpswProxyServer_VirtPortCfg virtPortCfg[ETHREMOTECFG_SERVER_MAX_INSTANCES];

    /*! Number of remote virtual ports that remotes cores can attach to */
    uint32_t numVirtPorts;

    /*! Enabled MAC ports */
    Enet_MacPort macPort[CPSWPROXYSERVER_MAC_PORT_MAX];

    /*! Number of MAC ports being enabled */
    uint32_t numMacPorts;

    /*! Default VLAN id to be used for MAC ports configured in MAC-only mode */
    uint16_t dfltVlanIdMacOnlyPorts;

    /*! Default VLAN id to be used for MAC ports configured in switch mode (non MAC-only) */
    uint16_t dfltVlanIdSwitchPorts;

    /*! Shared multicast configuration */
    CpswProxyServer_SharedMcastCfg sharedMcastCfg;

    /*! Reserved multicast configuration */
    CpswProxyServer_RsvdMcastCfg rsvdMcastCfg;
} CpswProxyServer_Config_t;

/*!
 * \brief Cpsw proxy server initialization function
 *
 * \param cfg  Cpsw Proxy Server configuration
 */
int32_t CpswProxyServer_init(CpswProxyServer_Config_t *cfg);

/*!
 * \brief Start the Cpsw proxy server
 *
 * Starts the remote device framework.
 *
 * \return Refer to \ref CpswProxyServer_ErrorCodes.
 */
int32_t  CpswProxyServer_start(void);

/* @} */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __CPSWPROXYSERVER_H__ */
