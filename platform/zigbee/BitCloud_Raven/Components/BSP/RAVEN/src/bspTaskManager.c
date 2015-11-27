/**************************************************************************//**
  \file  bspTaskManager.c

  \brief Implemenattion of BSP task manager.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    16/12/08 A. Luzhetsky - Created
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <bspTaskManager.h>
#include <atomic.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief BSP LCD handler.
******************************************************************************/
void bspLcdHandler(void);

/******************************************************************************
                   Global variables section
******************************************************************************/
volatile uint8_t bspTaskFlags0 = 0;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief BSP task handler.
******************************************************************************/
void BSP_TaskHandler(void)
{
}