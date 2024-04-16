/*
*
* Copyright (c) 2023 Texas Instruments Incorporated
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

/*  \file proc_names_j721e.c
 *
 *
 *  \brief Defines Processor Names and other processor dependents variables
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdio.h>
#include <ti/drv/ipc/ipc.h>

#include "main_rtos.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Processor ID's */
#ifdef BUILD_MCU1_0

uint32_t IpcRemoteApp_SelfProcId = IPC_MCU1_0;
/**< Own processor ID */

uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
/**< Valid Remote processor ID */
#endif

#ifdef BUILD_MPU1_0

uint32_t IpcRemoteApp_SelfProcId = IPC_MPU1_0;
/**< Own processor ID */

uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
/**< Valid Remote processor ID */
#endif

#ifdef BUILD_MCU1_1

uint32_t IpcRemoteApp_SelfProcId = IPC_MCU1_1;
/**< Own processor ID */

uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
/**< Valid Remote processor ID */
#endif

#ifdef BUILD_MCU2_0
uint32_t IpcRemoteApp_SelfProcId = IPC_MCU2_0;
uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
#endif

#ifdef BUILD_MCU2_1
uint32_t IpcRemoteApp_SelfProcId = IPC_MCU2_1;
uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
#endif

#ifdef BUILD_MCU3_0
uint32_t IpcRemoteApp_SelfProcId = IPC_MCU3_0;
uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
#endif

#ifdef BUILD_MCU3_1
uint32_t IpcRemoteApp_SelfProcId = IPC_MCU3_1;
uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_C66X_1, IPC_C66X_2, IPC_C7X_1
};
#endif

#ifdef BUILD_C66X_1
uint32_t IpcRemoteApp_SelfProcId = IPC_C66X_1;
uint32_t IpcRemoteApp_remoteProc[] =
{
#ifndef NO_R5FS
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_2, IPC_C7X_1
#else
    IPC_MPU1_0, IPC_C66X_2, IPC_C7X_1
#endif
};
#endif

#ifdef BUILD_C66X_2
uint32_t IpcRemoteApp_SelfProcId = IPC_C66X_2;
uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C7X_1
};
#endif

#ifdef BUILD_C7X_1
uint32_t IpcRemoteApp_SelfProcId = IPC_C7X_1;
uint32_t IpcRemoteApp_remoteProc[] =
{
    IPC_MPU1_0, IPC_MCU1_0, IPC_MCU1_1, IPC_MCU2_0, IPC_MCU2_1, IPC_MCU3_0, IPC_MCU3_1, IPC_C66X_1, IPC_C66X_2
};
#endif

uint32_t  IpcRemoteApp_NumProc = sizeof(IpcRemoteApp_remoteProc)/sizeof(uint32_t);
/**< Number of remote processors */

uint8_t  IpcRemoteApp_SysVqBuf[IPC_REMOTE_APP_VQ_BUF_SIZE] __attribute__((aligned(128U)));
/**< Local VirtIoQueue Object */

uint8_t  IpcRemoteApp_CtrlTaskMsgBuf[IPC_REMOTE_APP_RPMSG_DATA_SIZE] __attribute__((aligned(128U)));
/**< Buffer to store all messages received on this core, from all cores */

/* EoF */
