/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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

/*!
 * \file  enet_soc.h
 *
 * \brief This file contains AM65xx SoC specific definition.
 */

#ifndef ENET_SOC_AM65XX_H_
#define ENET_SOC_AM65XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/drv/enet/include/core/enet_dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/*! \brief Max number of supported channels */
#define ENET_UDMA_NUM_RXCHAN_MAX      (2U)

/*! \brief CPSW HSDIV Clockout2 */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_CPSWHSDIV_CLKOUT2            (0x0U)
/*! \brief Main HSDIV Clockout3 */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_MAINHSDIV_CLKOUT3            (0x1U)
/*! \brief MCU CPTS RFT Clock */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_MCU_CPTS0_RFT_CLK            (0x2U)
/*! \brief CPTS RFT Clock */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_CPTS0_RFT_CLK                (0x3U)
/*! \brief MCU External Reference Clock */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_MCU_EXT_REFCLK0              (0x4U)
/*! \brief External Reference Clock */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_EXT_REFCLK1                  (0x5U)
/*! \brief PCIE0 TX IO Clock */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_PCIE0_TXI0_CLK               (0x6U)
/*! \brief PCIE1 TX IO Clock */
#define ENET_MCU_CPSW0_CPTS_CLKSEL_PCIE1_TXI0_CLK               (0x7U)

/*! \brief Number of TimeSyncRouter inputs */
#define ENET_TIMESYNCRTR_NUM_INPUT                              (48U)
/*! \brief Number of TimeSyncRouter outputs */
#define ENET_TIMESYNCRTR_NUM_OUTPUT                             (40U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* ENET_SOC_AM65XX_H_ */
