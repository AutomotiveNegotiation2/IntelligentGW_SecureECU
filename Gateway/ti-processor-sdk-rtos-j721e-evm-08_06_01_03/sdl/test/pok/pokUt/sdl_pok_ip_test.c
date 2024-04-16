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
 *  \file     sdl_pok_ip_test.c
 *
 *  \brief    This file contains POK ip functionality test code.
 *
 *  \details  POK unit tests
 **/

#include "test_main.h"
#include <src/ip/sdl_ip_pok.h>
int32_t sdl_ip_pokNegTest(void)
{
     int32_t                   testStatus = SDL_APP_TEST_PASS;
     SDL_POK_Inst              i= SDL_POR_POKHV_OV_ID;;
     SDL_POK_config            pPokCfg;
     SDL_pokVal_t              pPokVal;
        SDL_wkupCtrlRegsBase_t    *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;

    /*  SDL_porSetControl negative function test*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t            pPorCfg;
        pPorCfg.trim_select = 4u;
        pPorCfg.maskHHVOutputEnable = 2u;

        if(SDL_porSetControl(pBaseAddr,&pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t            pPorCfg;

            if(SDL_porSetControl(NULL,&pPorCfg)!= SDL_EBADARGS)

            {
                testStatus = SDL_APP_TEST_FAILED;
            }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        if(SDL_porSetControl(pBaseAddr, NULL)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t            pPorCfg;

        pPorCfg.trim_select = 255u;
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t    pPorCfg;

        pPorCfg.maskHHVOutputEnable = (-(bool)1);
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t    pPorCfg;

        pPorCfg.override[SDL_PORHV_OVERRIDE_INDEX] = 255u;
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t    pPorCfg;
        pPorCfg.override[SDL_PORHV_OVERRIDE_INDEX] = SDL_POR_OVERRIDE_SET_ENABLE;
        pPorCfg.trim_select = 2;
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t    pPorCfg;

        pPorCfg.override[SDL_PORHV_OVERRIDE_INDEX] = SDL_POR_OVERRIDE_NOT_SET_DISABLE;
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t    pPorCfg;

        pPorCfg.override[SDL_PORHV_OVERRIDE_INDEX] = SDL_POR_SET_OVERRIDE_NO_CHANGE;
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_pokPorCfg_t    pPorCfg;

        pPorCfg.override[SDL_PORHV_OVERRIDE_INDEX] = 246u;
        if(SDL_porSetControl(pBaseAddr, &pPorCfg)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    /*  SDL_pokSetControl negative function test*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        pPokCfg.hystCtrl         = 255u;
        pPokCfg.voltDetMode      = 255u;
        pPokCfg.trim             = 255u;
        pPokCfg.detectionCtrl    = SDL_POK_GET_DETECTION_VALUE;
        pPokCfg.pokEnSelSrcCtrl  = 255u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        pPokCfg.hystCtrl         = 255u;
        pPokCfg.voltDetMode      = SDL_PWRSS_GET_VOLTAGE_DET_MODE;
        pPokCfg.trim             = 255u;
        pPokCfg.detectionCtrl    = 255u;
        pPokCfg.pokEnSelSrcCtrl  = 255u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        pPokCfg.hystCtrl         = 255u;
        pPokCfg.voltDetMode      = 255u;
        pPokCfg.trim             = SDL_PWRSS_GET_TRIM_VALUE;
        pPokCfg.detectionCtrl    = 255u;
        pPokCfg.pokEnSelSrcCtrl  = 255u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        i = SDL_POR_POKHV_OV_ID;
        pPokCfg.hystCtrl       = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   =  255u;
        pPokCfg.pokEnSelSrcCtrl  = 255u;

        if(SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        pPokCfg.hystCtrl         = 255u;
        pPokCfg.voltDetMode      = 255u;
        pPokCfg.trim             = 255u;
        pPokCfg.detectionCtrl    = 255u;
        pPokCfg.pokEnSelSrcCtrl  = SDL_POK_GET_ENSEL_VALUE;


        if(SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl       = SDL_PWRSS_GET_HYSTERESIS_VALUE;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   =  255u;
        pPokCfg.pokEnSelSrcCtrl  = 255u;

        if(SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EFAIL)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        if (SDL_pokSetControl(pBaseAddr,NULL,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        if (SDL_pokSetControl(pBaseAddr,NULL,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;
        if (SDL_pokSetControl(pBaseAddr,NULL,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }
    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;
        if (SDL_pokSetControl(NULL, &pPokCfg,i)!= SDL_EBADARGS)
        {
             testStatus = SDL_APP_TEST_FAILED;
        }
    }

        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 255u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = 46u;
        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 2u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    /*  SDL_pokGetControl negative function test*/

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        SDL_POK_Inst                 i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;

        if(SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i!= SDL_EFAIL))
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        SDL_POK_Inst                 i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pPokCfg.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pPokCfg.trim            = SDL_PWRSS_TRIM_NO_ACTION;
        pPokCfg.detectionCtrl   = SDL_POK_DETECTION_NO_ACTION;
        pPokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;

        if(SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i!= SDL_EFAIL))
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        SDL_POK_Inst                 i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 255u;

        if(SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i!= SDL_EFAIL))
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        SDL_POK_Inst                 i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = SDL_PWRSS_TRIM_NO_ACTION;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 255u;

        if(SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i!= SDL_EFAIL))
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        SDL_POK_Inst                 i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = SDL_POK_DETECTION_NO_ACTION;
        pPokCfg.pokEnSelSrcCtrl = 255u;

        if(SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i!= SDL_EFAIL))
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        SDL_POK_Inst                 i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;

        if(SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i!= SDL_EFAIL))
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;
        i = SDL_POR_POKHV_OV_ID;
        pPokCfg.hystCtrl        = 5u;
        pPokCfg.voltDetMode     = 5u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 5u;
        pPokCfg.pokEnSelSrcCtrl = 5u;

        if (SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_config               pPokCfg;
        SDL_pokVal_t                 pPokVal;

        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 255u;

        if (SDL_pokGetControl(pBaseAddr,&pPokCfg,&pPokVal,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_pokGetControl(NULL, &pPokCfg, &pPokVal,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_pokGetControl(pBaseAddr,NULL,&pPokVal,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {

        if (SDL_pokGetControl(pBaseAddr, &pPokCfg, NULL,i)!= SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPOK_ip_negTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }
       return (testStatus);
}


/******************************************************************************************/
/*                       Ip positve test                                                  */
/****************************************************************************************/

int32_t sdl_ip_pokPosTest(void)
{
    int32_t                   testStatus = SDL_APP_TEST_PASS;
    SDL_POK_Inst              i;
    SDL_POK_config            pPokCfg;
    SDL_wkupCtrlRegsBase_t    *pBaseAddr = (SDL_wkupCtrlRegsBase_t *) SDL_POK_MMR_BASE;

    /*  SDL_pokSetControl positive function test*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 255u;


        if (SDL_pokSetControl(pBaseAddr, &pPokCfg, i) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

     if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl =  255u;


        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

     if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = SDL_PWRSS_MAX_TRIM_VALUE;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl =  255u;


        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = SDL_POK_DETECTION_DISABLE;
        pPokCfg.pokEnSelSrcCtrl =  255u;


        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = SDL_POK_DETECTION_ENABLE;
        pPokCfg.pokEnSelSrcCtrl =  255u;


        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl =  SDL_POK_ENSEL_HWTIEOFFS;


        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

     if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 2u;
        pPokCfg.pokEnSelSrcCtrl = 255u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        pPokCfg.hystCtrl        = 255u;
        pPokCfg.voltDetMode     = 255u;
        pPokCfg.trim            = 255u;
        pPokCfg.detectionCtrl   = 255u;
        pPokCfg.pokEnSelSrcCtrl = 2u;

        if (SDL_pokSetControl(pBaseAddr,&pPokCfg,i)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    /* SDL_pok_GetShiftsAndMasks Positive test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;
        SDL_pokShiftsAndMasks_t pShMasks;

        if(SDL_pok_GetShiftsAndMasks(pBaseAddr, i ,&pShMasks)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }


        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    /* Get error signal Positive test */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        SDL_POK_Inst            esm_inst;
        bool                    usePorCfgFlag;
        uint32_t                esm_err_sig;

        sdlGetErrSig(SDL_POK_VDDA_PMIC_IN_ID, &esm_inst, &esm_err_sig, &usePorCfgFlag);

        if (esm_err_sig != ESM_ERR_SIG_VDDA_IN)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("sdlPok_ip_posTest: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

       return (testStatus);
}

/*****************************************************************************/







