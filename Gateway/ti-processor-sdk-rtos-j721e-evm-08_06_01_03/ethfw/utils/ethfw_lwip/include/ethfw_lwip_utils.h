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
 *  \file ethfw_lwip_utils.h
 *
 *  \brief Header file for Ethernet Firmware LwIP utils.
 */

#ifndef ETHFW_LWIP_UTILS_H_
#define ETHFW_LWIP_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "lwip/ip4_addr.h"
#include "lwip/prot/etharp.h"
#include "lwip/prot/ethernet.h"
#include "netif/ethernet.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/*! \brief Success. */
#define ETHFW_LWIP_UTILS_SOK                    (0)

/*! \brief Generic failure error condition. */
#define ETHFW_LWIP_UTILS_EFAIL                  (-1)

/*! \brief Invalid parameters (i.e. value out-of-range). */
#define ETHFW_LWIP_UTILS_EINVALIDPARAMS         (-3)

/*! \brief Allocation failure. */
#define ETHFW_LWIP_UTILS_EALLOC                 (-5)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t EthFwArpUtils_init(void);

void EthFwArpUtils_deinit(void);

int32_t EthFwArpUtils_getHwAddr(const ip4_addr_t *ipAddr,
                                struct eth_addr *hwAddr);

int32_t EthFwArpUtils_addAddr(const ip4_addr_t *ipAddr,
                              const struct eth_addr *hwAddr);

int32_t EthFwArpUtils_delAddr(const ip4_addr_t *ipAddr);

void EthFwArpUtils_printTable(void);

void EthFwArpUtils_sendRaw(struct netif *netif,
                           const struct eth_addr *ethSrcAddr,
                           const struct eth_addr *ethDstAddr,
                           const struct eth_addr *hwSrcAddr,
                           const ip4_addr_t *ipSrcAddr,
                           const struct eth_addr *hwDstAddr,
                           const ip4_addr_t *ipDstAddr,
                           const u16_t opcode);

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* ETHFW_LWIP_UTILS_H_ */
