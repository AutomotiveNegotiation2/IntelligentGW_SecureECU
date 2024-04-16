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
 * \file timeSync_tools.h
 *
 * \brief This file contains the interface to helper functions
 *        of timeSync driver
 */

/*!
 * \addtogroup TIMESYNC_HAL_API
 * @{
 */

#ifndef TIMESYNC_TOOLS_H
#define TIMESYNC_TOOLS_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Macro to set bit at given bit position */
#define TIMESYNC_SET_BIT(n)                (1U << (n))

/** Macro to get bit at given bit position */
#define TIMESYNC_GET_BIT(val, n)           ((val & (1U << n)) >> n)

/** Macro to check if bit at given bit position is set */
#define TIMESYNC_IS_BIT_SET(val, n)        (((val) & (1U << (n))) != 0U)

/**Starting offset for an IP header in TCP/IP packet*/
#define TIMESYNC_START_OF_IP_HEADER        (14)

/**Starting offset for checksum in IP header in TCP/IP packet*/
#define TIMESYNC_START_OF_IP_CHECKSUM      (TIMESYNC_START_OF_IP_HEADER + 10U)

/**Starting offset for length field in IP header in TCP/IP packet*/
#define TIMESYNC_START_OF_IP_LENGTH        (TIMESYNC_START_OF_IP_HEADER + 2U)

/**Starting offset for UDP header in TCP/IP packet*/
#define TIMESYNC_START_OF_UDP_HEADER       (34U)

/**Starting offset for checksum field in UDP header in TCP/IP packet*/
#define TIMESYNC_START_OF_UDP_CHECKSUM     (TIMESYNC_START_OF_UDP_HEADER + 6U)

/**Starting offset for length field in UDP header in TCP/IP packet*/
#define TIMESYNC_START_OF_UDP_LENGTH       (TIMESYNC_START_OF_UDP_HEADER + 4U)

/**Starting offset for protocol field in IP header in TCP/IP packet*/
#define TIMESYNC_START_OF_IP_PROTOCOL      (TIMESYNC_START_OF_IP_HEADER + 9U)

/**Starting offset for IP address field in IP header in TCP/IP packet*/
#define TIMESYNC_START_OF_IP_ADDRESS       (TIMESYNC_START_OF_IP_HEADER + 12U)

/**standard size for Ethernet Header (src MAC + dst MAC + EthType) in 802.3 packet*/
#define TIMESYNC_DEFAULT_ETH_HEADER_SIZE   (14U)

/**standard size for IP header in TCP/IP packet*/
#define TIMESYNC_DEFAULT_IP_HEADER_SIZE    (20U)

/**standard size for UDP header in TCP/IP packet*/
#define TIMESYNC_DEFAULT_UDP_HEADER_SIZE   (8U)

/**standard size for UDP + IP header in TCP/IP packet*/
#define TIMESYNC_DEFAULT_HEADER_SIZE       (42U)

/**Starting offset for payload data in UDP header in TCP/IP packet*/
#define TIMESYNC_START_OF_PAYLOAD          (TIMESYNC_START_OF_UDP_HEADER + TIMESYNC_DEFAULT_UDP_HEADER_SIZE)

/** Value of seconds in nanoseconds. Useful for calculations*/
#define TIMESYNC_SEC_TO_NS                 (1000000000U)

/** Length of MAC address in bytes*/
#define TIMESYNC_MAC_ADDR_LEN              (6U)

/** Length of IPv4 address in bytes*/
#define TIMESYNC_IPV4_ADDR_LEN             (4U)

/** Length of IPv4 address in bytes*/
#define TIMESYNC_IPV6_ADDR_LEN             (16U)

/**Compare MAC ID's. Uses memcmp internally */
#define TIMESYNC_COMPARE_MAC(x, y)         (memcmp((x), (y), 6U) == 0)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * @brief Add a word to the packet stream
 * @param src  Pointer to the packet stream
 * @param word Word which is to be added
 * @return None
 */
void TimeSync_addWord(uint8_t *src,
                      uint32_t word);

/**
 * @brief Add a half word to the packet stream
 * @param src      Pointer to the packet stream
 * @param halfWord 16-bit word which is to be added
 * @return None
 */
void TimeSync_addHalfWord(volatile uint8_t *src,
                          uint16_t halfWord);

/**
 * @brief Convert specified number of bytes in source from big endian bytes to little
 * endian and vice versa.
 * Assumption :
 * 1. Source and Destination are different
 * 2. Memory is properly allocated (!Function does not check for memory overrun)
 * 3. Number of bytes is even
 * @param src      Pointer to source byte stream
 * @param dst      Pointer to destination byte stream
 * @param numBytes Number of bytes to convert and copy
 * @return None
 */
void TimeSync_convEndianess(volatile void *src,
                            volatile void *dst,
                            uint8_t numBytes);

/**
 * @brief Compute checksum used in IP/UDP packets for a given stream
 * @param packet Pointer to the packet stream
 * @param len    Length of stream
 * @return Checksum computed
 */
uint32_t TimeSync_calcChecksum(uint8_t *packet,
                               uint16_t len);

/**
 * @brief Compute checksum for IP Header and modify in place
 * @param packet Pointer to the packet stream
 * @return None
 */
void TimeSync_calcIpChecksum(uint8_t *packet);

/**
 * @brief Compute checksum for UDP Header and modify in place
 * @param packet Pointer to the packet stream
 * @return None
 */
void TimeSync_calcUdpChecksum(uint8_t *packet);

/**
 * @brief Get the MAC Id from the network stream, convert it to little endian format and return it
 * assumption : MAC is present in big endian byte format and starts from zero offset
 * @param packet Pointer to byte stream
 * @param macId  Pointer to array of six bytes which contain the MAC Id in little endian format
 * @return None
 */
void TimeSync_getMacId(uint8_t *packet,
                       uint8_t *macId);

/**
 * @brief Copy MAC ID to a stream
 * @param src   Pointer to stream
 * @param macID Pointer to MAC ID
 * @return None
 */
void TimeSync_addMacID(uint8_t *src,
                       uint8_t *macID);

/**
 * @brief Get a word from the network stream, convert it to little endian format and return it
 * assumption word is present in big endian byte format and starts from zero offset
 * @param byte Pointer to byte stream
 * @return word in little endian format
 */
uint32_t TimeSync_convBigEndianToLittleEndianWord(uint8_t *byte);

/**
 * @brief get a halfword from the network stream, convert it to little endian format and return it
 * assumption halfword is present in big endian byte format and starts from zero offset
 * @param byte Pointer to byte stream
 * @return halfword halfword in little endian format
 */
uint16_t TimeSync_convBigEndianToLittleEndianHalfWord(uint8_t *byte);

/**
 * @brief Takes in a 6 byte reverse byte endian source and puts it in an 64 bit double word with
 * correct endianness. This function is specific to PTP
 * Assumption :
 * 1. Source and Destination are different
 * 2. Memory is properly allocated (!Function does not check for memory overrun)
 * @param src Pointer to source byte stream
 * @param dst Pointer to destination byte stream
 * @return None
 */
void TimeSync_convEnd6to8(volatile void *src,
                          void *dst);

#endif /* TIMESYNC_TOOLS_H */

/* @} */

