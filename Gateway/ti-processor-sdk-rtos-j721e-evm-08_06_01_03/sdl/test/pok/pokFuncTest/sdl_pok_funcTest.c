/* Copyright (c) 2021 Texas Instruments Incorporated
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

 /**
 *  \file     sdl_pok_funcTest.c
 *
 *  \brief    This file contains POK API functionality test code.
 *
 *  \details  POK functionality tests
 **/

/*===========================================================================*/
/*                         Include files                                     */
/*===========================================================================*/
#include "main.h"
#include <ti/osal/HwiP.h>
#include <ti/osal/RegisterIntr.h>

/*===========================================================================*/
/*                         Macros                                            */
/*===========================================================================*/
/* None */

/* Global variables */
volatile Bool ESM_Error = false;
HwiP_Handle gHwiHandle;

/*===========================================================================*/
/*                         Internal function declarations                    */
/*===========================================================================*/
static int32_t sdlPOK_Test(SDL_POK_Inst instance, SDL_POK_config *pPokCfg);
static void    sdlEsmSetupForPOK(uint32_t esm_err_sig);
static int32_t ESMApp_registerIsr(uintptr_t arg);
static int32_t ESMApp_unregisterIsr(uintptr_t arg);
static void    ESMApp_intrISR(uintptr_t handle);
int32_t        sdlPOKInPor_funcTest(void);
int32_t        sdlPOK_funcTest(void);


/*===========================================================================*/
/*                         Function definitions                              */
/*===========================================================================*/
static void sdlPOKGetUVOV(uint32_t id, bool *isOV)
{
    switch (id)
    {
        case SDL_POR_POKHV_UV_ID:
        case SDL_POR_POKLV_UV_ID:
        case SDL_POK_VDDA_PMIC_IN_ID:
        case SDL_POK_VDD_CORE_UV_ID:
        case SDL_POK_VDDSHV_WKUP_GEN_UV_ID:
        case SDL_POK_VDD_CPU_UV_ID:
        case SDL_POK_VDDR_MCU_UV_ID:
        case SDL_POK_VMON_EXT_UV_ID:
        case SDL_POK_VDDR_CORE_UV_ID:
            *isOV          = FALSE;
            break;
        case SDL_POR_POKHV_OV_ID:
        case SDL_POK_VDD_MCU_OV_ID:
        case SDL_POK_VDDSHV_WKUP_GEN_OV_ID:
        case SDL_POK_VDD_CORE_OV_ID:
        case SDL_POK_VDDR_MCU_OV_ID:
        case SDL_POK_VDD_CPU_OV_ID:
        case SDL_POK_VDDR_CORE_OV_ID:
        case SDL_POK_VMON_EXT_OV_ID:
        default:
            *isOV          = TRUE;
            break;
    }
    return;
}

static int32_t ESMApp_unregisterIsr(uintptr_t arg)
{
    int32_t retVal = SDL_EFAIL;
    OsalInterruptRetCode_e osalRetVal;

    osalRetVal = Osal_DeleteInterrupt(&gHwiHandle, 0U);
    if(OSAL_INT_SUCCESS != osalRetVal)
    {
        retVal = SDL_EFAIL;
        UART_printf("Error Could not un-register ISR !!!\n");
    }
    return (retVal);
}


static int32_t ESMApp_registerIsr(uintptr_t arg)
{
    int32_t retVal = SDL_EFAIL;
    uint32_t EsmInt;
    OsalRegisterIntrParams_t intrPrms;
    OsalInterruptRetCode_e osalRetVal;

    Osal_RegisterInterrupt_initParams(&intrPrms);
    intrPrms.corepacConfig.arg          = (uintptr_t) arg;
    intrPrms.corepacConfig.priority     = 1U;
    intrPrms.corepacConfig.corepacEventNum = 0U; /* NOT USED ? */

    EsmInt = ESM_INTID;
    intrPrms.corepacConfig.isrRoutine   = &ESMApp_intrISR;
    retVal = SDL_PASS;
    intrPrms.corepacConfig.intVecNum = EsmInt;
    osalRetVal = Osal_RegisterInterrupt(&intrPrms, &gHwiHandle);
    if(OSAL_INT_SUCCESS != osalRetVal)
    {
        retVal = SDL_EFAIL;
        UART_printf("Error Could not register ISR !!!\n");
    }
    return (retVal);
}


static void ESMApp_intrISR(uintptr_t handle)
{
    uint32_t esm_err_sig = (uint32_t) handle;
    ESM_Error = true;
    /* Disable the ESM Interrupt */
    SDL_ESM_disableIntr(ESM_INSTANCE, esm_err_sig);
    SDL_ESM_clearIntrStatus(ESM_INSTANCE, esm_err_sig);
    SDL_ESM_resetErrPin(ESM_INSTANCE);
}

void sdlEsmSetupForPOK(uint32_t esm_err_sig)
{
    /* ESM Variables */
    esmInfo_t   appEsmInfo;


    /* Check INFO register for ESM last reset cause */
    SDL_ESM_getInfo(ESM_INSTANCE, &appEsmInfo);
    SDL_ESM_reset(ESM_INSTANCE);

    /* The below function can be changed to force an error for diagnostic
     * reasons. */
    /* make sure we're not in force error mode */
    SDL_ESM_setMode(ESM_INSTANCE, ESM_OPERATION_MODE_NORMAL);

    /* Enable this ESM Error Signal */
    SDL_ESM_enableIntr(ESM_INSTANCE, esm_err_sig);

    /* Set the output interrupt priority level */
    SDL_ESM_setIntrPriorityLvl(ESM_INSTANCE, esm_err_sig, ESM_INTR_PRIORITY_LEVEL_HIGH);

    /* Enable Error Pin on this ESM Error Signal */
    SDL_ESM_setInfluenceOnErrPin(ESM_INSTANCE, esm_err_sig, TRUE);

    /* Enable for all ESM Error Signals */
    SDL_ESM_enableGlobalIntr(ESM_INSTANCE);
}

static int32_t sdlPOK_Test(SDL_POK_Inst instance, SDL_POK_config *pPokCfg)
{
    int32_t sdlRet;
    SDL_POK_staticRegs pStaticRegs;
    pPokCfg->hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
    pPokCfg->pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
    pPokCfg->detectionCtrl   = SDL_POK_DETECTION_ENABLE;

    sdlRet = SDL_POK_getStaticRegisters(instance,&pStaticRegs);
    if (sdlRet == SDL_PASS )
    {
        UART_printf ("\n\n static trim value is = %d \n", pStaticRegs.trim);
    }
    else{
        UART_printf ("\n\n SDL_POK_getStaticRegisters Failed \n");
    }
    sdlRet = SDL_POK_init(instance, pPokCfg);
    if (sdlRet != SDL_PASS)
    {
        UART_printf("SDL_POK_init failed! \n");
    }
    sdlRet = SDL_POK_verifyConfig(instance,pPokCfg );
    if (sdlRet != SDL_PASS)
    {
        UART_printf("SDL_POK_verifyConfig failed! \n");
    }
    else
    {
        volatile int32_t i = 0;
        UART_printf("Waiting for ESM to report the error \n");
        /* Wait for the ESM interrupt to report the error */
        do {
            i++;
            if (i > 0x0FFFFFFF)
            {
                /* Timeout for the wait */
                break;
            }
        } while (ESM_Error == false);
        if (ESM_Error == true)
        {
         UART_printf(" Got the ESM Error Interrupt \n");
#if defined(BUILD_UART_SCANFMT)
            UART_printf(" Update the voltage threshold the test \
                         (Note: If threshold is below or above \
                         tracking threshold, interrupt may be triggered again \n");
            UART_scanFmt ("%d \n", pPokCfg->trim);
#endif
            sdlRet  = SDL_PASS;
            ESM_Error = false;
            }
            else
            {
                sdlRet = SDL_EFAIL;
        }
    }
    return (sdlRet);
}

int32_t sdlPOKInPor_funcTest(void)
{
    int32_t                      testStatus, sdlRet = SDL_PASS, overallStatus = SDL_APP_TEST_PASS;
    SDL_POK_config               pPokCfg;
    uint32_t                     esm_err_sig;
    SDL_POK_Inst                 instance;
    bool                         usePorCfgFlag;
    uint32_t                     i;
    bool                         isOV;
    SDL_POK_staticRegs           pStaticRegs;

    UART_printf(" Below are the POK In POR ID values for the test\n");
    UART_printf("  SDL_POR_POKHV_UV_ID is:           14 \n");
    UART_printf("  SDL_POR_POKLV_UV_ID is:           15 \n");
    UART_printf("  SDL_POR_POKHV_OV_ID is:           16 \n");

#if defined (BUILD_UART_SCANFMT)
    UART_printf("\n\n Enter the POK ID for the test  \n");
    UART_scanFmt ("%d \n", &instance);
    UART_printf(" Enter the voltage threshold the test  \n");
    UART_scanFmt ("%d \n", &pPokCfg.trim);
    UART_printf(" Enter the Voltage Detection (0: UV, 1: OV) for the POK ID to monitor for the test  \n");
    UART_scanFmt ("%d \n", &pPokCfg.voltDetMode);
    if (pPokCfg.voltDetMode == 0U)
    {
         pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
    }
    else
    {
         pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
    }
#else
    instance = SDL_POR_POKHV_OV_ID;
    UART_printf ("\n\nDefault test loops through POK IDs \n", instance);
    pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
    pPokCfg.trim = 0;
#endif
    sdlRet = SDL_POK_getStaticRegisters(instance,&pStaticRegs);
    if (sdlRet == SDL_PASS )
    {
        UART_printf ("\n\bandGap status %d\n",  pStaticRegs.porBGapOK );
        UART_printf ("\n\nmodule status %d\n",  pStaticRegs.porModuleStatus );
    }
    else{
        UART_printf("SDL_POK_getStaticRegisters failed! \n");
    }

    for (i = SDL_POR_POKHV_UV_ID; i < SDL_POR_POKHV_OV_ID + 1; i++)
    {
        sdlGetErrSig(i, &instance, &esm_err_sig, &usePorCfgFlag);
        sdlPOKGetUVOV(i, &isOV);

        if (isOV == true)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = 0;
        }
        else
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = 127;
        }

        /* ESM Setup for POK tests */
        sdlEsmSetupForPOK(esm_err_sig);
        sdlRet = ESMApp_registerIsr((uintptr_t)esm_err_sig);
        if (sdlRet == SDL_PASS)
        {
            sdlRet = sdlPOK_Test(instance, &pPokCfg);
            /* Re-configure to "good" setting */
            if (isOV == true)
            {
                pPokCfg.trim = 45;
            }
            else
            {
                pPokCfg.trim = 0;
            }
            sdlPOK_Test(instance, &pPokCfg);
            /* Un register the Interrupt */
            ESMApp_unregisterIsr((uintptr_t)esm_err_sig);
        }

        if (sdlRet == SDL_PASS)
        {
            testStatus = SDL_APP_TEST_PASS;
        }
        else
        {
            testStatus = SDL_APP_TEST_FAILED;
            overallStatus = SDL_APP_TEST_FAILED;
        }
        UART_printf("Test for instance %d %s\n", instance, (testStatus == SDL_APP_TEST_PASS) ? "PASSED" : "FAILED");
    }
    return (overallStatus);
}


int32_t sdlPOK_funcTest(void)
{
    int32_t                      testStatus, sdlRet = SDL_PASS, overallStatus = SDL_APP_TEST_PASS;
    SDL_POK_config               pPokCfg;
    bool                         usePorCfgFlag;
    uint32_t                     esm_err_sig;
    SDL_POK_Inst                 instance;
    uint32_t                     i;
    bool                         isOV;
    SDL_POK_staticRegs           pStaticRegs;

    UART_printf(" Below are the POK ID values \n");
    UART_printf("  SDL_POK_VDDA_PMIC_IN_ID is:       0 \n");
    UART_printf("  SDL_POK_VDD_CORE_UV_ID is:        1 \n");
    UART_printf("  SDL_POK_VDDSHV_WKUP_GEN_UV_ID is: 2 \n");
    UART_printf("  SDL_POK_VDD_CPU_UV_ID is:         3 \n");
    UART_printf("  SDL_POK_VDDR_MCU_UV_ID is:        4 \n");
    UART_printf("  SDL_POK_VMON_EXT_UV_ID is:        5 \n");
    UART_printf("  SDL_POK_VDD_MCU_OV_ID is:         6 \n");
    UART_printf("  SDL_POK_VDDR_CORE_UV_ID is:       7 \n");
    UART_printf("  SDL_POK_VDDSHV_WKUP_GEN_OV_ID is: 8 \n");
    UART_printf("  SDL_POK_VDD_CORE_OV_ID is:        9 \n");
    UART_printf("  SDL_POK_VDDR_MCU_OV_ID is:        10 \n");
    UART_printf("  SDL_POK_VDD_CPU_OV_ID is:         11 \n");
    UART_printf("  SDL_POK_VDDR_CORE_OV_ID is:       12 \n");
    UART_printf("  SDL_POK_VMON_EXT_OV_ID is:        13 \n");

#if defined (BUILD_UART_SCANFMT)
    UART_printf("\n\n Enter the POK ID for the test  \n");
    UART_scanFmt ("%d \n", &instance);
    UART_printf(" Enter the voltage threshold the test  \n");
    UART_scanFmt ("%d \n", &pPokCfg.trim);
    UART_printf(" Enter the Voltage Detection (0: UV, 1: OV) for the POK ID to monitor for the test  \n");
    UART_scanFmt ("%d \n", &pPokCfg.voltDetMode);
    if (pPokCfg.voltDetMode == 0U)
    {
         pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
    }
    else
    {
         pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
    }
#else
    instance = SDL_POK_VDD_CORE_OV_ID;
    UART_printf ("\n\nDefault test with POK ID = %d , monitoring set to OV \n", instance);
    pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
    pPokCfg.trim = 0;
#endif

    for (i = SDL_POK_VDD_CORE_UV_ID; i < SDL_POK_VMON_EXT_OV_ID + 1; i++)
    {
        sdlGetErrSig(i, &instance, &esm_err_sig, &usePorCfgFlag);
        sdlPOKGetUVOV(i, &isOV);
        if (isOV == true)
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = 0;
        }
        else
        {
            pPokCfg.voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pPokCfg.trim = 127;
        }

        /* ESM Setup for POK tests */
        sdlEsmSetupForPOK(esm_err_sig);
        sdlRet = ESMApp_registerIsr((uintptr_t)esm_err_sig);

        if (sdlRet == SDL_PASS)
        {
            sdlRet = SDL_POK_getStaticRegisters(instance,&pStaticRegs);
            if (sdlRet == SDL_PASS )
            {
                 UART_printf ("\n\n static trim value is %d \n",pStaticRegs.trim );
            }

            sdlRet = sdlPOK_Test(instance, &pPokCfg);

            if (sdlRet == SDL_PASS)
            {
                testStatus = SDL_APP_TEST_PASS;
            }
            else
            {
                testStatus = SDL_APP_TEST_FAILED;
                overallStatus = SDL_APP_TEST_FAILED;
            }
            /* Re-set the trim value to a good value */
            if (isOV == true)
            {
                pPokCfg.trim = 45;
            }
            else
            {
                pPokCfg.trim = 0;
            }
            sdlPOK_Test(instance, &pPokCfg);
            /* Un register the Interrupt */
            ESMApp_unregisterIsr((uintptr_t)esm_err_sig);
        }
        UART_printf("Test for instance %d %s\n", instance, (testStatus == SDL_APP_TEST_PASS) ? "PASSED" : "FAILED");
    }
    return (overallStatus);
}

/* Nothing past this point */
