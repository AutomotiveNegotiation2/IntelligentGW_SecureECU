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

// include MMALIB
#include <mmalib.h>

// include test infrastructure provided by MMALIB
#include "../../test/MMALIB_test.h"

// include test data for this kernel
#include "MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_idat.h"


__attribute__ ((section (".ddrData"), aligned (64))) int8_t ddrBuffer[2048 * 1024];

#define MMALIB_FFT_HIGHRADIXDECOMPOSITIONS_IXX_CXX_OXX_MAXDIMXL2 65536

int MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_d(
   uint32_t *pProfile,
   uint8_t LevelOfFeedback)
{
   int32_t  tpi;
   int32_t  currentTestFail;
   int32_t  fail = 0;
   uint32_t  repCount;
   uint32_t numReps;
   MMALIB_bufParams1D_t bufParamsX, bufParamsY, bufParamsW;
   uint32_t k, j;
   uint32_t testNum;
   uint64_t archCycles, estCycles;
   int32_t dataDoubleBuffered;

   highRadixDecompositions_ixX_cxX_oxX_testParams_t   *prm;
   highRadixDecompositions_ixX_cxX_oxX_testParams_t   currPrm;
   highRadixDecompositions_ixX_cxX_oxX_getTestParams(&prm, &test_cases);

   MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_InitArgs    kerInitArgs;

   int32_t handleSize = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_getHandleSize(&kerInitArgs);
   MMALIB_kernelHandle handle = malloc(handleSize);

   TI_profile_init("MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX");

   for (tpi=0; tpi < test_cases; tpi++) {
      numReps = prm[tpi].numReps;
      testNum = prm[tpi].testID;
      currPrm = prm[tpi];

      for (repCount = 0; repCount < numReps; repCount++){
	 int32_t      status_nat_vs_opt = TI_TEST_KERNEL_FAIL;
	 int32_t      status_ref_vs_opt = TI_TEST_KERNEL_FAIL;
	 MMALIB_STATUS   status_init = MMALIB_SUCCESS;
	 MMALIB_STATUS   status_opt = MMALIB_SUCCESS;
	 MMALIB_STATUS   status_nat = MMALIB_SUCCESS;
	 void *pX, *pY, *pW, *pYCn, *pTemp;

	 /* Sometimes, depending on certain compile flags, the test will be
	  * marked PASS even if no comparison is done. This flag is to detect
	  * if a comparison was done or not                                   */
	 int32_t      comparisonDone = 0;

	 currentTestFail = 0;

	 kerInitArgs.fftSize = currPrm.fftSize;
	 if (kerInitArgs.fftSize*currPrm.batchSize*2*MMALIB_sizeof(currPrm.dataType) >
	       MMALIB_FFT_HIGHRADIXDECOMPOSITIONS_IXX_CXX_OXX_MAXDIMXL2) {
	    kerInitArgs.batchSize =
	       MMALIB_FFT_HIGHRADIXDECOMPOSITIONS_IXX_CXX_OXX_MAXDIMXL2/(kerInitArgs.fftSize*2*MMALIB_sizeof(currPrm.dataType));
	    dataDoubleBuffered = 1;
	 } else {
	    kerInitArgs.batchSize = currPrm.batchSize;
	    dataDoubleBuffered = 0;
	 }
	 for (k = 0; k < MMALIB_FFT_HIGHRADIXDECOMPOSITIONS_IXX_CXX_OXX_NUMSHIFTS; k++) {
	     kerInitArgs.shiftVector[k] = currPrm.shiftVector[k];
	 }
	 kerInitArgs.interleave = currPrm.interleave;
	 bufParamsX.data_type = currPrm.dataType;
	 bufParamsY.data_type = currPrm.dataType;
	 bufParamsW.data_type = currPrm.dataType;
	 MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_getSizes(&kerInitArgs,
								 &bufParamsX,
								 &bufParamsW,
								 &bufParamsY);

	 /* Allocate twice the size to facilitate double-buffering of data in
	    L2 to/from MSMC. We do not implement the double-buffering in this
	    driver file, but a higher layer application can potentially
	    implement the double-buffering
	       In addition, we align the following buffers to 64 bytes. Optimal
	    performance of loads using SE (using transpose mode in particular)
	    requires 64 byte alignment.                                       */
	 if (dataDoubleBuffered) {
	    pX   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, 2*bufParamsX.dim_x*MMALIB_sizeof(bufParamsX.data_type));
	    pY   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, 2*bufParamsY.dim_x*MMALIB_sizeof(bufParamsY.data_type));
	    pW   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsW.dim_x*MMALIB_sizeof(bufParamsW.data_type));
	    pYCn = NULL;
	    pTemp = NULL;
	 } else {
	    pX   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsX.dim_x*MMALIB_sizeof(bufParamsX.data_type));
	    pY   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsY.dim_x*MMALIB_sizeof(bufParamsY.data_type));
	    pW   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsW.dim_x*MMALIB_sizeof(bufParamsW.data_type));
	    pYCn = (void *) malloc(bufParamsY.dim_x*MMALIB_sizeof(bufParamsY.data_type));
	    pTemp = (void *) malloc(bufParamsX.dim_x*MMALIB_sizeof(bufParamsX.data_type));
	 }

	 /* Only run the test if the buffer allocations fit in the heap */
	 if( pX && pW && pY && (dataDoubleBuffered || (pYCn && pTemp)) ) {

	    if (dataDoubleBuffered) {
	       TI_fillBuffer(prm[tpi].testPattern,
			     0,
			     pX,
			     currPrm.staticIn,
			     2*kerInitArgs.batchSize*kerInitArgs.fftSize*2,
			     1,
			     2*kerInitArgs.batchSize*kerInitArgs.fftSize*2*MMALIB_sizeof(bufParamsX.data_type),
			     MMALIB_sizeof(bufParamsX.data_type),
			     testPatternString);
            } else {
	       TI_fillBuffer(prm[tpi].testPattern,
			     0,
			     pX,
			     currPrm.staticIn,
			     kerInitArgs.batchSize*kerInitArgs.fftSize*2,
			     1,
			     kerInitArgs.batchSize*kerInitArgs.fftSize*2*MMALIB_sizeof(bufParamsX.data_type),
			     MMALIB_sizeof(bufParamsX.data_type),
			     testPatternString);
            }

	    if (!dataDoubleBuffered) {
	       /* Save data before calling kernel function because kernel
		* writes into input buffer                                */
	       TI_fillBuffer(STATIC,
			     0,
			     pTemp,
			     pX,
			     kerInitArgs.batchSize*kerInitArgs.fftSize*2,
			     1,
			     kerInitArgs.batchSize*kerInitArgs.fftSize*2*MMALIB_sizeof(bufParamsX.data_type),
			     MMALIB_sizeof(bufParamsX.data_type),
			     testPatternString);
	    }

	    MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_twGen(&kerInitArgs,
								 pW,
								 &bufParamsW);

	    status_init = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_init_checkParams(handle,
											  &bufParamsX,
											  &bufParamsW,
											  &bufParamsY,
											  &kerInitArgs);
	    if (status_init == MMALIB_SUCCESS) {
	       TI_profile_start(TI_PROFILE_KERNEL_INIT);
	       MMALIB_asm(" MARK 0");
	       kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
	       status_init = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_init(handle,
										 &bufParamsX,
										 &bufParamsW,
										 &bufParamsY,
										 &kerInitArgs);
	       MMALIB_asm(" MARK 1");
	       TI_profile_stop();
	    }

	    status_opt = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_exec_checkParams(handle,
											 pX,
											 pW,
											 pY);
	    if((status_init == MMALIB_SUCCESS) && (status_opt == MMALIB_SUCCESS) ) {
	       if (!dataDoubleBuffered) {
		  TI_profile_start(TI_PROFILE_KERNEL_OPT);
		  MMALIB_asm(" MARK 2");
		  status_opt = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_exec(handle,
										   pX,
										   pW,
										   pY);
		  MMALIB_asm(" MARK 3");
		  TI_profile_stop();
	       } else {
		  int32_t pingPong;
		  uint8_t *pXPing, *pXPong;
		  uint8_t *pYPing, *pYPong;

		  pingPong = 0;
		  pXPing = (uint8_t *)pX;
		  pXPong = pXPing + bufParamsX.dim_x*MMALIB_sizeof(bufParamsX.data_type);
		  pYPing = (uint8_t *)pY;
		  pYPong = pYPing + bufParamsY.dim_x*MMALIB_sizeof(bufParamsY.data_type);

		  TI_profile_start(TI_PROFILE_KERNEL_OPT);
		  MMALIB_asm(" MARK 2");
		  /* Double-buffering to copy data between L2<->MSMC is not
		   * implemented, this loop is only for profiling purposes.
		   * The output will be overwritten in subsequent iterations
		   * and cannot be used for comparison with natural C output  */
		  for (j = 0; j < currPrm.batchSize; j += kerInitArgs.batchSize) {
		     status_opt = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_exec(handle,
										      pX,
										      pW,
										      pY);
		     pingPong ^= 1;
		     pX = pingPong ? (void *)pXPong : (void *)pXPing;
		     pY = pingPong ? (void *)pYPong : (void *)pYPing;
		  }
		  MMALIB_asm(" MARK 3");
		  TI_profile_stop();
	       }
	       if (!dataDoubleBuffered) {
		  /* The following for loop is to call kernel repeatedly so as to
		   * train the branch predictor                                   */
		  for (j = 0; j < 4; j++) {
		     /* Restore saved data into input buffer as previous kernel call
		      * must have destroyed the input buffer                           */
		     TI_fillBuffer(STATIC,
				   0,
				   pX,
				   pTemp,
				   kerInitArgs.batchSize*kerInitArgs.fftSize*2,
				   1,
				   kerInitArgs.batchSize*kerInitArgs.fftSize*2*MMALIB_sizeof(bufParamsX.data_type),
				   MMALIB_sizeof(bufParamsX.data_type),
				   testPatternString);

		     // run warm instruction cache test
		     TI_profile_clear_cycle_count_single(TI_PROFILE_KERNEL_OPT_WARM);
		     TI_profile_start(TI_PROFILE_KERNEL_OPT_WARM);
		     MMALIB_asm(" MARK 4");
		     status_opt = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_exec(handle,
										      pX,
										      pW,
										      pY);
		     MMALIB_asm(" MARK 5");
		     TI_profile_stop();
		  }
	       } else {
		  int32_t pingPong;
		  uint8_t *pXPing, *pXPong;
		  uint8_t *pYPing, *pYPong;

		  pingPong = 0;
		  pXPing = (uint8_t *)pX;
		  pXPong = pXPing + bufParamsX.dim_x*MMALIB_sizeof(bufParamsX.data_type);
		  pYPing = (uint8_t *)pY;
		  pYPong = pYPing + bufParamsY.dim_x*MMALIB_sizeof(bufParamsY.data_type);

		  TI_profile_start(TI_PROFILE_KERNEL_OPT_WARM);
		  MMALIB_asm(" MARK 4");
		  /* Double-buffering to copy data between L2<->MSMC is not
		   * implemented, this loop is only for profiling purposes.
		   * The output will be overwritten in subsequent iterations
		   * and cannot be used for comparison with natural C output  */
		  for (j = 0; j < currPrm.batchSize; j += kerInitArgs.batchSize) {
		     status_opt = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_exec(handle,
										      pX,
										      pW,
										      pY);
		     pingPong ^= 1;
		     pX = pingPong ? (void *)pXPong : (void *)pXPing;
		     pY = pingPong ? (void *)pYPong : (void *)pYPing;
		  }
		  MMALIB_asm(" MARK 5");
		  TI_profile_stop();
	       }
	    }

	    if (!dataDoubleBuffered) {
	    /* If double buffering was required to support the processing of
	     * batch from L2, then output of _ci kernels will not be anyway
	     * correct, hence we do not need to generate reference output
	     * using _cn kernels                                              */

	       /* Test _cn kernel */
	       kerInitArgs.funcStyle = MMALIB_FUNCTION_NATC;

	       // initialize the kernel to use the natural C variant
	       MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_init(handle,
								   &bufParamsX,
								   &bufParamsW,
								   &bufParamsY,
								   &kerInitArgs);

	       /* Restore saved data into input buffer as previous kernel call
		* must have destroyed the input buffer                           */
	       TI_fillBuffer(STATIC,
			     0,
			     pX,
			     pTemp,
			     kerInitArgs.batchSize*kerInitArgs.fftSize*2,
			     1,
			     kerInitArgs.batchSize*kerInitArgs.fftSize*2*MMALIB_sizeof(currPrm.dataType),
			     MMALIB_sizeof(currPrm.dataType),
			     testPatternString);

	       if((status_init == MMALIB_SUCCESS) && (status_opt == MMALIB_SUCCESS) ) {
		  TI_profile_start(TI_PROFILE_KERNEL_CN);
		  MMALIB_asm(" MARK 8");
		  status_nat = MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_exec(handle,
										   pX,
										   pW,
										   pYCn);
		  MMALIB_asm(" MARK 9");
		  TI_profile_stop();
	       }

	       status_nat_vs_opt = TI_compare_mem_2D((void *)pY,
						     (void *)pYCn,
						     50,
						     65535,
						     kerInitArgs.batchSize*kerInitArgs.fftSize*2,
						     1,
						     kerInitArgs.batchSize*kerInitArgs.fftSize*2* MMALIB_sizeof(bufParamsY.data_type),
						     MMALIB_sizeof(bufParamsY.data_type));
	       comparisonDone = 1;
	    } else {
	       status_nat_vs_opt = TI_TEST_KERNEL_PASS;
	    }

	    if( currPrm.staticOut != NULL ) {
		status_ref_vs_opt = TI_compare_mem_2D((void *)currPrm.staticOut,
						      (void *)pY,
						      200,
						      65535,
						      kerInitArgs.batchSize*kerInitArgs.fftSize*2,
						      1,
						      kerInitArgs.batchSize*kerInitArgs.fftSize*2* MMALIB_sizeof(bufParamsY.data_type),
						      MMALIB_sizeof(bufParamsY.data_type));
		comparisonDone = 1;
	    } else {
	       /* Set to pass since it wasn't supposed to run. */
	       status_ref_vs_opt = TI_TEST_KERNEL_PASS;
	    }

	    /* Set the 'fail' flag based on test vector comparison results */
	    currentTestFail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
			       (status_ref_vs_opt == TI_TEST_KERNEL_FAIL) ||
			       (status_init != MMALIB_SUCCESS) ||
			       (status_opt  != MMALIB_SUCCESS) ||
			       (status_nat  != MMALIB_SUCCESS) ||
			       (comparisonDone == 0) ||
			       (currentTestFail == 1)) ? 1 : 0;

	    fail = ((fail == 1) || (currentTestFail == 1)) ? 1 : 0;

	    pProfile[3*tpi]   = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT);
	    pProfile[3*tpi+1] = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT_WARM);
	    pProfile[3*tpi+2] = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT_WARMWRB);

	    sprintf(desc, "%s | fftSize=%d, batchSize=%d, dataType size=%d",
		    testPatternString, currPrm.fftSize,
		    currPrm.batchSize,
		    MMALIB_sizeof(currPrm.dataType));

	    MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_perfEst(handle,
								   &bufParamsX,
								   &bufParamsY,
								   &bufParamsW,
								   currPrm.fftSize,
								   currPrm.batchSize,
								   currPrm.interleave,
								   &archCycles,
								   &estCycles);

	    TI_profile_add_test(testNum++,
				currPrm.fftSize*currPrm.batchSize,
				archCycles,
				estCycles,
				currentTestFail,
				desc);
	 } else {
	    sprintf(desc, "fftSize=%d, batchSize=%d", currPrm.fftSize, currPrm.batchSize);
	    TI_profile_skip_test(desc);
	 } // end of memory allocation successful?

	 /* Free buffers for each test vector */
	 TI_align_free(pX);
	 TI_align_free(pW);
	 TI_align_free(pY);
	 if (!dataDoubleBuffered) {
	    free(pYCn);
	    free(pTemp);
	 }

      } // end repetitions
   } // end idat test cases

   free(handle);

   return fail;
}

int test_main(uint32_t *pProfile) {
#if !defined(_HOST_BUILD)
   if( TI_cache_init()) {
      TI_memError("MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX");
      return 1;
   } else
#else
      printf("_HOST_BUILD is defined.\n");
#endif
   {
      return MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_d(&pProfile[0],
							      0);
   }
}

/* Main call for individual test projects */
int main()
{
   int fail = 1;

   uint32_t profile[256*3];
   MMALIB_TEST_init();
   fail = test_main(&profile[0]);

#if !defined(NO_PRINTF)
   if(fail == 0)
      printf("Test Pass!\n");
   else
      printf("Test Fail!\n");

   int i;
   for(i = 0; i < test_cases; i++){
      printf("Test %4d: Cold Cycles = %8d, Warm Cycles = %8d, Warm Cycles WRB = %8d\n", i, profile[3*i], profile[3*i+1], profile[3*i+2]);
   }
#endif

      return fail;
}

/* ======================================================================== */
/*  End of file:  MMALIB_FFT_highRadixDecompositions_ixX_cxX_oxX_d.c                          */
/* ======================================================================== */
