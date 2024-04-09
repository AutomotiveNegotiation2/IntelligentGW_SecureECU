#include "Includes.h"

bool bEnetLinkUp;
bool bUdpTest = FALSE;

long EnetLinkUpCnt;

#if defined (APP_UDP)
void Enet_UdpCallback(void)
{
	HAL_TIM_PeriodUdpElapsedCallback();
	ENETINFO_PRINTF("UDP Callback is called.\r\n", __func__);
}
#endif
