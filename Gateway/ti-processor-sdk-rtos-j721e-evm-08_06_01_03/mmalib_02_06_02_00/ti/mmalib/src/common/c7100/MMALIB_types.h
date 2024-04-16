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
 *  @file
 *
 *  @brief    File to hold common structure, enums, macros and functions for
 *            MMALIB
 *
 *  @version  0.1 - May 2020 : Initial Version
 *
 *******************************************************************************
 */
#ifndef C7100_MMALIB_TYPES_H_
#define C7100_MMALIB_TYPES_H_ 1

#include <c7x.h> // for streaming engine, streaming address gen.
#ifdef __cplusplus
//#include <c7x_scalable.h> // for device scalability
#endif
///* ---------------------------------------------------------------- */
///* Desire C namespace for these defines/includes                    */
///* ---------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * \defgroup MMALIB_COMMON Common definitions
 * \brief This module consists of definitions (macros, structures, utility
 *        functions) that are commonly applicable to all MMALIB kernels.
 * \details
 */

/* @{ */

/*******************************************************************************
 *
 * TYPEDEFS
 *
 ******************************************************************************/

/*! \brief The enumeration of possible activation operations on the computation.
 */
typedef enum {
   MMALIB_NONE = 0,         //!< Return result as-is (allow wrapping)
   MMALIB_RELU,             //!< Return result after applying ReLU operation
   MMALIB_SATURATION,       //!< Return result after saturating
   MMALIB_ROUNDING,         //!< Return result after rounding
} MMALIB_activation_type_e; // formerly eMMAActivationType;

typedef enum {
   MMALIB_QUANT_PER_KERNEL = 0,
   MMALIB_QUANT_PER_CHANNEL   = 1,
} MMALIB_quantMethod_type_e;
typedef MMALIB_quantMethod_type_e MMALIB_quantMethod_type;

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

/* #define MMALIB_BYTE_WIDTH 64  //!< MMA width in bytes */


/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The advisory is not     */
/*  being addressed                                                 */
/* ---------------------------------------------------------------- */
/*! @brief Macro function that computes the minimum stride for the specified
 * number of bytes and alignment */
#define MMALIB_CALC_STRIDE(BYTES, ALIGN_SHIFT)                                 \
  (((((BYTES)-1) >> (ALIGN_SHIFT)) + 1) << (ALIGN_SHIFT))

/*! @brief Macro for MMALIB shift amounts */
#define MMALIB_MMA_SIZE_8_BIT_SHIFT   6 //!< Shift for MMA size when data type is 8-bit integers
#define MMALIB_MMA_SIZE_16_BIT_SHIFT  5 //!< Shift for MMA size when data type is 16-bit integers
#define MMALIB_MMA_SIZE_32_BIT_SHIFT  4 //!< Shift for MMA size when data type is 32-bit integers

/* /\*! @brief MMA size as a function of precision *\/ */
/* //#define MMALIB_MMA_SIZE_1_BYTE    1 */
/* #define MMALIB_MMA_SIZE_8_BIT                                              \ */
/*   ((uint32_t)(((uint32_t)1)                                                     \ */
/*              << MMALIB_MMA_SIZE_8_BIT_SHIFT)) //!< Shift for MMA size when data */
/*                                               //!< type is 8-bit integers */
/* #define MMALIB_MMA_SIZE_16_BIT                                                 \ */
/*   ((uint32_t)(((uint32_t)1)                                                     \ */
/*              << MMALIB_MMA_SIZE_16_BIT_SHIFT)) //!< Shift for MMA size when data */
/*                                                //!< type is 16-bit integers */
/* #define MMALIB_MMA_SIZE_32_BIT                                                 \ */
/*   ((int32_t)(((uint32_t)1)                                                     \ */
/*              << MMALIB_MMA_SIZE_32_BIT_SHIFT)) //!< Shift for MMA size when data */
/*                                                //!< type is 32-bit integers */

/* @} */
/*******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* C71000_MMALIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  MMALIB_types.h                                             */
/* ======================================================================== */
