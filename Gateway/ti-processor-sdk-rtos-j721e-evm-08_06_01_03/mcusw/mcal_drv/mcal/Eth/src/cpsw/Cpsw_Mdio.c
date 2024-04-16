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
 *  \file     Cpsw_Mdio.c
 *
 *  \brief    This file contains MDIO related functionality.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "cpsw/Cpsw_Types.h"
#include "cpsw/Cpsw_Mdio.h"
#include "Os.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \anchor MDIO Clause22 Bit definitions
 *  \name MDIO Clause22 Bit definitions
 *
 *  @{
 */
#define CPSW_MDIO_ST_OPCODE_MSB 0x08U       /**< ST (2bits) + OPCODE (2bits) */
#define CPSW_MDIO_PHYADR_MSB    0x10U       /**< PHYADR (5bits) */
#define CPSW_MDIO_REGADR_MSB    0x10U       /**< REGADR (5bits) */
#define CPSW_MDIO_DATA_MSB      0x08000U    /**< DATA (16bits) */
/* @} */

/**
 *  \anchor MDIO Function (Clause22)
 *  \name MDIO Function (Clause22)
 *
 *  Standard MDIO Functions for Clause22 (aka Article 22)
 *  i.e. Function = ST + OpCode
 *  Where:
 *   - ST (2 bits), Start of Frame (01 for Clause22)
 *   - OpCode (2 bits),
 *     - 01 for WRITE Operation
 *     - 10 for READ Operation
 *  @{
 */
/** \brief MDIO Write Function for Clause22 */
#define CPSW_MDIO_WRITE_FUNC    0x05U

/** \brief MDIO Read Function for Clause22 */
#define CPSW_MDIO_READ_FUNC     0x06U
/* @} */

/**
 *  \anchor PHY_Registers
 *  \name PHY registers
 *
 *  Standard PHY register address and definitions.
 *
 *  @{
 */
/** \brief Basic Mode Control Register (BMCR) */
#define CPSW_MDIO_BMCR          (0x00U)

/** \brief Basic Mode Status Register (BMSR) */
#define CPSW_MDIO_BMSR          (0x01U)

/** \brief BMSR[2] LINK STATUS bit-field mask */
#define CPSW_MDIO_BMSR_LINKSTS  (1U << 2U)
/* @} */

/** \brief Invalid Data Value to be set when Read Operation Failed */
#define CPSW_MDIO_INV_DATA_VAL  (0xFFFFU)

/** \brief one second in unit of microsecond */
#define CPSW_MDIO_SEC_TO_NSEC   (1000000000ULL)

/**
 *  \anchor NOP Macros
 *  \name NOP Macros
 *
 *  Macros to insert "NOP" assembly instructions.
 *
 *  @{
 */
#define __NOP  asm (" NOP ")

#define NOP5   do { __NOP; __NOP; __NOP; __NOP; __NOP; } while (0)

#define NOP10  NOP5; \
               NOP5

#define NOP50  NOP10; \
               NOP10; \
               NOP10; \
               NOP10; \
               NOP10
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief MDIO bit banging delay in terms of nanosecond.
 *        Applicable only when in Manual MDIO Operating Mode
 */
static uint32 mdcHalfPeriodNsec = 0U;

/* ========================================================================== */
/*                  Internal Function Declarations                            */
/* ========================================================================== */

/**
 *  \brief Get base address of CPSW MDIO register set
 *
 *  \return  Base address of CPSW MDIO register set
 */
static inline CSL_mdioHandle CpswMdio_getRegAddr(void);

/**
 * \brief Write Low to MDC Clock Register
 *
 * \return None
 */
static inline void CpswMdio_setMdclkLow(CSL_mdioHandle hMdioRegs);

/**
 * \brief Write High to MDC Clock Register
 *
 * \return None
 */
static inline void CpswMdio_setMdclkHigh(CSL_mdioHandle hMdioRegs);

/**
 * \brief Set MDIO Operation to Output Mode.
 *
 * \return None
 */
static inline void CpswMdio_setMdoOutputEnable(CSL_mdioHandle hMdioRegs);

/**
 * \brief Set MDIO Operation to Input Mode.
 *
 * \return None
 */
static inline void CpswMdio_setMdoInputEnable(CSL_mdioHandle hMdioRegs);

/**
 * \brief Write High to MDIO PIN Register
 *
 * \return None
 */
static inline void CpswMdio_setMdoHigh(CSL_mdioHandle hMdioRegs);

/**
 * \brief Write Low to MDIO PIN Register
 *
 * \return None
 */
static inline void CpswMdio_setMdoLow(CSL_mdioHandle hMdioRegs);

/**
 * \brief Read MDIO PIN Register Value
 *
 * \return None
 */
static inline uint32 CpswMdio_readMdi(CSL_mdioHandle hMdioRegs);

/**
 * \brief Clear Poll Enable Mask
 *
 * \return None
 */
static inline void CpswMdio_clearPollEnableMask(CSL_mdioHandle hMdioRegs);

/**
 * \brief Enableds MDIO Manual Mode
 *
 * \return None
 */
static void CpswMdio_enableManualMode(CSL_mdioHandle hMdioRegs);

/**
 * \brief Perfom a cpu delay
 *
 * \return None
 */
static void CpswMdio_delayNsec(uint32 delayInNsec);

/**
 * \brief Toggle MDC Clock.
 *
 * \return None
 */
static void CpswMdio_sw_toggleMdclk(CSL_mdioHandle hMdioRegs, uint32 delayInNsec);

/**
 * \brief Sends MDIO Field Value.
 *
 * \return None
 */
static void CpswMdio_sw_FieldSend(uint32 iMsb, uint32 iVal);

/**
 * \brief MDIO Synchronous Phy Reg Read in Normal Mode.
 *
 * \return E_OK if Phy Read is successful else E_NOT_OK
 */
static Std_ReturnType CpswMdio_syncRead(uint32 phyAddr,
                                        uint32 regNum,
                                        uint16 *val);

/**
 * \brief Gets the value of a PHY register read asynchronously. This function
 *        is expected to be called while servicing the MDIO interrupt.
 *
 * \return E_OK if Phy Read is successful else E_NOT_OK
 */
static Std_ReturnType CpswMdio_asyncReadComplete(uint16 *val);

/**
 * \brief MDIO Synchronous Phy Reg Write in Normal Mode.
 *
 * \return None
 */
static void CpswMdio_syncWrite(uint32 phyAddr,
                               uint32 regNum,
                               uint16 val);

/**
 * \brief MDIO Manual Phy Reg Read (Clause 22)
 *
 * \return E_OK if Phy Read is successful else E_NOT_OK
 */
static Std_ReturnType CpswMdio_manualPhyRegRead22(uint32 phyAddr,
                                                  uint32 regNum,
                                                  uint16 *val);

/**
 * \brief MDIO Manual Phy Reg Write (Clause 22)
 *
 * \return None
 */
static void CpswMdio_manualPhyRegWrite22(uint32 phyAddr,
                                         uint32 regNum,
                                         uint16 val);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CpswMdio_open(uint8 ctrlIdx)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    uint64 cppiClkFreqHz = Eth_Cpsw_GetCppiClockFreq();
    uint32 busFreq = Eth_Cpsw_GetMdioBusClockFreq(ctrlIdx);
    sint32 retVal = CPSW_SOK;
    uint32 clkdiv;

    /* sanity check */
    if (busFreq != 0U)
    {
        clkdiv = (cppiClkFreqHz / busFreq) - 1U;
        if (clkdiv > 65535U)
        {
            retVal = CPSW_EINVALID_PARAMS;
        }
    }
    else
    {
        retVal = CPSW_EBADARGS;
    }

    if (CPSW_SOK == retVal)
    {
#if (STD_ON == ETH_WRAPPER_ENABLED)
        /* Disable MDIO user command complete interrupt for user group 0 */
        CSL_REG32_FINS(&hMdioRegs->USER_INT_MASK_CLEAR_REG,
                       MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR, 1U);
#else
        if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
        {
            /* Disable MDIO user command complete interrupt for user group 0 */
            CSL_REG32_FINS(&hMdioRegs->USER_INT_MASK_CLEAR_REG,
                           MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR, 1U);
        }
        else
        {
            /* Enable MDIO user command complete interrupt for user group 0 */
            CSL_REG32_FINS(&hMdioRegs->USER_INT_MASK_SET_REG,
                           MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET, 1U);
        }
#endif
        /* Clear the USER_ACCESS_REG */
        CSL_REG32_WR(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG, 0U);

        if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
        {
            /* compute for MDC Half Period */
            mdcHalfPeriodNsec = ((CPSW_MDIO_SEC_TO_NSEC/busFreq)/2);

            /* enable mdio manual mode */
            CpswMdio_clearPollEnableMask(hMdioRegs);
            CpswMdio_enableManualMode(hMdioRegs);
        }
        else
        {
            /* Set the MDIO clock divider */
            CSL_MDIO_setClkDivVal(hMdioRegs, (uint16)clkdiv);

            /* Enable the state machine */
            CSL_MDIO_enableStateMachine(hMdioRegs);
        }
    }
}

void CpswMdio_close(void)
{
    /* Disable the state machine */
    CSL_MDIO_disableStateMachine(CpswMdio_getRegAddr());
}

boolean CpswMdio_isPhyAlive(uint8 ctrlIdx, uint32 phyAddr)
{
    boolean isAlive = FALSE;
    if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
    {
        sint32 retVal = CPSW_SOK;
        uint16 bmsrVal;

        retVal = CpswMdio_manualPhyRegRead22(phyAddr,
                                             CPSW_MDIO_BMSR,
                                             &bmsrVal);
        if (retVal == CPSW_SOK)
        {
            isAlive = TRUE;
        }
    }
    else
    {
        isAlive = CSL_MDIO_isPhyAlive(CpswMdio_getRegAddr(), phyAddr);
    }
    return isAlive;
}

boolean CpswMdio_isPhyLinked(uint8 ctrlIdx, uint32 phyAddr)
{
    boolean isLinked = FALSE;
    if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
    {
        sint32 retVal = CPSW_SOK;
        uint16 bmsrVal;

        retVal = CpswMdio_manualPhyRegRead22(phyAddr,
                                             CPSW_MDIO_BMSR,
                                             &bmsrVal);
        if (retVal == CSL_PASS)
        {
            if (bmsrVal & CPSW_MDIO_BMSR_LINKSTS)
            {
                 isLinked = TRUE;
            }
        }
    }
    else
    {
        isLinked = CSL_MDIO_isPhyLinked(CpswMdio_getRegAddr(), phyAddr);
    }
    return isLinked;
}

void CpswMdio_writePhyReg(uint8 ctrlIdx,
                          uint32 phyAddr,
                          uint32 reg,
                          uint16 val)
{
    if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
    {
        CpswMdio_manualPhyRegWrite22(phyAddr, reg, val);
    }
    else
    {
        CpswMdio_syncWrite(phyAddr, reg, val);
    }
}

Std_ReturnType CpswMdio_readPhyReg(uint8 ctrlIdx,
                                   uint32 phyAddr,
                                   uint32 reg,
                                   uint16 *val)
{
    Std_ReturnType retVal = E_OK;

    if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
    {
        retVal = CpswMdio_manualPhyRegRead22(phyAddr, reg, val);
    }
    else
    {
        retVal = CpswMdio_syncRead(phyAddr, reg, val);
    }

    return retVal;
}

Std_ReturnType CpswMdio_initiatePhyRegWrite(uint32 phyAddr,
                                            uint32 reg,
                                            uint16 val)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    Std_ReturnType retVal = E_OK;
    uint32 userAccess = 0U;

    if (0U == CSL_REG32_FEXT(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG,
                             MDIO_USER_GROUP_USER_ACCESS_REG_GO))
    {
        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_GO,
                 CSL_MDIO_USER_GROUP_USER_ACCESS_REG_GO_EN_0x1);

        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_WRITE,
                 CSL_MDIO_USER_GROUP_USER_ACCESS_REG_WRITE);

        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_PHYADR,
                 phyAddr);

        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_REGADR,
                 reg);

        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_DATA,
                 val);

        CSL_REG32_WR(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG, userAccess);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType CpswMdio_initiatePhyRegRead(uint32 phyAddr, uint32 reg)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    Std_ReturnType retVal = E_OK;
    uint32 userAccess = 0U;

    if (0U == CSL_REG32_FEXT(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG,
                             MDIO_USER_GROUP_USER_ACCESS_REG_GO))
    {
        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_GO,
                 CSL_MDIO_USER_GROUP_USER_ACCESS_REG_GO_EN_0x1);

        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_WRITE,
                 CSL_MDIO_USER_GROUP_USER_ACCESS_REG_READ);

        CSL_FINS(userAccess,
                 MDIO_USER_GROUP_USER_ACCESS_REG_PHYADR,
                 phyAddr);

        CSL_FINS(userAccess,
                MDIO_USER_GROUP_USER_ACCESS_REG_REGADR,
                reg);

        CSL_REG32_WR(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG, userAccess);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType CpswMdio_getPhyRegVal(uint8 ctrlIdx,
                                     uint32 phyAddr,
                                     uint32 reg,
                                     uint16 *val)
{
    Std_ReturnType retVal = E_OK;

    if (ETH_MDIO_OPMODE_MANUAL == Eth_Cpsw_GetMdioOpMode(ctrlIdx))
    {
        retVal = CpswMdio_manualPhyRegRead22(phyAddr, reg, val);
    }
    else
    {
        retVal = CpswMdio_asyncReadComplete(val);
    }

    return retVal;
}

void CpswMdio_clearUserInt(void)
{
    /* Clear the User Command Complete interrupt */
    CSL_REG32_FINS(&CpswMdio_getRegAddr()->USER_INT_MASKED_REG,
                   MDIO_USER_INT_MASKED_REG_USERINTMASKED,
                   1U);
}

boolean CpswMdio_isPhyRegReadWritePending(void)
{
    boolean retVal = TRUE;

    if (0U == CSL_REG32_FEXT(&CpswMdio_getRegAddr()->USER_GROUP[0U].USER_ACCESS_REG,
                             MDIO_USER_GROUP_USER_ACCESS_REG_GO))
    {
        retVal = FALSE;
    }

    return retVal;
}

/* ========================================================================== */
/*                  Internal Function Definitions                             */
/* ========================================================================== */

static inline CSL_mdioHandle CpswMdio_getRegAddr(void)
{
    return (CSL_mdioHandle)Eth_Cpsw_GetMdioRegAddr();
}

static inline void CpswMdio_setMdclkLow(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_MDCLK_O, 0U);
}

static inline void CpswMdio_setMdclkHigh(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_MDCLK_O, 1U);
}

static inline void CpswMdio_setMdoOutputEnable(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_OE, 1U);
}

static inline void CpswMdio_setMdoInputEnable(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_OE, 0U);
}

static inline void CpswMdio_setMdoHigh(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_PIN, 1U);
}

static inline void CpswMdio_setMdoLow(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_PIN, 0U);
}

static inline uint32 CpswMdio_readMdi(CSL_mdioHandle hMdioRegs)
{
    return CSL_FEXT(hMdioRegs->MANUAL_IF_REG, MDIO_MANUAL_IF_REG_MDIO_PIN);
}

static inline void CpswMdio_clearPollEnableMask(CSL_mdioHandle hMdioRegs)
{
    /* Due to a hardware limitation, bit 31 must always be set */
    hMdioRegs->POLL_EN_REG = (1U << 31U);
}

static void CpswMdio_enableManualMode(CSL_mdioHandle hMdioRegs)
{
    CSL_FINS(hMdioRegs->POLL_REG, MDIO_POLL_REG_STATECHANGEMODE, 1U);
    CSL_FINS(hMdioRegs->POLL_REG, MDIO_POLL_REG_MANUALMODE, 1U);
}

static void CpswMdio_delayNsec(uint32 delayInNsec)
{
    TickType delayInTicks = (((uint64)delayInNsec*ETH_OS_COUNTER_FREQ)/
                              CPSW_MDIO_SEC_TO_NSEC);
    TickType curTick;
    TickType endTick;
    StatusType status;

    status = GetCounterValue(ETH_OS_COUNTER_ID, &curTick);
    endTick = curTick + delayInTicks;

    while ((E_OK == status) && (curTick < endTick))
    {
        NOP50;
        status = GetCounterValue(ETH_OS_COUNTER_ID, &curTick);
    }
}

static void CpswMdio_sw_toggleMdclk(CSL_mdioHandle hMdioRegs, uint32 delayInNsec)
{
    CpswMdio_setMdclkLow(hMdioRegs);
    CpswMdio_delayNsec(delayInNsec);
    CpswMdio_setMdclkHigh(hMdioRegs);
    CpswMdio_delayNsec(delayInNsec);
}

static void CpswMdio_sw_FieldSend(uint32 iMsb, uint32 iVal)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    uint32 i;

    for (i = iMsb; i; i >>= 1)
    {
        if ((i & iVal) != 0U)
        {
            CpswMdio_setMdoHigh(hMdioRegs);
        }
        else
        {
            CpswMdio_setMdoLow(hMdioRegs);
        }
        CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);
    }
}

static Std_ReturnType CpswMdio_syncRead(uint32 phyAddr,
                                        uint32 regNum,
                                        uint16 *val)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    Std_ReturnType retVal = E_OK;
    boolean ret;

    ret = CSL_MDIO_phyRegRead2(hMdioRegs, 0U, phyAddr, regNum, val);
    if (FALSE == ret)
    {
        retVal = E_NOT_OK;
    }

    CpswMdio_clearUserInt();

    return retVal;
}

static Std_ReturnType CpswMdio_asyncReadComplete(uint16 *val)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    Std_ReturnType retVal = E_OK;

    if (CSL_MDIO_USER_GROUP_USER_ACCESS_REG_ACK_PASS ==
        CSL_REG32_FEXT(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG,
                       MDIO_USER_GROUP_USER_ACCESS_REG_ACK))
    {
        *val = (uint16)CSL_REG32_FEXT(&hMdioRegs->USER_GROUP[0U].USER_ACCESS_REG,
                                      MDIO_USER_GROUP_USER_ACCESS_REG_DATA);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

static void CpswMdio_syncWrite(uint32 phyAddr,
                               uint32 regNum,
                               uint16 val)
{
    CSL_MDIO_phyRegWrite2(CpswMdio_getRegAddr(), 0U, phyAddr, regNum, val);
    CpswMdio_clearUserInt();
}

/**
 * \brief MDIO Manual Phy Reg Read (Clause 22)
 */
static Std_ReturnType CpswMdio_manualPhyRegRead22(uint32 phyAddr,
                                                  uint32 regNum,
                                                  uint16 *val)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();
    uint32 i, sts;
    uint16 tmp;
    char ack;

    /* Disable Phy Interrupt driver */
    CpswMdio_setMdclkLow(hMdioRegs);
    /* Enable our drive capability */
    CpswMdio_setMdoOutputEnable(hMdioRegs);

    /* Issue clause 22 MII read function {0,1,1,0}*/
    CpswMdio_sw_FieldSend(CPSW_MDIO_ST_OPCODE_MSB, CPSW_MDIO_READ_FUNC);
    /* Send the device number MSB first */
    CpswMdio_sw_FieldSend(CPSW_MDIO_PHYADR_MSB, phyAddr);
    /* Send the register number MSB first */
    CpswMdio_sw_FieldSend(CPSW_MDIO_REGADR_MSB, regNum);

    /* send Turn-arround cycles */
    CpswMdio_setMdoInputEnable(hMdioRegs);
    CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);

    /* Get PHY Ack */
    ack = CpswMdio_readMdi(hMdioRegs);
    CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);

    if (ack == 0) /* If Acked read the data */
    {
        for (tmp = 0, i = CPSW_MDIO_DATA_MSB; i; i >>= 1)
        {
            if (CpswMdio_readMdi(hMdioRegs))
            {
                tmp |= i;
            }
            CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);
        }
        sts = CSL_PASS;
    }
    else
    {
        for (tmp = 0, i = CPSW_MDIO_DATA_MSB; i; i >>= 1)
        {
            CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);
        }
        tmp = CPSW_MDIO_INV_DATA_VAL;
        sts = CSL_ETIMEOUT;
    }

    /* Give time for pull-up to work */
    CpswMdio_setMdclkLow(hMdioRegs);
    CpswMdio_setMdclkLow(hMdioRegs);
    CpswMdio_setMdclkLow(hMdioRegs);

    /* re-enable PHY Interrupt function */
    CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);
    *val = tmp;

    return (sts == CSL_PASS) ? E_OK : E_NOT_OK;
}

/**
 * \brief MDIO Manual Phy Reg Write (Clause 22)
 */
static void CpswMdio_manualPhyRegWrite22(uint32 phyAddr,
                                         uint32 regNum,
                                         uint16 val)
{
    CSL_mdioHandle hMdioRegs = CpswMdio_getRegAddr();

    /* Disable Phy Interrupt driver */
    CpswMdio_setMdclkLow(hMdioRegs);
    /* Enable our drive capability */
    CpswMdio_setMdoOutputEnable(hMdioRegs);

    /* Issue clause 22 MII write function {0,1,0,1}*/
    CpswMdio_sw_FieldSend(CPSW_MDIO_ST_OPCODE_MSB, CPSW_MDIO_WRITE_FUNC);
    /* Send the device number MSB first */
    CpswMdio_sw_FieldSend(CPSW_MDIO_PHYADR_MSB, phyAddr);
    /* Send the register number MSB first */
    CpswMdio_sw_FieldSend(CPSW_MDIO_REGADR_MSB, regNum);

    /* send Turn-arround cycles */
    CpswMdio_setMdoHigh(hMdioRegs);
    CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);
    CpswMdio_setMdoLow(hMdioRegs);
    CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);

    /* Send Register data MSB first */
    CpswMdio_sw_FieldSend(CPSW_MDIO_DATA_MSB, val);
    CpswMdio_setMdoInputEnable(hMdioRegs);

    /* Give time for pull-up to work */
    CpswMdio_setMdclkLow(hMdioRegs);
    CpswMdio_setMdclkLow(hMdioRegs);
    CpswMdio_setMdclkLow(hMdioRegs);

    /* re-enable PHY Interrupt function */
    CpswMdio_sw_toggleMdclk(hMdioRegs, mdcHalfPeriodNsec);
}

