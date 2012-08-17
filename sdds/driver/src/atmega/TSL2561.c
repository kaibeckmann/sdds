/*
 * TSL2561.c
 *
 *  Created on: 7 Aug 2012
 *      Author: k_beckma
 *
 *      c&p from https://github.com/adafruit/TSL2561-Arduino-Library/blob/master/TSL2561.h
 */


#include "TSL2561.h"
#include "sdds_types.h"



#include "twi.h"

#include "driver.h"
#include "Log.h"


#define TSL2561_VISIBLE 2 // channel 0 - channel 1
#define TSL2561_INFRARED 1 // channel 1
#define TSL2561_FULLSPECTRUM 0 // channel 0

// 3 i2c address options!
#define TSL2561_ADDR_LOW 0x29
#define TSL2561_ADDR_FLOAT 0x39
#define TSL2561_ADDR_HIGH 0x49

// Lux calculations differ slightly for CS package
//#define TSL2561_PACKAGE_CS
#define TSL2561_PACKAGE_T_FN_CL

#define TSL2561_READBIT (0x01)

#define TSL2561_COMMAND_BIT (0x80) // Must be 1
#define TSL2561_CLEAR_BIT (0x40) // Clears any pending interrupt (write 1 to clear)
#define TSL2561_WORD_BIT (0x20) // 1 = read/write word (rather than byte)
#define TSL2561_BLOCK_BIT (0x10) // 1 = using block read/write

#define TSL2561_CONTROL_POWERON (0x03)
#define TSL2561_CONTROL_POWEROFF (0x00)

#define TSL2561_LUX_LUXSCALE (14) // Scale by 2^14
#define TSL2561_LUX_RATIOSCALE (9) // Scale ratio by 2^9
#define TSL2561_LUX_CHSCALE (10) // Scale channel values by 2^10
#define TSL2561_LUX_CHSCALE_TINT0 (0x7517) // 322/11 * 2^TSL2561_LUX_CHSCALE
#define TSL2561_LUX_CHSCALE_TINT1 (0x0FE7) // 322/81 * 2^TSL2561_LUX_CHSCALE

// T, FN and CL package values
#define TSL2561_LUX_K1T (0x0040) // 0.125 * 2^RATIO_SCALE
#define TSL2561_LUX_B1T (0x01f2) // 0.0304 * 2^LUX_SCALE
#define TSL2561_LUX_M1T (0x01be) // 0.0272 * 2^LUX_SCALE
#define TSL2561_LUX_K2T (0x0080) // 0.250 * 2^RATIO_SCALE
#define TSL2561_LUX_B2T (0x0214) // 0.0325 * 2^LUX_SCALE
#define TSL2561_LUX_M2T (0x02d1) // 0.0440 * 2^LUX_SCALE
#define TSL2561_LUX_K3T (0x00c0) // 0.375 * 2^RATIO_SCALE
#define TSL2561_LUX_B3T (0x023f) // 0.0351 * 2^LUX_SCALE
#define TSL2561_LUX_M3T (0x037b) // 0.0544 * 2^LUX_SCALE
#define TSL2561_LUX_K4T (0x0100) // 0.50 * 2^RATIO_SCALE
#define TSL2561_LUX_B4T (0x0270) // 0.0381 * 2^LUX_SCALE
#define TSL2561_LUX_M4T (0x03fe) // 0.0624 * 2^LUX_SCALE
#define TSL2561_LUX_K5T (0x0138) // 0.61 * 2^RATIO_SCALE
#define TSL2561_LUX_B5T (0x016f) // 0.0224 * 2^LUX_SCALE
#define TSL2561_LUX_M5T (0x01fc) // 0.0310 * 2^LUX_SCALE
#define TSL2561_LUX_K6T (0x019a) // 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6T (0x00d2) // 0.0128 * 2^LUX_SCALE
#define TSL2561_LUX_M6T (0x00fb) // 0.0153 * 2^LUX_SCALE
#define TSL2561_LUX_K7T (0x029a) // 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7T (0x0018) // 0.00146 * 2^LUX_SCALE
#define TSL2561_LUX_M7T (0x0012) // 0.00112 * 2^LUX_SCALE
#define TSL2561_LUX_K8T (0x029a) // 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8T (0x0000) // 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8T (0x0000) // 0.000 * 2^LUX_SCALE

// CS package values
#define TSL2561_LUX_K1C (0x0043) // 0.130 * 2^RATIO_SCALE
#define TSL2561_LUX_B1C (0x0204) // 0.0315 * 2^LUX_SCALE
#define TSL2561_LUX_M1C (0x01ad) // 0.0262 * 2^LUX_SCALE
#define TSL2561_LUX_K2C (0x0085) // 0.260 * 2^RATIO_SCALE
#define TSL2561_LUX_B2C (0x0228) // 0.0337 * 2^LUX_SCALE
#define TSL2561_LUX_M2C (0x02c1) // 0.0430 * 2^LUX_SCALE
#define TSL2561_LUX_K3C (0x00c8) // 0.390 * 2^RATIO_SCALE
#define TSL2561_LUX_B3C (0x0253) // 0.0363 * 2^LUX_SCALE
#define TSL2561_LUX_M3C (0x0363) // 0.0529 * 2^LUX_SCALE
#define TSL2561_LUX_K4C (0x010a) // 0.520 * 2^RATIO_SCALE
#define TSL2561_LUX_B4C (0x0282) // 0.0392 * 2^LUX_SCALE
#define TSL2561_LUX_M4C (0x03df) // 0.0605 * 2^LUX_SCALE
#define TSL2561_LUX_K5C (0x014d) // 0.65 * 2^RATIO_SCALE
#define TSL2561_LUX_B5C (0x0177) // 0.0229 * 2^LUX_SCALE
#define TSL2561_LUX_M5C (0x01dd) // 0.0291 * 2^LUX_SCALE
#define TSL2561_LUX_K6C (0x019a) // 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6C (0x0101) // 0.0157 * 2^LUX_SCALE
#define TSL2561_LUX_M6C (0x0127) // 0.0180 * 2^LUX_SCALE
#define TSL2561_LUX_K7C (0x029a) // 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7C (0x0037) // 0.00338 * 2^LUX_SCALE
#define TSL2561_LUX_M7C (0x002b) // 0.00260 * 2^LUX_SCALE
#define TSL2561_LUX_K8C (0x029a) // 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8C (0x0000) // 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8C (0x0000) // 0.000 * 2^LUX_SCALE

enum
{
  TSL2561_REGISTER_CONTROL = 0x00,
  TSL2561_REGISTER_TIMING = 0x01,
  TSL2561_REGISTER_THRESHHOLDL_LOW = 0x02,
  TSL2561_REGISTER_THRESHHOLDL_HIGH = 0x03,
  TSL2561_REGISTER_THRESHHOLDH_LOW = 0x04,
  TSL2561_REGISTER_THRESHHOLDH_HIGH = 0x05,
  TSL2561_REGISTER_INTERRUPT = 0x06,
  TSL2561_REGISTER_CRC = 0x08,
  TSL2561_REGISTER_ID = 0x0A,
  TSL2561_REGISTER_CHAN0_LOW = 0x0C,
  TSL2561_REGISTER_CHAN0_HIGH = 0x0D,
  TSL2561_REGISTER_CHAN1_LOW = 0x0E,
  TSL2561_REGISTER_CHAN1_HIGH = 0x0F
};



static TSL2561_Gain_t g_gain = TSL2561_GAIN_16X;

static TSL2561_IntegrationTime_t g_integrationtime = TSL2561_INTEGRATIONTIME_13MS;





/**
 * enable the sensor
 */
static rc_t _enable(void) {

	rc_t ret = twi_writeByte(TSL2561_TWI_ADDRESS,
			(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL),
			TSL2561_CONTROL_POWERON);

	return ret;

}

static rc_t _disable(void) {

	rc_t ret = twi_writeByte(TSL2561_TWI_ADDRESS,
			(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL),
			TSL2561_CONTROL_POWEROFF);

	return ret;
}

rc_t TSL2561_readID(uint8_t* id) {

	rc_t ret = twi_readByte(TSL2561_TWI_ADDRESS,
			TSL2561_REGISTER_ID, id);

	return ret;
}

rc_t _setTimeing() {

	rc_t ret = _enable();
	if (ret != SDDS_RT_OK)
		return ret;

	ret = twi_writeByte(TSL2561_TWI_ADDRESS,
			(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING),
			(g_integrationtime | g_gain));

	if (ret != SDDS_RT_OK)
		return ret;

	ret = _disable();

	if (ret != SDDS_RT_OK)
		return ret;

	return SDDS_RT_OK;
}

rc_t TSL2561_setGain(TSL2561_Gain_t gain) {


	g_gain = gain;

	return _setTimeing();
}

rc_t TSL2561_setTiming(TSL2561_IntegrationTime_t integration) {

	g_integrationtime = integration;

	return _setTimeing();
}

rc_t TSL2561_calculateLux(uint16_t ch0, uint16_t ch1, uint32_t* result) {

	uint32_t chScale;
	uint32_t channel1;
	uint32_t channel0;

	switch (g_integrationtime) {
	case TSL2561_INTEGRATIONTIME_13MS:
		chScale = TSL2561_LUX_CHSCALE_TINT0;
		break;
	case TSL2561_INTEGRATIONTIME_101MS:
		chScale = TSL2561_LUX_CHSCALE_TINT1;
		break;
	default: // No scaling ... integration time = 402ms
		chScale = (1 << TSL2561_LUX_CHSCALE);
		break;
	}

	// Scale for gain (1x or 16x)
	if (!g_gain)
		chScale = chScale << 4;

	// scale the channel values
	channel0 = (ch0 * chScale) >> TSL2561_LUX_CHSCALE;
	channel1 = (ch1 * chScale) >> TSL2561_LUX_CHSCALE;

	// find the ratio of the channel values (Channel1/Channel0)
	uint32_t ratio1 = 0;
	if (channel0 != 0) {
		ratio1 = (channel1 << (TSL2561_LUX_RATIOSCALE + 1)) / channel0;
	}

	// round the ratio value
	uint32_t ratio = (ratio1 + 1) >> 1;

	uint16_t b, m;

#ifdef TSL2561_PACKAGE_CS
	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1C))
	{	b=TSL2561_LUX_B1C; m=TSL2561_LUX_M1C;}
	else if (ratio <= TSL2561_LUX_K2C)
	{	b=TSL2561_LUX_B2C; m=TSL2561_LUX_M2C;}
	else if (ratio <= TSL2561_LUX_K3C)
	{	b=TSL2561_LUX_B3C; m=TSL2561_LUX_M3C;}
	else if (ratio <= TSL2561_LUX_K4C)
	{	b=TSL2561_LUX_B4C; m=TSL2561_LUX_M4C;}
	else if (ratio <= TSL2561_LUX_K5C)
	{	b=TSL2561_LUX_B5C; m=TSL2561_LUX_M5C;}
	else if (ratio <= TSL2561_LUX_K6C)
	{	b=TSL2561_LUX_B6C; m=TSL2561_LUX_M6C;}
	else if (ratio <= TSL2561_LUX_K7C)
	{	b=TSL2561_LUX_B7C; m=TSL2561_LUX_M7C;}
	else if (ratio > TSL2561_LUX_K8C)
	{	b=TSL2561_LUX_B8C; m=TSL2561_LUX_M8C;}
#else
	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1T)) {
		b = TSL2561_LUX_B1T;
		m = TSL2561_LUX_M1T;
	} else if (ratio <= TSL2561_LUX_K2T) {
		b = TSL2561_LUX_B2T;
		m = TSL2561_LUX_M2T;
	} else if (ratio <= TSL2561_LUX_K3T) {
		b = TSL2561_LUX_B3T;
		m = TSL2561_LUX_M3T;
	} else if (ratio <= TSL2561_LUX_K4T) {
		b = TSL2561_LUX_B4T;
		m = TSL2561_LUX_M4T;
	} else if (ratio <= TSL2561_LUX_K5T) {
		b = TSL2561_LUX_B5T;
		m = TSL2561_LUX_M5T;
	} else if (ratio <= TSL2561_LUX_K6T) {
		b = TSL2561_LUX_B6T;
		m = TSL2561_LUX_M6T;
	} else if (ratio <= TSL2561_LUX_K7T) {
		b = TSL2561_LUX_B7T;
		m = TSL2561_LUX_M7T;
	} else if (ratio > TSL2561_LUX_K8T) {
		b = TSL2561_LUX_B8T;
		m = TSL2561_LUX_M8T;
	}
#endif

	uint32_t temp;
	temp = ((channel0 * b) - (channel1 * m));

// do not allow negative lux value
	if (temp < 0)
		temp = 0;

// round lsb (2^(LUX_SCALE-1))
	temp += (1 << (TSL2561_LUX_LUXSCALE - 1));

// strip off fractional portion
	*result = temp >> TSL2561_LUX_LUXSCALE;

	return SDDS_RT_OK;
}

rc_t TSL2561_getChannels(uint16_t* channel0, uint16_t* channel1) {

	rc_t ret;

		if (channel0 == NULL || channel1 == NULL) {
			return SDDS_RT_BAD_PARAMETER;
		}
		// enable sensor
		ret = _enable();
		if (ret != SDDS_RT_OK)
			return ret;

		// wait till value is available

		switch (g_integrationtime)
		{
		case TSL2561_INTEGRATIONTIME_13MS:
			_delay_ms(14);
			break;
		case TSL2561_INTEGRATIONTIME_101MS:
			_delay_ms(102);
			break;
		default:
			_delay_ms(400);
			break;
		}


	ret = twi_readWord(TSL2561_TWI_ADDRESS,
					(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT |
					TSL2561_REGISTER_CHAN0_LOW), channel0);
	if (ret != SDDS_RT_OK)
		return ret;


	ret =twi_readWord(TSL2561_TWI_ADDRESS,
					(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT
					 | TSL2561_REGISTER_CHAN1_LOW), channel1);
	if (ret != SDDS_RT_OK)
		return ret;

	ret = _disable();
	if (ret != SDDS_RT_OK)
		return ret;
	return SDDS_RT_OK;
}



rc_t TSL2561_init(void) {

	twi_init();

	// set default gain and integration time
	_setTimeing();

	// default disable sensor
	_disable();

	return SDDS_RT_OK;
}
