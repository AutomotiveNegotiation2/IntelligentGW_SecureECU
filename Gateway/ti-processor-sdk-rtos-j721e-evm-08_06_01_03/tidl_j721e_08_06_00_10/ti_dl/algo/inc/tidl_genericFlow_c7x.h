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
 *  \file tidl_genericFlow_c7x.h
 *
 *  \brief This file defines the function prototypes for generic flow
 */

#ifndef TIDL_GENERIC_FLOW_C7X_H_
#define TIDL_GENERIC_FLOW_C7X_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tidl_alg_int.h"
#include "tidl_commonUtils.h"
#include "tidl_generic_datatypes.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MAX_MEM_PER_DRU_CHANNEL  (0xFFFFU)
#define TIDL_INVALID_CHANNEL     (-1)
#define TIDL_GENFLOW_MAX_IN_CH (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* Below structure is for old generic flow, so it will be removed eventually */
typedef struct
{
  int32_t deviceName; /* Device for which the network is working */
  int32_t numInputs;
  int32_t numPingPongs;
  int32_t memReqPerChPerInput;
  int32_t numChPerTrigPerInput; /* No. of channels brought per transfer trigger for each input */
  int32_t numChPerInput; /* Number of channels in each input */
  int32_t pingPongOffset; /* Offset for ping-pong buffers */
  int64_t inputSeparationOffset; /* Uniform offset between adjacent inputs */
  int32_t buffInputBlockOffset; /* When fetching multiple inputs, the offset between two blocks in buffer */
  int32_t outTriggerJumpOffset;
  int32_t numOutChunks;
  int32_t inTriggerJumpOffset;
  int32_t inTriggerJumpOffsets[TIDL_GENFLOW_MAX_IN_CH];
  int32_t numKernelCalls;
  int32_t inChPitch[TIDL_GENFLOW_MAX_IN_CH];
  TIDL_ExecInArgs exec_in_args;
  TIDL_ExecOutArgs exec_out_args;
} TIDL_GenericFlowHandleOld;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Dummy API for REF_ONLY mode to avoid PDK dependency */

#include "dmautils_ext.h"


void TIDL_setTensorProperties(TIDL_TensorTransferInfo *pTensorInfo,
                              sTIDL_DataParams_t *dataParams,
                              eTensorType tensorType,
                              int32_t planeSize,
                              int32_t elementType,
                              int32_t lfmJump);
int32_t TIDL_getGenericOutChPitch(const TIDL_GenericHandle *genericHandlePtr,
                                  const sDataFlowInfo_t *dataFlowInfo,
                                  int32_t outChPitch);
int32_t TIDL_genericFlowInit(sDataFlowInfo_t   *dataFlowInfo,
                            TIDL_GenericHandle  *genericHandlePtr,
                            int32_t  numInTensors,
                            int32_t  numOutTensors,
                            sTIDL_DataParams_t *inputDataParams[],
                            sTIDL_DataParams_t *outputDataParams,
                            int32_t  procElemSizeInBytes,
                            int32_t  inPlaneSize,
                            int32_t  outPlaneSize,
                            int32_t  jumpReduction,
                            int32_t  disableMSMCstaging,
                            int32_t disableMixedPrecision
                            );
int32_t TIDL_genericFlowProcess(
                         //Tensors:
                         void *inPtr[],
                         void *outPtr,
                         void *paramPtrs[],
                         //Information Structures
                         TIDL_KernelHandle kerHandle,
                         TIDL_GenericHandle  *genericHandlePtr,
                         sDataFlowInfo_t *dataFlowInfo,
                         //Profiling Data
                         TIDL_LayerMetaData *metaData,
                         //System Scratch Pointer
                         TIDL_sysScratchPtr *sysScratchPtr,
                         void *dmaUtilsContext
                         );

int32_t TIDL_genericColFlowOld(const sTIDL_DataParams_t *inputTensorParams,
                               sDataFlowInfo_t *dataFlowInfo,
                               void *inPtr,
                               void *outPtr,
                               sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX],
                               TIDL_LayerMetaData *metaData,
                               TIDL_sysScratchPtr *sysScratchPtr,
                               void *dmaUtilsContext,
                               TIDL_KernelHandle handle,
                               TIDL_GenericFlowHandleOld *flowHandle,
                               TIDL_genericExecFuncPtr fxnPtr,
                               TIDL_bufParams3D_t writeAddrObj);
/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#endif /* TIDL_GENERIC_FLOW_C7X_H_*/
