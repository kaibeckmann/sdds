// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief  Handlers for all internal(3290p only) events
 *
 * \par Application note:
 *      AVR2017: RZRAVEN FW
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Id: numedit.c 41136 2008-04-29 11:43:51Z hmyklebust $
 *
 * Copyright (c) 2008 , Atmel Corporation. All rights reserved.
 *
 * Licensed under Atmel’s Limited License Agreement (RZRaven Evaluation and Starter Kit). 
 *****************************************************************************/


/*========================= INCLUDES                 =========================*/
#include "int_evt.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "sipc.h"
#include "macros.h"
#include "battery.h"

#include "led.h"
#include "lcd.h"

#include "tick.h"

#include "rvn_loc.h"
#include "avrraven_3290p.h"

//! \addtogroup applCmdAVRRAVEN3290p
//! @{
/*========================= MACROS                   =========================*/

/*========================= TYPEDEFS                 =========================*/

/*========================= PUBLIC VARIABLES         =========================*/
//! Generic numeric editor buffer
uint16_t numedit_buffer;

/*========================= PRIVATE VARIABLES        =========================*/

/*========================= PUBLIC FUNCTIONS         =========================*/

/*========================= PRIVATE FUNCTIONS        =========================*/

/*========================= IMPLEMENTATION           =========================*/
void int_evt_startup(void* evt)
{
//  lcd_print_msg_none();
//  lcd_symbol_set(LCD_SYMBOL_RX);
//  uint8_t i;
//  for (i = 0; i < LCD_CMD_TOTAL_NUMBER; i++)
//   lcd_func_ptrs[i].func();
}

void int_evt_lcd_shift_left(void* evt)
{
    lcd_text_shift_left();
}

void int_evt_lcd_cursor_toggle(void* evt)
{
    lcd_cursor_toggle();
}

void int_evt_lcd_num_refresh(void* evt)
{
    lcd_num_refresh();
}

void int_evt_update_batt(void* evt)
{
    int16_t vcc_batt = battery_voltage_read();
    
    lcd_symbol_battery_empty();
    if (vcc_batt>2000) {
        lcd_symbol_set(LCD_SYMBOL_BAT_CAP1);
    }
    if (vcc_batt>2500) {
        lcd_symbol_set(LCD_SYMBOL_BAT_CAP2);
    }
    if (vcc_batt>2800) {
        lcd_symbol_set(LCD_SYMBOL_BAT_CAP3);
    }
}

void int_evt_show_clock(void* evt){}

void int_evt_toggle_num_digit(void* evt){}

void int_evt_audio(void* evt){}
//! @}

ISR(TIMER1_COMPA_vect){}
ISR(TIMER2_OVF_vect){ tick_handler(); }
ISR(PCINT0_vect){}
ISR(SPI_STC_vect){}
/*EOF*/
