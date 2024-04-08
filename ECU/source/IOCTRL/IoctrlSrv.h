#ifndef _IOCTRLSRV_H_
#define	_IOCTRLSRV_H_

typedef enum {
	KEY_IN_CHECK_START=0,
	KEY_IN_CBD_USER_BTN=0,
	KEY_IN_FBD_SW01_BTN,
	KEY_IN_FBD_SW02_BTN,
	KEY_IN_FBD_SW03_BTN,
	KEY_IN_FBD_SW04_BTN,
	KEY_IN_MAX
} keyIn_inst_t;

typedef bool (*ReadKeyInCallback)(void);
typedef void (*KeyFuncCallback)(void);

void IoctrlSrv(void);

#endif /* _IOCTRLSRV_H_ */ 
