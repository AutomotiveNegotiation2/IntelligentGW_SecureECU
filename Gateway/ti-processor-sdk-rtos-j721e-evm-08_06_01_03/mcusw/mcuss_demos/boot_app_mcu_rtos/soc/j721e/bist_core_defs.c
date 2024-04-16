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
 *  \file     bist_core_defs.c
 *
 *  \brief    This file defines available main domain bist modules and order of bist per stage
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "bist_core_defs.h"
#include "boot_stage_defs.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* NOTE: The PBIST and LBIST tests that are run in each stage on this SOC are
 * defined in this file.  To make modifications, the user simply can add/remove/move
 * ID's in the following arrays.
 * Run before any booting of cores:
 * pbist_pre_boot_stage
 * lbist_pre_boot_stage
 * Run before the first boot stage:
 * pbist_first_boot_stage
 * lbist_first_boot_stage
 * Run before the second boot stage:
 * pbist_second_boot_stage
 * lbist_second_boot_stage
 * Run before the third boot stage:
 * pbist_third_boot_stage
 * lbist_third_boot_stage
 * Care should be taken to ensure that BIST sections for particular cores match
 * the boot cores selected for each boot stage in soc/<SOC Device>/boot_core_defs.c.
 * */

/* Defines PBIST's needed for all cores before the first stage of the Main Domain
 * boot sequence for J721E SOC */
int pbist_pre_boot_stage[] =
{
    PBIST_HWPOST_MCU_INDEX,    /* Read results of HW POST MCU PBIST */
    PBIST_INSTANCE_MAIN_INFRA, /* Main Infra - Must be in pre-boot stage */
    PBIST_INSTANCE_MSMC        /* MSMC RAM - Must be in pre-boot stage */
};

int pbist_pre_boot_stage_status[] =
{
    0,  /* HW Post status */
    0,  /* Main Infra */
    0   /* MSMC */
};

int pbist_pre_boot_stage_neg_status[] =
{
    0,  /* HW Post status */
    0,  /* Main Infra */
    0   /* MSMC */
};

/* Defines LBIST's needed for all cores before the first stage of the Main Domain
 * boot sequence for J721E SOC */
int lbist_pre_boot_stage[] =
{
   LBIST_HWPOST_DMSC_INDEX,   /* Read results of HW POST DMSC LBIST */
   LBIST_HWPOST_MCU_INDEX     /* Read results of HW POST MCU LBIST */
};

int lbist_pre_boot_stage_status[] =
{
    0,  /* HW POST DMSC LBIST */
    0   /* HW POST MCU LBIST */
};

/* Defines PBIST's for the first stage of the Main Domain
 * boot sequence for J721E SOC */
int pbist_first_boot_stage[] =
{
    PBIST_INSTANCE_MAIN_PULSAR_0 /* Main R5F 0 */
};


/* Defines LBIST's for the first stage of the Main Domain
 * boot sequence for J721E SOC */
int lbist_first_boot_stage[] =
{
    LBIST_MAIN_MCU0_INDEX        /* Main R5F 0 */
};

/* Defines PBIST's for the second stage of the Main Domain
 * boot sequence for J721E SOC */
int pbist_second_boot_stage[] =
{
    PBIST_INSTANCE_MAIN_PULSAR_1, /* Main R5F 1 */
    PBIST_INSTANCE_C7X,           /* C7X */
    PBIST_INSTANCE_C66X_0,        /* C6X core 0 */
    PBIST_INSTANCE_C66X_1,        /* C6X core 1 */
    PBIST_INSTANCE_VPAC,          /* VPAC */
    PBIST_INSTANCE_DMPAC          /* DMPAC */
};

/* Defines LBIST's for the second stage of the Main Domain
 * boot sequence for J721E SOC */
int lbist_second_boot_stage[] =
{
    LBIST_MAIN_MCU1_INDEX,   /* Main R5F 1 */
    LBIST_C7X_CORE_INDEX,    /* C7X */
    LBIST_VPAC_INDEX,        /* VPAC */
    LBIST_DMPAC_INDEX        /* DMPAC */
};

/* Defines PBIST's for the third stage of the Main Domain
 * boot sequence for J721E SOC */
int pbist_third_boot_stage[] =
{
    PBIST_INSTANCE_A72,      /* A72 */
    PBIST_INSTANCE_HC,       /* HC - MLB PBIST */
    PBIST_INSTANCE_ENCODER,   /* Encoder */
    PBIST_INSTANCE_DECODER   /* Decoder */
};


/* Defines LBIST's for the third stage of the Main Domain
 * boot sequence for J721E SOC */
int lbist_third_boot_stage[] =
{
    LBIST_A72_CORE_INDEX     /* A72 */
};

/* Points to pbist arrays for each of the boot stages */
int *pbist_array_stage[NUM_BOOT_STAGES] =
{
    pbist_first_boot_stage,
    pbist_second_boot_stage,
    pbist_third_boot_stage
};

/* Points to lbist arrays for each of the boot stages */
int *lbist_array_stage[NUM_BOOT_STAGES] =
{
    lbist_first_boot_stage,
    lbist_second_boot_stage,
    lbist_third_boot_stage
};

/* Defines number of LBIST's run in each stage */
uint8_t num_lbists_per_boot_stage[NUM_BOOT_STAGES] =
{
    sizeof(lbist_first_boot_stage)  / sizeof(int),
    sizeof(lbist_second_boot_stage) / sizeof(int),
    sizeof(lbist_third_boot_stage)  / sizeof(int)
};

/* Defines number of PBIST's run in each stage */
uint8_t num_pbists_per_boot_stage[NUM_BOOT_STAGES] =
{
    sizeof(pbist_first_boot_stage)  / sizeof(int),
    sizeof(pbist_second_boot_stage) / sizeof(int),
    sizeof(pbist_third_boot_stage)  / sizeof(int)
};

uint8_t num_lbists_pre_boot = sizeof(lbist_pre_boot_stage) / sizeof(int);
uint8_t num_pbists_pre_boot = sizeof(pbist_pre_boot_stage) / sizeof(int);

const char *pbistName(uint32_t pbistID)
{
    char *name;

    switch(pbistID)
    {
        case (PBIST_HWPOST_MCU_INDEX):
            name="PBIST_HWPOST_MCU_INDEX";
            break;
        case (PBIST_INSTANCE_MCU):
            name="PBIST_INSTANCE_MCU";
            break;
        case (PBIST_INSTANCE_MAIN_PULSAR_0):
            name="PBIST_INSTANCE_MAIN_PULSAR_0";
            break;
        case (PBIST_INSTANCE_MAIN_PULSAR_1):
            name="PBIST_INSTANCE_MAIN_PULSAR_1";
            break;
        case (PBIST_INSTANCE_C7X):
            name="PBIST_INSTANCE_C7X";
            break;
        case (PBIST_INSTANCE_A72):
            name="PBIST_INSTANCE_A72";
            break;
        case (PBIST_INSTANCE_VPAC):
            name="PBIST_INSTANCE_VPAC";
            break;
        case (PBIST_INSTANCE_DMPAC):
            name="PBIST_INSTANCE_DMPAC";
            break;
        case (PBIST_INSTANCE_MAIN_NAVSS):
            name="PBIST_INSTANCE_MAIN_NAVSS";
            break;
        case (PBIST_INSTANCE_HC):
            name="PBIST_INSTANCE_HC";
            break;
        case (PBIST_INSTANCE_C66X_0):
            name="PBIST_INSTANCE_C66X_0";
            break;
        case (PBIST_INSTANCE_C66X_1):
            name="PBIST_INSTANCE_C66X_1";
            break;
        case (PBIST_INSTANCE_MAIN_INFRA):
            name="PBIST_INSTANCE_MAIN_INFRA";
            break;
        case (PBIST_INSTANCE_MSMC):
            name="PBIST_INSTANCE_MSMC";
            break;
        case (PBIST_INSTANCE_ENCODER):
            name="PBIST_INSTANCE_ENCODER";
            break;
	case (PBIST_INSTANCE_DECODER):
            name="PBIST_INSTANCE_DECODER";
            break;
        default:
            name="INVALID ID";
            break;
    }

    return name;
}


const char *lbistName(uint32_t lbistID)
{
    char *name;

    switch(lbistID)
    {
        case (LBIST_HWPOST_DMSC_INDEX):
            name="LBIST_HWPOST_DMSC_INDEX";
            break;
        case (LBIST_HWPOST_MCU_INDEX):
            name="LBIST_HWPOST_MCU_INDEX";
            break;
        case (LBIST_MAIN_MCU0_INDEX):
            name="LBIST_MAIN_MCU0_INDEX";
            break;
        case (LBIST_MAIN_MCU1_INDEX):
            name="LBIST_MAIN_MCU1_INDEX";
            break;
        case (LBIST_C7X_CORE_INDEX):
            name="LBIST_C7X_CORE_INDEX";
            break;
        case (LBIST_VPAC_INDEX):
            name="LBIST_VPAC_INDEX";
            break;
        case (LBIST_DMPAC_INDEX):
            name="LBIST_DMPAC_INDEX";
            break;
        case (LBIST_A72_CORE_INDEX):
            name="LBIST_A72_CORE_INDEX";
            break;
        default:
            name="INVALID ID";
            break;
    }

    return name;
}

