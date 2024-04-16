/*
*
* Copyright (c) {2015 - 2020} Texas Instruments Incorporated
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
 ----------------------------------------------------------------------------
 @file    tidl_priv_algo.h
 @brief   This file defines APIS for TIDL Private algorithms.
 @version 0.1 (Mar 2020) : Intial Version
 ----------------------------------------------------------------------------
*/

#ifndef ITIDL_PRIVALGO_H
#define ITIDL_PRIVALGO_H
#include "tidl_alg_int.h"

/**
 ----------------------------------------------------------------------------
 @ingroup    TIDL_PRIV_ALGO
 @fn         TIDL_privGetContextSize
 @brief      Function to get context memory size required for Provate algorithm.
 @param      None
 @remarks    None
 @return     Context memory Size in bytes 
 ----------------------------------------------------------------------------
*/

int32_t TIDL_privGetContextSize(void);



int32_t TIDL_privGetLayerToProcess(TIDL_Handle intAlgHandle, void *privHandle, int32_t *layerIdx, int32_t *algLayerIdx);


int32_t TIDL_privAlgoLayerProcess(
    TIDL_Handle intAlgHandle,
    sTIDL_AlgLayer_t *algLayer,
    sTIDL_Layer_t *TIDLLayer,
    void *inPtrs[],
    void *outPtrs[],
    sTIDL_sysMemHandle_t *sysMems,
    int32_t i,
    void *privContext,
    int32_t targetDevice);

int32_t TIDL_privAlgoHandlInit(TIDL_Handle intAlgHandle, void *privHandle);
int32_t TIDL_getInProcHeight(int32_t outTileHeight, sTIDL_Layer_t *currentLayer, int32_t calcTileHeight, int32_t targetDevice);
int32_t TIDL_privUpdateFeatMapSize(sPerfSim_t * perfInfoOut, int32_t i, int32_t outFeatMapSize);
int32_t TIDL_privGetNumHandles(const sDataFlowInfo_t *dataFlowInfo);
void TIDL_privGetInProcSize(const sDataFlowInfo_t * dataFlowInfo, int32_t i, sTIDL_Layer_t *currentLayer, int32_t * width, int32_t * height, int32_t targetDevice);
void TIDL_privGetOutProcSize(const sDataFlowInfo_t *dataFlowInfo, int32_t i, sTIDL_Layer_t *currentLayer, int32_t *width, int32_t *height, int32_t targetDevice);
int32_t TIDL_privGetProcType(const sDataFlowInfo_t *dataFlowInfo);

/**
 ----------------------------------------------------------------------------
 @ingroup    TIDL_PRIV_ALGO
 @fn         TIDL_privGetProcType
 @brief      Function to get Processing type for a given layer.
 @param      intAlgHandle - Internal algorithm hadnle
 @param      i - Current layer index
 @remarks    None
 @return     0 0r 1 
 ----------------------------------------------------------------------------
*/
int32_t TIDL_privGetCurrProcType(TIDL_Handle intAlgHandle, int32_t i);
void TIDL_privGetContextMemBaseAndSize(sDataFlowInfo_t * dataFlowInfo, int32_t*contextMemBase, int32_t*contextMemSize);
#endif /* ITIDL_PRIVALGO_H*/

