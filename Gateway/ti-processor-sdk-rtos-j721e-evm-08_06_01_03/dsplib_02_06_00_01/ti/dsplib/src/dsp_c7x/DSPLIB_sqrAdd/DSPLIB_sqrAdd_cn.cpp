/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2016 Texas Instruments Incorporated                |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/


#include "DSPLIB_sqrAdd_priv.h"

template <typename dataType, typename accumulateType, int32_t dataIn>
DSPLIB_STATUS DSPLIB_sqrAdd_exec_cn(DSPLIB_kernelHandle handle,
                                    void *restrict pIn,
                                    void *restrict pOut)
{
   DSPLIB_STATUS    status = DSPLIB_SUCCESS;

   DSPLIB_sqrAdd_PrivArgs *pKerPrivArgs = (DSPLIB_sqrAdd_PrivArgs *) handle;
   uint32_t      blockSize           = pKerPrivArgs->blockSize;

#if DSPLIB_DEBUGPRINT
   printf("Enter DSPLIB_sqrAdd_exec_cn\n");
#endif

   dataType *pInLocal1         = (dataType *)pIn;
   dataType *pOutLocal         = (dataType *)pOut;

#if DSPLIB_DEBUGPRINT
   printf("Enter pInLocal1 %p pOut %p\n", pInLocal1, pOut);
#endif

   dataType a;
   accumulateType out;
   for (int32_t counter = 0; counter < blockSize; counter++) {
      a = *pInLocal1++;
#if DSPLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d a %f\n", counter, a);
#endif

    out += a * a;
   }
   *pOutLocal = out;

#if DSPLIB_DEBUGPRINT
   printf("DSPLIB_DEBUGPRINT DSPLIB_sqrAdd_exec_cn result %lf\n", out);
#endif
   return (status);
}

// explicit inssqrAddtiation for the different data type versions
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<float, float, DSPLIB_FLOAT32>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);

template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<double, double, DSPLIB_FLOAT64>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<int8_t, long, DSPLIB_INT8>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<uint8_t, long, DSPLIB_UINT8>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<int16_t, long, DSPLIB_INT16>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<uint16_t, long, DSPLIB_UINT16>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<int32_t, long, DSPLIB_INT32>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
template DSPLIB_STATUS
         DSPLIB_sqrAdd_exec_cn<uint32_t, long, DSPLIB_UINT32>
                                            (DSPLIB_kernelHandle handle,
                                             void *restrict pIn,
                                             void *restrict pOut);
