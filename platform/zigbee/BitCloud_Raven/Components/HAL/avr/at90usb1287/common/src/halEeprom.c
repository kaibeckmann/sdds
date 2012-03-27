/**************************************************************************//**
  \file  halEeprom.c

  \brief  Implementation of the hardware dependent the EEPROM module.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      5/12/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <atomic.h>
#include <halEeprom.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Writes a byte to EEPROM.
Parameters:
  EECRMask - mask that define capability of interrupt after byte writing.
  address - address of byte
  data - data.
Returns:
  none.
******************************************************************************/
void halEepromWrite(uint8_t EECRMask, uint16_t address, uint8_t data)
{
  while (EECR & (1 << EEPE)); // wait for completion of previous eeprom write
  while (SPMCSR & (1 << SPMEN)); // wait for completion of previous program memory write
  EEAR = address;
  EEDR = data;
  ATOMIC_SECTION_ENTER
    EECR  = EECRMask;
    EECR |= (1 << EEPE);
  ATOMIC_SECTION_LEAVE
}

/******************************************************************************
Interrupt handler.
******************************************************************************/
ISR(EE_READY_vect)
{
  EECR &= ~(1 << EERIE); //disable interrupt
  halSigEepromReadyInterrupt();
}

// eof helEeprom.c
