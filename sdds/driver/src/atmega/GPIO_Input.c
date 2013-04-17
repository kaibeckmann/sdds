/*
 * GPIO_Input.c
 *
 *  Created on: Mar 26, 2013
 *      Author: k_beckma
 */
#include "avr/io.h"
#include "avr/interrupt.h"

#include "GPIO_Input.h"

#include "sdds/sdds_types.h"
#include "sdds/Log.h"

#if 1

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


//#define GPIO_INPUT_IRQ_ENABLE_INT0
//#define GPIO_INPUT_IRQ_ENABLE_INT1
//#define GPIO_INPUT_IRQ_ENABLE_INT2
//#define GPIO_INPUT_IRQ_ENABLE_INT3
//#define GPIO_INPUT_IRQ_ENABLE_INT4
//#define GPIO_INPUT_IRQ_ENABLE_INT5
//#define GPIO_INPUT_IRQ_ENABLE_INT6
//#define GPIO_INPUT_IRQ_ENABLE_INT7


//#define GPIO_INPUT_IRQ_ENABLE_PCINT0
/*
#define GPIO_INPUT_IRQ_ENABLE_PCINT1
#define GPIO_INPUT_IRQ_ENABLE_PCINT2
#define GPIO_INPUT_IRQ_ENABLE_PCINT3
#define GPIO_INPUT_IRQ_ENABLE_PCINT4
#define GPIO_INPUT_IRQ_ENABLE_PCINT5
#define GPIO_INPUT_IRQ_ENABLE_PCINT6
#define GPIO_INPUT_IRQ_ENABLE_PCINT7
*/

#ifdef GPIO_INPUT_IRQ_ENABLE_PCINT0
GPIO_Input_CallBack_Handler handler_pcint0 = NULL;
GPIO_Input gpio_input_pcint0 = NULL;
/**
 * todo support more than one irq sources
 */
ISR(PCINT0_vect) {
	/* Interrupt Code */

	// io port has changed

	bool_t value = 0;

	//PCMSK0 &= ~_BV(PCINT0);

	if (gpio_input_pcint0 != NULL && handler_pcint0 != NULL) {
		//GPIO_Input_getState(gpio_input_pcint0, &value);
		(*handler_pcint0)(gpio_input_pcint0, value);
	}
}
#endif


#ifdef GPIO_INPUT_IRQ_ENABLE_INT0
GPIO_Input_CallBack_Handler handler_int0;
GPIO_Input gpio_input_int0;
ISR(INT0_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int0->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRA |= _BV(ISC00) | _BV(ISC01);
			levelToggle = true;
		} else {
			EICRA &= ~(_BV(ISC00) | _BV(ISC01));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int0, &value);
	(*handler_int0)(gpio_input_int0, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT1
GPIO_Input_CallBack_Handler handler_int1;
GPIO_Input gpio_input_int1;
ISR(INT1_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int1->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRA |= _BV(ISC10) | _BV(ISC11);
			levelToggle = true;
		} else {
			EICRA &= ~(_BV(ISC10) | _BV(ISC11));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int1, &value);
	(*handler_int1)(gpio_input_int1, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT2
GPIO_Input_CallBack_Handler handler_int2;
GPIO_Input gpio_input_int2;
ISR(INT2_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int2->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRA |= _BV(ISC20) | _BV(ISC21);
			levelToggle = true;
		} else {
			EICRA &= ~(_BV(ISC20) | _BV(ISC21));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int2, &value);
	(*handler_int2)(gpio_input_int2, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT3
GPIO_Input_CallBack_Handler handler_int3;
GPIO_Input gpio_input_int3;
ISR(INT3_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int3->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRA |= _BV(ISC30) | _BV(ISC31);
			levelToggle = true;
		} else {
			EICRA &= ~(_BV(ISC30) | _BV(ISC31));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int3, &value);
	(*handler_int3)(gpio_input_int3, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT4
GPIO_Input_CallBack_Handler handler_int4;
GPIO_Input gpio_input_int4;
ISR(INT4_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int4->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRB |= _BV(ISC40) | _BV(ISC41);
			levelToggle = true;
		} else {
			EICRB &= ~(_BV(ISC40) | _BV(ISC41));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int4, &value);
	(*handler_int4)(gpio_input_int4, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT5
GPIO_Input_CallBack_Handler handler_int5;
GPIO_Input gpio_input_int5;
ISR(INT5_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int5->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRB |= _BV(ISC50) | _BV(ISC51);
			levelToggle = true;
		} else {
			EICRB &= ~(_BV(ISC50) | _BV(ISC51));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int5, &value);
	(*handler_int5)(gpio_input_int5, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT6
GPIO_Input_CallBack_Handler handler_int6;
GPIO_Input gpio_input_int6;
ISR(INT6_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int6->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRB |= _BV(ISC60) | _BV(ISC61);
			levelToggle = true;
		} else {
			EICRB &= ~(_BV(ISC60) | _BV(ISC61));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int6, &value);
	(*handler_int6)(gpio_input_int6, value);
}
#endif

#ifdef GPIO_INPUT_IRQ_ENABLE_INT7
GPIO_Input_CallBack_Handler handler_int7;
GPIO_Input gpio_input_int7;
ISR(INT7_vect) {
	/* Interrupt Code */
	bool_t value;
	static bool_t levelToggle = false;

	// change detection if level trigger
	if (gpio_input_int7->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
		if (levelToggle == false) {
			EICRB |= _BV(ISC70) | _BV(ISC71);
			levelToggle = true;
		} else {
			EICRB &= ~(_BV(ISC70) | _BV(ISC71));
			levelToggle = false;
		}
	}
	GPIO_Input_getState(gpio_input_int7, &value);
	(*handler_int7)(gpio_input_int7, value);
}
#endif

rc_t GPIO_Input_init(GPIO_Input _this) {

	if (_this == NULL ) {
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

rc_t GPIO_Input_setCallback(GPIO_Input _this,
		GPIO_Input_CallBack_Handler callback) {

#ifdef __AVR_ATmega128RFA1__

	// activate interrupt

	// check if interupts are configured, if not error
	if (!(_this->mode & GPIO_INPUT_MODE_INTERUPT_ENABLE)) {
		Log_error("Callback given, but no Interupts configured\n");
		return SDDS_RT_BAD_PARAMETER;
	}

	if (_this->bank == GPIO_INPUT_ATMEGA_BANK_E && _this->pin == 4) {
		// PE4 und INT4
#ifdef GPIO_INPUT_IRQ_ENABLE_INT4
		handler_int4 = callback;
		gpio_input_int4 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if(_this->mode &
				 (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK |
				 GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRB |= _BV(ISC40);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRB |= _BV(ISC41);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRB |= _BV(ISC41) | _BV(ISC40);
		}
		// unmask interupt
		EIMSK |= _BV(INT4);

	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_E && _this->pin == 5) {
		// PE5 und INT5
#ifdef GPIO_INPUT_IRQ_ENABLE_INT5
		handler_int5 = callback;
		gpio_input_int5 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRB |= _BV(ISC50);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRB |= _BV(ISC51);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRB |= _BV(ISC51) | _BV(ISC50);
		}
		// unmask interupt
		EIMSK |= _BV(INT5);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_E && _this->pin == 6) {
		// PE6 and INT6
#ifdef GPIO_INPUT_IRQ_ENABLE_INT6
		handler_int6 = callback;
		gpio_input_int6 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRB |= _BV(ISC60);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRB |= _BV(ISC61);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRB |= _BV(ISC61) | _BV(ISC60);
		}
		// unmask interupt
		EIMSK |= _BV(INT6);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_E && _this->pin == 7) {
		// PE7 und INT7
#ifdef GPIO_INPUT_IRQ_ENABLE_INT7
		handler_int7 = callback;
		gpio_input_int7 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRB |= _BV(ISC70);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRB |= _BV(ISC71);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRB |= _BV(ISC71) | _BV(ISC70);
		}
		// unmask interupt
		EIMSK |= _BV(INT7);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_D && _this->pin == 0) {
		// PD0 and INT0
#ifdef GPIO_INPUT_IRQ_ENABLE_INT0
		handler_int0 = callback;
		gpio_input_int0 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRA |= _BV(ISC00);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRA |= _BV(ISC01);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRA |= _BV(ISC01) | _BV(ISC00);
		}
		// unmask interupt
		EIMSK |= _BV(INT0);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_D && _this->pin == 1) {
		// PD1 and INT1
#ifdef GPIO_INPUT_IRQ_ENABLE_INT1
		handler_int1 = callback;
		gpio_input_int1 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRA |= _BV(ISC10);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRA |= _BV(ISC11);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRA |= _BV(ISC11) | _BV(ISC10);
		}
		// unmask interupt
		EIMSK |= _BV(INT1);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_D && _this->pin == 2) {
		// PD2 and INT2
#ifdef GPIO_INPUT_IRQ_ENABLE_INT2
		handler_int2 = callback;
		gpio_input_int2 = _this;
#endif
		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRA |= _BV(ISC20);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRA |= _BV(ISC21);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRA |= _BV(ISC21) | _BV(ISC20);
		}
		// unmask interupt
		EIMSK |= _BV(INT2);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_D && _this->pin == 3) {
		// PD3 and INT3

#ifdef GPIO_INPUT_IRQ_ENABLE_INT3
		handler_int3 = callback;
		gpio_input_int3 = _this;
#endif

		if (_this->mode & GPIO_INPUT_MODE_CALLBACK_LEVEL_TRIGGER) {
			// do nothing in EICRx
		}
		if (_this->mode
				& (GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK
						| GPIO_INPUT_MODE_CALLBACK_RISING_FLANK)) {
			// activate both
			EICRA |= _BV(ISC30);

		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_FALLING_FLANK) {
			EICRA |= _BV(ISC31);
		} else if (_this->mode & GPIO_INPUT_MODE_CALLBACK_RISING_FLANK) {
			EICRA |= _BV(ISC31) | _BV(ISC30);
		}
		// unmask interupt
		EIMSK |= _BV(INT3);
	} else if (_this->bank == GPIO_INPUT_ATMEGA_BANK_B && _this->pin == 0) {
		// PB0 and PCINT0
		// only one irq handler for all PCINTs
#ifdef GPIO_INPUT_IRQ_ENABLE_PCINT0
		handler_pcint0 = callback;
		gpio_input_pcint0 = _this;
#endif
		// activate IRQ handling for all PCINTs
		PCICR |= _BV(PCIE0);
		// activate PCINT0 for pin PB0
		PCMSK0 |= _BV(PCINT0);
	}

#endif /* __AVR_ATmega128RFA1__*/

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

rc_t GPIO_Input_activateInterrupt(GPIO_Input _this) {

	if (_this->bank == GPIO_INPUT_ATMEGA_BANK_B && _this->pin == 0) {
		PCMSK0 |= _BV(PCINT0);
	}
	return SDDS_RT_OK;
}

rc_t GPIO_Input_deactivateInterrupt(GPIO_Input _this) {

	if (_this->bank == GPIO_INPUT_ATMEGA_BANK_B && _this->pin == 0) {
		PCMSK0 &= ~_BV(PCINT0);
	}
	return SDDS_RT_OK;
}

#endif
