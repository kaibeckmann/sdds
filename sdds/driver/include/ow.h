/*
 * ow.h
 *
 *  Created on: 17 Aug 2012
 *      Author: k_beckma
 *
 *      c&p von hexabus
 *      adapted to driver structure
 */

#ifndef OW_H_
#define OW_H_

#include "sdds_types.h"
#include "driver.h"

/*******************************************/
/* Hardware connection */
/*******************************************/

/* Define DRIVER_OW_ONE_BUS if only one 1-Wire-Bus is used
in the application -> shorter code.
If not defined make sure to call ow_set_bus() before using
a bus. Runtime bus-select increases code size by around 300
bytes so use DRIVER_OW_ONE_BUS if possible */
#define DRIVER_OW_ONE_BUS

#ifdef DRIVER_OW_ONE_BUS

#define DRIVER_OW_PIN PE6
#define DRIVER_OW_IN PINE
#define DRIVER_OW_OUT PORTE
#define DRIVER_OW_DDR DDRE
#define DRIVER_OW_CONF_DELAYOFFSET 0

#else
#if ( F_CPU < 1843200 )
#warning | Experimental multi-bus-mode is not tested for
#warning | frequencies below 1,84MHz. Use OW_ONE_WIRE or
#warning | faster clock-source (i.e. internal 2MHz R/C-Osc.).
#endif
#define DRIVER_OW_CONF_CYCLESPERACCESS 13
#define DRIVER_OW_CONF_DELAYOFFSET ( (uint16_t)( ((DRIVER_OW_CONF_CYCLESPERACCESS) * 1000000L) / F_CPU ) )
#endif

// Recovery time (T_Rec) minimum 1usec - increase for long lines
// 5 usecs is a value give in some Maxim AppNotes
// 30u secs seem to be reliable for longer lines
//#define DRIVER_OW_RECOVERY_TIME 5 /* usec */
//#define DRIVER_OW_RECOVERY_TIME 300 /* usec */
#define DRIVER_OW_RECOVERY_TIME 10 /* usec */

// Use AVR's internal pull-up resistor instead of external 4,7k resistor.
// Based on information from Sascha Schade. Experimental but worked in tests
// with one DS18B20 and one DS18S20 on a rather short bus (60cm), where both
// sensores have been parasite-powered.
#define DRIVER_OW_USE_INTERNAL_PULLUP 1 /* 0=external, 1=internal */

/*******************************************/


#define DRIVER_OW_MATCH_ROM 0x55
#define DRIVER_OW_SKIP_ROM 0xCC
#define DRIVER_OW_SEARCH_ROM 0xF0

#define DRIVER_OW_SEARCH_FIRST 0xFF // start new search
#define DRIVER_OW_PRESENCE_ERR 0xFF
#define DRIVER_OW_DATA_ERR 0xFE
#define DRIVER_OW_LAST_DEVICE 0x00 // last device found

// rom-code size including CRC
#define DRIVER_OW_ROMCODE_SIZE 8

extern uint8_t ow_reset(void);

extern uint8_t ow_bit_io( uint8_t b );
extern uint8_t ow_byte_wr( uint8_t b );
extern uint8_t ow_byte_rd( void );

extern uint8_t ow_rom_search( uint8_t diff, uint8_t *id );

extern void ow_command( uint8_t command, uint8_t *id );
extern void ow_command_with_parasite_enable( uint8_t command, uint8_t *id );

extern void ow_parasite_enable( void );
extern void ow_parasite_disable( void );
extern uint8_t ow_input_pin_state( void );

#ifndef DRIVER_OW_ONE_BUS
extern void ow_set_bus( volatile uint8_t* in,
volatile uint8_t* out,
volatile uint8_t* ddr,
uint8_t pin );
#endif


#endif /* OW_H_ */
