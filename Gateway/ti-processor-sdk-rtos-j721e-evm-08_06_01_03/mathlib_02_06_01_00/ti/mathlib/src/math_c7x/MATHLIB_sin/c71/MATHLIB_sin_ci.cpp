/******************************************************************************/
/*!
 * \file MATHLIB_sin.c
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
  * Version 1.0  Date 4/13/22      Author: Asheesh Bhardwaj
  *****************************************************************************/

/*******************************************************************************
 *
 * INCLUDES
 *
 ******************************************************************************/

#include "../../../common/c71/MATHLIB_inlines.h"
#include "../MATHLIB_sin_priv.h"

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

void MATHLIB_sin_perfEst (MATHLIB_kernelHandle         handle,
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

template <typename dataType, typename intType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_sin_exec_ci(void *restrict pIn,
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
   printf("Enter MATHLIB_sin_exec_ci\n");
#endif

   typedef typename c7x::make_full_vector<dataType>::type vec;
   int32_t eleCount       = c7x::element_count_of<vec>::value;
   SE_VECLEN              = c7x::se_veclen<vec>::value;
   SA_VECLEN              = c7x::sa_veclen<vec>::value;
   SE_ELETYPE             = c7x::se_eletype<vec>::value;

   vec input;
   vec filter;

#if MATHLIB_DEBUGPRINT
   printf("Enter pInLocal %p\n", pInLocal);
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
   printf("Before SE0_Open\n");
#endif
   // Input samples
   __SE0_OPEN(pInLocal, se0Params);

#if MATHLIB_DEBUGPRINT
   printf("after SE0_Open\n");
#endif

  // Output samples
   __SA0_OPEN(sa0Params);

#if MATHLIB_DEBUGPRINT
   printf("Before SA0_Open\n");
#endif

#if MATHLIB_DEBUGPRINT
            printf("MATHLIB_DEBUGPRINT blockSize %d\n", blockSize);
#endif


   /* Get the filter states into corresponding regs */

   vec InvPI;
   vec One;
   vec MAX;
   vec Zero;
   vec s1;
   vec s2;
   vec s3;
   vec s4;
   vec C1;
   vec C2;

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
      InvPI =  (vec)0.318309886183791;
      One   =  (vec)1.0;
      MAX   =  (vec)1048576.0;
      Zero  =  (vec)0.0;
      s1    =  (vec)-1.666665668e-1;
      s2    =  (vec)8.333025139e-3;
      s3    =  (vec)-1.980741872e-4;
      s4    =  (vec)2.601903036e-6;
      C1    =  (vec)3.140625;
      C2    =  (vec)9.67653589793e-4;
   } else { }

   vec Sign, X, Y, Z, F, G, R;

   typedef typename c7x::make_full_vector<intType>::type int_vec;

//   if (dataIn == MATHLIB_FLOAT32) {
   int_vec   N;
   int_vec   int_one = (int_vec)1;

   vec       negativeOne = (vec)-1;
   Sign = One;

#if MATHLIB_DEBUGPRINT
//      MATHLIB_debugPrintVector(negativeOne);
#endif

   for (int32_t sample = 0; sample < blockSize; sample += eleCount*3) {
//first iteration
      vec a = c7x::strm_eng<0, vec>::get_adv();
#if MATHLIB_DEBUGPRINT
//      MATHLIB_debugPrintVector(a);
#endif
//      Sign = One;
      Y    = a;

//      if (__abs(Y) > (vec)MAX) {
//       Y = Zero;
//     }
      __vpred cmp_gt = __cmp_le_pred((vec)MAX, __abs(Y));
      Y = __select(cmp_gt, Zero, Y);

      X = Y * InvPI;                    /* X = Y * (1/PI)  */
      N = c7x::convert<int_vec>(X);           /* N = integer part of X  */
      Z = c7x::convert<vec>(N);

//      if ((N % 2) != 0) {
//         Sign = -Sign;           /* Quadrant 3 or 4 */
//      }

      int_vec andN = N & int_one;
      __vpred cmp_mod = __cmp_le_pred(Zero, c7x::convert<vec>(andN));
//      vec Sign_vec = __select(cmp_mod, Sign, negativeOne);
      vec Sign_vec = __select(cmp_mod, Sign, negativeOne);

      F = (Y - (Z*C1)) - (Z*C2);
      G = F * F;

      R = ((((((s4*G) + s3)*G) + s2)*G) + s1)*G;
#if MATHLIB_DEBUGPRINT
      MATHLIB_debugPrintVector((F+ F*R) * Sign_vec);
#endif
      vec output = ((F + (F*R)) * Sign_vec);
#if MATHLIB_DEBUGPRINT
      MATHLIB_debugPrintVector(output);
#endif
      __vpred tmp = c7x::strm_agen<0, vec>::get_vpred();
      vec * VB1 = c7x::strm_agen<0, vec>::get_adv(pOutLocal);

      __vstore_pred(tmp, VB1, output);

//second iteration
      a = c7x::strm_eng<0, vec>::get_adv();
#if MATHLIB_DEBUGPRINT
//      MATHLIB_debugPrintVector(a);
#endif
//      Sign = One;
      Y    = a;
//      if (__abs(Y) > (vec)MAX) {
//       Y = Zero;
//     }
      cmp_gt = __cmp_le_pred((vec)MAX, __abs(Y));
      Y = __select(cmp_gt, Zero, Y);

      X = Y * InvPI;                    /* X = Y * (1/PI)  */
      N = c7x::convert<int_vec>(X);           /* N = integer part of X  */
      Z = c7x::convert<vec>(N);

//      if ((N % 2) != 0) {
//         Sign = -Sign;           /* Quadrant 3 or 4 */
//      }

      andN = N & int_one;
      cmp_mod = __cmp_le_pred(Zero, c7x::convert<vec>(andN));
//      Sign_vec = __select(cmp_mod, Sign, negativeOne);
      Sign_vec = __select(cmp_mod, Sign, negativeOne);

      F = (Y - (Z*C1)) - (Z*C2);
      G = F * F;
      R = ((((((s4*G) + s3)*G) + s2)*G) + s1)*G;
#if MATHLIB_DEBUGPRINT
//      MATHLIB_debugPrintVector(F*R);
#endif
      output = ((F + (F*R)) * Sign_vec);

      tmp = c7x::strm_agen<0, vec>::get_vpred();
      VB1 = c7x::strm_agen<0, vec>::get_adv(pOutLocal);

      __vstore_pred(tmp, VB1, output);

//third iteration
      a = c7x::strm_eng<0, vec>::get_adv();
#if MATHLIB_DEBUGPRINT
//      MATHLIB_debugPrintVector(a);
#endif
//      Sign = One;
      Y    = a;
//      if (__abs(Y) > (vec)MAX) {
//       Y = Zero;
//     }
      cmp_gt = __cmp_le_pred((vec)MAX, __abs(Y));
      Y = __select(cmp_gt, Zero, Y);

      X = Y * InvPI;                    /* X = Y * (1/PI)  */
      N = c7x::convert<int_vec>(X);           /* N = integer part of X  */
      Z = c7x::convert<vec>(N);

//      if ((N % 2) != 0) {
//         Sign = -Sign;           /* Quadrant 3 or 4 */
//      }

      andN = N & int_one;
      cmp_mod = __cmp_le_pred(Zero, c7x::convert<vec>(andN));
      Sign_vec = __select(cmp_mod, Sign, negativeOne);

      F = (Y - (Z*C1)) - (Z*C2);
      G = F * F;
      R = ((((((s4*G) + s3)*G) + s2)*G) + s1)*G;
      output = ((F + (F*R)) * Sign_vec);

      tmp = c7x::strm_agen<0, vec>::get_vpred();
      VB1 = c7x::strm_agen<0, vec>::get_adv(pOutLocal);

      __vstore_pred(tmp, VB1, output);

#if MATHLIB_DEBUGPRINT
//      MATHLIB_debugPrintVector(a);
//      MATHLIB_debugPrintVector(output);
#endif
   }
   __SE0_CLOSE ();
   __SA0_CLOSE ();

   return MATHLIB_SUCCESS;
}

template MATHLIB_STATUS MATHLIB_sin_exec_ci<float, int32_t, MATHLIB_FLOAT32> (
   void *restrict pIn,
   void *restrict pOut,
   int32_t blockSize);

template MATHLIB_STATUS MATHLIB_sin_exec_ci<double, int64_t, MATHLIB_FLOAT64> (
   void *restrict pIn,
   void *restrict pOut,
   int32_t blockSize);
