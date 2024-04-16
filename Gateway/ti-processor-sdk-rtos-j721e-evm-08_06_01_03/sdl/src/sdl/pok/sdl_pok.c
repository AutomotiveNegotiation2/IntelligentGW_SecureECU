/**
 * @file  sdl_pok.c
 *
 * @brief
 *  C implementation file for the POK module SDL-FL.
 *
 *  Contains the different control command and status query functions definitions
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
#include <sdl_pok.h>
#include <osal/sdl_osal.h>
/* delay for 1us*/
#define DELAY 1

/**
 * Design: PROC_SDL-1349,PROC_SDL-1162
 */
/*function reads the values of static registers such as hysteresis control,voltage detect mode, trim ,
PORGAP and module status */
int32_t SDL_POK_getStaticRegisters(SDL_POK_Inst instance,SDL_POK_staticRegs *pStaticRegs)
{
    int32_t    retVal = SDL_EBADARGS;
    SDL_pokShiftsAndMasks_t    shiftsNMasks;
    SDL_wkupCtrlRegsBase_t    *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;

    if((pStaticRegs != NULL) && (instance <= SDL_POR_POKHV_OV_ID) \
            && (instance >= SDL_POK_VDDA_PMIC_IN_ID))
    {
        const    SDL_wkup_ctrl_mmr_cfg0Regs    *pCtrlMMRCfgRegs = (const SDL_wkup_ctrl_mmr_cfg0Regs *)pBaseAddr;
        retVal = SDL_pok_GetShiftsAndMasks(pBaseAddr, instance, &shiftsNMasks);

        pStaticRegs->hystCtrl = (SDL_pwrss_hysteresis)SDL_REG32_FEXT_RAW(shiftsNMasks.pokAddr, shiftsNMasks.hystMask, shiftsNMasks.hystShift);

        pStaticRegs->voltDetMode = (SDL_pwrss_vd_mode)SDL_REG32_FEXT_RAW(shiftsNMasks.pokAddr, shiftsNMasks.vdDetMask, shiftsNMasks.vdDetShift);

            if(instance != SDL_POK_VDDA_PMIC_IN_ID)
                {
                    pStaticRegs->trim = (SDL_pwrss_trim)SDL_REG32_FEXT_RAW(shiftsNMasks.pokAddr, shiftsNMasks.trimMask, shiftsNMasks.trimShift);
                }

        pStaticRegs->porBGapOK = (bool) ((SDL_REG32_FEXT(&pCtrlMMRCfgRegs->POR_STAT,WKUP_CTRL_MMR_CFG0_POR_STAT_BGOK) == 0x0u)?false:true);

        pStaticRegs->porModuleStatus = (SDL_por_module_status)SDL_REG32_FEXT(&pCtrlMMRCfgRegs->POR_STAT,WKUP_CTRL_MMR_CFG0_POR_STAT_SOC_POR);

    }
    return retVal;
}

/**
 * Design: PROC_SDL-1163
 */

/*returns pass or failure after checking the ESM error status*/
static int32_t SDL_POK_Thres_cong_seq(SDL_POK_Inst instance, SDL_POK_config *pInitCfg, uint32_t esm_err_sig)
{
    SDL_POK_config          pokCfg;
    SDL_pokVal_t            pokVal;
    int32_t                 retVal = SDL_EFAIL;
    SDL_wkupCtrlRegsBase_t    *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;

    /* POK configuration */
    /* Step 1: Mask POK event propogation by programming ESM_INTR_EN_CLR reg */
    retVal = SDL_ESM_disableIntr(ESM_INSTANCE, esm_err_sig);

    /* Step 2: Is POK Disabled, if not disable it */
    pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_GET_ENSEL_VALUE;
    pokCfg.trim    = SDL_PWRSS_TRIM_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;
    retVal = SDL_pokGetControl (pBaseAddr, &pokCfg, &pokVal, instance);

    if (pokVal.detectionStatus == SDL_POK_DETECTION_ENABLED)
    {
        /* Disable the detection control */
        pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
        pokCfg.trim    = SDL_PWRSS_TRIM_NO_ACTION;
        pokCfg.detectionCtrl = SDL_POK_DETECTION_DISABLE;
        retVal = SDL_pokSetControl(pBaseAddr,&pokCfg,instance);
    }

    /* Set to MMR control for POK */
    pokCfg.hystCtrl = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
    pokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;
    retVal = SDL_pokSetControl(pBaseAddr, &pokCfg, instance);

    /* Step 3: Program the appropriate threshold settings in POK_CTRL reg */

    pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;
    pokCfg.trim    = pInitCfg->trim;
    retVal = SDL_pokSetControl(pBaseAddr,&pokCfg,instance);

    /* Step 4: Enable the desired POK */
    pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode   = pInitCfg->voltDetMode;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
    pokCfg.trim    = SDL_PWRSS_TRIM_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_DETECTION_ENABLE;
    retVal = SDL_pokSetControl(pBaseAddr,&pokCfg,instance);

    /* Step 5: Wait for 100 us for the POK to settle */
    SDL_OSAL_delay(DELAY);

    /* Step 6: Read the POK out status to confirm voltage is within limits */
    if (retVal == SDL_PASS)
    {
        pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
        pokCfg.trim    = SDL_PWRSS_TRIM_NO_ACTION;
        pokCfg.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;
        /* below will get voltage threshold status */
        retVal = SDL_pokGetControl (pBaseAddr, &pokCfg, &pokVal, instance);
    }
    /* Step 7: If Power Good == Yes, unmask POK to ESM event propagation by
                    programming ESM_INTR_EN_SET register(s) else report to WKUP_ESM0*/
    if (retVal == SDL_PASS)
    {
        SDL_ESM_clearIntrStatus(ESM_INSTANCE, esm_err_sig);
        retVal = SDL_ESM_enableIntr(ESM_INSTANCE, esm_err_sig);
    }
    return (retVal);
}

/**
 * Design: PROC_SDL-1163
 */
static int32_t SDL_POR_Thres_cong_seq(SDL_POK_Inst instance, SDL_POK_config *pInitCfg, uint32_t esm_err_sig)
{
    SDL_wkupCtrlRegsBase_t      *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;
    SDL_pokPorCfg_t              porCfg;
    SDL_pokVal_t                 pokVal;
    SDL_POK_config               pokCfg;
    int32_t                      retVal = SDL_EFAIL;


    /* POR configuration */
    /* Step 1: MASKHHV set to 1 */
    porCfg.maskHHVOutputEnable                 = TRUE;

    /* Override is not needed to be changed for SW */
    porCfg.override[SDL_POKHV_OVERRIDE_INDEX]  = SDL_POR_SET_OVERRIDE_NO_CHANGE;
    porCfg.override[SDL_BGAP_OVERRIDE_INDEX]   = SDL_POR_SET_OVERRIDE_NO_CHANGE;
    porCfg.override[SDL_PORHV_OVERRIDE_INDEX]  = SDL_POR_SET_OVERRIDE_NO_CHANGE;
    porCfg.override[SDL_POKLVA_OVERRIDE_INDEX] = SDL_POR_SET_OVERRIDE_NO_CHANGE;
    porCfg.override[SDL_POKLVB_OVERRIDE_INDEX] = SDL_POR_SET_OVERRIDE_NO_CHANGE;

    /* Step 2: TRIM Mux selection is set to 0 */
    porCfg.trim_select                         = SDL_POR_TRIM_SELECTION_FROM_HHV_DEFAULT;

    retVal = SDL_porSetControl(pBaseAddr,&porCfg);

    /* Step 3: Is POK Disabled, if not disable it */
    pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
    pokCfg.trim          = SDL_PWRSS_TRIM_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;
    retVal = SDL_pokGetControl (pBaseAddr, &pokCfg, &pokVal, instance);


    if (pokVal.detectionStatus == SDL_POK_DETECTION_ENABLED)
    {
        /* Disable the detection control */
        pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
        pokCfg.trim          = SDL_PWRSS_TRIM_NO_ACTION;
        pokCfg.detectionCtrl = SDL_POK_DETECTION_DISABLE;
        retVal = SDL_pokSetControl(pBaseAddr,&pokCfg,instance);
    }

    /* Set to MMR control for POK */
    pokCfg.hystCtrl = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
    pokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;
    retVal = SDL_pokSetControl(pBaseAddr, &pokCfg, instance);


    /* Step 4: Pending: Mask POK to ESM event propagation by
                    programming ESM_INTR_EN_CLR register(s)
     */

    retVal = SDL_ESM_disableIntr(ESM_INSTANCE, esm_err_sig);


    /* Step 5: Program the appropriate threshold settings in POK_CTRL reg */

    pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
    pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
    pokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;

    pokCfg.trim          = pInitCfg->trim;
    retVal = SDL_pokSetControl(pBaseAddr,&pokCfg,instance);


    /* Step 6: Program the trim mux selection to 1, to select the new register/
               efuse values
     */
    if (retVal == SDL_PASS)
    {
        porCfg.trim_select                         = SDL_POR_TRIM_SELECTION_FROM_CTRL_REGS;
        retVal = SDL_porSetControl (pBaseAddr,&porCfg);

        /* Step 7: Set Mask HHV control to 0 */
        porCfg.trim_select                         = SDL_POR_TRIM_SELECTION_NO_CHANGE;
        porCfg.maskHHVOutputEnable                 = FALSE;
        retVal = SDL_porSetControl (pBaseAddr,&porCfg);
    }
    /* Step 8: Enable the desired POK */
    if (retVal == SDL_PASS)
    {
        pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pokCfg.voltDetMode   = pInitCfg->voltDetMode;
        pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
        pokCfg.trim          = SDL_PWRSS_TRIM_NO_ACTION;
        pokCfg.detectionCtrl = SDL_POK_DETECTION_ENABLE;
        retVal = SDL_pokSetControl(pBaseAddr,&pokCfg,instance);
    }
    /* Step 9: Wait for 100 us for the POK to settle */
     SDL_OSAL_delay(DELAY); /* has 1000 micro seconds delay, more than needed */

    /* Step 10: Read the POK out status to confirm voltage is within limits */
    if (retVal == SDL_PASS)
    {
       pokCfg.hystCtrl = SDL_PWRSS_HYSTERESIS_NO_ACTION;
       pokCfg.voltDetMode = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
       pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
       pokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
       pokCfg.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;
       retVal = SDL_pokGetControl (pBaseAddr, &pokCfg, &pokVal, instance);
    }
    /* Step 11: If Power Good == Yes, unmask POK to ESM event propagation by
                    programming ESM_INTR_EN_SET register(s) else report to WKUP_ESM0*/
    if (retVal == SDL_PASS)
    {
        SDL_ESM_clearIntrStatus(ESM_INSTANCE, esm_err_sig);
        retVal = SDL_ESM_enableIntr(ESM_INSTANCE, esm_err_sig);
    }
    return (retVal);
}

/**
 * Design: PROC_SDL-1344,PROC_SDL-1345,PROC_SDL-1346
 */
/*set POK and POR_POK module configurations*/
int32_t SDL_POK_init(SDL_POK_Inst instance,  SDL_POK_config *pPokCfg)
{
    int32_t                 retVal = SDL_PASS;
    SDL_POK_config          pokCfg;
    SDL_POK_Inst            esm_inst;
    bool                    usePorCfgFlag;
    uint32_t                esm_err_sig;

    if (pPokCfg == NULL)
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        if(instance == SDL_POK_VDDA_PMIC_IN_ID)
        {
            pokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
        }
        else
        {
            pokCfg.trim = pPokCfg->trim;
        }

        pokCfg.detectionCtrl = pPokCfg->detectionCtrl;
        pokCfg.hystCtrl = pPokCfg->hystCtrl;
        pokCfg.pokEnSelSrcCtrl = pPokCfg->pokEnSelSrcCtrl;
        pokCfg.voltDetMode = pPokCfg->voltDetMode;

        sdlGetErrSig(instance, &esm_inst, &esm_err_sig, &usePorCfgFlag);
        if (instance != esm_inst)
        {
            retVal = SDL_EBADARGS;
        }
        else if (usePorCfgFlag == (bool)false)
        {
            retVal = SDL_POK_Thres_cong_seq(instance, &pokCfg, esm_err_sig);
        }
        else
        {
            retVal = SDL_POR_Thres_cong_seq(instance, &pokCfg, esm_err_sig);
        }
    }

    return retVal;
}

/**
 * Design: PROC_SDL-1348,PROC_SDL-1161
 */

/*Verify POK module configurations*/
int32_t SDL_POK_verifyConfig(SDL_POK_Inst instance, SDL_POK_config *pPokCfg )
{
    int32_t              retVal= SDL_EFAIL;
    SDL_POK_config       pokCfg;
    SDL_pokVal_t         pPokVal;
    bool                 compare_hyst = false;
    bool                 compare_voltmode = false;
    bool                 compare_ensel = false;
    bool                 compare_trim = false;
    bool                 compare_detctrl = false;

    SDL_wkupCtrlRegsBase_t    *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;

    if (pPokCfg == NULL_PTR)
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        if ((pPokCfg->hystCtrl != SDL_PWRSS_HYSTERESIS_NO_ACTION) &&
            (pPokCfg->hystCtrl != SDL_PWRSS_GET_HYSTERESIS_VALUE))
        {
            pokCfg.hystCtrl = SDL_PWRSS_GET_HYSTERESIS_VALUE;
            compare_hyst = true;
        }
        else
        {
            pokCfg.hystCtrl = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        }
        if ((pPokCfg->voltDetMode != SDL_PWRSS_VOLTAGE_DET_NO_ACTION) &&
            (pPokCfg->voltDetMode != SDL_PWRSS_GET_VOLTAGE_DET_MODE))
        {
            pokCfg.voltDetMode = SDL_PWRSS_GET_VOLTAGE_DET_MODE;
            compare_voltmode = true;
        }
        else
        {
            pokCfg.voltDetMode = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        }
        if ((pPokCfg->pokEnSelSrcCtrl != SDL_POK_ENSEL_NO_ACTION) &&
            (pPokCfg->pokEnSelSrcCtrl != SDL_POK_GET_ENSEL_VALUE))
        {
            pokCfg.pokEnSelSrcCtrl = SDL_POK_GET_ENSEL_VALUE;
            compare_ensel = true;
        }
        else
        {
            pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
        }
        if ((pPokCfg->trim != SDL_PWRSS_TRIM_NO_ACTION) &&
            (pPokCfg->trim != SDL_PWRSS_GET_TRIM_VALUE))
        {
            pokCfg.trim = SDL_PWRSS_GET_TRIM_VALUE;
            compare_trim = true;
        }
        else
        {
            pokCfg.trim = SDL_PWRSS_TRIM_NO_ACTION;
        }
        if ((pPokCfg->detectionCtrl != SDL_POK_DETECTION_NO_ACTION) &&
            (pPokCfg->detectionCtrl != SDL_POK_GET_DETECTION_VALUE))
        {
            pokCfg.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;
            compare_detctrl = true;
        }
        else
        {
            pokCfg.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;
        }

        retVal = SDL_pokGetControl (pBaseAddr, &pokCfg, &pPokVal, instance);
        if (retVal == SDL_PASS)
        {
            if (((compare_hyst == (bool)true) && (pPokVal.hystCtrl != pPokCfg->hystCtrl)) ||
                ((compare_voltmode == (bool)true) && (pPokVal.voltDetMode != pPokCfg->voltDetMode)) ||
                ((compare_trim == (bool)true) && (pPokVal.trim != pPokCfg->trim)) ||
                ((compare_detctrl == (bool)true) && (pPokVal.detectionStatus == pPokCfg->detectionCtrl)) ||
                ((compare_ensel == (bool)true) && (pPokVal.pokEnSelSrcCtrl == pPokCfg->pokEnSelSrcCtrl)))
            {
                retVal = SDL_PASS;
            }
            else {
                retVal = SDL_EFAIL;
            }
        }
    }
    return (retVal);
}


/**
 * Design: PROC_SDL-1350
 */
/* Read threshold status of POK module */
int32_t SDL_POK_getStatus(SDL_POK_Inst instance, SDL_POK_thrStatus *pStatus)
{
    SDL_wkupCtrlRegsBase_t    *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;
    int32_t                    retVal = SDL_EBADARGS;
    SDL_pokVal_t               pPokVal;
    SDL_POK_config             pokCfg;

    if ((pStatus == NULL) || (instance < SDL_POK_VDDA_PMIC_IN_ID) || \
        (instance > SDL_POR_POKHV_OV_ID))
    {
        retVal = SDL_EBADARGS;
    }
    else
    {
        pokCfg.hystCtrl      = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pokCfg.voltDetMode   = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
        pokCfg.trim    = SDL_PWRSS_TRIM_NO_ACTION;
        pokCfg.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;
        retVal = SDL_pokGetControl (pBaseAddr, &pokCfg, &pPokVal, instance);
        if(retVal == SDL_PASS)
        {
            switch (instance)
            {
                /* PMIC POK ID */
                case    SDL_POK_VDDA_PMIC_IN_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* CORE POK Under Voltage ID */
                case     SDL_POK_VDD_CORE_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }

                    break;

                /* CPU under voltage POK ID */
                case     SDL_POK_VDD_CPU_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }

                    break;

                /* Wakeup General POK Under Voltage ID */
                case     SDL_POK_VDDSHV_WKUP_GEN_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }

                    break;

                /* MCU under voltage VDD POK ID */
                case     SDL_POK_VDDR_MCU_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }

                    break;

                /* VMON under voltage POK ID */
                case     SDL_POK_VMON_EXT_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }

                    break;

                /* MCU overvoltage POK ID */
                case     SDL_POK_VDD_MCU_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* VDD CORE POK ID */
                case     SDL_POK_VDDR_CORE_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* Wakeup General POK Over voltage ID */
                case     SDL_POK_VDDSHV_WKUP_GEN_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* CORE VDD Over Voltage POK ID */
                case     SDL_POK_VDD_CORE_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* MCU  over Voltage POK ID */
                case     SDL_POK_VDDR_MCU_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* CPU  over Voltage POK ID */
                case     SDL_POK_VDD_CPU_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* CORE VDDR over Voltage POK ID */
                case     SDL_POK_VDDR_CORE_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* VMON POK Over Voltage ID */
                case     SDL_POK_VMON_EXT_OV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* POKHV Under Voltage POK ID */
                case     SDL_POR_POKHV_UV_ID:

                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

               /* POKLV Under Voltage POK ID */
                case     SDL_POR_POKLV_UV_ID:
                     if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_BELOW_THRESHOLD;
                    }
                    else{
                         *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;

                /* POKHV Over Voltage POK ID */
                case     SDL_POR_POKHV_OV_ID:
                default:
                    if(pPokVal.voltageThrStatus == 0u)
                    {
                        *pStatus = SDL_VOLTAGE_ABOVE_THRESHOLD;
                    }
                    else{
                        *pStatus = SDL_VOLTAGE_GOOD ;
                    }
                    break;
            }
        }
    }
    return (retVal);
}
