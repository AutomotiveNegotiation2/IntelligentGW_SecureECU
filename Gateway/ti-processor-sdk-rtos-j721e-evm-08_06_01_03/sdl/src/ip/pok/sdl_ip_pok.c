/**
 * @file  sdl_pok_ip.c
 *
 * @brief
 *  C implementation file for the POK module SDL-FL.
 *
 *  Translates POK ID to POK Address. This is a SOC specific source file
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2021, Texas Instruments, Inc.
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
 *
*/
#include <tistdtypes.h>
#include <string.h>
#include <stdbool.h>
#include <sdl_ip_pok.h>
#include <src/sdl/sdl_pok.h>
/*=============================================================================
 *  Internal definitions and functions
 *===========================================================================*/

 /**
 * Design: PROC_SDL-1351
 */
/*function is used to set error signal wrt given POKID*/
void sdlGetErrSig(uint32_t id, SDL_POK_Inst *instance, uint32_t *esm_err_sig, bool *usePorCfgFlag)
{
    switch (id)
    {
        case SDL_POR_POKHV_UV_ID:
            *instance    = SDL_POR_POKHV_UV_ID;
            *usePorCfgFlag    = TRUE;
            *esm_err_sig    = ESM_ERR_SIG_POKHV_UV;
            break;
        case SDL_POR_POKHV_OV_ID:
            *instance    = SDL_POR_POKHV_OV_ID;
            *usePorCfgFlag    = TRUE;
            *esm_err_sig    = ESM_ERR_SIG_POKHV_OV;
            break;
        case SDL_POR_POKLV_UV_ID:
            *instance    = SDL_POR_POKLV_UV_ID;
            *usePorCfgFlag    = TRUE;
            *esm_err_sig    = ESM_ERR_SIG_POKLV_UV;
            break;
        case SDL_POK_VDDA_PMIC_IN_ID:
            *instance    = SDL_POK_VDDA_PMIC_IN_ID;
            *usePorCfgFlag    = FALSE;
            *esm_err_sig    = ESM_ERR_SIG_VDDA_IN;
            break;
        case SDL_POK_VDD_CORE_UV_ID:
            *instance    = SDL_POK_VDD_CORE_UV_ID;
            *usePorCfgFlag    = FALSE;
            *esm_err_sig    = ESM_ERR_SIG_VDD_CORE_UV;
            break;
        case SDL_POK_VDDSHV_WKUP_GEN_UV_ID:
            *instance = SDL_POK_VDDSHV_WKUP_GEN_UV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDDSHV_WKUP_GEN_UV;
            break;
        case SDL_POK_VDD_CPU_UV_ID:
            *instance = SDL_POK_VDD_CPU_UV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig     = ESM_ERR_SIG_VDD_CPU_UV;
            break;
        case SDL_POK_VDDR_MCU_UV_ID:
            *instance = SDL_POK_VDDR_MCU_UV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig     = ESM_ERR_SIG_VDDR_MCU_UV;
            break;
        case SDL_POK_VMON_EXT_UV_ID:
            *instance = SDL_POK_VMON_EXT_UV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig     = ESM_ERR_SIG_VMON_EXT_UV;
            break;
        case SDL_POK_VDD_MCU_OV_ID:
            *instance = SDL_POK_VDD_MCU_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig     = ESM_ERR_SIG_VDD_MCU_OV;
            break;
        case SDL_POK_VDDR_CORE_UV_ID:
            *instance = SDL_POK_VDDR_CORE_UV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDDR_CORE_UV;
            break;
        case SDL_POK_VDDSHV_WKUP_GEN_OV_ID:
            *instance = SDL_POK_VDDSHV_WKUP_GEN_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDDSHV_WKUP_GEN_OV;
            break;
        case SDL_POK_VDD_CORE_OV_ID:
            *instance = SDL_POK_VDD_CORE_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDD_CORE_OV;
            break;
        case SDL_POK_VDDR_MCU_OV_ID:
            *instance = SDL_POK_VDDR_MCU_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDDR_MCU_OV;
            break;
        case SDL_POK_VDD_CPU_OV_ID:
            *instance = SDL_POK_VDD_CPU_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDD_CPU_OV;
            break;
        case SDL_POK_VDDR_CORE_OV_ID:
            *instance = SDL_POK_VDDR_CORE_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VDDR_CORE_OV;
            break;
        case SDL_POK_VMON_EXT_OV_ID:
        default:
            *instance = SDL_POK_VMON_EXT_OV_ID;
            *usePorCfgFlag   = FALSE;
            *esm_err_sig   = ESM_ERR_SIG_VMON_EXT_OV;
            break;
    }
    return;
}


 /**
 * Design: PROC_SDL-1353,PROC_SDL-1354
 */

int32_t SDL_pok_GetShiftsAndMasks(SDL_wkupCtrlRegsBase_t     *pBaseAddress,
                                     SDL_POK_Inst  instance,
                                     SDL_pokShiftsAndMasks_t *pShMasks)
{
    SDL_wkup_ctrl_mmr_cfg0Regs      *pCtrlMMRCfgRegs = \
                                    (SDL_wkup_ctrl_mmr_cfg0Regs *)pBaseAddress;
    int32_t                         retVal = SDL_PASS;

    switch (instance)
    {
         /* PMIC POK ID */
         case    SDL_POK_VDDA_PMIC_IN_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDA_PMIC_IN_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDA_PMIC_IN_CTRL_OVER_VOLT_DET_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDA_PMIC_IN_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDA_PMIC_IN_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_SHIFT;
             break;

             /* CORE POK Under Voltage ID */
         case     SDL_POK_VDD_CORE_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDD_CORE_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_UV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CORE_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CORE_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* CPU under voltage POK ID */
         case     SDL_POK_VDD_CPU_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDD_CPU_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_UV_CTRL_POK_TRIM_SHIFT;
             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CPU_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CPU_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;
             break;

             /* Wakeup General POK Under Voltage ID */
         case     SDL_POK_VDDSHV_WKUP_GEN_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDSHV_WKUP_GEN_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_UV_CTRL_POK_TRIM_SHIFT;
             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDSHV_WKUP_GEN_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDSHV_WKUP_GEN_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* MCU under voltage VDD POK ID */
         case     SDL_POK_VDDR_MCU_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDR_MCU_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_UV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDR_MCU_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDR_MCU_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* VMON under voltage POK ID */
         case     SDL_POK_VMON_EXT_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VMON_EXT_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_UV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VMON_EXT_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VMON_EXT_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* MCU overvoltage POK ID */
         case     SDL_POK_VDD_MCU_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDD_MCU_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_MCU_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_MCU_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_MCU_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_MCU_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_MCU_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_MCU_OV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDD_MCU_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDD_MCU_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* VDD CORE POK ID */
         case     SDL_POK_VDDR_CORE_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDR_CORE_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_UV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDDR_CORE_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDDR_CORE_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* Wakeup General POK Over voltage ID */
         case     SDL_POK_VDDSHV_WKUP_GEN_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDSHV_WKUP_GEN_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDSHV_WKUP_GEN_OV_CTRL_POK_TRIM_SHIFT;
             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDSHV_WKUP_GEN_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDSHV_WKUP_GEN_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* CORE VDD Over Voltage POK ID */
         case     SDL_POK_VDD_CORE_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDD_CORE_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CORE_OV_CTRL_POK_TRIM_SHIFT;
             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CORE_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CORE_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;
             break;

             /* MCU  over Voltage POK ID */
         case     SDL_POK_VDDR_MCU_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDR_MCU_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_MCU_OV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDR_MCU_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_VDDR_MCU_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG0_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG0_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* CPU  over Voltage POK ID */
         case     SDL_POK_VDD_CPU_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDD_CPU_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDD_CPU_OV_CTRL_POK_TRIM_SHIFT;
             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CPU_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDD_CPU_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* CORE VDDR over Voltage POK ID */
         case     SDL_POK_VDDR_CORE_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VDDR_CORE_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VDDR_CORE_OV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDDR_CORE_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VDDR_CORE_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* VMON POK Over Voltage ID */
         case     SDL_POK_VMON_EXT_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POK_VMON_EXT_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POK_VMON_EXT_OV_CTRL_POK_TRIM_SHIFT;
             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VMON_EXT_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_VMON_EXT_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->MAIN_PRG_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_MAIN_PRG_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* POKHV Under Voltage POK ID */
         case     SDL_POR_POKHV_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POR_POKHV_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_UV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG1_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POKHV_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POKHV_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG1_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* POKLV Under Voltage POK ID */
         case     SDL_POR_POKLV_UV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POR_POKLV_UV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POR_POKLV_UV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKLV_UV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKLV_UV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POR_POKLV_UV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POR_POKLV_UV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKLV_UV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG1_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POKLV_UV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POKLV_UV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG1_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POK_EN_SEL_SHIFT;

             break;

             /* POKHV Over Voltage POK ID */
         case     SDL_POR_POKHV_OV_ID:
             pShMasks->pokAddr     = &pCtrlMMRCfgRegs->POR_POKHV_OV_CTRL;
             pShMasks->hystMask    = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_OV_CTRL_HYST_EN_MASK;
             pShMasks->hystShift   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_OV_CTRL_HYST_EN_SHIFT;
             pShMasks->vdDetMask   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_OV_CTRL_OVER_VOLT_DET_MASK;
             pShMasks->vdDetShift  = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_OV_CTRL_OVER_VOLT_DET_SHIFT;
             pShMasks->trimMask    = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_OV_CTRL_POK_TRIM_MASK;
             pShMasks->trimShift   = SDL_WKUP_CTRL_MMR_CFG0_POR_POKHV_OV_CTRL_POK_TRIM_SHIFT;

             /* POK Detection enable/disable control */
             pShMasks->pokDetAddr  = &pCtrlMMRCfgRegs->WKUP_PRG1_CTRL;
             pShMasks->detEnMask   = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POKHV_OV_EN_MASK;
             pShMasks->detEnShift  = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POKHV_OV_EN_SHIFT;

             /* POK Enable Selection SRC */
             pShMasks->pokEnSelAddr = &pCtrlMMRCfgRegs->WKUP_PRG1_CTRL;
             pShMasks->pokEnSelMask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POK_EN_SEL_MASK;
             pShMasks->pokEnSelShift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_PRG1_CTRL_POK_EN_SEL_SHIFT;

             break;

         default:
             pShMasks->pokAddr      = ( void * ) 0;
             pShMasks->pokDetAddr   = ( void * ) 0;
             pShMasks->pokEnSelAddr = ( void * ) 0;
             retVal  = SDL_EBADARGS;
             break;
     }

     return(retVal);

}

/*=============================================================================
 *  internal macros
 *===========================================================================*/
/* None */

/*=============================================================================
 *  static global variables
 *===========================================================================*/
/* None */

/*=============================================================================
 *  Non Interface function - internal use only
 *===========================================================================*/


static int32_t  SDL_pokSetOperation(SDL_wkupCtrlRegsBase_t           *pBaseAddress,
                             const SDL_POK_config               *pPokCfg,
                             SDL_POK_Inst                        instance)
{
    int32_t                          retVal = SDL_EBADARGS;
    SDL_pokShiftsAndMasks_t          shiftsNMasks;


    retVal =  SDL_pok_GetShiftsAndMasks(pBaseAddress, instance, &shiftsNMasks);

    if (retVal == SDL_PASS)
    {
        if (pPokCfg->hystCtrl != SDL_PWRSS_HYSTERESIS_NO_ACTION)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokAddr, shiftsNMasks.hystMask, shiftsNMasks.hystShift, pPokCfg->hystCtrl);
        }

        if (pPokCfg->voltDetMode != SDL_PWRSS_VOLTAGE_DET_NO_ACTION)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokAddr, shiftsNMasks.vdDetMask, shiftsNMasks.vdDetShift, pPokCfg->voltDetMode);
        }

        if (pPokCfg->trim <= SDL_PWRSS_MAX_TRIM_VALUE)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokAddr, shiftsNMasks.trimMask, shiftsNMasks.trimShift, pPokCfg->trim);
        }

        if (pPokCfg->detectionCtrl == SDL_POK_DETECTION_ENABLE)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokDetAddr, shiftsNMasks.detEnMask, shiftsNMasks.detEnShift, SDL_POK_DETECTION_ENABLE);
        }

        if (pPokCfg->detectionCtrl == SDL_POK_DETECTION_DISABLE)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokDetAddr, shiftsNMasks.detEnMask, shiftsNMasks.detEnShift, SDL_POK_DETECTION_DISABLE);
        }

        if (pPokCfg->pokEnSelSrcCtrl == SDL_POK_ENSEL_HWTIEOFFS)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokEnSelAddr, shiftsNMasks.pokEnSelMask, shiftsNMasks.pokEnSelShift, SDL_POK_ENSEL_HWTIEOFFS);
        }

        if (pPokCfg->pokEnSelSrcCtrl == SDL_POK_ENSEL_PRG_CTRL)
        {
            SDL_REG32_FINS_RAW(shiftsNMasks.pokEnSelAddr, shiftsNMasks.pokEnSelMask, shiftsNMasks.pokEnSelShift, SDL_POK_ENSEL_PRG_CTRL);
        }
    }

    return (retVal);

}

static int32_t SDL_por_set_override(volatile uint32_t     *pBaseAddr,
                                    const  SDL_por_override     *pOverRdAddr,
                                    uint32_t     set_shift,
                                    uint32_t     set_mask,
                                    uint32_t     en_shift,
                                    uint32_t     en_mask)
{
    int32_t     retVal = SDL_PASS;

    if (*pOverRdAddr == SDL_POR_OVERRIDE_SET_ENABLE)
    {
        SDL_REG32_FINS_RAW(pBaseAddr, en_mask, en_shift,0U);
        SDL_REG32_FINS_RAW(pBaseAddr, set_mask, set_shift,0U);
    }
    else if (*pOverRdAddr == SDL_POR_OVERRIDE_NOT_SET_DISABLE)
    {
        SDL_REG32_FINS_RAW(pBaseAddr, en_mask, en_shift,1U);
        SDL_REG32_FINS_RAW(pBaseAddr, set_mask, set_shift,1U);
    }
    else if (*pOverRdAddr == SDL_POR_SET_OVERRIDE_NO_CHANGE)
    {
        /* No change */
    }
    else
    {
        retVal = SDL_EBADARGS;
    }

    return (retVal);

}

 /**
 * Design: PROC_SDL-1357,PROC_SDL-1358
 */

int32_t SDL_porSetControl (SDL_wkupCtrlRegsBase_t           *pBaseAddress,
                           const SDL_pokPorCfg_t            *pPorCfg)
{
    int32_t     retVal = SDL_PASS;

    SDL_wkup_ctrl_mmr_cfg0Regs      *pCtrlMMRCfgRegs = \
                                    (SDL_wkup_ctrl_mmr_cfg0Regs *)pBaseAddress;

    if ( (pBaseAddress == NULL_PTR) ||
         (pPorCfg      == NULL_PTR) ||
         (pPorCfg->trim_select > SDL_POR_TRIM_SELECTION_GET_VALUE) )
    {
        retVal = SDL_EBADARGS;
    }


    if (retVal == SDL_PASS)
    {
        retVal = SDL_por_set_override(&pCtrlMMRCfgRegs->POR_CTRL,
                                      &pPorCfg->override[SDL_PORHV_OVERRIDE_INDEX],
                                      SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET0_SHIFT,
                                      SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET0_MASK,
                                      SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD0_SHIFT,
                                      SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD0_MASK);

        if (retVal == SDL_PASS)
        {

            retVal = SDL_por_set_override(&pCtrlMMRCfgRegs->POR_CTRL,
                              &pPorCfg->override[SDL_BGAP_OVERRIDE_INDEX],
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET1_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET1_MASK,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD1_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD1_MASK);
        }

        if (retVal == SDL_PASS)
        {

            retVal = SDL_por_set_override(&pCtrlMMRCfgRegs->POR_CTRL,
                              &pPorCfg->override[SDL_POKHV_OVERRIDE_INDEX],
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET2_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET2_MASK,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD2_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD2_MASK);
        }

        if (retVal == SDL_PASS)
        {

            retVal = SDL_por_set_override(&pCtrlMMRCfgRegs->POR_CTRL,
                              &pPorCfg->override[SDL_POKLVA_OVERRIDE_INDEX],
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET3_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET3_MASK,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD3_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD3_MASK);
        }

        if (retVal == SDL_PASS)
        {

            retVal = SDL_por_set_override(&pCtrlMMRCfgRegs->POR_CTRL,
                              &pPorCfg->override[SDL_POKLVB_OVERRIDE_INDEX],
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET4_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD_SET4_MASK,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD4_SHIFT,
                              SDL_WKUP_CTRL_MMR_CFG0_POR_CTRL_OVRD4_MASK);
        }

        if (retVal == SDL_PASS)
        {
            /* Mask HHV output when applying new TRIM values */
            if (pPorCfg->maskHHVOutputEnable == FALSE)
            {
                SDL_REG32_FINS(&pCtrlMMRCfgRegs->POR_CTRL, WKUP_CTRL_MMR_CFG0_POR_CTRL_MASK_HHV, 0U);
            }
            else
            {
                SDL_REG32_FINS(&pCtrlMMRCfgRegs->POR_CTRL, WKUP_CTRL_MMR_CFG0_POR_CTRL_MASK_HHV, 1U);
            }

            if (pPorCfg->trim_select == SDL_POR_TRIM_SELECTION_FROM_HHV_DEFAULT)
            {
                SDL_REG32_FINS(&pCtrlMMRCfgRegs->POR_CTRL, WKUP_CTRL_MMR_CFG0_POR_CTRL_TRIM_SEL, 0U);
            }
            else if (pPorCfg->trim_select == SDL_POR_TRIM_SELECTION_FROM_CTRL_REGS)
            {
                SDL_REG32_FINS(&pCtrlMMRCfgRegs->POR_CTRL, WKUP_CTRL_MMR_CFG0_POR_CTRL_TRIM_SEL, 1U);
            }
            else
            {
                /* No Action */
            }
        }
    }

    return (retVal);
}


static int32_t  SDL_pokGetOperation(SDL_wkupCtrlRegsBase_t           *pBaseAddress,
                             const SDL_POK_config               *pPokCfg,
                             SDL_pokVal_t                     *pPokVal,
                             SDL_POK_Inst                        instance)

{
    SDL_wkup_ctrl_mmr_cfg0Regs      *pCtrlMMRCfgRegs = \
                                (SDL_wkup_ctrl_mmr_cfg0Regs *)pBaseAddress;
    int32_t                          retVal;
    SDL_pokShiftsAndMasks_t          shiftsNMasks;

        retVal = SDL_pok_GetShiftsAndMasks(pBaseAddress, instance, &shiftsNMasks);
        switch (instance)
        {
            /* PMIC POK ID */
            case    SDL_POK_VDDA_PMIC_IN_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG0_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG0_STAT_POK_VDDA_PMIC_IN);
                break;

                /* CORE POK Under Voltage ID */
            case     SDL_POK_VDD_CORE_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VDD_CORE_UV);

                break;

                /* CPU under voltage POK ID */
            case     SDL_POK_VDD_CPU_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VDD_CPU_UV);

                break;

                /* Wakeup General POK Under Voltage ID */
            case     SDL_POK_VDDSHV_WKUP_GEN_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG0_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG0_STAT_POK_VDDSHV_WKUP_GEN_UV);

                break;

                /* MCU under voltage VDD POK ID */
            case     SDL_POK_VDDR_MCU_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG0_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG0_STAT_POK_VDDR_MCU_UV);
                break;

                /* VMON under voltage POK ID */
            case     SDL_POK_VMON_EXT_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VMON_EXT_UV);

                break;

                /* MCU overvoltage POK ID */
            case     SDL_POK_VDD_MCU_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG0_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG0_STAT_POK_VDD_MCU_OV);

                break;

                /* VDD CORE POK ID */
            case     SDL_POK_VDDR_CORE_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VDDR_CORE_UV);

                break;

                /* Wakeup General POK Over voltage ID */
            case     SDL_POK_VDDSHV_WKUP_GEN_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG0_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG0_STAT_POK_VDDSHV_WKUP_GEN_OV);

                break;

                /* CORE VDD Over Voltage POK ID */
            case     SDL_POK_VDD_CORE_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VDD_CORE_OV);

                break;

                /* MCU  over Voltage POK ID */
            case     SDL_POK_VDDR_MCU_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG0_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG0_STAT_POK_VDDR_MCU_OV);

                break;

                /* CPU  over Voltage POK ID */
            case     SDL_POK_VDD_CPU_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VDD_CPU_OV);

                break;

                /* CORE VDDR over Voltage POK ID */
            case     SDL_POK_VDDR_CORE_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VDDR_CORE_OV);

                break;

                /* VMON POK Over Voltage ID */
            case     SDL_POK_VMON_EXT_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->MAIN_PRG_STAT,
                                                           WKUP_CTRL_MMR_CFG0_MAIN_PRG_STAT_POK_VMON_EXT_UV);

                break;

                /* POKHV Under Voltage POK ID */
            case     SDL_POR_POKHV_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG1_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG1_STAT_POKHV_UV);

                break;

                /* POKLV Under Voltage POK ID */
            case     SDL_POR_POKLV_UV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG1_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG1_STAT_POKLV_UV);

                break;

                /* POKHV Over Voltage POK ID */
            case     SDL_POR_POKHV_OV_ID:
                /* Get the Voltage Threshold Status for this POK ID */
                pPokVal->voltageThrStatus = (SDL_POK_thrStatus)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->WKUP_PRG1_STAT,
                                                           WKUP_CTRL_MMR_CFG0_WKUP_PRG1_STAT_POKHV_OV);

                break;

            default:
                retVal  = SDL_EBADARGS;
                break;
        }


    if (retVal == SDL_PASS)
    {
        if (pPokCfg->hystCtrl == SDL_PWRSS_GET_HYSTERESIS_VALUE)
        {
            pPokVal->hystCtrl = (SDL_pwrss_hysteresis)SDL_REG32_FEXT_RAW(shiftsNMasks.pokAddr, shiftsNMasks.hystMask, shiftsNMasks.hystShift);
        }

        if (pPokCfg->voltDetMode == SDL_PWRSS_GET_VOLTAGE_DET_MODE)
        {
            pPokVal->voltDetMode = (SDL_pwrss_vd_mode)SDL_REG32_FEXT_RAW(shiftsNMasks.pokAddr, shiftsNMasks.vdDetMask, shiftsNMasks.vdDetShift);
        }

        if ((pPokCfg->trim == SDL_PWRSS_GET_TRIM_VALUE) &&
            (instance != SDL_POK_VDDA_PMIC_IN_ID))
        {
            pPokVal->trim = (SDL_pwrss_trim)SDL_REG32_FEXT_RAW(shiftsNMasks.pokAddr, shiftsNMasks.trimMask, shiftsNMasks.trimShift);
        }

        if (pPokCfg->detectionCtrl == SDL_POK_GET_DETECTION_VALUE)
        {
            pPokVal->detectionStatus = (SDL_POK_detection_status)SDL_REG32_FEXT_RAW(shiftsNMasks.pokDetAddr, shiftsNMasks.detEnMask, shiftsNMasks.detEnShift);
        }

        if (pPokCfg->pokEnSelSrcCtrl == SDL_POK_GET_ENSEL_VALUE)
        {
            pPokVal->pokEnSelSrcCtrl = (SDL_POK_enSelSrc)SDL_REG32_FEXT_RAW(shiftsNMasks.pokEnSelAddr, shiftsNMasks.pokEnSelMask, shiftsNMasks.pokEnSelShift);
        }

    }

    return (retVal);

}

/**
 * Design: PROC_SDL-1355,PROC_SDL-1356
 */

int32_t SDL_pokGetControl (SDL_wkupCtrlRegsBase_t           *pBaseAddress,
                             const SDL_POK_config               *pPokCfg,
                             SDL_pokVal_t                     *pPokVal,
                             SDL_POK_Inst                      instance)
{
    int32_t     retVal = SDL_PASS;


    if ( (pBaseAddress          == NULL_PTR) ||
         (pPokCfg               == NULL_PTR)  ||
         (pPokVal               == NULL_PTR) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        if ((pPokCfg->hystCtrl     == SDL_PWRSS_GET_HYSTERESIS_VALUE) ||
            (pPokCfg->voltDetMode  == SDL_PWRSS_GET_VOLTAGE_DET_MODE) ||
            (pPokCfg->trim         == SDL_PWRSS_GET_TRIM_VALUE)       ||
            (pPokCfg->detectionCtrl == SDL_POK_GET_DETECTION_VALUE)   ||
            (pPokCfg->pokEnSelSrcCtrl  == SDL_POK_GET_ENSEL_VALUE))
        {
            retVal = SDL_pokGetOperation(pBaseAddress,
                                         pPokCfg,
                                         pPokVal,
                                         instance);
        }
        else if ((pPokCfg->hystCtrl        == SDL_PWRSS_HYSTERESIS_NO_ACTION) ||
                 (pPokCfg->voltDetMode     == SDL_PWRSS_VOLTAGE_DET_NO_ACTION) ||
                 (pPokCfg->trim            == SDL_PWRSS_TRIM_NO_ACTION) ||
                 (pPokCfg->detectionCtrl   == SDL_POK_DETECTION_NO_ACTION) ||
                 (pPokCfg->pokEnSelSrcCtrl == SDL_POK_ENSEL_NO_ACTION))
        {
            /* No Action */
        }
        else
        {
            retVal = SDL_EBADARGS;
        }
    }

    return (retVal);
}

/**
 * Design: PROC_SDL-1357,PROC_SDL-1358
 */

int32_t SDL_pokSetControl (SDL_wkupCtrlRegsBase_t           *pBaseAddress,
                             const SDL_POK_config              *pPokCfg,
                             SDL_POK_Inst                      instance)
{
    int32_t     retVal;

    if ((pBaseAddress          == NULL_PTR) ||
        (pPokCfg               == NULL_PTR) )
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        if ((pPokCfg->hystCtrl     == SDL_PWRSS_GET_HYSTERESIS_VALUE) ||
            (pPokCfg->voltDetMode  == SDL_PWRSS_GET_VOLTAGE_DET_MODE) ||
            (pPokCfg->trim         == SDL_PWRSS_GET_TRIM_VALUE) ||
            (pPokCfg->detectionCtrl == SDL_POK_GET_DETECTION_VALUE) ||
            (pPokCfg->pokEnSelSrcCtrl == SDL_POK_GET_ENSEL_VALUE))
        {
            retVal = SDL_EFAIL;
        }
        else if ((pPokCfg->hystCtrl        <= SDL_PWRSS_HYSTERESIS_NO_ACTION) ||
                 (pPokCfg->voltDetMode     <= SDL_PWRSS_VOLTAGE_DET_NO_ACTION) ||
                 (pPokCfg->trim            <= SDL_PWRSS_MAX_TRIM_VALUE) ||
                 (pPokCfg->detectionCtrl   <  SDL_POK_GET_DETECTION_VALUE) ||
                 (pPokCfg->pokEnSelSrcCtrl <  SDL_POK_GET_ENSEL_VALUE))
        {
            retVal = SDL_pokSetOperation(pBaseAddress,
                                         pPokCfg,
                                         instance);
        }
        else
        {
            retVal = SDL_EBADARGS;
        }
    }
    return (retVal);}
