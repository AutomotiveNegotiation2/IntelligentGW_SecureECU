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
 *  \file tidl_batchNorm.c
 *
 *  \brief This file defines kernel functions for Batch Norm layer
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tidl_alg_int.h"
#include "tidl_commonUtils.h"
#include "tidl_batchNorm.h"
#include <cmath>
#include <limits>
#include "tidl_lut_module.h"


//#define TIDL_REF_BATCH_NORM_DEBUG
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

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
 * @brief Function will do multiplication with slope and rounding
 *
 * @param out  : Input value that requires rounding with slope
 * @param slopeFact : The amount of slope that need to be multiplied
 * @param slopeQBits : roundbits for rounding
 * @return int32_t : output after rounding with slope
 */
int32_t TIDL_refBatchNormCoreRoundSlope(
  int32_t out,
  int32_t slopeFact,
  int32_t slopeQBits)
{
  if(out < 0)
  {
    out = (((int64_t)out * slopeFact) >> slopeQBits);
  }
  return out;
}
/**
 * @brief This is main function perform batchNorm on differnt elementTypes
 *
 * @tparam Tin  : template for input
 * @tparam Tw   : template for weights
 * @tparam Tb   : template for Bias
 * @tparam Tout : template for output
 * @tparam Tsat : template for saturate values
 * @param inPtr : Input pointer on which bacthNorm is applied
 * @param outPtr : Output pointer after batchNorm opreation
 * @param weightsPtr : Pointer to weights buffer
 * @param slopePtr : Pointer to the Slope buffer
 * @param biasPtr  : Pointer to the Bias values
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param params : copy of bacthNorm parameters
 * @param algLayer : Pointer to the layer specific parameters
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @param satLow : min value for the saturation
 * @param satHigh : max value for the saturation
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tw, class Tb, class Tout, class Tacc>
static int32_t TIDL_refBatchNormCore(Tin  *inPtr,
                                     Tout *outPtr,
                                     const Tw *weightsPtr,
                                     const Tw *slopePtr,
                                     const Tb *biasPtr,
                                     Tacc     *refAccPtr,
                                     TIDL_Handle intAlgHandle,
                                     int32_t layerIdx,
                                     sTIDL_BatchNormParams_t *params,
                                     sTIDL_AlgLayer_t *algLayer,
                                     const sTIDL_DataParams_t *inDataParams,
                                     const sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  sTIDL_Network_t * net = intAlgHandle->createParams->net;
  int32_t i0, i1, i2, i3;
  int32_t imWidth    = (int32_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
  int32_t imHeight   = (int32_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
  int32_t inPitch    = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t inChPitch  = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t inBatchPitch  = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  int32_t outPitch   = (int32_t)outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t outChPitch = (int32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t outBatchPitch = (int32_t)outDataParams->pitch[TIDL_ROI_PITCH];
  Tin  *inData = (Tin *)inPtr + (inDataParams->padH*inPitch) + inDataParams->padW;
  Tacc out = 0;
  int32_t numTotBatches = inDataParams->dimValues[TIDL_DIM_BATCH];
  int32_t accMemSize;
  Tw weightVal;
  int32_t slopeQBits = 0;
  int32_t slopeFact  = 1;
  Tw preluScale = 1;
  uint32_t accumulatorSize = (uint32_t)(sizeof(*refAccPtr));

  params->numChannels = inDataParams->dimValues[TIDL_DIM_NUMCH];

  accMemSize = (numTotBatches * outBatchPitch* (int32_t)accumulatorSize);

  if(algLayer->scratchSize >= accMemSize)
  {
     refAccPtr = (Tacc *)algLayer->scratchMem;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refBatchNormCore accumulator is not sufficient exiting...\n    ");
    status = TIDL_ERR_FAILURE;
  }

  if(TIDL_SUCCESS == status)
  {
    Tacc min, max;

    max = std::numeric_limits<Tacc>::lowest();
    min = std::numeric_limits<Tacc>::max();

    for (i3 = 0; i3 < numTotBatches; i3++)
    {
      Tin  inDataVal;
      for (i2 = 0; i2 < params->numChannels; i2++)
      {
        weightVal = weightsPtr[i2];
        if(intAlgHandle->createParams->net->TIDLLayers[layerIdx].actParams.actType == TIDL_PRelU)
        {
          preluScale = slopePtr[i2];
          slopeQBits = 8;
          int32_t tempSlopeFact = preluScale*(((int32_t)1) << slopeQBits);
          float32_tidl floatSlopeFact = (float32_tidl)(tempSlopeFact) /
          intAlgHandle->createParams->net->TIDLLayers[layerIdx].actParams.slopeScale;
          slopeFact = (int32_t)(floatSlopeFact);
          /* for 16-bit weights the deviation is more because of float to int conversion : TIDL-1332 */
          if(sizeof(Tw) == sizeof(int16_t))
          {
            slopeFact = (int32_t)(floatSlopeFact*256);
            slopeQBits += 8;
          }
        }


        for (i0=0; i0<imHeight; i0++)
        {
#ifdef TIDL_REF_BATCH_NORM_DEBUG
          printf("i = %d \n",i0);
#endif
          for (i1=0; i1<imWidth; i1++)
          {
            inDataVal = (Tin)(inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
            out = ((inDataVal* weightVal) + (biasPtr[i2]));
            if (out < 0)
            {
              if (typeid(Tacc) == typeid(float32_tidl))
              {
                out = out * preluScale;
              }
              else
              {
                out = TIDL_refBatchNormCoreRoundSlope((int32_t)out, slopeFact, slopeQBits);
              }
            }
            min = (out<min) ? out : min;
            max = (out>max) ? out : max;

#ifdef TIDL_REF_BATCH_NORM_DEBUG
            printf("[%d , %d, %d, %d, %d], ", i1, inDataVal, weightVal, biasPtr[i2], out);
#endif
            refAccPtr[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = out;
          }
#ifdef TIDL_REF_BATCH_NORM_DEBUG
            printf("\n");
#endif
        }
      }
    }

    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if(TIDL_getDatElementSign(outDataParams->elementType) == 1)
      {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, (int64_t)min, (int64_t)max);
      }
      else
      {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, (int64_t)max);
      }
    }
    Tout *outData = (Tout *)outPtr + (outDataParams->padH*outPitch) + outDataParams->padW;

    int32_t satLow;
    int32_t satHigh;
    int32_t mixedPrecision = 0;
    int32_t outRoundBits;
    Tout temp;
    temp  = std::numeric_limits<Tout>::lowest();
    satLow = (int32_t)temp;
    temp  = std::numeric_limits<Tout>::max();

    satHigh = (int32_t)(temp);
    outRoundBits = outDataParams->roundBits;
    if ( sizeof(*weightsPtr) != sizeof(*outData))
    {
      mixedPrecision = 1;
      /* This is to match with target implementation wherin the saturations
    happens after applying outRoundBits - 8 shift and then the right shift
    of 8 is applied */
      outRoundBits = outRoundBits - 8;
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

    for (i3=0; i3<numTotBatches; i3++)
    {
      for (i2=0; i2<params->numChannels; i2++)
      {
        for (i0=0; i0<imHeight; i0++)
        {
          for (i1=0; i1<imWidth; i1++)
          {
            out = refAccPtr[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1];
            if (typeid(Tacc) == typeid(float32_tidl))
            {
              out =  TIDL_floatSat(out, &net->TIDLLayers[layerIdx]);
            }
            else
            {
              out = (int32_t)TIDL_roundSat((int64_t)out, outRoundBits , (int32_t)satLow, (int32_t)satHigh);
              if ( mixedPrecision == 1 )
              {
                out = (int64_t)out >> 8;
              }
            }
            outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (Tout)out;
          }
        }
      }
    }
  }

  return status;
}

/**
 * @brief This is main function perform Sigmoid on differnt elementTypes
 *
 * @tparam Tin  : template for input
 * @tparam Tout : template for output
 * @param inPtr : Input pointer on which bacthNorm is applied
 * @param outPtr : Output pointer after batchNorm opreation
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param params : copy of bacthNorm parameters
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @param slope : Pointer to slope values for sigmoid
 * @param offset : Pointer to offset values for sigmoid
 * @param satLow : min value for the saturation
 * @param satHigh : max value for the saturation
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tout, class Tacc >
static int32_t TIDL_refSigmoidCore(Tin  *inPtr,
                                   Tout *outPtr,
                                   TIDL_Handle intAlgHandle,
                                   sTIDL_AlgLayer_t *algLayer,
                                   int32_t layerIdx,
                                   sTIDL_BatchNormParams_t *params,
                                   sTIDL_DataParams_t *inDataParams,
                                   sTIDL_DataParams_t *outDataParams,
                                   Tout *slope,
                                   Tout *offset,
                                   Tout offsetScale,
                                   Tacc *scratchMemPtr
                                   )
{
  int32_t status = TIDL_SUCCESS;
  int32_t i0, i1, i2, i3;
  int32_t imWidth    = (int32_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
  int32_t imHeight   = (int32_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
  int32_t inPitch    = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t inChPitch  = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t inBatchPitch  = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  int32_t outPitch   = (int32_t)outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t outChPitch = (int32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t outBatchPitch = (int32_t)outDataParams->pitch[TIDL_ROI_PITCH];
  int32_t numTotBatches = inDataParams->dimValues[TIDL_DIM_BATCH];
  Tacc outVal;
  params->numChannels = inDataParams->dimValues[1];
  Tin  *inData = (Tin *)inPtr + (inDataParams->padH*inPitch) + inDataParams->padW;
  Tout *outData = (Tout *)outPtr + (outDataParams->padH*outPitch) + outDataParams->padW;
  Tout out = 0;
  Tout satHigh, satLow;

  if((intAlgHandle->createParams->reservedCtrl & TIDL_HIGH_ACCURACY_SIGMOID) == 0)
  {
    float inputScale = inDataParams->tensorScale;
    uint16_t thresholdScale = 16; // 4-bits to avoid thresholds overflow
    uint32_t threshold0 = 5*thresholdScale*inputScale;
    uint32_t threshold1 = 2.375*thresholdScale*inputScale;
    uint32_t threshold2 = 1*thresholdScale*inputScale;
    uint16_t inDataScale = thresholdScale;

    Tacc *refAccPtr;
    int32_t accMemSize;
    uint32_t accumulatorSize = (uint32_t)(sizeof(Tacc));
    accMemSize = (numTotBatches * outBatchPitch* (int32_t)accumulatorSize);
    if(algLayer->scratchSize >= accMemSize)
    {
       refAccPtr = (Tacc *)scratchMemPtr;
    }
    else
    {
      tidl_printf(0,"Memory for  TIDL_refSigmoidCore accumulator is not sufficient exiting...\n    ");
      status = TIDL_ERR_FAILURE;
    }

    if(TIDL_SUCCESS == status)
    {
      int32_t min, max;
      min = std::numeric_limits<Tacc>::max();
      max = std::numeric_limits<Tacc>::lowest();
      satHigh = std::numeric_limits<Tout>::max();
      satLow = std::numeric_limits<Tout>::lowest();

      for (i3 = 0; i3 < numTotBatches; i3++)
      {
        Tin  inDataVal, inDataValAbs, constZero = 0;
        uint32_t inDataValShl8;
        for (i2 = 0; i2 < params->numChannels; i2++)
        {
          for (i0=0; i0<imHeight; i0++)
          {
            for (i1=0; i1<imWidth; i1++)
            {
              inDataVal = (inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
              inDataValAbs = inDataVal < constZero?-inDataVal:inDataVal;
              inDataValShl8 = inDataValAbs * inDataScale;
              if(inDataValShl8 >= threshold0)
              {
                outVal = slope[0] * inDataValAbs + offset[0]*offsetScale;
              }
              else if ((inDataValShl8 < threshold0) && (inDataValShl8 >= threshold1))
              {
                outVal = slope[1] * inDataValAbs + offset[1]*offsetScale;
              }
              else if ((inDataValShl8 < threshold1) && (inDataValShl8 >= threshold2))
              {
                outVal = slope[2] * inDataValAbs + offset[2]*offsetScale;
              }
              else if ((inDataValShl8 < threshold2) && (inDataValShl8 >= constZero))
              {
                outVal = slope[3] * inDataValAbs + offset[3]*offsetScale;
              }

              if(inDataVal < constZero)
              {
                outVal = offset[0]*offsetScale - outVal;
              }

              min = (outVal<min) ? outVal : min;
              max = (outVal>max) ? outVal : max;
              refAccPtr[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = outVal;
            }
          }
        }
      }

      if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
      {
        if(TIDL_getDatElementSign(outDataParams->elementType) == 1)
        {
          TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, min, max);
        }
        else
        {
          TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, max);
        }
      }

      for (i3=0; i3<numTotBatches; i3++)
      {
        for (i2=0; i2<params->numChannels; i2++)
        {
          for (i0=0; i0<imHeight; i0++)
          {
            for (i1=0; i1<imWidth; i1++)
            {
              outVal = refAccPtr[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1];
              out = (Tout)TIDL_roundSat(outVal, outDataParams->roundBits, satLow, satHigh);
              outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (Tout)out;
            }
          }
        }
      }
    }
  }
  else
  {
    float inValF, outValF;    
    float inputScale = inDataParams->tensorScale;
    float inDataScaleFact = 1.0/inputScale;

    for (i3 = 0; i3 < numTotBatches; i3++)
    {
      Tin  inDataVal;
      for (i2 = 0; i2 < params->numChannels; i2++)
      {
        for (i0=0; i0<imHeight; i0++)
        {
          for (i1=0; i1<imWidth; i1++)
          {
            inDataVal = (inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
            inValF = inDataVal * inDataScaleFact;
            outValF = div_sp(1.0f, (exp_taylor(-inValF) + 1.0f));
            out = outValF*outDataParams->tensorScale;
            outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (Tout)out; 
          }
        }
      }
    }
  }
  return status;
}
/**
 * @brief  This funciton handles differnt input bit-depths for reference batchNorm
 *
 * @tparam Tw   : template for weights
 * @tparam Tb   : template for Bias
 * @param inPtr : Input pointer on which bacthNorm is applied
 * @param outPtr : Output pointer after batchNorm opreation
 * @param weightsPtr : Pointer to weights buffer
 * @param slopePtr : Pointer to the Slope buffer
 * @param biasPtr  : Pointer to the Bias values
 * @param params : copy of bacthNorm parameters
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param algLayer : Pointer to the layer specific parameters
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tw, class Tb, class Tacc>
static int32_t TIDL_refBatchNormBitDepth(void *inPtr,
                                         void *outPtr,
                                         const Tw *weightsPtr,
                                         const Tw *slopePtr,
                                         const Tb *biasPtr,
                                         Tacc     *accPtr,
                                         sTIDL_BatchNormParams_t *params,
                                         TIDL_Handle intAlgHandle,
                                         int32_t layerIdx,
                                         sTIDL_AlgLayer_t *algLayer,
                                         const sTIDL_DataParams_t *inDataParams,
                                         const sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  if(TIDL_SignedChar == ((int32_t)outDataParams->elementType))
  {
    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int8_t *)inPtr,
                                     (int8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint8_t *)inPtr,
                                     (int8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_SignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int16_t *)inPtr,
                                     (int8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint16_t *)inPtr,
                                     (int8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  else if(TIDL_UnsignedChar == ((int32_t)outDataParams->elementType))
  {
    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int8_t *)inPtr,
                                     (uint8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint8_t *)inPtr,
                                     (uint8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_SignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int16_t *)inPtr,
                                     (uint8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint16_t *)inPtr,
                                     (uint8_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  else if(TIDL_SignedShort == ((int32_t)outDataParams->elementType))
  {
    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int8_t *)inPtr,
                                     (int16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint8_t *)inPtr,
                                     (int16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_SignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int16_t *)inPtr,
                                     (int16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint16_t *)inPtr,
                                     (int16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  else if(TIDL_UnsignedShort == ((int32_t)outDataParams->elementType))
  {
    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int8_t *)inPtr,
                                     (uint16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint8_t *)inPtr,
                                     (uint16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_SignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((int16_t *)inPtr,
                                     (uint16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else if(TIDL_UnsignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refBatchNormCore((uint16_t *)inPtr,
                                     (uint16_t *)outPtr,
                                     weightsPtr,
                                     slopePtr,
                                     biasPtr,
                                     accPtr,
                                     intAlgHandle,
                                     layerIdx,
                                     params,
                                     algLayer,
                                     inDataParams,
                                     outDataParams);
    }
    else
    {
      status = TIDL_ERR_FAILURE;
    }
  }
  else if(TIDL_SinglePrecFloat == ((int32_t)outDataParams->elementType))
  {
    status = TIDL_refBatchNormCore((float32_tidl *)inPtr,
                                    (float32_tidl *)outPtr,
                                    weightsPtr,
                                    slopePtr,
                                    biasPtr,
                                    accPtr,
                                    intAlgHandle,
                                    layerIdx,
                                    params,
                                    algLayer,
                                    inDataParams,
                                    outDataParams);
  }
  else
  {
    status = TIDL_ERR_FAILURE;
  }
  return status;
}
/**
 * @brief This function is sigmoid reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of batch norm layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param inDataParams : pointer to input data parameters
 * @param outDataParams : pointer to output data parameters
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_refSigmoidProcess(TIDL_Handle intAlgHandle,
                                      sTIDL_AlgLayer_t *algLayer,
                                      const sTIDL_Layer_t    *tidlLayer,
                                      sTIDL_BatchNormParams_t *params,
                                      void *inPtr,
                                      void *outPtr,
                                      sTIDL_DataParams_t *inDataParams,
                                      sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;

  if(TIDL_UnsignedChar == ((int32_t)outDataParams->elementType))
  {
    /*
    slope = 0, 0.03125, 0.125, 0.25
    offset = 1, 0.84375, 0.625, 0.5
    Convert Slope and offset values to 7-bits (NUM_WHGT_BITS-1) */
    uint8_t TIDL_sigmoidSlope[4] = {0, 4, 16, 32};
    uint8_t TIDL_sigmoidOffset[4] = {128, 108, 80, 64};
    uint8_t OffsetScale = 1;
    /* Divide 16-bit offsets to two 8-bit offsets(Offset0, OffsetScale) and so on */
    if (inDataParams->tensorScale > 1.0)
    {
      OffsetScale = (uint8_t)(inDataParams->tensorScale);
      TIDL_sigmoidOffset[0] = (TIDL_sigmoidOffset[0]*inDataParams->tensorScale)/OffsetScale;
      TIDL_sigmoidOffset[1] = (TIDL_sigmoidOffset[1]*inDataParams->tensorScale)/OffsetScale;
      TIDL_sigmoidOffset[2] = (TIDL_sigmoidOffset[2]*inDataParams->tensorScale)/OffsetScale;
      TIDL_sigmoidOffset[3] = (TIDL_sigmoidOffset[3]*inDataParams->tensorScale)/OffsetScale;
    }
    else
    {
      OffsetScale = 1;
      TIDL_sigmoidOffset[0] *= inDataParams->tensorScale;
      TIDL_sigmoidOffset[1] *= inDataParams->tensorScale;
      TIDL_sigmoidOffset[2] *= inDataParams->tensorScale;
      TIDL_sigmoidOffset[3] *= inDataParams->tensorScale;
    }

    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refSigmoidCore((int8_t*)inPtr,
                                  (uint8_t*)outPtr,
                                   intAlgHandle,
                                   algLayer,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   TIDL_sigmoidSlope,
                                   TIDL_sigmoidOffset,
                                   (uint8_t)OffsetScale,
                                   (int32_t*)algLayer->scratchMem
                                   );
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refSigmoidCore((uint8_t*)inPtr,
                                  (uint8_t*)outPtr,
                                   intAlgHandle,
                                   algLayer,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   TIDL_sigmoidSlope,
                                   TIDL_sigmoidOffset,
                                   (uint8_t)OffsetScale,
                                   (int32_t*)algLayer->scratchMem
                                   );
    }
  }
  else if(TIDL_UnsignedShort == ((int32_t)outDataParams->elementType))
  {
    /*
    slope = 0, 0.03125, 0.125, 0.25
    offset = 1, 0.84375, 0.625, 0.5
    Convert Slope and offset values to 15-bits (NUM_WHGT_BITS-1) */
    uint16_t TIDL_sigmoidSlope[4] = {0, 1024, 4096, 8192};
    uint16_t TIDL_sigmoidOffset[4] = {32768, 27648, 20480, 16384};
    uint16_t OffsetScale = 1;
    if (inDataParams->tensorScale > 1.0)
    {
      OffsetScale = (uint16_t)(inDataParams->tensorScale);
      TIDL_sigmoidOffset[0] = (TIDL_sigmoidOffset[0]*inDataParams->tensorScale)/OffsetScale;
      TIDL_sigmoidOffset[1] = (TIDL_sigmoidOffset[1]*inDataParams->tensorScale)/OffsetScale;
      TIDL_sigmoidOffset[2] = (TIDL_sigmoidOffset[2]*inDataParams->tensorScale)/OffsetScale;
      TIDL_sigmoidOffset[3] = (TIDL_sigmoidOffset[3]*inDataParams->tensorScale)/OffsetScale;
    }
    else
    {
      OffsetScale = 1;
      TIDL_sigmoidOffset[0] *= inDataParams->tensorScale;
      TIDL_sigmoidOffset[1] *= inDataParams->tensorScale;
      TIDL_sigmoidOffset[2] *= inDataParams->tensorScale;
      TIDL_sigmoidOffset[3] *= inDataParams->tensorScale;
    }

    if(TIDL_SignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refSigmoidCore((int16_t*)inPtr,
                                   (uint16_t*)outPtr,
                                   intAlgHandle,
                                   algLayer,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   TIDL_sigmoidSlope,
                                   TIDL_sigmoidOffset,
                                   (uint16_t)OffsetScale,
                                   (int32_t*)algLayer->scratchMem
                                   );
    }
    else if(TIDL_UnsignedShort == ((int32_t)inDataParams->elementType))
    {
      status = TIDL_refSigmoidCore((uint16_t*)inPtr,
                                   (uint16_t*)outPtr,
                                   intAlgHandle,
                                   algLayer,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   TIDL_sigmoidSlope,
                                   TIDL_sigmoidOffset,
                                   (uint16_t)OffsetScale,
                                   (int32_t*)algLayer->scratchMem
                                   );
    }
  }
  else  //if(TIDL_SinglePrecFloat == ((int32_t)buffParams->inElementType))
  {
    int32_t i0, i1, i2, i3;
    int32_t imWidth    = (int32_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
    int32_t imHeight   = (int32_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
    int32_t inPitch    = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
    int32_t inChPitch  = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
    int32_t outPitch   = (int32_t)outDataParams->pitch[TIDL_LINE_PITCH];
    int32_t outChPitch = (int32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
    int32_t numTotBatches = inDataParams->dimValues[0];
    params->numChannels = inDataParams->dimValues[1];
    float32_tidl *inData = (float32_tidl *)inPtr + (inDataParams->padH*inPitch) + inDataParams->padW;
    float32_tidl *outData = (float32_tidl *)outPtr + (outDataParams->padH*outPitch) + outDataParams->padW;
    float32_tidl out = 0;
    float32_tidl Max = 1.0, Min = 0;

    for (i3 = 0; i3 < numTotBatches; i3++)
    {
      float32_tidl  inDataVal;
      for (i2 = 0; i2 < params->numChannels; i2++)
      {
        for (i0=0; i0<imHeight; i0++)
        {
          for (i1=0; i1<imWidth; i1++)
          {
            inDataVal = (inData[(i3*params->numChannels*inChPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
            out = 1.0/(1.0+exp(-inDataVal));
            Min = (out<Min) ? out : Min;
            Max = (out>Max) ? out : Max;
            outData[(i3*params->numChannels*outChPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (float32_tidl)out;
          }
        }
      }
    }

    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if(TIDL_getDatElementSign(outDataParams->elementType) == 1)
      {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, Min, Max);
      }
      else
      {
        TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, Max);
      }
    }
  }
  return status;
}

/**
 * @brief This is main function perform Non Linear function tramsformation on differnt elementTypes
 *
 * @tparam Tin  : template for input
 * @tparam Tout : template for output
 * @param inPtr : Input pointer on which bacthNorm is applied
 * @param outPtr : Output pointer after batchNorm opreation
 * @param layerIdx :index of the current layer
 * @param params : copy of bacthNorm parameters
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @param tidlLayer : Pointer to the common layer parameters
 * @param LUT_data_table : pointer to 256-element table for look up
 * @param readOffsetLUT : initial read offset for indexing LUT directly using input data
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tout>
static int32_t TIDL_refNonLinearLUTCore(Tin  *inPtr,
                                   Tout *outPtr,
                                   int32_t layerIdx,
                                   sTIDL_BatchNormParams_t *params,
                                   sTIDL_DataParams_t *inDataParams,
                                   sTIDL_DataParams_t *outDataParams,
                                   const sTIDL_Layer_t    *tidlLayer,
                                   Tout *LUT_data_table,
                                   int32_t readOffsetLUT
                                   )
{
  int32_t status = TIDL_SUCCESS;
  int32_t i0, i1, i2, i3;
  int32_t imWidth    = (int32_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
  int32_t imHeight   = (int32_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
  int32_t inPitch    = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t inChPitch  = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t inBatchPitch  = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  int32_t outPitch   = (int32_t)outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t outChPitch = (int32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t outBatchPitch = (int32_t)outDataParams->pitch[TIDL_ROI_PITCH];
  int32_t numTotBatches = inDataParams->dimValues[TIDL_DIM_BATCH];
  params->numChannels = inDataParams->dimValues[1];
  Tin  *inData = (Tin *)inPtr + (inDataParams->padH*inPitch) + inDataParams->padW;
  Tout *outData = (Tout *)outPtr + (outDataParams->padH*outPitch) + outDataParams->padW;


  for (i3 = 0; i3 < numTotBatches; i3++)
  {
    Tin  inDataVal;
    for (i2 = 0; i2 < params->numChannels; i2++)
    {
      for (i0=0; i0<imHeight; i0++)
      {
        for (i1=0; i1<imWidth; i1++)
        {
          inDataVal = (inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
          outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = LUT_data_table[inDataVal+readOffsetLUT]; 
        }
      }
    }
  }
  return status;
}

/**
 * @brief This function is Non Linear function LUT-based reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of batch norm layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param inDataParams : pointer to input data parameters
 * @param outDataParams : pointer to output data parameters
 * @param LUT_data_table : pointer to 256-element table for look up
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_refNonLinearLUTProcess(TIDL_Handle intAlgHandle,
                                      sTIDL_AlgLayer_t *algLayer,
                                      const sTIDL_Layer_t    *tidlLayer,
                                      sTIDL_BatchNormParams_t *params,
                                      void *inPtr,
                                      void *outPtr,
                                      sTIDL_DataParams_t *inDataParams,
                                      sTIDL_DataParams_t *outDataParams,
                                      void *LUT_data_table)
{
  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;
  int32_t readOffsetLUT, isOutputSigned;

  if(TIDL_UnsignedChar == ((int32_t)outDataParams->elementType))
  {
    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    { 
      TIDL_prepareLUTForNonLinearTransform8bit((int8_t*)inPtr, (uint8_t*)outPtr, tidlLayer, (uint8_t*)LUT_data_table, inDataParams, outDataParams, &readOffsetLUT, &isOutputSigned);
      status = TIDL_refNonLinearLUTCore((int8_t*)inPtr,
                                  (uint8_t*)outPtr,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   tidlLayer,
                                   (uint8_t*)LUT_data_table,
                                   readOffsetLUT
                                   );
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      TIDL_prepareLUTForNonLinearTransform8bit((uint8_t*)inPtr, (uint8_t*)outPtr, tidlLayer, (uint8_t*)LUT_data_table, inDataParams, outDataParams, &readOffsetLUT, &isOutputSigned);
      status = TIDL_refNonLinearLUTCore((uint8_t*)inPtr,
                                  (uint8_t*)outPtr,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   tidlLayer,
                                   (uint8_t*)LUT_data_table,
                                   readOffsetLUT
                                   );
    }
  }
  else if(TIDL_SignedChar == ((int32_t)outDataParams->elementType))
  {
    if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
    {
      TIDL_prepareLUTForNonLinearTransform8bit((int8_t*)inPtr, (int8_t*)outPtr, tidlLayer, (int8_t*)LUT_data_table, inDataParams, outDataParams, &readOffsetLUT, &isOutputSigned);
      status = TIDL_refNonLinearLUTCore((int8_t*)inPtr,
                                  (int8_t*)outPtr,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   tidlLayer,
                                   (int8_t*)LUT_data_table,
                                   readOffsetLUT
                                   );
    }
    else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
    {
      TIDL_prepareLUTForNonLinearTransform8bit((uint8_t*)inPtr, (int8_t*)outPtr, tidlLayer, (int8_t*)LUT_data_table, inDataParams, outDataParams, &readOffsetLUT, &isOutputSigned);
      status = TIDL_refNonLinearLUTCore((uint8_t*)inPtr,
                                  (int8_t*)outPtr,
                                   layerIdx,
                                   params,
                                   inDataParams,
                                   outDataParams,
                                   tidlLayer,
                                   (int8_t*)LUT_data_table,
                                   readOffsetLUT
                                   );
    }
  }
  
  return status;
}

/**
 * @brief This is main function perform Tanh operation if inp-output is in float-float manner 
 * @tparam Tin  : template for input
 * @tparam Tout : template for output
 * @param inPtr : Input pointer on which bacthNorm is applied
 * @param outPtr : Output pointer after batchNorm opreation
 * @param layerIdx :index of the current layer
 * @param params : copy of bacthNorm parameters
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @param tidlLayer : Pointer to the common layer parameters
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
template <class Tin, class Tout>
static int32_t TIDL_refFloatNonLinear(Tin  *inPtr,
                                   Tout *outPtr,
                                   int32_t layerIdx,
                                   sTIDL_BatchNormParams_t *params,
                                   sTIDL_DataParams_t *inDataParams,
                                   sTIDL_DataParams_t *outDataParams,
                                   const sTIDL_Layer_t    *tidlLayer
                                   )
{
  int32_t status = TIDL_SUCCESS;
  int32_t i0, i1, i2, i3;
  int32_t imWidth    = (int32_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
  int32_t imHeight   = (int32_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
  int32_t inPitch    = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t inChPitch  = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t inBatchPitch  = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  int32_t outPitch   = (int32_t)outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t outChPitch = (int32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t outBatchPitch = (int32_t)outDataParams->pitch[TIDL_ROI_PITCH];
  int32_t numTotBatches = inDataParams->dimValues[TIDL_DIM_BATCH];
  params->numChannels = inDataParams->dimValues[1];
  Tin  *inData = (Tin *)inPtr + (inDataParams->padH*inPitch) + inDataParams->padW;
  Tout *outData = (Tout *)outPtr + (outDataParams->padH*outPitch) + outDataParams->padW;
  float32_tidl alpha = (float)tidlLayer->layerParams.batchNormParams.inDataQ/((float)TIDL_NON_LIN_PARAM_SCALE);
  float32_tidl beta = (float)tidlLayer->layerParams.batchNormParams.weightsQ/((float)TIDL_NON_LIN_PARAM_SCALE);


  for (i3 = 0; i3 < numTotBatches; i3++)
  {
    Tin  inDataVal;
    for (i2 = 0; i2 < params->numChannels; i2++)
    {
      for (i0=0; i0<imHeight; i0++)
      {
        for (i1=0; i1<imWidth; i1++)
        {
          if(tidlLayer->actParams.actType == TIDL_Tanh)
          {
            inDataVal = (inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
            outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (Tout)std::tanh(inDataVal); 
          }
          else if(tidlLayer->actParams.actType == TIDL_ELU)
          {
            inDataVal = (inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
            outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (Tout)((inDataVal < 0.0) ? (alpha*(std::exp(inDataVal) - 1)) : inDataVal);
          }
          else if(tidlLayer->actParams.actType == TIDL_HardSigmoid)
          {
            inDataVal = (inData[(i3*inBatchPitch) + (i2*inChPitch) + (i0*inPitch) + i1]);
            float32_tidl outValF = alpha*inDataVal + beta;
            float32_tidl omin = 0;
            float32_tidl omax = 1;
            outValF = (outValF > omax) ? omax : outValF;
            outValF = (outValF < omin) ? omin : outValF;
            outData[(i3*outBatchPitch) + (i2*outChPitch) + (i0*outPitch) + i1] = (Tout)outValF;
          }
          
        }
      }
    }
  }
  return status;
}

/**
 * @brief This function is tanh implementation in fully float manner
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of batch norm layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param inDataParams : pointer to input data parameters
 * @param outDataParams : pointer to output data parameters
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_fullyFloatReferenceNonLinear(TIDL_Handle intAlgHandle,
                                      sTIDL_AlgLayer_t *algLayer,
                                      const sTIDL_Layer_t    *tidlLayer,
                                      sTIDL_BatchNormParams_t *params,
                                      void *inPtr,
                                      void *outPtr,
                                      sTIDL_DataParams_t *inDataParams,
                                      sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;


  status = TIDL_refFloatNonLinear((float32_tidl*)inPtr,
                              (float32_tidl*)outPtr,
                                layerIdx,
                                params,
                                inDataParams,
                                outDataParams,
                                tidlLayer
                                );

  
  return status;
}

 /**
 * @brief BatchNorm layer reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of batch norm layer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param inDataParams : pointer to input data parameters
 * @param outDataParams : pointer to output data parameters
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
static int32_t TIDL_refBatchNormProcess(TIDL_Handle intAlgHandle,
                                        sTIDL_AlgLayer_t *algLayer,
                                        const sTIDL_Layer_t    *tidlLayer,
                                        sTIDL_BatchNormParams_t *params,
                                        void *inPtr,
                                        void *outPtr,
                                        const sTIDL_DataParams_t *inDataParams,
                                        const sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;
  void * weightPtr = ((int8_t *)(intAlgHandle->createParams->net) + params->weights);
  sTIDL_ALgBatchNormParams_t * algBatchNormParams = &algLayer->layerParams.batchNormParams;
  int16_t * orgBiasPtr = (int16_t *)get_int8_t_pointer((int8_t *)(intAlgHandle->createParams->net), params->bias);
  void * biasPtr   = ((int8_t *)algBatchNormParams->biasParamMem);
  void * slopePtr  = ((int8_t *)(intAlgHandle->createParams->net) + tidlLayer->actParams.slope);
  int32_t i0;
  int32_t numChannels = intAlgHandle->createParams->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH];
  float inScaleFactor = (params->weightScale * inDataParams->tensorScale) / params->biasScale;
  void * accPtr = NULL;

  if(tidlLayer->weightsElementSizeInBits == 32)
  {
    biasPtr = ((int8_t *)(intAlgHandle->createParams->net) + params->bias);

    status = TIDL_refBatchNormBitDepth(inPtr,
                                       outPtr,
                                       (float32_tidl *)weightPtr,
                                       (float32_tidl *)slopePtr,
                                       (float32_tidl *)biasPtr,
                                       (float32_tidl *)accPtr,
                                       params,
                                       intAlgHandle,
                                       layerIdx,
                                       algLayer,
                                       inDataParams,
                                       outDataParams);
  }
  else if(tidlLayer->weightsElementSizeInBits <= 8)
  {

    if (params->biasScale != -1)
    {
      TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int16_t*)biasPtr, &algBatchNormParams->biasB, numChannels,
      inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF, TIDL_getDatElementSign(inDataParams->elementType));
    }

    for (i0 = 0; i0 < numChannels; i0++)
    {
      ((int16_t*)biasPtr)[i0] = ((int16_t*)biasPtr)[i0] * algBatchNormParams->biasB;
    }

    status = TIDL_refBatchNormBitDepth(inPtr,
                                       outPtr,
                                       (int8_t *)weightPtr,
                                       (int8_t *)slopePtr,
                                       (int16_t *)biasPtr,
                                       (int32_t *)accPtr,
                                       params,
                                       intAlgHandle,
                                       layerIdx,
                                       algLayer,
                                       inDataParams,
                                       outDataParams);
  }
  else
  {
    if (params->biasScale != -1)
    {
      int32_t maxBiasB = 0xFFFF;
      /* This condition indicates mixed precision where processing is in 16 bit but input is signed input.
      Here as target implementation scales the input with 256, we need to limit the biasB so that it doesn't
      go beyond 8 bits as the same is later multiplied by 256 to match the scale of accumulator*/
      if ( inDataParams->elementType == TIDL_SignedChar )
      {
        maxBiasB = 0xFF;
      }
      TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int32_t*)biasPtr, &algBatchNormParams->biasB, numChannels,
      inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32, maxBiasB, TIDL_getDatElementSign(inDataParams->elementType));
    }
    for (i0 = 0; i0 < numChannels; i0++)
    {
      ((int32_t*)biasPtr)[i0] = ((((int32_t*)biasPtr)[i0])) * algBatchNormParams->biasB;
    }

    status = TIDL_refBatchNormBitDepth(inPtr,
                                       outPtr,
                                       (int16_t *)weightPtr,
                                       (int16_t *)slopePtr,
                                       (int32_t *)biasPtr,
                                       (int64_t *)accPtr,
                                       params,
                                       intAlgHandle,
                                       layerIdx,
                                       algLayer,
                                       inDataParams,
                                       outDataParams);
  }
  return status;
}

static int32_t TIDL_floatReferenceKernelSupportsActivation( const sTIDL_Layer_t * tidlLayer){

  int32_t doesSupport = 0;
  if(tidlLayer->actParams.actType == TIDL_Tanh || tidlLayer->actParams.actType == TIDL_HardSigmoid || tidlLayer->actParams.actType == TIDL_ELU)
  {
    doesSupport = 1;
  }
  return doesSupport;
  
};

/**
 * @brief BatchNorm layer Process function
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
int32_t TIDL_batchNormProcess(TIDL_Handle          intAlgHandle,
                              sTIDL_AlgLayer_t     *algLayer,
                              sTIDL_Layer_t        *tidlLayer,
                              void                 *inPtrs[],
                              void                 *outPtrs[],
                              sTIDL_sysMemHandle_t *sysMems)
{

  int32_t  status      = TIDL_SUCCESS;
  uint8_t  (*inPtr)[]     = (uint8_t (*)[])(inPtrs[0]);
  int8_t   (*outPtr)[]    = (int8_t (*)[])(outPtrs[0]);
  uint32_t flowCtrl = intAlgHandle->createParams->flowCtrl; //  L3
  uint8_t LUT_data_table[TABLE_SIZE_8BIT];

  if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY)
  {
    status = TIDL_batchNormDspProcess(intAlgHandle, algLayer, tidlLayer, inPtrs, outPtrs, sysMems);
  }
  else /* if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) */
  {
    sTIDL_BatchNormParams_t   *params = &tidlLayer->layerParams.batchNormParams;
    sTIDL_DataParams_t        *inDataParams;
    inDataParams   = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;

    if(TIDL_LUTSupportsDatatype(inDataParams->elementType, tidlLayer->outData.elementType) && TIDL_DeviceSupportsLUT(intAlgHandle->createParams->net->deviceName) && TIDL_LUTSupportsActivation(tidlLayer))
    {
      status = TIDL_refNonLinearLUTProcess(intAlgHandle,
                                    algLayer,
                                    tidlLayer,
                                    params,
                                    inPtr,
                                    outPtr,
                                    inDataParams,
                                    &tidlLayer->outData,
                                    LUT_data_table);
    }
    else if(TIDL_floatReferenceKernelSupportsActivation(tidlLayer) && (inDataParams->elementType == TIDL_SinglePrecFloat))
    {
      status = TIDL_fullyFloatReferenceNonLinear(intAlgHandle,
                                    algLayer,
                                    tidlLayer,
                                    params,
                                    inPtr,
                                    outPtr,
                                    inDataParams,
                                    &tidlLayer->outData);
    }
    else
    {
      if (tidlLayer->actParams.actType == TIDL_Sigmoid)
      {
        status = TIDL_refSigmoidProcess(intAlgHandle,
                                      algLayer,
                                      tidlLayer,
                                      params,
                                      inPtr,
                                      outPtr,
                                      inDataParams,
                                      &tidlLayer->outData);  
      }
      else
      {
        status = TIDL_refBatchNormProcess(intAlgHandle,
                                          algLayer,
                                          tidlLayer,
                                          params,
                                          inPtr,
                                          outPtr,
                                          inDataParams,
                                          &tidlLayer->outData);
      }
    }
    TIDL_enableL1DandL2CacheWb();
  }
  return status;
}

