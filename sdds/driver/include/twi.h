#ifndef TWI_H_INCLUDED
#define TWI_H_INCLUDED

#include "twi-type.h"

#include "sdds_types.h"

/**
 * @struct
 * two wire interface module
 * -------------------------
 *
 * after twi_init you can build twi_data datastructures
 * and pass them to twi_communicate
 * to configure the i/o pins and frequency check 'twi-config.h'
 */

struct twi_data
{
	enum twi_type type;
	uint8_t byte;
};

typedef struct twi_data twi_data_t;

/**
 * initialize the twi
 */
void twi_init(void);

/**
 * communicate using the twi module
 *
 * @param data an array of twi_data command/byte pairs
 * @param amount the amount of passed array members
 * @param failed_command an output parameter, which will tell which command failed, if any
 *
 * @return 0, 1, -1 or 2
 *         0 on success
 *         1 if arbitration was lost
 *         -1 on protocol errors
 *         2 if ack/nack received although the opposite was supposed to happen
 */
int8_t twi_communicate(struct twi_data *data, uint8_t amount, uint8_t *failed_command);

/**
 * read a 16bit word from the twi slave
 *
 * @param addr 7bit Address of the twi slave. The address have to be shiffted by 1 bit, so the bit is free
 * @param reg The register which shall be read from
 * @param data Pointer to the 16 bit variable where the result shall be written
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t twi_readWord(uint8_t addr, uint8_t reg, uint16_t* data);

/**
 * read a 8bit word from the twi slave
 *
 * @param addr 7bit Address of the twi slave. The address have to be shiffted by 1 bit, so the bit is free
 * @param reg The register which shall be read from
 * @param data Pointer to the 8 bit variable where the result shall be written
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t twi_readByte(uint8_t addr, uint8_t reg, uint8_t* data);


/**
 * write a 16 bit value to a register of a twi slave
 *
 * @param addr 7bit Address of the twi slave. The address have to be shiffted by 1 bit, so the bit is free
 * @param reg The register which shall be written to
 * @param data the data which shall be written
 */
rc_t twi_writeWord(uint8_t addr, uint8_t reg, uint16_t data);

/**
 * write a 8 bit value to a register of a twi slave
 *
 * @param addr 7bit Address of the twi slave. The address have to be shiffted by 1 bit, so the bit is free
 * @param reg The register which shall be written to
 * @param data the data which shall be written
 */
rc_t twi_writeByte(uint8_t addr, uint8_t reg, uint8_t data);

#endif
