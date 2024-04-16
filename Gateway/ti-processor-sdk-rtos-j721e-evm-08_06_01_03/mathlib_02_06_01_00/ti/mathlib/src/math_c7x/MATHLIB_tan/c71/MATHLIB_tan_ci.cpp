/******************************************************************************/
/*!
 * \file MATHLIB_tan.c
 */
/* Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

 /******************************************************************************
  * Version 1.0  Date 10/2/22      Author: Asheesh Bhardwaj
  *****************************************************************************/

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

#include "../../../common/c71/MATHLIB_inlines.h"
#include "../MATHLIB_tan_priv.h"

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

void MATHLIB_tan_perfEst (MATHLIB_kernelHandle         handle,
                                         const MATHLIB_bufParams2D_t *bufParamsIn,
                                         const MATHLIB_bufParams1D_t *bufParamsFilterCoeff,
                                         const MATHLIB_bufParams1D_t *bufParamsFilterVar,
                                         const MATHLIB_bufParams2D_t *bufParamsOut,
                                         uint64_t *                  archCycles,
                                         uint64_t *                  estCycles)
{
   return;
}


/*******************************************************************************
 *
 * EXECUTION FUNCTIONS
 *
 ******************************************************************************/
template <typename dataType, typename vecType, int32_t dataIn>
static inline vecType recipsp_tansp_i (vecType a)
{
   vecType two, one, zero;

   if (dataIn == MATHLIB_FLOAT32) {
       two  = 2.0f;
       one  = 1.0f;
       zero = 0.0f;
   } else if (dataIn == MATHLIB_FLOAT64) {
       two  = (vecType)2.0;
       one  = (vecType)1.0;
       zero = (vecType)0.0;
   } else { }

   vecType x1, y;

   x1 = __recip(a);
   x1 = x1*(two - (a*x1));
   y = x1*(two - (a*x1));

//   if (a == zero) {
//      y = zero;
//   }
   __vpred cmp_eqzero = __cmp_eq_pred((vecType)a, zero);
    y = __select(cmp_eqzero, zero, y);

   return (y);
} /* End of recipsp_tansp_i */

template <typename dataType, typename vecType, int32_t dataIn>
static inline vecType pol_est_tansp_i (vecType x)
{
    vecType c12;
    vecType c10;
    vecType c8;
    vecType c6;
    vecType c4;
    vecType c2;

  /* coefficients for the polynomial for tan(x)*/
   if (dataIn == MATHLIB_FLOAT32) {
      c12  =  0.00457708084094171f;
      c10  =  0.00867365970442499f;
      c8   =  0.0236488997700456f;
      c6   =  0.0523817525811416f;
      c4   =  0.133766510899828f;
      c2   =  0.333299506194791f;
   } else if (dataIn == MATHLIB_FLOAT64){
      c12  =  (vecType)0.00457708084094171;
      c10  =  (vecType)0.00867365970442499;
      c8   =  (vecType)0.0236488997700456;
      c6   =  (vecType)0.0523817525811416;
      c4   =  (vecType)0.133766510899828;
      c2   =  (vecType)0.333299506194791;
   } else {}

   vecType x2, x4, x6, x8, pol;
   vecType tmp1, tmp2;

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

   return pol;
} /* End of pol_est_tansp_i */

template <typename dataType, typename intType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_tan_exec_ci(void *restrict pIn,
                                     void *restrict pOut,
                                     int32_t blockSize)
{
   __SE_TEMPLATE_v1 se0Params;
   __SA_TEMPLATE_v1 sa0Params;

   __SE_ELETYPE  SE_ELETYPE;
   __SE_VECLEN   SE_VECLEN;
   __SA_VECLEN   SA_VECLEN;

   dataType *restrict pInLocal          = (dataType *)pIn;
   dataType *restrict pOutLocal         = (dataType *)pOut;

#if MATHLIB_DEBUGPRINT
   printf("Enter MATHLIB_tan_exec_ci\n");
#endif

   typedef typename c7x::make_full_vector<dataType>::type vec;
   int32_t eleCount       = c7x::element_count_of<vec>::value;
   SE_VECLEN              = c7x::se_veclen<vec>::value;
   SA_VECLEN              = c7x::sa_veclen<vec>::value;
   SE_ELETYPE             = c7x::se_eletype<vec>::value;

   vec input;
   vec filter;

#if MATHLIB_DEBUGPRINT
//   printf("Enter pInLocal %p\n", pInLocal);
#endif

   /**********************************************************************/
   /* Prepare streaming engine 1 to fetch the input                      */
   /**********************************************************************/
   se0Params = __gen_SE_TEMPLATE_v1 ();

   se0Params.ICNT0         = blockSize;
   se0Params.ICNT1         = 1;
   se0Params.DIM1          = blockSize;
   se0Params.ELETYPE       = SE_ELETYPE;
   se0Params.VECLEN        = SE_VECLEN;
   se0Params.DIMFMT        = __SE_DIMFMT_2D;

   /**********************************************************************/
   /* Prepare SA template to store output                                */
   /**********************************************************************/
   sa0Params = __gen_SA_TEMPLATE_v1 ();

   sa0Params.ICNT0         = blockSize;
   sa0Params.DIM1          = blockSize;
   sa0Params.VECLEN        = SA_VECLEN;
   sa0Params.DIMFMT        = __SA_DIMFMT_1D;

#if MATHLIB_DEBUGPRINT
//   printf("Before SE0_Open\n");
#endif
   // Input samples
   __SE0_OPEN(pInLocal, se0Params);

#if MATHLIB_DEBUGPRINT
//   printf("after SE0_Open\n");
#endif

  // Output samples
   __SA0_OPEN(sa0Params);

#if MATHLIB_DEBUGPRINT
//   printf("Before SA0_Open\n");
#endif

#if MATHLIB_DEBUGPRINT
//            printf("MATHLIB_DEBUGPRINT blockSize %d\n", blockSize);
#endif


   vec pi4;
   vec pi2_h;
   vec pi2_l;
   vec pi;
   vec invPI;
   vec C1;
   vec C2;
   vec C3;
   vec one;
   vec zero;
   vec negativeOne = (vec)-1;

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
      negativeOne = -1.0f;
   } else if (dataIn == MATHLIB_FLOAT64){
      pi4   =  (vec)0.785398163;             /* pi/4 */
      pi2_h =  (vec)1.570796;
      pi2_l =  (vec)3.26794896476912e-7;     /* pi2_h + pi2_l = pi/2 */
      pi    =  (vec)3.14159265358979;
      C1    =  (vec)3.140625;
      C2    =  (vec)9.676535e-4;
      C3    =  (vec)8.97930618748433e-11;    /* C1 + C2 + C3 = PI */
      invPI =  (vec)0.318309886183791;        /* 1/pi */
      one   =  (vec)1.0;
      zero  =  (vec)0.0;
      negativeOne = (vec)-1.0;
   } else {}

   vec sign  =  one;

   vec a, res, res_gtPI4, y, temp, temp_gtPI4;

   typedef typename c7x::make_full_vector<intType>::type int_vec;
   int_vec N;

   for (int32_t counter = 0; counter < blockSize; counter += eleCount) {
      vec a = c7x::strm_eng<0, vec>::get_adv();
      /* extract multiples of pi */
      temp =  a * invPI;

      N = c7x::convert<int_vec>(temp);                           /* N = multiple of pi in x  */
      y = ((a - (c7x::convert<vec>(N) * C1)) - (c7x::convert<vec>(N) * C2)) - (c7x::convert<vec>(N) * C3);

//       if(y > pi2_h){
//          y = y - pi;                               /* x is in the range [-pi/2, pi/2] */
//       }

      vec yminusPi = y - pi;
      __vpred cmp_gt = __cmp_le_pred((vec)pi2_h, y);
      y = __select(cmp_gt, yminusPi, y);

//       if(y < zero){
//          sign = -sign;                             /* sign variable */
//          y = -y;
//       }
      vec negativeY =  -y;
      __vpred cmp_zero = __cmp_lt_pred(y, zero);
      y = __select(cmp_zero, negativeY, y);

      vec Sign_vec = __select(cmp_zero, negativeOne, sign);

#if MATHLIB_DEBUGPRINT
      if (counter == 0) {
         MATHLIB_debugPrintVector(Sign_vec);
      }
#endif
      __vpred cmp_yPI4 = __cmp_le_pred(y, pi4);

#if MATHLIB_DEBUGPRINT
      if (counter == 0) {
         printf("%016llX\n", cmp_yPI4);
         MATHLIB_debugPrintVector(y);
         MATHLIB_debugPrintVector(pi4);
      }
#endif

      vec y_gtPI4 = (pi2_h - y) + pi2_l;                  /* pi/2 - y */

      if (dataIn == MATHLIB_FLOAT32) {
         temp_gtPI4 = (vec)pol_est_tansp_i<float, vec, MATHLIB_FLOAT32>(y_gtPI4);
         res_gtPI4 = recipsp_tansp_i<float, vec, MATHLIB_FLOAT32>(temp_gtPI4);              /* 1/tan(pi/2 - y) */
#if MATHLIB_DEBUGPRINT
      if (counter == 0) {
         MATHLIB_debugPrintVector(temp_gtPI4);
         MATHLIB_debugPrintVector(temp_gtPI4);
         MATHLIB_debugPrintVector(res_gtPI4);
      }
#endif

      } else if (dataIn == MATHLIB_FLOAT64) {
         temp_gtPI4 = (vec)pol_est_tansp_i<double, vec, MATHLIB_FLOAT64>(y_gtPI4);
         res_gtPI4 = recipsp_tansp_i<double, vec, MATHLIB_FLOAT64>(temp_gtPI4);              /* 1/tan(pi/2 - y) */
      } else {}

      if (dataIn == MATHLIB_FLOAT32) {
         res = (vec)pol_est_tansp_i<float, vec, MATHLIB_FLOAT32>(y);
      } else if (dataIn == MATHLIB_FLOAT64){
         res = (vec)pol_est_tansp_i<double, vec, MATHLIB_FLOAT64>(y);
      } else {}
#if MATHLIB_DEBUGPRINT
      if (counter == 0) {
         MATHLIB_debugPrintVector(res_gtPI4);
         MATHLIB_debugPrintVector(res);
      }
#endif
      res_gtPI4 = res_gtPI4*Sign_vec;
      res = res*Sign_vec;

      res = __select(cmp_yPI4, res, res_gtPI4);
#if MATHLIB_DEBUGPRINT
      if (counter == 0) {
          printf("2nd time %016llX\n", cmp_yPI4);
         MATHLIB_debugPrintVector(res);
      }
#endif
      __vpred tmp = c7x::strm_agen<0, vec>::get_vpred();
      vec * VB1 = c7x::strm_agen<0, vec>::get_adv(pOutLocal);

      __vstore_pred(tmp, VB1, res);

   }
   __SE0_CLOSE ();
   __SA0_CLOSE ();

   return MATHLIB_SUCCESS;
}

template MATHLIB_STATUS MATHLIB_tan_exec_ci<float, int32_t, MATHLIB_FLOAT32> (
   void *restrict pIn,
   void *restrict pOut,
   int32_t blockSize);

template MATHLIB_STATUS MATHLIB_tan_exec_ci<double, int64_t, MATHLIB_FLOAT64> (
   void *restrict pIn,
   void *restrict pOut,
   int32_t blockSize);
