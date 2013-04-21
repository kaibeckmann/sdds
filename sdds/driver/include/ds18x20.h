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



/**
 * Initialise the DS18X20 Temperatur sensor.
 * There is only on sensor on the system supported!
 * Method have to be called before usage
 * @retrun SDDS_RT_OK if success, FAIL if there was a problem
 */
rc_t DS18X20_init();
/**
 * Methode to start a messurement. 
 * messurement takes up to 750ms time.
 * after value can be read with @see DS18X20_read_celsius method.
 * @retrun SDDS_RT_OK on success, FAIL if there was a problem
 */
rc_t DS18X20_start_meassurement();

/**
 * Methode to read the temperature value form the sensor.
 * the @see DS18X20_start_meassurement() method have to be called 750ms before
 * @temperature Pointer to a signed 16bit variable to store the temperature in
 * @return SDDS_RT_OK on success, FAIL if there was a problem
 */
rc_t DS18X20_read_celsius(int16_t* temperature);



#endif /* DS18X20_H_ */
