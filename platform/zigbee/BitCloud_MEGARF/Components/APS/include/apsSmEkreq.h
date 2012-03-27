/*************************************************************************//**
  \file apsSmEkreq.h

  \brief APSME-ESTABLISH-KEY.request feature header file
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
           
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/


#ifndef _APSSMEKREQ_H
#define _APSSMEKREQ_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
#ifdef _USE_SKKE_

#include <aps.h>
#include <apsMemoryManager.h>

extern bool apsSmEkreqNwkDataInd(NWK_DataInd_t *ind);
extern void apsResetSmEkreq(void);
extern void apsSmEkreqProcess(void);
extern void apsSmEkreqTimeoutHandler(ApsSecBuffer_t *sspReq);

#endif // _USE_SKKE_
#endif // _HIGH_SECURITY_
#endif // _SECURITY_

#endif  //#ifndef _APSSMKEREQ_H

//eof apsSmEkreq.h
