/*
* Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <cmath>
#include <stdarg.h>
#include <fstream>

#include "onnxrt_ep.h"
#include "tidl_onnxrt_common.h"

static TIDL_OnnxrtEPInferOptions * data_ = new TIDL_OnnxrtEPInferOptions;

extern "C"
{

/* Read interface options and populate to TIDL runtimes option class */
bool TIDL_populateOptions(std::vector<std::pair<std::string,std::string>> interface_options)
{
  data_->infer_ops.lib = dlopen("libvx_tidl_rt.so", RTLD_NOW | RTLD_GLOBAL);
  if(! data_->infer_ops.lib)
  {
    printf("Error -   %s \n", dlerror());
  }
  TIDL_rtLoadSymbols(&data_->infer_ops);

  TIDL_OnnxrtEPInferOptions * options = data_;
  for(auto option : interface_options)
  {
    auto key = option.first;
    auto value = option.second;
    if (!strcmp("debug_level", key.c_str())) 
    {
      std::stringstream(value) >> options->m_debug_level;
      // TODO: any invalid values? like negative, or beyond supported range?
    }
    if (!strcmp("priority", key.c_str())) 
    {
      std::stringstream(value) >> options->target_priority;
    }
    if (!strcmp("max_pre_empt_delay", key.c_str())) 
    {      
      std::stringstream(value) >> options->max_pre_empt_delay;
    }
    if (!strcmp("core_number", key.c_str())) 
    {
      std::stringstream(value) >> options->core_number;
    }
    if (!strcmp("artifacts_folder", key.c_str())) 
    {
      options->m_artifacts_folder = value;
      if(!TIDL_checkIsDir(options->m_artifacts_folder.c_str())) 
      {
        delete options;

        printf("ERROR : artifacts_folder not a directory");
        return false;
      }
    }
  }
  if (options->m_artifacts_folder.empty()) 
  {
      delete options;

      printf("ERROR : artifacts_folder must be provided");
      return false;
  }
  if(options->target_priority < 0 || options->target_priority > 7)
  {
    delete options;
    
    printf("ERROR : Please provide priority betweeen 0-7 ... exiting \n");
    return false;
  }

  options->osrtDebugPrintLevel = (options->m_debug_level == 0) ? 0 : 1;

  TIDL_osrtDebugPrint(options->osrtDebugPrintLevel, "artifacts_folder                                = %s \n", data_->m_artifacts_folder.c_str());
  TIDL_osrtDebugPrint(options->osrtDebugPrintLevel, "debug_level                                     = %d \n", data_->m_debug_level);
  TIDL_osrtDebugPrint(options->osrtDebugPrintLevel, "target_priority                                 = %d \n", data_->target_priority);
  TIDL_osrtDebugPrint(options->osrtDebugPrintLevel, "max_pre_empt_delay                              = %f \n", data_->max_pre_empt_delay);

  return true;
}
} //extern "C"

/** This function splits a string into a vector of substrings based on delimiter */
std::vector<std::string> TIDL_splitStringWithDelimiter(std::string inpStr, std::string del)
{
  int32_t start = 0;
  int32_t end = inpStr.find(del);
  std::vector<std::string> splitStr;
  while(end != -1)
  {
    splitStr.push_back(inpStr.substr(start, end - start));
    start = end + del.size();
    end = inpStr.find(del, start);
  }
  splitStr.push_back(inpStr.substr(start, end - start));

  return splitStr;
}



extern "C"
{

/* Called directly from ONNX runtime : return a vector of TIDL supported node groups */
std::vector<std::vector<int>> TIDL_getSupportedNodesInfer()
{ 
  std::vector<std::vector<int>> supportedNodeGroups;

  supportedNodeGroups = TIDL_readAllowedNodesList(data_->m_artifacts_folder);
  
  int32_t numSupportedNodes = 0;
  for(auto& v: supportedNodeGroups) numSupportedNodes += v.size();
  
  //read number of nodes in ONNX graph using meta data file
  int32_t numGraphNodes;
  std::ifstream onnxrtMetaData(data_->m_artifacts_folder + "/onnxrtMetaData.txt");
  std::string line;
  std::vector<std::string> dict;
  while(std::getline(onnxrtMetaData, line))
  {
    dict = TIDL_splitStringWithDelimiter(line, "=");  // vector of key and value
    if(dict[0] == "numGraphNodes")
    {
      std::stringstream num(dict[1]);
      num >> numGraphNodes;
    }
  }

  printf("Final number of subgraphs created are : %ld, - Offloaded Nodes - %d, Total Nodes - %d \n", supportedNodeGroups.size(), numSupportedNodes, numGraphNodes);
  if(supportedNodeGroups.empty())
  {
    return {{}};
  }
  else
  {
    return supportedNodeGroups;
  }
}


void TIDL_computeImportFunc(OnnxTIDLSubGraphParams * state_subGraph, std::string * string_buf,int32_t opSetVersion)
{
  printf("Error : This function call is not expected for inference flow \n");
}

int32_t TIDLEP_getDdrStats(uint64_t * read, uint64_t * write)
{
  return(data_->infer_ops.TIDLRT_getDdrStats(read, write));
}


/** Read metadata file which is saved during compilation and save in state_subGraph*/
void TIDL_readOnnxRtMetaDataForInference(OnnxTIDLSubGraphParams * state_subGraph, std::string artifactsFolder)
{
  onnxRtParams_t * onnxRtParams = &state_subGraph->onnxRtParams;
  std::string serialNumber = std::to_string(state_subGraph->serialNumber);
  
  std::ifstream onnxrtMetaData(artifactsFolder + "/onnxrtMetaData.txt");
  std::string line;
  std::vector<std::string> dict;
  while(std::getline(onnxrtMetaData, line))
  {
    dict = TIDL_splitStringWithDelimiter(line, "=");  // vector of key and value

    if(dict[0] == (serialNumber + ":subGraphName"))
    {
      strcpy((char*)state_subGraph->subGraphName_, dict[1].c_str());
    }
    if(dict[0] == (serialNumber + ":numInputs"))
    {
      std::stringstream num(dict[1]);
      num >> state_subGraph->numInputs;
    }
    if(dict[0] == (serialNumber + ":numOutputs"))
    {
      std::stringstream num(dict[1]);
      num >> state_subGraph->numOutputs;
    }
    if(dict[0] == (serialNumber + ":inputIdx"))
    {
      std::vector<std::string> idx = TIDL_splitStringWithDelimiter(dict[1], ",");
      for(int i = 0; i < idx.size(); i++)
      {
        std::stringstream num(idx[i]);
        num >> state_subGraph->inputIdx[i];
      }
    }
    if(dict[0] == (serialNumber + ":inDataNames"))
    {
      std::vector<std::string> idx = TIDL_splitStringWithDelimiter(dict[1], ",");
      for(int i = 0; i < idx.size(); i++)
      {
        strcpy((char *)onnxRtParams->inDataNames[i], idx[i].c_str());
      }
    }
    if(dict[0] == (serialNumber + ":outDataNames"))
    {
      std::vector<std::string> idx = TIDL_splitStringWithDelimiter(dict[1], ",");
      for(int i = 0; i < idx.size(); i++)
      {
        strcpy((char *)onnxRtParams->outDataNames[i], idx[i].c_str());
      }
    }
  }
}


/* Called from ONNX runtime - init of TIDL RT done in this function */
void TIDL_createStateInferFunc(OnnxTIDLSubGraphParams * state_subGraph, const std::string node_name)
{
  int32_t status = 0;
  TIDL_osrtDebugPrint(data_->osrtDebugPrintLevel, "In TIDL_createStateInfer \n");
  state_subGraph->currFrameIdx_ = 0;
  state_subGraph->subGraphPtr_ = NULL;
  state_subGraph->string_buf = NULL;

  TIDL_osrtDebugPrint(data_->osrtDebugPrintLevel, "Compute on node : %s\n",  node_name.c_str());
  
  TIDL_readOnnxRtMetaDataForInference(state_subGraph, data_->m_artifacts_folder);

  sTIDL_tidlRtParams_t * subgraphParams = reinterpret_cast<sTIDL_tidlRtParams_t *>(&state_subGraph->tidlRtParams);
  status = TIDL_subgraphRtCreate(data_->m_artifacts_folder, data_->m_debug_level, data_->osrtDebugPrintLevel, data_->max_pre_empt_delay, data_->target_priority, 
                                    data_->core_number, &data_->infer_ops, state_subGraph->subGraphName_, subgraphParams);
}




/* Called from ONNX runtime - call TIDL RT invoke from within this function */
void TIDL_computeInvokeFunc(OnnxTIDLSubGraphParams * state_subGraph)
{
  int32_t status;
  status = TIDL_subgraphRtInvoke(data_->osrtDebugPrintLevel, state_subGraph, &data_->infer_ops, 1);
}




/* Called from ONNX runtime - Free any allocated memories, TIDL RT handles */
void TIDL_releaseRtFunc(OnnxTIDLSubGraphParams * state_subGraph)
{
  sTIDL_tidlRtParams_t * subgraphParams = reinterpret_cast<sTIDL_tidlRtParams_t *>(&state_subGraph->tidlRtParams);
  int32_t status = TIDL_subgraphRtDelete(data_->osrtDebugPrintLevel, &data_->infer_ops, subgraphParams);
}

} //extern C

