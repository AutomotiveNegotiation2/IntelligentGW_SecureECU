/*
*
* Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     Eth.c
 *
 *  \brief    This file contains the implementation of the main APIs
 *            of the Ethernet driver.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include "Dem.h"
#if (STD_ON == ETH_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "Os.h"
#include "Eth.h"
#include "EthIf_Cbk.h"
#include "SchM_Eth.h"

#include "Eth_Types.h"
#include "Eth_Priv.h"
#include "Eth_Rpc.h"
#include "Eth_RpcPriv.h"
#include "Cdd_Ipc.h"
#include "Eth_Cfg.h"
#include "Eth_VirtMac.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal Function Definitions                             */
/* ========================================================================== */

#define ETH_START_SEC_CODE
#include "Eth_MemMap.h"

#define  ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

extern Eth_VirtualMacInfo  Eth_VirtMacInfo[ETH_CTRL_ID_MAX];

#define  ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static Eth_RpcCpswType Eth_RpcMapCpswType(Eth_EnetType enetType)
{
    Eth_RpcCpswType ethRpcCpswType = ETH_RPC_CPSWTYPE_MAIN;

    switch (enetType)
    {
        case ETH_ENETTYPE_CPSW2G:
        {
            ethRpcCpswType = ETH_RPC_CPSWTYPE_MCU;
            break;
        }
        case ETH_ENETTYPE_CPSW5G:
        case ETH_ENETTYPE_CPSW9G:
        {
            ethRpcCpswType = ETH_RPC_CPSWTYPE_MAIN;
            break;
        }
        default:
            break;

    }
    return ethRpcCpswType;
}

Std_ReturnType Eth_RpcSendExtendedAttachReq(uint8 ctrlIdx)
{
    Eth_RpcAttachExtendedRequest extendedAttachReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE) &&
        (Eth_VirtMacInfo[ctrlIdx].detachResponsePending == FALSE) &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id == 0))
    {
        Eth_RpcCpswType enetType;

        enetType = Eth_RpcMapCpswType(Eth_GetEnetType(ctrlIdx));
        extendedAttachReq.enetType = enetType;
        extendedAttachReq.header.messageLen = sizeof(extendedAttachReq);
        extendedAttachReq.header.messageId = ETH_RPC_CMD_TYPE_ATTACH_EXT_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &extendedAttachReq, sizeof(extendedAttachReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

Std_ReturnType Eth_RpcSendDetachReq(uint8 ctrlIdx)
{
    Eth_RpcDetachRequest detachReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        detachReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;

        Eth_VirtMacInfo[ctrlIdx].detachResponsePending = TRUE;
        detachReq.header.messageLen = sizeof(detachReq);
        detachReq.header.messageId = ETH_RPC_CMD_TYPE_DETACH_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &detachReq, sizeof(detachReq));
        if (E_OK == status)
        {
            /* Clear Cpsw Handle Info on sending the DETACH request */
            memset(&Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo, 0 ,
                   sizeof(Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo));
        }
        else
        {
            /* If IpcSendMsg failed, clear the response pending flag */
            Eth_VirtMacInfo[ctrlIdx].detachResponsePending = FALSE;
        }
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

Std_ReturnType Eth_RpcSendRegisterDefaultReq(uint8 ctrlIdx)
{
    Eth_RpcRegisterRxDefaultRequest registerDefaultReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        registerDefaultReq.defaultFlowIdx = (Eth_VirtMacInfo[ctrlIdx].rxFlowStartIdx
                                             +
                                             Eth_VirtMacInfo[ctrlIdx].rxFlowIdx);
        registerDefaultReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;
        registerDefaultReq.header.messageLen = sizeof(registerDefaultReq);
        registerDefaultReq.header.messageId = ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &registerDefaultReq, sizeof(registerDefaultReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

Std_ReturnType Eth_RpcSendUnregisterDefaultReq(uint8 ctrlIdx)
{
    Eth_RpcUnregisterRxDefaultRequest unregisterDefaultReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        unregisterDefaultReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;
        unregisterDefaultReq.defaultFlowIdx = (Eth_VirtMacInfo[ctrlIdx].rxFlowStartIdx
                                               +
                                               Eth_VirtMacInfo[ctrlIdx].rxFlowIdx);
        unregisterDefaultReq.header.messageLen = sizeof(unregisterDefaultReq);
        unregisterDefaultReq.header.messageId = ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &unregisterDefaultReq, sizeof(unregisterDefaultReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

Std_ReturnType Eth_RpcSendRegisterMacReq(uint8 ctrlIdx, uint8 *macAddress)
{
    Eth_RpcRegisterMacRequest registerMacReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        registerMacReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;
        registerMacReq.flowIdx = (Eth_VirtMacInfo[ctrlIdx].rxFlowStartIdx
                                  +
                                  Eth_VirtMacInfo[ctrlIdx].rxFlowIdx);
        memcpy(registerMacReq.macAddress, macAddress, sizeof(registerMacReq.macAddress));

        registerMacReq.header.messageLen = sizeof(registerMacReq);
        registerMacReq.header.messageId = ETH_RPC_CMD_TYPE_REGISTER_MAC_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &registerMacReq, sizeof(registerMacReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return  status;
}

Std_ReturnType Eth_RpcSendUnregisterMacReq(uint8 ctrlIdx, uint8 *macAddress)
{
    Eth_RpcUnregisterMacRequest unregisterMacReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        unregisterMacReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;
        unregisterMacReq.flowIdx = (Eth_VirtMacInfo[ctrlIdx].rxFlowStartIdx
                                    +
                                    Eth_VirtMacInfo[ctrlIdx].rxFlowIdx);
        memcpy(unregisterMacReq.macAddress, macAddress , sizeof(unregisterMacReq.macAddress));
        unregisterMacReq.header.messageLen = sizeof(unregisterMacReq);
        unregisterMacReq.header.messageId = ETH_RPC_CMD_TYPE_UNREGISTER_MAC_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &unregisterMacReq, sizeof(unregisterMacReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return  status;
}

Std_ReturnType Eth_RpcSendIPv4RegisterMacReq(uint8 ctrlIdx,
                                             uint8 * ipv4Address,
                                             uint8 *macAddress)
{
    Eth_RpcIpv4RegisterMacRequest registerIpv4MacReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        registerIpv4MacReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;
        memcpy(registerIpv4MacReq.ipv4Addr  , ipv4Address, sizeof(registerIpv4MacReq.ipv4Addr));
        memcpy(registerIpv4MacReq.macAddress, macAddress, sizeof(registerIpv4MacReq.macAddress));

        registerIpv4MacReq.header.messageLen = sizeof(registerIpv4MacReq);
        registerIpv4MacReq.header.messageId = ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &registerIpv4MacReq, sizeof(registerIpv4MacReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

Std_ReturnType Eth_RpcSendIPv4UnregisterMacReq(uint8 ctrlIdx, uint8 * ipv4Address)
{
    Eth_RpcIpv4UnregisterMacRequest unregisterIpv4MacReq;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        unregisterIpv4MacReq.info = Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo;
        memcpy(unregisterIpv4MacReq.ipv4Addr  , ipv4Address,
               sizeof(unregisterIpv4MacReq.ipv4Addr));

        unregisterIpv4MacReq.header.messageLen = sizeof(unregisterIpv4MacReq);
        unregisterIpv4MacReq.header.messageId = ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_REQ;

        status = Cdd_IpcSendMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                &unregisterIpv4MacReq, sizeof(unregisterIpv4MacReq));
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

static Std_ReturnType Eth_RpcSendC2SNotify(uint32 chId,
                                           const Eth_RpcCommonRequestInfo *info,
                                           Eth_RpcClientNotifyType notifyType,
                                           uint32 notifyLen,
                                           void *notifyInfo)
{
    Eth_RpcC2SNotify c2sNotify;
    Std_ReturnType status;

    c2sNotify.info = *info;
    c2sNotify.notifyid = notifyType;
    c2sNotify.notifyInfoLen = notifyLen;
    memcpy(c2sNotify.notifyInfo, notifyInfo, sizeof(c2sNotify.notifyInfo));

    c2sNotify.header.messageLen = sizeof(c2sNotify);
    c2sNotify.header.messageId = ETH_RPC_CMD_TYPE_C2S_NOTIFY;

    status = Cdd_IpcSendMsg(chId, &c2sNotify, sizeof(c2sNotify));

    return status;
}

Std_ReturnType Eth_RpcSendDumpCpswStats(uint8 ctrlIdx, Eth_RpcCommonRequestInfo * info)
{
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        status = Eth_RpcSendC2SNotify(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                      &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                      ETH_RPC_CLIENTNOTIFY_DUMPSTATS, 0, NULL);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

Std_ReturnType Eth_RpcSendCustomNotify(uint8 ctrlIdx, void *notifyInfo,
                                       uint32 notifyLen)
{
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        status = Eth_RpcSendC2SNotify(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                      &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                      ETH_RPC_CLIENTNOTIFY_CUSTOM,
                                      notifyLen, notifyInfo);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}


static Std_ReturnType Eth_RpcSendIoctlReq(uint32 chId,
                                          const Eth_RpcCommonRequestInfo *info,
                                          uint32 cmd,
                                          void *inArgs,
                                          uint32 inargsLen,
                                          uint32 outargsLen)
{
    Eth_RpcIoctlRequest ioctlReq;
    Std_ReturnType status;

    ioctlReq.cmd = cmd;
    memcpy(ioctlReq.inargs, inArgs, inargsLen);
    ioctlReq.inargsLen = inargsLen;
    ioctlReq.outargsLen = outargsLen;

    ioctlReq.info = *info;
    ioctlReq.header.messageLen = sizeof(ioctlReq);
    ioctlReq.header.messageId = ETH_RPC_CMD_TYPE_IOCTL_REQ;

    status = Cdd_IpcSendMsg(chId,
                            &ioctlReq, sizeof(ioctlReq));

    return status;
}

static Std_ReturnType Eth_RpcMapCpswPort(Eth_PortType port,
                                         Enet_MacPort *cpswMacPort,
                                         boolean *hostPort)
{
    Std_ReturnType status = E_OK;

    *hostPort = FALSE;
    switch (port)
    {
        case ETH_PORT_HOST_PORT:
             *hostPort = TRUE;
             break;
        case ETH_PORT_MAC_PORT_1:
            *cpswMacPort = ENET_MAC_PORT_1;
            break;
        case ETH_PORT_MAC_PORT_2:
            *cpswMacPort = ENET_MAC_PORT_2;
            break;
        case ETH_PORT_MAC_PORT_3:
            *cpswMacPort = ENET_MAC_PORT_3;
            break;
        case ETH_PORT_MAC_PORT_4:
            *cpswMacPort = ENET_MAC_PORT_4;
            break;
        case ETH_PORT_MAC_PORT_5:
            *cpswMacPort = ENET_MAC_PORT_5;
            break;
        case ETH_PORT_MAC_PORT_6:
            *cpswMacPort = ENET_MAC_PORT_6;
            break;
        case ETH_PORT_MAC_PORT_7:
            *cpswMacPort = ENET_MAC_PORT_7;
            break;
        case ETH_PORT_MAC_PORT_8:
            *cpswMacPort = ENET_MAC_PORT_8;
            break;
        default:
            status = E_NOT_OK;
    }
    return status;
}

Std_ReturnType Eth_RpcSendAddUnicastAddr(uint8 ctrlIdx, uint8 *macAddr,
                                         Eth_PortType port, uint32 vlanId)
{
    Eth_CpswAle_SetUcastEntryInArgs setUcastInArgs;
    Std_ReturnType status;
    Enet_MacPort cpswMacPort;
    boolean hostPort;

    status = Eth_RpcMapCpswPort(port, &cpswMacPort, &hostPort);
    if ((status == E_OK)
        &&
        (Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        memset(&setUcastInArgs, 0, sizeof(setUcastInArgs));
        memcpy(&setUcastInArgs.addr.addr[0U], macAddr,
               sizeof(setUcastInArgs.addr.addr));
        setUcastInArgs.addr.vlanId  = vlanId;
        if (hostPort)
        {
            setUcastInArgs.info.portNum = ETH_CPSW_ALE_HOST_PORT_NUM;
        }
        else
        {
            setUcastInArgs.info.portNum =
                ETH_CPSW_ALE_MACPORT_TO_ALEPORT(ENET_MACPORT_NORM(cpswMacPort));
        }
        setUcastInArgs.info.blocked = FALSE;
        setUcastInArgs.info.secure  = FALSE;
        setUcastInArgs.info.super   = 0U;
        setUcastInArgs.info.ageable = FALSE;
        setUcastInArgs.info.trunk   = FALSE;

        status = Eth_RpcSendIoctlReq(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                     &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                     ETH_CPSW_ALE_IOCTL_ADD_UCAST,
                                     &setUcastInArgs,
                                     sizeof(setUcastInArgs),
                                     sizeof(uint32));
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

Std_ReturnType Eth_RpcSendDelAddrEntry(uint8 ctrlIdx, const uint8 *macAddr,
                                       uint32 vlanId)
{
    Eth_CpswAle_MacAddrInfo addrInfo;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        memset(&addrInfo, 0, sizeof(addrInfo));
        memcpy(&addrInfo.addr[0U], macAddr, sizeof(addrInfo.addr));
        addrInfo.vlanId = vlanId;

        status = Eth_RpcSendIoctlReq (Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                      &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                      ETH_CPSW_ALE_IOCTL_REMOVE_ADDR,
                                      &addrInfo,
                                      sizeof(addrInfo),
                                      0);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

static Std_ReturnType Eth_RpcValidatePortList(const Eth_PortListType *portList)
{
    Std_ReturnType status = E_OK;
    uint32 i;
    Enet_MacPort macPort;
    boolean hostPort;

    if (portList->numPorts > ENET_ARRAYSIZE(portList->ports))
    {
        status = E_NOT_OK;
    }
    if (E_OK == status)
    {
        for (i = 0; i < portList->numPorts; i++)
        {
            status = Eth_RpcMapCpswPort(portList->ports[i], &macPort, &hostPort);
            if (E_OK != status)
            {
                break;
            }
        }
    }
    return status;
}


static Std_ReturnType Eth_RpcGetPortMask(const Eth_PortListType *portList,
                                         uint32 *portMask)
{
    uint32 i;
    Enet_MacPort macPort;
    boolean hostPort;
    Std_ReturnType status = E_NOT_OK;

    *portMask = 0U;

    if (portList->numPorts <= ENET_ARRAYSIZE(portList->ports))
    {
        for (i = 0; i < portList->numPorts; i++)
        {
            status = Eth_RpcMapCpswPort(portList->ports[i], &macPort, &hostPort);
            if (E_OK != status)
            {
                break;
            }
            else
            {
                if (hostPort)
                {
                    *portMask |= ETH_CPSW_ALE_HOST_PORT_MASK;
                }
                else
                {
                    *portMask |= ETH_CPSW_ALE_MACPORT_TO_PORTMASK(macPort);
                }
            }
        }
    }
    return status;
}



Std_ReturnType Eth_RpcSendAddMulticastEntry(uint8 ctrlIdx,
                                            const uint8 *macAddr,
                                            uint32 vlanId,
                                            uint32 numIgnBits,
                                            Eth_PortListType *portList)
{
    Eth_CpswAle_SetMcastEntryInArgs setMcastInArgs;
    Std_ReturnType status;

    status = Eth_RpcValidatePortList(portList);
    if ((E_OK == status)
        &&
        (Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        uint32 portMask;

        status = Eth_RpcGetPortMask(portList, &portMask);
        if (E_OK == status)
        {
            memcpy(&setMcastInArgs.addr.addr[0], macAddr,
                   sizeof(setMcastInArgs.addr.addr));
            setMcastInArgs.addr.vlanId = vlanId;

            setMcastInArgs.info.super  = FALSE;
            setMcastInArgs.info.fwdState   = ETH_CPSW_ALE_FWDSTLVL_FWD;
            setMcastInArgs.info.portMask   = portMask;
            setMcastInArgs.info.numIgnBits = numIgnBits;

            status = Eth_RpcSendIoctlReq (Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                          &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                          ETH_CPSW_ALE_IOCTL_ADD_MCAST,
                                          &setMcastInArgs,
                                          sizeof(setMcastInArgs),
                                          sizeof(uint32));
        }
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

static Std_ReturnType Eth_RpcMapRpcRecvCmd2Sid(Eth_RpcCmdType rpcCmd,
                                               uint32 ioctlCmd,
                                               boolean *isInternalCmd,
                                               uint8 *sid)
{
    Std_ReturnType status = E_OK;

    switch (rpcCmd)
    {
        case  ETH_RPC_CMD_TYPE_FWINFO_RES:
        {
            *sid = ETH_SID_INIT;
            *isInternalCmd = TRUE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_ATTACH_EXT_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_INIT;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_DETACH_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_DEINIT;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_REGISTER_DEFAULTFLOW_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_SUBSCRIBE_ALLTRAFFIC;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_REGISTER_MAC_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_SUBSCRIBE_DSTMAC;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_UNREGISTER_MAC_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_UNSUBSCRIBE_DSTMAC;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_UNREGISTER_DEFAULTFLOW_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_UNSUBSCRIBE_ALLTRAFFIC;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_IPV4_MACADDR_ASSOCIATE;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_RES:
        {
            *sid = ETH_SID_DISPATCH_VIRTMAC_IPV4_MACADDR_DISASSOCIATE;
            *isInternalCmd = FALSE;
            break;
        }
        case  ETH_RPC_CMD_TYPE_IOCTL_REQ:
        case  ETH_RPC_CMD_TYPE_IOCTL_RES:
        {
            switch(ioctlCmd)
            {
                case ETH_CPSW_ALE_IOCTL_ADD_UCAST:
                    *sid = ETH_SID_DISPATCH_VIRTMAC_ADD_UNICAST_MACADDR;
                    break;
                case ETH_CPSW_ALE_IOCTL_REMOVE_ADDR:
                    *sid = ETH_SID_DISPATCH_VIRTMAC_DEL_MACADDR;
                    break;
                case ETH_CPSW_ALE_IOCTL_ADD_MCAST:
                    *sid = ETH_SID_DISPATCH_VIRTMAC_ADD_MCAST_MACADDR;
                    break;
                case ETH_CPSW_ALE_IOCTL_ADD_VLAN:
                    *sid = ETH_SID_DISPATCH_VIRTMAC_ADD_VLAN;
                    break;
                case ETH_CPSW_ALE_IOCTL_REMOVE_VLAN:
                    *sid = ETH_SID_DISPATCH_VIRTMAC_DEL_VLAN;
                    break;
                default:
                    status = E_NOT_OK;

            }
            *isInternalCmd = FALSE;
            break;
        }
        default:
            status = E_NOT_OK;
    }
    return status;
}


static void Eth_RpcMsgStatusCb(uint32 controllerIdx,
                               Eth_RpcCmdComplete rpcCmdComplete,
                               Eth_RpcCmdType rpcCmd,
                               sint32 status,
                               uint32 ioctlCmd)
{
    Std_ReturnType retVal;
    boolean isInternalCmd;
    uint8 sid;

    retVal = Eth_RpcMapRpcRecvCmd2Sid(rpcCmd, ioctlCmd, &isInternalCmd, &sid);
    if (retVal == E_OK)
    {
        if (isInternalCmd)
        {
            /* For Rpc Cmds initiated by the ETh Driver internally
             * only invoke DetReportError on failure
             */
            if (status != ETH_RPC_CMDSTATUS_OK)
            {
                #if (STD_ON == ETH_DEV_ERROR_DETECT)
                Eth_reportDetError(sid, ETH_E_VIRTMAC_RPCCMDFAILED);
                #endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
            }
        }
        else
        {
            if (rpcCmdComplete != (Eth_RpcCmdComplete)NULL_PTR)
            {
                rpcCmdComplete(controllerIdx, sid, status);
            }
        }
    }
    else
    {
        #if (STD_ON == ETH_DEV_ERROR_DETECT)
        Eth_reportDetError(sid, ETH_E_VIRTMAC_RPCCMDFAILED);
        #endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
    }
}

static Std_ReturnType Eth_RpcProcessFwInfo(uint8 ctrlIdx,
                                           Eth_RpcDeviceData *fwInfo,
                                           uint8 apiId)
{
    Std_ReturnType status;

    if ((fwInfo->fwVer.major == ETH_RPC_API_VERSION_MAJOR)
        &&
        (fwInfo->fwVer.minor == ETH_RPC_API_VERSION_MINOR)
        &&
        (fwInfo->fwVer.rev == ETH_RPC_API_VERSION_REVISION))
    {
        Eth_VirtMacInfo[ctrlIdx].fwInfo = *fwInfo;
        Eth_VirtMacInfo[ctrlIdx].ethFwAttached = TRUE;
        if (Eth_VirtMacGetFwRegisterFuncPtr(ctrlIdx))
        {
            Eth_VirtMacGetFwRegisterFuncPtr(ctrlIdx)(ctrlIdx);
        }
        status = E_OK;
    }
    else
    {
        status = E_NOT_OK;
        #if (STD_ON == ETH_DEV_ERROR_DETECT)
        Eth_reportDetError(apiId, ETH_E_VIRTMAC_APIMISMATCH);
        #endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
    }
    return status;
}

static void Eth_RpcProcessAttachRes(uint8 ctrlIdx,
                                    Eth_RpcAttachExtendedResponse *attachRes)
{
    Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id = attachRes->id;
    Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.coreKey = attachRes->coreKey;
    Eth_VirtMacInfo[ctrlIdx].hostPortRxMtu = attachRes->rxMtu;
    memcpy(Eth_VirtMacInfo[ctrlIdx].txMtu, attachRes->txMtu,
           sizeof(Eth_VirtMacInfo[ctrlIdx].txMtu));
    Eth_VirtMacInfo[ctrlIdx].txPSILThreadId = attachRes->txCpswPsilDstId;
    Eth_VirtMacInfo[ctrlIdx].rxFlowStartIdx = attachRes->allocFlowIdxBase;
    Eth_VirtMacInfo[ctrlIdx].rxFlowIdx      = attachRes->allocFlowIdxOffset;
    memcpy(Eth_VirtMacInfo[ctrlIdx].macAddress, attachRes->macAddress,
           sizeof(Eth_VirtMacInfo[ctrlIdx].macAddress));
    Eth_VirtMacInfo[ctrlIdx].macOnlyPort    = attachRes->macOnlyPort;
    Eth_VirtMacInfo[ctrlIdx].features       = attachRes->features;
}

static void Eth_RpcProcessS2CNotify(Eth_RpcS2CNotify *s2cNotifyinfo, uint8 apiId)
{
    switch (s2cNotifyinfo->notifyid)
    {
        case ETH_RPC_SERVERNOTIFY_UNKNOWNCMD:
        {
            if (s2cNotifyinfo->notifyInfoLen == sizeof(Eth_RpcMessageHeader))
            {
                #if (STD_ON == ETH_DEV_ERROR_DETECT)
                Eth_reportDetError(apiId, ETH_E_VIRTMAC_UNSUPPORTEDSRVCMD);
                #endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
            }
            break;
        }
        default:
        {
            #if (STD_ON == ETH_DEV_ERROR_DETECT)
            Eth_reportDetError(apiId, ETH_E_VIRTMAC_UNSUPPORTECLIENTNOTIFY);
            #endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
        }
    }
}

Std_ReturnType Eth_RpcAnnounce(uint8 ctrlIdx)
{
    const char *announceMsg = ETH_RPC_REMOTE_SERVICE;
    Std_ReturnType status;

    status = Cdd_IpcAnnounce((UCHAR*)announceMsg, Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx));
    return status;
}

static Std_ReturnType Eth_RpcProcessIoctlRes(Eth_RpcIoctlResponse *ioctlRes)
{
    Std_ReturnType status = E_OK;

    switch (ioctlRes->cmd)
    {
        case ETH_CPSW_ALE_IOCTL_ADD_UCAST:
            /* Nothing to be done to process IOCTL response */
            break;
        case ETH_CPSW_ALE_IOCTL_REMOVE_ADDR:
            /* Nothing to be done to process IOCTL response */
            break;
        case ETH_CPSW_ALE_IOCTL_ADD_MCAST:
            /* Nothing to be done to process IOCTL response */
            break;
        default:
            status = E_NOT_OK;
    }
    return status;
}


Std_ReturnType Eth_RpcRecvMsg(uint8 ctrlIdx, uint8 callerApiId)
{
    uint64_t msgBuffer[(ETH_RPC_MSG_SIZE / sizeof(uint64_t))];
    uint32 msgSize;
    Std_ReturnType status;
    Eth_RpcMessageHeader *msgHeader;

    msgSize = sizeof(msgBuffer);
    status = Cdd_IpcReceiveMsg(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                               &msgBuffer, &msgSize);

    if ((status == E_OK) && (msgSize <= sizeof(msgBuffer)))
    {
        msgHeader = (Eth_RpcMessageHeader *)msgBuffer;

        switch(msgHeader->messageId)
        {
            case ETH_RPC_CMD_TYPE_FWINFO_RES:
            {
                Eth_RpcDeviceData *fwInfo = (Eth_RpcDeviceData *)msgBuffer;

                if ((fwInfo->header.messageId == ETH_RPC_CMD_TYPE_FWINFO_RES)
                    &&
                    (fwInfo->header.messageLen == sizeof(*fwInfo)))
                {
                    status = Eth_RpcProcessFwInfo(ctrlIdx, fwInfo, callerApiId);
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_ATTACH_EXT_RES:
            {
                Eth_RpcAttachExtendedResponse *attachRes = (Eth_RpcAttachExtendedResponse *)msgBuffer;

                if ((attachRes->header.messageId == ETH_RPC_CMD_TYPE_ATTACH_EXT_RES)
                    &&
                    (attachRes->header.messageLen == sizeof(*attachRes)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType) attachRes->header.messageId,
                                       attachRes->info.status,
                                       0 /* Not IOCTL cmd response */);
                    if (ETH_RPC_CMDSTATUS_OK == attachRes->info.status)
                    {
                        Eth_RpcProcessAttachRes(ctrlIdx, attachRes);
                    }
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_REGISTER_MAC_RES:
            {
                Eth_RpcRegisterMacResponse *registerMacRes =
                                       (Eth_RpcRegisterMacResponse *)msgBuffer;

                if ((registerMacRes->header.messageId == ETH_RPC_CMD_TYPE_REGISTER_MAC_RES)
                    &&
                    (registerMacRes->header.messageLen == sizeof(*registerMacRes)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType)registerMacRes->header.messageId,
                                       registerMacRes->info.status,
                                       0 /* Not IOCTL cmd response */);
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_RES:
            {
                 Eth_RpcIpv4RegisterMacResponse *registerIpv4Res =
                                   (Eth_RpcIpv4RegisterMacResponse *)msgBuffer;

                if ((registerIpv4Res->header.messageId == ETH_RPC_CMD_TYPE_IPV4_MAC_REGISTER_RES)
                    &&
                    (registerIpv4Res->header.messageLen == sizeof(*registerIpv4Res)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType)registerIpv4Res->header.messageId,
                                       registerIpv4Res->info.status,
                                       0 /* Not IOCTL cmd response */);
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_RES:
            {
                 Eth_RpcIpv4UnregisterMacResponse *unregisterIpv4Res =
                                 (Eth_RpcIpv4UnregisterMacResponse *)msgBuffer;

                if ((unregisterIpv4Res->header.messageId == ETH_RPC_CMD_TYPE_IPV4_MAC_UNREGISTER_RES)
                    &&
                    (unregisterIpv4Res->header.messageLen == sizeof(*unregisterIpv4Res)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType)unregisterIpv4Res->header.messageId,
                                       unregisterIpv4Res->info.status,
                                       0 /* Not IOCTL cmd response */);
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_UNREGISTER_MAC_RES:
            {
                Eth_RpcUnregisterMacResponse * unregisterMacRes =
                                     (Eth_RpcUnregisterMacResponse *)msgBuffer;

                if ((unregisterMacRes->header.messageId == ETH_RPC_CMD_TYPE_UNREGISTER_MAC_RES)
                    &&
                    (unregisterMacRes->header.messageLen == sizeof(*unregisterMacRes)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType)unregisterMacRes->header.messageId,
                                       unregisterMacRes->info.status,
                                       0 /* Not IOCTL cmd response */);
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_IOCTL_RES:
            {
                Eth_RpcIoctlResponse *ioctlRes =
                                             (Eth_RpcIoctlResponse *)msgBuffer;

                if ((ioctlRes->header.messageId == ETH_RPC_CMD_TYPE_IOCTL_RES)
                    &&
                    (ioctlRes->header.messageLen == sizeof(*ioctlRes)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType)ioctlRes->header.messageId,
                                       ioctlRes->info.status,
                                       ioctlRes->cmd);

                    if (ETH_RPC_CMDSTATUS_OK == ioctlRes->info.status)
                    {
                        Eth_RpcProcessIoctlRes(ioctlRes);
                    }
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }

            case ETH_RPC_CMD_TYPE_S2C_NOTIFY:
            {
                 Eth_RpcS2CNotify *s2cNotify = (Eth_RpcS2CNotify *)msgBuffer;

                if ((s2cNotify->header.messageId == ETH_RPC_CMD_TYPE_S2C_NOTIFY)
                    &&
                    (s2cNotify->header.messageLen == sizeof(*s2cNotify)))
                {
                    Eth_RpcProcessS2CNotify(s2cNotify, callerApiId);
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            case ETH_RPC_CMD_TYPE_DETACH_RES:
            {
                Eth_RpcDetachResponse *detachRes = (Eth_RpcDetachResponse *)msgBuffer;

                if ((detachRes->header.messageId == ETH_RPC_CMD_TYPE_DETACH_RES)
                    &&
                    (detachRes->header.messageLen == sizeof(*detachRes)))
                {
                    Eth_RpcMsgStatusCb(ctrlIdx,
                                       Eth_VirtMacGetRpcCmdCompleteFuncPtr(ctrlIdx),
                                       (Eth_RpcCmdType)detachRes->header.messageId,
                                       detachRes->info.status,
                                       0 /* Not IOCTL cmd response */);
                    Eth_VirtMacInfo[ctrlIdx].detachResponsePending = FALSE;
                }
                else
                {
                    status = E_NOT_OK;
                }
                break;
            }
            default:
            {
            }
        }
    } /* if ((status == E_OK) && (msgSize <= sizeof(msgBuffer))) */
    return status;
}


Std_ReturnType Eth_RpcSendAddVlan(uint8 ctrlIdx, uint32 vlanId,
                                  Eth_PortListType *portList)
{
    Eth_CpswAle_VlanEntryInfo addVlanInArgs;
    Std_ReturnType status;

    status = Eth_RpcValidatePortList(portList);
    if ((E_OK == status)
        &&
        (Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        uint32 portMask;

        status = Eth_RpcGetPortMask(portList, &portMask);
        if (E_OK == status)
        {
            memset(&addVlanInArgs, 0, sizeof(addVlanInArgs));
            addVlanInArgs.vlanIdInfo.vlanId        = vlanId;
            addVlanInArgs.vlanIdInfo.tagType       = ETH_ENET_VLAN_TAG_TYPE_INNER;
            addVlanInArgs.vlanMemberList           = portMask;
            addVlanInArgs.unregMcastFloodMask      = portMask;
            addVlanInArgs.regMcastFloodMask        = portMask;
            addVlanInArgs.forceUntaggedEgressMask  = 0U;
            addVlanInArgs.noLearnMask              = 0U;
            addVlanInArgs.vidIngressCheck          = FALSE;
            addVlanInArgs.limitIPNxtHdr            = FALSE;
            addVlanInArgs.disallowIPFrag           = FALSE;

            status = Eth_RpcSendIoctlReq(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                         &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                         ETH_CPSW_ALE_IOCTL_ADD_VLAN,
                                         &addVlanInArgs,
                                         sizeof(addVlanInArgs),
                                         sizeof(uint32));
        }
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

Std_ReturnType Eth_RpcSendDelVlan(uint8 ctrlIdx, uint32 vlanId)
{
    Eth_CpswAle_VlanIdInfo delVlanInArgs;
    Std_ReturnType status;

    if ((Eth_VirtMacInfo[ctrlIdx].ethFwAttached == TRUE)
        &&
        (Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo.id != 0))
    {
        memset(&delVlanInArgs, 0, sizeof(delVlanInArgs));
        delVlanInArgs.tagType = ETH_ENET_VLAN_TAG_TYPE_INNER;
        delVlanInArgs.vlanId = vlanId,

        status = Eth_RpcSendIoctlReq(Eth_VirtMacGetEthFwRpcComChannelId(ctrlIdx),
                                     &Eth_VirtMacInfo[ctrlIdx].cpswAttachInfo,
                                     ETH_CPSW_ALE_IOCTL_REMOVE_VLAN,
                                     &delVlanInArgs,
                                     sizeof(delVlanInArgs),
                                     0);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

#define ETH_STOP_SEC_CODE
#include "Eth_MemMap.h"
