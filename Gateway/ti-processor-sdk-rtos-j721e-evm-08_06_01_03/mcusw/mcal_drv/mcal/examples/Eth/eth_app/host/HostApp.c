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
 *  \file     HostApp.c
 *
 *  \brief    This file contains the host-side Eth test application code.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>

#include <EthUtils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define OCTETS_PER_ROW                  8

#define HOST_APP_VERBOSE_OCTETS         16

#define HOST_APP_SOCKET_BUFSIZE         (512 * 1024)

typedef bool (*TestFunc)(void);

#define MAX_RX_PKT 0xFFFFFFFFU
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct {
    int32_t sock;
    char *ifName;
    uint8_t hwAddr[ETH_HW_ADDR_LEN];
    uint8_t dutAddr[ETH_HW_ADDR_LEN];
    uint32_t timeout;
    struct ifreq ifIdx;
    struct ifreq ifMac;
    struct sockaddr_ll sockAddr;
    bool verbose;
    bool veryVerbose;
} HostApp;

typedef struct {
    uint32_t len;
    EthFrame frame;
} TestFrame;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void help(const char *me);

int32_t HostApp_open(const char *ifName);

void HostApp_close(void);

void HostApp_send(EthFrame *frame,
                  uint32_t len);

void HostApp_transmit(TestFrame *frames,
                      uint32_t testFramesNum,
                      uint32_t num);

bool HostApp_recv(EthFrame *frame,
                  uint32_t *len);

bool HostApp_receive(uint32_t *frames);

bool HostApp_receiveTput(uint32_t total_frame, uint32_t size);

void HostApp_waitForCmd(uint8_t cmd);

void HostApp_sendCmd(uint8_t cmd);

float HostApp_timeDiff(struct timeval t1,
                       struct timeval t0);

/**
 * \brief Test basic frame reception
 *
 * Basic DUT frame reception test.  The host side performs these operations:
 * - Wait for START command from DUT
 * - Transmit ETH_TEST_ITER_M_COUNT frames
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0001(void);

/**
 * \brief Test basic frame transmission
 *
 * Basic DUT frame transmission test.  The host side performs these operations:
 * - Wait for START command from DUT
 * - Receive frames until STOP command is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0002(void);

/**
 * \brief Test external loopback
 *
 * External loopback test.  The host side receives frames from the DUT and
 * sends them back.  The following operations are performed:
 * - Wait for START command from DUT
 * - Loop back all frames received until a STOP command is detected
 *   o One frame is received
 *   o Source and destination MAC addresses are swapped
 *   o The frame is sent back
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0003(void);

/**
 * \brief Test default filter operation
 *
 * Test the operation of the default DUT's filter configuration (only frames with
 * DUT's MAC address are accepted, all others are rejected).  The host side performs
 * these operations:
 * - Wait for START command from DUT
 * - Transmit ETH_TEST_ITER_M_COUNT frames:
 *   o Frame 1: Source MAC address is DUT's
 *   o Frame 2: Source MAC address is not DUT's
 *
 * Frame 1 is expected to be accepted, frame 2 to be rejected.  The total number of
 * frames received on the DUT's driver is ETH_TEST_ITER_M_COUNT / 2.
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0004(void);

/**
 * \brief Test different filter configurations
 *
 * Test the different modes of the DUT's filter configuration.  The host side performs
 * these operations:
 * - Wait for START command from DUT
 * - Part 1
 *    o <DUT resets filter>
 *    o Transmit ETH_TEST_ITER_M_COUNT frames:
 *      - Frame 1: Source MAC address is DUT's. It should be accepted
 *      - Frame 2: Source MAC address is not DUT's. It should be rejected
 * - Part 2
 *   o <DUT adds a second valid MAC address>
 *   o Transmit ETH_TEST_ITER_M_COUNT frames:
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is second valid MAC address. It should be accepted
 * - Part 3
 *   o <DUT adds a multicast MAC address>
 *   o Transmit ETH_TEST_ITER_M_COUNT frames:
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is multicast address. It should be accepted
 * - Part 4
 *   o <DUT removes the multicast MAC address>
 *   o Transmit ETH_TEST_ITER_M_COUNT frames:
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is multicast address. It should be rejected
 * - Part 5
 *   o <DUT opens up the filter (promiscuous mode)>
 *   o Transmit ETH_TEST_ITER_M_COUNT frames:
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be accepted
 * - Part 6
 *   o <DUT resets filter>
 *   o Transmit ETH_TEST_ITER_M_COUNT frames:
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be rejected
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0005(void);

/**
 * \brief Test frame transmission with confirmation
 *
 * DUT frame transmission test with TX confirmation.  The host side performs
 * these operations:
 * - Wait for START command from DUT
 * - Receive frames until STOP command is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 * This test is exactly the same as test_0002 on the host side.
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0006(void);

/**
 * \brief Test frame transmission of VLAN tagged frames
 *
 * DUT frame transmission test of VLAN tagged packets.  The host side performs
 * these operations:
 * - Wait for START command from DUT
 * - Receive frames until STOP command is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 * This test is exactly the same as test_0002 on the host side.
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0007(void);

/**
 * \brief Test frame transmission of different lengths
 *
 * DUT frame transmission test of different frame lengths, including short frames
 * (less than 64 octets).  The host side performs these operations:
 * - Wait for START command from DUT
 * - Receive frames until STOP command is detected. It's expected to receive
 *   ETH_TEST_ITER_S_COUNT packets of different lengths, starting at 10 octets
 *   in increments of 10 octets until 1500 octets.
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0008(void);

/**
 * \brief Test VLAN tagged frame reception
 *
 * DUT VLAN tagged frame reception test.  The host side performs these operations:
 * - Wait for START command from DUT
 * - Transmit ETH_TEST_ITER_M_COUNT frames with VLAN tag
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0009(void);

/**
 * \brief Test controller mode change
 *
 * Controller mode change test.  The host performs the following operations:
 * - Wait for START command from DUT
 * - Run ETH_TEST_ITER_S_COUNT iterations of:
 *   o <DUT sets controller mode to DOWN>
 *   o <DUT sets controller mode to ACTIVE>
 *   o Receive frames (run test 0002)
 *   o Transmit frames (run test 0001)
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0010(void);

/**
 * \brief Test multicast frame transmission
 *
 * Multicast frame transmission test.  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged multicast frames without
 *   confirmation
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0011(void);

/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput over frames number and packet lenght is size.
 * The host performs the following operations:
 * - Wait for START command from DUT
 * - Receive frames or until the STOP cmd is detected
 * - Compute the elapsed time, packets per second and Mbps
 *
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0100(uint32_t frames, uint32_t size);

/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput over ETH_TEST_ITER_L_COUNT with size are: 1024,521,128,64 frames.
 * The host performs the following operations:
 * - call HostApp_test_0100 for each frame size
 * 
 * \return PASS or FAIL  Test result
 */
bool HostApp_test_0110(void);

/* Measure Rx through*/
bool HostApp_test_0101(void);

/* Egress timestamp test */
bool HostApp_test_0300(void);

/* Ingress timestamp test */
bool HostApp_test_0301(void);

/* Get current time test */
bool HostApp_test_0302(void);

/* Traffic shaping test */
bool HostApp_test_0400(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

TestFunc testFuncs[] = {
    &HostApp_test_0001,
    &HostApp_test_0002,
    &HostApp_test_0003,
    &HostApp_test_0004,
    /* Depends on ETH_UPDATE_PHYS_ADDR_FILTER_API = STD_ON */
    &HostApp_test_0005,
    &HostApp_test_0006,
    &HostApp_test_0007,
    &HostApp_test_0008,
    &HostApp_test_0009,
    &HostApp_test_0010,
    &HostApp_test_0011,
    &HostApp_test_0300,
    &HostApp_test_0301,
    &HostApp_test_0302,
    &HostApp_test_0110,
    &HostApp_test_0101,
#ifdef ETH_WRAPPER_ENABLED
    &HostApp_test_0400,
#endif
};

HostApp gHostApp = {
    .dutAddr = { 0xf4, 0x84, 0x4c, 0xeb, 0x95, 0x09 },
};

EthFrame rxFrame;

CtrlFrame ctrlFrame;

/* Unicast header with dst address of DUT's */
EthFrameHeader hdrUcastCtrl = {
    .dstMac    = { 0xf4, 0x84, 0x4c, 0xeb, 0x95, 0x09 },
    .srcMac    = { 0x00 }, /* to be populated later */
    .etherType = htons(ETHERTYPE_EXPERIMENTAL1),
};

/* Unicast header with dst address to be allowed by DUT's filter */
EthFrameHeader hdrUcastVal = {
    .dstMac   = { 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
    .srcMac   = { 0x00 }, /* to be populated later */
    .etherType = htons(ETHERTYPE_EXPERIMENTAL2),
};

/* Unicast header with dst address to be rejected by DUT's filter */
EthFrameHeader hdrUcastInv = {
    .dstMac   = { 0x08, 0x00, 0x28, 0x01, 0xf6, 0x7c },
    .srcMac   = { 0x00 }, /* to be populated later */
    .etherType = htons(ETHERTYPE_EXPERIMENTAL2),
};

/* Broadcast header */
EthFrameHeader hdrBcast = {
    .dstMac   = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
    .srcMac   = { 0x00 }, /* to be populated later */
    .etherType = htons(ETHERTYPE_EXPERIMENTAL1),
};

/* Multicast header */
EthFrameHeader hdrMcast = {
    .dstMac   = { 0x01, 0x00, 0x5e, 0x0d, 0x0e, 0x0f },
    .srcMac   = { 0x00 }, /* to be populated later */
    .etherType = htons(ETHERTYPE_EXPERIMENTAL2),
};

/* Test control (broadcast) header */
EthFrameHeader hdrCtrl = {
    .dstMac   = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
    .srcMac   = { 0x00 }, /* to be populated later */
    .etherType = htons(ETHERTYPE_EXP_CONTROL),
};

static const struct option long_options[] = {
    {"timeout",      1, 0, 't'},      /* time-out */
    {"iface",        1, 0, 'i'},      /* interface number */
    {"verbose",      0, 0, 'v'},      /* verbose output */
    {"very-verbose", 0, 0, 'V'},      /* very verbose output */
    {"help",         0, 0, 'h'},      /* show help */
};

static const char short_options[] = "t:p:i:vh";

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(int argc, char *argv[])
{
    struct timeval timeout;
    const char *action;
    const char *me = argv[0];
    char *ifName = "eth0";
    bool status;
    bool globalStatus = true;
    long int val;
    int32_t option;
    int32_t c;
    int32_t i;
    int32_t ret;
    int32_t ti;

    gHostApp.verbose = false;
    gHostApp.veryVerbose = false;
    gHostApp.timeout = 10;

    while (1) {
        c = getopt_long(argc, argv, short_options, long_options, &option);
        if (c == -1)
            break;

        switch (c) {
        case 't':
            gHostApp.timeout = strtol(optarg, NULL, 0);
            break;
        case 'i':
            ifName = optarg;
            break;
        case 'v':
            gHostApp.verbose = true;
            break;
        case 'V':
            gHostApp.verbose = true;
            gHostApp.veryVerbose = true;
            break;
        case 'h':
            help(me);
            return 0;
        default:
            printf("Invalid option %d\n", option);
            return -EINVAL;
        }
    }

    ret = HostApp_open(ifName);
    if (ret) {
        printf("Failed to open and init raw socket: %d\n", ret);
        return ret;
    }

    for(ti = 0u; ti < ETH_APP_TEST_ROUND; ti++)
    {
        /* Wait for DUT */
        printf("Waiting for DUT.. %d\n", ti);
        HostApp_waitForCmd(CTRL_FRAME_CMD_READY);

        for (i = 0; i < ARRAY_SIZE(testFuncs); i++) {
            printf("\n\n-----------------------------------------------------------\n");
            status = testFuncs[i]();
            globalStatus &= status;
            printf("Test Result: %s\n", status?"Pass":"Fail");
            printf("-----------------------------------------------------------\n");
        }
    }
    HostApp_close();

    printf("\nTest Result: %s\n\n", globalStatus?"Pass":"Fail");

    return 0;
}

void help(const char *me)
{
    printf("Usage: %s [OPTION]...\n"
           "-h, --help              help\n"
           "-i, --iface=<NAME>      interface name (i.e. eth0)\n"
           "-t, --timeout=#         socket time-out (in secs)\n"
           "-v, --verbose           verbose output\n\n",
           me);
}

int32_t HostApp_open(const char *ifName)
{
    struct timeval timeout;
    uint32_t tout = 10;
    uint32_t size;
    uint32_t i;
    int32_t ret;

    /* Open a raw socket */
    ret = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (ret > 0) {
        gHostApp.sock = ret;
    } else {
        printf("open: failed to open raw socket: %s\n", strerror(errno));
        ret = -errno;
        return ret;
    }

    /* Set a timeout */
    timeout.tv_sec = tout;
    timeout.tv_usec = 0;
    ret = setsockopt(gHostApp.sock, SOL_SOCKET, SO_RCVTIMEO,
                     (const char *)&timeout, sizeof(timeout));
    if (ret) {
        printf("open: failed to set timeout: %s\n", strerror(errno));
        goto open_err;
    }

    /* Increase the socket buffer size */
    size = HOST_APP_SOCKET_BUFSIZE;
    ret  = setsockopt(gHostApp.sock, SOL_SOCKET, SO_RCVBUF,
                      &size, sizeof(size));
    if (ret) {
        printf("open: failed to socket buffer size: %s\n", strerror(errno));
        goto open_err;
    }

    /* Get interface index */
    memset(&gHostApp.ifIdx, 0, sizeof(struct ifreq));
    strncpy(gHostApp.ifIdx.ifr_name, ifName, IFNAMSIZ - 1);
    ret = ioctl(gHostApp.sock, SIOCGIFINDEX, &gHostApp.ifIdx);
    if (ret) {
        printf("open: failed to get interface index: %s\n", strerror(errno));
        goto open_err;
    }

    /* Get interface MAC address */
    memset(&gHostApp.ifMac, 0, sizeof(struct ifreq));
    strncpy(gHostApp.ifMac.ifr_name, ifName, IFNAMSIZ - 1);
    ret = ioctl(gHostApp.sock, SIOCGIFHWADDR, &gHostApp.ifMac);
    if (ret) {
        printf("open: failed to get interface MAC address: %s\n", strerror(errno));
        goto open_err;
    }

    /* Save host's MAC address */
    for (i = 0; i < ETH_HW_ADDR_LEN; i++)
        gHostApp.hwAddr[i] = gHostApp.ifMac.ifr_hwaddr.sa_data[i];

    gHostApp.sockAddr.sll_family  = PF_PACKET;
    gHostApp.sockAddr.sll_ifindex = gHostApp.ifIdx.ifr_ifindex;
    gHostApp.sockAddr.sll_halen = ETH_ALEN;
    memset(gHostApp.sockAddr.sll_addr, 0, ETH_HW_ADDR_LEN);

    /* Bind only to requested interface */
    ret = bind(gHostApp.sock,
               (struct sockaddr *)&gHostApp.sockAddr,
               sizeof(gHostApp.sockAddr));
    if (ret)
    {
        printf("open: failed to bind to '%s': %s\n", ifName, strerror(errno));
        goto open_err;
    }

    printf("Interface    : %s\n", ifName);
    printf("MAC address  : %02x:%02x:%02x:%02x:%02x:%02x\n",
           gHostApp.hwAddr[0] & 0xFF, gHostApp.hwAddr[1] & 0xFF,
           gHostApp.hwAddr[2] & 0xFF, gHostApp.hwAddr[3] & 0xFF,
           gHostApp.hwAddr[4] & 0xFF, gHostApp.hwAddr[5] & 0xFF);
    printf("\n\n");

    /* Update test packet headers with host's MAC address */
    memcpy(hdrUcastCtrl.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);
    memcpy(hdrUcastVal.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);
    memcpy(hdrUcastInv.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);
    memcpy(hdrBcast.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);
    memcpy(hdrMcast.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);
    memcpy(hdrCtrl.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);
    memcpy(&ctrlFrame.hdr, &hdrCtrl, ETH_HDR_LEN);

    return 0;

open_err:
    close(gHostApp.sock);
    gHostApp.sock = -1;
    ret = -errno;
    return ret;
}

void HostApp_close(void)
{
    close(gHostApp.sock);
    gHostApp.sock = -1;
}

void HostApp_send(EthFrame *frame,
                  uint32_t len)
{
    ssize_t sent;

    sent = sendto(gHostApp.sock,
                  frame, len, 0,
                  (struct sockaddr*)&gHostApp.sockAddr,
                  sizeof(struct sockaddr_ll));

    if (sent < 0)
        printf("send: failed to transmit packet: %s\n", strerror(errno));
    else if (sent != len)
        printf("sned: short transmission (req %d, got %d)\n", len, (int)sent);
}

void HostApp_transmit(TestFrame *frames,
                      uint32_t testFramesNum,
                      uint32_t num)
{
    TestFrame *frame;
    uint32_t sent = 0;

    while (true) {
        frame = &frames[sent % testFramesNum];

        HostApp_send(&frame->frame, frame->len);

        if (gHostApp.veryVerbose)
            EthUtils_printFrame(&frame->frame, HOST_APP_VERBOSE_OCTETS);

        usleep(1000);

        if (++sent >= num)
            break;
    }
}

bool HostApp_recv(EthFrame *frame,
                  uint32_t *len)
{
    ssize_t bytes;
    bool status = PASS;

    memset(frame, 0, sizeof(EthFrame));

    bytes = recv(gHostApp.sock, frame, sizeof(EthFrame), 0);
    if (bytes < 0) {
        printf("recv: failed to receive data over raw socket: %s\n", strerror(errno));
        *len = 0;
        status = FAIL;
    } else {
        *len = bytes;
    }

    return status;
}

bool HostApp_receive(uint32_t *frames)
{
    long long total = 0;
    uint32_t len;
    uint32_t i = 0;
    int32_t ret;
    bool forever = false;
    bool status = PASS;

    /* Receive packets indefinitely if requested frame count is 0 */
    if (*frames == 0)
        forever = true;

    /* Receive frames */
    while (true) {
        /* Receive one frame */
        status = HostApp_recv(&rxFrame, &len);
        if (status == FAIL) {
            printf("receive: failed to receive packet: %d\n", ret);
            break;
        }

        if (gHostApp.veryVerbose)
            EthUtils_printFrame(&rxFrame, HOST_APP_VERBOSE_OCTETS);

        /* Ignore frames with other EtherTypes */
        if ((rxFrame.hdr.etherType != htons(ETHERTYPE_EXPERIMENTAL1)) &&
            (rxFrame.hdr.etherType != htons(ETHERTYPE_EXPERIMENTAL2)) &&
            (rxFrame.hdr.etherType != htons(ETHERTYPE_EXP_CONTROL)) &&
            (rxFrame.hdr.etherType != htons(ETHERTYPE_VLAN_TAG)))
            continue;

        /* Check if it's a STOP cmd */
        if (EthFrame_isStopCmd(&rxFrame)) {
            if (gHostApp.verbose)
                printf("receive: STOP command received\n");
            break;
        }

        /* Verify frame content */
        if (EthFrame_isVlanTagged(&rxFrame))
            ret = EthUtils_checkVlanPayload((VlanDataFramePayload *)rxFrame.payload);
        else
            ret = EthUtils_checkPayload((DataFramePayload *)rxFrame.payload);

        if (ret != ETH_TEST_PKT_SOK) {
            printf("receive: frame %d is not valid: %d\n", i+1, ret);
            if (gHostApp.veryVerbose)
                EthUtils_printFrame(&rxFrame, len);
            status = FAIL;
        }

        total += len;
        i++;

        if ((!forever) && (i == *frames))
            break;
    }

    /* Update with the number of frames received */
    *frames = i;

    if (gHostApp.verbose)
        printf("receive: received %d frames, %lld bytes\n", i, total);

    return status;
}

bool HostApp_receiveTput(uint32_t total_frame, uint32_t size)
{
    struct timeval t0, t1;
    float elapsed;
    float pps;
    float mbps;
    long long total = 0;
    ssize_t bytes;
    uint32_t i;
    uint32_t frames = total_frame;

    /* Receive frames until STOP cmd is detected */
    for (i = 0; i < frames; i++) {
        bytes = recv(gHostApp.sock, &rxFrame, sizeof(EthFrame), 0);
        if (bytes < 0) {
            printf("receiveTput: failed to received data: %s\n", strerror(errno));
            return FAIL;
        }

        /* Get the "start" timestamp only after the first frame has been received */
        if (i == 0)
            gettimeofday(&t0, NULL);

        /* Check if it's a STOP cmd */
        if (EthFrame_isStopCmd(&rxFrame)) {
            frames = i;
            break;
        }

        total += bytes;
    }

    /* Get the "end" timestamp after DUT is done sending frames */
    gettimeofday(&t1, NULL);

    /* Compute elapsed time, packets per second and Mbps */
    elapsed = HostApp_timeDiff(t1, t0);
    pps = (float)frames / elapsed;
    mbps = (float)total * 8 / elapsed / 1000000;

    /* incase rate limit test, no need to show lost frame*/
    if(total_frame == MAX_RX_PKT) {
    printf("receiveTput-%d: received %d frames in %.2f secs (%.2f frames/s, %.2f Mbps)\n", size,
           frames, elapsed, pps, mbps);
    } 
    else {
    printf("receiveTput-%d: received %d frames in %.2f secs (%.2f frames/s, %.2f Mbps) Lost %d\n", size,
           frames, elapsed, pps, mbps, (total_frame-frames));
    }

    return PASS;
}

void HostApp_sendCmd(uint8_t cmd)
{
    EthFrame *frame = (EthFrame *)&ctrlFrame;

    ctrlFrame.payload.cmd = cmd;
    memset(ctrlFrame.payload.data.payload, 0, sizeof(ctrlFrame.payload.data));

    if (gHostApp.verbose) {
        switch (cmd) {
        case CTRL_FRAME_CMD_READY:
            printf("sendCmd: READY cmd\n");
            break;
        case CTRL_FRAME_CMD_START:
            printf("sendCmd: START cmd\n");
            break;
        case CTRL_FRAME_CMD_STOP:
            printf("sendCmd: STOP cmd\n");
            break;
        default:
            printf("sendCmd: invalid cmd\n");
            break;
        }
    }

    HostApp_send(frame, sizeof(CtrlFrame));
}

void HostApp_waitForCmd(uint8_t cmd)
{
    CtrlFrame *frame = (CtrlFrame *)&rxFrame;
    ssize_t bytes;

    /* Receive frames until a command frame is detected */
    while (true) {
        /* Receive one frame */
        memset(frame, 0, sizeof(EthFrame));
        bytes = recv(gHostApp.sock, frame, sizeof(EthFrame), 0);
        if (bytes < 0) {
            if (errno == EAGAIN) {
                continue;
            } else {
                /* Exit the application since host and DUT are no longer in sync */
                printf("waitForCmd: errno %d: %s\n", errno, strerror(errno));
                exit(1);
            }
        }

        /* Check if it's a control frame and take action depending on the type */
        if ((frame->hdr.etherType == ntohs(ETHERTYPE_EXP_CONTROL)) &&
            (frame->payload.cmd == cmd)) {
            switch (cmd) {
            case CTRL_FRAME_CMD_START:
                if (gHostApp.verbose)
                    printf("waitForCmd: START cmd received\n");
                break;
            case CTRL_FRAME_CMD_READY:
            default:
                memcpy(gHostApp.dutAddr, frame->hdr.srcMac, ETH_HW_ADDR_LEN);
                memcpy(hdrUcastCtrl.dstMac, gHostApp.dutAddr, ETH_HW_ADDR_LEN);
                printf("DUT detected: %02x:%02x:%02x:%02x:%02x:%02x\n",
                       gHostApp.dutAddr[0] & 0xFF, gHostApp.dutAddr[1] & 0xFF,
                       gHostApp.dutAddr[2] & 0xFF, gHostApp.dutAddr[3] & 0xFF,
                       gHostApp.dutAddr[4] & 0xFF, gHostApp.dutAddr[5] & 0xFF);
                break;
            }

            break;
        }
    }
}

float HostApp_timeDiff(struct timeval t1,
                       struct timeval t0)
{
    struct timeval temp;
    float elapsed;

    if ((t1.tv_usec - t0.tv_usec) < 0) {
        temp.tv_sec = t1.tv_sec - t0.tv_sec-1;
        temp.tv_usec = 1000000UL + t1.tv_usec - t0.tv_usec;
    } else {
        temp.tv_sec = t1.tv_sec - t0.tv_sec;
        temp.tv_usec = t1.tv_usec - t0.tv_usec;
    }

    elapsed = (float)temp.tv_sec + (float)temp.tv_usec/1000000;

    return elapsed;
}

bool HostApp_test_0001(void)
{
    uint32_t iterations = ETH_TEST_ITER_M_COUNT;
    TestFrame frames[1];
    DataFramePayload *payload;
    uint16_t len;
    uint32_t i;
    int32_t ret;
    bool status = PASS;

    printf("test_0001: START\n");

    /* Unicast packet with DUT's MAC address */
    frames[0].len = 100;
    payload = (DataFramePayload *)frames[0].frame.payload;
    memcpy(&frames[0].frame.hdr, &hdrUcastCtrl, ETH_HDR_LEN);

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Transmit one frame per iteration */
    for (i = 0; i < iterations; i++) {
        if (gHostApp.verbose)
            printf("test_0001: iteration: %d of %d\n", i+1, iterations);

        /* Unicast frame with DUT's MAC address */
        len = frames[0].len - ETH_HDR_LEN;
        ret = EthUtils_fillPayload(payload, i % ETH_TEST_NUM_TYPES, len);
        if (ret) {
            printf("test_0001: failed to create test packet: %d\n", ret);
            status = FAIL;
            break;
        }

        /* Transmit one frame */
        HostApp_transmit(frames, ARRAY_SIZE(frames), 1);
    }

    /* Indicate to the DUT that the test is complete */
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    printf("test_0001: transmitted %d of %d frames\n", i, iterations);
    printf("test_0001: END\n");

    return status;
}

bool HostApp_test_0002(void)
{
    uint32_t recvNum = 0;
    bool st;
    bool status = PASS;

    printf("test_0002: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    st = HostApp_receive(&recvNum);
    if (st == FAIL) {
        printf("test_0002: failed while receiving packets\n");
        status = FAIL;
    }

    /* Check that all packets were received */
    if (recvNum != ETH_TEST_ITER_M_COUNT) {
        printf("test_0002: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, recvNum);
        status = FAIL;
    }

    printf("test_0002: received %d of %d frames\n", recvNum, ETH_TEST_ITER_M_COUNT);
    printf("test_0002: END\n");

    return status;
}

bool HostApp_test_0003(void)
{
    uint32_t len;
    uint32_t cnt = 0;
    bool status;

    printf("test_0003: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Loop frames back to the DUT until STOP cmd is received */
    while (true) {
        if (gHostApp.verbose)
            printf("test_0003: iteration %d\n", cnt+1);

        /* Receive one frame */
        len = sizeof(rxFrame);
        status = HostApp_recv(&rxFrame, &len);
        if (status == FAIL) {
            printf("test_0003: failed to receive frame\n");
            HostApp_sendCmd(CTRL_FRAME_CMD_STOP);
            break;
        }

        if (gHostApp.verbose) {
            printf("test_0003: frame received (%d bytes)\n", len);
            if (gHostApp.veryVerbose)
                EthUtils_printFrame(&rxFrame, HOST_APP_VERBOSE_OCTETS);
        }

        /* End the test if STOP cmd is received */
        if (EthFrame_isStopCmd(&rxFrame))
            break;

        /* Swap src and dst MAC addresses */
        memcpy(rxFrame.hdr.dstMac, rxFrame.hdr.srcMac, ETH_HW_ADDR_LEN);
        memcpy(rxFrame.hdr.srcMac, gHostApp.hwAddr, ETH_HW_ADDR_LEN);

        if (gHostApp.verbose) {
            printf("test_0003: frame to be sent (%d bytes)\n", len);
            if (gHostApp.veryVerbose)
                EthUtils_printFrame(&rxFrame, HOST_APP_VERBOSE_OCTETS);
        }

        /* Send the frame back */
        HostApp_send(&rxFrame, len);
        cnt++;

        if (gHostApp.verbose)
            printf("test_0003: iteration %d complete\n", cnt);
    }

    printf("test_0003: looped back %d frames\n", cnt);
    printf("test_0003: END\n");

    return status;
}

bool HostApp_test_0004(void)
{
    uint32_t iterations = ETH_TEST_ITER_M_COUNT / 2;
    TestFrame frames[2];
    DataFramePayload *payload;
    uint16_t len;
    uint32_t i;
    int32_t ret;
    bool status = PASS;

    printf("test_0004: START\n");

    /* Unicast packet with DUT's MAC address */
    frames[0].len = 100;
    memcpy(&frames[0].frame.hdr, &hdrUcastCtrl, ETH_HDR_LEN);

    /* Unicast packet with MAC address to be rejected by DUT's filter */
    frames[1].len = 200;
    memcpy(&frames[1].frame.hdr, &hdrUcastInv, ETH_HDR_LEN);

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Transmit two frames per iteration */
    for (i = 0; i < iterations; i++) {
        if (gHostApp.verbose)
            printf("test_0004: iteration: %d of %d\n", i+1, iterations);

        /* Unicast packet with DUT's MAC address */
        payload = (DataFramePayload *)frames[0].frame.payload;
        len = frames[0].len - ETH_HDR_LEN;
        ret = EthUtils_fillPayload(payload, i % ETH_TEST_NUM_TYPES, len);
        if (ret) {
            printf("test_0004: failed to create test packet: %d\n", ret);
            status = FAIL;
            break;
        }

        /* Unicast packet with MAC address to be rejected by DUT's filter */
        payload = (DataFramePayload *)frames[1].frame.payload;
        len = frames[1].len - ETH_HDR_LEN;
        ret = EthUtils_fillPayload(payload, i % ETH_TEST_NUM_TYPES, len);
        if (ret) {
            printf("test_0004: failed to create test packet: %d\n", ret);
            status = FAIL;
            break;
        }

        /* Transmit the two packets */
        HostApp_transmit(frames, ARRAY_SIZE(frames), ARRAY_SIZE(frames));
    }

    /* Indicate to the DUT that the test is complete */
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    printf("test_0004: completed %d of %d iterations\n", i, iterations);
    printf("test_0004: END\n");

    return status;
}

bool HostApp_test_0005(void)
{
    TestFrame frames[2];
    DataFrame *frame;
    uint32_t num = ETH_TEST_ITER_M_COUNT;
    uint16_t len;
    bool status = PASS;

    printf("test_0005: START\n");

    len = frames[0].len = 1500;
    frame = (DataFrame *)&frames[0].frame;
    memcpy(&frame->hdr, &hdrUcastCtrl, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_1,
                         len - ETH_HDR_LEN);

    len = frames[1].len = 1500;
    frame = (DataFrame *)&frames[1].frame;

    /* Part 1: DUT's filter has been reset. Only packets with DUT's address
     *         should be accepted */
    memcpy(&frame->hdr, &hdrUcastInv, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_2,
                         len - ETH_HDR_LEN);

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);
    HostApp_transmit(frames, ARRAY_SIZE(frames), num);
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    /* Part 2: An unicast address has been added to the DUT's filter. Packets
     *         with new address as well as DUT's address should be accepted */
    memcpy(&frame->hdr, &hdrUcastVal, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_3,
                         len - ETH_HDR_LEN);

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);
    HostApp_transmit(frames, ARRAY_SIZE(frames), num);
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    /* Part 3: A multicast address has been added to the DUT's filter. Packets
     *         with the multicast address as well as DUT's address should be
     *         accepted */
    memcpy(&frame->hdr, &hdrMcast, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_2,
                         len - ETH_HDR_LEN);

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);
    HostApp_transmit(frames, ARRAY_SIZE(frames), num);
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    /* Part 4: The multicast address has been removed from the DUT's filter.
     *         Only packets with DUT's address should be accepted */
    memcpy(&frame->hdr, &hdrMcast, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_3,
                         len - ETH_HDR_LEN);

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);
    HostApp_transmit(frames, ARRAY_SIZE(frames), num);
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    /* Part 5: DUT's filter is open, all packets should be accepted */
    memcpy(&frame->hdr, &hdrUcastInv, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_4,
                         len - ETH_HDR_LEN);

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);
    HostApp_transmit(frames, ARRAY_SIZE(frames), num);
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    /* Part 5: DUT's filter has been reset. Only packets with DUT's address
     *         should be accepted */
    memcpy(&frame->hdr, &hdrUcastInv, ETH_HDR_LEN);
    EthUtils_fillPayload(&frame->payload,
                         ETH_TEST_TYPE_PATTERN_2,
                         len - ETH_HDR_LEN);

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);
    HostApp_transmit(frames, ARRAY_SIZE(frames), num);
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    printf("test_0005: END\n");

    return PASS;
}

bool HostApp_test_0006(void)
{
    uint32_t recvNum = 0;
    bool status;

    printf("test_0006: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    status = HostApp_receive(&recvNum);
    if (status == FAIL)
        printf("test_0006: failed while receiving packets\n");

    /* Check that all packets were received */
    if (recvNum != ETH_TEST_ITER_M_COUNT) {
        printf("test_0006: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, recvNum);
        status = FAIL;
    }

    printf("test_0006: received %d of %d frames\n", recvNum, ETH_TEST_ITER_M_COUNT);
    printf("test_0006: END\n");

    return status;
}

bool HostApp_test_0007(void)
{
    uint32_t recvNum = 0;
    bool st;
    bool status = PASS;

    printf("test_0007: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    st = HostApp_receive(&recvNum);
    if (st == FAIL) {
        printf("test_0007: failed while receiving packets\n");
        status = FAIL;
    }

    /* Check that all packets were received */
    if (recvNum != ETH_TEST_ITER_M_COUNT) {
        printf("test_0007: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, recvNum);
        status = FAIL;
    }

    printf("test_0007: received %d of %d frames\n", recvNum, ETH_TEST_ITER_M_COUNT);
    printf("test_0007: END\n");

    return status;
}

bool HostApp_test_0008(void)
{
    uint32_t recvNum;
    uint16_t len;
    bool st;
    bool status = PASS;

    printf("test_0008: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    for (len = 10; len <= 1500; len += 10) {
        recvNum = 0;
        st = HostApp_receive(&recvNum);
        if (st == FAIL) {
            printf("test_0008: failed while receiving packets\n");
            status = FAIL;
        }

        /* Check that all packets were received */
        if (recvNum != ETH_TEST_ITER_S_COUNT) {
            printf("test_0008: received frame count mismatch (exp=%d, got=%d)\n",
                   ETH_TEST_ITER_S_COUNT, recvNum);
            status = FAIL;
        }
    }

    printf("test_0008: END\n");

    return status;
}

bool HostApp_test_0009(void)
{
    uint32_t iterations = ETH_TEST_ITER_M_COUNT;
    TestFrame frames[1];
    VlanDataFramePayload *payload;
    uint16_t len;
    uint32_t i;
    int32_t ret;
    bool status = PASS;

    printf("test_0009: START\n");

    /* Unicast packet with DUT's MAC address */
    frames[0].len = 100;
    payload = (VlanDataFramePayload *)frames[0].frame.payload;
    memcpy(&frames[0].frame.hdr, &hdrUcastCtrl, ETH_HDR_LEN);
    frames[0].frame.hdr.etherType = htons(ETHERTYPE_VLAN_TAG);

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Transmit one frame per iteration */
    for (i = 0; i < iterations; i++) {
        if (gHostApp.verbose)
            printf("test_0009: iteration: %d of %d\n", i+1, iterations);

        /* Unicast frame with DUT's MAC address */
        len = frames[0].len - ETH_HDR_LEN;
        ret = EthUtils_fillVlanPayload(payload,
                                       i % ETH_TEST_NUM_TYPES,
                                       len,
                                       ETH_TEST_VLAN_PCP,
                                       ETH_TEST_VLAN_VID,
                                       ETHERTYPE_EXPERIMENTAL1);
        if (ret) {
            printf("test_0009: failed to create test packet: %d\n", ret);
            status = FAIL;
            break;
        }

        /* Transmit one frame */
        HostApp_transmit(frames, ARRAY_SIZE(frames), 1);
    }

    /* Indicate to the DUT that the test is complete */
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    printf("test_0009: transmitted %d of %d frames\n", i, iterations);
    printf("test_0009: END\n");

    return status;
}

bool HostApp_test_0010(void)
{
    uint32_t iterations = ETH_TEST_ITER_S_COUNT;
    uint32_t i;
    bool status = PASS;
    bool st;

    printf("test_0010: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Transmit and receive packets after DUT's mode change */
    for (i = 0; i < iterations; i++) {
        if (gHostApp.verbose)
            printf("test_0010: iteration: %d\n", i+1);

        /* Receive packets */
        st = HostApp_test_0002();
        if (st == FAIL) {
            printf("test_0010: failed to receive packets\n");
            status = FAIL;
        }

        /* Transmit packets */
        st = HostApp_test_0001();
        if (st == FAIL) {
            printf("test_0010: failed to transmit packets\n");
            status = FAIL;
        }
    }

    printf("test_0010: completed %d of %d iterations\n", i, iterations);
    printf("test_0010: END\n");

    return status;
}

bool HostApp_test_0011(void)
{
    uint32_t recvNum = 0;
    bool st;
    bool status = PASS;

    printf("test_0011: START\n");

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    st = HostApp_receive(&recvNum);
    if (st == FAIL) {
        printf("test_0011: failed while receiving packets\n");
        status = FAIL;
    }

    /* Check that all packets were received */
    if (recvNum != ETH_TEST_ITER_M_COUNT) {
        printf("test_0011: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_M_COUNT, recvNum);
        status = FAIL;
    }

    printf("test_0011: received %d of %d frames\n", recvNum, ETH_TEST_ITER_M_COUNT);
    printf("test_0011: END\n");

    return status;
}

bool HostApp_test_0100(uint32_t frames, uint32_t size)
{
    bool status;

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets and measure the throughput */
    status = HostApp_receiveTput(frames, size);
    if (status == FAIL)
        printf("test_0100: failed to get receive throughput\n");

    return status;
}

bool HostApp_test_0110(void)
{
    uint16_t txPktSizeMesure[] = { 1500u,   512u,    256u,    128u,    64u };
    uint32_t iterator_num[]    = { 150000u, 150000u, 150000u, 150000u, 150000u };
    bool status;
    uint32_t si;

    printf("test_0110: START\n");

    for(si = 0; si< sizeof(txPktSizeMesure)/sizeof(unsigned short); ++si)
    {
        status = HostApp_test_0100(iterator_num[si], txPktSizeMesure[si]);
    }

    printf("test_0110: DONE\n");

    return status;
}


bool HostApp_test_0101(void)
{
    uint32_t iterations = ETH_TEST_ITER_L_COUNT;
    uint16_t rxPktSizeMesure[] = { 1500u,   512u,    256u,    128u,    64u };
    uint32_t iterator_num[]    = { 150000u, 150000u, 150000u, 300000u, 300000u };
    uint32_t delay[]           = { 0u,      0u,      40u,     40u,     30u };
    TestFrame frames[1];
    DataFramePayload *payload;
    uint32_t i, si;
    int32_t ret;
    bool status = PASS;
    struct timeval t0, t1;
    float elapsed;
    float pps;
    float mbps;
    long long total = 0;
    ssize_t bytes;
    int j;

    EthUtils_printf("test_0101: START\n");

    for(si = 0; si< sizeof(rxPktSizeMesure)/sizeof(unsigned short); ++si)
    {
        /* Unicast packet with DUT's MAC address */
        frames[0].len = rxPktSizeMesure[si];
        payload = (DataFramePayload *)frames[0].frame.payload;
        memcpy(&frames[0].frame.hdr, &hdrUcastCtrl, ETH_HDR_LEN);
        frames[0].frame.hdr.etherType = htons(ETHERTYPE_EXPERIMENTAL3);

        iterations = iterator_num[si];

        /* Wait for DUT to start the test when it's ready */
        HostApp_waitForCmd(CTRL_FRAME_CMD_START);

        gettimeofday(&t0, NULL);

        /* Transmit one frame per iteration */
        for (i = 0; i < iterations; i++) {
            if (gHostApp.verbose)
                EthUtils_printf("test_0101: iteration: %d of %d\n", i+1, iterations);

            /* Transmit one frame */
            HostApp_send(&frames[0].frame, frames[0].len);
            if((delay[si] > 0u) && (i % delay[si] == 0))
            usleep(1);
        }

        /* Indicate to the DUT that the test is complete */
        HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

        /* Get the "end" timestamp after DUT is done sending frames */
        gettimeofday(&t1, NULL);

        /* Indicate to the DUT that the test is complete, try couple times to prevent lost of STOP packet */
        for(j=0; j<10; ++j) {
            HostApp_sendCmd(CTRL_FRAME_CMD_STOP);
            usleep(10000);
        }

       /* Compute elapsed time, packets per second and Mbps */
       elapsed = HostApp_timeDiff(t1, t0);
       pps = (float)i / elapsed;
       mbps = (float)i*frames[0].len * 8 / elapsed / 1000000;

       EthUtils_printf("transmitTput: TX side transmitted %d frames in %.2f secs (%.2f frames/s, %.2f Mbps)\n",
           i, elapsed, pps, mbps);
    }

    printf("test_0101: END\n");

    return status;
}

bool HostApp_test_0300(void)
{
    uint32_t i,iterations = ETH_TEST_ITER_S_COUNT;
    bool status = PASS;
    uint32_t recvNum;
    bool st;

    EthUtils_printf("test_0300: START\r\n");

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    st = HostApp_receive(&recvNum);
    if (st == FAIL) {
        printf("test_0300: failed while receiving packets\n");
        status = FAIL;
    }

    /* Check that all packets were received */
    if (recvNum != ETH_TEST_ITER_S_COUNT) {
        printf("test_0300: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_S_COUNT, recvNum);
        status = FAIL;
    }

    EthUtils_printf("test_0300: END\r\n");

    return status;
}

bool HostApp_test_0301(void)
{
    uint32_t iterations = ETH_TEST_ITER_S_COUNT;
    TestFrame frames[1];
    DataFramePayload *payload;
    uint16_t len;
    uint32_t i;
    int32_t ret;
    bool status = PASS;
    bool st;

    printf("test_0301: START\n");

    /* Unicast packet with DUT's MAC address */
    frames[0].len = 100;
    payload = (DataFramePayload *)frames[0].frame.payload;
    memcpy(&frames[0].frame.hdr, &hdrUcastCtrl, ETH_HDR_LEN);

    /* Wait for DUT to start the test when it's ready */
    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Transmit one frame per iteration */
    for (i = 0; i < iterations; i++) {
        if (gHostApp.verbose)
            printf("test_0301: iteration: %d of %d\n", i+1, iterations);

        /* Unicast frame with DUT's MAC address */
        len = frames[0].len - ETH_HDR_LEN;
        ret = EthUtils_fillPayload(payload, i % ETH_TEST_NUM_TYPES, len);
        if (ret) {
            printf("test_0301: failed to create test packet: %d\n", ret);
            status = FAIL;
            break;
        }

        /* Transmit one frame */
        HostApp_transmit(frames, ARRAY_SIZE(frames), 1);
        usleep(1000000u);
    }

    /* Indicate to the DUT that the test is complete */
    HostApp_sendCmd(CTRL_FRAME_CMD_STOP);

    printf("test_0301: transmitted %d of %d frames\n", i, iterations);
    printf("test_0301: END\n");
}

bool HostApp_test_0302(void)
{
    uint32_t i,iterations = ETH_TEST_ITER_S_COUNT;
    bool status = PASS;
    uint32_t recvNum;
    bool st;

    EthUtils_printf("test_0302: START\r\n");

    HostApp_waitForCmd(CTRL_FRAME_CMD_START);

    /* Receive packets indefinitely until STOP cmd is detected */
    st = HostApp_receive(&recvNum);
    if (st == FAIL) {
        printf("test_0302: failed while receiving packets\n");
        status = FAIL;
    }

    /* Check that all packets were received */
    if (recvNum != ETH_TEST_ITER_S_COUNT) {
        printf("test_0302: received frame count mismatch (exp=%d, got=%d)\n",
               ETH_TEST_ITER_S_COUNT, recvNum);
        status = FAIL;
    }

    EthUtils_printf("test_0302: END\r\n");

    return status;
}

#if (STD_ON == ETH_WRAPPER_ENABLED)
bool HostApp_test_0400(void)
{
    uint32_t frames = 15000;
    bool status = PASS;
    int i = 0;

    for(i = 7; i >= 0; i--)
    {
        printf("test_0400: START %d\n", i);
        /* Wait for DUT to start the test when it's ready */
        HostApp_waitForCmd(CTRL_FRAME_CMD_START);

        /* Receive packets and measure the throughput */
        status = HostApp_receiveTput(MAX_RX_PKT, frames);
        if (status == FAIL)
            printf("test_0400: failed to get receive throughput\n");

        printf("test_0400: END\n");
    }

    return status;
}
#endif