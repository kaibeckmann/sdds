/*
 * TSL2561.h
 *
 *  Created on: 7 Aug 2012
 *      Author: k_beckma
 *
 *      Driver for the TSL2561 Luminosity sensor
 *      Breakout board by Adafuit
 */

#ifndef TSL2561_H_
#define TSL2561_H_

#include <sdds_types.h>

typedef enum
{
  TSL2561_GAIN_0X = 0x00, // No gain
  TSL2561_GAIN_16X = 0x10, // 16x gain
}
TSL2561_Gain_t;

typedef enum
{
  TSL2561_INTEGRATIONTIME_13MS = 0x00, // 13.7ms
  TSL2561_INTEGRATIONTIME_101MS = 0x01, // 101ms
  TSL2561_INTEGRATIONTIME_402MS = 0x02 // 402ms
}
TSL2561_IntegrationTime_t;

/**
 * Initialises the light sensor
 */
rc_t TSL2561_init(void);

rc_t TSL2561_readID(uint8_t* id);

rc_t TSL2561_setGain(TSL2561_Gain_t gain);

rc_t TSL2561_setTiming(TSL2561_IntegrationTime_t integration);

rc_t TSL2561_calculateLux(uint16_t ch0, uint16_t ch1, uint32_t* result);

rc_t TSL2561_getChannels(uint16_t* channel0, uint16_t* channel1);
#endif /* TSL2561_H_ */
