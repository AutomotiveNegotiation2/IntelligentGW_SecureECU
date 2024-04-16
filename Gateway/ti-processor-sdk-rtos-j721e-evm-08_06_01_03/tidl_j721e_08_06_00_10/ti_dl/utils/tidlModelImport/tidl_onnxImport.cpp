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
//#include <io.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <float.h>
#include <cmath>
#include <limits>

#include "ti_dl.h"
#include "tidl_import_api.h"
#include "tidl_import_config.h"
//#include "onnx/onnx-ml.proto3.pb.h"
#include "onnx/onnx-ml.proto3.pb.h"
#include "tidl_custom_import.h"
#include "tidl_import_common.h"
#include "tidl_onnxImport.h"
#include "tidl_import_common_model_check.h"
#include "tidl_import_common_tidlrt_osrt.h"
#include "tidl_deviceInfo.h"

using namespace std;
using namespace onnx;
using ::google::protobuf::Message;
using ::google::protobuf::io::FileInputStream;
using ::google::protobuf::io::FileOutputStream;
using ::google::protobuf::io::ZeroCopyInputStream;
using ::google::protobuf::io::CodedInputStream;
using ::google::protobuf::io::ZeroCopyOutputStream;
using ::google::protobuf::io::CodedOutputStream;


#include "tidl_import_common.h"
int64_t onnxOpSetVersion;

extern sTIDL_OrgNetwork_t      orgTIDLNetStructure;
extern sTIDL_OrgNetwork_t      tempTIDLNetStructure;
extern sTIDL_Network_t         tIDLNetStructure;

extern "C"
{
extern std::vector<std::string> diagsInfo;
int32_t TIDL_isInputConstInGraph(GraphProto &onnGraph, const string name);
int32_t TIDL_isInputConstInGraph(GraphProto& onnGraph, const string name)
{
  int i;
  for (i = 0; i < numNetInData; i++)
  {
    if ((strcmp(inDataNames[i], name.c_str()) == 0))
    {
      return(0);
    }
  }
  for (i = 0; i < onnGraph.initializer_size(); i++)
  {
    if ((strcmp(onnGraph.initializer(i).name().c_str(), name.c_str()) == 0))
    {
      return(1);
    }
  }
  for (i = 0; i < onnGraph.node_size(); i++)
  {
    if ((strcmp(onnGraph.node(i).output(0).c_str(), name.c_str()) == 0) && (strcmp(onnGraph.node(i).op_type().c_str(), "Constant") == 0))
    {
      return(1);
    }
  }
  return (0);
}
}

/** Function to compute number of variable inputs of layer
 * Also populates corresponding indices of variable inputs
 */ 
int32_t TIDL_onnxNumVariableLayerInputs(GraphProto& onnGraph, int32_t i, std::vector<int32_t>& varIdx)
{
  int32_t numVarInputs = 0;
  for(int j = 0; j < onnGraph.node(i).input_size(); j++)
  {
    if(! TIDL_isInputConstInGraph(onnGraph, onnGraph.node(i).input(j)))
    {
      numVarInputs++;
      varIdx.push_back(j);
    }
  }
  return numVarInputs;
}

int32_t TIDL_onnxGetAttrIdx(const NodeProto& node, char * name)
{
  int32_t i;
  for (i = 0; i < node.attribute_size(); i++)
  {
    if ((strcmp(node.attribute(i).name().c_str(), name) == 0))
    {
      return(i);
    }
  }
  return (-1);
}

std::vector<int32_t> getNodeOutputShape(GraphProto& onnxGraph, const std::string name, int32_t debugLevel)
{
  std::vector<int32_t> dims;
  for (int k = 0; k < onnxGraph.output_size(); k++)
  {
    if((strcmp(onnxGraph.output(k).name().c_str(), name.c_str()) == 0))
    {
      if( onnxGraph.output(k).type().tensor_type().has_shape() )
      {
        auto& tensorShape = onnxGraph.output(k).type().tensor_type().shape();
        for (int j = 0; j < tensorShape.dim_size(); j++)
        {
          dims.push_back(tensorShape.dim(j).dim_value());
        }
      }
    }
  }
  for (int k = 0; k < onnxGraph.value_info_size(); k++)
  {
    if((strcmp(onnxGraph.value_info(k).name().c_str(), name.c_str()) == 0))
    {
      if( onnxGraph.value_info(k).type().tensor_type().has_shape() )
      {
        auto& tensorShape = onnxGraph.value_info(k).type().tensor_type().shape();
        for (int j = 0; j < tensorShape.dim_size(); j++)
        {
          dims.push_back(tensorShape.dim(j).dim_value());
        }
      }
    }
  }
  return dims;
}

std::vector<int32_t> getNodeInputShape(GraphProto& onnxGraph, const std::string name, int32_t debugLevel)
{
  std::vector<int32_t> dims;
  for (int k = 0; k < onnxGraph.input_size(); k++)
  {
    if((strcmp(onnxGraph.input(k).name().c_str(), name.c_str()) == 0))
    {
      if( onnxGraph.input(k).type().tensor_type().has_shape() )
      {
        auto& tensorShape = onnxGraph.input(k).type().tensor_type().shape();
        for (int j = 0; j < tensorShape.dim_size(); j++)
        {
          dims.push_back(tensorShape.dim(j).dim_value());
        }
      }
    }
  }

  for (int k = 0; k < onnxGraph.value_info_size(); k++)
  {
    if((strcmp(onnxGraph.value_info(k).name().c_str(), name.c_str()) == 0))
    {
      if( onnxGraph.value_info(k).type().tensor_type().has_shape() )
      {
        auto& tensorShape = onnxGraph.value_info(k).type().tensor_type().shape();
        for (int j = 0; j < tensorShape.dim_size(); j++)
        {
          dims.push_back(tensorShape.dim(j).dim_value());
        }
      }
    }
  }
  return dims;
}

int32_t TIDL_onnxGetIntAttr(const NodeProto& node, char * name, int32_t * valuePtr, int32_t idx)
{
  int32_t i = TIDL_onnxGetAttrIdx(node, name);
  if(i != -1)
  {
    if (node.attribute(i).ints_size() > idx)
    {
      *valuePtr = node.attribute(i).ints(idx);
    }
    else if (idx == 0)
    {
      *valuePtr = node.attribute(i).i();
    }
    else
    {
      return (-1);
    }
    return (0);
  }
  return (-1);
}

int32_t TIDL_onnxGetFloatAttr(const NodeProto& node, char * name, float * valuePtr, int32_t idx)
{
  int32_t i = TIDL_onnxGetAttrIdx(node, name);
  if (i != -1)
  {
    if (node.attribute(i).floats_size() > idx)
    {
      *valuePtr = node.attribute(i).floats(idx);
    }
    else if (idx == 0)
    {
      *valuePtr = node.attribute(i).f();
    }
    else
    {
      return (-1);
    }
    return (0);
  }
  return (-1);
}

int32_t TIDL_geTensorDim(TensorProto& tensor, int32_t idx)
{
  if (tensor.dims_size() > idx)
  {
    return(tensor.dims(idx));
  }
  else
  {
    return 0;
  }
}


int32_t TIDL_onnxGetStringAttr(const NodeProto& node, char * name, char * valuePtr, int32_t idx)
{
  strcpy(valuePtr, "");
  int32_t i = TIDL_onnxGetAttrIdx(node, name);
  if (i != -1)
  {
      strcpy(valuePtr, node.attribute(i).s().c_str());
      return (0);
  }
  return (-1);
}

TensorProto TIDL_getInitializerTensor(GraphProto& onnGraph, const string name, int32_t nIdx)
{
  int i;

  for (i = 0; i < onnGraph.initializer_size(); i++)
  {
    if ((strcmp(onnGraph.initializer(i).name().c_str(), name.c_str()) == 0))
    {
      auto & tensor = onnGraph.initializer(i);
      return(tensor);
    }
  }
  for (i = 0; i < onnGraph.node_size(); i++)
  {
    if ((strcmp(onnGraph.node(i).output(0).c_str(), name.c_str()) == 0) && (strcmp(onnGraph.node(i).op_type().c_str(), "Constant") == 0))
    {
      auto & tensor = onnGraph.node(i).attribute(0).t();
      return(tensor);
    }
  }
  printf("Could not find const or initializer of layer %s !!!", onnGraph.node(nIdx).name().c_str());
  return (onnx::TensorProto::default_instance());
}

int32_t TIDL_tfCopyTensor(TensorProto& tensor, void ** ptr, int32_t * size)
{
  int32_t i, tensorSize = 1;

  * ptr = NULL;
  if (tensor.data_type() == TensorProto_DataType_FLOAT) //DT_FLOAT
  {
    float *dst;
    for (i = 0; i < tensor.dims_size(); i++)
    {
      tensorSize *= tensor.dims(i);
    }
    *size = tensorSize;
    dst = (float *)my_malloc(*size *sizeof(float));

    if (tensor.float_data_size() > 0)
    {
      if (tensor.float_data_size() != tensorSize)
      {
        printf("Tensor size and Dims size not matching !! \n");
      }

      for (i = 0; i < tensorSize; i++)
      {
        dst[i] = tensor.float_data(i);
      }
    }
    else if (tensor.raw_data().size() > 0)
    {
      if ((tensor.raw_data().size() / sizeof(float)) != tensorSize)
      {
        printf("Tensor size and Dims size not matching !! \n");
      }
      memcpy(dst, (float *)tensor.raw_data().c_str(), tensor.raw_data().size());
    }
    *ptr = dst;
    return 0;
  }
  else if (tensor.data_type() == TensorProto_DataType_INT64) //DT_FLOAT
  {
    long long int *dst;
    for (i = 0; i < tensor.dims_size(); i++)
    {
      tensorSize *= tensor.dims(i);
    }
    *size = tensorSize;
    dst = (long long int *)my_malloc(*size *sizeof(long long int));

    if (tensor.int64_data_size() > 0)
    {
      if (tensor.int64_data_size() != tensorSize)
      {
        printf("Tensor size and Dims size not matching !! \n");
      }

      for (i = 0; i < tensorSize; i++)
      {
        dst[i] = tensor.int64_data(i);
      }
    }
    else if (tensor.raw_data().size() > 0)
    {
      if ((tensor.raw_data().size() / sizeof(long long int)) != tensorSize)
      {
        printf("Tensor size and Dims size not matching !! \n");
      }
      memcpy(dst, (long long int *)tensor.raw_data().c_str(), tensor.raw_data().size());
    }
    *ptr = dst;
    return 0;
  }
  else
  {
    printf("\nOnly float and INT64 tensor is supported \n");
    return -1;
  }
}

int32_t TIDL_tfCopyFloatInitializerTensor(GraphProto& onnGraph, int32_t nIdx, int32_t inIdx, sBuffer_t &buf)
{
  TensorProto tensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(nIdx).input(inIdx), nIdx);
  return TIDL_tfCopyTensor(tensor, &buf.ptr, &buf.bufSize);
}

int32_t TIDL_tfCopyFloatConst(GraphProto& onnGraph, int32_t nIdx, int32_t inIdx, sBuffer_t &buf)
{
  if (onnGraph.node(nIdx).input_size() >= (inIdx - 1))
  {
    TensorProto tensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(nIdx).input(inIdx), nIdx);
    TIDL_tfCopyTensor(tensor, &buf.ptr, &buf.bufSize);
  }
  else
  {
    printf("Requested Constant tensor %d in %s is not found", inIdx, onnGraph.node(nIdx).name().c_str());
    exit(0);
  }
  return 0;
}

/** Broadcast floating point vector buffer to have a modified dimension */
void TIDL_onnxBroadcastFloatTensor(sBuffer_t &buf, int32_t bufSize)
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

/** Function to save layer level tensor properties metadata to be used for allowlisting 
 * Saves data for sTIDL_allowlistingMetaData structure
 */
void TIDL_onnxSaveAllowlistingMetaData(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.allowlistingMetaData.numInputs = onnGraph.node(i).input_size();
  layer.allowlistingMetaData.numOutputs = onnGraph.node(i).output_size();
  layer.allowlistingMetaData.numValidInputs = layer.allowlistingMetaData.numInputs;
  layer.allowlistingMetaData.validInputIndices = {};
  layer.allowlistingMetaData.numVarInputs = TIDL_onnxNumVariableLayerInputs(onnGraph, i,  layer.allowlistingMetaData.varTensorIndices);
  layer.allowlistingMetaData.numConstInputs = layer.allowlistingMetaData.numValidInputs - layer.allowlistingMetaData.numVarInputs;
  
  //Find indices of constant tensors
  for(int j = 0; j < onnGraph.node(i).input_size(); j++)
  {
    if(std::find(layer.allowlistingMetaData.varTensorIndices.begin(), layer.allowlistingMetaData.varTensorIndices.end(), j) == layer.allowlistingMetaData.varTensorIndices.end()) 
    //idx not found in variable tensors indices => constant tensor idx
    {
      layer.allowlistingMetaData.constTensorIndices.push_back(j);
    }
  }
  //Populate dimensions of variable tensors
  for(auto& varIdx : layer.allowlistingMetaData.varTensorIndices)
  {
    layer.allowlistingMetaData.varTensorsDims.push_back(getNodeInputShape(onnGraph,  onnGraph.node(i).input(varIdx), 0));
  }
  //Populate dimensions of constant tensors
  for(auto& constIdx : layer.allowlistingMetaData.constTensorIndices)
  {
    TensorProto tensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(constIdx), i);
    std::vector<int32_t> dims;
    for(int j = 0; j < tensor.dims_size(); j++)
    {
      dims.push_back(tensor.dims(j));
    }
    layer.allowlistingMetaData.constTensorsDims.push_back(dims);
  }
  //Populate dimensions of output tensors
  for(int outputIdx=0; outputIdx<layer.allowlistingMetaData.numOutputs; outputIdx++)
  {
    layer.allowlistingMetaData.outputTensorDims.push_back(getNodeOutputShape(onnGraph,  onnGraph.node(i).output(outputIdx), 0));
  }
}

/* Check if Reshape-Transpose-Reshape corresponds to channel-wise shuffle operation */
bool TIDL_checkShuffleOperation(GraphProto& onnxGraph, std::vector<int>supportedNodesIndices)
{
  bool isSupported = false;
  sBuffer_t reshape1OutShape, reshape2OutShape, transposeOutShape;

  int32_t reshape1Idx = supportedNodesIndices[0];
  int32_t transposeIdx = supportedNodesIndices[1];
  int32_t reshape2Idx = supportedNodesIndices[2];

  TIDL_tfCopyFloatInitializerTensor(onnxGraph, reshape1Idx, 1, reshape1OutShape);
  TIDL_tfCopyFloatInitializerTensor(onnxGraph, reshape2Idx, 1, reshape2OutShape);
  NodeProto node = onnxGraph.node(transposeIdx);
  int32_t attrIdx = TIDL_onnxGetAttrIdx(node, "perm");
  if (attrIdx != -1)
  {
    int32_t j;
    int32_t dims = node.attribute(attrIdx).ints_size();
    transposeOutShape.ptr = (void*)malloc(sizeof(int)*dims);
    transposeOutShape.bufSize = dims;
    int32_t *dimVlaue = (int*)transposeOutShape.ptr;
    for (j = 0; j < transposeOutShape.bufSize; j++)
    {
      dimVlaue[j] = node.attribute(attrIdx).ints(j);
    }
  }
  if ((reshape1OutShape.bufSize ==  5) && (transposeOutShape.bufSize ==  5) && (reshape2OutShape.bufSize == 4))
  {
    int64_t * reshape1  = (int64_t *)reshape1OutShape.ptr;
    int64_t * reshape2  = (int64_t *)reshape2OutShape.ptr;
    int32_t * transpose = (int32_t *)transposeOutShape.ptr;
    if ((reshape1[4] == reshape2[3]) && (reshape1[3] == reshape2[2]) && (4 == transpose[4]) && (3 == transpose[3]) && (1 == transpose[2]) && (2 == transpose[1]))
    {
      isSupported = true;
    }
  }
  if ((reshape1OutShape.bufSize ==  6) && (transposeOutShape.bufSize ==  6) && (reshape2OutShape.bufSize == 4))
  {
    int64_t * reshape1  = (int64_t *)reshape1OutShape.ptr;
    int64_t * reshape2  = (int64_t *)reshape2OutShape.ptr;
    int32_t * transpose = (int32_t *)transposeOutShape.ptr;
    if ((reshape1[4]*reshape1[2] == reshape2[2]) && (reshape1[3]*reshape1[5] == reshape2[3]) && (reshape1[1] == reshape2[1]) && (reshape1[2] == reshape1[3]) &&
        (3 == transpose[5]) && (5 == transpose[4]) && (2 == transpose[3]) && (4 == transpose[2]) && (1 == transpose[1]))
    {
      isSupported = true;
    }
    if(TIDL_isDevice("am62a")) /* Pixel shuffle layer is not supported on AM62A */
    {
      isSupported = false;
    }
  }

  return isSupported;
}

int32_t TIDL_onnxMapConvBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status;
  int32_t padType;
  int32_t idx1, idx2;
  int32_t pads[4] = {0};
  int32_t kernel_shape[2];
  int32_t padL=-1, padR=-1, padT=-1, padB=-1;
  
  sTIDL_ConvParams_t &convParams      = layer.layerParams.convParams;
  layer.layerType = TIDL_ConvolutionLayer;

  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);

  layer.strideOffsetMethod = TIDL_StrideOffsetTopLeft;

  layer.outData[0].elementType = tidl_getElementType(1);

  TensorProto tensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(1), i);
  convParams.numOutChannels = TIDL_geTensorDim(tensor, 0);
  convParams.numInChannels  = TIDL_geTensorDim(tensor, 1);
  convParams.kernelH        = TIDL_geTensorDim(tensor, 2);
  convParams.kernelW        = TIDL_geTensorDim(tensor, 3);

  convParams.numGroups = 1;
  convParams.dilationW = 1;
  convParams.dilationH = 1;
  convParams.strideW = 1;
  convParams.strideH = 1;
  convParams.padW = 0;
  convParams.padH = 0;
  convParams.enableBias = 0;
  convParams.enablePooling = 0;

  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "strides",   &convParams.strideH, 0);
  TIDL_onnxGetIntAttr(node, "strides",   &convParams.strideW, 1);
  TIDL_onnxGetIntAttr(node, "dilations", &convParams.dilationH, 0);
  TIDL_onnxGetIntAttr(node, "dilations", &convParams.dilationW, 1);
  TIDL_onnxGetIntAttr(node, "group",     &convParams.numGroups, 0);
  TIDL_onnxGetIntAttr(node, "kernel_shape", &kernel_shape[0], 0);
  TIDL_onnxGetIntAttr(node, "kernel_shape", &kernel_shape[1], 1);

  char autoPad[50];
  status = TIDL_onnxGetStringAttr(node, "auto_pad", autoPad, 0);
  if((status == -1) || (strcmp(autoPad, "NOTSET") == 0))
  {
    TIDL_onnxGetIntAttr(node, "pads",       &pads[0], 0);
    TIDL_onnxGetIntAttr(node, "pads",       &pads[1], 1);
    TIDL_onnxGetIntAttr(node, "pads",       &pads[2], 2);
    TIDL_onnxGetIntAttr(node, "pads",       &pads[3], 3);
    if((pads[0] < pads[2]) && (pads[1] < pads[3])) //padL < padR && padT < padB
    {
      layer.strideOffsetMethod = TIDL_StrideOffsetCenter;
    }
    pads[2] = max(pads[0], pads[2]);
    pads[3] = max(pads[1], pads[3]);
    padL = pads[1];
    padR = pads[3];
    padT = pads[0];
    padB = pads[2];
  }
  else if ((strcmp(autoPad, "SAME_UPPER") == 0) || (strcmp(autoPad, "SAME_LOWER") == 0))
  {
    /* TCs pertaining to this condition are not existent as of now, hence this cannot be validated */
    pads[3] = ((convParams.kernelW - 1)*convParams.dilationW) / 2;
    pads[2] = ((convParams.kernelH - 1)*convParams.dilationH) / 2;
    if(strcmp(autoPad, "SAME_UPPER") == 0)
    {
      layer.strideOffsetMethod = TIDL_StrideOffsetCenter;
    }
    else  //SAME_LOWER
    {
      layer.strideOffsetMethod = TIDL_StrideOffsetTopLeft;
    }
  }
  else if(strcmp(autoPad, "VALID") == 0)
  {
    pads[3] = 0;
    pads[2] = 0;
    padL = 0; 
    padR = 0; 
    padT = 0; 
    padB = 0;
  }
  else
  {
    diagsInfo.push_back("ALLOWLISTING : CONV : Unsupported auto_pad attribute  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__));
    return -1;
  }



/*
if ((pads[0] != 0) || (pads[1] != 0))
  {
    printf("Pading Only supported in H and W axis \n");
  }
*/
  convParams.padW = pads[3];
  convParams.padH = pads[2];

  convParams.padT = padT;
  convParams.padL = padL;
  convParams.padB = padB;
  convParams.padR = padR;

  if ((kernel_shape[0] != convParams.kernelH) || (kernel_shape[1] != convParams.kernelW))
  {
    printf("Weight Tensor size is not matching with Proto kernel_shape \n");
  }
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 1, layer.weights);
  if (onnGraph.node(i).input_size() > 2)
  {
    convParams.enableBias = 1;
    TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 2, layer.bias);
  }

  return 0;
}


int32_t TIDL_onnxMapConvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapConvBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapConvTransposeBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status;
  int32_t padType;
  int32_t idx1, idx2;
  sTIDL_ConvParams_t &convParams = layer.layerParams.convParams;
  int32_t pads[4];
  int32_t kernel_shape[2];
  int32_t output_shape[2];

  layer.layerType = TIDL_Deconv2DLayer;

  layer.strideOffsetMethod = TIDL_StrideOffsetTopLeft;

  layer.outData[0].elementType = tidl_getElementType(1);

  TensorProto tensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(1), i);
  convParams.numInChannels =  TIDL_geTensorDim(tensor, 0);
  convParams.kernelH =        TIDL_geTensorDim(tensor, 2);
  convParams.kernelW =        TIDL_geTensorDim(tensor, 3);

  convParams.numGroups = 1;
  convParams.dilationW = 1;
  convParams.dilationH = 1;
  convParams.strideW = 1;
  convParams.strideH = 1;
  convParams.padW = 0;
  convParams.padH = 0;
  convParams.enableBias = 0;
  convParams.enablePooling = 0;

  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "strides", &convParams.strideH, 0);
  TIDL_onnxGetIntAttr(node, "strides", &convParams.strideW, 1);
  TIDL_onnxGetIntAttr(node, "dilations", &convParams.dilationH, 0);
  TIDL_onnxGetIntAttr(node, "dilations", &convParams.dilationW, 1);
  TIDL_onnxGetIntAttr(node, "group", &convParams.numGroups, 0);
  TIDL_onnxGetIntAttr(node, "kernel_shape", &kernel_shape[0], 0);
  TIDL_onnxGetIntAttr(node, "kernel_shape", &kernel_shape[1], 1);

  convParams.numOutChannels = TIDL_geTensorDim(tensor, 1) * convParams.numGroups;

  status = TIDL_onnxGetIntAttr(node, "output_shape", &output_shape[0], 0);
  if(status != -1)
  {
    TIDL_onnxGetIntAttr(node, "output_shape", &output_shape[0], 0);
    TIDL_onnxGetIntAttr(node, "output_shape", &output_shape[1], 1);

    layer.outData[0].dimValues[TIDL_DIM_HEIGHT] = -output_shape[0];
    layer.outData[0].dimValues[TIDL_DIM_WIDTH]  = -output_shape[1];

    pads[3] = ((convParams.kernelW - 1)*convParams.dilationW) / 2;
    pads[2] = ((convParams.kernelH - 1)*convParams.dilationH) / 2;
  }
  else
  {
    char autoPad[50];
    status = TIDL_onnxGetStringAttr(node, "auto_pad", autoPad, 0);
    if((status == -1) || (strcmp(autoPad, "NOTSET") == 0))
    {
      TIDL_onnxGetIntAttr(node, "pads",       &pads[0], 0);
      TIDL_onnxGetIntAttr(node, "pads",       &pads[1], 1);
      TIDL_onnxGetIntAttr(node, "pads",       &pads[2], 2);
      TIDL_onnxGetIntAttr(node, "pads",       &pads[3], 3);

      if((pads[0] < pads[2]) && (pads[1] < pads[3])) //padL < padR && padT < padB
      {
        layer.strideOffsetMethod = TIDL_StrideOffsetCenter;
      }
      pads[2] = max(pads[0], pads[2]);
      pads[3] = max(pads[1], pads[3]);
    }
    else if ((strcmp(autoPad, "SAME_UPPER") == 0) || (strcmp(autoPad, "SAME_LOWER") == 0))
    {
      pads[3] = ((convParams.kernelW - 1)*convParams.dilationW) / 2;
      pads[2] = ((convParams.kernelH - 1)*convParams.dilationH) / 2;
      if(strcmp(autoPad, "SAME_UPPER") == 0)
      {
        layer.strideOffsetMethod = TIDL_StrideOffsetCenter;
      }
      else  //SAME_LOWER
      {
        layer.strideOffsetMethod = TIDL_StrideOffsetTopLeft;
      }
    }
    else if(strcmp(autoPad, "VALID") == 0)
    {
      pads[3] = 0;
      pads[2] = 0;
    }
    else
    {
      diagsInfo.push_back("ALLOWLISTING : CONV : Unsupported auto_pad attribute  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__));
      return -1;
    }
  }


/*
if ((pads[0] != 0) || (pads[1] != 0))
  {
    printf("Pading Only supported in H and W axis \n");
  }
*/
  convParams.padW = pads[3];
  convParams.padH = pads[2];
  if ((kernel_shape[0] != convParams.kernelH) || (kernel_shape[1] != convParams.kernelW))
  {
    printf("Weight Tensor size is not matching with Proto kernel_shape \n");
  }
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 1, layer.weights);
  if (onnGraph.node(i).input_size() > 2)
  {
    convParams.enableBias = 1;
    TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 2, layer.bias);
  }
   return 0;
}

int32_t TIDL_onnxMapConvTransposeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapConvTransposeBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapSplitBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status, j;
  int32_t axis;
  int32_t splitSize, splitIdx;
  sTIDL_SliceLayerParams_t &sliceParams = layer.layerParams.sliceParams;

  layer.layerType = TIDL_SliceLayer;
  layer.numOutBufs = onnGraph.node(i).output_size();
  sliceParams.stride = 1;
  for (j = 0; j < layer.numOutBufs; j++)
  {
    layer.outData[j].elementType = tidl_getElementType(1);
  }

  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "axis", &axis, 0);
  if (axis == 0)
  {
    printf("\n Unsupported slice - axis parameters, in Slice ");
    return -1;
  }
  layer.layerParams.sliceParams.axis = axis;
  splitIdx = TIDL_onnxGetAttrIdx(node, "split");

  if (splitIdx != -1)
  {
    splitSize = node.attribute(splitIdx).ints_size();
    if(splitSize != layer.numOutBufs)
    {
      printf("\n Unsupported slice - axis parameters, in Slice");
      return -1;
    }
    sliceParams.slicePoints[0] = 0;
    for (j = 0; j < layer.numOutBufs; j++)
    {
      /* split attribute of split layer indicates the length of each slice */
      sliceParams.slicePoints[j+1] = sliceParams.slicePoints[j] + node.attribute(splitIdx).ints(j);
    }
  }
  else
  {
    for (j = 0; j < layer.numOutBufs; j++)
    {
      sliceParams.slicePoints[j] = -1;
    }
  }
   return 0;
}
int32_t TIDL_onnxSplitParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status, j;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.numOutBufs = onnGraph.node(i).output_size();
  for (j = 0; j < TIDLPCLayers.numOutBufs; j++)
  {
    TIDLPCLayers.outData[j].dataId = (*dataIndex)++;
  }
  status = TIDL_onnxMapSplitBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapSliceBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status, j;
  int32_t axis = 0;
  int32_t starts;
  sTIDL_SliceLayerParams_t &sliceParams = layer.layerParams.sliceParams;

  layer.layerType  = TIDL_SliceLayer;

  NodeProto node = onnGraph.node(i);
  sliceParams.stride = 1;

  if (onnxOpSetVersion == 9)
  {
    TIDL_onnxGetIntAttr(node, "axes", &axis, 0);

    TIDL_onnxGetIntAttr(node, "starts", &sliceParams.slicePoints[0], 0);
    TIDL_onnxGetIntAttr(node, "ends", &sliceParams.slicePoints[1], 0);
  }
  else if (onnxOpSetVersion == 11)
  {
    if(node.input_size() < 4)
    {
      axis = 0;
    }
    else
    {
      if (node.input_size() == 5)
      {
        sBuffer_t buf;
        TIDL_tfCopyFloatConst(onnGraph, i, 4, buf);
        long long int *ptr = (long long int *)buf.ptr;
        if (ptr[0] != 1)
        {
          sliceParams.stride = ptr[0];
          printf("\n Step != 1 is NOT supported for Slice Operator -- %s \n", onnGraph.node(i).name().c_str());
        }
        free(ptr);
      }

      sBuffer_t starts;
      TIDL_tfCopyFloatConst(onnGraph, i, 1, starts);
      long long int *startsPtr = (long long int *)starts.ptr;

      sBuffer_t ends;
      TIDL_tfCopyFloatConst(onnGraph, i, 2, ends);
      long long int *endsPtr = (long long int *)ends.ptr;

      sBuffer_t axes;
      TIDL_tfCopyFloatConst(onnGraph, i, 3, axes);
      long long int *axesPtr = (long long int *)axes.ptr;

      if(starts.bufSize > 1)
      {
        axis = 0;
      }
      else
      {
        sliceParams.slicePoints[0] = startsPtr[0];
        sliceParams.slicePoints[1] = endsPtr[0];
        axis = axesPtr[0];
      }
      free(startsPtr);
      free(endsPtr);
      free(axesPtr);
    }
  }
  else
  {
    printf("\n Slice layer : Unsupported onnxOpSetVersion %d -- %s\n", onnxOpSetVersion, onnGraph.node(i).name().c_str());
    return -1;
  }
  layer.layerParams.sliceParams.axis = axis;

  if ((axis < 1) || (axis > 3))
  {
    printf("\n Unsupported slice - axis parameters, in Slice -- %s \n", onnGraph.node(i).name().c_str());
  }
  return 0;
}
int32_t TIDL_onnxSliceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapSliceBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxGemmBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  int32_t transA = 0;
  int32_t transB = 1;
  float alpha = 1.0;
  float beta  = 1.0;
  sTIDL_InnerProductParams_t &innerProductParams = layer.layerParams.innerProductParams;
  
  layer.layerType = TIDL_InnerProductLayer;
  layer.outData[0].elementType = tidl_getElementType(1);
  
  //Do ONNX attribute checks
  NodeProto node = onnGraph.node(i);
  std::vector<int32_t> attr;
  attr.push_back(TIDL_onnxGetIntAttr(node, "transA", &transA, 0));
  attr.push_back(TIDL_onnxGetIntAttr(node, "transB", &transB, 0));
  attr.push_back(TIDL_onnxGetFloatAttr(node, "alpha", &alpha, 0));
  attr.push_back(TIDL_onnxGetFloatAttr(node, "beta", &beta, 0));

  if ((transA != 0) || (transB != 1) || (alpha != 1.0) || (beta != 1.0))
  {
    diagsInfo.push_back("ALLOWLISTING : GEMM : Only supported Gemm Params are transA = 0, transB = 1, alpha = 1.0 and beta = 1.0. The same will processed as Inner product or fully connected layer in TIDL  -- file info - "\
     + std::string(__FILE__) + " , " + std::string(__func__) + " , " + std::to_string(__LINE__));
    return -1;
  }
  
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  
  status = TIDL_checkInnerProductTensorProperties(layer);
  if(status == -1) return -1;

  sTIDL_allowlistingMetaData md = layer.allowlistingMetaData;

  if((md.constTensorIndices.size() == 1) || (md.constTensorIndices.size() == 2)) //filter, bias
  {
    int32_t filterIdx = md.constTensorIndices[0]; //first constant tensor should be filter
    TensorProto filterTensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(filterIdx), i);
    
    innerProductParams.numOutNodes = filterTensor.dims(0);
    innerProductParams.numInNodes = filterTensor.dims(1);

    layer.inData[0].dimValues[TIDL_DIM_BATCH]  = 1;
    layer.inData[0].dimValues[TIDL_DIM_NUMCH]  = 1;
    layer.inData[0].dimValues[TIDL_DIM_HEIGHT] = 1;
    layer.inData[0].dimValues[TIDL_DIM_WIDTH]  = innerProductParams.numInNodes;
    layer.outData[0].dimValues[TIDL_DIM_WIDTH] = innerProductParams.numOutNodes;

    status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, filterIdx, layer.weights);
    if(status == -1)
    {
      diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
      + std::string(__func__) + " , " + std::to_string(__LINE__));
      return -1;
    }
    
    if(md.constTensorIndices.size() == 2) //both weight and bias present
    {
      int32_t biasIdx = md.constTensorIndices[1]; //2nd constant tensor should be bias      
      TensorProto biasTensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(biasIdx), i);

      status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, biasIdx, layer.bias);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
        return -1;
      }
    }
    else  //bias tensor not specified, values should default to 0
    {
      layer.bias.ptr = calloc(innerProductParams.numOutNodes, sizeof(float));
      layer.bias.bufSize = innerProductParams.numOutNodes;
    }
  }
  return 0;
}

int32_t TIDL_onnxGemmParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxGemmBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapSoftmaxBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_SoftMaxLayer;
  return 0;
}

int32_t TIDL_onnxSoftmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapSoftmaxBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

void TIDL_tfBNToScaleBias(
  float    * scale,
  float    * bias,
  uint32_t  numCh,
  float * mean,
  float * var,
  float * gamma,
  float * beta,
  float eps
  );

int32_t TIDL_onnxMapBNBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  sBuffer_t gamma;
  sBuffer_t beta;
  sBuffer_t mean;
  sBuffer_t variance;
  float epsilon = 1e-05;
  int32_t dataSize;

  layer.layerType = TIDL_BatchNormLayer;
  NodeProto node = onnGraph.node(i);
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 1, gamma);
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 2, beta);
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 3, mean);
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 4, variance);
  TIDL_onnxGetFloatAttr(node, "epsilon", &epsilon, 0);

  dataSize = gamma.bufSize;
  layer.weights.ptr = my_malloc(dataSize*sizeof(float));
  layer.weights.bufSize = dataSize;
  layer.bias.ptr = my_malloc(dataSize*sizeof(float));
  layer.bias.bufSize = dataSize;


  TIDL_tfBNToScaleBias((float *)layer.weights.ptr,
    (float *)layer.bias.ptr, dataSize,
    (float *)mean.ptr, (float *)variance.ptr, (float *)gamma.ptr, (float *)beta.ptr, epsilon
    );
  my_free(mean.ptr);
  my_free(variance.ptr);
  my_free(gamma.ptr);
  my_free(beta.ptr);

  return 0;
}

int32_t TIDL_onnxMapBNParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapBNBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapMaxPoolBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  status = TIDL_checkPoolingTensorProperties(layer);
  if(status == -1) return -1;
  
  int32_t padType;
  int32_t idx1, idx2;
  int32_t pads[4] = {0};
  sTIDL_PoolingParams_t &poolParams = layer.layerParams.poolParams;
  layer.layerType = TIDL_PoolingLayer;
  poolParams.poolingType = TIDL_MaxPooling;
  poolParams.strideW = 1;
  poolParams.strideH = 1;
  poolParams.padW = 0;
  poolParams.padH = 0;
  poolParams.useCeil = 0;
  NodeProto node = onnGraph.node(i);

  std::vector<int32_t> attr;
  attr.push_back(TIDL_onnxGetIntAttr(node, "kernel_shape", &poolParams.kernelW, 1));
  attr.push_back(TIDL_onnxGetIntAttr(node, "kernel_shape", &poolParams.kernelH, 0));

  if(TIDL_onnxGetAttrIdx(node, "strides") != -1)
  {
    attr.push_back(TIDL_onnxGetIntAttr(node, "strides", &poolParams.strideW, 1));
    attr.push_back(TIDL_onnxGetIntAttr(node, "strides", &poolParams.strideH, 0));
  }

  char autoPad[50];
  status = TIDL_onnxGetStringAttr(node, "auto_pad", autoPad, 0);
  if((status == -1) || (strcmp(autoPad, "NOTSET") == 0))
  {
    if(TIDL_onnxGetAttrIdx(node, "pads") != -1)
    {
      attr.push_back(TIDL_onnxGetIntAttr(node, "pads",       &pads[0], 0));
      attr.push_back(TIDL_onnxGetIntAttr(node, "pads",       &pads[1], 1));
      attr.push_back(TIDL_onnxGetIntAttr(node, "pads",       &pads[2], 2));
      attr.push_back(TIDL_onnxGetIntAttr(node, "pads",       &pads[3], 3));
      if((pads[0] < pads[2]) && (pads[1] < pads[3]) && (poolParams.strideW != 1) && (poolParams.strideH != 1)) //padL < padR && padT < padB
      {
        /* This condition will occur when stride = 2 and size of input tensor is even 
          strideOffsetMethod is not handled in pooling layer, so take care of this in TIDL_tfOutReshapePoolingLayer */
        layer.strideOffsetMethod = TIDL_StrideOffsetCenter;
      }
      pads[2] = max(pads[0], pads[2]);
      pads[3] = max(pads[1], pads[3]);
    }
  }
  else if ((strcmp(autoPad, "SAME_UPPER") == 0) || (strcmp(autoPad, "SAME_LOWER") == 0))
  {
    if(poolParams.strideW > 1)
    {
      pads[3] = (poolParams.kernelW - 1) / 2;
    }
    else
    {
      pads[3] = poolParams.kernelW / 2;
    }
    if(poolParams.strideH > 1)
    {
      pads[2] = (poolParams.kernelH - 1) / 2;
    }
    else
    {
      pads[2] = poolParams.kernelH / 2;
    }

    if(strcmp(autoPad, "SAME_UPPER") == 0)
    {
      layer.strideOffsetMethod = TIDL_StrideOffsetCenter;
    }
    else  //SAME_LOWER
    {
      layer.strideOffsetMethod = TIDL_StrideOffsetTopLeft;
    }
  }
  else if(strcmp(autoPad, "VALID") == 0)
  {
    pads[3] = 0;
    pads[2] = 0;
  }
  else
  {
    diagsInfo.push_back("ALLOWLISTING : MAX POOL : Unsupported auto_pad attribute  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
    return -1;
  }

  if(std::find(attr.begin(), attr.end(), -1) != attr.end())
  {
    diagsInfo.push_back("ALLOWLISTING : MAX POOL : Missing attribute  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
    return -1;
  }

  poolParams.padW = pads[3];
  poolParams.padH = pads[2];

  return 0;
}

int32_t TIDL_onnxMapMaxPoolParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapMaxPoolBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapArgmaxBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status;
  int32_t axis, keepdim;
  sTIDL_ArgMaxParams_t &argMaxParams = layer.layerParams.argMaxParams;
  layer.layerType = TIDL_ArgMaxLayer;

  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "axis", &axis, 0);
  TIDL_onnxGetIntAttr(node, "keepdims", &keepdim, 0);
  if (keepdim != 1)
  {
    printf("Warning : only keepdims = 1 supported for Argmax Layer - forcing it to be 1 \n");
  }
  if (axis != 1)
  {
    printf("Only axis = 1 supported for Argmax Layer \n");
    return -1;
  }
  return 0;
}
int32_t TIDL_onnxMapArgmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapArgmaxBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapReluBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ReLULayer;
  layer.actParams.actType = TIDL_RelU;
  return 0;
}

int32_t TIDL_onnxMapReluParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapReluBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapClipBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ClipLayer;
  layer.actParams.actType = TIDL_Clip;
  NodeProto node = onnGraph.node(i);

  if ((onnxOpSetVersion >= 6) && (onnxOpSetVersion < 11))
  {
    TIDL_onnxGetFloatAttr(node, "min", &layer.actParams.clipMin, 0);
    TIDL_onnxGetFloatAttr(node, "max", &layer.actParams.clipMax, 0);
  }
  else if (onnxOpSetVersion == 11)
  {
    int32_t numInputs = node.input_size();
    float min;
    float max;
    sBuffer_t buf;

    min = std::numeric_limits<float>::lowest();
    max = std::numeric_limits<float>::max();

    if ( numInputs > 1 )
    {
      TIDL_tfCopyFloatConst(onnGraph, i, 1, buf);
      float *ptr = (float *)buf.ptr;
      layer.actParams.clipMin = *ptr;
      my_free(ptr);
    }

    if ( numInputs > 2 )
    {
      TIDL_tfCopyFloatConst(onnGraph, i, 2, buf);
      float *ptr = (float *)buf.ptr;
      layer.actParams.clipMax = *ptr;
      my_free(ptr);
    }

  }
  else
  {
    printf("Unsupported OpSet Version for this operator %d \n", onnxOpSetVersion);
  }

  return 0;
}

int32_t TIDL_onnxMapClipParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapClipBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapPReluBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status;
  status = TIDL_onnxMapReluBaseParams(onnGraph, i, layer);
  layer.actParams.actType = TIDL_PRelU;
  return 0;
}

int32_t TIDL_onnxMapPReluParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapPReluBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapSigmoidBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_SigmoidLayer;
  layer.actParams.actType = TIDL_Sigmoid;
  layer.outData[0].elementType = tidl_getElementType(0);
  return 0;
}

int32_t TIDL_onnxMapSigmoidParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapSigmoidBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapTanhBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_TanhLayer;
  layer.actParams.actType = TIDL_Tanh;
  layer.outData[0].elementType = tidl_getElementType(1);
  return 0;
} 

int32_t TIDL_onnxMapTanhParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_checkNonLinearLUTLayersStandAlone(TIDLPCLayers);
  if(status == TIDL_ALLOWLISTING_LAYER_CHECK_FAILED)
  {
    return status;
  }
  status = TIDL_onnxMapTanhBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapHardSigmoidBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_HardSigmoidLayer;
  layer.actParams.actType = TIDL_HardSigmoid;
  layer.outData[0].elementType = tidl_getElementType(0);
  sTIDL_HardSigmoidParams_t &hardSigmoidParams      = layer.layerPCParams.hardSigmoidParams;
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetFloatAttr(node, "alpha",   &hardSigmoidParams.alpha, 0);
  hardSigmoidParams.beta = 0.5;
  return 0;
} 

int32_t TIDL_onnxMapHardSigmoidParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_checkNonLinearLUTLayersStandAlone(TIDLPCLayers);
  if(status == TIDL_ALLOWLISTING_LAYER_CHECK_FAILED)
  {
    return status;
  }
  status = TIDL_onnxMapHardSigmoidBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapELUBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ELULayer;
  layer.actParams.actType = TIDL_ELU;
  layer.outData[0].elementType = tidl_getElementType(1);
  sTIDL_EluParams_t &eluParams      = layer.layerPCParams.eluParams;
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetFloatAttr(node, "alpha",   &eluParams.alpha, 0);
  return 0;
} 

int32_t TIDL_onnxMapELUParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_checkNonLinearLUTLayersStandAlone(TIDLPCLayers);
  if(status == TIDL_ALLOWLISTING_LAYER_CHECK_FAILED)
  {
    return status;
  }
  status = TIDL_onnxMapELUBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapLeakyReluBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_LeakyReluLayer;
  layer.outData[0].elementType = tidl_getElementType(1);
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetFloatAttr(node, "alpha", &layer.layerPCParams.leakyReluParams.alpha, 0);
  return 0;
}
int32_t TIDL_onnxMapLeakyReluParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapLeakyReluBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapFlattenBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_FlattenLayer;
  return 0;
}
int32_t TIDL_onnxMapFlattenParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapFlattenBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapPadBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t idx, j;
  layer.layerType = TIDL_PadLayer;

  NodeProto node = onnGraph.node(i);
  int32_t padT, padB, padL, padR;

  if (onnxOpSetVersion < 11)
  {
    int32_t atrIdx = TIDL_onnxGetAttrIdx(node, "pads");

    int32_t * padValStore = (int32_t *)my_malloc(node.attribute(atrIdx).ints_size() * sizeof(int32_t));

    for (j = 0; j < node.attribute(atrIdx).ints_size(); j++)
    {
      TIDL_onnxGetIntAttr(node, "pads", &padValStore[j], j);
    }
    if ( ( padValStore[0] != 0 ) || ( padValStore[1] != 0 ) ||
     ( padValStore[4] != 0 ) || ( padValStore[5] != 0 ) )
    {
      printf("ERROR : Padding is only supported in Width/height axis \n");
      return -1;
    }
    padT = padValStore[2];
    padB = padValStore[6];
    padL = padValStore[3];
    padR = padValStore[7];
    my_free(padValStore);
  }
  else if (onnxOpSetVersion < 13)
  {
    sBuffer_t buf;
    TIDL_tfCopyFloatConst(onnGraph, i, 1, buf);
    int64_t *padPtr = (int64_t *)buf.ptr;

    if ( ( padPtr[0] != 0 ) || ( padPtr[1] != 0 ) ||
         ( padPtr[4] != 0 ) || ( padPtr[5] != 0 ) )
    {
      printf("ERROR : Padding is only supported in Width/height axis \n");
      return -1;
    }
    padT = padPtr[2];
    padB = padPtr[6];
    padL = padPtr[3];
    padR = padPtr[7];
    my_free(buf.ptr);
  }
  else
  {
    /* Pad Layer Opset 13 and up is not supported */
    printf("ERROR : Opset 13 pad is not supported \n");
    return -1;
  }
  layer.layerParams.padLayerParams.padT = padT;
  layer.layerParams.padLayerParams.padB = padB;
  layer.layerParams.padLayerParams.padL = padL;
  layer.layerParams.padLayerParams.padR = padR;
  return 0;
}
int32_t TIDL_onnxMapPadParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapPadBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapAddBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  status = TIDL_checkAddMulSubDivTensorProperties(layer,BASE_OP_ADD);
  if(status == -1) return -1;

  sTIDL_allowlistingMetaData md = layer.allowlistingMetaData;
  int32_t is1DConstTensor = checkDimConstTensor (md);
  if(md.numConstInputs > 0) //addition with constant tensor
  {
    int constTensorIdx = md.constTensorIndices[0];
    if (is1DConstTensor == 1)
    {
      TensorProto constTensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(constTensorIdx), i);
      
      int32_t varTensorIdx = md.varTensorIndices[0];
      
      if(constTensor.dims_size() == 0) //tensor dim size = 0 --- Add constant to layer
      {
          layer.layerType = TIDL_BatchNormLayer;
          status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.bias);
          if(status == -1)
          {
            diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
            + std::string(__func__) + " , " + std::to_string(__LINE__));
            return -1;
          }
          int32_t biasSize = md.varTensorsDims[0][TIDL_DIM_NUMCH]; //broadcast the constant along number of channels
          if(constTensor.data_type() == TensorProto_DataType_FLOAT)
          {
            TIDL_onnxBroadcastFloatTensor(layer.bias, biasSize);
          }
          else
          {
            std::string diagMsg = "ALLOWLISTING : ADD layer : Supported only if data type of constant is float  --  file info - " + std::string(__FILE__) + " , " \
            + std::string(__func__) + " , " + std::to_string(__LINE__);
            diagsInfo.push_back(diagMsg);
            return -1;
          }
      }
      else //addition with constant vector
      {
        layer.layerType = TIDL_BatchNormLayer;
        status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.bias);
        if(status == -1)
        {
          diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
            + std::string(__func__) + " , " + std::to_string(__LINE__)); 
          return -1;
        }
      }

      layer.weights.ptr             = my_malloc(layer.bias.bufSize*sizeof(float));
      layer.weights.bufSize         = layer.bias.bufSize;
      float *ptr = (float *)layer.weights.ptr;
      for (int lc = 0; lc < layer.weights.bufSize; lc++)
        ptr[lc] = 1.0;
      return 0;
    }
    else 
    {
      //Multiply with constant tensor
      layer.layerType = TIDL_EltWiseLayer;
      layer.layerParams.eltWiseParams.eltWiseType = TIDL_EltWiseSum;
      layer.numInBufs = md.numInputs;      
      status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.weights);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__)); 
        return -1;
      }
    }
  }
  else //both inputs variable
  {
    layer.layerType = TIDL_EltWiseLayer;
    layer.layerParams.eltWiseParams.eltWiseType = TIDL_EltWiseSum;
    layer.numInBufs = md.numInputs;
  }
  return 0;
}

int32_t TIDL_onnxMapAddParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapAddBaseParams(onnGraph, i, TIDLPCLayers);

  return status;
}

int32_t TIDL_onnxMapSubBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  if(gParams.modelType == TIDL_IMPORT_MODEL_FORMAT_ONNX )
  {
    printf("*** WARNING : Subtract with constant tensor requires input dimensions of sub layer to be present as part of the network.\
      If present, this warning can be ignored. If not, please use open source runtimes offering to run this model or run shape inference on this model before executing import  *** \n");
  }
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  status = TIDL_checkAddMulSubDivTensorProperties(layer, BASE_OP_SUB);
  if(status == -1) return -1;
  sTIDL_allowlistingMetaData md = layer.allowlistingMetaData;

  if(md.numConstInputs > 0) //subtraction with constant tensor
  {
    int constTensorIdx = md.constTensorIndices[0];
    TensorProto constTensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(constTensorIdx), i);
    int32_t varTensorIdx = md.varTensorIndices[0];
    
    if(constTensor.dims_size() == 0) //tensor dim size = 0 --- Sub constant to layer
    {        
        layer.layerType = TIDL_BatchNormLayer;
        status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.bias);
        if(status == -1)
        {
          diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__));
          return -1;
        }
        int32_t biasSize = md.varTensorsDims[0][TIDL_DIM_NUMCH]; //broadcast the constant along number of channels
        if(constTensor.data_type() == TensorProto_DataType_FLOAT)
        {
          TIDL_onnxBroadcastFloatTensor(layer.bias, biasSize);
        }
        else
        {
          std::string diagMsg = "ALLOWLISTING : SUB layer : Supported only if data type of constant is float  --  file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__);
          diagsInfo.push_back(diagMsg);
          return -1;
        }
    }
    else //Subtraction with constant vector
    {
      layer.layerType = TIDL_BatchNormLayer;
      status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.bias);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__)); 
        return -1;
      }
    }
  
    layer.weights.ptr             = my_malloc(layer.bias.bufSize*sizeof(float));
    layer.weights.bufSize         = layer.bias.bufSize;
    float *ptr = (float *)layer.weights.ptr;        
    /* case: const - X */
    if(md.constTensorIndices[0]  < md.varTensorIndices[0] )
    {
      for (int lc = 0; lc < layer.weights.bufSize; lc++)
        ptr[lc] = -1.0;          
    }
    /* case: X - const */
    else
    {
      /* scaling bias with: -1 */
      float *biasPtr = (float *)layer.bias.ptr;
      for (int lc = 0; lc < layer.bias.bufSize; lc++)
        biasPtr[lc] = -1.0*biasPtr[lc];

      for (int lc = 0; lc < layer.weights.bufSize; lc++)
        ptr[lc] = 1.0;
    }
    return 0;
  }
  return 0;
}


int32_t TIDL_onnxMapSubParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapSubBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapMulBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  if(gParams.modelType == TIDL_IMPORT_MODEL_FORMAT_ONNX )
  {
    printf("*** WARNING : Mul with constant tensor requires input dimensions of mul layer to be present as part of the network.\
      If present, this warning can be ignored. If not, please use open source runtimes offering to run this model or run shape inference on this model before executing import  *** \n");
  }
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  status = TIDL_checkAddMulSubDivTensorProperties(layer, BASE_OP_MUL);
  if(status == -1) return -1;

  sTIDL_allowlistingMetaData md = layer.allowlistingMetaData;
  int32_t is1DConstTensor = checkDimConstTensor (md);
  if(md.numConstInputs > 0) //multiply with constant tensor
  {
    int constTensorIdx = md.constTensorIndices[0];
    if (is1DConstTensor == 1)
    {
      TensorProto constTensor = TIDL_getInitializerTensor(onnGraph, onnGraph.node(i).input(constTensorIdx), i);
      
      int32_t varTensorIdx = md.varTensorIndices[0];
      
      if(constTensor.dims_size() == 0) //tensor dim size = 0 --- Mul constant to layer
      {
          layer.layerType = TIDL_BatchNormLayer;
          status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.weights);
          if(status == -1)
          {
            diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
            + std::string(__func__) + " , " + std::to_string(__LINE__));
            return -1;
          }
          int32_t wtSize = md.varTensorsDims[0][TIDL_DIM_NUMCH]; //broadcast the constant along number of channels
          if(constTensor.data_type() == TensorProto_DataType_FLOAT)
          {
            TIDL_onnxBroadcastFloatTensor(layer.weights, wtSize);
          }
          else
          {
            std::string diagMsg = "ALLOWLISTING : Mul layer : Supported only if data type of constant is float  --  file info - " + std::string(__FILE__) + " , " \
            + std::string(__func__) + " , " + std::to_string(__LINE__);
            diagsInfo.push_back(diagMsg);
            return -1;
          }
      }
      else //Multiply with constant vector
      {
        layer.layerType = TIDL_BatchNormLayer;
        status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.weights);
        if(status == -1)
        {
          diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
            + std::string(__func__) + " , " + std::to_string(__LINE__)); 
          return -1;
        }
      }

      layer.bias.ptr             = my_malloc(layer.weights.bufSize*sizeof(float));
      layer.bias.bufSize         = layer.weights.bufSize;
      float *ptr = (float *)layer.bias.ptr;
      for (int lc = 0; lc < layer.bias.bufSize; lc++)
        ptr[lc] = 0.0;
      return 0;
    }
    else 
    {
      //Multiply with constant tensor
      layer.layerType = TIDL_EltWiseLayer;
      layer.layerParams.eltWiseParams.eltWiseType = TIDL_EltWiseProduct;
      layer.numInBufs = md.numInputs;      
      status = TIDL_tfCopyFloatInitializerTensor(onnGraph, i, constTensorIdx, layer.weights);
      if(status == -1)
      {
        diagsInfo.push_back("Cannot read initializer tensor : Only float and INT64 tensor is supported  -- file info - " + std::string(__FILE__) + " , " \
          + std::string(__func__) + " , " + std::to_string(__LINE__)); 
        return -1;
      }
    }
  }
  else //both inputs variable
  {
    layer.layerType = TIDL_EltWiseLayer;
    layer.layerParams.eltWiseParams.eltWiseType = TIDL_EltWiseProduct;
    layer.numInBufs = md.numInputs;
  }
  return 0;
}

int32_t TIDL_onnxMapMulParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapMulBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapConcatBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t axis;

  layer.layerType = TIDL_ConcatLayer;
  layer.numInBufs = onnGraph.node(i).input_size();
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "axis", &axis, 0);
  layer.layerParams.concatParams.axis = axis;
  return 0;
}

int32_t TIDL_onnxMapConcatParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapConcatBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapUpsampleBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t idx, j;
  char upsampleMode[50];
  layer.layerType = TIDL_ResizeLayer;
  int32_t axis;
  layer.numInBufs = 1;
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetStringAttr(node, "mode", upsampleMode, 0);
  if ((strcmp(upsampleMode, "nearest") == 0))
  {
    layer.layerParams.resizeParams.mode = TIDL_ResizeNearest;
  }
  else if((strcmp(upsampleMode, "linear") == 0))
  {
    layer.layerParams.resizeParams.mode = TIDL_ResizeBilinear;
  }
  else
  {
    printf("Un suported Upsample Mode \n");
    return -1;
  }
  if ((layer.layerParams.resizeParams.mode == TIDL_ResizeBilinear) ||
      (layer.layerParams.resizeParams.mode == TIDL_ResizeNearest))
  {
    sBuffer_t buf;
    TIDL_tfCopyFloatConst(onnGraph, i, 1, buf);
    float *ptr = (float *)buf.ptr;
    for (j = 0; j < buf.bufSize; j++)
    {
      layer.layerParams.resizeParams.resizeRatio[j] = ptr[j];
    }
    my_free(ptr);
  }
  return 0;
}

int32_t TIDL_onnxMapUpsampleParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapUpsampleBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapResizeBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t idx, j;
  int32_t status = 0;
  char upsampleMode[50];
  layer.layerType = TIDL_ResizeLayer;
  int32_t axis;
  layer.numInBufs = 1;
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetStringAttr(node, "mode", upsampleMode, 0);
  if ((strcmp(upsampleMode, "nearest") == 0))
  {
    layer.layerParams.resizeParams.mode = TIDL_ResizeNearest;
  }
  else if((strcmp(upsampleMode, "linear") == 0))
  {
    layer.layerParams.resizeParams.mode = TIDL_ResizeBilinear;
  }
  else
  {
    printf("Unsupported Resize mode \n");
    return -1;
  }
  if ((layer.layerParams.resizeParams.mode == TIDL_ResizeBilinear) ||
      (layer.layerParams.resizeParams.mode == TIDL_ResizeNearest))
  {
    sBuffer_t buf;
    if (onnxOpSetVersion == 10)
    {
      TIDL_tfCopyFloatConst(onnGraph, i, 1, buf);
    }
    else if (onnxOpSetVersion == 11)
    {
      if ( node.input_size()< 4 )
      {
        TIDL_tfCopyFloatConst(onnGraph, i, 2, buf);
      }
      else
      {
        printf("Error , Node %d : SIZES Input Tensor is not supported for Resize-11 operator\n", i);
        printf("\
                As a Workaround user can provide the resize factor using SCALES tensor \n \
                instead of using SIZES. As an example instead of using \n \
                interpolate(x, size=[W, H], mode='bilinear', align_corners=False)\n \
                user can use \n \
                interpolate(x, scale_factor=(s1,s2), mode='bilinear', align_corners=False) \n \
                where s1 and s2 are ratio of resize factor for width and height.\n\n");

        /* Set some default values as execution doesnt stop */
        layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_BATCH]  = 1;
        layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_NUMCH]  = 1;
        layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_HEIGHT] = 2;
        layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_WIDTH]  = 2;
        
        status = -1;
        goto Exit;
      }
    }
    else
    {
      printf("Error : Unsupported Opset for Resize OP \n");
      layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_BATCH]  = 1;
      layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_NUMCH]  = 1;
      layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_HEIGHT] = 2;
      layer.layerParams.resizeParams.resizeRatio[TIDL_DIM_WIDTH]  = 2;

      status = -1;
      goto Exit;
    }
    float *ptr = (float *)buf.ptr;
    for (j = 0; j < buf.bufSize; j++)
    {
      layer.layerParams.resizeParams.resizeRatio[j] = ptr[j];
    }
    my_free(ptr);
  }
Exit:
if(status == -1)
{
  if(gParams.modelType == TIDL_IMPORT_MODEL_FORMAT_ONNX_RT)
  {
    printf("Resize layer delegated to ARM -- '%s' \n", onnGraph.node(i).name().c_str());
    return -1;
  }
  else 
  {
    printf("*** WARNING : Code proceding with default resize ratio of 2 *** \n");
  }
}
return 0;

}

int32_t TIDL_onnxMapResizeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapResizeBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapAvgPoolBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{ 
  int32_t status = 0;
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  
  status = TIDL_checkPoolingTensorProperties(layer);
  if(status == -1) return -1;

  sTIDL_allowlistingMetaData md = layer.allowlistingMetaData;

  sTIDL_PoolingParams_t &poolParams = layer.layerParams.poolParams;

  std::vector<int32_t> attr;
  attr.push_back(TIDL_onnxGetIntAttr(onnGraph.node(i), "kernel_shape", &poolParams.kernelW, 0));
  attr.push_back(TIDL_onnxGetIntAttr(onnGraph.node(i), "kernel_shape", &poolParams.kernelH, 1));

  if(std::find(attr.begin(), attr.end(), -1) != attr.end())
  {
    diagsInfo.push_back("ALLOWLISTING : AVG POOL : Missing attribute  -- file info - " + std::string(__FILE__) + " , " \
        + std::string(__func__) + " , " + std::to_string(__LINE__));
    return -1;
  }
  
  int32_t isGlobalAvgPool = 0;
  if(gParams.modelType == TIDL_IMPORT_MODEL_FORMAT_ONNX_RT)
  {
    if((md.varTensorsDims[0][TIDL_DIM_HEIGHT] == poolParams.kernelH) && (md.varTensorsDims[0][TIDL_DIM_WIDTH] == poolParams.kernelW)) //global avg pool - e.g. squeezenet1.1
    {
      isGlobalAvgPool = 1;
    }
  }
  if(isGlobalAvgPool)
  {
    status = TIDL_onnxMapGlobalAvgPoolBaseParams(onnGraph, i, layer);
  }
  else
  {
    status = TIDL_onnxMapMaxPoolBaseParams(onnGraph, i, layer);
    poolParams.poolingType = TIDL_AveragePooling;

    // Convert 1x1 average pooling into max pooling (operations are identical)
    // mxnet_resnet50_v1d
    if (poolParams.kernelH == 1 && poolParams.kernelW == 1 &&
        ((poolParams.strideH == 2 && poolParams.strideW == 2) || 
        (poolParams.strideH == 1 && poolParams.strideW == 1)))
    {
      poolParams.poolingType = TIDL_MaxPooling;
    }
  }
  
  return 0;
}

int32_t TIDL_onnxMapAvgPoolParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  TIDL_onnxMapMaxPoolParams(pOrgTIDLNetStructure, i, layerIndex, dataIndex, onnGraph);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType = TIDL_AveragePooling;
  return 0;
}

int32_t TIDL_onnxMapGlobalAvgPoolBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  
  status = TIDL_checkPoolingTensorProperties(layer);
  if(status == -1) return -1;

  int32_t padType;
  int32_t idx1, idx2;
  int32_t pads[4];
  sTIDL_PoolingParams_t &poolParams = layer.layerParams.poolParams;
  layer.layerType = TIDL_PoolingLayer;
  poolParams.poolingType = TIDL_AveragePooling;
  poolParams.strideW = 1;
  poolParams.strideH = 1;
  poolParams.padW = 0;
  poolParams.padH = 0;
  poolParams.kernelW = 0;
  poolParams.kernelH = 0;
  return 0;
}

int32_t TIDL_onnxMapGlobalAvgPoolParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapGlobalAvgPoolBaseParams(onnGraph, i, TIDLPCLayers);

  return status;

}

int32_t TIDL_onnxMapReshapeBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t status = 0;
  layer.layerType = TIDL_ReshapeLayer;
  TIDL_onnxSaveAllowlistingMetaData(onnGraph, i, layer);
  
  status = TIDL_checkReshapeTensorProperties(layer);
  if(status == -1) return -1;
  TIDL_tfCopyFloatInitializerTensor(onnGraph, i, 1, layer.weights);
#if 0
  {
    int32_t * bufPtr;
    for (int k = 0; k < onnGraph.output_size(); k++)
    {
      if((strcmp(onnGraph.output(k).name().c_str(), onnGraph.node(i).output(0).c_str()) == 0))
      {
        if( onnGraph.output(k).type().tensor_type().has_shape() )
        {
          auto& tensorShape = onnGraph.output(k).type().tensor_type().shape();
          layer.weights.bufSize = tensorShape.dim_size();
          bufPtr = (int32_t *)malloc(layer.weights.bufSize * sizeof(int32_t));
          for (int j = 0; j < tensorShape.dim_size(); j++)
          {
            bufPtr[j] = tensorShape.dim(j).dim_value();
          }
          layer.weights.ptr = bufPtr;
        }
      }
    }
    for (int k = 0; k < onnGraph.value_info_size(); k++)
    {
      if((strcmp(onnGraph.value_info(k).name().c_str(), onnGraph.node(i).output(0).c_str()) == 0))
      {
        if( onnGraph.value_info(k).type().tensor_type().has_shape() )
        {
          auto& tensorShape = onnGraph.value_info(k).type().tensor_type().shape();
          layer.weights.bufSize = tensorShape.dim_size();
          bufPtr = (int32_t *)malloc(layer.weights.bufSize * sizeof(int32_t));
          for (int j = 0; j < tensorShape.dim_size(); j++)
          {
            bufPtr[j] = tensorShape.dim(j).dim_value();
          }
          layer.weights.ptr = bufPtr;
        }
      }
    }
  }
#endif
  return 0;
}

int32_t TIDL_onnxMapReshapeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapReshapeBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapTransposeBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  int32_t attrIdx;
  layer.layerType = TIDL_TransposeLayer;
  NodeProto node = onnGraph.node(i);
  attrIdx = TIDL_onnxGetAttrIdx(node, "perm");
  if (attrIdx != -1)
  {
    int32_t j;
    int32_t dims = node.attribute(attrIdx).ints_size();
    layer.weights.ptr = (void*)malloc(sizeof(int)*dims);
    layer.weights.bufSize = dims;
    int32_t *dimVlaue = (int*)layer.weights.ptr;
    for (j = 0; j < layer.weights.bufSize; j++)
    {
      dimVlaue[j] = node.attribute(attrIdx).ints(j);
    }
  }
  return 0;
}

int32_t TIDL_onnxMapTransposeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapTransposeBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_onnxMapDepthToSpaceBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_DepthToSpaceLayer;
  NodeProto node = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "blocksize",   &layer.layerParams.depthToSpaceParams.blockSize, 0);
  return 0;
}

int32_t TIDL_onnxMapDepthToSpaceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapDepthToSpaceBaseParams(onnGraph, i, TIDLPCLayers);
  return 0;
}

int32_t TIDL_onnxMapDropOutBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_DropOutLayer;
  return 0;
}

int32_t TIDL_onnxMapDropoutParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapDropOutBaseParams(onnGraph, i, TIDLPCLayers);
  return 0;
}

int32_t TIDL_onnxMapReduceMaxBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ReduceLayer;
  layer.numInBufs = onnGraph.node(i).input_size();
  NodeProto node  = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "axes",   &layer.layerParams.reduceParams.axis, 0);
  TIDL_onnxGetIntAttr(node, "keepdims",   &layer.layerParams.reduceParams.keepDims, 0);
  layer.layerParams.reduceParams.ops = 0;
  return 0;
}

int32_t TIDL_onnxMapReduceMinBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ReduceLayer;
  layer.numInBufs = onnGraph.node(i).input_size();
  NodeProto node  = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "axes",   &layer.layerParams.reduceParams.axis, 0);
  TIDL_onnxGetIntAttr(node, "keepdims",   &layer.layerParams.reduceParams.keepDims, 0);
  layer.layerParams.reduceParams.ops = 1;
  return 0;
}

int32_t TIDL_onnxMapReduceMaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapReduceMaxBaseParams(onnGraph, i, TIDLPCLayers);

  return 0;
}

int32_t TIDL_onnxMapReduceMinParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapReduceMinBaseParams(onnGraph, i, TIDLPCLayers);

  return 0;
}

int32_t TIDL_onnxMapScatterElementsBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ScatterElementsLayer;
  layer.numInBufs = onnGraph.node(i).input_size();
  TIDL_onnxGetIntAttr(onnGraph.node(i), "axis",   &layer.layerParams.scatterElementsParams.axis, 0);

  strcpy((char*)layer.layerParams.scatterElementsParams.dataTensorName, (char*)onnGraph.node(i).input(0).c_str());
  strcpy((char*)layer.layerParams.scatterElementsParams.indicesTensorName, (char*)onnGraph.node(i).input(1).c_str());
  strcpy((char*)layer.layerParams.scatterElementsParams.updateTensorName, (char*)onnGraph.node(i).input(2).c_str());

  return 0;
}

int32_t TIDL_onnxMapScatterElementsParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnxGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapScatterElementsBaseParams(onnxGraph, i, TIDLPCLayers);
  return 0;
}


int32_t TIDL_onnxMapScatterNDBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_ScatterElementsLayer;
  layer.numInBufs = onnGraph.node(i).input_size();
  layer.layerParams.scatterElementsParams.axis = -1;
  return 0;
}

int32_t TIDL_onnxMapScatterNDParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnxGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapScatterNDBaseParams(onnxGraph, i, TIDLPCLayers);
  /*Need to put some error checks on the input and weight dimension*/
  //@TODO
  return 0;
}


int32_t TIDL_onnxMapSqueezeBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_SqueezeLayer;
  layer.numInBufs = onnGraph.node(i).input_size();
  NodeProto node  = onnGraph.node(i);
  TIDL_onnxGetIntAttr(node, "axes",   &layer.layerPCParams.squeezeParams.axis[0], 0);

  return 0;
}

int32_t TIDL_onnxMapSqueezeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph )
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapSqueezeBaseParams(onnGraph, i, TIDLPCLayers);

  return 0;
}
int32_t TIDL_onnxMapConstParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_ConstDataLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = 0;
  return 0;
}


int32_t TIDL_onnxMapIdentityBaseParams(GraphProto&   onnGraph, int32_t i, sTIDL_LayerPC_t &layer)
{
  layer.layerType = TIDL_IdentityLayer;
  return 0;
}

int32_t TIDL_onnxMapIdentityParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  int32_t status;
  sTIDL_LayerPC_t &TIDLPCLayers = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex];
  TIDLPCLayers.outData[0].dataId = (*dataIndex)++;
  status = TIDL_onnxMapIdentityBaseParams(onnGraph, i, TIDLPCLayers);
  return status;
}

int32_t TIDL_tfMapUnSuportedlayerParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  int32_t              *dataIndex,
  GraphProto&            onnGraph)
{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_UnsupportedLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = (*dataIndex)++;
  return 0;
}

typedef struct {
  int8_t name[TIDL_STRING_SIZE];
  int32_t(*tidl_onnxMapFunc)(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
    int32_t              i,
    int32_t              layerIndex,
    int32_t              *dataIndex,
    GraphProto&             onnxGraph);
}sTIDL_onnxOpParamMap_t;

sTIDL_onnxOpParamMap_t tidl_onnxOpParamMapTable[] =
{
  { "Conv",                          TIDL_onnxMapConvParams },
  { "MaxPool",                       TIDL_onnxMapMaxPoolParams },
  { "Relu",                          TIDL_onnxMapReluParams },
  { "Clip",                          TIDL_onnxMapClipParams },
  { "PRelu",                         TIDL_onnxMapPReluParams },
  { "Sigmoid",                       TIDL_onnxMapSigmoidParams },
  { "Tanh",                          TIDL_onnxMapTanhParams },
  { "HardSigmoid",                   TIDL_onnxMapHardSigmoidParams },
  { "Elu",                           TIDL_onnxMapELUParams },
  { "Logistic",                      TIDL_onnxMapSigmoidParams },
  { "LeakyRelu",                     TIDL_onnxMapLeakyReluParams },
  { "Concat",                        TIDL_onnxMapConcatParams },
  { "AveragePool",                   TIDL_onnxMapAvgPoolParams },
  { "GlobalAveragePool",             TIDL_onnxMapGlobalAvgPoolParams },
  { "Upsample",                      TIDL_onnxMapUpsampleParams },
  { "Resize",                        TIDL_onnxMapResizeParams },
  { "ConvTranspose",                 TIDL_onnxMapConvTransposeParams },
  { "Reshape",                       TIDL_onnxMapReshapeParams },
  { "Transpose",                     TIDL_onnxMapTransposeParams },
  { "Add",                           TIDL_onnxMapAddParams },
  { "Sum",                           TIDL_onnxMapAddParams },
  { "Sub",                           TIDL_onnxMapSubParams },
  { "ArgMax",                        TIDL_onnxMapArgmaxParams },
  { "BatchNormalization",            TIDL_onnxMapBNParams },
  { "Gemm",                          TIDL_onnxGemmParams },
  { "Softmax",                       TIDL_onnxSoftmaxParams },
  { "Split",                         TIDL_onnxSplitParams },
  { "Slice",                         TIDL_onnxSliceParams },
  { "Flatten",                       TIDL_onnxMapFlattenParams },
  { "Pad",                           TIDL_onnxMapPadParams },
  { "Mul",                           TIDL_onnxMapMulParams },
  { "DepthToSpace",                  TIDL_onnxMapDepthToSpaceParams },
  { "ReduceMax",                     TIDL_onnxMapReduceMaxParams },
  { "ReduceMin",                     TIDL_onnxMapReduceMinParams },
  { "ScatterElements",               TIDL_onnxMapScatterElementsParams },
  { "Squeeze",                       TIDL_onnxMapSqueezeParams },
  { "Dropout",                       TIDL_onnxMapDropoutParams },
  { "ScatterND",                     TIDL_onnxMapScatterNDParams},
  { "Cast",                          TIDL_onnxMapIdentityParams }
};
int32_t TIDL_getOnnxOpParamMapId(const char  * name)
{
  int32_t i = -1;
  for (i = 0; i < sizeof(tidl_onnxOpParamMapTable) / sizeof(sTIDL_onnxOpParamMap_t); i++)
  {
    if ((strcmp(name, (const char *)tidl_onnxOpParamMapTable[i].name) == 0))
    {
      return (i);
    }
  }
  return (-1);
}

TIDL_TFLayerMapping_t TIDL_OnnxLayerMap[] =
{
  { (char*)"TIDL_OnnxShuffle",        (char*)"TIDL_ReshapeLayerTIDL_TransposeLayerTIDL_ReshapeLayer"   , 3 },
  { (char*)"TIDL_TFSlimShuffle",        (char*)"NANA"              , 3 }
};


int32_t tidl_FindOnnxShuffleLayer(sTIDL_OrgNetwork_t  &pOrgTIDLNetStructure, int32_t layerIndex)
{
  int32_t i1, i2, i3, i4;
  int32_t status = 0;
  for (i1 = 0; i1 < layerIndex; i1++)
  {
    if (tf_isLayerType("TIDL_OnnxShuffle", i1, pOrgTIDLNetStructure, TIDL_OnnxLayerMap, (sizeof(TIDL_OnnxLayerMap) / sizeof(TIDL_TFLayerMapping_t))))
    {
      int32_t mapIdx = tf_getLayreTypeMapIdx("TIDL_OnnxShuffle", TIDL_OnnxLayerMap, (sizeof(TIDL_OnnxLayerMap) / sizeof(TIDL_TFLayerMapping_t)));
      pOrgTIDLNetStructure.TIDLPCLayers[i1].layerType = TIDL_FlattenLayer;

      sTIDL_LayerPC_t &TIDLPCLayers1 = pOrgTIDLNetStructure.TIDLPCLayers[i1];
      int32_t nextlayerIdx = tidl_getOutLayer(pOrgTIDLNetStructure, pOrgTIDLNetStructure.numLayers, pOrgTIDLNetStructure.TIDLPCLayers[i1].outData[0].dataId);
      sTIDL_LayerPC_t &TIDLPCLayers2 = pOrgTIDLNetStructure.TIDLPCLayers[nextlayerIdx];
      nextlayerIdx = tidl_getOutLayer(pOrgTIDLNetStructure, pOrgTIDLNetStructure.numLayers, pOrgTIDLNetStructure.TIDLPCLayers[nextlayerIdx].outData[0].dataId);
      sTIDL_LayerPC_t &TIDLPCLayers3 = pOrgTIDLNetStructure.TIDLPCLayers[nextlayerIdx];

      if ((TIDLPCLayers1.weights.bufSize ==  5) && (TIDLPCLayers2.weights.bufSize ==  5) && (TIDLPCLayers3.weights.bufSize == 4))
      {
        int64_t * reshape1  = (int64_t *)TIDLPCLayers1.weights.ptr;
        int64_t * reshape2  = (int64_t *)TIDLPCLayers3.weights.ptr;
        int32_t * transpose = (int32_t *)TIDLPCLayers2.weights.ptr;
        if ((reshape1[4] == reshape2[3]) && (reshape1[3] == reshape2[2]) && (4 == transpose[4]) && (3 == transpose[3]) && (1 == transpose[2]) && (2 == transpose[1]))
        {
          pOrgTIDLNetStructure.TIDLPCLayers[i1].outData[0] = TIDLPCLayers3.outData[0];
          strcpy((char *)pOrgTIDLNetStructure.TIDLPCLayers[i1].outDataNames[0], (char *)TIDLPCLayers3.outDataNames[0]);
          pOrgTIDLNetStructure.TIDLPCLayers[i1].outConsumerCnt[0] = TIDLPCLayers3.outConsumerCnt[0];

          TIDLPCLayers2.numInBufs = -1;
          TIDLPCLayers2.numOutBufs = -1;
          TIDLPCLayers3.numInBufs = -1;
          TIDLPCLayers3.numOutBufs = -1;

          TIDLPCLayers1.layerType = TIDL_ShuffleChannelLayer;
          TIDLPCLayers1.layerParams.shuffleLayerParams.numGroups = reshape1[1];
        }
      }

      if ((TIDLPCLayers1.weights.bufSize ==  6) && (TIDLPCLayers2.weights.bufSize ==  6) && (TIDLPCLayers3.weights.bufSize == 4))
      {
        int64_t * reshape1  = (int64_t *)TIDLPCLayers1.weights.ptr;
        int64_t * reshape2  = (int64_t *)TIDLPCLayers3.weights.ptr;
        int32_t * transpose = (int32_t *)TIDLPCLayers2.weights.ptr;
        if ((reshape1[4]*reshape1[2] == reshape2[2]) && (reshape1[3]*reshape1[5] == reshape2[3]) && (reshape1[1] == reshape2[1]) && (reshape1[2] == reshape1[3]) &&
            (3 == transpose[5]) && (5 == transpose[4]) && (2 == transpose[3]) && (4 == transpose[2]) && (1 == transpose[1]))
        {
          pOrgTIDLNetStructure.TIDLPCLayers[i1].outData[0] = TIDLPCLayers3.outData[0];
          strcpy((char *)pOrgTIDLNetStructure.TIDLPCLayers[i1].outDataNames[0], (char *)TIDLPCLayers3.outDataNames[0]);
          pOrgTIDLNetStructure.TIDLPCLayers[i1].outConsumerCnt[0] = TIDLPCLayers3.outConsumerCnt[0];

          TIDLPCLayers2.numInBufs = -1;
          TIDLPCLayers2.numOutBufs = -1;
          TIDLPCLayers3.numInBufs = -1;
          TIDLPCLayers3.numOutBufs = -1;

          TIDLPCLayers1.layerType = TIDL_DepthToSpaceLayer;

          if((gParams.deviceName & ~TIDL_OTF_FLAG_BIT) == TIDL_AM62A)
          {
            printf("ERROR: Device AM62A currently does not support Pixel Shuffle Layer\n");
            exit(-1);
          }
          TIDLPCLayers1.layerParams.depthToSpaceParams.blockSize = reshape1[2];
        }
      }
    }
  }
  return 0;
}


int32_t tidl_onnxLayerFillTensorNames(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  GraphProto&             onnxGraph)
{
  int32_t j;
  if(strlen(onnxGraph.node(i).name().c_str()) < TIDL_STRING_SIZE)
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, onnxGraph.node(i).name().c_str());
  }
  else
  {
    printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, onnxGraph.node(i).name().c_str());
    exit(-1);
  }

  if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs > 0)
  {
    int k=0;
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++)
    {
      if(strlen(onnxGraph.node(i).input(j).c_str()) < TIDL_STRING_SIZE)
      {
        if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType != TIDL_EltWiseLayer)
        {
          while( 1 == TIDL_isInputConstInGraph(onnxGraph, onnxGraph.node(i).input(j+k).c_str())){
            k++;
          }
        }
        strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j], onnxGraph.node(i).input(j+k).c_str());
      }
      else
      {
        printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, onnxGraph.node(i).input(j).c_str());
        exit(-1);
      }
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].dataId = -1;
    }
  }
  if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs > 0)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; j++)
    {
      if(strlen(onnxGraph.node(i).output(j).c_str()) < TIDL_STRING_SIZE)
      {
        strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j], onnxGraph.node(i).output(j).c_str());
      }
      else
      {
        printf("\n*** Tensor name exceeds %d characters, exiting ! *** \nTensor name --- \n %s \n", TIDL_STRING_SIZE, onnxGraph.node(i).output(j).c_str());
        exit(-1);
      }
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outConsumerLinked[j] = 0;
    }
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].weightsElementSizeInBits = NUM_WHGT_BITS;

  return 0;
}

int32_t tidl_onnxLayerUpdateConsumerCount(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              layerIndex,
  GraphProto&             onnxGraph)
{
  int32_t i0, i1, i2;
  int32_t numCons = 0;
  for (i0 = 0; i0 < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; i0++)
  {

    for (i1 = 0; i1 < onnxGraph.node_size(); i1++)
    {
      for (i2 = 0; i2 < onnxGraph.node(i1).input_size(); i2++)
      {
        if (strcmp((const char *)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[i0], onnxGraph.node(i1).input(i2).c_str()) == 0)
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


int32_t TIDL_onnxGetNodeIdx(GraphProto&             onnxGraph, const char *bufName)
{
  int32_t i, j, nameLen, nodeIdx = -1;
  char nodeName[TIDL_MAX_DATA_NAME];
  char inDataName[TIDL_MAX_DATA_NAME];
  for (i = 0; i < onnxGraph.node_size(); i++)
  {
    for (j = 0; j < onnxGraph.node(i).output_size(); j++)
    {
      if (strcmp(onnxGraph.node(i).output(j).c_str(), bufName) == 0)
      {
        nodeIdx = i;
        break;
      }
    }
  }
  return nodeIdx;
}

int32_t tidl_onnxGetNewNodeToAdd(sTIDL_OrgNetwork_t   &orgTIDLNetStructure,
  int32_t              layerIndex,
  GraphProto&             onnxGraph)
{
  int32_t i, j, nodeIdx = -1;

  for (i = 0; i < layerIndex; i++)
  {
    for (j = 0; j < orgTIDLNetStructure.TIDLPCLayers[i].numInBufs; j++)
    {
      if (TIDL_getLayerIdx(&orgTIDLNetStructure, layerIndex, (const char *)orgTIDLNetStructure.TIDLPCLayers[i].inDataNames[j]) == -1)
      {
        nodeIdx = TIDL_onnxGetNodeIdx(onnxGraph, (const char *)orgTIDLNetStructure.TIDLPCLayers[i].inDataNames[j]);
        if (nodeIdx != -1)
        {
          if (strcmp(onnxGraph.node(nodeIdx).op_type().c_str(), "Constant") == 0)
          {
            nodeIdx = -1;
          }
        }
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

int32_t tidl_findOnnxOutputNames(GraphProto&             onnxGraph, char * outList)
{
  int i, j, k, l;
  char tensorName[FILE_NAME_SIZE];
  char inTensorName[FILE_NAME_SIZE];
  int outPutSize = 0;

  if(onnxGraph.output_size() > 0)
  {
    for (i = 0; i < onnxGraph.output_size(); i++)
    {
      strcat(outList, onnxGraph.output(i).name().c_str());
      strcat(outList, ",");
    }
  }
  else 
  {
    for (i = 0; i < onnxGraph.node_size(); i++)
    {
      outPutSize = onnxGraph.node(i).output_size();
      if (strcmp(onnxGraph.node(i).op_type().c_str(), "Dropout") == 0)
      {
        outPutSize = 1;
      }
      for (j = 0; j < outPutSize; j++)
      {
        int outDataUsed = 0;
        strcpy((char *)tensorName, onnxGraph.node(i).output(j).c_str());
        for (k = 0; k < onnxGraph.node_size(); k++)
        {
          for (l = 0; l < onnxGraph.node(k).input_size(); l++)
          {
            strcpy((char *)inTensorName, onnxGraph.node(k).input(l).c_str());
            if (strcmp(tensorName, inTensorName) == 0)
            {
              outDataUsed = 1;
              break;
            }
          }
          if (outDataUsed)
            break;
        }
        if (outDataUsed == 0)
        {
          strcat(outList, tensorName);
          strcat(outList, ",");
        }
      }
    }
  }
  return (0);
}

void onnx_import(tidl_import_config * params, int32_t *totalData, int32_t* totalLayers)
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
  ModelProto         onnxModel;
  int32_t status = 0;
  int32_t                    dataSize;
  int32_t                    id;
  int paramSet  = 0;
  int conv2DRandParams = 0;
  string attrKey;
  int32_t inLayerId = 0;
  int32_t weightsElementSizeInBits;
  int32_t mapTblIdx = -1;


  string key = "value";

  printf("ONNX Model (Proto) File  : %s  \n",(const char *)params->inputNetFile);
  printf("TIDL Network File      : %s  \n", (const char *)params->outputNetFile);
  printf("TIDL IO Info File      : %s  \n", (const char *)params->outputParamsFile);

  TIDL_readProtoFromBinaryFile((const char *)params->inputNetFile, (google::protobuf::Message*)&onnxModel);
  GraphProto onnxGraph = onnxModel.graph();
  auto & opset_import = onnxModel.opset_import(0);
  onnxOpSetVersion =  opset_import.version();
  printf("Current ONNX OpSet Version   : %d  \n", onnxOpSetVersion);

  layerIndex = 0;
  dataIndex  = 0;


  if (strcmp((char*)params->outDataNamesList, "") == 0)
  {
    char outDataNamesList[500] = "";
    tidl_findOnnxOutputNames(onnxGraph, (char*)outDataNamesList);
    numNetOutData = tidl_getStringsFromList((char *)outDataNamesList, (char*)outDataNames, TIDL_MAX_DATA_NAME);
  }
  else
  {
    numNetOutData = tidl_getStringsFromList((char *)params->outDataNamesList, (char*)outDataNames, TIDL_MAX_DATA_NAME);
  }
  for (i = 0; i < numNetOutData; i++)
  {
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs = 1;
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
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].numDim = 4;
      tidl_onnxLayerUpdateConsumerCount(&orgTIDLNetStructure, layerIndex, layerIndex, onnxGraph);
      tidl_linkOutputTensors(&orgTIDLNetStructure, layerIndex);
      layerIndex++;
    }
  }
  
  int newNode = tidl_onnxGetNewNodeToAdd(orgTIDLNetStructure, layerIndex, onnxGraph);
  while (newNode != -1)
  {
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs = 1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dataId = -1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].actParams.actType = TIDL_NoAct;

    mapTblIdx = TIDL_getOnnxOpParamMapId(onnxGraph.node(newNode).op_type().c_str());
    if (mapTblIdx == -1)
    {
      printf(" ONNX operator %s is not suported now..  By passing\n", onnxGraph.node(newNode).op_type().c_str());
      TIDL_tfMapUnSuportedlayerParams(&orgTIDLNetStructure, newNode, layerIndex, &dataIndex, onnxGraph);
    }
    else
    {
      status = tidl_onnxOpParamMapTable[mapTblIdx].tidl_onnxMapFunc(&orgTIDLNetStructure, newNode, layerIndex, &dataIndex, onnxGraph);
    }

    if(status == -1) 
    {
      for(auto &msg : diagsInfo)
      {
        if(! msg.empty())
          printf("%s  \n", msg.c_str());
      }
      exit(-1);
    }

    if (params->enableCustomLayers)
    {
      TIDL_MapCustomParams(&orgTIDLNetStructure,
                            newNode,
                            layerIndex,
                            &dataIndex,
                            &onnxGraph,
                            NULL,
                            TIDL_IMPORT_MODEL_FORMAT_ONNX);
    }

    tidl_onnxLayerFillTensorNames(&orgTIDLNetStructure, newNode, layerIndex, onnxGraph);
    tidl_onnxLayerUpdateConsumerCount(&orgTIDLNetStructure, newNode, layerIndex, onnxGraph);
    tidl_linkInputTensors(&orgTIDLNetStructure, layerIndex);
    tidl_linkOutputTensors(&orgTIDLNetStructure, layerIndex);
    layerIndex++;

    newNode = tidl_onnxGetNewNodeToAdd(orgTIDLNetStructure, layerIndex, onnxGraph);
  }
  *totalData = dataIndex;
  *totalLayers = layerIndex;
}