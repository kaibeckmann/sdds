/*
 * ds18x20.h
 *
 *  Created on: Dec 10, 2012
 *      Author: k_beckma
 *
 *      c&p from hexabus
 *      removed stuff we dont need
 */

#ifndef DS18X20_H_
#define DS18X20_H_

#include "sdds_types.h"

// DS18x20 EERPROM support disabled(0) or enabled(1) :
#define DS18X20_EEPROMSUPPORT 1
// decicelsius functions disabled(0) or enabled(1):
#define DS18X20_DECICELSIUS 1
// max. resolution functions disabled(0) or enabled(1):
#define DS18X20_MAX_RESOLUTION 1
// extended output via UART disabled(0) or enabled(1) :
#define DS18X20_VERBOSE 1



rc_t DS18X20_init();
rc_t DS18X20_read_celsius(int16_t* temperature);


#endif /* DS18X20_H_ */
