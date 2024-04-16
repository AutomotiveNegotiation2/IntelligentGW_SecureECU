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
 *  \file tidl_pooling.c
 *
 *  \brief This file defines kernel functions for pooling layer
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "tidl_alg_int.h"
#include "tidl_pooling.h"
#include "tidl_commonUtils.h"
#include "tidl_alg_utils.h"
#include <limits>
#include "math.h"
#include "tidl_device_functions.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TIDL_POOLING_PREDICATE_BUFF_SIZE                 (9U*1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/**
 * @brief  This is the reference implementation for global max pooling
 *
 * @param pInChannel : pointer to the input data buffer
 * @param width  : width of the input data buffer
 * @param height : height of the input data buffer
 * @param inPitch : pitch of the input data buffer
 * @param inChPitch : Channel pitch of the input data buffer
 * @param outChPitch : Channel pitch of the output data buffer
 * @param numOutChannels : no of output channels
 * @param initValue : initial value for Max operation
 * @param pOutChannel : Pointer to output data buffer
 * @param tidlLayer : Pointer to the common layer parameters
 */
template <class Tin>
static void TIDL_refGlobalMaxPooling(Tin *pInChannel,
                                     int32_t width,
                                     int32_t height,
                                     int32_t inPitch,
                                     int32_t inChPitch,
                                     int32_t outChPitch,
                                     int32_t numOutChannels,
                                     Tin *pOutChannel,
                                     const sTIDL_Layer_t *tidlLayer,
                                     sTIDL_DataParams_t *inDataParams)
{
  Tin input;
  Tin maxValue;
  int32_t i0, i1, i2, i3;
  int32_t numBatches     = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  
  Tin *inData = (Tin *)pInChannel + (inDataParams->padH * inPitch) + inDataParams->padW;
  Tin *outData = (Tin *)pOutChannel + (tidlLayer->outData.padH* tidlLayer->outData.pitch[TIDL_LINE_PITCH]) + tidlLayer->outData.padW;
  Tin initValue = std::numeric_limits<Tin>::lowest();

  for(i0=0; i0<numBatches; i0++)
  {
  for(i1=0; i1<numOutChannels; i1++)
  {
    maxValue = (Tin)initValue;
    for(i2=0; i2<height; i2++)
    {
      for(i3=0; i3<width; i3++)
      {
        input = inData[(i0*inBatchPitch) + (i1*inChPitch) + (i2*inPitch) + i3];
        /* Max pooling operations */
        maxValue = (maxValue>input) ? maxValue : input;
      }
    }
    outData[(i0*outBatchPitch) + i1*outChPitch] = maxValue;
  }
  }
}


template <class Tin, class Tout, class Tacc, class Tscale>
static int32_t TIDL_refGlobalAvgPoolingv2(TIDL_Handle intAlgHandle,
                                        Tin  *pInChannel,
                                        int32_t width,
                                        int32_t height,
                                        int32_t inPitch,
                                        int32_t inChPitch,
                                        int32_t outChPitch,
                                        int32_t numOutChannels,
                                        Tout *pOutChannel,
                                        Tacc *accPtr,
                                        Tscale  scaleValue,
                                        int32_t biasTerm,
                                        uint8_t mmaShift,
                                        const sTIDL_AlgLayer_t *algLayer,
                                        const sTIDL_Layer_t *tidlLayer,
                                        sTIDL_DataParams_t *inDataParams)
{
  sTIDL_Network_t *net = intAlgHandle->createParams->net;
  Tacc inRowCol;
  int32_t i0, i1, i2, i3;
  int32_t numBatches     = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  
  Tacc sumBlock;
  Tacc result;
  Tin *inData = (Tin *)pInChannel + (inDataParams->padH * inPitch) + inDataParams->padW;
  Tout *outData = (Tout *)pOutChannel + (tidlLayer->outData.padH* tidlLayer->outData.pitch[TIDL_LINE_PITCH]) + tidlLayer->outData.padW;

  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;
  int32_t roundBits;
  uint32_t accumulatorSize = (uint32_t)(sizeof(Tacc));
  int32_t accMemSize = numBatches * outBatchPitch *(int32_t)accumulatorSize;

  Tacc min, max;

  max = std::numeric_limits<Tacc>::lowest();
  min = std::numeric_limits<Tacc>::max();

  if(algLayer->scratchSize >= accMemSize)
  {
    accPtr = (Tacc *)algLayer->scratchMem;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refGlobalAvgPooling accumulator is not sufficient exiting...\n");
    status = TIDL_ERR_FAILURE;
  }

  if(TIDL_SUCCESS == status)
  {
    for(i0=0; i0<numBatches; i0++)
    {
      for(i1=0; i1<numOutChannels; i1++)
      {
        sumBlock = 0;
        for(i2=0; i2<height; i2++)
        {
          for(i3=0; i3<width; i3++)
          {
            inRowCol = (Tacc)inData[(i0*inBatchPitch) + (i1* inChPitch) + (i2 * inPitch) + i3];
            sumBlock += inRowCol;
          }
        }
        sumBlock += biasTerm;
        result = sumBlock * scaleValue;
        min = (result<min) ? result : min;
        max = (result>max) ? result : max;
        accPtr[(i0*outBatchPitch) +  (i1*outChPitch)] = result;
      }
    }
  }


  int32_t satLow;
  int32_t satHigh;
  int32_t mixedPrecision = 0;
  int32_t procElemSize;
  Tout temp;
  temp  = std::numeric_limits<Tout>::lowest();
  satLow = (int32_t)temp;
  temp  = std::numeric_limits<Tout>::max();
  satHigh = (int32_t)(temp);
  int64_t tempAcc;
  procElemSize = TIDL_getProcessingElementSizeInBytes(tidlLayer);

  roundBits = net->TIDLLayers[layerIdx].outData.roundBits;
  if ( sizeof(Tout) != procElemSize)
  {
    mixedPrecision = 1;
    /* This is to match with target implementation wherin the saturations
    happens after applying outRoundBits - 8 shift and then the right shift
    of 8 is applied */
    roundBits = roundBits - 8;
    if ( net->TIDLLayers[layerIdx].outData.elementType == TIDL_SignedChar )
    {
      satLow  = std::numeric_limits<int16_t>::lowest();
      satHigh = std::numeric_limits<int16_t>::max();
    }
    else
    {
      satLow  = std::numeric_limits<uint16_t>::lowest();
      satHigh = std::numeric_limits<uint16_t>::max();
    }
  }
  if(TIDL_SUCCESS == status)
  {
    for(i0=0; i0<numBatches; i0++)
    {
    for(i1=0; i1<numOutChannels; i1++)
    {
      result = accPtr[(i0*outBatchPitch) + (i1*outChPitch)];
      if (typeid(Tacc) == typeid(float32_tidl))
      {
        result = TIDL_floatSat(result, &net->TIDLLayers[layerIdx]);
      }
      else
      {
        tempAcc = result;
         /* Rounding and saturation */
        result = (Tacc)TIDL_roundSat((int64_t)tempAcc, mmaShift , (int32_t)satLow, (int32_t)satHigh);
        if ( mixedPrecision == 1)
        {
          result = (int64_t)result >> 8;
        }
      }
      outData[(i0*outBatchPitch) + (i1*outChPitch)] = (Tout)result;
    }
    }
  }

  return status;
}







/**
 * @brief  This is the reference implementation for global average pooling
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param pInChannel : pointer to the input data buffer
 * @param width  : width of the input data buffer
 * @param height : height of the input data buffer
 * @param inPitch : pitch of the input data buffer
 * @param inChPitch : Channel pitch of the input data buffer
 * @param outChPitch : Channel pitch of the output data buffer
 * @param numOutChannels : no of output channels
 * @param pOutChannel : Pointer to output data buffer
 * @param scaleValue : the scale value for the input
 * @param satLow : Min value for the saturation
 * @param satHigh : Max value for the saturation
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tout, class Tacc, class Tscale>
static int32_t TIDL_refGlobalAvgPooling(TIDL_Handle intAlgHandle,
                                        Tin  *pInChannel,
                                        int32_t width,
                                        int32_t height,
                                        int32_t inPitch,
                                        int32_t inChPitch,
                                        int32_t outChPitch,
                                        int32_t numOutChannels,
                                        Tout *pOutChannel,
                                        Tacc *accPtr,
                                        Tscale  scaleValue,
                                        const sTIDL_AlgLayer_t *algLayer,
                                        const sTIDL_Layer_t *tidlLayer,
                                        sTIDL_DataParams_t *inDataParams)
{
  sTIDL_Network_t *net = intAlgHandle->createParams->net;
  Tacc inRowCol;
  int32_t i0, i1, i2, i3;
  int32_t numBatches     = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  
  Tacc sumBlock;
  Tacc result;
  Tin *inData = (Tin *)pInChannel + (inDataParams->padH * inPitch) + inDataParams->padW;
  Tout *outData = (Tout *)pOutChannel + (tidlLayer->outData.padH* tidlLayer->outData.pitch[TIDL_LINE_PITCH]) + tidlLayer->outData.padW;

  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;
  int32_t roundBits;
  uint32_t accumulatorSize = (uint32_t)(sizeof(Tacc));
  int32_t accMemSize = numBatches * outBatchPitch *(int32_t)accumulatorSize;

  Tacc min, max;

  max = std::numeric_limits<Tacc>::lowest();
  min = std::numeric_limits<Tacc>::max();

  if(algLayer->scratchSize >= accMemSize)
  {
    accPtr = (Tacc *)algLayer->scratchMem;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refGlobalAvgPooling accumulator is not sufficient exiting...\n");
    status = TIDL_ERR_FAILURE;
  }

  if(TIDL_SUCCESS == status)
  {
    for(i0=0; i0<numBatches; i0++)
    {
    for(i1=0; i1<numOutChannels; i1++)
    {
      sumBlock = 0;
      for(i2=0; i2<height; i2++)
      {
        for(i3=0; i3<width; i3++)
        {
          inRowCol = (Tacc)inData[(i0*inBatchPitch) + (i1* inChPitch) + (i2 * inPitch) + i3];
          sumBlock += inRowCol;
        }
      }
      result = sumBlock * scaleValue;
      min = (result<min) ? result : min;
      max = (result>max) ? result : max;
      accPtr[(i0*outBatchPitch) +  (i1*outChPitch)] = result;
    }
    }
  }

  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    if(TIDL_getDatElementSign(net->TIDLLayers[layerIdx].outData.elementType) == 1)
    {
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, min, max);
    }
    else
    {
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, max);
    }
  }

  int32_t satLow;
  int32_t satHigh;
  int32_t mixedPrecision = 0;
  int32_t procElemSize;
  Tout temp;

  temp  = std::numeric_limits<Tout>::lowest();
  satLow = (int32_t)temp;
  temp  = std::numeric_limits<Tout>::max();
  satHigh = (int32_t)(temp);

  procElemSize = TIDL_getProcessingElementSizeInBytes(tidlLayer);

  roundBits = net->TIDLLayers[layerIdx].outData.roundBits;
  if ( sizeof(Tout) != procElemSize)
  {
    mixedPrecision = 1;
    /* This is to match with target implementation wherin the saturations
    happens after applying outRoundBits - 8 shift and then the right shift
    of 8 is applied */
    roundBits = roundBits - 8;
    if ( net->TIDLLayers[layerIdx].outData.elementType == TIDL_SignedChar )
    {
      satLow  = std::numeric_limits<int16_t>::lowest();
      satHigh = std::numeric_limits<int16_t>::max();
    }
    else
    {
      satLow  = std::numeric_limits<uint16_t>::lowest();
      satHigh = std::numeric_limits<uint16_t>::max();
    }
  }

  if(TIDL_SUCCESS == status)
  {
    for(i0=0; i0<numBatches; i0++)
    {
    for(i1=0; i1<numOutChannels; i1++)
    {
      result = accPtr[(i0*outBatchPitch) + (i1*outChPitch)];
      if (typeid(Tacc) == typeid(float32_tidl))
      {
        result = TIDL_floatSat(result, &net->TIDLLayers[layerIdx]);
      }
      else
      {
         /* Rounding and saturation */
        result = (Tacc)TIDL_roundSat((int64_t)result, roundBits , (int32_t)satLow, (int32_t)satHigh);

        if ( mixedPrecision == 1)
        {
          result = (int64_t)result >> 8;
        }
      }
      outData[(i0*outBatchPitch) + (i1*outChPitch)] = (Tout)result;
    }
    }
  }

  return status;
}

 /**
 * @brief Global pooling layer reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param tidlLayer : Pointer to the common layer parameters
 * @param algLayer : Pointer to the layer specific parameters
 * @param params : copy of pooling layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param poolingBuffParams : parameters of the pooling buffer
 * @param numBatches : number of total batches
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_refGlobalPoolingProcess(TIDL_Handle intAlgHandle,
                                            sTIDL_Layer_t *tidlLayer,
                                            sTIDL_DataParams_t *inDataParams,
                                            const sTIDL_AlgLayer_t *algLayer,
                                            const sTIDL_PoolingParams_t *params,
                                            void *inPtr,
                                            void *outPtr,
                                            const TIDL_SpatialPoolingBuffParams_t *poolingBuffParams,
                                            int32_t numBatches)
{
  int32_t status = TIDL_SUCCESS;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;

  if(TIDL_MaxPooling == params->poolingType)
  {
    if(poolingBuffParams->inElementType == TIDL_UnsignedChar)
    {
      TIDL_refGlobalMaxPooling((uint8_t*)inPtr,
                               poolingBuffParams->inWidth,
                               poolingBuffParams->inHeight,
                               poolingBuffParams->inPitch,
                               poolingBuffParams->inChPitch,
                               poolingBuffParams->outChPitch,
                               params->numChannels,
                               (uint8_t*)outPtr,
                               tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_SignedChar)
    {
      TIDL_refGlobalMaxPooling((int8_t*)inPtr,
                               poolingBuffParams->inWidth,
                               poolingBuffParams->inHeight,
                               poolingBuffParams->inPitch,
                               poolingBuffParams->inChPitch,
                               poolingBuffParams->outChPitch,
                               params->numChannels,
                               (int8_t*)outPtr,
                               tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_UnsignedShort)
    {
      TIDL_refGlobalMaxPooling((uint16_t*)inPtr,
                               poolingBuffParams->inWidth,
                               poolingBuffParams->inHeight,
                               poolingBuffParams->inPitch,
                               poolingBuffParams->inChPitch,
                               poolingBuffParams->outChPitch,
                               params->numChannels,
                               (uint16_t*)outPtr,
                               tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_SignedShort)
    {
      TIDL_refGlobalMaxPooling((int16_t*)inPtr,
                               poolingBuffParams->inWidth,
                               poolingBuffParams->inHeight,
                               poolingBuffParams->inPitch,
                               poolingBuffParams->inChPitch,
                               poolingBuffParams->outChPitch,
                               params->numChannels,
                               (int16_t*)outPtr,
                               tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_SinglePrecFloat)
    {
      TIDL_refGlobalMaxPooling((float32_tidl *)inPtr,
                               poolingBuffParams->inWidth,
                               poolingBuffParams->inHeight,
                               poolingBuffParams->inPitch,
                               poolingBuffParams->inChPitch,
                               poolingBuffParams->outChPitch,
                               params->numChannels,
                               (float32_tidl*)outPtr,
                               tidlLayer, inDataParams);
    }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  else if(TIDL_AveragePooling == params->poolingType)
  {
    void * accPtr = NULL;
    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      status = TIDL_refGlobalAvgPoolingv2(intAlgHandle,
                                      (int8_t*)inPtr,
                                      poolingBuffParams->inWidth,
                                      poolingBuffParams->inHeight,
                                      poolingBuffParams->inPitch,
                                      poolingBuffParams->inChPitch,
                                      poolingBuffParams->outChPitch,
                                      params->numChannels,
                                      (int8_t*)outPtr,
                                      (int32_t*)accPtr,
                                      (uint8_t)poolingBuffParams->scaleValue,
                                      (int32_t)poolingBuffParams->biasTerm,
                                      (uint8_t)poolingBuffParams->mmaShift,
                                      algLayer,
                                      tidlLayer, inDataParams);
    }
    else
    {
      if(poolingBuffParams->inElementType == TIDL_UnsignedChar)
      {
        if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint8_t*)outPtr,
                                          (uint32_t*)accPtr,
                                          (uint32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int8_t*)outPtr,
                                          (int32_t*)accPtr,
                                          (int32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint16_t*)outPtr,
                                          (uint64_t*)accPtr,
                                          (uint64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int16_t*)outPtr,
                                          (int64_t*)accPtr,
                                          (int64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else
        {
          status = TIDL_ERR_FAILURE;
        }
      }
      else if(poolingBuffParams->inElementType == TIDL_SignedChar)
      {
        if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint8_t*)outPtr,
                                          (uint32_t*)accPtr,
                                          (uint32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int8_t*)outPtr,
                                          (int32_t*)accPtr,
                                          (int32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint16_t*)outPtr,
                                          (uint64_t*)accPtr,
                                          (uint64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int8_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int16_t*)outPtr,
                                          (int64_t*)accPtr,
                                          (int64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else
        {
          status = TIDL_ERR_FAILURE;
        }
      }
      else if(poolingBuffParams->inElementType == TIDL_UnsignedShort)
      {
        if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint8_t*)outPtr,
                                          (uint32_t*)accPtr,
                                          (uint32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int8_t*)outPtr,
                                          (int32_t*)accPtr,
                                          (int32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint16_t*)outPtr,
                                          (uint64_t*)accPtr,
                                          (uint64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (uint16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int16_t*)outPtr,
                                          (int64_t*)accPtr,
                                          (int64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else
        {
          status = TIDL_ERR_FAILURE;
        }
      }
      else if(poolingBuffParams->inElementType == TIDL_SignedShort)
      {
        if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint8_t*)outPtr,
                                          (uint32_t*)accPtr,
                                          (uint32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedChar)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int8_t*)outPtr,
                                          (int32_t*)accPtr,
                                          (int32_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (uint16_t*)outPtr,
                                          (uint64_t*)accPtr,
                                          (uint64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else if (poolingBuffParams->outElementType == TIDL_SignedShort)
        {
          status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (int16_t*)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (int16_t*)outPtr,
                                          (int64_t*)accPtr,
                                          (int64_t)poolingBuffParams->scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
        }
        else
        {
          status = TIDL_ERR_FAILURE;
        }
      }
      else if(poolingBuffParams->inElementType == TIDL_SinglePrecFloat)
      {
        float32_tidl scaleValue = (float32_tidl)(1.0)/(poolingBuffParams->inWidth * poolingBuffParams->inHeight);
        status = TIDL_refGlobalAvgPooling(intAlgHandle,
                                          (float32_tidl *)inPtr,
                                          poolingBuffParams->inWidth,
                                          poolingBuffParams->inHeight,
                                          poolingBuffParams->inPitch,
                                          poolingBuffParams->inChPitch,
                                          poolingBuffParams->outChPitch,
                                          params->numChannels,
                                          (float32_tidl*)outPtr,
                                          (float32_tidl*)accPtr,
                                          scaleValue,
                                          algLayer,
                                          tidlLayer, inDataParams);
      }
    }
  }
  else
  {
    status = TIDL_ERR_FAILURE;
  }
  TIDL_enableL1DandL2CacheWb();
  return status;
}

/**
 * @brief  This is the reference implementation for spatial max pooling
 *
 * @param net : the network structure
 * @param pInChannel : pointer to the input data buffer
 * @param width  : width of the input data buffer
 * @param height : height of the input data buffer
 * @param inPitch : pitch of the input data buffer
 * @param inChPitch : Channel pitch of the input data buffer
 * @param outChPitch : Channel pitch of the output data buffer
 * @param numOutChannels : no of output channels
 * @param kernelW : width of the kernel
 * @param kernelH : height of the kernel
 * @param strideW : stride in width dimension
 * @param strideH : stride in height dimension
 * @param padW : Pad in width dimension
 * @param padH : Pad in height dimension
 * @param initValue : initial value for Max operation
 * @param pOutChannel : Pointer to output data buffer
 * @param tidlLayer : Pointer to the common layer parameters
 */
template <class Tin>
static void TIDL_refSpatialMaxPooling(sTIDL_Network_t *net,
                                      Tin *pInChannel,
                                      int32_t startRowNumberInTensor,
                                      int32_t orgInTensorHeight,
                                      int32_t width,
                                      int32_t height,
                                      int32_t inPitch,
                                      int32_t inChPitch,
                                      int32_t outChPitch,
                                      int32_t numOutChannels,
                                      int32_t kernelW,
                                      int32_t kernelH,
                                      int32_t strideW,
                                      int32_t strideH,
                                      int32_t padW,
                                      int32_t padH,
                                      Tin *pOutChannel,
                                      const sTIDL_Layer_t *tidlLayer,
                                      sTIDL_DataParams_t *inDataParams)
{
  Tin inRowCol;
  int32_t i0, i1, i2, i3, i4, i5;
  Tin maxValue;
  int32_t outPitch = tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  int32_t numBatches     = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  
  Tin *inData = (Tin *)pInChannel + ((inDataParams->padH - padH) * inPitch) + (inDataParams->padW - padW);
  Tin *outData = (Tin *)pOutChannel + ((tidlLayer->outData.padH)* tidlLayer->outData.pitch[TIDL_LINE_PITCH]) + (tidlLayer->outData.padW);

  Tin initValue = std::numeric_limits<Tin>::lowest();

  int32_t isBorderPixel;
  int32_t validPosXMin,validPosXMax,validPosYMin,validPosYMax;
  int32_t batchOffset, channelOffset, spatialOffsetY, spatialOffsetX;
  //Setting the parameters marking for pixels on borders
  validPosXMin = padW;
  validPosXMax = padW + width;
  validPosYMin = padH;
  validPosYMax = padH + orgInTensorHeight;

  for (i0=0; i0 < numBatches; i0++)
  {
  for(i1=0; i1<numOutChannels; i1++)
  {
    int32_t numRows,numCols;
    numRows = tidlLayer->outData.dimValues[TIDL_DIM_HEIGHT];
    numCols = tidlLayer->outData.dimValues[TIDL_DIM_WIDTH];
    for(i2=0; i2<numRows; i2++)
    {
      for(i3=0; i3<numCols; i3++)
      {
        maxValue = initValue;
        for(i4=0; i4<kernelH; i4++)
        {
          for(i5=0; i5<kernelW; i5++)
          {
            //For better readability, we segregate the below formula of inRowCol calculation into respestive spatial dimensions
            //channelOffset - for pixels in Channel dimesion
            //spatialOffsetY - for offset in height dimension,this is not multiplying with inPitch.
            //spatialOffsetX - for offset in widhth dimension
            //inRowCol = inData[(i1*inChPitch) + (((i2*strideH) + i4) * inPitch) + (i3*strideW) + i5];
            batchOffset = i0*inBatchPitch;
            channelOffset = i1*inChPitch;
            spatialOffsetY = (i2*strideH) + i4;
            spatialOffsetX = (i3*strideW) + i5;

            //checking if the current pixels falls in borders
            isBorderPixel = TIDL_checkPixelInPadRegion((spatialOffsetY+startRowNumberInTensor), spatialOffsetX, validPosXMin, validPosXMax, validPosYMin, validPosYMax);
            /*Over write the boarder pixel to not influence the operation */
            if(isBorderPixel)
            {
              inRowCol = initValue;
            }
            else
            {
              inRowCol = inData[batchOffset + channelOffset + (spatialOffsetY*inPitch) + spatialOffsetX];
            }
            /* Max pooling operation */
            maxValue = (maxValue > inRowCol) ? maxValue : inRowCol;
          }
        }
        outData[(i0*outBatchPitch) + (i1*outChPitch) + (i2 * outPitch) + i3] = (Tin)maxValue;
      }
    }
  }
  }
}

/**
 * @brief  This is the reference implementation for spatial average pooling
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param pInChannel : pointer to the input data buffer
 * @param width  : width of the input data buffer
 * @param height : height of the input data buffer
 * @param inPitch : pitch of the input data buffer
 * @param inChPitch : Channel pitch of the input data buffer
 * @param outChPitch : Channel pitch of the output data buffer
 * @param numOutChannels : no of output channels
 * @param kernelW : width of the kernel
 * @param kernelH : height of the kernel
 * @param strideW : stride in width dimension
 * @param strideH : stride in height dimension
 * @param padW : Pad in width dimension
 * @param padH : Pad in height dimension
 * @param pOutChannel : Pointer to output data buffer
 * @param satLow : Min value for the saturation
 * @param satHigh : Max value for the saturation
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tout, class Tacc>
static int32_t TIDL_refSpatialAvgPooling(TIDL_Handle intAlgHandle,
                                         Tin *pInChannel,
                                         int32_t width,
                                         int32_t height,
                                         int32_t inPitch,
                                         int32_t inChPitch,
                                         int32_t outChPitch,
                                         int32_t  numOutChannels,
                                         int32_t  kernelW,
                                         int32_t  kernelH,
                                         int32_t  strideW,
                                         int32_t  strideH,
                                         int32_t  padW,
                                         int32_t  padH,
                                         Tout *pOutChannel,
                                         Tacc *accPtr,
                                         const sTIDL_AlgLayer_t *algLayer,
                                         const sTIDL_Layer_t *tidlLayer,
                                         sTIDL_DataParams_t * inDataParams)
{
  sTIDL_Network_t *net = intAlgHandle->createParams->net;
  Tacc inRowCol;
  int32_t i0, i1, i2, i3, i4, i5;
  Tacc sumBlock;
  Tacc result;
  Tacc scaleValue;
  int32_t outPitch = tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  int32_t numBatches      = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  
  Tin *inData  = (Tin *)pInChannel + ((inDataParams->padH - padH)* inPitch) + (inDataParams->padW - padW);
  Tout *outData = (Tout *)pOutChannel + ((tidlLayer->outData.padH)* tidlLayer->outData.pitch[TIDL_LINE_PITCH]) + (tidlLayer->outData.padW);
  int32_t numRows, numCols, roundVal;

  int32_t isOTFpad = 0;
  int32_t startRowNumberInTensor = algLayer->layerParams.poolParams.startRowNumberInTensor;

  if(TIDL_isPadOTF(net->deviceName)){
    isOTFpad = 1;
  }

  int32_t isBorderPixel;
  int32_t validPosXMin,validPosXMax,validPosYMin,validPosYMax;
  int32_t spatialOffsetY, spatialOffsetX;
  //Setting the parameters marking for pixels on borders
  validPosXMin = padW;
  validPosXMax = padW + width;
  validPosYMin = padH;
  validPosYMax = padH + algLayer->layerParams.poolParams.orgInTensorHeight;

  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;

  int32_t roundBits;
  uint32_t accumulatorSize = (uint32_t)(sizeof(Tacc));
  int32_t accMemSize = numBatches * outBatchPitch*(int32_t)accumulatorSize;

  Tacc min, max;

  max = std::numeric_limits<Tacc>::lowest();
  min = std::numeric_limits<Tacc>::max();


  if(algLayer->scratchSize >= accMemSize)
  {
    accPtr = (Tacc *)algLayer->scratchMem;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refSpatialAvgPooling accumulator is not sufficient exiting...\n");
    status = TIDL_ERR_FAILURE;
  }

  if(TIDL_SUCCESS == status)
  {
    numRows = tidlLayer->outData.dimValues[TIDL_DIM_HEIGHT];
    numCols = tidlLayer->outData.dimValues[TIDL_DIM_WIDTH];

    roundVal= algLayer->layerParams.poolParams.internalPoolingWeightQ;
    for (i0=0; i0 < numBatches; i0++)
    {
    for(i1=0; i1<numOutChannels; i1++)
    {
      for(i2=0; i2<numRows; i2++)
      {
        for(i3=0; i3<numCols; i3++)
        {
          /*  BVLC caffe doesn't assume the values of invalid inputs as zero whereas this reference implementation assumes that invalid pixels
           *  belonging to the border have been pre-initialized to 0 before this function is called.
           *  While computing average pooling when the frame boundary is reached the average is computed for only the values inside the frame.
           *  Example: If the pooling size is 9 and at the boundary we only have 6 valid values then
           *  the average computed will be the sum of the 6 valid values divided by the the pooling size which will be 6.
           *  https://github.com/BVLC/caffe/blob/master/src/caffe/layers/pooling_layer.cpp
           */
          int32_t startH    = i2 * strideH;
          int32_t startW    = i3 * strideW;

          int32_t hEndComp  = startH + kernelH;
          int32_t hEndBound = height + padH;
          int32_t endH      = (hEndComp<hEndBound) ? hEndComp : hEndBound;

          int32_t wEndComp  = startW + kernelW;
          int32_t wEndBound = width + padW;
          int32_t endW      = (wEndComp<wEndBound) ? wEndComp: wEndBound;

          /* The values startH, endH, startW, endW contain the boundaries for valid indices.
           * In the following code please note that we compute the average for only the valid indices.
           */
          int32_t poolSize  = (endH - startH) * (endW - startW);

          sumBlock = 0;
          for(i4=startH; i4<endH; i4++)
          {
            for(i5=startW; i5<endW; i5++)
            {
              spatialOffsetY = i4;
              spatialOffsetX = i5;
              isBorderPixel = TIDL_checkPixelInPadRegion(spatialOffsetY+startRowNumberInTensor, spatialOffsetX, validPosXMin, validPosXMax, validPosYMin, validPosYMax);
              if(isBorderPixel & isOTFpad)
              {
                inRowCol = 0;
              }
              else{
                inRowCol = (Tacc)inData[(i0*inBatchPitch) + (i1* inChPitch) + (i4 * inPitch) + i5];
              }            
              sumBlock += inRowCol;
            }
          }
          if (typeid(Tacc) == typeid(float32_tidl))
          {
            scaleValue = 1.0 / poolSize;
          }
          else
          {
            scaleValue = ((int32_t)1 << roundVal) / (poolSize);
          }
          result = sumBlock * scaleValue;
          min = (result<min) ? result : min;
          max = (result>max) ? result : max;

          accPtr[(i0*outBatchPitch) + (i1 * outChPitch) + (i2 * outPitch) + i3] = result;
        }
      }
    }
    }
  }

  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    if(TIDL_getDatElementSign(net->TIDLLayers[layerIdx].outData.elementType) == 1)
    {
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, min, max);
    }
    else
    {
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, max);
    }
  }

  roundBits = net->TIDLLayers[layerIdx].outData.roundBits;

  int32_t satLow;
  int32_t satHigh;
  int32_t mixedPrecision = 0;
  int32_t procElemSize;
  Tout temp;
  temp  = std::numeric_limits<Tout>::lowest();
  satLow = (int32_t)temp;
  temp  = std::numeric_limits<Tout>::max();
  satHigh = (int32_t)(temp);

  procElemSize = TIDL_getProcessingElementSizeInBytes(tidlLayer);


  if ( sizeof(Tout) != procElemSize)
  {
    mixedPrecision = 1;
    /* This is to match with target implementation wherin the saturations
    happens after applying outRoundBits - 8 shift and then the right shift
    of 8 is applied */
    roundBits = roundBits - 8;
    if ( net->TIDLLayers[layerIdx].outData.elementType == TIDL_SignedChar )
    {
      satLow  = std::numeric_limits<int16_t>::lowest();
      satHigh = std::numeric_limits<int16_t>::max();
    }
    else
    {
      satLow  = std::numeric_limits<uint16_t>::lowest();
      satHigh = std::numeric_limits<uint16_t>::max();
    }
  }

  if(TIDL_SUCCESS == status)
  {
    for (i0=0; i0<numBatches; i0++)
    {    
    for(i1=0; i1<numOutChannels; i1++)
    {
      for(i2=0; i2<numRows; i2++)
      {
        for(i3=0; i3<numCols; i3++)
        {
          result = accPtr[(i0 * outBatchPitch) + (i1 * outChPitch) + (i2 * outPitch) + i3];
          min = (result<min) ? result : min;
          max = (result>max) ? result : max;
          if (typeid(Tacc) == typeid(float32_tidl))
          {
            result = TIDL_floatSat(result, &net->TIDLLayers[layerIdx]);
          }
          else
          {
            result = (Tacc)TIDL_roundSat((int64_t)result, roundBits , (int32_t)satLow, (int32_t)satHigh);
            if ( mixedPrecision == 1 )
            {
              result = (int64_t)result >> 8;
            }
          }
          outData[(i0 * outBatchPitch) + (i1 * outChPitch) + (i2 * outPitch) + i3] = (Tout)result;
        }
      }
    }
    }
  }

  return status;
}


 /**
 * @brief Spatial pooling layer reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param tidlLayer : Pointer to the common layer parameters
 * @param algLayer : Pointer to the layer specific parameters
 * @param params : copy of pooling layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param poolingBuffParams : parameters of the pooling buffer
 * @param numBatches : number of total batches
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_refSpatialPoolingProcess(TIDL_Handle intAlgHandle,
                                             sTIDL_Layer_t *tidlLayer,
                                             sTIDL_DataParams_t *inDataParams,
                                             const sTIDL_AlgLayer_t *algLayer,
                                             const sTIDL_PoolingParams_t *params,
                                             void *inPtr,
                                             void *outPtr,
                                             const TIDL_SpatialPoolingBuffParams_t *poolingBuffParams,
                                             int32_t numBatches)
{
  int32_t status = TIDL_SUCCESS;

  if(TIDL_MaxPooling == params->poolingType)
  {
    if(poolingBuffParams->inElementType == TIDL_UnsignedChar)
    {
      TIDL_refSpatialMaxPooling(intAlgHandle->createParams->net,
                                (uint8_t*)inPtr,
                                algLayer->layerParams.poolParams.startRowNumberInTensor,
                                algLayer->layerParams.poolParams.orgInTensorHeight,
                                poolingBuffParams->inWidth,
                                poolingBuffParams->inHeight,
                                poolingBuffParams->inPitch,
                                poolingBuffParams->inChPitch,
                                poolingBuffParams->outChPitch,
                                params->numChannels,
                                params->kernelW,
                                params->kernelH,
                                params->strideW,
                                params->strideH,
                                params->padW,
                                params->padH,
                                (uint8_t*)outPtr,
                                tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_SignedChar)
    {
      TIDL_refSpatialMaxPooling(intAlgHandle->createParams->net,
                                (int8_t*)inPtr,
                                algLayer->layerParams.poolParams.startRowNumberInTensor,
                                algLayer->layerParams.poolParams.orgInTensorHeight,
                                poolingBuffParams->inWidth,
                                poolingBuffParams->inHeight,
                                poolingBuffParams->inPitch,
                                poolingBuffParams->inChPitch,
                                poolingBuffParams->outChPitch,
                                params->numChannels,
                                params->kernelW,
                                params->kernelH,
                                params->strideW,
                                params->strideH,
                                params->padW,
                                params->padH,
                                (int8_t*)outPtr,
                                tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_UnsignedShort)
    {
      TIDL_refSpatialMaxPooling(intAlgHandle->createParams->net,
                                (uint16_t*)inPtr,
                                algLayer->layerParams.poolParams.startRowNumberInTensor,
                                algLayer->layerParams.poolParams.orgInTensorHeight,
                                poolingBuffParams->inWidth,
                                poolingBuffParams->inHeight,
                                poolingBuffParams->inPitch,
                                poolingBuffParams->inChPitch,
                                poolingBuffParams->outChPitch,
                                params->numChannels,
                                params->kernelW,
                                params->kernelH,
                                params->strideW,
                                params->strideH,
                                params->padW,
                                params->padH,
                                (uint16_t*)outPtr,
                                tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_SignedShort)
    {
      TIDL_refSpatialMaxPooling(intAlgHandle->createParams->net,
                                (int16_t*)inPtr,
                                algLayer->layerParams.poolParams.startRowNumberInTensor,
                                algLayer->layerParams.poolParams.orgInTensorHeight,
                                poolingBuffParams->inWidth,
                                poolingBuffParams->inHeight,
                                poolingBuffParams->inPitch,
                                poolingBuffParams->inChPitch,
                                poolingBuffParams->outChPitch,
                                params->numChannels,
                                params->kernelW,
                                params->kernelH,
                                params->strideW,
                                params->strideH,
                                params->padW,
                                params->padH,
                                (int16_t*)outPtr,
                                tidlLayer, inDataParams);
    }
    else if (poolingBuffParams->inElementType == TIDL_SinglePrecFloat)
    {
      TIDL_refSpatialMaxPooling(intAlgHandle->createParams->net,
                                (float32_tidl *)inPtr,
                                algLayer->layerParams.poolParams.startRowNumberInTensor,
                                algLayer->layerParams.poolParams.orgInTensorHeight,
                                poolingBuffParams->inWidth,
                                poolingBuffParams->inHeight,
                                poolingBuffParams->inPitch,
                                poolingBuffParams->inChPitch,
                                poolingBuffParams->outChPitch,
                                params->numChannels,
                                params->kernelW,
                                params->kernelH,
                                params->strideW,
                                params->strideH,
                                params->padW,
                                params->padH,
                                (float32_tidl *)outPtr,
                                tidlLayer, inDataParams);
    }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  else if(TIDL_AveragePooling == params->poolingType)
  {
    void * accPtr = NULL;

    if(poolingBuffParams->inElementType == TIDL_UnsignedChar)
    {
      if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else
      {
        status = TIDL_ERR_FAILURE;
      }
    }
    else if(poolingBuffParams->inElementType == TIDL_SignedChar)
    {
      if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int8_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else
      {
        status = TIDL_ERR_FAILURE;
      }
    }
    else if(poolingBuffParams->inElementType == TIDL_UnsignedShort)
    {
      if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (uint16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else
      {
        status = TIDL_ERR_FAILURE;
      }
    }
    else if(poolingBuffParams->inElementType == TIDL_SignedShort)
    {
      if(poolingBuffParams->outElementType == TIDL_UnsignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedChar)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int8_t*)outPtr,
                                         (int32_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_UnsignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (uint16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else if (poolingBuffParams->outElementType == TIDL_SignedShort)
      {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (int16_t*)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (int16_t*)outPtr,
                                         (int64_t *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
      else
      {
        status = TIDL_ERR_FAILURE;
      }
    }
    else if(poolingBuffParams->inElementType == TIDL_SinglePrecFloat)
    {
        status = TIDL_refSpatialAvgPooling(intAlgHandle,
                                         (float32_tidl *)inPtr,
                                         poolingBuffParams->inWidth,
                                         poolingBuffParams->inHeight,
                                         poolingBuffParams->inPitch,
                                         poolingBuffParams->inChPitch,
                                         poolingBuffParams->outChPitch,
                                         params->numChannels,
                                         params->kernelW,
                                         params->kernelH,
                                         params->strideW,
                                         params->strideH,
                                         params->padW,
                                         params->padH,
                                         (float32_tidl*)outPtr,
                                         (float32_tidl *)accPtr,
                                         algLayer,
                                         tidlLayer, inDataParams);
      }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  TIDL_enableL1DandL2CacheWb();
  return status;
}


/**
 * @brief Pooling layer Process function
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param inPtrs : Pointer to input buffers to be processed
 * @param outPtrs : Pointer to output buffers to be processed
 * @param sysMems : sysMem Handle
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
int32_t TIDL_poolingProcess(TIDL_Handle          intAlgHandle,
                            sTIDL_AlgLayer_t     *algLayer,
                            sTIDL_Layer_t        *tidlLayer,
                            void                 *inPtrs[],
                            void                 *outPtrs[],
                            sTIDL_sysMemHandle_t *sysMems)
{
  int32_t status = TIDL_SUCCESS;
  uint32_t isGlobalPooling = FALSE;
  uint8_t(*inPtr)[]  = (uint8_t(*)[])(inPtrs[0]);
  uint8_t(*outPtr)[] = (uint8_t(*)[])(outPtrs[0]);
  uint32_t flowCtrl = intAlgHandle->createParams->flowCtrl;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;

  sTIDL_PoolingParams_t *params = &tidlLayer->layerParams.poolParams;


  if((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY)
  {
    status = TIDL_poolingDspProcess(intAlgHandle, algLayer, tidlLayer, inPtrs, outPtrs, sysMems);
  }
  else /* ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) */
  {
    if((params->kernelW == 0) && (params->kernelH == 0))
    {
      isGlobalPooling = TRUE;
    }
    if(isGlobalPooling == FALSE)
    {
      sTIDL_DataParams_t *inDataParams;
      inDataParams = TIDL_getDataParams(intAlgHandle->createParams->net, tidlLayer->inData[0]);
      sTIDL_DataParams_t *outDataParams = TIDL_getDataParams(intAlgHandle->createParams->net, tidlLayer->outData.dataId);
      int32_t elementSize = TIDL_getDatElementSize(inDataParams->elementType);
      TIDL_SpatialPoolingBuffParams_t poolingBuffParams;
      poolingBuffParams.inWidth       = inDataParams->dimValues[TIDL_DIM_WIDTH];
      poolingBuffParams.inHeight      = inDataParams->dimValues[TIDL_DIM_HEIGHT];
      poolingBuffParams.inPitch       = inDataParams->pitch[TIDL_LINE_PITCH];
      poolingBuffParams.inChPitch     = inDataParams->pitch[TIDL_CHANNEL_PITCH];
      poolingBuffParams.outPitch      = outDataParams->pitch[TIDL_LINE_PITCH];
      poolingBuffParams.outChPitch    = outDataParams->pitch[TIDL_CHANNEL_PITCH];
      poolingBuffParams.inElementType = inDataParams->elementType;
      poolingBuffParams.outElementType = outDataParams->elementType;
      poolingBuffParams.scaleValue    = 1;
      poolingBuffParams.scratchSize   = algLayer->scratchSize;
      poolingBuffParams.scratchMem    = algLayer->scratchMem;
      params->numChannels = inDataParams->dimValues[TIDL_DIM_NUMCH];
      int32_t numBatches = inDataParams->dimValues[0];
        status = TIDL_refSpatialPoolingProcess(intAlgHandle,
                                                tidlLayer, inDataParams,
                                                algLayer,
                                                params,
                                                (int8_t *)inPtr,
                                                (int8_t *)outPtr,
                                                &poolingBuffParams,
                                                numBatches);
    }
    else /* (isGlobalPooling == TRUE)  */
    {
      sTIDL_DataParams_t *inDataParams;
      inDataParams = TIDL_getDataParams(intAlgHandle->createParams->net, tidlLayer->inData[0]);
      sTIDL_DataParams_t *outDataParams = TIDL_getDataParams(intAlgHandle->createParams->net, tidlLayer->outData.dataId);
      int32_t elementSize = TIDL_getDatElementSize(inDataParams->elementType);
      TIDL_SpatialPoolingBuffParams_t poolingBuffParams;
      poolingBuffParams.inWidth       = inDataParams->dimValues[TIDL_DIM_WIDTH];
      poolingBuffParams.inHeight      = inDataParams->dimValues[TIDL_DIM_HEIGHT];
      poolingBuffParams.inPitch       = inDataParams->pitch[TIDL_LINE_PITCH];
      poolingBuffParams.inChPitch     = inDataParams->pitch[TIDL_CHANNEL_PITCH];
      poolingBuffParams.outPitch      = outDataParams->pitch[TIDL_LINE_PITCH];
      poolingBuffParams.outChPitch    = outDataParams->pitch[TIDL_CHANNEL_PITCH];
      poolingBuffParams.inElementType = inDataParams->elementType;
      poolingBuffParams.outElementType = outDataParams->elementType;

      if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
      {
        poolingBuffParams.inElementType  = 1;
        poolingBuffParams.outElementType = 1;
      }

      poolingBuffParams.scaleValue    = 1;
      poolingBuffParams.scratchSize   = algLayer->scratchSize;
      poolingBuffParams.scratchMem    = algLayer->scratchMem;
      params->numChannels = inDataParams->dimValues[TIDL_DIM_NUMCH];
      if((params->kernelW == 0) && (params->kernelH == 0))
      {
        poolingBuffParams.outChPitch = 1;
        int32_t scaleValueNumInInt = ((int32_t)1 << algLayer->layerParams.poolParams.internalPoolingWeightQ);                        /* Numerator */
        int32_t scaleValueDenInInt = inDataParams->dimValues[3] * inDataParams->dimValues[2]; /* Denominator */
        float32_tidl scaleValueInFloat = (1.0f * (float32_tidl)scaleValueNumInInt)/(float32_tidl)scaleValueDenInInt;
        scaleValueInFloat += 0.5f;
        poolingBuffParams.scaleValue = (int32_t)scaleValueInFloat;
      }
      int32_t numBatches  = inDataParams->dimValues[0];

      if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
      {
        float32_tidl scaleRatio = inDataParams->tensorScale / (tidlLayer->outData.tensorScale * inDataParams->dimValues[3] * inDataParams->dimValues[2]);
        uint8_t mmaScale;
        uint8_t mmaShift;
        TIDL_getMMAv2_ScaleAndShift(scaleRatio, &mmaScale, &mmaShift);
        float32_tidl biasTerm = (tidlLayer->outData.tensorZeroPoint/scaleRatio) - (inDataParams->tensorZeroPoint * inDataParams->dimValues[3] * inDataParams->dimValues[2]);
        poolingBuffParams.biasTerm = round(biasTerm);
        poolingBuffParams.mmaShift = mmaShift;
        poolingBuffParams.scaleValue = mmaScale;
      }

      status = TIDL_refGlobalPoolingProcess(intAlgHandle,
                                            tidlLayer, inDataParams,
                                            algLayer,
                                            params,
                                            (int8_t *)inPtr,
                                            (int8_t *)outPtr,
                                            &poolingBuffParams,
                                            numBatches);
    }
    if((flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if(TIDL_MaxPooling == params->poolingType)
      {
        TIDL_UpdateScaleFactors(intAlgHandle, algLayer->layerIdx, 0, 0, 0);
      }
    }
  }

  return status;
}

