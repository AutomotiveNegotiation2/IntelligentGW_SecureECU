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
 *  \file    sdl_pok.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of POK.
 *            This also contains some related macros.
 */

#ifndef SDL_POK_H_
#define SDL_POK_H_
 
#include <src/ip/sdl_ip_pok.h>
#include <src/ip/sdl_ip_esm.h>
#include <osal/sdl_osal.h>

#if defined (SOC_J721E)
#include <include/soc/j721e/sdlr_soc_baseaddress.h>
#include <include/soc/j721e/sdlr_wkup_ctrl_mmr.h>
#endif /* SOC_J721E */

#ifdef __cplusplus
extern "C" {
#endif

/** 
 *
 * @ingroup  SDL_MODULE
 * @defgroup SDL_POK_API Power OK(POK)
 *   Provides the APIs for POK.
 *
 */

/**
@defgroup SDL_POK_DATASTRUCT  POK Data Structures
@ingroup SDL_POK_API
*/
/**
@defgroup SDL_POK_FUNCTION  POK Functions
@ingroup SDL_POK_API
*/

/**************************************************************************
* Register Macros
**************************************************************************/
#define SDL_WKUP_ESM0_CFG_BASE          (0x42080000U)
#define SDL_POK_MMR_BASE                (SDL_WKUP_CTRL_MMR0_CFG0_BASE)


#define WKUP_ESM_INSTANCE                   (SDL_WKUP_ESM0_CFG_BASE)
#define WKUP_ESM_INTID                      (SDLR_MCU_R5FSS0_CORE0_INTR_WKUP_ESM0_ESM_INT_HI_LVL_0)
#define WKUP_ESM_ERR_SIG_POKHV_UV           (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU_3POKS0_POK_PGOOD_OUT_N_TO_ESM_2)
#define WKUP_ESM_ERR_SIG_POKHV_OV           (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU_3POKS0_POK_PGOOD_OUT_N_TO_ESM_1)
#define WKUP_ESM_ERR_SIG_PORHV_UV           (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU_3POKS0_POK_PGOOD_OUT_N_TO_ESM_2)
#define WKUP_ESM_ERR_SIG_POKLV_UV           (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU_3POKS0_POK_PGOOD_OUT_N_TO_ESM_0)
#define WKUP_ESM_ERR_SIG_VDDA_IN            (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU0_POK_PGOOD_OUT_N_TO_ESM_0)
#define WKUP_ESM_ERR_SIG_VDDSHV_WKUP_GEN_UV (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU0_POK_PGOOD_OUT_N_TO_ESM_5)
#define WKUP_ESM_ERR_SIG_VDDR_MCU_UV        (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU0_POK_PGOOD_OUT_N_TO_ESM_4)
#define WKUP_ESM_ERR_SIG_VDD_MCU_OV         (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU0_POK_PGOOD_OUT_N_TO_ESM_1)
#define WKUP_ESM_ERR_SIG_VDDSHV_WKUP_GEN_OV (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU0_POK_PGOOD_OUT_N_TO_ESM_2)
#define WKUP_ESM_ERR_SIG_VDDR_MCU_OV        (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG_MCU0_POK_PGOOD_OUT_N_TO_ESM_3)
#define WKUP_ESM_ERR_SIG_VDD_CORE_UV        (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_7)
#define WKUP_ESM_ERR_SIG_VDD_CPU_UV         (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_6)
#define WKUP_ESM_ERR_SIG_VMON_EXT_UV        (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_5)
#define WKUP_ESM_ERR_SIG_VDDR_CORE_UV       (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_4)
#define WKUP_ESM_ERR_SIG_VDD_CORE_OV        (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_3)
#define WKUP_ESM_ERR_SIG_VDD_CPU_OV         (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_2)
#define WKUP_ESM_ERR_SIG_VMON_EXT_OV        (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_1)
#define WKUP_ESM_ERR_SIG_VDDR_CORE_OV       (SDLR_WKUP_ESM0_ESM_PLS_EVENT0_WKUP_PRG0_POK_PGOOD_OUT_N_TO_ESM_0)


#define  ESM_INSTANCE                      WKUP_ESM_INSTANCE
#define  ESM_INTID                         WKUP_ESM_INTID
#define  ESM_ERR_SIG_POKHV_UV              WKUP_ESM_ERR_SIG_POKHV_UV
#define  ESM_ERR_SIG_POKHV_OV              WKUP_ESM_ERR_SIG_POKHV_OV
#define  ESM_ERR_SIG_POKLV_UV              WKUP_ESM_ERR_SIG_POKLV_UV
#define  ESM_ERR_SIG_PORHV_UV              WKUP_ESM_ERR_SIG_PORHV_UV
#define  ESM_ERR_SIG_VDDA_IN               WKUP_ESM_ERR_SIG_VDDA_IN
#define  ESM_ERR_SIG_VDD_CORE_UV           WKUP_ESM_ERR_SIG_VDD_CORE_UV
#define  ESM_ERR_SIG_VDDSHV_WKUP_GEN_UV    WKUP_ESM_ERR_SIG_VDDSHV_WKUP_GEN_UV
#define  ESM_ERR_SIG_VDD_CPU_UV            WKUP_ESM_ERR_SIG_VDD_CPU_UV
#define  ESM_ERR_SIG_VDDR_MCU_UV           WKUP_ESM_ERR_SIG_VDDR_MCU_UV
#define  ESM_ERR_SIG_VMON_EXT_UV           WKUP_ESM_ERR_SIG_VMON_EXT_UV
#define  ESM_ERR_SIG_VDD_MCU_OV            WKUP_ESM_ERR_SIG_VDD_MCU_OV
#define  ESM_ERR_SIG_VDDR_CORE_UV          WKUP_ESM_ERR_SIG_VDDR_CORE_UV
#define  ESM_ERR_SIG_VDDSHV_WKUP_GEN_OV    WKUP_ESM_ERR_SIG_VDDSHV_WKUP_GEN_OV
#define  ESM_ERR_SIG_VDD_CORE_OV           WKUP_ESM_ERR_SIG_VDD_CORE_OV
#define  ESM_ERR_SIG_VDDR_MCU_OV           WKUP_ESM_ERR_SIG_VDDR_MCU_OV
#define  ESM_ERR_SIG_VDD_CPU_OV            WKUP_ESM_ERR_SIG_VDD_CPU_OV
#define  ESM_ERR_SIG_VDDR_CORE_OV          WKUP_ESM_ERR_SIG_VDDR_CORE_OV
#define  ESM_ERR_SIG_VMON_EXT_OV           WKUP_ESM_ERR_SIG_VMON_EXT_OV




/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** ===========================================================================
 *  @addtogroup SDL_POK_DATASTRUCT
    @{
 * ============================================================================
 */

/** ---------------------------------------------------------------------------
 * \brief POK Static Registers structure
 *
 * This structure defines the POK static configuration registers
 * ----------------------------------------------------------------------------
 */
typedef struct SDL_Pok_Static_Reg_read{
    uint8_t hystCtrl;
    /**< Hysteresis control value */
    uint8_t voltDetMode;
    /**< Voltage Detection Mode value */
    uint8_t trim;
    /**< trim value */
    bool porBGapOK;
    /**< POR Band Gap OK status */
    uint8_t porModuleStatus;
    /**< POR Module Status */
}SDL_POK_staticRegs;

/** @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** ===========================================================================
 *  @addtogroup SDL_POK_FUNCTION
    @{
 * ============================================================================
 */

/** ============================================================================
 *
 * \brief   POK Function to get the Static Registers.
 *          This function reads the values of the static registers such as
 *          hysteresis control, voltage detect mode, trim, PORGP and module
 *          status.
 *
 * \param   Instance: Instance of POK
 * \param   pStaticRegs: Pointer to the static registers structure
 *
 * \return  SDL_PASS for success. SDL Error Code for Failure.
 */
int32_t SDL_POK_getStaticRegisters(SDL_POK_Inst Instance,SDL_POK_staticRegs *pStaticRegs);

/** ============================================================================
 *
 * \brief   POK module configuration API
 *
 * \param   instance: Instance of POK
 * \param   pConfig: Pointer to the configuration structure
 *
 * \return  SDL_PASS for success. SDL Error Code for Failure.
 */
int32_t SDL_POK_init(SDL_POK_Inst instance, SDL_POK_config *pConfig);

/** ============================================================================
 *
 * \brief   POK Function to verify the written configuration.
 *          This function checks the provided config against the written config
 *          and returns the verification status.
 *
 * \param   instance: Instance of POK
 * \param   pConfig: Pointer to the configuration structure
 *
 * \return  SDL_PASS if configuration is verified to match.
 *          SDL Error Code for Failure.
 */
int32_t SDL_POK_verifyConfig(SDL_POK_Inst instance, SDL_POK_config *pConfig);

/** ============================================================================
 *
 * \brief   POK Function to get the threshold status of the POK instance.
 *
 * \param   instance: Instance of POK
 * \param   pStatus: Pointer to the threshold status
 *
 * \return  SDL_PASS for success. SDL Error Code for Failure.
 */
int32_t SDL_POK_getStatus(SDL_POK_Inst instance, SDL_POK_thrStatus *pStatus);

/** @} */

#ifdef __cplusplus
}
#endif
#endif /* SDL_POK_H_ */

