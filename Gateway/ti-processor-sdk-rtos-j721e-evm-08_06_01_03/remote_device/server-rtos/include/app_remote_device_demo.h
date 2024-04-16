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

#ifndef __APP_REMOTE_DEMO_H__
#define __APP_REMOTE_DEMO_H__

/**
 * \defgroup group_vision_apps_utils_remote_disp Remote Demo APIs
 *
 * \brief This section contains APIs for Remote Demo framework
 *
 * \ingroup group_libs
 *
 * @{
 */

/** \brief Max length of remote demo exported name */
#define APP_REMOTE_DEMO_MAX_NAME_LEN         (128)

/** \brief Max number of remote demo instances */
#define APP_REMOTE_DEMO_MAX_INSTANCES        (4)

/** \brief Max length of remote demo data */
#define APP_REMOTE_DEMO_MAX_DATA_LEN        (128)

/**
 * \brief Remote demo instance initialization parameters (forward declaration)
 */
struct __app_remote_demo_inst_prm_t;
typedef struct __app_remote_demo_inst_prm_t app_remote_demo_inst_prm_t;

/**
 * \brief Remote demo initialization parameters (forward declaration)
 */
struct __app_remote_demo_init_prm_t;
typedef struct __app_remote_demo_init_prm_t app_remote_demo_init_prm_t;

/**
 * \brief Remote demo instance initialization parameters
 */
struct __app_remote_demo_inst_prm_t {
    uint32_t host_id; /**< Host Id that should connect to this device */
    uint8_t name[APP_REMOTE_DEMO_MAX_NAME_LEN]; /**< Exported name */
    uint8_t data[APP_REMOTE_DEMO_MAX_DATA_LEN]; /**< Exported device data */
};

/**
 * \brief Remote demo device initialization parameters
 */
struct __app_remote_demo_init_prm_t {
    uint32_t num_instances; /**< Number of instances */
    app_remote_demo_inst_prm_t inst_prm[APP_REMOTE_DEMO_MAX_INSTANCES]; /**< List of instances */
    uint32_t rpmsg_buf_size; /**< Max transport packet size */
};


/**
 * \brief Set Remote Demo device init parameters to default state
 *
 * Recommend to call this API before callnig appRemoteDemoInit.
 *
 * \param prm [out] Parameters set to default
 */
static void appRemoteDemoInitPrmSetDefault(app_remote_demo_init_prm_t *prm)
{
    memset(prm, 0, sizeof(*prm));

    prm->rpmsg_buf_size = 256;
    prm->num_instances = 0;
}

/**
 * \brief Initialize remote demo module
 *
 * \param prm [in] Initialization parameters
 *
 * \return 0 on success, else failure
 */
int32_t appRemoteDemoInit(app_remote_demo_init_prm_t *prm);

#endif

