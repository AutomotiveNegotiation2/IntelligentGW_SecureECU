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


#include "MATHLIB_tan_priv.h"

/* ======================================================================= */
/* This function returns the reciprocal of the real floating-point value   */
/* a. The return value is precisely 1/a.                                   */
/* ======================================================================= */

template <typename dataType, int32_t dataIn>
static inline float recipsp_tansp_i (dataType a)
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


   y = one/a;
//   x1 = _rcpsp(a);    dataType f = __recip(x);
//   x1 = __recip(a);
//   x1 = x1*(two - (a*x1));
//   y = x1*(two - (a*x1));

   if (a == zero) {
      y = zero;
   }

   return (y);
} /* End of recipsp_tansp_i */


/* ======================================================================== */
/* Polynomial calculation to estimate the tangent funtion.                  */
/* The polynomial used is as follows:                                       */
/*   pol = x + c2 x^3 + c4 x^5 + c6 x^7 + c8 x^9 + c10 x^11 + c12 x^13      */
/*                                                                          */
/* where x is the input, c2 through c12 are the corresponding coefficients  */
/* to the polynomial, and pol is the result of the polynomial. This         */
/* polynomial only covers inputs in the range [0, PI/4].                    */
/* ======================================================================== */

template <typename dataType, int32_t dataIn>
static inline dataType pol_est_tansp_i (dataType x)
{
    dataType c12;
    dataType c10;
    dataType c8;
    dataType c6;
    dataType c4;
    dataType c2;

  /* coefficients for the polynomial for tan(x)*/
   if (dataIn == MATHLIB_FLOAT32) {
      c12  =  0.00457708084094171f;
      c10  =  0.00867365970442499f;
      c8   =  0.0236488997700456f;
      c6   =  0.0523817525811416f;
      c4   =  0.133766510899828f;
      c2   =  0.333299506194791f;
   } else {
      c12  =  0.00457708084094171;
      c10  =  0.00867365970442499;
      c8   =  0.0236488997700456;
      c6   =  0.0523817525811416;
      c4   =  0.133766510899828;
      c2   =  0.333299506194791;
   }

   dataType x2, x4, x6, x8, pol;
   dataType tmp1, tmp2;

   /* calculate the powers of x */
   x2  = x * x;
   x4  = x2 * x2;
   x6  = x2 * x4;
   x8  = x4 * x4;

   /* ====================================================================== */
   /* The polynomial calculation is done in two seperate parts.              */
   /*   tmp1 =  c2 x^2 + c4 x^4 + c6 x^6 + c8 x^8                            */
   /*   tmp2 =  c10 x^10 + c12 x^12                                          */
   /* In order to reduce the number of multiplications x is factored out of  */
   /* the polynomial and multiplied by later.                                */
   /* ====================================================================== */

   tmp1 = ((c8 * x8) + (c6 * x6))+ ((c4 * x4) + (c2 * x2));
   tmp2 = x8 * ((c10 * x2) + (c12 * x4));

   pol = ((tmp1 + tmp2) * x) + x;

#if MATHLIB_DEBUGPRINT
//   static int32_t i = 0;
//      if (i == 0)
//         printf("y > pi4 i %d x %f\n", i, pol);
//      i++;
#endif

   return pol;
} /* End of pol_est_tansp_i */

template <typename dataType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_tan_exec_cn(void *restrict pIn,
                                     void *restrict pOut,
                                     int32_t blockSize)
{
   MATHLIB_STATUS    status = MATHLIB_SUCCESS;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_tan_exec_cn\n");
#endif

   dataType *pInLocal          = (dataType *)pIn;
   dataType *pOutLocal         = (dataType *)pOut;

#if MATHLIB_DEBUGPRINT
//   printf("Enter pInLocal %p  pOut %p\n", pInLocal, pOut);
#endif
   dataType pi4;
   dataType pi2_h;
   dataType pi2_l;
   dataType pi;
   dataType invPI;
   dataType C1;
   dataType C2;
   dataType C3;
   dataType one;
   dataType zero;

   if (dataIn == MATHLIB_FLOAT32) {
       pi4   =  0.785398163f;             /* pi/4 */
       pi2_h =  1.570796f;
       pi2_l =  3.26794896476912e-7f;     /* pi2_h + pi2_l = pi/2 */
       pi    =  3.14159265358979f;
       C1    =  3.140625f;
       C2    =  9.676535e-4f;
       C3    =  8.97930618748433e-11f;    /* C1 + C2 + C3 = PI */
       invPI =  0.318309886183791f;        /* 1/pi */
       one   =  1.0f;
       zero  =  0.0f;


   } else {
       pi4   =  0.785398163;             /* pi/4 */
       pi2_h =  1.570796;
       pi2_l =  3.26794896476912e-7;     /* pi2_h + pi2_l = pi/2 */
       pi    =  3.14159265358979;
       C1    =  3.140625;
       C2    =  9.676535e-4;
       C3    =  8.97930618748433e-11;    /* C1 + C2 + C3 = PI */
       invPI =  0.318309886183791;        /* 1/pi */
       one   =  1.0;
       zero  =  0.0;
   }

   dataType sign  =  one;

   dataType a, res, y, temp;
   int N;

   for (int32_t counter = 0; counter < blockSize; counter++) {
      a = *pInLocal++;
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d a %f\n", counter, a);
#endif
      /* extract multiples of pi */
      temp =  a * invPI;
      N = (int32_t)(temp);                           /* N = multiple of pi in x  */
      y = ((a - ((dataType)N * C1)) - ((dataType)N * C2)) - ((dataType) N * C3);
      sign  =  one;
      if(y > pi2_h){
         y = y - pi;                               /* x is in the range [-pi/2, pi/2] */
      }
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d y minus pi %f\n", counter, y);
#endif
      if(y < zero){
         sign = -sign;                             /* sign variable */
         y = -y;
      }
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d y %f sign %f\n", counter, y, sign);
#endif
      /* calculate tan(y) */
      if (y > pi4){                                /* |y| > pi/4 */
         y = (pi2_h - y) + pi2_l;                  /* pi/2 - y */
#if MATHLIB_DEBUGPRINT
//      if (counter <= 8)
//         printf("y > pi4 counter %d y %f\n", counter, y);
#endif
         if (dataIn == MATHLIB_FLOAT32) {
            temp = (dataType)pol_est_tansp_i<float, MATHLIB_FLOAT32>(y);
            res = recipsp_tansp_i<float, MATHLIB_FLOAT32>(temp);              /* 1/tan(pi/2 - y) */
#if MATHLIB_DEBUGPRINT
//      if (counter <= 8)
//         printf("y > pi4 counter %d temp %f res %f\n", counter, temp, res);
#endif
         } else if (dataIn == MATHLIB_FLOAT64) {
            temp = (dataType)pol_est_tansp_i<double, MATHLIB_FLOAT64>(y);
            res = recipsp_tansp_i<double, MATHLIB_FLOAT64>(temp);              /* 1/tan(pi/2 - y) */
         } else { }
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("if counter %d y %f\n", counter, res);
#endif
      }
      else {                                       /* |y| <= pi/4 */
         if (dataIn == MATHLIB_FLOAT32) {
            res = (dataType)pol_est_tansp_i<float, MATHLIB_FLOAT32>(y);
         } else if (dataIn == MATHLIB_FLOAT64) {
            res = (dataType)pol_est_tansp_i<double, MATHLIB_FLOAT64>(y);
         } else { }
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("else counter %d y %f\n", counter, res);
#endif
      }

#if MATHLIB_DEBUGPRINT
//      if (counter <= 8)
//         printf("counter %d y %f sign %f\n", counter, res, sign);
#endif
      res = res * sign;                           /* sign for Quadrant 2 & 4 */
#if MATHLIB_DEBUGPRINT
      if (counter <= 8)
         printf("counter %d res %f\n", counter, res);
#endif
      *pOutLocal++ = res;
   }
   return (status);
}

// explicit instantiation for the different data type versions
template MATHLIB_STATUS
         MATHLIB_tan_exec_cn<float, MATHLIB_FLOAT32>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);

template MATHLIB_STATUS
         MATHLIB_tan_exec_cn<double, MATHLIB_FLOAT64>
                                            (void *restrict pIn,
                                             void *restrict pOut,
                                             int32_t blockSize);
