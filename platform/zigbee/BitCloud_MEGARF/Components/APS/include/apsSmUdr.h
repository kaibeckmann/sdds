/*************************************************************************//**
  \file apsSmUdr.h

  \brief APSME-UPDATE-DEVICE.request feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMUDR_H
#define _APSSMUDR_H

#ifdef _SECURITY_
#include <apsMemoryManager.h>

extern void apsSmUdrProcess(void);
extern void apsSmUdrSspConf(ApsSecBuffer_t *buffer, uint8_t *pdu, uint8_t pduLength, uint8_t status);
extern void apsResetSmUdr(void);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMUDR_H

//eof apsSmUdr.h
