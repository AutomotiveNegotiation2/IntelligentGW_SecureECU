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
@file    tidl_alg_utils.h
@brief   This file contains TILD alg inteface utilities API
@version 0.1 (Oct 2016) : Initial version [ADK]
@version 0.5 (Jan 2017) : Cleaned up [ADK]
----------------------------------------------------------------------------
*/
#ifndef ITIDL_ALG_UTILS_H
#define ITIDL_ALG_UTILS_H

/* Size of the memory in bytes allocated in DDR for custom layer */
#define TIDL_CUSTOM_LAYER_DDR_SIZE (64U*1024U)

/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_getSysScratchPtr
@brief      Function gives you a pointer to system memory used to store networks
            intermediate output
@param      bufInfo : Pointer to buffer info. This will come from dataflow
@param      sysScratchPtr    : Pointer which stores the base pointer for all system scratch
@param      baseAccessFlag   : Set it to one to get base pointer of feature map. Set it to zero to
                             go to the location where DMA/CPU will READ/WRITE.

@remarks    None
@return     Pointer to the memory. NULL if  buffers accessor is NONE
----------------------------------------------------------------------------
*/
void * TIDL_getSysScratchPtr(const sBufferInfo_t * bufInfo, const TIDL_sysScratchPtr *sysScratchPtr, uint32_t baseAccessFlag);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_FillPaddedRows
@brief      Fills the pading as per the requirements of the tensor
@param      ptr : Pointer to buffer  to fill
@param      bufInfo : Pointer to buffer info. This will come from dataflow

@remarks    None
@return     Pointer to the memory. NULL if  buffers accessor is NONE
----------------------------------------------------------------------------
*/
int32_t  TIDL_FillPaddedRows(uint8_t * ptr,
                                     const sBufferInfo_t * bufInfo,
                                     int32_t width,
                                     int32_t height,
                                     int32_t numBatches,
                                     int32_t linePitch,
                                     int32_t channelPitch,
                                     uint32_t batchPitch,
                                     void * dmautilsContext,
                                     uint8_t *zeroVec,
                                     uint8_t *isPadDmaPending,
                                     uint8_t * trMem,
                                     int32_t elementType,
                                     int32_t paddingType,
                                     void * padLayerParams,
                                     int32_t outDataPadH,
                                     int32_t outDataPadW,
                                     int32_t padFillValue,
                                     int32_t isFlowCtrlNatc,
                                     void * perChannelPadValPtr);
/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_FillPaddedColsWithZero
@brief      Fills the pading as per the requirements of the tensor
@param      ptr : Pointer to buffer  to fill
@param      bufInfo : Pointer to buffer info. This will come from dataflow

@remarks    None
@return     Pointer to the memory. NULL if  buffers accessor is NONE
----------------------------------------------------------------------------
*/
int32_t  TIDL_FillPaddedCols(uint8_t * ptr, const sBufferInfo_t * bufInfo, int32_t width, int32_t height, int32_t numBatches,
                                     int32_t linePitch, int32_t channelPitch, uint32_t batchPitch, int32_t elementType, int32_t flowCtrl, int32_t paddingType,
                                     void * padLayerParams, int32_t outDataPadH, int32_t outDataPadW, int32_t padFillValue, void * perChannelPadValPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_getMemoryChunkFromSysmem
@brief      Function gives you a pointer to system scratch memory based on user given input
            parameters

@param      sysMems : sysMem Handle
@param      size    : Number of bytes to be allocated
@param      alignment  : Alignment required for the pointer
@param      space     : in which memory memory is required. Refer \ref eSysMemScratch for valid values
@param      attribute : IALG_PERSIST/IALG_SCRATCH, note that all persistent memory should be allocated
                       in the beginning
@remarks    None
@return     Pointer to the allocated memory. NULL if there is not enough memory available
----------------------------------------------------------------------------
*/
void * TIDL_getMemoryChunkFromSysmem(sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX],
  uint32_t size, uint32_t alignment, uint32_t space, uint32_t attribute);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_resetSysmem
@brief      Function gives clears all the memories present in sysMem

@param      sysMems : sysMem Handle
@remarks    None
@return     None
----------------------------------------------------------------------------
*/
void TIDL_resetSysmem(sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX]);
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_isOutDataFlat
@brief      Function to Check whether current out data buffer needs to
            flattened

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_isOutDataFlat(const sTIDL_Network_t * pTIDLNetStructure, int32_t dataId);


int32_t TIDL_getDatElementSize(int32_t elementType);

int32_t TIDL_getDatElementSign(int32_t elementType);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_isOutDataBuff
@brief      Function to Check whether current data buffer is Output from
            current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@param      layersGroupId     : current algorithm instance Group ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_isOutDataBuff(const sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId, int32_t layersGroupId);



/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_isInDataBuff
@brief      Function to Check whether current data buffer is Input to
            current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@param      layersGroupId     : current algorithm instance Group ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_isInDataBuff(const sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId, int32_t layersGroupId);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getLayerNum
@brief      Function to get the layer index of data ID

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@param      layersGroupId     : current algorithm instance Group ID
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_getLayerNum(const sTIDL_Network_t * pTIDLNetStructure, int32_t dataId);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getDataParams
@brief      Function to Check whether current data buffer is Input to
            current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     Address of the Data Params Structure Base - If Successful
            NULL - If Faile - Requested dataID Not found
----------------------------------------------------------------------------
*/
sTIDL_DataParams_t * TIDL_getDataParams(sTIDL_Network_t * pTIDLNetStructure,
int32_t dataId);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getDataBuff
@brief      Function to get base buffer pointer from Ivision buffer

@param      bufDesc      : ivision buffer descriptor list
@param      numBufs      : Number of buffers in the list
@param      dataId       : Current data ID
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
void * TIDL_getDataBuff(IVISION_BufDesc *bufDesc[], uint32_t numBufs,
int32_t dataId, int32_t pitch[], int32_t isPaded);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_getLayerTypeForOutDataID
@brief      Function to Check whether current data buffer is Input to
current algorithm instance

@param      pTIDLNetStructure : Base pointer for net
@param      dataId            : Current data buffer ID
@remarks    None
@return     Address of the Data Params Structure Base - If Successful
NULL - If Faile - Requested dataID Not found
----------------------------------------------------------------------------
*/
int32_t TIDL_getLayerTypeForOutDataID(const sTIDL_Network_t * pTIDLNetStructure,
  int32_t dataId);


int32_t TIDL_updateDataParamsPitch(const sTIDL_DataParams_t  * dataParams);


int32_t TIDL_getNumInOutTensors(const TIDL_CreateParams *params,
                                int32_t layerIdx,
                                int32_t *numInTensors,
                                int32_t *numOutTensors
                                );



int32_t TIDL_getOutProcHeight(int32_t inHeight, sTIDL_Layer_t *currentLayer, sTIDL_DataParams_t *inDataParams);

void TIDL_poolingGetUpdatedPadValues(int32_t Fr, int32_t strideVal, int32_t padH, int32_t strideOffsetMethod, int32_t heightVal, int32_t *topPad, int32_t *bottomPad);

int32_t TIDL_getInOutPlaneSizes(const TIDL_CreateParams *params,
                                int32_t layerIdx,
                                sDataFlowInfo_t * dataFlowInfo,
                                sTIDL_DataParams_t *inDataParams,
                                int32_t *inPlaneSize,
                                sTIDL_DataParams_t *outDataParams,
                                int32_t *outPlaneSize,
                                int32_t *jumpReduction,
                                int32_t backupProcSize,
                                int32_t st,
                                int32_t targetDevice
                                );

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_outBuffAlloc
@brief      Function to Request Memory for layer output Memory

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
void TIDL_outBuffAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec memRec[], int32_t outDataSize);


void TIDL_scratchBufAlloc(int32_t layerIdx, IALG_MemRec memRec[], int32_t outDataSize);

void TIDL_scratchBufInit(int32_t layerIdx,
  const IALG_MemRec memRec[], void ** outPtr, int32_t outDataSize);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_findFreeOutBuff
@brief      Function to find the free output buffer used for tjis layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      outDataSize  : outDataSize required for this layer
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     outDataSize  : outDataSize required for this layer
----------------------------------------------------------------------------
*/
int32_t TIDL_findFreeOutBuff(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t outDataSize, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_outBuffInit
@brief      Function to Initialize the Layer output Memory

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
void TIDL_outBuffInit(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t *dataMemTabOffset,
const IALG_MemRec memRec[], void ** outPtr, int32_t outDataSize);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2DAlloc
@brief      Function to Request Memory required by the Convolution layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2DAlloc(const TIDL_CreateParams *params,
                                int32_t layerIdx, IALG_MemRec *memRec,
                                const  sDataFlowInfo_t * dataFlowInfo,
                                sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2dDspAlloc
@brief      Function to Request Memory required by the Convolution layer

@param      params       : Create Parameters
@param      dataFlowInfo : DataFlowInfo from Net structure
@param      mmaHandleSize: size of mmaHandleSize
@param      coeffBufferSize: size of coeffBufferSize
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2dDspAlloc(const TIDL_CreateParams *params,
                            const  sDataFlowInfo_t * dataFlowInfo,
                            int32_t convType,
                            int32_t layerIdx,
                            int32_t *mmaHandleSize,
                            int32_t *coeffBufferSize
);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2DInit
@brief      Function to Initialize the Convolution layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2DInit(TIDL_Handle tidlHandle,
                               const TIDL_CreateParams *params,
                               int32_t layerIdx,
                               sTIDL_AlgLayer_t *algLayer,
                               int32_t *paramMemTabOffset,
                               int32_t *dataMemTabOffset,
                               const IALG_MemRec memRec[],
                               void **outPtr,
                               int32_t quantizationStyle,
                               sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/*
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2dDspInit
@brief      Function to Initialize the Convolution layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2dDspInit(const TIDL_CreateParams *params,
                           int32_t layerIdx,
                           sTIDL_AlgLayer_t *algLayer,
                           int32_t *paramMemTabOffset,
                           const IALG_MemRec memRec[],
                           int32_t convType,
                           int32_t *mmaHandleSize,
                           int32_t *coeffBufferSize);

/*
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_conv2dSetupMmaHandle
@brief      Function to Initialize the Convolution layer mmahandles

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_conv2dSetupMmaHandle(TIDL_Handle tidlHandle,
                               const TIDL_CreateParams *params,
                               int32_t layerIdx,
                               sTIDL_AlgLayer_t *algLayer,
                               int32_t convType,
                               int32_t isChannelwiseQuantEnable
);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_deconv2DAlloc
@brief      Function to Request Memory required by the Convolution layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_deconv2DAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec,
  const  sDataFlowInfo_t * dataFlowInfo,
  sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_deconv2DInit
@brief      Function to Initialize the Convolution layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_deconv2DInit(TIDL_Handle tidlHandle,
                                const TIDL_CreateParams *params,
                                 int32_t layerIdx,
                                 sTIDL_AlgLayer_t *algLayer,
                                 const  sDataFlowInfo_t *dataFlowInfo,
                                 int32_t *paramMemTabOffset,
                                 int32_t *dataMemTabOffset,
                                 const IALG_MemRec memRec[],
                                 void **outPtr,
                                 int32_t quantizationStyle,
                                 sTIDL_LayerBuf_t *TIDLLayersBufPtr);


int32_t TIDL_innerProductAlloc(const TIDL_CreateParams *params,
                                     int32_t layerIdx, IALG_MemRec *memRec,
                                     sTIDL_LayerBuf_t *TIDLLayersBufPtr);



int32_t TIDL_innerProductInit(
        const TIDL_CreateParams *params, int32_t layerIdx,
        sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
        int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
        void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);



/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_eltWiseAlloc
@brief      Function to Request Memory required by the EltWise layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_eltWiseAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_shuffleChannelAlloc
@brief      Function to Request Memory required by the ShuffleChannel layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_shuffleChannelAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_resizeAlloc
@brief      Function to Request Memory required by the ShuffleChannel layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_resizeAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);



/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_eltWiseInit
@brief      Function to Initialize the EltWise layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_eltWiseInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_shuffleChannelInit
@brief      Function to Initialize the ShuffleChannel layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_shuffleChannelInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_resizeInit
@brief      Function to Initialize the ShuffleChannel layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_resizeInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_flattenAlloc
@brief      Function to Request Memory required by the Flatten layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_flattenAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_constDataAlloc
@brief      Function to Request Memory required by the ConstData layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_constDataAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_flattenInit
@brief      Function to Initialize the EltWise layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_flattenInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_constDataInit
@brief      Function to Initialize the constData layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_constDataInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_padAlloc
@brief      Function to Request Memory required by the Pad layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_padAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_padInit
@brief      Function to Initialize the Pad layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_padInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);
  

int32_t TIDL_colorConversionInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_reduceInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_scatterElementsInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);
/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_detectOutAlloc
@brief      Function to Request Memory required by the SSD detcetion output layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_detectOutAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_detectOutInit
@brief      Function to Initialize the SSD detcetion output layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_detectOutInit(
  const TIDL_CreateParams *params, int32_t layerIdx,
  sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_argMaxAlloc
@brief      Function to Request Memory required by the ArgMax layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_argMaxAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_roiPoolingAlloc
@brief      Function to Request Memory required by the ArgMax layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_roiPoolingAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_roiPoolingInit
@brief      Function to Initialize the ArgMax layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specicfic params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer ouput Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_roiPoolingInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_argMaxInit
@brief      Function to Initialize the ArgMax layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_argMaxInit(
const TIDL_CreateParams *params, int32_t layerIdx,
sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


int32_t TIDL_poolingAlloc(const TIDL_CreateParams *params,
                                 int32_t layerIdx, IALG_MemRec *memRec,
                                 sTIDL_LayerBuf_t *TIDLLayersBufPtr);


int32_t TIDL_poolingInit(const TIDL_CreateParams *params,
                                int32_t layerIdx,
                                sTIDL_AlgLayer_t * algLayer,
                                int32_t *paramMemTabOffset,
                                int32_t *dataMemTabOffset,
                                const IALG_MemRec *memRec,
                                void ** outPtr,
                                sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchNormAlloc
@brief      Function to Request Memory required by the Batch Norm layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchNormAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchNormInit
@brief      Function to Initialize the Batch Norm layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchNormInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchReshapeAlloc
@brief      Function to Request Memory required by the Batch Reshape layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchReshapeAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_batchReshapeInit
@brief      Function to Initialize the Batch Reshape layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_batchReshapeInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_softmaxAlloc
@brief      Function to Request Memory required by the Softmax layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_softmaxAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_softmaxInit
@brief      Function to Initialize the Softmax layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_softmaxInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_concatAlloc
@brief      Function to Request Memory required by the Concatinate layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_concatAlloc(const TIDL_CreateParams *params,
int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_concatInit
@brief      Function to Initialize the Concat layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_concatInit(const TIDL_CreateParams *params,
int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_dataConvertInit
@brief      Function to Initialize the Concat layer specific params

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      algLayer     : Pointer to current layer algorithm specific params
@param      paramMemTabOffset : Current Offset in ALG_LAYERS_PARAMS_BUFF_MEMREC
@param      dataMemTabOffset : Current Offset in ALG_SCRATCH_DATA_BUFF_MEMREC
@param      memRec       : memory table populated by the Algorithm
@param      outPtr       : Pointer to Layer output Pointers list
@param      TIDLLayersBuf: Temp structure to store outDataSize and Data Id's
@remarks    None
@return     IALG_EOK   - Successful
            IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_dataConvertInit(const TIDL_CreateParams *params,
                                  int32_t layerIdx, sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
                                  int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
                                  void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);


/**
----------------------------------------------------------------------------
@ingroup    TIDL_IVISION_SUPPORT
@fn         TIDL_customLayerAlloc
@brief      Function to Request Memory required by the Custom layer

@param      params       : Create Parameters
@param      layerIdx     : Current Layer index in Net structure
@param      memRec       : memory table populated by the Algorithm
@remarks    None
@return     IALG_EOK   - Successful
IALG_EFAIL - Unspecified error
----------------------------------------------------------------------------
*/
int32_t TIDL_customLayerAlloc(const TIDL_CreateParams *params,
  int32_t layerIdx, IALG_MemRec *memRec, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_customLayerInit(const TIDL_CreateParams *params, int32_t layerIdx,
    sTIDL_AlgLayer_t * algLayer, int32_t *paramMemTabOffset,
    int32_t *dataMemTabOffset, const IALG_MemRec *memRec,
    void ** outPtr, sTIDL_LayerBuf_t *TIDLLayersBufPtr);

int32_t TIDL_layerPadding(
  TIDL_Handle          intAlgHandle,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * outPtrs[],
  uint8_t              * trMem,
  int32_t i
  );



int32_t TIDL_getLayerInPtrs(
  IVISION_InBufs      *inBufs,
  IVISION_InBufs      *outBufs,
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * inPtrs[],
  int32_t i);


int32_t TIDL_getLayerOutPtrs(
  IVISION_InBufs      *outBufs,
  TIDL_Handle          intAlgHandle,
  sTIDL_AlgLayer_t     * algLayer,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * outPtrs[],
  int32_t i
  );


int32_t TIDL_updateAllLayersTensorStats(
  TIDL_Handle          intAlgHandle,
  sTIDL_Layer_t        * TIDLLayer,
  void                 * outPtrs[],
  int32_t i);


void TIDL_copyPersistentWeightsToIntMem(TIDL_Handle intAlgHandle);

void TIDL_switchHandles(void* algHandle);

void TIDL_forceTargetDeviceNonOTF(int32_t *targetDevice, int32_t layerType, int32_t convType);

int32_t TIDL_elementPromotionEnabledInAvgPool(const TIDL_CreateParams *params, sTIDL_Layer_t *tidlLayer);
#endif /* ITIDL_ARGMAX_H*/

