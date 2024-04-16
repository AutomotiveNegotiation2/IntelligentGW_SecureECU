/*
*
* Copyright (c) 2023 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/**
 *  \file     EthTrcv_Cfg.c
 *
 *  \brief    This file contains generated configuration for Ethernet
 *            Transceiver MCAL driver
 *
 */
 

#include "EthTrcv.h"
#include "phy/Dp83867.h"
/*******************************************************************************
 * Eth Trcv Configuration
 ******************************************************************************/
#define ETHTRCV_START_SEC_CONFIG_DATA
#include "EthTrcv_MemMap.h"

ETHTRCV_CONFIG_DATA_SECTION VAR(Dp83867_ConfigType, ETHTRCV_CONFIG_DATA)
    Dp83867_Cfg =
{
    .txClkShiftEnable           = TRUE,
    /**< Enable RGMII TX clock shift */
    .rxClkShiftEnable           = TRUE,
    /**< Enable RGMII RX clock shift */
    .txDelayInPs                = 2000U,
    /**< TX delay in pico seconds (2.00ns to 4.00ns) */
    .rxDelayInPs                = 2000U,
    /**< RX delay in pico seconds (2.00ns to 4.00ns) */
    .outputImpedanceInMilliOhms = 35000U,
    /**< Output impedance in milli-ohms (35 to 70ohms) */
    .txFifoDepth                = 4U,
    /**< TX FIFO Depth (3, 4, 6 or 8 bytes/nibbles) */

};

ETHTRCV_CONFIG_DATA_SECTION VAR(struct EthTrcv_ConfigType_s, ETHTRCV_CONFIG_DATA)
    EthTrcvConfig_0_PC =
{
    .ctrlIdx        = 0U,
    /**< Controller index */
    .trcvIdx        = 0U,
    /**< Index of the transceiver */
    .miiIdx         = 0U,
    /**< PHY Address */
    .isGigCapab     = TRUE,
    /**< Phy gigabit capability */
    .enableAutoNeg  = TRUE,
    /**< Enable Auto Negotiations */
    .advertiseCapab =(
            ETHERNET_ADV_CAPAB_100_HALF |
            ETHERNET_ADV_CAPAB_100_FULL |
            ETHERNET_ADV_CAPAB_1000_FULL ),
    /**< Phy capability advertisement */
    .linkPartCapab =
        (uint32)(0U
                ),
    /**< Link partner capability */
    .baudRate       = (ETHTRCV_BAUD_RATE_1000MBIT),
    /**< Phy operating speed */
    .duplexMode     = ETHTRCV_DUPLEX_MODE_FULL,
    /**< Phy operating mode full-duplexMode, half-duplex */
    .loopback       = FALSE,
    /**< Enable loopback in PHY : Expected to be used for testing */
    .phyId          = 0x2000a231U,
    /**< PHY Identifier */
    .extendedConfig = &Dp83867_Cfg
    /**< Dp83867 extended configuration */
};

#define ETHTRCV_STOP_SEC_CONFIG_DATA
#include "EthTrcv_MemMap.h"

/*******************************************************************************
 *  End of File: EthTrcv_Cfg.c
 ******************************************************************************/
