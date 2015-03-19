/*
 * GammaCorrection.h
 *
 *  Created on: 05.03.2013
 *      Author: kai
 */

#ifndef GAMMACORRECTION_H_
#define GAMMACORRECTION_H_


#include <avr/io.h>
#include <avr/pgmspace.h>

#include "sdds_types.h"

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT
rc_t GammaCorrection_getValue8to8(uint8_t in, uint8_t* out);
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_8BIT*/

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT
rc_t GammaCorrection_getValue8to16(uint8_t in, uint16_t* out);
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_16BIT */

#ifdef DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT
rc_t GammaCorrection_getValue8to10(uint8_t in, uint16_t* out);
#endif /* DRIVER_LED_DIMMING_GAMMACORRECTION_10BIT */


#endif /* GAMMACORRECTION_H_ */
