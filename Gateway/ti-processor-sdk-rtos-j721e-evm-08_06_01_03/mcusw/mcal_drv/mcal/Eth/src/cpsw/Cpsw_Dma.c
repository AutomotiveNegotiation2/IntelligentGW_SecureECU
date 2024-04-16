/*
*
* Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Cpsw_Dma.c
 *
 *  \brief    This file contains CPPI-related functionality.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Eth_Cfg.h"
#include "Udma.h"
#include "cpsw/Cpsw_Dma.h"

/* ========================================================================== */
/*                             Global Function Definition                     */
/* ========================================================================== */

Std_ReturnType CpswDma_open(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;
    uint8 index;

    for(index = 0u; index < Eth_GetRingTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Ring_Init(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetTxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_TxOpen(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetRxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_RxOpen(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetFlowTotalNumber(ctrlIdx); ++index)
    {
        retVal |= Udma_Flow_Enable(ctrlIdx, index);
    }

#if (ETH_DMA_IR_SUPPORT == STD_ON)
    for(index = 0u; index < Eth_GetEventTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_MasterEvent_Init(ctrlIdx, index);
    }
#endif

    for(index = 0u; index < Eth_GetRingEventTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_RingEvent_Init(ctrlIdx, index);
    }

    return retVal;
}

Std_ReturnType CpswDma_close(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;
    uint8 index;

    for(index = 0u; index < Eth_GetRingEventTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_RingEvent_Release(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetTxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_TxClose(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetRxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_RxClose(ctrlIdx, index);
    }

    return retVal;
}

Std_ReturnType CpswDma_enable(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;
    uint8 index;

    for(index = 0u; index < Eth_GetTxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_TxEnable(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetRxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_RxEnable(ctrlIdx, index);
    }

    return retVal;
}

Std_ReturnType CpswDma_disable(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;
    uint8 index;

    for(index = 0u; index < Eth_GetTxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_TxDisable(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetRxChanTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_Channel_RxDisable(ctrlIdx, index);
    }

    for(index = 0u; index < Eth_GetEventTotalNum(ctrlIdx); ++index)
    {
        retVal |= Udma_MasterEvent_Disable(ctrlIdx, index);
    }

    return retVal;
}

Std_ReturnType CpswDma_submitDesc(uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 DescAddr)
{
    return Udma_Ring_Queue(CtrlIdx, RingIdx, DescAddr);
}

Std_ReturnType CpswDma_retrieveDesc(uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 *DescAddrPtr)
{
    return Udma_Ring_DeQueue(CtrlIdx, RingIdx, DescAddrPtr);
}

Std_ReturnType CpswDma_flushDesc(uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 *DescAddrPtr)
{
    return Udma_Ring_Flush(CtrlIdx, RingIdx, DescAddrPtr);
}

uint32 CpswDma_retrieveReadPendingDescNumber(uint8 CtrlIdx,
    uint8 RingIdx)
{
    return Udma_Ring_ReadOccNum(CtrlIdx, RingIdx);
}

uint32 CpswDma_retrieveWritePendingDescNumber(uint8 CtrlIdx,
    uint8 RingIdx)
{
    return Udma_Ring_WriteOccNum(CtrlIdx, RingIdx);
}
