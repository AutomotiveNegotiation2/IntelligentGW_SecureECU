/*
*
* Copyright (c) {2015 - 2020} Texas Instruments Incorporated
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
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include <TI/tivx.h>
#include <utils/perf_stats/include/app_perf_stats.h>
#include <utils/remote_service/include/app_remote_service.h>
#include <utils/perf_stats/src/app_perf_stats_priv.h>
#include <utils/ipc/include/app_ipc.h>
#include <utils/app_init/include/app_init.h>
int tidlrt_printf(const char *fmt, ...);

uint32_t tidlrt_ddr_stats= 0;

#define APP_PERF_DDR_BURST_SIZE_BYTES   (  64u)  /* in units of bytes */

int32_t TIDLRT_getDdrStats(uint64_t *read_bytes, uint64_t *write_bytes)
{
    if(tidlrt_ddr_stats)
    {
        int32_t status;
        app_perf_stats_ddr_stats_t ddr_stats;
        #if defined(SOC_AM62A)
            status = appRemoteServiceRun(APP_IPC_CPU_MCU1_0, APP_PERF_STATS_SERVICE_NAME,
                APP_PERF_STATS_CMD_GET_DDR_COUNTERS,
                &ddr_stats, sizeof(app_perf_stats_ddr_stats_t),
                0);
        #elif defined(SOC_J721E) || defined (SOC_J721S2) || defined (SOC_J784S4)
            status = appRemoteServiceRun(APP_IPC_CPU_MCU2_0, APP_PERF_STATS_SERVICE_NAME,
                APP_PERF_STATS_CMD_GET_DDR_COUNTERS,
                &ddr_stats, sizeof(app_perf_stats_ddr_stats_t),
                0);
        #endif

        if(status)
            return status;

        *read_bytes  = (uint64_t)ddr_stats.counter0_total * APP_PERF_DDR_BURST_SIZE_BYTES;
        *write_bytes = (uint64_t)ddr_stats.counter1_total * APP_PERF_DDR_BURST_SIZE_BYTES;
    }
    else
    {
        *read_bytes  = 0;
        *write_bytes = 0;
    }

    return 0;
}

int32_t tidl_rt_ovx_Init()
{
    int32_t status = 0;
    char *debug_str;

    debug_str = getenv("TIDL_RT_DDR_STATS");
    if(!debug_str)
        tidlrt_ddr_stats = 0;
    else
        tidlrt_ddr_stats = atoi(debug_str);

    int32_t init_flag = 1;

    char *strVal = NULL;

    strVal = getenv("SKIP_TIOVX_INIT");

    if(strVal != NULL)
    {
        tidlrt_printf("Skipping appInit() in TIDL-RT!\n");
        init_flag = 0;
    }
    else
    {
        tidlrt_printf("Calling appInit() in TIDL-RT!\n");
    }

    if(init_flag == 1)
    {
        status = appInit();
    }
    return status;
}

int32_t tidl_rt_ovx_DeInit()
{
    int32_t status = 0;
    int32_t init_flag = 1;

    char *strVal = NULL;

    strVal = getenv("SKIP_TIOVX_INIT");

    if(strVal != NULL)
    {
        tidlrt_printf("Skipping appDeInit() in TIDL-RT!\n");
        init_flag = 0;
    }
    else
    {
        tidlrt_printf("Calling appDeInit() in TIDL-RT!\n");
    }

    if(init_flag == 1)
    {
        status = appDeInit();
    }
    return status;
}
