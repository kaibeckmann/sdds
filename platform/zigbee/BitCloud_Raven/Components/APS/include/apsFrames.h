/*****************************************************************************
  \file  apsFrames.h

  \brief 

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    16.04.2010 I.Vagulin - Created
******************************************************************************/


#ifndef _APSFRAMES_H_
#define _APSFRAMES_H_

#include <bcEndian.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#define APS_SM_KEY_SIZE                       16

#define APS_BROADCAST_MAC_RX_ON_SHORT_ADDRESS           0xfffd

//APDU Frame Format

//Frame control field - ApduFrameControlField_t

//Frame Type subfield values
#define APDU_FRAME_CONTROL_FIELD_DATA_FRAME_TYPE                  0x00
#define APDU_FRAME_CONTROL_FIELD_COMMAND_FRAME_TYPE               0x01
#define APDU_FRAME_CONTROL_FIELD_ACK_FRAME_TYPE                   0x02
#define APDU_FRAME_CONTROL_FIELD_RESERVED_FRAME_TYPE              0x03
#ifdef _INTERPAN_
/*
 ZigBee Smart Energy profile specification r15
 B.4 Frame Formats
 */
#define APDU_FRAME_CONTROL_FIELD_INTERPAN_FRAME_TYPE              0x03
#endif //_INTERPAN_

//Delivery Mode subfield values
#define APDU_FRAME_CONTROL_FIELD_UNICAST_MODE                     0x00
#define APDU_FRAME_CONTROL_FIELD_RESERVED_MODE                    0x01
#define APDU_FRAME_CONTROL_FIELD_BROADCAST_MODE                   0x02
#define APDU_FRAME_CONTROL_FIELD_GROUP_ADDRESSING_MODE            0x03

//Ack Format subfiel values
#define APDU_FRAME_CONTROL_FIELD_DATA_ACK_FORMAT                  0x00
#define APDU_FRAME_CONTROL_FIELD_COMMAND_ACK_FORMAT               0x01

//Security subfield values
#define APDU_FRAME_CONTROL_FIELD_NOTSECURED                       0x00
#define APDU_FRAME_CONTROL_FIELD_SECURED                          0x01

//Acknowledgement Request subfield values
#define APDU_FRAME_CONTROL_FIELD_NOACK                            0x00
#define APDU_FRAME_CONTROL_FIELD_ACK                              0x01

//Extended Header Present subfield values
#define APDU_FRAME_CONTROL_FIELD_EXTENDED_HEADER_NOT_PRESENT      0x00
#define APDU_FRAME_CONTROL_FIELD_EXTENDED_HEADER_PRESENT          0x01


//Extended Frame Control field - ApduExtendedFrameControlField_t
//Fragmentation subfield values
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_NOT_FRAGMENTED   0x00
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_FIRST_FRAGMENT   0x01
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_FRAGMENT         0x02
#define APDU_EXT_FRAME_CONTROL_FIELD_FRAGMENTATION_RESERVED         0x03

/* Macros is used to compress APS_UNSECURED_STATUS=0xaf, APS_SECURED_NWK_KEY_STATUS=0xac and
APS_SECURED_LINK_KEY_STATUS=0xab values to 2 unique bits*/

#define APS_COMPRESS_SECURITY_STATUS(status) ((status & 0x06) >> 1)

/* Tunneled auxiliary header consists of:
 * - security control field (1 octet),
 * - frame counter field (4 octets),
 * - source address (8 octets) */
#define APS_TUNNELED_AUXILIARY_HEADER_LEN  13
/* See ZigBee spec. r18, page 493, Table 4.38. For security level = 0x05. */
#define APS_TUNNELED_MIC_LEN               4

#define  APS_SINGLE_COMMAND_PAYLOAD \
  ApsSKKECommandPayload_t           skke;           \
  ApsTransportKeyCommandPayload_t   transportKey;   \
  ApsUpdateDeviceCommandPayload_t   updateDevice;   \
  ApsRemoveDeviceCommandPayload_t   removeDevice;   \
  ApsRequestKeyCommandPayload_t     requestKey;     \
  ApsSwitchKeyCommandPayload_t      switchKey;      \
  ApsAuthChallengeCommandPayload_t  authChallenge;  \
  ApsAuthMacAndDataCommandPayload_t authMacData

/******************************************************************************
                   Types section
******************************************************************************/
//APDU Frame Format
//Frame control field
BEGIN_PACK
typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(6, (
    uint8_t frameType               :2,
    uint8_t deliveryMode            :2,
    uint8_t ackFormat               :1,
    uint8_t security                :1,
    uint8_t ackRequest              :1,
    uint8_t extendedHeaderPresent   :1
  ))
} ApduFrameControlField_t;

//Extended Frame Control field
typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(2, (
    uint8_t fragmentation   :2,
    uint8_t reserved        :6
  ))
} ApduExtendedFrameControlField_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
  uint8_t blockNumber;
  uint8_t ackBitfield;
} ApduFragmentedAckExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
} ApduNotFragmentedAckExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
  uint8_t blockNumber;
} ApduFragmentedDataExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduExtendedFrameControlField_t extendedFrameControl;
} ApduNotFragmentedDataExtendedHeaderSubframe_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;
  uint8_t dstEndpoint;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;
  union PACK
  {
    ApduNotFragmentedDataExtendedHeaderSubframe_t notFragmentedExtHeaderSubframe;
    ApduFragmentedDataExtendedHeaderSubframe_t fragmentedExtHeaderSubframe;    //Extended header subframe
  };
} ApduDataFrameNongroup_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;
  uint16_t groupAddress;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;
} ApduDataFrameGroup_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;                 //Frame Control field
  uint8_t dstEndpoint;                                  //Destination endpoint
  uint16_t clusterId;                                   //Cluster identifier
  uint16_t profileId;                                   //Profile identifier
  uint8_t srcEndpoint;                                  //Source endpoint
  uint8_t apsCounter;                                   //APS counter
  union PACK
  {
    ApduNotFragmentedAckExtendedHeaderSubframe_t notFragmentedExtHeaderSubframe;
    ApduFragmentedAckExtendedHeaderSubframe_t fragmentedExtHeaderSubframe;    //Extended header subframe
  };
} ApduAcknowledgementFrame_t;

typedef struct PACK
{
  ApduFrameControlField_t frameControl;                 //Frame Control field
  uint8_t apsCounter;                                   //APS counter
} ApduCommandAcknowledgementFrame_t;

typedef struct PACK _ApduCommandBaseHeader_t
{
  ApduFrameControlField_t frameControl;
  uint8_t apsCounter;
} ApduCommandBaseHeader_t;

typedef struct PACK _ApduCommandHeader_t
{
  ApduFrameControlField_t frameControl;
  uint8_t apsCounter;
  uint8_t commandId;
} ApduCommandHeader_t;

typedef struct PACK _ApsSKKECommandPayload_t
{
  ExtAddr_t initiatorAddress;
  ExtAddr_t responderAddress;
  uint8_t data[APS_SM_KEY_SIZE];
} ApsSKKECommandPayload_t;

/*TransportKey*/
typedef struct PACK
{
  uint8_t key[APS_SM_KEY_SIZE];
  ExtAddr_t dstAddr;
  ExtAddr_t srcAddr;
} ApsTrustCenterKeyDescriptor_t;

typedef struct PACK
{
  uint8_t key[APS_SM_KEY_SIZE];
  uint8_t sequenceNumber;
  ExtAddr_t dstAddr;
  ExtAddr_t srcAddr;
} ApsNetworkKeyDescriptor_t;

typedef struct PACK
{
  uint8_t key[APS_SM_KEY_SIZE];
  ExtAddr_t partnerAddr;
  uint8_t initiatorFlag;
} ApsAppKeyDescriptor_t;

typedef struct PACK
{
  uint8_t keyType;
  union PACK
  {
    ApsTrustCenterKeyDescriptor_t   trustCenterKey;
    ApsNetworkKeyDescriptor_t       networkKey;
    ApsAppKeyDescriptor_t           appKey;
  };
} ApsTransportKeyCommandPayload_t;

typedef struct PACK
{
  ExtAddr_t deviceAddress;
  ShortAddr_t deviceShortAddress;
  uint8_t status;
} ApsUpdateDeviceCommandPayload_t;

typedef struct PACK
{
  ExtAddr_t childAddress;
} ApsRemoveDeviceCommandPayload_t;

typedef struct PACK
{
  uint8_t keyType;
  ExtAddr_t partnerAddress;
} ApsRequestKeyCommandPayload_t;

typedef struct PACK
{
  uint8_t sequenceNumber;
} ApsSwitchKeyCommandPayload_t;

typedef struct PACK
{
  uint8_t keyType;
  uint8_t keySeqNumber;
  ExtAddr_t initiator;
  ExtAddr_t responder;
  uint8_t challenge[APS_SM_KEY_SIZE];
} ApsAuthChallengeCommandPartWithKeySecNumber_t;

typedef struct PACK
{
  uint8_t keyType;
  ExtAddr_t initiator;
  ExtAddr_t responder;
  uint8_t challenge[APS_SM_KEY_SIZE];
} ApsAuthChallengeCommandPartWithoutKeySecNumber_t;

typedef enum
{
  APS_AUTH_ACTIVE_NETWORK_KEY_TYPE  = 0x00,
  APS_AUTH_LINK_KEY_TYPE            = 0x01
} ApsAuthChallengeKeyType_t;

typedef struct PACK
{
  union PACK
  {
    ApsAuthChallengeCommandPartWithKeySecNumber_t keySeq;
    ApsAuthChallengeCommandPartWithoutKeySecNumber_t noKeySeq;
  };
} ApsAuthChallengeCommandPayload_t;

typedef struct PACK
{
  uint8_t mac[APS_SM_KEY_SIZE];
  uint8_t dataType;
  uint32_t data;
} ApsAuthMacAndDataCommandPayload_t;

typedef union PACK _ApsCommandPayload_t
{
  APS_SINGLE_COMMAND_PAYLOAD;
} ApsCommandPayload_t;

typedef struct PACK _ApsCommand_t
{
  ApduCommandHeader_t header;
  ApsCommandPayload_t payload;
} ApsCommand_t;

/**
 * \brief Tunnel command frame payload. 
 *
 * See ZigBee spec. r18, 4.4.9.8, page 490, Figure 4.22.
 **/
typedef struct PACK _ApsTunnelCommandPayload_t
{
  /** The 64-bit extended address of the device that is to receive the tunnelled command. */
  ExtAddr_t  dstAddr;
  /* APS base header of the tunneled command: frame control and APS counter. */
  ApduCommandBaseHeader_t  tunneledHeader;
  /** The tunneled auxiliary frame indicate that a link key was used 
   * and shall included the extended nonce field. ZigBee spec. r18, 4.4.9.8.3, page 491.*/
  uint8_t  tunneledAuxHeader[APS_TUNNELED_AUXILIARY_HEADER_LEN];
  /* Identifier of the tunneled APS command. */
  uint8_t   commandId;
  /** The tunnelled command field shall be the APS command frame to be sent to the
   * destination. See ZigBee spec. r18, 4.4.9.8.4 and Figure 4.22. */
  ApsCommandPayload_t  tunneledCommand;
  /** Tunneled APS MIC. See ZigBee spec. r18, page 490, Figure 4.22. */
  uint8_t  mic[APS_TUNNELED_MIC_LEN];
} ApsTunnelCommandPayload_t;

typedef union PACK _ApsMultiCommandPayload_t
{
  APS_SINGLE_COMMAND_PAYLOAD;
  ApsTunnelCommandPayload_t  tunnel;
} ApsMultiCommandPayload_t;

typedef struct PACK _ApsCommandFrame_t
{
  uint8_t lowLevelHeader[NWK_NSDU_OFFSET];
  ApduCommandHeader_t header;
#if defined _SECURITY_ && defined _HIGH_SECURITY_
  ApsMultiCommandPayload_t payload;
#else  
  ApsCommandPayload_t payload;
#endif
#if (NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
  uint8_t lowLevelFooter[NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET];
#else
  uint8_t lowLevelFooter[1];
#endif
} ApsCommandFrame_t;

END_PACK

#endif /* _APSFRAMES_H_ */
