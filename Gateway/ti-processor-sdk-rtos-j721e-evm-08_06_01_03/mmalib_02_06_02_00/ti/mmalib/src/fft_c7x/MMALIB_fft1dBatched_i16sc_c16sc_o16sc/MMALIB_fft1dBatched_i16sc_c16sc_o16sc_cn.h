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

#ifndef MMALIB_FFT1DBATCHED_I16SC_C16SC_O16SC_CN_H_
#define MMALIB_FFT1DBATCHED_I16SC_C16SC_O16SC_CN_H_ 1

#include "../../common/MMALIB_types.h"

MMALIB_STATUS
MMALIB_fft1dBatched_i16sc_c16sc_o16sc_cn (int16_t *             pX,
                                          MMALIB_bufParams1D_t *bufParamsX,
                                          int16_t *             pW,
                                          MMALIB_bufParams1D_t *bufParamsW,
                                          int16_t *             pY,
                                          MMALIB_bufParams1D_t *bufParamsY,
                                          uint32_t *            pShift,
                                          MMALIB_bufParams1D_t *bufParamsShift,
                                          uint32_t              numPoints,
                                          uint32_t              numChannels);

MMALIB_STATUS MMALIB_fft1dBatched_i16sc_c16sc_o16sc_checkParams_cn (
    int16_t *             pX,
    MMALIB_bufParams1D_t *bufParamsX,
    int16_t *             pW,
    MMALIB_bufParams1D_t *bufParamsW,
    int16_t *             pY,
    MMALIB_bufParams1D_t *bufParamsY,
    uint32_t *            pShift,
    MMALIB_bufParams1D_t *bufParamsShift,
    uint32_t              numPoints,
    uint32_t              numChannels);

#endif /* MMALIB_FFT1DBATCHED_I16SC_C16SC_O16SC_CN_H_ */
