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
*  @file     MMALIB_CNN_deconvolve_row_ixX_ixX_oxX_idat.c
*
*  @brief    File to have static test data related content
*
*  @version  0.1 - Jan 2018 : Initial Version - Template [PKS]
*
*******************************************************************************
*/

#include "MMALIB_CNN_deconvolve_row_ixX_ixX_oxX_idat.h"

#if ((TEST_CASE == 0) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase0_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 3) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase3_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 13) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase13_i8s_i8s_o8s.h"
#endif

#if ((TEST_CASE == 44) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase44_i8s_i8s_o8s.h"
#endif


#if ((TEST_CASE == 5001) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase5001_i16s_i16s_o16s.h"
#endif

#if ((TEST_CASE == 5003) || (TEST_CATEGORY == 1000))
#include "test_data/staticRefCaseCase5003_i16s_i16s_o16s.h"
#endif



static deconvolve_row_ixX_ixX_oxX_testParams_t testParams[] = {
#if ((TEST_CASE == 0) || (TEST_CATEGORY == 1000))
    {
        STATIC, // testPattern
        staticRefInputXCaseCase0_i8s_i8s_o8s,
        staticRefInputHCaseCase0_i8s_i8s_o8s,
        staticRefOutputYMMALIBCaseCase0_i8s_i8s_o8s,
        staticRefOutputYCaseCase0_i8s_i8s_o8s,
        NULL,
        NULL,
        NULL,
        NULL,
        4,                 // kernelWidth
        4,                 // kernelHeight
        2,                 // strideWidth
        2,                 // strideHeight
        1,                 // dilationHeight
        1,                 // dilationWidth
        68,                // inWidth
        1,                 // pad
        8,                 // maxHeight
        448,               // inChoffset
        414,               // validColsIn
        261,               // kDim
        320,               // pitchA
        1,                 // numOfOutputChKerBuf
        1768,              // pitchC
        1,                 // subMChannels
        64,                // numInChannels
        1,                 // numOutChannels
        1,                 // numGroups
        9,                 // qShift
        12,                // biasB
        MMALIB_SATURATION, // activationType
        MMALIB_INT8,       // dataTypeA
        MMALIB_INT8,       // dataTypeB
        MMALIB_INT8,       // dataTypeC
        0,                 // mode
        0,                 // circularOffset
        1,                 // totalN
        1,                 // subN
        0,                 // validColsPerRowIn
        0,                 // ValidRowsIn
        0,                 // outputPitchPerRow
        0,                 // inputPitchPerRow
        MMALIB_TEST_OUTPUT_MSMC,
        0, // preProcessFlag
        0,
    },
#endif

#if ((TEST_CASE == 3) || (TEST_CATEGORY == 1000))
    {
        STATIC, // testPattern
        staticRefInputXCaseCase3_i8s_i8s_o8s,
        staticRefInputHCaseCase3_i8s_i8s_o8s,
        staticRefOutputYMMALIBCaseCase3_i8s_i8s_o8s,
        staticRefOutputYCaseCase3_i8s_i8s_o8s,
        NULL,
        NULL,
        NULL,
        NULL,
        4,                 // kernelWidth
        4,                 // kernelHeight
        2,                 // strideWidth
        2,                 // strideHeight
        1,                 // dilationHeight
        1,                 // dilationWidth
        68,                // inWidth
        1,                 // pad
        8,                 // maxHeight
        448,               // inChoffset
        414,               // validColsIn
        9,                 // kDim
        320,               // pitchA
        1,                 // numOfOutputChKerBuf
        1768,              // pitchC
        1,                 // subMChannels
        1,                 // numInChannels
        1,                 // numOutChannels
        1,                 // numGroups
        9,                 // qShift
        12,                // biasB
        MMALIB_SATURATION, // activationType
        MMALIB_INT8,       // dataTypeA
        MMALIB_INT8,       // dataTypeB
        MMALIB_INT8,       // dataTypeC
        0,                 // mode
        0,                 // circularOffset
        1,                 // totalN
        1,                 // subN
        0,                 // validColsPerRowIn
        0,                 // ValidRowsIn
        0,                 // outputPitchPerRow
        0,                 // inputPitchPerRow
        MMALIB_TEST_OUTPUT_MSMC,
        0, // preProcessFlag
        3,
    },
#endif

#if ((TEST_CASE == 13) || (TEST_CATEGORY == 1000))
    {
        STATIC, // testPattern
        staticRefInputXCaseCase13_i8s_i8s_o8s,
        staticRefInputHCaseCase13_i8s_i8s_o8s,
        staticRefOutputYMMALIBCaseCase13_i8s_i8s_o8s,
        staticRefOutputYCaseCase13_i8s_i8s_o8s,
        NULL,
        NULL,
        NULL,
        NULL,
        2,                 // kernelWidth
        2,                 // kernelHeight
        2,                 // strideWidth
        2,                 // strideHeight
        1,                 // dilationHeight
        1,                 // dilationWidth
        64,                // inWidth
        0,                 // pad
        8,                 // maxHeight
        448,               // inChoffset
        256,               // validColsIn
        69,                // kDim
        320,               // pitchA
        64,                // numOfOutputChKerBuf
        1768,              // pitchC
        64,                // subMChannels
        64,                // numInChannels
        64,                // numOutChannels
        1,                 // numGroups
        9,                 // qShift
        12,                // biasB
        MMALIB_SATURATION, // activationType
        MMALIB_INT8,       // dataTypeA
        MMALIB_INT8,       // dataTypeB
        MMALIB_INT8,       // dataTypeC
        0,                 // mode
        0,                 // circularOffset
        1,                 // totalN
        1,                 // subN
        0,                 // validColsPerRowIn
        0,                 // ValidRowsIn
        0,                 // outputPitchPerRow
        0,                 // inputPitchPerRow
        MMALIB_TEST_OUTPUT_MSMC,
        0, // preProcessFlag
        13,
    },
#endif


#if ((TEST_CASE == 44) || (TEST_CATEGORY == 1000))
    {
        STATIC, // testPattern
        staticRefInputXCaseCase44_i8s_i8s_o8s,
        staticRefInputHCaseCase44_i8s_i8s_o8s,
        staticRefOutputYMMALIBCaseCase44_i8s_i8s_o8s,
        staticRefOutputYCaseCase44_i8s_i8s_o8s,
        NULL,
        NULL,
        NULL,
        NULL,
        8,                 // kernelWidth
        8,                 // kernelHeight
        2,                 // strideWidth
        2,                 // strideHeight
        1,                 // dilationHeight
        1,                 // dilationWidth
        64,                // inWidth
        2,                 // pad
        8,                 // maxHeight
        1024,              // inChoffset
        528,               // validColsIn
        69,                // kDim
        1152,              // pitchA
        2,                 // numOfOutputChKerBuf
        2304,              // pitchC
        2,                 // subMChannels
        4,                 // numInChannels
        2,                 // numOutChannels
        1,                 // numGroups
        9,                 // qShift
        12,                // biasB
        MMALIB_SATURATION, // activationType
        MMALIB_INT8,       // dataTypeA
        MMALIB_INT8,       // dataTypeB
        MMALIB_INT8,       // dataTypeC
        0,                 // mode
        0,                 // circularOffset
        1,                 // totalN
        1,                 // subN
        0,                 // validColsPerRowIn
        0,                 // ValidRowsIn
        0,                 // outputPitchPerRow
        0,                 // inputPitchPerRow
        MMALIB_TEST_OUTPUT_MSMC,
        1, // preProcessFlag
        44,
    },
#endif


/* #if !defined(__RESERVED__) */


/* #endif */

/* #if !defined(__RESERVED__) */
/* #endif */

#if ((TEST_CASE == 5001) || (TEST_CATEGORY == 1000))
    {
        STATIC, // testPattern
        NULL,
        NULL,
        NULL,
        NULL,
        staticRefInputXCaseCase5001_i16s_i16s_o16s,
        staticRefInputHCaseCase5001_i16s_i16s_o16s,
        staticRefOutputYMMALIBCaseCase5001_i16s_i16s_o16s,
        staticRefOutputYCaseCase5001_i16s_i16s_o16s,
        4,                 // kernelWidth
        4,                 // kernelHeight
        2,                 // strideWidth
        2,                 // strideHeight
        1,                 // dilationHeight
        1,                 // dilationWidth
        64,                // inWidth
        1,                 // pad
        8,                 // maxHeight
        448,               // inChoffset
        390,               // validColsIn
        265,               // kDim
        640,               // pitchA
        64,                // numOfOutputChKerBuf
        3536,              // pitchC
        64,                // subMChannels
        64,                // numInChannels
        64,                // numOutChannels
        1,                 // numGroups
        12,                // qShift
        12,                // biasB
        MMALIB_SATURATION, // activationType
        MMALIB_INT16,      // dataTypeA
        MMALIB_INT16,      // dataTypeB
        MMALIB_INT16,      // dataTypeC
        0,                 // mode
        0,                 // circularOffset
        1,                 // totalN
        1,                 // subN
        0,                 // validColsPerRowIn
        0,                 // ValidRowsIn
        0,                 // outputPitchPerRow
        0,                 // inputPitchPerRow
        MMALIB_TEST_OUTPUT_MSMC,
        0, // preProcessFlag
        5001,
    },
#endif

#if ((TEST_CASE == 5003) || (TEST_CATEGORY == 1000))
    {
        STATIC, // testPattern
        NULL,
        NULL,
        NULL,
        NULL,
        staticRefInputXCaseCase5003_i16s_i16s_o16s,
        staticRefInputHCaseCase5003_i16s_i16s_o16s,
        staticRefOutputYMMALIBCaseCase5003_i16s_i16s_o16s,
        staticRefOutputYCaseCase5003_i16s_i16s_o16s,
        2,                 // kernelWidth
        2,                 // kernelHeight
        2,                 // strideWidth
        2,                 // strideHeight
        1,                 // dilationHeight
        1,                 // dilationWidth
        64,                // inWidth
        0,                 // pad
        8,                 // maxHeight
        448,               // inChoffset
        256,               // validColsIn
        41,                // kDim
        640,               // pitchA
        64,                // numOfOutputChKerBuf
        3536,              // pitchC
        64,                // subMChannels
        32,                // numInChannels
        64,                // numOutChannels
        1,                 // numGroups
        12,                // qShift
        12,                // biasB
        MMALIB_SATURATION, // activationType
        MMALIB_INT16,      // dataTypeA
        MMALIB_INT16,      // dataTypeB
        MMALIB_INT16,      // dataTypeC
        0,                 // mode
        0,                 // circularOffset
        1,                 // totalN
        1,                 // subN
        0,                 // validColsPerRowIn
        0,                 // ValidRowsIn
        0,                 // outputPitchPerRow
        0,                 // inputPitchPerRow
        MMALIB_TEST_OUTPUT_MSMC,
        0, // preProcessFlag
        5003,
    },
#endif



};

void deconvolve_row_ixX_ixX_oxX_getTestParams (deconvolve_row_ixX_ixX_oxX_testParams_t **params, int32_t *numTests)
{
   *params   = testParams;
   *numTests = sizeof (testParams) / sizeof (deconvolve_row_ixX_ixX_oxX_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
