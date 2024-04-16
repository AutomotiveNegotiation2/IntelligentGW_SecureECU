/********************************************************************
*
* WKUP_HSM0 INTERRUPT MAP. header file
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
#ifndef LLDR_WKUP_HSM0_INTERRUPT_MAP_H_
#define LLDR_WKUP_HSM0_INTERRUPT_MAP_H_

#include <hw_include/lldr.h>
#include <hw_include/tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: WKUP_HSM0
*/

#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_DMTIMER_0_INTR_PEND_0                                        (8U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_DMTIMER_1_INTR_PEND_0                                        (10U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RAT_0_EXP_INTR_0                                             (11U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_0_WDG_INTR_4                                             (16U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_0_WDG_INTR_0                                             (17U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_0_WDG_INTR_1                                             (18U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_0_WDG_INTR_2                                             (19U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_0_WDG_INTR_3                                             (20U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_DMTIMER_2_INTR_PEND_0                                        (32U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_DMTIMER_3_INTR_PEND_0                                        (34U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_DBG_AUTH_0_DBG_AUTH_0                                        (36U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_AESEIP38T_0_AES_SINTREQUEST_S_0                              (38U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_AESEIP38T_0_AES_SINTREQUEST_P_0                              (39U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_24                                  (48U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_25                                  (49U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_26                                  (50U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_27                                  (51U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_28                                  (52U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_29                                  (53U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_30                                  (54U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_31                                  (55U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_56                                  (56U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_57                                  (57U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_58                                  (58U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_59                                  (59U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_60                                  (60U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_61                                  (61U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_62                                  (62U)
#define CSLR_WKUP_HSM0_NVIC_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_63                                  (63U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_56                                           (64U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_57                                           (65U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_58                                           (66U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_59                                           (67U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_60                                           (68U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_61                                           (69U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_62                                           (70U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_LVL_INTRTR0_OUTL_63                                           (71U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_40                                           (72U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_41                                           (73U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_42                                           (74U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_43                                           (75U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_44                                           (76U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_45                                           (77U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_46                                           (78U)
#define CSLR_WKUP_HSM0_NVIC_MAIN2MCU_PLS_INTRTR0_OUTP_47                                           (79U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_0                                  (80U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_1                                  (81U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_2                                  (82U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_3                                  (83U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_4                                  (84U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_5                                  (85U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_6                                  (86U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_INTAGGR_0_INTAGGR_VINTR_7                                  (87U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_SA_UL_0_SA_UL_PKA_0                                        (88U)
#define CSLR_WKUP_HSM0_NVIC_MCU_SA3_SS0_SA_UL_0_SA_UL_TRNG_0                                       (89U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RAT_1_EXP_INTR_0                                             (152U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_1_WDG_INTR_4                                             (155U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_1_WDG_INTR_0                                             (156U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_1_WDG_INTR_1                                             (157U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_1_WDG_INTR_2                                             (158U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_SMS0_RTI_1_WDG_INTR_3                                             (159U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_PORZ_SYNC0_MAIN_PORZ_LATCHED_0                                    (176U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_RESETZ_SYNC0_MAIN_RESETZ_LATCHED_0                                (178U)
#define CSLR_WKUP_HSM0_NVIC_GLUELOGIC_FW_CBASS_INTR_OR_GLUE_FW_CBASS_AGG_ERR_INTR_0                (179U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_I2C0_POINTRPEND_0                                                 (180U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_I2C0_CLKSTOP_WAKEUP_0                                             (181U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_UART0_USART_IRQ_0                                                 (182U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_UART0_CLKSTOP_WAKEUP_0                                            (183U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_0                                            (184U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_1                                            (185U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_2                                            (186U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_3                                            (187U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_4                                            (188U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_5                                            (189U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_6                                            (190U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_7                                            (191U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_8                                            (192U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_9                                            (193U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_10                                           (194U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIOMUX_INTRTR0_OUTP_11                                           (195U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH1_INTR_0                             (196U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_VTM0_COMMON_0_THERM_LVL_LT_TH0_INTR_0                             (197U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_VTM0_COMMON_0_THERM_LVL_GT_TH2_INTR_0                             (198U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_ESM0_ESM_INT_CFG_LVL_0                                            (199U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_ESM0_ESM_INT_LOW_LVL_0                                            (200U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_ESM0_ESM_INT_HI_LVL_0                                             (201U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_CTRL_MMR0_ACCESS_ERR_0                                            (202U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_PSC0_PSC_ALLINT_0                                                 (203U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIO0_GPIO_LVL_0                                                  (204U)
#define CSLR_WKUP_HSM0_NVIC_WKUP_GPIO1_GPIO_LVL_0                                                  (205U)
#define CSLR_WKUP_HSM0_NVIC_AM_BOLT_PSC_WRAP0_PSC_ALLINT_0                                         (206U)
#define CSLR_WKUP_HSM0_NVIC_MCU_PBIST1_DFT_PBIST_CPU_0                                             (211U)
#define CSLR_WKUP_HSM0_NVIC_MCU_PBIST2_DFT_PBIST_CPU_0                                             (212U)
#define CSLR_WKUP_HSM0_NVIC_GLUELOGIC_NONFW_CBASS_INTR_OR_GLUE_NONFW__CBASS_AGG_ERR_INTR_0         (213U)
#define CSLR_WKUP_HSM0_NVIC_MCU_I2C1_POINTRPEND_0                                                  (214U)
#define CSLR_WKUP_HSM0_NVIC_MCU_I2C1_CLKSTOP_WAKEUP_0                                              (215U)
#define CSLR_WKUP_HSM0_NVIC_GLUELOGIC_MCU_PULSAR_LBIST_GLUE_DFT_LBIST_BIST_DONE_0                  (216U)
#define CSLR_WKUP_HSM0_NVIC_MCU_PBIST0_DFT_PBIST_CPU_0                                             (217U)
#define CSLR_WKUP_HSM0_NVIC_MCU_CTRL_MMR0_IPC_SET8_IPC_SET_IPCFG_0                                 (218U)
#define CSLR_WKUP_HSM0_NVIC_MCU_CTRL_MMR0_ACCESS_ERR_0                                             (219U)
#define CSLR_WKUP_HSM0_NVIC_MCU_DCC0_INTR_DONE_LEVEL_0                                             (220U)
#define CSLR_WKUP_HSM0_NVIC_MCU_DCC1_INTR_DONE_LEVEL_0                                             (221U)
#define CSLR_WKUP_HSM0_NVIC_MCU_DCC2_INTR_DONE_LEVEL_0                                             (222U)
#define CSLR_WKUP_HSM0_NVIC_MCU_UART0_USART_IRQ_0                                                  (223U)
#define CSLR_WKUP_HSM0_NVIC_MCU_FSS0_OSPI_0_OSPI_LVL_INTR_0                                        (224U)
#define CSLR_WKUP_HSM0_NVIC_MCU_FSS0_OSPI_1_OSPI_LVL_INTR_0                                        (225U)
#define CSLR_WKUP_HSM0_NVIC_MCU_FSS0_HYPERBUS1P0_0_HPB_INTR_0                                      (226U)
#define CSLR_WKUP_HSM0_NVIC_MCU_FSS0_FSAS_0_OTFA_INTR_ERR_PEND_0                                   (227U)
#define CSLR_WKUP_HSM0_NVIC_MCU_FSS0_FSAS_0_ECC_INTR_ERR_PEND_0                                    (228U)
#define CSLR_WKUP_HSM0_NVIC_PSC0_PSC_ALLINT_0                                                      (229U)
#define CSLR_WKUP_HSM0_NVIC_MCU_I2C0_POINTRPEND_0                                                  (230U)
#define CSLR_WKUP_HSM0_NVIC_MCU_I2C0_CLKSTOP_WAKEUP_0                                              (231U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR0_WAKE_REQUEST_0              (232U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR0_WAKE_REQUEST_1              (233U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR0_WAKE_REQUEST_2              (234U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR0_WAKE_REQUEST_3              (235U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR1_WAKE_REQUEST_0              (236U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR1_WAKE_REQUEST_1              (237U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR1_WAKE_REQUEST_2              (238U)
#define CSLR_WKUP_HSM0_NVIC_COMPUTE_CLUSTER0_GIC_OUTPUT_WAKER_GIC_PWR1_WAKE_REQUEST_3              (239U)

#ifdef __cplusplus
}
#endif
#endif /* LLDR_WKUP_HSM0_INTERRUPT_MAP_H_ */

