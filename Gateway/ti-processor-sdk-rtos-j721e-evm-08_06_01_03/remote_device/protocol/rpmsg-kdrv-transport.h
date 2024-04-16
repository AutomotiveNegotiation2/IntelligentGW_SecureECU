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


#ifndef __RPMSG_KDRV_TRANSPORT_H__
#define __RPMSG_KDRV_TRANSPORT_H__

#include "rpmsg-kdrv-transport-common.h"

enum rpmsg_kdrv_init_message_type {
	RPMSG_KDRV_TP_INIT_DEV_INFO_REQUEST,
	RPMSG_KDRV_TP_INIT_DEV_INFO_RESPONSE,
	RPMSG_KDRV_TP_INIT_CONNECT_MESSAGE,
	RPMSG_KDRV_TP_INIT_DISCONNECT_MESSAGE,
	RPMSG_KDRV_TP_INIT_MAX,
};

/*
 * message header for init device
 */
struct rpmsg_kdrv_init_message_header {
	/* enum: rpmsg_kdrv_init_message_type */
	u8 message_type;
} __attribute__((packed));

/*
 * init device request to provide list of devices
 */
struct rpmsg_kdrv_init_dev_info_request {
	/* message header */
	struct rpmsg_kdrv_init_message_header header;
} __attribute__((packed));

struct rpmsg_kdrv_init_device_info {
	/* device id */
	u8 device_id;
	/* device type (display, capture etc) */
	u8 device_type;
	/* name of device */
	u8 device_name[RPMSG_KDRV_TP_DEVICE_NAME_LEN];
	/* device specific info length */
	u16 device_data_len;
	/* per device-type info offset */
	u16 device_data_offset;
} __attribute__((packed));

/*
 * init device response with list of devices
 */
struct rpmsg_kdrv_init_dev_info_response {
	/* message header */
	struct rpmsg_kdrv_init_message_header header;
	/*number of exported devices */
	u8 num_devices;
	/* list of exported devices */
	struct rpmsg_kdrv_init_device_info devices[RPMSG_KDRV_TP_MAX_DEVICES];
	/* device specific data */
	u8 device_data[0];
} __attribute__((packed));

/*
 * init device per-device connect message
 */
struct rpmsg_kdrv_init_connect_message {
	/* message header */
	struct rpmsg_kdrv_init_message_header header;
	/* device ID to connect */
	u8 device_id;
} __attribute__((packed));

/*
 * init device per-device disconnect message
 */
struct rpmsg_kdrv_init_disconnect_message {
	/* message header */
	struct rpmsg_kdrv_init_message_header header;
	/* device ID to disconnect */
	u8 device_id;
} __attribute__((packed));

#endif
