/*
 *
 * Copyright (c) 2020 Texas Instruments Incorporated
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

#ifndef __CPSW_REMOTE_NOTIFY_SERVICE_H__
#define __CPSW_REMOTE_NOTIFY_SERVICE_H__

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/include/per/cpsw.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup ETHSWITCH_REMOTE_NOTIFY_SERVICE_API Ethernet Switch Remote Notify service
 *
 * The Ethernet Remote notify service enables Ethernet fimrware to send notifications to
 * clients. This can be used to notify clients about port link resets, CPTS hardware push events and
 * many more.
 *
 *  @{
 */
/* @} */

/*!
 * \addtogroup ETHSWITCH_REMOTE_NOTIFY_SERVICE_API
 * @{
 */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*! Remote notify service name */
#define CPSW_REMOTE_NOTIFY_SERVICE                      "ti.ethfw.notifyservice"

/*! Remote notify service endpoint Id */
#define CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID             (30U)

/*! Remote notify service max msg size */
#define CPSW_REMOTE_NOTIFY_SERVICE_RPC_MSG_SIZE         (496U + 32U)

/*! Remote notify service max number of rpmsg buffers */
#define CPSW_REMOTE_NOTIFY_SERVICE_NUM_RPMSG_BUFS       (256U)

/*! Remote notify service object size */
#define CPSW_REMOTE_NOTIFY_SERVICE_RPMSG_OBJ_SIZE       (256U)

/*! Remote notify service data size */
#define CPSW_REMOTE_NOTIFY_SERVICE_DATA_SIZE            (CPSW_REMOTE_NOTIFY_SERVICE_RPC_MSG_SIZE * \
                                                         CPSW_REMOTE_NOTIFY_SERVICE_NUM_RPMSG_BUFS + \
                                                         CPSW_REMOTE_NOTIFY_SERVICE_RPMSG_OBJ_SIZE)

/*! Remote notify service command count */
#define CPSW_REMOTE_NOTIFY_SERVICE_CMD_COUNT            (CPSW_REMOTE_NOTIFY_SERVICE_CMD_LAST + 1)

/*! Remote notify service task name */
#define CPSW_REMOTE_NOTIFY_SERVICE_TASK_NAME            ("NOTIFY_SERVICE_TASK")

/*! Remote notify service task priority */
#define CPSW_REMOTE_NOTIFY_SERVICE_TASK_PRIORITY        (2U)

/*! Remote notify service task stack size */
#define CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKSIZE       (16U * 1024U)

/*! Remote notify service task stack alignment */
#define CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKALIGN      CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKSIZE

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*!
 * \brief Remote notify service commands
 */
typedef enum
{
    /*! Remote notify service hardware push command  */
    CPSW_REMOTE_NOTIFY_SERVICE_CMD_HWPUSH          = 0U,

    /*! Remote notify service last command  */
    CPSW_REMOTE_NOTIFY_SERVICE_CMD_LAST            = CPSW_REMOTE_NOTIFY_SERVICE_CMD_HWPUSH,
} CpswRemoteNotifyService_Cmd;

/*!
 * \brief Common message header for all ethernet switch remote notify service commands
 */
typedef struct CpswRemoteNotifyService_MessageHeader_s
{
    /*! Message Type enum: CpswRemoteNotifyService_Cmd */
    uint32_t messageId;

    /*! Message length */
    uint32_t messageLen;
} CpswRemoteNotifyService_MessageHeader;

/*!
 * \brief CPSW_REMOTE_NOTIFY_SERVICE_CMD_HWPUSH cmd notify information
 */
typedef struct CpswRemoteNotifyService_HwPushMsg_s
{
    /*! common message header */
    CpswRemoteNotifyService_MessageHeader header;

    /*! CPSW type */
    Enet_Type enetType;

    /*! CPTS hardware push number */
    uint32_t hwPushNum;

    /*! CPTS hardware push event timestamp  */
    uint64_t timeStamp;
} CpswRemoteNotifyService_HwPushMsg;

/*!
 * \brief CPSW Remote hardware push notify handler
 *
 * \param hwPushNum Enum value of hardware psuh that triggered the event
 * \param syncTime  Timestamp value when hardware push event was triggered
 * \param cbArg     Callback argument
 *
 */
typedef void (*CpswRemoteNotifyService_hwPushNotifyCbFxn)(CpswCpts_HwPush hwPushNum,
                                                          uint64_t syncTime,
                                                          void *cbArg);

/*!
 * \brief CPSW Remote notify service callback handlers
 */
typedef struct CpswRemoteNotifyService_CallbackHandlers_s
{
    /*! Hardware push notify handler */
    CpswRemoteNotifyService_hwPushNotifyCbFxn hwPushCb;

    /*! Hardware push notify arguments */
    void *hwPushCbArg;
} CpswRemoteNotifyService_CallbackHandlers;


/* @} */
#endif

