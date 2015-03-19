#include "twi-pcf-config.h"
#include "twi-pcf.h"
#include "twi.h"

rc_t twi_init_pcf(uint8_t channel)
{
	twi_data_t data[4];
	uint8_t failed_command;

	data[0].type = TWI_TYPE_START;

	data[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	data[1].byte = DRIVER_TWI_PCF_8591P_ADDRESS;

	data[2].type = TWI_TYPE_TRANSMIT_DATA;
	data[2].byte = DRIVER_TWI_PCF_8591P_CONTROL | channel;

	data[3].type = TWI_TYPE_TRANSMIT_DATA;
	data[3].byte = DRIVER_TWI_PCF_8591P_TAP;

	if (twi_communicate(data, sizeof data / sizeof *data, &failed_command) != 0)
		return SDDS_RT_FAIL;

	return SDDS_RT_OK;
}

rc_t twi_read_pcf(uint8_t *value)
{
	twi_data_t data[4];
	uint8_t failed_command;

	data[0].type = TWI_TYPE_START;

	data[1].type = TWI_TYPE_RECEIVE_ADDRESS;
	data[1].byte = DRIVER_TWI_PCF_8591P_ADDRESS;

	data[2].type = TWI_TYPE_RECEIVE_DATA; /* throw this byte away */

	data[3].type = TWI_TYPE_RECEIVE_DATA;

	if (twi_communicate(data, sizeof data / sizeof *data, &failed_command) != 0)
		return SDDS_RT_FAIL;

	*value = data[1].byte;

	return SDDS_RT_OK;
}
