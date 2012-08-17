/*
 * wind_vane.h
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma \& d_mierswa
 */

#ifndef WIND_VANE_H_
#define WIND_VANE_H_

#include "sdds_types.h"

/*
 * initialize the wind vane sensor
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t wind_vane_init(void);

/*
 * read the current position multiplier
 *
 * the wind vane has 16 possible positions, i.e. the value
 * that is read is between 0 and 15, multiply this with 22.5
 * and you have the final position in degrees
 *
 * @param value the current position multiplier [0,16)
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t wind_vane_read(uint8_t *value);

#endif /* WIND_VANE_H_ */
