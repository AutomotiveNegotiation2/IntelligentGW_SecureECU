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
 *  \file     sdl_pbist_test_cfg.c
 *
 *  \brief    This file contains PBIST test configuration
 *
 *  \details  PBIST Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <sdl_types.h>
#include <soc.h>
#include <src/ip/sdl_ip_pbist.h>
#include <src/sdl/sdl_pbist.h>
#include <ti/csl/csl_clec.h>
#include <ti/csl/csl_cbass.h>
#include <ti/drv/sciclient/sciclient.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/csl/csl_rat.h>
#include <ti/csl/cslr_vpac.h>
#include <ti/csl/cslr_cp_ace.h>

#include "power_seq.h"
#include "pbist_test_cfg.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* This macro defined by default to indicate only a select memory section can
 * be run on the MCU memory PBIST instances to ensure test application running
 * on MCU is not corrupted. */
#define PBIST_MCU_SELECTED_MEMORY

/* Macro to determine if test is excluded because of failure.
 * Set to 0 to disable specific sections. */
#define PBIST_DISABLE_BECAUSE_OF_FAILURE 0

/* ========================================================================== */
/*                            Local function prototypes                       */
/* ========================================================================== */
/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_A72AuxInitRestore(bool init);
int32_t PBIST_VPACAuxInitRestore(bool init);
int32_t PBIST_MainInfraAuxInitRestore(bool init);
int32_t PBIST_decoderAuxInitRestore(bool init);
int32_t PBIST_GPUAuxInitRestore(bool init);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t PBIST_A72AuxDevList[A72_NUM_AUX_DEVICES] =
{
    TISCI_DEV_A72SS0,
};

uint32_t PBIST_MainInfraAuxDevList[MAIN_INFRA_NUM_AUX_DEVICES] =
{
    TISCI_DEV_DEBUGSS_WRAP0,
    TISCI_DEV_MCAN0,
    TISCI_DEV_MCAN1,
    TISCI_DEV_MCAN2,
    TISCI_DEV_MCAN3,
    TISCI_DEV_MCAN4,
    TISCI_DEV_MCAN5,
    TISCI_DEV_MCAN6,
    TISCI_DEV_MCAN7,
    TISCI_DEV_MCAN8,
    TISCI_DEV_MCAN9,
    TISCI_DEV_MCAN10,
    TISCI_DEV_MCAN11,
    TISCI_DEV_MCAN12,
    TISCI_DEV_MCAN13,
    TISCI_DEV_I3C0,
    TISCI_DEV_SA2_UL0,
    TISCI_DEV_CPSW0
};

uint32_t PBIST_MSMCAuxDevList[MSMC_NUM_AUX_DEVICES] =
{
    TISCI_DEV_COMPUTE_CLUSTER0_EN_MSMC_DOMAIN,
    TISCI_DEV_NAVSS0,
    TISCI_DEV_A72SS0,
};

uint32_t PBIST_GPUAuxDevList[GPU_NUM_AUX_DEVICES] =
{
    TISCI_DEV_GPU0,
    TISCI_DEV_GPU0_GPU_0,
};

uint32_t PBIST_DSSAuxDevList[DSS_NUM_AUX_DEVICES] =
{
    TISCI_DEV_DSS0,
    TISCI_DEV_DSS_EDP0,
    TISCI_DEV_CSI_RX_IF0,
    TISCI_DEV_CSI_RX_IF1,
    TISCI_DEV_CSI_TX_IF0,
    TISCI_DEV_CSI_PSILSS0,
    TISCI_DEV_DPHY_RX0,
    TISCI_DEV_DPHY_RX1,
    TISCI_DEV_DPHY_TX0,
    TISCI_DEV_SERDES_10G0,
   /* TODO: Need to check on SERDES8MTO*/
};

PBIST_TestHandle_t PBIST_TestHandleArray[PBIST_MAX_INSTANCE+1] =
{
    /* MCU PBIST - Only select memory guaranteed not to be utilized by this test application
     * can be run, since PBIST changes the memory upon which it is run. */
    {
        .testName               = "MCU PBIST",
        .pbistInst              = SDL_PBIST_INST_MCUR5F0,
        .numPostPbistToCheck    = 1u,
        .tisciPBISTDeviceId     = TISCI_DEV_MCU_PBIST0, /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                   /* No Aux devices */
        .auxInitRestoreFunction = NULL,                 /* Auxilliary init function */
    },
    /* Main R5F 0 */
    {
        .testName               = "Main R5F 0 PBIST",
        .pbistInst              = SDL_PBIST_INST_MAINR5F0,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST9,    /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "Main R5F0 core0",   /* Primary core   */
        .secCoreName            = "Main R5F0 core1",   /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_R5FSS0_CORE0, /* Main R5F core 0 Proc Id */
        .tisciSecProcId         = SCICLIENT_PROC_ID_R5FSS0_CORE1, /* Main R5F core 1 Proc Id */
        .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,   /* Main R5F core 0 Device Id */
        .tisciSecDeviceId       = TISCI_DEV_R5FSS0_CORE1,   /* Main R5F core 1 Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                   /* No Aux devices */
        .auxInitRestoreFunction = NULL,                 /* Auxilliary init function */
    },
    /* Main R5F 1 */
    {
        .testName               = "Main R5F 1 PBIST",
        .pbistInst              = SDL_PBIST_INST_MAINR5F1,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST10,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "Main R5F1 core0",   /* Primary core   */
        .secCoreName            = "Main R5F1 core1",   /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_R5FSS1_CORE0, /* Main R5F core 0 Proc Id */
        .tisciSecProcId         = SCICLIENT_PROC_ID_R5FSS1_CORE1, /* Main R5F core 1 Proc Id */
        .tisciDeviceId          = TISCI_DEV_R5FSS1_CORE0,  /* Main R5F core 0 Device id */
        .tisciSecDeviceId       = TISCI_DEV_R5FSS1_CORE1,  /* Main R5F core 1 Device id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                      /* No Aux devices */
        .auxInitRestoreFunction = NULL,                /* Auxilliary init function */
    },
    /* C7X */
    {
        .testName               = "C7X PBIST",
        .pbistInst              = SDL_PBIST_INST_C7X,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_C71X_0_PBIST_VD,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,               /* Secondary core needed */
        .coreName               = "C7x ",
        .tisciProcId            = SCICLIENT_PROC_ID_C71SS0,  /* C7x Proc Id */
        .tisciDeviceId          = TISCI_DEV_C71SS0,    /* C7x Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                  /* No Aux devices */
        .auxInitRestoreFunction = NULL,                /* Auxilliary init function */
    },
    /* A72 */
    {
        .testName               = "A72 PBIST",
        .pbistInst              = SDL_PBIST_INST_A72,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_COMPUTE_CLUSTER0_PBIST_WRAP, /* Device Id for A72 PBIST */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                /* Secondary core needed */
        .coreName               = "A72 core 0",        /* Primary core   */
        .secCoreName            = "A72 core 1",        /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_A72SS0_CORE0,  /* A72 core 0 Proc Id */
        .tisciSecProcId         = SCICLIENT_PROC_ID_A72SS0_CORE1,  /* A72 core 1 Proc Id */
        .tisciDeviceId          = TISCI_DEV_A72SS0_CORE0,  /* A72 core 0 Device Id */
        .tisciSecDeviceId       = TISCI_DEV_A72SS0_CORE1,  /* A72 core 1 Device Id */
        .coreCustPwrSeqNeeded   = true,                    /* A72 needs custom powerdown sequence steps */
        .numAuxDevices          = A72_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_A72AuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_A72AuxInitRestore, /* Auxilliary init function */
    },
    /* VPAC */
    {
        .testName               = "VPAC PBIST",
        .pbistInst              = SDL_PBIST_INST_VPAC,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST3,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,            /* Secondary core needed */
        .coreName               = "VPAC core",      /* Primary core   */
        .tisciProcId            = 0x0u,             /* No ProcId for VPAC */
        .tisciDeviceId          = TISCI_DEV_VPAC0,  /* VPAC core Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,               /* No Aux devices */
        .auxInitRestoreFunction = PBIST_VPACAuxInitRestore,/* Auxilliary init function */
    },
    /* DMPAC */
    {
        .testName               = "DMPAC PBIST",
        .pbistInst              = SDL_PBIST_INST_DMPAC,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST1,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                       /* Secondary core needed */
        .coreName               = "DMPAC core",               /* Primary core   */
        .secCoreName            = "DMPAC SDE core",           /* Secondary core */
        .tisciProcId            = 0x0u,                       /* No ProcId for DMPAC */
        .tisciSecProcId         = 0x0u,                       /* No Sec ProcId for DMPAC */
        .tisciDeviceId          = TISCI_DEV_DMPAC0,           /* DMPAC Core Device Id */
        .tisciSecDeviceId       = TISCI_DEV_DMPAC0_SDE_0,     /* DMPAC_SDE Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                  /* No Aux devices */
        .auxInitRestoreFunction = NULL,                /* Auxilliary init function */
    },
    /* NAVSS */
    {
        .testName               = "NAVSS PBIST",
        .pbistInst              = SDL_PBIST_INST_NAVSS,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST7,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "NAVSS",              /* Primary core   */
        .tisciProcId            = 0x0u,                 /* No ProcId for NAVSS */
        .tisciDeviceId          = TISCI_DEV_NAVSS0,     /* NAVSS Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                   /* No Aux devices */
        .auxInitRestoreFunction = NULL,                /* Auxilliary init function */
    },
    /* HC */
    {
        .testName               = "HC PBIST",
        .pbistInst              = SDL_PBIST_INST_HC,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST5, /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,            /* Secondary core needed */
        .coreName               = "",               /* No coreName   */
        .tisciProcId            = 0x0u,             /* No ProcId for HC */
        .tisciDeviceId          = 0x0u,             /* No Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,               /* No Aux devices */
        .auxInitRestoreFunction = NULL,             /* Auxilliary init function */
    },
    /* C6X core 0 */
    {
        .testName               = "C6x core 0 PBIST",
        .pbistInst              = SDL_PBIST_INST_C66X0,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_C66SS0_PBIST0,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = false,                           /* Secondary core needed */
        .coreName               = "C6x 0",                         /* Primary core   */
        .tisciProcId            = SCICLIENT_PROC_ID_C66SS0_CORE0,  /* C6x core0 Proc Id */
        .tisciDeviceId          = TISCI_DEV_C66SS0_CORE0,          /* C6x Core 0 Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                  /* No Aux devices */
        .auxInitRestoreFunction = NULL,             /* Auxilliary init function */
    },
    /* C6X core 1 */
    {
        .testName               = "C6x core 1 PBIST",
        .pbistInst              = SDL_PBIST_INST_C66X1,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_C66SS1_PBIST0,   /* PBIST device id  */
        .procRstNeeded          = true,              /* Initialize done flag */
        .secondaryCoreNeeded    = false,              /* Secondary core needed */
        .coreName               = "C6x 1",            /* Primary core   */
        .tisciProcId            = SCICLIENT_PROC_ID_C66SS1_CORE0,  /* C6x core0 Proc Id */
        .tisciDeviceId          = TISCI_DEV_C66SS1_CORE0,          /* C6x Core 0 Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                  /* No Aux devices */
        .auxInitRestoreFunction = NULL,                /* Auxilliary init function */
    },
    /* Main Infra */
    {
        .testName               = "Main Infra PBIST",
        .pbistInst              = SDL_PBIST_INST_MAININFRA,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST6,    /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,               /* Secondary core needed */
        .coreName               = "",                  /* No coreName   */
        .tisciProcId            = 0x0u,                /* No Proc Id needed for Main Intrastructure */
        .tisciDeviceId          = 0x0u,                /* No Device Id needed for Main infrastructure */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = MAIN_INFRA_NUM_AUX_DEVICES,    /* No Aux devices */
        .auxDeviceIdsP          = &PBIST_MainInfraAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_MainInfraAuxInitRestore, /* Auxilliary init function */
    },
    /* MSMC */
    {
        .testName               = "MSMC PBIST",
        .pbistInst              = SDL_PBIST_INST_MSMC,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_COMPUTE_CLUSTER0_PBIST_WRAP,   /* PBIST device id  */
        .procRstNeeded          = true,
        .secondaryCoreNeeded    = true,                    /* Secondary core needed */
        .coreName               = "A72 core 0",            /* Primary core   */
        .secCoreName            = "A72 core 1",            /* Secondary core */
        .tisciProcId            = SCICLIENT_PROC_ID_A72SS0_CORE0, /* A72 core 0 Proc Id */
        .tisciSecProcId         = SCICLIENT_PROC_ID_A72SS0_CORE1, /* A72 core 1 Proc Id */
        .tisciDeviceId          = TISCI_DEV_A72SS0_CORE0,         /* A72 core 0 Device Id */
        .tisciSecDeviceId       = TISCI_DEV_A72SS0_CORE1,         /* A72 core 1 Device Id */
        .coreCustPwrSeqNeeded   = true,
        .numAuxDevices          = MSMC_NUM_AUX_DEVICES,           /* No Aux devices       */
        .auxDeviceIdsP          = &PBIST_MSMCAuxDevList[0],       /* Array of Aux device ids */
        .auxInitRestoreFunction = NULL,                           /* Auxilliary init function */
    },
    /* Encoder */
    {
        .testName               = "Encoder PBIST",
        .pbistInst              = SDL_PBIST_INST_ENCODER,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST2,     /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "Encoder",            /* Primary core          */
        .tisciProcId            = 0x0u,                 /* No ProcId for Encoder */
        .tisciDeviceId          = TISCI_DEV_ENCODER0,   /* Encoder Device Id     */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                   /* No Aux devices        */
        .auxInitRestoreFunction = NULL,                 /* Auxilliary init function */
    },

    /* Decoder */
    {
        .testName               = "Decoder PBIST",
        .pbistInst              = SDL_PBIST_INST_DECODER,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST0,     /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreName               = "Decoder",            /* Primary core          */
        .tisciProcId            = 0x0u,                 /* No ProcId for Decoder */
        .tisciDeviceId          = TISCI_DEV_DECODER0,   /* Device Id             */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                          /* No Aux devices        */
        .auxInitRestoreFunction = PBIST_decoderAuxInitRestore, /* Auxilliary init function */
    },

    /* GPU */
    {
        .testName               = "GPU PBIST",
        .pbistInst              = SDL_PBIST_INST_GPU,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_GPU0_DFT_PBIST_0, /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                      /* Secondary core needed */
        .coreName               = "GPU",                      /* Primary core   */
        .tisciProcId            = 0x0u,                       /* No ProcId for GPU */
        .tisciDeviceId          = TISCI_DEV_GPU0_GPUCORE_0,   /* GPU Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = GPU_NUM_AUX_DEVICES,        /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_GPUAuxDevList[0],    /* Array of Aux device ids */
        .auxInitRestoreFunction = PBIST_GPUAuxInitRestore,    /* Auxilliary init function */
    },
    /* DSS EDP DSI */
    {
        .testName               = "DSS EDP PBIST",
        .pbistInst              = SDL_PBIST_INST_DSS,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_PBIST4,        /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                   /* Secondary core needed */
        .coreName               = "DSS",                   /* Primary core   */
        .tisciProcId            = 0x0u,                    /* No ProcId for MSMC */
        .tisciDeviceId          = TISCI_DEV_DSS_DSI0,      /* DSS Device Id */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = DSS_NUM_AUX_DEVICES,     /* Number of Aux devices   */
        .auxDeviceIdsP          = &PBIST_DSSAuxDevList[0], /* Array of Aux device ids */
        .auxInitRestoreFunction = NULL,                    /* Auxilliary init function */
    },
    /* MCU PULSAR PBIST */
    {
        .testName               = "MCU PULSAR PBIST",
        .pbistInst              = SDL_PBIST_INST_MCUR5F1,
        .numPostPbistToCheck    = 0u,
        .tisciPBISTDeviceId     = TISCI_DEV_MCU_PBIST1, /* PBIST device id  */
        .procRstNeeded          = false,
        .secondaryCoreNeeded    = false,                /* Secondary core needed */
        .coreCustPwrSeqNeeded   = false,
        .numAuxDevices          = 0u,                   /* No Aux devices        */
        .auxInitRestoreFunction = NULL,                 /* Auxilliary init function */
    },

};


/* HW POST-related functions */

int32_t PBIST_isPostPbistTimeout(uint32_t postStatMmrRegVal, bool *pIsTimedOut)
{
    int32_t status = SDL_PASS;

    if (pIsTimedOut == NULL)
    {
        status = SDL_EBADARGS;
    }
    else
    {
        *pIsTimedOut = ((postStatMmrRegVal >>
                         SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_PBIST_TIMEOUT_SHIFT) &
                         0x1u) ? TRUE : FALSE;
    }
    return status;
}

int32_t PBIST_isPostPbistDone(uint32_t postStatMmrRegVal, bool *pIsDone)
{
    int32_t status = SDL_PASS;

    if (pIsDone == NULL)
    {
        status = SDL_EBADARGS;
    }
    else
    {
        *pIsDone = ((postStatMmrRegVal >>
                    SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_PBIST_DONE_SHIFT) &
                    0x1u) ? TRUE : FALSE;
    }
    return status;
}

int32_t PBIST_postCheckResult(uint32_t postStatMmrRegVal, bool *pResult)
{
    int32_t cslResult= SDL_PASS;

    if(pResult == NULL)
    {
        cslResult = SDL_EFAIL;
    }
    else
    {
        if ((postStatMmrRegVal &
            SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_PBIST_FAIL_MASK) ==
            ((uint32_t)0x00000000u))
        {
            *pResult = TRUE;
        }
        else
        {
            *pResult = FALSE;
        }
    }

    return  cslResult;
}


/* PBIST_setFirewall: Sets firewall settings to be able to access CLEC registers */
static int32_t PBIST_setFirewall(void)
{
    int32_t retVal = SDL_PASS;
    uint32_t reqFlag = TISCI_MSG_FLAG_AOP | TISCI_MSG_FLAG_DEVICE_EXCLUSIVE;
    uint32_t timeout =  SCICLIENT_SERVICE_WAIT_FOREVER;
    struct  tisci_msg_fwl_set_firewall_region_req request;
    Sciclient_ReqPrm_t reqParam;
    Sciclient_RespPrm_t respParam;

    request.fwl_id       = (uint32_t)CSL_STD_FW_NAVSS0_NAV_SRAM0_ID;
    request.region = (uint32_t) 1U; /* Pick up any unused region : 1
                                       NOTE: region 0 is used by default by
                                             System firmware for MSMC Memory currently*/
    request.n_permission_regs = CSL_FW_NUM_CBASS_FW_EP_REGION_PERMISSION;
    request.control = (FW_REGION_ENABLE & CSL_CBASS_ISC_EP_REGION_CONTROL_ENABLE_MASK);
    request.permissions[0] = (FW_MCU_R5F0_PRIVID << CSL_CBASS_FW_EP_REGION_PERMISSION_PRIV_ID_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_DEBUG_SHIFT);
    request.permissions[1] = (FW_MCU_R5F0_PRIVID << CSL_CBASS_FW_EP_REGION_PERMISSION_PRIV_ID_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_DEBUG_SHIFT);
    request.permissions[2] = (FW_MCU_R5F0_PRIVID << CSL_CBASS_FW_EP_REGION_PERMISSION_PRIV_ID_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_SUPV_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_SEC_USER_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_SUPV_DEBUG_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_WRITE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_READ_SHIFT)
                             | (0U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_CACHEABLE_SHIFT)
                             | (1U << CSL_CBASS_FW_EP_REGION_PERMISSION_NONSEC_USER_DEBUG_SHIFT);
    request.start_address = CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE;
    request.end_address = CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE + CSL_COMPUTE_CLUSTER0_CLEC_REGS_SIZE;

    reqParam.messageType    = (uint16_t) TISCI_MSG_SET_FWL_REGION;
    reqParam.flags          = (uint32_t) reqFlag;
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) timeout;

    respParam.flags           = (uint32_t) 0;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) 0;
    respParam.respPayloadSize = (uint32_t) 0;


    if (((reqFlag & TISCI_MSG_FLAG_AOP) != TISCI_MSG_FLAG_AOP)&&
        (reqFlag != 0U))
    {
        retVal = SDL_EFAIL;
    }
    if (retVal == SDL_PASS)
    {
        retVal = Sciclient_service(&reqParam, &respParam);
    }
    if ((retVal != SDL_PASS) ||
        ((reqFlag != 0U) &&
        ((respParam.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK)))
    {
        retVal = SDL_EFAIL;
    }
    return retVal;
}

bool error_test_flag = false;
bool error_test_flag_2 = false;

int32_t SDL_OSAL_getClecOutputEvent(uint32_t *clecOutputEvt)
{
    int32_t retVal = SDL_PASS;

    *clecOutputEvt = CSLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12;

    if (error_test_flag == true)
    {
        *clecOutputEvt = 0x0u;
    }
    else if (error_test_flag_2 == true)
    {
        retVal = SDL_EFAIL;
    }
    return retVal;
}

int32_t SDL_OSAL_releaseClecOutputEvent(uint32_t clecOutputEvt)
{
    return SDL_PASS;
}

/* CLEC configuration for C7X and A72 instances */
int32_t PBIST_clecConfig(uint32_t instance)
{
    SDL_ErrType_t status = SDL_EFAIL;
    CSL_ClecEventConfig evtCfg;

    evtCfg.secureClaimEnable = 0U;
    evtCfg.evtSendEnable = 1U;
    evtCfg.rtMap = 2U;
    evtCfg.c7xEvtNum = 0U;

    if (PBIST_TestHandleArray[instance].pbistInst == SDL_PBIST_INST_A72)
    {
        evtCfg.extEvtNum = CSLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12;
        /* Configure interrupt router to take care of routing A72 PBIST interrupt event */
        status =  CSL_clecConfigEvent((CSL_CLEC_EVTRegs *)CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE,
                                      CSLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_8,
                                      &evtCfg);
        if (status != CSL_PASS)
        {
            UART_printf(" CSL_clecConfigEvent A72 failed \n");
        }
    }
    else if (PBIST_TestHandleArray[instance].pbistInst == SDL_PBIST_INST_C7X)
    {
        evtCfg.extEvtNum = CSLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12;
        /* Configure interrupt router to take care of routing C7x PBIST interrupt event */
        status =  CSL_clecConfigEvent((CSL_CLEC_EVTRegs *)CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE,
                                      CSLR_COMPUTE_CLUSTER0_CLEC_MSMC_EVENT_IN_COMPUTE_CLUSTER0_CORE_CORE_MSMC_INTR_12,
                                      &evtCfg);
        if (status != CSL_PASS)
        {
            UART_printf(" CSL_clecConfigEvent C7x failed \n");
        }
    }

    return status;
}

/* Captures common Initialization: currently initializes firewall for gaining access to CLEC registers */
int32_t PBIST_commonInit(void)
{
    SDL_ErrType_t status;

    /* Add firewall entry to gain access to CLEC registers */
    status = PBIST_setFirewall();
    if (status != SDL_PASS)
    {
        UART_printf(" PBIST_setFirewall failed \n");
    }

    return status;
}

/*
    InitRestore functions : Initialize or Restore based on init flag
    init : TRUE  --> Initialize
    init : FALSE --> Restore
*/
int32_t PBIST_A72AuxInitRestore(bool init)
{
    int32_t testResult = 0;
    bool result;

    CSL_RatTranslationCfgInfo translationCfg;
    uint32_t *localP = (uint32_t *)PBIST_REGION2_LOCAL_BASE;

    /* Add RAT configuration to access address > 32bit address range */
    translationCfg.translatedAddress = CSL_COMPUTE_CLUSTER0_CC_REGS_BASE;
    translationCfg.sizeInBytes = PBIST_REG_REGION_SIZE;
    translationCfg.baseAddress = (uint32_t)PBIST_REGION2_LOCAL_BASE;

    /* Set up RAT translation */
    result = CSL_ratConfigRegionTranslation((CSL_ratRegs *)PBIST_RAT_CFG_BASE,
                                            PBIST_RAT_REGION2_INDEX, &translationCfg);
    if (result == false) {
        UART_printf("   CSL_ratConfigRegionTranslation...FAILED \n");
        testResult = -1;
    }

    if (testResult == 0)
    {
        if (init)
        {
            *((uint32_t *)(((uint32_t)localP) + 0x100)) = 0x1;
        }
        else
        {
            *((uint32_t *)(((uint32_t)localP) + 0x100)) = 0x0;
        }
    }
    if (testResult == 0)
    {
        /* Disable RAT translation */
        result = CSL_ratDisableRegionTranslation((CSL_ratRegs *)PBIST_RAT_CFG_BASE,
                                                 PBIST_RAT_REGION2_INDEX);
        if (result == false) {
            UART_printf("   CSL_ratDisableRegionTranslation...FAILED \n");
            testResult = -1;
        }
    }

    return testResult;
}

int32_t PBIST_VPACAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    CSL_viss_topRegs *vissTopRegsP;

    vissTopRegsP = (CSL_viss_topRegs *)CSL_VPAC0_PAR_VPAC_VISS0_S_VBUSP_MMR_CFG_VISS_TOP_BASE;
    if (init)
    {
        vissTopRegsP->VISS_CNTL = CSL_VISS_TOP_VISS_CNTL_NSF4V_EN_MASK
                                  | CSL_VISS_TOP_VISS_CNTL_GLBCE_EN_MASK;
    }
    else
    {
        vissTopRegsP->VISS_CNTL &= (~(CSL_VISS_TOP_VISS_CNTL_NSF4V_EN_MASK
                                  | CSL_VISS_TOP_VISS_CNTL_GLBCE_EN_MASK));
    }

    return testResult;
}

int32_t PBIST_MainInfraAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    CSL_Cp_aceRegs *SA2ULRegsP;

    SA2ULRegsP = (CSL_Cp_aceRegs *)CSL_SA2_UL0_BASE;

    if (init)
    {
        SA2ULRegsP->UPDATES.ENGINE_ENABLE |= CSL_CP_ACE_UPDATES_ENGINE_ENABLE_PKA_EN_MASK;
    }
    else
    {
        SA2ULRegsP->UPDATES.ENGINE_ENABLE &= (~CSL_CP_ACE_UPDATES_ENGINE_ENABLE_PKA_EN_MASK);
    }

    return testResult;
}

int32_t PBIST_decoderAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    uint32_t *localP = (uint32_t *)CSL_DECODER0_MTX_CORE_BASE;

    if (init)
    {
        *((uint32_t *)(((uint32_t)localP) + 0x440)) = 0xffffffff;
        *((uint32_t *)(((uint32_t)localP) + 0x444)) = 0xffffffff;
        *((uint32_t *)(((uint32_t)localP) + 0x24020)) = 0xffffffff;
        *((uint32_t *)(((uint32_t)localP) + 0x4020)) = 0xffffffff;
        *((uint32_t *)(((uint32_t)localP) + 0x3020)) = 0xffffffff;
    }
    else
    {
        /* TODO: Need to see how to restore */
    }
    return testResult;
}

int32_t PBIST_GPUAuxInitRestore(bool init)
{
    int32_t testResult = 0;
    bool result;

    CSL_RatTranslationCfgInfo translationCfg;

    uint64_t *localP = (uint64_t *)PBIST_REGION2_LOCAL_BASE;

    /* Add RAT configuration to access address > 32bit address range */
    translationCfg.translatedAddress = CSL_GPU0_CORE_MMRS_BASE;
    translationCfg.sizeInBytes = PBIST_REG_REGION2_SIZE;
    translationCfg.baseAddress = (uint32_t)PBIST_REGION2_LOCAL_BASE;

    /* Set up RAT translation */
    result = CSL_ratConfigRegionTranslation((CSL_ratRegs *)PBIST_RAT_CFG_BASE,
                                            PBIST_RAT_REGION2_INDEX, &translationCfg);
    if (result == false) {
        UART_printf("   CSL_ratConfigRegionTranslation...FAILED \n");
        testResult = -1;
    }

    if (testResult == 0)
    {
        if (init)
        {
            *((uint64_t *)(((uint32_t)localP) + 0xA100)) = 0x0;

            while(*((uint64_t *)(((uint32_t)localP) + 0xA100)) !=  (uint64_t)0x0);
            *((uint64_t *)(((uint32_t)localP) + 0x00)) = 0x0555550015155555;
            *((uint64_t *)(((uint32_t)localP) + 0x80)) = 0x0000000400000000;
        }
        else
        {
          /* TODO: Need to see how to revert */
        }
    }
    if (testResult == 0)
    {
        /* Disable RAT translation */
        result = CSL_ratDisableRegionTranslation((CSL_ratRegs *)PBIST_RAT_CFG_BASE,
                                                 PBIST_RAT_REGION2_INDEX);
        if (result == false) {
            UART_printf("   CSL_ratDisableRegionTranslation...FAILED \n");
            testResult = -1;
        }
    }

    return testResult;
}

/* Nothing past this point */
