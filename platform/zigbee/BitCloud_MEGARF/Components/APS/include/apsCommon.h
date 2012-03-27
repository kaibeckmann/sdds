/**************************************************************************//**
  \file apsCommon.h

  \brief Declarations of common APS layer's constants and types.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    21/07/2010 Max Gekk - Created.
 ******************************************************************************/
#ifndef _APS_COMMON_H
#define _APS_COMMON_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwk.h>
#include <appFramework.h>
#include <macAddr.h>

/******************************************************************************
                               Definitions section
 ******************************************************************************/

#ifndef _HIGH_SECURITY_
/**************************************************************************//**
  \brief Max APS header size.
 ******************************************************************************/
#define APS_MAX_DATA_FRAME_HEADER_LENGTH  12

/**************************************************************************//**
  \brief Max APS footer size.
 ******************************************************************************/
#define APS_MAX_DATA_FRAME_FOOTER_LENGTH  0
#else /* _HIGH_SECURITY_ */

/**************************************************************************//**
  \brief APS auxiliary header size.

  See ZigBee spec. r18, 4.5.1.1, Security Control Field.
 ******************************************************************************/
#define APS_AUXILIARY_HEADER_LENGTH  6

/**************************************************************************//**
  \brief Max APS header size.
 ******************************************************************************/
#define APS_MAX_DATA_FRAME_HEADER_LENGTH  (12 + APS_AUXILIARY_HEADER_LENGTH)

/**************************************************************************//**
  \brief Max APS footer size.
 ******************************************************************************/
#if (CS_SECURITY_LEVEL == 0x05)
  /* 4 bytes - Message Integrity Code (MIC) */
  #define APS_MAX_DATA_FRAME_FOOTER_LENGTH  4        
#elif (CS_SECURITY_LEVEL == 0x06)
  /* 8 bytes - Message Integrity Code (MIC) */
  #define APS_MAX_DATA_FRAME_FOOTER_LENGTH  8        
#elif (CS_SECURITY_LEVEL == 0x07)
  /* 15 bytes - Message Integrity Code (MIC) */
  #define APS_MAX_DATA_FRAME_FOOTER_LENGTH  16       
#endif /* SECURITY_LEVEL parsing */

/**************************************************************************//**
  \brief Universal extended address.
 ******************************************************************************/
#ifdef _UNIVERSAL_EXTENDED_ADDRESS_
    #define APS_UNIVERSAL_EXTENDED_ADDRESS 0xFFFFFFFFFFFFFFFBLL
#endif /* _UNIVERSAL_EXTENDED_ADDRESS_ */

#endif /* _HIGH_SECURITY_ */

/**************************************************************************//**
  \brief Max size of APS payload.
 ******************************************************************************/
#define APS_MAX_ASDU_SIZE \
  (NWK_MAX_NSDU_SIZE - APS_MAX_DATA_FRAME_HEADER_LENGTH - APS_MAX_DATA_FRAME_FOOTER_LENGTH)

/**************************************************************************//**
  \brief Size of the reserved header in the data frame
  *****************************************************************************/
#define APS_ASDU_OFFSET \
  (NWK_NSDU_OFFSET + APS_MAX_DATA_FRAME_HEADER_LENGTH)

/**************************************************************************//**
  \brief Size of the reserved part in the data frame
 ******************************************************************************/
#define APS_AFFIX_LENGTH \
  (APS_MAX_DATA_FRAME_HEADER_LENGTH + APS_MAX_DATA_FRAME_FOOTER_LENGTH + NWK_AFFIX_LENGTH)

/**************************************************************************//**
  \brief APS Broadcast Endpoint.
 ******************************************************************************/
#define APS_BROADCAST_ENDPOINT      0xff

/**************************************************************************//**
  \brief Min user endpoint number.
 ******************************************************************************/
#define APS_MIN_USER_ENDPOINT       0x01

/**************************************************************************//**
  \brief Max user endpoint number
 ******************************************************************************/
#define APS_MAX_USER_ENDPOINT       0xf0

/** ZDO Endpoint */
#define APS_ZDO_ENDPOINT            0x00

/** Reserved endpoints */
#define APS_MIN_RESERVED_ENDPOINT   0xf1
#define APS_MAX_RESERVED_ENDPOINT   0xfe

/** APS short address defines */
#define APS_MAX_UNICAST_SHORT_ADDRESS     0xfff7

/******************************************************************************
                                 Types section
 ******************************************************************************/
/**************************************************************************//**
  \brief Common APS Address type.

    Used as the part of standard APS primitives
 ******************************************************************************/
typedef struct _APS_Address_t
{
  union
  {
    ShortAddr_t shortAddress; /*!< 16-bit network address */
#ifdef _APS_MULTICAST_
    GroupAddr_t groupAddress; /*!< 16-bit group (multicast) address */
#endif
  };
  ExtAddr_t extAddress;     /*!< 64-bit extended IEEE address */
} APS_Address_t;

/**************************************************************************//**
  \brief APS addressing modes.

    Defines APS addressing modes used in some standard primitives.
 ******************************************************************************/
typedef enum _APS_AddrMode_t
{
  APS_NO_ADDRESS        = 0x00,   /*!< Indirect addressing mode via binding future. */
  APS_GROUP_ADDRESS     = 0x01,   /*!< Group addressing mode via multicast. */
  APS_SHORT_ADDRESS     = 0x02,   /*!< Unicast addressing mode by 16-bit network address. */
  APS_EXT_ADDRESS       = 0x03    /*!< Unicast addressing mode by 64-bit IEEE address. */
} APS_AddrMode_t;

/**************************************************************************//**
  \brief APS status values.

    APS status values used in the most part of standard primives except
    for the security service primitives where APS_SecurityStatus_t is used
    instead
 ******************************************************************************/
typedef enum _APS_Status_t
{
  APS_SUCCESS_STATUS                      = 0x00,
  APS_ASDU_TOO_LONG_STATUS                = 0xa0,
  APS_DEFRAG_DEFERRED_STATUS              = 0xa1,
  APS_DEFRAG_UNSUPPORTED_STATUS           = 0xa2,
  APS_ILLEGAL_REQUEST_STATUS              = 0xa3,
  APS_INVALID_BINDING_STATUS              = 0xa4,
  APS_INVALID_GROUP_STATUS                = 0xa5,
  APS_INVALID_PARAMETER_STATUS            = 0xa6,
  APS_NO_ACK_STATUS                       = 0xa7,
  APS_NO_BOUND_DEVICE_STATUS              = 0xa8,
  APS_NO_SHORT_ADDRESS_STATUS             = 0xa9,
  APS_NOT_SUPPORTED_STATUS                = 0xaa,
  APS_SECURED_LINK_KEY_STATUS             = 0xab,
  APS_SECURED_NWK_KEY_STATUS              = 0xac,
  APS_SECURITY_FAIL_STATUS                = 0xad,
  APS_TABLE_FULL_STATUS                   = 0xae,
  APS_UNSECURED_STATUS                    = 0xaf,
  APS_UNSUPPORTED_ATTRIBUTE_STATUS        = 0xb0
} APS_Status_t;

#endif /* _APS_COMMON_H */
/** eof apsCommon.h */

