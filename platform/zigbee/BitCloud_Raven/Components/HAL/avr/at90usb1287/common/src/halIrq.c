/*************************************************************************//**
  \file  halirq.c

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
  uint8_t ui8ShiftCount = (irqNumber - IRQ_4) << 1;
  // IRQ pin is input
  DDRE &= ~(1 << irqNumber);
  PORTE |= (1 << irqNumber);
  // Clear previous settings of corresponding interrupt sense control
  EICRB &= ~(3 << ui8ShiftCount);
  // Setup corresponding interrupt sence control
  EICRB |= (irqMode & 0x03) << ui8ShiftCount;
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
  uint8_t ui8ShiftCount = (irqNumber - IRQ_4) << 1;
  DDRE &= ~(1 << irqNumber);// IRQ pin is input
  PORTE &= ~(1 << irqNumber); // pullup off
  EICRB &= ~(3 << ui8ShiftCount);
}

/******************************************************************************
 External interrupt 6 handler
******************************************************************************/
ISR(INT6_vect)
{
  /* user's callback */
  if (NULL != IrqCallbackList[IRQ_6 - HAL_FIRST_VALID_IRQ])
    IrqCallbackList[IRQ_6 - HAL_FIRST_VALID_IRQ]();
}

/******************************************************************************
 External interrupt 7 handler
******************************************************************************/
ISR(INT7_vect)
{
  /* user's callback */
  if (NULL != IrqCallbackList[IRQ_7 - HAL_FIRST_VALID_IRQ])
    IrqCallbackList[IRQ_7 - HAL_FIRST_VALID_IRQ]();
}
// eof irq.c
