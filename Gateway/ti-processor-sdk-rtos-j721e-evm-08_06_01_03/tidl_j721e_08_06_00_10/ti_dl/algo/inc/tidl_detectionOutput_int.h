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
 @file    tidl_detectionOutput_int.h
 @brief   This file defines some inline functions
          for detection Output layer
 @version 0.1 (Mar 2018) : Initial version [EPR]
 ----------------------------------------------------------------------------
*/

#ifndef ITIDL_DETECTIONOUTPUT_INT_H
#define ITIDL_DETECTIONOUTPUT_INT_H
#include "tidl_alg_int.h"

#define SSD_CONF_DATA_Q (((uint32_t)1U<<15U) - 1)

void TIDL_updateLocConfHeadPtrs(sTIDL_Layer_t * TIDLLayers, sTIDL_AlgLayer_t * algLayer, void * inPtrs[]);
int32_t TIDL_allocInternalMemBuffers(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams, float* priorData, sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX]);
int32_t TIDL_topKSelection(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams, int32_t countM);
void TIDL_topKAllClassesSelection(sTIDL_DetectOutputParams_t *params, sTIDL_ALgDetectOutputParams_t *algDetLyrParams);
template <typename Tloc>
void TIDL_sparseLocDataFetch(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams, sTIDL_AnchorBoxParams_t* anchorBox, int32_t curClass, int32_t countK);
void TIDL_sparseLocDataFetchiX(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams,
                              sTIDL_AnchorBoxParams_t* anchorBox, int32_t curClass, int32_t countK);
int32_t TIDL_boxParamsDecoding(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams, float* priorData, int32_t countK);
int32_t TIDL_applyNMSFast(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams,   int32_t    inCount);

template <typename Tloc>
int32_t TIDL_objOuputPreperation(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams, float* priorData, float* objData, int32_t keepKCnt, int32_t numDet, int32_t cls);

void TIDL_objOuputPreperationiX(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams,
                                  float* priorData, float* objData, int32_t keepKCnt, int32_t numDet, int32_t cls);

int32_t TIDL_findValidLocAndScore(void *pKerPrivArgs,
                              sTIDL_DetectOutputParams_t * params,
                              sTIDL_ALgDetectOutputParams_t * algDetLyrParams,
                              float* priorData,
                              int32_t flowCtrl);

float32_tidl TIDL_jaccardOverlap(
  const BBox *bbox1,
  const BBox *bbox2
  );

template <class Tconf>
int32_t TIDL_findValidLocation_cn(sTIDL_DetectOutputParams_t * params,
                                  sTIDL_ALgDetectOutputParams_t * algDetLyrParams,
                                  float32_tidl                *priorData);


template <class Tconf>
int32_t TIDL_sparseDetScoreCalc_cn(sTIDL_DetectOutputParams_t * params, sTIDL_ALgDetectOutputParams_t * algDetLyrParams);


#define TIDL_SOFTMAX_SCRATCH_BYTES_PER_CLASS (12)

#define TIDL_SIGMOID_SCRATCH_BYTES_PER_CLASS (10)

//static inline float32_tidl expsp(float32_tidl x)
//{
//  return (float32_tidl)exp((float64_tidl)x);
//}

static inline float32_tidl divsp(float32_tidl x, float32_tidl y)
{
  return (x/y);
}

static inline float32_tidl divsp_i(float32_tidl x, float32_tidl y)
{
  float recp_y = __recip(y);

  float TWO  = 2.0f;
  //float Maxe = 3.402823466E+38f;
  float result;

  recp_y = recp_y*(TWO - (y*recp_y));
  recp_y = recp_y*(TWO - (y*recp_y));
  result = x*recp_y;

  //if ((_fabsf(y) > Maxe) && (_fabs(y) <= Maxe)) {
    //result = 0.0f;
  //}

  return result;
}

#endif /* ITIDL_DETECTIONOUTPUT_INT_H*/
