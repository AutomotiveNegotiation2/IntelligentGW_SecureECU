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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/mman_peer.h>
#include <sys/neutrino.h>
#include <errno.h>
#include <hw/inout.h>
#include <string.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/CacheP.h>
#include <process.h>

#include <utils/mem/include/app_mem.h>
#include <SharedMemoryAllocatorUsr.h>

//#define APP_MEM_DEBUG
/**
 * \brief Memory module initialization parameters
 */
typedef struct {

} app_qnx_init_prm_t;

//static app_qnx_init_prm_t g_app_mem_init_prm;
#define MAX_BUFS 10240
shm_buf bufs[MAX_BUFS];

int32_t appMemInit(app_mem_init_prm_t *prm)
{
    int32_t status = 0;
    #ifdef APP_MEM_DEBUG
    printf("MEM: Init ... !!!\n");
    #endif

    /* Get I/O privilege */
    ThreadCtl (_NTO_TCTL_IO, 0);

    memset(&bufs[0], 0, (sizeof(shm_buf) * MAX_BUFS));

    #ifdef APP_MEM_DEBUG
    printf("MEM: Init ... Done !!!\n");
    #endif
    return(status);
}

int32_t appMemDeInit(void)
{
    int32_t status = 0;

    #ifdef APP_MEM_DEBUG
    printf("MEM: Deinit ... empty function !!!\n");
    printf("MEM: Deinit ... Done !!!\n");
    #endif

    return(status);
}


// Don't care for now, will be called for OpenGL
uint64_t appMemGetDmaBufFd(void *virPtr, volatile uint32_t *dmaBufFdOffset)
{
    uint64_t physAddr = (uint32_t)-1;
    int i = 0;

    #ifdef APP_MEM_DEBUG
    printf("MEM: appMemGetDmaBufFd ... !!!\n");
    #endif

    /* Find buffer */
    for(i=0; i < MAX_BUFS; i++)
    {
        if((void *) bufs[i].vir_addr == virPtr)
        {
            break;
        }
    }
    if(i == MAX_BUFS)
    {
        #ifdef APP_MEM_DEBUG
        printf("appMemGetDmaBufFd: Unable to locate buffer\n");
        #endif
    }
    else
    {
        physAddr = bufs[i].phy_addr;
    }

    return(physAddr);
}

int32_t appMemTranslateDmaBufFd(uint64_t dmaBufFd, uint32_t size, uint64_t *virtPtr, uint64_t *phyPtr)
{
    int32_t status = 0;
    int i = 0;

    #ifdef APP_MEM_DEBUG
    printf("MEM: appMemTranslateDmaBufFd ... !!!\n");
    #endif

    /* Find buffer */
    for(i=0; i < MAX_BUFS; i++)
    {
        if( (bufs[i].phy_addr == dmaBufFd) ||
            (bufs[i].phy_addr == 0) )
        {
            break;
        }
    }
    if(i == MAX_BUFS)
    {
        #ifdef APP_MEM_DEBUG
        printf("appMemTranslateDmaBufFd: Unable to locate buffer\n");
        #endif
        status = -1;
    }
    else
    {
        int pid;

        pid = getpid();

        /* If the virtual buffer is already being used in this process, it does not need to be mapped */
        if (pid == bufs[i].pid)
        {
            if (bufs[i].phy_addr != 0)
            {
                *virtPtr = bufs[i].vir_addr;
            }
            else
            {
                #ifdef APP_MEM_DEBUG
                printf("appMemTranslateDmaBufFd: Physical pointer has not been mapped in this process\n");
                #endif
                status = -1;
            }
        }
        else
        {
            /* Since the virtual pointer is not used in this process, map the virtual pointer to this process */
            *virtPtr = (uint64_t)mmap_peer(pid, NULL, size, PROT_READ | PROT_WRITE, MAP_PHYS | MAP_SHARED, NOFD, dmaBufFd);

            if (virtPtr == MAP_FAILED)
            {
                perror(__FUNCTION__);
                virtPtr = NULL;
                status = -1;
            }
            else
            {
                /* Virtual pointer in the buffer structure set to newly mapped virtual pointer and pid updated */
                bufs[i].vir_addr = (uint64_t)virtPtr;
                bufs[i].pid = pid;
                bufs[i].size = size;
                bufs[i].phy_addr = dmaBufFd;
            }
        }

        *phyPtr  = bufs[i].phy_addr;
    }

    return(status);
}

// Don't care for now, will be called for OpenGL
void appMemCloseDmaBufFd(uint64_t dmaBufFd)
{

    #ifdef APP_MEM_DEBUG
    printf("MEM: appMemCloseDmaBufFd ... FIXME!!!\n");
    #endif

    return;
}

uint64_t appMemGetVirt2PhyBufPtr(uint64_t virtPtr, uint32_t heap_id)
{
    off_t   phyPtr = 0;
    size_t  len = 0;
    int32_t ret = 0;
    int64_t offset = 0;


    #ifdef APP_MEM_DEBUG
    printf("MEM: appMemGetVirt2PhyBufPtr ... !!!\n");
    #endif

	  ret = mem_offset64((void *) virtPtr, NOFD, 4096, &offset, &len);
	  if (ret) {
	  	printf("MEM: Error from mem_offset\n");
	  	exit(-1);
	  }

	  phyPtr = (uint64_t)offset;
    #ifdef APP_MEM_DEBUG
	  printf("MEM: phyPtr 0x%x len/%d for virtPtr/0x%lx\n",(uint32_t) phyPtr, (int) len, virtPtr);
    #endif
    return (uint64_t)(phyPtr);
}

void *appMemAlloc(uint32_t block, uint32_t size, uint32_t align)
{
    void *virtPtr = 0;
    int32_t status = 0;
    int i = 0;

    #ifdef APP_MEM_DEBUG
    printf("MEM: appMemAlloc ... !!!\n");
    #endif

    /* Find empty buffer */
    for(i=0; i < MAX_BUFS; i++)
    {
        if(bufs[i].phy_addr == 0)
        {
            break;
        }
    }
    #ifdef APP_MEM_DEBUG
    printf("MEM: Using buf/%d\n",i);
    #endif
    if(align > 0) {
       status = SHM_alloc_aligned(size, align, &bufs[i]);
       #ifdef APP_MEM_DEBUG
       printf("\nMEM : SHM_alloc_aligned(%d, %d) : %s\n", size, align, status?"FAILED":"PASSED");
       #endif
    }
    else {
       status = SHM_alloc(size, &bufs[i]);
       #ifdef APP_MEM_DEBUG
       printf("\nMEM : SHM_alloc(%d) : %s\n", size, status?"FAILED":"PASSED");
       #endif
    }

    if(status)
    {
       #ifdef APP_MEM_DEBUG
       printf("MEM: allocation of size %d failed \n", size);
       #endif
    }

    virtPtr = (void *) (bufs[i].vir_addr);

    #ifdef APP_MEM_DEBUG
    printf("MEM: Allocated memory - virt base address = %p, phy/0x%08x size = %d \n", (void *) virtPtr, bufs[i].phy_addr, size);
    #endif
    return(virtPtr);
}

int32_t appMemFree(uint32_t block, void *virtPtr, uint32_t size )
{
    int32_t status = 0;
    int i = 0;


    #ifdef APP_MEM_DEBUG
    printf("MEM: appMemFree ... !!!\n");
    #endif

    /* Find buffer */
    for(i=0; i < MAX_BUFS; i++)
    {
        if((void *) bufs[i].vir_addr == virtPtr)
        {
            break;
        }
    }
    if(i == MAX_BUFS)
    {
        #ifdef APP_MEM_DEBUG
        printf("MEM: Unable to locate buffer to free\n");
        #endif
    }
    else {
        #ifdef APP_MEM_DEBUG
        printf("MEM: Found virtPtr at buf/%d, virt/%0x08x phy/%0x08x size/%d\n",i, bufs[i].vir_addr, bufs[i].phy_addr, size);
        #endif
        status = SHM_release(&bufs[i]);
        if(status)
        {
        #ifdef APP_MEM_DEBUG
          printf("MEM: unable to release shared memory virtual address/%p size %d \n", virtPtr, size);
        #endif
        }
        else
        {
            bufs[i].phy_addr = 0;
        }

    }
    virtPtr = NULL;

    return(status);
}

int32_t appMemStats(uint32_t block, app_mem_stats_t *stats)
{
    /* TBD */
    return(0);
}

void  appMemCacheInv(void *ptr, uint32_t size)
{
    /* Use the OSAL Cache APIs */
    CacheP_Inv(ptr, size);
}

void  appMemCacheWbInv(void *ptr, uint32_t size)
{
    /* Use the OSAL Cache APIs */
    CacheP_wbInv(ptr, size);
}

void  appMemCacheWb(void *ptr, uint32_t size)
{
    /* Use the OSAL Cache APIs */
    CacheP_wb(ptr, size);
}

/* Note: needed for linking tivx mem platform layer*/
int32_t appMemResetScratchHeap(uint32_t heap_id)
{
    return(0);
}

void appMemPrintMemAllocInfo()
{
    return;
}
