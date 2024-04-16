/*
 *******************************************************************************
 *
 * Module Name: TIDL Network Analyzer and Performance Simulator
 *
 * "Performance simulator for CNN netowrks" is software module developed
 *  for TI's C7x + MMA processor architecture. it models the performance
 *  of different layers of CNN netowrk and provides a summarized output
 * of performance

 * Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
  ******************************************************************************
  *  @file     common.h
  *
  *  @brief    Mainly to hold common macros, enums, constants across project
  *
  *  @author   PKS
  *
  *  @version  0.1 - Sep 2017 : Initial Version [PKS]
  *
 *****************************************************************************
*/

#ifndef _COMMON_H_
#define _COMMON_H_

/**
* @addtogroup networkAnalyzer
* @{
*/

#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define ABS(A)   ((A) > (0) ? (A) : (-(A)))

/** To align to a integer boundary  -
    mainly used for aligning to matrix panel size or any buswidth size */
#define ALIGN(VAL, ALIGN) ((((VAL) + (ALIGN) - 1)/(ALIGN)) * (ALIGN) )

/** To align to a integer boundary by using floor*/
#define ALIGN_FLOOR(VAL, ALIGN) (((VAL)/(ALIGN)) * (ALIGN) )


/** To Align in unit of K*Align + offset -
    Mainly used for Memory arrangement to minimize bank conflicts */
#define ALIGN_WITHOFFSET(VAL, ALIGN, OFFSET) ( ALIGN(VAL, ALIGN) + OFFSET )

#define   NONE (-1)

/** to extract number of bytes of an elements */
#define BYTES_PER_ELEMENT(dataType) (1 << dataType)

/**
 *  @enum       eMemType
 *  @brief      Enumeration for different level of memory
 *
 */
typedef enum
{
  L2 = 0,     /**< DSP L2  Memory       */
  MSMC,       /**< MSMC Memory          */
  DDR,        /**< External memory DDR  */
  MEMTYPE_TOTAL
} eMemType;

/**
 *  @enum   eStatus
 *  @brief  Enumeration for state variables (some times used for function return)
 *
 */
typedef enum
{
  NOT_VALID    = -1,  /**< Not Valid or Not initialized  */
  NOT_PRODUCED = -2,  /**< Data is not produced - specific for state */
  PRODUCED     = 100, /**< Data is not produced - specific for state */
  VALID        = 200  /**< Valid  - Use for state variable as well as return*/
} eStatus;

/**
 *  @enum   eReturnType
 *  @brief  Enumeration for function return indicating success/failure
 *
 */
typedef enum
{
  RETURN_PASS = 0,
  RETURN_FAIL = -1
} eReturnType;

/**
 *  @enum       eMemAccessType
 *  @brief      Enumeration for different access type
 *
 */
typedef enum
{
  READ = 0, /**< Read  Access */
  WRITE,    /**< Write Access */
  ACCTYPE_TOTAL
} eMemAccessType;

/**
*  @enum       eMemAccessor
*  @brief      Enumeration for accessor
*
*/
typedef enum
{
  CPU =   0, /**< CPU */
  DMA,       /**< DMA */
  NO_ACCESS, /**< DMA */
  DMA_ONCE,/** Persistent DMA */

  ACCESSOR_TOTAL
} eMemAccessor;

/**
 *  @enum       eBufferName
 *  @brief      Enumeration for different type of buffers
 *
 */
typedef enum
{
  IN_FEAT_MAP = 0, /**< Input Feature Map  */
  OUT_FEAT_MAP,    /**< Output Feature Map */
  WT_MAP,          /**< Wight Feature Map */
  BUFTYPE_TOTAL
} eBufferName;

/**
 *  @enum       eComputeCycleCategory
 *  @brief      Enumeration for different type of compute cycles
 *
 */
typedef enum
{
  CORERAW = 0,    /**< Raw cycles of core loop */
  COREL2,         /**< Cycles of core loop including L2 conflict*/
  SETUPOH,        /**< Overhead cycles of setup in outer loop*/
  COMPUTE,        /**< Total compute cycles = setup + core loop */
  COMP_TYPES      /**< Total types of compute cycles being categorized */
} eComputeCycleCategory;

/**
 *  @enum       eIOCycleCategory
 *  @brief      Enumeration for different type of IO cycles
 *
 */
typedef enum
{
  DDRACCESS = 0 , /**< Equivalent cycles for DDR access */
  MSMCACCESS,     /**< Equivalent cycles for MSMC access */
  IO,             /**< Total IO cycles (MSMC/DDR) */
  IO_TYPES        /**< Total types of IO cycles being categorized */
} eIOCycleCategory;

/**
 *  @enum   eOpType
 *  @brief  Enumeration for different type of operations
 *
 */
typedef enum
{
  OPTYPE_VEC = 0, /**< Vector Type operations*/
  OPTYPE_MAT,     /**< Matrix Type operations*/
  OPTYPE_TOTAL,   /**< Total Operations*/
  OPTYPE_MAT_CONV,
  OPTYPE_MAT_DECONV,
  OPTYPE_MAT_DWSCONV,
  OPTYPE_MAT_FC,
  OPTYPE_VEC_RELU,
  OPTYPE_VEC_POOL_3x3_S1,
  OPTYPE_VEC_POOL_3x3_S2,
  OPTYPE_VEC_POOL_OTHERS,
  OPTYPE_VECS_DUMMY,
  OPTYPE_VECS_OTHERS,
  OPTYPE_MAX
} eOpType ;

typedef enum
{
  CANT_OVERWRITE,                 /*Overwrite not allowed to any of the inputs*/
  CAN_OVERWRITE,                  /*Overwrite allowed to any of the inputs*/
  CAN_OVERWRITE_ONLY_FIRST_INPUT, /*Overwrite allowed only to first input  buffer*/
  OVERWRITE_TYPES_MAX
} eOverwriteType ;
/** @} */ // end of group

#endif
