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
@file    tidl_crop.c
@brief   This file defines private functions for Data Convert layer.
@version 0.1 (May 2021) : Initial version [ADK]
----------------------------------------------------------------------------
*/

#include "tidl_alg_int.h"
#include "tidl_dataConvert.h"
#include "tidl_commonUtils.h"

#include <stdio.h>



/**
 * @brief This is reference implementation of Data Convert layer
 *
 * @tparam Tin : template for input data buffers
 * @tparam Tout : template for output data buffers
 * @param  pIn : Pointer to input memory
 * @param  pOut : Pointer to output memory
 * @param inPtrOffset  : offset for the input buffer for crop
 * @param outPtrOffset : offset for the input buffer for crop
 * @param outWidth : width of the output buffer
 * @param outHeight : height of the output buffer
 * @param numChs : no of channels
 * @param inLinePitch : pitch of the input buffer
 * @param outLinePitch : pitch of the output buffer
 * @param inChPitch : Chnnel pitch of the input buffer
 * @param outChPitch : Chnnel pitch of the output buffer
 */

template <typename Tsrc, typename Tdst, typename Tacc, typename Tscale>
//:TODO:  Keep bias container different from accumulator
void TIDL_refDataConvertNew(Tsrc *src, Tdst *dst, int32_t src_offset, int32_t dst_offset,
                         int32_t nb, int32_t nc, int32_t nl, int32_t np,
                         int32_t src_bp, int32_t dst_bp, int32_t src_cp, int32_t dst_cp, int32_t src_lp, int32_t dst_lp, int32_t src_pp, int32_t dst_pp,
                         Tacc bias, Tscale scale, int32_t shift)
{

    int32_t i0, i1, i2, i3;
    Tdst *d0 = dst + dst_offset, *d1, *d2, *d3;
    Tsrc *s0 = src + src_offset, *s1, *s2, *s3;
    Tacc data, val;
    Tdst min, max;
    max = std::numeric_limits<Tdst>::max();
    min = std::numeric_limits<Tdst>::lowest();


    if (typeid(Tacc) == typeid(float32_tidl))
    {
      float32_tidl q1, q2;
      TIDL_dataConvertSplitBias((float32_tidl)bias,
                                &q1,
                                &q2);
      bias = q1* q2;
    }
    else if (typeid(Tacc) == typeid(int64_t))/* 16 bit case */
    {
      int16_t q1;/* Keep type of q1 and scale as signed in order to handle
      negative  value of zero point */
      int16_t q2;/* Type of q2 is determined by source */

      if ((typeid(Tsrc) == typeid(int16_t)) ||
          (typeid(Tsrc) == typeid(int8_t)))
      {
        TIDL_dataConvertSplitBias((int64_t)bias,
                                  &q1,
                                  (int16_t *)&q2);
      }
      else
      {
        TIDL_dataConvertSplitBias((int64_t)bias,
                                  &q1,
                                  (uint16_t *)&q2);
      }
      bias = q1* q2;
    }
    else/* 8 bit case */
    {
      int8_t q1;/* Keep type of q1 and scale as signed in order to handle
      negative  value of zero point */
      Tsrc q2;/* Type of q2 is determined by source */

      if (typeid(Tsrc) == typeid(int8_t))
      {
        TIDL_dataConvertSplitBias((int32_t)bias,
                                  &q1,
                                  (int8_t *)&q2);
      }
      else
      {
        TIDL_dataConvertSplitBias((int32_t)bias,
                                  &q1,
                                  (uint8_t *)&q2);
      }
      bias = q1* q2;
    }
    for(i0 =0; i0 < nb ; i0++){
      d1 = d0;
      s1 = s0;
      for (i1 = 0; i1 < nc; i1++)
      {
          d2 = d1;
          s2 = s1;
          for (i2 = 0; i2 < nl; i2++)
          {
              d3 = d2;
              s3 = s2;
              for (i3 = 0; i3 < np; i3++)
              {
                  data = (Tacc) *s3;
                  val = (data * scale + bias );
                  if (typeid(Tacc) == typeid(float32_tidl))
                  {
                      if( typeid(Tdst) != typeid(float32_tidl))
                      {
                        if(val>0)
                        {
                          *d3 = tidl_sat<Tdst>(val+0.5);
                        }
                        else
                        {
                          *d3 = tidl_sat<Tdst>(val-0.5);
                        }
                      }
                      else
                      {
                        *d3 = tidl_sat<Tdst>(val);
                      }
                  }
                  else
                  {
                    *d3 = TIDL_roundSat((int64_t)val, shift, (int32_t)min, (int32_t)max);
                  }
                  s3 += src_pp;
                  d3 += dst_pp;
              }
              d2 += dst_lp;
              s2 += src_lp;
          }
          d1 += dst_cp;
          s1 += src_cp;
      }
    d0 += dst_bp;
    s0 += src_bp;
    }
}

template <typename Tsrc, typename Tdst>
void TIDL_refDataConvertTemp(Tsrc *src, Tdst *dst, int32_t src_offset, int32_t dst_offset,
                         int32_t nb, int32_t nc, int32_t nl, int32_t np,
                         int32_t src_bp, int32_t dst_bp, int32_t src_cp, int32_t dst_cp, int32_t src_lp, int32_t dst_lp, int32_t src_pp, int32_t dst_pp,
                         float in_zf, float out_zf, float in_scale, float out_scale, int32_t shift)
{
  float32_tidl scale, bias;
  int64_t scaleFixed, biasFixed;

  TIDL_dataConvertGetScaleAndBias(in_scale,
                                   out_scale,
                                   in_zf,
                                   out_zf,
                                   shift,
                                   &scale,
                                   &bias,
                                   &scaleFixed,
                                   &biasFixed);

  if ( (typeid(Tsrc) == typeid(float32_tidl) ) ||
        (typeid(Tdst) == typeid(float32_tidl) ))
  {
    TIDL_refDataConvertNew(
      src, dst,  src_offset,  dst_offset,
      nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
      bias,  scale, 0);
  }
  else if (( sizeof(Tsrc) == 2  ) ||
        ( sizeof(Tdst) == 2  ))
  {
    int16_t max = std::numeric_limits<int16_t>::max();
    int16_t min = std::numeric_limits<int16_t>::lowest();
    scaleFixed = TIDL_roundSat((int64_t)scaleFixed, 0, (int32_t)min, (int32_t)max);
    TIDL_refDataConvertNew(
      src, dst,  src_offset,  dst_offset,
      nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
      (int64_t)biasFixed,  (int16_t)scaleFixed, shift);
  }
  else if (( sizeof(Tsrc) == 1  ) ||
        ( sizeof(Tdst) == 1  ))
  {
    int8_t max = std::numeric_limits<int8_t>::max();
    int8_t min = std::numeric_limits<int8_t>::lowest();
    scaleFixed = TIDL_roundSat((int64_t)scaleFixed, 0, (int32_t)min, (int32_t)max);
    TIDL_refDataConvertNew(
      src, dst,  src_offset,  dst_offset,
      nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
      (int32_t)biasFixed,  (int8_t)scaleFixed, shift);
  }
  else
  {
    /* Word and Double word data type, expected to only
    handle Argmax layer where scale is expected to be 1 and bias 0*/
    TIDL_refDataConvertNew(
      src, dst,  src_offset,  dst_offset,
      nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
      (int32_t)0,  (int16_t)1, 0);

  }
}


template <typename Tsrc, typename Tdst>
void TIDL_refDataConvert(Tsrc *src, Tdst *dst, int32_t src_offset, int32_t dst_offset,
                         int32_t nb, int32_t nc, int32_t nl, int32_t np,
                         int32_t src_bp, int32_t dst_bp, int32_t src_cp, int32_t dst_cp, int32_t src_lp, int32_t dst_lp, int32_t src_pp, int32_t dst_pp,
                         float in_zf, float out_zf, float in_scale, float out_scale)
{
    int32_t i0, i1, i2;
    Tdst *d0 = dst + dst_offset, *d1, *d2;
    Tsrc *s0 = src + src_offset, *s1, *s2;
    float data, scale = out_scale / in_scale;

    for (i0 = 0; i0 < nc; i0++)
    {
        d1 = d0;
        s1 = s0;
        for (i1 = 0; i1 < nl; i1++)
        {
            d2 = d1;
            s2 = s1;
            for (i2 = 0; i2 < np; i2++)
            {
                data = *s2;
                *d2 = tidl_sat<Tdst>((data - in_zf) * scale + out_zf);
                s2 += src_pp;
                d2 += dst_pp;
            }
            d1 += dst_lp;
            s1 += src_lp;
        }
        d0 += dst_cp;
        s0 += src_cp;
    }
}


template <typename Tsrc>
void TIDL_refDataConvertVarOutType( Tsrc *src, void *dst, int32_t src_offset, int32_t dst_offset,
                         int32_t nb, int32_t nc, int32_t nl, int32_t np,
                         int32_t src_bp, int32_t dst_bp, int32_t src_cp, int32_t dst_cp, int32_t src_lp, int32_t dst_lp, int32_t src_pp, int32_t dst_pp,
                         float in_zf, float out_zf, float in_scale, float out_scale, int32_t outElemenType, int32_t shift)
{
  if (outElemenType == TIDL_SinglePrecFloat)
  {
    TIDL_refDataConvertTemp(
    src, (float32_tidl *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
  else if (outElemenType == TIDL_SignedChar)
  {
    TIDL_refDataConvertTemp(
    src, (int8_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
  else if (outElemenType == TIDL_SignedShort)
  {
    TIDL_refDataConvertTemp(
    src, (int16_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
   else if (outElemenType == TIDL_SignedWord)
  {
    TIDL_refDataConvertTemp(
    src, (int32_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
  else if (outElemenType == TIDL_UnsignedChar)
  {
    TIDL_refDataConvertTemp(
    src, (uint8_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
  else if (outElemenType == TIDL_UnsignedShort)
  {
    TIDL_refDataConvertTemp(
    src, (uint16_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
  else if (outElemenType == TIDL_UnsignedWord)
  {
    TIDL_refDataConvertTemp(
    src, (uint32_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale, shift);
  }
  else if (outElemenType == TIDL_SignedDoubleWord)
  {
    TIDL_refDataConvert(
    src, (int64_t *)dst,  src_offset,  dst_offset,
    nb, nc,  nl, np, src_bp, dst_bp, src_cp, dst_cp,  src_lp, dst_lp, src_pp, dst_pp,
    in_zf,  out_zf,  in_scale,  out_scale);
  }
  else
  {
    tidl_printf(0," Un-supported Data type in %s %d \n", __FILE__, __LINE__);
  }
}

/**
 * @brief To find float min and max in the tensor
 *
 * @param ptr : pointer to tensor data
 * @param dataPrms : parametes of the data buffer
 * @param min : to store the min value
 * @param max : to store the max value
 */
template <class Tsrc>
void TIDL_TensorMinMaxinFloat(const Tsrc * ptr, const sTIDL_DataParams_t * dataPrms, float in_zf, float in_scale, float *min, float * max)
{
  int32_t padOffset = dataPrms->padW + (dataPrms->padH*dataPrms->pitch[TIDL_LINE_PITCH]);
  int32_t i0, i1, i2, i3;
  float val;
  *min = std::numeric_limits<float>::max();
  *max = -1*std::numeric_limits<float>::max();

  for (i0 = 0; i0 < dataPrms->dimValues[TIDL_DIM_BATCH]; i0++)
  {
    for (i1 = 0; i1 < dataPrms->dimValues[TIDL_DIM_NUMCH]; i1++)
    {
      for (i2 = 0; i2 < dataPrms->dimValues[TIDL_DIM_HEIGHT]; i2++)
      {
        for (i3 = 0; i3 < dataPrms->dimValues[TIDL_DIM_WIDTH]; i3++)
        {
          val = ptr[padOffset + (i0*dataPrms->pitch[TIDL_ROI_PITCH]) + (i1*dataPrms->pitch[TIDL_CHANNEL_PITCH]) + (i2*dataPrms->pitch[TIDL_LINE_PITCH]) + i3];
          val = val - in_zf;
          val = val / in_scale;
          *min = (val < *min) ? val : *min;
          *max = (val > *max) ? val : *max;
        }
      }
    }
  }
}

void TIDL_dataConvertGetScaleAndBias(float32_tidl in_scale,
                                                float32_tidl out_scale,
                                                float32_tidl in_zf,
                                                float32_tidl out_zf,
                                                int32_t      shift,
                                                float32_tidl *scale,
                                                float32_tidl *bias,
                                                int64_t      *scaleFixed,
                                                int64_t      *biasFixed)
{
  float32_tidl accScale;
  *scale =  out_scale / in_scale;
  *bias  =  out_zf - (in_zf * (*scale));

  accScale = (out_scale * (1 << shift));

  *scaleFixed = (int64_t)(accScale / in_scale);
  *biasFixed  = (int64_t)((*bias) * (1 << shift));

  if(*scaleFixed < 1)
  {
    *scaleFixed = 1;
  }
  return;
}

static int32_t TIDL_dataConvertRefProcess(TIDL_Handle          intAlgHandle,
                                                 sTIDL_AlgLayer_t     * algLayer,
                                                 const sTIDL_Layer_t  * tidlLayer,
                                                 void                 * inPtrs[],
                                                 void                 * outPtrs[])
{

  sTIDL_DataParams_t *inDataParams   = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
  const sTIDL_dataConvertParams_t *params = &tidlLayer->layerParams.dataConvertParams;

  int32_t outWidth           = tidlLayer->outData.dimValues[TIDL_DIM_WIDTH];
  int32_t outHeight          = tidlLayer->outData.dimValues[TIDL_DIM_HEIGHT];
  int32_t inChs              = inDataParams->dimValues[TIDL_DIM_NUMCH];
  int32_t inBhs              = inDataParams->dimValues[TIDL_DIM_BATCH];
  int32_t inPitch            = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t outPitch           = (int32_t)tidlLayer->outData.pitch[TIDL_LINE_PITCH];
  int32_t inBhPitch          = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];
  int32_t outBhPitch         = (int32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];
  int32_t inChPitch          = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t outChPitch         = (int32_t)tidlLayer->outData.pitch[TIDL_CHANNEL_PITCH];
  int32_t inPtrOffset        = (inPitch * (inDataParams->padH)) + (inDataParams->padW);
  int32_t outPtrOffset       = (outPitch * tidlLayer->outData.padH) + tidlLayer->outData.padW;
  int32_t status             = IALG_EOK;
  float32_tidl min, max;

  int32_t inElPitch  = 1;
  int32_t outElPitch = 1;
  int32_t inZeroPoint  = 0;
  int32_t outZeroPoint = 0;

  if (params->type == TIDL_DC_TYPE_INPUT)
  {
    inZeroPoint = params->inZeroPoint;
    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if (inDataParams->elementType == TIDL_SinglePrecFloat)
      {
        TIDL_TensorMinMaxinFloat((float32_tidl *)inPtrs[0], inDataParams, 0, 1.0, &min, &max);
        inZeroPoint = 0;
      }
      else if (inDataParams->elementType == TIDL_SignedChar)
      {
        TIDL_TensorMinMaxinFloat((int8_t *)inPtrs[0], inDataParams, params->inZeroPoint, inDataParams->tensorScale, &min, &max);
      }
      else if (inDataParams->elementType == TIDL_UnsignedChar)
      {
        TIDL_TensorMinMaxinFloat((uint8_t *)inPtrs[0], inDataParams, params->inZeroPoint, inDataParams->tensorScale, &min, &max);
      }
      else if (inDataParams->elementType == TIDL_SignedShort)
      {
        TIDL_TensorMinMaxinFloat((int16_t *)inPtrs[0], inDataParams, params->inZeroPoint, inDataParams->tensorScale, &min, &max);
      }
      else if (inDataParams->elementType == TIDL_UnsignedShort)
      {
        TIDL_TensorMinMaxinFloat((uint16_t *)inPtrs[0], inDataParams, params->inZeroPoint, inDataParams->tensorScale, &min, &max);
      }
      else if (inDataParams->elementType == TIDL_SignedWord)
      {
        TIDL_TensorMinMaxinFloat((int32_t *)inPtrs[0], inDataParams, params->inZeroPoint, inDataParams->tensorScale, &min, &max);
      }
      else if (inDataParams->elementType == TIDL_UnsignedWord)
      {
        TIDL_TensorMinMaxinFloat((uint32_t *)inPtrs[0], inDataParams, params->inZeroPoint, inDataParams->tensorScale, &min, &max);
      }
      else
      {
        tidl_printf(0," Un-supported Data type in %s %d \n", __FILE__, __LINE__);
      }

      min *= (1 << TIDL_INTERNAL_INDATA_Q);
      max *= (1 << TIDL_INTERNAL_INDATA_Q);

      if (TIDL_getDatElementSign(tidlLayer->outData.elementType)  == 1)
      {
        TIDL_UpdateScaleFactors(intAlgHandle, algLayer->layerIdx, 1, min, max);
      }
      else
      {
        TIDL_UpdateScaleFactors(intAlgHandle, algLayer->layerIdx, 1, 0, max);
      }
    }
    if (params->layout == TIDL_LT_NHWC)
    {
      inElPitch = inChs;
      inPitch   = inChs*outWidth;
      inChPitch = 1;
    }
  }
  else
  {
    outZeroPoint = params->outZeroPoint;
    if( (params->type == TIDL_DC_TYPE_INTERMEDIATE) || (params->type == TIDL_DC_TYPE_OUTPUT) )
      inZeroPoint  = params->inZeroPoint;

    if(params->layout == TIDL_LT_NHWC)
    {
      outElPitch = inChs;
      outPitch   = inChs*outWidth;
      outChPitch = 1;
    }
  }
  if (inDataParams->elementType == TIDL_SinglePrecFloat)
  {
    inZeroPoint = 0;
    if(intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
    {
      TIDL_refDataConvertVarOutType(
      (float32_tidl *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
      inBhs, inChs, outHeight, outWidth,
      inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
      inZeroPoint, outZeroPoint, 1.0, (1/tidlLayer->outData.tensorScale), tidlLayer->outData.elementType,
      tidlLayer->outData.roundBits);
    }
    else
    {
      TIDL_refDataConvertVarOutType(
      (float32_tidl *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
      inBhs, inChs, outHeight, outWidth,
      inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
      inZeroPoint, outZeroPoint, 1.0, (tidlLayer->outData.tensorScale), tidlLayer->outData.elementType,
      tidlLayer->outData.roundBits);
    }
  }
  else if (inDataParams->elementType == TIDL_SignedChar)
  {
    if(intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
    {
      TIDL_refDataConvertVarOutType(
        (int8_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
      inBhs, inChs, outHeight, outWidth,
      inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
      inZeroPoint, outZeroPoint, (1/inDataParams->tensorScale), (1/tidlLayer->outData.tensorScale), tidlLayer->outData.elementType,
      tidlLayer->outData.roundBits);
    }
    else
    {
      TIDL_refDataConvertVarOutType(
      (int8_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
      inBhs, inChs, outHeight, outWidth,
      inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
      inZeroPoint, outZeroPoint, inDataParams->tensorScale, tidlLayer->outData.tensorScale, tidlLayer->outData.elementType,
      tidlLayer->outData.roundBits);
    }
  }
  else if (inDataParams->elementType == TIDL_SignedShort)
  {
    TIDL_refDataConvertVarOutType(
     (int16_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
    inBhs, inChs, outHeight, outWidth,
    inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
    inZeroPoint, outZeroPoint, inDataParams->tensorScale, tidlLayer->outData.tensorScale, tidlLayer->outData.elementType,
    tidlLayer->outData.roundBits);
  }
  else if (inDataParams->elementType == TIDL_UnsignedChar)
  {
    if(intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
    {
      TIDL_refDataConvertVarOutType(
      (uint8_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
      inBhs, inChs, outHeight, outWidth,
      inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
      inZeroPoint, outZeroPoint, (1/inDataParams->tensorScale), (1/tidlLayer->outData.tensorScale), tidlLayer->outData.elementType,
      tidlLayer->outData.roundBits);
    }
    else
    {
      TIDL_refDataConvertVarOutType(
      (uint8_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
      inBhs, inChs, outHeight, outWidth,
      inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
      inZeroPoint, outZeroPoint, inDataParams->tensorScale, tidlLayer->outData.tensorScale, tidlLayer->outData.elementType,
      tidlLayer->outData.roundBits);      
    }
  }
  else  if (inDataParams->elementType == TIDL_UnsignedShort)
  {
    TIDL_refDataConvertVarOutType(
     (uint16_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
    inBhs, inChs, outHeight, outWidth,
    inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
    inZeroPoint, outZeroPoint, inDataParams->tensorScale, tidlLayer->outData.tensorScale, tidlLayer->outData.elementType,
    tidlLayer->outData.roundBits);
  }
  else  if (inDataParams->elementType == TIDL_UnsignedWord)
  {
    TIDL_refDataConvertVarOutType(
     (uint32_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
    inBhs, inChs, outHeight, outWidth,
    inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
    inZeroPoint, outZeroPoint, inDataParams->tensorScale, tidlLayer->outData.tensorScale, tidlLayer->outData.elementType,
    tidlLayer->outData.roundBits);
  }
  else if (inDataParams->elementType == TIDL_SignedWord)
  {
    TIDL_refDataConvertVarOutType(
     (int32_t *)inPtrs[0], (void*)outPtrs[0], inPtrOffset, outPtrOffset,
    inBhs, inChs, outHeight, outWidth,
    inBhPitch, outBhPitch, inChPitch, outChPitch, inPitch, outPitch, inElPitch, outElPitch,
    inZeroPoint, outZeroPoint, inDataParams->tensorScale, tidlLayer->outData.tensorScale, tidlLayer->outData.elementType,
    tidlLayer->outData.roundBits);
  }
  else
  {
    tidl_printf(0," Un-supported Data type in %s %d \n", __FILE__, __LINE__);
  }
  TIDL_enableL1DandL2CacheWb();
  return status;
}


/**
 ----------------------------------------------------------------------------
 @ingroup    TIDL_dataConvert
 @fn         TIDL_dataConvertProcess
 @brief      Data Convertion Layer process function

 @param      intAlgHandle : tidl algorothm handle
 @param      algLayer : Ptr to alg layer parameter used in crop layer
 @param      tidlLayer: Ptr to tidl layer parameter used in crop layer
 @param      inPtrs: Ptrs to input buffers to be processed
 @param      outPtrs: Ptrs to output buffers to be processed
 @param      sysMems: Ptr to memory related buffers used in crop layer
 @remarks    None
 @return     IALG_EOK   - Successful
             IALG_EFAIL - Unspecified error
 ----------------------------------------------------------------------------
*/
int32_t TIDL_dataConvertProcess(
           TIDL_Handle          intAlgHandle,
           sTIDL_AlgLayer_t     * algLayer,
           const sTIDL_Layer_t  * tidlLayer,
           void                 * inPtrs[],
           void                 * outPtrs[],
           sTIDL_sysMemHandle_t * sysMems)
{
  int32_t status             = IALG_EOK;
  int32_t isTargetExec = 0;
  int32_t isRefExecRequired = 1;

  sTIDL_DataParams_t *inDataParams   = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
  if ((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY)
  {   
    int32_t inBhPitch          = (int32_t)inDataParams->pitch[TIDL_ROI_PITCH];
    int32_t inBhs              = inDataParams->dimValues[TIDL_DIM_BATCH];
    int32_t outBhPitch         = (int32_t)tidlLayer->outData.pitch[TIDL_ROI_PITCH];
    int32_t inElementSize      = TIDL_getDatElementSize(inDataParams->elementType);
    int32_t outElementSize     = TIDL_getDatElementSize(tidlLayer->outData.elementType);

    void *tempInPtrs[1];
    void *tempOutPtrs[1];
    /*Run dataconvert dsp process for every batch */
    tempInPtrs[0] = inPtrs[0];
    tempOutPtrs[0] = outPtrs[0];
    for (int i = 0; i < inBhs; i++)
    { 
      tempInPtrs[0] = (void*)((int8_t*)inPtrs[0] + (i * inBhPitch * inElementSize));
      tempOutPtrs[0] = (void*)((int8_t*)outPtrs[0] + (i * outBhPitch * outElementSize));
      status =  TIDL_dataConvertDspProcess(intAlgHandle, algLayer, tidlLayer, tempInPtrs, tempOutPtrs, sysMems, &isTargetExec);
      if ( isTargetExec == 1 )
      {
        isRefExecRequired = 0;
      } 
    }    
  }

  if ( isRefExecRequired == 1 )
  {
    status = TIDL_dataConvertRefProcess(intAlgHandle, algLayer, tidlLayer, inPtrs, outPtrs);
  }

  return status;
}

