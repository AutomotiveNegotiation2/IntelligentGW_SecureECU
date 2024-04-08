/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* GPIO_AD_25 (coord M15), LPUART1_RXD/J32[2] */
/* Routed pin properties */
#define BOARD_INITPINS_LPUART1_RXD_PERIPHERAL                            LPUART1   /*!< Peripheral name */
#define BOARD_INITPINS_LPUART1_RXD_SIGNAL                                    RXD   /*!< Signal name */

/* GPIO_AD_24 (coord L13), LPUART1_TXD/J31[2] */
/* Routed pin properties */
#define BOARD_INITPINS_LPUART1_TXD_PERIPHERAL                            LPUART1   /*!< Peripheral name */
#define BOARD_INITPINS_LPUART1_TXD_SIGNAL                                    TXD   /*!< Signal name */

/* WAKEUP (coord T8), USER_BUTTON */
/* Routed pin properties */
#define BOARD_INITPINS_USER_BUTTON_PERIPHERAL                             GPIO13   /*!< Peripheral name */
#define BOARD_INITPINS_USER_BUTTON_SIGNAL                                gpio_io   /*!< Signal name */
#define BOARD_INITPINS_USER_BUTTON_CHANNEL                                    0U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_USER_BUTTON_GPIO                                   GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_USER_BUTTON_GPIO_PIN                                   0U   /*!< GPIO pin number */
#define BOARD_INITPINS_USER_BUTTON_GPIO_PIN_MASK                      (1U << 0U)   /*!< GPIO pin mask */

/* GPIO_AD_14 (coord N14), SPDIF_EXT_CLK/CAN_STBY/J9[16] */
/* Routed pin properties */
#define BOARD_INITPINS_CAN_FD_STBY_PERIPHERAL                              GPIO9   /*!< Peripheral name */
#define BOARD_INITPINS_CAN_FD_STBY_SIGNAL                                gpio_io   /*!< Signal name */
#define BOARD_INITPINS_CAN_FD_STBY_CHANNEL                                   13U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_CAN_FD_STBY_GPIO                                    GPIO9   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_CAN_FD_STBY_GPIO_PIN                                  13U   /*!< GPIO pin number */
#define BOARD_INITPINS_CAN_FD_STBY_GPIO_PIN_MASK                     (1U << 13U)   /*!< GPIO pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);                    /* Function assigned for the Cortex-M7F */

/* GPIO_LPSR_01 (coord R6), CAN3_RX/U42[4] */
/* Routed pin properties */
#define BOARD_INITCANPINS_CAN_RX_PERIPHERAL                                 CAN3   /*!< Peripheral name */
#define BOARD_INITCANPINS_CAN_RX_SIGNAL                                       RX   /*!< Signal name */

/* GPIO_LPSR_00 (coord N6), CAN3_TX/U42[1] */
/* Routed pin properties */
#define BOARD_INITCANPINS_CAN_TX_PERIPHERAL                                 CAN3   /*!< Peripheral name */
#define BOARD_INITCANPINS_CAN_TX_SIGNAL                                       TX   /*!< Signal name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCanPins(void);                 /* Function assigned for the Cortex-M7F */

/* GPIO_AD_07 (coord T17), USB_OTG2_PWR/WL_DEV_WAKE/U354[10]/J10[2] */
/* Routed pin properties */
#define BOARD_INITCANFDPINS_CANFD_RX_PERIPHERAL                             CAN1   /*!< Peripheral name */
#define BOARD_INITCANFDPINS_CANFD_RX_SIGNAL                                   RX   /*!< Signal name */

/* GPIO_AD_06 (coord N13), USB_OTG2_OC/U18[A2]/J9[10]/AUD_INT */
/* Routed pin properties */
#define BOARD_INITCANFDPINS_CANFD_TX_PERIPHERAL                             CAN1   /*!< Peripheral name */
#define BOARD_INITCANFDPINS_CANFD_TX_SIGNAL                                   TX   /*!< Signal name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCanFdPins(void);               /* Function assigned for the Cortex-M7F */

/* GPIO_AD_32 (coord K16), ENET_MDC/U7[12]/SD1_CD_B/J15[9] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_MDC_PERIPHERAL                              ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_MDC_SIGNAL                              enet_mdc   /*!< Signal name */

/* GPIO_AD_33 (coord H17), ENET_MDIO/U7[11] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_MDIO_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_MDIO_SIGNAL                            enet_mdio   /*!< Signal name */

/* GPIO_DISP_B2_02 (coord E9), ENET_TXD0/U7[24]/BT_CFG[8] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_TXD0_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_TXD0_SIGNAL                           enet_tdata   /*!< Signal name */
#define BOARD_INITENETPINS_ENET_TXD0_CHANNEL                                  0U   /*!< Signal channel */

/* GPIO_DISP_B2_03 (coord D7), ENET_TXD1/U7[25]/BT_CFG[9] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_TXD1_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_TXD1_SIGNAL                           enet_tdata   /*!< Signal name */
#define BOARD_INITENETPINS_ENET_TXD1_CHANNEL                                  1U   /*!< Signal channel */

/* GPIO_DISP_B2_04 (coord C7), ENET_TXEN/U7[23]/BT_CFG[10] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_TXEN_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_TXEN_SIGNAL                           enet_tx_en   /*!< Signal name */

/* GPIO_DISP_B2_05 (coord C9), ENET_TX_REF_CLK/U7[9]/BT_CFG[11] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_TX_REF_CLK_PERIPHERAL                       ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_TX_REF_CLK_SIGNAL                   enet_ref_clk   /*!< Signal name */

/* GPIO_DISP_B2_06 (coord C6), ENET_RXD0/U7[16] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_RXD0_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_RXD0_SIGNAL                           enet_rdata   /*!< Signal name */
#define BOARD_INITENETPINS_ENET_RXD0_CHANNEL                                  0U   /*!< Signal channel */

/* GPIO_DISP_B2_07 (coord D6), ENET_RXD1/U7[15] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_RXD1_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_RXD1_SIGNAL                           enet_rdata   /*!< Signal name */
#define BOARD_INITENETPINS_ENET_RXD1_CHANNEL                                  1U   /*!< Signal channel */

/* GPIO_DISP_B2_08 (coord B5), ENET_CRS_DV/U7[18] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_CRS_DV_PERIPHERAL                           ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_CRS_DV_SIGNAL                         enet_rx_en   /*!< Signal name */

/* GPIO_DISP_B2_09 (coord D8), ENET_RXER/U7[20] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_RXER_PERIPHERAL                             ENET   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_RXER_SIGNAL                           enet_rx_er   /*!< Signal name */

/* GPIO_AD_20 (coord K13), SAI1_RXD[0]/J9[7]/J50[20]/J61[1]/BT_PCM_RXD/U16[10]/U355[18] */
/* Routed pin properties */
#define BOARD_INITENETPINS_ENET_RST_PERIPHERAL                             GPIO9   /*!< Peripheral name */
#define BOARD_INITENETPINS_ENET_RST_SIGNAL                               gpio_io   /*!< Signal name */
#define BOARD_INITENETPINS_ENET_RST_CHANNEL                                  19U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITENETPINS_ENET_RST_GPIO                                   GPIO9   /*!< GPIO peripheral base pointer */
#define BOARD_INITENETPINS_ENET_RST_GPIO_PIN                                 19U   /*!< GPIO pin number */
#define BOARD_INITENETPINS_ENET_RST_GPIO_PIN_MASK                    (1U << 19U)   /*!< GPIO pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitEnetPins(void);                /* Function assigned for the Cortex-M7F */

/* GPIO_DISP_B1_00 (coord E13), ENET_RGMII_RX_EN/U10[26] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_RX_EN_PERIPHERAL                 ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RX_EN_SIGNAL                  enet_rx_en   /*!< Signal name */

/* GPIO_DISP_B1_01 (coord D13), ENET_RGMII_RXC/U10[27] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXC_PERIPHERAL                   ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXC_SIGNAL                   enet_rx_clk   /*!< Signal name */

/* GPIO_DISP_B1_02 (coord D11), ENET_RGMII_RXD0/U10[25] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD0_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD0_SIGNAL                   enet_rdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD0_CHANNEL                          0U   /*!< Signal channel */

/* GPIO_DISP_B1_03 (coord E11), ENET_RGMII_RXD1/U10[24] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD1_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD1_SIGNAL                   enet_rdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD1_CHANNEL                          1U   /*!< Signal channel */

/* GPIO_DISP_B1_04 (coord E10), ENET_RGMII_RXD2/U10[23] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD2_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD2_SIGNAL                   enet_rdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD2_CHANNEL                          2U   /*!< Signal channel */

/* GPIO_DISP_B1_05 (coord C11), ENET_RGMII_RXD3/U10[22] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD3_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD3_SIGNAL                   enet_rdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_RXD3_CHANNEL                          3U   /*!< Signal channel */

/* GPIO_DISP_B1_06 (coord D10), ENET_RGMII_TXD3/U10[15]/BT_CFG[0] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD3_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD3_SIGNAL                   enet_tdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD3_CHANNEL                          3U   /*!< Signal channel */

/* GPIO_DISP_B1_07 (coord E12), ENET_RGMII_TXD2/U10[16]/BT_CFG[1] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD2_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD2_SIGNAL                   enet_tdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD2_CHANNEL                          2U   /*!< Signal channel */

/* GPIO_DISP_B1_08 (coord A15), ENET_RGMII_TXD1/U10[17]/BT_CFG[2] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD1_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD1_SIGNAL                   enet_tdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD1_CHANNEL                          1U   /*!< Signal channel */

/* GPIO_DISP_B1_09 (coord C13), ENET_RGMII_TXD0/U10[18]/BT_CFG[3] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD0_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD0_SIGNAL                   enet_tdata   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXD0_CHANNEL                          0U   /*!< Signal channel */

/* GPIO_DISP_B1_10 (coord B14), ENET_RGMII_TX_EN/U10[19]/BT_CFG[4] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_TX_EN_PERIPHERAL                 ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TX_EN_SIGNAL                  enet_tx_en   /*!< Signal name */

/* GPIO_DISP_B1_11 (coord A14), ENET_RGMII_TXC/U10[20]/BT_CFG[5] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXC_PERIPHERAL                   ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_TXC_SIGNAL                enet_tx_clk_io   /*!< Signal name */

/* GPIO_DISP_B2_13 (coord A5), INT1_COMBO/BT_UART_RTS/U16[4]/U354[5]/ETHPHY_RST_B/U10[12] */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_1G_RST_PERIPHERAL                       GPIO11   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_1G_RST_SIGNAL                          gpio_io   /*!< Signal name */
#define BOARD_INITENET1GPINS_ENET_1G_RST_CHANNEL                             14U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITENET1GPINS_ENET_1G_RST_GPIO                             GPIO11   /*!< GPIO peripheral base pointer */
#define BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN                            14U   /*!< GPIO pin number */
#define BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN_MASK               (1U << 14U)   /*!< GPIO pin mask */

/* GPIO_EMC_B2_19 (coord U2), ENET_RGMII_MDC */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_MDC_PERIPHERAL                   ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_MDC_SIGNAL                      enet_mdc   /*!< Signal name */

/* GPIO_EMC_B2_20 (coord R3), ENET_RGMII_MDIO */
/* Routed pin properties */
#define BOARD_INITENET1GPINS_ENET_RGMII_MDIO_PERIPHERAL                  ENET_1G   /*!< Peripheral name */
#define BOARD_INITENET1GPINS_ENET_RGMII_MDIO_SIGNAL                    enet_mdio   /*!< Signal name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitEnet1GPins(void);              /* Function assigned for the Cortex-M7F */

/* GPIO_SD_B2_00 (coord J15), FlexSPI_B_D3/U21[E1] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D3_PERIPHERAL                      GPIO10   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D3_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D3_CHANNEL                             9U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D3_GPIO                            GPIO10   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D3_GPIO_PIN                            9U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D3_GPIO_PIN_MASK               (1U << 9U)   /*!< GPIO pin mask */

/* GPIO_SD_B2_01 (coord J14), FlexSPI_B_D2/U21[E2] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D2_PERIPHERAL                      GPIO10   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D2_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D2_CHANNEL                            10U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D2_GPIO                            GPIO10   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D2_GPIO_PIN                           10U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D2_GPIO_PIN_MASK              (1U << 10U)   /*!< GPIO pin mask */

/* GPIO_SD_B2_02 (coord H13), FlexSPI_B_D1/U21[E3] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D1_PERIPHERAL                      GPIO10   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D1_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D1_CHANNEL                            11U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D1_GPIO                            GPIO10   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D1_GPIO_PIN                           11U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D1_GPIO_PIN_MASK              (1U << 11U)   /*!< GPIO pin mask */

/* GPIO_SD_B2_03 (coord E15), FlexSPI_B_D0/U21[D5] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D0_PERIPHERAL                      GPIO10   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D0_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D0_CHANNEL                            12U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D0_GPIO                            GPIO10   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D0_GPIO_PIN                           12U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_FlexSPI_B_D0_GPIO_PIN_MASK              (1U << 12U)   /*!< GPIO pin mask */

/* GPIO_SNVS_00 (coord R10), J42[3] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_RED_D1_PERIPHERAL                        GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_RED_D1_SIGNAL                           gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_RED_D1_CHANNEL                               3U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO                              GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO_PIN                              3U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO_PIN_MASK                 (1U << 3U)   /*!< GPIO pin mask */

/* GPIO_SNVS_01 (coord P10), J42[4] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D1_PERIPHERAL                      GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D1_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D1_CHANNEL                             4U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO                            GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO_PIN                            4U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO_PIN_MASK               (1U << 4U)   /*!< GPIO pin mask */

/* GPIO_SNVS_02 (coord L9), J42[5] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_RED_D2_PERIPHERAL                        GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_RED_D2_SIGNAL                           gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_RED_D2_CHANNEL                               5U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO                              GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO_PIN                              5U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO_PIN_MASK                 (1U << 5U)   /*!< GPIO pin mask */

/* GPIO_SNVS_03 (coord M10), J42[6] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D2_PERIPHERAL                      GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D2_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D2_CHANNEL                             6U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO                            GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO_PIN                            6U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO_PIN_MASK               (1U << 6U)   /*!< GPIO pin mask */

/* GPIO_SNVS_04 (coord N10), J42[7] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_RED_D3_PERIPHERAL                        GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_RED_D3_SIGNAL                           gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_RED_D3_CHANNEL                               7U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO                              GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO_PIN                              7U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO_PIN_MASK                 (1U << 7U)   /*!< GPIO pin mask */

/* GPIO_SNVS_05 (coord P9), J42[8] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D3_PERIPHERAL                      GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D3_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D3_CHANNEL                             8U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO                            GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO_PIN                            8U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO_PIN_MASK               (1U << 8U)   /*!< GPIO pin mask */

/* GPIO_SNVS_06 (coord M9), J42[9] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_RED_D4_PERIPHERAL                        GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_RED_D4_SIGNAL                           gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_RED_D4_CHANNEL                               9U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO                              GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO_PIN                              9U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO_PIN_MASK                 (1U << 9U)   /*!< GPIO pin mask */

/* GPIO_SNVS_07 (coord R9), J42[10] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D4_PERIPHERAL                      GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D4_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D4_CHANNEL                            10U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO                            GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO_PIN                           10U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO_PIN_MASK              (1U << 10U)   /*!< GPIO pin mask */

/* GPIO_SNVS_08 (coord N9), J42[11] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_RED_D5_PERIPHERAL                        GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_RED_D5_SIGNAL                           gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_RED_D5_CHANNEL                              11U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO                              GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO_PIN                             11U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO_PIN_MASK                (1U << 11U)   /*!< GPIO pin mask */

/* GPIO_SNVS_09 (coord R11), J42[12] */
/* Routed pin properties */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D5_PERIPHERAL                      GPIO13   /*!< Peripheral name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D5_SIGNAL                         gpio_io   /*!< Signal name */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D5_CHANNEL                            12U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO                            GPIO13   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO_PIN                           12U   /*!< GPIO pin number */
#define BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO_PIN_MASK              (1U << 12U)   /*!< GPIO pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitFuncIoPins(void);              /* Function assigned for the Cortex-M7F */

/* GPIO_AD_15 (coord M14), SPDIF_IN/U43[4]/BT_RST#/U16[14]/J54[54] */
/* Routed pin properties */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_SPDIF_IN_PERIPHERAL             LPUART10   /*!< Peripheral name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_SPDIF_IN_SIGNAL                      TXD   /*!< Signal name */

/* GPIO_AD_16 (coord N17), SPDIF_OUT/WIFI_RST_B/U354[3] */
/* Routed pin properties */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_SPDIF_OUT_PERIPHERAL            LPUART10   /*!< Peripheral name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_SPDIF_OUT_SIGNAL                     RXD   /*!< Signal name */

/* GPIO_LPSR_08 (coord U8), DMIC_CLK/U41[1]/U44[1]/J50[18] */
/* Routed pin properties */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_DMIC_CLK_PERIPHERAL             LPUART11   /*!< Peripheral name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_DMIC_CLK_SIGNAL                      TXD   /*!< Signal name */

/* GPIO_LPSR_09 (coord P5), DMIC_DATA0/U41[5]/J50[20]/LPSPI6_CS0/J26[11] */
/* Routed pin properties */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_DMIC_DATA0_PERIPHERAL           LPUART11   /*!< Peripheral name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_DMIC_DATA0_SIGNAL                    RXD   /*!< Signal name */

/* GPIO_AD_21 (coord K14), SAI1_TXD[0]/J9[9]/J62[1]/BT_PCM_TXD/U16[9]/U354[6] */
/* Routed pin properties */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_WHITE_LED_PERIPHERAL               GPIO9   /*!< Peripheral name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_WHITE_LED_SIGNAL                 gpio_io   /*!< Signal name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_WHITE_LED_CHANNEL                    20U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_WHITE_LED_GPIO                     GPIO9   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_WHITE_LED_GPIO_PIN                   20U   /*!< GPIO pin number */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_WHITE_LED_GPIO_PIN_MASK      (1U << 20U)   /*!< GPIO pin mask */

/* GPIO_AD_27 (coord N16), BT_HOST_WAKE/U16[38]/BT_WAKE_B_3V3/J54[20] */
/* Routed pin properties */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_YELLOW_LED_PERIPHERAL              GPIO9   /*!< Peripheral name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_YELLOW_LED_SIGNAL                gpio_io   /*!< Signal name */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_YELLOW_LED_CHANNEL                   26U   /*!< Signal channel */

/* Symbols to be used with GPIO driver */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_YELLOW_LED_GPIO                    GPIO9   /*!< GPIO peripheral base pointer */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_YELLOW_LED_GPIO_PIN                  26U   /*!< GPIO pin number */
#define BOARD_INITFUNCLIGHTINGGRILLPINS_YELLOW_LED_GPIO_PIN_MASK     (1U << 26U)   /*!< GPIO pin mask */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitFuncLightingGrillPins(void);   /* Function assigned for the Cortex-M7F */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
