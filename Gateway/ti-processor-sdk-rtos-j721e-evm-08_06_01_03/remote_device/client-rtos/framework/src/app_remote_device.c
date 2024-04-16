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
#include <client-rtos/include/app_log.h>
#include <client-rtos/include/app_queue.h>
#include <client-rtos/include/app_remote_device.h>

#define APP_REMOTE_DEVICE_MAX_CORES             (8)
#define APP_REMOTE_DEVICE_MAX_DEVICES           (64)
#define APP_REMOTE_DEVICE_MAX_DEVICES_CORE      (64)

#define APP_REMOTE_DEVICE_MAX_MSG_CONTAINERS    (512)
#define APP_REMOTE_DEVICE_MAX_MESSAGES          (512)
#define APP_REMOTE_DEVICE_MAX_REQUESTS          (512)

#define APP_REMOTE_DEVICE_DEVICE_NAME_LEN       (128)
#define APP_REMOTE_DEVICE_DEVICE_DATA_LEN       (128)

/* this should be >= RPMessage_getMessageBufferSize() */
#define APP_REMOTE_DEVICE_MAX_PACKET_SIZE       (496U + 32U)

#if defined(SAFERTOS)
#define APP_REMOTE_DEVICE_STACKSIZE             (0x4000)
#define APP_REMOTE_DEVICE_STACKALIGN            APP_REMOTE_DEVICE_STACKSIZE
#else
#define APP_REMOTE_DEVICE_STACKSIZE             (0x2000)
#define APP_REMOTE_DEVICE_STACKALIGN            (8192)
#endif

#ifdef QNX_OS
  #include <sys/slog.h>
  #include <sys/slogcodes.h>
  #define APP_REMOTE_DEVICE_ASSERT_SUCCESS(x)  \
    { \
        if((x)!=0) slogf(_SLOGC_NETWORK, _SLOG_ERROR, \
            "%s:%d Return not success!",__func__, __LINE__); \
    }
#else
  #define APP_REMOTE_DEVICE_ASSERT_SUCCESS(x)  { if((x)!=0) while(1); }
#endif
#define DEVHDR_2_MSG(x) ((void *)(((struct rpmsg_kdrv_device_header *)(x)) + 1))
#define min(a, b) (a > b ? b : a)

struct __app_remote_device_device_data_t;
typedef struct __app_remote_device_device_data_t app_remote_device_device_data_t;

struct __app_remote_device_core_data_t;
typedef struct __app_remote_device_core_data_t app_remote_device_core_data_t;

struct __app_remote_device_data_t;
typedef struct __app_remote_device_data_t app_remote_device_data_t;

struct __app_remote_device_msg_container_t;
typedef struct __app_remote_device_msg_container_t app_remote_device_msg_container_t;

struct __app_remote_device_device_data_t {
    uint32_t serial;
    app_remote_device_core_data_t *core;
    uint32_t tp_id;
    uint32_t tp_type;
    uint32_t data_len;
    uint8_t name[APP_REMOTE_DEVICE_DEVICE_NAME_LEN];
    uint8_t data[APP_REMOTE_DEVICE_DEVICE_DATA_LEN];
    uint32_t (*message_cb)(void *priv_data, void *msg);
    void *message_cb_priv;
};

struct __app_remote_device_core_data_t {
    uint32_t serial;
    uint32_t core_id;
    app_remote_device_device_data_t *dev[APP_REMOTE_DEVICE_MAX_DEVICES_CORE];
    app_remote_device_device_data_t *conf_device;
    uint32_t dev_count;
    uint32_t local_endpt;
    RPMessage_Handle rpmsg_handle;
    TaskP_Handle discov_task;
    app_queue_t send_queue;
    SemaphoreP_Handle send_sem;
    TaskP_Params discov_params;
    TaskP_Params rx_params;
    TaskP_Params tx_params;
    TaskP_Handle rx_task;
    TaskP_Handle tx_task;
};

struct __app_remote_device_data_t {
    app_remote_device_init_prm_t prm;
    SemaphoreP_Handle lock_sem;

    app_remote_device_device_data_t dev_data[APP_REMOTE_DEVICE_MAX_DEVICES];
    uint32_t dev_count;
    app_remote_device_core_data_t core_data[APP_REMOTE_DEVICE_MAX_CORES];
    uint32_t core_count;

    app_queue_t message_pool;
    app_queue_t req_id_pool;
    app_queue_t msg_container_pool;
    app_queue_t pend_req_queue;

    TaskP_Params init_task_prm;
    TaskP_Handle init_task;
};

struct __app_remote_device_msg_container_t {
    app_remote_device_device_data_t *device;
    void *data;
    uint32_t len;
    int32_t (*free_cb)(void *data, void *msg, uint32_t len);
    void *free_cb_data;
    uint32_t *req_id;
    void *resp_data;
    uint32_t resp_avail;
    uint32_t resp_len;
    SemaphoreP_Handle wait_sem;

};


static uint8_t g_init_tsk_stack[APP_REMOTE_DEVICE_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(APP_REMOTE_DEVICE_STACKALIGN)));
static uint8_t g_rx_tsk_stack[APP_REMOTE_DEVICE_MAX_CORES * APP_REMOTE_DEVICE_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(APP_REMOTE_DEVICE_STACKALIGN)));
static uint8_t g_tx_tsk_stack[APP_REMOTE_DEVICE_MAX_CORES * APP_REMOTE_DEVICE_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(APP_REMOTE_DEVICE_STACKALIGN)));
static uint8_t g_discov_tsk_stack[APP_REMOTE_DEVICE_MAX_CORES * APP_REMOTE_DEVICE_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(APP_REMOTE_DEVICE_STACKALIGN)));

static uint64_t g_msg_container_pool_storage[((((sizeof(app_remote_device_msg_container_t) + APP_QUEUE_ELEM_META_SIZE)) / sizeof(uint64_t)) + 1) * APP_REMOTE_DEVICE_MAX_MSG_CONTAINERS];
static uint64_t g_message_pool_storage[(((APP_REMOTE_DEVICE_MAX_PACKET_SIZE + APP_QUEUE_ELEM_META_SIZE) / sizeof(uint64_t)) + 1) * APP_REMOTE_DEVICE_MAX_MESSAGES];
static uint64_t g_req_id_pool_storage[(((sizeof(uint32_t) + APP_QUEUE_ELEM_META_SIZE)  / sizeof(uint64_t)) + 1) * APP_REMOTE_DEVICE_MAX_MESSAGES];

#define IPC_RPMESSAGE_OBJ_SIZE  256
#define APP_REMOTE_DEVICE_MAX_MESSAGES_CORE     (512)
#define APP_REMOTE_DEVICE_CORE_RPMSG_BUF_SIZE   (IPC_RPMESSAGE_OBJ_SIZE + APP_REMOTE_DEVICE_MAX_MESSAGES_CORE * APP_REMOTE_DEVICE_MAX_PACKET_SIZE)
static uint8_t g_app_remote_device_rpmsg_buf[APP_REMOTE_DEVICE_MAX_CORES * APP_REMOTE_DEVICE_CORE_RPMSG_BUF_SIZE] __attribute__ ((aligned(1024)));

static app_remote_device_data_t g_rdev_data;

static int32_t appRemoteDeviceValidateInitPrm(app_remote_device_init_prm_t *prm, char *err_str, uint32_t err_len)
{
    return 0;
}

static app_remote_device_device_data_t *appRemoteDeviceFindCoreDeviceByTpId(app_remote_device_core_data_t *core, uint32_t tp_id)
{
    uint32_t cnt;
    app_remote_device_device_data_t *dev = NULL;

    for(cnt = 0; cnt < core->dev_count; cnt++) {
        if(tp_id == core->dev[cnt]->tp_id) {
            dev = core->dev[cnt];
            break;
        }
    }

    return dev;
}

static app_remote_device_device_data_t *appRemoteDeviceDataFindDeviceForId(uint32_t id)
{
    uint32_t cnt;
    app_remote_device_device_data_t *dev = NULL;

    for(cnt = 0; cnt < g_rdev_data.dev_count; cnt++) {
        if(id == g_rdev_data.dev_data[cnt].serial) {
            dev = &g_rdev_data.dev_data[cnt];
            break;
        }
    }

    return dev;
}

static app_remote_device_device_data_t *appRemoteDeviceDataFindDeviceForName(const char *device_name)
{
    uint32_t cnt;
    app_remote_device_device_data_t *dev = NULL;

    for(cnt = 0; cnt < g_rdev_data.dev_count; cnt++) {
        if(strncmp((char *)g_rdev_data.dev_data[cnt].name, device_name, APP_REMOTE_DEVICE_DEVICE_NAME_LEN) == 0) {
            dev = &g_rdev_data.dev_data[cnt];
            break;
        }
    }

    return dev;
}

static int32_t appRemoteDeviceValidateContainer(app_remote_device_msg_container_t *msg)
{
    int32_t ret = 0;
    struct rpmsg_kdrv_device_header *hdr = (struct rpmsg_kdrv_device_header *)msg->data;

    if(hdr->packet_type == RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE) {
        if(msg->free_cb == NULL) {
            appLogPrintf("%s: Invalid container, Message packet without free cb\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

static int32_t appRemoteDeviceFreeMessage(app_remote_device_msg_container_t *msg)
{
    int32_t ret = 0;

    if(ret == 0) {
        /* Call mesaage originator's free callback */
        ret = msg->free_cb(msg->free_cb_data, msg->data, msg->len);
        if(ret != 0)
            appLogPrintf("%s: msg_done_cb failed\n", __func__);
    }

    if(ret == 0) {
        /* Put the used container back to pool */
        ret = appQueuePut(&g_rdev_data.msg_container_pool, msg);
        if(ret != 0)
            appLogPrintf("%s: Could not put container abck to pool\n", __func__);
    }

    return ret;
}

static void appRemoteDeviceTxTaskFn(void *arg0, void *arg1)
{
    int32_t ret = 0;
    void *value;
    app_remote_device_msg_container_t *msg;
    app_remote_device_core_data_t *core = (app_remote_device_core_data_t *)arg0;
    struct rpmsg_kdrv_device_header *hdr;

    while(1)
    {
        ret = 0;

        if(ret == 0) {
            /* Wait for a signal = a new message to be sent */
            SemaphoreP_pend(core->send_sem, SemaphoreP_WAIT_FOREVER);
            ret = appQueueGet(&core->send_queue, &value);
            if(ret != 0)
                appLogPrintf("%s: Could not dequeue message to send\n", __func__);
        }

        if(ret == 0) {
            /* New container, send containing data using indicated channel */
            msg = (app_remote_device_msg_container_t *)value;
            hdr = (struct rpmsg_kdrv_device_header *)msg->data;

            ret = appRemoteDeviceValidateContainer(msg);
            if(ret)
                appLogPrintf("%s: Not a valid message container\n", __func__);

        }

        if(ret == 0) {
            ret = RPMessage_send(core->rpmsg_handle, core->core_id, g_rdev_data.prm.remote_endpt,
                    core->local_endpt, msg->data, msg->len);
            if (ret != IPC_SOK)
            {
                appLogPrintf("%s: RPMessage_send failed\n", __func__);
                ret = -1;
            }
        }

        if(ret == 0 && hdr->packet_type == RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE) {
            ret = appRemoteDeviceFreeMessage(msg);
            if(ret != 0)
                appLogPrintf("%s: Could not free message\n", __func__);
        } else if(ret == 0) {
            SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);
            ret = appQueuePut(&g_rdev_data.pend_req_queue, msg);
            if(ret != 0)
                appLogPrintf("%s: Could not put container to pending request queue\n", __func__);
            SemaphoreP_post(g_rdev_data.lock_sem);
        }

        APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);

    }
}

int32_t appRemoteDeviceHandleMessageInit(app_remote_device_device_data_t *dev, struct rpmsg_kdrv_device_header *hdr)
{
    int32_t ret = 0;

    if(ret == 0) {
        if(TRUE) {
            appLogPrintf("%s: init device does not support message\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

int32_t appRemoteDeviceHandleMessageDevice(app_remote_device_device_data_t *dev, struct rpmsg_kdrv_device_header *hdr)
{
    int32_t ret = 0;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        if(dev->message_cb == NULL) {
            appLogPrintf("%s: Device does not have a message callback\n", __func__);
            ret = -1;
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        ret = dev->message_cb(dev->message_cb_priv, hdr);
        if(ret != 0)
            appLogPrintf("%s: device message callback failed\n", __func__);
    }

    return ret;
}

static app_remote_device_msg_container_t *appRemoteDeviceFindMsgContainerForReqId(uint32_t req_id)
{
    int32_t ret;
    void *value;
    uint32_t loop_complete = FALSE;
    uint32_t found = FALSE;
    app_remote_device_msg_container_t *cont = NULL, *first = NULL, *temp;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);
    while(loop_complete == FALSE && found == FALSE) {
        ret = 0;

        if(ret == 0) {
            ret = appQueueGet(&g_rdev_data.pend_req_queue, &value);
            if(ret != 0)
                appLogPrintf("%s: Could not get from pending request queue\n", __func__);
        }

        if(ret == 0) {
            temp = value;
            if(first == NULL)
                first = temp;
            else if(first == temp)
                loop_complete = TRUE;

            if(*temp->req_id == req_id) {
                cont = temp;
                found = TRUE;
            } else {
                ret = appQueuePut(&g_rdev_data.pend_req_queue, temp);
                if(ret != 0)
                    appLogPrintf("%s: Could not put back to pending request queue\n", __func__);
            }
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    return cont;
}

static int32_t appRemoteDeviceHandleResponse(app_remote_device_core_data_t *core, struct rpmsg_kdrv_device_header *hdr)
{
    int32_t ret = 0;
    app_remote_device_msg_container_t *cont;

    if(ret == 0) {
        cont = appRemoteDeviceFindMsgContainerForReqId(hdr->packet_id);
        if(cont == NULL) {
            appLogPrintf("%s: Could not find request ID\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(hdr->packet_size > cont->resp_avail) {
            appLogPrintf("%s: Not enough free space to copy response\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        cont->resp_len = min(hdr->packet_size, cont->resp_avail);
        memcpy(cont->resp_data, hdr, cont->resp_len);
        SemaphoreP_post(cont->wait_sem);
    }

    return ret;
}

int32_t appRemoteDeviceHandleMessage(app_remote_device_core_data_t *core, struct rpmsg_kdrv_device_header *hdr)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;

    if(ret == 0) {
        switch(hdr->device_id) {
            case RPMSG_KDRV_TP_DEVICE_ID_INIT:
                ret = appRemoteDeviceHandleMessageInit(core->conf_device, hdr);
                break;
            default:
                dev = appRemoteDeviceFindCoreDeviceByTpId(core, hdr->device_id);
                if(dev == NULL) {
                    appLogPrintf("%s: Could not find a device\n", __func__);
                    ret = -1;
                } else {
                    ret = appRemoteDeviceHandleMessageDevice(dev, hdr);
                }
        }

        if(ret != 0)
            appLogPrintf("%s: Could not handle message", __func__);
    }

    return ret;

}

static void appRemoteDeviceRxTaskFn(void *arg0, void *arg1)
{
    char data[APP_REMOTE_DEVICE_MAX_PACKET_SIZE];
    uint32_t remote_ept;
    uint32_t remote_proc;
    uint16_t len;
    int32_t ret = 0;
    struct rpmsg_kdrv_device_header *hdr;
    app_remote_device_core_data_t *core = (app_remote_device_core_data_t *)arg0;

    while(1)
    {
        ret = 0;

        if(ret == 0) {
            /* Wait for a message */
            ret = RPMessage_recv(core->rpmsg_handle, (void *)data, &len, &remote_ept, &remote_proc,
                    IPC_RPMESSAGE_TIMEOUT_FOREVER);
            if(ret != IPC_SOK)
            {
                appLogPrintf("%s: RPMessage_recv failed\n", __func__);
                ret = -1;
            }
        }

        if(ret == 0) {
            hdr = (struct rpmsg_kdrv_device_header *)data;

            switch(hdr->packet_type) {
                case RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE:
                    ret = appRemoteDeviceHandleMessage(core, hdr);
                    break;
                case RPMSG_KDRV_TP_PACKET_TYPE_RESPONSE:
                    ret = appRemoteDeviceHandleResponse(core, hdr);
                    break;
                default:
                    appLogPrintf("%s: unsupported message type\n", __func__);
                    ret = -1;
            }

            if(ret != 0)
                appLogPrintf("%s: Could not handle message\n", __func__);
        }

        APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);
    }
}


static int32_t appRemoteDeviceCreateDevice(app_remote_device_core_data_t *core, struct rpmsg_kdrv_init_dev_info_response *resp,
        uint32_t idx, uint32_t is_conf)
{
    int32_t ret = 0;
    uint32_t id;
    struct rpmsg_kdrv_init_device_info *sdev;
    app_remote_device_device_data_t *ddev;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        if(g_rdev_data.dev_count >= APP_REMOTE_DEVICE_MAX_DEVICES) {
            appLogPrintf("%s: [device %u] Could not find slot for device\n", __func__, g_rdev_data.dev_count);
            ret = -1;
        }
    }

    if(ret == 0 && is_conf == FALSE) {
        if(core->dev_count >= APP_REMOTE_DEVICE_MAX_DEVICES_CORE) {
            appLogPrintf("%s: [core-device %u] Could not find slot for device\n", __func__, core->dev_count);
            ret = -1;
        }
    }

    if(ret == 0) {
        id = g_rdev_data.dev_count;

        ddev = &g_rdev_data.dev_data[id];
        ddev->serial = id;
        ddev->core = core;

        if(is_conf == FALSE) {
            sdev = &resp->devices[idx];

            ddev->tp_id = sdev->device_id;
            ddev->tp_type = sdev->device_type;
            ddev->data_len = min(APP_REMOTE_DEVICE_DEVICE_DATA_LEN, sdev->device_data_len);
            snprintf((char *)&ddev->name[0], APP_REMOTE_DEVICE_DEVICE_NAME_LEN, "%s", sdev->device_name);
            if(sdev->device_data_len > 0) {
                memcpy(&ddev->data[0], &resp->device_data[sdev->device_data_offset], ddev->data_len);
            }

        } else {
            ddev->tp_type = RPMSG_KDRV_TP_DEVICE_TYPE_INIT;
        }

        g_rdev_data.dev_count++;

        if(is_conf == FALSE) {
            core->dev[core->dev_count] = ddev;
            core->dev_count++;
        } else {
            core->conf_device = ddev;
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    return ret;
}

static int32_t appRemoteDeviceStartTxRxTasks(app_remote_device_core_data_t *core)
{
    int32_t ret = 0;
    SemaphoreP_Params    sem_params;

    if(ret == 0) {
        /* The send queue. Task picks up from this queue and sends */
        ret = appQueueInit(&core->send_queue, FALSE, 0, 0, NULL, 0);
        if(ret != 0)
            appLogPrintf("%s: Could not initialize send queue\n", __func__);
    }

    if(ret == 0) {
        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_COUNTING;

        core->send_sem = SemaphoreP_create(0, &sem_params);
        if(core->send_sem == NULL) {
            appLogPrintf("%s: Could not initialize send semaphore\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* Start the RX task */
        TaskP_Params_init(&core->rx_params);
        core->rx_params.priority = 3;
        core->rx_params.stack = &g_rx_tsk_stack[core->serial * APP_REMOTE_DEVICE_STACKSIZE];
        core->rx_params.stacksize = APP_REMOTE_DEVICE_STACKSIZE;
        core->rx_params.arg0 = core;
        core->rx_task = TaskP_create(&appRemoteDeviceRxTaskFn, &core->rx_params);
        if(core->rx_task == NULL) {
            appLogPrintf("%s: Failed to create RX task\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* Start the TX task */
        TaskP_Params_init(&core->tx_params);
        core->tx_params.priority = 3;
        core->tx_params.stack = &g_tx_tsk_stack[core->serial * APP_REMOTE_DEVICE_STACKSIZE];
        core->tx_params.stacksize = APP_REMOTE_DEVICE_STACKSIZE;
        core->tx_params.arg0 = core;
        core->tx_task = TaskP_create(&appRemoteDeviceTxTaskFn, &core->tx_params);
        if(core->tx_task == NULL) {
            appLogPrintf("%s: Failed to create TX task\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

static void appRemoteDeviceDiscoverTaskFn(void *arg0, void *arg1)
{
    int32_t ret = 0;
    void *value;
    uint32_t *req_id;
    uint32_t cnt;
    uint8_t rmsg[APP_REMOTE_DEVICE_MAX_PACKET_SIZE];
    uint16_t rlen;
    uint32_t remote_ept;
    uint32_t remote_proc;
    struct rpmsg_kdrv_device_header *hdr;
    struct rpmsg_kdrv_device_header *rhdr;
    struct rpmsg_kdrv_init_dev_info_response *resp;
    struct rpmsg_kdrv_init_dev_info_request *req;
    app_remote_device_core_data_t *core = (app_remote_device_core_data_t *)arg0;

    if(ret == 0) {
        ret = appQueueGet(&g_rdev_data.message_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty message\n", __func__);
    }

    if(ret == 0) {
        hdr = (struct rpmsg_kdrv_device_header *)value;

        ret = appQueueGet(&g_rdev_data.req_id_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get a request id\n", __func__);
    }

    if(ret == 0) {
        req_id = (uint32_t *)value;
        req = (struct rpmsg_kdrv_init_dev_info_request*)(DEVHDR_2_MSG(hdr));
        memset(hdr, 0, sizeof(*hdr) + sizeof(*req));

        hdr->device_id = RPMSG_KDRV_TP_DEVICE_ID_INIT;
        hdr->packet_type = RPMSG_KDRV_TP_PACKET_TYPE_REQUEST;
        hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_CLIENT;
        hdr->packet_id = *req_id;
        hdr->packet_size = sizeof(*hdr) + sizeof(*req);

        req->header.message_type = RPMSG_KDRV_TP_INIT_DEV_INFO_REQUEST;

        ret = RPMessage_send(core->rpmsg_handle, core->core_id, g_rdev_data.prm.remote_endpt,
                core->local_endpt, hdr, hdr->packet_size);
        if (ret != IPC_SOK)
        {
            appLogPrintf("%s: RPMessage_send failed\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        ret = RPMessage_recv(core->rpmsg_handle, (void *)rmsg, &rlen, &remote_ept, &remote_proc,
                IPC_RPMESSAGE_TIMEOUT_FOREVER);
        if(ret != IPC_SOK)
        {
            appLogPrintf("%s: RPMessage_recv failed\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        rhdr = (struct rpmsg_kdrv_device_header *)rmsg;
        resp = DEVHDR_2_MSG(rhdr);

        for(cnt = 0; cnt < resp->num_devices; cnt++) {
            ret = appRemoteDeviceCreateDevice(core, resp, cnt, FALSE);
            if(ret != 0)
                appLogPrintf("%s: Could not create a device for %s(%u)\n", __func__,
                        resp->devices[cnt].device_name, core->core_id);
        }
    }

    if(ret == 0) {
        ret = appRemoteDeviceCreateDevice(core, resp, cnt, TRUE);
        if(ret != 0)
            appLogPrintf("%s: Could not create conf device for %u\n", __func__, core->core_id);
    }

    if(ret == 0) {
        ret = appQueuePut(&g_rdev_data.message_pool, hdr);
        if(ret != 0)
            appLogPrintf("%s: Could not put empty message\n", __func__);
    }

    if(ret == 0) {
        ret = appQueuePut(&g_rdev_data.req_id_pool, req_id);
        if(ret != 0)
            appLogPrintf("%s: Could not put reqquest id\n", __func__);
    }

    if(ret == 0) {
        ret = appRemoteDeviceStartTxRxTasks(core);
        if(ret != 0)
            appLogPrintf("%s: Could not start Tx and Rx tasks\n", __func__);
    }

    APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);
}

static int32_t appRemoteDeviceCreateForCore(uint32_t core_idx)
{
    int32_t ret = 0;
    uint32_t id;
    RPMessage_Params    params;
    app_remote_device_core_data_t *core;

    if(ret == 0) {
        if(g_rdev_data.core_count >= APP_REMOTE_DEVICE_MAX_CORES) {
            appLogPrintf("%s: [core %u] Could not find slot for core\n", __func__, g_rdev_data.core_count);
            ret = -1;
        }
    }

    if(ret == 0) {
        id = g_rdev_data.core_count;
        core = &g_rdev_data.core_data[id];

        memset(core, 0, sizeof(*core));
        core->serial = id;
        core->core_id = g_rdev_data.prm.cores[core_idx];

        /* Create the RPMSG endpoint */
        RPMessageParams_init(&params);
        params.requestedEndpt = RPMESSAGE_ANY;
        params.buf = &g_app_remote_device_rpmsg_buf[core->serial * APP_REMOTE_DEVICE_CORE_RPMSG_BUF_SIZE];
        params.bufSize = APP_REMOTE_DEVICE_CORE_RPMSG_BUF_SIZE;

        core->rpmsg_handle = RPMessage_create(&params, &core->local_endpt);
        if(core->rpmsg_handle == NULL)
        {
            appLogPrintf("%s: Failed to create endpoint\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* Start the RX task */
        TaskP_Params_init(&core->discov_params);
        core->discov_params.priority = 3;
        core->discov_params.stack = &g_discov_tsk_stack[core->serial * APP_REMOTE_DEVICE_STACKSIZE];
        core->discov_params.stacksize = APP_REMOTE_DEVICE_STACKSIZE;
        core->discov_params.arg0 = core;
        core->discov_task = TaskP_create(&appRemoteDeviceDiscoverTaskFn, &core->discov_params);
        if(core->discov_task == NULL) {
            appLogPrintf("%s: Failed to create discovery task\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        g_rdev_data.core_count++;
    }

    return ret;
}

static void appRemoteDeviceInitFn(void *arg0, void *arg1)
{
    int32_t ret = 0;
    uint32_t cnt;
    SemaphoreP_Handle    wait_sem = (SemaphoreP_Handle) arg0;

    if(ret == 0) {
        /*Wait for HLOS to connect */
        SemaphoreP_pend(wait_sem, SemaphoreP_WAIT_FOREVER);

        for(cnt = 0; cnt < g_rdev_data.prm.num_cores; cnt++) {
            ret = appRemoteDeviceCreateForCore(cnt);
            if(ret != 0) {
                appLogPrintf("%s: Could not create remote device for core %d\n", __func__, cnt);
                break;
            }
        }
    }

    APP_REMOTE_DEVICE_ASSERT_SUCCESS(ret);

}

static int32_t appRemoteDevicePoolsInit(app_remote_device_init_prm_t *prm)
{
    int32_t ret = 0;
    uint32_t cnt;
    void *value;
    uint32_t *req_id;

    if(ret == 0) {
        /* The queue for pending requests */
        ret = appQueueInit(&g_rdev_data.pend_req_queue, FALSE, 0, 0, NULL, 0);
        if(ret != 0)
            appLogPrintf("%s: Could not initialize pending request queue\n", __func__);
    }

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

    if(ret == 0) {
        /* The pool for request IDs */
        ret = appQueueInit(&g_rdev_data.req_id_pool, TRUE, APP_REMOTE_DEVICE_MAX_REQUESTS,
                sizeof(uint32_t), g_req_id_pool_storage, sizeof(g_req_id_pool_storage));
        if(ret != 0) {
            appLogPrintf("%s: Could not initialize request ID pool\n", __func__);
        }
    }

    if(ret == 0) {
        for(cnt = RPMSG_KDRV_TP_PACKET_ID_FIRST; cnt < RPMSG_KDRV_TP_PACKET_ID_FIRST + APP_REMOTE_DEVICE_MAX_REQUESTS; cnt++) {
            if(ret == 0) {
                ret = appQueueGet(&g_rdev_data.req_id_pool, &value);
                if(ret != 0)
                    appLogPrintf("%s: Could not get empty id\n", __func__);
            }
            if(ret == 0) {
                req_id = (uint32_t *)value;
                *req_id = cnt;

                ret = appQueuePut(&g_rdev_data.req_id_pool, req_id);
                if(ret != 0)
                    appLogPrintf("%s: Could not put filled id\n", __func__);
            }

            if(ret != 0) {
                appLogPrintf("%s: Could not initialize request ID values\n", __func__);
                break;
            }
        }
    }

    return ret;
}

int32_t appRemoteDeviceInit(app_remote_device_init_prm_t *prm)
{
    int32_t ret = 0;
    SemaphoreP_Params sem_params;

    char err_str[128];

    if(ret == 0) {
        /* validate params. */
        ret = appRemoteDeviceValidateInitPrm(prm, err_str, 128);
        if(ret != 0)
            appLogPrintf("%s: Could not validate init params: %s\n", __func__, err_str);
    }

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
        TaskP_Params_init(&g_rdev_data.init_task_prm);
        g_rdev_data.init_task_prm.priority = 3;
        g_rdev_data.init_task_prm.stack = &g_init_tsk_stack;
        g_rdev_data.init_task_prm.stacksize = APP_REMOTE_DEVICE_STACKSIZE;
        g_rdev_data.init_task_prm.arg0 = (void *)prm->wait_sem;

        g_rdev_data.init_task = TaskP_create(&appRemoteDeviceInitFn, &g_rdev_data.init_task_prm);
        if(g_rdev_data.init_task == NULL) {
            appLogPrintf("%s: Could not start init task\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

static int32_t appRemoteDeviceFreeCbFn(void *priv, void *msg, uint32_t len)
{
    int32_t ret = 0;

    if(ret == 0) {
        /* Put the empty message back in message pool */
        ret = appQueuePut(&g_rdev_data.message_pool, msg);
        if(ret != 0)
            appLogPrintf("%s: Could not put empty message to pool\n", __func__);
    }

    return ret;
}

static int32_t appRemoteDeviceDevSendMessage(app_remote_device_device_data_t *dev, void *data, uint32_t len,
        void* free_cb_data, int32_t (*free_cb)(void *priv, void *msg, uint32_t len))
{
    int32_t ret = 0;
    void *value;
    app_remote_device_msg_container_t *cont;

    if(ret == 0) {
        ret = appQueueGet(&g_rdev_data.msg_container_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty container\n", __func__);
    }

    if(ret == 0) {
        cont = (app_remote_device_msg_container_t *)value;
        memset(cont, 0, sizeof(*cont));

        cont->device = dev;
        cont->data = data;
        cont->len = len;
        cont->free_cb_data = free_cb_data;
        cont->free_cb = free_cb;
        ret = appQueuePut(&dev->core->send_queue, cont);
        if(ret != 0)
            appLogPrintf("%s: Could not put msg to send queue\n", __func__);
    }

    if(ret == 0) {
        SemaphoreP_post(dev->core->send_sem);
    }

    return ret;
}

static int32_t appRemoteDeviceDevServiceRequest(app_remote_device_device_data_t *dev, void *data, uint32_t len, void* resp_data,
        uint32_t resp_avail, uint32_t *resp_len)
{
    int32_t ret = 0;
    SemaphoreP_Status sret;
    void *value;
    uint32_t *req_id;
    app_remote_device_msg_container_t *cont;
    struct rpmsg_kdrv_device_header *hdr;
    SemaphoreP_Params    sem_params;

    if(ret == 0) {
        ret = appQueueGet(&g_rdev_data.msg_container_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty container\n", __func__);
    }

    if(ret == 0) {
        cont = (app_remote_device_msg_container_t *)value;
        memset(cont, 0, sizeof(*cont));
        hdr = (struct rpmsg_kdrv_device_header *)data;

        ret = appQueueGet(&g_rdev_data.req_id_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get a request id\n", __func__);
    }


    if(ret == 0) {
        req_id = (uint32_t *)value;
        hdr->packet_id = *req_id;

        cont->device = dev;
        cont->data = data;
        cont->len = len;
        cont->resp_data = resp_data;
        cont->resp_avail = resp_avail;

        cont->req_id = req_id;

        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_BINARY;

        cont->wait_sem = SemaphoreP_create(0, &sem_params);
        if(cont->wait_sem == NULL) {
            appLogPrintf("%s: Could not initialize message semaphore\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        ret = appQueuePut(&dev->core->send_queue, cont);
        if(ret != 0)
            appLogPrintf("%s: Could not put msg to send queue\n", __func__);
    }

    if(ret == 0) {
        SemaphoreP_post(dev->core->send_sem);
        SemaphoreP_pend(cont->wait_sem, SemaphoreP_WAIT_FOREVER);

        sret = SemaphoreP_delete(cont->wait_sem);
        if(sret != SemaphoreP_OK) {
            appLogPrintf("%s: Could not delete container semaphore\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        ret = appQueuePut(&g_rdev_data.req_id_pool, cont->req_id);
        if(ret != 0)
            appLogPrintf("%s: Could not put reqquest id\n", __func__);
    }

    if(ret == 0) {
        *resp_len = cont->resp_len;
        ret = appQueuePut(&g_rdev_data.msg_container_pool, cont);
        if(ret != 0)
            appLogPrintf("%s: Could not put empty container\n", __func__);
    }

    return ret;
}

int32_t appRemoteDeviceSendMessage(uint32_t device_id, void *data, uint32_t len,
        void* free_cb_data, int32_t (*free_cb)(void *priv, void *msg, uint32_t len))
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;
    struct rpmsg_kdrv_device_header *hdr;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        dev = appRemoteDeviceDataFindDeviceForId(device_id);
        if(dev == NULL) {
            appLogPrintf("%s: Could not find requested device\n", __func__);
            ret = -1;
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        hdr = (struct rpmsg_kdrv_device_header *)data;

        hdr->device_id = dev->tp_id;
        hdr->packet_type = RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE;
        hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_CLIENT;
        hdr->packet_id = RPMSG_KDRV_TP_PACKET_ID_NONE;
        hdr->packet_size = len;

        ret = appRemoteDeviceDevSendMessage(dev, data, len, free_cb_data, free_cb);
        if(ret != 0)
            appLogPrintf("%s: Could not send message\n", __func__);

    }

    return ret;
}

int32_t appRemoteDeviceServiceRequest(uint32_t device_id, void *data, uint32_t len, void *resp, uint32_t resp_avail, uint32_t *resp_len)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;
    struct rpmsg_kdrv_device_header *hdr;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        dev = appRemoteDeviceDataFindDeviceForId(device_id);
        if(dev == NULL) {
            appLogPrintf("%s: Could not find requested device\n", __func__);
            ret = -1;
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        hdr = (struct rpmsg_kdrv_device_header *)data;

        hdr->device_id = dev->tp_id;
        hdr->packet_type = RPMSG_KDRV_TP_PACKET_TYPE_REQUEST;
        hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_CLIENT;
        /* This will be filled up in the next function */
        hdr->packet_id = RPMSG_KDRV_TP_PACKET_ID_NONE;
        hdr->packet_size = len;

        ret = appRemoteDeviceDevServiceRequest(dev, data, len, resp, resp_avail, resp_len);
        if(ret != 0)
            appLogPrintf("%s: Could not service request\n", __func__);

    }

    return ret;
}

#if 0
int32_t appRemoteDeviceSendRequestCallback(uint32_t device_id, uint8_t *data, uint32_t len,
        uint32_t (*callback)(uint8_t *req, uint32_t *req_len, uint8_t *resp, uint32_t *resp_len));
#endif

int32_t appRemoteDeviceConnect(app_remote_device_device_connect_prm_t *prm, uint32_t *device_id)
{
    int32_t ret = 0;
    void *value;
    app_remote_device_device_data_t *dev;
    struct rpmsg_kdrv_device_header *hdr;
    struct rpmsg_kdrv_init_connect_message *msg;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        dev = appRemoteDeviceDataFindDeviceForName(prm->device_name);
        if(dev == NULL)
        {
            *device_id = APP_REMOTE_DEVICE_DEVICE_ID_EAGAIN;
        }
    }

    if(ret == 0 && dev != NULL) {
        dev->message_cb = prm->message_cb;
        dev->message_cb_priv = prm->message_cb_priv;
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0 && dev != NULL) {
        ret = appQueueGet(&g_rdev_data.message_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty message\n", __func__);
    }

    if(ret == 0 && dev != NULL) {
        hdr = (struct rpmsg_kdrv_device_header *)value;
        msg = (struct rpmsg_kdrv_init_connect_message *)(DEVHDR_2_MSG(hdr));
        memset(hdr, 0, sizeof(*hdr) + sizeof(*msg));

        hdr->device_id = RPMSG_KDRV_TP_DEVICE_ID_INIT;
        hdr->packet_type = RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE;
        hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_CLIENT;
        hdr->packet_id = RPMSG_KDRV_TP_PACKET_ID_NONE;
        hdr->packet_size = sizeof(*hdr) + sizeof(*msg);

        msg->header.message_type = RPMSG_KDRV_TP_INIT_CONNECT_MESSAGE;
        msg->device_id = dev->tp_id;

        ret = appRemoteDeviceDevSendMessage(dev->core->conf_device, hdr, hdr->packet_size,
                NULL, appRemoteDeviceFreeCbFn);
        if(ret != 0)
            appLogPrintf("%s: Could not send connect message\n", __func__);

    }

    if(ret == 0 && dev != NULL) {
        *device_id = dev->serial;
    }

    return ret;

}

int32_t appRemoteDeviceDisconnect(uint32_t device_id)
{
    int32_t ret = 0;
    void *value;
    app_remote_device_device_data_t *dev;
    struct rpmsg_kdrv_device_header *hdr;
    struct rpmsg_kdrv_init_connect_message *msg;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        dev = appRemoteDeviceDataFindDeviceForId(device_id);
        if(dev == NULL) {
            appLogPrintf("%s: Could not find requested device\n", __func__);
            ret = -1;
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    if(ret == 0) {
        ret = appQueueGet(&g_rdev_data.message_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty message\n", __func__);
    }

    if(ret == 0) {
        hdr = (struct rpmsg_kdrv_device_header *)value;
        msg = (struct rpmsg_kdrv_init_connect_message *)(DEVHDR_2_MSG(hdr));
        memset(hdr, 0, sizeof(*hdr) + sizeof(*msg));

        hdr->device_id = RPMSG_KDRV_TP_DEVICE_ID_INIT;
        hdr->packet_type = RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE;
        hdr->packet_source = RPMSG_KDRV_TP_PACKET_SOURCE_CLIENT;
        hdr->packet_id = RPMSG_KDRV_TP_PACKET_ID_NONE;
        hdr->packet_size = sizeof(*hdr) + sizeof(*msg);

        msg->header.message_type = RPMSG_KDRV_TP_INIT_DISCONNECT_MESSAGE;
        msg->device_id = dev->tp_id;

        ret = appRemoteDeviceDevSendMessage(dev->core->conf_device, hdr, hdr->packet_size,
                NULL, appRemoteDeviceFreeCbFn);
        if(ret != 0)
            appLogPrintf("%s: Could not send disconnect message\n", __func__);

    }

    return ret;

}

int32_t appRemoteDeviceGetType(uint32_t device_id, uint32_t *device_type)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        dev = appRemoteDeviceDataFindDeviceForId(device_id);
        if(dev == NULL) {
            appLogPrintf("%s: Could not find requested device\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        switch(dev->tp_type) {
            case RPMSG_KDRV_TP_DEVICE_TYPE_DISPLAY:
                *device_type = APP_REMOTE_DEVICE_DEVICE_TYPE_DISPLAY;
                break;
            case RPMSG_KDRV_TP_DEVICE_TYPE_DEMO:
                *device_type = APP_REMOTE_DEVICE_DEVICE_TYPE_DEMO;
                break;
            case RPMSG_KDRV_TP_DEVICE_TYPE_ETHSWITCH:
                *device_type = APP_REMOTE_DEVICE_DEVICE_TYPE_ETHSWITCH;
                break;
            default:
                appLogPrintf("%s: unidentified device type\n", __func__);
                ret = -1;
        }
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    return ret;

}

int32_t appRemoteDeviceGetData(uint32_t device_id, uint8_t *device_data, uint32_t avail_len, uint32_t *act_len)
{
    int32_t ret = 0;
    app_remote_device_device_data_t *dev;

    SemaphoreP_pend(g_rdev_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        dev = appRemoteDeviceDataFindDeviceForId(device_id);
        if(dev == NULL) {
            appLogPrintf("%s: Could not find requested device\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        *act_len = min(avail_len, dev->data_len);
        memcpy(device_data, &dev->data[0], *act_len);
    }

    SemaphoreP_post(g_rdev_data.lock_sem);

    return ret;

}
