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
 *  \file     Udma_Sciclient.h
 *
 *  \brief    This file contains Udma Sciclient function declarations.
 */


#ifndef UDMA_SCICLIENT_H_
#define UDMA_SCICLIENT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief UDMA Sciclient configure ring function
 *
 *  Configure sciclient for ring via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param ringIdx  Ring Idx
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_RingCfg(
    uint8 ctrlIdx,
    uint8 ringIdx);

/**
 *  \brief UDMA Sciclient configure rx channel pair function
 *
 *  Configure rx channel pair via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param chIdx    Channel index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_RxChannelPair(
    uint8 ctrlIdx,
    uint8 chIdx);

/**
 *  \brief UDMA Sciclient configure tx channel pair function
 *
 *  Configure tx channel pair via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param chIdx    Channel index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_TxChannelPair(
    uint8 ctrlIdx,
    uint8 chIdx);

/**
 *  \brief UDMA Sciclient configure tx channel unpair function
 *
 *  Configure tx channel unpair via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param chIdx    Channel index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_TxChannelUnPair(
    uint8 ctrlIdx,
    uint8 chIdx);

/**
 *  \brief UDMA Sciclient configure rx channel unpair function
 *
 *  Configure rx channel unpair via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param chIdx    Channel index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_RxChannelUnPair(
    uint8 ctrIdx,
    uint8 chIdx);

/**
 *  \brief UDMA Sciclient configure tx channel function
 *
 *  Configure tx channel
 *
 *  \param ctrlIdx  Controller Idx
 *  \param chIdx    Channel index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_TxChannelConfig(
    uint8 ctrlIdx,
    uint8 chIdx);

/**
 *  \brief UDMA Sciclient configure rx channel function
 *
 *  Configure rx channel via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param chIdx    Channel index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_RxChannelConfig(
    uint8 ctrlIdx,
    uint8 chIdx);

/**
 *  \brief UDMA Sciclient configure flow
 *
 *  Configure UDMA flow via Sciclient
 *
 *  \param ctrlIdx  Controller Idx
 *  \param FlowId     Flow index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_FlowConfig(
    uint8 ctrlIdx,
    uint8 flowIdx);

#if (ETH_DMA_IR_SUPPORT == STD_ON)
/**
 *  \brief UDMA Sciclient translate core interrupt IR intput
 *
 *  Translate core interrupt intput via Sciclient
 *
 *  \param EventId    Event index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_EventrmTranslateIrOutput(uint32 irIntrId);

/**
 *  \brief UDMA Sciclient translate core interrupt intput
 *
 *  Translate core interrupt intput via Sciclient
 *
 *  \param EventId    Event index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_EventrmTranslateCoreIntrInput(uint32 coreIntr);
#endif

/**
 *  \brief UDMA Sciclient configure master event function
 *
 *  Configure master event via Sciclient
 *
 *  \param ctrlIdx   controller index
 *  \param eventIdx  master event index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_MasterEventConfig(uint8 ctrlIdx,
    uint8 eventIdx);

/**
 *  \brief UDMA Sciclient configure sub event function
 *
 *  Configure sub event via Sciclient
 *
 *  \param ctrlIdx   controller index
 *  \param eventIdx  ringEventIdx ring event index
 *  \param masterEventIdx     master event index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_RingEventConfig(uint8 ctrlIdx,
    uint8 ringEventIdx,
    uint8 masterEventIdx);

/**
 *  \brief UDMA Sciclient release master event function
 *
 *  Release master event via Sciclient
 *
 *  \param ctrlIdx   controller index
 *  \param eventIdx  master event index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_MasterEventRelease(uint8 ctrlIdx,
    uint8 eventIdx);

/**
 *  \brief UDMA Sciclient release sub event function
 *
 *  Release sub event via Sciclient
 *
 *  \param ctrlIdx   controller index
 *  \param eventIdx  ringEventIdx ring event index
 *  \param masterEventIdx     master event index
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType Eth_UdmaSciClient_RingEventRelease(uint8 ctrlIdx,
    uint8 ringEventIdx,
    uint8 masterEventIdx);

#ifdef __cplusplus
}
#endif

#endif /* UDMA_SCICLIENT_H_ */
