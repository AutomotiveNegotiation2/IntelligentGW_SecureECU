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

#include <ti/csl/soc.h>
#include <ti/osal/osal.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/SemaphoreP.h>

#include <protocol/rpmsg-kdrv-transport-demo.h>
#include <server-rtos/include/app_log.h>
#include <server-rtos/include/app_queue.h>
#include <server-rtos/include/app_remote_device.h>
#include <server-rtos/include/app_remote_device_demo.h>

#define APP_REMOTE_DEMO_MAX_MESSAGES         (32)
#define APP_REMOTE_DEMO_MAX_PACKET_SIZE      (512)

#define g_sender_tsk_stack_size                 (0x2000)
#define g_message_monitor_tsk_stack_size                 (0x2000)

#define APP_REMOTE_DEMO_ASSERT_SUCCESS(x)  { if((x)!=0) while(1); }
#define DEVHDR_2_MSG(x) ((void *)(((struct rpmsg_kdrv_device_header *)(x)) + 1))

struct __app_remote_demo_inst_data_t;
typedef struct __app_remote_demo_inst_data_t app_remote_demo_inst_data_t;
struct __app_remote_demo_data_t;
typedef struct __app_remote_demo_data_t app_remote_demo_data_t;
struct __app_remote_demo_message_t;
typedef struct __app_remote_demo_message_t app_remote_demo_message_t;

struct __app_remote_demo_inst_data_t {
    app_remote_demo_inst_prm_t inst_prm;
    uint32_t device_id;
    uint32_t serial;
    app_remote_device_channel_t *channel;

    uint32_t num_incoming_message;
    SemaphoreP_Handle message_sem;    
    TaskP_Handle message_mon_task;    
};

struct __app_remote_demo_data_t {
    app_remote_demo_init_prm_t prm;
    uint32_t inst_count;
    app_remote_demo_inst_data_t inst_data[APP_REMOTE_DEMO_MAX_INSTANCES];
    app_queue_t send_queue;
    app_queue_t message_pool;
    SemaphoreP_Handle send_sem;
    SemaphoreP_Handle lock_sem;
    TaskP_Handle sender_task;
};

struct __app_remote_demo_message_t {
    uint32_t request_id;
    uint32_t message_size;
    uint32_t device_id;
    uint32_t is_response;
    app_remote_device_channel_t *channel;
    uint8_t data[0];

};

/* stack for sender task */
static uint8_t g_sender_tsk_stack[g_sender_tsk_stack_size] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));
static uint8_t g_message_monitor_tsk_stack[g_message_monitor_tsk_stack_size * APP_REMOTE_DEMO_MAX_INSTANCES] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));

/* Storage areas for pools */
static uint8_t g_message_pool_storage[(APP_REMOTE_DEMO_MAX_PACKET_SIZE + sizeof(app_remote_demo_message_t)+ APP_QUEUE_ELEM_META_SIZE) * APP_REMOTE_DEMO_MAX_MESSAGES];

static app_remote_demo_data_t g_rdemo_data;

static uint32_t min(uint32_t a, uint32_t b)
{
    if(a > b)
        return b;
    else
        return a;
}

static app_remote_demo_inst_data_t *appRemoteDemoDataFindDeviceId(uint32_t device_id)
{
    uint32_t cnt;
    app_remote_demo_inst_data_t *inst = NULL;

    for(cnt = 0; cnt < g_rdemo_data.inst_count; cnt++) {
        if(g_rdemo_data.inst_data[cnt].device_id == device_id) {
            inst = &g_rdemo_data.inst_data[cnt];
            break;
        }
    }

    return inst;
}

static int32_t appRemoteDemoHandlePingRequest(app_remote_demo_inst_data_t *inst,
        app_remote_device_channel_t *channel, uint32_t request_id,
        struct rpmsg_kdrv_demodev_ping_request *req)
{
    void *value;
    int32_t ret = 0;
    app_remote_demo_message_t *msg;
    struct rpmsg_kdrv_device_header *dev_hdr;
    struct rpmsg_kdrv_demodev_ping_response *resp;

    if(ret == 0) {
        ret = appQueueGet(&g_rdemo_data.message_pool, &value);
        if(ret != 0)
            appLogPrintf("%s: Could not get an empty message\n", __func__);
    }

    if(ret == 0) {
        msg = (app_remote_demo_message_t *)value;
        memset(msg, 0, sizeof(*msg) + sizeof(*dev_hdr) + sizeof(*resp));

        msg->request_id = request_id;
        msg->message_size = sizeof(*resp);
        msg->device_id = inst->device_id;
        msg->is_response = TRUE;
        msg->channel = inst->channel;

        dev_hdr = (struct rpmsg_kdrv_device_header *)(&msg->data[0]);
        resp = (struct rpmsg_kdrv_demodev_ping_response *)(DEVHDR_2_MSG(dev_hdr));

        resp->header.message_type = RPMSG_KDRV_TP_DEMODEV_PING_RESPONSE;
        memcpy(&resp->data[0], &req->data[0], RPMSG_KDRV_TP_DEMODEV_MESSAGE_DATA_LEN);

        ret = appQueuePut(&g_rdemo_data.send_queue, msg);
        if(ret != 0)
            appLogPrintf("%s: Could not queue message for transmission\n", __func__);
    }

    if(ret == 0)
        SemaphoreP_post(g_rdemo_data.send_sem);

    return ret;
}


static int32_t appRemoteDemoRequest(uint32_t device_id, app_remote_device_channel_t *channel,
        uint32_t request_id, void *data, uint32_t len)
{
    app_remote_demo_inst_data_t *inst;
    struct rpmsg_kdrv_demodev_message_header *hdr = data;
    int32_t ret = 0;

    SemaphoreP_pend(g_rdemo_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        inst = appRemoteDemoDataFindDeviceId(device_id);
        if(inst == NULL) {
            appLogPrintf("%s: Could not find a instance\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(channel != inst->channel) {
            appLogPrintf("%s: mismatch channel\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        switch(hdr->message_type) {
            case RPMSG_KDRV_TP_DEMODEV_PING_REQUEST:
                ret = appRemoteDemoHandlePingRequest(inst, channel, request_id,
                        (struct rpmsg_kdrv_demodev_ping_request *)data);
                break;
            default:
                appLogPrintf("%s: unidentified request\n", __func__);
                ret = -1;
        }
    }

    SemaphoreP_post(g_rdemo_data.lock_sem);
    return ret;
}

static int32_t appRemoteDemoHandleC2sMessage(app_remote_demo_inst_data_t *inst,
        app_remote_device_channel_t *channel, struct rpmsg_kdrv_demodev_c2s_message *req)
{
    int32_t ret = 0;

    if(ret == 0) {
        inst->num_incoming_message++;
        SemaphoreP_post(inst->message_sem);
    }

    return ret;
}

static int32_t appRemoteDemoMessage(uint32_t device_id, app_remote_device_channel_t *channel,
        void *data, uint32_t len)
{
    app_remote_demo_inst_data_t *inst;
    struct rpmsg_kdrv_demodev_message_header *hdr = data;
    int32_t ret = 0;

    SemaphoreP_pend(g_rdemo_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        inst = appRemoteDemoDataFindDeviceId(device_id);
        if(inst == NULL) {
            appLogPrintf("%s: Could not find a instance\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(channel != inst->channel) {
            appLogPrintf("%s: mismatch channel\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        switch(hdr->message_type) {
            case RPMSG_KDRV_TP_DEMODEV_C2S_MESSAGE:
                ret = appRemoteDemoHandleC2sMessage(inst, channel,
                        (struct rpmsg_kdrv_demodev_c2s_message *)data);
                break;
            default:
                appLogPrintf("%s: unidentified request\n", __func__);
                ret = -1;
        }
    }

    SemaphoreP_post(g_rdemo_data.lock_sem);
    return ret;
}

static int32_t appRemoteDemoDisconnect(uint32_t device_id)
{
    app_remote_demo_inst_data_t *inst;
    int32_t ret = 0;

    SemaphoreP_pend(g_rdemo_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        inst = appRemoteDemoDataFindDeviceId(device_id);
        if(inst == NULL) {
            appLogPrintf("%s: Could not find a instance\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /*
         * Connect the display to one remote-procId + remote-endpt.
         * All future messages from this channel will be entertained
         */
        inst->channel = NULL;
    }

    SemaphoreP_post(g_rdemo_data.lock_sem);
    return ret;
}

static int32_t appRemoteDemoConnect(uint32_t device_id, app_remote_device_channel_t *channel)
{
    app_remote_demo_inst_data_t *inst;
    int32_t ret = 0;

    SemaphoreP_pend(g_rdemo_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        inst = appRemoteDemoDataFindDeviceId(device_id);
        if(inst == NULL) {
            appLogPrintf("%s: Could not find a instance\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /*
         * Connect the display to one remote-procId + remote-endpt.
         * All future messages from this channel will be entertained
         */
        inst->channel = channel;
    }

    SemaphoreP_post(g_rdemo_data.lock_sem);
    return ret;
}

static uint32_t appRemoteDemoFillPrivData(uint32_t device_id, void *priv_data, uint32_t avail_len)
{
    struct rpmsg_kdrv_demodev_device_data *demo_data = (struct rpmsg_kdrv_demodev_device_data *)priv_data;
    app_remote_demo_inst_data_t *inst;
    int32_t ret = 0;

    SemaphoreP_pend(g_rdemo_data.lock_sem, SemaphoreP_WAIT_FOREVER);

    if(ret == 0) {
        inst = appRemoteDemoDataFindDeviceId(device_id);
        if(inst == NULL) {
            appLogPrintf("%s: Could not find a instance\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        memcpy(&demo_data->charString[0], &inst->inst_prm.data[0], min(avail_len, min(APP_REMOTE_DEMO_MAX_DATA_LEN, RPMSG_KDRV_TP_DEMODEV_DEVICE_DATA_LEN)));
    }

    SemaphoreP_post(g_rdemo_data.lock_sem);
    return sizeof(*demo_data);
}


static int32_t appRemoteDemoMessageDoneFn(void *meta, void *msg, uint32_t len)
{
    int32_t ret = 0;
    app_remote_demo_message_t *message = (app_remote_demo_message_t *)meta;

    if(ret == 0) {
        /* Put the empty message back in message pool */
        ret = appQueuePut(&g_rdemo_data.message_pool, message);
        if(ret != 0)
            appLogPrintf("%s: Could not put empty message to pool\n", __func__);
    }

    return ret;
}

static void appRemoteDemoMessageMonitorTaskFn(void *arg0, void *arg1)
{
    void *value;
    app_remote_demo_message_t *msg;
    struct rpmsg_kdrv_device_header *dev_hdr;
    struct rpmsg_kdrv_demodev_s2c_message *resp;    
    app_remote_demo_inst_data_t *inst = (app_remote_demo_inst_data_t *)arg0;
    int32_t ret = 0;

    while(1) {
        ret = 0;
        uint32_t should_send_message = 0;

        if(ret == 0) {
            /* Wait for a signal = a new message has been recv */
            SemaphoreP_pend(inst->message_sem, SemaphoreP_WAIT_FOREVER);
            if(inst->num_incoming_message > 0 && (inst->num_incoming_message % 10) == 0) {
                should_send_message = 1;
                ret = appQueueGet(&g_rdemo_data.message_pool, &value);
                if(ret != 0)
                    appLogPrintf("%s: Could not get an empty message\n", __func__);
            }
        }

        if(ret == 0 && should_send_message == 1) {
            msg = (app_remote_demo_message_t *)value;
            memset(msg, 0, sizeof(*msg) + sizeof(*dev_hdr) + sizeof(*resp));

            msg->request_id = 0; // messages do not have request IDs
            msg->message_size = sizeof(*resp);
            msg->device_id = inst->device_id;
            msg->is_response = FALSE;
            msg->channel = inst->channel;

            dev_hdr = (struct rpmsg_kdrv_device_header *)(&msg->data[0]);
            resp = (struct rpmsg_kdrv_demodev_s2c_message *)(DEVHDR_2_MSG(dev_hdr));

            resp->header.message_type = RPMSG_KDRV_TP_DEMODEV_S2C_MESSAGE;
            snprintf((char *)&resp->data[0], RPMSG_KDRV_TP_DEMODEV_MESSAGE_DATA_LEN, "S2C-message-%u", inst->num_incoming_message);

            ret = appQueuePut(&g_rdemo_data.send_queue, msg);
            if(ret != 0)
                appLogPrintf("%s: Could not queue message for transmission\n", __func__);
        }

        if(ret == 0 && should_send_message == 1)
            SemaphoreP_post(g_rdemo_data.send_sem);

        APP_REMOTE_DEMO_ASSERT_SUCCESS(ret);

    }
}

static void appRemoteDemoSenderTaskFn(void *arg0, void *arg1)
{
    void *value;
    app_remote_demo_message_t *msg;
    int32_t ret = 0;

    while(1) {
        ret = 0;

        if(ret == 0) {
            /* Wait for a signal = a new message to be sent */
            SemaphoreP_pend(g_rdemo_data.send_sem, SemaphoreP_WAIT_FOREVER);
            ret = appQueueGet(&g_rdemo_data.send_queue, &value);
            if(ret != 0)
                appLogPrintf("%s: Could not dequeue message to send\n", __func__);
        }

        if(ret == 0) {
            msg = (app_remote_demo_message_t *)value;
            /* Use remote device framework to send the message */
            ret = appRemoteDeviceSendMessage(msg->channel, &msg->data[0], msg->message_size, msg->is_response, msg->request_id,
                    msg->device_id, appRemoteDemoMessageDoneFn, msg);
            if(ret != 0)
                appLogPrintf("%s: Could not send message\n", __func__);

        }

        APP_REMOTE_DEMO_ASSERT_SUCCESS(ret);

    }
}

static int32_t appRemoteDemoMessageConsumerTaskInit(app_remote_demo_inst_data_t *inst)
{
    SemaphoreP_Params sem_params;
    TaskP_Params tsk_prm;
    int32_t ret = 0;

    if(ret == 0) {
        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_COUNTING;

        inst->message_sem = SemaphoreP_create(0, &sem_params);
        if(inst->message_sem == NULL) {
            appLogPrintf("%s: Could not initialize send semaphore\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {

        TaskP_Params_init(&tsk_prm);
        tsk_prm.priority = 3;
        tsk_prm.stack = &g_message_monitor_tsk_stack[g_message_monitor_tsk_stack_size * inst->serial];
        tsk_prm.stacksize = g_message_monitor_tsk_stack_size;
        tsk_prm.arg0 = inst;

        inst->message_mon_task = TaskP_create(&appRemoteDemoMessageMonitorTaskFn, &tsk_prm);
        if(inst->message_mon_task == NULL) {
            appLogPrintf("%s: Could not initialize sender task\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

static int32_t appRemoteDemoSenderTaskInit()
{
    SemaphoreP_Params sem_params;
    TaskP_Params tsk_prm;
    int32_t ret = 0;

    if(ret == 0) {
        /* The send queue. Task picks up from this queue and sends */
        ret = appQueueInit(&g_rdemo_data.send_queue, FALSE, 0, 0, NULL, 0);
        if(ret != 0)
            appLogPrintf("%s: Could not initialize send queue\n", __func__);
    }

    if(ret == 0) {
        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_COUNTING;

        g_rdemo_data.send_sem = SemaphoreP_create(0, &sem_params);
        if(g_rdemo_data.send_sem == NULL) {
            appLogPrintf("%s: Could not initialize send semaphore\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {

        TaskP_Params_init(&tsk_prm);
        tsk_prm.priority = 3;
        tsk_prm.stack = &g_sender_tsk_stack;
        tsk_prm.stacksize = g_sender_tsk_stack_size;

        g_rdemo_data.sender_task = TaskP_create(&appRemoteDemoSenderTaskFn, &tsk_prm);
        if(g_rdemo_data.sender_task == NULL) {
            appLogPrintf("%s: Could not initialize sender task\n", __func__);
            ret = -1;
        }
    }

    return ret;
}

static int32_t appRemoteDemoValidateInitPrm(app_remote_demo_init_prm_t *prm, char *err_str, uint32_t err_len)
{
    int32_t ret = 0;

    if(ret == 0) {
        if(prm == NULL) {
            snprintf(err_str, err_len, "prm = NULL not allowed");
            ret = -1;
        }
    }

    if(ret == 0) {
        if(prm->rpmsg_buf_size > APP_REMOTE_DEMO_MAX_PACKET_SIZE) {
            snprintf(err_str, err_len, "rpmsg_buf_size > %u not allowed", APP_REMOTE_DEMO_MAX_PACKET_SIZE);
            ret = -1;
        }
    }

    if(ret == 0) {
        if(prm->num_instances > APP_REMOTE_DEMO_MAX_INSTANCES) {
            snprintf(err_str, err_len, "num instances > %u not allowed", APP_REMOTE_DEMO_MAX_INSTANCES);
            ret = -1;
        }
    }

    return ret;
}

static int32_t appRemoteDemoValidateInstPrm(app_remote_demo_inst_prm_t *inst_prm, char *err_str, uint32_t err_len)
{
    int32_t ret = 0;

    if(ret == 0) {
        if(inst_prm == NULL) {
            snprintf(err_str, err_len, "inst_prm = NULL not allowed");
            ret = -1;
        }
    }

    return ret;

}
static int32_t appRemoteDemoInitInst(app_remote_demo_inst_prm_t *inst_prm)
{
    int32_t ret = 0;
    app_remote_demo_inst_data_t *inst_data = &g_rdemo_data.inst_data[g_rdemo_data.inst_count];
    app_remote_device_register_prm_t demo_register_prm;
    char err_str[128];

    if(ret == 0) {
        /* validate instance params */
        ret = appRemoteDemoValidateInstPrm(inst_prm, err_str, 128);
        if(ret != 0)
            appLogPrintf("%s: [inst %u] Could not validate inst params: %s\n", __func__, g_rdemo_data.inst_count, err_str);
    }

    if(ret == 0) {
        /* find a slot for this instance in global data */
        if(g_rdemo_data.inst_count > APP_REMOTE_DEMO_MAX_INSTANCES) {
            appLogPrintf("%s: [inst %u] Could not find slot for instance\n", g_rdemo_data.inst_count);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* copy params into inst data */
        memset(inst_data, 0, sizeof(*inst_data));
        memcpy(&inst_data->inst_prm, inst_prm, sizeof(*inst_prm));
        inst_data->serial = g_rdemo_data.inst_count;

        appRemoteDeviceRegisterParamsInit(&demo_register_prm);

        demo_register_prm.num_host_ids = 1;
        demo_register_prm.host_ids[0] = inst_data->inst_prm.host_id;
        demo_register_prm.device_type = APP_REMOTE_DEVICE_DEVICE_TYPE_DEMO;
        demo_register_prm.cb.fill_priv_data = appRemoteDemoFillPrivData;
        demo_register_prm.cb.connect = appRemoteDemoConnect;
        demo_register_prm.cb.disconnect = appRemoteDemoDisconnect;
        demo_register_prm.cb.request = appRemoteDemoRequest;
        demo_register_prm.cb.message = appRemoteDemoMessage;
        snprintf(demo_register_prm.name, APP_REMOTE_DEVICE_MAX_NAME, "%s", inst_data->inst_prm.name);

        /* Register a virtual display device */
        ret = appRemoteDeviceRegisterDevice(&demo_register_prm, &inst_data->device_id);
        if(ret != 0)
            appLogPrintf("%s: [inst %u] Could not register remote device\n", __func__, g_rdemo_data.inst_count);
    }

    if(ret == 0) {
        ret = appRemoteDemoMessageConsumerTaskInit(inst_data);
        if(ret != 0)
            appLogPrintf("%s: [inst %u] Could not create message monitor task\n", __func__, g_rdemo_data.inst_count);
    }

    if(ret == 0)
        g_rdemo_data.inst_count++;

    return ret;
}

static int32_t appRemoteDemoPoolsInit(app_remote_demo_init_prm_t *prm)
{
    int32_t ret = 0;

    if(ret == 0) {
        /* The pool for transport messages */
        ret = appQueueInit(&g_rdemo_data.message_pool, TRUE, APP_REMOTE_DEMO_MAX_MESSAGES,
                prm->rpmsg_buf_size + sizeof(app_remote_demo_message_t),
                g_message_pool_storage, sizeof(g_message_pool_storage));
        if(ret != 0) {
            appLogPrintf("%s: Could not initialize message pool\n", __func__);
        }
    }

    return ret;
}

int32_t appRemoteDemoInit(app_remote_demo_init_prm_t *prm)
{
    int32_t ret = 0;
    uint32_t cnt;
    SemaphoreP_Params sem_params;
    char err_str[128];

    if(ret == 0) {
        /* validate params. */
        ret = appRemoteDemoValidateInitPrm(prm, err_str, 128);
        if(ret != 0)
            appLogPrintf("%s: Could not validate init params: %s\n", __func__, err_str);
    }

    if(ret == 0) {
        /* copy params into inst data */
        memset(&g_rdemo_data, 0, sizeof(g_rdemo_data));
        memcpy(&g_rdemo_data.prm, prm, sizeof(*prm));

        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_BINARY;

        g_rdemo_data.lock_sem = SemaphoreP_create(1, &sem_params);
        if(g_rdemo_data.lock_sem == NULL) {
            appLogPrintf("%s: Could not initialize lock semaphore (mutex)\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* allocate pools */
        ret = appRemoteDemoPoolsInit(prm);
        if(ret != 0) {
            appLogPrintf("%s: Could not initialize mandatory pools\n", __func__);
        }
    }

    if(ret == 0) {
        /* initialise instances */
        for(cnt = 0; cnt < prm->num_instances; cnt++) {
            ret = appRemoteDemoInitInst(&prm->inst_prm[cnt]);
            if(ret != 0) {
                appLogPrintf("%s: Could not initialize instance %u\n", __func__, cnt);
                break;
            }
        }
    }

    if(ret == 0) {
        /* start message sender task (common for all instances) */
        ret = appRemoteDemoSenderTaskInit();
        if(ret != 0)
            appLogPrintf("Could not start sender task\n");
    }

    return ret;
}
