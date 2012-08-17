/*
 * bmp085.c
 *
 *  Created on: 2 Jul 2012
 *      Author: k_beckma
 */


#include "bmp085.h"
#include "driver.h"

#include "twi.h"

/* eeprom data for the bmp085 sensor */
struct
{
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;
} g_bmp085_eeprom;

rc_t bmp085_init(void)
{
	uint8_t i;
	twi_data_t data[27];
	uint8_t failed_command;

	twi_init();

	data[0].type = TWI_TYPE_START;

	data[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	data[1].byte = 0xEE;

	data[2].type = TWI_TYPE_TRANSMIT_DATA;
	data[2].byte = 0xAA;

	data[3].type = TWI_TYPE_START;

	data[4].type = TWI_TYPE_RECEIVE_ADDRESS;
	data[4].byte = 0xEF;

	for (i = 0; i < 22; i++)
		data[4 + 1 + i].type = TWI_TYPE_RECEIVE_DATA;

	if (twi_communicate(data, sizeof data / sizeof *data, &failed_command) != 0)
		return SDDS_RT_FAIL;

	g_bmp085_eeprom.ac1 =  (data[5].byte << 8) | data[6].byte;
	g_bmp085_eeprom.ac2 =  (data[7].byte << 8) | data[8].byte;
	g_bmp085_eeprom.ac3 =  (data[9].byte << 8) | data[10].byte;
	g_bmp085_eeprom.ac4 = (data[11].byte << 8) | data[12].byte;
	g_bmp085_eeprom.ac5 = (data[13].byte << 8) | data[14].byte;
	g_bmp085_eeprom.ac6 = (data[15].byte << 8) | data[16].byte;
	g_bmp085_eeprom.b1 =  (data[17].byte << 8) | data[18].byte;
	g_bmp085_eeprom.b2 =  (data[19].byte << 8) | data[20].byte;
	g_bmp085_eeprom.mb =  (data[21].byte << 8) | data[22].byte;
	g_bmp085_eeprom.mc =  (data[23].byte << 8) | data[24].byte;
	g_bmp085_eeprom.md =  (data[25].byte << 8) | data[26].byte;

	return SDDS_RT_OK;
}

static rc_t bmp085_read_temperature_and_b5(int16_t *temperature, int32_t *b5_store)
{
	twi_data_t data[7];
	uint8_t failed_command;
	int32_t x1;
	int32_t x2;
	int32_t b5;
	int32_t raw_temperature;

	twi_init();

	data[0].type = TWI_TYPE_START;

	data[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	data[1].byte = 0xEE;

	data[2].type = TWI_TYPE_TRANSMIT_DATA;
	data[2].byte = 0xF4;

	data[3].type = TWI_TYPE_TRANSMIT_DATA;
	data[3].byte = 0x2E;

	if (twi_communicate(data, 4, &failed_command) != 0)
		return SDDS_RT_FAIL;

	/* datasheet says 4.5, be on the safe side here */
	_delay_ms(10);

	data[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	data[1].byte = 0xEE;

	data[2].type = TWI_TYPE_TRANSMIT_DATA;
	data[2].byte = 0xF6;

	data[3].type = TWI_TYPE_START;

	data[4].type = TWI_TYPE_RECEIVE_ADDRESS;
	data[4].byte = 0xEF;

	data[5].type = TWI_TYPE_RECEIVE_DATA;

	data[6].type = TWI_TYPE_RECEIVE_DATA;

	if (twi_communicate(data, sizeof data / sizeof *data, &failed_command) != 0)
		return SDDS_RT_FAIL;

	raw_temperature = ((data[5].byte << 8) | data[6].byte);
	x1 = (raw_temperature - g_bmp085_eeprom.ac6) * g_bmp085_eeprom.ac5 / ((int32_t)1 << 15);
	x2 = (int32_t)g_bmp085_eeprom.mc * (1 << 11) / (x1 + g_bmp085_eeprom.md);
	b5 = x1 + x2;

	if (temperature)
		*temperature = (b5 + 8) / (1 << 4) * 10;

	if (b5_store)
		*b5_store = b5;

	return SDDS_RT_OK;
}

rc_t bmp085_read_temperature(int16_t *temperature)
{
	if (bmp085_read_temperature_and_b5(temperature, NULL) != 0)
		return SDDS_RT_FAIL;

	return SDDS_RT_OK;
}

rc_t bmp085_read_pressure(uint16_t *pressure)
{
	twi_data_t data[7];
	uint8_t failed_command;
	int32_t x1;
	int32_t x2;
	int32_t x3;
	int32_t b3;
	uint32_t b4;
	int32_t b5;
	int32_t b6;
	uint32_t b7;
	int32_t temp_pressure;
	enum { oss = 0 };

	twi_init();

	data[0].type = TWI_TYPE_START;

	data[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	data[1].byte = 0xEE;

	data[2].type = TWI_TYPE_TRANSMIT_DATA;
	data[2].byte = 0xF4;

	data[3].type = TWI_TYPE_TRANSMIT_DATA;
	data[3].byte = 0x34;

	if (twi_communicate(data, 4, &failed_command) != 0)
		return SDDS_RT_FAIL;

	/* datasheet says 4.5, be on the safe side here */
	_delay_ms(10);

	data[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	data[1].byte = 0xEE;

	data[2].type = TWI_TYPE_TRANSMIT_DATA;
	data[2].byte = 0xF6;

	data[3].type = TWI_TYPE_START;

	data[4].type = TWI_TYPE_RECEIVE_ADDRESS;
	data[4].byte = 0xEF;

	data[5].type = TWI_TYPE_RECEIVE_DATA;

	data[6].type = TWI_TYPE_RECEIVE_DATA;

	if (twi_communicate(data, sizeof data / sizeof *data, &failed_command) != 0)
		return SDDS_RT_FAIL;

	if (bmp085_read_temperature_and_b5(NULL, &b5) != 0)
		return SDDS_RT_FAIL;

	temp_pressure = ((int32_t)data[5].byte << 8) | data[6].byte;

	b6 = b5 - 4000;
	x1 = ((int32_t)g_bmp085_eeprom.b2 * (b6 * b6 / (1 << 12))) / (1 << 11);
	x2 = (int32_t)g_bmp085_eeprom.ac2 * b6 / (1 << 11);
	x3 = x1 + x2;
	b3 = ((((int32_t)g_bmp085_eeprom.ac1 * 4 + x3) << oss) + 2) / 4;
	x1 = (int32_t)g_bmp085_eeprom.ac3 * b6 / (1 << 13);
	x2 = ((int32_t)g_bmp085_eeprom.b1 * (b6 * b6 / (1 << 12))) / ((int32_t)1 << 16);
	x3 = ((x1 + x2) + 2) / (1 << 2);
	b4 = (int32_t)g_bmp085_eeprom.ac4 * (uint32_t)(x3 + 32768) / ((int32_t)1 << 15);
	b7 = ((uint32_t)temp_pressure - b3) * (50000 >> oss);
	b4 = (int32_t)g_bmp085_eeprom.ac4 * (uint32_t)(x3 + 32768) / ((int32_t)1 << 15);

	if (b7 < (uint32_t)0x80000000)
		temp_pressure = (b7 * 2) / b4;
	else
		temp_pressure = (b7 / b4) * 2;

	x1 = (temp_pressure / (1 << 8)) * (temp_pressure / (1 << 8));
	x1 = (x1 * 3038) / ((int32_t)1 << 16);
	x2 = (-7357 * temp_pressure) / ((int32_t)1 << 16);

	temp_pressure += (x1 + x2 + 3791) / (1 << 4);

	// 1 pA => 10 hPa
	*pressure = temp_pressure / 10;

	return SDDS_RT_OK;
}
