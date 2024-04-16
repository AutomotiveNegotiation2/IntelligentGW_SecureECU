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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <cmath>
#ifdef _WIN32
#include <asprintf.h>
#endif

#include "tidl_import_quantize.h"
#include "tidl_deviceInfo.h"

#define QUAN_STYLE2_ROUND ((gParams.quantRoundAdd*1.0 / 100))
char *currLayerName;
int currElemenType;

FILE *paramDebugFile = NULL;
int debugLayeId = 0;
#define ENABLE_HIST_BASED_RANGE (0)
#define USE_16BIT_BIAS_FOR_8BIT_MODE (1)

/**
 * @brief Function to find the max scale across diffent weights and biases
 *
 * @param pOrgTIDLNetStructure : Network structure to get weight and bias pointers
 * @param dataId : ID of the data buffer being processed
 * @return float32_tidl : returns the max weight scale
 */
float32_tidl  TIDL_maxWeightScale(const sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, int32_t dataId)
{
  int32_t k, l;
  float32_tidl maxScale = 0.0001f;
  float32_tidl scale_for_non_conv = 1.0f/256.0f; //1
  float32_tidl scale;
  for (k = 0; k < pOrgTIDLNetStructure->numLayers; k++)
  {
    for (l = 0; l < pOrgTIDLNetStructure->TIDLPCLayers[k].numInBufs; l++)
    {
      scale = scale_for_non_conv;
      if (dataId == pOrgTIDLNetStructure->TIDLPCLayers[k].inData[l].dataId)
      {
        if ((pOrgTIDLNetStructure->TIDLPCLayers[k].layerType == TIDL_ConvolutionLayer) ||
          (pOrgTIDLNetStructure->TIDLPCLayers[k].layerType == TIDL_Deconv2DLayer))
        {
          int32_t numInChannels = pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.convParams.numInChannels;
          int32_t numOutChannels = pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.convParams.numOutChannels;
          int32_t numGroups = pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.convParams.numGroups;
          scale = pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.convParams.weightScale;
          if ((pOrgTIDLNetStructure->TIDLPCLayers[k].layerType == TIDL_ConvolutionLayer) &&
              ((numGroups == numInChannels) && (numGroups == numOutChannels) && (numInChannels == numOutChannels)) &&
              (( gParams.calibrationOption & TIDL_CalibOptionPerChannelWeightQuantization) ==
                       TIDL_CalibOptionPerChannelWeightQuantization ))
          {
            /* For per channel quantization we reduce weight bits to avoid bias saturation and hence
            set scale to minimum to avoid reducing activation bits */
            scale = scale_for_non_conv;
          }
          if (pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.convParams.enableBias == 1)
          {
            scale /= pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.convParams.biasScale;
          }
          else
          {
            scale = scale_for_non_conv;
          }

        }
        else if (pOrgTIDLNetStructure->TIDLPCLayers[k].layerType == TIDL_InnerProductLayer)
        {
          scale = pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.innerProductParams.weightScale /
            pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.innerProductParams.biasScale;
        }
        else if (pOrgTIDLNetStructure->TIDLPCLayers[k].layerType == TIDL_BatchNormLayer)
        {
          scale = pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.batchNormParams.weightScale /
            pOrgTIDLNetStructure->TIDLPCLayers[k].layerParams.batchNormParams.biasScale;
        }
        else
        {
          scale = scale_for_non_conv;
        }
      }
      if (scale > maxScale)
      {
        maxScale = scale;
      }
    }
  }
  return (maxScale);
}

void TIDL_findRange(float * data, int32_t dataSize, float * minOut, float * maxOut, float scale)
{
  float min = FLT_MAX;
  float max = -FLT_MAX;
  int32_t i;
  for (i = 0; i < dataSize; i++)
  {
    min = ((data[i] * scale) < min) ? (data[i] * scale) : min;
    max = ((data[i] * scale) > max) ? (data[i] * scale) : max;
  }
  *minOut = (min < *minOut) ? min : *minOut;
  *maxOut = (max > *maxOut) ? max : *maxOut;
#if ENABLE_HIST_BASED_RANGE
  int * histPtr = (int *)my_malloc(HIST_SIZE * sizeof(int));
  float orgMax;
  TIDL_computeHist(data, dataSize, histPtr, &orgMax);
  int curPer = 0;
  int maxPer = dataSize*0.995;
  for (i = 0; i < HIST_SIZE; i++)
  {
    curPer += histPtr[i];
    if (curPer >= maxPer)
      break;
  }
  my_free(histPtr);

  *maxOut = (orgMax*i) / (HIST_SIZE);
  *minOut = -1 * *maxOut;
#endif

}

int32_t TIDL_findRangeHist(float32_tidl * data,
                        int32_t dataSize,
                        int32_t numBins,
                        float32_tidl percentileRangeShrink,
                        float32_tidl * min,
                        float32_tidl * max)
{
  int32_t binIdx, minBinIdx, maxBinIdx;
  float32_tidl minValue = *min;
  float32_tidl maxValue = *max;
  float32_tidl val, val_norm;
  int32_t i1, i2;
  int32_t * histogramArray = (int32_t*)my_malloc(numBins * sizeof(int32_t));
  if(histogramArray != NULL)
  {
    memset(histogramArray, 0, (numBins * sizeof(int32_t)));
  }
  else
  {
    printf("ERROR : TIDL_findRangeHist - Not enough memory available for histogram \n");
    return -1;
  }
  if((maxValue - minValue) != 0) /*not all values in tensor constant */
  {
    for(int i1 = 0; i1 < dataSize; i1++)
    {
      val = data[i1];
      val_norm = (val - minValue)/(maxValue - minValue) * (numBins - 1);
      binIdx = (int32_t)(val_norm + 0.5);  /* Round to nearest integer */
      if ( binIdx > (numBins-1) )
      {
        binIdx = (numBins-1);
      }
      histogramArray[binIdx]++;
    }
    int32_t pct_freq = (int32_t)((percentileRangeShrink / 100.0) * dataSize);
    int32_t count = 0;
    if (*min < 0)  /* minimum to be shrinked only for signed */
    {
      for(i2 = 0; i2 < numBins; i2++)
      {
        count += histogramArray[i2];
        if(count >= pct_freq)
        {
          minBinIdx = i2;
          break;
        }
      }
    }
    else
    {
      minBinIdx = 0;
    }
    count = 0;
    for(i2 = numBins - 1; i2 >= 0; i2--)
    {
      count += histogramArray[i2];
      if(count >= pct_freq)
      {
        maxBinIdx = i2;
        break;
      }
    }
    *min = minValue + (float32_tidl)minBinIdx / (numBins-1) * (maxValue - minValue);
    *max = minValue + (float32_tidl)maxBinIdx / (numBins-1) * (maxValue - minValue);
    *max = (*max > maxValue) ? maxValue : *max; /*to ensure back calculated bin value not greater than original max */
    *min = (*min < minValue) ? minValue : *min;
  }
  else
  {
    *min = minValue;
    *max = maxValue;
  }
  if(histogramArray != NULL)
  {
    my_free(histogramArray);
  }
  return 0;
}


void TIDL_quickSort(float32_tidl * dataSort, int32_t left, int32_t right)
{
  if(left >= right)
  {
    return;
  }
  float32_tidl pivot = dataSort[right];
  int32_t cnt = left;
  float32_tidl temp;
  for (int i = left; i <= right; i++)
  {
    if(dataSort[i] <= pivot)
    {
      temp = dataSort[i];
      dataSort[i] = dataSort[cnt];
      dataSort[cnt] = temp;
      cnt++;
    }
  }
  TIDL_quickSort(dataSort, left, cnt - 2);
  TIDL_quickSort(dataSort, cnt, right);
}

/* Find Kth smallest value in the array.
   Based on quicksort, but there is no need to sort the whole array.
   After partitioning, only need to search in one half.
   Also, tail recursion (with help from compiler) can avoid stack overflow.
   Okay, converting tail recursion to while loop so that we do not need
       to rely on compiler optimization to avoid stack overflow issue.
*/
float32_tidl TIDL_findKthSmallest(float32_tidl * dataSort,
                                  int32_t dataSize, int32_t k)
{
  int32_t left  = 0;
  int32_t right = dataSize - 1;
  int32_t iters = dataSize;

  while (iters-- >= 0)                          /* while (1) */
  {
    if(left >= right)
    {
      return dataSort[left];
    }
    float32_tidl pivot = dataSort[right];
    int32_t cnt = left;
    float32_tidl temp;
    if (dataSort[left + k] < pivot)             /* introduce randomness */
    {
      dataSort[right] = dataSort[left + k];
      dataSort[left + k] = pivot;
      pivot = dataSort[right];
    }
    for (int i = left; i < right; i++)          /* partition */
    {
      if(dataSort[i] < pivot)
      {
        temp = dataSort[i];
        dataSort[i] = dataSort[cnt];
        dataSort[cnt] = temp;
        cnt++;
      }
    }
    dataSort[right] = dataSort[cnt];
    dataSort[cnt]   = pivot;

    int32_t new_left, new_right, new_k;
    if (k < cnt - 1 - left + 1)                 /* <  pivot */
    {
      new_left = left;
      new_right = cnt - 1;
      new_k = k;
    }
    else if (k == cnt - left)                   /* == pivot */
    {
      return dataSort[cnt];
    }
    else                                        /* >= pivot */
    {
      new_left = cnt + 1;
      new_right = right;
      new_k = k - (cnt + 1 - left);
    }

    /* Converting tail recursion into explicit loop, so that we don't need
       to rely on the compiler optimization to avoid stack overflow issue */
    left  = new_left;
    right = new_right;
    k     = new_k;
  }

  return dataSort[left];
}


float32_tidl TIDL_findMedian(float32_tidl * dataSort, int32_t dataSize)
{
#if 0
  float32_tidl temp, median;
  /* sort data - bubble sort too slow, hence quick sort implemented */
  TIDL_quickSort(dataSort, 0, dataSize - 1);
  /* find median value */
  if (dataSize % 2 == 0)
  {
    median = (dataSort[dataSize/2] + dataSort[(dataSize/2) + 1])/2.0;
  }
  else
  {
    median = dataSort[(dataSize+1)/2];
  }
  return median;
#else
  return TIDL_findKthSmallest(dataSort, dataSize, dataSize/2 + 1);
#endif
}


#define TIDL_WEIGHTS_CLAMP_VALUE (15)
#define TIDL_WEIGHTS_CLAMP_RATIO (16)
int32_t TIDL_findRangeUsingMedian(float32_tidl * data,
                              int32_t dataSize,
                              int32_t weightsElementSizeInBits,
                              float32_tidl * min,
                              float32_tidl * max)
{
  float32_tidl weightsClampValue = (pow(2,(weightsElementSizeInBits-1)))/8 - 1;
  float32_tidl weightsClampRatio = TIDL_WEIGHTS_CLAMP_RATIO;
  float32_tidl minValue = *min;
  float32_tidl maxValue = *max;
  float32_tidl absMaxRoundPow2, clampMargin, clampMax;
  float32_tidl absMax = (fabs(minValue) > fabs(maxValue)) ? fabs(minValue) : fabs(maxValue);

  float32_tidl * dataSort = (float32_tidl*)my_malloc(dataSize*sizeof(float32_tidl));
  if(dataSort == NULL)
  {
    printf("ERROR : TIDL_findRangeUsingMedian - Not enough memory available for data sorting to find median \n");
    return -1;
  }
  for(int i = 0; i < dataSize; i++)
  {
    dataSort[i] = fabs(data[i]);
  }
  float32_tidl weightMedian = TIDL_findMedian(dataSort, dataSize);

  if((absMax > weightsClampValue) &&  (absMax > weightMedian * weightsClampRatio))
  {
    absMax = (absMax < (weightMedian * weightsClampRatio)) ? absMax : (weightMedian * weightsClampRatio);
    absMaxRoundPow2 = pow(2, ceil(log(absMax)/log(2.0)));
    clampMargin = 1.0;
    clampMax = absMaxRoundPow2 - clampMargin;
    *max = (maxValue > clampMax) ? clampMax : maxValue;
    *min = (minValue < -1.0*clampMax) ? -1.0*clampMax : minValue;
  }
  else
  {
    *min = minValue;
    *max = maxValue;
  }
  if(dataSort != NULL)
  {
    my_free(dataSort);
  }
  return 0;
}

#define HIST_SIZE (1000)
void TIDL_computeHist(float *origParams, int paramNum, int *histPtr, float *orgMax)
{
  int i;
  float orgMaxFloat = 0;
  for (i = 0; i < HIST_SIZE; i++)
  {
    histPtr[i] = 0;
  }
  for (i = 0; i < paramNum; i++)
  {
    orgMaxFloat = orgMaxFloat <= fabs(origParams[i]) ? fabs(origParams[i]) : orgMaxFloat;
  }
  if(orgMaxFloat == 0)
    orgMaxFloat = 1;
  for (i = 0; i < paramNum; i++)
  {
    if (orgMaxFloat != 0.0)
    {
      int idx = (int)((fabs(origParams[i])* (HIST_SIZE - 1)) / orgMaxFloat);
      if (idx >= 0 && idx < HIST_SIZE)
      {
        histPtr[idx] += 1;
      }
    }
  }
  *orgMax = orgMaxFloat;
}

/* compares quantized values and the original values (for parameters) */
template <class quantParamType>
int TIDL_CompareParams(quantParamType *quantizedParams, float *origParams, int paramNum, float scale) {
  /* absolute value of difference is considered */
  float meanDifference = 0;
  float maxDifference = 0;

  float meanRelDifference = 0;
  float maxRelDifference = 0;
  float orgMaxFloat   = 0;
  float quantMaxFloat = 0;

  float meanOrigFloat = 0;

  int relValidNum = 0;
  int maxRelDiffIndex = 0;
  for (int i = 0; i < paramNum; i++)
  {
    float quantParamFloat = quantizedParams[i] / scale;
    float origFloat = origParams[i];
    float difference = quantParamFloat>origFloat ? (quantParamFloat - origFloat) : (origFloat - quantParamFloat); /* abs value */
    float absOrigFloat = origFloat>0 ? origFloat : -origFloat;
    float absQuantFloat = quantParamFloat>0 ? quantParamFloat : -quantParamFloat;
    int  absQuantizedParams = quantizedParams[i] > 0 ? quantizedParams[i] : -quantizedParams[i];
    meanOrigFloat += absOrigFloat;

    meanDifference += difference;

    if (maxDifference < difference)
    {
      maxDifference = difference;
    }
    if (orgMaxFloat < absOrigFloat)
    {
      orgMaxFloat = absOrigFloat;
    }
    if (quantMaxFloat < absQuantFloat)
    {
      quantMaxFloat = absQuantFloat;
    }
    float relDifference = 0;

    if (absQuantizedParams > 2)
    {
      relDifference = (difference / absOrigFloat) * 100;
      relValidNum++;
    }

    if (maxRelDifference < relDifference)
    {
      maxRelDifference = relDifference;
      maxRelDiffIndex = i;
    }
    meanRelDifference += relDifference;

  }
  meanDifference /= paramNum;

  if (relValidNum != 0)
    meanRelDifference /= relValidNum;
  else
    meanRelDifference = -1;

  meanOrigFloat /= paramNum;
  if (paramDebugFile != NULL)
  {
    int * histPtr = (int *)my_malloc(HIST_SIZE * sizeof(int));
    float temp;
    TIDL_computeHist(origParams, paramNum, histPtr, &temp);
    fprintf(paramDebugFile, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f, , , ,", debugLayeId, meanDifference, maxDifference, meanOrigFloat, meanRelDifference, orgMaxFloat, quantMaxFloat, origParams[maxRelDiffIndex], quantizedParams[maxRelDiffIndex] / scale, maxRelDifference, scale);
    for (int i = 0; i < HIST_SIZE; i++)
    {
      fprintf(paramDebugFile, "%d,", histPtr[i]);
    }
    fprintf(paramDebugFile, "\n");
    my_free(histPtr);
  }
  return 0;

}
static int32_t TIDL_isDepthwiseConvLayer(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, int32_t i)
{
  int32_t isDepthwiseConvLayer = 0;

    if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)
    {
      int32_t numInChannels = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numInChannels;
      int32_t numOutChannels = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numOutChannels;
      int32_t numGroups = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numGroups;
      if((numInChannels == numGroups) && (numOutChannels == numGroups) && (numInChannels == numOutChannels))
      {
        return 1;
      }
  }
  return 0;
}

static int32_t TIDL_depthwiseConvExists(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, int32_t layerIndex)
{
  int32_t isDepthwiseConvLayer = 0;
  for(int i = 0; i < layerIndex; i++)
  {
    if(TIDL_isDepthwiseConvLayer(pOrgTIDLNetStructure , i))
    {
      isDepthwiseConvLayer = 1;
      break;
    }
  }
  return isDepthwiseConvLayer;
}


#define TIDL_MINIMUM_QUANTIZATION_RANGE  (pow(10.0,-15.0))


float TIDL_GetMaxQuantScale(float min,
                            float max,
                            int32_t weightBits
                            )

{
  float absRange = (fabs(max) > fabs(min)) ? fabs(max) : fabs(min);

  /* If absolute range is below minimum and treat it as zero */
  if ( absRange < TIDL_MINIMUM_QUANTIZATION_RANGE)
  {
    absRange = 0;
  }
  else if (gParams.quantizationStyle == TIDL_QuantStyleP2Dynamic)
  {
    absRange = (float)ceil(log((double)absRange) / log((double)2));
    absRange = pow(2.0, (double)absRange);
  }
  else
  {

  }
  float maxWeightsScalePossible = -1;
  if (absRange != 0)
  {
    maxWeightsScalePossible = ((1.0*(1 << (weightBits - 1))) / absRange);
  }
  return (maxWeightsScalePossible);
}


template <class Tout>
float TIDL_QuantizeSignedMax(Tout * params,
                            float * data,
                            int32_t dataSize,
                            float min,
                            float max,
                            int32_t weightBits,
                            float maxScale,
                            int32_t isOutMaxSat,
                            float inTensorScale,
                            float outTensorScale
                            )

{
  int32_t i;
  float quantPrec = FLT_MAX;
  float pData;
  int32_t param;


  /* Finding maximum scale that can be used for current parameters
  based on the quantization scheme  requested by user */
  float maxWeightsScalePossible = TIDL_GetMaxQuantScale(min, max, weightBits);
  quantPrec = maxWeightsScalePossible;

  /* Clip the scale to avoid Bias staturation */
  if ( quantPrec > maxScale )
  {
    quantPrec = maxScale;
  }

  /* If the current layers output tensor scale needs to satisfy
      any requirements on output tensor scale clipping (Example relu6).
      Adjust the weight scale as per IP requirement (Power of 2 divider)
  */

  if(isOutMaxSat)
  {
    if(quantPrec == -1)
    {
      quantPrec = 1;
    }
    float accScale = inTensorScale*quantPrec;
    float outDiv = (accScale / outTensorScale);
    float pow2Div = (float)ceil(log((double)outDiv) / log((double)2));
    pow2Div = pow(2.0, (double)pow2Div);
    if(pow2Div > outDiv)
    {
      pow2Div = pow2Div / 2;
    }
    accScale = outTensorScale * pow2Div;
    quantPrec = accScale / inTensorScale;
  }

  /* Convert the floating point parameters to fixed point based on the selected scale */
  for (i = 0; i < dataSize; i++)
  {
    if(quantPrec == -1)
    {
      params[i] = 0;
    }
    else
    {
      pData = data[i];
      pData = pData > max ? max : pData;
      pData = pData < min ? min : pData;
      if (pData > 0)
      {
        param = (pData *  quantPrec + QUAN_STYLE2_ROUND);
      }
      else
      {
        param = (pData *  quantPrec - QUAN_STYLE2_ROUND);
      }
      param = param > ((1 << (weightBits - 1)) - 1) ? ((1 << (weightBits - 1)) - 1) : param;
      params[i] = param < (-1 * (1 << (weightBits - 1))) ? (-1 * (1 << (weightBits - 1))) : param;
      /* If weigtBits is 1 then it indicates that there are no bits avaialable to quantize weights
      hence explicitly set weights as 0 */
      if ( weightBits == 1)
      {
        params[i] = 0;
      }
    }
  }
  TIDL_CompareParams(params, data, dataSize, quantPrec);

  if((gParams.debugTraceLevel > 0) && (weightBits <=8) &&
     ((((maxWeightsScalePossible / quantPrec) >= 1.5) && (isOutMaxSat == 1)) ||
      (((maxWeightsScalePossible / quantPrec) >  1.0) && (isOutMaxSat == 0))))
  {
      printf("Warning :: Weight Scale Clipped - %10.2f, %10.2f, %10.2f, %4d, %2d, %4d, %s \n", (maxWeightsScalePossible / quantPrec),
                                    maxWeightsScalePossible, quantPrec, currElemenType, isOutMaxSat, debugLayeId, currLayerName);
  }

  return (quantPrec);
}

template float TIDL_QuantizeSignedMax<signed char>(signed char * params, float * data, int32_t dataSize, float min, float max, int32_t weightsElementSizeInBits, float maxScale, int32_t isOutMaxSat, float inTensorScale, float outTensorScale);
template float TIDL_QuantizeSignedMax<signed short>(signed short * params, float * data, int32_t dataSize, float min, float max, int32_t weightsElementSizeInBits, float maxScale, int32_t isOutMaxSat, float inTensorScale, float outTensorScale);



float TIDL_findMaxQuantizationScale(float min, float max, int32_t elementSizeInBits, int32_t sign)
{
  float absRange = (fabs(max) > fabs(min)) ? fabs(max) : fabs(min);

  if (gParams.quantizationStyle == TIDL_QuantStyleP2Dynamic)
  {
    absRange = (float)ceil(log((double)absRange) / log((double)2));
    absRange = pow(2.0, (double)absRange);
  }

  float quantPrec;
  if (absRange != 0)
  {
    /* One sign bit it Bias A is fixed and one side
       bit in Bias B depends on the input tensor element type */
    quantPrec = ((1.0*(1ll << (elementSizeInBits - sign - 1))) / absRange);
  }
  else
  {
    quantPrec = FLT_MAX;
  }

  return quantPrec;
}

#define TIDL_CONCAT_INTERNAL_WEIGHT_Q_U8    ((uint32_t)7)
#define TIDL_CONCAT_INTERNAL_WEIGHT_Q_U16   ((uint32_t)15)
#define TIDL_INTERNAL_POOLING_WEIGHT_Q_U8   ((uint32_t)8)
#define TIDL_INTERNAL_POOLING_WEIGHT_Q_U16   ((uint32_t)12)
#define TIDL_ELTWISE_INTERNAL_WEIGHT_Q_U8   ((uint32_t)6)
#define TIDL_ELTWISE_INTERNAL_WEIGHT_Q_U16   ((uint32_t)14)
#define TIDL_INTERNAL_INDATA_Q              ((uint32_t)7)

/**
 * @brief Function to check if TensorScale update is required or not
 *
 * @param pLayer : Pointer to the current layer
 * @return int32_t : returns updated required or not
 */
int32_t TIDL_canUpdateTensorScale(sTIDL_LayerPC_t * pLayer, tidl_import_config * configParams)
{
  int32_t canUpdate = 1;
  if (pLayer->layerType == TIDL_PoolingLayer )
  {
    if ( pLayer->layerParams.poolParams.poolingType == TIDL_MaxPooling )
    {
      canUpdate = 0;
    }
  }
  else if (pLayer->layerType == TIDL_DataConvertLayer)
  {
    const sTIDL_dataConvertParams_t *params = &pLayer->layerParams.dataConvertParams;
    canUpdate = 1;

    if ( params->type == TIDL_DC_TYPE_OUTPUT )
    {
      int32_t configParamsOutIndex;
      configParamsOutIndex = TIDL_getConfigParamOutIndexFromLayerName((const char *)pLayer->outDataNames[0]);
      if ( configParams->outTensorScale[configParamsOutIndex] != 0.0)
      {
        /* This indicates that for data convert layer on output side, output tensor scale is given by the
        user and we  have to adhere to it hence disable updating the tensor scale*/
        canUpdate = 0;
      }
    }
  }
  else if ((pLayer->layerType == TIDL_FlattenLayer) ||
            (pLayer->layerType == TIDL_CropLayer) ||
            (pLayer->layerType == TIDL_SplitLayer) ||
            (pLayer->layerType == TIDL_SliceLayer) ||
            (pLayer->layerType == TIDL_PadLayer) ||
            (pLayer->layerType == TIDL_OdOutputReformatLayer))
  {
    canUpdate = 0;
  }
  else
  {
    canUpdate = 1;
  }
  return canUpdate;
}
int32_t  isOutputTensorMaxSatAvailable(sTIDL_LayerPC_t *TIDLPCLayers, float * outScale)
{
  float clipMax;
  if (((TIDLPCLayers->actParams.actType == TIDL_Clip) && (TIDLPCLayers->actParams.clipMax > 0) && 
  ((TIDLPCLayers->actParams.clipMin == 0) || ( (-1*TIDLPCLayers->actParams.clipMin) == TIDLPCLayers->actParams.clipMax))) ||
      (TIDLPCLayers->actParams.actType == TIDL_RelU6))
  {
    clipMax = TIDLPCLayers->actParams.clipMax;
    if(TIDLPCLayers->actParams.actType == TIDL_RelU6)
    {
      clipMax = 6.0;
    }
    int32_t elemBits = tidl_getElementSizeInBits(TIDLPCLayers->outData[0].elementType);
    if(TIDLPCLayers->actParams.clipMin  < 0)
    {
      elemBits -= 1;
    }
    *outScale = (1 << elemBits) / clipMax;
    return 1;
  }
  return 0;
}
int32_t TIDLIT_getProcessingElementSizeInBytes(const sTIDL_LayerPC_t  * tidlLayer)
{
  int32_t procElemSizeInBytes;
  if ( tidlLayer->weightsElementSizeInBits <= 8 )
  {
    procElemSizeInBytes = 1;
  }
  else if ( tidlLayer->weightsElementSizeInBits <= 16 )
  {
    procElemSizeInBytes = 2;
  }
  else
  {
    procElemSizeInBytes = 4;
  }

  return procElemSizeInBytes;
}

static int32_t TIDL_getMinConsumerWeightElemBits(const sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, int32_t dataId)
{
  int32_t layerIdx, inBufIdx;
  int32_t weightElementBits = 128;

  for (layerIdx = 0; layerIdx < pOrgTIDLNetStructure->numLayers; layerIdx++)
  {
    for (inBufIdx = 0; inBufIdx < pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].numInBufs; inBufIdx++)
    {
      if (dataId == pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[inBufIdx].dataId)
      {
        if (  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].weightsElementSizeInBits < weightElementBits  )
        {
          weightElementBits = pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].weightsElementSizeInBits;
        }
      }
    }
  }

  return weightElementBits;
}

void TIDL_UpdateScaleFactors(sTIDL_OrgNetwork_t * net,
                                     int32_t i,
                                     int32_t updateStats,
                                     int64_t accMin,
                                     int64_t accMax,
                                     tidl_import_config * configParams)
{
  int32_t j;
  float32_tidl accScale = 1.0f;
  float32_tidl minScale;
  float32_tidl outMin = 1.0f;
  float32_tidl outMax = 1.0f;
  float32_tidl max = 1.0f;
  int32_t elementSizeBits;
  int32_t elementSizeBytes;
  double maxP2;
  float32_tidl curMin;
  float32_tidl curMax;
  float32_tidl outDiv;
  int32_t internal_pooling_weight = 0;
  int32_t procElemSize;
  int32_t canUpdateTensorScale = 0;
  int32_t minConsumerWtElemBits;
  elementSizeBytes = tidl_getElementSizeInBits(net->TIDLPCLayers[i].outData[0].elementType)/8;
  procElemSize     = TIDLIT_getProcessingElementSizeInBytes(&net->TIDLPCLayers[i]);

  /* Find the minimum consumer weight element bits and based on decide how much bias can expand. The minimum
  weight element bits will ensure that constraint to avoid bias saturation is satisfied for all the consumer layers */
  minConsumerWtElemBits = TIDL_getMinConsumerWeightElemBits(net, net->TIDLPCLayers[i].outData[0].dataId );

#if USE_16BIT_BIAS_FOR_8BIT_MODE
  float32_tidl biasExpanScale = 256.0f;
#else
  float32_tidl biasExpanScale = 256.0f*128.0f;
#endif
  if (minConsumerWtElemBits > 8)
  {
    biasExpanScale = 128.0f*256.0f;
  }
  if ((net->TIDLPCLayers[i].outData[0].elementType == TIDL_SignedChar) ||
      (net->TIDLPCLayers[i].outData[0].elementType == TIDL_SignedShort))
  {
    biasExpanScale /= 2.0f;
  }

  /* For float we don't have to call update anything for stats collection */
  if ( elementSizeBytes == 4 )
  {
    net->TIDLPCLayers[i].outData[0].roundBits = 0;
    net->TIDLPCLayers[i].outData[0].tensorScale = 1.0f;
    return;
  }

  if ((net->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)    ||
      (net->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)  ||
      (net->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer) ||
      (net->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer)     ||
      (net->TIDLPCLayers[i].layerType == TIDL_EltWiseLayer)      ||
      (net->TIDLPCLayers[i].layerType == TIDL_PoolingLayer)      ||
      (net->TIDLPCLayers[i].layerType == TIDL_DataConvertLayer)  ||
      (net->TIDLPCLayers[i].layerType == TIDL_ConcatLayer)       ||
      (net->TIDLPCLayers[i].layerType == TIDL_ConstDataLayer))
  {

    const sTIDL_DataParams_t * indata = TIDL_getOutData(net,
      net->TIDLPCLayers[i].inData[0].dataId);

    if (net->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
    {
      accScale = net->TIDLPCLayers[i].layerParams.batchNormParams.weightScale * indata->tensorScale;
    }
    else if (net->TIDLPCLayers[i].layerType == TIDL_ConstDataLayer)
    {
      accScale = net->TIDLPCLayers[i].layerParams.constDataParams.weightScale;
    }
    else if ((net->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
              (net->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer))
    {
      accScale = net->TIDLPCLayers[i].layerParams.convParams.weightScale * indata->tensorScale;
    }
    else if (net->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
    {
      accScale = net->TIDLPCLayers[i].layerParams.innerProductParams.weightScale * indata->tensorScale;
    }
    else if(net->TIDLPCLayers[i].layerType == TIDL_PoolingLayer)
    {
        /* The lines below must match the same lines in function TIDL_poolingInit()
         * Local average pooling 2x2, 3x3, with stride 2 implement an optimized kernel that assumes the scale factors bit-depth are
         * the same as the input data type, which is either 8-bits or 16-bits.
         * The remaining local average pooling assume 16-bits or 32-bits scale factors.
         * */
        if(net->TIDLPCLayers[i].layerParams.poolParams.poolingType == TIDL_AveragePooling)
        {
          if((net->TIDLPCLayers[i].layerParams.poolParams.strideW== 2) &&
             (net->TIDLPCLayers[i].layerParams.poolParams.strideH== 2) &&
             (((net->TIDLPCLayers[i].layerParams.poolParams.kernelW== 2) &&
               (net->TIDLPCLayers[i].layerParams.poolParams.kernelH== 2)) ||
              ((net->TIDLPCLayers[i].layerParams.poolParams.kernelW== 3) &&
               (net->TIDLPCLayers[i].layerParams.poolParams.kernelH== 3))))
          {
            if(procElemSize == 1)
            {
              internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U8;
            }
            else
            {
              internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;
            }
          }
          else
          {
            internal_pooling_weight = TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;
         }
          accScale = ((float32_tidl)(((uint32_t)1) << internal_pooling_weight)) * indata->tensorScale;
        }
        else
        {
          accScale = indata->tensorScale;
        }
    }
    else if ((net->TIDLPCLayers[i].layerType == TIDL_EltWiseLayer) ||
            (net->TIDLPCLayers[i].layerType == TIDL_ConcatLayer))
    {
      uint32_t weightQ = 0;
      if(net->TIDLPCLayers[i].layerType == TIDL_EltWiseLayer)
      {
        if( procElemSize == 1)
        {
          weightQ = TIDL_ELTWISE_INTERNAL_WEIGHT_Q_U8;
        }
        else
        {
          weightQ = TIDL_ELTWISE_INTERNAL_WEIGHT_Q_U16;
        }
      }
      if(net->TIDLPCLayers[i].layerType == TIDL_ConcatLayer)
      {
        if(elementSizeBytes== 1)
        {
          weightQ = TIDL_CONCAT_INTERNAL_WEIGHT_Q_U8;
        }
        else
        {
          weightQ = TIDL_CONCAT_INTERNAL_WEIGHT_Q_U16;
        }
      }

      if((net->TIDLPCLayers[i].layerType == TIDL_EltWiseLayer) && (net->TIDLPCLayers[i].layerParams.eltWiseParams.eltWiseType == TIDL_EltWiseProduct))
      {
        accScale = 1.0f;
        for(j = 0; j < net->TIDLPCLayers[i].numInBufs; j++)
        {
            const sTIDL_DataParams_t * eltWiseIndata = TIDL_getOutData(net,
            net->TIDLPCLayers[i].inData[j].dataId);
            accScale = accScale * eltWiseIndata->tensorScale;
        }
      }
      else
      {
        minScale = FLT_MAX;
        for(j = 0; j < net->TIDLPCLayers[i].numInBufs; j++)
        {
            const sTIDL_DataParams_t * eltWiseIndata = TIDL_getOutData(net,
            net->TIDLPCLayers[i].inData[j].dataId);
            minScale = (eltWiseIndata->tensorScale  < minScale) ? eltWiseIndata->tensorScale : minScale;
        }
        accScale = minScale * (float32_tidl)(((uint32_t)1)  << weightQ);
      }
    }
    else if (net->TIDLPCLayers[i].layerType == TIDL_DataConvertLayer)
    {
      sTIDL_dataConvertParams_t *params = &net->TIDLPCLayers[i].layerParams.dataConvertParams;

       /* multiply by the quantization scale */
      accScale = indata->tensorScale  * (1 << TIDL_INTERNAL_INDATA_Q);

      if ( params->type == TIDL_DC_TYPE_OUTPUT)
      {
        int32_t configParamsOutIndex;
        configParamsOutIndex = TIDL_getConfigParamOutIndexFromLayerName((const char *)&net->TIDLPCLayers[i].outDataNames[0]);
        if ( configParams->outTensorScale[configParamsOutIndex] != 0.0)
        {
          /* if user has requested any specific scale on the output side then we have to adhere to it hence
          accumulator scale will be determined by the output tensor scale */
          accScale = (int)((net->TIDLPCLayers[i].outData[0].tensorScale / indata->tensorScale ) * (1 << TIDL_INTERNAL_INDATA_Q));
          /* When converting from 16 bit fixed point to 8 bit fixed point the scale become < 1 (some thing like ~0.5). This will be treated as 0 during scale computation in inference.
This is as good as not applying any additional scale on input and directly applying the shift. So made the accScale =1 for this case here and inference as well */
          if(accScale < 1)
          {
            accScale = 1;
          }
          accScale = accScale*indata->tensorScale;

        }
        else if ( (net->TIDLPCLayers[i].outData[0].elementType == TIDL_UnsignedWord) ||
            (net->TIDLPCLayers[i].outData[0].elementType == TIDL_SignedWord) ||
            (net->TIDLPCLayers[i].outData[0].elementType == TIDL_UnsignedDoubleWord) ||
            (net->TIDLPCLayers[i].outData[0].elementType == TIDL_SignedDoubleWord))
        {
          if ( indata->tensorScale == 1.0 )
          {
            accScale = 1.0;
          }
          else
          {
            printf("Output datatype is word or double word but input and scale are not 1.\n");
            printf("Conversion to word or double word is only supported in context of \
                    Argmax layer where the scales are already expected to be 1 \n");
            exit(1);
          }
        }
      }

    }
    else
    {
      accScale = 1.0f;
    }

    if(accScale > FLT_MAX)
    {
      accScale = FLT_MAX;
    }

    if(updateStats == 1)
    {
      if ((net->TIDLPCLayers[i].layerType == TIDL_PoolingLayer) &&
          (net->TIDLPCLayers[i].layerParams.poolParams.poolingType == TIDL_AveragePooling))
      {
        float32_tidl tscale =  ((float32_tidl)(((uint32_t)1) << internal_pooling_weight)) * indata->tensorScale;

        curMin = (float32_tidl)accMin / tscale;
        curMax = (float32_tidl)accMax / tscale;
      }
      else
      {
        curMin = (float32_tidl)accMin / accScale;
        curMax = (float32_tidl)accMax / accScale;
      }

    }
    else
    {
      curMin = net->TIDLPCLayers[i].outData[0].minTensorValue;
      curMax = net->TIDLPCLayers[i].outData[0].maxTensorValue;
    }

    /* Do not apply expansion factor for data conversion layer */
    if((gParams.quantRangeExpansionFactor != 1.0f) &&
      (net->TIDLPCLayers[i].layerType != TIDL_DataConvertLayer) )
    {
        curMin = curMin * gParams.quantRangeExpansionFactor;
        curMax = curMax * gParams.quantRangeExpansionFactor;
    }

    if (net->TIDLPCLayers[i].actParams.actType == TIDL_Clip)
    {
      curMin = net->TIDLPCLayers[i].actParams.clipMin;
      net->TIDLPCLayers[i].outData[0].minTensorValue = curMin;
      curMax = net->TIDLPCLayers[i].actParams.clipMax;
      net->TIDLPCLayers[i].outData[0].maxTensorValue = curMax;
    }

    if (net->TIDLPCLayers[i].actParams.actType == TIDL_RelU6)
    {
      curMin = net->TIDLPCLayers[i].outData[0].minTensorValue = 0;
      curMax = net->TIDLPCLayers[i].outData[0].maxTensorValue = 6.0f;
    }
    if ((net->TIDLPCLayers[i].layerType == TIDL_PoolingLayer) &&
        (net->TIDLPCLayers[i].layerParams.poolParams.poolingType == TIDL_AveragePooling)&&
        (net->TIDLPCLayers[i].actParams.actType != TIDL_Clip))
    {
      if((net->TIDLPCLayers[i].layerParams.poolParams.kernelW== 0) &&
         (net->TIDLPCLayers[i].layerParams.poolParams.kernelH== 0))
      {
        curMax = curMax * 1.25;
        outMin = outMin * 1.25;
      }
    }
    if((net->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)&&
    (net->TIDLPCLayers[i].actParams.actType != TIDL_Clip))
    {
      curMax = curMax * 1.25;
      outMin = outMin * 1.25;
    }

    outMin = curMin * accScale;
    outMax = curMax * accScale;
    max = (fabs(outMax) > fabs(outMin)) ? fabs(outMax) : fabs(outMin);


    if (TIDL_getDatElementSign(net->TIDLPCLayers[i].outData[0].elementType) == 1)
    {
      elementSizeBits = (elementSizeBytes * 8) - 1;
      maxP2 = (int32_t)ceil(log((float64_tidl)max) / log((float64_tidl)2));
      maxP2 = pow(2.0, (double)maxP2);
      if(max == maxP2)
      {
        max -= 1;
      }
    }
    else
    {
      elementSizeBits = (elementSizeBytes * 8);
    }



    /* If max== INFINITY, there is a discrepancy between host emulation and target in the result of maxP2
     * if maxP2= (int32_t)ceil(log((float64_tidl)max) / log((float64_tidl)2));
     * So to avoid any issue, we force maxP2 to be 0 only for that particular corner case when max==INFINITY
     * which shouldn't happen in real-world use-case anyway.
     */
    if (max <= FLT_MAX)
    {
        outDiv =  max / (1 << elementSizeBits);
        if(outDiv >= 1.0)
        {
          maxP2 = (int32_t)ceil(log((float64_tidl)outDiv) / log((float64_tidl)2));
          maxP2 = pow(2.0, (double)maxP2);
          if(maxP2 >= 2*outDiv)
          {
            maxP2 = maxP2 / 2;
          }
          maxP2 = (int32_t)ceil(log((float64_tidl)maxP2) / log((float64_tidl)2));
        }
        else
        {
          maxP2 = 0;
        }
    }
    else
    {
        maxP2= 0; /* this will force the code to take the 'else' side of the next 'if (maxP2 > elementSizeBits)' */
    }

    canUpdateTensorScale = TIDL_canUpdateTensorScale(&net->TIDLPCLayers[i], configParams);

    if ((maxP2 > 0) &&  canUpdateTensorScale)
    {
      net->TIDLPCLayers[i].outData[0].roundBits = maxP2;
      if ((net->TIDLPCLayers[i].layerType == TIDL_PoolingLayer) &&
          (net->TIDLPCLayers[i].layerParams.poolParams.poolingType == TIDL_AveragePooling))
      {
        net->TIDLPCLayers[i].outData[0].tensorScale = accScale / (float32_tidl)(((uint32_t)1) << net->TIDLPCLayers[i].outData[0].roundBits);
      }
      else
      {
        net->TIDLPCLayers[i].outData[0].tensorScale = accScale / (float32_tidl)(((uint32_t)1)  << net->TIDLPCLayers[i].outData[0].roundBits);
        int32_t dataIDWeightScale = net->TIDLPCLayers[i].outData[0].dataId;
        int32_t outLayerdx = tidl_getOutLayer(*net, net->numLayers, net->TIDLPCLayers[i].outData[0].dataId);
        if(TIDL_isPadOTF(gParams.deviceName))
        {
          if((net->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer) &&( net->TIDLPCLayers[outLayerdx].layerType == TIDL_DataConvertLayer)) 
          {
            /* This piece of code is for Deconv to see outData of the DC layer succeeding it, for collection of stats */
            dataIDWeightScale = net->TIDLPCLayers[outLayerdx].outData[0].dataId;
          }
          else if((outLayerdx!=-1) && (net->TIDLPCLayers[outLayerdx].layerType == TIDL_DataConvertLayer))
          {
            if(net->TIDLPCLayers[outLayerdx].layerParams.dataConvertParams.type == TIDL_DC_TYPE_INTERMEDIATE)
            {
              dataIDWeightScale = net->TIDLPCLayers[outLayerdx].outData[0].dataId;
            }
          }
        }
        
        float32_tidl wightScale = TIDL_maxWeightScale(net,dataIDWeightScale);
        float outTensorScale;
        int32_t isOutMaxSat = isOutputTensorMaxSatAvailable(&net->TIDLPCLayers[i], &outTensorScale);

       /* When output tensor needs to be clipped at specific value (Like Relu6), the scale for this tensor has the fixed.
           So, in this case tensor scale reduction is not possible. While selecting the weight scale, this criteria is already considered.
           For QAT case, the tensor scale is always reduced to satisfy the bias scale limitation in the next layer. So the TIDL_CalibOptionBiasRange
           is used to by-pass the saturation condition
        */
        if((isOutMaxSat) && ((gParams.calibrationOption & TIDL_CalibOptionBiasRange) == 0))
        {
         if ((net->TIDLPCLayers[i].layerType == TIDL_EltWiseLayer) ||
             (net->TIDLPCLayers[i].layerType == TIDL_ConcatLayer))
            {
                while(((((float32_tidl)(((uint32_t)1)  << net->TIDLPCLayers[i].outData[0].roundBits))*  outTensorScale) >= accScale) &&
                      (net->TIDLPCLayers[i].outData[0].roundBits > 0))

                {
                  net->TIDLPCLayers[i].outData[0].roundBits--;
                }
                accScale = ((float32_tidl)(((uint32_t)1)  << net->TIDLPCLayers[i].outData[0].roundBits))*  outTensorScale;
                net->TIDLPCLayers[i].outData[0].tensorScale = accScale / (float32_tidl)(((uint32_t)1)  << net->TIDLPCLayers[i].outData[0].roundBits);
            }

          wightScale = 0.0001f;
          if((outTensorScale != net->TIDLPCLayers[i].outData[0].tensorScale) && (gParams.debugTraceLevel > 0))
          {
           printf("Warning :: Tensorscale value is not met for the relu6/Clip Activation -  %d \n", i);
          }
        }
        float currTensorScale = net->TIDLPCLayers[i].outData[0].tensorScale;
        int32_t numAddBits = 0;

        /* Find the number of bits needs to be reduced in the tensor scale to avoid saturation in Bias of next layer */
        while ((currTensorScale * wightScale) > biasExpanScale)
        {
          currTensorScale /= 2.0f;
          numAddBits++;
        }
        /* if TIDL_CalibOptionBiasRange is enabled, then  the scale reduction
           is NOT applied on Tensor scale. This would be enabled in QAT cases where tensor
           scale is selected at training time. In this bias would be saturated which is accounted
          during training
          */
        if((numAddBits > 0) && ((gParams.calibrationOption & TIDL_CalibOptionBiasRange) == 0))
        {
          numAddBits = (numAddBits + 1) / 2;
          net->TIDLPCLayers[i].outData[0].roundBits += numAddBits;
          net->TIDLPCLayers[i].outData[0].tensorScale /= (1 << numAddBits);
          if(gParams.debugTraceLevel > 0)
          {
            printf("Warning :: Tensor Scale for layer %d is reduced by %d Bits \n", i, numAddBits);
          }
        }

      }
    }
    else
    {
      if (net->TIDLPCLayers[i].layerType == TIDL_DataConvertLayer)
      {
        sTIDL_dataConvertParams_t *params = &net->TIDLPCLayers[i].layerParams.dataConvertParams;
        if ( params->type == TIDL_DC_TYPE_OUTPUT)
        {
          int32_t configParamsOutIndex;
          configParamsOutIndex = TIDL_getConfigParamOutIndexFromLayerName((const char *)&net->TIDLPCLayers[i].outDataNames[0]);
          if ( configParams->outTensorScale[configParamsOutIndex] != 0.0)
          {
            /* This indicates that for data convert layer on output side, output tensor scale is given by the
            user and we  have to adhere to it hence disable updating the tensor scale. If output is float then this
            gets automatically taken care as scale to be multiplied is float*/
            if (net->TIDLPCLayers[i].outData[0].elementType == TIDL_SinglePrecFloat )
            {
              net->TIDLPCLayers[i].outData[0].roundBits   = 0;
            }
            else
            {
              maxP2 = accScale / net->TIDLPCLayers[i].outData[0].tensorScale ;
              maxP2 = (int32_t)round(log((float64_tidl)maxP2) / log((float64_tidl)2));;
              /* Shift by the same amount which was multiplied to the accumular to bring the scale back to original value */
              //net->TIDLPCLayers[i].outData[0].roundBits   = TIDL_INTERNAL_INDATA_Q;
              if(maxP2 >= 0)
              {
                net->TIDLPCLayers[i].outData[0].roundBits     = maxP2;
              }
              else
              {
                net->TIDLPCLayers[i].outData[0].roundBits     = 0;
              }
            }

         }
        }
        else
        {
          net->TIDLPCLayers[i].outData[0].roundBits  = 0;
          net->TIDLPCLayers[i].outData[0].tensorScale = accScale;
        }
      }
      else
      {
        net->TIDLPCLayers[i].outData[0].roundBits  = 0;
        net->TIDLPCLayers[i].outData[0].tensorScale = accScale;
      }
    }
  }
  else  if ((net->TIDLPCLayers[i].layerType == TIDL_SoftMaxLayer) ||
            (net->TIDLPCLayers[i].layerType == TIDL_ArgMaxLayer) ||
            (net->TIDLPCLayers[i].layerType == TIDL_DetectionOutputLayer))
  {
    net->TIDLPCLayers[i].outData[0].roundBits = 0;
    net->TIDLPCLayers[i].outData[0].tensorScale = 1.0f;

  }
  else  if (net->TIDLPCLayers[i].layerType == TIDL_CustomLayer)
  {
    float32_tidl wightScale = TIDL_maxWeightScale(net,net->TIDLPCLayers[i].outData[0].dataId);
    float32_tidl maxOutputTensorScale = 1.0;

    /* Make sure inData is updated by copying outData from producer layer */
    for (int bufIdx = 0; bufIdx < net->TIDLPCLayers[i].numInBufs; bufIdx++)
    {
      int32_t inLayerdx = tidl_getInLayer(*net, net->numLayers, net->TIDLPCLayers[i].inData[bufIdx].dataId);
      net->TIDLPCLayers[i].inData[bufIdx] = net->TIDLPCLayers[inLayerdx].outData[0];
    }


    /* Maximum possible output tensor scale without bias saturation in the consumer scale */
    maxOutputTensorScale = biasExpanScale/ wightScale;

    net->TIDLPCLayers[i].outData[0].tensorScale = TIDL_getCustomLayerOutputTensorScale(net,
                                                                                  net->TIDLPCLayers[i].weights.ptr,
                                                                                  i,
                                                                                  net->TIDLPCLayers[i].outData[0].minTensorValue,
                                                                                  net->TIDLPCLayers[i].outData[0].maxTensorValue,
                                                                                  maxOutputTensorScale);
  }
  else if(net->TIDLPCLayers[i].layerType == TIDL_ScatterElementsLayer)
  {
    // find the update tensor , as that tensor will drive the output tensor scale
    for(j = 0; j < net->TIDLPCLayers[i].numInBufs; j++)
    {
      if(strcmp((char*)net->TIDLPCLayers[i].layerParams.scatterElementsParams.updateTensorName,
                (char*)net->TIDLPCLayers[i].inDataNames[j])==0)
      {
        break;
      }
    }

    const sTIDL_DataParams_t * indata = TIDL_getOutData(net,
      net->TIDLPCLayers[i].inData[j].dataId);
    net->TIDLPCLayers[i].outData[0].roundBits = 0;
    net->TIDLPCLayers[i].outData[0].tensorScale    = indata->tensorScale;

  }
  else if (! ((net->TIDLPCLayers[i].layerType == TIDL_DataLayer) && (net->TIDLPCLayers[i].numOutBufs > 0)) )
  {
    /* tensorScale for input data layer is already set, and if tried to write here, all scales are overwritten with first scale since inData[0].dataId = 0
    for all input data layers */
    const sTIDL_DataParams_t * indata = TIDL_getOutData(net,
      net->TIDLPCLayers[i].inData[0].dataId);
    net->TIDLPCLayers[i].outData[0].roundBits = 0;
    net->TIDLPCLayers[i].outData[0].tensorScale    = indata->tensorScale;
  }
  if(net->TIDLPCLayers[i].outData[0].tensorScale == 0)
  {
    net->TIDLPCLayers[i].outData[0].tensorScale = FLT_MIN;
  }

  if(net->TIDLPCLayers[i].outData[0].tensorScale > FLT_MAX)
  {
    net->TIDLPCLayers[i].outData[0].tensorScale = FLT_MAX;
  }
  if(net->TIDLPCLayers[i].layerType == TIDL_DataConvertLayer)
  {
    if(net->TIDLPCLayers[i].layerParams.dataConvertParams.type == TIDL_DC_TYPE_INTERMEDIATE)
    {
      /* This piece of code is for making the intermediate DC layer act as a bypass layer */
      net->TIDLPCLayers[i].outData[0].roundBits = 0;
      const sTIDL_DataParams_t * indata = TIDL_getOutData(net,
      net->TIDLPCLayers[i].inData[0].dataId);
      net->TIDLPCLayers[i].outData[0].tensorScale    = indata->tensorScale;
      net->TIDLPCLayers[i].outData[0].tensorZeroPoint   = indata->tensorZeroPoint;
    }
  }
  return;
}


#define TIDL_NUM_WEIGHT_HISTOGRAM_BINS (1024U)
void TIDL_importQuantLayerParams_HPTQ(sTIDL_OrgNetwork_t   * pOrgTIDLNetStructure,
                                            sTIDL_Network_t        *pTIDLNetStructure,
                                            tidl_import_config       *configParams,
                                            int32_t layerIndex)
{
  int32_t i;
  int32_t numBins = TIDL_NUM_WEIGHT_HISTOGRAM_BINS;
  char filenameStr[1000];
  sprintf(filenameStr, "%s_paramDebug.csv", configParams->outputNetFile);

  if (configParams->modelType == TIDL_IMPORT_MODEL_FORMAT_TFLITE)
  {
    //Scale update for the first layer (Needs to generalize for multi input):
    pOrgTIDLNetStructure->TIDLPCLayers[1].inData[0].tensorScale = gParams.inQuantFactor[0];
    pOrgTIDLNetStructure->TIDLPCLayers[1].inData[0].tensorZeroPoint = gParams.inZeroPoint[0];
    pOrgTIDLNetStructure->TIDLPCLayers[0].outData[0].tensorScale = gParams.inQuantFactor[0];
    pOrgTIDLNetStructure->TIDLPCLayers[0].outData[0].tensorZeroPoint = gParams.inZeroPoint[0];
  }

  paramDebugFile = fopen(filenameStr, "w+");
  if (paramDebugFile == NULL)
  {
    printf("Could not open %s file \n", filenameStr);
    exit(0);
  }
  fprintf(paramDebugFile, "LayerId , meanDifference, maxDifference, meanOrigFloat, meanRelDifference, orgmax, quantizedMax,orgAtmaxDiff, quantizedAtMaxDiff,maxRelDifference, Scale , , , , Hist \n");

  for (i = 0; i < layerIndex; i++)
  {
    int32_t weightsElementSizeInBits;
    debugLayeId = i;
    int32_t numGroups = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numGroups;
    int32_t numInChannels = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numInChannels;
    int32_t numOutChannels = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numOutChannels;

    if  ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_DetectionOutputLayer)
        )
    {
      float min_clipped = FLT_MAX;
      float max_clipped = -FLT_MAX;
      float min = FLT_MAX;
      float max = -FLT_MAX;
      float maxWeightScale = FLT_MAX;

      if ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
          (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer))
      { 
       //Deal with cases when bias is disabled.. bias HAS to be enabled to support asymmetric quantization
       //Modify bias based on:
       /*****************************************************
        zp,wts,etc..

       *******************************************************/
       if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)
       {
         //TFLITE IMPLICIT ASSUMPTION THAT WEIGHTS ARE INT8
         int32_t outIdx;
         int32_t wtIdx;
         int8_t *pWeights = (int8_t*) pOrgTIDLNetStructure->TIDLPCLayers[i].weights.ptr;
         float32_tidl *pWeightScales = (float32_tidl*)pOrgTIDLNetStructure->TIDLPCLayers[i].weightScales.ptr;
         int32_t *pBias = (int32_t*) pOrgTIDLNetStructure->TIDLPCLayers[i].bias.ptr;
         int32_t originalBias;
         float32_tidl unitConvResult = 0;
         int32_t numInWeights = (numInChannels/numGroups)*(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.kernelH * pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.kernelW);
         int8_t z_x = pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].tensorZeroPoint;
         int8_t z_y = pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorZeroPoint;
         float32_tidl scale_x = pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].tensorScale;
         float32_tidl scale_y = pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorScale;
         float32_tidl scale_w = 1;         
         float32_tidl nScale = 1;
         float32_tidl finalBias = 0;

         for(outIdx = 0; outIdx < numOutChannels; outIdx++)
         {
           unitConvResult = 0;
           scale_w = pWeightScales[outIdx];
           for(wtIdx = 0; wtIdx < numInWeights ; wtIdx++) //Is dilation taken care of here??
           {
             unitConvResult += pWeights[wtIdx + outIdx*numInWeights];
           }
           originalBias = pBias[outIdx];
           nScale = scale_y/(scale_x * scale_w);
           finalBias = originalBias + ( z_y * nScale - (z_x * unitConvResult));
           float32_tidl absBias = finalBias < 0 ? (finalBias*-1) : finalBias;
           if(absBias > ((float)2147483647))
           {
             //Saturation case, i.e. filter and input are irrelevant:
             //Zero weights out: (Consequence of a huge bias is that your output is more or less going to be a DC term)
             for(wtIdx = 0; wtIdx < numInWeights ; wtIdx++) //Is dilation taken care of here??
             {
               pWeights[wtIdx + outIdx*numInWeights] = 0;
             }
             //At this point only a bias term exists and weight scale needs to be modified for it to fit in the 32-bit bias container:
             //Default weight scale to 1 and recalc bias:
             //Bias in output domain:
             finalBias = (finalBias/nScale);
             //In weight scale = 1 domain:
             pWeightScales[outIdx] = 1;
             //Switching to original domain with new scale:
             finalBias = ((finalBias * scale_y)/scale_x);
             pBias[outIdx] = round(finalBias);
           }
           else
           {
              pBias[outIdx] = round(finalBias);
           }
         }
       }
      }
      else if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
      {
        //TFLITE IMPLICIT ASSUMPTION THAT WEIGHTS ARE INT8 && only for single ROI
        int32_t outIdx;
        int32_t wtIdx;
        int8_t *pWeights = (int8_t*) pOrgTIDLNetStructure->TIDLPCLayers[i].weights.ptr;
        float32_tidl *pWeightScales = (float32_tidl*)pOrgTIDLNetStructure->TIDLPCLayers[i].weightScales.ptr;
        int32_t *pBias = (int32_t*) pOrgTIDLNetStructure->TIDLPCLayers[i].bias.ptr;
        int32_t originalBias;
        float32_tidl unitConvResult = 0;
        int32_t numInWeights = (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.numInNodes);
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weightScale = *pWeightScales; //Global weight scale populated here! 
        int8_t z_x = pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].tensorZeroPoint;
        int8_t z_y = pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorZeroPoint;
        float32_tidl scale_x = pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].tensorScale;
        float32_tidl scale_y = pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorScale;
        float32_tidl scale_w = 1;         
        float32_tidl nScale = 1;
        float32_tidl finalBias = 0;
        for(outIdx = 0; outIdx <  pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.numOutNodes; outIdx++)
        {
          unitConvResult = 0;
          scale_w = pWeightScales[0];
          for(wtIdx = 0; wtIdx < numInWeights ; wtIdx++) //Is dilation taken care of here??
          {
            unitConvResult += pWeights[wtIdx + outIdx*numInWeights];
          }
          originalBias = pBias[outIdx];
          nScale = scale_y/(scale_x * scale_w);
          finalBias = originalBias + ( z_y * nScale - (z_x * unitConvResult));
          float32_tidl absBias = finalBias < 0 ? (finalBias*-1) : finalBias;
          if(absBias > ((float)2147483647))
          {
            //Saturation case, i.e. filter and input are irrelevant:
            //Zero weights out: (Consequence of a huge bias is that your output is more or less going to be a DC term)
            for(wtIdx = 0; wtIdx < numInWeights ; wtIdx++) //Is dilation taken care of here??
            {
              pWeights[wtIdx + outIdx*numInWeights] = 0;
            }
            //At this point only a bias term exists and weight scale needs to be modified for it to fit in the 32-bit bias container:
            //Default weight scale to 1 and recalc bias:
            //Bias in output domain:
            finalBias = (finalBias/nScale);
            //In weight scale = 1 domain:
            pWeightScales[outIdx] = 1;
            //Switching to original domain with new scale:
            finalBias = ((finalBias * scale_y)/scale_x);
            pBias[outIdx] = round(finalBias);
          }
          else
          {
            pBias[outIdx] = round(finalBias);
          }
        }
      }
      else if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
      {
        //TFL doesn't have any implementation - needs to be potentially handled for other frameworks for PTQ ingest
      }
    }
    else if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_SoftMaxLayer)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].elementType = TIDL_SignedChar;
      pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].elementType  = TIDL_SignedChar;
    }
    else if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_PoolingLayer /*  check for global avg pooling also  */)
    {
      if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.poolingType == TIDL_AveragePooling)
      {
        int32_t internal_pooling_weight;
        int32_t procElemSize     = TIDLIT_getProcessingElementSizeInBytes(&pOrgTIDLNetStructure->TIDLPCLayers[i]);
        float32_tidl accScale = 1.0f;
        const sTIDL_DataParams_t * indata = TIDL_getOutData(pOrgTIDLNetStructure, pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].dataId);
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.strideW== 2) &&
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.strideH== 2) &&
            (((pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelW== 2) &&
              (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelH== 2)) ||
            ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelW== 3) &&
              (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelH== 3))))
        {
          
          if(procElemSize == 1 && ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelW== 3) &&
              (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelH== 3)))
          {
            //internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U8;
            internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;/*Setting this to 2^12 for 8-bit case also to get higher accuracy while losing out on performance*/
          }
          else if(procElemSize == 1){
            internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U8;
          }
          else
          {
            internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;
          }
          
        }
        else
        {
          internal_pooling_weight = TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;
        }
        if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelW != 0 && pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.poolParams.kernelH != 0)
        {
          accScale = ((float32_tidl)(((uint32_t)1) << internal_pooling_weight)) * indata->tensorScale;
          pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].roundBits  = internal_pooling_weight;
          pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorScale = indata->tensorScale;
        }
      }
    }
    /* In case of DataConvertLayer mapped from quantized layer of TFL asymQuant populate the max possible bits for roundBits (used in shift) */
    else if( (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_DataConvertLayer) && (gParams.quantizationStyle == TIDL_QuantStyleAsymNP2_TFL) )
    {      
        /* find the maxP2 number of shifts possible for scale to avoid overflow*/
        float maxP2 = ((pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].tensorScale) * (1 << TIDL_INTERNAL_INDATA_Q)) /
                          (pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorScale) ;
        maxP2 = (int32_t)round(log((float64_tidl)maxP2) / log((float64_tidl)2));;
        
        /* In case of inData/outData in float, the scale and bias is used in float32 mode , roundBits is not used,
           Remaining cases we need to check bias is overflowing*/
        if ( (pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].elementType != TIDL_SinglePrecFloat) && \
             (pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].elementType != TIDL_SinglePrecFloat))
        {
          /* bias = out_zf - (in_zf * (out_scale/in_scale))  - scale is reciprocal in case of TIDL_QuantStyleAsymNP2_TFL */
          float bias  =  pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.dataConvertParams.outZeroPoint - \
                            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.dataConvertParams.inZeroPoint * \
                            ((pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].tensorScale)  /(pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorScale)));
          /* Type of q1 is of type int8_t in split bias case*/
          int64_t q1AbsMax,q2AbsMax;
          q1AbsMax = std::numeric_limits<int8_t>::max(); // 127
          /* Type of q2 is determined by source */
          if (pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].elementType == TIDL_SignedChar)
          {
            q2AbsMax = -1 * std::numeric_limits<int8_t>::min();
          }
          else
          {
            q2AbsMax = std::numeric_limits<uint8_t>::max();
          }
          int64_t biasAbsMax = (int64_t)(bias * (1 << (int32_t)maxP2));
          while(biasAbsMax > (q2AbsMax * q1AbsMax) ){
            maxP2--;
            biasAbsMax = bias * (1 << (int32_t)maxP2);
          }
        }
        if(maxP2 >= 0)
        {
          pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].roundBits     = maxP2;
        }
        else
        {
          pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].roundBits     = 0;
        }
        /* In case of DataconvertLayer from dequantize set the outData.tensorScale  to 1 */ 
        if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.dataConvertParams.type ==  TIDL_DC_TYPE_OUTPUT)
        {
          if( ((pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].elementType == TIDL_UnsignedChar) || (pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].elementType ==  TIDL_SignedChar)) \
          && (pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].elementType ==  TIDL_SinglePrecFloat))
            pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].tensorScale = 1;
        }
    }
  }
  fclose(paramDebugFile);
}

void TIDL_updateParamsRange(sTIDL_OrgNetwork_t   * pOrgTIDLNetStructure,
                            sTIDL_Network_t        *pTIDLNetStructure,
                            int32_t layerIndex)
{
  int32_t i,j;
  int32_t numBins = TIDL_NUM_WEIGHT_HISTOGRAM_BINS;

  for (i = 0; i < layerIndex; i++)
  {
    for (j = 0; j < TIDL_MAX_QUANT_PARAMS; j++)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].size = 0;
    }

    if  ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer)     ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)    ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConstDataLayer))
    {
      if ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
          (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer))
      {
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.biasScale;
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_WEIGHT_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.weightScale;
      }
      else if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.biasScale;
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_WEIGHT_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weightScale;
      }
      else if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.biasScale;
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_WEIGHT_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.weightScale;
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_SLOPE_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.slopeScale;
      }
      else if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConstDataLayer)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_WEIGHT_QUANT_PARAMS].scalePtr =
                                        &pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.constDataParams.weightScale;        
      }
      pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].size   = pOrgTIDLNetStructure->TIDLPCLayers[i].bias.bufSize;
      pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_WEIGHT_QUANT_PARAMS].size = pOrgTIDLNetStructure->TIDLPCLayers[i].weights.bufSize;
      pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_SLOPE_QUANT_PARAMS].size   = pOrgTIDLNetStructure->TIDLPCLayers[i].slope.bufSize;
    }
  }
  void **data;
  float min;
  float max;


  for (i = 0; i < layerIndex; i++)
  {
    int32_t  weightsElementSizeInBits = pOrgTIDLNetStructure->TIDLPCLayers[i].weightsElementSizeInBits;
    for (j = 0; j < TIDL_MAX_QUANT_PARAMS; j++)
    {
      int32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].size;
      if (dataSize)
      {
        min = FLT_MAX;
        max = -FLT_MAX;
        if(j == TIDL_BIAS_QUANT_PARAMS)
        {
          data = (void **)&(pOrgTIDLNetStructure->TIDLPCLayers[i].bias.ptr);
        }
        else if(j == TIDL_WEIGHT_QUANT_PARAMS)
        {
          data = (void **)&(pOrgTIDLNetStructure->TIDLPCLayers[i].weights.ptr);
        }
        else if(j == TIDL_SLOPE_QUANT_PARAMS)
        {
          data = (void **)&(pOrgTIDLNetStructure->TIDLPCLayers[i].slope.ptr);
        }
        TIDL_findRange((float*)(*data), dataSize, &min, &max, 1.0);
        if(j == TIDL_WEIGHT_QUANT_PARAMS)
        {
          if (( pTIDLNetStructure->calibrationOption & TIDL_CalibOptionWeightRange ) == TIDL_CalibOptionWeightRange)
          {
            if ( pTIDLNetStructure->calibrationParams.weightRangeMethod == TIDL_WeightRangeMethodHistogram )
            {
              TIDL_findRangeHist((float*)(*data), dataSize, numBins, pTIDLNetStructure->calibrationParams.percentileWtRangeShrink, &min, &max);
            }
            if ( pTIDLNetStructure->calibrationParams.weightRangeMethod == TIDL_WeightRangeMethodMedian)
            {
              TIDL_findRangeUsingMedian((float*)(*data), dataSize, weightsElementSizeInBits, &min, &max);
            }
          }
        }
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].prmPtr = data;
        *(pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].scalePtr) = TIDL_GetMaxQuantScale(min, max, weightsElementSizeInBits);

        if ((j == TIDL_WEIGHT_QUANT_PARAMS) &&
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer) &&
            ((pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_Sigmoid)||(pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_Tanh)||(pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_HardSigmoid)||(pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_ELU)))
        {
          /* The default value of weightsElementSizeInBits is set during initially which is set based on numParamBits as given by the user. For mixed precision
          the default value is updated based on whether a particular layer is running at higher precision or not. Hence at this point we should read the updated
          value of weightsElementSizeInBits as decided based on the precision of the layer*/
         *(pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].scalePtr) = (1.0*((1 << (pOrgTIDLNetStructure->TIDLPCLayers[i].weightsElementSizeInBits -1))));
        }


        if(*(pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].scalePtr) == -1)
        {
          if(j == TIDL_BIAS_QUANT_PARAMS)
          {
            *(pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].scalePtr) = FLT_MAX;
          }
          else
          {
            *(pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].scalePtr) = 1;
          }
        }
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].max = max;
        pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].min = min;
      }
    }
  }


}

void TIDL_QuantPerChannelWeight(sTIDL_OrgNetwork_t   * pOrgTIDLNetStructure,
                                            sTIDL_Network_t        *pTIDLNetStructure,
                                            tidl_import_config       *configParams,
                                            int32_t i)
{
    float min_clipped = FLT_MAX;
    float max_clipped = -FLT_MAX;
    float maxWeightScale = FLT_MAX;
    float min = FLT_MAX;
    float max = -FLT_MAX;
    int32_t weightsElementSizeInBits = pOrgTIDLNetStructure->TIDLPCLayers[i].weightsElementSizeInBits;
    int32_t numInChannels = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numInChannels;
    int32_t numOutChannels = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numOutChannels;

    float outTensorScale;
    int32_t isOutMaxSat = isOutputTensorMaxSatAvailable(&pOrgTIDLNetStructure->TIDLPCLayers[i], &outTensorScale);
    const sTIDL_DataParams_t * indata = TIDL_getOutData(pOrgTIDLNetStructure,
                  pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].dataId);

    if(pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].size > 0)
    {
        min = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].min;
        max = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].max;
        float maxBiasScale = TIDL_findMaxQuantizationScale(min, max, weightsElementSizeInBits*2, TIDL_getDatElementSign(indata->elementType));
        maxWeightScale = maxBiasScale / indata->tensorScale;
    }
    float32_tidl * data = (float32_tidl *)pOrgTIDLNetStructure->TIDLPCLayers[i].weights.ptr;
    int32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].weights.bufSize;
    min = FLT_MAX;
    max = -FLT_MAX;
    TIDL_findRange(data, dataSize, &min, &max, 1.0);
    min_clipped = min;
    max_clipped = max;
    /* dataSizePerChannel is the number of weights per channel */
    uint32_t dataSizePerChannel = (dataSize / numInChannels);
    if(dataSizePerChannel > 0)
    {
      int i1;
      float32_tidl * perChannelWeightScale = (float32_tidl *)my_malloc(numInChannels * sizeof(float32_tidl));
      uint8_t * quantizedParams = (uint8_t *)my_malloc(dataSize * sizeof(float32_tidl)); /* allocate 32 bit memory to ensure memory doesn't have to be allocated in each iteration of bias calibration */
      for(i1 = 0; i1 < numOutChannels; i1++)
      {
        min = FLT_MAX;
        max = -FLT_MAX;
        TIDL_findRange(&data[i1*dataSizePerChannel], dataSizePerChannel, &min, &max, 1.0);
        min = ( min < min_clipped ) ? min_clipped : min;
        max = ( max > max_clipped ) ? max_clipped : max;
        if (weightsElementSizeInBits <= 8)
        {
          perChannelWeightScale[i1] = TIDL_QuantizeSignedMax((int8_t *)&quantizedParams[i1*dataSizePerChannel*((weightsElementSizeInBits - 1) / 8 + 1)], &data[i1*dataSizePerChannel], dataSizePerChannel, min, max, weightsElementSizeInBits, maxWeightScale, isOutMaxSat, indata->tensorScale, outTensorScale);
        }
        else // weightsElementSizeInBits == 2
        {
          perChannelWeightScale[i1] = TIDL_QuantizeSignedMax((int16_t *)&quantizedParams[i1*dataSizePerChannel*((weightsElementSizeInBits - 1) / 8 + 1)], &data[i1*dataSizePerChannel], dataSizePerChannel, min, max, weightsElementSizeInBits, maxWeightScale, isOutMaxSat, indata->tensorScale, outTensorScale);
        }
      }
      if (perChannelWeightScale[i1] == -1)
      {
        /* weightScale = -1 means all weights are very small and set to 0. Given all weights are 0, scale forced to 1
        in order to prevent it from blowing up thereby ensuring tensorScale doesn't get reduced to prevent bias saturation */
        perChannelWeightScale[i1] = 1;
      }
      pOrgTIDLNetStructure->TIDLPCLayers[i].perChannelWeightScale.ptr = perChannelWeightScale;
      pOrgTIDLNetStructure->TIDLPCLayers[i].perChannelWeightScale.bufSize = numInChannels;
      pOrgTIDLNetStructure->TIDLPCLayers[i].weights.ptr = quantizedParams;
      my_free(data);
    }
}

void TIDL_importQuantLayerParams(sTIDL_OrgNetwork_t   * pOrgTIDLNetStructure,
                                            sTIDL_Network_t        *pTIDLNetStructure,
                                            tidl_import_config       *configParams,
                                            int32_t layerIndex)
{
  int32_t i,j;
  int32_t numBins = TIDL_NUM_WEIGHT_HISTOGRAM_BINS;
  char filenameStr[1000];

  /* Find the maximum scale possible for each layer’s Bias
  and weight parameters based on the actual range of their parameters.
  These. would be used while deciding the actual parameter and tensors
  scales in the next loop which would stratify the requirements of DL acceleration IP
  */
  TIDL_updateParamsRange(pOrgTIDLNetStructure, pTIDLNetStructure,layerIndex);


  sprintf(filenameStr, "%s_paramDebug.csv", configParams->outputNetFile);

  paramDebugFile = fopen(filenameStr, "w+");
  if (paramDebugFile == NULL)
  {
    printf("Coudl not open %s file \n", filenameStr);
    exit(0);
  }
  fprintf(paramDebugFile, "LayerId , meanDifference, maxDifference, meanOrigFloat, meanRelDifference, orgmax, quantizedMax,orgAtmaxDiff, quantizedAtMaxDiff,maxRelDifference, Scale , , , , Hist \n");

  for (i = 0; i < layerIndex; i++)
  {
    int32_t weightsElementSizeInBits = pOrgTIDLNetStructure->TIDLPCLayers[i].weightsElementSizeInBits;
    const sTIDL_DataParams_t * indata = TIDL_getOutData(pOrgTIDLNetStructure,
                        pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].dataId);
    debugLayeId = i;
    currLayerName = (char*)pOrgTIDLNetStructure->TIDLPCLayers[i].name;
    currElemenType = indata->elementType;
    for (j = 0; j < TIDL_MAX_QUANT_PARAMS; j++)
    {
      int32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].size;
      if (dataSize)
      {
        /* PerChannelWeightQuantization for DWS convolution layer is handled differently compared to res of the layers */
        if((j == TIDL_WEIGHT_QUANT_PARAMS) &&  TIDL_isDepthwiseConvLayer(pOrgTIDLNetStructure,i) &&
           ((configParams->calibrationOption & TIDL_CalibOptionPerChannelWeightQuantization) == TIDL_CalibOptionPerChannelWeightQuantization))
        {
          TIDL_QuantPerChannelWeight(pOrgTIDLNetStructure,pTIDLNetStructure,configParams,i);
        }
        else
        {
          float *scalePtr = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].scalePtr;
          void **prmPtr = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].prmPtr;
          float min;
          float max;
          float maxWeightScale = FLT_MAX;
          float outTensorScale;
          void * params = (void *)my_malloc(dataSize * sizeof(float32_tidl));

          /* Check whether the current layers output tensor scale needs to satisfy
             any requirements on output tensor scale clipping (Example relu6).
          */
          int32_t isOutMaxSat = isOutputTensorMaxSatAvailable(&pOrgTIDLNetStructure->TIDLPCLayers[i], &outTensorScale);
          if(j != TIDL_WEIGHT_QUANT_PARAMS)
          {
            isOutMaxSat = 0;
          }

          /* Finding the maximum scale that can be used for weight parameters which would not saturate the
           Bias parameters of the current layers based on current layers input scale
           */
          if((j == TIDL_WEIGHT_QUANT_PARAMS) && ((configParams->calibrationOption & TIDL_CalibOptionBiasRange) == 0) &&
            (pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].size > 0)  &&
            ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
              (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer)))
          {
              min = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].min;
              max = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[TIDL_BIAS_QUANT_PARAMS].max;

              float maxBiasScale = TIDL_findMaxQuantizationScale(min, max, weightsElementSizeInBits*2, TIDL_getDatElementSign(indata->elementType));
              maxWeightScale = maxBiasScale / indata->tensorScale;

          }
          min = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].min;
          max = pOrgTIDLNetStructure->TIDLPCLayers[i].quantParams[j].max;

           if((j == TIDL_BIAS_QUANT_PARAMS) || (weightsElementSizeInBits > 8))
          {
            *scalePtr = TIDL_QuantizeSignedMax((int16_t *)params, (float*)(*prmPtr), dataSize, min, max, weightsElementSizeInBits, maxWeightScale, isOutMaxSat, indata->tensorScale, outTensorScale);
          }
          else
          {
            *scalePtr = TIDL_QuantizeSignedMax((int8_t *)params, (float*)(*prmPtr), dataSize, min, max, weightsElementSizeInBits, maxWeightScale, isOutMaxSat, indata->tensorScale, outTensorScale);
          }
          if ((j == TIDL_WEIGHT_QUANT_PARAMS) &&
              (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer) &&
              ((pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_Sigmoid)||(pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_Tanh)||(pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_HardSigmoid)||(pOrgTIDLNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_ELU)))
          {
            /* The default value of weightsElementSizeInBits is set during initially which is set based on numParamBits as given by the user. For mixed precision
            the default value is updated based on whether a particular layer is running at higher precision or not. Hence at this point we should read the updated
            value of weightsElementSizeInBits as decided based on the precision of the layer*/
            *scalePtr = (1.0*((1 << (pOrgTIDLNetStructure->TIDLPCLayers[i].weightsElementSizeInBits -1))));
          }

          if(*scalePtr == -1)
          {
            if(j == TIDL_BIAS_QUANT_PARAMS)
            {
              *scalePtr = FLT_MAX;
            }
            else
            {
              *scalePtr = 1;
            }
          }
          my_free((*prmPtr));
          *prmPtr = (void*)params;
        }
      }
    }
    TIDL_UpdateScaleFactors(pOrgTIDLNetStructure, i, 0, 0, 0, configParams);
  }
  fclose(paramDebugFile);
}



/* This function should always be in sync with similar function in TIDL with name
   TIDL_findCurrentOffsetForPerChannelMean
*/
          static int32_t tidlFindCurrentOffsetForPerChannelMean(sTIDL_Network_t * net, int32_t currLayerNum, int32_t * totalMemReq)
          {
            int layerIdx = 0;
            int32_t totNumOutChannels = 0;
            int32_t currNumOutChannels = 0;
            for (layerIdx = 0; layerIdx < net->numLayers; layerIdx++)
            {

              if (layerIdx == (currLayerNum))
              {
                currNumOutChannels = totNumOutChannels;
              }

              if ((net->TIDLLayers[layerIdx].layerType != TIDL_DataLayer))
              {
                //:TODO: This can eventually be done only for the layers where bias is applicable
                totNumOutChannels += net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH];
              }
            }
            if (totalMemReq != NULL)
            {
              *totalMemReq = totNumOutChannels * sizeof(float32_tidl);
            }
            /* return -1 if data layer else actual offset */
            return ((net->TIDLLayers[currLayerNum].layerType != TIDL_DataLayer) ? (currNumOutChannels * sizeof(float32_tidl)) : -1);
}

int32_t tidlReadPerChannelMeanStatistics(sTIDL_Network_t * tidlNetStructure,
                                                                                void * perChannelMeanStats,
                                                                                int32_t perChannelMeanMemSize,
                                                                                tidl_import_config * configParams)
{
  if ( tidlNetStructure->isQuantStatsAvailable == 1 )
  {
    if (( tidlNetStructure->calibrationOption & TIDL_CalibOptionBiasCalibration) == TIDL_CalibOptionBiasCalibration )
    {
        int32_t memRequired;
        tidlFindCurrentOffsetForPerChannelMean(tidlNetStructure,
                                                              0,
                                                              &memRequired);
        if ( perChannelMeanMemSize != memRequired )
        {
          printf("tidlReadPerChannelMeanStatistics : Not enough memory to read per channel mean statistics\n");
          return -1;
        }

        if ( perChannelMeanStats == NULL )
        {
          printf("tidlReadPerChannelMeanStatistics : perChannelMeanStats pointer is NULL\n");
          return -1;
        }

        char perChannelMeanFileName[1024];
        char outDirName[1024];

        getAbsPath((char *)configParams->outputNetFile, outDirName);
        getDirFromPath(outDirName);
        sprintf(perChannelMeanFileName, "%s/%s_LayerPerChannelMean.bin", outDirName, getFileNameFromPath(inConfigFilename));

        FILE * fp = fopen(perChannelMeanFileName,"rb");
        if ( fp != NULL )
        {
          fread(perChannelMeanStats, 1, perChannelMeanMemSize, fp);
          fclose(fp);
        }
        else
        {
          printf("tidlReadPerChannelMeanStatistics : Unable to read Per Channel Mean statistics \n");
          return -1;
        }
    }
  }

  return 0 ;
}

void TIDL_computeMeanActivationShift(float32_tidl * perChannelActShift,
                                    float32_tidl * perChannelMeanPtrFloat,
                                    float32_tidl * perChannelMeanPtrQuantized,
                                    float32_tidl biasCalibrationFactor,
                                    int32_t layerIndex)
{
  int32_t currOffsetInBytes, currOffsetInfloats, perChannelMeanMemSize;
  sTIDL_Network_t * net = &tIDLNetStructure;
  float32_tidl meanFloat, meanQuantized;
  float32_tidl activationDelta;
  float max_diff = -FLT_MAX;
  int32_t max_index;
  for(int i1 = 0; i1 < layerIndex; i1++)
  {
    sTIDL_DataParams_t * dataPrms = &net->TIDLLayers[i1].outData;
    currOffsetInBytes = tidlFindCurrentOffsetForPerChannelMean(net,
                                                              i1,
                                                              &perChannelMeanMemSize);
    currOffsetInfloats = ( currOffsetInBytes / sizeof(float32_tidl) );
    for(int i2 = 0; i2 < dataPrms->dimValues[TIDL_DIM_NUMCH]; i2++)
    {
      if(currOffsetInBytes != -1)    /* if layer is not a data layer */
      {
        meanFloat = perChannelMeanPtrFloat[currOffsetInfloats + i2];
        meanQuantized = perChannelMeanPtrQuantized[currOffsetInfloats + i2];
        perChannelActShift[currOffsetInfloats + i2] = (meanFloat - meanQuantized) * biasCalibrationFactor;
      }
    }
  }
}

void TIDL_updateBiasForBiasCalibration(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, float32_tidl * perChannelMeanDelta, int32_t layerIndex)
{
  int32_t currOffsetInBytes, currOffsetInfloats, perChannelMeanMemSize;
  for (int i = 0; i < layerIndex; i++)
  {
    if  ((((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer)) &&
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.enableBias)) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer) ||
        (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_DetectionOutputLayer)
        )    /* if conv or deconv layer, enableBias must be 1 for update */
    {
      currOffsetInBytes = tidlFindCurrentOffsetForPerChannelMean(&tIDLNetStructure,
                                                              i,
                                                              &perChannelMeanMemSize);
      currOffsetInfloats = ( currOffsetInBytes / sizeof(float32_tidl) );

      float32_tidl * data = (float32_tidl*)pOrgTIDLNetStructure->TIDLPCLayers[i].bias.ptr;
      uint32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].bias.bufSize;
      if(dataSize > 0)
      {
        for(int i1 = 0; i1 < dataSize; i1++)
        {
          data[i1] += perChannelMeanDelta[currOffsetInfloats + i1];
        }
      }
    }
  }
}

/* This function runs the quant stats tool either in float mode or fixed mode.
   Tensor ranges after running stats tools are updated in pOrgTIDLNetStructure */
void TIDL_quantStatsFixedOrFloat(sTIDL_OrgNetwork_t    * pOrgTIDLNetStructure,
                                  sTIDL_Network_t   * pTIDLNetStructure,
                                  tidl_import_config * configParams,
                                  int32_t statsCollectionType)
{
  int32_t numLayers = pOrgTIDLNetStructure->numLayers;

  if ( statsCollectionType == STATS_COLLECTION_FLOAT)
  {
    tidl_import_config importConfigParamsFloat;
    sTIDL_OrgNetwork_t * pOrgTIDLNetStructureFloat = new sTIDL_OrgNetwork_t;
    if ( pOrgTIDLNetStructureFloat == NULL )
    {
      printf("TIDL_quantStatsFixedOrFloat: Unable to allocate memory for pOrgTIDLNetStructureFloat \n");
      return;
    }
    
    *pOrgTIDLNetStructureFloat = *pOrgTIDLNetStructure;
    TIDL_allocAndCopyModelParams(pOrgTIDLNetStructureFloat,
                                                     pOrgTIDLNetStructure,
                                                     numLayers);

    importConfigParamsFloat = *configParams;

    importConfigParamsFloat.numParamBits = 32;
    importConfigParamsFloat.numFeatureBits = 32;

    for (int i = 0; i < TIDL_MAX_ALG_IN_BUFS; i++)
    {
      importConfigParamsFloat.inElementType[i] = TIDL_SinglePrecFloat;
    }
    for (int i = 0; i < TIDL_MAX_ALG_OUT_BUFS; i++)
    {
      importConfigParamsFloat.outElementType[i] = TIDL_SinglePrecFloat;
    }
    tidl_updateWeightElemSize(pOrgTIDLNetStructureFloat, &importConfigParamsFloat, numLayers);
    tidl_convertElementTypeGivenParambits(pOrgTIDLNetStructureFloat, numLayers, 32);
    updatePadAndWriteModel(pOrgTIDLNetStructureFloat, pTIDLNetStructure, &importConfigParamsFloat);
    pTIDLNetStructure->isQuantStatsAvailable = 0;

    /* Call the stats collection in float mode */
    tidlRunQuantStatsTool(pOrgTIDLNetStructureFloat,
                                      pTIDLNetStructure,
                                      &importConfigParamsFloat,
                                      numLayers);

    TIDL_copyTensorStats(pOrgTIDLNetStructure, pOrgTIDLNetStructureFloat, 1);

    TIDL_freeModelParams(pOrgTIDLNetStructureFloat, numLayers);
    if ( pOrgTIDLNetStructureFloat != NULL )
    {
      delete pOrgTIDLNetStructureFloat;
    }
  }
  else
  {
    TIDL_importQuantLayerParams(pOrgTIDLNetStructure,
                                    pTIDLNetStructure,
                                    configParams,
                                    numLayers);
    updatePadAndWriteModel(pOrgTIDLNetStructure, pTIDLNetStructure, configParams);
    pTIDLNetStructure->isQuantStatsAvailable = 0;
    pOrgTIDLNetStructure->quantStats = TIDL_QUANT_STATS_NONE;

    /* Call the stats collection in fixed point mode mode */
    tidlRunQuantStatsTool(pOrgTIDLNetStructure,
                                      pTIDLNetStructure,
                                      configParams,
                                      numLayers);

  }

}

#define TIDL_PI (3.141593)
#define TIDL_BIAS_CALIBRATION_WARMUP_FACTOR (10.0)
#define TIDL_BIAS_CALIBRATION_USE_COSINE_DECAY (0)

int32_t TIDL_runIterativeCalibration(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,
                                               sTIDL_Network_t       * pTIDLNetStructure,
                                               tidl_import_config * configParams
                                               )
{
    sTIDL_OrgNetwork_t * pOrgTIDLNetStructureBkpFloat = NULL;
    float32_tidl     * perChannelMeanPtrFloat = NULL;
    float32_tidl     * perChannelMeanPtrQuantized = NULL;
    float32_tidl     * perChannelMeanDelta = NULL;
    float32_tidl biasCalibrationFactor;
    int32_t perChannelMeanMemSize;
    int32_t numFramesOrig;
    float quantRangeUpdateFactorOrig;
    int32_t numLayers;
    int32_t numBiasCalibFrames;
    const float32_tidl math_pi = TIDL_PI;
    float32_tidl biasCalibrationFactorStart = configParams->biasCalibrationFactor;
    float32_tidl biasCalibrationFactorEnd = 1e-4;
    float32_tidl curIteration;
    const float32_tidl warmupFactor = TIDL_BIAS_CALIBRATION_WARMUP_FACTOR;
    int warmpIters;

    pOrgTIDLNetStructureBkpFloat = new sTIDL_OrgNetwork_t;

    /* Set number of frames for bias calibration */
    numFramesOrig = configParams->numFrames;
    quantRangeUpdateFactorOrig = configParams->quantRangeUpdateFactor;

    numBiasCalibFrames = configParams->numFramesBiasCalibration;

    if (configParams->biasCalibrationIterations == -1)
    {
      if((configParams->calibrationOption == 0) || (configParams->calibrationOption == TIDL_CalibOptionBiasRange))
      {
        configParams->biasCalibrationIterations = 1;
      }
      else
      {
        configParams->biasCalibrationIterations = 50;
      }
    }
    if (configParams->numFramesBiasCalibration == -1)
    {
      if ((configParams->inFileFormat == 2) || (configParams->inFileFormat == 5))
      {
        if (configParams->numFrames == -1)
        {
          numBiasCalibFrames = getNumberOfLinesIntheFile((char *)configParams->inData);
        }
        else
        {
          numBiasCalibFrames = configParams->numFrames;
        }
      }
      else if(((configParams->modelType == TIDL_IMPORT_MODEL_FORMAT_TFLITE_RT) || (configParams->modelType == TIDL_IMPORT_MODEL_FORMAT_ONNX_RT)) && (configParams->inFileFormat == 1))
      {
        numBiasCalibFrames = configParams->numFrames;
      }
      else if (configParams->inFileFormat == 1)
      {
        /* Raw data format keep default same as number of frames*/
        numBiasCalibFrames = configParams->numFrames;
      }
      else if ((configParams->inFileFormat == 0) || (configParams->inFileFormat == 3))
      {
        numBiasCalibFrames = 1;
      }
    }

    configParams->numFrames = numBiasCalibFrames;

    numLayers = pOrgTIDLNetStructure->numLayers;

    /* At this point TIDLNetStructure is not populated so copy PC net to device net */
    tidl_copyPCNetToDeviceNet(pOrgTIDLNetStructure,
                                              pTIDLNetStructure,
                                              configParams,
                                              numLayers);

    pTIDLNetStructure->numLayers = numLayers;

    if (( configParams->calibrationOption & TIDL_CalibOptionBiasCalibration) == TIDL_CalibOptionBiasCalibration)
    {
      /* Allocate memory for perChannelMeanDelta */
      tidlFindCurrentOffsetForPerChannelMean(pTIDLNetStructure, 0, &perChannelMeanMemSize);

      perChannelMeanPtrFloat = (float32_tidl*)malloc(perChannelMeanMemSize);
      if(perChannelMeanPtrFloat == NULL)
      {
        printf("ERROR : TIDL_runBiasCalibration - Not enough memory available perChannelMeanPtrFloat \n");
        return -1;
      }

      perChannelMeanPtrQuantized = (float32_tidl*)malloc(perChannelMeanMemSize);
      if(perChannelMeanPtrQuantized == NULL)
      {
        printf("ERROR : TIDL_runBiasCalibration - Not enough memory available for perChannelMeanPtrQuantized\n");
        return -1;
      }

      perChannelMeanDelta = (float32_tidl*)malloc(perChannelMeanMemSize);
      if(perChannelMeanDelta == NULL)
      {
        printf("ERROR : TIDL_runBiasCalibration - Not enough memory available for mean delta \n");
        return -1;
      }
    }

     *pOrgTIDLNetStructureBkpFloat = *pOrgTIDLNetStructure;
     /* Allocate separate memory for backing up parameters before quantization */
     TIDL_allocAndCopyModelParams(pOrgTIDLNetStructureBkpFloat, pOrgTIDLNetStructure, numLayers);

     /* Run Stats collection in float to find the original per channel mean */
     TIDL_quantStatsFixedOrFloat((pOrgTIDLNetStructure),
                                 (pTIDLNetStructure),
                                 configParams,
                                 STATS_COLLECTION_FLOAT);

     if (( configParams->calibrationOption & TIDL_CalibOptionBiasCalibration) == TIDL_CalibOptionBiasCalibration)
     {
       /*Read the original float mean stats per channel */
       tidlReadPerChannelMeanStatistics(pTIDLNetStructure,
                                        perChannelMeanPtrFloat,
                                        perChannelMeanMemSize,
                                        configParams);
    }

    warmpIters = configParams->biasCalibrationIterations/10;

    /*****    Loop for bias calibration  *****/
    for(int i = 0; i < configParams->biasCalibrationIterations; i++)
    {
      /* Run quant stats tool to get per channel mean means after quantization */
      TIDL_quantStatsFixedOrFloat(pOrgTIDLNetStructure,
                                  pTIDLNetStructure,
                                  configParams,
                                  STATS_COLLECTION_FIXED_POINT);

      if (( configParams->calibrationOption & TIDL_CalibOptionBiasCalibration) == TIDL_CalibOptionBiasCalibration)
      {
        /*Read the per Channel  mean stats per channel */
       tidlReadPerChannelMeanStatistics(pTIDLNetStructure,
                                        perChannelMeanPtrQuantized,
                                        perChannelMeanMemSize,
                                        configParams);
        curIteration = (float32_tidl)i;

#if TIDL_BIAS_CALIBRATION_USE_COSINE_DECAY
        biasCalibrationFactor = biasCalibrationFactorEnd +
                                0.5*(biasCalibrationFactorStart - biasCalibrationFactorEnd) *
                                (1.0 + std::cos(math_pi* curIteration /configParams->biasCalibrationIterations));
#else
        biasCalibrationFactor = configParams->biasCalibrationFactor;
        if ( warmpIters > 0 )
        {
          if((curIteration < warmpIters) ||
            ( curIteration >= (configParams->biasCalibrationIterations - warmpIters)))
          {
            biasCalibrationFactor = (biasCalibrationFactor / warmupFactor);
          }
        }
#endif

        /* Mean delta calculation */
        TIDL_computeMeanActivationShift(perChannelMeanDelta,
                                        perChannelMeanPtrFloat,
                                        perChannelMeanPtrQuantized,
                                        biasCalibrationFactor,
                                        numLayers);

        /* Update bias as per the mean shift observed */
        TIDL_updateBiasForBiasCalibration(pOrgTIDLNetStructureBkpFloat, perChannelMeanDelta, numLayers);
      }

      /* Copy the updated bias to orgTIDLNetStructure, which will be used in next iteration for quantization */
      TIDL_copyModelParams(pOrgTIDLNetStructure, pOrgTIDLNetStructureBkpFloat, numLayers);

      printf("\n \n \n *****************   Calibration iteration number %d completed ************************ \n \n \n \n", i);
    }
    /******   End of bias calibration loop  *******/

    if ( perChannelMeanPtrFloat != NULL )
    {
      my_free(perChannelMeanPtrFloat );
    }

    if ( perChannelMeanPtrQuantized != NULL )
    {
      my_free(perChannelMeanPtrQuantized );
    }

    if (perChannelMeanDelta != NULL)
    {
      my_free(perChannelMeanDelta);
    }

    TIDL_freeModelParams(pOrgTIDLNetStructureBkpFloat, numLayers);
    if ( pOrgTIDLNetStructureBkpFloat != NULL )
    {
      delete pOrgTIDLNetStructureBkpFloat;
    }

    /* revert to original number of frames */
    configParams->numFrames = numFramesOrig;
    configParams->quantRangeUpdateFactor = quantRangeUpdateFactorOrig;

    //TIDL_quantStatsFixedOrFloat(*pOrgTIDLNetStructure, *pTIDLNetStructure, configParams, 1, numLayers);

    /* Run quant stats again to save the final min/max statistics after bias calibration */
//    tidlRunQuantStatsTool((void**)&perChannelMeanPtrFloat);

}


static int32_t TIDL_isIterativeCalibrationRequired(tidl_import_config * configParams)
{
  int32_t isRequired = 0;
  if (( configParams->calibrationOption & TIDL_CalibOptionBiasCalibration) ==
                                          TIDL_CalibOptionBiasCalibration)
  {
    isRequired  = 1;
  }
  else if (( configParams->calibrationOption & TIDL_CalibOptionPerChannelWeightQuantization) ==
                                              TIDL_CalibOptionPerChannelWeightQuantization)
  {
    isRequired = 1;
  }
  else if (( configParams->calibrationOption & TIDL_CalibOptionActivationRange ) ==
                                              TIDL_CalibOptionActivationRange)
  {
    if ( configParams->activationRangeMethod == TIDL_ActivationRangeMethodGlobalHistogram)
    {
      isRequired  = 1;
    }
  }
  else
  {
    isRequired  = 0;
  }

  return isRequired;
}



#define PRECISION_LAYER_DEFAULT          (-1)
#define PRECISION_LAYER_FEATURE_IN_16BIT (1)
#define PRECISION_LAYER_PARAMS_IN_16BIT  (0)

int32_t getDataIdFromName(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,const char * layerName)
{
  int32_t dataId = -1;
  int32_t layerIdx = 0;
  for (layerIdx = 0; layerIdx < pOrgTIDLNetStructure->numLayers; layerIdx++)
  {
   if ( strncmp((const char *)layerName, (const char *)pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outDataNames[0], FILE_NAME_SIZE - 1) == 0 ) /* TODO: Temporary fix, should be cleaned in import tool to error and exit if layer name > 512 chars*/
    {
      dataId = pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dataId;
      break;
    }
  }

  if ( dataId == -1 )
  {
    printf("Invalid Layer Name  %s\n", layerName);
  }

  return dataId;
}

int32_t getUserPrecisionFromDataId(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,
                                   tidl_import_config * params, int32_t dataId)
{
  char paramsIn16BitList[TIDL_NUM_MAX_LAYERS][FILE_NAME_SIZE];
  char featureIn16BitList[TIDL_NUM_MAX_LAYERS][FILE_NAME_SIZE];
  int32_t numParamIn16Bit = 0;
  int32_t numFeatureIn16Bit = 0;

  int32_t userDataId;
  int32_t i= 0;
  int32_t precision = PRECISION_LAYER_DEFAULT;

  numParamIn16Bit   = tidl_getStringsFromList((char *)params->params16bitNamesList,  (char *)paramsIn16BitList, FILE_NAME_SIZE);
  numFeatureIn16Bit = tidl_getStringsFromList((char *)params->outputFeature16bitNamesList, (char *)featureIn16BitList, FILE_NAME_SIZE);

  for ( i = 0; i < numParamIn16Bit; i++)
  {
    userDataId = getDataIdFromName(pOrgTIDLNetStructure, (const char*)paramsIn16BitList[i]);
    if ( dataId == userDataId)
    {
      precision = PRECISION_LAYER_PARAMS_IN_16BIT;
      break;
    }
  }

  for ( i = 0; i < numFeatureIn16Bit; i++)
  {
    userDataId = getDataIdFromName(pOrgTIDLNetStructure, (const char*)featureIn16BitList[i]);
    if ( dataId == userDataId)
    {
      precision = PRECISION_LAYER_FEATURE_IN_16BIT;
      break;
    }
  }

  return precision;

}


int32_t TIDL_increasePrecision(int32_t elementType)
{
  int32_t outElemType;
  if ( elementType == TIDL_SignedChar )
  {
    outElemType = TIDL_SignedShort;
  }
  else if ( elementType == TIDL_UnsignedChar )
  {
    outElemType = TIDL_UnsignedShort;
  }
  else
  {
    outElemType = elementType;
  }

  return outElemType;
}

int32_t TIDL_increaseWeightPrecision(sTIDL_LayerPC_t * layer, int32_t weightsElementSizeInBits)
{
  int32_t retVal = weightsElementSizeInBits;

  if ( weightsElementSizeInBits <= 8 )
  {
    retVal = 16;
  }
  else
  {
    retVal = weightsElementSizeInBits;
  }

  return retVal;
}

int32_t TIDL_doesLayerSupportMixedPrecision(sTIDL_LayerPC_t * layer)
{
  int32_t doesLayeSupportMixedPrecision = 0;

  if ( layer->layerType == TIDL_ConvolutionLayer )
  {
    doesLayeSupportMixedPrecision = 1;
  }
  else if ( layer->layerType == TIDL_DataLayer)
  {
    doesLayeSupportMixedPrecision = 1;
  }
  else if ( layer->layerType == TIDL_BatchNormLayer)
  {
    doesLayeSupportMixedPrecision = 1;
    if ( (layer->actParams.actType == TIDL_Sigmoid) || (layer->actParams.actType == TIDL_Tanh) || (layer->actParams.actType == TIDL_HardSigmoid)||(layer->actParams.actType == TIDL_ELU))
    {
      doesLayeSupportMixedPrecision = 0;
    }
  }
  else if ( layer->layerType == TIDL_EltWiseLayer)
  {
    doesLayeSupportMixedPrecision = 1;
  }
  else if ( layer->layerType == TIDL_PoolingLayer)
  {
    doesLayeSupportMixedPrecision = 1;
    if ((layer->layerParams.poolParams.poolingType == TIDL_MaxPooling) ||
	    /* Disable mixed precision support for Global Pooling Layers with 16 bit to 8 bit conversion */
	   ((layer->layerParams.poolParams.kernelW == 0 && layer->layerParams.poolParams.kernelH == 0 &&
	    (layer->weightsElementSizeInBits == 16) &&
		(tidl_getElementSizeInBits(layer->outData[0].elementType) == 8))))
    {
      doesLayeSupportMixedPrecision = 0;
    }
  }
  else
  {
    /* For all other layer input and output precision will be decided by producer/consumer*/
  }

  return doesLayeSupportMixedPrecision;
}


/* Function checks if a given dataId is the final output of the network and returns -1 if it is not
otherwise returns the corresponding output buffer index */
int32_t TIDL_isLayerNetworkOutput(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, int32_t dataId)
{
  int32_t layerIdx, inBufIdx, userOutBufIdx;
  sTIDL_LayerPC_t * currLayer;

  userOutBufIdx  = -1;

  /* Go through all the layers */
  for ( layerIdx = 0; layerIdx < pOrgTIDLNetStructure->numLayers; layerIdx++)
  {
    currLayer = &pOrgTIDLNetStructure->TIDLPCLayers[layerIdx];
    /* Find layers whos input contains the data Id. This will indicate the producer
    layer's output goes to this layer */
    for ( inBufIdx = 0; inBufIdx < currLayer->numInBufs;inBufIdx++)
    {
      if ( dataId == currLayer->inData[inBufIdx].dataId )
      {
        /* Check if the consumer layer is a data layer. This will indicate
        that this is the final output of the network */
        if ( currLayer->layerType == TIDL_DataLayer )
        {
          char * consumerLayerName = (char *)&currLayer->outDataNames[0][0];

          for (userOutBufIdx = 0; userOutBufIdx < numNetOutData; userOutBufIdx++)
          {
            if (strcmp(consumerLayerName, outDataNames[userOutBufIdx]) == 0)
            {
              break;
            }
          }
          goto Exit;
        }
      }
    }
  }

Exit:

  return  userOutBufIdx;
}

int32_t TIDL_checkConsumerProducerDataType(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,
                                                         int32_t producerLayerIdx)
{
  int32_t layerIdx;
  sTIDL_LayerPC_t * currLayer;
  sTIDL_LayerPC_t * producerLayer;
  int32_t producerElemType;
  int32_t producerDataId;
  int32_t inIdx;
  int32_t updated = 0;

  producerLayer = &pOrgTIDLNetStructure->TIDLPCLayers[producerLayerIdx];
  producerElemType = producerLayer->outData[0].elementType;
  producerDataId   = producerLayer->outData[0].dataId;

  if ( producerLayer->numOutBufs > 0)
  {
    /* Go through all the layers */
    for ( layerIdx = 0; layerIdx < pOrgTIDLNetStructure->numLayers; layerIdx++)
    {
      currLayer = &pOrgTIDLNetStructure->TIDLPCLayers[layerIdx];
      /* Find layers whos input contains the data Id. This will indicate the producer
      layer's output goes to this layer */
      for (inIdx = 0; inIdx < currLayer->numInBufs; inIdx++)
      {
        /* Indicates one of the consumer layer is found */
        if ( producerDataId == currLayer->inData[inIdx].dataId)
        {
          /* Check the element type of producer and consumer are same or not. If not then it
          indicates mismatch which should be corrected*/
          if ( producerElemType != currLayer->inData[inIdx].elementType)
          {
            /* producer 8 bit and consumer expects 16 bit, make producer output to be 16 bit */
            if ( producerElemType <= TIDL_SignedChar )
            {
              producerLayer->outData[0].elementType = TIDL_increasePrecision(producerLayer->outData[0].elementType);
              producerLayer->weightsElementSizeInBits = TIDL_increaseWeightPrecision(producerLayer,
                                                              producerLayer->weightsElementSizeInBits );
              /* Check if producer layer supports mixed precision, if not then make output and input to be same
              bit depth*/
              if (TIDL_doesLayerSupportMixedPrecision(producerLayer) == 0 )
              {
                int32_t i;
                for ( i = 0; i < producerLayer->numInBufs; i++)
                {
                  producerLayer->inData[i].elementType = TIDL_increasePrecision(producerLayer->inData[i].elementType);
                }
              }

            }
            else
            {
              /* Producer is 16 bit and consumer is 8bit, make consumer's all inputs to 16 bit */
              int32_t i;
              currLayer->weightsElementSizeInBits = TIDL_increaseWeightPrecision(currLayer,
                                                              currLayer->weightsElementSizeInBits );
              for ( i = 0; i < currLayer->numInBufs; i++)
              {
                currLayer->inData[i].elementType = TIDL_increasePrecision(currLayer->inData[i].elementType);
              }
              /* Check if producer layer supports mixed precision, if not then make output and input to be same
              bit depth*/
              if (TIDL_doesLayerSupportMixedPrecision(currLayer) == 0 )
              {
                currLayer->outData[0].elementType = TIDL_increasePrecision(currLayer->outData[0].elementType);
              }
            }
            updated = 1;
          }
        }
      }

      if ( updated == 1 )
      {
        break;
      }
    }
  }
  return updated;
}


int32_t TIDL_isAllFeatureRangeAvailable(sTIDL_OrgNetwork_t *pOrgNetStructure, int32_t layerIndex)
{
  int32_t i, featureRangeAvailable = 1;

  for (i = 0; i < layerIndex; i++)
  {
    if ((pOrgNetStructure->TIDLPCLayers[i].layerType != TIDL_DataLayer) && (pOrgNetStructure->TIDLPCLayers[i].actParams.actType != TIDL_Clip)
        && (pOrgNetStructure->TIDLPCLayers[i].layerType != TIDL_PadLayer)
        && (
          (pOrgNetStructure->TIDLPCLayers[i].layerType != TIDL_BatchNormLayer) || 
          (pOrgNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_PRelU) || 
           (pOrgNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_Sigmoid)  || 
           (pOrgNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_Tanh) ||
           (pOrgNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_HardSigmoid)  || 
           (pOrgNetStructure->TIDLPCLayers[i].actParams.actType == TIDL_ELU) 
           )
        && (pOrgNetStructure->TIDLPCLayers[i].layerType != TIDL_DataConvertLayer) && (pOrgNetStructure->TIDLPCLayers[i].layerType != TIDL_ConstDataLayer))
        /* For pre-calibrated models, layers added by TIDL should be eliminated from this check to ensure bias calibration is not run on these models
        due to featureRangeAvailable set to 0 in this function */
    {
      featureRangeAvailable = 0;
    }
  }
  if(featureRangeAvailable == 1)
  {
    if (pOrgNetStructure->TIDLPCLayers[i].layerType != TIDL_DataLayer)
    {
      pOrgNetStructure->TIDLPCLayers[i].outData[0].minTensorValue = pOrgNetStructure->TIDLPCLayers[i].actParams.clipMin;
      pOrgNetStructure->TIDLPCLayers[i].outData[0].maxTensorValue = pOrgNetStructure->TIDLPCLayers[i].actParams.clipMax;
      float max = fabs(pOrgNetStructure->TIDLPCLayers[i].outData[0].minTensorValue) > fabs(pOrgNetStructure->TIDLPCLayers[i].outData[0].maxTensorValue) ?
                  fabs(pOrgNetStructure->TIDLPCLayers[i].outData[0].minTensorValue) : fabs(pOrgNetStructure->TIDLPCLayers[i].outData[0].maxTensorValue);
      max = (float)ceil(log((double)max) / log((double)2));
      max = pow(2.0, (double)max);
      if (max != 0)
      {
        pOrgNetStructure->TIDLPCLayers[i].outData[0].tensorScale = ((1.0*(1 << (NUM_WHGT_BITS - 1))) / max);
      }
      else
      {
        pOrgNetStructure->TIDLPCLayers[i].outData[0].tensorScale = 1.0;
      }

    }
  }
  return (featureRangeAvailable);
}

void TIDL_setDefaultWeightElementBits(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,
                                           tidl_import_config * params,
                                           int32_t numLayers)
{
  int32_t layerIdx;
  sTIDL_LayerPC_t * currLayer;
  int32_t inIdx;
  /* This is required because in mixed precision weightElementSizeInBits is used to decide
  the processing size */
  for ( layerIdx = 0; layerIdx < numLayers; layerIdx++)
  {
    currLayer = &pOrgTIDLNetStructure->TIDLPCLayers[layerIdx];
    /* Set default weightElementSizeInBits based on original precision */
    currLayer->weightsElementSizeInBits = NUM_WHGT_BITS;

    if ( currLayer->layerType == TIDL_DataConvertLayer )
    {
        /* If for data convert layer input is float then processing is
        expected to be in float and hence set weightsElementSizeInBits
        to 32 bits as it indicates the size of processing */
      currLayer->weightsElementSizeInBits = tidl_getElementSizeInBits(currLayer->inData[0].elementType);
    }

    for ( inIdx = 0;inIdx < currLayer->numInBufs; inIdx++)
    {
      if (( currLayer->outData[0].elementType != TIDL_SinglePrecFloat ) &&
          ( currLayer->inData[inIdx].elementType != TIDL_SinglePrecFloat ))
      {
        /* Data Convert layer are not handled via mixed precision flow */
        if ( currLayer->layerType != TIDL_DataConvertLayer )
        {
          /* If input and output data size of any layer is different then
          increase weight preicision to indicate mixed precision */
          if ( tidl_getElementSizeInBits(currLayer->outData[0].elementType) !=
                tidl_getElementSizeInBits(currLayer->inData[inIdx].elementType) )
          {
            currLayer->weightsElementSizeInBits = TIDL_increaseWeightPrecision(currLayer, currLayer->weightsElementSizeInBits);
          }
        }
      }
    }
  }
}

/* First Pass : Initialize each layers input and output datatype based on
user given/automated parameters.
   Secong Pass : if there is any difference between two layers datatype then
   correct it*/
void TIDL_convert8bitLayersTo16Bit(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,
                                           tidl_import_config * params,
                                           int32_t numLayers)
{
  int32_t layerIdx;
  sTIDL_LayerPC_t * currLayer;
  int32_t outDataId;
  int32_t precision;
  int32_t outBufIdx;
  int32_t inIdx;

  /* First Pass : Initialize each layers input and output datatype based on
user given/automated parameters.*/
  for ( layerIdx = 0; layerIdx < numLayers; layerIdx++)
  {
    currLayer = &pOrgTIDLNetStructure->TIDLPCLayers[layerIdx];
    outDataId = currLayer->outData[0].dataId;

    precision = getUserPrecisionFromDataId(pOrgTIDLNetStructure, params, outDataId);

    if ( currLayer->layerType == TIDL_ConvolutionLayer )
    {
      if (( params->calibrationOption & TIDL_CalibOptionMixedPrecisionInput) ==
                      TIDL_CalibOptionMixedPrecisionInput)
      {
        /* If convolution layers input is a data layer then enable higher weight precision*/
        if (pOrgTIDLNetStructure->TIDLPCLayers[currLayer->inData[0].dataId].layerType == TIDL_DataLayer )
        {
          precision = PRECISION_LAYER_PARAMS_IN_16BIT;
        }
      }

      if (( params->calibrationOption & TIDL_CalibOptionMixedPrecisionDepthwise) ==
                      TIDL_CalibOptionMixedPrecisionDepthwise)
      {
        int32_t numGroups = currLayer->layerParams.convParams.numGroups;
        int32_t numInChannels = currLayer->layerParams.convParams.numInChannels;
        int32_t numOutChannels = currLayer->layerParams.convParams.numOutChannels;
        /* If the layer is depthewise convolution layer, then enable higher weight precision*/
        if((numGroups == numInChannels) && (numGroups == numOutChannels) && (numInChannels == numOutChannels))
        {
          precision = PRECISION_LAYER_PARAMS_IN_16BIT;
        }
      }
    }

    outBufIdx = TIDL_isLayerNetworkOutput(pOrgTIDLNetStructure, outDataId);

    if ( outBufIdx != - 1)
    {
      /* Increase activation precision if output size is 2 bytes */
      if ( params->outElementSize[outBufIdx] == 2 )
      {
        precision = PRECISION_LAYER_FEATURE_IN_16BIT;
      }
    }

    if ( precision != PRECISION_LAYER_DEFAULT)
    {
      currLayer->weightsElementSizeInBits = TIDL_increaseWeightPrecision(currLayer,
                                                      currLayer->weightsElementSizeInBits );
      if (precision == PRECISION_LAYER_FEATURE_IN_16BIT )
      {
        currLayer->outData[0].elementType = TIDL_increasePrecision(currLayer->outData[0].elementType);
        /* If the layer doesn't support mixed precision then input dataType for the same should
        also increase. Two scenario's this can happen, if input is signed or currently  we don't have
        implementation to convert 8 bit to 16 bit */
        if (TIDL_doesLayerSupportMixedPrecision(currLayer) == 0 )
        {
          for ( inIdx = 0; inIdx < currLayer->numInBufs; inIdx++ )
          {
            currLayer->inData[inIdx].elementType = TIDL_increasePrecision(currLayer->inData[inIdx].elementType);
          }
        }
      }
      else if (precision == PRECISION_LAYER_PARAMS_IN_16BIT )
      {
        /* If layer doesn't support mixed precision then increase the precision of both inputs and output in this
        case */
        if (TIDL_doesLayerSupportMixedPrecision(currLayer) == 0 )
        {
          for ( inIdx = 0; inIdx < currLayer->numInBufs; inIdx++ )
          {
            currLayer->inData[inIdx].elementType = TIDL_increasePrecision(currLayer->inData[inIdx].elementType);
          }
          currLayer->outData[0].elementType = TIDL_increasePrecision(currLayer->outData[0].elementType);
        }
      }
    }
  }

  int32_t updated;
  int32_t outputElemType;
  /* Second pass: Run through the network and update the consumer/producer data type if
  there is a mismtach between the two. Repeat this process till we go to a stage
  that no update is done in the network */
  do
  {
    updated = 0;
    for ( layerIdx = 0; layerIdx < numLayers; layerIdx++)
    {
      updated = TIDL_checkConsumerProducerDataType(pOrgTIDLNetStructure, layerIdx);
      if ( updated == 1 )
      {
        break;
      }
    }
  }while (updated != 0 );

}


// This function post-processes the network after it has been imported and optimized.
uint32_t TIDL_import_quantize(uint32_t layerIndex)
{
  /* At this point model is frozen */
  int32_t i;
  /* Set default outElementSize based on numParamBits*/
  for ( i = 0; i < TIDL_MAX_ALG_OUT_BUFS; i++)
  {
    if ( gParams.outElementSize[i] == -1 )
    {
      if ( gParams.numParamBits <= 8 )
      {
        gParams.outElementSize[i] = 1;
      }
      else if ( gParams.numParamBits <= 16 )
      {
        gParams.outElementSize[i] = 2;
      }
      else
      {
        gParams.outElementSize[i] = 4;
      }
    }
  }

  TIDL_setDefaultWeightElementBits(&orgTIDLNetStructure, &gParams , layerIndex );

  if (( gParams.numParamBits <= 8 ) && (gParams.enableHighResOptimization == 0))
  {
    TIDL_convert8bitLayersTo16Bit(&orgTIDLNetStructure, &gParams , layerIndex );
  }

  if(gParams.enableHighResOptimization == 1)
  {
    gParams.compileConstraintsFlag |= 0x80;
  }

  if ( (gParams.numParamBits < 32) )
  {
    /* Per channel quantization is only applicable with power of quantization, hence force it if its not */
    if (( gParams.calibrationOption & TIDL_CalibOptionPerChannelWeightQuantization) == TIDL_CalibOptionPerChannelWeightQuantization)
    {
      int32_t depthwiseConvExists = TIDL_depthwiseConvExists(&orgTIDLNetStructure, layerIndex);
      if(depthwiseConvExists == 1)
      {
        gParams.quantizationStyle = TIDL_QuantStyleP2Dynamic;
      }
    }

    tIDLNetStructure.isQuantStatsAvailable = 0;
    if(gParams.quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
    {
      tIDLNetStructure.isQuantStatsAvailable =  TIDL_isAllFeatureRangeAvailable(&orgTIDLNetStructure, layerIndex);
      if(tIDLNetStructure.isQuantStatsAvailable == 0)
      {
        printf("Import Error: TFL PTQ Model with all ranges not supplied\n");
        exit(-1);
      }
  
      TIDL_importQuantLayerParams_HPTQ(&orgTIDLNetStructure,
                                    &tIDLNetStructure,
                                    &gParams,
                                    orgTIDLNetStructure.numLayers);
      updatePadAndWriteModel(&orgTIDLNetStructure, &tIDLNetStructure, &gParams);
    }
    else
    {
    TIDL_runIterativeCalibration(&orgTIDLNetStructure,
                              &tIDLNetStructure,
                              &gParams);
    TIDL_importQuantLayerParams(&orgTIDLNetStructure,
                                    &tIDLNetStructure,
                                    &gParams,
                                    orgTIDLNetStructure.numLayers);
    updatePadAndWriteModel(&orgTIDLNetStructure, &tIDLNetStructure, &gParams);
    }
  }
  else
  {
    for (int i = 0; i < TIDL_MAX_ALG_IN_BUFS; i++)
    {
      gParams.inElementType[i] = TIDL_SinglePrecFloat;
    }
    tIDLNetStructure.isQuantStatsAvailable = 1;
    updatePadAndWriteModel(&orgTIDLNetStructure, &tIDLNetStructure, &gParams);
    /* Float inference is only supported in ref only flow so do not execute network compiler */
    gParams.executeNetworkCompiler = 0;
  }

  return 0;
}
