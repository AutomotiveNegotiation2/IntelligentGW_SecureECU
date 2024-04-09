#ifndef _ENET_APP_H_
#define	_ENET_APP_H_

#define	APP_UDP
//#define	APP_TCP

#define	ENET_100M_RESET_ENABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 0);
#define	ENET_100M_RESET_DISABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 1);

#define	ENET_100M_RESET_TIMEOUT	10U

extern bool bEnetLinkUp;
extern bool bUdpTest;
extern long EnetLinkUpCnt;

void Enet_IPADDR_Config(void);
void Enet_UdpCallback(void);

#endif /* _ENET_APP_H_ */
