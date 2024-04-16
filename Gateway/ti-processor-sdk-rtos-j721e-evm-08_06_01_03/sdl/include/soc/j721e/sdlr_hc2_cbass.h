/********************************************************************
 * Copyright (C) 2018 Texas Instruments Incorporated.
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
 *  Name        : sdlr_hc2_cbass.h
*/
#ifndef SDLR_HC2_CBASS_H_
#define SDLR_HC2_CBASS_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <sdlr.h>
#include <stdint.h>

/**************************************************************************
* Hardware Region  : Global Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* Revision Register */
} SDL_hc2_cbass_glbRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_HC2_CBASS_GLB_PID                                                      (0x00000000U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define SDL_HC2_CBASS_GLB_PID_MINOR_MASK                                           (0x0000003FU)
#define SDL_HC2_CBASS_GLB_PID_MINOR_SHIFT                                          (0x00000000U)
#define SDL_HC2_CBASS_GLB_PID_MINOR_RESETVAL                                       (0x00000001U)
#define SDL_HC2_CBASS_GLB_PID_MINOR_MAX                                            (0x0000003FU)

#define SDL_HC2_CBASS_GLB_PID_CUSTOM_MASK                                          (0x000000C0U)
#define SDL_HC2_CBASS_GLB_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define SDL_HC2_CBASS_GLB_PID_CUSTOM_RESETVAL                                      (0x00000000U)
#define SDL_HC2_CBASS_GLB_PID_CUSTOM_MAX                                           (0x00000003U)

#define SDL_HC2_CBASS_GLB_PID_MAJOR_MASK                                           (0x00000700U)
#define SDL_HC2_CBASS_GLB_PID_MAJOR_SHIFT                                          (0x00000008U)
#define SDL_HC2_CBASS_GLB_PID_MAJOR_RESETVAL                                       (0x00000001U)
#define SDL_HC2_CBASS_GLB_PID_MAJOR_MAX                                            (0x00000007U)

#define SDL_HC2_CBASS_GLB_PID_RTL_MASK                                             (0x0000F800U)
#define SDL_HC2_CBASS_GLB_PID_RTL_SHIFT                                            (0x0000000BU)
#define SDL_HC2_CBASS_GLB_PID_RTL_RESETVAL                                         (0x00000008U)
#define SDL_HC2_CBASS_GLB_PID_RTL_MAX                                              (0x0000001FU)

#define SDL_HC2_CBASS_GLB_PID_FUNC_MASK                                            (0x0FFF0000U)
#define SDL_HC2_CBASS_GLB_PID_FUNC_SHIFT                                           (0x00000010U)
#define SDL_HC2_CBASS_GLB_PID_FUNC_RESETVAL                                        (0x00000600U)
#define SDL_HC2_CBASS_GLB_PID_FUNC_MAX                                             (0x00000FFFU)

#define SDL_HC2_CBASS_GLB_PID_BU_MASK                                              (0x30000000U)
#define SDL_HC2_CBASS_GLB_PID_BU_SHIFT                                             (0x0000001CU)
#define SDL_HC2_CBASS_GLB_PID_BU_RESETVAL                                          (0x00000002U)
#define SDL_HC2_CBASS_GLB_PID_BU_MAX                                               (0x00000003U)

#define SDL_HC2_CBASS_GLB_PID_SCHEME_MASK                                          (0xC0000000U)
#define SDL_HC2_CBASS_GLB_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define SDL_HC2_CBASS_GLB_PID_SCHEME_RESETVAL                                      (0x00000001U)
#define SDL_HC2_CBASS_GLB_PID_SCHEME_MAX                                           (0x00000003U)

#define SDL_HC2_CBASS_GLB_PID_RESETVAL                                             (0x66004101U)

/**************************************************************************
* Hardware Region  : Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_16[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_48[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_80[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_112[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL;   /* ISC Region 4 Control Register */
    volatile uint8_t  Resv_144[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L;   /* ISC Region 4 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H;   /* ISC Region 4 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L;   /* ISC Region 4 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H;   /* ISC Region 4 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL;   /* ISC Region 5 Control Register */
    volatile uint8_t  Resv_176[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L;   /* ISC Region 5 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H;   /* ISC Region 5 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L;   /* ISC Region 5 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H;   /* ISC Region 5 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL;   /* ISC Region 6 Control Register */
    volatile uint8_t  Resv_208[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L;   /* ISC Region 6 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H;   /* ISC Region 6 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L;   /* ISC Region 6 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H;   /* ISC Region 6 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL;   /* ISC Region 7 Control Register */
    volatile uint8_t  Resv_240[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L;   /* ISC Region 7 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H;   /* ISC Region 7 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L;   /* ISC Region 7 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H;   /* ISC Region 7 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_1024[764];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_1040[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_1072[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_1104[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_1136[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL;   /* ISC Region 4 Control Register */
    volatile uint8_t  Resv_1168[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L;   /* ISC Region 4 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H;   /* ISC Region 4 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L;   /* ISC Region 4 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H;   /* ISC Region 4 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL;   /* ISC Region 5 Control Register */
    volatile uint8_t  Resv_1200[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L;   /* ISC Region 5 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H;   /* ISC Region 5 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L;   /* ISC Region 5 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H;   /* ISC Region 5 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL;   /* ISC Region 6 Control Register */
    volatile uint8_t  Resv_1232[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L;   /* ISC Region 6 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H;   /* ISC Region 6 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L;   /* ISC Region 6 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H;   /* ISC Region 6 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL;   /* ISC Region 7 Control Register */
    volatile uint8_t  Resv_1264[12];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L;   /* ISC Region 7 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H;   /* ISC Region 7 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L;   /* ISC Region 7 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H;   /* ISC Region 7 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_2048[764];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_2064[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_2096[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_2128[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_2160[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL;   /* ISC Region 4 Control Register */
    volatile uint8_t  Resv_2192[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L;   /* ISC Region 4 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H;   /* ISC Region 4 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L;   /* ISC Region 4 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H;   /* ISC Region 4 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL;   /* ISC Region 5 Control Register */
    volatile uint8_t  Resv_2224[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L;   /* ISC Region 5 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H;   /* ISC Region 5 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L;   /* ISC Region 5 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H;   /* ISC Region 5 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL;   /* ISC Region 6 Control Register */
    volatile uint8_t  Resv_2256[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L;   /* ISC Region 6 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H;   /* ISC Region 6 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L;   /* ISC Region 6 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H;   /* ISC Region 6 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL;   /* ISC Region 7 Control Register */
    volatile uint8_t  Resv_2288[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L;   /* ISC Region 7 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H;   /* ISC Region 7 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L;   /* ISC Region 7 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H;   /* ISC Region 7 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_3072[764];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_3088[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_3120[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_3152[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_3184[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL;   /* ISC Region 4 Control Register */
    volatile uint8_t  Resv_3216[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L;   /* ISC Region 4 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H;   /* ISC Region 4 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L;   /* ISC Region 4 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H;   /* ISC Region 4 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL;   /* ISC Region 5 Control Register */
    volatile uint8_t  Resv_3248[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L;   /* ISC Region 5 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H;   /* ISC Region 5 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L;   /* ISC Region 5 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H;   /* ISC Region 5 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL;   /* ISC Region 6 Control Register */
    volatile uint8_t  Resv_3280[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L;   /* ISC Region 6 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H;   /* ISC Region 6 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L;   /* ISC Region 6 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H;   /* ISC Region 6 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL;   /* ISC Region 7 Control Register */
    volatile uint8_t  Resv_3312[12];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L;   /* ISC Region 7 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H;   /* ISC Region 7 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L;   /* ISC Region 7 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H;   /* ISC Region 7 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_4096[764];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_4112[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_4144[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_4176[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_4208[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL;   /* ISC Region 4 Control Register */
    volatile uint8_t  Resv_4240[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L;   /* ISC Region 4 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H;   /* ISC Region 4 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L;   /* ISC Region 4 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H;   /* ISC Region 4 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL;   /* ISC Region 5 Control Register */
    volatile uint8_t  Resv_4272[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L;   /* ISC Region 5 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H;   /* ISC Region 5 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L;   /* ISC Region 5 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H;   /* ISC Region 5 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL;   /* ISC Region 6 Control Register */
    volatile uint8_t  Resv_4304[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L;   /* ISC Region 6 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H;   /* ISC Region 6 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L;   /* ISC Region 6 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H;   /* ISC Region 6 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL;   /* ISC Region 7 Control Register */
    volatile uint8_t  Resv_4336[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L;   /* ISC Region 7 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H;   /* ISC Region 7 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L;   /* ISC Region 7 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H;   /* ISC Region 7 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_5120[764];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_5136[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL;   /* ISC Region 1 Control Register */
    volatile uint8_t  Resv_5168[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L;   /* ISC Region 1 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H;   /* ISC Region 1 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L;   /* ISC Region 1 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H;   /* ISC Region 1 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL;   /* ISC Region 2 Control Register */
    volatile uint8_t  Resv_5200[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L;   /* ISC Region 2 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H;   /* ISC Region 2 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L;   /* ISC Region 2 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H;   /* ISC Region 2 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL;   /* ISC Region 3 Control Register */
    volatile uint8_t  Resv_5232[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L;   /* ISC Region 3 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H;   /* ISC Region 3 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L;   /* ISC Region 3 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H;   /* ISC Region 3 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL;   /* ISC Region 4 Control Register */
    volatile uint8_t  Resv_5264[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L;   /* ISC Region 4 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H;   /* ISC Region 4 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L;   /* ISC Region 4 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H;   /* ISC Region 4 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL;   /* ISC Region 5 Control Register */
    volatile uint8_t  Resv_5296[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L;   /* ISC Region 5 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H;   /* ISC Region 5 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L;   /* ISC Region 5 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H;   /* ISC Region 5 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL;   /* ISC Region 6 Control Register */
    volatile uint8_t  Resv_5328[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L;   /* ISC Region 6 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H;   /* ISC Region 6 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L;   /* ISC Region 6 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H;   /* ISC Region 6 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL;   /* ISC Region 7 Control Register */
    volatile uint8_t  Resv_5360[12];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L;   /* ISC Region 7 Start Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H;   /* ISC Region 7 Start Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L;   /* ISC Region 7 End Address Low Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H;   /* ISC Region 7 End Address High Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_7168[1788];
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_7184[12];
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_8192[988];
    volatile uint32_t MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_8208[12];
    volatile uint32_t MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_9216[988];
    volatile uint32_t MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_9232[12];
    volatile uint32_t MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_12288[3036];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_12304[12];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_13312[988];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_13328[12];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_14336[988];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_14352[12];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
    volatile uint8_t  Resv_15360[988];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL;   /* ISC Region 0 Control Register */
    volatile uint8_t  Resv_15376[12];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L;   /* ISC Region 0 Start Address Low Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H;   /* ISC Region 0 Start Address High Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L;   /* ISC Region 0 End Address Low Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H;   /* ISC Region 0 End Address High Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL;   /* ISC Default Region Control Register */
} SDL_hc2_cbass_iscRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL              (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L      (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H      (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L        (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H        (0x0000001CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL              (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L      (0x00000030U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H      (0x00000034U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L        (0x00000038U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H        (0x0000003CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL              (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L      (0x00000050U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H      (0x00000054U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L        (0x00000058U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H        (0x0000005CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL              (0x00000060U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L      (0x00000070U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H      (0x00000074U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L        (0x00000078U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H        (0x0000007CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL              (0x00000080U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L      (0x00000090U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H      (0x00000094U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L        (0x00000098U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H        (0x0000009CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL              (0x000000A0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L      (0x000000B0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H      (0x000000B4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L        (0x000000B8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H        (0x000000BCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL              (0x000000C0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L      (0x000000D0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H      (0x000000D4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L        (0x000000D8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H        (0x000000DCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL              (0x000000E0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L      (0x000000F0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H      (0x000000F4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L        (0x000000F8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H        (0x000000FCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL            (0x00000100U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL              (0x00000400U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L      (0x00000410U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H      (0x00000414U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L        (0x00000418U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H        (0x0000041CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL              (0x00000420U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L      (0x00000430U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H      (0x00000434U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L        (0x00000438U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H        (0x0000043CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL              (0x00000440U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L      (0x00000450U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H      (0x00000454U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L        (0x00000458U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H        (0x0000045CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL              (0x00000460U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L      (0x00000470U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H      (0x00000474U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L        (0x00000478U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H        (0x0000047CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL              (0x00000480U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L      (0x00000490U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H      (0x00000494U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L        (0x00000498U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H        (0x0000049CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL              (0x000004A0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L      (0x000004B0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H      (0x000004B4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L        (0x000004B8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H        (0x000004BCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL              (0x000004C0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L      (0x000004D0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H      (0x000004D4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L        (0x000004D8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H        (0x000004DCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL              (0x000004E0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L      (0x000004F0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H      (0x000004F4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L        (0x000004F8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H        (0x000004FCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL            (0x00000500U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL              (0x00000800U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L      (0x00000810U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H      (0x00000814U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L        (0x00000818U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H        (0x0000081CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL              (0x00000820U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L      (0x00000830U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H      (0x00000834U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L        (0x00000838U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H        (0x0000083CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL              (0x00000840U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L      (0x00000850U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H      (0x00000854U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L        (0x00000858U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H        (0x0000085CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL              (0x00000860U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L      (0x00000870U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H      (0x00000874U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L        (0x00000878U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H        (0x0000087CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL              (0x00000880U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L      (0x00000890U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H      (0x00000894U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L        (0x00000898U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H        (0x0000089CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL              (0x000008A0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L      (0x000008B0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H      (0x000008B4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L        (0x000008B8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H        (0x000008BCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL              (0x000008C0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L      (0x000008D0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H      (0x000008D4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L        (0x000008D8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H        (0x000008DCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL              (0x000008E0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L      (0x000008F0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H      (0x000008F4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L        (0x000008F8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H        (0x000008FCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL            (0x00000900U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL              (0x00000C00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L      (0x00000C10U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H      (0x00000C14U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L        (0x00000C18U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H        (0x00000C1CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL              (0x00000C20U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L      (0x00000C30U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H      (0x00000C34U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L        (0x00000C38U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H        (0x00000C3CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL              (0x00000C40U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L      (0x00000C50U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H      (0x00000C54U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L        (0x00000C58U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H        (0x00000C5CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL              (0x00000C60U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L      (0x00000C70U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H      (0x00000C74U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L        (0x00000C78U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H        (0x00000C7CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL              (0x00000C80U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L      (0x00000C90U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H      (0x00000C94U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L        (0x00000C98U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H        (0x00000C9CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL              (0x00000CA0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L      (0x00000CB0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H      (0x00000CB4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L        (0x00000CB8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H        (0x00000CBCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL              (0x00000CC0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L      (0x00000CD0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H      (0x00000CD4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L        (0x00000CD8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H        (0x00000CDCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL              (0x00000CE0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L      (0x00000CF0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H      (0x00000CF4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L        (0x00000CF8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H        (0x00000CFCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL            (0x00000D00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL              (0x00001000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L      (0x00001010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H      (0x00001014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L        (0x00001018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H        (0x0000101CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL              (0x00001020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L      (0x00001030U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H      (0x00001034U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L        (0x00001038U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H        (0x0000103CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL              (0x00001040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L      (0x00001050U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H      (0x00001054U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L        (0x00001058U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H        (0x0000105CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL              (0x00001060U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L      (0x00001070U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H      (0x00001074U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L        (0x00001078U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H        (0x0000107CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL              (0x00001080U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L      (0x00001090U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H      (0x00001094U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L        (0x00001098U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H        (0x0000109CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL              (0x000010A0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L      (0x000010B0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H      (0x000010B4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L        (0x000010B8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H        (0x000010BCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL              (0x000010C0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L      (0x000010D0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H      (0x000010D4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L        (0x000010D8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H        (0x000010DCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL              (0x000010E0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L      (0x000010F0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H      (0x000010F4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L        (0x000010F8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H        (0x000010FCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL            (0x00001100U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL              (0x00001400U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L      (0x00001410U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H      (0x00001414U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L        (0x00001418U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H        (0x0000141CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL              (0x00001420U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L      (0x00001430U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H      (0x00001434U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L        (0x00001438U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H        (0x0000143CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL              (0x00001440U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L      (0x00001450U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H      (0x00001454U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L        (0x00001458U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H        (0x0000145CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL              (0x00001460U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L      (0x00001470U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H      (0x00001474U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L        (0x00001478U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H        (0x0000147CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL              (0x00001480U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L      (0x00001490U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H      (0x00001494U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L        (0x00001498U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H        (0x0000149CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL              (0x000014A0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L      (0x000014B0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H      (0x000014B4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L        (0x000014B8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H        (0x000014BCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL              (0x000014C0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L      (0x000014D0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H      (0x000014D4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L        (0x000014D8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H        (0x000014DCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL              (0x000014E0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L      (0x000014F0U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H      (0x000014F4U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L        (0x000014F8U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H        (0x000014FCU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL            (0x00001500U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL    (0x00001C00U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L (0x00001C10U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H (0x00001C14U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L (0x00001C18U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H (0x00001C1CU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL  (0x00001C20U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL     (0x00002000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L (0x00002010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H (0x00002014U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L (0x00002018U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H (0x0000201CU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL   (0x00002020U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL     (0x00002400U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L (0x00002410U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H (0x00002414U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L (0x00002418U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H (0x0000241CU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL   (0x00002420U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL (0x00003000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L (0x00003010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H (0x00003014U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L (0x00003018U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H (0x0000301CU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL (0x00003020U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL (0x00003400U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L (0x00003410U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H (0x00003414U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L (0x00003418U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H (0x0000341CU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL (0x00003420U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL (0x00003800U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L (0x00003810U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H (0x00003814U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L (0x00003818U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H (0x0000381CU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL (0x00003820U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL (0x00003C00U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L (0x00003C10U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H (0x00003C14U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L (0x00003C18U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H (0x00003C1CU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL (0x00003C20U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_4_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_5_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_6_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_7_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_MASK  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_DEF_MASK   (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_DEF_SHIFT  (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_DEF_MAX    (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_SEC_MASK   (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_SEC_SHIFT  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_SEC_MAX    (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PASS_MASK  (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PASS_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_MASK  (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTR0_ISC_REGION_DEF_CONTROL_RESETVAL   (0x00009B4AU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_4_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_5_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_6_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_7_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_MASK  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_DEF_MASK   (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_DEF_SHIFT  (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_DEF_MAX    (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_SEC_MASK   (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_SEC_SHIFT  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_SEC_MAX    (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PASS_MASK  (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PASS_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_MASK  (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_0_MSTW0_ISC_REGION_DEF_CONTROL_RESETVAL   (0x00009B4AU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_4_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_5_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_6_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_7_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_MASK  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_DEF_MASK   (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_DEF_SHIFT  (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_DEF_MAX    (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_SEC_MASK   (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_SEC_SHIFT  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_SEC_MAX    (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PASS_MASK  (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PASS_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_MASK  (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTR0_ISC_REGION_DEF_CONTROL_RESETVAL   (0x00009B4AU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_4_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_5_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_6_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_7_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_MASK  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_DEF_MASK   (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_DEF_SHIFT  (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_DEF_MAX    (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_SEC_MASK   (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_SEC_SHIFT  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_SEC_MAX    (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PASS_MASK  (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PASS_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_MASK  (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_1_MSTW0_ISC_REGION_DEF_CONTROL_RESETVAL   (0x00009B4AU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_4_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_5_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_6_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_7_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_MASK  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_LOCK_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_DEF_MASK   (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_DEF_SHIFT  (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_DEF_MAX    (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_SEC_MASK   (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_SEC_SHIFT  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_SEC_MAX    (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PASS_MASK  (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PASS_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_MASK  (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_PRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTR0_ISC_REGION_DEF_CONTROL_RESETVAL   (0x00009B4AU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_4_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_5_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_6_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_CH_MODE_MAX  (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_DEF_MASK     (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_DEF_SHIFT    (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_DEF_MAX      (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_ID_MAX  (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_SEC_MASK     (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_SEC_SHIFT    (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_SEC_MAX      (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NONSEC_MASK  (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NONSEC_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PASS_MASK    (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PASS_SHIFT   (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PASS_MAX     (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_MASK    (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_SHIFT   (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_PRIV_MAX     (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_MASK  (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_NOPRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_CONTROL_RESETVAL     (0x00009B00U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_L_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_START_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_7_END_ADDRESS_H_RESETVAL (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_MASK  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_LOCK_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_DEF_MASK   (0x00000040U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_DEF_SHIFT  (0x00000006U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_DEF_MAX    (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x0000009BU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_SEC_MASK   (0x000F0000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_SEC_SHIFT  (0x00000010U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_SEC_MAX    (0x0000000FU)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PASS_MASK  (0x00200000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PASS_MAX   (0x00000001U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_MASK  (0x03000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_PRIV_MAX   (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_IUSB3P1SS_MAIN_2_MSTW0_ISC_REGION_DEF_CONTROL_RESETVAL   (0x00009B4AU)

/* MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MLB0_MLBSS_DMA_VBUSP_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/* MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_RD_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/* MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_MMCSD0_EMMCSS_WR_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/* UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/* UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS0_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/* UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_RD_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/* UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_CONTROL_RESETVAL (0x00008000U)

/* UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_L_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_L_RESETVAL (0x00000FFFU)

/* UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL */

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_RESETVAL (0x0000000AU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_MASK (0x00000020U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_SHIFT (0x00000005U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_CH_MODE_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_MASK (0x00000040U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_SHIFT (0x00000006U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_RESETVAL (0x00000001U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_DEF_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_MASK (0x0000FF00U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_RESETVAL (0x00000080U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_ID_MAX (0x000000FFU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_MASK (0x000F0000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_SEC_MAX (0x0000000FU)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_MASK (0x00100000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NONSEC_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_MASK (0x00200000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_SHIFT (0x00000015U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PASS_MAX (0x00000001U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_MASK (0x03000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_PRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_MASK (0x0C000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_SHIFT (0x0000001AU)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_NOPRIV_MAX (0x00000003U)

#define SDL_HC2_CBASS_ISC_UFS1_UFSHCI_VBM_MST_WR_ISC_REGION_DEF_CONTROL_RESETVAL (0x0000804AU)

/**************************************************************************
* Hardware Region  : Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_256[248];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP0;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP1;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP2;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP3;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP4;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP5;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP6;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTR0_MAP7;   /* Map Register */
    volatile uint8_t  Resv_1024[736];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_1280[248];
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP0;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP1;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP2;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP3;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP4;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP5;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP6;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_0_MSTW0_MAP7;   /* Map Register */
    volatile uint8_t  Resv_2048[736];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_2304[248];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP0;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP1;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP2;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP3;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP4;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP5;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP6;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTR0_MAP7;   /* Map Register */
    volatile uint8_t  Resv_3072[736];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_3328[248];
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP0;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP1;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP2;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP3;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP4;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP5;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP6;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_1_MSTW0_MAP7;   /* Map Register */
    volatile uint8_t  Resv_4096[736];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_4352[248];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP0;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP1;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP2;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP3;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP4;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP5;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP6;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTR0_MAP7;   /* Map Register */
    volatile uint8_t  Resv_5120[736];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_5376[248];
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP0;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP1;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP2;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP3;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP4;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP5;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP6;   /* Map Register */
    volatile uint32_t IUSB3P1SS_MAIN_2_MSTW0_MAP7;   /* Map Register */
    volatile uint8_t  Resv_7168[1760];
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_7424[248];
    volatile uint32_t MLB0_MLBSS_DMA_VBUSP_MAP0;   /* Map Register */
    volatile uint8_t  Resv_8192[764];
    volatile uint32_t MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_8448[248];
    volatile uint32_t MMCSD0_EMMCSS_RD_MAP0;   /* Map Register */
    volatile uint8_t  Resv_9216[764];
    volatile uint32_t MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_9472[248];
    volatile uint32_t MMCSD0_EMMCSS_WR_MAP0;   /* Map Register */
    volatile uint8_t  Resv_12288[2812];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_12544[248];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_MAP0;   /* Map Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_RD_MAP1;   /* Map Register */
    volatile uint8_t  Resv_13312[760];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_13568[248];
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_MAP0;   /* Map Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_MAP1;   /* Map Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_MAP2;   /* Map Register */
    volatile uint32_t UFS0_UFSHCI_VBM_MST_WR_MAP3;   /* Map Register */
    volatile uint8_t  Resv_14336[752];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_14592[248];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_MAP0;   /* Map Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_RD_MAP1;   /* Map Register */
    volatile uint8_t  Resv_15360[760];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1;   /* Group Map Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2;   /* Group Map Register */
    volatile uint8_t  Resv_15616[248];
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_MAP0;   /* Map Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_MAP1;   /* Map Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_MAP2;   /* Map Register */
    volatile uint32_t UFS1_UFSHCI_VBM_MST_WR_MAP3;   /* Map Register */
} SDL_hc2_cbass_qosRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2             (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0                              (0x00000100U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1                              (0x00000104U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2                              (0x00000108U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3                              (0x0000010CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4                              (0x00000110U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5                              (0x00000114U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6                              (0x00000118U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7                              (0x0000011CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1             (0x00000400U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2             (0x00000404U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0                              (0x00000500U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1                              (0x00000504U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2                              (0x00000508U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3                              (0x0000050CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4                              (0x00000510U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5                              (0x00000514U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6                              (0x00000518U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7                              (0x0000051CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1             (0x00000800U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2             (0x00000804U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0                              (0x00000900U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1                              (0x00000904U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2                              (0x00000908U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3                              (0x0000090CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4                              (0x00000910U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5                              (0x00000914U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6                              (0x00000918U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7                              (0x0000091CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1             (0x00000C00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2             (0x00000C04U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0                              (0x00000D00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1                              (0x00000D04U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2                              (0x00000D08U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3                              (0x00000D0CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4                              (0x00000D10U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5                              (0x00000D14U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6                              (0x00000D18U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7                              (0x00000D1CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1             (0x00001000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2             (0x00001004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0                              (0x00001100U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1                              (0x00001104U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2                              (0x00001108U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3                              (0x0000110CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4                              (0x00001110U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5                              (0x00001114U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6                              (0x00001118U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7                              (0x0000111CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1             (0x00001400U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2             (0x00001404U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0                              (0x00001500U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1                              (0x00001504U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2                              (0x00001508U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3                              (0x0000150CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4                              (0x00001510U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5                              (0x00001514U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6                              (0x00001518U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7                              (0x0000151CU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1   (0x00001C00U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2   (0x00001C04U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0                    (0x00001D00U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1    (0x00002000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2    (0x00002004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0                     (0x00002100U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1    (0x00002400U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2    (0x00002404U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0                     (0x00002500U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1 (0x00003000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2 (0x00003004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0         (0x00003100U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1         (0x00003104U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1 (0x00003400U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2 (0x00003404U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0         (0x00003500U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1         (0x00003504U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2         (0x00003508U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3         (0x0000350CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1 (0x00003800U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2 (0x00003804U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0         (0x00003900U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1         (0x00003904U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1 (0x00003C00U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2 (0x00003C04U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0         (0x00003D00U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1         (0x00003D04U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2         (0x00003D08U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3         (0x00003D0CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP1_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_GR_HC2_TO_HC_GRP_MAP2_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP0 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP0_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP1_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP2_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP3 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP3_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP4 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP4_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP5 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP5_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP6 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP6_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTR0_MAP7 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTR0_MAP7_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP1_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_GR_HC2_TO_HC_GRP_MAP2_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP0 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP0_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP1_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP2_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP3 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP3_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP4 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP4_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP5 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP5_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP6 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP6_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_0_MSTW0_MAP7 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_0_MSTW0_MAP7_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP1_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_GR_HC2_TO_HC_GRP_MAP2_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP0 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP0_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP1_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP2_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP3 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP3_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP4 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP4_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP5 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP5_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP6 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP6_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTR0_MAP7 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTR0_MAP7_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP1_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_GR_HC2_TO_HC_GRP_MAP2_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP0 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP0_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP1_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP2_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP3 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP3_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP4 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP4_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP5 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP5_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP6 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP6_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_1_MSTW0_MAP7 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_1_MSTW0_MAP7_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP1_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_GR_HC2_TO_HC_GRP_MAP2_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP0 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP0_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP1_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP2_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP3 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP3_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP4 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP4_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP5 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP5_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP6 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP6_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTR0_MAP7 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTR0_MAP7_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP1_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_GR_HC2_TO_HC_GRP_MAP2_RESETVAL    (0x00000000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP0 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP0_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP1 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP1_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP2 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP2_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP3 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP3_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP4 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP4_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP5 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP5_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP6 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP6_RESETVAL                     (0x00007000U)

/* IUSB3P1SS_MAIN_2_MSTW0_MAP7 */

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_QOS_MASK                     (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_QOS_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_QOS_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_QOS_MAX                      (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ORDERID_MASK                 (0x000000F0U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ORDERID_SHIFT                (0x00000004U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ORDERID_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ORDERID_MAX                  (0x0000000FU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_EPRIORITY_MASK               (0x00007000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_EPRIORITY_SHIFT              (0x0000000CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_EPRIORITY_RESETVAL           (0x00000007U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_EPRIORITY_MAX                (0x00000007U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_VIRTID_MASK                  (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_VIRTID_SHIFT                 (0x00000010U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_VIRTID_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_VIRTID_MAX                   (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ATYPE_MASK                   (0x30000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ATYPE_SHIFT                  (0x0000001CU)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ATYPE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_ATYPE_MAX                    (0x00000003U)

#define SDL_HC2_CBASS_QOS_IUSB3P1SS_MAIN_2_MSTW0_MAP7_RESETVAL                     (0x00007000U)

/* MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* MLB0_MLBSS_DMA_VBUSP_MAP0 */

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_QOS_MASK           (0x00000007U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_QOS_SHIFT          (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_QOS_RESETVAL       (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_QOS_MAX            (0x00000007U)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ORDERID_MASK       (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ORDERID_SHIFT      (0x00000004U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ORDERID_RESETVAL   (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ORDERID_MAX        (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_VIRTID_MASK        (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_VIRTID_SHIFT       (0x00000010U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_VIRTID_RESETVAL    (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_VIRTID_MAX         (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ATYPE_MASK         (0x30000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ATYPE_SHIFT        (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ATYPE_RESETVAL     (0x00000000U)
#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_ATYPE_MAX          (0x00000003U)

#define SDL_HC2_CBASS_QOS_MLB0_MLBSS_DMA_VBUSP_MAP0_RESETVAL           (0x00000000U)

/* MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_RD_MAP0 */

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_QOS_MASK            (0x00000007U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_QOS_SHIFT           (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_QOS_RESETVAL        (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_QOS_MAX             (0x00000007U)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ORDERID_MASK        (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ORDERID_SHIFT       (0x00000004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ORDERID_RESETVAL    (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ORDERID_MAX         (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_EPRIORITY_MASK      (0x00007000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_EPRIORITY_SHIFT     (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_EPRIORITY_RESETVAL  (0x00000007U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_EPRIORITY_MAX       (0x00000007U)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_VIRTID_MASK         (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_VIRTID_SHIFT        (0x00000010U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_VIRTID_RESETVAL     (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_VIRTID_MAX          (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ATYPE_MASK          (0x30000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ATYPE_SHIFT         (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ATYPE_RESETVAL      (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_ATYPE_MAX           (0x00000003U)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_RD_MAP0_RESETVAL            (0x00007000U)

/* MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* MMCSD0_EMMCSS_WR_MAP0 */

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_QOS_MASK            (0x00000007U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_QOS_SHIFT           (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_QOS_RESETVAL        (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_QOS_MAX             (0x00000007U)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ORDERID_MASK        (0x000000F0U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ORDERID_SHIFT       (0x00000004U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ORDERID_RESETVAL    (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ORDERID_MAX         (0x0000000FU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_EPRIORITY_MASK      (0x00007000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_EPRIORITY_SHIFT     (0x0000000CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_EPRIORITY_RESETVAL  (0x00000007U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_EPRIORITY_MAX       (0x00000007U)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_VIRTID_MASK         (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_VIRTID_SHIFT        (0x00000010U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_VIRTID_RESETVAL     (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_VIRTID_MAX          (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ATYPE_MASK          (0x30000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ATYPE_SHIFT         (0x0000001CU)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ATYPE_RESETVAL      (0x00000000U)
#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_ATYPE_MAX           (0x00000003U)

#define SDL_HC2_CBASS_QOS_MMCSD0_EMMCSS_WR_MAP0_RESETVAL            (0x00007000U)

/* UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_RD_MAP0 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP0_RESETVAL (0x00007000U)

/* UFS0_UFSHCI_VBM_MST_RD_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_RD_MAP1_RESETVAL (0x00007000U)

/* UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* UFS0_UFSHCI_VBM_MST_WR_MAP0 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP0_RESETVAL (0x00007000U)

/* UFS0_UFSHCI_VBM_MST_WR_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP1_RESETVAL (0x00007000U)

/* UFS0_UFSHCI_VBM_MST_WR_MAP2 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP2_RESETVAL (0x00007000U)

/* UFS0_UFSHCI_VBM_MST_WR_MAP3 */

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS0_UFSHCI_VBM_MST_WR_MAP3_RESETVAL (0x00007000U)

/* UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_RD_MAP0 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP0_RESETVAL (0x00007000U)

/* UFS1_UFSHCI_VBM_MST_RD_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_RD_MAP1_RESETVAL (0x00007000U)

/* UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID7_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID6_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID5_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID4_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID3_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID2_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID1_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_ORDERID0_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP1_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MASK (0xF0000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID15_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MASK (0x0F000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_SHIFT (0x00000018U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID14_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MASK (0x00F00000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_SHIFT (0x00000014U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID13_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MASK (0x000F0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID12_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MASK (0x0000F000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID11_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MASK (0x00000F00U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_SHIFT (0x00000008U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID10_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID9_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MASK (0x0000000FU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_ORDERID8_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_GR_HC2_TO_HC_GRP_MAP2_RESETVAL (0x00000000U)

/* UFS1_UFSHCI_VBM_MST_WR_MAP0 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP0_RESETVAL (0x00007000U)

/* UFS1_UFSHCI_VBM_MST_WR_MAP1 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP1_RESETVAL (0x00007000U)

/* UFS1_UFSHCI_VBM_MST_WR_MAP2 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP2_RESETVAL (0x00007000U)

/* UFS1_UFSHCI_VBM_MST_WR_MAP3 */

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_QOS_MASK (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_QOS_SHIFT (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_QOS_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_QOS_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ORDERID_MASK (0x000000F0U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ORDERID_SHIFT (0x00000004U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ORDERID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ORDERID_MAX (0x0000000FU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_MASK (0x00007000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_SHIFT (0x0000000CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_RESETVAL (0x00000007U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_EPRIORITY_MAX (0x00000007U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_VIRTID_MASK (0x0FFF0000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_VIRTID_SHIFT (0x00000010U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_VIRTID_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_VIRTID_MAX (0x00000FFFU)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ATYPE_MASK (0x30000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ATYPE_SHIFT (0x0000001CU)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ATYPE_RESETVAL (0x00000000U)
#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_ATYPE_MAX (0x00000003U)

#define SDL_HC2_CBASS_QOS_UFS1_UFSHCI_VBM_MST_WR_MAP3_RESETVAL (0x00007000U)

/**************************************************************************
* Hardware Region  : Error Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t PID;                       /* Revision Register */
    volatile uint32_t DESTINATION_ID;            /* Destination ID Register */
    volatile uint8_t  Resv_36[28];
    volatile uint32_t EXCEPTION_LOGGING_HEADER0;   /* Exception Logging Header 0 Register */
    volatile uint32_t EXCEPTION_LOGGING_HEADER1;   /* Exception Logging Header 1 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA0;   /* Exception Logging Data 0 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA1;   /* Exception Logging Data 1 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA2;   /* Exception Logging Data 2 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA3;   /* Exception Logging Data 3 Register */
    volatile uint8_t  Resv_80[20];
    volatile uint32_t ERR_INTR_RAW_STAT;         /* Global Interrupt Raw Status Register */
    volatile uint32_t ERR_INTR_ENABLED_STAT;     /* Global Interrupt Enabled Status Register */
    volatile uint32_t ERR_INTR_ENABLE_SET;       /* Interrupt Enable Set Register */
    volatile uint32_t ERR_INTR_ENABLE_CLR;       /* Interrupt Enable Clear Register */
    volatile uint32_t EOI;                       /* EOI Register */
} SDL_hc2_cbass_errRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_HC2_CBASS_ERR_PID                                                      (0x00000000U)
#define SDL_HC2_CBASS_ERR_DESTINATION_ID                                           (0x00000004U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0                                (0x00000024U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1                                (0x00000028U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA0                                  (0x0000002CU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA1                                  (0x00000030U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2                                  (0x00000034U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA3                                  (0x00000038U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_RAW_STAT                                        (0x00000050U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLED_STAT                                    (0x00000054U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_SET                                      (0x00000058U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_CLR                                      (0x0000005CU)
#define SDL_HC2_CBASS_ERR_EOI                                                      (0x00000060U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define SDL_HC2_CBASS_ERR_PID_MINOR_MASK                                           (0x0000003FU)
#define SDL_HC2_CBASS_ERR_PID_MINOR_SHIFT                                          (0x00000000U)
#define SDL_HC2_CBASS_ERR_PID_MINOR_RESETVAL                                       (0x00000000U)
#define SDL_HC2_CBASS_ERR_PID_MINOR_MAX                                            (0x0000003FU)

#define SDL_HC2_CBASS_ERR_PID_CUSTOM_MASK                                          (0x000000C0U)
#define SDL_HC2_CBASS_ERR_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define SDL_HC2_CBASS_ERR_PID_CUSTOM_RESETVAL                                      (0x00000000U)
#define SDL_HC2_CBASS_ERR_PID_CUSTOM_MAX                                           (0x00000003U)

#define SDL_HC2_CBASS_ERR_PID_MAJOR_MASK                                           (0x00000700U)
#define SDL_HC2_CBASS_ERR_PID_MAJOR_SHIFT                                          (0x00000008U)
#define SDL_HC2_CBASS_ERR_PID_MAJOR_RESETVAL                                       (0x00000001U)
#define SDL_HC2_CBASS_ERR_PID_MAJOR_MAX                                            (0x00000007U)

#define SDL_HC2_CBASS_ERR_PID_RTL_MASK                                             (0x0000F800U)
#define SDL_HC2_CBASS_ERR_PID_RTL_SHIFT                                            (0x0000000BU)
#define SDL_HC2_CBASS_ERR_PID_RTL_RESETVAL                                         (0x00000008U)
#define SDL_HC2_CBASS_ERR_PID_RTL_MAX                                              (0x0000001FU)

#define SDL_HC2_CBASS_ERR_PID_FUNC_MASK                                            (0x0FFF0000U)
#define SDL_HC2_CBASS_ERR_PID_FUNC_SHIFT                                           (0x00000010U)
#define SDL_HC2_CBASS_ERR_PID_FUNC_RESETVAL                                        (0x00000600U)
#define SDL_HC2_CBASS_ERR_PID_FUNC_MAX                                             (0x00000FFFU)

#define SDL_HC2_CBASS_ERR_PID_BU_MASK                                              (0x30000000U)
#define SDL_HC2_CBASS_ERR_PID_BU_SHIFT                                             (0x0000001CU)
#define SDL_HC2_CBASS_ERR_PID_BU_RESETVAL                                          (0x00000002U)
#define SDL_HC2_CBASS_ERR_PID_BU_MAX                                               (0x00000003U)

#define SDL_HC2_CBASS_ERR_PID_SCHEME_MASK                                          (0xC0000000U)
#define SDL_HC2_CBASS_ERR_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define SDL_HC2_CBASS_ERR_PID_SCHEME_RESETVAL                                      (0x00000001U)
#define SDL_HC2_CBASS_ERR_PID_SCHEME_MAX                                           (0x00000003U)

#define SDL_HC2_CBASS_ERR_PID_RESETVAL                                             (0x66004100U)

/* DESTINATION_ID */

#define SDL_HC2_CBASS_ERR_DESTINATION_ID_DEST_ID_MASK                              (0x000000FFU)
#define SDL_HC2_CBASS_ERR_DESTINATION_ID_DEST_ID_SHIFT                             (0x00000000U)
#define SDL_HC2_CBASS_ERR_DESTINATION_ID_DEST_ID_RESETVAL                          (0x00000000U)
#define SDL_HC2_CBASS_ERR_DESTINATION_ID_DEST_ID_MAX                               (0x000000FFU)

#define SDL_HC2_CBASS_ERR_DESTINATION_ID_RESETVAL                                  (0x00000000U)

/* EXCEPTION_LOGGING_HEADER0 */

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_MASK                   (0x000000FFU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_SHIFT                  (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_MAX                    (0x000000FFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_MASK                    (0x00FFFF00U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_SHIFT                   (0x00000008U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_RESETVAL                (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_MAX                     (0x0000FFFFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_MASK                    (0xFF000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_SHIFT                   (0x00000018U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_RESETVAL                (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_MAX                     (0x000000FFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER1 */

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_MASK                      (0x00FF0000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_SHIFT                     (0x00000010U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_RESETVAL                  (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_MAX                       (0x000000FFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_MASK                     (0xFF000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_SHIFT                    (0x00000018U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_MAX                      (0x000000FFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_DATA0 */

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_MASK                      (0xFFFFFFFFU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_SHIFT                     (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_RESETVAL                  (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_MAX                       (0xFFFFFFFFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA0_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA1 */

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_MASK                      (0x0000FFFFU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_SHIFT                     (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_RESETVAL                  (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_MAX                       (0x0000FFFFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA1_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA2 */

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_MASK                     (0x000000FFU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_MAX                      (0x000000FFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_MASK                      (0x00000100U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_SHIFT                     (0x00000008U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_RESETVAL                  (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_MAX                       (0x00000001U)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_MASK                        (0x00000200U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_SHIFT                       (0x00000009U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_RESETVAL                    (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_MAX                         (0x00000001U)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_MASK                   (0x00000400U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_SHIFT                  (0x0000000AU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_RESETVAL               (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_MAX                    (0x00000001U)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_MASK                       (0x00000800U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_SHIFT                      (0x0000000BU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_RESETVAL                   (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_MAX                        (0x00000001U)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_MASK                        (0x00001000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_SHIFT                       (0x0000000CU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_RESETVAL                    (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_MAX                         (0x00000001U)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_MASK                       (0x00002000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_SHIFT                      (0x0000000DU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_RESETVAL                   (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_MAX                        (0x00000001U)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_MASK                     (0x0FFF0000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_SHIFT                    (0x00000010U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_MAX                      (0x00000FFFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA2_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA3 */

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_MASK                     (0x000003FFU)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_SHIFT                    (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_RESETVAL                 (0x00000000U)
#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_MAX                      (0x000003FFU)

#define SDL_HC2_CBASS_ERR_EXCEPTION_LOGGING_DATA3_RESETVAL                         (0x00000000U)

/* ERR_INTR_RAW_STAT */

#define SDL_HC2_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_MASK                              (0x00000001U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_SHIFT                             (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_RESETVAL                          (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_MAX                               (0x00000001U)

#define SDL_HC2_CBASS_ERR_ERR_INTR_RAW_STAT_RESETVAL                               (0x00000000U)

/* ERR_INTR_ENABLED_STAT */

#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_MASK                  (0x00000001U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_SHIFT                 (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_RESETVAL              (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_MAX                   (0x00000001U)

#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLED_STAT_RESETVAL                           (0x00000000U)

/* ERR_INTR_ENABLE_SET */

#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_MASK                 (0x00000001U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_SHIFT                (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_MAX                  (0x00000001U)

#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_SET_RESETVAL                             (0x00000000U)

/* ERR_INTR_ENABLE_CLR */

#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_MASK                 (0x00000001U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_SHIFT                (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_RESETVAL             (0x00000000U)
#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_MAX                  (0x00000001U)

#define SDL_HC2_CBASS_ERR_ERR_INTR_ENABLE_CLR_RESETVAL                             (0x00000000U)

/* EOI */

#define SDL_HC2_CBASS_ERR_EOI_WR_MASK                                              (0x0000FFFFU)
#define SDL_HC2_CBASS_ERR_EOI_WR_SHIFT                                             (0x00000000U)
#define SDL_HC2_CBASS_ERR_EOI_WR_RESETVAL                                          (0x00000000U)
#define SDL_HC2_CBASS_ERR_EOI_WR_MAX                                               (0x0000FFFFU)

#define SDL_HC2_CBASS_ERR_EOI_RESETVAL                                             (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
