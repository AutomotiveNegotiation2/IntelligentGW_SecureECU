/*******************************************************************************
 **+--------------------------------------------------------------------------+**
 **|                            **** |**
 **|                            **** |**
 **|                            ******o*** |**
 **|                      ********_///_**** |**
 **|                      ***** /_//_/ **** |**
 **|                       ** ** (__/ **** |**
 **|                           ********* |**
 **|                            **** |**
 **|                            *** |**
 **| |**
 **|         Copyright (c) 2016 Texas Instruments Incorporated |**
 **|                        ALL RIGHTS RESERVED |**
 **| |**
 **| Permission to use, copy, modify, or distribute this software, |**
 **| whether in part or in whole, for any purpose is forbidden without |**
 **| a signed licensing agreement and NDA from Texas Instruments |**
 **| Incorporated (TI). |**
 **| |**
 **| TI makes no representation or warranties with respect to the |**
 **| performance of this computer program, and specifically disclaims |**
 **| any responsibility for any damages, special or consequential, |**
 **| connected with the use of this program. |**
 **| |**
 **+--------------------------------------------------------------------------+**
 *******************************************************************************/

#include "MATHLIB_cos_idat.h"

__attribute__ ((section (".staticData"))) static float staticRefInputCase1[] = {
    0.,         0.78539816, 1.57079633, 2.35619449,
    3.14159265, 3.92699082, 4.71238898, 5.49778714};

static cos_testParams_t testParams[] = {
/********************************************
 {
 testPattern,
 staticIn,
 filter,
 staticOut,
 dataType,
 dataSize,
 dataPitchIn,//in bytes
 dataPitchOut, // in bytes
 batchSize,
 filterSize,
 shift,
 outputDataLocation,
 numReps, testID
 },
 *********************************************/

#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 1) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        256,                      // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        1                         // testID
    },
#endif
#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 2) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM_SIGNED,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        64,                       // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        2                         // testID
    },
#endif
#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 3) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM_SIGNED,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        512,                      // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        3                         // testID
    },
#endif
#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 4) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM_SIGNED,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        1024,                     // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        4                         // testID
    },
#endif
#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 5) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM_SIGNED,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        576,                      // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        5                         // testID
    },
#endif
#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 6) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM_SIGNED,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        1152,                     // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        6                         // testID
    },
#endif
#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 7) ||                   \
     (TEST_CATEGORY == 100))
    {
        RANDOM_SIGNED,
        NULL,                     //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        10240,                    // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        7                         // testID
    },
#endif

#if (defined(ALL_TEST_CASES) || (EXTENDED_TEST_CASE == 8) ||                   \
     (TEST_CATEGORY == 100))
    {
        STATIC,
        staticRefInputCase1,      //*staticIn
        NULL,                     //*staticOut
        MATHLIB_FLOAT32,          // dataType
        8,                        // dataSize
        MATHLIB_TEST_OUTPUT_MSMC, // outputDataLocation
        1,                        // numReps
        8                         // testID
    },
#endif

};

/*
 *  Sends the test parameter structure and number of tests
 */
void cos_getTestParams (cos_testParams_t **params, int32_t *numTests)
{
   *params   = testParams;
   *numTests = sizeof (testParams) / sizeof (cos_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
