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
 **| TI makes no representation or warranties with respect to performance             |**
 **| the of this computer program, and specifically disclaims         |**
 **| any responsibility for any damages, special or consequential,            |**
 **| connected with the use of this program.                                  |**
 **|                                                                          |**
 **+--------------------------------------------------------------------------+**
 *******************************************************************************/

#include "MMALIB_CNN_fullyConnected_ixX_ixX_oxX_idat.h"

#if ((TEST_CASE == 14) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseMobv2_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 74) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase3_ABC_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 75) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseMobv2Batch64_ABC_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 76) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseMobv2Batch128_ABC_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 81) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase4_ABC_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 555) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseMobv2Batch64Unaligned_i16s_i16s_o16s.h"
#endif

static fullyConnected_ixX_ixX_oxX_testParams_t testParams[] = {

#if ((TEST_CASE == 14) || (TEST_CATEGORY == 1000))
    {
        STATIC,
        staticRefInputACaseMobv2_i8s_i8s_o8s,
        MMALIB_INT8,
        staticRefInputBCaseMobv2_i8s_i8s_o8s,
        MMALIB_INT8,
        staticRefOutputCaseMobv2_i8s_i8s_o8s,
        MMALIB_INT8,
        1,
        1280,
        1280 * sizeof (int8_t),
        1344,
        128,
        (1344 * 64) * sizeof (int8_t),
        1,
        128,
        128 * sizeof (int8_t),
        13,
        12,
        MMALIB_SATURATION,
        MMALIB_TEST_OUTPUT_MSMC,
        MULTIPASS_FALSE,
        MULTIPASS_FALSE,
        1,
        1,
        14,
    },
#endif

#if ((TEST_CASE == 74) || (TEST_CATEGORY == 1000))
    {STATIC,
     staticRefInputACaseCase3_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefInputBCaseCase3_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefOutputCaseCase3_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     32,
     3,
     (3) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((1280)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     (8),
     128,
     (8 * 64) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((128)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     32,
     128,
     (128) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((100)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     13,
     12,
     MMALIB_SATURATION,
     MMALIB_TEST_OUTPUT_MSMC,
     MULTIPASS_FALSE,
     MULTIPASS_FALSE,
     1,
     1,
     74},
#endif

#if ((TEST_CASE == 75) || (TEST_CATEGORY == 1000))
    {STATIC,
     staticRefInputACaseMobv2Batch64_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefInputBCaseMobv2Batch64_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefOutputCaseMobv2Batch64_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     64,
     512,
     (576) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((1280)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     (517),
     128,
     (517 * 64) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((128)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     64,
     128,
     (128) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((100)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     13,
     12,
     MMALIB_SATURATION,
     MMALIB_TEST_OUTPUT_MSMC,
     MULTIPASS_FALSE,
     MULTIPASS_FALSE,
     1,
     1,
     75},
#endif

#if ((TEST_CASE == 76) || (TEST_CATEGORY == 1000))
    {STATIC,
     staticRefInputACaseMobv2Batch128_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefInputBCaseMobv2Batch128_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefOutputCaseMobv2Batch128_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     128,
     512,
     (576) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((1280)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     (517),
     128,
     (517 * 64) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((128)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     128,
     128,
     (128) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((100)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     13,
     12,
     MMALIB_SATURATION,
     MMALIB_TEST_OUTPUT_MSMC,
     MULTIPASS_FALSE,
     MULTIPASS_FALSE,
     1,
     1,
     76},
#endif


#if ((TEST_CASE == 81) || (TEST_CATEGORY == 1000))
    {STATIC,
     staticRefInputACaseCase4_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefInputBCaseCase4_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     staticRefOutputCaseCase4_ABC_i8s_i8s_o8s,
     MMALIB_INT8,
     64,
     1280,
     (1600) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((1280)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     (1285),
     128,
     (1285 * 64) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((128)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     64,
     128,
     (128) * sizeof (int8_t),
     /* MMALIB_CALC_STRIDE((100)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     13,
     12,
     MMALIB_SATURATION,
     MMALIB_TEST_OUTPUT_MSMC,
     MULTIPASS_FALSE,
     MULTIPASS_FALSE,
     1,
     1,
     81},
#endif

#if ((TEST_CASE == 555) || (TEST_CATEGORY == 1000))
    {STATIC,
     staticRefInputACaseMobv2Batch64Unaligned_i16s_i16s_o16s,
     MMALIB_INT16,
     staticRefInputBCaseMobv2Batch64Unaligned_i16s_i16s_o16s,
     MMALIB_INT16,
     staticRefOutputCaseMobv2Batch64Unaligned_i16s_i16s_o16s,
     MMALIB_INT16,
     64,
     1280,
     (1312) * sizeof (int16_t),
     /* MMALIB_CALC_STRIDE((63)*sizeof(int8_t),
      *                  MMALIB_ALIGN_SHIFT_64BYTES), */
     (1289),
     32,
     (1289 * 32) * sizeof (int16_t),
     /* MMALIB_CALC_STRIDE((128)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     64,
     32,
     (32) * sizeof (int16_t),
     /* MMALIB_CALC_STRIDE((100)*sizeof(int8_t),
      *                 MMALIB_ALIGN_SHIFT_64BYTES), */
     14,
     12,
     MMALIB_SATURATION,
     MMALIB_TEST_OUTPUT_MSMC,
     MULTIPASS_FALSE,
     MULTIPASS_FALSE,
     1,
     1,
     555},
#endif

};

/*
 *  Sends the test parameter structure and number of tests
 */
void fullyConnected_ixX_ixX_oxX_getTestParams (fullyConnected_ixX_ixX_oxX_testParams_t **params, int32_t *numTests)
{
   *params   = testParams;
   *numTests = sizeof (testParams) / sizeof (fullyConnected_ixX_ixX_oxX_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
