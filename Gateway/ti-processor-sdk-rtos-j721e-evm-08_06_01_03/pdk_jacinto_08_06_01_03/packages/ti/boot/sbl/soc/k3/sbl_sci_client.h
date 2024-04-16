/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SBL_SCI_CLIENT_H
#define SBL_SCI_CLIENT_H

#include "sbl_log.h"
#include "sbl_profile.h"
#include <ti/board/board.h>
#include <ti/drv/sciclient/sciclient.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SBL_NEVER_AUTH_APP         (0x55555555u)
#define SBL_ALWAYS_AUTH_APP        (0xAAAAAAAAu)
#define SBL_SYSFW_MAX_SIZE         (0x42000U)


#define SBL_SYS_STATUS_REG              (0x44234100U)
#define SBL_SYS_STATUS_DEV_TYPE_MASK    (0x0000000FU)
#define SBL_SYS_STATUS_DEV_SUBTYPE_MASK (0x00000F00U)


#define SBL_SYS_STATUS_DEV_TYPE_GP      (0x3U)
#define SBL_SYS_STATUS_DEV_TYPE_TEST    (0x5U)
#define SBL_SYS_STATUS_DEV_SUBTYPE_FS   (0x00000A00U)

/**
 * @brief - SBL_SciClientInit() - function to do load DMSC firmware.
 *
 * @param   devGroup - Indicate which dev group to use  
 *
 * @return - none
 *      Loops forever if error occurs
 *
 */
void SBL_SciClientInit(uint32_t devGroup);

/**
 * @brief - SBL_ReadSysfwImage() - function to do read DMSC firmware.
 *
 * @param pBuffer        [IN] Pointer to buffer large enough for SYSFW
 * @param num_bytes      [IN] Size in bytes of system firmware bnary
 *
 * @return CSL_PASS on success, CSL_EFAIL failure
 *
 *      Loops forever if error occurs
 *
 */
int32_t SBL_ReadSysfwImage(void **pBuffer, uint32_t num_bytes);

/**
 * @brief - SBL_IsAuthReq() - function to check if SBL needs to authenticate app
 *
 * @param  none
 *
 * @return SBL_ALWAYS_AUTH_APP if apps have to be authenticated and/decrypted before being executed (SE subtype)
 *         SBL_NEVER_AUTH_APP  if app authentication must not be done (no SMPK/BMPK present)
 *
 *      Loops forever if error occurs
 *
 */
uint32_t SBL_IsAuthReq(void);

extern const struct tisci_boardcfg_pm gBoardConfigLow_pm;

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
