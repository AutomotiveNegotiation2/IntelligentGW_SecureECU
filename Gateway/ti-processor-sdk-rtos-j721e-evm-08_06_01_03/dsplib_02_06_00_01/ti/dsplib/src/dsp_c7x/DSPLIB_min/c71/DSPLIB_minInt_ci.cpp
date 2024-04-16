/******************************************************************************/
/*!
 * \file DSPLIB_min.c
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
#include "../DSPLIB_min_priv.h"
#include <float.h>

template <typename dataType, int32_t dataIn>
DSPLIB_STATUS DSPLIB_minint_exec_ci(DSPLIB_kernelHandle handle,
                                    void *restrict pIn1,
                                    void *restrict pIn2,
                                    void *restrict pOut)
{
    DSPLIB_min_PrivArgs *pKerPrivArgs = (DSPLIB_min_PrivArgs *) handle;
    uint32_t      blockSize           = pKerPrivArgs->blockSize;

   __SE_TEMPLATE_v1 se0Params;
   __SA_TEMPLATE_v1 sa0Params;

   dataType *restrict pInLocal1         = (dataType *)pIn1;
   dataType *restrict pInLocal2         = (dataType *)pIn2;
   dataType *restrict pOutLocal         = (dataType *)pOut;

#if DSPLIB_DEBUGPRINT
   printf("Enter DSPLIB_min_exec_ci\n");
#endif

   typedef typename c7x::make_full_vector<dataType>::type vec;
   int32_t eleCount       = c7x::element_count_of<vec>::value;

#if DSPLIB_DEBUGPRINT
    printf("Enter eleCount %d\n", eleCount);
#endif
    uint8_t *pBlock     = pKerPrivArgs->bufPblock;
    se0Params    = *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SE0_PARAM_OFFSET);
    sa0Params = *(__SA_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE_SA0_PARAM_OFFSET);

   // Input samples
   __SE0_OPEN(pInLocal1, se0Params);
   __SE1_OPEN(pInLocal2, se0Params);

  // Output samples
   __SA0_OPEN(sa0Params);

#if DSPLIB_DEBUGPRINT
   printf("DSPLIB_DEBUGPRINT blockSize %d\n", blockSize);
#endif

   vec out;
   __vpred cmp_lt;
   for (int32_t counter = 0; counter < blockSize; counter += eleCount) {
      vec a = c7x::strm_eng<0, vec>::get_adv();
      vec b = c7x::strm_eng<1, vec>::get_adv();

      cmp_lt = __cmp_gt_pred(b, a);

      out = __select(cmp_lt, a, b);

      __vpred tmp = c7x::strm_agen<0, vec>::get_vpred();
      vec * VB1 = c7x::strm_agen<0, vec>::get_adv(pOutLocal);

      __vstore_pred(tmp, VB1, out);
#if DSPLIB_DEBUGPRINT
//      if (counter == 0) {
//         DSPLIB_debugPrintVector(a);
//         DSPLIB_debugPrintVector(b);
//         DSPLIB_debugPrintVector(out);
//      }
#endif
   }
   __SE0_CLOSE ();
   __SE1_CLOSE ();
   __SA0_CLOSE ();

   return DSPLIB_SUCCESS;
}

template DSPLIB_STATUS DSPLIB_minint_exec_ci<int8_t, DSPLIB_INT8> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn1,
   void *restrict pIn2,
   void *restrict pOut);

template DSPLIB_STATUS DSPLIB_minint_exec_ci<uint8_t, DSPLIB_UINT8> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn1,
   void *restrict pIn2,
   void *restrict pOut);

template DSPLIB_STATUS DSPLIB_minint_exec_ci<int16_t, DSPLIB_INT16> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn1,
   void *restrict pIn2,
   void *restrict pOut);

template DSPLIB_STATUS DSPLIB_minint_exec_ci<uint16_t, DSPLIB_UINT16> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn1,
   void *restrict pIn2,
   void *restrict pOut);

template DSPLIB_STATUS DSPLIB_minint_exec_ci<int32_t, DSPLIB_INT32> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn1,
   void *restrict pIn2,
   void *restrict pOut);

template DSPLIB_STATUS DSPLIB_minint_exec_ci<uint32_t, DSPLIB_UINT32> (
   DSPLIB_kernelHandle handle,
   void *restrict pIn1,
   void *restrict pIn2,
   void *restrict pOut);
