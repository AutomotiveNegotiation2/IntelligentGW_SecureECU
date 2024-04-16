/*
 *
 * Copyright (c) 2021 Texas Instruments Incorporated
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

/*!
 * \file  ethremotecfg_virtport.h
 *
 * \brief This file contains the type definitions and helper macros for
 *        Ethernet Firmware's Virtual Port.
 */

#ifndef ETHREMOTECFG_VIRTPORT_H_
#define ETHREMOTECFG_VIRTPORT_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/enet/enet.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*!
 * \brief Virtual port id.
 */
typedef enum EthRemoteCfg_VirtPort_e
{
    /*! Virtual switch port 0. */
    ETHREMOTECFG_SWITCH_PORT_0,

    /*! Virtual switch port 1. */
    ETHREMOTECFG_SWITCH_PORT_1,

    /*! Virtual switch port 2. */
    ETHREMOTECFG_SWITCH_PORT_2,

    /*! Virtual switch port 3. */
    ETHREMOTECFG_SWITCH_PORT_3,

    /*! Last virtual switch port id. */
    ETHREMOTECFG_SWITCH_PORT_LAST = ETHREMOTECFG_SWITCH_PORT_3,

    /*! Virtual MAC port 1. */
    ETHREMOTECFG_MAC_PORT_1,

    /*! Virtual MAC port 2. */
    ETHREMOTECFG_MAC_PORT_2,

    /*! Virtual MAC port 3. */
    ETHREMOTECFG_MAC_PORT_3,

    /*! Virtual MAC port 4. */
    ETHREMOTECFG_MAC_PORT_4,

    /*! Virtual MAC port 5. */
    ETHREMOTECFG_MAC_PORT_5,

    /*! Virtual MAC port 6. */
    ETHREMOTECFG_MAC_PORT_6,

    /*! Virtual MAC port 7. */
    ETHREMOTECFG_MAC_PORT_7,

    /*! Virtual MAC port 8. */
    ETHREMOTECFG_MAC_PORT_8,

    /*! Last virtual MAC port id. */
    ETHREMOTECFG_MAC_PORT_LAST = ETHREMOTECFG_MAC_PORT_8,
} EthRemoteCfg_VirtPort;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/*!
 * \brief Check whether port is a virtual switch port or not.
 *
 * \param portId [in]   Virtual port id.
 *
 * \return true if virtual switch port, false otherwise.
 */
static bool EthRemoteCfg_isSwitchPort(EthRemoteCfg_VirtPort portId)
{
    return (portId <= ETHREMOTECFG_SWITCH_PORT_LAST);
}

/*!
 * \brief Check whether port is a virtual MAC port or not.
 *
 * \param portId [in]   Virtual port id.
 *
 * \return true if virtual MAC port, false otherwise.
 */
static bool EthRemoteCfg_isMacPort(EthRemoteCfg_VirtPort portId)
{
    return (portId >= ETHREMOTECFG_MAC_PORT_1);
}

/*!
 * \brief Get virtual port number.
 *
 * Gets the port number of a virtual port. Virtual switch ports numbers are
 * 0-relative and virtual MAC ports are 1-relative.
 *
 * \param portId [in]   Virtual port id.
 *
 * \return Port number.
 */
static uint32_t EthRemoteCfg_getPortNum(EthRemoteCfg_VirtPort portId)
{
    uint32_t portNum;

    if (EthRemoteCfg_isSwitchPort(portId))
    {
        portNum = (uint32_t)portId;
    }
    else
    {
        portNum = (uint32_t)(portId - ETHREMOTECFG_MAC_PORT_1) + 1U;
    }

    return portNum;
}

/*!
 * \brief Get Enet MAC port number corresponding to a virtual port id.
 *
 * Gets the Enet MAC port number corresponding to a virtual MAC port.  It will return
 * `ENET_MAC_PORT_INV` for virtual switch ports.
 *
 * The returned value of this function could be used as is to populate the port
 * number used for TX directed packets.
 *
 * \param portId    Virtual port id.
 *
 * \return Enet MAC port number for virtual MAC ports, `ENET_MAC_PORT_INV` for
 *         virtual switch ports.
 */
static Enet_MacPort EthRemoteCfg_getMacPort(EthRemoteCfg_VirtPort portId)
{
    Enet_MacPort macPort = ENET_MAC_PORT_INV;

    if (EthRemoteCfg_isMacPort(portId))
    {
        macPort = ENET_MACPORT_DENORM(portId - ETHREMOTECFG_MAC_PORT_1);
    }

    return macPort;
}

#ifdef __cplusplus
}
#endif

#endif /* ETHREMOTECFG_VIRTPORT_H_ */
