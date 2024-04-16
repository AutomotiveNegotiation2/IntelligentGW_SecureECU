/*
 *  Copyright (C) 2017-2020 Texas Instruments Incorporated
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

#ifndef SDLR_SOC_IN_H
#define SDLR_SOC_IN_H

#include <sdl_psilcfg_thread_map.h>
#include <sdl_soc_isc.h>
#include <sdl_soc_qos.h>
#include <sdlr_soc_intr.h>
#include <sdlr_navss_defines.h>
#include <sdlr_soc_baseaddress.h>
#include <sdlr_soc_c66_baseaddress.h>
#include <sdlr_soc_defines.h>
#include <sdlr_soc_mcu_r5_baseaddress.h>
#include <sdlr_soc_main_r5_baseaddress.h>
#include <sdlr_main_ctrl_mmr.h>
#include <sdlr_mcu_ctrl_mmr.h>
#include <sdlr_wkup_ctrl_mmr.h>
#include <sdl_soc_firewalls.h>
#include <sdlr_soc_pbist.h>

/* Temp changes needed to get osal_nonos to build for J721E/C66x.  Obviously this
 * is not the right thing to do and needs to be replaced with suitable SDL
 * update to support the C66x definitions.  Tracked in PDK-2934.
 */
#define SDL_C66X_COREPAC_REG_BASE_ADDRESS_REGS                                  (0x1800000U)
#define SOC_DSP_XMC_CTRL_BASE                                                   (0x8000000U)
#define SDL_DSP_DSP_XMC_CTRL_REGS                                               (SOC_DSP_XMC_CTRL_BASE)
#define SDL_COMPUTE_CLUSTER0_DRU_BASE                                           (0x6d000000UL)
#define SDL_COMPUTE_CLUSTER0_DRU_SIZE                                           (0x1000000UL)


#ifndef SDL_MODIFICATION
#define SDL_SOC_DSP_L1P_BASE               (SDL_C66X_COREPAC_LOCAL_L1P_SRAM_REGS)
#define SDL_SOC_DSP_L1D_BASE               (SDL_C66X_COREPAC_LOCAL_L1D_SRAM_REGS)
#define SDL_SOC_DSP_L2_BASE                (SDL_C66X_COREPAC_LOCAL_L2_SRAM_REGS)
#define SDL_SOC_DSP_ICFG_BASE              (SDL_C66X_COREPAC_REG_BASE_ADDRESS_REGS - 0x800000U)
#define SDL_C66X_COREPAC_LOCAL_L2_SRAM_REGS  (0x00800000)
#define SDL_C66X_COREPAC_LOCAL_L1P_SRAM_REGS  (0x00E00000)
#define SDL_C66X_COREPAC_LOCAL_L1D_SRAM_REGS  (0x00F00000)
#endif

/* Manual changes needed for VTM EFUSE register reads for J721E */
#define SDL_VTM_EFUSE_BASE_ADDR                             (0x43000300UL)


/* Manual changes to support LBIST base Addresses */
#define SDL_DMSC_LBIST_BASE      (SDL_WKUP_CTRL_MMR0_CFG0_BASE+SDL_WKUP_CTRL_MMR_CFG0_DMSC_LBIST_CTRL)
#define SDL_MCU_LBIST_BASE       (SDL_MCU_CTRL_MMR0_CFG0_BASE+SDL_MCU_CTRL_MMR_CFG0_MCU_LBIST_CTRL)
#define SDL_MAIN_R5F0_LBIST_BASE (SDL_CTRL_MMR0_CFG0_BASE+SDL_MAIN_CTRL_MMR_CFG0_MCU0_LBIST_CTRL)
#define SDL_MAIN_R5F1_LBIST_BASE (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_MCU1_LBIST_CTRL)
#define SDL_C7X_LBIST_BASE       (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_DSP0_LBIST_CTRL)
#define SDL_VPAC_LBIST_BASE      (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_VPAC_LBIST_CTRL)
#define SDL_DMPAC_LBIST_BASE     (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_DMPAC_LBIST_CTRL)
#define SDL_A72_LBIST_BASE       (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_MPU0_LBIST_CTRL)

#define SDL_DMSC_LBIST_SIG      (SDL_WKUP_CTRL_MMR0_CFG0_BASE + SDL_WKUP_CTRL_MMR_CFG0_DMSC_LBIST_SIG)
#define SDL_MCU_LBIST_SIG       (SDL_MCU_CTRL_MMR0_CFG0_BASE + SDL_MCU_CTRL_MMR_CFG0_MCU_LBIST_SIG)
#define SDL_MAIN_R5F0_LBIST_SIG (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_MCU0_LBIST_SIG)
#define SDL_MAIN_R5F1_LBIST_SIG (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_MCU1_LBIST_SIG)
#define SDL_C7X_LBIST_SIG       (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_DSP0_LBIST_SIG)
#define SDL_VPAC_LBIST_SIG      (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_VPAC_LBIST_SIG)
#define SDL_DMPAC_LBIST_SIG     (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_DMPAC_LBIST_SIG)
#define SDL_A72_LBIST_SIG       (SDL_CTRL_MMR0_CFG0_BASE + SDL_MAIN_CTRL_MMR_CFG0_MPU0_LBIST_SIG)


#endif /* SDLR_SOC_IN_H */
