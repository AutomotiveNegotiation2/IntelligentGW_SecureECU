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
 *  \file tidl_scatterElements.c
 *
 *  \brief This file defines kernel functions for Batch Norm layer
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "tidl_alg_int.h"
#include "tidl_commonUtils.h"
#include "tidl_scatterElements.h"
#include "math.h"
#include <limits>

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
 * @brief This is main function perform scatterElements on differnt elementTypes
 *
 * @tparam Tin  : template for input
 * @tparam Tw   : template for weights
 * @tparam Tb   : template for Bias
 * @tparam Tout : template for output
 * @tparam Tsat : template for saturate values
 * @param inPtr : Input pointer on which bacthNorm is applied
 * @param outPtr : Output pointer after scatterElements opreation
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

template <class Tin, class Tindx, class Tout>
static int32_t TIDL_refScatterElements(Tin  *data,
                                     Tindx* indices,
                                     Tin  *update,
                                     Tout *outPtr,
                                     TIDL_Handle intAlgHandle,
                                     int32_t layerIdx,
                                     sTIDL_ScatterElementsParams_t *params,
                                     sTIDL_AlgLayer_t *algLayer,
                                     const sTIDL_DataParams_t *inDataParams,
                                     const sTIDL_DataParams_t *inIndicesParams,
                                     const sTIDL_DataParams_t *inUpdateParams,
                                     const sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  int32_t i0, i1, i2, i3;

  int32_t inIndicesNumCols    = (int32_t)inIndicesParams->dimValues[TIDL_DIM_WIDTH];
  int32_t inIndicesNumRows    = (int32_t)inIndicesParams->dimValues[TIDL_DIM_HEIGHT];

  int32_t outNumCols          = (int32_t)outDataParams->dimValues[TIDL_DIM_WIDTH];
  int32_t outNumRows          = (int32_t)outDataParams->dimValues[TIDL_DIM_HEIGHT];
  int32_t outChs              = (int32_t)outDataParams->dimValues[TIDL_DIM_NUMCH];
  int32_t outBatches          = (int32_t)outDataParams->dimValues[TIDL_DIM_BATCH];

  int32_t inDataPitch         = (int32_t)inDataParams->pitch[TIDL_LINE_PITCH];
  int32_t inDataChPitch       = (int32_t)inDataParams->pitch[TIDL_CHANNEL_PITCH];

  int32_t inIndicesPitch      = (int32_t)inIndicesParams->pitch[TIDL_LINE_PITCH];
  int32_t inIndicesChPitch    = (int32_t)inIndicesParams->pitch[TIDL_CHANNEL_PITCH];

  int32_t inUpdatePitch       = (int32_t)inUpdateParams->pitch[TIDL_LINE_PITCH];
  int32_t inUpdateChPitch     = (int32_t)inUpdateParams->pitch[TIDL_CHANNEL_PITCH];

  int32_t outPitch            = (int32_t)outDataParams->pitch[TIDL_LINE_PITCH];
  int32_t outChPitch          = (int32_t)outDataParams->pitch[TIDL_CHANNEL_PITCH];
  int32_t outRoiPitch         = (int32_t)outDataParams->pitch[TIDL_ROI_PITCH];

  data               = (Tin *)data + (inDataParams->padH*inDataPitch) + inDataParams->padW;
  indices            = (Tindx *)indices + (inIndicesParams->padH*inIndicesPitch) + inIndicesParams->padW;
  update             = (Tin *)update + (inUpdateParams->padH*inUpdatePitch) + inUpdateParams->padW;

  Tout *output= (Tout *)outPtr + (outDataParams->padH*outPitch) + outDataParams->padW;

  int32_t numTotRoi = inDataParams->dimValues[TIDL_DIM_BATCH];

  int32_t numInChannels = inDataParams->dimValues[TIDL_DIM_NUMCH];
  int32_t numOutChannels = outDataParams->dimValues[TIDL_DIM_NUMCH];
  int32_t axis = params->axis;

  int32_t index;
  Tin updateVal;

  int32_t isScatterND = (params->axis == -1)?1:0;
  int32_t n, c, h, w, targetIndex;
 
  if(isScatterND)
  {
    for(i0=0;i0<inIndicesNumRows;i0++)
    {
      n = (int32_t)indices[i0*inIndicesNumCols + 0];
      c = (int32_t)indices[i0*inIndicesNumCols + 1];
      h = (int32_t)indices[i0*inIndicesNumCols + 2];
      w = (int32_t)indices[i0*inIndicesNumCols + 3];
      
      if((n >= outBatches) || (c >= outChs) || (h >= outNumRows) || w >= outNumCols)
      {
        tidl_printf(0, "Index out of bounds! skipping the update");
        continue;
      }
      targetIndex = n*outRoiPitch + c*outChPitch + h*outPitch + w;
      output[targetIndex] = (Tout)update[i0];
    }
  }

  else 
  {
    /**
     * First tensor, data : initialization data. NxCxW*H
     * Second tensor, Indices : Location at which update has to happen. NxCxP
     * Third tensor, update : values to be scattered.NxCxP
     * Values are taken from update and placed in data buffer at indices location.
     * Final data buffer is copied into output buffer output of shape NxCxW*H
     * output[index[i][j][k]][j][k] = update[i][j][k]  # if axis == 0
     * output[i][index[i][j][k]][k] = update[i][j][k]  # if axis == 1
     * output[i][j][index[i][j][k]] = update[i][j][k]  # if axis == 2
     */

    for(i0=0; i0<numTotRoi; i0++)
    {
      for(i1=0; i1<numInChannels; i1++)
      {
        for(i2=0; i2<inIndicesNumRows; i2++)
        {
          for(i3=0; i3<inIndicesNumCols; i3++)
          {
            /*indices and updates should be of same dimension*/
            index = (int32_t)indices[i0*inIndicesChPitch*numInChannels + i1*inIndicesChPitch + i2*inIndicesPitch + i3];
            updateVal = update[i0*inUpdateChPitch*numInChannels + i1*inUpdateChPitch + i2*inUpdatePitch + i3];

            if(index >= inDataPitch)
            {
              tidl_printf(0,"something is wrong as index is higher than the allowed \n");
              continue;
            }

            if(index <= 0)
            {
              continue;
            }

            if(axis == 0)
            {
              data[index + i1*inDataChPitch + i2*inDataPitch + i3] = updateVal;
            }
            else if(axis == 1)
            {
              data[i0*inDataChPitch*numOutChannels + index + i2*inDataPitch + i3] = updateVal;
            }
            else if(axis == 2)
            {
              data[i0*inDataChPitch*numOutChannels + i1*inDataChPitch + index + i3] = updateVal;
            }
            else if(axis == 3)
            {
              data[i0*inDataChPitch*numOutChannels + i1*inDataChPitch + i2*inDataPitch + index] = updateVal;
            }
            else
            {
              status = TIDL_ERR_FAILURE;
            }
          }
        }
      }
    }

    /*reshape of data also happens here as in data is assumed to be linear*/
    for(i0=0; i0<numTotRoi; i0++)
    {
      for(i1=0; i1<numOutChannels; i1++)
      {
        for(i2=0; i2<outNumRows; i2++)
        {
          memcpy(output + i0*outChPitch*numOutChannels + i1*outChPitch + i2*outPitch,
                data + i0*outNumCols*outNumRows*numOutChannels + i1*outNumCols*outNumRows + i2*outNumCols,
                outNumCols*sizeof(output[0]));
        }
      }
    }
  }
  return status;
}

 /**
 * @brief scatterElements layer reference implementation
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
static int32_t TIDL_refScatterElementsProcess(TIDL_Handle intAlgHandle,
                                        sTIDL_AlgLayer_t *algLayer,
                                        const sTIDL_Layer_t    *tidlLayer,
                                        sTIDL_ScatterElementsParams_t *params,
                                        void *data,
                                        void *indices,
                                        void *update,
                                        void *outPtr,
                                        const sTIDL_DataParams_t *inDataParams,
                                        const sTIDL_DataParams_t *inIndicesParams,
                                        const sTIDL_DataParams_t *inUpdateParams,
                                        const sTIDL_DataParams_t *outDataParams)
{
  int32_t status = TIDL_SUCCESS;
  int32_t layerIdx = algLayer->layerIdx;

  if(TIDL_SignedChar == ((int32_t)inDataParams->elementType))
  {

    if(TIDL_SignedWord != ((int32_t)inIndicesParams->elementType))
    {
      tidl_printf(0,"Indice data type should int32");
      status = TIDL_ERR_FAILURE;
      return status;
    }
    status = TIDL_refScatterElements((int8_t *)data,
                                    (int32_t *)indices,
                                    (int8_t *)update,
                                    (int8_t *)outPtr,
                                    intAlgHandle,
                                    layerIdx,
                                    params,
                                    algLayer,
                                    inDataParams,
                                    inIndicesParams,
                                    inUpdateParams,
                                    outDataParams);
  }
  else if(TIDL_UnsignedChar == ((int32_t)inDataParams->elementType))
  {

    if(TIDL_SignedWord != ((int32_t)inIndicesParams->elementType))
    {
      tidl_printf(0,"Indice data type should int32");
      status = TIDL_ERR_FAILURE;
      return status;
    }

    status = TIDL_refScatterElements((uint8_t *)data,
                                    (int32_t *)indices,
                                    (uint8_t *)update,
                                    (uint8_t *)outPtr,
                                    intAlgHandle,
                                    layerIdx,
                                    params,
                                    algLayer,
                                    inDataParams,
                                    inIndicesParams,
                                    inUpdateParams,
                                    outDataParams);
  }
  else if(TIDL_SignedShort == ((int32_t)inDataParams->elementType))
  {

    if(TIDL_SignedWord != ((int32_t)inIndicesParams->elementType))
    {
      tidl_printf(0,"Indice data type should int32");
      status = TIDL_ERR_FAILURE;
      return status;
    }

    status = TIDL_refScatterElements((int16_t *)data,
                                    (int32_t *)indices,
                                    (int16_t *)update,
                                    (int16_t *)outPtr,
                                    intAlgHandle,
                                    layerIdx,
                                    params,
                                    algLayer,
                                    inDataParams,
                                    inIndicesParams,
                                    inUpdateParams,
                                    outDataParams);
  }
  else if(TIDL_UnsignedShort == ((int32_t)inDataParams->elementType))
  {

    if(TIDL_SignedWord != ((int32_t)inIndicesParams->elementType))
    {
      tidl_printf(0,"Indice data type should int32");
      status = TIDL_ERR_FAILURE;
      return status;
    }

    status = TIDL_refScatterElements((uint16_t *)data,
                                    (int32_t *)indices,
                                    (uint16_t *)update,
                                    (uint16_t *)outPtr,
                                    intAlgHandle,
                                    layerIdx,
                                    params,
                                    algLayer,
                                    inDataParams,
                                    inIndicesParams,
                                    inUpdateParams,
                                    outDataParams);
  }
  else if(TIDL_SinglePrecFloat == ((int32_t)inDataParams->elementType))
  {
    /*In stat collection , all input tensor is assumed as float.
      hence making indices as float in this flow
    */
    if(TIDL_SinglePrecFloat != ((int32_t)inIndicesParams->elementType))
    {
      tidl_printf(0,"Indice data type should float32");
      status = TIDL_ERR_FAILURE;
      return status;
    }

    status = TIDL_refScatterElements((float32_tidl *)data,
                                    (float32_tidl *)indices,
                                    (float32_tidl *)update,
                                    (float32_tidl *)outPtr,
                                    intAlgHandle,
                                    layerIdx,
                                    params,
                                    algLayer,
                                    inDataParams,
                                    inIndicesParams,
                                    inUpdateParams,
                                    outDataParams);
  }
  else
  {
    status = TIDL_ERR_FAILURE;
  }
  TIDL_enableL1DandL2CacheWb();
  return status;
}
/**
 * @brief ScatterElements layer Process function
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
int32_t TIDL_scatterElementsProcess(TIDL_Handle          intAlgHandle,
                              sTIDL_AlgLayer_t     *algLayer,
                              sTIDL_Layer_t        *tidlLayer,
                              void                 *inPtrs[],
                              void                 *outPtrs[],
                              sTIDL_sysMemHandle_t *sysMems)
{

  int32_t  status      = TIDL_SUCCESS;

  /*It is import tool duty to provide in data in following order
  data    = 0;
  indices = 1;
  update  = 2;
  this order is same as onnx operator
  update is treated as feature, indices are treated as weights. data is treated as initializer.
  */

  int32_t dataIdx    = 0;
  int32_t indicesIdx = 1;
  int32_t voxelIdx   = 2;

  uint8_t  (*data)[]   = (uint8_t (*)[])(inPtrs[dataIdx]);
  uint8_t  (*indices)[]= (uint8_t (*)[])(inPtrs[indicesIdx]);
  uint8_t  (*update)[] = (uint8_t (*)[])(inPtrs[voxelIdx]);

  int8_t   (*outPtr)[]    = (int8_t (*)[])(outPtrs[0]);
  uint32_t flowCtrl = intAlgHandle->createParams->flowCtrl; //  L3

  sTIDL_ScatterElementsParams_t   *params = &tidlLayer->layerParams.scatterElementsParams;
  sTIDL_DataParams_t        *inDataParams;
  sTIDL_DataParams_t        *inIndicesParams;
  sTIDL_DataParams_t        *inUpdateParams;

  inDataParams   = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[0]].outData;
  inIndicesParams= &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[1]].outData;
  inUpdateParams = &intAlgHandle->createParams->net->TIDLLayers[algLayer->inLayerIdx[2]].outData;

  if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) != TIDL_FLOW_CTRL_REF_ONLY)
  {
    status = TIDL_scatterElementsDspProcess(intAlgHandle, algLayer, tidlLayer, inPtrs, outPtrs, sysMems);
  }
  else /* if ((flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY) */
  {
    status = TIDL_refScatterElementsProcess(intAlgHandle,
                                      algLayer,
                                      tidlLayer,
                                      params,
                                      data,
                                      indices,
                                      update,
                                      outPtr,
                                      inDataParams,
                                      inIndicesParams,
                                      inUpdateParams,
                                      &tidlLayer->outData);
  }

  if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    int32_t layerIdx;
    layerIdx = algLayer->layerIdx;

    TIDL_UpdateScaleFactors(intAlgHandle, layerIdx, 0, 0, 1);
  }
  return status;
}

