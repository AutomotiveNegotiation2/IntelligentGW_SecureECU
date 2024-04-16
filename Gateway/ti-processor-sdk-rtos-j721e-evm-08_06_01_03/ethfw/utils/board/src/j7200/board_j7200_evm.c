/*
 *  Copyright (c) Texas Instruments Incorporated 2022
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

/*!
 * \file  board_j7200_evm.c
 *
 * \brief This file contains the implementation of the J7200 EVM board
 *        configuration functions.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdarg.h>

#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>

#include <ti/board/board.h>
#include <ti/board/src/j7200_evm/include/board_cfg.h>
#include <ti/board/src/j7200_evm/include/board_pinmux.h>
#include <ti/board/src/j7200_evm/include/board_utils.h>
#include <ti/board/src/j7200_evm/include/board_control.h>
#include <ti/board/src/j7200_evm/include/board_ethernet_config.h>
#include <ti/board/src/j7200_evm/include/board_serdes_cfg.h>

#include <utils/console_io/include/app_log.h>
#include <utils/board/include/ethfw_board_utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* UART port domain/instance used for logging */
#define ETHFW_UART_DOMAIN                       (BOARD_SOC_DOMAIN_MAIN)
#define ETHFW_UART_INST                         (3U)

/* CPTS clock source */
#define ETHFW_CPSW_CPTS_RFT_CLK                 (ENET_CPSW0_CPTS_CLKSEL_MAIN_SYSCLK0)

/* VSC8514 wait time between NRESET deassert and access of the SMI interface */
#define ETHFW_QSGMII_PHY_TWAIT_MSECS            (105U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* EthFw board configuration params object */
typedef struct EthFwBoard_Obj_s
{
    /* UART configuration allowed */
    bool uartAllowed;

    /* I2C configuration allowed */
    bool i2cAllowed;

    /* SerDes configuration allowed */
    bool serdesAllowed;
} EthFwBoard_Obj;

/*!
 * \brief Board related configuration parameters of an Ethernet PHY.
 */
typedef struct EthFwBoard_PhyCfg_s
{
    /*! PHY device address */
    uint32_t phyAddr;

    /*! Interface type */
    EnetPhy_Mii mii;

    /*! Whether PHY is strapped or not */
    bool isStrapped;

    /*! Whether to skip PHY-specific extended configuration */
    bool skipExtendedCfg;

    /*! Extended PHY-specific configuration */
    const void *extendedCfg;

    /*! Size of the extended configuration */
    uint32_t extendedCfgSize;
} EthFwBoard_PhyCfg;

/*!
 * \brief Ethernet port configuration parameters.
 */
typedef struct EthFwBoard_MacPortCfg_s
{
    /*! MAC port connected to */
    Enet_MacPort macPort;

    /*! MAC port interface */
    EnetMacPort_Interface mii;

    /*! PHY configuration parameters */
    EthFwBoard_PhyCfg phyCfg;

    /*! SGMII mode. Applicable only when port is used in Q/SGMII mode */
    EnetMac_SgmiiMode sgmiiMode;

    /*! Link configuration (speed and duplexity) */
    EnetMacPort_LinkCfg linkCfg;
} EthFwBoard_MacPortCfg;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void EthFwBoard_enableMods(void);

static void EthFwBoard_configPinmux(void);

static void EthFwBoard_detectDBs(void);

static void EthFwBoard_configUart(void);

static void EthFwBoard_configQenet(void);

static void EthFwBoard_configTorrentClks(void);

static void EthFwBoard_configCpswClocks(void);

static uint32_t EthFwBoard_getMacAddrPoolEeprom(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                                uint32_t poolSize);

static uint32_t EthFwBoard_getMacAddrPoolStatic(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                                uint32_t poolSize);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static EthFwBoard_Obj gEthFwBoard;

/* Default port configuration for all ports in EVM:
 *   4 x QSGMII ports in QEnet */
static EthFwBoard_MacPortCfg gEthFw_macPortCfg[] =
{
    {   /* "P0" */
        .macPort   = ENET_MAC_PORT_1,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_MAIN },
        .phyCfg    =
        {
            .phyAddr         = 16U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "P1" */
        .macPort   = ENET_MAC_PORT_2,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB },
        .phyCfg    =
        {
            .phyAddr         = 17U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "P2" */
        .macPort   = ENET_MAC_PORT_3,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB },
        .phyCfg    =
        {
            .phyAddr         = 18U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "P3" */
        .macPort   = ENET_MAC_PORT_4,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB },
        .phyCfg    =
        {
            .phyAddr         = 19U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t EthFwBoard_init(uint32_t flags)
{
    Board_initCfg boardCfg = 0U;
    Board_STATUS boardStatus;

    /* Save the functionality requested by app */
    gEthFwBoard.serdesAllowed = ENET_NOT_ZERO(flags & ETHFW_BOARD_SERDES_CONFIG);
    gEthFwBoard.uartAllowed   = ENET_NOT_ZERO(flags & ETHFW_BOARD_UART_ALLOWED);
    gEthFwBoard.i2cAllowed    = ENET_NOT_ZERO(flags & ETHFW_BOARD_I2C_ALLOWED);

    /* Enable hardware block/modules that EthFw will need */
    EthFwBoard_enableMods();

    /* Configure pinmux only for the pins used by EthFw */
    EthFwBoard_configPinmux();

    /* Configure UART used for EthFw logging */
    if (gEthFwBoard.uartAllowed)
    {
        EthFwBoard_configUart();
        boardCfg |= BOARD_INIT_UART_STDIO;
    }

    /* Initialize board via board library */
    boardCfg |= BOARD_INIT_ENETCTRL_CPSW5G;
    boardStatus = Board_init(boardCfg);
    EnetAppUtils_assert(boardStatus == BOARD_SOK);

    /* Detect expansion boards attached to main board (CPB) */
    EthFwBoard_detectDBs();

    /* Configure QSGMII expansion board */
    EthFwBoard_configQenet();

    /* Set CPSW clocks: CPPI, RGMII 5/50/250 MHz, CPTS */
    EthFwBoard_configCpswClocks();

    return boardStatus;
}

uint32_t EthFwBoard_getMacPorts(Enet_MacPort macPorts[ENET_MAC_PORT_NUM])
{
    uint32_t numMacPorts;
    uint32_t i;

    memset(macPorts, 0, sizeof(*macPorts));

    numMacPorts = EnetUtils_min(ENET_ARRAYSIZE(gEthFw_macPortCfg),
                                ENET_MAC_PORT_NUM);

    for (i = 0U; i < numMacPorts; i++)
    {
        macPorts[i] = gEthFw_macPortCfg[i].macPort;
    }

    return numMacPorts;
}

int32_t EthFwBoard_setPortCfg(Enet_MacPort macPort,
                              CpswMacPort_Cfg *macCfg,
                              EnetMacPort_Interface *mii,
                              EnetPhy_Cfg *phyCfg,
                              EnetMacPort_LinkCfg *linkCfg)
{
    EthFwBoard_MacPortCfg *portCfg;
    uint32_t i;
    int32_t status = ENET_ENOTFOUND;

    CpswMacPort_initCfg(macCfg);
    EnetPhy_initCfg(phyCfg);

    for (i = 0U; i < ENET_ARRAYSIZE(gEthFw_macPortCfg); i++)
    {
        portCfg = &gEthFw_macPortCfg[i];

        if (portCfg->macPort == macPort)
        {
            /* Set MII configuration: RGMII or Q/SGMII */
            *mii = portCfg->mii;
            mii->variantType = ENET_MAC_VARIANT_FORCED;

            /* Set PHY configuration parameters */
            phyCfg->phyAddr         = portCfg->phyCfg.phyAddr;
            phyCfg->isStrapped      = portCfg->phyCfg.isStrapped;
            phyCfg->loopbackEn      = false;
            phyCfg->skipExtendedCfg = portCfg->phyCfg.skipExtendedCfg;
            phyCfg->extendedCfgSize = portCfg->phyCfg.extendedCfgSize;
            memcpy(phyCfg->extendedCfg, portCfg->phyCfg.extendedCfg, portCfg->phyCfg.extendedCfgSize);

            /* Set link configuration: speed and duplex */
            *linkCfg = portCfg->linkCfg;

            /* Set SGMII mode (applicable for Q/SGMII ports only) */
            macCfg->sgmiiMode = portCfg->sgmiiMode;

            status = ENET_SOK;
            break;
        }
    }

    return status;
}

static void EthFwBoard_enableMods(void)
{
    uint32_t i;
    uint32_t clkModId[] = { TISCI_DEV_DDR0,
                            TISCI_DEV_TIMER12,
                            TISCI_DEV_TIMER13,
                            TISCI_DEV_UART3, };

    /* Enable hardware block/modules that EthFw will need */
    for (i = 0U; i < ENET_ARRAYSIZE(clkModId); i++)
    {
        EnetAppUtils_setDeviceState(clkModId[i], TISCI_MSG_VALUE_DEVICE_SW_STATE_ON, 0U);
    }
}

static void EthFwBoard_configPinmux(void)
{
    Board_PinmuxConfig_t pinmuxCfg;

    /* Pinmux configuration of pins used for I2C, PHY reset gpios, UART, etc. */
    Board_pinmuxUpdate(gJ7200_MainPinmuxDataCpsw, BOARD_SOC_DOMAIN_MAIN);

    /* Configure pinmux settings for Ethernet ports and MDIO */
    Board_pinmuxUpdate(gJ7200_WkupPinmuxDataCpsw, BOARD_SOC_DOMAIN_MAIN);
}

static void EthFwBoard_detectDBs(void)
{
    bool qenetDetected;

    if (gEthFwBoard.i2cAllowed)
    {
        qenetDetected = Board_detectBoard(BOARD_ID_ENET);

        appLogPrintf("Detected boards:%s\n", qenetDetected ? " QSGMII" : "");
    }
}

static void EthFwBoard_configUart(void)
{
    Board_initParams_t initParams;
    Board_STATUS boardStatus;

    Board_getInitParams(&initParams);
    initParams.uartSocDomain = ETHFW_UART_DOMAIN;
    initParams.uartInst      = ETHFW_UART_INST;
    initParams.pscMode       = BOARD_PSC_DEVICE_MODE_NONEXCLUSIVE;
    Board_setInitParams(&initParams);

    if (gEthFwBoard.i2cAllowed)
    {
        /* Set SOM's MUX2 for UART3 route */
        boardStatus = Board_control(BOARD_CTRL_CMD_SET_SOM_UART_MUX, NULL);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
    }
}

static void EthFwBoard_configQenet(void)
{
    Board_STATUS boardStatus;

    if (gEthFwBoard.i2cAllowed)
    {
        /* Release PHY reset */
        boardStatus = Board_cpswEnetExpPhyReset(0U);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);

        /* Release the COMA_MODE pin */
        boardStatus = Board_cpswEnetExpComaModeCfg(0U);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
    }

    /* Wait till we can access QSGMII PHY registers after reset, irrespective
     * of the NRESET gpio set by ETHFW or bootloader */
    TaskP_sleepInMsecs(ETHFW_QSGMII_PHY_TWAIT_MSECS);

    if (gEthFwBoard.serdesAllowed)
    {
        /* Configure SerDes clocks */
        EthFwBoard_configTorrentClks();

        /* Configure SerDes for QSGMII functionality */
        boardStatus = Board_serdesCfgQsgmii();
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
    }
}

static void EthFwBoard_configTorrentClks(void)
{
    uint32_t moduleId = TISCI_DEV_SERDES_10G1;
    uint32_t clkParId = TISCI_DEV_SERDES_10G1_CORE_REF_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT4_CLK;
    uint32_t clkId = TISCI_DEV_SERDES_10G1_CORE_REF_CLK;
    uint32_t clkRateHz = 100000000U;
    int32_t status;

    status = Sciclient_pmSetModuleClkParent(moduleId, clkId, clkParId, SCICLIENT_SERVICE_WAIT_FOREVER);
    if (status != CSL_PASS)
    {
        appLogPrintf("Failed to reparent clk %u: %d\n", clkId, status);
        EnetAppUtils_assert(false);
    }

    EnetAppUtils_clkRateSet(moduleId, clkId, clkRateHz);

    EnetAppUtils_setDeviceState(moduleId, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON, 0U);
}

static void EthFwBoard_configCpswClocks(void)
{
    /* Enable CPPI_CLK_CLK and set RGMII_MHZ_[5,50,250]_CLK clock rate */
    EnetAppUtils_enableClocks(ENET_CPSW_5G, 0U);

    /* Select CPTS source clock (CPTS_RFT_CLK) in CLKSEL mux */
    EnetAppUtils_selectCptsClock(ENET_CPSW_5G, 0U, ETHFW_CPSW_CPTS_RFT_CLK);
}

uint32_t EthFwBoard_getMacAddrPool(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                   uint32_t poolSize)
{
    uint32_t allocCnt = 0U;
    uint32_t staticCnt = 0U;

    if (gEthFwBoard.i2cAllowed)
    {
        allocCnt = EthFwBoard_getMacAddrPoolEeprom(macAddr, poolSize);
    }

    if (allocCnt < poolSize)
    {
        staticCnt = EthFwBoard_getMacAddrPoolStatic(&macAddr[allocCnt], poolSize - allocCnt);
        if (staticCnt > 0U)
        {
            appLogPrintf("Warning: Using %u MAC address(es) from static pool\n", staticCnt);
        }

        allocCnt += staticCnt;
    }

    return allocCnt;
}

static uint32_t EthFwBoard_getMacAddrPoolEeprom(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                                uint32_t poolSize)
{
    uint8_t macAddrBuf[ENET_RM_NUM_MACADDR_MAX * BOARD_MAC_ADDR_BYTES];
    Board_STATUS boardStatus;
    uint32_t macAddrCnt, tempCnt;
    uint32_t allocCnt = 0U;
    uint32_t i;

    /* Read number of MAC addresses in QUAD Eth board */
    boardStatus = Board_readMacAddrCount(BOARD_ID_ENET, &macAddrCnt);
    EnetAppUtils_assert(boardStatus == BOARD_SOK);
    EnetAppUtils_assert(macAddrCnt <= ENET_RM_NUM_MACADDR_MAX);

    /* Read MAC addresses */
    boardStatus = Board_readMacAddr(BOARD_ID_ENET, macAddrBuf, sizeof(macAddrBuf), &tempCnt);
    EnetAppUtils_assert(boardStatus == BOARD_SOK);
    EnetAppUtils_assert(tempCnt == macAddrCnt);

    /* Save only those required to meet the max number of MAC entries */
    allocCnt = EnetUtils_min(macAddrCnt, poolSize);
    for (i = 0U; i < allocCnt; i++)
    {
        memcpy(macAddr[i], &macAddrBuf[i * BOARD_MAC_ADDR_BYTES], ENET_MAC_ADDR_LEN);
    }

    if (allocCnt == 0U)
    {
        appLogPrintf("No MAC addresses read from QENET board\n");
        EnetAppUtils_assert(false);
    }

    return allocCnt;
}

static uint32_t EthFwBoard_getMacAddrPoolStatic(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                                uint32_t poolSize)
{
    uint32_t allocCnt = 0U;

    /*
     * Workaround for EthFw/u-boot I2C conflicts:
     * EthFw reads MAC addresses from GESI and QUAD_ETH boards during EthFw
     * initialization which are stored in EEPROM memories and are read via
     * I2C.  These I2C accesses tend to occur around the same u-boot is also
     * performing I2C accesses, causing transactions to timeout or other
     * similar symptoms.
     *
     * I2C sharing is a known limitation but no current solution exists at
     * this time.  As a temporary workaround, EthFw will use fixed MAC
     * addresses in Linux builds. For RTOS build, MAC addresses will still
     * be read from EEPROM as such I2C contention isn't an problem.
     */
    uint8_t macAddrBuf[][ENET_MAC_ADDR_LEN] =
    {
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0x92U, 0xC1U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0x92U, 0xC2U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0x92U, 0xC3U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0x92U, 0xC4U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0x92U, 0xC5U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0X8BU, 0xC4U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0X8BU, 0xC5U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0X8BU, 0xC6U },
        { 0x70U, 0xFFU, 0x76U, 0x1DU, 0X8BU, 0xC7U },
    };
    uint32_t macAddrCnt = ENET_ARRAYSIZE(macAddrBuf);

    /* Save only those required to meet the max number of MAC entries */
    allocCnt = EnetUtils_min(macAddrCnt, poolSize);
    memcpy(&macAddr[0U][0U], &macAddrBuf[0U][0U], allocCnt * ENET_MAC_ADDR_LEN);

    return allocCnt;
}
