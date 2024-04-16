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
 *  Name        : sdlr_csi_cbass.h
*/
#ifndef SDLR_CSI_CBASS_H_
#define SDLR_CSI_CBASS_H_

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
} SDL_csi_cbass_glbRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_CSI_CBASS_GLB_PID                                                      (0x00000000U)
#define SDL_CSI_CBASS_GLB_DESTINATION_ID                                           (0x00000004U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL                                (0x00000020U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0                                (0x00000024U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1                                (0x00000028U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA0                                  (0x0000002CU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA1                                  (0x00000030U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2                                  (0x00000034U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA3                                  (0x00000038U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_SET                                       (0x00000040U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_CLEAR                                     (0x00000044U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define SDL_CSI_CBASS_GLB_PID_MINOR_MASK                                           (0x0000003FU)
#define SDL_CSI_CBASS_GLB_PID_MINOR_SHIFT                                          (0x00000000U)
#define SDL_CSI_CBASS_GLB_PID_MINOR_RESETVAL                                       (0x00000001U)
#define SDL_CSI_CBASS_GLB_PID_MINOR_MAX                                            (0x0000003FU)

#define SDL_CSI_CBASS_GLB_PID_CUSTOM_MASK                                          (0x000000C0U)
#define SDL_CSI_CBASS_GLB_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define SDL_CSI_CBASS_GLB_PID_CUSTOM_RESETVAL                                      (0x00000000U)
#define SDL_CSI_CBASS_GLB_PID_CUSTOM_MAX                                           (0x00000003U)

#define SDL_CSI_CBASS_GLB_PID_MAJOR_MASK                                           (0x00000700U)
#define SDL_CSI_CBASS_GLB_PID_MAJOR_SHIFT                                          (0x00000008U)
#define SDL_CSI_CBASS_GLB_PID_MAJOR_RESETVAL                                       (0x00000001U)
#define SDL_CSI_CBASS_GLB_PID_MAJOR_MAX                                            (0x00000007U)

#define SDL_CSI_CBASS_GLB_PID_RTL_MASK                                             (0x0000F800U)
#define SDL_CSI_CBASS_GLB_PID_RTL_SHIFT                                            (0x0000000BU)
#define SDL_CSI_CBASS_GLB_PID_RTL_RESETVAL                                         (0x00000007U)
#define SDL_CSI_CBASS_GLB_PID_RTL_MAX                                              (0x0000001FU)

#define SDL_CSI_CBASS_GLB_PID_FUNC_MASK                                            (0x0FFF0000U)
#define SDL_CSI_CBASS_GLB_PID_FUNC_SHIFT                                           (0x00000010U)
#define SDL_CSI_CBASS_GLB_PID_FUNC_RESETVAL                                        (0x00000600U)
#define SDL_CSI_CBASS_GLB_PID_FUNC_MAX                                             (0x00000FFFU)

#define SDL_CSI_CBASS_GLB_PID_BU_MASK                                              (0x30000000U)
#define SDL_CSI_CBASS_GLB_PID_BU_SHIFT                                             (0x0000001CU)
#define SDL_CSI_CBASS_GLB_PID_BU_RESETVAL                                          (0x00000002U)
#define SDL_CSI_CBASS_GLB_PID_BU_MAX                                               (0x00000003U)

#define SDL_CSI_CBASS_GLB_PID_SCHEME_MASK                                          (0xC0000000U)
#define SDL_CSI_CBASS_GLB_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define SDL_CSI_CBASS_GLB_PID_SCHEME_RESETVAL                                      (0x00000001U)
#define SDL_CSI_CBASS_GLB_PID_SCHEME_MAX                                           (0x00000003U)

#define SDL_CSI_CBASS_GLB_PID_RESETVAL                                             (0x66003901U)

/* DESTINATION_ID */

#define SDL_CSI_CBASS_GLB_DESTINATION_ID_DEST_ID_MASK                              (0x000000FFU)
#define SDL_CSI_CBASS_GLB_DESTINATION_ID_DEST_ID_SHIFT                             (0x00000000U)
#define SDL_CSI_CBASS_GLB_DESTINATION_ID_DEST_ID_RESETVAL                          (0x00000000U)
#define SDL_CSI_CBASS_GLB_DESTINATION_ID_DEST_ID_MAX                               (0x000000FFU)

#define SDL_CSI_CBASS_GLB_DESTINATION_ID_RESETVAL                                  (0x00000000U)

/* EXCEPTION_LOGGING_CONTROL */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_MASK                 (0x00000001U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_SHIFT                (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_RESETVAL             (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_F_MAX                  (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_MASK              (0x00000002U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_SHIFT             (0x00000001U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_RESETVAL          (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_DISABLE_PEND_MAX               (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_CONTROL_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER0 */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_MASK                   (0x000000FFU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_SHIFT                  (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_RESETVAL               (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_DEST_ID_MAX                    (0x000000FFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_MASK                    (0x00FFFF00U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_SHIFT                   (0x00000008U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_RESETVAL                (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_SRC_ID_MAX                     (0x0000FFFFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_MASK                    (0xFF000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_SHIFT                   (0x00000018U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_RESETVAL                (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_TYPE_F_MAX                     (0x000000FFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER0_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER1 */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_MASK                      (0x00FF0000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_SHIFT                     (0x00000010U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_CODE_MAX                       (0x000000FFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_MASK                     (0xFF000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_SHIFT                    (0x00000018U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_GROUP_MAX                      (0x000000FFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_HEADER1_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_DATA0 */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_MASK                      (0xFFFFFFFFU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_SHIFT                     (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA0_ADDR_L_MAX                       (0xFFFFFFFFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA0_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA1 */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_MASK                      (0x0000FFFFU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_SHIFT                     (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA1_ADDR_H_MAX                       (0x0000FFFFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA1_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA2 */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_MASK                     (0x000000FFU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_SHIFT                    (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_ID_MAX                      (0x000000FFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_MASK                      (0x00000100U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_SHIFT                     (0x00000008U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_SECURE_MAX                       (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_MASK                        (0x00000200U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_SHIFT                       (0x00000009U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_RESETVAL                    (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_PRIV_MAX                         (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_MASK                   (0x00000400U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_SHIFT                  (0x0000000AU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_RESETVAL               (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_CACHEABLE_MAX                    (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_MASK                       (0x00000800U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_SHIFT                      (0x0000000BU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_RESETVAL                   (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_DEBUG_MAX                        (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_MASK                        (0x00001000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_SHIFT                       (0x0000000CU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_RESETVAL                    (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_READ_MAX                         (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_MASK                       (0x00002000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_SHIFT                      (0x0000000DU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_RESETVAL                   (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_WRITE_MAX                        (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_MASK                     (0x0FFF0000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_SHIFT                    (0x00000010U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_ROUTEID_MAX                      (0x00000FFFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA2_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA3 */

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_MASK                     (0x000003FFU)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_SHIFT                    (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA3_BYTECNT_MAX                      (0x000003FFU)

#define SDL_CSI_CBASS_GLB_EXCEPTION_LOGGING_DATA3_RESETVAL                         (0x00000000U)

/* EXCEPTION_PEND_SET */

#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_MASK                         (0x00000001U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_SHIFT                        (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_RESETVAL                     (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_SET_PEND_SET_MAX                          (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_SET_RESETVAL                              (0x00000000U)

/* EXCEPTION_PEND_CLEAR */

#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_MASK                       (0x00000001U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_SHIFT                      (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_RESETVAL                   (0x00000000U)
#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_CLEAR_PEND_CLR_MAX                        (0x00000001U)

#define SDL_CSI_CBASS_GLB_EXCEPTION_PEND_CLEAR_RESETVAL                            (0x00000000U)

/**************************************************************************
* Hardware Region  : Config port MMR
**************************************************************************/


/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint8_t  Resv_1024[896];
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint8_t  Resv_2048[896];
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint8_t  Resv_4096[1920];
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint8_t  Resv_5120[960];
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint8_t  Resv_6144[960];
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint8_t  Resv_8192[1984];
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL;   /* Firewall Region 1 Control Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0;   /* Firewall Region 1 Permission 0 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1;   /* Firewall Region 1 Permission 1 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2;   /* Firewall Region 1 Permission 2 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L;   /* Firewall Region 1 Start Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H;   /* Firewall Region 1 Start Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L;   /* Firewall Region 1 End Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H;   /* Firewall Region 1 End Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL;   /* Firewall Region 2 Control Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0;   /* Firewall Region 2 Permission 0 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1;   /* Firewall Region 2 Permission 1 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2;   /* Firewall Region 2 Permission 2 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L;   /* Firewall Region 2 Start Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H;   /* Firewall Region 2 Start Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L;   /* Firewall Region 2 End Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H;   /* Firewall Region 2 End Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL;   /* Firewall Region 3 Control Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0;   /* Firewall Region 3 Permission 0 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1;   /* Firewall Region 3 Permission 1 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2;   /* Firewall Region 3 Permission 2 Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L;   /* Firewall Region 3 Start Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H;   /* Firewall Region 3 Start Address High Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L;   /* Firewall Region 3 End Address Low Register */
    volatile uint32_t CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H;   /* Firewall Region 3 End Address High Register */
    volatile uint8_t  Resv_10240[1920];
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_14336[4064];
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
    volatile uint8_t  Resv_31744[17376];
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL;   /* Firewall Region 0 Control Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0;   /* Firewall Region 0 Permission 0 Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1;   /* Firewall Region 0 Permission 1 Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2;   /* Firewall Region 0 Permission 2 Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L;   /* Firewall Region 0 Start Address Low Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H;   /* Firewall Region 0 Start Address High Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L;   /* Firewall Region 0 End Address Low Register */
    volatile uint32_t CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H;   /* Firewall Region 0 End Address High Register */
} SDL_csi_cbass_fwRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL               (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0          (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1          (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2          (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L       (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H       (0x00000014U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L         (0x00000018U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H         (0x0000001CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL               (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0          (0x00000024U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1          (0x00000028U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2          (0x0000002CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L       (0x00000030U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H       (0x00000034U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L         (0x00000038U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H         (0x0000003CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL               (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0          (0x00000044U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1          (0x00000048U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2          (0x0000004CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L       (0x00000050U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H       (0x00000054U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L         (0x00000058U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H         (0x0000005CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL               (0x00000060U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0          (0x00000064U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1          (0x00000068U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2          (0x0000006CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L       (0x00000070U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H       (0x00000074U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L         (0x00000078U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H         (0x0000007CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL               (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0          (0x00000404U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1          (0x00000408U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2          (0x0000040CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L       (0x00000410U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H       (0x00000414U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L         (0x00000418U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H         (0x0000041CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL               (0x00000420U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0          (0x00000424U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1          (0x00000428U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2          (0x0000042CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L       (0x00000430U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H       (0x00000434U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L         (0x00000438U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H         (0x0000043CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL               (0x00000440U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0          (0x00000444U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1          (0x00000448U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2          (0x0000044CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L       (0x00000450U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H       (0x00000454U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L         (0x00000458U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H         (0x0000045CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL               (0x00000460U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0          (0x00000464U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1          (0x00000468U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2          (0x0000046CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L       (0x00000470U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H       (0x00000474U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L         (0x00000478U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H         (0x0000047CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL               (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0          (0x00000804U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1          (0x00000808U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2          (0x0000080CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L       (0x00000810U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H       (0x00000814U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L         (0x00000818U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H         (0x0000081CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL               (0x00000820U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0          (0x00000824U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1          (0x00000828U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2          (0x0000082CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L       (0x00000830U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H       (0x00000834U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L         (0x00000838U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H         (0x0000083CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL               (0x00000840U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0          (0x00000844U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1          (0x00000848U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2          (0x0000084CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L       (0x00000850U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H       (0x00000854U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L         (0x00000858U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H         (0x0000085CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL               (0x00000860U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0          (0x00000864U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1          (0x00000868U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2          (0x0000086CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L       (0x00000870U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H       (0x00000874U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L         (0x00000878U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H         (0x0000087CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL              (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0         (0x00001004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1         (0x00001008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2         (0x0000100CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L      (0x00001010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H      (0x00001014U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L        (0x00001018U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H        (0x0000101CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL              (0x00001020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0         (0x00001024U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1         (0x00001028U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2         (0x0000102CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L      (0x00001030U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H      (0x00001034U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L        (0x00001038U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H        (0x0000103CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL              (0x00001400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0         (0x00001404U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1         (0x00001408U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2         (0x0000140CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L      (0x00001410U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H      (0x00001414U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L        (0x00001418U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H        (0x0000141CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL              (0x00001420U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0         (0x00001424U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1         (0x00001428U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2         (0x0000142CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L      (0x00001430U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H      (0x00001434U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L        (0x00001438U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H        (0x0000143CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL              (0x00001800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0         (0x00001804U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1         (0x00001808U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2         (0x0000180CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L      (0x00001810U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H      (0x00001814U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L        (0x00001818U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H        (0x0000181CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL              (0x00001820U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0         (0x00001824U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1         (0x00001828U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2         (0x0000182CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L      (0x00001830U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H      (0x00001834U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L        (0x00001838U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H        (0x0000183CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL               (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0          (0x00002004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1          (0x00002008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2          (0x0000200CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L       (0x00002010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H       (0x00002014U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L         (0x00002018U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H         (0x0000201CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL               (0x00002020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0          (0x00002024U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1          (0x00002028U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2          (0x0000202CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L       (0x00002030U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H       (0x00002034U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L         (0x00002038U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H         (0x0000203CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL               (0x00002040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0          (0x00002044U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1          (0x00002048U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2          (0x0000204CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L       (0x00002050U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H       (0x00002054U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L         (0x00002058U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H         (0x0000205CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL               (0x00002060U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0          (0x00002064U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1          (0x00002068U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2          (0x0000206CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L       (0x00002070U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H       (0x00002074U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L         (0x00002078U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H         (0x0000207CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL              (0x00002800U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0         (0x00002804U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1         (0x00002808U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2         (0x0000280CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L      (0x00002810U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H      (0x00002814U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L        (0x00002818U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H        (0x0000281CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL                (0x00003800U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0           (0x00003804U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1           (0x00003808U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2           (0x0000380CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L        (0x00003810U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H        (0x00003814U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L          (0x00003818U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H          (0x0000381CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL    (0x00007C00U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0 (0x00007C04U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1 (0x00007C08U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2 (0x00007C0CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L (0x00007C10U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H (0x00007C14U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L (0x00007C18U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H (0x00007C1CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004500U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04500000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004500U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04500FFFU)

/* CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004504U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x04504000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004504U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x04504FFFU)

/* CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004508U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_RESETVAL (0x04508000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004508U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_RESETVAL (0x04508FFFU)

/* CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002A30U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_RESETVAL (0x02A30000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002A30U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_RESETVAL (0x02A30FFFU)

/* CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004510U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04510000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004510U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04510FFFU)

/* CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004514U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x04514000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004514U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x04514FFFU)

/* CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004518U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_L_RESETVAL (0x04518000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004518U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_L_RESETVAL (0x04518FFFU)

/* CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002A31U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_L_RESETVAL (0x02A31000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002A31U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_L_RESETVAL (0x02A31FFFU)

/* CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF1_VBUSP_FW_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004520U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04520000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004520U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04520FFFU)

/* CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004524U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x04524000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004524U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x04524FFFU)

/* CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004528U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_L_RESETVAL (0x04528000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004528U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_L_RESETVAL (0x04528FFFU)

/* CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_CONTROL_RESETVAL      (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002A32U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_L_RESETVAL (0x02A32000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002A32U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_L_RESETVAL (0x02A32FFFU)

/* CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_RX_IF2_VBUSP_FW_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004581U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04581000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004581U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04581FFFU)

/* DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004580U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x04580000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004580U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x04580FFFU)

/* DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX0_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004591U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04591000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004591U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04591FFFU)

/* DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004590U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x04590000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004590U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x04590FFFU)

/* DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX1_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x000045A1U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x045A1000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x000045A1U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x045A1FFFU)

/* DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x000045A0U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x045A0000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x000045A0U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x045A0FFFU)

/* DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_RX2_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_CONTROL_RESETVAL      (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04400000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04400FFFU)

/* CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_CONTROL_RESETVAL      (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004404U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_L_RESETVAL (0x04404000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004404U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_L_RESETVAL (0x04404FFFU)

/* CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_1_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_CONTROL_RESETVAL      (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004408U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_L_RESETVAL (0x04408000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004408U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_L_RESETVAL (0x04408FFFU)

/* CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_2_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_MASK   (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_SHIFT  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_ENABLE_MAX    (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_MASK     (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_SHIFT    (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_LOCK_MAX      (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_CONTROL_RESETVAL      (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_0_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_1_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_PERMISSION_2_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002A38U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_L_RESETVAL (0x02A38000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002A38U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_L_RESETVAL (0x02A38FFFU)

/* CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_TX_IF0_VBUSP_FW_REGION_3_END_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_TX0_SLV_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_ENABLE_MASK  (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_ENABLE_MAX   (0x0000000FU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_LOCK_MASK    (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_LOCK_SHIFT   (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_LOCK_MAX     (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_CONTROL_RESETVAL     (0x00000000U)

/* DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00004480U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x04480000U)

/* DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00004480U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x04480FFFU)

/* DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_DPHY_TX0_SLV_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_ENABLE_MASK    (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_ENABLE_SHIFT   (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_ENABLE_MAX     (0x0000000FU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_LOCK_MASK      (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_LOCK_SHIFT     (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_LOCK_RESETVAL  (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_LOCK_MAX       (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_CONTROL_RESETVAL       (0x00000000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_0_RESETVAL  (0x00000000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_1_RESETVAL  (0x00000000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_PERMISSION_2_RESETVAL  (0x00000000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00003410U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x03410000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00003410U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x03410FFFU)

/* CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CSI_PSILSS0_CFG_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_MASK (0x0000000FU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_ENABLE_MAX (0x0000000FU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_LOCK_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_BACKGROUND_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_CACHE_MODE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_CONTROL_RESETVAL (0x00000000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0 */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_0_RESETVAL (0x00000000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1 */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_1_RESETVAL (0x00000000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2 */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MASK (0x00000001U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MASK (0x00000002U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_SHIFT (0x00000001U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MASK (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_SHIFT (0x00000002U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MASK (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_SHIFT (0x00000003U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MASK (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_SHIFT (0x00000004U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MASK (0x00000020U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_SHIFT (0x00000005U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MASK (0x00000040U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_SHIFT (0x00000006U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MASK (0x00000080U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_SHIFT (0x00000007U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_SEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MASK (0x00000100U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_SHIFT (0x00000008U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MASK (0x00000200U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_SHIFT (0x00000009U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MASK (0x00000400U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_SHIFT (0x0000000AU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MASK (0x00000800U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_SHIFT (0x0000000BU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_SUPV_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MASK (0x00001000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_WRITE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MASK (0x00002000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_SHIFT (0x0000000DU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_READ_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MASK (0x00004000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_SHIFT (0x0000000EU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_CACHEABLE_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MASK (0x00008000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_SHIFT (0x0000000FU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_NONSEC_USER_DEBUG_MAX (0x00000001U)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_MASK (0x00FF0000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_SHIFT (0x00000010U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_PRIV_ID_MAX (0x000000FFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_PERMISSION_2_RESETVAL (0x00000000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_RESETVAL (0x00002A88U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_START_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_L_RESETVAL (0x02A88000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_START_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_START_ADDRESS_H_RESETVAL (0x00000000U)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MASK (0xFFFFF000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_SHIFT (0x0000000CU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_RESETVAL (0x00002A88U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_L_MAX (0x000FFFFFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MASK (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_RESETVAL (0x00000FFFU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_END_ADDRESS_LSB_MAX (0x00000FFFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_L_RESETVAL (0x02A88FFFU)

/* CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H */

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MASK (0x0000FFFFU)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_SHIFT (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_RESETVAL (0x00000000U)
#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_END_ADDRESS_H_MAX (0x0000FFFFU)

#define SDL_CSI_CBASS_FW_CBASS_CSI0_CBASS_ERR_SLV_FW_REGION_0_END_ADDRESS_H_RESETVAL (0x00000000U)

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
} SDL_csi_cbass_errRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define SDL_CSI_CBASS_ERR_PID                                                      (0x00000000U)
#define SDL_CSI_CBASS_ERR_DESTINATION_ID                                           (0x00000004U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0                                (0x00000024U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1                                (0x00000028U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA0                                  (0x0000002CU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA1                                  (0x00000030U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2                                  (0x00000034U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA3                                  (0x00000038U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_RAW_STAT                                        (0x00000050U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLED_STAT                                    (0x00000054U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_SET                                      (0x00000058U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_CLR                                      (0x0000005CU)
#define SDL_CSI_CBASS_ERR_EOI                                                      (0x00000060U)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* PID */

#define SDL_CSI_CBASS_ERR_PID_MINOR_MASK                                           (0x0000003FU)
#define SDL_CSI_CBASS_ERR_PID_MINOR_SHIFT                                          (0x00000000U)
#define SDL_CSI_CBASS_ERR_PID_MINOR_RESETVAL                                       (0x00000000U)
#define SDL_CSI_CBASS_ERR_PID_MINOR_MAX                                            (0x0000003FU)

#define SDL_CSI_CBASS_ERR_PID_CUSTOM_MASK                                          (0x000000C0U)
#define SDL_CSI_CBASS_ERR_PID_CUSTOM_SHIFT                                         (0x00000006U)
#define SDL_CSI_CBASS_ERR_PID_CUSTOM_RESETVAL                                      (0x00000000U)
#define SDL_CSI_CBASS_ERR_PID_CUSTOM_MAX                                           (0x00000003U)

#define SDL_CSI_CBASS_ERR_PID_MAJOR_MASK                                           (0x00000700U)
#define SDL_CSI_CBASS_ERR_PID_MAJOR_SHIFT                                          (0x00000008U)
#define SDL_CSI_CBASS_ERR_PID_MAJOR_RESETVAL                                       (0x00000001U)
#define SDL_CSI_CBASS_ERR_PID_MAJOR_MAX                                            (0x00000007U)

#define SDL_CSI_CBASS_ERR_PID_RTL_MASK                                             (0x0000F800U)
#define SDL_CSI_CBASS_ERR_PID_RTL_SHIFT                                            (0x0000000BU)
#define SDL_CSI_CBASS_ERR_PID_RTL_RESETVAL                                         (0x00000007U)
#define SDL_CSI_CBASS_ERR_PID_RTL_MAX                                              (0x0000001FU)

#define SDL_CSI_CBASS_ERR_PID_FUNC_MASK                                            (0x0FFF0000U)
#define SDL_CSI_CBASS_ERR_PID_FUNC_SHIFT                                           (0x00000010U)
#define SDL_CSI_CBASS_ERR_PID_FUNC_RESETVAL                                        (0x00000600U)
#define SDL_CSI_CBASS_ERR_PID_FUNC_MAX                                             (0x00000FFFU)

#define SDL_CSI_CBASS_ERR_PID_BU_MASK                                              (0x30000000U)
#define SDL_CSI_CBASS_ERR_PID_BU_SHIFT                                             (0x0000001CU)
#define SDL_CSI_CBASS_ERR_PID_BU_RESETVAL                                          (0x00000002U)
#define SDL_CSI_CBASS_ERR_PID_BU_MAX                                               (0x00000003U)

#define SDL_CSI_CBASS_ERR_PID_SCHEME_MASK                                          (0xC0000000U)
#define SDL_CSI_CBASS_ERR_PID_SCHEME_SHIFT                                         (0x0000001EU)
#define SDL_CSI_CBASS_ERR_PID_SCHEME_RESETVAL                                      (0x00000001U)
#define SDL_CSI_CBASS_ERR_PID_SCHEME_MAX                                           (0x00000003U)

#define SDL_CSI_CBASS_ERR_PID_RESETVAL                                             (0x66003900U)

/* DESTINATION_ID */

#define SDL_CSI_CBASS_ERR_DESTINATION_ID_DEST_ID_MASK                              (0x000000FFU)
#define SDL_CSI_CBASS_ERR_DESTINATION_ID_DEST_ID_SHIFT                             (0x00000000U)
#define SDL_CSI_CBASS_ERR_DESTINATION_ID_DEST_ID_RESETVAL                          (0x00000000U)
#define SDL_CSI_CBASS_ERR_DESTINATION_ID_DEST_ID_MAX                               (0x000000FFU)

#define SDL_CSI_CBASS_ERR_DESTINATION_ID_RESETVAL                                  (0x00000000U)

/* EXCEPTION_LOGGING_HEADER0 */

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_MASK                   (0x000000FFU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_SHIFT                  (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_RESETVAL               (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_DEST_ID_MAX                    (0x000000FFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_MASK                    (0x00FFFF00U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_SHIFT                   (0x00000008U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_RESETVAL                (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_SRC_ID_MAX                     (0x0000FFFFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_MASK                    (0xFF000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_SHIFT                   (0x00000018U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_RESETVAL                (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_TYPE_F_MAX                     (0x000000FFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER0_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_HEADER1 */

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_MASK                      (0x00FF0000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_SHIFT                     (0x00000010U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_CODE_MAX                       (0x000000FFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_MASK                     (0xFF000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_SHIFT                    (0x00000018U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_GROUP_MAX                      (0x000000FFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_HEADER1_RESETVAL                       (0x00000000U)

/* EXCEPTION_LOGGING_DATA0 */

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_MASK                      (0xFFFFFFFFU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_SHIFT                     (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA0_ADDR_L_MAX                       (0xFFFFFFFFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA0_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA1 */

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_MASK                      (0x0000FFFFU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_SHIFT                     (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA1_ADDR_H_MAX                       (0x0000FFFFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA1_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA2 */

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_MASK                     (0x000000FFU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_SHIFT                    (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_ID_MAX                      (0x000000FFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_MASK                      (0x00000100U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_SHIFT                     (0x00000008U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_RESETVAL                  (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_SECURE_MAX                       (0x00000001U)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_MASK                        (0x00000200U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_SHIFT                       (0x00000009U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_RESETVAL                    (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_PRIV_MAX                         (0x00000001U)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_MASK                   (0x00000400U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_SHIFT                  (0x0000000AU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_RESETVAL               (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_CACHEABLE_MAX                    (0x00000001U)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_MASK                       (0x00000800U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_SHIFT                      (0x0000000BU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_RESETVAL                   (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_DEBUG_MAX                        (0x00000001U)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_MASK                        (0x00001000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_SHIFT                       (0x0000000CU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_RESETVAL                    (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_READ_MAX                         (0x00000001U)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_MASK                       (0x00002000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_SHIFT                      (0x0000000DU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_RESETVAL                   (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_WRITE_MAX                        (0x00000001U)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_MASK                     (0x0FFF0000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_SHIFT                    (0x00000010U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_ROUTEID_MAX                      (0x00000FFFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA2_RESETVAL                         (0x00000000U)

/* EXCEPTION_LOGGING_DATA3 */

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_MASK                     (0x000003FFU)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_SHIFT                    (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_RESETVAL                 (0x00000000U)
#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA3_BYTECNT_MAX                      (0x000003FFU)

#define SDL_CSI_CBASS_ERR_EXCEPTION_LOGGING_DATA3_RESETVAL                         (0x00000000U)

/* ERR_INTR_RAW_STAT */

#define SDL_CSI_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_MASK                              (0x00000001U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_SHIFT                             (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_RESETVAL                          (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_RAW_STAT_INTR_MAX                               (0x00000001U)

#define SDL_CSI_CBASS_ERR_ERR_INTR_RAW_STAT_RESETVAL                               (0x00000000U)

/* ERR_INTR_ENABLED_STAT */

#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_MASK                  (0x00000001U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_SHIFT                 (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_RESETVAL              (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLED_STAT_ENABLED_INTR_MAX                   (0x00000001U)

#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLED_STAT_RESETVAL                           (0x00000000U)

/* ERR_INTR_ENABLE_SET */

#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_MASK                 (0x00000001U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_SHIFT                (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_RESETVAL             (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_SET_INTR_ENABLE_SET_MAX                  (0x00000001U)

#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_SET_RESETVAL                             (0x00000000U)

/* ERR_INTR_ENABLE_CLR */

#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_MASK                 (0x00000001U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_SHIFT                (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_RESETVAL             (0x00000000U)
#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_CLR_INTR_ENABLE_CLR_MAX                  (0x00000001U)

#define SDL_CSI_CBASS_ERR_ERR_INTR_ENABLE_CLR_RESETVAL                             (0x00000000U)

/* EOI */

#define SDL_CSI_CBASS_ERR_EOI_WR_MASK                                              (0x0000FFFFU)
#define SDL_CSI_CBASS_ERR_EOI_WR_SHIFT                                             (0x00000000U)
#define SDL_CSI_CBASS_ERR_EOI_WR_RESETVAL                                          (0x00000000U)
#define SDL_CSI_CBASS_ERR_EOI_WR_MAX                                               (0x0000FFFFU)

#define SDL_CSI_CBASS_ERR_EOI_RESETVAL                                             (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
