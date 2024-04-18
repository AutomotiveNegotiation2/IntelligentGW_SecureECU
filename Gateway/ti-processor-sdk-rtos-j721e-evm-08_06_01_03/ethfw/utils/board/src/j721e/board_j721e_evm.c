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
 * \file  board_j721e_evm.c
 *
 * \brief This file contains the implementation of the J721E EVM board
 *        configuration functions.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdarg.h>

#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/include/phy/dp83867.h>
#include <ti/drv/enet/include/phy/mv88q2120.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>

#include <ti/board/board.h>
#include <ti/board/src/j721e_evm/include/board_cfg.h>
#include <ti/board/src/j721e_evm/include/board_pinmux.h>
#include <ti/board/src/j721e_evm/include/board_utils.h>
#include <ti/board/src/j721e_evm/include/board_control.h>
#include <ti/board/src/j721e_evm/include/board_ethernet_config.h>
#include <ti/board/src/j721e_evm/include/board_serdes_cfg.h>

#include <utils/console_io/include/app_log.h>
#include <utils/board/include/ethfw_board_utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* UART port domain/instance used for logging */
#define ETHFW_UART_DOMAIN                       (BOARD_SOC_DOMAIN_MAIN)
#define ETHFW_UART_INST                         (2U)

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

    /* GPIO configuration allowed */
    bool gpioAllowed;

    /* SerDes configuration allowed */
    bool serdesAllowed;

    /* GESI to be enabled or not */
    bool gesiEnabled;

    /* GESI board detected */
    bool gesiDetected;

    /* QSGMII board to be enabled or not */
    bool qenetEnabled;

    /* QSGMII board detected */
    bool qenetDetected;

    /* ENET bridge board to be enabled or not. Mutually exclusive with QSGMII board. */
    bool enetBridgeEnabled;
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
	
	bool isPhyModeC45;
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

static void EthFwBoard_configGesi(void);

static void EthFwBoard_configQenet(void);

static void EthFwBoard_configSerdesBridge(void);

static void EthFwBoard_configSierra0Clks(void);

static void EthFwBoard_configCpswClocks(void);

static uint32_t EthFwBoard_getMacAddrPoolEeprom(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                                uint32_t poolSize);

static uint32_t EthFwBoard_getMacAddrPoolStatic(uint8_t macAddr[][ENET_MAC_ADDR_LEN],
                                                uint32_t poolSize);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static EthFwBoard_Obj gEthFwBoard;

extern pinmuxBoardCfg_t gEthFwPinmuxData[];

/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig gEthFw_gpioPinCfgs[] =
{
    GPIO_DEVICE_CONFIG(0, 61) | GPIO_CFG_OUTPUT,
    GPIO_DEVICE_CONFIG(0, 62) | GPIO_CFG_OUTPUT,
};

/* GPIO Driver callback functions */
GPIO_CallbackFxn gEthFw_gpioCbFunctions[] =
{
    NULL
};

/* GPIO Driver configuration structure */
GPIO_v0_Config GPIO_v0_config =
{
    gEthFw_gpioPinCfgs,
    gEthFw_gpioCbFunctions,
    sizeof(gEthFw_gpioPinCfgs) / sizeof(GPIO_PinConfig),
    sizeof(gEthFw_gpioCbFunctions) / sizeof(GPIO_CallbackFxn),
    0,
};

#define PHY_88Q2120  1
#if PHY_88Q2120
// +mcbae : Marvell 88q2120 1G base t1 phy
static EthFwBoard_MacPortCfg gEthFw_gesiMacPortCfg[] =
{
    {   /* "PRG1_RGMII1_B" */
        .macPort   = ENET_MAC_PORT_1,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 4U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0,
			.isPhyModeC45    = true,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "PRG1_RGMII2_T" */
        .macPort   = ENET_MAC_PORT_8,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 7U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0,
			.isPhyModeC45    = true,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "PRG0_RGMII1_B" */
        .macPort   = ENET_MAC_PORT_3,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 0U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0,
			.isPhyModeC45    = true,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "PRG0_RGMII02_T" */
        .macPort   = ENET_MAC_PORT_4,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 3U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0,
			.isPhyModeC45    = true,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
};

#else
/* GESI board's DP83867 PHY configuration */
static const Dp83867_Cfg gEnetGesiBoard_dp83867PhyCfg =
{
    .txClkShiftEn         = true,
    .rxClkShiftEn         = true,
    .txDelayInPs          = 2750U,  /* 2.75 ns */
    .rxDelayInPs          = 2500U,  /* 2.50 ns */
    .txFifoDepth          = 4U,
    .idleCntThresh        = 4U,     /* Improves short cable performance */
    .impedanceInMilliOhms = 35000,  /* 35 ohms */
    .gpio0Mode            = DP83867_GPIO0_LED3,
    .gpio1Mode            = DP83867_GPIO1_COL, /* Unused */
    .ledMode              =
    {
        DP83867_LED_LINKED,         /* Unused */
        DP83867_LED_LINKED_100BTX,
        DP83867_LED_RXTXACT,
        DP83867_LED_LINKED_1000BT,
    },
};

/* 4 x RGMII ports in GESI expansion board */
static EthFwBoard_MacPortCfg gEthFw_gesiMacPortCfg[] =
{
    {   /* "PRG1_RGMII1_B" */
        .macPort   = ENET_MAC_PORT_1,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 12U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = &gEnetGesiBoard_dp83867PhyCfg,
            .extendedCfgSize = sizeof(gEnetGesiBoard_dp83867PhyCfg),
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "PRG1_RGMII2_T" */
        .macPort   = ENET_MAC_PORT_8,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 15U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = &gEnetGesiBoard_dp83867PhyCfg,
            .extendedCfgSize = sizeof(gEnetGesiBoard_dp83867PhyCfg),
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "PRG0_RGMII1_B" */
        .macPort   = ENET_MAC_PORT_3,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 0U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = &gEnetGesiBoard_dp83867PhyCfg,
            .extendedCfgSize = sizeof(gEnetGesiBoard_dp83867PhyCfg),
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "PRG0_RGMII02_T" */
        .macPort   = ENET_MAC_PORT_4,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_REDUCED },
        .phyCfg    =
        {
            .phyAddr         = 3U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = &gEnetGesiBoard_dp83867PhyCfg,
            .extendedCfgSize = sizeof(gEnetGesiBoard_dp83867PhyCfg),
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_INVALID,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
};
#endif

/* 4 x QSGMII ports in QEnet expansion board */
static EthFwBoard_MacPortCfg gEthFw_qenetMacPortCfg[] =
{
    {   /* "P0" */
        .macPort   = ENET_MAC_PORT_2,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_MAIN },
        .phyCfg    =
        {
            .phyAddr         = 16U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "P1" */
        .macPort   = ENET_MAC_PORT_5,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB },
        .phyCfg    =
        {
            .phyAddr         = 17U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "P2" */
        .macPort   = ENET_MAC_PORT_6,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB },
        .phyCfg    =
        {
            .phyAddr         = 18U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
    {   /* "P3" */
        .macPort   = ENET_MAC_PORT_7,
        .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_QUAD_SERIAL_SUB },
        .phyCfg    =
        {
            .phyAddr         = 19U,
            .isStrapped      = false,
            .skipExtendedCfg = false,
            .extendedCfg     = NULL,
            .extendedCfgSize = 0U,
			.isPhyModeC45    = false,
        },
        .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_WITH_PHY,
        .linkCfg   = { ENET_SPEED_AUTO, ENET_DUPLEX_AUTO },
    },
};

/* 1 x XAUI port in MAC-to-MAC mode using (SGMII) ENET bridge expansion board */
static EthFwBoard_MacPortCfg gEthFw_enetBridgeMacPortCfg =
{
    .macPort   = ENET_MAC_PORT_2,
    .mii       = { ENET_MAC_LAYER_GMII, ENET_MAC_SUBLAYER_SERIAL },
    .phyCfg    =
    {
        .phyAddr = ENETPHY_INVALID_PHYADDR,
        .isStrapped      = false,
        .skipExtendedCfg = false,
        .extendedCfg     = NULL,
        .extendedCfgSize = 0U,
		.isPhyModeC45    = false,
    },
    .sgmiiMode = ENET_MAC_SGMIIMODE_SGMII_AUTONEG_MASTER,
    .linkCfg   = { ENET_SPEED_1GBIT, ENET_DUPLEX_FULL },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t EthFwBoard_init(uint32_t flags)
{
    Board_initCfg boardCfg = 0U;
    Board_STATUS boardStatus;

    /* Save the functionality requested by app */
    gEthFwBoard.enetBridgeEnabled = ENET_NOT_ZERO(flags & ETHFW_BOARD_ENET_BRIDGE_ENABLE);
    gEthFwBoard.gesiEnabled   = ENET_NOT_ZERO(flags & ETHFW_BOARD_GESI_ENABLE);
    gEthFwBoard.qenetEnabled  = ENET_NOT_ZERO(flags & ETHFW_BOARD_QENET_ENABLE);
    gEthFwBoard.serdesAllowed = ENET_NOT_ZERO(flags & ETHFW_BOARD_SERDES_CONFIG);
    gEthFwBoard.uartAllowed   = ENET_NOT_ZERO(flags & ETHFW_BOARD_UART_ALLOWED);
    gEthFwBoard.i2cAllowed    = ENET_NOT_ZERO(flags & ETHFW_BOARD_I2C_ALLOWED);
    gEthFwBoard.gpioAllowed   = ENET_NOT_ZERO(flags & ETHFW_BOARD_GPIO_ALLOWED);

    /* QpENet expansion board and SerDes bridge board are mutually exclusive */
    if (gEthFwBoard.qenetEnabled && gEthFwBoard.enetBridgeEnabled)
    {
        appLogPrintf("QpENet and SerDes bridge cannot be simultaneously enabled\n");
        EnetAppUtils_assert(false);
    }

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
    boardCfg |= BOARD_INIT_ENETCTRL_CPSW9G;
    boardStatus = Board_init(boardCfg);
    EnetAppUtils_assert(boardStatus == BOARD_SOK);

    /* Detect expansion boards attached to main board (CPB) */
    EthFwBoard_detectDBs();

    /* Configure GESI board */
    if (gEthFwBoard.gesiEnabled && gEthFwBoard.gesiDetected)
    {
        EthFwBoard_configGesi();
    }

    /* Configure QSGMII expansion board */
    if (gEthFwBoard.qenetEnabled && gEthFwBoard.qenetDetected)
    {
        EthFwBoard_configQenet();
    }

    if (gEthFwBoard.enetBridgeEnabled)
    {
        EthFwBoard_configSerdesBridge();
    }

    /* Set CPSW clocks: CPPI, RGMII 5/50/250 MHz, CPTS */
    EthFwBoard_configCpswClocks();

    return boardStatus;
}

uint32_t EthFwBoard_getMacPorts(Enet_MacPort macPorts[ENET_MAC_PORT_NUM])
{
    uint32_t num = 0U;
    uint32_t req;
    uint32_t i;

    memset(macPorts, 0, sizeof(*macPorts));

    if (gEthFwBoard.gesiEnabled && gEthFwBoard.gesiDetected)
    {
        req = EnetUtils_min(ENET_MAC_PORT_NUM, ENET_ARRAYSIZE(gEthFw_gesiMacPortCfg));
        for (i = 0U; i < req; i++)
        {
            macPorts[num++] = gEthFw_gesiMacPortCfg[i].macPort;
        }
    }

    if (gEthFwBoard.qenetEnabled && gEthFwBoard.qenetDetected)
    {
        req = EnetUtils_min(ENET_MAC_PORT_NUM - num, ENET_ARRAYSIZE(gEthFw_qenetMacPortCfg));
        for (i = 0U; i < req; i++)
        {
            macPorts[num++] = gEthFw_qenetMacPortCfg[i].macPort;
        }
    }

    if (gEthFwBoard.enetBridgeEnabled)
    {
        if (num < ENET_MAC_PORT_NUM)
        {
            macPorts[num++] = gEthFw_enetBridgeMacPortCfg.macPort;
        }
    }

    return num;
}

static const EthFwBoard_MacPortCfg *EthFwBoard_findPortCfg(Enet_MacPort macPort)
{
    const EthFwBoard_MacPortCfg *portCfg = NULL;
    uint32_t i;

    if (gEthFwBoard.gesiEnabled && gEthFwBoard.gesiDetected)
    {
        for (i = 0U; i < ENET_ARRAYSIZE(gEthFw_gesiMacPortCfg); i++)
        {
            if (gEthFw_gesiMacPortCfg[i].macPort == macPort)
            {
                portCfg = &gEthFw_gesiMacPortCfg[i];
                break;
            }
        }
    }

    if ((portCfg == NULL) &&
        gEthFwBoard.qenetEnabled && gEthFwBoard.qenetDetected)
    {
        for (i = 0U; i < ENET_ARRAYSIZE(gEthFw_qenetMacPortCfg); i++)
        {
            if (gEthFw_qenetMacPortCfg[i].macPort == macPort)
            {
                portCfg = &gEthFw_qenetMacPortCfg[i];
                break;
            }
        }
    }

    if ((portCfg == NULL) && gEthFwBoard.enetBridgeEnabled)
    {
        if (gEthFw_enetBridgeMacPortCfg.macPort == macPort)
        {
            portCfg = &gEthFw_enetBridgeMacPortCfg;
        }
    }

    return portCfg;
}

int32_t EthFwBoard_setPortCfg(Enet_MacPort macPort,
                              CpswMacPort_Cfg *macCfg,
                              EnetMacPort_Interface *mii,
                              EnetPhy_Cfg *phyCfg,
                              EnetMacPort_LinkCfg *linkCfg)
{
    const EthFwBoard_MacPortCfg *portCfg;
    uint32_t i;
    int32_t status = ENET_ENOTFOUND;

    CpswMacPort_initCfg(macCfg);
    EnetPhy_initCfg(phyCfg);

    portCfg = EthFwBoard_findPortCfg(macPort);
    if (portCfg != NULL)
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

		phyCfg->isPhyModeC45      = portCfg->phyCfg.isPhyModeC45;
        /* Set link configuration: speed and duplex */
        *linkCfg = portCfg->linkCfg;

        /* Set SGMII mode (applicable for Q/SGMII ports only) */
        macCfg->sgmiiMode = portCfg->sgmiiMode;

        status = ENET_SOK;
    }

    return status;
}

static void EthFwBoard_enableMods(void)
{
    uint32_t i;
    uint32_t clkModId[] = { TISCI_DEV_DDR0,
                            TISCI_DEV_TIMER12,
                            TISCI_DEV_TIMER13,
                            TISCI_DEV_UART2, };

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
    Board_pinmuxUpdate(gEthFwPinmuxData, BOARD_SOC_DOMAIN_MAIN);

    /* Configure pinmux settings for Ethernet ports and MDIO */
    Board_pinmuxUpdate(gJ721E_MainPinmuxDataGesiCpsw9gQsgmii, BOARD_SOC_DOMAIN_MAIN);

    /* REVISIT - Configure CPSW9G pins for ports on the GESI board */
    Board_pinmuxGetCfg(&pinmuxCfg);
    pinmuxCfg.gesiExp = BOARD_PINMUX_GESI_CPSW;
    Board_pinmuxSetCfg(&pinmuxCfg);
}

static void EthFwBoard_detectDBs(void)
{
	appLogPrintf("EthFwBoard_detectDBs - i2cAllowed(%d)\n", gEthFwBoard.i2cAllowed);
    if (gEthFwBoard.i2cAllowed)
    {
        gEthFwBoard.gesiDetected  = Board_detectBoard(BOARD_ID_GESI);
        gEthFwBoard.qenetDetected = Board_detectBoard(BOARD_ID_ENET);

        appLogPrintf("Detected boards:%s%s\n",
                     gEthFwBoard.gesiDetected ? " GESI" : "",
                     gEthFwBoard.qenetDetected ? " QSGMII" : "");
    }
    else
    {
        /* Assume expansion boards are present if detection not allowed */
        gEthFwBoard.gesiDetected  = true;
		//gEthFwBoard.qenetDetected = true;
		gEthFwBoard.qenetDetected = false;
    }
}

static void EthFwBoard_configUart(void)
{
    Board_initParams_t initParams;

    Board_getInitParams(&initParams);
    initParams.uartSocDomain = ETHFW_UART_DOMAIN;
    initParams.uartInst      = ETHFW_UART_INST;
    initParams.pscMode       = BOARD_PSC_DEVICE_MODE_NONEXCLUSIVE;
    Board_setInitParams(&initParams);
}

static void EthFwBoard_configGesi(void)
{
    if (gEthFwBoard.gpioAllowed)
    {
        GPIO_init();
        GPIO_write(0, 1);
        GPIO_write(1, 1);
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
        EthFwBoard_configSierra0Clks();

        /* Configure SerDes for QSGMII functionality */
        boardStatus = Board_serdesCfgQsgmii();
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
    }
}

static void EthFwBoard_configSerdesBridge(void)
{
    Board_STATUS boardStatus;

    if (gEthFwBoard.serdesAllowed)
    {
        /* Configure SerDes clocks */
        EthFwBoard_configSierra0Clks();

        /* Configure SerDes for XAUI functionality */
        boardStatus = Board_serdesCfgXaui();
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
    }
}

static void EthFwBoard_configSierra0Clks(void)
{
    uint32_t moduleId = TISCI_DEV_SERDES_16G0;
    uint32_t clkRateHz = 100000000U;
    uint32_t clkId[] = {
        TISCI_DEV_SERDES_16G0_CORE_REF1_CLK,
        TISCI_DEV_SERDES_16G0_CORE_REF_CLK};
    uint32_t clkParId[] = {
        TISCI_DEV_SERDES_16G0_CORE_REF1_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT4_CLK,
        TISCI_DEV_SERDES_16G0_CORE_REF_CLK_PARENT_HSDIV4_16FFT_MAIN_2_HSDIVOUT4_CLK};
    uint32_t i;
    int32_t status;

    for (i = 0U; i < ENET_ARRAYSIZE(clkId); i++)
    {
        status = Sciclient_pmSetModuleClkParent(moduleId, clkId[i], clkParId[i], SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != CSL_PASS)
        {
            appLogPrintf("Failed to reparent clk %u: %d\n", clkId[i], status);
            EnetAppUtils_assert(false);
        }

        EnetAppUtils_clkRateSet(moduleId, clkId[i], clkRateHz);
    }

    EnetAppUtils_setDeviceState(moduleId, TISCI_MSG_VALUE_DEVICE_SW_STATE_ON, 0U);
}

static void EthFwBoard_configCpswClocks(void)
{
    /* Enable CPPI_CLK_CLK and set RGMII_MHZ_[5,50,250]_CLK clock rate */
    EnetAppUtils_enableClocks(ENET_CPSW_9G, 0U);

    /* Select CPTS source clock (CPTS_RFT_CLK) in CLKSEL mux */
    EnetAppUtils_selectCptsClock(ENET_CPSW_9G, 0U, ETHFW_CPSW_CPTS_RFT_CLK);
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
    uint32_t i, j;

    if (gEthFwBoard.gesiEnabled && gEthFwBoard.gesiDetected)
    {
        /* Read number of MAC addresses in GESI board */
        boardStatus = Board_readMacAddrCount(BOARD_ID_GESI, &macAddrCnt);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
        EnetAppUtils_assert(macAddrCnt <= ENET_RM_NUM_MACADDR_MAX);

        /* Read MAC addresses */
        boardStatus = Board_readMacAddr(BOARD_ID_GESI, macAddrBuf, sizeof(macAddrBuf), &tempCnt);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
        EnetAppUtils_assert(tempCnt == macAddrCnt);

        /* Save only those required to meet the max number of MAC entries */
        macAddrCnt = EnetUtils_min(macAddrCnt, poolSize);
        for (i = 0U; i < macAddrCnt; i++)
        {
            memcpy(macAddr[i], &macAddrBuf[i * BOARD_MAC_ADDR_BYTES], ENET_MAC_ADDR_LEN);
        }

        allocCnt = macAddrCnt;
    }

    if (gEthFwBoard.qenetEnabled && gEthFwBoard.qenetDetected)
    {
        /* Read number of MAC addresses in QUAD Eth board */
        boardStatus = Board_readMacAddrCount(BOARD_ID_ENET, &macAddrCnt);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
        EnetAppUtils_assert(macAddrCnt <= ENET_RM_NUM_MACADDR_MAX);

        /* Read MAC addresses */
        boardStatus = Board_readMacAddr(BOARD_ID_ENET, macAddrBuf, sizeof(macAddrBuf), &tempCnt);
        EnetAppUtils_assert(boardStatus == BOARD_SOK);
        EnetAppUtils_assert(tempCnt == macAddrCnt);

        /* Save only those required to meet the max number of MAC entries */
        macAddrCnt = EnetUtils_min(macAddrCnt, poolSize - allocCnt);
        for (i = 0U, j = allocCnt; i < macAddrCnt; i++, j++)
        {
            memcpy(macAddr[j], &macAddrBuf[i * BOARD_MAC_ADDR_BYTES], ENET_MAC_ADDR_LEN);
        }

        allocCnt += macAddrCnt;
    }

    if (allocCnt == 0U)
    {
        appLogPrintf("No MAC addresses read from GESI and/or QENET boards\n");
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
