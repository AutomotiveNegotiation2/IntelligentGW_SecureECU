/*
 *  Copyright (c) Texas Instruments Incorporated 2018
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
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
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/*
 *******************************************************************************
 *
 *  DMA utility functions
 *
 *******************************************************************************
*/

/**
 *****************************************************************************
 * \file  dmautils_autoincrement_3d.c
 *
 * \brief*  This file contains function implementation for dma util functions for
 *  configuring DMA on J7 device for autoincrement 3D usecase.
 *
 *
 *****************************************************************************
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "ti/drv/udma/dmautils/src/dmautils_autoincrement_3d_priv.h"
#include "ti/drv/udma/dmautils/include/dmautils_autoincrement_3d.h"
#include <ti/csl/csl_clec.h>
#include <ti/csl/arch/c7x/cslr_C7X_CPU.h>

#if defined (BUILD_C7X)
#include <c7x.h>
#endif

#define DRU_LOCAL_EVENT_START_DEFAULT  (192U)   // Default for J721E and J721S2
#define DRU_LOCAL_EVENT_START_J784S4   (664U)

/* If its a Loki Build then force the mode to be in hostemulation as Loki doesnt support DRU */
#if defined (LOKI_BUILD)
#define HOST_EMULATION (1U)
#endif

#define DMAUTILS_ALIGN_CEIL(VAL, ALIGN) ((((VAL) + (ALIGN) - 1)/(ALIGN)) * (ALIGN) )

int32_t DmaUtilsAutoInc3d_getTotalBlockCount(uint8_t * trMem, uint32_t numTr)
{
    uint32_t i;
    CSL_UdmapTR * pTr;
    uint32_t isRingBasedFlowReq = 0;
    uint32_t numTotBlks = 0;
    uint32_t triggerType;
    uint32_t srcCounts;
    uint32_t dstCounts;

    pTr = ( CSL_UdmapTR * )trMem;

    if ( numTr > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
      isRingBasedFlowReq = 1U;
    }

    if (  isRingBasedFlowReq == 1U )
    {
      /* Setup TR descriptor */
      pTr = (CSL_UdmapTR *)(trMem + sizeof(CSL_UdmapTR));
    }

    for ( i = 0; i < numTr; i++)
    {
        triggerType = CSL_FEXT(pTr[i].flags, UDMAP_TR_FLAGS_TRIGGER0_TYPE );
        if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC )
        {
            srcCounts = pTr[i].icnt1 * pTr[i].icnt2 * pTr[i].icnt3;
            dstCounts = pTr[i].dicnt1 * pTr[i].dicnt2 * pTr[i].dicnt3;
        }
        else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC )
        {
            srcCounts = pTr[i].icnt2 * pTr[i].icnt3;
            dstCounts = pTr[i].dicnt2 * pTr[i].dicnt3;
        }
        else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT3_DEC )
        {
            srcCounts = pTr[i].icnt3;
            dstCounts = pTr[i].dicnt3;
        }
        else
        {
            srcCounts = 1U;
            dstCounts = 1U;
        }

        /* Always pick the minmum of the src and dst count as once any one is exhausted TR is compete */
        numTotBlks += ( srcCounts > dstCounts) ? dstCounts : srcCounts;
    }

    return numTotBlks;

}

static inline uintptr_t DmaUtilsAutoInc3d_getPhysicalAddress(DmaUtilsAutoInc3d_Context * dmautilsContext,
                                                                 const uintptr_t virtualAddr,
                                                                 int32_t chNum);

static inline uintptr_t DmaUtilsAutoInc3d_getPhysicalAddress(DmaUtilsAutoInc3d_Context * dmautilsContext,
                                                                 const uintptr_t virtualAddr,
                                                                 int32_t chNum)
{
  uintptr_t phyAddr = virtualAddr;
  
  Udma_DrvHandle udmaDrvHandle = (Udma_DrvHandle)dmautilsContext->initParams.udmaDrvHandle;
  /* If virtual to physical address conversion function is available then use it for
  conversion else directly program the address as it is */
  if ( udmaDrvHandle->initPrms.virtToPhyFxn != NULL )
  {
      phyAddr = (uintptr_t) udmaDrvHandle->initPrms.virtToPhyFxn(
                                                          (void *)virtualAddr,
                                                          chNum,
                                                          NULL);
  }
  return phyAddr;
}

static uint32_t DmaUtilsAutoInc3d_getTrFlags(int32_t syncType)
{
    uint32_t flags;
    uint32_t triggerBoundary;
    uint32_t waitBoundary;
    switch (syncType)
    {
        case DMAUTILSAUTOINC3D_SYNC_1D :
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT1_DEC;
          break;
        }
        case DMAUTILSAUTOINC3D_SYNC_2D :
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT2_DEC;
          break;
        }
        case DMAUTILSAUTOINC3D_SYNC_3D:
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT3_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT3_DEC;
          break;
        }
        case DMAUTILSAUTOINC3D_SYNC_4D:
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION;
          break;
        }
        default :
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT2_DEC;
          break;
        }
    }

    flags =  CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING)             |
             CSL_FMK(UDMAP_TR_FLAGS_STATIC, FALSE)                                           |
             CSL_FMK(UDMAP_TR_FLAGS_EOL, FALSE)                                              |   /* NA */
             CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, waitBoundary)    |
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0)          |/*Set the trigger to local trigger*/
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, triggerBoundary)      |/* This is to transfer a 2D block for each trigger*/
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE)               |
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL)      |
             CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, 0)                                           |   /* This will come back in TR response */
             CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U)                                         |
             CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U)                                         |
             CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);

    return flags;
}

static uint32_t DmaUtilsAutoInc3d_getTrFmtFlags(DmaUtilsAutoInc3d_TransferCirc * circProp, int32_t dmaDfmt)
{
    uint32_t fmtflags = 0;
    uint32_t  eltype    = CSL_UDMAP_TR_FMTFLAGS_ELYPE_1;
    uint32_t  sectrType = CSL_UDMAP_TR_FMTFLAGS_SECTR_NONE;
    int32_t  CBK0      = CSL_UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK_512B;
    int32_t  CBK1      = CSL_UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK_512B;
    uint32_t circDir    = CSL_UDMAP_TR_FMTFLAGS_DIR_DST_USES_AMODE;
    uint32_t  AMODE     = CSL_UDMAP_TR_FMTFLAGS_AMODE_LINEAR;

	  if ( ( circProp->circSize1 != 0 ) ||
                ( circProp->circSize2 != 0 ) )
    {
        uint32_t circSize1 = circProp->circSize1;
        uint32_t circSize2 = circProp->circSize2;

        if ( circProp->circDir == DMAUTILSAUTOINC3D_CIRCDIR_SRC )
        {
          circDir = CSL_UDMAP_TR_FMTFLAGS_DIR_SRC_USES_AMODE;
        }
        else
        {
          circDir = CSL_UDMAP_TR_FMTFLAGS_DIR_DST_USES_AMODE;
        }

        CBK0 = log2((double) circSize1) - 9;
        CBK1 = log2((double)circSize2)  - 1U -CBK0;

        if ( CBK1 < 0 )
        {
           CBK1 = 0;
        }
        AMODE = CSL_UDMAP_TR_FMTFLAGS_AMODE_CIRCULAR;
     }
    if (dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP || dmaDfmt == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO (de)compression CSLs don't exist yet*/
    {
      eltype    = CSL_UDMAP_TR_FMTFLAGS_ELYPE_16;
      sectrType = CSL_UDMAP_TR_FMTFLAGS_SECTR_64;
	  }
    fmtflags =     CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE,                   AMODE                  ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_DIR,                 circDir                ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_ELYPE,               eltype                 ) |
               	   CSL_FMK(UDMAP_TR_FMTFLAGS_DFMT,                dmaDfmt                ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_SECTR,               sectrType                            ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK0, CBK0 ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK1, CBK1 ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM0, circProp->addrModeIcnt0) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM1, circProp->addrModeIcnt1) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM2, circProp->addrModeIcnt2) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM3, circProp->addrModeIcnt3);

    return fmtflags;
}


static uint32_t DmaUtilsAutoInc3d_SetupCmpSecTr(DmaUtilsAutoInc3d_TransferProp * transferProp);

static uint32_t DmaUtilsAutoInc3d_SetupCmpSecTr(DmaUtilsAutoInc3d_TransferProp * transferProp)
{
    uint32_t cmpFlags = 0;
    CSL_UdmapSecTR * secondaryTR = (CSL_UdmapSecTR *) transferProp->ioPointers.strPtr;

    if ( transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP )
    {
      secondaryTR->addr    = (uint64_t)transferProp->ioPointers.dstPtr;
      secondaryTR->data[4] = 0x0UL; /*maximum offset*/
    }
    else
    {
      secondaryTR->addr = (uint64_t)transferProp->ioPointers.srcPtr;
      secondaryTR->data[4] = (uint64_t)transferProp->ioPointers.cdbPtr - (uint64_t)transferProp->ioPointers.strPtr; /*offset to CDB table*/
    }
    
    uint32_t sectrFlags  = 1U; /*TODO CSL doesn't exist yet for compression secTR type*/

    secondaryTR->flags   = (sectrFlags & 0xF) | (transferProp->cmpProp.sbDim1 & 0xFFFFFFF0);
    secondaryTR->data[1] = ( (transferProp->cmpProp.sbIcnt0 & 0xFFFF)       )
                         | ( (transferProp->cmpProp.sbIcnt1 & 0xFFFF) << 16 );
    secondaryTR->data[2] = transferProp->cmpProp.sDim0;
    secondaryTR->data[3] = transferProp->cmpProp.dDim0;
    if ( transferProp->cmpProp.cmpAlg == 3 ) /*TODO CSL doesn't exist yet for variable K SEG type */  
    { /*Image/video compression flags setup*/
      cmpFlags    = ( (transferProp->cmpProp.cmpAlg       & 0xF )       )
                  | ( (transferProp->cmpProp.varKStartK   & 0x7 ) << 8  )
                  | ( (transferProp->cmpProp.varKUpdateK  & 0x3 ) << 12 )
                  | ( (transferProp->cmpProp.varKElemSize & 0x3 ) << 16 )
                  | ( (transferProp->cmpProp.varKSubType  & 0x7 ) << 20 )
                  | ( (transferProp->cmpProp.varKSubSel0  & 0x3 ) << 24 )
                  | ( (transferProp->cmpProp.varKSubSel1  & 0x3 ) << 26 )
                  | ( (transferProp->cmpProp.varKSubSel2  & 0x3 ) << 28 )
                  | ( (transferProp->cmpProp.varKSubSel3  & 0x3 ) << 30 );
    }
    else
    { /*Analytical compression flags setup*/
      cmpFlags    = ( (transferProp->cmpProp.cmpAlg  & 0xF )      )
                  | ( (transferProp->cmpProp.sbAM0   & 0x3 ) << 4 )
                  | ( (transferProp->cmpProp.sbAM1   & 0x3 ) << 6 )
                  | ( (transferProp->cmpProp.cmpBias & 0xFF) << 8 );
    
    }
    secondaryTR->data[0] = cmpFlags;
 
  return DMAUTILS_SOK;
}

static void DmaUtilsAutoInc3d_setupTr(CSL_UdmapTR * tr,
                                              DmaUtilsAutoInc3d_TransferProp * transferProp);

static void DmaUtilsAutoInc3d_setupTr(CSL_UdmapTR * tr,
                                              DmaUtilsAutoInc3d_TransferProp * transferProp)
{
     /* Setup flags in TR*/
    tr->flags     = DmaUtilsAutoInc3d_getTrFlags(transferProp->syncType);
    /* Configure circularity parameters if required */
    tr->fmtflags    = DmaUtilsAutoInc3d_getTrFmtFlags(&transferProp->circProp, transferProp->dmaDfmt);
    if ( transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO decompression CSLs don't exist yet*/
      tr->addr       = (uintptr_t)transferProp->ioPointers.strPtr;
    else
      tr->addr       = (uintptr_t)transferProp->ioPointers.srcPtr;
    tr->icnt0        = transferProp->transferDim.sicnt0;
    tr->icnt1        = transferProp->transferDim.sicnt1;
    tr->icnt2        = transferProp->transferDim.sicnt2;
    tr->icnt3        = transferProp->transferDim.sicnt3;
    tr->dim1        = transferProp->transferDim.sdim1;
    tr->dim2        = transferProp->transferDim.sdim2;
    tr->dim3        = transferProp->transferDim.sdim3;
    if ( transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP ) /*TODO compression CSLs don't exist yet*/
      tr->daddr      = (uintptr_t) transferProp->ioPointers.strPtr;
    else
      tr->daddr      = (uintptr_t) transferProp->ioPointers.dstPtr;
    tr->dicnt0       = transferProp->transferDim.dicnt0;
    tr->dicnt1       = transferProp->transferDim.dicnt1;
    tr->dicnt2       = transferProp->transferDim.dicnt2;
    tr->dicnt3       = transferProp->transferDim.dicnt3;
    tr->ddim1      =  transferProp->transferDim.ddim1;
    tr->ddim2      =  transferProp->transferDim.ddim2;
    tr->ddim3      =  transferProp->transferDim.ddim3;
    if (transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP || transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_DECOMP)
    {
      int32_t success = DmaUtilsAutoInc3d_SetupCmpSecTr(transferProp);
    }
}

static void DmaUtilsAutoInc3d_printf(void * autoIncrementContext, int traceLevel, const char *format, ...);
static void DmaUtilsAutoInc3d_printf(void * autoIncrementContext, int traceLevel, const char *format, ...)
{
  DmaUtilsAutoInc3d_Context * dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;
  va_list args;

  if(dmautilsContext != NULL)
  {
    if ( dmautilsContext->initParams.DmaUtilsVprintf != NULL )
    {
        if ( traceLevel < dmautilsContext->initParams.traceLogLevel)
        {
            va_start(args, format);
            dmautilsContext->initParams.DmaUtilsVprintf(format, args);
            va_end(args);
        }
    }
  }
}

static void  DmaUtilsAutoInc3d_initializeContext(void * autoIncrementContext);
static void  DmaUtilsAutoInc3d_initializeContext(void * autoIncrementContext)
{
    DmaUtilsAutoInc3d_Context * autoIncHandle = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    memset(autoIncHandle, 0, sizeof(DmaUtilsAutoInc3d_Context));

/*:TODO: This needs to be done at appropriate place*/
#ifdef HOST_EMULATION

#endif
    return ;
}


int32_t DmaUtilsAutoInc3d_getContextSize(int32_t numChannels)
{
    int32_t contextSize = 0;

    contextSize += DMAUTILS_ALIGN_CEIL(sizeof(DmaUtilsAutoInc3d_ChannelContext), 128) * numChannels;

    contextSize += DMAUTILS_ALIGN_CEIL(sizeof(DmaUtilsAutoInc3d_Context), 128);

    return contextSize;
}

static int32_t DmaUtilsAutoInc3d_setupContext(void * autoIncrementContext, DmaUtilsAutoInc3d_InitParam * initParams);
static int32_t DmaUtilsAutoInc3d_setupContext(void * autoIncrementContext, DmaUtilsAutoInc3d_InitParam * initParams)
{
    int32_t     retVal = DMAUTILS_SOK;
    int32_t memLocation = 0;
    uint8_t * memPointer;
    int32_t i;
    DmaUtilsAutoInc3d_Context * dmaUtilsContext;

    memPointer  = (uint8_t *)autoIncrementContext;
    dmaUtilsContext = (DmaUtilsAutoInc3d_Context *)memPointer;
    memLocation += DMAUTILS_ALIGN_CEIL(sizeof(DmaUtilsAutoInc3d_Context), 128);

    dmaUtilsContext->initParams = *initParams;

    for ( i = 0; i < initParams->numChannels; i++)
    {
      dmaUtilsContext->channelContext[i] = (DmaUtilsAutoInc3d_ChannelContext *) (memPointer + memLocation);
      memLocation += DMAUTILS_ALIGN_CEIL(sizeof (DmaUtilsAutoInc3d_ChannelContext), 128);
    }

    if ( memLocation > initParams->contextSize)
    {
        DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, " DmaUtilsAutoInc3d_setupContext : Failed \n");
        retVal = DMAUTILS_EINVALID_PARAMS;
    }

    return retVal;
}

static void DmaUtilsAutoInc3d_getUtcInfo(uint32_t *pUtcId, uint32_t *pDru_local_event_start)
{
  uint32_t utcId  = 0;
  uint32_t dru_local_event_start = DRU_LOCAL_EVENT_START_DEFAULT ;

#ifndef HOST_EMULATION
  uint64_t dnum;
  uint8_t corePacNum;
  /* Get the bits from bit 7 to bit 15, which represents the core pac number */
  dnum = __DNUM;    // This register is used to identify the current core
  corePacNum = CSL_REG64_FEXT(&dnum, C7X_CPU_DNUM_COREPACNUM);
  switch (corePacNum)
  {
#ifdef SOC_J784S4
    case CSL_C7X_CPU_COREPACK_NUM_C7X1:
      utcId = UDMA_UTC_ID_C7X_MSMC_DRU4;
      dru_local_event_start = DRU_LOCAL_EVENT_START_J784S4 + (96*0); // TODO: Pick from CSL if possible
      break;
    case CSL_C7X_CPU_COREPACK_NUM_C7X2:
      utcId = UDMA_UTC_ID_C7X_MSMC_DRU5;
      dru_local_event_start = DRU_LOCAL_EVENT_START_J784S4 + (96*1) ; // TODO: Pick from CSL if possible
      break;
    case CSL_C7X_CPU_COREPACK_NUM_C7X3:
      utcId = UDMA_UTC_ID_C7X_MSMC_DRU6;
      dru_local_event_start = DRU_LOCAL_EVENT_START_J784S4 + (96*2); // TODO: Pick from CSL if possible
      break;
    case CSL_C7X_CPU_COREPACK_NUM_C7X4:
      utcId = UDMA_UTC_ID_C7X_MSMC_DRU7;
      dru_local_event_start = DRU_LOCAL_EVENT_START_J784S4 + (96*3); // TODO: Pick from CSL if possible
      break;
#else
    default:  //J7ES and J721S2 will fall in this condition
      utcId = UDMA_UTC_ID_MSMC_DRU0;
      dru_local_event_start = DRU_LOCAL_EVENT_START_DEFAULT; // TODO: Pick from CSL if possible
#endif
  }
#endif
  if(pUtcId) *pUtcId = utcId ;
  if(pDru_local_event_start) *pDru_local_event_start = dru_local_event_start ;
  return ;
}

#ifndef HOST_EMULATION
//:TODO: Check if this function can be included in CSL
static int32_t DmaUtilsAutoInc3d_getClecConfigEvent(CSL_CLEC_EVTRegs *pRegs,
                            uint32_t evtNum,
                            CSL_ClecEventConfig *evtCfg)
{
    int32_t     retVal = CSL_PASS;
    uint32_t    regVal;

    if((NULL == pRegs) ||
        (evtNum >= CSL_CLEC_MAX_EVT_IN))
    {
        retVal = CSL_EFAIL;
    }
    else
    {
        /* Perform read/modify/write so that the default interrupt mode (bit 24)
         * is in power on reset value and should not be changed by CSL
         */
        regVal = CSL_REG32_RD(&pRegs->CFG[evtNum].MRR);
        evtCfg->secureClaimEnable = CSL_REG32_FEXT(&regVal, CLEC_EVT_CFG_MRR_S         );
        evtCfg->evtSendEnable     = CSL_REG32_FEXT(&regVal, CLEC_EVT_CFG_MRR_ESE       );
        evtCfg->rtMap             = CSL_REG32_FEXT(&regVal, CLEC_EVT_CFG_MRR_RTMAP     );
        evtCfg->extEvtNum         = CSL_REG32_FEXT(&regVal, CLEC_EVT_CFG_MRR_EXT_EVTNUM);
        evtCfg->c7xEvtNum         = CSL_REG32_FEXT(&regVal, CLEC_EVT_CFG_MRR_C7X_EVTNUM);
    }

    return (retVal);
}
#endif

int32_t DmaUtilsAutoInc3d_getEventNum(DmaUtilsAutoInc3d_ChannelContext * channelContext, void * autoIncrementContext)
{
  int32_t eventId;

#if !defined(HOST_EMULATION)
  uint32_t dru_local_event_start;
  CSL_ClecEventConfig   cfgClec;
  int32_t thisCore = CSL_clecGetC7xRtmapCpuId() ;

  CSL_CLEC_EVTRegs     *clecBaseAddr = (CSL_CLEC_EVTRegs*)CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE;

  DmaUtilsAutoInc3d_getUtcInfo( NULL, &dru_local_event_start) ;
  DmaUtilsAutoInc3d_getClecConfigEvent(clecBaseAddr, dru_local_event_start + channelContext->druChannelId, &cfgClec);
  if((cfgClec.rtMap !=  thisCore) && (cfgClec.rtMap != CSL_CLEC_RTMAP_CPU_ALL)){
    DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, 
    " This core (%d) is different than CLEC RTMAP CPU (%d) programming for channel %d\n",
    thisCore, cfgClec.rtMap, channelContext->druChannelId);
    return DMAUTILS_EFAIL;  
  }
  else{
    eventId = cfgClec.c7xEvtNum;
  }
#else
  //It is assumed that DRU local events are routed to 32 event of c7x
  eventId = channelContext->druChannelId + 32; // Assuming dru channel id is where the dru event will be generated
#endif

  return eventId;
}

int32_t DmaUtilsAutoInc3d_init(void * autoIncrementContext , DmaUtilsAutoInc3d_InitParam * initParams, DmaUtilsAutoInc3d_ChannelInitParam chInitParams[])
{
  uint32_t size;
  int32_t     retVal = DMAUTILS_SOK;
  int32_t i;
  uint32_t                chType;
  int32_t                eventId;
  Udma_ChPrms       chPrms;
  Udma_ChUtcPrms  utcPrms;
  DmaUtilsAutoInc3d_Context              * dmautilsContext;
  DmaUtilsAutoInc3d_ChannelContext * channelContext;
  Udma_ChHandle channelHandle;

  if ( initParams == NULL)
  {
    retVal = DMAUTILS_EBADARGS;
    goto Exit;
  }

  if ( autoIncrementContext == NULL)
  {
    retVal = DMAUTILS_EBADARGS;
    goto Exit;
  }

  size = DmaUtilsAutoInc3d_getContextSize(initParams->numChannels);

  if ( size != initParams->contextSize )
  {
    retVal = DMAUTILS_EINVALID_PARAMS;
    goto Exit;
  }
  /* Reset internal variables of autoincrement context */
  DmaUtilsAutoInc3d_initializeContext(autoIncrementContext);

  dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

  retVal = DmaUtilsAutoInc3d_setupContext(autoIncrementContext, initParams);
  if   (DMAUTILS_SOK != retVal)
  {
    goto Exit;
  }

  /* Initialize the channel params to default */
   chType = UDMA_CH_TYPE_UTC;
   UdmaChPrms_init(&chPrms, chType);
   DmaUtilsAutoInc3d_getUtcInfo( &chPrms.utcId, NULL) ;
   UdmaChUtcPrms_init(&utcPrms);

  for ( i = 0; i < initParams->numChannels; i++)
  {
      channelContext = dmautilsContext->channelContext[i];

      if ( chInitParams[i].druOwner == DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR )
      {
#ifndef DMA_UTILS_STANDALONE
          chPrms.fqRingPrms.ringMem      = NULL;
          chPrms.cqRingPrms.ringMem     = NULL;
          chPrms.tdCqRingPrms.ringMem = NULL;
          chPrms.fqRingPrms.elemCnt     = 0U;
          chPrms.cqRingPrms.elemCnt     = 0U;
          chPrms.tdCqRingPrms.elemCnt  = 0U;
#endif
          utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
      }
      else
      {
#ifndef DMA_UTILS_STANDALONE
          chPrms.fqRingPrms.ringMem     = &channelContext->ringMem;
          chPrms.cqRingPrms.ringMem    = &channelContext->responseRingMem;
          chPrms.tdCqRingPrms.ringMem = NULL;
          chPrms.fqRingPrms.ringMemSize = sizeof(uint64_t);
          chPrms.cqRingPrms.ringMemSize = sizeof(uint64_t);
          chPrms.tdCqRingPrms.ringMemSize = 0;
          chPrms.fqRingPrms.elemCnt      = 1U;/* We have only one element per ring */
          chPrms.cqRingPrms.elemCnt     = 1U;/* We have only one element per ring */
          chPrms.tdCqRingPrms.elemCnt  = 0U;/* We have only one element per ring */
#endif
          utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
      }

      channelHandle = &(channelContext->chHandle);

      retVal = Udma_chOpen((Udma_DrvHandle)initParams->udmaDrvHandle, channelHandle, chType, &chPrms);
      if(DMAUTILS_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "Udma_chOpen : Failed \n");
         goto Exit;
      }

      /* Config UTC channel */
      utcPrms.druQueueId  =chInitParams[i].dmaQueNo;

      retVal = Udma_chConfigUtc(channelHandle, &utcPrms);
      if(DMAUTILS_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "Udma_chConfigUtc : Failed \n");
          goto Exit;
      }

      /* Enable The channel */
      retVal = Udma_chEnable(channelHandle);
      if(DMAUTILS_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "Udma_chEnable : Failed \n");
          goto Exit;
      }
      channelContext->druChannelId = Udma_chGetNum(channelHandle);
      channelContext->swTriggerPointer = Udma_druGetTriggerRegAddr(channelHandle);

      eventId = DmaUtilsAutoInc3d_getEventNum(channelContext, autoIncrementContext);
      if(eventId == DMAUTILS_EFAIL)
      {
        retVal = DMAUTILS_EFAIL;
        goto Exit;
      }
      channelContext->waitWord =  ((uint64_t)1U << eventId);
  }

Exit:
    return retVal;
}

int32_t DmaUtilsAutoInc3d_getTrMemReq(int32_t numTRs)
{
    int32_t isRingBasedFlowReq = 0;
    int32_t trMemReq = 0;

    if ( numTRs > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
      isRingBasedFlowReq = 1;
    }

    if ( isRingBasedFlowReq )
    {
         //:TODO: Check how to make sure align required
         /* This indicates ring accelerator mode and hence will need memory for TR descriptor */
        trMemReq = sizeof(CSL_UdmapCppi5TRPD) + /* Number of Bytes for TR descriptor */
                               sizeof(CSL_UdmapTR) + /* Padding required to bring start of TR request to natural alignment for memory fetch efficiency */
                               numTRs * sizeof(CSL_UdmapTR) + /* Memory for Transfer Records */
                               numTRs * sizeof(uint32_t);/* Memory for Transfer Response Records */
    }
    else
    {
      trMemReq = numTRs * sizeof(CSL_UdmapTR);
    }

    return trMemReq;
}


int32_t DmaUtilsAutoInc3d_prepareTr(DmaUtilsAutoInc3d_TrPrepareParam * trPrepParam ,
                                            DmaUtilsAutoInc3d_TransferProp transferProp[])
{
    int32_t size;
    int32_t     retVal = DMAUTILS_SOK;
    int32_t isRingBasedFlowReq = 0;
    CSL_UdmapTR * pTrArray;
    int32_t i;

    if ( trPrepParam == NULL )
    {
      retVal = DMAUTILS_EBADARGS;
      goto Exit;
    }

    size = DmaUtilsAutoInc3d_getTrMemReq(trPrepParam->numTRs);

    if ( trPrepParam->trMemSize < size )
    {
      retVal = DMAUTILS_EINVALID_PARAMS;
      goto Exit;
    }

    if ( trPrepParam->trMem == NULL )
    {
      retVal = DMAUTILS_EBADARGS;
      goto Exit;
    }

    if ( trPrepParam->numTRs > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
        isRingBasedFlowReq = 1;
    }

    pTrArray = (CSL_UdmapTR *)trPrepParam->trMem;

    if ( isRingBasedFlowReq == 1 )
    {
#ifndef DMA_UTILS_STANDALONE
      /* This needs to be updated with correct value during configure */
      uint32_t cqRingNum = 0;
      /* Setup TR descriptor */

      CSL_UdmapCppi5TRPD * pTrpd = (CSL_UdmapCppi5TRPD *)trPrepParam->trMem;
      CSL_UdmapTR           *pTr = (CSL_UdmapTR *)(trPrepParam->trMem + sizeof(CSL_UdmapTR));

      UdmaUtils_makeTrpd(pTrpd, UDMA_TR_TYPE_9, trPrepParam->numTRs, cqRingNum);
      pTrArray = pTr;
#endif
    }

    for ( i = 0; i < trPrepParam->numTRs ; i++)
    {
        DmaUtilsAutoInc3d_setupTr(&pTrArray[i], &transferProp[i]);
    }


Exit:

    return retVal;

}


int32_t DmaUtilsAutoInc3d_prepareTrWithPhysicalAddress(void * autoIncrementContext,
                                           DmaUtilsAutoInc3d_TrPrepareParam * trPrepParam ,
                                           DmaUtilsAutoInc3d_TransferProp transferProp[])
{
    int32_t     retVal = DMAUTILS_SOK;
    uint32_t convertMask = ( DMAUTILSAUTOINC3D_ADDRCONVERTMASK_SRCADDR | DMAUTILSAUTOINC3D_ADDRCONVERTMASK_DSTADDR);
    retVal = DmaUtilsAutoInc3d_prepareTr(trPrepParam, transferProp);

    if ( retVal == DMAUTILS_SOK )
    {
        retVal = DmaUtilsAutoInc3d_convertTrVirtToPhyAddr(autoIncrementContext,
                                                        trPrepParam,
                                                        convertMask);
    }
    return retVal;
}


int32_t DmaUtilsAutoInc3d_convertTrVirtToPhyAddr(void * autoIncrementContext,
                                            DmaUtilsAutoInc3d_TrPrepareParam * trPrepParam ,
                                            uint32_t convertMask)
{
    int32_t     retVal = DMAUTILS_SOK;
    int32_t isRingBasedFlowReq = 0;
    CSL_UdmapTR * pTrArray;
    int32_t i;
    DmaUtilsAutoInc3d_Context        * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    int32_t druChannelNum;
    Udma_DrvHandle udmaDrvHandle;

    if ( autoIncrementContext == NULL )
    {
      retVal = DMAUTILS_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_convertTrVirtToPhyAddr : Failed :autoIncrementContext == NULL \n");
      goto Exit;
    }
    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;
    udmaDrvHandle = (Udma_DrvHandle)dmautilsContext->initParams.udmaDrvHandle;
    
    /* Do not call the translation function if the pointer is already NULL */
    if ( udmaDrvHandle->initPrms.virtToPhyFxn != NULL )
    {
        if ( trPrepParam == NULL )
        {
          retVal = DMAUTILS_EBADARGS;
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_convertTrVirtToPhyAddr : Failed :trPrepParam == NULL \n");
          goto Exit;
        }

        if ( trPrepParam->trMem == NULL )
        {
          retVal = DMAUTILS_EBADARGS;
          goto Exit;
        }

        channelContext = dmautilsContext->channelContext[trPrepParam->channelId];

        druChannelNum = channelContext->druChannelId;

        if ( trPrepParam->numTRs > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
        {
            isRingBasedFlowReq = 1;
        }

        pTrArray = (CSL_UdmapTR *)trPrepParam->trMem;

        if ( isRingBasedFlowReq == 1 )
        {
          CSL_UdmapTR           *pTr = (CSL_UdmapTR *)(trPrepParam->trMem + sizeof(CSL_UdmapTR));
          pTrArray = pTr;
        }

        for ( i = 0; i < trPrepParam->numTRs ; i++)
        {
            if (( convertMask & DMAUTILSAUTOINC3D_ADDRCONVERTMASK_SRCADDR) ==
              DMAUTILSAUTOINC3D_ADDRCONVERTMASK_SRCADDR)
            {
                pTrArray[i].addr = DmaUtilsAutoInc3d_getPhysicalAddress(dmautilsContext,
                                                                        pTrArray[i].addr,
                                                                        druChannelNum);
            }
            if (( convertMask & DMAUTILSAUTOINC3D_ADDRCONVERTMASK_DSTADDR) ==
              DMAUTILSAUTOINC3D_ADDRCONVERTMASK_DSTADDR)
            {
                pTrArray[i].daddr = DmaUtilsAutoInc3d_getPhysicalAddress(dmautilsContext,
                                                                        pTrArray[i].daddr,
                                                                        druChannelNum);
            }
        }
    }
Exit:
      return retVal;

}

int32_t DmaUtilsAutoInc3d_configure(void * autoIncrementContext, int32_t channelId, uint8_t * trMem, int32_t numTr)
{
    int32_t     retVal = DMAUTILS_SOK;
    DmaUtilsAutoInc3d_Context              * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    uint32_t isRingBasedFlowReq =0;
    Udma_ChHandle channelHandle;

    uint32_t i;

#ifdef HOST_EMULATION
    uint32_t druChannelNum;
    Udma_DrvHandle udmaDrvHandle;
#endif
    if ( autoIncrementContext == NULL)
    {
      retVal = DMAUTILS_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed :autoIncrementContext == NULL \n");
      goto Exit;
    }

    if ( trMem == NULL )
    {
      retVal = DMAUTILS_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed : trMem == NULL \n");
      goto Exit;
    }

    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    channelContext = dmautilsContext->channelContext[channelId];
    channelHandle = &channelContext->chHandle;

    if ( numTr > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
        isRingBasedFlowReq = 1U;
    }
    
    if ( isRingBasedFlowReq  == 0U)
    {

        CSL_UdmapTR * tr;

        tr = ( CSL_UdmapTR *)trMem;

        /* Submit the TR using atomic write */
        //:TODO: currently host emulation doesn't handle multiple TR in direct TR mode
        for ( i = 0; i < numTr; i++)
        {
#ifndef HOST_EMULATION
          Udma_chDruSubmitTr(channelHandle, tr + i);
#else
          udmaDrvHandle = (Udma_DrvHandle)dmautilsContext->initParams.udmaDrvHandle;
          druChannelNum = Udma_chGetNum(channelHandle);
          hostEmulation_druChSubmitAtomicTr(udmaDrvHandle->utcInfo[0].druRegs,
                                                                                druChannelNum , (void *)tr);
#endif
        }
    }
#ifndef DMA_UTILS_STANDALONE
    else
    {
      uint32_t cqRingNum = Udma_chGetCqRingNum(channelHandle);

      CSL_UdmapCppi5TRPD * pTrpd = (CSL_UdmapCppi5TRPD *)trMem;

      /* Update the cq ring number as it was not set correctly during descriptor preperation */
      CSL_udmapCppi5SetReturnPolicy(
              pTrpd,
              CSL_UDMAP_CPPI5_PD_DESCINFO_DTYPE_VAL_TR,
              CSL_UDMAP_CPPI5_PD_PKTINFO2_RETPOLICY_VAL_ENTIRE_PKT,
              CSL_UDMAP_CPPI5_PD_PKTINFO2_EARLYRET_VAL_NO,
              CSL_UDMAP_CPPI5_PD_PKTINFO2_RETPUSHPOLICY_VAL_TO_TAIL,
              cqRingNum);

      Udma_ringQueueRaw(Udma_chGetFqRingHandle(channelHandle),
              (uint64_t)trMem);

#ifdef HOST_EMULATION
      CSL_UdmapTR           *pTr = (CSL_UdmapTR *)(trMem + sizeof(CSL_UdmapTR));
      udmaDrvHandle = (Udma_DrvHandle)dmautilsContext->initParams.udmaDrvHandle;
      druChannelNum = (channelHandle->extChNum - channelHandle->utcInfo->startCh);
      hostEmulation_druChSubmitAtomicTr(udmaDrvHandle->utcInfo[0].druRegs,
                                                                        druChannelNum,
                                                                        (void *)pTr);

      /* Use this field to track the TR, For the target build this would be handled by hardware */
      /* In real hardware this will not be like this it is done just for host emulation*/
      udmaDrvHandle->utcInfo[0].druRegs->CHATOMIC[druChannelNum].DEBUG[1].NEXT_TR_WORD0_1 = 1;

#endif
    }
#endif
    dmautilsContext->blkIdx[channelId] = DmaUtilsAutoInc3d_getTotalBlockCount(trMem, numTr);
Exit :

    return retVal;

}


int32_t DmaUtilsAutoInc3d_trigger(void * autoIncrementContext, int32_t channelId)
{
    DmaUtilsAutoInc3d_Context              * dmautilsContext;

    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    CSL_druChSetGlobalTrigger0Raw(dmautilsContext->channelContext[channelId]->swTriggerPointer);//:TODO: This should be replaced by something else as we are not suppose to directly use these registers
#ifdef HOST_EMULATION
    Udma_DrvHandle udmaDrvHandle = (Udma_DrvHandle)dmautilsContext->initParams.udmaDrvHandle;
    hostEmulation_updateTriggerCount(udmaDrvHandle, dmautilsContext->channelContext[channelId]->swTriggerPointer);
#endif

    dmautilsContext->blkIdx[channelId]--;

    return dmautilsContext->blkIdx[channelId];
}



void  DmaUtilsAutoInc3d_wait(void * autoIncrementContext, int32_t channelId)
{
    DmaUtilsAutoInc3d_Context              * dmautilsContext;

    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

#ifndef HOST_EMULATION
    volatile uint64_t eflRegisterVal;
    uint64_t waitWord;

    waitWord = dmautilsContext->channelContext[channelId]->waitWord;
    eflRegisterVal = __get_indexed(__EFR,0);
    while((eflRegisterVal & waitWord ) != waitWord )
    {
      eflRegisterVal = __get_indexed(__EFR,0);
    }
    __set_indexed(__EFCLR,0, waitWord);
#else
    Udma_DrvHandle udmaDrvHandle = (Udma_DrvHandle)dmautilsContext->initParams.udmaDrvHandle;
    /* Do the actual Transfer for host emulation*/
    hostEmulation_triggerDMA(udmaDrvHandle);
#endif

    return;
}


int32_t DmaUtilsAutoInc3d_deconfigure(void * autoIncrementContext, int32_t channelId, uint8_t * trMem, int32_t numTr)
{
    int32_t     retVal = DMAUTILS_SOK;
#ifndef DMA_UTILS_STANDALONE
    DmaUtilsAutoInc3d_Context              * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    Udma_ChHandle channelHandle;
#endif
    uint32_t isRingBasedFlowReq =0;

    if ( autoIncrementContext == NULL)
    {
      retVal = DMAUTILS_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed :autoIncrementContext == NULL \n");
      goto Exit;
    }

    if ( trMem == NULL )
    {
      retVal = DMAUTILS_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed : trMem == NULL \n");
      goto Exit;
    }

#ifndef DMA_UTILS_STANDALONE
    dmautilsContext = ( DmaUtilsAutoInc3d_Context *)autoIncrementContext;
    channelContext = dmautilsContext->channelContext[channelId];
    channelHandle = &channelContext->chHandle;
#endif

    /* disable  The channel */
    if ( numTr > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
        isRingBasedFlowReq = 1U;
    }

    if ( isRingBasedFlowReq  == 1 )
    {
#ifndef DMA_UTILS_STANDALONE
       uint64_t    pDesc = 0;
      retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(channelHandle), &pDesc);
      if(DMAUTILS_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_deconfigure : Failed : Udma_ringDequeueRaw\n");
          retVal = DMAUTILS_EFAIL;
          goto Exit;
      }
#endif
    }

Exit:
    return retVal;

}


int32_t DmaUtilsAutoInc3d_deinit(void * autoIncrementContext)
{
    int32_t     retVal = DMAUTILS_SOK;
    DmaUtilsAutoInc3d_Context              * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    Udma_ChHandle channelHandle;
    int32_t i;
    if ( autoIncrementContext == NULL)
    {
        retVal = DMAUTILS_EBADARGS;
        DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed :autoIncrementContext == NULL \n");
        goto Exit;
    }

    dmautilsContext = ( DmaUtilsAutoInc3d_Context *)autoIncrementContext;
    for ( i = 0; i < dmautilsContext->initParams.numChannels; i++)
     {
         channelContext = dmautilsContext->channelContext[i];
         channelHandle = &(channelContext->chHandle);

#if !HOST_EMULATION
         /* Avoid calling chDisable API for host emulation as it depends on some of the hardware sequence
         which are not emulated in host emulation */
         retVal = Udma_chDisable(channelHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
#endif
         if(DMAUTILS_SOK != retVal)
         {
             DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_deconfigure : Failed : Udma_chDisable\n");
             retVal = DMAUTILS_EFAIL;
             goto Exit;
         }

         retVal = Udma_chClose(channelHandle);
         if(DMAUTILS_SOK != retVal)
         {
             DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_deinit : Udma_chClose : Failed \n");
            goto Exit;
         }
    }
Exit:

    return retVal;

}
