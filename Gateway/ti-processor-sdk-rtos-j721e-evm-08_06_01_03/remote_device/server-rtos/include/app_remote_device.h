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

#ifndef __APP_REMOTE_DEVICE_H__
#define __APP_REMOTE_DEVICE_H__

#include <server-rtos/remote-device.h>

/**
 * \defgroup group_vision_apps_utils_remote_device Remote Device APIs
 *
 * \brief This section contains APIs for Remote Device framework
 *
 * \ingroup group_libs
 *
 * @{
 */

/** \brief Init Device Type */
#define APP_REMOTE_DEVICE_DEVICE_TYPE_INIT          (0)
/** \brief Display Device Type */
#define APP_REMOTE_DEVICE_DEVICE_TYPE_DISPLAY       (1)
/** \brief Demo Device Type */
#define APP_REMOTE_DEVICE_DEVICE_TYPE_DEMO          (2)
/** \brief Demo Device Type */
#define APP_REMOTE_DEVICE_DEVICE_TYPE_ETHSWITCH     (3)

/** \brief Max length of remote device exported name */
#define APP_REMOTE_DEVICE_MAX_NAME                  (128)

/** \brief Max number of host IDs per virtual device */
#define APP_REMOTE_DEVICE_MAX_HOST_IDS              (4)

/**
 * \brief Message channel information
 */
typedef struct {
    uint32_t endpoint; /**< remote endpoint of received message */
    uint32_t procid; /**< remote processor ID */
} app_remote_device_channel_t;

/**
 * \brief Remote device callback functions
 */
typedef struct {
    /**< private data cb: called when remote device is initialised */
    uint32_t (*fill_priv_data)(uint32_t device_id, void *priv_data, uint32_t avail_len);
    /**< connect cb: called when remote driver connects */
    int32_t (*connect)(uint32_t device_id, app_remote_device_channel_t *channel);
    /**< disconnect cb: called when remote driver disconnects */
    int32_t (*disconnect)(uint32_t device_id);
    /**< request cb: called when remote driver sends REQUEST Packets */
    int32_t (*request)(uint32_t device_id, app_remote_device_channel_t *channel,
            uint32_t request_id, void *request, uint32_t request_size);
    /**< message cb: called when remote driver sends MESSAGE Packets */
    int32_t (*message)(uint32_t device_id, app_remote_device_channel_t *channel,
            void *message, uint32_t message_size);
} app_remote_device_cb_t;

/**
 * \brief virtual device register parameters
 */
typedef struct {
    uint32_t device_type; /**< Type of device: display / network etc */
    uint32_t host_ids[APP_REMOTE_DEVICE_MAX_HOST_IDS]; /**< list of IPC host IDs which should know about this device */
    uint32_t num_host_ids; /**< Number of entries in host_ids */
    char name[APP_REMOTE_DEVICE_MAX_NAME]; /**< Exported name of device */
    app_remote_device_cb_t cb; /**< Device callbacks */
} app_remote_device_register_prm_t;

/**
 * \brief Set Remote Device Register parameters to default state
 *
 * Recommend to call this API before callnig appRemoteDeviceRegisterDevice.
 *
 * \param prm [out] Parameters set to default
 */
static void appRemoteDeviceRegisterParamsInit(app_remote_device_register_prm_t *prm)
{
    memset(prm, 0, sizeof(*prm));
}

/**
 * \brief Register a device with remote device framework
 *
 * \param prm [in] Device parameters
 * \param device_id [out] ID of new device
 *
 * \return 0 on success, else failure
 */
int32_t appRemoteDeviceRegisterDevice(app_remote_device_register_prm_t *prm, uint32_t *device_id);

/**
 * \brief Send a message to remote driver
 *
 * \param channel [in] channel (rproc / ept) to send message
 * \param data [in] message data
 * \param len [in] len of message
 * \param is_response [in] whether this is a direct message or a response to a request
 * \param request_id [in] id of request if is_response is TRUE
 * \param device_id [in] id of virtual device
 * \param msg_done_cb [in] callback to free message
 * \param meta_data [in] first argument to msg_done_cb
 *
 * \return 0 on success, else failure
 */
int32_t appRemoteDeviceSendMessage(app_remote_device_channel_t *channel, void *data,
        uint32_t len, uint32_t is_response, uint32_t request_id, uint32_t device_id,
        int32_t (*msg_done_cb)(void *data, void *msg, uint32_t len), void *meta_data);

#endif
