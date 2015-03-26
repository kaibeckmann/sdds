/*
 * LED.c
 *
 *  Created on: 4 Oct 2012
 *      Author: k_beckma
 */

#include "avr/io.h"

#include "sdds/Log.h"

#include "LED.h"
#include "ATMEGA_LED.h"
#include "GammaCorrection.h"

void _switchOn(LED _this);
void _switchOff(LED _this);
#ifdef DRIVER_LED_DIMMING
void _dim(LED _this, uint8_t setValue);
#endif

rc_t LED_init(LED _this) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}

#ifdef __AVR_ATmega128RFA1__

	uint8_t mypin = 0;

	switch (_this->bank) {
	case (HAL_LED_BANK_A):
		switch (_this->pin) {
		case (HAL_LED_PIN_0):
			mypin = PA0;
			break;
		case (HAL_LED_PIN_1):
			mypin = PA1;
			break;
		case (HAL_LED_PIN_2):
			mypin = PA2;
			break;
		case (HAL_LED_PIN_3):
			mypin = PA3;
			break;
		case (HAL_LED_PIN_4):
			mypin = PA4;
			break;
		case (HAL_LED_PIN_5):
			mypin = PA5;
			break;
		case (HAL_LED_PIN_6):
			mypin = PA6;
			break;
		case (HAL_LED_PIN_7):
			mypin = PA7;
			break;
		}
		;
		DDRA |= _BV(mypin);
		_this->realpin = mypin;
		break;
	case (HAL_LED_BANK_B):

		switch (_this->pin) {
		case (HAL_LED_PIN_0):
			mypin = PB0;
			break;
		case (HAL_LED_PIN_1):
			mypin = PB1;
			break;
		case (HAL_LED_PIN_2):
			mypin = PB2;
			break;
		case (HAL_LED_PIN_3):
			mypin = PB3;
			break;
		case (HAL_LED_PIN_4):
			mypin = PB4;
			break;
		case (HAL_LED_PIN_5):
			mypin = PB5;
			break;
		case (HAL_LED_PIN_6):
			mypin = PB6;
			break;
		case (HAL_LED_PIN_7):
			mypin = PB7;
			break;
		}
		;
		DDRB |= _BV(mypin);
		break;
	case (HAL_LED_BANK_C):
		break;
	case (HAL_LED_BANK_D):
		switch (_this->pin) {
		case (HAL_LED_PIN_0):
			mypin = PD0;
			break;
		case (HAL_LED_PIN_1):
			mypin = PD1;
			break;
		case (HAL_LED_PIN_2):
			mypin = PD2;
			break;
		case (HAL_LED_PIN_3):
			mypin = PD3;
			break;
		case (HAL_LED_PIN_4):
			mypin = PD4;
			break;
		case (HAL_LED_PIN_5):
			mypin = PD5;
			break;
		case (HAL_LED_PIN_6):
			mypin = PD6;
			break;
		case (HAL_LED_PIN_7):
			mypin = PD7;
			break;
		}
		;
		DDRD |= _BV(mypin);
		break;

	case (HAL_LED_BANK_E):
		break;
	case (HAL_LED_BANK_F):
		break;
	case (HAL_LED_BANK_G):
		break;
	};

	_this->realpin = mypin;

#endif

	LED_switchOff(_this);

#ifdef DRIVER_LED_DIMMING

	if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_5 && (_this->mode & HAL_LED_DIM_ACTIVATE)) {
		Log_debug("Conf B5 for dimming\n");
		// timer 1
		TCCR1A |= _BV(COM1A1);
		if (_this->sourceing == false) {
			// inverse
			TCCR1A |= _BV(COM1A0);
		}
		if (_this->resolution == HAL_LED_DIM_RESOLUTION_10BIT) {
			TCCR1A |= _BV(WGM11) | _BV(WGM10);
			TCCR1B |= _BV(WGM12) |
			_BV(CS11); // 8mhz / 10bit (1024) / prescaler 8 = ~976 herz pwm frequenz
		}

		TCCR1C |= 0;

	} else if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_6 && (_this->mode & HAL_LED_DIM_ACTIVATE)) {
		// timer 1
		TCCR1A |= _BV(COM1B1);
		if (_this->sourceing == false) {
			// inverse
			TCCR1A |= _BV(COM1B0);
		}
		if (_this->resolution == HAL_LED_DIM_RESOLUTION_10BIT) {
			TCCR1A |= _BV(WGM11) | _BV(WGM10);
			TCCR1B |= _BV(WGM12) |
			_BV(CS11); // 8mhz / 10bit (1024) / prescaler 8 = ~976 herz pwm frequenz
		}

		TCCR1C |= 0;

	} else if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_7 && (_this->mode & HAL_LED_DIM_ACTIVATE)) {
		// timer 1
		TCCR1A |= _BV(COM1C1);
		if (_this->sourceing == false) {
			// inverse
			TCCR1A |= _BV(COM1C0);
		}

		if (_this->resolution == HAL_LED_DIM_RESOLUTION_10BIT) {
			TCCR1A |= _BV(WGM11) | _BV(WGM10);
			TCCR1B |= _BV(WGM12) |
			_BV(CS11); // 8mhz / 10bit (1024) / prescaler 8 = ~976 herz pwm frequenz
		}

		TCCR1C |= 0;
	} else if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_4 && (_this->mode & HAL_LED_DIM_ACTIVATE)) {
		// timer 2 achtung wird benötigt wenn der uC schlafen soll!
		TCCR2A |= _BV(COM2A1);
		if (_this->sourceing == false) {
			// inverse
			TCCR2A |= _BV(COM2A0);
		}
		if (_this->resolution == HAL_LED_DIM_RESOLUTION_8BIT) {
			TCCR2A |= _BV(WGM21) | _BV(WGM20);
			TCCR2B |= 	_BV(CS22); // 8mhz / 8bit (255) / prescaler 64 = ~490 herz pwm frequenz
		}

	}

#endif

#ifdef DRIVER_LED_BLINK
#endif

	return SDDS_RT_OK;
}

void _switchOn(LED _this) {

	if (_this->sourceing) {
			//PORTB |= _BV(PB7);
			switch (_this->bank) {
			case (HAL_LED_BANK_A):
				PORTA |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_B):
				PORTB |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_C):
				PORTC |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_D):
				PORTD |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_E):
				PORTE |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_F):
				PORTF |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_G):
				PORTG |= _BV(_this->realpin);
				break;
			};
		} else {
			switch (_this->bank) {
			case (HAL_LED_BANK_A):
				PORTA &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_B):
				PORTB &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_C):
				PORTC &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_D):
				PORTD &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_E):
				PORTE &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_F):
				PORTF &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_G):
				PORTG &= ~_BV(_this->realpin);
				break;
			};
		}
}

rc_t LED_switchOn(LED _this) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	Log_debug("Lamp %x \n", _this->pin);

	_switchOn(_this);

#ifdef DRIVER_LED_DIMMING
	if (_this->dimValue > 0 ){
		_dim(_this, _this->dimValue);
	}
#endif
	return SDDS_RT_OK;
}

void _switchOff(LED _this) {
	if (_this->sourceing) {
			switch (_this->bank) {
			case (HAL_LED_BANK_A):
				PORTA &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_B):
				PORTB &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_C):
				PORTC &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_D):
				PORTD &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_E):
				PORTE &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_F):
				PORTF &= ~_BV(_this->realpin);
				break;
			case (HAL_LED_BANK_G):
				PORTG &= ~_BV(_this->realpin);
				break;
			};
		} else {
			switch (_this->bank) {
			case (HAL_LED_BANK_A):
				PORTA |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_B):
				PORTB |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_C):
				PORTC |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_D):
				PORTD |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_E):
				PORTE |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_F):
				PORTF |= _BV(_this->realpin);
				break;
			case (HAL_LED_BANK_G):
				PORTG |= _BV(_this->realpin);
				break;
			};
		}
}


rc_t LED_switchOff(LED _this) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	Log_debug("Lamp %x \n", _this->pin);

	_switchOff(_this);


#ifdef DRIVER_LED_DIMMING
	if (_this->dimValue > 0) {
		_dim(_this, 0);
	}
#endif
	return SDDS_RT_OK;
}
rc_t LED_toggle(LED _this) {
	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	switch (_this->bank) {
	case (HAL_LED_BANK_A):
		PORTA ^= _BV(_this->realpin);
		break;
	case (HAL_LED_BANK_B):
		PORTB ^= _BV(_this->realpin);
		break;
	case (HAL_LED_BANK_C):
		PORTC ^= _BV(_this->realpin);
		break;
	case (HAL_LED_BANK_D):
		PORTD ^= _BV(_this->realpin);
		break;
	case (HAL_LED_BANK_E):
		PORTE ^= _BV(_this->realpin);
		break;
	case (HAL_LED_BANK_F):
		PORTF ^= _BV(_this->realpin);
		break;
	case (HAL_LED_BANK_G):
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
		case (HAL_LED_BANK_A):
			*state = (PORTA & _BV(_this->realpin)) ? true : false;
			break;
		case (HAL_LED_BANK_B):
			*state = (PORTB & _BV(_this->realpin)) ? true : false;
			break;
		case (HAL_LED_BANK_C):
			*state = (PORTC & _BV(_this->realpin)) ? true : false;
			break;
		case (HAL_LED_BANK_D):
			*state = (PORTD & _BV(_this->realpin)) ? true : false;
			break;
		case (HAL_LED_BANK_E):
			*state = (PORTE & _BV(_this->realpin)) ? true : false;
			break;
		case (HAL_LED_BANK_F):
			*state = (PORTF & _BV(_this->realpin)) ? true : false;
			break;
		case (HAL_LED_BANK_G):
			*state = (PORTG & _BV(_this->realpin)) ? true : false;
			break;
		};
	} else {
		switch (_this->bank) {
		case (HAL_LED_BANK_A):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (HAL_LED_BANK_B):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (HAL_LED_BANK_C):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (HAL_LED_BANK_D):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (HAL_LED_BANK_E):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (HAL_LED_BANK_F):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		case (HAL_LED_BANK_G):
			*state = (PORTA & _BV(_this->realpin)) ? false : true;

			break;
		};
	}

	return SDDS_RT_OK;
}

#ifdef DRIVER_LED_DIMMING
void _dim(LED _this, uint8_t setValue) {

#if defined (DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT)
	uint16_t val;
	GammaCorrection_getValue8to16(setValue, &val);
#elif defined (DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT)
	uint8_t val;
	GammaCorrection_getValue8to8(setValue, &val);
#elif defined (DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT)
	uint16_t val;
	GammaCorrection_getValue8to10(setValue, &val);
#else
	uint8_t val;
	val = setValue;
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT */


	// check if dimm value is 0, deactivate the port
	if (setValue > 0) {
		_switchOn(_this);
	} else {
		_switchOff(_this);
	}


	if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_5) {
		// timer 1
		OCR1A = (uint16_t) val;
	} else if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_6) {
		// timer 1
		OCR1B = val;
	} else if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_7) {
		// timer 1
		OCR1C = val;
	} else if (_this->bank == HAL_LED_BANK_B && _this->pin == HAL_LED_PIN_4) {
		// timer 2
		OCR2A = val;
	}
}
rc_t LED_dim(LED _this, uint8_t setValue) {

	if (_this == NULL ) {
		return SDDS_RT_BAD_PARAMETER;
	}
	Log_debug("New Value %u\n", setValue);
	_this->dimValue = setValue;


	_dim(_this, setValue);

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

#ifdef DRIVER_LED_BLINK
rc_t LED_blink(LED _this, drv_led_blink_interval interval_t, drv_led_blink_mode_t mode) {
	return SDDS_RT_OK;
}
#endif

