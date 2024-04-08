#include "pin_mux.h"

#include "Includes.h"

static char McuVer[20] = "M0.001_20230628T";

static void main_init(void);

static void SystemInfo(void)
{
	uint32_t freq=CLOCK_GetFreq(kCLOCK_CpuClk);
	
	SYSINFO_PRINTF("\r\n");
	SYSINFO_PRINTF("***********************************************************\r\n");
	SYSINFO_PRINTF("***                     MIMX1170 MCU                    ***\r\n");
	SYSINFO_PRINTF("***                                                     ***\r\n");
	SYSINFO_PRINTF("*** SW Version : %s	                ***\r\n", McuVer);
	SYSINFO_PRINTF("***                                                     ***\r\n");
	SYSINFO_PRINTF("***                                                     ***\r\n");
	SYSINFO_PRINTF("*** Core Clock = %dHz                            ***\r\n", freq);
	SYSINFO_PRINTF("*** CPU wakeup source = 0x%x...                          ***\r\n", SRC->SRSR);
	SYSINFO_PRINTF("***                                                     ***\r\n");
	SYSINFO_PRINTF("***                                                     ***\r\n");
	SYSINFO_PRINTF("***********************************************************\r\n");
	SYSINFO_PRINTF("\r\n");
}

int main(void)
{
	/* Initialize board hardware. */
	BOARD_ConfigMPU();
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	main_init();

	while (1)
	{
		GlobalSequence();
		
		CanMain();
		EnetMain();
		AppMain();
		IoctrlMain();
	}
}

static void main_init(void)
{
	/* System Information */
	SystemInfo();

	/* Initialize global sequence */
	GlobalSequence_Init();

	/* Initialize softtimer */
	SoftTimerInit();

	ApplCan_InitBuf();
}
