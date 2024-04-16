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

#ifdef QNX_OS
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/slogcodes.h>
#else
#if defined(__KLOCWORK__)
#include <stdlib.h>
#endif
#endif

/* OSAL */
#include <ti/osal/osal.h>
#include <ti/osal/MutexP.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/MailboxP.h>

#include <client-rtos/remote-device.h>
#include <ethremotecfg/protocol/rpmsg-kdrv-transport-ethswitch.h>
#include <ethremotecfg/client/include/ethremotecfg_client.h>
#include <ethremotecfg/client/include/cpsw_proxy.h>

#include <ti/drv/ipc/ipc.h>
#include <ti/drv/enet/enet.h>

#include "cpsw_proxy_cfg.h"

#if defined(SAFERTOS)
#include "SafeRTOS_API.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CPSWPROXY_RDEV_MSGSIZE                          (256U)

#define CPSWPROXY_RDEV_MSGCOUNT                         (3U)

#define CPSWPROXY_RDEVCLIENT_CONNECT_RETRY_MS           (10U)

#define CPSWPROXY_RDEVFRAMEWORK_LOCATE_TIMEOUT          (10U)

#if defined(SAFERTOS)
#define CPSWPROXY_RDEV_MBOX_SIZE            (sizeof(CpswProxy_rdevCmd_t) * CPSWPROXY_RDEV_MSGCOUNT + safertosapiQUEUE_OVERHEAD_BYTES)
#else
#define CPSWPROXY_RDEV_MBOX_SIZE            (sizeof(CpswProxy_rdevCmd_t) * CPSWPROXY_RDEV_MSGCOUNT)
#endif

#if defined(__KLOCWORK__)
#define CpswProxy_assert(cond)               do { if (!(cond)) abort(); } while (0)
#else
#define CpswProxy_assert(cond)                                   \
    (CpswProxy_assertLocal((bool) (cond), (const char *) # cond, \
                    (const char *) __FILE__, (int32_t) __LINE__))
#endif


typedef enum CpswProxy_RdevCmd_tag
{
    CPSWPROXY_RDEVCMD_IOCTL,
    CPSWPROXY_RDEVCMD_REGWR,
    CPSWPROXY_RDEVCMD_REGRD,
    CPSWPROXY_RDEVCMD_ATTACH,
    CPSWPROXY_RDEVCMD_ATTACHEXT,
    CPSWPROXY_RDEVCMD_DETACH,
    CPSWPROXY_RDEVCMD_REGIPV6,
    CPSWPROXY_RDEVCMD_UNREGIPV6,
    CPSWPROXY_RDEVCMD_REGIPV4,
    CPSWPROXY_RDEVCMD_UNREGIPV4,
    CPSWPROXY_RDEVCMD_ALLOCTX,
    CPSWPROXY_RDEVCMD_FREETX,
    CPSWPROXY_RDEVCMD_ALLOCRX,
    CPSWPROXY_RDEVCMD_FREERX,
    CPSWPROXY_RDEVCMD_ALLOCMAC,
    CPSWPROXY_RDEVCMD_FREEMAC,
    CPSWPROXY_RDEVCMD_REGMAC,
    CPSWPROXY_RDEVCMD_UNREGMAC,
    CPSWPROXY_RDEVCMD_REGDEFAULT,
    CPSWPROXY_RDEVCMD_UNREGDEFAULT,
    CPSWPROXY_RDEVCMD_REGETHTYPE,
    CPSWPROXY_RDEVCMD_UNREGETHTYPE,
    CPSWPROXY_RDEVCMD_REGREMOTETIMER,
    CPSWPROXY_RDEVCMD_UNREGREMOTETIMER,
    CPSWPROXY_RDEVCMD_SETPROMISCMODE,
    CPSWPROXY_RDEVCMD_FILTERADDMAC,
    CPSWPROXY_RDEVCMD_FILTERDELMAC,
    CPSWPROXY_RDEVCMD_NOTIFY,
    CPSWPROXY_RDEVCMD_PING,
    CPSWPROXY_RDEVCMD_EXIT,
} CpswProxy_rdevCmd_e;


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
typedef struct CpswProxy_rdevCmdAttachReq_s
{
    enum rpmsg_kdrv_ethswitch_cpsw_type enetType;
} CpswProxy_rdevCmdAttachReq_t;

typedef struct CpswProxy_rdevCmdAttachExtReq_s
{
    enum rpmsg_kdrv_ethswitch_cpsw_type enetType;
} CpswProxy_rdevCmdAttachExtReq_t;

typedef struct CpswProxy_rdevCmdAttachRes_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_mtu;
    uint32_t tx_mtu[RPMSG_KDRV_TP_ETHSWITCH_CPSW_PRIORITY_NUM];
    uint32_t features;
    uint32_t mac_only_port;
} CpswProxy_rdevCmdAttachRes_t;

typedef struct CpswProxy_rdevCmdAttachExtRes_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_mtu;
    uint32_t tx_mtu[RPMSG_KDRV_TP_ETHSWITCH_CPSW_PRIORITY_NUM];
    uint32_t features;
    uint32_t tx_id;
    uint32_t rx_flow_allocidx;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    uint32_t mac_only_port;
} CpswProxy_rdevCmdAttachExtRes_t;

typedef struct CpswProxy_rdevCmdAllocReq_s
{
    uint64_t id;
    uint32_t core_key;
} CpswProxy_rdevCmdAllocReq_t;

typedef struct CpswProxy_rdevCmdAllocTxRes_s
{
    uint32_t tx_id;
} CpswProxy_rdevCmdAllocTxRes_t;

typedef struct CpswProxy_rdevCmdFreeTxReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t tx_id;
} CpswProxy_rdevCmdFreeTxReq_t;

typedef struct CpswProxy_rdevCmdAllocRxRes_s
{
    uint32_t rx_flow_allocidx;
} CpswProxy_rdevCmdAllocRxRes_t;

typedef struct CpswProxy_rdevCmdFreeRxReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
} CpswProxy_rdevCmdFreeRxReq_t;

typedef struct CpswProxy_rdevCmdAllocMacRes_s
{
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
} CpswProxy_rdevCmdAllocMacRes_t;

typedef struct CpswProxy_rdevCmdFreeMacReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
} CpswProxy_rdevCmdFreeMacReq_t;

typedef struct CpswProxy_rdevCmdRegDefaultReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_default_flow_allocidx;
} CpswProxy_rdevCmdRegDefaultReq_t;

typedef struct CpswProxy_rdevCmdUnRegDefaultReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_default_flow_allocidx;
} CpswProxy_rdevCmdUnRegDefaultReq_t;

typedef struct CpswProxy_rdevCmdRegMacReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
} CpswProxy_rdevCmdRegMacReq_t;

typedef struct CpswProxy_rdevCmdUnRegMacReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
} CpswProxy_rdevCmdUnRegMacReq_t;

typedef struct CpswProxy_rdevCmdRegIPv4Req_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    uint8_t ipv4Addr[RPMSG_KDRV_TP_ETHSWITCH_IPV4ADDRLEN];
} CpswProxy_rdevCmdRegIPv4Req_t;

typedef struct CpswProxy_rdevCmdUnRegIPv4Req_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t ipv4Addr[RPMSG_KDRV_TP_ETHSWITCH_IPV4ADDRLEN];
} CpswProxy_rdevCmdUnRegIPv4Req_t;

typedef struct CpswProxy_rdevCmdRegIPv6Req_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    uint8_t ipv6Addr[RPMSG_KDRV_TP_ETHSWITCH_IPV6ADDRLEN];
} CpswProxy_rdevCmdRegIPv6Req_t;

typedef struct CpswProxy_rdevCmdUnRegIPv6Req_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t ipv6Addr[RPMSG_KDRV_TP_ETHSWITCH_IPV6ADDRLEN];
} CpswProxy_rdevCmdUnRegIPv6Req_t;

typedef struct CpswProxy_rdevCmdDetachReq_s
{
    uint64_t id;
    uint32_t core_key;
} CpswProxy_rdevCmdDetachReq_t;

typedef struct CpswProxy_rdevCmdRegRdReq_s
{
    uint32_t regRdAddr;
} CpswProxy_rdevCmdRegRdReq_t;

typedef struct CpswProxy_rdevCmdRegRdRes_s
{
    uint32_t regRdValue;
} CpswProxy_rdevCmdRegRdRes_t;

typedef struct CpswProxy_rdevCmdRegWrReq_s
{
    uint32_t regWrAddr;
    uint32_t regWrValue;
} CpswProxy_rdevCmdRegWrReq_t;

typedef struct CpswProxy_rdevCmdRegWrRes_s
{
    uint32_t regPostWrValue;
} CpswProxy_rdevCmdRegWrRes_t;

typedef struct CpswProxy_rdevCmdIOCTLReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t cmd;
    const void *inArgs;
    uint32_t inArgsSize;
    void *outArgs;
    uint32_t outArgsSize;
} CpswProxy_rdevCmdIOCTLReq_t;

typedef struct CpswProxy_rdevCmdIOCTLRes_s
{
    uint8_t *outArgs;
} CpswProxy_rdevCmdIOCTLRes_t;

typedef struct rdecEthSwitchAppPingReq_s
{
    char msgText[128];
} rdecEthSwitchAppPingReq_t;

typedef struct rdecEthSwitchAppPingRes_s
{
    char resp[128];
} rdecEthSwitchAppPingRes_t;

typedef struct CpswProxy_rdevCmdRegEthertypeReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
    uint16_t ether_type;
} CpswProxy_rdevCmdRegEthertypeReq_t;

typedef struct CpswProxy_rdevCmdUnRegEthertypeReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
    uint16_t ether_type;
} CpswProxy_rdevCmdUnRegEthertypeReq_t;

typedef struct CpswProxy_rdevCmdRegRemoteTimerReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t timerId;
    uint8_t hwPushNum;
} CpswProxy_rdevCmdRegRemoteTimerReq_t;

typedef struct CpswProxy_rdevCmdUnRegRemoteTimerReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t hwPushNum;
} CpswProxy_rdevCmdUnRegRemoteTimerReq_t;

typedef struct CpswProxy_rdevCmdSetPromiscMode_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t enable;
} CpswProxy_rdevCmdSetPromiscMode_t;

typedef struct CpswProxy_rdevCmdFilterAddMacReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    uint16_t vlan_id;
} CpswProxy_rdevCmdFilterAddMacReq_t;

typedef struct CpswProxy_rdevCmdFilterDelMacReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint32_t rx_flow_allocidx;
    uint8_t mac_address[RPMSG_KDRV_TP_ETHSWITCH_MACADDRLEN];
    uint16_t vlan_id;
} CpswProxy_rdevCmdFilterDelMacReq_t;

typedef struct CpswProxy_rdevCmdNotifyReq_s
{
    uint64_t id;
    uint32_t core_key;
    uint8_t notify_id;
    uint8_t *notify_info;
    uint32_t notify_len;
} CpswProxy_rdevCmdNotifyReq_t;


typedef struct CpswProxy_rdevCmdReqMsg_s
{
    CpswProxy_rdevCmd_e cmd;
#ifndef QNX_OS
    MailboxP_Handle hResponseMbx;
#endif
    union
    {
        CpswProxy_rdevCmdIOCTLReq_t ioctl;
        CpswProxy_rdevCmdRegWrReq_t regwr;
        CpswProxy_rdevCmdRegRdReq_t regrd;
        CpswProxy_rdevCmdAttachReq_t attach;
        CpswProxy_rdevCmdAttachExtReq_t attachext;
        CpswProxy_rdevCmdDetachReq_t detach;
        CpswProxy_rdevCmdRegIPv6Req_t regipv6;
        CpswProxy_rdevCmdUnRegIPv6Req_t unregipv6;
        CpswProxy_rdevCmdRegIPv4Req_t regipv4;
        CpswProxy_rdevCmdUnRegIPv4Req_t unregipv4;
        CpswProxy_rdevCmdRegMacReq_t regmac;
        CpswProxy_rdevCmdUnRegMacReq_t unregmac;
        CpswProxy_rdevCmdRegDefaultReq_t regdefault;
        CpswProxy_rdevCmdUnRegDefaultReq_t unregdefault;
        CpswProxy_rdevCmdAllocReq_t alloc;
        CpswProxy_rdevCmdFreeTxReq_t freetx;
        CpswProxy_rdevCmdFreeRxReq_t freerx;
        CpswProxy_rdevCmdFreeMacReq_t freemac;
        CpswProxy_rdevCmdRegEthertypeReq_t regethtype;
        CpswProxy_rdevCmdUnRegEthertypeReq_t unregethtype;
        CpswProxy_rdevCmdRegRemoteTimerReq_t regremotetimer;
        CpswProxy_rdevCmdUnRegRemoteTimerReq_t unregremotetimer;
        CpswProxy_rdevCmdSetPromiscMode_t setpromiscmode;
        CpswProxy_rdevCmdFilterAddMacReq_t filteraddmac;
        CpswProxy_rdevCmdFilterDelMacReq_t filterdelmac;
        CpswProxy_rdevCmdNotifyReq_t notify;
        rdecEthSwitchAppPingReq_t ping;
    } u;
} CpswProxy_rdevCmdReqMsg_t;

typedef struct CpswProxy_rdevCmdResMsg_s
{
    int32_t retVal;
    union
    {
        CpswProxy_rdevCmdAttachRes_t attach;
        CpswProxy_rdevCmdAttachExtRes_t attachext;
        CpswProxy_rdevCmdAllocTxRes_t tx;
        CpswProxy_rdevCmdAllocRxRes_t rx;
        CpswProxy_rdevCmdAllocMacRes_t mac;
        CpswProxy_rdevCmdIOCTLRes_t ioctl;
        CpswProxy_rdevCmdRegWrRes_t regwr;
        CpswProxy_rdevCmdRegRdRes_t regrd;
        rdecEthSwitchAppPingRes_t ping;
    } u;
} CpswProxy_rdevCmdResMsg_t;

typedef struct CpswProxy_rdevCmdMsg_s
{
    CpswProxy_rdevCmdReqMsg_t req;
    CpswProxy_rdevCmdResMsg_t res;
} CpswProxy_rdevCmd_t;

typedef struct CpswProxy_notifyServiceObj_s
{
    TaskP_Handle hNotifyServiceTsk;
    RPMessage_Handle hNotifyServicRpMsgEp;
    uint32_t localEp;
    CpswRemoteNotifyService_CallbackHandlers cb;

    /* Buffer to store received messages for remote notify service */
    uint8_t rpmsgBuf[CPSW_REMOTE_NOTIFY_SERVICE_DATA_SIZE]  __attribute__ ((aligned(8192)));

    /* Notify service task stack buffer */
    uint8_t taskStack[CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKSIZE] __attribute__ ((aligned(CPSW_REMOTE_NOTIFY_SERVICE_TASK_STACKALIGN)));
} CpswProxy_notifyServiceObj;

typedef struct CpswProxy_ClientObj_s
{
    CpswProxy_Config cfg;

    /* Whether client object is already in used by an app */
    bool inUse;

    TaskP_Handle      hRdevCmdTsk;
#ifdef QNX_OS
    int chid;
    int coid;
#else
    MailboxP_Handle    hCmdMbx;
    MailboxP_Handle    hResponseMbx;
    uint8_t cmdMbxBuf[CPSWPROXY_RDEV_MBOX_SIZE] __attribute__ ((aligned(32)));
    uint8_t responseMbxBuf[CPSWPROXY_RDEV_MBOX_SIZE] __attribute__ ((aligned(32)));
#endif

    /* remote_device command handler task stack buffer */
    uint8_t rdevCmdTaskStack[CPSWPROXY_RDEVCMD_TSK_STACKSIZE] __attribute__ ((aligned(CPSWPROXY_RDEVCMD_TSK_STACKALIGN)));
} CpswProxy_ClientObj;

typedef struct CpswProxy_Obj_s
{
    /* Mutex object used to protect get/free CpswProxy_ClientObjs */
    MutexP_Object mutexObj;

    /* Handle to mutexObj */
    MutexP_Handle hMutex;

    /* Array of client objects. Size of this array determines the number of virtual ports
     * that can be used by this core */
    CpswProxy_ClientObj clientObj[CPSWPROXY_CLIENT_MAX];

    /* Master core id where Cpsw Proxy Server runs */
    uint32_t masterCoreId;

    /* Endpoint associated with the underlying remote_device used by CpswProxyServer */
    uint32_t masterEndpt;

    SemaphoreP_Handle hRdevStartSem;

    /* Timestamp event notify service */
    CpswProxy_notifyServiceObj notifyServiceObj;
} CpswProxy_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void CpswProxy_sendCmd(CpswProxy_Handle hProxy,
                              CpswProxy_rdevCmd_e cmd,
                              CpswProxy_rdevCmd_t *msg);

static void CpswProxy_getRxStartFlowIdx(CpswProxy_Handle hProxy,
                                        Enet_Handle hEnet,
                                        uint32_t coreKey,
                                        uint32_t *startFlowIdx);

#ifdef QNX_OS
static void slog_printf(const char *pcString, ...);
#define System_printf slog_printf
#else
// TODO: Need to replace with Ipc_Trace_printf
#define System_printf printf
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static CpswProxy_Obj gCpswProxy;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if !defined(__KLOCWORK__)
static void CpswProxy_assertLocal(bool condition,
                                  const char *str,
                                  const char *fileName,
                                  int32_t lineNum)
{
    volatile static bool gCpswProxyAssertWaitInLoop = TRUE;

    if (!(condition))
    {
        System_printf("Assertion @ Line: %d in %s: %s : failed !!!\n",
                           lineNum, fileName, str);
#ifdef QNX_OS
        gCpswProxyAssertWaitInLoop = FALSE;
#endif
        while (gCpswProxyAssertWaitInLoop)
        {
        }
    }

    return;
}
#endif

#ifdef QNX_OS
static void slog_printf(const char *pcString, ...)
{
    char printBuffer[256];
    va_list arguments;

    if (256 < strlen(pcString))
    {
        assert(false);
    }

    /* Start the varargs processing */
    va_start(arguments, pcString);
    vsnprintf(printBuffer, sizeof(printBuffer), pcString, arguments);

    slogf(_SLOGC_NETWORK, _SLOG_INFO, printBuffer);

    /* End the varargs processing */
    va_end(arguments);
}
#endif

#ifndef QNX_OS
static void  CpswProxy_createMbx(CpswProxy_Handle hProxy,
                                 MailboxP_Handle *pMailboxHandle,
                                 bool IsCMD)
{
    MailboxP_Params mboxParams;

    MailboxP_Params_init(&mboxParams);
    if (IsCMD == true)
    {
        mboxParams.name = (uint8_t *)"CmdMbx";
        mboxParams.buf = (void *)hProxy->cmdMbxBuf;
    }
    else
    {
        mboxParams.name = (uint8_t *)"ResponseMbx";
        mboxParams.buf = (void *)hProxy->responseMbxBuf;
    }
    mboxParams.size =  sizeof(CpswProxy_rdevCmd_t);
    mboxParams.count = CPSWPROXY_RDEV_MSGCOUNT;
    mboxParams.bufsize = CPSWPROXY_RDEV_MBOX_SIZE;

    *pMailboxHandle = MailboxP_create(&mboxParams);
    CpswProxy_assert(*pMailboxHandle != NULL);
}

static void  CpswProxy_deleteMbx(MailboxP_Handle *pMailboxHandle)
{
    MailboxP_delete(*pMailboxHandle);
}
#endif

static void CpswProxy_createSem(SemaphoreP_Handle *pSemHandle)
{
    SemaphoreP_Params semParams;

    SemaphoreP_Params_init(&semParams);
    semParams.mode = SemaphoreP_Mode_BINARY;
    *pSemHandle = SemaphoreP_create(0, &semParams);

    CpswProxy_assert(*pSemHandle != NULL);
}

static void CpswProxy_cmdHandler(CpswProxy_Handle hProxy,
                                 uint32_t deviceId)
{
#ifdef QNX_OS
    int rcvid;
    int status;
#else
    Bool mbxStatus;
    MailboxP_Handle hMailbox = hProxy->hCmdMbx;
#endif
    Bool exitCmdHandler;
    CpswProxy_rdevCmd_t msg;

    exitCmdHandler = FALSE;
    while (exitCmdHandler != TRUE)
    {
#ifdef QNX_OS
        rcvid = MsgReceive(hProxy->chid, &msg, sizeof(msg), NULL);
        CpswProxy_assert(rcvid != -1);
#else
        mbxStatus = MailboxP_pend(hMailbox, &msg, MailboxP_WAIT_FOREVER);
        CpswProxy_assert(mbxStatus == MailboxP_OK);
#endif
        switch (msg.req.cmd)
        {
            case CPSWPROXY_RDEVCMD_PING:
            {
                memset(msg.res.u.ping.resp, 0, sizeof(msg.res.u.ping.resp));
                System_printf("%s: sending ping request\n", __func__);
                msg.res.retVal = rdevEthSwitchClient_sendping(deviceId,
                                                              msg.req.u.ping.msgText,
                                                              strlen(msg.req.u.ping.msgText),
                                                              msg.res.u.ping.resp,
                                                              sizeof(msg.res.u.ping.resp));
                if (0 == msg.res.retVal)
                {
                    uint32_t respLen = sizeof(msg.res.u.ping.resp);

                    msg.res.u.ping.resp[respLen - 1U] = '\0';
                    System_printf("%s: respose %s\n", __func__, msg.res.u.ping.resp);
                }

                break;
            }

            case CPSWPROXY_RDEVCMD_ATTACH:
            {
                msg.res.retVal = rdevEthSwitchClient_attach(deviceId,
                                                            msg.req.u.attach.enetType,
                                                            &msg.res.u.attach.id,
                                                            &msg.res.u.attach.core_key,
                                                            &msg.res.u.attach.rx_mtu,
                                                            msg.res.u.attach.tx_mtu,
                                                            ENET_ARRAYSIZE(msg.res.u.attach.tx_mtu),
                                                            &msg.res.u.attach.features,
                                                            &msg.res.u.attach.mac_only_port);
                if (0 == msg.res.retVal)
                {
                    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)(msg.res.u.attach.id));
                    System_printf("Function:%s,Handle:%p,CoreKey:%x, RxMtu:%4u, TxMtu:%4u:%4u:%4u:%4u:%4u:%4u:%4u:%4u, TxCsum:%s, MacOnly:%u\n",
                                  __func__,
                                  hEnet,
                                  msg.res.u.attach.core_key,
                                  msg.res.u.attach.rx_mtu,
                                  msg.res.u.attach.tx_mtu[0],
                                  msg.res.u.attach.tx_mtu[1],
                                  msg.res.u.attach.tx_mtu[2],
                                  msg.res.u.attach.tx_mtu[3],
                                  msg.res.u.attach.tx_mtu[4],
                                  msg.res.u.attach.tx_mtu[5],
                                  msg.res.u.attach.tx_mtu[6],
                                  msg.res.u.attach.tx_mtu[7],
                                  (((msg.res.u.attach.features & RPMSG_KDRV_TP_ETHSWITCH_FEATURE_TXCSUM) != 0)?"enabled":"disabled"),
                                  msg.res.u.attach.mac_only_port);
                }

                break;
            }

            case CPSWPROXY_RDEVCMD_ATTACHEXT:
            {
                msg.res.retVal = rdevEthSwitchClient_attachext(deviceId,
                                                               msg.req.u.attachext.enetType,
                                                               &msg.res.u.attachext.id,
                                                               &msg.res.u.attachext.core_key,
                                                               &msg.res.u.attachext.rx_mtu,
                                                               msg.res.u.attachext.tx_mtu,
                                                               ENET_ARRAYSIZE(msg.res.u.attachext.tx_mtu),
                                                               &msg.res.u.attachext.features,
                                                               &msg.res.u.attachext.tx_id,
                                                               &msg.res.u.attachext.rx_flow_allocidx,
                                                               msg.res.u.attachext.mac_address,
                                                               ENET_ARRAYSIZE(msg.res.u.attachext.mac_address),
                                                               &msg.res.u.attachext.mac_only_port);
                if (0 == msg.res.retVal)
                {
                    Enet_Handle hEnet = (Enet_Handle)((uintptr_t)(msg.res.u.attach.id));
                    System_printf("Function:%s,Handle:%p,CoreKey:%x, RxMtu:%4u, TxMtu:%4u:%4u:%4u:%4u:%4u:%4u:%4u:%4u, TxCsum:%s, MacOnly:%u\n",
                                  __func__,
                                  hEnet,
                                  msg.res.u.attachext.core_key,
                                  msg.res.u.attachext.rx_mtu,
                                  msg.res.u.attachext.tx_mtu[0],
                                  msg.res.u.attachext.tx_mtu[1],
                                  msg.res.u.attachext.tx_mtu[2],
                                  msg.res.u.attachext.tx_mtu[3],
                                  msg.res.u.attachext.tx_mtu[4],
                                  msg.res.u.attachext.tx_mtu[5],
                                  msg.res.u.attachext.tx_mtu[6],
                                  msg.res.u.attachext.tx_mtu[7],
                                  (((msg.res.u.attachext.features & RPMSG_KDRV_TP_ETHSWITCH_FEATURE_TXCSUM) != 0)?"enabled":"disabled"),
                                  msg.res.u.attachext.mac_only_port);
                }

                break;
            }

            case CPSWPROXY_RDEVCMD_ALLOCTX:
            {
                msg.res.retVal = rdevEthSwitchClient_alloctx(deviceId, msg.req.u.alloc.id, msg.req.u.alloc.core_key, &msg.res.u.tx.tx_id);
                if (0 == msg.res.retVal)
                {
                    System_printf("Function:%s,Txid:%u\n", __func__, msg.res.u.tx.tx_id);
                }

                break;
            }

            case CPSWPROXY_RDEVCMD_ALLOCRX:
            {
                msg.res.retVal = rdevEthSwitchClient_allocrx(deviceId, msg.req.u.alloc.id, msg.req.u.alloc.core_key, &msg.res.u.rx.rx_flow_allocidx);
                if (0 == msg.res.retVal)
                {
                    System_printf("Function:%s,RxAllocId:%u\n", __func__, msg.res.u.rx.rx_flow_allocidx);
                }

                break;
            }

            case CPSWPROXY_RDEVCMD_REGDEFAULT:
            {
                msg.res.retVal = rdevEthSwitchClient_registerrxdefault(deviceId, msg.req.u.regdefault.id, msg.req.u.regdefault.core_key, msg.req.u.regdefault.rx_default_flow_allocidx);
                break;
            }

            case CPSWPROXY_RDEVCMD_ALLOCMAC:
            {
                msg.res.retVal = rdevEthSwitchClient_allocmac(deviceId, msg.req.u.alloc.id, msg.req.u.alloc.core_key, msg.res.u.mac.mac_address, ENET_ARRAYSIZE(msg.res.u.mac.mac_address));
                if (0 == msg.res.retVal)
                {
                    System_printf("Function:%s,mac_address:%2x:%2x:%2x:%2x:%2x:%2x \n",
                                  __func__,
                                  msg.res.u.mac.mac_address[0],
                                  msg.res.u.mac.mac_address[1],
                                  msg.res.u.mac.mac_address[2],
                                  msg.res.u.mac.mac_address[3],
                                  msg.res.u.mac.mac_address[4],
                                  msg.res.u.mac.mac_address[5]);
                }

                break;
            }

            case CPSWPROXY_RDEVCMD_REGMAC:
            {
                msg.res.retVal = rdevEthSwitchClient_registermac(deviceId, msg.req.u.regmac.id, msg.req.u.regmac.core_key, msg.req.u.regmac.rx_flow_allocidx, msg.req.u.regmac.mac_address);
                break;
            }

            case CPSWPROXY_RDEVCMD_REGIPV4:
            {
                msg.res.retVal = rdevEthSwitchClient_ipv4macregister(deviceId, msg.req.u.regipv4.id, msg.req.u.regipv4.core_key, msg.req.u.regipv4.mac_address, msg.req.u.regipv4.ipv4Addr);
                break;
            }

            case CPSWPROXY_RDEVCMD_REGIPV6:
            {
                msg.res.retVal = rdevEthSwitchClient_ipv6macregister(deviceId, msg.req.u.regipv6.id, msg.req.u.regipv6.core_key, msg.req.u.regipv6.mac_address, msg.req.u.regipv6.ipv6Addr);
                break;
            }

            case CPSWPROXY_RDEVCMD_UNREGIPV4:
            {
                msg.res.retVal = rdevEthSwitchClient_ipv4macunregister(deviceId, msg.req.u.unregipv4.id, msg.req.u.unregipv4.core_key, msg.req.u.unregipv4.ipv4Addr);
                break;
            }

            case CPSWPROXY_RDEVCMD_UNREGIPV6:
            {
                /* Nothing to do */
                break;
            }

            case CPSWPROXY_RDEVCMD_IOCTL:
            {
                msg.res.retVal = rdevEthSwitchClient_ioctl(deviceId,
                                                           msg.req.u.ioctl.id,
                                                           msg.req.u.ioctl.core_key,
                                                           msg.req.u.ioctl.cmd,
                                                           msg.req.u.ioctl.inArgs,
                                                           msg.req.u.ioctl.inArgsSize,
                                                           msg.req.u.ioctl.outArgs,
                                                           msg.req.u.ioctl.outArgsSize);
                break;
            }

            case CPSWPROXY_RDEVCMD_UNREGMAC:
            {
                msg.res.retVal = rdevEthSwitchClient_unregistermac(deviceId, msg.req.u.unregmac.id, msg.req.u.unregmac.core_key, msg.req.u.unregmac.rx_flow_allocidx, msg.req.u.unregmac.mac_address);
                break;
            }

            case CPSWPROXY_RDEVCMD_UNREGDEFAULT:
            {
                msg.res.retVal = rdevEthSwitchClient_unregisterrxdefault(deviceId, msg.req.u.unregdefault.id, msg.req.u.unregdefault.core_key, msg.req.u.unregdefault.rx_default_flow_allocidx);
                break;
            }

            case CPSWPROXY_RDEVCMD_FREEMAC:
            {
                msg.res.retVal = rdevEthSwitchClient_freemac(deviceId, msg.req.u.freemac.id, msg.req.u.freemac.core_key, msg.req.u.freemac.mac_address);

                break;
            }

            case CPSWPROXY_RDEVCMD_FREETX:
            {
                msg.res.retVal = rdevEthSwitchClient_freetx(deviceId, msg.req.u.freetx.id, msg.req.u.freetx.core_key, msg.req.u.freetx.tx_id);

                break;
            }

            case CPSWPROXY_RDEVCMD_FREERX:
            {
                msg.res.retVal = rdevEthSwitchClient_freerx(deviceId, msg.req.u.freerx.id, msg.req.u.freerx.core_key, msg.req.u.freerx.rx_flow_allocidx);

                break;
            }

            case CPSWPROXY_RDEVCMD_DETACH:
            {
                /* Dump stats before detach */
                uint8_t notifyInfo[] = {'d', 'u', 'm', 'p', 's', 't', 'a', 't', 's'};
                System_printf("%s: sending message\n", __func__);
                rdevEthSwitchClient_sendNotify(deviceId, msg.req.u.detach.id, msg.req.u.detach.core_key, RPMSG_KDRV_TP_ETHSWITCH_CLIENTNOTIFY_DUMPSTATS, notifyInfo, sizeof(notifyInfo));
                msg.res.retVal = rdevEthSwitchClient_detach(deviceId, msg.req.u.detach.id, msg.req.u.detach.core_key);
                break;
            }

            case CPSWPROXY_RDEVCMD_REGWR:
            {
                msg.res.retVal = rdevEthSwitchClient_regwr(deviceId, msg.req.u.regwr.regWrAddr, msg.req.u.regwr.regWrValue, &msg.res.u.regwr.regPostWrValue);
                break;
            }

            case CPSWPROXY_RDEVCMD_REGRD:
            {
                msg.res.retVal = rdevEthSwitchClient_regrd(deviceId, msg.req.u.regrd.regRdAddr, &msg.res.u.regrd.regRdValue);
                break;
            }
            case CPSWPROXY_RDEVCMD_REGETHTYPE:
            {
                msg.res.retVal = rdevEthSwitchClient_registerethtype(deviceId, msg.req.u.regethtype.id, msg.req.u.regethtype.core_key, msg.req.u.regethtype.rx_flow_allocidx, msg.req.u.regethtype.ether_type);
                break;
            }
            case CPSWPROXY_RDEVCMD_UNREGETHTYPE:
            {
                msg.res.retVal = rdevEthSwitchClient_unregisterethtype(deviceId, msg.req.u.unregethtype.id, msg.req.u.unregethtype.core_key, msg.req.u.unregethtype.rx_flow_allocidx, msg.req.u.unregethtype.ether_type);
                break;
            }
            case CPSWPROXY_RDEVCMD_REGREMOTETIMER:
            {
                msg.res.retVal = rdevEthSwitchClient_registerremotetimer(deviceId,
                                                                         msg.req.u.regremotetimer.id,
                                                                         msg.req.u.regremotetimer.core_key,
                                                                         msg.req.u.regremotetimer.timerId,
                                                                         msg.req.u.regremotetimer.hwPushNum);
                break;
            }
            case CPSWPROXY_RDEVCMD_UNREGREMOTETIMER:
            {
                msg.res.retVal = rdevEthSwitchClient_unregisterremotetimer(deviceId,
                                                                           msg.req.u.unregremotetimer.id,
                                                                           msg.req.u.unregremotetimer.core_key,
                                                                           msg.req.u.unregremotetimer.hwPushNum);
                break;
            }
            case CPSWPROXY_RDEVCMD_SETPROMISCMODE:
            {
                msg.res.retVal = rdevEthSwitchClient_setPromiscMode(deviceId,
                                                                    msg.req.u.setpromiscmode.id,
                                                                    msg.req.u.setpromiscmode.core_key,
                                                                    msg.req.u.setpromiscmode.enable);
                break;
            }
            case CPSWPROXY_RDEVCMD_FILTERADDMAC:
            {
                msg.res.retVal = rdevEthSwitchClient_filterAddMac(deviceId,
                                                                  msg.req.u.filteraddmac.id,
                                                                  msg.req.u.filteraddmac.core_key,
                                                                  msg.req.u.filteraddmac.rx_flow_allocidx,
                                                                  msg.req.u.filteraddmac.mac_address,
                                                                  msg.req.u.filteraddmac.vlan_id);
                break;
            }
            case CPSWPROXY_RDEVCMD_FILTERDELMAC:
            {
                msg.res.retVal = rdevEthSwitchClient_filterDelMac(deviceId,
                                                                   msg.req.u.filterdelmac.id,
                                                                   msg.req.u.filterdelmac.core_key,
                                                                   msg.req.u.filterdelmac.rx_flow_allocidx,
                                                                   msg.req.u.filterdelmac.mac_address,
                                                                   msg.req.u.filterdelmac.vlan_id);
                break;
            }
            case CPSWPROXY_RDEVCMD_NOTIFY:
            {
                msg.res.retVal = rdevEthSwitchClient_sendNotify(deviceId,
                                                                msg.req.u.notify.id,
                                                                msg.req.u.notify.core_key,
                                                                msg.req.u.notify.notify_id,
                                                                msg.req.u.notify.notify_info,
                                                                msg.req.u.notify.notify_len);
                break;
            }
            case CPSWPROXY_RDEVCMD_EXIT:
            {
                exitCmdHandler = TRUE;
                msg.res.retVal = rdevEthSwitchClient_disconnect(deviceId);
                break;
            }
        }

#ifdef QNX_OS
        status = MsgReply(rcvid, EOK, &msg, sizeof(msg));
        CpswProxy_assert(status != -1);
#else
        CpswProxy_assert(msg.req.hResponseMbx != NULL);
        mbxStatus =
            MailboxP_post(msg.req.hResponseMbx, &msg, MailboxP_WAIT_FOREVER);
        CpswProxy_assert(mbxStatus == MailboxP_OK);
#endif
    }
}

static void CpswProxy_setRemoteParams(EthRemoteCfg_VirtPort portId,
                                      rdevEthSwitchClientInitPrms_t *prm)
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
    uint32_t coreId = EnetSoc_getCoreId();
    uint32_t portNum = EthRemoteCfg_getPortNum(portId);
    bool isSwitchPort = EthRemoteCfg_isSwitchPort(portId);

    snprintf((char *)&prm->device_name[0],
             ETHREMOTECFG_SERVER_MAX_NAME_LEN,
             "%s_eth%s-device-%u",
             coreName[coreId],
             isSwitchPort ? "switch" : "mac",
             portNum);
}

static void CpswProxy_rdevCmdTskFxn(void* a0, void* a1)
{
    int32_t ret = 0;
    rdevEthSwitchClientInitPrms_t prm;
    CpswProxy_Handle hProxy = (CpswProxy_Handle) a0;

    CpswProxy_setRemoteParams(hProxy->cfg.virtPort, &prm);
    prm.cbHandler = rdevEthSwitchClient_printText;

    System_printf("Connecting to '%s'\n", prm.device_name);

    while (TRUE)
    {
        ret = rdevEthSwitchClient_connect(&prm);
        if (ret != 0)
        {
            System_printf("error in device query\n");
        }

        if (ret != 0 || (ret == 0 && prm.device_id != APP_REMOTE_DEVICE_DEVICE_ID_EAGAIN))
        {
            break;
        }

        if (ret == 0 && (prm.device_id == APP_REMOTE_DEVICE_DEVICE_ID_EAGAIN))
        {
            TaskP_sleep(CPSWPROXY_RDEVCLIENT_CONNECT_RETRY_MS);
        }
    }

    if (ret == 0)
    {
        System_printf("Registered a device name = %s, id = %u, type = %u\n",
                      prm.device_name,
                      prm.device_id,
                      prm.device_type);
        hProxy->cfg.deviceDataNotifyCb(&prm.eth_device_data);
    }

    CpswProxy_cmdHandler(hProxy, prm.device_id);
}

static void CpswProxy_notifyServiceTskFxn(void* a0, void* a1)
{
    int32_t ret = CPSWPROXY_SOK;
    CpswProxy_notifyServiceObj *notifyObj = (CpswProxy_notifyServiceObj *)a0;
    RPMessage_Params rpmsgPrm;
    uint32_t localEp;
    uint32_t remoteProcId, remoteEndPt;
    uint32_t remoteProc, remoteEp;
    CpswRemoteNotifyService_MessageHeader *header = NULL;
    uint16_t len;
    uint64_t msgBuffer[CPSW_REMOTE_NOTIFY_SERVICE_RPC_MSG_SIZE / sizeof(uint64_t)];
    volatile bool exitTask = false;
    void *data;
    CpswRemoteNotifyService_HwPushMsg *hwPushMsg;

    data = (void *)msgBuffer;
    /* Create RPMsg */
    RPMessageParams_init(&rpmsgPrm);
    rpmsgPrm.requestedEndpt = CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID;
    rpmsgPrm.buf = notifyObj->rpmsgBuf;
    rpmsgPrm.bufSize = sizeof(notifyObj->rpmsgBuf);
    rpmsgPrm.numBufs = CPSW_REMOTE_NOTIFY_SERVICE_NUM_RPMSG_BUFS;

    notifyObj->hNotifyServicRpMsgEp = RPMessage_create(&rpmsgPrm, &localEp);

    if (NULL == notifyObj->hNotifyServicRpMsgEp)
    {
        System_printf("Could not create communication channel\n");
        ret = CPSWPROXY_EFAIL;
    }

    if (CPSWPROXY_SOK == ret)
    {
        if (localEp != CPSW_REMOTE_NOTIFY_SERVICE_ENDPT_ID)
        {
            System_printf("Could not create required End Point");
        }
        else
        {
            notifyObj->localEp = localEp;
        }

        /* Wait for Remote EP to active */
        ret = RPMessage_getRemoteEndPt(gCpswProxy.masterCoreId,
                                      CPSW_REMOTE_NOTIFY_SERVICE,
                                      &remoteProcId,
                                      &remoteEndPt,
                                      IPC_RPMESSAGE_TIMEOUT_FOREVER);
        if(ret != 0)
        {
            System_printf("Remote Notify service locate failed\n");
        }

        while (!exitTask)
        {
            ret = RPMessage_recv(notifyObj->hNotifyServicRpMsgEp,
                                data,
                                &len,
                                &remoteEp,
                                &remoteProc,
                                IPC_RPMESSAGE_TIMEOUT_FOREVER);
            if (IPC_SOK == ret)
            {
                CpswProxy_assert(len <= sizeof(msgBuffer));
                CpswProxy_assert(remoteEp == remoteEndPt);
                CpswProxy_assert(remoteProcId == remoteProc);

                /* Process received message */
                header = (CpswRemoteNotifyService_MessageHeader *)data;
                switch(header->messageId)
                {
                    case CPSW_REMOTE_NOTIFY_SERVICE_CMD_HWPUSH:
                    {
                        hwPushMsg = (CpswRemoteNotifyService_HwPushMsg *)data;
                        CpswProxy_assert(hwPushMsg->header.messageLen == sizeof(CpswRemoteNotifyService_HwPushMsg));

                        if (notifyObj->cb.hwPushCb != NULL)
                        {
                            notifyObj->cb.hwPushCb((CpswCpts_HwPush)hwPushMsg->hwPushNum,
                                                   hwPushMsg->timeStamp,
                                                   notifyObj->cb.hwPushCbArg);
                        }

                        break;
                    }
                    default:
                    {
                        System_printf("CpswProxy_notifyServiceTskFxn: Received unknown notify command: %u\n", header->messageId);
                        break;
                    }
                }
            }
        }
    }
}

static void CpswProxy_remoteDeviceInit(uint32_t masterCoreId,
                                       uint32_t remoteEp,
                                       SemaphoreP_Handle rdevStartSem)
{
    app_remote_device_init_prm_t remote_dev_init_prm;

    appRemoteDeviceInitParamsInit(&remote_dev_init_prm);

    remote_dev_init_prm.rpmsg_buf_size = CPSWPROXY_RDEV_MSGSIZE;
    remote_dev_init_prm.remote_endpt = remoteEp;
    remote_dev_init_prm.wait_sem     = rdevStartSem;
    remote_dev_init_prm.num_cores    = 1;
    remote_dev_init_prm.cores[0]     = masterCoreId;

    appRemoteDeviceInit(&remote_dev_init_prm);

#ifdef QNX_OS
    System_printf("Remote device (core : mpu1_0) .....\r\n");
#else
    System_printf("Remote device (core : mcu2_1) .....\r\n");
#endif
}

static void CpswProxy_createRDevCmdTask(CpswProxy_Handle hProxy)
{
    TaskP_Params taskParams;

    TaskP_Params_init(&taskParams);
    taskParams.priority  = CPSWPROXY_RDEVCMD_TSK_PRI;
    taskParams.arg0      = (void *)hProxy;
    taskParams.stack     = &hProxy->rdevCmdTaskStack[0];
    taskParams.stacksize = sizeof(hProxy->rdevCmdTaskStack);

    hProxy->hRdevCmdTsk = TaskP_create(&CpswProxy_rdevCmdTskFxn, &taskParams);
    CpswProxy_assert(hProxy->hRdevCmdTsk != NULL);
}

static void CpswProxy_createNotifyServiceTask(void)
{
    CpswProxy_notifyServiceObj *notifyObj = &gCpswProxy.notifyServiceObj;
    TaskP_Params taskParams;

    TaskP_Params_init(&taskParams);
    taskParams.priority  = CPSW_REMOTE_NOTIFY_SERVICE_TASK_PRIORITY;
    taskParams.arg0      = (void *)notifyObj;
    taskParams.stack     = &notifyObj->taskStack[0];
    taskParams.stacksize = sizeof(notifyObj->taskStack);

    notifyObj->hNotifyServiceTsk = TaskP_create(&CpswProxy_notifyServiceTskFxn, &taskParams);
    CpswProxy_assert(notifyObj->hNotifyServiceTsk != NULL);
}

void CpswProxy_init(uint32_t masterCoreId,
                    uint32_t masterEndpt)
{
    memset(&gCpswProxy, 0, sizeof(gCpswProxy));

    gCpswProxy.hMutex = MutexP_create(&gCpswProxy.mutexObj);

    CpswProxy_createSem(&gCpswProxy.hRdevStartSem);

    /* Initialize remote_device on the client side */
    CpswProxy_remoteDeviceInit(masterCoreId, masterEndpt, gCpswProxy.hRdevStartSem);
    gCpswProxy.masterCoreId = masterCoreId;
    gCpswProxy.masterEndpt  = masterEndpt;
}

void CpswProxy_deinit(void)
{
    SemaphoreP_delete(gCpswProxy.hRdevStartSem);
    MutexP_delete(gCpswProxy.hMutex);
}

int32_t CpswProxy_connect(void)
{
    uint32_t remoteCoreId;
    uint32_t remoteEndPt;
    int32_t status;

    /* Check if remote_device has been initialized on the server side */
    status = RPMessage_getRemoteEndPt(RPMESSAGE_ANY,
                                      ETHREMOTEDEVICE_REMOTEDEVICE_FRAMEWORK_SERVICE,
                                      &remoteCoreId,
                                      &remoteEndPt,
                                      CPSWPROXY_RDEVFRAMEWORK_LOCATE_TIMEOUT);
    if (status != IPC_SOK)
    {
        System_printf("Remote Device Framework Endpoint locate failed. Retrying !!!\n");
    }
    else
    {
        System_printf("Remote Device Framework Endpoint located. Remote Core Id:%u, Remote End Point:%u\n",
                      remoteCoreId, remoteEndPt);

        /* Unblock client side's remote device that it can proceed */
        SemaphoreP_post(gCpswProxy.hRdevStartSem);

        /* Create time sync notify task */
        CpswProxy_createNotifyServiceTask();
    }

    return status;
}

static CpswProxy_Handle CpswProxy_getHandle(void)
{
    CpswProxy_Handle hProxy = NULL;
    uint32_t i;

    MutexP_lock(gCpswProxy.hMutex, MutexP_WAIT_FOREVER);

    for (i = 0U; i < ENET_ARRAYSIZE(gCpswProxy.clientObj); i++)
    {
        if (!gCpswProxy.clientObj[i].inUse)
        {
            hProxy = &gCpswProxy.clientObj[i];
            hProxy->inUse = true;
            break;
        }
    }

    MutexP_unlock(gCpswProxy.hMutex);

    return hProxy;
}

static void CpswProxy_freeHandle(CpswProxy_Handle hProxy)
{
    MutexP_lock(gCpswProxy.hMutex, MutexP_WAIT_FOREVER);
    memset(hProxy, 0, sizeof(*hProxy));
    hProxy->inUse = false;
    MutexP_unlock(gCpswProxy.hMutex);
}

static void CpswProxy_instanceInit(CpswProxy_Handle hProxy, const CpswProxy_Config *cfg)
{
    hProxy->cfg = *cfg;
#ifdef QNX_OS
    hProxy->chid = ChannelCreate(0);
    CpswProxy_assert(hProxy->chid != -1);
    hProxy->coid = ConnectAttach(ND_LOCAL_NODE, 0, hProxy->chid, _NTO_SIDE_CHANNEL, 0);
    CpswProxy_assert(hProxy->coid != -1);
#else
    CpswProxy_createMbx(hProxy, &hProxy->hCmdMbx, true);
    CpswProxy_createMbx(hProxy, &hProxy->hResponseMbx, false);
#endif

    CpswProxy_createRDevCmdTask(hProxy);
}

static void CpswProxy_instanceDeinit(CpswProxy_Handle hProxy)
{
    CpswProxy_rdevCmd_t msg;

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_EXIT, &msg);

#ifdef QNX_OS
    ConnectDetach(hProxy->coid);
    ChannelDestroy(hProxy->chid);
#else
    CpswProxy_deleteMbx(&hProxy->hCmdMbx);
    CpswProxy_deleteMbx(&hProxy->hResponseMbx);
#endif
}

CpswProxy_Handle CpswProxy_open(const CpswProxy_Config *cfg)
{
    CpswProxy_Handle hProxy;

    /* Get a handle to a free CpswProxy object, if any */
    hProxy = CpswProxy_getHandle();
    if (hProxy == NULL)
    {
        System_printf("All CpswProxy instances for this core are already in use\n");
    }
    else
    {
        /* Create CpswProxy's mailboxes, init cmd and notify tasks */
        CpswProxy_instanceInit(hProxy, cfg);
    }

    return hProxy;
}

void CpswProxy_close(CpswProxy_Handle hProxy)
{
    /* Delete CpswProxy's mailboxes, close tasks */
    CpswProxy_instanceDeinit(hProxy);

    /* Release handle to CpswProxy object */
    CpswProxy_freeHandle(hProxy);
}

static void CpswProxy_sendCmd(CpswProxy_Handle hProxy,
                              CpswProxy_rdevCmd_e cmd,
                              CpswProxy_rdevCmd_t *msg)
{
#ifdef QNX_OS
    int status;
    int size = sizeof(CpswProxy_rdevCmd_t);

    CpswProxy_assert(hProxy != NULL);
    CpswProxy_assert(hProxy->coid != -1);

    msg->req.cmd = cmd;
    status = MsgSend(hProxy->coid,
                     msg,
                     size,
                     msg,
                     size);
    CpswProxy_assert(status != -1);
    CpswProxy_assert(msg->res.retVal == ENET_SOK);
#else
    Bool mbxStatus;
    MailboxP_Handle hCmdMbx = hProxy->hCmdMbx;
    MailboxP_Handle hResponseMbx = hProxy->hResponseMbx;

    CpswProxy_assert(hCmdMbx != NULL);
    CpswProxy_assert(hResponseMbx != NULL);

    msg->req.cmd = cmd;
    msg->req.hResponseMbx = hResponseMbx;
    mbxStatus = MailboxP_post(hCmdMbx, msg, MailboxP_WAIT_FOREVER);
    CpswProxy_assert(mbxStatus == MailboxP_OK);
    mbxStatus = MailboxP_pend(hResponseMbx, msg, MailboxP_WAIT_FOREVER);
    CpswProxy_assert(mbxStatus == MailboxP_OK);
    CpswProxy_assert(msg->res.retVal == ENET_SOK);
#endif
}

void CpswProxy_addHostPortEntry(CpswProxy_Handle hProxy,
                                Enet_Handle hEnet,
                                uint32_t coreKey,
                                const uint8_t *macAddr)
{
    CpswProxy_rdevCmd_t msg;
    uint32_t setUcastOutArgs;
    CpswAle_SetUcastEntryInArgs setUcastInArgs;

    memset(&setUcastInArgs, 0, sizeof(setUcastInArgs));
    memcpy(&setUcastInArgs.addr.addr[0U], macAddr, sizeof(setUcastInArgs.addr.addr));
    setUcastInArgs.addr.vlanId = 0U;
    setUcastInArgs.info.portNum = CPSW_ALE_HOST_PORT_NUM;
    setUcastInArgs.info.blocked = false;
    setUcastInArgs.info.secure = true;
    setUcastInArgs.info.super = false;
    setUcastInArgs.info.ageable = false;

    msg.req.u.ioctl.cmd = CPSW_ALE_IOCTL_ADD_UCAST;
    msg.req.u.ioctl.core_key = coreKey;
    msg.req.u.ioctl.id = (uint64_t)hEnet;
    msg.req.u.ioctl.inArgsSize = sizeof(setUcastInArgs);
    msg.req.u.ioctl.inArgs = &setUcastInArgs;
    msg.req.u.ioctl.outArgs = &setUcastOutArgs;
    msg.req.u.ioctl.outArgsSize = sizeof(setUcastOutArgs);

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_IOCTL, &msg);
}

void CpswProxy_delAddrEntry(CpswProxy_Handle hProxy,
                            Enet_Handle hEnet,
                            uint32_t coreKey,
                            const uint8_t *macAddr)
{
    CpswProxy_rdevCmd_t msg;
    CpswAle_MacAddrInfo addrInfo;

    memset(&addrInfo, 0, sizeof(addrInfo));
    memcpy(&addrInfo.addr[0U], macAddr, sizeof(addrInfo.addr));
    addrInfo.vlanId = 0U;

    msg.req.u.ioctl.cmd = CPSW_ALE_IOCTL_REMOVE_ADDR;
    msg.req.u.ioctl.core_key = coreKey;
    msg.req.u.ioctl.id = (uint64_t)hEnet;
    msg.req.u.ioctl.inArgsSize = sizeof(addrInfo);
    msg.req.u.ioctl.inArgs = &addrInfo;
    msg.req.u.ioctl.outArgs = NULL;
    msg.req.u.ioctl.outArgsSize = 0;

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_IOCTL, &msg);
}

static void CpswProxy_getRxStartFlowIdx(CpswProxy_Handle hProxy,
                                        Enet_Handle hEnet,
                                        uint32_t coreKey,
                                        uint32_t *startFlowIdx)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.ioctl.cmd = CPSW_HOSTPORT_GET_FLOW_ID_OFFSET;
    msg.req.u.ioctl.core_key = coreKey;
    msg.req.u.ioctl.id = (uint64_t)hEnet;
    msg.req.u.ioctl.inArgsSize = 0;
    msg.req.u.ioctl.inArgs = NULL;
    msg.req.u.ioctl.outArgs = startFlowIdx;
    msg.req.u.ioctl.outArgsSize = sizeof(*startFlowIdx);

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_IOCTL, &msg);
}

static enum rpmsg_kdrv_ethswitch_cpsw_type CpswProxy_getRdevCpswType(Enet_Type enetType)
{
    enum rpmsg_kdrv_ethswitch_cpsw_type rdevCpswType = RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAX;

    switch (enetType)
    {
        case ENET_CPSW_2G:
            rdevCpswType = RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MCU;
            break;

#if defined(SOC_J7200)
        case ENET_CPSW_5G:
            rdevCpswType = RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAIN;
            break;
#endif

#if defined(SOC_J721E) || defined(SOC_J784S4)
        case ENET_CPSW_9G:
            rdevCpswType = RPMSG_KDRV_TP_ETHSWITCH_CPSWTYPE_MAIN;
            break;
#endif

        default:
            /* Invalid Enet_Type value */
            CpswProxy_assert(FALSE);
            break;
    }

    return rdevCpswType;
}

void CpswProxy_allocRxFlow(CpswProxy_Handle hProxy,
                           Enet_Handle hEnet,
                           uint32_t coreKey,
                           uint32_t *rxFlowStartIdx,
                           uint32_t *rxFlowIdx)
{
    CpswProxy_rdevCmd_t msg;
    uint32_t absRxFlowIdx;

    msg.req.u.alloc.id = (uint64_t)hEnet;
    msg.req.u.alloc.core_key = coreKey;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_ALLOCRX, &msg);
    absRxFlowIdx = msg.res.u.rx.rx_flow_allocidx;
    CpswProxy_getRxStartFlowIdx(hProxy, hEnet, coreKey, rxFlowStartIdx);
    CpswProxy_assert((absRxFlowIdx >= *rxFlowStartIdx) && (absRxFlowIdx < (*rxFlowStartIdx + ENET_CFG_RM_RX_CH_MAX)));
    *rxFlowIdx = (absRxFlowIdx - *rxFlowStartIdx);
}

void CpswProxy_allocMac(CpswProxy_Handle hProxy,
                        Enet_Handle hEnet,
                        uint32_t coreKey,
                        uint8_t *macAddress)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.alloc.id = (uint64_t)hEnet;
    msg.req.u.alloc.core_key = coreKey;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_ALLOCMAC, &msg);
    memcpy(macAddress, msg.res.u.mac.mac_address, sizeof(msg.res.u.mac.mac_address));
}

void CpswProxy_registerDefaultRxFlow(CpswProxy_Handle hProxy,
                                     Enet_Handle hEnet,
                                     uint32_t coreKey,
                                     uint32_t rxFlowStartIdx,
                                     uint32_t freeRxFlowIdx)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.regdefault.id = (uint64_t)hEnet;
    msg.req.u.regdefault.core_key = coreKey;
    msg.req.u.regdefault.rx_default_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_REGDEFAULT, &msg);
}

void CpswProxy_unregisterDefaultRxFlow(CpswProxy_Handle hProxy,
                                       Enet_Handle hEnet,
                                       uint32_t coreKey,
                                       uint32_t rxFlowStartIdx,
                                       uint32_t freeRxFlowIdx)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.unregdefault.id = (uint64_t)hEnet;
    msg.req.u.unregdefault.core_key = coreKey;
    msg.req.u.unregdefault.rx_default_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_UNREGDEFAULT, &msg);
}

void CpswProxy_registerDstMacRxFlow(CpswProxy_Handle hProxy,
                                    Enet_Handle hEnet,
                                    uint32_t coreKey,
                                    uint32_t rxFlowStartIdx,
                                    uint32_t freeRxFlowIdx,
                                    const uint8_t *macAddress)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.regmac.id = (uint64_t)hEnet;
    msg.req.u.regmac.core_key = coreKey;
    msg.req.u.regmac.rx_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
    memcpy(msg.req.u.regmac.mac_address, macAddress, sizeof(msg.req.u.regmac.mac_address));
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_REGMAC, &msg);
}

void CpswProxy_unregisterDstMacRxFlow(CpswProxy_Handle hProxy,
                                      Enet_Handle hEnet,
                                      uint32_t coreKey,
                                      uint32_t rxFlowStartIdx,
                                      uint32_t freeRxFlowIdx,
                                      const uint8_t *macAddress)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.unregmac.id = (uint64_t)hEnet;
    msg.req.u.unregmac.core_key = coreKey;
    msg.req.u.unregmac.rx_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
    memcpy(msg.req.u.unregmac.mac_address, macAddress, sizeof(msg.req.u.unregmac.mac_address));
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_UNREGMAC, &msg);
}


void CpswProxy_freeMac(CpswProxy_Handle hProxy,
                       Enet_Handle hEnet,
                       uint32_t coreKey,
                       const uint8_t *macAddress)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.freemac.id = (uint64_t)hEnet;
    msg.req.u.freemac.core_key = coreKey;
    memcpy(msg.req.u.freemac.mac_address, macAddress, sizeof(msg.req.u.freemac.mac_address));
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_FREEMAC, &msg);
}

void CpswProxy_freeRxFlow(CpswProxy_Handle hProxy,
                          Enet_Handle hEnet,
                          uint32_t coreKey,
                          uint32_t rxFlowStartIdx,
                          uint32_t rxFlowIdx)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.freerx.id = (uint64_t)hEnet;
    msg.req.u.freerx.core_key = coreKey;
    msg.req.u.freerx.rx_flow_allocidx = rxFlowStartIdx + rxFlowIdx;

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_FREERX, &msg);
}


void CpswProxy_allocTxCh(CpswProxy_Handle hProxy,
                         Enet_Handle hEnet,
                         uint32_t coreKey,
                         uint32_t *txPSILThreadId)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.alloc.id = (uint64_t)hEnet;
    msg.req.u.alloc.core_key = coreKey;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_ALLOCTX, &msg);
    *txPSILThreadId = msg.res.u.tx.tx_id;
}

void CpswProxy_freeTxCh(CpswProxy_Handle hProxy,
                        Enet_Handle hEnet,
                        uint32_t coreKey,
                        uint32_t txChNum)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.cmd = CPSWPROXY_RDEVCMD_FREETX;
    msg.req.u.freetx.id = (uint64_t)hEnet;
    msg.req.u.freetx.core_key = coreKey;
    msg.req.u.freetx.tx_id = txChNum;

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_FREETX, &msg);
}


void CpswProxy_attach(CpswProxy_Handle hProxy,
                      Enet_Type enetType,
                      Enet_Handle *pCpswHandle,
                      uint32_t *coreKey,
                      uint32_t *rxMtu,
                      uint32_t *txMtu,
                      Enet_MacPort *macPort)
{
    CpswProxy_rdevCmd_t msg;
    uint32_t i;
    enum rpmsg_kdrv_ethswitch_cpsw_type rdevCpswType;

    rdevCpswType = CpswProxy_getRdevCpswType(enetType);
    msg.req.u.attach.enetType = rdevCpswType;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_ATTACH, &msg);
    *pCpswHandle = (Enet_Handle)((uintptr_t)(msg.res.u.attach.id));
    *coreKey = msg.res.u.attach.core_key;
    *rxMtu = msg.res.u.attach.rx_mtu;
    for (i = 0; i < ENET_ARRAYSIZE(msg.res.u.attach.tx_mtu); i++)
    {
        txMtu[i] = msg.res.u.attach.tx_mtu[i];
    }

    if ((msg.res.u.attach.features & RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MAC_ONLY) != 0U)
    {
        *macPort = ENET_MACPORT_DENORM(msg.res.u.attach.mac_only_port - 1U);
    }
    else
    {
        *macPort = ENET_MAC_PORT_INV;
    }
}

void CpswProxy_attachExtended(CpswProxy_Handle hProxy,
                              Enet_Type enetType,
                              Enet_Handle *pCpswHandle,
                              uint32_t *coreKey,
                              uint32_t *rxMtu,
                              uint32_t *txMtu,
                              uint32_t *txPSILThreadId,
                              uint32_t *rxFlowStartIdx,
                              uint32_t *rxFlowIdx,
                              uint8_t *macAddress,
                              Enet_MacPort *macPort)
{
    CpswProxy_rdevCmd_t msg;
    uint32_t i;
    uint32_t absRxFlowIdx;
    enum rpmsg_kdrv_ethswitch_cpsw_type rdevCpswType;

    rdevCpswType = CpswProxy_getRdevCpswType(enetType);
    msg.req.u.attach.enetType = rdevCpswType;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_ATTACHEXT, &msg);
    *pCpswHandle = (Enet_Handle)((uintptr_t)(msg.res.u.attachext.id));
    *coreKey = msg.res.u.attachext.core_key;
    *rxMtu = msg.res.u.attachext.rx_mtu;
    for (i = 0; i < ENET_ARRAYSIZE(msg.res.u.attachext.tx_mtu); i++)
    {
        txMtu[i] = msg.res.u.attachext.tx_mtu[i];
    }

    *txPSILThreadId = msg.res.u.attachext.tx_id;
    absRxFlowIdx = msg.res.u.attachext.rx_flow_allocidx;
    CpswProxy_getRxStartFlowIdx(hProxy,
                                *pCpswHandle,
                                *coreKey,
                                rxFlowStartIdx);
    CpswProxy_assert((absRxFlowIdx >= *rxFlowStartIdx) && (absRxFlowIdx < (*rxFlowStartIdx + ENET_CFG_RM_RX_CH_MAX)));
    *rxFlowIdx = (absRxFlowIdx - *rxFlowStartIdx);
    memcpy(macAddress, msg.res.u.attachext.mac_address, sizeof(msg.res.u.attachext.mac_address));

    if ((msg.res.u.attachext.features & RPMSG_KDRV_TP_ETHSWITCH_FEATURE_MAC_ONLY) != 0U)
    {
        *macPort = ENET_MACPORT_DENORM(msg.res.u.attachext.mac_only_port - 1U);
    }
    else
    {
        *macPort = ENET_MAC_PORT_INV;
    }
}

void CpswProxy_detach(CpswProxy_Handle hProxy,
                      Enet_Handle hEnet,
                      uint32_t coreKey)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.cmd = CPSWPROXY_RDEVCMD_DETACH;
    msg.req.u.detach.id = (uint64_t)hEnet;
    msg.req.u.detach.core_key = coreKey;

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_DETACH, &msg);
}

void CpswProxy_registerIPV4Addr(CpswProxy_Handle hProxy,
                                Enet_Handle hEnet,
                                uint32_t coreKey,
                                uint8_t *macAddr,
                                uint8_t *ipv4Addr)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.regipv4.id = (uint64_t)hEnet;
    msg.req.u.regipv4.core_key = coreKey;
    ENET_UTILS_ARRAY_COPY(msg.req.u.regipv4.mac_address, macAddr);
    memcpy(msg.req.u.regipv4.ipv4Addr, ipv4Addr, sizeof(msg.req.u.regipv4.ipv4Addr));
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_REGIPV4, &msg);
}

void CpswProxy_unregisterIPV4Addr(CpswProxy_Handle hProxy,
                                  Enet_Handle hEnet,
                                  uint32_t coreKey,
                                  uint8_t *ipv4Addr)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.unregipv4.id = (uint64_t)hEnet;
    msg.req.u.unregipv4.core_key = coreKey;
    memcpy(msg.req.u.unregipv4.ipv4Addr, ipv4Addr, sizeof(msg.req.u.unregipv4.ipv4Addr));
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_UNREGIPV4, &msg);
}


bool CpswProxy_isPhyLinked(CpswProxy_Handle hProxy,
                           Enet_Handle hEnet,
                           uint32_t coreKey,
                           Enet_MacPort portNum)
{
    CpswProxy_rdevCmd_t msg;
    bool isLinked;

    msg.req.u.ioctl.cmd = ENET_PER_IOCTL_IS_PORT_LINK_UP;
    msg.req.u.ioctl.core_key = coreKey;
    msg.req.u.ioctl.id = (uint64_t)hEnet;
    msg.req.u.ioctl.inArgsSize = sizeof(portNum);
    msg.req.u.ioctl.inArgs = &portNum;
    msg.req.u.ioctl.outArgs = &isLinked;
    msg.req.u.ioctl.outArgsSize = sizeof(isLinked);

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_IOCTL, &msg);
    return isLinked;
}

void CpswProxy_ioctl(CpswProxy_Handle hProxy,
                     Enet_Handle hEnet,
                     uint32_t coreKey,
                     uint32_t cmd,
                     Enet_IoctlPrms *prms)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.ioctl.cmd = cmd;
    msg.req.u.ioctl.core_key = coreKey;
    msg.req.u.ioctl.id = (uint64_t)hEnet;
    msg.req.u.ioctl.inArgsSize = prms->inArgsSize;
    msg.req.u.ioctl.inArgs = prms->inArgs;
    msg.req.u.ioctl.outArgs = prms->outArgs;
    msg.req.u.ioctl.outArgsSize = prms->outArgsSize;

    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_IOCTL, &msg);
}

void CpswProxy_registerEthertypeRxFlow(CpswProxy_Handle hProxy,
                                       Enet_Handle hEnet,
                                       uint32_t coreKey,
                                       uint32_t rxFlowStartIdx,
                                       uint32_t freeRxFlowIdx,
                                       uint16_t etherType)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.regethtype.id = (uint64_t)hEnet;
    msg.req.u.regethtype.core_key = coreKey;
    msg.req.u.regethtype.rx_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
    msg.req.u.regethtype.ether_type = etherType;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_REGETHTYPE, &msg);
}

void CpswProxy_unregisterEthertypeRxFlow(CpswProxy_Handle hProxy,
                                      Enet_Handle hEnet,
                                      uint32_t coreKey,
                                      uint32_t rxFlowStartIdx,
                                      uint32_t freeRxFlowIdx,
                                      uint16_t etherType)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.unregethtype.id = (uint64_t)hEnet;
    msg.req.u.unregethtype.core_key = coreKey;
    msg.req.u.unregethtype.rx_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
    msg.req.u.unregethtype.ether_type = etherType;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_UNREGETHTYPE, &msg);
}

void CpswProxy_registerRemoteTimer(CpswProxy_Handle hProxy,
                                   Enet_Handle hEnet,
                                   uint32_t coreKey,
                                   uint8_t timerId,
                                   uint8_t hwPushNum)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.regremotetimer.id = (uint64_t)hEnet;
    msg.req.u.regremotetimer.core_key = coreKey;
    msg.req.u.regremotetimer.timerId = timerId;
    msg.req.u.regremotetimer.hwPushNum = hwPushNum;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_REGREMOTETIMER, &msg);
}

void CpswProxy_unregisterRemoteTimer(CpswProxy_Handle hProxy,
                                     Enet_Handle hEnet,
                                     uint32_t coreKey,
                                     uint8_t hwPushNum)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.unregremotetimer.id = (uint64_t)hEnet;
    msg.req.u.unregremotetimer.core_key = coreKey;
    msg.req.u.unregremotetimer.hwPushNum = hwPushNum;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_UNREGREMOTETIMER, &msg);
}

void CpswProxy_setPromiscMode(CpswProxy_Handle hProxy,
                              Enet_Handle hEnet,
                              uint32_t coreKey,
                              bool enable)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.setpromiscmode.id = (uint64_t)hEnet;
    msg.req.u.setpromiscmode.core_key = coreKey;
    msg.req.u.setpromiscmode.enable = enable ? 1U : 0U;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_SETPROMISCMODE, &msg);
}

int32_t CpswProxy_filterAddMac(CpswProxy_Handle hProxy,
                               Enet_Handle hEnet,
                               uint32_t coreKey,
                               uint32_t rxFlowStartIdx,
                               uint32_t freeRxFlowIdx,
                               const uint8_t *macAddress,
                               uint16_t vlanId)
{
    CpswProxy_rdevCmd_t msg;
    int32_t status = CPSWPROXY_SOK;

    if (!EnetUtils_isMcastAddr(macAddress))
    {
        System_printf("%s: MAC addr is not multicast\n", __func__);
        status = CPSWPROXY_EINVALIDPARAMS;
    }

    if (status == CPSWPROXY_SOK)
    {
        msg.req.u.filteraddmac.id = (uint64_t)hEnet;
        msg.req.u.filteraddmac.core_key = coreKey;
        msg.req.u.filteraddmac.rx_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
        msg.req.u.filteraddmac.vlan_id = vlanId;
        memcpy(msg.req.u.filteraddmac.mac_address, macAddress, sizeof(msg.req.u.filteraddmac.mac_address));
        CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_FILTERADDMAC, &msg);
    }

    return status;
}

int32_t CpswProxy_filterDelMac(CpswProxy_Handle hProxy,
                               Enet_Handle hEnet,
                               uint32_t coreKey,
                               uint32_t rxFlowStartIdx,
                               uint32_t freeRxFlowIdx,
                               const uint8_t *macAddress,
                               uint16_t vlanId)
{
    CpswProxy_rdevCmd_t msg;
    int32_t status = CPSWPROXY_SOK;

    if (!EnetUtils_isMcastAddr(macAddress))
    {
        System_printf("%s: MAC addr is not multicast\n", __func__);
        status = CPSWPROXY_EINVALIDPARAMS;
    }

    if (status == CPSWPROXY_SOK)
    {
        msg.req.u.filterdelmac.id = (uint64_t)hEnet;
        msg.req.u.filterdelmac.core_key = coreKey;
        msg.req.u.filterdelmac.rx_flow_allocidx = (rxFlowStartIdx + freeRxFlowIdx);
        msg.req.u.filterdelmac.vlan_id = vlanId;
        memcpy(msg.req.u.filterdelmac.mac_address, macAddress, sizeof(msg.req.u.filterdelmac.mac_address));
        CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_FILTERDELMAC, &msg);
    }

    return status;
}

void CpswProxy_sendNotify(CpswProxy_Handle hProxy,
                          Enet_Handle hEnet,
                          uint32_t coreKey,
                          uint8_t notifyId,
                          uint8_t *notifyInfo,
                          uint32_t notifyInfoLength)
{
    CpswProxy_rdevCmd_t msg;

    msg.req.u.notify.id = (uint64_t)hEnet;
    msg.req.u.notify.core_key = coreKey;
    msg.req.u.notify.notify_id = notifyId;
    msg.req.u.notify.notify_info = notifyInfo;
    msg.req.u.notify.notify_len = notifyInfoLength;
    CpswProxy_sendCmd(hProxy, CPSWPROXY_RDEVCMD_NOTIFY, &msg);
}

int32_t CpswProxy_registerHwPushNotifyCb(CpswRemoteNotifyService_hwPushNotifyCbFxn cbFxn,
                                         void *cbArg)
{
    CpswProxy_notifyServiceObj *notifyObj = &gCpswProxy.notifyServiceObj;
    int status = CPSWPROXY_SOK;

    if (NULL != cbFxn)
    {
        if (notifyObj->cb.hwPushCb == NULL)
        {
            notifyObj->cb.hwPushCb = cbFxn;
            notifyObj->cb.hwPushCbArg = cbArg;
        }
        else
        {
            status = CPSWPROXY_EALREADYOPEN;
        }
    }
    else
    {
        status = CPSWPROXY_EBADARGS;
    }

    return status;
}

void CpswProxy_unregisterHwPushNotifyCb(void)
{
    CpswProxy_notifyServiceObj *notifyObj = &gCpswProxy.notifyServiceObj;

    notifyObj->cb.hwPushCb = NULL;
    notifyObj->cb.hwPushCbArg = NULL;
}
