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
 *  \file tidl_pooling.h
 *
 *  \brief This file defines the process function prototype of pooling layer
 */

#ifndef TIDL_POOLING_H_
#define TIDL_POOLING_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tidl_alg_int.h"
#include "itidl_ti.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 @struct  TIDL_SpatialPoolingBuffParams_t
 @brief   This structure contains buffer parameters used for transferring input
          from external memory to internal memory for computation and for
          transferring output from internal memory to external memory after
          computation.

 @params  inWidth
          Width of input data pointer in external memory.

 @params  inHeight
          Height of input data pointer in external memory.

 @params  inPitch
          Pitch of input data in external memory.

 @params  outPitch
          Pitch of output data in external memory.

 @params  inChPitch
          Channel Pitch of input data in external memory. It contains the size
          of one complete channel data.

 @params  outChPitch
          Channel Pitch of output data in external memory. It contains the size
          of one complete channel output data.

 @params  scaleValue
          scaleValue used for reciprocal multiplication in Average pooling
          operations.

 @params  roundBits
          Round bits used for final output in pooling operations.

 @params  inElementType
          Indicates the type of input as signed or unsigned.

 @param  scratchSize
         Size of scratch memory.

 @param  scratchMem
         Pointer to the scratch memory.
*/
typedef struct {
  int32_t inWidth;
  int32_t inHeight;
  int32_t inPitch;
  int32_t outPitch;
  int32_t inChPitch;
  int32_t outChPitch;
  int32_t scaleValue;
  int32_t biasTerm;
  uint8_t mmaShift;
  int32_t roundBits;
  int32_t inElementType;
  int32_t outElementType;
  int32_t scratchSize;
  void *scratchMem;
} TIDL_SpatialPoolingBuffParams_t;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* None */
int32_t TIDL_getPoolingKernelHandleSize(sTIDL_Layer_t *tidlLayer, int32_t numSubHandles);
int32_t TIDL_getPoolingFeaturePlaneSize(const TIDL_CreateParams *createParams,
                                        sTIDL_Layer_t *tidlLayer,
                                        int32_t inHeight);
int32_t TIDL_poolingKernelInit(const TIDL_CreateParams *createParams,
                                sTIDL_AlgLayer_t     *algLayer,
                                sTIDL_Layer_t        *tidlLayer,
                                int32_t              procType,
                                int32_t              inHeight,
                                int32_t              outHeight,
                                sTIDL_virtualPad    *virtualPad
                                );
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 ----------------------------------------------------------------------------
 @ingroup    TIDL_Pppling
 @fn         TIDL_poolingProcess
 @brief      Spatial pooling operation currently supports max pooling and
             average pooling.
             Max pooling/Average pooling kernel can have Kernel Width and
             Kernel Height in any combination of MxN (where M,N = 2 to 9).
             Horizontal skip or stride value is limited to 2 only. Vertical
             skip or stride can have values 2 or 4.
             Average operation in average pooling is performed through shift
             value(outDataQ) given to the kernel.

 @param      algLayer : Ptr Common Layer parameters and other layer parameters.
 @param      tidlLayer: Ptr to Spatial Pooling layer parameters which includes
                         input, output buffer pointers also.
 @param      inPtrs: Ptr array to input buffers  in external memory.
 @param      outPtrs: Ptr to output buffer in external memory.
 @param      sysMems: Structure Ptr to internal memory buffers.
 @remarks    None
 @return     status =>  0: PASS; Anything else: FAIL
 ----------------------------------------------------------------------------
*/
int32_t TIDL_poolingProcess(TIDL_Handle          intAlgHandle,
                            sTIDL_AlgLayer_t     *algLayer,
                            sTIDL_Layer_t        *tidlLayer,
                            void                 *inPtrs[],
                            void                 *outPtrs[],
                            sTIDL_sysMemHandle_t *sysMems);

int32_t TIDL_poolingDspProcess(TIDL_Handle        intAlgHandle,
                            sTIDL_AlgLayer_t     *algLayer,
                            sTIDL_Layer_t        *tidlLayer,
                            void                 *inPtrs[],
                            void                 *outPtrs[],
                            sTIDL_sysMemHandle_t *sysMems);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#endif /* TIDL_POOLING_H_*/

