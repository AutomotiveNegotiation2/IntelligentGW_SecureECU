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
 *  Name        : sdlr_mcasp_g1_cbass.h
*/
#ifndef SDLR_MCASP_G1_CBASS_H_
#define SDLR_MCASP_G1_CBASS_H_

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
    volatile uint32_t DESTINATION_ID;            /* Destination ID Register */
    volatile uint8_t  Resv_32[24];
    volatile uint32_t EXCEPTION_LOGGING_CONTROL;   /* Exception Logging Control Register */
    volatile uint32_t EXCEPTION_LOGGING_HEADER0;   /* Exception Logging Header 0 Register */
    volatile uint32_t EXCEPTION_LOGGING_HEADER1;   /* Exception Logging Header 1 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA0;   /* Exception Logging Data 0 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA1;   /* Exception Logging Data 1 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA2;   /* Exception Logging Data 2 Register */
    volatile uint32_t EXCEPTION_LOGGING_DATA3;   /* Exception Logging Data 3 Register */
    volatile uint8_t  Resv_64[4];
    volatile uint32_t EXCEPTION_PEND_SET;        /* Exception Logging Pending Set Register */
    volatile uint32_t EXCEPTION_PEND_CLEAR;      /* Exception Logging Pending Clear Register */
} SDL_mcasp_g1_cbass_glbRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_MCASP_G1_CBASS_GLB_PID                                                      (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_DESTINATION_ID                                           (0x00000004U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL                                (0x00000020U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0                                (0x00000024U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1                                (0x00000028U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA0                                  (0x0000002CU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA1                                  (0x00000030U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2                                  (0x00000034U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA3                                  (0x00000038U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_SET                                       (0x00000040U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_CLEAR                                     (0x00000044U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define SDL_MCASP_G1_CBASS_GLB_PID_MINOR_MASK                                           (0x0000003FU)
#define SDL_MCASP_G1_CBASS_GLB_PID_MINOR_SHIFT                                          (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_PID_MINOR_RESETVAL                                       (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_PID_MINOR_MAX                                            (0x0000003FU)

#define SDL_MCASP_G1_CBASS_GLB_PID_CUSTOM_MASK                                          (0x000000C0U)
#define SDL_MCASP_G1_CBASS_GLB_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define SDL_MCASP_G1_CBASS_GLB_PID_CUSTOM_RESETVAL                                      (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_PID_CUSTOM_MAX                                           (0x00000003U)

#define SDL_MCASP_G1_CBASS_GLB_PID_MAJOR_MASK                                           (0x00000700U)
#define SDL_MCASP_G1_CBASS_GLB_PID_MAJOR_SHIFT                                          (0x00000008U)
#define SDL_MCASP_G1_CBASS_GLB_PID_MAJOR_RESETVAL                                       (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_PID_MAJOR_MAX                                            (0x00000007U)

#define SDL_MCASP_G1_CBASS_GLB_PID_RTL_MASK                                             (0x0000F800U)
#define SDL_MCASP_G1_CBASS_GLB_PID_RTL_SHIFT                                            (0x0000000BU)
#define SDL_MCASP_G1_CBASS_GLB_PID_RTL_RESETVAL                                         (0x00000007U)
#define SDL_MCASP_G1_CBASS_GLB_PID_RTL_MAX                                              (0x0000001FU)

#define SDL_MCASP_G1_CBASS_GLB_PID_FUNC_MASK                                            (0x0FFF0000U)
#define SDL_MCASP_G1_CBASS_GLB_PID_FUNC_SHIFT                                           (0x00000010U)
#define SDL_MCASP_G1_CBASS_GLB_PID_FUNC_RESETVAL                                        (0x00000600U)
#define SDL_MCASP_G1_CBASS_GLB_PID_FUNC_MAX                                             (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_GLB_PID_BU_MASK                                              (0x30000000U)
#define SDL_MCASP_G1_CBASS_GLB_PID_BU_SHIFT                                             (0x0000001CU)
#define SDL_MCASP_G1_CBASS_GLB_PID_BU_RESETVAL                                          (0x00000002U)
#define SDL_MCASP_G1_CBASS_GLB_PID_BU_MAX                                               (0x00000003U)

#define SDL_MCASP_G1_CBASS_GLB_PID_SCHEME_MASK                                          (0xC0000000U)
#define SDL_MCASP_G1_CBASS_GLB_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define SDL_MCASP_G1_CBASS_GLB_PID_SCHEME_RESETVAL                                      (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_PID_SCHEME_MAX                                           (0x00000003U)

#define SDL_MCASP_G1_CBASS_GLB_PID_RESETVAL                                             (0x66003901U)

/* DESTINATION_ID */

#define SDL_MCASP_G1_CBASS_GLB_DESTINATION_ID_DEST_ID_MASK                              (0x000000FFU)
#define SDL_MCASP_G1_CBASS_GLB_DESTINATION_ID_DEST_ID_SHIFT                             (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_DESTINATION_ID_DEST_ID_RESETVAL                          (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_DESTINATION_ID_DEST_ID_MAX                               (0x000000FFU)

#define SDL_MCASP_G1_CBASS_GLB_DESTINATION_ID_RESETVAL                                  (0x00000000U)

/* EXCEPTION_LOGGING_CONTROL */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_MASK                 (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_SHIFT                (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_RESETVAL             (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_MAX                  (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_MASK              (0x00000002U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_SHIFT             (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_RESETVAL          (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_MAX               (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER0 */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_MASK                   (0x000000FFU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_SHIFT                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_RESETVAL               (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_MAX                    (0x000000FFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_MASK                    (0x00FFFF00U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_SHIFT                   (0x00000008U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_RESETVAL                (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_MAX                     (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_MASK                    (0xFF000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_SHIFT                   (0x00000018U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_RESETVAL                (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_MAX                     (0x000000FFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER1 */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_MASK                      (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_SHIFT                     (0x00000010U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_MAX                       (0x000000FFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_MASK                     (0xFF000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_SHIFT                    (0x00000018U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_MAX                      (0x000000FFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_DATA0 */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_MASK                      (0xFFFFFFFFU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_SHIFT                     (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_MAX                       (0xFFFFFFFFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA0_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA1 */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_MASK                      (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_SHIFT                     (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_MAX                       (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA1_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA2 */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_MASK                     (0x000000FFU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_SHIFT                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_MAX                      (0x000000FFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_MASK                      (0x00000100U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_SHIFT                     (0x00000008U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_MAX                       (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_MASK                        (0x00000200U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_SHIFT                       (0x00000009U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_RESETVAL                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_MAX                         (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_MASK                   (0x00000400U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_SHIFT                  (0x0000000AU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_RESETVAL               (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_MAX                    (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_MASK                       (0x00000800U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_SHIFT                      (0x0000000BU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_RESETVAL                   (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_MAX                        (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_MASK                        (0x00001000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_SHIFT                       (0x0000000CU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_RESETVAL                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_MAX                         (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_MASK                       (0x00002000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_SHIFT                      (0x0000000DU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_RESETVAL                   (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_MAX                        (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_MASK                     (0x0FFF0000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_SHIFT                    (0x00000010U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_MAX                      (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA2_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA3 */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_MASK                     (0x000003FFU)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_SHIFT                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_MAX                      (0x000003FFU)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_LOGGING_DATA3_RESETVAL                         (0x00000000U)

/* EXCEPTION_PEND_SET */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_MASK                         (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_SHIFT                        (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_RESETVAL                     (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_MAX                          (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_SET_RESETVAL                              (0x00000000U)

/* EXCEPTION_PEND_CLEAR */

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_MASK                       (0x00000001U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_SHIFT                      (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_RESETVAL                   (0x00000000U)
#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_MAX                        (0x00000001U)

#define SDL_MCASP_G1_CBASS_GLB_EXCEPTION_PEND_CLEAR_RESETVAL                            (0x00000000U)

/**************************************************************************
* Hardware Region  : Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_1024[992];
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_2048[992];
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_3072[992];
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_4096[992];
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_5120[992];
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_6144[992];
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_7168[992];
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_8192[992];
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_9216[992];
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_10240[992];
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_11264[992];
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_12288[992];
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_13312[992];
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_14336[992];
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_15360[992];
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_16384[992];
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_17408[992];
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_31744[14304];
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
} SDL_mcasp_g1_cbass_fwRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00000014U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00000018U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000001CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL                 (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00000404U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00000408U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x0000040CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00000410U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00000414U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00000418U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x0000041CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL                 (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00000804U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00000808U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000080CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00000810U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00000814U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00000818U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000081CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL                 (0x00000C00U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00000C04U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00000C08U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x00000C0CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00000C10U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00000C14U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00000C18U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x00000C1CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL                 (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00001004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00001008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000100CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00001010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00001014U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00001018U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000101CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL                 (0x00001400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00001404U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00001408U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x0000140CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00001410U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00001414U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00001418U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x0000141CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL                 (0x00001800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00001804U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00001808U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000180CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00001810U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00001814U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00001818U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000181CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL                 (0x00001C00U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00001C04U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00001C08U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x00001C0CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00001C10U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00001C14U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00001C18U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x00001C1CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL                 (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00002004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00002008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000200CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00002010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00002014U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00002018U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000201CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL                 (0x00002400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00002404U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00002408U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x0000240CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00002410U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00002414U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00002418U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x0000241CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL                 (0x00002800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00002804U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00002808U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000280CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00002810U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00002814U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00002818U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000281CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL                 (0x00002C00U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00002C04U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00002C08U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x00002C0CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00002C10U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00002C14U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00002C18U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x00002C1CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL                 (0x00003000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0            (0x00003004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1            (0x00003008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2            (0x0000300CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L         (0x00003010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H         (0x00003014U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L           (0x00003018U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H           (0x0000301CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL                 (0x00003400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0            (0x00003404U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1            (0x00003408U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2            (0x0000340CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L         (0x00003410U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H         (0x00003414U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L           (0x00003418U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H           (0x0000341CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL                (0x00003800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0           (0x00003804U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1           (0x00003808U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2           (0x0000380CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L        (0x00003810U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H        (0x00003814U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L          (0x00003818U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H          (0x0000381CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL                (0x00003C00U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0           (0x00003C04U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1           (0x00003C08U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2           (0x00003C0CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L        (0x00003C10U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H        (0x00003C14U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L          (0x00003C18U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H          (0x00003C1CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL                (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0           (0x00004004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1           (0x00004008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2           (0x0000400CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L        (0x00004010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H        (0x00004014U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L          (0x00004018U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H          (0x0000401CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL                (0x00004400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0           (0x00004404U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1           (0x00004408U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2           (0x0000440CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L        (0x00004410U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H        (0x00004414U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L          (0x00004418U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H          (0x0000441CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL (0x00007C00U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0 (0x00007C04U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1 (0x00007C08U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2 (0x00007C0CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L (0x00007C10U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H (0x00007C14U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L (0x00007C18U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H (0x00007C1CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* MCASP3_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B30U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B30000U)

/* MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B31U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B31FFFU)

/* MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP3_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B38U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B38000U)

/* MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B38U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B38FFFU)

/* MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP3_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP4_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B40U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B40000U)

/* MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B41U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B41FFFU)

/* MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP4_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B48U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B48000U)

/* MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B48U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B48FFFU)

/* MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP4_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP5_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B50U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B50000U)

/* MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B51U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B51FFFU)

/* MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP5_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B58U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B58000U)

/* MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B58U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B58FFFU)

/* MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP5_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP6_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B60U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B60000U)

/* MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B61U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B61FFFU)

/* MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP6_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B68U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B68000U)

/* MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B68U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B68FFFU)

/* MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP6_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP7_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B70U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B70000U)

/* MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B71U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B71FFFU)

/* MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP7_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B78U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B78000U)

/* MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B78U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B78FFFU)

/* MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP7_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP8_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B80U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B80000U)

/* MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B81U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B81FFFU)

/* MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP8_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B88U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B88000U)

/* MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B88U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B88FFFU)

/* MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP8_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP9_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B90U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B90000U)

/* MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B91U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B91FFFU)

/* MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP9_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK     (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT    (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX      (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK       (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT      (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX        (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX  (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL        (0x00000000U)

/* MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL   (0x00000000U)

/* MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL   (0x00000000U)

/* MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL   (0x00000000U)

/* MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002B98U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02B98000U)

/* MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002B98U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL  (0x02B98FFFU)

/* MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP9_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL  (0x00000000U)

/* MCASP10_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK    (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX     (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK      (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT     (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL  (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX       (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL       (0x00000000U)

/* MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL  (0x00000000U)

/* MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL  (0x00000000U)

/* MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL  (0x00000000U)

/* MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002BA0U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02BA0000U)

/* MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002BA1U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x02BA1FFFU)

/* MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP10_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK    (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX     (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK      (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT     (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL  (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX       (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL       (0x00000000U)

/* MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL  (0x00000000U)

/* MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL  (0x00000000U)

/* MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL  (0x00000000U)

/* MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002BA8U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02BA8000U)

/* MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002BA8U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x02BA8FFFU)

/* MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP10_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP11_SLV_CFG_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MASK    (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_ENABLE_MAX     (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MASK      (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT     (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL  (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_LOCK_MAX       (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_CONTROL_RESETVAL       (0x00000000U)

/* MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_0_RESETVAL  (0x00000000U)

/* MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_1_RESETVAL  (0x00000000U)

/* MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_PERMISSION_2_RESETVAL  (0x00000000U)

/* MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002BB0U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02BB0000U)

/* MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002BB1U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x02BB1FFFU)

/* MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP11_SLV_DMA_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MASK    (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_SHIFT   (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_ENABLE_MAX     (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MASK      (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_LOCK_SHIFT     (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_LOCK_RESETVAL  (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_LOCK_MAX       (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_CONTROL_RESETVAL       (0x00000000U)

/* MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_0_RESETVAL  (0x00000000U)

/* MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_1_RESETVAL  (0x00000000U)

/* MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_PERMISSION_2_RESETVAL  (0x00000000U)

/* MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002BB8U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02BB8000U)

/* MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002BB8U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x02BB8FFFU)

/* MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_MCASP11_SLV_DMA_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_RESETVAL (0x00000000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0 */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1 */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2 */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002A8BU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02A8B000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002A8BU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x02A8BFFFU)

/* CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H */

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_FW_CBASS_MCASP_G1_0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

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
} SDL_mcasp_g1_cbass_errRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_MCASP_G1_CBASS_ERR_PID                                                      (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_DESTINATION_ID                                           (0x00000004U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0                                (0x00000024U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1                                (0x00000028U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA0                                  (0x0000002CU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA1                                  (0x00000030U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2                                  (0x00000034U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA3                                  (0x00000038U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_RAW_STAT                                        (0x00000050U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLED_STAT                                    (0x00000054U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_SET                                      (0x00000058U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_CLR                                      (0x0000005CU)
#define SDL_MCASP_G1_CBASS_ERR_EOI                                                      (0x00000060U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define SDL_MCASP_G1_CBASS_ERR_PID_MINOR_MASK                                           (0x0000003FU)
#define SDL_MCASP_G1_CBASS_ERR_PID_MINOR_SHIFT                                          (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_PID_MINOR_RESETVAL                                       (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_PID_MINOR_MAX                                            (0x0000003FU)

#define SDL_MCASP_G1_CBASS_ERR_PID_CUSTOM_MASK                                          (0x000000C0U)
#define SDL_MCASP_G1_CBASS_ERR_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define SDL_MCASP_G1_CBASS_ERR_PID_CUSTOM_RESETVAL                                      (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_PID_CUSTOM_MAX                                           (0x00000003U)

#define SDL_MCASP_G1_CBASS_ERR_PID_MAJOR_MASK                                           (0x00000700U)
#define SDL_MCASP_G1_CBASS_ERR_PID_MAJOR_SHIFT                                          (0x00000008U)
#define SDL_MCASP_G1_CBASS_ERR_PID_MAJOR_RESETVAL                                       (0x00000001U)
#define SDL_MCASP_G1_CBASS_ERR_PID_MAJOR_MAX                                            (0x00000007U)

#define SDL_MCASP_G1_CBASS_ERR_PID_RTL_MASK                                             (0x0000F800U)
#define SDL_MCASP_G1_CBASS_ERR_PID_RTL_SHIFT                                            (0x0000000BU)
#define SDL_MCASP_G1_CBASS_ERR_PID_RTL_RESETVAL                                         (0x00000007U)
#define SDL_MCASP_G1_CBASS_ERR_PID_RTL_MAX                                              (0x0000001FU)

#define SDL_MCASP_G1_CBASS_ERR_PID_FUNC_MASK                                            (0x0FFF0000U)
#define SDL_MCASP_G1_CBASS_ERR_PID_FUNC_SHIFT                                           (0x00000010U)
#define SDL_MCASP_G1_CBASS_ERR_PID_FUNC_RESETVAL                                        (0x00000600U)
#define SDL_MCASP_G1_CBASS_ERR_PID_FUNC_MAX                                             (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_ERR_PID_BU_MASK                                              (0x30000000U)
#define SDL_MCASP_G1_CBASS_ERR_PID_BU_SHIFT                                             (0x0000001CU)
#define SDL_MCASP_G1_CBASS_ERR_PID_BU_RESETVAL                                          (0x00000002U)
#define SDL_MCASP_G1_CBASS_ERR_PID_BU_MAX                                               (0x00000003U)

#define SDL_MCASP_G1_CBASS_ERR_PID_SCHEME_MASK                                          (0xC0000000U)
#define SDL_MCASP_G1_CBASS_ERR_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define SDL_MCASP_G1_CBASS_ERR_PID_SCHEME_RESETVAL                                      (0x00000001U)
#define SDL_MCASP_G1_CBASS_ERR_PID_SCHEME_MAX                                           (0x00000003U)

#define SDL_MCASP_G1_CBASS_ERR_PID_RESETVAL                                             (0x66003900U)

/* DESTINATION_ID */

#define SDL_MCASP_G1_CBASS_ERR_DESTINATION_ID_DEST_ID_MASK                              (0x000000FFU)
#define SDL_MCASP_G1_CBASS_ERR_DESTINATION_ID_DEST_ID_SHIFT                             (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_DESTINATION_ID_DEST_ID_RESETVAL                          (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_DESTINATION_ID_DEST_ID_MAX                               (0x000000FFU)

#define SDL_MCASP_G1_CBASS_ERR_DESTINATION_ID_RESETVAL                                  (0x00000000U)

/* EXCEPTION_LOGGING_HEADER0 */

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_MASK                   (0x000000FFU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_SHIFT                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_RESETVAL               (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_MAX                    (0x000000FFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_MASK                    (0x00FFFF00U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_SHIFT                   (0x00000008U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_RESETVAL                (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_MAX                     (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_MASK                    (0xFF000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_SHIFT                   (0x00000018U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_RESETVAL                (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_MAX                     (0x000000FFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER1 */

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_MASK                      (0x00FF0000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_SHIFT                     (0x00000010U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_MAX                       (0x000000FFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_MASK                     (0xFF000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_SHIFT                    (0x00000018U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_MAX                      (0x000000FFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_DATA0 */

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_MASK                      (0xFFFFFFFFU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_SHIFT                     (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_MAX                       (0xFFFFFFFFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA0_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA1 */

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_MASK                      (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_SHIFT                     (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_MAX                       (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA1_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA2 */

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_MASK                     (0x000000FFU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_SHIFT                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_MAX                      (0x000000FFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_MASK                      (0x00000100U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_SHIFT                     (0x00000008U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_RESETVAL                  (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_MAX                       (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_MASK                        (0x00000200U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_SHIFT                       (0x00000009U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_RESETVAL                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_MAX                         (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_MASK                   (0x00000400U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_SHIFT                  (0x0000000AU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_RESETVAL               (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_MAX                    (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_MASK                       (0x00000800U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_SHIFT                      (0x0000000BU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_RESETVAL                   (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_MAX                        (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_MASK                        (0x00001000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_SHIFT                       (0x0000000CU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_RESETVAL                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_MAX                         (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_MASK                       (0x00002000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_SHIFT                      (0x0000000DU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_RESETVAL                   (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_MAX                        (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_MASK                     (0x0FFF0000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_SHIFT                    (0x00000010U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_MAX                      (0x00000FFFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA2_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA3 */

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_MASK                     (0x000003FFU)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_SHIFT                    (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_RESETVAL                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_MAX                      (0x000003FFU)

#define SDL_MCASP_G1_CBASS_ERR_EXCEPTION_LOGGING_DATA3_RESETVAL                         (0x00000000U)

/* ERR_INTR_RAW_STAT */

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_MASK                              (0x00000001U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_SHIFT                             (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_RESETVAL                          (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_MAX                               (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_RAW_STAT_RESETVAL                               (0x00000000U)

/* ERR_INTR_ENABLED_STAT */

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_MASK                  (0x00000001U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_SHIFT                 (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_RESETVAL              (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_MAX                   (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLED_STAT_RESETVAL                           (0x00000000U)

/* ERR_INTR_ENABLE_SET */

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_MASK                 (0x00000001U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_SHIFT                (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_RESETVAL             (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_MAX                  (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_SET_RESETVAL                             (0x00000000U)

/* ERR_INTR_ENABLE_CLR */

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_MASK                 (0x00000001U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_SHIFT                (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_RESETVAL             (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_MAX                  (0x00000001U)

#define SDL_MCASP_G1_CBASS_ERR_ERR_INTR_ENABLE_CLR_RESETVAL                             (0x00000000U)

/* EOI */

#define SDL_MCASP_G1_CBASS_ERR_EOI_WR_MASK                                              (0x0000FFFFU)
#define SDL_MCASP_G1_CBASS_ERR_EOI_WR_SHIFT                                             (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EOI_WR_RESETVAL                                          (0x00000000U)
#define SDL_MCASP_G1_CBASS_ERR_EOI_WR_MAX                                               (0x0000FFFFU)

#define SDL_MCASP_G1_CBASS_ERR_EOI_RESETVAL                                             (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
