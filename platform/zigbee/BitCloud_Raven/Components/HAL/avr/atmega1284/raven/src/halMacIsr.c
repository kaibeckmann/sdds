/**************************************************************************//**
  \file  halMacIsr.c

  \brief mac interrups implementation.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      14/01/08 A. Mandychev - Created.
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <halMacIsr.h>
#include <halRfCtrl.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#if defined(HAL_3d6864MHz)
  #define HAL_RTIMER_INTERVAL_CALCULATE(period)    (period >> 1)
#elif defined(HAL_4MHz)
  #define HAL_RTIMER_INTERVAL_CALCULATE(period)    (period >> 1)
#elif defined(HAL_7d3728MHz)
  #define HAL_RTIMER_INTERVAL_CALCULATE(period)    (period)
#elif defined(HAL_8MHz)
  #define HAL_RTIMER_INTERVAL_CALCULATE(period)    (period)
#endif

/******************************************************************************
                   Global variables section
******************************************************************************/
RTimerDescr_t __rtimer;

/******************************************************************************
                    Prototypes section
******************************************************************************/
/******************************************************************************
  Initializes Rtimer and RF ext. interrupts.
******************************************************************************/
void HAL_InitMacIsr(void);

/******************************************************************************
  Redirect interrupt event depending on the TrxState.
  Parameters: none.
  Returns: none.
******************************************************************************/
void phyDispatcheRTimerEvent(void);

/******************************************************************************
  Redirect interrupt event depending on the TrxState.
  Parameters: none.
  Returns: none.
******************************************************************************/
void phyDispatcheRfInterrupt(void);

/******************************************************************************
                    Implementations section
******************************************************************************/
/******************************************************************************
  Initializes Rtimer.
******************************************************************************/
void HAL_InitMacIsr(void)
{
  __rtimer.mode = HAL_RTIMER_STOPPED_MODE;
  HAL_InitRfIrq();
}

/******************************************************************************
  Starts RTimer. Function should be invoked in critical section.
  Parameters:
    source  - source of invocation.
    mode    - RTimer mode.
    period  - RTimer period.
******************************************************************************/
bool HAL_StartRtimer(HAL_RTimerMode_t mode, uint16_t period)
{
  if (HAL_RTIMER_STOPPED_MODE != __rtimer.mode)
    return false;

  __rtimer.period    = HAL_RTIMER_INTERVAL_CALCULATE(period);
  __rtimer.mode      = mode;
  __rtimer.nextEvent = TCNT1 + __rtimer.period;
  if (__rtimer.nextEvent > TOP_TIMER_COUNTER_VALUE)
    __rtimer.nextEvent -= TOP_TIMER_COUNTER_VALUE;
  OCR1B = __rtimer.nextEvent;
  // clear possible interrupt by setting logical one.
  TIFR1 = (1 << OCF1B);
  // enable interrupt
  TIMSK1 |= (1 << OCIE1B);
  return true;
}

/******************************************************************************
  Stops RTimer. Function should be invoked in critical section.
******************************************************************************/
void HAL_StopRtimer(void)
{
  // clear possible interrupt
  TIFR1 &= ~(1 << OCF1B);
  // disable interrupt
  TIMSK1 &= ~(1 << OCIE1B);
  __rtimer.mode = HAL_RTIMER_STOPPED_MODE;
}

/******************************************************************************
  Output compare unit (channel B) interrupt handler.
******************************************************************************/
ISR(TIMER1_COMPB_vect)
{
  if (HAL_RTIMER_ONE_SHOT_MODE == __rtimer.mode)
  {
    TIMSK1 &= ~(1 << OCIE1B);
    __rtimer.mode = HAL_RTIMER_STOPPED_MODE;
  }
  else
  {
    __rtimer.nextEvent += __rtimer.period;
    if (__rtimer.nextEvent > TOP_TIMER_COUNTER_VALUE)
      __rtimer.nextEvent -= TOP_TIMER_COUNTER_VALUE;
    OCR1B = __rtimer.nextEvent;
  }
  phyDispatcheRTimerEvent();
}

/****************************************************************
  Interrupt service routine.
  Do not move this ISR! It could be omitted in your project.
****************************************************************/
ISR(TIMER1_CAPT_vect)
{
  phyDispatcheRfInterrupt();
}

// eof halMacIsr.c
