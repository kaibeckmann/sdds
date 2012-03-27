/**************************************************************************//**
\file  halSleep.c

\brief The module to make power off mode.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    2/06/08 A. Khromykh - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halSleep.h>

/******************************************************************************
                   External variables section
******************************************************************************/
extern HalSleepControl_t halSleepControl;

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
  Prepares system for power-save, power-down.
  Power-down the mode is possible only when internal RC is used
  Parametres:
  none.
  Returns:
  -1 there is no possibility to power-down system.
******************************************************************************/
int HAL_Sleep(void)
{
  return 0;
}

/*******************************************************************************
  Makes MCU enter Idle mode.
*******************************************************************************/
void HAL_IdleMode(void)
{
}

/**************************************************************************//**
\brief Dummy function for compatibility with end device mode
\return
   0 - always.
******************************************************************************/
int HAL_StartSleepTimer(HAL_SleepTimer_t *sleepTimer)
{
  halSleepControl.sleepTimer = *sleepTimer;
  halSleepControl.sleepTimer.callback = halSleepControl.callback;
  HAL_StartAppTimer(&halSleepControl.sleepTimer);
  return 0;
}

// eof halSleep.c
