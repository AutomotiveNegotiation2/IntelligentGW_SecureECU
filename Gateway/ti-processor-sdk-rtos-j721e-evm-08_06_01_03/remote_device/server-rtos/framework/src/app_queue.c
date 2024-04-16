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
#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/osal/osal.h>
#include <ti/osal/QueueP.h>
#include <ti/osal/HwiP.h>

#include <server-rtos/include/app_log.h>
#include <server-rtos/include/app_queue.h>

#define QELEM2DATA(x) ((void *)(&(((QueueP_Elem *)x)[1])))
#define DATA2QELEM(x) ((QueueP_Elem *)((uintptr_t)x - sizeof(QueueP_Elem)))


int32_t appQueueInit(app_queue_t *q, uint32_t is_pool, uint32_t num_elems,
        uint32_t elem_sz, void *storage, uint32_t storage_sz)
{
    QueueP_Params queue_params;
    void *data;
    uint32_t cnt;
    int32_t ret = 0;

    if(is_pool == TRUE && storage == NULL) {
        appLogPrintf("%s: Failed to init queue: NULL storage for pool\n", __func__);
        ret = -1;
    }

    if(ret == 0) {
        if(is_pool == TRUE && (num_elems * (elem_sz + APP_QUEUE_ELEM_META_SIZE)) > storage_sz) {
            appLogPrintf("%s: Failed to init queue: storage_sz < required size for pool\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        QueueP_Params_init(&queue_params);
        q->q = QueueP_create(&queue_params);
        if(q->q == NULL) {
            appLogPrintf("%s: Failed to init queue : Queue_create failed\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        /* If it is a pool, then we need to pre-allocate */
        if(is_pool == TRUE) {
            for(cnt = 0; cnt < num_elems; cnt++) {
                data = storage;
                QueueP_put(q->q, (QueueP_Elem *)data);
                storage = (uint8_t *)storage + (elem_sz + APP_QUEUE_ELEM_META_SIZE);
            }
        }
    }

    return ret;
}

int32_t appQueueGet(app_queue_t *q, void **value)
{
    int32_t ret = 0;
    uintptr_t key;
    QueueP_Elem *elem;

    if(q == NULL) {
        appLogPrintf("%s: Failed to get from NULL queue\n", __func__);
        ret = -1;
    }

    if(ret == 0) {
        if(value == NULL) {
            appLogPrintf("%s: Failed to get into NULL value\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        key = HwiP_disable();
        if(QueueP_EMPTY == QueueP_isEmpty(q->q)) {
            HwiP_restore(key);
            appLogPrintf("%s: Failed to get from empty queue\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        elem = QueueP_get(q->q);
        if(elem == NULL) {
            HwiP_restore(key);
            appLogPrintf("%s: Failed to get from unused queue\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        *value = QELEM2DATA(elem);
        HwiP_restore(key);
    }


    return ret;
}

int32_t appQueuePut(app_queue_t *q, void *data)
{
    int32_t ret = 0;
    uintptr_t    key;

    if(q == NULL) {
        appLogPrintf("%s: Failed to put to NULL queue\n", __func__);
        ret = -1;
    }

    if(ret == 0) {
        if(data == NULL) {
            appLogPrintf("%s: Failed to put NULL data to queue\n", __func__);
            ret = -1;
        }
    }

    if(ret == 0) {
        key = HwiP_disable();

        QueueP_put(q->q, DATA2QELEM(data));

        HwiP_restore(key);
    }

    return ret;
}

int32_t appQueueDeinit(app_queue_t *q)
{
    QueueP_delete(&q->q);
    return 0;
}

