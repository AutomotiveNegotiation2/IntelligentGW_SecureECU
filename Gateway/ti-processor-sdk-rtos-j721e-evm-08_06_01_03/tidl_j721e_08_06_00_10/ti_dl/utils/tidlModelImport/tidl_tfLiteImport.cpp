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
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>
using namespace std;
using ::google::protobuf::Message;
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>

#include "ti_dl.h"
#include "tidl_import_api.h"
#include "schema_generated.h"
#include "tidl_import_config.h"

using namespace std;
using namespace tflite;


extern "C"
{
  extern std::vector<std::string> diagsInfo;
}

#include "tidl_import_common.h"
#include "tidl_custom_import.h"
#include "tidl_import_common_model_check.h"

#define IS_SIGNED_DATA (1)
#define QUAN_STYLE2_ROUND (0.5)

extern sTIDL_OrgNetwork_t      orgTIDLNetStructure;
extern sTIDL_OrgNetwork_t      tempTIDLNetStructure;
extern sTIDL_Network_t         tIDLNetStructure;

int32_t TIDL_tfliteGetNodeIdx(const Model* tfliteModel, const char *bufName)
{
  int32_t i,j,flag = 0, nameLen, nodeIdx = -1;
  char nodeName[TIDL_MAX_DATA_NAME];
  char inDataName[TIDL_MAX_DATA_NAME];
  auto operator_codes = tfliteModel->operator_codes();
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  //auto metadata_buffer = tfliteModel->metadata_buffer();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();

  for (i = 0; i < operators->size(); i++)
  {
    const auto *op = operators->Get(i);
    for(j = 0; j < op->outputs()->size(); j++)
    {
      const auto *tensor = tensors->Get(op->outputs()->Get(j));
      const auto *op_code = operator_codes->Get(op->opcode_index());
      //printf("Node Name %d - %d- %s- %s - %d \n",i, op->opcode_index(), EnumNamesBuiltinOperator()[ op_code->builtin_code()], tensor->name()->c_str());
      strcpy(nodeName,tensor->name()->c_str());
      strcpy(inDataName, bufName);
      if (strcmp(nodeName, inDataName) == 0)
      {
        nodeIdx = i;
        flag = 1;
        break;
      }
    }
    if(flag)
      break;
  }
  return nodeIdx;
}

template <class Tw>
uint32_t TIDL_tflitekernelReshape(Tw* param, uint32_t w, uint32_t h, uint32_t ci, uint32_t co)
{
  Tw* tPtr = (Tw * )my_malloc(w*h*ci*co*sizeof(Tw));
  int32_t counter = 0;
  for(int l1 = 0; l1 < co; ++l1){
    for(int l = 0; l < ci; ++l){
      int k = l;
      for(int j = 1; j<=w*h; ++j){
        tPtr[counter] = param[l1*w*h*ci + k];
        k+=ci;
        counter++;
      }
    }
  }
  memcpy(param,tPtr,w*h*ci*co*sizeof(Tw));
  free(tPtr);
  return 0;
}

static void readTensor(const flatbuffers::Vector<uint8_t> * data, uint8_t * ptr)
{
  for (int id = 0; id < data->size(); id++)
  {
    ptr[id] = data->Get(id);
  }
}
void TIDL_tfliteDequantTensor(sBuffer_t &buf, sBuffer_t &scaleBuf, sBuffer_t &zpBuf, int32_t size)
{
  int   * src      = (int *)buf.ptr;
  float * dst      = (float *)buf.ptr;
  float * qscale   = (float *)scaleBuf.ptr;
  int * qzero_point = (int *)zpBuf.ptr;

  if((qscale != NULL) && (qzero_point != NULL))
  {
    int co = buf.bufSize / size;
    int numScales = scaleBuf.bufSize;
    for (int i = 0; i < co; i++)
    {
      for (int j = 0; j < size; j++)
      {
        int param = src[i*size+j] - qzero_point[i % numScales];
        dst[i*size + j] = param * qscale[i % numScales];
        if (param == qzero_point[i % numScales])
        {
          dst[i*size + j] = 0;
        }
      }
    }
    my_free(qscale);
    my_free(qzero_point);
  }
}

int32_t TIDL_tfliteCopyInputConstTensor(const Model* tfliteModel, int32_t nIdx, int32_t inIdx, sBuffer_t &buf, sBuffer_t &scaleBuf, sBuffer_t &zpBuf)
{
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(nIdx);
  int tensor_idx = op->inputs()->Get(inIdx);
  const auto *tensor = tensors->Get(tensor_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();


  float * ptr = (float *)malloc(data->size());
  readTensor(data, (uint8_t *) ptr);
  if(tensor->type() == TensorType_FLOAT32)
  {
    buf.bufSize = data->size() / sizeof(float);
    buf.ptr = (float *)my_malloc(buf.bufSize*sizeof(float));
    memcpy(buf.ptr, ptr, buf.bufSize*sizeof(float));
    free(ptr);
    scaleBuf.ptr = NULL;
    zpBuf.ptr = NULL;
    return 0;
  }
  else if (tensor->type() == TensorType_INT32)
  {
    buf.bufSize = data->size() / sizeof(int);
    buf.ptr = (float *)my_malloc(buf.bufSize*sizeof(float));
    memcpy(buf.ptr, ptr, buf.bufSize*sizeof(int));

    auto * quantization = tensor->quantization();
    auto *scale = quantization->scale();

    if (scale)
    {
      scaleBuf.bufSize = scale->size();
      scaleBuf.ptr = (float *)my_malloc(scaleBuf.bufSize*sizeof(float));
      zpBuf.bufSize = scaleBuf.bufSize;
      zpBuf.ptr = (int *)my_malloc(zpBuf.bufSize * sizeof(int));

      float * qscale        = (float *)scaleBuf.ptr;
      int32_t * qzero_point = (int32_t*)zpBuf.ptr;
      for (int i = 0; i < scaleBuf.bufSize; i++)
      {
        qscale[i] = scale->Get(i);
        qzero_point[i] = 0;
      }
    }
    free(ptr);
    return 0;
  }
  else if ((tensor->type() == TensorType_UINT8) || (tensor->type() == TensorType_INT8))
  {
    buf.bufSize = data->size();

    if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
    {
      buf.ptr = (float *)my_malloc(buf.bufSize*sizeof(float));
    }
    else
    {
      buf.ptr = (int8_t *)my_malloc(buf.bufSize*sizeof(int8_t));
    }

    
    if(tensor->type() == TensorType_UINT8)
    {
      if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
      {
        int* dst = (int*)buf.ptr;
        uint8_t * src = (uint8_t *)ptr;
        for (int i = 0; i < buf.bufSize; i++)
        {
          dst[i] = src[i];
        }
      }
      else
      {
        uint8_t * dst = (uint8_t *)buf.ptr;
        uint8_t * src = (uint8_t *)ptr;
        for (int i = 0; i < buf.bufSize; i++)
        {
          dst[i] = src[i];
        }
      }
    }
    else /* (tensor->type() == TensorType_INT8) */
    {
      if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
      {
        int* dst = (int*)buf.ptr;
        int8_t * src = (int8_t *)ptr;
        for (int i = 0; i < buf.bufSize; i++)
        {
          dst[i] = src[i];
        }
      }
      else
      {
        int8_t * dst = (int8_t *)buf.ptr; 
        int8_t * src = (int8_t *)ptr;
        for (int i = 0; i < buf.bufSize; i++)
        {
          dst[i] = src[i];
        }
      }
    }

    free(ptr);

    auto * quantization = tensor->quantization();
    auto *scale = quantization->scale();
    auto *zero_point = quantization->zero_point();

    if (scale && zero_point)
    {
      if(scale->size() != zero_point->size())
      {
        printf(" Size of scale vector and zero_point shall match. It is not matching for Tensor %s \n", tensor->name()->c_str());
        exit(-1);
      }
      scaleBuf.bufSize = scale->size();
      scaleBuf.ptr = (float *)my_malloc(scaleBuf.bufSize*sizeof(float));
      zpBuf.bufSize = zero_point->size();
      zpBuf.ptr = (int *)my_malloc(zpBuf.bufSize*sizeof(int));

      float * qscale        = (float *)scaleBuf.ptr;
      int32_t * qzero_point = (int32_t*)zpBuf.ptr;
      for (int i = 0; i < scaleBuf.bufSize; i++)
      {
        qscale[i] = scale->Get(i);
        qzero_point[i] = zero_point->Get(i);
      }
    }
    else
    {
        printf(" scale vector or zero_point Not found for Tensor %s \n", tensor->name()->c_str());
        exit(-1);
    }
  }
  else
  {
    printf("\nOnly float, DT_INT32 and DT_UNT8 tensor is suported \n");
    return -1;
  }
}

bool isTensorVariable(const Model* tfliteModel,int32_t idx)
{
  int i, j, k, l;
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  char index[1000];
  strcpy(index,tensors->Get(idx)->name()->c_str());

  auto inputs = (*tfliteModel->subgraphs())[0]->inputs();

  /* Check if the input is part of the global inputs */
  for (i = 0; i < inputs->size(); i++)
  {
    char str[1000]={'\0'};
    strcpy(str,tensors->Get(inputs->Get(i))->name()->c_str());
    if(strcmp(index,str)==0)
      return true;
  }

  /* Check if the input is part of one of the networks nodes output*/
  for (i = 0; i < operators->size(); i++)
  {
    const auto *op = operators->Get(i);
    for(j = 0; j < op->outputs()->size(); j++)
    {
      char str[1000]={'\0'};
      strcpy(str,tensors->Get(op->outputs()->Get(j))->name()->c_str());
      if(strcmp(index,str)==0)
        return true;
    }
  }
  return false;
}

void TIDL_tfLiteFillActParams(sTIDL_ActParams_t & actParams, int32_t tfLiteActType)
{
  actParams.actType = TIDL_NoAct;
  if (tfLiteActType == 1)
  {
    actParams.actType = TIDL_RelU;
  }
  if (tfLiteActType == 3)
  {
    actParams.actType = TIDL_RelU6;
  }
}

int32_t TIDL_tfliteMapPlaceHolderParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_DataLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = -1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  return 0;
}

/** Find number of valid inputs of a tensor and populate corresponding indices
 * This function is needed since tflite layers can have some inputs with tensor location -1 rendering them invalid
 * e.g fully connected layer without bias has the bias tensor input with location -1 and hence is not valid
 */ 
int32_t TIDL_tfliteNumValidInputs(const Operator* op, std::vector<int32_t> &validInputIndices)
{
  int32_t numValidInputs = 0;
  validInputIndices = {};
  int32_t tensorIdx = 0;
  while(tensorIdx <  op->inputs()->size() )
  {    
    if(op->inputs()->Get(tensorIdx) != -1)
    {
      validInputIndices.push_back(tensorIdx);
      numValidInputs++;
    }
    tensorIdx++;
  }
  return numValidInputs;
}

/** Function to check a input tensor at idx is a variable one or not*/ 
bool TIDL_isInputVariable(const Model* tfliteModel, int32_t op_index, int32_t idx)
{
  int i, j, k, l;
  char index[1000];
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  const auto* op = operators->Get(op_index);
  int tensor_idx = op->inputs()->Get(idx);
  const auto *tensor = tensors->Get(tensor_idx);
  strcpy(index,tensor->name()->c_str());
  auto inputs = (*tfliteModel->subgraphs())[0]->inputs();

  /* Check if the input is part of the global inputs */
  for (i = 0; i < inputs->size(); i++)
  {
    char str[1000]={'\0'};
    strcpy(str,tensors->Get(inputs->Get(i))->name()->c_str());
    if(strcmp(index,str)==0)
      return true;
  }

  /* Check if the input is part of one of the networks nodes output*/
  for (i = 0; i < operators->size(); i++)
  {
    const auto *op = operators->Get(i);
    for(j = 0; j < op->outputs()->size(); j++)
    {
      char str[1000]={'\0'};
      strcpy(str,tensors->Get(op->outputs()->Get(j))->name()->c_str());
      if(strcmp(index,str)==0)
        return true;
    }
  }
  return false;
}

/** Function to compute number of variable inputs of layer
 * Also populates corresponding indices of variable inputs
 * Checks for variable tensors among the valid tensors if valid tensors list provided, else checks all tensors
 */ 
int32_t TIDL_tfliteNumVariableLayerInputs(const Model* tfliteModel,int32_t i, std::vector<int32_t> &varIdx, const std::vector<int32_t> validInputIndices = {})
{
  int32_t numVarInputs = 0;
  int32_t numInputs = 0;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  const auto* op = operators->Get(i);
  int tensor_idx = op->inputs()->Get(1);
  if(! validInputIndices.empty())
  {
    for(int j = 0; j < validInputIndices.size(); j++)
    {
      if(TIDL_isInputVariable(tfliteModel,i, j))
      {
        numVarInputs++;
        varIdx.push_back(validInputIndices[j]);
      }
    }
  }
  else  // default argument {} passed for validInputIndices. In this case, iterate over all node inputs
  {
    for(int j = 0; j < op->inputs()->size(); j++)
    {
      if(TIDL_isInputVariable(tfliteModel,i,j))
      {
        numVarInputs++;
        varIdx.push_back(j);
      }
    }
  }
  return numVarInputs;
}


/** Function to save layer level tensor properties metadata to be used for allowlisting 
 * Saves data for sTIDL_allowlistingMetaData structure
 */
void TIDL_tfliteSaveAllowlistingMetaData(const Model* tfliteModel, int32_t i, sTIDL_LayerPC_t &layer)
{
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensor = tensors->Get(i);
  const auto* op = operators->Get(i);
  layer.allowlistingMetaData.numInputs = op->inputs()->size();
  layer.allowlistingMetaData.numValidInputs = TIDL_tfliteNumValidInputs(op, layer.allowlistingMetaData.validInputIndices);
  layer.allowlistingMetaData.numVarInputs = TIDL_tfliteNumVariableLayerInputs(tfliteModel,i, layer.allowlistingMetaData.varTensorIndices, layer.allowlistingMetaData.validInputIndices);
  layer.allowlistingMetaData.numConstInputs = layer.allowlistingMetaData.numValidInputs - layer.allowlistingMetaData.numVarInputs;
  
  //Find indices of constant tensors -- indices which are not variable are const
  for(int j = 0; j < layer.allowlistingMetaData.validInputIndices.size(); j++)
  {
    if(std::find(layer.allowlistingMetaData.varTensorIndices.begin(), layer.allowlistingMetaData.varTensorIndices.end(), layer.allowlistingMetaData.validInputIndices[j])
         == layer.allowlistingMetaData.varTensorIndices.end()) //idx not found in variable tensors indices => constant tensor idx
    {
      layer.allowlistingMetaData.constTensorIndices.push_back(layer.allowlistingMetaData.validInputIndices[j]);
    }
  }

  //save dimensions of variable and constant tensors
  for(auto& varIdx : layer.allowlistingMetaData.varTensorIndices)
  {
    auto *var_tensor_shape = tensors->Get(op->inputs()->Get(varIdx))->shape();
    std::vector<int32_t> tensorDim;
    for(int i = 0; i < var_tensor_shape->size(); i++)
    {
      tensorDim.push_back(var_tensor_shape->Get(i));
    }
    layer.allowlistingMetaData.varTensorsDims.push_back(tensorDim);
  }
  for(auto& constIdx : layer.allowlistingMetaData.constTensorIndices)
  {
    auto *const_tensor_shape = tensors->Get(op->inputs()->Get(constIdx))->shape();
    std::vector<int32_t> tensorDim;
    for(int i = 0; i < const_tensor_shape->size(); i++)
    {
      tensorDim.push_back(const_tensor_shape->Get(i));
    }
    layer.allowlistingMetaData.constTensorsDims.push_back(tensorDim);
  }
  
  auto *out_tensor_shape = tensors->Get(op->outputs()->Get(0))->shape();
  std::vector<int32_t> tensorDim;
  for(int i = 0; i < out_tensor_shape->size(); i++)
  {
    tensorDim.push_back(out_tensor_shape->Get(i));
  }
  layer.allowlistingMetaData.outputTensorDims.push_back(tensorDim);

  //convert NHWC to NCHW dimensions for compatibility with ONNX RT checks
  for(int i = 0; i < layer.allowlistingMetaData.varTensorsDims.size(); i++)
  {
    if(layer.allowlistingMetaData.varTensorsDims[i].size() == 4)
    {
      std::vector<int32_t> tempDims = layer.allowlistingMetaData.varTensorsDims[i];
      layer.allowlistingMetaData.varTensorsDims[i][TIDL_DIM_HEIGHT] = tempDims[1];
      layer.allowlistingMetaData.varTensorsDims[i][TIDL_DIM_WIDTH] = tempDims[2];
      layer.allowlistingMetaData.varTensorsDims[i][TIDL_DIM_NUMCH] = tempDims[3];
    }
  }
  for(int i = 0; i < layer.allowlistingMetaData.constTensorsDims.size(); i++)
  {
    if(layer.allowlistingMetaData.constTensorsDims[i].size() == 4)
    {
      std::vector<int32_t> tempDims = layer.allowlistingMetaData.constTensorsDims[i];
      layer.allowlistingMetaData.constTensorsDims[i][TIDL_DIM_HEIGHT] = tempDims[1];
      layer.allowlistingMetaData.constTensorsDims[i][TIDL_DIM_WIDTH] = tempDims[2];
      layer.allowlistingMetaData.constTensorsDims[i][TIDL_DIM_NUMCH] = tempDims[3];
    }
  }
  for(int i = 0; i < layer.allowlistingMetaData.outputTensorDims.size(); i++)
  {
    if(layer.allowlistingMetaData.outputTensorDims[i].size() == 4)
    {
      std::vector<int32_t> tempDims = layer.allowlistingMetaData.outputTensorDims[i];
      layer.allowlistingMetaData.outputTensorDims[i][TIDL_DIM_HEIGHT] = tempDims[1];
      layer.allowlistingMetaData.outputTensorDims[i][TIDL_DIM_WIDTH] = tempDims[2];
      layer.allowlistingMetaData.outputTensorDims[i][TIDL_DIM_NUMCH] = tempDims[3];
    }
  }
}

/** Broadcast vector buffer to have a modified dimension for StandAlone mode*/
void TIDL_broadcastFloatTensorSA(sBuffer_t &buf, int32_t bufSize)
{
  float * ptr = (float *)buf.ptr;
  float val = ptr[0]; //only one const val for computation
  void * newPtr = realloc(ptr, bufSize * sizeof(float)); //ptr is void* so it should be reallocated to a void * ptr
  float *newPtrCast = (float *)newPtr;
  for(int i = 0; i < bufSize; i++)
  {
    newPtrCast[i] = val;  //broadcast the constant along number of channels
  }
  buf.ptr = newPtr;
  buf.bufSize = bufSize;
}

int32_t TIDL_tfliteMapQuantizeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  sTIDL_LayerPC_t &TIDLPCLayer       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayer.layerType = TIDL_DataConvertLayer;
  TIDLPCLayer.layerParams.dataConvertParams.type = TIDL_DC_TYPE_INTERMEDIATE;

  /*TODO: check for any other case.Assuming quantization supports only 1 input and 1 output*/ 
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  const auto *inTensor = tensors->Get(op->inputs()->Get(0));
  const auto *opTensor = tensors->Get(op->outputs()->Get(0));
  if (inTensor->quantization() != NULL || inTensor->type() != TensorType_FLOAT32)
  {
    auto *in_zero_point = inTensor->quantization()->zero_point();
    TIDLPCLayer.layerParams.dataConvertParams.inZeroPoint = in_zero_point->Get(0);  
  }
  else
  {   
    TIDLPCLayer.layerParams.dataConvertParams.inZeroPoint = 0;  
  }  
  auto *op_zero_point = opTensor->quantization()->zero_point();
  TIDLPCLayer.layerParams.dataConvertParams.outZeroPoint = op_zero_point->Get(0);
  return 0;
}


int32_t TIDL_tfliteMapDeQuantizeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  sTIDL_LayerPC_t &TIDLPCLayer       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  auto *inTensor = tensors->Get(op->inputs()->Get(0));
  auto *outTensor = tensors->Get(op->outputs()->Get(0));
  /* Only map to dataConvert if it layer is from uint8/int8 -> float*/
  //TODO:Figure out the condition to switch between the identity and data convert
  if (((inTensor->type() == TensorType_UINT8) || (inTensor->type() == TensorType_INT8)) && ((outTensor->type() == TensorType_FLOAT32)))
  { 
    TIDLPCLayer.layerType = TIDL_DataConvertLayer;
    TIDLPCLayer.layerParams.dataConvertParams.type = TIDL_DC_TYPE_OUTPUT;
    TIDLPCLayer.outData[0].elementType = TIDL_SinglePrecFloat;
    TIDLPCLayer.outData[0].tensorScale = 1;
    /*TODO: check for any other case.Assuming dequantization supports only 1 input and 1 output*/ 
    if (inTensor->quantization() != NULL )
    {
      auto *in_zero_point = inTensor->quantization()->zero_point();
      TIDLPCLayer.layerParams.dataConvertParams.inZeroPoint = in_zero_point->Get(0);  
    }
    else
    {
      TIDLPCLayer.layerParams.dataConvertParams.inZeroPoint = 0;  
    }
    // output always will be float
    TIDLPCLayer.layerParams.dataConvertParams.outZeroPoint = 0;  
    return 0;
  }
  
  TIDLPCLayer.layerType = TIDL_DequantizeLayer;
  TIDLPCLayer.layerPCParams.dequantParams.scale = 0.1;
  TIDLPCLayer.layerPCParams.dequantParams.zeroPoint = 0.0;

  if (((inTensor->type() == TensorType_UINT8) || (inTensor->type() == TensorType_INT8)) && (gParams.addDataConvertToNet))
  {
    if(inTensor->quantization() != NULL)
    {
        auto * scale = inTensor->quantization()->scale();
        auto *zero_point = inTensor->quantization()->zero_point();
        if (scale && zero_point)
        {
          TIDLPCLayer.layerPCParams.dequantParams.scale     = scale->Get(0);
          TIDLPCLayer.layerPCParams.dequantParams.zeroPoint = zero_point->Get(0);
        }
    }
  }
  return 0;
}

int32_t TIDL_tfliteMapConvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status;
  int32_t padType;
  int32_t idx1, idx2;
  sTIDL_LayerPC_t &TIDLPCLayers       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  sTIDL_ConvParams_t &convParams      = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams;

  TIDLPCLayers.layerType = TIDL_ConvolutionLayer;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  TIDLPCLayers.outData[0].elementType = tidl_getElementType(1);

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int kernel_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(kernel_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  convParams.numInChannels   = shape->Get(3);
  convParams.numOutChannels  = shape->Get(0);
  convParams.kernelW         = shape->Get(2);
  convParams.kernelH         = shape->Get(1);

  convParams.numGroups       = 1;
  convParams.dilationW       = 1;
  convParams.dilationH       = 1;
  convParams.strideW         = 1;
  convParams.strideH         = 1;
  convParams.padW            = 0;
  convParams.padH            = 0;
  convParams.padL            = -1;
  convParams.padR            = -1;
  convParams.padT            = -1;
  convParams.padB            = -1;
  convParams.enableBias      = 0;
  convParams.enablePooling   = 0;
  // TIDL_getAttr_data_format(tfGraphDef.node(i), "data_format");
  // if (gloab_data_format == 1)
  // {
  //   idx1 = 3;
  //   idx2 = 2;
  // }
  // else
  // {
  //   idx1 = 2;
  //   idx2 = 1;
  // }
  // TIDL_getAttr_value(tfGraphDef.node(i), "strides", &convParams.strideW, idx1);
  // TIDL_getAttr_value(tfGraphDef.node(i), "strides", &convParams.strideH, idx2);
  // TIDL_getAttr_value(tfGraphDef.node(i), "dilation_rate", &convParams.dilationW, idx1);
  // TIDL_getAttr_value(tfGraphDef.node(i), "dilation_rate", &convParams.dilationH, idx2);

  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  auto *Conv2DParams = op->builtin_options_as_Conv2DOptions();
  convParams.strideW = Conv2DParams->stride_w();
  convParams.strideH = Conv2DParams->stride_h();
  convParams.dilationW = Conv2DParams->dilation_w_factor();
  convParams.dilationH = Conv2DParams->dilation_h_factor();

  TIDL_tfLiteFillActParams(TIDLPCLayers.actParams,  Conv2DParams->fused_activation_function());
  // TIDL_getAttr_padding(tfGraphDef.node(i), "padding", &padType);
  padType = Conv2DParams->padding();
  TIDLPCLayers.strideOffsetMethod = TIDL_StrideOffsetCenter;
  if (padType == TF_PAD_SAME)   /* SAME : Padding done to input */
  {
    convParams.padW = ((convParams.kernelW - 1)*convParams.dilationW) / 2;
    convParams.padH = ((convParams.kernelH - 1)*convParams.dilationH) / 2;
  }
  else if (padType == TF_PAD_VALID)  /* VALID : No padding to input */
  {
    TIDLPCLayers.strideOffsetMethod = TIDL_StrideOffsetTopLeft;
    convParams.padL            = 0;
    convParams.padR            = 0;
    convParams.padT            = 0;
    convParams.padB            = 0;
  }
  if (tflite::BuiltinOperator_CONV_2D == operator_codes)
  {
    TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 1, TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints);
    
    if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
    {
      TIDL_tflitekernelReshape((float *)TIDLPCLayers.weights.ptr, convParams.kernelW, convParams.kernelH, convParams.numInChannels, convParams.numOutChannels);
      TIDL_tfliteDequantTensor(TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints, convParams.kernelW * convParams.kernelH * convParams.numInChannels);
    }
    else
    {
      TIDL_tflitekernelReshape((int8_t *)TIDLPCLayers.weights.ptr, convParams.kernelW, convParams.kernelH, convParams.numInChannels, convParams.numOutChannels);
    }

    if (op->inputs()->size() == 3)
    {
      TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 2, TIDLPCLayers.bias, TIDLPCLayers.biasScales, TIDLPCLayers.biasZeroPoints);
      if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
      {
        TIDL_tfliteDequantTensor(TIDLPCLayers.bias, TIDLPCLayers.biasScales,  TIDLPCLayers.biasZeroPoints, 1);
      }
      convParams.enableBias = 1;
    }
  }
  return 0;
}

int32_t TIDL_tfliteMapDeConvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status;
  int32_t padType;
  int32_t idx1, idx2;
  sTIDL_LayerPC_t &TIDLPCLayers       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  sTIDL_ConvParams_t &convParams      = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams;

  TIDLPCLayers.layerType = TIDL_Deconv2DLayer;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  TIDLPCLayers.outData[0].elementType = tidl_getElementType(1);

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int kernel_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(kernel_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  convParams.numInChannels   = shape->Get(3);
  convParams.numOutChannels  = shape->Get(0);
  convParams.kernelW         = shape->Get(2);
  convParams.kernelH         = shape->Get(1);

  convParams.numGroups       = 1;
  convParams.dilationW       = 1;
  convParams.dilationH       = 1;
  convParams.strideW         = 1;
  convParams.strideH         = 1;
  convParams.padW            = 0;
  convParams.padH            = 0;
  convParams.enableBias      = 0;
  convParams.enablePooling   = 0;

  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  auto *Conv2DParams = op->builtin_options_as_TransposeConvOptions();
  convParams.strideW = Conv2DParams->stride_w();
  convParams.strideH = Conv2DParams->stride_h();

  padType = Conv2DParams->padding();
  TIDLPCLayers.strideOffsetMethod = TIDL_StrideOffsetCenter;
  if (padType == TF_PAD_SAME)   /* SAME : Padding done to input */
  {
    convParams.padW = ((convParams.kernelW - 1)*convParams.dilationW) / 2;
    convParams.padH = ((convParams.kernelH - 1)*convParams.dilationH) / 2;
  }
  else if (padType == TF_PAD_VALID)  /* VALID : No padding to input */
  {
    TIDLPCLayers.strideOffsetMethod = TIDL_StrideOffsetTopLeft;
  }
  sBuffer_t scale;
  sBuffer_t zero_point;
  TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 1, TIDLPCLayers.weights, scale, zero_point);
  if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
  {
    TIDL_tflitekernelReshape((float *)TIDLPCLayers.weights.ptr, convParams.kernelW, convParams.kernelH, convParams.numInChannels, convParams.numOutChannels);
    TIDL_tfliteDequantTensor(TIDLPCLayers.weights, scale, zero_point, convParams.kernelW * convParams.kernelH * convParams.numInChannels);
  }
  else
  {
    TIDL_tflitekernelReshape((int8_t *)TIDLPCLayers.weights.ptr, convParams.kernelW, convParams.kernelH, convParams.numInChannels, convParams.numOutChannels); //MMAv2 tf-2.0 pre quant assumption
  }
  const auto *shape_tensor = tensors->Get(op->inputs()->Get(0));
  auto *shape_data   = (*tfliteModel->buffers())[shape_tensor->buffer()]->data();
  int32_t * ptr = (int32_t *)malloc(shape_data->size());
  readTensor(shape_data, (uint8_t *) ptr);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[TIDL_DIM_HEIGHT] = -ptr[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[TIDL_DIM_WIDTH]  = -ptr[2];
  free(ptr);


  return 0;
}



int32_t TIDL_tfliteMapLeakyRluParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_LeakyReluLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].elementType = tidl_getElementType(1);
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  auto *LeakyReluOptions = op->builtin_options_as_LeakyReluOptions();
  TIDLPCLayers.layerPCParams.leakyReluParams.alpha = LeakyReluOptions->alpha();
  return 0;
}

int32_t TIDL_tfliteMapDWConvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status;
  int32_t padType;
  int32_t idx1, idx2;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  sTIDL_ConvParams_t &convParams = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams;
  int32_t depth_multiplier;

  TIDLPCLayers.layerType = TIDL_ConvolutionLayer;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  TIDLPCLayers.outData[0].elementType = tidl_getElementType(1);

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int kernel_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(kernel_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  convParams.numOutChannels  = shape->Get(3);
  convParams.kernelW         = shape->Get(2);
  convParams.kernelH         = shape->Get(1);

  convParams.numGroups       = 1;
  convParams.dilationW       = 1;
  convParams.dilationH       = 1;
  convParams.strideW         = 1;
  convParams.strideH         = 1;
  convParams.padW            = 0;
  convParams.padH            = 0;
  convParams.padL            = -1;
  convParams.padR            = -1;
  convParams.padT            = -1;
  convParams.padB            = -1;
  convParams.enableBias      = 0;
  convParams.enablePooling   = 0;
  // TIDL_getAttr_data_format(tfGraphDef.node(i), "data_format");
  // if (gloab_data_format == 1)
  // {
  //   idx1 = 3;
  //   idx2 = 2;
  // }
  // else
  // {
  //   idx1 = 2;
  //   idx2 = 1;
  // }
  // TIDL_getAttr_value(tfGraphDef.node(i), "strides", &convParams.strideW, idx1);
  // TIDL_getAttr_value(tfGraphDef.node(i), "strides", &convParams.strideH, idx2);
  // TIDL_getAttr_value(tfGraphDef.node(i), "dilation_rate", &convParams.dilationW, idx1);
  // TIDL_getAttr_value(tfGraphDef.node(i), "dilation_rate", &convParams.dilationH, idx2);

  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  auto *DWConv2DParams = op->builtin_options_as_DepthwiseConv2DOptions();
  convParams.strideW = DWConv2DParams->stride_w();
  convParams.strideH = DWConv2DParams->stride_h();
  convParams.dilationW = DWConv2DParams->dilation_w_factor();
  convParams.dilationH = DWConv2DParams->dilation_h_factor();
  depth_multiplier = DWConv2DParams->depth_multiplier();
  TIDL_tfLiteFillActParams(TIDLPCLayers.actParams,  DWConv2DParams->fused_activation_function());
  // TIDL_getAttr_padding(tfGraphDef.node(i), "padding", &padType);
  padType = DWConv2DParams->padding();
  TIDLPCLayers.strideOffsetMethod = TIDL_StrideOffsetCenter;
  if (padType == TF_PAD_SAME)   /* SAME : Padding done to input */
  {
    convParams.padW = ((convParams.kernelW - 1)*convParams.dilationW) / 2;
    convParams.padH = ((convParams.kernelH - 1)*convParams.dilationH) / 2;
  }
  else if (padType == TF_PAD_VALID)  /* VALID : No padding to input */
  {
    TIDLPCLayers.strideOffsetMethod = TIDL_StrideOffsetTopLeft;
    convParams.padL            = 0;
    convParams.padR            = 0;
    convParams.padT            = 0;
    convParams.padB            = 0;
  }

  convParams.numInChannels = (convParams.numOutChannels / depth_multiplier);
  convParams.numGroups      = convParams.numInChannels;

  TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 1, TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints);
  if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
  {
    TIDL_tflitekernelReshape((float *)TIDLPCLayers.weights.ptr, convParams.kernelW, convParams.kernelH,
    convParams.numOutChannels, convParams.numInChannels/ convParams.numGroups );
    TIDL_tfliteDequantTensor(TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints, convParams.kernelW * convParams.kernelH * (convParams.numInChannels/convParams.numGroups));
  }
  else
  {
    TIDL_tflitekernelReshape((int8_t *)TIDLPCLayers.weights.ptr, convParams.kernelW, convParams.kernelH,
     convParams.numOutChannels, convParams.numInChannels/ convParams.numGroups );
  }

  if(op->inputs()->size()==3)
  {
    TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 2, TIDLPCLayers.bias, TIDLPCLayers.biasScales, TIDLPCLayers.biasZeroPoints);
    if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
    {
      TIDL_tfliteDequantTensor(TIDLPCLayers.bias, TIDLPCLayers.biasScales, TIDLPCLayers.biasZeroPoints, 1);
    }
    convParams.enableBias = 1;
  }
  return 0;
}

int32_t TIDL_tfliteMapAddParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status = 0;
  sTIDL_LayerPC_t &TIDLPCLayer = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDL_tfliteSaveAllowlistingMetaData(tfliteModel,i,TIDLPCLayer);
  status = TIDL_checkAddMulSubDivTensorProperties(TIDLPCLayer, BASE_OP_ADD);
  if(status == -1) return -1;
  sTIDL_allowlistingMetaData md = TIDLPCLayer.allowlistingMetaData;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  const auto* op = operators->Get(i);
  auto *AddParams = op->builtin_options_as_AddOptions();
  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  int32_t is1DConstTensor = checkDimConstTensor (md);
  if(md.numConstInputs > 0) //addition with constant tensor
  {
    int constTensorIdx = md.constTensorIndices[0];
    int tensor_idx = op->inputs()->Get(constTensorIdx);
    const auto *tensor = tensors->Get(tensor_idx);
    auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
    auto *shape = tensor->shape();
    sBuffer_t scale,zero_point;
    if (is1DConstTensor == 1)
    {
      TIDLPCLayer.layerType = TIDL_BatchNormLayer;
      TIDLPCLayer.outData[0].elementType = tidl_getElementType(1);
      TIDL_tfLiteFillActParams(TIDLPCLayer.actParams,  AddParams->fused_activation_function());
      status = TIDL_tfliteCopyInputConstTensor(tfliteModel, i, constTensorIdx, TIDLPCLayer.bias, scale, zero_point);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read constant tensor : Only float, int32, uint8 and int8 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
        return -1;
      }
      if(shape->size() == 0) { //tensor dim size = 0 --- Add constant to layer

        int32_t biasSize = md.varTensorsDims[0][TIDL_DIM_NUMCH]; //broadcast the constant along number of channels
        TIDL_broadcastFloatTensorSA(TIDLPCLayer.bias, biasSize);  //already dequantized tensor, so float      
      }
      else
      { //addition with constant vector

      }
      if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
      {
        TIDL_tfliteDequantTensor(TIDLPCLayer.bias, scale, zero_point, 1);
      }
      TIDLPCLayer.outData->dataId = (*dataIndex)++;
      TIDLPCLayer.weights.ptr             = my_malloc(TIDLPCLayer.bias.bufSize*sizeof(float));
      TIDLPCLayer.weights.bufSize         = TIDLPCLayer.bias.bufSize;
      float *ptr = (float *)TIDLPCLayer.weights.ptr;
      for (int lc = 0; lc < TIDLPCLayer.weights.bufSize; lc++)
        ptr[lc] = 1.0;
      return 0;    
    }
    else
    {
      sTIDL_EltWiseParams_t &addParams = TIDLPCLayer.layerParams.eltWiseParams;
      TIDLPCLayer.layerType = TIDL_EltWiseLayer;
      TIDLPCLayer.outData[0].dataId = (*dataIndex)++;
      TIDLPCLayer.outData[0].elementType = tidl_getElementType(1);
      addParams.eltWiseType = TIDL_EltWiseSum;
      TIDLPCLayer.numInBufs = op->inputs()->size();
      TIDL_tfLiteFillActParams(TIDLPCLayer.actParams,  AddParams->fused_activation_function());

      status = TIDL_tfliteCopyInputConstTensor(tfliteModel, i, constTensorIdx, TIDLPCLayer.weights, TIDLPCLayer.weightScales, TIDLPCLayer.weightZeroPoints);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read constant tensor : Only float, int32, uint8 and int8 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
        return -1;
      }
      return 0;      
    }
  }
  else
  { //both inputs variable
    sTIDL_EltWiseParams_t &addParams = TIDLPCLayer.layerParams.eltWiseParams;
    TIDLPCLayer.layerType = TIDL_EltWiseLayer;
    TIDLPCLayer.outData[0].dataId = (*dataIndex)++;
    TIDLPCLayer.outData[0].elementType = tidl_getElementType(1);
    addParams.eltWiseType = TIDL_EltWiseSum;
    TIDLPCLayer.numInBufs = op->inputs()->size();
    TIDL_tfLiteFillActParams(TIDLPCLayer.actParams,  AddParams->fused_activation_function());
    return 0;
  }
}

int32_t TIDL_tfliteMapSubParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status = 0;
  sTIDL_LayerPC_t &TIDLPCLayer = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDL_tfliteSaveAllowlistingMetaData(tfliteModel,i,TIDLPCLayer);
  sTIDL_allowlistingMetaData md = TIDLPCLayer.allowlistingMetaData;
  int constTensorIdx = md.constTensorIndices[0];
  status = TIDL_checkAddMulSubDivTensorProperties(TIDLPCLayer, BASE_OP_SUB);
  if(status == -1) return -1;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  const auto* op = operators->Get(i);
  int tensor_idx = op->inputs()->Get(constTensorIdx);
  const auto *tensor = tensors->Get(tensor_idx);
  auto *shape = tensor->shape();
  sBuffer_t scale,zero_point;
  if(md.numConstInputs > 0) 
  {
    TIDLPCLayer.layerType = TIDL_BatchNormLayer;
    status = TIDL_tfliteCopyInputConstTensor(tfliteModel, i, constTensorIdx, TIDLPCLayer.bias, scale, zero_point);
    if(status == -1)
    {
      diagsInfo.push_back("Cannot read constant tensor : Only float, int32, uint8 and int8 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
      return -1;
    }
    if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
    {
      TIDL_tfliteDequantTensor(TIDLPCLayer.bias, scale, zero_point, 1);
    }
    if(shape->size()==0)//subtraction with constant 
    {
      int32_t biasSize = md.varTensorsDims[0][TIDL_DIM_NUMCH]; //broadcast the constant along number of channels
      TIDL_broadcastFloatTensorSA(TIDLPCLayer.bias, biasSize);
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData->dataId = (*dataIndex)++;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.ptr             = my_malloc(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.bufSize*sizeof(float));
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.bufSize         = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.bufSize;
    float *ptr = (float *)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.ptr;  
    /* case: const - X */
    if(md.constTensorIndices[0]  < md.varTensorIndices[0] )
    {
      for (int lc = 0; lc < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.bufSize; lc++)
        ptr[lc] = -1.0;          
    }
    /* case: X - const */
    else
    {
      /* scaling bias with: -1 */
      float *biasPtr = (float *)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.ptr;
      for (int lc = 0; lc < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.bufSize; lc++)
        biasPtr[lc] = -1.0*biasPtr[lc];

      for (int lc = 0; lc < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.bufSize; lc++)
        ptr[lc] = 1.0; 
    }
  }
  return 0;
}
int32_t TIDL_tfliteMapMulParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status = 0;
  sTIDL_LayerPC_t &TIDLPCLayer = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDL_tfliteSaveAllowlistingMetaData(tfliteModel,i,TIDLPCLayer);
  sTIDL_allowlistingMetaData md = TIDLPCLayer.allowlistingMetaData;
  status = TIDL_checkAddMulSubDivTensorProperties(TIDLPCLayer, BASE_OP_MUL);
  if(status == -1) return -1;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  const auto* op = operators->Get(i);
  sBuffer_t scale,zero_point;
  int32_t is1DConstTensor = checkDimConstTensor (md);
  if(md.numConstInputs > 0) 
  {
    int constTensorIdx = md.constTensorIndices[0];
    int tensor_idx = op->inputs()->Get(constTensorIdx);
    const auto *tensor = tensors->Get(tensor_idx);
    auto *shape = tensor->shape();
    if (is1DConstTensor == 1)
    {
      TIDLPCLayer.layerType = TIDL_BatchNormLayer;
      status = TIDL_tfliteCopyInputConstTensor(tfliteModel, i, constTensorIdx, TIDLPCLayer.weights, scale, zero_point);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read constant tensor : Only float, int32, uint8 and int8 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
        return -1;
      }
      if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
      {
        TIDL_tfliteDequantTensor(TIDLPCLayer.weights, scale, zero_point, 1);
      }
      if(shape->size()==0)//multiplication with constant 
      {
        int32_t wtSize = md.varTensorsDims[0][TIDL_DIM_NUMCH]; //broadcast the constant along number of channels
        TIDL_broadcastFloatTensorSA(TIDLPCLayer.weights, wtSize);
      }    
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.ptr = my_malloc(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.bufSize*sizeof(float));
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.bufSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weights.bufSize;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData->dataId = (*dataIndex)++;
      float* ptr = (float*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.ptr;    
      for(int lc = 0; lc < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].bias.bufSize; ++lc)
        ptr[lc] = 0.0;  
      return 0;
    }
    else 
    { //mul with one var and one const tensor
      TIDLPCLayer.layerType = TIDL_EltWiseLayer;
      TIDLPCLayer.layerParams.eltWiseParams.eltWiseType = TIDL_EltWiseProduct;
      TIDLPCLayer.outData->dataId = (*dataIndex)++;
      TIDLPCLayer.numInBufs = md.numInputs;
      if (md.numConstInputs > 0 && is1DConstTensor == 0)
      {
        status = TIDL_tfliteCopyInputConstTensor(tfliteModel, i, constTensorIdx, TIDLPCLayer.weights, TIDLPCLayer.weightScales, TIDLPCLayer.weightZeroPoints);
        if(status == -1)
        {
          diagsInfo.push_back("Cannot read constant tensor : Only float, int32, uint8 and int8 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__));
          return -1;
        }
      }
      return 0;
    }
  }
  else
  { //mul with two var tensors
    TIDLPCLayer.layerType = TIDL_EltWiseLayer;
    TIDLPCLayer.layerParams.eltWiseParams.eltWiseType = TIDL_EltWiseProduct;
    TIDLPCLayer.outData->dataId = (*dataIndex)++;
    TIDLPCLayer.numInBufs = md.numInputs;
    return 0;
  }   
}     

int32_t TIDL_tfliteMapMaxPoolParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status;
  int32_t padType;
  int32_t idx1, idx2;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  sTIDL_PoolingParams_t &poolParams = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);

  TIDLPCLayers.layerType = TIDL_PoolingLayer;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  poolParams.poolingType = TIDL_MaxPooling;
  //TIDL_getAttr_data_format(tfGraphDef.node(i), "data_format");
  // if (gloab_data_format == 1)
  // {
  //   idx1 = 3;
  //   idx2 = 2;
  // }
  // else
  // {
  //   idx1 = 2;
  //   idx2 = 1;
  // }

  poolParams.strideW = 1;
  poolParams.strideH = 1;
  poolParams.padW = 0;
  poolParams.padH = 0;
  // TIDL_getAttr_value(tfGraphDef.node(i), "strides", &poolParams.strideW, idx1);
  // TIDL_getAttr_value(tfGraphDef.node(i), "strides", &poolParams.strideH, idx2);
  // TIDL_getAttr_value(tfGraphDef.node(i), "ksize",   &poolParams.kernelW, idx1);
  // TIDL_getAttr_value(tfGraphDef.node(i), "ksize",   &poolParams.kernelH, idx2);

  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  auto *Pool2DParams = op->builtin_options_as_Pool2DOptions();
  poolParams.strideW = Pool2DParams->stride_w();
  poolParams.strideH = Pool2DParams->stride_h();
  poolParams.kernelW = Pool2DParams->filter_width();
  poolParams.kernelH = Pool2DParams->filter_height();

  padType = Pool2DParams->padding();
  if (padType == 0)
  {
    poolParams.padW = ((poolParams.kernelW - 1)) / 2;
    poolParams.padH = ((poolParams.kernelH - 1)) / 2;
  }

  return 0;
}

int32_t TIDL_tfliteMapAvgPoolParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{

  TIDL_tfliteMapMaxPoolParams(pOrgTIDLNetStructure, i, layerIndex, dataIndex, tfliteModel);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType = TIDL_AveragePooling;
  return 0;
}

int32_t TIDL_tfliteMapConcatV2Params(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t idx;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ConcatLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  sTIDL_ConcatParams_t &concatParams = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.concatParams;

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = op->inputs()->size();

  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  auto *ConcatParams = op->builtin_options_as_ConcatenationOptions();
  if (ConcatParams->axis() == 3)
    concatParams.axis = TIDL_DIM_NUMCH;
  else if (ConcatParams->axis() == 2)
    concatParams.axis = TIDL_DIM_WIDTH;
  else if (ConcatParams->axis() == 1)
    concatParams.axis = TIDL_DIM_HEIGHT;      
  else // if(ConcatParams->axis() == 0)
    concatParams.axis = TIDL_DIM_BATCH;      
  return 0;
}

int32_t TIDL_tfliteMapReshapeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status = 0;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.layerType = TIDL_ReshapeLayer;
  TIDL_tfliteSaveAllowlistingMetaData(tfliteModel,i,TIDLPCLayers);
  status = TIDL_checkReshapeTensorProperties(TIDLPCLayers);
  if(status == -1) return -1;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 1, TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints);
  return 0;
}

int32_t TIDL_tfliteMapSoftmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_SoftMaxLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  return 0;
}

int32_t TIDL_tfliteMapArgmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ArgMaxLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  return 0;
}


int32_t TIDL_tfliteMapPadParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t idx,j;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_PadLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int tensor_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(tensor_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  float * ptr;
  std::string outputName = tensors->Get(op->outputs()->Get(0))->name()->c_str();
  if(data)
  {
    ptr = (float *)malloc(data->size());
    readTensor(data, (uint8_t *) ptr);
  }
  if(data->size() / 4 == 8)
  {
    if((((int32_t *)ptr)[0] != 0) || (((int32_t *)ptr)[1] != 0) || (((int32_t *)ptr)[6] != 0) || (((int32_t *)ptr)[7] != 0))
    {
      printf("Padding is only supported in Width/height axis  - layer name - %s \n", outputName.c_str());
      diagsInfo.push_back("Padding is only supported in Width/height axis -- layer name - " + outputName  +" -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
      return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;
    }
  }
  else
  {
    printf("Pad layer is expected to provide 8 pad values  - layer name - %s \n", outputName.c_str());
      diagsInfo.push_back("Pad layer is expected to provide 8 pad values -- layer name - " + outputName  +" -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
    return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;
  }
  int32_t padT, padB, padL, padR;
  padT = ((int32_t *)ptr)[2];
  padB = ((int32_t *)ptr)[3];
  padL = ((int32_t *)ptr)[4];
  padR = ((int32_t *)ptr)[5];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.padLayerParams.padT = padT;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.padLayerParams.padB = padB;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.padLayerParams.padL = padL;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.padLayerParams.padR = padR;

  my_free(ptr);
  return 0;
}

int32_t TIDL_tfliteMapMinimumParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t idx,j;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ClipLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Clip;

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int tensor_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(tensor_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  if(!data)
  {
    printf("Error : Second input to minimum perator shall be const\n");
    exit(0);
  }
  if((data->size()/sizeof(float)) > 1)
  {
    printf("Error : The size of const tensor for minimum operator shall be one : %d\n", (data->size() / sizeof(float)));
    exit(0);
  }
  if(data)
  {
    readTensor(data, (uint8_t *)&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMax);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin = -FLT_MAX;
  }
  return 0;
}

int32_t TIDL_tfliteMapMaximumParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t idx,j;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ClipLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Clip;

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int tensor_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(tensor_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  if(!data)
  {
    printf("Error : Second input to maximum perator shall be const\n");
    exit(0);
  }
  if((data->size()/sizeof(float)) > 1)
  {
    printf("Error : The size of const tensor for maximum operator shall be one : %d\n", (data->size() / sizeof(float)));
    exit(0);
  }
  if(data)
  {
    readTensor(data, (uint8_t *)&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMax = FLT_MAX;
  }
  return 0;
}



int32_t TIDL_tfliteMapMeanParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  sTIDL_PoolingParams_t &poolParams = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams;

  TIDLPCLayers.layerType = TIDL_PoolingLayer;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  poolParams.poolingType = TIDL_AveragePooling;
  poolParams.strideW = 1;
  poolParams.strideH = 1;
  poolParams.padW = 0;
  poolParams.padH = 0;
  poolParams.kernelW = 0;
  poolParams.kernelH = 0;
  return 0;
}

int32_t TIDL_tfliteMapBiInterPResizeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t idx, j;
  char upsampleMode[50];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ResizeLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  int32_t axis;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = 1;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int tensor_idx = op->inputs()->Get(1);
  auto *resizeParams = op->builtin_options_as_ResizeNearestNeighborOptions();
  const auto *tensor = tensors->Get(tensor_idx);
  char nodeName[TIDL_MAX_DATA_NAME];

  if(isTensorVariable(tfliteModel,tensor_idx))
  {
    strcpy(nodeName,tensor->name()->c_str());
    int32_t scale_node_idx = TIDL_tfliteGetNodeIdx(tfliteModel, (const char *)nodeName);

    auto* scale_op = operators->Get(scale_node_idx);
    tensor_idx = scale_op->inputs()->Get(1);
    auto operator_codes = (*tfliteModel->operator_codes())[scale_op->opcode_index()]->builtin_code();
    if (tflite::BuiltinOperator_MUL != operator_codes)
    {
      printf(" Resizer scale ratio Op Shall be MUL - exiting \n");
      exit(0);
    }


    if(isTensorVariable(tfliteModel,tensor_idx))
    {
      printf(" Resizer scale ratio can not be dynamic - exiting \n");
      exit(0);
    }
    else
    {
        tensor_idx = scale_op->inputs()->Get(0);
        const auto *in_tensor = tensors->Get(tensor_idx);
        strcpy(nodeName,in_tensor->name()->c_str());
        int32_t stride_slice_idx = TIDL_tfliteGetNodeIdx(tfliteModel, (const char *)nodeName);
        auto* stride_slice_op = operators->Get(stride_slice_idx);
        operator_codes = (*tfliteModel->operator_codes())[stride_slice_op->opcode_index()]->builtin_code();

        if (tflite::BuiltinOperator_STRIDED_SLICE != operator_codes)
        {
          printf(" Resizer scale ratio Op's input shall be BuiltinOperator_STRIDED_SLICE - exiting \n");
          exit(0);
        }
        tensor_idx = stride_slice_op->inputs()->Get(0);
        in_tensor = tensors->Get(tensor_idx);
        strcpy(nodeName,in_tensor->name()->c_str());
        int32_t shape_ix = TIDL_tfliteGetNodeIdx(tfliteModel, (const char *)nodeName);
        auto* shape_op = operators->Get(shape_ix);
        operator_codes = (*tfliteModel->operator_codes())[shape_op->opcode_index()]->builtin_code();
        if (tflite::BuiltinOperator_SHAPE != operator_codes)
        {
          printf(" BuiltinOperator_STRIDED_SLICE Op's input shall be BuiltinOperator_SHAPE - exiting \n");
          exit(0);
        }
        tensor_idx = shape_op->inputs()->Get(0);
        in_tensor = tensors->Get(tensor_idx);
        strcpy(nodeName,in_tensor->name()->c_str());
        tensor_idx = op->inputs()->Get(0);
        in_tensor = tensors->Get(tensor_idx);
        if(strcmp(nodeName,in_tensor->name()->c_str()) != 0)
        {
          printf(" ReshapeLayer input and Scale Brach Input not matching - exiting \n");
          exit(0);
        }

        tensor_idx = scale_op->inputs()->Get(1);
        const auto *scale_tensor = tensors->Get(tensor_idx);
        auto *data   = (*tfliteModel->buffers())[scale_tensor->buffer()]->data();
        int32_t * ptr = (int32_t *)malloc(data->size());
        readTensor(data, (uint8_t *) ptr);
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.resizeParams.resizeRatio[TIDL_DIM_HEIGHT] = ptr[0];
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.resizeParams.resizeRatio[TIDL_DIM_WIDTH]  = ptr[1];
        free(ptr);
    }
  }
  else
  {
    auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
    int32_t * ptr = (int32_t *)malloc(data->size());
    readTensor(data, (uint8_t *) ptr);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.resizeParams.resizeRatio[TIDL_DIM_HEIGHT] = -ptr[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.resizeParams.resizeRatio[TIDL_DIM_WIDTH]  = -ptr[1];
    free(ptr);
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.resizeParams.mode = TIDL_ResizeBilinear;
  if((resizeParams) && (resizeParams->align_corners() == true))
  {
     printf("Error: Align corners TRUE is not supported\n");
  }


  return 0;
}

int32_t TIDL_tfliteMapNNResizeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{

  TIDL_tfliteMapBiInterPResizeParams(pOrgTIDLNetStructure, i, layerIndex, dataIndex, tfliteModel);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.resizeParams.mode = TIDL_ResizeNearest;
  return 0;
}

int32_t TIDL_tfliteMapFullyConnectedParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  sTIDL_InnerProductParams_t &innerProductParams = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams;

  orgTIDLNetStructure.TIDLPCLayers[i].layerType = TIDL_InnerProductLayer;

  TIDLPCLayers.layerType = TIDL_InnerProductLayer;
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  TIDLPCLayers.outData[0].elementType = tidl_getElementType(1);

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  int kernel_idx = op->inputs()->Get(1);
  const auto *tensor = tensors->Get(kernel_idx);
  auto *shape = tensor->shape();
  auto *data   = (*tfliteModel->buffers())[tensor->buffer()]->data();
  innerProductParams.numOutNodes = shape->Get(0);
  innerProductParams.numInNodes = shape->Get(1);
  auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
  auto *FullyConnectedParams = op->builtin_options_as_FullyConnectedOptions();

  TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 1, TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints);
  if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
  {
    TIDL_tfliteDequantTensor(TIDLPCLayers.weights, TIDLPCLayers.weightScales, TIDLPCLayers.weightZeroPoints, 1);
  }

  TIDL_tfliteCopyInputConstTensor(tfliteModel, i, 2, TIDLPCLayers.bias, TIDLPCLayers.biasScales, TIDLPCLayers.biasZeroPoints);
  if(gParams.quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
  {
    TIDL_tfliteDequantTensor(TIDLPCLayers.bias, TIDLPCLayers.biasScales, TIDLPCLayers.biasZeroPoints, 1);
  }

  return 0;

}

int32_t TIDL_tfliteMapStridedSliceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              layerIdx,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  int32_t status = TIDL_ALLOWLISTING_LAYER_CHECK_PASSED;
  /**************** Tensor property checks ****************/
  sTIDL_LayerPC_t &layer = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDL_tfliteSaveAllowlistingMetaData(tfliteModel,layerIdx,layer);
  status = TIDL_checkSliceTensorProperties(layer);
  if(status == -1) return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;

  layer.outData[0].dataId = (*dataIndex)++;
  
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(layerIdx);
  auto *StridedSliceParams = op->builtin_options_as_StridedSliceOptions();
  
  /**************** Map attributes ****************/
  
  int32_t beginMask = StridedSliceParams->begin_mask();
  int32_t endMask = StridedSliceParams->end_mask();
  int32_t ellipsisMask = StridedSliceParams->ellipsis_mask();
  int32_t newAxisMask = StridedSliceParams->new_axis_mask();
  int32_t shrinkAxisMask = StridedSliceParams->shrink_axis_mask();
  
  /****************  Basic attribute checks **************/

  if((ellipsisMask != 0) || (newAxisMask != 0) || (shrinkAxisMask != 0))
  {
    diagsInfo.push_back("ALLOWLISTING : SLICE : ellipsis_mask, new_axis_mask and shrink_axis_mask must be 0  -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
    return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;
  }

  if((beginMask < 0) || (beginMask > 15) || (endMask < 0) || (endMask > 15)) /* since only 4 input dims are supported, mask can be only 4 bit - this is a sanity check */
  {
    diagsInfo.push_back("ALLOWLISTING : SLICE : begin_mask/end_mask not in supported range - [0,15]  -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
    return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;
  }

  /***************** Map inputs/parameters *****************/

  const auto *tensorBegin = tensors->Get(op->inputs()->Get(1));
  const auto *tensorEnd = tensors->Get(op->inputs()->Get(2));
  const auto *tensorStrides = tensors->Get(op->inputs()->Get(3));
  auto *dataBeginTflitePtr   = (*tfliteModel->buffers())[tensorBegin->buffer()]->data();
  auto *dataEndTflitePtr   = (*tfliteModel->buffers())[tensorEnd->buffer()]->data();
  auto *dataStridesTflitePtr   = (*tfliteModel->buffers())[tensorStrides->buffer()]->data();
  
  int *dataBegin, *dataEnd, *dataStrides;
  if(dataBeginTflitePtr)
  {
    dataBegin = (int *)malloc(dataBeginTflitePtr->size());
    readTensor(dataBeginTflitePtr, (uint8_t *) dataBegin);
  }

  if(dataEndTflitePtr)
  {
    dataEnd = (int *)malloc(dataEndTflitePtr->size());
    readTensor(dataEndTflitePtr, (uint8_t *) dataEnd);
  }

  if(dataStridesTflitePtr)
  {
    dataStrides = (int *)malloc(dataStridesTflitePtr->size());
    readTensor(dataStridesTflitePtr, (uint8_t *) dataStrides);
  }

  /**************** Mapped inputs/parameters related checks *************/
  for(int i = 0; i < 4; i++)
  {
    if(dataStrides[i] != 1)
    {
      diagsInfo.push_back("ALLOWLISTING : SLICE : only stride 1 slice is supported  -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
    return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;
    }
  }
  
  /****************** Derived parameters *****************/

  /* Convert beginMask and endMask to binary bits */
  std::vector<int> beginMaskBits, endMaskBits;
  for(int i = 0; i < 4; i++) /* beginMask = 7 corresponds to 1110 in bits, 4 corresponds to 0010 - bits are reversed as per tflite interpretation */
  {
    beginMaskBits.push_back(beginMask % 2);
    beginMask /= 2;
    endMaskBits.push_back(endMask % 2);
    endMask /= 2;
  }

  const auto *outTensor = tensors->Get(op->outputs()->Get(0));
  const auto *inTensor = tensors->Get(op->inputs()->Get(0));

  std::vector<int32_t> outTensorDims, inTensorDims;
  for(int i = 0; i < 4; i++)  /* TIDL_checkSliceTensorProperties ensures both input_0 and output_0 have 4 dimensions */
  {
    outTensorDims.push_back(outTensor->shape()->Get(i));
    inTensorDims.push_back(inTensor->shape()->Get(i));
  }

  std::vector<int32_t> axes;
  for(int i = 1; i < 4; i++) /* Only batch size = 1 supported as checked in TIDL_checkSliceTensorProperties. Batch slicing not supported and batch bits not checked in tflite runtime implementation */
  {
    if(beginMaskBits[i] == 1) /* begin ignored for index i, set begin to 0 : no slicing at beginning */
    {
      dataBegin[i] = 0;
    }
    if(endMaskBits[i] == 1) /* end ignored for index, set end same as the corresponding input dimension : no slicing at end */
    {
      dataEnd[i] = inTensorDims[i];
    }
    if((dataBegin[i] != 0) || (dataEnd[i] != inTensorDims[i])) /* implies slicing happens in this axis */
    {
      axes.push_back(i);
    }
  }

  /****************** Check derived parameters *****************/
  if(axes.size() != 1)
  {
    diagsInfo.push_back("ALLOWLISTING : SLICE : Slicing is supported only across either of height, width or channel axis, not across multiple axes  -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
    return TIDL_ALLOWLISTING_LAYER_CHECK_FAILED;
  }
  
  /*************** Mapping of attributes and inputs/parameters to TIDL layer *************/
  int32_t NhwcAxis = axes[0];
  int32_t NchwAxis;
  NchwAxis = NhwcAxis == 1 ? TIDL_DIM_HEIGHT :   // H
            NhwcAxis == 2 ? TIDL_DIM_WIDTH :   // W
            NhwcAxis == 3 ? TIDL_DIM_NUMCH :   // C
            NhwcAxis;

  layer.layerParams.sliceParams.axis = NchwAxis;
  layer.layerParams.sliceParams.stride = 1;
  layer.layerParams.sliceParams.slicePoints[0] = dataBegin[NhwcAxis];
  layer.layerParams.sliceParams.slicePoints[1] = dataEnd[NhwcAxis];

  layer.layerType = TIDL_SliceLayer;
  layer.numInBufs = 1;
  layer.numOutBufs = 1;

  if(dataBegin) free(dataBegin);
  if(dataEnd) free(dataEnd);
  if(dataStrides) free(dataStrides);

  return TIDL_ALLOWLISTING_LAYER_CHECK_PASSED;
}

static int32_t tidl_getFBModel(uint8_t * fileString, uint8_t **buffer_pointer)
{
  FILE * fptr;
  int32_t netSize;

  fptr = fopen((const char *)fileString, "rb");
  if (fptr)
  {
    fseek(fptr, 0L, SEEK_END);
    netSize = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);
    *buffer_pointer = (uint8_t *)malloc(netSize);
    fread(*buffer_pointer, 1, netSize, fptr);
    fclose(fptr);
  }
  else
  {
    printf("Could Not Open Files %s\n", fileString);
    return -1;
  }

}

int32_t TIDL_tfliteMapReluParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ReLULayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  return 0;
}

int32_t TIDL_tfliteMapRelu6Params(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  TIDL_tfliteMapReluParams(pOrgTIDLNetStructure, i, layerIndex, dataIndex, tfliteModel);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_RelU6;
  return 0;
}
int32_t TIDL_tfliteMapSigmoidParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_SigmoidLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Sigmoid;
  return 0;
}

int32_t TIDL_tfliteMapTanhParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_TanhLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Tanh;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  int32_t status = TIDL_checkNonLinearLUTLayersStandAlone(TIDLPCLayers);
  return status;
}

int32_t TIDL_tfliteMapHardSigmoidParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_HardSigmoidLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_HardSigmoid;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  int32_t status = TIDL_checkNonLinearLUTLayersStandAlone(TIDLPCLayers);
  return status;
}

int32_t TIDL_tfliteMapELUParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ELULayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_ELU;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.eluParams.alpha = (float32_tidl)1;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  int32_t status = TIDL_checkNonLinearLUTLayersStandAlone(TIDLPCLayers);
  return status;
}

int32_t TIDL_tfliteMapDepthTpSpaceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{

  int32_t idx,j;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_DepthToSpaceLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto* op = operators->Get(i);
  auto *depToSpacePrms = op->builtin_options_as_DepthToSpaceOptions();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.depthToSpaceParams.blockSize = depToSpacePrms->block_size();
  return 0;
}

int32_t TIDL_tfliteMapBatchToSpaceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_BatchToSpaceLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  //fill block size
  const auto *tensor_blockSize = tensors->Get(op->inputs()->Get(1));
  auto *blockSize   = (*tfliteModel->buffers())[tensor_blockSize->buffer()]->data();
  int32_t* ptrBlockSize = (int32_t *)malloc(blockSize->size());
  readTensor(blockSize, (uint8_t *)ptrBlockSize);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.batchToSpaceParams.blockHeight = ptrBlockSize[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.batchToSpaceParams.blockWidth = ptrBlockSize[1];
  //fill cropping dimensions
  const auto *tensor_crop = tensors->Get(op->inputs()->Get(2));
  auto *cropping   = (*tfliteModel->buffers())[tensor_crop->buffer()]->data();
  int32_t* ptrCropping = (int32_t *)malloc(cropping->size());
  readTensor(cropping, (uint8_t *)ptrCropping);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.batchToSpaceParams.cropT = ptrCropping[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.batchToSpaceParams.cropB = ptrCropping[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.batchToSpaceParams.cropL = ptrCropping[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.batchToSpaceParams.cropR = ptrCropping[3];

  free(ptrCropping);
  free(ptrBlockSize);
  return 0;
}

int32_t TIDL_tfliteMapSpaceToBatchParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_SpaceToBatchLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;

  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  auto* op = operators->Get(i);
  // fill block shape 
  const auto *tensor_blockSize = tensors->Get(op->inputs()->Get(1));
  auto *blockSize   = (*tfliteModel->buffers())[tensor_blockSize->buffer()]->data();
  int32_t* ptrBlockSize = (int32_t *)malloc(blockSize->size());
  readTensor(blockSize, (uint8_t *)ptrBlockSize);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.spaceToBatchParams.blockHeight = ptrBlockSize[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.spaceToBatchParams.blockWidth = ptrBlockSize[1];

  //fill padding
  const auto *tensor_padding = tensors->Get(op->inputs()->Get(2));
  auto *padding   = (*tfliteModel->buffers())[tensor_padding->buffer()]->data();
  int32_t* ptrPadding = (int32_t *)malloc(padding->size());
  readTensor(padding, (uint8_t *)ptrPadding);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.spaceToBatchParams.padT = ptrPadding[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.spaceToBatchParams.padB = ptrPadding[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.spaceToBatchParams.padL = ptrPadding[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerPCParams.spaceToBatchParams.padR = ptrPadding[3];

  free(ptrBlockSize);
  free(ptrPadding);
  return 0;
}

int32_t TIDL_tfliteMapCastParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_CastLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  return 0;
}

typedef struct {
  int8_t name[TIDL_STRING_SIZE];
  int32_t(*tidl_tfliteMapFunc)(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
    int32_t              i,
    int32_t              layerIndex,
    int32_t              *dataIndex,
    const Model*         tfliteModel);
}sTIDL_tfliteOpParamMap_t;

sTIDL_tfliteOpParamMap_t tidl_TfliteOpParamMapTable[] =
{
  { "Placeholder",                     TIDL_tfliteMapPlaceHolderParams },       //  TIDL_DataLayer,
  { "CONV_2D",                         TIDL_tfliteMapConvParams },       //  TIDL_ConvolutionLayer ,
  { "TRANSPOSE_CONV",                  TIDL_tfliteMapDeConvParams },       //  TIDL_ConvolutionLayer ,
  { "DEPTHWISE_CONV_2D",               TIDL_tfliteMapDWConvParams },       //  TIDL_ConvolutionLayer ,
  { "ADD",                             TIDL_tfliteMapAddParams },       //  TIDL_EltWiseLayer ,
  { "SUB",                             TIDL_tfliteMapSubParams },       //  TIDL_EltWiseLayer ,
  { "MUL",                             TIDL_tfliteMapMulParams },       //  TIDL_EltWiseLayer ,
  { "MINIMUM",                         TIDL_tfliteMapMinimumParams },       //  TIDL_EltWiseLayer ,
  { "MAXIMUM",                         TIDL_tfliteMapMaximumParams },       //  TIDL_EltWiseLayer ,
  { "RELU",                            TIDL_tfliteMapReluParams },       //  TIDL_ReLULayer ,
  { "RELU6",                           TIDL_tfliteMapRelu6Params },       //  TIDL_ReLULayer ,
  { "LEAKY_RELU",                      TIDL_tfliteMapLeakyRluParams },       //  TIDL_ReLULayer ,
  { "MAX_POOL_2D",                     TIDL_tfliteMapMaxPoolParams },       //  TIDL_PoolingLayer ,
  { "AVERAGE_POOL_2D",                 TIDL_tfliteMapAvgPoolParams },      //  TIDL_PoolingLayer ,
  { "CONCATENATION",                   TIDL_tfliteMapConcatV2Params },       //  TIDL_ConcatLayer ,
  { "RESHAPE",                         TIDL_tfliteMapReshapeParams },       //  TIDL_ReshapeLayer ,
  { "SOFTMAX",                         TIDL_tfliteMapSoftmaxParams },      //  TIDL_SoftMaxLayer ,
  { "SIGMOID",                         TIDL_tfliteMapSigmoidParams },      //  TIDL_SigmoidLayer ,
  { "LOGISTIC",                        TIDL_tfliteMapSigmoidParams },      //  TIDL_SigmoidLayer ,
  { "TANH",                            TIDL_tfliteMapTanhParams },      //  TIDL_TanhLayer ,
  { "HARDSIGMOID",                     TIDL_tfliteMapHardSigmoidParams },      //  TIDL_HardSigmoidLayer ,
  { "ELU",                             TIDL_tfliteMapELUParams },      //  TIDL_ELULayer ,
  { "ARG_MAX",                         TIDL_tfliteMapArgmaxParams },      //  TIDL_ArgMaxLayer ,
  { "PAD",                             TIDL_tfliteMapPadParams },       //  TIDL_SoftMaxLayer ,
  { "MEAN",                            TIDL_tfliteMapMeanParams },       //  TIDL_SoftMaxLayer ,
  { "RESIZE_NEAREST_NEIGHBOR",         TIDL_tfliteMapNNResizeParams },       //  TIDL_ResizeLayer ,
  { "RESIZE_BILINEAR",                 TIDL_tfliteMapBiInterPResizeParams },       //  TIDL_ResizeLayer ,
  { "FULLY_CONNECTED",                 TIDL_tfliteMapFullyConnectedParams }, // TIDL_InnerProductLayer ,
  { "STRIDED_SLICE",                   TIDL_tfliteMapStridedSliceParams }, // TIDL_SliceLayer ,
  { "DEPTH_TO_SPACE",                  TIDL_tfliteMapDepthTpSpaceParams }, // TIDL_SliceLayer ,
  { "BATCH_TO_SPACE_ND",               TIDL_tfliteMapBatchToSpaceParams }, // TIDL_BatchToSpaceLayer ,
  { "SPACE_TO_BATCH_ND",               TIDL_tfliteMapSpaceToBatchParams }, // TIDL_SpaceToBatchLayer ,
  { "QUANTIZE",                        TIDL_tfliteMapQuantizeParams }, // TIDL_DataConvertLayer ,
  { "DEQUANTIZE",                      TIDL_tfliteMapDeQuantizeParams }, // TIDL_DataConvertLayer ,
  { "CAST",                            TIDL_tfliteMapCastParams } // TIDL_tfliteMapCastParams ,
};


int32_t TIDL_getTfliteOpParamMapId(const char  * name)
{
  int32_t i = -1;
  for (i = 0; i < sizeof(tidl_TfliteOpParamMapTable) / sizeof(sTIDL_tfliteOpParamMap_t); i++)
  {
    if ((strcmp(name, (const char *)tidl_TfliteOpParamMapTable[i].name) == 0))
    {
      return (i);
    }
  }
  return (-1);
}

int32_t TIDL_tfliteMapUnSuportedlayerParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  const Model*         tfliteModel)
{
  return 0;
}

void tidl_findTfliteOutputNames(const Model* tfliteModel, char * outList)
{
  int i, j, k, l;
  char tensorName[FILE_NAME_SIZE];
  char inTensorName[FILE_NAME_SIZE];
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  for (i = 0; i < operators->size(); i++)
  {
    int outDataUsed = 0;
    const auto *op = operators->Get(i);
    for(j = 0; j < op->outputs()->size(); j++)
    {
      strcpy((char *)tensorName, tensors->Get(op->outputs()->Get(j))->name()->c_str());
      for (k = 0; k < operators->size(); k++)
      {
        const auto *op1 = operators->Get(k);
        for (l = 0; l < op1->inputs()->size(); l++)
        {
          strcpy((char *)inTensorName,  tensors->Get(op1->inputs()->Get(l))->name()->c_str());
          if (strcmp(tensorName, inTensorName) == 0)
          {
            outDataUsed = 1;
            break;
          }

          if (outDataUsed)
          break;
        }
        if (outDataUsed)
          break;
      }
      if (outDataUsed == 0)
      {
        strcpy(tensorName,tensors->Get(op->outputs()->Get(0))->name()->c_str());
        strcat(outList, tensorName);
        strcat(outList, ",");
      }
    }
  }
}

int32_t tidl_tfliteLayerFillTensorNames(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  const Model*         tfliteModel)
{
  int32_t j;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();

  const auto *op = operators->Get(i);
  if(strlen(tensors->Get(op->outputs()->Get(0))->name()->c_str()) < TIDL_STRING_SIZE)
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, tensors->Get(op->outputs()->Get(0))->name()->c_str());
  }
  else
  {
    printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, tensors->Get(op->outputs()->Get(0))->name()->c_str());
    exit(-1);
  }

  //printf("Adding OP %d - %s \n", layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);

  if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs > 0)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++)
    {
      auto *tensor = tensors->Get(op->inputs()->Get(j));

      if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType == TIDL_Deconv2DLayer)
      {
        if(strlen(tensors->Get(op->inputs()->Get(j+2))->name()->c_str()) < TIDL_STRING_SIZE)
        {
          strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j], tensors->Get(op->inputs()->Get(j+2))->name()->c_str());
        }
        else
        {
          printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, tensors->Get(op->inputs()->Get(j+2))->name()->c_str());
          exit(-1);
        }
      }
      else
      {
        if(strlen(tensors->Get(op->inputs()->Get(j))->name()->c_str()) < TIDL_STRING_SIZE)
        {
          strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j], tensors->Get(op->inputs()->Get(j))->name()->c_str());
        }
        else
        {
          printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, tensors->Get(op->inputs()->Get(j))->name()->c_str());
          exit(-1);
        }
      }

      /* Populate tensor scale and zero point if 8-bit:*/
      if(gParams.quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
      {
        if ((tensor->type() == TensorType_UINT8) || (tensor->type() == TensorType_INT8))
        {
          auto * scale = tensor->quantization()->scale();
          auto *zero_point = tensor->quantization()->zero_point();
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].tensorScale = scale->Get(0);
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].tensorZeroPoint = zero_point->Get(0);       
        }
      }
      /******************************************/
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].dataId = -1;
   }
  }
  if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs > 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outConsumerLinked[0] = 0;
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; j++)
    {
      auto *tensor = tensors->Get(op->outputs()->Get(j));
      
      if(strlen(tensors->Get(op->outputs()->Get(j))->name()->c_str()) < TIDL_STRING_SIZE)
      {
        strcpy((char *)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j], tensors->Get(op->outputs()->Get(j))->name()->c_str());
      }
      else
      {
        printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, tensors->Get(op->outputs()->Get(j))->name()->c_str());
        exit(-1);
      }

      
      /* Populate tensor scale and zero point if 8-bit: */
      if(gParams.quantizationStyle == TIDL_QuantStyleAsymNP2_TFL)
      {
        if ((tensor->type() == TensorType_UINT8) || (tensor->type() == TensorType_INT8))
        {
          auto * scale = tensor->quantization()->scale();
          auto *zero_point = tensor->quantization()->zero_point();
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].tensorScale = scale->Get(0);
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].tensorZeroPoint = zero_point->Get(0);       
       }
      }
      /******************************************/

      if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType == TIDL_RelU6)
      {
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Clip;
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMax = 6.0;
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin = 0;
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = tidl_getElementType(0);

      }
      else if ((tensor->type() == TensorType_UINT8) || (tensor->type() == TensorType_INT8))
      {
        auto * scale = tensor->quantization()->scale();
        auto *min    = tensor->quantization()->min();
        auto *max    = tensor->quantization()->max();
        auto *zero_point = tensor->quantization()->zero_point();
        if (scale && min && max)
        {
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Clip;
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMax = max->Get(0);
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin = min->Get(0);
          if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin >= 0)
          {
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = tidl_getElementType(0);
          }
          else
          {
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = tidl_getElementType(1);
          }
        }
        else if (scale && zero_point)
        {
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.actType = TIDL_Clip;

          int32_t inMax = 127;
          int32_t inMin = -128;

          if (tensor->type() == TensorType_UINT8)
          {
            inMax = 255;
            inMin = 0;
          }

          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMax = (inMax - zero_point->Get(0)) * scale->Get(0);
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin = (inMin-zero_point->Get(0)) * scale->Get(0);
          if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].actParams.clipMin >= 0)
          {
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = tidl_getElementType(0);
          }
          else
          {
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = tidl_getElementType(1);
          }
        }
      }
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outConsumerLinked[j] = 0;
    }
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weightsElementSizeInBits = NUM_WHGT_BITS;

  return 0;
}

int32_t tidl_tfliteGetNewNodeToAdd(sTIDL_OrgNetwork_t   &orgTIDLNetStructure,
  int32_t              layerIndex,
  const Model*         tfliteModel)
{
  int32_t i, j, nodeIdx = -1;

  for (i = 0; i < layerIndex; i++)
  {
    for (j = 0; j < orgTIDLNetStructure.TIDLPCLayers[i].numInBufs; j++)
    {
      if (TIDL_getLayerIdx(&orgTIDLNetStructure, layerIndex, (const char *)orgTIDLNetStructure.TIDLPCLayers[i].inDataNames[j]) == -1)
      {

        nodeIdx = TIDL_tfliteGetNodeIdx(tfliteModel, (const char *)orgTIDLNetStructure.TIDLPCLayers[i].inDataNames[j]);
        if (nodeIdx != -1)
        {
          break;
        }
      }
    }
    if (nodeIdx != -1)
    {
      break;
    }
  }
  return nodeIdx;
}

int32_t tidl_tfliteLayerUpdateConsumerCount(sTIDL_OrgNetwork_t *pOrgTIDLNetStructure,
                                        int32_t i,
                                        int32_t layerIndex,
                                        const Model* tfliteModel)
{
  int32_t i0, i1, i2;
  int32_t numCons = 0;
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors = (*tfliteModel->subgraphs())[0]->tensors();

  for (i0 = 0; i0 < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; i0++)
  {
    numCons = 0;
    for (i1 = 0; i1 < operators->size(); i1++)
    {
      const auto *op = operators->Get(i1);
      for (i2 = 0; i2 < op->inputs()->size(); i2++)
      {
        if (strcmp((const char *)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[i0], tensors->Get(op->inputs()->Get(i2))->name()->c_str()) == 0)
        {
          numCons++;
        }
      }
    }
    for (i2 = 0; i2 < numNetOutData; i2++)
    {
      if (strcmp((const char *)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[i0], outDataNames[i2]) == 0)
      {
        numCons++;
      }
    }

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outConsumerCnt[i0] = numCons;
  }
  return 0;
}


void tfLite_import(tidl_import_config * params, int32_t *totalData, int32_t* totalLayers)
{
  int32_t                    i,j;
  int32_t                    layerNum;
  int32_t                    inputSize;
  int32_t                    pad,stride;
  int32_t                    layerIndex;
  int32_t                    tiLayerIndex;
  int32_t                    dataIndex;
  const uint8_t             *name;
  const uint8_t             *inputName[10];
  const uint8_t             *outputName;
  int32_t status;
  int32_t                    dataSize;
  int32_t                    id;
  int paramSet  = 0;
  int conv2DRandParams = 0;
  string attrKey;
  int32_t inLayerId = 0;
  int32_t weightsElementSizeInBits;
  int32_t mapTblIdx = -1;

  string key = "value";

  printf("TFLite Model (Flatbuf) File  : %s  \n",(const char *)params->inputNetFile);
  printf("TIDL Network File      : %s  \n", (const char *)params->outputNetFile);
  printf("TIDL IO Info File      : %s  \n", (const char *)params->outputParamsFile);
  uint8_t *buffer_pointer ;
  tidl_getFBModel(params->inputNetFile, &buffer_pointer);

  auto* tfliteModel = GetModel(buffer_pointer);
  auto operators = (*tfliteModel->subgraphs())[0]->operators();
  auto tensors   = (*tfliteModel->subgraphs())[0]->tensors();
  printf("%d\n",operators->size());
  // gloab_data_format = 0;
  layerIndex = 0;
  dataIndex  = 0;

  if (strcmp((char*)params->outDataNamesList, "") == 0)
  {
    char outDataNamesList[500] = "";
    tidl_findTfliteOutputNames(tfliteModel, (char*)outDataNamesList);
    numNetOutData = tidl_getStringsFromList((char *)outDataNamesList, (char*)outDataNames, TIDL_MAX_DATA_NAME);
  }
  else
  {
    numNetOutData = tidl_getStringsFromList((char *)params->outDataNamesList, (char*)outDataNames, TIDL_MAX_DATA_NAME);
  }

  for (i = 0; i < numNetOutData; i++)
  {
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs =  1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = -1;
    strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name, outDataNames[i]);
    strcpy((char *)orgTIDLNetStructure.TIDLPCLayers[layerIndex].inDataNames[0], outDataNames[i]);
    strcpy((char *)orgTIDLNetStructure.TIDLPCLayers[layerIndex].outDataNames[0], outDataNames[i]);
    layerIndex++;
  }

  if (strcmp((char *)params->inDataNamesList, "") != 0)
  {
    numNetInData = tidl_getStringsFromList((char *)params->inDataNamesList, (char *)inDataNames, TIDL_MAX_DATA_NAME);
    for (i = 0; i < numNetInData; i++)
    {
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs = -1;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
      strcpy((char *)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name, inDataNames[i]);
      strcpy((char *)orgTIDLNetStructure.TIDLPCLayers[layerIndex].outDataNames[0], inDataNames[i]);
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outConsumerCnt[0] = 1;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outConsumerLinked[0] = 0;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
      tidl_tfliteLayerUpdateConsumerCount(&orgTIDLNetStructure, layerIndex, layerIndex, tfliteModel);
      tidl_linkOutputTensors(&orgTIDLNetStructure, layerIndex);
      layerIndex++;
    }
  }

  int newNode = tidl_tfliteGetNewNodeToAdd(orgTIDLNetStructure, layerIndex, tfliteModel);
  while (newNode != -1)
  {
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs = 1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dataId = -1;
    const auto *op = operators->Get(newNode);
    auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
    const char* str = EnumNameBuiltinOperator(operator_codes);
    mapTblIdx = TIDL_getTfliteOpParamMapId(str);
    if(gParams.debugTraceLevel > 1)
    {
      const auto *tensor = tensors->Get(op->outputs()->Get(0));
      printf(" TFlite operator %s : %s is added to net in %d \n", str, tensor->name()->c_str(), layerIndex);
    }
    if (mapTblIdx == -1)
    {
      printf(" TFlite operator %s is not suported now..  By passing\n", str);
      TIDL_tfliteMapUnSuportedlayerParams(&orgTIDLNetStructure, newNode, layerIndex, &dataIndex, tfliteModel);
    }
    else
    {
      tidl_TfliteOpParamMapTable[mapTblIdx].tidl_tfliteMapFunc(&orgTIDLNetStructure, newNode, layerIndex, &dataIndex, tfliteModel);
    }

    if (params->enableCustomLayers)
    {
      TIDL_MapCustomParams(&orgTIDLNetStructure,
                            newNode,
                            layerIndex,
                            &dataIndex,
                            tfliteModel,
                            NULL,
                            TIDL_IMPORT_MODEL_FORMAT_TFLITE);
    }

    tidl_tfliteLayerFillTensorNames(&orgTIDLNetStructure, newNode, layerIndex, tfliteModel);
    tidl_tfliteLayerUpdateConsumerCount(&orgTIDLNetStructure, newNode, layerIndex, tfliteModel);
    tidl_linkInputTensors(&orgTIDLNetStructure, layerIndex);
    tidl_linkOutputTensors(&orgTIDLNetStructure, layerIndex);

    layerIndex++;
    newNode = tidl_tfliteGetNewNodeToAdd(orgTIDLNetStructure, layerIndex, tfliteModel);
  }
  *totalData = dataIndex;
  *totalLayers = layerIndex;
#if 0
  for (id = 0; id < operators->size(); id++)
  {
    const auto *op = operators->Get(id);
    auto operator_codes = (*tfliteModel->operator_codes())[op->opcode_index()]->builtin_code();
    printf("Node |   %d |  %40s |",id, EnumNameBuiltinOperator(operator_codes));
    //printf("builtin type index %d\n",operator_codes);
    auto builtin_options = op->builtin_options();
    if(tflite::BuiltinOperator_AVERAGE_POOL_2D == operator_codes )
    {
      printf("None      |");
    }
    else if(tflite::BuiltinOperator_CONV_2D == operator_codes )
    {
      auto *Conv2DParams = op->builtin_options_as_Conv2DOptions();
      printf("stride_w :%d |",Conv2DParams->fused_activation_function());
    }
    else if(tflite::BuiltinOperator_DEPTHWISE_CONV_2D == operator_codes )
    {
      auto *DepthwiseConv2DOptions = op->builtin_options_as_DepthwiseConv2DOptions();
      printf("stride_w: %d |",DepthwiseConv2DOptions->stride_w());
    }
    printf("Input %d - ",op->inputs()->size());
    for(i = 0; i < op->inputs()->size(); i++)
    {
      printf(" %d ", op->inputs()->Get(i));
    }
    printf(" | ");
    printf("Outputs %d - ",op->outputs()->size());
    for(i = 0; i < op->outputs()->size(); i++)
    {
      printf(" %d ", op->outputs()->Get(i));
    }
    printf(" |\n ");
  }
#endif
}
