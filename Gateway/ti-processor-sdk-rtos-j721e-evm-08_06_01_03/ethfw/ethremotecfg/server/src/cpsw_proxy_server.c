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
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>

/* OSAL */
#include <ti/osal/osal.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/EventP.h>

#include <ti/drv/ipc/ipc.h>
#include <server-rtos/remote-device.h>
#include <ethremotecfg/server/include/ethremotecfg_server.h>
#include <ethremotecfg/server/include/cpsw_proxy_server.h>

#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/include/core/enet_dma.h>
#include <ti/drv/enet/include/core/enet_mod_hostport.h>
#include <ti/drv/enet/include/per/cpsw.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>
#include <ti/drv/enet/examples/utils/include/enet_mcm.h>
#include <ti/drv/enet/examples/utils/include/enet_apprm.h>

#include <utils/ethfw_lwip/include/ethfw_lwip_utils.h>

#include <ethremotecfg/protocol/Eth_Rpc.h>
#include <ethremotecfg/protocol/cpsw_remote_notify_service.h>

/* EthFw utils header files */
#include <utils/console_io/include/app_log.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CPSWPROXY_RDEV_MSGSIZE                          (256U)

#define CPSWPROXY_CPSW9G_HWPUSH_BASE                    (26U)

#define CPSWPROXY_CPTS_HWPUSH_EVENTS_OR_MASK            (0xFFU)

#define CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_NAME           ("ASRETHDEVICE")

#define CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_PRIORITY       (2U)

#if defined(SAFERTOS)
#define CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_STACK          (16U * 1024U)
#define CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_ALIGN          CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_STACK
#else
#define CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_STACK          (0x4000)
#define CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_ALIGN          (32)
#endif

#define CPSWPROXY_AUTOSAR_ETHDRIVER_MSG_SIZE            (496U + 32U)

#define CPSWPROXY_AUTOSAR_ETHDRIVER_NUM_RPMSG_BUFS      (256U)

#define CPSWPROXY_AUTOSAR_ETHDRIVER_RPMSG_OBJ_SIZE      (256U)

#define CPSWPROXY_AUTOSAR_ETHDRIVER_DATA_SIZE           (CPSWPROXY_AUTOSAR_ETHDRIVER_MSG_SIZE * \
                                                         CPSWPROXY_AUTOSAR_ETHDRIVER_NUM_RPMSG_BUFS + \
                                                         CPSWPROXY_AUTOSAR_ETHDRIVER_RPMSG_OBJ_SIZE)

#define CPSWPROXY_ENET2RPMSG_ERR(x)                     ((status == ENET_SOK) ? \
                                                         RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK : \
                                                         RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_EFAIL)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct CpswProxyServer_HandleEntry_s
{
    Enet_Type   enetType;
    Enet_Handle cpswHandle;
    EnetMcm_CmdIf  *hMcmCmdIf;
} CpswProxyServer_HandleEntry;

typedef struct CpswProxyServer_HandleTable_s
{
    uint32_t numEntries;
    CpswProxyServer_HandleEntry entries[ENET_TYPE_NUM];
} CpswProxyServer_HandleTable;

typedef struct CpswProxyServer_EthDriverObj_s
{
    TaskP_Handle                 hAutosarEthTsk;
    RPMessage_Handle             hAutosarEthRpMsgEp;
    uint32_t                     dstProc;
    uint32_t                     localEp;
    uint32_t                     remoteEp;
    EthRemoteCfg_VirtPort        virtPort;
} CpswProxyServer_EthDriverObj;

typedef struct CpswProxyServer_NotifyServiceObj_s
{
    Enet_Type                    notifyServiceCpswType;
    TaskP_Handle                 hNotifyServiceTsk;
    EventP_Handle                hHwPushNotifyServiceEvent;
    uint32_t                     hwPushNotifyEventId[CPSW_CPTS_HWPUSH_COUNT_MAX];
    RPMessage_Handle             hNotifyServicRpMsgEp;
    uint32_t                     hwPush2CoreIdMap[CPSW_CPTS_HWPUSH_COUNT_MAX];
    uint32_t                     dstProcMask;
    uint32_t                     localEp;
    uint32_t                     remoteEp;
} CpswProxyServer_NotifyServiceObj;

typedef struct CpswProxyServer_SharedMcastEntry_s
{
    uint8_t macAddr[ENET_MAC_ADDR_LEN];
    uint32_t refCnt;
} CpswProxyServer_SharedMcastEntry;

typedef struct CpswProxyServer_SharedMcastTable_s
{
    CpswProxyServer_SharedMcastEntry entry[CPSWPROXYSERVER_SHARED_MCAST_LIST_LEN];
    uint32_t len;
} CpswProxyServer_SharedMcastTable;

typedef struct CpswProxyServer_Obj_s
{
    bool                        initDone;
    CpswProxyServer_HandleTable handleTbl;
    CpswProxyServer_InitEthfwDeviceDataCb initEthfwDeviceDataCb;
    CpswProxyServer_GetMcmCmdIfCb         getMcmCmdIfCb;
    CpswProxyServer_NotifyCb              notifyCb;
    SemaphoreP_Handle                     rdevStartSem;
    CpswProxyServer_EthDriverObj          ethDrvObj;
    CpswProxyServer_NotifyServiceObj      notifyServiceObj;
    CpswProxyServer_RsvdMcastCfg          rsvdMcastTbl;
    CpswProxyServer_SharedMcastTable      sharedMcastTbl;
    CpswProxyServer_FilterAddMacSharedCb  filterAddMacSharedCb;
    CpswProxyServer_FilterDelMacSharedCb  filterDelMacSharedCb;
    uint32_t alePortMask;
    uint32_t aleMacOnlyPortMask;
    uint16_t dfltVlanIdMacOnlyPorts;
    uint16_t dfltVlanIdSwitchPorts;
} CpswProxyServer_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static int32_t CpswProxyServer_initAutosarEthDeviceEp(CpswProxyServer_Obj * hProxyServer,
                                                      CpswProxyServer_Config_t * cfg);
static void CpswProxyServer_autosarEthDriverTaskFxn(void* arg0, void* arg1);

static int32_t CpswProxyServer_initNotifyServiceEp(CpswProxyServer_Obj * hProxyServer,
                                                      CpswProxyServer_Config_t * cfg);

static void CpswProxyServer_hwPushNotifyFxn(void *arg, CpswCpts_HwPush hwPushNum);

static void CpswProxyServer_notifyServiceTaskFxn(void* arg0, void* arg1);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**< Buffer to store received messages. 256 messages of 512 bytes +
        space for book-keeping */
static uint8_t g_CpswProxyServerAutosarRpmsgBuf[CPSWPROXY_AUTOSAR_ETHDRIVER_DATA_SIZE]  __attribute__ ((aligned(8192)));

/**< Buffer to store received messages. 256 messages of 512 bytes +
        space for book-keeping */
static uint8_t g_CpswProxyServerNotifyServiceRpmsgBuf[CPSW_REMOTE_NOTIFY_SERVICE_DATA_SIZE]  __attribute__ ((aligned(8192)));

/**< StackBuffer for different tasks */
static uint8_t gCpswProxyServer_autosarEthDriverTaskStackBuf[CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_STACK] __attribute__ ((aligned(CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_ALIGN)));
static uint8_t gCpswProxyServer_notifyServiceTaskStackBuf[CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKSIZE] __attribute__ ((aligned(CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKALIGN)));

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static int32_t CpswProxyServer_getMcmCmdIf(const CpswProxyServer_HandleTable *tbl, Enet_Type key, EnetMcm_CmdIf  **hMcmCmdIf)
{
    int32_t i;
    int32_t retVal;

    EnetAppUtils_assert(tbl->numEntries < ENET_ARRAYSIZE(tbl->entries));

    for (i = 0; i < tbl->numEntries; i++)
    {
        if (key == tbl->entries[i].enetType)
        {
            break;
        }
    }
    if (i < tbl->numEntries)
    {
        *hMcmCmdIf = tbl->entries[i].hMcmCmdIf;
        retVal = CPSWPROXYSERVER_SOK;
    }
    else
    {
        *hMcmCmdIf = NULL;
        retVal = CPSWPROXYSERVER_EFAIL;
    }
    return retVal;
}

static int32_t CpswProxyServer_getCpswHandle(const CpswProxyServer_HandleTable *tbl, Enet_Type key, Enet_Handle  *pCpswHandle)
{
    int32_t i;
    int32_t retVal;

    EnetAppUtils_assert(tbl->numEntries < ENET_ARRAYSIZE(tbl->entries));

    for (i = 0; i < tbl->numEntries; i++)
    {
        if (key == tbl->entries[i].enetType)
        {
            break;
        }
    }
    if (i < tbl->numEntries)
    {
        *pCpswHandle = tbl->entries[i].cpswHandle;
        retVal = CPSWPROXYSERVER_SOK;
    }
    else
    {
        *pCpswHandle = NULL;
        retVal = CPSWPROXYSERVER_EFAIL;
    }
    return retVal;
}

static int32_t CpswProxyServer_getCpswType(const CpswProxyServer_HandleTable *tbl, Enet_Handle hEnet, Enet_Type *pCpswType)
{
    int32_t i;
    int32_t retVal;

    EnetAppUtils_assert(tbl->numEntries < ENET_ARRAYSIZE(tbl->entries));

    for (i = 0; i < tbl->numEntries; i++)
    {
        if (hEnet == tbl->entries[i].cpswHandle)
        {
            break;
        }
    }
    if (i < tbl->numEntries)
    {
        *pCpswType = tbl->entries[i].enetType;
        retVal = CPSWPROXYSERVER_SOK;
    }
    else
    {
        retVal = CPSWPROXYSERVER_EFAIL;
    }
    return retVal;
}

static  int32_t CpswProxy_mapRdev2CpswType(enum rpmsg_kdrv_ethswitch_cpsw_type  rdevCpswType, Enet_Type * pCpswType)
{
    int32_t retVal = CPSWPROXYSERVER_SOK;

    switch (rdevCpswType)
    {
        case RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MCU:
            *pCpswType = ENET_CPSW_2G;
            break;

        case RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAIN:
#if defined(SOC_J7200)
            *pCpswType = ENET_CPSW_5G;
#elif defined(SOC_J721E) || defined(SOC_J784S4)
            *pCpswType = ENET_CPSW_9G;
#else
            retVal = CPSWPROXYSERVER_EFAIL;
#endif
            break;

        default:
            retVal = CPSWPROXYSERVER_EFAIL;
            break;
    }
    return retVal;
}

static  int32_t CpswProxy_mapEthRpc2RdevCpswType(Eth_RpcCpswType ethRpcCpswType, enum rpmsg_kdrv_ethswitch_cpsw_type  *rdevCpswType)
{
    int32_t retVal = CPSWPROXYSERVER_SOK;

    switch (ethRpcCpswType)
    {
        case ETH_RPC_CPSWTYPE_MCU:
            *rdevCpswType = RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MCU;
            break;

        case ETH_RPC_CPSWTYPE_MAIN:
            *rdevCpswType = RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAIN;
            break;

        default:
            retVal = CPSWPROXYSERVER_EFAIL;
            break;
    }
    return retVal;
}

static  int32_t CpswProxy_mapEthRpcClientNotify2RdevClientNotifyType(Eth_RpcClientNotifyType ethRpcClientNotifyType, enum rpmsg_kdrv_ethswitch_client_notify_type *rdevNotifyType)
{
    int32_t retVal = CPSWPROXYSERVER_SOK;

    switch (ethRpcClientNotifyType)
    {
        case ETH_RPC_CLIENTNOTIFY_DUMPSTATS:
            *rdevNotifyType = RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_DUMPSTATS;
            break;

        case ETH_RPC_CLIENTNOTIFY_CUSTOM:
            *rdevNotifyType = RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_CUSTOM;
            break;

        default:
            retVal = CPSWPROXYSERVER_EFAIL;
            break;
    }
    return retVal;
}

static CpswProxyServer_Obj * CpswProxyServer_getHandle(void)
{
    static CpswProxyServer_Obj gProxyServerObj =
    {
        .handleTbl = {.numEntries = 0},
        .initEthfwDeviceDataCb = NULL,
        .getMcmCmdIfCb         = NULL,
        .rdevStartSem          = NULL,
        .initDone              = FALSE
    };

    return (&gProxyServerObj);
}


static void CpswProxyServer_addHandleEntry(CpswProxyServer_HandleTable *tbl, Enet_Handle hEnet, Enet_Type enetType, EnetMcm_CmdIf *hMcmCmdIf)
{
    int32_t status;
    Enet_Handle hCpswLocal;

    status = CpswProxyServer_getCpswHandle(tbl, enetType, &hCpswLocal);

    if (status == CPSWPROXYSERVER_SOK)
    {
        EnetMcm_CmdIf *hMcmCmdIfLocal;

        EnetAppUtils_assert(hCpswLocal == hEnet);
        CpswProxyServer_getMcmCmdIf(tbl, enetType, &hMcmCmdIfLocal);
        EnetAppUtils_assert(hMcmCmdIfLocal == hMcmCmdIf);
    }
    else
    {
        EnetAppUtils_assert(tbl->numEntries < ENET_ARRAYSIZE(tbl->entries));
        tbl->entries[tbl->numEntries].cpswHandle = hEnet;
        tbl->entries[tbl->numEntries].enetType   = enetType;
        tbl->entries[tbl->numEntries].hMcmCmdIf  = hMcmCmdIf;
        tbl->numEntries++;
    }
}

static int32_t CpswProxyServer_attachHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                               uint32_t host_id,
                                               uint8_t cpsw_type,
                                               uint64_t *pId,
                                               uint32_t *pCoreKey,
                                               uint32_t *pRxMtu,
                                               uint32_t *pTxMtu,
                                               uint32_t txMtuArraySize,
                                               uint32_t *pFeatures,
                                               uint32_t *pMacOnlyPort)
{
    int32_t status;
    EnetMcm_HandleInfo handleInfo;
    EnetPer_AttachCoreOutArgs attachInfo;
    Enet_IoctlPrms prms;
    bool csumOffloadFlag;
    Enet_Type enetType;
    CpswProxyServer_Obj * hProxyServer;
    EnetMcm_CmdIf *hMcmCmdIf;
    enum rpmsg_kdrv_ethswitch_cpsw_type  rdevCpswType = (enum rpmsg_kdrv_ethswitch_cpsw_type)cpsw_type;
    bool isMacPort = EthRemoteCfg_isMacPort(virtPort);

    status = CpswProxy_mapRdev2CpswType(rdevCpswType, &enetType);
    if (ENET_SOK == status)
    {
        appLogPrintf("Function:%s,HostId:%u,CpswType:%u\n", __func__, host_id, enetType);

        hProxyServer = CpswProxyServer_getHandle();
        EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
        status = CpswProxyServer_getMcmCmdIf(&hProxyServer->handleTbl, enetType, &hMcmCmdIf);
        if ((status != ENET_SOK) || (hMcmCmdIf == NULL))
        {
            EnetAppUtils_assert(hProxyServer->getMcmCmdIfCb != NULL);
            hProxyServer->getMcmCmdIfCb(enetType, &hMcmCmdIf);
            EnetAppUtils_assert(hMcmCmdIf != NULL);
            status = ENET_SOK;
        }
    }

    if (ENET_SOK == status)
    {
        EnetAppUtils_assert(hMcmCmdIf->hMboxCmd != NULL);
        EnetAppUtils_assert(hMcmCmdIf->hMboxResponse != NULL);

        EnetMcm_acquireHandleInfo(hMcmCmdIf, &handleInfo);
        EnetMcm_coreAttach(hMcmCmdIf, host_id, &attachInfo);

        *pId = (uint64_t)(handleInfo.hEnet);
        *pCoreKey = attachInfo.coreKey;
        *pRxMtu = attachInfo.rxMtu;
        EnetAppUtils_assert(txMtuArraySize ==
                            ENET_ARRAYSIZE(attachInfo.txMtu));
        memcpy(pTxMtu, attachInfo.txMtu, sizeof(attachInfo.txMtu));
        *pFeatures = 0;
        ENET_IOCTL_SET_OUT_ARGS(&prms, &csumOffloadFlag);
        status = Enet_ioctl(handleInfo.hEnet,
                            host_id,
                            ENET_HOSTPORT_IS_CSUM_OFFLOAD_ENABLED,
                            &prms);

        EnetAppUtils_assert(status == ENET_SOK);

        if (csumOffloadFlag)
        {
            *pFeatures |= RPMSG_KDRV_TP_ETHSWITCH_FEATURE_TXCSUM;
        }

        if (isMacPort)
        {
            *pFeatures |= RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MAC_ONLY;
            *pMacOnlyPort = EthRemoteCfg_getPortNum(virtPort);
        }
        else
        {
            *pFeatures |= RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MC_FILTER;
            *pMacOnlyPort = 0U;
        }

        CpswProxyServer_addHandleEntry(&hProxyServer->handleTbl, handleInfo.hEnet, enetType, hMcmCmdIf);
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static void CpswProxyServer_validateHandle(Enet_Handle hEnet)
{
    int32_t status;
    CpswProxyServer_Obj * hProxyServer;
    Enet_Type enetType;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
    status = CpswProxyServer_getCpswType(&hProxyServer->handleTbl, hEnet, &enetType);
    EnetAppUtils_assert(CPSWPROXYSERVER_SOK == status);
    EnetAppUtils_assert(hEnet == Enet_getHandle(enetType, 0U));

}

static int32_t CpswProxyServer_allocTxHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                uint32_t host_id,
                                                uint64_t handle,
                                                uint32_t core_key,
                                                uint32_t *pTxCpswPsilDstId)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x\n", __func__, host_id, hEnet, core_key);
    CpswProxyServer_validateHandle(hEnet);

    status = EnetAppUtils_allocTxCh(hEnet,
                                    core_key,
                                    host_id,
                                    pTxCpswPsilDstId);

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static void CpswProxyServer_validateStartIdx(Enet_Handle hEnet,
                                             uint32_t host_id,
                                             uint32_t rxFlowStartId)
{
    uint32_t p0FlowIdOffset;

    p0FlowIdOffset = EnetAppUtils_getStartFlowIdx(hEnet, host_id);
    EnetAppUtils_assert(rxFlowStartId == p0FlowIdOffset);
}

static int32_t CpswProxyServer_allocRxHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                uint32_t host_id,
                                                uint64_t handle,
                                                uint32_t core_key,
                                                uint32_t *pAllocFlowIdx)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    uint32_t start_flow_idx, flow_idx_offset;

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x\n", __func__, host_id, hEnet, core_key);
    CpswProxyServer_validateHandle(hEnet);

    status = EnetAppUtils_allocRxFlow(hEnet, core_key, host_id, &start_flow_idx, &flow_idx_offset);
    if (status == ENET_SOK)
    {
        CpswProxyServer_validateStartIdx(hEnet, host_id, start_flow_idx);
        *pAllocFlowIdx = start_flow_idx + flow_idx_offset;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_allocMacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                 uint32_t host_id,
                                                 uint64_t handle,
                                                 uint32_t core_key,
                                                 u8 *mac_address)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x\n", __func__, host_id, hEnet, core_key);
    CpswProxyServer_validateHandle(hEnet);

    status = EnetAppUtils_allocMac(hEnet, core_key, host_id, mac_address);

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_regMacPortFlow(Enet_Handle hEnet,
                                              uint32_t remoteCoreId,
                                              uint32_t coreKey,
                                              Enet_MacPort macPort,
                                              u8 *macAddr,
                                              uint32_t flowStartIdx,
                                              uint32_t flowIdx)
{
    Cpsw_PortRxFlowInfo portRxFlow;
    CpswAle_SetUcastEntryInArgs ucastInArgs;
    Enet_IoctlPrms prms;
    uint32_t entryIdx;
    int32_t status = CPSWPROXYSERVER_SOK;

    if (EnetUtils_isMcastAddr(macAddr))
    {
        EnetAppUtils_print("regMacPortFlow() port %u: mcast not supported\n",
                           ENET_MACPORT_ID(macPort));
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    /* Add unicast address */
    if (status == CPSWPROXYSERVER_SOK)
    {
        ucastInArgs.addr.vlanId  = 0U;
        ucastInArgs.info.portNum = CPSW_ALE_HOST_PORT_NUM;
        ucastInArgs.info.blocked = false;
        ucastInArgs.info.secure  = true;
        ucastInArgs.info.super   = false;
        ucastInArgs.info.ageable = false;
        ucastInArgs.info.trunk   = false;
        EnetUtils_copyMacAddr(&ucastInArgs.addr.addr[0U], macAddr);

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &ucastInArgs, &entryIdx);

        status = Enet_ioctl(hEnet, remoteCoreId, CPSW_ALE_IOCTL_ADD_UCAST, &prms);
        if (status != ENET_SOK)
        {
            EnetAppUtils_print("regMacPortFlow() port %u: failed to add ucast entry: %d\n",
                               ENET_MACPORT_ID(macPort), status);
        }
    }

    /* Setup policer with "port" as match criteria */
    if (status == CPSWPROXYSERVER_SOK)
    {
        portRxFlow.coreKey  = coreKey;
        portRxFlow.startIdx = flowStartIdx;
        portRxFlow.flowIdx  = flowIdx;
        portRxFlow.macPort  = macPort;

        ENET_IOCTL_SET_IN_ARGS(&prms, &portRxFlow);

        status = Enet_ioctl(hEnet, remoteCoreId, CPSW_IOCTL_REGISTER_PORT_RX_FLOW, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("regMacPortFlow() port %u: failed to register RX flow: %s\n",
                         ENET_MACPORT_ID(macPort), status);
        }
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_unregMacPortFlow(Enet_Handle hEnet,
                                                uint32_t remoteCoreId,
                                                uint32_t coreKey,
                                                Enet_MacPort macPort,
                                                u8 *macAddr,
                                                uint32_t flowStartIdx,
                                                uint32_t flowIdx)
{
    Cpsw_PortRxFlowInfo portRxFlow;
    CpswAle_MacAddrInfo macAddrInfo;
    Enet_IoctlPrms prms;
    int32_t status = CPSWPROXYSERVER_SOK;

    if (EnetUtils_isMcastAddr(macAddr))
    {
        EnetAppUtils_print("unregMacPortFlow() port %u: mcast not supported\n",
                           ENET_MACPORT_ID(macPort));
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    /* Remove policer with "port" match criteria */
    if (status == CPSWPROXYSERVER_SOK)
    {
        portRxFlow.coreKey  = coreKey;
        portRxFlow.startIdx = flowStartIdx;
        portRxFlow.flowIdx  = flowIdx;
        portRxFlow.macPort  = macPort;

        ENET_IOCTL_SET_IN_ARGS(&prms, &portRxFlow);

        status = Enet_ioctl(hEnet, remoteCoreId, CPSW_IOCTL_UNREGISTER_PORT_RX_FLOW, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("unregMacPortFlow() port %u: failed to unregister RX flow: %s\n",
                         ENET_MACPORT_ID(macPort), status);
        }
    }

    /* Remove unicast address */
    if (status == CPSWPROXYSERVER_SOK)
    {
        macAddrInfo.vlanId = 0U;
        EnetUtils_copyMacAddr(&macAddrInfo.addr[0U], macAddr);

        ENET_IOCTL_SET_IN_ARGS(&prms, &macAddrInfo);

        status = Enet_ioctl(hEnet, remoteCoreId, CPSW_ALE_IOCTL_REMOVE_ADDR, &prms);
        if (status != ENET_SOK)
        {
            EnetAppUtils_print("unregMacPortFlow() port %u: failed to remove ucast entry: %d\n",
                               ENET_MACPORT_ID(macPort), status);
        }
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_registerMacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                    uint32_t host_id,
                                                    uint64_t handle,
                                                    uint32_t core_key,
                                                    u8 *mac_address,
                                                    uint32_t flow_idx)
{
    CpswProxyServer_Obj *hProxyServer;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_MacPort macPort = EthRemoteCfg_getMacPort(virtPort);
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);
    uint32_t start_flow_idx, flow_idx_offset;
    int32_t status;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));

    CpswProxyServer_validateHandle(hEnet);
    EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);
    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x, FlowIdx:%u, FlowIdxOffset:%u\n",
                 __func__,
                 host_id,
                 hEnet,
                 core_key,
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5],
                 flow_idx,
                 flow_idx_offset);

    if (isSwitchPort)
    {
        status = EnetAppUtils_regDstMacRxFlow(hEnet, core_key, host_id, start_flow_idx, flow_idx_offset, mac_address);
        if (status != ENET_SOK)
        {
            appLogPrintf("EnetAppUtils_regDstMacRxFlow() failed CPSW_ALE_IOCTL_SET_POLICER: %d\n", status);
        }
    }
    else
    {
        status = CpswProxyServer_regMacPortFlow(hEnet,
                                                host_id,
                                                core_key,
                                                macPort,
                                                mac_address,
                                                start_flow_idx,
                                                flow_idx_offset);
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_unregisterMacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                      uint32_t host_id,
                                                      uint64_t handle,
                                                      uint32_t core_key,
                                                      u8 *mac_address,
                                                      uint32_t flow_idx)
{
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_MacPort macPort = EthRemoteCfg_getMacPort(virtPort);
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);
    uint32_t start_flow_idx, flow_idx_offset;
    int32_t status;

    CpswProxyServer_validateHandle(hEnet);
    EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);
    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x, FlowIdx:%u, FlowIdOffset:%u\n",
                 __func__,
                 host_id,
                 hEnet,
                 core_key,
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5],
                 flow_idx,
                 flow_idx_offset);

    if (isSwitchPort)
    {
        status = EnetAppUtils_unregDstMacRxFlow(hEnet, core_key, host_id, start_flow_idx, flow_idx_offset, mac_address);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed EnetAppUtils_unregDstMacRxFlow: %d\n", status);
        }
    }
    else
    {
        status = CpswProxyServer_unregMacPortFlow(hEnet,
                                                  host_id,
                                                  core_key,
                                                  macPort,
                                                  mac_address,
                                                  start_flow_idx,
                                                  flow_idx_offset);
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_registerRxDefaultHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                          uint32_t host_id,
                                                          uint64_t handle,
                                                          uint32_t core_key,
                                                          uint32_t flow_idx)
{
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);
    uint32_t start_flow_idx, flow_idx_offset;
    int32_t status = CPSWPROXYSERVER_SOK;

    if (isSwitchPort)
    {
        CpswProxyServer_validateHandle(hEnet);
        EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);

        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, FlowId:%x, FlowIdOffset:%x\n",
                     __func__, host_id, hEnet, core_key, flow_idx, flow_idx_offset);

        status = EnetAppUtils_unregDfltRxFlow(hEnet, core_key, host_id, start_flow_idx, flow_idx_offset);
    }
    else
    {
        appLogPrintf("registerRxDefaultFlow is not supported on virtual MAC ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_unregisterRxDefaultHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                            uint32_t host_id,
                                                            uint64_t handle,
                                                            uint32_t core_key,
                                                            uint32_t flow_idx)
{
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);
    uint32_t start_flow_idx, flow_idx_offset;
    int32_t status = CPSWPROXYSERVER_SOK;

    if (isSwitchPort)
    {
        CpswProxyServer_validateHandle(hEnet);
        EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);

        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, FlowId:%x\n",
                     __func__, host_id, hEnet, core_key, flow_idx);

        status = EnetAppUtils_unregDfltRxFlow(hEnet, core_key, host_id, start_flow_idx, flow_idx_offset);
    }
    else
    {
        appLogPrintf("unregisterRxDefaultFlow is not supported on virtual MAC ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_freeTxHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                               uint32_t host_id,
                                               uint64_t handle,
                                               uint32_t core_key,
                                               uint32_t tx_cpsw_psil_dst_id)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, TxId:%x\n",
                 __func__, host_id, hEnet, core_key, tx_cpsw_psil_dst_id);

    CpswProxyServer_validateHandle(hEnet);

    status = EnetAppUtils_freeTxCh(hEnet, core_key, host_id, tx_cpsw_psil_dst_id);

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_freeRxHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                               uint32_t host_id,
                                               uint64_t handle,
                                               uint32_t core_key,
                                               uint32_t alloc_flow_idx)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    uint32_t start_flow_idx, flow_idx_offset;

    CpswProxyServer_validateHandle(hEnet);
    EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, alloc_flow_idx, &start_flow_idx, &flow_idx_offset);

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, RxId:%x RxOffset:%x\n",
                 __func__, host_id, hEnet, core_key, alloc_flow_idx, flow_idx_offset);

    CpswProxyServer_validateStartIdx(hEnet, host_id, start_flow_idx);
    status = EnetAppUtils_freeRxFlow(hEnet,
                                     core_key,
                                     host_id,
                                     flow_idx_offset);

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_freeMacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                uint32_t host_id,
                                                uint64_t handle,
                                                uint32_t core_key,
                                                u8 *mac_address)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x\n",
                 __func__,
                 host_id,
                 hEnet,
                 core_key,
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5]);

    CpswProxyServer_validateHandle(hEnet);

    status = EnetAppUtils_freeMac(hEnet, core_key, host_id, mac_address);

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_detachHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                               uint32_t host_id,
                                               uint64_t handle,
                                               uint32_t core_key)
{
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    EnetMcm_CmdIf *hMcmCmdIf;
    CpswProxyServer_Obj * hProxyServer;
    int32_t status;
    Enet_Type enetType;

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x\n", __func__, host_id, hEnet, core_key);
    CpswProxyServer_validateHandle(hEnet);

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
    status = CpswProxyServer_getCpswType(&hProxyServer->handleTbl, hEnet, &enetType);
    EnetAppUtils_assert(status == CPSWPROXYSERVER_SOK);
    status = CpswProxyServer_getMcmCmdIf(&hProxyServer->handleTbl, enetType, &hMcmCmdIf);
    EnetAppUtils_assert((status == CPSWPROXYSERVER_SOK) && (hMcmCmdIf != NULL));
    EnetAppUtils_assert(hMcmCmdIf->hMboxCmd != NULL);
    EnetAppUtils_assert(hMcmCmdIf->hMboxResponse != NULL);

    EnetMcm_coreDetach(hMcmCmdIf, host_id, core_key);
    EnetMcm_releaseHandleInfo(hMcmCmdIf);

    return RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK;
}

static void CpswProxyServer_printStats(Enet_Handle hEnet,
                                       Enet_Type enetType,
                                       uint32_t coreId)
{
    Enet_IoctlPrms prms;
    Enet_MacPort portNum;
    CpswStats_PortStats portStats;
    int32_t status = ENET_SOK;
    uint32_t i;

    ENET_IOCTL_SET_OUT_ARGS(&prms, &portStats);
    status = Enet_ioctl(hEnet, coreId, ENET_STATS_IOCTL_GET_HOSTPORT_STATS, &prms);
    if (status == ENET_SOK)
    {
        appLogPrintf("\n Port 0 Statistics\n");
        appLogPrintf("-----------------------------------------\n");
        switch (enetType)
        {
            case ENET_CPSW_2G:
            {
                CpswStats_HostPort_2g *st;

                st = (CpswStats_HostPort_2g *)&portStats;
                EnetAppUtils_printHostPortStats2G(st);
                break;
            }

            case ENET_CPSW_5G:
            case ENET_CPSW_9G:
            {
                CpswStats_HostPort_Ng *st;

                st = (CpswStats_HostPort_Ng *)&portStats;
                EnetAppUtils_printHostPortStats9G(st);
                break;
            }

            default:
            {
                EnetAppUtils_assert(false);
                break;
            }
        }

        appLogPrintf("\n");
    }
    else
    {
        appLogPrintf("CpswProxyServer_printStats() failed to get host stats: %d\n", status);
    }

    if (status == ENET_SOK)
    {
        for (i = 0, portNum = ENET_MAC_PORT_FIRST; i < Enet_getMacPortMax(enetType, 0u); i++, portNum++)
        {
            ENET_IOCTL_SET_INOUT_ARGS(&prms, &portNum, &portStats);
            status = Enet_ioctl(hEnet, coreId, ENET_STATS_IOCTL_GET_MACPORT_STATS, &prms);
            if (status == ENET_SOK)
            {
                appLogPrintf("\n External Port %d Statistics\n", ENET_MACPORT_NORM(portNum));
                appLogPrintf("-----------------------------------------\n");
                switch (enetType)
                {
                    case ENET_CPSW_2G:
                    {
                        CpswStats_MacPort_2g *st;

                        st = (CpswStats_MacPort_2g *)&portStats;
                        EnetAppUtils_printMacPortStats2G(st);
                        break;
                    }

                    case ENET_CPSW_5G:
                    case ENET_CPSW_9G:
                    {
                        CpswStats_MacPort_Ng *st;

                        st = (CpswStats_MacPort_Ng *)&portStats;
                        EnetAppUtils_printMacPortStats9G(st);
                        break;
                    }

                    default:
                    {
                        EnetAppUtils_assert(false);
                        break;
                    }
                }

                appLogPrintf("\n");
            }
            else
            {
                appLogPrintf("CpswProxyServer_printStats() failed to get MAC stats: %d\n", status);
            }
        }
    }
}

static int32_t CpswProxyServer_ioctlHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                              uint32_t host_id,
                                              uint64_t handle,
                                              uint32_t core_key,
                                              u32 cmd,
                                              const u8 *inargs,
                                              u32 inargs_len,
                                              u8 *outargs,
                                              uint32_t outargs_len)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_IoctlPrms prms;
    uint64_t inArgsBuf[(RPMSG_KDRV_TP_ETHSWITCH_IOCTL_INARGS_LEN/sizeof(uint64_t)) + 1];
    uint64_t outArgsBuf[(RPMSG_KDRV_TP_ETHSWITCH_IOCTL_OUTARGS_LEN/sizeof(uint64_t)) + 1];

    /* Skip PHY link status check prints as they happen too often */
    if (cmd != ENET_PER_IOCTL_IS_PORT_LINK_UP)
    {
        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, Cmd:%x,InArgsLen:%u, OutArgsLen:%u\n",
                     __func__, host_id, hEnet, core_key, cmd, inargs_len, outargs_len);
    }

    CpswProxyServer_validateHandle(hEnet);

    prms.inArgsSize = inargs_len;
    prms.outArgsSize = outargs_len;
    EnetAppUtils_assert(inargs_len <= sizeof(inArgsBuf));
    /* To ensure structure are aligned, copy the inArgs to unit64_t aligned buffer */
    memcpy(inArgsBuf, inargs, inargs_len);
    prms.inArgs = inArgsBuf;
    /* To ensure structure are aligned, use unit64_t aligned buffer for outArgs  */
    EnetAppUtils_assert(outargs_len <= sizeof(outArgsBuf));
    prms.outArgs = outArgsBuf;
    if (prms.inArgsSize == 0)
    {
        prms.inArgs = NULL;
    }

    if (prms.outArgsSize == 0)
    {
        prms.outArgs = NULL;
    }

    status = Enet_ioctl(hEnet, host_id, cmd, &prms);

    if (status == ENET_SOK)
    {
        /* Copy the outArgs from temporary aligned buffer back to msg buffer */
        memcpy(outargs, outArgsBuf, outargs_len);
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_regwrHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                              uint32_t host_id,
                                              uint32_t regaddr,
                                              uint32_t regval,
                                              uint32_t *pRegval)
{
    appLogPrintf("Function:%s,HostId:%u, RegAddr:%p, RegVal:%x \n", __func__, host_id, regaddr, regval);

    CSL_REG32_WR(regaddr, regval);

    *pRegval = CSL_REG32_RD(regaddr);

    return RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK;
}

static int32_t CpswProxyServer_regrdHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                              uint32_t host_id,
                                              uint32_t regaddr,
                                              uint32_t *pRegval)
{
    appLogPrintf("Function:%s,HostId:%u, RegAddr:%p \n", __func__, host_id, regaddr);

    *pRegval = CSL_REG32_RD(regaddr);

    return RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK;
}

static int32_t CpswProxyServer_registerIpv4MacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                        uint32_t host_id,
                                                        uint64_t handle,
                                                        uint32_t core_key,
                                                        uint8_t *mac_address,
                                                        uint8_t *ipv4_addr)
{
    int32_t status = 0;
    uint32_t ipaddr = ((uint32_t)ipv4_addr[0] << 24U) | ((uint32_t)ipv4_addr[1] << 16U) | ((uint32_t)ipv4_addr[2] << 8U) | ((uint32_t)ipv4_addr[3] << 0U);
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
#if (defined(FREERTOS) || defined(SAFERTOS)) && defined(ETHFW_PROXY_ARP_HANDLING)
    ip4_addr_t ip4Addr;
    struct eth_addr hwAddr;
#endif
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);

    if (isSwitchPort)
    {
        ipaddr = Enet_htonl(ipaddr);
        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x IPv4Addr:%d.%d.%d.%d\n",
                     __func__,
                     host_id,
                     hEnet,
                     core_key,
                     mac_address[0],
                     mac_address[1],
                     mac_address[2],
                     mac_address[3],
                     mac_address[4],
                     mac_address[5],
                     ipv4_addr[0],
                     ipv4_addr[1],
                     ipv4_addr[2],
                     ipv4_addr[3]);

        CpswProxyServer_validateHandle(hEnet);

#if (defined(FREERTOS) || defined(SAFERTOS)) && defined(ETHFW_PROXY_ARP_HANDLING)
        IP4_ADDR(&ip4Addr, ipv4_addr[0], ipv4_addr[1], ipv4_addr[2], ipv4_addr[3]);
        SMEMCPY(&hwAddr, mac_address, ETH_HWADDR_LEN);

        status = EthFwArpUtils_addAddr(&ip4Addr, &hwAddr);
        if (status != ETHFW_LWIP_UTILS_SOK)
        {
            appLogPrintf("Failed to add ARP entry: %d\n", status);
        }
        else
        {
            EthFwArpUtils_printTable();
        }
#endif
    }
    else
    {
        appLogPrintf("registerIPv4Mac is not supported on virtual MAC ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_unregisterIpv4MacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                          uint32_t host_id,
                                                          uint64_t handle,
                                                          uint32_t core_key,
                                                          uint8_t *ipv4_addr)
{
    int32_t status = 0;
    uint32_t ipaddr = ((uint32_t)ipv4_addr[0] << 24U) | ((uint32_t)ipv4_addr[1] << 16U) | ((uint32_t)ipv4_addr[2] << 8U) | ((uint32_t)ipv4_addr[3] << 0U);
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
#if (defined(FREERTOS) || defined(SAFERTOS)) && defined(ETHFW_PROXY_ARP_HANDLING)
    ip4_addr_t ip4Addr;
#endif
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);

    if (isSwitchPort)
    {
        ipaddr = Enet_htonl(ipaddr);
        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x,IPv4Addr:%x:%x:%x:%x\n",
                     __func__,
                     host_id,
                     hEnet,
                     core_key,
                     ipv4_addr[0],
                     ipv4_addr[1],
                     ipv4_addr[2],
                     ipv4_addr[3]);

        CpswProxyServer_validateHandle(hEnet);

#if (defined(FREERTOS) || defined(SAFERTOS)) && defined(ETHFW_PROXY_ARP_HANDLING)
        IP4_ADDR(&ip4Addr, ipv4_addr[0], ipv4_addr[1], ipv4_addr[2], ipv4_addr[3]);

        status = EthFwArpUtils_delAddr(&ip4Addr);
        if (status != ETHFW_LWIP_UTILS_SOK)
        {
            appLogPrintf("Failed to remove ARP entry: %d\n", status);
        }
        else
        {
            EthFwArpUtils_printTable();
        }
#endif
    }
    else
    {
        appLogPrintf("unregisterIPv4Mac is not supported on virtual MAC ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_registerIpv6MacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                        uint32_t host_id,
                                                        uint64_t handle,
                                                        uint32_t core_key,
                                                        uint8_t *mac_address,
                                                        uint8_t *ipv6_addr)
{
    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x IPv6Addr:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x\n",
                 __func__,
                 host_id,
                 handle,
                 core_key,
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5],
                 ipv6_addr[0],
                 ipv6_addr[1],
                 ipv6_addr[2],
                 ipv6_addr[3],
                 ipv6_addr[4],
                 ipv6_addr[5],
                 ipv6_addr[6],
                 ipv6_addr[7],
                 ipv6_addr[8],
                 ipv6_addr[9],
                 ipv6_addr[10],
                 ipv6_addr[11],
                 ipv6_addr[12],
                 ipv6_addr[13],
                 ipv6_addr[14],
                 ipv6_addr[15]);

    return RPMSG_KDRV_TP_ETHSWITCH_CMDSTATUS_OK;
}

static int32_t CpswProxyServer_attachExtHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                  uint32_t host_id,
                                                  uint8_t cpsw_type,
                                                  uint64_t *pId,
                                                  uint32_t *pCoreKey,
                                                  uint32_t *pRxMtu,
                                                  uint32_t *pTxMtu,
                                                  uint32_t txMtuArraySize,
                                                  uint32_t *pFeatures,
                                                  uint32_t *pAllocFlowIdx,
                                                  uint32_t *pTxCpswPsilDstId,
                                                  uint8_t *macAddress,
                                                  uint32_t *pMacOnlyPort)
{
    int32_t status = CPSWPROXYSERVER_SOK;
    EnetMcm_HandleInfo handleInfo;
    EnetPer_AttachCoreOutArgs attachInfo;
    Enet_IoctlPrms prms;
    bool csumOffloadFlag;
    Enet_Type enetType;
    uint32_t start_flow_idx, flow_idx_offset;
    CpswProxyServer_Obj * hProxyServer;
    EnetMcm_CmdIf *hMcmCmdIf;
    enum rpmsg_kdrv_ethswitch_cpsw_type rdevCpswType = (enum rpmsg_kdrv_ethswitch_cpsw_type) cpsw_type;
    bool isMacPort = EthRemoteCfg_isMacPort(virtPort);

    status = CpswProxy_mapRdev2CpswType(rdevCpswType, &enetType);
    if (CPSWPROXYSERVER_SOK == status)
    {
        appLogPrintf("Function:%s,HostId:%u,CpswType:%u\n", __func__, host_id, enetType);

        hProxyServer = CpswProxyServer_getHandle();
        EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
        status = CpswProxyServer_getMcmCmdIf(&hProxyServer->handleTbl, enetType, &hMcmCmdIf);
        if ((status != CPSWPROXYSERVER_SOK) || (hMcmCmdIf == NULL))
        {
            EnetAppUtils_assert(hProxyServer->getMcmCmdIfCb != NULL);
            hProxyServer->getMcmCmdIfCb(enetType, &hMcmCmdIf);
            EnetAppUtils_assert(hMcmCmdIf != NULL);
            status = CPSWPROXYSERVER_SOK;
        }
    }

    if (CPSWPROXYSERVER_SOK == status)
    {
        EnetAppUtils_assert(hMcmCmdIf->hMboxCmd != NULL);
        EnetAppUtils_assert(hMcmCmdIf->hMboxResponse != NULL);

        EnetMcm_acquireHandleInfo(hMcmCmdIf, &handleInfo);
        EnetMcm_coreAttach(hMcmCmdIf, host_id, &attachInfo);

        *pId = (uint64_t)(handleInfo.hEnet);
        *pCoreKey = attachInfo.coreKey;
        *pRxMtu = attachInfo.rxMtu;
        EnetAppUtils_assert(txMtuArraySize ==
                            ENET_ARRAYSIZE(attachInfo.txMtu));
        memcpy(pTxMtu, attachInfo.txMtu, sizeof(attachInfo.txMtu));
        *pFeatures = 0;
        ENET_IOCTL_SET_OUT_ARGS(&prms, &csumOffloadFlag);
        status = Enet_ioctl(handleInfo.hEnet,
                            host_id,
                            ENET_HOSTPORT_IS_CSUM_OFFLOAD_ENABLED,
                            &prms);

        EnetAppUtils_assert(status == ENET_SOK);

        if (csumOffloadFlag)
        {
            *pFeatures |= RPMSG_KDRV_TP_ETHSWITCH_FEATURE_TXCSUM;
        }

        if (isMacPort)
        {
            *pFeatures |= RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MAC_ONLY;
            *pMacOnlyPort = EthRemoteCfg_getPortNum(virtPort);
        }
        else
        {
            *pFeatures |= RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MC_FILTER;
            *pMacOnlyPort = 0U;
        }
    }

    if (CPSWPROXYSERVER_SOK == status)
    {
        status = EnetAppUtils_allocRxFlow(handleInfo.hEnet,
                                          attachInfo.coreKey,
                                          host_id,
                                          &start_flow_idx,
                                          &flow_idx_offset);
        if (ENET_SOK == status)
        {
            CpswProxyServer_validateStartIdx(handleInfo.hEnet, host_id, start_flow_idx);
            *pAllocFlowIdx = start_flow_idx + flow_idx_offset;
        }
    }

    if (CPSWPROXYSERVER_SOK == status)
    {
        status = EnetAppUtils_allocTxCh(handleInfo.hEnet,
                                        attachInfo.coreKey,
                                        host_id,
                                        pTxCpswPsilDstId);
    }

    if (CPSWPROXYSERVER_SOK == status)
    {
        status = EnetAppUtils_allocMac(handleInfo.hEnet,
                                       attachInfo.coreKey,
                                       host_id,
                                       macAddress);
    }

    if (status == CPSWPROXYSERVER_SOK)
    {
        CpswProxyServer_addHandleEntry(&hProxyServer->handleTbl, handleInfo.hEnet, enetType, hMcmCmdIf);
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static void CpswProxyServer_clientNotifyHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                  uint32_t host_id,
                                                  uint64_t handle,
                                                  uint32_t core_key,
                                                  enum rpmsg_kdrv_ethswitch_client_notify_type notifyid,
                                                  uint8_t *notify_info,
                                                  uint32_t notify_info_len)
{
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_IoctlPrms prms;
    Enet_Type enetType;
    int32_t status;
    CpswProxyServer_Obj *hProxyServer;
#define STRINGIFY(x) # x
#define XSTRINGIFY(x) STRINGIFY(x)
    char *notify_type_str[] = {XSTRINGIFY(RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_DUMPSTATS),
                               XSTRINGIFY(RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_CUSTOM)};

    EnetAppUtils_assert(notifyid < ENET_ARRAYSIZE(notify_type_str));
    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x,NotifyId:%s,NotifyLen\n",
                 __func__, host_id, core_key, hEnet, notify_type_str[notifyid], notify_info_len);
    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
    status = CpswProxyServer_getCpswType(&hProxyServer->handleTbl, hEnet, &enetType);
    EnetAppUtils_assert(CPSWPROXYSERVER_SOK == status);

    switch (notifyid)
    {
        case RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_DUMPSTATS:
        {
            int32_t status;

            CpswProxyServer_validateHandle(hEnet);

            ENET_IOCTL_SET_NO_ARGS(&prms);
            status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_DUMP_TABLE,
                                &prms);
            EnetAppUtils_assert(status == ENET_SOK);

            ENET_IOCTL_SET_NO_ARGS(&prms);
            status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_DUMP_POLICER_ENTRIES,
                                &prms);

            EnetAppUtils_assert(status == ENET_SOK);

            CpswProxyServer_printStats(hEnet, enetType, host_id);
            break;
        }
        case RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_CUSTOM:
        {
            CpswProxyServer_validateHandle(hEnet);

            if (hProxyServer->notifyCb != NULL)
            {
                hProxyServer->notifyCb(host_id, hEnet, enetType, core_key, notifyid, notify_info, notify_info_len);
            }
            break;
        }
        default:
            /* unhandled notify.do nothing */
            break;
    }
}

static void  CpswProxyServer_initDeviceDataHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                     uint32_t host_id,
                                                     struct rpmsg_kdrv_ethswitch_device_data *eth_dev_data)
{
    CpswProxyServer_Obj *hProxyServer;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
    EnetAppUtils_assert(hProxyServer->initEthfwDeviceDataCb != NULL);
    hProxyServer->initEthfwDeviceDataCb(host_id, eth_dev_data);
}

static int32_t CpswProxyServer_registerEthertypeHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                          uint32_t host_id,
                                                          uint64_t handle,
                                                          uint32_t core_key,
                                                          u16 ether_type,
                                                          uint32_t flow_idx)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    uint32_t start_flow_idx, flow_idx_offset;
    Enet_IoctlPrms prms;
    CpswAle_SetPolicerEntryOutArgs setPolicerOutArgs;
    CpswAle_SetPolicerEntryInArgs setPolicerInArgs;
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);

    if (isSwitchPort)
    {
        CpswProxyServer_validateHandle(hEnet);
        EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);
        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, Ethertype:%x, FlowIdx:%u, FlowIdxOffset:%u\n",
                     __func__,
                     host_id,
                     hEnet,
                     core_key,
                     ether_type,
                     flow_idx,
                     flow_idx_offset);

        memset(&setPolicerInArgs, 0, sizeof(setPolicerInArgs));
        setPolicerInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_ETHERTYPE;
        setPolicerInArgs.policerMatch.etherType = ether_type;
        setPolicerInArgs.threadIdEn = TRUE;
        setPolicerInArgs.threadId   = flow_idx_offset;
        setPolicerInArgs.peakRateInBitsPerSec   = 0;
        setPolicerInArgs.commitRateInBitsPerSec = 0;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &setPolicerInArgs, &setPolicerOutArgs);

        status = Enet_ioctl(hEnet,host_id, CPSW_ALE_IOCTL_SET_POLICER, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("Enet_ioctl() failed CPSW_ALE_IOCTL_SET_POLICER: %d\n", status);
        }
    }
    else
    {
        appLogPrintf("registerEtherType is not supported on virtual MAC ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_unregisterEthertypeHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                            uint32_t host_id,
                                                            uint64_t handle,
                                                            uint32_t core_key,
                                                            u16 ether_type,
                                                            uint32_t flow_idx)
{
    int32_t status;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    uint32_t start_flow_idx, flow_idx_offset;
    Enet_IoctlPrms prms;
    CpswAle_DelPolicerEntryInArgs delPolicerInArgs;
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPort);

    if (isSwitchPort)
    {
        CpswProxyServer_validateHandle(hEnet);
        EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);
        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, Ethertype:%x, FlowIdx:%u, FlowIdOffset:%u\n",
                     __func__,
                     host_id,
                     hEnet,
                     core_key,
                     ether_type,
                     flow_idx,
                     flow_idx_offset);

        memset(&delPolicerInArgs, 0, sizeof(delPolicerInArgs));
        delPolicerInArgs.policerMatch.policerMatchEnMask = CPSW_ALE_POLICER_MATCH_ETHERTYPE;
        delPolicerInArgs.policerMatch.etherType = ether_type;
        delPolicerInArgs.aleEntryMask = CPSW_ALE_POLICER_TABLEENTRY_DELETE_ETHERTYPE;

        ENET_IOCTL_SET_IN_ARGS(&prms, &delPolicerInArgs);

        status = Enet_ioctl(hEnet,host_id, CPSW_ALE_IOCTL_DEL_POLICER, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed Enet_ioctl CPSW_ALE_IOCTL_DEL_POLICER : %d\n", status);
        }
    }
    else
    {
        appLogPrintf("unregisterEtherType is not supported on virtual MAC ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_registerRemoteTimerHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                            uint32_t host_id,
                                                            uint8_t *name,
                                                            uint64_t handle,
                                                            uint32_t core_key,
                                                            uint8_t timer_id,
                                                            uint8_t hwPushNum)
{
    int32_t status = ENET_SOK;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_IoctlPrms prms;
    CpswCpts_RegisterHwPushCbInArgs hwPushCbInArgs;
    Enet_Type enetType;
    CpswProxyServer_Obj *hProxyServer;
    uint32_t hwPushNorm = CPSW_CPTS_HWPUSH_NORM((CpswCpts_HwPush)hwPushNum);
    uint32_t instId = 0U;

    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, Name:%s, Timer:%d, PushNum:%u\n",
                 __func__,
                 host_id,
                 hEnet,
                 core_key,
                 name,
                 timer_id,
                 hwPushNum);

    if (hwPushNum >= CPSW_CPTS_HWPUSH_COUNT_MAX)
    {
        status = ENET_EINVALIDPARAMS;
    }

    if (status == ENET_SOK)
    {
        hProxyServer = CpswProxyServer_getHandle();
        EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
        status = CpswProxyServer_getCpswType(&hProxyServer->handleTbl, hEnet, &enetType);
    }

    /* Register hardware push callback */
    if (status == ENET_SOK)
    {
        hwPushCbInArgs.hwPushNum = (CpswCpts_HwPush)hwPushNum;
        hwPushCbInArgs.hwPushNotifyCb = CpswProxyServer_hwPushNotifyFxn;
        hwPushCbInArgs.hwPushNotifyCbArg = (void *)hProxyServer;
        ENET_IOCTL_SET_IN_ARGS(&prms, &hwPushCbInArgs);
        status = Enet_ioctl(hEnet,
                            host_id,
                            CPSW_CPTS_IOCTL_REGISTER_HWPUSH_CALLBACK,
                            &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed Enet_ioctl CPSW_CPTS_IOCTL_REGISTER_HWPUSH_CALLBACK : %d\n", status);
        }
    }

    /* Configure timesync router */
    if (status == ENET_SOK)
    {
        status = EnetAppUtils_setTimeSyncRouter(enetType,
                                                instId,
                                                timer_id,
                                                hwPushNorm + CPSWPROXY_CPSW9G_HWPUSH_BASE);
    }

    if (status == ENET_SOK)
    {
        hProxyServer->notifyServiceObj.hwPush2CoreIdMap[hwPushNorm] = host_id;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_unregisterRemoteTimerHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                              uint32_t host_id,
                                                              uint8_t *name,
                                                              uint64_t handle,
                                                              uint32_t core_key,
                                                              uint8_t hwPushNum)
{
    int32_t status = ENET_SOK;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_IoctlPrms prms;
    Enet_Type enetType;
    CpswProxyServer_Obj *hProxyServer;
    uint32_t hwPushNorm = CPSW_CPTS_HWPUSH_NORM((CpswCpts_HwPush)hwPushNum);
    uint32_t instId = 0U;

    if (hwPushNum >= CPSW_CPTS_HWPUSH_COUNT_MAX)
    {
        status = ENET_EINVALIDPARAMS;
    }

    if (status == ENET_SOK)
    {
        hProxyServer = CpswProxyServer_getHandle();
        EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));
        status = CpswProxyServer_getCpswType(&hProxyServer->handleTbl, hEnet, &enetType);
    }

    /* Unregister hardware push callback */
    if (status == ENET_SOK)
    {
        hwPushNum = (CpswCpts_HwPush)hwPushNum;
        ENET_IOCTL_SET_IN_ARGS(&prms, &hwPushNum);
        status = Enet_ioctl(hEnet,
                            host_id,
                            CPSW_CPTS_IOCTL_UNREGISTER_HWPUSH_CALLBACK,
                            &prms);
    }

    /* Clear timesync router configuration for hardware push,
     * Note: This assumes input signal is stopped */
    if (status == ENET_SOK)
    {
        status = EnetAppUtils_setTimeSyncRouter(enetType,
                                                instId,
                                                0U,
                                                hwPushNorm + CPSWPROXY_CPSW9G_HWPUSH_BASE);
    }

    if (status == ENET_SOK)
    {
        /* Use IPC_MAX_PROCS as invalid core id */
        hProxyServer->notifyServiceObj.hwPush2CoreIdMap[hwPushNorm] = IPC_MAX_PROCS;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_setPromiscModeHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                       uint32_t host_id,
                                                       uint64_t handle,
                                                       uint32_t core_key,
                                                       uint32_t enable)
{
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    Enet_MacPort macPort;
    Enet_IoctlPrms prms;
    bool isMacPort = EthRemoteCfg_isMacPort(virtPort);
    uint32_t cmd;
    int32_t status = ENET_SOK;

    if (isMacPort)
    {
        CpswProxyServer_validateHandle(hEnet);

        appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x,mode:%s\n",
                     __func__,
                     host_id,
                     hEnet,
                     core_key,
                     enable ? "enable":"disable");

        macPort = EthRemoteCfg_getMacPort(virtPort);
        ENET_IOCTL_SET_IN_ARGS(&prms, &macPort);

        cmd = (enable != 0U) ? CPSW_ALE_IOCTL_ENABLE_PROMISC_MODE : CPSW_ALE_IOCTL_DISABLE_PROMISC_MODE;
        status = Enet_ioctl(hEnet, host_id, cmd, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("setPromiscModeHandleCb() virt MAC port %u: failed to set promisc mode: %d\n",
                         ENET_MACPORT_ID(macPort), status);
        }
    }
    else
    {
        appLogPrintf("setPromiscMode is not supported on virtual switch ports\n");
        status = CPSWPROXYSERVER_ENOTSUPPORTED;
    }

    return CPSWPROXY_ENET2RPMSG_ERR(status);
}

static int32_t CpswProxyServer_filterAddMacExcl(EthRemoteCfg_VirtPort virtPort,
                                                Enet_Handle hEnet,
                                                uint32_t host_id,
                                                uint8_t *mac_address,
                                                uint16_t vlan_id,
                                                uint32_t flow_idx_offset)
{
    CpswProxyServer_Obj *hProxyServer;
    Enet_IoctlPrms prms;
    CpswAle_GetMcastEntryInArgs lookupInArgs;
    CpswAle_GetMcastEntryOutArgs lookupOutArgs;
    CpswAle_SetMcastEntryInArgs mcastInArgs;
    CpswAle_SetPolicerEntryInArgs polInArgs;
    CpswAle_SetPolicerEntryOutArgs polOutArgs;
    Enet_MacPort macPort = EthRemoteCfg_getMacPort(virtPort);
    bool isMacPort = EthRemoteCfg_isMacPort(virtPort);
    uint32_t entry;
    int32_t status;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));

    /* Lookup for multicast address */
    lookupInArgs.addr.vlanId = vlan_id;
    EnetUtils_copyMacAddr(&lookupInArgs.addr.addr[0], mac_address);
    lookupInArgs.numIgnBits = 0U;

    ENET_IOCTL_SET_INOUT_ARGS(&prms, &lookupInArgs, &lookupOutArgs);

    status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_LOOKUP_MCAST, &prms);
    if (status == ENET_SOK)
    {
        /* Multicast address already requested, with requestor having exclusive access.
         * Reject new caller */
        status = CPSWPROXYSERVER_EBUSY;
    }
    else if (status == ENET_ENOTFOUND)
    {
        /* No one has requested this multicas address, caller gets it */
        status = CPSWPROXYSERVER_SOK;
    }
    else
    {
        appLogPrintf("Failed to lookup mcast entry: %d\n", status);
    }

    /* Add multicast entry */
    if (status == CPSWPROXYSERVER_SOK)
    {
        mcastInArgs.addr.vlanId = vlan_id;
        EnetUtils_copyMacAddr(&mcastInArgs.addr.addr[0], mac_address);

        mcastInArgs.info.super    = false;
        mcastInArgs.info.fwdState = CPSW_ALE_FWDSTLVL_FWD;
        mcastInArgs.info.portMask = CPSW_ALE_HOST_PORT_MASK;
        mcastInArgs.info.numIgnBits = 0U;

        if (isMacPort)
        {
            mcastInArgs.info.portMask |= CPSW_ALE_MACPORT_TO_PORTMASK(macPort);
        }
        else
        {
            mcastInArgs.info.portMask |= (hProxyServer->alePortMask &
                                          ~hProxyServer->aleMacOnlyPortMask);
        }

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &mcastInArgs, &entry);

        status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_ADD_MCAST, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed to add mcast entry: %d\n", status);
        }
    }

    /* Setup classifier */
    if (status == CPSWPROXYSERVER_SOK)
    {
        polInArgs.policerMatch.policerMatchEnMask = 0U;

        /* Multicast MAC address as match criteria */
        polInArgs.policerMatch.policerMatchEnMask |= CPSW_ALE_POLICER_MATCH_MACDST;
        polInArgs.policerMatch.dstMacAddrInfo.portNum = CPSW_ALE_HOST_PORT_NUM;
        polInArgs.policerMatch.dstMacAddrInfo.addr.vlanId = vlan_id;
        EnetUtils_copyMacAddr(&polInArgs.policerMatch.dstMacAddrInfo.addr.addr[0], mac_address);

        /* Ingress port as match criteria to fully qualify the classifier for
         * virtual MAC ports as directed packets will be used and could hit i2148 errata */
        if (isMacPort)
        {
            polInArgs.policerMatch.policerMatchEnMask |= CPSW_ALE_POLICER_MATCH_PORT;
            polInArgs.policerMatch.portNum = CPSW_ALE_MACPORT_TO_ALEPORT(macPort);
            polInArgs.policerMatch.portIsTrunk = false;
        }

        polInArgs.threadIdEn = true;
        polInArgs.threadId   = flow_idx_offset;
        polInArgs.peakRateInBitsPerSec   = 0U;
        polInArgs.commitRateInBitsPerSec = 0U;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &polInArgs, &polOutArgs);

        status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_SET_POLICER, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("Failed to setup ALE classifier: %d\n", status);
        }
    }

    return status;
}

static int32_t CpswProxyServer_filterDelMacExcl(EthRemoteCfg_VirtPort virtPort,
                                                Enet_Handle hEnet,
                                                uint32_t host_id,
                                                uint8_t *mac_address,
                                                uint16_t vlan_id)
{
    CpswProxyServer_Obj *hProxyServer;
    Enet_IoctlPrms prms;
    CpswAle_DelPolicerEntryInArgs polInArgs;
    Enet_MacPort macPort = EthRemoteCfg_getMacPort(virtPort);
    bool isMacPort = EthRemoteCfg_isMacPort(virtPort);
    int32_t status;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));

    polInArgs.policerMatch.policerMatchEnMask = 0U;

    /* Multicast MAC address as match criteria */
    polInArgs.policerMatch.policerMatchEnMask |= CPSW_ALE_POLICER_MATCH_MACDST;
    polInArgs.policerMatch.dstMacAddrInfo.portNum = CPSW_ALE_HOST_PORT_NUM;
    polInArgs.policerMatch.dstMacAddrInfo.addr.vlanId = vlan_id;
    EnetUtils_copyMacAddr(&polInArgs.policerMatch.dstMacAddrInfo.addr.addr[0], mac_address);

    /* Ingress port as match criteria to fully qualify the classifier for
     * virtual MAC ports as directed packets will be used and could hit i2148 errata */
    if (isMacPort)
    {
        polInArgs.policerMatch.policerMatchEnMask |= CPSW_ALE_POLICER_MATCH_PORT;
        polInArgs.policerMatch.portNum = CPSW_ALE_MACPORT_TO_ALEPORT(macPort);
        polInArgs.policerMatch.portIsTrunk = false;
    }

    polInArgs.aleEntryMask = CPSW_ALE_POLICER_TABLEENTRY_DELETE_ALL;

    ENET_IOCTL_SET_IN_ARGS(&prms, &polInArgs);

    status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_DEL_POLICER, &prms);
    if (status != ENET_SOK)
    {
        appLogPrintf("Failed to delete ALE classifier: %d\n", status);
    }

    return status;
}

static int32_t CpswProxyServer_filterAddMacShared(CpswProxyServer_Obj *hProxyServer,
                                                  Enet_Handle hEnet,
                                                  CpswProxyServer_SharedMcastEntry *entry,
                                                  uint16_t vlan_id,
                                                  uint8_t host_id)
{
    Enet_IoctlPrms prms;
    CpswAle_SetMcastEntryInArgs mcastInArgs;
    uint8_t coreId = EnetSoc_getCoreId();
    uint32_t aleEntry;
    int32_t status = CPSWPROXYSERVER_SOK;

    /* Add multicast entry in ALE table */
    if (entry->refCnt == 0U)
    {
        mcastInArgs.addr.vlanId = vlan_id;
        EnetUtils_copyMacAddr(&mcastInArgs.addr.addr[0], &entry->macAddr[0U]);

        mcastInArgs.info.super    = false;
        mcastInArgs.info.fwdState = CPSW_ALE_FWDSTLVL_FWD;
        mcastInArgs.info.portMask = CPSW_ALE_HOST_PORT_MASK;
        mcastInArgs.info.numIgnBits = 0U;

        ENET_IOCTL_SET_INOUT_ARGS(&prms, &mcastInArgs, &aleEntry);

        status = Enet_ioctl(hEnet, coreId, CPSW_ALE_IOCTL_ADD_MCAST, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("%s: Failed to add shared mcast entry in ALE: %d\n", __func__, status);
        }
    }

    /* Increase reference counter and call 'add' callback */
    if (status == CPSWPROXYSERVER_SOK)
    {
        entry->refCnt++;
        if (hProxyServer->filterAddMacSharedCb != NULL)
        {
            hProxyServer->filterAddMacSharedCb(&entry->macAddr[0U], host_id);
        }
    }

    return status;
}

static int32_t CpswProxyServer_filterDelMacShared(CpswProxyServer_Obj *hProxyServer,
                                                  Enet_Handle hEnet,
                                                  CpswProxyServer_SharedMcastEntry *entry,
                                                  uint16_t vlan_id,
                                                  uint8_t host_id)
{
    Enet_IoctlPrms prms;
    CpswAle_MacAddrInfo macAddrInfo;
    uint8_t coreId = EnetSoc_getCoreId();
    int32_t status = CPSWPROXYSERVER_SOK;

    /* Remove mcast address from ALE table */
    if (entry->refCnt == 1U)
    {
        macAddrInfo.vlanId = vlan_id;
        EnetUtils_copyMacAddr(&macAddrInfo.addr[0U], &entry->macAddr[0U]);

        ENET_IOCTL_SET_IN_ARGS(&prms, &macAddrInfo);

        status = Enet_ioctl(hEnet, host_id, CPSW_ALE_IOCTL_REMOVE_ADDR, &prms);
        if (status != ENET_SOK)
        {
            appLogPrintf("%s: Failed to remove shared mcast entry in ALE: %d\n", __func__, status);
        }
    }
    else if (entry->refCnt == 0U)
    {
        appLogPrintf("Shared multicast address not in use, cannot be deleted\n");
        status = CPSWPROXYSERVER_EFAIL;
    }
    else
    {
        /* Nothing to do */
    }

    if (status == CPSWPROXYSERVER_SOK)
    {
        entry->refCnt--;
        if (hProxyServer->filterDelMacSharedCb != NULL)
        {
            hProxyServer->filterDelMacSharedCb(&entry->macAddr[0U], host_id);
        }
    }

    return status;
}

static bool CpswProxyServer_isRsvdMcast(CpswProxyServer_Obj *hProxyServer,
                                        const uint8_t *mac_address)

{
    uint32_t i;
    bool isRsvd = false;

    for (i = 0U; i < hProxyServer->rsvdMcastTbl.numMacAddr; i++)
    {
        if (EnetUtils_cmpMacAddr(&hProxyServer->rsvdMcastTbl.macAddrList[i][0U], mac_address))
        {
            appLogPrintf("%s: Reserved mcast cannot be added to filter\n", __func__);
            isRsvd = true;
            break;
        }
    }

    return isRsvd;
}

static CpswProxyServer_SharedMcastEntry *CpswProxyServer_getSharedMcastEntry(CpswProxyServer_Obj *hProxyServer,
                                                                             const uint8_t *mac_address)
{
    CpswProxyServer_SharedMcastTable *table = &hProxyServer->sharedMcastTbl;
    CpswProxyServer_SharedMcastEntry *entry = NULL;
    uint32_t i;

    for (i = 0U; i < table->len; i++)
    {
        if (EnetUtils_cmpMacAddr(&table->entry[i].macAddr[0U], mac_address))
        {
            entry = &table->entry[i];
            break;
        }
    }

    return entry;
}

static int32_t CpswProxyServer_filterAddMacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                     uint32_t host_id,
                                                     uint64_t handle,
                                                     uint32_t core_key,
                                                     uint8_t *mac_address,
                                                     uint16_t vlan_id,
                                                     uint32_t flow_idx)
{
    CpswProxyServer_Obj *hProxyServer;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    uint32_t start_flow_idx, flow_idx_offset;
    int32_t status = CPSWPROXYSERVER_SOK;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));

    CpswProxyServer_validateHandle(hEnet);
    EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);
    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x, vlanId:%u, FlowIdx:%u, FlowIdOffset:%u\n",
                 __func__,
                 host_id,
                 hEnet,
                 core_key,
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5],
                 vlan_id,
                 flow_idx,
                 flow_idx_offset);

    if (!EnetUtils_isMcastAddr(mac_address))
    {
        appLogPrintf("Addr is not multicast, cannot add to filter\n");
        status = CPSWPROXYSERVER_EINVALIDPARAMS;
    }

    if ((status == CPSWPROXYSERVER_SOK) &&
        !CpswProxyServer_isRsvdMcast(hProxyServer, mac_address))
    {
        CpswProxyServer_SharedMcastEntry *sharedMcastEntry;

        if (vlan_id == RPMSG_KDRV_TP_ETHSWITCH_VLAN_USE_DFLT)
        {
            vlan_id = hProxyServer->dfltVlanIdSwitchPorts;
        }

        sharedMcastEntry = CpswProxyServer_getSharedMcastEntry(hProxyServer, mac_address);
        if (sharedMcastEntry != NULL)
        {
            status = CpswProxyServer_filterAddMacShared(hProxyServer, hEnet, sharedMcastEntry, vlan_id, host_id);
            if (status != CPSWPROXYSERVER_SOK)
            {
                appLogPrintf("Failed to add multicast (shared): %d\n", status);
            }
        }
        else
        {
            status = CpswProxyServer_filterAddMacExcl(virtPort, hEnet, host_id, mac_address, vlan_id, flow_idx_offset);
            if (status != CPSWPROXYSERVER_SOK)
            {
                appLogPrintf("Failed to add multicast (exclusive): %d\n", status);
            }
        }
    }

    return status;
}

static int32_t CpswProxyServer_filterDelMacHandlerCb(EthRemoteCfg_VirtPort virtPort,
                                                     uint32_t host_id,
                                                     uint64_t handle,
                                                     uint32_t core_key,
                                                     uint8_t *mac_address,
                                                     uint16_t vlan_id,
                                                     uint32_t flow_idx)
{
    CpswProxyServer_Obj *hProxyServer;
    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)handle);
    uint32_t start_flow_idx, flow_idx_offset;
    int32_t status = CPSWPROXYSERVER_SOK;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));

    CpswProxyServer_validateHandle(hEnet);
    EnetAppUtils_absFlowIdx2FlowIdxOffset(hEnet, host_id, flow_idx, &start_flow_idx, &flow_idx_offset);
    appLogPrintf("Function:%s,HostId:%u,Handle:%p,CoreKey:%x, MacAddress:%x:%x:%x:%x:%x:%x, vlanId:%u, FlowIdx:%u, FlowIdOffset:%u\n",
                 __func__,
                 host_id,
                 hEnet,
                 core_key,
                 mac_address[0],
                 mac_address[1],
                 mac_address[2],
                 mac_address[3],
                 mac_address[4],
                 mac_address[5],
                 vlan_id,
                 flow_idx,
                 flow_idx_offset);

    if (!EnetUtils_isMcastAddr(mac_address))
    {
        appLogPrintf("Addr is not multicast, cannot delete from filter\n");
        status = CPSWPROXYSERVER_EINVALIDPARAMS;
    }

    if ((status == CPSWPROXYSERVER_SOK) &&
        !CpswProxyServer_isRsvdMcast(hProxyServer, mac_address))
    {
        CpswProxyServer_SharedMcastEntry *sharedMcastEntry;

        if (vlan_id == RPMSG_KDRV_TP_ETHSWITCH_VLAN_USE_DFLT)
        {
            vlan_id = hProxyServer->dfltVlanIdSwitchPorts;
        }

        sharedMcastEntry = CpswProxyServer_getSharedMcastEntry(hProxyServer, mac_address);
        if (sharedMcastEntry != NULL)
        {
            status = CpswProxyServer_filterDelMacShared(hProxyServer, hEnet, sharedMcastEntry, vlan_id, host_id);
            if (status != CPSWPROXYSERVER_SOK)
            {
                appLogPrintf("Failed to remove multicast (shared): %d\n", status);
            }
        }
        else
        {
            status = CpswProxyServer_filterDelMacExcl(virtPort, hEnet, host_id, mac_address, vlan_id);
            if (status != CPSWPROXYSERVER_SOK)
            {
                appLogPrintf("Failed to remove multicast (exclusive): %d\n", status);
            }
        }
    }

    return status;
}

static void CpswProxyServer_setRemoteParams(const CpswProxyServer_VirtPortCfg *virtPortCfg,
                                            rdevEthSwitchServerInstPrm_t *prm)
{
    const char *coreName[] = {
        [IPC_MPU1_0] = "mpu_1_0",
        [IPC_MCU1_0] = "mcu_1_0",
        [IPC_MCU1_1] = "mcu_1_1",
        [IPC_MCU2_0] = "mcu_2_0",
        [IPC_MCU2_1] = "mcu_2_1",
#if defined (SOC_J721E) || defined(SOC_J784S4)
        [IPC_MCU3_0] = "mcu_3_0",
        [IPC_MCU3_1] = "mcu_3_1",
#endif
    };
    uint32_t portNum = EthRemoteCfg_getPortNum(virtPortCfg->portId);
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(virtPortCfg->portId);

    prm->host_id  = virtPortCfg->remoteCoreId;
    prm->virtPort = virtPortCfg->portId;

    snprintf((char *)&prm->name[0],
             ETHREMOTECFG_SERVER_MAX_NAME_LEN,
             "%s_eth%s-device-%u",
             coreName[virtPortCfg->remoteCoreId],
             isSwitchPort ? "switch" : "mac",
             portNum);

    appLogPrintf("  %s <-> %s port %u: %s\n",
                 coreName[virtPortCfg->remoteCoreId],
                 isSwitchPort ? "Switch" : "MAC",
                 portNum,
                 prm->name);
}

static rdevEthSwitchServerCbFxn_t CpswProxyRdevEthSwitchServerCbFxnTbl =
{
    .attach_handler                 = CpswProxyServer_attachHandlerCb,
    .attach_ext_handler             = CpswProxyServer_attachExtHandlerCb,
    .alloc_tx_handler               = CpswProxyServer_allocTxHandlerCb,
    .alloc_rx_handler               = CpswProxyServer_allocRxHandlerCb,
    .alloc_mac_handler              = CpswProxyServer_allocMacHandlerCb,
    .register_mac_handler           = CpswProxyServer_registerMacHandlerCb,
    .unregister_mac_handler         = CpswProxyServer_unregisterMacHandlerCb,
    .register_rx_default_handler    = CpswProxyServer_registerRxDefaultHandlerCb,
    .unregister_rx_default_handler  = CpswProxyServer_unregisterRxDefaultHandlerCb,
    .free_tx_handler                = CpswProxyServer_freeTxHandlerCb,
    .free_rx_handler                = CpswProxyServer_freeRxHandlerCb,
    .free_mac_handler               = CpswProxyServer_freeMacHandlerCb,
    .detach_handler                 = CpswProxyServer_detachHandlerCb,
    .ioctl_handler                  = CpswProxyServer_ioctlHandlerCb,
    .regwr_handler                  = CpswProxyServer_regwrHandlerCb,
    .regrd_handler                  = CpswProxyServer_regrdHandlerCb,
    .ipv4_register_mac_handler      = CpswProxyServer_registerIpv4MacHandlerCb,
    .ipv6_register_mac_handler      = CpswProxyServer_registerIpv6MacHandlerCb,
    .ipv4_unregister_mac_handler    = CpswProxyServer_unregisterIpv4MacHandlerCb,
    .client_notify_handler          = CpswProxyServer_clientNotifyHandlerCb,
    .init_device_data_handler       = CpswProxyServer_initDeviceDataHandlerCb,
    .register_ethertype_handler     = CpswProxyServer_registerEthertypeHandlerCb,
    .unregister_ethertype_handler   = CpswProxyServer_unregisterEthertypeHandlerCb,
    .register_remotetimer_handler   = CpswProxyServer_registerRemoteTimerHandlerCb,
    .unregister_remotetimer_handler = CpswProxyServer_unregisterRemoteTimerHandlerCb,
    .set_promisc_mode_handler       = CpswProxyServer_setPromiscModeHandlerCb,
    .filter_add_mac_handler         = CpswProxyServer_filterAddMacHandlerCb,
    .filter_del_mac_handler         = CpswProxyServer_filterDelMacHandlerCb,
};

void CpswProxyServer_getMacPortMask(CpswProxyServer_Obj *hProxyServer,
                                    const CpswProxyServer_Config_t *cfg)
{
    EthRemoteCfg_VirtPort virtPort;
    Enet_MacPort macPort;
    uint32_t i;

    hProxyServer->alePortMask = 0U;
    hProxyServer->aleMacOnlyPortMask = 0U;

    for (i = 0U; i < cfg->numMacPorts; i++)
    {
        macPort = cfg->macPort[i];
        hProxyServer->alePortMask |= CPSW_ALE_MACPORT_TO_PORTMASK(macPort);
    }

    for (i = 0U; i < cfg->numVirtPorts; i++)
    {
        virtPort = cfg->virtPortCfg[i].portId;

        if (EthRemoteCfg_isMacPort(virtPort))
        {
            macPort = EthRemoteCfg_getMacPort(virtPort);
            hProxyServer->aleMacOnlyPortMask |= CPSW_ALE_MACPORT_TO_PORTMASK(macPort);
        }
    }

    /* TODO - Check for AUTOSAR virtual port configuration.
     * Currently, it's virtual switch port */
}

int32_t CpswProxyServer_init(CpswProxyServer_Config_t *cfg)
{
    SemaphoreP_Params sem_params;
    CpswProxyServer_Obj * hProxyServer;
    app_remote_device_init_prm_t remote_dev_init_prm;
    rdevEthSwitchServerInitPrm_t remote_ethswitch_init_prm;
    rdevEthSwitchServerInstPrm_t *inst;
    CpswProxyServer_RsvdMcastCfg *rsvdMcastCfg;
    CpswProxyServer_SharedMcastCfg *sharedMcastCfg;
    CpswProxyServer_SharedMcastEntry *entry;
    int32_t i;
    int32_t status = CPSWPROXYSERVER_SOK;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == false));

    hProxyServer->dfltVlanIdMacOnlyPorts = cfg->dfltVlanIdMacOnlyPorts;
    hProxyServer->dfltVlanIdSwitchPorts  = cfg->dfltVlanIdSwitchPorts;

    CpswProxyServer_getMacPortMask(hProxyServer, cfg);

    if ((hProxyServer->aleMacOnlyPortMask & hProxyServer->alePortMask) !=
        hProxyServer->aleMacOnlyPortMask)
    {
        appLogPrintf("CpswProxyServer: MAC ports required for virtual MAC ports are not enabled\r\n");
        status = CPSWPROXYSERVER_EINVALIDPARAMS;
    }

    if (status == CPSWPROXYSERVER_SOK)
    {
        sharedMcastCfg = &cfg->sharedMcastCfg;

        if (sharedMcastCfg->numMacAddr <= CPSWPROXYSERVER_SHARED_MCAST_LIST_LEN)
        {
            hProxyServer->sharedMcastTbl.len = sharedMcastCfg->numMacAddr;
        }
        else
        {
            hProxyServer->sharedMcastTbl.len = CPSWPROXYSERVER_SHARED_MCAST_LIST_LEN;
        }

        for (i = 0U; i < hProxyServer->sharedMcastTbl.len; i++)
        {
            entry = &hProxyServer->sharedMcastTbl.entry[i];
            entry->refCnt = 0U;
            EnetUtils_copyMacAddr(&entry->macAddr[0U], &sharedMcastCfg->macAddrList[i][0U]);
        }

        hProxyServer->filterAddMacSharedCb = sharedMcastCfg->filterAddMacSharedCb;
        hProxyServer->filterDelMacSharedCb = sharedMcastCfg->filterDelMacSharedCb;
    }

    if (status == CPSWPROXYSERVER_SOK)
    {
        rsvdMcastCfg = &cfg->rsvdMcastCfg;

        memcpy(&hProxyServer->rsvdMcastTbl, rsvdMcastCfg, sizeof(hProxyServer->rsvdMcastTbl));

        if (rsvdMcastCfg->numMacAddr > CPSWPROXYSERVER_RSVD_MCAST_LIST_LEN)
        {
            hProxyServer->rsvdMcastTbl.numMacAddr = CPSWPROXYSERVER_RSVD_MCAST_LIST_LEN;
        }
    }

    if (status == CPSWPROXYSERVER_SOK)
    {
        SemaphoreP_Params_init(&sem_params);
        sem_params.mode = SemaphoreP_Mode_BINARY;
        hProxyServer->rdevStartSem = SemaphoreP_create(0, &sem_params);
        EnetAppUtils_assert(hProxyServer->rdevStartSem != NULL);

        hProxyServer->getMcmCmdIfCb = cfg->getMcmCmdIfCb;
        hProxyServer->initEthfwDeviceDataCb = cfg->initEthfwDeviceDataCb;
        hProxyServer->notifyCb = cfg->notifyCb;
        hProxyServer->handleTbl.numEntries = 0;
        appRemoteDeviceInitParamsInit(&remote_dev_init_prm);

        remote_dev_init_prm.rpmsg_buf_size = CPSWPROXY_RDEV_MSGSIZE;
        remote_dev_init_prm.remote_device_endpt = cfg->rpmsgEndPointId;
        remote_dev_init_prm.wait_sem = hProxyServer->rdevStartSem;

        status = appRemoteDeviceInit(&remote_dev_init_prm);
        EnetAppUtils_assert(status == 0);

        rdevEthSwitchServerInitPrmSetDefault(&remote_ethswitch_init_prm);

        remote_ethswitch_init_prm.rpmsg_buf_size = CPSWPROXY_RDEV_MSGSIZE;
        remote_ethswitch_init_prm.num_instances = cfg->numVirtPorts;
        remote_ethswitch_init_prm.cb = CpswProxyRdevEthSwitchServerCbFxnTbl;

        EnetAppUtils_assert(cfg->numVirtPorts <= ENET_ARRAYSIZE(remote_ethswitch_init_prm.inst_prm));
        EnetAppUtils_assert(cfg->numVirtPorts <= ENET_ARRAYSIZE(cfg->virtPortCfg));

        appLogPrintf("CpswProxyServer: Virtual port configuration:\n");

        for (i = 0U; i < cfg->numVirtPorts; i++)
        {
            inst = &remote_ethswitch_init_prm.inst_prm[i];

            CpswProxyServer_setRemoteParams(&cfg->virtPortCfg[i], inst);
        }

        status = rdevEthSwitchServerInit(&remote_ethswitch_init_prm);
        EnetAppUtils_assert(status == 0);

        status = CpswProxyServer_initAutosarEthDeviceEp(hProxyServer, cfg);
        EnetAppUtils_assert(status == 0);

        status = CpswProxyServer_initNotifyServiceEp(hProxyServer, cfg);
        EnetAppUtils_assert(status == 0);

        hProxyServer->initDone = true;
    }

    appLogPrintf("CpswProxyServer: initialization %s (core: mcu2_0)\r\n",
                 (status == CPSWPROXYSERVER_SOK) ? "completed" : "failed");

    return status;
}

int32_t  CpswProxyServer_start(void)
{
    CpswProxyServer_Obj * hProxyServer;

    hProxyServer = CpswProxyServer_getHandle();
    EnetAppUtils_assert((hProxyServer != NULL) && (hProxyServer->initDone == true));

    SemaphoreP_post(hProxyServer->rdevStartSem);
    return CPSWPROXYSERVER_SOK;
}

static int32_t CpswProxyServer_initAutosarEthDeviceEp(CpswProxyServer_Obj * hProxyServer, CpswProxyServer_Config_t * cfg)
{
    TaskP_Params     taskParams;
    int32_t retVal = CPSWPROXYSERVER_SOK;
    RPMessage_Params comChParam;
    uint32_t  localEp;

    hProxyServer->ethDrvObj.dstProc = cfg->autosarEthDriverRemoteCoreId;
    hProxyServer->ethDrvObj.virtPort = cfg->autosarEthDriverVirtPort;
    RPMessageParams_init(&comChParam);
    comChParam.numBufs = CPSWPROXY_AUTOSAR_ETHDRIVER_NUM_RPMSG_BUFS;
    comChParam.buf = g_CpswProxyServerAutosarRpmsgBuf;
    comChParam.bufSize = sizeof(g_CpswProxyServerAutosarRpmsgBuf);
    comChParam.requestedEndpt = cfg->autosarEthDeviceEndPointId;
    hProxyServer->ethDrvObj.hAutosarEthRpMsgEp = RPMessage_create(&comChParam, &localEp);

    if (NULL == hProxyServer->ethDrvObj.hAutosarEthRpMsgEp)
    {
        appLogPrintf("Could not create communication channel \n");
        retVal = CPSWPROXYSERVER_EFAIL;
    }

    if (CPSWPROXYSERVER_SOK == retVal)
    {
        if (localEp != cfg->autosarEthDeviceEndPointId)
        {
            appLogPrintf("Could not create required End Point");
        }
        else
        {
            hProxyServer->ethDrvObj.localEp = localEp;
        }
    }

    if (CPSWPROXYSERVER_SOK == retVal)
    {
        /* Initialize the task params */
        TaskP_Params_init(&taskParams);
        taskParams.name         = CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_NAME;
        taskParams.priority     = CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_PRIORITY;
        taskParams.arg0         = (void*) hProxyServer;
        taskParams.stack        = &gCpswProxyServer_autosarEthDriverTaskStackBuf[0];
        taskParams.stacksize    = CPSWPROXY_AUTOSAR_ETHDRIVER_TASK_STACK;
        hProxyServer->ethDrvObj.hAutosarEthTsk = TaskP_create(&CpswProxyServer_autosarEthDriverTaskFxn, &taskParams);
        if(hProxyServer->ethDrvObj.hAutosarEthTsk == NULL)
        {
            retVal = CPSWPROXYSERVER_EFAIL;
            appLogPrintf("Could not create a Task \n");
        }
    }

    return retVal;
}

static int32_t CpswProxyServer_initNotifyServiceEp(CpswProxyServer_Obj * hProxyServer, CpswProxyServer_Config_t * cfg)
{
    TaskP_Params     taskParams;
    int32_t retVal = CPSWPROXYSERVER_SOK;
    RPMessage_Params comChParam;
    uint32_t  localEp;
    EventP_Params eventParams;
    uint8_t i = 0;

    hProxyServer->notifyServiceObj.notifyServiceCpswType = cfg->notifyServiceCpswType;
    hProxyServer->notifyServiceObj.dstProcMask = 0U;
    for (i = 0U; i < cfg->numVirtPorts; i++)
    {
        hProxyServer->notifyServiceObj.dstProcMask |= ENET_BIT(cfg->notifyServiceRemoteCoreId[i]);
    }
    for (i = 0U; i < CPSW_CPTS_HWPUSH_COUNT_MAX; i++)
    {
        hProxyServer->notifyServiceObj.hwPush2CoreIdMap[i] = IPC_MAX_PROCS;
    }

    RPMessageParams_init(&comChParam);
    comChParam.numBufs = CPSW_REMOTE_NOTIFY_SERVICE_NUM_RPMSG_BUFS;
    comChParam.buf = g_CpswProxyServerNotifyServiceRpmsgBuf;
    comChParam.bufSize = sizeof(g_CpswProxyServerNotifyServiceRpmsgBuf);
    comChParam.requestedEndpt = CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID;
    hProxyServer->notifyServiceObj.hNotifyServicRpMsgEp = RPMessage_create(&comChParam, &localEp);

    if (NULL == hProxyServer->notifyServiceObj.hNotifyServicRpMsgEp)
    {
        appLogPrintf("Could not create communication channel\n");
        retVal = CPSWPROXYSERVER_EFAIL;
    }

    if (CPSWPROXYSERVER_SOK == retVal)
    {
        if (localEp != CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID)
        {
            appLogPrintf("Could not create required End Point\n");
        }
        else
        {
            hProxyServer->notifyServiceObj.localEp = localEp;
        }
    }

    /* Announce service */
    if (CPSWPROXYSERVER_SOK == retVal)
    {
        retVal = RPMessage_announce(RPMESSAGE_ALL,
                                    CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID,
                                    CPSW_REMOTE_NOTIFY_SERVICE);
    }

    /* Create Event to notify task */
    if (CPSWPROXYSERVER_SOK == retVal)
    {
        EventP_Params_init(&eventParams);

        for (i = 0U; i < CPSW_CPTS_HWPUSH_COUNT_MAX; i++)
        {
            hProxyServer->notifyServiceObj.hwPushNotifyEventId[i] = (1U << i);
        }

        hProxyServer->notifyServiceObj.hHwPushNotifyServiceEvent = EventP_create(&eventParams);

        if (hProxyServer->notifyServiceObj.hHwPushNotifyServiceEvent == NULL)
        {
            retVal = CPSWPROXYSERVER_EFAIL;
            appLogPrintf("Could not create an Event \n");
        }
    }

    if (CPSWPROXYSERVER_SOK == retVal)
    {
        /* Initialize the task params */
        TaskP_Params_init(&taskParams);
        taskParams.name         = CPSW_REMOTE_NOTIFY_SERVICE_TASK_NAME;
        taskParams.priority     = CPSW_REMOTE_NOTIFY_SERVICE_TASK_PRIORITY;
        taskParams.arg0         = (void*) hProxyServer;
        taskParams.stack        = &gCpswProxyServer_notifyServiceTaskStackBuf[0];
        taskParams.stacksize    = CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKSIZE;
        hProxyServer->notifyServiceObj.hNotifyServiceTsk = TaskP_create(&CpswProxyServer_notifyServiceTaskFxn, &taskParams);
        if(hProxyServer->notifyServiceObj.hNotifyServiceTsk == NULL)
        {
            retVal = CPSWPROXYSERVER_EFAIL;
            appLogPrintf("Could not create a Task \n");
        }
    }

    return retVal;
}

static void  CpswProxyServer_initDeviceData(const struct rpmsg_kdrv_ethswitch_device_data *src, Eth_RpcDeviceData *dst)
{
    dst->header.messageId = ETH_RPC_CMD_TYPE_FWINFO_RES;
    dst->header.messageLen = sizeof(*dst);

    dst->uartId = src->uart_id;
    dst->uartConnected = src->uart_connected;
    dst->permissionFlags = src->permission_flags;
    ENET_UTILS_ARRAY_COPY(dst->fwVer.commitHash ,src->fw_ver.commit_hash);
    ENET_UTILS_ARRAY_COPY(dst->fwVer.date , src->fw_ver.date);
    dst->fwVer.major = src->fw_ver.major;
    dst->fwVer.minor = src->fw_ver.minor;
    ENET_UTILS_ARRAY_COPY(dst->fwVer.month , src->fw_ver.month);
    dst->fwVer.rev = src->fw_ver.rev;
    memcpy(dst->fwVer.year , src->fw_ver.year, sizeof(dst->fwVer.year));
}



static void CpswProxyServer_autosarEthDriverTaskFxn(void* arg0, void* arg1)
{
    int32_t rtnVal = IPC_SOK;
    uint32_t remoteProcId, remoteEndPt;
    CpswProxyServer_Obj * hProxyServer = (CpswProxyServer_Obj *)arg0;
    EthRemoteCfg_VirtPort virtPort = hProxyServer->ethDrvObj.virtPort;
    uint32_t remoteProc, remoteEp;
    uint16_t len;
    uint64_t msgBuffer[(CPSWPROXY_AUTOSAR_ETHDRIVER_MSG_SIZE / sizeof(uint64_t))];


    /* Wait for Remote EP to active */
    if (IPC_SOK != RPMessage_getRemoteEndPt(hProxyServer->ethDrvObj.dstProc,
                                            ETH_RPC_REMOTE_SERVICE,
                                            &remoteProcId,
                                            &remoteEndPt,
                                            osal_WAIT_FOREVER))
    {
        appLogPrintf("CpswProxyServer: Remote AUTOSAR Ethernet Device locate failed\n");
    }
    else
    {
        struct rpmsg_kdrv_ethswitch_device_data eth_dev_data;
        Eth_RpcDeviceData deviceData;
        bool exitTask = false;

        EnetAppUtils_assert(hProxyServer->initEthfwDeviceDataCb != NULL);
        hProxyServer->initEthfwDeviceDataCb(remoteProcId, &eth_dev_data);

        CpswProxyServer_initDeviceData(&eth_dev_data, &deviceData);

        /* Send the EthFw Device Data to AUTOSAR EthDriver on location of
         * end point
         */
        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                remoteProcId,
                                remoteEndPt,
                                hProxyServer->ethDrvObj.localEp,
                                (Ptr)&deviceData,
                                sizeof(deviceData));
        EnetAppUtils_assert(IPC_SOK == rtnVal);

        while (!exitTask)
        {
            rtnVal = RPMessage_recv(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                    (Ptr)msgBuffer,
                                    &len,
                                    &remoteEp,
                                    &remoteProc,
                                    IPC_RPMESSAGE_TIMEOUT_FOREVER);
            if (IPC_SOK == rtnVal)
            {
                Eth_RpcMessageHeader *header;
                int32_t status;

                EnetAppUtils_assert(len <= sizeof(msgBuffer));
                EnetAppUtils_assert(remoteEp == remoteEndPt);
                EnetAppUtils_assert(remoteProcId == remoteProc);

                header = (Eth_RpcMessageHeader *)msgBuffer;

                switch(header->messageId)
                {
                    case ETH_RPC_CMD_TYPE_ATTACH_EXT_REQ:
                    {
                        Eth_RpcAttachExtendedRequest  *attachReq = (Eth_RpcAttachExtendedRequest  *)msgBuffer;
                        Eth_RpcAttachExtendedResponse attachRes;
                        enum rpmsg_kdrv_ethswitch_cpsw_type rdevCpswType;
                        uint32_t allocFlowIdx;

                        EnetAppUtils_assert((attachReq->header.messageId == ETH_RPC_CMD_TYPE_ATTACH_EXT_REQ)
                                            &&
                                            (attachReq->header.messageLen == sizeof(*attachReq)));
                        status = CpswProxy_mapEthRpc2RdevCpswType((Eth_RpcCpswType)attachReq->enetType, &rdevCpswType);
                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            status =  CpswProxyServer_attachExtHandlerCb(virtPort,
                                                                         remoteProc,
                                                                         rdevCpswType,
                                                                         &attachRes.id,
                                                                         &attachRes.coreKey,
                                                                         &attachRes.rxMtu,
                                                                         attachRes.txMtu,
                                                                         ENET_ARRAYSIZE(attachRes.txMtu),
                                                                         &attachRes.features,
                                                                         &allocFlowIdx,
                                                                         &attachRes.txCpswPsilDstId,
                                                                         attachRes.macAddress,
                                                                         &attachRes.macOnlyPort);

                            if (CPSWPROXYSERVER_SOK == status)
                            {
                                Enet_Handle hEnet = (Enet_Handle)((uintptr_t)attachRes.id);

                                attachRes.allocFlowIdxBase = EnetAppUtils_getStartFlowIdx(hEnet, remoteProc);
                                EnetAppUtils_assert(allocFlowIdx >= attachRes.allocFlowIdxBase);
                                attachRes.allocFlowIdxOffset =  allocFlowIdx - attachRes.allocFlowIdxBase;
                            }
                        }
                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            attachRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            attachRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }
                        attachRes.header.messageId = ETH_RPC_CMD_TYPE_ATTACH_EXT_RES;
                        attachRes.header.messageLen = sizeof(attachRes);
                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &attachRes,
                                                sizeof(attachRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);
                        break;
                    }
                    case ETH_RPC_CMD_TYPE_DETACH_REQ:
                    {
                        Eth_RpcDetachRequest *detachReq = (Eth_RpcDetachRequest *)msgBuffer;
                        Eth_RpcDetachResponse detachRes;

                        EnetAppUtils_assert((detachReq->header.messageId == ETH_RPC_CMD_TYPE_DETACH_REQ)
                                            &&
                                            (detachReq->header.messageLen == sizeof(*detachReq)));

                        status =  CpswProxyServer_detachHandlerCb(virtPort,
                                                                  remoteProcId,
                                                                  detachReq->info.id,
                                                                  detachReq->info.coreKey);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            detachRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            detachRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }
                        detachRes.header.messageId = ETH_RPC_CMD_TYPE_DETACH_RES;
                        detachRes.header.messageLen = sizeof(detachRes);
                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &detachRes,
                                                sizeof(detachRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }

                    case ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_REQ:
                    {
                        Eth_RpcRegisterRxDefaultRequest *registerDefaultReq = (Eth_RpcRegisterRxDefaultRequest *)msgBuffer;
                        Eth_RpcRegisterRxDefaultResponse registerDefaultRes;

                        EnetAppUtils_assert((registerDefaultReq->header.messageId == ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_REQ)
                                            &&
                                            (registerDefaultReq->header.messageLen == sizeof(*registerDefaultReq)));

                        status =  CpswProxyServer_registerRxDefaultHandlerCb(virtPort,
                                                                             remoteProcId,
                                                                             registerDefaultReq->info.id,
                                                                             registerDefaultReq->info.coreKey,
                                                                             registerDefaultReq->defaultFlowIdx);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            registerDefaultRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            registerDefaultRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        registerDefaultRes.header.messageId = ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_RES;
                        registerDefaultRes.header.messageLen = sizeof(registerDefaultRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &registerDefaultRes,
                                                sizeof(registerDefaultRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_REGISTER_MAC_REQ:
                    {
                        Eth_RpcRegisterMacRequest * registerMacReq = (Eth_RpcRegisterMacRequest * )msgBuffer;
                        Eth_RpcRegisterMacResponse registerMacRes;

                        EnetAppUtils_assert((registerMacReq->header.messageId == ETH_RPC_CMD_TYPE_REGISTER_MAC_REQ)
                                            &&
                                            (registerMacReq->header.messageLen == sizeof(*registerMacReq)));

                        status =  CpswProxyServer_registerMacHandlerCb(virtPort,
                                                                       remoteProcId,
                                                                       registerMacReq->info.id,
                                                                       registerMacReq->info.coreKey,
                                                                       registerMacReq->macAddress,
                                                                       registerMacReq->flowIdx);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            registerMacRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            registerMacRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        registerMacRes.header.messageId = ETH_RPC_CMD_TYPE_REGISTER_MAC_RES;
                        registerMacRes.header.messageLen = sizeof(registerMacRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &registerMacRes,
                                                sizeof(registerMacRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_UNREGISTER_MAC_REQ:
                    {
                        Eth_RpcUnregisterMacRequest *unregisterMacReq = (Eth_RpcUnregisterMacRequest *)msgBuffer;
                        Eth_RpcUnregisterMacResponse unregisterMacRes;

                        EnetAppUtils_assert((unregisterMacReq->header.messageId == ETH_RPC_CMD_TYPE_UNREGISTER_MAC_REQ)
                                            &&
                                            (unregisterMacReq->header.messageLen == sizeof(*unregisterMacReq)));

                        status =  CpswProxyServer_unregisterMacHandlerCb(virtPort,
                                                                         remoteProcId,
                                                                         unregisterMacReq->info.id,
                                                                         unregisterMacReq->info.coreKey,
                                                                         unregisterMacReq->macAddress,
                                                                         unregisterMacReq->flowIdx);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            unregisterMacRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            unregisterMacRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        unregisterMacRes.header.messageId = ETH_RPC_CMD_TYPE_UNREGISTER_MAC_RES;
                        unregisterMacRes.header.messageLen = sizeof(unregisterMacRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &unregisterMacRes,
                                                sizeof(unregisterMacRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_REQ:
                    {
                        Eth_RpcUnregisterRxDefaultRequest *unregisterDefaultReq = (Eth_RpcUnregisterRxDefaultRequest *)msgBuffer;
                        Eth_RpcUnregisterRxDefaultResponse unregisterDefaultRes;

                        EnetAppUtils_assert((unregisterDefaultReq->header.messageId == ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_REQ)
                                            &&
                                            (unregisterDefaultReq->header.messageLen == sizeof(*unregisterDefaultReq)));

                        status =  CpswProxyServer_unregisterRxDefaultHandlerCb(virtPort,
                                                                               remoteProcId,
                                                                               unregisterDefaultReq->info.id,
                                                                               unregisterDefaultReq->info.coreKey,
                                                                               unregisterDefaultReq->defaultFlowIdx);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            unregisterDefaultRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            unregisterDefaultRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        unregisterDefaultRes.header.messageId = ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_RES;
                        unregisterDefaultRes.header.messageLen = sizeof(unregisterDefaultRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &unregisterDefaultRes,
                                                sizeof(unregisterDefaultRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_IOCTL_REQ:
                    {
                        Eth_RpcIoctlRequest *ioctlReq = (Eth_RpcIoctlRequest *)msgBuffer;
                        Eth_RpcIoctlResponse ioctlRes;

                        EnetAppUtils_assert((ioctlReq->header.messageId == ETH_RPC_CMD_TYPE_IOCTL_REQ)
                                             &&
                                             (ioctlReq->header.messageLen == sizeof(*ioctlReq)));

                        status =  CpswProxyServer_ioctlHandlerCb(virtPort,
                                                                 remoteProcId,
                                                                 ioctlReq->info.id,
                                                                 ioctlReq->info.coreKey,
                                                                 ioctlReq->cmd,
                                                                 (const u8 *)ioctlReq->inargs,
                                                                 ioctlReq->inargsLen,
                                                                 (u8 *)ioctlRes.outargs,
                                                                 ioctlReq->outargsLen);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            ioctlRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            ioctlRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        /* Set IOCTL cmd and outArgs len in response so that
                         * it can be processed on client side without keeping
                         * track of IOCTL response belongs to which IOCTL request
                         */
                        ioctlRes.cmd = ioctlReq->cmd;
                        ioctlRes.outargsLen = ioctlReq->outargsLen;
                        ioctlRes.header.messageId = ETH_RPC_CMD_TYPE_IOCTL_RES;
                        ioctlRes.header.messageLen = sizeof(ioctlRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &ioctlRes,
                                                sizeof(ioctlRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_REQ:
                    {
                         Eth_RpcIpv4RegisterMacRequest *registerIpv4Req = (Eth_RpcIpv4RegisterMacRequest *)msgBuffer;
                         Eth_RpcIpv4RegisterMacResponse registerIpv4Res;

                        EnetAppUtils_assert((registerIpv4Req->header.messageId == ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_REQ)
                                            &&
                                            (registerIpv4Req->header.messageLen == sizeof(*registerIpv4Req)));

                        status =  CpswProxyServer_registerIpv4MacHandlerCb(virtPort,
                                                                           remoteProcId,
                                                                           registerIpv4Req->info.id,
                                                                           registerIpv4Req->info.coreKey,
                                                                           registerIpv4Req->macAddress,
                                                                           registerIpv4Req->ipv4Addr);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            registerIpv4Res.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            registerIpv4Res.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        registerIpv4Res.header.messageId = ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_RES;
                        registerIpv4Res.header.messageLen = sizeof(registerIpv4Res);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &registerIpv4Res,
                                                sizeof(registerIpv4Res));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_REQ:
                    {
                         Eth_RpcIpv4UnregisterMacRequest *unregisterIpv4Req = (Eth_RpcIpv4UnregisterMacRequest *)msgBuffer;
                         Eth_RpcIpv4UnregisterMacResponse unregisterIpv4Res;

                        EnetAppUtils_assert((unregisterIpv4Req->header.messageId == ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_REQ)
                                            &&
                                            (unregisterIpv4Req->header.messageLen == sizeof(*unregisterIpv4Req)));

                        status =  CpswProxyServer_unregisterIpv4MacHandlerCb(virtPort,
                                                                             remoteProcId,
                                                                             unregisterIpv4Req->info.id,
                                                                             unregisterIpv4Req->info.coreKey,
                                                                             unregisterIpv4Req->ipv4Addr);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            unregisterIpv4Res.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            unregisterIpv4Res.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        unregisterIpv4Res.header.messageId = ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_RES;
                        unregisterIpv4Res.header.messageLen = sizeof(unregisterIpv4Res);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &unregisterIpv4Res,
                                                sizeof(unregisterIpv4Res));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_SET_PROMISC_MODE_REQ:
                    {
                        Eth_RpcSetPromiscModeRequest *setPromiscModeReq = (Eth_RpcSetPromiscModeRequest *)msgBuffer;
                        Eth_RpcSetPromiscModeResponse setPromiscModeRes;

                        EnetAppUtils_assert((setPromiscModeReq->header.messageId == ETH_RPC_CMD_TYPE_SET_PROMISC_MODE_REQ) &&
                                            (setPromiscModeReq->header.messageLen == sizeof(*setPromiscModeReq)));

                        status =  CpswProxyServer_setPromiscModeHandlerCb(virtPort,
                                                                          remoteProcId,
                                                                          setPromiscModeReq->info.id,
                                                                          setPromiscModeReq->info.coreKey,
                                                                          setPromiscModeReq->enable);

                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            setPromiscModeRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            setPromiscModeRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        setPromiscModeRes.header.messageId = ETH_RPC_CMD_TYPE_SET_PROMISC_MODE_RES;
                        setPromiscModeRes.header.messageLen = sizeof(setPromiscModeRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &setPromiscModeRes,
                                                sizeof(setPromiscModeRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_FILTER_ADD_MAC_REQ:
                    {
                        Eth_RpcFilterAddMacRequest *filterAddMacReq = (Eth_RpcFilterAddMacRequest *)msgBuffer;
                        Eth_RpcFilterAddMacResponse filterAddMacRes;

                        EnetAppUtils_assert((filterAddMacReq->header.messageId == ETH_RPC_CMD_TYPE_FILTER_ADD_MAC_REQ) &&
                                            (filterAddMacReq->header.messageLen == sizeof(*filterAddMacReq)));

                        status =  CpswProxyServer_filterAddMacHandlerCb(virtPort,
                                                                        remoteProcId,
                                                                        filterAddMacReq->info.id,
                                                                        filterAddMacReq->info.coreKey,
                                                                        filterAddMacReq->macAddress,
                                                                        filterAddMacReq->vlanId,
                                                                        filterAddMacReq->flowIdx);
                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            filterAddMacRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            filterAddMacRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        filterAddMacRes.header.messageId = ETH_RPC_CMD_TYPE_FILTER_ADD_MAC_RES;
                        filterAddMacRes.header.messageLen = sizeof(filterAddMacRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &filterAddMacRes,
                                                sizeof(filterAddMacRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_FILTER_DEL_MAC_REQ:
                    {
                        Eth_RpcFilterDelMacRequest *filterDelMacReq = (Eth_RpcFilterDelMacRequest *)msgBuffer;
                        Eth_RpcFilterDelMacResponse filterDelMacRes;

                        EnetAppUtils_assert((filterDelMacReq->header.messageId == ETH_RPC_CMD_TYPE_FILTER_DEL_MAC_REQ) &&
                                            (filterDelMacReq->header.messageLen == sizeof(*filterDelMacReq)));

                        status =  CpswProxyServer_filterDelMacHandlerCb(virtPort,
                                                                        remoteProcId,
                                                                        filterDelMacReq->info.id,
                                                                        filterDelMacReq->info.coreKey,
                                                                        filterDelMacReq->macAddress,
                                                                        filterDelMacReq->vlanId,
                                                                        filterDelMacReq->flowIdx);
                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            filterDelMacRes.info.status =  ETH_RPC_CMDSTATUS_OK;
                        }
                        else
                        {
                            filterDelMacRes.info.status =  ETH_RPC_CMDSTATUS_EFAIL;
                        }

                        filterDelMacRes.header.messageId = ETH_RPC_CMD_TYPE_FILTER_DEL_MAC_RES;
                        filterDelMacRes.header.messageLen = sizeof(filterDelMacRes);

                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &filterDelMacRes,
                                                sizeof(filterDelMacRes));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                    case ETH_RPC_CMD_TYPE_C2S_NOTIFY:
                    {
                         Eth_RpcC2SNotify *c2sNotify = (Eth_RpcC2SNotify *)msgBuffer;
                         enum rpmsg_kdrv_ethswitch_client_notify_type rdevNotifyType;

                        EnetAppUtils_assert((c2sNotify->header.messageId == ETH_RPC_CMD_TYPE_C2S_NOTIFY)
                                            &&
                                            (c2sNotify->header.messageLen == sizeof(*c2sNotify)));

                        status = CpswProxy_mapEthRpcClientNotify2RdevClientNotifyType((Eth_RpcClientNotifyType)c2sNotify->notifyid, &rdevNotifyType);
                        if (CPSWPROXYSERVER_SOK == status)
                        {
                            CpswProxyServer_clientNotifyHandlerCb(virtPort,
                                                                  remoteProcId,
                                                                  c2sNotify->info.id,
                                                                  c2sNotify->info.coreKey,
                                                                  rdevNotifyType,
                                                                  (uint8_t *)c2sNotify->notifyInfo,
                                                                  c2sNotify->notifyInfoLen);
                        }
                        break;
                    }
                    default:
                    {
                        Eth_RpcS2CNotify s2cNotify;

                        s2cNotify.notifyid = ETH_RPC_SERVERNOTIFY_UNKNOWNCMD;
                        s2cNotify.notifyInfoLen = sizeof(*header);
                        memcpy(s2cNotify.notifyInfo, header, sizeof(*header));
                        s2cNotify.header.messageId = ETH_RPC_CMD_TYPE_S2C_NOTIFY;
                        s2cNotify.header.messageLen = sizeof(s2cNotify);
                        rtnVal = RPMessage_send(hProxyServer->ethDrvObj.hAutosarEthRpMsgEp,
                                                remoteProcId,
                                                remoteEndPt,
                                                hProxyServer->ethDrvObj.localEp,
                                                &s2cNotify,
                                                sizeof(s2cNotify));
                        EnetAppUtils_assert(IPC_SOK == rtnVal);

                        break;
                    }
                }
            }
        }
    }

}

static void CpswProxyServer_hwPushNotifyFxn(void *arg, CpswCpts_HwPush hwPushNum)
{

    if (arg != NULL)
    {
        CpswProxyServer_Obj * hProxyServer = (CpswProxyServer_Obj *)arg;

        /* Post Event */
        EventP_post(hProxyServer->notifyServiceObj.hHwPushNotifyServiceEvent,
                    hProxyServer->notifyServiceObj.hwPushNotifyEventId[CPSW_CPTS_HWPUSH_NORM(hwPushNum)]);
    }
}

static void CpswProxyServer_notifyServiceTaskFxn(void* arg0, void* arg1)
{
    int32_t rtnVal = IPC_SOK;
    Enet_Handle hEnet;
    CpswProxyServer_Obj * hProxyServer = (CpswProxyServer_Obj *)arg0;
    uint64_t msgBuffer[(CPSW_REMOTE_NOTIFY_SERVICE_RPC_MSG_SIZE / sizeof(uint64_t))];
    volatile bool exitTask = false;
    Enet_IoctlPrms prms;
    CpswCpts_Event lookupEventInArgs;
    CpswCpts_Event lookupEventOutArgs;
    uint32_t i = 0U, events = 0U;
    uint32_t remoteCoreId;

    while (!exitTask)
    {
        /*Wait 1ms for hardware push event, then move on to other events*/
        events = EventP_wait(hProxyServer->notifyServiceObj.hHwPushNotifyServiceEvent,
                             CPSWPROXY_CPTS_HWPUSH_EVENTS_OR_MASK,
                             EventP_WaitMode_ANY,
                             1U);

        /* Lookup for timestamp if it is a hardware push notification*/
        if (events)
        {
            rtnVal = CpswProxyServer_getCpswHandle(&hProxyServer->handleTbl,
                                                   hProxyServer->notifyServiceObj.notifyServiceCpswType,
                                                   &hEnet);

            if ((rtnVal == CPSWPROXYSERVER_SOK) && (NULL != hEnet))
            {
                for ( i = 0U; i < CPSW_CPTS_HWPUSH_COUNT_MAX; i++)
                {
                    if(ENET_IS_BIT_SET(events, i))
                    {
                        CpswRemoteNotifyService_HwPushMsg *hwPushMsg = (CpswRemoteNotifyService_HwPushMsg *)msgBuffer;

                        remoteCoreId = hProxyServer->notifyServiceObj.hwPush2CoreIdMap[i];

                        memset(hwPushMsg, 0, sizeof(*hwPushMsg));
                        hwPushMsg->header.messageId = CPSW_REMOTE_NOTIFY_SERVICE_CMD_HWPUSH;
                        hwPushMsg->header.messageLen = sizeof(*hwPushMsg);
                        hwPushMsg->enetType = hProxyServer->notifyServiceObj.notifyServiceCpswType;
                        hwPushMsg->hwPushNum = i + 1U;

                        lookupEventInArgs.eventType = CPSW_CPTS_EVENTTYPE_HW_TS_PUSH;
                        lookupEventInArgs.hwPushNum = (CpswCpts_HwPush) hwPushMsg->hwPushNum;
                        lookupEventInArgs.portNum = 0U;
                        lookupEventInArgs.seqId = 0U;
                        lookupEventInArgs.domain  = 0U;

                        ENET_IOCTL_SET_INOUT_ARGS(&prms, &lookupEventInArgs, &lookupEventOutArgs);
                        rtnVal = Enet_ioctl(hEnet,
                                            EnetSoc_getCoreId(),
                                            CPSW_CPTS_IOCTL_LOOKUP_EVENT,
                                            &prms);
                        if (rtnVal == ENET_SOK)
                        {
                            if ((remoteCoreId != IPC_MAX_PROCS) &&
                                ENET_IS_BIT_SET(hProxyServer->notifyServiceObj.dstProcMask, remoteCoreId))
                            {
                                hwPushMsg->timeStamp = lookupEventOutArgs.tsVal;

                                rtnVal = RPMessage_send(hProxyServer->notifyServiceObj.hNotifyServicRpMsgEp,
                                                        remoteCoreId,
                                                        CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID,
                                                        hProxyServer->notifyServiceObj.localEp,
                                                        hwPushMsg,
                                                        sizeof(*hwPushMsg));
                            }
                        }
                    }
                }
            }
        }
    }
}

