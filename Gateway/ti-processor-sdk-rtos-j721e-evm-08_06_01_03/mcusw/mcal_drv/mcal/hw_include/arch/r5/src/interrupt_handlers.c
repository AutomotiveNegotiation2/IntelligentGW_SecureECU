/*
 *  Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   interrupt.c
 *
 *  \brief  Interrupt related common APIs for Nonos and FreeRTOS.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <interrupt.h>
#include <lld_arm_r5.h>
#include <lld_vim.h>
#include "interrupt_priv.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* None */


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

__attribute__((interrupt("IRQ")))    void masterIsr(void);
__attribute__((interrupt("UDEF")))   void undefInstructionExptnHandler(void);
__attribute__((interrupt("SWI")))     void swIntrExptnHandler(void);
__attribute__((interrupt("PABT")))   void prefetchAbortExptnHandler(void);
__attribute__((interrupt("DABT")))   void dataAbortExptnHandler(void);
__attribute__((interrupt("IRQ")))     void irqExptnHandler(void);
__attribute__((interrupt("FIQ")))     void fiqExptnHandler(void);



#ifdef __cplusplus
#pragma CODE_STATE (32)
#else
#pragma CODE_STATE (masterIsr,32)
#endif  /* #ifdef __cplusplus */
void masterIsr(void)
{
    IntrFuncPtr        fxnPtr;
    volatile uint32_t  intNum;

    /* Process a pending FIQ interrupt before a pending IRQ interrupt */
    if( ( CSL_vimGetActivePendingIntr( (CSL_vimRegs *)(uintptr_t)gVimBaseAddr, CSL_VIM_INTR_MAP_FIQ, (uint32_t *)&intNum, (uint32_t *)0 ) == 0 )       ||
        ( CSL_vimGetActivePendingIntr( (CSL_vimRegs *)(uintptr_t)gVimBaseAddr, CSL_VIM_INTR_MAP_IRQ, (uint32_t *)&intNum, (uint32_t *)0 ) == 0 ) )
    {
        /* Clear pulse-type interrupt before calling ISR */
        if( intrSrcType[intNum] == (uint32_t)CSL_VIM_INTR_TYPE_PULSE )
        {
            CSL_vimClrIntrPending( (CSL_vimRegs *)(uintptr_t)gVimBaseAddr, intNum );
        }
        /* Call ISR */
        if( fxnArray[intNum] != NULL )
        {
            fxnPtr = fxnArray[intNum];
            fxnPtr(argArray[intNum]);
        }
        /* Clear level-type interrupt after calling ISR */
        if( intrSrcType[intNum] == (uint32_t)CSL_VIM_INTR_TYPE_LEVEL )
        {
            CSL_vimClrIntrPending( (CSL_vimRegs *)(uintptr_t)gVimBaseAddr, intNum );
        }
        /* Acknowledge interrupt servicing */
        CSL_vimAckIntr( (CSL_vimRegs *)(uintptr_t)gVimBaseAddr, (CSL_VimIntrMap)intrMap[intNum] );
    }
}


#ifdef __cplusplus
#pragma CODE_STATE (32)
#pragma FUNC_EXT_CALLED()
#else
#pragma FUNC_EXT_CALLED(undefInstructionExptnHandler)
#pragma CODE_STATE (undefInstructionExptnHandler,32)
#endif  /* #ifdef __cplusplus */
void undefInstructionExptnHandler(void)
{
    /* Call registered call back */
    if (gExptnHandlers.udefExptnHandler != (exptnHandlerPtr)NULL)
    {
        gExptnHandlers.udefExptnHandler(gExptnHandlers.udefExptnHandlerArgs);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

#ifdef __cplusplus
#pragma CODE_STATE (32)
#pragma FUNC_EXT_CALLED()
#else
#pragma FUNC_EXT_CALLED(swIntrExptnHandler)
#pragma CODE_STATE (swIntrExptnHandler,32)
#endif  /* #ifdef __cplusplus */
void swIntrExptnHandler(void)
{
    /* Call registered call back */
    if (gExptnHandlers.swiExptnHandler != (exptnHandlerPtr)NULL)
    {
        gExptnHandlers.swiExptnHandler(gExptnHandlers.swiExptnHandlerArgs);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

#ifdef __cplusplus
#pragma CODE_STATE (32)
#pragma FUNC_EXT_CALLED()
#else
#pragma CODE_STATE (prefetchAbortExptnHandler,32)
#pragma FUNC_EXT_CALLED(prefetchAbortExptnHandler)
#endif  /* #ifdef __cplusplus */
void prefetchAbortExptnHandler(void)
{
    /* Call registered call back */
    if (gExptnHandlers.pabtExptnHandler != (exptnHandlerPtr)NULL)
    {
        gExptnHandlers.pabtExptnHandler(gExptnHandlers.pabtExptnHandlerArgs);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

#ifdef __cplusplus
#pragma CODE_STATE (32)
#pragma FUNC_EXT_CALLED()
#else
#pragma CODE_STATE (dataAbortExptnHandler,32)
#pragma FUNC_EXT_CALLED(dataAbortExptnHandler)
#endif  /* #ifdef __cplusplus */
void dataAbortExptnHandler(void)
{
    /* Call registered call back */
    if (gExptnHandlers.dabtExptnHandler != (exptnHandlerPtr)NULL)
    {
        gExptnHandlers.dabtExptnHandler(gExptnHandlers.dabtExptnHandlerArgs);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

#ifdef __cplusplus
#pragma CODE_STATE (32)
#pragma FUNC_EXT_CALLED()
#else
#pragma CODE_STATE (irqExptnHandler,32)
#pragma FUNC_EXT_CALLED(irqExptnHandler)
#endif  /* #ifdef __cplusplus */
void irqExptnHandler(void)
{
    /* Call registered call back */
    if (gExptnHandlers.irqExptnHandler != (exptnHandlerPtr)NULL)
    {
        gExptnHandlers.irqExptnHandler(gExptnHandlers.irqExptnHandlerArgs);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

#ifdef __cplusplus
#pragma CODE_STATE (32)
#pragma FUNC_EXT_CALLED()
#else
#pragma CODE_STATE (fiqExptnHandler,32)
#pragma FUNC_EXT_CALLED(fiqExptnHandler)

#endif  /* #ifdef __cplusplus */
void fiqExptnHandler(void)
{
    /* Call registered call back */
    if (gExptnHandlers.fiqExptnHandler != (exptnHandlerPtr)NULL)
    {
        gExptnHandlers.fiqExptnHandler(gExptnHandlers.fiqExptnHandlerArgs);
    }
    else
    {
        /* Go into an infinite loop.*/
        volatile uint32_t loop = 1U;
        while (1U == loop)
        {
            ;
        }
    }
}

/********************************* End of file ******************************/


