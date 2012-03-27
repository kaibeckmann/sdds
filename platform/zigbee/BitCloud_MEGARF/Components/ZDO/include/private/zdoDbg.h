/************************************************************************//**
  \file zdoDbg.h

  \brief ZDO assert codes

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    27.07.09 A. Taradov - Refactoring
    29.10.09 A. Taradov - Refactoring
******************************************************************************/

#ifndef _ZDODBG_H
#define _ZDODBG_H

#include <dbg.h>

typedef enum _ZdoDbgCode_t
{
  ZDO_ASSERT_MESSAGE                      = 0x5000,
  ZDO_NULL_CONFIRM_MESSAGE                = 0x5001,
  ZDO_UNKNOWN_DEVICE_TYPE_MESSAGE         = 0x5002,
  ZDO_UNKNOWN_EVENT_MESSAGE               = 0x5003,
  ZDO_UNKNOWN_STATE_MESSAGE               = 0x5004,
  ZDO_UNEXPECTED_FAIL_CONFIRM_MESSAGE     = 0x5005,
  ZDO_UNKNOWN_NETWORK_START_TYPE_MESSAGE  = 0x5006,
  ZDO_STACK_RESET_FAIL_MESSAGE            = 0x5007,
  ZDO_UNKNOWN_ZDP_CLUSTER_MESSAGE         = 0x5008,
  ZDO_ILLEGAL_ADDRESS_MODE_MESSAGE        = 0x5009,
  ZDO_UNKNOWN_SECURITY_KEY_MESSAGE        = 0x500A,
  ZDO_UNEXPECTED_CALLBACK                 = 0x500B,
  ZDO_NULL_CALLBACK_WAKEUP_CONF           = 0x500C,
  ZDO_NULL_CALLBACK_SLEEP_CONF            = 0x500D,
  ZDO_NULL_CALLBACK_SET_TX_POWER_CONF_0   = 0x500E,
  ZDO_NULL_CALLBACK_SET_TX_POWER_CONF_1   = 0x500F,
  ZDO_NULL_CALLBACK_ENDTOENDAPPKEY_CONF   = 0x5010,
  ZDO_NULL_CALLBACK_STARTNETWORK_CONF     = 0x5011,
  ZDO_ZDP_MANAGER_QUEUE_EMPTY             = 0x5013,
  ZDO_INVALID_ZDP_REQUEST_STATE           = 0x5014,
  ZDO_DISCOVERY_MANAGER_UNKNOWN_REQ_CLUSTER = 0x5015,
  ZDO_BIND_MANAGER_UNKNOWN_REQ_CLUSTER    = 0x5016,
  ZDO_NODE_MANAGER_UNKNOWN_REQ_CLUSTER    = 0x5017,
  ZDO_DISCOVERY_MANAGER_UNKNOWN_RESP_CLUSTER = 0x5018,
  ZDO_BIND_MANAGER_UNKNOWN_RESP_CLUSTER    = 0x5019,
  ZDO_NODE_MANAGER_UNKNOWN_RESP_CLUSTER    = 0x5020,
  ZDO_NODE_MANAGER_INVALID_SRC_ADDR_MODE  = 0x5021,

  ZDO_SECURITY_MANAGER_0                  = 0x5030,

  ZDO_NWK_MANAGER_0                       = 0x5040,

  ZDO_START_NETWORK_0                     = 0x5050,
  ZDO_START_NETWORK_1                     = 0x5051,
  ZDO_START_NETWORK_2                     = 0x5052,
  ZDO_START_NETWORK_3                     = 0x5053,
  ZDO_START_NETWORK_4                     = 0x5054,
  ZDO_START_NETWORK_5                     = 0x5055,
  ZDO_START_NETWORK_6                     = 0x5056,
  ZDO_START_NETWORK_7                     = 0x5057,
  ZDO_START_NETWORK_8                     = 0x5058,
  ZDO_START_NETWORK_9                     = 0x5059,
  ZDO_START_NETWORK_10                    = 0x505a,
  ZDO_START_NETWORK_11                    = 0x505b,
  ZDO_START_NETWORK_12                    = 0x505c,
  ZDO_START_NETWORK_13                    = 0x505d,
  ZDO_START_NETWORK_14                    = 0x505e,
  ZDO_START_NETWORK_15                    = 0x505f,
  ZDO_START_NETWORK_16                    = 0x5060,
  ZDO_START_NETWORK_17                    = 0x5061,
  ZDO_START_NETWORK_18                    = 0x5062,
  ZDO_START_NETWORK_19                    = 0x5063,

  ZDO_RESET_NETWORK_0                     = 0x5070,
  ZDO_RESET_NETWORK_1                     = 0x5071,
  ZDO_RESET_NETWORK_2                     = 0x5072,
  ZDO_RESET_NETWORK_3                     = 0x5073,

  ZDO_LEAVE_NETWORK_0                     = 0x5090,
  ZDO_LEAVE_NETWORK_1                     = 0x5091,
  ZDO_LEAVE_NETWORK_2                     = 0x5092,
  ZDO_LEAVE_NETWORK_3                     = 0x5093,

  ZDO_TC_SWAPOUT_0                        = 0x50a0,
  ZDO_TC_SWAPOUT_1                        = 0x50a1,
  ZDO_TC_SWAPOUT_2                        = 0x50a2,
  ZDO_TC_SWAPOUT_3                        = 0x50a3,
  ZDO_TC_SWAPOUT_4                        = 0x50a4,
  ZDO_TC_SWAPOUT_5                        = 0x50a5,
  ZDO_TC_SWAPOUT_6                        = 0x50a6,
  ZDO_TC_SWAPOUT_7                        = 0x50a7,

  ZDO_TC_KEEP_ALIVE_0                     = 0x50b0,
} ZdoDbgCode_t;

#endif // _ZDODBG_H

// eof zdoDbg.h
