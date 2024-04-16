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
 *  ======== MutexP_safertos.c ========
 */

#include "SafeRTOS_priv.h"

#include <ti/osal/MutexP.h>
#include <mutex.h>


extern uint32_t  gOsalMutexAllocCnt, gOsalMutexPeak;

/*!
 *  @brief    Mutex structure
 */
typedef struct MutexP_safertos_s {
    bool used;
    uint64_t            mutObj[(safertosapiQUEUE_OVERHEAD_BYTES/sizeof(uint64_t) + (1U))];
    xMutexHandleType    mutHndl;
    uint32_t isRecursiveMutex;
} MutexP_safertos;

/* global pool of statically allocated mutex pools */
static MutexP_safertos gOsalMutexPSafeRtosPool[OSAL_SAFERTOS_CONFIGNUM_MUTEX] __attribute__( ( aligned( 32 ) ) );;


MutexP_Handle MutexP_create(MutexP_Object *mutexObj)
{
    MutexP_Handle ret_handle = NULL;
    MutexP_safertos *handle = (MutexP_safertos *) NULL_PTR;
    MutexP_safertos *mutexPool;
    uint32_t i;
    uintptr_t key;
    uint32_t maxMutex;
    portBaseType xCreateResult;

    if (mutexObj == NULL)
    {
        ret_handle = NULL;
    }
    else
    {

        /* Pick up the internal static memory block */
        mutexPool = (MutexP_safertos *) &gOsalMutexPSafeRtosPool[0];
        maxMutex  = OSAL_SAFERTOS_CONFIGNUM_MUTEX;

        if(gOsalMutexAllocCnt==0U)
        {
            (void)memset((void *)gOsalMutexPSafeRtosPool,0,sizeof(gOsalMutexPSafeRtosPool));
        }

        key = HwiP_disable();

        for (i = 0; i < maxMutex; i++)
        {
            if (mutexPool[i].used == (bool)false)
            {
                mutexPool[i].used = (bool)true;
                /* Update statistics */
                gOsalMutexAllocCnt++;
                if (gOsalMutexAllocCnt > gOsalMutexPeak)
                {
                    gOsalMutexPeak = gOsalMutexAllocCnt;
                }
                break;
            }
        }
        HwiP_restore(key);

        if (i < maxMutex)
        {
            /* Grab the memory */
            handle = (MutexP_safertos *) &mutexPool[i];
        }

      if (handle == NULL_PTR) {
          ret_handle = NULL_PTR;
      }
      else
      {
          handle->isRecursiveMutex = 1;
          xCreateResult = xMutexCreate((portInt8Type *)&(handle->mutObj[0]), &handle->mutHndl);

          if (xCreateResult != pdPASS)
          {
              /* If there was an error reset the mutex object and return NULL. */
              key = HwiP_disable();
              handle->used = (bool)false;
              /* Found the osal task object to delete */
              if (gOsalMutexAllocCnt > 0U)
              {
                  gOsalMutexAllocCnt--;
              }
              HwiP_restore(key);
              ret_handle = NULL_PTR;
          }
          else
          {
              mutexObj->object = (void *)handle;
              mutexObj->key = 0;
              ret_handle = (MutexP_Handle)mutexObj;
          }
      }
    }
    return ret_handle;
}

MutexP_Status MutexP_delete(MutexP_Handle handle)
{
    DebugP_assert(handle != NULL_PTR);

    uintptr_t   key;
    MutexP_Status ret = MutexP_OK;
    MutexP_Object *mutexObj = (MutexP_Object *)handle;
    MutexP_safertos *mutex = (MutexP_safertos *)mutexObj->object;
    
    /*
     * NOTE : Mutex delete is not supported in safertos.
     * We just memset and return success.
     */
    if ((mutex != NULL_PTR) && (mutex->used == (bool)true))
    {
        memset(&mutex->mutObj, 0, sizeof(mutex->mutObj));
        mutex->mutHndl = NULL;
        key = HwiP_disable(  );
        mutex->used = (bool)false;
        /* decrement the count */
        if ( gOsalMutexAllocCnt > 0U )
        {
            gOsalMutexAllocCnt--;
        }
        HwiP_restore( key );
        ret = MutexP_OK;
    }
    else
    {
       ret = MutexP_FAILURE;
    }

    return ret;
}

MutexP_Status MutexP_lock(MutexP_Handle handle,
                          uint32_t timeout)
{
    DebugP_assert(handle != NULL_PTR);

    MutexP_Status ret = MutexP_OK;
    MutexP_Object *mutexObj = (MutexP_Object *)handle;
    MutexP_safertos *mutex = (MutexP_safertos *)mutexObj->object;
    portBaseType xCreateResult;

    /* TODO check why this mutex->isRecursiveMutex needed, may be removed */
    if ((mutex != NULL_PTR) && (mutex->used == (bool)true)&& (mutex->isRecursiveMutex == 1U ))
    {
        if (Osal_isInISRContext() == 0 )
        {
            if (timeout == MutexP_WAIT_FOREVER)
            {
                /* Should not be called from ISR */
                xCreateResult = xMutexTake(mutex->mutHndl, safertosapiMAX_DELAY);
            }
            else
            {
                /* Should not be called from ISR */
                xCreateResult = xMutexTake(mutex->mutHndl, timeout);
            }

            if(xCreateResult == pdPASS)
            {
                ret = MutexP_OK;
            }
            else
            {
                ret = MutexP_TIMEOUT;
            }
        }
        else
        {
            ret = MutexP_FAILURE;
        }
    }
    else
    {
       ret = MutexP_FAILURE;
    }
    return ret;
}

MutexP_Status MutexP_unlock(MutexP_Handle handle)
{
    DebugP_assert(handle != NULL_PTR);

    MutexP_Status ret = MutexP_OK;
    MutexP_Object *mutexObj = (MutexP_Object *)handle;
    MutexP_safertos *mutex = (MutexP_safertos *)mutexObj->object;
    portBaseType xCreateResult;
    /* Note: timeout is not use */

    if ((mutex != NULL_PTR) && (mutex->used == (bool)true) && (mutex->isRecursiveMutex == 1U ))
    {
        if ( Osal_isInISRContext() == 0 )
        {
            /* Should not be called from ISR */
            xCreateResult = xMutexGive(mutex->mutHndl);

            if(xCreateResult == pdPASS)
            {
                ret = MutexP_OK;
            }
            else
            {
                ret = MutexP_TIMEOUT;
            }
        }
        else
        {
            ret = MutexP_FAILURE;
        }
    }
    else
    {
       ret = MutexP_FAILURE;
    }
    return ret;
}


/* Nothing past this point */
