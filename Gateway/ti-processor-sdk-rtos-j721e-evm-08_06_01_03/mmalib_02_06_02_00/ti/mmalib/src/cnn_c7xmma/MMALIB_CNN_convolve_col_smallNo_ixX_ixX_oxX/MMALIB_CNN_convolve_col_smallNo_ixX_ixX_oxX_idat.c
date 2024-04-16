/******************************************************************************
 *                                                                             *
 * module name       :MMALIB                                                   *
 *                                                                             *
 * module descripton :Matrix Multiply Accelerator Library module for C7x+MMA   *
 *                                                                             *
 * Copyright (C) 2017-2018 Texas Instruments Incorporated - http://www.ti.com/ *
 * ALL RIGHTS RESERVED                                                         *
 *                                                                             *
 ******************************************************************************/

/**
 ******************************************************************************
 *  @file     MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat.c
 *
 *  @brief    File to have static test data related content
 *
 *  @version  0.1 - Feb 2018 : Initial Version
 *
 *******************************************************************************
 */

#include "MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat.h"

#if ((TEST_CASE == 1000) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1000.h"
#endif
#if ((TEST_CASE == 1001) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1001.h"
#endif
#if ((TEST_CASE == 1002) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1002.h"
#endif
#if ((TEST_CASE == 1003) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1003.h"
#endif
#if ((TEST_CASE == 1004) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1004.h"
#endif
#if ((TEST_CASE == 1005) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1005.h"
#endif
#if ((TEST_CASE == 1006) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1006.h"
#endif
#if ((TEST_CASE == 1007) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1007.h"
#endif
#if ((TEST_CASE == 1008) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1008.h"
#endif
#if ((TEST_CASE == 1009) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1009.h"
#endif
#if ((TEST_CASE == 1010) || (TEST_CATEGORY == 1000))
#include "test_data/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat_testcase1010.h"
#endif

/**********************************************************************************************************************/
static convolve_col_smallNo_ixX_ixX_oxX_testParams_t testParams[] =
{
   
#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1000))
   {
      STATIC,      /* testPattern */
      staticRefKernel_test1000,
      NULL,
      staticRefIn_test1000,
      NULL,
      NULL,
      staticRefOut_test1000,
      NULL,
      NULL,
      3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      256, //Lc;
      256, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      1, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1000, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1001))
   {
      STATIC,      /* testPattern */
      staticRefKernel_test1001,
      NULL,
      staticRefIn_test1001,
      NULL,
      NULL,
      staticRefOut_test1001,
      NULL,
      NULL,
      5, //kernelWidth;
      5, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      256, //Lc;
      256, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      1, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1001, //testID;
   }              ,
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1002))
   {
      STATIC,      /* testPattern */
      staticRefKernel_test1002,
      NULL,
      staticRefIn_test1002,
      NULL,
      NULL,
      staticRefOut_test1002,
      NULL,
      NULL,
      7, //kernelWidth;
      7, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      256, //Lc;
      256, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      1, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1002, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1003))
   {
      STATIC,      /* testPattern */
         staticRefKernel_test1003,
         NULL,
         staticRefIn_test1003,
         NULL,
         NULL,
         staticRefOut_test1003,
         NULL,
         NULL,
         3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      128, //Lc;
      256, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      1, //numGroupsPerKernel;
      8, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_RELU, //activationType;
      MMALIB_INT16, //dataTypeA;
      MMALIB_INT16, //dataTypeB;
      MMALIB_INT16, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1003, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1004))
   {
      STATIC,      /* testPattern */
      staticRefKernel_test1004,
      NULL,
      staticRefIn_test1004,
      NULL,
      NULL,
      staticRefOut_test1004,
      NULL,
      NULL,
      3, //kernelWidth;
      3, //kernelHeight;
      2, //strideX;
      2, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      384, //Lc;
      384, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      1, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_RELU, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1004, //testID;
   },
#endif
#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1005))
   {
      STATIC,      /* testPattern */
         staticRefKernel_test1005,
         NULL,
         staticRefIn_test1005,
         NULL,
         NULL,
         staticRefOut_test1005,
         NULL,
         NULL,
         3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      256, //Lc;
      128, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      2, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_RELU, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1005, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1006))
   {
      STATIC,      /* testPattern */
      staticRefKernel_test1006,
      NULL,
      staticRefIn_test1006,
      NULL,
      NULL,
      staticRefOut_test1006,
      NULL,
      NULL,
      3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      128, //Lc;
      256, //Lr;
      2, //numInChannels;
      2, //numOutChannels;
      1, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_RELU, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1006, //testID;
   },
#endif
#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1007))
   {
      STATIC,      /* testPattern */
         staticRefKernel_test1007,
         NULL,
         staticRefIn_test1007,
         NULL,
         NULL,
         staticRefOut_test1007,
         NULL,
         NULL,
         3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      64, //Lc;
      1024, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      1, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1007, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1008))
   {
      STATIC,      /* testPattern */
         staticRefKernel_test1008,
         NULL,
         staticRefIn_test1008,
         NULL,
         NULL,
         staticRefOut_test1008,
         NULL,
         NULL,
         3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      64, //Lc;
      128, //Lr;
      1, //numInChannels;
      1, //numOutChannels;
      4, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1008, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1009))
   {
      STATIC,      /* testPattern */
         staticRefKernel_test1009,
         NULL,
         staticRefIn_test1009,
         NULL,
         NULL,
         staticRefOut_test1009,
         NULL,
         NULL,
         3, //kernelWidth;
      3, //kernelHeight;
      1, //strideX;
      1, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      128, //Lc;
      64, //Lr;
      2, //numInChannels;
      2, //numOutChannels;
      4, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1009, //testID;
   },
#endif

#if (defined(ALL_TEST_CASES) || (TEST_CATEGORY == 1000) || (TEST_CASE == 1010))
   {
      STATIC,      /* testPattern */
         staticRefKernel_test1010,
         NULL,
         staticRefIn_test1010,
         NULL,
         NULL,
         staticRefOut_test1010,
         NULL,
         NULL,
         3, //kernelWidth;
      3, //kernelHeight;
      2, //strideX;
      2, //strideY;
      1, //dilationHeight;
      1, //dilationWidth;
      128, //Lc;
      128, //Lr;
      4, //numInChannels;
      4, //numOutChannels;
      2, //numGroupsPerKernel;
      4, //qShift;
      MMALIB_CONVOLVE_COL_SHIFT_SINGLE, //shiftMethod;
      1, //biasB;
      1, //numBiasVals;
      MMALIB_SATURATION, //activationType;
      MMALIB_INT8, //dataTypeA;
      MMALIB_INT8, //dataTypeB;
      MMALIB_INT8, //dataTypeC;
      MMALIB_TEST_OUTPUT_MSMC, //outputDataLocation;
      1, //repetitions;
      1010, //testID;
   },
#endif

};  // do not delete this brace!


void convolve_col_smallNo_ixX_ixX_oxX_getTestParams(convolve_col_smallNo_ixX_ixX_oxX_testParams_t * *params, int32_t *numTests) {
   *params   = testParams;
   *numTests = sizeof(testParams) / sizeof(convolve_col_smallNo_ixX_ixX_oxX_testParams_t);
}


/* ======================================================================== */
/*  End of file:  MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX_idat.c        */
/* ======================================================================== */
