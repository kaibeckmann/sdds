/**************************************************************************//**
  \file nwkConfig.h

  \brief Constant definition header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2007-06-20 V. Panov - Created.
    2008-09-29 M. Gekk  - Values of constants for a network from 60
                        nodes are increased.
   Last change:
    $Id: nwkConfig.h 12570 2010-09-24 20:25:34Z mgekk $
******************************************************************************/
#if !defined  _NWK_CONFIG_H
#define  _NWK_CONFIG_H

/******************************************************************************
                             Definitions section
 ******************************************************************************/
/** A Boolean flag indicating whether the device is capable of becoming
 * the ZigBee coordinator. ZigBee spec r17, page 338, table 3.43.
 * */
#if defined _COORDINATOR_
  #define NWKC_COORDINATOR_CAPABLE              true
#else
  #define NWKC_COORDINATOR_CAPABLE              false
#endif /* _COORDINATOR_ */

/** Define for coordinator address */
#define NWKC_COORD_ADDR                         0x0000U

/** North America */
/* #define NWK_NO_WIFI_CHANNELS_MASK               0x610800 */
/** Europe */
#define NWK_NO_WIFI_CHANNELS_MASK               0x618000U

#define NWK_FAVOURITE_CHANNELS_MASK             (NWK_NO_WIFI_CHANNELS_MASK)

#define NWKC_PROTOCOL_ID                        0U

#define NWKC_INITIAL_LINK_STATUS_PERIOD         15000UL /* msec*/

#define NWK_MAX_CHANNEL                         26

#define NWK_MAX_LINK_STATUS_FAILURES            3U
#define NWK_END_DEVICE_MAX_FAILURES             3U

/* #define NWK_PJ_TIMER_SUPPORT */
/* #define NWK_PJ_SUPERSEDE_ALL_PREVIOUS_REQUESTS */

#define NWK_MAX_ED_LEVEL      0xCCU /* 255 * 0.8 */

/** Support network realignment */
/* #define NWK_COORD_REALIGNMENT */

#if defined _NWK_NONSTANDARD_BEACON_FILTER_
  /** Filter by extended pan id */
  #define  NWK_BEACON_FILTER_EXTENDED_PANID
  /** If predefined short pan id then discard beacons with other pan id. */
  #define  NWK_BEACON_FILTER_PREDEFINED_PANID
  /** Beacons with the end device capacity bit equal zero will discard. */
  #define  NWK_BEACON_FILTER_END_DEVICE_CAPACITY
  /** Beacons with the router capacity bit equal zero will discard. */
  #define  NWK_BEACON_FILTER_ROUTER_CAPACITY
#endif /* NWK_NONSTANDARD_BEACON_FILTER */

/** Update the neighbor table only if our network address is presented in
 * the received link status command. */
/* #define NWK_LINK_STATUS_ONLY_IN_LIST */

/** Duration of searching other networks on same channel.
 * It is ~(2^NWK_REPORT_SCAN_DURATION)*960*16 (usec) - for 2.4MHz */
#define  NWK_SEARCH_NETWORKS_DURATION  8U /* ~4sec - 2.4MHz */

#define  NWK_SELECT_RANDOM_PARENT
#define  NWK_DELTA_LQI  (255/10)

#if defined _NWK_ROUTE_CACHE_
  #define NWKC_NO_ROUTE_CACHE false
#else
  #define NWKC_NO_ROUTE_CACHE  true
#endif /* _NWK_ROUTE_CACHE_ */

/** Maximum number of the many-to-one route requests after that the
 * route record command must be transmitted if no source route packet has
 * been received. */
#define  NWK_MAX_NO_SOURCE_ROUTE_PERIODS  3U

#define NWK_LIFE_TIME_OF_RX_ON_END_DEVICE  (60U * 2048UL) /* msec */

#if defined _COORDINATOR_ || defined _ROUTER_
  #define NWK_ROUTING_CAPACITY
#endif /* _COORDINATOR_ or _ROUTER_ */

/** The maximum time duration in milliseconds allowed for the parent and
 * all child devices to retransmit a broadcast message. */
#define  NWK_PASSIVE_ACK_TIMEOUT  500U

/** The maximum broadcast jitter time measured in milliseconds.*/
#define  NWKC_MAX_BROADCAST_JITTER  0x40U

/** Maximum data packet retransmission. The maximum number of retries allowed
 * after a broadcast transmission failure.*/
#define  NWK_MAX_BROADCAST_RETRIES  3U

/** Maximum value of a link cost metric. */
#define  NWK_MAX_LINK_COST  7U

/** Time duration in milliseconds until a route discovery expires.
 * ZigBee spec r18, Table 3.43, page 342. */
#define  NWKC_ROUTE_DISCOVERY_TIME  0x2710U

#define NWK_ALWAYS_REJECT_OWN_BROADCAST

#if !defined _NWK_ROUTING_OPTIMIZATION_
#define _NWK_ROUTING_OPTIMIZATION_ 0
#endif

#endif /* _NWK_CONFIG_H */
/** eof nwkConfig.h */

