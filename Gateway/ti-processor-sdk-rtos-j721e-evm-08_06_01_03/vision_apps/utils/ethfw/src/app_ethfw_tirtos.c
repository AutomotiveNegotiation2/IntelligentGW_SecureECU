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

static int32_t EthApp_initEthFw(void);

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

    appLogPrintf("ETHFW: Init ... !!!\n");

    gEthAppObj.coreId = EnetSoc_getCoreId();

    /* Board related initialization */
    EnetBoard_initEthFw();
    EnetAppUtils_enableClocks(gEthAppObj.enetType, gEthAppObj.instId);

    /* Open UDMA driver */
    gEthAppObj.hUdmaDrv = appUdmaGetObj();
    if (gEthAppObj.hUdmaDrv == NULL)
    {
        appLogPrintf("ETHFW: ERROR: failed to open UDMA driver\n");
        status = -1;
    }

    /* Initialize Ethernet Firmware */
    if (status == ETHAPP_OK)
    {
        status = EthApp_initEthFw();
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

static int32_t EthApp_initEthFw(void)
{
    EthFw_Version ver;
    EthFw_Config ethFwCfg;
    EnetUdma_Cfg dmaCfg;
    int32_t status = ETHAPP_OK;
    int32_t i;

    /* Set EthFw config params */
    EthFw_initConfigParams(gEthAppObj.enetType, &ethFwCfg);

    dmaCfg.rxChInitPrms.dmaPriority = UDMA_DEFAULT_RX_CH_DMA_PRIORITY;
    dmaCfg.hUdmaDrv = gEthAppObj.hUdmaDrv;
    ethFwCfg.cpswCfg.dmaCfg = (void *)&dmaCfg;

    /* Set hardware port configuration parameters */
    ethFwCfg.ports = &gEthAppPorts[0];
    ethFwCfg.numPorts = ARRAY_SIZE(gEthAppPorts);

    /* Set virtual port configuration parameters */
    ethFwCfg.virtPortCfg  = &gEthApp_virtPortCfg[0];
    ethFwCfg.numVirtPorts = ARRAY_SIZE(gEthApp_virtPortCfg);

    /* Set AUTOSAR virtual port configuration parameters */
    ethFwCfg.autosarVirtPortCfg  = &gEthApp_autosarVirtPortCfg[0];
    ethFwCfg.numAutosarVirtPorts = ARRAY_SIZE(gEthApp_autosarVirtPortCfg);

    /* Overwrite config params with those for hardware interVLAN */
    EthHwInterVlan_setOpenPrms(&ethFwCfg.cpswCfg);

    /* Initialize the EthFw */
    gEthAppObj.hEthFw = EthFw_init(gEthAppObj.enetType, &ethFwCfg);
    if (gEthAppObj.hEthFw == NULL)
    {
        appLogPrintf("ETHFW: ERROR: failed to initialize the firmware\n");
        status = ETHAPP_ERROR;
    }

    /* Get and print EthFw version */
    if (status == ETHAPP_OK)
    {
        EthFw_getVersion(gEthAppObj.hEthFw, &ver);
        appLogPrintf("ETHFW: Version   : %d.%02d.%02d\n", ver.major, ver.minor, ver.rev);
        appLogPrintf("ETHFW: Build Date: %s %s, %s\n", ver.month, ver.date, ver.year);
        appLogPrintf("ETHFW: Build Time: %s:%s:%s\n", ver.hour, ver.min, ver.sec);
        appLogPrintf("ETHFW: Commit SHA: %s\n\n", ver.commitHash);
    }

    /* Post semaphore so that NDK/NIMU can continue with their initialization */
    if (status == ETHAPP_OK)
    {
        SemaphoreP_post(gEthAppObj.hInitSem);
    }

    return status;
}

/* NIMU callbacks (exact name required) */

bool EthFwCallbacks_isPortLinked(Enet_Handle hEnet)
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

void NimuEnetAppCb_getHandle(NimuEnetAppIf_GetHandleInArgs *inArgs,
                             NimuEnetAppIf_GetHandleOutArgs *outArgs)
{
    /* Wait for EthFw to be initialized */
    SemaphoreP_pend(gEthAppObj.hInitSem, SemaphoreP_WAIT_FOREVER);

    EthFwCallbacks_nimuCpswGetHandle(inArgs, outArgs);

    /* Save host port MAC address */
    memcpy(&gEthAppObj.hostMacAddr[0U],
           &outArgs->rxInfo.macAddr[0U],
           ENET_MAC_ADDR_LEN);
}

void NimuEnetAppCb_releaseHandle(NimuEnetAppIf_ReleaseHandleInfo *releaseInfo)
{
    EthFwCallbacks_nimuCpswReleaseHandle(releaseInfo);
}

/* NDK hooks */

void EthApp_ipAddrHookFxn(uint32_t IPAddr,
                          uint32_t IfIdx,
                          uint32_t fAdd)
{
    volatile uint32_t ipAddrHex = 0U;

    /* Use default/generic hook function */
    EthFwCallbacks_ipAddrHookFxn(IPAddr, IfIdx, fAdd);

    /* Save host port IP address */
    ipAddrHex = Enet_ntohl(IPAddr);
    memcpy(&gEthAppObj.hostIpAddr[0U],
           (uint8_t *)&ipAddrHex,
           ENET_IPv4_ADDR_LEN);

    EthFw_initTimeSyncPtp(ipAddrHex,
                          &gEthAppObj.hostMacAddr[0U],
                          ENET_BIT(ENET_MACPORT_NORM(gEthAppPorts[1].portNum)));
}

