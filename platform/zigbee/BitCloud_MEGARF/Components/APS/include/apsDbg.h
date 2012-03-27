/***************************************************************************//**
  \file apsDbg.h

  \brief APS Debug Module header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    09/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSDBG_H
#define _APSDBG_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <dbg.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                   Constants section
******************************************************************************/
typedef enum
{
  /***********************************
    APS section. Range 0x4000 - 0x4FFF
  ************************************/

  //APS Data Manager Id (0x4000 - 0x40ff)
  APSDATAMANAGER_NWKDATACONFPROCESS_0         = 0x4000,
  APS_DM_UNKNOWN_BUFFER_TYPE_0                = 0x4001,
  APS_DM_MEMORY_FAULT_0                       = 0x4002,
  APS_DM_MEMORY_FAULT_1                       = 0x4003,
  APS_DM_DUPLICATE_REJECTION_TIMEOUT_OVERFLOW = 0x4004,
  APS_DM_DATA_REQ_PROCESS0                    = 0x4005,
  APS_DM_APSHANDLETRANSMITTEDDATA_0           = 0x4006,
  APS_DM_APSGETACKBYDATABUFFER_1              = 0x4007,
  APS_DM_MEMORY_FAULT_2                       = 0x4008,

  //APS Security Manager Id (0x4100 - 0x41ff)
  APS_SM_OWN_EXTADDR_ERROR                    = 0x4100,
  APS_SM_UNKNOWN_COMPONENT_ID                 = 0x4101,
  DBG_SM_MEMORY_FAULT_1,
  APS_SM_COMMAND_DATA_REQ_MEMORY_FAULT_1      = 0x4106,
  APS_SM_COMMAND_DATA_REQ_MEMORY_FAULT_2      = 0x4107,
  DBG_APS_SM_GET_PARENT_EXT_ADDR_FAULT        = 0x4108,
  APS_UNKNOWN_DECRYPTED_COMMAND_ID            = 0x4109,

  //APS Security Manager Key Establish Router (0x4200 - 0x42ff)
  DBG_APS_SM_KERO_INVALID_STATE_1             = 0x4200,
  DBG_APS_SM_KERO_INVALID_STATE_2             = 0x4201,
  DBG_APS_SM_KERO_INVALID_STATE_3             = 0x4202,
  DBG_APS_SM_KERO_MEMORY_FAULT_1              = 0x4203,
  DBG_APS_SM_KERO_MEMORY_FAULT_2              = 0x4204,


  DBG_APS_SM_KEREQ_INVALID_REQUEST            = 0x4205,
  DBG_APS_SM_KEREQ_INVALID_STATE_1            = 0x4206,
  DBG_APS_SM_KEREQ_INVALID_STATE_2            = 0x4207,
  DBG_APS_SM_KEREQ_MEMORY_FAULT_1             = 0x4208,
  DBG_APS_SM_KEREQ_MEMORY_FAULT_2             = 0x4209,

  DBG_APS_SM_KERESP_INVALID_STATE_1           = 0x420a,
  DBG_APS_SM_KERESP_INVALID_STATE_2           = 0x420b,
  DBG_APS_SM_KERESP_MEMORY_FAULT_1            = 0x420c,
  DBG_APS_SM_KERESP_MEMORY_FAULT_2            = 0x420d,
  DBG_APS_SM_KERESP_MEMORY_FAULT_3            = 0x420e,
  DBG_APS_SM_KERESP_MEMORY_FAULT_4            = 0x420f,
  DBG_APS_SM_KERESP_MEMORY_FAULT_5            = 0x4210,
  DBG_APS_SM_KERESP_MEMORY_FAULT_6            = 0x4211,
  DBG_APS_SM_KERESP_MEMORY_FAULT_7            = 0x4212,
  DBG_APS_SM_KERESP_MEMORY_FAULT_8            = 0x4213,

  DBG_APS_SM_TKR_INVALID_REQUEST              = 0x4214,
  DBG_APS_SM_TKR_INVALID_STATE_1              = 0x4215,
  DBG_APS_SM_TKR_INVALID_STATE_2              = 0x4216,
  DBG_APS_SM_TKR_MEMORY_FAULT_1               = 0x4217,
  DBG_APS_SM_TKR_MEMORY_FAULT_2               = 0x4218,

  DBG_APS_SM_UDR_INVALID_REQUEST              = 0x4219,
  DBG_APS_SM_UDR_INVALID_STATE_1              = 0x421a,
  DBG_APS_SM_UDR_INVALID_STATE_2              = 0x421b,

  DBG_APS_SM_TRANSACTION_MEMORY_FAULT_1       = 0x421c,

  //DBG_APS_SM_ENCRYPTION_MEMORY_FAULT_1        = 0x421d,
  //DBG_APS_SM_ENCRYPTION_MEMORY_FAULT_2        = 0x421e,

  //DBG_APS_SM_DECRYPTION_MEMORY_FAULT_1        = 0x421f,

  //DBG_SM_INVALID_SSP_SKKE_CONF                = 0x4220,

  /* APS_SM_SSPE */
  DBG_APS_SM_SSPE_INVALID_BUFFER_TYPE         = 0x4221,

  //DBG_APS_SM_EKREQ_MEMORY_FAULT_1             = 0x4222,
  //DBG_APS_SM_EKREQ_MEMORY_FAULT_1             = 0x4223,
  DBG_APS_SM_EKREQ_INVALID_IND                = 0x4224,

  DBG_APS_SM_EKRESP_INVALID_RESP              = 0x4225,
  DBG_APS_SM_EKRESP_INVALID_NWK_CONF          = 0x4226,
  DBG_APS_SM_EKRESP_INVALID_STATE_1           = 0x4227,
  DBG_APS_SM_EKRESP_INVALID_STATE_2           = 0x4228,

  DBG_APS_SM_AUI_INVALID_REQ                  = 0x4229,

  APS_DM_UNKNOWN_BUFFER_TYPE_1                = 0x422a,
  APSSMSSP_APSSMDECRYPTSENTFRAMECONF_0        = 0x422b,
  DBG_APS_FRAGMENTATION_RECEIVE_0             = 0x422c,
  DBG_APS_FRAGMENTATION_RECEIVE_1             = 0x422d,
  APSMEMORYMANAGER_GETMEMORY_0                = 0x422e,
  APSMEMORYMANAGER_GETMEMORY_1                = 0x422f,
  APSMEMORYMANAGER_FREEBUFFER_0               = 0x4230,
  APSMEMORYMANAGER_FREEBUFFER_1               = 0x4231,
  APSMEMORYMANAGER_FREEBUFFER_2               = 0x4232,
  APSMEMORYMANAGER_FREEBUFFER_3               = 0x4233,
  APSMEMORYMANAGER_FREEBUFFER_4               = 0x4234,
  APSSMSSP_APSENCRYPTFRAME_0                  = 0x4235,
  APSMEMORYMANAGER_FREEBUFFER_6               = 0x4236,

  APS_DM_NWKDATACONFPROCESS_0                 = 0x4237,
  APS_DM_NWKDATACONFPROCESS_1                 = 0x4238,
  APS_DM_NWKDATACONFPROCESS_2                 = 0x4239,
  APS_DM_NWKDATACONFPROCESS_3                 = 0x423A,
  APS_DM_APDUACKHANDLER_0                     = 0x423B,
  APS_SMSSP_SMSSPPROCESS_0                    = 0x423C,

  APS_TUNNEL_APSTUNNELTRANSPORTKEYREQ_0       = 0x423D,
  APSGROUPMANAGER_APSADDGROUPREQ0             = 0x423E,
  APSGROUPMANAGER_APSREMOVEGROUPREQ0          = 0x423F,
  APSGROUPMANAGER_APSREMOVEALLGROUPSREQ0      = 0x4240,

  // NULL Pointer asserts 0x4300 - 0x43ff
  DBG_APS_NULL_POINTER_0  = 0x4300, // apsDataManager.c apsMakeApsDataConf()
  DBG_APS_NULL_POINTER_1  = 0x4301, // apsDataManager.c apsNwkDataConfProcess()
  DBG_APS_NULL_POINTER_2  = 0x4302, // apsControlManager.c apsSendStopConf()
  DBG_APS_NULL_POINTER_3  = 0x4303, // apsControlManager.c apsNwkResetConf()
  DBG_APS_NULL_POINTER_4  = 0x4304, // apsControlManager.c APS_StartReq()
  DBG_APS_NULL_POINTER_5  = 0x4305, // apsControlManager.c apsSendStopConf()
  DBG_APS_NULL_POINTER_6  = 0x4306, // apsDataManager.c apsMakeNwkDataResp()
  DBG_APS_NULL_POINTER_7  = 0x4307, // apsSmRdi.c sendRdc()
  DBG_APS_NULL_POINTER_8  = 0x4308, // apsSmSkr.c sendSkc()
  DBG_APS_NULL_POINTER_9  = 0x4309, // apsSmTkr.c sendTkc()
  DBG_APS_NULL_POINTER_10 = 0x430a, // apsSmUdr.c sendUdc()
  DBG_APS_NULL_POINTER_11 = 0x430b, // apsInterpan.c intrpReqProcess()
  DBG_APS_NULL_POINTER_12 = 0x430c, // apsInterpan.c intrpMACDataConfProccess()
  DBG_APS_NULL_POINTER_13 = 0x430d,
  DBG_APS_NULL_POINTER_14 = 0x430e,
  DBG_APS_NULL_POINTER_15 = 0x430f,
  DBG_APS_NULL_POINTER_16 = 0x4310,
  DBG_APS_NULL_POINTER_17 = 0x4311,
} ApsDbgCodeId_t;

typedef enum
{
  LOG_APS_APS_DATA_REQ,
  LOG_APS_NWK_DATA_REQ
} ApsLogCodeId_t;

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
                   Inline static functions section
******************************************************************************/


#endif  //#ifndef _APSDBG_H

//eof apsDbg.h
