/*************************************************************************//**
  \file apsSmEkresp.h

  \brief SKKE Protocol Responder Role features header file
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMEKRESP_H
#define _APSSMEKRESP_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
#ifdef _USE_SKKE_

#include <aps.h>
#include <apsMemoryManager.h>

extern bool apsSmEkrespNwkDataInd(NWK_DataInd_t *ind);
extern void apsSmEkrespProcess(void);
extern void apsResetSmEkresp(void);
extern void apsSmEkrespTimeoutHandler(ApsSecBuffer_t *sspReq);

#endif // _USE_SKKE_
#endif // _HIGH_SECURITY_
#endif // _SECURITY_

#endif //#ifndef _APSSMEKRESP_H

//eof apsSmEkresp.h
