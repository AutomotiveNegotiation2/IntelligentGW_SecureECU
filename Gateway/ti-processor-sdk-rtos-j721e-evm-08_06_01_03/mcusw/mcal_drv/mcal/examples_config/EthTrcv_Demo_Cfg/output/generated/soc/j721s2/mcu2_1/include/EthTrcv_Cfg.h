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
 *  \file     EthTrcv_Cfg.h
 *
 *  \brief    This file contains generated pre compile configuration file for
 *            Ethernet Transceiver MCAL driver
 *
 */

/**
 *  \defgroup MCAL_ETHTRCV_CFG EthTrcv Configuration
 *
 *  This files defines EthTrcv MCAL configuration structures
 *  @{
 */

#ifndef ETHTRCV_CFG_H_
#define ETHTRCV_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Dem.h"
#include "Os.h"
 

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
*  \brief ETHTRCV Build Variant.
*   Build variant pre-compile (STD_ON/STD_OFF)
*/
#define ETHTRCV_PRE_COMPILE_VARIANT      (STD_ON)


/**
 *  \name EthTrcv Driver Configuration SW Version Info
 *
 *  Pre-compile switches for enabling/disabling ETHTRCV MCAL APIs
 *  @{
 */
/** \brief Enable/Disable EthTrcv_GetVersionInfo()*/
#define ETHTRCV_VERSION_INFO_API        (STD_ON)/** \brief Enable/Disable DEV error detection */
#define ETHTRCV_DEV_ERROR_DETECT        (STD_ON)/* @} */

/** \brief EthTrcv max number of controllers. */
#define ETHTRCV_MAX_CONTROLLER          (2U)

/** \brief EthTrcv max number of configurations. */
#define ETHTRCV_MAX_CONTROLLER_CFGS     (2U)

/**
 *  \name EthTrcv Controller names
 *
 *  Symbolic names for the EthTrcvControllerId.
 *  @{
 */
/* Requirements : MCAL-1750 */
#define ETHTRCV_CONTROLLER_ID_0         (0U)
/* @} */

/**
 *  \name EthTrcv Transceiver names
 *
 *  Symbolic names for the EthTrcv.
 *  @{
 */
#define ETHTRCV_CONTROLLER_ID_0_TRCV_ID_0        (0U)
/* @} */


/** \brief EthTrcv auto-negotiation wait count
 *       Transceiver delay after auto-negotiation started to auto-negotiation
 *       completed. Transceiver (PHY) sets auto-negotiation status bit in
 *       status register once it is complete. Depending on Transceiver type,
 *       MDIO frequency it will take different time. change count value if
 *       transceiver detection fails in auto-negotiation.
 */
/* For auto-negotiation configuring wait count to 100ms
 * (32K/10 X 31.25ms each tick = ~1s)
 */
#define ETHTRCV_AUTONEG_STATUS_WAITCOUNT_TICKS (0x7d0U)

/** \brief  Wait for link status to become up after configuration */
#define ETHTRCV_LINKSTATUS_WAITCOUNT_TICKS     (0x7d0U)

/* Requirements : MCAL-1839 */
/** \brief Enable/disable Ethernet transceiver EthTrcvWakeUpSupport APIs. */
#define ETHTRCV_WAKEUPSUPPORT_API             (ETHTRCV_WAKEUP_NOT_SUPPORTED)

/* Requirements : MCAL-1781 */
/** \brief Enable/disable Ethernet transceiver settransceivermode API */
#define ETHTRCV_SETTRANSCEIVERMODE_API        (STD_ON)
/* Requirements : MCAL-1788 */
/** \brief Enable/disable Ethernet transceiver gettransceivermodeapi API */
#define ETHTRCV_GETTRANSCEIVERMODE_API        (STD_ON)
/* Requirements : MCAL-1794 */
/** \brief Enable/disable Ethernet transceiver startautonegotiation API */
#define ETHTRCV_STARTAUTONEGOTIATION_API      (STD_ON)
/* Requirements : MCAL-1801 */
/** \brief Enable/disable Ethernet transceiver getlinkstate API */
#define ETHTRCV_GETLINKSTATE_API        (STD_ON)
/* Requirements : MCAL-1808 */
/**  \brief Enable/disable Ethernet transceiver getbaudrate API */
#define ETHTRCV_GETBAUDRATE_API         (STD_ON)
/* Requirements : MCAL-1815 */
/**  \brief Enable/disable Ethernet transceiver getduplexmode API */
#define ETHTRCV_GETDUPLEXMODE_API       (STD_ON)
/** \brief Counter ID for counter used to count wait ticks */
#define ETHTRCV_OS_COUNTER_ID          ((CounterType)OsCounter_0)

/** \brief ETH timeout */
#define ETHTRCV_TIMEOUT_DURATION       (160000U)

/**
 *  \name ETHTRCV DEM Error codes to report
 *
 *  Pre-compile switches for enabling/disabling DEM events
 *  @{
 */
#define DemConf_DemEventParameter_ETHTRCV_DEM_NO_EVENT (0xFFFFU)
#define ETHTRCV_DEM_NO_EVENT DemConf_DemEventParameter_ETHTRCV_DEM_NO_EVENT

#ifndef ETHTRCV_E_HARDWARE_ERROR
/** \brief Hardware failed */
#define ETHTRCV_E_HARDWARE_ERROR        (ETHTRCV_DEM_NO_EVENT)
#endif

#ifndef ETHTRCV_E_ACCESS
/** \brief Hardware failed */
#define ETHTRCV_E_ACCESS                (ETHTRCV_DEM_NO_EVENT)
#endif

/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/** \brief ETHTRCV Configuration struct declaration */
extern struct EthTrcv_ConfigType_s EthTrcvConfig_0_PC;

/**< \brief Configuration of the driver */
#define ETHTRCV_DRV_CONFIG_0    ((const EthTrcv_ConfigType *) &EthTrcvConfig_0_PC)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* ETHTRCV_CFG_H_ */

/* @} */

