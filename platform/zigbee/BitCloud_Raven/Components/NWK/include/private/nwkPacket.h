/**************************************************************************//**
  \file  nwkPacket.h

  \brief Interface of the network packet manager.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2009-07-06 M. Gekk - Created.
   Last change:
    $Id: nwkPacket.h 12570 2010-09-24 20:25:34Z mgekk $
 ******************************************************************************/
#if !defined _NWK_PACKET_H
#define  _NWK_PACKET_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwkConfig.h>
#include <queue.h>
#include <mac.h>
#include <nwkCommon.h>
#include <nwkRx.h>
#include <nwkTx.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Type of network packet. */
typedef enum _NwkPacketType_t
{
  NWK_UNKNOWN_PACKET = 0x0,
  /** Command packet from NWK component. */
  NWK_OUTPUT_COMMAND_PACKET = 0x1,
  /** Command packet from MAC-layer. */
  NWK_INPUT_COMMAND_PACKET = 0x2,
  /** Data packet from MAC-layer. */
  NWK_INPUT_DATA_PACKET = 0x3,
  /** Transit packet from MAC-layer. */
  NWK_TRANSIT_PACKET = 0x4,
  /** Loopback transmission from APS-layer. */
  NWK_LOOPBACK_PACKET = 0x5,
  NWK_BUFFER_TYPE_LAST
}  NwkPacketType_t;

/** Network packet type. */
typedef struct _NwkPacket_t
{
  /** Network packet type. */
  NwkPacketType_t  type;
#if defined _SECURITY_
  NwkLength_t  macHeader[MAC_MAX_DATA_FRAME_HEADER_LENGTH + NWK_SECURITY_HEADER_SIZE];
#else
  NwkLength_t  macHeader[MAC_MAX_DATA_FRAME_HEADER_LENGTH];
#endif /* _SECURITY_ */
  uint8_t  macPayload[MAC_MAX_MSDU_SIZE];
  union
  {
    NwkInputPacket_t  in;
    NwkOutputPacket_t  out;
  } pkt;
}  NwkPacket_t;

/** Internal variables of the network packet manager. */
typedef struct _NwkPacketManager_t
{
  /** Array of network packets. */
  NwkPacket_t  *pkt;
  /** Total amount of network packets. */
  uint8_t  amount;
  /** Queue of command requests. */
  QueueDescriptor_t  commandQueue;
}  NwkPacketManager_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Allocate a free memory space for an input packet with type.

  \param[in] type - type of packet.
  \param[in] length - needed packet length.
  \return Pointer to input packet or NULL.
 ******************************************************************************/
NWK_PRIVATE NwkInputPacket_t*  nwkAllocInputPacket(const NwkPacketType_t type, 
  NwkLength_t length);

/**************************************************************************//**
  \brief Free an input packet.

  \param[in] inPkt - pointer to an input packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkFreeInputPacket(NwkInputPacket_t *const inPkt);

/**************************************************************************//**
  \brief Allocate a free memory space for an output.

  \param[in] type - type of output packet.
  \return Pointer to output packet or NULL.
 ******************************************************************************/
NWK_PRIVATE NwkOutputPacket_t* nwkAllocOutputPacket(const NwkPacketType_t type);

/**************************************************************************//**
  \brief Free an output packet.

  \param[in] outPkt - pointer to an output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkFreeOutputPacket(NwkOutputPacket_t *const outPkt);

#if defined NWK_ROUTING_CAPACITY
/**************************************************************************//**
  \brief To transform an input packet to the output packet.

  \param[in] inPkt - pointer to an input packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE
NwkOutputPacket_t* nwkTransformInToOutPacket(NwkInputPacket_t *inPkt);
#endif /* NWK_ROUTING_CAPACITY */

/**************************************************************************//**
  \brief Reset the network packet manager.
 ******************************************************************************/
NWK_PRIVATE void nwkResetPacketManager(void);

#endif /* _NWK_PACKET_H */
/** eof nwkPacket.h */

