/*
 * raingauge.c
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma
 */


#include "raingauge.h"
#include "driver.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#define RAINGAUGE_ISC(x) INTERNAL_CONCAT(ISC, INTERNAL_CONCAT(DRIVER_RAINGAUGE_INTERRUPT, x))
#define RAINGAUGE_INT INTERNAL_CONCAT(INT, DRIVER_RAINGAUGE_INTERRUPT)
#define RAINGAUGE_VECTOR INTERNAL_CONCAT(INT, INTERNAL_CONCAT(DRIVER_RAINGAUGE_INTERRUPT, _vect))
#define RAINGAUGE_INTF INTERNAL_CONCAT(INTF, DRIVER_RAINGAUGE_INTERRUPT)
#define DRIVER_RAINGAUGE_PORTR INTERNAL_CONCAT(PORT, DRIVER_RAINGAUGE_PORT)
#define DRIVER_RAINGAUGE_PORTVAL INTERNAL_CONCAT(P, INTERNAL_CONCAT(DRIVER_RAINGAUGE_PORT, DRIVER_RAINGAUGE_PIN))

/*
 * raingauge
 * using factor 10000, 0.2794 * 10000 = 2794
 * max current 8bit:    (255 ticks / 1 s) * 2794 = 712400 (71,24 mm/h)
 * max current 16bit: (65535 ticks / 1 s) * 2794 = 183104790 (18310,479 mm/h) (record 401 mm/h)
 * max hour 16bit:      (65535 ticks / 3600 s) * 2794 = 50862,4416667 (5,08624416667 mm/h)
 * max hour 32bit: (4294967295 ticks / 3600 s) * 2794 = 3333371839.51 (333337,183951 mm/h)
 */
static uint16_t g_raingauge_callback_calls;
static uint32_t g_raingauge_ticks[3];
static uint16_t g_raingauge_values[3]; // hour, minute, seconds


ISR(RAINGAUGE_VECTOR)
{
	g_raingauge_ticks[0]++;
	g_raingauge_ticks[1]++;
	g_raingauge_ticks[2]++;
}

static void raingauge_callback(void)
{
	uint16_t time_passed;

	g_raingauge_callback_calls++;

	time_passed = g_raingauge_callback_calls * DRIVER_RAINGAUGE_CALLBACK_PERIOD;

	if (time_passed % 60 == 0)
	{
		uint64_t temp_value;

		temp_value = (uint64_t)g_raingauge_ticks[0] * 2749 / 60;
		temp_value /= 2;

		/* temp_value has factor 10000, repr has 100 */
		g_raingauge_values[0] = INTERNAL_MIN(UINT16_MAX, temp_value / 100);
		g_raingauge_ticks[0] = 0;
	}

	if (time_passed % 3600 == 0)
	{
		uint64_t temp_value;

		temp_value = (uint64_t)g_raingauge_ticks[1] * 2749 / 3600;
		temp_value /= 2;

		/* temp_value has factor 10000, repr has 100 */
		g_raingauge_values[1] = INTERNAL_MIN(UINT16_MAX, temp_value / 100);
		g_raingauge_ticks[1] = 0;

		// reset every hour
		g_raingauge_callback_calls = 0;
	}

	/* temp_value has factor 10000, repr has 100 */
	g_raingauge_values[2] = INTERNAL_MIN(UINT16_MAX, (g_raingauge_ticks[2] * 2749) / 100 / DRIVER_RAINGAUGE_CALLBACK_PERIOD);
	g_raingauge_ticks[2] = 0;
}

rc_t raingauge_init(void)
{
	DRIVER_RAINGAUGE_PORTR |= _BV(DRIVER_RAINGAUGE_PORTVAL);

	// prevent an interrupt to occur when changing ISC bits
	EIMSK &= ~_BV(RAINGAUGE_INT);

#if 1
	// positive edge triggered
	DRIVER_RAINGAUGE_EICR |= _BV(RAINGAUGE_ISC(1)) | _BV(RAINGAUGE_ISC(0));
#else
	// negative edge triggered
	DRIVER_RAINGAUGE_EICR |= _BV(RAINGAUGE_ISC(1));
	DRIVER_RAINGAUGE_EICR &= ~_BV(RAINGAUGE_ISC(0));
#endif

	// clear interrupt flag, so it can't get fired until re-enabling
	EIFR |= _BV(RAINGAUGE_INTF);

	// enable the interrupt again
	EIMSK |= _BV(RAINGAUGE_INT);

	raingauge_register_callback(raingauge_callback);

	return SDDS_RT_OK;
}

rc_t raingauge_read_current(uint16_t *value)
{
	*value = g_raingauge_values[2];

	return SDDS_RT_OK;
}

rc_t raingauge_read_minute(uint16_t *value)
{
	*value = g_raingauge_values[0];

	return SDDS_RT_OK;
}

rc_t raingauge_read_hour(uint16_t *value)
{
	*value = g_raingauge_values[1];

	return SDDS_RT_OK;
}
