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
 @file    tidl_innerProduct.c
 @brief   This file contains TILD InnerProduct Layer implementation
 @version 0.1 (Jan 2017) : initial version [EPR]
 ----------------------------------------------------------------------------
*/

#include "tidl_innerProduct.h"
#include "tidl_innerProduct_int.h"
#include <math.h>
#include <float.h>
#include "tidl_commonUtils.h"
#include "tidl_innerProduct_mma.h"

/**
 * @brief  This funciton is the core kernel of reference innerProduct
 * 
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param accPtr : pointer to the accumulator buffer
 * @param inPtr : Input pointer on which innerProduct is applied 
 * @param outPtr : Output pointer after innerProduct opreation
 * @param biasPtr  : Pointer to the Bias values 
 * @param weightsPtr : Pointer to weights buffer
 * @param buffParams : parameters of the innerProduct buffer 
 * @param satLow : Min value for the saturation
 * @param satHigh : Max value for the saturation
 */
template <class Tin, class Tw, class Tb, class Tout, class Tacc>
void TIDL_refInnerProduct(
  TIDL_Handle intAlgHandle,
  int32_t layerIdx,
  Tacc*   accPtr,
  Tin*    inPtr,
  Tout*   outPtr,
  Tb*     biasPtr,
  Tw*     weightsPtr,
  tidlInnerProductBuffParams_t  * buffParams,
  int32_t  satLow,
  int32_t  satHigh
  )
{ 
  sTIDL_Network_t * net = intAlgHandle->createParams->net;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  int32_t mmaScale = 1U;
  sTIDL_Layer_t  * tidlLayer = &net->TIDLLayers[layerIdx];
  sTIDL_DataParams_t *inDataParams   = TIDL_getDataParams(net, tidlLayer->inData[0]);
  Tin      *pInData;
  Tw       *pWeightData;
  Tb       *pBiasData;
  int32_t  inIdx, outIdx, chIdx;
  int32_t  roundBits;
  Tacc  sum;

  uint16_t  numBatches      =  buffParams->numTotRoi; 
  uint16_t  numInNodes     =  buffParams->numInNodes; 
  uint16_t  numOutNodes    =  buffParams->numOutNodes;
  uint32_t  inBatchPitch     = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t  outBatchPitch    = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  
  
  Tacc      min, max;
  int32_t   accMemSize = numBatches*outBatchPitch*sizeof(Tacc);
  int64_t   temp;
 
  pBiasData = (Tb *)biasPtr;
  if (buffParams->scratchSize >= accMemSize)
  {
    accPtr = (Tacc *)buffParams->scratchMem;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refInnerProduct accumulator is not sufficient exiting... %d %d \n", buffParams->scratchSize, accMemSize);
    exit(-1);
  }
  min = (Tacc)((((uint64_t)1)<< ((sizeof(Tacc)*8)-1)) - 1);
  temp =(int64_t) (((uint64_t)1) << ((sizeof(Tacc) * 8) - 1));

  max = (Tacc)temp*-1;

  for (chIdx = 0; chIdx < numBatches; chIdx++)
  {

    pInData = ((Tin *)inPtr + (chIdx * inBatchPitch));
    pWeightData = (Tw *)weightsPtr;

    for (outIdx = 0; outIdx < numOutNodes; outIdx++) 
    {

      sum = pBiasData[outIdx];

      for (inIdx = 0; inIdx < numInNodes; inIdx++) 
      {
        /* Multiply input nodes with weights and accumulate */
        sum += pInData[inIdx] * pWeightData[inIdx];
      }
      pWeightData += numInNodes;

      min = sum < min ? sum : min;
      max = sum > max ? sum : max;
      accPtr[(chIdx * outBatchPitch)+outIdx] = sum;
    }
  }

  if(TIDL_QuantStyleAsymNP2_TFL != quantizationStyle)
  {
    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if (TIDL_getDatElementSign(net->TIDLLayers[layerIdx].outData.elementType) == 1)
      {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, min, max);
      }
      else
      {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, max);
      }
    }
    roundBits = net->TIDLLayers[layerIdx].outData.roundBits;
    mmaScale  = 1;
  }
  else
  {
    roundBits = buffParams->mmaShift;
    mmaScale  = buffParams->mmaScale;
  }

  


  int64_t tempAcc;
  for (chIdx = 0; chIdx < numBatches; chIdx++)
  {
    for (outIdx = 0; outIdx < numOutNodes; outIdx++)
    {
      sum = accPtr[(chIdx * outBatchPitch) + outIdx];
      if (tidlLayer -> outData.elementType == TIDL_SinglePrecFloat)
      {
        sum = TIDL_floatSat(sum, &net->TIDLLayers[layerIdx]);
      }
      else
      {
        tempAcc = sum * mmaScale;
        sum = (Tacc)TIDL_roundSat((int64_t)tempAcc, roundBits, satLow, satHigh);
      }
      outPtr[(chIdx * outBatchPitch) + outIdx] = sum;
    }
  }
}
/**
 * @brief  This funciton handles differnt input bit-depths for reference innerProduct
 * 
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param inPtr : Input pointer on which innerProduct is applied 
 * @param refPtr : Output pointer after innerProduct opreation
 * @param biasPtr  : Pointer to the Bias values 
 * @param weightsPtr : Pointer to weights buffer
 * @param accPtr : pointer to the accumulator buffer
 * @param outElementType : elementType of the output
 * @param buffParams : parameters of the innerProduct buffer 
 */
template <class Tw, class Tb, class Tacc>
void TIDL_refInnerProductParamBitDepth(
  TIDL_Handle intAlgHandle,
  int32_t layerIdx,
  void*    inPtr,
  void*    refPtr,
  Tb*     biasPtr,
  Tw*     weightsPtr,
  Tacc*   accPtr,
  int32_t outElementType,
  tidlInnerProductBuffParams_t  * buffParams
  )
{
  int32_t satLow, sathigh;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  if (outElementType == TIDL_SinglePrecFloat)
  {
    sTIDL_Layer_t  * tidlLayer = &intAlgHandle->createParams->net->TIDLLayers[layerIdx];
    float32_tidl minFloat, maxFloat;
    TIDL_getSaturationFloat(tidlLayer, &minFloat, &maxFloat);
    TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (float32_tidl *)inPtr, (float32_tidl *)refPtr, biasPtr, weightsPtr, buffParams, minFloat, maxFloat);
  }

  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    satLow = TIDL_SAT_LO_INT8;
    sathigh = TIDL_SAT_HI_INT8;
    TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int8_t *)inPtr, (int8_t *)refPtr,
      biasPtr, weightsPtr, buffParams, satLow, sathigh);    
  }


  if(TIDL_QuantStyleAsymNP2_TFL != quantizationStyle)
  {
    if ((outElementType == TIDL_SignedChar) || 
        (outElementType == TIDL_SignedShort))  
    {
      if (TIDL_getDatElementSize(outElementType) == 1)
      {
        satLow = TIDL_SAT_LO_INT8;
        sathigh = TIDL_SAT_HI_INT8;
      }
      else
      {
        satLow = TIDL_SAT_LO_INT16;
        sathigh = TIDL_SAT_HI_INT16;
      }
      

      if ((buffParams->inElementType == TIDL_SignedChar) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int8_t *)inPtr, (int8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedChar) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint8_t *)inPtr, (int8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_SignedChar) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int8_t *)inPtr, (int16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedChar) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint8_t *)inPtr, (int16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else  if ((buffParams->inElementType == TIDL_SignedShort) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int16_t *)inPtr, (int8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedShort) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint16_t *)inPtr, (int8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_SignedShort) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int16_t *)inPtr, (int16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedShort) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint16_t *)inPtr, (int16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
    }
    else /* Unsigned output */
    {

      if (TIDL_getDatElementSize(outElementType) == 1)
      {
        satLow = 0;
        sathigh = TIDL_SAT_HI_UINT8;
      }
      else
      {
        satLow = 0;
        sathigh = TIDL_SAT_HI_UINT16;
      }

      if ((buffParams->inElementType == TIDL_SignedChar) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int8_t *)inPtr, (uint8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedChar) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint8_t *)inPtr, (uint8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_SignedChar) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int8_t *)inPtr, (uint16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedChar) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint8_t *)inPtr, (uint16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_SignedShort) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int16_t *)inPtr, (uint8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedShort) && (TIDL_getDatElementSize(outElementType) == 1))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint16_t *)inPtr, (uint8_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_SignedShort) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (int16_t *)inPtr, (uint16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }
      else if ((buffParams->inElementType == TIDL_UnsignedShort) && (TIDL_getDatElementSize(outElementType) == 2))
      {
        TIDL_refInnerProduct(intAlgHandle, layerIdx, accPtr, (uint16_t *)inPtr, (uint16_t *)refPtr,
          biasPtr, weightsPtr, buffParams, satLow, sathigh);
      }

    }
  }

}
 /**
 * @brief InnerProduct layer reference implementation
 * 
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of innerProduct layer parameters
 * @param buffParams : parameters of the innerProduct buffer
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
int32_t TIDL_innerProductRefProcess(
                                  TIDL_Handle          intAlgHandle,
                                  sTIDL_AlgLayer_t     * algLayer, 
                                  sTIDL_Layer_t        * tidlLayer, 
                                  sTIDL_InnerProductParams_t * params,
                                  tidlInnerProductBuffParams_t  * buffParams,
                                  void   *inPtr,  
                                  void   *outPtr 
                                  )
{
  int32_t     i0, status = IALG_EOK;

  //sTIDL_Network_t * net = intAlgHandle->createParams->net;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  int32_t layerIdx = algLayer->layerIdx;
  void * accPtr = NULL;
  void * weightPtr    = ((int8_t *)(intAlgHandle->createParams->net) + params->weights);
  void * orgBiasPtr   = ((int8_t *)(intAlgHandle->createParams->net) + params->bias);
  void * biasPtr;

  if(TIDL_forceInnerProductRef(intAlgHandle->createParams,tidlLayer)){
    //Forced Refrence case. in that case the space to hold weights is from algLayer
    weightPtr   = algLayer->layerParams.innerProductParams.wtTranformMem;
    orgBiasPtr = (void*)get_int8_t_pointer((int8_t *)(weightPtr), params->bias - params->weights);
  }

  float32_tidl * orgBiasPtrFloat = (float32_tidl *)orgBiasPtr;
   
  if (algLayer->layerParams.innerProductParams.biasParamSize >= (params->numOutNodes*sizeof(int16_t)))
  {
    biasPtr = (void *)algLayer->layerParams.innerProductParams.biasParamMem;
  }
  else
  {
    tidl_printf(0,"Memory for  biasptr  is not sufficient exiting...\n    ");
    exit(-1);
  }

  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    int32_t* fBiasPtr = (int32_t*)algLayer->layerParams.innerProductParams.biasParamMem; //Txed bias
    TIDL_refInnerProductParamBitDepth(intAlgHandle, layerIdx, inPtr, outPtr, (int32_t *)fBiasPtr, (int8_t *)weightPtr, (int32_t*)accPtr, tidlLayer->outData.elementType, buffParams);
  }
  else
  {
    if (tidlLayer->weightsElementSizeInBits <= 8)
    {
      if (params->biasScale != -1)
      {
        TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int16_t*)biasPtr, &buffParams->biasB, params->numOutNodes, buffParams->inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF, TIDL_getDatElementSign(buffParams->inElementType));
      }
      for (i0 = 0; i0 < params->numOutNodes; i0++)
      {
        ((int16_t*)biasPtr)[i0] = ((int16_t*)biasPtr)[i0] * buffParams->biasB;
      }

      TIDL_refInnerProductParamBitDepth(intAlgHandle, layerIdx, inPtr, outPtr, (int16_t *)biasPtr, (int8_t *)weightPtr, (int32_t*)accPtr, tidlLayer->outData.elementType, buffParams);
    }
    else if (tidlLayer->weightsElementSizeInBits <= 16)
    {
      if (params->biasScale != -1)
      {
        TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int32_t*)biasPtr, &buffParams->biasB, params->numOutNodes, buffParams->inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32, 0xFFFF, TIDL_getDatElementSign(buffParams->inElementType));
      }
      for (i0 = 0; i0 < params->numOutNodes; i0++)
      {
        ((int32_t*)biasPtr)[i0] = ((int32_t*)biasPtr)[i0] * buffParams->biasB;
      }

      TIDL_refInnerProductParamBitDepth(intAlgHandle, layerIdx, inPtr, outPtr, (int32_t *)biasPtr, (int16_t *)weightPtr, (int64_t*)accPtr, tidlLayer->outData.elementType, buffParams);
    }
    else if (tidlLayer->weightsElementSizeInBits == 32)
    {
      TIDL_refInnerProductParamBitDepth(intAlgHandle, layerIdx, inPtr, outPtr, orgBiasPtrFloat, (float32_tidl *)weightPtr, (float32_tidl*)accPtr, tidlLayer->outData.elementType, buffParams);
    }
  }
  TIDL_enableL1DandL2CacheWb();
  return status;  
}

int32_t TIDL_forceInnerProductRef(
  const TIDL_CreateParams  *createParamsPtr,
  sTIDL_Layer_t* tidlLayer
)
{
  int32_t forceRef ;
  sTIDL_Network_t *pNet = createParamsPtr->net ;
  sTIDL_DataParams_t *inDataParams;
  uint16_t numInNodes, numOutNodes ;

  inDataParams   = TIDL_getDataParams(pNet, tidlLayer->inData[0]);
  numOutNodes    = (uint16_t)tidlLayer->outData.dimValues[3];
  numInNodes     = (uint16_t)inDataParams->dimValues[3]; 

  forceRef = !TIDL_referencFlow(createParamsPtr);

  if (((createParamsPtr->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0) && 
    ((((numInNodes <= 2048) && (numOutNodes <= 1024) && (numOutNodes >= 128)) && 
    ((createParamsPtr->reservedCtrl & TIDL_REF_CODE_FOR_IP) == 0))))
  {
    forceRef = 0 ;
  }
  return forceRef ;
}

/**
 * @brief InnerProduct layer Process function
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
int32_t TIDL_innerProductProcess(
                              TIDL_Handle          intAlgHandle,
                              sTIDL_AlgLayer_t     * algLayer, 
                              sTIDL_Layer_t        * tidlLayer, 
                              void                 * inPtrs[], 
                              void                 * outPtrs[],
                              sTIDL_sysMemHandle_t sysMems[])
{
  sTIDL_InnerProductParams_t   * params = 
  &tidlLayer->layerParams.innerProductParams;
  tidlInnerProductBuffParams_t buffParams;
  sTIDL_DataParams_t *inDataParams;
  inDataParams   = TIDL_getDataParams(intAlgHandle->createParams->net,
  tidlLayer->inData[0]);
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  uint16_t  inPitch           = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
  uint16_t  outPitch          = (uint16_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  uint8_t   *inPtr            = (uint8_t*)inPtrs[0];
  uint8_t   *outPtr           = (uint8_t*)outPtrs[0];

  uint16_t  numBatches      = (uint16_t)inDataParams->dimValues[0];  /* Batches */
  uint16_t  numOutNodes    = (uint16_t)tidlLayer->outData.dimValues[3];
  uint16_t  numInNodes     = (uint16_t)inDataParams->dimValues[3]; 
  int32_t   status = 1;
  int32_t inSize  = TIDL_getDatElementSize(inDataParams->elementType);
  int32_t outSize = TIDL_getDatElementSize(tidlLayer->outData.elementType);
  int32_t forceRef ;

  numInNodes = (uint16_t )inDataParams->dimValues[1] * 
  (uint16_t )inDataParams->dimValues[2] * 
  (uint16_t )inDataParams->dimValues[3];  

  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    buffParams.mmaShift = algLayer->layerParams.innerProductParams.mmaShift;
    buffParams.mmaScale = algLayer->layerParams.innerProductParams.mmaScale;
  }

  /* Need to change the memory sizes based on the availalbity of memory - EPR*/
  TIDL_innerProductBuffProps(&buffParams, params, numInNodes, numOutNodes, numBatches, 
     tidlLayer, INBUF_INT_MEM_SIZE, INBUF_INT_MEM_SIZE, inDataParams->elementType);
  
  buffParams.numInNodes   =  numInNodes;
  buffParams.numOutNodes  =  numOutNodes;
  buffParams.inPitch      =  inPitch;
  buffParams.outPitch     =  outPitch;
  buffParams.numTotRoi    =  numBatches;
  buffParams.scratchSize  = algLayer->layerParams.innerProductParams.accMemSize;
  buffParams.scratchMem   = algLayer->layerParams.innerProductParams.accMem; 

  if ((intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleNP2Fixed) || 
      (intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleP2Dynamic))
  {
    buffParams.inScaleFactor = (params->weightScale * inDataParams->tensorScale) / params->biasScale; 
    buffParams.outRoundBits  = tidlLayer->outData.roundBits;
    if(params->biasScale == -1)
    {
      buffParams.inScaleFactor = 0;
    }
  }

  inPtr  =  inPtr +  ((inDataParams->padH*inPitch)    + inDataParams->padW) * inSize;
  outPtr =  outPtr + ((tidlLayer->outData.padH*outPitch)  + tidlLayer->outData.padW) * outSize;

  forceRef = TIDL_forceInnerProductRef(intAlgHandle->createParams, tidlLayer);
  if(forceRef || TIDL_referencFlow(intAlgHandle->createParams) ){
    tidl_printf(1,"Executing reference flow for inner product layer \n");
    status = TIDL_innerProductRefProcess(intAlgHandle,
                                          algLayer,
                                          tidlLayer, 
                                           params, 
                                           &buffParams,
                                           (void*)inPtr, 
                                           (void*)outPtr);

  }else{
    for (int32_t i = 0; i < numBatches; i++)
    {
      status = TIDL_innerProductMMAProcess(intAlgHandle,
        algLayer,
        tidlLayer,
        params,
        &buffParams,
        sysMems,
        (void*)(inPtr + i* inDataParams->pitch[TIDL_ROI_PITCH] * inSize),
        (void*)(outPtr + i* tidlLayer->outData.pitch[TIDL_ROI_PITCH] * outSize));
    }
  }
  return status;
}
