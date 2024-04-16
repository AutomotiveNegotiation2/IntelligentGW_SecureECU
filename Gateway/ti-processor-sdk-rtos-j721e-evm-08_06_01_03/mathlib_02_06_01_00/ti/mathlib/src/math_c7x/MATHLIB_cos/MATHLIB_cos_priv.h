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

/********************************************************************************
  *  @file     MATHLIB_cos_priv.h
  *
  *  @brief    File to hold private parameter of function MATHLIB_cos
  *
  *  @version  0.1 - Mar 2022 : Initial Version
  *            
 ********************************************************************************/

#ifndef MATHLIB_COS_IXX_IXX_OXX_PRIV_H_
#define MATHLIB_COS_IXX_IXX_OXX_PRIV_H_

#include "../../common/MATHLIB_utility.h"
#include "MATHLIB_cos.h"

/*!
 * \file
 * \brief Header file for kernel's internal use. For the kernel's interface, please 
 *        see @ref MATHLIB_cos
 */

/*! 
 * @brief Macro to define the size of bufPblock array of 
 *        @ref MATHLIB_cos_PrivArgs structure.
 *
 */

/*!
 *  @brief This is a function pointer type that conforms to the 
 *         declaration of @ref MATHLIB_cos_exec_ci
 *         and @ref MATHLIB_cos_exec_cn.
 */
typedef MATHLIB_STATUS  (*pFxnMATHLIB_cos_exec)(
  void *restrict pIn,
  void *restrict pOut,
  int32_t blockSize);

/*!
 *  @brief This function is the initialization function for the C7x 
 *         implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref MATHLIB_cos_init.
 *
 * @details This function determines the configuration for the streaming engine
 *          and MMA hardware resources based on the function call parameters, 
 *          and the configuration is saved in bufPBlock array. In the kernel
 *          call sequence, @ref MATHLIB_cos_exec_ci would be
 *          called later independently by the application. When 
 *          @ref MATHLIB_cos_exec_ci runs, it merely retrieves
 *          the configuration from the bufPBlock and uses it to set up the 
 *          hardware resources. This arrangement is so that 
 *          @ref MATHLIB_cos_exec_ci does not lose cycles
 *          to determine the hardware configuration.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
 *                               information of input buffer
 *  @param [in]  bufParamsFilterCoeff :  Pointer to the structure containing dimensional
 *                               information of filter coefficient buffer
 *  @param [in/out]  bufParamsFilterVar :  Pointer to the structure containing dimensional
 *                               information of filter variable buffer
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of ouput buffer
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref MATHLIB_STATUS.
 *
 */
template <typename dataType>
extern MATHLIB_STATUS MATHLIB_cos_init_ci(
                     MATHLIB_kernelHandle handle,
                     const MATHLIB_bufParams2D_t *bufParamsIn,
                     const MATHLIB_bufParams2D_t *bufParamsOut,
                     const MATHLIB_cos_InitArgs *pKerInitArgs);


/*!
 *  @brief This function is the main execution function for the C7x 
 *         implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref MATHLIB_cos_exec.
 *
 * @details The function uses MMA hardware accelerator to perform the
 *          convolution computation. Filter data is loaded into B panel of the
 *          MMA from memory using one streaming engine, while the input data is 
 *          loaded into A vectors of the MMA using the other streaming engine. 
 *          Result of the compute from MMA C panel is stored into memory using 
 *          a stream address generator.
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn         : Pointer to buffer holding the input data
 *  @param [out] pOut        : Pointer to buffer holding the output data
 *
 *  @return      Status value indicating success or failure. Refer to @ref MATHLIB_STATUS.
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - the input and output data buffers are expected to be in L2 memory
 *    - the buffer pointers are assumed to be 64-byte aligned
 *
 */
template <typename dataType, typename intType, int32_t dataIn>
extern MATHLIB_STATUS MATHLIB_cos_exec_ci(void *restrict pIn,
                                            void *restrict pOut,
                                            int32_t blockSize);

/*!
 *  @brief This function is the main execution function for the natural
 *         C implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref MATHLIB_cos_exec.
 *
 * @details 
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn         : Pointer to buffer holding the input data
 *  @param [in]  pFilterCoeff: Pointer to buffer holding the filter coefficient data
 *  @param [in]  pFilterVar  : Pointer to buffer holding the filter variable data
 *  @param [out] pOut        : Pointer to buffer holding the output data
 *
 *  @return      Status value indicating success or failure. Refer to @ref MATHLIB_STATUS.
 *
 */
template <typename dataType, int32_t dataIn>
extern MATHLIB_STATUS MATHLIB_cos_exec_cn(void *restrict pIn,
                                            void *restrict pOut,
                                            int32_t blockSize);

/*!
 * @brief Structure that is reserved for internal use by the kernel
 */
typedef struct
{
   /*! @brief Function pointer to point to the right execution variant between
    *         @ref MATHLIB_cos_exec_cn and
    *         @ref MATHLIB_cos_exec_ci.                        */
   pFxnMATHLIB_cos_exec execute;
   /*! @brief Size of input buffer for different batches
    *         @ref MATHLIB_cos_init that will be retrieved
    *         and used by @ref MATHLIB_cos_exec                */
   int32_t blockSize;
} MATHLIB_cos_PrivArgs;

/*!
 *  @brief This function is the initialization function for the natural C
 *         implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref MATHLIB_cos_init.
 *
 * @details 
 *
 *  @param [in]  handle                 :  Active handle to the kernel
 *  @param [in]  bufParamsIn            :  Pointer to the structure containing dimensional
 *                                         information of input buffer
 *  @param [out] bufParamsOut           :  Pointer to the structure containing dimensional
 *                                         information of ouput buffer
 *  @param [in]  pKerInitArgs           :  Pointer to the structure holding init parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref MATHLIB_STATUS.
 *
 */
MATHLIB_STATUS MATHLIB_cos_init_cn(
              MATHLIB_kernelHandle handle,
              MATHLIB_bufParams2D_t *bufParamsIn,
              MATHLIB_bufParams2D_t *bufParamsOut);

#endif /* MATHLIB_COS_IXX_IXX_OXX_PRIV_H_ */

/* ======================================================================== */
/*  End of file:  MATHLIB_cos.h          */
/* ======================================================================== */

