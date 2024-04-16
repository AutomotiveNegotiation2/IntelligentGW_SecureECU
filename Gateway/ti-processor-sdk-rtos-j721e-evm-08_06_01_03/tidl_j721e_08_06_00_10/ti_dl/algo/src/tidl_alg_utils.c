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
@file    tidl_alg.c
@brief   This file contains TILD alg inteface implementation
@version 0.1 (Oct 2016) : Initial version [ADK]
@version 0.5 (Jan 2017) : Cleaned up [ADK]
----------------------------------------------------------------------------
*/
#include "tidl_alg_int.h"
#include "tidl_types.h"
#include "tidl_layer.h"
#include "itidl_ti.h"
#include "tidl_genericFlow_c7x.h"
#include "perfsim.h"
#include "tidl_priv_algo.h"
#include "tidl_deviceInfo.h"
#include "tidl_device_functions.h"
#include "tidl_device_utils.h"
#include "tidl_alg_utils.h"
#include "tidl_commonUtils.h"
#include "tidl_innerProduct_mma.h"

using namespace c7x;

#include "math.h"
#include "float.h"


#define TIDL_L3_SCRATCH_SIZE (128U*1024U)
#define TIDL_L3_MSMC_DDR_STAGING_MEM  ( 1025U * 1024U)

#define USE_16BIT_BIAS_FOR_8BIT_MODE (1)



 void TIDL_getMMAv2_ScaleAndShift(float scaleRatio, uint8_t *scale, uint8_t *shift)
{
  int32_t shiftBits = 0;
  float newScaleRatio = scaleRatio;
  //int32_t mmaV2MaxScale = 255;
  //Check if scaleRatio > 255
  if(scaleRatio > 255)
  {
    printf("TIDL_getMMAv2_ScaleAndShift: ScaleRatio exceeds representation capability\n");
  }
  //Since exponent goes only in one direction, repeated multiplication with 2 is performed till it exceeds the max range.
  while(1)
  {
    newScaleRatio *= 2; 
    if(shiftBits >= 40 )
    {
      break; //Max capability of a right shift of 40 for 8-bit.
    }
    else if(newScaleRatio > 255.0)
    {
      newScaleRatio /= 2; 
      break;
    }
    shiftBits++;
  }
  
  *shift        = shiftBits;
  /*Add nudge of 0.5 to round correctly:*/
  *scale        = (uint8_t) (newScaleRatio + 0.5);
}

void TIDL_getMMAv2_EltwiseScalesAndShift(float scale1, float scale2, uint8_t *intScale1, uint8_t *intScale2,uint8_t *cScale, uint8_t *shift)
{
  float fMax;
  float fMin;
  int32_t maxScaleID;
  /*TIDL's MMA based eltwise addition kernel has a restriction that the scales in the A vector and B panel need to be 7-bit,
    hence the max ceiling is set to 127U (0b1111111)*/
  uint8_t fScaleVal = 127U;
  if(scale1 > scale2)
  {
    maxScaleID = 0;
    fMax = scale1;
    fMin = scale2;
  }
  else
  {
    maxScaleID = 1;
    fMax = scale2;
    fMin = scale1;
  }
  float fVal = fMax/(float)fScaleVal;
  uint8_t iMin;
  TIDL_getMMAv2_ScaleAndShift(fVal,cScale,shift);
  float commonFactor = (*cScale)/(pow(2,(*shift)));
  iMin = floor(fMin/commonFactor);
  /*Add nudge of 0.5 to round correctly:*/
  if(maxScaleID == 0)
  {
    *intScale1 = fScaleVal + 0.5;
    *intScale2 = iMin + 0.5; 
  }
  else
  {
    *intScale1 = iMin + 0.5;
    *intScale2 = fScaleVal + 0.5; 
  }
  
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_getSysScratchPtr
@brief      Function gives you a pointer to system memory used to store networks
            intermediate output
@param      bufInfo : Pointer to buffer info. This will come from dataflow
@param      sysScratchPtr    : Pointer which stores the base pointer for all system scratch
@param      baseAccessFlag   : Set it to one to get base pointer of feature map. Set it to zero to
                             go to the location where DMA/CPU will READ/WRITE.

@remarks    None
@return     Pointer to the memory. NULL if  buffers accessor is NONE
----------------------------------------------------------------------------
*/
void * TIDL_getSysScratchPtr(const sBufferInfo_t * bufInfo, const TIDL_sysScratchPtr *sysScratchPtr, uint32_t baseAccessFlag)
{
  uint8_t * ptr = NULL;
  int32_t addrOffset;
  if ( baseAccessFlag == 1U)
  {
    addrOffset = bufInfo->baseMem;
  }
  else
  {
    addrOffset = bufInfo->baseMem + bufInfo->accessoffset;
  }


  if ( bufInfo->space == (int32_t)L2 )
  {
    ptr = &(sysScratchPtr->l2BasePtr[addrOffset]);
  }
  else if ( bufInfo->space == (int32_t)MSMC )
  {
    ptr = &(sysScratchPtr->l3BasePtr[addrOffset]);
  }
  else if ( bufInfo->space == (int32_t)DDR )
  {
    ptr = &(sysScratchPtr->ddrBasePtr[addrOffset]);
  }
  else
  {
    ptr = NULL;
  }

  return ptr;
}

/**
 * @brief This function fills padded rows with zero
 *
 * @param ptr : Buffer pointer that needs pad filling
 * @param bufInfo : Properties of the buffer to be filled
 * @param width : Width of the buffer
 * @param height : Height of the buffer
 * @param linePitch : Pitch of the buffer between two rows
 * @param channelPitch :Pitch of the buffer between two channels
 * @param dmautilsContext : Memory to store DMA properties
 * @param zeroVec : Vector containing zeros for row filling
 * @param isPadDmaPending : Flag to indicate the DMA trigger status
 * @param trMem : Memory to store DMA trasfer properties
 * @param elementType : The element type of the pad buffer
 * @param paddingType : Indicates the type of padding to be done
 * @param padLayerParams : Layer level parameters of the Pad layer
 * @param outDataPadH : Pad height of the output buffer
 * @param outDataPadW : Pad Width of the output buffer
 * @param isFlowCtrlNatc : Flag to indicate the flow status
 * @param perChannelPadValPtr : Pointer indicating Pad values per channel
 * @return int32_t : retuns the status of Pad filling
 */
int32_t  TIDL_FillPaddedRows(uint8_t * ptr,
                                     sBufferInfo_t * bufInfo,
                                     int32_t width,
                                     int32_t height,
                                     int32_t numBatches,
                                     int32_t linePitch,
                                     int32_t channelPitch,
                                     uint32_t batchPitch,
                                     void * dmautilsContext,
                                     uint8_t *zeroVec,
                                     uint8_t *isPadDmaPending,
                                     uint8_t * trMem,
                                     int32_t elementType,
                                     int32_t paddingType,
                                     void * padLayerParams,
                                     int32_t outDataPadH,
                                     int32_t outDataPadW,
                                     int32_t padFillValue,
                                     int32_t isFlowCtrlNatc,
                                     void * perChannelPadValPtr)
{

  int32_t i, j, k;
  int32_t retVal = IALG_EOK;
  int32_t elementSize = TIDL_getDatElementSize(elementType);

  int32_t orgBufHeight = bufInfo->bufHeight;

  bufInfo->bufHeight = bufInfo->bufHeight / numBatches;

  /* We have allocated only 1k of zero vector so maximum supported offset filling via dma is 1k */
  if(((dmautilsContext == NULL) || (bufInfo->accessoffset > ((int32_t)TIDL_1K_ZERO_VECTOR))) && (TIDL_PADDING_TYPE_PAD_LAYER != paddingType)
     && (TIDL_PADDING_TYPE_PAD_LAYER_BOTH != paddingType) && (TIDL_PADDING_TYPE_PAD_LAYER_TOP != paddingType) && (TIDL_PADDING_TYPE_PAD_LAYER_BOTTOM != paddingType))
  {
    for(k=0; k<numBatches; k++)
    {
    for(j=0; j<bufInfo->bufHeight; j++)
    {
      if(TIDL_PADDING_TYPE_BOTH == paddingType)
      {
        for(i=0; i<bufInfo->accessoffset; i++)
        {
          ptr[(j*channelPitch) + i] = padFillValue;
          ptr[(j*channelPitch) + i + (bufInfo->activeBufWidth- bufInfo->accessoffset)] = padFillValue;
        }
      }
      else if(TIDL_PADDING_TYPE_TOP == paddingType)
      {
        for(i=0; i<bufInfo->accessoffset; i++)
        {
          ptr[j*channelPitch + i] = padFillValue;
        }
      }
      else if(TIDL_PADDING_TYPE_BOTTOM == paddingType)
      {
        for(i=0; i<bufInfo->accessoffset; i++)
        {
          ptr[j*channelPitch + i + ((outDataPadH + height)*linePitch)] = padFillValue;
        }
      }
      else if((TIDL_PADDING_TYPE_TOP_LEFT    == paddingType) ||
              (TIDL_PADDING_TYPE_ST_TOP_LEFT == paddingType))
      {
        for(i=0; i<bufInfo->padCReq*elementSize; i++)
        {
          ptr[j*channelPitch+bufInfo->accessoffset-(bufInfo->padCReq*elementSize) + i] = padFillValue;
        }
      }
      else
      {
        /* Do nothing */
      }
    }
    ptr = ptr + batchPitch;
    }
  }
  else
  {
    for(k=0; k<numBatches; k++)
    {
      TIDL_DspFillPaddedRows((ptr)+(k*batchPitch), bufInfo, width, height, linePitch,channelPitch,
                                     dmautilsContext, zeroVec, isPadDmaPending, trMem,
                                     elementType, paddingType, padLayerParams, outDataPadH, outDataPadW, isFlowCtrlNatc, perChannelPadValPtr);
      
      if(k < (numBatches-1))
      {
        DmaUtilsAutoInc3d_wait(dmautilsContext, TIDL_DMA_CHANNEL_MEMCPY);
        (void)DmaUtilsAutoInc3d_deconfigure(dmautilsContext, TIDL_DMA_CHANNEL_MEMCPY, trMem, 1);
      }
    }
  }
  bufInfo->bufHeight = orgBufHeight;
  return retVal;
}

/**
 * @brief This function fills padded columns with zero
 *
 * @param ptr : Buffer pointer that needs pad filling
 * @param bufInfo : Properties of the buffer to be filled
 * @param width : Width of the buffer
 * @param height : Height of the buffer
 * @param linePitch : Pitch of the buffer between two rows
 * @param channelPitch :Pitch of the buffer between two channels
 * @param elementType : The element type of the pad buffer
 * @param flowCtrl : Flag to indicate the flow status
 * @param paddingType : Indicates the type of padding to be done
 * @param padLayerParams : Layer level parameters of the Pad layer
 * @param outDataPadH : Pad height of the output buffer
 * @param outDataPadW : Pad Width of the output buffer
 * @param perChannelPadValPtr : Pointer indicating Pad values per channel
 * @return int32_t : retuns the status of Pad filling
 */
 int32_t  TIDL_FillPaddedCols(uint8_t * ptr, const sBufferInfo_t * bufInfo, int32_t width, int32_t height, int32_t numBatches,
                                      int32_t linePitch, int32_t channelPitch, uint32_t batchPitch, int32_t elementType, int32_t flowCtrl, int32_t paddingType,
                                      void * padLayerParams, int32_t outDataPadH, int32_t outDataPadW,int32_t padFillValue, void * perChannelPadValPtr)
{
  int32_t i;
  int32_t ptrOffset;
  int32_t heightToPad;
  int32_t elementSize = TIDL_getDatElementSize(elementType);

  ptrOffset = bufInfo->accessoffset - (bufInfo->padC * elementSize);
  heightToPad = height + bufInfo->padR;
  int32_t numColPad = bufInfo->padC * elementSize;

  int32_t isZeroPaddingNeeded = 0;
  if(paddingType == TIDL_PADDING_TYPE_PAD_LAYER)
  {
    sTIDL_PadLayerParams_t * padParams = (sTIDL_PadLayerParams_t *)padLayerParams;
    int32_t padLayerPadT = padParams->padT;
    int32_t padLayerPadL = padParams->padL;
    int32_t padLayerPadR = padParams->padR;
    ptrOffset = ((linePitch * (padLayerPadT + outDataPadH)) - padLayerPadR) * elementSize; //bufInfo->accessoffset - (bufInfo->padC * elementSize);
    numColPad = (outDataPadW + padLayerPadL + padLayerPadR) * elementSize;
    if(padParams->padType == TIDL_PadZero)
    {
      isZeroPaddingNeeded = 1;
    }
  }

  if(((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) ||
      ((flowCtrl & TIDL_FLOW_CTRL_DSP_NATC) == TIDL_FLOW_CTRL_DSP_NATC))
  {
    if((paddingType == TIDL_PADDING_TYPE_PAD_LAYER) && isZeroPaddingNeeded == 0)
    {
      /* Don't do 0 padding for pad layer if layer has non zero pad requirement */
      /* Non zero padding for NATC done as part of REF flow itself */
    }
    else
    {
      int32_t  j, k, n;
      for (n = 0; n < numBatches; n++)
      {
        for (j = 0; j < bufInfo->bufHeight; j++)
        {
          for (i = 0; i < heightToPad; i++)
          {
            for (k = 0; k < numColPad; k++)  //bufInfo->padC*elementSize
            {
              ptr[ptrOffset + n*batchPitch + j*channelPitch + i*linePitch*elementSize + k] = (int8_t)padFillValue;
            }
          }
        }
      }
    }
  }
  else
  {

    if(TIDL_PADDING_TYPE_PAD_LAYER == paddingType)
    {
      for (int32_t n = 0; n < numBatches; n++)
      {
      if(elementType == TIDL_UnsignedChar)
      {
        uchar_vec padVector = (uchar_vec)0;
        TIDL_DspFillPaddedColsPadLayer((uint8_t *)ptr+ n*batchPitch, padVector, bufInfo, width, height, linePitch, channelPitch, elementSize, flowCtrl,
                                    paddingType, padLayerParams, outDataPadH, outDataPadW, perChannelPadValPtr);
      }
      else if(elementType == TIDL_SignedChar)
      {
        char_vec padVector = (char_vec)0;
        TIDL_DspFillPaddedColsPadLayer((int8_t *)ptr+ n*batchPitch, padVector, bufInfo, width, height, linePitch, channelPitch, elementSize, flowCtrl,
                                    paddingType, padLayerParams, outDataPadH, outDataPadW, perChannelPadValPtr);
      }
      else if(elementType == TIDL_UnsignedShort)
      {
        ushort_vec padVector = (ushort_vec)0;
        TIDL_DspFillPaddedColsPadLayer((uint16_t *)(ptr+ n*batchPitch), padVector, bufInfo, width, height, linePitch, channelPitch, elementSize, flowCtrl,
                                    paddingType, padLayerParams, outDataPadH, outDataPadW, perChannelPadValPtr);
      }
      else if(elementType == TIDL_SignedShort)
      {
        short_vec padVector = (short_vec)0;
        TIDL_DspFillPaddedColsPadLayer((int16_t *)(ptr+ n*batchPitch), padVector, bufInfo, width, height, linePitch, channelPitch, elementSize, flowCtrl,
                                    paddingType, padLayerParams, outDataPadH, outDataPadW, perChannelPadValPtr);
      }
      }
    }
    else
    {
      TIDL_DspFillPaddedCols((uint8_t*)ptr, bufInfo, width, height, linePitch, channelPitch, elementSize, flowCtrl,
                                    paddingType, padLayerParams, outDataPadH, outDataPadW, perChannelPadValPtr, numBatches, batchPitch);
    }
  }
  return IALG_EOK;
}



/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_getMemoryChunkFromSysmem
@brief      Function gives you a pointer to system scratch memory based on user given input
            parameters

@param      sysMems : sysMem Handle
@param      size    : Number of bytes to be allocated
@param      alignment  : Alignment required for the pointer
@param      space     : in which memory memory is required. Refer \ref eSysMemScratch for valid values
@param      attribute : IALG_PERSIST/IALG_SCRATCH, note that all persistent memory should be allocated
                       in the beginning
@remarks    None
@return     Pointer to the allocated memory. NULL if there is not enough memory available
----------------------------------------------------------------------------
*/
void * TIDL_getMemoryChunkFromSysmem(sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX],
  uint32_t size, uint32_t alignment, uint32_t space, uint32_t attribute)
{
  uint8_t  *mem ;
  uint8_t * ptrCurr = &((uint8_t*)sysMems[space].base)[sysMems[space].offset];
  int32_t alignmentBytes;
  int32_t offsetOrig = sysMems[space].offset;
  if(alignment > 0U)
  {
    alignmentBytes = (int32_t)(((((uintptr_t)ptrCurr) + alignment - 1U) & (~(alignment - 1U))) - ((uintptr_t)ptrCurr));
  }
  else
  {
    alignmentBytes = 0;
  }
  if( (sysMems[space].size - sysMems[space].offset) < (alignmentBytes + (int32_t)size))
  {
    /* ----------------------------------------------------*/
    /* This scenario arrives if remaining space in SL2     */
    /* is not sufficient for the requested chunk of memory */
    /* Control never hits below  instruction at run-time   */
    /* This while(1) is kept here to catch the SL2 memory  */
    /* insufficiency during development phase              */
    /* ----------------------------------------------------*/
    /* Removing while loop. If a memory is not avilable then
     * test app can take action to allocate this memory from
     * DDR instead of just getting stuck in while(1)
    */
    /*while(1){
        ;
    }*/
    mem = NULL;
  }
  else
  {
    mem                 = &ptrCurr[alignmentBytes];
    sysMems[space].offset += (alignmentBytes   + (int32_t)size);
    if ( attribute == (uint32_t)IALG_PERSIST )
    {
      sysMems[space].base = &mem[(int32_t)size];
      sysMems[space].size  = sysMems[space].size - (offsetOrig + alignmentBytes   + (int32_t)size);
      sysMems[space].offset = 0;

    }
  }
  return mem;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_resetSysmem
@brief      Function gives clears all the memories present in sysMem

@param      sysMems : sysMem Handle
@remarks    None
@return     None
----------------------------------------------------------------------------
*/
void TIDL_resetSysmem(sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX])
{
  uint32_t i;

  for ( i = 0; i < TIDL_SYSMEM_MAX; i++)
  {
    sysMems[i].offset = 0;
  }

  return;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_isOutDataFlat
@brief      Function to Check whether current out data buffer needs to
            flattened

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_isOutDataFlat(const sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId)
{
  int32_t i,j;
  int32_t status = 1;
  for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
  {
    for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
    {
      if((pTIDLNetStructure->TIDLLayers[i].layerType != TIDL_InnerProductLayer) &&
          (pTIDLNetStructure->TIDLLayers[i].inData[j] == dataId))
      {
        status = 0;
        break;
      }
    }
    if(status==0)
    {
      break;
    }
  }

  return status;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getDatElementSize
@brief      Function to gives the element size based on elementType

@param      elementType            : Current data element type
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_getDatElementSize(int32_t elementType)
{
  int32_t size = 1;
  if ((elementType == TIDL_SignedChar) || (elementType == TIDL_UnsignedChar))
  {
    size = 1;
  }
  else if ((elementType == TIDL_SignedShort) || (elementType == TIDL_UnsignedShort))
  {
    size = 2;
  }
  else if ((elementType == TIDL_SinglePrecFloat) || (elementType == TIDL_UnsignedWord) || (elementType == TIDL_SignedWord))
  {
    size = 4;
  }
  else if ((elementType == TIDL_UnsignedDoubleWord) || (elementType == TIDL_SignedDoubleWord))
  {
    size = 8;
  }
  else
  {
    size = 1;
  }
  return size;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getDatElementSign
@brief      Function to gives the element sign based on elementType

@param      elementType            : Current data element type
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_getDatElementSign(int32_t elementType)
{
  int32_t sign = 1;
  if ((elementType == TIDL_SignedChar) || (elementType == TIDL_SignedShort) || (elementType == TIDL_SignedWord) || (elementType == TIDL_SinglePrecFloat))
  {
    sign = 1;
  }
  else
  {
    sign = 0;
  }
  return sign;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_isOutDataBuff
@brief      Function to Check whether current data buffer is Output from
            current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@param      layersGroupId     : current algorithm instance Group ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_isOutDataBuff(const sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId, int32_t layersGroupId)
{
  int32_t i,j;
  int32_t status = 0;
  if(pTIDLNetStructure->numLayers >= TIDL_NUM_MAX_LAYERS)
  {
    status = -1;
  }
  else
  {
    for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
    {
      for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
      {
        if((pTIDLNetStructure->TIDLLayers[i].layersGroupId != layersGroupId) &&
            (pTIDLNetStructure->TIDLLayers[i].inData[j] == dataId))
        {
          status = 1;
          break;
        }
      }
      if(status == 1)
      {
        break;
      }
    }
  }

  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_isInDataBuff
@brief      Function to Check whether current data buffer is Input to
            current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@param      layersGroupId     : current algorithm instance Group ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_isInDataBuff(const sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId, int32_t layersGroupId)
{
  int32_t i,j;
  int32_t status = 0;
  for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
  {
    for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numOutBufs; j++)
    {
      if((pTIDLNetStructure->TIDLLayers[i].layersGroupId != layersGroupId) &&
          (pTIDLNetStructure->TIDLLayers[i].outData.dataId == dataId))
      {
        status = 1;
        break;
      }
    }
    if(status == 1)
    {
      break;
    }
  }

  return status;
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getLayerNum
@brief      Function to get the layer index of data ID

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_getLayerNum(const sTIDL_Network_t * pTIDLNetStructure, int32_t dataId)
{
  int32_t i, j;
  int32_t layerNum = -1;
  for (i = 0; i < pTIDLNetStructure->numLayers; i++)
  {
    for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numOutBufs; j++)
    {
      if (pTIDLNetStructure->TIDLLayers[i].outData.dataId == dataId)
      {
        layerNum = i;
      }
    }
  }
  return layerNum;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getDataParams
@brief      Function to Check whether current data buffer is Input to
            current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     Address of the Data Params Structure Base - If Successful
            NULL - If Faile - Requested dataID Not found
----------------------------------------------------------------------------
*/
sTIDL_DataParams_t * TIDL_getDataParams(sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId)
{
  int32_t i,j;
  sTIDL_DataParams_t *dataPtr = NULL;
  if(pTIDLNetStructure->numLayers < TIDL_NUM_MAX_LAYERS)
  {
    for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
    {
      for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numOutBufs; j++)
      {
        if(pTIDLNetStructure->TIDLLayers[i].outData.dataId == dataId)
        {
          dataPtr = &(pTIDLNetStructure->TIDLLayers[i].outData);
          break;
        }
      }
      if(dataPtr != NULL)
      {
        break;
      }
    }
  }
  return(dataPtr);
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getDataBuff
@brief      Function to get base buffer pointer from Ivision buffer

@param      bufDesc      : ivision buffer descriptor list
@param      numBufs      : Number of buffers in the list
@param      dataId       : Current data ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
void * TIDL_getDataBuff(IVISION_BufDesc *bufDesc[], uint32_t numBufs,
int32_t dataId, int32_t numBatches, int32_t pitch[], int32_t isPaded)
{
  int32_t i;
  void * ptr;
  void * retVal = NULL;
  for (i = 0 ; i < (int32_t)numBufs; i++)
  {
    if(bufDesc[i]->bufferId  == dataId)
    {
      IVISION_BufPlanes (*ivisionBufPlane)[]  = (IVISION_BufPlanes (*)[])((void*)(&bufDesc[i]->bufPlanes[0]));

      ptr = (void*)(get_uint8_t_pointer((uint8_t*)(*ivisionBufPlane)[0].buf,
      (((((int32_t)(*ivisionBufPlane)[0].frameROI.topLeft.y) * (int32_t)(*ivisionBufPlane)[0].width)) +
      ((int32_t)(*ivisionBufPlane)[0].frameROI.topLeft.x))));
      retVal =  ptr;
      if((((uint32_t)pitch[TIDL_LINE_PITCH] != (*ivisionBufPlane)[0].width) /*|| ((uint32_t)pitch[TIDL_ROI_PITCH] != ((*ivisionBufPlane)[0].width*(*ivisionBufPlane)[0].height))*/) && (isPaded == 1))
      {
        retVal = NULL;
      }
      if (isPaded == 0)
      {
        pitch[TIDL_LINE_PITCH] = (int32_t)((*ivisionBufPlane)[0].width);
        pitch[TIDL_ROI_PITCH] = (*ivisionBufPlane)[0].width*(*ivisionBufPlane)[0].height / numBatches;
      }
      break;
    }
  }

  return retVal;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getLayerTypeForOutDataID
@brief      Function to Check whether current data buffer is Input to
current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     Address of the Data Params Structure Base - If Successful
NULL - If Faile - Requested dataID Not found
----------------------------------------------------------------------------
*/
int32_t TIDL_getLayerTypeForOutDataID(const sTIDL_Network_t * pTIDLNetStructure,
  int32_t dataId)
{
  int32_t i, j;
  int32_t layerType = TIDL_UnsupportedLayer;
  if (pTIDLNetStructure->numLayers < TIDL_NUM_MAX_LAYERS)
  {
    for (i = 0; i < pTIDLNetStructure->numLayers; i++)
    {
      for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numOutBufs; j++)
      {
        if (pTIDLNetStructure->TIDLLayers[i].outData.dataId == dataId)
        {
          layerType = pTIDLNetStructure->TIDLLayers[i].layerType;
          break;
        }
      }
      if (layerType != TIDL_UnsupportedLayer)
      {
        break;
      }
    }
  }
  return(layerType);
}

/**
----------------------------------------------------------------------------
@fn         TIDL_getNumConsumersForDataId
@brief      Function to Check number of consumers for given data Id

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Indata Id of current layer
@remarks    None
@return     Number of consumers with given data Id
----------------------------------------------------------------------------
*/
int32_t TIDL_getNumConsumersForDataId(const sTIDL_Network_t * pTIDLNetStructure, int32_t dataId)
{
  int32_t numConsumers = 0;
  for(int i = 0; i < pTIDLNetStructure->numLayers; i++)
  {
    for(int j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
    {
      if(pTIDLNetStructure->TIDLLayers[i].inData[j] == dataId)
      {
        numConsumers++;
      }
    }
  }
  return numConsumers;
}


/**
 * @brief This function returns the ROI pitch in bytes
 *
 * @param dataParams : This has the parameters of data or kernel buffer
 * @return int32_t :  returns the ROI pitch in bytes
 */
int32_t TIDL_updateDataParamsPitch(const sTIDL_DataParams_t  * dataParams)
{
  int32_t dataSize;
  dataSize = dataParams->dimValues[TIDL_DIM_BATCH]*dataParams->pitch[TIDL_ROI_PITCH] * TIDL_getDatElementSize(dataParams->elementType);

  return (dataSize);
}

/**
 * @brief This function the no of Input and output tensors that requires the
 *        new generic dataflow
 *
 * @param params : Create time parameters for tidl
 * @param layerIdx : Index of the layer to be processed
 * @param numInTensors : no of input tensors that requires the generic dataflow
 * @param numOutTensors : no of output tensors that requires the generic dataflow
 * @return int32_t : returns function status
 */
int32_t TIDL_getNumInOutTensors(const TIDL_CreateParams *params,
                                int32_t layerIdx,
                                int32_t *numInTensors,
                                int32_t *numOutTensors
                                )
{
  int32_t status = IALG_EOK;
  *numInTensors = params->net->TIDLLayers[layerIdx].numInBufs;
  *numOutTensors = params->net->TIDLLayers[layerIdx].numOutBufs;
  sTIDL_Layer_t *tidlLayer = &params->net->TIDLLayers[layerIdx];
  /* For concat layer we process one tensor at a time, so set numInTensors as 1 */
  if(tidlLayer->layerType == TIDL_ConcatLayer)
  {
    *numInTensors = 1;
  }

  if(tidlLayer->layerType == TIDL_DetectionOutputLayer)
  {
    *numInTensors = 1;
  }
  if (*numInTensors > TIDL_MAX_IN_TENSORS)
  {
    tidl_printf(0, "For Eltwise layer num of Inputs are morethan TIDL_MAX_IN_TENSORS supported for New GenericFlow. \n");
    status = IALG_EFAIL; /* TODO : Replace with proper error code */
  }

  return status;
}

/**
 * @brief This function returns the output processing height for the given inHeight
 *
 * @param inHeight : input processing height
 * @param currentLayer : layer properties of the current layer
 * @return int32_t : returns the output processing height
 */
int32_t TIDL_getOutProcHeight(int32_t inHeight, sTIDL_Layer_t *currentLayer, sTIDL_DataParams_t *inDataParams)
{
  int32_t retVal;
  if ((currentLayer->layerType == TIDL_ArgMaxLayer) ||
     (currentLayer->layerType == TIDL_EltWiseLayer) ||
     (currentLayer->layerType == TIDL_BatchNormLayer) ||
     (currentLayer->layerType == TIDL_BatchReshapeLayer) ||
     (currentLayer->layerType == TIDL_ConcatLayer) ||
     (currentLayer->layerType == TIDL_DataConvertLayer) ||
     (currentLayer->layerType == TIDL_ReduceLayer) ||
     (currentLayer->layerType == TIDL_ScatterElementsLayer)
    )
  {
    retVal = inHeight;
  }
  else if(currentLayer->layerType == TIDL_PoolingLayer)
  {
    int32_t strideH    = currentLayer->layerParams.poolParams.strideH;
    /* TODO : Need to re-visit this code */
    retVal = TIDL_CEIL_DIV(inHeight, strideH);
  }
  else if(currentLayer->layerType == TIDL_ResizeLayer)
  {
    int32_t resizeFact = currentLayer->layerParams.resizeParams.resizeRatio[3];
    retVal = inHeight * resizeFact;
  }
  else if(currentLayer->layerType == TIDL_ColorConversionLayer)
  {
    retVal = inHeight * 2;
  }
  else if (currentLayer->layerType == TIDL_CustomLayer)
  {
    /* For custom layer if more than one inputs are present it is expected
    that the input to output ratio is 1. If not then it is assumed that input
    to output ratio is same for all input heights */
    float32_tidl outInHeightRatio = 1.0;
    if ( currentLayer->numInBufs == 1 )
    {
      outInHeightRatio = (float32_tidl)currentLayer->outData.dimValues[TIDL_DIM_HEIGHT] /
              (float32_tidl)inDataParams->dimValues[TIDL_DIM_HEIGHT];
    }
    retVal = inHeight * outInHeightRatio;
  }
  else
  {
    tidl_printf(0, "This layer is not currently supported for New GenericFlow. \n");
    retVal = -1;
  }
  return retVal;
}


void TIDL_poolingGetUpdatedPadValues(int32_t Fr, int32_t strideVal, int32_t padH, int32_t strideOffsetMethod, int32_t heightVal, int32_t *topPad, int32_t *bottomPad)
{
  if(strideOffsetMethod == TIDL_StrideOffsetTopLeft)
  {
    if((strideVal == 2) && ((heightVal & 1) == 0))
    {
      if(padH > 0)
      {
        *bottomPad -= 1U;
      }
    }
  }
  else
  {
    if((strideVal == 2) && ((heightVal & 1) == 0))
    {
      if(padH > 0)
      {
        *topPad -= 1U;
      }
    }
  }
}

/**
 * @brief This function returns the in and out DMA planesizes required for generic DMA dataflow
 *
 * @param params : Create time parameters for tidl
 * @param layerIdx : index of the layer to be processed
 * @param dataFlowInfo : the populated structure from NC
 * @param inDataParams : parameters of the input data buffer
 * @param inPlaneSize : input DMA planesize required for generic DMA dataflow
 * @param outDataParams : parameters of the output data buffer
 * @param outPlaneSize : output DMA planesize required for generic DMA dataflow
 * @param backupProcSize : the original planSize/ProcSize from NC
 * @param st : Index if the current superTile
 * @return int32_t : returns the status
 */
int32_t TIDL_getInOutPlaneSizes(const TIDL_CreateParams *params,
                                int32_t layerIdx,
                                sDataFlowInfo_t * dataFlowInfo,
                                sTIDL_DataParams_t *inDataParams,
                                int32_t *inPlaneSize,
                                sTIDL_DataParams_t *outDataParams,
                                int32_t *outPlaneSize,
                                int32_t *jumpReduction,
                                int32_t backupProcSize,
                                int32_t st,
                                int32_t targetDevice
                                )
{
  int32_t outHeight = 0, status = IALG_EOK;
  int32_t outLinePitch  = outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t numStHandles = TIDL_privGetNumHandles(dataFlowInfo);
  sTIDL_Layer_t *tidlLayer = &params->net->TIDLLayers[layerIdx];
  int32_t procElemSize = TIDL_getProcessingElementSizeInBytes(tidlLayer);
  int32_t outElemSize  = TIDL_getDatElementSize(outDataParams->elementType);
  int32_t extraTxSize = 0U;
  *jumpReduction = 0U;

  /* Calculate inPlaneSize and outPlaneSize incase of LargeFeatureMap */
  if((dataFlowInfo->numSplit>1))
  {
    int32_t inLinePitch   = inDataParams->pitch[TIDL_LINE_PITCH];
    int32_t inElementSize = TIDL_getDatElementSize(inDataParams->elementType);
    /* In large feature map case, calculate the num of lines from the procSize first and then
     multiply it with outPitch to get the planeSize for output */
    int32_t inHeight = TIDL_CEIL_DIV(dataFlowInfo->procSize, (inLinePitch*procElemSize));
    outHeight = TIDL_getOutProcHeight(inHeight, &params->net->TIDLLayers[layerIdx], inDataParams);
    if(TIDL_isPadOTF(params->net->deviceName))
    {
      if(TIDL_isLayerSpatialPooling(params, layerIdx))
      {
        /*Need to replace .padH with virtual pad equivalent which reflects strideOffsetMethod*/
        int32_t localTopPad = tidlLayer->layerParams.poolParams.padH;
        int32_t localBottomPad = tidlLayer->layerParams.poolParams.padH;
        TIDL_poolingGetUpdatedPadValues( tidlLayer->layerParams.poolParams.kernelH, tidlLayer->layerParams.poolParams.strideH, tidlLayer->layerParams.poolParams.padH, tidlLayer->strideOffsetMethod, inDataParams->dimValues[TIDL_DIM_HEIGHT], &localTopPad, &localBottomPad);
        sTIDL_PoolingParams_t *poolParams = &(tidlLayer->layerParams.poolParams);
        outHeight = TIDL_CEIL_DIV(outDataParams->dimValues[TIDL_DIM_HEIGHT], dataFlowInfo->numSplit);
        inHeight  =  outHeight * poolParams->strideH + (poolParams->kernelH - poolParams->strideH);
        extraTxSize = inDataParams->dimValues[TIDL_DIM_WIDTH] * (dataFlowInfo->numSplit - 1) * localTopPad * procElemSize;
        *jumpReduction = localTopPad * inDataParams->dimValues[TIDL_DIM_WIDTH] * procElemSize; 
      }
    }
  }
  else
  {
    /* Calculate inPlaneSize/procSize for each tile incase of ST sfm flow because
       perfsim gives procSize for only large tile, so calculate for other tiles here */
    if (numStHandles != 1)
    {
      int32_t imWidth, imHeight, outWidth, featurePlaneSize;
      TIDL_privGetInProcSize(dataFlowInfo, st, tidlLayer, &imWidth, &imHeight, targetDevice);
      TIDL_privGetOutProcSize(dataFlowInfo, st, tidlLayer, &outWidth, &outHeight, targetDevice);
      featurePlaneSize = TIDL_getFeaturePlaneSize(params, layerIdx, imHeight);
      dataFlowInfo->procSize = MIN(featurePlaneSize, backupProcSize);
    }
  }

  if ( tidlLayer->layerType == TIDL_DataConvertLayer)
  {
    const sTIDL_dataConvertParams_t *dataConvertParams = &tidlLayer->layerParams.dataConvertParams;
    if ( dataConvertParams->layout == TIDL_LT_NHWC )
    {
      if (dataConvertParams->type == TIDL_DC_TYPE_OUTPUT )
      {

        /* While convert NCHW to NHWC format, output pitch is not correctly calculated in TIDL
        hence recompute it */
        outLinePitch = outDataParams->dimValues[TIDL_DIM_WIDTH];
      }
      else if (dataConvertParams->type == TIDL_DC_TYPE_INPUT )
      {
        /* While coverting NHWC to NCHW format, the writes always happen in terms of all
        the output channels. Now as outProcSize is used to decide the jump between the blocks
        set outLinePitch = 1 to get the right amount of jump */
        outLinePitch  = 1;
      }
    }

  }
  *outPlaneSize = outHeight * (outLinePitch * outElemSize);
  *inPlaneSize = dataFlowInfo->procSize + extraTxSize;
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_outBuffAlloc
@brief      Function to Request Memory for layer output Memory

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
void TIDL_outBuffAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec memRec[], int32_t outDataSize)
{

  if((TIDL_isOutDataBuff(params->net,
        params->net->TIDLLayers[layerIdx].outData.dataId,
        params->currLayersGroupId) == 0)
     && (params->net->dataFlowInfo == NULL)
    )
  {
    memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].size += ((uint32_t)outDataSize + 128U);
    //tidl_printf(0," ALG_SCRATCH_DATA_BUFF_MEMREC Size for Layer , %4d,  %8d \n", layerIdx, memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].size);
  }
  return;
}
/**
 * @brief This function requests scratch memory size
 *
 * @param layerIdx : current layer index
 * @param memRec : memory table populated by the Algorithm
 * @param outDataSize : Ouptut buffer size
 */
void TIDL_scratchBufAlloc(int32_t layerIdx, IALG_MemRec memRec[], int32_t outDataSize)
{
  /* Allocate the maximum scratch buf required */
  if ( outDataSize >  (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size )
  {
     memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size = (uint32_t)outDataSize + 128U;
  }

  /*tidl_printf(0," ALG_REF_SCRATCH_BUFF_MEMREC Size for Layer , %4d,  %8d \n", layerIdx, memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size);*/
  return;
}
/**
 * @brief This function initializes scratch memory pointer
 *
 * @param layerIdx : current layer index
 * @param memRec : memory table populated by the Algorithm
 * @param outPtr : ouptut scratch pointer
 * @param outDataSize : Ouptut buffer size
 */
void TIDL_scratchBufInit(int32_t layerIdx,
  const IALG_MemRec memRec[], void ** outPtr, int32_t outDataSize)
{
  *outPtr = memRec[ALG_REF_SCRATCH_BUFF_MEMREC].base;

  return;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_findFreeOutBuff
@brief      Function to find the free output buffer used for tjis layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      outDataSize  : outDataSize required for this layer
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     outDataSize  : outDataSize required for this layer
----------------------------------------------------------------------------
*/
int32_t TIDL_findFreeOutBuff(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t outDataSize, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_findFreeOutBuff(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t outDataSize, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataId = params->net->TIDLLayers[layerIdx].outData.dataId;
  int32_t ii, jj, kk, skipLoop, curOutDataId = outDataId;
  const sTIDL_Layer_t *TIDLLayer = &params->net->TIDLLayers[layerIdx];
  int32_t currDataSize = outDataSize;
  if((TIDL_isOutDataBuff(params->net,
        outDataId,
        params->currLayersGroupId) == 0))
  {
    if(params->optimiseExtMem == TIDL_OptimiseExtMemL2)
    {
      /* For loop to find an output buffer of same size in previous layers */
      for(ii = (layerIdx - 2); ii > 0; ii--)
      {
        /* To check whether output memory is allocated to this layer */
        if(TIDLLayersBufPtr->outDataSize[ii] != 0)
        {
          /* Compare current layer outDataSize with previous layers */
          if(currDataSize <= TIDLLayersBufPtr->outDataSize[ii])
          {
            /* Found an output buffer of required size in previous layers */
            curOutDataId = params->net->TIDLLayers[ii].outData.dataId;

            skipLoop = 0;
            /* Check whether that layer is used as input to any future layers */
            for(kk = layerIdx; kk < params->net->numLayers; kk++)
            {
              const sTIDL_Layer_t *TIDLLayerCur = &params->net->TIDLLayers[kk];
              for(jj = 0; jj < TIDLLayerCur->numInBufs; jj++)
              {
                int32_t inDataId  =  (int32_t)TIDLLayersBufPtr->newInDataId[kk][jj];
                if((inDataId == curOutDataId) && (skipLoop == 0))
                {
                  /* The output buffer found is still in use for future layers,
                     So, break this loop and continue to find
                     next free output buffer */
                  curOutDataId = outDataId;
                  /* kk = params->net->numLayers; */
                  /* break; */
                  skipLoop = 1;
                }
              }
            }
            /* Free output buffer found, so break from for loop */
            if(curOutDataId != outDataId)
            {
              /* ii = 0; */
              break;
            }
          }
        }
      }
    }
    else /* if(params->optimiseExtMem == TIDL_OptimiseExtMemL1) */
    {
      int32_t outWidth       = TIDLLayer->outData.dimValues[TIDL_DIM_WIDTH];
      int32_t outHeight      = TIDLLayer->outData.dimValues[TIDL_DIM_HEIGHT];
      int32_t numChannels    = TIDLLayer->outData.dimValues[TIDL_DIM_NUMCH];
      int32_t layerType      = TIDLLayer->layerType;
      int32_t padW = TIDLLayer->outData.padW;
      int32_t padH = TIDLLayer->outData.padH;
      const sTIDL_Layer_t   *TIDLLayerCur;

      /* For loop to find an output buffer of same size in previous layers */
      for(ii = (layerIdx - 2); ii > 0; ii--)
      {
        /* To check whether output memory is allocated to this layer */
        if(TIDLLayersBufPtr->outDataSize[ii] != 0)
        {
          TIDLLayerCur = &params->net->TIDLLayers[ii];
          /* Compare the output elementsize with previous layer */
          if ( TIDL_getDatElementSize(TIDLLayerCur->outData.elementType) == TIDL_getDatElementSize(TIDLLayer->outData.elementType))
          {
            /* Compare width and height with previous layers */
            if((outWidth == TIDLLayerCur->outData.dimValues[TIDL_DIM_WIDTH]) &&
                (outHeight == TIDLLayerCur->outData.dimValues[TIDL_DIM_HEIGHT]))
            {
              /* Compare numChannels with previous layers */
              if(numChannels <= TIDLLayerCur->outData.dimValues[TIDL_DIM_NUMCH])
              {
                /* Compare layerType with previous layers, re-use output from
                   same layerType, otherwise padding may be differnt. This is
                   because different layers will be processed with different
                   blockwidth and heights, so padding will change.
                */
                if((layerType == TIDLLayerCur->layerType) && (padW == TIDLLayerCur->outData.padW) && (padH == TIDLLayerCur->outData.padH))
                {
                  /* Found an output buffer of required size in previous layers */
                  curOutDataId = params->net->TIDLLayers[ii].outData.dataId;

                  skipLoop = 0;
                  /* Check whether that layer is used as input to any future layers */
                  for(kk = layerIdx; kk < params->net->numLayers; kk++)
                  {
                    const sTIDL_Layer_t *TIDLLayerCurkk = &params->net->TIDLLayers[kk];
                    for(jj = 0; jj < TIDLLayerCurkk->numInBufs; jj++)
                    {
                      int32_t inDataId  =  (int32_t)TIDLLayersBufPtr->newInDataId[kk][jj];
                      if((inDataId == curOutDataId) && (skipLoop == 0))
                      {
                        /* The output buffer found is still in use for future layers,
                           So, break this loop and continue to find
                           next free output buffer */
                        curOutDataId = outDataId;
                        /* kk = params->net->numLayers; */
                        /* break; */
                        skipLoop = 1;
                      }
                    }
                  }
                  /* Free output buffer found, so break from for loop */
                  if(curOutDataId != outDataId)
                  {
                    /* ii = 0; */
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }

    /* Check the curOutDataId is used as input to SliceLayer */
    skipLoop = 0;
    if(curOutDataId != outDataId)
    {
      for(kk = 0; kk < layerIdx; kk++)
      {
        const sTIDL_Layer_t *TIDLLayerCur = &params->net->TIDLLayers[kk];
        for(jj = 0; jj < TIDLLayerCur->numInBufs; jj++)
        {
          int32_t inDataId  =  (int32_t)TIDLLayersBufPtr->newInDataId[kk][jj];
          if((inDataId == curOutDataId) && (skipLoop == 0))
          {
            if(TIDLLayerCur->layerType == TIDL_SliceLayer)
            {
                /* The output buffer found is used for Slice layers,
                    So can not be re-used */
                curOutDataId = outDataId;
                skipLoop = 1;
            }
          }
        }
      }
    }

    /*
       As the free output buffer found, update the input dataID to point to
       the new output buffer, Also make outDataSize = 0, to not allocate the
       new memory for output(as it can re-use the memory from previous layers)
   */
    if(curOutDataId != outDataId)
    {
      for(kk = layerIdx; kk < params->net->numLayers; kk++)
      {
        const sTIDL_Layer_t *TIDLLayerCur = &params->net->TIDLLayers[kk];
        for(jj = 0; jj < TIDLLayerCur->numInBufs; jj++)
        {
          int32_t inDataId  =  (int32_t)TIDLLayersBufPtr->newInDataId[kk][jj];
          if(inDataId == outDataId)
          {
            TIDLLayersBufPtr->newInDataId[kk][jj] = curOutDataId;
          }
        }
      }
      TIDLLayersBufPtr->newOutDataId[layerIdx][0] = curOutDataId;
      currDataSize = 0;
    }
  }
  else
  {
    currDataSize = 0;
  }
  return currDataSize;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_outBuffInit
@brief      Function to Initialize the Layer output Memory

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      outDataSize  : Size of the ouput buffer to be allocated
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
void TIDL_outBuffInit(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t *dataMemTabOffset,
const IALG_MemRec memRec[], void ** outPtr, int32_t outDataSize)
{

  if((TIDL_isOutDataBuff(params->net,
        params->net->TIDLLayers[layerIdx].outData.dataId,
        params->currLayersGroupId) == 1) || (params->net->dataFlowInfo != NULL) )
  {
    *outPtr = NULL;
  }
  else
  {
    /* outDataSize is 0 means, not allocate the new memory for output buffer */
    if(outDataSize == 0)
    {
      *outPtr = NULL;
    }
    else
    {
      *outPtr  =  (void*)(get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].base, \
      *dataMemTabOffset));
      *dataMemTabOffset += ALIGN_SIZE((int32_t)outDataSize, 128);
    }
    //tidl_printf(0," ALG_SCRATCH_DATA_BUFF_MEMREC Offset for Layer, %4d, %8d \n", layerIdx, *dataMemTabOffset);
  }
  return;
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2DAlloc
@brief      Function to Request Memory required by the Convolution layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      dataFlowInfo : The dataFlowInfo structure from NC
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2DAlloc(const TIDL_CreateParams *params,
                                int32_t layerIdx, IALG_MemRec *memRec,
                                const  sDataFlowInfo_t * dataFlowInfo,
                                sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  const sTIDL_ConvParams_t *conv2dparams = &params->net->TIDLLayers[layerIdx].layerParams.convParams;
  int32_t quantizationStyle = params->net->quantizationStyle;
  int32_t biasParamSize;
  int32_t coeffBufferSize = 0;
  int32_t outRoundBitsSize = 0;
  int32_t mmaScaleBufferSize = 0;
  int32_t mmaShiftBufferSize = 0;
  int32_t biasBSize = 0;
  int32_t mmaHandleSize = 4;
  int32_t targetDevice = params->net->deviceName;
  TIDL_forceTargetDeviceNonOTF(&targetDevice, params->net->TIDLLayers[layerIdx].layerType, -1);

  sTIDL_DataParams_t *dataParams = TIDL_getDataParams(params->net,
                                                      params->net->TIDLLayers[layerIdx].inData[0]);
  int32_t scratchDataSize, outBatchPitch;
  int32_t outDataSize;

  if(dataFlowInfo != NULL)
  {
    coeffBufferSize = dataFlowInfo->bufInfo[WT_MAP][READ].bufSize;      
    if((TIDL_isOneShotWeightTx(dataFlowInfo) == TRUE) && (TIDL_isWeightCompEnabled(targetDevice) == TRUE))
    {
      //Allocating 2.5x to acommodate compressed buffer and potential expansion
      coeffBufferSize = (coeffBufferSize * 5)/2;
      coeffBufferSize += 4096U; /*Secondary TR space*/
    }
  }

  if (TIDL_isOutDataFlat(params->net,
        params->net->TIDLLayers[layerIdx].outData.dataId) == 1)
  {
    params->net->TIDLLayers[layerIdx].outData.padW = 0;
    params->net->TIDLLayers[layerIdx].outData.padH = 0;
  }

  outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  /* The output buffer size will actually depend on the actual block size used for DMA/Compute
   * as this information is not available at alloc time let's assume worst case last block size
   * is of TIDL_CONV2D_EXTRA_L2MEM_FOR_FEAT_REQ bytes so that we don't go and overwrite the other buffers */
  outDataSize += (int32_t)TIDL_CONV2D_EXTRA_L2MEM_FOR_FEAT_REQ;

  biasParamSize = TIDL_getBiasParamSize(targetDevice, conv2dparams->numOutChannels);
  
  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    biasParamSize = (4 *conv2dparams->numOutChannels);
  }

  mmaHandleSize = 0;
  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_conv2dDspAlloc(params, dataFlowInfo, TIDLCONV_TYPE_CONV, layerIdx, &mmaHandleSize, &coeffBufferSize);
  }

  if (isPerChannelQuantizationEnabled(conv2dparams, params->net->calibrationOption) == 1) //Break this to enable on  a better flag..
  {
    outRoundBitsSize = conv2dparams->numOutChannels * sizeof(uint8_t);
    biasBSize        = conv2dparams->numOutChannels * sizeof(int32_t);
  }


  if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
  {
    mmaScaleBufferSize = conv2dparams->numOutChannels * 1; //In bytes
    mmaShiftBufferSize = conv2dparams->numOutChannels * 1; //In bytes
  }


  if(status != IALG_EFAIL)
  {
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += 128U;/* To handle the alignment if user gives unaligned pointer */
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)coeffBufferSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)biasParamSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)mmaHandleSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)outRoundBitsSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)biasBSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)mmaScaleBufferSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)mmaShiftBufferSize + 128U);

    if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                        outDataSize, TIDLLayersBufPtr);
      TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
    }
    TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

    outBatchPitch = params->net->TIDLLayers[layerIdx].outData.pitch[TIDL_ROI_PITCH];
    scratchDataSize  = dataParams->dimValues[TIDL_DIM_BATCH] * outBatchPitch *
      TIDL_getDatElementSize(dataParams->elementType);

    scratchDataSize = (int32_t)((float32_tidl)scratchDataSize * 1.5f); //:TODO: This will not be needed if we use perfsim output during alloc also
    if (TIDL_getDatElementSize(params->net->TIDLLayers[layerIdx].outData.elementType) <= 2)
    {
      scratchDataSize *= ((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8) *  ((int32_t)(sizeof(int32_t)));
    }
    TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);
  }

  return status;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2DInit
@brief      Function to Initialize the Convolution layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2DInit(TIDL_Handle tidlHandle,
                               const TIDL_CreateParams *params,
                               int32_t layerIdx,
                               sTIDL_AlgLayer_t *algLayer,
                               int32_t *paramMemTabOffset,
                               int32_t *dataMemTabOffset,
                               const IALG_MemRec memRec[],
                               void **outPtr,
                               int32_t quantizationStyle,
                               sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK, i;
  sTIDL_ConvParams_t * conv2dparams =
  &params->net->TIDLLayers[layerIdx].layerParams.convParams;
  int32_t coeffBufferSize = 0;
  int32_t mmaHandleSize = 4;
  int32_t dataFlowType = 0;
  sTIDL_DataParams_t * dataParams = TIDL_getDataParams(params->net,
                                                       params->net->TIDLLayers[layerIdx].inData[0]);
  const  sDataFlowInfo_t * dataFlowInfo = algLayer->layerParams.convParams.dataFlowInfo;
  int32_t numHandles = TIDL_privGetNumHandles(dataFlowInfo);

  int32_t targetDevice = params->net->deviceName;
  TIDL_forceTargetDeviceNonOTF(&targetDevice, params->net->TIDLLayers[layerIdx].layerType, -1);

  int32_t scratchDataSize, outChPitch, inChPitch;
  int32_t outRoundBitsSize = 0;
  int32_t biasBSize = 0;
  int32_t outDataSize;
  int32_t isChannelwiseQuantEnable = 0;

  algLayer->layerParams.convParams.procElemSize = 1;

  /* processing size is based on the weights size */
  algLayer->layerParams.convParams.procElemSize = TIDL_getProcessingElementSizeInBytes(&params->net->TIDLLayers[layerIdx]);
  algLayer->layerParams.convParams.startRowNumberInTensor = 0;
  if(dataFlowInfo != NULL)
  {
    dataFlowType = (int32_t)GETDATAFLOW_BUFTYPE(dataFlowInfo->dataFlowType);
    coeffBufferSize = dataFlowInfo->bufInfo[WT_MAP][READ].bufSize;
    if((TIDL_isOneShotWeightTx(dataFlowInfo) == TRUE) && (TIDL_isWeightCompEnabled(targetDevice) == TRUE))
    {
      //Allocating 2.5x to acommodate compressed buffer and potential expansion
      coeffBufferSize = (coeffBufferSize * 5)/2;
      coeffBufferSize += 4096U; /*Secondary TR space*/
    }
  }

  mmaHandleSize = 0;
  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_conv2dDspInit(params, layerIdx, algLayer, paramMemTabOffset, memRec, TIDLCONV_TYPE_CONV, &mmaHandleSize, &coeffBufferSize);
  }
  if(status == IALG_EOK)
  {
    algLayer->layerParams.convParams.biasParamSize = TIDL_getBiasParamSize(targetDevice, conv2dparams->numOutChannels);
  
    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      algLayer->layerParams.convParams.biasParamSize = 4 * conv2dparams->numOutChannels; //32 bits (TFL Specific)
    } 

    /* Align the user given pointer to 128 byte alignment as this is required for some of the memories */
    {
      uintptr_t basePtr = (uintptr_t)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
      uintptr_t basePtrAlign =(uintptr_t)TIDL_ALIGN_CEIL((uint64_t)basePtr, (uint64_t)128U);
      *paramMemTabOffset = (int32_t)((uint64_t)(*paramMemTabOffset) + ((uint64_t)basePtrAlign - (uint64_t)basePtr));
    }

    algLayer->layerParams.convParams.biasParamMem =
    get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)algLayer->layerParams.convParams.biasParamSize, 128);

    algLayer->layerParams.convParams.outRoundBitsPtr = NULL;
    algLayer->layerParams.convParams.biasBPtr = NULL;

    if (isPerChannelQuantizationEnabled(conv2dparams,params->net->calibrationOption) == 1 )
    {
      outRoundBitsSize = conv2dparams->numOutChannels * sizeof(uint8_t);
      biasBSize        = conv2dparams->numOutChannels * sizeof(int32_t);

      algLayer->layerParams.convParams.outRoundBitsPtr =
        get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
        *paramMemTabOffset += ALIGN_SIZE((int32_t)outRoundBitsSize, 128);

      algLayer->layerParams.convParams.biasBPtr =
        get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
        *paramMemTabOffset += ALIGN_SIZE((int32_t)biasBSize, 128);

    }


    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      int32_t mmaScaleShiftBufSize = conv2dparams->numOutChannels * sizeof(uint8_t);
      algLayer->layerParams.convParams.mmaShiftsPtr =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
      *paramMemTabOffset += ALIGN_SIZE((int32_t)mmaScaleShiftBufSize, 128);

      algLayer->layerParams.convParams.mmaScalesPtr =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
      *paramMemTabOffset += ALIGN_SIZE((int32_t)mmaScaleShiftBufSize, 128);
    }

    if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      for(i=0; i<numHandles; i++)
      {
        algLayer->layerParams.convParams.mmaHandleArgsMem[i] =
        get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
        *paramMemTabOffset += ALIGN_SIZE((int32_t)algLayer->layerParams.convParams.mmaHandleArgsSize[i], 128);
      }
    }

    /* Set the weight staging pointer to be NULL, the actual value will be set later */
    algLayer->layerParams.convParams.pCoeffStagePtr = NULL;

    if (TIDL_isOutDataFlat(params->net, params->net->TIDLLayers[layerIdx].outData.dataId) == 1)
    {
      params->net->TIDLLayers[layerIdx].outData.padW = 0;
      params->net->TIDLLayers[layerIdx].outData.padH = 0;
    }

    if(dataFlowInfo != NULL)
    {
      outDataSize = dataFlowInfo->bufInfo[OUT_FEAT_MAP][WRITE].bufSize;
    }
    else
    {
      outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
    }

    if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                         outDataSize, TIDLLayersBufPtr);
      TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
    }
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);

    outChPitch = params->net->TIDLLayers[layerIdx].outData.pitch[TIDL_CHANNEL_PITCH];
    inChPitch = dataParams->pitch[TIDL_CHANNEL_PITCH];
    outChPitch = (inChPitch > outChPitch) ? inChPitch : outChPitch;

    scratchDataSize = dataParams->dimValues[TIDL_DIM_BATCH] *
      params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
      outChPitch *
      TIDL_getDatElementSize(dataParams->elementType);

    scratchDataSize = (int32_t)((float32_tidl)scratchDataSize * 1.5f); //:TODO: This will not be needed if we use perfsim output during alloc also

    scratchDataSize *= ((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8) *  ((int32_t)(sizeof(int32_t)));
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;


    if(params->net->TIDLLayers[layerIdx].layerType == TIDL_ConvolutionLayer)
    {
      algLayer->metaData.totalOps  = ((conv2dparams->numOutChannels *
      conv2dparams->numInChannels  *
      conv2dparams->kernelW * conv2dparams->kernelH)/
      conv2dparams->numGroups);
      algLayer->metaData.actualOps =(int32_t)
      algLayer->layerParams.convParams.totalNumCoeffs[conv2dparams->numGroups-1];
    }
    else
    {
      algLayer->metaData.totalOps  = ((conv2dparams->numOutChannels *
      conv2dparams->numInChannels  *
      conv2dparams->kernelW * conv2dparams->kernelH)/
      (conv2dparams->numGroups*conv2dparams->strideW*conv2dparams->strideH));
      algLayer->metaData.actualOps = algLayer->metaData.totalOps;
    }

    if((params->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == 0)
    {
      /* REF for stats flow this will be happening with the convlution later ref process call */
      if (isPerChannelQuantizationEnabled(conv2dparams, params->net->calibrationOption) == 1 )
      {
        int32_t chIdx;
        float32_tidl perChannelAccScale;
        float32_tidl * perChannelWeightScalePtr =
                (float32_tidl *)get_int8_t_pointer((int8_t *)(params->net), conv2dparams->perChannelWeightScaleOffset);
        uint8_t * roundBitsPtr = (uint8_t *)(algLayer->layerParams.convParams.outRoundBitsPtr);
        isChannelwiseQuantEnable= 1;
        if ( dataParams->tensorScale != 0 )
        {
          for(chIdx = 0; chIdx < conv2dparams->numInChannels; chIdx++)
          {
            perChannelAccScale = perChannelWeightScalePtr[chIdx] * dataParams->tensorScale;
            roundBitsPtr[chIdx] = (uint8_t)(log((float32_tidl)perChannelAccScale /
              params->net->TIDLLayers[layerIdx].outData.tensorScale)/log(2.0));
            //printf("Layer Idx %d, roundBitsPtr %d \n", layerIdx, chIdx);
          }
        }
      }
    }

    sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].inData[0]);
    sTIDL_DataParams_t * outDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].outData.dataId);

    //TODO: Break this if/else into smaller functions
    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      //Populate scale and shift for MMA for convolution:
      //Scale ratio
      float32_tidl scaleRatio = 1;
      float32_tidl* weightScalePtr = (float32_tidl *)get_int8_t_pointer((int8_t *)(params->net), conv2dparams->weightScales);
      float32_tidl scale_x = inDataParams->tensorScale;
      float32_tidl scale_y = params->net->TIDLLayers[layerIdx].outData.tensorScale;
      int32_t axisCtr;
      uint8_t* scaleBuffer = (uint8_t*)algLayer->layerParams.convParams.mmaScalesPtr;
      uint8_t* shiftBuffer = (uint8_t*)algLayer->layerParams.convParams.mmaShiftsPtr; 
      //Assuming per axis: (should be single iteration for non per ch) !Replace with axis length
      //Temp logic:
      for(axisCtr = 0; axisCtr < conv2dparams->numOutChannels; axisCtr++)
      {
        scaleRatio = (scale_x * weightScalePtr[axisCtr])/scale_y;
        TIDL_getMMAv2_ScaleAndShift(scaleRatio, &scaleBuffer[axisCtr],&shiftBuffer[axisCtr]); 
      }
      int32_t * orgbiasptr = (int32_t *)get_int8_t_pointer((int8_t *)(params->net), conv2dparams->bias);
      int32_t * biasPtr  = (int32_t *)algLayer->layerParams.convParams.biasParamMem;
      //Simple copy over of bias from model to local memory.
      for(axisCtr = 0; axisCtr < conv2dparams->numOutChannels; axisCtr++)
      {
        biasPtr[axisCtr] = orgbiasptr[axisCtr];
      }
    }
    else
    {
      int16_t * orgbiasptr = (int16_t *)get_int8_t_pointer((int8_t *)(params->net), conv2dparams->bias);
      int8_t * biasPtr  = (int8_t *)algLayer->layerParams.convParams.biasParamMem;
      float32_tidl inScaleFactor;

      if(conv2dparams->enableBias == 1)
      {
        inScaleFactor = (conv2dparams->weightScale * inDataParams->tensorScale) / conv2dparams->biasScale;
      }
      else
      {
        inScaleFactor = 0.0f;
      }
  #if USE_16BIT_BIAS_FOR_8BIT_MODE
      if(params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8)
      {
        if (isPerChannelQuantizationEnabled(conv2dparams, params->net->calibrationOption) == 1 )
        {
          int chIdx;
          float32_tidl inScaleFactor;
          float32_tidl * perChannelWeightScalePtr =(float32_tidl *) ((int8_t *)(params->net) + conv2dparams->perChannelWeightScaleOffset);
          sTIDL_DataParams_t * inDataParams  =
            &params->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
          int32_t * biasBPtr = (int32_t *)(algLayer->layerParams.convParams.biasBPtr);

          int32_t biasB;
          for ( chIdx = 0; chIdx < conv2dparams->numOutChannels; chIdx++ )
          {
            inScaleFactor = (perChannelWeightScalePtr[chIdx] * inDataParams->tensorScale) / conv2dparams->biasScale;
            TIDL_conv2dBiasSplit(targetDevice,
                                dataFlowType,
                                algLayer->layerParams.convParams.procElemSize,
                                orgbiasptr + chIdx,
                                (int8_t*)biasPtr + chIdx,
                                &biasB,
                                1,
                                inScaleFactor,
                                TIDL_SAT_LO_INT16,
                                TIDL_SAT_HI_INT16,
                                0xFF,
                                TIDL_getDatElementSign(inDataParams->elementType));
            biasBPtr[chIdx] = biasB;

          }
        }
        else
        {
          //Wrapper function for the basic split logic (This is an overloaded function, deviceName is the point of overload)
          TIDL_conv2dBiasSplit(targetDevice,
                              dataFlowType,
                              algLayer->layerParams.convParams.procElemSize,
                              orgbiasptr,
                              (int8_t *)biasPtr,
                              &conv2dparams->biasB,
                              conv2dparams->numOutChannels,
                              inScaleFactor,
                              TIDL_SAT_LO_INT16,
                              TIDL_SAT_HI_INT16,
                              0xFF,
                              TIDL_getDatElementSign(dataParams->elementType));
        }
      }
      else
  #endif
      {
      /* 16 bit weights*/
        if (isPerChannelQuantizationEnabled(conv2dparams, params->net->calibrationOption) == 1 )
        {
          int chIdx;
          float32_tidl inScaleFactor;
          float32_tidl * perChannelWeightScalePtr =(float32_tidl *) ((int8_t *)(params->net) + conv2dparams->perChannelWeightScaleOffset);
          sTIDL_DataParams_t * inDataParams  =
            &params->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
          int32_t * biasBPtr = (int32_t *)(algLayer->layerParams.convParams.biasBPtr);

          int32_t biasB;
          for ( chIdx = 0; chIdx < conv2dparams->numOutChannels; chIdx++ )
          {
            inScaleFactor = (perChannelWeightScalePtr[chIdx] * inDataParams->tensorScale) / conv2dparams->biasScale;
            TIDL_conv2dBiasSplit(targetDevice,
                                dataFlowType,
                                algLayer->layerParams.convParams.procElemSize,
                                orgbiasptr + chIdx,
                                (int16_t*)biasPtr + chIdx,
                                &biasB,
                                1,
                                inScaleFactor,
                                TIDL_SAT_LO_INT32,
                                TIDL_SAT_HI_INT32,
                                0xFFFF,
                                TIDL_getDatElementSign(dataParams->elementType));
            biasBPtr[chIdx] = biasB;
          }
        }
        else
        {
          int32_t maxBiasB = 0xFFFF;
          /* This condition indicates mixed precision where processing is in 16 bit but input is signed input.
          Here as target implementation scales the input with 256, we need to limit the biasB so that it doesn't
          go beyond 8 bits as the same is later multiplied by 256 to match the scale of accumulator*/
          if ( dataParams->elementType == TIDL_SignedChar )
          {
            maxBiasB = 0xFF;
          }
          TIDL_conv2dBiasSplit(targetDevice, dataFlowType, algLayer->layerParams.convParams.procElemSize, orgbiasptr, (int16_t*)biasPtr, &conv2dparams->biasB, conv2dparams->numOutChannels, inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32,maxBiasB, TIDL_getDatElementSign(dataParams->elementType));
        }
      }
    }

    if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      status = TIDL_conv2dSetupMmaHandle(tidlHandle, params, layerIdx, algLayer, TIDLCONV_TYPE_CONV, isChannelwiseQuantEnable);
    }
  }

  return status;
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_deconv2DAlloc
@brief      Function to Request Memory required by the Convolution layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      dataFlowInfo : The dataFlowInfo structure from NC
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_deconv2DAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec,
  const  sDataFlowInfo_t * dataFlowInfo,
  sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  const sTIDL_ConvParams_t * conv2dparams =
    &params->net->TIDLLayers[layerIdx].layerParams.convParams;
  int32_t dataFlowType = 0;

  int32_t outDataSize;
  int32_t scratchDataSize;
  int32_t biasParamSize;
  int32_t coeffBufferSize= 0;
  uint32_t coeffBufferPitch;
  int32_t mmaHandleSize = 4;

  if(dataFlowInfo != NULL)
  {
    dataFlowType = (int32_t)GETDATAFLOW_BUFTYPE(dataFlowInfo->dataFlowType);
    coeffBufferSize = TIDL_deconv2DCoeffMemRequired(conv2dparams,  (uint32_t)params->net->TIDLLayers[layerIdx].weightsElementSizeInBits, (uint32_t)dataFlowType, &coeffBufferPitch);
  }

  outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  /* The output buffer size will actually depend on the actual block size used for DMA/Compute
     as this information is not available at alloc time let's assume worst case last block size
     is of TIDL_CONV2D_EXTRA_L2MEM_FOR_FEAT_REQ bytes so that we don't go and overwrite the other buffers */
  outDataSize += (int32_t)TIDL_CONV2D_EXTRA_L2MEM_FOR_FEAT_REQ;

  biasParamSize = conv2dparams->numOutChannels* ((int32_t )sizeof(int32_t));

  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_conv2dDspAlloc(params, dataFlowInfo, TIDLCONV_TYPE_DECONV, layerIdx, &mmaHandleSize, &coeffBufferSize);
  }
  if(status != IALG_EFAIL)
  {
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += 128U;/* To handle the alignment if user gives unaligned pointer */
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)coeffBufferSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)biasParamSize + 128U);
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)mmaHandleSize + 128U);

    if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
        outDataSize, TIDLLayersBufPtr);
      TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
    }
    TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

    scratchDataSize = TIDL_deconv2DGetScratchDataSize(params, layerIdx);
    TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);
  }

  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_deconv2DInit
@brief      Function to Initialize the Convolution layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_deconv2DInit(TIDL_Handle tidlHandle,
                                const TIDL_CreateParams *params,
                                 int32_t layerIdx,
                                 sTIDL_AlgLayer_t *algLayer,
                                 const  sDataFlowInfo_t *dataFlowInfo,
                                 int32_t *paramMemTabOffset,
                                 int32_t *dataMemTabOffset,
                                 const IALG_MemRec memRec[],
                                 void **outPtr,
                                 int32_t quantizationStyle,
                                 sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK, i;
  sTIDL_ConvParams_t * conv2dparams =
          &params->net->TIDLLayers[layerIdx].layerParams.convParams;
  int32_t coeffBufferSize = 0;
  uint32_t coeffBufferPitch;
  int32_t mmaHandleSize = 4;
  int32_t dataFlowType = 0;
  sTIDL_DataParams_t * dataParams = TIDL_getDataParams(params->net,
          params->net->TIDLLayers[layerIdx].inData[0]);

  int32_t scratchDataSize;
  int32_t outDataSize;
  int32_t numHandles = TIDL_privGetNumHandles(dataFlowInfo);

  algLayer->layerParams.convParams.procElemSize = 1;

  /* processing size is based on the weights size */
  if ( params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8 )
  {
    algLayer->layerParams.convParams.procElemSize = 1;
  }
  else if ( params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 16 )
  {
    algLayer->layerParams.convParams.procElemSize = 2;
  }
  else
  {
    algLayer->layerParams.convParams.procElemSize = 4;
  }

  if(dataFlowInfo != NULL)
  {
    dataFlowType = (int32_t)GETDATAFLOW_BUFTYPE(dataFlowInfo->dataFlowType);
    coeffBufferSize = TIDL_deconv2DCoeffMemRequired(conv2dparams,  (uint32_t)params->net->TIDLLayers[layerIdx].weightsElementSizeInBits,  (uint32_t)dataFlowType, &coeffBufferPitch);
  }

  mmaHandleSize = 0;
  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_conv2dDspInit(params, layerIdx, algLayer, paramMemTabOffset, memRec, TIDLCONV_TYPE_DECONV, &mmaHandleSize, &coeffBufferSize);
  }

  if(status == IALG_EOK)
  {
    algLayer->layerParams.convParams.biasParamSize = conv2dparams->numOutChannels*  ((int32_t)(sizeof(int32_t)));
    /* Align the user given pointer to 128 byte alignment as this is required for some of the memories */
    {
      uintptr_t basePtr = (uintptr_t)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
      uintptr_t basePtrAlign = TIDL_ALIGN_CEIL((uintptr_t)basePtr, (uintptr_t)128);
      *paramMemTabOffset = (int32_t)((uintptr_t)*paramMemTabOffset+ (basePtrAlign - basePtr));
    }

    algLayer->layerParams.convParams.biasParamMem =
            get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)algLayer->layerParams.convParams.biasParamSize, 128);

    if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
   {
      for(i=0; i<numHandles; i++)
      {
        algLayer->layerParams.convParams.mmaHandleArgsMem[i] =
                get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
        *paramMemTabOffset += ALIGN_SIZE((int32_t)algLayer->layerParams.convParams.mmaHandleArgsSize[i], 128);

      }
    }

    /* Set the weight staging pointer to be NULL, the actual value will be set later */
    algLayer->layerParams.convParams.pCoeffStagePtr = NULL;

    if(dataFlowInfo != NULL)
    {
      outDataSize = dataFlowInfo->bufInfo[OUT_FEAT_MAP][WRITE].bufSize;
    }
    else
    {
      outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
    }
    if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
              outDataSize, TIDLLayersBufPtr);
      TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
    }
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);

    scratchDataSize = TIDL_deconv2DGetScratchDataSize(params, layerIdx);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

    algLayer->metaData.totalOps = ((conv2dparams->numOutChannels *
            conv2dparams->numInChannels  *
            conv2dparams->kernelW * conv2dparams->kernelH) /
            conv2dparams->numGroups);

    int16_t * orgbiasptr = (int16_t *)get_int8_t_pointer((int8_t *)(params->net), conv2dparams->bias);
    int8_t * biasPtr  = (int8_t *)algLayer->layerParams.convParams.biasParamMem;
    float32_tidl inScaleFactor;
    sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
            params->net->TIDLLayers[layerIdx].inData[0]);
    sTIDL_DataParams_t * outDataParams = TIDL_getDataParams(params->net,
            params->net->TIDLLayers[layerIdx].outData.dataId);

    if(conv2dparams->enableBias == 1)
    {
      inScaleFactor = (conv2dparams->weightScale * inDataParams->tensorScale) / conv2dparams->biasScale;
    }
    else
    {
      inScaleFactor = 1.0f;
    }

#if USE_16BIT_BIAS_FOR_8BIT_MODE
    if(params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8)
    {
       TIDL_conv2dBiasSplit(orgbiasptr, biasPtr, &conv2dparams->biasB, conv2dparams->numOutChannels, inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF, TIDL_getDatElementSign(dataParams->elementType));
    }
    else
#endif
    {
      TIDL_conv2dBiasSplit(orgbiasptr, (int16_t*)biasPtr, &conv2dparams->biasB, conv2dparams->numOutChannels, inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32,0xFFFF, TIDL_getDatElementSign(dataParams->elementType));
    }

    if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      status = TIDL_conv2dSetupMmaHandle(tidlHandle, params, layerIdx, algLayer, TIDLCONV_TYPE_DECONV, 0);
    }
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_innerProductAlloc
@brief      Function to Request Memory required by the Innerproduct layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/

int32_t TIDL_innerProductAlloc(const TIDL_CreateParams *params,
                                     int32_t layerIdx, IALG_MemRec *memRec,
                                     sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = (int32_t)(outDataSize * ((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8) *  ((int32_t)(sizeof(int32_t))));
  int32_t biasParamSize = params->net->TIDLLayers[layerIdx].layerParams.innerProductParams.numOutNodes * (((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8)) *  ((int32_t)(sizeof(int32_t))); 

  int32_t tranformSize  = TIDL_getDatElementSize(params->net->TIDLLayers[layerIdx].outData.elementType) *
      TIDL_innerProductCoeffMemRequired(&params->net->TIDLLayers[layerIdx].layerParams.innerProductParams);
  //Have addtional space for bias during forced reference for inner product
  if(TIDL_forceInnerProductRef(params, &params->net->TIDLLayers[layerIdx]))
    tranformSize += biasParamSize;

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)biasParamSize + 128U);

  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)scratchDataSize + 128U);

  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)tranformSize + 128U);
  }
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);
  
  /* Allocating DDR SCRATCH */
  sTIDL_InnerProductParams_t * innerProductParams =
  &params->net->TIDLLayers[layerIdx].layerParams.innerProductParams;
  
  int32_t numInputs, roisPerCall, outNodesPerCall, kernel_int_mem;

  numInputs = innerProductParams->numInNodes;
  //Using TIDL_innerProductGetBlockProps() to get outNodesPerCall. roisPerCall variable is not used here.
  TIDL_innerProductGetBlockProps(numInputs, &roisPerCall, &outNodesPerCall);

  kernel_int_mem = (numInputs * outNodesPerCall) + 1024;
  
  if(kernel_int_mem > memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size)
  {
    memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size = (uint32_t)(kernel_int_mem*2);
  }

  return 0;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_innerProductInit
@brief      Function to Initialize the InnerProduct layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/

int32_t TIDL_innerProductInit(
        const TIDL_CreateParams *params, int32_t layerIdx,
        sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
        int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
        void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t tranformSize;
  int32_t status = IALG_EOK;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8) *  ((int32_t)(sizeof(int32_t)));
  int32_t quantizationStyle = params->net->quantizationStyle;
/*
#if defined TEMP_DISABLE_ROW_FLOW && defined (TIDL_BUILD_WITH_MMA)
int32_t tranformSize = 0;
#endif
*/

  tranformSize  = TIDL_getDatElementSize(params->net->TIDLLayers[layerIdx].outData.elementType) *
                  TIDL_innerProductCoeffMemRequired(&params->net->TIDLLayers[layerIdx].layerParams.innerProductParams);

  sTIDL_InnerProductParams_t * innerProductParams =
  &params->net->TIDLLayers[layerIdx].layerParams.innerProductParams;

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

    algLayer->layerParams.innerProductParams.biasParamSize =
      params->net->TIDLLayers[layerIdx].layerParams.innerProductParams.numOutNodes*  ((int32_t)(sizeof(int32_t)));
    if(TIDL_isBiasHighPrecision(params->net->deviceName) == TRUE)
    {
      if(params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8)
      {
        algLayer->layerParams.innerProductParams.biasParamSize =
          ALIGN(params->net->TIDLLayers[layerIdx].layerParams.innerProductParams.numOutNodes, 64) *  ((int32_t)(sizeof(int32_t)));
      }
      else
      {
        algLayer->layerParams.innerProductParams.biasParamSize =
        ALIGN(params->net->TIDLLayers[layerIdx].layerParams.innerProductParams.numOutNodes, 64) *  ((int32_t)(sizeof(int64_t)));
      }

    }

    algLayer->layerParams.innerProductParams.biasParamMem =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)algLayer->layerParams.innerProductParams.biasParamSize, 128);

    algLayer->layerParams.innerProductParams.accMemSize = scratchDataSize;

    algLayer->layerParams.innerProductParams.accMem =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)scratchDataSize, 128);

    algLayer->layerParams.innerProductParams.wtTranformMem =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);

    //Have addtional space for bias during forced reference for inner product
    if(TIDL_forceInnerProductRef(params, &params->net->TIDLLayers[layerIdx]))
      tranformSize += algLayer->layerParams.innerProductParams.biasParamSize;

    if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      algLayer->layerParams.innerProductParams.wtTranformSize =
          tranformSize;
      (void)memset(algLayer->layerParams.innerProductParams.wtTranformMem, 0,
        (size_t)algLayer->layerParams.innerProductParams.wtTranformSize);
      *paramMemTabOffset += ALIGN_SIZE((int32_t)tranformSize, 128);
    }
    else{
      algLayer->layerParams.innerProductParams.wtTranformSize = 0 ;
    }


    int32_t numInputs, numOutputs;
    numInputs = innerProductParams->numInNodes;
    numOutputs = innerProductParams->numOutNodes;
    int8_t * weightPtr = get_int8_t_pointer((int8_t *)(params->net), innerProductParams->weights);
    void * orgBiasPtr = NULL;
    void * biasPtr = NULL;
    float32_tidl inScaleFactor;
    sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
        params->net->TIDLLayers[layerIdx].inData[0]);
    if(TIDL_QuantStyleAsymNP2_TFL != quantizationStyle)
    {
      orgBiasPtr = (int16_t *)get_int8_t_pointer((int8_t*)(params->net), innerProductParams->bias);
      biasPtr = (int16_t*)(algLayer->layerParams.innerProductParams.biasParamMem);
      inScaleFactor = (innerProductParams->weightScale * inDataParams->tensorScale) / innerProductParams->biasScale;
      if (innerProductParams->biasScale == -1.0f)
      {
        inScaleFactor = 0.0f;
      }
    }

    int32_t * orgbiasptr;
    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      //Populate scale and shift for MMA for convolution:
      //Scale ratio
      float32_tidl scaleRatio = 1;
      float32_tidl weightScalePtr =  innerProductParams->weightScale;
      float32_tidl scale_x = inDataParams->tensorScale;
      float32_tidl scale_y = params->net->TIDLLayers[layerIdx].outData.tensorScale;
      //Assuming per axis: (should be single iteration for non per ch) !Replace with axis length
      //Temp logic:
      scaleRatio = (scale_x * weightScalePtr)/scale_y;
      TIDL_getMMAv2_ScaleAndShift(scaleRatio, &algLayer->layerParams.innerProductParams.mmaScale,&algLayer->layerParams.innerProductParams.mmaShift); 
      int32_t axisCtr;
      orgbiasptr = (int32_t *)get_int8_t_pointer((int8_t *)(params->net), innerProductParams->bias);
      biasPtr  = (int32_t *)algLayer->layerParams.innerProductParams.biasParamMem;
      //Simple copy over of bias from model to local memory.
      for(axisCtr = 0; axisCtr < numOutputs; axisCtr++)
      {
        ((int32_t*)biasPtr)[axisCtr] = orgbiasptr[axisCtr];
      }
    }

#if USE_16BIT_BIAS_FOR_8BIT_MODE
    if (params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8)
    {
      if(TIDL_QuantStyleAsymNP2_TFL != quantizationStyle)//No Splitting
      {
        if(TIDL_isBiasHighPrecision(params->net->deviceName) == TRUE)
        {
          TIDL_AM_conv2dBiasSplit((int16_t*)orgBiasPtr, (int32_t*)biasPtr, &innerProductParams->biasB, numOutputs, inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF, TIDL_getDatElementSign(inDataParams->elementType));
        }
        else
        {
          TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int16_t*)biasPtr, &innerProductParams->biasB,
          numOutputs, inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF,TIDL_getDatElementSign(inDataParams->elementType));
        }
      
        if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
        {

          int8_t *tranformPtr = (int8_t*)algLayer->layerParams.innerProductParams.wtTranformMem;
          TIDL_innerProductTransform(weightPtr, tranformPtr, (int16_t*)biasPtr,
            numInputs, numOutputs, params->net->deviceName);
        }
      }
    }
    else
#endif
    {
      if(TIDL_QuantStyleAsymNP2_TFL != quantizationStyle)//No Splitting
      {
          if((TIDL_isBiasHighPrecision(params->net->deviceName) == TRUE))
          {
            TIDL_AM_conv2dBiasSplit((int16_t*)orgBiasPtr, (int64_t*)biasPtr, &innerProductParams->biasB, numOutputs, inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32, 0xFFFF, TIDL_getDatElementSign(inDataParams->elementType));
          }
          else
          {
            TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int16_t*)biasPtr,  &innerProductParams->biasB,
            numOutputs, inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32,0xFFFF,TIDL_getDatElementSign(inDataParams->elementType));
          }

        if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
        {
          int16_t *tranformPtr = (int16_t*)algLayer->layerParams.innerProductParams.wtTranformMem;
          TIDL_innerProductTransform((int16_t*)weightPtr, tranformPtr, (int16_t*)biasPtr,
            numInputs, numOutputs, params->net->deviceName);
        }
      }
    }

    if(TIDL_QuantStyleAsymNP2_TFL == quantizationStyle)
    {
      if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
      {
        int8_t *tranformPtr = (int8_t*)algLayer->layerParams.innerProductParams.wtTranformMem;
        TIDL_innerProductTransform(weightPtr, tranformPtr, (int32_t*)biasPtr,
          numInputs, numOutputs, params->net->deviceName);
      }
    }

  }
  {
    int32_t forceRef = TIDL_forceInnerProductRef(params, &params->net->TIDLLayers[layerIdx]);
    if(forceRef){
      //copy the original weights and bias in alg layer buffer space
      void * src = get_int8_t_pointer((int8_t *)(params->net), innerProductParams->weights);
      void *dst = algLayer->layerParams.innerProductParams.wtTranformMem;
      int32_t size = algLayer->layerParams.innerProductParams.wtTranformSize;
      if(size && (dst != NULL) && (src != NULL)) memcpy(dst,src,size );
    }
  }
  return status;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_eltWiseAlloc
@brief      Function to Request Memory required by the EltWise layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_eltWiseAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);

  return 0;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchReshapeAlloc
@brief      Function to Request Memory required by the batchReshape layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchReshapeAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);

  return 0;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_shuffleChannelAlloc
@brief      Function to Request Memory required by the ShuffleChannel layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_shuffleChannelAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);

  return 0;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_resizeAlloc
@brief      Function to Request Memory required by the ShuffleChannel layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_resizeAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));
  int32_t planeDataSize = params->net->TIDLLayers[layerIdx].outData.pitch[TIDL_CHANNEL_PITCH];
  sTIDL_ResizeLayerParams_t * resizeParams = &params->net->TIDLLayers[layerIdx].layerParams.resizeParams;

  if (resizeParams->mode == TIDL_ResizeBilinear)
  {
      planeDataSize+= 2U*params->net->TIDLLayers[layerIdx].outData.pitch[TIDL_LINE_PITCH]*TIDL_getDatElementSize(params->net->TIDLLayers[layerIdx].outData.elementType);
  }

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);
 /* Allocating DDR SCRATCH */
 if ( planeDataSize >  (int32_t)memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size )
  {
     memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size = (uint32_t)planeDataSize + 128U;
  }
/**************************/
  return 0;
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_eltWiseInit
@brief      Function to Initialize the EltWise layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_eltWiseInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;
  }
  if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchReshapeInit
@brief      Function to Initialize the batchReshape layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchReshapeInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;
  }
  if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_shuffleChannelInit
@brief      Function to Initialize the ShuffleChannel layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_shuffleChannelInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

    algLayer->metaData.totalOps  =
    (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH]); // Verify this:
    algLayer->metaData.actualOps = algLayer->metaData.totalOps;
  }
  return status;
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_resizeInit
@brief      Function to Initialize the ShuffleChannel layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_resizeInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;
  }
  
  /** Resize layer duplicates the top and bottom rows into the input buffer's padded region
   * If resize is the only consumer of the input layer, then there is no issue
   * However, if the input layer has any other consumer layer, then padded region should be restored with zeroes
   * Below code checks for this and populates "inputPadRefillZeros" to be used in resize code
   */
  algLayer->layerParams.resizeParams.inputPadRefillZeros = 0;
  int32_t resizeInDataId = params->net->TIDLLayers[layerIdx].inData[0];
  int32_t numConsumersResizeId = TIDL_getNumConsumersForDataId(params->net, resizeInDataId);
  if(numConsumersResizeId > 1)
  {
    algLayer->layerParams.resizeParams.inputPadRefillZeros = 1;
  }

  if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_flattenAlloc
@brief      Function to Request Memory required by the Flatten layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_flattenAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  return 0;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_constDataAlloc
@brief      Function to Request Memory required by the ConstData layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_constDataAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)outDataSize + 128U);
  return 0;
}

int32_t TIDL_constDataInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int8_t *src=NULL;
  int8_t *dst=NULL;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  sTIDL_DataParams_t*  DataParams = &params->net->TIDLLayers[layerIdx].outData;

  algLayer->layerParams.constDataParams.paramPtr =
    get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
  *paramMemTabOffset += ALIGN_SIZE((int32_t)TIDL_CUSTOM_LAYER_DDR_SIZE, 128);

  int32_t paramOffset = params->net->TIDLLayers[layerIdx].layerParams.constDataParams.offset;
  src = ((int8_t *)(params->net) + paramOffset);
  dst = (int8_t *)algLayer->layerParams.constDataParams.paramPtr;
  memset(dst, 0, outDataSize); //zero point

  int32_t elm_size    = TIDL_getDatElementSize(DataParams->elementType);
  int32_t dstPtrOffset = ((uint32_t)DataParams->pitch[TIDL_LINE_PITCH] * (DataParams->padH)) + (DataParams->padW);
  dst = dst + dstPtrOffset;
  int32_t i=0,ch=0,batch=0;

  for(batch = 0; batch < DataParams->dimValues[TIDL_DIM_BATCH]; batch++)
  {
    for(ch = 0; ch < DataParams->dimValues[TIDL_DIM_NUMCH]; ch++)
    {
      for(i = 0; i < DataParams->dimValues[TIDL_DIM_HEIGHT]; i++)
      {
          memcpy(dst + (batch*DataParams->pitch[TIDL_ROI_PITCH] + ch*DataParams->pitch[TIDL_CHANNEL_PITCH] + i*DataParams->pitch[TIDL_LINE_PITCH])*elm_size,
                  src  + (batch * DataParams->dimValues[TIDL_DIM_NUMCH] * DataParams->dimValues[TIDL_DIM_WIDTH] * DataParams->dimValues[TIDL_DIM_HEIGHT]
                       + ch * DataParams->dimValues[TIDL_DIM_WIDTH] * DataParams->dimValues[TIDL_DIM_HEIGHT]
                       + i*DataParams->dimValues[TIDL_DIM_WIDTH])*elm_size,
                  DataParams->dimValues[TIDL_DIM_WIDTH]*elm_size);
      }
    }
  }

  return status;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_customLayerAlloc
@brief      Function to Request Memory required by the Custom layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_customLayerAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += 128U;/* To handle the alignment if user gives unaligned pointer */
  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)TIDL_CUSTOM_LAYER_DDR_SIZE + 128U);

  { //Add custom layer learnable parameters to this
    sTIDL_CustomParams_t *layerParams = &params->net->TIDLLayers[layerIdx].layerParams.customParams;
    int32_t paramsize = layerParams->rsvdPassThroughSize ;
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)paramsize + 128U);
  }
  return 0;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_customLayerInit
@brief      Function to Initialize the customer layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_customLayerInit(const TIDL_CreateParams *params, int32_t layerIdx,
    sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
    int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
    void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
  {
    int32_t status = IALG_EOK;

    int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

    if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
        outDataSize, TIDLLayersBufPtr);
      TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
    }
    if (status == IALG_EOK)
    {
      TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
      algLayer->scratchSize = 0;
      algLayer->metaData.totalOps =
        (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
          params->net->TIDLLayers[layerIdx].layerParams.eltWiseParams.numInData);
      algLayer->metaData.actualOps = algLayer->metaData.totalOps;
    }

    algLayer->dataFlowMemPtr =
    get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)TIDL_CUSTOM_LAYER_DDR_SIZE, 128);
    algLayer->dataFlowMemSize = TIDL_CUSTOM_LAYER_DDR_SIZE;

    if (status == IALG_EOK)
    { //Copy the learnable or custom layer specific parameters to layer properties
      sTIDL_CustomParams_t *layerParams = &params->net->TIDLLayers[layerIdx].layerParams.customParams;
      int32_t paramSize   = layerParams->rsvdPassThroughSize ;
      int32_t paramOffset = layerParams->rsvdPassThrough ;
      void *dst ;
      sTIDL_AlgCustomParams_t* algCustomParams = &algLayer->layerParams.customParams;

      dst = get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
      *paramMemTabOffset += ALIGN_SIZE(paramSize, 128);
      algCustomParams->paramPtr = dst ;
      algCustomParams->paramSize = paramSize ;
      if(paramSize && paramOffset){
        void * src   = ((int8_t *)(params->net) + paramOffset);
        memcpy(dst, src, paramSize);
      }
    }

    return status;
  }


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_flattenInit
@brief      Function to Initialize the Flatten layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_flattenInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if (status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    algLayer->scratchSize = 0;
    algLayer->metaData.totalOps =
      (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
        params->net->TIDLLayers[layerIdx].layerParams.eltWiseParams.numInData);
    algLayer->metaData.actualOps = algLayer->metaData.totalOps;
  }
  return status;
}


int32_t TIDL_padAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = TIDL_flattenAlloc(params, layerIdx,memRec,TIDLLayersBufPtr);
  sTIDL_PadLayerParams_t *layerParams = &params->net->TIDLLayers[layerIdx].layerParams.padLayerParams;
  int32_t padParamSize = layerParams->perChannelPadConstTensorSize ;
  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)padParamSize + 128U);

  return status;
}

int32_t TIDL_padInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  sTIDL_PadLayerParams_t *layerParams = &params->net->TIDLLayers[layerIdx].layerParams.padLayerParams;
  int32_t paramSize   = layerParams->perChannelPadConstTensorSize ;
  int32_t paramOffset = layerParams->perChannelPadConstTensorOffset ;
  void *dst ;

  sTIDL_AlgPadParams_t* algPadParams = &algLayer->layerParams.padParams;

  status = TIDL_flattenInit(
    params, layerIdx, algLayer, paramMemTabOffset,
    dataMemTabOffset,memRec, outPtr, TIDLLayersBufPtr);

  dst = get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
  *paramMemTabOffset += ALIGN_SIZE(paramSize, 128);
  
  algPadParams->perChannelPadConstTensorPtr = dst ;
  algPadParams->perChannelPadConstTensorSize = paramSize ;

  if(paramSize && paramOffset){
    void * src   = ((int8_t *)(params->net) + paramOffset);
    memcpy(dst, src, paramSize);
  }

  return status;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_colorConversionInit
@brief      Function to Initialize the color conversion layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_colorConversionInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    algLayer->scratchSize = 0;
    algLayer->metaData.totalOps =
      (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
        params->net->TIDLLayers[layerIdx].layerParams.eltWiseParams.numInData);
    algLayer->metaData.actualOps = algLayer->metaData.totalOps;
  }
  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_scatterElementsInit
@brief      Function to Initialize the color conversion layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_scatterElementsInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    algLayer->scratchSize = 0;
    algLayer->metaData.totalOps =
      (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
        params->net->TIDLLayers[layerIdx].layerParams.eltWiseParams.numInData);
    algLayer->metaData.actualOps = algLayer->metaData.totalOps;
  }
  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_reduceInit
@brief      Function to Initialize the color conversion layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_reduceInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    algLayer->scratchSize = 0;
    algLayer->metaData.totalOps =
      (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
        params->net->TIDLLayers[layerIdx].layerParams.eltWiseParams.numInData);
    algLayer->metaData.actualOps = algLayer->metaData.totalOps;
  }
  if((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@fn         TIDL_detectOutAlloc
@brief      Function to Request Memory required by the SSD detcetion output layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_detectOutAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t numConfPts = 0;
  int32_t curData = 0;
  int32_t scratchDataSize;
  int32_t curCnfPlaneSize = 0;
  int32_t maxConfPlaneSize = 0;
  int32_t elementSize = 0;    
  int32_t priorBoxParamSize ;

  sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].inData[0]);
  elementSize = TIDL_getDatElementSize(inDataParams->elementType);

  sTIDL_DetectOutputParams_t  * detectOutParams = &params->net->TIDLLayers[layerIdx].layerParams.detectOutParams;
  priorBoxParamSize = detectOutParams->numHeads * sizeof(sTIDL_AnchorBoxParams_t) ;
  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)priorBoxParamSize + 128U);


  if(detectOutParams->metaArchType != TIDL_metaArchTIDLYolo)
  {
    /*total number input buffers will be twice the number of heads, and first half are location heads,
      and second half is confidence head*/
    for(int32_t i = (params->net->TIDLLayers[layerIdx].numInBufs >> 1) ; i < (params->net->TIDLLayers[layerIdx].numInBufs); i++)
    {
      const int32_t(*indimValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->dimValues;

      const int32_t(*inpitchValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->pitch;

      curData = ((int32_t)(*indimValues)[TIDL_DIM_BATCH] *
        (int32_t)(*indimValues)[TIDL_DIM_NUMCH] *
        ((int32_t)(*indimValues)[TIDL_DIM_HEIGHT])*
        ((int32_t)(*inpitchValues)[TIDL_LINE_PITCH]));

      curCnfPlaneSize = ((int32_t)(*indimValues)[TIDL_DIM_HEIGHT]) * ((int32_t)(*inpitchValues)[TIDL_LINE_PITCH]);

      numConfPts += curData;

      if(maxConfPlaneSize < curCnfPlaneSize)
      {
        maxConfPlaneSize = curCnfPlaneSize;
      }
    }
  }
  else
  {
    for(int32_t i = 0 ; i < (params->net->TIDLLayers[layerIdx].numInBufs); i++)
    {
      const int32_t(*indimValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->dimValues;

      const int32_t(*inpitchValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->pitch;

      curData = ((int32_t)(*indimValues)[TIDL_DIM_BATCH] *
        (((int32_t)(*indimValues)[TIDL_DIM_NUMCH])  - 5)* // yolo has conf and location as common head, and it has 5 channels for box parameter(4) and objectness score(1)
        ((int32_t)(*indimValues)[TIDL_DIM_HEIGHT])*
        ((int32_t)(*inpitchValues)[TIDL_LINE_PITCH]));

      numConfPts += curData;

      curCnfPlaneSize = ((int32_t)(*indimValues)[TIDL_DIM_HEIGHT]) * ((int32_t)(*inpitchValues)[TIDL_LINE_PITCH]);

      if(maxConfPlaneSize < curCnfPlaneSize)
      {
        maxConfPlaneSize = curCnfPlaneSize;
      }
    }
  }

  if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  /*For worst scenario all the sratch memory is reserved in DDR*/

  // L2 related pointers
  /* topMScore, topMScoreSorted, topMIndices, topMIndicesSorted*/
  scratchDataSize = numConfPts * ((sizeof(int16_t) * 2) + (sizeof(int32_t) * 2)) + 128*4;

  // L1 related pointers
  scratchDataSize += (detectOutParams->topK * sizeof(BBox) + 128); //topKBbox
  scratchDataSize += (detectOutParams->topK * sizeof(uint16_t) + 128); //topKScore
  scratchDataSize += (detectOutParams->topK * sizeof(int32_t)  + 128); //topKIndices
  scratchDataSize += (detectOutParams->topK * sizeof(int32_t)  + 128); //nmsKeptIndices
  scratchDataSize += (sizeof(int32_t) * detectOutParams->numClasses + 128); //countMList
  scratchDataSize += (sizeof(int32_t) * detectOutParams->numClasses + 128); //countMListAcc
  scratchDataSize += (detectOutParams->numClasses * sizeof(float) + 128); // if (softmax) tempScore

  // L3 related pointers
  maxConfPlaneSize = (maxConfPlaneSize >> 6) << 6; // make it multiple of 64 for SIMD width
  scratchDataSize += (((maxConfPlaneSize + 63) >> 1) + 128); //pred
  scratchDataSize += ((maxConfPlaneSize * 2 * elementSize) + 128); //featMaxMinVal

  if(scratchDataSize > memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size)
  {
    memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size = (uint32_t)(scratchDataSize);
  }

  return 0;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_detectOutInit
@brief      Function to Initialize the SSD detcetion output layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_detectOutInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t numConfPts = 0;
  int32_t priorBoxParamSize;
  int32_t curData = 0;
  int32_t scratchDataSize;
  int32_t locScratchOffset = 0;
  sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].inData[0]);
  sTIDL_ALgDetectOutputParams_t * algDetectOutParams = &algLayer->layerParams.detectionOutputParams;
  float32_tidl* priorData ;


  sTIDL_DetectOutputParams_t  * detectOutParams = &params->net->TIDLLayers[layerIdx].layerParams.detectOutParams;
  priorData    = (float32_tidl*)(((int8_t *)params->net) + detectOutParams->priorBox);

  if(detectOutParams->metaArchType != TIDL_metaArchTIDLYolo)
  {
    /*total number input buffers will be twice the number of heads, and first half are location heads,
      and second half is confidence head*/
    for(int32_t i = (params->net->TIDLLayers[layerIdx].numInBufs >> 1) ; i < (params->net->TIDLLayers[layerIdx].numInBufs); i++)
    {
      const int32_t(*indimValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->dimValues;

      const int32_t(*inpitchValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->pitch;

      curData = ((int32_t)(*indimValues)[TIDL_DIM_BATCH] *
        (int32_t)(*indimValues)[TIDL_DIM_NUMCH] *
        ((int32_t)(*indimValues)[TIDL_DIM_HEIGHT])*
        ((int32_t)(*inpitchValues)[TIDL_LINE_PITCH]));

      numConfPts += curData;
    }
  }
  else
  {
    for(int32_t i = 0 ; i < (params->net->TIDLLayers[layerIdx].numInBufs); i++)
    {
      const int32_t(*indimValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->dimValues;

      const int32_t(*inpitchValues)[TIDL_DIM_MAX] =
        (const int32_t(*)[TIDL_DIM_MAX])\
        inDataParams->pitch;

      curData = ((int32_t)(*indimValues)[TIDL_DIM_BATCH] *
        (((int32_t)(*indimValues)[TIDL_DIM_NUMCH])  - 5)* // yolo has conf and location as common head, and it has 5 channels for box parameter(4) and objectness score(1)
        ((int32_t)(*indimValues)[TIDL_DIM_HEIGHT])*
        ((int32_t)(*inpitchValues)[TIDL_LINE_PITCH]));

      numConfPts += curData;
    }
  }

  if (params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
      outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }

  priorBoxParamSize = detectOutParams->numHeads * sizeof(sTIDL_AnchorBoxParams_t) ;
  algDetectOutParams->priorBoxPtr =
    get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
  *paramMemTabOffset += ALIGN_SIZE(priorBoxParamSize, 128);
  memcpy(algDetectOutParams->priorBoxPtr, priorData, priorBoxParamSize);


  if (status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    algLayer->scratchSize = 0;
    scratchDataSize = numConfPts * sizeof(int16_t);
    algLayer->layerParams.detectionOutputParams.topMScoreDdr =
      (uint16_t*)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_SCRATCH_DDR_MEM_MEMREC].base, locScratchOffset);
    locScratchOffset = locScratchOffset + ALIGN_SIZE((int32_t)scratchDataSize, 128);

    scratchDataSize = numConfPts * sizeof(int16_t);
    algLayer->layerParams.detectionOutputParams.topMScoreSortedDdr =
      (uint16_t*)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_SCRATCH_DDR_MEM_MEMREC].base, locScratchOffset);
    locScratchOffset = locScratchOffset + ALIGN_SIZE((int32_t)scratchDataSize, 128);

    scratchDataSize = numConfPts * sizeof(int32_t);
    algLayer->layerParams.detectionOutputParams.topMIndicesDdr =
      (int32_t*)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_SCRATCH_DDR_MEM_MEMREC].base, locScratchOffset);
    locScratchOffset = locScratchOffset + ALIGN_SIZE((int32_t)scratchDataSize, 128);

    scratchDataSize = numConfPts * sizeof(int32_t);
    algLayer->layerParams.detectionOutputParams.topMIndicesSortedDdr =
      (int32_t*)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_SCRATCH_DDR_MEM_MEMREC].base, locScratchOffset);
    locScratchOffset = locScratchOffset + ALIGN_SIZE((int32_t)scratchDataSize, 128);

    algLayer->layerParams.detectionOutputParams.topMDdr = numConfPts;
    algLayer->layerParams.detectionOutputParams.scratchDDRConsumed = locScratchOffset;

    algLayer->metaData.totalOps =
      (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *
        params->net->TIDLLayers[layerIdx].layerParams.eltWiseParams.numInData);
    algLayer->metaData.actualOps = algLayer->metaData.totalOps;

    TIDL_collectLocConfHeadInfo(params->net->TIDLLayers, algLayer, NULL, algDetectOutParams->priorBoxPtr);

    if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      TIDL_odFindValidLocAndScoreKernelInit(params,algLayer,&params->net->TIDLLayers[layerIdx],0,0,0);
    }


  }

  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_argMaxAlloc
@brief      Function to Request Memory required by the ArgMax layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_argMaxAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  return 0;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_roiPoolingAlloc
@brief      Function to Request Memory required by the ArgMax layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_roiPoolingAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  return 0;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_roiPoolingInit
@brief      Function to Initialize the ArgMax layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specicfic params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer ouput Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_roiPoolingInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }

  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_argMaxInit
@brief      Function to Initialize the ArgMax layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_argMaxInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
  }
  if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

int32_t TIDL_elementPromotionEnabledInAvgPool(const TIDL_CreateParams *params, sTIDL_Layer_t *tidlLayer)
{
  sTIDL_PoolingParams_t *poolParams  = &tidlLayer->layerParams.poolParams;
  
  int32_t promoteModeOn = 0;
  if(params->net->quantizationStyle==TIDL_QuantStyleAsymNP2_TFL)
  {
    if(poolParams->poolingType== TIDL_AveragePooling)
    {
      if(((poolParams->kernelW== 3) && (poolParams->kernelH== 3)) && ((poolParams->strideW== 2) && (poolParams->strideH== 2)))
      {
        promoteModeOn = 1;
      }
    }
  }
  return promoteModeOn;
}

int32_t TIDL_getScaleMemSize(sTIDL_PoolingParams_t *poolParams,
                             int32_t outWidth,
                             int32_t outHeight,
                             int32_t outLinePitch,
                             int32_t scaleFact,
                             int32_t elementSize,
                             int32_t scaleElementSize,
                             int32_t promoteModeOn)
{
  int32_t scaleMemSize;
  if(promoteModeOn)
  {
    elementSize *= 2;
  }
  if((poolParams->kernelW == 0) && (poolParams->kernelH == 0))
  {
    scaleMemSize = 0;
  }
  else if(poolParams->poolingType== TIDL_AveragePooling)
  {
    if((poolParams->strideW== 2) && (poolParams->strideH== 2) &&
       (((poolParams->kernelW== 2) && (poolParams->kernelH== 2)) ||
        ((poolParams->kernelW== 3) && (poolParams->kernelH== 3))))
    {
      scaleMemSize = 2*outWidth*elementSize;
    }
    else
    {
      scaleMemSize = outHeight*outLinePitch*scaleElementSize*scaleFact;
    }
  }
  else
  {
    scaleMemSize = 0;
  }

  return scaleMemSize;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_poolingAlloc
@brief      Function to Request Memory required by the pooling layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/

int32_t TIDL_poolingAlloc(const TIDL_CreateParams *params,
                          int32_t layerIdx, IALG_MemRec *memRec,
                          sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));
  sTIDL_PoolingParams_t *poolParams  = &params->net->TIDLLayers[layerIdx].layerParams.poolParams;

  sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].inData[0]);

  sTIDL_Layer_t *tidlLayer  = &params->net->TIDLLayers[layerIdx];
  int32_t outHeight        = tidlLayer->outData.dimValues[TIDL_DIM_HEIGHT];
  int32_t outWidth         = tidlLayer->outData.dimValues[TIDL_DIM_WIDTH];
  int32_t outPitch         = params->net->TIDLLayers[layerIdx].outData.pitch[TIDL_LINE_PITCH];
  int32_t elementSize      = TIDL_getDatElementSize(inDataParams->elementType);
  int32_t procElemSize     = TIDL_getProcessingElementSizeInBytes(tidlLayer);
  int32_t scaleFact        = poolParams->strideW;
  int32_t scaleElementSize = procElemSize*2; /* Scale is calculated as 16 bit for 8 bit input and 32 bit for 16 bit input */
  int32_t scaleMemSize = 0;
  int32_t promoteModeOn       = TIDL_elementPromotionEnabledInAvgPool(params, tidlLayer);
  scaleMemSize = TIDL_getScaleMemSize(poolParams, outWidth, outHeight, outPitch, scaleFact, procElemSize, scaleElementSize, promoteModeOn);

  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)scaleMemSize + 128U);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params,
                                       layerIdx,
                                       outDataSize,
                                       TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);

  return 0;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_poolingInit
@brief      Function to Initialize the pooling layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/

int32_t TIDL_poolingInit(const TIDL_CreateParams *params,
                                int32_t layerIdx,
                                sTIDL_AlgLayer_t * algLayer,
                                int32_t *paramMemTabOffset,
                                int32_t *dataMemTabOffset,
                                const IALG_MemRec *memRec,
                                void ** outPtr,
                                sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;

  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));
  sTIDL_PoolingParams_t *poolParams  = &params->net->TIDLLayers[layerIdx].layerParams.poolParams;
  sTIDL_Layer_t        *tidlLayer = &params->net->TIDLLayers[layerIdx];
  sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].inData[0]);

  algLayer->layerParams.poolParams.startRowNumberInTensor = 0;
  algLayer->layerParams.poolParams.orgInTensorHeight = inDataParams->dimValues[TIDL_DIM_HEIGHT];

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params,
                                       layerIdx,
                                       outDataSize,
                                       TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

    sDataFlowInfo_t *dataFlowInfo = algLayer->dataFlowInfo;
    int32_t st, heightStart = 0;
    int32_t numHandles = TIDL_privGetNumHandles(dataFlowInfo);
    for(st=0; st<numHandles; st++)
    {
      int32_t outFeatHeight = params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_HEIGHT];
      int32_t outFeatWidth = params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_WIDTH];
      TIDL_privGetOutProcSize(dataFlowInfo, st, &params->net->TIDLLayers[layerIdx], &outFeatWidth, &outFeatHeight, params->net->deviceName);//Correct for AEP??

      if(outFeatHeight > 0)
      {
        int32_t outHeight        = outFeatHeight;
        int32_t outWidth         = outFeatWidth;
        int32_t outPitch         = params->net->TIDLLayers[layerIdx].outData.pitch[TIDL_LINE_PITCH];
        int32_t elementSize      = TIDL_getDatElementSize(inDataParams->elementType);
        int32_t scaleFact        = poolParams->strideW;
        int32_t procElemSize     = TIDL_getProcessingElementSizeInBytes(tidlLayer);
        int32_t scaleElementSize = procElemSize*2; /* Scale is calculated as 16 bit for 8 bit input and 32 bit for 16 bit input */
        int32_t promoteModeOn       = TIDL_elementPromotionEnabledInAvgPool(params, tidlLayer);
        algLayer->layerParams.poolParams.scaleMemSize[st] = TIDL_getScaleMemSize(poolParams, outWidth, outHeight, outPitch, scaleFact, procElemSize, scaleElementSize, promoteModeOn);

        algLayer->layerParams.poolParams.scalePtr[st] =
                get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
        *paramMemTabOffset += ALIGN_SIZE(algLayer->layerParams.poolParams.scaleMemSize[st], 128U);

        algLayer->layerParams.poolParams.nextOutOffset = 0;
        (void)memset(algLayer->layerParams.poolParams.scalePtr[st], 0, algLayer->layerParams.poolParams.scaleMemSize[st]);

        int32_t i,j;
        int32_t totalOutHeight = params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_HEIGHT];

        /* The lines below must match the same lines in function TIDL_UpdateScaleFactors()
         * Local average pooling 2x2, 3x3, with stride 2 implement an optimized kernel that assumes the scale factors bit-depth are
         * the same as the input data type, which is either 8-bits or 16-bits.
         * The remaining local average pooling assume 16-bits or 32-bits scale factors.
         * */
        if ((poolParams->poolingType== TIDL_AveragePooling) &&
            ((poolParams->strideW== 2) && (poolParams->strideH== 2) &&
             (((poolParams->kernelW== 2) && (poolParams->kernelH== 2)) ||
              ((poolParams->kernelW== 3) && (poolParams->kernelH== 3)))))
        {
          int32_t internal_pooling_weight;

          int32_t inWidth  = inDataParams->dimValues[3];
          int32_t inHeight = inDataParams->dimValues[2];

          if (procElemSize == 1)
          {
            if(params->net->quantizationStyle==TIDL_QuantStyleAsymNP2_TFL && ((poolParams->kernelW== 3) && (poolParams->kernelH== 3)))
            {internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;}
            else
            {internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U8;}
          }
          else
          {
            internal_pooling_weight= TIDL_INTERNAL_POOLING_WEIGHT_Q_U16; /* To avoid overflow, we set it 12-bits instead fo 16-bits */
          }

          algLayer->layerParams.poolParams.internalPoolingWeightQ= (int32_t)internal_pooling_weight;

          if(algLayer->layerParams.poolParams.scaleMemSize[st] > 0)
          {
            for(i=0; i<totalOutHeight; i=i+totalOutHeight-1)
            {
              for (j = 0; j<outWidth; j++)
              {
                int32_t startH    = (i * poolParams->strideH);
                int32_t startW    = (j * poolParams->strideW);

                int32_t hEndComp  = startH + poolParams->kernelH;
                int32_t hEndBound = inHeight + poolParams->padH;
                int32_t endH      = (hEndComp<hEndBound)?hEndComp:hEndBound;

                int32_t wEndComp  = startW + poolParams->kernelW;
                int32_t wEndBound = inWidth + poolParams->padW;
                int32_t endW      = (wEndComp<wEndBound)?wEndComp:wEndBound;

                int32_t poolSize  = (endH - startH) * (endW - startW);
                uint32_t scaleVal = ((uint32_t)(((float)((uint32_t)1 << internal_pooling_weight)) / ((float)poolSize)));
                int32_t scaleIndexStart = (i==0)? 0: outWidth;
                int32_t scaleIndex = scaleIndexStart+j;

                if(procElemSize == 1)
                {
                  if(params->net->quantizationStyle==TIDL_QuantStyleAsymNP2_TFL && ((poolParams->kernelW== 3) && (poolParams->kernelH== 3)))
                  {
                  ((uint16_t*)algLayer->layerParams.poolParams.scalePtr[st])[scaleIndex] = (uint16_t)scaleVal;
                  }
                  else
                  {
                  ((uint8_t*)algLayer->layerParams.poolParams.scalePtr[st])[scaleIndex] = (uint8_t)scaleVal;
                  }
                }
                else /* if(elementSize==2) */
                {
                  ((uint16_t*)algLayer->layerParams.poolParams.scalePtr[st])[scaleIndex] = (uint16_t)scaleVal;
                }
              }
            }
          }
        }
        else
        {
          int32_t internal_pooling_weight = TIDL_INTERNAL_POOLING_WEIGHT_Q_U16;

          algLayer->layerParams.poolParams.internalPoolingWeightQ= (int32_t)internal_pooling_weight;

          if(algLayer->layerParams.poolParams.scaleMemSize[st] > 0)
          {
            for (i = heightStart; i< (heightStart+outHeight); i++)
            {
              for (j = 0; j<outWidth; j++)
              {
                int32_t startH    = (i * poolParams->strideH);
                int32_t startW    = (j * poolParams->strideW);
                int32_t inWidth  = inDataParams->dimValues[3];
                int32_t inHeight = inDataParams->dimValues[2];

                int32_t hEndComp  = startH + poolParams->kernelH;
                int32_t hEndBound = inHeight + poolParams->padH;
                int32_t endH      = (hEndComp<hEndBound)?hEndComp:hEndBound;

                int32_t wEndComp  = startW + poolParams->kernelW;
                int32_t wEndBound = inWidth + poolParams->padW;
                int32_t endW      = (wEndComp<wEndBound)?wEndComp:wEndBound;

                int32_t poolSize  = (endH - startH) * (endW - startW);
                uint16_t scaleVal = ((uint16_t)(((float32_tidl)((uint32_t)1 << internal_pooling_weight)) / ((float32_tidl)poolSize)));
                int32_t scaleIndex = (((i-heightStart)*outPitch)+j)*scaleFact;
                if(procElemSize == 1)
                {
                  ((uint16_t*)algLayer->layerParams.poolParams.scalePtr[st])[scaleIndex] = scaleVal;
                }
                else /* if(elementSize==2) */
                {
                  ((uint32_t*)algLayer->layerParams.poolParams.scalePtr[st])[scaleIndex] = scaleVal;
                }
              }
            }
            heightStart+=outHeight;
          }
        }
      }
    }

    if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
    }
  }

  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchNormAlloc
@brief      Function to Request Memory required by the Batch Norm layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchNormAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t weightSizeInBytes = ((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8);
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * (weightSizeInBytes) *  ((int32_t)(sizeof(int32_t)));
  int32_t numChannels = params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH];
  int32_t biasParamSize = numChannels *  ((int32_t)(sizeof(int32_t)));
  int32_t slopeFactSize = numChannels *  ((int32_t)(sizeof(int32_t)));
  int32_t weightParamSize = numChannels *  weightSizeInBytes;  

  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)slopeFactSize + 128U);
  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)biasParamSize + 128U);
  memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((uint32_t)weightParamSize + 128U);
  

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);

  return 0;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchNormInit
@brief      Function to Initialize the Batch Norm layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchNormInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int32_t weightSizeInBytes = ((params->net->TIDLLayers[layerIdx].weightsElementSizeInBits + 7) / 8);
  int32_t weightParamSize;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * (weightSizeInBytes) *  ((int32_t)(sizeof(int32_t)));
  int32_t numChannels = params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH];
  sTIDL_BatchNormParams_t * batchNormParams = &params->net->TIDLLayers[layerIdx].layerParams.batchNormParams;
  sTIDL_ALgBatchNormParams_t * algBatchNormParams = &algLayer->layerParams.batchNormParams;
  sTIDL_DataParams_t * dataParams = TIDL_getDataParams(params->net,
                                                       params->net->TIDLLayers[layerIdx].inData[0]);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  if(status == IALG_EOK)
  {
    TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
    TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
    algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

    algBatchNormParams->biasParamSize = numChannels*  ((int32_t)(sizeof(int32_t)));
    algBatchNormParams->biasParamMem =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)algLayer->layerParams.batchNormParams.biasParamSize, 128);

    weightParamSize   = numChannels *  weightSizeInBytes;
    algBatchNormParams->weightParamMem =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE(weightParamSize, 128);

    algLayer->layerParams.batchNormParams.slopeFactSize = params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH] *  ((int32_t)(sizeof(int32_t)));
    algLayer->layerParams.batchNormParams.slopeFactMem =
      get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, *paramMemTabOffset);
    *paramMemTabOffset += ALIGN_SIZE((int32_t)algBatchNormParams->slopeFactSize, 128);

    algLayer->layerParams.batchNormParams.slopeFact = (int32_t *)algLayer->layerParams.batchNormParams.slopeFactMem;
    int32_t preluScale = 1, i;
    void * slopePtr  = get_int8_t_pointer((int8_t *)(params->net), params->net->TIDLLayers[layerIdx].actParams.slope);

    for (i = 0; i < params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH]; i++)
    {
      if(params->net->TIDLLayers[layerIdx].actParams.actType == TIDL_PRelU)
      {
        if(params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8)
        {
          preluScale = ((int8_t*)slopePtr)[i];
          algLayer->layerParams.batchNormParams.slopeFact[i] = (int32_t)((preluScale*(1 << 8)) / params->net->TIDLLayers[layerIdx].actParams.slopeScale);
        }
        else
        {
          preluScale = ((int16_t*)slopePtr)[i];
          algLayer->layerParams.batchNormParams.slopeFact[i] = (int32_t)(((preluScale*(1 << 8)) / params->net->TIDLLayers[layerIdx].actParams.slopeScale)*256);
        }
      }
      else
      {
        algLayer->layerParams.batchNormParams.slopeFact[i] = 1;
      }
    }

    int16_t * orgBiasPtr = (int16_t *)get_int8_t_pointer((int8_t *)(params->net), batchNormParams->bias);
    int8_t * biasPtr  = (int8_t *)algBatchNormParams->biasParamMem;

    float32_tidl inScaleFactor;
    sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(params->net,
      params->net->TIDLLayers[layerIdx].inData[0]);

    inScaleFactor = (batchNormParams->weightScale * inDataParams->tensorScale) / batchNormParams->biasScale;

    if(weightParamSize){
      void * weightPtr   = ((int8_t *)(params->net) + batchNormParams->weights);
      memcpy(algBatchNormParams->weightParamMem, weightPtr, weightParamSize);
    }

    if(params->net->TIDLLayers[layerIdx].weightsElementSizeInBits <= 8)
    {
      TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int16_t*)biasPtr, &algBatchNormParams->biasB, numChannels, inScaleFactor, TIDL_SAT_LO_INT16, TIDL_SAT_HI_INT16,0xFF, TIDL_getDatElementSign(dataParams->elementType));
    }
    else
    {
      int32_t maxBiasB = 0xFFFF;
      /* This condition indicates mixed precision where processing is in 16 bit but input is signed input.
      Here as target implementation scales the input with 256, we need to limit the biasB so that it doesn't
      go beyond 8 bits as the same is later multiplied by 256 to match the scale of accumulator*/
      if ( dataParams->elementType == TIDL_SignedChar )
      {
        maxBiasB = 0xFF;
      }
      TIDL_conv2dBiasSplit((int16_t*)orgBiasPtr, (int32_t*)biasPtr, &algBatchNormParams->biasB, numChannels, inScaleFactor, TIDL_SAT_LO_INT32, TIDL_SAT_HI_INT32, maxBiasB, TIDL_getDatElementSign(dataParams->elementType));
    }

    if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
    }
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_softmaxAlloc
@brief      Function to Request Memory required by the Softmax layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_softmaxAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);


  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);

  return 0;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_softmaxInit
@brief      Function to Initialize the Softmax layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_softmaxInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }

  TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);

  algLayer->metaData.totalOps  =
  (params->net->TIDLLayers[layerIdx].outData.dimValues[TIDL_DIM_NUMCH]);
  algLayer->metaData.actualOps = algLayer->metaData.totalOps;
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_concatAlloc
@brief      Function to Request Memory required by the Concatinate layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_concatAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_concatAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));
  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }
  TIDL_outBuffAlloc(params, layerIdx, memRec, outDataSize);
  TIDL_scratchBufAlloc(layerIdx, memRec, scratchDataSize);

  return 0;
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_concatInit
@brief      Function to Initialize the Concat layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_concatInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_concatInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }

  TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
  TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
  algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

  if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_dataConvertInit
@brief      Function to Initialize the Concat layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_dataConvertInit(const TIDL_CreateParams *params,
                                  int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
                                  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
                                  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr)
{
  int32_t status = IALG_EOK;
  int32_t outDataSize = TIDL_updateDataParamsPitch(&params->net->TIDLLayers[layerIdx].outData);
  int32_t scratchDataSize = outDataSize * ( ((int32_t)(sizeof(int32_t))));

  if(params->optimiseExtMem != TIDL_OptimiseExtMemL0)
  {
    outDataSize = TIDL_findFreeOutBuff(params, layerIdx,
                                       outDataSize, TIDLLayersBufPtr);
    TIDLLayersBufPtr->outDataSize[layerIdx] = outDataSize;
  }

  TIDL_outBuffInit(params, layerIdx, dataMemTabOffset, memRec, outPtr, outDataSize);
  TIDL_scratchBufInit(layerIdx, memRec, &algLayer->scratchMem, scratchDataSize);
  algLayer->scratchSize = (int32_t)memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size;

  if ((params->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    status = TIDL_setupKernelHandle(params, layerIdx, algLayer);
  }
  return status;
}

/**
 * @brief This layer fills the pad buffers with Zeros
 *
 * @param intAlgHandle : Algorithm Instance handle
 * @param TIDLLayer : This structure contains the common layer parameters in tidl
 * @param outPtrs : poniters to ouptut buffers
 * @param trMem : Memory to store the DMA trasfer properties
 * @param i : layer index
 * @return int32_t : retuns the status
 */
int32_t TIDL_layerPadding(
  TIDL_Handle          intAlgHandle,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * outPtrs[],
  uint8_t              * trMem,
  int32_t i
  )
{
  int32_t j, status = IALG_EOK;
  bool padRow = false, padCol = false;
  if ((intAlgHandle->perfSimOutput != NULL) && (status == IALG_EOK))
  {
    int32_t padC;

    if(TIDLLayer->layerType == TIDL_ConcatLayer)
    {
      if ( intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padCZeros != 0 )
      {
        //:TODO: this is a temporary fix which needs to be fixed in concat linear flow
        intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padCFillZeros =
          intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padCZeros ;
      }
    }

    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY)
    {
      padC = intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padC;
    }
    else
    {
      padC = intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padCFillZeros;
    }

    for (j = 0; j < TIDLLayer->numOutBufs; j++)
    {
      int32_t padRFillZeros = intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padRFillZeros;
      int32_t padRZeros = intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padRZeros;
      int32_t padCReq = intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE].padCReq;

      int32_t paddingType = TIDL_PADDING_TYPE_BOTH;

      if((padCReq > 0) && (padRZeros == 0) && (padRFillZeros == 0))
      {
        paddingType = TIDL_PADDING_TYPE_TOP_LEFT;
      }

      if(TIDLLayer->layerType == TIDL_PadLayer)
      {
        paddingType = TIDL_PADDING_TYPE_PAD_LAYER;
      }

      if (((padRFillZeros > 0) || (TIDL_PADDING_TYPE_TOP_LEFT == paddingType)) && (TIDL_PADDING_TYPE_PAD_LAYER != paddingType))
      {
        padRow = true;
        status = TIDL_FillPaddedRows((uint8_t *)outPtrs[j],
                                             &intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE],
                                             TIDLLayer->outData.dimValues[TIDL_DIM_WIDTH],
                                             TIDLLayer->outData.dimValues[TIDL_DIM_HEIGHT],
                                             TIDLLayer->outData.dimValues[TIDL_DIM_BATCH],
                                             TIDLLayer->outData.pitch[TIDL_LINE_PITCH],
                                             TIDLLayer->outData.pitch[TIDL_CHANNEL_PITCH]* TIDL_getDatElementSize(TIDLLayer->outData.elementType),
                                             TIDLLayer->outData.pitch[TIDL_ROI_PITCH]* TIDL_getDatElementSize(TIDLLayer->outData.elementType),
                                             intAlgHandle->dmaUtilsContext,
                                             intAlgHandle->zeroVector1k,
                                             &intAlgHandle->isPadDmaPending,
                                             trMem,
                                             TIDLLayer->outData.elementType, //TIDL_getDatElementSize(TIDLLayer->outData.elementType),
                                             paddingType,
                                             &TIDLLayer->layerParams.padLayerParams,
                                             TIDLLayer->outData.padH,
                                             TIDLLayer->outData.padW,
                                             TIDLLayer->outData.tensorZeroPoint,
                                             0,                                /* parameter needed only for pad layer */
                                             NULL);             /* parameter needed only for pad layer */
#if defined (SOC_J784S4)
#ifndef HOST_EMULATION
/**
 * Issue noticed in resnet18v1 2MP
 * Need to ensure DMA transfer is complete before CPU col padding starts
 * If col padding starts before DMA is complete, it will fetch the cache line state at this point of time when DMA padding is still happening, so it 
 * will fetch corrupt data for the memory regions where DMA padding is yet to be completed
 * If we do cache writeback after col padding, this same corrupt data would overwrite the DMA padded region resulting in incorrect output
*/
  TIDL_syncPadTransfer(intAlgHandle, trMem);
#endif
#endif
      }
      if((padC > 0) && (TIDL_PADDING_TYPE_PAD_LAYER != paddingType) && (status == IALG_EOK))
      {
        padCol = true;
        status = TIDL_FillPaddedCols((uint8_t *)outPtrs[j],
                                             &intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE],
                                             TIDLLayer->outData.dimValues[TIDL_DIM_WIDTH],
                                             TIDLLayer->outData.dimValues[TIDL_DIM_HEIGHT],
                                             TIDLLayer->outData.dimValues[TIDL_DIM_BATCH],
                                             TIDLLayer->outData.pitch[TIDL_LINE_PITCH],
                                             TIDLLayer->outData.pitch[TIDL_CHANNEL_PITCH]* TIDL_getDatElementSize(TIDLLayer->outData.elementType),
                                             TIDLLayer->outData.pitch[TIDL_ROI_PITCH]* TIDL_getDatElementSize(TIDLLayer->outData.elementType),
                                             TIDLLayer->outData.elementType, //TIDL_getDatElementSize(TIDLLayer->outData.elementType),
                                             intAlgHandle->createParams->flowCtrl,
                                             paddingType,
                                             &TIDLLayer->layerParams.padLayerParams,
                                             TIDLLayer->outData.padH,
                                             TIDLLayer->outData.padW,
                                             TIDLLayer->outData.tensorZeroPoint,
                                             NULL);               /* parameter needed only for pad layer */
      }

      /**
       * Wb/inv required after CPU write is done for next layer processing
       * This wb/inv must be common for row and col padding (cannot be done only for col padding) since row padding can also be done using CPU in some cases
       * This can be optimized to disable wb when no col padding and row padding happens via DMA
      */
      if(padRow || padCol)
      {
        TIDL_enableL1DCacheWb();
      }

      if( status != IALG_EOK)
      {
        break;
      }
    }
  }
  
  /* Fill zeros in the Batch Pad region as the current layer could have written to this pad region */          
  for (j = 0; j < TIDLLayer->numOutBufs; j++)
  {
    if ((TIDLLayer->outData.dimValues[TIDL_DIM_BATCH] == 1) && (TIDLLayer->outData.numBatchW > 1)) // Do this for only stitched layers
    {
      int32_t  i0, i1, i2, i3;
      uint8_t * ptr = (uint8_t *)outPtrs[j];
      int32_t width = TIDLLayer->outData.dimValues[TIDL_DIM_WIDTH];
      int32_t height = TIDLLayer->outData.dimValues[TIDL_DIM_HEIGHT];
      int32_t numChs = TIDLLayer->outData.dimValues[TIDL_DIM_NUMCH];
      int32_t numBatchW = TIDLLayer->outData.numBatchW;
      int32_t batchPadW = TIDLLayer->outData.batchPadW;
      int32_t elementSize = TIDL_getDatElementSize(TIDLLayer->outData.elementType);
      int32_t channelPitch = TIDLLayer->outData.pitch[TIDL_CHANNEL_PITCH] * elementSize;
      int32_t linePitch = TIDLLayer->outData.pitch[TIDL_LINE_PITCH] * elementSize;
      int32_t OrgWidth = (width - (batchPadW *(numBatchW-1)))/numBatchW;
      int32_t ptrOffset = ((TIDLLayer->outData.pitch[TIDL_LINE_PITCH] * TIDLLayer->outData.padH) + TIDLLayer->outData.padW + OrgWidth) * elementSize ;
      uint32_t batchPitch = (OrgWidth + TIDLLayer->outData.batchPadW) * elementSize;
      if(((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) ||
          ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_DSP_NATC) == TIDL_FLOW_CTRL_DSP_NATC))
      {
        for (i0 = 0; i0 < numChs; i0++)
        {
          for (i1 = 0; i1 < height; i1++)
          {
            for (i2 = 0; i2 < (numBatchW - 1); i2++)
            {
              for (i3 = 0; i3 < batchPadW*elementSize; i3++)
              {
                ptr[ptrOffset + i0*channelPitch + i1*linePitch + i2*batchPitch + i3] = 0;
              }
            }
          }
        }
      }
      else
      {
        TIDL_DspFillPaddedBatches(ptr, ptrOffset, (batchPadW*elementSize), height, numChs, (numBatchW-1), linePitch, channelPitch, batchPitch);
      }
      TIDL_enableL1DCacheWb();
    }
  } 
  return status;
}

/**
 * @brief This function returns the input buffer pointers for the layer
 *
 * @param inBufs : Inpupt buffers
 * @param outBufs : Ouput buffers
 * @param intAlgHandle : Algorithm Instance handle
 * @param algLayer : Pointer to current layer algorithm specific params
 * @param TIDLLayer : Pointer to common layer parameters
 * @param inPtrs : input buffer pointers
 * @param i : layer Index
 * @return int32_t : returns the status
 */
int32_t TIDL_getLayerInPtrs(
  IVISION_InBufs      *inBufs,
  IVISION_InBufs      *outBufs,
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * inPtrs[],
  int32_t i)
{
  int32_t j, twStatus, status = IALG_EOK;

  for(j = 0; j < TIDLLayer->numInBufs; j++)
  {
    int32_t curInDataId, inDataId  =  TIDLLayer->inData[j];
    if(intAlgHandle->createParams->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      curInDataId = (int32_t)intAlgHandle->TIDLLayersBuf->newInDataId[i][j];
    }
    else
    {
      curInDataId = inDataId;
    }
    if(algLayer->isInData[j] == 1)
    {
      sTIDL_DataParams_t *inDataParams;
      inDataParams = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].outData;
      if (inDataParams != NULL)
      {
        inPtrs[j] =
        TIDL_getDataBuff(inBufs->bufDesc,inBufs->numBufs,curInDataId, inDataParams->dimValues[TIDL_DIM_BATCH], inDataParams->pitch, intAlgHandle->createParams->isInbufsPaded);
        if(inPtrs[j] != NULL)
        {
          TIDLLayer->inData[j] = intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].outData.dataId;
          twStatus = tidl_writeTraceDataBuf((int8_t*)inPtrs[j],intAlgHandle->createParams->net,curInDataId,
            (int8_t *)intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base,
            intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size, 0, inDataParams->dimValues[TIDL_DIM_HEIGHT], inDataParams->pitch[TIDL_CHANNEL_PITCH]);
          if(twStatus != IALG_EOK)
          {
            tidl_printf(0,"Trace write failed\n");
          }
        }
      }
    }
    else if(algLayer->isInOutData[j] == 1)
    {
      sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(intAlgHandle->createParams->net,
                                                            TIDLLayer->inData[j]);

      inPtrs[j] =
      TIDL_getDataBuff(outBufs->bufDesc,outBufs->numBufs,curInDataId, inDataParams->dimValues[TIDL_DIM_BATCH], inDataParams->pitch, 1);
    }
    else
    {
      if(intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].layerType != TIDL_ConstDataLayer)
      {
        if (intAlgHandle->createParams->net->dataFlowInfo != NULL)
        {
          inPtrs[j] = TIDL_getSysScratchPtr(&intAlgHandle->perfSimOutput->sdataFlowInfo[algLayer->inLayerIdx[j]].bufInfo[OUT_FEAT_MAP][WRITE],
                                            &intAlgHandle->sysScratchPtr,
                                            1U);
        }
        else
        {
          inPtrs[j] = (uint8_t *)intAlgHandle->dataBuf[curInDataId];
        }
      }
      else
      {
        int32_t algIdx = getAlgLyrIdx (intAlgHandle->alglayerParams, algLayer->inLayerIdx[j]);
        sTIDL_AlgLayer_t *constalgLayer = get_AlgLayer_t_pointer(intAlgHandle->alglayerParams, algIdx);
        sTIDL_Layer_t& constLayer = intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]];
        inPtrs[j] = constalgLayer->layerParams.constDataParams.paramPtr;

        twStatus = tidl_writeTraceDataBuf((int8_t*)inPtrs[j],intAlgHandle->createParams->net,constLayer.outData.dataId,
          (int8_t *)intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base,
          intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size, 0, constLayer.outData.dimValues[TIDL_DIM_HEIGHT], constLayer.outData.pitch[TIDL_CHANNEL_PITCH]);
        if(twStatus != IALG_EOK)
        {
          tidl_printf(0,"Trace write failed\n");
        }
      }
    }
    if(inPtrs[j] == NULL)
    {
      status = TIDL_E_INVALID_IO_LINE_PITCH;
      break;
    }
  }

  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY)
  {
    if (intAlgHandle->createParams->net->dataFlowInfo != 0)
    {
      int32_t totalBufSize = 0;
      for (j = 0; j < TIDLLayer->numInBufs; j++)
      {
      sTIDL_DataParams_t * inDataParams = TIDL_getDataParams(intAlgHandle->createParams->net,
                                                            TIDLLayer->inData[j]);

        int32_t dataElementSize = TIDL_getDatElementSize(inDataParams->elementType);
        int32_t numBatches = inDataParams->dimValues[0];
        /* For first only 16-bit BN layer dataElementSize is different from that of rest of the layers in the network */
        if( (TIDL_getDatElementSize(inDataParams->elementType) != TIDL_getDatElementSize(TIDLLayer->outData.elementType)) &&
            (TIDLLayer->layerType == TIDL_BatchNormLayer))
        {
          dataElementSize = TIDL_getDatElementSize(inDataParams->elementType);
        }
        int32_t numBytesToCopy = inDataParams->pitch[TIDL_ROI_PITCH]*dataElementSize*numBatches;
        memcpy(intAlgHandle->refScratchBuf+totalBufSize, inPtrs[j], numBytesToCopy);
        inPtrs[j] = intAlgHandle->refScratchBuf+totalBufSize;
        totalBufSize += numBytesToCopy;
      }
    }
  }
  return status;
}
/**
 * @brief This function returns the input buffer pointers for the layer
 *
 * @param outBufs : Output buffers
 * @param intAlgHandle : Algorithm Instance handle
 * @param algLayer : Pointer to current layer algorithm specific params
 * @param TIDLLayer : Pointer to common layer parameters
 * @param outPtrs : output buffer pointers
 * @param i : layer Index
 * @return int32_t : returns the status
 */
int32_t TIDL_getLayerOutPtrs(
  IVISION_InBufs      *outBufs,
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * outPtrs[],
  int32_t i
  )
{
  int32_t j, status = IALG_EOK;
  for(j = 0; j < TIDLLayer->numOutBufs; j++)
  {
    int32_t outDataId = TIDLLayer->outData.dataId;
    if(algLayer->isOutData[j] == 1)
    {
      outPtrs[j] = (uint8_t *)
      TIDL_getDataBuff(outBufs->bufDesc,outBufs->numBufs,outDataId, TIDLLayer->outData.dimValues[TIDL_DIM_BATCH], TIDLLayer->outData.pitch, 1);
      if(outPtrs[j] == NULL)
      {
        status = TIDL_E_INVALID_IO_LINE_PITCH;
        break;
      }
    }
    else
    {

      if(intAlgHandle->createParams->net->dataFlowInfo != 0)
      {
          outPtrs[j] = (uint8_t *)TIDL_getSysScratchPtr(&intAlgHandle->perfSimOutput->sdataFlowInfo[i].bufInfo[OUT_FEAT_MAP][WRITE],
                                                              &intAlgHandle->sysScratchPtr, 1U);
      }
      else
      {
        outPtrs[j] = (uint8_t *)intAlgHandle->dataBuf[outDataId];
        if(outPtrs[j] == NULL)
        {
          int32_t curOutDataId = (int32_t)intAlgHandle->TIDLLayersBuf->newOutDataId[i][j];
          outPtrs[j] = (uint8_t *)intAlgHandle->dataBuf[curOutDataId];
          intAlgHandle->dataBuf[outDataId]  = (uint8_t *)(outPtrs[j]);
        }
      }
    }
    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY)
    {
      /* This is required so that padded regions are filled with zero's as Padding is done only
      when NC information is available */
      if(intAlgHandle->createParams->net->dataFlowInfo == 0)
      {
        int32_t dataElementSize = TIDL_getDatElementSize(TIDLLayer->outData.elementType);
        /* Assign to zero point */
        (void)memset(outPtrs[j],  TIDLLayer->outData.tensorZeroPoint,
                     TIDLLayer->outData.dimValues[TIDL_DIM_NUMCH] *
                     TIDLLayer->outData.pitch[TIDL_CHANNEL_PITCH] *
                     dataElementSize);
      }
    }
  }
  return status;
}
/**
 * @brief This function Updates TensorStats for all the layers
 *
 * @param intAlgHandle : Algorithm Instance handle
 * @param TIDLLayer : Pointer to common layer parameters
 * @param outPtrs : output buffer pointers
 * @param i : layer Index
 * @return int32_t : returns the status
 */
int32_t TIDL_updateAllLayersTensorStats(
  TIDL_Handle          intAlgHandle,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * outPtrs[],
  int32_t i)
{
  int32_t j, status = TIDL_SUCCESS;

  if( ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT) ||
      (intAlgHandle->createParams->quantRangeUpdateFactor != 0.0f))
  {
    for (j = 0; j < TIDLLayer->numOutBufs; j++)
    {
      status = TIDL_UpdateTensorRange(intAlgHandle, i, j, outPtrs[j]);
      if( status != TIDL_SUCCESS)
      {
        break;
      }
      if  (( intAlgHandle->createParams->net->calibrationOption & TIDL_CalibOptionBiasCalibration) == TIDL_CalibOptionBiasCalibration )
      {
        status = TIDL_UpdateTensorPerChannelMean(intAlgHandle,
                                                                           i,
                                                                           j,
                                                                           outPtrs[j]);
        if( status != TIDL_SUCCESS)
        {
          break;
        }
      }

    }
  }
  return status;
}
/**
 * @brief This function copies persistent weights to internal memory
 *
 * @param intAlgHandle : Algorithm Instance handle
 */
void TIDL_copyPersistentWeightsToIntMem(TIDL_Handle intAlgHandle)
{
  if ( ( intAlgHandle->perfSimOutput != NULL ) &&
    ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0) )
  {
    int32_t layerIdx;
    int32_t currAlgLayer = 0;
    sTIDL_Network_t * net = intAlgHandle->createParams->net;
    for (layerIdx = 0; layerIdx < net->numLayers; layerIdx++)
    {
      if(net->TIDLLayers[layerIdx].layersGroupId == intAlgHandle->createParams->currLayersGroupId)
      {
        if (( net->TIDLLayers[layerIdx].layerType == TIDL_ConvolutionLayer ) || ( net->TIDLLayers[layerIdx].layerType  == TIDL_Deconv2DLayer ))
        {
          sTIDL_AlgLayer_t *algLayer = get_AlgLayer_t_pointer(intAlgHandle->alglayerParams,currAlgLayer);
          //:TODO: Need to hanlde this for super tiling, eventually we should use this also from NC
          int8_t * pCoeffExtMem = (int8_t *)algLayer->layerParams.convParams.pCoeffs[0];
          int8_t * pCoeffIntMem = NULL;
          int32_t intMemLineOffset;
          int32_t extMemLineOffset;

          extMemLineOffset= intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].bufInfo[WT_MAP][READ].bufWidth;

          if ( intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].bufInfo[WT_MAP][WRITE].accessor == DMA_ONCE )
          {
            pCoeffIntMem = (int8_t *)TIDL_getSysScratchPtr( &intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].bufInfo[WT_MAP][WRITE],
                                                                       &intAlgHandle->sysScratchPtr,
                                                                       1);
            intMemLineOffset = intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].bufInfo[WT_MAP][WRITE].bufWidth;

          }
          else if ( intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].wtOneShot[READ].accessor == DMA_ONCE )
          {
            pCoeffIntMem = (int8_t *)TIDL_getSysScratchPtr( &intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].wtOneShot[READ],
                                                                       &intAlgHandle->sysScratchPtr,
                                                                       1);
            intMemLineOffset = intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].wtOneShot[READ].bufWidth;
          }
          else
          {
          }

          if  (( pCoeffIntMem != NULL ) && (pCoeffExtMem != NULL))
          {
            TIDL_memcpy2D(pCoeffIntMem,
                          pCoeffExtMem,
                          intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].bufInfo[WT_MAP][READ].activeBufWidth,
                          intAlgHandle->perfSimOutput->sdataFlowInfo[layerIdx].bufInfo[WT_MAP][READ].bufHeight,
                          intMemLineOffset,
                          extMemLineOffset,
                          intAlgHandle->dmaUtilsContext,
                          intAlgHandle->memcpyTr);
          }
        }

        currAlgLayer++;
      }
    }
  }
}

void TIDL_switchHandles(void* algHandle)
{
  TIDL_Handle handle      = (TIDL_Handle)algHandle;
  void * TIDL_lastActiveHandle = TIDL_getLastActiveHandle();

  if(TIDL_lastActiveHandle != handle && TIDL_lastActiveHandle != NULL)
  {
    TIDL_deactivate((IALG_Handle)TIDL_lastActiveHandle);
  }
  if((TIDL_lastActiveHandle != handle) || (handle->algState == (uint8_t)ALG_NOT_ACTIVE))
  {
    TIDL_activate((IALG_Handle)(void*)handle);
    TIDL_setLastActiveHandle(handle);
  }
}

int32_t TIDL_referencFlow(const TIDL_CreateParams *pCreateParams){
  int32_t refFlow = 0 ;
  if(((pCreateParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) != 0) ||
    ((pCreateParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != 0)
  )
  {
    refFlow = 1 ;
  }
  return refFlow ;
}

int32_t TIDL_getSizeNet(const TIDL_CreateParams *pCreateParams){
  int32_t size = 128  ;
  /** we need the basic structure and compiled part of network always
   * and additionally the parameter part in case of reference flow
   */
#if !(TIDL_KEEP_NET_FROM_APP_ALIVE)
  size = pCreateParams->net->netBufInfo[TIDL_NET_STRUCTURE_BUF].size +
    pCreateParams->net->netBufInfo[TIDL_NET_COMPILER_BUF].size  ;

  if(TIDL_referencFlow(pCreateParams)){
    size +=  pCreateParams->net->netBufInfo[TIDL_NET_PARAMS_BUF].size ;
  }
#endif
  return size ;
}

void TIDL_MoveNetToPrivateMemory(TIDL_Handle algHandle, 
  const IALG_MemRec memRec[])
{
  sTIDL_Network_t *pNet = algHandle->createParams->net ;
#if !(TIDL_KEEP_NET_FROM_APP_ALIVE)
  int32_t size, bufIdx;
  int8_t *src, *dst, *pBaseSrc ;
  int32_t isReference = TIDL_referencFlow(algHandle->createParams);

  pBaseSrc = (int8_t*) pNet ;
  for(bufIdx = TIDL_NET_STRUCTURE_BUF; bufIdx <  TIDL_NET_TOTAL_BUF; bufIdx++)
  {
    if( (isReference) ||
        (bufIdx == TIDL_NET_STRUCTURE_BUF) || 
        (bufIdx == TIDL_NET_COMPILER_BUF) )
    {
      src = get_int8_t_pointer(pBaseSrc,pNet->netBufInfo[bufIdx].offset);
      dst = get_int8_t_pointer((int8_t*) memRec[ALG_PERSIST_DDR_NET_MEMREC].base,
        pNet->netBufInfo[bufIdx].offset);
      size = pNet->netBufInfo[bufIdx].size ;
      memcpy(dst,src,size);
    }
  }
  algHandle->createParams->net = (sTIDL_Network_t*) memRec[ALG_PERSIST_DDR_NET_MEMREC].base ;
#else
  sTIDL_AlgLayer_t * alglayerParams = algHandle->alglayerParams ;
  sTIDL_DetectOutputParams_t *pDetParams;
  sTIDL_ALgDetectOutputParams_t * algDetLyrParams = NULL;

  for(int32_t i = 0 ; i < pNet->numLayers ; i++){
    switch(pNet->TIDLLayers[i].layerType){
      case TIDL_DetectionOutputLayer:
      case TIDL_OdPostProcessingLayer:
        //Find the alg Layer Params for this layer
        for(int32_t j = 0 ; j < pNet->numLayers  && alglayerParams !=NULL ; j++){
          if(alglayerParams[j].layerIdx == i){
            algDetLyrParams = &alglayerParams[j].layerParams.detectionOutputParams;
            break;
          } 
        }
        pDetParams = &pNet->TIDLLayers[i].layerParams.detectOutParams;
        if(algDetLyrParams){
          algDetLyrParams->priorBoxPtr = (void*) get_int8_t_pointer((int8_t*)pNet, 
          pDetParams->priorBox);
        }
        break;
    }
  }
#endif  
  return ;
}

sPerfSim_t * TIDL_getCompilerBufPtr(
    sTIDL_Network_t *pNet,
    const IALG_MemRec memRec[] )
{
  sPerfSim_t *pPerfInfo, *pPerfInfoSrc ;

  pPerfInfo = pPerfInfoSrc = 
    (sPerfSim_t *)get_int8_t_pointer((int8_t *)pNet, pNet->dataFlowInfo);
#if TIDL_KEEP_NET_FROM_APP_ALIVE
   memRec = NULL ;
#endif
  if(memRec != NULL){
    pPerfInfo = (sPerfSim_t *)get_int8_t_pointer((int8_t *)memRec[ALG_PERSIST_DDR_NET_MEMREC].base, 
      pNet->dataFlowInfo);
    memcpy(pPerfInfo, pPerfInfoSrc, pNet->netBufInfo[TIDL_NET_COMPILER_BUF].size);
  }
  return pPerfInfo ;
}

void TIDL_forceTargetDeviceNonOTF(int32_t *targetDevice, int32_t layerType, int32_t convType)
{
  if(layerType==TIDL_Deconv2DLayer || convType==TIDLCONV_TYPE_DECONV)
  {
    *targetDevice &= (~TIDL_OTF_FLAG_BIT);
  }  
}
