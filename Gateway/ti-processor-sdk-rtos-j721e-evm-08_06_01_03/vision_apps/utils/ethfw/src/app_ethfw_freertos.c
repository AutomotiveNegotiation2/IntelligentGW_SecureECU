/*
 *
 * Copyright (c) 2020 Texas Instruments Incorporated
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

#include "app_ethfw_priv.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined(SAFERTOS)
#define ETHAPP_LWIP_TASK_STACKSIZE      (16U * 1024U)
#define ETHAPP_LWIP_TASK_STACKALIGN     ETHAPP_LWIP_TASK_STACKSIZE
#else
#define ETHAPP_LWIP_TASK_STACKSIZE      (4U * 1024U)
#define ETHAPP_LWIP_TASK_STACKALIGN     (32U)
#endif

static uint8_t gEthAppLwipStackBuf[ETHAPP_LWIP_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__((aligned(ETHAPP_LWIP_TASK_STACKALIGN)));

/* lwIP features that EthFw relies on */
#ifndef LWIP_IPV4
#error "LWIP_IPV4 is not enabled"
#endif
#ifndef LWIP_NETIF_STATUS_CALLBACK
#error "LWIP_NETIF_STATUS_CALLBACK is not enabled"
#endif
#ifndef LWIP_NETIF_LINK_CALLBACK
#error "LWIP_NETIF_LINK_CALLBACK is not enabled"
#endif

/* DHCP or static IP */
#define ETHAPP_LWIP_USE_DHCP            (1)
#if !ETHAPP_LWIP_USE_DHCP
#define ETHFW_SERVER_IPADDR(addr)       IP4_ADDR((addr), 192,168,1,200)
#define ETHFW_SERVER_GW(addr)           IP4_ADDR((addr), 192,168,1,1)
#define ETHFW_SERVER_NETMASK(addr)      IP4_ADDR((addr), 255,255,255,0)
#endif

/* BridgeIf configuration parameters */
#define ETHAPP_LWIP_BRIDGE_MAX_PORTS (4U)
#define ETHAPP_LWIP_BRIDGE_MAX_DYNAMIC_ENTRIES (32U)
#define ETHAPP_LWIP_BRIDGE_MAX_STATIC_ENTRIES (8U)

/* BridgeIf port IDs
 * Used for creating CoreID to Bridge PortId Map
 */
#define ETHAPP_BRIDGEIF_PORT1_ID        (1U)
#define ETHAPP_BRIDGEIF_PORT2_ID        (2U)
#define ETHAPP_BRIDGEIF_CPU_PORT_ID     BRIDGEIF_MAX_PORTS

/* Inter-core netif IDs */
#define ETHAPP_NETIF_IC_MCU2_0_MCU2_1_IDX   (0U)
#define ETHAPP_NETIF_IC_MCU2_0_A72_IDX      (1U)
#define ETHAPP_NETIF_IC_MAX_IDX             (2U)

/* Max length of shared mcast address list */
#define ETHAPP_MAX_SHARED_MCAST_ADDR        (8U)

/* Required size of the MAC address pool (specific to the TI EVM configuration):
 *  1 x MAC address for Ethernet Firmware
 *  2 x MAC address for mpu1_0 virtual switch and MAC-only ports (Linux, 1 for QNX)
 *  2 x MAC address for mcu2_1 virtual switch and MAC-only ports (RTOS)
 *  1 x MAC address for mcu2_1 virtual switch port (AUTOSAR) */
#define ETHAPP_MAC_ADDR_POOL_SIZE           (6U)

static EthAppObj gEthAppObj =
{
    .enetType = ENET_CPSW_9G,
    .hEthFw = NULL,
    .hUdmaDrv = NULL,
    .instId   = 0U,
};

static Enet_MacPort gEthAppPorts[] =
{
#if defined(SOC_J721E)
    /* On J721E EVM to use all 8 ports simultaneously, we use below configuration
       RGMII Ports - 1,3,4,8. QSGMII ports - 2,5,6,7 */
    ENET_MAC_PORT_1, /* RGMII */
    ENET_MAC_PORT_3, /* RGMII */
    ENET_MAC_PORT_4, /* RGMII */
    ENET_MAC_PORT_8, /* RGMII */
#if defined(ENABLE_QSGMII_PORTS)
    ENET_MAC_PORT_2, /* QSGMII main */
    ENET_MAC_PORT_5, /* QSGMII sub */
    ENET_MAC_PORT_6, /* QSGMII sub */
    ENET_MAC_PORT_7, /* QSGMII sub */
#endif
#elif defined(SOC_J784S4)
    ENET_MAC_PORT_1, /* QSGMII main */
    ENET_MAC_PORT_3, /* QSGMII sub */
    ENET_MAC_PORT_4, /* QSGMII sub */
    ENET_MAC_PORT_5, /* QSGMII sub */
#endif
};

static EthFw_VirtPortCfg gEthApp_virtPortCfg[] =
{
    {
        .remoteCoreId = IPC_MPU1_0,
        .portId       = ETHREMOTECFG_SWITCH_PORT_0,
    },
    {
        .remoteCoreId = IPC_MCU2_1,
        .portId       = ETHREMOTECFG_SWITCH_PORT_1,
    },
    {
        .remoteCoreId = IPC_MPU1_0,
        .portId       = ETHREMOTECFG_MAC_PORT_1,
    },
    {
        .remoteCoreId = IPC_MCU2_1,
        .portId       = ETHREMOTECFG_MAC_PORT_4,
    },
};

static EthFw_VirtPortCfg gEthApp_autosarVirtPortCfg[] =
{
    {
        .remoteCoreId = IPC_MCU2_1,
        .portId       = ETHREMOTECFG_SWITCH_PORT_1,
    },
};

#if defined(SAFERTOS)
static sys_sem_t gEthApp_lwipMainTaskSemObj;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void EthApp_lwipMain(void *a0,
                            void *a1);

static void EthApp_initLwip(void *arg);

static void EthApp_initNetif(void);

static void EthApp_netifStatusCb(struct netif *netif);

static int32_t EthApp_initEthFw(void);

static void EthApp_startSwInterVlan(char *recvBuff,
                                    char *sendBuff);

static void EthApp_startHwInterVlan(char *recvBuff,
                                    char *sendBuff);

#if defined(ETHAPP_ENABLE_INTERCORE_ETH)
static void EthApp_filterAddMacSharedCb(const uint8_t *mac_address,
                                        const uint8_t hostId);

static void EthApp_filterDelMacSharedCb(const uint8_t *mac_address,
                                        const uint8_t hostId);

/* Array to store coreId to lwip bridge portId map */
static uint8_t gEthApp_lwipBridgePortIdMap[IPC_MAX_PROCS];

/* Shared multicast address table */
typedef struct
{
    /*! Shared Mcast address */
    uint8_t macAddr[ENET_MAC_ADDR_LEN];
    /*! lwIP Bridge port mask */
    bridgeif_portmask_t portMask;
} EthApp_SharedMcastAddrTable;

/* Must not exceed ETHAPP_MAX_SHARED_MCAST_ADDR entries */
static EthApp_SharedMcastAddrTable gEthApp_sharedMcastAddrTable[] =
{
    {
        /* MCast IP ADDR: 224.0.0.1 */
        .macAddr = {0x01,0x00,0x5E,0x00,0x00,0x01},
        .portMask= 0U,
    },
    {
        /* MCast IP ADDR: 224.0.0.251 */
        .macAddr = {0x01,0x00,0x5E,0x00,0x00,0xFB},
        .portMask= 0U,
    },
    {
        /* MCast IP ADDR: 224.0.0.252 */
        .macAddr = {0x01,0x00,0x5E,0x00,0x00,0xFC},
        .portMask= 0U,
    },
    {
        .macAddr = {0x33,0x33,0x00,0x00,0x00,0x01},
        .portMask= 0U,
    },
    {
        .macAddr = {0x33,0x33,0xFF,0x1D,0x92,0xC2},
        .portMask= 0U,
    },
    {
        .macAddr = {0x01,0x80,0xC2,0x00,0x00,0x00},
        .portMask= 0U,
    },
    {
        .macAddr = {0x01,0x80,0xC2,0x00,0x00,0x03},
        .portMask= 0U,
    },
};
#endif

/* List of multicast addresses reserved for EthFw. Currently, this list is populated
 * only with PTP related multicast addresses which are used by the test PTP stack
 * used by EthFw.
 * Note: Must not exceed ETHFW_RSVD_MCAST_LIST_LEN */
static uint8_t gEthApp_rsvdMcastAddrTable[][ENET_MAC_ADDR_LEN] =
{
    /* PTP - Peer delay messages */
    {
        0x01, 0x80, 0xc2, 0x00, 0x00, 0x0E,
    },
    /* PTP - Non peer delay messages */
    {
        0x01, 0x1b, 0x19, 0x00, 0x00, 0x00,
    },
};

static struct netif netif;
#if defined(ETHAPP_ENABLE_INTERCORE_ETH)
static struct netif netif_ic[ETHAPP_NETIF_IC_MAX_IDX];

static uint32_t netif_ic_state[IC_ETH_MAX_VIRTUAL_IF] =
{
    IC_ETH_IF_MCU2_0_MCU2_1,
    IC_ETH_IF_MCU2_1_MCU2_0,
    IC_ETH_IF_MCU2_0_A72
};

static struct netif netif_bridge;
bridgeif_initdata_t bridge_initdata;
#endif /* ETHAPP_ENABLE_INTERCORE_ETH */
void appEthFwEarlyInit()
{
    SemaphoreP_Params semParams;

    /* Create semaphore used to synchronize EthFw and NDK init.
     * EthFw opens the CPSW driver which is required by NDK during NIMU
     * initialization, hence EthFw init must complete first.
     * Currently, there is no control over NDK initialization time and its
     * task runs right away after BIOS_start() hence causing a race
     * condition with EthFw init */
    SemaphoreP_Params_init(&semParams);
    semParams.mode = SemaphoreP_Mode_BINARY;
    gEthAppObj.hInitSem = SemaphoreP_create(0, &semParams);
}

int32_t appEthFwInit()
{
    int32_t status = ETHAPP_OK;
    uint32_t flags = 0U;

    appLogPrintf("ETHFW: Init ... !!!\n");

    gEthAppObj.coreId = EnetSoc_getCoreId();

    /* Board related initialization */
#if defined(SOC_J721E)
    flags |= ETHFW_BOARD_GESI_ENABLE;
#if defined(ENABLE_QSGMII_PORTS)
    flags |= ETHFW_BOARD_QENET_ENABLE;
#endif
#elif defined(SOC_J784S4)
    flags |= (ETHFW_BOARD_QENET_ENABLE | ETHFW_BOARD_SERDES_CONFIG);
#endif

    /* Board related initialization */
    status = EthFwBoard_init(flags);
    if (status != ENET_SOK)
    {
        appLogPrintf("ETHFW: Board initialization failed\n");
    }

    /* Open UDMA driver */
    if (status == ENET_SOK)
    {
        gEthAppObj.hUdmaDrv = appUdmaGetObj();
        if (gEthAppObj.hUdmaDrv == NULL)
        {
            appLogPrintf("ETHFW: ERROR: failed to open UDMA driver\n");
            status = -1;
        }
    }

    /* Initialize Ethernet Firmware */
    if (status == ETHAPP_OK)
    {
        status = EthApp_initEthFw();
    }

    /* Initialize lwIP */
    if (status == ENET_SOK)
    {
        TaskP_Params taskParams;

        TaskP_Params_init(&taskParams);
        taskParams.priority  = DEFAULT_THREAD_PRIO;
        taskParams.stack     = &gEthAppLwipStackBuf[0];
        taskParams.stacksize = sizeof(gEthAppLwipStackBuf);
        taskParams.name      = "lwIP main loop";
#if defined(SAFERTOS)
        taskParams.userData  = &gEthApp_lwipMainTaskSemObj;
#endif

        TaskP_create(&EthApp_lwipMain, &taskParams);
    }

    if (status == ETHAPP_OK)
    {
        appLogPrintf("ETHFW: Init ... DONE !!!\n");
    }
    else
    {
        appLogPrintf("ETHFW: Init ... ERROR !!!\n");
    }


    return status;
}

int32_t appEthFwDeInit()
{
    int32_t status = 0;

    EthFw_deinit(gEthAppObj.hEthFw);

    return status;
}

int32_t appEthFwRemoteServerInit()
{
    int32_t status;

    appLogPrintf("ETHFW: Remove server Init ... !!!\n");

    /* Initialize the Remote Config server (CPSW Proxy Server) */
    status = EthFw_initRemoteConfig(gEthAppObj.hEthFw);
    if (status != ENET_SOK)
    {
        appLogPrintf("ETHFW: Remove server Init ... ERROR (%d) !!! \n", status);
    }
    else
    {
        appLogPrintf("ETHFW: Remove server Init ... DONE !!!\n");
    }

    return status;
}

void LwipifEnetAppCb_getHandle(LwipifEnetAppIf_GetHandleInArgs *inArgs,
                               LwipifEnetAppIf_GetHandleOutArgs *outArgs)
{
    /* Wait for EthFw to be initialized */
    SemaphoreP_pend(gEthAppObj.hInitSem, SemaphoreP_WAIT_FOREVER);

    EthFwCallbacks_lwipifCpswGetHandle(inArgs, outArgs);

    /* Save host port MAC address */
    EnetUtils_copyMacAddr(&gEthAppObj.hostMacAddr[0U],
                          &outArgs->rxInfo[0U].macAddr[0U]);
}

void LwipifEnetAppCb_releaseHandle(LwipifEnetAppIf_ReleaseHandleInfo *releaseInfo)
{
    EthFwCallbacks_lwipifCpswReleaseHandle(releaseInfo);
}

static int32_t EthApp_initEthFw(void)
{
    EthFw_Version ver;
    EthFw_Config ethFwCfg;
    Cpsw_Cfg *cpswCfg = &ethFwCfg.cpswCfg;
    EnetUdma_Cfg dmaCfg;
    EnetRm_MacAddressPool *pool = &cpswCfg->resCfg.macList;
    uint32_t poolSize;
    int32_t status = ETHAPP_OK;
    int32_t i;

    /* Set EthFw config params */
    EthFw_initConfigParams(gEthAppObj.enetType, &ethFwCfg);

    dmaCfg.rxChInitPrms.dmaPriority = UDMA_DEFAULT_RX_CH_DMA_PRIORITY;
    dmaCfg.hUdmaDrv = gEthAppObj.hUdmaDrv;
    cpswCfg->dmaCfg = (void *)&dmaCfg;

    /* Populate MAC address pool */
    poolSize = EnetUtils_min(ENET_ARRAYSIZE(pool->macAddress), ETHAPP_MAC_ADDR_POOL_SIZE);
    pool->numMacAddress = EthFwBoard_getMacAddrPool(pool->macAddress, poolSize);

    /* Set hardware port configuration parameters */
    ethFwCfg.ports = &gEthAppPorts[0];
    ethFwCfg.numPorts = ARRAY_SIZE(gEthAppPorts);
    ethFwCfg.setPortCfg = EthFwBoard_setPortCfg;

    /* Set virtual port configuration parameters */
    ethFwCfg.virtPortCfg  = &gEthApp_virtPortCfg[0];
    ethFwCfg.numVirtPorts = ARRAY_SIZE(gEthApp_virtPortCfg);

    /* Set AUTOSAR virtual port configuration parameters */
    ethFwCfg.autosarVirtPortCfg  = &gEthApp_autosarVirtPortCfg[0];
    ethFwCfg.numAutosarVirtPorts = ARRAY_SIZE(gEthApp_autosarVirtPortCfg);

    /* CPTS_RFT_CLK is sourced from MAIN_SYSCLK0 (500MHz) */
    cpswCfg->cptsCfg.cptsRftClkFreq = CPSW_CPTS_RFTCLK_FREQ_500MHZ;

    /* Overwrite config params with those for hardware interVLAN */
    EthHwInterVlan_setOpenPrms(&ethFwCfg.cpswCfg);

#if defined(ETHAPP_ENABLE_INTERCORE_ETH)
    if (ARRAY_SIZE(gEthApp_sharedMcastAddrTable) > ETHAPP_MAX_SHARED_MCAST_ADDR)
    {
        appLogPrintf("ETHFW error: No. of shared mcast addr cannot exceed %d\n",
                    ETHAPP_MAX_SHARED_MCAST_ADDR);
        status = ETHAPP_ERROR;
    }
    else
    {
        for (i = 0U; i < ARRAY_SIZE(gEthApp_sharedMcastAddrTable); i++)
        {
            EnetUtils_copyMacAddr(&ethFwCfg.sharedMcastCfg.macAddrList[i][0],
                                  &gEthApp_sharedMcastAddrTable[i].macAddr[0]);
        }

        ethFwCfg.sharedMcastCfg.numMacAddr = ARRAY_SIZE(gEthApp_sharedMcastAddrTable);
        ethFwCfg.sharedMcastCfg.filterAddMacSharedCb = EthApp_filterAddMacSharedCb;
        ethFwCfg.sharedMcastCfg.filterDelMacSharedCb = EthApp_filterDelMacSharedCb;
    }
#endif

    if (status == ETHAPP_OK)
    {
        if (ARRAY_SIZE(gEthApp_rsvdMcastAddrTable) > ETHFW_RSVD_MCAST_LIST_LEN)
        {
            appLogPrintf("ETHFW error: No. of rsvd mcast addr cannot exceed %d\n",
                         ETHFW_RSVD_MCAST_LIST_LEN);
            status = ETHAPP_ERROR;
        }
        else
        {
            for (i = 0U; i < ARRAY_SIZE(gEthApp_rsvdMcastAddrTable); i++)
            {
                EnetUtils_copyMacAddr(&ethFwCfg.rsvdMcastCfg.macAddrList[i][0],
                                      &gEthApp_rsvdMcastAddrTable[i][0]);
            }

            ethFwCfg.rsvdMcastCfg.numMacAddr = ARRAY_SIZE(gEthApp_rsvdMcastAddrTable);
        }
    }

    /* Initialize the EthFw */
    if (status == ETHAPP_OK)
    {
        gEthAppObj.hEthFw = EthFw_init(gEthAppObj.enetType, &ethFwCfg);
        if (gEthAppObj.hEthFw == NULL)
        {
            appLogPrintf("ETHFW: failed to initialize the firmware\n");
            status = ETHAPP_ERROR;
        }
    }

    /* Get and print EthFw version */
    if (status == ETHAPP_OK)
    {
        EthFw_getVersion(gEthAppObj.hEthFw, &ver);
        appLogPrintf("\nETHFW Version   : %d.%02d.%02d\n", ver.major, ver.minor, ver.rev);
        appLogPrintf("ETHFW Build Date: %s %s, %s\n", ver.month, ver.date, ver.year);
        appLogPrintf("ETHFW Build Time: %s:%s:%s\n", ver.hour, ver.min, ver.sec);
        appLogPrintf("ETHFW Commit SHA: %s\n\n", ver.commitHash);
    }

    /* Post semaphore so that lwip or NIMU/NDK can continue with their initialization */
    if (status == ETHAPP_OK)
    {
        SemaphoreP_post(gEthAppObj.hInitSem);
    }

    return status;
}

/* lwIP callbacks (exact name required) */

bool EthFwCallbacks_isPortLinked(struct netif *netif,
                                 Enet_Handle hEnet)
{
    bool linked = false;
    uint32_t i;

    /* Report port linked as long as any port owned by EthFw is up */
    for (i = 0U; (i < ARRAY_SIZE(gEthAppPorts)) && !linked; i++)
    {
        linked = EnetAppUtils_isPortLinkUp(hEnet,
                                           gEthAppObj.coreId,
                                           gEthAppPorts[i]);
    }

    return linked;
}

static void EthApp_lwipMain(void *a0,
                            void *a1)
{
    err_t err;
    sys_sem_t initSem;

    appUtilsTaskInit();

    /* initialize lwIP stack and network interfaces */
    err = sys_sem_new(&initSem, 0);
    LWIP_ASSERT("failed to create initSem", err == ERR_OK);
    LWIP_UNUSED_ARG(err);

    tcpip_init(EthApp_initLwip, &initSem);

    /* we have to wait for initialization to finish before
     * calling update_adapter()! */
    sys_sem_wait(&initSem);
    sys_sem_free(&initSem);

#if (LWIP_SOCKET || LWIP_NETCONN) && LWIP_NETCONN_SEM_PER_THREAD
    netconn_thread_init();
#endif
}

static void EthApp_initLwip(void *arg)
{
    sys_sem_t *initSem;

    LWIP_ASSERT("arg != NULL", arg != NULL);
    initSem = (sys_sem_t*)arg;

    /* init randomizer again (seed per thread) */
    srand((unsigned int)sys_now()/1000);

    /* init network interfaces */
    EthApp_initNetif();

    sys_sem_signal(initSem);
}

static void EthApp_initNetif(void)
{
    ip4_addr_t ipaddr, netmask, gw;
#if ETHAPP_LWIP_USE_DHCP
    err_t err;
#endif

    ip4_addr_set_zero(&gw);
    ip4_addr_set_zero(&ipaddr);
    ip4_addr_set_zero(&netmask);

#if ETHAPP_LWIP_USE_DHCP
    appLogPrintf("Starting lwIP, local interface IP is dhcp-enabled\n");
#else /* ETHAPP_LWIP_USE_DHCP */
    ETHFW_SERVER_GW(&gw);
    ETHFW_SERVER_IPADDR(&ipaddr);
    ETHFW_SERVER_NETMASK(&netmask);
    appLogPrintf("Starting lwIP, local interface IP is %s\n", ip4addr_ntoa(&ipaddr));
#endif /* ETHAPP_LWIP_USE_DHCP */

#if defined(ETHAPP_ENABLE_INTERCORE_ETH)
    /* Create Enet LLD ethernet interface */
    netif_add(&netif, NULL, NULL, NULL, NULL, LWIPIF_LWIP_init, tcpip_input);

    /* Create inter-core virtual ethernet interface: MCU2_0 <-> MCU2_1 */
    netif_add(&netif_ic[ETHAPP_NETIF_IC_MCU2_0_MCU2_1_IDX], NULL, NULL, NULL,
              (void*)&netif_ic_state[IC_ETH_IF_MCU2_0_MCU2_1],
              LWIPIF_LWIP_IC_init, tcpip_input);

    /* Create inter-core virtual ethernet interface: MCU2_0 <-> A72 */
    netif_add(&netif_ic[ETHAPP_NETIF_IC_MCU2_0_A72_IDX], NULL, NULL, NULL,
              (void*)&netif_ic_state[IC_ETH_IF_MCU2_0_A72],
              LWIPIF_LWIP_IC_init, tcpip_input);

    /* Create bridge interface */
    bridge_initdata.max_ports = ETHAPP_LWIP_BRIDGE_MAX_PORTS;
    bridge_initdata.max_fdb_dynamic_entries = ETHAPP_LWIP_BRIDGE_MAX_DYNAMIC_ENTRIES;
    bridge_initdata.max_fdb_static_entries = ETHAPP_LWIP_BRIDGE_MAX_STATIC_ENTRIES;
    EnetUtils_copyMacAddr(&bridge_initdata.ethaddr.addr[0U], &gEthAppObj.hostMacAddr[0U]);

    netif_add(&netif_bridge, &ipaddr, &netmask, &gw, &bridge_initdata, bridgeif_init, netif_input);

    /* Add all netifs to the bridge and create coreId to bridge portId map */
    bridgeif_add_port(&netif_bridge, &netif);
    gEthApp_lwipBridgePortIdMap[IPC_MCU2_0] = ETHAPP_BRIDGEIF_CPU_PORT_ID;

    bridgeif_add_port(&netif_bridge, &netif_ic[0]);
    gEthApp_lwipBridgePortIdMap[IPC_MCU2_1] = ETHAPP_BRIDGEIF_PORT1_ID;

    bridgeif_add_port(&netif_bridge, &netif_ic[1]);
    gEthApp_lwipBridgePortIdMap[IPC_MPU1_0] = ETHAPP_BRIDGEIF_PORT2_ID;

    /* Set bridge interface as the default */
    netif_set_default(&netif_bridge);
#else
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, LWIPIF_LWIP_init, tcpip_input);
    netif_set_default(&netif);
#endif

    netif_set_status_callback(netif_default, EthApp_netifStatusCb);

    dhcp_set_struct(netif_default, &gEthAppObj.dhcpNetif);

#if defined(ETHAPP_ENABLE_INTERCORE_ETH)
    netif_set_up(&netif);
    netif_set_up(&netif_ic[ETHAPP_NETIF_IC_MCU2_0_MCU2_1_IDX]);
    netif_set_up(&netif_ic[ETHAPP_NETIF_IC_MCU2_0_A72_IDX]);
    netif_set_up(&netif_bridge);
#else
    netif_set_up(netif_default);
#endif

#if ETHAPP_LWIP_USE_DHCP
    err = dhcp_start(netif_default);
    if (err != ERR_OK)
    {
        appLogPrintf("Failed to start DHCP: %d\n", err);
    }
#endif /* ETHAPP_LWIP_USE_DHCP */
}

static void EthApp_netifStatusCb(struct netif *netif)
{
    Enet_MacPort macPort = ENET_MAC_PORT_1;
    int32_t status;

    if (netif_is_up(netif))
    {
        const ip4_addr_t *ipAddr = netif_ip4_addr(netif);

        appLogPrintf("Added interface '%c%c%d', IP is %s\n",
                     netif->name[0], netif->name[1], netif->num, ip4addr_ntoa(ipAddr));

        if (ipAddr->addr != 0)
        {
            gEthAppObj.hostIpAddr = lwip_ntohl(ip_addr_get_ip4_u32(ipAddr));

            /* MAC port used for PTP */
            macPort = ENET_MAC_PORT_3;

            /* Initialize and enable PTP stack */
            EthFw_initTimeSyncPtp(gEthAppObj.hostIpAddr,
                                  &gEthAppObj.hostMacAddr[0U],
                                  ENET_BIT(ENET_MACPORT_NORM(macPort)));

            /* Assign functions that are to be called based on actions in GUI.
             * These cannot be dynamically pushed to function pointer array, as the
             * index is used in GUI as command */
            EnetCfgServer_fxn_table[9] = &EthApp_startSwInterVlan;
            EnetCfgServer_fxn_table[10] = &EthApp_startHwInterVlan;

            /* Start Configuration server */
            status = EnetCfgServer_init(gEthAppObj.enetType, gEthAppObj.instId);
            EnetAppUtils_assert(ENET_SOK == status);

            /* Start the software-based interVLAN routing */
            EthSwInterVlan_setupRouting(gEthAppObj.enetType, ETH_SWINTERVLAN_TASK_PRI);
        }
    }
    else
    {
        appLogPrintf("Removed interface '%c%c%d'\n", netif->name[0], netif->name[1], netif->num);
    }
}

/* Functions called from Config server library based on selection from GUI */

static void EthApp_startSwInterVlan(char *recvBuff,
                                    char *sendBuff)
{
    EnetCfgServer_InterVlanConfig *pInterVlanCfg;
    int32_t status;

    if (recvBuff != NULL)
    {
        pInterVlanCfg = (EnetCfgServer_InterVlanConfig *)recvBuff;
        status = EthSwInterVlan_addClassifierEntries(pInterVlanCfg);
        EnetAppUtils_assert(ENET_SOK == status);
    }
}

static void EthApp_startHwInterVlan(char *recvBuff,
                                    char *sendBuff)
{
    EnetCfgServer_InterVlanConfig *pInterVlanCfg;

    if (recvBuff != NULL)
    {
        pInterVlanCfg = (EnetCfgServer_InterVlanConfig *)recvBuff;
        EthHwInterVlan_setupRouting(gEthAppObj.enetType, pInterVlanCfg);
    }
}

#if defined(ETHAPP_ENABLE_INTERCORE_ETH)
/* Application callback function to handle addition of a shared mcast
 * address in the ALE */
static void EthApp_filterAddMacSharedCb(const uint8_t *mac_address,
                                        const uint8_t hostId)
{
    uint8_t idx = 0;
    bridgeif_portmask_t portMask;
    struct eth_addr ethaddr;
    bool matchFound = false;
    int32_t errVal = 0;

    /* Search the mac_address in the shared mcast addr table */
    for (idx = 0; idx < ARRAY_SIZE(gEthApp_sharedMcastAddrTable); idx++)
    {
        if (EnetUtils_cmpMacAddr(mac_address,
                    &gEthApp_sharedMcastAddrTable[idx].macAddr[0]))
        {
            matchFound = true;
            /* Read and update stored port mask */
            portMask = gEthApp_sharedMcastAddrTable[idx].portMask;
            portMask |= (0x01 << gEthApp_lwipBridgePortIdMap[hostId]);
            gEthApp_sharedMcastAddrTable[idx].portMask = portMask;

            /* Update bridge fdb entry for this mac_address */
            EnetUtils_copyMacAddr(&ethaddr.addr[0U], mac_address);

            /* There will be a delay between removing existing FDB entry
             * and adding the updated one. During this time, multicast
             * packets will be flodded to all the bridge ports
             */
            bridgeif_fdb_remove(&netif_bridge, &ethaddr);

            errVal = bridgeif_fdb_add(&netif_bridge,
                                      &ethaddr,
                                      gEthApp_sharedMcastAddrTable[idx].portMask);

            if (errVal)
            {
                appLogPrintf("addMacSharedCb: bridgeif_fdb_add failed (%d)\n", errVal);
            }

            /* The array should have unique mcast addresses,
             * so no other match is expected
             */
            break;
        }
    }

    if (!matchFound)
    {
        appLogPrintf("addMacSharedCb: Address not found\n");
    }
}

/* Application callback function to handle deletion of a shared mcast
 * address from the ALE */
static void EthApp_filterDelMacSharedCb(const uint8_t *mac_address,
                                        const uint8_t hostId)
{
    uint8_t idx = 0;
    bridgeif_portmask_t portMask;
    struct eth_addr ethaddr;
    bool matchFound = false;
    int32_t errVal = 0;

    /* Search the mac_address in the shared mcast addr table */
    for (idx = 0; idx < ARRAY_SIZE(gEthApp_sharedMcastAddrTable); idx++)
    {
        if (EnetUtils_cmpMacAddr(mac_address,
                    &gEthApp_sharedMcastAddrTable[idx].macAddr[0]))
        {
            matchFound = true;
            /* Read and update stored port mask */
            portMask = gEthApp_sharedMcastAddrTable[idx].portMask;
            portMask &= ~(0x01 << gEthApp_lwipBridgePortIdMap[hostId]);
            gEthApp_sharedMcastAddrTable[idx].portMask = portMask;

            /* Update bridge fdb entry for this mac_address */
            EnetUtils_copyMacAddr(&ethaddr.addr[0U], mac_address);

            /* There will be a delay between removing existing FDB entry
             * and adding the updated one. During this time, multicast
             * packets will be flodded to all the bridge ports
             */
            bridgeif_fdb_remove(&netif_bridge, &ethaddr);

            if (gEthApp_sharedMcastAddrTable[idx].portMask)
            {
                errVal = bridgeif_fdb_add(&netif_bridge,
                                          &ethaddr,
                                          gEthApp_sharedMcastAddrTable[idx].portMask);
            }

            if (errVal)
            {
                appLogPrintf("delMacSharedCb: bridgeif_fdb_add failed (%d)\n", errVal);
            }

            /* The array should have unique mcast addresses,
             * so no other match is expected
             */
            break;
        }
    }

    if (!matchFound)
    {
        appLogPrintf("delMacSharedCb: Address not found\n");
    }
}
#endif
