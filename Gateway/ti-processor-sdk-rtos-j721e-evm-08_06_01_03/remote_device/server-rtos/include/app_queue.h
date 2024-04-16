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

#ifndef APP_QUEUE_H_
#define APP_QUEUE_H_

#include <ti/osal/QueueP.h>

/**
 * \defgroup group_vision_apps_utils_queue APIs
 *
 * \brief This section contains APIs for queue module
 *
 * \ingroup group_vision_apps_utils
 *
 * @{
 */

/** \brief Additional Meta data size for each element */
#define APP_QUEUE_ELEM_META_SIZE        (sizeof(QueueP_Elem))

/**
 * \brief App Queue metadata
 */
typedef struct {
    QueueP_Handle q; /**< Internal queue */
} app_queue_t;

/**
 * \brief Initialise a queue
 *
 * \param q [out] Queue metadata to be initialised
 * \param is_pool [in] Queue behavior : TRUE if pool, FALSE if queue
 * \param num_elems [in] Number of elements if pool, 0 if not pool
 * \param elem_sz [in] size of each element if pool, 0 if not pool
 * \param storage [in] valid storage for elements if pool, NULL if not pool
 * \param storage_sz [in] size of storage if pool, 0 if not pool
 *
 * \return 0 on success, else failure
 */
int32_t appQueueInit(app_queue_t *q, uint32_t is_pool, uint32_t num_elems,
        uint32_t elem_sz, void *storage, uint32_t storage_sz);

/**
 * \brief Get an element from queue
 *
 * \param q [in] Queue to be used
 * \param value [out] Location to store element
 *
 * \return 0 on success, else failure
 */
int32_t appQueueGet(app_queue_t *q, void **value);

/**
 * \brief Put an element in queue
 *
 * \param q [in] Queue to be used
 * \param value [in] Value to be stored
 *
 * \return 0 on success, else failure
 */
int32_t appQueuePut(app_queue_t *q, void *data);

/**
 * \brief Destroy a queue
 *
 * \param q [in] Queue to be destroyed
 *
 * \return 0 on success, else failure
 */
int32_t appQueueDeinit(app_queue_t *q);

#endif


