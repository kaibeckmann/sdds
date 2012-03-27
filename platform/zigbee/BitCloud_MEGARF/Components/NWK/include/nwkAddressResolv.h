/**************************************************************************//**
  \file nwkAddressResolv.h

  \brief Interface of address resolution.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2010-07-04 Max Gekk - Created.
   Last change:
    $Id: nwkAddressResolv.h 12575 2010-09-25 21:25:48Z mgekk $
 ******************************************************************************/
#if !defined _NWK_ADDRESS_RESOLV_H
#define _NWK_ADDRESS_RESOLV_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <appFramework.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Link short network and IEEE extended address.

  \param[in] shortAddr - a short address.
  \param[in] extAddr - an extended address.
  \return 'true' if short and extended addresses are linked successfully
    otherwise 'false'.
 ******************************************************************************/
bool NWK_LinkShortAndExtAddress(const ShortAddr_t shortAddr,
  const ExtAddr_t extAddr);

/**************************************************************************//**
  \brief Searching a extended address by the short address.

  \param[in] shortAddr - a short address.
  \return Pointer to the extended address in the address map.
 ******************************************************************************/
const ExtAddr_t*  NWK_GetExtByShortAddress(const ShortAddr_t shortAddr);

/**************************************************************************//**
  \brief Searching a short address by the extended address.

  \param[in] extAddr - pointer to the extended address.
  \return Pointer to the short address in the address map.
 ******************************************************************************/
const ShortAddr_t*  NWK_GetShortByExtAddress(const ExtAddr_t *const extAddr);

#endif /* _NWK_ADDRESS_RESOLV_H */
/** eof nwkAddressResolv.h */

