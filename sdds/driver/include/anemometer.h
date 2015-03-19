/*
 * anemometer.h
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma \& d_mierswa
 */

#ifndef ANEMOMETER_H_
#define ANEMOMETER_H_

#include "sdds_types.h"

/**
 * initialize the anemometer
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t anemometer_init(void);

/**
 * read the current wind speed or for the last 60 or 3600 seconds in 0.01 km/h
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t anemometer_read_current(uint16_t *value);
rc_t anemometer_read_minute(uint16_t *value);
rc_t anemometer_read_hour(uint16_t *value);

/*
 * the passed callback needs to be called every DRIVER_ANEMOMETER_CALLBACK_PERIOD (see config.h)
 * to keep track of the current speed
 */
void anemometer_register_callback(void(*callback)(void));

#endif /* ANEMOMETER_H_ */
