/*************************************************************************//** 
  \file apsMemoryManager.h

  \brief The header file describes APS memory manager primitive.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal

*****************************************************************************/ 

#ifndef APSMEMORYMANAGER_H_
#define APSMEMORYMANAGER_H_

/******************************************************************************
                   Includes section
******************************************************************************/
#include <queue.h>
#include <aps.h>
#include <nwk.h>
#include <appTimer.h>
#include <apsBindManager.h>
#include <apsFrames.h>
#include <sspSkke.h>
#include <sspSfp.h>
#include <sspAuthentic.h>
#ifdef _INTERPAN_
#include <apsInterpan.h>
#endif //_INTERPAN_

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  APS_DM_DATA_BUFFER_TYPE,
  APS_DM_ACK_DATA_BUFFER_TYPE,
  APS_SM_FREE_BUFFER_TYPE,
  APS_SM_EKREQ_SKKE1_COMMAND_BUFFER_TYPE,
  APS_SM_EKREQ_SKKE3_COMMAND_BUFFER_TYPE,
  APS_SM_EKREQ_SSP_SKKE_BUFFER_TYPE,
  APS_SM_EKRESP_SSP_SKKE_BUFFER_TYPE,
  APS_SM_EKRESP_SKKE2_COMMAND_BUFFER_TYPE,
  APS_SM_EKRESP_SKKE4_COMMAND_BUFFER_TYPE,
  APS_SM_EKRO_SKKE_COMMAND_BUFFER_TYPE,
  APS_SM_AUR_SSP_AUTH_BUFFER_TYPE,
  APS_SM_AUR_CHALLENGE_COMMAND_BUFFER_TYPE,
  APS_SM_AUR_MAC_DATA_COMMAND_TYPE,
  APS_SM_AUI_SSP_AUTH_BUFFER_TYPE,
  APS_SM_AUI_CHALLENGE_COMMAND_BUFFER_TYPE,
  APS_SM_AUI_MAC_COMMAND_BUFFER_TYPE,
  APS_SM_SSPD_BUFFER_TYPE,
  APS_SM_UDR_COMMAND_BUFFER_TYPE,             //UpdateDevice command
  APS_SM_RDR_COMMAND_BUFFER_TYPE,             //RemoveDevice command
  APS_SM_RKR_COMMAND_BUFFER_TYPE,             //RequestKey command
  APS_SM_SKR_COMMAND_BUFFER_TYPE,             //RequestKey command
  APS_SM_TKR_COMMAND_BUFFER_TYPE,             //TransportKey command
  APS_SM_TKI_COMMAND_BUFFER_TYPE,
  APS_SM_COMMAND_IND_BUFFER_TYPE,
  APS_TUNNEL_COMMAND_BUFFER_TYPE
} ApsBufferType_t;

typedef enum {
  APS_DEFAULT_STATE,
  APS_NLDE_DATA_CONF_WAIT_STATE,
  APS_ACK_WAIT_STATE,
  APS_ACK_RECEIVED_STATE,
  APS_RETRANSMISSION_STATE,
  APS_TIMEOUT_STATE,
} ApsDataDescriptorState_t ;

typedef enum
{
  APS_NLDE_DATA_REQ_BUFFER_TYPE,
  APS_NLDE_DATA_REQ_WITH_ACK_BUFFER_TYPE,
  APS_NLDE_DATA_REQ_ACK_BUFFER_TYPE,
  APS_NLDE_DATA_REQ_BLOCK_BUFFER_TYPE,
#ifdef _INTERPAN_
  APS_INTRP_DATA_REQ,
  APS_INTRP_DATA_IND,
#endif //_INTERPAN_
} ApsNldeDataReqType_t;

typedef struct
{
#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
  uint8_t headerLength;
  QueueElement_t queueElement;
  APS_Status_t securityStatus;
  uint8_t keyPairDescriptorId;
#endif // _HIGH_SECURITY_
#endif //_SECURITY_

  uint8_t busy:1;
  ApsNldeDataReqType_t entryType:7;
  ApsDataDescriptorState_t state:4;
  //if request with ack requested data frame then it is a retries counter
  uint8_t retriesCounter:4;

  NWK_DataReq_t nwkDataReq; //NLDE-DATA.request primitive

#ifdef _BINDING_
  ApsBindingDescriptor_t bindDescriptor;
#endif
} ApsDataDescriptor_t;

typedef struct
{
  APS_DataReq_t *link; // request pointer
  ApsBufferType_t type;
  uint32_t timeout;
  union {
    ApsDataDescriptor_t dataDescriptor;
#ifdef _INTERPAN_
    union
    {
      INTRP_DataInd_t intrpDataInd;
      MAC_DataReq_t macDataReq;
    };
#endif //_INTERPAN_
  };
} ApsDataBuffer_t ;

#ifdef _SECURITY_
typedef struct _ApsCommandDescriptor_t
{
  QueueElement_t      queueElement;
  uint8_t             *decryptKey;
  uint8_t             apduLength;
  ShortAddr_t         shortAddr;
  ExtAddr_t           extAddr;
  uint8_t             extendedNonce;
  NWK_DataReq_t       nwkDataReq;
  ApsCommandFrame_t   commandFrame;
} ApsCommandDescriptor_t;

#ifdef _HIGH_SECURITY_
typedef struct
{
  uint8_t state;
  ShortAddr_t shortAddr;
  ExtAddr_t extAddr;
  ApsKeyPairDescriptor_t *keyPairDescriptor;
  void *transaction;
  uint32_t timeout;
  //APS_EstablishKeyReq_t req;
  SSP_CalculateSkkeParamsReq_t skkeReq;
} ApsSmSkkeDescriptor_t;

typedef struct
{
  uint8_t state;
  ShortAddr_t shortAddr;
  ExtAddr_t extAddr;
  uint8_t keySeqNumber;
  uint32_t initiatorFrameCounter;
  uint32_t responderFrameCounter;
  NWK_SecMaterialDescriptor_t *keyDescriptor;
  APS_AuthenticateReq_t *transaction;
  uint32_t timeout;
  SSP_CalculateAuthenticParamsReq_t authReq;
} ApsSmAuthDescriptor_t;
#endif //#ifdef _HIGH_SECURITY_


typedef struct
{
  void *link; // request pointer
  ApsBufferType_t type;
  uint32_t timeout;
  union
  {
    ApsCommandDescriptor_t commandDescriptor;
#ifdef _HIGH_SECURITY_
    ApsSmSkkeDescriptor_t skkeDescriptor;
    ApsSmAuthDescriptor_t authDescriptor;
#endif // ifdef _HIGH_SECURITY_
  };
} ApsSecBuffer_t;
#endif // ifdef _SECURITY_

/*
  APS Acknowledge buffer declaration
*/
typedef struct
{
  // Current buffer status.
  struct
  {
    uint8_t busy :1;
    /* Determines type of encryption to be used for ack. Three variants are possible: 
       UNSECURED, SECURED_NWK_KEY and SECURED_LINK_KEY.
       APS_UNSECURED_STATUS=0xaf, APS_SECURED_NWK_KEY_STATUS=0xac and
       APS_SECURED_LINK_KEY_STATUS=0xab defines are used as allowed values of this field.
       To compress this values to 2 bits APS_COMPRESS_SECURITY_STATUS() macros is used.
    */
    uint8_t securityStatus :2;
    uint8_t reserved :5;
  };
  NWK_DataInd_t *dataIndLink; // link to relative NWK_DataInd entity

  BEGIN_PACK
  struct PACK
  {
    uint8_t lowLevelHeader[NWK_NSDU_OFFSET];
#ifdef _HIGH_SECURITY_
    uint8_t apsSecHeader[APS_AUXILIARY_HEADER_LENGTH];
#endif /*_HIGH_SECURITY_*/
    union  PACK
    {
      ApduAcknowledgementFrame_t dataAck; //Acknowledgement frame for data
      ApduCommandAcknowledgementFrame_t commandAck; //Acknowledgement frame for command
    } frame;
#ifdef _HIGH_SECURITY_
    uint8_t apsSecFooter[APS_MAX_DATA_FRAME_FOOTER_LENGTH];
#endif /*_HIGH_SECURITY_*/
#if (NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
      uint8_t lowLevelFooter[NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET];
#else // #if !(NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
  #ifndef __GNUC__
        uint8_t lowLevelFooter[1];
  #else // IAR
        uint8_t lowLevelFooter[0];
  #endif // IAR
#endif // #if !(NWK_AFFIX_LENGTH - NWK_NSDU_OFFSET)
  };
  END_PACK
} ApsAckBuffer_t;

typedef struct
{
  uint8_t buffersAmount;
  ApsAckBuffer_t *buffers;
} ApsAckBuffersPool_t;

typedef struct
{
  uint8_t buffersAmount;
  uint8_t maxAckCounter;
  uint8_t maxReqCounter;
  uint8_t ackCounter;
  uint8_t reqCounter;
  ApsDataBuffer_t *buffers;
} ApsDataReqBuffersPool_t;

#ifdef _SECURITY_
typedef struct
{
  uint8_t buffersAmount;
  uint8_t busyAmount;
  ApsSecBuffer_t *buffers;
} ApsSmBuffersPool_t;
#endif // ifdef _SECURITY_

#ifdef _APS_FRAGMENTATION_
typedef enum
{
  APS_PERMIT,     // - permitted
  APS_REJECT,     // - must be rejected
  APS_INDICATE    // - must be indicated
} ApsFragmentAction_t;

typedef struct
{
  uint8_t state;
  uint8_t *buffers;
  uint8_t *bufferLengths;
  uint8_t maxBlocksAmount;
  uint16_t blockSize;
  uint32_t timeout;
  uint8_t blocksAmount;
  uint8_t currentWindowStartBlockNumber;
  uint8_t ackBitfield;
  uint16_t srcAddress;
  uint8_t dstEndpoint;
  uint16_t clusterId;
  uint16_t profileId;
  uint8_t srcEndpoint;
  uint8_t apsCounter;
  ApsDataBuffer_t apsBuffer;
  ApsAckBuffer_t apsAckBuffer;
  APS_Status_t securityStatus;
} ApsFragmRxDescr_t;

typedef struct
{
  uint8_t blockNumber;
  uint8_t ackBlockNumber; // block number that expect ack, also it is first block number in the window
  uint8_t blocksToTransmit; // block in window requires to  transmit. 1 required transmission
  uint8_t blocksCount;
  uint8_t apsCounter;
  uint8_t retryCounter;
  HAL_AppTimer_t sendTimer; // timer that send frame per apsInterframeDelay
  ApsDataBuffer_t *block; // memory for block
  uint8_t *buffer;
} ApsFragmTxDescr_t;
#endif // _APS_FRAGMENTATION_

/*
 * APS sublayer memory structure.
 */
typedef struct
{
  ApsDataReqBuffersPool_t dataReqBuffersPool; // Buffers to execute APS Data requests
  ApsAckBuffersPool_t ackBuffersPool; // Buffers to generate APS acknowledgements
#ifdef _SECURITY_
  ApsSmBuffersPool_t apsSmBuffersPool; // Buffers to execute security requests
#endif // ifdef _SECURITY_
#ifdef _APS_FRAGMENTATION_
  ApsFragmRxDescr_t apsFragmRxDescr;
  ApsFragmTxDescr_t apsFragmTxDescr;
#endif // _APS_FRAGMENTATION_
} ApsMem_t;


/******************************************************************************
                   Extern variables section
******************************************************************************/
extern ApsMem_t apsMem;

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*****************************************************************************
  \brief Make a reset of APS Memory Manager

  \param fullReset - reset all internal variables of APS-layer or not.
  \retur none
*****************************************************************************/
void apsResetMemoryManager(void);

#ifdef _SECURITY_
/***************************************************************************//**
  \brief APS Security Manager Buffer get function

  \param bufferType - type of buffer (ApsSecurityBufferType_t should be used)
  \return valid buffer pointer if free buffer exist,
          NULL - in other case
*******************************************************************************/
ApsSecBuffer_t *apsGetSecBuffer(uint8_t bufferType);

/***************************************************************************//**
  \brief APS Security Manager Buffer free function

  \param buffer - buffer pointer
  \return None
*******************************************************************************/
void apsFreeSecBuffer(ApsSecBuffer_t *buffer);

/*****************************************************************************
  \brief Finds buffer of a given type in the whole security buffers space if
   parameter "buffer" is NULL. Otherwise finds next buffer of a 
   given type after "buffer".
    
  \param buffer - specifies memory (buffer) to start buffer search process from 
   (if null - search is started from the first buffer).
  \return found buffer pointer if search is succeed, NULL otherwise.
*****************************************************************************/
ApsSecBuffer_t *apsFindSecBuffer(ApsSecBuffer_t *buffer, uint8_t bufferType);

/*****************************************************************************
  \brief Gives pointer to APS Security Manager buffers.

  \param none
  \retur pointer to Security Manager Buffers.
*****************************************************************************/
INLINE ApsSmBuffersPool_t *apsGetsSecBuffersMem(void)
{
  return &apsMem.apsSmBuffersPool;
}
#endif // _SECURITY_

/***************************************************************************//**
  \brief Allocates memory buffer for NLDE-DATA.request primitive specified by
  parameter primitiveType.

  \param primitiveType - type of buffer which will be allocated
    APS_NLDE_DATA_REQ_BUFFER_TYPE - NLDE-DATA.request without frame
    APS_NLDE_DATA_REQ_WITH_ACK_BUFFER_TYPE - NLDE-DATA.request with ack
      required flag in APDU
    APS_NLDE_DATA_REQ_ACK_BUFFER_TYPE - NLDE-DATA.request with ack frame
  \return nonNULL buffer pointer if memory was allocated successfully
          NULL - no free buffers available.
*******************************************************************************/
ApsDataBuffer_t *apsGetBuffer(uint8_t primitiveType);

/***************************************************************************//**
  \brief Deallocate memory buffer

  \param buffer - pointer to buffer to be freed.
  \return None
*******************************************************************************/
void apsFreeBuffer(void *buffer);

/***************************************************************************//**
  \brief Check memory availability for NLDE-DATA.request primitive to generate
  APS acknowledge.

  \param  None
  \return true - memory is available
          false - in other case
*******************************************************************************/
bool apsIsBufferAvailableForAck(void);

/******************************************************************************
                   Inline functions section
******************************************************************************/
/*****************************************************************************
  \brief Gives pointer to APS layer memory pool.

  \param none
  \retur pointer to APS memory pool.
*****************************************************************************/
INLINE ApsDataReqBuffersPool_t *apsGetDataReqBuffersMem(void)
{
  return &apsMem.dataReqBuffersPool;
}

/*****************************************************************************
  \brief Gives pointer to APS layer acknowledgements memory pool.

  \param none
  \retur pointer to APS acknowledgements memory pool.
*****************************************************************************/
INLINE ApsAckBuffersPool_t *apsGetAckBuffersMem(void)
{
  return &apsMem.ackBuffersPool;
}

#ifdef _APS_FRAGMENTATION_
/*****************************************************************************
  \brief Gives pointer to APS layer fragmentation feature memory (Rx).

  \param none
  \retur pointer to fragmentation feature memory (Rx).
*****************************************************************************/
INLINE ApsFragmRxDescr_t *apsGetFragmRxDescrMem(void)
{
  return &apsMem.apsFragmRxDescr;
}

/*****************************************************************************
  \brief Gives pointer to APS layer fragmentation feature memory (Tx).

  \param none
  \retur pointer to fragmentation feature memory (Tx).
*****************************************************************************/
INLINE ApsFragmTxDescr_t *apsGetFragmTxDescrMem(void)
{
  return &apsMem.apsFragmTxDescr;
}

/*****************************************************************************
  \brief Resets structure which controls fragmented data receiption procedure.

  \param none
  \retur none
*****************************************************************************/
INLINE void apsResetFragmRxDescr(void)
{
  ApsFragmRxDescr_t *apsFragmRxDescr = apsGetFragmRxDescrMem();

  apsFragmRxDescr->ackBitfield = 0;
  apsFragmRxDescr->apsCounter = 0;
  apsFragmRxDescr->blocksAmount = 0;
  apsFragmRxDescr->clusterId = 0;
  apsFragmRxDescr->currentWindowStartBlockNumber = 0;
  apsFragmRxDescr->dstEndpoint = 0;
  apsFragmRxDescr->profileId = 0;
  apsFragmRxDescr->srcAddress = 0;
  apsFragmRxDescr->srcEndpoint = 0;
  apsFragmRxDescr->state = 0;
  apsFragmRxDescr->timeout = 0;

  memset(&apsFragmRxDescr->apsBuffer, 0, sizeof(apsFragmRxDescr->apsBuffer));
  memset(&apsFragmRxDescr->apsAckBuffer, 0, sizeof(apsFragmRxDescr->apsAckBuffer));
  memset(apsFragmRxDescr->buffers, 0,
    apsFragmRxDescr->maxBlocksAmount * apsFragmRxDescr->blockSize + apsFragmRxDescr->maxBlocksAmount);

  apsFragmRxDescr->apsBuffer.dataDescriptor.nwkDataReq.nsdu = (uint8_t *)&apsFragmRxDescr->apsAckBuffer.frame;
}

#endif // ifdef _APS_FRAGMENTATION_
#endif /*APSMEMORYMANAGER_H_*/

//eof apsMemoryManager.h
