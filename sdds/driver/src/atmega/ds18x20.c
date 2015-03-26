/*
 * ds18x20.c
 *
 *  Created on: Dec 10, 2012
 *      Author: k_beckma
 *
 *      c&p from hexabus
 */

/*********************************************************************************
 Title: DS18X20-Functions via One-Wire-Bus
 Author: Martin Thomas <eversmith@heizung-thomas.de>
 http://www.siwawi.arubi.uni-kl.de/avr-projects
 Software: avr-gcc 4.3.3 / avr-libc 1.6.7 (WinAVR 3/2010)
 Hardware: any AVR - tested with ATmega16/ATmega32/ATmega324P and 3 DS18B20

 Partly based on code from Peter Dannegger and others.

 changelog:
 20041124 - Extended measurements for DS18(S)20 contributed by Carsten Foss (CFO)
 200502xx - function DS18X20_read_meas_single
 20050310 - DS18x20 EEPROM functions (can be disabled to save flash-memory)
 (DRIVER_DS18X20_EEPROMSUPPORT in ds18x20.h)
 20100625 - removed inner returns, added static function for read scratchpad
 . replaced full-celcius and fractbit method with decicelsius
 and maxres (degreeCelsius*10e-4) functions, renamed eeprom-functions,
 delay in recall_e2 replaced by timeout-handling
 10100714 - ow_command_skip_last_recovery used for parasite-powerd devices so the
 strong pull-up can be enabled in time even with longer OW recovery times
 **********************************************************************************/

#include <stdlib.h>
#include <contiki.h>
#include <contiki-net.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>

#include <stdarg.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "ds18x20.h"
#include "ow.h"
#include "crc8.h"

#include "driver.h"
#include "sdds_types.h"
#include "Log.h"

#define PRINTF(FORMAT,args...) printf_P(PSTR(FORMAT),##args)


/* return values */
#define RETURN_DS18X20_OK 0x00
#define RETURN_DS18X20_ERROR 0x01
#define RETURN_DS18X20_START_FAIL 0x02
#define RETURN_DS18X20_ERROR_CRC 0x03

#define RETURN_DS18X20_INVALID_DECICELSIUS 2000

#define RETURN_DS18X20_POWER_PARASITE 0x00
#define RETURN_DS18X20_POWER_EXTERN 0x01

#define RETURN_DS18X20_CONVERSION_DONE 0x00
#define RETURN_DS18X20_CONVERTING 0x01

/* DS18X20 specific values (see datasheet) */
#define DRIVER_CONF_DS18S20_FAMILY_CODE 0x10
#define DRIVER_CONF_DS18B20_FAMILY_CODE 0x28
#define DRIVER_CONF_DS1822_FAMILY_CODE 0x22

#define DRIVER_CONF_DS18X20_CONVERT_T 0x44
#define DRIVER_CONF_DS18X20_READ 0xBE
#define DRIVER_CONF_DS18X20_WRITE 0x4E
#define DRIVER_CONF_DS18X20_EE_WRITE 0x48
#define DRIVER_CONF_DS18X20_EE_RECALL 0xB8
#define DRIVER_CONF_DS18X20_READ_POWER_SUPPLY 0xB4

#define DRIVER_CONF_DS18B20_CONF_REG 4
#define DRIVER_CONF_DS18B20_9_BIT 0
#define DRIVER_CONF_DS18B20_10_BIT (1<<5)
#define DRIVER_CONF_DS18B20_11_BIT (1<<6)
#define DRIVER_CONF_DS18B20_12_BIT ((1<<6)|(1<<5))
#define DRIVER_CONF_DS18B20_RES_MASK ((1<<6)|(1<<5))

// undefined bits in LSB if 18B20 != 12bit
#define DRIVER_CONF_DS18B20_9_BIT_UNDF ((1<<0)|(1<<1)|(1<<2))
#define DRIVER_CONF_DS18B20_10_BIT_UNDF ((1<<0)|(1<<1))
#define DRIVER_CONF_DS18B20_11_BIT_UNDF ((1<<0))
#define DRIVER_CONF_DS18B20_12_BIT_UNDF 0

// conversion times in milliseconds
#define DRIVER_CONF_DS18B20_TCONV_12BIT 750
#define DRIVER_CONF_DS18B20_TCONV_11BIT DS18B20_TCONV_12_BIT/2
#define DRIVER_CONF_DS18B20_TCONV_10BIT DS18B20_TCONV_12_BIT/4
#define DRIVER_CONF_DS18B20_TCONV_9BIT DS18B20_TCONV_12_BIT/8
#define DRIVER_CONF_DS18S20_TCONV DS18B20_TCONV_12_BIT

// constant to convert the fraction bits to cel*(10^-4)
#define DRIVER_CONF_DS18X20_FRACCONV 625

// scratchpad size in bytes
#define DRIVER_CONF_DS18X20_SP_SIZE 9

// DS18X20 EEPROM-Support
#define DRIVER_CONF_DS18X20_WRITE_SCRATCHPAD 0x4E
#define DRIVER_CONF_DS18X20_COPY_SCRATCHPAD 0x48
#define DRIVER_CONF_DS18X20_RECALL_E2 0xB8
#define DRIVER_CONF_DS18X20_COPYSP_DELAY 10 /* ms */
#define DRIVER_CONF_DS18X20_TH_REG 2
#define DRIVER_CONF_DS18X20_TL_REG 3

#define DRIVER_CONF_DS18X20_DECIMAL_CHAR '.'


#if DRIVER_DS18X20_EEPROMSUPPORT
// for 10ms delay in copy scratchpad
#include <util/delay.h>
#endif /* DRIVER_DS18X20_EEPROMSUPPORT */

/*----------- start of "debug-functions" ---------------*/

#if DRIVER_DS18X20_VERBOSE
#if (!DRIVER_DS18X20_DECICELSIUS)
#error "DRIVER_DS18X20_DECICELSIUS must be enabled for verbose-mode"
#endif
#endif

uint8_t DS18X20_find_sensor(uint8_t *diff, uint8_t id[]);
uint8_t DS18X20_get_power_status(uint8_t id[]);
uint8_t DS18X20_start_meas( uint8_t with_external, uint8_t id[]);
// returns 1 if conversion is in progress, 0 if finished
// not available when parasite powered
uint8_t DS18X20_conversion_in_progress(void);


#if DS18X20_MAX_RESOLUTION
// temperature unit for max. resolution is °C * 10e-4
// examples: -250625 -> -25.0625°C, 1250000 -> 125.0000 °C
uint8_t DS18X20_read_maxres( uint8_t id[], int32_t *temperaturevalue );
#endif /* DS18X20_MAX_RESOLUTION */


#if DRIVER_DS18X20_EEPROMSUPPORT
// write th, tl and config-register to scratchpad (config ignored on DS18S20)
uint8_t DS18X20_write_scratchpad( uint8_t id[], uint8_t th, uint8_t tl, uint8_t conf);
// read scratchpad into array SP
uint8_t DS18X20_read_scratchpad( uint8_t id[], uint8_t sp[], uint8_t n);
// copy values int scratchpad into DS18x20 eeprom
uint8_t DS18X20_scratchpad_to_eeprom( uint8_t with_power_extern, uint8_t id[] );
// copy values from DS18x20 eeprom into scratchpad
uint8_t DS18X20_eeprom_to_scratchpad( uint8_t id[] );
#endif /* DRIVER_DS18X20_EEPROMSUPPORT */



/* functions for debugging-output - undef DRIVER_DS18X20_VERBOSE in .h
 if you run out of program-memory */

static int16_t DS18X20_raw_to_decicelsius(uint8_t fc, uint8_t sp[]);
void DS18X20_show_id_uart(uint8_t *id, size_t n);
static uint8_t read_scratchpad(uint8_t id[], uint8_t sp[], uint8_t n);

uint8_t gSensorID[1][DRIVER_OW_ROMCODE_SIZE];

rc_t DS18X20_init() {

	ow_reset();

	// search for the sensor
	uint8_t id[DRIVER_OW_ROMCODE_SIZE];
	uint8_t diff;
	diff = DRIVER_OW_SEARCH_FIRST;
	uint8_t nSensors = 0;

	while ( diff != DRIVER_OW_LAST_DEVICE ) {
			DS18X20_find_sensor( &diff, &id[0] );
			if( diff == DRIVER_OW_PRESENCE_ERR ) {
				Log_error( "No Sensor found\n"  );
				break;
			}
			if( diff == DRIVER_OW_DATA_ERR ) {
				Log_error( "Bus Error \n" );
				break;
			}
			for (uint8_t i = 0; i < DRIVER_OW_ROMCODE_SIZE; i++ )
				gSensorID[nSensors][i] = id[i];

			Log_debug("sensor found: ");
			DS18X20_show_id_uart(id, DRIVER_OW_ROMCODE_SIZE);
			break;
	}


	return SDDS_RT_OK;
}

rc_t DS18X20_read_celsius(int16_t* temperature) {

	uint8_t sp[DRIVER_CONF_DS18X20_SP_SIZE];
	uint8_t ret;
	
	ow_reset();
	ret = read_scratchpad(gSensorID[0], sp, DRIVER_CONF_DS18X20_SP_SIZE);
	if (ret == RETURN_DS18X20_OK) {
		*temperature = DS18X20_raw_to_decicelsius(gSensorID[0][0], sp);
		return SDDS_RT_OK;
	} else {
		return SDDS_RT_FAIL;
	}
}

rc_t DS18X20_start_meassurement() {
    uint8_t ret;
    
    ret = DS18X20_start_meas(RETURN_DS18X20_POWER_EXTERN, gSensorID[0]);
    
    if (ret != RETURN_DS18X20_OK) {
        return SDDS_RT_FAIL;
    }
    
    return SDDS_RT_OK;
}

void DS18X20_show_id_uart(uint8_t *id, size_t n) {
	size_t i;

	for (i = 0; i < n; i++) {
		if (i == 0) {
			PRINTF(" FC: ");
		} else if (i == n - 1) {
			PRINTF(" CRC: ");
		}
		if (i == 1) {
			PRINTF(" SN: ");
		}
//uart_puthex_byte(id[i]);
		PRINTF("%X", id[i]);
		if (i == 0) {
			if (id[0] == DRIVER_CONF_DS18S20_FAMILY_CODE) {
				PRINTF(" (18S)");
			} else if (id[0] == DRIVER_CONF_DS18B20_FAMILY_CODE) {
				PRINTF(" (18B)");
			} else if (id[0] == DRIVER_CONF_DS1822_FAMILY_CODE) {
				PRINTF(" (22)");
			} else {
				PRINTF(" ( ? )");
			}
		}
	}
	if (crc8(id, DRIVER_OW_ROMCODE_SIZE))
		PRINTF(" CRC FAIL ");
	else
		PRINTF(" CRC O.K. ");
	PRINTF("\n");
}


/* find DS18X20 Sensors on 1-Wire-Bus
 input/ouput: diff is the result of the last rom-search
 *diff = DRIVER_OW_SEARCH_FIRST for first call
 output: id is the rom-code of the sensor found */
uint8_t DS18X20_find_sensor(uint8_t *diff, uint8_t id[]) {
	uint8_t go;
	uint8_t ret;

	ret = RETURN_DS18X20_OK;
	go = 1;
	do {
		*diff = ow_rom_search(*diff, &id[0]);
		if (*diff == DRIVER_OW_PRESENCE_ERR || *diff == DRIVER_OW_DATA_ERR
				|| *diff == DRIVER_OW_LAST_DEVICE) {
			go = 0;
			ret = RETURN_DS18X20_ERROR;
		} else {
			if (id[0] == DRIVER_CONF_DS18B20_FAMILY_CODE || id[0] == DRIVER_CONF_DS18S20_FAMILY_CODE
					|| id[0] == DRIVER_CONF_DS1822_FAMILY_CODE) {
				go = 0;
			}
		}
	} while (go);

	return ret;
}

/* get power status of DS18x20
 input: id = rom_code
 returns: RETURN_DS18X20_POWER_EXTERN or RETURN_DS18X20_POWER_PARASITE */
uint8_t DS18X20_get_power_status(uint8_t id[]) {
	uint8_t pstat;

	ow_reset();
	ow_command(DRIVER_CONF_DS18X20_READ_POWER_SUPPLY, id);
	pstat = ow_bit_io(1);
	ow_reset();
	return (pstat) ? RETURN_DS18X20_POWER_EXTERN : RETURN_DS18X20_POWER_PARASITE;
}

/* start measurement (CONVERT_T) for all sensors if input id==NULL
 or for single sensor where id is the rom-code */
uint8_t DS18X20_start_meas(uint8_t with_power_extern, uint8_t id[]) {
	uint8_t ret;

	ow_reset();
	if (ow_input_pin_state()) { // only send if bus is "idle" = high
		if (with_power_extern != RETURN_DS18X20_POWER_EXTERN) {
			ow_command_with_parasite_enable(DRIVER_CONF_DS18X20_CONVERT_T, id);
			/* not longer needed: ow_parasite_enable(); */
		} else {
			ow_command(DRIVER_CONF_DS18X20_CONVERT_T, id);
		}
		ret = RETURN_DS18X20_OK;
	} else {
		Log_error("DS18X20_start_meas: Short Circuit!\r");
		ret = RETURN_DS18X20_START_FAIL;
	}

	return ret;
}

// returns 1 if conversion is in progress, 0 if finished
// not available when parasite powered.
uint8_t DS18X20_conversion_in_progress(void) {
	return ow_bit_io(1) ? RETURN_DS18X20_CONVERSION_DONE : RETURN_DS18X20_CONVERTING;
}

static uint8_t read_scratchpad(uint8_t id[], uint8_t sp[], uint8_t n) {
	uint8_t i;
	uint8_t ret;

	ow_command(DRIVER_CONF_DS18X20_READ, id);
	for (i = 0; i < n; i++) {
		sp[i] = ow_byte_rd();
	}
	if (crc8(&sp[0], DRIVER_CONF_DS18X20_SP_SIZE)) {
		ret = RETURN_DS18X20_ERROR_CRC;
	} else {
		ret = RETURN_DS18X20_OK;
	}

	return ret;
}



/* convert scratchpad data to physical value in unit decicelsius */
static int16_t DS18X20_raw_to_decicelsius(uint8_t familycode, uint8_t sp[]) {
	uint16_t measure;
	uint8_t negative;
	int16_t decicelsius;
	uint16_t fract;

	measure = sp[0] | (sp[1] << 8);
//measure = 0xFF5E; // test -10.125
//measure = 0xFE6F; // test -25.0625

	if (familycode == DRIVER_CONF_DS18S20_FAMILY_CODE) { // 9 -> 12 bit if 18S20
	/* Extended measurements for DS18S20 contributed by Carsten Foss */
		measure &= (uint16_t) 0xfffe; // Discard LSB, needed for later extended precicion calc
		measure <<= 3; // Convert to 12-bit, now degrees are in 1/16 degrees units
		measure += (16 - sp[6]) - 4; // Add the compensation and remember to subtract 0.25 degree (4/16)
	}

// check for negative
	if (measure & 0x8000) {
		negative = 1; // mark negative
		measure ^= 0xffff; // convert to positive => (twos complement)++
		measure++;
	} else {
		negative = 0;
	}

// clear undefined bits for DS18B20 != 12bit resolution
	if (familycode == DRIVER_CONF_DS18B20_FAMILY_CODE || familycode == DRIVER_CONF_DS1822_FAMILY_CODE) {
		switch (sp[DRIVER_CONF_DS18B20_CONF_REG] & DRIVER_CONF_DS18B20_RES_MASK) {
		case DRIVER_CONF_DS18B20_9_BIT:
			measure &= ~(DRIVER_CONF_DS18B20_9_BIT_UNDF);
			break;
		case DRIVER_CONF_DS18B20_10_BIT:
			measure &= ~(DRIVER_CONF_DS18B20_10_BIT_UNDF);
			break;
		case DRIVER_CONF_DS18B20_11_BIT:
			measure &= ~(DRIVER_CONF_DS18B20_11_BIT_UNDF);
			break;
		default:
// 12 bit - all bits valid
			break;
		}
	}

	decicelsius = (measure >> 4);
	decicelsius *= 10;

// decicelsius += ((measure & 0x000F) * 640 + 512) / 1024;
// 625/1000 = 640/1024
	fract = (measure & 0x000F) * 640;
	if (!negative) {
		fract += 512;
	}
	fract /= 1024;
	decicelsius += fract;

	if (negative) {
		decicelsius = -decicelsius;
	}

	if ( /* decicelsius == 850 || */decicelsius < -550 || decicelsius > 1250) {
		return RETURN_DS18X20_INVALID_DECICELSIUS;
	} else {
		return decicelsius;
	}
}




#if DS18X20_MAX_RESOLUTION

static int32_t DS18X20_raw_to_maxres(uint8_t familycode, uint8_t sp[]) {
	uint16_t measure;
	uint8_t negative;
	int32_t temperaturevalue;

	measure = sp[0] | (sp[1] << 8);
//measure = 0xFF5E; // test -10.125
//measure = 0xFE6F; // test -25.0625

	if (familycode == DRIVER_CONF_DS18S20_FAMILY_CODE) { // 9 -> 12 bit if 18S20
	/* Extended measurements for DS18S20 contributed by Carsten Foss */
		measure &= (uint16_t) 0xfffe; // Discard LSB, needed for later extended precicion calc
		measure <<= 3; // Convert to 12-bit, now degrees are in 1/16 degrees units
		measure += (16 - sp[6]) - 4; // Add the compensation and remember to subtract 0.25 degree (4/16)
	}

// check for negative
	if (measure & 0x8000) {
		negative = 1; // mark negative
		measure ^= 0xffff; // convert to positive => (twos complement)++
		measure++;
	} else {
		negative = 0;
	}

// clear undefined bits for DS18B20 != 12bit resolution
	if (familycode == DRIVER_CONF_DS18B20_FAMILY_CODE || familycode == DRIVER_CONF_DS1822_FAMILY_CODE) {
		switch (sp[DRIVER_CONF_DS18B20_CONF_REG] & DRIVER_CONF_DS18B20_RES_MASK) {
		case DRIVER_CONF_DS18B20_9_BIT:
			measure &= ~(DRIVER_CONF_DS18B20_9_BIT_UNDF);
			break;
		case DRIVER_CONF_DS18B20_10_BIT:
			measure &= ~(DRIVER_CONF_DS18B20_10_BIT_UNDF);
			break;
		case DRIVER_CONF_DS18B20_11_BIT:
			measure &= ~(DRIVER_CONF_DS18B20_11_BIT_UNDF);
			break;
		default:
// 12 bit - all bits valid
			break;
		}
	}

	temperaturevalue = (measure >> 4);
	temperaturevalue *= 10000;
	temperaturevalue += (measure & 0x000F) * DRIVER_CONF_DS18X20_FRACCONV;

	if (negative) {
		temperaturevalue = -temperaturevalue;
	}

	return temperaturevalue;
}

uint8_t DS18X20_read_maxres(uint8_t id[], int32_t *temperaturevalue) {
	uint8_t sp[DRIVER_CONF_DS18X20_SP_SIZE];
	uint8_t ret;

	ow_reset();
	ret = read_scratchpad(id, sp, DRIVER_CONF_DS18X20_SP_SIZE);
	if (ret == RETURN_DS18X20_OK) {
		*temperaturevalue = DS18X20_raw_to_maxres(id[0], sp);
	}
	return ret;
}



#endif /* DS18X20_MAX_RESOLUTION */

#if DRIVER_DS18X20_EEPROMSUPPORT

uint8_t DS18X20_write_scratchpad(uint8_t id[], uint8_t th, uint8_t tl,
		uint8_t conf) {
	uint8_t ret;

	ow_reset();
	if (ow_input_pin_state()) { // only send if bus is "idle" = high
		ow_command(DRIVER_CONF_DS18X20_WRITE_SCRATCHPAD, id);
		ow_byte_wr(th);
		ow_byte_wr(tl);
		if (id[0] == DRIVER_CONF_DS18B20_FAMILY_CODE || id[0] == DRIVER_CONF_DS1822_FAMILY_CODE) {
			ow_byte_wr(conf); // config only available on DS18B20 and DS1822
		}
		ret = RETURN_DS18X20_OK;
	} else {
		Log_error("DS18X20_write_scratchpad: Short Circuit!\r");
		ret = RETURN_DS18X20_ERROR;
	}

	return ret;
}

uint8_t DS18X20_read_scratchpad(uint8_t id[], uint8_t sp[], uint8_t n) {
	uint8_t ret;

	ow_reset();
	if (ow_input_pin_state()) { // only send if bus is "idle" = high
		ret = read_scratchpad(id, sp, n);
	} else {
		Log_error("DS18X20_read_scratchpad: Short Circuit!\r");
		ret = RETURN_DS18X20_ERROR;
	}

	return ret;
}

uint8_t DS18X20_scratchpad_to_eeprom(uint8_t with_power_extern, uint8_t id[]) {
	uint8_t ret;

	ow_reset();
	if (ow_input_pin_state()) { // only send if bus is "idle" = high
		if (with_power_extern != RETURN_DS18X20_POWER_EXTERN) {
			ow_command_with_parasite_enable(DRIVER_CONF_DS18X20_COPY_SCRATCHPAD, id);
			/* not longer needed: ow_parasite_enable(); */
		} else {
			ow_command(DRIVER_CONF_DS18X20_COPY_SCRATCHPAD, id);
		}
		_delay_ms(DRIVER_CONF_DS18X20_COPYSP_DELAY); // wait for 10 ms
		if (with_power_extern != RETURN_DS18X20_POWER_EXTERN) {
			ow_parasite_disable();
		}
		ret = RETURN_DS18X20_OK;
	} else {
		Log_error("DS18X20_copy_scratchpad: Short Circuit!\r");
		ret = RETURN_DS18X20_START_FAIL;
	}

	return ret;
}

uint8_t DS18X20_eeprom_to_scratchpad(uint8_t id[]) {
	uint8_t ret;
	uint8_t retry_count = 255;

	ow_reset();
	if (ow_input_pin_state()) { // only send if bus is "idle" = high
		ow_command(DRIVER_CONF_DS18X20_RECALL_E2, id);
		while (retry_count-- && !(ow_bit_io(1))) {
			;
		}
		if (retry_count) {
			ret = RETURN_DS18X20_OK;
		} else {
			Log_error("DS18X20_recall_E2: timeout!\r");
			ret = RETURN_DS18X20_ERROR;
		}
	} else {
		Log_error("DS18X20_recall_E2: Short Circuit!\r");
		ret = RETURN_DS18X20_ERROR;
	}

	return ret;
}
#endif
