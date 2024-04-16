/*
 *  Copyright (C) 2023-2023 Texas Instruments Incorporated
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
 *  \file sciclient_fw_notify.h
 *
 */

#ifndef SCICLIENT_FW_NOTIFY_H_
#define SCICLIENT_FW_NOTIFY_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define FW_MAX_ISR_INPUTS 27
#define SIZE_EXCEPTION_LOG_REG 4
#define EXCEPTION_INTERRUPT_CNT 2
#define DMSC_FW_EXCP_REG (CSL_STD_FW_WKUP_DMSC0_IIRAM_SLV_IRAM_START)
#define CMBN_FW_EXCP_REG (CSL_STD_FW_NAVSS0_RINGACC_0_RINGACC0_SRC_UDMASS_RINGACC0_SRC_FIFOS_START)

/*Firewall exception logging registers*/
#define DMSC_FW_EXCP_LOG_REG    (0x45B00000U)
#define CMBN_FW_EXCP_LOG_REG_0  (0x45B02000U)
#define CMBN_FW_EXCP_LOG_REG_1  (0x45B06000U)
#define CMBN_FW_EXCP_LOG_REG_3  (0x45B0C000U)
#define CMBN_FW_EXCP_LOG_REG_5  (0x45B20400U)
#define CMBN_FW_EXCP_LOG_REG_6  (0x45B21400U)
#define CMBN_FW_EXCP_LOG_REG_7  (0x45B20000U)
#define CMBN_FW_EXCP_LOG_REG_8  (0x45B21800U)
#define CMBN_FW_EXCP_LOG_REG_9  (0x45B21C00U)
#define CMBN_FW_EXCP_LOG_REG_10 (0x45B20800U)
#define CMBN_FW_EXCP_LOG_REG_11 (0x45B20C00U)
#define CMBN_FW_EXCP_LOG_REG_12 (0x45B21000U)
#define CMBN_FW_EXCP_LOG_REG_13 (0x45B22000U)
#define CMBN_FW_EXCP_LOG_REG_14 (0x45B22400U)
#define CMBN_FW_EXCP_LOG_REG_15 (0x45B22C00U)
#define CMBN_FW_EXCP_LOG_REG_20 (0x45B10400U)
#define CMBN_FW_EXCP_LOG_REG_24 (0x45B17000U)
#define CMBN_FW_EXCP_LOG_REG_25 (0x45B18000U)
#define CMBN_FW_EXCP_LOG_REG_26 (0x45B12000U)
#define CMBN_FW_EXCP_LOG_REG_27 (0x45B12400U)
#define CMBN_FW_EXCP_LOG_REG_28 (0x45B0A000U)
#define CMBN_FW_EXCP_LOG_REG_29 (0x45B0B800U)
#define CMBN_FW_EXCP_LOG_REG_30 (0x45B0B000U)
#define CMBN_FW_EXCP_LOG_REG_40 (0x45B0D000U)
#define CMBN_FW_EXCP_LOG_REG_41 (0x45B0D400U)
#define CMBN_FW_EXCP_LOG_REG_42 (0x45B0D800U)
#define CMBN_FW_EXCP_LOG_REG_43 (0x45B0DC00U)
#define CMBN_FW_EXCP_LOG_REG_48 (0x45B04000U)  

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */


/**
 * \brief structure definition for firewall exception data
 *
 * \param rev      - Revision Register
 * \param dest_id  - Destination ID Register
 * \param rsvd_32  - Padding
 * \param ctrl     - Exception Logging control
 * \param hdr      - Exception Logging slot 0 header 2 Words
 * \param data     - Exception Logging slot 0 data 4 Words
 * \param rsvd_64  - Padding
 * \param pend_set - Exception Pending Set Register
 * \param pend_clr - Exception Pending Clear Register
 */
typedef struct
{
    uint32_t rev;
    uint32_t dest_id;
    uint32_t rsvd_32[6];
    uint32_t ctrl;
    uint32_t hdr[2];
    uint32_t data[4];
    uint32_t rsvd_64;
    uint32_t pend_set;
    uint32_t pend_clr;
} App_fwExceptionData_t; 


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Callback function for dmsc firewall exception notification interrupt */
void App_fwNotiIsrDmsc(void);
/* Callback function for cmbn firewall exception notification interrupt */
void App_fwNotiIsrCmbn(void);
/* Function to print firewall exception logging information */
void App_fwExcepSendTrace(App_fwExceptionData_t *ptr);
/* Callback function for abort handler */
void App_fwAbortHandlerIsr(void);

#endif /* #ifndef SCICLIENT_FW_NOTIFY_H_ */


