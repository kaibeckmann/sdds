/*************************************************************************//**
  \file  halClkCtrl.c

  \brief Implementation of clock control module.

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
#include <halClkCtrl.h>
#include <halRfCtrl.h>
#include <calibration.h>
#include <atomic.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// defines fuse mask for RC oscillator
#define HAL_RC_OSCILLATOR_CLOCK 0x02
// mask for CKSEL bits
#define HAL_CKSEL_MASK          0x0F

/******************************************************************************
                   Prototypes section
******************************************************************************/
void halStartingCalibrate(void);

/******************************************************************************
                   Global variables section
******************************************************************************/
static volatile ClkSource_t clkClockSource;

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
Initializations PLL clock for usb.
******************************************************************************/
void halInitPll(void)
{
  // sets prescaler 4
  PLLCSR = (1 << PLLP1) | (1 << PLLP0) | (1 << PLLE);
  // waits for when pll is locked reference clock (about 100 ms)
  while (!(PLLCSR & (1 << PLOCK)));
}

/******************************************************************************
Initializations system clock.
******************************************************************************/
void halInitFreq(void)
{
  uint8_t lowFuseByte;

  // wait for end of eeprom writing
  while (EECR & (1 << EEPE));
  ATOMIC_SECTION_ENTER
    lowFuseByte = SF_GET_LOW_FUSES();
  ATOMIC_SECTION_LEAVE

  if (HAL_RC_OSCILLATOR_CLOCK == (lowFuseByte & HAL_CKSEL_MASK))
    clkClockSource = INTERNAL_RC;
  else
    clkClockSource = OTHER_SOURCE;

  if (INTERNAL_RC == clkClockSource)
  {
        ATOMIC_SECTION_ENTER

        ASM (
        "push r21                    \n\t"

        "ldi  r21, 0x80              \n\t" /* CLKPR = 1 << CLKPCE */
        "sts  0x0061, r21            \n\t" /* CLKPR = 1 << CLKPCE */

#if (F_CPU == 4000000ul)
        "ldi  r21, 0x01              \n\t" /* CLKPR = 1 << CLKPS0 (1 cycle) */
        "sts  0x0061, r21            \n\t" /* CLKPR = 1 << CLKPS0 (2 cycle) */
#endif
#if (F_CPU == 8000000ul)
        "ldi  r21, 0x00              \n\t" /* CLKPR = 0 (1 cycle) */
        "sts  0x0061, r21            \n\t" /* CLKPR = 0 (2 cycle) */
#endif

        "pop r21                     \n\t"
    );

    ATOMIC_SECTION_LEAVE
    halStartingCalibrate();
  }
  else
  {
    halInitPll();
  }
}

/**************************************************************************//**
\brief Return clock source

\return
  clock source.
******************************************************************************/
ClkSource_t halGetClockSource(void)
{
  return clkClockSource;
}

/**************************************************************************//**
\brief System clock.

\return
  system clock in Hz.
******************************************************************************/
uint32_t HAL_ReadFreq(void)
{
  return (uint32_t)F_CPU;
}

// eof halClkCtrl.c
