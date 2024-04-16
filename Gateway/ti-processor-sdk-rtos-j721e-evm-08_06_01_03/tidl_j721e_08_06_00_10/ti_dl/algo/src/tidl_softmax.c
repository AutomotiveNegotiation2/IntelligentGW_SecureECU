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
@file    tidl_softmax.c
@brief   This file defines private functions for Softmax layer.
@version 0.1 (Feb 2017) : Initial version [ADK]
----------------------------------------------------------------------------
 */

#include "tidl_alg_int.h"
#include "tidl_commonUtils.h"
#include "tidl_softmax.h"
#include "math.h"
#include "float.h"

#define lutTensorScale (1.0/255.0) /* This is an intermediate variable set by user */
#define lutTensorZP (0.0) /* This is an intermediate variable set by user */
#define SCALE_PRECISION_BITS 8 /* This parameter specifies the precision to which the scale of float should be calculated while converting float to scale and shift */
#define FLOAT_SIMD_WIDTH ((uint32_t)(VEC_NELEM(float))) // This macro defines the max number of float elements that can be present in a full c7x vector. Since the softmax kernel uses float vectors a lot, it is useful to have this macro defined.

template <class Tin, class Tout>
int32_t TIDL_refSoftmaxProcessInt8(
    Tin * inData,
    Tout * outData,
    float32_tidl tensorScale,
    int32_t imWidth,
    int32_t inPitch,
    int32_t outPitch,
    int32_t numBatches,
    int32_t inBatchPitch,
    int32_t outBatchPitch,
    sTIDL_DataParams_t  * inDataParams,
    sTIDL_DataParams_t  * outDataParams

)
{
  int32_t i,j;
  Tin * inPtr   = inData  + inDataParams->padH*inPitch   + inDataParams->padW;
  Tout * outPtr = outData + outDataParams->padH*outPitch + outDataParams->padW;
  int32_t outputTensorZP = outDataParams->tensorZeroPoint;
  float32_tidl outputTensorScale = outDataParams->tensorScale;//
  float32_tidl inputTensorScale = inDataParams->tensorScale;

  for (j = 0; j < numBatches; j++)
  {
    int32_t xMax = TIDL_SAT_LO_INT8;
    int32_t inDataVal;
    int32_t k;
    int32_t numTiles = imWidth / TIDL_SIMD_WIDTH;
    if(imWidth % TIDL_SIMD_WIDTH != 0)
    {
      numTiles++;
    }
    int32_t denomSum=0;

    for (i = 0; i < imWidth; i++)
    {
      inDataVal = inPtr[(j*inBatchPitch) + i];
      xMax = xMax > inDataVal ? xMax : inDataVal;
    }

    
    for (i = 0; i < numTiles; i++)
    {
      for(k = 0; k < TIDL_SIMD_WIDTH ; k++)
      {
        if(((i*TIDL_SIMD_WIDTH) + k) < imWidth)
        {
          uint8_t inputLUT = (uint8_t)(xMax - inPtr[(j*inBatchPitch) + (i*TIDL_SIMD_WIDTH) + k]);
          int32_t expOut = round((exp(-1*inputLUT*inputTensorScale)*(1.0/lutTensorScale))+lutTensorZP);/*LUT output calculation, out = (exp(-5∗sx)∗(1/sp))+zp */
          denomSum += expOut;
          outPtr[(j*inBatchPitch) + (i*TIDL_SIMD_WIDTH) + k] = (uint8_t)(expOut);
        }

      }
    }

    float mulFactor = (1.0/denomSum)*(1.0/outputTensorScale);
    int32_t OutScale, OutShift;
    TIDL_convertFloatToScaleAndShift(mulFactor, &OutScale, &OutShift, SCALE_PRECISION_BITS); 
    uint16_t scaleFactor =(uint16_t)OutScale;
    int32_t absShift = abs(OutShift);

    if(OutShift>=0)
    {
      for (i = 0; i < numTiles; i++)
      {
        for(k = 0; k < TIDL_SIMD_WIDTH ; k++)
        {
          if(((i*TIDL_SIMD_WIDTH) + k) < imWidth)
          {
            uint16_t expOut = (uint8_t)outPtr[(j*inBatchPitch) + (i*TIDL_SIMD_WIDTH) + k];
            uint16_t prod = (expOut*scaleFactor);
            uint16_t shiftOut = prod<<OutShift;
            int16_t softmaxOut = (int16_t)(shiftOut) + outputTensorZP;
            outPtr[(j*inBatchPitch) + (i*TIDL_SIMD_WIDTH) + k] = (Tout)(softmaxOut);
          }
        }
      }
    }
    else
    {
      for (i = 0; i < numTiles; i++)
      {
        for(k = 0; k < TIDL_SIMD_WIDTH ; k++)
        {
          if(((i*TIDL_SIMD_WIDTH) + k) < imWidth)
          {
            uint16_t expOut = (uint8_t)outPtr[(j*inBatchPitch) + (i*TIDL_SIMD_WIDTH) + k];
            uint16_t prod = (expOut*scaleFactor);
            uint16_t shiftOut = (prod+(1<<(absShift-1)))>>absShift;
            int16_t softmaxOut = (int16_t)(shiftOut) + outputTensorZP;
            outPtr[(j*inBatchPitch) + (i*TIDL_SIMD_WIDTH) + k] = (Tout)(softmaxOut);
          }
        }
      }
    }

  }

  return 0;

}

/**
 * @brief This function is reference implementation of softmax layer
 * 
 * @param inData : Pointer to input memory
 * @param outData : Pointer to output memory 
 * @param tensorScale : scale for the input tensor
 * @param imWidth : width of the input buffer
 * @param inPitch : pitch of the input buffer
 * @param outPitch : pitch of the output buffer 
 * @param numBatches : no of total Batches
 * @param inBatchPitch : Batch pitch of the input buffer
 * @param inDataParams : parameters of the input data buffer 
 * @param outDataParams : parameters of the output data buffer 
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tout>
int32_t TIDL_refSoftmaxProcess(
    Tin * inData,
    Tout * outData,
    float32_tidl tensorScale,
    int32_t imWidth,
    int32_t inPitch,
    int32_t outPitch,
    int32_t numBatches,
    int32_t inBatchPitch,
    int32_t outBatchPitch,
    sTIDL_DataParams_t  * inDataParams,
    sTIDL_DataParams_t  * outDataParams

)
{
  float32_tidl maxValue = 0;
  int32_t   maxIndex = 0;
  int32_t i,j;
  float32_tidl temp;
  float32_tidl denom;
  float32_tidl numer;
  float32_tidl output;
  int32_t max, min = TIDL_SAT_LO_INT8;
  Tin * inPtr   = inData  + inDataParams->padH*inPitch   + inDataParams->padW;
  Tout * outPtr = outData + outDataParams->padH*outPitch + outDataParams->padW;

  if(outDataParams->elementType == TIDL_SinglePrecFloat)
  {
    for (j = 0; j < numBatches; j++)
    {
      if(inDataParams->elementType == TIDL_SignedChar)
      {
        min = TIDL_SAT_LO_INT8;
      }
      else if(inDataParams->elementType == TIDL_UnsignedChar)
      {
        min = TIDL_SAT_LO_UINT8;
      }
      else if(inDataParams->elementType == TIDL_SignedShort)
      {
        min = TIDL_SAT_LO_INT16;
      }
      else if(inDataParams->elementType == TIDL_UnsignedShort)
      {
        min = TIDL_SAT_LO_UINT16;
      }
      max = min;
      denom = 0.0;
      maxValue = 0;
      float32_tidl inDataVal;
      float32_tidl log2baseE = (float32_tidl)0.693147180559945;
      float32_tidl logEbase2 = (float32_tidl)1/(float32_tidl)0.693147180559945;
      float32_tidl oneBy6  = (1 / (float32_tidl)6);
      float32_tidl oneBy24 = (0.25) * (1 / (float32_tidl)6);
      for (i = 0; i < imWidth; i++)
      {
        inDataVal = inPtr[(j*inBatchPitch) + i];
        max = max > inDataVal ? max : inDataVal;
      }

      int32_t numTiles = imWidth / FLOAT_SIMD_WIDTH;
      if(imWidth % FLOAT_SIMD_WIDTH != 0)
      {
        numTiles++;
      }
      float32_tidl vecSim[20];
      for(int k = 0; k < FLOAT_SIMD_WIDTH; k++)
      {
        vecSim[k] = 0;
      }
      for (i = 0; i < numTiles; i++)
      {
        for(int k = 0; k < FLOAT_SIMD_WIDTH ; k++)
        {

          // Imitating decdim.
          if((i * FLOAT_SIMD_WIDTH + k) >= imWidth)
          {
            inDataVal = min;
          }
          else
          {
            inDataVal = inPtr[(j*inBatchPitch) + (i * FLOAT_SIMD_WIDTH + k)];
          }

          temp = (inDataVal - max) * (1 / tensorScale);
          
          if(inDataParams->elementType == TIDL_SinglePrecFloat)
          {
            numer = exp(temp);
          }
          else
          {
            temp = logEbase2 * temp;
            int32_t floorTemp = (int32_t)temp;
            float32_tidl floatRes = temp - floorTemp;
            floatRes = floatRes * log2baseE;

            float32_tidl floatRes2 = floatRes * floatRes;
            float32_tidl floatRes3 = floatRes2 * floatRes;
            float32_tidl floatRes4 = floatRes2 * floatRes2;
            numer = 1 + floatRes + (floatRes2 * 0.5);
            numer = numer + (floatRes3 * oneBy6);
            numer = numer + (floatRes4 * oneBy24);
            if(floorTemp > 0)
            {
              numer = numer * ( (1<<16) << (floorTemp) );
            }
            else
            {
              numer = numer * ( (1<<16) >> (-floorTemp) );
            }

            numer = numer * ( 1 / ((float32_tidl)(1<<16)) );
            if(floorTemp < -16 )
              numer = 0;
          }
          

          output = numer;

          vecSim[k] += numer;

          if (maxValue <= output)
          {
            maxValue = output;
            maxIndex = i * FLOAT_SIMD_WIDTH + k;
          }
          /*tidl_printf(0,"%4d : %6.2f",i, output*100);*/
          if((i * FLOAT_SIMD_WIDTH + k) < imWidth)
            outPtr[(j*outBatchPitch) + (i * FLOAT_SIMD_WIDTH + k)] = (Tout)(output);
        }
      }

      for(int k = 0; k < FLOAT_SIMD_WIDTH; k++)
      {
        denom += vecSim[k];
      }
      float32_tidl denomInv = (1/denom);
      for(i = 0; i < imWidth; i++)
      {
        outPtr[(j*outBatchPitch + i)] = outPtr[(j*outBatchPitch + i)]  * denomInv;
        output = outPtr[(j*outBatchPitch + i)];
      }
      tidl_printf(2,"-------Max Index %4d : %7.2f -------\n", maxIndex, outPtr[(j*outBatchPitch) + maxIndex]);
    }   
  }

  else if((inDataParams->elementType == TIDL_SignedChar || inDataParams->elementType == TIDL_UnsignedChar) && (outDataParams->elementType == TIDL_SignedChar || outDataParams->elementType == TIDL_UnsignedChar))
  {
    int32_t rval = TIDL_refSoftmaxProcessInt8<Tin, Tout>(
    inData,
    outData,
    tensorScale,
    imWidth,
    inPitch,
    outPitch,
    numBatches,
    inBatchPitch,
    outBatchPitch,
    inDataParams,
    outDataParams);
  }
  TIDL_enableL1DandL2CacheWb();
  return 0;
}



/**
 * @brief This function is reference implementation of softmax layer
 * 
 * @param tidlLayer : Pointer to the common layer parameters
 * @param inPtrs : Pointer to input memory
 * @param outPtr : Pointer to output memory 
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @param basePrmPtr : Copy of softmax layer parameters
 */
int32_t TIDL_softmaxtProcessSP(
  sTIDL_Layer_t        * tidlLayer,
  void                 * inPtrs,
  void                 * outPtr,
  sTIDL_DataParams_t   * inDataParams[],
  sTIDL_DataParams_t   * outDataParams,
  uint8_t              * basePrmPtr
  )
{
  int32_t   i, maxIndex = 0;
  float32_tidl *in   = (float32_tidl*)inPtrs;
  float32_tidl *out  = (float32_tidl*)outPtr;


  int32_t outImPitch = outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t inImPitch  = inDataParams[0]->pitch[TIDL_LINE_PITCH];

  int32_t imWidth   = inDataParams[0]->dimValues[TIDL_DIM_WIDTH];

  int32_t inOffset  = inDataParams[0]->padH * inImPitch + inDataParams[0]->padW;
  int32_t outOffset = outDataParams->padH * outImPitch + outDataParams->padW;

  float32_tidl max = -FLT_MAX;
  float32_tidl denom = 0.0;
  float32_tidl maxValue = 0;
  float32_tidl inDataVal, output;
  float32_tidl * inPtr = &in[inOffset];
  float32_tidl temp, numer;

  for (i = 0; i < imWidth; i++)
  {
    inDataVal = inPtr[i];
    max = max > inDataVal ? max : inDataVal;
  }
  for (i = 0; i < imWidth; i++)
  {
    inDataVal = inPtr[i] ;
    temp = (inDataVal - max);
    denom += (float32_tidl)exp((float64_tidl)(temp));
  }
  for (i = 0; i < imWidth; i++)
  {
    inDataVal = inPtr[i] ;
    temp = (inDataVal - max);
    numer = (float32_tidl)exp((float64_tidl)(temp));
    output = (numer / denom);
    if (maxValue <= output)
    {
      maxValue = output;
      maxIndex = i;
    }
    out[outOffset+i] = (output);
  }
  tidl_printf(1,"-------Max Index %4d : %7.2f -------\n", maxIndex, out[outOffset+maxIndex]);
  return IALG_EOK;
}


/**
 ----------------------------------------------------------------------------
 @ingroup    TIDL_SOFTMAX
 @fn         TIDL_softmaxProcess
 @brief      Softmax activation Layer

 @param      intAlgHandle : tidl algorithm handle
 @param      algLayer : Ptr to alg layer parameter used in Softmax layer
 @param      tidlLayer: Ptr to tidl layer parameter used in Softmax layer
 @param      inPtrs: Ptrs to input buffers to be processed
 @param      outPtrs: Ptrs to output buffers to be processed
 @param      sysMems: Ptr to memory releated buffers used in Softmax layer
 @remarks    None
 @return     IALG_EOK   - Successful
             IALG_EFAIL - Unspecified error
 ----------------------------------------------------------------------------
 */
int32_t TIDL_softmaxProcess(
    TIDL_Handle          intAlgHandle,
    sTIDL_AlgLayer_t     * algLayer,
    sTIDL_Layer_t        * tidlLayer,
    void                 * inPtrs[],
    void                 * outPtrs[],
    sTIDL_sysMemHandle_t * sysMems)
{

  sTIDL_DataParams_t *inDataParams;
  inDataParams = TIDL_getDataParams(intAlgHandle->createParams->net,
      tidlLayer->inData[0]);
  sTIDL_DataParams_t *outDataParams = &tidlLayer->outData;

  int32_t  imWidth           = inDataParams->dimValues[3];
  int32_t  inPitch           = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t  outPitch          = (uint16_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  int32_t  inBatchPitch        = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];;
  int32_t  numBatches         = (int32_t)inDataParams->dimValues[0]; /*Batches  */
  int32_t  outBatchPitch       = tidlLayer->outData.pitch[TIDL_ROI_PITCH];
  int32_t inElementSize      = TIDL_getDatElementSize(inDataParams->elementType);
  int32_t outElementSize     = TIDL_getDatElementSize(tidlLayer->outData.elementType);
  int32_t status = IALG_EOK;
  if(intAlgHandle->createParams->net->weightsElementSize == 4)
  {
    sTIDL_DataParams_t * inDataPrms[TIDL_NUM_IN_BUFS] = {0};
    for(int j=0; j < tidlLayer->numInBufs; j++)
    {
      inDataPrms[0]  = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].outData;
    }
    for (int32_t ii = 0; ii < numBatches; ii++){
      status = TIDL_softmaxtProcessSP(tidlLayer,  (void*)((int8_t*)inPtrs[0] + (ii*inBatchPitch*inElementSize)), (void*)((int8_t*)outPtrs[0] + (ii*outBatchPitch*outElementSize)), inDataPrms, &tidlLayer->outData, (uint8_t*)intAlgHandle->createParams->net);
    }
    return (status);
  } 

  if (((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY) &&
      ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_DSP_NATC) != TIDL_FLOW_CTRL_DSP_NATC))
  {
    if (numBatches == 1)
    {
      status = TIDL_softmaxDspProcess(intAlgHandle, algLayer, tidlLayer, inPtrs[0],
      outPtrs[0], sysMems);
    }
    else
    {
      for (int32_t ii = 0; ii < numBatches; ii++)
      {
        status = TIDL_softmaxDspProcess(intAlgHandle, algLayer, tidlLayer, (void*)((int8_t*)inPtrs[0] + (ii*inBatchPitch*inElementSize)),
        (void*)((int8_t*)outPtrs[0] + (ii*outBatchPitch*outElementSize)), sysMems);
      }
    }
  }
  else /* ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) */
  {
    if(outDataParams->elementType == TIDL_SinglePrecFloat)
    {
      if (inDataParams->elementType == TIDL_SignedChar)
      {

        TIDL_refSoftmaxProcess(
            (int8_t*)(inPtrs[0]),
            (float32_tidl*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
      else if (inDataParams->elementType == TIDL_UnsignedChar)
      {

        TIDL_refSoftmaxProcess(
            (uint8_t*)(inPtrs[0]),
            (float32_tidl*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
      else if (inDataParams->elementType == TIDL_SignedShort)
      {

        TIDL_refSoftmaxProcess(
            (int16_t*)(inPtrs[0]),
            (float32_tidl*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
      else if (inDataParams->elementType == TIDL_UnsignedShort)
      {

        TIDL_refSoftmaxProcess(
            (uint16_t*)(inPtrs[0]),
            (float32_tidl*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
    }
    else if(outDataParams->elementType == TIDL_SignedChar)
    {
      if (inDataParams->elementType == TIDL_SignedChar)
      {

        TIDL_refSoftmaxProcess(
            (int8_t*)(inPtrs[0]),
            (int8_t*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
      else if (inDataParams->elementType == TIDL_UnsignedChar)
      {

        TIDL_refSoftmaxProcess(
            (uint8_t*)(inPtrs[0]),
            (int8_t*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
    }
    else if(outDataParams->elementType == TIDL_UnsignedChar)
    {
      if (inDataParams->elementType == TIDL_SignedChar)
      {

        TIDL_refSoftmaxProcess(
            (int8_t*)(inPtrs[0]),
            (uint8_t*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
      else if (inDataParams->elementType == TIDL_UnsignedChar)
      {

        TIDL_refSoftmaxProcess(
            (uint8_t*)(inPtrs[0]),
            (uint8_t*)(outPtrs[0]),
            inDataParams->tensorScale,
            imWidth,
            inPitch,
            outPitch,
            numBatches,
            inBatchPitch,
            outBatchPitch,
            inDataParams,
            &tidlLayer->outData
        );
      }
    }


    
  }
  return status;
}

