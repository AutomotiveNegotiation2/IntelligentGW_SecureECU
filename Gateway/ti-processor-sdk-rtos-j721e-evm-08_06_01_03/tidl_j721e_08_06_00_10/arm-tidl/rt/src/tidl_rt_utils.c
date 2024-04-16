/*
*
* Copyright (c) {2015 - 2021} Texas Instruments Incorporated
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


/** @file tivx_utils.c
*
*  @brief  This file contains common TIVX utilities used by TIDL Modules
*
*
*  @date   Jul 2021
*
*/
#include "itidl_rt.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "TI/tivx.h"

typedef struct  {
  void *base_addr;
  void *aligned_addr;
  int32_t size;
} sDevice_Mem_t;



#define MAM_MEM_RECS (128)
sDevice_Mem_t device_mems[MAM_MEM_RECS] = {0};

int32_t get_free_mem_rec(void)
{
  for (int i = 0; i <MAM_MEM_RECS; i++)
  {
    if(device_mems[i].base_addr == NULL)
    {
      return i;
    }
  }
  return -1;
}

int32_t get_used_mem_rec(void* ptr)
{
  for (int i = 0; i <MAM_MEM_RECS; i++)
  {
    if(device_mems[i].aligned_addr == ptr)
    {
      return i;
    }
  }
  return -1;
}

uintptr_t val_align(uintptr_t in, int32_t align)
{
  return (((in + align - 1) / align) * align);
}

void * TIDLRT_allocSharedMem(int32_t alignment, int32_t size)
{
  int32_t mem_rec = get_free_mem_rec();
  if(mem_rec != -1)
  {
    sDevice_Mem_t *dm = &device_mems[mem_rec];
    dm->base_addr = tivxMemAlloc((size + alignment), TIVX_MEM_EXTERNAL);
    dm->size = (size + alignment);
    if (dm->base_addr != NULL)
    {
      dm->aligned_addr = (void*)val_align((uintptr_t)dm->base_addr, alignment);
      return dm->aligned_addr;
    }
  }
  return NULL;
}

void TIDLRT_freeSharedMem(void * ptr)
{
  if(ptr)
  {
    int32_t mem_rec = get_used_mem_rec(ptr);
    if(mem_rec != -1)
    {
      sDevice_Mem_t *dm = &device_mems[mem_rec];
      tivxMemFree(dm->base_addr, dm->size, TIVX_MEM_EXTERNAL);
      dm->base_addr = NULL;
      dm->aligned_addr = NULL;
      dm->size = 0;
    }
  }
}

int32_t TIDLRT_isSharedMem(void *ptr)
{
    uint64_t fd;
    void *phyAddr;
    int32_t tivx_mem_status = tivxMemTranslateVirtAddr(ptr, &fd, &phyAddr);
    if((phyAddr == NULL) || (tivx_mem_status == -1))
    {
      return 0;
    }
    else
    {
      return 1;
    }
}
#ifdef __cplusplus
}
#endif
