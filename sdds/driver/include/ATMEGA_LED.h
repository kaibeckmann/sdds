/*
 * ATMEGA_LED.h
 *
 *  Created on: 4 Oct 2012
 *      Author: k_beckma
 */

#ifndef ATMEGA_LED_H_
#define ATMEGA_LED_H_

#include "LED.h"

#define LED_CONF_BANK_A 0
#define LED_CONF_BANK_B 1
#define LED_CONF_BANK_C 2
#define LED_CONF_BANK_D 3
#define LED_CONF_BANK_E 4
#define LED_CONF_BANK_F 5
#define LED_CONF_BANK_G 6

#define LED_CONF_PIN_0 0
#define LED_CONF_PIN_1 1
#define LED_CONF_PIN_2 2
#define LED_CONF_PIN_3 3
#define LED_CONF_PIN_4 4
#define LED_CONF_PIN_5 5
#define LED_CONF_PIN_6 6
#define LED_CONF_PIN_7 7


#define LED_CONF_DIM_MODE_FAST_PWM 0x01

#define LED_CONF_DIM_RESOLUTION_8BIT 0
#define LED_CONF_DIM_RESOLUTION_9BIT 1
#define LED_CONF_DIM_RESOLUTION_10BIT 2
#define LED_CONF_DIM_RESOLUTION_16BIT 3

struct LED_t {
	uint8_t bank 		: 4;
	uint8_t pin			: 3;  // max 8 pins
	uint8_t sourceing	: 1;  // bool
	uint8_t realpin;
#ifdef DRV_LED_DIMMING
	uint8_t mode		: 4; // 16 modes
	uint8_t resolution	: 3; // 8 modes
	uint8_t dimValue;
#endif

#ifdef DRV_LED_BLINK
#endif
};

#endif /* ATMEGA_LED_H_ */
