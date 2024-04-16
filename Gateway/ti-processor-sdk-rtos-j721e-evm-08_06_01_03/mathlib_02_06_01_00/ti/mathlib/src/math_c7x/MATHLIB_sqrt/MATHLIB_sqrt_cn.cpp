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


#include "MATHLIB_sqrt_priv.h"

/* ======================================================================= */
/* This function returns the reciprocal of the real floating-point value   */
/* a. The return value is precisely 1/a.                                   */
/* ======================================================================= */

template <typename dataType, int32_t dataIn>
static inline float recip_sqrt (dataType a)
{
   dataType half, OneP5, zero, maxValue;

   dataType x, y;

   if (dataIn == MATHLIB_FLOAT32) {
       half  = 0.5f;
       OneP5 = 1.5f;
       zero  = 0.0f;
       maxValue = FLT_MAX;
   } else {
       half  = 0.5;
       OneP5 = 1.5;
       zero  = 0.0;
       maxValue = DBL_MAX;
   }
#if RTS
   y = sqrt(a);
#else
   x = __recip_sqrt(a); /* compute square root reciprocal */

   #pragma UNROLL(1)   /* PRAGMA: do not unroll this loop */
   for(int32_t i=0; i< 2; i++){
     x = x * (OneP5 - (a * x * x * half));
   }
   y = a * x;
#endif

   if (a <= zero) {
     y = zero;
   }
   if (a > maxValue) {
     y = maxValue;
   }

   return (y);

} /* End of recip_sqrt */


template <typename dataType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_sqrt_exec_cn(void *restrict pIn,
                                     void *restrict pOut,
                                     int32_t blockSize)
{
   MATHLIB_STATUS    status = MATHLIB_SUCCESS;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_sqrt_exec_cn\n");
#endif

   dataType *pInLocal          = (dataType *)pIn;
   dataType *pOutLocal         = (dataType *)pOut;

#if MATHLIB_DEBUGPRINT
//   printf("Enter pInLocal %p  pOut %p\n", pInLocal, pOut);
#endif

   dataType a, res;

   for (int32_t counter = 0; counter < blockSize; counter++) {
      a = *pInLocal++;
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d a %f\n", counter, a);
#endif
      if (dataIn == MATHLIB_FLOAT32) {
         res = (dataType)recip_sqrt<float, MATHLIB_FLOAT32>(a);
      } else if (dataIn == MATHLIB_FLOAT64) {
         res = (dataType)recip_sqrt<double, MATHLIB_FLOAT64>(a);
      } else { }
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d y %f\n", counter, res);
#endif

      *pOutLocal++ = res;
   }
   return (status);
}

// explicit inssqrttiation for the different data type versions
template MATHLIB_STATUS
         MATHLIB_sqrt_exec_cn<float, MATHLIB_FLOAT32>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);

template MATHLIB_STATUS
         MATHLIB_sqrt_exec_cn<double, MATHLIB_FLOAT64>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);
