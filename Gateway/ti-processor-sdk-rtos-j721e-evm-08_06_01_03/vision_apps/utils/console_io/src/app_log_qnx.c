/*
 *
 * Copyright (c) 2019 Texas Instruments Incorporated
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
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <ti/drv/sciclient/sciclient.h>
#if _POSIX_C_SOURCE >= 199309L
#include <time.h>   /* for nanosleep */
int nanosleep(const struct timespec *req, struct timespec *rem);
#else
#include <unistd.h> /* for usleep */
extern int usleep (useconds_t __useconds);
#endif
#include "app_log_priv.h"
#include <inttypes.h>

#undef APP_LOG_DEBUG

static void *GTC_BASE_ADDR = NULL;
static uint64_t mhzFreq = 0;

#define GET_GTC_VALUE64 (*(volatile uint64_t*)(GTC_BASE_ADDR + 8))

#define PRI_MAX  sched_get_priority_max(SCHED_FIFO)
#define PRI_MIN  sched_get_priority_min(SCHED_FIFO)

#define ONE_BILLION ((uint64_t) 1000000000U)

typedef struct
{
    pthread_mutex_t lock;
    pthread_t task;
} app_log_qnx_obj_t;

app_log_qnx_obj_t g_app_log_qnx_obj;

uintptr_t appLogWrLock(app_log_wr_obj_t *obj)
{
    pthread_mutex_lock(&g_app_log_qnx_obj.lock);
    return 0;
}

void appLogWrUnLock(app_log_wr_obj_t *obj, uintptr_t key)
{
    pthread_mutex_unlock(&g_app_log_qnx_obj.lock);
}

int32_t appLogGlobalTimeInit()
{
    int32_t status = 0;
    uint64_t clkFreq;

    GTC_BASE_ADDR = appMemMap((void*)GTC_TIMER_MAPPED_BASE, GTC_TIMER_MAPPED_SIZE);
    if(GTC_BASE_ADDR==NULL)
    {
        printf("APP_LOG: ERROR: Unable to mmap gtc (%p of %d bytes) !!!\n", (void*)GTC_TIMER_MAPPED_BASE, GTC_TIMER_MAPPED_SIZE );
        status = -1;
        return status;
    }

    if (0 == status)
    {
        status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_GTC0,
                                           TISCI_DEV_GTC0_GTC_CLK,
                                           &clkFreq,
                                           SCICLIENT_SERVICE_WAIT_FOREVER);

    }

    if (0 == status)
    {
        mhzFreq = clkFreq / APP_LOG_HZ_TO_MHZ;
    }

    return status;
}

int32_t appLogGlobalTimeDeInit()
{
    int32_t status = 0;

    if (NULL != GTC_BASE_ADDR)
    {
        status = appMemUnMap((void*)GTC_BASE_ADDR, GTC_TIMER_MAPPED_SIZE);
    }

    return status;
}

void appLogPrintGtcFreq()
{
    appLogPrintf("GTC Frequency = %" PRIu64 " MHz\n", mhzFreq);
}

uint64_t appLogGetGlobalTimeInUsec()
{
    uint64_t cur_ts = 0; /* Returning ts in usecs */

    if ((NULL != GTC_BASE_ADDR) &&
        (0 != mhzFreq) )
    {
        cur_ts = GET_GTC_VALUE64 / mhzFreq;
    }

    return cur_ts;
}

uint64_t appLogGetLocalTimeInUsec()
{
    uint64_t timeInUsecs = 0U;
    struct timespec currentTime;
    static uint64_t g_start_time = 0U;

    if( clock_gettime( CLOCK_MONOTONIC, &currentTime) == -1 ) {
        perror( "clock gettime" );
        return EXIT_FAILURE;
    }

    timeInUsecs = ((((uint64_t) currentTime.tv_sec * ONE_BILLION) + (uint64_t) currentTime.tv_nsec) / 1000);
    if(g_start_time==0)
    {
        g_start_time = timeInUsecs;
    }
    return (timeInUsecs-g_start_time);
}

uint64_t appLogGetTimeInUsec()
{
    #ifdef APP_LOG_USE_GLOBAL_TIME
    return appLogGetGlobalTimeInUsec();
    #else
    return appLogGetLocalTimeInUsec();
    #endif
}

void appLogWaitMsecs(uint32_t time_in_msecs)
{
#if _POSIX_C_SOURCE >= 199309L
    struct timespec delay_time, remain_time;
    int ret;

    delay_time.tv_sec  = time_in_msecs/1000;
    delay_time.tv_nsec = (time_in_msecs%1000)*1000000;

    do
    {
        ret = nanosleep(&delay_time, &remain_time);
        if(ret < 0 && remain_time.tv_sec > 0 && remain_time.tv_nsec > 0)
        {
            /* restart for remaining time */
            delay_time = remain_time;
        }
        else
        {
            break;
        }
    } while(1);
#else
    usleep(time_in_msecs * 1000);
#endif
}

int32_t appLogWrCreateLock(app_log_wr_obj_t *obj)
{
    return 0;
}

int32_t appLogRdCreateTask(app_log_rd_obj_t *obj, app_log_init_prm_t *prm)
{
    pthread_mutexattr_t mutex_attr;
    pthread_attr_t thread_attr;
    int32_t status = 0;

    status |= pthread_mutexattr_init(&mutex_attr);
    if(status==0)
    {
        status |= pthread_mutex_init(&g_app_log_qnx_obj.lock, &mutex_attr);
        pthread_mutexattr_destroy(&mutex_attr);
    }
    if(status!=0)
    {
        printf("APP_LOG: ERROR: Unable to create mutex !!!\n");
    }
    if(status==0)
    {
        status |= pthread_attr_init(&thread_attr);
        if(status!=0)
        {
            printf("APP_LOG: ERROR: Unable to set thread attr !!!\n");
        }
        if(status==0)
        {
            status |= pthread_create(&g_app_log_qnx_obj.task, &thread_attr, (void*)appLogRdRun, obj);
        }
        pthread_attr_destroy(&thread_attr);
    }
    if(status!=0)
    {
        printf("APP_LOG: ERROR: Unable to create thread !!!\n");
    }

    return status;
}

void *appMemMap(void *phys_ptr, uint32_t size)
{
    uint32_t  pageSize = getpagesize();
    uintptr_t taddr;
    uint32_t  tsize;
    void     *virt_ptr = NULL;
#ifdef MEM_DEV_OPEN
    int32_t   status = 0;
    static int dev_mem_fd = -1;

    if(dev_mem_fd == -1)
    {
        dev_mem_fd = open("/dev/mem",O_RDWR|O_SYNC);
        if(dev_mem_fd  < 0)
        {
            printf("APP_LOG: ERROR: Unable to open /dev/mem !!!\n");
            status = -1;
        }
    }
    if(status==0 && dev_mem_fd >= 0)
    {
        #ifdef APP_LOG_DEBUG
        printf("APP_LOG: Mapping %p ...\n", phys_ptr);
        #endif
        /* Mapping this physical address to qnx user space */
        taddr = (uintptr_t)phys_ptr;
        tsize = size;

        /* Align the physical address to page boundary */
        tsize = appAlign(tsize + (taddr % pageSize), pageSize);
        taddr = appFloor(taddr, pageSize);

        virt_ptr  = mmap64(0, tsize,
                        (PROT_READ | PROT_WRITE | PROT_NOCACHE),
                        (MAP_SHARED), dev_mem_fd, taddr);
        if(virt_ptr==MAP_FAILED)
        {
            virt_ptr = NULL;
        }
        else
        {
            virt_ptr = (void*)((uintptr_t)virt_ptr + ((uintptr_t)phys_ptr % pageSize));
        }
        #ifdef APP_LOG_DEBUG
        printf("APP_LOG: Mapped %p -> %p of size %d bytes \n", phys_ptr, virt_ptr, size);
        #endif
    }
    if(virt_ptr==NULL)
    {
        printf("APP_LOG: ERROR: Unable to map memory @ %p of size %d bytes !!!\n", phys_ptr, size);
    }
#else
    #ifdef APP_LOG_DEBUG
    printf("APP_LOG: Mapping %p ...\n", phys_ptr);
    #endif

    /* Mapping this physical address to qnx user space */
    taddr = (uintptr_t)phys_ptr;
    tsize = size;

    /* Align the physical address to page boundary */
    tsize = appAlign(tsize + (taddr % pageSize), pageSize);
    taddr = appFloor(taddr, pageSize);


    virt_ptr  = mmap_device_memory(0, tsize, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, taddr);
    if(virt_ptr==MAP_FAILED)
    {
        virt_ptr = NULL;
    }
    else
    {
        virt_ptr = (void*)((uintptr_t)virt_ptr + ((uintptr_t)phys_ptr % pageSize));
    }
    #ifdef APP_LOG_DEBUG
    printf("APP_LOG: Mapped %p -> %p of size %d bytes \n", phys_ptr, virt_ptr, size);
    #endif
    if(virt_ptr==NULL)
    {
        printf("APP_LOG: ERROR: Unable to map memory @ %p of size %d bytes !!!\n", phys_ptr, size);
    }
#endif
    return virt_ptr;
}

int32_t appMemUnMap(void *virt_ptr, uint32_t size)
{
    int32_t status=0;
    uint32_t pageSize = getpagesize();
    uintptr_t taddr;
    uint32_t  tsize;

    #ifdef APP_LOG_DEBUG
    printf("APP_LOG: UnMapped memory at virtual address @ 0x%p of size %d bytes \n", virt_ptr, size);
    #endif

    taddr = (uint64_t)virt_ptr;
    tsize = size;

    tsize = appAlign(tsize + (taddr % pageSize), pageSize);
    taddr = appFloor(taddr, pageSize);

#ifdef MEM_DEV_OPEN
    munmap((void *)taddr, tsize);
#else
    munmap_device_memory((void *)taddr, tsize);
#endif

    return status;
}
