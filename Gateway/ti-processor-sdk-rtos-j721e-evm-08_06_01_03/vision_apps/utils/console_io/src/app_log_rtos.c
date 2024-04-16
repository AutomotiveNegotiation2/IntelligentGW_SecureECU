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

#include "app_log_priv.h"
#include <utils/perf_stats/include/app_perf_stats.h>
#include <ti/osal/HwiP.h>
#include <ti/osal/TimerP.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/SemaphoreP.h>
#include <string.h>
#include <ti/drv/sciclient/sciclient.h>
#include "app_global_timer_priv.h"

static uintptr_t GTC_BASE_ADDR = 0;
static uint64_t mhzFreq = 0;

#define GET_GTC_VALUE64 (*(volatile uint64_t*)(GTC_BASE_ADDR + 0x8U))

int32_t appLogWrCreateLock(app_log_wr_obj_t *obj)
{
    int32_t status = 0;
    SemaphoreP_Params semParams;

    SemaphoreP_Params_init(&semParams);
    semParams.mode = SemaphoreP_Mode_BINARY;
    obj->lock = SemaphoreP_create(1U, &semParams);
    if(obj->lock==NULL)
    {
        status = -1;
    }
    return status;
}

uintptr_t appLogWrLock(app_log_wr_obj_t *obj)
{
    if(obj->lock)
    {
        SemaphoreP_pend(obj->lock, SemaphoreP_WAIT_FOREVER);
    }
    return (uintptr_t)0;
}

void appLogWrUnLock(app_log_wr_obj_t *obj, uintptr_t key)
{
    if(obj->lock)
    {
        SemaphoreP_post(obj->lock);
    }
}

uint64_t appLogGetGlobalTimeInUsec()
{
    uint64_t cur_ts = 0; /* Returning ts in usecs */

    if (((uintptr_t)NULL != GTC_BASE_ADDR) &&
        (0 != mhzFreq) )
    {
        cur_ts = GET_GTC_VALUE64 / mhzFreq;
    }

    return cur_ts;
}

uint64_t appLogGetLocalTimeInUsec()
{
    return TimerP_getTimeInUsecs(); /* in units of usecs */
}

uint64_t appLogGetTimeInUsec()
{
    #ifdef APP_LOG_USE_GLOBAL_TIME
    return appLogGetGlobalTimeInUsec();
    #else
    return appLogGetLocalTimeInUsec();
    #endif
}

int32_t appLogGlobalTimeInit()
{
    int32_t status = 0;
    uint64_t clkFreq;

    #ifdef C66
    GTC_BASE_ADDR = (uintptr_t)GTC_TIMER_MAPPED_BASE_C66;
    #else
    GTC_BASE_ADDR = (uintptr_t)GTC_TIMER_MAPPED_BASE;
    #endif

    #ifdef C66
    CSL_RatTranslationCfgInfo translationCfg;
    CSL_ratRegs *pGTCRatRegs = (CSL_ratRegs *)(CSL_C66_COREPAC_C66_RATCFG_BASE);

    translationCfg.sizeInBytes = GTC_TIMER_MAPPED_SIZE;
    translationCfg.baseAddress = GTC_BASE_ADDR;
    translationCfg.translatedAddress = CSL_GTC0_GTC_CFG1_BASE;

    CSL_ratConfigRegionTranslation(pGTCRatRegs, 1, &translationCfg);
    #endif

    /* needs to be enabled only once, do it from R5F */
    #if defined(R5F)
    /* Configure GTC Timer - running at 200MHz as per config and default mux mode */
    /* 200 MHz depends on 'MCU_PLL1' and is selected through 'GTCCLK_SEL' mux */
    /* Enable GTC */
    HW_WR_REG32((volatile uint32_t*)GTC_BASE_ADDR + 0x0U, 0x1);
    #endif

    #if defined (SOC_AM62A)
    status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_WKUP_GTC0,
                                       TISCI_DEV_WKUP_GTC0_GTC_CLK,
                                       &clkFreq,
                                       SCICLIENT_SERVICE_WAIT_FOREVER);
    #else
    status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_GTC0,
                                       TISCI_DEV_GTC0_GTC_CLK,
                                       &clkFreq,
                                       SCICLIENT_SERVICE_WAIT_FOREVER);
    #endif

    if (0 == status)
    {
        mhzFreq = clkFreq / APP_LOG_HZ_TO_MHZ;
    }

    return status;
}

int32_t appLogGlobalTimeDeInit()
{
    return 0;
}

void appLogWaitMsecs(uint32_t time_in_msecs)
{
    TaskP_sleepInMsecs(time_in_msecs);
}

int32_t   appLogRdCreateTask(app_log_rd_obj_t *obj, app_log_init_prm_t *prm)
{
    TaskP_Params rtos_task_prms;
    int32_t status = 0;

    TaskP_Params_init(&rtos_task_prms);

    rtos_task_prms.stacksize = obj->task_stack_size;
    rtos_task_prms.stack = obj->task_stack;
    rtos_task_prms.priority = prm->log_rd_task_pri;
    rtos_task_prms.arg0 = (void*)(obj);
    rtos_task_prms.arg1 = NULL;
    rtos_task_prms.name = (const char*)&obj->task_name[0];

    strncpy(obj->task_name, "LOG_RD", APP_LOG_MAX_TASK_NAME);
    obj->task_name[APP_LOG_MAX_TASK_NAME-1] = 0;

    obj->task_handle = (void*)TaskP_create(
                            &appLogRdRun,
                            &rtos_task_prms);
    if(obj->task_handle==NULL)
    {
        status = -1;
    }
    else
    {
        appPerfStatsRegisterTask(obj->task_handle, obj->task_name);
    }
    return status;
}

void *appMemMap(void *phys_ptr, uint32_t size)
{
    return phys_ptr; /* phys == virtual in rtos */
}

int32_t appMemUnMap(void *virt_ptr, uint32_t size)
{
    return 0; /* nothing to do in rtos */
}
