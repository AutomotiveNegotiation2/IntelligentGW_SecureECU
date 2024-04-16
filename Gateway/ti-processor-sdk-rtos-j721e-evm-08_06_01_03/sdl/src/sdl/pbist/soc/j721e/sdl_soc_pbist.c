/**
 * @file  sdl_soc_pbist.c
 *
 * @brief
 *  SDL implementation file for the SoC-specific pbist implementations.
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

#include <stdint.h>
#include <sdl_types.h>
#include <src/sdl/sdl_pbist.h>
#include <src/sdl/pbist/sdl_pbist_priv.h>
#include <soc.h>

/**
 *  \brief Maximum number of input events supported by CLEC. This is just the
 *  maximum registers supported for programming. The actual event supported
 *  depends on the SOC.
 */
#define SDL_CLEC_MAX_EVT_IN             (2047U)

#define ECR_CLR_VAL                     (1U)

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* CLEC PID register */
    volatile uint8_t  Resv_1000[4092];
    volatile uint32_t MRR;
    volatile uint8_t  RESV_3000[8188];
    volatile uint32_t ESR;
    volatile uint8_t  Resv_4000[4092];
    volatile uint32_t ECR;
    volatile uint8_t  Resv_C000[32764];
    volatile uint32_t GELRS;                     /* Global Event Lock register for secure claims */
    volatile uint8_t  Resv_D000[4092];
    volatile uint32_t GELRNS;                    /* Global Event Lock register for non-secure claims */
    volatile uint8_t  Resv_12284[12284];
} SDL_PBIST_CLEC_EVTRegs_GLOBAL;

typedef struct {
    SDL_PBIST_CLEC_EVTRegs_GLOBAL CFG[2047]; /* This block will contain all
                                              * registers only CFG[0] will
                                              * contain the PID, GELRS and
                                              * GELRNS registes*/
} SDL_PBIST_CLEC_EVTRegs;

/*
 * Note: the order for the below must match order of SDL_PBIST_inst
 */
static SDL_pbistInstInfo SDL_PBIST_InstInfoArray[SDL_PBIST_NUM_INSTANCES] =
{
    /* MCU R5F Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_MCU_PBIST0_BASE,
        /*
         * Golden vectors not currently supported running from MCU core because
         * this will be self destructive. Below select memory which is guaranteed
         * not to be utilized can be run.
         */
        .numPBISTRuns        = 1u,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                /* NOTE: As the MCU R5f is running this code override bit cannot be set to enable all memory test */
                .algorithmsBitMap   = 0x00002000u,          /* Choose Algorithm 14 */
                .memoryGroupsBitMap = 0x0080000000000000u,  /* Choose ADC RAM */
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },
        .PBISTNegConfigRun =
        {
            .CA0   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_MCU_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_MCU_PBIST0_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },

    /* MCU Pulsar Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_MCU_PBIST1_BASE,
        .numPBISTRuns        = SDL_MCU_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_MCU_PBIST1_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap */
                /* NOTE: As the MCU R5f is running this code override bit cannot be set to enable all memory test */
                .memoryGroupsBitMap = SDL_MCU_PBIST1_MEM_BITMAP_0,    /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value       */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_MCU_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_MCU_PBIST1_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* Main Pulsar Instance 0 */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST9_BASE, /* PBIST9: Main R5F 0 */
        .numPBISTRuns        = SDL_PBIST9_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                /* NOTE: override set to 1 is not functional currently */
                .algorithmsBitMap   = SDL_PBIST9_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST9_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST9_FAIL_INSERTION_TEST_VECTOR_RAMT,
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST9_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* Main Pulsar Instance 1 */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST10_BASE, /* PBIST10: Main MCU 1 */
        .numPBISTRuns        = SDL_PBIST10_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                /* NOTE: override set to 1 is not functional currently */
                .algorithmsBitMap   = SDL_PBIST10_ALGO_BITMAP_0,  /* Choose recommended Algo bitmap */
                .memoryGroupsBitMap = SDL_PBIST10_MEM_BITMAP_0,   /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U,        /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST10_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST10_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* C7X Instance */
    {
        .PBISTRegsHiAddress  = SDL_COMPUTE_CLUSTER0_C71SS0_PBIST_BASE,
        .pPBISTRegs          = (SDL_pbistRegs *)NULL,
        .numPBISTRuns        = SDL_C71SS0_PBIST_WRAP_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C71SS0_PBIST_WRAP_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap */
                .memoryGroupsBitMap = SDL_C71SS0_PBIST_WRAP_MEM_BITMAP_0,    /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U,                  /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_C71SS0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = 0x0u,
        .clecInputEvt           = SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* A72 Instance */
    {
        .PBISTRegsHiAddress  = SDL_COMPUTE_CLUSTER0_A72SS0_PBIST0_BASE,
        .pPBISTRegs          = (SDL_pbistRegs *)NULL,
        .numPBISTRuns        = SDL_A72SS0_CORE0_PBIST_WRAP_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_A72SS0_CORE0_PBIST_WRAP_ALGO_BITMAP_0,  /* Choose recommended Algo bitmap */
                .memoryGroupsBitMap = SDL_A72SS0_CORE0_PBIST_WRAP_MEM_BITMAP_0,   /* Choose recommended mem bitmap  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                .algorithmsBitMap   = 0x0u,
                .memoryGroupsBitMap = 0x0u,
                .scrambleValue      = 0x0u,
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_A72SS0_CORE0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = 0x0u,
        .clecInputEvt           = SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_8,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* VPAC Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST3_BASE,
        .numPBISTRuns        = SDL_PBIST3_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            /* Golden Vector Part 1 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST3_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST3_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U,    /* Scramble Value */
            },
            /* Golden Vector Part 2 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST3_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST3_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U,       /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST3_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST3_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* DMPAC Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST1_BASE,
        .numPBISTRuns        = SDL_PBIST1_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            /* Golden Vector Part 1 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   =   SDL_PBIST1_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST1_MEM_BITMAP_0,      /* Choose recommended mem bitmap 0 */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            /* Golden Vector Part 2 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   =   SDL_PBIST1_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST1_MEM_BITMAP_1,      /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U,   /* Scramble Value */
            },
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST1_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST1_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* NAVSS Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST7_BASE,
        .numPBISTRuns        = SDL_PBIST7_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            /* Golden Vector Part 1 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST7_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST7_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
            },
            /* Golden Vector Part 2 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST7_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST7_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST7_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST7_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* HC Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST5_BASE,
        .numPBISTRuns        = SDL_PBIST5_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            /* Golden Vector Part 1 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST5_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST5_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
            },
            /* Golden Vector Part 2 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST5_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST5_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1 */
                .scrambleValue      = 0xFEDCBA9876543210U,  /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST5_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST5_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* C66X Instance 0 */
    {
        .PBISTRegsHiAddress  = SDL_C66SS0_VBUSP_CFG_PBISTCFG_BASE,
        .pPBISTRegs          = (SDL_pbistRegs *)NULL,
        .numPBISTRuns        = SDL_C66SS0_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {

            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C66SS0_PBIST0_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_C66SS0_PBIST0_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C66SS0_PBIST0_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_C66SS0_PBIST0_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xDCBA9876543210FEU, /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_C66SS0_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_C66SS0_PBIST0_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* C66X Instance 1 */
    {
        .PBISTRegsHiAddress  = SDL_C66SS1_VBUSP_CFG_PBISTCFG_BASE,
        .pPBISTRegs          = (SDL_pbistRegs *)NULL,
        .numPBISTRuns        = SDL_C66SS1_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C66SS1_PBIST0_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_C66SS1_PBIST0_MEM_BITMAP_0,    /* Choose recommended mem bitmap  0 */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_C66SS1_PBIST0_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_C66SS1_PBIST0_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xDCBA9876543210FEU, /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_C66SS1_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_C66SS1_PBIST0_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* Main Infrastructure Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST6_BASE,
        .numPBISTRuns        = SDL_PBIST6_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            /* Golden Vector Part 1 */
            {
                .override           = 0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST6_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST6_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            /* Golden Vector Part 2 */
            {
                .override           = 0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST6_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST6_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1 */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST6_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST6_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* MSMC Instance */
    {
        .PBISTRegsHiAddress  = SDL_COMPUTE_CLUSTER0_MSMC_PBIST_BASE,
        .pPBISTRegs          = (SDL_pbistRegs *)NULL,
        .numPBISTRuns        = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            /* Golden Vector Part 1 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            /* Golden Vector Part 2 */
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            }
        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_COMPUTE_CLUSTER0_PBIST_WRAP_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_PBIST_WRAP_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* Encoder Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST2_BASE,
        .numPBISTRuns        = SDL_PBIST2_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST2_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST2_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST2_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST2_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },

        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST2_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST2_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* Decoder Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_PBIST0_BASE,
        .numPBISTRuns        = SDL_PBIST0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST0_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST0_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST0_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST0_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value          */
            },

        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST0_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* DSS Instance */
    {
        .PBISTRegsHiAddress  = SDL_COMPUTE_CLUSTER0_MSMC_PBIST_BASE,
        .pPBISTRegs          = (SDL_pbistRegs *)NULL,
        .numPBISTRuns        = SDL_PBIST4_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST4_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_PBIST4_MEM_BITMAP_0,    /* Choose recommended mem bitmap  0 */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_PBIST4_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_PBIST4_MEM_BITMAP_1,    /* Choose recommended mem bitmap  1 */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value */
            },

        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_PBIST4_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_PBIST4_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
    /* GPU Instance */
    {
        .PBISTRegsHiAddress  = 0u,
        .pPBISTRegs          = (SDL_pbistRegs *)SDL_GPU0_PBIST_CFG_BASE,
        .numPBISTRuns        = SDL_GPU0_DFT_PBIST_0_NUM_TEST_VECTORS,
        .PBISTConfigRun = {
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_GPU0_DFT_PBIST_0_ALGO_BITMAP_0,   /* Choose recommended Algo bitmap 0 */
                .memoryGroupsBitMap = SDL_GPU0_DFT_PBIST_0_MEM_BITMAP_0,    /* Choose recommended mem bitmap 0  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value        */
            },
            {
                .override           = 0x0u,
                /* Override bit set to 0 to use memoryGroupsBitMap & algorithmsBitMap */
                .algorithmsBitMap   = SDL_GPU0_DFT_PBIST_0_ALGO_BITMAP_1,   /* Choose recommended Algo bitmap 1 */
                .memoryGroupsBitMap = SDL_GPU0_DFT_PBIST_0_MEM_BITMAP_1,    /* Choose recommended mem bitmap 1  */
                .scrambleValue      = 0xFEDCBA9876543210U, /* Scramble Value          */
            },

        },
        .PBISTNegConfigRun = {
            .CA0   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CA0,
            .CA1   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CA1,
            .CA2   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CA2,
            .CA3   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CA3,
            .CL0   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CL0,
            .CL1   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CL1,
            .CL2   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CL2,
            .CL3   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CL3,
            .CMS   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CMS,
            .CSR   = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_CSR,
            .I0    = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_I0,
            .I1    = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_I1,
            .I2    = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_I2,
            .I3    = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_I3,
            .RAMT  = SDL_GPU0_DFT_PBIST_0_FAIL_INSERTION_TEST_VECTOR_RAMT
        },
        .interruptNumber        = SDLR_MCU_R5FSS0_CORE0_INTR_GPU0_DFT_PBIST_0_DFT_PBIST_CPU_0,
        .clecInputEvt           = 0x0,
        .doneFlag               = PBIST_NOT_DONE
    },
};

SDL_pbistInstInfo * SDL_PBIST_getInstInfo(SDL_PBIST_inst instance)
{
    SDL_pbistInstInfo *pInfo = NULL;

    if ((uint32_t)instance < SDL_PBIST_NUM_INSTANCES)
    {
        pInfo = &SDL_PBIST_InstInfoArray[instance];
    }

    return pInfo;
}

#define SDL_PBIST_MAX_CLEC_EVTS 4U

typedef struct {
    uint32_t outputEvt;
    uint32_t intNum;
} sdlClecEvtMap;

sdlClecEvtMap clecLookupTable[SDL_PBIST_MAX_CLEC_EVTS] =
{
    {SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_8,
     SDLR_MCU_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_CLEC_SOC_EVENTS_OUT_LEVEL_8},
    {SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_9,
     SDLR_MCU_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_CLEC_SOC_EVENTS_OUT_LEVEL_9},
    {SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12,
     SDLR_MCU_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_CLEC_SOC_EVENTS_OUT_LEVEL_12},
    {SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_13,
     SDLR_MCU_R5FSS0_CORE0_INTR_COMPUTE_CLUSTER0_CLEC_SOC_EVENTS_OUT_LEVEL_13}
};

uint32_t SDL_PBIST_translateClecToIntr(uint32_t outputEvt)
{
    uint32_t intNum = 0;
    uint32_t i;

    for (i = 0; i < SDL_PBIST_MAX_CLEC_EVTS; i++)
    {
        if (outputEvt == clecLookupTable[i].outputEvt)
        {
            intNum = clecLookupTable[i].intNum;
            break;
        }
    }

    return intNum;
}

static void SDL_PBIST_clecClearEvent(SDL_PBIST_CLEC_EVTRegs *pRegs, uint32_t evtNum)
{
    uint32_t    regVal;

    /* ECR is a write-only register. When written value of 0x1
     * it will clear the event. So write 0x1. */
    regVal = ECR_CLR_VAL;
    SDL_REG32_WR(&pRegs->CFG[evtNum].ECR, regVal);

    return;
}

void SDL_PBIST_eventHandler( uint32_t instanceId)
{
    if (instanceId == (uint32_t) SDL_PBIST_INST_C7X)
    {
        /* Clear C7x PBIST interrupt event in CLEC */
        SDL_PBIST_clecClearEvent((SDL_PBIST_CLEC_EVTRegs *)SDL_COMPUTE_CLUSTER0_CLEC_REGS_BASE,
                       SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12);
    }
    if (instanceId == (uint32_t) SDL_PBIST_INST_A72)
    {
        /* Clear A72 PBIST interrupt event in CLEC*/
        SDL_PBIST_clecClearEvent((SDL_PBIST_CLEC_EVTRegs *)SDL_COMPUTE_CLUSTER0_CLEC_REGS_BASE,
                       SDLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_8);
    }

    SDL_PBIST_InstInfoArray[instanceId].doneFlag = PBIST_DONE;

    return;
}

static void SDL_PBIST_postCheckResult(uint32_t postStatMmrRegVal,
                                      SDL_PBIST_hwpostInst instance,
                                      bool *pResult)
{
    uint32_t mask = 0xFFFFFFFFu;
    (void)instance;

    /* Only one instance supported for J721E: SDL_PBIST_HWPOST_INST_MCU */
    mask = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_PBIST_FAIL_MASK;

    if ((postStatMmrRegVal & mask) == ((uint32_t)0x00000000u))
    {
        *pResult = (bool)true;
    }
    else
    {
        *pResult = (bool)false;
    }

    return;
}

static void SDL_PBIST_isPostPbistTimeout(uint32_t postStatMmrRegVal,
                                         SDL_PBIST_hwpostInst instance,
                                         bool *pIsTimedOut)
{
    uint32_t shift;
    (void)instance;

    /* Only one instance supported for J721E: SDL_PBIST_HWPOST_INST_MCU */
    shift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_PBIST_TIMEOUT_SHIFT;

    *pIsTimedOut = (((postStatMmrRegVal >> shift) & 0x1u) == 0x1u) ? (bool)true : (bool)false;

    return;
}

static void SDL_PBIST_isPostPbistDone(uint32_t postStatMmrRegVal,
                                      SDL_PBIST_hwpostInst instance,
                                      bool *pIsDone)
{
    uint32_t shift;
    (void)instance;

    /* Only one instance supported for J721E: SDL_PBIST_HWPOST_INST_MCU */
    shift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_PBIST_DONE_SHIFT;

    *pIsDone = (((postStatMmrRegVal >> shift) & 0x1u) == 0x1u) ? (bool)true : (bool)false;

    return;
}

static void SDL_PBIST_runPostPbistCheck(SDL_PBIST_hwpostInst instance, SDL_PBIST_postStatus *pPostStatus)
{
    uint32_t postRegVal;
    bool     PBISTResult;

    /* Get PBIST register space Pointer */
    *pPostStatus = SDL_PBIST_POST_COMPLETED_SUCCESS;

    /* Read HW POST status register */
    postRegVal = SDL_REG32_RD(SDL_WKUP_CTRL_MMR0_CFG0_BASE +
                              SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT);

    /* Check if HW POST PBIST was performed */
    SDL_PBIST_isPostPbistDone(postRegVal, instance, &PBISTResult);

    if (PBISTResult != (bool) true)
    {
        /* HW POST: PBIST not completed, check if it timed out */
        SDL_PBIST_isPostPbistTimeout(postRegVal,
                                     instance,
                                     &PBISTResult);
        if (PBISTResult != (bool) true)
        {
            /* HW POST: PBIST was not performed at all on this device
             * for this core */
            *pPostStatus = SDL_PBIST_POST_NOT_RUN;
        }
        else
        {
            /* HW POST: PBIST was attempted but timed out for this section */
            *pPostStatus = SDL_PBIST_POST_TIMEOUT;
        }
    }
    else
    {
        /* HW POST: PBIST was completed on this device, check the result */
        SDL_PBIST_postCheckResult(postRegVal, instance, &PBISTResult);
        if (PBISTResult != (bool) true)
        {
            /* HW POST: PBIST was completed, but the test failed */
            *pPostStatus = SDL_PBIST_POST_COMPLETED_FAILURE;
        }
    } /* if (PBISTResult != (bool) true) */

    return;
}

int32_t SDL_PBIST_getDevicePostStatus(SDL_PBIST_postResult *pResult)
{
    int32_t ret = SDL_PASS;

    /* Get status for MCU */
    SDL_PBIST_runPostPbistCheck(SDL_PBIST_HWPOST_INST_MCU, &pResult->mcuPostStatus);

    return ret;
}
