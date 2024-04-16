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
 *  \file     Udma.h
 *
 *  \brief    This file contains Udma function definitions.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Eth_Cfg.h"
#include "Udma.h"
#include "Udma_SciClient.h"
#include "Udma_Ring_LL.h"
#include "Udma_LL.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
Std_ReturnType Udma_Channel_TxOpen(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    Std_ReturnType retVal = E_OK;

    retVal |= Eth_UdmaSciClient_TxChannelPair(CtrlIdx, ChIdx);
    retVal |= Eth_UdmaSciClient_TxChannelConfig(CtrlIdx, ChIdx);

    return retVal;
}

Std_ReturnType Udma_Channel_RxOpen(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    Std_ReturnType retVal = E_OK;

    retVal |= Eth_UdmaSciClient_RxChannelPair(CtrlIdx, ChIdx);
    retVal |= Eth_UdmaSciClient_RxChannelConfig(CtrlIdx, ChIdx);

    return retVal;
}

Std_ReturnType Udma_Channel_TxClose(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    return Eth_UdmaSciClient_TxChannelUnPair(CtrlIdx, ChIdx);
}

Std_ReturnType Udma_Channel_RxClose(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    return Eth_UdmaSciClient_RxChannelUnPair(CtrlIdx, ChIdx);
}

Std_ReturnType Udma_Channel_TxEnable(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    return Udma_Channel_LL_TxEnable(CtrlIdx, ChIdx);
}

Std_ReturnType Udma_Channel_RxEnable(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    return Udma_Channel_LL_RxEnable(CtrlIdx, ChIdx);
}

Std_ReturnType Udma_Channel_TxDisable(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    return Udma_Channel_LL_TxDisable(CtrlIdx, ChIdx);
}

Std_ReturnType Udma_Channel_RxDisable(
    uint8 CtrlIdx,
    uint8 ChIdx)
{
    return Udma_Channel_LL_RxDisable(CtrlIdx, ChIdx);
}

#if (ETH_DMA_IR_SUPPORT == STD_ON)
Std_ReturnType Udma_MasterEvent_Init(
    uint8 CtrlIdx,
    uint8 EventIdx)
{
    Std_ReturnType retVal = E_OK;

    retVal |= Eth_UdmaSciClient_EventrmTranslateIrOutput(
        Eth_GetEventIrIntrNum(CtrlIdx, EventIdx));
    retVal |= Eth_UdmaSciClient_EventrmTranslateCoreIntrInput(
        Eth_GetEventCoreIntrNum(CtrlIdx, EventIdx));
    retVal |= Eth_UdmaSciClient_MasterEventConfig(CtrlIdx, EventIdx);

    return retVal;
}
#endif

Std_ReturnType Udma_RingEvent_Init(
    uint8 CtrlIdx,
    uint8 EventIdx)
{
    return Eth_UdmaSciClient_RingEventConfig(CtrlIdx, EventIdx,
        Eth_GetRingEventEventIdx(CtrlIdx, EventIdx));
}

Std_ReturnType Udma_MasterEvent_Release(
    uint8 CtrlIdx,
    uint8 EventIdx)
{
    return Eth_UdmaSciClient_MasterEventRelease(CtrlIdx, EventIdx);
}

Std_ReturnType Udma_RingEvent_Release(
    uint8 CtrlIdx,
    uint8 EventIdx)
{
    return Eth_UdmaSciClient_RingEventRelease(CtrlIdx, EventIdx,
        Eth_GetRingEventEventIdx(CtrlIdx, EventIdx));
}

Std_ReturnType Udma_MasterEvent_Disable(
    uint8 CtrlIdx,
    uint8 EventIdx)
{
    return Udma_LL_Event_Disable(Eth_GetEventVirtIntrNum(CtrlIdx, EventIdx));
}

Std_ReturnType Udma_Flow_Enable(
    uint8 CtrlIdx,
    uint8 FlowId)
{
    return Eth_UdmaSciClient_FlowConfig(CtrlIdx, FlowId);
}

Std_ReturnType Udma_Ring_Init(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    Std_ReturnType retVal = E_OK;

    retVal |= Eth_UdmaSciClient_RingCfg(CtrlIdx, RingIdx);
    if(E_OK == retVal)
    {
        Udma_Ring_LL_Init(CtrlIdx, RingIdx);
    }

    return retVal;
}

void Udma_Ring_Reset(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    return Udma_Ring_LL_Reset(CtrlIdx, RingIdx);
}

Std_ReturnType Udma_Ring_Queue(
    uint8 CtrlIdx,
    uint8 RingIdx, uint64 phyDescMem)
{
    return Udma_Ring_LL_Queue(CtrlIdx, RingIdx, phyDescMem);
}

Std_ReturnType Udma_Ring_DeQueue(
    uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 *phyDescMem)
{
    return Udma_Ring_LL_Dequeue(CtrlIdx, RingIdx, phyDescMem);
}

Std_ReturnType Udma_Ring_Flush(
    uint8 CtrlIdx,
    uint8 RingIdx,
    uint64 *phyDescMem)
{
    return Udma_Ring_LL_Flush(CtrlIdx, RingIdx, phyDescMem);
}

uint32 Udma_Ring_ReadOccNum(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    return Udma_Ring_LL_ReadOccNum(CtrlIdx, RingIdx);
}

uint32 Udma_Ring_WriteOccNum(
    uint8 CtrlIdx,
    uint8 RingIdx)
{
    return Udma_Ring_LL_WriteOccNum(CtrlIdx, RingIdx);
}
