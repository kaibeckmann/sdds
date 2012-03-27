/**************************************************************************//**
  \file zclOTAUCluster.h

  \brief Declaration of the private OTAU interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13.05.10 A. Khromykh - Created.
*******************************************************************************/
#ifndef _ZCLOTAUDISCOVERY_H
#define _ZCLOTAUDISCOVERY_H

/******************************************************************************
                        Includes section
******************************************************************************/
#include <zcl.h>
#include <clusters.h>
#include <zdo.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define SERVER_DISCOVERY_SERVER_BUFFER_SIZE    3

/******************************************************************************
                           Types section
******************************************************************************/
typedef struct
{
  Endpoint_t  serverEndpoint;
  ShortAddr_t serverShortAddress;
  ExtAddr_t   serverExtAddress;
} OtauServerInfo_t;

typedef struct
{
  OtauServerInfo_t  serverArray[SERVER_DISCOVERY_SERVER_BUFFER_SIZE];
  uint8_t           serverCounter;
} OtauServerArray_t;

typedef union
{
  ZDO_ZdpReq_t          zdpOtauReq;
#ifdef _ZCL_SECURITY_
  APS_RequestKeyReq_t   apsKeyReq;
#endif // _ZCL_SECURITY_
  ZCL_Request_t         zclCommandReq;
} OtauReqMemory_t;

typedef union
{
  ZCL_OtauQueryNextImageReq_t   uQueryNextImageReq;
  ZCL_OtauImageBlockReq_t       uImageBlockReq;
  ZCL_OtauUpgradeEndReq_t       uUpgradeEndReq;
} OtauZclReqMemory_t;

typedef struct
{
  uint32_t  imageInternalLength;
  uint8_t   internalAddressStatus;
  uint32_t  currentFileOffset;
  uint8_t   currentDataSize;
  uint32_t  imageRemainder;
} OtauImageAuxVar_t;

/***************************************************************************//**
  \brief
  ZCL OTAU Cluster parametres.
*******************************************************************************/
typedef struct
{
  uint32_t          imageSize;
  uint8_t           imageData[OFD_BLOCK_SIZE];
  uint8_t           upgradeEndReqCounter;
} ZclOtauClusterParameters_t;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/***************************************************************************//**
\brief Restart poll timer

\param[in] period - timer fired time
\param[in] cb     - pointer to fired method
******************************************************************************/
void otauStartGenericTimer(uint32_t period, void (* cb)(void));

/***************************************************************************//**
\brief Restart discovery service with context gap
******************************************************************************/
void otauStartPollDiscovery(void);

/***************************************************************************//**
\brief Send query next image request
******************************************************************************/
void otauQueryNextImageReq(void);

/***************************************************************************//**
\brief Start discovery of upgrade server
******************************************************************************/
void ZCL_OtauUpgradeServerDiscovery(void);

/***************************************************************************//**
\brief Server IEEE addresses request
******************************************************************************/
void otauServerExtAddrReq(void);

#endif /* _ZCLOTAUDISCOVERY_H */
