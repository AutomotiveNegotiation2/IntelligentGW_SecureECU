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
@file    tidl_alg.c
@brief   This file contains TILD alg inteface implementation
@version 0.1 (Oct 2016) : Initial version [ADK]
@version 0.5 (Jan 2017) : Cleaned up [ADK]
----------------------------------------------------------------------------
*/
#include "tidl_alg_int.h"
#include "tidl_types.h"
#include "tidl_layer.h"
#include "itidl_ti.h"
#include "tidl_genericFlow_c7x.h"
#include "perfsim.h"
#include "tidl_priv_algo.h"
#include "tidl_preEmption.h"
#include "tidl_deviceInfo.h"
#include "tidl_device_functions.h"
#include "tidl_device_utils.h"
#include "tidl_alg_utils.h"
#include "tidl_commonUtils.h"

#define TEMP_FORCE_OUTPUT_TO_DDR (0)
#define VAILD_DDR_BUFFER         (1U)
#define TIDL_DDR_EXCESS_SCRATCH  (512*1024U)


#ifdef BUILD_WITH_CUDA
#include "tidl_cuda.h"
#endif
#include "math.h"
#include "float.h"
#ifdef HOST_EMULATION
#include "time.h"
#endif

#define TIDL_L3_SCRATCH_SIZE (128U*1024U)
#define TIDL_L3_MSMC_DDR_STAGING_MEM  ( 1025U * 1024U)

#define USE_16BIT_BIAS_FOR_8BIT_MODE (1)


#if (ENABLE_TRACE_PROFILE) && defined(CORE_DSP)
int64_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, \
accCycle1,accCycle2,accCycle3,accCycle4,accCycle5,accCycle6;
#endif


#define TIDL_DDR_MEMREC_CACHEABLE        ((IALG_MemSpace)IALG_EXTERNAL)
#if defined (SOC_J784S4)
#define TIDL_DDR_MEMREC_NON_CACHEABLE    ((IALG_MemSpace)IALG_EXTERNAL_NON_CACHEABLE)
#else
#define TIDL_DDR_MEMREC_NON_CACHEABLE    ((IALG_MemSpace)IALG_EXTERNAL)
#endif
/**
* IVISION interface of the algorithm
*/
const int32_t ImplementationID =0;

const IVISION_Fxns TIDL_VISION_FXNS =
{
  {
    (void*) (&ImplementationID),
    &TIDL_activate,
    &TIDL_alloc,
    (int32_t (*)(IALG_Handle, IALG_Cmd, IALG_Status*))NULL,
    &TIDL_deactivate,
    &TIDL_free,
    &TIDL_init,
    (void (*)(IALG_Handle, const IALG_MemRec*, IALG_Handle, const IALG_Params*))NULL,
    &TIDL_numAlloc
  },
  &TIDL_process,
  &TIDL_control
};

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_numAlloc
@brief      Function to return the number of memory table needed by algorithm
@remarks    None
@return     Number of memory table
----------------------------------------------------------------------------
*/
int32_t TIDL_numAlloc(void)
{
  return (int32_t)MAX_NUM_MEMRECS;
}

static int32_t TIDL_getMaxParamSizeInBytes(sTIDL_Layer_t * tidlLayer)
{
  int32_t dataSize = 0;

  if ( ( tidlLayer->layerType == TIDL_ConvolutionLayer ) ||
           ( tidlLayer->layerType == TIDL_Deconv2DLayer) ||
           ( tidlLayer->layerType == TIDL_BatchNormLayer) ||
           ( tidlLayer->layerType == TIDL_BatchReshapeLayer) ||
           ( tidlLayer->layerType == TIDL_InnerProductLayer))
  {
      if ( ( tidlLayer->layerType == TIDL_ConvolutionLayer ) ||
           ( tidlLayer->layerType == TIDL_Deconv2DLayer) )
      {
        dataSize = ( tidlLayer->layerParams.convParams.numOutChannels *
                   tidlLayer->layerParams.convParams.numInChannels *
                   tidlLayer->layerParams.convParams.kernelW *
                   tidlLayer->layerParams.convParams.kernelH )/
                   tidlLayer->layerParams.convParams.numGroups;
      }
  }

  return (dataSize * sizeof(float32_tidl) );

}

static inline int32_t TIDL_checkDdrTransferParams(const sBufferInfo_t* bufInfo)
{
  int32_t paramsOk = 0U;
  if(bufInfo->baseMem != NOT_VALID && bufInfo->space == DDR)
  {
    paramsOk = VAILD_DDR_BUFFER;
  }
  return paramsOk;
}

static void TIDL_printMemorySizeStats(const IALG_MemRec memRec[], 
  int32_t numMemRec)
{
  int32_t i, totalSize[IALG_EXTERNAL_NON_CACHEABLE + 1] = {0};
  const char *spaceMapping[IALG_EXTERNAL_NON_CACHEABLE+1];
  const char *attrMapping[IALG_WRITEONCE + 1];
  spaceMapping[IALG_DARAM0]   = "L1D";
  spaceMapping[IALG_DARAM1]   = "L2";
  spaceMapping[IALG_SARAM0]   = "L3/MSMC";
  spaceMapping[IALG_EXTERNAL] = "DDR Cacheable";
  spaceMapping[IALG_EXTERNAL_NON_CACHEABLE] = "DDR Non-cacheable";

  attrMapping[IALG_SCRATCH] = "Scratch";
  attrMapping[IALG_PERSIST] = "Persistent";

  tidl_printf(1,"\n--------------------------------------------\n");

  tidl_printf(1,"TIDL Memory size requiement (record wise):\n");
  tidl_printf(1, "%-12s, %-12s, %-12s, %-12s \n","MemRecNum","Space","Attribute","Size(KBytes)");

  for( i = 0; i < numMemRec; i++){

    tidl_printf(1, "%-12d, %-12s, %-12s, %-8.2f \n",i, 
      spaceMapping[memRec[i].space], attrMapping[memRec[i].attrs], memRec[i].size/1024.0);
      totalSize[memRec[i].space] += memRec[i].size ;
  }
  tidl_printf(1,"--------------------------------------------\n");
  tidl_printf(1,"Total memory size requirement (space wise):\n");
  tidl_printf(1,"%-10s, %-10s\n", "Mem Space", "Size(KBytes)");
  for( i = 0; i <= TIDL_DDR_MEMREC_NON_CACHEABLE ; i++){
    if(totalSize[i]){
      tidl_printf(1,"%-10s, %-8.2f\n", spaceMapping[i], totalSize[i]/1024.0);
    }
  }
  tidl_printf(1,"--------------------------------------------\n");
  tidl_printf(1,"NOTE: Memory requirement in host emulation can be different from the same on EVM\n");
  tidl_printf(1,"      To get the actual TIDL memory requirement make sure to run on EVM with \n");
  tidl_printf(1,"      debugTraceLevel = 2\n\n");
  tidl_printf(1,"--------------------------------------------\n");
  return ;
}

static inline int32_t TIDL_getBufInfoAddr(sBufferInfo_t *pBufInfo, int32_t end){
  int32_t addr ;
  if(end) addr = pBufInfo->baseMem + pBufInfo->bufSize ;
  else    addr = pBufInfo->baseMem  ;
  return addr ;
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_alloc
@brief      Function to supply memory requirement to user
            refer algAlloc function for details in XADIS (ialg.h file)
@param      params       : Input Parameters
@param      parentFxns   : Parent function pointer
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
static sTIDL_LayerBuf_t TIDLLayersBuf = {0};
int32_t TIDL_alloc(const IALG_Params *params,
IALG_Fxns **parentFxns,
IALG_MemRec memRec[])
{
  int32_t status = IALG_EOK;
  int32_t l1MemSize, l2MemSize, l3MemSize;
  int32_t i, j;
  const TIDL_CreateParams * createParams =
  (const TIDL_CreateParams*)(const void*)params;
  sPerfSim_t * perfInfoOut = NULL;
  sDataFlowInfo_t * dataFlowInfo = NULL;

  status = TIDL_initDebugTraceParams(createParams->traceLogLevel, createParams->traceWriteLevel, createParams->TIDLVprintf, createParams->TIDLWriteBinToFile, createParams->TIDLReadBinFromFile, createParams->traceBaseName, createParams->tracePtr);
  tidl_printf(2,"TIDL_initDebugTraceParams Done \n");

  if (status != IALG_EOK)
  {
    status = TIDL_E_INVALID_DEBUG_TRACE_PRM;
  }

  if(status == IALG_EOK)
  {
    if (createParams->net->netVersion != TIDL_NET_VERSION)
    {
      status = TIDL_E_INVALID_NET_VERSION;
    }
  }

  if((status == IALG_EOK) && ((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == 0))
  {
    if (createParams->net->isQuantStatsAvailable == 0)
    {
      status = TIDL_E_QUANT_STATS_NOT_AVAILABALE;
    }
  }

  if(status == IALG_EOK)
  {
    if (createParams->isInbufsPaded == 0)
    {
      tidl_printf(1,"Padding of input buffer in Library is not supported now\n");
      status = IALG_EFAIL;
    }

  }

  if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_COMP) == TIDL_FLOW_CTRL_REF_COMP)
  {
    tidl_printf(0,"WARNING : TIDL_FLOW_CTRL_REF_COMP Support is deprecated in Inference Software now \n");
  }

  if (createParams->net->dataFlowInfo != 0)
  {
    perfInfoOut = (sPerfSim_t *)get_int8_t_pointer((int8_t *)(createParams->net), createParams->net->dataFlowInfo);
  }

  if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    perfInfoOut  = NULL;
  }

  if(NULL == perfInfoOut)
  {
    l1MemSize = TIDL_DEFAULT_L1_MEM_SIZE;
    l2MemSize = TIDL_DEFAULT_L2_MEM_SIZE;
    l3MemSize = TIDL_DEFAULT_L3_MEM_SIZE;
  }
  else
  {
    l1MemSize = TIDL_DEFAULT_L1_MEM_SIZE;
    l2MemSize = (perfInfoOut->simConfig.sizeL2MemKB * 1024);
    l3MemSize = perfInfoOut->simConfig.sizeL3MemKB * 1024;
  }

  if(status == IALG_EOK)
  {
    memRec[ALG_HANDLE_MEMREC].size          = (uint32_t)sizeof(TIDL_Obj);
    memRec[ALG_HANDLE_MEMREC].space         = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
    memRec[ALG_HANDLE_MEMREC].alignment     = 128;

    memRec[ALG_SCRATCH_L1_MEM_MEMREC].size       = (uint32_t)l1MemSize;
    memRec[ALG_SCRATCH_L1_MEM_MEMREC].attrs      = IALG_SCRATCH;
    memRec[ALG_SCRATCH_L1_MEM_MEMREC].alignment  = 128;
    memRec[ALG_SCRATCH_L1_MEM_MEMREC].space      = (IALG_MemSpace)IALG_DARAM0;

    memRec[ALG_SCRATCH_L2_MEM_MEMREC].size       = (uint32_t)l2MemSize;
    memRec[ALG_SCRATCH_L2_MEM_MEMREC].attrs      = IALG_SCRATCH;
    memRec[ALG_SCRATCH_L2_MEM_MEMREC].alignment  = 128;
    memRec[ALG_SCRATCH_L2_MEM_MEMREC].space      = IALG_DARAM1;

    memRec[ALG_SCRATCH_L3_MEM_MEMREC].size       = (uint32_t)l3MemSize;
    memRec[ALG_SCRATCH_L3_MEM_MEMREC].space      = (IALG_MemSpace)IALG_SARAM0;
    memRec[ALG_SCRATCH_L3_MEM_MEMREC].attrs      = IALG_SCRATCH;
    memRec[ALG_SCRATCH_L3_MEM_MEMREC].alignment  = 128;

    memRec[ALG_CREATE_PARAM_MEMREC].size        = (uint32_t)sizeof(TIDL_CreateParams);
    memRec[ALG_CREATE_PARAM_MEMREC].space       = TIDL_DDR_MEMREC_CACHEABLE;
    memRec[ALG_CREATE_PARAM_MEMREC].attrs       = IALG_PERSIST;
    memRec[ALG_CREATE_PARAM_MEMREC].alignment   = 128;

    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size     = 256 *1024; // Minimum 256 KB to allow some last unaligned transfers
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].space    = TIDL_DDR_MEMREC_CACHEABLE; /* Supposed to be read only during process call, so mark cacheable */
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].attrs    = IALG_PERSIST;
    memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].alignment = 128;

    memRec[ALG_LAYERS_MEMREC].size                 = 0;
    memRec[ALG_LAYERS_MEMREC].space                = TIDL_DDR_MEMREC_CACHEABLE;
    memRec[ALG_LAYERS_MEMREC].attrs                = IALG_PERSIST;
    memRec[ALG_LAYERS_MEMREC].alignment            = 128;

    memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size      = 256;
    memRec[ALG_REF_SCRATCH_BUFF_MEMREC].space     = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_REF_SCRATCH_BUFF_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_REF_SCRATCH_BUFF_MEMREC].alignment = 128;

    memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].size      = 256;
    memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].space     = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].attrs     = IALG_SCRATCH;
    memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].alignment = 128;

    memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size        = 256 + TIDL_DDR_EXCESS_SCRATCH; // Alloc at allocResize
    memRec[ALG_SCRATCH_DDR_MEM_MEMREC].space       = TIDL_DDR_MEMREC_CACHEABLE;
    memRec[ALG_SCRATCH_DDR_MEM_MEMREC].attrs       = IALG_SCRATCH;
    memRec[ALG_SCRATCH_DDR_MEM_MEMREC].alignment   = 128;

    /* ALG_SCRATCH_DATA_BUFF_MEMREC Will be filled
    as max of all the temp buffer requirement by all the layers */

    /* Allocate Memory to store newdataID's in TIDL_Handle to use in Process call */
    memRec[ALG_LAYERS_MEMREC].size +=
      (uint32_t)(sizeof(sTIDL_LayerBuf_t) +  128U);

    /* Initialize newDataId of inData with dataId, so that this can be used later
        to find the free output buffer for Re-using
    */
    if(createParams->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      for(i = 0; i <  createParams->net->numLayers; i++)
      {
        const sTIDL_Layer_t *TIDLLayerCur = &createParams->net->TIDLLayers[i];
        for(j = 0; j < TIDLLayerCur->numInBufs; j++)
        {
          TIDLLayersBuf.newInDataId[i][j] = TIDLLayerCur->inData[j];
        }
      }
    }

    for(i = 0; i <  createParams->net->numLayers; i++)
    {
      tidl_printf(1,"Alg Alloc for Layer # - %4d\n",i);
      if ( perfInfoOut != NULL )
      {
        dataFlowInfo = &perfInfoOut->sdataFlowInfo[i];
      }
      if(createParams->net->TIDLLayers[i].layersGroupId ==
          createParams->currLayersGroupId)
      {
        /* Request memory for genericFlowHandle and KernelHandle for supported layers */
        int32_t isNewGenericFlow = TIDL_isNewGenericFlowEnabled(createParams, i);
        if(((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0) && isNewGenericFlow)
        {
          uint32_t genricFlowHandleSize = sizeof(TIDL_GenericHandle);
          int32_t targetDevice = createParams->net->deviceName;
          int32_t numSubHandles = 1U;
          if(TIDL_isPadOTF(targetDevice))
          {
            if(TIDL_isLayerSpatialPooling(createParams, i))
            {
              if(dataFlowInfo->numSplit > 1)
              {
                numSubHandles = 3U;
              }
            }
          }
          uint32_t kerHandleSize = TIDL_getKernelHandleSize(createParams, i, numSubHandles);
          int32_t numGenericFlowHandles = TIDL_getNumGenericFlowHandles(&createParams->net->TIDLLayers[i]);
          int32_t numStHandles = TIDL_privGetNumHandles(dataFlowInfo);

          memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += (genricFlowHandleSize*numGenericFlowHandles*numStHandles);
          memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size += ((kerHandleSize*numGenericFlowHandles*numStHandles));
        }

        if(createParams->net->TIDLLayers[i].layerType == TIDL_ConvolutionLayer)
        {
          status = TIDL_conv2DAlloc(createParams, i, memRec, dataFlowInfo,  &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_Deconv2DLayer)
        {
          status = TIDL_deconv2DAlloc(createParams, i, memRec, dataFlowInfo, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_EltWiseLayer)
        {
          status = TIDL_eltWiseAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ShuffleChannelLayer)
        {
          status = TIDL_shuffleChannelAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ResizeLayer)
        {
          status = TIDL_resizeAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ArgMaxLayer)
        {
          status = TIDL_argMaxAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_PoolingLayer)
        {
          status = TIDL_poolingAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_CustomLayer)
        {
          status = TIDL_customLayerAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_BatchNormLayer)
        {
          status = TIDL_batchNormAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_SoftMaxLayer)
        {
          status = TIDL_softmaxAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_InnerProductLayer)
        {
          status = TIDL_innerProductAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ConcatLayer)
        {
          status = TIDL_concatAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_FlattenLayer)
        {
          status = TIDL_flattenAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_ConstDataLayer)
        {
          status = TIDL_constDataAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if ( (createParams->net->TIDLLayers[i].layerType == TIDL_DetectionOutputLayer) ||
                              (createParams->net->TIDLLayers[i].layerType == TIDL_OdPostProcessingLayer))
        {

          status = TIDL_detectOutAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_RoiPoolingLayer)
        {
          status = TIDL_roiPoolingAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if ((createParams->net->TIDLLayers[i].layerType == TIDL_SliceLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_CropLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_DataConvertLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_DepthToSpaceLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_OdOutputReformatLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_ReduceLayer)||
                (createParams->net->TIDLLayers[i].layerType == TIDL_ScatterElementsLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_SqueezeLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_ReshapeLayer)
                )
        {
          status = TIDL_flattenAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_ColorConversionLayer)
        {
          status = TIDL_flattenAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_BatchReshapeLayer)
        {
          status = TIDL_batchReshapeAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_PadLayer)
        {
          status = TIDL_padAlloc(createParams, i, memRec, &TIDLLayersBuf);
        }
        else
        {
          status = TIDL_E_UNSUPPORTED_LAYER;
        }
        if(status != IALG_EOK)
        {
          break;
        }
        memRec[ALG_LAYERS_MEMREC].size +=   (uint32_t)(sizeof(sTIDL_AlgLayer_t) +  128U);
      }
    }
  }
  if(status == IALG_EOK)
  {
    memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size          = 128;
    memRec[ALG_REF_OUTPUT_BUFF_MEMREC].space       = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_REF_OUTPUT_BUFF_MEMREC].attrs         = IALG_SCRATCH;
    memRec[ALG_REF_OUTPUT_BUFF_MEMREC].alignment  = 128;

    int32_t maxOutFeatMapSize = 0;
    int32_t maxOutFeatMapSize1 = 0;
    int32_t outFeatMapSize;
    int32_t maxParamSize = 0;

    for (i = 0; i < createParams->net->numLayers; i++)
    {
      int32_t paramSize;
      sTIDL_DataParams_t * dataParams = TIDL_getDataParams(createParams->net,
      createParams->net->TIDLLayers[i].outData.dataId);
      outFeatMapSize = dataParams->dimValues[TIDL_DIM_BATCH] *
                              dataParams->dimValues[TIDL_DIM_NUMCH] *
                              dataParams->pitch[TIDL_CHANNEL_PITCH] *
                              (TIDL_getDatElementSize(dataParams->elementType));

      outFeatMapSize = TIDL_privUpdateFeatMapSize(perfInfoOut, i, outFeatMapSize);

      if ( outFeatMapSize > maxOutFeatMapSize)
      {
        maxOutFeatMapSize = outFeatMapSize;
      }
      if ( (outFeatMapSize > maxOutFeatMapSize1) && (outFeatMapSize < maxOutFeatMapSize) )
      {
        maxOutFeatMapSize1 = outFeatMapSize;
      }

      paramSize = TIDL_getMaxParamSizeInBytes(&createParams->net->TIDLLayers[i]);

      maxParamSize = (paramSize > maxParamSize) ? paramSize : maxParamSize;

    }
    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY )
    {
      memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size          = (2U * sizeof(float32_tidl) * maxOutFeatMapSize) + TRACE_STRINGS_MEM_SIZE;/* Twice for input and output */
    }
    else
    {
      memRec[ALG_REF_SCRATCH_BUFF_MEMREC].size         = 128U;
      if(createParams->traceWriteLevel == 3)
      {
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size          = (uint32_t)((sizeof(float32_tidl) + 1U)* (uint32_t)maxOutFeatMapSize) + TRACE_STRINGS_MEM_SIZE;
      }
      else if(createParams->traceWriteLevel == 2)
      {
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size          = (2U*(uint32_t)maxOutFeatMapSize) + TRACE_STRINGS_MEM_SIZE;
      }
      else if(createParams->traceWriteLevel == 1)
      {
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size          = (uint32_t)maxOutFeatMapSize + TRACE_STRINGS_MEM_SIZE;
      }
      else
      {
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size          = 128U + TRACE_STRINGS_MEM_SIZE;
      }
    }

    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if ( ( createParams->net->calibrationOption & TIDL_CalibOptionActivationRange) ==
        TIDL_CalibOptionActivationRange)
      {
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += 128;
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += (createParams->net->numLayers *
                                                   TIDL_NUM_ACTIVATION_HISTOGRAM_BINS *
                                                   sizeof(int32_t));
        /* To store the min and max value of each layer */
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += 128;
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += (createParams->net->numLayers *
                                                   2 * sizeof(float32_tidl));
      }
    }

    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      if ( ( createParams->net->calibrationOption & TIDL_CalibOptionActivationRange) ==
        TIDL_CalibOptionActivationRange)
      {
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += 128;
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += (createParams->net->numLayers *
                                                   TIDL_NUM_ACTIVATION_HISTOGRAM_BINS *
                                                   sizeof(int32_t));
        /* To store the min and max value of each layer */
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += 128;
        memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size += (createParams->net->numLayers *
                                                   2 * sizeof(float32_tidl));
      }
    }

    if(createParams->traceWriteLevel == 4)
    {
      maxParamSize = maxParamSize + TRACE_STRINGS_MEM_SIZE;
      memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size = (maxParamSize >
                                                memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size) ?
                                                maxParamSize : memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size;
    }

    //shall remove this, for now ony changing properties to have NULL effect to avoid any assumption on number
    memRec[ALG_ANALYZE_NETWORK_MEMREC].size     = 128 ;//ALIGN_SIZE(128U, 128U) + ALIGN_SIZE((uint32_t)sizeof(sPerfSim_t), 128U);
    memRec[ALG_ANALYZE_NETWORK_MEMREC].space   = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_ANALYZE_NETWORK_MEMREC].attrs    = IALG_SCRATCH;//:TODO: Check this
    memRec[ALG_ANALYZE_NETWORK_MEMREC].alignment = 128;

    memRec[ALG_SCRATCH_DATA_BUFF_EXT_MEMREC].space       = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_SCRATCH_DATA_BUFF_EXT_MEMREC].attrs         = IALG_SCRATCH;
    memRec[ALG_SCRATCH_DATA_BUFF_EXT_MEMREC].alignment  = 128;

    /* memTab to allocate memory to backup context memory for pre-emption */
    if (TIDL_checkIfPreEmptionEnabled(createParams))
    {
      /* Making this memTab as PERSIST to avoid context memory DDR to DDR copy */
      memRec[ALG_SCRATCH_DATA_BUFF_EXT_MEMREC].attrs         = IALG_PERSIST;
      memRec[ALG_CONTEXT_MEM_MEMREC].size = 
        TIDL_getContextMemSize(createParams->targetPriority, perfInfoOut);
    }
    else{
      memRec[ALG_CONTEXT_MEM_MEMREC].size = TIDL_PREEMPT_CONTEXT_MEMSIZE_DUMMY;
    }
    memRec[ALG_CONTEXT_MEM_MEMREC].space       = TIDL_DDR_MEMREC_NON_CACHEABLE;
    memRec[ALG_CONTEXT_MEM_MEMREC].attrs       = IALG_PERSIST;
    memRec[ALG_CONTEXT_MEM_MEMREC].alignment   = 128;


    int32_t maxDdrOffset = 128;
    if(perfInfoOut != NULL)
    {
      sBufferInfo_t *pBufInfo ;
      /* Find the minimum of baseAddr for DDR write buffers */
      int32_t minDDRbaseMem = INT32_MAX, maxDDRbaseMem = 0;
      int32_t minDDRbaseMemWt = INT32_MAX, maxDDRbaseMemWt = 0;
      int32_t *pMinDDRbaseMem, *pMaxDDRBaseMem ;
      
      for(i=0; i<createParams->net->numLayers; i++)
      {
        for(j=0; j<(int32_t)BUFTYPE_TOTAL; j++)
        {
          if(j == WT_MAP){
            pBufInfo = &perfInfoOut->sdataFlowInfo[i].bufInfo[j][READ] ;
            pMinDDRbaseMem = &minDDRbaseMemWt ;
            pMaxDDRBaseMem = &maxDDRbaseMemWt ;
          }
          else{
            pBufInfo = &perfInfoOut->sdataFlowInfo[i].bufInfo[j][WRITE] ;
            pMinDDRbaseMem = &minDDRbaseMem ;
            pMaxDDRBaseMem = &maxDDRbaseMem ;
          }
          if(TIDL_checkDdrTransferParams(pBufInfo) == (int32_t)VAILD_DDR_BUFFER)
          {
            if(*pMinDDRbaseMem > TIDL_getBufInfoAddr(pBufInfo, 0))
            {
              *pMinDDRbaseMem = TIDL_getBufInfoAddr(pBufInfo, 0);
            }
            if(*pMaxDDRBaseMem < TIDL_getBufInfoAddr(pBufInfo, 1))
            {
              *pMaxDDRBaseMem = TIDL_getBufInfoAddr(pBufInfo, 1);
            }              
          }
        }
      }

      /* Following are possible cases of memory layout: */
      /*  case 1 (weights at the end): minFM.....................maxFM xx minWt....maxWt  */
      /*  case 2 (weights in begin)  : minWt....maxWt xx minFM.....................maxFM  */
      /*  case 3: (weights in middle): minFM........x minWt....maxWt x.............maxFM  */
      /* But GC makes sure below layout and also minFM to be zero */
      /*  (weights in end and no hole)  :minFM..................maxFM<> minWt....maxWt    */
      if((minDDRbaseMemWt < maxDDRbaseMem)){
        tidl_printf(0,"DDR request and layout from GC doesn't seem correct:\n");
        tidl_printf(0,"min(FM): %8d, max(FM): %8d, min(WT): %8d, max(WT): %8d\n",
        minDDRbaseMem, maxDDRbaseMem, minDDRbaseMemWt, maxDDRbaseMemWt);
        status = TIDL_E_INVALID_DDR_INFO_FROM_GC ;
      }
      else{
        //(minDDRbaseMem != 0) is not an error case and it is possible due to feature alignments
        tidl_printf(1,"min(FM): %8d, max(FM): %8d, min(WT): %8d, max(WT): %8d\n",
        minDDRbaseMem, maxDDRbaseMem, minDDRbaseMemWt, maxDDRbaseMemWt);
        maxDdrOffset = MAX(perfInfoOut->memorySizeRequirement[DDR], maxDDRbaseMemWt) ;
        if(1) //weights not used from GC request - make it 1 to save size
         maxDdrOffset = maxDDRbaseMem ;
      }
    }
    memRec[ALG_SCRATCH_DATA_BUFF_EXT_MEMREC].size = (uint32_t)(maxDdrOffset);

    /* memTab to allocate memory for net structure along with compiled information*/
    memRec[ALG_PERSIST_DDR_NET_MEMREC].size        = TIDL_getSizeNet(createParams) ;
    memRec[ALG_PERSIST_DDR_NET_MEMREC].space       = TIDL_DDR_MEMREC_CACHEABLE;
    memRec[ALG_PERSIST_DDR_NET_MEMREC].attrs       = IALG_PERSIST;
    memRec[ALG_PERSIST_DDR_NET_MEMREC].alignment   = 128;

    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY)
    {
      for( i = 0; i < MAX_NUM_MEMRECS; i++)
      {
        memRec[i].space = TIDL_DDR_MEMREC_CACHEABLE;
      }
    }
  }
  
  if (tidl_getTraceLogLevel() >= 2 )
  {
    TIDL_printMemorySizeStats(memRec, MAX_NUM_MEMRECS);
  }

  return (status);
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_init
@brief      Function to accept memory pointers from user and initialize algo
            Refer algInit function for details in XADIS (ialg.h file)
@param      handle   : Algorithm Instance handle
@param      memRec   : memory table populated by the Algorithm
@param      parent   : Parent function pointer
@param      params   : Input Parameters
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_init(IALG_Handle handle,
const IALG_MemRec memRec[],
IALG_Handle parent,
const IALG_Params * params)
{
  int32_t status = IALG_EOK;
  int32_t currAlgLayer = 0;
  int32_t paramMemTabOffset = 0;
  int32_t dataMemTabOffset = 0;
  sPerfSim_t * perfInfoOut;

  const TIDL_CreateParams * createParams =
  (const TIDL_CreateParams*)(const void*)params;
  int32_t i,j;
  int32_t intAlghandleMemSize;
  int32_t dmaContextSize;
  sDataFlowInfo_t * dataFlowInfo = NULL;
  int32_t msmcSramSize;
  int32_t l2SramSize;
  TIDL_Handle algHandle    =
  (TIDL_Handle)(void*)memRec[ALG_HANDLE_MEMREC].base;

  typedef struct{
    int32_t i_OD;
    sTIDL_AlgLayer_t *algLayer_OD ;
  }sODLayerInfo_t ;
  sODLayerInfo_t odLayerInfo[TIDL_OBJ_DET_MAX_HEADS];
  int32_t numODLayer = 0;


  algHandle->perfSimOutput = NULL ;

  status = TIDL_initDebugTraceParams(createParams->traceLogLevel, createParams->traceWriteLevel, createParams->TIDLVprintf, createParams->TIDLWriteBinToFile, createParams->TIDLReadBinFromFile, createParams->traceBaseName, createParams->tracePtr);
  if (status != IALG_EOK)
  {
    status = TIDL_E_INVALID_DEBUG_TRACE_PRM;
  }

  if (status == IALG_EOK)
  {
    algHandle->createParams   =
    (TIDL_CreateParams *) (void *)memRec[ALG_CREATE_PARAM_MEMREC].base;

    *algHandle->createParams  = *createParams;

    algHandle->TIDLLayersBuf =
    (sTIDL_LayerBuf_t *) (void *)memRec[ALG_LAYERS_MEMREC].base;

    algHandle->alglayerParams =
    (sTIDL_AlgLayer_t *) (void *)(get_int8_t_pointer((int8_t*)(void*)memRec[ALG_LAYERS_MEMREC].base,
                  ALIGN_SIZE((int32_t)sizeof(sTIDL_LayerBuf_t), 128)));

    algHandle->ivision = &TIDL_VISION_FXNS;

    algHandle->udmaDrvObj = createParams->udmaDrvObj;

    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
    {
      algHandle->createParams->quantRangeUpdateFactor = 0.0f;
      if ( algHandle->udmaDrvObj == NULL )
      {
        status = IALG_EFAIL;
      }
    }

  }

  if (status == IALG_EOK)
  {
    for(i = 0; i <  TIDL_MAX_DATA_BUFS; i++)
    {
      algHandle->dataBuf[i] =  NULL;
    }
    algHandle->numMemRecs    = (uint32_t)MAX_NUM_MEMRECS;
    (void)memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);
  }

  if (status == IALG_EOK)
  {
    /* analyze the network */
    perfInfoOut  = NULL;
    msmcSramSize = 128;
    l2SramSize = 128;

    if(algHandle->createParams->net->dataFlowInfo != 0)
    {
      perfInfoOut = TIDL_getCompilerBufPtr(algHandle->createParams->net, memRec );
      msmcSramSize = (perfInfoOut->simConfig.sizeL3MemKB - L3MEM_SCRATCH_BUF_SIZEKB) * 1024;
      l2SramSize   = (perfInfoOut->simConfig.sizeL2MemKB - L2MEM_SCRATCH_BUF_SIZEKB)* 1024;
    }

    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      perfInfoOut  = NULL;
    }

    algHandle->perfSimOutput = perfInfoOut;
  }


  if(status == IALG_EOK)
  {
    status = TIDL_AsymQuantizationCheck(algHandle);
  }
  
  if(status == IALG_EOK)
  {
    status = TIDL_OTFPadErrorCheck(algHandle);
  }
  
  /* Initialize newDataId of inData with dataId, so that this can be used later
      to find the free output buffer for Re-using
  */
  if (status == IALG_EOK)
  {
    if(createParams->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      for(i = 0; i <  createParams->net->numLayers; i++)
      {
        const sTIDL_Layer_t *TIDLLayerCur = &createParams->net->TIDLLayers[i];
        for(j = 0; j < TIDLLayerCur->numInBufs; j++)
        {
          TIDLLayersBuf.newInDataId[i][j] = TIDLLayerCur->inData[j];
        }
      }
    }

    if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
    {
      algHandle->createParams->net->dataFlowInfo = 0;
    }
    if (((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0) && (algHandle->createParams->net->dataFlowInfo == 0))
    {
      status = TIDL_E_DATAFLOW_INFO_NULL;
    }
  }



  if(status == IALG_EOK)
  {
    /* Setup System memories */
    algHandle->sysMems[TIDL_SYSMEM_L1_SCRATCH].base =
        (void *)  memRec[ALG_SCRATCH_L1_MEM_MEMREC].base;
    algHandle->sysMems[TIDL_SYSMEM_L1_SCRATCH].size =
        (int32_t ) memRec[ALG_SCRATCH_L1_MEM_MEMREC].size;

    algHandle->sysMems[TIDL_SYSMEM_L2_SCRATCH].base =
      (void *)  memRec[ALG_SCRATCH_L2_MEM_MEMREC].base;
    algHandle->sysMems[TIDL_SYSMEM_L2_SCRATCH].size =
        (int32_t )memRec[ALG_SCRATCH_L2_MEM_MEMREC].size;

    algHandle->sysMems[TIDL_SYSMEM_L3_SCRATCH].base =
        (void *)  memRec[ALG_SCRATCH_L3_MEM_MEMREC].base;
    algHandle->sysMems[TIDL_SYSMEM_L3_SCRATCH].size =
        (int32_t ) memRec[ALG_SCRATCH_L3_MEM_MEMREC].size;

    algHandle->sysMems[TIDL_SYSMEM_DDR_SCRATCH].base =
        (void *)  memRec[ALG_SCRATCH_DDR_MEM_MEMREC].base;
    algHandle->sysMems[TIDL_SYSMEM_DDR_SCRATCH].size =
        (int32_t)  memRec[ALG_SCRATCH_DDR_MEM_MEMREC].size;

    /* Reset all memories for the first time */
    TIDL_resetSysmem(algHandle->sysMems);
    intAlghandleMemSize = (int32_t)(ALIGN_SIZE((uint32_t)sizeof(TIDL_Obj), 128U));

    algHandle->sysScratchPtr.l3BasePtr = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                    (uint32_t)msmcSramSize,
                                    128U,
                                    TIDL_SYSMEM_L3_SCRATCH, (uint32_t)IALG_PERSIST);

    if ( algHandle->sysScratchPtr.l3BasePtr == NULL )
    {
      status = IALG_EFAIL;//:TODO: Add new error types for this
      tidl_printf(0, "Not able to allocate MSMC memory\n");
    }
    algHandle->intAlgHandle = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                    (uint32_t)intAlghandleMemSize,
                                    128U,
                                    TIDL_SYSMEM_L3_SCRATCH, (uint32_t)IALG_PERSIST);
    if ( algHandle->intAlgHandle == NULL )
    {
      status = IALG_EFAIL;//:TODO: Add new error types for this
      tidl_printf(0, "Not able to allocate intAlgHandle memory\n");
    }
  }

  if(status == IALG_EOK)
  {
    algHandle->sysScratchPtr.l2BasePtr = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                    (uint32_t)l2SramSize,
                                    128U,
                                    TIDL_SYSMEM_L2_SCRATCH, (uint32_t)IALG_PERSIST);
    if ( algHandle->sysScratchPtr.l2BasePtr == NULL )
    {
      status = IALG_EFAIL;//:TODO: Add new error types for this
      tidl_printf(0, "Not able to allocate L2 memory\n");
    }
  }

  if (status == IALG_EOK)
  {
    uint32_t privContextSize = TIDL_privGetContextSize();

    algHandle->privContext = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems,
      (uint32_t)privContextSize,
      128U,
      TIDL_SYSMEM_L3_SCRATCH, (uint32_t)IALG_PERSIST);
  
    if (algHandle->privContext == NULL)
    {
      status = IALG_EFAIL;
      tidl_printf(0, "Not able to allocate priv algo context memory\n");
    }
  }

  if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
  {
    if(status == IALG_EOK)
    {
      if (gTempUseMsmcStageForWt == 1)
      {
        algHandle->layerShare.wtMemBasePtr = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                          TIDL_WT_STAGING_MEM,
                                          128U,
                                          TIDL_SYSMEM_L3_SCRATCH, (uint32_t)IALG_PERSIST);
        algHandle->layerShare.currPtrOffset = 0;
        algHandle->layerShare.lastPtrOffset = 0;
        algHandle->layerShare.isWtDmaPending = 0;
        algHandle->layerShare.totStageMemAvail = (int32_t)TIDL_WT_STAGING_MEM;

        algHandle->weightStageSync.wtMemBasePtr = algHandle->layerShare.wtMemBasePtr;
        algHandle->weightStageSync.currPtrOffset= (uint32_t)algHandle->layerShare.currPtrOffset;
        algHandle->weightStageSync.lastPtrOffset= (uint32_t)algHandle->layerShare.lastPtrOffset;
        algHandle->weightStageSync.isWtDmaPending= (uint32_t)algHandle->layerShare.isWtDmaPending;
        algHandle->weightStageSync.totStageMemAvail= (uint32_t)algHandle->layerShare.totStageMemAvail;
        if ( algHandle->layerShare.wtMemBasePtr == NULL )
        {
          status = IALG_EFAIL;//:TODO: Add new error types for this
          tidl_printf(0, "Not able to allocate wt stage memory\n");
        }
      }
    }
    if(status == IALG_EOK)
    {
      dmaContextSize = DmaUtilsAutoInc3d_getContextSize((uint32_t)TIDL_DMA_CHANNEL_MAX);

      algHandle->dmaUtilsContext = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                      (uint32_t) dmaContextSize,
                                        128U,
                                        TIDL_SYSMEM_L3_SCRATCH, (uint32_t)IALG_PERSIST);

      if ( algHandle->dmaUtilsContext == NULL )
      {
        status = IALG_EFAIL;//:TODO: Add new error types for this
        tidl_printf(0, "Not able to allocate DMAUTILS context memory\n");
      }

    }

    if(status == IALG_EOK)
    {
      algHandle->zeroVector1k  = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                                                          (TIDL_1K_ZERO_VECTOR),
                                                                          128U,
                                                                          TIDL_SYSMEM_L2_SCRATCH,
                                                                          (uint32_t)IALG_PERSIST);

      if ( algHandle->zeroVector1k  == NULL )
      {
        tidl_printf(0, "Not able to allocate zero vector in L2  memory\n");
        status = IALG_EFAIL;//:TODO: Add new error types for this
      }
      algHandle->memcpyTr = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems ,
                                                                          (TIDL_MEMCPY_TR_MEM),
                                                                          128U,
                                                                          TIDL_SYSMEM_L2_SCRATCH,
                                                                          (uint32_t)IALG_PERSIST);

      if ( algHandle->zeroVector1k  == NULL )
      {
        tidl_printf(0, "Not able to allocate zero vector in L2  memory\n");
        status = IALG_EFAIL;//:TODO: Add new error types for this
      }
    }
  }

  if(status == IALG_EOK)
  {
  //:TODO: Remove this once inner product buffers are correclty given by perfsim
    algHandle->sysMems[TIDL_SYSMEM_L2_SCRATCH].base =
      (void *)  memRec[ALG_SCRATCH_L2_MEM_MEMREC].base;
    algHandle->sysMems[TIDL_SYSMEM_L2_SCRATCH].size =
        (int32_t )memRec[ALG_SCRATCH_L2_MEM_MEMREC].size - TIDL_1K_ZERO_VECTOR - TIDL_MEMCPY_TR_MEM;


    algHandle->sysScratchPtr.l1BasePtr   = (uint8_t *) memRec[ALG_SCRATCH_L1_MEM_MEMREC].base;
    algHandle->sysScratchPtr.ddrBasePtr = (uint8_t *) memRec[ALG_SCRATCH_DATA_BUFF_EXT_MEMREC].base;
  }

  if (status == IALG_EOK)
  {
    for(i = 0; i <  createParams->net->numLayers; i++)
    {
      tidl_printf(1,"Alg Init for Layer # - %4d out of %4d\n",i,createParams->net->numLayers - 1);

      if ( perfInfoOut != NULL )
      {
        dataFlowInfo = &perfInfoOut->sdataFlowInfo[i];
      }

      int32_t targetDevice = createParams->net->deviceName;
      int32_t numSubHandles = 1U;
      TIDL_forceTargetDeviceNonOTF(&targetDevice, createParams->net->TIDLLayers[i].layerType, -1);
      if(TIDL_isPadOTF(targetDevice))
      {
        if(TIDL_isLayerSpatialPooling(createParams, i))
        {
          if(dataFlowInfo->numSplit > 1)
          {
            numSubHandles = 3U;
          }
        }
      }

      if(createParams->net->TIDLLayers[i].layersGroupId ==
          createParams->currLayersGroupId)
      {
        sTIDL_AlgLayer_t *algLayer = get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer);
        algLayer->layerIdx = i;

        for (j = 0; j < createParams->net->TIDLLayers[i].numInBufs; j++)
        {
          int32_t inDataId        = createParams->net->TIDLLayers[i].inData[j];
          algLayer->inLayerIdx[j] = TIDL_getLayerNum(createParams->net, inDataId);
          algLayer->isInData[j]   = TIDL_isInDataBuff(createParams->net, inDataId, createParams->currLayersGroupId);
          algLayer->isInOutData[j]   = TIDL_isOutDataBuff(createParams->net, inDataId, createParams->currLayersGroupId);

        }
        for (j = 0; j < createParams->net->TIDLLayers[i].numOutBufs; j++)
        {
          int32_t outDataId        = createParams->net->TIDLLayers[i].outData.dataId;
          algLayer->isOutData[j]   = TIDL_isOutDataBuff(createParams->net, outDataId, createParams->currLayersGroupId);
        }

        algLayer->dataFlowInfo = dataFlowInfo;

        void ** outPtr =
        &algHandle->dataBuf[createParams->net->TIDLLayers[i].outData.dataId];

        if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == 0)
        {
          if ((algHandle->createParams->net->quantizationStyle == TIDL_QuantStyleNP2Fixed) ||
            (algHandle->createParams->net->quantizationStyle == TIDL_QuantStyleP2Dynamic))
          {
            if (algHandle->createParams->quantRangeUpdateFactor == 0.0f)
            {
              TIDL_UpdateScaleFactors(algHandle, i, 0, 0, 0);
            }
          }
        }

        /* Check if new GenericFlow is enabled for this layer */
        int32_t isNewGenericFlow = TIDL_isNewGenericFlowEnabled(createParams, i);
        if(((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0) && isNewGenericFlow && dataFlowInfo)
        {
          int32_t backupProcSize = dataFlowInfo->procSize;
          int32_t backupDmaFreq  = dataFlowInfo->dmaFreq;
          int32_t backupAccessor = dataFlowInfo->bufInfo[IN_FEAT_MAP][READ].accessor;
          int32_t backupBufWidth = dataFlowInfo->bufInfo[IN_FEAT_MAP][WRITE].activeBufWidth;
          int32_t backupBufSize  = dataFlowInfo->bufInfo[IN_FEAT_MAP][WRITE].bufSize;
          int32_t backupNci      = dataFlowInfo->Nci ;
          int32_t backupNumSplit = dataFlowInfo->numSplit;
          /* Flag to disable output MSMC staging for debugging */
          int32_t flagDisableMSMCstaging  = 0;
          int32_t numStHandles = TIDL_privGetNumHandles(dataFlowInfo);
          int32_t numGenericFlowHandles = TIDL_getNumGenericFlowHandles(&createParams->net->TIDLLayers[i]);
          int32_t outFeatWidth = 0, outFeatHeight = 0;
          int32_t inFeatWidth = 0, inFeatHeight = 0;

          /****************************************************************************************/
          /* For each layer number of Handles created are numStHandles*numGenericFlowHandles      */
          /* - numStHandles can be >1 for superTiling flow and it is one for other flow           */
          /* - numGenericFlowHandles can be > 1 for Concat layer and it is one for other layers   */
          /*                                                                                      */
          /* We need to populate below variables to send to TIDL_genericFlowInit function         */
          /* - numInTensors  : Total number of input tensors requires generic DMA data flow       */
          /* - inDataParams  : Data Params of input tensors required in generic DMA data flow     */
          /* - inPlaneSize   : DMA transfer size of each input tensor                             */
          /* - numOutTensors : Total number of output tensors requires generic DMA data flow      */
          /* - outDataParams : Data Params of input tensors required in generic DMA data flow     */
          /* - outPlaneSize  : DMA transfer size of each output tensor                            */
          /* - disableMSMCstaging : Indicates GenericFlow that MSMC staging is disabled           */
          /*                                                                                      */
          /* So,the below code will populate them for each Handle and creates GenericFlow Handles */
          /****************************************************************************************/
          for(int32_t st=0; st<numStHandles; st++)
          {
            TIDL_privGetOutProcSize(dataFlowInfo, st, &createParams->net->TIDLLayers[i], &outFeatWidth, &outFeatHeight, targetDevice);
            for (int32_t j = 0; j < numGenericFlowHandles; j++)
            {
              int32_t numInTensors;
              int32_t numOutTensors;
              int32_t inPlaneSize;
              int32_t outPlaneSize;
              int32_t jumpReduction = 0U;
              sTIDL_DataParams_t outDataParamsOrig;
              sTIDL_DataParams_t inDataParamsOrig;

              sTIDL_DataParams_t *outDataParams;
              sTIDL_DataParams_t *inDataParams[TIDL_MAX_IN_TENSORS];
              int32_t disableMSMCstaging = 0; // By default MSMCstaging is enabled
              int32_t disableMixedPrecision = 0; // By default Mixed precision in enabeld
              int32_t procElemSizeInBytes;
              int32_t outConversionFactor = 1;

              procElemSizeInBytes = TIDL_getProcessingElementSizeInBytes(&createParams->net->TIDLLayers[i]);

              status = TIDL_getNumInOutTensors(createParams, i, &numInTensors, &numOutTensors);
              if(status != IALG_EOK) /* break if numInTensors is > TIDL_MAX_IN_TENSORS */
              {
                break;
              }

              outDataParams = &createParams->net->TIDLLayers[i].outData;
              inDataParams[0] = &createParams->net->TIDLLayers[algLayer->inLayerIdx[j]].outData;

              for(int32_t k = 1; k < numInTensors; k++)
              {
                inDataParams[k] = &createParams->net->TIDLLayers[algLayer->inLayerIdx[k]].outData;

              }

              if ( createParams->net->TIDLLayers[i].layerType == TIDL_DataConvertLayer)
              {
                sTIDL_dataConvertParams_t * dataConvertParams =
                        &createParams->net->TIDLLayers[i].layerParams.dataConvertParams;
                /* Backup original data params */
                inDataParamsOrig  = *inDataParams[0];
                outDataParamsOrig = *outDataParams;
                disableMixedPrecision = 1;

                if ( dataConvertParams->layout == TIDL_LT_NHWC)
                {
                  if ( dataConvertParams->type == TIDL_DC_TYPE_OUTPUT)
                  {
                    outDataParams->pitch[TIDL_LINE_PITCH] = outDataParams->dimValues[TIDL_DIM_NUMCH];
                    outDataParams->pitch[TIDL_CHANNEL_PITCH] = outDataParams->pitch[TIDL_LINE_PITCH] *
                                                            outDataParams->dimValues[TIDL_DIM_WIDTH];
                    outDataParams->pitch[TIDL_ROI_PITCH] = outDataParams->pitch[TIDL_CHANNEL_PITCH] *
                                                            outDataParams->dimValues[TIDL_DIM_HEIGHT];
                  }
                  else if ( dataConvertParams->type == TIDL_DC_TYPE_INPUT)
                  {
                    inDataParams[0]->pitch[TIDL_LINE_PITCH] = inDataParams[0]->dimValues[TIDL_DIM_NUMCH];
                    inDataParams[0]->pitch[TIDL_CHANNEL_PITCH] = inDataParams[0]->pitch[TIDL_LINE_PITCH] *
                                                            inDataParams[0]->dimValues[TIDL_DIM_WIDTH];
                    inDataParams[0]->pitch[TIDL_ROI_PITCH] = inDataParams[0]->pitch[TIDL_CHANNEL_PITCH] *
                                                            inDataParams[0]->dimValues[TIDL_DIM_HEIGHT];

                    /* This is a hack to match match how generic flow uses these variables internally */
                    outDataParams->pitch[TIDL_CHANNEL_PITCH] = outDataParams->pitch[TIDL_LINE_PITCH];
                  }
                }
              }

              /* outConversionFactor is to handle mixed precision, but data convert layer this is handled
                 differently from mixed precision as the conversion happens as part of the processing itself
                 and not via DRU */
              if ( createParams->net->TIDLLayers[i].layerType != TIDL_DataConvertLayer)
              {
                if ( procElemSizeInBytes != TIDL_getDatElementSize(outDataParams->elementType) )
                {
                  outConversionFactor = 2;
                }
              }


              /* Some layers had known constraints for New genericFlow implementation, so update them here */
              dataFlowInfo->Nci = backupNci;
              dataFlowInfo->numSplit = backupNumSplit;
              dataFlowInfo->dmaFreq  = backupDmaFreq;
              dataFlowInfo->procSize  = backupProcSize;
              dataFlowInfo->bufInfo[IN_FEAT_MAP][READ].accessor  = backupAccessor;
              dataFlowInfo->bufInfo[IN_FEAT_MAP][WRITE].activeBufWidth  = backupBufWidth;
              dataFlowInfo->bufInfo[IN_FEAT_MAP][WRITE].bufSize = backupBufSize;
              inFeatHeight = inDataParams[0]->dimValues[TIDL_DIM_HEIGHT];
              TIDL_privGetInProcSize(dataFlowInfo, st, &createParams->net->TIDLLayers[i], &inFeatWidth, &inFeatHeight, targetDevice);
              TIDL_updateGenericFlowConstraints(createParams, i, inDataParams[0], dataFlowInfo, inFeatHeight, &flagDisableMSMCstaging);

              /* In case small feature map inPlaneSize will be minimum of procSize and activeBufWidth */
              inPlaneSize = MIN(dataFlowInfo->procSize, dataFlowInfo->bufInfo[IN_FEAT_MAP][WRITE].activeBufWidth);
              outPlaneSize = dataFlowInfo->bufInfo[OUT_FEAT_MAP][WRITE].bufWidth;

              /* Calculate inPlaneSize and outPlaneSize incase of LargeFeatureMap or superTiling */
              if((dataFlowInfo->numSplit>1) || (numStHandles != 1))
              {
                /* Use the procSize updated in TIDL_updateGenericFlowConstraints function for this */
                TIDL_getInOutPlaneSizes(createParams, i, dataFlowInfo, inDataParams[0], &inPlaneSize, outDataParams, &outPlaneSize, &jumpReduction, dataFlowInfo->procSize, st, targetDevice);
              }

              /* The outPlaneSize is in terms of final output's plane size, convert it to the out plane size corresponding
              to the kernel processing*/
              outPlaneSize = outPlaneSize * outConversionFactor;

              /* For some tiles, tileHeight can be zero, so not required to create Handle for that tile*/
              if((outFeatHeight > 0) || (numStHandles == 1))
              {
                algLayer->TIDL_GenericFlowHandle[st][j] =
                  (TIDL_GenericHandle*)get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, paramMemTabOffset);
                paramMemTabOffset += sizeof(TIDL_GenericHandle);

                /* Disable MSMC staging if user provided flagDisableMSMCstaging is 1 or output accessor type is not DMA */
                if (dataFlowInfo->bufInfo[OUT_FEAT_MAP][WRITE].accessor != ((int32_t)DMA)||(flagDisableMSMCstaging == 1))
                  disableMSMCstaging = 1;

                /* Disable MSMC staging if the staging buffer is allocated in DDR*/
                if ( dataFlowInfo->bufInfo[OUT_FEAT_MAP][READ].baseMem != NOT_VALID)
                {
                  if (dataFlowInfo->bufInfo[OUT_FEAT_MAP][READ].space == DDR)
                  {
                    disableMSMCstaging = 1;
                  }
                }

                /* Mixed precision with processing in 16 bit and output in 8 bit compulsory needs
                staging */
                if ( outConversionFactor > 1 )
                {
                  disableMSMCstaging = 0;
                }

                /* Generic DMA Init function to configure the DMA */
                status = TIDL_genericFlowInit(dataFlowInfo, (TIDL_GenericHandle*)algLayer->TIDL_GenericFlowHandle[st][j],
                 numInTensors, numOutTensors, inDataParams, outDataParams, procElemSizeInBytes, inPlaneSize, outPlaneSize, jumpReduction,
                 disableMSMCstaging, disableMixedPrecision);
                if(status != IALG_EOK)
                {
                  break;
                }
              }

              if ( createParams->net->TIDLLayers[i].layerType == TIDL_DataConvertLayer)
              {
                /* Restore original data params */
                *inDataParams[0] = inDataParamsOrig;
                *outDataParams   = outDataParamsOrig;
              }
            }
            if(status != IALG_EOK)
            {
              break;
            }

            /* For some tiles, tileHeight can be zero, so not required to create Kernel Handle */
            if((outFeatHeight > 0) || (numStHandles == 1))
            {
              for (int32_t j = 0; j < numGenericFlowHandles; j++)
              {
                /* Memory for KernelHandle is allocated next to GenericFlow handle so that
                   it is easy to copy them to L1D in a single DMA transfer in the Process call */
                algLayer->kernelHandle[st][j] =
                  get_uint8_t_pointer((uint8_t*)(void*)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].base, paramMemTabOffset);
                algLayer->kerHandleSize = TIDL_getKernelHandleSize(createParams, i, numSubHandles);
                paramMemTabOffset += algLayer->kerHandleSize;
              }
            }
          }
        }

        if(status != IALG_EOK)
        {
          break;
        }
         /* System memories are expected to be reset for every layer */
        TIDL_resetSysmem(algHandle->sysMems);

        if((createParams->net->TIDLLayers[i].layerType == TIDL_ConvolutionLayer))
        {
          algLayer->layerParams.convParams.dataFlowInfo = dataFlowInfo;

          status = TIDL_conv2DInit(algHandle,
                                   createParams,
                                   i,
                                   get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                   &paramMemTabOffset,
                                   &dataMemTabOffset,
                                   memRec,
                                   outPtr,
                                   algHandle->createParams->net->quantizationStyle,
                                   &TIDLLayersBuf);
        }
        else if ((createParams->net->TIDLLayers[i].layerType == TIDL_Deconv2DLayer))
        {
          algLayer->layerParams.convParams.dataFlowInfo = dataFlowInfo;

          status = TIDL_deconv2DInit(algHandle,
            createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            dataFlowInfo,
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr,
            algHandle->createParams->net->quantizationStyle, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_EltWiseLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_eltWiseInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ShuffleChannelLayer)
        {
          status = TIDL_shuffleChannelInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ResizeLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_resizeInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ArgMaxLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_argMaxInit(createParams, i,
                                  get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                  &paramMemTabOffset, &dataMemTabOffset,
                                  memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_PoolingLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_poolingInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_CustomLayer)
        {
          status = TIDL_customLayerInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_BatchNormLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_batchNormInit(createParams, i,
                                get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                &paramMemTabOffset, &dataMemTabOffset,
                                memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_BatchReshapeLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_batchReshapeInit(createParams, i,
                                get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                &paramMemTabOffset, &dataMemTabOffset,
                                memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_SoftMaxLayer)
        {
          status = TIDL_softmaxInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_InnerProductLayer)
        {
          status = TIDL_innerProductInit(createParams, i,
                                        get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                        &paramMemTabOffset, &dataMemTabOffset,
                                        memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ConcatLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_concatInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_FlattenLayer)
        {
          status = TIDL_flattenInit(createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_ConstDataLayer)
        {
          status = TIDL_constDataInit(createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr, &TIDLLayersBuf);
        }
        else if ((createParams->net->TIDLLayers[i].layerType == TIDL_DetectionOutputLayer) ||
          (createParams->net->TIDLLayers[i].layerType == TIDL_OdPostProcessingLayer))
        {
          if(TIDL_OBJ_DET_MAX_HEADS == numODLayer){
            status = TIDL_E_COMMON;
            tidl_printf(0,"OD Heads exceeds the max limit of %d\n", TIDL_OBJ_DET_MAX_HEADS);
          }else{          
            odLayerInfo[numODLayer].i_OD = i ;
            odLayerInfo[numODLayer].algLayer_OD =  get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer) ;
            algLayer->dataFlowInfo = dataFlowInfo;
            status = TIDL_detectOutInit(createParams, i,
              odLayerInfo[numODLayer].algLayer_OD,
              &paramMemTabOffset, &dataMemTabOffset,
              memRec, outPtr, &TIDLLayersBuf);
            numODLayer++;
          }
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_RoiPoolingLayer)
        {
          status = TIDL_roiPoolingInit(createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr, &TIDLLayersBuf);
        }
        else if ((createParams->net->TIDLLayers[i].layerType == TIDL_CropLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_DepthToSpaceLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_SliceLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_OdOutputReformatLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_SqueezeLayer) ||
                (createParams->net->TIDLLayers[i].layerType == TIDL_ReshapeLayer)
                )
        {
          status = TIDL_flattenInit(createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_PadLayer)
        {
          status = TIDL_padInit(createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr, &TIDLLayersBuf);
        }
        else if (createParams->net->TIDLLayers[i].layerType == TIDL_ColorConversionLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;
          status = TIDL_colorConversionInit(createParams, i,
            get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer),
            &paramMemTabOffset, &dataMemTabOffset,
            memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_DataConvertLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_dataConvertInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ReduceLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_reduceInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else if(createParams->net->TIDLLayers[i].layerType == TIDL_ScatterElementsLayer)
        {
          algLayer->dataFlowInfo = dataFlowInfo;

          status = TIDL_scatterElementsInit(createParams, i,
                                    get_AlgLayer_t_pointer(algHandle->alglayerParams,currAlgLayer),
                                    &paramMemTabOffset, &dataMemTabOffset,
                                    memRec, outPtr, &TIDLLayersBuf);
        }
        else
        {
            status = TIDL_E_UNSUPPORTED_LAYER;
        }

        if ( paramMemTabOffset > (int32_t)memRec[ALG_LAYERS_PARAMS_BUFF_MEMREC].size )
        {
          status = TIDL_E_COMMON;
          tidl_printf(0,"Memory used for  ALG_LAYERS_PARAMS_BUFF_MEMREC is greater than requested \n");
        }

        if ( dataMemTabOffset > (int32_t)memRec[ALG_SCRATCH_DATA_BUFF_MEMREC].size )
        {
          status = TIDL_E_COMMON;
          tidl_printf(0,"Memory used for  ALG_SCRATCH_DATA_BUFF_MEMREC is greater than requested \n");
        }

        algLayer = get_AlgLayer_t_pointer(algHandle->alglayerParams, currAlgLayer);
        algLayer->metaData.totalOps = 0;
        algLayer->metaData.actualOps = 0;
        for (int32_t k = 0; k < TIDL_PROFILE_MAX; k++)
        {
          algLayer->metaData.profilePoint[k] = 0;
        }
        currAlgLayer++;
      }

      if(status != IALG_EOK)
      {
        break;
      }
    }
  }

  if(status == IALG_EOK)
  {
    if(createParams->optimiseExtMem != TIDL_OptimiseExtMemL0)
    {
      for(i = 0; i <  createParams->net->numLayers; i++)
      {
        const sTIDL_Layer_t *TIDLLayerCur = &createParams->net->TIDLLayers[i];
        for(j = 0; j < TIDLLayerCur->numInBufs; j++)
        {
          algHandle->TIDLLayersBuf->newInDataId[i][j] = TIDLLayersBuf.newInDataId[i][j];
        }
        algHandle->TIDLLayersBuf->newOutDataId[i][0] = TIDLLayersBuf.newOutDataId[i][0];
      }
    }
    algHandle->procCallCounter = 0;

    {
      int32_t ptrOffset = 0;
      algHandle->activationHistPtr = NULL;
      algHandle->activationRangePtr = NULL;

      if((createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
      {
        if (( createParams->net->calibrationOption & TIDL_CalibOptionActivationRange ) ==
                  TIDL_CalibOptionActivationRange)
        {
          int32_t histogramSize = (createParams->net->numLayers *
                                   TIDL_NUM_ACTIVATION_HISTOGRAM_BINS *
                                   sizeof(int32_t));

          algHandle->activationHistPtr = (int32_t *)get_uint8_t_pointer((uint8_t *)memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base, ptrOffset);
          memset(algHandle->activationHistPtr, 0, histogramSize);
          ptrOffset += ALIGN_SIZE(histogramSize, 128);
          if ( createParams->net->calibrationParams.activationRangeMethod ==
            TIDL_ActivationRangeMethodGlobalHistogram )
          {
            int32_t layerIdx;
            int32_t activationRangePtrSize = (createParams->net->numLayers *
                                     2 * sizeof(float32_tidl));
            algHandle->activationRangePtr = (float32_tidl *) get_uint8_t_pointer((uint8_t *)memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base, ptrOffset);
            ptrOffset += ALIGN_SIZE(activationRangePtrSize, 128);
            for ( layerIdx = 0; layerIdx < createParams->net->numLayers; layerIdx++)
            {
              /* Copy the activation range during init these will come from the previous
              run of TIDL. Multiply it by a factor to account for any variation across
              iteration */
              algHandle->activationRangePtr[layerIdx * 2] =
                createParams->net->TIDLLayers[layerIdx].outData.minTensorValue;
              algHandle->activationRangePtr[layerIdx * 2 + 1] =
                createParams->net->TIDLLayers[layerIdx].outData.maxTensorValue;

            }
          }
        }
      }

      algHandle->refScratchBuf = (uint8_t *)get_uint8_t_pointer((uint8_t *)memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base,
                                                              ptrOffset);
      algHandle->refScratchBufSize = memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size - ptrOffset;
    }
  }

  if(status == IALG_EOK)
  {
    if(algHandle->perfSimOutput)
    {
     sPerfSimConfig_t *pSimConfig = &algHandle->perfSimOutput->simConfig;
     algHandle->ddrBytesPerCPUCycle =  pSimConfig->numEMIFPorts * pSimConfig->freqDDR * 
     (pSimConfig->busWidthDDR/8)* (pSimConfig->ddrEfficiency /pSimConfig->freqMHz) ;
    }
    
    algHandle->isPreEmptionEnable = TIDL_checkIfPreEmptionEnabled(createParams);
    algHandle->preEmptContextInfo.contextMemPtr = (uint8_t*)memRec[ALG_CONTEXT_MEM_MEMREC].base;
    algHandle->preEmptContextInfo.contextMemSize = memRec[ALG_CONTEXT_MEM_MEMREC].size;
    algHandle->preEmptContextInfo.earlyPreEmpt = 0;
    status = TIDL_addPriorityObject(algHandle,&memRec[ALG_CONTEXT_MEM_MEMREC], 
      algHandle->createParams->targetPriority);
    algHandle->preEmptContextInfo.contextMemPtr = (uint8_t*) TIDL_getContextMemAddr(algHandle);
    if (algHandle->isPreEmptionEnable)
    {
      /* Allocate memory for preemption handle */
      algHandle->preEmptHandle = (uint8_t *)TIDL_getMemoryChunkFromSysmem(algHandle->sysMems,
        (uint32_t)TIDL_getHandleSizeForPreemption(algHandle->createParams->net->numLayers),
        128U,
        TIDL_SYSMEM_L3_SCRATCH, (uint32_t)IALG_PERSIST);

      if (algHandle->preEmptHandle == NULL)
      {
        status = IALG_EFAIL;
        tidl_printf(0, "Not able to allocate preEmption Handle\n");
      }

      /* Initialize preemption handle */
      if(status == IALG_EOK)
      {
        algHandle->preemptPerfHW = 1;
        /* Avoided initializing preEmptHandle in L3, instead initializing it in the contextMemPtr (DDR)
           and copy it to preEmptHandle in L3 in the activate function
        */
        TIDL_initializeHandleForPreemption(algHandle->preEmptContextInfo.contextMemPtr, algHandle->perfSimOutput,
        algHandle->createParams->net->numLayers, algHandle->createParams->maxPreEmptDelay, 
        algHandle->sysScratchPtr.l2BasePtr, algHandle->ddrBytesPerCPUCycle,
        algHandle->perfSimOutput->simConfig.freqMHz);
        /* To copy this contextMemPtr to preEmptHandle in the activate function */
        algHandle->preEmptContextInfo.contextBufInfo[0].src = (uint8_t *) algHandle->preEmptHandle;
        algHandle->preEmptContextInfo.contextBufInfo[0].dst = (uint8_t *) algHandle->preEmptContextInfo.contextMemPtr;
        algHandle->preEmptContextInfo.contextBufInfo[0].size = TIDL_getHandleSizeForPreemption(algHandle->createParams->net->numLayers);
        algHandle->preEmptContextInfo.earlyPreEmpt = 1;
        algHandle->preEmptContextInfo.numContextBufs = 1;
      }
      tidl_printf(1, "TIDL_initializeHandleForPreemption is completed \n");
    }
  }

  if(status == IALG_EOK)
  {
    TIDL_MoveNetToPrivateMemory(algHandle, memRec);   
    //Need to do init again specifically for OD as the parameters are assigned quite a lot
    while(numODLayer){
      numODLayer--;
      TIDL_odFindValidLocAndScoreKernelInit(algHandle->createParams,
        odLayerInfo[numODLayer].algLayer_OD, 
        &algHandle->createParams->net->TIDLLayers[odLayerInfo[numODLayer].i_OD],0,0,0);
    }

    /*-----------------------------------------------------------------------*/
    /* State to indicate that internal context of algorithm is not active    */
    /*-----------------------------------------------------------------------*/
    algHandle->algState = (uint8_t)ALG_NOT_ACTIVE;
  }

  TIDL_enableL1DandL2CacheWb();
  
  return (status);
}
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_control
@brief      Function to accept any run time updates with recreation of object
            Refer algControl function for details in ivision.h file
@param      handle   : Algorithm Instance handle
@param      cmd      : Command to be processed
@param      inParams : Input Parameters
@param      outParams: Output Parameters
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_control(IVISION_Handle Handle,
IALG_Cmd cmd,
const IALG_Params *inParams,
IALG_Params *outParams)
{
  int32_t status = IALG_EOK;

  return (status);
}

//#define INTERNAL_PROFILING
#ifdef INTERNAL_PROFILING
typedef struct
{
  char   fmt[20];
  char   fmtVal[20];
  char   string[64];
  void*  pValue ;
} sTIDLProfilePrintInfo_t ;

static TIDL_LayerMetaData gLayerMetaData = {0};

static sTIDLProfilePrintInfo_t gProfilePrintInfo[] =
{
  {"%6s,"   , "%6d,"     , "Layer"                 ,  NULL},
  {"%15s,"  , "%15llu,"  , "Layer Cycles"          ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER]},
  {"%15s,"  , "%15llu,"  , "kernelOnlyCycles"      ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_KERNEL_ONLY]},
  {"%15s,"  , "%15llu,"  , "coreLoopCycles"        ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_CORE_LOOP]},
  {"%15s,"  , "%15llu,"  , "LayerSetupCycles"      ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER_SETUP]},
  {"%15s,"  , "%15llu,"  , "dmaPipeupCycles"       ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_DMA_PIPEUP]},
  {"%18s,"  , "%18llu,"  , "dmaPipeDownCycles"     ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_DMA_PIPEDOWN]},
  {"%15s,"  , "%15llu,"  , "PrefetchCycles"        ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_PREFETCH]},
  {"%18s,"  , "%18llu,"  , "copyKerCoeffCycles"    ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_KERNEL_COPY]},
  {"%15s,"  , "%15llu,"  , "LayerDeinitCycles"     ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER_DEINIT]},
  {"%15s,"  , "%15llu,"  , "LastBlockCycles"       ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAST_BLOCK_CYCLES]},
  {"%15s,"  , "%15llu,"  , "paddingTrigger"        ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER_PADDING_TRIGGER]},
  {"%15s,"  , "%15llu,"  , "paddingWait"           ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER_PADDING_WAIT]},
  {"%15s,"  , "%15llu,"  , "LayerWithoutPad"       ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER_WITHOUT_PADDING]},
  {"%15s,"  , "%15llu,"  , "LayerHandleCopy"       ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER_SETUP_HANDLE_COPY]},
  {"%15s,"  , "%15llu,"  , "BackupCycles"          ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_BACKUP]},
  {"%15s,"  , "%15llu,"  , "RestoreCycles"         ,  &gLayerMetaData.profilePoint[TIDL_PROFILE_RESTORE]}
};

void TIDL_printProfileData(
  TIDL_Handle intAlgHandle, 
  uint64_t tStartNetwork, uint64_t tEndNetwork, 
  int32_t i)
{
  int32_t numProfilePoints, j;
  uint64_t sumOfLayerCycles = 0;
  sTIDL_AlgLayer_t * algLayer;
  sTIDL_Layer_t *TIDLLayer = &intAlgHandle->createParams->net->TIDLLayers[i];
  algLayer = &intAlgHandle->alglayerParams[i];

  if ( i ==  0)
  {
    uint64_t netWorkCycles;
    netWorkCycles = (uint64_t)(tEndNetwork - tStartNetwork);
    numProfilePoints = (int32_t)(sizeof(gProfilePrintInfo)/sizeof(sTIDLProfilePrintInfo_t));
    tidl_printf(0,"\n");
    tidl_printf(0,"Network Cycles %llu \n", netWorkCycles);

    for ( j= 0; j < numProfilePoints; j++)
    {
      tidl_printf(0,gProfilePrintInfo[j].fmt, gProfilePrintInfo[j].string);
    }
    tidl_printf(0,"\n");
  }

  if (TIDLLayer->layerType != TIDL_DataLayer)
  {
    gLayerMetaData = algLayer->metaData;
    sumOfLayerCycles += gLayerMetaData.profilePoint[TIDL_PROFILE_LAYER];
    gProfilePrintInfo[0].pValue = &i;

    for ( j= 0; j < numProfilePoints; j++)
    {
      tidl_printf(0,gProfilePrintInfo[j].fmtVal, *((uint32_t *)gProfilePrintInfo[j].pValue));
    }
    tidl_printf(0,"\n");
  }
  tidl_printf(0," Sum of Layer Cycles %llu \n", sumOfLayerCycles);
}

#endif
/**
 * @brief This is the layer processing function and should be called
 *          for each layer process.
 *
 * @param intAlgHandle  : Algorithm Instance handle
 * @param algLayer : This structure contains the layer specific parameters
 * @param TIDLLayer : This structure contains the common layer parameters
 *          in TIDL
 * @param inPtrs : Input Buffer Pointers
 * @param outPtrs : Output Buffer Pointers descriptor
 * @param sysMems : This structure has the system memory handles in TIDL
 * @param i : Layer number to be processed
 * @return int32_t : return value
 */
int32_t TIDL_layerProcess(
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * inPtrs[],
  void                 * outPtrs[],
  sTIDL_sysMemHandle_t * sysMems,
  int32_t i)
{
  int32_t status = IALG_EOK;

  if(TIDLLayer->layerType == TIDL_ConvolutionLayer)
  {
    status = TIDL_conv2dProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if (TIDLLayer->layerType == TIDL_Deconv2DLayer)
  {
    status = TIDL_deconv2dProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_EltWiseLayer)
  {
    status = TIDL_eltWiseProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ShuffleChannelLayer)
  {
    status = TIDL_shuffleChannelProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ResizeLayer)
  {
    status = TIDL_resizeProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ArgMaxLayer)
  {
    status = TIDL_argmaxProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_BatchNormLayer)
  {
    status = TIDL_batchNormProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_PoolingLayer)
  {
    status = TIDL_poolingProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_CustomLayer)
  {
    status = TIDL_customProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_InnerProductLayer)
  {
    status = TIDL_innerProductProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_SoftMaxLayer)
  {
    status = TIDL_softmaxProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ConcatLayer)
  {
    status = TIDL_concatProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if (TIDLLayer->layerType == TIDL_FlattenLayer)
  {
    status = TIDL_flattenProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if ((TIDLLayer->layerType == TIDL_DetectionOutputLayer) || (TIDLLayer->layerType == TIDL_OdPostProcessingLayer))
  {
    status = TIDL_detectionOutputProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if (TIDLLayer->layerType == TIDL_RoiPoolingLayer)
  {
    status = TIDL_roiPoolingProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_SliceLayer)
  {
    status = TIDL_sliceProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_CropLayer)
  {
    status = TIDL_cropProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_DepthToSpaceLayer)
  {
    status = TIDL_depthToSpaceProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_BatchReshapeLayer)
  {
    status = TIDL_batchReshapeProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_PadLayer)
  {
    status = TIDL_padProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ColorConversionLayer)
  {
    status = TIDL_colorConversionProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_OdOutputReformatLayer)
  {
    status = TIDL_odOutputReformatProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_DataConvertLayer)
  {
    status = TIDL_dataConvertProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ReduceLayer)
  {
    status = TIDL_reduceProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ScatterElementsLayer)
  {
    status = TIDL_scatterElementsProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_SqueezeLayer)
  {
    // copy input data to output buffer. NC can allocate output and input buffer same
    status = TIDL_squeezeProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems);
  }
  else if(TIDLLayer->layerType == TIDL_ReshapeLayer)
  {
    /*Copy the data for reference flow if perfsimInfo not available*/
    if(intAlgHandle->perfSimOutput == NULL)
    {
      int32_t cpSize = TIDLLayer->outData.dimValues[0]*TIDLLayer->outData.pitch[TIDL_ROI_PITCH];
      int32_t outElementSize     = TIDL_getDatElementSize(TIDLLayer->outData.elementType);

      memcpy((void*)((size_t)outPtrs[0]), (void*)((size_t)inPtrs[0]), outElementSize*cpSize);
    }
  }
  else if(TIDLLayer->layerType == TIDL_ConstDataLayer)
  {

  }
  else
  {
    status = TIDL_E_UNSUPPORTED_LAYER;
  }

  return (status);
}


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_process
@brief      This is the main processing function and should be called
            for each frame.
            Refer process function for details in ivision.h file

@param      handle : Algorithm Instance handle
@param      inBufs : Input Buffer Pointers descriptor
@param      outBufs: Output Buffer Pointers descriptor
@param      inArgs : Input Arguments
@param      outArgs: Output Arguments
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/

int32_t gCurrLayerNumber;
int32_t gLayerNumber = -1;
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7
Pointer parameter inBufs and outBufs are not used to modify the addressed
object but is not declared as a pointer to const
Deviation is allowed because this function is of type IVISION_Fxns :
algProcess in order to be ASSIGNED IVISION_Fxns */
int32_t TIDL_process(IVISION_Handle Handle,
IVISION_InBufs *inBufs,
IVISION_OutBufs *outBufs,
IVISION_InArgs *inArgs,
IVISION_OutArgs *outArgs)
{
  /** Init phase performs a lot of writes to DDR which can get cached in L1/L2D 
   * so need to writeback/invalidate cache to ensure correct data is fetched in case DMA is done e.g. DMA transfer for handle from DDR to MSMC can result in 
   * corrupt data if this wb/inv is not done 
  */
  TIDL_enableL1DandL2CacheWb();
  /*RESET_MISRA("16.7")  -> Reset rule 16.7  */
  TIDL_Handle algHandle = (TIDL_Handle)(void*)(Handle);
  TIDL_Handle intAlgHandle = NULL;
  int32_t twStatus, status            = IALG_EOK;
  TIDL_InArgs * tidlInArgs = (TIDL_InArgs*)(void*)inArgs;
  TIDL_outArgs * tidlOutArgs = (TIDL_outArgs*)(void*)outArgs;

  int32_t currAlgLayer = 0;
  int32_t i;
  sTIDL_sysMemHandle_t *sysMems;

  uint64_t tStart, tEnd;
  uint64_t tStartNetwork, tEndNetwork;
  uint64_t tStart1, tEnd1;
  uint64_t tStartLayer, tEndLayer;
  uint8_t trMem[64]; //:TODO: Add a macro in DMA utils to return size of single TR
  int32_t oldIntState = 0;
  int32_t lockState = UNLOCKED;

  TIDL_getTscTime(&tStartNetwork);

  status = TIDL_initDebugTraceParams(algHandle->createParams->traceLogLevel,
  algHandle->createParams->traceWriteLevel,
  algHandle->createParams->TIDLVprintf,
  algHandle->createParams->TIDLWriteBinToFile,
  algHandle->createParams->TIDLReadBinFromFile,
  algHandle->createParams->traceBaseName,
  algHandle->createParams->tracePtr);

  if (status != IALG_EOK)
  {
    status = TIDL_E_INVALID_DEBUG_TRACE_PRM;
  }

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  if (status == IALG_EOK)
  {
    /* Disable interrupts here */
    if (algHandle->isPreEmptionEnable)
    {
      tidl_printf(1, "TIDL_process is started with handle : %x \n", algHandle);
      oldIntState = TIDL_lockForPreemption(algHandle, algHandle->createParams, &lockState);
    }
    else
    {
      TIDL_switchHandles((IALG_Handle)(void*)Handle);
    }

    intAlgHandle = (TIDL_Handle)(void *)algHandle->intAlgHandle;
    intAlgHandle->isPadDmaPending = 0;
    sysMems = intAlgHandle->sysMems;

    /*Scale factors should never be updated for TIDL_QuantStyleAsymNP2_TFL*/
    if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == 0)
    {
      if ((intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleNP2Fixed) ||
        (intAlgHandle->createParams->net->quantizationStyle == TIDL_QuantStyleP2Dynamic))
      {
        for (i = 0; i < intAlgHandle->createParams->net->numLayers; i++)
        {
          if ((intAlgHandle->createParams->quantRangeUpdateFactor != 0.0f) &&
              (intAlgHandle->createParams->net->TIDLLayers[i].layersGroupId ==
               intAlgHandle->createParams->currLayersGroupId))
          {
            TIDL_UpdateScaleFactors(intAlgHandle, i, 0, 0, 0);
          }
        }
      }
    }

    for (i = 0; i < (int32_t)inBufs->numBufs; i++)
    {
      sTIDL_DataParams_t *inDataParams;
      int32_t layeType = TIDL_getLayerTypeForOutDataID(intAlgHandle->createParams->net,inBufs->bufDesc[i]->bufferId);
      if (layeType != TIDL_DataLayer)
      {
        inDataParams = TIDL_getDataParams(intAlgHandle->createParams->net,inBufs->bufDesc[i]->bufferId);
        inDataParams->tensorScale = tidlInArgs->scale[i];
      }
    }

    TIDL_privAlgoHandlInit(intAlgHandle, intAlgHandle->privContext);
    TIDL_privGetLayerToProcess(intAlgHandle, intAlgHandle->privContext, &i, &currAlgLayer);
    if (intAlgHandle->isPreEmptionEnable)
    {
      status = TIDL_updateContextMemPtrsForPreemption(&intAlgHandle->preEmptContextInfo, intAlgHandle->privContext,
      intAlgHandle->preEmptHandle, intAlgHandle->perfSimOutput, intAlgHandle->sysScratchPtr.l2BasePtr,
      intAlgHandle->sysScratchPtr.l3BasePtr, 0, intAlgHandle->createParams->net->numLayers);
      TIDL_unlockForPreemption(oldIntState, intAlgHandle->createParams, &lockState);
    }

    while(i != -1)
    {
      /* Disable interrupts here */
      if (intAlgHandle->isPreEmptionEnable)
      {
        oldIntState = TIDL_lockForPreemption(algHandle, intAlgHandle->createParams, &lockState);
      }

      /*  Critical section starts here */
      sTIDL_Layer_t *TIDLLayer = &intAlgHandle->createParams->net->TIDLLayers[i];
      int32_t targetDevice = intAlgHandle->createParams->net->deviceName;
      TIDL_forceTargetDeviceNonOTF(&targetDevice, TIDLLayer->layerType, -1);
      if(TIDLLayer->layersGroupId ==  intAlgHandle->createParams->currLayersGroupId &&
          TIDLLayer->layerType != TIDL_ConstDataLayer)
      {
        void * inPtrs[TIDL_NUM_IN_BUFS] = {0};
        void * outPtrs[TIDL_NUM_OUT_BUFS] = {0};
        sTIDL_AlgLayer_t *algLayer = get_AlgLayer_t_pointer(intAlgHandle->alglayerParams,currAlgLayer);
        intAlgHandle->currAlgLayer = currAlgLayer;
        tidl_printf(1,"Starting Layer # - %4d\n",i);

        intAlgHandle->alglayerParams[currAlgLayer].metaData.layerExecId = algLayer->layerIdx;

        TIDL_getTscTime(&tStart);
        status = TIDL_getLayerInPtrs(inBufs, outBufs, intAlgHandle, algLayer, TIDLLayer, inPtrs, i);

        if(status == IALG_EOK)
        {
          status = TIDL_getLayerOutPtrs(outBufs, intAlgHandle, algLayer, TIDLLayer, outPtrs, i);
        }

        if(status == IALG_EOK)
        {
          if((intAlgHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == 0)
          {
            status = TIDL_syncWeightStagingTransfer(intAlgHandle, i, currAlgLayer, targetDevice);
          }
        }

        if(status == IALG_EOK)
        {
          TIDL_getTscTime(&tStart1);

          TIDL_syncPadTransfer(intAlgHandle, trMem);

          TIDL_getTscTime(&tEnd1);
          TIDL_updateprofileData(intAlgHandle->alglayerParams[currAlgLayer].metaData.profilePoint, TIDL_PROFILE_LAYER_PADDING_WAIT,  tStart1, tEnd1);
          
          tidl_printf(1, "Processing Layer # - %4d\n", i);
          TIDL_getTscTime(&tStartLayer);
          gLayerNumber = i;
          gCurrLayerNumber = i;
          if(TIDL_privGetCurrProcType(intAlgHandle, i))
          {
            algLayer->procType = 0;
            status = TIDL_layerProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems, i);
            if(intAlgHandle->createParams->net->quantizationStyle != TIDL_QuantStyleAsymNP2_TFL)
            {
              if((status == IALG_EOK) && (TIDL_privGetCurrProcType(intAlgHandle, i)))
              {
                status = TIDL_updateAllLayersTensorStats(intAlgHandle, TIDLLayer, outPtrs, i);
              }
            }

            twStatus = tidl_writeTraceDataBuf((int8_t *)outPtrs[0], intAlgHandle->createParams->net, TIDLLayer->outData.dataId,
                        (int8_t *)intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base,
                        intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size, 0, TIDLLayer->outData.dimValues[TIDL_DIM_HEIGHT],
                        TIDLLayer->outData.pitch[TIDL_CHANNEL_PITCH]);
            if(twStatus != IALG_EOK)
            {
              tidl_printf(0,"Trace write failed\n");
            }
            tidl_writeTraceParamBuf(intAlgHandle->createParams->net,
                                    algLayer,
                                    TIDLLayer,
                                    TIDLLayer->outData.dataId,
                                    (int8_t *)intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].base,
                                    intAlgHandle->memRec[ALG_REF_OUTPUT_BUFF_MEMREC].size);
          }
          else
          {
            status = TIDL_privAlgoLayerProcess(intAlgHandle, algLayer, TIDLLayer, inPtrs, outPtrs, sysMems, i, intAlgHandle->privContext, targetDevice);
          }
          TIDL_getTscTime(&tEndLayer);
          TIDL_updateprofileData(intAlgHandle->alglayerParams[currAlgLayer].metaData.profilePoint, TIDL_PROFILE_LAYER_WITHOUT_PADDING,  tStartLayer, tEndLayer);
          
          /** Cache wb/inv after layer processing is required for the following scenarios:
           * (1) If layer processing writes output to DDR, L1D and L2 wb/inv
           * (2) If layer processing writes output to MSMC, L1D wb/inv
           * So both L1D and L2 wb/inv is required after layer processing
           * 
           * This wb/inv is also needed to be done before padding
           * Padding can (1) Row padding - done mostly by DMA but by CPU as well in some cases (2) Col padding - Done by CPU
           * (1) In case of DMA for row padding : It is necessary that relevant cached data at this stage
           * is written back (cannot just invalidate cache, else relevant cached data can be lost) and cache is invalidated before DMA starts - reason being 
           * Any Cache wb after DMA would write back all the data present in the cache line which can overwrite the padded data written by DMA    
           * 
           * Even if DMA padding is not done, this write back is anyways needed for next layer, so no harm in doing at this point
          */
          TIDL_enableL1DCacheWb();
        }

        if((status == IALG_EOK) && (TIDL_privGetCurrProcType(intAlgHandle, i)))
        {
          TIDL_getTscTime(&tStart1);
          status = TIDL_layerPadding(intAlgHandle, TIDLLayer, outPtrs, trMem, i);
          TIDL_getTscTime(&tEnd1);
          TIDL_updateprofileData(intAlgHandle->alglayerParams[currAlgLayer].metaData.profilePoint, TIDL_PROFILE_LAYER_PADDING_TRIGGER,  tStart1, tEnd1);
        }

        TIDL_getTscTime(&tEnd);
        TIDL_updateprofileData(intAlgHandle->alglayerParams[currAlgLayer].metaData.profilePoint, TIDL_PROFILE_LAYER,  tStart, tEnd);
        tidl_printf(1, "End of Layer # - %4d with outPtrs[0] = %p\n", i, (int8_t*)outPtrs[0]);
        if (intAlgHandle->isPreEmptionEnable)
        {
          TIDL_updateLayerCyclesForPreemption((void*)intAlgHandle->preEmptHandle, intAlgHandle->preemptPerfHW, (tEnd-tStart), i, algLayer->procType,
          intAlgHandle->perfSimOutput->simConfig.freqMHz);
        }
      }
      if (status != IALG_EOK)
      {
      // break;
      }
      TIDL_privGetLayerToProcess(intAlgHandle, intAlgHandle->privContext, &i, &currAlgLayer);
      /* critical section end here */

      if (intAlgHandle->isPreEmptionEnable)
      {
        if (TIDL_isThisLayerOptimalForPreemption(intAlgHandle->preEmptHandle, i))
        {
          /* Wait for layer padding DMA before restoring the interrupts */
          TIDL_syncPadTransfer(intAlgHandle, trMem);
          status = TIDL_updateContextMemPtrsForPreemption(&intAlgHandle->preEmptContextInfo, intAlgHandle->privContext,
          intAlgHandle->preEmptHandle, intAlgHandle->perfSimOutput, intAlgHandle->sysScratchPtr.l2BasePtr,
          intAlgHandle->sysScratchPtr.l3BasePtr, i, intAlgHandle->createParams->net->numLayers);

          TIDL_unlockForPreemption(oldIntState, intAlgHandle->createParams, &lockState);
        }
      }
    }
  }

  /* Disable interrupts here */
  if (intAlgHandle->isPreEmptionEnable)
  {
    oldIntState = TIDL_lockForPreemption(algHandle, intAlgHandle->createParams, &lockState);
    /* Recalculate pre-emption layer list using HW performance */
    TIDL_reCalculateListForPreemption((void*)intAlgHandle->preEmptHandle,
        &intAlgHandle->preemptPerfHW,	
        intAlgHandle->createParams->net->numLayers, 
        intAlgHandle->createParams->maxPreEmptDelay, 
        intAlgHandle->sysScratchPtr.l2BasePtr,
        intAlgHandle->ddrBytesPerCPUCycle,
        intAlgHandle->perfSimOutput->simConfig.freqMHz);
  }
  if(status == IALG_EOK)
  {
    if(intAlgHandle->procCallCounter < 256U)
    {
      intAlgHandle->procCallCounter++;
    }

    for (i = 0; i < (int32_t)outBufs->numBufs; i++)
    {
      sTIDL_DataParams_t *dataParams;
      dataParams = TIDL_getDataParams(intAlgHandle->createParams->net,outBufs->bufDesc[i]->bufferId);
      tidlOutArgs->scale[i] = dataParams->tensorScale;
    }
    tidlOutArgs->numOutBufs = (int32_t)outBufs->numBufs;
    tidlOutArgs->numLayers = intAlgHandle->createParams->net->numLayers;
    tidlOutArgs->privArgs  = (void*) intAlgHandle->createParams->net ;
  }

  TIDL_getTscTime(&tEndNetwork);

  if((tidlInArgs->enableLayerPerfTraces == 1) && (NULL != intAlgHandle))
  {
    sTIDL_AlgLayer_t * algLayer;
    
    currAlgLayer = 0;
    for(i = 0; i < intAlgHandle->createParams->net->numLayers; i++)
    {
      if(intAlgHandle->createParams->net->TIDLLayers[i].layersGroupId == intAlgHandle->createParams->currLayersGroupId)
      {
        algLayer = &intAlgHandle->alglayerParams[currAlgLayer];
        #ifndef INTERNAL_PROFILING
          tidlOutArgs->metaDataLayer[i] = algLayer->metaData;
        #else
          TIDL_printProfileData(intAlgHandle, tStartNetwork, tEndNetwork, i);
        #endif
        for(int32_t k = 0; k < TIDL_PROFILE_MAX; k++)
        {
          algLayer->metaData.profilePoint[k] = 0;
        }
        
        currAlgLayer++;
      }
      #ifndef INTERNAL_PROFILING
      else
      {
        tidlOutArgs->metaDataLayer[i].layerExecId = -1;
      }
      #endif
    }
  }

  /* Set earlyPreEmpt to 0 indicate that no pre-emption from TIDL Process function */
  if (intAlgHandle->isPreEmptionEnable)
  {
    intAlgHandle->preEmptContextInfo.earlyPreEmpt = 0;
    intAlgHandle->preEmptContextInfo.numContextBufs = 0;
    TIDL_unlockForPreemption(oldIntState, intAlgHandle->createParams, &lockState);
  }
  
  TIDL_enableL1DandL2CacheWb();

  tidl_printf(1, "TIDL_process is completed with handle : %x \n", algHandle);


  return status;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_activate
@brief      This is the function to do activation of algorithm.
            All scratch memory  are restored in this
            Refer algFree function for details in ialg.h file.
@param      handle : Algorithm Instance handle
@remarks    None
@return     None
----------------------------------------------------------------------------
*/
void  TIDL_activate(IALG_Handle handle)
{
  TIDL_Handle algHandle = (TIDL_Handle)(void*)(handle);

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  int32_t status = IALG_EOK;
  if(algHandle->algState == (uint8_t)ALG_NOT_ACTIVE)
  {
    tidl_printf(1, "TIDL_activate is called with handle : %x \n", algHandle);

    /* Initialize the DMA Utils Handle */
    if((algHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_ONLY) == TIDL_FLOW_CTRL_REF_ONLY)
    {
      algHandle->dmaUtilsContext = NULL;
    }
    else
    {
      status = TIDL_initDmaUtils(algHandle);
    }

    if(status != IALG_EOK)
    {
      tidl_printf(0, "TIDL_initDmaUtils returned Error Code for handle: %x \n", algHandle);
      return;
    }

    TIDL_Handle intAlgHandle = (TIDL_Handle)algHandle->intAlgHandle;

    status = TIDL_memcpy2D(intAlgHandle,
                  (const void  *)algHandle->memRec[ALG_HANDLE_MEMREC].base,
                  algHandle->memRec[ALG_HANDLE_MEMREC].size,
                  1U,
                  0,
                  0,
                  algHandle->dmaUtilsContext,
                  algHandle->memcpyTr);

    if(status != IALG_EOK)
    {
      tidl_printf(0, "TIDL_memcpy2D returned Error Code for handle: %x \n", algHandle);
      return;
    }
    
    TIDL_mmaHwaStatusWorkAround();

    /* Copy persistent weight buffers for all layers*/
    TIDL_copyPersistentWeightsToIntMem(intAlgHandle);

    /* Copy Pre-emption ContextMemory to Internal memory*/
    if (intAlgHandle->isPreEmptionEnable)
    {
      TIDL_restoreContextMemToIntMemForPreemption(&intAlgHandle->preEmptContextInfo,
        intAlgHandle->dmaUtilsContext, intAlgHandle->memcpyTr, intAlgHandle->createParams);
    }

    algHandle->algState = (uint8_t)ALG_ACTIVE;
  }

  return;
}



/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_deactivate
@brief      This is the function to do de-activation of algorithm.
            All scratch memory are stoed to external memory in this
            Refer algFree function for details in ialg.h file.
@param      handle : Algorithm Instance handle
@remarks    None
@return     None
----------------------------------------------------------------------------
*/
void  TIDL_deactivate(IALG_Handle handle)
{
  TIDL_Handle algHandle = (TIDL_Handle)(void*)(handle);
  TIDL_Handle intAlgHandle = (TIDL_Handle)(void*)(algHandle->intAlgHandle);

  if(algHandle->algState == (uint8_t)ALG_ACTIVE)
  {
    tidl_printf(1, "TIDL_deactivate is called with handle : %x \n", algHandle);

    if(NULL != intAlgHandle)
    {
      TIDL_memcpy2D(intAlgHandle->memRec[ALG_HANDLE_MEMREC].base,
                  intAlgHandle,
                  intAlgHandle->memRec[ALG_HANDLE_MEMREC].size,
                  1U,
                  0,
                  0,
                  intAlgHandle->dmaUtilsContext,
                  intAlgHandle->memcpyTr);

      /* Backup Pre-emption ContextMemory to external memory*/
      if (intAlgHandle->isPreEmptionEnable)
      {
        TIDL_storeContextMemToExtMemForPreemption(&intAlgHandle->preEmptContextInfo,
          intAlgHandle->dmaUtilsContext, intAlgHandle->memcpyTr);
      }
      /* Release the dma resources*/
      if (intAlgHandle->dmaUtilsContext != NULL )
      {
        (void)DmaUtilsAutoInc3d_deinit(intAlgHandle->dmaUtilsContext);
      }
    }
    algHandle->algState = (uint8_t)ALG_NOT_ACTIVE;

    TIDL_enableL1DandL2CacheWb();
  }

  return;
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION
@fn         TIDL_free
@brief      This is the function which user can call to get back
            the memory given to algo.
            Refer algFree function for details in ialg.h file.
@param      handle : Algorithm Instance handle
@param      memTab : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_free(IALG_Handle handle, IALG_MemRec *memRec)
{
  int32_t status            = IALG_EOK;
  TIDL_Handle algHandle = (TIDL_Handle)(void*)(handle);

  /* Removed TIDL_deactivate from test bench and added here to release DMA resources before freeing handle */
  TIDL_deactivate((IALG_Handle)handle);

  /* Since we are freeing this handle, we need to set TIDL_lastActiveHandle to NULL if it matches,
   * so that a deactivate is not called by the preemption logic later */
  if (TIDL_getLastActiveHandle() == handle)
  {
    TIDL_setLastActiveHandle(NULL);
  }

  /* For stats collection update the final calculated tensor scales which should be used during
  inference */
  if ((algHandle->createParams->flowCtrl & TIDL_FLOW_CTRL_REF_STAT) == TIDL_FLOW_CTRL_REF_STAT)
  {
    if ((algHandle->createParams->net->quantizationStyle == TIDL_QuantStyleNP2Fixed) ||
            (algHandle->createParams->net->quantizationStyle == TIDL_QuantStyleP2Dynamic))
    {
      if (algHandle->createParams->quantRangeUpdateFactor == 0.0f)
      {
        int32_t layerIdx;
        for ( layerIdx = 0; layerIdx < algHandle->createParams->net->numLayers; layerIdx++)
        {
          TIDL_UpdateScaleFactors(algHandle, layerIdx, 0, 0, 0);
        }
      }
    }

  }
  (void)memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  status = TIDL_removePriorityObject(algHandle, &algHandle->memRec[ALG_CONTEXT_MEM_MEMREC]);
#ifdef BUILD_WITH_CUDA
  TIDL_cudaFreeConvPtrs();
  TIDL_cudaFreeConvCudaPtrs();
  //TIDL_cudaFreeEltPtrs();
  TIDL_freeMaxPtrs();
  TIDL_cudaFreeConcatPtrs();
#endif
  return status;
}

