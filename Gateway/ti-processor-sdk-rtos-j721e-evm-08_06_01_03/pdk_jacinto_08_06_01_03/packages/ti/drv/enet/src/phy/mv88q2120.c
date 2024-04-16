/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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
 */

/*!
 * \file  generic_phy.c
 *
 * \brief This file contains the implementation of the generic Ethernet PHY.
 *        It provides the basic functionality allowed with IEEE standard
 *        registers.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdarg.h>
#include <ti/drv/enet/include/core/enet_utils.h>
#include <ti/drv/enet/priv/core/enet_trace_priv.h>
#include <ti/drv/enet/include/phy/enetphy.h>
#include <ti/drv/enet/include/phy/mv88q2120.h>
#include "enetphy_priv.h"
#include "mv88q2120_priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static int32_t Mv88q2120_config(EnetPhy_Handle hPhy,
                              const EnetPhy_Cfg *cfg,
                              EnetPhy_Mii mii);
							  
static bool Mv88q2120_isPhyDevSupported(EnetPhy_Handle hPhy,
                                         const EnetPhy_Version *version);

static bool Mv88q2120_isMacModeSupported(EnetPhy_Handle hPhy,
                                          EnetPhy_Mii mii);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

EnetPhy_Drv gEnetPhyDrv88q2120 =
{
    .name               = "mv88q2120",
    .isPhyDevSupported  = Mv88q2120_isPhyDevSupported,
    .isMacModeSupported = Mv88q2120_isMacModeSupported,
    .config             = Mv88q2120_config,
    .reset              = Mv88q2120_reset,
    .isResetComplete    = Mv88q2120_isResetComplete,
    .readExtReg         = Mv88q2120_readExtReg,
    .writeExtReg        = Mv88q2120_writeExtReg,
    .printRegs          = Mv88q2120_printRegs,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static int32_t Mv88q2120_config(EnetPhy_Handle hPhy,
                              const EnetPhy_Cfg *cfg,
                              EnetPhy_Mii mii)
{
	int32_t status = ENETPHY_SOK;
	
    return status;
}

static bool Mv88q2120_isPhyDevSupported(EnetPhy_Handle hPhy,
                                         const EnetPhy_Version *version)
{
	bool supported = false;
	if (version->oui == 0x002b0098)
    {
        supported = true;
    }
	ENETTRACE_INFO(" PHY(%u), supported:0x%x\n", hPhy->addr, supported);
    return supported;
}

static bool Mv88q2120_isMacModeSupported(EnetPhy_Handle hPhy,
                                          EnetPhy_Mii mii)
{
    bool supported;
    switch (mii)
    {
        case ENETPHY_MAC_MII_GMII:
        case ENETPHY_MAC_MII_RGMII:
            supported = true;
            break;
        default:
            supported = false;
            break;
    }
	ENETTRACE_INFO(" PHY(%u), supported:0x%x\n", hPhy->addr, supported);
    return supported;
}

void Mv88q2120_reset(EnetPhy_Handle hPhy)
{
	uint16_t val;
    /* Reset the PHY */
	EnetPhy_rmwC45Reg(hPhy, 3, 0x8000, 0x8000, 0x8000);
	ENETTRACE_DBG(" RGMII SW reset\n");
	EnetPhy_readC45Reg(hPhy, 3, 0x8000, &val);
	ENETTRACE_DBG(" PHY(%u) 3.0x8000(0x%x)\n", hPhy->addr, val);
	EnetPhy_rmwC45Reg(hPhy, 3, 0x8000, 0x8000, 0x0000);
	
	// PMA reset
	EnetPhy_rmwC45Reg(hPhy, 1, 0x0000, 0x8000, 0x8000);
	EnetPhy_rmwC45Reg(hPhy, 1, 0x0900, 0x8000, 0x8000);
	val = EnetPhy_readC45Reg(hPhy, 1, 0x0900, &val);
	ENETTRACE_DBG(" PHY(%u) 1.0x0900(0x%x)\n", hPhy->addr, val);
	// PCS reset
	EnetPhy_rmwC45Reg(hPhy, 3, 0x0000, 0x8000, 0x8000);
	EnetPhy_rmwC45Reg(hPhy, 3, 0x0900, 0x8000, 0x8000);	
	val = EnetPhy_readC45Reg(hPhy, 3, 0x0900, &val);
	ENETTRACE_DBG(" PHY(%u) 3.0x0900(0x%x)\n", hPhy->addr, val);
}

bool Mv88q2120_isResetComplete(EnetPhy_Handle hPhy)
{
    int32_t status;
    uint16_t val;
    bool complete = false;

	
	EnetPhy_readC45Reg(hPhy, 1, 0x0900, &val);
	if((val & 0x8000) == 0x00)
	{
		EnetPhy_readC45Reg(hPhy, 3, 0x0900, &val);
		if((val & 0x8000) == 0x00)
			complete = true;
	}
    ENETTRACE_DBG(" PHY(%u) reset is %s complete\n", hPhy->addr, complete ? "" : "not");
	
    return complete;
}

int32_t Mv88q2120_readExtReg(EnetPhy_Handle hPhy,
                              uint32_t reg,
                              uint16_t *val)
{
    int32_t status = -1;
	ENETTRACE_DBG("PHY(%u), reg:%u\n", hPhy->addr, reg);


    return status;
}

int32_t Mv88q2120_writeExtReg(EnetPhy_Handle hPhy,
                               uint32_t reg,
                               uint16_t val)
{
    int32_t status = -1;
	ENETTRACE_DBG("PHY(%u), reg:%u, val:%u\n", hPhy->addr, reg, val);

    return status;
}

void Mv88q2120_printRegs(EnetPhy_Handle hPhy)
{
    uint32_t i;
    uint16_t val;
	ENETTRACE_DBG("PHY(%u)\n", hPhy->addr);

}
