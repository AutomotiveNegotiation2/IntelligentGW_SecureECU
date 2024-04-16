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


#include "MATHLIB_div_priv.h"

/* ======================================================================= */
/* This function returns the reciprocal of the real floating-point value   */
/* a. The return value is precisely 1/a.                                   */
/* ======================================================================= */

template <typename dataType, int32_t dataIn>
static inline float recip_div (dataType a)
{
   dataType two, one, zero;

   if (dataIn == MATHLIB_FLOAT32) {
       two  = 2.0f;
       one  = 1.0f;
       zero = 0.0f;
   } else {
       two  = 2.0;
       one  = 1.0;
       zero = 0.0;
   }

   dataType x1, y;


   y = (dataType)one/a;
//   x1 = _rcpsp(a);    dataType f = __recip(x);
//   x1 = __recip(a);
//   x1 = x1*(two - (a*x1));
//   y = x1*(two - (a*x1));

   if (a == zero) {
      y = zero;
   }

   return (y);
} /* End of recipsp_divsp_i */



template <typename dataType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_div_exec_cn(void *restrict pIn,
                                     void *restrict pOut,
                                     int32_t blockSize)
{
   MATHLIB_STATUS    status = MATHLIB_SUCCESS;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_div_exec_cn\n");
#endif

   dataType *pInLocal          = (dataType *)pIn;
   dataType *pOutLocal         = (dataType *)pOut;

#if MATHLIB_DEBUGPRINT
//   printf("Enter pInLocal %p  pOut %p\n", pInLocal, pOut);
#endif

   dataType a, res;

   for (int32_t counter = 0; counter < blockSize; counter++) {
      a = *pInLocal++;
      if (dataIn == MATHLIB_FLOAT32) {
         res = (dataType)recip_div<float, MATHLIB_FLOAT32>(a);
      } else if (dataIn == MATHLIB_FLOAT64) {
         res = (dataType)recip_div<double, MATHLIB_FLOAT64>(a);
      } else { }
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("else counter %d y %f\n", counter, res);
#endif

      *pOutLocal++ = res;
   }
   return (status);
}

// explicit insdivtiation for the different data type versions
template MATHLIB_STATUS
         MATHLIB_div_exec_cn<float, MATHLIB_FLOAT32>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);

template MATHLIB_STATUS
         MATHLIB_div_exec_cn<double, MATHLIB_FLOAT64>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);
