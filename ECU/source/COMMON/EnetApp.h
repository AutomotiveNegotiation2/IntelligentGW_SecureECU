#ifndef _ENET_APP_H_
#define	_ENET_APP_H_

#define	APP_UDP
//#define	APP_TCP

#define	ENET_100M_RESET_ENABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 0);
#define	ENET_100M_RESET_DISABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 1);

#define	ENET_100M_RESET_TIMEOUT	10U

#if BOARD_NETWORK_USE_1G_ENET_PORT
#define	ENET_1G_RESET_ENABLE	GPIO_WritePinOutput(BOARD_INITENET1GPINS_ENET_1G_RST_GPIO, BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN, 0);
#define	ENET_1G_RESET_DISABLE	GPIO_WritePinOutput(BOARD_INITENET1GPINS_ENET_1G_RST_GPIO, BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN, 1);

#define	ENET_1G_RESET_TIMEOUT	10U
#endif

/* IP address configuration. */
#define configIP_ADDR0 192
#define configIP_ADDR1 168
#define configIP_ADDR2 0
#define configIP_ADDR3 102

#if BOARD_NETWORK_USE_1G_ENET_PORT
#define configIP1G_ADDR3_1G 104
#endif

/* Netmask configuration. */
#define configNET_MASK0 255
#define configNET_MASK1 255
#define configNET_MASK2 255
#define configNET_MASK3 0

/* Gateway address configuration. */
#define configGW_ADDR0 192
#define configGW_ADDR1 168
#define configGW_ADDR2 0
#define configGW_ADDR3 254

extern bool bEnetLinkUp;
extern bool bUdpTest;
extern long EnetLinkUpCnt;

void Enet_IPADDR_Config(void);
void Enet_UdpCallback(void);
#endif /* _ENET_APP_H_ */
