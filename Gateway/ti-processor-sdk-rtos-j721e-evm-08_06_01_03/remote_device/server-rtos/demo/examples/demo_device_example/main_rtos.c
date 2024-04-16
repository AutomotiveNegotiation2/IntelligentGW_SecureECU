/*
 *
 * Copyright (c) 2017-2021 Texas Instruments Incorporated
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
#include <stdio.h>
#include <stdint.h>

/* OSAL */
#include <ti/osal/osal.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/TaskP.h>

#include <ti/drv/ipc/ipc.h>

#include <server-rtos/remote-device.h>
#include <server-rtos/include/app_remote_device_demo.h>

#include "ipc_rsctable.h"

/* this should be >= RPMessage_getObjMemRequired() */
#define IPC_RPMESSAGE_OBJ_SIZE  256
/* this should be >= RPMessage_getMessageBufferSize() */
#define IPC_RPMESSAGE_MSG_BUFFER_SIZE  (496U + 32U)
#define VQ_BUF_SIZE             2048
#define REMOTE_DEVICE_ENDPT     26
#define RPMSG_DATA_SIZE         (256U*IPC_RPMESSAGE_MSG_BUFFER_SIZE + IPC_RPMESSAGE_OBJ_SIZE)
#if defined(SOC_J721E)
#define VRING_BASE_ADDRESS      0xAA000000
#elif defined(SOC_J7200)
#define VRING_BASE_ADDRESS      0xA4000000
#elif defined(SOC_J721S2)
#define VRING_BASE_ADDRESS      0xA8000000
#elif defined(SOC_J784S4)
#define VRING_BASE_ADDRESS      0xAC000000
#endif

#include "ipc_trace.h"
#define App_printf  Ipc_Trace_printf

static uint8_t g_monitorStackBuf[IPC_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));
static uint8_t g_rdevStackBuf[IPC_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));
static uint8_t g_ipcStackBuf[IPC_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));
static uint8_t g_vdevMonStackBuf[IPC_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));
static uint8_t g_mainStackBuf[IPC_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));
static uint8_t ctrlTaskBuf[IPC_TASK_STACKSIZE] __attribute__ ((section(".bss:taskStackSection"))) __attribute__ ((aligned(8192)));

static uint8_t  sysVqBuf[VQ_BUF_SIZE]  __attribute__ ((section ("ipc_data_buffer"), aligned (8)));
static uint8_t  gCntrlBuf[RPMSG_DATA_SIZE] __attribute__ ((section("ipc_data_buffer"), aligned (8)));

static SemaphoreP_Handle g_rdev_init_wait_sem;
static SemaphoreP_Handle g_ipc_init_wait_sem;
static SemaphoreP_Handle g_rdev_start_sem;

static uint32_t selfProcId = IPC_MCU2_1;
static uint32_t gRemoteProc[] =
{
#if defined(SOC_J721E)
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
#elif defined(SOC_J7200)
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0
#elif defined(SOC_J721S2)
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C7X_1, IPC_C7X_2
#elif defined(SOC_J784S4)
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_MCU4_0, IPC_MCU4_1, IPC_C7X_1, IPC_C7X_2, IPC_C7X_3, IPC_C7X_4
#endif
};
static uint32_t gNumRemoteProc = sizeof(gRemoteProc)/sizeof(uint32_t);

/* App Log Print max line length */
#define APP_LOG_PRINT_MAX_LINE_LENGTH  ((uint32_t) 512U)

void appLogPrintf(const char *format, ...)
{
    char buffer[APP_LOG_PRINT_MAX_LINE_LENGTH];
    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    App_printf("%s", buffer);
}

static void rpmsg_vdevMonitorFxn(void* arg0, void* arg1)
{
    int32_t status;

    /* Wait for Linux VDev ready... */
    while(!Ipc_isRemoteReady(IPC_MPU1_0))
    {
        TaskP_sleep(10);
    }

    /* Create the VRing now ... */
    status = Ipc_lateVirtioCreate(IPC_MPU1_0);
    if(status != IPC_SOK)
    {
        App_printf("%s: Ipc_lateVirtioCreate failed\n", __func__);
        return;
    }

    status = RPMessage_lateInit(IPC_MPU1_0);
    if(status != IPC_SOK)
    {
        App_printf("%s: RPMessage_lateInit failed\n", __func__);
        return;
    }

    status = appRemoteDeviceLateAnnounce(IPC_MPU1_0);
    if(status != IPC_SOK)
    {
        App_printf("%s: RPMessage_announce() failed\n", __func__);
    }
}

static void monitorAndUnlockRdev(void* a0, void* a1)
{
    SemaphoreP_pend(g_ipc_init_wait_sem, SemaphoreP_WAIT_FOREVER);
    SemaphoreP_pend(g_rdev_init_wait_sem, SemaphoreP_WAIT_FOREVER);
    SemaphoreP_post(g_rdev_start_sem);

}

static void ipcPrintFxn(const char *str)
{
    App_printf("%s", str);

    return;
}

static void ipc_init(void* a0, void* a1)
{
    TaskP_Params      params;
    uint32_t          numProc = gNumRemoteProc;
    Ipc_VirtIoParams  vqParam;
    Ipc_InitPrms      initPrms;

    /* Initialize params with defaults */
    IpcInitPrms_init(0U, &initPrms);
    
    initPrms.printFxn = &ipcPrintFxn;

    Ipc_init(&initPrms);

    /* Step1 : Initialize the multiproc */
    Ipc_mpSetConfig(selfProcId, numProc, &gRemoteProc[0]);

    App_printf("IPC_echo_test (core : %s) .....\r\n",
            Ipc_mpGetSelfName());


    Ipc_loadResourceTable((void*)&ti_ipc_remoteproc_ResourceTable);

    /* Step2 : Initialize Virtio */
    vqParam.vqObjBaseAddr = (void*)&sysVqBuf[0];
    vqParam.vqBufSize     = numProc * Ipc_getVqObjMemoryRequiredPerCore();
    vqParam.vringBaseAddr = (void*)VRING_BASE_ADDRESS;
    vqParam.vringBufSize  = IPC_VRING_BUFFER_SIZE;
    vqParam.timeoutCnt    = 100;  /* Wait for counts */
    Ipc_initVirtIO(&vqParam);

    /* Step 3: Initialize RPMessage */
    RPMessage_Params cntrlParam;

    /* Initialize the param */
    RPMessageParams_init(&cntrlParam);

    /* Set memory for HeapMemory for control task */
    cntrlParam.buf         = &gCntrlBuf[0];
    cntrlParam.bufSize     = RPMSG_DATA_SIZE;
    cntrlParam.stackBuffer = &ctrlTaskBuf[0];
    cntrlParam.stackSize   = IPC_TASK_STACKSIZE;
    RPMessage_init(&cntrlParam);

    SemaphoreP_post(g_ipc_init_wait_sem);

    TaskP_Params_init(&params);
    params.priority = 3;
    params.stacksize = IPC_TASK_STACKSIZE;
    params.stack = &g_vdevMonStackBuf[0];
    params.stacksize = IPC_TASK_STACKSIZE;
    TaskP_create(&rpmsg_vdevMonitorFxn, &params);
}

static void remotedev_init(void* a0, void* a1)
{
    app_remote_device_init_prm_t remote_dev_init_prm;
    app_remote_demo_init_prm_t remote_demo_init_prm;
    app_remote_demo_inst_prm_t *inst;


    appRemoteDeviceInitParamsInit(&remote_dev_init_prm);

    remote_dev_init_prm.rpmsg_buf_size = 256;
    remote_dev_init_prm.remote_device_endpt = REMOTE_DEVICE_ENDPT;
    remote_dev_init_prm.wait_sem = g_rdev_start_sem;

    appRemoteDeviceInit(&remote_dev_init_prm);
    App_printf("Remote device (core : mcu2_1) .....\r\n");

    appRemoteDemoInitPrmSetDefault(&remote_demo_init_prm);

    remote_demo_init_prm.rpmsg_buf_size = 256;
    remote_demo_init_prm.num_instances = 1;

    inst = &remote_demo_init_prm.inst_prm[0];
    inst->host_id = IPC_MCU2_0;
    {
        snprintf((char *)&inst->name[0], APP_REMOTE_DEMO_MAX_NAME_LEN, "mcu2_1-demo-device-0");
        snprintf((char *)&inst->data[0], APP_REMOTE_DEMO_MAX_DATA_LEN, "mcu2_1-demo-device-0-data");
    }

    appRemoteDemoInit(&remote_demo_init_prm);
    App_printf("Remote demo device (core : mcu2_1) .....\r\n");

    SemaphoreP_post(g_rdev_init_wait_sem);
}

static void taskFxn(void* a0, void* a1)
{

    TaskP_Params ipc_taskParams;
    TaskP_Params rdev_taskParams;
    TaskP_Params monitor_taskParams;
    SemaphoreP_Params sem_params;

    SemaphoreP_Params_init(&sem_params);
    sem_params.mode = SemaphoreP_Mode_BINARY;
    g_ipc_init_wait_sem = SemaphoreP_create(0, &sem_params);

    SemaphoreP_Params_init(&sem_params);
    sem_params.mode = SemaphoreP_Mode_BINARY;
    g_rdev_init_wait_sem = SemaphoreP_create(0, &sem_params);

    SemaphoreP_Params_init(&sem_params);
    sem_params.mode = SemaphoreP_Mode_BINARY;
    g_rdev_start_sem = SemaphoreP_create(0, &sem_params);

    TaskP_Params_init(&ipc_taskParams);
    ipc_taskParams.priority = 2;
    ipc_taskParams.stack = &g_ipcStackBuf[0];
    ipc_taskParams.stacksize = IPC_TASK_STACKSIZE;
    TaskP_create(&ipc_init, &ipc_taskParams);

    TaskP_Params_init(&rdev_taskParams);
    rdev_taskParams.priority = 2;
    rdev_taskParams.stack = &g_rdevStackBuf[0];
    rdev_taskParams.stacksize = IPC_TASK_STACKSIZE;
    TaskP_create(&remotedev_init, &rdev_taskParams);

    TaskP_Params_init(&monitor_taskParams);
    monitor_taskParams.priority = 2;
    monitor_taskParams.stack = &g_monitorStackBuf[0];
    monitor_taskParams.stacksize = IPC_TASK_STACKSIZE;
    TaskP_create(&monitorAndUnlockRdev, &monitor_taskParams);
}

int main(void)
{
    TaskP_Handle task;
    TaskP_Params taskParams;

    OS_init();

    /* Initialize the task params */
    TaskP_Params_init(&taskParams);
    /* Set the task priority higher than the default priority (1) */
    taskParams.priority = 2;
    taskParams.stack = &g_mainStackBuf[0];
    taskParams.stacksize = IPC_TASK_STACKSIZE;

    task = TaskP_create(&taskFxn, &taskParams);
    if(NULL == task)
    {
        OS_stop();
    }
    OS_start();    /* does not return */

    return(0);
}
