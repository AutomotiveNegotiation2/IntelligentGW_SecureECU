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

#include "tidl_onnxrt_common.h"

/** Get TIDL element type corresponding to ONNX data type */
int32_t TIDL_ortGetType(int64_t ortType, int32_t * type)
{
  int32_t status = 0;
  if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8)
  {
    *type =  TIDL_UnsignedChar;
  }
  else if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8)
  {
    *type =  TIDL_SignedChar;
  }
  else if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT16)
  {
    *type =  TIDL_UnsignedShort;
  }
  else if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_INT16)
  {
    *type =  TIDL_SignedShort;
  }
  else if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT)
  {
    *type =  TIDL_SinglePrecFloat;
  }
  else if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32)
  {
    *type =  TIDLRT_Int32;
  }
  else if(ortType == ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64)
  {
    *type =  TIDLRT_Int64;
  }
  else
  {
    printf("ERROR : ONNX RT data type : %d not supported by TIDL\n", (int32_t)ortType);
    status = -1;
  }
  return status;
}


/** Set input and output TIDL RT tensor properties and call TIDL RT Invoke */
int32_t TIDL_subgraphRtInvoke(int32_t osrtDebugPrintLevel, OnnxTIDLSubGraphParams * subgraphParams, sTIDL_tidlRtDynamicLoading_t * infer_ops, int32_t isInfer)
{
  TIDL_osrtDebugPrint(osrtDebugPrintLevel, "*******   In TIDL_subgraphRtInvoke  ******** \n");
  int status = 0;
  int j = 0;
  onnxRtParams_t * onnxRtParams = &subgraphParams->onnxRtParams;
  void *handle = subgraphParams->tidlRtParams.rtHandle;
  sTIDLRT_PerfStats_t *stats = (sTIDLRT_PerfStats_t *)subgraphParams->tidlRtParams.stats;

  sTIDLRT_Tensor_t *in[128];
  sTIDLRT_Tensor_t *out[128];
  sTIDLRT_Tensor_t *ins;
  sTIDLRT_Tensor_t *outs;

  ins = (sTIDLRT_Tensor_t *)subgraphParams->tidlRtParams.rtInList;
  outs = (sTIDLRT_Tensor_t *)subgraphParams->tidlRtParams.rtOutList;

  if ((ins == NULL) || (outs == NULL))
  {
    printf("Invoke  : ERROR: Unable to allocate memory for TIDL RT in[] out [] tensor struct\n");
    return -1;
  }
  else
  {
    int32_t currInIdx = 0;
    /* Input tesnsors property set up */
    for (j = 0; j < onnxRtParams->numNetInData; j++)
    {
      in[j] = &(ins[j]);
      status = infer_ops->TIDLRT_setTensorDefault(in[j]);
      in[j]->ptr = onnxRtParams->inputTensorData[j];
      if(infer_ops->TIDLRT_isSharedMem(in[j]->ptr) && isInfer)
      {
        in[j]->memType = TIDLRT_MEM_SHARED;
      }
      strcpy((char *)in[j]->name, (char *)onnxRtParams->inDataNames[j]);
      status |= TIDL_ortGetType(onnxRtParams->inputTensorElementType[j], &in[j]->elementType);
      
      if(status != 0)
      {
        return status;
      }
    }
    /* Output tesnsors property set up */
    for (j = 0; j < onnxRtParams->numNetOutData; j++)
    {
      out[j] = &(outs[j]);
      status = infer_ops->TIDLRT_setTensorDefault(out[j]);
      out[j]->ptr = onnxRtParams->outputTensorData[j];
      if(infer_ops->TIDLRT_isSharedMem(out[j]->ptr) && isInfer)
      {
        out[j]->memType = TIDLRT_MEM_SHARED;
      }
      
      strcpy((char *)out[j]->name, (char *)onnxRtParams->outDataNames[j]);
      status |= TIDL_ortGetType(onnxRtParams->outputTensorElementType[j], &out[j]->elementType);
    
      if(status != 0)
      {
        return status;
      }
    }
  }
  status = infer_ops->TIDLRT_invoke(handle, in, out);

  if(osrtDebugPrintLevel)
  {
    TIDL_printSubgraphStats(stats);
  }
  TIDL_osrtDebugPrint(osrtDebugPrintLevel, "*******  TIDL_subgraphRtInvoke done  ******** \n");
  return status;
}

extern "C"
{
/** Find output shape for a particular ONNX RT output name using TIDL RT Io buf descriptor */ 
std::vector<int64_t> TIDL_getOutputShape(void * ioBufDescVPtr, int8_t onnxName[])
{
  sTIDL_IOBufDesc_t *ioBufDescPtr = (sTIDL_IOBufDesc_t *)ioBufDescVPtr;
  std::vector<int64_t> nchw_shape;

  for(int i = 0; i < ioBufDescPtr->numOutputBuf; i++)
  {
    if(strcmp((char *)ioBufDescPtr->outDataName[i], (char *)onnxName) == 0)
    {
      nchw_shape = { ioBufDescPtr->outNumBatches[i], ioBufDescPtr->outNumChannels[i], ioBufDescPtr->outHeight[i], ioBufDescPtr->outWidth[i]};      
    }
  }
  if(nchw_shape.size() == 0)
  {
    printf("Warning : Couldn't find corresponding ioBuf tensor for onnx tensor with matching name \n");
  }

  return nchw_shape;
}

int32_t TIDLEP_getSubGraphStats(OnnxTIDLSubGraphParams * state_subGraph, char **node_name, void **node_data)
{
  sTIDLRT_PerfStats_t * stats = (sTIDLRT_PerfStats_t*)state_subGraph->tidlRtParams.stats;
  std::vector<uint64_t> *v = new std::vector<uint64_t>();
  v->push_back(uint64_t(stats->cpIn_time_start));
  v->push_back(uint64_t(stats->cpIn_time_end));
  v->push_back(uint64_t(stats->proc_time_start));
  v->push_back(uint64_t(stats->proc_time_end));
  v->push_back(uint64_t(stats->cpOut_time_start));
  v->push_back(uint64_t(stats->cpOut_time_end));
  *node_data = static_cast<void *>(v);
  *node_name = const_cast<char *>(state_subGraph->subGraphName_);
  return 0;
}

} //extern "C"