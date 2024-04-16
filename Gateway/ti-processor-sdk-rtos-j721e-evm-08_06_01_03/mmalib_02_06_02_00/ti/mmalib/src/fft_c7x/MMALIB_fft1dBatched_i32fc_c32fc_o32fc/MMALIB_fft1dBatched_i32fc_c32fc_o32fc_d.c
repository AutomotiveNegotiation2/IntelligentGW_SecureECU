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

#include <mmalib.h>

// include test infrastructure provided by MMALIB
#include "../../test/MMALIB_test.h"

#include "MMALIB_fft1dBatched_i32fc_c32fc_o32fc.h"
#include "MMALIB_fft1dBatched_i32fc_c32fc_o32fc_cn.h"
#include "MMALIB_fft1dBatched_i32fc_c32fc_o32fc_idat.h"
#include <math.h>

__attribute__ ((section (".msmcData"), aligned (64)))
int8_t msmcBuffer[MMALIB_L3_RESULTS_BUFFER_SIZE];
__attribute__ ((section (".ddrData"), aligned (64)))
int8_t ddrBuffer[2048 * 1024];

int16_t volatile volatileSum = 0;

#pragma DATA_SECTION(MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock, ".pinit")
uint8_t MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock
    [MMALIB_FFT1DBATCHED_I32FC_C32FC_O32FC_PBLOCK_SIZE];

void tw_gen (MMALIB_F32 *pW, uint32_t numPoints)
{
   uint32_t     i, j, k, t;
   const double PI = 3.141592654;
   t               = numPoints >> 2;
   for (j = 1, k = 0; j <= numPoints >> 2; j = j << 2) {
      for (i = 0; i < numPoints >> 2; i += j) {
         /* TODO: Big endian requires different format of Twiddle factors? */
         pW[k]             = (MMALIB_F32) cos (2 * PI * i / numPoints);
         pW[k + 1]         = (MMALIB_F32) -sin (2 * PI * i / numPoints);
         pW[k + 2 * t]     = (MMALIB_F32) cos (4 * PI * i / numPoints);
         pW[k + 2 * t + 1] = (MMALIB_F32) -sin (4 * PI * i / numPoints);
         pW[k + 4 * t]     = (MMALIB_F32) cos (6 * PI * i / numPoints);
         pW[k + 4 * t + 1] = (MMALIB_F32) -sin (6 * PI * i / numPoints);
         k += 2;
      }
      k += (t) *4;
      t = t >> 2;
   }
}

int MMALIB_fft1dBatched_i32fc_c32fc_o32fc_d (uint32_t *pProfile,
                                             uint8_t   LevelOfFeedback)
{
   int32_t             tpi;
   fft1d_testParams_t *prm;
   uint32_t            testNum;         // test case id
   int32_t             currentTestFail; // status of current test case
   int32_t             fail = 0;        // fail flag

   fft1d_getTestParams (&prm, &test_cases);

   TI_profile_init ("MMALIB_fft1dBatched_i32fc_c32fc_o32fc");

   for (tpi = 0; tpi < test_cases; tpi++) {

      int32_t       status_nat_vs_opt = TI_TEST_KERNEL_PASS;
      int32_t       status_nat_vs_ref = TI_TEST_KERNEL_PASS;
      MMALIB_STATUS status_opt        = MMALIB_SUCCESS;
      MMALIB_STATUS status_nat        = MMALIB_SUCCESS;
      uint32_t      numPoints;
      uint32_t      numChannels;
      uint32_t      dataMemSize;
      testNum = prm[tpi].testID;

      MMALIB_F32 *pX;
      MMALIB_F32 *pY;
      MMALIB_F32 *pXCn;
      MMALIB_F32 *pYCn;
      MMALIB_F32 *pW;
      int16_t *   pTempIn;

      numPoints   = prm[tpi].numPoints;
      numChannels = prm[tpi].numChannels;
      dataMemSize = numChannels * numPoints < 64
                        ? /* Kernel requires input/output */
                        64 * 2
                        : numChannels * numPoints * 2; /* buffers to be atleast
                                                        * 64 elements long */
      pX = (MMALIB_F32 *) TI_memalign (
          128,                                /* pX is required to be*/
          dataMemSize * sizeof (MMALIB_F32)); /* 16-byte aligned for
                                               * streaming engine use
                                               * in kernel           */
      pY = (MMALIB_F32 *) TI_memalign (128, dataMemSize * sizeof (MMALIB_F32));
      pW =
          (MMALIB_F32 *) TI_memalign (128, numPoints * 2 * sizeof (MMALIB_F32));

      /* pXCn    = (MMALIB_F32 *) malloc (dataMemSize * sizeof (MMALIB_F32)); */
      /* pYCn    = (MMALIB_F32 *) malloc (dataMemSize * sizeof (MMALIB_F32)); */
      /* pTempIn = (int16_t *) malloc (dataMemSize * sizeof (int16_t)); */
      pXCn    = (MMALIB_F32 *) msmcBuffer;
      pYCn    = pXCn + dataMemSize;
      pTempIn = (int16_t *) ((MMALIB_F32 *) pYCn + dataMemSize);

      MMALIB_DEBUGPRINTFN (1, "pXCn: %p, pYCn: %p, pTempIn: %p\n", pXCn, pYCn,
                           pTempIn);

      if (pX && pY && pW && pXCn && pYCn && pTempIn) {
         MMALIB_bufParams1D_t bufParamsData;
         MMALIB_bufParams1D_t bufParamsTw;
         int32_t              bufWidth, bufHeight;
         uint16_t             i;

         /* Utilities to copy buffers assume 16-bit types for buffer width,
          * height and stride. Hence, set width so that
          * stride = width*elementSize occupies less than 16 bits. */
         bufWidth  = numChannels * numPoints * 2;
         bufWidth  = bufWidth > 0x0800 ? 0x0800 : bufWidth;
         bufHeight = numChannels * numPoints * 2 / bufWidth;

         if ((prm[tpi].testPattern == RANDOM) ||
             (prm[tpi].testPattern == RANDOM_SIGNED)) {
            /* We control the magnitude of the random floats to ~ +/- 256 */

            /* We first generate random integers of a maximum value of
             * +/- 2^15                                                   */
            TI_fillBuffer (prm[tpi].testPattern, 0, pTempIn, NULL, bufWidth,
                           bufHeight, bufWidth * sizeof (int16_t),
                           sizeof (int16_t), testPatternString);
            /* We divide the random integers by 2^7 and convert to float  */
            for (i = 0; i < numChannels * numPoints * 2; i++) {
               pX[i] = ((float) (pTempIn[i])) /
                       ((float) (1 << (sizeof (int16_t) * 8 - 9)));
            }
         }
         else {
            TI_fillBuffer (prm[tpi].testPattern, 0, pX, prm[tpi].staticIn0,
                           bufWidth, bufHeight, bufWidth * sizeof (MMALIB_F32),
                           sizeof (MMALIB_F32), testPatternString);
         }
         bufParamsData.dim_x     = dataMemSize;
         bufParamsData.data_type = MMALIB_FLOAT32;

         /* Save data before calling kernel function because kernel
          * writes into input buffer                                */
         TI_fillBuffer (STATIC, 0, pXCn, pX, bufWidth, bufHeight,
                        bufWidth * sizeof (MMALIB_F32), sizeof (MMALIB_F32),
                        testPatternString);

         tw_gen (pW, numPoints);
         bufParamsTw.dim_x     = numPoints * 2;
         bufParamsTw.data_type = MMALIB_FLOAT32;

         TI_profile_start (TI_PROFILE_KERNEL_INIT);
         status_opt = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_init (
             (MMALIB_F32 *) pX, &bufParamsData, (MMALIB_F32 *) pW, &bufParamsTw,
             (MMALIB_F32 *) pY, &bufParamsData, numPoints, numChannels,
             MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock);
         TI_profile_stop ();

         TI_profile_start (TI_PROFILE_KERNEL_OPT);
         status_opt = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_kernel (
             (MMALIB_F32 *) pX, &bufParamsData, (MMALIB_F32 *) pW, &bufParamsTw,
             (MMALIB_F32 *) pY, &bufParamsData, numPoints, numChannels,
             MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock);
         TI_profile_stop ();

         /* Copy data again before calling kernel function because kernel
          * writes into input buffer                                */
         if ((prm[tpi].testPattern == RANDOM) ||
             (prm[tpi].testPattern == RANDOM_SIGNED)) {
            /* /\* We control the magnitude of the random floats to ~ +/- 256
             * *\/ */

            /* /\* We first generate random integers of a maximum value of */
            /*  * +/- 2^15                                                   *\/
             */
            /* TI_fillBuffer (prm[tpi].testPattern, */
            /*                0, */
            /*                pTempIn, */
            /*                NULL, */
            /*                bufWidth, */
            /*                bufHeight, */
            /*                bufWidth * sizeof (int16_t), */
            /*                sizeof (int16_t), */
            /*                testPatternString); */
            /* We divide the random integers by 2^7 and convert to float  */
            for (i = 0; i < numChannels * numPoints * 2; i++) {
               pX[i] = ((float) (pTempIn[i])) /
                       ((float) (1 << (sizeof (int16_t) * 8 - 9)));
            }
         }
         else {
            TI_fillBuffer (prm[tpi].testPattern, 0, pX, prm[tpi].staticIn0,
                           bufWidth, bufHeight, bufWidth * sizeof (MMALIB_F32),
                           sizeof (MMALIB_F32), testPatternString);
         }

         /* tw_gen (pW, numPoints); */
         /* TI_profile_start (TI_PROFILE_KERNEL_INIT); */
         /* status_opt = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_init ( */
         /*     (MMALIB_F32 *) pX, */
         /*     &bufParamsData, */
         /*     (MMALIB_F32 *) pW, */
         /*     &bufParamsTw, */
         /*     (MMALIB_F32 *) pY, */
         /*     &bufParamsData, */
         /*     numPoints, */
         /*     numChannels, */
         /*     MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock); */
         /* TI_profile_stop (); */

         /* run warm instruction cache test */
         TI_profile_start (TI_PROFILE_KERNEL_OPT_WARM);
         status_opt = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_kernel (
             (MMALIB_F32 *) pX, &bufParamsData, (MMALIB_F32 *) pW, &bufParamsTw,
             (MMALIB_F32 *) pY, &bufParamsData, numPoints, numChannels,
             MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock);
         TI_profile_stop ();

         // get output to L1D
         uint32_t row    = 0;
         int32_t  col    = 0;
         int16_t  outSum = 0;
         // treat output as bytes to be data type agnostic
         MMALIB_F32 *pDst = (MMALIB_F32 *) pY;
         for (row = 0; row < numChannels; row++) {
            for (col = 0; col < numPoints; col++) {
               outSum += *pDst;
               pDst++;
            }
         }

         /* dummy store of outSum to insure that the compiler does
not remove
          * it. */
         volatileSum = outSum;

         if ((prm[tpi].testPattern == RANDOM) ||
             (prm[tpi].testPattern == RANDOM_SIGNED)) {
            /* We control the magnitude of the random floats to ~ +/- 256 */

            /* We first generate random integers of a maximum value of
             * +/- 2^15                                                   */
            /* TI_fillBuffer (prm[tpi].testPattern, */
            /*                0, */
            /*                pTempIn, */
            /*                NULL, */
            /*                bufWidth, */
            /*                bufHeight, */
            /*                bufWidth * sizeof (int16_t), */
            /*                sizeof (int16_t), */
            /*                testPatternString); */
            /* We divide the random integers by 2^7 and convert to float  */
            for (i = 0; i < numChannels * numPoints * 2; i++) {
               pX[i] = ((float) (pTempIn[i])) /
                       ((float) (1 << (sizeof (int16_t) * 8 - 9)));
            }
         }
         else {
            TI_fillBuffer (prm[tpi].testPattern, 0, pX, prm[tpi].staticIn0,
                           bufWidth, bufHeight, bufWidth * sizeof (MMALIB_F32),
                           sizeof (MMALIB_F32), testPatternString);
         }

         /* tw_gen (pW, numPoints); */
         /* TI_profile_start (TI_PROFILE_KERNEL_INIT); */
         /* status_opt = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_init ( */
         /*     (MMALIB_F32 *) pX, */
         /*     &bufParamsData, */
         /*     (MMALIB_F32 *) pW, */
         /*     &bufParamsTw, */
         /*     (MMALIB_F32 *) pY, */
         /*     &bufParamsData, */
         /*     numPoints, */
         /*     numChannels, */
         /*     MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock); */
         /* TI_profile_stop (); */

         /* run warm instruction cache test */
         TI_profile_start (TI_PROFILE_KERNEL_OPT_WARMWRB);
         status_opt = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_kernel (
             (MMALIB_F32 *) pX, &bufParamsData, (MMALIB_F32 *) pW, &bufParamsTw,
             (MMALIB_F32 *) pY, &bufParamsData, numPoints, numChannels,
             MMALIB_fft1dBatched_i32fc_c32fc_o32fc_pBlock);
         TI_profile_stop ();

         TI_profile_start (TI_PROFILE_KERNEL_CN);
         status_nat = MMALIB_fft1dBatched_i32fc_c32fc_o32fc_cn (
             (MMALIB_F32 *) pXCn, &bufParamsData, (MMALIB_F32 *) pW,
             &bufParamsTw, (MMALIB_F32 *) pYCn, &bufParamsData, numPoints,
             numChannels);
         TI_profile_stop ();

         status_nat_vs_opt = TI_compare_mem_2D_float (
             (void *) pY, (void *) pYCn, 0, (double) powf (2, -5), bufWidth,
             bufHeight, bufWidth * sizeof (MMALIB_F32), sizeof (MMALIB_F32));

         if (prm[tpi].staticOut != NULL) {
            status_nat_vs_ref = TI_compare_mem_2D_float (
                (void *) prm[tpi].staticOut, (void *) pYCn, 0,
                (double) powf (2, -5), bufWidth, bufHeight,
                bufWidth * sizeof (MMALIB_F32), sizeof (MMALIB_F32));
         }

         currentTestFail =
             ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
              (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
              (status_opt != MMALIB_SUCCESS) || (status_nat != MMALIB_SUCCESS))
                 ? 1
                 : 0;

         fail = ((fail == 1) || (currentTestFail == 1)) ? 1 : 0;

         pProfile[3 * tpi] =
             (int32_t) TI_profile_get_cycles (TI_PROFILE_KERNEL_OPT);
         pProfile[3 * tpi + 1] =
             (int32_t) TI_profile_get_cycles (TI_PROFILE_KERNEL_OPT_WARM);
         pProfile[3 * tpi + 2] =
             (int32_t) TI_profile_get_cycles (TI_PROFILE_KERNEL_OPT_WARMWRB);
         /* est_test = 1; */
         sprintf (desc, "%s generated input | numPoints=%d numChannels=%d",
                  testPatternString, numPoints, numChannels);

         uint64_t archCycles = 0, estCycles = 0;
         /* TI_profile_formula_add_test ( */
         /*     numPoints * numChannels, 1, NULL, fail, desc, 1); */
         TI_profile_add_test (testNum++, numPoints * numChannels, archCycles,
                              estCycles, currentTestFail, desc);
      }
      else {
         sprintf (desc, "numPoints=%d, numChannels=%d", numPoints, numChannels);
         TI_profile_skip_test (desc);
         TI_profile_clear_run_stats ();
      }

      /* printf("pX:%p, pY:%p, pW:%p\n",pX, pY, pW); */
      TI_align_free (pX);
      TI_align_free (pY);
      TI_align_free (pW);
      /* free (pXCn); */
      /* free (pYCn); */
      /* free (pTempIn); */
   }

   return fail;
}

int test_main (uint32_t *pProfile)
{
#if !defined(_HOST_BUILD)
   if (TI_cache_init ()) {
      TI_memError ("MMALIB_fft1dBatched_i32fc_c32fc_o32fc");
      return 1;
   }
   else
#else
   printf ("_HOST_BUILD is defined.\n");
#endif //_HOST_BUILD
   {
      return MMALIB_fft1dBatched_i32fc_c32fc_o32fc_d (&pProfile[0], 0);
   }
}

/* Main call for individual test projects */
int main ()
{
   int fail = 1;

   uint32_t profile[256 * 3];

   MMALIB_TEST_init ();

   fail = test_main (&profile[0]);

#if !defined(NO_PRINTF)
   if (fail == 0)
      printf ("Test Pass!\n");
   else
      printf ("Test Fail!\n");

   int i;
   for (i = 0; i < test_cases; i++) {
      printf ("Test %4d: Cold Cycles = %8d, Warm Cycles = %8d, Warm Cycles WRB "
              "= %8d\n",
              i, profile[3 * i], profile[3 * i + 1], profile[3 * i + 2]);
   }
#endif

   return fail;
}

/* ======================================================================== */
/*  End of file:  MMALIB_fft1dBatched_i32fc_c32fc_o32fc_d.c */
/* ======================================================================== */
