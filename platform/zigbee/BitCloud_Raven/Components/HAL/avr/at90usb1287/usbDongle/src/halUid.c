/**************************************************************************//**
  \file   uid.c

  \brief  Implementation of UID interface.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      6/02/09 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <i2c.h>
#include <uid.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// twi eeprom(at24c02b) address on i2c bus
#define AT24_DEVICE_ADDRESS  0xA0
#define SIZE_RANDOM_AREA     16

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
 UID discovery.
 Parameters:
   id - UID buffer pointer.
 Returns:
   0 - if UID of DS2411 has been found without error;
  -1 - if there are some errors during UID discovery.
******************************************************************************/
int HAL_ReadUid(uint64_t *id)
{
  HAL_i2cMode_t i2cMode;
  uint8_t state;
  uint8_t itr;
  uint8_t readData[SIZE_RANDOM_AREA];

  if (NULL == id)
    return -1;

  i2cMode.clockrate = I2C_CLOCK_RATE_250;
  if (-1 == HAL_OpenI2cPacket(&i2cMode))
    return -1;

  // disable twi interrupt
  TWCR &= (~(1 << TWIE));
  /////////////// start of dummy write  ////////////////////
  // send start condition
  TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);

  // wait for end of action
  while(!(TWCR & (1 << TWINT)));

  state = TWSR & 0xF8;
  if ((TWS_START != state) && (TWS_RSTART != state))
  {
    HAL_CloseI2cPacket();
    return -1;
  }
  // send at24 address + W
  TWDR =  AT24_DEVICE_ADDRESS;
  TWCR = (1 << TWINT) | (1 << TWEN);

  // wait for end of action
  while(!(TWCR & (1 << TWINT)));

  state = TWSR & 0xF8;
  if (TWS_MT_SLA_ACK != state)
  {
    HAL_CloseI2cPacket();
    return -1;
  }
  // send internal eeprom cell address (0)
  for (itr=0; itr<2; ++itr)
  {
    // send address byte
    TWDR =  0x00;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for end of action
    while(!(TWCR & (1 << TWINT)));

    state = TWSR & 0xF8;
    if (TWS_MT_DATA_ACK != state)
    {
      HAL_CloseI2cPacket();
      return -1;
    }
  }
  /////////////// end of dummy write  ////////////////////
  /////////////// start of data read ////////////////////
  // send start condition
  TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);

  // wait for end of action
  while(!(TWCR & (1 << TWINT)));

  state = TWSR & 0xF8;
  if ((TWS_START != state) && (TWS_RSTART != state))
  {
    HAL_CloseI2cPacket();
    return -1;
  }
  // send at24 address + R
  TWDR =  AT24_DEVICE_ADDRESS | 0x01;
  TWCR = (1 << TWINT) | (1 << TWEN);

  // wait for end of action
  while(!(TWCR & (1 << TWINT)));

  state = TWSR & 0xF8;
  if (TWS_MR_SLA_ACK != state)
  {
    HAL_CloseI2cPacket();
    return -1;
  }

  // send internal eeprom cell address (0)
  for (itr=0; itr<SIZE_RANDOM_AREA; itr++)
  {
    if ((SIZE_RANDOM_AREA-1) == itr)
    { // send nack on last data byte
      TWCR &= ~(1 << TWEA);
      TWCR = (1 << TWINT) | (1 << TWEN);
    }
    else
    { // send ack
      TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    }
    // wait for end of action
    while(!(TWCR & (1 << TWINT)));

    state = TWSR & 0xF8;
    if ((TWS_MR_DATA_ACK != state) && (TWS_MR_DATA_NACK != state))
    {
      HAL_CloseI2cPacket();
      return -1;
    }
    readData[itr] = TWDR;
  }
  /////////////// end of data read ////////////////////
  // send stop condition
  TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
  // wait for end of stop condition
  while(!(TWCR & (1 << TWSTO)));

  for (itr=0; itr<(SIZE_RANDOM_AREA >> 1); itr++)
  {
    ((uint8_t *)id)[itr] = readData[itr] ^ readData[itr + (SIZE_RANDOM_AREA >> 1)];
  }

  HAL_CloseI2cPacket();
  return 0;
}

// eof uid.c
