/*
 * AMN31112.c
 *
 *  Created on: 3 Jul 2012
 *      Author: k_beckma
 */


#include "AMN31112.h"
#include "driver.h"

#include <avr/io.h>

#define AMN31112_DDR INTERNAL_CONCAT(DDR, AMN31112_PORT)
#define AMN31112_PORTR INTERNAL_CONCAT(PORT, AMN31112_PORT)
#define AMN31112_PORTVAL INTERNAL_CONCAT(P, INTERNAL_CONCAT(AMN31112_PORT, AMN31112_PIN))
#define AMN31112_PINR INTERNAL_CONCAT(PIN, AMN31112_PORT)


rc_t AMN31112_init() {

	// set direction to input
	AMN31112_DDR &= ~_BV(AMN31112_PORTVAL);
	// deactivate pull up
	AMN31112_PORTR &= ~_BV(AMN31112_PORTVAL);

	return SDDS_RT_OK;
}

rc_t AMN31112_readMovement(bool_t* movement) {

	if (movement == NULL) {
		return SDDS_RT_BAD_PARAMETER;
	}

	*movement = (AMN31112_PINR & _BV(AMN31112_PORTVAL));

	return SDDS_RT_OK;
}
