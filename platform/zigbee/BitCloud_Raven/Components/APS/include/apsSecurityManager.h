/*************************************************************************//**
  \file apsSecurityManager.h

  \brief APS Security Manager header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSECURITYMANAGER_H
#define _APSSECURITYMANAGER_H

#ifdef _SECURITY_


/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <aps.h>
#include <nwk.h>
#include <apsFrames.h>
#include <apsMemoryManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define APS_SM_INVALID_FRAME_COUNTER_VALUE  (0xffffffffL)

#define APS_SM_BROADCAST_EXT_ADDRESS                        0xffffffffffffffffLL
#define APS_SM_BROADCAST_ALL_EXT_ADDRESS                    0xffffffffffffffffLL
#define APS_SM_BROADCAST_RX_ON_WHEN_IDLE_EXT_ADDRESS        0xfffffffffffffffdLL
#define APS_SM_BROADCAST_ALL_ROUTERS_EXT_ADDRESS            0xfffffffffffffffcLL
#define APS_SM_BROADCAST_LOW_POWER_ROUTERS_EXT_ADDRESS      0xfffffffffffffffbLL

#define APS_SM_UNIVERSAL_TRUST_CENTER_EXT_ADDRESS           0xfffffffffffffffaLL

#define APS_SM_INVALID_EXT_ADDRESS                          0x0000000000000000LL


/******************************************************************************
                   Types section
******************************************************************************/
typedef enum _ApsSecurityComponentId_t
{
  APS_SM_EKREQ_ID = 0x00,   //Establish Key Request (initiator)
  APS_SM_EKRESP_ID,         //Establish Key Responder
  APS_SM_EKRO_ID,           //Establish Key Router
  APS_SM_TKR_ID,            //Transport Key Request
  APS_SM_TKI_ID,            //Transport Key Indication
  APS_SM_UDR_ID,            //Update Device Request
  APS_SM_UDI_ID,            //Update Device Indication
  APS_SM_RDR_ID,            //Remove Device Request
  APS_SM_RDI_ID,            //Remove Device Indication
  APS_SM_RKR_ID,            //Request Key Request
  APS_SM_RKI_ID,            //Request Key Indication
  APS_SM_SKR_ID,            //Switch Key Request
  APS_SM_SKI_ID,            //Switch Key Indication
  APS_SM_AUR_ID,            //Authenticate Request
  APS_SM_AUI_ID,            //Authenticate Indication
  APS_SM_MM_ID,
  APS_SM_SSP_ID,
  APS_SM_DUMMY_ID
} ApsSecurityComponentId_t;

#ifdef _HIGH_SECURITY_
typedef struct _ApsDeviceKeyPairSet_t
{
  uint8_t amount;
  ApsKeyPairDescriptor_t *keyPairDescriptors;
} ApsDeviceKeyPairSet_t;
#endif //#ifdef _HIGH_SECURITY_


/******************************************************************************
                   Constants section
******************************************************************************/
typedef enum _ApsSecurityCommandId_t
{
  APS_CMD_SKKE_1_ID                = 0x01,
  APS_CMD_SKKE_2_ID                = 0x02,
  APS_CMD_SKKE_3_ID                = 0x03,
  APS_CMD_SKKE_4_ID                = 0x04,
  APS_CMD_TRANSPORT_KEY_ID         = 0x05,
  APS_CMD_UPDATE_DEVICE_ID         = 0x06,
  APS_CMD_REMOVE_DEVICE_ID         = 0x07,
  APS_CMD_REQUEST_KEY_ID           = 0x08,
  APS_CMD_SWITCH_KEY_ID            = 0x09,
  APS_CMD_EA_INIT_CHLNG_ID         = 0x0a,
  APS_CMD_EA_RSP_CHLNG_ID          = 0x0b,
  APS_CMD_EA_INIT_MAC_DATA_ID      = 0x0c,
  APS_CMD_EA_RSP_MAC_DATA_ID       = 0x0d,
  APS_CMD_TUNNEL_ID                = 0x0e
} ApsSecurityCommandId_t;

/******************************************************************************
                   External variables section
******************************************************************************/
#ifdef _HIGH_SECURITY_
extern ApsDeviceKeyPairSet_t apsDeviceKeyPairSet;
#endif //#ifdef _HIGH_SECURITY_

/******************************************************************************
                   Prototypes section
******************************************************************************/
extern void apsSecurityManagerReset(bool powerFailure);
extern void apsSecurityManagerProcess(void);
extern bool apsCommandReceiveProcess(NWK_DataInd_t *ind);
extern void apsSmPostTask(uint8_t apsSmComponentId);
extern uint8_t apsSmGetFreeBuffersAmount(void);
extern void apsSmMakeCommandHeader(ApduCommandHeader_t *header, uint8_t commandId);
extern NwkNeighbor_t *apsFindNeibByExtAddr(ExtAddr_t *extAddr);
extern NwkNeighbor_t *apsFindNeibByShortAddr(ShortAddr_t *shortAddr);
extern uint32_t apsGetPollPeriod(void);
extern ShortAddr_t apsGetParentShortAddr(void);
extern bool apsIsKeyValid(uint8_t *key);
extern void apsSmAddToAddrMapTable(ExtAddr_t *extAddr, ShortAddr_t *shortAddr);
extern void apsDecryptedCommandReceiveProcess(ApsSecBuffer_t *buffer);
extern void apsSmSetTimeout(ApsSecBuffer_t *buffer, uint32_t timeout);

/******************************************************************************
                   Inline static functions section
******************************************************************************/
#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSECURITYMANAGER_H

//eof apsSecurityManager.h
