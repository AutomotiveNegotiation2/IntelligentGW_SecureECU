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

/**
 *  \file ethfw_callbacks_lwipif.c
 *
 *  \brief Default LwIP interface callbacks for Ethernet Firmware application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>

#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/include/dma/udma/enet_udma.h>
#include <ti/drv/udma/udma.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils_cfg.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils.h>
#include <ti/drv/enet/examples/utils/include/enet_mcm.h>
#include <ti/drv/enet/examples/utils/include/enet_apprm.h>
#include <ti/drv/enet/lwipif/inc/lwipif2enet_appif.h>

#include <utils/ethfw_callbacks/include/ethfw_callbacks_lwipif.h>
#include <utils/ethfw_lwip/include/ethfw_lwip_utils.h>
#include <utils/console_io/include/app_log.h>

/* If defined, enables ARP packet handle function debug prints */
#undef ETHFW_CALLBACKS_DEBUG

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*! Remote app packet poll period in milliseconds */
#define CPSW_REMOTE_APP_PACKET_POLL_PERIOD_US         (1000U)

/*! Number of entries in the address table */
#define CPSW_REMOTE_CORE_TABLE_SIZE                   (4U)

/*!
 * \brief Table entry with IP address and MAC address for remote cores.
 */
typedef struct EthFwCallbacks_RemoteCoreAddrTable_s
{
    /*! Remote core's IP address */
    ip4_addr_t ipAddr;

    /*! Remote core's MAC address */
    struct eth_addr hwAddr;

    /*! Whether this entry is free or not */
    bool isFree;
} EthFwCallbacks_RemoteCoreAddrTable;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if defined(ETHFW_PROXY_ARP_HANDLING)
static int32_t EthFwCallbacks_setupArpRoute(Enet_Handle hEnet,
                                            uint32_t coreKey,
                                            uint32_t coreId,
                                            EnetMcm_HandleInfo *handleInfo,
                                            LwipifEnetAppIf_RxConfig *arpRxCfg,
                                            EnetDma_RxChHandle *hRxFlow,
                                            uint32_t *rxFlowStartIdx,
                                            uint32_t *flowIdx);

static void EthFwCallbacks_teardownArpRoute(Enet_Handle hEnet,
                                            uint32_t coreKey,
                                            uint32_t coreId,
                                            EnetDma_RxChHandle hRxFlow,
                                            uint32_t rxFlowStartIdx,
                                            uint32_t flowIdx,
                                            Lwip2EnetAppIf_FreePktInfo *freePktInfo);

static bool EthFwCallbacks_handleArpRxPktFxn(struct netif *netif,
                                             struct pbuf *pbuf);
#endif
/* ========================================================================== */
/*                          Extern variables                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void EthFwCallbacks_lwipifCpswGetHandle(LwipifEnetAppIf_GetHandleInArgs *inArgs,
                                        LwipifEnetAppIf_GetHandleOutArgs *outArgs)
{
    LwipifEnetAppIf_RxHandleInfo *rxInfo;
    LwipifEnetAppIf_RxConfig *rxCfg;
    EnetMcm_CmdIf mcmCmdIf;
    EnetMcm_HandleInfo handleInfo;
    EnetPer_AttachCoreOutArgs attachInfo;
    EnetUdma_OpenTxChPrms cpswTxChCfg;
    EnetUdma_OpenRxFlowPrms cpswRxFlowCfg;
    EnetUdma_UdmaRingPrms *pFqRingPrms;
#if defined(SOC_J721E) || defined(SOC_J784S4)
    Enet_Type enetType = ENET_CPSW_9G;
#elif defined(SOC_J7200)
    Enet_Type enetType = ENET_CPSW_5G;
#endif
    uint8_t *macAddr;
    uint32_t coreId = EnetSoc_getCoreId();
    bool useDefaultFlow = true;    /* Must handle the default flow */
    bool useRingMon = true;
#if defined(ETHFW_PROXY_ARP_HANDLING)
    int32_t status;
#endif

    /* Get MCM command interface */
    EnetMcm_getCmdIf(enetType, &mcmCmdIf);
    EnetAppUtils_assert(mcmCmdIf.hMboxCmd != NULL);
    EnetAppUtils_assert(mcmCmdIf.hMboxResponse != NULL);

    /* Get CPSW and UDMA driver handles */
    EnetMcm_acquireHandleInfo(&mcmCmdIf, &handleInfo);

    /* Attach this core, if not done already */
    EnetMcm_coreAttach(&mcmCmdIf, coreId, &attachInfo);

    /* Open TX channel */
    EnetDma_initTxChParams(&cpswTxChCfg);
    cpswTxChCfg.hUdmaDrv            = handleInfo.hUdmaDrv;
    cpswTxChCfg.numTxPkts           = inArgs->txCfg.numPackets;
    cpswTxChCfg.cbArg               = inArgs->txCfg.cbArg;
    cpswTxChCfg.notifyCb            = inArgs->txCfg.notifyCb;
    cpswTxChCfg.useProxy            = true;
    cpswTxChCfg.disableCacheOpsFlag = false;
    cpswTxChCfg.ringMemAllocFxn     = &EnetMem_allocRingMem;
    cpswTxChCfg.ringMemFreeFxn      = &EnetMem_freeRingMem;
    cpswTxChCfg.dmaDescAllocFxn     = &EnetMem_allocDmaDesc;
    cpswTxChCfg.dmaDescFreeFxn      = &EnetMem_freeDmaDesc;

    EnetAppUtils_openTxCh(handleInfo.hEnet,
                          attachInfo.coreKey,
                          coreId,
                          &outArgs->txInfo.txChNum,
                          &outArgs->txInfo.hTxChannel,
                          &cpswTxChCfg);

    /* Open first RX channel/flow */
    rxCfg  = &inArgs->rxCfg[0U];
    rxInfo = &outArgs->rxInfo[0U];

    EnetDma_initRxChParams(&cpswRxFlowCfg);
    cpswRxFlowCfg.notifyCb  = rxCfg->notifyCb;
    cpswRxFlowCfg.numRxPkts = rxCfg->numPackets;
    cpswRxFlowCfg.hUdmaDrv  = handleInfo.hUdmaDrv;
    cpswRxFlowCfg.cbArg     = rxCfg->cbArg;
    cpswRxFlowCfg.useProxy  = true;

    /* Use ring monitor for the CQ ring of RX flow */
    pFqRingPrms                  = &cpswRxFlowCfg.udmaChPrms.fqRingPrms;
    pFqRingPrms->useRingMon      = useRingMon;
    pFqRingPrms->ringMonCfg.mode = TISCI_MSG_VALUE_RM_MON_MODE_THRESHOLD;
    /* Ring mon low threshold */
#if defined _DEBUG_
    /* In debug mode as CPU is processing lesser packets per event, keep threshold more */
    pFqRingPrms->ringMonCfg.data0 = (rxCfg->numPackets - 10U);
#else
    pFqRingPrms->ringMonCfg.data0 = (rxCfg->numPackets - 20U);
#endif
    /* Ring mon high threshold - to get only low  threshold event, setting high threshold as more than ring depth*/
    pFqRingPrms->ringMonCfg.data1 = rxCfg->numPackets;

    cpswRxFlowCfg.disableCacheOpsFlag = false;
    cpswRxFlowCfg.rxFlowMtu           = attachInfo.rxMtu;
    cpswRxFlowCfg.ringMemAllocFxn     = &EnetMem_allocRingMem;
    cpswRxFlowCfg.ringMemFreeFxn      = &EnetMem_freeRingMem;
    cpswRxFlowCfg.dmaDescAllocFxn     = &EnetMem_allocDmaDesc;
    cpswRxFlowCfg.dmaDescFreeFxn      = &EnetMem_freeDmaDesc;

    EnetAppUtils_openRxFlow(enetType,
                            handleInfo.hEnet,
                            attachInfo.coreKey,
                            coreId,
                            useDefaultFlow,
                            &rxInfo->rxFlowStartIdx,
                            &rxInfo->rxFlowIdx,
                            &rxInfo->macAddr[0U],
                            &rxInfo->hRxFlow,
                            &cpswRxFlowCfg);

    outArgs->coreId          = coreId;
    outArgs->coreKey         = attachInfo.coreKey;
    outArgs->hEnet           = handleInfo.hEnet;
    outArgs->hostPortRxMtu   = attachInfo.rxMtu;
    ENET_UTILS_ARRAY_COPY(outArgs->txMtu, attachInfo.txMtu);
    outArgs->hUdmaDrv        = handleInfo.hUdmaDrv;
    outArgs->print           = &EnetAppUtils_print;
    outArgs->isPortLinkedFxn = &EthFwCallbacks_isPortLinked;

    /* TODO: Polling timer is getting corrupted at times of sudden burst of
     * traffic, because of which timer callback is never called.
     * With polling timer not functional, packets are never serviced then after.
     * As a workaround setting isRingMonUsed to true (irrespective of ring monitor
     * is enabled or not) to ensure interrupts are used instead of polling.
     * Timer corruption needs to be root-caused and fixed. */
    rxInfo->disableEvent = !useRingMon;
    outArgs->timerPeriodUs = CPSW_REMOTE_APP_PACKET_POLL_PERIOD_US;

    /* Let LwIP interface use optimized processing where TX packets are relinquished
     * in next TX submit call */
    outArgs->txInfo.disableEvent = true;

    outArgs->txInfo.txPortNum = ENET_MAC_PORT_INV;

    macAddr = &rxInfo->macAddr[0U];
    appLogPrintf("Host MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n",
                 macAddr[0] & 0xFF, macAddr[1] & 0xFF, macAddr[2] & 0xFF,
                 macAddr[3] & 0xFF, macAddr[4] & 0xFF, macAddr[5] & 0xFF);


#if defined(ETHFW_PROXY_ARP_HANDLING)
    rxInfo->handlePktFxn = NULL;

    /* Open second RX channel/flow for ARP */
    rxCfg  = &inArgs->rxCfg[1U];
    rxInfo = &outArgs->rxInfo[1U];

    status = EthFwCallbacks_setupArpRoute(handleInfo.hEnet,
                                          outArgs->coreKey,
                                          outArgs->coreId,
                                          &handleInfo,
                                          rxCfg,
                                          &rxInfo->hRxFlow,
                                          &rxInfo->rxFlowStartIdx,
                                          &rxInfo->rxFlowIdx);
    if (status != ENET_SOK)
    {
        /* Just print an error as EthFw and its clients will continue to run with
         * limited functionality */
        appLogPrintf("Failed to setup route for ARP request packets: %d\n", status);
    }
    else
    {
        rxInfo->handlePktFxn = EthFwCallbacks_handleArpRxPktFxn;
    }
#endif
}

void EthFwCallbacks_lwipifCpswReleaseHandle(LwipifEnetAppIf_ReleaseHandleInfo *releaseInfo)
{
    LwipifEnetAppIf_RxHandleInfo *rxInfo;
    Lwip2EnetAppIf_FreePktInfo *freePktInfo;
    EnetMcm_CmdIf mcmCmdIf;
    EnetDma_PktQ fqPktInfoQ;
    EnetDma_PktQ cqPktInfoQ;
#if defined(SOC_J721E) || defined(SOC_J784S4)
    Enet_Type enetType = ENET_CPSW_9G;
#elif defined(SOC_J7200)
    Enet_Type enetType = ENET_CPSW_5G;
#endif
    bool useDefaultFlow = true;    /* Must handle the default flow */

    /* Get MCM command interface */
    EnetMcm_getCmdIf(enetType, &mcmCmdIf);
    EnetAppUtils_assert(mcmCmdIf.hMboxCmd != NULL);
    EnetAppUtils_assert(mcmCmdIf.hMboxResponse != NULL);

#if defined(ETHFW_PROXY_ARP_HANDLING)
    /* Tear-down ARP route (RX flow + ALE classifier) */
    rxInfo = &releaseInfo->rxInfo[1U];
    freePktInfo = &releaseInfo->rxFreePkt[1U];

    EthFwCallbacks_teardownArpRoute(releaseInfo->hEnet,
                                    releaseInfo->coreKey,
                                    releaseInfo->coreId,
                                    rxInfo->hRxFlow,
                                    rxInfo->rxFlowStartIdx,
                                    rxInfo->rxFlowIdx,
                                    freePktInfo);
#endif

    /* Close TX channel */
    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);
    EnetAppUtils_closeTxCh(releaseInfo->hEnet,
                           releaseInfo->coreKey,
                           releaseInfo->coreId,
                           &fqPktInfoQ,
                           &cqPktInfoQ,
                           releaseInfo->txInfo.hTxChannel,
                           releaseInfo->txInfo.txChNum);
    releaseInfo->txFreePkt.cb(releaseInfo->txFreePkt.cbArg, &fqPktInfoQ, &cqPktInfoQ);

    /* Close first RX channel/flow */
    rxInfo = &releaseInfo->rxInfo[0U];
    freePktInfo = &releaseInfo->rxFreePkt[0U];

    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);
    EnetAppUtils_closeRxFlow(enetType,
                             releaseInfo->hEnet,
                             releaseInfo->coreKey,
                             releaseInfo->coreId,
                             useDefaultFlow,
                             &fqPktInfoQ,
                             &cqPktInfoQ,
                             rxInfo->rxFlowStartIdx,
                             rxInfo->rxFlowIdx,
                             rxInfo->macAddr,
                             rxInfo->hRxFlow);
    freePktInfo->cb(freePktInfo->cbArg, &fqPktInfoQ, &cqPktInfoQ);

    EnetMcm_coreDetach(&mcmCmdIf, releaseInfo->coreId, releaseInfo->coreKey);
    EnetMcm_releaseHandleInfo(&mcmCmdIf);
}

#if defined(ETHFW_PROXY_ARP_HANDLING)
static int32_t EthFwCallbacks_setupArpRoute(Enet_Handle hEnet,
                                     uint32_t coreKey,
                                     uint32_t coreId,
                                     EnetMcm_HandleInfo *handleInfo,
                                     LwipifEnetAppIf_RxConfig *arpRxCfg,
                                     EnetDma_RxChHandle *hRxFlow,
                                     uint32_t *rxFlowStartIdx,
                                     uint32_t *flowIdx)
{
    EnetDma_Handle hDma = Enet_getDmaHandle(hEnet);
    const uint8_t bcastAddr[ENET_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    EnetUdma_OpenRxFlowPrms rxFlowCfg;
    CpswAle_SetPolicerEntryInArgs polInArgs;
    CpswAle_SetPolicerEntryOutArgs polOutArgs;
    Enet_IoctlPrms prms;
    int32_t status = ENET_SOK;

    if (hDma == NULL)
    {
        appLogPrintf("Failed to get Enet DMA handle\n");
        status = ENET_EFAIL;
    }

    if (status == ENET_SOK)
    {
        status = EnetAppUtils_allocRxFlow(hEnet, coreKey, coreId, rxFlowStartIdx, flowIdx);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed to alloc RX flow for ARP traffic: %d\n", status);
        }
    }

    /* Open RX Flow */
    if (status == ENET_SOK)
    {
        EnetDma_initRxChParams(&rxFlowCfg);
        rxFlowCfg.startIdx  = *rxFlowStartIdx;
        rxFlowCfg.flowIdx   = *flowIdx;
        rxFlowCfg.notifyCb  = arpRxCfg->notifyCb;
        rxFlowCfg.cbArg     = arpRxCfg->cbArg;
        rxFlowCfg.numRxPkts = arpRxCfg->numPackets;
        rxFlowCfg.hUdmaDrv  = handleInfo->hUdmaDrv;
        rxFlowCfg.useProxy  = true;
        EnetAppUtils_setCommonRxFlowPrms(&rxFlowCfg);

        *hRxFlow = EnetDma_openRxCh(hDma, &rxFlowCfg);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed to open RX flow for ARP traffic: %d\n", status);
        }
    }

    /* Set policer for ARP EtherType + Broadcast address matching */
    if (status == ENET_SOK)
    {
        /* Set policer params for ARP EtherType matching */
        polInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_ETHERTYPE;
        polInArgs.policerMatch.etherType = ETHTYPE_ARP;
        polInArgs.policerMatch.portIsTrunk = false;

        /* Set policer params for broadcast address matching
         * Note that policer IOCTL takes a port number not a port mask which is what
         * we really need (mask = CPSW_ALE_ALL_PORTS_MASK).  So, we would have to
         * amend the ALE broadcast entry with another IOCTL, but the EthFw library
         * creates such broadcast entry (see EthFw_setAleBcastEntry(), so we
         * intentionally won't do it here. */
        polInArgs.policerMatch.policerMatchEnMask |= CPSW_ALE_POLICER_MATCH_MACDST;
        polInArgs.policerMatch.dstMacAddrInfo.portNum = CPSW_ALE_HOST_PORT_NUM;
        polInArgs.policerMatch.dstMacAddrInfo.addr.vlanId = 0U;
        EnetUtils_copyMacAddr(&polInArgs.policerMatch.dstMacAddrInfo.addr.addr[0], &bcastAddr[0]);

        polInArgs.threadIdEn = true;
        polInArgs.threadId   = *flowIdx;
        polInArgs.peakRateInBitsPerSec   = 0U;
        polInArgs.commitRateInBitsPerSec = 0U;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &polInArgs, &polOutArgs);

        status = Enet_ioctl(hEnet, coreId, CPSW_ALE_IOCTL_SET_POLICER, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed to add ARP policer: %d\n", status);
        }
    }

    return status;
}

static void EthFwCallbacks_teardownArpRoute(Enet_Handle hEnet,
                                            uint32_t coreKey,
                                            uint32_t coreId,
                                            EnetDma_RxChHandle hRxFlow,
                                            uint32_t rxFlowStartIdx,
                                            uint32_t flowIdx,
                                            Lwip2EnetAppIf_FreePktInfo *freePktInfo)
{
    EnetDma_Handle hDma = Enet_getDmaHandle(hEnet);
    EnetDma_PktQ fqPktInfoQ;
    EnetDma_PktQ cqPktInfoQ;
    const uint8_t bcastAddr[ENET_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    CpswAle_DelPolicerEntryInArgs polInArgs;
    Enet_IoctlPrms prms;
    int32_t status;

    /* Set policer params for ARP EtherType matching */
    polInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_ETHERTYPE;
    polInArgs.policerMatch.etherType = ETHTYPE_ARP;
    polInArgs.policerMatch.portIsTrunk = false;

    /* Set policer params for broadcast address matching */
    polInArgs.policerMatch.policerMatchEnMask |= CPSW_ALE_POLICER_MATCH_MACDST;
    polInArgs.policerMatch.dstMacAddrInfo.portNum = CPSW_ALE_HOST_PORT_NUM;
    polInArgs.policerMatch.dstMacAddrInfo.addr.vlanId = 0U;
    EnetUtils_copyMacAddr(&polInArgs.policerMatch.dstMacAddrInfo.addr.addr[0], &bcastAddr[0]);

    /* We didn't add broadcast entry for all ports, so we won't delete anything either */
    polInArgs.aleEntryMask = CPSW_ALE_POLICER_MATCH_ETHERTYPE;

    ENET_IOCTL_SET_IN_ARGS(&prms, &polInArgs);

    /* Delete ALE policer */
    status = Enet_ioctl(hEnet, coreId, CPSW_ALE_IOCTL_DEL_POLICER, &prms);
    if (status != ENET_SOK)
    {
        appLogPrintf("Failed to delete ARP policer: %d\n", status);
    }

    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);

    if (hRxFlow != NULL)
    {
        EnetDma_disableRxEvent(hRxFlow);

        /* Close RX flow */
        status = EnetDma_closeRxCh(hRxFlow, &fqPktInfoQ, &cqPktInfoQ);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed to close RX flow used for ARP traffic: %d\n", status);
        }

        /* Free RX flow only if channel was closed */
        if (status == ENET_SOK)
        {
            status = EnetAppUtils_freeRxFlow(hEnet, coreKey, coreId, flowIdx);
            if (status != ENET_SOK)
            {
                appLogPrintf("Failed to free RX flow used for ARP traffic: %d\n", status);
            }

            freePktInfo->cb(freePktInfo->cbArg, &fqPktInfoQ, &cqPktInfoQ);
        }
    }
}

static bool EthFwCallbacks_handleArpRxPktFxn(struct netif *netif,
                                             struct pbuf *pbuf)
{
    struct eth_hdr *ethHdr;
    struct etharp_hdr *ethArpHdr;
    struct eth_addr hwAddr;
#if defined(ETHFW_CALLBACKS_DEBUG)
    uint8_t *dstMac;
#endif
    ip4_addr_t srcIp;
    ip4_addr_t dstIp;
    bool handled = false;
    int32_t status;

    ethHdr = (struct eth_hdr *)(pbuf->payload);
    ethArpHdr = (struct etharp_hdr *)(ethHdr + 1);

    IPADDR_WORDALIGNED_COPY_TO_IP4_ADDR_T(&srcIp, &ethArpHdr->sipaddr);
    IPADDR_WORDALIGNED_COPY_TO_IP4_ADDR_T(&dstIp, &ethArpHdr->dipaddr);

#if defined(ETHFW_CALLBACKS_DEBUG)
    dstMac = &ethHdr->dest.addr[0];

    appLogPrintf("Received ARP dstIp %s, dstMac %02x:%02x:%02x:%02x:%02x:%02x\n",
                 ip4addr_ntoa(&dstIp),
                 dstMac[0] & 0xFF, dstMac[1] & 0xFF, dstMac[2] & 0xFF,
                 dstMac[3] & 0xFF, dstMac[4] & 0xFF, dstMac[5] & 0xFF);
#endif

    status = EthFwArpUtils_getHwAddr(&dstIp, &hwAddr);
    if (status == ETHFW_LWIP_UTILS_SOK)
    {
        EthFwArpUtils_sendRaw(netif,
                              &hwAddr,
                              &ethArpHdr->shwaddr,
                              &hwAddr,
                              &dstIp,
                              &ethArpHdr->shwaddr,
                              &srcIp,
                              ARP_REPLY);

#if defined(ETHFW_CALLBACKS_DEBUG)
        appLogPrintf("Sent ARP response\n");
#endif
        handled = true;
    }

    return handled;
}
#endif
