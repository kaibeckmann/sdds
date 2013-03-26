/*
 * GPIO_Input.c
 *
 *  Created on: Mar 26, 2013
 *      Author: k_beckma
 */
#include "avr/io.h"

#include "GPIO_Input.h"

#include "sdds/sdds_types.h"

/*
#define GPIO_INPUT_MODE_INTERUPT_ENABLE			0x01
#define GPIO_INPUT_MODE_NEGATIVE_LOGIC			0x02
#define GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER	0x04
#define GPIO_INPUT_MODE_CALLBACK_RISING_FLANK	0x08
#define GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK	0x10
#define GPIO_INPUT_MODE_free4					0x20
#define GPIO_INPUT_MODE_free5					0x40
#define GPIO_INPUT_MODE_free6					0x80
 */

rc_t GPIO_Input_init(GPIO_Input _this) {

	if (_this == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}
#ifdef __AVR_ATmega128RFA1__

	// set as input
	switch (_this->bank) {
	case (GPIO_INPUT_ATMEGA_BANK_A):
		// as input
		DDRA &= ~_BV(_this->pin);
		break;
	case (GPIO_INPUT_ATMEGA_BANK_B):
		// as input
		DDRB &= ~_BV(_this->pin);
		break;
	case (GPIO_INPUT_ATMEGA_BANK_C):
		// as input
		DDRC &= ~_BV(_this->pin);
		break;
	case (GPIO_INPUT_ATMEGA_BANK_D):
		// as input
		DDRD &= ~_BV(_this->pin);
		break;
	case (GPIO_INPUT_ATMEGA_BANK_E):
		// as input
		DDRE &= ~_BV(_this->pin);
		break;
	case (GPIO_INPUT_ATMEGA_BANK_F):
		// as input
		DDRF &= ~_BV(_this->pin);
		break;
	case (GPIO_INPUT_ATMEGA_BANK_G):
		// as input
		DDRG &= ~_BV(_this->pin);
		break;
	};

	// activate pull up

	if (_this->mode & GPIO_INPUT_MODE_PULLUP_ACTIVATE) {

		// activate pull up
		switch (_this->bank) {
		case (GPIO_INPUT_ATMEGA_BANK_A):
			PORTA |= _BV(_this->pin);
			break;
		case (GPIO_INPUT_ATMEGA_BANK_B):
			PORTB |= _BV(_this->pin);
			break;
		case (GPIO_INPUT_ATMEGA_BANK_C):
			PORTC |= _BV(_this->pin);
			break;
		case (GPIO_INPUT_ATMEGA_BANK_D):
			PORTD |= _BV(_this->pin);
			break;
		case (GPIO_INPUT_ATMEGA_BANK_E):
			PORTE |= _BV(_this->pin);
			break;
		case (GPIO_INPUT_ATMEGA_BANK_F):
			PORTF |= _BV(_this->pin);
			break;
		case (GPIO_INPUT_ATMEGA_BANK_G):
			PORTG |= _BV(_this->pin);
			break;
		};
	}



#endif
	return SDDS_RT_OK;
}

rc_t GPIO_Input_setCallback(GPIO_Input _this, GPIO_Input_CallBack_Handler callback ) {

#ifdef __AVR_ATmega128RFA1__

	// activate interrupt

#endif
	return SDDS_RT_OK;
}
rc_t GPIO_Input_getState(GPIO_Input _this, bool_t* state) {

#ifdef __AVR_ATmega128RFA1__
// PINB register
    // set as input
	switch (_this->bank) {
	case (GPIO_INPUT_ATMEGA_BANK_A):
		*state = (PINA & _BV(_this->pin)) ? 1 : 0;
		break;
	case (GPIO_INPUT_ATMEGA_BANK_B):
		*state = (PINB & _BV(_this->pin)) ? 1 : 0;
		break;
	case (GPIO_INPUT_ATMEGA_BANK_C):
		*state = (PINC & _BV(_this->pin)) ? 1 : 0;
		break;
	case (GPIO_INPUT_ATMEGA_BANK_D):
		*state = (PIND & _BV(_this->pin)) ? 1 : 0;
		break;
	case (GPIO_INPUT_ATMEGA_BANK_E):
		*state = (PINE & _BV(_this->pin)) ? 1 : 0;
		break;
	case (GPIO_INPUT_ATMEGA_BANK_F):
		*state = (PINF & _BV(_this->pin)) ? 1 : 0;
		break;
	case (GPIO_INPUT_ATMEGA_BANK_G):
		*state = (PING & _BV(_this->pin)) ? 1 : 0;
		break;
	};

	if (_this->mode & GPIO_INPUT_MODE_NEGATIVE_LOGIC) {
		if (*state == 1) {
			*state = 0;
		} else {
			*state = 1;
		}
	}


#endif
	return SDDS_RT_OK;
}
