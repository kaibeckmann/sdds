/************************************************************************//**
  \file zdoSecurityManager.h

  \brief The header file describes the constants, types and internal interface
  of ZDO security manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _ZDOSECURITYMANAGER_H
#define _ZDOSECURITYMANAGER_H

/******************************************************************************
                    Includes section
******************************************************************************/
#include <appTimer.h>
#include <zdo.h>

/******************************************************************************
                    Types section
******************************************************************************/
typedef enum
{
  ZDO_IDLE_SECURITY_STATE,
  ZDO_NORMAL_OPERATING_SECURITY_STATE,
  ZDO_WAITING_ESTABLISH_KEY_SECURITY_STATE,
  ZDO_WAITING_TRANSPORT_KEY_SECURITY_STATE,
  ZDO_WAITING_PARENT_AUTHENTICATION_SECURITY_STATE,
  ZDO_APP_KEY_ESTABLISH_RESPONDER_SECURITY_STATE,
  ZDO_APP_KEY_ESTABLISH_INITIATOR_SECURITY_STATE,
  ZDO_STARTING_NORMAL_OPERATING_SECURITY_STATE,
  ZDO_FAIL_CONFIRM_SECURITY_STATE,
  ZDO_CONFIRM_APP_KEY_SECURITY_STATE,
  ZDO_WAITING_APP_KEY_SECURITY_STATE,
} ZdoSecurityManagerState_t;

typedef struct
{
  ZdoSecurityManagerState_t state;
#ifdef _SECURITY_
  HAL_AppTimer_t             waitTimer;
  HAL_AppTimer_t             delayTimer;
  uint8_t                    newKeySeqNum;
#ifdef _HIGH_SECURITY_
  union
  {
    APS_AuthenticateReq_t    apsAuthenticateReq;
    APS_EstablishKeyReq_t    apsEstablishKeyReq;
    APS_RequestKeyReq_t      apsRequestKeyReq;
  };
  APS_EstablishKeyResp_t     apsEstablishKeyResp;
  ZDO_EndToEndAppKeyReq_t   *appKeyReq;
#endif // _HIGH_SECURITY_
#endif // _SECURITY_

} ZdoSecurityManager_t;

/******************************************************************************
                    Prototypes section
******************************************************************************/
void zdoResetSecurityManager(void);
void zdoAuthenticationStart(void);
void zdoAuthenticationConf(ZDO_Status_t status);
uint8_t zdoGetPreconfiguredStatus(void);
void zdoAuthenticateChild(ExtAddr_t *childAddr);
void zdoSecurityManagerHandler(void);

/******************************************************************************
  Get Trust Center address
  Parameters:
    none
  Return:
    Trust Center extended address
******************************************************************************/
ExtAddr_t zdoGetTrustCenterAddress(void);

/******************************************************************************
  Set Trust Center address
  Parameters:
    addr - address to set as Trust Center address
  Return:
    none
******************************************************************************/
void zdoSetTrustCenterAddress(ExtAddr_t *addr);

#endif // _ZDOSECURITYMANAGER_H

// eof zdoSecurityManager.h
