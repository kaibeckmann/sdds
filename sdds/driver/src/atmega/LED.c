/*
 * LED.c
 *
 *  Created on: 4 Oct 2012
 *      Author: k_beckma
 */


#include "LED.h"
#include "ATMEGA_LED.h"

rc_t LED_init(LED _this) {

	if (_this == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}
	// set Direction
	_this->ddr |= _BV(_this->p);
	// set LED OFF
	LED_switchOff(_this);

#ifdef DRV_LED_DIMMING
#endif

#ifdef DRV_LED_BLINK
#endif

	return SDDS_RT_OK;
}

rc_t LED_switchOn(LED _this) {

	if (_this == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}
	if (_this->sourceing) {
		_this->port |= _BV(_this->p);
	} else {
		_this->port &= ~_BV(_this->p);
	}
	return SDDS_RT_OK;
}
rc_t LED_switchOff(LED _this) {

	if (_this == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}
	if (_this->sourceing) {
		_this->port &= ~_BV(_this->p);
	} else {
		_this->port |= _BV(_this->p);
	}
	return SDDS_RT_OK;
}
rc_t LED_toggle(LED _this) {
	if (_this == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}
	_this->port ^= _this->p;

	return SDDS_RT_OK;
}
rc_t LED_getState(LED _this, bool* state) {

	if (_this == NULL || state == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}

	if (_this->sourceing) {
		*state = (_this->port & _BV(_this->p)) ? true : false;
	} else {
		*state = (_this->port & _BV(_this->p)) ? false : true;
	}

	return SDDS_RT_OK;
}

#ifdef DRV_LED_DIMMING
rc_t LED_dim(LED _this, uint8_t setValue) {
	return SDDS_RT_OK;
}
#endif

#ifdef DRV_LED_BLINK
rc_t LED_blink(LED _this, drv_led_blink_interval interval_t, drv_led_blink_mode_t mode) {
	return SDDS_RT_OK;
}
#endif
