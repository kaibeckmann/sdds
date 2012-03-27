/**************************************************************************//**
  \file  bspTaskManager.h

  \brief The header file describes enums and functions of BSP task manager.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    16/12/08 E. ALuzhetsky - Created
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
  BSP_LCD      = (uint8_t)1 << 0,
// For futer extensions.
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

