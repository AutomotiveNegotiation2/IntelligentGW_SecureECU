/*
 *   Copyright (c) Texas Instruments Incorporated 2020-2021
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
 *  \file     sdl_lbist_test_cfg.c
 *
 *  \brief    This file contains LBIST test configuration
 *
 *  \details  LBIST Test Configuration
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <sdl_types.h>
#include <soc.h>
#include <src/sdl/sdl_lbist.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/sciclient/sciclient.h>

/* Osal API header files */
//#include <ti/osal/HwiP.h>
#include <ti/osal/TimerP.h>

#include "lbist_test_cfg.h"

/* #define DEBUG */

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32_t LBIST_A72AuxDevList[A72_NUM_AUX_DEVICES] =
{
    TISCI_DEV_A72SS0,
};

LBIST_TestHandle_t LBIST_TestHandleArray[SDL_LBIST_NUM_INSTANCES] =
{
#if 0
 /* HW POST - DMSC - Checks MISR results only */
 {
  .coreName               = "HWPOST - DMSC",
  .pLBISTRegs             = (SDL_lbistRegs *)(SDL_DMSC_LBIST_BASE),
  .pLBISTSig              = (uint32_t *)(SDL_DMSC_LBIST_SIG),
  .doneFlag               = false,                    /* Initialize done flag */
  .numAuxDevices          = 0u,                       /* No Aux devices */
  .hwPostCoreCheck        = true,
  .hwPostCoreNum          = LBIST_POST_CORE_DMSC,
  .handler                = NULL             ,       /* LBIST event handler */
 },
 /* HW POST - MCU - Checks MISR results only */
 {
  .coreName               = "HWPOST - MCU",
  .pLBISTRegs             = (SDL_lbistRegs *)(SDL_MCU_LBIST_BASE),
  .pLBISTSig              = (uint32_t *)(SDL_MCU_LBIST_SIG),
  .doneFlag               = false,                    /* Initialize done flag */
  .numAuxDevices          = 0u,                       /* No Aux devices */
  .hwPostCoreCheck        = true,
  .hwPostCoreNum          = LBIST_POST_CORE_MCU,
  .handler                = NULL             ,       /* LBIST event handler */
 },
#endif
 /* Main R5F 0 */
 {
  .coreName               = "Main R5F0-0",
  .instance               = SDL_LBIST_INST_MAINR5F0,
  .secondaryCoreNeeded    = true,             /* Secondary core needed */
  .wfiCheckNeeded         = false,            /* wfi check needed */
  .secCoreName            = "Main R5F1-0",    /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_R5FSS0_CORE0, /* Main R5F core 0 Proc Id */
  .tisciSecProcId         = SCICLIENT_PROC_ID_R5FSS0_CORE1, /* Main R5F core 1 Proc Id */
  .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,   /* Main R5F core 0 Device Id */
  .tisciSecDeviceId       = TISCI_DEV_R5FSS0_CORE1,   /* Main R5F core 1 Device Id */
  .numAuxDevices          = 0u,                       /* No Aux devices */
 },
 /* Main R5F 1 */
 {
  .coreName               = "Main R5F1-0",
  .instance               = SDL_LBIST_INST_MAINR5F1,
  .secondaryCoreNeeded    = true,            /* Secondary core needed */
  .wfiCheckNeeded         = false,           /* wfi check needed */
  .secCoreName            = "Main R5F1-1",   /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_R5FSS1_CORE0, /* Main R5F core 0 Proc Id */
  .tisciSecProcId         = SCICLIENT_PROC_ID_R5FSS1_CORE1, /* Main R5F core 1 Proc Id */
  .tisciDeviceId          = TISCI_DEV_R5FSS1_CORE0,  /* Main R5F core 0 Device id */
  .tisciSecDeviceId       = TISCI_DEV_R5FSS1_CORE1,  /* Main R5F core 1 Device id */
  .numAuxDevices          = 0u,                      /* No Aux devices */
 },
 /* C7x */
 {
  .coreName               = "C7x ",
  .instance               = SDL_LBIST_INST_C7X,
  .secondaryCoreNeeded    = false,  /* Secondary core needed */
  .wfiCheckNeeded         = false,  /* wfi check needed */
  .secCoreName            = "None",   /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_C71SS0,  /* C7x Proc Id */
  .tisciSecProcId         = 0,
  .tisciDeviceId          = TISCI_DEV_C71SS0,          /* C7x Device Id */
  .tisciSecDeviceId       = 0,
  .numAuxDevices          = 0u,                        /* No Aux devices */
 },

 /* VPAC */
 {
  .coreName               = "VPAC",
  .instance               = SDL_LBIST_INST_VPAC,
  .secondaryCoreNeeded    = false,           /* Secondary core needed */
  .wfiCheckNeeded         = false,           /* wfi check needed */
  .secCoreName            = "None",          /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = 0,  /* No proc id */
  .tisciSecProcId         = 0,  /* No Proc Id */
  .tisciDeviceId          = TISCI_DEV_VPAC0,                       /* VPAC Device Id */
  .tisciSecDeviceId       = 0,
  .numAuxDevices          = 0u,                                    /* No Aux devices */
 },

 /* DMPAC */
 {
  .coreName               = "DMPAC",
  .instance               = SDL_LBIST_INST_DMPAC,
  .secondaryCoreNeeded    = false,           /* Secondary core needed */
  .wfiCheckNeeded         = false,           /* wfi check needed */
  .secCoreName            = "None",          /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = 0,  /* No proc id */
  .tisciSecProcId         = 0,  /* No Proc Id */
  .tisciDeviceId          = TISCI_DEV_DMPAC0,                       /* DMPAC Device Id */
  .tisciSecDeviceId       = 0,
  .numAuxDevices          = 0u,                                     /* No Aux devices */
 },

 /* A72 */
 {
  .coreName               = "A72 core 0",
  .instance               = SDL_LBIST_INST_A72,
  .secondaryCoreNeeded    = true,           /* Secondary core needed */
  .wfiCheckNeeded         = false,          /* wfi check needed */
  .secCoreName            = "A72 core 1",   /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_A72SS0_CORE0, /* A72 core 0 Proc Id */
  .tisciSecProcId         = SCICLIENT_PROC_ID_A72SS0_CORE1, /* A72 core 1 Proc Id */
  .tisciDeviceId          = TISCI_DEV_A72SS0_CORE0,  /* A72 core 0 Device Id */
  .tisciSecDeviceId       = TISCI_DEV_A72SS0_CORE1,  /* A72 core 1 Device Id */
  .numAuxDevices          = A72_NUM_AUX_DEVICES,     /* Number of Aux devices */
  .auxDeviceIdsP          = &LBIST_A72AuxDevList[0], /* Array of Aux device ids */
 },

};

#if 0
LBIST_TestHandle_t LBIST_TestHandleArray_ES1_1[LBIST_MAX_CORE_INDEX+1] =
{
#if 0
 /* HW POST - DMSC - Checks MISR results only */
 {
  .coreName               = "HWPOST - DMSC",
  .pLBISTRegs             = (SDL_lbistRegs *)(SDL_DMSC_LBIST_BASE),
  .pLBISTSig              = (uint32_t *)(SDL_DMSC_LBIST_SIG),
  .doneFlag               = false,                    /* Initialize done flag */
  .numAuxDevices          = 0u,                       /* No Aux devices */
  .hwPostCoreCheck        = true,
  .hwPostCoreNum          = LBIST_POST_CORE_DMSC,
  .handler                = NULL             ,       /* LBIST event handler */
 },
 /* HW POST - MCU - Checks MISR results only */
 {
  .coreName               = "HWPOST - MCU",
  .pLBISTRegs             = (SDL_lbistRegs *)(SDL_MCU_LBIST_BASE),
  .pLBISTSig              = (uint32_t *)(SDL_MCU_LBIST_SIG),
  .doneFlag               = false,                    /* Initialize done flag */
  .numAuxDevices          = 0u,                       /* No Aux devices */
  .hwPostCoreCheck        = true,
  .hwPostCoreNum          = LBIST_POST_CORE_MCU,
  .handler                = NULL             ,       /* LBIST event handler */
 },
#endif
 /* Main R5F 0 */
 {
  .coreName               = "Main R5F0-0",
  .secondaryCoreNeeded    = true,             /* Secondary core needed */
  .wfiCheckNeeded         = false,            /* wfi check needed */
  .secCoreName            = "Main R5F1-0",    /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_R5FSS0_CORE0, /* Main R5F core 0 Proc Id */
  .tisciSecProcId         = SCICLIENT_PROC_ID_R5FSS0_CORE1, /* Main R5F core 1 Proc Id */
  .tisciDeviceId          = TISCI_DEV_R5FSS0_CORE0,   /* Main R5F core 0 Device Id */
  .tisciSecDeviceId       = TISCI_DEV_R5FSS0_CORE1,   /* Main R5F core 1 Device Id */
  .numAuxDevices          = 0u,                       /* No Aux devices */
 },
 /* Main R5F 1 */
 {
  .coreName               = "Main R5F1-0",
  .secondaryCoreNeeded    = true,            /* Secondary core needed */
  .wfiCheckNeeded         = false,           /* wfi check needed */
  .secCoreName            = "Main R5F1-1",   /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_R5FSS1_CORE0, /* Main R5F core 0 Proc Id */
  .tisciSecProcId         = SCICLIENT_PROC_ID_R5FSS1_CORE1, /* Main R5F core 1 Proc Id */
  .tisciDeviceId          = TISCI_DEV_R5FSS1_CORE0,  /* Main R5F core 0 Device id */
  .tisciSecDeviceId       = TISCI_DEV_R5FSS1_CORE1,  /* Main R5F core 1 Device id */
  .numAuxDevices          = 0u,                      /* No Aux devices */
 },
 /* C7x */
 {
  .coreName               = "C7x ",
  .secondaryCoreNeeded    = false,  /* Secondary core needed */
  .wfiCheckNeeded         = false,  /* wfi check needed */
  .secCoreName            = "None",   /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_C71SS0,  /* C7x Proc Id */
  .tisciSecProcId         = 0,
  .tisciDeviceId          = TISCI_DEV_C71SS0,          /* C7x Device Id */
  .tisciSecDeviceId       = 0,
  .numAuxDevices          = 0u,                        /* No Aux devices */
 },

 /* VPAC */
 {
  .coreName               = "VPAC",
  .secondaryCoreNeeded    = false,           /* Secondary core needed */
  .wfiCheckNeeded         = false,           /* wfi check needed */
  .secCoreName            = "None",          /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = 0,  /* No proc id */
  .tisciSecProcId         = 0,  /* No Proc Id */
  .tisciDeviceId          = TISCI_DEV_VPAC0,                       /* VPAC Device Id */
  .tisciSecDeviceId       = 0,
  .numAuxDevices          = 0u,                                    /* No Aux devices */
 },

 /* DMPAC */
 {
  .coreName               = "DMPAC",
  .secondaryCoreNeeded    = false,           /* Secondary core needed */
  .wfiCheckNeeded         = false,           /* wfi check needed */
  .secCoreName            = "None",          /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = 0,  /* No proc id */
  .tisciSecProcId         = 0,  /* No Proc Id */
  .tisciDeviceId          = TISCI_DEV_DMPAC0,                       /* DMPAC Device Id */
  .tisciSecDeviceId       = 0,
  .numAuxDevices          = 0u,                                     /* No Aux devices */
 },

 /* A72 */
 {
  .coreName               = "A72 core 0",
  .secondaryCoreNeeded    = true,           /* Secondary core needed */
  .wfiCheckNeeded         = false,          /* wfi check needed */
  .secCoreName            = "A72 core 1",   /* Secondary core */
  .cpuStatusFlagMask      = TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI, /* Expected boot status value for wfi */
  .tisciProcId            = SCICLIENT_PROC_ID_A72SS0_CORE0, /* A72 core 0 Proc Id */
  .tisciSecProcId         = SCICLIENT_PROC_ID_A72SS0_CORE1, /* A72 core 1 Proc Id */
  .tisciDeviceId          = TISCI_DEV_A72SS0_CORE0,  /* A72 core 0 Device Id */
  .tisciSecDeviceId       = TISCI_DEV_A72SS0_CORE1,  /* A72 core 1 Device Id */
  .numAuxDevices          = A72_NUM_AUX_DEVICES,     /* Number of Aux devices */
  .auxDeviceIdsP          = &LBIST_A72AuxDevList[0], /* Array of Aux device ids */
 },

};
#endif

#if 0
static int32_t LBIST_isPostLbistTimeout(uint32_t postStatMmrRegVal,
                                        uint8_t section,
                                        Bool *pIsTimedOut);

static int32_t LBIST_isPostLbistDone(uint32_t postStatMmrRegVal,
                                     uint8_t section,
                                     Bool *pIsDone);

static int32_t LBIST_isPostLbistTimeout(uint32_t postStatMmrRegVal,
                                        uint8_t section,
                                        Bool *pIsTimedOut)
{
    int32_t status = SDL_PASS;
    uint32_t shift;

    if ((pIsTimedOut == NULL) || (section > LBIST_POST_CORE_MAX))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        if (section == LBIST_POST_CORE_DMSC)
        {
            shift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_DMSC_LBIST_TIMEOUT_SHIFT;
        }
        else if (section == LBIST_POST_CORE_MCU)
        {
            shift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_LBIST_TIMEOUT_SHIFT;
        }

        *pIsTimedOut = ((postStatMmrRegVal >> shift) & 0x1u) ? TRUE : FALSE;
    }

    return status;
}

static int32_t LBIST_isPostLbistDone(uint32_t postStatMmrRegVal,
                                     uint8_t section,
                                     Bool *pIsDone)
{
    int32_t status = SDL_PASS;
    uint32_t shift;

    if ((pIsDone == NULL) || (section > LBIST_POST_CORE_MAX))
    {
        status = SDL_EBADARGS;
    }
    else
    {
        if (section == LBIST_POST_CORE_DMSC)
        {
            shift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_DMSC_LBIST_DONE_SHIFT;
        }
        else if (section == LBIST_POST_CORE_MCU)
        {
            shift = SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT_POST_MCU_LBIST_DONE_SHIFT;
        }

        *pIsDone = ((postStatMmrRegVal >> shift) & 0x1u) ? TRUE : FALSE;
    }
    return status;
}

int32_t LBIST_runPostLbistCheck(uint32_t hwPostCoreNum,
                                       SDL_lbistRegs *pLBISTRegs,
                                       uint32_t *pLBISTSig)
{
    int32_t  status = 0;
    uint32_t calculatedMISR;
    uint32_t expectedMISR;
    int32_t  postStatus = LBIST_POST_COMPLETED_SUCCESS;
    uint32_t postRegVal;
    Bool     LBISTResult;

    /* Read HW POST status register */
    postRegVal = SDL_REG32_RD(SDL_WKUP_CTRL_MMR0_CFG0_BASE +
                              SDL_WKUP_CTRL_MMR_CFG0_WKUP_POST_STAT);

    /* Check if HW POST LBIST was performed */
    status = LBIST_isPostLbistDone(postRegVal, hwPostCoreNum, &LBISTResult);
    if (status != SDL_PASS)
    {
        UART_printf("   HW POST: LBIST_isPostLbistDone failed\n");
    }
    else
    {
        if (LBISTResult != true)
        {
            /* HW POST: LBIST not completed, check if it timed out */
            status = LBIST_isPostLbistTimeout(postRegVal,
                                              hwPostCoreNum,
                                              &LBISTResult);
            if (LBISTResult != true)
            {
                /* HW POST: LBIST was not performed at all on this device
                 * for this core */
                postStatus = LBIST_POST_NOT_RUN;
                UART_printf("\n   HW POST: LBIST not run on this device\n");
            }
            else
            {
                /* HW POST: LBIST was attempted but timed out for this section */
                postStatus = LBIST_POST_ATTEMPTED_TIMEOUT;
                UART_printf("\n   HW POST: LBIST failed with HW POST timeout\n");
            }
        }
        else
        {
            /* Get the output MISR and the expected MISR */
            if (status == 0)
            {
                status = SDL_LBIST_getMISR(pLBISTRegs, &calculatedMISR);
                if (status != SDL_PASS)
                {
                    UART_printf("\n HW POST: Get MISR failed \n");
                }
            }

            if (status == 0)
            {
                status = SDL_LBIST_getExpectedMISR(pLBISTSig, &expectedMISR);
                if ( status != SDL_PASS)
                {
                    UART_printf("\n HW POST: Get Expected MISR failed \n");
                }
            }

            /* Compare the results, and set failure if they do not match */
#ifdef DEBUG
            UART_printf(" For HW POST LBIST core %d, Expected MISR= 0x%x, Calculated MISR = 0x%x\n",
                        hwPostCoreNum,
                        expectedMISR,
                        calculatedMISR);
#endif
            if (calculatedMISR != expectedMISR)
            {
                /* HW POST: LBIST was completed, but the test failed for this
                 * core */
                postStatus = LBIST_POST_COMPLETED_FAILURE;
                UART_printf("\n   HW POST: LBIST failed with MISR mismatch: Expected 0x%x got 0x%x\n",
                            expectedMISR, calculatedMISR);
            }
            else if ((calculatedMISR == 0) && (expectedMISR == 0))
            {
                postStatus = LBIST_POST_NOT_RUN;
                UART_printf("\n   HW POST: Device does not contain proper seed for MISR in eFuse - "\
                            "HW POST LBIST not supported on this device \n");
            }
            else
            {
                UART_printf("\n   HW POST: LBIST MISR matched \n");
            }
        } /* if (LBISTResult != true) */
    } /* if (status != SDL_PASS) */

    if (status == 0)
    {
        /* All function calls returned successfully */
        return(postStatus);
    }
    else
    {
        /* Error in function calls */
        return(status);
    }
}
#endif

#if 0
LBIST_TestHandle_t* LBIST_getTestHandleArray(void)
{
    LBIST_TestHandle_t *handle;
    uint32_t siliconRev = 0U;

    siliconRev = SDL_REG32_FEXT((SDL_WKUP_CTRL_MMR0_CFG0_BASE +
                                SDL_WKUP_CTRL_MMR_CFG0_JTAGID),
                                WKUP_CTRL_MMR_CFG0_JTAGID_VARIANT);
    if (0U != siliconRev)
    {
        handle = LBIST_TestHandleArray_ES1_1;
    }
    else
    {
        handle = LBIST_TestHandleArray_ES1_0;
    }
    return handle;
}
#endif

/* Nothing past this point */
