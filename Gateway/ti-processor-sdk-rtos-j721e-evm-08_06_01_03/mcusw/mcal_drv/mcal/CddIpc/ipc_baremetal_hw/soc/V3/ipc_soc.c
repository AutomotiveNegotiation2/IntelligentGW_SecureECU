/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2020
 *  All rights reserved.
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

/**
 *  \file ipc_soc.c
 *
 *  \brief File containing the IPC driver - soc specific implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <CddIpc/ipc_baremetal_hw/ipc.h>
#include <CddIpc/ipc_baremetal_hw/src/ipc_mailbox.h>
#include <ti/drv/sciclient/sciclient.h>

#define TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS (uint8)58
#define TISCI_DEV_MCU_R5FSS0_CORE0 (uint8)346
#define TISCI_DEV_MCU_R5FSS0_CORE1 (uint8)347
#define TISCI_DEV_R5FSS0_CORE0 (uint8)339
#define TISCI_DEV_R5FSS0_CORE1 (uint8)340
#define TISCI_DEV_R5FSS1_CORE0 (uint8)341
#define TISCI_DEV_R5FSS1_CORE1 (uint8)342
#define TISCI_DEV_R5FSS2_CORE0 (uint8)343
#define TISCI_DEV_R5FSS2_CORE1 (uint8)344
#define TISCI_DEV_COMPUTE_CLUSTER0_CLEC (uint8)44
#define TISCI_RESASG_SUBTYPE_IR_OUTPUT (0x0000U)
#define TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST (0xFFu)

/**
 * \ Dependencies from pdk Sciclient
 */



#define NAVSS_INTRTR_INPUT_MAILBOX0_USER0   (436U)
#define NAVSS_INTRTR_INPUT_MAILBOX1_USER0   (432U)
#define NAVSS_INTRTR_INPUT_MAILBOX2_USER0   (428U)
#define NAVSS_INTRTR_INPUT_MAILBOX3_USER0   (424U)
#define NAVSS_INTRTR_INPUT_MAILBOX4_USER0   (420U)
#define NAVSS_INTRTR_INPUT_MAILBOX5_USER0   (416U)
#define NAVSS_INTRTR_INPUT_MAILBOX6_USER0   (412U)
#define NAVSS_INTRTR_INPUT_MAILBOX7_USER0   (408U)
#define NAVSS_INTRTR_INPUT_MAILBOX8_USER0   (404U)
#define NAVSS_INTRTR_INPUT_MAILBOX9_USER0   (400U)
#define NAVSS_INTRTR_INPUT_MAILBOX10_USER0  (396U)
#define NAVSS_INTRTR_INPUT_MAILBOX11_USER0  (392U)

#define    IPC_INTERRUPT_OFFSET                             (6U)

/**
 * \brief Main NavSS512 - Mailbox input line
 */
uint32 g_Navss512MbInput[IPC_MAILBOX_CLUSTER_CNT] =
{
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_0_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_1_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_2_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_3_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_4_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_5_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_6_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_7_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_8_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_9_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_10_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX_11_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX1_0_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX1_1_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX1_2_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX1_3_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX1_4_PEND_INTR_0,
    CSLR_NAVSS0_INTR_0_IN_INTR_NAVSS0_MAILBOX1_5_PEND_INTR_0

};

uint32 Ipc_getNavss512MailboxInputIntr(uint32 clusterId, uint32 userId);
int32_t Ipc_setCoreEventId(uint32 selfId, Ipc_MbConfig* cfg, uint32 intrCnt);
int32_t Ipc_sciclientIrqTranslate(uint16 coreId, uint32 eventId,
        uint16 *procIrq);

int32_t Ipc_getMailboxInfoTx(uint32 selfId, uint32 remoteId,
                 uint32 *clusterId, uint32 *userId, uint32 *queueId)
{
    int32_t retVal = -1;

    if( (selfId < IPC_MAX_PROCS) &&
        (remoteId < IPC_MAX_PROCS))
    {
        Ipc_MailboxInfo   *pMailboxInfo = &g_IPC_MailboxInfo[selfId][remoteId];

        *clusterId = pMailboxInfo->tx.cluster;
        *userId    = pMailboxInfo->tx.user;
        *queueId   = pMailboxInfo->tx.fifo;
        retVal = 0;
    }

    return retVal;
}

int32_t Ipc_getMailboxInfoRx(uint32 selfId, uint32 remoteId,
                 uint32 *clusterId, uint32 *userId, uint32 *queueId)
{
    int32_t retVal = -1;

    if( (selfId < IPC_MAX_PROCS) &&
        (remoteId < IPC_MAX_PROCS))
    {
        Ipc_MailboxInfo   *pMailboxInfo = &g_IPC_MailboxInfo[selfId][remoteId];

        *clusterId = pMailboxInfo->rx.cluster;
        *userId    = pMailboxInfo->rx.user;
        *queueId   = pMailboxInfo->rx.fifo;
        retVal = 0;
    }

    return retVal;

}

uintptr_t Ipc_getMailboxBaseAddr(uint32 clusterId)
{
    uintptr_t baseAddr = 0x00000000U;

    if( clusterId < IPC_MAILBOX_CLUSTER_CNT)
    {
        baseAddr = IPC_Mailbox_BasePhyAddr[clusterId];
    }

    return baseAddr;
}

const UCHAR* Ipc_getCoreName(uint32 procId)
{
    UCHAR*     p = (UCHAR*)0;
    uint32 id = procId;

    if(id < IPC_MAX_PROCS)
    {
       p = g_Ipc_mp_procInfo[id].name;
    }
    return p;
}

uint32 Ipc_getNavss512MailboxInputIntr(uint32 clusterId, uint32 userId)
{
    uint32  mailboxIntrNum = 0U;

    if( (clusterId != MAILBOX_CLUSTER_INVALID) &&
        (clusterId < IPC_MAILBOX_CLUSTER_CNT)  &&
        (userId != MAILBOX_USER_INVALID)       &&
        (userId < IPC_MAILBOX_USER_CNT))
    {
        mailboxIntrNum = g_Navss512MbInput[clusterId] + userId;
    }
    return mailboxIntrNum;
}

int32_t Ipc_setCoreEventId(uint32 selfId, Ipc_MbConfig* cfg, uint32 intrCnt)
{
    int32_t    retVal          = IPC_SOK;
    uint32   outIntrBaseNum  = 0;
    uint32   vimEventBaseNum = 0;
    uint16   proc_irq        = 0;

    /*
     * static variable to used to store the base for first
     * mailbox interrupt register. In subsequent call, it uses
     * the offset of intrCnt from base
     */
    static uint16   start    = 0;
    static uint16   range    = 0;
    uint16   offset   = 0;

    /* Get available CorePack IRQ number from DMSC */
    if( (start == 0) && (range == 0))
    {
        /* Query the Interrupt Router o/p # alloacted for the core. */
        retVal = Ipc_getIntNumRange(selfId, &start, &range);
    }

    if((retVal == IPC_SOK) && (range >= 1))
    {
        /* Allocate the last 6 interrupts for IPC. Note that the IR allocation is
         * static so this needs to be carefully set. Currently first interrupt is
         * used by UDMA and middle one's are used by other modules like CPSW9G so
         * we are using last 6 as a safe option.
         */
        if(range >= IPC_INTERRUPT_OFFSET)
        {
            offset = IPC_INTERRUPT_OFFSET;
        }
        else
        {
            offset = range;
        }
        vimEventBaseNum = (start + range) - offset;

        /* Translation must happen after this offset */
        retVal = Ipc_sciclientIrqTranslate((uint16)selfId, vimEventBaseNum,
                                           &proc_irq);
        if (CSL_PASS == retVal)
        {
            vimEventBaseNum = proc_irq;
        }

    }
    else
    {
        retVal = IPC_EFAIL;
    }

    switch(selfId)
    {
        case IPC_MPU1_0:
            outIntrBaseNum = NAVSS512_MPU1_0_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_MCU1_0:
            outIntrBaseNum = NAVSS512_MCU1R5F0_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_MCU1_1:
            outIntrBaseNum = NAVSS512_MCU1R5F1_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_MCU2_0:
            outIntrBaseNum = NAVSS512_MCU2R5F0_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_MCU2_1:
            outIntrBaseNum = NAVSS512_MCU2R5F1_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_MCU3_0:
            outIntrBaseNum = NAVSS512_MCU3R5F0_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_MCU3_1:
            outIntrBaseNum = NAVSS512_MCU3R5F1_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_C7X_1:
            outIntrBaseNum = NAVSS512_C7X1_INPUT_MAILBOX_OFFSET;
            break;
        case IPC_C7X_2:
            outIntrBaseNum = NAVSS512_C7X2_INPUT_MAILBOX_OFFSET;
            break;
        default:
            break;
    }
    cfg->outputIntrNum = outIntrBaseNum + intrCnt;
    cfg->eventId       = vimEventBaseNum + intrCnt;

    return retVal;
}

int32_t Ipc_getMailboxIntrRouterCfg(uint32 selfId, uint32 clusterId,
        uint32 userId, Ipc_MbConfig* cfg, uint32 cnt)
{
    int32_t    retVal         = IPC_SOK;
    uint32   mailboxIntrNum = 0;

    /* Get Navss512 input interrupt number for mailbox */
    mailboxIntrNum = Ipc_getNavss512MailboxInputIntr(clusterId, userId);

    cfg->inputIntrNum  = mailboxIntrNum;
    cfg->priority      = 1U;
    retVal = Ipc_setCoreEventId(selfId, cfg, cnt);

    return retVal;
}

#ifdef IPC_SUPPORT_SCICLIENT

/* Indexed list of dst ids */
static const uint16 map_dst_id[] =
{
    TISCI_DEV_COMPUTE_CLUSTER0_GIC500SS,
    TISCI_DEV_MCU_R5FSS0_CORE0,
    TISCI_DEV_MCU_R5FSS0_CORE1,
    TISCI_DEV_R5FSS0_CORE0,
    TISCI_DEV_R5FSS0_CORE1,
    TISCI_DEV_R5FSS1_CORE0,
    TISCI_DEV_R5FSS1_CORE1,
    TISCI_DEV_R5FSS2_CORE0,
    TISCI_DEV_R5FSS2_CORE1,
    TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
    TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
    TISCI_DEV_COMPUTE_CLUSTER0_CLEC,
    TISCI_DEV_COMPUTE_CLUSTER0_CLEC
};

/* Indexed list of req type */
static const uint16 req_type[] =
{
    /* NOTE: This list should match the Core index */
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0,
    TISCI_DEV_NAVSS0_INTR_0

};


/* Indexed list of req subtype */
static const uint16 req_subtype[] =
{
    /* NOTE: This list should match the Core index */
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT,
    TISCI_RESASG_SUBTYPE_IR_OUTPUT
};

int32_t Ipc_sciclientIrqTranslate(uint16 coreId, uint32 eventId,
        uint16 *procIrq)
{
    return Sciclient_rmIrqTranslateIrOutput(req_type[coreId],
                                            (uint16)eventId,
                                            map_dst_id[coreId],
                                            procIrq);
}

int32_t Ipc_getIntNumRange(uint32 coreIndex,
        uint16 *rangeStartP, uint16 *rangeNumP)
{
    int32_t                                     retVal = IPC_SOK;
    struct tisci_msg_rm_get_resource_range_resp res = {0};
    struct tisci_msg_rm_get_resource_range_req  req = {0};

    req.type           = req_type[coreIndex];
    req.subtype        = (uint8)req_subtype[coreIndex];
    req.secondary_host = (uint8)TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;

    res.range_num = 0;
    res.range_start = 0;

    /* Get interrupt number range */
    retVal =  Sciclient_rmGetResourceRange(
                &req,
                &res,
                IPC_SCICLIENT_TIMEOUT);
    if (CSL_PASS != retVal || res.range_num == 0) {
        /* Try with HOST_ID_ALL */
        req.type           = req_type[coreIndex];
        req.subtype        = (uint8)req_subtype[coreIndex];
        req.secondary_host = TISCI_HOST_ID_ALL;

        retVal = Sciclient_rmGetResourceRange(
                &req,
                &res,
                IPC_SCICLIENT_TIMEOUT);
    }
    if (CSL_PASS == retVal)
    {
        *rangeStartP = res.range_start;
        *rangeNumP = res.range_num;
    }
    return retVal;
}

#endif

uint32 Ipc_getCoreId(void)
{
    uint32 selfId =  IPC_INVALID_PROCID;

#if defined(BUILD_MPU1_0)
    selfId = IPC_MPU1_0;
#elif defined(BUILD_MCU1_0)
    selfId = IPC_MCU1_0;
#elif defined(BUILD_MCU1_1)
    selfId = IPC_MCU1_1;
#elif defined(BUILD_MCU2_0)
    selfId = IPC_MCU2_0;
#elif defined(BUILD_MCU2_1)
    selfId = IPC_MCU2_1;
#elif defined(BUILD_MCU3_0)
    selfId = IPC_MCU3_0;
#elif defined(BUILD_MCU3_1)
    selfId = IPC_MCU3_1;
#elif defined(BUILD_MCU4_0)
    selfId = IPC_MCU4_0;
#elif defined(BUILD_MCU4_1)
    selfId = IPC_MCU4_1;
#elif defined(BUILD_C7X_1)
    selfId = IPC_C7X_1;
#elif defined(BUILD_C7X_2)
    selfId = IPC_C7X_2;
#elif defined(BUILD_C7X_3)
    selfId = IPC_C7X_3;
#elif defined(BUILD_C7X_4)
    selfId = IPC_C7X_4;
#else
#error "Unsupported core Id"
#endif

    return (selfId);
}
