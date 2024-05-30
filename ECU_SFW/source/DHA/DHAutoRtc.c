#include "Includes.h"

#define kCLOCK_SnvsHp0		kCLOCK_SnvsHp
#define SNVS_IRQn			SNVS_HP_NON_TZ_IRQn
#define SNVS_IRQHandler		SNVS_HP_NON_TZ_IRQHandler

volatile bool busyWait;

void SNVS_IRQHandler(void)
{
    if (SNVS_HP_RTC_GetStatusFlags(SNVS) & kSNVS_RTC_AlarmInterruptFlag)
    {
        busyWait = false;

        /* Clear alarm flag */
        SNVS_HP_RTC_ClearStatusFlags(SNVS, kSNVS_RTC_AlarmInterruptFlag);
    }
    SDK_ISR_EXIT_BARRIER;
}

void InitRTC(void)
{
	snvs_hp_rtc_datetime_t rtcDate;
    snvs_hp_rtc_config_t snvsRtcConfig;

	/* Init SNVS */
    /*
     * snvsConfig->rtccalenable = false;
     * snvsConfig->rtccalvalue = 0U;
     * snvsConfig->srtccalenable = false;
     * snvsConfig->srtccalvalue = 0U;
     * snvsConfig->PIFreq = 0U;
     */
    SNVS_HP_RTC_GetDefaultConfig(&snvsRtcConfig);
    SNVS_HP_RTC_Init(SNVS, &snvsRtcConfig);

	IOCTRLINFO_PRINTF("Initialize SNVS HP RTC\r\n");

	/* Set a start date time and start RT */
    rtcDate.year   = 2023;
    rtcDate.month  = 8;
    rtcDate.day    = 31;
    rtcDate.hour   = 12;
    rtcDate.minute = 0;
    rtcDate.second = 0;

	/* Set RTC time to default time and date and start the RTC */
    SNVS_HP_RTC_SetDatetime(SNVS, &rtcDate);
    SNVS_HP_RTC_StartTimer(SNVS);

	/* Enable at the NVIC */
    EnableIRQ(SNVS_IRQn);
}

void DebugRTC(void)
{
	snvs_hp_rtc_datetime_t rtcDate;
	
	/* Get date time */
	SNVS_HP_RTC_GetDatetime(SNVS, &rtcDate);

	IOCTRLINFO_PRINTF("Current datetime: %04hd-%02hd-%02hd %02hd:%02hd:%02hd\r\n", rtcDate.year, rtcDate.month, rtcDate.day,
               rtcDate.hour, rtcDate.minute, rtcDate.second);
}

