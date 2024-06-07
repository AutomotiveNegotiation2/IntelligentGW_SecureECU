#ifndef _DHAUTO_APP_LIGHTING_GRILL_H_
#define	_DHAUTO_APP_LIGHTING_GRILL_H_

#define	OP_LED_TURN_RIGHT	0xAA55
#define	OP_LED_TURN_LEFT	0x55AA
#define	OP_LED_REMOVE		0xEEAA
#define	OP_LED_EMERGENCY	0xAA77
#define	OP_LED_WELCOME		0x77AA


void DHADemoApp_LG_TURN_RIGHT(void);
void DHADemoApp_LG_TURN_LEFT(void);
void DHADemoApp_LG_EMERGENCY(void);
void DHADemoApp_LG_WELCOME(void);

void lightingGrill_Init(void);
void lightingGrill_OpStart(uint16_t led_op, uint16_t repTimes);
void lightingGrill_OpSeq(void);

#endif /* _DHAUTO_APP_LIGHTING_GRILL_H_ */
