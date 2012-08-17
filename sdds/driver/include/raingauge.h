/*
 * raingauge.h
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma \& d_mierswa
 */

#ifndef RAINGAUGE_H_
#define RAINGAUGE_H_

#include "sdds_types.h"

/**
 * initialize the raingauge
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t raingauge_init(void);

/**
 * read the current amount of rain or for the last 60 or 3600 seconds in 0.01 mm/h
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t raingauge_read_current(uint16_t *value);
rc_t raingauge_read_minute(uint16_t *value);
rc_t raingauge_read_hour(uint16_t *value);

/*
 * the passed callback needs to be called every RAINGAUGE_CALLBACK_PERIOD (see config.h)
 * to keep track of the current speed
 */
void raingauge_register_callback(void(*callback)(void));

#endif /* RAINGAUGE_H_ */
