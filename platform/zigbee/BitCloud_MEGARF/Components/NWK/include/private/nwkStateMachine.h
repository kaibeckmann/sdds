/**************************************************************************//**
  \file nwkStateMachine.h

  \brief State machine header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2007-06-14 V. Panov - Created.
    2009-02-21 M. Gekk  - Refactoring.
   Last change:
    $Id: nwkStateMachine.h 12570 2010-09-24 20:25:34Z mgekk $
 ******************************************************************************/
#if !defined _NWK_STATE_MACHINE_H
#define _NWK_STATE_MACHINE_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwkConfig.h>
#include <nwkCommon.h>
#include <nwkMem.h>

/******************************************************************************
                                Define(s) section
 ******************************************************************************/
/* Identifiers of modules. */
#define  NWK_MODULE_ID_DATA_REQ      (1U << 0)
#define  NWK_MODULE_ID_SYNC          (1U << 1)
#define  NWK_MODULE_ID_LINK_STATUS   (1U << 2)
#define  NWK_MODULE_ID_JOIN_IND      (1U << 3)
#define  NWK_MODULE_ID_NETWORK_COMMAND  (1U << 4)
#define  NWK_MODULE_ID_LEAVE         (1U << 5)
#define  NWK_MODULE_ID_PANID_CONFLICT   (1U << 6)
#define  NWK_MODULE_ID_DATA_IND      (1U << 7)
#define  NWK_MODULE_ID_DISCOVERY     (1U << 8)
#define  NWK_MODULE_ID_FORMATION     (1U << 9)
#define  NWK_MODULE_ID_JOIN_REQ      (1U << 10)
#define  NWK_MODULE_ID_COMMAND_REQ   (1U << 11)
#define  NWK_MODULE_ID_COMMAND_IND   (1U << 12)
#define  NWK_MODULE_ID_EDSCAN        (1U << 13)
#define  NWK_MODULE_ID_START_ROUTER  (1U << 14)
#define  NWK_MODULE_ID_ADDR_CONFLICT (1U << 15)

/* Module permitions */
#define NWK_EVENT_RESET_REQ \
  (NWK_MODULE_ID_DISCOVERY | NWK_MODULE_ID_FORMATION \
  | NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ | NWK_MODULE_ID_COMMAND_IND)

#define NWK_EVENT_FORMATION_SUCCESS ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_FORMATION))
#define NWK_EVENT_JOIN_SUCCESS ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_FORMATION))

#define NWK_EVENT_LEAVE_ALL_CHILDREN \
  ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_JOIN_IND & ~NWK_MODULE_ID_FORMATION \
  & ~NWK_MODULE_ID_START_ROUTER))

#define NWK_EVENT_LEAVE_SUCCESS (NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ)
#define NWK_EVENT_LEAVE_FAIL NWK_EVENT_JOIN_SUCCESS

#define NWK_EVENT_REJOIN_REQ \
  (NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ \
  | NWK_MODULE_ID_COMMAND_IND | NWK_MODULE_ID_DISCOVERY)
#define NWK_EVENT_REJOIN_SUCCESS ((NwkStateMachineEvent_t)(~NWK_MODULE_ID_FORMATION))

#define NWK_EVENT_POWER_FAILURE_RESET (NWK_EVENT_FORMATION_SUCCESS | NWK_EVENT_JOIN_SUCCESS)
#define NWK_EVENT_EDSCAN 0U /* disable all nwk modules */

/******************************************************************************
                                  Types section
 ******************************************************************************/
/** Type of identifier of module. */
typedef uint16_t  NwkStateMachineModuleID_t;

/** Type of NWK event. */
typedef NwkState_t  NwkStateMachineEvent_t;

/******************************************************************************
                          Inline functions section
******************************************************************************/
/**************************************************************************//**
  \brief this function return true, if module with moduleID is allowed to work.
 ******************************************************************************/
INLINE bool nwkCheckStateMachine(NwkStateMachineModuleID_t moduleID)
{
  return (nwkMem.state & moduleID)? true: false;
}

/**************************************************************************//**
  \brief Modules that can switch state machine shall send events.

  \param[in] event - id of event.
  \return None.
 ******************************************************************************/
INLINE void nwkSwitchStateMachine(NwkStateMachineEvent_t event)
{
  nwkMem.state = event;
}

/**************************************************************************//**
  \brief This function return the current state of network layer.

  \return current state
 ******************************************************************************/
INLINE NwkState_t nwkGetStateMachine(void)
{
  return nwkMem.state;
}

/**************************************************************************//**
 \brief Set new the network layer state.

 \param[in] state - new state.
 \return current state
 ******************************************************************************/
INLINE void nwkRestoreStateMachine(NwkState_t state)
{
  nwkMem.state = state;
}

#endif /* _NWK_STATE_MACHINE_H */
/** eof nwkStateMachine.h */

