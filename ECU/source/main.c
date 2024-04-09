#include "Includes.h"

static char McuVer[20] = "M0.001_20240118T";

void SystemInfo(void)
{
	uint32_t freq=CLOCK_GetFreq(kCLOCK_CpuClk);

	COMMON_PRINTF("\33[0m");	// normal
	COMMON_PRINTF("\r\n");
	COMMON_PRINTF("***********************************************************\r\n");
	COMMON_PRINTF("***                     MIMX1170 MCU                    ***\r\n");
	COMMON_PRINTF("***                                                     ***\r\n");
	COMMON_PRINTF("*** SW Version : %s	                ***\r\n", McuVer);
	COMMON_PRINTF("***                                                     ***\r\n");
	COMMON_PRINTF("***                                                     ***\r\n");
	COMMON_PRINTF("*** Core Clock = %dHz                            ***\r\n", freq);
	//COMMON_PRINTF("*** CPU wakeup source = 0x%x...                      ***\r\n", SRC->SRSR);
	COMMON_PRINTF("***                                                     ***\r\n");
#if ((CAN3toCAN_EN == ON) && (CAN1toCANFD_EN == ON))
	COMMON_PRINTF("*** CAN / CANFD NETWORK OPERATION                       ***\r\n");
#elif (CAN3toCAN_EN == ON) 
	COMMON_PRINTF("*** CAN NETWORK OPERATION                               ***\r\n");
#elif (CAN1toCANFD_EN == ON)
	COMMON_PRINTF("*** CANFD NETWORK OPERATION                             ***\r\n");
#endif
	COMMON_PRINTF("***                                                     ***\r\n");
	COMMON_PRINTF("***********************************************************\r\n");
	COMMON_PRINTF("\r\n");
}

int main(void)
{
	/* Initialize board hardware. */
	BOARD_ConfigMPU();
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	/* Init_****Func() : Initialize registers and variables */
	Init_AutoCryptFunc();
	Init_KorUnivFunc();
	Init_KetiFunc();
#if (DHAUTO_FUNC_EN == ON)
	Init_DHAutoFunc();
#endif

	/* Initialize general drivers */
	Init_CommonFunc();
	
	while (1)
	{
#if (DHAUTO_FUNC_EN == ON)
		SoftTimerSrv();
#endif

		CommonFunc();
		
#if (DHAUTO_FUNC_EN == ON)
		SoftTimerSrv();
#endif

		AutoCryptFunc();
		
#if (DHAUTO_FUNC_EN == ON)
		SoftTimerSrv();
#endif

		KorUnivFunc();
		
#if (DHAUTO_FUNC_EN == ON)
		SoftTimerSrv();
#endif

		KetiFunc();
		
#if (DHAUTO_FUNC_EN == ON)
		DHAutoFunc();
#endif
	}
}
