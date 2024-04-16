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
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>
using namespace std;
using ::google::protobuf::Message;
#include "object_detection/protos/ssd.pb.h"
#include "object_detection/protos/image_resizer.pb.h"
#include "object_detection/protos/box_coder.pb.h"
#include "object_detection/protos/faster_rcnn_box_coder.pb.h"
#include "object_detection/protos/anchor_generator.pb.h"
#include "object_detection/protos/ssd_anchor_generator.pb.h"
#include "object_detection/protos/post_processing.pb.h"

#include "ti_dl.h"
#include "tidl_import_api.h"
#include "schema_generated.h"
#include "flatbuffers/flexbuffers.h"
#include "tidl_import_config.h"
#include "tidl_runtimes_infer_common.h"
#include "tidl_runtimes_import_common.h"
#include "tidl_import_common.h"
#include "tidl_meta_arch.pb.h"
#include "object_detection/protos/pipeline.pb.h"
#include "tidl_import_common_tidlrt_osrt.h"

#define MAX_NUM_TIDL_SUBGRAPHS (16)

sTIDL_runtimesImportState_t runtimes_import_state;

extern uint8_t tidl_OdOutputNames[TIDL_MAX_TF_SSD_LAYERS][TIDL_STRING_SIZE];
extern "C"
{

/** This function read the names of the OD heads from meta arch file and returns them as a vector of strings
 * */
std::vector<std::string> TIDL_readMetaArchInfo(std::string filePath,int32_t graphOutputSize,int metaType)
{
  int32_t  i, j, k, l;
  std::vector<std::string> inOdDataNames = {};
  
  if(metaType != -1)
  {
    if(metaType ==  TIDL_metaArchTFSSD)
    {
      printf("TIDL Meta PipeLine (Proto) File  : %s  \n", filePath.c_str());
      object_detection::protos::TrainEvalPipelineConfig tfOdpipeLineDef;
      TIDL_readProtoFromTextFile((const char *)filePath.c_str(), &tfOdpipeLineDef);
      if (tfOdpipeLineDef.has_model() == true)
      {
        if (tfOdpipeLineDef.model().has_ssd() == true)
        {
          auto &ssdDef = tfOdpipeLineDef.model().ssd();
          if(ssdDef.box_input_size() == ssdDef.class_input_size())
          {
            for (j = 0; j < ssdDef.box_input_size(); j++)
            {
              inOdDataNames.push_back(ssdDef.box_input(j).c_str());
              inOdDataNames.push_back(ssdDef.class_input(j).c_str());
            }
          }
          else
          {
            printf("\nBox Input Size and Class Input Size mismatches must be same check for inputs names again\n");
          }
        }
      }
    }
    else
    {
      tidl_meta_arch::TIDLMetaArch  tidlMetaArch;
      TIDL_readProtoFromTextFile((const char *)filePath.c_str(), &tidlMetaArch);
      printf("%s is meta arch name \n",tidlMetaArch.name().c_str());

      for (j = 0; j < tidlMetaArch.caffe_ssd_size(); j++)
      {
        printf("%s\n",tidlMetaArch.caffe_ssd(j).name().c_str());

        for(k =0; k < tidlMetaArch.caffe_ssd(j).box_input_size(); k++)
        {
          inOdDataNames.push_back(tidlMetaArch.caffe_ssd(j).box_input(k));
        }
        for(k =0; k < tidlMetaArch.caffe_ssd(j).class_input_size(); k++)
        {
          inOdDataNames.push_back(tidlMetaArch.caffe_ssd(j).class_input(k));
        }
        if(tidlMetaArch.caffe_ssd(j).output_size() != graphOutputSize)
        {
          printf("\nERROR : Number of output names provided in prototxt - %d - do not match actual number of outputs of OD network - %d \n\n", tidlMetaArch.caffe_ssd(j).output_size(), graphOutputSize);
          exit(-1);
        }
        for(k =0; k < tidlMetaArch.caffe_ssd(j).output_size(); k++)
        {
          strcpy((char *)tidl_OdOutputNames[k],tidlMetaArch.caffe_ssd(j).output(k).c_str());
        }
      }

      for (j = 0; j < tidlMetaArch.tidl_retinanet_size(); j++)        //tidl_retinanet_size()
      {
        printf("%s\n",tidlMetaArch.tidl_retinanet(j).name().c_str());
        
        if(tidlMetaArch.tidl_retinanet(j).box_input_size() == tidlMetaArch.tidl_retinanet(j).class_input_size())
        {
          for(k =0; k < tidlMetaArch.tidl_retinanet(j).box_input_size(); k++)
          {
            inOdDataNames.push_back(tidlMetaArch.tidl_retinanet(j).box_input(k).c_str());
          }
          for(k =0; k < tidlMetaArch.tidl_retinanet(j).class_input_size(); k++)
          {
            inOdDataNames.push_back(tidlMetaArch.tidl_retinanet(j).class_input(k).c_str());
          }
        }
        else
        {
          printf("\nBox Input Size and Class Input Size mismatches - must be same; check for inputs names again\n");
        }
        if(tidlMetaArch.tidl_retinanet(j).output_size() != graphOutputSize)
        {
          printf("\nERROR : Number of output names provided in prototxt - %d - do not match actual number of outputs of OD network - %d \n\n", tidlMetaArch.tidl_retinanet(j).output_size(), graphOutputSize);
          exit(-1);
        }
        for(k =0; k < tidlMetaArch.tidl_retinanet(j).output_size(); k++)
        {
          strcpy((char *)tidl_OdOutputNames[k],tidlMetaArch.tidl_retinanet(j).output(k).c_str());
        }
      }

      for (j = 0; j < tidlMetaArch.tidl_yolo_size(); j++)
      {
        printf("%s\n",tidlMetaArch.tidl_yolo(j).name().c_str());
        for(k =0; k < tidlMetaArch.tidl_yolo(j).yolo_param_size(); k++)
        {
          inOdDataNames.push_back(tidlMetaArch.tidl_yolo(j).yolo_param(k).input().c_str());
        }
        if(tidlMetaArch.tidl_yolo(j).output_size() != graphOutputSize)
        {
          printf("\nERROR : Number of output names provided in prototxt - %d - do not match actual number of outputs of OD network - %d \n\n", tidlMetaArch.tidl_yolo(j).output_size(), graphOutputSize);
          exit(-1);
        }
        for(int k = 0; k < tidlMetaArch.tidl_yolo(j).output_size(); k++)
        {
          strcpy((char *)tidl_OdOutputNames[k],tidlMetaArch.tidl_yolo(j).output(k).c_str());
        }
      }

      for (j = 0; j < tidlMetaArch.tidl_3dod_size(); j++)
      {
        printf("%s\n",tidlMetaArch.tidl_3dod(j).name().c_str());
        for(k =0; k < tidlMetaArch.tidl_3dod(j).box_input_size(); k++)
        {
          inOdDataNames.push_back(tidlMetaArch.tidl_3dod(j).box_input(k).c_str());
        }
        for(k =0; k < tidlMetaArch.tidl_3dod(j).class_input_size(); k++)
        {
          inOdDataNames.push_back(tidlMetaArch.tidl_3dod(j).class_input(k).c_str());
        }
        for(k =0; k < tidlMetaArch.tidl_3dod(j).dir_input_size(); k++)
        {
          inOdDataNames.push_back(tidlMetaArch.tidl_3dod(j).dir_input(k).c_str());
        }
        if(tidlMetaArch.tidl_3dod(j).output_size() != graphOutputSize)
        {
          printf("\nERROR : Number of output names provided in prototxt - %d - do not match actual number of outputs of OD network - %d \n\n", tidlMetaArch.tidl_yolo(j).output_size(), graphOutputSize);
          exit(-1);
        }
        for(k =0; k < tidlMetaArch.tidl_3dod(j).output_size(); k++)
        {
          strcpy((char *)tidl_OdOutputNames[k],tidlMetaArch.tidl_3dod(j).output(k).c_str());
        }
      }
    }
  }
  return inOdDataNames;
}

/** Iterative implementation of DFS on graph */
void TIDL_nodeTraversal(std::vector<std::vector<int>> adjacencyList, int startIdx, std::vector<int> &odBackboneNodes, std::vector<bool> &visited)
{
  // Mark the current node as visited
  visited[startIdx] = true;
  odBackboneNodes.push_back(startIdx);

  // Create a stack for DFS
  std::stack<int> stack;
  // Push the current source node
  stack.push(startIdx);

  while (!stack.empty())
  {
    // Pop the topmost node from stack
    startIdx = stack.top();
    stack.pop();

    if (!visited[startIdx])
    {
      odBackboneNodes.push_back(startIdx);
      visited[startIdx] = true;
    }

    // Get all adjacent nodes of the popped node 
    // If an adjacent has not been visited, then push it
    // to the stack.
    for (int i = 0; i < adjacencyList[startIdx].size(); i++)
    {
      if (visited[adjacencyList[startIdx][i]] == false)
            stack.push(adjacencyList[startIdx][i]);
    }
  }
}

/** This function calls DFS with each of the OD heads as root node */
std::vector<int> TIDL_callNodeTraversal(std::vector<std::vector<int>> adjacencyList, std::vector<int> postProcInputIds, int graphSize)
{
  std::vector<bool> visited;
  visited.assign(graphSize, false);
  
  std::vector<int> odBackboneNodes = {};
  for(auto inIds : postProcInputIds)  //Trace back from each of the OD post proc inputs/ heads
  {
    TIDL_nodeTraversal(adjacencyList, inIds, odBackboneNodes, visited);
  }
  printf("Number of OD backbone nodes = %ld \n", std::count(visited.begin(), visited.end(), true));
  return odBackboneNodes;
}

/** This function calls the exe for runtimes visualization */
void TIDL_runGraphvizToolRuntimes(std::string tidlToolsPath, std::string artifactsFolderPath, int32_t debugLevel)
{
  std::string allowlistPath = artifactsFolderPath + "/allowedNode.txt";
  std::string graphvizInfoPath = artifactsFolderPath + "/tempDir/graphvizInfo.txt";
  std::string outputPath = artifactsFolderPath + "/tempDir/runtimes_visualization.svg";

  std::string sysCommandStr = tidlToolsPath + "/tidl_graphVisualiser_runtimes.out " + allowlistPath + " " + graphvizInfoPath + " " + outputPath;
  
  char * sysCommand = new char[sysCommandStr.length() + 1];
  strcpy(sysCommand, sysCommandStr.c_str()); 
  
  system(sysCommand);

  if(debugLevel > 0)
  {
    printf("Running runtimes graphviz - %s \n", sysCommand);
  }
  
  delete [] sysCommand;
}

/* Check if directory is empty */
bool TIDL_checkIsEmpty(const char *path) {
    if (!TIDL_checkIsDir(path))
        return false;

    struct dirent *e;
    DIR *d = opendir(path);

    if(!d)
        return false;

    errno = 0;
    while(e = readdir(d)) {
        /* do not recurse into . and .. */
        if(!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;
        return false;
    }

    if(errno)
        return false;

    return true;
}

/** Read individual elements of a comma separated string
  * This function is used to read interface options which are provided as comma separated strings */ 
std::vector<std::string> TIDL_readCommaSeparatedString(char * deny_list)
{
    std::vector<std::string> ret;
    char * token = strtok(deny_list, ",");
    while( token != NULL ) 
    {
        for(int i = 0; i < strlen(token); i++)
        {
            if(token[i] ==  ' ')
            {
                memmove(token+i, token+i+1, strlen(token) - i);
            } 
        }
        std::string itoken;
        std::stringstream(token) >> itoken;
        ret.push_back(itoken);
        token = strtok(NULL, ",");
    }
    return ret;
}

/** This function can be used to add a particular layer to deny list if needed */
std::vector<int32_t> tidl_fillDenyListOption(std::string deny_list)
{
    std::vector<int32_t> ret;
    char * deny_list_char =  new char[deny_list.length() + 1];
    strcpy(deny_list_char, deny_list.c_str());

    char * token = strtok(deny_list_char, ",");

    while( token != NULL ) 
    {
        for(int i = 0; i < strlen(token); i++)
        {
            if(token[i] ==  ' ')
            {
                memmove(token+i, token+i+1, strlen(token) - i);
            } 
        }
        int32_t itoken;
        sscanf(token, "%d", &itoken);
        ret.push_back(itoken);
        token = strtok(NULL, ",");
    }
    delete deny_list_char;
    return ret;
}

/* Read interface options and populate to TIDL runtimes option class */
bool TIDL_readInterfaceOptions(TIDL_osrtOptions * options, std::string option_name, std::string option_value)
{
  if (!strcmp("tidl_tools_path", option_name.c_str())) 
    {
      options->m_tidl_tools_path = option_value;
      if(!TIDL_checkIsDir(options->m_tidl_tools_path.c_str())) 
      {
        printf("ERROR : tidl_tools_path not a directory");
        return false;
      }
      // TODO: maybe check for the libs, quants tools, GC tool are contained inside
    }
    if (!strcmp("artifacts_folder", option_name.c_str())) 
    {
      options->m_artifacts_folder = option_value;
      if(!TIDL_checkIsDir(options->m_artifacts_folder.c_str())) 
      {
        printf("ERROR : artifacts_folder not a directory");
        return false;
      }
      if(!TIDL_checkIsEmpty(options->m_artifacts_folder.c_str())) 
      {
        printf("ERROR : artifacts_folder not empty");
        return false;
      }
    }
    
    if (!strcmp("model_type", option_name.c_str())) 
    {
      options->m_model_type = option_value;
      if(options->m_model_type.c_str()=="OD") 
      {
        printf("The Model is classified as OD as mentioned by the user assumptions so considering as OD \n");
      }
    }

    if (!strcmp("debug_level", option_name.c_str())) 
    {
      std::stringstream(option_value) >> options->m_debug_level;
      // TODO: any invalid option_values? like negative, or beyond supported range?
    }

    options->osrtDebugPrintLevel = (options->m_debug_level == 0) ? 0 : 1;
    
    if (!strcmp("tensor_bits", option_name.c_str()))
    {
        std::stringstream(option_value) >> options->m_num_param_bits;

        std::vector<int> valid_num_params{8, 16, 32};
        if(std::find(valid_num_params.begin(), valid_num_params.end(), options->m_num_param_bits) == valid_num_params.end()) 
        {
            printf("ERROR : unsupported tensor_bits \n");
            return false;
        }
        if(options->m_num_param_bits == 32)
        {
          printf("\n***** WARNING : tensor_bits = 32 -- Compiling for floating point - target execution is not supported for 32 bit compilation !! ***** \n");
        }
    }

    if (!strcmp("max_num_subgraphs", option_name.c_str())) 
    {
        std::stringstream(option_value) >> options->m_num_tidl_subgraphs;

        if(options->m_num_tidl_subgraphs > MAX_NUM_TIDL_SUBGRAPHS) 
        {
            printf("ERROR : max_num_subgraphs > %d not allowed \n", (int32_t)MAX_NUM_TIDL_SUBGRAPHS);
            return false;
        }
    }

    // TODO: fix denylist
    if (strcmp("deny_list", option_name.c_str()) == 0)        //option for Deny_List
    {
        try 
        {
          std::string str = option_value;
          char *cstr = new char[str.length() + 1];
          strcpy(cstr, str.c_str());
          options->m_deny_list = TIDL_readCommaSeparatedString(cstr);
          delete cstr;
        }
        catch(std::string &e) {
            printf("ERROR : could not parse malformed deny_list option");
            return false;
        }
    }

    if (strcmp("deny_list:layer_type", option_name.c_str()) == 0)  //option for Deny_List_type
    {
        try 
        {
          std::string str = option_value;
          char *cstr = new char[str.length() + 1];
          strcpy(cstr, str.c_str());
          options->m_deny_list_layer_type = TIDL_readCommaSeparatedString(cstr);
          delete cstr;
        }
        catch(std::string &e) {
            printf("ERROR : could not parse malformed deny_list option");
            return false;
        }
    }
    if (strcmp("deny_list:layer_name", option_name.c_str()) == 0)     //option for Deny_List_name
    {
        try 
        {
          std::string str = option_value;
          char *cstr = new char[str.length() + 1];
          strcpy(cstr, str.c_str());
          options->m_deny_list_layer_name = TIDL_readCommaSeparatedString(cstr);
          delete cstr;
        }
        catch(std::string &e) {
            printf("ERROR : could not parse malformed deny_list option");
            return false;
        }
    }

    if (strcmp("allow_list:layer_name", option_name.c_str()) == 0)     //option for allow_List_name
    {
        try 
        {
          std::string str = option_value;
          char *cstr = new char[str.length() + 1];
          strcpy(cstr, str.c_str());
          options->m_allow_list_layer_name = TIDL_readCommaSeparatedString(cstr);
          delete cstr;
        }
        catch(std::string &e) {
            printf("ERROR : could not parse malformed allow_list option");
            return false;
        }
    }

    if (strcmp("deny_list", option_name.c_str()) == 0)  {
        try {
            options->m_deny_list_int = tidl_fillDenyListOption(option_value);
        } catch(std::string &e) {
            printf("ERROR : could not parse malformed 'deny_list' option");
            return false;
        } 
    }

    if (!strcmp("accuracy_level", option_name.c_str())) 
    {
        std::map<std::string, int> valid_calibs {{"0", 64}, {"1", 7}, {"9", 9}};  // 9 will be mapped to suitable flag based on advanced options
        if(valid_calibs.find(option_value) == valid_calibs.end()) 
        {
            printf("ERROR : unsupported accuracy_level");
            return false;
        }
        options->m_tidl_calibration_flags = valid_calibs[option_value];
    }

    if (!strcmp("advanced_options:calibration_frames", option_name.c_str())) 
    {
        std::stringstream(option_value) >> options->m_calibration_frames;
        // TODO: any invalid option_values? like negative, or too many frames?
    }

    if (!strcmp("advanced_options:calibration_iterations", option_name.c_str())) 
    { 
        std::stringstream(option_value) >> options->m_calibration_iterations;
        // TODO: any invalid option_values? like negative, or too many iters?
    }

    if(!strcmp("advanced_options:mixed_precision_factor",option_name.c_str()))
    {
      std::stringstream(option_value) >> options->m_mixed_precision_factor;
    }
    if(!strcmp("advanced_options:model_group_id",option_name.c_str()))
    {
      std::stringstream(option_value) >> options->m_model_group_id;
    }

    if (!strcmp("advanced_options:quantization_scale_type", option_name.c_str())) 
    { 
        std::map<std::string, int> quantization_scale_type_mapping {{"0", TIDL_QuantStyleNP2Fixed}, {"1", TIDL_QuantStyleP2Dynamic}, {"3", TIDL_QuantStyleAsymNP2_TFL}};
        if(quantization_scale_type_mapping.find(option_value) == quantization_scale_type_mapping.end()) 
        {
            printf("ERROR : unsupported quantization_scale_type : specify either '0', '1' or '3' ");
            return false;
        }
        options->m_quantization_scale_type = quantization_scale_type_mapping[option_value];
    }

    if (!strcmp("advanced_options:high_resolution_optimization", option_name.c_str())) 
    { 
      std::stringstream(option_value) >> options->m_high_resolution_optimization;
    }

    if (!strcmp("advanced_options:pre_batchnorm_fold", option_name.c_str())) 
    { 
        std::stringstream(option_value) >> options->m_pre_batchnorm_fold;
    }
    if (!strcmp("advanced_options:add_data_convert_ops", option_name.c_str())) 
    { 
        std::stringstream(option_value) >> options->m_add_data_convert_ops;
    }

    if (!strcmp("ti_internal_nc_flag", option_name.c_str())) 
    { 
        std::stringstream(option_value) >> options->m_compileConstraintsFlag;
    }

    if (strcmp("ti_internal_reserved_1", option_name.c_str()) == 0)  
    {
        try 
        {
          std::string str = option_value;
          char *cstr = new char[str.length() + 1];
          strcpy(cstr, str.c_str());
          std::vector<std::string> ctrl = TIDL_readCommaSeparatedString(cstr);
          delete cstr;

          for(auto& s : ctrl)
          {
            int x;
            std::stringstream(s) >> x;
            options->m_reserved_ctrl_1.push_back(x);
          }
          options->m_reserved_ctrl_1.push_back(-1); //Read of this particular option is terminated with (-1)
        }
        catch(std::string &e) {
            printf("ERROR : could not parse malformed ti_internal_reserved_1 option");
            return false;
        }

    }
    
    if (!strcmp("advanced_options:output_feature_16bit_names_list", option_name.c_str())) 
    {
      options->m_output_feature_16bit_names_list = option_value;
    }
    if (!strcmp("advanced_options:params_16bit_names_list", option_name.c_str())) 
    {
      options->m_params_16bit_names_list = option_value;
    }
    if (!strcmp("object_detection:meta_layers_names_list", option_name.c_str())) 
    {
      options->m_meta_layers_names_list = option_value;
    }
    if (!strcmp("object_detection:meta_arch_type", option_name.c_str()))
    {
        std::stringstream(option_value) >> options->m_meta_arch_type;
    }

    if (!strcmp("object_detection:confidence_threshold", option_name.c_str())) {
        std::stringstream(option_value) >> options->odUserParams.confidence_threshold;
    }
    if (!strcmp("object_detection:nms_threshold", option_name.c_str())) {
        std::stringstream(option_value) >> options->odUserParams.nms_threshold;
    }
    if (!strcmp("object_detection:top_k", option_name.c_str())) {
        std::stringstream(option_value) >> options->odUserParams.top_k;
    }
    if (!strcmp("object_detection:keep_top_k", option_name.c_str())) {
        std::stringstream(option_value) >> options->odUserParams.keep_top_k;
    }

    // below options will be used only if accuracy_level = 9
    if (!strcmp("advanced_options:activation_clipping", option_name.c_str())) { 
        std::stringstream(option_value) >> options->m_activation_clipping;
    }
    if (!strcmp("advanced_options:weight_clipping", option_name.c_str())) { 
        std::stringstream(option_value) >> options->m_weight_clipping;
    }
    if (!strcmp("advanced_options:bias_calibration", option_name.c_str())) { 
        std::stringstream(option_value) >> options->m_bias_calibration;
    }
    if (!strcmp("advanced_options:channel_wise_quantization", option_name.c_str())) { 
        std::stringstream(option_value) >> options->m_channel_wise_quantization;
    }
    if (!strcmp("advanced_options:bias_clipping", option_name.c_str())) { 
        std::stringstream(option_value) >> options->m_bias_clipping;
    }
    return true;
}

/** Validated conditions on interface options if any are met */
bool TIDL_checkInterfaceOptions(TIDL_osrtOptions * options)
{
  if (options->m_tidl_tools_path.empty()) 
  {
    printf("ERROR : tidl_tools_path must be provided");
    return false;
  }

  if (options->m_artifacts_folder.empty()) 
  {
    printf("ERROR : artifacts_folder must be provided");
    return false;
  }

  if(mkdir(options->m_temp_folder.c_str(), 0755))
  {
    printf("ERROR : mkdir tempDir failed");
    return false;
  }

  if(((options->m_deny_list_layer_name.size() > 0) || (options->m_deny_list_layer_type.size() > 0) || (options->m_deny_list.size() > 0) || (options->m_deny_list_int.size() > 0))
       && (options->m_allow_list_layer_name.size() > 0))
  {
    printf("ERROR : Specify either allow list or deny list - cannot specify both simultaneously\n");
    return false;
  }

  return true;
} 

/** Options derived from the basic options read from interface */
void TIDL_derivedInterfaceOptions(TIDL_osrtOptions * options)
{  
  if(options->m_tidl_calibration_flags == 9) //user defined accuracy level
  {
    options->m_tidl_calibration_flags = options->m_activation_clipping * TIDL_CalibOptionActivationRange +     //default 1
                                        options->m_weight_clipping * TIDL_CalibOptionWeightRange +     //default 1
                                        options->m_bias_calibration * TIDL_CalibOptionBiasCalibration +    //default 1
                                        options->m_channel_wise_quantization * TIDL_CalibOptionPerChannelWeightQuantization + //default 0
                                        options->m_bias_clipping * TIDL_CalibOptionBiasRange;   //default 0
  }

  options->m_temp_folder = options->m_artifacts_folder + "/tempDir";
}

/** Print interface options for debug purposes */
void TIDL_printInterfaceOptions(TIDL_osrtOptions * options)
{
  if(options->m_debug_level)
  {
    printf("tidl_tools_path                                 = %s \n", options->m_tidl_tools_path.c_str());
    printf("artifacts_folder                                = %s \n", options->m_artifacts_folder.c_str());
    printf("tidl_tensor_bits                                = %d \n", options->m_num_param_bits);
    printf("debug_level                                     = %d \n", options->m_debug_level);
    printf("num_tidl_subgraphs                              = %d \n", options->m_num_tidl_subgraphs);
    printf("tidl_denylist                                   = ");     //option for Deny_List
    for(int i = 0; i < options->m_deny_list.size(); i++)
    {
      printf("%s   ", options->m_deny_list[i].c_str());
    }
    printf("\n");
    printf("tidl_denylist_layer_name                        = ");     //option for Deny_List_Name
    for(int i = 0; i < options->m_deny_list_layer_name.size(); i++)
    {
      printf("%s   ", options->m_deny_list_layer_name[i].c_str());
    }
    printf("\n");
    printf("tidl_denylist_layer_type                         = ");    //option for Deny_List_Type
    for(int i = 0; i < options->m_deny_list_layer_type.size(); i++)
    {
      printf("%s   ", options->m_deny_list_layer_type[i].c_str());
    }
    printf("\n");
    printf("tidl_allowlist_layer_name                        = ");     //option for allow_List_Name
    for(int i = 0; i < options->m_allow_list_layer_name.size(); i++)
    {
      printf("%s   ", options->m_allow_list_layer_name[i].c_str());
    }
    printf("\n");
    printf("model_type                                      = %s \n",options->m_model_type.c_str());
    printf("tidl_calibration_accuracy_level                 = %d \n", options->m_tidl_calibration_flags);
    printf("tidl_calibration_options:num_frames_calibration = %d \n", options->m_calibration_frames);
    printf("tidl_calibration_options:bias_calibration_iterations = %d \n", options->m_calibration_iterations);
    printf("mixed_precision_factor = %f \n",options->m_mixed_precision_factor);
    printf("model_group_id = %d \n",options->m_model_group_id);
    printf("power_of_2_quantization                         = %d \n", options->m_quantization_scale_type);
    printf("enable_high_resolution_optimization             = %d \n", options->m_high_resolution_optimization);
    printf("pre_batchnorm_fold                              = %d \n", options->m_pre_batchnorm_fold);
    printf("add_data_convert_ops                          = %d \n", options->m_add_data_convert_ops);
    printf("output_feature_16bit_names_list                 = %s \n", options->m_output_feature_16bit_names_list.c_str());
    printf("m_params_16bit_names_list                       = %s \n", options->m_params_16bit_names_list.c_str());
    printf("reserved_compile_constraints_flag               = %d \n", options->m_compileConstraintsFlag);
    printf("ti_internal_reserved_1                          = ");
    for(auto& x : options->m_reserved_ctrl_1)
    {
      printf("%d   ", x);
    }
    printf("\n");
  }
}

/** Copy data from src file to dst file */
void TIDL_copyFile(std::string basename, std::string dstdir, std::string srcdir) {
    std::string src_fname = srcdir + "/" + basename;
    std::string dst_fname = dstdir + "/" + basename;
    int src_fd = open(src_fname.c_str(), O_RDONLY);
    int dst_fd = open(dst_fname.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ssize_t size = lseek(src_fd, 0, SEEK_END); lseek(src_fd, 0, SEEK_SET);
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);

    {
        auto done = 0;
        auto remaining = size;
        while(remaining) {
            int ret = read(src_fd, buffer.get() + done, remaining);
            done += ret;
            remaining -= ret;
        }
    }
    {
        auto done = 0;
        auto remaining = size;
        while(remaining) {
            int ret = write(dst_fd, buffer.get() + done, remaining);
            done += ret;
            remaining -= ret;
        }
    }

    close(src_fd);
    close(dst_fd);
}

/* Check for OD related options read from interface */
bool TIDL_OdOptionChecks(TIDL_osrtOptions * options, std::vector<int> valid_meta_arch_type, bool hasDetectionPostprocLayer)
{
  bool status = false;
  if(options->m_meta_layers_names_list.empty() && (options->m_meta_arch_type != TIDL_metaArchTfliteRtSsdDetectionLayer))
  {
    options->m_meta_arch_type = -1;
    printf("\nWARNING : 'meta_layers_names_list' is not provided - running OD post processing in ARM mode \n \n");
  }
  else if(options->m_meta_arch_type != TIDL_metaArchTfliteRtSsdDetectionLayer)
  {
    //Check if meta_layers_names_list file exists
    std::ifstream ifile(options->m_meta_layers_names_list.c_str());
    if(! ifile.good())
    {
      printf("\nERROR : File provided in meta_layers_names_list does not exist : %s \n \n", options->m_meta_layers_names_list.c_str());
      return false;
    }
    //Check if metaArchType is valid
    if(std::find(valid_meta_arch_type.begin(), valid_meta_arch_type.end(), options->m_meta_arch_type) == valid_meta_arch_type.end()) 
    {
      printf("\nERROR : 'meta_arch_type' = %d not valid. Please provide valid 'meta_arch_type'. \n \n", options->m_meta_arch_type);
      return false;
    }
  }
  return true;
}

} //extern "C"

/** find quantization scale based on min/max range of data */
float TIDL_findMaxQuantizationScale(float min, float max, int32_t elementSizeInBits)
{
    float absRange = (fabs(max) > fabs(min)) ? fabs(max) : fabs(min);
    absRange = (float)ceil(log((double)absRange) / log((double)2));
    absRange = pow(2.0, (double)absRange);
    float quantPrec;
    if (absRange != 0)
    {
        quantPrec = ((1.0*(1 << (elementSizeInBits - 1))) / absRange);
    }
    else
    {
        quantPrec = 1;
    }

    return quantPrec;
}

/** Convert data to float and find range of data */
void TIDL_runtimesFindRange( float * src, int32_t n, int32_t c, int32_t h, int32_t w, float src_scale, int32_t zero, float &min, float &max)
{
    float curr;
    min = FLT_MAX;
    max = -FLT_MAX;
    int32_t i0, i1, i2, i3;
    for(i0 = 0; i0 < n; i0++){
      for (i1 = 0; i1 < c; i1++) 
      {
          for (i2 = 0; i2 < h; i2++) 
          {
              for (i3 = 0; i3 < w; i3++) 
              {
                  curr = ((src[i0*c*h*w + i1 + i2*w*c + i3*c] - zero)*src_scale);
                  min = curr < min ? curr : min;
                  max = curr > max ? curr : max;
              }
          } 
      }
    }
}

/* Read parameters from device config file */
void TIDL_readDeviceConfigParams(char * fileName)
{
  std::ifstream ifile(fileName);
  if(! ifile.good())
  {
    printf("\nERROR : Device config file does not exist : %s \n \n", fileName);
    return;
  }
  std::string line;
  while(std::getline(ifile, line))
  {
    int equalPos = line.find("=");
    if(equalPos != -1) /* if = exists in line */
    {
      std::string tokenName = line.substr(0, equalPos);
      std::string tokenValue = line.substr(equalPos + 1, line.length());
      tokenName.erase(remove(tokenName.begin(), tokenName.end(), ' '), tokenName.end()); /* remove spaces */
      tokenValue.erase(remove(tokenValue.begin(), tokenValue.end(), ' '), tokenValue.end()); /* remove spaces */
      std::istringstream tokenValSs(tokenValue);
      int tokenVal;
      tokenValSs >> tokenVal;
      
      /* Parse import tool required device config parameters here */
      if(strcmp(tokenName.c_str(), "DEVICE_NAME") == 0)
      {
        gParams.deviceName = tokenVal;
      }
    }
  }
}

/* Set global import config parameters - parameters which are needed by optimizeNet to decide optimization of layers must be put here */
int32_t TIDL_runtimesGparamsInit(TIDL_osrtOptions * osrt_options, int32_t modelType)
{
  setDefaultParams(&gParams);
  gParams.numParamBits = osrt_options->m_num_param_bits;
  gParams.numFeatureBits = osrt_options->m_num_param_bits;
  gParams.foldPreBnConv2D = osrt_options->m_pre_batchnorm_fold;
  gParams.addDataConvertToNet = osrt_options->m_add_data_convert_ops;
  gParams.inFileFormat = 1;  // raw data
  gParams.modelType = modelType;   // tflite runtime - 5, ONNX runtime - 6
  gParams.quantizationStyle = osrt_options->m_quantization_scale_type;
  char * tidl_tools_path = const_cast<char *>(osrt_options->m_tidl_tools_path.c_str());
  if(tidl_tools_path)
  {
    strcpy((char*)gParams.tidlStatsTool, tidl_tools_path);
    strcat((char*)gParams.tidlStatsTool,"/PC_dsp_test_dl_algo.out");
    strcpy((char*)gParams.perfSimTool, tidl_tools_path);
    strcat((char*)gParams.perfSimTool,"/ti_cnnperfsim.out");
    strcpy((char*)gParams.graphVizTool, tidl_tools_path);
    strcat((char*)gParams.graphVizTool,"/tidl_graphVisualiser.out");
    strcpy((char*)gParams.perfSimConfig, tidl_tools_path);
    strcat((char*)gParams.perfSimConfig,"/device_config.cfg");
  }
  else
  {
    printf("Please provide TIDL tools path \n");
    exit(-1);
  }

  /* Device Name is manipulated as part of import, so need to read from device config file and populate in gParams */
  TIDL_readDeviceConfigParams((char*)gParams.perfSimConfig);
}

/** Add output data layer to subgraph */
int32_t TIDL_addOutputDataLayer(int32_t idx, const char * layerName)
{
  int32_t layerIndex = runtimes_import_state.layerIndex++;
  sTIDL_LayerPC_t& layer = orgTIDLNetStructure.TIDLPCLayers[layerIndex];
  layer.layerType         = TIDL_DataLayer;
  layer.numInBufs         = 1;
  layer.numOutBufs        = -1;
  layer.outData[0].dataId = 0;
  strcpy((char*)layer.name, layerName);
  strcpy((char*)layer.inDataNames[0], layerName);
  strcpy((char*)layer.outDataNames[0], layerName);
  layer.outConsumerCnt[0] = 0;
  strcpy((char*)outDataNames[idx], layerName);
  return layerIndex;
}

/** Add input data layer to subgraph */
int32_t TIDL_addInputDataLayer(int32_t idx,  int32_t numBatches, int32_t inNumCh, int32_t inHeight, int32_t inWidth, const char * layerName)
{
  gParams.numBatches[idx] = numBatches;
  gParams.inNumChannels[idx] = inNumCh;
  gParams.inHeight[idx] = inHeight;
  gParams.inWidth[idx] = inWidth;
  int32_t layerIndex = runtimes_import_state.layerIndex++;
  sTIDL_LayerPC_t& layer = orgTIDLNetStructure.TIDLPCLayers[layerIndex];
  layer.layerType         = TIDL_DataLayer;
  layer.numInBufs         = -1;
  layer.numOutBufs        = 1;
  layer.outData[0].dataId = runtimes_import_state.dataIndex++;
  layer.outData[0].elementType  = gParams.inElementType[idx];
  layer.outData[0].numDim       = 4;
  layer.outData[0].dimValues[0] = gParams.numBatches[idx];
  layer.outData[0].dimValues[1] = gParams.inNumChannels[idx];
  layer.outData[0].dimValues[2] = gParams.inHeight[idx];
  layer.outData[0].dimValues[3] = gParams.inWidth[idx];
  strcpy((char *)layer.name,  layerName);
  strcpy((char *)layer.outDataNames[0],  layerName);
  layer.outConsumerCnt[0] = 1;
  layer.outConsumerLinked[0] = 0;

  return layerIndex;
}

/** This runtimes function calls "tidl_optimizeNet" in the backend for layer level graph optimization */
int32_t TIDL_runtimesOptimizeNet(int32_t osrtDebugPrintLevel)
{
  TIDL_osrtDebugPrint(osrtDebugPrintLevel, "In TIDL_runtimesOptimizeNet: LayerIndex = %d, dataIndex = %d \n", runtimes_import_state.layerIndex, runtimes_import_state.dataIndex);

  tidl_optimizeNet(orgTIDLNetStructure, runtimes_import_state.layerIndex, runtimes_import_state.dataIndex);

  return 0;
}

/** Since we call postProcessNet multiple times, some of the variables may be overwritten, so restore them to 
 * original values in this function to be used again */
int32_t tidl_setParamsForPostProcessNet(int32_t tensor_bits)
{
  gParams.numParamBits = tensor_bits;
  gParams.numFeatureBits = tensor_bits;

  gParams.executeNetworkCompiler = 1;
  
  /** For all networks, raw input data is saved as float with corresponding quantization scales
   * For pointpillars 3D OD network, indices cannot be quantized so are saved in int32 format only
   * So need to set rawDataInElementType as int32 to read indices correctly during calibration */
  for (int i = 0; i < TIDL_MAX_ALG_IN_BUFS; i++)
  {
    if(gParams.inElementType[i] == TIDL_SignedWord) //indices input
    {
      gParams.rawDataInElementType[i] = TIDL_SignedWord;
    }
  }
}

/** This function calls "TIDL_import_backend" to run calibration, quantization and save the final network files */
int32_t TIDL_runtimesPostProcessNet(TIDL_osrtOptions * osrt_options, int32_t calibrationFrames, int32_t numParamBits, void * subGraphPtr, void * configParams, float * inQuantFactor, int32_t * zp, char* subGraphName)
{
  TIDL_osrtDebugPrint(osrt_options->osrtDebugPrintLevel, "In TIDL_runtimesPostProcessNet \n");
  int32_t status = 0;
  sTIDL_OrgNetwork_t * netPtr = (sTIDL_OrgNetwork_t *)subGraphPtr;
  orgTIDLNetStructure = *netPtr;
  TIDL_allocAndCopyModelParams(&orgTIDLNetStructure, (sTIDL_OrgNetwork_t *)subGraphPtr, orgTIDLNetStructure.numLayers);
  
  /* Restore gParams saved during init */
  if(configParams != NULL)
  {
    /* This backup is needed since gParams populated during init for a subgraph won't be preserved during invoke for the same subgraph
      Specifically required for parameters like inQuantFactor and inZeroPoint which will vary across subgraphs */
    tidl_import_config * configParamsCast = (tidl_import_config *)configParams;
    gParams = *configParamsCast;
  }
  
  memset(&tIDLNetStructure, 0, sizeof(sTIDL_Network_t));
  
  tidl_setParamsForPostProcessNet(numParamBits);
  gParams.numFramesBiasCalibration = calibrationFrames;
  gParams.calibrationOption = osrt_options->m_tidl_calibration_flags;
  gParams.biasCalibrationIterations = osrt_options->m_calibration_iterations;
  gParams.mixedPrecisionFactor = osrt_options->m_mixed_precision_factor;
  gParams.modelGroupId = osrt_options->m_model_group_id;
  gParams.enableHighResOptimization = osrt_options->m_high_resolution_optimization;
  gParams.compileConstraintsFlag = osrt_options->m_compileConstraintsFlag;
  gParams.foldPreBnConv2D = osrt_options->m_pre_batchnorm_fold;

  strcpy((char *)&gParams.outputFeature16bitNamesList[0], const_cast<char *>(osrt_options->m_output_feature_16bit_names_list.c_str()));
  strcpy((char *)&gParams.params16bitNamesList[0], const_cast<char *>(osrt_options->m_params_16bit_names_list.c_str()));

  for(int i = 0; i < osrt_options->m_reserved_ctrl_1.size(); i++)
  {
    gParams.ddrLayers[i] = osrt_options->m_reserved_ctrl_1[i];
  }
  
  if((gParams.addDataConvertToNet & ADD_DC_LAYER_AT_INPUT) == 0)
  {
    /** If data convert layer not present, need to get the input tensor scale separately using representative input frames
     * For data convert layer:
     * This scale is computed as part of calibration process similar to other layers, so no need to specifically populate here
     * It is populated in runtimes import init to model tensor scale (same as that in RT expected tensor scale - set as part of RT invoke) so ARM conversion is bypassed 
     */
    for(int i = 0; i < TIDL_MAX_ALG_IN_BUFS; i++)
    {
      gParams.inQuantFactor[i] = inQuantFactor[i];
      if((gParams.quantizationStyle == TIDL_QuantStyleAsymNP2_TFL) && (zp != NULL)) // Zp required only for asym quant flow
      {
        gParams.inZeroPoint[i] = zp[i];
      }
      if(numParamBits == 32)
      {
        gParams.inQuantFactor[i] = 1.0;
        gParams.inZeroPoint[i] = 0.0;
      }
    }
  }

  int netInputIdx = 0;
  for(int i = 0; i < orgTIDLNetStructure.numLayers; i++)
  {
    if((orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_DataLayer) && (orgTIDLNetStructure.TIDLPCLayers[i].numInBufs == -1))
    {
      int32_t outDataId;
      int32_t currInputIdx = netInputIdx;
      orgTIDLNetStructure.TIDLPCLayers[i].outData[0].tensorScale = gParams.inQuantFactor[currInputIdx];
      orgTIDLNetStructure.TIDLPCLayers[i].outData[0].tensorZeroPoint = gParams.inZeroPoint[currInputIdx];
      outDataId = orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dataId;
      netInputIdx++;
      /* Identify all the layers which are consumer of input data layer and update tensorScale and tensorZeroPoint
      in their inDataParams*/
      for (int k = 0; k < orgTIDLNetStructure.numLayers; k++ )
      {
        for ( int inBufIdx = 0;inBufIdx < orgTIDLNetStructure.TIDLPCLayers[k].numInBufs; inBufIdx++)
        {
          if ( orgTIDLNetStructure.TIDLPCLayers[k].inData[inBufIdx].dataId == outDataId)
          {
            orgTIDLNetStructure.TIDLPCLayers[k].inData[inBufIdx].tensorScale     = orgTIDLNetStructure.TIDLPCLayers[i].outData[0].tensorScale;
            orgTIDLNetStructure.TIDLPCLayers[k].inData[inBufIdx].tensorZeroPoint = orgTIDLNetStructure.TIDLPCLayers[i].outData[0].tensorZeroPoint;
          }
        }
      }
    }
  }
  //tidl_updateWeightElemSize(&orgTIDLNetStructure, &gParams, orgTIDLNetStructure.numLayers);
  for(int i = 0; i < orgTIDLNetStructure.numLayers; i++)
  {
    if(orgTIDLNetStructure.TIDLPCLayers[i].layerType != TIDL_DataLayer)
      orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits = gParams.numParamBits;
  }
  
  if(numParamBits == 32)
  {
    tidl_convertElementTypeGivenParambits(&orgTIDLNetStructure, orgTIDLNetStructure.numLayers, 32);
  }

  const char * artifacts_folder = const_cast<char *>(osrt_options->m_temp_folder.c_str());
  snprintf((char *)inConfigFilename, FILE_NAME_SIZE, "%s/%s_tidl_io_", artifacts_folder, subGraphName);
  snprintf((char *)gParams.outputNetFile, FILE_NAME_SIZE, "%s/%s_tidl_net.bin", artifacts_folder, subGraphName);
  snprintf((char *)gParams.outputParamsFile, FILE_NAME_SIZE, "%s/%s_tidl_io_", artifacts_folder, subGraphName);
  sprintf((char *)gParams.inData, "%s/%s_calib_raw_data.bin", artifacts_folder, subGraphName);
  status = TIDL_import_backend(orgTIDLNetStructure.numLayers);

  return status;
}

/** We need to call postProcessNet multiple times, so save the optimized subgraph, which can be copied 
 * during postProcessNet and used multiple times */
void TIDL_saveTidlSubGraph(void ** subGraphPtr)
{
  *(sTIDL_OrgNetwork_t**)subGraphPtr = new sTIDL_OrgNetwork_t;
  if ( *subGraphPtr == NULL )
  {
    printf("Unable to allocate memory to save the subgraph \n");
    return;
  }
  **((sTIDL_OrgNetwork_t**)subGraphPtr) = orgTIDLNetStructure;
}

void TIDL_saveGparams(void ** configParams)
{
  *(tidl_import_config**)configParams = new tidl_import_config;
  if ( *configParams == NULL )
  {
    printf("Unable to allocate memory to save the import config parameters \n");
    return;
  }
  **((tidl_import_config**)configParams) = gParams;
}


/** Broadcast vector buffer to have a modified dimension */
void TIDL_broadcastFloatTensor(sBuffer_t &buf, int32_t bufSize)
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
