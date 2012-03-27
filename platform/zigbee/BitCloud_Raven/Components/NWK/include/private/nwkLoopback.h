/**************************************************************************//**
  \file  nwkLoopback.h

  \brief Interface of network loopback.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2009-10-06 Max Gekk - Created.
   Last change:
    $Id: nwkLoopback.h 12570 2010-09-24 20:25:34Z mgekk $
 ******************************************************************************/
#if !defined _NWK_LOOPBACK_H
#define _NWK_LOOPBACK_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwkConfig.h>
#include <queue.h>
#include <nldeData.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Internal states of the loopback component. */
typedef enum _NwkLoopbackState_t
{
  NWK_LOOPBACK_UNKNOWN_STATE = 0x00,
  NWK_LOOPBACK_FIRST_STATE = 0x8e,
  NWK_LOOPBACK_IDLE_STATE = NWK_LOOPBACK_FIRST_STATE,
  NWK_LOOPBACK_REQUEST_PROCESSING_STATE = 0x8f,
  NWK_LOOPBACK_WAIT_PACKET_STATE = 0x90,
  NWK_LOOPBACK_LAST_STATE
}  NwkLoopbackState_t;

/** Internal parameters of the loopback component. */
typedef struct _NwkLoopback_t
{
  QueueDescriptor_t  queue;  /**< Queue of requests from upper layer */
  NwkLoopbackState_t  state;  /**< Finite-state machine */
}  NwkLoopback_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief The request to send own data packet to itself.

  \param[in] req - pointer to parameters of NLDE-DATA.request primitive.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkLoopbackTxReq(NWK_DataReq_t  *const req);

/**************************************************************************//**
  \brief The main task handler of the network loopback component.
 ******************************************************************************/
NWK_PRIVATE void nwkLoopbackTaskHandler(void);

/**************************************************************************//**
  \brief Handler of free packet indication.
 ******************************************************************************/
NWK_PRIVATE void nwkLoopbackFreePacketInd(void);

/**************************************************************************//**
  \brief Reset the network loopback component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetLoopback(void);

#endif /* _NWK_LOOPBACK_H */
/** nwkLoopback.h */

