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
 *  @version  0.1 - May 2020 : Initial Version
 *
 *******************************************************************************
 */
#ifndef C7100_DSPLIB_TYPES_H_
#define C7100_DSPLIB_TYPES_H_ 1

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

/*! \brief The enumeration of possible activation operations on the computation.
 */
typedef enum {
   DSPLIB_NONE = 0,         //!< Return result as-is (allow wrapping)
   DSPLIB_RELU,             //!< Return result after applying ReLU operation
   DSPLIB_SATURATION,       //!< Return result after saturating
   DSPLIB_ROUNDING,         //!< Return result after rounding
} DSPLIB_activation_type_e; // formerly eMMAActivationType;

typedef enum {
   DSPLIB_QUANT_PER_KERNEL = 0,
   DSPLIB_QUANT_PER_CHANNEL   = 1,
} DSPLIB_quantMethod_type_e;
typedef DSPLIB_quantMethod_type_e DSPLIB_quantMethod_type;

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

#define DSPLIB_BYTE_WIDTH 64  //!< MMA width in bytes


/* ---------------------------------------------------------------- */
/*  MISRAC Rule 4.9(DEFINE.FUNC) Deviation: The advisory is not     */
/*  being addressed                                                 */
/* ---------------------------------------------------------------- */
/*! @brief Macro function that computes the minimum stride for the specified
 * number of bytes and alignment */
#define DSPLIB_CALC_STRIDE(BYTES, ALIGN_SHIFT)                                 \
  (((((BYTES)-1) >> (ALIGN_SHIFT)) + 1) << (ALIGN_SHIFT))

/*! @brief Macro for DSPLIB shift amounts */
#define DSPLIB_MMA_SIZE_8_BIT_SHIFT                                            \
  6 //!< Shift for MMA size when data type is 8-bit integers
#define DSPLIB_MMA_SIZE_16_BIT_SHIFT                                           \
  5 //!< Shift for MMA size when data type is 16-bit integers
#define DSPLIB_MMA_SIZE_32_BIT_SHIFT                                           \
  4 //!< Shift for MMA size when data type is 32-bit integers

/*! @brief MMA size as a function of precision */
//#define DSPLIB_MMA_SIZE_1_BYTE    1
#define DSPLIB_MMA_SIZE_8_BIT                                              \
  ((uint32_t)(((uint32_t)1)                                                     \
             << DSPLIB_MMA_SIZE_8_BIT_SHIFT)) //!< Shift for MMA size when data
                                              //!< type is 8-bit integers
#define DSPLIB_MMA_SIZE_16_BIT                                                 \
  ((uint32_t)(((uint32_t)1)                                                     \
             << DSPLIB_MMA_SIZE_16_BIT_SHIFT)) //!< Shift for MMA size when data
                                               //!< type is 16-bit integers
#define DSPLIB_MMA_SIZE_32_BIT                                                 \
  ((int32_t)(((uint32_t)1)                                                     \
             << DSPLIB_MMA_SIZE_32_BIT_SHIFT)) //!< Shift for MMA size when data
                                               //!< type is 32-bit integers

/* @} */
/*******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* C71000_DSPLIB_TYPES_H_ */

/* ======================================================================== */
/*  End of file:  DSPLIB_types.h                                             */
/* ======================================================================== */
