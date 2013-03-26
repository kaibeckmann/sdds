#include "twi.h"

#include "Log.h"
#include <avr/io.h>
#include <avr/power.h>

#include <util/twi.h>

/* macros to create easy access to the pin registers */
#define INTERNAL_CONCAT2(x, y) x ## y
#define INTERNAL_CONCAT(x, y) INTERNAL_CONCAT2(x, y)

#define TWI_SDA_DDR INTERNAL_CONCAT(DDR, TWI_DATA_PORT)
#define TWI_SDA_DD INTERNAL_CONCAT(DD, INTERNAL_CONCAT(TWI_DATA_PORT, TWI_DATA_PIN))
#define TWI_SDA_PORTR INTERNAL_CONCAT(PORT, TWI_DATA_PORT)
#define TWI_SDA_PORT INTERNAL_CONCAT(P, INTERNAL_CONCAT(TWI_DATA_PORT, TWI_DATA_PIN))
#define TWI_SCL_PINR INTERNAL_CONCAT(PIN, TWI_CLOCK_PORT)
#define TWI_SCL_PIN INTERNAL_CONCAT(TWI_SCL_PINR, TWI_CLOCK_PIN)
#define TWI_SCL_DDR INTERNAL_CONCAT(DDR, TWI_CLOCK_PORT)
#define TWI_SCL_DD INTERNAL_CONCAT(DD, INTERNAL_CONCAT(TWI_CLOCK_PORT, TWI_CLOCK_PIN))
#define TWI_SCL_PORTR INTERNAL_CONCAT(PORT, TWI_CLOCK_PORT)
#define TWI_SCL_PORT INTERNAL_CONCAT(P, INTERNAL_CONCAT(TWI_CLOCK_PORT, TWI_CLOCK_PIN))

/* the last set status register value */
static uint8_t g_twst;

rc_t twi_activateInternalPullUp() {

	TWI_SCL_PORTR |= _BV(TWI_SCL_PORT);
	TWI_SDA_PORTR |= _BV(TWI_SDA_PORT);


	return SDDS_RT_OK;
}

void twi_init(void)
{
#ifndef F_CPU
#error "Please set F_CPU to the frequency of the target system in Hz."
#endif

	static int init = 0;

	if (init)
		return;

	power_twi_enable();

#ifdef USE_DERFMEGA128
	/* deactivate the onboard twi-eeprom */
	DDRD |= _BV(DDD6);
#endif

	/* setup the scl and sda registers */
	//TWI_SCL_PORTR |= _BV(TWI_SCL_DD);
	//TWI_SDA_PORTR |= _BV(TWI_SDA_DD);

	/* setup frequency and finally enable the twi functions */
	TWSR = 0;
	TWBR = (uint8_t)(F_CPU / TWI_BUS_SPEED - 16) / 2;
	TWDR = 0xFF;
	TWCR = _BV(TWEN);

	init = 1;
}

static void twi_set_control(uint8_t byte)
{
	TWCR = _BV(TWINT) | _BV(TWEN) | byte;
}

static void twi_wait(void)
{
	while ((TWCR & _BV(TWINT)) == 0)
		;

	g_twst = TWSR & TW_STATUS_MASK;
}

static void twi_wait_stop(void)
{
	while (TWCR & _BV(TWSTO))
		;
}

/*
 * for the following functions:
 * -1 on error, 1 on lost, 2 on nack/ack, 0 on success
 */
static int twi_transmit_to_slave(twi_data_t *data)
{
	TWDR = data->byte | TW_WRITE;
	twi_set_control(0);
	twi_wait();

	switch (g_twst)
	{
		case TW_MT_ARB_LOST:
			return 1;

		case TW_MT_SLA_NACK:
			return 2;

		case TW_MT_SLA_ACK:
			return 0;
	}

	return -1;
}

static int twi_receive_from_slave(twi_data_t *data)
{
	TWDR = data->byte | TW_READ;
	twi_set_control(0);
	twi_wait();

	switch (g_twst)
	{
		case TW_MR_ARB_LOST:
			return 1;

		case TW_MR_SLA_NACK:
			return 2;

		case TW_MR_SLA_ACK:
			return 0;
	}

	return -1;
}

static int twi_transmit_data(twi_data_t *data)
{
	TWDR = data->byte;
	twi_set_control(0);
	twi_wait();

	switch (g_twst)
	{
		case TW_MT_ARB_LOST:
			return 1;

		case TW_MT_DATA_NACK:
			return 2;

		case TW_MT_DATA_ACK:
			return 0;
	}

	return -1;
}

static int twi_receive_data(twi_data_t *data, uint8_t set_ack)
{
	twi_set_control(0 | (set_ack ? _BV(TWEA) : 0));
	twi_wait();

	switch (g_twst)
	{
		case TW_MR_ARB_LOST:
			return 1;

		case TW_MR_DATA_NACK:
			data->byte = TWDR;
			return 2;

		case TW_MR_DATA_ACK:
			data->byte = TWDR;
			return 0;
	}

	return -1;
}

static int twi_set_start(void)
{
	twi_set_control(_BV(TWSTA));
	twi_wait();

	if (g_twst == TW_MT_ARB_LOST)
		return 1;

	if (g_twst != TW_START && g_twst != TW_REP_START)
		return -1;

	return 0;
}

int8_t twi_communicate(twi_data_t *data, uint8_t amount, uint8_t *failed_command)
{
	uint8_t i;
	int result = 0;

	if (amount == 0)
		return 0;

	for (i = 0; i < amount; i++)
	{
		switch (data[i].type)
		{
			case TWI_TYPE_START:
				result = twi_set_start();
				break;

			case TWI_TYPE_TRANSMIT_ADDRESS:
				result = twi_transmit_to_slave(data + i);
				break;

			case TWI_TYPE_RECEIVE_ADDRESS:
				result = twi_receive_from_slave(data + i);
				break;

			case TWI_TYPE_TRANSMIT_DATA:
				result = twi_transmit_data(data + i);
				break;

			case TWI_TYPE_RECEIVE_DATA:
				if (i != amount - 1)
				{
					result = twi_receive_data(data + i, 1);
				}
				else
				{
					/* no ack wanted */
					result = twi_receive_data(data + i, 0);

					if (result == 0) /* ack received */
						result = 2;
					else if (result == 2)
						result = 0;
				}

				break;

			default:
				result = 0;
				break;
		}

		if (result == 2) /* ack/nack received although not wanted */
			break;

		if (result == 1) /* arb lost */

			break;

		if (result == -1)
			break;
	}

	twi_set_control(_BV(TWSTO));
	twi_wait_stop();


	if (result != 0)
		*failed_command = i;

	return result;
}

rc_t twi_writeByte(uint8_t addr, uint8_t reg, uint8_t data) {


	uint8_t failed_command;
	twi_data_t send[4];

//	Log_debug("write: addr 0x%x, reg 0x%x, data 0x%x\n", addr, reg, data);
	send[0].type = TWI_TYPE_START;

	send[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	send[1].byte = addr;

	send[2].type = TWI_TYPE_TRANSMIT_DATA;
	send[2].byte = reg;

	send[3].type = TWI_TYPE_TRANSMIT_DATA;
	send[3].byte = data;

	// send wake up command
	if (twi_communicate(send, 4, &failed_command) != 0)
		return SDDS_RT_FAIL;

	//return failed_command;

	return SDDS_RT_OK;

}

rc_t twi_writeWord(uint8_t addr, uint8_t reg, uint16_t data) {


	uint8_t failed_command;
	twi_data_t send[5];

	send[0].type = TWI_TYPE_START;

	send[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	send[1].byte = addr;

	send[2].type = TWI_TYPE_TRANSMIT_DATA;
	send[2].byte = reg;

	send[3].type = TWI_TYPE_TRANSMIT_DATA;
	send[3].byte = (uint8_t) (data & 0x00ff);

	send[4].type = TWI_TYPE_TRANSMIT_DATA;
	send[4].byte = (uint8_t) (data >> 8);

	// send wake up command
	if (twi_communicate(send, 5, &failed_command) != 0)
		return SDDS_RT_FAIL;

	return SDDS_RT_OK;
}

rc_t twi_readByte(uint8_t addr, uint8_t reg, uint8_t* data) {


	uint8_t failed_command;
	twi_data_t buf[6];

	buf[0].type = TWI_TYPE_START;

	buf[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	buf[1].byte = addr;

	buf[2].type = TWI_TYPE_TRANSMIT_DATA;
	buf[2].byte = reg;

	buf[3].type = TWI_TYPE_START;

	buf[4].type = TWI_TYPE_RECEIVE_ADDRESS;
	buf[4].byte = addr;

	buf[5].type = TWI_TYPE_RECEIVE_DATA;

	if (twi_communicate(buf, 6, &failed_command) != 0) {
		Log_debug("command %d failed\n", failed_command);
		return SDDS_RT_FAIL;
	}


	*data = buf[5].byte;

	return SDDS_RT_OK;
}

rc_t twi_readWord(uint8_t addr, uint8_t reg, uint16_t* data) {


	uint8_t failed_command;
	twi_data_t buf[7];

	buf[0].type = TWI_TYPE_START;

	buf[1].type = TWI_TYPE_TRANSMIT_ADDRESS;
	buf[1].byte = addr;

	buf[2].type = TWI_TYPE_TRANSMIT_DATA;
	buf[2].byte = reg;

	buf[3].type = TWI_TYPE_START;

	buf[4].type = TWI_TYPE_RECEIVE_ADDRESS;
	buf[4].byte = addr;

	buf[5].type = TWI_TYPE_RECEIVE_DATA;

	buf[6].type = TWI_TYPE_RECEIVE_DATA;

	if (twi_communicate(buf, 7, &failed_command) != 0) {
		Log_debug("command %d failed\n", failed_command);
		return SDDS_RT_FAIL;
	}

	*data = (buf[6].byte << 8);
	*data |= buf[5].byte;


	return SDDS_RT_OK;
}
