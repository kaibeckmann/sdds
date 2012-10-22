/*
 * ATMEGA_LED.h
 *
 *  Created on: 4 Oct 2012
 *      Author: k_beckma
 */

#ifndef ATMEGA_LED_H_
#define ATMEGA_LED_H_

#include "LED.h"

typedef volatile uint8_t* reg_ptr_t;

struct LED_t {
	reg_ptr_t port;
	reg_ptr_t ddr;
	reg_ptr_t pin;
	uint8_t p;
	bool sourceing;
#ifdef DRV_LED_DIMMING
	reg_ptr_t foo;
#endif
#ifdef DRV_LED_BLINK
#endif
};

#endif /* ATMEGA_LED_H_ */
