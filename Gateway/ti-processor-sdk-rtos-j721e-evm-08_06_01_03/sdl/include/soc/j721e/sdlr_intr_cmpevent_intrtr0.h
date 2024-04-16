/********************************************************************
*
* CMPEVENT_INTRTR0 INTERRUPT MAP. header file
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
#ifndef SDLR_CMPEVENT_INTRTR0_INTERRUPT_MAP_H_
#define SDLR_CMPEVENT_INTRTR0_INTERRUPT_MAP_H_

#include <sdlr.h>
#include <tistdtypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

/*
* List of intr sources for receiver: CMPEVENT_INTRTR0
*/

#define SDLR_CMPEVENT_INTRTR0_IN_PCIE0_PCIE_CPTS_COMP_0                                            (4U)
#define SDLR_CMPEVENT_INTRTR0_IN_PCIE1_PCIE_CPTS_COMP_0                                            (5U)
#define SDLR_CMPEVENT_INTRTR0_IN_PCIE2_PCIE_CPTS_COMP_0                                            (6U)
#define SDLR_CMPEVENT_INTRTR0_IN_PCIE3_PCIE_CPTS_COMP_0                                            (7U)
#define SDLR_CMPEVENT_INTRTR0_IN_NAVSS0_CPTS0_COMP_0                                               (8U)
#define SDLR_CMPEVENT_INTRTR0_IN_CPSW0_CPTS_COMP_0                                                 (9U)
#define SDLR_CMPEVENT_INTRTR0_IN_MCU_CPSW0_CPTS_COMP_0                                             (10U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_0                                    (16U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_1                                    (17U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_2                                    (18U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_3                                    (19U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_4                                    (20U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_5                                    (21U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_6                                    (22U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_HOST_INTR_REQ_7                                    (23U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_0                                    (24U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_1                                    (25U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_2                                    (26U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_3                                    (27U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_4                                    (28U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_5                                    (29U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_6                                    (30U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_HOST_INTR_REQ_7                                    (31U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_0                                (32U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_1                                (33U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_2                                (34U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_3                                (35U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_4                                (36U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_5                                (37U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_6                                (38U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_7                                (39U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_8                                (40U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_9                                (41U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_10                               (42U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_11                               (43U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_12                               (44U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_13                               (45U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_14                               (46U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP0_CMP_INTR_REQ_15                               (47U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_0                                (48U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_1                                (49U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_2                                (50U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_3                                (51U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_4                                (52U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_5                                (53U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_6                                (54U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_7                                (55U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_8                                (56U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_9                                (57U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_10                               (58U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_11                               (59U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_12                               (60U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_13                               (61U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_14                               (62U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG0_PR1_IEP1_CMP_INTR_REQ_15                               (63U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_0                                (64U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_1                                (65U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_2                                (66U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_3                                (67U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_4                                (68U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_5                                (69U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_6                                (70U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_7                                (71U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_8                                (72U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_9                                (73U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_10                               (74U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_11                               (75U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_12                               (76U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_13                               (77U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_14                               (78U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP0_CMP_INTR_REQ_15                               (79U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_0                                (80U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_1                                (81U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_2                                (82U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_3                                (83U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_4                                (84U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_5                                (85U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_6                                (86U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_7                                (87U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_8                                (88U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_9                                (89U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_10                               (90U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_11                               (91U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_12                               (92U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_13                               (93U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_14                               (94U)
#define SDLR_CMPEVENT_INTRTR0_IN_PRU_ICSSG1_PR1_IEP1_CMP_INTR_REQ_15                               (95U)

#ifdef __cplusplus
}
#endif
#endif /* SDLR_CMPEVENT_INTRTR0_INTERRUPT_MAP_H_ */

