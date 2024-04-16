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
*  @file     MATHLIB_cos.c
*
*  @brief    DFT computation
*
*  @version  0.1 - Jan 2018 : Initial Version
*            
*******************************************************************************
*/

#include "MATHLIB_cos_priv.h"

int32_t MATHLIB_cos_getHandleSize(
        MATHLIB_cos_InitArgs *pKerInitArgs)
{
  int32_t privBufSize = sizeof(MATHLIB_cos_PrivArgs);
  return privBufSize ;
}

MATHLIB_STATUS MATHLIB_cos_init_checkParams(
              MATHLIB_kernelHandle handle,
              const MATHLIB_bufParams2D_t * bufParamsIn,
              const MATHLIB_bufParams2D_t * bufParamsOut,
              const MATHLIB_cos_InitArgs *pKerInitArgs)
{
   MATHLIB_STATUS status  = MATHLIB_SUCCESS;
//   MATHLIB_bufParams1D_t bufParamsFilterCoeffLocal;
//   MATHLIB_bufParams2D_t bufParamsInLocal, bufParamsOutLocal, bufParamsFilterVarLocal;


#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_cos_init_checkParams\n");
#endif
   if(handle == NULL) {
      status = MATHLIB_ERR_NULL_POINTER;
   }

   if (status == MATHLIB_SUCCESS) {
      if ((bufParamsIn->data_type != MATHLIB_INT16) &&
          (bufParamsIn->data_type != MATHLIB_INT32) &&
          (bufParamsIn->data_type != MATHLIB_INT8)  &&
          (bufParamsIn->data_type != MATHLIB_FLOAT32) )        {
         status = MATHLIB_ERR_INVALID_TYPE;
      } else if (bufParamsIn->data_type != bufParamsOut->data_type) {
         status = MATHLIB_ERR_INVALID_TYPE;
      } else {
         /* Nothing to do here */
      }
   }

   return status;
}


MATHLIB_STATUS MATHLIB_cos_exec_checkParams(
  MATHLIB_kernelHandle handle,
  const void *restrict pIn,
  const void *restrict pOut)
{
  MATHLIB_STATUS status;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_cos_exec_checkParams\n");
#endif
   if ((pIn == NULL) || (pOut == NULL) ) {
      status = MATHLIB_ERR_NULL_POINTER;
   } else {
      status  = MATHLIB_SUCCESS ;
   }

  return status ;
}

MATHLIB_STATUS MATHLIB_cos_init(
              MATHLIB_kernelHandle handle,
              MATHLIB_bufParams1D_t * bufParamsIn,
              MATHLIB_bufParams1D_t * bufParamsOut,
              const MATHLIB_cos_InitArgs *pKerInitArgs)
{
   MATHLIB_STATUS status = MATHLIB_SUCCESS;
   MATHLIB_cos_PrivArgs *pKerPrivArgs =
   (MATHLIB_cos_PrivArgs*) handle ;
   
#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT Enter MATHLIB_cos_init\n");
#endif
   pKerPrivArgs->blockSize = pKerInitArgs->dataSize;
   
   int32_t ele_size;

#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT MATHLIB_cos_init pKerPrivArgs->blockSize %d bufParamsIn->data_type %d\n", pKerPrivArgs->blockSize, bufParamsIn->data_type);
#endif

   if (bufParamsIn->data_type == MATHLIB_FLOAT32) {
       ele_size = 4;
   } else if (bufParamsIn->data_type == MATHLIB_FLOAT32) {
       ele_size = 8;
   } else {
       status = MATHLIB_ERR_INVALID_TYPE;
#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT  CP 1 status %d\n", status);
#endif
   }

   if (pKerInitArgs->funcStyle == MATHLIB_FUNCTION_NATC)
   {
      if (bufParamsIn->data_type == MATHLIB_FLOAT32) {
          pKerPrivArgs->execute =
             MATHLIB_cos_exec_cn<float, MATHLIB_FLOAT32>;
      } else if (bufParamsIn->data_type == MATHLIB_FLOAT64) {
          pKerPrivArgs->execute =
             MATHLIB_cos_exec_cn<double, MATHLIB_FLOAT64>;
      } else {
         status = MATHLIB_ERR_INVALID_TYPE;
#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT  CP 2 status %d\n", status);
#endif
      }
   } else {
      if (bufParamsIn->data_type == MATHLIB_FLOAT32) {
#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT bufParamsIn->data_type == MATHLIB_FLOAT32\n");
#endif
         pKerPrivArgs->execute =
            MATHLIB_cos_exec_ci<float, int32_t, MATHLIB_FLOAT32>;
      } else {
         pKerPrivArgs->execute =
            MATHLIB_cos_exec_ci<double, int64_t, MATHLIB_FLOAT64>;
      }
   }
#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT  CP 3 status %d\n", status);
#endif
   return status ;
}

MATHLIB_STATUS MATHLIB_cos_exec(
   MATHLIB_kernelHandle handle,
   void *restrict pIn,
   void *restrict pOut)
{
   MATHLIB_STATUS status ;

#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT Enter MATHLIB_cos_exec\n");
#endif

   MATHLIB_cos_PrivArgs *pKerPrivArgs =
      (MATHLIB_cos_PrivArgs*) handle;

   int32_t blockSize = pKerPrivArgs->blockSize;
#if MATHLIB_DEBUGPRINT
       printf("MATHLIB_DEBUGPRINT pKerPrivArgs->blockSize %d\n", pKerPrivArgs->blockSize);
#endif
   status = pKerPrivArgs->execute(pIn, pOut, blockSize);
  
   return status ;
}
