/*
 * sht15.c
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma
 */


#include "sht15.h"
#include "driver.h"

#include <avr/io.h>

#define SHT15_SDA_PINR INTERNAL_CONCAT(PIN, DRIVER_SHT15_DATA_PORT)
#define SHT15_SDA_PIN INTERNAL_CONCAT(PIN, INTERNAL_CONCAT(DRIVER_SHT15_DATA_PORT, DRIVER_SHT15_DATA_PIN))
#define SHT15_SDA_DDR INTERNAL_CONCAT(DDR, DRIVER_SHT15_DATA_PORT)
#define SHT15_SDA_DD INTERNAL_CONCAT(DD, INTERNAL_CONCAT(DRIVER_SHT15_DATA_PORT, DRIVER_SHT15_DATA_PIN))
#define SHT15_SDA_PORTR INTERNAL_CONCAT(PORT, DRIVER_SHT15_DATA_PORT)
#define SHT15_SDA_PORT INTERNAL_CONCAT(P, INTERNAL_CONCAT(DRIVER_SHT15_DATA_PORT, DRIVER_SHT15_DATA_PIN))
#define SHT15_SCL_PINR INTERNAL_CONCAT(PIN, DRIVER_SHT15_CLOCK_PORT)
#define SHT15_SCL_PIN INTERNAL_CONCAT(SHT15_SCL_PINR, DRIVER_SHT15_CLOCK_PIN)
#define SHT15_SCL_DDR INTERNAL_CONCAT(DDR, DRIVER_SHT15_CLOCK_PORT)
#define SHT15_SCL_DD INTERNAL_CONCAT(DD, INTERNAL_CONCAT(DRIVER_SHT15_CLOCK_PORT, DRIVER_SHT15_CLOCK_PIN))
#define SHT15_SCL_PORTR INTERNAL_CONCAT(PORT, DRIVER_SHT15_CLOCK_PORT)
#define SHT15_SCL_PORT INTERNAL_CONCAT(P, INTERNAL_CONCAT(DRIVER_SHT15_CLOCK_PORT, DRIVER_SHT15_CLOCK_PIN))




static inline uint8_t sht15_sda_bit_is_set(void)
{
	return (SHT15_SDA_PINR & _BV(SHT15_SDA_PIN)) != 0;
}

static inline void sht15_scl_high(void)
{
	SHT15_SCL_PORTR |= _BV(SHT15_SCL_PORT);
}

static inline void sht15_scl_low(void)
{
	SHT15_SCL_PORTR &= ~_BV(SHT15_SCL_PORT);
}

static inline void sht15_sda_high(void)
{
	// due to the use of pull-ups, just release pin
	SHT15_SDA_DDR &= ~_BV(SHT15_SDA_DD);
}

static inline void sht15_sda_low(void)
{
	// due to the use of pull-ups, setting pin = pulling down
	SHT15_SDA_DDR |= _BV(SHT15_SDA_DD);
}

static inline void sht15_delay(void)
{
	// half period wait
	_delay_us((int32_t)1.0 * 1000 * 1000 / (DRIVER_SHT15_BUS_SPEED * 2));
}

static inline void sht15_pulse(void)
{
	sht15_scl_high();
	sht15_delay();
	sht15_scl_low();
}

static void sht15_start(void)
{
	sht15_scl_high();
	sht15_delay();
	sht15_sda_low();
	sht15_delay();
	// now low pulse
	sht15_scl_low();
	sht15_delay();
	sht15_scl_high();
	sht15_delay();
	// back to initial state
	sht15_sda_high();
	sht15_delay();
	sht15_scl_low();
	sht15_delay();
}

static uint8_t sht15_write(uint8_t byte)
{
	uint8_t i;
	uint8_t ack_received;

	for (i = 0; i < 8; i++)
	{
		if (byte & (1 << 7))
			sht15_sda_high();
		else
			sht15_sda_low();

		byte <<= 1;

		sht15_delay();
		sht15_pulse();
	}

	sht15_sda_high();
	sht15_delay();

	// slave pulls down data if ACKed
	ack_received = sht15_sda_bit_is_set() == 0;

	sht15_pulse();

	return ack_received;
}

static uint8_t sht15_read(uint8_t ack)
{
	uint8_t i;
	uint8_t byte;

	byte = 0;

	for (i = 0; i < 8; i++)
	{
		if (sht15_sda_bit_is_set())
			byte |= 1;

		if (i != 7)
			byte <<= 1;

		sht15_pulse();
		sht15_delay();
	}

	// master pulls down data if ACKed
	if (ack)
		sht15_sda_low();
	else
		sht15_sda_high();

	sht15_delay();
	sht15_pulse();

	// only need to reset pin if ACKed
	if (ack)
		sht15_sda_high();

	sht15_delay();

	return byte;
}

static void sht15_reset_communication(void)
{
	uint8_t i;

	// at least 9 pulses
	for (i = 0; i < 9; i++)
	{
		sht15_pulse();
		sht15_delay();
	}
}

static int8_t sht15_read_16bit(uint8_t command, int16_t *word)
{
	int16_t value;

	sht15_reset_communication();
	sht15_start();

	if (sht15_write(command) == 0)
		return 1;

	// watchdog will prevent timing out... hopefully :)
	while (sht15_sda_bit_is_set())
		;

	value = sht15_read(1) << 8 | sht15_read(0);

	*word = value;

	return 0;
}

rc_t sht15_init(void)
{
	// set sda tri-state
	SHT15_SDA_PORTR &= ~_BV(SHT15_SDA_PORT);
	SHT15_SDA_DDR &= ~_BV(SHT15_SDA_DD);

	// set scl low
	SHT15_SCL_PORTR &= ~_BV(SHT15_SCL_PORT);
	SHT15_SCL_DDR |= _BV(SHT15_SCL_DD);

	_delay_ms(11);

	// initial software reset
	sht15_reset_communication();
	sht15_start();
	sht15_write(0x1E);

	_delay_ms(11);

#ifndef DRIVER_SHT15_HIGH_RESOLUTION
	// setup resolution if required
	sht15_reset_communication();
	sht15_start();

	// write status register
	if (sht15_write(0x6) == 0)
		return SDDS_RT_FAIL;

	// write low resolution bit
	if (sht15_write(0x1) == 0)
		return SDDS_RT_FAIL;
#endif

	return SDDS_RT_OK;
}

rc_t sht15_read_temperature(int16_t *temperature)
{
	int16_t sensor_temp;

	enum
	{
		/*
		 * coefficients specified in the datasheet
		 * adjusted to give a non-floating integer
		 */

#ifdef DRIVER_SHT15_HIGH_RESOLUTION
		d1 = DRIVER_SHT15_TEMPERATURE_COEFFICIENT, // factor 100
		d2 = 1                              // factor 100
#else
		d1 = DRIVER_SHT15_TEMPERATURE_COEFFICIENT, // factor 100
		d2 = 4                              // factor 100
#endif
	};

	// read sensor temperature
	if (sht15_read_16bit(0x03, &sensor_temp) != 0)
		return SDDS_RT_FAIL;

	// result has factor 100
	*temperature = (int32_t)d1 + (int32_t)d2 * sensor_temp;

	return SDDS_RT_OK;
}

rc_t sht15_read_relative_humidity(uint16_t *humidity)
{
	enum
	{
		/*
		 * coefficients specified in the datasheet
		 * adjusted to give a non-floating integer
		 */
#ifdef DRIVER_SHT15_HIGH_RESOLUTION
		c1 = -20468,   // factor = 10000
		c2 = 367,      // factor = 10000
		c3 = -15955,   // factor = 10000000000
		t1 = 1,        // factor = 100
		t2 = 8         // factor = 100000
#else
		c1 = -20468,   // factor = 10000
		c2 = 5872,     // factor = 10000
		c3 = -4085400, // factor = 10000000000
		t1 = 1,        // factor = 100
		t2 = 128       // factor = 100000
#endif
	};

	/*
	 * linear_hum = c1 + c2 * sensor_hum + c3 * sensor_hum * sensor_hum
	 * c3 has the highest factor, so adjust to that factor
	 * c1 -> c3 = 1000000
	 * c2 -> c3 = 1000000
	 *
	 * as the highest factor is beyond the range of a 32bit
	 * integer, use 64bit
	 */
	int16_t sensor_hum;
	int64_t linear_hum;

	if (sht15_read_16bit(0x05, &sensor_hum) != 0)
		return 1;

	linear_hum = (int64_t)c1 * 1000000;
	linear_hum += (int64_t)c2 * sensor_hum * 1000000;
	linear_hum += (int64_t)c3 * sensor_hum * sensor_hum;

	/*
	 * if the temperature is significantly different from 25°C
	 * it needs a correction
	 */
	{
		int16_t sensor_temp;;
		int32_t comp_temp;

		/*
		 * the forumla is hum_true = (sensor_temp - 25) * (t1 + t2 * sensor_hum) +
		 *                           linear_hum
		 * t2 has the highest factor, so adjust to that factor
		 * t1 -> t2 = 1000
		 * sensor_temp -> t2 = 1000
		 */
		if (sht15_read_temperature(&sensor_temp) != 0)
			return SDDS_RT_FAIL;

		// sensor_temp is factor 100, 25 * 100 = 2500
		comp_temp = sensor_temp - 2500;
		// 16bit * 1000 could overflow, so expand
		comp_temp *= (int32_t)t1 * 1000 + (int32_t)t2 * sensor_hum;

		/*
		 * linear_hum has factor 10000000000
		 * comp_temp has factor 100000 (t2) * 100 (left side) = 10000000
		 * comp_temp -> linear_hum = 1000
		 * result needs to be factor 100, hence / 100000000
		 */
		*humidity = (linear_hum + (int64_t)comp_temp * 1000) / 100000000;
	}

	return SDDS_RT_OK;
}
