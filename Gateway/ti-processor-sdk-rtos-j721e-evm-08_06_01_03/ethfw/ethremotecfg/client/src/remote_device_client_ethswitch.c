/*
 *
 * Copyright (c) 2017 Texas Instruments Incorporated
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
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#ifdef QNX_OS
#include <stdlib.h>
#include <assert.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/slogcodes.h>
#endif
#include <ti/osal/osal.h>
#include <ethremotecfg/protocol/rpmsg-kdrv-transport-ethswitch.h>
#include <client-rtos/remote-device.h>
#include <ethremotecfg/client/include/ethremotecfg_client.h>
#include <ti/drv/enet/enet.h>

#ifdef QNX_OS
static void slog_printf(const char *pcString, ...);
#define System_printf slog_printf

static void slog_printf(const char *pcString, ...)
{
    char printBuffer[256];
    va_list arguments;

    if (256 < strlen(pcString))
    {
        assert(false);
    }

    /* Start the varargs processing */
    va_start(arguments, pcString);
    vsnprintf(printBuffer, sizeof(printBuffer), pcString, arguments);

    slogf(_SLOGC_NETWORK, _SLOG_INFO, printBuffer);

    /* End the varargs processing */
    va_end(arguments);
}
#else
// TODO: Need to replace with Ipc_Trace_printf
#define System_printf printf
#endif

typedef struct rdevEthSwitchClientMessageList_s
{
    struct rpmsg_kdrv_device_header hdr;
    rdevEthSwitchServerMessageList_t rdevEthSwitchMsg;
} __attribute__((packed)) rdevEthSwitchClientMessageList_t;

#define MAX_RDEV_ETH_SWITCH_CLIENT_MESSAGE      32
rdevEthSwitchClientMessageList_t g_rdevEthSwitchClientMessageList[MAX_RDEV_ETH_SWITCH_CLIENT_MESSAGE];
uint32_t g_rdevEthSwitchClientMessageListIndex = 0;

uint32_t rdevEthSwitchClient_printText(void *priv,
                                       void *data)
{
    struct rpmsg_kdrv_device_header *hdr = (struct rpmsg_kdrv_device_header *)data;
    struct rpmsg_kdrv_ethswitch_s2c_notify *msg = (struct rpmsg_kdrv_ethswitch_s2c_notify *)(&hdr[1]);

    System_printf("%s: message (hdr = %u) %s\n", __func__, msg->header.message_type, msg->data);
    return 0;
}

static int32_t rdevEthSwitchClientFreeMsg(void *priv,
                                          void *data,
                                          uint32_t len)
{
    return 0;
}

int32_t rdevEthSwitchClient_sendNotify(uint32_t device_id,
                                       u64 id,
                                       u32 core_key,
                                       enum rpmsg_kdrv_ethswitch_client_notify_type notify_id,
                                       uint8_t *notify_info,
                                       uint32_t notify_info_len)
{
    int32_t ret;
    rdevEthSwitchClientMessageList_t *clientMsg = &g_rdevEthSwitchClientMessageList[g_rdevEthSwitchClientMessageListIndex];
    g_rdevEthSwitchClientMessageListIndex++;
    if (g_rdevEthSwitchClientMessageListIndex == MAX_RDEV_ETH_SWITCH_CLIENT_MESSAGE)
    {
        g_rdevEthSwitchClientMessageListIndex = 0;
    }
    struct rpmsg_kdrv_ethswitch_c2s_notify *msg = &clientMsg->rdevEthSwitchMsg.c2s_notify;

    if (notify_info_len <= sizeof(msg->notify_info))
    {
        msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_C2S_NOTIFY;
        msg->info.id = id;
        msg->info.core_key = core_key;
        msg->notifyid = notify_id;
        memcpy(msg->notify_info, notify_info, notify_info_len);
        msg->notify_info_len = notify_info_len;
        ret = appRemoteDeviceSendMessage(device_id, clientMsg, sizeof(*clientMsg), NULL, rdevEthSwitchClientFreeMsg);
    }
    else
    {
        ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
    }

    return ret;
}

int32_t rdevEthSwitchClient_connect(rdevEthSwitchClientInitPrms_t *initPrms)
{
    int32_t ret = 0;
    app_remote_device_device_connect_prm_t prm;
    uint32_t dataFilledLen = 0;

    appRemoteDeviceDeviceConnectParamsInit(&prm);

    ret = snprintf(prm.device_name, APP_REMOTE_DEVICE_CONNECT_NAME_LEN, "%s", initPrms->device_name);
    if (ret >= 0)
    {
        ret = 0;
        prm.message_cb = initPrms->cbHandler;
        prm.message_cb_priv = NULL;
        ret = appRemoteDeviceConnect(&prm, &initPrms->device_id);
    }

    if ((ret == 0) && (initPrms->device_id != APP_REMOTE_DEVICE_DEVICE_ID_EAGAIN))
    {
        ret = appRemoteDeviceGetType(initPrms->device_id, &initPrms->device_type);
    }

    if ((ret == 0) && (initPrms->device_id != APP_REMOTE_DEVICE_DEVICE_ID_EAGAIN))
    {
        ret = appRemoteDeviceGetData(initPrms->device_id,
                                     (uint8_t *)&initPrms->eth_device_data,
                                     sizeof(initPrms->eth_device_data),
                                     &dataFilledLen);
        if (ret == 0)
        {
            assert(dataFilledLen == sizeof(initPrms->eth_device_data));
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_disconnect(uint32_t device_id)
{
    int32_t ret;

    ret = appRemoteDeviceDisconnect(device_id);

    return ret;
}

int32_t rdevEthSwitchClient_attach(uint32_t device_id,
                                   uint8_t enetType,
                                   uint64_t *id,
                                   uint32_t *core_key,
                                   uint32_t *rx_mtu,
                                   uint32_t tx_mtu[],
                                   uint32_t tx_mtu_array_size,
                                   uint32_t *pFeatures,
                                   uint32_t *mac_only_port)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_attach_request *msg = &clientMsg.rdevEthSwitchMsg.attach_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t attach_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_ATTACH;
    msg->cpsw_type = enetType;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &attach_reponse, sizeof(attach_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(attach_reponse.hdr) + sizeof(attach_reponse.rdevEthSwitchMsg.attach_res)));
        if (attach_reponse.rdevEthSwitchMsg.attach_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            *id = attach_reponse.rdevEthSwitchMsg.attach_res.id;
            *core_key = attach_reponse.rdevEthSwitchMsg.attach_res.core_key;
            *rx_mtu = attach_reponse.rdevEthSwitchMsg.attach_res.rx_mtu;
            *pFeatures = attach_reponse.rdevEthSwitchMsg.attach_res.features;
            *mac_only_port = attach_reponse.rdevEthSwitchMsg.attach_res.mac_only_port;
            if (tx_mtu_array_size >= ENET_ARRAYSIZE(attach_reponse.rdevEthSwitchMsg.attach_res.tx_mtu))
            {
                uint32_t i;

                for (i = 0; i < ENET_ARRAYSIZE(attach_reponse.rdevEthSwitchMsg.attach_res.tx_mtu); i++)
                {
                    tx_mtu[i] = attach_reponse.rdevEthSwitchMsg.attach_res.tx_mtu[i];
                }
            }
            else
            {
                ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
            }
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_attachext(uint32_t device_id,
                                      uint8_t enetType,
                                      uint64_t *id,
                                      uint32_t *core_key,
                                      uint32_t *rx_mtu,
                                      uint32_t tx_mtu[],
                                      uint32_t tx_mtu_array_size,
                                      uint32_t *pFeatures,
                                      uint32_t *tx_cpsw_psil_dst_id,
                                      uint32_t *rx_flow_allocidx,
                                      uint8_t *mac_address,
                                      uint32_t mac_address_len,
                                      uint32_t *mac_only_port)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_attach_request *msg = &clientMsg.rdevEthSwitchMsg.attach_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t attach_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_ATTACH_EXT;
    msg->cpsw_type = enetType;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &attach_reponse, sizeof(attach_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(attach_reponse.hdr) + sizeof(attach_reponse.rdevEthSwitchMsg.attach_ext_res)));
        if (attach_reponse.rdevEthSwitchMsg.attach_ext_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            *id = attach_reponse.rdevEthSwitchMsg.attach_ext_res.id;
            *core_key = attach_reponse.rdevEthSwitchMsg.attach_ext_res.core_key;
            *rx_mtu = attach_reponse.rdevEthSwitchMsg.attach_ext_res.rx_mtu;
            *pFeatures = attach_reponse.rdevEthSwitchMsg.attach_ext_res.features;
            *tx_cpsw_psil_dst_id = attach_reponse.rdevEthSwitchMsg.attach_ext_res.tx_cpsw_psil_dst_id;
            *rx_flow_allocidx = attach_reponse.rdevEthSwitchMsg.attach_ext_res.alloc_flow_idx;
            *mac_only_port = attach_reponse.rdevEthSwitchMsg.attach_ext_res.mac_only_port;
            if (mac_address_len >= ENET_ARRAYSIZE(attach_reponse.rdevEthSwitchMsg.attach_ext_res.mac_address))
            {
                memcpy(mac_address,
                       attach_reponse.rdevEthSwitchMsg.attach_ext_res.mac_address,
                       sizeof(attach_reponse.rdevEthSwitchMsg.attach_ext_res.mac_address));
            }
            else
            {
                ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
            }

            if (ret == 0)
            {
                if (tx_mtu_array_size >= ENET_ARRAYSIZE(attach_reponse.rdevEthSwitchMsg.attach_ext_res.tx_mtu))
                {
                    uint32_t i;

                    for (i = 0; i < ENET_ARRAYSIZE(attach_reponse.rdevEthSwitchMsg.attach_ext_res.tx_mtu); i++)
                    {
                        tx_mtu[i] = attach_reponse.rdevEthSwitchMsg.attach_ext_res.tx_mtu[i];
                    }
                }
                else
                {
                    ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
                }
            }
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_alloctx(uint32_t device_id,
                                    u64 id,
                                    u32 core_key,
                                    u32 *tx_cpsw_psil_dst_id)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_alloc_request *msg = &clientMsg.rdevEthSwitchMsg.alloc_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t alloc_tx_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_ALLOC_TX;
    msg->info.id = id;
    msg->info.core_key = core_key;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &alloc_tx_reponse, sizeof(alloc_tx_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(alloc_tx_reponse.hdr) + sizeof(alloc_tx_reponse.rdevEthSwitchMsg.alloc_tx_res)));
        if (alloc_tx_reponse.rdevEthSwitchMsg.alloc_tx_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            *tx_cpsw_psil_dst_id = alloc_tx_reponse.rdevEthSwitchMsg.alloc_tx_res.tx_cpsw_psil_dst_id;
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_allocrx(uint32_t device_id,
                                    uint64_t id,
                                    uint32_t core_key,
                                    uint32_t *rx_flow_allocidx)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_alloc_request *msg = &clientMsg.rdevEthSwitchMsg.alloc_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t alloc_rx_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_ALLOC_RX;
    msg->info.id = id;
    msg->info.core_key = core_key;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &alloc_rx_reponse, sizeof(alloc_rx_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(alloc_rx_reponse.hdr) + sizeof(alloc_rx_reponse.rdevEthSwitchMsg.alloc_rx_res)));
        if (alloc_rx_reponse.rdevEthSwitchMsg.alloc_rx_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            *rx_flow_allocidx = alloc_rx_reponse.rdevEthSwitchMsg.alloc_rx_res.alloc_flow_idx;
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_registerrxdefault(uint32_t device_id,
                                              uint64_t id,
                                              uint32_t core_key,
                                              uint32_t default_flow_idx)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_register_rx_default_request *msg = &clientMsg.rdevEthSwitchMsg.register_rx_default_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t register_rx_default_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_REGISTER_DEFAULTFLOW;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->default_flow_idx = default_flow_idx;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &register_rx_default_response, sizeof(register_rx_default_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(register_rx_default_response.hdr) + sizeof(register_rx_default_response.rdevEthSwitchMsg.register_rx_default_res)));
        ret = register_rx_default_response.rdevEthSwitchMsg.register_rx_default_res.info.status;
    }

    return ret;
}

int32_t rdevEthSwitchClient_allocmac(uint32_t device_id,
                                     uint64_t id,
                                     uint32_t core_key,
                                     uint8_t *mac_address,
                                     uint32_t mac_address_len)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_alloc_request *msg = &clientMsg.rdevEthSwitchMsg.alloc_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t alloc_mac_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_ALLOC_MAC;
    msg->info.id = id;
    msg->info.core_key = core_key;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &alloc_mac_reponse, sizeof(alloc_mac_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(alloc_mac_reponse.hdr) + sizeof(alloc_mac_reponse.rdevEthSwitchMsg.alloc_mac_res)));
        if (alloc_mac_reponse.rdevEthSwitchMsg.alloc_mac_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            if (mac_address_len >= ENET_ARRAYSIZE(alloc_mac_reponse.rdevEthSwitchMsg.alloc_mac_res.mac_address))
            {
                memcpy(mac_address, alloc_mac_reponse.rdevEthSwitchMsg.alloc_mac_res.mac_address, sizeof(alloc_mac_reponse.rdevEthSwitchMsg.alloc_mac_res.mac_address));
            }
            else
            {
                ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
            }
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_registermac(uint32_t device_id,
                                        uint64_t id,
                                        uint32_t core_key,
                                        uint32_t flow_idx,
                                        uint8_t *mac_address)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_register_mac_request *msg = &clientMsg.rdevEthSwitchMsg.register_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t register_mac_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_REGISTER_MAC;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->flow_idx = flow_idx;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &register_mac_reponse, sizeof(register_mac_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(register_mac_reponse.hdr) + sizeof(register_mac_reponse.rdevEthSwitchMsg.register_mac_res)));
        if (register_mac_reponse.rdevEthSwitchMsg.register_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_unregistermac(uint32_t device_id,
                                          uint64_t id,
                                          uint32_t core_key,
                                          uint32_t flow_idx,
                                          uint8_t *mac_address)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_unregister_mac_request *msg = &clientMsg.rdevEthSwitchMsg.unregister_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t unregister_mac_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_MAC;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->flow_idx = flow_idx;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &unregister_mac_reponse, sizeof(unregister_mac_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(unregister_mac_reponse.hdr) + sizeof(unregister_mac_reponse.rdevEthSwitchMsg.unregister_mac_res)));
        if (unregister_mac_reponse.rdevEthSwitchMsg.unregister_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_unregisterrxdefault(uint32_t device_id,
                                                uint64_t id,
                                                uint32_t core_key,
                                                uint32_t default_flow_idx)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_unregister_rx_default_request *msg = &clientMsg.rdevEthSwitchMsg.unregister_rx_default_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t unregister_rx_default_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_DEFAULTFLOW;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->default_flow_idx = default_flow_idx;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &unregister_rx_default_reponse, sizeof(unregister_rx_default_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(unregister_rx_default_reponse.hdr) + sizeof(unregister_rx_default_reponse.rdevEthSwitchMsg.unregister_rx_default_res)));
        if (unregister_rx_default_reponse.rdevEthSwitchMsg.unregister_rx_default_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_freemac(uint32_t device_id,
                                    uint64_t id,
                                    uint32_t core_key,
                                    uint8_t *mac_address)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_free_mac_request *msg = &clientMsg.rdevEthSwitchMsg.free_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t free_mac_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_FREE_MAC;
    msg->info.id = id;
    msg->info.core_key = core_key;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &free_mac_response, sizeof(free_mac_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(free_mac_response.hdr) + sizeof(free_mac_response.rdevEthSwitchMsg.free_mac_res)));
        if (free_mac_response.rdevEthSwitchMsg.free_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_freetx(uint32_t device_id,
                                   uint64_t id,
                                   uint32_t core_key,
                                   uint32_t tx_cpsw_psil_dst_id)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_free_tx_request *msg = &clientMsg.rdevEthSwitchMsg.free_tx_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t free_tx_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, rdevEthSwitchMsg) == sizeof(struct rpmsg_kdrv_device_header));
    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_FREE_TX;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->tx_cpsw_psil_dst_id = tx_cpsw_psil_dst_id;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &free_tx_response, sizeof(free_tx_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(free_tx_response.hdr) + sizeof(free_tx_response.rdevEthSwitchMsg.free_tx_res)));
        if (free_tx_response.rdevEthSwitchMsg.free_tx_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_freerx(uint32_t device_id,
                                   uint64_t id,
                                   uint32_t core_key,
                                   uint32_t alloc_flow_idx)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_free_rx_request *msg = &clientMsg.rdevEthSwitchMsg.free_rx_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t free_rx_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_FREE_RX;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->alloc_flow_idx = alloc_flow_idx;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &free_rx_response, sizeof(free_rx_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(free_rx_response.hdr) + sizeof(free_rx_response.rdevEthSwitchMsg.free_rx_res)));
        if (free_rx_response.rdevEthSwitchMsg.free_rx_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_detach(uint32_t device_id,
                                   uint64_t id,
                                   uint32_t core_key)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_detach_request *msg = &clientMsg.rdevEthSwitchMsg.detach_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t detach_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_DETACH;
    msg->info.id = id;
    msg->info.core_key = core_key;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &detach_response, sizeof(detach_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(detach_response.hdr) + sizeof(detach_response.rdevEthSwitchMsg.detach_res)));
        if (detach_response.rdevEthSwitchMsg.detach_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_ioctl(uint32_t device_id,
                                  uint64_t id,
                                  uint32_t core_key,
                                  uint32_t cmd,
                                  const void *inargs,
                                  uint32_t inargs_len,
                                  void *outargs,
                                  uint32_t outargs_len)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_ioctl_request *msg = &clientMsg.rdevEthSwitchMsg.ioctl_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t ioctl_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    if (inargs_len <= sizeof(msg->inargs))
    {
        memset(&clientMsg, 0, sizeof(clientMsg));
        msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_IOCTL;
        msg->info.id = id;
        msg->info.core_key = core_key;
        msg->cmd = cmd;
        msg->inargs_len = inargs_len;
        memcpy(msg->inargs, inargs, inargs_len);
        msg->outargs_len = outargs_len;
        ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &ioctl_response, sizeof(ioctl_response), &respMsgSize);
    }
    else
    {
        ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
    }

    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(ioctl_response.hdr) + sizeof(ioctl_response.rdevEthSwitchMsg.ioctl_res)));
        if (ioctl_response.rdevEthSwitchMsg.ioctl_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            memcpy(outargs, ioctl_response.rdevEthSwitchMsg.ioctl_res.outargs, outargs_len);
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_regwr(uint32_t device_id,
                                  uint32_t regaddr,
                                  uint32_t regval,
                                  uint32_t *post_wr_regval)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_regwr_request *msg = &clientMsg.rdevEthSwitchMsg.regwr_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t regwr_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_REGWR;
    msg->regaddr = regaddr;
    msg->regval = regval;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &regwr_response, sizeof(regwr_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(regwr_response.hdr) + sizeof(regwr_response.rdevEthSwitchMsg.regwr_res)));
        if (regwr_response.rdevEthSwitchMsg.regwr_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            *post_wr_regval = regwr_response.rdevEthSwitchMsg.regwr_res.regval;
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_regrd(uint32_t device_id,
                                  uint32_t regaddr,
                                  uint32_t *pregval)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_regrd_request *msg = &clientMsg.rdevEthSwitchMsg.regrd_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t regrd_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_REGRD;
    msg->regaddr = regaddr;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &regrd_response, sizeof(regrd_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(regrd_response.hdr) + sizeof(regrd_response.rdevEthSwitchMsg.regrd_res)));
        if (regrd_response.rdevEthSwitchMsg.regrd_res.info.status == RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            *pregval = regrd_response.rdevEthSwitchMsg.regrd_res.regval;
        }
        else
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_sendping(uint32_t device_id,
                                     char *ping_msg,
                                     uint32_t ping_len,
                                     char *respMsg,
                                     uint32_t respMaxLen)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_ping_request *msg = &clientMsg.rdevEthSwitchMsg.ping_req;
    rdevEthSwitchClientMessageList_t ping_response;
    int32_t ret = 0;
    uint32_t respMsgSize;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);

    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_PING_REQUEST;
    if (ping_len > sizeof(msg->data))
    {
        ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
    }

    if (0 == ret)
    {
        memcpy(msg->data, ping_msg, ping_len);
        ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &ping_response, sizeof(ping_response), &respMsgSize);
        assert(respMsgSize <= respMaxLen);
        assert(respMsgSize == (sizeof(ping_response.hdr) + sizeof(ping_response.rdevEthSwitchMsg.ping_res)));
        memcpy(respMsg, ping_response.rdevEthSwitchMsg.ping_res.data, ping_len);
    }

    return ret;
}

int32_t rdevEthSwitchClient_ipv4macregister(uint32_t device_id,
                                            uint64_t id,
                                            uint32_t core_key,
                                            uint8_t *mac_address,
                                            uint8_t *ipv4_address)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_ipv4_register_mac_request *msg = &clientMsg.rdevEthSwitchMsg.ipv4_register_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t ipv4_register_mac_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_IPV4_MAC_REGISTER;
    msg->info.id = id;
    msg->info.core_key = core_key;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    memcpy(msg->ipv4_addr, ipv4_address, sizeof(msg->ipv4_addr));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &ipv4_register_mac_response, sizeof(ipv4_register_mac_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(ipv4_register_mac_response.hdr) + sizeof(ipv4_register_mac_response.rdevEthSwitchMsg.ipv4_register_mac_res)));
        if (ipv4_register_mac_response.rdevEthSwitchMsg.ipv4_register_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_ipv6macregister(uint32_t device_id,
                                            uint64_t id,
                                            uint32_t core_key,
                                            uint8_t *mac_address,
                                            uint8_t *ipv6_address)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_ipv6_register_mac_request *msg = &clientMsg.rdevEthSwitchMsg.ipv6_register_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t ipv6_register_mac_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_IPV6_MAC_REGISTER;
    msg->info.id = id;
    msg->info.core_key = core_key;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    memcpy(msg->ipv6_addr, ipv6_address, sizeof(msg->ipv6_addr));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &ipv6_register_mac_response, sizeof(ipv6_register_mac_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(ipv6_register_mac_response.hdr) + sizeof(ipv6_register_mac_response.rdevEthSwitchMsg.ipv6_register_mac_res)));
        if (ipv6_register_mac_response.rdevEthSwitchMsg.ipv6_register_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_ipv4macunregister(uint32_t device_id,
                                              uint64_t id,
                                              uint32_t core_key,
                                              uint8_t *ipv4_address)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_ipv4_unregister_mac_request *msg = &clientMsg.rdevEthSwitchMsg.ipv4_unregister_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t ipv4_unregister_mac_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_IPV4_MAC_UNREGISTER;
    msg->info.id = id;
    msg->info.core_key = core_key;
    memcpy(msg->ipv4_addr, ipv4_address, sizeof(msg->ipv4_addr));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &ipv4_unregister_mac_response, sizeof(ipv4_unregister_mac_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(ipv4_unregister_mac_response.hdr) + sizeof(ipv4_unregister_mac_response.rdevEthSwitchMsg.ipv4_unregister_mac_res)));
        if (ipv4_unregister_mac_response.rdevEthSwitchMsg.ipv4_unregister_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_registerethtype(uint32_t device_id,
                                            uint64_t id,
                                            uint32_t core_key,
                                            uint32_t flow_idx,
                                            uint16_t ether_type)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_register_ethertype_request *msg = &clientMsg.rdevEthSwitchMsg.register_ethertype_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t register_ethertype_reponse;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_REGISTER_ETHTYPE;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->flow_idx = flow_idx;
    msg->ether_type = ether_type;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &register_ethertype_reponse, sizeof(register_ethertype_reponse), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(register_ethertype_reponse.hdr) + sizeof(register_ethertype_reponse.rdevEthSwitchMsg.register_ethertype_res)));
        if (register_ethertype_reponse.rdevEthSwitchMsg.register_ethertype_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_unregisterethtype(uint32_t device_id,
                                              uint64_t id,
                                              uint32_t core_key,
                                              uint32_t flow_idx,
                                              uint16_t ether_type)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_unregister_ethertype_request *msg = &clientMsg.rdevEthSwitchMsg.unregister_ethertype_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t unregister_ethertype_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_ETHTYPE;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->flow_idx = flow_idx;
    msg->ether_type = ether_type;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &unregister_ethertype_response, sizeof(unregister_ethertype_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(unregister_ethertype_response.hdr) + sizeof(unregister_ethertype_response.rdevEthSwitchMsg.unregister_ethertype_res)));
        if (unregister_ethertype_response.rdevEthSwitchMsg.unregister_ethertype_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_registerremotetimer(uint32_t device_id,
                                                uint64_t id,
                                                uint32_t core_key,
                                                uint8_t timerid,
                                                uint8_t hwPushNum)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_register_remotetimer_request *msg = &clientMsg.rdevEthSwitchMsg.register_remotetimer_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t register_remotetimer_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_REGISTER_REMOTEIMER;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->timer_id = timerid;
    msg->hwPushNum = hwPushNum;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &register_remotetimer_response, sizeof(register_remotetimer_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(register_remotetimer_response.hdr) + sizeof(register_remotetimer_response.rdevEthSwitchMsg.register_remotetimer_res)));
        if (register_remotetimer_response.rdevEthSwitchMsg.register_remotetimer_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_unregisterremotetimer(uint32_t device_id,
                                                  uint64_t id,
                                                  uint32_t core_key,
                                                  uint8_t hwPushNum)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_unregister_remotetimer_request *msg = &clientMsg.rdevEthSwitchMsg.unregister_remotetimer_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t unregister_remotetimer_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_UNREGISTER_REMOTEIMER;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->hwPushNum = hwPushNum;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &unregister_remotetimer_response, sizeof(unregister_remotetimer_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(unregister_remotetimer_response.hdr) + sizeof(unregister_remotetimer_response.rdevEthSwitchMsg.unregister_remotetimer_res)));
        if (unregister_remotetimer_response.rdevEthSwitchMsg.unregister_remotetimer_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_setPromiscMode(uint32_t device_id,
                                           uint64_t id,
                                           uint32_t core_key,
                                           uint32_t enable)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_set_promisc_mode_request *msg = &clientMsg.rdevEthSwitchMsg.set_promisc_mode_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t set_promisc_mode_response;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_SET_PROMISC_MODE;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->enable = enable;
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &set_promisc_mode_response, sizeof(set_promisc_mode_response), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(set_promisc_mode_response.hdr) + sizeof(set_promisc_mode_response.rdevEthSwitchMsg.set_promisc_mode_res)));
        if (set_promisc_mode_response.rdevEthSwitchMsg.set_promisc_mode_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_filterAddMac(uint32_t device_id,
                                         uint64_t id,
                                         uint32_t core_key,
                                         uint32_t flow_idx,
                                         uint8_t *mac_address,
                                         uint16_t vlan_id)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_filter_add_mac_request *msg = &clientMsg.rdevEthSwitchMsg.filter_add_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t filter_add_resp;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_FILTER_ADD_MAC;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->flow_idx = flow_idx;
    msg->vlan_id = vlan_id;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &filter_add_resp, sizeof(filter_add_resp), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(filter_add_resp.hdr) + sizeof(filter_add_resp.rdevEthSwitchMsg.filter_add_mac_res)));
        if (filter_add_resp.rdevEthSwitchMsg.filter_add_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}

int32_t rdevEthSwitchClient_filterDelMac(uint32_t device_id,
                                         uint64_t id,
                                         uint32_t core_key,
                                         uint32_t flow_idx,
                                         uint8_t *mac_address,
                                         uint16_t vlan_id)
{
    rdevEthSwitchClientMessageList_t clientMsg;
    struct rpmsg_kdrv_ethswitch_filter_del_mac_request *msg = &clientMsg.rdevEthSwitchMsg.filter_del_mac_req;
    int32_t ret;
    uint32_t respMsgSize;
    rdevEthSwitchClientMessageList_t filter_del_resp;

    ENET_UTILS_COMPILETIME_ASSERT(offsetof(rdevEthSwitchClientMessageList_t, hdr) == 0);
    memset(&clientMsg, 0, sizeof(clientMsg));
    msg->header.message_type = RPMSG_KDRV_TP_ETHSWITCH_FILTER_DEL_MAC;
    msg->info.id = id;
    msg->info.core_key = core_key;
    msg->flow_idx = flow_idx;
    msg->vlan_id = vlan_id;
    memcpy(msg->mac_address, mac_address, sizeof(msg->mac_address));
    ret = appRemoteDeviceServiceRequest(device_id, &clientMsg, sizeof(clientMsg), &filter_del_resp, sizeof(filter_del_resp), &respMsgSize);
    if (ret == 0)
    {
        assert(respMsgSize == (sizeof(filter_del_resp.hdr) + sizeof(filter_del_resp.rdevEthSwitchMsg.filter_del_mac_res)));
        if (filter_del_resp.rdevEthSwitchMsg.filter_del_mac_res.info.status != RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK)
        {
            ret = RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL;
        }
    }

    return ret;
}
