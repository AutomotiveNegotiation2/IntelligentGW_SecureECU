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
@file    tidl_device_utils.h
@brief   This file contains TILD alg Device Specific utils
@version 0.5 (Aug 2020) : Initial version [ADK]
----------------------------------------------------------------------------
*/


#ifndef ITIDL_DEVICE_UTILS_H
#define ITIDL_DEVICE_UTILS_H


void TIDL_setMark(int32_t layerIdx, int32_t markType);
void TIDL_setBlockMark(int32_t layerIdx, int32_t markType);

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
int32_t  TIDL_DspFillPaddedRows(uint8_t * ptr,
                                     const sBufferInfo_t * bufInfo,
                                     int32_t width,
                                     int32_t height,
                                     int32_t linePitch,
                                     int32_t channelPitch,
                                     void * dmautilsContext,
                                     uint8_t *zeroVec,
                                     uint8_t *isPadDmaPending,
                                     uint8_t * trMem,
                                     int32_t elementType,
                                     int32_t paddingType,
                                     void * padLayerParams,
                                     int32_t outDataPadH,
                                     int32_t outDataPadW,
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
int32_t  TIDL_DspFillPaddedCols(uint8_t * ptr, const sBufferInfo_t * bufInfo, int32_t width, int32_t height, 
                                          int32_t linePitch, int32_t channelPitch, int32_t elementSize, int32_t flowCtrl,
                                          int32_t paddingType, void * padLayerParams, int32_t outDataPadH, int32_t outDataPadW, void * perChannelPadValPtr, int32_t numBatches, uint32_t batchPitch );

template <class Tin, class Tinvec>
int32_t  TIDL_DspFillPaddedColsPadLayer(Tin *ptr, Tinvec padVector, const sBufferInfo_t * bufInfo, int32_t width, int32_t height, 
                                          int32_t linePitch, int32_t channelPitch, int32_t elementSize, int32_t flowCtrl, int32_t paddingType,
                                          void * padLayerParams, int32_t outDataPadH, int32_t outDataPadW, void * perChannelPadValPtr);

/* New generic Flow related functions are defined here */
int32_t TIDL_getKernelHandleSize(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t numSubHandles);


int32_t TIDL_getFeaturePlaneSize(const TIDL_CreateParams *params,
int32_t layerIdx, int32_t inHeight);


int32_t TIDL_setupKernelHandle(const TIDL_CreateParams *params,
                              int32_t layerIdx,
                              sTIDL_AlgLayer_t * algLayer
                              );


int32_t TIDL_isNewGenericFlowEnabled(const TIDL_CreateParams *params,
                                    int32_t layerIdx
                                    );

int32_t TIDL_isLayerSpatialPooling( const TIDL_CreateParams *params,
                                    int32_t layerIdx
                                    );

int32_t TIDL_getNumGenericFlowHandles(const sTIDL_Layer_t *tidlLayer);



int32_t TIDL_updateGenericFlowConstraints(const TIDL_CreateParams *params,
                                          int32_t layerIdx,
                                          sTIDL_DataParams_t *inDataParams,
                                          sDataFlowInfo_t * dataFlowInfo,
                                          int32_t inHeight,
                                          int32_t *flagDisableMSMCstaging
                                          );


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


void TIDL_syncPadTransfer(TIDL_Handle intAlgHandle, uint8_t * trMem);



/* Trigger the Weight DMA transfer for the next convolution layer from DDR to MSMC
and wait for the transfer for previously triggered convolution layer */

int32_t TIDL_syncWeightStagingTransfer(TIDL_Handle algHandle,
                                                                           int32_t currLayerNum,
                                                                           int32_t currAlgLayerIdx,
                                                                           int32_t targetDevice);


void TIDL_mmaHwaStatusWorkAround(void);


int32_t TIDL_initDmaUtils(
  TIDL_Handle          intAlgHandle
  );

/* Function to update the shift and bias for handling mix precision */
void TIDL_updateKernelShiftAndBiasForMixPrecision(int32_t shiftIn,
                                                              int32_t biasIn,
                                                              int32_t outputMixPrecision,
                                                              int32_t signedInputMixPrecision,
                                                              int32_t * shiftOut,
                                                              int32_t * biasOut);

/*Function to detect OTF specific errors*/
int32_t TIDL_OTFPadErrorCheck(TIDL_Handle algHandle);
/*Function to detect asymmetric specific errors*/
int32_t TIDL_AsymQuantizationCheck(TIDL_Handle algHandle);
/**
----------------------------------------------------------------------------
@ingroup    TIDL_UTILS
@fn         TIDL_getScratchMemChunkFromSysmem
@brief      Utility that allocates scratch mem of requested size
@param      sysMems : Array of sysMem parameters
@param      size : Size of memory chunk to be allocated
@param      alignment : Memory alignment amount

@remarks    None
@return     Pointer to the memory. NULL if no memory available
----------------------------------------------------------------------------
*/
void * TIDL_getScratchMemChunkFromSysmem(sTIDL_sysMemHandle_t sysMems[TIDL_SYSMEM_MAX],
                                      uint32_t size, 
                                      uint32_t alignment);

#endif /*  ITIDL_DEVICE_UTILS_H */

