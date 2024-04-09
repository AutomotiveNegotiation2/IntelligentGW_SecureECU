#ifndef _DHAUTO_IOCTRL_H_
#define	_DHAUTO_IOCTRL_H_

typedef enum {
	KEY_IN_CHECK_START=0,
	KEY_IN_CBD_USER_BTN=0,
	KEY_IN_FBD_SW01_BTN,
	KEY_IN_FBD_SW02_BTN,
	KEY_IN_FBD_SW03_BTN,
	KEY_IN_FBD_SW04_BTN,
	KEY_IN_MAX
} keyIn_inst_t;

typedef enum {
	LED_GREEN=0,
	LED_RED=1,
	LED_COLOR_MAX
} led_color_inst_t;

typedef enum {
	LED_D1=0,
	LED_D2,
	LED_D3,
	LED_D4,
	LED_D5,
	LED_NUM_MAX
} led_inst_t;

typedef bool (*ReadKeyInCallback)(void);
typedef void (*KeyFuncCallback)(void);
typedef void (*LedOpCallback)(void);

void IOCTRL_SetLedOpForTx(uint8_t inst, uint8_t attr);
void IOCTRL_SetLedOpForRx(uint8_t inst);

void IoctrlMain(void);

#endif /* _DHAUTO_IOCTRL_H_ */
