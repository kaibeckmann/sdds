/**************************************************************************//**
  \file nwkConcentrator.h

  \brief Interface of network concentrator.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2009-09-14 Max Gekk - Created.
   Last change:
    $Id: nwkConcentrator.h 12570 2010-09-24 20:25:34Z mgekk $
 ******************************************************************************/
#if !defined _NWK_CONCENTRATOR_H
#define _NWK_CONCENTRATOR_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwkConfig.h>
#include <appTimer.h>
#include <nlmeRouteDiscovery.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Internal states of the network concentrator. */
typedef  enum  _NwkConcentratorState_t
{
  NWK_CONCENTRATOR_IDLE_STATE = 0x89,
  NWK_CONCENTRATOR_FIRST_STATE = 0x8A,
  NWK_CONCENTRATOR_START_TIMER_STATE = NWK_CONCENTRATOR_FIRST_STATE,
  NWK_CONCENTRATOR_ROUTE_DISCOVERY_STATE = 0x8B,
  NWK_CONCENTRATOR_LAST_STATE
}  NwkConcentratorState_t;

/** State and parameters of the network concentrator. */
typedef  struct  _NwkConcentrator_t
{
  NwkConcentratorState_t  state;
  union
  {
    HAL_AppTimer_t  timer;
    NWK_RouteDiscoveryReq_t  routeDiscovery;
  } req;
}  NwkConcentrator_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _NWK_CONCENTRATOR_
/**************************************************************************//**
  \brief Start the network concentrator.

    Periodic sending of route discovery commands.
 ******************************************************************************/
NWK_PRIVATE void nwkStartConcentrator(void);

/**************************************************************************//**
  \brief Reset the network concentrator.
 ******************************************************************************/
NWK_PRIVATE void nwkResetConcentrator(void);

#else /* _NWK_CONCENTRATOR_ */

#define nwkStartConcentrator()  (void)0
#define nwkStopConcentrator()  (void)0
#define nwkResetConcentrator() (void)0

#endif /* _NWK_CONCENTRATOR_ */
#endif /* _NWK_CONCENTRATOR_H */
/** eof nwkConcentrator.h */

