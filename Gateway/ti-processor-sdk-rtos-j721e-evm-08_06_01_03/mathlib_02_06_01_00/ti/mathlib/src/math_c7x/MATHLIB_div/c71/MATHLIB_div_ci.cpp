/******************************************************************************/
/*!
 * \file MATHLIB_div.c
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
#include "../MATHLIB_div_priv.h"

/*******************************************************************************
 *
 * DEFINES
 *
 ******************************************************************************/

void MATHLIB_div_perfEst (MATHLIB_kernelHandle         handle,
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
static inline vecType recip_div (vecType a)
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
} /* End of recip_div */


template <typename dataType, typename intType, int32_t dataIn>
MATHLIB_STATUS MATHLIB_div_exec_ci(void *restrict pIn,
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
   printf("Enter MATHLIB_div_exec_ci\n");
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

   vec res;
   for (int32_t counter = 0; counter < blockSize; counter += eleCount) {
      vec a = c7x::strm_eng<0, vec>::get_adv();

      if (dataIn == MATHLIB_FLOAT32) {
         res = (vec)recip_div<float, vec, MATHLIB_FLOAT32>(a);
      } else if (dataIn == MATHLIB_FLOAT64){
         res = (vec)recip_div<double, vec, MATHLIB_FLOAT64>(a);
      } else {}
      __vpred tmp = c7x::strm_agen<0, vec>::get_vpred();
      vec * VB1 = c7x::strm_agen<0, vec>::get_adv(pOutLocal);

      __vstore_pred(tmp, VB1, res);

   }
   __SE0_CLOSE ();
   __SA0_CLOSE ();

   return MATHLIB_SUCCESS;
}

template MATHLIB_STATUS MATHLIB_div_exec_ci<float, int32_t, MATHLIB_FLOAT32> (
   void *restrict pIn,
   void *restrict pOut,
   int32_t blockSize);

template MATHLIB_STATUS MATHLIB_div_exec_ci<double, int64_t, MATHLIB_FLOAT64> (
   void *restrict pIn,
   void *restrict pOut,
   int32_t blockSize);
