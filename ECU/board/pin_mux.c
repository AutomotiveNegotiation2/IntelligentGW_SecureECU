/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v13.0
processor: MIMXRT1176xxxxx
package_id: MIMXRT1176DVMAA
mcu_data: ksdk2_0
processor_version: 13.0.2
board: MIMXRT1170-EVK
pin_labels:
- {pin_num: N6, pin_signal: GPIO_LPSR_00, label: 'CAN3_TX/U42[1]', identifier: CAN3_TX;CAN_TX}
- {pin_num: R6, pin_signal: GPIO_LPSR_01, label: 'CAN3_RX/U42[4]', identifier: CAN3_RX;CAN_RX}
- {pin_num: A5, pin_signal: GPIO_DISP_B2_13, label: 'INT1_COMBO/BT_UART_RTS/U16[4]/U354[5]/ETHPHY_RST_B/U10[12]', identifier: BT_UART_RTS;ENET_1G_RST}
- {pin_num: N13, pin_signal: GPIO_AD_06, label: 'USB_OTG2_OC/U18[A2]/J9[10]/AUD_INT', identifier: CANFD_TX}
- {pin_num: T17, pin_signal: GPIO_AD_07, label: 'USB_OTG2_PWR/WL_DEV_WAKE/U354[10]/J10[2]', identifier: CANFD_RX}
- {pin_num: N14, pin_signal: GPIO_AD_14, label: 'SPDIF_EXT_CLK/CAN_STBY/J9[16]', identifier: CAN_FD_STBY}
- {pin_num: K13, pin_signal: GPIO_AD_20, label: 'SAI1_RXD[0]/J9[7]/J50[20]/J61[1]/BT_PCM_RXD/U16[10]/U355[18]', identifier: ENET_RST}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
    BOARD_InitCanPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: M15, peripheral: LPUART1, signal: RXD, pin_signal: GPIO_AD_25, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Pull,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: L13, peripheral: LPUART1, signal: TXD, pin_signal: GPIO_AD_24, software_input_on: Disable, pull_up_down_config: Pull_Down, pull_keeper_select: Pull,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: T8, peripheral: GPIO13, signal: 'gpio_io, 00', pin_signal: WAKEUP, direction: INPUT, software_input_on: Enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  /* GPIO configuration of USER_BUTTON on WAKEUP_DIG (pin T8) */
  gpio_pin_config_t USER_BUTTON_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on WAKEUP_DIG (pin T8) */
  GPIO_PinInit(GPIO13, 0U, &USER_BUTTON_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 is configured as LPUART1_TXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 is configured as LPUART1_RXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_WAKEUP_DIG_GPIO13_IO00,          /* WAKEUP_DIG is configured as GPIO13_IO00 */
      1U);                                    /* Software Input On Field: Force input path of pad WAKEUP_DIG */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 PAD functional properties : */
      0x06U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Enable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 PAD functional properties : */
      0x06U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Enable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitCanPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: R6, peripheral: CAN3, signal: RX, pin_signal: GPIO_LPSR_01, identifier: CAN_RX, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: N6, peripheral: CAN3, signal: TX, pin_signal: GPIO_LPSR_00, identifier: CAN_TX, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper,
    open_drain: Disable, drive_strength: High, slew_rate: Slow}
  - {pin_num: T17, peripheral: CAN1, signal: RX, pin_signal: GPIO_AD_07, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper, open_drain: Disable,
    drive_strength: High, slew_rate: Slow}
  - {pin_num: N13, peripheral: CAN1, signal: TX, pin_signal: GPIO_AD_06, software_input_on: Enable, pull_up_down_config: Pull_Down, pull_keeper_select: Keeper, open_drain: Disable,
    drive_strength: High, slew_rate: Slow}
  - {pin_num: N14, peripheral: GPIO9, signal: 'gpio_io, 13', pin_signal: GPIO_AD_14, direction: OUTPUT, gpio_init_state: 'true', pull_up_down_config: Pull_Down}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitCanPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitCanPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */
  CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);      /* LPCG on: LPCG is ON. */

  /* GPIO configuration of CAN_FD_STBY on GPIO_AD_14 (pin N14) */
  gpio_pin_config_t CAN_FD_STBY_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_14 (pin N14) */
  GPIO_PinInit(GPIO9, 13U, &CAN_FD_STBY_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_06_FLEXCAN1_TX,          /* GPIO_AD_06 is configured as FLEXCAN1_TX */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_AD_06 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_07_FLEXCAN1_RX,          /* GPIO_AD_07 is configured as FLEXCAN1_RX */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_AD_07 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_14_GPIO9_IO13,           /* GPIO_AD_14 is configured as GPIO9_IO13 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_00_FLEXCAN3_TX,        /* GPIO_LPSR_00 is configured as FLEXCAN3_TX */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_00 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_01_FLEXCAN3_RX,        /* GPIO_LPSR_01 is configured as FLEXCAN3_RX */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_01 */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_06_FLEXCAN1_TX,          /* GPIO_AD_06 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_07_FLEXCAN1_RX,          /* GPIO_AD_07 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AD_14_GPIO9_IO13,           /* GPIO_AD_14 PAD functional properties : */
      0x06U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Enable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_00_FLEXCAN3_TX,        /* GPIO_LPSR_00 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain LPSR Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_LPSR_01_FLEXCAN3_RX,        /* GPIO_LPSR_01 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: high driver
                                                 Pull / Keep Select Field: Pull Disable
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain LPSR Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitEnetPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: P17, peripheral: GPIO9, signal: 'gpio_io, 11', pin_signal: GPIO_AD_12}
  - {pin_num: K16, peripheral: ENET, signal: enet_mdc, pin_signal: GPIO_AD_32}
  - {pin_num: H17, peripheral: ENET, signal: enet_mdio, pin_signal: GPIO_AD_33}
  - {pin_num: E9, peripheral: ENET, signal: 'enet_tdata, 00', pin_signal: GPIO_DISP_B2_02}
  - {pin_num: D7, peripheral: ENET, signal: 'enet_tdata, 01', pin_signal: GPIO_DISP_B2_03}
  - {pin_num: C7, peripheral: ENET, signal: enet_tx_en, pin_signal: GPIO_DISP_B2_04}
  - {pin_num: C9, peripheral: ENET, signal: enet_ref_clk, pin_signal: GPIO_DISP_B2_05, direction: OUTPUT, software_input_on: Enable, slew_rate: Fast}
  - {pin_num: C6, peripheral: ENET, signal: 'enet_rdata, 00', pin_signal: GPIO_DISP_B2_06}
  - {pin_num: D6, peripheral: ENET, signal: 'enet_rdata, 01', pin_signal: GPIO_DISP_B2_07}
  - {pin_num: B5, peripheral: ENET, signal: enet_rx_en, pin_signal: GPIO_DISP_B2_08}
  - {pin_num: D8, peripheral: ENET, signal: enet_rx_er, pin_signal: GPIO_DISP_B2_09}
  - {pin_num: K13, peripheral: GPIO9, signal: 'gpio_io, 19', pin_signal: GPIO_AD_20, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitEnetPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitEnetPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  /* GPIO configuration of ENET_RST on GPIO_AD_20 (pin K13) */
  gpio_pin_config_t ENET_RST_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_20 (pin K13) */
  GPIO_PinInit(GPIO9, 19U, &ENET_RST_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_12_GPIO9_IO11,           /* GPIO_AD_12 is configured as GPIO9_IO11 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_20_GPIO9_IO19,           /* GPIO_AD_20 is configured as GPIO9_IO19 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_32_ENET_MDC,             /* GPIO_AD_32 is configured as ENET_MDC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_33_ENET_MDIO,            /* GPIO_AD_33 is configured as ENET_MDIO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00,  /* GPIO_DISP_B2_02 is configured as ENET_TX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01,  /* GPIO_DISP_B2_03 is configured as ENET_TX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN,      /* GPIO_DISP_B2_04 is configured as ENET_TX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK,    /* GPIO_DISP_B2_05 is configured as ENET_REF_CLK */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_DISP_B2_05 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00,  /* GPIO_DISP_B2_06 is configured as ENET_RX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01,  /* GPIO_DISP_B2_07 is configured as ENET_RX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN,      /* GPIO_DISP_B2_08 is configured as ENET_RX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER,      /* GPIO_DISP_B2_09 is configured as ENET_RX_ER */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_GPR->GPR4 = ((IOMUXC_GPR->GPR4 &
    (~(IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK))) /* Mask bits to zero which are setting */
      | IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR(0x01U) /* ENET_REF_CLK direction control: 0x01U */
    );
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK,    /* GPIO_DISP_B2_05 PAD functional properties : */
      0x03U);                                 /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitEnet1GPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: E13, peripheral: ENET_1G, signal: enet_rx_en, pin_signal: GPIO_DISP_B1_00}
  - {pin_num: D13, peripheral: ENET_1G, signal: enet_rx_clk, pin_signal: GPIO_DISP_B1_01}
  - {pin_num: D11, peripheral: ENET_1G, signal: 'enet_rdata, 00', pin_signal: GPIO_DISP_B1_02}
  - {pin_num: E11, peripheral: ENET_1G, signal: 'enet_rdata, 01', pin_signal: GPIO_DISP_B1_03}
  - {pin_num: E10, peripheral: ENET_1G, signal: 'enet_rdata, 02', pin_signal: GPIO_DISP_B1_04}
  - {pin_num: C11, peripheral: ENET_1G, signal: 'enet_rdata, 03', pin_signal: GPIO_DISP_B1_05}
  - {pin_num: D10, peripheral: ENET_1G, signal: 'enet_tdata, 03', pin_signal: GPIO_DISP_B1_06}
  - {pin_num: E12, peripheral: ENET_1G, signal: 'enet_tdata, 02', pin_signal: GPIO_DISP_B1_07}
  - {pin_num: A15, peripheral: ENET_1G, signal: 'enet_tdata, 01', pin_signal: GPIO_DISP_B1_08}
  - {pin_num: C13, peripheral: ENET_1G, signal: 'enet_tdata, 00', pin_signal: GPIO_DISP_B1_09}
  - {pin_num: B14, peripheral: ENET_1G, signal: enet_tx_en, pin_signal: GPIO_DISP_B1_10}
  - {pin_num: A14, peripheral: ENET_1G, signal: enet_tx_clk_io, pin_signal: GPIO_DISP_B1_11}
  - {pin_num: A5, peripheral: GPIO11, signal: 'gpio_io, 14', pin_signal: GPIO_DISP_B2_13, identifier: ENET_1G_RST, direction: OUTPUT}
  - {pin_num: U2, peripheral: ENET_1G, signal: enet_mdc, pin_signal: GPIO_EMC_B2_19}
  - {pin_num: R3, peripheral: ENET_1G, signal: enet_mdio, pin_signal: GPIO_EMC_B2_20}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitEnet1GPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitEnet1GPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  /* GPIO configuration of ENET_1G_RST on GPIO_DISP_B2_13 (pin A5) */
  gpio_pin_config_t ENET_1G_RST_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_DISP_B2_13 (pin A5) */
  GPIO_PinInit(GPIO11, 14U, &ENET_1G_RST_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_00_ENET_1G_RX_EN,   /* GPIO_DISP_B1_00 is configured as ENET_1G_RX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_01_ENET_1G_RX_CLK,  /* GPIO_DISP_B1_01 is configured as ENET_1G_RX_CLK */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_02_ENET_1G_RX_DATA00,  /* GPIO_DISP_B1_02 is configured as ENET_1G_RX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_03_ENET_1G_RX_DATA01,  /* GPIO_DISP_B1_03 is configured as ENET_1G_RX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_04_ENET_1G_RX_DATA02,  /* GPIO_DISP_B1_04 is configured as ENET_1G_RX_DATA02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_05_ENET_1G_RX_DATA03,  /* GPIO_DISP_B1_05 is configured as ENET_1G_RX_DATA03 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_06_ENET_1G_TX_DATA03,  /* GPIO_DISP_B1_06 is configured as ENET_1G_TX_DATA03 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_07_ENET_1G_TX_DATA02,  /* GPIO_DISP_B1_07 is configured as ENET_1G_TX_DATA02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_08_ENET_1G_TX_DATA01,  /* GPIO_DISP_B1_08 is configured as ENET_1G_TX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_09_ENET_1G_TX_DATA00,  /* GPIO_DISP_B1_09 is configured as ENET_1G_TX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_10_ENET_1G_TX_EN,   /* GPIO_DISP_B1_10 is configured as ENET_1G_TX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_11_ENET_1G_TX_CLK_IO,  /* GPIO_DISP_B1_11 is configured as ENET_1G_TX_CLK_IO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_13_GPIO11_IO14,     /* GPIO_DISP_B2_13 is configured as GPIO11_IO14 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_EMC_B2_19_ENET_1G_MDC,      /* GPIO_EMC_B2_19 is configured as ENET_1G_MDC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_EMC_B2_20_ENET_1G_MDIO,     /* GPIO_EMC_B2_20 is configured as ENET_1G_MDIO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
