#ifndef _ENET_APP_H_
#define	_ENET_APP_H_

//#define	APP_UDP
//#define	APP_TCP

#define	ENET_RESET_ENABLE_100M	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 0);
#define	ENET_RESET_DISABLE_100M	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 1);
#define	ENET_RESET_ENABLE_TIME		10000U	// 10ms
#define	ENET_RESET_STABLE_TIME		10000U	// 10ms

#if BOARD_NETWORK_USE_1G_ENET_PORT
#define	ENET_RESET_ENABLE_1G	GPIO_WritePinOutput(BOARD_INITENET1GPINS_ENET_1G_RST_GPIO, BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN, 0);
#define	ENET_RESET_DISABLE_1G	GPIO_WritePinOutput(BOARD_INITENET1GPINS_ENET_1G_RST_GPIO, BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN, 1);
#define	ENET_RESET_ENABLE_TIME_1G	10000U	// 10ms
#define	ENET_RESET_STABLE_TIME_1G	30000U	// 30ms
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

extern bool bUdpTest;

void Enet_IPADDR_Config(void);
void Enet_UdpCallback(void);

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet_UdpCallback_1G(void);
#endif

#endif /* _ENET_APP_H_ */
