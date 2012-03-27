/***************************************************************************//**
  \file halRfCtrl.h

  \brief Types and constants declaration for IEEE802.15.4 PHY implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    28/05/07 A. Luzhetsky - Created.
    06/08/07 A. Mandychev, E. Ivanov - Modified.
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALRFCTRL_H
#define _HALRFCTRL_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <types.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum
{
  HAL_FREQ_NOCLK,
  HAL_FREQ_1MHZ,
  HAL_FREQ_2MHZ,
  HAL_FREQ_4MHZ,
  HAL_FREQ_8MHZ,
  HAL_FREQ_16MHZ
} HalSysFreq_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
  Delay in us
******************************************************************************/
void HAL_Delay(uint8_t us);

/******************************************************************************
  Clears the irq.
******************************************************************************/
void HAL_ClearRfIrqFlag(void);

/******************************************************************************
  Enables the irq.
******************************************************************************/
void HAL_EnableRfIrq(void);

/******************************************************************************
  Disables the irq.
******************************************************************************/
uint8_t HAL_DisableRfIrq(void);

/******************************************************************************
  Sets SLP_TR pin to 1.
******************************************************************************/
void HAL_SetRfSlpTr(void);

/******************************************************************************
  Clears SLP_TR pin to 0.
******************************************************************************/
void HAL_ClearRfSlpTr(void);

/******************************************************************************
  Makes SLP_TR pin as input.
******************************************************************************/
void HAL_MakeInRfSlpTr(void);

/******************************************************************************
  Makes SLP_TR pin as input.
******************************************************************************/
void HAL_MakeOutRfSlpTr(void);

/******************************************************************************
  Sets RST_TR pin to 1.
******************************************************************************/
void HAL_SetRfRst(void);

/******************************************************************************
  Clears RST_TR pin to 1.
******************************************************************************/
void HAL_ClearRfRst(void);

/******************************************************************************
  Init pins that controls RF chip.
******************************************************************************/
void HAL_InitRfPins(void);

/******************************************************************************
  Inits Atmega IRQ pin.
******************************************************************************/
void HAL_InitRfIrq(void);

/******************************************************************************
  Returns current frequency code.
******************************************************************************/
HalSysFreq_t HAL_GetRfFreq(void);

/**************************************************************************//**
  \brief Enables RX TX indicator for radio if that is supported.
******************************************************************************/
void HAL_EnableRxTxSwitcher(void);

#endif /* _HALRFCTRL_H */

// eof halRfCtrl.h
