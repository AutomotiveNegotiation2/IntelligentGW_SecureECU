/********************************************************************
*
* VPAC0_INTD_0 INTERRUPT MAP. header file
*
* Copyright (C) 2015-2019 Texas Instruments Incorporated.
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
#ifndef SDLR_VPAC0_INTD_0_INTERRUPT_MAP_H_
#define SDLR_VPAC0_INTD_0_INTERRUPT_MAP_H_

#include <sdlr.h>
#include <tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: VPAC0_INTD_0
*/

#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_RAWFE_CFG_ERR_INTR_0                                (0U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_NSF4V_LINEMEM_CFG_ERR_INTR_0                        (1U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_GLBCE_CFG_ERR_INTR_0                                (2U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_FCFA_CFG_ERR_INTR_0                                 (3U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_FCC_CFG_ERR_INTR_0                                  (4U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_EE_CFG_ERR_0                                        (5U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_EE_SYNCOVF_ERR_0                                    (6U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_FCC_HIST_READ_ERR_INTR_0                            (7U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_NSF4V_HBLANK_ERR_INTR_0                             (8U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_NSF4V_VBLANK_ERR_INTR_0                             (9U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_GLBCE_HSYNC_ERR_INTR_0                              (10U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_GLBCE_VSYNC_ERR_INTR_0                              (11U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_GLBCE_VP_ERR_INTR_0                                 (12U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_LSE_CAL_VP_ERR_INTR_0                               (13U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_LSE_SL2_RD_ERR_INTR_0                               (14U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_LSE_SL2_WR_ERR_INTR_0                               (15U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_FCC_OUTIF_OVF_ERR_INTR_0                            (16U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_RAWFE_AEW_PULSE_INTR_0                              (17U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_RAWFE_AF_PULSE_INTR_0                               (18U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_RAWFE_H3A_PULSE_INTR_0                              (19U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_RAWFE_H3A_BUF_OVRFLOW_PULSE_INTR_0                  (20U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_GLBCE_FILT_START_INTR_0                             (21U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_GLBCE_FILT_DONE_INTR_0                              (22U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_LSE_FR_DONE_EVT_INTR_0                              (23U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VISS_0_LSE_OUT_FR_START_EVT_INTR_0                         (24U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_PIX_IBLK_OUTOFBOUND_INTR_0                       (32U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_MESH_IBLK_OUTOFBOUND_INTR_0                      (33U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_PIX_IBLK_MEMOVF_INTR_0                           (34U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_MESH_IBLK_MEMOVF_INTR_0                          (35U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_IFR_OUTOFBOUND_INTR_0                            (36U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_INT_SZOVF_INTR_0                                 (37U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_FR_DONE_EVT_INTR_0                               (38U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_SL2_WR_ERR_INTR_0                                (39U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_LDC_0_LDC_VBUSM_RD_ERR_INTR_0                              (40U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_MSC_0_MSC_LSE_FR_DONE_EVT_0_INTR_0                         (64U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_MSC_0_MSC_LSE_FR_DONE_EVT_1_INTR_0                         (65U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_MSC_0_MSC_LSE_SL2_RD_ERR_INTR_0                            (66U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_MSC_0_MSC_LSE_SL2_WR_ERR_INTR_0                            (67U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VPAC_NF_0_NF_FR_DONE_INTR_0                                (72U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VPAC_NF_0_NF_SL2_WR_ERR_INTR_0                             (73U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_VPAC_NF_0_NF_SL2_RD_ERR_INTR_0                             (74U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_0                                          (96U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_1                                          (97U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_2                                          (98U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_3                                          (99U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_4                                          (100U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_5                                          (101U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_PIPE_DONE_6                                          (102U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_TDONE_0                                              (103U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_TDONE_2                                              (105U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_TDONE_4                                              (107U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_TDONE_5                                              (108U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_TDONE_6                                              (109U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_SPARE_DEC_0                                          (110U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_SPARE_DEC_1                                          (111U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_SPARE_PEND_PULSE_0                                   (112U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_SPARE_PEND_LEVEL_0                                   (113U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_SPARE_PEND_PULSE_1                                   (114U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_SPARE_PEND_LEVEL_1                                   (115U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_WATCHDOGTIMER_ERR_0                                  (116U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_WATCHDOGTIMER_ERR_2                                  (118U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_WATCHDOGTIMER_ERR_4                                  (120U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_WATCHDOGTIMER_ERR_5                                  (121U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_HTS_0_WATCHDOGTIMER_ERR_6                                  (122U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_0                              (128U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_1                              (129U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_2                              (130U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_3                              (131U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_4                              (132U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_5                              (133U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_6                              (134U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_7                              (135U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_8                              (136U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_9                              (137U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_10                             (138U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_11                             (139U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_12                             (140U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_13                             (141U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_14                             (142U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_15                             (143U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_16                             (144U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_17                             (145U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_18                             (146U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_19                             (147U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_20                             (148U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_21                             (149U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_22                             (150U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_23                             (151U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_24                             (152U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_25                             (153U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_26                             (154U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_27                             (155U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_28                             (156U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_29                             (157U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_30                             (158U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_COMPLETE_INTR_31                             (159U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_0                             (160U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_1                             (161U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_2                             (162U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_3                             (163U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_4                             (164U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_5                             (165U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_6                             (166U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_7                             (167U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_8                             (168U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_9                             (169U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_10                            (170U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_11                            (171U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_12                            (172U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_13                            (173U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_14                            (174U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_15                            (175U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_16                            (176U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_17                            (177U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_18                            (178U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_19                            (179U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_20                            (180U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_21                            (181U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_22                            (182U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_23                            (183U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_24                            (184U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_25                            (185U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_26                            (186U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_27                            (187U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_28                            (188U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_29                            (189U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_30                            (190U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_31                            (191U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_32                            (192U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_33                            (193U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_34                            (194U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_35                            (195U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_36                            (196U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_37                            (197U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_38                            (198U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_39                            (199U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_40                            (200U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_41                            (201U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_42                            (202U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_43                            (203U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_44                            (204U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_45                            (205U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_46                            (206U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_47                            (207U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_48                            (208U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_49                            (209U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_50                            (210U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_51                            (211U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_52                            (212U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_53                            (213U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_54                            (214U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_55                            (215U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_56                            (216U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_57                            (217U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_58                            (218U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_59                            (219U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_60                            (220U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_61                            (221U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_62                            (222U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_COMPLETE_INTR_63                            (223U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_ERR_0                                        (224U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_ERR_0                                       (225U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_RT_0_DRU0_PROT_ERR_INTR_0                              (226U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_UTC_NRT_0_DRU1_PROT_ERR_INTR_0                             (227U)
#define SDLR_VPAC0_INTD_0_IP_INTR_VPAC0_CTSET_0_CTM_PULSE_INTR_0                                   (228U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_VPAC0_INTD_0_INTERRUPT_MAP_H_ */

