/**************************************************************************//**
  \file  halInit.c

  \brief HAL start up module.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
     29/06/07 E. Ivanov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halAppClock.h>
#include <halSleepTimerClock.h>
#include <halRfSpi.h>
#include <halIrq.h>
#include <halInterrupt.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Performs start up HAL initialization.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
void HAL_Init(void)
{
  HAL_InitRfSpi();
  /* start sleep time */
  halStartSleepTimerClock();
  /* initialization work frequency &
   *  start calibration */
  halInitFreq();
  /* initialization and start application timer */
  halInitAppClock();
  // workaround
  TIMSK1 &= ~(1 << ICIE1);    // disable interrupt from RF - cause of 1284P power reset issue.
  TIFR1 |= (1 << ICF1);       // cause of 1284P power reset issue.
  /* global enable interrupt*/
  HAL_EnableInterrupts();
}
// eof halInit.c
