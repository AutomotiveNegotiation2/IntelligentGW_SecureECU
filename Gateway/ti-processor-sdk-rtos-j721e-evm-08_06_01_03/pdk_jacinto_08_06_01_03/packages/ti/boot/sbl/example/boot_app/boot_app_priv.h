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

/* Protection against multiple inclusion */
#ifndef BOOT_APP_PRIV_H_
#define BOOT_APP_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* files related to SBL */
#include <ti/boot/sbl/src/rprc/sbl_rprc_parse.h>
#include <ti/boot/sbl/src/mmcsd/sbl_mmcsd.h>
#include <ti/boot/sbl/src/ospi/sbl_ospi.h>
#include <ti/boot/sbl/soc/sbl_soc.h>
#include <ti/boot/sbl/soc/k3/sbl_slave_core_boot.h>
#include <ti/boot/sbl/soc/k3/sbl_soc_cfg.h>

/* files related to CSL */
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr.h>

/*files related to borad */
#include <ti/board/board.h>
#include <ti/board/board_cfg.h>
#include <ti/board/src/flash/include/board_flash.h>
#if defined(SOC_J721E)
#include <ti/board/src/j721e_evm/include/board_control.h>
#include <soc/j721e/boot_core_defs.h>
#endif
#if defined(SOC_J7200)
#include <ti/board/src/j7200_evm/include/board_control.h>
#include <soc/j7200/boot_core_defs.h>
#endif
#if defined(SOC_J721S2)
#include <ti/board/src/j721s2_evm/include/board_control.h>
#include <soc/j721s2/boot_core_defs.h>
#endif
#if defined(SOC_J784S4)
#include <ti/board/src/j784s4_evm/include/board_control.h>
#include <soc/j784s4/boot_core_defs.h>
#endif

/* files related to osal */
#include <ti/osal/osal.h>
#include <ti/osal/TaskP.h>

/* files related to uart */
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/uart/soc/UART_soc.h>

#include <ti/drv/spi/soc/SPI_soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const sblSlaveCoreInfo_t sbl_late_slave_core_info[];

extern const sblSlaveCoreInfo_t sbl_late_slave_core_stages_info[NUM_BOOT_STAGES]
                                                               [MAX_CORES_PER_STAGE];

extern const uint32_t ospi_main_domain_flash_rtos_images[NUM_BOOT_STAGES];

extern TCHAR mmcsd_main_domain_rtos_image_name[NUM_BOOT_STAGES]
                                              [MAX_APPIMAGE_NAME_LEN];

/* Defines boot order for the first stage of the Main Domain
 * boot sequence for J721E SOC */
extern cpu_core_id_t boot_order_first_stage[];

/* Defines boot order for the second stage of the Main Domain
 * boot sequence for J721E SOC */
extern cpu_core_id_t boot_order_second_stage[];

/* Points to boot order arrays for each of the boot stages */
extern cpu_core_id_t *boot_array_stage[];

/* Defines number of cores booted in each stage */
extern uint8_t num_cores_per_boot_stage[];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if defined(MPU1_HLOS_BOOT_ENABLED)
/* Function to clean the MCU R5 cache for a given start address and given memory size */
void BootApp_McuDCacheClean(void *addr, uint32_t size);
#endif

#ifdef __cplusplus
}
#endif

#endif /* BOOT_APP_PRIV_H_ */
