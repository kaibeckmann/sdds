/************************************************************************//**
  \file zclTaskManager.h

  \brief
    The header file describes the public interface of ZCL Task Manager

    The file describes the public interface and types of ZCL Task Manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTMs).

  \internal
    History:
    01.12.08 A. Poptashov - Created.
******************************************************************************/

#ifndef _ZCLTASKMANAGER_H
#define _ZCLTASKMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include "types.h"

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/


/******************************************************************************
                   Constants section
******************************************************************************/
typedef enum
{
  ZCL_CAPS_TASK_ID        = (1 << 0),
  ZCL_SUBTASK_ID         = (1 << 1),
  ZCL_PARESER_TASK_ID = (1 << 2),
} ZclTaskId_t;

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/


/*****************************************************************************
  \brief ZCL Task Manager post task function
  \param[in] taskId - Determines the task Id to be posted (ZclTaskId_t should be used)
*****************************************************************************/
extern void zclPostTask(uint8_t taskId);


/*****************************************************************************
  \brief Task Manager task handler function
*****************************************************************************/
extern void ZCL_TaskHandler(void);

#endif  //#ifndef _ZCLTASKMANAGER_H


//eof zclTaskManager.h
