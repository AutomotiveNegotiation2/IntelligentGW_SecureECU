/*
*
* Copyright (c) 2023 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/**
 *  \file     Spi_Mcspi.c
 *
 *  \brief    This file contains SPI MCAL driver functions for the McSPI
 *            peripheral
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "Spi_Cfg.h"
#include "Spi.h"
#include "Spi_Priv.h"
#include "Dem.h"
#include "Os.h"

/* There are static inline functions in hw_types.h file. Map them as well */
#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"
#include <hw_include/lldr.h>
#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"

#include <hw_include/lldr_mcspi.h>



/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Total length of FIFO for both TX/RX */
#define MCSPI_FIFO_LENGTH               (128U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void Spi_mcspiReadFifo(Spi_ChannelObjType *chObj,
                              uint32              baseAddr,
                              uint32              csNum);
static void Spi_mcspiWriteFifo(Spi_ChannelObjType *chObj,
                               uint32              baseAddr,
                               uint32              csNum);
static void Spi_mcspiInitiateChunkXfer(const Spi_ChannelObjType *chObj,
                                       const Spi_JobObjType     *jobObj,
                                       uint32                    baseAddr);
static uint32 Spi_mcspiGetTxRxMasks(uint32 csNum);
static void Spi_mcspiReset(uint32 baseAddr);
static void Spi_mcspiConfigDataPinDir(
    const Spi_HwUnitObjType *hwUnitObj, const Spi_JobObjType *jobObj);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/*
 * Design: MCAL-6398
 */
SPI_FUNC_TEXT_SECTION void Spi_mcspiInit(const Spi_HwUnitObjType *hwUnitObj)
{
    uint32 regVal;
    uint32 baseAddr, index, csNum;
    Spi_JobObjType  *jobObj;
    Spi_McspiExternalDeviceConfigType *extDevCfg;

    baseAddr = hwUnitObj->baseAddr;

    /* Reset McSPI */
    Spi_mcspiReset(baseAddr);

    /* Set sysconfig */
    regVal = ((MCSPI_SYSCONFIG_CLOCKACTIVITY_BOTH <<
               MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT) |
              (MCSPI_SYSCONFIG_SIDLEMODE_NO <<
               MCSPI_SYSCONFIG_SIDLEMODE_SHIFT) |
              (MCSPI_SYSCONFIG_ENAWAKEUP_NOWAKEUP <<
               MCSPI_SYSCONFIG_ENAWAKEUP_SHIFT) |
              (MCSPI_SYSCONFIG_AUTOIDLE_OFF <<
               MCSPI_SYSCONFIG_AUTOIDLE_SHIFT));
    CSL_REG32_WR(baseAddr + MCSPI_SYSCONFIG, regVal);

    /* Dynamic coverage, for fail condition in for loop cannot be achievable,
    * as hwUnitObj or hwUnit id or SPI_MAX_JOB, can be detected and report the
    * DET error inearlier stage itself */
    for (index = 0U; index < SPI_MAX_JOBS; index++)
    {
        jobObj =  &Spi_DrvObj.jobObj[index];
        if (hwUnitObj->hwUnitCfg.hwUnitId == jobObj->jobCfg.hwUnitId)
        {
            csNum     = (uint32)(jobObj->jobCfg_PC.csPin);
            extDevCfg = &jobObj->extDevCfg->mcspi;
            /* Set CS polarity */
            if (SPI_LOW == extDevCfg->csPolarity)
            {
                CSL_REG32_FINS(
                    baseAddr + MCSPI_CHCONF(csNum),
                    MCSPI_CH0CONF_EPOL,
                    MCSPI_CH0CONF_EPOL_ACTIVELOW);
            }
            else
            {
                CSL_REG32_FINS(
                    baseAddr + MCSPI_CHCONF(csNum),
                    MCSPI_CH0CONF_EPOL,
                    MCSPI_CH0CONF_EPOL_ACTIVEHIGH);
            }

            /* Applicable only for single channel master mode only.
               In case of multi-channel, this pin has no effect  */
            CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_FORCE,
            MCSPI_CH0CONF_FORCE_DEASSERT);

            break;
        }
    }

    /* Set master mode - MCAL supports only master mode */
    CSL_REG32_FINS(
        baseAddr + MCSPI_MODULCTRL,
        MCSPI_MODULCTRL_MS,
        MCSPI_MODULCTRL_MS_MASTER);

    return;
}

/*
 * Design: MCAL-6734
 */
SPI_FUNC_TEXT_SECTION void Spi_mcspiDeInit(const Spi_HwUnitObjType *hwUnitObj)
{
    /* Reset McSPI */
    Spi_mcspiReset(hwUnitObj->baseAddr);

    return;
}

SPI_FUNC_TEXT_SECTION void Spi_mcspiConfigJob(const Spi_HwUnitObjType *hwUnitObj,
                        Spi_JobObjType          *jobObj)
{
    uint32 baseAddr, regVal, csNum, clkD, extClk;
    uint32 txFifoTrigLvl, rxFifoTrigLvl;
    Spi_McspiExternalDeviceConfigType *extDevCfg;
    uint32 clkModeTemp;

    baseAddr  = hwUnitObj->baseAddr;
    csNum     = (uint32)(jobObj->jobCfg_PC.csPin);
    extDevCfg = &jobObj->extDevCfg->mcspi;

    /*
     * Set Data Pin Directions
     */
    Spi_mcspiConfigDataPinDir(hwUnitObj, jobObj);

    /*
     * Set all CS related functionality
     */
    /* Set 3-pin mode (CS disable) or 4-pin mode CS enable */
    if (((uint32) FALSE) == extDevCfg->csEnable)
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_MODULCTRL,
            MCSPI_MODULCTRL_PIN34,
            MCSPI_MODULCTRL_PIN34_3PINMODE);
    }
    else
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_MODULCTRL,
            MCSPI_MODULCTRL_PIN34,
            MCSPI_MODULCTRL_PIN34_4PINMODE);
    }

    if (SPI_CONTINUOUS == extDevCfg->csMode)
    {
        /* In continuous mode, CS is controlled by driver by setting FORCE
         * enable bit just before starting */
        CSL_REG32_FINS(
            baseAddr + MCSPI_MODULCTRL,
            MCSPI_MODULCTRL_SINGLE,
            MCSPI_MODULCTRL_SINGLE_SINGLE);
    }
    else
    {
        /* In single mode, let the hardware decide when to toggle the CS */
        CSL_REG32_FINS(
            baseAddr + MCSPI_MODULCTRL,
            MCSPI_MODULCTRL_SINGLE,
            MCSPI_MODULCTRL_SINGLE_MULTI);
    }

    /* Set CS polarity */
    if (SPI_LOW == extDevCfg->csPolarity)
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_EPOL,
            MCSPI_CH0CONF_EPOL_ACTIVELOW);
    }
    else
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_EPOL,
            MCSPI_CH0CONF_EPOL_ACTIVEHIGH);
    }

    /* Set the TCS0 field - delay between CS active and first CLK toggling */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_TCS0,
        extDevCfg->csIdleTime);

    /*
     * Set clock configuration
     */
    /* Set divider */
    extClk = (extDevCfg->clkDivider >> ((uint32) 4U));      /* MSB 8-bit */
    clkD   = (extDevCfg->clkDivider & ((uint32) 0x0FU));    /* LSB 4-bit */
    CSL_REG32_FINS(baseAddr + MCSPI_CHCTRL(csNum), MCSPI_CH0CTRL_EXTCLK, extClk);
    CSL_REG32_FINS(baseAddr + MCSPI_CHCONF(csNum), MCSPI_CH0CONF_CLKD, clkD);
    /* Set the clock granularity to 1 clock cycle.*/
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_CLKG,
        MCSPI_CH0CONF_CLKG_ONECYCLE);
    /* Set clock mode */
    regVal  = CSL_REG32_RD(baseAddr + MCSPI_CHCONF(csNum));
    regVal &= ~(MCSPI_CH0CONF_PHA_MASK | MCSPI_CH0CONF_POL_MASK);
    clkModeTemp = (uint32) extDevCfg->clkMode;
    regVal |= (clkModeTemp &
               (MCSPI_CH0CONF_PHA_MASK | MCSPI_CH0CONF_POL_MASK));
    CSL_REG32_WR(baseAddr + MCSPI_CHCONF(csNum), regVal);

    /*
     * Set start bit params
     */
    if (((uint32) FALSE) == extDevCfg->startBitEnable)
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_SBE,
            MCSPI_CH0CONF_SBE_DISABLED);
    }
    else
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_SBE,
            MCSPI_CH0CONF_SBE_ENABLED);
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_SBPOL,
            extDevCfg->startBitLevel);
    }

    /* Set TX/RX mode */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_TRM,
        extDevCfg->txRxMode);

    /*
     * Note: TX/RX FIFO trigger levels are set to half the TX/RX FIFO levels,
     *       so that it is efficient as well as we don't get TX underflow or
     *       RX overflow.
     *       Setting a low value is in-efficient where as setting a high value
     *       leads to overflow/underflow!!
     */
    /* Calculate effective FIFO Trigger level */
    rxFifoTrigLvl = 0U;
    if (extDevCfg->txRxMode == SPI_TX_RX_MODE_BOTH)
    {
        /* Both TX/RX is used, divide the FIFO equally */
        txFifoTrigLvl = (MCSPI_FIFO_LENGTH >> 2U) - 1U;
        rxFifoTrigLvl = (MCSPI_FIFO_LENGTH >> 2U) - 1U;
    }
    else
    {
        /* TX only mode, full FIFO is used for TX */
        txFifoTrigLvl = (MCSPI_FIFO_LENGTH >> 1U) - 1U;
    }
    jobObj->txFifoTrigLvl = txFifoTrigLvl + 1U; /* To compensate for -1U */
    jobObj->rxFifoTrigLvl = rxFifoTrigLvl + 1U; /* To compensate for -1U */

    return;
}

/*
 * Design: MCAL-6521
 */
SPI_FUNC_TEXT_SECTION void Spi_mcspiConfigCh(const Spi_HwUnitObjType *hwUnitObj,
                       const Spi_JobObjType    *jobObj,
                       Spi_ChannelObjType      *chObj)
{
    uint32 baseAddr, csNum;
    uint32 txFifoTrigLvl, rxFifoTrigLvl;
    uint32 regVal, reminder, effNumWordsTxRx;

    baseAddr = hwUnitObj->baseAddr;
    csNum    = (uint32)(jobObj->jobCfg_PC.csPin);

    /* Reset counter and other params */
#if ((SPI_CHANNELBUFFERS == SPI_EB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
    if (SPI_EB == chObj->chCfg.channelBufType)
    {
        chObj->curTxBufPtr = chObj->txBufPtr;
        chObj->curRxBufPtr = chObj->rxBufPtr;
    }
#endif
#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
    if (SPI_IB == chObj->chCfg.channelBufType)
    {
        chObj->curTxBufPtr = (const uint8 *) &chObj->txIb[0U];
        chObj->curRxBufPtr = (uint8 *) &chObj->rxIb[0U];
    }
#endif
    chObj->curTxWords  = 0U;
    chObj->curRxWords  = 0U;
    chObj->effTxFifoDepth = jobObj->txFifoTrigLvl / chObj->bufWidth;

    /*
     * Set all the channel parameters
     */
    /* Set wordlength in bits */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_WL,
        ((uint32) chObj->chCfg.dataWidth - 1U));

    /* Start transferring only multiple of FIFO trigger level */
    reminder = (((uint32) chObj->numWordsTxRx) & (chObj->effTxFifoDepth - 1U));

    effNumWordsTxRx = ((uint32) chObj->numWordsTxRx) - reminder;

    rxFifoTrigLvl = jobObj->rxFifoTrigLvl;
    txFifoTrigLvl = jobObj->txFifoTrigLvl;
    /* Handle transfers with less than FIFO level.
     * Set FIFO trigger level and word count to be equal to the
     * reminder word. Otherwise the HW doesn't generating TX
     * empty interrupt if WCNT is less than FIFO trigger level */
    if (effNumWordsTxRx == 0U)
    {
        effNumWordsTxRx = reminder;
        if (rxFifoTrigLvl != 1U)
        {
            /* Set RX level only when RX FIFO is enabled */
            rxFifoTrigLvl = reminder;
        }
        txFifoTrigLvl = reminder;
    }

    /* Set FIFO trigger level and word count */
    regVal  = CSL_REG32_RD(baseAddr + MCSPI_XFERLEVEL);
    regVal &= ~(MCSPI_XFERLEVEL_AFL_MASK | MCSPI_XFERLEVEL_AEL_MASK);
    regVal |= (((rxFifoTrigLvl - 1U) << MCSPI_XFERLEVEL_AFL_SHIFT) &
               MCSPI_XFERLEVEL_AFL_MASK);
    regVal |= (((txFifoTrigLvl - 1U) << MCSPI_XFERLEVEL_AEL_SHIFT) &
               MCSPI_XFERLEVEL_AEL_MASK);
    regVal &= ~MCSPI_XFERLEVEL_WCNT_MASK;
    regVal |= ((effNumWordsTxRx << MCSPI_XFERLEVEL_WCNT_SHIFT) &
               MCSPI_XFERLEVEL_WCNT_MASK);
    CSL_REG32_WR(baseAddr + MCSPI_XFERLEVEL, regVal);

    return;
}

SPI_FUNC_TEXT_SECTION void Spi_mcspiStart(const Spi_HwUnitObjType *hwUnitObj,
                    const Spi_JobObjType    *jobObj,
                    uint32                   isIntrMode)
{
    uint32 baseAddr, csNum, intrMask, csIntrMask;
    Spi_McspiExternalDeviceConfigType *extDevCfg;

    baseAddr  = hwUnitObj->baseAddr;
    csNum     = (uint32)(jobObj->jobCfg_PC.csPin);
    extDevCfg = &jobObj->extDevCfg->mcspi;

    /* Clear all previous interrupt status */
    Spi_mcspiClearAllIrqStatus(baseAddr);

    /* Enable TX and RX FIFO */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_FFEW,
        MCSPI_CH0CONF_FFEW_FFENABLED);
    if (extDevCfg->txRxMode == SPI_TX_RX_MODE_BOTH)
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_FFER,
            MCSPI_CH0CONF_FFER_FFENABLED);
    }

    if (((uint32) TRUE) == isIntrMode)
    {
        /* Enable EOW, TX and RX interrupts */
        intrMask   = CSL_REG32_RD(baseAddr + MCSPI_IRQENABLE);
        intrMask  |= MCSPI_IRQSTATUS_EOW_MASK;
        csIntrMask = Spi_mcspiGetCsIntrMask(csNum, extDevCfg->txRxMode);
        intrMask  |= csIntrMask;
        CSL_REG32_WR(baseAddr + MCSPI_IRQENABLE, intrMask);
    }

    /* Set force mode */
    if (SPI_CONTINUOUS == extDevCfg->csMode)
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_FORCE,
            MCSPI_CH0CONF_FORCE_ASSERT);
    }

    /* Enable channel */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCTRL(csNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_ACT);

    /*
     * Note: Once the channel is enabled, we will get the TX almost empty
     *       interrupt. No data transfer is required here!!
     */

    return;
}

SPI_FUNC_TEXT_SECTION void Spi_mcspiReStart(const Spi_HwUnitObjType *hwUnitObj,
                      const Spi_JobObjType    *jobObj)
{
    uint32 baseAddr, csNum;

    baseAddr = hwUnitObj->baseAddr;
    csNum    = (uint32)(jobObj->jobCfg_PC.csPin);

    /* Disable channel and re-enable so that new word count takes effect */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCTRL(csNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_NACT);
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCTRL(csNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_ACT);

    return;
}

/*
 * Design: MCAL-6376,MCAL-6446,MCAL-6621,MCAL-6600
 */
SPI_FUNC_TEXT_SECTION Spi_JobResultType Spi_mcspiContinueTxRx(
    const Spi_HwUnitObjType *hwUnitObj,
    const Spi_JobObjType    *jobObj,
    Spi_ChannelObjType      *chObj)
{
    uint32 baseAddr, csNum;
    uint32 intrStatus, txEmptyMask;
    Spi_JobResultType                  jobResult = SPI_JOB_PENDING;
    Spi_McspiExternalDeviceConfigType *extDevCfg;

    baseAddr    = hwUnitObj->baseAddr;
    extDevCfg   = &jobObj->extDevCfg->mcspi;
    csNum       = (uint32)(jobObj->jobCfg_PC.csPin);
    txEmptyMask = Spi_mcspiGetTxRxMasks(csNum);

    /* Get interrupt status */
    intrStatus = CSL_REG32_RD(baseAddr + MCSPI_IRQSTATUS);

    /* clear interrupt status */
    CSL_REG32_WR(baseAddr + MCSPI_IRQSTATUS, intrStatus);

    /*
     * Read out all RX data first in case RX mode is enabled.
     */
    if (extDevCfg->txRxMode == SPI_TX_RX_MODE_BOTH)
    {
        Spi_mcspiReadFifo(chObj, baseAddr, csNum);
    }

#if (SPI_E_HARDWARE_ERROR != SPI_DEM_NO_EVENT)
    (void)Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
#endif

    /*
     * Handle TX events
     */
    if ((intrStatus & txEmptyMask) == txEmptyMask)
    {
        Spi_mcspiWriteFifo(chObj, baseAddr, csNum);
    }

    /*
     * TX/RX is complete
     */
    if ((intrStatus & MCSPI_IRQSTATUS_EOW_MASK) == MCSPI_IRQSTATUS_EOW_MASK)
    {
        if (chObj->numWordsTxRx == chObj->curTxWords)
        {
            /* This channel transfer is complete */
            jobResult = SPI_JOB_OK;
        }
        else
        {
            /* Initiate the reminder transfer */
            Spi_mcspiInitiateChunkXfer(chObj, jobObj, baseAddr);
        }
    }

    return (jobResult);
}

SPI_FUNC_TEXT_SECTION Spi_JobResultType Spi_mcspiXferJob(
    const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj)
{
    uint32              index;
    Spi_ChannelType     chId;
    Spi_ChannelObjType *chObj;
    Spi_JobResultType   jobResult = SPI_JOB_OK;

    /* Transfer all the channels */
    for (index = 0U; index < jobObj->jobCfg.channelPerJob; index++)
    {
        chId  = jobObj->jobCfg.channelList[jobObj->curChIdx];
        chObj = Spi_getCurrChannelObj(chId);

        /* Configure and start the channel */
        Spi_mcspiConfigCh(hwUnitObj, jobObj, chObj);
        if (0U == index)
        {
            /* First channel */
            Spi_mcspiStart(hwUnitObj, jobObj, (uint32) FALSE);
        }
        else
        {
            /* Non-first channel - just restart is sufficient */
            Spi_mcspiReStart(hwUnitObj, jobObj);
        }

        /* Busy loop till channel transfer is completed */
        do
        {
            jobResult = Spi_mcspiContinueTxRx(hwUnitObj, jobObj, chObj);
        }
        while (SPI_JOB_PENDING == jobResult);

        /* Move to next channel */
        jobObj->curChIdx++;
    }

    Spi_mcspiStop(hwUnitObj, jobObj);

    return (jobResult);
}

SPI_FUNC_TEXT_SECTION void Spi_mcspiStop(const Spi_HwUnitObjType *hwUnitObj,
                   const Spi_JobObjType    *jobObj)
{
    uint32 baseAddr, csNum;
    uint32 intrMask, csIntrMask;
    Spi_McspiExternalDeviceConfigType *extDevCfg;

    baseAddr  = hwUnitObj->baseAddr;
    extDevCfg = &jobObj->extDevCfg->mcspi;
    csNum     = (uint32)(jobObj->jobCfg_PC.csPin);

    /* Deassert CS */
    if (SPI_CONTINUOUS == extDevCfg->csMode)
    {
        CSL_REG32_FINS(
            baseAddr + MCSPI_CHCONF(csNum),
            MCSPI_CH0CONF_FORCE,
            MCSPI_CH0CONF_FORCE_DEASSERT);
    }

    /* Disable channel */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCTRL(csNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_NACT);

    /* Disable EOW, TX and RX interrupts */
    intrMask   = CSL_REG32_RD(baseAddr + MCSPI_IRQENABLE);
    intrMask  &= ~(MCSPI_IRQSTATUS_EOW_MASK);
    csIntrMask = Spi_mcspiGetCsIntrMask(csNum, extDevCfg->txRxMode);
    intrMask  &= ~(csIntrMask);
    CSL_REG32_WR(baseAddr + MCSPI_IRQENABLE, intrMask);

    /* Disable TX and RX FIFO - This is required so that next CS can
     * use the FIFO - done as per McSPI spec */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_FFEW,
        MCSPI_CH0CONF_FFEW_FFDISABLED);
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_FFER,
        MCSPI_CH0CONF_FFER_FFDISABLED);

    /* Clear all previous interrupt status */
    Spi_mcspiClearAllIrqStatus(baseAddr);

    return;
}

SPI_FUNC_TEXT_SECTION void Spi_mcspiClearAllIrqStatus(uint32 baseAddr)
{
    /* Clear all previous interrupt status */
    CSL_REG32_FINS(baseAddr + MCSPI_SYST, MCSPI_SYST_SSB, MCSPI_SYST_SSB_OFF);
    CSL_REG32_WR(baseAddr + MCSPI_IRQSTATUS, MCSPI_IRQSTATUS_CLEAR_ALL);

    return;
}

SPI_FUNC_TEXT_SECTION void Spi_mcspiDisableAllIntr(uint32 baseAddr)
{
    uint32 intrMask;

    /* Disable all interrupts */
    intrMask   = CSL_REG32_RD(baseAddr + MCSPI_IRQENABLE);
    intrMask  &= ~(MCSPI_IRQSTATUS_CLEAR_ALL);
    CSL_REG32_WR(baseAddr + MCSPI_IRQENABLE, intrMask);

    return;
}

#if (STD_ON == SPI_REGISTER_READBACK_API)
SPI_FUNC_TEXT_SECTION void Spi_mcspiRegReadback(
    const Spi_HwUnitObjType *hwUnitObj, Spi_RegisterReadbackType *RegRbPtr)
{
    uint32 baseAddr;

    baseAddr = hwUnitObj->baseAddr;
    RegRbPtr->mcspiHlRev      	  = CSL_REG32_RD(baseAddr + MCSPI_HL_REV);
    RegRbPtr->mcspiHlHwInfo    	  = CSL_REG32_RD(baseAddr + MCSPI_HL_HWINFO);
    RegRbPtr->mcspiHlSysConfig 	  = CSL_REG32_RD(baseAddr + MCSPI_HL_SYSCONFIG);
    RegRbPtr->mcspiRev         	  = CSL_REG32_RD(baseAddr + MCSPI_REVISION);
    RegRbPtr->mcspiSysStatus   	  = CSL_REG32_RD(baseAddr + MCSPI_SYSSTATUS);
    RegRbPtr->mcspiSyst           = CSL_REG32_RD(baseAddr + MCSPI_SYST);
    RegRbPtr->mcspiModulctrl   	  = CSL_REG32_RD(baseAddr + MCSPI_MODULCTRL);
    RegRbPtr->mcspiSysConfig      = CSL_REG32_RD(baseAddr + MCSPI_SYSCONFIG);
    RegRbPtr->mcspiCh0config      = CSL_REG32_RD(baseAddr + MCSPI_CH0CONF);
    RegRbPtr->mcspiCh1config      = CSL_REG32_RD(baseAddr + MCSPI_CH1CONF);
    RegRbPtr->mcspiCh2config      = CSL_REG32_RD(baseAddr + MCSPI_CH2CONF);
    RegRbPtr->mcspiCh3config      = CSL_REG32_RD(baseAddr + MCSPI_CH3CONF);
    RegRbPtr->mcspiIrqenable  	  = CSL_REG32_RD(baseAddr + MCSPI_IRQENABLE);
    return;
}
#endif  /* #if (STD_ON == SPI_REGISTER_READBACK_API) */

/*
 * Design: MCAL-6533,MCAL-6454,MCAL-6697,MCAL-6524,MCAL-6627
 */
SPI_FUNC_TEXT_SECTION static void Spi_mcspiReadFifo(Spi_ChannelObjType *chObj,
                              uint32              baseAddr,
                              uint32              csNum)
{
    uint32  rxData, chStat, isRxRegFull;
    uint8  *tempBuf8;
    uint16 *tempBuf16;
    uint32 *tempBuf32;
    uint32  rxFifoEmptyFlag = (uint32) FALSE;

    do
    {
        chStat      = CSL_REG32_RD(baseAddr + MCSPI_CHSTAT(csNum));
        isRxRegFull = (chStat & MCSPI_CH0STAT_RXS_MASK);
        if (isRxRegFull != MCSPI_CH0STAT_RXS_MASK)
        {
            /* RX register is empty */
            rxFifoEmptyFlag = ((uint32) TRUE);
        }
        else
        {
            /* Read the RX data */
            rxData      = CSL_REG32_RD(baseAddr + MCSPI_CHRX(csNum));
            rxData     &= chObj->dataWidthBitMask;

            /* Dynamic coverage for MC/DC cannot be achievable for True and false
             *condition, as curRxWords is always less than  numWordsTxRx if
             *curRxBufPtr is not a NULL_PTR*/
             /* Check if we are not overshooting the RX buffer */
            if ((chObj->curRxBufPtr != NULL_PTR) &&
                (chObj->curRxWords < chObj->numWordsTxRx))
            {
                if (1U == chObj->bufWidth)
                {
                    tempBuf8 = (uint8 *) chObj->curRxBufPtr;
                    *tempBuf8           = (uint8) rxData;
                    chObj->curRxBufPtr += 1U;
                }
                else if (2U == chObj->bufWidth)
                {
                    tempBuf16 = (uint16 *) chObj->curRxBufPtr;
                    *tempBuf16          = (uint16) rxData;
                    chObj->curRxBufPtr += 2U;
                }
                else
                {
                    tempBuf32 = (uint32 *) chObj->curRxBufPtr;
                    *tempBuf32          = (uint32) rxData;
                    chObj->curRxBufPtr += 4U;
                }
                chObj->curRxWords++;
            }
        }
    } while (((uint32) TRUE) != rxFifoEmptyFlag);

    return;
}

/*
 * Design: MCAL-6533,MCAL-6454,MCAL-6697,MCAL-6414,MCAL-6584
 */
SPI_FUNC_TEXT_SECTION static void Spi_mcspiWriteFifo(Spi_ChannelObjType *chObj,
                               uint32              baseAddr,
                               uint32              csNum)
{
    uint32        i, txData, numWordsToWrite;
    const uint8  *tempBuf8;
    uint8         tempBufdata8;
    const uint16 *tempBuf16;
    uint16        tempBufdata16;
    const uint32 *tempBuf32;
    uint32        tempBufdata32;

    /* TX is empty, write TX FIFO level */
    numWordsToWrite =
        (uint32) ((uint32) chObj->numWordsTxRx -
                  (uint32) chObj->curTxWords);
    if (numWordsToWrite > chObj->effTxFifoDepth)
    {
        numWordsToWrite = chObj->effTxFifoDepth; /* Limit to FIFO depth */
    }

    for (i = 0U; i < numWordsToWrite; i++)
    {
        if (chObj->curTxBufPtr != NULL_PTR)
        {
            if (1U == chObj->bufWidth)
            {
                tempBuf8 = (const uint8 *) chObj->curTxBufPtr;
                tempBufdata8        = *tempBuf8;
                txData              = (uint32)tempBufdata8;
                chObj->curTxBufPtr += 1U;
            }
            else if (2U == chObj->bufWidth)
            {
                tempBuf16 = (const uint16 *) chObj->curTxBufPtr;
                tempBufdata16       = *tempBuf16;
                txData              = (uint32)tempBufdata16;
                chObj->curTxBufPtr += 2U;
            }
            else
            {
                tempBuf32 = (const uint32 *) chObj->curTxBufPtr;
                tempBufdata32       = *tempBuf32;
                txData              = tempBufdata32;
                chObj->curTxBufPtr += 4U;
            }
        }
        else
        {
            txData = chObj->chCfg.defaultTxData;
        }

        CSL_REG32_WR(baseAddr + MCSPI_CHTX(csNum), txData);
    }
    chObj->curTxWords += (Spi_NumberOfDataType) numWordsToWrite;

    return;
}

SPI_FUNC_TEXT_SECTION static void Spi_mcspiInitiateChunkXfer(
    const Spi_ChannelObjType *chObj,
    const Spi_JobObjType     *jobObj,
    uint32                    baseAddr)
{
    uint32 reminder, regVal;
    uint32 csNum;

    csNum = (uint32)(jobObj->jobCfg_PC.csPin);

    /* Disable channel so that new settings takes effect */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCTRL(csNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_NACT);

    /* Set FIFO trigger level and word count to be equal to the
     * reminder word. Otherwise the HW doesn't generating TX
     * empty interrupt if WCNT is less than FIFO trigger level */
    reminder = (((uint32) chObj->numWordsTxRx) & (chObj->effTxFifoDepth - 1U));

    regVal   = CSL_REG32_RD(baseAddr + MCSPI_XFERLEVEL);
    regVal  &= ~(MCSPI_XFERLEVEL_AFL_MASK | MCSPI_XFERLEVEL_AEL_MASK);
    if (jobObj->rxFifoTrigLvl != 1U)
    {
        regVal |= (((reminder - 1U) << MCSPI_XFERLEVEL_AFL_SHIFT) &
                   MCSPI_XFERLEVEL_AFL_MASK);
    }
    regVal |= (((reminder - 1U) << MCSPI_XFERLEVEL_AEL_SHIFT) &
               MCSPI_XFERLEVEL_AEL_MASK);
    regVal &= ~MCSPI_XFERLEVEL_WCNT_MASK;
    regVal |= ((reminder << MCSPI_XFERLEVEL_WCNT_SHIFT) &
               MCSPI_XFERLEVEL_WCNT_MASK);
    CSL_REG32_WR(baseAddr + MCSPI_XFERLEVEL, regVal);

    /* Enable channel */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCTRL(csNum),
        MCSPI_CH0CTRL_EN,
        MCSPI_CH0CTRL_EN_ACT);

    return;
}

SPI_FUNC_TEXT_SECTION uint32 Spi_mcspiGetCsIntrMask(
    uint32 csNum, Spi_TxRxMode txRxMode)
{
    uint32 csIntrMask = 0U;

    if ((uint32)SPI_CS0 == csNum)
    {
        csIntrMask |= (uint32) MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_MASK;
        if (SPI_TX_RX_MODE_BOTH == txRxMode)
        {
            csIntrMask |= (uint32) MCSPI_IRQENABLE_RX0_FULL_ENABLE_MASK;
            csIntrMask |= (uint32) MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK;
        }
    }
    else if ((uint32)SPI_CS1 == csNum)
    {
        csIntrMask |= (uint32) MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_MASK;
        if (SPI_TX_RX_MODE_BOTH == txRxMode)
        {
            csIntrMask |= (uint32) MCSPI_IRQENABLE_RX1_FULL_ENABLE_MASK;
        }
    }
    else if ((uint32)SPI_CS2 == csNum)
    {
        csIntrMask |= (uint32) MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_MASK;
        if (SPI_TX_RX_MODE_BOTH == txRxMode)
        {
            csIntrMask |= (uint32) MCSPI_IRQENABLE_RX2_FULL_ENABLE_MASK;
        }
    }
    else
    {
        csIntrMask |= (uint32) MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_MASK;
        if (SPI_TX_RX_MODE_BOTH == txRxMode)
        {
            csIntrMask |= (uint32) MCSPI_IRQENABLE_RX3_FULL_ENABLE_MASK;
        }
    }

    return (csIntrMask);
}

SPI_FUNC_TEXT_SECTION static uint32 Spi_mcspiGetTxRxMasks(uint32 csNum)
{
    uint32 txEmptyMask;

    if ((uint32)SPI_CS0 == csNum)
    {
        txEmptyMask = (uint32) MCSPI_IRQSTATUS_TX0_EMPTY_MASK;
    }
    else if ((uint32)SPI_CS1 == csNum)
    {
        txEmptyMask = (uint32) MCSPI_IRQSTATUS_TX1_EMPTY_MASK;
    }
    else if ((uint32)SPI_CS2 == csNum)
    {
        txEmptyMask = (uint32) MCSPI_IRQSTATUS_TX2_EMPTY_MASK;
    }
    else
    {
        txEmptyMask = (uint32) MCSPI_IRQSTATUS_TX3_EMPTY_MASK;
    }

    return (txEmptyMask);
}

SPI_FUNC_TEXT_SECTION static void Spi_mcspiReset(uint32 baseAddr)
{
    StatusType status;
    TickType   startCount = 0U, tempCount, elaspsedCount = 0U;

    /* Set the SOFTRESET field of MCSPI_SYSCONFIG register. */
    CSL_REG32_FINS(
        baseAddr + MCSPI_SYSCONFIG,
        MCSPI_SYSCONFIG_SOFTRESET,
        MCSPI_SYSCONFIG_SOFTRESET_ON);

    status = GetCounterValue(SPI_OS_COUNTER_ID, &startCount);
    if (((StatusType) E_OK) == status)
    {
        /* Stay in the loop until reset is done. */
        while ((MCSPI_SYSSTATUS_RESETDONE_MASK &
                CSL_REG32_RD(baseAddr + MCSPI_SYSSTATUS)) !=
               MCSPI_SYSSTATUS_RESETDONE_MASK)
        {
            /* Dynamic Code coverage for this statement is not covered
             * because the hardware reset ends before timeout
             */
            /* Below API can change start time, so use temp variable */
            tempCount = startCount;
            status    = GetElapsedValue(
                SPI_OS_COUNTER_ID,
                &tempCount,
                &elaspsedCount);
            if ((((StatusType) E_OK) != status) ||
                (elaspsedCount >= SPI_TIMEOUT_DURATION))
            {
                /* timeout */
#if (SPI_E_HARDWARE_ERROR != SPI_DEM_NO_EVENT)
                (void)Dem_SetEventStatus(
                    SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
        }
    }

    return;
}

SPI_FUNC_TEXT_SECTION static void Spi_mcspiConfigDataPinDir(
    const Spi_HwUnitObjType *hwUnitObj, const Spi_JobObjType *jobObj)
{
    uint32 baseAddr, csNum;
    Spi_McspiExternalDeviceConfigType *extDevCfg;

    baseAddr  = hwUnitObj->baseAddr;
    csNum     = (uint32)(jobObj->jobCfg_PC.csPin);
    extDevCfg = &jobObj->extDevCfg->mcspi;

    /* Enable Rx Data Line IS */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_IS,
        extDevCfg->receptionLineEnable);

    /* Enable Tx Data Lines DPE0/DPE1 */
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_DPE0,
        ((uint32)extDevCfg->transmissionLineEnable & (uint32)0x1U));
    CSL_REG32_FINS(
        baseAddr + MCSPI_CHCONF(csNum),
        MCSPI_CH0CONF_DPE1,
        (((uint32)extDevCfg->transmissionLineEnable & (uint32)0x2U) >> 1U));

    return;
}

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
