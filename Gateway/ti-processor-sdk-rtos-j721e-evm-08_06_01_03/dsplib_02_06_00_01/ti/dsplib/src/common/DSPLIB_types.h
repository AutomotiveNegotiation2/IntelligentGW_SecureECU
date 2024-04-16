/******************************************************************************
 *                                                                             *
 * module name       :DSPLIB                                                   *
 *                                                                             *
 * module descripton :Matrix Multiply Accelerator Library module for C7x+MMA   *
 *                                                                             *
 * Copyright (C) 2017-2018 Texas Instruments Incorporated - http://www.ti.com/ *
 * ALL RIGHTS RESERVED                                                         *
 *                                                                             *
 ******************************************************************************/

/**
 ******************************************************************************
 *  @file
 *
 *  @brief    File to hold common structure, enums, macros and functions for
 *            DSPLIB
 *
 *  @version  0.1 - Jan 2018 : Initial Version
 *
 *******************************************************************************
 */
#ifndef COMMON_DSPLIB_TYPES_H_
#define COMMON_DSPLIB_TYPES_H_ 1

/* This header is needed to be included in OpenCL programs which link
 * against DSPLIB, but OpenCL doesn't need the following headers */
#ifndef __OPENCL_VERSION__
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stddef.h> // for NULL
#include <stdio.h>  // for printf
#endif
#include <c7x.h> // for streaming engine, streaming address gen.


#include "DSPLIB_bufParams.h"
#include "TI_platforms.h"

#include "c71/DSPLIB_defines.h"

#include "c7100/DSPLIB_defines.h"
#include "c7100/DSPLIB_types.h"

///* ---------------------------------------------------------------- */
///* Desire C namespace for these defines/includes                    */
///* ---------------------------------------------------------------- */
#if !defined(DSPLIB_DEBUGPRINT)
#define DSPLIB_DEBUGPRINT 0 //!< Enable debug printf statements
#endif

#if (defined(_HOST_BUILD) && (DSPLIB_COMPILER_VERSION < 1003999))
#define DSPLIB_const
#else
#define DSPLIB_const const
#endif

#define __PRAGMA(x) _Pragma(#x)
#ifdef __cplusplus
#  define __INLINE_FUNC(x) __PRAGMA(FUNC_ALWAYS_INLINE)
#else
#  define __INLINE_FUNC(x) __PRAGMA(FUNC_ALWAYS_INLINE(x))
#endif

/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The following two       */
/*  function-like macros do not have equivalent function            */
/*  implementations.                                                */
/* ---------------------------------------------------------------- */
#if defined(EVM_TEST)
#define DSPLIB_PRINTF(fmt,...)                                                 \
   do {                                                                        \
      fprintf(stdout, fmt, __VA_ARGS__);                                       \
   } while (0)

#if DSPLIB_DEBUGPRINT > 0
#define DSPLIB_DEBUGPRINTFN(N, fmt, ...)                                       \
  do {                                                                         \
    if (DSPLIB_DEBUGPRINT >= (N)) {                                            \
      fprintf(stdout, "DSPLIB debug %s - %d: " fmt, __FUNCTION__, __LINE__,    \
              __VA_ARGS__);                                                    \
    }                                                                          \
  } while (0)

#else // DSPLIB_DEBUGPRINT == 0

#define DSPLIB_DEBUGPRINTFN(N, fmt, ...)
//#define DSPLIB_PRINTF(fmt, ...)
#endif // #if DSPLIB_DEBUGPRINT

#else

#if DSPLIB_DEBUGPRINT > 0
#define DSPLIB_DEBUGPRINTFN(N, fmt, ...)                                       \
    if (DSPLIB_DEBUGPRINT >= (N)) {                                            \
      fprintf(stderr, "DSPLIB debug %s - %d: " fmt, __FUNCTION__, __LINE__,    \
              __VA_ARGS__);                                                    \
    }                                                                          \

#define DSPLIB_PRINTF(fmt, ...)                                                \
   fprintf(stderr, fmt, __VA_ARGS__)

#else // DSPLIB_DEBUGPRINT == 0

#define DSPLIB_DEBUGPRINTFN(N, fmt, ...)
#define DSPLIB_PRINTF(fmt, ...)

#endif // #if DSPLIB_DEBUGPRINT
#endif // #if defined(EVM_TEST)

#if defined(DSPLIB_MESSAGES)
// if enabled, display messages to the library user
// DSPLIB_MESSAGES should only be defined when TARGET_BUILD=debug or CHECKPARAMS=1
#define DSPLIB_MESG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DSPLIB_MESG(fmt, ...)
#endif //#if defined(DSPLIB_MESSAGES)

/* Original implementation that had the benefit of always being compiled and thus
 receiving error checking.  However, the fprintf generates a MISRA-C violation.
#define DSPLIB_DEBUGPRINTFN(N, fmt, ...)                                       \
  do {                                                                         \
    if (DSPLIB_DEBUGPRINT >= (N)) {                                            \
      fprintf(stderr, "DSPLIB debug %s - %d: " fmt, __FUNCTION__, __LINE__,    \
              __VA_ARGS__);                                                    \
    }                                                                          \
  } while (0)

#define DSPLIB_PRINTF(fmt, ...)                                                \
   do {                                                                        \
       fprintf(stderr, fmt, __VA_ARGS__);                                      \
   } while (0)
#endif
 */


#define DSPLIB_SOFT_MMA_RESET 0

// switch to enable or disable static inline for DSPLIB functions defined in .c files (so not many functions)
#define DSPLIB_STATIC_INLINE static inline


#ifdef __cplusplus
#include <c7x_scalable.h> // for device scalability

extern const c7x::uchar_vec DSPLIB_zeroVect_uchar_vec;
extern const c7x::ushort_vec DSPLIB_zeroVect_ushort_vec;
extern const c7x::uchar_vec DSPLIB_vperm_data_0_63;

extern "C" {
#endif /* __cplusplus */

/*!
 * \defgroup DSPLIB_COMMON Common definitions
 * \brief This module consists of definitions (macros, structures, utility
 *        functions) that are commonly applicable to all DSPLIB kernels.
 * \details
 */

/* @{ */

/*******************************************************************************
 *
 * TYPEDEFS
 *
 ******************************************************************************/

typedef double DSPLIB_D64; //!< Double precision floating point
typedef float DSPLIB_F32;  //!< Single precision floating point

/*! \brief The enumeration of all status codes. */
typedef enum {
   DSPLIB_SUCCESS = 0,           /*!< 0 => No error */
   DSPLIB_ERR_FAILURE = 1,       /*!< 1 => Unspecified error */
   DSPLIB_ERR_INVALID_VALUE = 2, /*!< 2 => Invalid parameter value */
   DSPLIB_ERR_INVALID_TYPE  = 3, /*!< 3 => Invalid parameter type (DSPLIB_data_type_e data_type) */
   DSPLIB_ERR_INVALID_DIMENSION = 4, /*!< 4 => Dimension parameter (width/height) is too big/small */
   DSPLIB_ERR_NULL_POINTER = 5, /*!< 5 => Unsupported null pointer condition */
   DSPLIB_ERR_NOT_IMPLEMENTED = 6, /*!< 6 => Parameter configuration is not supported/implemented */
   DSPLIB_ERR_NOT_EQUAL_WIDTH_STRIDE = 7, /*!< 7 => Stride should be equal to width * element size */
   DSPLIB_ERR_NOT_ALIGNED_PTRS_STRIDES = 8, /*!< 8 => Pointers and stride values are not aligned to documented value  */
   DSPLIB_ERR_NOT_ALIGNED_WIDTHS = 9, /*!< 9 => Width values are not aligned to documented value */
   DSPLIB_ERR_BUFFER_TOO_SMALL = 10, /*!< 10 => Buffer size not large enough */
   DSPLIB_ERR_INVALID_ACTIVATION = 11, /*!< 11 => Activation selection incompatible with data type */
   DSPLIB_ERR_INVALID_SHIFT = 12,      /*!< 12 => Requested shift amount is not valid */
   DSPLIB_ERROR_MAX = 13,
   // DSPLIB_CNN_convolve_row
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_INCHOFFSET_CIRCULAR = 1000, /*!< 1000 => Invalid InChOffset value*/
   DSPLIB_ERR_CONVOLVE_ROW_UNSUPPORTED_STRIDE  = 1001, /*!< 1001 => Unsupported stride value*/
   DSPLIB_ERR_CONVOLVE_ROW_UNSUPPORTED_TYPE_COMBINATION = 1002, /*!< 1002 => Unsupported combination of weights, input and output data types */
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_PTR_STRIDE = 1003, /*!< 1003 => Invalid pointer stride */
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_SUBMCHANNELS_STRIDE = 1004,  /*!< 1004 => Invalid subMChannels strided */
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_SUBMCHANNELS = 1005,  /*!< 1005 => Invalid subMChannels and MChannels combination*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_BUFFER_DIMENSION = 1006,  /*!< 1006 => Invalid buffer dimension*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_ROWS_STRIDE = 1007, /*!< 1007 => Invalid Valid RowsIn Strided*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_INITARGS = 1008, /*!< 1008 => inWidth, validColsIn, inChOffset, Fc, Fr, dilationX, dilationY, strideX, strideY, or maxHeight*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_VALIDCOLSIN = 1009,  /*!< 1009 => Invalid Valid ColsIn*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_NUM_GROUPS_PER_KERNEL = 1010,  /*!< 1010 => Invalid numGroupsPerKernel*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_NUM_OUTPUT_CHANNELS_PER_GROUP = 1011,  /*!< 1011 => Invalid number of output channels per group*/
   DSPLIB_ERR_CONVOLVE_ROW_INVALID_NUM_GROUPS_PER_KERNEL_STRIDED = 1012, /*!< 1012 => Invalid numGroupsPerKernel strided convolution*/

   // DSPLIB_CNN_convolve_col_smallNo
   DSPLIB_ERR_CONVOLVE_COL_INVALID_SHIFTMETHOD = 2000, /*!< 2000 => Invalid shiftMethod selected */
   DSPLIB_ERR_CONVOLVE_COL_INVALID_SHIFTVALUES = 2001, /*!< 2001 => Invalid shiftValues pointer in combination with shiftMethod value */
   DSPLIB_ERR_CONVOLVE_COL_INVALID_PAD_VALUES  = 2002, /*!< 2002 => Invalid combination of pad values */
   DSPLIB_ERR_CONVOLVE_COL_INVALID_NUMBIASVALS = 2003, /*!< 2003 => Invalid selection for numBiasVals, note combination restrictions with shiftMethod*/
   DSPLIB_ERR_CONVOLVE_COL_INVALID_BIASBVALUES = 2004, /*!< 2004 => Invalid biasBValues pointer in combination with shiftMethod value */
   DSPLIB_ERR_CONVOLVE_COL_INVALID_BIASB_TYPE  = 2005, /*!< 2005 => Invalid biasB data type, check that it matches input feature map type */
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_INPUT_FEATURE_MAP_TYPE  = 2006, /*!< 2006 => Unsupported input feature map data type */
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_WEIGHTS_TYPE            = 2007, /*!< 2007 => Unsupported filter weights data type */
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_WEIGHTS_DIMENSION       = 2008, /*!< 2008 => Unsupported filter weights dimension */
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_OUTPUT_FEATURE_MAP_TYPE = 2009, /*!< 2009 => Unsupported output feature map data type */
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_TYPE_COMBINATION        = 2010, /*!< 2010 => Unsupported combination of weights, input and output data types */
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_STRIDE  = 2011, /*!< 2011 => Unsupported stride value*/
   DSPLIB_ERR_CONVOLVE_COL_UNSUPPORTED_GROUPING= 2012, /*!< 2012 => Unsupported input/output feature map grouping*/
   DSPLIB_ERR_CONVOLVE_COL_INVALID_CASE        = 2013, /*!< 2013 => Unexpected error related to problem geometry*/

   // DSPLIB_CNN_deconvolve_row
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_KERNEL_SIZE = 3000, /*!< 3000 => Invalid kernel size, widht or height*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_STRIDE = 3001, /*!< 3001 => Invalid stride values*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_DILATION = 3002, /*!< 3002 => Invalid dilation values*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_PAD = 3003, /*!< 3003 => Invalid pad value*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_INIT_ARGS = 3004, /*!< 3004 => Invalid init args*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_BUFFER_DIMENSION_WEIGHTS = 3005, /*!< 3005 => Invalid buffer dim for weights*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_SUBMCHANNELS = 3006,  /*!< 3006 => Invalid subMChannels and MChannels combination*/
   DSPLIB_ERR_DECONVOLVE_ROW_INVALID_BUFFER_SIZES = 3007,  /*!< 3007 => Invalid buffer size*/

   // DSPLIB_CNN_fullyConnected
   DSPLIB_ERR_FULLYCONNECTED_INVALID_TYPE_COMBINATION = 4000, /*!< 4000 => Invalid datatype combination*/
   DSPLIB_ERR_FULLYCONNECTED_INVALID_DIMENSION_COMBINATION = 4001, /*!< 4001 => Invalid dimension combination*/
   DSPLIB_ERR_FULLYCONNECTED_INVALID_TYPE_RELU_COMBINATION = 4002, /*!< 4002 => Invalid type and ReLU combination*/

   // DSPLIB_CNN_pixelShuffle_row
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_INCHOFFSET_CIRCULAR = 5000, /*!< 5000 => Invalid InChOffset value*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_UNSUPPORTED_STRIDE  = 5001, /*!< 5001 => Unsupported stride value*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_UNSUPPORTED_TYPE_COMBINATION = 5002, /*!< 5002 => Unsupported combination of weights, input and output data types */
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_PTR_STRIDE = 5003, /*!< 5003 => Invalid pointer stride */
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_SUBMCHANNELS_STRIDE = 5004,  /*!< 5004 => Invalid subMChannels strided */
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_SUBMCHANNELS = 5005,  /*!< 5005 => Invalid subMChannels and MChannels combination*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_BUFFER_DIMENSION = 5006,  /*!< 5006 => Invalid buffer dimension*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_ROWS_STRIDE = 5007, /*!< 5007 => Invalid Valid RowsIn Strided*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_INITARGS = 5008, /*!< 5008 => inWidth, validColsIn, inChOffset, Fc, Fr, dilationX, dilationY, strideX, strideY, or maxHeight*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_VALIDCOLSIN = 5009,  /*!< 5009 => Invalid Valid ColsIn*/
   DSPLIB_ERR_PIXELSHUFFLE_ROW_INVALID_UPSCALE_FACTOR = 5010,  /*!< 5010 => Invalid upscale factor*/

   // DSPLIB_CNN_tensor_convert_ixX_oxX
   DSPLIB_ERR_TENSOR_CONVERT_INVALID_TYPE_COMBINATION = 6000, /*!< 6000 => Invalid datatype combination*/
   DSPLIB_ERR_TENSOR_CONVERT_INVALID_DIMENSION_COMBINATION = 6001, /*!< 6001 => Invalid dimension combination*/
   DSPLIB_ERR_TENSOR_CONVERT_UNSUPPORTED_TYPE_COMBINATION = 6002, /*!< 6002 => Unsupported dimension combination*/
   DSPLIB_ERR_TENSOR_CONVERT_UNSUPPORTED_CHANNEL_DIMENSION = 6003, /*!< 6003 => Unsupported channel dimension*/
   DSPLIB_ERR_TENSOR_CONVERT_UNSUPPORTED_CONVRSION_FORMAT = 6004, /*!< 6004 => Unsupported conversion format*/
   DSPLIB_ERR_TENSOR_CONVERT_UNSUPPORTED_PAD_DIMENSION = 6005, /*!< 6005 => Unsupported pad dimension*/


   // DSPLIB_LINALG_matrixMatrixMultiply
   DSPLIB_ERR_MATRIX_MATRIX_MULTIPLY_UNSUPPORTED_INPUT_TYPE  = 10000, /*!< 10000 => Unsupported input data type */
   DSPLIB_ERR_MATRIX_MATRIX_MULTIPLY_UNSUPPORTED_OUTPUT_TYPE = 10001, /*!< 10001 => Unsupported output data type */
   DSPLIB_ERR_MATRIX_MATRIX_MULTIPLY_UNSUPPORTED_TYPE_COMBINATION = 10002,  /*!< 10002 => Unsupported combination of input and output data type */
   // DSPLIB_LINALG_matrixMatrixMultiplyAccumulate
   DSPLIB_ERR_MATRIX_MATRIX_MULTIPLY_ACCUMULATE_UNSUPPORTED_INPUT_TYPE  = 11000, /*!< 11000 => Unsupported input data type */
   DSPLIB_ERR_MATRIX_MATRIX_MULTIPLY_ACCUMULATE_UNSUPPORTED_OUTPUT_TYPE = 11001, /*!< 11001 => Unsupported output data type */
   DSPLIB_ERR_MATRIX_MATRIX_MULTIPLY_ACCUMULATE_UNSUPPORTED_TYPE_COMBINATION = 11002,  /*!< 11002 => Unsupported combination of input and output data type */
   // DSPLIB_LINALG_matrixTranspose
   DSPLIB_ERR_MATRIX_TRANSPOSE_UNSUPPORTED_INPUT_TYPE  = 12000, /*!< 12000 => Unsupported input data type */
   DSPLIB_ERR_MATRIX_TRANSPOSE_UNSUPPORTED_OUTPUT_TYPE = 12001, /*!< 12001 => Unsupported output data type */
   DSPLIB_ERR_MATRIX_TRANSPOSE_UNSUPPORTED_TYPE_COMBINATION = 12002,  /*!< 12002 => Unsupported combination of input and output data type */
   // DSPLIB_LINALG_pointwiseMatrixMatrixMultiply
   DSPLIB_ERR_POINTWISE_MATRIX_MATRIX_MULTIPLY_UNSUPPORTED_INPUT_TYPE  = 13000, /*!<  13000 => Unsupported input data type */
   DSPLIB_ERR_POINTWISE_MATRIX_MATRIX_MULTIPLY_UNSUPPORTED_OUTPUT_TYPE = 13001, /*!<  13001 => Unsupported output data type */
   DSPLIB_ERR_POINTWISE_MATRIX_MATRIX_MULTIPLY_UNSUPPORTED_TYPE_COMBINATION = 13002,  /*!< 13002 => Unsupported combination of input and output data type */
} DSPLIB_STATUS_NAME;

typedef DSPLIB_STATUS_NAME DSPLIB_STATUS; //!< Return value for DSPLIB functions

typedef void *DSPLIB_kernelHandle; //!< Handle type for DSPLIB operations

/*! \brief  Enumeration for the style of function implementation. */
typedef enum {
  DSPLIB_FUNCTION_NATC = 0,  /*!< Natural C implementation of the function */
  DSPLIB_FUNCTION_OPTIMIZED, /*!< Optimized C implementation of the function for
                                the MMA + C7x architecture*/
  DSPLIB_FUNCTION_MAX = 128
} DSPLIB_FUNCTION_STYLE;

/*! \brief Buffer structure for input feature maps and coefficients of @ref
 * DSPLIB_CNN_convolve_row_ixX_ixX_oxX */
typedef enum {
  DSPLIB_LINEAR = 0,    //!< Linear buffer
  DSPLIB_SE_CIRCULAR,   //!< Circular buffer for input feature map managed by
                        //!< streaming engine
  DSPLIB_BUF_CIRCULAR   //!< Circular buffer for coefficients
} DSPLIB_buffer_mode_e; // formerly eMMABufferMode;

 /*! \brief Tensor format */
typedef enum {
  DSPLIB_CHW = 0,    //!< Used when tensor is in NCHW format
  DSPLIB_HWC         //!< Used when tensor is in NHWC format
} DSPLIB_tensor_format_e;

  typedef DSPLIB_tensor_format_e DSPLIB_tensor_format;

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

#define DSPLIB_PARAM_SIZE 128 //!< Parameter structure size in bytes
//#define DSPLIB_BYTE_WIDTH 64  //!< MMA width in bytes
#define DSPLIB_MMA_ACCUMULATOR_BYTE_WIDTH_8_BIT  4  //!< MMA accumulator width in bytes for 8 bit output data width
#define DSPLIB_MMA_ACCUMULATOR_BYTE_WIDTH_16_BIT 8  //!< MMA accumulator width in bytes for 16 bit output data width
#define DSPLIB_MMA_ACCUMULATOR_BYTE_WIDTH_32_BIT 16 //!< MMA accumulator width in bytes for 32 bit output data width


/*******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/

#define DSPLIB_ALIGN_SHIFT_64BYTES                                             \
  6 //!< Number of bits to shift for 64-byte memory alignment
#define DSPLIB_ALIGN_SHIFT_128BYTES                                            \
  7 //!< Number of bits to shift for 128-byte memory alignment
#define DSPLIB_ALIGN_SHIFT_256BYTES                                            \
  8 //!< Number of bits to shift for 256-byte memory alignment

#define DSPLIB_ALIGN_64BYTES                                                   \
  (1 << DSPLIB_ALIGN_SHIFT_64BYTES) //!< Align by 64-byte memory alignment
#define DSPLIB_ALIGN_128BYTES                                                  \
  (1 << DSPLIB_ALIGN_SHIFT_128BYTES) //!< Align by 128-byte memory alignment
#define DSPLIB_ALIGN_256BYTES                                                  \
  (1 << DSPLIB_ALIGN_SHIFT_256BYTES) //!< Align by 256-byte memory alignment

#define DSPLIB_L2DATA_ALIGN_SHIFT                                              \
  DSPLIB_ALIGN_SHIFT_64BYTES //!< Set the default L2 data alignment

/*! @brief Macro that specifies the alignment of data buffers in L2 memory for
 * optimal performance */
#define DSPLIB_L2DATA_ALIGNMENT (((uint32_t)1) << ((uint32_t)DSPLIB_L2DATA_ALIGN_SHIFT))

/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The advisory is not     */
/*  being addressed                                                 */
/* ---------------------------------------------------------------- */
/*! @brief Macro function that computes the minimum stride for the specified
 * number of bytes and alignment */
/* #define DSPLIB_CALC_STRIDE(BYTES, ALIGN_SHIFT)                                 \ */
/*   (((((BYTES)-1) >> (ALIGN_SHIFT)) + 1) << (ALIGN_SHIFT)) */

/* /\*! @brief Macro for DSPLIB shift amounts *\/ */
/* #define DSPLIB_MMA_SIZE_8_BIT_SHIFT                                            \ */
/*   6 //!< Shift for MMA size when data type is 8-bit integers */
/* #define DSPLIB_MMA_SIZE_16_BIT_SHIFT                                           \ */
/*   5 //!< Shift for MMA size when data type is 16-bit integers */
/* #define DSPLIB_MMA_SIZE_32_BIT_SHIFT                                           \ */
/*   4 //!< Shift for MMA size when data type is 32-bit integers */

/* /\*! @brief MMA size as a function of precision *\/ */
/* //#define DSPLIB_MMA_SIZE_1_BYTE    1 */
/* #define DSPLIB_MMA_SIZE_8_BIT                                              \ */
/*   ((uint32_t)(((uint32_t)1)                                                     \ */
/*              << DSPLIB_MMA_SIZE_8_BIT_SHIFT)) //!< Shift for MMA size when data */
/*                                               //!< type is 8-bit integers */
/* #define DSPLIB_MMA_SIZE_16_BIT                                                 \ */
/*   ((uint32_t)(((uint32_t)1)                                                     \ */
/*              << DSPLIB_MMA_SIZE_16_BIT_SHIFT)) //!< Shift for MMA size when data */
/*                                                //!< type is 16-bit integers */
/* #define DSPLIB_MMA_SIZE_32_BIT                                                 \ */
/*   ((int32_t)(((uint32_t)1)                                                     \ */
/*              << DSPLIB_MMA_SIZE_32_BIT_SHIFT)) //!< Shift for MMA size when data */
/*                                                //!< type is 32-bit integers */

/* @} */

/******************************************************************************
 *
 *  Do not document these in the User Guide
 ******************************************************************************/

/*!
 * @cond
 */
/* @{ */


/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The advisory is not     */
/*  being addressed                                                 */
/* ---------------------------------------------------------------- */
// remove asm comments for Loki testing as they may add cycles
#if defined(QT_TEST) || defined(RTL_TEST) || defined(EVM_TEST)
   #if defined(_HOST_BUILD)
      #define DSPLIB_asm(string) ;
   #else
      #define DSPLIB_asm(string); asm(string);
   #endif  // _HOST_BUILD
#else
   #define DSPLIB_asm(string) ;
#endif

/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The advisory is not     */
/*  being addressed  so as not to lose portability across different */
/*  platforms.                                                      */
/* ---------------------------------------------------------------- */
// cl7x unroll attributes not recognized by gcc/gpp compiler and generate
// warnings. Remove them with macro
#if defined(_HOST_BUILD)
#define str(x) #x
#define xstr(x) str(x)
#ifdef WIN32
#define __attribute__()
#define DSPLIB_UNROLL(count)
#else
#define DSPLIB_UNROLL(count) _Pragma(str(UNROLL(count)))
#endif
#else
#define DSPLIB_UNROLL(COUNT) [[TI::unroll(COUNT)]]
#endif

#if defined(_HOST_BUILD)
#ifdef WIN32
#define __attribute__()
#define DSPLIB_MUST_ITERATE(initial, max, multiple)
#else
#define DSPLIB_MUST_ITERATE(initial, max, multiple) _Pragma(str(MUST_ITERATE(initial, max, multiple)))
#endif
#else
#define DSPLIB_MUST_ITERATE(INTIAL, MAX, MULTIPLE)  [[TI::must_iterate(INTIAL, MAX, MULTIPLE)]]
#endif

#ifndef DSPLIB_NUMBER_RANDOM_DIM_TESTS
#define DSPLIB_NUMBER_RANDOM_DIM_TESTS 25
#endif

#if defined(PERFORMANCE_TEST)
#define DSPLIB_PERFORMANCE_TEST_PATTERN SEQUENTIAL
#else
#define DSPLIB_PERFORMANCE_TEST_PATTERN RANDOM_SIGNED
#endif

#define DSPLIB_TEST_OUTPUT_HEAP 0
#if defined(_HOST_BUILD)
   // Valgrind works better when output is in the heap (it can't track statically allocated memory), so
   // in host emulation mode, place test outputs in the heap rather than statically allocated MSMC
   #define DSPLIB_TEST_OUTPUT_MSMC DSPLIB_TEST_OUTPUT_HEAP
#else
   #define DSPLIB_TEST_OUTPUT_MSMC 1
#endif

#define STRIDE_OPT_4CYCLE 1

/*******************************************************************************
 *
 * MACROS
 *
 ******************************************************************************/

/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The following           */
/*  function-like macros are intended to be used across different   */
/*  data types.                                                     */
/* ---------------------------------------------------------------- */
#define DSPLIB_min(x, y)                                                       \
  (((x) < (y)) ? (x) : (y)) /*!< A macro to return the minimum of 2 values. */
#define DSPLIB_max(x, y)                                                       \
  (((x) < (y)) ? (y) : (x)) /*!< A macro to return the maximum of 2 values. */
#define DSPLIB_ceilingDiv(x, y)                                                \
  (((x) + (y)-1) /                                                             \
   (y)) /*!< A macro to return the ceiling of the division of two integers. */


/******************************************************************************
 *
 * COMMON MMA CONIFGURATIONS
 *
 ******************************************************************************/

   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i32s_i32s_o32s;

   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i16s_i16s_o16s;
   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i16s_i16s_o16u;
   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i16u_i16s_o16s;
   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i16u_i16s_o16u;

   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i8s_i8s_o8s;
   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i8s_i8s_o8u;
   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i8u_i8s_o8s;
   extern const DSPLIB_MMA_CONFIG_REG configRegisterStruct_i8u_i8s_o8u;

   extern const __HWA_OFFSET_REG offsetRegStruct_zeros;
   extern const __HWA_OFFSET_REG offsetRegStruct_diagonal_32bit;
   extern const __HWA_OFFSET_REG offsetRegStruct_diagonal_16bit;
   extern const __HWA_OFFSET_REG offsetRegStruct_diagonal_8bit;


/* @} */
/** @endcond  */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* COMMON_DSPLIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  DSPLIB_types.h                                             */
/* ======================================================================== */
