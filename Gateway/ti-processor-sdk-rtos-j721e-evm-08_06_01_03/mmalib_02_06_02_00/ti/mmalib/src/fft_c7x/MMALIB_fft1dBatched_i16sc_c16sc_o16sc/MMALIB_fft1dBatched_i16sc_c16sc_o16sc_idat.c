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
 **|         Copyright (c) 2017 Texas Instruments Incorporated |**
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
#include "MMALIB_fft1dBatched_i16sc_c16sc_o16sc_idat.h"
/* #include "../../common/TI_memory.h" */

__attribute__ ((section (".staticData"))) static uint32_t shiftVector27[] = {0, 1, 1, 0, 1};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector28[] = {1, 1, 1, 1};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector29[] = {1, 1, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector30[] = {1, 1};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector31[] = {1, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector32[] = {0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector33[] = {0, 1};

__attribute__ ((section (".staticData"))) static uint32_t shiftVector16Point[]   = {0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector32Point[]   = {0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector64Point[]   = {0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector128Point[]  = {0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector256Point[]  = {0, 0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector512Point[]  = {0, 0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector1024Point[] = {0, 0, 0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector2048Point[] = {0, 0, 0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector4096Point[] = {0, 0, 0, 0, 0, 0};
__attribute__ ((section (".staticData"))) static uint32_t shiftVector8192Point[] = {0, 0, 0, 0, 0, 0};

__attribute__ ((section (".staticData"))) static fft1dBatched_i16sc_c16sc_o16sc_testParams_t testParams[] = {
/********************************************
    {
       testPattern,
       *staticIn0, staticIn1, staticOut
       width, height, stride
    },
*********************************************/

#if ((TEST_CASE == 66) || (TEST_CATEGORY == 1000))
    {
        RANDOM,
        NULL,
        shiftVector512Point,
        NULL,
        4,
        64,
        512,
        66,
    },
#endif

/* #if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 300) || (TEST_CATEGORY == 100) || (EXTENDED_TEST_CASE == 93)) */
/*     { */
/*         RANDOM, */
/*         NULL, */
/*         shiftVector8192Point, */
/*         NULL, */
/*         6, */
/*         32, */
/*         8192, */
/*         93, */
/*     }, */
/* #endif */
/* #if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 300) || (TEST_CATEGORY == 100) || (EXTENDED_TEST_CASE == 94)) */
/*     { */
/*         RANDOM, */
/*         NULL, */
/*         shiftVector8192Point, */
/*         NULL, */
/*         6, */
/*         64, */
/*         8192, */
/*         94, */
/*     }, */
/* #endif */

#if ((TEST_CASE == 95) || (TEST_CATEGORY == 1000))
    {
        RANDOM,
        NULL,
        shiftVector32Point,
        NULL,
        2,
        256,
        32,
        95,
    },
#endif
};

/*
 *  Sends the test parameter structure and number of tests
 */
void fft1dBatched_i16sc_c16sc_o16sc_getTestParams (fft1dBatched_i16sc_c16sc_o16sc_testParams_t **params, int32_t *numTests)
{
   *params   = testParams;
   *numTests = sizeof (testParams) / sizeof (fft1dBatched_i16sc_c16sc_o16sc_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2017 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
