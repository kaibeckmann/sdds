#ifndef EXPERIMENTS_H_INCLUDED
#define EXPERIMENTS_H_INCLUDED

#include <stdint.h>
#include <sdds_types.h>

#define TWI_TI0_ADDRESS 0xc2
#define TWI_TI1_ADDRESS 0xc4
#define TWI_TI2_ADDRESS 0xc8

/* initialize the light sensor
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t init_light(void);

/* read the current value from the light sensor
 * higher values represent darker environments
 *
 * @param value light intensity [0,256)
 *
 * @return SDDS_RT_OK on success, SDDS_RT_FAIL on failure
 */
rc_t read_light(uint8_t *value);

rc_t swrst_ti(void);
rc_t setup_ti_one(uint8_t address);
rc_t setup_ti_all(void);
rc_t control_ti_led(uint8_t address, uint8_t led_index, uint8_t byte);

#endif
