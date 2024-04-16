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

#include <string.h>
#include <utils/mem/include/app_mem.h>
#include <ti/osal/HeapP.h>
#include <ti/osal/MemoryP.h>
#include <ti/osal/HwiP.h>
#include <ti/osal/CacheP.h>
#include <utils/console_io/include/app_log.h>
#include <app_mem_map.h>

#if defined(R5F) && (defined(SOC_J784S4) || defined(SOC_J721S2))
#include <ti/csl/csl_rat.h>
#endif

#define ENABLE_CACHE_OPS

#if 0
#if defined(__C7100__) || defined(__C7120__)
#undef ENABLE_CACHE_OPS /* since C7x is coherent */
#elif defined(__C7504__)
#define ENABLE_CACHE_OPS /* since C7504 is incoherent */
#endif
#endif

/* #define APP_MEM_DEBUG */

/** \brief Minmum number of bytes that will be used for alignment, MUST >= max CPU cache line size */
#define APP_MEM_ALIGN_MIN_BYTES     (128u)

#if defined(__C7100__) || defined(__C7120__)

#if defined(SOC_J721S2) || defined(SOC_J721E)
/* Offset to be added to convert virtual address to physical address */
#define VIRT_PHY_ADDR_OFFSET (DDR_64BIT_BASE_PADDR - DDR_64BIT_BASE_VADDR)

uint64_t appUdmaVirtToPhyAddrConversion(const void *virtAddr,
                                      uint32_t chNum,
                                      void *appData)
{
  uint64_t phyAddr = (uint64_t)virtAddr;

  if ((uint64_t)virtAddr >= DDR_64BIT_BASE_VADDR)
  {
    phyAddr = ((uint64_t)virtAddr + VIRT_PHY_ADDR_OFFSET);
  }

  return phyAddr;
}
#elif defined(SOC_J784S4)
extern uint64_t appUdmaVirtToPhyAddrConversion(const void *virtAddr,
                                      uint32_t chNum,
                                      void *appData);
#endif
#elif defined(__C7504__)
/* For AM62A max DDR size assumed is 2GB which falls within the 32-bit range */
/* This routine should be implemented if addition memory above 2GB is added */
uint64_t appUdmaVirtToPhyAddrConversion(const void *virtAddr,
                                      uint32_t chNum,
                                      void *appData)
{

  return (uint64_t)virtAddr;
}
#endif

typedef struct {

    uint16_t is_valid;
    HeapP_Handle rtos_heap_handle;
    uint32_t alloc_offset;
    app_mem_heap_prm_t heap_prm;

} app_mem_heap_obj_t;

typedef struct {

    app_mem_heap_obj_t heap_obj[APP_MEM_HEAP_MAX];

} app_mem_obj_t;

static app_mem_obj_t g_app_mem_obj;

void appMemInitPrmSetDefault(app_mem_init_prm_t *prm)
{
    uint32_t heap_id;

    for(heap_id = 0; heap_id < APP_MEM_HEAP_MAX; heap_id++)
    {
        app_mem_heap_prm_t *heap_prm;

        heap_prm = &prm->heap_info[heap_id];

        heap_prm->base = NULL;
        heap_prm->size = 0u;
        heap_prm->name[0u] = 0u;
        heap_prm->flags = 0;
    }
}

int32_t appMemInit(app_mem_init_prm_t *prm)
{
    int32_t status = 0;

    uint32_t heap_id;

    appLogPrintf("MEM: Init ... !!!\n");

    for(heap_id = 0; heap_id < APP_MEM_HEAP_MAX; heap_id++)
    {
        app_mem_heap_prm_t *heap_prm;
        app_mem_heap_obj_t *heap_obj;

        heap_prm = &prm->heap_info[heap_id];
        heap_obj = &g_app_mem_obj.heap_obj[heap_id];

        heap_obj->is_valid = 0;
        heap_obj->alloc_offset = 0;
        heap_obj->rtos_heap_handle = NULL;

        if( (heap_prm->base == NULL) || (heap_prm->size == 0))
        {
            /* no heap specified by user */
        }
        else
        {
            /* copy user parameters to local object */
            heap_obj->heap_prm = *heap_prm;
            /* point local variable to local object */
            heap_prm = &heap_obj->heap_prm;

            heap_obj->is_valid = 1;

            if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_TYPE_LINEAR_ALLOCATE))
            {
                /* no rtos heap, linear allocator based on offset */
                heap_obj->alloc_offset = 0;
            }
            else
            {
                /* create a rtos heap */
                HeapP_Params rtos_heap_prm;

                HeapP_Params_init(&rtos_heap_prm);
                rtos_heap_prm.buf = APP_MEM_ALIGNPTR(
                    heap_prm->base, APP_MEM_ALIGN_MIN_BYTES);
                rtos_heap_prm.size = APP_MEM_ALIGN32(
                    heap_prm->size, APP_MEM_ALIGN_MIN_BYTES);

                heap_obj->rtos_heap_handle = HeapP_create(&rtos_heap_prm);

                heap_prm->base   = rtos_heap_prm.buf;
                heap_prm->size   = rtos_heap_prm.size;
            }
            appLogPrintf("MEM: Created heap (%s, id=%d, flags=0x%08x) @ %p of size %d bytes !!!\n",
                heap_prm->name,
                heap_id,
                heap_prm->flags,
                heap_prm->base,
                heap_prm->size);
        }
    }
    appLogPrintf("MEM: Init ... Done !!!\n");
    return status;
}

int32_t appMemDeInit()
{
    int32_t status = 0;

    uint32_t heap_id;

    appLogPrintf("MEM: Deinit ... !!!\n");

    for(heap_id = 0; heap_id < APP_MEM_HEAP_MAX; heap_id++)
    {
        app_mem_heap_obj_t *heap_obj;

        heap_obj = &g_app_mem_obj.heap_obj[heap_id];

        if(heap_obj->is_valid)
        {
            if(heap_obj->rtos_heap_handle != NULL)
            {
                HeapP_delete(&heap_obj->rtos_heap_handle);
            }

            heap_obj->is_valid = 0;
            heap_obj->alloc_offset = 0;
            heap_obj->rtos_heap_handle = NULL;
        }
    }

    appLogPrintf("MEM: Deinit ... Done !!!\n");

    return status;
}

void    *appMemAlloc(uint32_t heap_id, uint32_t size, uint32_t align)
{
    void *ptr = NULL;

    if(heap_id < APP_MEM_HEAP_MAX && size != 0)
    {
        app_mem_heap_obj_t *heap_obj;
        app_mem_heap_prm_t *heap_prm;

        heap_obj = &g_app_mem_obj.heap_obj[heap_id];
        heap_prm = &heap_obj->heap_prm;

        if(heap_obj->is_valid)
        {
            if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_TYPE_LINEAR_ALLOCATE))
            {
                uint32_t offset;
                uintptr_t key;

                key = HwiP_disable();

                offset = APP_MEM_ALIGN32(heap_obj->alloc_offset, align);

                if( (offset+size) <= heap_prm->size)
                {
                    ptr = (void*)((uintptr_t)heap_prm->base + offset);

                    heap_obj->alloc_offset = (offset+size);
                }
                else
                {
                    #ifdef APP_MEM_DEBUG
                    appLogPrintf("MEM: heap mem size insufficient for memory to be allocated\n");
                    #endif
                }

                HwiP_restore(key);
            }
            else
            {
                if(heap_obj->rtos_heap_handle!=NULL)
                {
                    size  = APP_MEM_ALIGN32(size, APP_MEM_ALIGN_MIN_BYTES);

                    ptr = HeapP_alloc(heap_obj->rtos_heap_handle,
                               size);

                    if(ptr!=NULL)
                    {
                        if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_DO_CLEAR_ON_ALLOC))
                        {
                            memset(ptr, 0, size);
                        }
                        if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_IS_SHARED))
                        {
                            appMemCacheWbInv(ptr, size);
                        }
                        #ifdef APP_MEM_DEBUG
                        appLogPrintf("MEM: Allocated %d bytes @ 0x%08x\n", size, (uint32_t)(uintptr_t)ptr);
                        #endif
                    }
                }
            }
        }
    }
    return ptr;
}

int32_t appMemResetScratchHeap(uint32_t heap_id)
{
    int32_t status = -1;

    if(heap_id < APP_MEM_HEAP_MAX)
    {
        app_mem_heap_obj_t *heap_obj;
        app_mem_heap_prm_t *heap_prm;

        heap_obj = &g_app_mem_obj.heap_obj[heap_id];
        heap_prm = &heap_obj->heap_prm;

        if(heap_obj->is_valid)
        {
            if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_TYPE_LINEAR_ALLOCATE))
            {
                uintptr_t key;

                key = HwiP_disable();

                heap_obj->alloc_offset = 0;

                HwiP_restore(key);

                status = 0;
            }
            else
            {
                #ifdef APP_MEM_DEBUG
                appLogPrintf("appMemResetScratchHeap: invalid heap ID\n");
                #endif
            }
        }
    }
    return status;
}

int32_t appMemFree(uint32_t heap_id, void *ptr, uint32_t size)
{
    int32_t status = -1;

    if(heap_id < APP_MEM_HEAP_MAX)
    {
        app_mem_heap_obj_t *heap_obj;
        app_mem_heap_prm_t *heap_prm;

        heap_obj = &g_app_mem_obj.heap_obj[heap_id];
        heap_prm = &heap_obj->heap_prm;

        if(heap_obj->is_valid)
        {
            if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_TYPE_LINEAR_ALLOCATE))
            {
                uintptr_t key;

                key = HwiP_disable();

                heap_obj->alloc_offset = 0;

                HwiP_restore(key);

                status = 0;
            }
            else
            {
                if(heap_obj->rtos_heap_handle!=NULL && ptr != NULL && size != 0)
                {
                    size  = APP_MEM_ALIGN32(size, APP_MEM_ALIGN_MIN_BYTES);

                    if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_IS_SHARED))
                    {
                        appMemCacheWbInv(ptr, size);
                    }

                    #ifdef APP_MEM_DEBUG
                    appLogPrintf("MEM: Freeing %d bytes @ 0x%08x\n", size, (uint32_t)(uintptr_t)ptr);
                    #endif

                    HeapP_free(heap_obj->rtos_heap_handle,
                        ptr,
                        size);

                    status = 0;
                }
            }
        }
    }
    return status;
}

int32_t appMemStats(uint32_t heap_id, app_mem_stats_t *stats)
{
    int32_t status = -1;

    if(heap_id < APP_MEM_HEAP_MAX && stats != NULL )
    {
        app_mem_heap_obj_t *heap_obj;
        app_mem_heap_prm_t *heap_prm;

        heap_obj = &g_app_mem_obj.heap_obj[heap_id];
        heap_prm = &heap_obj->heap_prm;

        stats->heap_id = heap_id;
        strncpy(stats->heap_name, "INVALID", APP_MEM_HEAP_NAME_MAX);
        stats->heap_name[APP_MEM_HEAP_NAME_MAX-1]=0;
        stats->heap_size = 0;
        stats->free_size = 0;

        if(heap_obj->is_valid)
        {
            stats->heap_id = heap_id;
            strncpy(stats->heap_name, heap_prm->name, APP_MEM_HEAP_NAME_MAX);
            stats->heap_name[APP_MEM_HEAP_NAME_MAX-1]=0;
            stats->heap_size = heap_prm->size;

            if( (heap_prm->flags & APP_MEM_HEAP_FLAGS_TYPE_LINEAR_ALLOCATE))
            {
                uintptr_t key;

                key = HwiP_disable();

                stats->free_size = heap_prm->size - heap_obj->alloc_offset;

                HwiP_restore(key);

                status = 0;
            }
            else
            {
                if(heap_obj->rtos_heap_handle!=NULL)
                {
                    HeapP_MemStats rtos_heap_stats;

                    HeapP_getHeapStats(heap_obj->rtos_heap_handle, &rtos_heap_stats);

                    stats->free_size = rtos_heap_stats.totalFreeSize;

                    status = 0;
                }
            }
        }
    }
    else
    {
        if(stats!=NULL)
        {
            stats->heap_id = heap_id;
            strncpy(stats->heap_name, "INVALID", APP_MEM_HEAP_NAME_MAX);
            stats->heap_name[APP_MEM_HEAP_NAME_MAX-1]=0;
            stats->heap_size = 0;
            stats->free_size = 0;
        }
    }
    return status;
}

#if defined(__C7100__) || defined(__C7120__) || defined(__C7504__)
#include <c6x_migration.h>
#include <c7x.h>
#endif

void appMemFence()
{
    #if defined(__C7100__) || defined(__C7120__) || defined(__C7504__)
    _mfence();
    _mfence();
    #endif
}

void  appMemCacheInv(void *ptr, uint32_t size)
{
    #ifdef ENABLE_CACHE_OPS
    CacheP_Inv(
        ptr,
        APP_MEM_ALIGN32(size, APP_MEM_ALIGN_MIN_BYTES));
    #endif
    appMemFence();
}

void  appMemCacheWb(void *ptr, uint32_t size)
{
    #ifdef ENABLE_CACHE_OPS
    CacheP_wb(
        ptr,
        APP_MEM_ALIGN32(size, APP_MEM_ALIGN_MIN_BYTES));
    #endif
    appMemFence();

}

void  appMemCacheWbInv(void *ptr, uint32_t size)
{
    #ifdef ENABLE_CACHE_OPS
    CacheP_wbInv(
        ptr,
        APP_MEM_ALIGN32(size, APP_MEM_ALIGN_MIN_BYTES));
    #endif
    appMemFence();
}

uint64_t appMemGetVirt2PhyBufPtr(uint64_t virtPtr, uint32_t heap_id)
{
    /* For rtos implementation, virtual and shared pointers are same
     */
#if defined(__C7100__) || defined(__C7120__)
    uint64_t physPtr;

    physPtr = appUdmaVirtToPhyAddrConversion((void*)virtPtr, 0, NULL);

    return physPtr;
#else
    return virtPtr;

#endif
}

uint32_t appMemGetDmaBufFd(void *virPtr, volatile uint32_t *dmaBufFdOffset)
{
   /* For rtos implementation, dmaBufFd is not valid and just return 0
     */
    *dmaBufFdOffset = 0;
    return (uint32_t)(-1);
}

int32_t appMemTranslateDmaBufFd(uint32_t dmaBufFd, uint32_t size, uint64_t *virtPtr, uint64_t *phyPtr)
{
    /* For rtos implementation, dmaBufFd is not valid and just return -1. */
    return -1;
}

void appMemCloseDmaBufFd(int32_t dmaBufFd)
{
   /* For rtos implementation, dmaBufFd is not valid and just return 0
     */
    return;
}

void appMemPrintMemAllocInfo()
{
    return;
}

#if defined (SOC_J784S4) && defined (C7120)

#define APP_MEM_DMC_L1DWBINV_WBINV_MASK                             (0x00000001U)
#define APP_MEM_DMC_L1DWBINV_WBINV_SHIFT                            (0U)
#define APP_MEM_DMC_L1DWBINV_WBINV_RESETVAL                         (0x00000000U)
#define APP_MEM_DMC_L1DWBINV_WBINV_MAX                              (0x00000001U)
#define APP_MEM_UMC_L2WBINV_WBINV_MASK                              (0x00000001ULL)
#define APP_MEM_UMC_L2WBINV_WBINV_SHIFT                             (0ULL)
#define APP_MEM_UMC_L2WBINV_WBINV_RESETVAL                          (0x00000000ULL)
#define APP_MEM_UMC_L2WBINV_WBINV_MAX                               (0x00000001ULL)

__asm__ __volatile__("appMemC7xSetL1DWBINV: \n"
                     "    MVC   .S1 A4,     ECR259; \n"
                     "    RET   .B1\n"
          );
__asm__ __volatile__("appMemC7xGetL1DWBINV: \n"
        " MVC   .S1 ECR259, A4  ; \n"
          " RET .B1; \n"
       );

__asm__ __volatile__("appMemC7xSetL2WBINV: \n"
                     "    MVC   .S1 A4,     ECR387  ; \n"
                     "    RET   .B1\n"
          );
__asm__ __volatile__("appMemC7xGetL2WBINV: \n"
        " MVC   .S1 ECR387, A4  ; \n"
          " RET .B1; \n"
       );

void appMemC7xCleaninvalidateL1DCache()
{
    volatile uint64_t wbinv;
    wbinv  = appMemC7xGetL1DWBINV();
    wbinv  &= ~APP_MEM_DMC_L1DWBINV_WBINV_MASK;
    wbinv |= (0x1U << APP_MEM_DMC_L1DWBINV_WBINV_SHIFT) & APP_MEM_DMC_L1DWBINV_WBINV_MASK;
    appMemC7xSetL1DWBINV(wbinv);
    return;
}

void appMemC7xCleaninvalidateL2Cache()
{
    volatile uint64_t       wbinv;
    wbinv = appMemC7xGetL2WBINV() & ~APP_MEM_UMC_L2WBINV_WBINV_MASK;
    wbinv |= (0x1U << APP_MEM_UMC_L2WBINV_WBINV_SHIFT) & APP_MEM_UMC_L2WBINV_WBINV_MASK;
    appMemC7xSetL2WBINV(wbinv);
    return;
}
#endif

#if defined(R5F) && (defined(SOC_J784S4) || defined(SOC_J721S2))

int32_t appMemAddrTranslate(app_mem_rat_prm_t *prm)
{
    int32_t status = 0;
    bool ret = false, availableRatRegion = false;
    uint32_t maxRegions, i;
    bool        bIsEnabled;
    uintptr_t key;

    CSL_RatTranslationCfgInfo translationCfg;
    CSL_ratRegs *pGTCRatRegs = (CSL_ratRegs *)(CSL_R5FSS0_RAT_CFG_BASE);

    maxRegions = CSL_ratGetMaxRegions(pGTCRatRegs);

    key = HwiP_disable();

    for (i = 0; i < maxRegions; i++)
    {
        bIsEnabled = CSL_ratIsRegionTranslationEnabled(pGTCRatRegs,i);
        if (false == bIsEnabled)
        {
            #ifdef APP_MEM_DEBUG
            appLogPrintf("appMemAddrTranslate(): Using RAT region %d for translation of address : %llx\n", i, prm->translatedAddress);
            #endif
            availableRatRegion = (bool)true;
            break;
        }
    }

    if ((bool)true == availableRatRegion)
    {
        translationCfg.sizeInBytes       = prm->size;
        translationCfg.baseAddress       = prm->baseAddress;
        translationCfg.translatedAddress = prm->translatedAddress;

        ret = CSL_ratConfigRegionTranslation(pGTCRatRegs, i, &translationCfg);

        if(ret == (bool)false)
        {
            appLogPrintf("appMemAddrTranslate(): Error in CSL_ratConfigRegionTranslation()\n");
            status = -1;
        }

        #ifdef APP_MEM_DEBUG
        for (i = 0; i < maxRegions; i++)
        {
            bIsEnabled = CSL_ratIsRegionTranslationEnabled(pGTCRatRegs,i);
            appLogPrintf("appMemAddrTranslate(): RAT region %d translation enabled status after OCMC map (0: disabled, 1: enabled): %d\n", i, bIsEnabled);
        }
        #endif
    }
    else
    {
        appLogPrintf("appMemAddrTranslate(): No available RAT regions for mapping\n");
        status = -1;
    }

    HwiP_restore(key);

    return status;
}

#endif
