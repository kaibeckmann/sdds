/*
 * AMN31112.h
 *
 *  Created on: 3 Jul 2012
 *      Author: k_beckma
 */

#ifndef AMN31112_H_
#define AMN31112_H_

#include "sdds_types.h"

/**
 * Initialises the AMN31112 PIR movement sensor
 */
rc_t AMN31112_init();

/**
 * Basic method to get the state of the PIR movement sensor
 *
 * @param movement Pointer to the result. true for movement, false for none
 * @return SDDS_RT_OK for all OK, SDDS_RT_FAIL for an error
 */
rc_t AMN31112_readMovement(bool_t* movement);


#endif /* AMN31112_H_ */
