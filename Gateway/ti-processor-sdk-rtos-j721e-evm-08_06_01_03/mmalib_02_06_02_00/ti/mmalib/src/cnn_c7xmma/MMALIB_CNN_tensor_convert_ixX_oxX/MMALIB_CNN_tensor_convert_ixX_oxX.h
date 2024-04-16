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
*  @file     MMALIB_CNN_tensor_convert_ixX_oxX.h
*
*  @brief    Public header file for MMALIB_CNN_tensor_convert_ixX_oxX
*            function
*
*  //version  0.1 - June 2020 : Initial Version - [Barath Ramesh]
*
*******************************************************************************
*/

#ifndef MMALIB_CNN_TENSOR_CONVERT_IXX_IXX_OXX_H_
#define MMALIB_CNN_TENSOR_CONVERT_IXX_IXX_OXX_H_

#include "../../common/MMALIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @defgroup MMALIB_CNN_tensor_convert_ixX_oxX MMALIB_CNN_tensor_convert_ixX_oxX
 * @brief Kernel for converting tensors of various datatypes and formats
 * @details
 *   - Kernel requires input tensor (\f$ X \f$) to be available in memory
 *   - The output tensor (\f$ Y \f$) is computed as shown below
 *     - \f$Y =  (X - inZf) \times scale + outZf \\
 *         \hspace{1.25ex} =  X \times scale - (inZf \times scale + outZf) \\
 *         \hspace{1.25ex} =  X \times scale + q \f$
 *   - For integer to floating-point conversions and vice versa, the mapping is
 *     as shown below
 *     - \f$ Y = X \times scale + q_1 \times q_2 \f$
 *   - For integer-to-integer conversions, the mapping is as shown below
 *     - \f$
 *     Y =  \text{shiftAndRound}(X \times scale + q_1 \times q_2) \\
 *       \hspace{1.25ex} =  \begin{bmatrix} scale \times I & Q_1\end{bmatrix}
 *       \times \begin{bmatrix} X \\ Q_2\end{bmatrix} \text{where, }Q_1
 *       \text{is a constant matrix and }
 *       \text{shiftAndRound is performed within MMA} \\
 *     \f$
 *   - Example configuration with two rows allocated to handle precision for
 *     qauntization; @ref
 *     MMALIB_CNN_tensor_convert_ixX_oxX_InitArgs.numRowsQuant = 2
 *     - \f$
 * Y = \begin{bmatrix}
 *          s      & 0      & \cdots & 0 & q_1 & q_1 \\
 *          0      & s      & \cdots & 0 & q_1 & q_1 \\
 *          \vdots & \cdots & \ddots & 0 & q_1 & q_1 \\
 *          0      & 0      & 0      & s & q_1 & q_1 \\
 *     \end{bmatrix}\times
 *     \begin{bmatrix}
 *          x_{(0,0)}    & x_{(0,1)}    & \cdots & x_{(0,61)} & 0 & 0 \\
 *          x_{(1,0)}    & x_{(1,1)}    & \cdots & x_{(1,61)} & 0 & 0 \\
 *          \vdots     & \vdots     & \ddots & \vdots   & 0 & 0 \\
 *          x_{(61,0)}   & x_{(61,1)}   & \cdots & x_{(61,61)} & 0 & 0 \\
 *          q_{2(0,0)}    & q_{2(0,1)}    & \cdots & q_{2(0,61)} & 0 & 0 \\
 *          q_{2(1,0)}    & q_{2(1,1)}    & \cdots & q_{2(1,61)} & 0 & 0 \\
 *       \end{bmatrix}
 *       \f$
 *   - Output pad (@ref MMALIB_CNN_tensor_convert_ixX_oxX_InitArgs.outPad) is
 *     always zero if output tensor format is NHWC (@ref MMALIB_HWC)
 *   - Performance estimates is TBD, "Arch. Compute cyc." and "Est. Compute
 *     cyc." are yet to be analyzed; right now printed as "0"
 *   - Signedness of Q2: since we use B buffers of MMA to hold the input tensor
 *     and Q2 during compute, it is required that the signedness of Q2 is the
 *     same as the input tensor
 *      - For example, Q2 cannot be int8_t when converting from uint8_t to
 *        int8_t
 *   - Signedness of Scale: Scale is always signed and the same precision as
 *     the max precision involved in the conversion
 *      - For example, scale is int16_t when converting from uint8_t to uint16_t
 *   - Only the below conversion formats are supported
 * \image html tensor_covert_supported_formats.svg "Supported Formats"
 *
 * @ingroup  MMALIB_CNN
 */

/* @{ */

/*!
 * @brief Structure containing the parameters
 * initialization of tensor convert function
 */
typedef struct {
   /*! @brief Variant of the function refer to @ref MMALIB_FUNCTION_STYLE     */
   int8_t funcStyle;
   /*! @brief input pad of each row of output feature map, unused for now*/
   int32_t inPad;
   /*! @brief output pad of each row of output feature map, specify pad only on
    * one side
    */
   int32_t outPad;

   /*! @brief Number of rows allocated for quantization matrix, Q2
    */
   int32_t numRowsQuant;

   /*! @brief input tensor format: CHW or HWC
    */
   MMALIB_tensor_format tensorFormatIn;
   /*! @brief output tensor format: CHW or HWC
    */
   MMALIB_tensor_format tensorFormatOut;

} MMALIB_CNN_tensor_convert_ixX_oxX_InitArgs;

/*!
 * @brief This structure holds all the runtime input parameters for tensor
 *        convert kernel
 */

typedef struct {

   /* bool                    lastCall; */
   /*! @brief update if this is different from init src_addr.dimz */
   uint32_t srcDimZ;
   /*! @brief update if this is different from init src_addr.dimy */
   uint32_t srcDimY;

} MMALIB_CNN_tensor_convert_ixX_oxX_ExecInArgs;

/*!
 * @brief This structure holds all the runtime output parameters for tensor
 *        convert kernel
 */

typedef struct {
   /*! @brief dummy placeholder for now */
   int32_t validColsOut;
} MMALIB_CNN_tensor_convert_ixX_oxX_ExecOutArgs;

/*!
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */
int32_t MMALIB_CNN_tensor_convert_ixX_oxX_getHandleSize (
    MMALIB_CNN_tensor_convert_ixX_oxX_InitArgs *pKerInitArgs);

/*!
 *  @brief       This function call is required to initialize the handle. In
 *               this function, most of the one-time operations are performed
 *               and results are stored in handle
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  src_addr     :  Pointer to structure containing dimensional
 *                               information of src (input tensor)
 *  @param [in]  scale_addr   :  Pointer to structure containing dimensional
 *  @param [out] dst_addr     :  Pointer to structure containing dimensional
 *                               information of dst (output tensor)
 *  @param [in]  pKerInitArgs : Pointer to structure holding init parameters
 *
 *  @return      Status of success or Error with Error Codes
 *
 *  @remarks     Application is expected to do provide valid handle
 */

MMALIB_STATUS MMALIB_CNN_tensor_convert_ixX_oxX_init (
    MMALIB_kernelHandle                               handle,
    const MMALIB_bufParams3D_t                       *src_addr,
    const MMALIB_bufParams1D_t                       *scale_addr,
    const MMALIB_bufParams3D_t                       *dst_addr,
    const MMALIB_CNN_tensor_convert_ixX_oxX_InitArgs *pKerInitArgs);

/*!
 *  @brief       This function checks the validity of the input parameters
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  src_addr     :  Pointer to structure containing dimensional
 *                               information of src (input tensor)
 *  @param [in]  scale_addr   :  Pointer to structure containing dimensional
 *                               information of scale
 *  @param [out] dst_addr     :  Pointer to structure containing dimensional
 *                               information of dst (output tensor)
 *  @param [in]  pKerInitArgs : Pointer to structure holding init parameters
 *
 *  @return      Status of success or Error with Error Codes
 *
 *  @remarks     Application is expected to do provide valid handle
 */

MMALIB_STATUS MMALIB_CNN_tensor_convert_ixX_oxX_init_checkParams (
    MMALIB_kernelHandle                               handle,
    const MMALIB_bufParams3D_t                       *src_addr,
    const MMALIB_bufParams1D_t                       *scale_addr,
    const MMALIB_bufParams3D_t                       *dst_addr,
    const MMALIB_CNN_tensor_convert_ixX_oxX_InitArgs *pKerInitArgs);

/*!
 *  @brief       This function is the main compute function, and performs
 *               the tensor datatype conversion.
 *
 *  @details     TBD
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  src[]       : Pointer to buffer holding input tensor
 *  @param [in]  scale[]     : Pointer to buffer holding scale
 *  @param [in]  shift[]     : Pointer to buffer holding shift
 *  @param [in]  q1[]        : Pointer to buffer holding Q1 matrix,
 *                             which is a scalar
 *  @param [in]  q2[]        : Pointer to buffer holding Q2 matrix
 *  @param [out] dst[]       : Pointer to buffer holding output tensor
 *  @param [in]  pKerInArgs  : Pointer to structure holding args used during
 *                             kernel execution
 *  @param [out] pKerOutArgs : Pointer to structure holding args generated
 *                             during kernel execution (unused for now)
 *
 *  @return      Status of success or Error with Error Codes
 *
 *  @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *
 *  @par Performance Considerations:
 *    - TBD
 *
 *  @remarks     Application is expected to do call of checkParams function
 *               prior to this function as it avoids check of paramaters for
 *               each invocation for optimization
 */

MMALIB_STATUS MMALIB_CNN_tensor_convert_ixX_oxX_exec (
    MMALIB_kernelHandle                                 handle,
    const void                                         *src,
    const void                                         *scale,
    const uint8_t                                      *shift,
    const void                                         *q1,
    const void                                         *q2,
    void                                               *dst,
    const MMALIB_CNN_tensor_convert_ixX_oxX_ExecInArgs *pKerInArgs,
    MMALIB_CNN_tensor_convert_ixX_oxX_ExecOutArgs      *pKerOutArgs);

/*!
 *  @brief       This function checks the parameters and should be called
 *               before kernel executuon. It can be called once
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  src[]       : Pointer to buffer holding input tensor
 *  @param [in]  scale[]     : Pointer to buffer holding scale
 *  @param [in]  shift[]     : Pointer to buffer holding shift
 *  @param [in]  q1[]        : Pointer to buffer holding Q1 matrix,
 *                             which is a scalar
 *  @param [in]  q2[]        : Pointer to buffer holding Q2 matrix
 *  @param [out] dst[]       : Pointer to buffer holding output tensor
 *  @param [in]  pKerInArgs  : Pointer to structure holding args used during
 *                             kernel execution
 *  @param [out] pKerOutArgs : Pointer to structure holding args generated
 *                             during kernel execution (unused for now)
 *
 *  @return      Status of success or Error with Error Codes
 *
 *  @remarks     None
 */

MMALIB_STATUS
MMALIB_CNN_tensor_convert_ixX_oxX_exec_checkParams (
    MMALIB_kernelHandle                                 handle,
    const void                                         *src,
    const void                                         *scale,
    const uint8_t                                      *shift,
    const void                                         *q1,
    const void                                         *q2,
    void                                               *dst,
    const MMALIB_CNN_tensor_convert_ixX_oxX_ExecInArgs *pKerInArgs,
    MMALIB_CNN_tensor_convert_ixX_oxX_ExecOutArgs      *pKerOutArgs);

/*!
 *  @brief       This function estimates the kernel performance
 *
 *  @param [in]  handle       : Active handle to the kernel
 *  @param [in]  src_addr     :  Pointer to structure containing dimensional
 *                               information of src (input tensor)
 *  @param [in]  dst_addr     :  Pointer to structure containing dimensional
 *                               information of dst (output tensor)
 *  @param [out] idealCycles  :  TBD
 *  @param [out] archCycles   :  TBD
 *  @param [out] estCycles    :  Cycles estimated for the compute, startup,
 *                               teardown and any associated overhead
 *  @remarks     This function is only a crude estimation
 *               Performance of interger to integer conversion can degrade by
 *               2x due to unaligned memory accesses

 */

void MMALIB_CNN_tensor_convert_ixX_oxX_perfEst (
    MMALIB_kernelHandle         handle,
    const MMALIB_bufParams3D_t *src_addr,
    const MMALIB_bufParams3D_t *dst_addr,
    uint64_t                   *idealCycles,
    uint64_t                   *archCycles,
    uint64_t                   *estCycles);

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* _MMALIB_CNN_TENSOR_CONVERT_IXX_IXX_OXX_H_ */

/* ======================================================================== */
/*  End of file:  MMALIB_CNN_tensor_convert_ixX_oxX.h                     */
/* ======================================================================== */
