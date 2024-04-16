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


#include "MATHLIB_cos_priv.h"

template <typename dataType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_cos_exec_cn(void *restrict pIn,
                                     void *restrict pOut,
                                     int32_t blockSize)
{
   MATHLIB_STATUS    status = MATHLIB_SUCCESS;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_cos_exec_cn\n");
#endif

   dataType *pInLocal          = (dataType *)pIn;
   dataType *pOutLocal         = (dataType *)pOut;

#if MATHLIB_DEBUGPRINT
   printf("Enter pInLocal %p  pOut %p\n", pInLocal, pOut);
#endif

   dataType InvPI;
   dataType HalfPI;
   dataType One;
   dataType MAX;
   dataType MIN;
   dataType Zero;
   dataType s1;
   dataType s2;
   dataType s3;
   dataType s4;
   dataType C1;
   dataType C2;

   if (dataIn == MATHLIB_FLOAT32) {
      InvPI =  0.318309886183791f;
      HalfPI =  1.5707963268f;
      One   =  1.0f;
      MAX   =  1048576.0f;
      MIN   =  2.4414062e-4f;
      Zero  =  0.0f;
      s1    = -1.666665668e-1f;
      s2    =  8.333025139e-3f;
      s3    = -1.980741872e-4f;
      s4    =  2.601903036e-6f;
      C1    =  3.140625f;
      C2    =  9.67653589793e-4f;
   } else if (dataIn == MATHLIB_FLOAT64){
      InvPI =  0.318309886183791;
      HalfPI =  1.5707963268;
      One   =  1.0;
      MAX   =  1048576.0;
      MIN   =  2.4414062e-4;
      Zero  =  0.0;
      s1    = -1.666665668e-1;
      s2    =  8.333025139e-3;
      s3    = -1.980741872e-4;
      s4    =  2.601903036e-6;
      C1    =  3.140625;
      C2    =  9.67653589793e-4;
   } else {}

   dataType a, Sign, X, Y, Z, F, G, R, res;
   int   N;

   for (int32_t counter = 0; counter < blockSize; counter++) {
      a = *pInLocal++;

      if (dataIn == MATHLIB_FLOAT32) {
          Y = fabsf(a) + HalfPI;
      } else if (dataIn == MATHLIB_FLOAT64){
          Y = fabs(a) + HalfPI;
      } else {}
#if MATHLIB_DEBUGPRINT
      if (counter <= 17) {
          printf("counter %d Y %f\n", counter, Y);
      }
#endif
      if (Y > MAX) {
        Y = HalfPI;
      }
      Sign = One;
      /*-----------------------------------------------------------------------*/
      /*  X = |a|/PI + 1/2                                                     */
      /*-----------------------------------------------------------------------*/
      /*  when rounded to the nearest integer yields the signedness of cos(a)  */
      /*     e.g.                                                              */
      /*  positive (rounds to odd number):  a=0 --> 1/2       a=pi/2 --> 1     */
      /*  negative (rounds to even number): a=pi -> 3/2       a=3pi/2 -> 2     */
      /*-----------------------------------------------------------------------*/

      X = Y * InvPI;            /* X = Y * (1/PI)         */
      N = (int32_t)(X);            /* N = X, rounded to nearest integer */
      Z = (dataType)N;                    /* Z = float (N)          */

      /* opposite of final sign */
      if ((N%2) != 0) {
        Sign = -Sign;           /* quad. 3 or 4   */
      }

      F = (Y - (Z*C1)) - (Z*C2);
      R = F;
#if MATHLIB_DEBUGPRINT
//      if (counter <= 17) {
//          printf("counter %d R %f\n", counter, R);
//      }
#endif

      if (F < Zero) {
        R = -R;
      }

      if (R < MIN) {
        res = R*Sign;
#if MATHLIB_DEBUGPRINT
//      if (counter <= 17) {
//          printf("R < MIN counter %d res %f\n", counter, res);
//      }
#endif
      } else {
        G = F*F;
        R = ((((((s4*G) + s3)*G) + s2)*G) + s1)*G;
        res = (F + (F*R))*Sign;
#if MATHLIB_DEBUGPRINT
//      if (counter <= 17) {
//          printf("Else R < MIN counter %d res %f\n", counter, res);
//      }
#endif
      }

      *pOutLocal++ = res;
   }

   return (status);
}


// explicit inscostiation for the different data type versions
template MATHLIB_STATUS
         MATHLIB_cos_exec_cn<float, MATHLIB_FLOAT32>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);

template MATHLIB_STATUS
         MATHLIB_cos_exec_cn<double, MATHLIB_FLOAT64>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);
