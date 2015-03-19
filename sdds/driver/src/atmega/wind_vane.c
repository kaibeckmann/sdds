/*
 * wind_vane.c
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma
 */


#include "wind_vane.h"
#include "driver.h"
#include "adc.h"

#include <avr/io.h>

/* resistor used as voltage divider */
#define DRIVER_WIND_VANE_DIVIDER_RESISTOR 5.4f

/* maximum amount of switch positions */
#define DRIVER_WIND_VANE_MAX_SWITCHES 16

/* lookup table for wind vane conversions, calculated on initialization */
static uint16_t wind_vane_conversions[DRIVER_WIND_VANE_MAX_SWITCHES];


rc_t wind_vane_init(void)
{
	uint8_t i;

	/* lookup table for wind vane resistors, recalculated on initialization */
	float const wind_vane_resistors[DRIVER_WIND_VANE_MAX_SWITCHES] =
	{
		33,
		(33 * 8.2) / (33 + 8.2),
		8.2,
		(8.2 * 1) / (8.2 + 1),
		1,
		(1 * 2.2) / (1 + 2.2),
		2.2,
		(2.2 * 3.9) / (2.2 + 3.9),
		3.9,
		(3.9 * 16) / (3.9 + 16),
		16,
		(16 * 120) / (16 + 120),
		120,
		(120 * 64.9) / (120 + 64.9),
		64.9,
		(64.9 * 33) / (64.9 + 33)
	};

#if 1
	// for connection to the adc
	adc_init_mux(DRIVER_WIND_VANE_ADC_REFERENCE);
	adc_init();
#else
	// for connection to the twi
	twi_init();
#endif

	for (i = 0; i < DRIVER_WIND_VANE_MAX_SWITCHES; i++)
	{
		float const divider = wind_vane_resistors[i] / (wind_vane_resistors[i] + DRIVER_WIND_VANE_DIVIDER_RESISTOR);
		wind_vane_conversions[i] = DRIVER_WIND_VANE_POSSIBLE_VALUES * divider;
	}

	return SDDS_RT_OK;
}

/* find the closest possible match from the lookup table */
static uint8_t closest_wind_vane_direction_index(uint16_t value)
{
	uint8_t current_index;
	uint8_t min_index;
	uint16_t current_min;

	/* initialize first set, then loop */
	current_index = 0;
	current_min = abs(wind_vane_conversions[current_index] - value);
	min_index = 0;

	for (current_index = 1; current_index < DRIVER_WIND_VANE_MAX_SWITCHES; current_index++)
	{
		uint16_t distance;

		/* calculate the current distance to this lookup entry */
		distance = abs(wind_vane_conversions[current_index] - value);

		if (distance < current_min)
		{
			min_index = current_index;
			current_min = distance;
		}
	}

	return min_index;
}

rc_t wind_vane_read(uint8_t *value)
{
	uint16_t read_value;

	// for connection to the adc input 1
	read_value = adc_read(DRIVER_WIND_VANE_ADC_CHANNEL);

	/* find the closest match from the lookup table */
	*value = closest_wind_vane_direction_index(read_value);

	return SDDS_RT_OK;
}
