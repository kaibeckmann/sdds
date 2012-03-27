/***************************************************************************//**
  \file  bspLeds.h

  \brief The header file describes the led interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    29/05/07 E. Ivanov - Created
*******************************************************************************/

#ifndef _BSPLEDS_H
#define _BSPLEDS_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <gpio.h>
#include <leds.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define halInitFirstLed()       GPIO_8_make_out(); GPIO_8_set()
#define halUnInitFirstLed()     GPIO_8_make_in()
#define halOnFirstLed()         GPIO_8_clr()
#define halOffFirstLed()        GPIO_8_set()
#define halReadFirstLed()       GPIO_8_read()
#define halToggleFirstLed()     GPIO_8_toggle()

#define halInitSecondLed()      GPIO_6_make_out(); GPIO_6_set()
#define halUnInitSecondLed()    GPIO_6_make_in()
#define halOnSecondLed()        GPIO_6_clr()
#define halOffSecondLed()       GPIO_6_set()
#define halReadSecondLed()      GPIO_6_read()
#define halToggleSecondLed()    GPIO_6_toggle()

#define halInitThirdLed()       GPIO_7_make_out(); GPIO_7_set()
#define halUnInitThirdLed()     GPIO_7_make_in()
#define halOnThirdLed()         GPIO_7_clr()
#define halOffThirdLed()        GPIO_7_set()
#define halReadThirdLed()       GPIO_7_read()
#define halToggleThirdLed()     GPIO_7_toggle()

#define halInitFourthLed()      GPIO_9_make_out(); GPIO_9_set()
#define halUnInitFourthLed()    GPIO_9_make_in()
#define halOnFourthLed()        GPIO_9_clr()
#define halOffFourthLed()       GPIO_9_set()
#define halReadFourthLed()      GPIO_9_read()
#define halToggleFourthLed()    GPIO_9_toggle()

#endif /*_BSPLEDS_H*/
// eof bspLeds.h
