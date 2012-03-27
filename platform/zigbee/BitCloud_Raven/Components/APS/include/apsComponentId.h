/***************************************************************************//**
  \file apsComponentsId.h

  \brief APS components Id header file
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal 
  History:
    06/06/07 A. Potashov - Created
*****************************************************************************/

#ifndef _APSCOMPONENTID_H
#define _APSCOMPONENTID_H

/******************************************************************************
                   Types section
 ******************************************************************************/

/*****************************************************************************
  APS Component Id
*****************************************************************************/
typedef enum
{
  APS_CONTROL_MANAGER_ID =              0x00,
  APS_AIB_MANAGER_ID =                  0x01,
  APS_SECURITY_MANAGER_ID =             0x02,
  APS_DATA_MANAGER_ID =                 0x03,
  APS_BIND_MANAGER_ID =                 0x04,
  APS_MAX_COMPONENT_ID
} ApsComponentId_t;

#endif  //#ifndef _APSCOMPONENTID_H

//eof apsComponentId.h
