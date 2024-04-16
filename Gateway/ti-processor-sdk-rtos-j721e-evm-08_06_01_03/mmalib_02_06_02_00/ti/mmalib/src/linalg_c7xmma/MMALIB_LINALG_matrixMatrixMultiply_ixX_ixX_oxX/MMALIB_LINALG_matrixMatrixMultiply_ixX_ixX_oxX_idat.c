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
 **|         Copyright (c) 2016 Texas Instruments Incorporated                |**
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

#include "MMALIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_idat.h"

static matrixMatrixMultiply_ixX_ixX_oxX_testParams_t    testParams[]=
{
   /********************************************
    {
    testPattern,
    staticIn0, staticIn1, staticOut
    heightIn0 (M), widthIn0 (K), strideIn0
    heightIn1 (K), widthIn1 (N), strideIn1
    heightOut (M), widthOut (N), strideOut,
    shiftOut, numRepetitions
    },
    *********************************************/
   
#if ((TEST_CATEGORY == 1000) || (TEST_CASE == 1000))
   {
      MMALIB_PERFORMANCE_TEST_PATTERN,
      NULL, MMALIB_INT8, NULL, MMALIB_INT8, NULL, MMALIB_INT8,
      1*MMALIB_MMA_SIZE_8_BIT+0, 1*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((1*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      1*MMALIB_MMA_SIZE_8_BIT+0, 1*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((1*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      1*MMALIB_MMA_SIZE_8_BIT+0, 1*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((1*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      11,   // shiftOut
      MMALIB_TEST_OUTPUT_MSMC,
      1,    // numReps
      1000   //testID
   },
#endif
#if ((TEST_CATEGORY == 1000) || (TEST_CASE == 1001))
   {
      MMALIB_PERFORMANCE_TEST_PATTERN,
      NULL, MMALIB_INT8, NULL, MMALIB_INT8, NULL, MMALIB_INT8,
      2*MMALIB_MMA_SIZE_8_BIT+0, 2*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((2*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      2*MMALIB_MMA_SIZE_8_BIT+0, 2*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((2*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      2*MMALIB_MMA_SIZE_8_BIT+0, 2*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((2*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      11,   // shiftOut
      MMALIB_TEST_OUTPUT_MSMC,
      1,    // numReps
      1001   //testID
   },
#endif
#if ((TEST_CATEGORY == 1000) || (TEST_CASE == 1002))
   {
      MMALIB_PERFORMANCE_TEST_PATTERN,
      NULL, MMALIB_INT8, NULL, MMALIB_INT8, NULL, MMALIB_INT8,
      4*MMALIB_MMA_SIZE_8_BIT+0, 4*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((4*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      4*MMALIB_MMA_SIZE_8_BIT+0, 4*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((4*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      4*MMALIB_MMA_SIZE_8_BIT+0, 4*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((4*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      11,   // shiftOut
      MMALIB_TEST_OUTPUT_MSMC,
      1,    // numReps
      1002   //testID
   },
#endif
#if ((TEST_CATEGORY == 1000) || (TEST_CASE == 1003))
   {
      MMALIB_PERFORMANCE_TEST_PATTERN,
      NULL, MMALIB_INT8, NULL, MMALIB_INT8, NULL, MMALIB_INT8,
      6*MMALIB_MMA_SIZE_8_BIT+0, 6*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((6*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      6*MMALIB_MMA_SIZE_8_BIT+0, 6*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((6*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      6*MMALIB_MMA_SIZE_8_BIT+0, 6*MMALIB_MMA_SIZE_8_BIT+0, MMALIB_CALC_STRIDE((6*MMALIB_MMA_SIZE_8_BIT+0)*sizeof(int8_t)+64, MMALIB_ALIGN_SHIFT_64BYTES),
      11,   // shiftOut
      MMALIB_TEST_OUTPUT_MSMC,
      1,    // numReps
      1003   //testID
   },
#endif
   
};

/*
 *  Sends the test parameter structure and number of tests
 */
void matrixMatrixMultiply_ixX_ixX_oxX_getTestParams(matrixMatrixMultiply_ixX_ixX_oxX_testParams_t * *params, int32_t *numTests)
{
   *params = testParams;
   *numTests = sizeof(testParams) / sizeof(matrixMatrixMultiply_ixX_ixX_oxX_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

