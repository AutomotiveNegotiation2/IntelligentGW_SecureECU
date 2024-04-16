/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== MailboxP_freertos.c ========
 */

#include <ti/osal/MailboxP.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/osal/osal.h>
#include <ti/osal/soc/osal_soc.h>

#include <FreeRTOS.h>
#include "queue.h"

uint32_t  gOsalMailboxAllocCnt = 0U, gOsalMailboxPeak = 0U;

/*!
 *  @brief    MailboxP_freertos structure
 */
typedef struct MailboxP_freertos_s
{
    bool                used;
    StaticQueue_t       mailboxObj;
    QueueHandle_t       mailboxHndl;
} MailboxP_freertos;

/* global pool of statically allocated mailbox pools */
static MailboxP_freertos gOsalMailboxPFreeRtosPool[OSAL_FREERTOS_CONFIGNUM_MAILBOX];

void MailboxP_Params_init(MailboxP_Params *params)
{
    if (params != NULL_PTR)
    {
        params->pErrBlk =  NULL_PTR;
        params->name    =  NULL_PTR;
        params->size    =  0U;
        params->count   =  0U;
        params->bufsize =  0U;
        params->buf     =  NULL_PTR;
    }
    return;
}

MailboxP_Handle MailboxP_create(const MailboxP_Params *params)
{
    MailboxP_Handle     ret_handle; 
    MailboxP_freertos   *handle = (MailboxP_freertos *) NULL_PTR;
    MailboxP_freertos   *mailboxPool;
    uint32_t            i;
    uintptr_t           key;
    uint32_t            maxMailbox;

    DebugP_assert((params != NULL_PTR));
    DebugP_assert((params->buf != NULL_PTR));
    DebugP_assert((params->bufsize >= (params->size * params->count)));

    /* Pick up the internal static memory block */
    mailboxPool       = (MailboxP_freertos *) &gOsalMailboxPFreeRtosPool[0];
    maxMailbox        = OSAL_FREERTOS_CONFIGNUM_MAILBOX;
    
    if(gOsalMailboxAllocCnt==0U) 
    {
        (void)memset( (void *)gOsalMailboxPFreeRtosPool,0,sizeof(gOsalMailboxPFreeRtosPool));
    }

    key = HwiP_disable();

     for (i = 0; i < maxMailbox; i++)
     {
         if (mailboxPool[i].used == (bool)false)
         {
             mailboxPool[i].used = (bool)true;
             /* Update statistics */
             gOsalMailboxAllocCnt++;
             if (gOsalMailboxAllocCnt > gOsalMailboxPeak)
             {
                 gOsalMailboxPeak = gOsalMailboxAllocCnt;
             }
             break;
         }
     }
    HwiP_restore(key);

    if (i < maxMailbox)
    {
        /* Grab the memory */
        handle = (MailboxP_freertos *) &mailboxPool[i];
    }

    if (handle == NULL_PTR) {
        ret_handle = NULL_PTR;
    }
    else
    {
        handle->mailboxHndl = xQueueCreateStatic((UBaseType_t)params->count, 
                                        (UBaseType_t)params->size, 
                                        (uint8_t*)params->buf,
                                        &handle->mailboxObj);
        if(handle->mailboxHndl == NULL)
        {
            /* If there was an error reset the mailbox object and return NULL. */
            key = HwiP_disable();
            handle->used = (bool)false;
            /* Found the osal mailbox object to delete */
            if (gOsalMailboxAllocCnt > 0U)
            {
                gOsalMailboxAllocCnt--;
            }
            HwiP_restore(key);
            ret_handle = NULL_PTR;
        }
        else
        {
            ret_handle = ((MailboxP_Handle)handle);
        }
    }

    return ret_handle;
}

MailboxP_Status MailboxP_delete(MailboxP_Handle handle)
{
    DebugP_assert((handle != NULL_PTR));

    uintptr_t   key;
    MailboxP_Status ret_val = MailboxP_OK;
    MailboxP_freertos *mailbox = (MailboxP_freertos *)handle;

    if((mailbox != NULL_PTR) && (mailbox->used==(bool)true))
    {
        vQueueDelete(mailbox->mailboxHndl);

        key = HwiP_disable();
        mailbox->used = (bool)false;
        /* Found the osal mailbox object to delete */
        if (gOsalMailboxAllocCnt > 0U)
        {
            gOsalMailboxAllocCnt--;
        }
        HwiP_restore(key);
        ret_val = MailboxP_OK;
    }
    else
    {
       ret_val = MailboxP_FAILURE;
    }  

    return ret_val;
}

MailboxP_Status MailboxP_post(MailboxP_Handle handle,
                              void * msg,
                              uint32_t timeout)
{
    DebugP_assert((handle != NULL_PTR));
    
    BaseType_t qStatus;
    MailboxP_Status ret_val = MailboxP_OK;
    MailboxP_freertos *mailbox = (MailboxP_freertos *)handle;

    if( xPortInIsrContext() == 1 )
    {
        BaseType_t xHigherPriorityTaskWoken = 0;

        /* timeout is ignored when in ISR mode */
        qStatus = xQueueSendToBackFromISR(mailbox->mailboxHndl, msg, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR((uint32_t)xHigherPriorityTaskWoken);
    }
    else
    {
        if (timeout == MailboxP_WAIT_FOREVER)
        {
            qStatus = xQueueSendToBack(mailbox->mailboxHndl, msg, portMAX_DELAY);
        }
        else
        {
            qStatus = xQueueSendToBack(mailbox->mailboxHndl, msg, timeout);
        }
    }

    if (qStatus == pdPASS)
    {
        ret_val = MailboxP_OK;
    }
    else
    {
        ret_val = MailboxP_TIMEOUT;
    }

    return ret_val;
}

MailboxP_Status MailboxP_pend(MailboxP_Handle handle,
                              void * msg,
                              uint32_t timeout)
{
    DebugP_assert((handle != NULL_PTR));
    
    BaseType_t qStatus;
    MailboxP_Status ret_val = MailboxP_OK;
    MailboxP_freertos *mailbox = (MailboxP_freertos *)handle;

    if( xPortInIsrContext() == 1 )
    {
        BaseType_t xHigherPriorityTaskWoken = 0;

        /* timeout is ignored when in ISR mode */
        qStatus = xQueueReceiveFromISR(mailbox->mailboxHndl, msg, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR((uint32_t)xHigherPriorityTaskWoken);
    }
    else
    {
        if (timeout == MailboxP_WAIT_FOREVER)
        {
            qStatus = xQueueReceive(mailbox->mailboxHndl, msg, portMAX_DELAY);
        }
        else
        {
            qStatus = xQueueReceive(mailbox->mailboxHndl, msg, timeout);
        }
    }

    if (qStatus == pdPASS)
    {
        ret_val = MailboxP_OK;
    }
    else
    {
        ret_val = MailboxP_TIMEOUT;
    }

    return ret_val;
}

int32_t MailboxP_getNumPendingMsgs(MailboxP_Handle handle)
{
    DebugP_assert((handle != NULL_PTR));

    UBaseType_t numMsg;
    MailboxP_freertos *mailbox = (MailboxP_freertos *)handle;

    if( xPortInIsrContext() == 1 )
    {
        numMsg = uxQueueMessagesWaitingFromISR(mailbox->mailboxHndl);
    }
    else
    {
        numMsg = uxQueueMessagesWaiting(mailbox->mailboxHndl);
    }

    return ((int32_t)numMsg);
}

/* Nothing past this point */
