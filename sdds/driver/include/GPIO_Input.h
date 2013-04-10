/*
 * GPIO_Input.h
 *
 *  Created on: Mar 26, 2013
 *      Author: k_beckma
 */

#ifndef GPIO_INPUT_H_
#define GPIO_INPUT_H_

#include "sdds/sdds_types.h"

#define GPIO_INPUT_MODE_INTERUPT_ENABLE			0x01
#define GPIO_INPUT_MODE_NEGATIVE_LOGIC			0x02
#define GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER	0x04
#define GPIO_INPUT_MODE_CALLBACK_RISING_FLANK	0x08
#define GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK	0x10
#define GPIO_INPUT_MODE_PULLUP_ACTIVATE			0x20
#define GPIO_INPUT_MODE_free5					0x40
#define GPIO_INPUT_MODE_free6					0x80

#define GPIO_INPUT_ATMEGA_BANK_A 				0
#define GPIO_INPUT_ATMEGA_BANK_B 				1
#define GPIO_INPUT_ATMEGA_BANK_C 				2
#define GPIO_INPUT_ATMEGA_BANK_D 				3
#define GPIO_INPUT_ATMEGA_BANK_E 				4
#define GPIO_INPUT_ATMEGA_BANK_F 				5
#define GPIO_INPUT_ATMEGA_BANK_G 				6

struct GPIO_Input_t {
	uint8_t pin;
	uint8_t bank;
	uint8_t mode;
};

typedef struct GPIO_Input_t* GPIO_Input;


typedef void (*GPIO_Input_CallBack_Handler)( GPIO_Input _this, bool_t state);

// callback kann optional sein
rc_t GPIO_Input_init(GPIO_Input _this);

// callback is called depending on configuration
rc_t GPIO_Input_setCallback(GPIO_Input _this, GPIO_Input_CallBack_Handler callback );

rc_t GPIO_Input_activateInterrupt(GPIO_Input _this);

rc_t GPIO_Input_deactivateInterrupt(GPIO_Input _this);

rc_t GPIO_Input_getState(GPIO_Input _this, bool_t* state);


#endif /* GPIO_INPUT_H_ */
