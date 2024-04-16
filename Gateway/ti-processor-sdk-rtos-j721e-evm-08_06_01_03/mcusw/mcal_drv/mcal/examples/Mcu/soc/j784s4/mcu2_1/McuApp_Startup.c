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
/**
 *  \file     McuApp_Startup.c
 *
 *  \brief    This file contains the MCU test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "McuApp_Startup.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define MSG_NORMAL      (APP_UTILS_PRINT_MSG_NORMAL)
/**< Message type */
#define MSG_STATUS      (APP_UTILS_PRINT_MSG_STATUS)
/**< Message type */


/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

uint32 size;
uint32 clkData;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** \brief Start up sequence : priorities */
void McuApp_Startup(void)
{

  /* OSAL being generic might not record the correct frequency and hence we
   * are setting it explicitly. Osal_delay function uses PMU counter which
   * runs at CPU speed and uses OSAL_CPU_FREQ_KHZ_DEFAULT to get the CPU
   * frequency. By default OSAL_CPU_FREQ_KHZ_DEFAULT is set to 400MHZ.
 * In case of J721E this parameter needs to be set explicitly to 1GHZ
   * to get the correct delay functionality.
   */
   AppUtils_SetCpuFrequency();

   /* Initialize memory sections  */
 AppUtils_McuSectionInit();

}

/* performs the functionality of Board_moduleClockEnable */


void McuApp_PlatformInit(void)
{
    return;
}

Std_ReturnType Mcu_CB_App_Implementation(uint32 moduleId, uint32 clkId, uint32 ParentId)
{
  uint32 retVal = E_OK;
  sint32 status = -1U;
  uint32 moduleState = 0U;
  uint32 resetState = 0U;
  uint32 contextLossState = 0U;
  uint64 freqHz;

  status = Sciclient_init(NULL);

  if (status == 0)
 {

        /* Get the module state. No need to change the state if already ON */
        status = Sciclient_pmGetModuleState(moduleId, &moduleState, &resetState,
                                            &contextLossState,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);

        if(moduleState == TISCI_MSG_VALUE_DEVICE_HW_STATE_OFF)
        {
          status = Sciclient_pmSetModuleState(moduleId,
                                              TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                              (TISCI_MSG_FLAG_AOP |
                                                TISCI_MSG_FLAG_DEVICE_RESET_ISO),
                                              SCICLIENT_SERVICE_WAIT_FOREVER);

          if (status == 0)
          {
            status = Sciclient_pmSetModuleRst(moduleId,
                                              0x0U,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);

          }
        else
        {
          AppUtils_Printf(APP_UTILS_PRINT_MSG_NORMAL,
                            " Module state is set for module id = %d !!!\n",
                                                        moduleId);
        }
      }

        status = Sciclient_pmModuleClkRequest(moduleId, clkId , 1U,
                                             TISCI_MSG_FLAG_AOP,
                                             SCICLIENT_SERVICE_WAIT_FOREVER);
         if (status == 0)
         {
           if (0 == status)
           {

             AppUtils_Printf(APP_UTILS_PRINT_MSG_NORMAL,
                            " Module clock request successful !!!\n");
            }
            else
            {
              retVal = E_NOT_OK;
            }
         }
        status = Sciclient_pmSetModuleClkFreq(moduleId, clkId,
                                              19200000,
                                             TISCI_MSG_FLAG_AOP,
                                             SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == 0)
        {
          status = Sciclient_pmGetModuleClkFreq(moduleId, clkId,
                                                 &freqHz,
                                               SCICLIENT_SERVICE_WAIT_FOREVER);

              AppUtils_Printf(APP_UTILS_PRINT_MSG_NORMAL,
                           " Module clock frequency set. Freq = %llu !!!\n",freqHz);
          }
        else
          {
            AppUtils_Printf(APP_UTILS_PRINT_MSG_NORMAL,
                         " Module clock frequency setting failed !!!\n");
            retVal = E_NOT_OK;
          }


  }
      else
      {
        AppUtils_Printf(APP_UTILS_PRINT_MSG_NORMAL,
                          " Sciclient is not initialized  !!!\n");
      }

      return (retVal);
}
