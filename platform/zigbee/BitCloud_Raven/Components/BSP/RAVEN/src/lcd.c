/**************************************************************************//**
  \file  lcd.c

  \brief Implemenattion of LCD management functions.

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
#include <usart.h>
#include <bspTaskManager.h>
#include <lcd.h>
#include <atomic.h>

#include "sipc.h"
#include "sipcproto.h"

/******************************************************************************
                   Prototypes section
******************************************************************************/
void bspLcdHandler(void);

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief LCD task handler.
******************************************************************************/
void bspLcdHandler(void)
{
}

/**************************************************************************//**
\brief Initializes USART to control LCD.
******************************************************************************/
void BSP_OpenLcd(void)
{
  bspSipcOpen(NULL);
}

/**************************************************************************//**
\brief Sends the command to the LCD.
******************************************************************************/
void BSP_SendLcdCmd(BspLcdCmd_t cmdId)
{
  bspSipcSendFrame(&cmdId, 1);
}

/**************************************************************************//**
\brief Sends the message to the LCD.
******************************************************************************/
void BSP_SendLcdMsg(const char *str)
{
  SipcFramePart_t parts[] =
  {
      {&(uint8_t){SIPC_CMD_ID_MSG}, 1},
      {(uint8_t*)str, strlen(str)},
  };
  bspSipcSendFrameByParts(parts, sizeof(parts)/sizeof(parts[0]));
}

/**************************************************************************//**
\brief Checks whether the LCD command transmission is finished or not.

\param  void
\return 1 in case if empty, 0 otherwise
******************************************************************************/
int BSP_IsLcdOperationCompleted(void)
{
  return !bspSipcTxInProgress();
}

// eof lcd.c
