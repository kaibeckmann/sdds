/**************************************************************************//**
\file  halUsart.c

\brief Implementation of usart hardware-dependent module.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <usart.h>
#include <halAppClock.h>
#include <halIrq.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
void halPostUsartTask(HalUsartTaskId_t taskId);

/******************************************************************************
                   External global variables section
******************************************************************************/
extern volatile bool halEnableDtrWakeUp;
extern void (* dtrWakeUpCallback)(void);

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
  \brief Sets USART module parameters.
  \param
    usartmode - pointer to HAL_UsartDescriptor_t
******************************************************************************/
void halSetUsartConfig(HAL_UsartDescriptor_t *usartMode)
{
  UCSRnB(usartMode->tty) = 0x00; // disable usart
  UBRRnL(usartMode->tty) = usartMode->baudrate; // usart speed

  if (USART_MODE_ASYNC == usartMode->mode)
  {
    UCSRnA(usartMode->tty) = (uint8_t)USART_DOUBLE_SPEED << U2X1; // Double the USART Transmition Speed
    UCSRnC(usartMode->tty) = 0x00;
  }
  else
  {
    UCSRnA(usartMode->tty) = 0;
    UCSRnC(usartMode->tty) = usartMode->edge; // edge select
  }

  UCSRnC(usartMode->tty) |= usartMode->mode;
  UCSRnC(usartMode->tty) |= usartMode->dataLength;     // character size
  UCSRnC(usartMode->tty) |= usartMode->parity;   // parity mode
  UCSRnC(usartMode->tty) |= usartMode->stopbits; // stop bit select
  UCSRnA(usartMode->tty) |= (1 << RXC1); // clear receive interrupt
  UCSRnB(usartMode->tty) |= (1 << RXEN1) | (1 << TXEN1); // usart enable
  UCSRnB(usartMode->tty) |= (1 << RXCIE1) ; // receive interrupt enable
}

/**************************************************************************//**
 \brief The interrupt handler of USART1 - data register is empty.
******************************************************************************/
ISR(USART1_UDRE_vect)
{
  // We must disable the interrupt because we must "break" context.
  halDisableUsartDremInterrupt(USART_CHANNEL_1);
  halPostUsartTask(HAL_USART_TASK_USART1_DRE);
}

/**************************************************************************//**
 \brief The interrupt handler of USART1 - transmission is completed.
******************************************************************************/
ISR(USART1_TX_vect)
{
  halDisableUsartTxcInterrupt(USART_CHANNEL_1);
  halPostUsartTask(HAL_USART_TASK_USART1_TXC);
}

/**************************************************************************//**
 \brief The interrupt handler of USART1 - reception is completed.
******************************************************************************/
ISR(USART1_RX_vect)
{
  uint8_t  status = UCSR1A;
  uint8_t  data = UDR1;

  if (!(status & ((1 << FE1) | (1 << DOR1) | (1 << UPE1))))
  {
    halUsartRxBufferFiller(USART_CHANNEL_1, data);
    halPostUsartTask(HAL_USART_TASK_USART1_RXC);
  }
#if defined(_USE_USART_ERROR_EVENT_)
  else // There is an error in the received byte.
  {
    halUsartSaveErrorReason(USART_CHANNEL_1, status);
    halPostUsartTask(HAL_USART_TASK_USART1_ERR);
  }
#endif
}

#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
/**************************************************************************//**
/brief External interrupt 4 (DTR) handler
******************************************************************************/
ISR(INT4_vect)
{
  if (halEnableDtrWakeUp)
  { /* enable DTR (irq 4) wake up */
    halDisableIrqInterrupt(IRQ_4);
  } /* enable DTR (irq 4) wake up */

  if (NULL != dtrWakeUpCallback)
    dtrWakeUpCallback();
}
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT
// eof halUsart.c
