/*
 * LED.c
 *
 *  Created on: 4 Oct 2012
 *      Author: k_beckma
 */

#include "avr/io.h"

#include "LED.h"
#include "ATMEGA_LED.h"
#include "GammaCorrection.h"

rc_t LED_init(LED _this) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}

#ifdef __AVR_ATmega128RFA1__

	uint8_t mypin;

	switch (_this->bank) {
	case (LED_CONF_BANK_A):
		switch (_this->pin) {
		case (LED_CONF_PIN_0):
			mypin = PA0;
			break;
		case (LED_CONF_PIN_1):
			mypin = PA1;
			break;
		case (LED_CONF_PIN_2):
			mypin = PA2;
			break;
		case (LED_CONF_PIN_3):
			mypin = PA3;
			break;
		case (LED_CONF_PIN_4):
			mypin = PA4;
			break;
		case (LED_CONF_PIN_5):
			mypin = PA5;
			break;
		case (LED_CONF_PIN_6):
			mypin = PA6;
			break;
		case (LED_CONF_PIN_7):
			mypin = PA7;
			break;
		}
		;
		DDRA |= mypin;
		_this->realpin = mypin;
		break;
	case (LED_CONF_BANK_B):

		switch (_this->pin) {
		case (LED_CONF_PIN_0):
			mypin = PB0;
			break;
		case (LED_CONF_PIN_1):
			mypin = PB1;
			break;
		case (LED_CONF_PIN_2):
			mypin = PB2;
			break;
		case (LED_CONF_PIN_3):
			mypin = PB3;
			break;
		case (LED_CONF_PIN_4):
			mypin = PB4;
			break;
		case (LED_CONF_PIN_5):
			mypin = PB5;
			break;
		case (LED_CONF_PIN_6):
			mypin = PB6;
			break;
		case (LED_CONF_PIN_7):
			mypin = PB7;
			break;
		}
		;
		DDRB |= mypin;
		break;
	case (LED_CONF_BANK_C):
		break;
	case (LED_CONF_BANK_D):
		switch (_this->pin) {
		case (LED_CONF_PIN_0):
			mypin = PD0;
			break;
		case (LED_CONF_PIN_1):
			mypin = PD1;
			break;
		case (LED_CONF_PIN_2):
			mypin = PD2;
			break;
		case (LED_CONF_PIN_3):
			mypin = PD3;
			break;
		case (LED_CONF_PIN_4):
			mypin = PD4;
			break;
		case (LED_CONF_PIN_5):
			mypin = PD5;
			break;
		case (LED_CONF_PIN_6):
			mypin = PD6;
			break;
		case (LED_CONF_PIN_7):
			mypin = PD7;
			break;
		}
		;
		DDRD |= mypin;
		break;

	case (LED_CONF_BANK_E):
		break;
	case (LED_CONF_BANK_F):
		break;
	case (LED_CONF_BANK_G):
		break;
	};

	_this->realpin = mypin;

#endif

	LED_switchOff(_this);

#ifdef DRV_LED_DIMMING

	if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_5) {
		// timer 1
		TCCR1A |= _BV(COM1A1);
		if (_this->sourceing == true) {
			// inverse
			TCCR1A |= _BV(COM1A0);
		}
		if (_this->resolution == LED_CONF_DIM_RESOLUTION_10BIT) {
			TCCR1A |= _BV(WGM11) | _BV(WGM10);
			TCCR1B |= _BV(WGM12) |
			_BV(CS11); // 8mhz / 10bit (1024) / prescaler 8 = ~976 herz pwm frequenz
		}

		TCCR1C |= 0;

	} else if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_6) {
		// timer 1
		TCCR1A |= _BV(COM1B1);
		if (_this->sourceing == true) {
			// inverse
			TCCR1A |= _BV(COM1B0);
		}
		if (_this->resolution == LED_CONF_DIM_RESOLUTION_10BIT) {
			TCCR1A |= _BV(WGM11) | _BV(WGM10);
			TCCR1B |= _BV(WGM12) |
			_BV(CS11); // 8mhz / 10bit (1024) / prescaler 8 = ~976 herz pwm frequenz
		}

		TCCR1C |= 0;

	} else if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_7) {
		// timer 1
		TCCR1A |= _BV(COM1C1);
		if (_this->sourceing == true) {
			// inverse
			TCCR1A |= _BV(COM1C0);
		}

		if (_this->resolution == LED_CONF_DIM_RESOLUTION_10BIT) {
			TCCR1A |= _BV(WGM11) | _BV(WGM10);
			TCCR1B |= _BV(WGM12) |
			_BV(CS11); // 8mhz / 10bit (1024) / prescaler 8 = ~976 herz pwm frequenz
		}

		TCCR1C |= 0;
	} else if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_4) {
		// timer 2 achtung wird benötigt wenn der uC schlafen soll!
		TCCR2A |= _BV(COM2A1);
		if (_this->sourceing == true) {
			// inverse
			TCCR2A |= _BV(COM2A0);
		}
		if (_this->resolution == LED_CONF_DIM_RESOLUTION_8BIT) {
			TCCR2A |= _BV(WGM21) | _BV(WGM20);
			TCCR2B |= 	_BV(CS22); // 8mhz / 8bit (255) / prescaler 64 = ~490 herz pwm frequenz
		}

	}

#endif

#ifdef DRV_LED_BLINK
#endif

	return SDDS_RT_OK;
}

rc_t LED_switchOn(LED _this) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	if (_this->sourceing) {
		//PORTB |= _BV(PB7);
		switch (_this->bank) {
		case (LED_CONF_BANK_A):
			PORTA |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_B):
			PORTB |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_C):
			PORTC |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_D):
			PORTD |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_E):
			PORTE |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_F):
			PORTF |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_G):
			PORTG |= _BV(_this->realpin);
			break;
		};
	} else {
		switch (_this->bank) {
		case (LED_CONF_BANK_A):
			PORTA &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_B):
			PORTB &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_C):
			PORTC &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_D):
			PORTD &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_E):
			PORTE &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_F):
			PORTF &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_G):
			PORTG &= ~_BV(_this->realpin);
			break;
		};
	}
	return SDDS_RT_OK;
}
rc_t LED_switchOff(LED _this) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	if (_this->sourceing) {
		switch (_this->bank) {
		case (LED_CONF_BANK_A):
			PORTA &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_B):
			PORTB &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_C):
			PORTC &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_D):
			PORTD &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_E):
			PORTE &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_F):
			PORTF &= ~_BV(_this->realpin);
			break;
		case (LED_CONF_BANK_G):
			PORTG &= ~_BV(_this->realpin);
			break;
		};
	} else {
		switch (_this->bank) {
		case (LED_CONF_BANK_A):
			PORTA |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_B):
			PORTB |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_C):
			PORTC |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_D):
			PORTD |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_E):
			PORTE |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_F):
			PORTF |= _BV(_this->realpin);
			break;
		case (LED_CONF_BANK_G):
			PORTG |= _BV(_this->realpin);
			break;
		};
	}
	return SDDS_RT_OK;
}
rc_t LED_toggle(LED _this) {
	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	switch (_this->bank) {
	case (LED_CONF_BANK_A):
		PORTA ^= _BV(_this->realpin);
		break;
	case (LED_CONF_BANK_B):
		PORTB ^= _BV(_this->realpin);
		break;
	case (LED_CONF_BANK_C):
		PORTC ^= _BV(_this->realpin);
		break;
	case (LED_CONF_BANK_D):
		PORTD ^= _BV(_this->realpin);
		break;
	case (LED_CONF_BANK_E):
		PORTE ^= _BV(_this->realpin);
		break;
	case (LED_CONF_BANK_F):
		PORTF ^= _BV(_this->realpin);
		break;
	case (LED_CONF_BANK_G):
		PORTG ^= _BV(_this->realpin);
		break;
	};

	return SDDS_RT_OK;
}
rc_t LED_getState(LED _this, bool_t* state) {

	if (_this == NULL || state == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}

	if (_this->sourceing) {
		switch (_this->bank) {
		case (LED_CONF_BANK_A):
			*state = (PORTA & _BV(_this->realpin)) ? true : false;
			break;
		case (LED_CONF_BANK_B):
			*state = (PORTB & _BV(_this->realpin)) ? true : false;
			break;
		case (LED_CONF_BANK_C):
			*state = (PORTC & _BV(_this->realpin)) ? true : false;
			break;
		case (LED_CONF_BANK_D):
			*state = (PORTD & _BV(_this->realpin)) ? true : false;
			break;
		case (LED_CONF_BANK_E):
			*state = (PORTE & _BV(_this->realpin)) ? true : false;
			break;
		case (LED_CONF_BANK_F):
			*state = (PORTF & _BV(_this->realpin)) ? true : false;
			break;
		case (LED_CONF_BANK_G):
			*state = (PORTG & _BV(_this->realpin)) ? true : false;
			break;
		};
	} else {
		switch (_this->bank) {
		case (LED_CONF_BANK_A):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (LED_CONF_BANK_B):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (LED_CONF_BANK_C):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (LED_CONF_BANK_D):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (LED_CONF_BANK_E):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (LED_CONF_BANK_F):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (LED_CONF_BANK_G):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		};
	}

	return SDDS_RT_OK;
}

#ifdef DRV_LED_DIMMING
rc_t LED_dim(LED _this, uint8_t setValue) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	_this->dimValue = setValue;

#if defined (DRV_LED_DIMMING_GAMMACORRECTION_16BIT)
	uint16_t val;
	GammaCorrection_getValue8to16(setValue, &val);
#elif defined (DRV_LED_DIMMING_GAMMACORRECTION_8BIT)
	uint8_t val;
	GammaCorrection_getValue8to8(setValue, &val);
#elif defined (DRV_LED_DIMMING_GAMMACORRECTION_10BIT)
	uint16_t val;
	GammaCorrection_getValue8to10(setValue, &val);
#else
	uint8_t val;
	val = setValue;
#endif /* DRV_LED_DIMMING_GAMMACORRECTION_16BIT */


	// check if dimm value is 0, deactivate the port
	if (setValue > 0) {
		LED_switchOn(_this);
	} else {
		LED_switchOff(_this);
	}


	if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_5) {
		// timer 1
		OCR1A = val;
	} else if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_6) {
		// timer 1
		OCR1B = val;
	} else if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_7) {
		// timer 1
		OCR1C = val;
	} else if (_this->bank == LED_CONF_BANK_B && _this->pin == LED_CONF_PIN_4) {
		// timer 2
		OCR2A = val;
	}

	return SDDS_RT_OK;
}

rc_t LED_getDimValue(LED _this, uint8_t* value)  {
	if (_this == NULL || value == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}

	*value = _this->dimValue;

	return SDDS_RT_OK;
}

#endif

#ifdef DRV_LED_BLINK
rc_t LED_blink(LED _this, drv_led_blink_interval interval_t, drv_led_blink_mode_t mode) {
	return SDDS_RT_OK;
}
#endif

