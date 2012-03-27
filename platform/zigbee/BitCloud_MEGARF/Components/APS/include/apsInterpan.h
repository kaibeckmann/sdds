/**************************************************************************//**
  \file  apsInterpan.h

  \brief INTERP-DATA interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
 ******************************************************************************/
#if !defined _INTRP_DATA_H
#define _INTRP_DATA_H
#ifdef _INTERPAN_
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <aps.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/**//**
 * \brief INTRP-DATA confirm primitive's parameters structure declaration.
 * ZigBee Smart Energy profile specification r15
 * B.3.2 The The INTRP-DATA.confirm Primitive, page 85.
 */
typedef struct _INTRP_DataConf_t
{
  /* Service fields - for internal needs. */
  struct
  {
    void  *next;
  } service;
  /** An integer handle associated with the transmitted frame */
  uint8_t  asduHandle;
  /** The status of the ASDU transmission corresponding to ASDUHandle as 
   * returned by the MAC.*/
  MAC_Status_t  status;
} INTRP_DataConf_t;


/**//**
 * \brief INTRP-DATA.request primitive's parameters structure declaration.
 * ZigBee Smart Energy profile specification r15
 * B.3.1 The INTRP-DATA.request Primitive, page 83.
 */
typedef struct _INTRP_DataReq_t
{
  struct
  {
    void *next;
  } service;
  //Primitive fields
  /*!
   * Valid srcAddrMode is always 0x03. So this field is not necessary in this 
   * structure.*/
  //APS_AddrMode_t srcAddrMode;
  /*!
  The addressing mode for the destination address used in this primitive. This 
  parameter can take one of the values from the following list: 
  0x01 = 16-bit group address
  0x02 = 16-bit NWK address, normally  the broadcast address 0xffff 
  0x03 = 64-bit extended address
  */
  APS_AddrMode_t dstAddrMode;
  /*!
  The 16-bit PAN identifier of the entity or entities to which the ASDU is 
  being  transferred or the broadcast PANId 0xffff.
  */
  PanId_t dstPANID;
  /*!The address of the entity or entities to which the ASDU is being 
  transferred.
  */
  MAC_Addr_t dstAddress;
  /*!The identifier of the profile for which this frame is intended.*/
  ProfileId_t profileId;
  /*!
  The identifier of the cluster, within the profile specified by the ProfileId 
  parameter, which defines the application semantics of the ASDU.
  */
  ClusterId_t clusterId;
  /*!The number of octets in the ASDU to be transmitted.
  */
  uint8_t asduLength;
  /*!The set of octets comprising the ASDU to be transferred.*/
  uint8_t *asdu;
  /*! An integer handle associated with the ASDU to be transmitted.*/
  uint8_t asduHandle;
  void (*INTRP_DataConf)(INTRP_DataConf_t *conf);
  INTRP_DataConf_t confirm;                       //!<  Confirm primitive as a parameter of the callback function

} INTRP_DataReq_t;

/**//**
 * \brief INTRP-DATA indication primitive's parameters structure declaration.
 * ZigBee Smart Energy profile specification r15
 * B.3.3 The INTRP-DATA.indication Primitive, page 86
 */
typedef struct _INTRP_DataInd_t
{
  struct
  {
    void *next;
  } service;
  //Primitive fields
  /*!
   * Valid srcAddrMode is always 0x03. So this field is not necessary in this 
   * structure.*/
  //APS_AddrMode_t srcAddrMode;
  /*!
  The 16-bit PAN identifier of the entity from which the ASDU is being 
  transferred
  */
  PanId_t srcPANID;
  /*! The device address of the entity from which the ASDU is being transferred
  */
  MAC_Addr_t srcAddress;
  /*!
  The addressing mode for the destination address used in this primitive. This 
  parameter can take one of the values from the following list: 
  0x01 = 16-bit group address
  0x02 = 16-bit NWK address, normally  the broadcast address 0xffff 
  0x03 = 64-bit extended address
  */
  APS_AddrMode_t dstAddrMode;
  /*!
  The 16-bit PAN identifier of the entity or entities to which the ASDU is 
  being  transferred or the broadcast PANId 0xffff.
  */
  PanId_t dstPANID;
  /*!The address of the entity or entities to which the ASDU is being 
  transferred.
  */
  MAC_Addr_t dstAddress;
  /*!The identifier of the profile for which this frame is intended.*/
  ProfileId_t profileId;
  /*!
  The identifier of the cluster, within the profile specified by the ProfileId 
  parameter, which defines the application semantics of the ASDU.
  */
  ClusterId_t clusterId;
  /*!The number of octets in the ASDU to be transmitted.
  */
  uint8_t asduLength;
  /*!The set of octets comprising the ASDU to be transferred.*/
  uint8_t *asdu;
  /*!The link quality observed during the reception of the ASDU*/
  Lqi_t lqi;
} INTRP_DataInd_t;

/**//**
 * \brief Inter-PAN frame description
 * ZigBee Smart Energy profile specification r15
 * B.4 Frame Format, page 88
 */

BEGIN_PACK
typedef struct PACK
{
  LITTLE_ENDIAN_OCTET(3, (
    uint8_t nwkFrameType   : 2,
    uint8_t protocolVersion: 4,
    uint8_t nwkReserved1   : 2))
    uint8_t nwkReserved2;
  LITTLE_ENDIAN_OCTET(6, (
    uint8_t apsFrameType              :2,
    uint8_t deliveryMode              :2,
    uint8_t ackFormat                 :1,
    uint8_t security                  :1,
    uint8_t ackRequest                :1,
    uint8_t extendedHeaderPresent     :1
  ))
  union PACK
  {
    struct PACK
    {
      ShortAddr_t groupAddr;
      ClusterId_t clusterId;
      ProfileId_t profileId;
    } groupAddressing;
    struct PACK
    {
      ClusterId_t clusterId;
      ProfileId_t profileId;
    } nonGroupAddressing;
  };
} IntrpHeader_t;
END_PACK


/******************************************************************************
                               Define(s) section
 ******************************************************************************/

/******************************************************************************
                              Prototypes section
 ******************************************************************************/


/**************************************************************************//**
  \brief Inter-PAN request handler.
  \param None
  \return None.
 ******************************************************************************/
void intrpReqProcess(void);

/**************************************************************************//**
  \brief Inter-PAN MAC confirmation handler.
  \param None
  \return None.
 ******************************************************************************/
void intrpMACDataConfProccess(void);

/**************************************************************************//**
  \brief Inter-PAN indication handler.
  \param None
  \return None.
 ******************************************************************************/
void intrpINTRPDataIndProcess(void);

/**************************************************************************//**
  \brief INTRP-DATA request primitive's prototype.

  \param[in] req - INTRP-DATA request parameters' structure pointer.
  \return None.
 ******************************************************************************/
void INTRP_DataReq(INTRP_DataReq_t *const req);

/**************************************************************************//**
  \brief INTRP-DATA indication primitive's prototype.

  \param[in] ind - INTRP-DATA indication parameters' structure pointer.
  \return None.
 ******************************************************************************/
void INTRP_DataInd(INTRP_DataInd_t *ind);

#endif //_INTERPAN_
#endif  /* _INTRP_DATA_H */
/** eof apsInterpan.h */

