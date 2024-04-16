/*
*
* Copyright (C) 2023 Texas Instruments Incorporated
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

/**
 *  \file     Udma_Ring_LL.c
 *
 *  \brief    This file contains Udma Sciclient function definitions.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "cslr.h"
#include "Udma_Ring_LL.h"
#include "Eth_Cfg.h"

/* ========================================================================== */
/*                             Macro Definition                               */
/* ========================================================================== */

/**
*  \brief CLS RINGACC register position definition
*  @{
*/
#define CSL_RINGACC_RINGRT_RING_FDB_CNT_MASK                         (0x000000FFU)
#define CSL_RINGACC_RINGRT_RING_FDB_CNT_SHIFT                        (0x00000000U)
#define CSL_RINGACC_RINGRT_RING_FDB_CNT_MAX                          (0x000000FFU)
#define CSL_RINGACC_RINGRT_RING_FOCC_CNT_MASK                        (0x001FFFFFU)
#define CSL_RINGACC_RINGRT_RING_FOCC_CNT_SHIFT                       (0x00000000U)
#define CSL_RINGACC_RINGRT_RING_FOCC_CNT_MAX                         (0x001FFFFFU)
#define CSL_RINGACC_RINGRT_RING_RDB_ACK_MASK                         (0x80000000U)
#define CSL_RINGACC_RINGRT_RING_RDB_ACK_SHIFT                        (0x0000001FU)
#define CSL_RINGACC_RINGRT_RING_RDB_ACK_MAX                          (0x00000001U)
#define CSL_RINGACC_RINGRT_RING_RDB_CNT_MASK                         (0x000000FFU)
#define CSL_RINGACC_RINGRT_RING_RDB_CNT_SHIFT                        (0x00000000U)
#define CSL_RINGACC_RINGRT_RING_RDB_CNT_MAX                          (0x000000FFU)
#define CSL_RINGACC_RINGRT_RING_ROCC_COMP_MASK                       (0x80000000U)
#define CSL_RINGACC_RINGRT_RING_ROCC_COMP_SHIFT                      (0x0000001FU)
#define CSL_RINGACC_RINGRT_RING_ROCC_COMP_MAX                        (0x00000001U)
#define CSL_RINGACC_RINGRT_RING_ROCC_CNT_MASK                        (0x001FFFFFU)
#define CSL_RINGACC_RINGRT_RING_ROCC_CNT_SHIFT                       (0x00000000U)
#define CSL_RINGACC_RINGRT_RING_ROCC_CNT_MAX                         (0x001FFFFFU)
/* @} */

/* ========================================================================== */
/*                             Global Variable Declaration                    */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void Udma_Ring_LL_Init(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc = 0u;
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdOcc = 0u;
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx = 0u;
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdIdx = 0u;
}

Std_ReturnType Udma_Ring_LL_Queue(
    uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 phyDescMem)
{
    Std_ReturnType retVal = E_NOT_OK;

    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc =
        CSL_REG32_FEXT(Eth_GetRingFOCCReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), RINGACC_RINGRT_RING_FOCC_CNT);

    if(Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc < Eth_GetRingTotalElemNum(CtrlIdx, RingIdx))
    {
        Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx] = phyDescMem;

        if(Eth_RingGetCacheWritebackFuncPtr(CtrlIdx))
        {
            Eth_RingGetCacheWritebackFuncPtr(CtrlIdx)(
                (uint8*)&Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx],
                sizeof(uint64));
        }

        Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx = (Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx + 1u) % Eth_GetRingTotalElemNum(CtrlIdx, RingIdx);
        Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc  = Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc + 1u;

        CSL_REG32_WR(Eth_GetRingFDBReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), CSL_FMK(RINGACC_RINGRT_RING_FDB_CNT, (uint32)1u));
        retVal = E_OK;
    }

    return retVal;
}

Std_ReturnType Udma_Ring_LL_Dequeue(
    uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 *phyDescMem)
{
    Std_ReturnType retVal = E_NOT_OK;

    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdOcc =
        CSL_REG32_FEXT(Eth_GetRingROCCReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), RINGACC_RINGRT_RING_ROCC_CNT);

    if(Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdOcc > 0u)
    {
        if(Eth_RingGetCacheInvalidateFuncPtr(CtrlIdx))
        {
            Eth_RingGetCacheInvalidateFuncPtr(CtrlIdx)(
                (uint8*)&Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdIdx],
                sizeof(uint64));
        }

        *phyDescMem = Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdIdx];
        Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdOcc = Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdOcc - 1u;
        Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdIdx = (Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdIdx + 1u) % Eth_GetRingTotalElemNum(CtrlIdx, RingIdx);
        CSL_REG32_WR(Eth_GetRingRDBReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), CSL_FMK(RINGACC_RINGRT_RING_RDB_CNT, (uint32)(-1)));
        retVal = E_OK;
    }

    return retVal;
}

Std_ReturnType Udma_Ring_LL_Flush(
    uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 *phyDescMem)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint32 fifoIdx;
    uint32 Idx;

    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc =
        CSL_REG32_FEXT(Eth_GetRingFOCCReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), RINGACC_RINGRT_RING_FOCC_CNT);

    if(Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc > 0u)
    {
        if(Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx < Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc)
        {
            fifoIdx = Eth_GetRingTotalElemNum(CtrlIdx, RingIdx) - (Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc - Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx);
        }
        else
        {
            fifoIdx = Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx - Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc;
        }

        *phyDescMem = Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[fifoIdx];

        for(Idx = 0U; Idx < (Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc - 1U); Idx++)
        {
            Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[(fifoIdx + Idx) % Eth_GetRingTotalElemNum(CtrlIdx, RingIdx)] =
                Eth_GetRingMemBaseAddress(CtrlIdx, RingIdx)[(fifoIdx + Idx + 1u) % Eth_GetRingTotalElemNum(CtrlIdx, RingIdx)];
        }

        if(CSL_REG32_FEXT(Eth_GetRingFOCCReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), RINGACC_RINGRT_RING_FOCC_CNT))
        {
            CSL_REG32_WR(Eth_GetRingFDBReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), CSL_FMK(RINGACC_RINGRT_RING_FDB_CNT, (uint32)(-1u)));
        }

        if(Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx == 0U)
        {
            Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx = Eth_GetRingTotalElemNum(CtrlIdx, RingIdx) - 1u;
        }
        else
        {
            Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx = Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx - 1u;
        }

        Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc--;

        retVal = E_OK;
    }

    return retVal;
}

uint32 Udma_Ring_LL_ReadOccNum(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    return CSL_REG32_FEXT(Eth_GetRingROCCReg(Eth_GetRingHwId(CtrlIdx, RingIdx)),
        RINGACC_RINGRT_RING_ROCC_CNT);
}

uint32 Udma_Ring_LL_WriteOccNum(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    return CSL_REG32_FEXT(Eth_GetRingFOCCReg(Eth_GetRingHwId(CtrlIdx, RingIdx)),
        RINGACC_RINGRT_RING_FOCC_CNT);
}

void Udma_Ring_LL_Reset(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    uint32 regVal = 0u;

    /* Write to SIZE register to reset RING */
    regVal = CSL_REG32_RD(Eth_GetRingSizeReg(Eth_GetRingHwId(CtrlIdx, RingIdx)));
    CSL_REG32_WR(Eth_GetRingSizeReg(Eth_GetRingHwId(CtrlIdx, RingIdx)), regVal);

    /* Reset ring software index */
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrOcc = 0u;
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdOcc = 0u;
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->wrIdx = 0u;
    Eth_GetDynRingElemAddress(CtrlIdx, RingIdx)->rdIdx = 0u;
}
