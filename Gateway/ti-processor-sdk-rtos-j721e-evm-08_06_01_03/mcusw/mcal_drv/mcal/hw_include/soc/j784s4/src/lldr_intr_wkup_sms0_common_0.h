/********************************************************************
*
* WKUP_SMS0_COMMON_0 INTERRUPT MAP. header file
*
* Copyright (C) 2023 Texas Instruments Incorporated.
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
#ifndef LLDR_WKUP_SMS0_COMMON_0_INTERRUPT_MAP_H_
#define LLDR_WKUP_SMS0_COMMON_0_INTERRUPT_MAP_H_

#include <hw_include/lldr.h>
#include <hw_include/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: WKUP_SMS0_COMMON_0
*/

#define CSLR_WKUP_SMS0_COMMON_0_DEBUG_FORCEACTIVE_WKUP_DDPA0_DDPA_INTR_0                           (0U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_WKUP_CBASS0_DEFAULT_EXP_0                                   (0U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_MCU_CBASS0_DEFAULT_EXP_0                                    (1U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_MAIN_CBASS0_DEFAULT_EXP_0                                   (3U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_INFRA_NON_SAFE0_DEFAULT_EXP_0                         (4U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_CSI0_DEFAULT_EXP_0                                    (5U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_IPPHY0_DEFAULT_EXP_0                                  (6U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_IPPHY_SAFE0_DEFAULT_EXP_0                             (7U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_DATADEBUG0_DEFAULT_EXP_0                              (10U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_HC2_0_DEFAULT_EXP_0                                   (11U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_HC_CFG0_DEFAULT_EXP_0                                 (12U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_RC0_DEFAULT_EXP_0                                     (13U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_RC_CFG0_DEFAULT_EXP_0                                 (14U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_AC_CFG0_DEFAULT_EXP_0                                 (15U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_AC_CFG_NONSAFE0_DEFAULT_EXP_0                         (16U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_CBASS_AC_NONSAFE0_DEFAULT_EXP_0                             (17U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_AM_PULSAR0_SLV_CBASS0_DEFAULT_EXP_0                         (18U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_AM_PULSAR0_MEM_CBASS0_DEFAULT_EXP_0                         (19U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_EN_MSMC_DOMAIN_0_ARM0_EN_FW_EXP_0          (20U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_EN_MSMC_DOMAIN_0_ARM1_EN_FW_EXP_0          (21U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_CORE_CORE_DRU_0_MST_FW_EXP_0               (24U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_CORE_CORE_DRU_0_SLV_FW_EXP_0               (25U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS0_CORE0_0_AC71_4_EXP_L2PIPE_0         (26U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS0_CORE0_0_AC71_4_EXP_MDMA_0           (27U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_NAVSS0_MODSS_DEFAULT_EXP_0                                  (28U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_NAVSS0_VIRTSS_DEFAULT_EXP_0                                 (29U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_NAVSS0_UDMASS_DEFAULT_EXP_0                                 (30U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_AM_PULSAR1_MEM_CBASS0_DEFAULT_EXP_0                         (31U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_SA2_UL0_COMMON_0_SECURITY_0                                 (32U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS1_CORE0_0_AC71_5_EXP_L2PIPE_0         (36U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS1_CORE0_0_AC71_5_EXP_MDMA_0           (37U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS2_CORE0_0_AC71_6_EXP_L2PIPE_0         (38U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS2_CORE0_0_AC71_6_EXP_MDMA_0           (39U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_DMPAC0_MISC_0_CFG_EXP_0                                     (40U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_DMPAC0_MISC_0_SL2_EXP_0                                     (41U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_VPAC0_COMMON_0_VPAC_SCRM_0                                  (42U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_VPAC0_COMMON_0_VPAC_SCRP_0                                  (43U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_VPAC1_COMMON_0_VPAC_SCRM_0                                  (44U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_VPAC1_COMMON_0_VPAC_SCRP_0                                  (45U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS3_CORE0_0_AC71_7_EXP_L2PIPE_0         (46U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS3_CORE0_0_AC71_7_EXP_MDMA_0           (47U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_MCU_NAVSS0_MODSS_DEFAULT_EXP_0                              (48U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_MCU_SA3_SS0_SA_UL_0_SECURITY_0                              (49U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS0_0_AW4_DRU_0_MST_FW_EXP_0            (50U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS0_0_AW4_DRU_0_SLV_FW_EXP_0            (51U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS1_0_AW5_DRU_0_MST_FW_EXP_0            (52U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS1_0_AW5_DRU_0_SLV_FW_EXP_0            (53U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS2_0_AW6_DRU_0_MST_FW_EXP_0            (54U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS2_0_AW6_DRU_0_SLV_FW_EXP_0            (55U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS3_0_AW7_DRU_0_MST_FW_EXP_0            (56U)
#define CSLR_WKUP_SMS0_COMMON_0_SEC_IN_COMPUTE_CLUSTER0_C71SS3_0_AW7_DRU_0_SLV_FW_EXP_0            (57U)

#ifdef __cplusplus
}
#endif
#endif /* LLDR_WKUP_SMS0_COMMON_0_INTERRUPT_MAP_H_ */

