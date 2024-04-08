#ifndef _ELMOS_LED_H
#define _ELMOS_LED_H

#define	OP_LED_TURN_RIGHT	0xAA55
#define	OP_LED_TURN_LEFT	0x55AA
#define	OP_LED_REMOVE		0xEEAA
#define	OP_LED_EMERGENCY	0xAA77
#define	OP_LED_WELCOME		0x77AA

void lightingGrill_Init(void);
void lightingGrill_OpStart(uint16_t led_op, uint16_t repTimes);
void lightingGrill_OpSeq(void);
void turn_right_sig(void);
void remove_sig(void);
#if 0
uint8_t led_disp_data(uint8_t led_pos, uint8_t mem_addr, uint8_t dev_addr, uint8_t num_words, uint16_t data);
#endif
#endif /* _ELMOS_LED_H */