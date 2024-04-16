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
@file    tidl_conv2d_base.c
@brief   This file contains basic functions required by Convolution Layer
@version 0.1 (Oct 2016) : Initial version [ADK]
@version 0.5 (Jan 2017) : Cleaned up [ADK]
----------------------------------------------------------------------------
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits>

#include "tidl_alg_int.h"
#include "tidl_eltWise.h"
#include "tidl_deconv2d.h"
#include "tidl_conv2d_spatialPooling.h"
#include "tidl_argmax.h"
#include "tidl_commonUtils.h"
#include "tidl_types.h"
#include "tidl_depthToSpace.h"
#include "tidl_device_functions.h"

#include <math.h>
#ifdef BUILD_WITH_CUDA
#include"tidl_cuda.h"
#endif
#if defined(_HOST_BUILD)
#define _POSIX_C_SOURCE 200112L
#include "tidl_avx.h"
#include <cmath>
#endif
#include <stdlib.h>
#include "tidl_conv2d_mma_i.h"
#include "tidl_deviceInfo.h"

#define DUMP_MMA_TEST_CASE (0)

#define USE_16BIT_BIAS_FOR_8BIT_MODE (1)

#if defined(_HOST_BUILD)
int32_t circularBlockSizeTbl[11] =
{ 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288 };
#endif

#if DUMP_MMA_TEST_CASE
void TIDL_WriteMemAsUint8Array(FILE * fp, uint8_t * ptr, int32_t size, const char arrayName[], const char secName[])
{
  int32_t ctr;
  //Write luma data
  fprintf(fp, "#pragma DATA_SECTION(%s, \".%s\")\n", arrayName, secName);
  fprintf(fp, "const uint8_t  %s[] = {\n", arrayName);

  for (ctr = 0; ctr < (size-1); ctr++)
    fprintf(fp, "%4d,", ptr[ctr]);

  fprintf(fp, "%4d};\n\n", ptr[ctr]);
}
#endif


/**
----------------------------------------------------------------------------
@ingroup    TIDL_CONV2D
@fn         TIDL_conv2DConvertCoeffBuffer
@brief      Function copies the coefficient buffers from the network parameters
            to internal buffer which will be used by MMALIB convolution kernels

@param      conv2dparams : Convolution Layer params
@param      dataFlowInfo : The dataflow information from NC
@param      inFeatWidth : width of the input tensor
@param      inFeatHeight : height of the input tensor
@param      coeffNetBuf  : Pointer to the network coeffiecient buffer
@param      biasBuf  : Pointer to the bias buffer
@param      coeffAlgBuf  : Pointer to the alg/internal coeffiecient buffer
@param      weightsElementSizeInBits  : no of bits used for weights
@param      isChannelwiseQuantEnable  : to indicate if channelWiseQuant on/off
@param      targetDevice  : device on which the code is running
@remarks    None
@return     None.
----------------------------------------------------------------------------
*/

void TIDL_conv2DConvertCoeffBuffer( const sTIDL_ConvParams_t * conv2dparams,
                                    const  sDataFlowInfo_t * dataFlowInfo,
                                    uint16_t inFeatWidth,
                                    uint16_t inFeatHeight,
                                    const void *coeffNetBuf,
                                    void *biasBuf,
                                    void  *coeffAlgBuf,
                                    int32_t weightsElementSizeInBits,
                                    int32_t isChannelwiseQuantEnable,
                                    int32_t targetDevice,
                                    sTIDL_virtualPad *virtualPad)
{
  uint32_t dataFlowType = GETDATAFLOW_BUFTYPE(dataFlowInfo->dataFlowType);

  if (( dataFlowType == ROW_LINEAR ) || ( dataFlowType == ROW_CIRCULAR))
  {            
      TIDL_conv2dRowFlow_convertCoeffBiasBuffer(conv2dparams,
                                                dataFlowInfo,
                                                inFeatWidth,
                                                coeffNetBuf,
                                                biasBuf,
                                                coeffAlgBuf,
                                                weightsElementSizeInBits,
                                                targetDevice);
   
  }
  else if ( dataFlowType == COL)
  {
    if ( weightsElementSizeInBits <= 8 )
    {
      #ifdef __C7100__
      TIDL_conv2dColFlow_convertCoeffBiasBuffer<int8_t,int8_t,MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_reorderWeights_Args>(conv2dparams,
                                                                                                                                dataFlowInfo,
                                                                                                                                inFeatWidth,
                                                                                                                                inFeatHeight,
                                                                                                                                (int8_t *)coeffNetBuf,
                                                                                                                                (int8_t *)biasBuf,
                                                                                                                                (int8_t *)coeffAlgBuf,
                                                                                                                                isChannelwiseQuantEnable,
                                                                                                                                targetDevice,
                                                                                                                                virtualPad);
      //PC--
      #else //C7120 && C7504
      if(TIDL_isLegacyKernelEnabled(targetDevice) == FALSE)
      {
        if(conv2dparams->quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
        { 
          #ifndef __C7100__
          TIDL_conv2dColFlow_convertCoeffBiasBuffer<int8_t,int8_t,MMALIB_CNN_convolve_col_smallNo_highPrecision_reorderWeights_Args>(conv2dparams,
                                                                                                                            dataFlowInfo,
                                                                                                                            inFeatWidth,
                                                                                                                            inFeatHeight,
                                                                                                                            (int8_t *)coeffNetBuf,
                                                                                                                            (int8_t *)biasBuf,
                                                                                                                            (int8_t *)coeffAlgBuf,
                                                                                                                            isChannelwiseQuantEnable,
                                                                                                                            targetDevice,
                                                                                                                            virtualPad);
          #endif
        }
        else
        {
          TIDL_conv2dColFlow_convertCoeffBiasBuffer<int8_t,int8_t,MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_reorderWeights_Args>(conv2dparams,
                                                                                                                            dataFlowInfo,
                                                                                                                            inFeatWidth,
                                                                                                                            inFeatHeight,
                                                                                                                            (int8_t *)coeffNetBuf,
                                                                                                                            (int8_t *)biasBuf,
                                                                                                                            (int8_t *)coeffAlgBuf,
                                                                                                                            isChannelwiseQuantEnable,
                                                                                                                            targetDevice,
                                                                                                                            virtualPad);
        }

      }
      #endif
  
      #ifdef LEGACY 
      else
      {
        TIDL_conv2dColFlow_convertCoeffBiasBuffer<int8_t,int8_t,MMALIB_CNN_convolve_col_smallNo_legacy_ixX_ixX_oxX_reorderWeights_Args>(conv2dparams,
                                                                                                                                        dataFlowInfo,
                                                                                                                                        inFeatWidth,
                                                                                                                                        inFeatHeight,
                                                                                                                                        (int8_t *)coeffNetBuf,
                                                                                                                                        (int8_t *)biasBuf,
                                                                                                                                        (int8_t *)coeffAlgBuf,
                                                                                                                                        isChannelwiseQuantEnable,
                                                                                                                                        targetDevice,
                                                                                                                                        virtualPad);
      }
      #endif
    }
    else
    {
      #ifdef __C7100__
      TIDL_conv2dColFlow_convertCoeffBiasBuffer<int16_t,int16_t,MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_reorderWeights_Args>(conv2dparams,
                                                                    dataFlowInfo,
                                                                    inFeatWidth,
                                                                    inFeatHeight,
                                                                    (int16_t *)coeffNetBuf,
                                                                    (int16_t *)biasBuf,
                                                                    (int16_t *)coeffAlgBuf,
                                                                    isChannelwiseQuantEnable,
                                                                    targetDevice,
                                                                    virtualPad);
      //PC--
      #else //C7120 && C7504
      if( FALSE == TIDL_isLegacyKernelEnabled(targetDevice) )
      {
        TIDL_conv2dColFlow_convertCoeffBiasBuffer<int16_t,int16_t,MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_reorderWeights_Args>(conv2dparams,
                                                                      dataFlowInfo,
                                                                      inFeatWidth,
                                                                      inFeatHeight,
                                                                      (int16_t *)coeffNetBuf,
                                                                      (int16_t *)biasBuf,
                                                                      (int16_t *)coeffAlgBuf,
                                                                      isChannelwiseQuantEnable,
                                                                      targetDevice,
                                                                      virtualPad);
      }
      #endif
  
      #ifdef LEGACY
      else
      {
        TIDL_conv2dColFlow_convertCoeffBiasBuffer<int16_t,int16_t,MMALIB_CNN_convolve_col_smallNo_legacy_ixX_ixX_oxX_reorderWeights_Args>(conv2dparams,
                                                                      dataFlowInfo,
                                                                      inFeatWidth,
                                                                      inFeatHeight,
                                                                      (int16_t *)coeffNetBuf,
                                                                      (int16_t *)biasBuf,
                                                                      (int16_t *)coeffAlgBuf,
                                                                      isChannelwiseQuantEnable,
                                                                      targetDevice,
                                                                      virtualPad);
      }
     #endif
    }
  }




}

/**
 * @brief  This function is to find min max for quant
 *
 * @param numBatches  : no of total Batches
 * @param numGroups : total no of groups
 * @param numInChannels : no of input channles
 * @param numOutChannels :  no of output channles
 * @param inChPitch : Channel pitch of the input buffer
 * @param outChPitch : Channel pitch of the output buffer
 * @param outImPitch : line pitch of the output buffer
 * @param width : Width of the input buffer
 * @param height : Height of the input buffer
 * @param strideWidth : Stride in width dimension
 * @param strideHeight: Stride in height dimension
 * @param perChannelWeightScalePtr : pointer to scale buffer
 * @param tensorScale : scale of the input tensor
 * @param min : pointer to store minimum value
 * @param max : pointer to store maximum value
 */
template <class Tacc>
float32_tidl TIDL_findMinMaxForChQuant(
  Tacc * accPtr,
  int32_t  numBatches, // N
  int32_t  numGroups, //G
  int32_t  numInChannels, //Ci
  int32_t  numOutChannels, //Co
  int32_t  outBatchPitch,
  int32_t  outChPitch,
  int32_t  outImPitch,
  int32_t  width, // Wi
  int32_t  height, // Hi
  int32_t strideHeight,
  int32_t strideWidth,
  float32_tidl * perChannelWeightScalePtr,
  float32_tidl tensorScale,
  float32_tidl *min,
  float32_tidl *max
)
{
  Tacc inDataVal;
  float32_tidl inDataFloat;
  float32_tidl absMax = 0;
  float32_tidl accScale;
  int32_t  outdataOffset, maxChIdx = 0;
  int32_t i2, i3, i6, i7, i8;
  *min = FLT_MAX;
  *max = -FLT_MAX;

  for (i8 = 0; i8 < numBatches; i8++)
  {
    for (i7 = 0; i7 < numGroups; i7++)   // for depthwise channels in TIDL_refConv2dKernel, numInChannels = numOutChannels = 1, main iteration on numGroups
    {
      outdataOffset = i7*numOutChannels*outChPitch + i8*outBatchPitch;
      accScale = perChannelWeightScalePtr[i7] * tensorScale;
      for (i6 = 0; i6 < numOutChannels; i6++)    // numOutChannels = params->numOutChannels / params->numGroups
      {
        for (i2 = 0; i2 < (height); i2 += strideHeight)
        {
          for (i3 = 0; i3 < (width); i3 += strideWidth)
          {
            inDataVal = accPtr[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)];
            inDataFloat = inDataVal / accScale;
            *max = (inDataFloat > *max) ? inDataFloat : *max;
            *min = (inDataFloat < *min) ? inDataFloat : *min;
          }
        }
      }

      if (fabs(*max) > absMax)
      {
        absMax = fabs(*max);
        maxChIdx = i7;
      }
      if (fabs(*min) > absMax)
      {
        absMax = fabs(*min);
        maxChIdx = i7;
      }
    }
  }
  return perChannelWeightScalePtr[maxChIdx];
}
/**
 * @brief  This is the reference conv2d core Kernel implementation
 *
 * @param numBatches  : no of total batches
 * @param numGroups : total no of groups
 * @param numInChannels : no of input channles
 * @param numOutChannels :  no of output channles
 * @param inChPitch : Channel pitch of the input buffer
 * @param outChPitch : Channel pitch of the output buffer
 * @param width : Width of the input buffer
 * @param height : Height of the input buffer
 * @param inImPitch : line pitch of the input buffer
 * @param outImPitch : line pitch of the output buffer
 * @param coeffsWidth : width of the coeff buffer
 * @param coeffsHeight : height of the coeff buffer
 * @param dilationWidth : Dilation in the width dimension
 * @param dilationHeight: Dilation in the height dimension
 * @param strideWidth : Stride in width dimension
 * @param strideHeight: Stride in height dimension
 * @param enableBias : Flag to indicate if bias in enabled
 */
template <class Tin, class Tw, class Tb, class Tacc>
void TIDL_refConv2dKernel(
  Tin*     pInChannel,
  Tw*      pCoeffs,
  Tb*      pBias,
  Tacc *   accPtr,
  Tacc *   min,
  Tacc *   max,
  int32_t  numBatches, // N
  int32_t  numGroups, //G
  int32_t  numInChannels, //Ci
  int32_t  numOutChannels, //Co
  int32_t  inChPitch, //CiStride
  int32_t  outChPitch, //CoStide
  uint32_t inBatchPitch, //BatchStride
  uint32_t outBatchPitch, //BatchStide
  int32_t  width, // Wi
  int32_t  height, // Hi
  int32_t  inImPitch, //HiStride
  int32_t  outImPitch, //HoStride
  int32_t  coeffsWidth, //KW
  int32_t  coeffsHeight, //KH
  int32_t  dilationWidth, //DW
  int32_t  dilationHeight, //DH
  int32_t  strideWidth, //SW S[0]
  int32_t  strideHeight, //SH S[1]
  int32_t  enableBias,
  int32_t isOTFpad,
  int32_t leftPad,
  int32_t topPad,
  int32_t padVal,
  int32_t startRowNumberInTensor,
  int32_t orgInTensorHeight
  )
{

  int32_t   i0, i2, i3, i4, i5, i6, i7, i8;
  int32_t   coeffOffset, indataOffset, outdataOffset;
  Tacc      outAcc;
  Tin       inData;
  Tw        coefData;
  Tb        biasData;
  int32_t isBorderPixel;
  int32_t validPosXMin,validPosXMax,validPosYMin,validPosYMax;
  int32_t spatialOffsetY, spatialOffsetX;
  //Setting the parameters marking for pixels on borders
  validPosXMin = leftPad;
  validPosXMax = leftPad + width;
  validPosYMin = topPad;
  validPosYMax = topPad + orgInTensorHeight;

  for (i8 = 0; i8 < numBatches; i8++)
  {
    for (i7 = 0; i7 < numGroups; i7++)
    {
      indataOffset = i7*numInChannels*inChPitch + i8*inBatchPitch;
      outdataOffset = i7*numOutChannels*outChPitch + i8*outBatchPitch;
      for (i6 = 0; i6 < numOutChannels; i6++)
      {
        if(enableBias)
        {
          biasData = pBias[i7*numOutChannels + i6];
        }
        else
        {
          biasData = 0;
        }
        for (i2 = 0; i2 < (height); i2 += strideHeight)
        {
          for (i3 = 0; i3 < (width); i3 += strideWidth)
          {
            outAcc = biasData;
            for (i0 = 0; i0 < numInChannels; i0++)
            {
              coeffOffset = i7*numInChannels * coeffsHeight * coeffsWidth *numOutChannels + \
                i6* numInChannels * coeffsHeight * coeffsWidth + i0 * coeffsHeight * coeffsWidth;
              for (i4 = 0; i4 < coeffsHeight; i4++)
              {
                for (i5 = 0; i5 < coeffsWidth; i5++)
                {
                  spatialOffsetY = i2+(i4*dilationHeight);
                  spatialOffsetX = i3+(i5*dilationWidth);
                  isBorderPixel = TIDL_checkPixelInPadRegion(spatialOffsetY + startRowNumberInTensor, spatialOffsetX, validPosXMin, validPosXMax, validPosYMin, validPosYMax); 
                  if(isBorderPixel & isOTFpad)
                  {
                    inData = padVal;
                  }
                  else{
                    inData = pInChannel[indataOffset + i0* inChPitch + ((i2)* inImPitch) + i3 +
                    (i4 * inImPitch*dilationHeight) + i5*dilationWidth];
                  }          
                  coefData = pCoeffs[coeffOffset + (i4 * coeffsWidth) + i5];
                  outAcc += (inData * coefData);
                }
              }
            }
            *min = outAcc < *min ? outAcc : *min;
            *max = outAcc > *max ? outAcc : *max;
            accPtr[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)] = outAcc;
          }
        }
      }
    }
  }
}

/**
 * @brief  This is the reference conv2d core Kernel implementation
 *
 * @param numBatches  : no of total Batches
 * @param numGroups : total no of groups
 * @param numInChannels : no of input channles
 * @param numOutChannels :  no of output channles
 * @param inChPitch : Channel pitch of the input buffer
 * @param outChPitch : Channel pitch of the output buffer
 * @param width : Width of the input buffer
 * @param height : Height of the input buffer
 * @param inImPitch : line pitch of the input buffer
 * @param outImPitch : line pitch of the output buffer
 * @param coeffsWidth : width of the coeff buffer
 * @param coeffsHeight : height of the coeff buffer
 * @param dilationWidth : Dilation in the width dimension
 * @param dilationHeight: Dilation in the height dimension
 * @param strideWidth : Stride in width dimension
 * @param strideHeight: Stride in height dimension
 * @param enableBias : Flag to indicate if bias in enabled
 */
template <int Ksize, class Tin, class Tw, class Tb, class Tacc>
void TIDL_refConv2dKernelFast(
  Tin*     pInChannel,
  Tw*      pCoeffs,
  Tb*      pBias,
  Tacc *   accPtr,
  Tacc *   min,
  Tacc *   max,
  int32_t  numBatches, // N
  int32_t  numGroups, //G
  int32_t  numInChannels, //Ci
  int32_t  numOutChannels, //Co
  int32_t  inChPitch, //CiStride
  int32_t  outChPitch, //CoStide
  int32_t  inBatchPitch, //BatchStride
  int32_t  outBatchPitch, //BatchStide
  int32_t  width, // Wi
  int32_t  height, // Hi
  int32_t  inImPitch, //HiStride
  int32_t  outImPitch, //HoStride
  int32_t  coeffsWidth, //KW
  int32_t  coeffsHeight, //KH
  int32_t  dilationWidth, //DW
  int32_t  dilationHeight, //DH
  int32_t  strideWidth, //SW S[0]
  int32_t  strideHeight, //SH S[1]
  int32_t enableBias,
  int32_t isOTFpad,
  int32_t leftPad,
  int32_t topPad,
  int32_t padVal,
  int32_t startRowNumberInTensor,
  int32_t orgInTensorHeight
  )
{

  int32_t   i0, i2, i3, i4, i5, i6, i7, i8;
  int32_t   coeffOffset, indataOffset, outdataOffset;
  Tacc      outAcc;
  Tin       inData;
  Tw        coefData;
  Tb        biasData;
  int32_t isBorderPixel;
  int32_t validPosXMin,validPosXMax,validPosYMin,validPosYMax;
  int32_t spatialOffsetY, spatialOffsetX;
  //Setting the parameters marking for pixels on borders
  validPosXMin = leftPad;
  validPosXMax = leftPad + width;
  validPosYMin = topPad;
  validPosYMax = topPad + orgInTensorHeight;

  for (i8 = 0; i8 < numBatches; i8++)
  {
    for (i7 = 0; i7 < numGroups; i7++)
    {
      indataOffset = i7*numInChannels*inChPitch + i8*inBatchPitch;
      outdataOffset = i7*numOutChannels*outChPitch + i8*outBatchPitch;
      for (i6 = 0; i6 < numOutChannels; i6++)
      {
        if(enableBias)
        {
          biasData = pBias[i7*numOutChannels + i6];
        }
        else
        {
          biasData = 0;
        }
        for (i2 = 0; i2 < (height); i2 += strideHeight)
        {
          for (i3 = 0; i3 < (width); i3 += strideWidth)
          {
            outAcc = biasData;
            for (i0 = 0; i0 < numInChannels; i0++)
            {
              coeffOffset = i7*numInChannels * coeffsHeight * coeffsWidth *numOutChannels + \
                i6* numInChannels * coeffsHeight * coeffsWidth + i0 * coeffsHeight * coeffsWidth;
              for (i4 = 0; i4 < Ksize; i4++)
              {
                for (i5 = 0; i5 < Ksize; i5++)
                {
                  spatialOffsetY = i2+(i4*dilationHeight);
                  spatialOffsetX = i3+(i5*dilationWidth);
                  isBorderPixel = TIDL_checkPixelInPadRegion(spatialOffsetY + startRowNumberInTensor, spatialOffsetX, validPosXMin, validPosXMax, validPosYMin, validPosYMax); 
                  if(isBorderPixel & isOTFpad)
                  {
                    inData = padVal;
                  }
                  else{
                    inData = pInChannel[indataOffset + i0* inChPitch + ((i2)* inImPitch) + i3 + (i4 * inImPitch*dilationHeight) + i5*dilationWidth];
                  }            
                  coefData = pCoeffs[coeffOffset + (i4 * coeffsWidth) + i5];
                  outAcc += (inData * coefData);
                }
              }
            }
            *min = outAcc < *min ? outAcc : *min;
            *max = outAcc > *max ? outAcc : *max;
            accPtr[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)] = outAcc;
          }
        }
      }
    }
  }
}

#ifdef BUILD_WITH_CUDA
int CUDNNLC;
#endif

/**
 * @brief  This funciton does the quant and saturation of the accumulator data
 *
 * @param pInChannel : Input pointer on which conv is applied
 * @param pCoeffs : Pointer to weights buffer
 * @param pBias  : Pointer to the Bias values
 * @param pOutChanne : Pointer to output after Conv opreation
 * @param accPtr : Pointer to store intermidiate accumulator values
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param params : copy of conv parameters
 * @param buffParams : copy of conv buffer parameters
 * @param satLow : min value for the saturation
 * @param satHigh : max value for the saturation
 */
template <class Tin, class Tw, class Tb, class Tout, class Tacc>
void TIDL_refConv2d(
  Tin*    pInChannel,
  Tw*     pCoeffs,
  Tb*     pBias,
  Tout*   pOutChanne,
  Tacc *   accPtr,
  TIDL_Handle   intAlgHandle,
  int32_t layerIdx,
  sTIDL_ConvParams_t * params,
  tidlConv2dBuffParams_t *buffParams,
  sTIDL_AlgLayer_t     * algLayer)
{
  sTIDL_Network_t * net = intAlgHandle->createParams->net;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  sTIDL_Layer_t * tidlLayer = &net->TIDLLayers[layerIdx];
  uint16_t numInChannels = params->numInChannels / params->numGroups;
  uint16_t numOutChannels = params->numOutChannels / params->numGroups;
  uint16_t coeffsWidth = params->kernelW;
  uint16_t coeffsHeight = params->kernelH;
  uint16_t strideWidth = params->strideW;
  uint16_t strideHeight = params->strideH;
  uint16_t dilationWidth = params->dilationW;
  uint16_t dilationHeight = params->dilationH;
  uint16_t p_w = (params->padL < params->padR)?params->padR:params->padL;
  uint16_t p_h = (params->padT < params->padB)?params->padB:params->padT;
  uint16_t width = (((buffParams->inWidth + (p_w * 2) - ((coeffsWidth - 1) * dilationWidth + 1)) / strideWidth) + 1)*strideWidth;
  uint16_t height = (((buffParams->inHeight + (p_h * 2) - ((coeffsHeight - 1)* dilationHeight + 1)) / strideHeight) + 1)*strideHeight;
  uint16_t inImPitch = buffParams->inPitch;
  uint32_t inChPitch = buffParams->inChPitch;
  uint32_t inBatchPitch = buffParams->inBatchPitch;
  uint16_t outImPitch = buffParams->outPitch;
  uint32_t outChPitch = buffParams->outChPitch;
  uint32_t outBatchPitch = buffParams->outBatchPitch;
  uint8_t outRoundBits = (params->inDataQ + params->weightsQ - params->outDataQ);
  int32_t  numBatches = buffParams->numTotRoi;
  uint16_t numGroups = params->numGroups;
  void * perChannelWeightScalePtr = ((int8_t *)(intAlgHandle->createParams->net) + params->perChannelWeightScaleOffset);
  sTIDL_DataParams_t * indata = TIDL_getDataParams(net, net->TIDLLayers[layerIdx].inData[0]);
  float32_tidl tensorScale = indata->tensorScale;

  int32_t    i2, i3, i6, i8;
  Tacc      outAcc;
  int32_t   outdataOffset;
  Tacc      min, max;
  int64_t   temp;
  int32_t accMemSize = outBatchPitch*numBatches*sizeof(Tacc);

  int32_t padVal = 0;
  int32_t leftPad = 0, topPad = 0;
  if(TIDL_isPadOTF( net->deviceName))
  {
    leftPad = params->padL;
    topPad = params->padT;
    width = buffParams->inWidth;
    height = buffParams->inHeight;
  }
  int32_t orgInTensorHeight = buffParams->inHeight;
  if(algLayer->procType != 0U)
  {
    orgInTensorHeight = algLayer->layerParams.convParams.orgInTensorHeight;
  }

  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    params->enableBias = 1;//Always need bias for asymmetric quant
    padVal = indata->tensorZeroPoint;
  }

  if ((buffParams->quantizationStyle == TIDL_QuantStyleNP2Fixed) || (buffParams->quantizationStyle == TIDL_QuantStyleP2Dynamic))
  {
    outRoundBits = buffParams->secondRoundBits;
  }
  min = (Tacc)((((uint64_t)1)<< ((sizeof(Tacc)*8)-1)) - 1);
  temp = (int64_t)(((uint64_t)1) << ((sizeof(Tacc) * 8) - 1));
  max = (Tacc)temp*-1;

  if (buffParams->scratchSize >= accMemSize)
  {
    accPtr = (Tacc *)buffParams->scratchMem;
    accPtr += indata->padH*buffParams->outPitch + indata->padW;
  }
  else
  {
    tidl_printf(0,"Memory for  TIDL_refConv2d accumulator is not sufficient exiting...\n    ");
    exit(-1);
  }
  if (net->TIDLLayers[layerIdx].strideOffsetMethod != TIDL_StrideOffsetTopLeft)
  {
    /* Line 94 : /tensorflow/core/kernels/quantized_conv_ops.cc*/
    int32_t effectiveKw = ((coeffsWidth - 1)*dilationWidth) + 1;
    int32_t effectiveKh = ((coeffsHeight - 1)*dilationHeight) + 1;
    int32_t filter_left_offset =
      ((net->TIDLLayers[layerIdx].outData.dimValues[3] - 1) * strideWidth + effectiveKw - buffParams->inWidth) / 2;
    int32_t filter_top_offset =
      ((net->TIDLLayers[layerIdx].outData.dimValues[2] - 1) * strideHeight + effectiveKh - buffParams->inHeight) / 2;

    pInChannel = pInChannel + ((effectiveKh / 2)*inImPitch + (effectiveKw / 2));

    pInChannel = pInChannel - (filter_top_offset*inImPitch + filter_left_offset);
  }

#ifdef BUILD_WITH_CUDA
  CUDNNLC = layerIdx;
  TIDL_cudaConvolve2d(pInChannel, pCoeffs, pBias, accPtr, &min, &max, numBatches, numGroups, numInChannels,
                        numOutChannels, inChPitch, outChPitch, width, height, inImPitch, outImPitch,
                        coeffsWidth, coeffsHeight, dilationWidth, dilationHeight, strideWidth, strideHeight);
#else
#if defined(_HOST_BUILD)
    if(((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_AVX_REF) == TIDL_FLOW_CTRL_AVX_REF) &&
      ((strideWidth == 1) && (strideHeight == 1) ) &&
       ((dilationWidth == 1) && (dilationHeight == 1) ) &&
       (typeid(Tw) != typeid(float32_tidl)) && (sizeof(Tw) == 1) && (sizeof(Tin) == 1) &&
       (inImPitch == outImPitch) && (TIDL_isPadOTF( net->deviceName) == 0))
    {
       TIDL_refConv2dKernelAvxProc(pInChannel, pCoeffs, pBias, accPtr, &min, &max, numGroups, numInChannels,
                                   numOutChannels, inChPitch, outChPitch, width, height, inImPitch, coeffsWidth, coeffsHeight, params->enableBias);
    }
    else
#endif
    if ((coeffsWidth == 1) && (coeffsHeight == 1))
    {
      TIDL_refConv2dKernelFast<1, Tin, Tw, Tb, Tacc>(pInChannel, pCoeffs, pBias, accPtr, &min, &max, numBatches, numGroups, numInChannels,
        numOutChannels, inChPitch, outChPitch, inBatchPitch, outBatchPitch, width, height, inImPitch, outImPitch,
        coeffsWidth, coeffsHeight, dilationWidth, dilationHeight, strideWidth, strideHeight, params->enableBias, TIDL_isPadOTF( net->deviceName), leftPad, topPad, padVal, algLayer->layerParams.convParams.startRowNumberInTensor, orgInTensorHeight);
    }
    else
    if ((coeffsWidth == 3) && (coeffsHeight == 3))
    {
      TIDL_refConv2dKernelFast<3, Tin, Tw, Tb, Tacc>(pInChannel, pCoeffs, pBias, accPtr, &min, &max, numBatches, numGroups, numInChannels,
        numOutChannels, inChPitch, outChPitch, inBatchPitch, outBatchPitch, width, height, inImPitch, outImPitch,
        coeffsWidth, coeffsHeight, dilationWidth, dilationHeight, strideWidth, strideHeight, params->enableBias, TIDL_isPadOTF( net->deviceName), leftPad, topPad, padVal, algLayer->layerParams.convParams.startRowNumberInTensor, orgInTensorHeight);
    }
    else
    {
      TIDL_refConv2dKernel(pInChannel, pCoeffs, pBias, accPtr, &min, &max, numBatches, numGroups, numInChannels,
        numOutChannels, inChPitch, outChPitch, inBatchPitch, outBatchPitch, width, height, inImPitch, outImPitch,
        coeffsWidth, coeffsHeight, dilationWidth, dilationHeight, strideWidth, strideHeight, params->enableBias, TIDL_isPadOTF( net->deviceName), leftPad, topPad, padVal, algLayer->layerParams.convParams.startRowNumberInTensor, orgInTensorHeight);
    }
#endif /*BUILD_WITH_CUDA*/
  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    if(isPerChannelQuantizationEnabled(params,net->calibrationOption) == 1)
    {
      float32_tidl accMinFloat = FLT_MAX;
      float32_tidl accMaxFloat = -FLT_MAX;
      /* Find accMin and accMax in float and the weight scale of the channel with absolute max value */
      float32_tidl accMaxWeightScale = TIDL_findMinMaxForChQuant(accPtr, numBatches, numGroups, numInChannels, numOutChannels, outBatchPitch, outChPitch, outImPitch, width, height,
      strideHeight, strideWidth, (float32_tidl *)perChannelWeightScalePtr, tensorScale, &accMinFloat, &accMaxFloat);
      /* convert accMinFloat and accMaxFloat to the scale of channel with the absolute max value */
      min = (Tacc)(accMinFloat * (accMaxWeightScale * tensorScale));
      max = (Tacc)(accMaxFloat * (accMaxWeightScale * tensorScale));
      net->TIDLLayers[layerIdx].layerParams.convParams.weightScale = accMaxWeightScale;
    }
    if (TIDL_getDatElementSign(net->TIDLLayers[layerIdx].outData.elementType) == 1)
    {
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, min, max);
    }
    else
    {
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, max);
    }
  }

  outRoundBits = net->TIDLLayers[layerIdx].outData.roundBits;
  if (typeid(Tin) == typeid(float32_tidl))
  {
    outRoundBits = 0;
  }

  uint8_t * roundBitsPtr = (uint8_t *)(&outRoundBits);
  int32_t enablePerChannelShift = 0;
  if(isPerChannelQuantizationEnabled(params,net->calibrationOption) == 1)
  {
    int32_t chIdx;
    float32_tidl perChannelAccScale;
    float32_tidl * perChannelWeightScalePtr =
            (float32_tidl *)get_int8_t_pointer((int8_t *)(net), params->perChannelWeightScaleOffset);
    roundBitsPtr = (uint8_t *)(buffParams->outRoundBitsPtr);
    if ( indata->tensorScale != 0 )
    {
      for(chIdx = 0; chIdx < params->numInChannels; chIdx++)
      {
        perChannelAccScale = perChannelWeightScalePtr[chIdx] * indata->tensorScale;
        roundBitsPtr[chIdx] = (int8_t)(log((float32_tidl)perChannelAccScale /
                               net->TIDLLayers[layerIdx].outData.tensorScale)/log(2.0));
      }
    }
    enablePerChannelShift = 1;
  }


  int32_t satLow;
  int32_t satHigh;
  int32_t mixedPrecision = 0;

  TIDL_getSaturationLimits(buffParams->outElementType, &satLow, &satHigh);


  /* If size of weights is not same as size of output then it indicates
  mixed precision */
  if ( sizeof(*pCoeffs) != sizeof(*pOutChanne))
  {
    mixedPrecision = 1;
    /* This is to match with target implementation wherin the saturations
    happens after applying outRoundBits - 8 shift and then the right shift
    of 8 is applied */
    outRoundBits = outRoundBits - 8;
    if ( buffParams->outElementType == TIDL_SignedChar )
    {
      TIDL_getSaturationLimits(TIDL_SignedShort, &satLow, &satHigh);
    }
    else
    {
      TIDL_getSaturationLimits(TIDL_UnsignedShort, &satLow, &satHigh);
    }

  }

#ifdef BUILD_WITH_CUDA
  int32_t sizeOstream = numBatches*outBatchPitch;
  Tout *devPtrOf;
  int32_t precisionAdjustmentShift = 0;
  if (mixedPrecision == 1)
  {
    precisionAdjustmentShift = 8;
  }

  if(typeid(Tin) == typeid(float32_tidl))
  {
    float32_tidl fmin, fmax;
    TIDL_getSaturationFloat(&net->TIDLLayers[layerIdx],&fmin,&fmax);
    TIDL_cudaSaturateV1(&devPtrOf, numBatches, params->numOutChannels, height / strideHeight, width / strideWidth, outChPitch, outImPitch, outRoundBits, fmin, fmax);//Performing Saturation for float
  }
  else
  {
    TIDL_cudaSaturateFixedPoint<Tacc,Tout>(&devPtrOf, numBatches, params->numOutChannels, height / strideHeight, width / strideWidth, outChPitch, outImPitch, roundBitsPtr, satLow, satHigh, enablePerChannelShift, precisionAdjustmentShift);//Performing Saturation for Fixed Point
  }

  TIDL_cudaOutputTx( devPtrOf, sizeOstream, numBatches, params->numOutChannels, height, width, outChPitch, outImPitch, strideHeight, strideWidth, pOutChanne); //Performing Tx of output stream
#else


  int64_t tempAcc;
  uint8_t* mmav2_Scales = (uint8_t*) algLayer->layerParams.convParams.mmaScalesPtr;
  uint8_t* mmav2_Shifts = (uint8_t*) algLayer->layerParams.convParams.mmaShiftsPtr;

  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    for (i8 = 0; i8 < numBatches; i8++)
    {
      outdataOffset = i8*outBatchPitch;
      for (i6 = 0; i6 < params->numOutChannels; i6++)
      {
        if (enablePerChannelShift == 1)
        {
          outRoundBits = roundBitsPtr[i6];
        }
        for (i2 = 0; i2 < (height); i2 += strideHeight)
        {
          for (i3 = 0; i3 < (width); i3 += strideWidth)
          {
            outAcc = accPtr[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)];
            outAcc = outAcc;
            if (tidlLayer->outData.elementType == TIDL_SinglePrecFloat)
            {
              outAcc = TIDL_floatSat(outAcc, &net->TIDLLayers[layerIdx]);
            }
            else
            {
              tempAcc = (int64_t)outAcc * mmav2_Scales[i6]; //Replace this with an array indexed by outChannel
              outAcc  = (Tacc)TIDL_roundSatMMA(tempAcc, mmav2_Shifts[i6], buffParams->mmaPSATMin, buffParams->mmaPSATMax);
              if(typeid(Tin) == typeid(int8_t) || typeid(Tin) == typeid(uint8_t))
              {
              outAcc = ((int64_t)outAcc & (int64_t)0xFFFFFFFFFF); //Only 40 bits are valid in the accumulator..
              }
              if ( mixedPrecision == 1 ) //Invalid for Asymmetric currently
              {
                outAcc = (int64_t)outAcc >> 8;
              }
            }
            pOutChanne[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)] = outAcc;
          }
        }
      }
    }
  }
  else
  {
    for (i8 = 0; i8 < numBatches; i8++)
    {
      outdataOffset = i8*outBatchPitch;
      for (i6 = 0; i6 < params->numOutChannels; i6++)
      {
        if (enablePerChannelShift == 1)
        {
          outRoundBits = roundBitsPtr[i6];
        }
        for (i2 = 0; i2 < (height); i2 += strideHeight)
        {
          for (i3 = 0; i3 < (width); i3 += strideWidth)
          {
            outAcc = accPtr[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)];
            outAcc = outAcc;
            if (tidlLayer->outData.elementType == TIDL_SinglePrecFloat)
            {
              outAcc = TIDL_floatSat(outAcc, &net->TIDLLayers[layerIdx]);
            }
            else
            {

              outAcc = (Tacc)TIDL_roundSatMMA((int64_t)outAcc, outRoundBits, satLow, satHigh);

              if ( mixedPrecision == 1 )
              {
                outAcc = (int64_t)outAcc >> 8;
              }
            }
            pOutChanne[outdataOffset + i6 * outChPitch + ((i2 / strideHeight) * outImPitch) + (i3 / strideWidth)] = outAcc;
          }
        }
      }
    }
  }
#endif /*BUILD_WITH_CUDA*/
}

/**
 * @brief  This funciton handles differnt input bit-depths for Conv reference
 *
 * @param inPtr : Input pointer on which Deconv is applied
 * @param refPtr : Pointer to output after DeConv opreation
 * @param wgtPtr : Pointer to weights buffer
 * @param biasPtr  : Pointer to the Bias values
 * @param accPtr : Pointer to store intermidiate accumulator values
 * @param intAlgHandle : tidl algorothm handle
 * @param layerIdx :index of the current layer
 * @param params : copy of Deconv parameters
 * @param buffParams : copy of Deconv buffer parameters
 * @param inElementType : ElementType of the input
 * @param inDataOffset : initial offest the input data buffer
 * @param outDataOffset : initial offset of the output data buffer
 * @return  None
 */
template <class Tw, class Tb, class Tacc>
void TIDL_refConv2dBitDepth(
  void * inPtr,
  void * refPtr,
  Tw   * wgtPtr,
  Tb   * biasPtr,
  Tacc * accPtr,
  TIDL_Handle intAlgHandle,
  int32_t layerIdx,
  sTIDL_ConvParams_t     * params,
  tidlConv2dBuffParams_t *buffParams,
  int32_t inElementType,
  int32_t inDataOffset,
  int32_t outDataOffset,
  sTIDL_AlgLayer_t     * algLayer)
{

  if (inElementType == TIDL_SinglePrecFloat)
  {
    TIDL_refConv2d(
            ((float32_tidl *)inPtr + inDataOffset),
            (float32_tidl *)wgtPtr,
            (float32_tidl *)biasPtr,
            (((float32_tidl *)refPtr) + outDataOffset),
            (float32_tidl *)accPtr,
            intAlgHandle, layerIdx, params, buffParams, algLayer);
  }
  else if ( buffParams->inElementType == TIDL_SignedChar)
  {
    if ( buffParams->outElementType == TIDL_SignedChar )
    {
      TIDL_refConv2d(
      ((int8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedChar )
    {
      TIDL_refConv2d(
      ((int8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_SignedShort )
    {
      TIDL_refConv2d(
      ((int8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedShort )
    {
      TIDL_refConv2d(
      ((int8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
  }
  else if ( buffParams->inElementType == TIDL_UnsignedChar)
  {
    if ( buffParams->outElementType == TIDL_SignedChar )
    {
      TIDL_refConv2d(
      ((uint8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedChar )
    {
      TIDL_refConv2d(
      ((uint8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_SignedShort )
    {
      TIDL_refConv2d(
      ((uint8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedShort )
    {
      TIDL_refConv2d(
      ((uint8_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
  }
  else if ( buffParams->inElementType == TIDL_SignedShort)
  {
    if ( buffParams->outElementType == TIDL_SignedChar )
    {
      TIDL_refConv2d(
      ((int16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedChar )
    {
      TIDL_refConv2d(
      ((int16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_SignedShort )
    {
      TIDL_refConv2d(
      ((int16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedShort )
    {
      TIDL_refConv2d(
      ((int16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
  }
  else if ( buffParams->inElementType == TIDL_UnsignedShort)
  {
    if ( buffParams->outElementType == TIDL_SignedChar )
    {
      TIDL_refConv2d(
      ((uint16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedChar )
    {
      TIDL_refConv2d(
      ((uint16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint8_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_SignedShort )
    {
      TIDL_refConv2d(
      ((uint16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((int16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
    else if ( buffParams->outElementType == TIDL_UnsignedShort )
    {
      TIDL_refConv2d(
      ((uint16_t *)inPtr + inDataOffset),
      wgtPtr,
      biasPtr,
      ((uint16_t *)refPtr + outDataOffset),
      accPtr,
      intAlgHandle, layerIdx, params, buffParams, algLayer);
    }
  }
  else
  {
    //:TODO: ERROR condition
  }


}
/**
 * @brief Function to check if perChannelQuantizationEnabled
 *
 * @param convParams : conv layer parameters
 * @param calibrationOption : indicates calibration Options
 * @return : PerChannelQuantization Enabled or not
 */
int32_t isPerChannelQuantizationEnabled(const sTIDL_ConvParams_t * convParams,
                                                 int32_t calibrationOption)
{
  int32_t isEnabled = 0;

  if(((convParams->numInChannels/convParams->numGroups == 1) &&
    (convParams->numOutChannels/convParams->numGroups == 1)) &&
    (( calibrationOption & TIDL_CalibOptionPerChannelWeightQuantization) ==
       TIDL_CalibOptionPerChannelWeightQuantization ))
  {
    isEnabled = 1;
  }
  return isEnabled;
}

/**
 * @brief Convolution layer reference implementation
 *
 * @param intAlgHandle : tidl algorothm handle
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : copy of conv layer parameters
 * @param buffParams : copy of conv buffer parameters
 * @param inPtr : Pointer to input buffers to be processed
 * @param outPtr : Pointer to output buffers to be processed
 * @param inElementType : ElementType of the input
 * @param numBatches : total no of batches
 * @param sysMems : sysMem Handle
 * @return  IALG_EOK   - Successful
 *          IALG_EFAIL - Unspecified error
 */
int32_t TIDL_refConv2dProcess(
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * tidlLayer,
  sTIDL_ConvParams_t * params,
  tidlConv2dBuffParams_t *buffParams,
  void *inPtr,
  void *outPtr,
  int32_t inElementType,
  uint16_t numBatches,
  sTIDL_sysMemHandle_t * sysMems)
{

  uint16_t numOutChs = params->numOutChannels / params->numGroups;
  uint16_t k_w = params->kernelW;
  uint16_t k_h = params->kernelH;
  uint16_t s_w = params->strideW;
  uint16_t s_h = params->strideH;
  uint16_t dilation_w = params->dilationW;
  uint16_t dilation_h = params->dilationH;
  uint16_t p_w = (params->padL < params->padR)?params->padR:params->padL;
  uint16_t p_h = (params->padT < params->padB)?params->padB:params->padT;
  uint16_t imWidth = (((buffParams->inWidth + (p_w * 2) - ((k_w - 1)* dilation_w + 1)) / s_w) + 1)*s_w;
  uint16_t imHeight = (((buffParams->inHeight + (p_h * 2) - ((k_h - 1)* dilation_h + 1)) / s_h) + 1)*s_h;
  uint16_t inPitch = buffParams->inPitch;
  uint16_t outPitchPooling = buffParams->outPitchPooling;
  int16_t  outRefPitch = 0;
  int32_t  status = IALG_EOK;
  uint16_t avgPoolingRoundBits;
  int32_t  inChPitchPooling, outChPitchPooling;
  int32_t  j;
  int32_t outWidth, outHeight;
  uint8_t   *refPtr;
  uint8_t   *refPtrMerged;
  int32_t  inDataOffset;
  int32_t  outDataOffset;
  int32_t layerIdx;
  void * biasptr;
  int16_t * orgbiasptr;
  float32_tidl * orgbiasptrfloat;
  void * accPtr = NULL;
  int32_t outRefChPitch;
  int32_t padH, padW;
  int32_t upscaleFactor = 1;

  sTIDL_Network_t * net = intAlgHandle->createParams->net;
  int32_t quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  void * weightPtr = ((int8_t *)(intAlgHandle->createParams->net) + params->weights);
  void * biasPtr = ((int8_t *)(intAlgHandle->createParams->net) + params->bias);
  sTIDL_DataParams_t * inDataParams  =  &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;

  layerIdx = algLayer->layerIdx;

  outWidth = s_w > 1 ? ((imWidth + 1) / s_w) : imWidth;
  outHeight = s_h > 1 ? ((imHeight + 1) / s_h) : imHeight;

  padW = net->TIDLLayers[layerIdx].outData.padW;
  padH = net->TIDLLayers[layerIdx].outData.padH;


  outPitchPooling   = buffParams->outPitchPooling;
  outChPitchPooling = buffParams->outChPitch;

  if (params->enablePooling == TRUE)
  {
    refPtrMerged = (uint8_t *)outPtr;
    refPtr = (uint8_t *)algLayer->scratchMem;
    outRefPitch = outWidth + padW;
    outRefChPitch = outRefPitch*((outHeight)+2 * padH + 1);
    buffParams->outPitch    = outRefPitch;
    buffParams->outChPitch = outRefChPitch;

  }
  else if (params->enableDepthToSpace == TRUE)
  {
    refPtrMerged = (uint8_t *)outPtr;
    refPtr = (uint8_t *)algLayer->scratchMem;
    upscaleFactor = params->upscaleFactor;
    outRefPitch = (outWidth) + padW;
    outRefChPitch = outRefPitch*((outHeight)+2 * padH + 1);
    buffParams->outPitch    = outRefPitch;
    buffParams->outChPitch = outRefChPitch;
  }
  else
  {
    outRefPitch   = buffParams->outPitch;
    outRefChPitch = buffParams->outChPitch;
    refPtrMerged = (uint8_t *)outPtr;
    refPtr = (uint8_t *)outPtr;
  }

  orgbiasptr = (int16_t *)biasPtr;
  orgbiasptrfloat = (float32_tidl *)biasPtr;

  if(TIDL_QuantStyleAsymNP2_TFL != quantizationStyle)
  {
  #if USE_16BIT_BIAS_FOR_8BIT_MODE
    if (tidlLayer->weightsElementSizeInBits <= 8)
    {
      if (algLayer->layerParams.convParams.biasParamSize >= (params->numOutChannels*sizeof(int16_t)))
      {
        biasptr = (void *)algLayer->layerParams.convParams.biasParamMem;
      }
      else
      {
        tidl_printf(0,"Memory for  biasptr  is not sufficient exiting...\n    ");
        exit(-1);
      }

      if ( params->enableBias )
      {
        if(isPerChannelQuantizationEnabled(params,net->calibrationOption) == 1)
        {
          int32_t chIdx;
          float32_tidl inScaleFactor;
          float32_tidl * perChannelWeightScalePtr =
                  (float32_tidl *)get_int8_t_pointer((int8_t *)(net), params->perChannelWeightScaleOffset);

          int32_t biasB;
          for (chIdx = 0; chIdx < params->numOutChannels; chIdx++ )
          {
            inScaleFactor = (perChannelWeightScalePtr[chIdx] * inDataParams->tensorScale) / params->biasScale;
            TIDL_conv2dBiasSplit(orgbiasptr + chIdx,
                                              (int16_t*)biasptr + chIdx,
                                              &biasB,
                                              1,
                                              inScaleFactor,
                                              TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,
                                              0xFF,
                                              TIDL_getDatElementSign(inElementType));
            ((int16_t*)biasptr)[chIdx] = ((int16_t*)biasptr)[chIdx] * biasB;
          }
        }
        else
        {
          TIDL_conv2dBiasSplit(orgbiasptr, (int16_t*)biasptr, &params->biasB, params->numOutChannels, buffParams->inScaleFactor,
                                TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF, TIDL_getDatElementSign(inElementType));
          for (j = 0; j < params->numOutChannels; j++)
          {
            ((int16_t*)biasptr)[j] = ((int16_t*)biasptr)[j] * params->biasB;
          }
        }
      }
      else
      {
        params->biasB = 0;
        for (j = 0; j < params->numOutChannels; j++)
        {
          ((int16_t*)biasptr)[j] = ((int16_t*)biasptr)[j] * params->biasB;
        }
      }
    }
    else
  #endif
    {
      if (algLayer->layerParams.convParams.biasParamSize >= (params->numOutChannels*sizeof(int32_t)))
      {
        biasptr = (void *)algLayer->layerParams.convParams.biasParamMem;
      }
      else
      {
        tidl_printf(0,"Memory for  biasptr  is not sufficient exiting...\n    ");
        exit(-1);
      }

      if ( params->enableBias )
      {
        if(isPerChannelQuantizationEnabled(params,net->calibrationOption) == 1)
        {
          int chIdx;
          float32_tidl inScaleFactor;
          float32_tidl * perChannelWeightScalePtr =(float32_tidl *) ((int8_t *)(intAlgHandle->createParams->net) + params->perChannelWeightScaleOffset);
          sTIDL_DataParams_t * inDataParams  =
            &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;

          int32_t biasB;
          for ( chIdx = 0; chIdx < params->numOutChannels; chIdx++ )
          {
            inScaleFactor = (perChannelWeightScalePtr[chIdx] * inDataParams->tensorScale) / params->biasScale;
            TIDL_conv2dBiasSplit(orgbiasptr + chIdx,
                                          (int32_t*)biasptr + chIdx,
                                          &biasB,
                                          1,
                                          inScaleFactor,
                                          TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32,
                                          0xFFFF,
                                          TIDL_getDatElementSign(inElementType));
            ((int32_t*)biasptr)[chIdx] = ((int32_t*)biasptr)[chIdx] * biasB;
          }
        }
        else
        {
          int32_t maxBiasB = 0xFFFF;
          /* This condition indicates mixed precision where processing is in 16 bit but input is signed input.
          Here as target implementation scales the input with 256, we need to limit the biasB so that it doesn't
          go beyond 8 bits as the same is later multiplied by 256 to match the scale of accumulator*/
          if ( inElementType == TIDL_SignedChar )
          {
            maxBiasB = 0xFF;
          }
          TIDL_conv2dBiasSplit(orgbiasptr, (int32_t*)biasptr, &params->biasB, params->numOutChannels, buffParams->inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32,maxBiasB, TIDL_getDatElementSign(inElementType));
          for (j = 0; j < params->numOutChannels; j++)
          {
            ((int32_t*)biasptr)[j] = ((int32_t*)biasptr)[j] * params->biasB;
          }
        }
      }
      else
      {
        params->biasB = 0;
        for (j = 0; j < params->numOutChannels; j++)
        {
          ((int32_t*)biasptr)[j] = ((int32_t*)biasptr)[j] * params->biasB;
        }
        /* When bias is not enabled for a conv layer then the 
        original bias pointer in the net would not be pointing to zeros 
        refernce kenrls Implemenation expects zero for bias disabled case */
        orgbiasptrfloat = (float32_tidl *)biasptr;
      }
    }
  }
  else
  {
   biasptr = (int32_t *)algLayer->layerParams.convParams.biasParamMem;
  }

  avgPoolingRoundBits = 2;

  inDataOffset = (inDataParams->padH - p_h)*inPitch + (inDataParams->padW - p_w);
  outDataOffset = (padH)*outRefPitch + (padW);

  if (tidlLayer->weightsElementSizeInBits <= 8)
  {
    if (inElementType < 2)
    {
    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      buffParams->inElementType = 1;
      TIDL_refConv2dBitDepth(inPtr, refPtr, ((int8_t *)weightPtr), ((int32_t *)biasptr), ((int32_t *)accPtr), intAlgHandle, layerIdx, params, buffParams, inElementType, inDataOffset, outDataOffset, algLayer);
    }
    else
    {
  #if USE_16BIT_BIAS_FOR_8BIT_MODE
      TIDL_refConv2dBitDepth(inPtr, refPtr, ((int8_t *)weightPtr), ((int16_t *)biasptr), ((int32_t *)accPtr), intAlgHandle, layerIdx, params, buffParams, inElementType, inDataOffset, outDataOffset, algLayer);
  #else
      TIDL_refConv2dBitDepth(inPtr, refPtr, ((int8_t *)weightPtr), ((int32_t *)biasptr), ((int32_t *)accPtr), intAlgHandle, layerIdx, params, buffParams, inElementType, inDataOffset, outDataOffset, algLayer);
  #endif
    }
    }
    else
    {
      tidl_printf(0,"Element type > 1 is supported only if  weightsElementSizeInBits > 8 \n   ");
      assert(0);
    }
  }
  else if (tidlLayer->weightsElementSizeInBits <= 16)
  {
    TIDL_refConv2dBitDepth(inPtr, refPtr, ((int16_t *)weightPtr), ((int32_t *)biasptr), ((int64_t *)accPtr), intAlgHandle, layerIdx, params, buffParams, inElementType, inDataOffset, outDataOffset, algLayer);
  }
  else if (tidlLayer->weightsElementSizeInBits == 32)
  {
    TIDL_refConv2dBitDepth(inPtr, refPtr, (int8_t *)weightPtr, (int32_t *)orgbiasptrfloat, (int32_t *)accPtr, intAlgHandle, layerIdx, params, buffParams, inElementType, inDataOffset, outDataOffset, algLayer);
  }

  if (params->enablePooling == TRUE)
  {
    tidlConv2dPoolingParams_t poolParams;

    inChPitchPooling  = outRefChPitch;

    buffParams->outPitch   = outPitchPooling ;
    buffParams->outChPitch = outChPitchPooling;


    poolParams.width = outWidth;
    poolParams.height = outHeight;
    poolParams.inPitch = outRefPitch;
    poolParams.outPitch = outPitchPooling;
    poolParams.numOutChannels = numOutChs*params->numGroups;
    poolParams.roundBits = avgPoolingRoundBits;
    poolParams.inChPitch = inChPitchPooling;
    poolParams.outChPitch = outChPitchPooling;

    for (j = 0; j < numBatches; j++)
    {

      inDataOffset = (padH)*outRefPitch + (padW)+
        j*params->numGroups*numOutChs*outRefPitch*inChPitchPooling;
      outDataOffset = (padH)*outPitchPooling + (padW)+
        j*params->numGroups*numOutChs*outPitchPooling*outChPitchPooling;

      if ((buffParams->outElementType == TIDL_UnsignedChar) ||
       (buffParams->outElementType == TIDL_UnsignedShort))
      {
        if (params->poolParams.poolingType == TIDL_MaxPooling)
        {
          TIDL_refMaxPooling_2x2_skip2_cn(
            (refPtr + inDataOffset),
            (refPtrMerged + outDataOffset),
            &poolParams);
        }
        else if (params->poolParams.poolingType == TIDL_AveragePooling)
        {
          TIDL_refAvgPooling_2x2_skip2_cn(
            (refPtr + inDataOffset),
            (refPtrMerged + outDataOffset),
            &poolParams,
            (uint8_t)0,
            (uint8_t)255);
        }
      }
      else
      {
        if (params->poolParams.poolingType == TIDL_MaxPooling)
        {
          TIDL_refMaxPooling_2x2_skip2_cn(
            (((int8_t *)refPtr) + inDataOffset),
            (((int8_t *)refPtrMerged) + outDataOffset),
            &poolParams);
        }
        else if (params->poolParams.poolingType == TIDL_AveragePooling)
        {
          TIDL_refAvgPooling_2x2_skip2_cn(
            (((int8_t *)refPtr) + inDataOffset),
            (((int8_t *)refPtrMerged) + outDataOffset),
            &poolParams,
            (int8_t)-128,
            (int8_t)127);
        }
      }

    }

    outWidth = outWidth / 2;
    outHeight = outHeight / 2;
  }
  else if(params->enableDepthToSpace == TRUE)
  {
      inDataOffset = (padH)*outRefPitch + (padW);
      outDataOffset = (padH)*net->TIDLLayers[layerIdx].outData.pitch[TIDL_LINE_PITCH] + (padW);

      TIDL_refDepthToSpaceiX((void *)refPtr, (void *)refPtrMerged, inDataOffset, outDataOffset,
      net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_WIDTH],
      net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_HEIGHT],
      params->numOutChannels ,
      net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_BATCH],
      outRefPitch,
      net->TIDLLayers[layerIdx].outData.pitch[TIDL_LINE_PITCH],
      outRefChPitch,
      net->TIDLLayers[layerIdx].outData.pitch[TIDL_CHANNEL_PITCH],
      outRefChPitch*params->numOutChannels,
      net->TIDLLayers[layerIdx].outData.pitch[TIDL_CHANNEL_PITCH]*net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH],
      upscaleFactor,
      net->TIDLLayers[layerIdx].outData.elementType);
  }
  TIDL_enableL1DandL2CacheWb();
  return status;
}

/**
 * @brief Convolution layer Process function
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
int32_t TIDL_conv2dProcess(
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * tidlLayer,
  void                 * inPtrs[],
  void                 * outPtrs[],
  sTIDL_sysMemHandle_t * sysMems)
{

  sTIDL_ConvParams_t * params = &tidlLayer->layerParams.convParams;
  tidlConv2dBuffParams_t buffParams;
  sTIDL_DataParams_t *inDataParams;
  sTIDL_DataParams_t *outDataParams;

  uint16_t strideH = (uint16_t)params->strideH;
  uint16_t strideW = (uint16_t)params->strideW;
  void    *inPtr = inPtrs[0];
  uint8_t(*outPtr)[] = (uint8_t(*)[])outPtrs[0];
  uint16_t numBatches;
  uint32_t isRefExecRequired = 0;
  uint32_t isTargetExec = 0U;
  void * refInPtr;
  void * refOutPtr;
  void * targetInPtr;
  int32_t padW, padH;
  padW = (params->padL < params->padR)?params->padR:params->padL;
  padH = (params->padT < params->padB)?params->padB:params->padT;

  int32_t layerIdx;
  void * targetOutPtr;
  layerIdx = algLayer->layerIdx;
  int32_t status = 0;

  inDataParams  = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
  outDataParams = &tidlLayer->outData;
  numBatches    = inDataParams->dimValues[0]; /*Batches  */

  buffParams.inElementType = inDataParams->elementType;
  buffParams.outElementType = tidlLayer->outData.elementType;
  buffParams.inWidth = (uint16_t)inDataParams->dimValues[3];
  buffParams.inHeight = (uint16_t)inDataParams->dimValues[2];
  buffParams.outWidth = (((buffParams.inWidth + (padW * 2U)) - (((params->kernelW - 1U)* params->dilationW) + 1U)) / strideW) + 1U;
  buffParams.outHeight = (((buffParams.inHeight + (padH * 2U)) - (((params->kernelH - 1U)* params->dilationH) + 1U)) / strideH) + 1U;
  buffParams.inPitch = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
  buffParams.inChPitch = (uint32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  buffParams.outPitch = (uint16_t)outDataParams->pitch[TIDL_LINE_PITCH];
  buffParams.outChPitch = (uint32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  buffParams.outPitchPooling = (uint16_t)outDataParams->pitch[TIDL_LINE_PITCH];
  buffParams.outChPitchPooling = (uint32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  buffParams.actType = tidlLayer->actParams.actType;
  buffParams.outRoundBitsPtr = algLayer->layerParams.convParams.outRoundBitsPtr;

  int32_t   qFact = 0;
  int32_t   zeroWeightValue = 0;
  int32_t  outRoundBits, quantFactor = 1;

  buffParams.inScaleFactor = 1;
  outRoundBits = 0;

  if ((intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleNP2Fixed) || (intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleP2Dynamic))
  {
    if(params->enableBias)
    {
      buffParams.inScaleFactor = (params->weightScale * inDataParams->tensorScale) / params->biasScale;
    }
    else
    {
      buffParams.inScaleFactor = 1;
    }
    outRoundBits = tidlLayer->outData.roundBits;
  }

  buffParams.secondRoundBits = outRoundBits;
  buffParams.avgPoolingRoundBits = 2;
  buffParams.biasQFact = qFact;
  buffParams.quantizationStyle = intAlgHandle->createParams->net->quantizationStyle;
  buffParams.quantFactor = quantFactor;
  buffParams.zeroWeightValue = zeroWeightValue;
  buffParams.max = 0;
  buffParams.min = (int32_t)0xFFFFFFFFU;
  buffParams.kernelType = params->kernelType;
  buffParams.numTotRoi = numBatches;

  if(TIDL_QuantStyleAsymNP2_TFL == buffParams.quantizationStyle)
  {
    buffParams.mmaPSATMin = round(tidlLayer->actParams.clipMin/tidlLayer->outData.tensorScale) + tidlLayer->outData.tensorZeroPoint; //zy
    buffParams.mmaPSATMax = round(tidlLayer->actParams.clipMax/tidlLayer->outData.tensorScale) + tidlLayer->outData.tensorZeroPoint;
    params->minPSAT = buffParams.mmaPSATMin;
    params->maxPSAT = buffParams.mmaPSATMax;
  }

  targetInPtr = ((int8_t *)inPtr);
  refInPtr = NULL;

  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    if(intAlgHandle->createParams->quantRangeUpdateFactor != 0)
    {

      int16_t * biasPtr;
      int16_t * orgbiasptr = (int16_t *)((int8_t *)(intAlgHandle->createParams->net) + params->bias);
      uint32_t i;
      int8_t * coeffPtr;
      uint32_t numBiasValues;
      uint32_t NiFrFc;
      uint32_t coeffPitch;

      /* Allocate bias pointer memmory from one of the scratch memory available */
      biasPtr = (int16_t *)TIDL_getMemoryChunkFromSysmem(sysMems, params->numOutChannels*sizeof(int16_t), 128U, TIDL_SYSMEM_L3_SCRATCH, IALG_SCRATCH);
      if(biasPtr)
      {
        TIDL_conv2dBiasSplit(orgbiasptr, biasPtr, &params->biasB, params->numOutChannels, buffParams.inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16, 0xFF, TIDL_getDatElementSign(buffParams.inElementType));

        if ( params->enableBias == 0 )
        {
          numBiasValues = 0;
        }
        else
        {
          numBiasValues = 1U; //:TODO: this should come from some parameter, maybe from biasSplit function
        }

        coeffPtr = (int8_t *) algLayer->layerParams.convParams.pCoeffs;//:TODO: Data type of coefficient point should come from user

        NiFrFc = (params->numInChannels * params->kernelW * params->kernelH)/params->numGroups;

        coeffPitch = (NiFrFc + numBiasValues);

      /* Fill the bias values in src0 */
        for (i = 0; i < params->numOutChannels; i++)
        {
          //:TODO: Need to handle multiple bias not sure how they will come
          coeffPtr[i*coeffPitch + NiFrFc] = biasPtr[i];
        }

        /* Bias pointer is not needed after this so release the memory allocated for it */
        TIDL_resetSysmem(sysMems);
      }
    }


  buffParams.memcpyTr = intAlgHandle->memcpyTr;
  targetOutPtr = ((uint8_t *)outPtr);
  TIDL_conv2dMMAProcess(intAlgHandle->createParams->net,
                        params,
                        &algLayer->layerParams.convParams,
                        &buffParams,
                        sysMems,
                        &algLayer->metaData,
                        &intAlgHandle->sysScratchPtr,
                        intAlgHandle->dmaUtilsContext,
                        targetInPtr,
                        targetOutPtr,
                        layerIdx,
                        &isTargetExec,
                        algLayer->procType,
                        algLayer);
  if ( isTargetExec == 0 )
  {
    tidl_printf(0, "ConvolutionLayer  Not Computed for layer %d \n ", layerIdx);
    status = TIDL_ERR_FAILURE;
    return status;
  }

  }

  refOutPtr =(*outPtr);

  if ( isTargetExec == 0 )
  {
    refInPtr = targetInPtr;
    refOutPtr =(*outPtr);
    isRefExecRequired = 1U;
  }

  if ( isRefExecRequired == 1U )
  {
    buffParams.inBatchPitch = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
    buffParams.outBatchPitch = (uint32_t)outDataParams->pitch[TIDL_ROI_PITCH];
    buffParams.scratchSize = algLayer->scratchSize;
    buffParams.scratchMem  = algLayer->scratchMem;

    status =
      TIDL_refConv2dProcess(
        intAlgHandle,
        algLayer,
        tidlLayer,
        params,
        &buffParams,
        (int8_t *)refInPtr,
        (void *)refOutPtr,
        buffParams.inElementType,
        numBatches,
        sysMems);
  }

  return status;
}

