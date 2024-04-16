/*
 *  Copyright (c) Texas Instruments Incorporated 2018
 *  All rights reserved.
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
 */

/**
 *  \ingroup DRV_IPC_MODULE
 *  \defgroup DRV_IPC_SOC_MODULE IPC SoC Config
 *            This is IPC documentation specific to J784S4 SoC
 *
 *  @{
 */

/**
 *  \file ipc_soc.h
 *
 *  \brief IPC Low Level Driver J7 SOC specific file.
 */
#ifndef IPC_SOC_V3_H_
#define IPC_SOC_V3_H_

#include <CddIpc/ipc_baremetal_hw/include/ipc_config.h>
#include "Cdd_IpcCfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief VRing Buffer Size required for all core
 * combinations.
 * TBD: This number can be smaller, if needed, for # cores on J721S2
 */
#define IPC_VRING_BUFFER_SIZE   (0x3000000U)

/*
 * For VLAB toolbox 0.14.5.snapshot2 onward,
 * this must be defined for C66x interrupt to work
 * properly.
 */
#define    SUPPORT_C66X_BIT0

#define    IPC_MAILBOX_USER_CNT                  (4U)
#define    MAIN_NAVSS_MAILBOX_INPUTINTR_MAX    (440U)
#define    MAIN_NAVSS_MAILBOX_OUTPUTINTR_MAX   (512U)



/* Refer to J784S4 interrupt mapping table */
#ifndef QNX_OS
#define    NAVSS512_MPU1_0_INPUT_MAILBOX_OFFSET             (105U)
#define    NAVSS512_MPU1_0_INPUT_MAILBOX_VIM_OFFSET         (457U)
#else
#define    NAVSS512_MPU1_0_INPUT_MAILBOX_OFFSET             (91U)
#define    NAVSS512_MPU1_0_INPUT_MAILBOX_VIM_OFFSET         (475U)
#endif
#define    NAVSS512_MCU1R5F0_INPUT_MAILBOX_OFFSET           (400U)
#define    NAVSS512_MCU1R5F0_INPUT_MAILBOX_VIM_OFFSET       (376U)
#define    NAVSS512_MCU1R5F1_INPUT_MAILBOX_OFFSET           (404U)
#define    NAVSS512_MCU1R5F1_INPUT_MAILBOX_VIM_OFFSET       (380U)
#define    NAVSS512_MCU2R5F0_INPUT_MAILBOX_OFFSET           (219U)
#define    NAVSS512_MCU2R5F0_INPUT_MAILBOX_VIM_OFFSET       (251U)
#define    NAVSS512_MCU2R5F1_INPUT_MAILBOX_OFFSET           (251U)
#define    NAVSS512_MCU2R5F1_INPUT_MAILBOX_VIM_OFFSET       (251U)
#define    NAVSS512_MCU4R5F0_INPUT_MAILBOX_OFFSET           (347U)
#define    NAVSS512_MCU3R5F0_INPUT_MAILBOX_VIM_OFFSET       (251U)
#define    NAVSS512_MCU3R5F0_INPUT_MAILBOX_OFFSET           (280U)
#define    NAVSS512_MCU3R5F1_INPUT_MAILBOX_OFFSET           (312U)
#define    NAVSS512_MCU4R5F1_INPUT_MAILBOX_OFFSET           (379U)
#define    NAVSS512_MCU3R5F1_INPUT_MAILBOX_VIM_OFFSET       (251U)
#define    NAVSS512_MCU4R5F0_INPUT_MAILBOX_OFFSET           (283U)
#define    NAVSS512_MCU4R5F0_INPUT_MAILBOX_VIM_OFFSET       (251U)
#define    NAVSS512_MCU4R5F1_INPUT_MAILBOX_OFFSET           (315U)
#define    NAVSS512_MCU4R5F1_INPUT_MAILBOX_VIM_OFFSET       (251U)
#define    NAVSS512_C7X1_INPUT_MAILBOX_OFFSET               (126U)
#define    NAVSS512_C7X1_INPUT_MAILBOX_VIM_OFFSET           (511U)
#define    NAVSS512_C7X2_INPUT_MAILBOX_OFFSET               (147U)
#define    NAVSS512_C7X2_INPUT_MAILBOX_VIM_OFFSET           (691U)
#define    NAVSS512_C7X3_INPUT_MAILBOX_OFFSET               (159U)
#define    NAVSS512_C7X3_INPUT_MAILBOX_VIM_OFFSET           (703U)
#define    NAVSS512_C7X4_INPUT_MAILBOX_OFFSET               (171U)
#define    NAVSS512_C7X4_INPUT_MAILBOX_VIM_OFFSET           (715U)

#define IPC_MCU_NAVSS0_INTR0_CFG_BASE    (CSL_NAVSS0_INTR0_INTR_ROUTER_CFG_BASE)

/* For C7x, DMSC does not configure or map CLEC router
 * it must be done by C7x software.
 */
#define   C7X_CLEC_BASE_ADDR              (CSL_COMPUTE_CLUSTER0_CLEC_BASE)

/* CLEC is shared b/w all C7x cores and the offset can be common.
 * ClecEvent # will be different for a particular C7x since the
 * range is returned from BoardCfg based on core specific allocation */
#define   C7X_CLEC_OFFSET                 (1024 - 32)


/* Request Sciclient for available resource in group2 NavSS
 * For C7x, DMSC does not configure or map CLEC router
 * it must be done by C7x software.
 * StartEvent = 672 (CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_128)
 * ClecEvent  = 1664 corresponds to 672
 */
#define   C7X_CLEC_BASE_ADDR              (CSL_COMPUTE_CLUSTER0_CLEC_REGS_BASE)

/* Base NAVSS event from group 2 */
#define   IPC_C7X_COMPUTE_CLUSTER_OFFSET  (CSLR_COMPUTE_CLUSTER0_GIC500SS_SPI_NAVSS0_INTR_ROUTER_0_OUTL_INTR_128)

/* CLEC event corresponding to Base NAVSS event */
#define   C7X1_CLEC_BASE_GR2_NAVSS        (1664U)

/* User selected IRQ number */
#define   C7X1_MBINTR_OFFSET            (59U)

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* @} */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
int32_t Ipc_getIntNumRange(uint32 coreIndex, uint16 *rangeStartP,
        uint16 *rangeNumP);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef IPC_SOC_V3_H_ */

/* @} */
