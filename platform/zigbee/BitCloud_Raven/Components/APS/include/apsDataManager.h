/*************************************************************************//**
  \file apsDataManager.h

  \brief APS Data Manager header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    06/06/07 A. Potashov - Created.
*****************************************************************************/


#ifndef _APS_DATAMANAGER_H
#define _APS_DATAMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <bcEndian.h>
#include <aps.h>
#include <nwk.h>
#include <appTimer.h>
#include <apsBindManager.h>
#include <apsFrames.h>
#include <apsMemoryManager.h>

/******************************************************************************
                   Types section
******************************************************************************/
enum
{
  APS_FRAGMENTED_RECEIVE_FREE_STATE,
  APS_FRAGMENTED_RECEIVE_BUSY_STATE,
  APS_FRAGMENTED_RECEIVE_INDICATION_STATE
};

typedef enum _ApsTransmittedDataHandlerState_t
{
  START_DATA_HANDLING_STATE,
  DATA_DECRYPTION_STATE,
  SEND_DATA_TO_BOUND_DEVICES_STATE,
  FINISH_DATA_HANDLING_STATE
} ApsTransmittedDataHandlerState_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  Make a reset of APS Data Manager
  Parameters: fullReset - reset all internal variables of APS-layer or not.
  Returns:    None
*****************************************************************************/
void apsResetDataManager(const bool fullReset);


/*****************************************************************************
  APS Stop Event Handler
  Parameters: options - options field APS_StopReq value
  Returns:    None
******************************************************************************/
void apsStopDataManager(void);

/*****************************************************************************
  APS Start after Stop Event Handler
  Parameters: options - options field APS_StartReq value
  Returns:    None
******************************************************************************/
void apsStartAfterStopDataManager(void);

/*****************************************************************************
  APS Data Manager Process function
  Parameters: None
  Returns: None
*****************************************************************************/
void apsDataManagerProcess(void);

/*****************************************************************************
  APS Data Manager apsCounter get function
  Parameters: None
  Returns: apsCounter value
*****************************************************************************/
extern uint8_t apsGetApsCounter(void);

/*****************************************************************************
  APS Data Manager nsduHandle get function
  Parameters: None
  Returns: nsduHandle value
*****************************************************************************/
extern uint8_t apsGetNsduHandle(void);

/*****************************************************************************
  Routine for IEEE addressing. Extended address by NWK short address
  mapping function.
  Parameters: shortAddr - NWK short address pointer
  Returns: valid IEEE 64-bit address pointer if success
           NULL in other case
*****************************************************************************/
extern const ExtAddr_t *apsFindExtByShort(ShortAddr_t *shortAddr);

/*****************************************************************************
  Routine for IEEE addressing. NWK address by Extended 64-bit address
  mapping function.
  Parameters: extAddr - extended 64-bit IEEE address pointer
  Returns: valid unicast NWK short address pointer
           NULL in other case
*****************************************************************************/
extern const ShortAddr_t *apsFindShortByExt(ExtAddr_t *extAddr);

extern void apsMakeNwkDataResp(NWK_DataInd_t *ind);

extern ExtAddr_t *apsGetOwnExtAddress(void);

extern void apsDmHotReset(void);

/**************************************************************************//***
  \brief  Process the NLDE-DATA.indication primitive and make an indication to
          NHLE or transmit an acknowledgement frame to NWK.

  \param  nwkInd - NLDE-DATA.indication primitive pointer.
          securityStatus - securityStatus field value should be used in 
          APS_DataInd primitive.
  \return true -  if the NWK Data Response needs to be executed for this 
          indication, false - in other case.
*******************************************************************************/
extern bool apsNwkDataIndHandler(NWK_DataInd_t *nwkDataInd, APS_Status_t securityStatus);


/*************************************************************************//**
  \brief Frame encryption is finished

  \param buffer - buffer wich was encrypted
  \param status - status of operation
  \return none
*****************************************************************************/
void apsEncryptDataFrameConf(ApsDataBuffer_t *buffer, uint8_t* pdu, uint8_t pduLength, uint8_t status);

/*****************************************************************************
  Indicates that sent frame which was previously encrypted is decrypted.
  Parameters: buffer - APS memory buffer pointer.
  Returns: None
*****************************************************************************/
void apsDecryptSentFrameConf(ApsDataBuffer_t *buffer);

#endif  //#ifndef _APSDATAMANAGER_H

//eof apsDataManager.h
