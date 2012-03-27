/**************************************************************************//**
\file  bspTaslManager.h

\brief Declarations of enums and functions of BSP task manager.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    26.08.09 A. Taradov - Created
*******************************************************************************/

#ifndef _BSPTASKHANDLER_H
#define _BSPTASKHANDLER_H

/******************************************************************************
                   Includes section
******************************************************************************/
// \cond
#include <types.h>
#include <taskManager.h>
// \endcond

/******************************************************************************
                   Define(s) section
******************************************************************************/
enum
{
  BSP_BUTTONS = 1<<0,
};

/******************************************************************************
                   External variables section
******************************************************************************/
extern volatile uint8_t bspTaskFlags0;

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/***************************************************************************//**
\brief posting bsp task for task manager.
\param[in]
  flag - task number
*******************************************************************************/
INLINE void bspPostTask0(uint8_t flag)
{
  bspTaskFlags0 |= flag;
  SYS_PostTask(BSP_TASK_ID);
}

#endif /* _BSPTASKHANDLER_H */
// eof bspTaskManager.h
