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
 *  \file     Eth_Irq.c
 *
 *  \brief    This file contains the ISR implementation of the Ethernet
 *            driver.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Eth.h"
#include "Eth_Irq.h"
#if (STD_ON == ETH_ENABLE_MII_API)
#include "EthTrcv.h"
#endif
#if (STD_ON == ETH_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "Dem.h"
#include "Eth_Priv.h"
#include "cpsw/Cpsw_Dma.h"
#include "Eth_IrqPacing.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ETH_CONTROL_INDEX_0      (0u)

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define  ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

extern volatile Eth_MiiAccessType Eth_MiiAccess[ETH_CTRL_ID_MAX];

#define  ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

/* ========================================================================== */
/*                  Internal Function Definitions                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define ETH_START_SEC_ISR_CODE
#include "Eth_MemMap.h"

/* Design : ETH_DesignId_017 */
/*
 * Requirements : MCAL-1604, MCAL-1605, MCAL-1606, MCAL-1607,
 *                MCAL-1608
 */
#if (ETH_ISR_TYPE == ETH_ISR_CAT1 || ETH_ISR_TYPE == ETH_ISR_VOID)
ETH_ISR_TEXT_SECTION FUNC(void, ETH_CODE_FAST) Eth_RxIrqHdlr_0(void)
#else
ETH_ISR_TEXT_SECTION ISR(Eth_RxIrqHdlr_0)
#endif
{
    uint8 ctrlIdx = ETH_CONTROL_INDEX_0;
    uint8 fifoIdx;

    for(fifoIdx = 0u; fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        if(CpswDma_Ring_IrqIsSet(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx)))
        {
            (void)Eth_receiveProcess(ctrlIdx, fifoIdx);
        }
    }

    if(TRUE == Eth_GetRxIrqPacingEnable(ctrlIdx))
    {
        for(fifoIdx = 0u; fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx); ++fifoIdx)
        {
            CpswDma_Ring_IrqDisable(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx));
        }
        Eth_IrqPacingStartTimer(ctrlIdx, Eth_GetRxHwTimerIdx(ctrlIdx));
    }
}

/* Design : ETH_DesignId_018 */
/*
 * Requirements : MCAL-1609, MCAL-1610, MCAL-1611, MCAL-1612,
 *                MCAL-1613
 */
#if (ETH_ISR_TYPE == ETH_ISR_CAT1 || ETH_ISR_TYPE == ETH_ISR_VOID)
ETH_ISR_TEXT_SECTION FUNC(void, ETH_CODE_FAST) Eth_TxIrqHdlr_0(void)
#else
ETH_ISR_TEXT_SECTION ISR(Eth_TxIrqHdlr_0)
#endif
{
    uint8 ctrlIdx = ETH_CONTROL_INDEX_0;
    uint8 fifoIdx;

    for(fifoIdx = 0u; fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        if(CpswDma_Ring_IrqIsSet(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx)))
        {
            (void)Eth_txProcess(ctrlIdx, fifoIdx);
        }
    }

    if(TRUE == Eth_GetTxIrqPacingEnable(ctrlIdx))
    {
        for(fifoIdx = 0u; fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx); ++fifoIdx)
        {
            CpswDma_Ring_IrqDisable(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx));
        }
        Eth_IrqPacingStartTimer(ctrlIdx, Eth_GetTxHwTimerIdx(ctrlIdx));
    }
}

#if (ETH_ISR_TYPE == ETH_ISR_CAT1 || ETH_ISR_TYPE == ETH_ISR_VOID)
ETH_ISR_TEXT_SECTION FUNC(void, ETH_CODE_FAST) Eth_RxIrqPacingHdlr_0(void)
#else
ETH_ISR_TEXT_SECTION ISR(Eth_RxIrqPacingHdlr_0)
#endif
{
    uint8 ctrlIdx = ETH_CONTROL_INDEX_0;
    boolean isRestart = FALSE;
    uint8 fifoIdx;

    for(fifoIdx = 0u; fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        if(ETH_RECEIVED_MORE_DATA_AVAILABLE == Eth_receiveProcess(ctrlIdx, fifoIdx))
        {
            isRestart = TRUE;
        }
    }

    if(FALSE == isRestart)
    {
        for(fifoIdx = 0u; fifoIdx < Eth_GetIngressFifoTotalNum(ctrlIdx); ++fifoIdx)
        {
            CpswDma_Ring_IrqEnable(ctrlIdx, Eth_GetIngressFifoCqIdx(ctrlIdx, fifoIdx));
        }
    }

    Eth_IrqPacingRestartHwTimer(ctrlIdx,
        Eth_GetRxHwTimerIdx(ctrlIdx),
        isRestart);
}

#if (ETH_ISR_TYPE == ETH_ISR_CAT1 || ETH_ISR_TYPE == ETH_ISR_VOID)
ETH_ISR_TEXT_SECTION FUNC(void, ETH_CODE_FAST) Eth_TxIrqPacingHdlr_0(void)
#else
ETH_ISR_TEXT_SECTION ISR(Eth_TxIrqPacingHdlr_0)
#endif
{
    uint8 ctrlIdx = ETH_CONTROL_INDEX_0;
    boolean isRestart = FALSE;
    uint8 fifoIdx;

    for(fifoIdx = 0u; fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx); ++fifoIdx)
    {
        if(ETH_TRANSMITED_BUFFER_PENDING == Eth_txProcess(ctrlIdx, fifoIdx))
        {
            isRestart = TRUE;
        }
    }

    if(FALSE == isRestart)
    {
        for(fifoIdx = 0u; fifoIdx < Eth_GetEgressFifoTotalNum(ctrlIdx); ++fifoIdx)
        {
            CpswDma_Ring_IrqEnable(ctrlIdx, Eth_GetEgressFifoCqIdx(ctrlIdx, fifoIdx));
        }
    }

    Eth_IrqPacingRestartHwTimer(ctrlIdx,
        Eth_GetTxHwTimerIdx(ctrlIdx),
        isRestart);
}

#if (STD_ON == ETH_ENABLE_MII_API)

#if (ETH_ISR_TYPE == ETH_ISR_CAT1 || ETH_ISR_TYPE == ETH_ISR_VOID)
ETH_ISR_TEXT_SECTION FUNC(void, ETH_CODE_FAST) Eth_MdioIrqHdlr_0(void)
#else
ETH_ISR_TEXT_SECTION ISR(Eth_MdioIrqHdlr_0)
#endif
{
    uint16 val;
    Std_ReturnType retVal;

    if (TRUE == Eth_MiiAccess[ETH_CONTROL_INDEX_0].isActive)
    {
        if (TRUE == Eth_MiiAccess[ETH_CONTROL_INDEX_0].isRead)
        {
            retVal = Eth_getMiiReadVal(ETH_CONTROL_INDEX_0, &val);
            if (E_OK == retVal)
            {
                EthTrcv_ReadMiiIndication(Eth_MiiAccess[ETH_CONTROL_INDEX_0].ctrlIdx,
                                          Eth_MiiAccess[ETH_CONTROL_INDEX_0].trcvIdx,
                                          Eth_MiiAccess[ETH_CONTROL_INDEX_0].regIdx,
                                          val);
            }
        }
        else
        {
            EthTrcv_WriteMiiIndication(Eth_MiiAccess[ETH_CONTROL_INDEX_0].ctrlIdx,
                                       Eth_MiiAccess[ETH_CONTROL_INDEX_0].trcvIdx,
                                       Eth_MiiAccess[ETH_CONTROL_INDEX_0].regIdx);

        }

        Eth_MiiAccess[ETH_CONTROL_INDEX_0].isActive = FALSE;
    }
    /* Always clear MDIO Irq */
    Eth_clearMdioInt(ETH_CONTROL_INDEX_0);
}

#endif /* (STD_ON == ETH_ENABLE_MII_API) */

#define ETH_STOP_SEC_ISR_CODE
#include "Eth_MemMap.h"
