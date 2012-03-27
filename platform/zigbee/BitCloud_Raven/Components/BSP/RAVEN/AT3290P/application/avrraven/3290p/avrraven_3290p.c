// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief  This file implements the main loop for the AVR Raven application program
 *
 * \par Application note:
 *      AVR2017: RZRAVEN FW
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: htttp://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Id: avrraven_3290p.c 41767 2008-05-15 18:53:24Z hmyklebust $
 *
 * Copyright (c) 2008 , Atmel Corporation. All rights reserved.
 *
 * Licensed under Atmel’s Limited License Agreement (RZRaven Evaluation and Starter Kit). 
 *****************************************************************************/


/*================================= INCLUDES         =========================*/

// 
#include <stdint.h>
#include <stdbool.h>

#include "compiler.h"
#include "wdt_avr.h"

// Peripherals
#include "led.h"
#include "lcd.h"

// Modules
#include "temp.h"
#include "sipc.h"
#include "battery.h"
#include "sleep_avr.h"
#include "tick.h"
#include "asy_tmr.h"
#include "avrraven_3290p.h"

// Kernel
#include "vrt_kernel.h"
#include "vrt_mem.h"

// Misc.
#include "rvn_loc.h"
#include "cmd_if_3290p.h"
#include "macros.h"
#include "int_evt.h"
#include "error.h"

#include "math.h"


/*========================= PUBLIC VARIABLES         =========================*/
avrraven_t avrraven;

/*========================= PRIVATE FUNCTIONS        =========================*/

/*! \brief  General MCU initialization
 *
 * \retval true     Initialization OK
 * \retval false    Initialization FAIL
 */
static bool avr_init(void);


/*! \brief Thid function evaluates if the VRT system is in idle state. That is
 *         no tasks running.
 *
 *  \retval true The VRT framework is ready to SLEEP.
 *  \retval false The VRT framework is not ready to SLEEP.
 */
static bool vrt_in_idle(void);


/*! \brief  Enter sleep mode
 */
static void go_to_sleep(void);


/*! \brief  Error handler for fatal errors
 *
 */
void error_handler(const char* str, int num);

/*========================= IMPLEMENTATION           =========================*/
#if defined(__ICCAVR__)
#pragma type_attribute = __task
void main(void) {
#else
int main(void) {
#endif
    
    // System initialization
    if (true != avr_init()) {               // Generic MCU initialization
        ERROR();
    } else if (true != vrt_init()) {        // Kernel init
        ERROR();
    } else if (true != cmd_if_init()) {     // Command interface (does also "sipc_init()")
        ERROR();
    } else if (tick_init() != 0) {          // System tick
        ERROR();
    }
    
    // Test if basic user configuration is valid. If not, load with default values
    avrraven.user_config.basic_valid             = USER_CONFIG_BASIC_VALID_ID;
    avrraven.user_config.panid                   = 0xBABE;
    avrraven.user_config.channel                 = 11;
    avrraven.user_config.extended_valid          = USER_CONFIG_EXTENDED_VALID_ID;
    avrraven.user_config.unit.temp               = TEMP_UNIT_CELCIUS;
    //avrraven.user_config.unit.clock              = TIME_CLOCK_UNIT_24;
    avrraven.user_config.txtmsg_preview          = true;
    avrraven.user_config.fw_upgr_auto            = true;
    avrraven.user_config.fw_rcv_auto             = true;
    avrraven.user_config.join_auto               = true;
    avrraven.user_config.show_hidden_files       = true;
    avrraven.user_config.show_system_files       = true;
    avrraven.user_config.debug_enable            = false;
    avrraven.user_config.data_flash_valid        = false;
    avrraven.user_config.lcd.contrast            = LCD_CONTRAST_2_75;
    avrraven.user_config.lcd.scrolling           = LCD_SCROLLING_SLOW;

    
    // Load default configuration for LCD driver and read constrast level from user variable
    lcd_config_t lcd_config = LCD_DEFAULT_CONFIG;
    lcd_config.contrast = avrraven.user_config.lcd.contrast;
    lcd_config.scrolling = avrraven.user_config.lcd.scrolling;

    
    // Driver initialization
    if (asy_tmr_init() != 0) {              // Asynchronous timer
        ERROR();
    } else if (led_init() != 0) {           // Raven eye LED driver
        ERROR();
    } else if (lcd_init(lcd_config) != 0) { // Display driver
        ERROR();
    } else if (battery_init() != 0) {       // Battery icon driver
        ERROR();
    } else if (temp_init() != 0) {
      ERROR();
    }

    int_evt_update_batt((void*)NULL);
    
    // Set initial state
    avrraven.status.state = STATE_STARTUP;
    
    // Enable interrupts
    sei();
    
    
    // Register periodic events
    asy_tmr_get(int_evt_update_batt, (void*)NULL, 1000);
    
    //disable JTAG for proper temperature sensor reading
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);

    // Post system startup event
    vrt_post_event(int_evt_startup, (void*)NULL);
    
    lcd_symbol_battery_init();
    
    // Main loop, 
    while (true) {
        vrt_dispatch_event();
    
        // Serve asynchronous timer
        asy_tmr_task(tick_count_get());
        
        if (true == vrt_in_idle()) {
            go_to_sleep();
        }
    }
}

static bool avr_init(void) {
    /* The input buffers must be disabled before the ADC, because the disabling
     * is handled by the ADC module.
     */
	DIDR0 = (1 << ADC7D) | // Disable digital ionput buffer for analog input pins.
	        (1 << ADC6D) |
	        (1 << ADC5D) |
	        (1 << ADC4D) |
	        (1 << ADC3D) |
	        (1 << ADC2D) |
	        (1 << ADC1D) |
	        (1 << ADC0D);
	DIDR1 = (1 << AIN1D) |
	        (1 << AIN0D);

    // NOTE: Modules are turned on/off by driver.
	PRR = (1 << PRLCD)    |
	      (1 << PRTIM1)   |
	      (1 << PRSPI)    |
        (1 << PRUSART0) |
	      (1 << PRADC);

	ACSR |= (1 << ACD); // Disable Analog Comparator.

    /* System is started with the CLKPR set to divide by eight. To run at 4 MHz
     * the value of the CLKPR must be updated.
     */
    ENTER_CRITICAL_REGION();
    CLKPR = (1<<CLKPCE);
    CLKPR = ((0<<CLKPS3)|(0<<CLKPS2)|(0<<CLKPS1)|(1<<CLKPS0));
    LEAVE_CRITICAL_REGION();
    
    // Set default idle sleep mode
    SMCR = (0<<SM2)|(1<<SM1)|(0<<SM0);

    return true;
}


static bool vrt_in_idle(void) {
    
    bool idle = false;
    if (0 != VRT_GET_ITEMS_USED()) {
    } else {
        idle = true;
    }
    
    return idle;
}


void error_handler(const char* str, int num) {}


static void go_to_sleep(void)
{
    avr_set_sleep_mode(SLEEP_IDLE);
    avr_sleep_enable();
    avr_mcu_sleep();
}


void reboot(void)
{
    watchdog_timeout_set(WDT_TIMEOUT_16K);
    watchdog_enable();
    while(1);
}
/*EOF*/
