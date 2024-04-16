/**
 * @file  osal_interface.c
 *
 * @brief
 *  Example implementation of SDL OSAL API.
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

#include <stdio.h>
#include <soc.h>
#include <ti/osal/osal.h>
#include <osal/sdl_osal.h>
#include <ti/csl/csl_rat.h>
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>

pSDL_OSAL_hwipHandle SDL_TEST_registerInterrupt(SDL_OSAL_hwipParams *pParams)
{
    HwiP_Params hwipParams;
    HwiP_Params_init(&hwipParams);

    hwipParams.arg = pParams->callbackArg;

    return HwiP_create(pParams->intNum, pParams->callback, &hwipParams);
}

int32_t SDL_TEST_enableInterrupt(uint32_t intNum)
{
    HwiP_enableInterrupt(intNum);
    return SDL_PASS;
}

int32_t SDL_TEST_disableInterrupt(uint32_t intNum)
{
    HwiP_disableInterrupt(intNum);
    return SDL_PASS;
}

int32_t SDL_TEST_globalDisableInterrupts(uintptr_t *key)
{
    *key = HwiP_disable();
    return SDL_PASS;
}

int32_t SDL_TEST_globalRestoreInterrupts(uintptr_t key)
{
    HwiP_restore(key);
    return SDL_PASS;
}

#define PBIST_RAT_CFG_BASE CSL_MCU_ARMSS_RAT_CFG_BASE
#define PBIST_RAT_REGION_INDEX            0

/* Note that this example provide a single instance of mappedEccRegs (which is RAT-mapped
 * ECC aggregator configuration registers that lie in larger address space than the 32-bit
 * address space on the MCU.  If more ECC aggregator registers need to be mapped, additional
 * global variables are needed for each set of aggregator registers, and SDL_ECC_init() needs
 * to be modified to make SDL_ECC_mapEccAggrReg() calls for each one that needs to be mapped.
 * The expectation is that this mapping will be retained in perpetuity because in order to obtain
 * information about the ECC errors, the ECC Aggregator configuration registers require to be
 * visible from the MCU. */
__attribute((section(".my_aggr_reg"))) uint8_t mappedEccRegs[0x400];
__attribute((section(".my_aggr_reg1"))) uint8_t mappedEccRegs1[0x400];
__attribute((section(".my_aggr_reg2"))) uint8_t mappedEccRegs2[0x400];
__attribute((section(".my_aggr_reg3"))) uint8_t mappedEccRegs3[0x400];
__attribute((section(".my_aggr_reg4"))) uint8_t mappedEccRegs4[0x400];
__attribute((section(".my_aggr_reg5"))) uint8_t mappedEccRegs5[0x400];
__attribute((section(".my_aggr_reg6"))) uint8_t mappedEccRegs6[0x400];
__attribute((section(".my_aggr_reg7"))) uint8_t mappedEccRegs7[0x400];
__attribute((section(".my_aggr_reg8"))) uint8_t mappedEccRegs8[0x400];
__attribute((section(".my_aggr_reg9"))) uint8_t mappedEccRegs9[0x400];

void* SDL_TEST_addrTranslate(uint64_t addr, uint32_t size)
{
    void * ret = (void *)(-1);
    CSL_RatTranslationCfgInfo translationCfg;
    uint32_t transAddr = (uint32_t)(-1);
    uint32_t index = 0;
    bool result;

    if ((addr == SDL_COMPUTE_CLUSTER0_C71SS0_PBIST_BASE) ||
        (addr == SDL_COMPUTE_CLUSTER0_A72SS0_PBIST0_BASE) ||
        (addr == SDL_C66SS0_VBUSP_CFG_PBISTCFG_BASE) ||
        (addr == SDL_C66SS1_VBUSP_CFG_PBISTCFG_BASE) ||
        (addr == SDL_COMPUTE_CLUSTER0_MSMC_PBIST_BASE) ||
        (addr == SDL_COMPUTE_CLUSTER0_MSMC_PBIST_BASE))
    {
        /* Disable RAT translation */
        result = CSL_ratDisableRegionTranslation((CSL_ratRegs *)PBIST_RAT_CFG_BASE,
                                                 PBIST_RAT_REGION_INDEX);
        transAddr = (uint32_t)0x60000000;
        index = PBIST_RAT_REGION_INDEX;
    }
    else
    {
            /* Currently, below aggregators configuration registers can be
             * mapped by this code.  To expand to other aggregators, additional
             * instances of "mappedEccRegs" are needed and should be mapped to
             * those additional aggregators. */
            switch(addr)
            {
                case SDL_COMPUTE_CLUSTER0_MSMC_ECC_AGGR0_BASE:
                    transAddr = (uint32_t)mappedEccRegs;
                    index = 1;
                    break;
                case SDL_COMPUTE_CLUSTER0_MSMC_ECC_AGGR1_BASE:
                    transAddr = (uint32_t)mappedEccRegs1;
            index = 2;
                    break;
                case SDL_COMPUTE_CLUSTER0_MSMC_ECC_AGGR2_BASE:
                    transAddr = (uint32_t)mappedEccRegs2;
            index = 3;
                    break;
                case SDL_COMPUTE_CLUSTER0_A72SS0_COMMON_ECC_AGGR_BASE:
                    transAddr = (uint32_t)mappedEccRegs3;
            index = 4;
                    break;
                case SDL_COMPUTE_CLUSTER0_A72SS0_CORE0_ECC_AGGR_BASE:
                    transAddr = (uint32_t)mappedEccRegs4;
            index = 5;
                    break;
                case SDL_COMPUTE_CLUSTER0_A72SS0_CORE1_ECC_AGGR_BASE:
                    transAddr = (uint32_t)mappedEccRegs5;
            index = 6;
                    break;
                case SDL_COMPUTE_CLUSTER0_ECC_AGGR_VBUS_BASE:
                    transAddr = (uint32_t)mappedEccRegs6;
            index = 7;
                    break;
                case SDL_COMPUTE_CLUSTER0_ECC_AGGR_CTL_BASE:
                    transAddr = (uint32_t)mappedEccRegs7;
            index = 8;
                    break;
                case SDL_COMPUTE_CLUSTER0_ECC_AGGR_CFG_BASE:
                    transAddr = (uint32_t)mappedEccRegs8;
            index = 9;
                    break;
                case SDL_COMPUTE_CLUSTER0_C71SS0_ECC_AGGR_BASE:
                    transAddr = (uint32_t)mappedEccRegs9;
            index = 10;
                    break;
                default:
                    break;
            }
    }

    if (transAddr != (uint32_t)(-1))
    {
        /* Add RAT configuration to access address > 32bit address range */
        translationCfg.translatedAddress = addr;
        translationCfg.sizeInBytes = size;
        translationCfg.baseAddress = transAddr;

        /* Set up RAT translation */
        result = CSL_ratConfigRegionTranslation((CSL_ratRegs *)PBIST_RAT_CFG_BASE,
                                                index, &translationCfg);
        if (result == (bool)true ) {
            ret = (void *)transAddr;
        }
    }

    return ret;
}

SDL_OSAL_Interface osal_interface =
{
    .enableInterrupt = (pSDL_OSAL_interruptFunction) SDL_TEST_enableInterrupt,
    .disableInterrupt = (pSDL_OSAL_interruptFunction) SDL_TEST_disableInterrupt,
    .registerInterrupt = (pSDL_OSAL_registerFunction) SDL_TEST_registerInterrupt,
    .deregisterInterrupt = (pSDL_OSAL_deregisterFunction) HwiP_delete,
    .globalDisableInterrupts = (pSDL_OSAL_globalDisableInterruptsFunction) SDL_TEST_globalDisableInterrupts,
    .globalRestoreInterrupts = (pSDL_OSAL_globalRestoreInterruptsFunction) SDL_TEST_globalRestoreInterrupts,
    .printFxn = (pSDL_OSAL_printFunction) UART_printf,
    .delay = (pSDL_OSAL_delayFunction) Osal_delay,
    .addrTranslate = (pSDL_OSAL_addrTranslateFunction) SDL_TEST_addrTranslate
};

int32_t SDL_TEST_osalInit(void)
{
    SDL_ErrType_t ret = SDL_PASS;

    ret = SDL_OSAL_init(&osal_interface);

    return ret;
}
