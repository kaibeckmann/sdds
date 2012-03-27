/**************************************************************************//**
  \file  nwkAddress.h

  \brief Formation header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2009-05-12 M. Gekk - Created.
   Last change:
    $Id: nwkAddress.h 12570 2010-09-24 20:25:34Z mgekk $
 ******************************************************************************/
#if !defined _NWK_ADDRESS_H
#define  _NWK_ADDRESS_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwkConfig.h>
#include <types.h>
#include <mac.h>
#include <nwkCommon.h>
#include <nwkSystem.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _COORDINATOR_ || defined _ROUTER_
/**************************************************************************//**
  \brief Allocate short address.

  \param[in] router - parameters is used if tree addressing is active.
  \param[in] addrRequested - if rejoin is used, it is address device selects for
     itself otherwise NWK_NO_SHORT_ADDR.
  \param[in] extAddr - IEEE extended address of node.
  \return Allocated address. addrRequested - is possible,
          or address allocated in little endian.
 ******************************************************************************/
NWK_PRIVATE ShortAddr_t nwkAllocateShortAddr(const bool router,
  const ShortAddr_t addrRequested, const ExtAddr_t extAddr);
#endif /* _COORDINATOR_ or _ROUTER_ */

#if defined _NWK_DISTRIBUTED_ADDRESSING_
/**************************************************************************//**
  \brief Computing the size of the address sub-block.

  \param[in] depth - current depth of node in network tree topology.
  \return cskip block in big endian format.
 ******************************************************************************/
NWK_PRIVATE NwkAddrRange_t nwkCSkip(const NwkDepth_t depth);
#endif /* _NWK_DISTRIBUTED_ADDRESSING_ */
#endif  /* _NWK_ADDRESS_H */
/** eof nwkAddress.h */

