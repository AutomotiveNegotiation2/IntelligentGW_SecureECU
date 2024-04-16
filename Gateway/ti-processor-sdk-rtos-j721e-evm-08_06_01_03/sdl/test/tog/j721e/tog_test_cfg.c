/*
 *   Copyright (c) Texas Instruments Incorporated 2021
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
 *  \file     tog_test_cfg.c
 *
 *  \brief    This file contains TOG test configuration
 *
 *  \details  TOG Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <src/sdl/sdl_types.h>
#include <src/ip/sdl_ip_tog.h>
#include <include/soc.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/sciclient/sciclient.h>

/* Osal API header files */
#include <ti/osal/HwiP.h>
#include <ti/osal/TimerP.h>
#include "esm_app.h"
#include "tog_test_cfg.h"
#include "tog_test_utils.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */


/* ========================================================================== */
/*                                Function prototypes                         */
/* ========================================================================== */
__attribute((section(".text:TOG_test"))) void TOG_injectESMError(uint32_t instanceIndex);
__attribute((section(".text:TOG_test"))) void TOG_injectMCU64B2TimeoutError(uint32_t instanceIndex);
__attribute((section(".text:TOG_test"))) void TOG_injectMCUINFRATimeoutError(uint32_t instanceIndex);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t gTestMSMCLocation[256] __attribute((section(".data:TOG_MSMC_location")));

TOG_TestHandle_t TOG_TestHandleArray[TOG_MAX_INSTANCE+1] __attribute((section(".data:TOG_test")))=
{

    /* MCU_INFRA0 */
    {
        .instanceName           = "MCU INFRA0",

        .handler                = TOG_eventHandler,                   /* TOG event handler */
        .injectFunction         = TOG_injectMCUINFRATimeoutError,     /* TOG inject error */
        .ESMEventNumber         = SDLR_MCU_ESM0_ESM_LVL_EVENT_MCU_TIMEOUT_INFRA0_SAFEG_TRANS_ERR_LVL_0, /* TOG ESM event number */

        .doneFlag               = false,                 /* Initialize done flag */
        .timeoutValue           = 0x10000U,              /* timeout value */
        .intSrcBitmap           = (SDL_TOG_INTRSRC_TRANSACTION_TIMEOUT |
                                   SDL_TOG_INTRSRC_UNEXPECTED_RESPONSE),

    },

    /* MCU_FW1 */
    {
        .instanceName           = "MCU FW1",

        .handler                = TOG_eventHandler,       /* TOG event handler */
        .injectFunction         = TOG_injectESMError,     /* TOG inject ESM error */
        .ESMEventNumber         = SDLR_MCU_ESM0_ESM_LVL_EVENT_MCU_TIMEOUT_FW1_SAFEG_TRANS_ERR_LVL_0, /* TOG ESM event number */

        .doneFlag               = false,                  /* Initialize done flag */
        .timeoutValue           = 0x10000U,               /* timeout value */
        .intSrcBitmap           = 0x0U,

    },

    /* MCU_64B2 */
    {
        .instanceName           = "MCU 64B2",

        .handler                = TOG_eventHandler,                   /* TOG event handler */
        .injectFunction         = TOG_injectMCU64B2TimeoutError,     /* TOG inject error */
        .ESMEventNumber         = SDLR_MCU_ESM0_ESM_LVL_EVENT_MCU_TIMEOUT_64B2_TRANS_ERR_LVL_0, /* TOG ESM event number */

        .doneFlag               = false,                 /* Initialize done flag */
        .timeoutValue           = 0x10000U,              /* timeout value */
        .intSrcBitmap           = (SDL_TOG_INTRSRC_TRANSACTION_TIMEOUT |
                                   SDL_TOG_INTRSRC_UNEXPECTED_RESPONSE),

    },

    /* WKUP INFRA0 */
    {
        .instanceName           = "WKUP INFRA0",

        .handler                = TOG_eventHandler,       /* TOG event handler */
        .injectFunction         = TOG_injectESMError,     /* TOG inject ESM error */
        .ESMEventNumber         = SDLR_WKUP_ESM0_ESM_LVL_EVENT_WKUP_TIMEOUT_INFRA0_SAFEG_TRANS_ERR_LVL_0, /* TOG ESM event number */

        .doneFlag               = false,                  /* Initialize done flag */
        .timeoutValue           = 0x10000U,               /* timeout value */
        .intSrcBitmap           = 0x0U,

    },

};

void TOG_injectESMError(uint32_t instanceIndex)
{
    /* Do transaction that will exercise TOG */
    SDL_ESM_setIntrStatusRAW(MCU_ESM_BASE, TOG_TestHandleArray[instanceIndex].ESMEventNumber);
}

void TOG_injectMCU64B2TimeoutError(uint32_t instanceIndex)
{
    SDL_TOG_config cfg;
    SDL_TOG_Inst instance;
    instance = instanceIndex;
    cfg.cfgCtrl = SDL_TOG_CFG_TIMEOUT;
    int32_t status;
    int i;

    /* Injecting error can result in a Data abort, so disable temporarily */
    disableABORT();

    /* Call SDL API to set smaller timeout to trigger error */
    cfg.timeoutVal = 1u;
    status = SDL_TOG_init(instance, &cfg);
    if (status != SDL_PASS)
    {
        UART_printf("   Inject SDL_TOG_init TimeoutVal Failed \n");
        /* Assert */
    }

    /* Do something to trigger transaction through the Gasket */
    for (i=0; i< 256; i++)
        gTestMSMCLocation[i] = 1U;

    /* Call SDL API to set configure back to original timeout value */
    cfg.timeoutVal = TOG_TestHandleArray[instanceIndex].timeoutValue;
    status = SDL_TOG_init(instance, &cfg);
    if (status != SDL_PASS)
    {
        UART_printf("   Configure back SDL_TOG_init TimeoutVal Failed \n");
        /* Assert */
    }

    /* Enable back Abort */
    enableABORT();
}

void TOG_injectMCUINFRATimeoutError(uint32_t instanceIndex)
{
    SDL_TOG_Inst instance;
    SDL_TOG_config cfg;
    instance = instanceIndex;
    cfg.cfgCtrl = SDL_TOG_CFG_TIMEOUT;
    int32_t status;
    volatile esmRevisionId_t esmRevisionId;

    /* Injecting error can result in a Data abort, so disable temporarily */
    disableABORT();

    /* Call SDL API to set smaller timeout to trigger error */
    cfg.timeoutVal = 1u;
    status = SDL_TOG_init(instance, &cfg);
    if (status != SDL_PASS)
    {
        UART_printf("   Inject SDL_TOG_init TimeoutVal Failed \n");
        /* Assert */
    }

    /* Access Main ESM to trigger transaction through the Gasket */
    (void)SDL_ESM_getRevisionId(ESM_CFG_BASE, (esmRevisionId_t *)&esmRevisionId);

    /* Call SDL API to set configure back to original timeout value */
    cfg.timeoutVal = TOG_TestHandleArray[instanceIndex].timeoutValue;
    status = SDL_TOG_init(instance, &cfg);
    if (status != SDL_PASS)
    {
        UART_printf("   Configure back SDL_TOG_init TimeoutVal Failed \n");
        /* Assert */
    }

    /* Enable back Abort */
    enableABORT();
}
/* Nothing past this point */
