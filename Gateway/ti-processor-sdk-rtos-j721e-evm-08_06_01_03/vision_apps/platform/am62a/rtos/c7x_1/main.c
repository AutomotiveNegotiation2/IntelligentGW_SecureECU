/*
 *
 * Copyright (c) 2018 Texas Instruments Incorporated
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

#include <app.h>
#include <utils/console_io/include/app_log.h>
#include <utils/misc/include/app_misc.h>
#include <stdio.h>
#include <string.h>
#include <ti/osal/osal.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/HwiP.h>
#include <ti/osal/CacheP.h>
#include <app_mem_map.h>
#include <app_ipc_rsctable.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_clec.h>

#if (defined (FREERTOS))
#include <ti/kernel/freertos/portable/TI_CGT/c7x/Cache.h>
#include <ti/kernel/freertos/portable/TI_CGT/c7x/Hwi.h>
#include <ti/kernel/freertos/portable/TI_CGT/c7x/Mmu.h>
#else
#include <ti/sysbios/family/c7x/Cache.h>
#include <ti/sysbios/family/c7x/Hwi.h>
#include <ti/sysbios/family/c7x/Mmu.h>
#endif

#define ENABLE_C7X_CACHE_WRITE_THROUGH

#define C7x_EL2_SNOOP_CFG_REG (0x7C00000Cu)

#define DISABLE_C7X_SNOOP_FILTER    (0) /*On reset value is 0*/
#define ENABLE_C7X_MMU_TO_DMC_SNOOP (1) /*On reset value is 1*/
#define ENABLE_C7X_PMC_TO_DMC_SNOOP (0) /*On reset value is 1*/
#define ENABLE_C7X_SE_TO_DMC_SNOOP  (1) /*On reset value is 1*/
#define ENABLE_C7X_DRU_TO_DMC_SNOOP (1) /*On reset value is 1*/
#define ENABLE_C7X_SOC_TO_DMC_SNOOP (1) /*On reset value is 1*/

static void setC7xSnoopCfgReg()
{
    volatile uint32_t *pReg = (uint32_t *)C7x_EL2_SNOOP_CFG_REG;

    /* This operation overrides the existing value of snoop config!*/
    *pReg = (uint32_t)((DISABLE_C7X_SNOOP_FILTER    << 31) |
                       (ENABLE_C7X_MMU_TO_DMC_SNOOP << 18) |
                       (ENABLE_C7X_PMC_TO_DMC_SNOOP << 17) |
                       (ENABLE_C7X_SE_TO_DMC_SNOOP  << 16) |
                       (ENABLE_C7X_DRU_TO_DMC_SNOOP << 1)  |
                       (ENABLE_C7X_SOC_TO_DMC_SNOOP << 0));
}


static void appMain(void* arg0, void* arg1)
{
    appUtilsTaskInit();
    appInit();
    appRun();
    #if 1
    while(1)
    {
        appLogWaitMsecs(100u);
    }
    #else
    appDeInit();
    #endif
}

void StartupEmulatorWaitFxn (void)
{
    volatile uint32_t enableDebug = 0;
    do
    {
    }while (enableDebug);
}

/* IMPORTANT NOTE: For C7x,
 * - stack size and stack ptr MUST be 8KB aligned
 * - AND min stack size MUST be 16KB
 * - AND stack assigned for task context is "size - 8KB"
 *       - 8KB chunk for the stack area is used for interrupt handling in this task context
 */
static uint8_t gTskStackMain[64*1024]
__attribute__ ((section(".bss:taskStackSection")))
__attribute__ ((aligned(8192)))
    ;

#if defined(ENABLE_C7X_CACHE_WRITE_THROUGH)

#ifdef __cplusplus
extern "C" {
#endif

void temp_CSL_c7xSetL1DCFG(uint64_t param);

#ifdef __cplusplus
}
#endif

__asm__ __volatile__("temp_CSL_c7xSetL1DCFG: \n"
" MVC .S1 A4, ECR256 ; \n"
" RET .B1\n"
);

static void configureC7xL1DCacheAsWriteThrough()
{
    volatile uint64_t l1dcfg = 0x1U;
    Cache_wbInvL1dAll();
    temp_CSL_c7xSetL1DCFG(l1dcfg);
}
#endif

int main(void)
{
    TaskP_Params tskParams;
    TaskP_Handle task;

    StartupEmulatorWaitFxn();

    OS_init();

    TaskP_Params_init(&tskParams);
    tskParams.priority = 8u;
    tskParams.stack = gTskStackMain;
    tskParams.stacksize = sizeof (gTskStackMain);
    task = TaskP_create(appMain, &tskParams);
    if(NULL == task)
    {
        OS_stop();
    }
    OS_start();

    return 0;
}

uint32_t g_app_rtos_c7x_mmu_map_error = 0;

void appMmuMap(Bool is_secure)
{
    Bool            retVal;
    Mmu_MapAttrs    attrs;

    uint32_t ns = 1;

    if(is_secure)
        ns = 0;
    else
        ns = 1;

    Mmu_initMapAttrs(&attrs);

    attrs.attrIndx = Mmu_AttrIndx_MAIR0;
    attrs.ns = ns;

    retVal = Mmu_map(0x00000000, 0x00000000, 0x20000000, &attrs, is_secure);
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x20000000, 0x20000000, 0x20000000, &attrs, is_secure);
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x40000000, 0x40000000, 0x20000000, &attrs, is_secure);
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x60000000, 0x60000000, 0x10000000, &attrs, is_secure);
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x70000000, 0x70000000, 0x10000000, &attrs, is_secure);
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x7C200000U, 0x7C200000U, 0x00100000U, &attrs, is_secure); /* CLEC */
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(0x7C400000U, 0x7C400000U, 0x00100000U, &attrs, is_secure); /* DRU */
    if(retVal==FALSE)
    {
        goto mmu_exit;
    }

    Mmu_initMapAttrs(&attrs);

    attrs.attrIndx = Mmu_AttrIndx_MAIR4;
    attrs.ns = ns;

    retVal = Mmu_map(APP_LOG_MEM_ADDR, APP_LOG_MEM_ADDR, APP_LOG_MEM_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(TIOVX_OBJ_DESC_MEM_ADDR, TIOVX_OBJ_DESC_MEM_ADDR, TIOVX_OBJ_DESC_MEM_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(IPC_VRING_MEM_ADDR, IPC_VRING_MEM_ADDR, IPC_VRING_MEM_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

	retVal = Mmu_map(DDR_C7x_1_IPC_ADDR, DDR_C7x_1_IPC_ADDR, 2*DDR_C7x_1_IPC_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(TIOVX_LOG_RT_MEM_ADDR, TIOVX_LOG_RT_MEM_ADDR, TIOVX_LOG_RT_MEM_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7X_1_LOCAL_HEAP_NON_CACHEABLE_ADDR, DDR_C7X_1_LOCAL_HEAP_NON_CACHEABLE_ADDR, DDR_C7X_1_LOCAL_HEAP_NON_CACHEABLE_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7X_1_SCRATCH_NON_CACHEABLE_ADDR, DDR_C7X_1_SCRATCH_NON_CACHEABLE_ADDR, DDR_C7X_1_SCRATCH_NON_CACHEABLE_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    Mmu_initMapAttrs(&attrs);
    attrs.attrIndx = Mmu_AttrIndx_MAIR7;
    attrs.ns = ns;

    retVal = Mmu_map(L2RAM_C7x_1_MAIN_ADDR, L2RAM_C7x_1_MAIN_ADDR, 0x01000000, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(L2RAM_C7x_1_AUX_ADDR, L2RAM_C7x_1_AUX_ADDR, 0x01000000, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7x_1_DTS_ADDR, DDR_C7x_1_DTS_ADDR, DDR_C7x_1_DTS_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_SHARED_MEM_ADDR, DDR_SHARED_MEM_ADDR, DDR_SHARED_MEM_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7X_1_LOCAL_HEAP_ADDR, DDR_C7X_1_LOCAL_HEAP_ADDR, DDR_C7X_1_LOCAL_HEAP_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

    retVal = Mmu_map(DDR_C7X_1_SCRATCH_ADDR, DDR_C7X_1_SCRATCH_ADDR, DDR_C7X_1_SCRATCH_SIZE, &attrs, is_secure);
    if(retVal == FALSE)
    {
        goto mmu_exit;
    }

mmu_exit:
    if(retVal == FALSE)
    {
        g_app_rtos_c7x_mmu_map_error++;
    }

    return;
}

void appCacheInit()
{
    /* Going with default cache setting on reset */
    /* L1P - 32kb$, L1D - 64kb$, L2 - 0kb$ */
#if defined(ENABLE_C7X_CACHE_WRITE_THROUGH)
    configureC7xL1DCacheAsWriteThrough();
#endif

    setC7xSnoopCfgReg();

}

void InitMmu(void)
{
    /* This is for debug purpose - see the description of function header */
    g_app_rtos_c7x_mmu_map_error = 0;

    /* There is no secure mode in C7504 */
    appMmuMap(FALSE);

    appCacheInit();
}
