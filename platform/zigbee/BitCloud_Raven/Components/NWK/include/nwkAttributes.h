/**************************************************************************//**
 \file nwkAttributes.h

 \brief Interface of network attributes.

 \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2009-05-01 Max Gekk - Created
   Last change:
    $Id: nwkAttributes.h 12575 2010-09-25 21:25:48Z mgekk $
 ******************************************************************************/
#if !defined _NWK_ATTRIBUTES_H
#define _NWK_ATTRIBUTES_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <nwkCommon.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief This function return a short address that is allocated by parent.

  \return Short address of this node or NWK_NO_SHORT_ADDR.
 ******************************************************************************/
ShortAddr_t NWK_GetShortAddr(void);

/**************************************************************************//**
  \brief Setting new short address of this device.

  \param[in] shortAddr - new short (16-bit) address.
  \return NWK_SUCCESS_STATUS - if this request is valid
     otherwise NWK_NOT_PERMITTED_STATUS.
 ******************************************************************************/
NWK_Status_t NWK_SetShortAddr(const ShortAddr_t shortAddr);

/**************************************************************************//**
  \brief This function return a short address of parent.

  \return Short address of parent device or NWK_NO_SHORT_ADDR
 ******************************************************************************/
ShortAddr_t NWK_GetParentShortAddr(void);

/**************************************************************************//**
  \brief This function return a short panid of network.

  \return short panid or 0xFFFF
 ******************************************************************************/
PanId_t NWK_GetPanId(void);

/**************************************************************************//**
  \brief This function return a extended panid of network.

  \return extended panid or 0
 ******************************************************************************/
ExtPanId_t NWK_GetExtPanId(void);

/**************************************************************************//**
  \brief Current RF channel.
 ******************************************************************************/
Channel_t NWK_GetLogicalChannel(void);

/**************************************************************************//**
  \brief Setting a new RF channel.

  \param[in] channel - the number of new channel.
 ******************************************************************************/
void NWK_SetLogicalChannel(const Channel_t channel);

/**************************************************************************//**
  \brief Maximum delivery time of broadcasting transmission on a network.

    Distination nodes of broadcasting transmission are only full function devices.

  \return Current value of broadcast delivery time in seconds.
 ******************************************************************************/
uint8_t NWK_GetBroadcastDeliveryTime(void);

/**************************************************************************//**
  \brief Medium delivery time of unicast data transmission on a network.

  \return Current value of unicast delivery time in milliseconds.
 ******************************************************************************/
uint32_t NWK_GetUnicastDeliveryTime(void);

/**************************************************************************//**
  \brief Set a short address of the network manager.

  \param[in] - short address of the network manager.
 ******************************************************************************/
void NWK_SetManagerAddr(const ShortAddr_t  shortAddr);

/**************************************************************************//**
  \brief Set a id of network snapshot.

  \param[in] - new value of the update identifier.
 ******************************************************************************/
void NWK_SetUpdateId(const NwkUpdateId_t updateId);

/**************************************************************************//**
  \brief Sets symmetric link attribute value.

  \param[in] symLink - new symmetric link attribute value.
  \return None.
 ******************************************************************************/
void NWK_SetSymLink(const bool symLink);

/**************************************************************************//**
  \brief Changing the route fail order.

    After 2^order failure attempts a route entry will be deleted.

  \param[in] order - new order of route fail.
  \return None.
 ******************************************************************************/
void NWK_SetRouteFailOrder(const uint8_t order);

#endif /* _NWK_ATTRIBUTES_H */
/** eof nwkAttributes.h */

