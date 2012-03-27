/***************************************************************************//**
  \file  leds.c

  \brief The module to access to the leds.

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
                   Includes section
******************************************************************************/
#include <bspLeds.h>

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Inits LEDs control module.
******************************************************************************/
static void initLeds(void)
{
  halInitFirstLed();
  halInitSecondLed();
  halInitThirdLed();
  halInitFourthLed();
}

/**************************************************************************//**
\brief Opens leds module to use.

\return
    operation state
******************************************************************************/
result_t BSP_OpenLeds(void)
{
  initLeds();
  return BC_SUCCESS;
}

/**************************************************************************//**
\brief Closes leds module.

\return
    operation state
******************************************************************************/
result_t BSP_CloseLeds(void)
{
  halUnInitFirstLed();
  halUnInitSecondLed();
  halUnInitThirdLed();
  halUnInitFourthLed();
  return BC_SUCCESS;
}

/**************************************************************************//**
\brief Turns on the LED.

\param[in]
    id - number of led
******************************************************************************/
void BSP_OnLed(uint8_t id)
{
  switch (id)
  {
    case LED_FIRST:
      halOnFirstLed();
      break;
    case LED_SECOND:
      halOnSecondLed();
      break;
    case LED_THIRD:
      halOnThirdLed();
      break;
    case LED_FOURTH:
      halOnFourthLed();
      break;
  }
}

/**************************************************************************//**
\brief Turns off the LED.

\param[in]
      id - number of led
******************************************************************************/
void BSP_OffLed(uint8_t id)
{
  switch (id)
  {
    case LED_FIRST:
      halOffFirstLed();
      break;
    case LED_SECOND:
      halOffSecondLed();
      break;
    case LED_THIRD:
      halOffThirdLed();
      break;
    case LED_FOURTH:
      halOffFourthLed();
      break;
  }
}

/**************************************************************************//**
\brief Changes the LED state to opposite.

\param[in]
      id - number of led
******************************************************************************/
void BSP_ToggleLed(uint8_t id)
{
  switch (id)
  {
    case LED_FIRST:
      halToggleFirstLed();
      break;
    case LED_SECOND:
      halToggleSecondLed();
      break;
    case LED_THIRD:
      halToggleThirdLed();
      break;
    case LED_FOURTH:
      halToggleFourthLed();
      break;
  }
}

// eof leds.c
