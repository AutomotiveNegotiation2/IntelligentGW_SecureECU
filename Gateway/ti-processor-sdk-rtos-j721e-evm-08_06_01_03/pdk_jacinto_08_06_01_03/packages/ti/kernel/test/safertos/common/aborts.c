/*
 *  Copyright ( C ) 2022 Texas Instruments Incorporated
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
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES ( INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION ) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  ( INCLUDING NEGLIGENCE OR OTHERWISE ) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "SafeRTOS_API.h"
#include "aborts.h"

/*-----------------------------------------------------------------------------
 * Private Function Declarations.
 *---------------------------------------------------------------------------*/

static void prvAbortDelay( void );

#if defined (BUILD_MCU)
/*-----------------------------------------------------------------------------
 * External Functions (declared in utilsasm_r5f.asm)
 *---------------------------------------------------------------------------*/

portUInt32Type ulGetDataFaultStatusRegister( void );
portUInt32Type ulGetDataFaultAddressRegister( void );
portUInt32Type ulGetInstructionFaultStatusRegister( void );
portUInt32Type ulGetInstructionFaultAddressRegister( void );

/*-----------------------------------------------------------------------------
 * Function Definitions
 *---------------------------------------------------------------------------*/
#if !defined (SOC_J7200)
void vApplicationDataAbortHook( void )
#else
void vDataAbort( void )
#endif
{
    volatile portUInt32Type ulDataFaultStatusReg;
    volatile portUInt32Type ulDataFaultAddressReg;

    ulDataFaultStatusReg = ulGetDataFaultStatusRegister();
    ulDataFaultAddressReg = ulGetDataFaultAddressRegister();

    for( ;; )
    {
        prvAbortDelay();
    }
}
/*---------------------------------------------------------------------------*/

#if !defined (SOC_J7200)
void vApplicationPrefetchAbortHook( void )
#else
void vPrefetchAbort( void )
#endif
{
    volatile portUInt32Type ulInstrFaultStatusReg;
    volatile portUInt32Type ulInstrFaultAddressReg;

    ulInstrFaultStatusReg = ulGetInstructionFaultStatusRegister();
    ulInstrFaultAddressReg = ulGetInstructionFaultAddressRegister();

    for( ;; )
    {
        prvAbortDelay();
    }
}
/*---------------------------------------------------------------------------*/
#if !defined (SOC_J7200)
void vApplicationUndefAbortHook( void )
#else
void vUndefAbort( void )
#endif
{
    for( ;; )
    {
        prvAbortDelay();
    }
}
/*---------------------------------------------------------------------------*/
#endif

void vApplicationAbort( void )
{
    for( ;; )
    {
        prvAbortDelay();
    }
}
/*---------------------------------------------------------------------------*/

void vStartupAbort( void )
{
    for( ;; )
    {
        prvAbortDelay();
    }
}
/*---------------------------------------------------------------------------*/

static void prvAbortDelay( void )
{
    const portUnsignedBaseType uxDelayTime = 3500000;
    volatile portUnsignedBaseType uxCount = 0;

    for( uxCount = 0; uxCount < uxDelayTime; uxCount++ )
    {
        ; /* Do nothing. */
    }
}
/*---------------------------------------------------------------------------*/
