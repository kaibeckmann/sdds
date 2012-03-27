/****************************************************************************//**
  \file halDbg.h

  \brief Declarations of hal , bsb mistake interface.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    09/11/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALDBG_H
#define _HALDBG_H

#include <dbg.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
enum
{
  APPTIMER_MISTAKE                         = 0x2000,
  INCORRECT_EEPROM_ADDRESS                 = 0x2001,
  MEMORY_CANNOT_WRITE                      = 0x2002,
  USARTC_HALUSARTRXBUFFERFILLER_0          = 0x2003,
  USARTC_HALSIGUSARTTRANSMISSIONCOMPLETE_0 = 0x2004,
  USARTC_HALSIGUSARTRECEPTIONCOMPLETE_0    = 0x2005,
  HALUSARTH_HALCLOSEUSART_0                = 0X2006,
  HALUSARTH_HALENABLEUSARTDREMINTERRUPT_0  = 0X2007,
  HALUSARTH_HALDISABLEUSARTDREMINTERRUPT_0 = 0X2008,
  HALUSARTH_HALENABLEUSARTTXCINTERRUPT_0   = 0X2009,
  HALUSARTH_HALDISABLEUSARTTXCINTERRUPT_0  = 0X200A,
  HALUSARTH_HALENABLEUSARTRXCINTERRUPT_0   = 0X200B,
  HALUSARTH_HALDISABLEUSARTRXCINTERRUPT_0  = 0X200C,
  HALUSARTH_HALSENDUSARTBYTE_0             = 0X200D,
  USARTC_HALUSARTSAVEERRORREASON           = 0x200E,
  USARTC_HALSIGUSARTERROROCCURED_0         = 0x200F,
  USARTC_HALUNKNOWNERRORREASON_0           = 0x2010
};

/******************************************************************************
                   Prototypes section
******************************************************************************/

#endif /* _HALDBG_H */

// eof halDbg.h
