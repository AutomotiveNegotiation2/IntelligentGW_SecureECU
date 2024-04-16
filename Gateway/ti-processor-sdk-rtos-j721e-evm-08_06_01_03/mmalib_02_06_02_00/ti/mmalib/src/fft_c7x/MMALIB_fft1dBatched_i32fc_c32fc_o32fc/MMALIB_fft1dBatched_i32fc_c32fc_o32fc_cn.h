/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2017 Texas Instruments Incorporated                |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef MMALIB_FFT1DBATCHED_I32FC_C32FC_O32FC_CN_H_
#define MMALIB_FFT1DBATCHED_I32FC_C32FC_O32FC_CN_H_ 1

#include "../../common/MMALIB_types.h"

MMALIB_STATUS
MMALIB_fft1dBatched_i32fc_c32fc_o32fc_cn (MMALIB_F32 *          pX,
                                          MMALIB_bufParams1D_t *bufParamsX,
                                          MMALIB_F32 *          pW,
                                          MMALIB_bufParams1D_t *bufParamsW,
                                          MMALIB_F32 *          pY,
                                          MMALIB_bufParams1D_t *bufParamsY,
                                          uint32_t              numPoints,
                                          uint32_t              numChannels);

MMALIB_STATUS MMALIB_fft1dBatched_i32fc_c32fc_o32fc_checkParams_cn (
    MMALIB_F32 *          pX,
    MMALIB_bufParams1D_t *bufParamsX,
    MMALIB_F32 *          pW,
    MMALIB_bufParams1D_t *bufParamsW,
    MMALIB_F32 *          pY,
    MMALIB_bufParams1D_t *bufParamsY,
    uint32_t              numPoints,
    uint32_t              numChannels);

#endif
