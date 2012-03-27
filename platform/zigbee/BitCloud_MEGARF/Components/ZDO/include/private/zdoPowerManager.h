/************************************************************************//**
  \file zdoPowerManager.h

  \brief The header file describes the constants, types and internal interface
  of ZDO power manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _ZDOPOWERMANAGER_H
#define _ZDOPOWERMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <zdo.h>

/******************************************************************************
                   Types section
******************************************************************************/

typedef enum _SleepState_t
{
  ZDO_IDLE_SLEEP_STATE,
  ZDO_SLEEPING_SLEEP_STATE
} SleepState_t;

typedef enum _SyncState_t
{
  ZDO_STOPPED_SYNC_STATE,
  ZDO_RUNNING_SYNC_STATE,
  ZDO_WAIT_SYNC_CONF_STATE,
} SyncState_t;

typedef struct _ZdoPowerManager_t
{
  SleepState_t        sleepState;
  SyncState_t         syncState;
  uint8_t             syncFailCounter;
  ZDO_SleepReq_t      *sleepReq;
  ZDO_WakeUpReq_t     *wakeUpReq;
  HAL_AppTimer_t      syncTimer;
  NWK_SyncReq_t       zdoSyncReqParams;
} ZdoPowerManager_t;

void zdoPowerManagerInit(void);

#endif // _ZDOPOWERMANAGER_H_

// eof zdoPowerManager.h
