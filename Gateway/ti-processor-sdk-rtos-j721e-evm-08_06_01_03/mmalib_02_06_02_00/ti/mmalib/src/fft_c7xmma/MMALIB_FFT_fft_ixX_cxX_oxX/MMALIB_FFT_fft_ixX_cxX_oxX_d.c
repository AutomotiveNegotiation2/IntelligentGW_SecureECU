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
#include "MMALIB_FFT_fft_ixX_cxX_oxX_idat.h"


__attribute__ ((section (".ddrData"), aligned (64))) int8_t ddrBuffer[2048 * 1024];
int16_t volatile volatileSum = 0;  // use volatile to keep compiler from removing this operation

int MMALIB_FFT_fft_ixX_cxX_oxX_d(
   uint32_t *pProfile,
   uint8_t LevelOfFeedback)
{
   int32_t  tpi;
   int32_t  currentTestFail;
   int32_t  fail = 0;
   uint32_t  repCount;
   uint32_t numReps;
   MMALIB_bufParams1D_t bufParamsX, bufParamsY, bufParamsW;
   int32_t k;
   uint32_t testNum;

   fft_ixX_cxX_oxX_testParams_t   *prm;
   fft_ixX_cxX_oxX_testParams_t   currPrm;
   fft_ixX_cxX_oxX_getTestParams(&prm, &test_cases);

   MMALIB_FFT_fft_ixX_cxX_oxX_InitArgs    kerInitArgs;

   int32_t handleSize = MMALIB_FFT_fft_ixX_cxX_oxX_getHandleSize(&kerInitArgs);
   MMALIB_kernelHandle handle = malloc(handleSize);

   TI_profile_init("MMALIB_FFT_fft_ixX_cxX_oxX");

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
	 currentTestFail = 0;

	 kerInitArgs.fftSize = currPrm.fftSize;
	 kerInitArgs.batchSize = currPrm.batchSize;
	 for (k = 0; k < MMALIB_FFT_FFT_IXX_CXX_OXX_NUMSHIFTS; k++) {
	     kerInitArgs.shiftVector[k] = currPrm.shiftVector[k];
	 }
	 kerInitArgs.interleave = currPrm.interleave;
	 bufParamsX.data_type = currPrm.dataType;
	 bufParamsY.data_type = currPrm.dataType;;
	 bufParamsW.data_type = currPrm.dataType;;
	 MMALIB_FFT_fft_ixX_cxX_oxX_getSizes(&kerInitArgs,
					     &bufParamsX,
					     &bufParamsW,
					     &bufParamsY);

	 void *pX   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsX.dim_x*MMALIB_sizeof(currPrm.dataType));
	 void *pW   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsW.dim_x*MMALIB_sizeof(currPrm.dataType));
	 void *pY   = (void *) TI_memalign(MMALIB_L2DATA_ALIGNMENT, bufParamsY.dim_x*MMALIB_sizeof(currPrm.dataType));
//	 void *pYCn = (void *) malloc(bufParamsX.dim_x*MMALIB_sizeof(currPrm.dataType));
	 void *pYCn = (void *) ddrBuffer;

	 /* Only run the test if the buffer allocations fit in the heap */
	 if( pX && pW && pY && pYCn ) {

	    TI_fillBuffer(prm[tpi].testPattern,
			  0,
			  pX,
			  prm[tpi].staticIn,
			  currPrm.batchSize*currPrm.fftSize*2,
			  1,
			  currPrm.batchSize*currPrm.fftSize*2*MMALIB_sizeof(currPrm.dataType),
			  MMALIB_sizeof(currPrm.dataType),
			  testPatternString);

	    MMALIB_FFT_fft_ixX_cxX_oxX_twGen(&kerInitArgs,
					     pW,
					     &bufParamsW);

	    status_init = MMALIB_FFT_fft_ixX_cxX_oxX_init_checkParams(handle,
								      &bufParamsX,
								      &bufParamsW,
								      &bufParamsY,
								      &kerInitArgs);
	    if (status_init == MMALIB_SUCCESS) {
	       TI_profile_start(TI_PROFILE_KERNEL_INIT);
	       MMALIB_asm(" MARK 0");
	       kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
	       status_init = MMALIB_FFT_fft_ixX_cxX_oxX_init(handle,
							     &bufParamsX,
							     &bufParamsW,
							     &bufParamsY,
							     &kerInitArgs);
	       MMALIB_asm(" MARK 1");
	       TI_profile_stop();
	    }

	    status_opt = MMALIB_FFT_fft_ixX_cxX_oxX_exec_checkParams(handle,
								     pX,
								     pW,
								     pY);
	    if(status_opt == MMALIB_SUCCESS){
	       TI_profile_start(TI_PROFILE_KERNEL_OPT);
	       MMALIB_asm(" MARK 2");
	       status_opt = MMALIB_FFT_fft_ixX_cxX_oxX_exec(handle,
							    pX,
							    pW,
							    pY);
	       MMALIB_asm(" MARK 3");
	       TI_profile_stop();
	    }
	    TI_fillBuffer(prm[tpi].testPattern,
			  0,
			  pX,
			  prm[tpi].staticIn,
			  currPrm.batchSize*currPrm.fftSize*2,
			  1,
			  currPrm.batchSize*currPrm.fftSize*2*MMALIB_sizeof(currPrm.dataType),
			  MMALIB_sizeof(currPrm.dataType),
			  testPatternString);

	    // run warm instruction cache test
	    TI_profile_start(TI_PROFILE_KERNEL_OPT_WARM);
	    MMALIB_asm(" MARK 4");
	    status_opt = MMALIB_FFT_fft_ixX_cxX_oxX_exec(handle,
							 pX,
							 pW,
							 pY);
	    MMALIB_asm(" MARK 5");
	    TI_profile_stop();

	    // get output to L1D
	    uint32_t k;
	    int16_t outSum = 0;
	    int8_t *pYTemp = (int8_t *)pY;       // treat output as bytes to be data type agnostic
	    for (k = 0; k < currPrm.fftSize*currPrm.batchSize*2; k++) {
		outSum += *pYTemp;
		pYTemp++;
	    }

	    // dummy store of outSum to insure that the compiler does not remove it.
	    volatileSum = outSum;

	    TI_fillBuffer(prm[tpi].testPattern,
			  0,
			  pX,
			  prm[tpi].staticIn,
			  currPrm.batchSize*currPrm.fftSize*2,
			  1,
			  currPrm.batchSize*currPrm.fftSize*2*MMALIB_sizeof(currPrm.dataType),
			  MMALIB_sizeof(currPrm.dataType),
			  testPatternString);

	    // run warm instruction cache test
	    TI_profile_start(TI_PROFILE_KERNEL_OPT_WARMWRB);
	    MMALIB_asm(" MARK 6");
	    status_opt = MMALIB_FFT_fft_ixX_cxX_oxX_exec(handle,
							 pX,
							 pW,
							 pY);
	    MMALIB_asm(" MARK 7");
	    TI_profile_stop();

	    /* Test _cn kernel */
	    kerInitArgs.funcStyle = MMALIB_FUNCTION_NATC;

	    TI_fillBuffer(prm[tpi].testPattern,
			  0,
			  pX,
			  prm[tpi].staticIn,
			  currPrm.batchSize*currPrm.fftSize*2,
			  1,
			  currPrm.batchSize*currPrm.fftSize*2*MMALIB_sizeof(currPrm.dataType),
			  MMALIB_sizeof(currPrm.dataType),
			  testPatternString);

	    // initialize the kernel to use the natural C variant
	    MMALIB_FFT_fft_ixX_cxX_oxX_init(handle,
					    &bufParamsX,
					    &bufParamsW,
					    &bufParamsY,
					    &kerInitArgs);

	    TI_profile_start(TI_PROFILE_KERNEL_CN);
	    MMALIB_asm(" MARK 8");
	    status_nat = MMALIB_FFT_fft_ixX_cxX_oxX_exec(handle,
							 pX,
							 pW,
							 pYCn);
	    MMALIB_asm(" MARK 9");
	    TI_profile_stop();

	    status_nat_vs_opt = TI_compare_mem_2D((void *)pY,
						  (void *)pYCn,
						  50,
						  65535,
						  currPrm.batchSize*currPrm.fftSize*2,
						  1,
						  currPrm.batchSize*currPrm.fftSize*2*MMALIB_sizeof(bufParamsY.data_type),
						  MMALIB_sizeof(bufParamsY.data_type));

	    if( currPrm.staticOut != NULL ) {
		status_ref_vs_opt = TI_compare_mem_2D((void *)currPrm.staticOut,
						      (void *)pY,
						      50,
						      65535,
						      currPrm.batchSize*currPrm.fftSize*2,
						      1,
						      currPrm.batchSize*currPrm.fftSize*2*MMALIB_sizeof(bufParamsY.data_type),
						      MMALIB_sizeof(bufParamsY.data_type));
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
			       (currentTestFail == 1)) ? 1 : 0;

	    fail = ((fail == 1) || (currentTestFail == 1)) ? 1 : 0;

	    pProfile[3*tpi]   = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT);
	    pProfile[3*tpi+1] = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT_WARM);
	    pProfile[3*tpi+2] = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT_WARMWRB);

	    sprintf(desc, "%s generated input | fftSize=%d, batchSize=%d",
		    testPatternString, currPrm.fftSize, currPrm.batchSize);
	    TI_profile_add_test(testNum++,
				currPrm.fftSize*currPrm.batchSize,
				1, // this is a wrapper kernel, no estimation done for this
				1, // this is a wrapper kernel, no estimation done for this
				currentTestFail,
				desc);
	 } else {
	    sprintf(desc, "fftSize=%d, batchSize=%d", currPrm.fftSize, currPrm.batchSize);
	    TI_profile_skip_test(desc);
	 } // end of memory allocation successful?

	 /* Free buffers for each test vector */
//	 free(pYCn);
	 TI_align_free(pX);
	 TI_align_free(pW);
	 TI_align_free(pY);

      } // end repetitions
   } // end idat test cases

   free(handle);

   return fail;
}

int test_main(uint32_t *pProfile) {
#if !defined(_HOST_BUILD)
   if( TI_cache_init()) {
      TI_memError("MMALIB_FFT_fft_ixX_cxX_oxX");
      return 1;
   } else
#else
      printf("_HOST_BUILD is defined.\n");
#endif
   {
      return MMALIB_FFT_fft_ixX_cxX_oxX_d(&pProfile[0],
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
/*  End of file:  MMALIB_FFT_fft_ixX_cxX_oxX_d.c                          */
/* ======================================================================== */
