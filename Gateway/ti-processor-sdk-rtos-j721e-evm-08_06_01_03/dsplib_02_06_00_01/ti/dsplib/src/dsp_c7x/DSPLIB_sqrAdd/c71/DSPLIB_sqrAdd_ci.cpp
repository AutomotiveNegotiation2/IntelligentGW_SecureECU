/******************************************************************************/
/*!
 * \file DSPLIB_sqrAdd.c
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

#include "../../../common/c71/DSPLIB_inlines.h"
#include "../DSPLIB_sqrAdd_priv.h"
#include <float.h>


template <typename dataType>
DSPLIB_STATUS DSPLIB_sqrAdd_init_ci (
    DSPLIB_kernelHandle                        handle,
    const DSPLIB_bufParams1D_t *               bufParamsIn,
    const DSPLIB_bufParams1D_t *               bufParamsOut,
    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs)
{
   DSPLIB_STATUS                        status = DSPLIB_SUCCESS;
   DSPLIB_sqrAdd_PrivArgs *pKerPrivArgs = (DSPLIB_sqrAdd_PrivArgs *) handle;
   uint32_t blockSize                = pKerPrivArgs->blockSize;

   __SE_TEMPLATE_v1                     se0Params;
   __SE_TEMPLATE_v1                     se1Params;
   __SA_TEMPLATE_v1                     sa0Params;

   __SE_ELETYPE  SE_ELETYPE;
   __SE_VECLEN   SE_VECLEN;
   __SA_VECLEN   SA_VECLEN;

   uint8_t *     pBlock             = pKerPrivArgs->bufPblock;

   typedef typename c7x::make_full_vector<dataType>::type vec;
   int32_t eleCount       = c7x::element_count_of<vec>::value;
   SE_VECLEN              = c7x::se_veclen<vec>::value;
   SA_VECLEN              = c7x::sa_veclen<vec>::value;
   SE_ELETYPE             = c7x::se_eletype<vec>::value;

#if DSPLIB_DEBUGPRINT
    printf("Enter eleCount %d\n", eleCount);
#endif

    int32_t blockCount     = (blockSize % eleCount == 0) ? (blockSize/eleCount) : (blockSize/eleCount) + 1;
    int32_t blockCountHalf = (blockCount % 2 == 0)? blockCount/2 : blockCount/2 + 1;

   /**********************************************************************/
   /* Prepare streaming engine 0 to fetch the input                      */
   /**********************************************************************/
   se0Params = __gen_SE_TEMPLATE_v1 ();
   uint32_t icnt0Param     = (blockSize < eleCount) ? blockSize: eleCount;
   se0Params.ICNT0         = icnt0Param;
   se0Params.ICNT1         = blockCountHalf;
   se0Params.DIM1          = eleCount*2;
   se0Params.ELETYPE       = SE_ELETYPE;
   se0Params.VECLEN        = SE_VECLEN;
   se0Params.DECDIM1_WIDTH = blockSize;
   se0Params.DECDIM1       = __SE_DECDIM_DIM1;
   se0Params.DIMFMT        = __SE_DIMFMT_2D;

   /**********************************************************************/
   /* Prepare streaming engine 1 to fetch the input                      */
   /**********************************************************************/
   se1Params = __gen_SE_TEMPLATE_v1 ();
   icnt0Param              = ((blockSize - eleCount)  < eleCount) ? (blockSize - eleCount) : eleCount;
   se1Params.ICNT0         = icnt0Param;
   se1Params.ICNT1         = blockCountHalf;
   se1Params.DIM1          = eleCount*2;
   se1Params.ELETYPE       = SE_ELETYPE;
   se1Params.VECLEN        = SE_VECLEN;
   se1Params.DECDIM1_WIDTH = blockSize - eleCount;
   se1Params.DECDIM1       = __SE_DECDIM_DIM1;
   se1Params.DIMFMT        = __SE_DIMFMT_2D;

   /**********************************************************************/
   /* Prepare SA template to store output                                */
   /**********************************************************************/
   sa0Params = __gen_SA_TEMPLATE_v1 ();

   sa0Params.ICNT0         = blockSize;
   sa0Params.DIM1          = blockSize;
   sa0Params.VECLEN        = SA_VECLEN;
   sa0Params.DIMFMT        = __SA_DIMFMT_1D;

   *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SE0_PARAM_OFFSET) = se0Params;
   *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SE1_PARAM_OFFSET) = se1Params;
   *(__SA_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SA0_PARAM_OFFSET) = sa0Params;

   return status;
}

//template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<int16_t> (
//    DSPLIB_kernelHandle                        handle,
//    const DSPLIB_bufParams1D_t *               bufParamsIn,
//    const DSPLIB_bufParams1D_t *               bufParamsOut,
//    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);
//
//template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<uint16_t> (
//    DSPLIB_kernelHandle                        handle,
//    const DSPLIB_bufParams1D_t *               bufParamsIn,
//    const DSPLIB_bufParams1D_t *               bufParamsOut,
//    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);
//
//template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<int32_t> (
//    DSPLIB_kernelHandle                        handle,
//    const DSPLIB_bufParams1D_t *               bufParamsIn,
//    const DSPLIB_bufParams1D_t *               bufParamsOut,
//    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);
//
//template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<uint32_t> (
//    DSPLIB_kernelHandle                        handle,
//    const DSPLIB_bufParams1D_t *               bufParamsIn,
//    const DSPLIB_bufParams1D_t *               bufParamsOut,
//    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);
//
//template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<int8_t> (
//    DSPLIB_kernelHandle                        handle,
//    const DSPLIB_bufParams1D_t *               bufParamsIn,
//    const DSPLIB_bufParams1D_t *               bufParamsOut,
//    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);
//
//template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<uint8_t> (
//    DSPLIB_kernelHandle                        handle,
//    const DSPLIB_bufParams1D_t *               bufParamsIn,
//    const DSPLIB_bufParams1D_t *               bufParamsOut,
//    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);

template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<float> (
    DSPLIB_kernelHandle                        handle,
    const DSPLIB_bufParams1D_t *               bufParamsIn,
    const DSPLIB_bufParams1D_t *               bufParamsOut,
    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);

template DSPLIB_STATUS DSPLIB_sqrAdd_init_ci<double> (
    DSPLIB_kernelHandle                        handle,
    const DSPLIB_bufParams1D_t *               bufParamsIn,
    const DSPLIB_bufParams1D_t *               bufParamsOut,
    const DSPLIB_sqrAdd_InitArgs *pKerInitArgs);


#pragma FUNC_ALWAYS_INLINE
static inline float DSPLIB_horiAdd(c7x::float_vec vector){
   float sum = 0;
   for (uint i = 0; i < c7x::element_count_of<c7x::float_vec>::value; i++){
      sum += *((float*)(&vector) + i);
   }
   return sum;
}

#pragma FUNC_ALWAYS_INLINE
static inline double DSPLIB_horiAdd(c7x::double_vec vector){
   double sum = 0;
   for (uint i = 0; i < c7x::element_count_of<c7x::double_vec>::value; i++){
      sum += *((double*)(&vector) + i);
   }
   return sum;
}

template <typename dataType, int32_t dataIn>
DSPLIB_STATUS DSPLIB_sqrAdd_exec_ci(DSPLIB_kernelHandle handle,
                                    void *restrict pIn,
                                    void *restrict pOut)
{
    DSPLIB_sqrAdd_PrivArgs *pKerPrivArgs = (DSPLIB_sqrAdd_PrivArgs *) handle;
    uint32_t      blockSize           = pKerPrivArgs->blockSize;

   __SE_TEMPLATE_v1 se0Params;
   __SE_TEMPLATE_v1 se1Params;
   __SA_TEMPLATE_v1 sa0Params;

   dataType *restrict pInLocal1         = (dataType *)pIn;
   dataType *restrict pOutLocal        = (dataType *)pOut;

#if DSPLIB_DEBUGPRINT
   printf("Enter DSPLIB_sqrAdd_exec_ci\n");
#endif

   typedef typename c7x::make_full_vector<dataType>::type vec;
   int32_t eleCount       = c7x::element_count_of<vec>::value;

   dataType *restrict pInLocal2         = pInLocal1 + eleCount;
#if DSPLIB_DEBUGPRINT
    printf("Enter eleCount %d\n", eleCount);
#endif

   uint8_t *pBlock     = pKerPrivArgs->bufPblock;

   se0Params = *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SE0_PARAM_OFFSET);
   se1Params = *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SE1_PARAM_OFFSET);
   sa0Params = *(__SA_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SA0_PARAM_OFFSET);
   // Input samples
   __SE0_OPEN(pInLocal1, se0Params);
   __SE1_OPEN(pInLocal2, se1Params);


  // Output samples
   __SA0_OPEN(sa0Params);

#if DSPLIB_DEBUGPRINT
   printf("DSPLIB_DEBUGPRINT blockSize %d pInLocal1 %p pInLocal2 %p\n", blockSize, pInLocal1, pInLocal2);
#endif

   vec outa, outb, outc, outd, oute, outf, outg, outh, outab, outcd, outef, outgh, out;
   if (dataIn == DSPLIB_FLOAT32) {
      outa  = 0.0f;
      outb  = 0.0f;
      outc  = 0.0f;
      outd  = 0.0f;
      oute  = 0.0f;
      outf  = 0.0f;
      outg  = 0.0f;
      outh  = 0.0f;
      outab = 0.0f;
      outcd = 0.0f;
      outef = 0.0f;
      outgh = 0.0f;
      out   = 0.0f;
   } else {
       outa  = (vec)0.0;
       outb  = (vec)0.0;
       outc  = (vec)0.0;
       outd  = (vec)0.0;
       oute  = (vec)0.0;
       outf  = (vec)0.0;
       outg  = (vec)0.0;
       outh  = (vec)0.0;
       outab = (vec)0.0;
       outcd = (vec)0.0;
       outef = (vec)0.0;
       outgh = (vec)0.0;
       out   = (vec)0.0;
   }

   dataType result;
   for (int32_t counter = 0; counter < blockSize; counter += eleCount*8) {
      vec a = c7x::strm_eng<0, vec>::get_adv();
      vec b = c7x::strm_eng<1, vec>::get_adv();

      outa += a * a;
      outb += b * b;
#if DSPLIB_DEBUGPRINT
//      DSPLIB_debugPrintVector(a);
//      DSPLIB_debugPrintVector(outa);
#endif
      vec c = c7x::strm_eng<0, vec>::get_adv();
      vec d = c7x::strm_eng<1, vec>::get_adv();

      outc += c * c;
      outd += d * d;

      vec e = c7x::strm_eng<0, vec>::get_adv();
      vec f = c7x::strm_eng<1, vec>::get_adv();

      oute += e * e;
      outf += f * f;

      vec g = c7x::strm_eng<0, vec>::get_adv();
      vec h = c7x::strm_eng<1, vec>::get_adv();

      outg += g * g;
      outh += h * h;

   }

   outab = outa + outb;
   outcd = outc + outd;
   outef = oute + outf;
   outgh = outg + outh;
   out = outab + outcd;
   out += outef;
   out += outgh;
#if DSPLIB_DEBUGPRINT
      DSPLIB_debugPrintVector(out);
#endif
   result = DSPLIB_horiAdd(out);
   *pOutLocal = result;
#if DSPLIB_DEBUGPRINT
   printf("DSPLIB_DEBUGPRINT DSPLIB_sqrAdd_exec_ci result %lf\n", result);
#endif

   __SE0_CLOSE ();
   __SE1_CLOSE ();
   __SA0_CLOSE ();

   return DSPLIB_SUCCESS;
}

template DSPLIB_STATUS DSPLIB_sqrAdd_exec_ci<float, DSPLIB_FLOAT32> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn,
   void *restrict pOut);

template DSPLIB_STATUS DSPLIB_sqrAdd_exec_ci<double, DSPLIB_FLOAT64> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn,
   void *restrict pOut);
