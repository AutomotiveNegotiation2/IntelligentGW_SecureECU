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
*  @file     DSPLIB_sqrAdd.c
*
*  @brief
*
*  @version  0.1 - Oct 2022 : Initial Version [AB]
*            
*******************************************************************************
*/

#include "DSPLIB_sqrAdd_priv.h"

int32_t DSPLIB_sqrAdd_getHandleSize(
        DSPLIB_sqrAdd_InitArgs *pKerInitArgs)
{
  int32_t privBufSize = sizeof(DSPLIB_sqrAdd_PrivArgs);
  return privBufSize ;
}

DSPLIB_STATUS DSPLIB_sqrAdd_init_checkParams(
              DSPLIB_kernelHandle handle,
              const DSPLIB_bufParams1D_t * bufParamsIn,
              const DSPLIB_bufParams1D_t * bufParamsOut,
              const DSPLIB_sqrAdd_InitArgs *pKerInitArgs)
{
   DSPLIB_STATUS status  = DSPLIB_SUCCESS;

#if DSPLIB_DEBUGPRINT
   printf("Enter DSPLIB_sqrAdd_init_checkParams\n");
#endif
   if(handle == NULL) {
      status = DSPLIB_ERR_NULL_POINTER;
   }

   if (status == DSPLIB_SUCCESS) {
      if ((bufParamsIn->data_type != DSPLIB_INT16) &&
          (bufParamsIn->data_type != DSPLIB_INT32) &&
          (bufParamsIn->data_type != DSPLIB_INT8)  &&
          (bufParamsIn->data_type != DSPLIB_FLOAT32) )        {
         status = DSPLIB_ERR_INVALID_TYPE;
      } else if (bufParamsIn->data_type != bufParamsOut->data_type) {
         status = DSPLIB_ERR_INVALID_TYPE;
      } else {
         /* Nothing to do here */
      }
   }

   return status;
}


DSPLIB_STATUS DSPLIB_sqrAdd_exec_checkParams(
  DSPLIB_kernelHandle handle,
  const void *restrict pIn,
  const void *restrict pOut)
{
  DSPLIB_STATUS status;

#if DSPLIB_DEBUGPRINT
   printf("Enter DSPLIB_sqrAdd_exec_checkParams\n");
#endif
   if ((pIn == NULL) || (pOut == NULL) ) {
      status = DSPLIB_ERR_NULL_POINTER;
   } else {
      status  = DSPLIB_SUCCESS ;
   }

  return status ;
}

DSPLIB_STATUS DSPLIB_sqrAdd_init(
              DSPLIB_kernelHandle handle,
              DSPLIB_bufParams1D_t * bufParamsIn,
              DSPLIB_bufParams1D_t * bufParamsOut,
              const DSPLIB_sqrAdd_InitArgs *pKerInitArgs)
{
   DSPLIB_STATUS status = DSPLIB_SUCCESS;
   DSPLIB_sqrAdd_PrivArgs *pKerPrivArgs =
   (DSPLIB_sqrAdd_PrivArgs*) handle ;
   
#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT Enter DSPLIB_sqrAdd_init\n");
#endif
   pKerPrivArgs->blockSize = pKerInitArgs->dataSize;
   
#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT DSPLIB_sqrAdd_init pKerPrivArgs->blockSize %d bufParamsIn->data_type %d\n", pKerPrivArgs->blockSize, bufParamsIn->data_type);
#endif

   if (pKerInitArgs->funcStyle == DSPLIB_FUNCTION_NATC)
   {
      if (bufParamsIn->data_type == DSPLIB_FLOAT32) {
          pKerPrivArgs->execute =
             DSPLIB_sqrAdd_exec_cn<float, float, DSPLIB_FLOAT32>;
      } else if (bufParamsIn->data_type == DSPLIB_FLOAT64) {
          pKerPrivArgs->execute =
             DSPLIB_sqrAdd_exec_cn<double, double, DSPLIB_FLOAT64>;
      } else if (bufParamsIn->data_type == DSPLIB_INT8) {
          pKerPrivArgs->execute =
             DSPLIB_sqrAdd_exec_cn<int8_t, long, DSPLIB_INT8>;
      }
      else {
         status = DSPLIB_ERR_INVALID_TYPE;
#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT  CP 2 status %d\n", status);
#endif
      }
   } else {
      if (bufParamsIn->data_type == DSPLIB_FLOAT32) {
#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT bufParamsIn->data_type == DSPLIB_FLOAT32\n");
#endif
         pKerPrivArgs->execute =
            DSPLIB_sqrAdd_exec_ci<float, DSPLIB_FLOAT32>;
         status = DSPLIB_sqrAdd_init_ci<float>(handle, bufParamsIn, bufParamsOut, pKerInitArgs);
      } else if (bufParamsIn->data_type == DSPLIB_FLOAT64){
         pKerPrivArgs->execute =
            DSPLIB_sqrAdd_exec_ci<double, DSPLIB_FLOAT64>;
         status = DSPLIB_sqrAdd_init_ci<double>(handle, bufParamsIn, bufParamsOut, pKerInitArgs);
      }  else {
          status = DSPLIB_ERR_INVALID_TYPE;
 #if DSPLIB_DEBUGPRINT
        printf("DSPLIB_DEBUGPRINT  CP 2 status %d\n", status);
 #endif
      }
   }
#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT  CP 3 status %d\n", status);
#endif
   return status ;
}

DSPLIB_STATUS DSPLIB_sqrAdd_exec(
   DSPLIB_kernelHandle handle,
   void *restrict pIn,
   void *restrict pOut)
{
   DSPLIB_STATUS status ;

#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT Enter DSPLIB_sqrAdd_exec\n");
#endif

   DSPLIB_sqrAdd_PrivArgs *pKerPrivArgs =
      (DSPLIB_sqrAdd_PrivArgs*) handle;

#if DSPLIB_DEBUGPRINT
       printf("DSPLIB_DEBUGPRINT pKerPrivArgs->blockSize %d\n", pKerPrivArgs->blockSize);
#endif
   status = pKerPrivArgs->execute(handle, pIn, pOut);
  
   return status ;
}
