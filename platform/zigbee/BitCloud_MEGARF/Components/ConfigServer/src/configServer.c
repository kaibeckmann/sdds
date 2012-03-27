/***************************************************************************//**
  \file configServer.c

  \brief Config Server implementation

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    04/07/07 A. Potashov - Created
*****************************************************************************/

#include <bcEndian.h>
#include <configServer.h>
#include <macAddr.h>
#include <macBuffers.h>
#include <macBanNode.h>
#include <pdsDataServer.h>
#include <sysDuplicateTable.h>

#ifndef _MAC2_
#include <appFramework.h>
#include <aps.h>
#include <apsDataManager.h>
#include <apsBindManager.h>
#include <apsGroupManager.h>
#include <apsSecurityManager.h>
#include <apsMemoryManager.h>
#include <dbg.h>
#include <zdo.h>
#include <nwkConfigServer.h>

#if defined(_SECURITY_)
#include <tcAuthentic.h>
#ifdef _HIGH_SECURITY_
#include <tcKeyEstablish.h>
#endif
#endif

#ifdef _ZCL_
#include <zclMemoryManager.h>
#endif // _ZCL_

#endif // _MAC2_

/*****************************************************************************
  Allocated memory
*****************************************************************************/
#ifndef _MAC2_

static Neib_t      csNeibTable[CS_NEIB_TABLE_SIZE];

static MutableNeib_t  csMutableNeibTable[CS_NEIB_TABLE_SIZE];

static ExtAddr_t    csUId = CCPU_TO_LE64(CS_UID);

static ExtPanId_t   csExtPANID = CCPU_TO_LE64(CS_EXT_PANID);

static ExtPanId_t   csNwkExtPANID = CCPU_TO_LE64(CS_NWK_EXT_PANID);

static ShortAddr_t csNwkAddr = CCPU_TO_LE16(CS_NWK_ADDR);

static ShortAddr_t csNwkParentAddr = CCPU_TO_LE16(0xFFFF);

static uint8_t     csNwkDepth = 0;

static uint32_t    csChannelMask = CS_CHANNEL_MASK;

static uint32_t    csEndDeviceSleepPeriod = CS_END_DEVICE_SLEEP_PERIOD;

#if CS_ROUTE_CACHE_SIZE > 0
static NwkRouteCacheRecord_t  csRouteCache[CS_ROUTE_CACHE_SIZE];
#endif
#if CS_NWK_BUFFERS_AMOUNT > 0
static NwkPacket_t csNwkBuffer[CS_NWK_BUFFERS_AMOUNT];
#endif
#if CS_APS_DATA_REQ_BUFFERS_AMOUNT > 0
static ApsDataBuffer_t csApsDataReqBuffer[CS_APS_DATA_REQ_BUFFERS_AMOUNT];
#endif
#if CS_APS_ACK_FRAME_BUFFERS_AMOUNT > 0
static ApsAckBuffer_t csApsAckFrameBuffer[CS_APS_ACK_FRAME_BUFFERS_AMOUNT];
#endif
static uint8_t csApsMaxFrameRetries = CS_APS_MAX_FRAME_RETRIES;
static uint32_t csIndirectPollRate = CS_INDIRECT_POLL_RATE;

#if CS_JOIN_IND_OBJ_AMOUNT > 0
static NwkJoinIndObj_t csJoinIndObjects[CS_JOIN_IND_OBJ_AMOUNT];
#endif

static MAC_PanDescriptor_t csMacPanDescriptorBuffer[CS_NEIB_TABLE_SIZE];

#if CS_DUPLICATE_REJECTION_TABLE_SIZE > 0
static SYS_DuplicateTableEntry_t csDuplicateRejectionTable[CS_DUPLICATE_REJECTION_TABLE_SIZE];
#endif

static uint8_t csMacFrameRxBuffer[CS_MAC_FRAME_RX_BUFFER_SIZE];

#if defined _GROUP_TABLE_
static NWK_GroupTableEntry_t csGroupTable[CS_GROUP_TABLE_SIZE];
#endif

static uint8_t csSoftResetReason = CS_SOFT_RESET_REASON;

//Stack profile identifier
static StackProfile_t csStackProfileId = CS_STACK_PROFILE;

//Protocol version identifier
static uint8_t csProtocolVersionId = CS_PROTOCOL_VERSION;

#if CS_ROUTE_TABLE_SIZE > 0
static NwkRoutingTableEntry_t csRoutingTable[CS_ROUTE_TABLE_SIZE];
#endif
#if CS_ROUTE_DISCOVERY_TABLE_SIZE > 0
static NwkRouteDiscoveryEntry_t csRouteDiscoveryTable[CS_ROUTE_DISCOVERY_TABLE_SIZE];
#endif
#if CS_ADDRESS_MAP_TABLE_SIZE > 0
static NwkAddressMapEntry_t csAddressMapTable[CS_ADDRESS_MAP_TABLE_SIZE];
#endif
#if CS_NWK_BTT_SIZE > 0
static SYS_DuplicateTableEntry_t csBTR[CS_NWK_BTT_SIZE];
#endif

static uint8_t csNwkMaxLinkStatusFailures = CS_NWK_MAX_LINK_STATUS_FAILURES;
static uint8_t csNwkEndDeviceMaxFailures = CS_NWK_END_DEVICE_MAX_FAILURES;

static uint8_t csNwkLogicalChannel = 0;
static PanId_t csNwkPanid = CCPU_TO_LE16(CS_NWK_PANID);

#if defined _BINDING_ && CS_APS_BINDING_TABLE_ENTRIES_AMOUNT > 0
static uint8_t apsBindingTable[CS_APS_BINDING_TABLE_SIZE];
#endif //_BINDING_

#ifdef _APS_FRAGMENTATION_
// It allocates memory for array of blocks and array of its length
  #if ((CS_APS_BLOCK_SIZE > APS_MAX_ASDU_SIZE) || (CS_APS_BLOCK_SIZE == 0))
      #undef CS_APS_BLOCK_SIZE
      #define CS_APS_BLOCK_SIZE APS_MAX_ASDU_SIZE
  #endif

  #if 0 < CS_APS_MAX_BLOCKS_AMOUNT
    static uint8_t csFragmentationMemoryPool[CS_APS_MAX_BLOCKS_AMOUNT * CS_APS_BLOCK_SIZE + CS_APS_MAX_BLOCKS_AMOUNT];
    static uint8_t csFragmentationPacketBuffer[APS_ASDU_OFFSET + CS_APS_BLOCK_SIZE + APS_AFFIX_LENGTH];
  #endif

static uint8_t csApsMaxTransmissionWindowSize = CS_APS_MAX_TRANSMISSION_WINDOW_SIZE;
#endif /* _APS_FRAGMENTATION_ */

#if defined _NWK_CONCENTRATOR_
static uint8_t csNwkConcentratorDiscoveryTime = NWK_CONCENTRATOR_DISCOVERY_TIME;
#endif

static uint8_t  csZdoJoinAttempts = CS_ZDO_JOIN_ATTEMPTS;
static uint16_t csZdoJoinInterval = CS_ZDO_JOIN_INTERVAL;

#ifdef _TC_SWAPOUT_
static uint8_t  csZdoTcKeepAliveInterval = CS_ZDO_TC_KEEP_ALIVE_INTERVAL;
#endif // _TC_SWAPOUT_

/*****************************************************************************
 The Permit duration parameter affect directly to asscociation permit in
 MAC layer.
 0xff - always on
 0x00 - always off
*****************************************************************************/
static uint8_t csPermitDuration = CS_PERMIT_DURATION;
//============================================================================

static uint32_t csMacTransactionTime = CS_MAC_TRANSACTION_TIME;

static UserDescriptor_t   csUserDescriptor;
static uint16_t   csManufacturerCode = CS_MANUFACTURER_CODE;

#if defined(_SECURITY_)
static NWK_SecurityIB_t  csNwkSecurityIb;
PROGMEM_DECLARE(static const uint32_t  csApsSecurityTimeoutPeriod) = CS_APS_SECURITY_TIMEOUT_PERIOD;
static ExtAddr_t csApsTrustCenterAddress = CCPU_TO_LE64(CS_APS_TRUST_CENTER_ADDRESS);
static uint8_t csNetworkKey[SECURITY_KEY_SIZE] = CS_NETWORK_KEY;
static ApsSecBuffer_t csApsSecurityBuffers[CS_APS_SECURITY_BUFFERS_AMOUNT];
#if CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT > 0
static TC_AuthenticObj_t csTcAuthenticProcessBuffer[CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT];
#endif
#if defined _TC_PERMISSION_TABLE_ && CS_MAX_TC_ALLOWED_DEVICES_AMOUNT > 0
  static ExtAddr_t csTcDevicePermissionTable[CS_MAX_TC_ALLOWED_DEVICES_AMOUNT];
#endif
#ifdef _HIGH_SECURITY_
static ApsKeyPairDescriptor_t csApsKeyPairDescriptors[CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT];
PROGMEM_DECLARE(static const uint8_t csLinkKey[16]) = CS_LINK_KEY;
PROGMEM_DECLARE(static const uint8_t csMasterKey[16]) = CS_MASTER_KEY;
#if CS_MAX_TC_ESTABLISH_KEY_AMOUNT > 0
static TC_KeyEstablishObj_t csTcEstablishKeyBuffer[CS_MAX_TC_ESTABLISH_KEY_AMOUNT];
#endif
#endif
#endif

#else   // _MAC2_

// variables. Memory was not allocate for CS_MAC_TRANSACTION_TIME.
static uint64_t    csUId                      = CCPU_TO_LE64(CS_UID);
// buffers
static uint8_t csMacFrameRxBuffer[CS_MAC_FRAME_RX_BUFFER_SIZE];
static uint32_t csMacTransactionTime = CS_MAC_TRANSACTION_TIME;

#endif  // _MAC2_

#ifdef _ZCL_
static uint16_t csZclAttributeReportTimerInterval = CS_ZCL_ATTRIBUTE_REPORT_TIMER_INTERVAL;
static ZclMmBufferDescriptor_t zclMmBuffers[CS_ZCL_MEMORY_BUFFERS_AMOUNT];
#ifdef _OTAU_
static ExtAddr_t csOtauDefaultServerAddress = CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS;
#endif //_OTAU_
#endif //_ZCL_

#ifdef _MAC_BAN_NODE_
static MAC_BanTableEntry_t  csBanTable[CS_BAN_TABLE_SIZE];
#endif /* _MAC_BAN_NODE_ */

/*****************************************************************************
The definitions of bit fields
*****************************************************************************/

typedef struct
{
#ifndef _MAC2_
  uint8_t       maxNeighborRouteCost : 4;
  bool          rxOnWhenIdle : 1;
  bool          dtrWakeup : 1;
  bool          nwkPredefinedPanid : 1;
  bool          nwkUniqueAddr : 1;
  bool          nwkUseMulticast : 1;
  bool          complexDescriptorAvailable  : 1;
  bool          userDescriptorAvailable : 1;
#ifdef _POWER_FAILURE_
  bool          powerFailure : 1;
#endif
#ifdef _SECURITY_
  bool          securityOn   : 1;
  uint8_t       zdoSecurityStatus : 2;
#endif // _SECURITY_
  uint8_t       channelPage : 3;
  DeviceType_t  deviceType : 2;
  int8_t        rfTxPower : 7;
  uint8_t       maxFrameTransmissionTime : CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE;
  bool          autoPoll  : 1;
#ifdef AT86RF212
  bool          lbtMode : 1;
#endif //AT86RF212
#else   // _MAC2_
  int8_t        rfTxPower : 7;
  uint8_t       maxFrameTransmissionTime : CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE;
#endif  // _MAC2_
} csBitFields_t;

/*****************************************************************************
The values of bit fields
*****************************************************************************/
csBitFields_t  csBitFields =
{
#ifndef _MAC2_
  .maxNeighborRouteCost = CS_MAX_NEIGHBOR_ROUTE_COST,
#ifdef CS_RX_ON_WHEN_IDLE
  .rxOnWhenIdle = CS_RX_ON_WHEN_IDLE,
#else
  .rxOnWhenIdle = (CS_DEVICE_TYPE == DEVICE_TYPE_END_DEVICE) ? false : true,
#endif
  .dtrWakeup = CS_DTR_WAKEUP,
  .nwkPredefinedPanid = CS_NWK_PREDEFINED_PANID,
  .nwkUniqueAddr = CS_NWK_UNIQUE_ADDR,
  .nwkUseMulticast = CS_NWK_USE_MULTICAST,
  .complexDescriptorAvailable = CS_COMPLEX_DESCRIPTOR_AVAILABLE,
  .userDescriptorAvailable = CS_USER_DESCRIPTOR_AVAILABLE,
#ifdef _POWER_FAILURE_
  .powerFailure = CS_POWER_FAILURE,
#endif
#ifdef _SECURITY_
  .securityOn = CS_SECURITY_ON,
  .zdoSecurityStatus = CS_ZDO_SECURITY_STATUS,
#endif // _SECURITY_
  .channelPage = CS_CHANNEL_PAGE,
  .deviceType = CS_DEVICE_TYPE,
  .rfTxPower = CS_RF_TX_POWER,
  .maxFrameTransmissionTime = CS_MAX_FRAME_TRANSMISSION_TIME,
  .autoPoll = CS_AUTO_POLL,
#ifdef AT86RF212
  .lbtMode = CS_LBT_MODE,
#endif //AT86RF212
#else   // _MAC2_
  .rfTxPower = CS_RF_TX_POWER,
  .maxFrameTransmissionTime = CS_MAX_FRAME_TRANSMISSION_TIME,
#endif  // _MAC2_
};

/*****************************************************************************
Read parameter value specified by parameter identifier
Parameters:
  parameterId     - parameter Id
  parameterValue  - parameter value pointer will be read to
Returns:
  None
*****************************************************************************/
void CS_ReadParameter(CS_ParameterId_t parameterId, void *parameterValue)
{
  if (parameterValue)
  {
    switch (parameterId)
    {
#ifdef _MAC_BAN_NODE_
      case CS_BAN_TABLE_SIZE_ID:
        *((MAC_BanTableSize_t *) parameterValue) = CS_BAN_TABLE_SIZE;
        break;
#endif /* _MAC_BAN_NODE_ */
#ifndef _MAC2_
      case CS_MAX_NEIGHBOR_ROUTE_COST_ID:
        *((NwkLinkCost_t *) parameterValue) = csBitFields.maxNeighborRouteCost;
        break;
      case CS_DEVICE_TYPE_ID:
        *((DeviceType_t *) parameterValue) = csBitFields.deviceType;
        break;
      case CS_NWK_ADDR_ID:
        *((ShortAddr_t *) parameterValue) = csNwkAddr;
        break;
      case CS_NWK_PARENT_ADDR_ID:
        *((ShortAddr_t *) parameterValue) = csNwkParentAddr;
        break;
      case CS_NWK_DEPTH_ID:
        *((uint8_t *) parameterValue) = csNwkDepth;
        break;
      case CS_RX_ON_WHEN_IDLE_ID:
        *((bool *) parameterValue) = csBitFields.rxOnWhenIdle;
        break;
      case CS_INDIRECT_POLL_RATE_ID:
        *((uint32_t *) parameterValue) = csIndirectPollRate;
        break;
      case CS_ROUTE_CACHE_SIZE_ID:
        *((NwkRouteCacheSize_t *) parameterValue) = CS_ROUTE_CACHE_SIZE;
        break;
      case CS_NEIB_TABLE_SIZE_ID:
        *((NwkSizeOfNeighborTable_t *) parameterValue) = CS_NEIB_TABLE_SIZE;
        break;
      case CS_MAC_PAN_DESCRIPTOR_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_NEIB_TABLE_SIZE;
        break;
      case CS_MAX_CHILDREN_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_CHILDREN_AMOUNT;
        break;
      case CS_MAX_CHILDREN_ROUTER_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_CHILDREN_ROUTER_AMOUNT;
        break;
      case CS_MAX_NETWORK_DEPTH_ID:
        *((uint8_t *) parameterValue) = CS_MAX_NETWORK_DEPTH;
        break;
      case CS_END_DEVICE_SLEEP_PERIOD_ID:
        *((uint32_t *) parameterValue) = csEndDeviceSleepPeriod;
        break;
      case CS_ADDRESS_ASSIGNMENT_METHOD_ID:
        *((uint8_t *) parameterValue) = CS_ADDRESS_ASSIGNMENT_METHOD;
        break;
      case CS_NWK_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_NWK_BUFFERS_AMOUNT;
        break;
      case CS_APS_DATA_REQ_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_DATA_REQ_BUFFERS_AMOUNT;
        break;
      case CS_JOIN_IND_OBJ_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_JOIN_IND_OBJ_AMOUNT;
        break;
      case CS_APS_ACK_FRAME_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_ACK_FRAME_BUFFERS_AMOUNT;
        break;
      case CS_PROTOCOL_VERSION_ID:
        *((uint8_t *) parameterValue) = csProtocolVersionId;
        break;
      case CS_STACK_PROFILE_ID:
        *((StackProfile_t *) parameterValue) = csStackProfileId;
        break;
      case CS_SCAN_DURATION_ID:
        *((uint8_t *) parameterValue) = CS_SCAN_DURATION;
        break;
      case CS_PERMIT_DURATION_ID:
        *((uint8_t *) parameterValue) = csPermitDuration;
        break;
      case CS_NWK_EXT_PANID_ID:
        *((ExtPanId_t *) parameterValue) = csNwkExtPANID;
        break;
      case CS_EXT_PANID_ID:
        *((ExtPanId_t *) parameterValue) = csExtPANID;
        break;
      case CS_CHANNEL_MASK_ID:
        *((uint32_t *) parameterValue) = csChannelMask;
        break;
      case CS_CHANNEL_PAGE_ID:
        *((uint8_t *) parameterValue) = csBitFields.channelPage;
        break;
#endif // _MAC2_
      case CS_UID_ID:
        //*((uint64_t *) parameterValue) = csUId;
        memcpy(parameterValue, &csUId, sizeof(ExtAddr_t));
        break;
#ifndef _MAC2_
      case CS_DUPLICATE_REJECTION_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_DUPLICATE_REJECTION_TABLE_SIZE;
        break;
#endif // _MAC2_
      case CS_MAC_FRAME_RX_BUFFER_SIZE_ID:
        *((uint16_t *) parameterValue) = CS_MAC_FRAME_RX_BUFFER_SIZE;
        break;
#ifndef _MAC2_
#if defined _GROUP_TABLE_
      case CS_GROUP_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_GROUP_TABLE_SIZE;
        break;
#endif
      case CS_APS_MAX_FRAME_RETRIES_ID:
        *((uint8_t *) parameterValue) = csApsMaxFrameRetries;
        break;
#endif // _MAC2_
      case CS_RF_TX_POWER_ID:
        *((int8_t *) parameterValue) = csBitFields.rfTxPower;
        break;
#ifndef _MAC2_
      case CS_SOFT_RESET_REASON_ID:
        *((uint8_t *) parameterValue) = csSoftResetReason;
        break;
      case CS_NWK_USE_MULTICAST_ID:
        *((bool *) parameterValue) = csBitFields.nwkUseMulticast;
        break;
      case CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID:
        *((bool *) parameterValue) = csBitFields.complexDescriptorAvailable;
        break;
      case CS_USER_DESCRIPTOR_AVAILABLE_ID:
        *((bool *) parameterValue) = csBitFields.userDescriptorAvailable;
        break;
      case CS_MANUFACTURER_CODE_ID:
        *((uint16_t *) parameterValue) = csManufacturerCode;
        break;
#ifdef _POWER_FAILURE_
      case CS_POWER_FAILURE_ID:
        *((bool *) parameterValue) = csBitFields.powerFailure;
        break;
#endif
      case CS_ROUTE_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ROUTE_TABLE_SIZE;
        break;
      case CS_ADDRESS_MAP_TABLE_SIZE_ID:
        *((NwkSizeOfAddressMap_t *) parameterValue) = CS_ADDRESS_MAP_TABLE_SIZE;
        break;
      case CS_ROUTE_DISCOVERY_TABLE_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_ROUTE_DISCOVERY_TABLE_SIZE;
        break;
      case CS_BTT_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_NWK_BTT_SIZE;
        break;
      case CS_NWK_MAX_LINK_STATUS_FAILURES_ID:
        *((uint8_t *) parameterValue) = csNwkMaxLinkStatusFailures;
        break;
      case CS_NWK_END_DEVICE_MAX_FAILURES_ID:
        *((uint8_t *) parameterValue) = csNwkEndDeviceMaxFailures;
        break;
#endif //_MAC2_
      case CS_MAC_TRANSACTION_TIME_ID:
        *((uint32_t *) parameterValue) = csMacTransactionTime;
        break;
#ifndef _MAC2_
      case CS_NWK_UNIQUE_ADDR_ID:
        *((bool *) parameterValue) = csBitFields.nwkUniqueAddr;
        break;
      case CS_DTR_WAKEUP_ID:
        *((bool *) parameterValue) = csBitFields.dtrWakeup;
        break;
      case CS_NWK_LOGICAL_CHANNEL_ID:
        *((uint8_t *) parameterValue) = csNwkLogicalChannel;
        break;
      case CS_NWK_PANID_ID:
        *((PanId_t *) parameterValue) = csNwkPanid;
        break;
      case CS_ZDP_USER_DESCRIPTOR_ID:
        memcpy(parameterValue, &csUserDescriptor, sizeof(csUserDescriptor));
        break;
      case CS_NWK_PREDEFINED_PANID_ID:
        *((bool *) parameterValue) = csBitFields.nwkPredefinedPanid;
        break;
      case CS_AUTO_POLL_ID:
        *((bool *) parameterValue) = csBitFields.autoPoll;
        break;
      case CS_ZDO_JOIN_ATTEMPTS_ID:
        *((uint8_t *) parameterValue) = csZdoJoinAttempts;
        break;
      case CS_ZDO_JOIN_INTERVAL_ID:
        *((uint32_t *) parameterValue) = csZdoJoinInterval;
        break;
#ifdef _TC_SWAPOUT_
      case CS_ZDO_TC_KEEP_ALIVE_INTERVAL_ID:
        *((uint8_t *) parameterValue) = csZdoTcKeepAliveInterval;
        break;
#endif // _TC_SWAPOUT_
#ifdef AT86RF212
      case CS_LBT_MODE_ID:
        *(bool*)parameterValue = csBitFields.lbtMode;
        break;
#endif // AT86RF212
#ifdef _BINDING_
      case CS_APS_BINDING_TABLE_ENTRIES_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_BINDING_TABLE_ENTRIES_AMOUNT;
        break;
      case CS_APS_BINDING_TABLE_ENTRY_SIZE_ID:
        *((uint8_t *) parameterValue) = CS_APS_BINDING_TABLE_ENTRY_SIZE;
        break;
#endif //_BINDING_
#ifdef _APS_FRAGMENTATION_
      case CS_APS_MAX_BLOCKS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_MAX_BLOCKS_AMOUNT;
        break;
      case CS_APS_BLOCK_SIZE_ID:
        *((uint16_t *) parameterValue) = CS_APS_BLOCK_SIZE;
        break;
      case CS_APS_MAX_TRANSMISSION_WINDOW_SIZE_ID:
        *((uint8_t *) parameterValue) = csApsMaxTransmissionWindowSize;
        break;
#endif /* _APS_FRAGMENTATION_ */
#if defined _NWK_CONCENTRATOR_
      case CS_CONCENTRATOR_DISCOVERY_TIME_ID:
        *((uint8_t *) parameterValue) = csNwkConcentratorDiscoveryTime;
        break;
#endif /* _NWK_CONCENTRATOR_ */
#endif // _MAC2_
      case CS_MAX_FRAME_TRANSMISSION_TIME_ID:
        *((uint8_t *) parameterValue) = csBitFields.maxFrameTransmissionTime;
        break;
#ifndef _MAC2_
/***********************************************************************
 Security related action's
***********************************************************************/
#ifdef _SECURITY_
    case CS_SECURITY_ON_ID:
        *(bool *)parameterValue = csBitFields.securityOn;
        break;
      case CS_APS_SECURITY_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_SECURITY_BUFFERS_AMOUNT;
        break;
      case CS_APS_SECURITY_TIMEOUT_PERIOD_ID:
        memcpy_P(parameterValue, &csApsSecurityTimeoutPeriod, sizeof(uint32_t));
        break;
      case CS_APS_TRUST_CENTER_ADDRESS_ID:
        memcpy(parameterValue, &csApsTrustCenterAddress, sizeof(ExtAddr_t));
        break;
#ifdef _SECURITY_
      case CS_ZDO_SECURITY_STATUS_ID:
        *((uint8_t *) parameterValue) = csBitFields.zdoSecurityStatus;
        break;
#endif // _SECURITY_
      case CS_SECURITY_LEVEL_ID:
        *((uint8_t *) parameterValue) = CS_SECURITY_LEVEL;
        break;
      case CS_SECURITY_ALL_FRAMES_ID:
        *((bool *) parameterValue) = CS_SECURITY_ALL_FRAMES;
        break;
      case CS_NETWORK_KEY_ID:
        memcpy(parameterValue, csNetworkKey, sizeof(csNetworkKey));
        break;
      case CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT_ID:
          *((uint8_t *) parameterValue) = CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT;
      break;
#ifdef _TC_PERMISSION_TABLE_
      case CS_MAX_TC_ALLOWED_DEVICES_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_ALLOWED_DEVICES_AMOUNT;
      break;
#endif
#ifdef _HIGH_SECURITY_
      case CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT;
        break;
      case CS_LINK_KEY_ID:
        memcpy_P(parameterValue, csLinkKey, sizeof(csLinkKey));
        break;
      case CS_MASTER_KEY_ID:
        memcpy_P(parameterValue, csMasterKey, sizeof(csMasterKey));
        break;
      case CS_MAX_TC_ESTABLISH_KEY_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_MAX_TC_ESTABLISH_KEY_AMOUNT;
      break;
#endif // _SECURITY_
#endif // _HIGH_SECURITY_
#endif // _MAC2_
#ifdef _ZCL_
      case CS_ZCL_ATTRIBUTE_REPORT_TIMER_INTERVAL_ID:
        *((uint16_t *) parameterValue) = csZclAttributeReportTimerInterval;
        break;
      case CS_ZCL_MEMORY_BUFFERS_AMOUNT_ID:
        *((uint8_t *) parameterValue) = CS_ZCL_MEMORY_BUFFERS_AMOUNT;
        break;
#ifdef _OTAU_
      case CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS_ID:
        *((ExtAddr_t *) parameterValue) = csOtauDefaultServerAddress;
        break;
#endif //_OTAU_
#endif //_ZCL_

      case CS_STACK_VERSION_ID:
        *((uint32_t *) parameterValue) = CS_STACK_VERSION;
        break;
      default:
        break;
    }
  }
}


/*****************************************************************************
Allocate memory area specified by memory identifier
Parameters:
  memoryId        - memory area Id
  memoryPtr       - pointer to pointer wich will be modified
Returns:
  None
*****************************************************************************/
void CS_GetMemory(CS_MemoryId_t memoryId, void **memoryPtr)
{
  switch (memoryId)
  {
#ifdef _MAC_BAN_NODE_
    case CS_BAN_TABLE_ID:
      *memoryPtr = csBanTable;
      break;
#endif /* _MAC_BAN_NODE_ */
#ifndef _MAC2_
    case CS_NEIB_TABLE_ID:
      *memoryPtr = csNeibTable;
      break;
#if CS_ROUTE_CACHE_SIZE > 0
    case CS_ROUTE_CACHE_ID:
      *memoryPtr = csRouteCache;
      break;
#endif
#if CS_NWK_BUFFERS_AMOUNT > 0
    case CS_NWK_BUFFERS_ID:
      *memoryPtr = csNwkBuffer;
      break;
#endif
#if CS_APS_DATA_REQ_BUFFERS_AMOUNT > 0
    case CS_APS_DATA_REQ_BUFFER_ID:
      *memoryPtr = csApsDataReqBuffer;
      break;
#endif
#if CS_APS_ACK_FRAME_BUFFERS_AMOUNT > 0
    case CS_APS_ACK_FRAME_BUFFER_ID:
      *memoryPtr = csApsAckFrameBuffer;
      break;
#endif
#if CS_JOIN_IND_OBJ_AMOUNT > 0
    case CS_JOIN_IND_OBJ_ID:
      *memoryPtr = csJoinIndObjects;
      break;
#endif
    case CS_MAC_PAN_DESCRIPTOR_BUFFER_ID:
      *memoryPtr = csMacPanDescriptorBuffer;
      break;
#if CS_DUPLICATE_REJECTION_TABLE_SIZE > 0
    case CS_DUPLICATE_REJECTION_TABLE_ID:
      *memoryPtr = csDuplicateRejectionTable;
      break;
#endif
#endif //_MAC2_
    case CS_MAC_FRAME_RX_BUFFER_ID:
      *memoryPtr = csMacFrameRxBuffer;
      break;
#ifndef _MAC2_
#if defined _GROUP_TABLE_
    case CS_GROUP_TABLE_ID:
      *memoryPtr = csGroupTable;
      break;
#endif
#if CS_ROUTE_TABLE_SIZE > 0
    case CS_ROUTE_TABLE_ID:
      *memoryPtr = csRoutingTable;
      break;
#endif
#if CS_ADDRESS_MAP_TABLE_SIZE > 0
    case CS_ADDRESS_MAP_TABLE_ID:
      *memoryPtr = csAddressMapTable;
      break;
#endif
#if CS_ROUTE_DISCOVERY_TABLE_SIZE > 0
    case CS_ROUTE_DISCOVERY_TABLE_ID:
      *memoryPtr = csRouteDiscoveryTable;
      break;
#endif
#if CS_NWK_BTT_SIZE > 0
    case CS_BTT_ID:
      *memoryPtr = csBTR;
      break;
#endif
    case CS_MUTABLE_NEIB_TABLE_ID:
       *memoryPtr = csMutableNeibTable;
      break;
   case CS_EXT_ADDR_ID:
       *memoryPtr = &csUId;
      break;
#if defined _BINDING_ && CS_APS_BINDING_TABLE_ENTRIES_AMOUNT > 0
   case CS_APS_BINDING_TABLE_ID:
     *memoryPtr = apsBindingTable;
     break;
#endif //_BINDING_

#ifdef _APS_FRAGMENTATION_
    case CS_APS_FRAGMENTATION_MEMORY_POOL_ID:
#if CS_APS_MAX_BLOCKS_AMOUNT
      *memoryPtr = csFragmentationMemoryPool;
#else
      *memoryPtr = NULL;
#endif
      break;

    case CS_APS_FRAGMENTATION_PACKET_BUFFER:
#if CS_APS_MAX_BLOCKS_AMOUNT
      *memoryPtr = csFragmentationPacketBuffer;
#else
      *memoryPtr = NULL;
#endif
      break;
#endif //_APS_FRAGMENTATION_

/***********************************************************************
  Security related action's
***********************************************************************/
#if defined(_SECURITY_)
    case CS_NWK_SECURITY_IB_ID:
      *memoryPtr = &csNwkSecurityIb;
      break;
    case CS_APS_SECURITY_BUFFERS_ID:
      *memoryPtr = csApsSecurityBuffers;
      break;
#if CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT > 0
    case CS_TC_AUTHENTIC_PROCESS_BUFFER_ID:
      *memoryPtr = csTcAuthenticProcessBuffer;
      break;
#endif
#if defined _TC_PERMISSION_TABLE_ && CS_MAX_TC_ALLOWED_DEVICES_AMOUNT > 0
    case CS_TC_PERMISSION_TABLE_ID:
      *memoryPtr = csTcDevicePermissionTable;
      break;
#endif
#ifdef _HIGH_SECURITY_
    case CS_APS_KEY_PAIR_DESCRIPTORS_ID:
      *memoryPtr = csApsKeyPairDescriptors;
      break;
#if CS_MAX_TC_ESTABLISH_KEY_AMOUNT > 0
    case CS_TC_ESTABLISH_KEY_BUFFER_ID:
      *memoryPtr = csTcEstablishKeyBuffer;
      break;
#endif
#endif
#endif
/***********************************************************************
        ZCL buffer
***********************************************************************/
#ifdef _ZCL_
    case CS_ZCL_MEMORY_BUFFERS_ID:
      *memoryPtr = zclMmBuffers;
      break;
#endif // _ZCL_

#endif //_MAC2_
    default:
      *memoryPtr = NULL;
      break;
  }
}


/*****************************************************************************
Write parameter value specified by parameter identifier and parameter value
pointer
Parameters:
  parameterId     - parameter Id
  parameterValue  - parameter value pointer will be write from
Returns:
  None
*****************************************************************************/
extern void CS_WriteParameter(CS_ParameterId_t parameterId, void *parameterValue)
{
  switch (parameterId)
  {
#ifndef _MAC2_
    case CS_MAX_NEIGHBOR_ROUTE_COST_ID:
      csBitFields.maxNeighborRouteCost = *((NwkLinkCost_t *) parameterValue);
      break;
    case CS_NWK_ADDR_ID:
      csNwkAddr = *(ShortAddr_t *) parameterValue;
      break;
    case CS_NWK_PARENT_ADDR_ID:
      csNwkParentAddr = *((ShortAddr_t *) parameterValue);
      break;
    case CS_NWK_DEPTH_ID:
      csNwkDepth = *((uint8_t *) parameterValue);
      break;
    case CS_NWK_UNIQUE_ADDR_ID:
      csBitFields.nwkUniqueAddr = *(bool *) parameterValue;
      break;
    case CS_DEVICE_TYPE_ID:
      csBitFields.deviceType = *(DeviceType_t *) parameterValue;
      break;
    case CS_APS_MAX_FRAME_RETRIES_ID:
      csApsMaxFrameRetries = *((uint8_t *) parameterValue);
      break;
#endif // _MAC2_
    case CS_UID_ID:
      csUId = *(ExtAddr_t *) parameterValue;
      break;
#ifndef _MAC2_
    case CS_EXT_PANID_ID:
      csExtPANID = *(ExtPanId_t *) parameterValue;
      break;
    case CS_NWK_EXT_PANID_ID:
      csNwkExtPANID = *(ExtPanId_t *) parameterValue;
      break;
    case CS_RX_ON_WHEN_IDLE_ID:
      csBitFields.rxOnWhenIdle = *(bool *) parameterValue;
      break;
    case CS_CHANNEL_MASK_ID:
      csChannelMask = *(uint32_t *) parameterValue;
      break;
    case CS_CHANNEL_PAGE_ID:
      csBitFields.channelPage = *(uint8_t *) parameterValue;
      break;
#endif //_MAC2_
    case CS_RF_TX_POWER_ID:
      csBitFields.rfTxPower = *(int8_t *) parameterValue;
      break;
#ifndef _MAC2_
    case CS_NWK_MAX_LINK_STATUS_FAILURES_ID:
      csNwkMaxLinkStatusFailures = *((uint8_t *) parameterValue);
      break;
    case CS_NWK_END_DEVICE_MAX_FAILURES_ID:
      csNwkEndDeviceMaxFailures = *((uint8_t *) parameterValue);
      break;
    case CS_SOFT_RESET_REASON_ID:
      csSoftResetReason = *(uint8_t *) parameterValue;
      break;
    case CS_STACK_PROFILE_ID:
      csStackProfileId = *(StackProfile_t *) parameterValue;
      break;
    case CS_PROTOCOL_VERSION_ID:
      csProtocolVersionId = *(uint8_t *) parameterValue;
      break;
    case CS_PERMIT_DURATION_ID:
      csPermitDuration = *(uint8_t *) parameterValue;
      break;
    case CS_INDIRECT_POLL_RATE_ID:
      csIndirectPollRate = *(uint32_t *) parameterValue;
      break;
    case CS_END_DEVICE_SLEEP_PERIOD_ID:
      csEndDeviceSleepPeriod = *(uint32_t *) parameterValue;
      break;
    case CS_NWK_USE_MULTICAST_ID:
      csBitFields.nwkUseMulticast = *(bool *) parameterValue;
      break;
    case CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID:
      csBitFields.complexDescriptorAvailable = *((bool *) parameterValue);
      break;
    case CS_USER_DESCRIPTOR_AVAILABLE_ID:
      csBitFields.userDescriptorAvailable = *((bool *) parameterValue);
      break;
    case CS_MANUFACTURER_CODE_ID:
      csManufacturerCode = *((uint16_t *) parameterValue);
      break;
#ifdef _POWER_FAILURE_
    case CS_POWER_FAILURE_ID:
      csBitFields.powerFailure = *((bool *) parameterValue);
      break;
#endif
    case CS_DTR_WAKEUP_ID:
      csBitFields.dtrWakeup = *(bool *) parameterValue;
      break;
    case CS_NWK_LOGICAL_CHANNEL_ID:
      csNwkLogicalChannel = *(uint8_t *) parameterValue;
      break;
    case CS_NWK_PANID_ID:
      csNwkPanid = *(PanId_t *) parameterValue;
      break;
    case CS_ZDP_USER_DESCRIPTOR_ID:
      memcpy(&csUserDescriptor, parameterValue, sizeof(csUserDescriptor));
      break;
    case CS_NWK_PREDEFINED_PANID_ID:
      csBitFields.nwkPredefinedPanid = *((bool *) parameterValue);
      break;
    case CS_AUTO_POLL_ID:
      csBitFields.autoPoll = *((bool *) parameterValue);
      break;
    case CS_ZDO_JOIN_ATTEMPTS_ID:
      csZdoJoinAttempts = *((uint8_t *) parameterValue);
      break;
    case CS_ZDO_JOIN_INTERVAL_ID:
      csZdoJoinInterval = *((uint16_t *) parameterValue);
      break;
#ifdef _TC_SWAPOUT_
    case CS_ZDO_TC_KEEP_ALIVE_INTERVAL_ID:
      csZdoTcKeepAliveInterval = *((uint8_t *) parameterValue);
      break;
#endif // _TC_SWAPOUT_
#if defined _NWK_CONCENTRATOR_
    case CS_CONCENTRATOR_DISCOVERY_TIME_ID:
      csNwkConcentratorDiscoveryTime = *((uint8_t *) parameterValue);
      break;
#endif /* _NWK_CONCENTRATOR_ */
#ifdef AT86RF212
    case CS_LBT_MODE_ID:
      csBitFields.lbtMode = *(bool*)parameterValue;
      break;
#endif //AT86RF212
#endif //_MAC2_
    case CS_MAX_FRAME_TRANSMISSION_TIME_ID:
      csBitFields.maxFrameTransmissionTime = *(uint8_t *) parameterValue;
      break;
    case CS_MAC_TRANSACTION_TIME_ID:
      csMacTransactionTime = *(uint32_t *) parameterValue;
      break;
#ifndef _MAC2_
#ifdef _SECURITY_
    case CS_SECURITY_ON_ID:
      csBitFields.securityOn = *(bool *) parameterValue;
      break;
    case CS_ZDO_SECURITY_STATUS_ID:
      csBitFields.zdoSecurityStatus = *(uint8_t *) parameterValue;
      break;
    case CS_NETWORK_KEY_ID:
      memcpy(&csNetworkKey, parameterValue, sizeof(csNetworkKey));
      break;
    case CS_APS_TRUST_CENTER_ADDRESS_ID:
      memcpy(&csApsTrustCenterAddress, parameterValue, sizeof(ExtAddr_t));
      break;
#endif
#endif //_MAC2_

#ifdef _ZCL_
    case CS_ZCL_ATTRIBUTE_REPORT_TIMER_INTERVAL_ID:
      csZclAttributeReportTimerInterval = *((uint16_t *) parameterValue);
      break;
#ifdef _OTAU_
    case CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS_ID:
      csOtauDefaultServerAddress = *((ExtAddr_t *) parameterValue);
      break;
#endif //_OTAU_
#endif //_ZCL_

#ifdef _APS_FRAGMENTATION_
    case CS_APS_MAX_TRANSMISSION_WINDOW_SIZE_ID:
      csApsMaxTransmissionWindowSize = *((uint8_t *) parameterValue);
      break;
#endif /* _APS_FRAGMENTATION_ */

    default:
      break;
  }
}



/*****************************************************************************
Init the Config Server
Parameters:
  None
Returns:
  None
*****************************************************************************/
void CS_Init(void)
{
  PDS_Init();
}

/*****************************************************************************
Set PDS default
Parameters:
  None
Returns:
  None
*****************************************************************************/
void CS_PdsDefaultValue(void)
{
#ifndef _MAC2_
  csNwkExtPANID = CCPU_TO_LE64(CS_NWK_EXT_PANID);
  csExtPANID = CCPU_TO_LE64(CS_EXT_PANID);
  csNwkAddr = CCPU_TO_LE16(CS_NWK_ADDR);
  csChannelMask = CS_CHANNEL_MASK;
  csBitFields.channelPage = CS_CHANNEL_PAGE;
#endif //_MAC2_
  csUId = CCPU_TO_LE64(CS_UID);
#ifndef _MAC2_
  csBitFields.maxNeighborRouteCost = CS_MAX_NEIGHBOR_ROUTE_COST;
  csBitFields.deviceType = CS_DEVICE_TYPE;
  #ifdef CS_RX_ON_WHEN_IDLE
    csBitFields.rxOnWhenIdle = CS_RX_ON_WHEN_IDLE;
  #else
    csBitFields.rxOnWhenIdle = (CS_DEVICE_TYPE == DEVICE_TYPE_END_DEVICE) ? false : true;
  #endif
#endif //_MAC2_
  csBitFields.rfTxPower = CS_RF_TX_POWER;
#ifndef _MAC2_
  csSoftResetReason = CS_SOFT_RESET_REASON;
  csBitFields.nwkUniqueAddr = CS_NWK_UNIQUE_ADDR;
  csBitFields.dtrWakeup = CS_DTR_WAKEUP;
  csBitFields.complexDescriptorAvailable = CS_COMPLEX_DESCRIPTOR_AVAILABLE;
  csBitFields.userDescriptorAvailable = CS_USER_DESCRIPTOR_AVAILABLE;
  csBitFields.autoPoll = CS_AUTO_POLL;
#ifdef AT86RF212
  csBitFields.lbtMode = CS_LBT_MODE;
#endif //AT86RF212

  csNwkLogicalChannel = 0;
  csNwkPanid = CCPU_TO_LE16(CS_NWK_PANID);
  csManufacturerCode = CS_MANUFACTURER_CODE;
  csNwkMaxLinkStatusFailures = CS_NWK_MAX_LINK_STATUS_FAILURES;
  csNwkEndDeviceMaxFailures = CS_NWK_END_DEVICE_MAX_FAILURES;

#if defined(_SECURITY_)
  csBitFields.securityOn = CS_SECURITY_ON;
  csBitFields.zdoSecurityStatus = CS_ZDO_SECURITY_STATUS;
  {const uint8_t csDefaultNetworkKey[16] = CS_NETWORK_KEY;
   uint8_t i = 0;
   for (; i < 16; i++)
     csNetworkKey[i] = csDefaultNetworkKey[i];
  }
#endif // _SECURITY_
#endif //_MAC2_
}

