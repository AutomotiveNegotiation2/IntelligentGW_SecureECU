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
@file    tidl_device_functions.c
@brief   This file defines private device specific functions.
----------------------------------------------------------------------------
*/

#include "tidl_device_functions.h"
#include "tidl_deviceInfo.h"


/**
 * @brief  To find total of number of handles 
 * 
 * @param inWidth : Width of the input buffer
 * @param procSize : Processing size of the dataflow
 * @param dmaFreq : DMA freq for dataflow
 * @param Fc : Kernel freq
 * @return int32_t : Total no of handles
 */
int32_t TIDL_getRowFlowHandleCount(int32_t inWidth, const sDataFlowInfo_t* dataFlowInfo, int32_t Fc, int32_t Fr, int32_t targetDevice, int32_t isLastBlockHandleNeeded)
{

  int32_t nHandles = 1;
#if  defined (__C7120__)  || defined (__C7504__)
  //Temporarily set to reflect worst case for TDA4AM
  int32_t nTop;
  int32_t nCentre;
  int32_t nBottom;
  int32_t filterMaxDim = Fr > Fc ? Fr : Fc;
  int32_t nCirc = (filterMaxDim/2) * 2 + 1;
  if(TRUE == TIDL_isPadOTF(targetDevice))
  {
    if(dataFlowInfo->procSize + dataFlowInfo->preFetch  >= dataFlowInfo->requiredInPlaneSize)
    {
      nHandles = 1;
    }
    else
    {
      nTop = ALIGN(inWidth,dataFlowInfo->procSize) / (dataFlowInfo->procSize);
      nCentre = nCirc;
      nBottom =  nCirc;
      if(nTop > nBottom)
      {
        nBottom = nTop;
      }
      nHandles =  (nTop + nCentre + nBottom);
    }
    if(isLastBlockHandleNeeded)
    {
      /*An additional set of handles is created to handle the scenario where subMChannels is not the same as
        the regular handles*/
      nHandles *= 2; 
    }
  }
  else
  {
    nHandles = 1;
  }
#else
  {
    nHandles = 1;
  }
#endif

  return nHandles;

}

/**
 * @brief To find the total number of handles
 * 
 * @param deviceName  : the device used 
 * @param dataFlowType : the type of the DMA dataFlow 
 * @param inWidth : Width of the input buffer
 * @param dataFlowInfo : Dataflow information from NC
 * @param kernelWidth : Width of the kernel size
 * @return int32_t : total of handles 
 */
int32_t TIDL_getSubHandleCount(int32_t deviceName, int32_t dataFlowType, int32_t inWidth, const sDataFlowInfo_t* dataFlowInfo, int32_t kernelWidth, int32_t kernelHeight, int32_t isLastBlockHandleNeeded)
{
  int32_t nSubHandles = 1;
  
  if(TRUE == TIDL_isBiasHighPrecision(deviceName))
  {
	if(dataFlowInfo != NULL)
	{
	  if(( dataFlowType == (int32_t)ROW_LINEAR ) || (dataFlowType == (int32_t)ROW_CIRCULAR ))
	  {
	    if(dataFlowInfo->procSize + dataFlowInfo->preFetch >= dataFlowInfo->requiredInPlaneSize)
	    {
	      nSubHandles = 1;
        if(isLastBlockHandleNeeded == TRUE)
        {
          nSubHandles *= 2;
        }
	    }
	    else
	    {
	      nSubHandles = TIDL_getRowFlowHandleCount(inWidth, dataFlowInfo, kernelWidth, kernelHeight, deviceName, isLastBlockHandleNeeded);
	    }     
	  }  
	}
  }

  return nSubHandles;

}

/**
 * @brief To get the size of the bias parameters
 * 
 * @param deviceName :  the device used 
 * @param numOutChannels : the number of output channels
 * @return int32_t : returns the biasParamSize
 */
int32_t TIDL_getBiasParamSize(int32_t deviceName, int32_t numOutChannels)
{
  int32_t biasParamSize = 0;

  if(TIDL_isBiasHighPrecision(deviceName) == TRUE)
  {
    biasParamSize = (numOutChannels * ((int32_t)( ((int32_t)(sizeof(int64_t))))));//AM Specific change
  }
  else
  {
    biasParamSize = (numOutChannels * ((int32_t)( ((int32_t)(sizeof(int32_t))))));
  }

  return biasParamSize;

}

//Bias Split Wrapper (8 Bit only right now):
/**
 * @brief The function does the bias split for the conv parameters
 * 
 * @param deviceName : the device used
 * @param dataFlowType : the type of the DMA dataFlow used
 * @param srcPtr : Pointer to the source buffer
 * @param dstPtr : Pointer to the destination buffer
 * @param biasB : Pointer to the bias buffer
 * @param dataSize : no of output channels
 * @param inScaleFactor : scale factor for the input 
 * @param satLow : Min value of the saturation
 * @param satHigh : Max value of the saturation 
 * @param biasBMax : the max value of the bias values
 * @param inFeatSign : the sign of the input feature map
 */
template <class Tdst, class Tsrc, class TBias>
void TIDL_conv2dBiasSplit(int32_t deviceName, int32_t dataFlowType, int32_t procElemSize, Tsrc * srcPtr, Tdst * dstPtr, TBias * biasB, int32_t dataSize, float inScaleFactor, int32_t satLow, int32_t satHigh, int32_t biasBMax , int32_t inFeatSign)
{
  if((TIDL_isBiasHighPrecision(deviceName) == TRUE) && ((dataFlowType == (int32_t)ROW_LINEAR ) || (dataFlowType == (int32_t)ROW_CIRCULAR)))
  {
    if (procElemSize == 1)
    {
      TIDL_AM_conv2dBiasSplit(srcPtr, (int32_t*)dstPtr, biasB, dataSize, inScaleFactor, satLow, satHigh, biasBMax, inFeatSign);
    }
    else
    {
      TIDL_AM_conv2dBiasSplit(srcPtr, (int64_t*)dstPtr, biasB, dataSize, inScaleFactor, satLow, satHigh, biasBMax, inFeatSign);
    }
  }
  else
  {
    TIDL_conv2dBiasSplit(srcPtr, dstPtr, biasB, dataSize, inScaleFactor, satLow, satHigh, biasBMax, inFeatSign);
  }

}

int32_t TIDL_isLastSubMBlockHandleNeeded(int32_t subMChannels, int32_t No, int32_t stridedFlow, int32_t targetDevice)
{
  int32_t lastBlockCase = FALSE;
  if(((No % subMChannels) != 0) && stridedFlow != 0 && (TIDL_isPadOTF(targetDevice) == TRUE))
  {
    lastBlockCase = TRUE;
  }
  return lastBlockCase;
}

//Template Instances:
template void TIDL_conv2dBiasSplit<signed char, short, int32_t>(int, int, int, short*, signed char*, int*, int, float, int, int, int, int);
template void TIDL_conv2dBiasSplit<short, short, int>(int, int, int, short*, short*, int*, int, float, int, int, int, int);
