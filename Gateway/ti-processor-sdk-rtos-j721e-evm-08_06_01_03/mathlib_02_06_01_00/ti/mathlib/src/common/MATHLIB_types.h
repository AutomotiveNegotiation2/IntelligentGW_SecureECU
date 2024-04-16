/******************************************************************************
 *                                                                             *
 * module name       :MATHLIB                                                   *
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
 *            MATHLIB
 *
 *  @version  0.1 - Jan 2018 : Initial Version
 *
 *******************************************************************************
 */
#ifndef COMMON_MATHLIB_TYPES_H_
#define COMMON_MATHLIB_TYPES_H_ 1

/* This header is needed to be included in OpenCL programs which link
 * against MATHLIB, but OpenCL doesn't need the following headers */
#ifndef __OPENCL_VERSION__
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stddef.h> // for NULL
#include <stdio.h>  // for printf
#endif
#include <c7x.h> // for streaming engine, streaming address gen.


#include "MATHLIB_bufParams.h"
#include "TI_platforms.h"

#include "c71/MATHLIB_defines.h"

#include "c7100/MATHLIB_defines.h"
#include "c7100/MATHLIB_types.h"

///* ---------------------------------------------------------------- */
///* Desire C namespace for these defines/includes                    */
///* ---------------------------------------------------------------- */
#if !defined(MATHLIB_DEBUGPRINT)
#define MATHLIB_DEBUGPRINT 0 //!< Enable debug printf statements
#endif

#if (defined(_HOST_BUILD) && (MATHLIB_COMPILER_VERSION < 1003999))
#define MATHLIB_const
#else
#define MATHLIB_const const
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
#define MATHLIB_PRINTF(fmt,...)                                                 \
   do {                                                                        \
      fprintf(stdout, fmt, __VA_ARGS__);                                       \
   } while (0)

#if MATHLIB_DEBUGPRINT > 0
#define MATHLIB_DEBUGPRINTFN(N, fmt, ...)                                       \
  do {                                                                         \
    if (MATHLIB_DEBUGPRINT >= (N)) {                                            \
      fprintf(stdout, "MATHLIB debug %s - %d: " fmt, __FUNCTION__, __LINE__,    \
              __VA_ARGS__);                                                    \
    }                                                                          \
  } while (0)

#else // MATHLIB_DEBUGPRINT == 0

#define MATHLIB_DEBUGPRINTFN(N, fmt, ...)
//#define MATHLIB_PRINTF(fmt, ...)
#endif // #if MATHLIB_DEBUGPRINT

#else

#if MATHLIB_DEBUGPRINT > 0
#define MATHLIB_DEBUGPRINTFN(N, fmt, ...)                                       \
    if (MATHLIB_DEBUGPRINT >= (N)) {                                            \
      fprintf(stderr, "MATHLIB debug %s - %d: " fmt, __FUNCTION__, __LINE__,    \
              __VA_ARGS__);                                                    \
    }                                                                          \

#define MATHLIB_PRINTF(fmt, ...)                                                \
   fprintf(stderr, fmt, __VA_ARGS__)

#else // MATHLIB_DEBUGPRINT == 0

#define MATHLIB_DEBUGPRINTFN(N, fmt, ...)
#define MATHLIB_PRINTF(fmt, ...)

#endif // #if MATHLIB_DEBUGPRINT
#endif // #if defined(EVM_TEST)

#if defined(MATHLIB_MESSAGES)
// if enabled, display messages to the library user
// MATHLIB_MESSAGES should only be defined when TARGET_BUILD=debug or CHECKPARAMS=1
#define MATHLIB_MESG(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define MATHLIB_MESG(fmt, ...)
#endif //#if defined(MATHLIB_MESSAGES)

/* Original implementation that had the benefit of always being compiled and thus
 receiving error checking.  However, the fprintf generates a MISRA-C violation.
#define MATHLIB_DEBUGPRINTFN(N, fmt, ...)                                       \
  do {                                                                         \
    if (MATHLIB_DEBUGPRINT >= (N)) {                                            \
      fprintf(stderr, "MATHLIB debug %s - %d: " fmt, __FUNCTION__, __LINE__,    \
              __VA_ARGS__);                                                    \
    }                                                                          \
  } while (0)

#define MATHLIB_PRINTF(fmt, ...)                                                \
   do {                                                                        \
       fprintf(stderr, fmt, __VA_ARGS__);                                      \
   } while (0)
#endif
 */


#define MATHLIB_SOFT_MMA_RESET 0
#define RTS 1

// switch to enable or disable static inline for MATHLIB functions defined in .c files (so not many functions)
#define MATHLIB_STATIC_INLINE static inline


#ifdef __cplusplus
#include <c7x_scalable.h> // for device scalability

extern const c7x::uchar_vec MATHLIB_zeroVect_uchar_vec;
extern const c7x::ushort_vec MATHLIB_zeroVect_ushort_vec;
extern const c7x::uchar_vec MATHLIB_vperm_data_0_63;

extern "C" {
#endif /* __cplusplus */

/*!
 * \defgroup MATHLIB_COMMON Common definitions
 * \brief This module consists of definitions (macros, structures, utility
 *        functions) that are commonly applicable to all MATHLIB kernels.
 * \details
 */

/* @{ */

/*******************************************************************************
 *
 * TYPEDEFS
 *
 ******************************************************************************/

typedef double MATHLIB_D64; //!< Double precision floating point
typedef float MATHLIB_F32;  //!< Single precision floating point

/*! \brief The enumeration of all status codes. */
typedef enum {
   MATHLIB_SUCCESS = 0,           /*!< 0 => No error */
   MATHLIB_ERR_FAILURE = 1,       /*!< 1 => Unspecified error */
   MATHLIB_ERR_INVALID_VALUE = 2, /*!< 2 => Invalid parameter value */
   MATHLIB_ERR_INVALID_TYPE  = 3, /*!< 3 => Invalid parameter type (MATHLIB_data_type_e data_type) */
   MATHLIB_ERR_INVALID_DIMENSION = 4, /*!< 4 => Dimension parameter (width/height) is too big/small */
   MATHLIB_ERR_NULL_POINTER = 5, /*!< 5 => Unsupported null pointer condition */
   MATHLIB_ERR_NOT_IMPLEMENTED = 6, /*!< 6 => Parameter configuration is not supported/implemented */
   MATHLIB_ERR_NOT_EQUAL_WIDTH_STRIDE = 7, /*!< 7 => Stride should be equal to width * element size */
   MATHLIB_ERR_NOT_ALIGNED_PTRS_STRIDES = 8, /*!< 8 => Pointers and stride values are not aligned to documented value  */
   MATHLIB_ERR_NOT_ALIGNED_WIDTHS = 9, /*!< 9 => Width values are not aligned to documented value */
   MATHLIB_ERR_BUFFER_TOO_SMALL = 10, /*!< 10 => Buffer size not large enough */
   MATHLIB_ERR_INVALID_ACTIVATION = 11, /*!< 11 => Activation selection incompatible with data type */
   MATHLIB_ERR_INVALID_SHIFT = 12,      /*!< 12 => Requested shift amount is not valid */
   MATHLIB_ERROR_MAX = 13,
} MATHLIB_STATUS_NAME;

typedef MATHLIB_STATUS_NAME MATHLIB_STATUS; //!< Return value for MATHLIB functions

typedef void *MATHLIB_kernelHandle; //!< Handle type for MATHLIB operations

/*! \brief  Enumeration for the style of function implementation. */
typedef enum {
  MATHLIB_FUNCTION_NATC = 0,  /*!< Natural C implementation of the function */
  MATHLIB_FUNCTION_OPTIMIZED, /*!< Optimized C implementation of the function for
                                the MMA + C7x architecture*/
  MATHLIB_FUNCTION_MAX = 128
} MATHLIB_FUNCTION_STYLE;

/*! \brief Buffer structure for input feature maps and coefficients of @ref
 * MATHLIB_CNN_convolve_row_ixX_ixX_oxX */
typedef enum {
  MATHLIB_LINEAR = 0,    //!< Linear buffer
  MATHLIB_SE_CIRCULAR,   //!< Circular buffer for input feature map managed by
                        //!< streaming engine
  MATHLIB_BUF_CIRCULAR   //!< Circular buffer for coefficients
} MATHLIB_buffer_mode_e; // formerly eMMABufferMode;



/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

#define MATHLIB_PARAM_SIZE 128 //!< Parameter structure size in bytes
//#define MATHLIB_BYTE_WIDTH 64  //!< MMA width in bytes
#define MATHLIB_MMA_ACCUMULATOR_BYTE_WIDTH_8_BIT  4  //!< MMA accumulator width in bytes for 8 bit output data width
#define MATHLIB_MMA_ACCUMULATOR_BYTE_WIDTH_16_BIT 8  //!< MMA accumulator width in bytes for 16 bit output data width
#define MATHLIB_MMA_ACCUMULATOR_BYTE_WIDTH_32_BIT 16 //!< MMA accumulator width in bytes for 32 bit output data width


/*******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/

#define MATHLIB_ALIGN_SHIFT_64BYTES                                             \
  6 //!< Number of bits to shift for 64-byte memory alignment
#define MATHLIB_ALIGN_SHIFT_128BYTES                                            \
  7 //!< Number of bits to shift for 128-byte memory alignment
#define MATHLIB_ALIGN_SHIFT_256BYTES                                            \
  8 //!< Number of bits to shift for 256-byte memory alignment

#define MATHLIB_ALIGN_64BYTES                                                   \
  (1 << MATHLIB_ALIGN_SHIFT_64BYTES) //!< Align by 64-byte memory alignment
#define MATHLIB_ALIGN_128BYTES                                                  \
  (1 << MATHLIB_ALIGN_SHIFT_128BYTES) //!< Align by 128-byte memory alignment
#define MATHLIB_ALIGN_256BYTES                                                  \
  (1 << MATHLIB_ALIGN_SHIFT_256BYTES) //!< Align by 256-byte memory alignment

#define MATHLIB_L2DATA_ALIGN_SHIFT                                              \
  MATHLIB_ALIGN_SHIFT_64BYTES //!< Set the default L2 data alignment

/*! @brief Macro that specifies the alignment of data buffers in L2 memory for
 * optimal performance */
#define MATHLIB_L2DATA_ALIGNMENT (((uint32_t)1) << ((uint32_t)MATHLIB_L2DATA_ALIGN_SHIFT))

/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The advisory is not     */
/*  being addressed                                                 */
/* ---------------------------------------------------------------- */
/*! @brief Macro function that computes the minimum stride for the specified
 * number of bytes and alignment */
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
      #define MATHLIB_asm(string) ;
   #else
      #define MATHLIB_asm(string); asm(string);
   #endif  // _HOST_BUILD
#else
   #define MATHLIB_asm(string) ;
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
#define MATHLIB_UNROLL(count)
#else
#define MATHLIB_UNROLL(count) _Pragma(str(UNROLL(count)))
#endif
#else
#define MATHLIB_UNROLL(COUNT) [[TI::unroll(COUNT)]]
#endif

#if defined(_HOST_BUILD)
#ifdef WIN32
#define __attribute__()
#define MATHLIB_MUST_ITERATE(initial, max, multiple)
#else
#define MATHLIB_MUST_ITERATE(initial, max, multiple) _Pragma(str(MUST_ITERATE(initial, max, multiple)))
#endif
#else
#define MATHLIB_MUST_ITERATE(INTIAL, MAX, MULTIPLE)  [[TI::must_iterate(INTIAL, MAX, MULTIPLE)]]
#endif

#ifndef MATHLIB_NUMBER_RANDOM_DIM_TESTS
#define MATHLIB_NUMBER_RANDOM_DIM_TESTS 25
#endif

#if defined(PERFORMANCE_TEST)
#define MATHLIB_PERFORMANCE_TEST_PATTERN SEQUENTIAL
#else
#define MATHLIB_PERFORMANCE_TEST_PATTERN RANDOM_SIGNED
#endif

#define MATHLIB_TEST_OUTPUT_HEAP 0
#if defined(_HOST_BUILD)
   // Valgrind works better when output is in the heap (it can't track statically allocated memory), so
   // in host emulation mode, place test outputs in the heap rather than statically allocated MSMC
   #define MATHLIB_TEST_OUTPUT_MSMC MATHLIB_TEST_OUTPUT_HEAP
#else
   #define MATHLIB_TEST_OUTPUT_MSMC 1
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
#define MATHLIB_min(x, y)                                                       \
  (((x) < (y)) ? (x) : (y)) /*!< A macro to return the minimum of 2 values. */
#define MATHLIB_max(x, y)                                                       \
  (((x) < (y)) ? (y) : (x)) /*!< A macro to return the maximum of 2 values. */
#define MATHLIB_ceilingDiv(x, y)                                                \
  (((x) + (y)-1) /                                                             \
   (y)) /*!< A macro to return the ceiling of the division of two integers. */


/* @} */
/** @endcond  */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* COMMON_MATHLIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  MATHLIB_types.h                                             */
/* ======================================================================== */
