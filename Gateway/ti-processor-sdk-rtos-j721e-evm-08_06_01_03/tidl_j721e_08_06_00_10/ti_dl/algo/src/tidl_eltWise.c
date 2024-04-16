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
 *  \file tidl_eltWise.c
 *
 *  \brief This file defines kernel functions for Element Wise layer
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tidl_alg_int.h"
#include "tidl_eltWise.h"
#include "tidl_commonUtils.h"
#include <limits>
#include "tidl_alg_utils.h"
#include "math.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 @struct  TIDL_EltWiseBuffParams_t

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
          
 @params  numBatches
          Number of Batches

 @params  inBatchPitch
          Batch Pitch of input data in external memory. It contains the size
          of one complete channel data.

 @params  outBatchPitch
          Batch Pitch of output data in external memory. It contains the size
          of one complete channel output data.
          
 @params  outDataQ
          Round bits for output data after EltWise layer operations.

 @params  eltWiseType
          Type of element wise operation.

 @params  numInData
          Number of Input Data.

 @params  numChannels
          Number of channels.
*/
typedef struct {
  uint16_t inWidth;
  uint16_t inHeight;
  uint16_t inPitch;
  uint16_t outPitch;
  uint32_t inChPitch;
  uint32_t outChPitch;
  uint32_t numBatches;
  uint32_t inBatchPitch;
  uint32_t outBatchPitch;  
  int32_t  eltWiseType;
  uint16_t numInData;
  uint16_t numChannels;
} TIDL_EltWiseBuffParams_t;

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
/*                       Static Function Definitions                          */
/* ========================================================================== */

 /**
 * @brief Eltwise layer Sum operation implementation
 *
 * @param pIn : Pointer to input buffer
 * @param pAcc : Pointer to accumulator buffer
 * @param scale : Scale to be applied on the input
 * @param eltWiseBuffParams : parameters of eltwise buffer
 * @param callno : Variable to check if it is first call
 * @param isSigned : to check if one of the input is signed
 */
template <class Tin, class Tacc>
static void TIDL_refEltWiseSum(const Tin *pIn,
                               Tacc *pAcc,
                               int32_t scale,
                               const TIDL_EltWiseBuffParams_t *eltWiseBuffParams,
                               int32_t callno,
                               int32_t isSigned)
{
  uint32_t i1, i2, i3;
  for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
  {
    for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
    {
      for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
      {
        uint32_t inOffset  = (i1 * eltWiseBuffParams->inChPitch) + (i2 * eltWiseBuffParams->inPitch) + i3;
        uint32_t outOffset = (i1 * eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
        pAcc[outOffset] += pIn[inOffset]*scale;
      }
    }
  }
}

 /**
 * @brief Eltwise layer Product operation implementation
 *
 * @param pIn : Pointer to input buffer
 * @param pAcc : Pointer to accumulator buffer
 * @param scale : Scale to be applied on the input
 * @param eltWiseBuffParams : parameters of eltwise buffer
 * @param callno : Variable to check if it is first call
 */
template <class Tin, class Tacc>
static void TIDL_refEltWiseProduct(const Tin *pIn,
                                   Tacc *pAcc,
                                   int32_t scale,
                                   int32_t zeropoint,
                                   const TIDL_EltWiseBuffParams_t *eltWiseBuffParams,
                                   int32_t callno)
{
  uint32_t i1, i2, i3;
  if(callno == 0)
  {
    for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
    {
      for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
      {
        for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
        {
          uint32_t inOffset  = (i1 * eltWiseBuffParams->inChPitch) + (i2 * eltWiseBuffParams->inPitch) + i3;
          uint32_t outOffset = (i1 * eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
          pAcc[outOffset] = (pIn[inOffset] * scale - zeropoint);
        }
      }
    }
  }
  else
  {
    for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
    {
      for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
      {
        for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
        {
          uint32_t inOffset  = (i1 * eltWiseBuffParams->inChPitch) + (i2 * eltWiseBuffParams->inPitch) + i3;
          uint32_t outOffset = (i1 * eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
          pAcc[outOffset] *= (pIn[inOffset] * scale - zeropoint);
        }
      }
    }
  }
}

 /**
 * @brief Eltwise layer Max operation implementation
 *
 * @param pIn : Pointer to input buffer
 * @param pAcc : Pointer to accumulator buffer
 * @param scale : Scale to be applied on the input
 * @param eltWiseBuffParams : parameters of eltwise buffer
 * @param callno : Variable to check if it is first call
 */
template <class Tin, class Tacc>
static void TIDL_refEltWiseMax(const Tin* pIn,
                               Tacc*   pAcc,
                               int32_t scale,
                               const TIDL_EltWiseBuffParams_t *eltWiseBuffParams,
                               int32_t callno)
{
  uint32_t i1, i2, i3;
  if(callno == 0)
  {
    for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
    {
      for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
      {
        for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
        {
          uint32_t inOffset  = (i1 * eltWiseBuffParams->inChPitch) + (i2 * eltWiseBuffParams->inPitch) + i3;
          uint32_t outOffset = (i1 * eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
          pAcc[outOffset] = pIn[inOffset]* scale;
        }
      }
    }
  }
  else
  {
    for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
    {
      for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
      {
        for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
        {
          uint32_t inOffset  = (i1 * eltWiseBuffParams->inChPitch) + (i2 * eltWiseBuffParams->inPitch) + i3;
          uint32_t outOffset = (i1 * eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
          pAcc[outOffset] = ((pIn[inOffset] * scale) > pAcc[outOffset]) ? (pIn[inOffset] * scale) : pAcc[outOffset];
        }
      }
    }
  }
}

 /**
 * @brief Eltwise layer differnt operations implementation
 *
 * @param pIn : Pointer to input buffer
 * @param pAcc : Pointer to accumulator buffer
 * @param scale : Scale to be applied on the input
 * @param eltWiseBuffParams : parameters of eltwise buffer
 * @param callno : Variable to check if it is first call
 * @param isSigned : to check if one of the input is signed
 */
template <class Tin, class Tacc>
static void TIDL_refEltWiseOp(const Tin *pIn,
                              Tacc *pAcc,
                              int32_t scale,
                              int32_t zeropoint,
                              const TIDL_EltWiseBuffParams_t *eltWiseBuffParams,
                              int32_t callno,
                              int32_t isSigned)
{
  if(eltWiseBuffParams->eltWiseType == TIDL_EltWiseSum)
  {
    TIDL_refEltWiseSum(pIn, pAcc, scale, eltWiseBuffParams, callno, isSigned);
  }
  else if(eltWiseBuffParams->eltWiseType == TIDL_EltWiseProduct)
  {
    TIDL_refEltWiseProduct(pIn, pAcc, scale, zeropoint, eltWiseBuffParams, callno);
  }
  else if(eltWiseBuffParams->eltWiseType == TIDL_EltWiseMax)
  {
    TIDL_refEltWiseMax(pIn, pAcc, scale, eltWiseBuffParams, callno);
  }
  else
  {
    tidl_printf(0,"TIDL_EltWise Type %d is  Not supported !!!\n ", eltWiseBuffParams->eltWiseType);
  }
}

static void TIDL_refEltWiseMMAv2Quantize(TIDL_Handle intAlgHandle,
                                    int32_t layerIdx,
                                    int32_t *pAcc,
                                    int8_t *pout,
                                    uint8_t mmaScale,
                                    uint8_t mmaShift,
                                    int32_t biasTerm,
                                    const TIDL_EltWiseBuffParams_t *eltWiseBuffParams)
{
  
  uint32_t i1, i2, i3;
  int64_t tempAcc;
  int32_t mmaAcc;

    for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
  {
    for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
    {
      for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
      {
        uint32_t outOffset = (i1* eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
        mmaAcc = pAcc[outOffset] + biasTerm;
        tempAcc =  mmaAcc * mmaScale;
        pout[outOffset]  = (int8_t)TIDL_roundSat(tempAcc, mmaShift, std::numeric_limits<int8_t>::lowest(), std::numeric_limits<int8_t>::max());
      }
    }
  }

}
 /**
 * @brief Eltwise layer quantization function
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx : Index of the current layer
 * @param pAcc : Pointer to accumulator buffer
 * @param pout : Pointer to ouptut buffer
 * @param eltWiseBuffParams : parameters of eltwise buffer
 * @param satLow : Min value of the saturation
 * @param satHigh : Max value of the saturation
 */
template <class Tacc, class Tout>
static void TIDL_refEltWiseQuantize(TIDL_Handle intAlgHandle,
                                    int32_t layerIdx,
                                    const Tacc *pAcc,
                                    Tout *pout,
                                    const TIDL_EltWiseBuffParams_t *eltWiseBuffParams)
{
  uint32_t i0, i1, i2, i3;
  int32_t roundBits;
  Tacc outAcc;
  sTIDL_Network_t *net = intAlgHandle->createParams->net;
  sTIDL_Layer_t   *tidlLayer = &intAlgHandle->createParams->net->TIDLLayers[layerIdx];
  Tacc min, max;

  min = std::numeric_limits<Tacc>::max();
  max = std::numeric_limits<Tacc>::lowest();

  for (i0=0U; i0 < eltWiseBuffParams->numBatches; i0++)
  {
  for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
  {
    for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
    {
      for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
      {
        uint32_t outOffset = (i0* eltWiseBuffParams->outBatchPitch) +  (i1* eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
        outAcc = pAcc[outOffset];
        min = (outAcc<min) ? outAcc : min;
        max = (outAcc>max) ? outAcc : max;
      }
    }
  }
  }
  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    if(TIDL_getDatElementSign(net->TIDLLayers[layerIdx].outData.elementType) == 1)
    {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, (int64_t)min, (int64_t)max);
    }
    else
    {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, (int64_t)max);
    }
  }

  roundBits = net->TIDLLayers[layerIdx].outData.roundBits;
  int32_t satLow;
  int32_t satHigh;
  int32_t mixedPrecision = 0;
  int32_t procElemSize;
  Tout temp;
  procElemSize = TIDL_getProcessingElementSizeInBytes(tidlLayer);


  temp  = std::numeric_limits<Tout>::lowest();
  satLow = (int32_t)temp;
  temp  = std::numeric_limits<Tout>::max();
  satHigh = (int32_t)(temp);

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


  for (i0=0U; i0 < eltWiseBuffParams->numBatches; i0++)
  {
  for(i1=0U; i1<eltWiseBuffParams->numChannels; i1++)
  {
    for(i2=0U; i2<eltWiseBuffParams->inHeight; i2++)
    {
      for(i3=0U; i3<eltWiseBuffParams->inWidth; i3++)
      {
        uint32_t outOffset = (i0* eltWiseBuffParams->outBatchPitch) + (i1* eltWiseBuffParams->outChPitch) + (i2 * eltWiseBuffParams->outPitch) + i3;
        outAcc = pAcc[outOffset];
        if (tidlLayer->outData.elementType == TIDL_SinglePrecFloat)
        {
          outAcc = TIDL_floatSat(outAcc, tidlLayer);
        }
        else
        {
          outAcc = (Tacc)TIDL_roundSat((int64_t)outAcc, roundBits, satLow, satHigh);
          if ( mixedPrecision == 1 )
          {
            outAcc = (int64_t)outAcc >> 8;
          }
        }
        pout[outOffset] = outAcc;
      }
    }
  }
  }
}
 /**
 * @brief Eltwise layer reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of eltwise layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param numBatches : no of total Batches to be processed
 * @param eltWiseBuffParams : parameters of the eltwise buffer
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_refEltWiseProcess(TIDL_Handle intAlgHandle,
                                      const sTIDL_AlgLayer_t *algLayer,
                                      const sTIDL_Layer_t    *tidlLayer,
                                      const sTIDL_EltWiseParams_t *params,
                                      void *inPtrs[],
                                      uint8_t *outPtr,
                                      uint16_t numBatches,
                                      TIDL_EltWiseBuffParams_t *eltWiseBuffParams)
{
  int32_t status = TIDL_SUCCESS;
  int32_t i4;
  int32_t i, j;
  int32_t inDataScale[TIDL_NUM_IN_BUFS];
  float32_tidl accScale;
  int32_t * refAccPtr;
  int32_t layerIdx = algLayer->layerIdx;
  uint32_t accMemSize;
  int32_t outElementSize = TIDL_getDatElementSize(tidlLayer->outData.elementType);
  int32_t procElemSize = TIDL_getProcessingElementSizeInBytes(tidlLayer);
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  for(i=0; i<TIDL_NUM_IN_BUFS; i++)
  {
    inDataScale[i] = 1;
  }

  uint8_t *outPtrLocal;
  outPtrLocal = (uint8_t *)outPtr + ((((int32_t)eltWiseBuffParams->outPitch * tidlLayer->outData.padH) + tidlLayer->outData.padW) * outElementSize);

  accMemSize = (uint32_t)numBatches*eltWiseBuffParams->outBatchPitch*((uint32_t)sizeof(int32_t));
  if(algLayer->scratchSize >= (int32_t)accMemSize)
  {
    refAccPtr = (int32_t *)algLayer->scratchMem;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refEltWiseProcess accumulator is not sufficient exiting...\n    ");
    status = TIDL_ERR_FAILURE;
  }

  if(TIDL_SUCCESS == status)
  {
    (void)memset(refAccPtr, 0, sizeof(int32_t)*numBatches*eltWiseBuffParams->outBatchPitch);

    if(params->eltWiseType == TIDL_EltWiseProduct)
    {
      for(j=0; j<tidlLayer->numInBufs; j++)
      {
        inDataScale[j] = 1;
      }
    }
    else
    {
      accScale = tidlLayer->outData.tensorScale *  ((float32_tidl)(((uint32_t)1)  << tidlLayer->outData.roundBits));
      for(j=0; j<tidlLayer->numInBufs; j++)
      {
        sTIDL_DataParams_t * indata = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].outData;
        float32_tidl temp2 = accScale / indata->tensorScale;
        inDataScale[j] = (int32_t)temp2;
      }
    }
    uint8_t commonScale = 1;
    uint8_t mmaShift    = 0;
    int32_t biasTerm;
    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      if (params->eltWiseType == TIDL_EltWiseSum)
      {
        //Currently for 2 tensor eltwise only.. fix!
        sTIDL_DataParams_t *inDataParams1;
        sTIDL_DataParams_t *inDataParams2;
        inDataParams1 =  &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
        inDataParams2 =  &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[1]].outData;
        float32_tidl scale1 = inDataParams1->tensorScale/tidlLayer->outData.tensorScale;
        float32_tidl scale2 = inDataParams2->tensorScale/tidlLayer->outData.tensorScale;
        uint8_t iScale1, iScale2;
        TIDL_getMMAv2_EltwiseScalesAndShift(scale1,scale2,&iScale1,&iScale2,&commonScale,&mmaShift);
        inDataScale[0] = iScale1;
        inDataScale[1] = iScale2;
        float32_tidl floatBias = tidlLayer->outData.tensorZeroPoint;
        floatBias -= (((inDataParams1->tensorScale*inDataParams1->tensorZeroPoint)+(inDataParams2->tensorScale*inDataParams2->tensorZeroPoint))/tidlLayer->outData.tensorScale);
        //This term needs to be inverted by the mmaScale to be added to the accumulator:
        float32_tidl mmaFloatScale = (commonScale)/pow(2,(mmaShift));
        floatBias *= (1/mmaFloatScale);
        biasTerm = round(floatBias);
      }
      else if (params->eltWiseType == TIDL_EltWiseProduct)
      {
        sTIDL_DataParams_t *inDataParams1;
        sTIDL_DataParams_t *inDataParams2;
        inDataParams1 =  &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
        inDataParams2 =  &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[1]].outData;
        float32_tidl scale1 = inDataParams1->tensorScale;
        float32_tidl scale2 = inDataParams2->tensorScale;                
        float32_tidl scale = tidlLayer->outData.tensorScale;
        scale = (scale1*scale2)/scale;
        TIDL_getMMAv2_ScaleAndShift(scale,&commonScale,&mmaShift);
        inDataScale[0] = 1;
        inDataScale[1] = 1;
        float32_tidl floatBias = (tidlLayer->outData.tensorZeroPoint*tidlLayer->outData.tensorScale)/(inDataParams1->tensorScale*inDataParams2->tensorScale);
        biasTerm = round(floatBias);
      }
    }

    for(j=0; j<(int32_t)numBatches; j++)
    {
      int32_t * refAccPtrRoi = refAccPtr + j * eltWiseBuffParams->outBatchPitch;      
      
      for(i4=0; i4<(int32_t)eltWiseBuffParams->numInData; i4++)
      {
        sTIDL_DataParams_t *inDataParams;
        inDataParams =  &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[i4]].outData;
        eltWiseBuffParams->inPitch = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
        eltWiseBuffParams->inChPitch = (uint32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
        int32_t inZeroPoint = inDataParams->tensorZeroPoint;

        int32_t inElementSize = TIDL_getDatElementSize(inDataParams->elementType);
        void *inPtr = (uint8_t *)inPtrs[i4] +
                         (((j * (int32_t)eltWiseBuffParams->inBatchPitch) +
                            ((int32_t)eltWiseBuffParams->inPitch * inDataParams->padH) +
                            inDataParams->padW)* inElementSize);

        if(inDataParams->elementType == TIDL_SignedChar)
        {
          TIDL_refEltWiseOp((int8_t*)inPtr,
                            refAccPtrRoi,
                            inDataScale[i4],
                            inZeroPoint,
                            eltWiseBuffParams,
                            i4,
                            1);
        }
        else if(inDataParams->elementType == TIDL_UnsignedChar)
        {
          TIDL_refEltWiseOp((uint8_t*)inPtr,
                            refAccPtrRoi,
                            inDataScale[i4],
                            inZeroPoint,
                            eltWiseBuffParams,
                            i4,
                            0);
        }
        else if(inDataParams->elementType == TIDL_SignedShort)
        {
          TIDL_refEltWiseOp((int16_t*)inPtr,
                            refAccPtrRoi,
                            inDataScale[i4],
                            inZeroPoint,
                            eltWiseBuffParams,
                            i4,
                            1);
        }
        else if(inDataParams->elementType == TIDL_UnsignedShort)
        {
          TIDL_refEltWiseOp((uint16_t*)inPtr,
                            refAccPtrRoi,
                            inDataScale[i4],
                            inZeroPoint,
                            eltWiseBuffParams,
                            i4,
                            0);
        }
        else if(inDataParams->elementType == TIDL_SinglePrecFloat)
        {
          TIDL_refEltWiseOp((float32_tidl *)inPtr,
                            (float32_tidl *)refAccPtrRoi,
                            1.0,
                            0,
                            eltWiseBuffParams,
                            i4,
                            1);
        }
        else
        {
          tidl_printf(0,"TIDL_EltWise in elementType is  Not supported !!!\n ");
        }
      }
    }


    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      TIDL_refEltWiseMMAv2Quantize(intAlgHandle,
                                  layerIdx,
                                  refAccPtr,
                                  (int8_t*)outPtrLocal,
                                  commonScale,
                                  mmaShift,
                                  biasTerm,
                                  eltWiseBuffParams);
    }
    else
    {
      if(tidlLayer->outData.elementType == TIDL_SignedChar)
      {
        TIDL_refEltWiseQuantize(intAlgHandle,
                                layerIdx,
                                refAccPtr,
                                (int8_t*)outPtrLocal,
                                eltWiseBuffParams);
      }
      else if(tidlLayer->outData.elementType == TIDL_UnsignedChar)
      {
        TIDL_refEltWiseQuantize(intAlgHandle,
                                layerIdx,
                                refAccPtr,
                                (uint8_t*)outPtrLocal,
                                eltWiseBuffParams);
      }
      else if(tidlLayer->outData.elementType == TIDL_SignedShort)
      {
        TIDL_refEltWiseQuantize(intAlgHandle,
                                layerIdx,
                                refAccPtr,
                                (int16_t*)outPtrLocal,
                                eltWiseBuffParams);
      }
      else if(tidlLayer->outData.elementType == TIDL_UnsignedShort)
      {
        TIDL_refEltWiseQuantize(intAlgHandle,
                                layerIdx,
                                refAccPtr,
                                (uint16_t*)outPtrLocal,
                                eltWiseBuffParams);
      }
      else if(tidlLayer->outData.elementType == TIDL_SinglePrecFloat) /* Use only to saturate at max/min */
      {
        TIDL_refEltWiseQuantize(intAlgHandle,
                                layerIdx,
                                (float32_tidl *)refAccPtr,
                                (float32_tidl *)outPtrLocal,
                                eltWiseBuffParams); /* Last 2 parameters not used for float */
      }
      else
      {
        tidl_printf(0,"TIDL_EltWiseProduct out elementType is  Not supported !!!\n ");
      }
    }

  }
  TIDL_enableL1DandL2CacheWb();
  return status;
}

/**
 * @brief Eltwise layer Process function
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
int32_t TIDL_eltWiseProcess(TIDL_Handle          intAlgHandle,
                            sTIDL_AlgLayer_t     *algLayer,
                            sTIDL_Layer_t        *tidlLayer,
                            void                 *inPtrs[],
                            void                 *outPtrs[],
                            sTIDL_sysMemHandle_t *sysMems)
{
  int32_t status = TIDL_SUCCESS;
  uint8_t *outPtr = (uint8_t *)outPtrs[0];
  uint32_t flowCtrl = intAlgHandle->createParams->flowCtrl;

  sTIDL_EltWiseParams_t *params = &tidlLayer->layerParams.eltWiseParams;
  sTIDL_DataParams_t *inDataParams;
  sTIDL_DataParams_t *outDataParams;
  inDataParams  = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
  outDataParams = &tidlLayer->outData;
  int32_t inElmtSize  = TIDL_getDatElementSize(inDataParams->elementType);
  int32_t outElmtSize = TIDL_getDatElementSize(outDataParams->elementType);

  //@TODO CAN_BE_MOVED_TO_INIT
  if(((tidlLayer->numInBufs > (TIDL_SIMD_WIDTH/inElmtSize)) && (params->eltWiseType == TIDL_EltWiseSum)) ||
     ((tidlLayer->numInBufs > 2) && (params->eltWiseType != TIDL_EltWiseSum)))
  {
    tidl_printf(0, "Forcing REF_ONLY mode as number of inputs is more than 2 \n");
    flowCtrl |= TIDL_FLOW_CTRL_REF_ONLY;
  }

  if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY)
  {
      status = TIDL_eltWiseDspProcess(intAlgHandle, algLayer, tidlLayer, inPtrs, outPtrs, sysMems);
  }
  else /* ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) */
  {
    TIDL_EltWiseBuffParams_t eltWiseBuffParams;

    uint16_t numBatches = (uint16_t)inDataParams->dimValues[TIDL_DIM_BATCH];
    eltWiseBuffParams.numChannels = (uint16_t)inDataParams->dimValues[1];
    eltWiseBuffParams.inWidth     = (uint16_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
    eltWiseBuffParams.inHeight    = (uint16_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
    eltWiseBuffParams.inPitch     = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
    eltWiseBuffParams.inChPitch   = (uint32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
    eltWiseBuffParams.outPitch    = (uint16_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];
    eltWiseBuffParams.outChPitch  = (uint32_t)tidlLayer->outData.pitch[TIDL_CHANNEL_PITCH];
    eltWiseBuffParams.numInData   = (uint16_t)tidlLayer->numInBufs;
    eltWiseBuffParams.eltWiseType = params->eltWiseType;
    eltWiseBuffParams.numBatches     = (uint16_t)inDataParams->dimValues[TIDL_DIM_BATCH];
    eltWiseBuffParams.inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
    eltWiseBuffParams.outBatchPitch = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];
    
    status = TIDL_refEltWiseProcess(intAlgHandle,
                                    algLayer,
                                    tidlLayer,
                                    params,
                                    inPtrs,
                                    outPtr,
                                    numBatches,
                                    &eltWiseBuffParams);
  }

  return status;
}

