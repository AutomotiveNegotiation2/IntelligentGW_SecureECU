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
#include <string.h>

#include <ti/osal/TaskP.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/drv/ipc/ipc.h>

#include <protocol/rpmsg-kdrv-transport.h>
#include <server-rtos/include/app_log.h>
#include <server-rtos/include/app_queue.h>
#include <server-rtos/include/app_remote_device.h>

#define APP_REMOTE_DEVICE_MAX_DEVICES           (8)
#define APP_REMOTE_DEVICE_MAX_MSG_CONTAINERS    (32)
#define APP_REMOTE_DEVICE_MAX_CHANNELS          (8)
#define APP_REMOTE_DEVICE_MAX_MESSAGES          (32)

/* this should be >= RPMessage_getMessageBufferSize() */
#define APP_REMOTE_DEVICE_MAX_PACKET_SIZE       (496U + 32U)

#define APP_REMOTE_DEVICE_SERVICE_NAME          "rpmsg-kdrv"

#if defined(SAFERTOS)
#define g_init_tsk_stack_size                   (0x4000)
#define g_rx_tsk_stack_size                     (0x4000)
#define g_tx_tsk_stack_size                     (0x4000)
#define g_init_tsk_stack_align                  g_init_tsk_stack_size
#define g_rx_tsk_stack_align                    g_rx_tsk_stack_size
#define g_tx_tsk_stack_align                    g_tx_tsk_stack_size
#else
#define g_init_tsk_stack_size                   (0x2000)
#define g_rx_tsk_stack_size                     (0x2000)
#define g_tx_tsk_stack_size                     (0x2000)
#define g_init_tsk_stack_align                  (8192)
#define g_rx_tsk_stack_align                    (8192)
#define g_tx_tsk_stack_align                    (8192)
#endif

#define APP_REMOTE_DEVICE_ASSERT_SUCCESS(x)  { if((x)!=0) while(1); }
#define DEVHDR_2_MSG(x) ((void *)(((struct rpmsg_kdrv_device_header *)(x)) + 1))

struct __app_remote_device_device_data_t;
typedef struct __app_remote_device_device_data_t app_remote_device_device_data_t;

struct __app_remote_device_data_t;
typedef struct __app_remote_device_data_t app_remote_device_data_t;

struct __app_remote_device_msg_container_t;
typedef struct __app_remote_device_msg_container_t app_remote_device_msg_container_t;

struct __app_remote_device_device_data_t {
    uint32_t tp_id;
    uint32_t serial;
    app_remote_device_register_prm_t prm;
    uint32_t connected;
    app_remote_device_channel_t *channel;
};

struct __app_remote_device_data_t {
    app_remote_device_init_prm_t prm;
    app_remote_device_device_data_t dev_data[APP_REMOTE_DEVICE_MAX_DEVICES];
    uint32_t dev_count;
    app_queue_t msg_container_pool;
    app_queue_t channel_pool;
    app_queue_t message_pool;
    app_queue_t send_queue;
    SemaphoreP_Handle send_sem;
    SemaphoreP_Handle lock_sem;
    TaskP_Handle rx_task;
    TaskP_Handle tx_task;
    RPMessage_Handle rpmsg_handle;
    uint32_t remote_device_endpt;
};

struct __app_remote_device_msg_container_t {
    uint32_t remote_endpt;
    uint32_t remote_proc;
    void *data;
    void *meta;
    uint32_t len;
    uint32_t tx_len;
    int32_t (*msg_done_cb)(void *data, void *msg, uint32_t len);
};

static uint8_t g_rx_tsk_stack[g_rx_tsk_stack_size] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(g_rx_tsk_stack_align)));
static uint8_t g_tx_tsk_stack[g_tx_tsk_stack_size] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(g_tx_tsk_stack_align)));
static uint8_t g_init_tsk_stack[g_init_tsk_stack_size] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(g_init_tsk_stack_align)));

static uint64_t g_channel_pool_storage[(((sizeof(app_remote_device_channel_t) + APP_QUEUE_ELEM_META_SIZE) / sizeof(uint64_t)) + 1)* APP_REMOTE_DEVICE_MAX_CHANNELS];
static uint64_t g_msg_container_pool_storage[((((sizeof(app_remote_device_msg_container_t) + APP_QUEUE_ELEM_META_SIZE)) / sizeof(uint64_t)) + 1) * APP_REMOTE_DEVICE_MAX_MSG_CONTAINERS];
static uint64_t g_message_pool_storage[(((APP_REMOTE_DEVICE_MAX_PACKET_SIZE + APP_QUEUE_ELEM_META_SIZE) / sizeof(uint64_t)) + 1) * APP_REMOTE_DEVICE_MAX_MESSAGES];


/* TODO: cant these be done in ipcinit? */
#define IPC_RPMESSAGE_OBJ_SIZE  256
static uint8_t g_app_remote_device_rpmsg_buf[APP_REMOTE_DEVICE_MAX_MESSAGES * APP_REMOTE_DEVICE_MAX_PACKET_SIZE + IPC_RPMESSAGE_OBJ_SIZE] __attribute__ ((aligned(1024)));

static app_remote_device_data_t g_rdev_data;

static app_remote_device_device_data_t *appRemoteDeviceDataFindDeviceForId(uint32_t tp_id)
{
    uint32_t cnt;
    app_remote_device_device_data_t *dev = NULL;

    for(cnt = 0; cnt < g_rdev_data.dev_count; cnt++) {
        if(g_rdev_data.dev_data[cnt].tp_id == tp_id) {
            dev = &g_rdev_data.dev_data[cnt];
            break;
        }
    }

    return dev;
}

static uint32_t appCheckHostForDevice(app_remote_device_device_data_t *dev, uint32_t host_id)
{
    uint32_t cnt;
    uint32_t valid = FALSE;

    for(cnt = 0; cnt < dev->prm.num_host_ids; cnt++) {
        if(dev->prm.host_ids[cnt] == host_id) {
            valid = TRUE;
            break;
        }
    }

    return valid;
}

static int32_t appRemoteDeviceValidateInitPrm(app_remote_device_init_prm_t *prm, char *err_str, uint32_t err_len)
{
    int32_t ret = 0;

    if(prm == NULL) {
        snprintf(err_str, err_len, "prm = NULL not allowed");
        ret = -1;
    }

    if(ret == 0) {
        if(prm->rpmsg_buf_size > APP_REMOTE_DEVICE_MAX_PACKET_SIZE) {
            snprintf(err_str, err_len, "rpmsg_buf_size > %u not allowed", APP_REMOTE_DEVICE_MAX_PACKET_SIZE);
            ret = -1;
        }
    }

    return ret;
}

static int32_t appRemoteDeviceMessageDoneCb(void *meta, void *msg, uint32_t len)
{
    int32_t ret;

    /* Put the empty message back in message pool */
    ret = appQueuePut(&g_rdev_data.message_pool, msg);
    if(ret != 0)
        appLogPrintf("%s: Could not put empty message to pool\n", __func__);

    return ret;
}

int32_t appRemoteDeviceSendMessage(app_remote_device_channel_t *channel, void *data,
        uint32_t len, uint32_t is_response, uint32_t request_id, uint32_t device_id,
        int32_t (*msg_done_cb)(void *data, void *msg, uint32_t len), void *meta_data)
{
    int32_t ret;
    void *value;
    app_remote_device_msg_container_t *msg;
    struct rpmsg_kdrv_device_header *hdr = (struct rpmsg_kdrv_device_header *)data;

    hdr->device_id = device_id;
    hdr->packet_type = is_response == TRUE ? RPMSG_KDRV_TP_PACKET_TYPE_RESPONSE : RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE;
    hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_SERVER;
    hdr->packet_id = is_response == TRUE ? request_id : RPMSG_KDRV_TP_PACKET_ID_NONE;
    hdr->packet_size =  sizeof(*hdr) + len;

    ret = appQueueGet(&g_rdev_data.msg_container_pool, &value);
    if(ret != 0)
        appLogPrintf("%s: Could not get an empty container\n", __func__);

    if(ret == 0) {
        msg = (app_remote_device_msg_container_t *)value;
        memset(msg, 0, sizeof(*msg));

        msg->remote_proc = channel->procid;
        msg->remote_endpt = channel->endpoint;
        msg->data = data;
        msg->msg_done_cb = msg_done_cb;
        msg->meta = meta_data;
        msg->len = len;
        msg->tx_len = len + sizeof(*hdr);

        ret = appQueuePut(&g_rdev_data.send_queue, msg);
        if(ret != 0)
            appLogPrintf("%s: Could not put msg to send queue\n", __func__);
    }

    if(ret == 0) {
        SemaphoreP_post(g_rdev_data.send_sem);
    }

    return ret;
}

static int32_t appRemoteDeviceHandleDisconnect(struct rpmsg_kdrv_init_disconnect_message *disconnect,
        app_remote_device_channel_t *channel)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;
    uint32_t hostValid;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    /* Find the device for which connect is requested */
    dev = appRemoteDeviceDataFindDeviceForId(disconnect->device_id);
    if(dev == NULL) {
        appLogPrintf("%s: Could not find device\n", __func__);
        ret = -1;
    }

    if(ret == 0) {
        hostValid = appCheckHostForDevice(dev, channel->procid);
        if(hostValid != TRUE) {
            appLogPrintf("%s: Unauthorized host for device\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(dev->connected == FALSE) {
            appLogPrintf("%s: Failed to process disconnect: device already disconnected\n", __func__);
            ret = -1;
        }
    }

    /* Unlock the mutex before CB */
    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        ret = dev->prm.cb.disconnect(dev->tp_id);
        if(ret != 0)
            appLogPrintf("%s: device disconenct cb failed\n", __func__);
    }

    /* Relock the mutex */
    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        ret = appQueuePut(&g_rdev_data.channel_pool, dev->channel);
	if(ret != 0)
            appLogPrintf("%s: appQueuePut failed\n", __func__);
    }

    if(ret == 0) {
        dev->channel = NULL;
        dev->connected = FALSE;
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    return ret;
}

static int32_t appRemoteDeviceHandleConnect(struct rpmsg_kdrv_init_connect_message *connect,
        app_remote_device_channel_t *channel)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;
    void *value;
    app_remote_device_channel_t *nchannel;
    uint32_t hostValid;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    /* Find the device for which connect is requested */
    dev = appRemoteDeviceDataFindDeviceForId(connect->device_id);
    if(dev == NULL) {
        appLogPrintf("%s: Could not find device\n", __func__);
        ret = -1;
    }

    if(ret == 0) {
        hostValid = appCheckHostForDevice(dev, channel->procid);
        if(hostValid != TRUE) {
            appLogPrintf("%s: Unauthorized host for device\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(dev->connected == TRUE) {
            appLogPrintf("%s: Failed to process connect: device already connected\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        ret = appQueueGet(&g_rdev_data.channel_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get a free channel\n", __func__);
    }

    if(ret == 0) {
        nchannel = (app_remote_device_channel_t *)value;
        memset(nchannel, 0, sizeof(*nchannel));

        nchannel->procid = channel->procid;
        nchannel->endpoint = channel->endpoint;

        dev->channel = nchannel;
        dev->connected = TRUE;
    }

    /* Release the lock before calling the cb */
    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        dev->prm.cb.connect(dev->tp_id, dev->channel);
    }

    return ret;
}

static int32_t appRemoteDeviceHandleDevInfoRequest(struct rpmsg_kdrv_init_dev_info_request *devinfo,
        uint32_t request_id, app_remote_device_channel_t *channel)
{
    int32_t ret;
    void *value;
    struct rpmsg_kdrv_device_header *hdr;
    struct rpmsg_kdrv_init_dev_info_response *resp;
    app_remote_device_device_data_t *sdev;
    struct rpmsg_kdrv_init_device_info *ddev;
    app_remote_device_msg_container_t *msg;
    uint32_t i;
    uint32_t device_data_size = 0, remaining;
    uint32_t shouldSend;
    int32_t priv_data_len;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    ret = appQueueGet(&g_rdev_data.message_pool, &value);
    if(ret != 0)
        appLogPrintf("%s: Could not get an empty message\n", __func__);

    if(ret == 0) {
        hdr = (struct rpmsg_kdrv_device_header *)value;
        resp = (struct rpmsg_kdrv_init_dev_info_response *)(DEVHDR_2_MSG(hdr));
        memset(hdr, 0, sizeof(*hdr) + sizeof(*resp));

        hdr->device_id = RPMSG_KDRV_TP_DEVICE_ID_INIT;
        hdr->packet_type = RPMSG_KDRV_TP_PACKET_TYPE_RESPONSE;
        hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_SERVER;
        hdr->packet_id = request_id;
        hdr->packet_size = sizeof(*hdr) + sizeof(*resp);

        resp->header.message_type = RPMSG_KDRV_TP_INIT_DEV_INFO_RESPONSE;

        if(g_rdev_data.dev_count > RPMSG_KDRV_TP_MAX_DEVICES) {
            appLogPrintf("%s: More devices than transport allows\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        resp->num_devices = 0;
        remaining = g_rdev_data.prm.rpmsg_buf_size - hdr->packet_size;

        for(i = 0; i < g_rdev_data.dev_count; i++) {

            sdev = &g_rdev_data.dev_data[i];
            ddev = &resp->devices[resp->num_devices];
            shouldSend = appCheckHostForDevice(sdev, channel->procid);

            if(shouldSend == TRUE) {
                resp->num_devices++;

                ddev->device_id = sdev->tp_id;
                snprintf((char *)(&ddev->device_name[0]), RPMSG_KDRV_TP_DEVICE_NAME_LEN, "%s", sdev->prm.name);
                priv_data_len = sdev->prm.cb.fill_priv_data(sdev->tp_id, (void *)(&resp->device_data[device_data_size]), remaining);
                if(priv_data_len < 0) {
                    appLogPrintf("%s: Could not fill device data\n", __func__);
                    ret = -1;
                }

                remaining -= priv_data_len;
                ddev->device_data_len = priv_data_len;
                ddev->device_data_offset = device_data_size;

                device_data_size += priv_data_len;

                switch(sdev->prm.device_type) {
                    case APP_REMOTE_DEVICE_DEVICE_TYPE_DISPLAY:
                        ddev->device_type = RPMSG_KDRV_TP_DEVICE_TYPE_DISPLAY;
                        break;
                    case APP_REMOTE_DEVICE_DEVICE_TYPE_DEMO:
                        ddev->device_type = RPMSG_KDRV_TP_DEVICE_TYPE_DEMO;
                        break;
                    case APP_REMOTE_DEVICE_DEVICE_TYPE_ETHSWITCH:
                        ddev->device_type = RPMSG_KDRV_TP_DEVICE_TYPE_ETHSWITCH;
                        break;
                    default:
                        appLogPrintf("%s: unidentified device type\n", __func__);
                        ret = -1;
                }

                if(ret != 0) {
                    appLogPrintf("%s: Could not fill device info\n", __func__);
                    break;
                }
            }
        }
    }

    /* Atomic ops are complete. Release the lock */
    SemaphoreP_post(g_rdev_data.lock_sem);


    if(ret == 0) {
        hdr->packet_size += device_data_size;

        ret = appQueueGet(&g_rdev_data.msg_container_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty container\n", __func__);
    }

    if(ret == 0) {
        msg = (app_remote_device_msg_container_t *)value;
        memset(msg, 0, sizeof(*msg));

        msg->remote_proc = channel->procid;
        msg->remote_endpt = channel->endpoint;
        msg->data = hdr;
        msg->msg_done_cb = appRemoteDeviceMessageDoneCb;
        msg->meta = NULL;
        msg->len = hdr->packet_size;
        msg->tx_len = hdr->packet_size;

        ret = appQueuePut(&g_rdev_data.send_queue, msg);
        if(ret != 0)
            appLogPrintf("%s: Could not put msg to send queue\n", __func__);
    }

    if(ret == 0) {
        SemaphoreP_post(g_rdev_data.send_sem);
    }

    return ret;
}

static int32_t appRemoteDeviceHandleInitRequest(struct rpmsg_kdrv_init_message_header *mhdr,
        uint32_t request_id, app_remote_device_channel_t *channel)
{
    int32_t ret = 0;
    struct rpmsg_kdrv_init_dev_info_request *dev_info;

    switch(mhdr->message_type) {
        case RPMSG_KDRV_TP_INIT_DEV_INFO_REQUEST:
            dev_info = (struct rpmsg_kdrv_init_dev_info_request *)mhdr;
            ret = appRemoteDeviceHandleDevInfoRequest(dev_info, request_id, channel);
            break;
        default:
            appLogPrintf("%s: unidentified type:request\n", __func__);
            ret = -1;
    }

    if(ret != 0)
        appLogPrintf("%s: Could not handle init type:request\n", __func__);

    return ret;
}

static int32_t appRemoteDeviceHandleInitMessage(struct rpmsg_kdrv_init_message_header *mhdr,
        app_remote_device_channel_t *channel)
{
    int32_t ret = 0;
    struct rpmsg_kdrv_init_connect_message *connect;
    struct rpmsg_kdrv_init_disconnect_message *disconnect;

    switch(mhdr->message_type) {
        case RPMSG_KDRV_TP_INIT_CONNECT_MESSAGE:
            connect = (struct rpmsg_kdrv_init_connect_message *)mhdr;
            ret = appRemoteDeviceHandleConnect(connect, channel);
            break;
        case RPMSG_KDRV_TP_INIT_DISCONNECT_MESSAGE:
            disconnect = (struct rpmsg_kdrv_init_disconnect_message *)mhdr;
            ret = appRemoteDeviceHandleDisconnect(disconnect, channel);
            break;
        default:
            appLogPrintf("%s: unidentified type:message\n", __func__);
            ret = -1;
    }

    if(ret != 0)
        appLogPrintf("%s: Could not handle init type:message\n", __func__);

    return ret;
}

static int32_t appRemoteDeviceHandleDevice(struct rpmsg_kdrv_device_header *hdr,
        app_remote_device_channel_t *channel)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;
    void *msg;
    uint32_t hostValid;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    /* Find the device for which the message is directed */
    dev = appRemoteDeviceDataFindDeviceForId(hdr->device_id);
    if(dev == NULL) {
        appLogPrintf("%s: Could not find device\n", __func__);
        ret = -1;
    }

    if(ret == 0) {
        hostValid = appCheckHostForDevice(dev, channel->procid);
        if(hostValid != TRUE) {
            appLogPrintf("%s: Unauthorized host for device\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(dev->connected == FALSE) {
            appLogPrintf("%s: Failed to deliver message: device not connected\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(dev->channel->endpoint != channel->endpoint || dev->channel->procid != channel->procid) {
            appLogPrintf("%s: Failed to deliver message: channel mismatch\n", __func__);
            ret = -1;
        }
    }

    /* Atomic ops complete. Release the lock */
    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        msg = DEVHDR_2_MSG(hdr);

        switch(hdr->packet_type) {
            case RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE:
                ret = dev->prm.cb.message(dev->tp_id, dev->channel, msg, hdr->packet_size - sizeof(*hdr));
                break;
            case RPMSG_KDRV_TP_PACKET_TYPE_REQUEST:
                ret = dev->prm.cb.request(dev->tp_id, dev->channel, hdr->packet_id, msg, hdr->packet_size - sizeof(*hdr));
                break;
            default:
                appLogPrintf("%s: unidentified message type\n", __func__);
                ret = -1;
        }

        if(ret != 0)
            appLogPrintf("%s: Device failed to process message\n", __func__);

    }

    return ret;
}

static int32_t appRemoteDeviceHandleInit(struct rpmsg_kdrv_device_header *hdr,
        app_remote_device_channel_t *channel)
{
    int32_t ret = 0;
    struct rpmsg_kdrv_init_message_header *mhdr;

    mhdr = DEVHDR_2_MSG(hdr);
    switch(hdr->packet_type) {
        case RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE:
            ret = appRemoteDeviceHandleInitMessage(mhdr, channel);
            break;
        case RPMSG_KDRV_TP_PACKET_TYPE_REQUEST:
            ret = appRemoteDeviceHandleInitRequest(mhdr, hdr->packet_id, channel);
            break;
        default:
            appLogPrintf("%s: unidentified message type\n", __func__);
            ret = -1;
    }

    if(ret != 0)
        appLogPrintf("%s: Could not handle init message\n", __func__);

    return ret;
}

static void appRemoteDeviceRxTaskFn(void *arg0, void *arg1)
{
    char data[APP_REMOTE_DEVICE_MAX_PACKET_SIZE];
    uint32_t remote_ept;
    uint32_t remote_proc;
    uint16_t len;
    int32_t ret;
    struct rpmsg_kdrv_device_header *hdr;
    app_remote_device_channel_t channel;

    while(1)
    {
        ret = 0;

        /* Wait for a message */
        ret = RPMessage_recv(g_rdev_data.rpmsg_handle, (void *)data, &len, &remote_ept, &remote_proc,
                IPC_RPMESSAGE_TIMEOUT_FOREVER);
        if(ret != IPC_SOK)
        {
            appLogPrintf("%s: RPMessage_recv failed\n", __func__);
            ret = -1;
        }

        if(ret == 0) {
            hdr = (struct rpmsg_kdrv_device_header *)data;
            channel.procid = remote_proc;
            channel.endpoint = remote_ept;

            if(hdr->device_id == RPMSG_KDRV_TP_DEVICE_ID_INIT)
                /* Is it a message for framework? */
                ret = appRemoteDeviceHandleInit(hdr, &channel);
            else
                /* Is it a message for a connected device? */
                ret = appRemoteDeviceHandleDevice(hdr, &channel);

            if(ret != 0)
                appLogPrintf("%s: Could not handle message\n", __func__);
        }

        APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);
    }
}

static void appRemoteDeviceTxTaskFn(void *arg0, void *arg1)
{
    int32_t ret;
    app_remote_device_msg_container_t *msg;
    void *value;

    while(1)
    {
        ret = 0;

        /* Wait for a signal = a new message to be sent */
        SemaphoreP_pend(g_rdev_data.send_sem, SemaphoreP_WAIT_FOREVER);
        ret = appQueueGet(&g_rdev_data.send_queue, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not dequeue message to send\n", __func__);

        if(ret == 0) {
            /* New container, send containing data using indicated channel */
            msg = (app_remote_device_msg_container_t *)value;
            ret = RPMessage_send(g_rdev_data.rpmsg_handle, msg->remote_proc, msg->remote_endpt,
                    g_rdev_data.remote_device_endpt, msg->data, msg->tx_len);
            if (ret != IPC_SOK)
            {
                appLogPrintf("%s: RPMessage_send failed\n", __func__);
                ret = -1;
            }
        }

        if(ret == 0) {
            /* Call mesaage originator's free callback */
            ret = msg->msg_done_cb(msg->meta, msg->data, msg->len);
            if(ret != 0)
                appLogPrintf("%s: msg_done_cb failed\n", __func__);
        }

        if(ret == 0) {
            /* Put the used container back to pool */
            ret = appQueuePut(&g_rdev_data.msg_container_pool, msg);
            if(ret != 0)
                appLogPrintf("%s: Could not put container abck to pool\n");
        }

        APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);
    }
}

static void appRemoteDeviceInitFn(void *arg0, void *arg1)
{
    int32_t ret;
    SemaphoreP_Handle    wait_sem = (SemaphoreP_Handle) arg0;
    SemaphoreP_Params    sem_params;
    TaskP_Params         rx_params;
    TaskP_Params         tx_params;
    RPMessage_Params     params;

    /* The send queue. Task picks up from this queue and sends */
    ret = appQueueInit(&g_rdev_data.send_queue, FALSE, 0, 0, NULL, 0);
    if(ret != 0)
        appLogPrintf("%s: Could not initialize send queue\n", __func__);

    if(ret == 0) {
        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_COUNTING;

        g_rdev_data.send_sem = SemaphoreP_create(0, &sem_params);
        if(g_rdev_data.send_sem == NULL) {
            appLogPrintf("%s: Could not initialize send semaphore\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /*Wait for HLOS to connect */
        SemaphoreP_pend(wait_sem, SemaphoreP_WAIT_FOREVER);

        /* Create the RPMSG endpoint */
        RPMessageParams_init(&params);
        params.requestedEndpt = g_rdev_data.prm.remote_device_endpt;
        params.buf = g_app_remote_device_rpmsg_buf;
        params.bufSize = sizeof(g_app_remote_device_rpmsg_buf);

        g_rdev_data.rpmsg_handle = RPMessage_create(&params, &g_rdev_data.remote_device_endpt);
        if(g_rdev_data.rpmsg_handle == NULL)
        {
            appLogPrintf("%s: Failed to create endpoint\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* Announce the framework endpoint to remote cores */
        ret = RPMessage_announce(RPMESSAGE_ALL, g_rdev_data.remote_device_endpt, APP_REMOTE_DEVICE_SERVICE_NAME);
        if(ret != IPC_SOK) {
            appLogPrintf("%s: Could not announce endpoint\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* Start the RX task */
        TaskP_Params_init(&rx_params);
        rx_params.priority = 10;
        rx_params.stack = g_rx_tsk_stack;
        rx_params.stacksize = g_rx_tsk_stack_size;
        g_rdev_data.rx_task = TaskP_create(&appRemoteDeviceRxTaskFn, &rx_params);
        if(g_rdev_data.rx_task == NULL) {
            appLogPrintf("%s: Failed to create RX task\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* Start the TX task */
        TaskP_Params_init(&tx_params);
        tx_params.priority = 10;
        tx_params.stack = g_tx_tsk_stack;
        tx_params.stacksize = g_tx_tsk_stack_size;
        g_rdev_data.tx_task = TaskP_create(&appRemoteDeviceTxTaskFn, &tx_params);
        if(g_rdev_data.tx_task == NULL) {
            appLogPrintf("%s: Failed to create TX task\n", __func__);
            ret = -1;
        }
    }

    APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);
}

static int32_t appRemoteDevicePoolsInit(app_remote_device_init_prm_t *prm)
{
    int32_t ret;

    /* The pool for channels */
    ret = appQueueInit(&g_rdev_data.channel_pool, TRUE, APP_REMOTE_DEVICE_MAX_CHANNELS,
            sizeof(app_remote_device_channel_t), g_channel_pool_storage, sizeof(g_channel_pool_storage));
    if(ret != 0)
        appLogPrintf("%s: Could not initialize channel pool\n", __func__);

    if(ret == 0) {
        /* The pool for rx-to-tx references */
        ret = appQueueInit(&g_rdev_data.msg_container_pool, TRUE, APP_REMOTE_DEVICE_MAX_MSG_CONTAINERS,
                sizeof(app_remote_device_msg_container_t), g_msg_container_pool_storage, sizeof(g_msg_container_pool_storage));
        if(ret != 0) {
            appLogPrintf("%s: Could not initialize container pool\n", __func__);
        }
    }

    if(ret == 0) {
        /* The pool for transport messages */
        ret = appQueueInit(&g_rdev_data.message_pool, TRUE, APP_REMOTE_DEVICE_MAX_MESSAGES,
                prm->rpmsg_buf_size, g_message_pool_storage, sizeof(g_message_pool_storage));
        if(ret != 0) {
            appLogPrintf("%s: Could not initialize message pool\n", __func__);
        }
    }

    return ret;
}

int32_t appRemoteDeviceInit(app_remote_device_init_prm_t *prm)
{
    int32_t ret;
    SemaphoreP_Params sem_params;
    TaskP_Params tsk_prm;
    TaskP_Handle task;
    char err_str[128];

    /* validate params. */
    ret = appRemoteDeviceValidateInitPrm(prm, err_str, 128);
    if(ret != 0)
        appLogPrintf("%s: Could not validate init params: %s\n", __func__, err_str);

    if(ret == 0) {
        memset(&g_rdev_data, 0, sizeof(g_rdev_data));
        memcpy(&g_rdev_data.prm, prm, sizeof(*prm));

        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_BINARY;

        g_rdev_data.lock_sem = SemaphoreP_create(1, &sem_params);
        if(g_rdev_data.lock_sem == NULL) {
            appLogPrintf("%s: Could not initialize lock semaphore (mutex)\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* allocate pools */
        ret = appRemoteDevicePoolsInit(prm);
        if(ret != 0)
            appLogPrintf("%s: Could not initialize mandatory pools\n", __func__);
    }

    if(ret == 0) {
        /* start a init task which will create RPMSG and then start RX / TX tasks */
        TaskP_Params_init(&tsk_prm);
        tsk_prm.priority = 3;
        tsk_prm.stack = &g_init_tsk_stack;
        tsk_prm.stacksize = g_init_tsk_stack_size;
        tsk_prm.arg0 = (void *)prm->wait_sem;

        task = TaskP_create(&appRemoteDeviceInitFn, &tsk_prm);
        if(task == NULL) {
            appLogPrintf("%s: Could not start init task\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

int32_t appRemoteDeviceRegisterDevice(app_remote_device_register_prm_t *prm, uint32_t *device_id)
{
    int32_t ret = 0;
    uint32_t id;
    app_remote_device_device_data_t *dev;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(g_rdev_data.dev_count >= APP_REMOTE_DEVICE_MAX_DEVICES) {
        appLogPrintf("%s: [dev %u] Could not find slot for device\n", __func__, g_rdev_data.dev_count);
        ret = -1;
    }

    if(ret == 0) {
        id = g_rdev_data.dev_count;
        dev = &g_rdev_data.dev_data[id];

        memset(dev, 0, sizeof(*dev));
        memcpy(&dev->prm, prm, sizeof(*prm));

        dev->tp_id = RPMSG_KDRV_TP_DEVICE_ID_INIT + 1 + id;
        dev->serial = id;

        *device_id = dev->tp_id;
        g_rdev_data.dev_count++;
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    return ret;
}

int32_t appRemoteDeviceLateAnnounce(uint32_t proc_id)
{
    int32_t ret;

    /* Announce the framework endpoint to remote cores */
    ret = RPMessage_announce(proc_id, g_rdev_data.remote_device_endpt, APP_REMOTE_DEVICE_SERVICE_NAME);
    if(ret != IPC_SOK) {
        appLogPrintf("%s: Could not announce endpoint\n", __func__);
        ret = -1;
    }

    return ret;
}
