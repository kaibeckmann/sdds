/**************************************************************************//**
  \file  halIrq.c

  \brief Implementation of HWD IRQ interface.

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
#include <halIrq.h>
#include <sleep.h>
#include <halSleepTimerClock.h>
#include <halAppClock.h>

/******************************************************************************
                   Global variables section
******************************************************************************/
IrqCallback_t IrqCallbackList[HAL_NUM_IRQ_LINES] = {NULL, NULL};

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Sets configuration of pins and the registers.
Parameters:
  irqNumber - number of interrupt.
  irqMode - mode of interrupt
Returns:
  none.
******************************************************************************/
void halSetIrqConfig(uint8_t irqNumber, uint8_t irqMode)
{
  // IRQ pin is input
  switch (irqNumber)
  {
    case IRQ_0:
      DDRD &= ~(1 << 2);
      PORTD |= (1 << 2);
      break;
    case IRQ_1:
      DDRD &= ~(1 << 3);
      PORTD |= (1 << 3);
      break;
    case IRQ_2:
      DDRB &= ~(1 << 2);
      PORTB |= (1 << 2);
      break;
    default:
      break;
  }
  // Clear previous settings of corresponding interrupt sense control
  EICRA &= ~(3 << (irqNumber << 1));
  // Setup corresponding interrupt sence control
  EICRA |= (irqMode & 0x03) << (irqNumber << 1);
  // Clear the INTn interrupt flag
  EIFR |= (1 << irqNumber);
}

/**************************************************************************//**
\brief Clears configuration of pins and the registers.
\param[in]
  irqNumber - number of interrupt.
******************************************************************************/
void halClrIrqConfig(uint8_t irqNumber)
{
  switch (irqNumber)
  {
    case IRQ_0:
      PORTD &= ~(1 << 2);
      break;
    case IRQ_1:
      PORTD &= ~(1 << 3);
      break;
    case IRQ_2:
      PORTB &= ~(1 << 2);
      break;
    default:
      break;
  }
  EICRA &= ~(3 << (irqNumber << 1));
}

/******************************************************************************
 External interrupt 0 handler
******************************************************************************/
ISR(INT0_vect)
{
  halWakeupFromIrq();
  /* user's callback */
  if (NULL != IrqCallbackList[IRQ_0 - HAL_FIRST_VALID_IRQ])
    IrqCallbackList[IRQ_0 - HAL_FIRST_VALID_IRQ]();
}

/******************************************************************************
 External interrupt 1 handler
******************************************************************************/
ISR(INT1_vect)
{
  halWakeupFromIrq();
  /* user's callback */
  if (NULL != IrqCallbackList[IRQ_1 - HAL_FIRST_VALID_IRQ])
    IrqCallbackList[IRQ_1 - HAL_FIRST_VALID_IRQ]();
}

/******************************************************************************
 External interrupt 1 handler
******************************************************************************/
ISR(INT2_vect)
{
  halWakeupFromIrq();
  /* user's callback */
  if (NULL != IrqCallbackList[IRQ_2 - HAL_FIRST_VALID_IRQ])
    IrqCallbackList[IRQ_2 - HAL_FIRST_VALID_IRQ]();
}
// eof irq.c
