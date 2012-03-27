/**************************************************************************//**
\file  halSleep.h

\brief Interface to control sleep mode.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    2/06/08 A. Khromykh - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
#ifndef _HALSLEEP_H
#define _HALSLEEP_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sleep.h>
#include <appTimer.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define HAL_SleepTimer_t       HAL_AppTimer_t
#define HAL_StopSleepTimer     HAL_StopAppTimer

#define HAL_ACTIVE_MODE                    0
#define HAL_SLEEP_MODE                     1
#define HAL_SLEEP_TIMER_IS_STOPPED         0
#define HAL_SLEEP_TIMER_IS_STARTED         1
#define HAL_SLEEP_TIMER_IS_WAKEUP_SOURCE   0
#define HAL_EXT_IRQ_IS_WAKEUP_SOURCE       1

/******************************************************************************
                   Types section
******************************************************************************/
typedef struct
{
  HAL_WakeUpCallback_t callback;
  HAL_SleepTimer_t sleepTimer;
  uint8_t wakeupStation    : 1;
  uint8_t wakeupSource     : 1;
  uint8_t sleepTimerState  : 1;
} HalSleepControl_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief  dummy function for avr compatibility
\return
  0 - always
******************************************************************************/
int HAL_Sleep(void);

/***************************************************************************//**
\brief  Makes MCU enter Idle mode.
*******************************************************************************/
void HAL_IdleMode(void);

/**************************************************************************//**
\brief Dummy function for compatibility with end device mode
\return
   0 - always.
******************************************************************************/
int HAL_StartSleepTimer(HAL_SleepTimer_t *sleepTimer);

#endif /* _HALSLEEP_H */
// eof halSleep.h
