/**************************************************************************//**
  \file  halWdtInit.c

  \brief Implementation of WDT start up procedure.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      29/05/07 E. Ivanov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <resetReason.h>
#include <halAppClock.h>

/******************************************************************************
                   Defines section
******************************************************************************/
#define PIN_OUT 62500
#define MEANING_BITS   0x1F

/******************************************************************************
                        Prototypes section
******************************************************************************/
#ifdef _SYS_ASSERT_ON_
  INLINE void halJumpNullHandler(void);
#endif

/******************************************************************************
                   Global variables section
******************************************************************************/
#if defined(__GNUC__)
  uint8_t halResetReason __attribute__ ((section (".noinit")));
#elif defined(__ICCAVR__)
  __no_init uint8_t halResetReason;
#endif

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Resets and stops wdt. Saves the reason of reset.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
#if defined(__GNUC__)

  void halWdtInit(void) __attribute__ ((naked)) \
    __attribute__ ((section (".init0")));

  void halWdtInit(void)
  {
    ASM("clr r1");
#elif defined(__ICCAVR__)

  __task void halWdtInit(void)
  {
    ASM("clr r15");
#else
  #error 'Compiler not supported.'
#endif

    if (TEMP_WARM_RESET != halResetReason)
    {
      halResetReason = MCUSR & MEANING_BITS;

      if (halResetReason & POWER_ON_RESET)
        halResetReason = POWER_ON_RESET;
    }
    else
    {
      halResetReason = WARM_RESET;
    }
    MCUSR = 0;
    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00;

  #ifdef _SYS_ASSERT_ON_
    halJumpNullHandler();
  #endif
  }

#ifdef _SYS_ASSERT_ON_
/******************************************************************************
Jump to NULL handler.
Parameters:
  none.
Returns:
  none.
******************************************************************************/
void halJumpNullHandler(void)
{
  if (0 == halResetReason) // was jump on NULL
  {
    register volatile uint16_t tmp;
    tmp = SP;

    ASM ("cli");
    DDRB |= 0xE0;
    /* Init UART*/
    UBRR1H = 0;
    #if (F_CPU == 4000000ul)
      UBRR1L = 12;
    #elif (F_CPU == 8000000ul)
      UBRR1L = 25;
    #endif
    UCSR1A = (1 << U2X1);
    UCSR1B = (1 << TXEN1);
    UCSR1C = (3 << UCSZ10);  // 8-bit data

    /* Init timer counter 1.*/
    OCR1A = 0;
    /* Disable TC4 interrupt */
    TIMSK1 &= ~(1 << OCIE1A);
    /* main clk / 8 */
    TCCR1B = (1 << WGM12) | (1 << CS11);

    while(1)
    {
      do{
        /* Send byte to UART */
        while (!(UCSR1A & (1 << UDRE1)));
        UDR1 = *((uint8_t *)SP);
        SP++;
      }while (RAMEND >= SP);
      SP = tmp;

      PORTE |= 0x40;
      TCNT1 = 0;
      while(TCNT1 < PIN_OUT);
      PORTE &= ~0x40;
      PORTE |= 0x80;
      TCNT1 = 0;
      while(TCNT1 < PIN_OUT);
      PORTE &= ~0x80;
      PORTD |= 0x20;
      TCNT1 = 0;
      while(TCNT1 < PIN_OUT);
      PORTD &= ~0x20;
    }
  }
}
#endif
// eof halWdtInit.c
