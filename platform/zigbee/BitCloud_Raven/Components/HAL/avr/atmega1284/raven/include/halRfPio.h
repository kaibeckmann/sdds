/***************************************************************************//**
  \file halRfPio.h

  \brief AT86RF230 control pins declarations.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    29/05/07 A. Luzhetsky - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALRFPIO_H_
#define _HALRFPIO_H_

#include <gpio.h>

HAL_ASSIGN_PIN(RF_TST,    B, 0);
// Macros for the RF_RST pin manipulation.
HAL_ASSIGN_PIN(RF_RST,    B, 1);
// Macros for the RF_SLP_TR pin manipulation.
HAL_ASSIGN_PIN(RF_SLP_TR, B, 3);
// Macros for the SPI_CS pin manipulation.
HAL_ASSIGN_PIN(SPI_CS,    B, 4);
// Macros for the SPI_MOSI pin manipulation.
HAL_ASSIGN_PIN(SPI_MOSI,  B, 5);
// Macros for the SPI_MISO pin manipulation.
HAL_ASSIGN_PIN(SPI_MISO,  B, 6);
// Macros for the SPI_SCK pin manipulation.
HAL_ASSIGN_PIN(SPI_SCK,   B, 7);
// Macros for the RF_IRQ pin manipulation.
HAL_ASSIGN_PIN(RF_IRQ,    D, 6);

#endif /* _HALRFPIO_H_ */
