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

#ifndef LUT_MODULE_H_
#define LUT_MODULE_H_ 1

#include "c7x.h"
#include "tidl_types.h"
#include "tidl_alg_int.h"
#include "tidl_commonUtils.h"
#include <cmath>
#define TABLE_SIZE_8BIT 256

static int32_t TIDL_LUTSupportsDatatype(int32_t inputDataType, int32_t outputDataType){

  int32_t doesSupport = 0;
  if((inputDataType==TIDL_SignedChar || inputDataType==TIDL_UnsignedChar) && (outputDataType==TIDL_SignedChar || outputDataType==TIDL_UnsignedChar))
  {
    doesSupport = 1;
  }
  return doesSupport;
  
};

static int32_t TIDL_DeviceSupportsLUT(int32_t targetDeviceName){

  int32_t doesSupport = 0;
  if(targetDeviceName==TIDL_TDA4VM || (targetDeviceName &= (~TIDL_OTF_FLAG_BIT))==TIDL_TDA4AEP)
  {
    doesSupport = 1;
  }
  return doesSupport;
  
};

static int32_t TIDL_LUTSupportsActivation( const sTIDL_Layer_t * tidlLayer){

  int32_t doesSupport = 0;
  if(tidlLayer->actParams.actType == TIDL_Sigmoid || 
  tidlLayer->actParams.actType == TIDL_Tanh || 
  tidlLayer->actParams.actType == TIDL_HardSigmoid || 
  tidlLayer->actParams.actType == TIDL_ELU)
  {
    doesSupport = 1;
  }
  return doesSupport;
  
};

template <class Tin, class Tout>
Tout TIDL_sigmoid_8bit(Tin data, int32_t Zx, float32_tidl Sx, int32_t Zy, float32_tidl Sy, const sTIDL_Layer_t * tidlLayer){

  float inValF = ((float)data - (float)Zx)* (1/Sx);
  float outValF = div_sp(1.0f, (exp_taylor(-inValF) + 1.0f));
  return ((Tout)((outValF*Sy)+Zy));

}
template <class Tin, class Tout>
Tout TIDL_tanh_8bit(Tin data, int32_t Zx, float32_tidl Sx, int32_t Zy, float32_tidl Sy, const sTIDL_Layer_t * tidlLayer){

  float inValF = ((float)data - (float)Zx)* (1/Sx);
  float outValF = std::tanh(inValF); //this should replicate tanh functionality from some open source runtime, should be corrected soon
  //return ((Tout)((outValF*Sy)+Zy));
  int32_t outValInt = round((outValF*Sy)+Zy);
  int32_t omin = std::numeric_limits<Tout>::lowest();
  int32_t omax = std::numeric_limits<Tout>::max();
  outValInt = (outValInt > omax) ? omax : outValInt;
  outValInt = (outValInt < omin) ? omin : outValInt;
  return (Tout)outValInt;

}

#define TIDL_NON_LIN_PARAM_SCALE (int32_t(1<<24))

template <class Tin, class Tout>
Tout TIDL_elu_8bit(Tin data, int32_t Zx, float32_tidl Sx, int32_t Zy, float32_tidl Sy, const sTIDL_Layer_t * tidlLayer){
    
  float32_tidl alpha = (float)tidlLayer->layerParams.batchNormParams.inDataQ/((float)TIDL_NON_LIN_PARAM_SCALE);
  float inValF = ((float)data - (float)Zx)* (1/Sx);
  float outValF = inValF < 0.0 ? (alpha*(std::exp(inValF) - 1)) : inValF;
  int32_t outValInt = round((outValF*Sy)+Zy);
  return ((Tout)(outValInt));

}
template <class Tin, class Tout>
Tout TIDL_hardsigmoid_8bit(Tin data, int32_t Zx, float32_tidl Sx, int32_t Zy, float32_tidl Sy, const sTIDL_Layer_t * tidlLayer){

  float32_tidl alpha = (float)tidlLayer->layerParams.batchNormParams.inDataQ/((float)TIDL_NON_LIN_PARAM_SCALE);
  float32_tidl beta = (float)tidlLayer->layerParams.batchNormParams.weightsQ/((float)TIDL_NON_LIN_PARAM_SCALE);
  float inValF = ((float)data - (float)Zx)* (1/Sx);
  float outValF = alpha*inValF + beta;
  float32_tidl omin = 0;
  float32_tidl omax = 1;
  outValF = (outValF > omax) ? omax : outValF;
  outValF = (outValF < omin) ? omin : outValF;
  int32_t outValInt = round((outValF*Sy)+Zy);
  return (Tout)outValInt;

}
/*----------------------------------------------------------------------------*/
/* Func: TIDL_prepareLUT8bit                                                   */
/*                                                                            */
/* Args: uint8_t (*transformation_ptr)(uint8_t, int32_t, float32_tidl, int32_t, float32_tidl)                                                                 */
/*            - Transformation function pointer to map intput to output       */
/*       uint8_t *LUTdata                                                     */
/*            - Pointer to array to populate the output values into           */
/*       int32_t Zx                                                           */
/*            - Input zero point value                                        */
/*       float32_tidl Sx                                                      */
/*            - Input scale value                                             */
/*       int32_t Zy                                                           */
/*            - Output zero point value                                       */
/*       float32_tidl Sy                                                      */
/*            - Output scale value                                            */

/* Return: None                                                               */
/*                                                                            */
/* Desc: Below function populates the output array based on the 
transformation pointer, and input/output zero points and scales, 
the array is populated for all 8 bit unsigned values                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
template <class Tin, class Tout>
static inline void TIDL_prepareLUT8bit(Tout (*transformation_ptr)(Tin, int32_t, float32_tidl, int32_t, float32_tidl, const sTIDL_Layer_t *), Tout *LUTdata, int32_t Zx, float32_tidl Sx, int32_t Zy, float32_tidl Sy, int32_t readOffsetLUT, const sTIDL_Layer_t * tidlLayer){

  int32_t i;
  int32_t imin = std::numeric_limits<Tin>::lowest();
  int32_t imax = std::numeric_limits<Tin>::max();
  imax++;
  for(i=imin; i<imax; i++){
    LUTdata[i+readOffsetLUT] = (*transformation_ptr)(i, Zx, Sx, Zy, Sy,tidlLayer);
  }
};

template <class Tin, class Tout>
static void TIDL_prepareLUTForNonLinearTransform8bit(Tin *inPtr, Tout *outPtr, const sTIDL_Layer_t * tidlLayer, Tout* LUTdata, sTIDL_DataParams_t *inDataParams, sTIDL_DataParams_t *outDataParams, int32_t * readOffsetLUT, int32_t * isOutputSigned)
{
  Tout (*transformation_ptr)(Tin, int32_t, float32_tidl, int32_t, float32_tidl, const sTIDL_Layer_t * tidlLayer);   
  if(tidlLayer->actParams.actType == TIDL_Sigmoid)
  {
    transformation_ptr = TIDL_sigmoid_8bit<Tin,Tout>;
  }
  else if(tidlLayer->actParams.actType == TIDL_Tanh)
  {
    transformation_ptr = TIDL_tanh_8bit<Tin,Tout>;
  }
  else if(tidlLayer->actParams.actType == TIDL_HardSigmoid)
  {
    transformation_ptr = TIDL_hardsigmoid_8bit<Tin,Tout>;
  }
  else if(tidlLayer->actParams.actType == TIDL_ELU)
  {
    transformation_ptr = TIDL_elu_8bit<Tin,Tout>;
  }

  *readOffsetLUT = 0;
  int32_t imin = std::numeric_limits<Tin>::lowest();
  int32_t omin = std::numeric_limits<Tout>::lowest();
  if(imin<0)
  {
    *readOffsetLUT = -1*imin;
  }
  *isOutputSigned = 0;
  if(omin<0)
  {
    *isOutputSigned = 1;
  }

  TIDL_prepareLUT8bit(transformation_ptr, (Tout*)LUTdata, inDataParams->tensorZeroPoint, inDataParams->tensorScale, outDataParams->tensorZeroPoint, outDataParams->tensorScale, *readOffsetLUT, tidlLayer);
}

#endif /* LUT_MODULE_H_ */

/* ======================================================================== */
/*  End of file:  tidl_lut_module.h                                                  */
/* ======================================================================== */

