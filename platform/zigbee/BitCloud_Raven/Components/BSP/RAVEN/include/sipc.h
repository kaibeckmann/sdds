/*****************************************************************************
  \file  sipc.h

  \brief 

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    10/26/2009 I.Vagulin - Created
******************************************************************************/


#ifndef _SIPC_H_
#define _SIPC_H_

/*****************************************************************************
                              Includes section
******************************************************************************/
#include "types.h"
#include "sipcproto.h"

/*****************************************************************************
                              Types section
******************************************************************************/
//sipc frame listeners, can be passed to bspSipcOpen()
typedef struct
{
  struct
  {
    void *next;
  } service ;
  void (*sipcInd)(SipcAnswerId_t id, uint8_t *bytes);
} SipcInd_t ;

//frame part description
typedef struct {
  const uint8_t *data;
  const int len;
} SipcFramePart_t ;

/***********************************************************************************
  Description: open sipc connection, can be called more that once.
  Parameters: pointer to SipcInd_t or none
  Return: none
 ***********************************************************************************/
void bspSipcOpen(SipcInd_t* listener);

/***********************************************************************************
  Description: queue sipc frame sending
  Parameters: frame, frame length
  Return: none
 ***********************************************************************************/
void bspSipcSendFrame(void* frame, uint8_t len);

/***********************************************************************************
  Description: send frame built from parts.
  Parameters: array of parts, parts count.
  Return: none
 ***********************************************************************************/
void bspSipcSendFrameByParts(SipcFramePart_t parts[], uint8_t partsCnt);

/***********************************************************************************
  Description: Close sipc conenction if no users left otherwise decrement use count
  Parameters: listener passed in bspSipcOpen, for proper deregistring
  Return: none
 ***********************************************************************************/
void bspSipcClose(SipcInd_t* listener);

/***********************************************************************************
  Description: check if sipc have queued but unsent data
  Parameters: none
  Return: true if some data still unsent
 ***********************************************************************************/
bool bspSipcTxInProgress();

#endif /* _SIPC_H_ */
