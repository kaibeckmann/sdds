/*
 * LED.h
 *
 *  Created on: 4 Oct 2012
 *      Author: k_beckma
 *
 *  Driver Interface to access LEDs
 */

#ifndef LED_H_
#define LED_H_

#include "sdds_types.h"


struct LED_t;
typedef struct LED_t* LED;


rc_t LED_init(LED _this);

rc_t LED_switchOn(LED _this);
rc_t LED_switchOff(LED _this);
rc_t LED_toggle(LED _this);
rc_t LED_getState(LED _this, bool_t* state);

#ifdef DRV_LED_DIMMING
rc_t LED_dim(LED _this, uint8_t setValue);
#endif

#ifdef DRV_LED_BLINK
typedef drv_led_blink_interval_t uint8_t;
typedef drv_led_blink_mode_t uint8_t;
#define DRV_LED_BLINK_SINGLE 1
#define DRV_LED_BLINK_DOUBLEPULSE 2
rc_t LED_blink(LED _this, drv_led_blink_interval interval_t, drv_led_blink_mode_t mode);
#endif


#endif /* LED_H_ */
