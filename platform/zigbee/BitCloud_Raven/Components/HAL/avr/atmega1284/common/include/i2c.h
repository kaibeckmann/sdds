/**************************************************************************//**
  \file i2c.h

  \brief Declarations of i2c interface.

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

#ifndef _I2C_H
#define _I2C_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <i2cPacket.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
/** \brief TWI status codes. */
enum
{
  TWS_BUSERROR      = 0x00,
  TWS_START         = 0x08,
  TWS_RSTART        = 0x10,
  TWS_MT_SLA_ACK    = 0x18,
  TWS_MT_SLA_NACK   = 0x20,
  TWS_MT_DATA_ACK   = 0x28,
  TWS_MT_DATA_NACK  = 0x30,
  TWS_M_ARB_LOST    = 0x38,
  TWS_MR_SLA_ACK    = 0x40,
  TWS_MR_SLA_NACK   = 0x48,
  TWS_MR_DATA_ACK   = 0x50,
  TWS_MR_DATA_NACK  = 0x58
};

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Inits TWI module. Setup the speed of TWI.
\param[in]
  i2cMode - the speed of TWI.
******************************************************************************/
void halInitI2c(HAL_i2cMode_t *i2cMode);

/**************************************************************************//**
\brief Notification about the start condition was sent.
******************************************************************************/
void halSendStartDoneI2c(void);

/**************************************************************************//**
\brief Notification that byte was written to the TWI.
\param[in]
  result - contains result of previous operation.
******************************************************************************/
void halWriteDoneI2c(void);

/**************************************************************************//**
\brief Notification that byte was read from the TWI.
\param[in]
  data - contains byte that was read.
******************************************************************************/
void halReadDoneI2c(uint8_t data);

/**************************************************************************//**
\brief Notification that last byte was read from the TWI. Needs send STOP condition
on bus.
\param[in]
  data - contains byte that was read.
******************************************************************************/
void halReadLastByteDoneI2c(uint8_t data);

/**************************************************************************//**
\brief Notification that address byte was written to the TWI and was read ACK.
Starts reading data.
******************************************************************************/
void halMasterReadWriteAddressAckI2c(void);

/**************************************************************************//**
\brief Resets TWI bus and i2c HAL.
******************************************************************************/
void halI2cBusReset(void);

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/**************************************************************************//**
\brief Loop for waiting for end of stop condition on bus.
******************************************************************************/
INLINE void halWaitEndOfStopStation(void)
{
  loop_until_bit_is_clear(TWCR, TWSTO);
}

/**************************************************************************//**
\brief Enables interrupt on TWI.
******************************************************************************/
INLINE void halInterruptEnableI2c(void)
{
  TWCR |= (1 << TWIE);
}

/**************************************************************************//**
\brief Disables interrupt on TWI.
******************************************************************************/
INLINE void halInterruptDisableI2c(void)
{
  TWCR &= (~(1 << TWIE));
}

/*************************************************************************//**
\brief Returns byte that was read from the TWI.
******************************************************************************/
INLINE uint8_t halReadByteI2c(void)
{
  return TWDR;
}

/*************************************************************************//**
\brief Resets the TWI.
******************************************************************************/
INLINE void halResetI2c(void)
{
  TWCR = ((1 << TWSTO) | (1 << TWINT));  // Reset TWI
}

/**************************************************************************//**
\brief Begins writing an byte to TWI.
\param[in]
  data - an byte for sending.
******************************************************************************/
INLINE void halWriteI2c(uint8_t data)
{
  TWDR =  data;
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
}

/**************************************************************************//**
\brief Begins read an byte from TWI.
\param[in]
  ack - defines the need to send ACK after an byte was recieved.
******************************************************************************/
INLINE void halReadI2c(bool ack)
{
  if (ack)
    TWCR |= (1 << TWEA);
  else
    TWCR &= ~(1 << TWEA);

  TWCR |= ((1 << TWINT) | (1 << TWIE) | (1 << TWEN));  // Trigger the TWI
}

/**************************************************************************//**
\brief Directs TWI to send stop condition.
******************************************************************************/
INLINE void halSendStopI2c(void)
{
  TWCR = ((1 << TWSTO) | (1 << TWINT) | (1 << TWEN));
}

/**************************************************************************//**
\brief Directs the TWI to send start condition.
******************************************************************************/
INLINE void halSendStartI2c(void)
{
  TWCR = ((1 << TWSTA) | (1 <<TWINT) | (1 << TWEN) | (1 << TWIE));
}

#endif /* _I2C_H*/
// eof i2c.h
