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
 *  \file     Mcu_Priv.c
 *
 *  \brief    This file contains MCU MCAL driver implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Mcu_Priv.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/* Memory mapping, done via MemMap.h: Code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/*******************************************************************************
 * Mcu_InterpretRawResetStatus
 ******************************************************************************/
/*! \brief      This function will get the raw reset status.
 *
 ******************************************************************************/
 /*
 *Design: MCAL-8493
 */
FUNC(Mcu_ResetType, MCU_CODE)Mcu_InterpretRawResetStatus(
    Mcu_RawResetType reset_raw)
{
    Mcu_ResetType reset_reason = MCU_RESET_UNDEFINED;
    Mcu_RawResetType rstRaw = reset_raw;

    /* Get the raw reset reason  */
    reset_reason = Mcu_GetRawResetReason(rstRaw);

    return (reset_reason);
}

/*******************************************************************************
 * Mcu_ClearResetReason
 ******************************************************************************/
/*! \brief      This function will clear the reset reason.
 *
 ******************************************************************************/
 /*
 *Design: MCAL-8425
 */
FUNC(void, MCU_CODE) Mcu_ClearResetReason(void)
{
    uint32 regRDVal = 0;
    LLD_REG32_WR(&rstaddr->RESET_SRC_STAT, MCU_RST_SRC_STAT_CLEAR);

} /* end of Mcu_ClearResetReason() */



/*******************************************************************************
 * Mcu_PerformSoftSysReset
 ******************************************************************************/
/*! \brief      This function will perform system reset.
 *
 ******************************************************************************/
 /*
 *Design: MCAL-8452,MCAL-8444
 */
void Mcu_PerformSoftSysReset(uint32 resetVal)
{
     uint32 regRDVal = 0;

     LLD_REG32_WR(&rstaddr->MAIN_WARM_RST_CTRL, MCU_PERFORM_RESET_MASK);

}

/*******************************************************************************
 * Mcu_GetRawResetReason
 ******************************************************************************/
/*! \brief      This function will get the raw reset value from hardware register.
 *
 ******************************************************************************/
 /*
 *Design: MCAL-8493
 */
Mcu_ResetType Mcu_GetRawResetReason(Mcu_RawResetType reset_raw)
{
  uint8         idx;
  Mcu_ResetType reset_reason = MCU_RESET_UNDEFINED;

  for (idx = 0U; idx < Mcu_ResetInfoTbl.numFields; idx++)
  {
      if (reset_raw == Mcu_ResetInfoTbl.resetMap[idx].rawresetval )
      {
        reset_reason = Mcu_ResetInfoTbl.resetMap[idx].resetReason;
        break;
      }
  }
  return (reset_reason);
}

/*******************************************************************************
 * Mcu_GetSystemRstCause
 ******************************************************************************/
/*! \brief      This function will get the reset cause from hardware register.
 *
 ******************************************************************************/
 /*
 *Design: MCAL-8493
 */
uint32 Mcu_GetSystemRstCause(void)
{
    uint32 RegRDVal = 0U;
    uint32 RegRDBits = 0U;
    uint32 RstRawVal;

    RegRDBits = LLD_REG32_RD(&rstaddr->RESET_SRC_STAT);

    return (RegRDBits);
}


#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
/*******************************************************************************
 *  End of File: Mcu_priv.c
 ******************************************************************************/
