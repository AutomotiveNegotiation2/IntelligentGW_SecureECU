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

// include FFTLIB
#include <fftlib.h>

// include test infrastructure provided by FFTLIB
#include "../../test/FFTLIB_test.h"

// include test data for this kernel
#include "FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_idat.h"

__attribute__((section(".msmcData"), aligned(64))) int8_t msmcBuffer[FFTLIB_L3_RESULTS_BUFFER_SIZE];
__attribute__ ((section (".ddrData"), aligned (64))) int8_t ddrBuffer[2048 * 1024];

/* FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_d:  Test Driver Routine */
int FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_d(uint32_t *pProfile, uint8_t LevelOfFeedback)
{
   int32_t  tpi;       /* test parameter index */
   int32_t  currentTestFail;
   int32_t  fail = 0;  /* fail flag */
   uint32_t repCount;  /* number of times to repeat a test; useful for random data and random sizes (set to 1 for static) */
   uint32_t numReps;
   uint32_t testNum;
   
   // variables for calculating performance estimates
   uint64_t archCycles, estCycles;
   int32_t caseNumber;
   
   /* Test Parameters */
   matrixMatrixMultiply_ixX_ixX_oxX_testParams_t   *prm;
   matrixMatrixMultiply_ixX_ixX_oxX_testParams_t   currPrm;
   matrixMatrixMultiply_ixX_ixX_oxX_getTestParams(&prm, &test_cases);
   
   /* Function call parameters */
   FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_InitArgs    kerInitArgs;
   
   /* Initialize profiling */
   TI_profile_init("FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX");
#if ( !defined(RTL_TEST) && !defined(QT_TEST) && !defined(EVM_TEST))
   FILE *fpSummaryCSV = fopen("FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_summary.csv", "w+");
   fprintf(fpSummaryCSV, "Kernel, Bit width, Parameters, Code case, m, k, n, Output memory, Test case, Data pattern, Stride C, Stride A, Stride B, Arch cycles, Loki cycles, Loki/arch cycles, QT cold cycles, QT warm cycles, Ratio of QT cold/arch cycles, Ratio of QT warm/arch cycles, Ratio of QT cold/loki cycles, Ratio of QT warm/loki cycles, Comments\n");
   
   // file IO for Loki benchmarking
   FILE *fpOutputCSV = fopen("FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX.csv", "w+");
   fprintf(fpOutputCSV, "Kernel, Test ID, Requirement Mapping, Data type, signedness C, signedness A,  unsigned B, Stride C, Stride A, Stride B, ReLU_SAT, m, k, n, Output memory, IR, Category, Test Adequacy, Loki cycles\n");
#endif //   #if ( !defined(RTL_TEST) && !defined(QT_TEST) && !defined(EVM_TEST))
   
   /* Run each test case */
   for( tpi=0; tpi < test_cases; tpi++ ) {
      /* Number of repetitions for the test */
      numReps = prm[tpi].numReps;
      testNum = prm[tpi].testID;
      
      currPrm = prm[tpi];
      
      int32_t handleSize = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_getHandleSize(&kerInitArgs);
      FFTLIB_kernelHandle handle = malloc(handleSize);
      
      for(repCount = 0; repCount < numReps; repCount++){
         /* Initialize status flags */
         int32_t      status_nat_vs_opt = TI_TEST_KERNEL_FAIL; /* Test status : Natural c vs. Optimized */
         int32_t      status_ref_vs_opt = TI_TEST_KERNEL_FAIL; /* Test status : Static Reference vs. Optimized */
         FFTLIB_STATUS   status_init = FFTLIB_SUCCESS;
         FFTLIB_STATUS   status_opt = FFTLIB_SUCCESS;
         FFTLIB_STATUS   status_nat = FFTLIB_SUCCESS;
         currentTestFail = 0;
         
         /* Sometimes, depending on certain compile flags, the test will be
          * marked PASS even if no comparison is done. This flag is to detect
          * if a comparison was done or not                                   */
         int32_t      comparisonDone = 0;
         
         /* Special handling for random dimensions */
         if(prm[tpi].testPattern == RANDOM_DIMENSION){
            // set data type to random data
            currPrm.testPattern = RANDOM_SIGNED;
            
            // values provided in prm are considered max values
            uint32_t Mrand = TI_randomDimensionLessThan((uint32_t)prm[tpi].heightIn0);
            uint32_t Krand = TI_randomDimensionLessThan((uint32_t)prm[tpi].widthIn0);
            uint32_t Nrand = TI_randomDimensionLessThan((uint32_t)prm[tpi].widthIn1);
            
            currPrm.heightIn0 = Mrand;
            currPrm.widthIn0  = Krand;
            currPrm.strideIn0 = FFTLIB_CALC_STRIDE(currPrm.widthIn0 * FFTLIB_sizeof(currPrm.dataTypeIn0), FFTLIB_ALIGN_SHIFT_64BYTES);
            
            currPrm.heightIn1 = Krand;
            currPrm.widthIn1  = Nrand;
            currPrm.strideIn1 = FFTLIB_CALC_STRIDE(currPrm.widthIn1 * FFTLIB_sizeof(currPrm.dataTypeIn1), FFTLIB_ALIGN_SHIFT_64BYTES);
            
            currPrm.heightOut = Mrand;
            currPrm.widthOut  = Nrand;
            currPrm.strideOut = FFTLIB_CALC_STRIDE(currPrm.widthOut * FFTLIB_sizeof(currPrm.dataTypeOut), FFTLIB_ALIGN_SHIFT_64BYTES);
         }
         
         /* Compute buffer sizes */
         uint32_t    inp0_size =   currPrm.strideIn0 * currPrm.heightIn0;
         uint32_t    inp1_size =   currPrm.strideIn1 * currPrm.heightIn1;
         uint32_t    outp_size =   currPrm.strideOut * currPrm.heightOut;
         uint32_t    num_pts   =   currPrm.heightIn0 * currPrm.widthIn0 * currPrm.widthIn1;
         
         /* Allocate buffers for each test vector */
         void *src0    =  TI_memalign(FFTLIB_L2DATA_ALIGNMENT, inp0_size); //TI_malloc(inp0_size);
         void *src1    =  TI_memalign(FFTLIB_L2DATA_ALIGNMENT, inp1_size); //TI_malloc(inp1_size);
         
         void * dst;
         dst = NULL;
         if (currPrm.outputDataLocation == FFTLIB_TEST_OUTPUT_HEAP){
            dst        = TI_memalign(FFTLIB_ALIGN_128BYTES, outp_size);
         } else if(currPrm.outputDataLocation == FFTLIB_TEST_OUTPUT_MSMC) {
            dst        = (void *)msmcBuffer;
         } else {
            dst        = (void *)msmcBuffer;
         }
         
#if !defined(PERFORMANCE_TEST)
         void *dst_cn = NULL;
         if (prm[tpi].outputDataLocation == FFTLIB_TEST_OUTPUT_HEAP) {
            dst_cn  =  malloc(outp_size);
         } else {
            dst_cn = (void *) ddrBuffer;
         }
#endif
         
         /* Output shift applied by MMA */
         kerInitArgs.shift = currPrm.shiftOut;
         
         /* Only run the test if the buffer allocations fit in the heap */
#if !defined(PERFORMANCE_TEST)
         if( src0 && src1 && dst && dst_cn )
#else
            if( src0 && src1 && dst )
#endif
            {
               FFTLIB_bufParams2D_t    src0_addr, src1_addr, dst_addr;
               
               /* Fill input arrays according to desired test pattern */
               TI_fillBuffer(currPrm.testPattern,
                             (uint8_t)255,
                             src0, currPrm.staticIn0,
                             currPrm.widthIn0, currPrm.heightIn0, currPrm.strideIn0,
                             FFTLIB_sizeof(currPrm.dataTypeIn0), testPatternString);
               
               // height of second matrix should be same as width of first
               TI_fillBuffer(currPrm.testPattern,
                             (uint8_t)255,
                             src1, currPrm.staticIn1,
                             currPrm.widthIn1, currPrm.heightIn1, currPrm.strideIn1,
                             FFTLIB_sizeof(currPrm.dataTypeIn1), testPatternString);
               
               src0_addr.dim_x = currPrm.widthIn0;
               src0_addr.dim_y = currPrm.heightIn0;
               src0_addr.stride_y = currPrm.strideIn0;
               src0_addr.data_type = currPrm.dataTypeIn0;
               
               src1_addr.dim_x = currPrm.widthIn1;
               src1_addr.dim_y = currPrm.heightIn1;
               src1_addr.stride_y = currPrm.strideIn1;
               src1_addr.data_type = currPrm.dataTypeIn1;
               
               dst_addr.dim_x = currPrm.widthOut;
               dst_addr.dim_y = currPrm.heightOut;
               dst_addr.stride_y = currPrm.strideOut;
               dst_addr.data_type = currPrm.dataTypeOut;
               
               /* Initialize kernel */
               status_init = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_init_checkParams(handle, &src0_addr, &src1_addr, &dst_addr, &kerInitArgs);
#if !defined(FFTLIB_SKIP_CI)
               if(status_init == FFTLIB_SUCCESS){
                  TI_profile_start(TI_PROFILE_KERNEL_INIT);
                  FFTLIB_asm(" MARK 0");
                  kerInitArgs.funcStyle = FFTLIB_FUNCTION_OPTIMIZED;
                  status_init = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_init(handle,
                                                                                    &src0_addr,
                                                                                    &src1_addr,
                                                                                    &dst_addr,
                                                                                    &kerInitArgs);
                  FFTLIB_asm(" MARK 1");
                  TI_profile_stop();
               }
               
               /* Test optimized kernel */
               status_opt = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_exec_checkParams(handle, src0, src1, dst);
               if(status_opt == FFTLIB_SUCCESS){
                  TI_profile_start(TI_PROFILE_KERNEL_OPT);
                  FFTLIB_asm(" MARK 2");
                  status_opt = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_exec(handle, src0, src1, dst);
                  FFTLIB_asm(" MARK 3");
                  TI_profile_stop();
               }
#if (defined(RTL_TEST) || defined(QT_TEST) || defined(EVM_TEST) )
               // run warm instruction cache test
               TI_profile_start(TI_PROFILE_KERNEL_OPT_WARM);
               FFTLIB_asm(" MARK 4");
               status_opt = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_exec(handle,
                                                                                src0,
                                                                                src1,
                                                                                dst);
               FFTLIB_asm(" MARK 5");
               TI_profile_stop();
               
               // get output to L1D
               int32_t row, col;
               int16_t outSum = 0;
               int16_t volatile volatileSum = 0;  // use volatile to keep compiler from removing this operation
               int8_t *pDst = (int8_t *)dst;       // treat output as bytes to be data type agnostic
               for(row = 0; row < dst_addr.dim_y; row++)
               {
                  for(col = 0; col < dst_addr.stride_y; col++)
                  {
                     outSum += *pDst;
                     pDst++;
                  }
               }
               
               // dummy store of outSum to insure that the compiler does not remove it.
               volatileSum = outSum;
               
               // run warm instruction cache test
               TI_profile_start(TI_PROFILE_KERNEL_OPT_WARMWRB);
               FFTLIB_asm(" MARK 6");
               status_opt = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_exec(handle,
                                                                                src0,
                                                                                src1,
                                                                                dst);
               FFTLIB_asm(" MARK 7");
               TI_profile_stop();
#endif
#endif // #if !defined(FFTLIB_SKIP_CI)
               
#if !defined(RTL_TEST) && !defined(PERFORMANCE_TEST) && !defined(FFTLIB_SKIP_CN)
               /* Test _cn kernel */
               kerInitArgs.funcStyle = FFTLIB_FUNCTION_NATC;
               
               // initialize the kernel to use the natural C variant
               FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_init(handle,
                                                                   &src0_addr,
                                                                   &src1_addr,
                                                                   &dst_addr,
                                                                   &kerInitArgs);
               
               TI_profile_start(TI_PROFILE_KERNEL_CN);
               FFTLIB_asm(" MARK 8");
               status_nat = FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_exec(handle,
                                                                                src0,
                                                                                src1,
                                                                                dst_cn);
               FFTLIB_asm(" MARK 9");
               TI_profile_stop();
               
               /* Compare natural C Output and Optimized Output */
               status_nat_vs_opt = TI_compare_mem_2D(dst, dst_cn, 0, 0, currPrm.widthOut, currPrm.heightOut, currPrm.strideOut, FFTLIB_sizeof(dst_addr.data_type));
               comparisonDone = 1;
#else
               /* Set to pass since it wasn't supposed to run. */
               status_nat_vs_opt = TI_TEST_KERNEL_PASS;
#endif // !defined(RTL_TEST) && !defined(PERFORMANCE_TEST)
               
               
               /* If static output is available, then additionally compares optimized C output with static reference output data */
               if( currPrm.staticOut != NULL ) {
                  status_ref_vs_opt = TI_compare_mem_roi2DStatic((void *) dst, (void *) currPrm.staticOut, 0, 0, currPrm.widthOut, currPrm.heightOut, currPrm.strideOut, FFTLIB_sizeof(dst_addr.data_type));
                  comparisonDone = 1;
               } else {
                  /* Set to pass since it wasn't supposed to run. */
                  status_ref_vs_opt = TI_TEST_KERNEL_PASS;
               }
               
               /* Set the 'fail' flag based on test vector comparison results */
               currentTestFail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                                  (status_ref_vs_opt == TI_TEST_KERNEL_FAIL) ||
                                  (status_init != FFTLIB_SUCCESS) ||
                                  (status_opt  != FFTLIB_SUCCESS) ||
                                  (status_nat  != FFTLIB_SUCCESS) ||
                                  (comparisonDone == 0) ||
                                  (currentTestFail == 1)) ? 1 : 0;
               
               fail = ((fail == 1) || (currentTestFail == 1)) ? 1 : 0;
               
#if FFTLIB_DEBUGPRINT
               printf("%s: status_nat_vs_opt = %d\n", __FUNCTION__, status_nat_vs_opt);
               printf("%s: status_ref_vs_opt = %d\n", __FUNCTION__, status_ref_vs_opt);
               printf("%s: status_init       = %d\n", __FUNCTION__, status_init);
               printf("%s: status_opt        = %d\n", __FUNCTION__, status_opt);
               printf("%s: status_nat        = %d\n", __FUNCTION__, status_nat);
               printf("%s: comparison done   = %d\n", __FUNCTION__, comparisonDone);
#endif
               
               pProfile[3*tpi]   = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT);
               pProfile[3*tpi+1] = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT_WARM);
               pProfile[3*tpi+2] = (int32_t)TI_profile_get_cycles(TI_PROFILE_KERNEL_OPT_WARMWRB);
#if defined(QT_TEST)
               __ESTP_GS         = pProfile[3*tpi];
               __FSR             = pProfile[3*tpi+1];
               __ESTP_S          = pProfile[3*tpi+2];
               __GPLY            = !fail;
               __DBGCTXT         = testNum;
#endif // QT_TEST
               
#if !defined(RTL_TEST)
               /* Profile display and preparation for cycle estimation */
               sprintf(desc, "%s generated input | dataType=%d, m=%d, k=%d, n=%d",
                       testPatternString, dst_addr.data_type, currPrm.heightIn0, currPrm.widthIn0, currPrm.widthIn1);
               
               FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_perfEst(handle, &src0_addr, &src1_addr, &dst_addr, &archCycles, &estCycles, &caseNumber);
               
#if ( !defined(RTL_TEST) && !defined(QT_TEST) && !defined(EVM_TEST))
               // write to CSV, must happen prior to write to screen because TI_profile_formula_add clears values in counters
               fprintf(fpSummaryCSV, "%s, %d, %dx%dx%d, Case %d, %d, %d, %d, %s, %d,%s,%d,%d,%d,%lu ,%lu ,%.2f , , , , , , , , \n",
                       "Matrix matrix multiply",
                       8*FFTLIB_sizeof(dst_addr.data_type),
                       currPrm.heightIn0, currPrm.widthIn0, currPrm.widthIn1,
                       caseNumber,
                       currPrm.heightIn0,
                       currPrm.widthIn0,
                       currPrm.widthIn1,
                       currPrm.outputDataLocation == FFTLIB_TEST_OUTPUT_HEAP ? "HEAP" : "MSMC",
                       testNum,
                       testPatternString,
                       currPrm.strideOut,
                       currPrm.strideIn0,
                       currPrm.strideIn1,
                       archCycles,
                       cycles[TI_PROFILE_KERNEL_OPT],
                       (double)(cycles[TI_PROFILE_KERNEL_OPT])/archCycles);
               
               fprintf(fpOutputCSV, "%s, %s%04u, , %d, %s, %s, %s, %d, %d, %d, %s, ",
                       "FFTLIB_LINALG_matrixMatrixMultiply",
                       "FFTLIB_LINALG_matrixMatrixMultiply", testNum,
                       8*FFTLIB_sizeof(dst_addr.data_type),
                       FFTLIB_SIGNEDNESS(dst_addr.data_type),
                       FFTLIB_SIGNEDNESS(src0_addr.data_type),
                       FFTLIB_SIGNEDNESS(src1_addr.data_type),
                       currPrm.strideOut,
                       currPrm.strideIn0,
                       currPrm.strideIn1,
                       "SAT");
               fprintf(fpOutputCSV, "%u, %u, %u, %s, %s, %s, %s, %lu\n",
                       currPrm.heightIn0,  // m
                       currPrm.widthIn0,   // k
                       currPrm.widthIn1,   // n
                       currPrm.outputDataLocation == FFTLIB_TEST_OUTPUT_HEAP ? "HEAP" : "MSMC",
                       " ",                // IR
                       testPatternString,  // category
                       " ",                // test adequacy
                       cycles[TI_PROFILE_KERNEL_OPT]); // loki cycles
#endif // #if ( !defined(RTL_TEST) && !defined(QT_TEST) && !defined(EVM_TEST))
               
               TI_profile_add_test(testNum++, num_pts, archCycles, estCycles, currentTestFail, desc);
               
#if FFTLIB_DEBUGPRINT
               if(currentTestFail){
                  printf("\nA is: \n");
                  FFTLIB_debugPrintMatrix(src0, &src0_addr);
                  printf("B is: \n");
                  FFTLIB_debugPrintMatrix(src1, &src1_addr);
#if !defined(PERFORMANCE_TEST)
                  printf("\nThe natural-c output is: \n");
                  FFTLIB_debugPrintMatrix(dst_cn, &dst_addr);
#endif
                  printf("The computed output is: \n");
                  FFTLIB_debugPrintMatrix(dst, &dst_addr);
               }
#endif
            } else {
               /* Display the error printout for this test vector before moving on to the next test vector */
               sprintf(desc, "m=%d, k=%d, n=%d",
                       currPrm.heightIn0, currPrm.widthIn0, currPrm.widthIn1);
               TI_profile_skip_test(desc);
#else
               // clear the counters between runs; normally handled by TI_profile_add_test
               TI_profile_clear_run_stats ();
#endif
            } // end of memory allocation successful?
         
         /* Free buffers for each test vector */
#if !defined(PERFORMANCE_TEST)
         if (prm[tpi].outputDataLocation == FFTLIB_TEST_OUTPUT_HEAP) {
            free(dst_cn);
         } else {}
#endif
         if (currPrm.outputDataLocation == FFTLIB_TEST_OUTPUT_HEAP){
            // only malloc'd data can be freed
            TI_align_free(dst);
         }
         
         TI_align_free(src1);
         TI_align_free(src0);
         
#if defined(RTL_TEST)
         // for RTL testing, request to return after first fail
         if(fail){
            free(handle);
            return fail;
         }
#endif
      } // end repetitions
      free(handle);
   } // end idat test cases
   
   
   /* Provide memory requirements */
#if ( !defined(RTL_TEST) && !defined(QT_TEST) && !defined(EVM_TEST))
   /* Close results CSV */
   fclose(fpOutputCSV);
#endif //#if ( !defined(RTL_TEST) && !defined(QT_TEST) && !defined(EVM_TEST))
   
   return fail;
}

int test_main(uint32_t *pProfile) {
#if !defined(_HOST_BUILD)
   if( TI_cache_init()) {
      TI_memError("FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX");
      return 1;
   } else
#else
      printf("_HOST_BUILD is defined.\n");
#endif //_HOST_BUILD
   {
      return FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_d(&pProfile[0], 0);
   }
}

/* Main call for individual test projects */
#if !defined(__ONESHOTTEST) && !defined(RTL_TEST)
int main()
{
   int fail = 1;
   
   uint32_t profile[256*3];
   
   FFTLIB_TEST_init();
   
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
#endif

/* ======================================================================== */
/*  End of file:  FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_d.c                          */
/* ======================================================================== */
