/*
*
* Copyright (c) 2022 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/**
 *  \file boot_app_main.c
 *
 *  \brief Main file for building boot app build
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "boot_app_priv.h"

#if (defined (BUILD_MCU1_0) && (defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)))
#include <ti/drv/sciclient/sciserver_tirtos.h>
#endif

#if defined(BOOT_MMCSD)
#include "boot_app_mmcsd.h"
#elif defined(BOOT_OSPI)
#include "boot_app_ospi.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define APP_TASK_STACK                  (10U * 1024U)
/**< Task Priority Levels */
#define BOOT_TASK_PRIORITY              (2)

/* uncomment the following for debug logs */
// #define UART_PRINT_DEBUG

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void BootApp_TaskFxn(void* a0, void* a1);
static uint32_t Boot_App();
static void BootApp_AppSetup();
static int32_t BootApp_RequestStageCores(uint8_t stageNum);
static int32_t BootApp_ReleaseStageCores(uint8_t stageNum);
static void BootApp_ArmR5PmuCntrInit();
static uint32_t BootApp_GetTimeInMicroSec(uint32_t pmuCntrVal);
static uint32_t BootApp_SetupSciServer(void);

/* Function Pointer used while reading data from the storage. */
extern int32_t   (*fp_readData)(void *dstAddr, void *srcAddr, uint32_t length);
extern void     (*fp_seek)(void *srcAddr, uint32_t location);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Stack for the Boot task */
static uint8_t gBootAppTaskStack[APP_TASK_STACK] __attribute__((aligned(32)));
TaskP_Handle gbootTask;
static uint64_t gtimeBootAppStart, gtimeBootAppFinish;

int32_t main(void)
{
    Board_initCfg boardCfg;
    uint32_t ret = CSL_PASS;
    TaskP_Params bootTaskParams;
    
    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_UART_STDIO;
    Board_init(boardCfg);
    OS_init();
    
    ret = BootApp_SetupSciServer();
    if(ret != CSL_PASS)
    {
        UART_printf("\nFailed to setup sciserver for boot app\r\n");
        OS_stop();
    }

    BootApp_ArmR5PmuCntrInit();

    UART_printf("\nMCU R5F App started at %d usecs\r\n", BootApp_GetTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM)));

    /* Initialize the task params */
    TaskP_Params_init(&bootTaskParams);
    bootTaskParams.priority       = BOOT_TASK_PRIORITY;
    bootTaskParams.stack          = gBootAppTaskStack;
    bootTaskParams.stacksize      = sizeof (gBootAppTaskStack);

    gbootTask = TaskP_create(&BootApp_TaskFxn, &bootTaskParams);
    if (NULL == gbootTask)
    {
        UART_printf("\nBoot Task creation failed\r\n");
        OS_stop();
    }

    OS_start();    /* does not return */

    return(0);
}

static void BootApp_TaskFxn(void* a0, void* a1)
{
    gtimeBootAppStart = BootApp_GetTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));

    Boot_App();

    gtimeBootAppFinish = BootApp_GetTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));

    UART_printf("\nMCU Boot Task started at %d usecs and finished at %d usecs\r\n", (uint32_t)gtimeBootAppStart, (uint32_t)gtimeBootAppFinish);

    return;
}

uint32_t Boot_App()
{
    uint32_t       retVal;
    cpu_core_id_t  core_id;
    cpu_core_id_t  booted_core_ids[DSP2_C7X_ID];
    uint8_t        i, j;
    cpu_core_id_t *boot_array;
    uint8_t        num_cores_to_boot;
    uint8_t        num_booted_cores = 0;
    uint64_t       time_boot_core_finish[DSP2_C7X_ID];

#if defined(BOOT_OSPI)
    SBL_SPI_init();
    SBL_ospiInit(&boardHandle);
#endif

    /* Configuration of items needed by apps on some cores, before they boot */
    BootApp_AppSetup();

#if defined(BOOT_MMCSD)

    retVal = BootApp_MMCBootImageInit();
    if (retVal != CSL_PASS)
    {
        UART_printf("Failure during BootApp_MMCBootImageInit\n\n");
    }
#endif

    /* Initialize the entry point array to 0. */
    for (core_id = MPU1_CPU0_ID; core_id < NUM_CORES; core_id ++)
        (&gK3xx_evmEntry)->CpuEntryPoint[core_id] = SBL_INVALID_ENTRY_ADDR;

    for (j = 0; j < NUM_BOOT_STAGES; j++)
    {

        retVal = BootApp_RequestStageCores(j);

        if (retVal != CSL_PASS)
        {
            UART_printf("Failed to request all late cores in Stage %d\n\n", j);
            BootApp_ReleaseStageCores(j);
        } else
        {
            UART_printf("Loading BootImage\n");

            #if defined(BOOT_MMCSD)
                retVal = BootApp_MMCSDBootStageImage(&gK3xx_evmEntry, mmcsd_main_domain_rtos_image_name[j]);
            #endif

            #if defined(BOOT_OSPI)
                retVal = BootApp_OSPIBootStageImage(&gK3xx_evmEntry, ospi_main_domain_flash_rtos_images[j]);
            #endif

            UART_printf("BootImage completed, status = %d\n", retVal);

            if (retVal != CSL_PASS)
            {
                UART_printf("Failure during image copy and parsing\n\n");
            } 
            else
            {
                retVal = BootApp_ReleaseStageCores(j);
                if (retVal != CSL_PASS)
                {
                    UART_printf("Failed to release all late cores\n\n");
                }
            }
        } /* if (retVal != CSL_PASS) */

        if (retVal == CSL_PASS)
        {
            /* Start the individual cores for the boot stage */
            num_cores_to_boot = num_cores_per_boot_stage[j];
            boot_array        = boot_array_stage[j];
            for (i = 0; i < num_cores_to_boot; i++)
            {
                core_id = boot_array[i];
                /* Try booting all cores other than the cluster running the SBL */
                if ((gK3xx_evmEntry.CpuEntryPoint[core_id] != SBL_INVALID_ENTRY_ADDR) &&
                    ((core_id != MCU1_CPU1_ID) && (core_id != MCU1_CPU0_ID)))
                {
                    SBL_SlaveCoreBoot(core_id, 0, &gK3xx_evmEntry, SBL_REQUEST_CORE);
                    UART_printf("SBL_SlaveCoreBoot completed for Core ID#%d, Entry point is 0x%x\n",
                                    core_id, gK3xx_evmEntry.CpuEntryPoint[core_id]);
                    booted_core_ids[num_booted_cores] = core_id;
                    time_boot_core_finish[num_booted_cores] = BootApp_GetTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));
                    num_booted_cores++;
                }
            }
        } /* if (retVal == CSL_PASS) */
    } /* for (j = 0; j < NUM_BOOT_STAGES; j++) */

#if defined(BOOT_MMCSD)
    BootApp_MMCBootImageDeInit();
#endif

#if defined(BOOT_OSPI)
    SBL_ospiClose(&boardHandle);

    BootApp_OSPILeaveConfigSPI();
#endif

    /* Delay print out of boot log to avoid prints by other tasks */
    TaskP_sleep(4000);

    if (retVal == CSL_PASS)
    {
        /* Print boot log, including all gathered timestamps */
        UART_printf("Boot App: Started at %d usec\n",
                        (uint32_t)gtimeBootAppStart);

        UART_printf("Boot App: Total Num booted cores = %d\n",
                        num_booted_cores);

        for (core_id = 0; core_id < num_booted_cores; core_id++)
        {
            UART_printf("Boot App: Booted Core ID #%d at %d usecs\n",
                            booted_core_ids[core_id],
                            (uint32_t)time_boot_core_finish[core_id]);
        }
    } /* if (retVal == CSL_PASS) */
    else
    {
        UART_printf("Boot App: Failure occurred in boot sequence\n");
    }

    return (retVal);
}

static int32_t BootApp_RequestStageCores(uint8_t stageNum)
{
    uint32_t i;
    int32_t  status = CSL_EFAIL;
    uint8_t  stage  = stageNum;

    for (i = 0; i < MAX_CORES_PER_STAGE; i++)
    {
        if (sbl_late_slave_core_stages_info[stage][i].tisci_proc_id != SBL_INVALID_ID)
        {
            #if defined(UART_PRINT_DEBUG)
                UART_printf("Calling Sciclient_procBootRequestProcessor, ProcId 0x%x... \n",
                            sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
            #endif
            status = Sciclient_procBootRequestProcessor(sbl_late_slave_core_stages_info[stage][i].tisci_proc_id,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != CSL_PASS)
            {
                #if defined(UART_PRINT_DEBUG)
                    UART_printf("Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED \n",
                                        sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
                #endif
                break;
            }
        }
    }

    return (status);
}

static int32_t BootApp_ReleaseStageCores(uint8_t stageNum)
{
    uint32_t i;
    int32_t  status   = CSL_EFAIL;
    uint8_t  stage  = stageNum;

    for (i = 0; i < MAX_CORES_PER_STAGE; i++)
    {
        if (sbl_late_slave_core_stages_info[stage][i].tisci_proc_id != SBL_INVALID_ID)
        {
            #if defined(UART_PRINT_DEBUG)
                UART_printf("Sciclient_procBootReleaseProcessor, ProcId 0x%x...\n",
                            sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
            #endif
            status = Sciclient_procBootReleaseProcessor(sbl_late_slave_core_stages_info[stage][i].tisci_proc_id,
                                                        TISCI_MSG_FLAG_AOP,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != CSL_PASS)
            {
                UART_printf("Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \n",
                            sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
                break;
            }
        }
    }

    return (status);
}

void BootApp_ArmR5PmuCntrInit()
{
    uint32_t val;
    CSL_armR5PmuCfg(0, 0, 1);
    /* Clear the overflow */
    val = CSL_armR5PmuReadCntrOverflowStatus();
    val &= 0x80000000;
    CSL_armR5PmuClearCntrOverflowStatus(val);
    CSL_armR5PmuCfgCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM, CSL_ARM_R5_PMU_EVENT_TYPE_CYCLE_CNT);
    CSL_armR5PmuEnableAllCntrs(1);
    CSL_armR5PmuEnableCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM, 1);
}

uint32_t BootApp_GetTimeInMicroSec(uint32_t pmuCntrVal){
    uint64_t mcu_clk_freq = SBL_MCU1_CPU0_FREQ_HZ;
    uint32_t cycles_per_usec = (mcu_clk_freq / 1000000);
    return (pmuCntrVal/cycles_per_usec);
}

#if defined(MPU1_HLOS_BOOT_ENABLED)
/* Function to clean the MCU R5 cache for a given start address and given memory size */
void BootApp_McuDCacheClean(void *addr, uint32_t size)
{
    /* Invalidate by MVA */
    CSL_armR5CacheWbInv((const void *)addr, uint32_to_int32(size), (bool)TRUE);
}
#endif

static void BootApp_AppSetup(void)
{
#if defined(SOC_J721E)
    Board_STATUS status;

    /* Ethernet config: set proper board muxes for J712E Eth. firmware */
    /* Set IO Expander to use RMII on GESI board */
    status = Board_control(BOARD_CTRL_CMD_SET_RMII_DATA_MUX, NULL);
    if (status != BOARD_SOK)
    {
        UART_printf("Board_control failed to configure RMII pins\n");
    }
    /* Enable CPSW9G MDIO mux */
    status = Board_control(BOARD_CTRL_CMD_SET_GESI_CPSW_MDIO_MUX, NULL);
    if (status != BOARD_SOK)
    {
        UART_printf("Board_control failed to configure CPSW9G MDIO mux\n");
    }
#endif
}

uint32_t BootApp_SetupSciServer(void)
{
    #if (defined (BUILD_MCU1_0) && (defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)))
        Sciserver_TirtosCfgPrms_t appPrms;
        Sciclient_ConfigPrms_t clientPrms;
        uint32_t ret = CSL_PASS;

        appPrms.taskPriority[SCISERVER_TASK_USER_LO] = 1;
        appPrms.taskPriority[SCISERVER_TASK_USER_HI] = 4;

        /* Sciclient needs to be initialized before Sciserver. Sciserver depends on
        * Sciclient API to execute message forwarding */
        ret = Sciclient_configPrmsInit(&clientPrms);
        if (ret == CSL_PASS)
        {
            ret = Sciclient_init(&clientPrms);
        }

        if (ret == CSL_PASS)
        {
            ret = Sciserver_tirtosInit(&appPrms);
        }

        if (ret == CSL_PASS)
        {
            UART_printf("Starting Sciserver..... PASSED\n");
        }
        else
        {
            UART_printf("Starting Sciserver..... FAILED\n");
        }

    #endif
    return ret;
}
