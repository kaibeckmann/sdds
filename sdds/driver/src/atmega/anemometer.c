/*
 * anemometer.c
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma
 */


#include "anemometer.h"
#include "driver.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define ANEMOMETER_ISC(x) INTERNAL_CONCAT(ISC, INTERNAL_CONCAT(ANEMOMETER_INTERRUPT, x))
#define ANEMOMETER_INT INTERNAL_CONCAT(INT, ANEMOMETER_INTERRUPT)
#define ANEMOMETER_VECTOR INTERNAL_CONCAT(INT, INTERNAL_CONCAT(ANEMOMETER_INTERRUPT, _vect))
#define ANEMOMETER_INTF INTERNAL_CONCAT(INTF, ANEMOMETER_INTERRUPT)
#define ANEMOMETER_PORTR INTERNAL_CONCAT(PORT, ANEMOMETER_PORT)
#define ANEMOMETER_PORTVAL INTERNAL_CONCAT(P, INTERNAL_CONCAT(ANEMOMETER_PORT, ANEMOMETER_PIN))


/*
 * anemometer:
 * using factor 100, 2.4 * 100 = 240
 * max current: (255 ticks / 1 s) * 240 = 61200 (612 km/h)
 * max hour 8bit:    (255 ticks /    1 s) * 240 = 17 (0.17 km/h)
 * max hour 16bit: (65535 ticks / 3600 s) * 240 = 436900 (4369 km/h)
 */
static uint16_t g_anemometer_callback_calls;
static uint16_t g_anemometer_ticks[3];
static uint16_t g_anemometer_values[3]; // hour, minute, seconds



ISR(ANEMOMETER_VECTOR)
{
	g_anemometer_ticks[0]++;
	g_anemometer_ticks[1]++;
	g_anemometer_ticks[2]++;
}

static void anemometer_callback(void)
{
	uint16_t time_passed;

	g_anemometer_callback_calls++;

	time_passed = g_anemometer_callback_calls * ANEMOMETER_CALLBACK_PERIOD;

	if (time_passed % 60 == 0)
	{
		uint32_t temp_value;

		temp_value = (uint32_t)g_anemometer_ticks[0] * 240 / 60;
		temp_value /= 2;

		g_anemometer_values[0] = INTERNAL_MIN(UINT16_MAX, temp_value);
		g_anemometer_ticks[0] = 0;
	}

	if (time_passed % 3600 == 0)
	{
		uint32_t temp_value;

		temp_value = (uint32_t)g_anemometer_ticks[1] * 240 / 3600;
		temp_value /= 2;

		g_anemometer_values[1] = INTERNAL_MIN(UINT16_MAX, temp_value);
		g_anemometer_ticks[1] = 0;

		// reset every hour
		g_anemometer_callback_calls = 0;
	}

	g_anemometer_values[2] = INTERNAL_MIN(UINT16_MAX, (g_anemometer_ticks[2] * 240) / ANEMOMETER_CALLBACK_PERIOD);
	g_anemometer_ticks[2] = 0;
}

rc_t anemometer_init(void)
{
	ANEMOMETER_PORTR |= _BV(ANEMOMETER_PORTVAL);

	// prevent an interrupt to occur when changing ISC bits
	EIMSK &= ~_BV(ANEMOMETER_INT);

#if 1
	// positive edge triggered
	ANEMOMETER_EICR |= _BV(ANEMOMETER_ISC(1)) | _BV(ANEMOMETER_ISC(0));
#else
	// negative edge triggered
	ANEMOMETER_EICR |= _BV(ANEMOMETER_ISC(1));
	ANEMOMETER_EICR &= ~_BV(ANEMOMETER_ISC(0));
#endif

	// clear interrupt flag, so it can't get fired until re-enabling
	EIFR |= _BV(ANEMOMETER_INTF);

	// enable the interrupt again
	EIMSK |= _BV(ANEMOMETER_INT);

	anemometer_register_callback(anemometer_callback);

	return SDDS_RT_OK;
}

rc_t anemometer_read_current(uint16_t *value)
{
	*value = g_anemometer_values[2];

	return SDDS_RT_OK;
}

rc_t anemometer_read_minute(uint16_t *value)
{
	*value = g_anemometer_values[0];

	return SDDS_RT_OK;
}

rc_t anemometer_read_hour(uint16_t *value)
{
	*value = g_anemometer_values[1];

	return SDDS_RT_OK;
}
