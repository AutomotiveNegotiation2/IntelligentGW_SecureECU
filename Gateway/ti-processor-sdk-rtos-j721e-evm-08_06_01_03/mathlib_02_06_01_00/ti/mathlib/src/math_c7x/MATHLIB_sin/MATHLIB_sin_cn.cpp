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


#include "MATHLIB_sin_priv.h"

template <typename dataType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_sin_exec_cn(void *restrict pIn,
                                     void *restrict pOut,
                                     int32_t blockSize)
{
   MATHLIB_STATUS    status = MATHLIB_SUCCESS;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_sin_exec_cn\n");
#endif

   dataType *pInLocal          = (dataType *)pIn;
   dataType *pOutLocal         = (dataType *)pOut;

#if MATHLIB_DEBUGPRINT
   printf("Enter pInLocal %p  pOut %p\n", pInLocal, pOut);
#endif

   dataType InvPI;
   dataType One;
   dataType MAX;
   dataType Zero;
   dataType s1;
   dataType s2;
   dataType s3;
   dataType s4;
   dataType C1;
   dataType C2;

   if (dataIn == MATHLIB_FLOAT32) {
      InvPI =  0.318309886183791f;
      One   =  1.0f;
      MAX   =  1048576.0f;
      Zero  =  0.0f;
      s1    = -1.666665668e-1f;
      s2    =  8.333025139e-3f;
      s3    = -1.980741872e-4f;
      s4    =  2.601903036e-6f;
      C1    =  3.140625f;
      C2    =  9.67653589793e-4f;
   } else if (dataIn == MATHLIB_FLOAT64){
      InvPI =  0.318309886183791;
      One   =  1.0;
      MAX   =  1048576.0;
      Zero  =  0.0;
      s1    = -1.666665668e-1;
      s2    =  8.333025139e-3;
      s3    = -1.980741872e-4;
      s4    =  2.601903036e-6;
      C1    =  3.140625;
      C2    =  9.67653589793e-4;
   } else {}

   dataType a, Sign, X, Y, Z, F, G, R;
   int   N;

   for (int32_t counter = 0; counter < blockSize; counter++) {
      a = *pInLocal++;

      Sign = One;
      Y    = a;
      if (dataIn == MATHLIB_FLOAT32) {
         if (fabsf(Y) > MAX) {
              Y = Zero;
         } else {}
      } else if (dataIn == MATHLIB_FLOAT64){
         if (fabs(Y) > MAX) {
             Y = Zero;
         } else {}
      } else {}

      X = Y * InvPI;            /* X = Y * (1/PI)  */
      N = (int32_t)(X);            /* N = integer part of X  */
      Z = (dataType) N;

      if ((N % 2) != 0) {
         Sign = -Sign;           /* Quadrant 3 or 4 */
      }

      F = (Y - (Z*C1)) - (Z*C2);
      G = F * F;
      R = ((((((s4*G) + s3)*G) + s2)*G) + s1)*G;
      *pOutLocal++ = ((F + (F*R)) * Sign);

#if MATHLIB_DEBUGPRINT
      if (counter == 0)
      printf("counter %d input a = %f\n", counter, ((F + (F*R)) * Sign));
#endif
   }

   return (status);
}


// explicit instantiation for the different data type versions
template MATHLIB_STATUS
         MATHLIB_sin_exec_cn<float, MATHLIB_FLOAT32>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);

template MATHLIB_STATUS
         MATHLIB_sin_exec_cn<double, MATHLIB_FLOAT64>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);
