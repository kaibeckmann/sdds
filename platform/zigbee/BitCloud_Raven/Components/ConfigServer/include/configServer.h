/*************************************************************************//**
  \file configServer.h

  \brief The header file describes the public ConfigServer interface

  The file describes the public interface and parameters of Config Server.
  It is intended for reading/writing the stack parameters.
  To keep the default values unchanged, the user is recommended to redefine needed values
  in the application's Makefiles or via the environment variables.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    04/07/07 A. Potashov - Created
*****************************************************************************/

#ifndef _CONFIGSERVER_H
#define _CONFIGSERVER_H

#include <types.h>
#include <stackVersion.h>

/*****************************************************************************
  Defines
*****************************************************************************/
#ifdef CS_APS_DATA_REQ_BUFFER_SIZE
 #error CS_APS_DATA_REQ_BUFFER_SIZE definition is renamed to CS_APS_DATA_REQ_BUFFERS_AMOUNT - please, use the new name.
#endif
#ifdef CS_APS_ACK_FRAME_BUFFER_SIZE
 #error CS_APS_ACK_FRAME_BUFFER_SIZE definition is renamed to CS_APS_ACK_FRAME_BUFFERS_AMOUNT - please, use the new name.
#endif

#ifdef _MAC2_

//BOOST mode is enabled automatically only for 11, 10, 9, 8, 7, 6 dBm(s) all other power valuses do not use BOOST mode.
//! \brief RF transmit power.
#ifndef CS_RF_TX_POWER
/* It was TX_PWR_3_0DBM. */
#define CS_RF_TX_POWER                        0
#endif

//! \brief MAC transaction persistence time. For more details see MAC PIB attributes Table 86 in IEEE 802.15.4-2006
// (by default in MAC = 7680L)
#ifndef CS_MAC_TRANSACTION_TIME
#define CS_MAC_TRANSACTION_TIME               7680L
#endif

//! \brief Determines the device UID.
/*! Should be unique for each device in a network.
If set to 0, the stack will use the value from the UID chip (if present).*/
#ifndef CS_UID
#define CS_UID                                0x0000000000000000LL
#endif

//! \brief Duration in ms of maximum length frame transferring.
#ifndef CS_MAX_FRAME_TRANSMISSION_TIME
#define CS_MAX_FRAME_TRANSMISSION_TIME         5
#endif

// \cond internal
#define CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE  3
// \endcond

#if CS_MAX_FRAME_TRANSMISSION_TIME >= (1 << CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE)
#error CS_MAX_FRAME_TRANSMISSION_TIME shall be less (1 << CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE)
#endif

//! \brief Size of MAC RX buffer intended to receive frames. Must be greater than 130.
#ifndef CS_MAC_FRAME_RX_BUFFER_SIZE
#define CS_MAC_FRAME_RX_BUFFER_SIZE            131
#endif

#else  //_MAC2_

// \cond internal
//! \brief Protocol version identifier. Could not be changed by user.
#ifndef CS_PROTOCOL_VERSION
#define CS_PROTOCOL_VERSION                   0x02
#endif
//! \brief Stack profile identifier (Zigbee PRO profile is equal to 2). Could not be changed by user.
#ifndef CS_STACK_PROFILE
#define CS_STACK_PROFILE                      0x02
#endif
// \endcond
//! \brief Type of device
/*! May be chosen from: \n
0 = ::DEVICE_TYPE_COORDINATOR \n
1 = ::DEVICE_TYPE_ROUTER \n
2 = ::DEVICE_TYPE_END_DEVICE*/
#ifndef CS_DEVICE_TYPE
#define CS_DEVICE_TYPE                        DEVICE_TYPE_ROUTER
#endif

//! \brief The size of neighbor table
/*! Upper-bounds the maximum possible amount of child devices.
Determines the maximum possible amount of beacons to be saved.
The parameter should exceed ::CS_MAX_CHILDREN_AMOUNT at least by 1*/
#ifndef CS_NEIB_TABLE_SIZE
  #define CS_NEIB_TABLE_SIZE                  7
#elif CS_NEIB_TABLE_SIZE == 0
  #undef  CS_NEIB_TABLE_SIZE
  #define CS_NEIB_TABLE_SIZE                  1
  #warning  CS_NEIB_TABLE_SIZE was set to 1
#endif

//! \brief Maximum number of children that a given device (coordinator or router) may have
#ifndef CS_MAX_CHILDREN_AMOUNT
#define CS_MAX_CHILDREN_AMOUNT                6
#endif
//! \brief Maximum number of routers among the children of one device
/*! The maximum number of end devices is equal to ::CS_MAX_CHILDREN_AMOUNT - ::CS_MAX_CHILDREN_ROUTER_AMOUNT */
#ifndef CS_MAX_CHILDREN_ROUTER_AMOUNT
#define CS_MAX_CHILDREN_ROUTER_AMOUNT         2
#endif
//! \brief Maximum depth of a network
/*! The maximum number of hops that a packet may travel is twice that large.*/
#ifndef CS_MAX_NETWORK_DEPTH
#define CS_MAX_NETWORK_DEPTH                  5
#endif
// \cond internal
//! \brief The method of address assignment.
/*!  In the current version is limited to 2.*/
#ifndef CS_ADDRESS_ASSIGNMENT_METHOD
#define CS_ADDRESS_ASSIGNMENT_METHOD          2
#endif
// \endcond

#ifdef AT86RF212
/* Channel number range
  Page 0 (BPSK modulation is used and supported IEEE 802.15.4 2003/2006 )
    channel  0: 868 MHz      | 20 Kbit/sec
    channels 1 - 10: 915 MHz | 40 Kbit/sec
  Page 2 (O-QPSK modulation is used and supported IEEE 802.15.4 2006)
    channel  0: 868 MHz      | 100 Kbit/sec
    channels 1 - 10: 915 MHz | 250 Kbit/sec

  BOOST mode is enabled automatically only for 11, 10, 9, 8, 7, 6 dBm. All other power values do not use BOOST mode.
*/
//! \brief Channel mask to be used by the application.
/*! Determines the channel(s) on which the device may operate*/
  #ifndef CS_CHANNEL_MASK
    #define CS_CHANNEL_MASK                       0x00000002L
  #endif
//! \brief Number of channel page to be used.
/*! 0 means BPSK modulation, 2 means O-QPSK */
  #ifndef CS_CHANNEL_PAGE
    #define CS_CHANNEL_PAGE                       0
  #endif
#else // AT86RF230/230B/231
//! \brief Channel mask to be used by the application.
/*! Determines the channel(s) on which the device may operate*/
  #ifndef CS_CHANNEL_MASK
    #define CS_CHANNEL_MASK                       0x00010000L
  #endif
//! \brief Number of channel page to be used. Ignored in the case of AT86RF230/230B/231 RF chip.
  #ifndef CS_CHANNEL_PAGE
    #define CS_CHANNEL_PAGE                       0
  #endif
#endif

//! \brief Determines the device UID.
/*! Should be unique for each device in a network.
If set to 0, the stack will use the value from the UID chip (if present).*/
#ifndef CS_UID
#define CS_UID                                0x0000000000000000LL
#endif
//! \brief Extended PAN ID of the network to which the device should join.
/*! For a coordinator, this is an extended PAN ID of a network to be started.*/
#ifndef CS_EXT_PANID
#define CS_EXT_PANID                          CS_UID
#endif
//! \brief Extended PAN ID used in commissioning feature.
/*! Determines the extended PAN ID of a network where a device may start without having to join.*/
#ifndef CS_NWK_EXT_PANID
#define CS_NWK_EXT_PANID                      0LL
#endif
//! \brief Determines whether or not the static addressing mode will be used.
/*! If set to true, the CS_NWK_ADDR will be used as the device's short address\n
Otherwise, the stochastic addressing mode will be employed.*/
#ifndef CS_NWK_UNIQUE_ADDR
#define CS_NWK_UNIQUE_ADDR                          false
#endif
//! \brief Device's short address if ::CS_NWK_UNIQUE_ADDR=true, otherwise neglected.
#ifndef CS_NWK_ADDR
#define CS_NWK_ADDR                       0xFFFF
#endif
//! \brief End Device sleep period.
/*! It is used by a parent for tracking that an End Device lives.
For an End Device, this parameter sets its own sleep period.
For router, it should be maximum over all sleep periods in a network*/
#ifndef CS_END_DEVICE_SLEEP_PERIOD
#define CS_END_DEVICE_SLEEP_PERIOD            10000L
#endif

//! \brief Encryption time of maximum-size packet in ms. Decryption time is equal to encryption time.
#ifndef CS_ENCRYPTION_TIME
#if defined(_SECURITY_)
  #ifdef _MAC_HW_AES_
    #define CS_ENCRYPTION_TIME 18     // HW encryption
  #else
    #define CS_ENCRYPTION_TIME 119    // SW encryption
  #endif
#else
  #define CS_ENCRYPTION_TIME 0ul
#endif
#endif

//! \brief Duration of internal processing of the maximum-size packet (without encryption)
#define CS_PACKET_PROCESS_INSIDE 7

//! \brief Time of polling own parent by end device.
#ifndef CS_INDIRECT_POLL_RATE
#define CS_INDIRECT_POLL_RATE                 1000
#endif
//BOOST mode is enabled automatically only for 11, 10, 9, 8, 7, 6 dBm(s) all other power valuses do not use BOOST mode.
#ifndef CS_RF_TX_POWER
/* It was TX_PWR_3_0DBM. */
#define CS_RF_TX_POWER                        0
#endif
#ifndef CS_SCAN_DURATION
#define CS_SCAN_DURATION                      0x05
#endif
/*! \brief The Permit duration parameter directly affect the asscociation permit on
 MAC layer. 0xff means "always on", 0x00 means "always off" */
#ifndef CS_PERMIT_DURATION
#define CS_PERMIT_DURATION                    0xff
#endif
#ifndef CS_SOFT_RESET_REASON
#define CS_SOFT_RESET_REASON                  0
#endif
//! \brief Determines the value of nwkUseMulticast attribute in NIB.
/*! Enables or disables the multicast transmission mode on NWK layer. Recomended to be set to true.*/
#ifndef CS_NWK_USE_MULTICAST
#define CS_NWK_USE_MULTICAST                  true
#endif

//! \brief Specifies whether a complex descriptor is available on this device.
#ifndef CS_COMPLEX_DESCRIPTOR_AVAILABLE
#define CS_COMPLEX_DESCRIPTOR_AVAILABLE       false
#endif

/*! \brief Specifies whether a user descriptor is available on this device. */
#ifndef CS_USER_DESCRIPTOR_AVAILABLE
#define CS_USER_DESCRIPTOR_AVAILABLE          true
#endif

/*! \brief Version of stack. */
#ifndef CS_STACK_VERSION
#define CS_STACK_VERSION                      CS_STACK_VERSION_VALUE
#endif

//! \brief Enabales or disables the power failure feature.
#ifdef _POWER_FAILURE_
#ifndef CS_POWER_FAILURE
#define CS_POWER_FAILURE                      false
#endif
#endif
// \cond
// by default in MAC = 7680L
#ifndef CS_MAC_TRANSACTION_TIME
#define CS_MAC_TRANSACTION_TIME               ((uint32_t)CS_END_DEVICE_SLEEP_PERIOD + ((uint32_t)CS_INDIRECT_POLL_RATE * 3ul))
#endif
// \endcond
//! \brief Size of the APS Duplicate Rejection Table. According to ZigBee standard, should be not less than 1.
#ifndef CS_DUPLICATE_REJECTION_TABLE_SIZE
#define CS_DUPLICATE_REJECTION_TABLE_SIZE     10
#endif

//! \brief Maximum amount of records in the NWK Route Table.
#if defined _ROUTER_ || defined _COORDINATOR_
  #if !defined CS_ROUTE_TABLE_SIZE
    #define CS_ROUTE_TABLE_SIZE               4
  #endif
  #if CS_ROUTE_TABLE_SIZE == 0
    #undef  CS_ROUTE_TABLE_SIZE
    #define CS_ROUTE_TABLE_SIZE               1
    #warning CS_ROUTE_TABLE_SIZE was set to 1
  #endif
#else // _ENDDEVICE_
  #undef CS_ROUTE_TABLE_SIZE
  #define CS_ROUTE_TABLE_SIZE                 0
#endif // _ROUTER_ or _COORDINATOR_

//! \brief Maximum amount of records in the NWK Address Map Table.
#ifndef CS_ADDRESS_MAP_TABLE_SIZE
#define CS_ADDRESS_MAP_TABLE_SIZE             5
#endif
#if CS_ADDRESS_MAP_TABLE_SIZE == 0
  #undef  CS_ADDRESS_MAP_TABLE_SIZE
  #define CS_ADDRESS_MAP_TABLE_SIZE           1
  #warning CS_ADDRESS_MAP_TABLE_SIZE was set to 1
#endif

//! \brief Maximum amount of records in the NWK Route Discovery Table.
#if defined _ROUTER_ || defined _COORDINATOR_
  #if !defined CS_ROUTE_DISCOVERY_TABLE_SIZE
    #define CS_ROUTE_DISCOVERY_TABLE_SIZE     3
  #endif
  #if CS_ROUTE_DISCOVERY_TABLE_SIZE == 0
    #undef  CS_ROUTE_DISCOVERY_TABLE_SIZE
    #define CS_ROUTE_DISCOVERY_TABLE_SIZE     1
    #warning CS_ROUTE_DISCOVERY_TABLE_SIZE was set to 1
  #endif
#else // _ENDDEVICE_
  #undef CS_ROUTE_DISCOVERY_TABLE_SIZE
  #define CS_ROUTE_DISCOVERY_TABLE_SIZE       0
#endif // _ROUTER_ or _COORDINATOR_

#if !defined CS_NWK_BUFFERS_AMOUNT
  #define CS_NWK_BUFFERS_AMOUNT         4
#endif // CS_NWK_BUFFERS_AMOUNT

#if !defined CS_NWK_BTT_SIZE
  #define CS_NWK_BTT_SIZE                     8
#endif

#if defined CS_GROUP_TABLE_SIZE
  #if CS_GROUP_TABLE_SIZE == 0
    #undef CS_GROUP_TABLE_SIZE
    #define CS_GROUP_TABLE_SIZE               1
    #warning CS_GROUP_TABLE_SIZE was set to 1
  #endif
#else
  #define CS_GROUP_TABLE_SIZE                 1
#endif

//! \brief Number of buffers to execute (in parallel) data requests on APS layer.
#ifndef CS_APS_DATA_REQ_BUFFERS_AMOUNT
  #ifdef _SECURITY_
    #define CS_APS_DATA_REQ_BUFFERS_AMOUNT       3
  #else // !_SECURITY_
    #define CS_APS_DATA_REQ_BUFFERS_AMOUNT       2
  #endif // _SECURITY_
#endif

//! \brief Number of buffers to send APS acks. Shall be not greater than CS_APS_DATA_REQ_BUFFERS_AMOUNT.
//  To send APS ACK both types of buffers are used (.._DATA_REQ_.. and .._ACK_FRAME_..)
#ifndef CS_APS_ACK_FRAME_BUFFERS_AMOUNT
  #define CS_APS_ACK_FRAME_BUFFERS_AMOUNT        2
#endif

//! \brief The maximum number of retries allowed after a transmission failure
#ifndef CS_APS_MAX_FRAME_RETRIES
  #define CS_APS_MAX_FRAME_RETRIES     3
#elif CS_APS_MAX_FRAME_RETRIES > 5
  #undef  CS_APS_MAX_FRAME_RETRIES
  #define CS_APS_MAX_FRAME_RETRIES     5
  #warning CS_APS_MAX_FRAME_RETRIES was set to 5
#endif

//! \brief Size of MAC RX buffer intended to receive frames. Must be greater than 130.
#ifndef CS_MAC_FRAME_RX_BUFFER_SIZE
#define CS_MAC_FRAME_RX_BUFFER_SIZE            131
#endif

#ifndef CS_DTR_WAKEUP
#define CS_DTR_WAKEUP                         false
#endif

#ifndef CS_MAX_FRAME_TRANSMISSION_TIME
#define CS_MAX_FRAME_TRANSMISSION_TIME         5
#endif

#define CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE  3

#if CS_MAX_FRAME_TRANSMISSION_TIME >= (1 << CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE)
#error CS_MAX_FRAME_TRANSMISSION_TIME shall be less (1 << CS_FRAME_TRANSMISSION_TIME_FIELD_SIZE)
#endif

/* The router is deleted from the table of neighbours after
 *  CS_NWK_MAX_LINK_STATUS_FAILURES skipped link status commands */
#ifndef CS_NWK_MAX_LINK_STATUS_FAILURES
#define CS_NWK_MAX_LINK_STATUS_FAILURES   3
#endif

/*  Number not received data request before being notified about child loss or
 *  being able to identify that neighbor has left is too long.
 */
#ifndef CS_NWK_END_DEVICE_MAX_FAILURES
#define CS_NWK_END_DEVICE_MAX_FAILURES    3
#endif

#ifndef CS_LBT_MODE
#define CS_LBT_MODE false
#endif


#ifdef _BINDING_
#ifndef CS_APS_BINDING_TABLE_ENTRIES_AMOUNT
#define CS_APS_BINDING_TABLE_ENTRIES_AMOUNT     1
#endif

#ifndef CS_APS_BINDING_TABLE_ENTRY_SIZE
#define CS_APS_BINDING_TABLE_ENTRY_SIZE         2
#endif

#define CS_APS_BINDING_TABLE_SIZE ((sizeof(ApsBindingTableDestinationEntry_t) * CS_APS_BINDING_TABLE_ENTRY_SIZE + sizeof(ApsBindingTableSourceEntry_t)) * CS_APS_BINDING_TABLE_ENTRIES_AMOUNT)
#endif //_BINDING_

#ifdef _APS_FRAGMENTATION_
// \brief The maximum blocks amount the asdu could be splitted into.
//        It correlates with formula CS_APS_MAX_BLOCKS_AMOUNT * APS_MAX_ASDU_SIZE
//        that defines the maximum asdu size when fragmentation feature is used.
#ifndef CS_APS_MAX_BLOCKS_AMOUNT
#define CS_APS_MAX_BLOCKS_AMOUNT 0
#endif

// \brief The block size that is used for fragments in fragmented transmission.
#ifndef CS_APS_BLOCK_SIZE
#define CS_APS_BLOCK_SIZE 0
#endif

// \brief Maximum transmission window size (in blocks)
#ifndef CS_APS_MAX_TRANSMISSION_WINDOW_SIZE
  #ifdef _ZHP_SECURITY_
    #define CS_APS_MAX_TRANSMISSION_WINDOW_SIZE        1
  #else
    #define CS_APS_MAX_TRANSMISSION_WINDOW_SIZE        3
  #endif
#endif

#endif /* _APS_FRAGMENTATION_  */
// \endcond

/*****************************************************************************
  Security related defines
*****************************************************************************/
// \cond internal
#ifdef _SECURITY_
//Turn on/off security
#ifndef CS_SECURITY_ON
#define CS_SECURITY_ON  true
#endif
//Amount of Aps Security Manager buffers
/*Should be no less than 2*/
#ifndef CS_APS_SECURITY_BUFFERS_AMOUNT
#define CS_APS_SECURITY_BUFFERS_AMOUNT      1
#endif
#ifndef CS_APS_SECURITY_TIMEOUT_PERIOD
#define CS_APS_SECURITY_TIMEOUT_PERIOD        (2 * 1000 * 10)
#endif
// \endcond
//! \brief Default address of the Trust Center.
#ifndef CS_APS_TRUST_CENTER_ADDRESS
#define CS_APS_TRUST_CENTER_ADDRESS           0xAAAAAAAAAAAAAAAALL
#endif
//! \brief ZDO security status.
/*! May be chosen among: \n
0 - preconfigured network key \n
3 - not preconfigured. */
#ifndef CS_ZDO_SECURITY_STATUS
#define CS_ZDO_SECURITY_STATUS                PRECONFIGURED_NETWORK_KEY
#endif
//! \brief Default value of the network key.
#ifndef CS_NETWORK_KEY
#define CS_NETWORK_KEY                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
// \cond internal
// Default security level. SHould not be changed without stack recompiling!!!
// MAX_ASDU_LENGTH depends on this parameter through the footer length.
#ifndef CS_SECURITY_LEVEL
#define CS_SECURITY_LEVEL             0x05
#endif
// Default nwkSecureAllFrames attribute value in NIB.
#ifndef CS_SECURITY_ALL_FRAMES
#define CS_SECURITY_ALL_FRAMES        true
#endif
#ifndef CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT
  #define CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT     1
#endif
// \endcond
#ifdef _TC_PERMISSION_TABLE_
//! \brief For a Trust Center, maximum amount of records in the Permission Table.
  #ifndef CS_MAX_TC_ALLOWED_DEVICES_AMOUNT
    #define CS_MAX_TC_ALLOWED_DEVICES_AMOUNT    5
  #endif
#endif
// \cond internal
#ifdef _HIGH_SECURITY_
//Maximum amount of Key-Pair Descriptors
#ifndef CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT
#define CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT  3
#endif
#ifndef CS_MASTER_KEY
#define CS_MASTER_KEY                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
#ifndef CS_LINK_KEY
#define CS_LINK_KEY                   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
#ifndef CS_MAX_TC_ESTABLISH_KEY_AMOUNT
#define CS_MAX_TC_ESTABLISH_KEY_AMOUNT      1
#endif
#endif
// \endcond

#endif

//! \brief Number of network scans ZDO is performing before it returns fail.
#ifndef CS_ZDO_JOIN_ATTEMPTS
#define CS_ZDO_JOIN_ATTEMPTS                4
#endif

//! \brief Interval between network scan attempts.
#ifndef CS_ZDO_JOIN_INTERVAL
#define CS_ZDO_JOIN_INTERVAL                1000
#endif

//! \brief TC Keep-Alive polling interval, should be in the range 5-20 minutes.
#ifndef CS_ZDO_TC_KEEP_ALIVE_INTERVAL
#define CS_ZDO_TC_KEEP_ALIVE_INTERVAL       20
#endif

// \cond internal

#ifndef CS_NWK_PREDEFINED_PANID
#define CS_NWK_PREDEFINED_PANID false
#endif

#ifndef CS_NWK_PANID
#define CS_NWK_PANID    0x1234
#endif

/*! 16-bit manufacturer code allocated by the ZigBee Alliance. */
#ifndef CS_MANUFACTURER_CODE
#define CS_MANUFACTURER_CODE  0x100c
#endif

/*! Auto polling by end device */
#ifndef CS_AUTO_POLL
#define CS_AUTO_POLL    true
#endif

#if defined _ROUTER_ || defined _COORDINATOR_
  #if !defined CS_JOIN_IND_OBJ_AMOUNT
    #define CS_JOIN_IND_OBJ_AMOUNT          (CS_NWK_BUFFERS_AMOUNT >> 1)
  #endif
#else // _ENDDEVICE_
  #undef   CS_JOIN_IND_OBJ_AMOUNT
  #define  CS_JOIN_IND_OBJ_AMOUNT           0
#endif // _ROUTER_ or _COORDINATOR_

/* Maximum number of records in the route cache */
#if defined _NWK_ROUTE_CACHE_ && (defined _ROUTER_ || defined _COORDINATOR_)
  #if !defined CS_ROUTE_CACHE_SIZE
    #define CS_ROUTE_CACHE_SIZE             4
  #endif /* CS_ROUTE_CACHE_SIZE */
  #if CS_ROUTE_CACHE_SIZE == 0
    #undef  CS_ROUTE_CACHE_SIZE
    #define CS_ROUTE_CACHE_SIZE     1
    #warning CS_ROUTE_CACHE_SIZE was set to 1
  #endif
#else /* no route cache */
  #undef  CS_ROUTE_CACHE_SIZE
  #define CS_ROUTE_CACHE_SIZE               0
#endif

/** The time in seconds between concentrator route discoveries.
 * ZigBee spec r18, Table 3.44, page 348. */
#if !defined NWK_CONCENTRATOR_DISCOVERY_TIME
  #define NWK_CONCENTRATOR_DISCOVERY_TIME  20U /* sec. */
#endif

// \endcond
#endif  //_MAC2_

#ifdef _ZCL_
#ifndef CS_ZCL_ATTRIBUTE_REPORT_TIMER_INTERVAL
  #define CS_ZCL_ATTRIBUTE_REPORT_TIMER_INTERVAL 4000
#endif

#ifndef CS_ZCL_MEMORY_BUFFERS_AMOUNT
  #define CS_ZCL_MEMORY_BUFFERS_AMOUNT           5
#endif

#ifdef _OTAU_
  /** Default values of ZCL OTAU Cluster attributes */
  #define CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS          0xFFFFFFFFFFFFFFFFull
#endif //_OTAU_
#endif //_ZCL_

#ifndef CS_BAN_TABLE_SIZE
  #define CS_BAN_TABLE_SIZE  1
#endif /* _MAC_BAN_NODE_ */

/** Route to neighbor directly only if the incoming cost is less than given threshold.
 * 0 - ignore information in the neighbor table. Valid range 1..8. */
#ifndef CS_MAX_NEIGHBOR_ROUTE_COST
  #define CS_MAX_NEIGHBOR_ROUTE_COST       8U
#endif

/*!
\brief IDs of the parameters in Config Server
*/
typedef enum
{
  CS_MAX_NEIGHBOR_ROUTE_COST_ID,
  CS_UID_ID,                // eeprom
  CS_MAC_FRAME_RX_BUFFER_SIZE_ID,
  CS_RF_TX_POWER_ID,                // eeprom
  CS_MAC_TRANSACTION_TIME_ID,
  CS_MAX_FRAME_TRANSMISSION_TIME_ID,
  CS_LBT_MODE_ID,
#ifdef _MAC_BAN_NODE_
  CS_BAN_TABLE_SIZE_ID,
#endif /* _MAC_BAN_NODE_ */
#ifndef _MAC2_
  CS_ROUTE_CACHE_SIZE_ID,
  CS_NEIB_TABLE_SIZE_ID,
  CS_MAC_PAN_DESCRIPTOR_AMOUNT_ID,
  CS_MAX_CHILDREN_AMOUNT_ID,
  CS_MAX_CHILDREN_ROUTER_AMOUNT_ID,
  CS_MAX_NETWORK_DEPTH_ID,
  CS_ADDRESS_ASSIGNMENT_METHOD_ID,
  CS_NWK_BUFFERS_AMOUNT_ID,
  CS_APS_DATA_REQ_BUFFERS_AMOUNT_ID,
  CS_JOIN_IND_OBJ_AMOUNT_ID,
  CS_APS_ACK_FRAME_BUFFERS_AMOUNT_ID,
  CS_PROTOCOL_VERSION_ID,
  CS_STACK_PROFILE_ID,
  CS_SCAN_DURATION_ID,
  CS_PERMIT_DURATION_ID,
  CS_NWK_EXT_PANID_ID,      // eeprom
  CS_EXT_PANID_ID,          // eeprom
  CS_NWK_ADDR_ID,           // eeprom
  CS_NWK_PARENT_ADDR_ID,    // eeprom
  CS_NWK_DEPTH_ID,          // eeprom
  CS_NWK_UNIQUE_ADDR_ID,    // bool // eeprom
  CS_CHANNEL_MASK_ID,       // eeprom
  CS_CHANNEL_PAGE_ID,       // eeprom
  CS_INDIRECT_POLL_RATE_ID,
  CS_DEVICE_TYPE_ID,        // eeprom
  CS_DUPLICATE_REJECTION_TABLE_SIZE_ID,
  CS_GROUP_TABLE_SIZE_ID,
  CS_APS_MAX_FRAME_RETRIES_ID,
  CS_END_DEVICE_SLEEP_PERIOD_ID,
  // Whether the stack is to enable its receiver during idle periods
  CS_RX_ON_WHEN_IDLE_ID,    // eeprom
  CS_SOFT_RESET_REASON_ID,  // eeprom
  CS_NWK_USE_MULTICAST_ID,
  CS_COMPLEX_DESCRIPTOR_AVAILABLE_ID,
  CS_USER_DESCRIPTOR_AVAILABLE_ID,
  CS_ROUTE_TABLE_SIZE_ID,
  CS_ADDRESS_MAP_TABLE_SIZE_ID,
  CS_ROUTE_DISCOVERY_TABLE_SIZE_ID,
  CS_BTT_SIZE_ID,
  CS_NWK_MAX_LINK_STATUS_FAILURES_ID,
  CS_NWK_END_DEVICE_MAX_FAILURES_ID,
  CS_DTR_WAKEUP_ID,                 // eeprom
  CS_NWK_LOGICAL_CHANNEL_ID,        // eeprom
  CS_NWK_PANID_ID,                  // eeprom
  CS_ZDP_USER_DESCRIPTOR_ID,
  CS_NWK_PREDEFINED_PANID_ID,
  CS_MANUFACTURER_CODE_ID,
  CS_AUTO_POLL_ID,
  CS_ZDO_JOIN_ATTEMPTS_ID,
  CS_ZDO_JOIN_INTERVAL_ID,
#ifdef _TC_SWAPOUT_
  CS_ZDO_TC_KEEP_ALIVE_INTERVAL_ID,
#endif // _TC_SWAPOUT_
#ifdef _BINDING_
  CS_APS_BINDING_TABLE_ENTRIES_AMOUNT_ID,
  CS_APS_BINDING_TABLE_ENTRY_SIZE_ID,
#endif //_BINDING_
#ifdef _POWER_FAILURE_
  CS_POWER_FAILURE_ID,
#endif //_POWER_FAILURE_
#ifdef _APS_FRAGMENTATION_
  CS_APS_MAX_BLOCKS_AMOUNT_ID,
  CS_APS_BLOCK_SIZE_ID,
  CS_APS_MAX_TRANSMISSION_WINDOW_SIZE_ID,
#endif //_APS_FRAGMENTATION_
#ifdef _NWK_CONCENTRATOR_
  CS_CONCENTRATOR_DISCOVERY_TIME_ID,
#endif // _NWK_CONCENTRATOR_
/***************************************************************************
    Security related ID's
***************************************************************************/
#ifdef _SECURITY_
  CS_SECURITY_ON_ID,
  CS_NETWORK_KEY_ID,                    // eeprom
  CS_SECURITY_LEVEL_ID,
  CS_SECURITY_ALL_FRAMES_ID,
  CS_APS_SECURITY_BUFFERS_AMOUNT_ID,
  CS_APS_SECURITY_TIMEOUT_PERIOD_ID,
  CS_APS_TRUST_CENTER_ADDRESS_ID,
  CS_ZDO_SECURITY_STATUS_ID,            // eeprom
  CS_MAX_TC_AUTHENTIC_PROCESS_AMOUNT_ID,
#ifdef _TC_PERMISSION_TABLE_
  CS_MAX_TC_ALLOWED_DEVICES_AMOUNT_ID,
#endif //_TC_PERMISSION_TABLE_
#ifdef _HIGH_SECURITY_
  CS_APS_KEY_PAIR_DESCRIPTORS_AMOUNT_ID,
  CS_LINK_KEY_ID,                       // eeprom
  CS_MASTER_KEY_ID,                     // eeprom
  CS_MAX_TC_ESTABLISH_KEY_AMOUNT_ID,
#endif //_HIGH_SECURITY_
#endif //_SECURITY_
#endif // _MAC2_
#ifdef _ZCL_
  CS_ZCL_ATTRIBUTE_REPORT_TIMER_INTERVAL_ID,
  CS_ZCL_MEMORY_BUFFERS_AMOUNT_ID,
#ifdef _OTAU_
  CS_ZCL_OTAU_DEFAULT_UPGRADE_SERVER_IEEE_ADDRESS_ID,
#endif //_OTAU_
#endif //_ZCL_

  CS_STACK_VERSION_ID,
} CS_ParameterId_t;

// \cond internal
/*!
\brief IDs of the memory area in Config Server
*/
typedef enum
{
  CS_MAC_FRAME_RX_BUFFER_ID,
#ifdef _MAC_BAN_NODE_
  CS_BAN_TABLE_ID,
#endif /* _MAC_BAN_NODE_ */
#ifndef _MAC2_
  CS_ROUTE_CACHE_ID,
  CS_NEIB_TABLE_ID,                   // eeprom
  CS_NWK_BUFFERS_ID,
  CS_APS_DATA_REQ_BUFFER_ID,
  CS_APS_ACK_FRAME_BUFFER_ID,
  CS_JOIN_IND_OBJ_ID,
  CS_MAC_PAN_DESCRIPTOR_BUFFER_ID,
  CS_DUPLICATE_REJECTION_TABLE_ID,
  CS_GROUP_TABLE_ID,               // eeprom
  CS_ROUTE_TABLE_ID,               // eeprom
  CS_ADDRESS_MAP_TABLE_ID,         // eeprom
  CS_ROUTE_DISCOVERY_TABLE_ID,
  CS_BTT_ID,
  CS_MUTABLE_NEIB_TABLE_ID,
  CS_EXT_ADDR_ID,
#ifdef _BINDING_
  CS_APS_BINDING_TABLE_ID,
#endif //_BINDING_
#ifdef _APS_FRAGMENTATION_
  CS_APS_FRAGMENTATION_MEMORY_POOL_ID,
  CS_APS_FRAGMENTATION_PACKET_BUFFER,
#endif //_APS_FRAGMENTATION_
  /***********************************************************************************
  Security related ID's
  *************************************************************************************/
#ifdef _SECURITY_
  CS_NWK_SECURITY_IB_ID,             // eeprom
  CS_APS_SECURITY_BUFFERS_ID,
  CS_TC_AUTHENTIC_PROCESS_BUFFER_ID,
#ifdef _TC_PERMISSION_TABLE_
  CS_TC_PERMISSION_TABLE_ID,
#endif //_TC_PERMISSION_TABLE_
#ifdef _HIGH_SECURITY_
  CS_APS_KEY_PAIR_DESCRIPTORS_ID,      // eeprom
  CS_TC_ESTABLISH_KEY_BUFFER_ID,
#endif //_HIGH_SECURITY_
#endif //_SECURITY_
/***********************************************************************************
  ZCL buffer's ID's
*************************************************************************************/
#ifdef _ZCL_
  CS_ZCL_MEMORY_BUFFERS_ID,
#endif
#endif // _MAC2_
} CS_MemoryId_t;

// \endcond
/************************************************************************************//*!
\brief Reads a parameter value specified by parameter identifier from Config Server

\param[in] parameterId - ID of the parameter being read
\param[out] parameterValue - Value of the parameter being read
*****************************************************************************/
extern void CS_ReadParameter(CS_ParameterId_t parameterId, void *parameterValue);

/***********************************************************************************//*!
\brief Writes a parameter value specified by parameter identifier to Config Server

If the parameter is in persistense data server it also is saved there.

\param[in] parameterId - ID of the parameter being written
\param[in] parameterValue - Value of the parameter being written
**************************************************************************************/
extern void CS_WriteParameter(CS_ParameterId_t parameterId, void *parameterValue);

// \cond internal
/***********************************************************************************//*!
\brief Inits the Config Server

Config server gets values from defines and reads from persistence data server
***************************************************************************************/
extern void CS_Init(void);

/***********************************************************************************//*!
\brief Gets allocated memory specified by memory identifier

  \param[in] memoryId - memory area Id
  \param[out] memoryPtr - pointer to the memory
***************************************************************************************/
extern void CS_GetMemory(CS_MemoryId_t memoryId, void **memoryPtr);

/**************************************************************************//*!
\brief Set persist default value
*****************************************************************************/
extern void CS_PdsDefaultValue(void);
// \endcond

#endif  //#ifndef _CONFIGSERVER_H

