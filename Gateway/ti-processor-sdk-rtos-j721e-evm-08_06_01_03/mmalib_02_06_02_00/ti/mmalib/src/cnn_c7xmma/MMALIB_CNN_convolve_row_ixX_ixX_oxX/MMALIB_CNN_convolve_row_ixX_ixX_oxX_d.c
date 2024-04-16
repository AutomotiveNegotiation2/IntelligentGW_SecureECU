/******************************************************************************
 *                                                                             *
 * module name       :MMALIB                                                   *
 *                                                                             *
 * module descripton :Matrix Multiply Accelerator Library module for C7x+MMA   *
 *                                                                             *
 * Copyright (C) 2017-2018 Texas Instruments Incorporated - http://www.ti.com/ *
 * ALL RIGHTS RESERVED                                                         *
 *                                                                             *
 ******************************************************************************/

/**
******************************************************************************
*  @file     MMALIB_CNN_convolve_row_ixX_ixX_oxX_d.c
*
*  @brief    File to demnostrate usage of kernel
*
*  @version  0.1 - Jan 2018 : Initial Version - [Asheesh Bhardwaj]
*  @version  0.2 - Feb 2018 : Support for 8 bit [Asheesh Bhardwaj]
*  @version  0.3 - March 2018: Support for 16 bit, templates and 3x3 stride by 2 [Asheesh Bhardwaj]
*
*******************************************************************************
*/

// include MMALIB
#include <mmalib.h>

// include test infrastructure provided by MMALIB
#include "../../test/MMALIB_test.h"

// include test data for this kernel
#include "MMALIB_CNN_convolve_row_ixX_ixX_oxX_idat.h"

__attribute__ ((section (".msmcData"), aligned (64))) int8_t msmcBuffer[MMALIB_L3_RESULTS_BUFFER_SIZE];
__attribute__ ((section (".ddrData"), aligned (64))) int8_t ddrBuffer[2048 * 1024];

int16_t volatile volatileSum = 0; // use volatile to keep compiler from removing this operation

/* Test Driver Routine */
int MMALIB_CNN_convolve_row_ixX_ixX_oxX_d (uint32_t *pProfile, uint8_t LevelOfFeedback)
{
   int32_t tpi; /* test parameter index */
   int32_t fail = 0;
   uint64_t archCycles, estCycles;
   uint32_t num_pts = 0;
   /* Test Parameters */
   convolve_row_ixX_ixX_oxX_testParams_t *prm;

   convolve_row_ixX_ixX_oxX_getTestParams (&prm, &test_cases);

   MMALIB_kernelHandle handle;
   int32_t handleSize;

   MMALIB_CNN_convolve_row_ixX_ixX_oxX_InitArgs kerInitArgs;
   MMALIB_CNN_convolve_row_ixX_ixX_oxX_ExecInArgs kerExecInArgs;
   MMALIB_CNN_convolve_row_ixX_ixX_oxX_ExecOutArgs kerExecOutArgs;

   /* Initialize profiling */
   TI_profile_init("convolve_row_ixX_ixX_oxX");

   /* Run each test case */
   for (tpi = 0; tpi < test_cases; tpi++) {

      /* Initialize status flags */

      int32_t status_nat_vs_opt =
          TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Optimized */
      int32_t status_opt_vs_ref =
          TI_TEST_KERNEL_PASS; /* Test status : Natural c vs. Static Reference */
      int32_t status_nat_vs_ref = TI_TEST_KERNEL_PASS;
      MMALIB_STATUS status_init = MMALIB_SUCCESS;
      MMALIB_STATUS status_opt  = MMALIB_SUCCESS;
      MMALIB_STATUS status_nat  = MMALIB_SUCCESS;

      uint32_t inp0Size, inp1Size, outSize;

      int32_t inWidth               = prm[tpi].inWidth;
      int32_t inputBlockWidth       = inWidth + prm[tpi].pad;
      int32_t inChOffset            = prm[tpi].inChOffset;
      int32_t numInChannels         = prm[tpi].numInChannels;
      int32_t numOutChannels        = prm[tpi].numOutChannels;
      int32_t numOfOutputChKerBuf   = prm[tpi].numOfOutputChKerBuf;
      int32_t subMChannels          = prm[tpi].subMChannels;
      int32_t kernelWidth           = prm[tpi].kernelWidth;
      int32_t kernelHeight          = prm[tpi].kernelHeight;
      int32_t dilationWidth         = prm[tpi].dilationWidth;
      int32_t dilationHeight        = prm[tpi].dilationHeight;
      int32_t validColsIn           = prm[tpi].validColsIn;
      int32_t strideWidth           = prm[tpi].strideWidth;
      int32_t strideHeight          = prm[tpi].strideHeight;
      int32_t kDim                  = prm[tpi].kDim;
      int32_t pitchA                = prm[tpi].pitchA;
      int32_t pitchC                = prm[tpi].pitchC;
      uint8_t dataTypeA             = prm[tpi].dataTypeA;
      uint8_t dataTypeB             = prm[tpi].dataTypeB;
      uint8_t dataTypeC             = prm[tpi].dataTypeC;
      uint8_t activationType        = prm[tpi].activationType;
      int32_t pad                   = prm[tpi].pad;
      int32_t shift                 = prm[tpi].qShift;
      int32_t bias                  = prm[tpi].biasB;
      uint8_t mode                  = prm[tpi].mode;
      int32_t circularOffset        = prm[tpi].circularOffset;
      int32_t maxHeight             = prm[tpi].maxHeight;
      int32_t totalN                = prm[tpi].totalN;
      int32_t subN                  = prm[tpi].subN;
      int32_t validColsPerRowIn     = prm[tpi].validColsPerRowIn;
      int32_t validRowsIn           = prm[tpi].validRowsIn;
      int32_t outputPitchPerRow     = prm[tpi].outputPitchPerRow;
      int32_t inputPitchPerRow      = prm[tpi].inputPitchPerRow;
      int32_t validColsInlast       = prm[tpi].validColsInlast;
      int32_t validRowsInlast       = prm[tpi].validRowsInlast;
      int32_t validColsPerRowInlast = prm[tpi].validColsPerRowInlast;
      int32_t numGroupsPerKernel    = prm[tpi].numGroupsPerKernel;
      int32_t MCounter              = numOutChannels/subMChannels;
      MCounter                      = (numOutChannels%subMChannels == 0) ? MCounter - 1: MCounter;

      int32_t testNum  = prm[tpi].testID;
      int32_t numBytes = 1;
      int32_t MMA_SIZE = MMALIB_MMA_SIZE_8_BIT;

      if (dataTypeC == MMALIB_INT8 || dataTypeC == MMALIB_UINT8) {
         numBytes = 1;
         MMA_SIZE = MMALIB_MMA_SIZE_8_BIT;
      }
      else if (dataTypeC == MMALIB_INT16 || dataTypeC == MMALIB_UINT16) {
         numBytes = 2;
         MMA_SIZE = MMALIB_MMA_SIZE_16_BIT;
      }
      else {
         // TODO
      }

      // Function returns the memory for the handle to be allocated
      handleSize = MMALIB_CNN_convolve_row_ixX_ixX_oxX_getHandleSize (&kerInitArgs);
#if MMALIB_DEBUGPRINT
         printf ("\nAfter MMALIB_CNN Handle Size before %d\n", handleSize);
#endif
      // Predicate buffer size is returned for allocating appropriate memory by application
      if (strideWidth == 1 && strideHeight == 1) {
         int32_t defaultPredSize = MMALIB_CNN_seamPredicateRegistersSizeDefault();
         int32_t actualPredSize = MMALIB_CNN_seamPredicateRegistersSize(inWidth, pad, maxHeight, MMA_SIZE, numOutChannels, subMChannels);

         if (actualPredSize > defaultPredSize) {
            handleSize = handleSize + actualPredSize - defaultPredSize;
         }
      }
#if MMALIB_DEBUGPRINT
         printf ("\nAfter MMALIB_CNN Handle Size after %d\n", handleSize);
#endif
      handle     = malloc (handleSize);

      int32_t strideShiftW = 0;
      if (strideWidth == 2)
         strideShiftW = 1;
      if (strideWidth == 4)
         strideShiftW = 2;

      int32_t strideShiftH = 0;
      if (strideHeight == 2)
         strideShiftH = 1;
      if (strideHeight == 4)
         strideShiftH = 2;

      // validColsOut calculated for non strided convolution
      int32_t validColsOut =
          ((validColsIn - inputBlockWidth * (kernelHeight * dilationHeight - 1)) >>
           strideShiftH) >>
          strideShiftW;
      int32_t validColsPerRow = 0;
      /* Compute buffer sizes */
      inp0Size = numOfOutputChKerBuf * pitchA * numGroupsPerKernel;
      inp1Size = numInChannels * inChOffset * numGroupsPerKernel * numBytes;
      outSize  = numOutChannels * numGroupsPerKernel * pitchC * (totalN / subN);

      /* Allocate buffers for each test vector */
#if MMALIB_DEBUGPRINT
      printf (
          "pitchA %d, inChOffset %d, pitchC %d, inp0Size %d, inp1Size %d, outSize %d numGroupsPerKernel %d\n",
          pitchA,
          inChOffset,
          pitchC,
          inp0Size,
          inp1Size,
          outSize,
          numGroupsPerKernel);

      printf ("numOfOutputChKerBuf %d, numInChannels %d, numOutChannels %d, totalN %d, "
              "subN %d\n",
              numOfOutputChKerBuf,
              numInChannels,
              numOutChannels,
              totalN,
              subN);
#endif

      MMALIB_bufParams2D_t src0_addr; // paramsWgt
      MMALIB_bufParams2D_t src1_addr; // input
      MMALIB_bufParams2D_t src2_addr; // bias
      MMALIB_bufParams3D_t dst_addr;
      int32_t numBiasVals = kDim - kernelWidth*kernelHeight*numInChannels;
      // Allocate coefficient buffers
      src0_addr.dim_x     = kDim;
      src0_addr.dim_y     = numOfOutputChKerBuf*numGroupsPerKernel;
      src0_addr.stride_y  = pitchA;
      src0_addr.data_type = dataTypeA;

      // allocate input Channels
      src1_addr.dim_x     = inChOffset;
      src1_addr.dim_y     = numInChannels*numGroupsPerKernel;
      src1_addr.stride_y  = inChOffset;
      src1_addr.data_type = dataTypeB;

      // allocate Bias per output channel
      src2_addr.dim_x     = numBiasVals;
      src2_addr.dim_y     = numOutChannels;
      src2_addr.stride_y  = numBiasVals*numBytes;
      src2_addr.data_type = dataTypeA;

      // allocate output Channels
      dst_addr.dim_x     = pitchC / numBytes;
      dst_addr.dim_y     = numOutChannels;
      dst_addr.stride_y  = pitchC;
      dst_addr.dim_z     = numGroupsPerKernel;
      dst_addr.stride_z  = numOutChannels*pitchC;//numOutChannels*pitchC = pitchG
      dst_addr.data_type = dataTypeC;

      // Assign to Init Args and Interface file
      kerInitArgs.Fc                = kernelWidth;
      kerInitArgs.Fr                = kernelHeight;
      kerInitArgs.dilationX         = dilationWidth;
      kerInitArgs.dilationY         = dilationHeight;
      kerInitArgs.strideX           = strideWidth;
      kerInitArgs.strideY           = strideHeight;
      kerInitArgs.validColsIn       = validColsIn;
      kerInitArgs.subMChannels      = subMChannels;
      kerInitArgs.inWidth           = inWidth;
      kerInitArgs.pad               = pad;
      kerInitArgs.maxHeight         = maxHeight;
      kerInitArgs.inChOffset        = inChOffset;
      kerInitArgs.shift             = shift;
      kerInitArgs.No                = numOutChannels;
      kerInitArgs.bias              = bias;
      kerInitArgs.activationType    = activationType;
      kerInitArgs.mode              = mode;
      kerInitArgs.validColsPerRowIn = validColsPerRowIn;
      kerInitArgs.validRowsIn       = validRowsIn;
      kerInitArgs.outputPitchPerRow = outputPitchPerRow;
      kerInitArgs.inputPitchPerRow  = inputPitchPerRow;
      kerInitArgs.numGroupsPerKernel= numGroupsPerKernel;
      kerInitArgs.numBiasVals       = numBiasVals;

      kerExecInArgs.bufferReset     = 0;

      MMALIB_CNN_convolve_row_ixX_ixX_oxX_reorderWeights_Args reorderWeights;

      reorderWeights.dataType            =  src1_addr.data_type;
      reorderWeights.Ni                  =  src1_addr.dim_y;
      reorderWeights.No                  =  kerInitArgs.No;
      reorderWeights.Fr                  =  kerInitArgs.Fr;
      reorderWeights.Fc                  =  kerInitArgs.Fc;
      reorderWeights.strideX             =  kerInitArgs.strideX;
      reorderWeights.strideY             =  kerInitArgs.strideY;
      reorderWeights.dilationX           =  kerInitArgs.dilationX;
      reorderWeights.dilationY           =  kerInitArgs.dilationY;
      reorderWeights.numBiasVals         =  kerInitArgs.numBiasVals;
      reorderWeights.subMChannels        =  kerInitArgs.subMChannels;
      reorderWeights.numGroupsPerKernel  =  kerInitArgs.numGroupsPerKernel;
      reorderWeights.inWidth             =  kerInitArgs.inWidth;
      reorderWeights.pad                 =  kerInitArgs.pad;
      reorderWeights.validColsIn         =  kerInitArgs.validColsIn;

//      kerInitArgs.weightReorderFlag = MMALIB_CNN_convolve_row_reorderWeightsFlag(&src0_addr, &src1_addr, &kerInitArgs);
      kerInitArgs.weightReorderFlag = MMALIB_CNN_convolve_row_reorderWeightsFlag(&reorderWeights);


      int32_t weightBufferSize;
      if (kerInitArgs.weightReorderFlag == 1) {
         weightBufferSize =  MMALIB_CNN_convolve_row_reorderWeightsBufferSize(&src0_addr, &reorderWeights, &kerInitArgs);
      } else {
          weightBufferSize = 0;
      }

      int8_t *src0 = NULL;

      if (kerInitArgs.weightReorderFlag == 0) {
          src0 = (int8_t *) TI_memalign (numBytes * MMA_SIZE, inp0Size);
      } else {
          src0 = (int8_t *) TI_memalign (numBytes * MMA_SIZE, weightBufferSize);
      }

      int8_t *src1 = NULL;
      if (mode == MMALIB_LINEAR) {
         src1 = (int8_t *) TI_memalign (MMA_SIZE * numBytes, inp1Size);
      }
      else if (mode == MMALIB_SE_CIRCULAR) {
         src1 = (int8_t *) TI_memalign (inChOffset * numBytes, inp1Size);
      }

      int8_t *dst = NULL;
      if (prm[tpi].outputDataLocation == MMALIB_TEST_OUTPUT_HEAP)
         dst = (int8_t *) TI_memalign (MMALIB_ALIGN_128BYTES, outSize);
      else if (prm[tpi].outputDataLocation == MMALIB_TEST_OUTPUT_MSMC) {
         dst = (int8_t *) msmcBuffer;
      }
      else
         dst = (int8_t *) msmcBuffer;

      int32_t biasSize = numOutChannels*numBiasVals*numBytes;
      int8_t *src2 = NULL;
      src2 = (int8_t *) TI_memalign (biasSize, biasSize);

#if !defined(PERFORMANCE_TEST) && !defined(COMPILER_TEST)
      int8_t *dst_cn = NULL;
      if (prm[tpi].outputDataLocation == MMALIB_TEST_OUTPUT_HEAP) {
          dst_cn = (int8_t *) malloc (outSize);
      } else {
         dst_cn = (int8_t *) ddrBuffer;
      }
#endif

      int32_t MCount, NCount;

#if MMALIB_DEBUGPRINT
      printf ("MMALIB_DEBUGPRINT test_case %d  src1: %p  src0 %p dst %p \n",
              tpi,
              src1,
              src0,
              dst);
#if !defined(PERFORMANCE_TEST) && !defined(COMPILER_TEST)
      printf ("MMALIB_DEBUGPRINT test_case %d  dst_cn %p\n", tpi, dst_cn);
#endif
#endif
      /* Only run the test if the buffer allocations fit in the heap */
      if (src0 && src1 && dst) {

#if MMALIB_DEBUGPRINT
      printf ("MMALIB_DEBUGPRINT test_case %d  weightReorderFlag: %d  weightBufferSize %d \n",
              tpi,
              kerInitArgs.weightReorderFlag,
              weightBufferSize
              );
#endif


         /* Fill input arrays according to desired test pattern */
         if (numBytes == 1) {
            if (kerInitArgs.weightReorderFlag == 1 && prm[tpi].staticKernel8Bit != NULL) {
                TI_fillBuffer (prm[tpi].testPattern,
                              (uint8_t) 255,
                              src2,
                              prm[tpi].staticKernel8Bit,
                              numOutChannels*numBiasVals,
                              1,
                              numOutChannels*numBiasVals,
                              sizeof (int8_t),
                              testPatternString);


               MMALIB_CNN_convolve_row_reorderWeights(prm[tpi].staticKernel8Bit, src0, src2, &src0_addr, &src2_addr, &reorderWeights, &kerInitArgs);
            } else {
               TI_fillBuffer (prm[tpi].testPattern,
                             (uint8_t) 255,
                             src0,
                             prm[tpi].staticKernel8Bit,
                             kDim,
                             numOfOutputChKerBuf*numGroupsPerKernel,
                             pitchA,
                             sizeof (int8_t),
                             testPatternString);
            }

            // Fill Input buffer
            TI_fillBuffer (prm[tpi].testPattern,
                           (uint8_t) 255,
                           src1,
                           prm[tpi].staticIn8Bit,
                           inChOffset,
                           numInChannels*numGroupsPerKernel,
                           inChOffset,
                           sizeof (int8_t),
                           testPatternString);

         }
         else if (numBytes == 2) {
            if (kerInitArgs.weightReorderFlag == 1 && prm[tpi].staticKernel16Bit != NULL) {
                TI_fillBuffer (prm[tpi].testPattern,
                              (uint8_t) 255,
                              src2,
                              prm[tpi].staticKernel16Bit,
                              numOutChannels*numBiasVals,
                              1,
                              numOutChannels*numBiasVals,
                              sizeof (int16_t),
                              testPatternString);

               MMALIB_CNN_convolve_row_reorderWeights(prm[tpi].staticKernel16Bit, src0, src2, &src0_addr, &src2_addr, &reorderWeights, &kerInitArgs);
            } else {
               TI_fillBuffer (prm[tpi].testPattern,
                             (uint8_t) 255,
                             src0,
                             prm[tpi].staticKernel16Bit,
                             kDim,
                             numOfOutputChKerBuf*numGroupsPerKernel,
                             pitchA,
                             sizeof (int16_t),
                             testPatternString);
            }
            // Fill Input buffer
            TI_fillBuffer (prm[tpi].testPattern,
                           (uint8_t) 255,
                           src1,
                           prm[tpi].staticIn16Bit,
                           inChOffset,
                           numInChannels*numGroupsPerKernel,
                           inChOffset * numBytes,
                           sizeof (int16_t),
                           testPatternString);
         }

         /* This for creating the predicate buffers */
         int32_t totalBytes;
         if (kerInitArgs.strideX == 1) {
            totalBytes = MMALIB_CNN_generateFillSeamPredicateRegisters (
                handle, inWidth, pad, maxHeight, MMA_SIZE, numOutChannels, subMChannels);
         }
#if MMALIB_DEBUGPRINT
         printf ("\nAfter MMALIB_CNN_generateFillSeamPredicateRegisters  totalBytes %d\n",
                 totalBytes);
#endif
         /* Initialize kernel */
         kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
         TI_profile_start (TI_PROFILE_KERNEL_INIT);
         MMALIB_asm (" MARK 0");
         status_init = MMALIB_CNN_convolve_row_ixX_ixX_oxX_init (
             handle, &src0_addr, &src1_addr, &dst_addr, &kerInitArgs);

         MMALIB_asm (" MARK 1");
         TI_profile_stop ();

         /* Test optimized kernel */
#if MMALIB_DEBUGPRINT
         printf ("\nEntering:MMALIB_CNN_convolve_row_ixX_ixX_oxX");
#endif
         int32_t iterN = 0;
         int32_t validOutputRows;

         // subN is number of input pixels processed in one call and used to calcuate the starting address of feature map buffers
         // total N is total number of input pixels to be processed for a entire feature map
         // The test code is limited due memory available since there is no background data transfer
         // Verify upto two or 3 calls to kernel
         for (NCount = 0; NCount < totalN; NCount += subN) {
            int8_t *src1_Iter = src1 + NCount * numBytes;
            if (mode == MMALIB_SE_CIRCULAR)
               src1_Iter = src1_Iter + circularOffset * numBytes;

            // MCount iterates over number of output channels to be processed in a given kernel call
            // subMChannels are processed in one kernel call and numOutChannels is total output Channels
            // For memory restrictions not all channels can fit in L2 memory
            for (MCount = 0; MCount < numOutChannels; MCount += subMChannels) {
//               kerExecInArgs.subMChannels      = subMChannels;
               if (MCount == MCounter*subMChannels) {
                  kerExecInArgs.subMChannels      = numOutChannels - MCount;
               }
               else {
                  kerExecInArgs.subMChannels      = subMChannels;
               }

               // validColsInLast, validColsPerRowInlast, validRowsInlast should be kept same as validColsIn as in init phase.
               // This parameter is only for cases when last call parameters are different than what is initialized.
               kerExecInArgs.validColsIn       = validColsInlast;
               kerExecInArgs.validColsPerRowIn = validColsPerRowInlast;
               kerExecInArgs.validRowsIn       = validRowsInlast;
               kerExecInArgs.pad               = pad;
               int8_t *dst_iter                = dst + MCount * pitchC + numOutChannels * iterN * pitchC;

#if MMALIB_DEBUGPRINT
               printf ("src1_Iter %p dst_iter %p dst %p src0 %p\n",
                       src1_Iter,
                       dst_iter,
                       dst,
                       src0);
               printf ("subMChannels %d, validColsIn %d MCount %d NCount %d subN %d\n",
                       subMChannels,
                       validColsIn,
                       MCount,
                       NCount,
                       subN);
#endif
               TI_profile_start (TI_PROFILE_KERNEL_OPT);
               MMALIB_asm (" MARK 2");
               status_opt = MMALIB_CNN_convolve_row_ixX_ixX_oxX_exec (
                   handle, src0, src1_Iter, dst_iter, &kerExecInArgs, &kerExecOutArgs);
               MMALIB_asm (" MARK 3");
               TI_profile_stop ();
               validColsOut    = kerExecOutArgs.validColsOut;
               validColsPerRow = kerExecOutArgs.validColsPerRowOut;
            }

#if MMALIB_DEBUGPRINT
            validColsOut = kerExecOutArgs.validColsOut;
            printf ("OptC: valid cols out %d itenN %d\n", validColsOut, iterN);
#endif
            iterN++;
         }
         __SE0_CLOSE ();
         __SE1_CLOSE ();

         validOutputRows = kerExecOutArgs.validRowsOut;

#if MMALIB_DEBUGPRINT
         printf ("\n validColsOut after optimized C %d validColsPerRow %d "
                 "outputPitchPerRow %d validOutputRows%d\n",
                 validColsOut,
                 validColsPerRow,
                 outputPitchPerRow,
                 validOutputRows);
#endif

         // run warm instruction cache test
         if (kerInitArgs.strideX == 1) {
            totalBytes = MMALIB_CNN_generateFillSeamPredicateRegisters (
                handle, inWidth, pad, maxHeight, MMA_SIZE, numOutChannels, subMChannels);
         }

         /* Initialize kernel */
         kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
         TI_profile_start (TI_PROFILE_KERNEL_INIT);
         MMALIB_asm (" MARK 4");
         status_init = MMALIB_CNN_convolve_row_ixX_ixX_oxX_init (
             handle, &src0_addr, &src1_addr, &dst_addr, &kerInitArgs);

         MMALIB_asm (" MARK 5");
         TI_profile_stop ();
#if MMALIB_DEBUGPRINT

            printf ("Mark 5\n");
#endif
         /* Test optimized kernel */
         iterN = 0;
         for (NCount = 0; NCount < totalN; NCount += subN) {
            int8_t *src1_Iter = src1 + NCount * numBytes;
            if (mode == MMALIB_SE_CIRCULAR)
               src1_Iter = src1_Iter + circularOffset * numBytes;
            for (MCount = 0; MCount < numOutChannels; MCount += subMChannels) {
               kerExecInArgs.subMChannels      = subMChannels;
               kerExecInArgs.validColsIn       = validColsInlast;
               kerExecInArgs.validColsPerRowIn = validColsPerRowInlast;
               kerExecInArgs.validRowsIn       = validRowsInlast;
               kerExecInArgs.pad               = pad;
               int8_t *dst_iter =
                   dst + MCount * pitchC + numOutChannels * iterN * pitchC;
               TI_profile_start (TI_PROFILE_KERNEL_OPT_WARM);
               MMALIB_asm (" MARK 6");
               status_opt = MMALIB_CNN_convolve_row_ixX_ixX_oxX_exec (
                   handle, src0, src1_Iter, dst_iter, &kerExecInArgs, &kerExecOutArgs);
               MMALIB_asm (" MARK 7");
               TI_profile_stop ();
               validColsOut    = kerExecOutArgs.validColsOut;
               validColsPerRow = kerExecOutArgs.validColsPerRowOut;
            }
            iterN++;
         }
         __SE0_CLOSE ();
         __SE1_CLOSE ();
#if MMALIB_DEBUGPRINT

            printf ("Mark 7\n");
#endif
         // get output to L1D
         uint32_t row;
         int32_t col;
         int16_t outSum = 0;
         int8_t *pDst = (int8_t *) dst; // treat output as bytes to be data
         for (row = 0; row < dst_addr.dim_y; row++) {
            for (col = 0; col < dst_addr.stride_y; col++) {
               outSum += *pDst;
               pDst++;
            }
         }
         // dummy store of outSum to insure that the compiler does not remove
         // it.
         volatileSum = outSum;

         // run warm instruction cache test
         /* This for creating the predicate buffers */
         if (kerInitArgs.strideX == 1) {
            totalBytes = MMALIB_CNN_generateFillSeamPredicateRegisters (
                //handle, inWidth, pad, maxHeight, MMA_SIZE);
            handle, inWidth, pad, maxHeight, MMA_SIZE, numOutChannels, subMChannels);
         }

         /* Initialize kernel */
         kerInitArgs.funcStyle = MMALIB_FUNCTION_OPTIMIZED;
         TI_profile_start (TI_PROFILE_KERNEL_INIT);
         MMALIB_asm (" MARK 8");
         status_init = MMALIB_CNN_convolve_row_ixX_ixX_oxX_init (
             handle, &src0_addr, &src1_addr, &dst_addr, &kerInitArgs);

         MMALIB_asm (" MARK 9");
         TI_profile_stop ();

         /* Test optimized kernel */

         iterN = 0;
#if MMALIB_DEBUGPRINT

            printf ("Mark 9\n");
#endif
         for (NCount = 0; NCount < totalN; NCount += subN) {
            int8_t *src1_Iter = src1 + NCount * numBytes;
            if (mode == MMALIB_SE_CIRCULAR)
               src1_Iter = src1_Iter + circularOffset * numBytes;
            for (MCount = 0; MCount < numOutChannels; MCount += subMChannels) {
               kerExecInArgs.subMChannels      = subMChannels;
               kerExecInArgs.validColsIn       = validColsInlast;
               kerExecInArgs.validColsPerRowIn = validColsPerRowInlast;
               kerExecInArgs.validRowsIn       = validRowsInlast;
               kerExecInArgs.pad               = pad;
               int8_t *dst_iter =
                   dst + MCount * pitchC + numOutChannels * iterN * pitchC;

               TI_profile_start (TI_PROFILE_KERNEL_OPT_WARMWRB);
               MMALIB_asm (" MARK 10");
               status_opt = MMALIB_CNN_convolve_row_ixX_ixX_oxX_exec (
                   handle, src0, src1_Iter, dst_iter, &kerExecInArgs, &kerExecOutArgs);
               MMALIB_asm (" MARK 11");
               TI_profile_stop ();
               validColsOut    = kerExecOutArgs.validColsOut;
               validColsPerRow = kerExecOutArgs.validColsPerRowOut;
            }
            iterN++;
         }
         __SE0_CLOSE ();
         __SE1_CLOSE ();
#if MMALIB_DEBUGPRINT

            printf ("Mark 11\n");
#endif

#if !defined(PERFORMANCE_TEST) && !defined(COMPILER_TEST)

         /* Test _cn kernel */
         kerInitArgs.funcStyle = MMALIB_FUNCTION_NATC;
#if MMALIB_DEBUGPRINT

            printf ("natC MMALIB_CNN_convolve_row_ixX_ixX_oxX_init\n");
#endif
         status_init           = MMALIB_CNN_convolve_row_ixX_ixX_oxX_init (
             handle, &src0_addr, &src1_addr, &dst_addr, &kerInitArgs);
         iterN = 0;
         // subN is number of input pixels processed in one call and used to calcuate the starting address of feature map buffers
         // total N is total number of input pixels to be processed for a entire feature map
         // The test code is limited due memory available since there is no background data transfer
         // Verify upto two or 3 calls to kernel
#if MMALIB_DEBUGPRINT

            printf ("natC MMALIB_CNN_convolve_row_ixX_ixX_oxX_exec\n");
#endif
         for (NCount = 0; NCount < totalN; NCount += subN) {
            int8_t *src1_Iter = src1 + NCount * numBytes;
            if (mode == MMALIB_SE_CIRCULAR)
               src1_Iter = src1_Iter + circularOffset * numBytes;
            // MCount iterates over number of output channels to be processed in a given kernel call
            // subMChannels are processed in one kernel call and numOutChannels is total output Channels
            // For memory restrictions not all channels can fit in L2 memory
            for (MCount = 0; MCount < numOutChannels; MCount += subMChannels) {
               if (MCount == MCounter*subMChannels) {
                  kerExecInArgs.subMChannels      = numOutChannels - MCount;
               }
               else {
                  kerExecInArgs.subMChannels      = subMChannels;
               }
               // validColsInLast, validColsPerRowInlast, validRowsInlast should be kept same as validColsIn as in init phase.
               // This parameter is only for cases when last call parameters are different than what is initialized.
               kerExecInArgs.validColsIn       = validColsInlast;
               kerExecInArgs.validColsPerRowIn = validColsPerRowInlast;
               kerExecInArgs.validRowsIn       = validRowsInlast;
               kerExecInArgs.pad               = pad;
               int8_t *dst_cn_iter =
                   dst_cn + MCount * pitchC + numOutChannels * iterN * pitchC;

#if MMALIB_DEBUGPRINT
               printf (
                   "src1_Iter %p dst_cn_iter %p src0 %p\n", src1_Iter, dst_cn_iter, src0);
               printf ("subMChannels %d, validColsIn %d MCount %d NCount %d subN %d\n",
                       subMChannels,
                       validColsIn,
                       MCount,
                       NCount,
                       subN);
#endif
               TI_profile_start (TI_PROFILE_KERNEL_CN);
               MMALIB_asm (" MARK 4");
               status_nat = MMALIB_CNN_convolve_row_ixX_ixX_oxX_exec (
                   handle, src0, src1_Iter, dst_cn_iter, &kerExecInArgs, &kerExecOutArgs);
               MMALIB_asm (" MARK 5");
               TI_profile_stop ();
               validColsPerRow = kerExecOutArgs.validColsPerRowOut;
               validColsOut    = kerExecOutArgs.validColsOut;
            }
#if MMALIB_DEBUGPRINT
            validColsOut = kerExecOutArgs.validColsOut;
            printf ("NatC: valid cols out %d itenN %d\n", validColsOut, iterN);
#endif
            iterN++;
         }

         validOutputRows = kerExecOutArgs.validRowsOut;
#if MMALIB_DEBUGPRINT
         printf ("\n validColsOut after refrence C %d validOutputRows %d validColsPerRow "
                 "%d \n",
                 validColsOut,
                 validOutputRows,
                 validColsPerRow);
#endif
         /* Compare natural C Output and Optimized Output */
         if (kerInitArgs.strideX == 1) {
            if (numGroupsPerKernel == 1) {
               status_nat_vs_opt = TI_compare_mem_2D ((void *) dst,
                                                   (void *) dst_cn,
                                                   0,
                                                   0,
                                                   validColsOut,
                                                   numOutChannels * iterN,
                                                   pitchC,
                                                   numBytes);
            } else {
               status_nat_vs_opt = TI_compare_mem_3D ((void *) dst,
                                                   (void *) dst_cn,
                                                   0,
                                                   0,
                                                   validColsOut,
                                                   numOutChannels * iterN,
                                                   numGroupsPerKernel,
                                                   pitchC,
                                                   numOutChannels*pitchC,
                                                   numBytes);
            }
#if MMALIB_DEBUGPRINT
            printf ("reaching comparison for Compare natural C Output and Optimized "
                    "Output\n");
            printf ("%s: status_nat_vs_opt = %d\n", __FUNCTION__, status_nat_vs_opt);
#endif
         }
         else if (kerInitArgs.strideX > 1) {
            status_nat_vs_opt = TI_compare_mem_3D ((void *) dst,
                                                   (void *) dst_cn,
                                                   0,
                                                   0,
                                                   validColsPerRow,
                                                   validOutputRows,
                                                   numOutChannels * iterN,
                                                   outputPitchPerRow,
                                                   pitchC,
                                                   numBytes);
         }

#else
         /* Set to pass since it wasn't supposed to run. */
         status_nat_vs_opt = TI_TEST_KERNEL_FAIL;
#endif //#if !defined(PERFORMANCE_TEST)  && !defined(COMPILER_TEST)
         if (numBytes == 1) {
            if (prm[tpi].staticOut8Bit != NULL) {
#ifndef _HOST_BUILD
#if MMALIB_DEBUGPRINT
               printf ("dst %p prm[tpi].staticOut8Bit %p validColsOut %d numOutChannels "
                       "%d pitchC %d outputPitchPerRow %d validColsPerRow %d\n",
                       dst,
                       prm[tpi].staticOut8Bit,
                       validColsOut,
                       numOutChannels,
                       pitchC,
                       outputPitchPerRow,
                       validColsPerRow);
#endif
                if (kerInitArgs.strideX == 1) {
                  status_opt_vs_ref =
                      TI_compare_mem_roi2DStatic ((void *) dst,
                                                  (void *) prm[tpi].staticOut8Bit,
                                                  0,
                                                  0,
                                                  validColsOut,
                                                  numOutChannels * iterN * numGroupsPerKernel,
                                                  pitchC,
                                                  numBytes);
               }
               else if (kerInitArgs.strideX > 1) {
                  status_opt_vs_ref = TI_compare_mem_3D ((void *) dst,
                                                         (void *) prm[tpi].staticOut8Bit,
                                                         0,
                                                         0,
                                                         validColsPerRow,
                                                         validOutputRows,
                                                         numOutChannels * iterN,
                                                         outputPitchPerRow,
                                                         pitchC,
                                                         numBytes);
               }
#if MMALIB_DEBUGPRINT
                  printf ("reaching comparison for host status_opt_vs_ref static\n");
                  printf (
                      "%s: status_opt_vs_ref = %d\n", __FUNCTION__, status_opt_vs_ref);
#endif
               status_nat_vs_ref = TI_TEST_KERNEL_PASS;
               status_nat_vs_opt = TI_TEST_KERNEL_PASS;

#else
#if MMALIB_DEBUGPRINT
               printf ("reaching comparison for host\n");
#endif
               if (kerInitArgs.strideX == 1) {
                  status_nat_vs_ref =
                      TI_compare_mem_roi2DStatic ((void *) dst_cn,
                                                  (void *) prm[tpi].staticOut8Bit,
                                                  0,
                                                  0,
                                                  validColsOut,
                                                  numOutChannels * iterN * numGroupsPerKernel,
                                                  pitchC,
                                                  numBytes);
#if MMALIB_DEBUGPRINT
                  printf ("reaching comparison for host status_nat_vs_ref static\n");
                  printf (
                      "%s: status_nat_vs_ref = %d\n", __FUNCTION__, status_nat_vs_ref);
#endif
               }
               else if (kerInitArgs.strideX > 1) {
                  status_nat_vs_ref = TI_compare_mem_3D ((void *) dst_cn,
                                                         (void *) prm[tpi].staticOut8Bit,
                                                         0,
                                                         0,
                                                         validColsPerRow,
                                                         validOutputRows,
                                                         numOutChannels * iterN,
                                                         outputPitchPerRow * numBytes,
                                                         pitchC,
                                                         numBytes);
               }
#endif
            }
            else {
               status_opt_vs_ref = TI_TEST_KERNEL_PASS;
               status_nat_vs_ref = TI_TEST_KERNEL_PASS;
            }
         }
         else if (numBytes == 2) {
            if (prm[tpi].staticOut16Bit != NULL) {
#ifndef _HOST_BUILD
               if (kerInitArgs.strideX == 1) {
#if MMALIB_DEBUGPRINT
               printf ("dst %p prm[tpi].staticOut8Bit %p validColsOut %d numOutChannels "
                       "%d pitchC %d outputPitchPerRow %d validColsPerRow %d\n",
                       dst,
                       prm[tpi].staticOut8Bit,
                       validColsOut,
                       numOutChannels,
                       pitchC,
                       outputPitchPerRow,
                       validColsPerRow);
#endif
                  status_opt_vs_ref =
                      TI_compare_mem_roi2DStatic ((void *) dst,
                                                  (void *) prm[tpi].staticOut16Bit,
                                                  0,
                                                  0,
                                                  validColsOut,
                                                  numOutChannels * iterN * numGroupsPerKernel,
                                                  pitchC,
                                                  numBytes);
               }
               else if (kerInitArgs.strideX > 1) {
                  status_opt_vs_ref = TI_compare_mem_3D ((void *) dst,
                                                         (void *) prm[tpi].staticOut16Bit,
                                                         0,
                                                         0,
                                                         validColsPerRow,
                                                         validOutputRows,
                                                         numOutChannels * iterN,
                                                         outputPitchPerRow,
                                                         pitchC,
                                                         numBytes);
               }
               status_nat_vs_ref = TI_TEST_KERNEL_PASS;
               status_nat_vs_opt = TI_TEST_KERNEL_PASS;
#else
#if MMALIB_DEBUGPRINT
               printf ("reaching comparison for host\n");
#endif
#if MMALIB_DEBUGPRINT
               printf ("dst %p prm[tpi].staticOut8Bit %p validColsOut %d numOutChannels "
                       "%d pitchC %d outputPitchPerRow %d validColsPerRow %d\n",
                       dst,
                       prm[tpi].staticOut8Bit,
                       validColsOut,
                       numOutChannels,
                       pitchC,
                       outputPitchPerRow,
                       validColsPerRow);
#endif
               if (kerInitArgs.strideX == 1) {
                  status_nat_vs_ref =
                      TI_compare_mem_roi2DStatic ((void *) dst_cn,
                                                  (void *) prm[tpi].staticOut16Bit,
                                                  0,
                                                  0,
                                                  validColsOut,
                                                  numOutChannels * iterN * numGroupsPerKernel,
                                                  pitchC,
                                                  numBytes);
               }

               else if (kerInitArgs.strideX > 1) {
                  status_nat_vs_ref = TI_compare_mem_3D ((void *) dst_cn,
                                                         (void *) prm[tpi].staticOut16Bit,
                                                         0,
                                                         0,
                                                         validColsPerRow,
                                                         validOutputRows,
                                                         numOutChannels * iterN,
                                                         outputPitchPerRow,
                                                         pitchC,
                                                         numBytes);
               }
#endif
            }
            else {
               status_opt_vs_ref = TI_TEST_KERNEL_PASS;
               status_nat_vs_ref = TI_TEST_KERNEL_PASS;
            }
         }

         /* Set the 'fail' flag based on test vector comparison results */
         fail = ((status_nat_vs_opt == TI_TEST_KERNEL_FAIL) ||
                 (status_opt_vs_ref == TI_TEST_KERNEL_FAIL) ||
                 (status_nat_vs_ref == TI_TEST_KERNEL_FAIL) ||
                 (status_init != MMALIB_SUCCESS) || (status_opt != MMALIB_SUCCESS) ||
                 (status_nat != MMALIB_SUCCESS))
                    ? 1
                    : 0;
#if MMALIB_DEBUGPRINT
         printf ("%s: status_nat_vs_opt = %d\n", __FUNCTION__, status_nat_vs_opt);
         printf ("%s: status_opt_vs_ref = %d\n", __FUNCTION__, status_opt_vs_ref);
         printf ("%s: status_nat_vs_ref = %d\n", __FUNCTION__, status_nat_vs_ref);
         printf ("%s: status_init       = %d\n", __FUNCTION__, status_init);
         printf ("%s: status_opt        = %d\n", __FUNCTION__, status_opt);
         printf ("%s: status_nat        = %d\n", __FUNCTION__, status_nat);
#endif
         pProfile[3 * tpi] = (int32_t) TI_profile_get_cycles (TI_PROFILE_KERNEL_OPT);
         pProfile[3 * tpi + 1] =
             (int32_t) TI_profile_get_cycles (TI_PROFILE_KERNEL_OPT_WARM);
         pProfile[3 * tpi + 2] =
             (int32_t) TI_profile_get_cycles (TI_PROFILE_KERNEL_OPT_WARMWRB);

         if (kerInitArgs.strideX == 1 ||  (kerInitArgs.strideX > 1 && kerInitArgs.Fc == 1)) {
            num_pts = numOutChannels * validColsOut * iterN;
         }
         else if (kerInitArgs.strideX > 1) {
            num_pts = numOutChannels * validOutputRows * validColsPerRow * iterN;
         }

         MMA_CNNLIB_convolveBiasReLUCompute_ixX_ixX_oxX_perfEst (&src0_addr,
                                                                 &src1_addr,
                                                                 &dst_addr,
                                                                 &kerInitArgs,
                                                                 &kerExecInArgs,
                                                                 &kerExecOutArgs,
                                                                 iterN,
                                                                 &archCycles,
                                                                 &estCycles);

         if (kerInitArgs.strideX == 1 || (kerInitArgs.strideX > 1 && kerInitArgs.Fc == 1)) {
            sprintf (desc,
                     "%s generated input | Input Channels = %d, Output per ker Channels= "
                     "%d, total Output Channels= %d, totalNCols = %d, "
                     "Output number Cols = %d, kernel width = %d strideWidth %d dilation "
                     "width = %d Predicate Bytes %d",
                     testPatternString,
                     numInChannels,
                     subMChannels,
                     numOutChannels,
                     totalN,
                     validColsOut,
                     kernelWidth,
                     strideWidth,
                     dilationWidth,
                     totalBytes);
         }
         else if (kerInitArgs.strideX > 1) {
            sprintf (desc,
                     "%s generated input | Input Channels = %d, Output per ker Channels= "
                     "%d, total Output Channels= %d, totalNCols = %d, "
                     "Output number Rows = %d, Output number Cols = %d, kernel width = "
                     "%d strideWidth %d dilation width = %d",
                     testPatternString,
                     numInChannels,
                     subMChannels,
                     numOutChannels,
                     totalN,
                     validOutputRows,
                     validColsPerRow,
                     kernelWidth,
                     strideWidth,
                     dilationWidth);
         }

         TI_profile_add_test (
                      testNum, num_pts, archCycles, estCycles, fail, desc);

#if MMALIB_DEBUGPRINT
         MMALIB_bufParams2D_t dst_addrDebug;
         dst_addrDebug.dim_x    = validColsOut;
         dst_addrDebug.dim_y    = numOutChannels * (iterN)*numGroupsPerKernel;
         dst_addrDebug.stride_y = pitchC;
         if (numBytes == 1)
            dst_addrDebug.data_type = MMALIB_INT8;
         else if (numBytes == 2)
            dst_addrDebug.data_type = MMALIB_INT16;

         printf ("The computed output is: \n");
         MMALIB_debugPrintMatrix ((char *) dst, &dst_addrDebug);
         printf ("\nThe correct output is: \n");
#if !defined(PERFORMANCE_TEST) && !defined(COMPILER_TEST)
         printf ("MMALIB_DEBUGPRINT dst: %p\n", dst_cn);
         MMALIB_debugPrintMatrix ((char *) dst_cn, &dst_addrDebug);
#endif
#endif
      }
      else {
         /* Display the error printout for this test vector before moving on to the next
          * test vector */
         TI_profile_skip_test (desc);
      }

      /* Free buffers for each test vector */
#if !defined(PERFORMANCE_TEST) && !defined(COMPILER_TEST)
      if (prm[tpi].outputDataLocation == MMALIB_TEST_OUTPUT_HEAP) {
          free (dst_cn);
      } else {}
#endif
      if (prm[tpi].outputDataLocation == MMALIB_TEST_OUTPUT_HEAP) {
         // only malloc'd data can be freed
         TI_align_free (dst);
      } else {}

      TI_align_free (src1);
      TI_align_free (src0);
      free (handle);
   }
   /* Provide memory requirements */
   TI_kernel_memory ();
   return fail;
}

int test_main (uint32_t *pProfile)
{
#ifndef _HOST_BUILD
   if (TI_cache_init ()) {
      TI_memError ("MMALIB_CNN_convolve_row_ixX_ixX_oxX");
      return 1;
   }
   else
#else
   printf ("_HOST_BUILD is defined.\n");
#endif //_HOST_BUILD
      return MMALIB_CNN_convolve_row_ixX_ixX_oxX_d (&pProfile[0], 0);
}

/* Main call for individual test projects */

int main()
{
   int fail = 1;

   uint32_t profile[256 * 3];

   MMALIB_TEST_init();

   fail = test_main(&profile[0]);

#if !defined(NO_PRINTF)
   if (fail == 0)
      printf ("Test Pass!\n");
   else
      printf ("Test Fail!\n");

   int i;
   for (i = 0; i < test_cases; i++) {
      printf ("Test %4d: Cold Cycles = %8d, Warm Cycles = %8d, Warm Cycles WRB = %8d\n",
              i,
              profile[3 * i],
              profile[3 * i + 1],
              profile[3 * i + 2]);
   }
#endif

   return fail;
}
/* ======================================================================== */
/*  End of file:  MMALIB_CNN_convolve_row_ixX_ixX_oxX_d.c                   */
/* ======================================================================== */
