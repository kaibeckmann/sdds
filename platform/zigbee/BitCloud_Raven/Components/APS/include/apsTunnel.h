/**************************************************************************//**
  \file  apsTunnel.h

  \brief Interface of APS tunneling.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    03/06/2010 Max Gekk - Created.
 ******************************************************************************/
#ifndef _APS_TUNNEL_H
#define _APS_TUNNEL_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <apsMemoryManager.h>

#if defined _SECURITY_ && defined _HIGH_SECURITY_
/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Processing of a tunnelling APS command.
    
    Extracting the embedded tunnel command and send it to destination.

  \param[in]  ind - pointer to NWK data indication parameter's structure..

  \return 'true' if NWK buffer should be released otherwise 'false'.
 ******************************************************************************/
bool apsTunnelNwkDataInd(NWK_DataInd_t *const ind);

/**************************************************************************//**
  \brief Tunnel the encrypted transport key command.
  
  \param[in] dstAddr - destination short address of APS tunneling command
  \param[in] buffer - pointer to APS security command buffer with encrypted
                       transport key command
  \param[in] pdu - pointer to encrypted data.
  \param[in] pduLength - total length of the transport key command: APS header,
                          Aux header, payload and MIC.

  \return None.
 ******************************************************************************/
void apsTunnelTransportKeyReq(const ShortAddr_t  dstAddr, ApsSecBuffer_t *const buffer, 
  uint8_t *const pdu, const uint8_t pduLength);

#endif /* _HIGH_SECURITY_ */
#endif /* _APS_TUNNEL_H */
/* eof apsTunnel.h */

