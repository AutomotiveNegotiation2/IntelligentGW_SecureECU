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

/**
@file     tidl_deviceInfo.h
@brief    This file contains device specific structures and utility functions
*/

#ifndef _TIDL_DEVICEINFO_H_
#define _TIDL_DEVICEINFO_H_

#include <stdint.h>
#include "itidl_ti.h"

/**
 *  \anchor eTIDL_DeviceName
 *  \brief  Specifies the target device
 *
 *  @{
 */
#define TIDL_DEVICE_UNDEFINED       ((int32_t) -1)
#define TIDL_TDA4VM                 ((int32_t)  0)
#define TIDL_TDA4AEP                ((int32_t)  1)
#define TIDL_TDA4AM                 ((int32_t)  2)
#define TIDL_TDA4AMPlus             ((int32_t)  3)
#define TIDL_AM62A                  ((int32_t)  4)
/* @} */
#define TIDL_OTF_FLAG_BIT  (0x100)

/*Device property functions*/
static inline int32_t TIDL_isPadOTF(int32_t deviceName)
{
    #ifdef __C7100__
    return 0;
    #else
    /*
      Only the lower 8 bits encode the actual device, the upper bits
      are reserved as control bits to enable/disable features
    */
    if((deviceName & TIDL_OTF_FLAG_BIT) == TIDL_OTF_FLAG_BIT)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    #endif
}


#endif /* _TIDL_DEVICEINFO_H_ */
