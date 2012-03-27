/**************************************************************************//**
  \file   halUid.c

  \brief  Implementation of UID interface.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      7/12/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <gpio.h>
#include <uid.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
  Writes/reads byte to/from SPI.
  parameters: value - byte to write.
  Returns:    the byte which was read.
******************************************************************************/
static uint8_t halWriteByteSpi(uint8_t value)
{
  SPDR = value;
  asm("nop");   // This "nop" tunes up the "while" to reduce time for SPIF flag detecting.
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}

/******************************************************************************
 Returns number which was read from external eeprom.
 Parameters:
   id - UID buffer pointer.
 Returns:
   0 - if UID of DS2411 has been found without error;
  -1 - if there are some erros during UID discovery.
******************************************************************************/
int HAL_ReadUid(uint64_t *id)
{
  uint8_t command = 0x03;
  uint8_t address = 0;
  uint8_t itr;

  if (!id)
    return -1;

  GPIO_SPI_CS_set();
  GPIO_SPI_MISO_make_in();
  GPIO_SPI_MOSI_make_out();
  GPIO_SPI_SCK_make_out();
  GPIO_HW_SPI_CS_make_out();
  GPIO_SPI_CS_make_out();

  SPCR = ((1 << SPE) | (1 << MSTR));               // SPI enable, master mode.
  SPSR = (1 << SPI2X);                             // rate = fosc/2

  GPIO_SPI_CS_clr();

  halWriteByteSpi(command);
  halWriteByteSpi(address);
  for (itr=0; itr<sizeof(uint64_t); itr++)
    *((uint8_t *)id+itr) = halWriteByteSpi(address);

  GPIO_SPI_CS_set();

  GPIO_HW_SPI_CS_make_out();
  GPIO_SPI_MOSI_make_in();
  GPIO_SPI_SCK_make_in();
  GPIO_SPI_CS_make_in();

  return 0;
}

// eof uid.c
