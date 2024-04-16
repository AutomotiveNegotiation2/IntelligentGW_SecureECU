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
 *  \file     Fls_Brd_Nor_Xspi.c
 *
 *  \brief    This file contains FLS MCAL driver internal functions for Board Nor XSPI
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "string.h"
#include "Fls_Brd_Nor.h"
#include "Fee_Cbk.h"
#include <hw_include/soc.h>
#include <hw_include/hw_types.h>
#include "nor_spi_phy_tune.h"
#include "nor_spi_patterns.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static Std_ReturnType Nor_xspiCmdWrite(SPI_Handle handle, uint8 *cmdBuf,
                                uint32 cmdLen, uint32 dataLen);
static Std_ReturnType Nor_xspiCmdRead(SPI_Handle handle, uint8 *cmdBuf,
                                uint32 cmdLen, uint8 *rxBuf, uint32 rxLen);
static Std_ReturnType Nor_xspiHybridSectCfg(SPI_Handle handle, uint8 enable,
                                        uint32   cfgFlag);
static Std_ReturnType Nor_xspiReadId(SPI_Handle handle);
static Std_ReturnType Nor_xspiEnableDDR(SPI_Handle handle);
static Std_ReturnType Nor_xspiEnableSDR(SPI_Handle handle);
static Std_ReturnType Nor_xspiWaitReady(SPI_Handle handle, uint32 timeOut);
static Std_ReturnType Nor_xspiSetOpcode(SPI_Handle handle);
static Std_ReturnType Nor_xspiSetDummyCycle(SPI_Handle handle, uint32 dummyCycle);
static Std_ReturnType Fls_norRead(uint32 actualChunkSize);
static Std_ReturnType Fls_norWrite(uint32 actualChunkSize);
static Std_ReturnType Fls_norErase(uint32 actualChunkSize);
static boolean Fls_VerifyData_priv(const uint8 *expData,
                const uint8 *rxData,
                uint32 length);
static Std_ReturnType Fls_norCompare(uint32 actualChunkSize);
static Std_ReturnType Fls_norBlankCheck(uint32 actualChunkSize);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static boolean gPhyEnable;
static boolean gDtrEnable;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */


#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiCmdWrite(SPI_Handle handle, uint8 *cmdBuf,
                                        uint32 cmdLen, uint32 dataLen)
{
    SPI_Transaction  transaction_local;
    uint32         transferType = (uint32) SPI_TRANSACTION_TYPE_WRITE;
    Std_ReturnType  retVal = E_NOT_OK;
    boolean             ret;

    /* Update the mode and transfer type with the required values */
    retVal = OSPI_control(handle, SPI_V0_CMD_SET_CFG_MODE, NULL);
    if (retVal == E_OK)
    {
        retVal = OSPI_control(handle, SPI_V0_CMD_XFER_MODE_RW, (void *)&transferType);
    }

    if (retVal == E_OK)
    {
        transaction_local.txBuf = (void *)cmdBuf;
        /* Buffer includes command and write data */
        transaction_local.count = cmdLen + dataLen;
        transaction_local.rxBuf = NULL;
        transaction_local.arg = (void *)(uint32)dataLen;

        ret = OSPI_transfer(handle, &transaction_local);
        if (ret == TRUE)
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiRegRead(SPI_Handle handle,
                                  uint32   regAddr,
                                  uint8    *data)
{
    Std_ReturnType retVal =  E_OK;
    uint8    cmd[6];

    cmd[0] = NOR_CMD_RDREG;
    cmd[1] = (regAddr >> 24) & 0xFF;
    cmd[2] = (regAddr >> 16) & 0xFF;
    cmd[3] = (regAddr >> 8) & 0xFF;
    cmd[4] = (regAddr) & 0xFF;

    retVal = Nor_xspiCmdRead(handle, cmd, 5, data, 1);
    if(retVal != E_OK)
    {
        return E_NOT_OK;
    }

    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiRegWrite(SPI_Handle handle,
                                   uint32   regAddr,
                                   uint8    data)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint8    cmd[6];

    /* Enable flash write */
    cmd[0] = NOR_CMD_WREN;
    retVal = Nor_xspiCmdWrite(handle, cmd, 1, 0);
    if(retVal == E_OK)
    {
        retVal = Nor_xspiWaitReady(handle, NOR_WRR_WRITE_TIMEOUT);
        if (retVal == E_OK)
        {
            cmd[0] = NOR_CMD_WRREG;
            cmd[1] = (regAddr >> 24) & 0xFF;
            cmd[2] = (regAddr >> 16) & 0xFF;
            cmd[3] = (regAddr >> 8) & 0xFF;
            cmd[4] = (regAddr) & 0xFF;
            cmd[5] = data;

            retVal = Nor_xspiCmdWrite(handle, cmd, 5, 1);
            if (retVal == E_OK)
            {
                retVal = Nor_xspiWaitReady(handle, NOR_WRR_WRITE_TIMEOUT);
            }
        }
    }

    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiHybridSectCfg(SPI_Handle handle,
                                        uint8    enable,
                                        uint32   cfgFlag)
{
    Std_ReturnType  retVal = E_OK;
    uint8     regData;

    /* Read configuration register3 */
    retVal = Nor_xspiRegRead(handle, NOR_CFG3_VREG_ADDR, &regData);
    if(retVal != E_OK)
    {
        return E_NOT_OK;
    }

    if(enable == 1)
    {
        /* Enable hybrid sector configuration */
        regData &= ~0x8;
    }
    else
    {
        /* Disable hybrid sector configuration */
        regData |= 0x8;
    }

    /* Write configuration register3 */
    retVal = Nor_xspiRegWrite(handle, NOR_CFG3_VREG_ADDR, regData);
    if(retVal != E_OK)
    {
        return E_NOT_OK;
    }

    return retVal;
}


FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiCmdRead(SPI_Handle handle, uint8 *cmdBuf,
                            uint32 cmdLen, uint8 *rxBuf, uint32 rxLen)
{
    SPI_Transaction  transaction_local;
    uint32         transferType = (uint32) SPI_TRANSACTION_TYPE_READ;
    Std_ReturnType  retVal = E_NOT_OK;
    boolean             ret;

    /* Update the mode and transfer type with the required values */
    retVal = OSPI_control(handle, SPI_V0_CMD_SET_CFG_MODE, NULL);
    if (retVal == E_OK)
    {
        retVal = OSPI_control(handle, SPI_V0_CMD_XFER_MODE_RW, (void *)&transferType);
    }

    if (retVal == E_OK)
    {
        transaction_local.txBuf = (void *)cmdBuf;
        transaction_local.rxBuf = (void *)rxBuf;
        transaction_local.count = cmdLen + rxLen;

        ret = OSPI_transfer(handle, &transaction_local);
        if (ret == TRUE)
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiReadId(SPI_Handle handle)
{
    Std_ReturnType       retVal = E_NOT_OK;
    uint8     idCode[NOR_RDID_NUM_BYTES];
    uint8     cmd[6];
    uint32    manfID, devID;
    cmd[0] = NOR_CMD_RDID;
    cmd[1] = 0;  /* Address Bytes */
    cmd[2] = 0;
    cmd[3] = 0;
    cmd[4] = 0;

    retVal = Nor_xspiCmdRead(handle, cmd, 5, idCode, NOR_RDID_NUM_BYTES);
    if (retVal == E_OK)
    {
        manfID = (uint32)idCode[0];
        devID = ((uint32)idCode[1] << 8) | ((uint32)idCode[2]);
        if ((manfID != NOR_MANF_ID) || (devID != NOR_DEVICE_ID))
        {
            retVal = E_NOT_OK;
        }
    }
    return (retVal);
}


FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiEnableDDR(SPI_Handle handle)
{
    Std_ReturnType       retVal = E_NOT_OK;
    uint8          cmdWren = NOR_CMD_WREN;
    uint32         data[6];

    /* Send Write Enable command */
    retVal = Nor_xspiCmdWrite(handle, &cmdWren, 1U, 0U);

    /* Enable double transfer rate mode */
    if (retVal == E_OK)
    {
        /* send write VCR command to reg addr 0x0 to set to DDR mode */
        data[0] = ((uint32)NOR_CMD_WRITE_VCR << 24U)         | /* write volatile config reg cmd */
                  ((uint32)0U << 23U)                         | /* read data disable */
                  ((uint32)7U << 20U)                         | /* read 8 data bytes */
                  ((uint32)1U << 19U)                         | /* enable cmd adddr */
                  ((uint32)2U << 16U)                         | /* 3 address bytes */
                  ((uint32)1U << 15U);                          /* write data enable */
        data[1] = 0x00800006;     /* Non-volatile config register address */
        data[2] = 0x43; /* set to Octal DDR in Nonvolatile Config Reg 0x0 */
        retVal = OSPI_control(handle, SPI_V0_CMD_ENABLE_DDR, (void *)data);
    }

    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiEnableSDR(SPI_Handle handle)
{
    Std_ReturnType       retVal = E_NOT_OK;
    uint8          cmdWren = NOR_CMD_WREN;
    uint32         data[6];
    CSL_ospi_flash_cfgRegs *regAddr; //TODO
    uint32               regVal;

    /* Send Write Enable command */
    retVal = Nor_xspiCmdWrite(handle, &cmdWren, 1U, 0U);

    /* Enable single transfer rate mode */
    if (retVal == E_OK)
    {
        /* send write VCR command to reg addr 0x0 to set to DDR mode */
        data[0] = ((uint32)NOR_CMD_WRITE_VCR << 24U)         | /* write volatile config reg cmd */
                  ((uint32)0U << 23U)                         | /* read data disable */
                  ((uint32)7U << 20U)                         | /* read 8 data bytes */
                  ((uint32)1U << 19U)                         | /* enable cmd adddr */
                  ((uint32)2U << 16U)                         | /* 3 address bytes */
                  ((uint32)1U << 15U);                          /* write data enable */
        data[1] = 0x00800006;     /* Non-volatile config register address */
        data[2] = 0x41U; /* set to Extended SPI mode in Nonvolatile Config Reg 0x0 */
        retVal = OSPI_control(handle, SPI_V0_CMD_ENABLE_SDR, (void *)data);

        /* Flash device requires 4-bit access for command as well in quad mode */
        regAddr = (CSL_ospi_flash_cfgRegs *)(FLS_OSPI_CTRL_BASE_ADDR); //TODO
        regVal = LLD_REG32_RD(&regAddr->DEV_INSTR_RD_CONFIG_REG);
        regVal |= 0x300;
        LLD_REG32_WR(&regAddr->DEV_INSTR_RD_CONFIG_REG, regVal);

    }
    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiWaitReady(SPI_Handle handle, uint32 timeOut)
{
    uint8         status;
    uint8         cmd[6];
    Std_ReturnType       retVal = E_OK;
    Std_ReturnType       ready = E_NOT_OK;
    uint32 timeOutVal = timeOut;

    cmd[0] = NOR_CMD_RDREG;
    cmd[1] = 0;
    cmd[2] = NOR_VREG_OFFSET;
    cmd[3] = 0;
    cmd[4] = 0;

    do
    {
        if (E_OK == Nor_xspiCmdRead(handle, cmd, 5U, &status, 1U))
        {
            if ((status & NOR_SR_WIP) == 0U)
            {
                ready = E_OK;
            }
            if (E_OK == ready)
            {
                break;
            }
            else
            {
                timeOutVal--;
                if (timeOutVal == 0U)
                {
                    retVal = E_NOT_OK;
                }
            }
        }
        else
        {
            retVal = E_NOT_OK;
        }
    } while (retVal == E_OK);

    /*Timed out*/
    if (ready == E_OK)
    {
        retVal = E_OK;
    }
    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiSetDummyCycle(SPI_Handle handle, uint32 dummyCycle)
{
    Std_ReturnType         retVal;
    uint8                 regData;

    /* Read configuration register2 */
    retVal = Nor_xspiRegRead(handle, NOR_CFG2_VREG_ADDR, &regData);
    if (retVal == E_OK)
    {
        /* Set the dummy cycles */
        regData = (regData & ~0xF) | dummyCycle;

        /* Write configuration register2 */
        retVal = Nor_xspiRegWrite(handle, NOR_CFG2_VREG_ADDR, regData);
    }

    return retVal;
}

FLS_FUNC_TEXT_SECTION static Std_ReturnType Nor_xspiSetOpcode(SPI_Handle handle)
{
    uint32               data[6];
    uint32               rdDummyCycles = 0;
    uint32               cmdDummyCycles = 0;
    uint32               readCmd;
    uint32               progCmd;
    uint32               latencyCode = 0;
    uint32               rx_lines;
    Std_ReturnType       retVal = E_OK;
    rx_lines = (uint32)OSPI_XFER_LINES_OCTAL;

    if (Fls_DrvObj.dacEnable == TRUE)
    {
        rdDummyCycles = NOR_OCTAL_READ_DUMMY_CYCLE;
        latencyCode   = NOR_OCTAL_READ_DUMMY_CYCLE_LC;
    }
    else
    {
        rdDummyCycles = NOR_OCTAL_READ_DUMMY_CYCLE_INDAC;
        latencyCode   = NOR_OCTAL_READ_DUMMY_CYCLE_LC_INDAC;
    }

    if (gDtrEnable == TRUE)
    {
        cmdDummyCycles = NOR_OCTAL_DDR_CMD_READ_DUMMY_CYCLE;
        readCmd = NOR_CMD_OCTAL_DDR_READ;
        if (gPhyEnable == FALSE)
        {
            rdDummyCycles += 1;
        }
    }
    else
    {
        cmdDummyCycles = NOR_OCTAL_SDR_CMD_READ_DUMMY_CYCLE;
        readCmd = NOR_CMD_OCTAL_READ;
    }

    progCmd = NOR_CMD_OCTAL_PROG;

    data[0] = readCmd;
    data[1] = progCmd;
    data[2] = NOR_CMD_RDSR;

    /* Update the read opCode, rx lines and read dummy cycles */
    if (OSPI_control(handle, SPI_V0_CMD_RD_DUMMY_CLKS, (void *)&rdDummyCycles) != E_OK)
    {
        retVal = E_NOT_OK;
    }
    if (E_OK == retVal)
    {
        if (OSPI_control(handle, SPI_V0_CMD_SET_XFER_LINES, (void *)&rx_lines) != E_OK)
        {
            retVal = E_NOT_OK;
        }
    }
    if (E_OK == retVal)
    {
        if (OSPI_control(handle, SPI_V0_CMD_XFER_OPCODE, (void *)data) != E_OK)
        {
            retVal = E_NOT_OK;
        }
    }
    if (E_OK == retVal)
    {
        /* Set the opcodes for dual opcode mode */
        data[0] = 0;
        data[1] = 0xFA;
        data[2] = readCmd;
        data[3] = progCmd;
        data[4] = 0xF9;
        data[5] = 0x6;
        if (OSPI_control(handle, SPI_V0_CMD_XFER_OPCODE_EXT, (void *)data) != E_OK)
        {
            retVal = E_NOT_OK;
        }
        if (E_OK == retVal)
        {
            if (OSPI_control(handle, SPI_V0_CMD_EXT_RD_DUMMY_CLKS, (void *)&cmdDummyCycles) != E_OK)
            {
                retVal = E_NOT_OK;
            }
        }
        if (E_OK == retVal)
        {
            /* Set read dummy cycles to the flash device */
            retVal = Nor_xspiSetDummyCycle(handle, latencyCode);
        }
    }

    return retVal;
}

/*
 * Design : MCAL-7289
 */
FLS_FUNC_TEXT_SECTION Std_ReturnType Fls_hwUnitInit(void)
{
    Std_ReturnType retVal;
    SPI_Handle handle = NULL;

    (void)OSPI_init(((SPI_Handle)&(SPI_config[0])));
    handle = (SPI_Handle)&(SPI_config[0]);

    if (handle != NULL)
    {
        Fls_DrvObj.spiHandle = handle;
        retVal = Fls_norOpen();
    }
    else
    {
        retVal = E_NOT_OK; /*Handle is NULL */
    }
    return retVal;
}

FLS_FUNC_TEXT_SECTION static void ReportFlsError(Fls_JobType job)
{
    switch(job) {
        case FLS_JOB_COMPARE:
			(void) Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_COMPARE_FAILED);
            break;
        case FLS_JOB_ERASE:
			(void) Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_ERASE_FAILED);
            break;
        case FLS_JOB_READ:
			(void) Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_READ_FAILED);
            break;
        case FLS_JOB_WRITE:
			(void) Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_WRITE_FAILED);
            break;
        default:
            break;
    }
	Fls_DrvObj.jobResultType = MEMIF_JOB_FAILED;
	Fls_DrvObj.status = MEMIF_IDLE;
}


/*
 * Design : MCAL-7278,MCAL-7409,MCAL-7448,MCAL-7269,MCAL-7266,MCAL-7441,MCAL-7255,MCAL-7313,MCAL-7278,MCAL-7284,MCAL-7313,MCAL-7334,MCAL-7367,MCAL-7379,MCAL-7409,MCAL-7441
 */
FLS_FUNC_TEXT_SECTION void processJobs(Fls_JobType job)
{
    uint32 chunkSize;
    Std_ReturnType retVal = E_NOT_OK;
    /*Get the MIN of two*/
    if (Fls_DrvObj.length < Fls_DrvObj.jobChunkSize)
    {
        chunkSize = Fls_DrvObj.length;
    }
    else
    {
        chunkSize = Fls_DrvObj.jobChunkSize;
    }

    SchM_Enter_Fls_FLS_EXCLUSIVE_AREA_0();

    switch(job) {
        case FLS_JOB_COMPARE:
            retVal = Fls_norCompare(chunkSize);
            break;
        case FLS_JOB_ERASE:
            retVal = Fls_norErase(chunkSize);
            break;
        case FLS_JOB_READ:
            retVal = Fls_norRead(chunkSize);
            break;
        case FLS_JOB_WRITE:
            retVal = Fls_norWrite(chunkSize);
            break;
        case FLS_JOB_BLANKCHECK:
            retVal = Fls_norBlankCheck(chunkSize);
            break;
        default:
            retVal = E_NOT_OK;
            break;
    }

    if (retVal == E_OK)
    {
        Fls_DrvObj.ramAddr = &Fls_DrvObj.ramAddr[chunkSize];
        if (job != FLS_JOB_ERASE)
        {
            Fls_DrvObj.flashAddr += chunkSize;
            /*Erase FlashAddr updated in Fls_norErase*/
        }
        Fls_DrvObj.length -= chunkSize;
        Fls_DrvObj.transferred += chunkSize;

        if( 0U == Fls_DrvObj.length )
        {
            Fls_DrvObj.jobResultType = MEMIF_JOB_OK;
            Fls_DrvObj.status = MEMIF_IDLE;
            Fls_DrvObj.jobType = FLS_JOB_NONE;
            Fls_DrvObj.transferred = 0;
            if( Fls_DrvObj.Fls_JobEndNotification != NULL )
            {
                Fls_DrvObj.Fls_JobEndNotification();
            }
        }
    }
    else /*if retval == E_NOT_OK or E_COMPARE_MISMATCH*/
    {
        if ((E_BLANKCHECK_MISMATCH == retVal) || (E_COMPARE_MISMATCH == retVal))
        {
            Fls_DrvObj.status = MEMIF_IDLE;
            Fls_DrvObj.jobType = FLS_JOB_NONE;
            Fls_DrvObj.transferred = 0;
            if (FLS_JOB_BLANKCHECK == job)
            {
				(void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_VERIFY_ERASE_FAILED);
            }
            else /*if (FLS_JOB_COMPARE == job)*/
            {
                Fls_DrvObj.jobResultType = MEMIF_BLOCK_INCONSISTENT;
				(void) Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_VERIFY_WRITE_FAILED);
            }
            if( Fls_DrvObj.Fls_JobErrorNotification != NULL )
            {
                Fls_DrvObj.Fls_JobErrorNotification();
            }
        }
        else /*if retVal == E_NOT_OK*/
        {
            /*Hardware/driver internal error occured*/
            ReportFlsError(job);
            if( Fls_DrvObj.Fls_JobErrorNotification != NULL )
            {
                   Fls_DrvObj.Fls_JobErrorNotification();
            }
        }
    }

    SchM_Exit_Fls_FLS_EXCLUSIVE_AREA_0();

    return;
}

static SPI_Transaction transaction;

/*
 * Design : MCAL-7436,MCAL-7436,MCAL-7292,MCAL-7325,MCAL-7296
 */
FLS_FUNC_TEXT_SECTION static Std_ReturnType Fls_norRead(uint32 actualChunkSize)
{
    SPI_Handle handle;
    uint32 addr     = Fls_DrvObj.flashAddr;
    uint8 *buf      = Fls_DrvObj.ramAddr;
    boolean ret;
    uint32 transferType = (uint32)SPI_TRANSACTION_TYPE_READ;
    handle          = Fls_DrvObj.spiHandle;
    Std_ReturnType retVal = E_OK;

    if (handle != NULL)
    {

        if ((gPhyEnable == TRUE) && (tuneDone == FALSE))
        {
            retVal = Nor_spiPhyTune(handle, NOR_TUNING_DATA_OFFSET);
            tuneDone = TRUE;
        }

        if (E_OK == retVal)
        {
            /* Set transfer mode and read type */
            if (E_OK == OSPI_control(handle, SPI_V0_CMD_SET_XFER_MODE, NULL))
            {
                if (E_OK == OSPI_control(handle, SPI_V0_CMD_XFER_MODE_RW, (void *)&transferType))
                {
                    retVal = E_OK;
                }
                else
                {
                    retVal = E_NOT_OK;
                }
            }
            else
            {
                retVal = E_NOT_OK;
            }

            if (E_OK == retVal)
            {
                transaction.arg   = (void *)(uint32)addr;
                transaction.txBuf = NULL;
                transaction.rxBuf = (void *)buf;
                transaction.count = actualChunkSize;

                ret = OSPI_transfer(handle, &transaction);
                if (ret != TRUE)
                {
                    retVal = E_NOT_OK; /*HW error occured*/
                }
            }
        }
        else
        {
            retVal = E_NOT_OK; /*Nor_spiPhyTune Failed */
        }
    }
    else
    {
        retVal = E_NOT_OK; /*Handle is NULL*/
    }
    return retVal;
}

/*
 * Design : MCAL-7303,MCAL-7315
 */
FLS_FUNC_TEXT_SECTION static Std_ReturnType Fls_norWrite(uint32 actualChunkSize) //TODO
{
    SPI_Handle       handle;
    uint32 addr = Fls_DrvObj.flashAddr;
    uint32 len = actualChunkSize;
    uint8 *buf = Fls_DrvObj.ramAddr;
    boolean        ret;
    uint32         byteAddr;
    uint32         wrSize = len ;
    uint32         chunkLen;
    uint32         actual;
    uint32         transferType = (uint32)SPI_TRANSACTION_TYPE_WRITE;
    uint8          cmdWren[2];
    Std_ReturnType retVal = E_OK;

    handle = Fls_DrvObj.spiHandle;

    if(handle != NULL)
    {
        cmdWren[0] = NOR_CMD_WREN;

        if (Fls_DrvObj.dacEnable == FALSE)
        {
            /* indirect access transfer mode */
            #if (STD_ON == FLS_USE_INTERRUPTS)
                wrSize = Fls_DrvObj.sectorList[0].sectorPageSize; /*for Intr mode, has to be page size of flash device.*/
            #endif
        }

        byteAddr = addr & (wrSize - 1U);
        for (actual = 0; actual < len; actual += chunkLen)
        {
            if (E_OK == retVal)
            {
                if (Nor_xspiCmdWrite(handle, cmdWren, 1, 0)) //TODO correct structure
                {
                    return E_NOT_OK;
                }

                if (Nor_xspiWaitReady(handle, NOR_WRR_WRITE_TIMEOUT))
                {
                    return E_NOT_OK;
                }

                /* Set the transfer mode, write op code and tx lines */
                OSPI_control(handle, SPI_V0_CMD_SET_XFER_MODE, NULL);
                OSPI_control(handle, SPI_V0_CMD_XFER_MODE_RW, (void *)&transferType);


                /* Send Page Program command */
                chunkLen = (((len - actual) < (wrSize - byteAddr)) ?
                            (len - actual) : (wrSize - byteAddr));

                transaction.arg   = (void *)(uint32)addr;
                transaction.txBuf = (void *)(buf + actual);
                transaction.rxBuf = NULL;
                transaction.count = chunkLen;

                ret = OSPI_transfer(handle, &transaction);
                if (ret == TRUE)
                {
                    addr += chunkLen;
                    byteAddr = 0;
                    retVal = E_OK;
                }
                else
                {
                    retVal = E_NOT_OK;
                }
                /* Wait till the write operation completes */
                if (Nor_xspiWaitReady(handle, NOR_PAGE_PROG_TIMEOUT))
                {
                    return E_NOT_OK;
                }


            }
            else
            {
                retVal = E_NOT_OK;
                break; /*error occured while writing, exit loop */
            }
        }
    }
    else
    {
        retVal = E_NOT_OK; /*handle is NULL */
    }

    return retVal;
}

/*
 * Design : MCAL-7327,MCAL-7249,MCAL-7400
 */
FLS_FUNC_TEXT_SECTION static Std_ReturnType Fls_norErase(uint32 actualChunkSize)
{
    uint8           cmd[10];
    uint32          cmdLen;
    uint32          address = 0;
    uint8           cmdWren[2];
    SPI_Handle      handle;
    uint32          sector;
    uint32          page;
    uint32          leftover, sector_count, page_size, page_count;
    Std_ReturnType retVal = E_OK;
    handle = Fls_DrvObj.spiHandle;

    cmdWren[0]  = NOR_CMD_WREN;

    if (handle != NULL)
    {
        /*Calculate sector number based on flashAddr, erase one sector at a time*/

        page_size       = Fls_DrvObj.sectorList[0].sectorPageSize;
        page_count  	= NOR_NUM_PAGES_PER_BLOCK;
        sector_count    = Fls_DrvObj.sectorList[0].numberOfSectors;

        sector          = Fls_DrvObj.flashAddr / Fls_DrvObj.sectorList[0].sectorSize;
        leftover        = Fls_DrvObj.flashAddr % Fls_DrvObj.sectorList[0].sectorSize;
        page 	        = leftover / page_size;

        if ((leftover % page_size ) || (sector > sector_count) ||
            (page > page_count) || (sector >= sector_count))
        {
            retVal = E_NOT_OK;
        }

        if (E_OK == retVal)
        {
            address   = sector * Fls_DrvObj.sectorList[0].sectorSize;
            cmd[0]  = NOR_CMD_BLOCK_ERASE;

            cmd[1] = (uint8)(address >> 24U) & 0xffU; /* 4 address bytes */
            cmd[2] = (uint8)(address >> 16U) & 0xffU;
            cmd[3] = (uint8)(address >>  8U) & 0xffU;
            cmd[4] = (uint8)(address >>  0U) & 0xffU;
            cmdLen = 5U;

            if (Nor_xspiWaitReady(handle, NOR_WRR_WRITE_TIMEOUT) == E_OK)
            {
                if (Nor_xspiCmdWrite(handle, cmdWren, 1, 0) == E_OK)
                {
                    if (Nor_xspiWaitReady(handle, NOR_WRR_WRITE_TIMEOUT) == E_OK)
                    {
                        if (Nor_xspiCmdWrite(handle, cmd, cmdLen, 0) == E_OK)
                        {
                            if (Nor_xspiWaitReady(handle, NOR_BULK_ERASE_TIMEOUT)!= E_OK)
                            {
                                retVal = E_NOT_OK;
                            }
                        }
                        else
                        {
                            retVal = E_NOT_OK;
                        }
                    }
                    else
                    {
                        retVal = E_NOT_OK;
                    }
                }
                else
                {
                    retVal = E_NOT_OK;
                }
            }
            else
            {
                retVal = E_NOT_OK;
            }

            Fls_DrvObj.flashAddr = (sector + 1U) * Fls_DrvObj.sectorList[0].sectorSize;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

FLS_FUNC_TEXT_SECTION static boolean Fls_VerifyData_priv(const uint8 *expData,
                const uint8 *rxData,
                uint32 length)
{
    uint32 idx = 0U;
    uint32 match = 1U;
    boolean retVal = FALSE;
    uint8 *expData_local = (uint8 *)expData;
    uint8 *rxData_local = (uint8 *)rxData;

    for(idx = 0; ((idx < length) && (match != 0U)); idx++)
    {
        if(*expData_local != *rxData_local)
        {
            match = 0U;
        }
        expData_local++;
        rxData_local++;
    }
    if(match == 1U)
    {
        retVal = TRUE;
    }
    return retVal;
}

/*
 * Design : MCAL-7406,MCAL-7281
 */
FLS_FUNC_TEXT_SECTION static Std_ReturnType Fls_norCompare(uint32 actualChunkSize)
{
    SPI_Handle handle;
    uint32 addr             = Fls_DrvObj.flashAddr;
    uint32 len              = actualChunkSize;
    uint8 *readData_buf     = NULL;
    uint8 *expData_Buf      = Fls_DrvObj.ramAddr;
    boolean  ret;
    uint32 transferType     = (uint32) SPI_TRANSACTION_TYPE_READ;
    Std_ReturnType retVal;

    handle = Fls_DrvObj.spiHandle;

    if (handle != NULL)
    {
        /* Set transfer mode and read type */
        if (E_OK == OSPI_control(handle, SPI_V0_CMD_SET_XFER_MODE, NULL))
        {
            if (E_OK == OSPI_control(handle, SPI_V0_CMD_XFER_MODE_RW, (void *)&transferType))
            {
                retVal = E_OK;
            }
            else
            {
                retVal = E_NOT_OK;
            }
        }
        else
        {
            retVal = E_NOT_OK;
        }

        if(E_OK == retVal)
        {
            transaction.arg   = (void *)(uint32)addr;
            transaction.txBuf = NULL;
            transaction.rxBuf = (void *)readData_buf;
            transaction.count = len;

            ret = OSPI_transfer(handle, &transaction);
            if (TRUE == ret)
            {
                if (Fls_VerifyData_priv(expData_Buf, (const uint8*)transaction.rxBuf, len) == TRUE)
                {
                    retVal = E_OK;
                }
                else
                {
                    retVal = E_COMPARE_MISMATCH;
                }
            }
            else
            {
                retVal = E_NOT_OK;
            }
        }
    }
    else
    {
        retVal = E_NOT_OK; /* Handle is NULL*/
    }
    return retVal;
};

/*
 * Design : MCAL-7279,MCAL-7437,MCAL-7310,MCAL-7419
 */
FLS_FUNC_TEXT_SECTION static Std_ReturnType Fls_norBlankCheck(uint32 actualChunkSize)
{
    SPI_Handle handle;
    uint32 addr             = Fls_DrvObj.flashAddr;
    uint32 len              = actualChunkSize;
    uint8 *readData_buf     = NULL;
    boolean  ret;
    uint32         transferType = (uint32)SPI_TRANSACTION_TYPE_READ;
    Std_ReturnType retVal;

    handle = Fls_DrvObj.spiHandle;

    if (handle != NULL)
    {
        /* Buffer containing the received data */
        uint8 expData_Buf[Fls_DrvObj.maxReadNormalMode];

        volatile uint32 idx;
        volatile uint8 *expData_ptr = expData_Buf;

        for(idx = 0; idx < len; idx++)
        {
            *expData_ptr = NOR_ERASED_DATA;
            expData_ptr++;
        }

        /* Set transfer mode and read type */
        if (E_OK == OSPI_control(handle, SPI_V0_CMD_SET_XFER_MODE, NULL))
        {
            if (E_OK == OSPI_control(handle, SPI_V0_CMD_XFER_MODE_RW, (void *)&transferType))
            {
                retVal = E_OK;
            }
            else
            {
                retVal = E_NOT_OK;
            }
        }
        else
        {
            retVal = E_NOT_OK;
        }

        if(E_OK == retVal)
        {
            transaction.arg   = (void *)(uint32)addr;
            transaction.txBuf = NULL;
            transaction.rxBuf = (void *)readData_buf;
            transaction.count = len;

            ret = OSPI_transfer(handle, &transaction);
            if (TRUE == ret)
            {
                if (Fls_VerifyData_priv(expData_Buf, (const uint8*)transaction.rxBuf, len) == TRUE)
                {
                    retVal = E_OK;
                }
                else
                {
                    retVal = E_BLANKCHECK_MISMATCH;
                }
            }
            else
            {
                retVal = E_NOT_OK;
            }
        }
    }
    else
    {
        retVal = E_NOT_OK; /*Handle is NULL*/
    }
    return retVal;
}

FLS_FUNC_TEXT_SECTION Std_ReturnType Fls_norOpen(void)
{
    SPI_Params      spiParams;  /* SPI params structure */
    SPI_Handle      hwHandle;  /* SPI handle */
    Std_ReturnType             retVal = E_OK;

    /*Save the DTR enable flag*/
    gDtrEnable = Fls_DrvObj.dtrEnable;

    if (Fls_DrvObj.dacEnable == TRUE)
    {
        /*enable PHY for DAC mode*/
        Nor_spiPhyTuneReset(gDtrEnable);
    }
    else
    {
        Fls_DrvObj.phyEnable = FALSE;
        /*Check to ensure that phy mode should be disabled for INDAC mode*/
    }

    gPhyEnable = Fls_DrvObj.phyEnable;
    if (gPhyEnable == TRUE)
    {
        /*
         * phyEnable is turned on only for DAC read,
         * it turned off for open/erase/write operation
         */
        Fls_DrvObj.phyEnable = FALSE; /*keep phyEnable off for all and only enable for reads */
        /*Set the TuneDone variable to false in open */
        tuneDone = FALSE;
    }

    if(Fls_DrvObj.clkSpeed == 133333333U)
    {
        devDelays[3] = OSPI_DEV_DELAY_CSDA;
    }
    else
    {
        devDelays[3] = OSPI_DEV_DELAY_CSDA_3;
    }

    if(Fls_DrvObj.clkSpeed == 200000000U)
    {
        Fls_DrvObj.flsBaudRateDiv = BOARD_XSPI_BAUDRATE_DIV_200M;
    }
    else
    {
        Fls_DrvObj.flsBaudRateDiv = BOARD_XSPI_BAUDRATE_DIV_133M;
    }




    /* Use default SPI config params if no params provided */
    SPI_Params_init(&spiParams);

    hwHandle = (SPI_Handle)OSPI_open(Fls_DrvObj.spiHandle, &spiParams);

    if (hwHandle != NULL)
    {

        if (gDtrEnable == TRUE)
        {
           if (Nor_xspiEnableDDR(hwHandle) != E_OK)
           {
                retVal = E_NOT_OK;
           }
        }
        else
        {
           if (Nor_xspiEnableSDR(hwHandle) != E_OK)
           {
                retVal = E_NOT_OK;
           }
        }
        if (E_OK == retVal)
        {
            /* Set read/write opcode and read dummy cycles */
            if (Nor_xspiSetOpcode(hwHandle) == E_OK)
            {
                if (Nor_xspiReadId(hwHandle) != E_OK)
                {
                    OSPI_close(hwHandle);
                    /*
                     * Design : MCAL-7257,MCAL-7308
                     */
					(void) Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_UNEXPECTED_FLASH_ID);
                    retVal = E_NOT_OK;
                }

                if (E_OK == retVal)
                {
                    /* Disable hybrid sector configuration */
                    retVal = Nor_xspiHybridSectCfg(hwHandle, 0U, 0U);
                }
            }
            else
            {
                OSPI_close(hwHandle);
                retVal = E_NOT_OK;
            }
        }
   }
   else
   {
       retVal = E_NOT_OK;
   }
   return (retVal);
}

void Fls_NorOspiClose(void)
{
    SPI_Handle   spiHandle;
    spiHandle = Fls_DrvObj.spiHandle;
    if (spiHandle != NULL)
    {
        OSPI_close(spiHandle);
    }
}


FLS_FUNC_TEXT_SECTION void Fls_copyConfig(Fls_DriverObjType *drvObj,
    const Fls_ConfigType *cfgPtr)
{
    drvObj->Fls_JobEndNotification = cfgPtr->Fls_JobEndNotification;
    drvObj->Fls_JobErrorNotification = cfgPtr->Fls_JobErrorNotification;
    drvObj->maxReadNormalMode = cfgPtr->maxReadNormalMode;
    drvObj->maxWriteNormalMode = cfgPtr->maxWriteNormalMode;
    drvObj->clkSpeed = cfgPtr->ospiClkSpeed;
    drvObj->dacEnable = cfgPtr->dacEnable;
    drvObj->xipEnable = cfgPtr->xipEnable;
    drvObj->dtrEnable = cfgPtr->dtrEnable;
    drvObj->phyEnable = cfgPtr->phyEnable;
    drvObj->ospixferlines = cfgPtr->ospixferlines;
	drvObj->sectorList[0] = cfgPtr->sectorList[0];
	drvObj->flsBaudRateDiv = cfgPtr->flsBaudRateDiv;
	drvObj->blockSize = cfgPtr->blockSize;
    return;
}
/*
 * Design : MCAL-6620
 */
FLS_FUNC_TEXT_SECTION void Fls_resetDrvObj(Fls_DriverObjType *drvObj)
{
    drvObj->Fls_JobEndNotification = NULL;
    drvObj->Fls_JobErrorNotification = NULL;
    drvObj->maxReadNormalMode = 0U;
    drvObj->maxWriteNormalMode = 0U;
    drvObj->clkSpeed = 0U;
    drvObj->dacEnable = (uint32)NULL;
    drvObj->xipEnable = (uint32)NULL;
    drvObj->dtrEnable = (uint32)NULL;
    drvObj->phyEnable = (uint32)NULL;
    drvObj->status = MEMIF_UNINIT;
    drvObj->jobResultType = MEMIF_JOB_OK;
    drvObj->jobType = FLS_JOB_NONE;
    drvObj->flashAddr = 0U;
    drvObj->ramAddr = NULL;
    drvObj->length = 0U;
    drvObj->mode = MEMIF_MODE_SLOW;
    drvObj->jobChunkSize = 0U;
    drvObj->spiHandle = NULL;
    drvObj->transferred = 0U;
	drvObj->flsBaudRateDiv=0U;
	drvObj->blockSize=0U;
	tuneDone=FALSE;
    return;
}


#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
