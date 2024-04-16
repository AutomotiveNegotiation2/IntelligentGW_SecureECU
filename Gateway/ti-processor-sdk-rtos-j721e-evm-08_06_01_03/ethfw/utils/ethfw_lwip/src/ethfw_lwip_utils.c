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
 *  \file ethfw_lwip_utils.c
 *
 *  \brief lwIP utils functions for Ethernet Firmware.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ti/osal/MutexP.h>
#include <utils/ethfw_lwip/include/ethfw_lwip_utils.h>
#include <utils/console_io/include/app_log.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Number of entries in the address table */
#define ETHFW_ARP_UTILS_TABLE_SIZE                 (8U)

/* Macro to get the size of an array */
#define ARRAY_SIZE(x)                              (sizeof((x)) / sizeof(x[0U]))

/*! Macro to set bit at given bit position */
#define BIT(n)                                     (1U << (n))

/* Macro to check if bit at given bit position is set */
#define IS_BIT_SET(val, n)                         (((val) & BIT(n)) != 0U)

/*!
 * \brief Table entry with IP address and MAC address for remote cores.
 */
typedef struct EthFwArpUtils_AddrEntry_s
{
    /*! Remote core's IP address */
    ip4_addr_t ipAddr;

    /*! Remote core's MAC address */
    struct eth_addr hwAddr;

    /*! Whether this entry is free or not */
    bool isFree;
} EthFwArpUtils_AddrEntry;

/*!
 * \brief lwIP ARP Utils object.
 */
typedef struct EthFwArpUtils_Obj_s
{
    /*! ARP table */
    EthFwArpUtils_AddrEntry remoteCoreArpTable[ETHFW_ARP_UTILS_TABLE_SIZE];

    /*! Mutex object. Used to protect ARP table from concurrent accesses */
    MutexP_Object mutexObj;

    /*! Handle to ARP table mutex */
    MutexP_Handle hMutex;
} EthFwArpUtils_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Extern variables                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static EthFwArpUtils_Obj gEthFwArpObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t EthFwArpUtils_init(void)
{
    int32_t status = ETHFW_LWIP_UTILS_SOK;
    uint32_t i;

    /* Create mutex to protect ARP table */
    gEthFwArpObj.hMutex = MutexP_create(&gEthFwArpObj.mutexObj);
    if (gEthFwArpObj.hMutex == NULL)
    {
        appLogPrintf("EthFwArpUtils_init() failed to create mutex\n");
        status = ETHFW_LWIP_UTILS_EFAIL;
    }

    /* Mark all entries in table as free */
    if (status == ETHFW_LWIP_UTILS_SOK)
    {
        for (i = 0U; i < ETHFW_ARP_UTILS_TABLE_SIZE; i++)
        {
            gEthFwArpObj.remoteCoreArpTable[i].isFree = true;
        }
    }

    return status;
}

void EthFwArpUtils_deinit(void)
{
    if (gEthFwArpObj.hMutex != NULL)
    {
        MutexP_delete(gEthFwArpObj.hMutex);
    }
}

int32_t EthFwArpUtils_getHwAddr(const ip4_addr_t *ipAddr,
                                struct eth_addr *hwAddr)
{
    EthFwArpUtils_AddrEntry *entry;
    int32_t status = ETHFW_LWIP_UTILS_EFAIL;
    uint32_t i;

    MutexP_lock(gEthFwArpObj.hMutex, MutexP_WAIT_FOREVER);

    for (i = 0U; i < ETHFW_ARP_UTILS_TABLE_SIZE; i++)
    {
        entry = &gEthFwArpObj.remoteCoreArpTable[i];

        /* Check if there is an entry matching given IP address */
        if (!entry->isFree &&
            ip4_addr_cmp(&entry->ipAddr, ipAddr))
        {
            SMEMCPY(hwAddr, &entry->hwAddr, ETH_HWADDR_LEN);
            status = ETHFW_LWIP_UTILS_SOK;
            break;
        }
    }

    MutexP_unlock(gEthFwArpObj.hMutex);

    return status;
}

int32_t EthFwArpUtils_addAddr(const ip4_addr_t *ipAddr,
                              const struct eth_addr *hwAddr)
{
    EthFwArpUtils_AddrEntry *entry;
    int32_t status = ETHFW_LWIP_UTILS_SOK;
    uint32_t i;
    bool done = false;

    if (IS_BIT_SET(hwAddr->addr[0], 0))
    {
        appLogPrintf("EthFwArpUtils_addAddr() mcast MAC address cannot be added\n");
        status = ETHFW_LWIP_UTILS_EINVALIDPARAMS;
    }
    else if (ip4_addr_ismulticast(ipAddr))
    {
        appLogPrintf("EthFwArpUtils_addAddr() mcast IP address cannot be added\n");
        status = ETHFW_LWIP_UTILS_EINVALIDPARAMS;
    }
    else
    {
        MutexP_lock(gEthFwArpObj.hMutex, MutexP_WAIT_FOREVER);

        /* Check if an entry already in table needs to be updated */
        for (i = 0U; i < ETHFW_ARP_UTILS_TABLE_SIZE; i++)
        {
            entry = &gEthFwArpObj.remoteCoreArpTable[i];

            if (!entry->isFree)
            {
                /* Check if an entry for the IP address is already in table,
                 * if so, update MAC address */
                if (ip4_addr_cmp(ipAddr, &entry->ipAddr))
                {
                    SMEMCPY(&entry->hwAddr, hwAddr, ETH_HWADDR_LEN);
                    done = true;
                    break;
                }

                /* Check if an entry for the MAC address is already in table,
                 * if so, update IP address */
                if (memcmp(&entry->hwAddr, hwAddr, ETH_HWADDR_LEN) == 0)
                {
                    ip4_addr_copy(entry->ipAddr, *ipAddr);
                    done = true;
                    break;
                }
            }
        }

        /* Look for new entry in table */
        if (!done)
        {
            for (i = 0U; i < ETHFW_ARP_UTILS_TABLE_SIZE; i++)
            {
                entry = &gEthFwArpObj.remoteCoreArpTable[i];

                /* Take free entry and populate IP address / MAC address pair */
                if (entry->isFree)
                {
                    ip4_addr_copy(entry->ipAddr, *ipAddr);
                    SMEMCPY(&entry->hwAddr, hwAddr, ETH_HWADDR_LEN);
                    entry->isFree = false;
                    done = true;
                    break;
                }
            }
        }

        MutexP_unlock(gEthFwArpObj.hMutex);

        status = done ? ETHFW_LWIP_UTILS_SOK : ETHFW_LWIP_UTILS_EALLOC;
    }

    return status;
}

int32_t EthFwArpUtils_delAddr(const ip4_addr_t *ipAddr)
{
    EthFwArpUtils_AddrEntry *entry;
    int32_t status = ETHFW_LWIP_UTILS_SOK;
    uint32_t i;

    MutexP_lock(gEthFwArpObj.hMutex, MutexP_WAIT_FOREVER);

    for (i = 0U; i < ETHFW_ARP_UTILS_TABLE_SIZE; i++)
    {
        entry = &gEthFwArpObj.remoteCoreArpTable[i];

        /* Clear entry if matching IP address is found */
        if (!entry->isFree &&
            ip4_addr_cmp(&entry->ipAddr, ipAddr))
        {
            ip4_addr_set_zero(&entry->ipAddr);
            memset(&entry->hwAddr, 0, sizeof(struct eth_addr));
            entry->isFree = true;
            break;
        }
    }

    MutexP_unlock(gEthFwArpObj.hMutex);

    if (i == ETHFW_ARP_UTILS_TABLE_SIZE)
    {
        status = ETHFW_LWIP_UTILS_EALLOC;
    }
    else
    {
        status = ETHFW_LWIP_UTILS_SOK;
    }

    return status;
}

void EthFwArpUtils_printTable(void)
{
    EthFwArpUtils_AddrEntry *entry;
    const uint8_t *hwAddr;
    uint32_t used = 0U;
    uint32_t i;

    appLogPrintf("\n SNo.      IP Address          MAC Address   \n");
    appLogPrintf("------    -------------     -----------------\n");

    for (i = 0U; i < ETHFW_ARP_UTILS_TABLE_SIZE; i++)
    {
        entry = &gEthFwArpObj.remoteCoreArpTable[i];

        if (!entry->isFree)
        {
            hwAddr = &entry->hwAddr.addr[0U];

            appLogPrintf("  %d       %s     %02x:%02x:%02x:%02x:%02x:%02x\n",
                         ++used,
                         ip4addr_ntoa(&entry->ipAddr),
                         hwAddr[0] & 0xFF, hwAddr[1] & 0xFF, hwAddr[2] & 0xFF,
                         hwAddr[3] & 0xFF, hwAddr[4] & 0xFF, hwAddr[5] & 0xFF);
        }
    }
}

void EthFwArpUtils_sendRaw(struct netif *netif,
                           const struct eth_addr *ethSrcAddr,
                           const struct eth_addr *ethDstAddr,
                           const struct eth_addr *hwSrcAddr,
                           const ip4_addr_t *ipSrcAddr,
                           const struct eth_addr *hwDstAddr,
                           const ip4_addr_t *ipDstAddr,
                           const u16_t opcode)
{
    struct pbuf *pbuf;
    struct etharp_hdr *hdr;

    /* allocate a pbuf for the outgoing ARP request packet */
    pbuf = pbuf_alloc(PBUF_LINK, SIZEOF_ETHARP_HDR, PBUF_RAM);
    /* could allocate a pbuf for an ARP request? */
    if (pbuf == NULL)
    {
        appLogPrintf("Could not allocate pbuf for ARP request\n");
    }
    else
    {
        hdr = (struct etharp_hdr *)pbuf->payload;
        hdr->opcode = lwip_htons(opcode);

        /* Write the ARP MAC-Addresses */
        SMEMCPY(&hdr->shwaddr, hwSrcAddr, ETH_HWADDR_LEN);
        SMEMCPY(&hdr->dhwaddr, hwDstAddr, ETH_HWADDR_LEN);

        /* Copy struct ip4_addr_wordaligned to aligned ip4_addr, to support compilers without
         * structure packing. */
        IPADDR_WORDALIGNED_COPY_FROM_IP4_ADDR_T(&hdr->sipaddr, ipSrcAddr);
        IPADDR_WORDALIGNED_COPY_FROM_IP4_ADDR_T(&hdr->dipaddr, ipDstAddr);

        hdr->hwtype = PP_HTONS(1);
        hdr->proto = PP_HTONS(ETHTYPE_IP);
        /* set hwlen and protolen */
        hdr->hwlen = ETH_HWADDR_LEN;
        hdr->protolen = sizeof(ip4_addr_t);

        LOCK_TCPIP_CORE();
        ethernet_output(netif, pbuf, ethSrcAddr, ethDstAddr, ETHTYPE_ARP);
        UNLOCK_TCPIP_CORE();

        pbuf_free(pbuf);
    }
}
