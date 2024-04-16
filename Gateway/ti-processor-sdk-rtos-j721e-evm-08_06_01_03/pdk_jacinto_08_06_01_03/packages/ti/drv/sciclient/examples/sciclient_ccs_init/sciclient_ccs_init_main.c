/*
 *  Copyright (C) 2018-2020 Texas Instruments Incorporated
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
 *  \file sciclient_ccs_init_main.c
 *
 *  \brief Implementation of System firmware boot test for CCS initialization
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>
#include <sciclient.h>
#include <ti/board/board.h>
#include <ti/drv/sciclient/src/sciclient/sciclient_priv.h>
#include <ti/osal/CacheP.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Set desired DDR PLL frequency here */
#define CSL_DDR_PLL_CLK_FREQ                 (400000000)

/* Config flag to disable PM and RM board config */
#define CONFIG_NO_PM_RM                      (1)

#define CONFIG_BOARDCFG (1)
#define CONFIG_BOARDCFG_SECURITY (1)

/* PM Init is specifically done as the DDR init needs to happen afetr this
 * The sciserver may do pm init again. But that is harmless.
 */
#define CONFIG_BOARDCFG_PM (1)

#if defined(SOC_AM65XX) || defined (SOC_AM64X)
#define CONFIG_BOARDCFG_RM (1)
#endif

#if defined (SOC_AM65XX) || defined (SOC_J721E) || defined (SOC_J7200)
#define SCICLIENT_CCS_DEVGRP0 (DEVGRP_00)
#define SCICLIENT_CCS_DEVGRP1 (DEVGRP_01)
#endif

#if defined (SOC_AM64X) || defined (SOC_J721S2) || defined (SOC_J784S4)
#define SCICLIENT_CCS_DEVGRP0 (DEVGRP_ALL)
#endif

#if defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)
/** \brief Aligned address at which the Board Config header is placed. */
#define SCISERVER_BOARDCONFIG_HEADER_ADDR (0x41c80000U)

/** \brief Aligned address at which the Board Config is placed. */
#define SCISERVER_BOARDCONFIG_DATA_ADDR (0x41c80040U)

#define SCISERVER_POPULATE_BOARDCFG (1U)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const struct tisci_boardcfg gBoardConfigLow_debug
__attribute__(( aligned(128), section(".boardcfg_data") )) =
{
    /* tisci_boardcfg_abi_rev */
    .rev = {
        .tisci_boardcfg_abi_maj = TISCI_BOARDCFG_ABI_MAJ_VALUE,
        .tisci_boardcfg_abi_min = TISCI_BOARDCFG_ABI_MIN_VALUE,
    },

    /* tisci_boardcfg_control */
    .control = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_CONTROL_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_control),
        },
        /* Enable/disable support for System Firmware main isolation.
         * If disabled, main isolation SCI message will be rejected with NAK.
         */
        .main_isolation_enable = 0x5A,
        /* Host-ID allowed to send SCI-message for main isolation.
         * If mismatch, SCI message will be rejected with NAK.
         */
#if defined (SOC_AM64X)
        .main_isolation_hostid = TISCI_HOST_ID_MAIN_0_R5_0,
#elif defined (SOC_J7200) || defined (SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
        .main_isolation_hostid = TISCI_HOST_ID_MCU_0_R5_1,
#else
        .main_isolation_hostid = TISCI_HOST_ID_R5_1,
#endif
    },

    /* tisci_boardcfg_sec_proxy */
    .secproxy = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_SECPROXY_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_secproxy),
        },
        /* Memory allocation for messages scaling factor. In current design,
         * only value of “1” is supported. For future design, a value of “2”
         * would double all memory allocations and credits, “3” would triple,
         * and so on.
         */
        .scaling_factor = 0x1,
        /* Memory allocation for messages profile number. In current design,
         * only a value of “1” is supported. “0” is always invalid due to
         * fault tolerance.
         */
        .scaling_profile = 0x1,
        /* Do not configure main nav secure proxy. This removes all MSMC memory
         * demands from System Firmware but limits MPU channels to one set of
         * secure and one set of insecure. In current design, supports only “0”.
         */
        .disable_main_nav_secure_proxy = 0,
    },

    /* tisci_boardcfg_msmc */
    .msmc = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_MSMC_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_msmc),
        },
        /* If the whole memory is X MB the value you write to this field is n.
         * The value of n sets the cache size as n * X/32. The value of n should
         * be given in steps of 4, which makes the size of cache to be
         * configured in steps on X/8 MB.
         */
        .msmc_cache_size = 0x00,
    },

    /* boardcfg_dbg_cfg */
    .debug_cfg = {
        .subhdr = {
            .magic = TISCI_BOARDCFG_DBG_CFG_MAGIC_NUM,
            .size = sizeof(struct tisci_boardcfg_dbg_cfg),
        },
        /* This enables the trace for DMSC logging. Should be used only for
         * debug. Profiling should not be done with this enabled.
         */
        .trace_dst_enables = (TISCI_BOARDCFG_TRACE_DST_UART0 |
                              TISCI_BOARDCFG_TRACE_DST_ITM |
                              TISCI_BOARDCFG_TRACE_DST_MEM),
        .trace_src_enables = (TISCI_BOARDCFG_TRACE_SRC_PM |
                              TISCI_BOARDCFG_TRACE_SRC_RM |
                              TISCI_BOARDCFG_TRACE_SRC_SEC |
                              TISCI_BOARDCFG_TRACE_SRC_BASE |
                              TISCI_BOARDCFG_TRACE_SRC_USER |
                              TISCI_BOARDCFG_TRACE_SRC_SUPR)
    }
};

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if defined (SOC_AM65XX)
static int32_t setPLLClk(uint32_t modId, uint32_t clkId, uint64_t clkRate);
#endif
static int32_t App_getRevisionTest(void);
static int32_t Sciclient_ccs_init_send_boardcfg (uint8_t devgrp_curr);
#if defined (SCISERVER_POPULATE_BOARDCFG)
static void Sciclient_ccsSetBoardConfigHeader ();
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t main(void)
{
    
    printf(" SCICLIENT_CCS_INIT: %s, %s", __DATE__, __TIME__);
    App_getRevisionTest();

    #if defined (SCISERVER_POPULATE_BOARDCFG)
    Sciclient_ccsSetBoardConfigHeader ();
    #endif

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static int32_t App_getRevisionTest(void)
{
    int32_t status = CSL_EFAIL;
    Sciclient_ConfigPrms_t        config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
        NULL,
        1U,
        0U,
        TRUE
    };
    struct tisci_msg_version_req req = {0};
    const Sciclient_ReqPrm_t      reqPrm =
    {
        TISCI_MSG_VERSION,
        TISCI_MSG_FLAG_AOP,
        (const uint8_t *)&req,
        sizeof(req),
        SCICLIENT_SERVICE_WAIT_FOREVER
    };
    struct tisci_msg_version_resp response;
    Sciclient_RespPrm_t           respPrm =
    {
        0,
        (uint8_t *) &response,
        sizeof (response)
    };

    /* Sciclient CCS Init to start the operation. Call this beforr board init */
    status = Sciclient_init(&config);
    if (CSL_PASS == status)
    {
        printf ("Sciclient_Init Passed.\n");
    }
    else
    {
        printf ("Sciclinet_Init Failed.\n");
    }
    status = Sciclient_ccs_init_send_boardcfg (SCICLIENT_CCS_DEVGRP0);
#if defined (SCICLIENT_CCS_DEVGRP1)
    if (CSL_PASS == status)
    {
        printf ("=================================================================\n");
        printf ("Sciclient Dev Group 01 initilization started\n");
#if !defined (SOC_AM65XX)
#if CONFIG_BOARDCFG_PM
        printf ("Power on the WKUPMCU to MAIN and MAIN to WKUPMCU VDs... ");
        /* This is specifically required if you are booting in MCU_ONLY boot mode. */
        status = Sciclient_pmSetModuleState(TISCI_DEV_WKUPMCU2MAIN_VD,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP | TISCI_MSG_FLAG_DEVICE_RESET_ISO,
                                            0xFFFFFFFFU);
        status += Sciclient_pmSetModuleState(TISCI_DEV_MAIN2WKUPMCU_VD,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP | TISCI_MSG_FLAG_DEVICE_RESET_ISO,
                                            0xFFFFFFFFU);
        if (CSL_PASS == status)
        {
            printf("PASSED\n");
        }
        else
        {
            printf("FAILED\n");
        }
#endif
#endif
    }
    if (CSL_PASS == status)
    {
        status = Sciclient_ccs_init_send_boardcfg (SCICLIENT_CCS_DEVGRP1);
    }
#endif    
    if (status == CSL_PASS)
    {
        status = Sciclient_service(&reqPrm, &respPrm);
        if ((CSL_PASS == status) && (respPrm.flags == TISCI_MSG_FLAG_ACK))
        {
            status = CSL_PASS;
            printf ("=================================================================\n");
            printf(" DMSC Firmware Version %s\n",
                              (char *) response.str);
            printf(" Firmware revision 0x%x\n", response.version);
            printf(" ABI revision %d.%d\n", response.abi_major,
                              response.abi_minor);
        }
        else
        {
            printf(" DMSC Firmware Get Version failed \n");
        }
    }
    /* Set DDR PLL to 400 Mhz. SYSFW default sets this to 333.33 Mhz */
    /* Comment this code if LPDDR is used */
#if defined(SOC_AM65XX)
    if (status == CSL_PASS)
    {
        /* Set DDR PLL to 400 Mhz. SYSFW default sets this to 333.33 Mhz */
        /* Comment this code if LPDDR is used */
        status = setPLLClk(TISCI_DEV_DDRSS0, TISCI_DEV_DDRSS0_BUS_DDRSS_BYP_4X_CLK, CSL_DDR_PLL_CLK_FREQ);
    }
#endif
    if (status == CSL_PASS)
    {
        status = Sciclient_deinit();
    }
    printf ("=================================================================\n");
    if (CSL_PASS == status)
    {
        printf("Sciclient_ccs_init Passed.\n");
    }
    else
    {
        printf("Sciclient_ccs_init Failed.\n");
    }
    return status;
}

static int32_t Sciclient_ccs_init_send_boardcfg (uint8_t devgrp_curr)
{
    int32_t status = CSL_PASS;
    /* Common Board configuration to set up trace, secure Proxy and 
     * MSMC configuration.
     */
#if CONFIG_BOARDCFG
    if (CSL_PASS == status)
    {
        printf ("=================================================================\n");
        printf (" DEVGRP = %d\n", devgrp_curr);
        printf ("=================================================================\n");
        printf("SYSFW Common Board Configuration with Debug enabled... ");
        Sciclient_BoardCfgPrms_t boardCfgPrms =
        {
            .boardConfigLow = (uint32_t) &gBoardConfigLow_debug,
            .boardConfigHigh = 0,
            .boardConfigSize = sizeof(gBoardConfigLow_debug),
            .devGrp = devgrp_curr
        };
        status = Sciclient_boardCfg(&boardCfgPrms);
        if (CSL_PASS == status)
        {
            printf("PASSED\n");
        }
        else
        {
            printf("FAILED\n");
        }
    }
#endif
    /* PM board configuration to setup the PLLs and internal state of
     * the devices.
     */
#if CONFIG_BOARDCFG_PM
    if (CSL_PASS == status)
    {
        uint32_t boardCfgLow[] = SCICLIENT_BOARDCFG_PM;
        Sciclient_BoardCfgPrms_t boardCfgPrms_pm =
        {
            .boardConfigLow = (uint32_t)boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = 0,
            .devGrp = devgrp_curr
        };
        printf("SYSFW PM Board Configuration... ");
        status = Sciclient_boardCfgPm(&boardCfgPrms_pm);
        if (CSL_PASS == status)
        {
            printf("PASSED\n");
        }
        else
        {
            printf("FAILED\n");
        }
    }
#endif
    /* RM Board configuration to define the use of Resources allocated
     * to each core.
     */
#if CONFIG_BOARDCFG_RM
    if (status == CSL_PASS)
    {
        uint32_t boardCfgLow[] = SCICLIENT_BOARDCFG_RM;
        Sciclient_BoardCfgPrms_t boardCfgPrms_rm =
        {
            .boardConfigLow = (uint32_t) boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
            .devGrp = devgrp_curr
        };
        printf("SYSFW RM Board Configuration... ");
        status = Sciclient_boardCfgRm(&boardCfgPrms_rm);
        if (CSL_PASS == status)
        {
            printf("PASSED\n");
        }
        else
        {
            printf("FAILED\n");
        }
    }
#endif
    /* Security board configuration for the security subsystem init */
#if CONFIG_BOARDCFG_SECURITY
    if (status == CSL_PASS)
    {
        uint32_t boardCfgLow[] = SCICLIENT_BOARDCFG_SECURITY;
        Sciclient_BoardCfgPrms_t boardCfgPrms_security =
        {
            .boardConfigLow = (uint32_t) boardCfgLow,
            .boardConfigHigh = 0,
            .boardConfigSize = SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES,
            .devGrp = devgrp_curr
        };
        printf("SYSFW Security Board Configuration... ");
        status = Sciclient_boardCfgSec(&boardCfgPrms_security) ;
        if (CSL_PASS == status)
        {
            printf("PASSED\n");
        }
        else
        {
            printf("FAILED\n");
        }
    }
#endif
    return status;
}

#if defined(SOC_AM65XX)
/**
 * \brief  PLL clock configuration
 *
 * This function is used to set the PLL Module clock frequency
 *
 * \param  moduleId [IN]  Module for which the state should be set.
 *                        Refer Sciclient_PmDeviceIds in sciclient_fmwMsgParams.h
 * \param  clockId  [IN]  Clock Id for the module.
 *                        Refer Sciclient_PmModuleClockIds in sciclient_fmwMsgParams.h
 * \param  clkRate  [IN]  Value of the clock frequency to be set
 *
 * \return int32_t
 *                CSL_PASS - on Success
 *                CSL_EFAIL - on Failure
 *
 */
static int32_t setPLLClk(uint32_t modId,
                             uint32_t clkId,
                             uint64_t clkRate)
{
    uint8_t parentId = 0;
    uint32_t i = 0U;
    int32_t status   = 0;
    uint64_t respClkRate = 0;
    uint32_t clockBaseId = 0U;
    uint32_t numParents = 0U;
    uint32_t clockStatus;

    status = Sciclient_pmQueryModuleClkFreq(modId,
                                        clkId,
                                        clkRate,
                                        &respClkRate,
                                        SCICLIENT_SERVICE_WAIT_FOREVER);
    if(status == CSL_PASS)
    {
        /* Check if the clock is enabled or not */
        status = Sciclient_pmModuleGetClkStatus(modId,
                                                clkId,
                                                &clockStatus,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
    }

    if(status == CSL_PASS)
    {
        /* Check if the clock is enabled or not */
        status = Sciclient_pmGetModuleClkNumParent(modId,
                                                clkId,
                                                &numParents,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
    }

    if ((status == CSL_PASS) && (respClkRate == clkRate))
    {
        status = Sciclient_pmSetModuleClkFreq(
                                modId,
                                clkId,
                                clkRate,
                                TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            if (clockStatus == TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ)
            {
                /* Enable the clock */
                status = Sciclient_pmModuleClkRequest(
                                                    modId,
                                                    clkId,
                                                    TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
                                                    0U,
                                                    SCICLIENT_SERVICE_WAIT_FOREVER);
            }
        }
    }
    else if (status == CSL_PASS)
    {
        /* Try to loop and change parents of the clock */
        for(i = 0U; i < numParents; i++)
        {
            /* Disabling the clock */
            status = Sciclient_pmModuleClkRequest(modId,
                                                  clkId,
                                                  TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ,
                                                  0U,
                                                  SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status == CSL_PASS)
            {
                clockStatus = TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ;
                /* Setting the new parent */
                status = Sciclient_pmSetModuleClkParent(
                                        modId,
                                        clkId,
                                        clkId+i+1,
                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            }
            /* Check if the clock can be set to desirable freq. */
            if (status == CSL_PASS)
            {
                status = Sciclient_pmQueryModuleClkFreq(modId,
                                                        clkId,
                                                        clkRate,
                                                        &respClkRate,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            }
            if (status == CSL_PASS)
            {
                if(respClkRate == clkRate)
                {
                    break;
                }
                else
                {
                    status = CSL_EFAIL;
                }
            }
            parentId++;
            clockBaseId++;
        }

        if (status == CSL_PASS)
        {
            /* Set the clock at the desirable frequency*/
            status = Sciclient_pmSetModuleClkFreq(
                                    modId,
                                    clkId,
                                    clkRate,
                                    TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                    SCICLIENT_SERVICE_WAIT_FOREVER);
        }
        if((status == CSL_PASS) && (clockStatus == TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ))
        {
            /*Enable the clock again */
            status = Sciclient_pmModuleClkRequest(
                                                modId,
                                                clkId,
                                                TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ,
                                                0U,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        }
    }
    if (CSL_PASS == status)
    {
        printf("PLL set to %f MHz \n", (float)(clkRate/1000000) );
    }
    else
    {
        printf("Failed to change PLL clock \n");
    }

    return status;
}
#endif

#if defined (SCISERVER_POPULATE_BOARDCFG)
static void Sciclient_ccsSetBoardConfigHeader ()
{
    int32_t status = CSL_PASS;
    uint32_t boardCfgLowPm[] = SCICLIENT_BOARDCFG_PM;
    uint32_t boardCfgLowRm[] = SCICLIENT_BOARDCFG_RM;
    uint32_t alignedOffset = ((sizeof(boardCfgLowPm) + 128U)/128U)*128U;
    Sciclient_BoardCfgPrms_t boardCfgPrms_pm =
    {
        .boardConfigLow = (uint32_t)SCISERVER_BOARDCONFIG_DATA_ADDR,
        .boardConfigHigh = 0,
        .boardConfigSize = SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES,
        .devGrp = DEVGRP_ALL
    };
    Sciclient_BoardCfgPrms_t boardCfgPrms_rm =
    {
        .boardConfigLow =
            (uint32_t) SCISERVER_BOARDCONFIG_DATA_ADDR + alignedOffset,
        .boardConfigHigh = 0,
        .boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
        .devGrp = DEVGRP_ALL
    };
    printf("SCISERVER Board Configuration header population... ");
    status = Sciclient_boardCfgPrepHeader (
        (uint8_t *) SCISERVER_COMMON_X509_HEADER_ADDR,
        (uint8_t *) SCISERVER_BOARDCONFIG_HEADER_ADDR,
        &boardCfgPrms_pm, &boardCfgPrms_rm);
    CacheP_wbInv((void*)SCISERVER_COMMON_X509_HEADER_ADDR, 0x500); 
    CacheP_wbInv((void*)SCISERVER_BOARDCONFIG_HEADER_ADDR, 0x500); 
    if (CSL_PASS == status)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED\n");
    }
    memcpy((void *)boardCfgPrms_pm.boardConfigLow, (void *) boardCfgLowPm, sizeof(boardCfgLowPm));
    CacheP_wbInv((void*)boardCfgPrms_pm.boardConfigLow, sizeof(boardCfgLowPm)); 
    memcpy((void *)boardCfgPrms_rm.boardConfigLow, (void *) boardCfgLowRm, sizeof(boardCfgLowRm));
    CacheP_wbInv((void*)boardCfgPrms_rm.boardConfigLow, sizeof(boardCfgLowRm)); 
}
#endif
