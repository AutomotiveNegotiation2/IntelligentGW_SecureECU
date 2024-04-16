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

#ifndef __REMOTE_DEVICE_H__
#define __REMOTE_DEVICE_H__

#include <string.h>

#define APP_REMOTE_DEVICE_CONNECT_NAME_LEN (32)

#define APP_REMOTE_DEVICE_MAX_PARAM_CORES (16)

#define APP_REMOTE_DEVICE_DEVICE_ID_EAGAIN (0xffffffff)

/**
 * \brief Remote device framework initialisation parameters
 */
typedef struct {
    uint32_t remote_endpt; /**< Remote endpoint to connect to */
    uint32_t rpmsg_buf_size; /**< Max Transport packet size */
    SemaphoreP_Handle wait_sem; /**< Semaphore signalled by HLOS RPMSG connect */
    uint32_t num_cores; /**< Number of cores to connect and probe */
    uint32_t cores[APP_REMOTE_DEVICE_MAX_PARAM_CORES]; /**< Array of IPC core IDs */
} app_remote_device_init_prm_t;


typedef struct {
    char device_name[APP_REMOTE_DEVICE_CONNECT_NAME_LEN];
    void *message_cb_priv;
    uint32_t (*message_cb)(void *priv_data, void *msg);
} app_remote_device_device_connect_prm_t;
/**
 * \brief Set Remote Device framework init parameters to default state
 *
 * Recommend to call this API before callnig appRemoteDeviceInit.
 *
 * \param prm [out] Parameters set to default
 */
static void appRemoteDeviceInitParamsInit(app_remote_device_init_prm_t *prm)
{
    memset(prm, 0, sizeof(*prm));
}

static void appRemoteDeviceDeviceConnectParamsInit(app_remote_device_device_connect_prm_t *prm)
{
    memset(prm, 0, sizeof(*prm));
}

/**
 * \brief Initialize remote device framework
 *
 * \param prm [in] Initialization parameters
 *
 * \return 0 on success, else failure
 */
int32_t appRemoteDeviceInit(app_remote_device_init_prm_t *prm);

int32_t appRemoteDeviceConnect(app_remote_device_device_connect_prm_t *prm, uint32_t *device_id);
int32_t appRemoteDeviceDisconnect(uint32_t device_id);
int32_t appRemoteDeviceGetType(uint32_t device_id, uint32_t *device_type);
int32_t appRemoteDeviceGetData(uint32_t device_id, uint8_t *device_data, uint32_t avail_len, uint32_t *act_len);

int32_t appRemoteDeviceSendMessage(uint32_t device_id, void *data, uint32_t len,
        void* free_cb_data, int32_t (*free_cb)(void *priv, void *msg, uint32_t len));
int32_t appRemoteDeviceServiceRequest(uint32_t device_id, void *data, uint32_t len, void *resp, uint32_t avail, uint32_t *resp_size);

#if 0
int32_t appRemoteDeviceLateAnnounce(uint32_t proc_id);
#endif

#endif
