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
 *  \file     Cpsw_Cpts.h
 *
 *  \brief    This file contains the structure definitions and function
 *            prototypes of the CPTS
 */

#ifndef CPSW_CPTS_H
#define CPSW_CPTS_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief CPTS open function
 *
 *  Opens the CPTS module and performs an initial
 *  configuration according to the config structure being passed.
 *
 *  This function must be called before any other CpswCpts_*() function.
 *
 *  \return None
 */
void CpswCpts_open(void);

/**
 *  \brief Get CPTS current timestamp
 *
 *  Get CPTS current timestamp
 *
 *  This function must be called before any other CpswCpts_*() function.
 *
 *  \param timeStampPtr ouput current timestamp pointer
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType CpswCpts_getCurrentTimeStamp(uint64 *timeStampPtr);

/**
 *  \brief Get host packet egress timestamp
 *
 *  Get CPTS host packet egress timestamp
 *
 *  This function must be called before any other CpswCpts_*() function.
 *
 *  \param DomainId host packet domain id
 *  \param msgType host packet message type
 *  \param seqId host packet sequence id
 *  \param timeStampPtr egress timestamp value
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType CpswCpts_getHostEgressTimeStamp(uint32 DomainId, 
                                               uint8 msgType, 
                                               uint32 seqId, 
                                               uint64 *timeStampPtr);

/**
 *  \brief Set global timestamp
 *
 *  Set global timestamp
 *
 *  This function must be called before any other CpswCpts_*() function.
 *
 *  \param tsLoadVal timestamp value
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType CpswCpts_setTimeStamp(uint64 tsLoadVal);

/**
 *  \brief Adjust global timestamp
 *
 *  Adjust global timestamp
 *
 *  This function must be called before any other CpswCpts_*() function.
 *
 *  \param adjValInNsecs Adjustment value for timestamp
 *  \param intervalInNsecs Interval to apply the adjustment
 *
 *  \return \ref Std_ReturnType
 */
Std_ReturnType CpswCpts_adjustTimeStamp(sint32 adjValInNsecs,
                                        uint32 intervalInNsecs);

#ifdef __cplusplus
}
#endif

#endif /* CPSW_CPTS_H */

