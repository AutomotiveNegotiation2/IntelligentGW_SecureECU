/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <ti/drv/ipc/ipc.h>
#include <ti/osal/osal.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/TaskP.h>

#include <utils/perf_stats/include/app_perf_stats.h>
#include <utils/console_io/include/app_log.h>
#include <utils/ipc/include/app_ipc.h>
#include <utils/misc/include/app_misc.h>

/* #define APP_IPC_ECHO_TEST_DEBUG */

#define MSGSIZE  512
#define SERVICE  "ti.ipc4.ping-pong"
#define ENDPT1   APP_IPC_ECHO_TEST_RPMSG_PORT_ID
#define NUMMSGS  2   /* number of message sent per task */

#define APP_IPC_ECHO_TEST_TASK_STACKSIZE       (64*1024)

#if defined(R5F) && defined(SAFERTOS)
#define APP_IPC_ECHO_TEST_TASK_ALIGNMENT    (64*1024)
#else
#define APP_IPC_ECHO_TEST_TASK_ALIGNMENT    (8192u)
#endif

/* this should be >= RPMessage_getObjMemRequired() */
#define IPC_RPMESSAGE_OBJ_SIZE  (256)

#define RPMSG_DATA_SIZE         (256*MSGSIZE + IPC_RPMESSAGE_OBJ_SIZE)

#if defined (SOC_J721E)
static uint32_t g_app_to_ipc_cpu_id[APP_IPC_CPU_MAX] =
{
    IPC_MPU1_0,
    IPC_MCU1_0,
    IPC_MCU1_1,
    IPC_MCU2_0,
    IPC_MCU2_1,
    IPC_MCU3_0,
    IPC_MCU3_1,
    IPC_C66X_1,
    IPC_C66X_2,
    IPC_C7X_1
};
#endif

#if defined (SOC_J721S2)
static uint32_t g_app_to_ipc_cpu_id[APP_IPC_CPU_MAX] =
{
    IPC_MPU1_0,
    IPC_MCU1_0,
    IPC_MCU1_1,
    IPC_MCU2_0,
    IPC_MCU2_1,
    IPC_MCU3_0,
    IPC_MCU3_1,
    IPC_C7X_1,
    IPC_C7X_2
};
#endif

#if defined (SOC_J784S4)
static uint32_t g_app_to_ipc_cpu_id[APP_IPC_CPU_MAX] =
{
    IPC_MPU1_0,
    IPC_MCU1_0,
    IPC_MCU1_1,
    IPC_MCU2_0,
    IPC_MCU2_1,
    IPC_MCU3_0,
    IPC_MCU3_1,
    IPC_MCU4_0,
    IPC_MCU4_1,
    IPC_C7X_1,
    IPC_C7X_2,
    IPC_C7X_3,
    IPC_C7X_4
};
#endif

#if defined (SOC_AM62A)
static uint32_t g_app_to_ipc_cpu_id[APP_IPC_CPU_MAX] =
{
    IPC_MPU1_0,
    IPC_MCU1_0,
    IPC_C7X_1
};
#endif

/* IMPORTANT NOTE: For C7x,
 * - stack size and stack ptr MUST be 8KB aligned
 * - AND min stack size MUST be 16KB
 * - AND stack assigned for task context is "size - 8KB"
 *       - 8KB chunk for the stack area is used for interrupt handling in this task context
 */
static uint8_t  g_taskStackBuf[APP_IPC_CPU_MAX][APP_IPC_ECHO_TEST_TASK_STACKSIZE]
__attribute__ ((section(".bss:taskStackSection")))
__attribute__ ((aligned(APP_IPC_ECHO_TEST_TASK_ALIGNMENT)))
    ;

#if defined(R5F) && defined(SAFERTOS)
#define APP_IPC_SENDBUF_TASK_ALIGNMENT    (262144u)
#else
#define APP_IPC_SENDBUF_TASK_ALIGNMENT    (128u)
#endif

#if defined(R5F) && defined(SAFERTOS)
#define APP_IPC_RSPBUF_TASK_ALIGNMENT    (16384u)
#else
#define APP_IPC_RSPBUF_TASK_ALIGNMENT    (128u)
#endif

static uint8_t  g_sendBuf[RPMSG_DATA_SIZE * APP_IPC_CPU_MAX]  __attribute__ ((aligned (APP_IPC_SENDBUF_TASK_ALIGNMENT)));
static uint8_t  g_rspBuf[RPMSG_DATA_SIZE]  __attribute__ ((aligned (APP_IPC_RSPBUF_TASK_ALIGNMENT)));

uint32_t g_ipc_echo_test_status[APP_IPC_CPU_MAX];

static SemaphoreP_Handle g_ipc_echo_test_lock;

#define APP_IPC_ECHO_TEST_MAX_TASK_NAME     (12u)
static char g_rpmsg_responder_task_name[APP_IPC_ECHO_TEST_MAX_TASK_NAME];
static char g_rpmsg_sender_task_name[APP_IPC_CPU_MAX][APP_IPC_ECHO_TEST_MAX_TASK_NAME];

static void appIpcEchoTestLock(void)
{
    if(g_ipc_echo_test_lock!=NULL)
    {
        SemaphoreP_pend(g_ipc_echo_test_lock, SemaphoreP_WAIT_FOREVER);
    }
}

static void appIpcEchoTestUnLock(void)
{
    if(g_ipc_echo_test_lock!=NULL)
    {
        SemaphoreP_post(g_ipc_echo_test_lock);
    }
}

static void appIpcEchoTestStatusUpdate(uint32_t dst_ipc_lld_cpu_id, uint32_t value)
{
    appIpcEchoTestLock();
    if(dst_ipc_lld_cpu_id < APP_IPC_CPU_MAX)
    {
        g_ipc_echo_test_status[dst_ipc_lld_cpu_id] = value;
    }
    appIpcEchoTestUnLock();
}

static void appIpcEchoTestStatusShow()
{
    #define BUF_SIZE (1024u)
    char buf[BUF_SIZE];
    uint32_t count = 0;
    uint32_t cpu_id;
    uint32_t all_pass;

    appIpcEchoTestLock();

    buf[count] = 0;

    all_pass = 1;

    count += snprintf(&buf[count], BUF_SIZE-count, "IPC: Echo status: ");
    for(cpu_id=0; cpu_id<APP_IPC_CPU_MAX; cpu_id++)
    {
        if(appIpcIsCpuEnabled(cpu_id))
        {
            char status_char = 's';

            if(cpu_id!=appIpcGetSelfCpuId())
            {
                if(g_ipc_echo_test_status[cpu_id]==(uint32_t)-1)
                {
                    status_char = 'x';
                    all_pass = 0;
                }
                else
                if(g_ipc_echo_test_status[cpu_id]==NUMMSGS)
                {
                    status_char = 'P';
                }
                else
                {
                    status_char = '.';
                    all_pass = 0;
                }
            }
            if (NULL != Ipc_mpGetName(g_app_to_ipc_cpu_id[cpu_id]))
            {
                count += snprintf(&buf[count], BUF_SIZE-count, "%s[%c] ",
                    Ipc_mpGetName(g_app_to_ipc_cpu_id[cpu_id]),
                    status_char
                    );
            }
        }
    }
    if(all_pass)
    {
        count += snprintf(&buf[count], BUF_SIZE-count, " - ALL PASSED !!!\n");
    }
    else
    {
        count += snprintf(&buf[count], BUF_SIZE-count, "\n");
    }

    appLogPrintf(buf);
    appIpcEchoTestUnLock();
}

/*
 * This "Task" waits for a "ping" message from any processor
 * then replies with a "pong" message.
 */
static void rpmsg_responderFxn(void* arg0, void* arg1)
{
    RPMessage_Handle    handle;
    RPMessage_Params    params;
    uint32_t    myEndPt = 0;
    uint32_t    remoteEndPt;
    uint32_t    remoteProcId;
    uint16_t    len;
    uint32_t    count;
    int32_t     n;
    int32_t     status = 0;
    void        *buf;
    uint32_t    bufSize = RPMSG_DATA_SIZE;
    char        str[MSGSIZE];

    appUtilsTaskInit();

    #ifdef APP_IPC_ECHO_TEST_DEBUG
    appLogPrintf("IPC: RecvTask: Started ...\n");
    #endif

    buf = g_rspBuf;
    RPMessageParams_init(&params);
    params.requestedEndpt = ENDPT1;
    params.buf = buf;
    params.bufSize = bufSize;

    handle = RPMessage_create(&params, &myEndPt);
    if(!handle)
    {
        appLogPrintf("IPC: RecvTask: Failed to create endpoint\n");
        status = -1;
    }

    if (status == 0)
    {
        status = RPMessage_announce(RPMESSAGE_ALL, myEndPt, SERVICE);
        if(status != 0)
        {
            appLogPrintf("IPC: RecvTask: RPMessage_announce() failed\n");
            status = -1;
        }

        count = 0;

        #ifdef APP_IPC_ECHO_TEST_DEBUG
        appLogPrintf("IPC: RecvTask: Waiting for messages ...\n");
        #endif

        while(1)
        {
            status = RPMessage_recv(handle, (void*)str, &len, &remoteEndPt, &remoteProcId,
            IPC_RPMESSAGE_TIMEOUT_FOREVER);
            if(status != IPC_SOK)
            {
                appLogPrintf("IPC: RecvTask: failed with code %d\n", status);
            }
            else
            {
                count++;
                /* NULL terminated string */
                str[len] = '\0';
                #ifdef APP_IPC_ECHO_TEST_DEBUG
                appLogPrintf("IPC: RecvTask: Revcvd msg #%d \"%s\" len %d bytes from %s\n",
                    count, str, len, Ipc_mpGetName(remoteProcId));
                #endif
            }

            status = sscanf(str, "ping %d", &n);
            if(status == 1)
            {
                len = snprintf(str, MSGSIZE-1, "pong %d", n);
            }

            #ifdef APP_IPC_ECHO_TEST_DEBUG
            appLogPrintf("IPC: RecvTask: Sending msg #%d \"%s\" len %d bytes from %s to %s\n",
                count, str, len, Ipc_mpGetSelfName(),
                Ipc_mpGetName(remoteProcId));
            #endif

            status = RPMessage_send(handle, remoteProcId, remoteEndPt, myEndPt, str, len);
            if (status != IPC_SOK)
            {
                appLogPrintf("IPC: RecvTask: RPMessage_send "
                    " failed, status %d procId %d\n", status, remoteProcId);
            }
        }
    }

    /* Delete the RPMesg object now */
    //RPMessage_delete(&handle);
}

static void rpmsg_senderFxn(void* arg0, void* arg1)
{
    RPMessage_Handle    handle;
    RPMessage_Params    params;
    uint32_t            myEndPt = 0;
    uint32_t            remoteEndPt;
    uint32_t            remoteProcId;
    uint16_t            dstProc;
    uint32_t            appDstProcId;
    uint16_t            len;
    int32_t             i;
    int32_t             status = 0;
    char                buf[MSGSIZE];
    uint8_t            *buf1;

    appUtilsTaskInit();

    dstProc = (uint16_t)((uintptr_t)arg0);
    appDstProcId = (uint32_t)((uintptr_t)arg1);

    buf1 = &g_sendBuf[RPMSG_DATA_SIZE * appDstProcId];

    /* appIpcEchoTestStatusShow(); */

    #ifdef APP_IPC_ECHO_TEST_DEBUG
    appLogPrintf("IPC: SendTask%d: Started ... \n", dstProc);
    #endif

    /* Create the endpoint for receiving. */
    RPMessageParams_init(&params);
    params.numBufs = 2;
    params.buf = buf1;
    params.bufSize = RPMSG_DATA_SIZE;
    handle = RPMessage_create(&params, &myEndPt);
    if(!handle)
    {
        appLogPrintf("IPC: SendTask%d: Failed to create message endpoint\n",
             dstProc);
        status = -1;
    }

    status = RPMessage_getRemoteEndPt(dstProc, SERVICE, &remoteProcId,
                             &remoteEndPt, SemaphoreP_WAIT_FOREVER);

    if(dstProc != remoteProcId)
    {
        appLogPrintf("IPC: SendTask%d: RPMessage_getRemoteEndPt() malfunctioned, status %d\n",
             dstProc, status);
        status = -1;
    }

    if (status == 0)
    {
        appIpcEchoTestStatusUpdate(appDstProcId, 0);
        /* appIpcEchoTestStatusShow(); */

        #ifdef APP_IPC_ECHO_TEST_DEBUG
        appLogPrintf("IPC: SendTask%d: Sending messages to %s ... \n", dstProc, Ipc_mpGetName(dstProc));
        #endif

        for (i = 0; i < NUMMSGS; i++)
        {
            /* Send data to remote endPt: */
            len = snprintf(buf, MSGSIZE-1, "ping %d", i);
            buf[len++] = '\0';
            #ifdef APP_IPC_ECHO_TEST_DEBUG
            appLogPrintf("IPC: SendTask%d: Sending msg #%d \"%s\" from %s to %s...\n", dstProc,
                    i, buf, Ipc_mpGetSelfName(),
                    Ipc_mpGetName(dstProc));
            #endif
            status = RPMessage_send(handle, dstProc, ENDPT1, myEndPt, (Ptr)buf, len);
            if (status != IPC_SOK)
            {
                appLogPrintf("IPC: SendTask%d: rpmsg_senderFxn: RPMessage_send "
                " failed status %d\n", dstProc, status);
            }
            if (status == IPC_SOK)
            {
                /* wait a for a response message: */
                status = RPMessage_recv(handle, (void*)buf, &len, &remoteEndPt,
                                 &remoteProcId, IPC_RPMESSAGE_TIMEOUT_FOREVER);

                if(status != IPC_SOK)
                {
                    appLogPrintf("IPC: SendTask%d: RPMessage_recv failed with status %d\n",
                            dstProc, status);
                }

                /* Make it NULL terminated string */
                if(len >= MSGSIZE)
                {
                    buf[MSGSIZE-1] = '\0';
                }
                else
                {
                    buf[len] = '\0';
                }
                if(status==IPC_SOK)
                {
                    #ifdef APP_IPC_ECHO_TEST_DEBUG
                    appLogPrintf("IPC: SendTask%d: Received msg #%d \"%s\" len %d bytes from %s endPt %d \n",
                        dstProc, i, buf, len, Ipc_mpGetName(remoteProcId),
                        remoteEndPt);
                    #endif
                    appIpcEchoTestStatusUpdate(appDstProcId, i+1);
                }
            }
        }
        #ifdef APP_IPC_ECHO_TEST_DEBUG
        appLogPrintf("IPC: SendTask%d: Finished test with %s\n", dstProc,
             Ipc_mpGetName(dstProc));
        #endif
        appIpcEchoTestStatusShow();
    }


    /* Delete the RPMesg object now */
    RPMessage_delete(&handle);
}

int32_t appIpcEchoTestStart(void)
{
    uint32_t          cpu_id;
    TaskP_Params      params;
    uint32_t          numProc = APP_IPC_CPU_MAX;
    int32_t status = 0;
    SemaphoreP_Params semParams;
    TaskP_Handle rx_task, tx_task[APP_IPC_CPU_MAX];

    appLogPrintf("IPC: Starting echo test ...\n");

    /* Default parameter initialization */
    SemaphoreP_Params_init(&semParams);
    semParams.mode = SemaphoreP_Mode_BINARY;
    g_ipc_echo_test_lock = SemaphoreP_create(1U, &semParams);
    if(g_ipc_echo_test_lock==NULL)
    {
        appLogPrintf("IPC: ERROR: Failed to create lock !!!\n");
        status = -1;
    }

    if(status==0)
    {
        for(cpu_id = 0; cpu_id < APP_IPC_CPU_MAX; cpu_id++)
        {
            appIpcEchoTestStatusUpdate(cpu_id, (uint32_t)-1);
        }

        #ifdef APP_IPC_ECHO_TEST_DEBUG
        appLogPrintf("IPC: RecvTask: Creating ...\n");
        #endif

        /* Respond to messages coming in to endPt ENDPT1 */
        cpu_id = appIpcGetSelfCpuId();

        TaskP_Params_init(&params);
        params.priority = 3;
        params.stack     = g_taskStackBuf[cpu_id];
        params.stacksize = APP_IPC_ECHO_TEST_TASK_STACKSIZE;
        params.arg0 = 0;
        params.name = (const char*)&g_rpmsg_responder_task_name[0];

        strncpy(g_rpmsg_responder_task_name, "IPC_TEST_RX", APP_IPC_ECHO_TEST_MAX_TASK_NAME);
        g_rpmsg_responder_task_name[APP_IPC_ECHO_TEST_MAX_TASK_NAME-1] = 0;

        rx_task = TaskP_create(&rpmsg_responderFxn, &params);
        if(rx_task==NULL)
        {
            appLogPrintf("IPC: ERROR: Failed to create RX task !!!\n");
            status = -1;
        }
        else
        {
            appPerfStatsRegisterTask(rx_task, g_rpmsg_responder_task_name);
        }
        if(status==0)
        {
            for(cpu_id = 0; cpu_id < numProc; cpu_id++)
            {
                if((cpu_id != appIpcGetSelfCpuId()) && appIpcIsCpuEnabled(cpu_id))
                {
                    uint32_t ipc_lld_cpu_id = g_app_to_ipc_cpu_id[cpu_id];

                    #ifdef APP_IPC_ECHO_TEST_DEBUG
                    appLogPrintf("IPC: SendTask%d: Creating ...\n", ipc_lld_cpu_id);
                    #endif
                    /* send messages to peer(s) on ENDPT1 */
                    TaskP_Params_init(&params);
                    params.priority = 3;
                    params.stack     = g_taskStackBuf[cpu_id];
                    params.stacksize = APP_IPC_ECHO_TEST_TASK_STACKSIZE;
                    params.arg0     = (void*)ipc_lld_cpu_id;
                    params.arg1     = (void*)cpu_id;
                    params.name     = (const char*)&g_rpmsg_sender_task_name[cpu_id][0];

                    strncpy(g_rpmsg_sender_task_name[cpu_id], "IPC_TEST_TX", APP_IPC_ECHO_TEST_MAX_TASK_NAME);
                    g_rpmsg_sender_task_name[cpu_id][APP_IPC_ECHO_TEST_MAX_TASK_NAME-1] = 0;

                    tx_task[cpu_id] = TaskP_create(&rpmsg_senderFxn, &params);
                    if(tx_task[cpu_id]==NULL)
                    {
                        appLogPrintf("IPC: ERROR: Failed to create TX task %d !!!\n", cpu_id);
                        status = -1;
                    }
                    else
                    {
                        appPerfStatsRegisterTask(tx_task[cpu_id], g_rpmsg_sender_task_name[cpu_id]);
                    }
                }
            }
        }
    }

    return status;
}
