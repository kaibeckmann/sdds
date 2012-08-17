/*
 * sht15.h
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma \& d_mierswa
 *
 */

#ifndef SHT15_H_
#define SHT15_H_

#include "sdds_types.h"

/**
 * initialize the temperature and humidity sensor SHT15
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t sht15_init(void);

/**
 * read the temperature in 0.01°C
 *
 * @param temperature the temperature if the function returns 0
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t sht15_read_temperature(int16_t *temperature);

/**
 * read relative humidity in 0.01%
 *
 * @param humidity the relative humidity if the function returns 0
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t sht15_read_relative_humidity(uint16_t *humidity);


#endif /* SHT15_H_ */
