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
@file    tidl_resize.c
@brief   This file defines private functions for resize layer.
@version 0.1 (Aug 2019) : Initial version
----------------------------------------------------------------------------
*/

#include <math.h>
#include "tidl_resize.h"
#include "float.h"
#include "tidl_commonUtils.h"
#include "tidl_priv_algo.h"
#include "tidl_device_functions.h"

/**
 * @brief This is reference implementation of Resize layer
 * 
 * @tparam Tin : template for input data buffers 
 * @param pIn : Pointer to input memory
 * @param pOut : Pointer to output memory 
 * @param algLayer : Pointer to the layer specific parameters
 * @param tidlLayer : Pointer to the common layer parameters
 * @param params : Copy of Resize layer parameters
 * @param inDataParams : parameters of the input data buffer
 */
template <class Tin>
void TIDL_refResize(
    Tin *pIn,
    Tin *pOut,
    sTIDL_AlgLayer_t *algLayer,
    sTIDL_Layer_t *tidlLayer,
    sTIDL_ResizeLayerParams_t *params,
    sTIDL_DataParams_t *inDataParams)
{
  uint32_t numInChannels        = (uint16_t)inDataParams->dimValues[TIDL_DIM_NUMCH];
  uint32_t inWidth              = (uint16_t)inDataParams->dimValues[TIDL_DIM_WIDTH];
  uint32_t inHeight             = (uint16_t)inDataParams->dimValues[TIDL_DIM_HEIGHT];
  uint32_t inPitch              = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
  uint32_t inChPitch            = (uint32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  uint32_t outPitch             = (uint16_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  uint32_t outChPitch           = (uint32_t)tidlLayer->outData.pitch[TIDL_CHANNEL_PITCH];
  uint32_t outWidth             = (uint16_t)tidlLayer->outData.dimValues[TIDL_DIM_WIDTH];
  uint32_t outHeight            = (uint16_t)tidlLayer->outData.dimValues[TIDL_DIM_HEIGHT];
  int32_t  numBatches              = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch           = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch          = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  

  float32_tidl wRatio ;
  float32_tidl hRatio ;

  int32_t widthResizeRatio  = params->resizeRatio[3];
  int32_t heightResizeRatio = params->resizeRatio[2];

  if (params->resizeRatio[3] > 0)
  {
    wRatio = 1 / params->resizeRatio[3];
  }
  else
  {
    wRatio = 0;
  }
  if (params->resizeRatio[2] > 0)
  {
    hRatio = 1 / params->resizeRatio[2];
  }
  else
  {
    hRatio = 0;
  }

  if (params->mode == TIDL_ResizeNearest)
  {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    float32_tidl hLoc, wLoc;
    int hIdx, wIdx;
    for(l=0; l<numBatches; l++)
    {
    for (k = 0; k < numInChannels; k++)
    {
      for (i = 0; i < outHeight; i++)
      {
        hLoc = hRatio * (i + 0.5) - 0.5;
        hLoc = (hLoc < 0) ? 0 : hLoc;
        hIdx = hLoc + 0.5;
        hIdx = (hIdx < inHeight) ? hIdx : (inHeight - 1);
        for (j = 0; j < outWidth; j++)
        {
          wLoc = wRatio * (j + 0.5) - 0.5;
          wLoc = (wLoc < 0) ? 0 : wLoc;
          wIdx = wLoc + 0.5;
          wIdx = (wIdx < inWidth) ? wIdx : inWidth - 1;
          int32_t inputOffset = inPitch * hIdx + wIdx;
          int32_t outputOffset = outPitch * i + j;

          *(pOut + l * outBatchPitch + k * outChPitch + outputOffset) = *(pIn + l * inBatchPitch + k * inChPitch + inputOffset);
        }
      }
    }
    }
  }
  else
  if (params->mode == TIDL_ResizeBilinear)
  {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    float32_tidl hLoc, wLoc;
    int hIdx, wIdx, hNext, wNext;
    float32_tidl w00, w01, w10, w11;
    int32_t enableHClip = 0;
    /* Horizontal clipping should not be done while processing different proc sizes */
    if(TIDL_privGetProcType(algLayer->dataFlowInfo) == 0)
    {
      if(algLayer->procType == 0)
      {
        enableHClip = 1;
      }
    }
    else
    {
      enableHClip = 1;
    }

    for(l=0; l<numBatches; l++)
    {
    for (k = 0; k < numInChannels; k++)
    {
      for (i = 0; i < outHeight; i++)
      {
        hLoc = hRatio * (i + 0.5) - 0.5;
        if(1 == enableHClip)
        {
          hLoc = (hLoc < 0) ? 0 : hLoc;
        }
        if(hLoc < 0)
        {
          hIdx = floor(hLoc);
        }
        else
        {
          hIdx = hLoc;
        }
        hNext = (hIdx < (inHeight - 1)) ? 1 : 0;
        w11 = hLoc - hIdx;
        w10 = 1 - w11;
        for (j = 0; j < outWidth; j++)
        {
          wLoc = wRatio * (j + 0.5) - 0.5;
          wLoc = (wLoc < 0) ? 0 : wLoc;
          wIdx = wLoc;
          w01 = wLoc - wIdx;
          w00 = 1 - w01;
          int32_t inputOffset = inPitch * hIdx + wIdx;
          int32_t inputOffset2 = inputOffset;
          int32_t outputOffset = outPitch * (i) + (j);
          wNext = (wIdx < (inWidth - 1)) ? 1 : 0;

          /* Calculate the offset for second line differently when horizontal clipping is disabled */
          if(inputOffset < 0)
          {
            inputOffset2 = wIdx;
          }

          Tin i00 = *(pIn + l * inBatchPitch + k * inChPitch + inputOffset);
          Tin i01 = *(pIn + l * inBatchPitch + k * inChPitch + inputOffset + wNext);
          Tin i10 = *(pIn + l * inBatchPitch + k * inChPitch + inputOffset2 + hNext * inPitch);
          Tin i11 = *(pIn + l * inBatchPitch + k * inChPitch + inputOffset2 + hNext * inPitch + wNext);

          int32_t inter1, inter2;
          uint8_t w00Int, w01Int;
          uint8_t w10Int, w11Int;

          if ((params->resizeRatio[2] == params->resizeRatio[3]) && ((params->resizeRatio[2] == 2.0)|| (params->resizeRatio[2] == 4.0)))
          {
            if(params->resizeRatio[2] == 4)
            {
              heightResizeRatio = 3;
              widthResizeRatio  = 3;
            }
            else
            {
              heightResizeRatio = 2;
              widthResizeRatio  = 2;
            }
            w00Int = w00 * (1 << widthResizeRatio);
            w01Int = (1 << widthResizeRatio) - w00Int;
            w10Int = w10 * (1 << heightResizeRatio);
            w11Int = (1 << heightResizeRatio) - w10Int;
            inter1 = (i00 * w00Int + i01 * w01Int) ;
            inter2 = (i10 * w00Int + i11 * w01Int) ;
            *(pOut + l * outBatchPitch + k * outChPitch + outputOffset) = (w10Int * inter1 + w11Int * inter2) >> (heightResizeRatio + widthResizeRatio);

          }
          else
          {
            *(pOut + l * outBatchPitch + k * outChPitch + outputOffset) = (w10 * (i00 * w00 + i01 * w01) + w11 * (i10 * w00 + i11 * w01));
          }
        }
      }
    }
    }
  }
  else
  {
    tidl_printf(0, "params->mode is  Not supported !!!\n ");
    assert(0);
  }
}

/**
 * @brief This is reference implementation of Resize layer
 * 
 * @param tidlLayer : Pointer to the common layer parameters
 * @param inPtrs : Pointer to input memory
 * @param outPtr : Pointer to output memory 
 * @param inDataParams : parameters of the input data buffer
 * @param outDataParams : parameters of the output data buffer
 * @param basePrmPtr : Copy of Resize layer parameters
 */
int32_t TIDL_resizeProcessSP(
  sTIDL_Layer_t        * tidlLayer,
  void                 * inPtrs[],
  void                 * outPtr,
  sTIDL_DataParams_t   * inDataParams[],
  sTIDL_DataParams_t   * outDataParams,
  uint8_t              * basePrmPtr
  )
{
  sTIDL_ResizeLayerParams_t *params = &tidlLayer->layerParams.resizeParams;
  float32_tidl *in   = (float32_tidl*)inPtrs[0];
  float32_tidl *out  = (float32_tidl*)outPtr;

  uint32_t numInChannels        = (uint16_t)inDataParams[0]->dimValues[1];
  uint32_t inWidth              = (uint16_t)inDataParams[0]->dimValues[3];
  uint32_t inHeight             = (uint16_t)inDataParams[0]->dimValues[2];
  uint32_t inPitch              = (uint16_t)inDataParams[0]->pitch[TIDL_LINE_PITCH];
  uint32_t inChPitch            = (uint32_t)inDataParams[0]->pitch[TIDL_CHANNEL_PITCH];
  uint32_t outPitch             = (uint16_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  uint32_t outChPitch           = (uint32_t)tidlLayer->outData.pitch[TIDL_CHANNEL_PITCH];
  uint32_t outWidth             = (uint16_t)tidlLayer->outData.dimValues[3];
  uint32_t outHeight            = (uint16_t)tidlLayer->outData.dimValues[2];
  int32_t  numBatches              = (int32_t)inDataParams[0]->dimValues[TIDL_DIM_BATCH];
  uint32_t inBatchPitch           = (uint32_t)inDataParams[0]->pitch[TIDL_ROI_PITCH];
  uint32_t outBatchPitch          = (uint32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];  

  int32_t inOffset = inDataParams[0]->padH * inPitch + inDataParams[0]->padW;
  int32_t outOffset = outDataParams->padH * outPitch + outDataParams->padW;

  float32_tidl wRatio ;
  float32_tidl hRatio ;

  if (params->resizeRatio[3] > 0)
  {
    wRatio = 1 / params->resizeRatio[3];
  }
  else
  {
    wRatio = 0;
  }
  if (params->resizeRatio[2] > 0)
  {
    hRatio = 1 / params->resizeRatio[2];
  }
  else
  {
    hRatio = 0;
  }


  if (params->mode == TIDL_ResizeNearest)
  {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    float32_tidl hLoc, wLoc;
    int hIdx, wIdx;
    for (l = 0; l < numBatches; l++)
    {
    for (i = 0; i < outHeight; i++)
    {
      hLoc = hRatio * (i + 0.5) - 0.5;
      hLoc = (hLoc < 0) ? 0 : hLoc;
      hIdx = hLoc+0.5;
      hIdx = (hIdx < inHeight) ? hIdx : (inHeight-1);
      for (j = 0; j < outWidth; j++)
      {
        wLoc = wRatio * (j + 0.5) - 0.5;
        wLoc = (wLoc < 0) ? 0 : wLoc;
        wIdx = wLoc+0.5;
        wIdx = (wIdx < inWidth) ? wIdx : inWidth-1;
        int32_t inputOffset = inOffset + inPitch  * hIdx + wIdx;
        int32_t outputOffset = outOffset + outPitch * i + j;
        for (k = 0; k < numInChannels; k++)
        {
          *(out + l*outBatchPitch + k*outChPitch + outputOffset) = *(in + l*inBatchPitch + k*inChPitch + inputOffset);
        }
      }
    }
    }
  }
  else
  if (params->mode == TIDL_ResizeBilinear)
  {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    float32_tidl hLoc, wLoc;
    int hIdx, wIdx, hNext, wNext;
    float32_tidl w00, w01, w10, w11;
    for (l = 0; l < numBatches; l++)
    {
    for (i = 0; i < outHeight; i++)
    {
      hLoc = hRatio * (i + 0.5) - 0.5;
      hLoc = (hLoc < 0) ? 0 : hLoc;
      hIdx = hLoc;
      hNext = (hIdx < (inHeight-1)) ? 1 : 0;
      w11 = hLoc - hIdx;
      w10 = 1 - w11;
      for (j = 0; j < outWidth; j++)
      {
        wLoc = wRatio * (j + 0.5) - 0.5;
        wLoc = (wLoc < 0) ? 0 : wLoc;
        wIdx = wLoc;
        w01 = wLoc - wIdx;
        w00 = 1 - w01;
        int32_t inputOffset = inOffset+ inPitch  * hIdx + wIdx;
        int32_t outputOffset = outOffset + outPitch * (i) + (j);
        wNext = (wIdx < (inWidth-1)) ? 1 : 0;

        for (k = 0; k < numInChannels; k++)
        {
          float32_tidl i00 = *(in + l*inBatchPitch + k*inChPitch + inputOffset);
          float32_tidl i01 = *(in + l*inBatchPitch + k*inChPitch + inputOffset + wNext);
          float32_tidl i10 = *(in + l*inBatchPitch + k*inChPitch + inputOffset + hNext*inPitch);
          float32_tidl i11 = *(in + l*inBatchPitch + k*inChPitch + inputOffset + hNext*inPitch + wNext);

          *(out + l*outBatchPitch + k*outChPitch + outputOffset) = (w10*(i00* w00 +  i01* w01) + w11*(i10* w00 +  i11* w01));
        }
      }
    }
    }
  }
  else
  {
    tidl_printf(0,"params->mode is  Not supported !!!\n ");
    assert(0);
  }

  return IALG_EOK;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_RESIZE
@fn         TIDL_ResizeProcess
@brief      Resizes the frames
@param      intAlgHandle :  tidl algorothm handle
@param      algLayer : Ptr Common Layer parameters and other layer parameters.
@param      tidlLayer: Ptr to RESIZE layer parameters which includes input,
                        output buffer pointers also.
@param      inPtrs: Ptr array to input buffers  in external memory.
@param      outPtrs: Ptr to output buffer in external memory.
@param      sysMems: Structure Ptr to internal memory buffers.
@remarks    None
@return     status
----------------------------------------------------------------------------
*/
int32_t TIDL_resizeProcess(
    TIDL_Handle intAlgHandle,
    sTIDL_AlgLayer_t *algLayer,
    sTIDL_Layer_t *tidlLayer,
    void *inPtrs[],
    void *outPtrs[],
    sTIDL_sysMemHandle_t *sysMems)
{
  int32_t status = TIDL_SUCCESS;
  sDataFlowInfo_t * localDataFlowPtr = algLayer->dataFlowInfo;

  if(intAlgHandle->createParams->net->weightsElementSize == 4)
  {
    sTIDL_DataParams_t * inDataPrms[TIDL_NUM_IN_BUFS] = {0};
    for(int j=0; j < tidlLayer->numInBufs; j++)
    {
      inDataPrms[j]  = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].outData;
    }
    status = TIDL_resizeProcessSP(tidlLayer, inPtrs, outPtrs[0], inDataPrms, &tidlLayer->outData, (uint8_t*)intAlgHandle->createParams->net);
    return (status);
  }

  sTIDL_ResizeLayerParams_t *params = &tidlLayer->layerParams.resizeParams;
  sTIDL_ALgResizeLayer_t *resizeParams;
  resizeParams = &algLayer->layerParams.resizeParams;
  uint32_t flowCtrl = intAlgHandle->createParams->flowCtrl;

  if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    if (resizeParams->isOptResizeAvail == 0)
    {
      tidl_printf(1," WARNING : Running unoptimized code (Natural C code) for the resize layer number  %d !!!\n ", algLayer->layerIdx);
      flowCtrl |= TIDL_FLOW_CTRL_REF_ONLY;
    }
  }

  if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY)
  {
    status = TIDL_resizeDspProcess(intAlgHandle, algLayer, tidlLayer, inPtrs, outPtrs, sysMems);
  }
  else /* ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) */
  {

    sTIDL_DataParams_t *inDataParams;
    inDataParams = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;

    uint32_t inElmtSize     = TIDL_getDatElementSize(inDataParams->elementType);
    uint32_t outElmtSize    = TIDL_getDatElementSize(tidlLayer->outData.elementType);

    uint16_t inPitch        = (uint16_t)inDataParams->pitch[TIDL_LINE_PITCH];
    uint16_t inPitchBytes   = inPitch * inElmtSize;
    uint16_t outPitch       = (uint16_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];

    // Output parameters
    uint32_t resizeOutChPitch        = tidlLayer->outData.pitch[TIDL_CHANNEL_PITCH];
    uint32_t resizeOutChPitchBytes   = resizeOutChPitch * TIDL_getDatElementSize(tidlLayer->outData.elementType);
    uint32_t resizeNumChannels       = tidlLayer->outData.dimValues[TIDL_DIM_NUMCH];
    uint32_t resizeOutLinePitch      = tidlLayer->outData.pitch[TIDL_LINE_PITCH];
    uint32_t resizeOutLinePitchBytes = resizeOutLinePitch * TIDL_getDatElementSize(tidlLayer->outData.elementType);

    // Input parameters
    uint32_t resizeInChPitch    = inDataParams->pitch[TIDL_CHANNEL_PITCH];
    uint32_t resizeInHeight     = inDataParams->dimValues[TIDL_DIM_HEIGHT];
    uint32_t resizeInWidth      = inDataParams->dimValues[TIDL_DIM_WIDTH];
    uint32_t resizeInWidthBytes = resizeInWidth * inElmtSize;
    uint32_t resizeInChPitchBytes= resizeInChPitch * inElmtSize;

    uint8_t *outPtr         = ((uint8_t *)outPtrs[0]) + (tidlLayer->outData.padH * outPitch + tidlLayer->outData.padW) * outElmtSize;
    uint8_t *inPtrOrig = ((uint8_t *)inPtrs[0]) +  ((inDataParams->padH - 1) * inPitch + inDataParams->padW - 1) * inElmtSize;
    uint8_t *inPtr     = ((uint8_t *)inPtrs[0]) +  (inDataParams->padH * inPitch + inDataParams->padW) * inElmtSize;
    int32_t copyTopLine = 0, copyBottomLine = 0;
    int32_t inputWidth = 0, inputHeight = 0;

    if (params->mode == TIDL_ResizeBilinear)
    {
      if ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY)
      {
        if(TIDL_privGetProcType(localDataFlowPtr) == 0)
        {
          if(algLayer->procType == 0)
          {
            copyTopLine = 1;
          }
          else if(algLayer->procType == 2)
          {
            copyBottomLine = 1;
            TIDL_privGetInProcSize(localDataFlowPtr, algLayer->procType, tidlLayer, &inputWidth, &inputHeight, 0);//TIDL_TDA4AEP: Currently not setting correctly for AEP/ OTF buffers;
            /* Input height is one more due to bilinear property, hence subtract 1 to be at the correct location */
            inputHeight -= 1;
          }
        }
        else
        {
          copyTopLine = 1;
          copyBottomLine = 1;
          inputHeight = resizeInHeight;
        }
        if(TIDL_isPadOTF(intAlgHandle->createParams->net->deviceName))
        {
          copyTopLine = 0;
          copyBottomLine = 0;
        }
        int32_t numBatches     = (int32_t)inDataParams->dimValues[TIDL_DIM_BATCH];
        uint32_t inBatchPitch  = (uint32_t)inDataParams->pitch[TIDL_ROI_PITCH];        
        for (int k = 0; k < numBatches; k++)
        {
        for (int c = 0; c < resizeNumChannels; c++)
        {
          for (int j = 0; j < resizeInWidthBytes; j++)
          {
            if(1 == copyTopLine)
            {
              *(inPtrOrig + k * inBatchPitch + c * resizeInChPitchBytes + inElmtSize + j) = *(inPtr + k * inBatchPitch + c * resizeInChPitchBytes + j);
            }
            if(1 == copyBottomLine)
            {
              *(inPtrOrig + k * inBatchPitch + c * resizeInChPitchBytes + inElmtSize + (inputHeight + 1) * inPitchBytes + j) =
                  *(inPtr + k * inBatchPitch + c * resizeInChPitchBytes + (inputHeight - 1) * inPitchBytes + j);
            }
          }
        }
        }
      }
    }
    if (inDataParams->elementType == TIDL_SignedChar)
    {
      TIDL_refResize((int8_t *)inPtr, (int8_t *)outPtr, algLayer, tidlLayer, params, inDataParams);
    }
    else if (inDataParams->elementType == TIDL_UnsignedChar)
    {
      TIDL_refResize((uint8_t *)inPtr, (uint8_t *)outPtr, algLayer, tidlLayer, params, inDataParams);
    }
    else if (inDataParams->elementType == TIDL_SignedShort)
    {
      TIDL_refResize((int16_t *)inPtr, (int16_t *)outPtr, algLayer, tidlLayer, params, inDataParams);
    }
    else if (inDataParams->elementType == TIDL_UnsignedShort)
    {
      TIDL_refResize((uint16_t *)inPtr, (uint16_t *)outPtr, algLayer, tidlLayer, params, inDataParams);
    }
    else
    {
      tidl_printf(0, "TIDL_ResizeProcess in elementType is  Not supported !!!\n ");
    }
    if ((flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      int32_t layerIdx = algLayer->layerIdx;
      TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 1, 0, 0);
    }
    TIDL_enableL1DandL2CacheWb();
  }
  return 0;
}
