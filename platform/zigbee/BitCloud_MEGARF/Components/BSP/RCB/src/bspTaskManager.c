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
    26.08.09 A. Taradov - Created
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
\brief BSP button handler.
******************************************************************************/
void bspButtonsHandler(void);

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
#ifdef _BUTTONS_
  if (bspTaskFlags0 & BSP_BUTTONS)
  {
    bspTaskFlags0 &= ~BSP_BUTTONS;
    bspButtonsHandler();
  }
#endif

  if (bspTaskFlags0)
    SYS_PostTask(BSP_TASK_ID);
}

// eof bspTaskManager.c
