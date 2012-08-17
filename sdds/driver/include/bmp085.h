/*
 * bmp085.h
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma \& d_mierswa
 */

#ifndef BMP085_H_
#define BMP085_H_

#include "sdds_types.h"


/**
 * initialize the temperature and pressure sensor BMP085
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t bmp085_init(void);

/**
 * read the temperature in 0.01°C
 *
 * @param temperature the temperature if the function returns 0
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t bmp085_read_temperature(int16_t *temperature);

/**
 * read the pressure in 0.1 mbar (hPa) (which is 1 Pa)
 *
 * @param pressure the pressure if the function returns 0
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t bmp085_read_pressure(uint16_t *pressure);

#endif /* BMP085_H_ */
