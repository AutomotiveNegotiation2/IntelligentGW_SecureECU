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
 *  \file     sdl_pok_api_test_neg.c
 *
 *  \brief    This file contains POK API unit test code..
 *
 *  \details  POK unit tests
 **/

#include "test_main.h"

int32_t sdl_pok_negTest(void)
{
    int32_t              testStatus = SDL_APP_TEST_PASS;
    SDL_POK_Inst         i = SDL_INVALID_POK_ID;
    SDL_POK_staticRegs   pStaticRegs;
    SDL_POK_config       pConfig;
    SDL_POK_thrStatus    pStatus;

    /* function test reads the values of static registers such as hysteresis
     * control,voltage detect mode, trim, PORGAP and module status */

    if (testStatus == SDL_APP_TEST_PASS)
    {
        if ((SDL_POK_getStaticRegisters(i,&pStaticRegs)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;
        if ((SDL_POK_getStaticRegisters(i,NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;
        if ((SDL_POK_getStaticRegisters(i,NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;
        if ((SDL_POK_getStaticRegisters(i,NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;

        if ((SDL_POK_getStaticRegisters(i,&pStaticRegs)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i=(-(int32_t) (46));

        if ((SDL_POK_getStaticRegisters(i,&pStaticRegs)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    /*Negetive test functin POK module configurations*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;
        if ((SDL_POK_init(i,&pConfig)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        if ((SDL_POK_init(i,NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }


    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= (-(int32_t) (46));


        if ((SDL_POK_init(i,&pConfig)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    /* test Read threshold status of POK module */

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;

        if ((SDL_POK_getStatus(i, &pStatus)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POR_POKHV_OV_ID;

        if ((SDL_POK_getStatus(i,NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;

        if ((SDL_POK_getStatus(i,NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= (-(int32_t) (46));

        if ((SDL_POK_getStatus(i, &pStatus)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    /*test Verify POK module configurations*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;
        pConfig.hystCtrl      = SDL_PWRSS_SET_HYSTERESIS_ENABLE;
        pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
        pConfig.trim          = 127;
        pConfig.voltDetMode   = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
        pConfig.detectionCtrl = SDL_POK_DETECTION_ENABLE;

        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_POR_POKHV_OV_ID;

        if ((SDL_POK_verifyConfig(i, NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_INVALID_POK_ID;
        if ((SDL_POK_verifyConfig(i, NULL)) != SDL_EBADARGS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    return (testStatus);
}
