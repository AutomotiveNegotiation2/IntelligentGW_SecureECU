/*
 *  Copyright (c) Texas Instruments Incorporated 2021
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
 * \file  main.c
 *
 * \brief Main file for lwIP example application.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdarg.h>

/* lwIP header files */
#include <lwipopts.h>
#include <lwip/api.h>
#include <lwip/netif.h>
#include <arch/sys_arch.h>
#include <ti/drv/enet/lwipif/inc/lwipif2enet_appif.h>

#include <ti/drv/sciclient/sciclient.h>
#include <ti/drv/udma/udma.h>
#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils_rtos.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils.h>
#include <ti/drv/enet/examples/utils/include/enet_mcm.h>
#include <ti/drv/enet/examples/utils/include/enet_apprm.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils_cfg.h>
#include <ti/drv/enet/examples/utils/include/enet_board.h>
#if defined(ENET_ENABLE_ICSSG)
#include <ti/drv/enet/include/per/icssg.h>
#endif

#include <ti/drv/enet/include/core/enet_per.h>
#include <ti/drv/enet/include/core/enet_soc.h>
#include <ti/drv/enet/include/per/cpsw.h>
#include <ti/drv/enet/include/mod/cpsw_ale.h>
#include <ti/drv/enet/include/mod/cpsw_macport.h>

/* OSAL Header files */
#include <ti/osal/osal.h>
#include <ti/osal/LoadP.h>

#if defined(ENET_ENABLE_TIMESYNC)
/* Timesync header files */
#include <ti/drv/enet/examples/timesync/timeSync.h>
#include <ti/drv/enet/examples/timesync/protocol/ptp/include/timeSync_ptp.h>
#endif

#include "test_config.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined(SAFERTOS)
#define ENETAPP_TSK_STACK_APPINIT         (16U * 1024U)
#define ENETAPP_TSK_STACK_MAIN            (16U * 1024U)
#define ENETAPP_TSK_STACK_CPU_LOAD        (16U * 1024U)
#define ENETAPP_TSK_STACK_APPINIT_ALIGN   ENETAPP_TSK_STACK_APPINIT
#define ENETAPP_TSK_STACK_MAIN_ALIGN      ENETAPP_TSK_STACK_MAIN
#define ENETAPP_TSK_STACK_CPU_LOAD_ALIGN  ENETAPP_TSK_STACK_CPU_LOAD
#else
#define ENETAPP_TSK_STACK_APPINIT         (5U * 1024U)
#define ENETAPP_TSK_STACK_MAIN            (5U * 1024U)
#define ENETAPP_TSK_STACK_CPU_LOAD        (2U * 1024U)
#define ENETAPP_TSK_STACK_APPINIT_ALIGN   (32U)
#define ENETAPP_TSK_STACK_MAIN_ALIGN      (32U)
#define ENETAPP_TSK_STACK_CPU_LOAD_ALIGN  (32U)
#define ENETAPP_TSK_STACK_ALIGN           (32U)
#endif

/* How often lwIP adaptation layer will poll for RX packets (pacing timer period) */
#define ENETAPP_PACKET_POLL_PERIOD_US     (1000U)

/* Configuration via menu or statically */
#define APP_ENABLE_STATIC_CFG             (0U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct EnetApp_Cfg_s
{
    /* Peripheral instance type */
    Enet_Type enetType;

    /* Peripheral instance id */
    uint32_t instId;

    /* Ethernet ports to be enabled */
    EnetBoard_EthPort ethPorts[ENET_MAC_PORT_NUM];

    /* Number of Ethernet ports to be enabled */
    uint32_t numEthPorts;

    /* Whether or not to use RX default flow */
    bool useDfltFlow;

    /* Whether PTP stack will be used for the test or not */
    bool useTimeSyncPtp;
} EnetApp_Cfg;

typedef struct EnetApp_Obj_s
{
    /* Host MAC address */
    uint8_t macAddr[ENET_MAC_ADDR_LEN];

    /* Enet MCM handle */
    EnetMcm_CmdIf hMcmCmdIf[ENET_TYPE_NUM];

    /* UDMA driver handle */
    Udma_DrvHandle hUdmaDrv;

#if defined(ENET_ENABLE_TIMESYNC)
    /* Handle to PTP stack */
    TimeSyncPtp_Handle hTimeSyncPtp;
#endif

    /* Handle to task which performs board initialization, test menu and starts
     * lwIP main task and CPU load task */
    TaskP_Handle hAppInitTask;

    /* Handle to task which run stack initialization main loop */
    TaskP_Handle hMainLoopTask;

    /* Handle to task which prints CPU load periodically */
    TaskP_Handle hCpuLoadTask;
} EnetApp_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t EnetApp_init(Enet_Type enetType);

static void EnetApp_deinit(void);

static void EnetApp_appInitTask(void *a0,
                                void *a1);

static void EnetApp_cpuLoadTask(void *a0,
                                void *a1);

#if defined(ENET_ENABLE_TIMESYNC)
void EnetApp_initTimeSyncPtp(Enet_Type enetType,
                                 Enet_MacPort macPort,
                                 const uint8_t *hostMacAddr,
                                 uint32_t ipAddr);

void EnetApp_deinitTimeSyncPtp(void);
#endif

extern void main_loop(void *a0,
                      void *a1);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint8_t gEnetAppInitTskStack[ENETAPP_TSK_STACK_APPINIT]
__attribute__ ((aligned(ENETAPP_TSK_STACK_APPINIT_ALIGN)));

static uint8_t gEnetAppMainTskStack[ENETAPP_TSK_STACK_MAIN]
__attribute__ ((aligned(ENETAPP_TSK_STACK_MAIN_ALIGN)));

static uint8_t gEnetAppLoadTskStack[ENETAPP_TSK_STACK_CPU_LOAD]
__attribute__ ((aligned(ENETAPP_TSK_STACK_CPU_LOAD_ALIGN)));

#if defined(SAFERTOS)
static sys_sem_t gEnetAppMainLoopSemObj;
#endif

static EnetApp_Cfg gEnetAppCfg =
{
    .useDfltFlow    = true,
    .useTimeSyncPtp = false,
};

static EnetApp_Obj gEnetAppObj =
{
    .hMcmCmdIf =
    {
        [ENET_ICSSG_DUALMAC] = {.hMboxCmd = NULL, .hMboxResponse = NULL},
        [ENET_ICSSG_SWITCH]  = {.hMboxCmd = NULL, .hMboxResponse = NULL},
        [ENET_GMAC_3G] = {.hMboxCmd = NULL, .hMboxResponse = NULL},
        [ENET_CPSW_2G] = {.hMboxCmd = NULL, .hMboxResponse = NULL},
        [ENET_CPSW_5G] = {.hMboxCmd = NULL, .hMboxResponse = NULL},
        [ENET_CPSW_9G] = {.hMboxCmd = NULL, .hMboxResponse = NULL},
    },

    .hAppInitTask  = NULL,
    .hMainLoopTask = NULL,
    .hCpuLoadTask  = NULL,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    TaskP_Params params;

    OS_init();

    /* Create task to print CPU load periodically */
    TaskP_Params_init(&params);
    params.name      = (uint8_t *)"App_Init";
    params.priority  = DEFAULT_THREAD_PRIO;
    params.stack     = gEnetAppInitTskStack;
    params.stacksize = sizeof(gEnetAppInitTskStack);

    gEnetAppObj.hAppInitTask = TaskP_create(&EnetApp_appInitTask, &params);
    if (gEnetAppObj.hAppInitTask == NULL)
    {
        EnetAppUtils_print("Failed to create app initialization task\n");
        EnetAppUtils_assert(false);
    }

    OS_start();    /* does not return */

    return(0);
}

static void EnetApp_appInitTask(void *a0,
                                void *a1)
{
    TaskP_Params params;
    int32_t status;

    EnetBoard_init();

    EnetAppUtils_print("==========================\n");
    EnetAppUtils_print("      Enet lwIP App       \n");
    EnetAppUtils_print("==========================\n");

    EnetApp_getTestConfig(&gEnetAppCfg.enetType,
                          &gEnetAppCfg.instId,
                          &gEnetAppCfg.ethPorts[0U],
                          &gEnetAppCfg.numEthPorts,
                          &gEnetAppCfg.useTimeSyncPtp);

    EnetAppUtils_enableClocks(gEnetAppCfg.enetType, gEnetAppCfg.instId);

    status = EnetBoard_setupPorts(gEnetAppCfg.enetType,
                                  gEnetAppCfg.instId,
                                  &gEnetAppCfg.ethPorts[0U],
                                  gEnetAppCfg.numEthPorts);
    EnetAppUtils_assert(status == ENET_SOK);

    /* Create task to print CPU load periodically */
    TaskP_Params_init(&params);
    params.name      = (const char *)"CPU_LOAD";
    params.priority  = 15U;
    params.stack     = gEnetAppLoadTskStack;
    params.stacksize = sizeof(gEnetAppLoadTskStack);

    gEnetAppObj.hCpuLoadTask = TaskP_create(&EnetApp_cpuLoadTask, &params);
    if (gEnetAppObj.hCpuLoadTask == NULL)
    {
        EnetAppUtils_print("Failed to create CPU load task\n");
        EnetAppUtils_assert(false);
    }

    /* Create main loop where lwIP is initialized */
    TaskP_Params_init(&params);
    params.name = (const char *)"Main Loop";
    params.priority  = DEFAULT_THREAD_PRIO;
    params.stack     = gEnetAppMainTskStack;
    params.stacksize = sizeof(gEnetAppMainTskStack);
#if defined(SAFERTOS)
    params.userData = &gEnetAppMainLoopSemObj;
#endif

    gEnetAppObj.hMainLoopTask = TaskP_create(&main_loop, &params);
    if (gEnetAppObj.hMainLoopTask == NULL)
    {
        EnetAppUtils_print("Failed to create main loop task\n");
        EnetAppUtils_assert(false);
    }
}

void EnetApp_initAleConfig(CpswAle_Cfg *aleCfg)
{
    aleCfg->modeFlags = CPSW_ALE_CFG_MODULE_EN;

    aleCfg->agingCfg.autoAgingEn     = true;
    aleCfg->agingCfg.agingPeriodInMs = 1000;

    aleCfg->nwSecCfg.vid0ModeEn = true;

    aleCfg->vlanCfg.aleVlanAwareMode           = FALSE;
    aleCfg->vlanCfg.cpswVlanAwareMode          = FALSE;
    aleCfg->vlanCfg.unknownUnregMcastFloodMask = CPSW_ALE_ALL_PORTS_MASK;
    aleCfg->vlanCfg.unknownRegMcastFloodMask   = CPSW_ALE_ALL_PORTS_MASK;
    aleCfg->vlanCfg.unknownVlanMemberListMask  = CPSW_ALE_ALL_PORTS_MASK;

    aleCfg->policerGlobalCfg.policingEn         = true;
    aleCfg->policerGlobalCfg.yellowDropEn       = false;
    aleCfg->policerGlobalCfg.redDropEn          = false;
    aleCfg->policerGlobalCfg.policerNoMatchMode = CPSW_ALE_POLICER_NOMATCH_MODE_GREEN;
}

void EnetApp_initLinkArgs(EnetPer_PortLinkCfg *linkArgs,
                          Enet_MacPort macPort)
{
    EnetPhy_Cfg *phyCfg = &linkArgs->phyCfg;
    EnetMacPort_LinkCfg *linkCfg = &linkArgs->linkCfg;
    EnetMacPort_Interface *mii = &linkArgs->mii;
    const EnetBoard_EthPort *ethPort = NULL;
    const EnetBoard_PortCfg *portCfg;
    int32_t status;
    uint32_t i;

    /* Setup board for requested Ethernet port */
    for (i = 0U; i < gEnetAppCfg.numEthPorts; i++)
    {
        if (gEnetAppCfg.ethPorts[i].macPort == macPort)
        {
            ethPort = &gEnetAppCfg.ethPorts[i];
        }
    }

    if (ethPort == NULL)
    {
        EnetAppUtils_print("MAC port %u is not enabled in the test\n", ENET_MACPORT_ID(macPort));
        EnetAppUtils_assert(false);
    }

    if (Enet_isCpswFamily(gEnetAppCfg.enetType))
    {
        CpswMacPort_Cfg *macCfg = (CpswMacPort_Cfg *)linkArgs->macCfg;
        CpswMacPort_initCfg(macCfg);
    }
#if defined(ENET_ENABLE_ICSSG)
    else
    {
        IcssgMacPort_Cfg *macCfg = (IcssgMacPort_Cfg *)linkArgs->macCfg;

        IcssgMacPort_initCfg(macCfg);
        macCfg->specialFramePrio = 1U;
    }
#endif

    portCfg = EnetBoard_getPortCfg(gEnetAppCfg.enetType, gEnetAppCfg.instId, ethPort);
    if (portCfg != NULL)
    {
        EnetPhy_initCfg(phyCfg);
        phyCfg->phyAddr     = portCfg->phyCfg.phyAddr;
        phyCfg->isStrapped  = portCfg->phyCfg.isStrapped;
        phyCfg->loopbackEn  = false;
        phyCfg->skipExtendedCfg = portCfg->phyCfg.skipExtendedCfg;
        phyCfg->extendedCfgSize = portCfg->phyCfg.extendedCfgSize;
        memcpy(phyCfg->extendedCfg, portCfg->phyCfg.extendedCfg, phyCfg->extendedCfgSize);

        *linkCfg = portCfg->linkCfg;
    }
    else
    {
        EnetAppUtils_print("No port configuration found for MAC port %u\n",
                           ENET_MACPORT_ID(macPort));
        EnetAppUtils_assert(false);
    }

    mii->layerType     = ethPort->mii.layerType;
    mii->sublayerType  = ethPort->mii.sublayerType;
    mii->variantType   = ENET_MAC_VARIANT_FORCED;

    if (Enet_isCpswFamily(gEnetAppCfg.enetType))
    {
        CpswMacPort_Cfg *macCfg = (CpswMacPort_Cfg *)linkArgs->macCfg;

        macCfg->sgmiiMode = portCfg->sgmiiMode;
    }
}

static void EnetApp_portLinkStatusChangeCb(Enet_MacPort macPort,
                                           bool isLinkUp,
                                           void *appArg)
{
    EnetAppUtils_print("MAC Port %u: link %s\n",
                       ENET_MACPORT_ID(macPort), isLinkUp ? "up" : "down");
}

static void EnetApp_mdioLinkStatusChange(Cpsw_MdioLinkStateChangeInfo *info,
                                         void *appArg)
{
    static uint32_t linkUpCount = 0;
    if ((info->linkChanged) && (info->isLinked))
    {
        linkUpCount++;
    }
}

static void EnetApp_initEnetLinkCbPrms(Cpsw_Cfg *cpswCfg)
{

    cpswCfg->mdioLinkStateChangeCb     = EnetApp_mdioLinkStatusChange;
    cpswCfg->mdioLinkStateChangeCbArg  = &gEnetAppObj;

    cpswCfg->portLinkStatusChangeCb    = &EnetApp_portLinkStatusChangeCb;
    cpswCfg->portLinkStatusChangeCbArg = &gEnetAppObj;
}

static int32_t EnetApp_init(Enet_Type enetType)
{
    int32_t status = ENET_SOK;
    EnetMcm_InitConfig enetMcmCfg;
    Cpsw_Cfg cpswCfg;
#if defined(ENET_ENABLE_ICSSG)
    Icssg_Cfg icssgCfg;
#endif
    EnetRm_ResCfg *resCfg;
    EnetUdma_Cfg dmaCfg;
    uint32_t i;

    EnetAppUtils_assert(gEnetAppCfg.numEthPorts <= Enet_getMacPortMax(gEnetAppCfg.enetType, gEnetAppCfg.instId));

    /* Open UDMA */
    gEnetAppObj.hUdmaDrv = EnetAppUtils_udmaOpen(gEnetAppCfg.enetType, NULL);
    EnetAppUtils_assert(NULL != gEnetAppObj.hUdmaDrv);

    dmaCfg.rxChInitPrms.dmaPriority = UDMA_DEFAULT_RX_CH_DMA_PRIORITY;
    dmaCfg.hUdmaDrv = gEnetAppObj.hUdmaDrv;

    /* Set configuration parameters */
    if (Enet_isCpswFamily(enetType))
    {
        cpswCfg.dmaCfg = (void *)&dmaCfg;

        Enet_initCfg(gEnetAppCfg.enetType, gEnetAppCfg.instId, &cpswCfg, sizeof(cpswCfg));
        cpswCfg.vlanCfg.vlanAware          = false;
        cpswCfg.hostPortCfg.removeCrc      = true;
        cpswCfg.hostPortCfg.padShortPacket = true;
        cpswCfg.hostPortCfg.passCrcErrors  = true;

        /* CPTS_RFT_CLK is sourced from MAIN_SYSCLK0 (500MHz) */
        cpswCfg.cptsCfg.cptsRftClkFreq = CPSW_CPTS_RFTCLK_FREQ_500MHZ;

        EnetApp_initEnetLinkCbPrms(&cpswCfg);
        resCfg = &cpswCfg.resCfg;

        EnetApp_initAleConfig(&cpswCfg.aleCfg);
        enetMcmCfg.perCfg = &cpswCfg;
    }
#if defined(ENET_ENABLE_ICSSG)
    else
    {
        Enet_initCfg(gEnetAppCfg.enetType, gEnetAppCfg.instId, &icssgCfg, sizeof(icssgCfg));

        /* Currently we only support one ICSSG port */
        EnetAppUtils_assert(gEnetAppCfg.numEthPorts == 1U);

        resCfg = &icssgCfg.resCfg;
        icssgCfg.dmaCfg = (void *)&dmaCfg;
        enetMcmCfg.perCfg = &icssgCfg;
    }
#endif

    EnetAppUtils_assert(NULL != enetMcmCfg.perCfg);
    EnetAppUtils_initResourceConfig(gEnetAppCfg.enetType, gEnetAppCfg.instId, EnetSoc_getCoreId(), resCfg);

    enetMcmCfg.enetType           = gEnetAppCfg.enetType;
    enetMcmCfg.instId             = gEnetAppCfg.instId;
    enetMcmCfg.setPortLinkCfg     = EnetApp_initLinkArgs;
    enetMcmCfg.numMacPorts        = gEnetAppCfg.numEthPorts;
    enetMcmCfg.periodicTaskPeriod = ENETPHY_FSM_TICK_PERIOD_MS;
    enetMcmCfg.print              = EnetAppUtils_print;

    for (i = 0U; i < gEnetAppCfg.numEthPorts; i++)
    {
        enetMcmCfg.macPortList[i] = gEnetAppCfg.ethPorts[i].macPort;
    }

    status = EnetMcm_init(&enetMcmCfg);

    return status;
}

void EnetApp_netIfCb(struct netif *netif)
{
    const ip4_addr_t *ipAddr;
#if defined(ENET_ENABLE_TIMESYNC)
    uint32_t addr;
#endif

    if (netif_is_up(netif))
    {
        ipAddr = netif_ip4_addr(netif);

        if (ipAddr->addr != 0)
        {
            EnetAppUtils_print("Enet lwIP App: Added Network IP address I/F %c%c%d: %s\n",
                               netif->name[0], netif->name[1], netif->num,
                               ip4addr_ntoa(ipAddr));

#if defined(ENET_ENABLE_TIMESYNC)
            if (gEnetAppCfg.useTimeSyncPtp)
            {
                addr = lwip_ntohl(ip_addr_get_ip4_u32(ipAddr));

                EnetApp_initTimeSyncPtp(gEnetAppCfg.enetType,
                                        gEnetAppCfg.ethPorts[0U].macPort,
                                        &gEnetAppObj.macAddr[0U],
                                        addr);
            }
#endif
        }
    }
    else
    {
        EnetAppUtils_print("Enet lwIP App: Removed Network IP address I/F %c%c%u\n",
                           netif->name[0], netif->name[1], netif->num);
#if defined(ENET_ENABLE_TIMESYNC)
        if (gEnetAppCfg.useTimeSyncPtp)
        {
            EnetApp_deinitTimeSyncPtp();
        }
#endif

        /* Deinit the app as it would be again initialized in LwipifEnetAppCb_getHandle */
        EnetApp_deinit();
    }
}

static bool EnetApp_isPortLinked(struct netif *netif,
                                 Enet_Handle hEnet)
{
    uint32_t coreId = EnetSoc_getCoreId();
    uint32_t i;
    bool isLinked = false;

    for (i = 0U; i < gEnetAppCfg.numEthPorts; i++)
    {
        isLinked = EnetAppUtils_isPortLinkUp(hEnet, coreId, gEnetAppCfg.ethPorts[i].macPort);
        if (isLinked)
        {
            break;
        }
    }

    return isLinked;
}

void LwipifEnetAppCb_getHandle(LwipifEnetAppIf_GetHandleInArgs *inArgs,
                               LwipifEnetAppIf_GetHandleOutArgs *outArgs)
{
    int32_t status;
    EnetMcm_HandleInfo handleInfo;
    EnetPer_AttachCoreOutArgs attachInfo;
    LwipifEnetAppIf_RxHandleInfo *rxInfo;
    LwipifEnetAppIf_RxConfig *rxCfg;
    EnetMcm_CmdIf *pMcmCmdIf = &gEnetAppObj.hMcmCmdIf[gEnetAppCfg.enetType];
    EnetUdma_OpenRxFlowPrms enetRxFlowCfg;
    EnetUdma_OpenTxChPrms enetTxChCfg;
    bool useRingMon = false;
    bool useDfltFlow = gEnetAppCfg.useDfltFlow;
    uint32_t coreId = EnetSoc_getCoreId();

    if (pMcmCmdIf->hMboxCmd == NULL)
    {
        status = EnetApp_init(gEnetAppCfg.enetType);
        if (status != ENET_SOK)
        {
            EnetAppUtils_print("Failed to open Enet app: %d\n", status);
            EnetAppUtils_assert(status == ENET_SOK);
        }

        EnetMcm_getCmdIf(gEnetAppCfg.enetType, pMcmCmdIf);
    }

    EnetAppUtils_assert(pMcmCmdIf->hMboxCmd != NULL);
    EnetAppUtils_assert(pMcmCmdIf->hMboxResponse != NULL);
    EnetMcm_acquireHandleInfo(pMcmCmdIf, &handleInfo);
    EnetMcm_coreAttach(pMcmCmdIf, coreId, &attachInfo);

    /* Confirm HW checksum offload is enabled when LWIP chksum offload is enabled */
    if (Enet_isCpswFamily(gEnetAppCfg.enetType))
    {
        Enet_IoctlPrms prms;
        bool csumOffloadFlg;

        ENET_IOCTL_SET_OUT_ARGS(&prms, &csumOffloadFlg);
        status = Enet_ioctl(handleInfo.hEnet,
                            coreId,
                            ENET_HOSTPORT_IS_CSUM_OFFLOAD_ENABLED,
                            &prms);
        if (status != ENET_SOK)
        {
            EnetAppUtils_print("Failed to get checksum offload info: %d\n", status);
        }

        EnetAppUtils_assert(true == csumOffloadFlg);
    }

    /* Open TX channel */
    EnetDma_initTxChParams(&enetTxChCfg);
    EnetAppUtils_setCommonTxChPrms(&enetTxChCfg);

    enetTxChCfg.hUdmaDrv  = handleInfo.hUdmaDrv;
    enetTxChCfg.useProxy  = true;
    enetTxChCfg.numTxPkts = inArgs->txCfg.numPackets;
    enetTxChCfg.cbArg     = inArgs->txCfg.cbArg;
    enetTxChCfg.notifyCb  = inArgs->txCfg.notifyCb;

    EnetAppUtils_openTxCh(handleInfo.hEnet,
                          attachInfo.coreKey,
                          coreId,
                          &outArgs->txInfo.txChNum,
                          &outArgs->txInfo.hTxChannel,
                          &enetTxChCfg);

    /* Open first RX channel/flow */
    rxInfo = &outArgs->rxInfo[0U];
    rxCfg = &inArgs->rxCfg[0U];

    EnetDma_initRxChParams(&enetRxFlowCfg);
    EnetAppUtils_setCommonRxFlowPrms(&enetRxFlowCfg);
    enetRxFlowCfg.notifyCb  = rxCfg->notifyCb;
    enetRxFlowCfg.numRxPkts = rxCfg->numPackets;
    enetRxFlowCfg.cbArg     = rxCfg->cbArg;
    enetRxFlowCfg.hUdmaDrv  = handleInfo.hUdmaDrv;
    enetRxFlowCfg.useProxy  = true;

    /* Use ring monitor for the CQ ring of RX flow */
    EnetUdma_UdmaRingPrms *pFqRingPrms = &enetRxFlowCfg.udmaChPrms.fqRingPrms;
    pFqRingPrms->useRingMon = useRingMon;
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

#if defined(ENET_ENABLE_ICSSG)
    if(Enet_isIcssFamily(gEnetAppCfg.enetType))
    {
        enetRxFlowCfg.flowPrms.sizeThreshEn = 0U;
    }
#endif

    EnetAppUtils_openRxFlow(gEnetAppCfg.enetType,
                            handleInfo.hEnet,
                            attachInfo.coreKey,
                            coreId,
                            useDfltFlow,
                            &rxInfo->rxFlowStartIdx,
                            &rxInfo->rxFlowIdx,
                            &rxInfo->macAddr[0U],
                            &rxInfo->hRxFlow,
                            &enetRxFlowCfg);

    outArgs->coreId          = coreId;
    outArgs->coreKey         = attachInfo.coreKey;
    outArgs->hEnet           = handleInfo.hEnet;
    outArgs->hostPortRxMtu   = attachInfo.rxMtu;
    ENET_UTILS_ARRAY_COPY(outArgs->txMtu, attachInfo.txMtu);
    outArgs->print           = &EnetAppUtils_print;
    outArgs->isPortLinkedFxn = &EnetApp_isPortLinked;
    outArgs->timerPeriodUs   = ENETAPP_PACKET_POLL_PERIOD_US;

    outArgs->hUdmaDrv = handleInfo.hUdmaDrv;
    rxInfo->disableEvent = !useRingMon;
    outArgs->txInfo.txPortNum = ENET_MAC_PORT_INV;
    /* Use optimized processing where TX packets are relinquished in next TX submit call */
    outArgs->txInfo.disableEvent = true;

    EnetAppUtils_print("Host MAC address: ");
    EnetAppUtils_printMacAddr(&rxInfo->macAddr[0U]);

    EnetUtils_copyMacAddr(&gEnetAppObj.macAddr[0U], &rxInfo->macAddr[0U]);

#if defined(ENET_ENABLE_ICSSG)
    /* Add port MAC entry in case of ICSSG dual MAC */
    if (ENET_ICSSG_DUALMAC == gEnetAppCfg.enetType)
    {
        Enet_IoctlPrms prms;
        IcssgMacPort_SetMacAddressInArgs inArgs;

        memset(&inArgs, 0, sizeof(inArgs));
        memcpy(&inArgs.macAddr[0U], &rxInfo->macAddr[0U], sizeof(inArgs.macAddr));
        inArgs.macPort = gEnetAppCfg.macPort;

        ENET_IOCTL_SET_IN_ARGS(&prms, &inArgs);
        status = Enet_ioctl(handleInfo.hEnet, coreId, ICSSG_MACPORT_IOCTL_SET_MACADDR, &prms);
        if (status != ENET_SOK)
        {
            EnetAppUtils_print("Failed to set MAC address: %d\n", status);
            EnetAppUtils_assert(status == ENET_SOK);
        }
    }
#endif

    rxInfo->handlePktFxn = NULL;
}

void LwipifEnetAppCb_releaseHandle(LwipifEnetAppIf_ReleaseHandleInfo *releaseInfo)
{
    EnetMcm_CmdIf *pMcmCmdIf = &gEnetAppObj.hMcmCmdIf[gEnetAppCfg.enetType];
    Lwip2EnetAppIf_FreePktInfo *freePktInfo;
    EnetDma_PktQ fqPktInfoQ;
    EnetDma_PktQ cqPktInfoQ;
    LwipifEnetAppIf_RxHandleInfo *rxInfo;
    bool useDfltFlow = gEnetAppCfg.useDfltFlow;

    EnetAppUtils_assert(pMcmCmdIf->hMboxCmd != NULL);
    EnetAppUtils_assert(pMcmCmdIf->hMboxResponse != NULL);

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
    freePktInfo = &releaseInfo->rxFreePkt[0U];

    EnetQueue_initQ(&fqPktInfoQ);
    EnetQueue_initQ(&cqPktInfoQ);

    rxInfo = &releaseInfo->rxInfo[0U];
    EnetAppUtils_closeRxFlow(gEnetAppCfg.enetType,
                             releaseInfo->hEnet,
                             releaseInfo->coreKey,
                             releaseInfo->coreId,
                             useDfltFlow,
                             &fqPktInfoQ,
                             &cqPktInfoQ,
                             rxInfo->rxFlowStartIdx,
                             rxInfo->rxFlowIdx,
                             rxInfo->macAddr,
                             rxInfo->hRxFlow);

    freePktInfo->cb(freePktInfo->cbArg, &fqPktInfoQ, &cqPktInfoQ);

    EnetMcm_coreDetach(pMcmCmdIf, releaseInfo->coreId, releaseInfo->coreKey);
    EnetMcm_releaseHandleInfo(pMcmCmdIf);
}

static void EnetApp_deinit(void)
{
    EnetAppUtils_udmaclose(gEnetAppObj.hUdmaDrv);
    EnetMcm_deInit(gEnetAppCfg.enetType);
    memset(&gEnetAppObj, 0U, sizeof(gEnetAppObj));
}

static void EnetApp_cpuLoadTask(void *a0,
                                void *a1)
{
    volatile uint32_t enableLoad = 1U;

    while (enableLoad)
    {
        /* LoadP_getCPULoad() and LoadP_reset() currently supported only for FreeRTOS */
#if defined(FREERTOS)
        EnetAppUtils_print("CPU Load: %u%%\n", LoadP_getCPULoad());
        LoadP_reset();
#endif
        TaskP_sleep(10000U);
    }
}

/* PTP related functions */

#if defined(ENET_ENABLE_TIMESYNC)
void EnetApp_initTimeSyncPtp(Enet_Type enetType,
                                 Enet_MacPort macPort,
                                 const uint8_t *hostMacAddr,
                                 uint32_t ipAddr)
{
    TimeSyncPtp_Config ptpCfg;

    /* Initialize and enable PTP stack */
    TimeSyncPtp_setDefaultPtpConfig(&ptpCfg);
    ptpCfg.vlanCfg.vlanType     = TIMESYNC_VLAN_TYPE_NONE;
    ptpCfg.deviceMode           = TIMESYNC_ORDINARY_CLOCK;
    ptpCfg.portMask             = ENET_MACPORT_MASK(macPort);

    EnetApp_getTimeSyncSocCfg(enetType, gEnetAppCfg.instId, &ptpCfg.socConfig);

    /* PPS is currently not enabled for ICSSG Dual-MAC */
    if (enetType == ENET_ICSSG_DUALMAC)
    {
        ptpCfg.processToDSync2PPS  = false;
    }

    ptpCfg.socConfig.instId = gEnetAppCfg.instId;

    /* Save host port IP address and MAC address */
    memcpy(&ptpCfg.ipAddr[0U], &ipAddr, ENET_IPv4_ADDR_LEN);
    memcpy(&ptpCfg.ifMacID[0U], hostMacAddr, ENET_MAC_ADDR_LEN);

    gEnetAppObj.hTimeSyncPtp = TimeSyncPtp_init(&ptpCfg);
    EnetAppUtils_assert(gEnetAppObj.hTimeSyncPtp != NULL);

    TimeSyncPtp_enable(gEnetAppObj.hTimeSyncPtp);
    EnetAppUtils_print("TimeSync PTP enabled\n");
}

void EnetApp_deinitTimeSyncPtp(void)
{
    if (gEnetAppObj.hTimeSyncPtp != NULL)
    {
        TimeSyncPtp_disable(gEnetAppObj.hTimeSyncPtp);

        /* ETHFW-1767 - TimeSync PTP doesn't support deinit */
        //TimeSyncPtp_deInit(gEnetAppObj.hTimeSyncPtp);
    }
}
#endif
