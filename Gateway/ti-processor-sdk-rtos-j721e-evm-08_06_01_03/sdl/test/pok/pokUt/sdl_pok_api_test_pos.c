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
 *  \file     sdl_pok_api_test_pos.c
 *
 *  \brief    This file contains POK API unit test code.
 *
 *  \details  POK unit tests
 **/

#include "test_main.h"

int32_t sdl_pok_posTest(void)
{
    int32_t             testStatus = SDL_APP_TEST_PASS;
    SDL_POK_Inst        i;
    SDL_POK_staticRegs  pStaticRegs;
    SDL_POK_config      pConfig;
    SDL_POK_thrStatus   pStatus;


    /** hysteresis control */
    SDL_pwrss_hysteresis            hystCtrl;
    /** Voltage Detection Mode control */
    SDL_pwrss_vd_mode               voltDetMode;
    /** POK Trim bits 7 bits wide */
    SDL_pwrss_trim                  trim;
    /** POK Detection Enable */
    SDL_POK_detection               detectionCtrl;
    /** POK Enable Source control */
    SDL_POK_enSelSrc                pokEnSelSrcCtrl;



    /*test functin POK module configurations*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for (i = SDL_FIRST_POK_ID; i <= SDL_LAST_POK_ID; i++)
        {
            for (hystCtrl = SDL_PWRSS_SET_HYSTERESIS_DISABLE; \
                 hystCtrl <= SDL_PWRSS_HYSTERESIS_NO_ACTION; \
                 hystCtrl++ )
            {
                for (voltDetMode = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE; \
                     voltDetMode <= SDL_PWRSS_VOLTAGE_DET_NO_ACTION; \
                     voltDetMode++ )
                {
                    for (trim = SDL_PWRSS_MAX_TRIM_VALUE; \
                         trim <= SDL_PWRSS_GET_TRIM_VALUE; \
                         trim++ )
                    {
                        for (detectionCtrl = SDL_POK_DETECTION_DISABLE; \
                             detectionCtrl <= SDL_POK_GET_DETECTION_VALUE; \
                             detectionCtrl++ )
                        {
                            for (pokEnSelSrcCtrl= SDL_POK_ENSEL_HWTIEOFFS; \
                                 pokEnSelSrcCtrl <= SDL_POK_GET_ENSEL_VALUE; \
                                 pokEnSelSrcCtrl++ )
                            {
                                pConfig.hystCtrl         = hystCtrl;
                                pConfig.voltDetMode      = voltDetMode;
                                pConfig.trim             = trim;
                                pConfig.detectionCtrl    = detectionCtrl;
                                pConfig.pokEnSelSrcCtrl  = pokEnSelSrcCtrl;

                                if (((SDL_POK_init(i,&pConfig)) != SDL_PASS) &&   \
                                    (SDL_POK_verifyConfig(i, &pConfig ) != SDL_PASS))
                                {
                                    if ( (pokEnSelSrcCtrl == SDL_POK_GET_ENSEL_VALUE) ||
                                         (detectionCtrl   == SDL_POK_GET_DETECTION_VALUE) ||
                                         (trim            == SDL_PWRSS_GET_TRIM_VALUE) ||
                                         (voltDetMode     == SDL_PWRSS_GET_VOLTAGE_DET_MODE) ||
                                         (hystCtrl        == SDL_PWRSS_GET_HYSTERESIS_VALUE))
                                    {
                                        /* no break, expected result */
                                    }
                                    else
                                    {
                                        testStatus = SDL_APP_TEST_FAILED;
                                        UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POK_VDDR_CORE_UV_ID;
        pConfig.voltDetMode  = 246u;

        if (SDL_POK_init(i, &pConfig)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }

        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i = SDL_POK_VDDR_CORE_UV_ID;
        pConfig.trim  = 246u;

        if (SDL_POK_init(i, &pConfig)!= SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }

        if (testStatus != SDL_APP_TEST_PASS)
        {
            UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
            return (testStatus);
        }
    }

    /* function test reads the values of static registers such as hysteresis
     * control,voltage detect mode, trim, PORGAP and module status */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            if ((SDL_POK_getStaticRegisters(i,&pStaticRegs)) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
            }
        }
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
            pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
            pConfig.trim            = 0u;
            pConfig.voltDetMode     = SDL_PWRSS_SET_UNDER_VOLTAGE_DET_ENABLE;
            pConfig.detectionCtrl   = SDL_POK_DETECTION_ENABLE;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    /*test Verify POK module configurations*/
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            if ((SDL_POK_getStatus(i, &pStatus)) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
            }
        }

    }

    /* test Read threshold status of POK module */
    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
            pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
            pConfig.trim            = 0u;
            pConfig.voltDetMode     = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
            pConfig.detectionCtrl   = SDL_POK_DETECTION_ENABLE;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
        {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
        }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
            pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
            pConfig.trim            = 0u;
            pConfig.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
            pConfig.detectionCtrl   = SDL_POK_DETECTION_ENABLE;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
        {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
        }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
            pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
            pConfig.trim            = 0;
            pConfig.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
            pConfig.detectionCtrl   = SDL_POK_DETECTION_ENABLE;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
        {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
        }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
            pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_NO_ACTION;
            pConfig.trim            = SDL_PWRSS_TRIM_NO_ACTION ;
            pConfig.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
            pConfig.detectionCtrl   = SDL_POK_DETECTION_ENABLE;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
        {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
        }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }



    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.trim            = 45u;
            pConfig.voltDetMode     = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
        {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
        }
            if ((SDL_POK_getStatus(i, &pStatus) != SDL_PASS))
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = 255u;
            pConfig.pokEnSelSrcCtrl = 255u;
            pConfig.trim            = 255u ;
            pConfig.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
            pConfig.detectionCtrl   = 255u;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = 255u;
            pConfig.pokEnSelSrcCtrl = 255u;
            pConfig.trim            = 255u ;
            pConfig.voltDetMode     = SDL_PWRSS_GET_VOLTAGE_DET_MODE;
            pConfig.detectionCtrl   = 255u;

            if (SDL_POK_init(i, &pConfig) != SDL_EFAIL)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_POR_POKHV_OV_ID;
        pConfig.hystCtrl      = SDL_PWRSS_SET_HYSTERESIS_ENABLE;
        pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
        pConfig.trim          = 127;
        pConfig.voltDetMode   = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
        pConfig.detectionCtrl = SDL_POK_DETECTION_NO_ACTION;

        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_POR_POKHV_OV_ID;
        pConfig.hystCtrl      = SDL_PWRSS_SET_HYSTERESIS_ENABLE;
        pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
        pConfig.trim          = 127;
        pConfig.voltDetMode   = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
        pConfig.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;

        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_POR_POKHV_OV_ID;
        pConfig.hystCtrl      = 246u;
        pConfig.pokEnSelSrcCtrl = SDL_POK_ENSEL_PRG_CTRL;
        pConfig.trim          = 127;
        pConfig.voltDetMode   = SDL_PWRSS_SET_OVER_VOLTAGE_DET_ENABLE;
        pConfig.detectionCtrl = SDL_POK_GET_DETECTION_VALUE;

        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_POR_POKHV_OV_ID;
        pConfig.hystCtrl        = 255u;
        pConfig.pokEnSelSrcCtrl = 255u;
        pConfig.trim            = 255u;
        pConfig.voltDetMode     = 255u;
        pConfig.detectionCtrl   = 255u;

        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i= SDL_POR_POKHV_OV_ID;
        pConfig.hystCtrl        = 255u;
        pConfig.pokEnSelSrcCtrl = 255u;
        pConfig.trim            = 255u;
        pConfig.voltDetMode     = 255u;
        pConfig.detectionCtrl   = SDL_POK_GET_DETECTION_VALUE;

        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
        }
    }

    if (testStatus != SDL_APP_TEST_PASS)
    {
        UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
        return (testStatus);
    }



    if (testStatus == SDL_APP_TEST_PASS)
    {
        for( i=SDL_POK_VDDA_PMIC_IN_ID; i<=SDL_POR_POKHV_OV_ID; i++)
        {
            pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
            pConfig.pokEnSelSrcCtrl = 255u;
            pConfig.trim            = 255u;
            pConfig.voltDetMode     = 255u;
            pConfig.detectionCtrl   = 255u;

            if (SDL_POK_init(i, &pConfig) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
            if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
            {
                testStatus = SDL_APP_TEST_FAILED;
                UART_printf("SDLPok_api_Pos_Test: failure on line no. %d \n", __LINE__);
                break;
            }
        }

    }

    if (testStatus == SDL_APP_TEST_PASS)
    {
        i=SDL_POR_POKHV_OV_ID;
        pConfig.hystCtrl        = SDL_PWRSS_HYSTERESIS_NO_ACTION;
        pConfig.pokEnSelSrcCtrl = 255u;
        pConfig.trim            = 255u ;
        pConfig.voltDetMode     = SDL_PWRSS_VOLTAGE_DET_NO_ACTION;
        pConfig.detectionCtrl   = 255u;

        if (SDL_POK_init(i, &pConfig) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);

        }
        if ((SDL_POK_verifyConfig(i, &pConfig )) != SDL_PASS)
        {
            testStatus = SDL_APP_TEST_FAILED;
            UART_printf("SDLPok_api_Neg_Test: failure on line no. %d \n", __LINE__);

        }
    }

    return (testStatus);
}
