/*
 * Copyright (c) 2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "sbl_amp_multicore_sections.h"
#include "sbl_print.h"

void sbl_puts_itoa(unsigned int num) {
    volatile char *putsBuffer = (volatile char *)PUTS_BUFFER;
    putsBuffer[1] = '\0';

    if (!num) {
        /* BASE CASE */
    } else {
        sbl_puts_itoa(num/10);
        putsBuffer[0] = (num % 10) + 0x30;
        sbl_puts((char*)putsBuffer);
    }
}

int sblTestmain(void)
{
    volatile int *pokeMemAddr = (volatile int *)POKE_MEM_ADDR;
    volatile int *bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
    volatile int *startCheckAddr = (volatile int *)START_CHECK_ADDR;
    volatile int *coreCounterAddr = (volatile int *)CORE_COUNTER_ADDR;
    volatile int *semaphoreAddr = (volatile int *)SEMAPHORE_ADDR;

    volatile int num_cores_booted = 0, boot_delay=1000, core_count = 0, pend_num = 0;

    // if we have run before, someone
    // reset the system, dont print message
    if (*pokeMemAddr != 0xC0DEBABE)
    {
        // Check if we have initialized our memory, if not then we need to set up counters etc
        // If we are the first core, then we can go ahead and execute without pending
        if (*startCheckAddr != STARTED) {
            *startCheckAddr = STARTED;
            *coreCounterAddr = 1;
            core_count = 1;
            pend_num = SEMAPHORE + core_count;
            *semaphoreAddr = pend_num;
        } else { // Memory already initialized, "pend" on core boot order
            while (boot_delay--) { } // ensure we don't run this branch before memory initialized
            core_count = ++(*coreCounterAddr);
            pend_num = SEMAPHORE + core_count;

            // Wait for our ticket to get called
            while (*semaphoreAddr != pend_num) { }
        }

        // Poke memory
        *pokeMemAddr = 0xC0DEBABE;

        // log completion
        sbl_puts(CORE_NAME);
        sbl_puts (" running: boot order #");
        sbl_puts_itoa(core_count);
        sbl_puts ("\n\r");

        // Release the lock
        (*semaphoreAddr)++;
    }

    // Check if all cores have run by checking flags
    // left in MSMC by each cores testcase
    #if defined(SOC_J784S4)
        while (bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_3)
        {
            if (*bootFlagAddr == 0xC0DEBABE)
            {
                num_cores_booted++;
            }

            bootFlagAddr += 0x400;
        }
    #else
        while (bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_1)
        {
            if (*bootFlagAddr == 0xC0DEBABE)
            {
                num_cores_booted++;
            }

            bootFlagAddr += 0x800;
        }
    #endif

    if (num_cores_booted == SBL_AMP_TEST_NUM_BOOT_CORES)
    {
        sbl_puts(CORE_NAME);
        sbl_puts(" reports: All tests have passed\n\r");

        // Clean up pokemem flags for the next run
        #if defined(SOC_J784S4)
            for (bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
                bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_3;
                bootFlagAddr += 0x400)
            {
                *bootFlagAddr = 0xFEEDFACE;
            }
        #else
            for (bootFlagAddr = (volatile int *)POKE_MEM_ADDR_MCU1_0;
                bootFlagAddr <= (int *)POKE_MEM_ADDR_MPU2_1;
                bootFlagAddr += 0x800)
            {
                *bootFlagAddr = 0xFEEDFACE;
            }
        #endif
    }

    return 0XFEEDFACE;
}

