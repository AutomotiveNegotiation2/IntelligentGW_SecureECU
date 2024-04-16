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


#ifndef __RPMSG_KDRV_TRANSPORT_COMMON_H__
#define __RPMSG_KDRV_TRANSPORT_COMMON_H__

#include "rpmsg-kdrv-transport-types.h"

/*
 * Device types supported by RPMSG-KDRV framework
 * Currently supported device types: display
 * Planned future support for capture and i2c devices
 */
#define RPMSG_KDRV_TP_DEVICE_TYPE_INIT		(0x0)
#define RPMSG_KDRV_TP_DEVICE_TYPE_DISPLAY	(0x1)
#define RPMSG_KDRV_TP_DEVICE_TYPE_DEMO		(0x2)
#define RPMSG_KDRV_TP_DEVICE_TYPE_ETHSWITCH	(0x3)
/* More device types here*/
#define RPMSG_KDRV_TP_DEVICE_TYPE_MAX		(0x4)

/*
 * Maximum number of proxy devices per remotecore
 */
#define RPMSG_KDRV_TP_MAX_DEVICES		(4)

/*
 * Maximum length of proxy device name
 */
#define RPMSG_KDRV_TP_DEVICE_NAME_LEN		(32)

/*
 * Statically assigned device ID for init device
 * Remote device framework dynamically assigns device
 * IDs for other devices. All dynamically assigned IDs
 * are greater than RPMSG_KDRV_TP_DEVICE_ID_INIT
 */
#define RPMSG_KDRV_TP_DEVICE_ID_INIT		(0)

/*
 * Packet IDs are assigned dynamically (for REQUEST packets)
 * starting from RPMSG_KDRV_TP_PACKET_ID_FIRST
 * For MESSAGE packets, framework can use RPMSG_KDRV_TP_PACKET_ID_NONE
 */
#define RPMSG_KDRV_TP_PACKET_ID_NONE		(0x10)
#define RPMSG_KDRV_TP_PACKET_ID_FIRST		(RPMSG_KDRV_TP_PACKET_ID_NONE + 1)

enum rpmsg_kdrv_packet_source {
	RPMSG_KDRV_TP_PACKET_SOURCE_SERVER,
	RPMSG_KDRV_TP_PACKET_SOURCE_CLIENT,
	RPMSG_KDRV_TP_PACKET_SOURCE_MAX,
};

enum rpmsg_kdrv_packet_type {
	RPMSG_KDRV_TP_PACKET_TYPE_REQUEST,
	RPMSG_KDRV_TP_PACKET_TYPE_RESPONSE,
	RPMSG_KDRV_TP_PACKET_TYPE_MESSAGE,
	RPMSG_KDRV_TP_PACKET_TYPE_MAX,
};

/*RPMSG_KDRV message :
 * => device_header
 * => message_header : defined by each device type
 * => request / response / message payload
 */
struct rpmsg_kdrv_device_header {
	/* ID of device sending the packet */
	u8 device_id;
	/* enum: rpmsg_kdrv_packet_type */
	u8 packet_type;
	/* enum: rpmsg_kdrv_packet_source */
	u8 packet_source;
	/* dynamically assigned packet ID for response matching */
	u32 packet_id;
	/* size of packet */
	u32 packet_size;
} __attribute__((packed));

#endif

