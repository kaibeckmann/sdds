/**************************************************************************//**
  \file nwkGroup.h

  \brief Interface of the group table.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2010-07-20 Max Gekk - Created.
   Last change:
    $Id: nwkGroup.h 12575 2010-09-25 21:25:48Z mgekk $
 ******************************************************************************/
#if !defined _NWK_GROUP_H
#define _NWK_GROUP_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <appFramework.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
/** Value that can not be used as a group data parameter. */
#define NWK_INVALID_GROUP_DATA  0x00
/** Universal group data. It means any group data value. */
#define NWK_ANY_GROUP_DATA      0xFF

/******************************************************************************
                                Types section
 ******************************************************************************/
/** Type of data linked to group. */
typedef uint8_t NWK_GroupData_t;
/** Type of group address. */
typedef GroupAddr_t NWK_GroupAddr_t;

/** Type of group table entry. */
typedef struct _NWK_GroupTableEntry_t
{
  /** The data used by user, for example APS end point. */
  NWK_GroupData_t  data;
  /** Address of group. */
  NWK_GroupAddr_t  addr;
} NWK_GroupTableEntry_t;

/** Type of size of the group table.*/
typedef uint8_t NWK_GroupTableSize_t;

/** Type of internal variables of group component. */
typedef struct _NWK_GroupTable_t
{
  /** Pointer to first entry of the group table. */
  NWK_GroupTableEntry_t  *begin;
  /** Pointer to memory after last entry of the group table. */
  NWK_GroupTableEntry_t  *end;
} NWK_GroupTable_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined _GROUP_TABLE_
/**************************************************************************//**
  \brief Add new entry to the group table.

  \param[in] addr - address of group. Valid range 0x0000 - 0xffff.
  \param[in] data - value linked to group. Valid range 0x01 - 0xfe.

  \return 'true' if entry is added successfully otherwise 'false'.
 ******************************************************************************/
bool NWK_AddGroup(const NWK_GroupAddr_t addr, const NWK_GroupData_t data);

/**************************************************************************//**
  \brief Remove group entries from the group table.

  \param[in] addr - address of group. Valid range 0x0000 - 0xffff.
  \param[in] data - value linked to group. Valid range 0x01 - 0xff.
                    If data is equal to NWK_ANY_GROUP_DATA then remove
                    all entries with given group address.

  \return 'true' if any entry is removed successfully otherwise 'false'.
 ******************************************************************************/
bool NWK_RemoveGroup(const NWK_GroupAddr_t addr, const NWK_GroupData_t data);

/**************************************************************************//**
  \brief Remove all group entries with given group data

  \param[in] data - value linked to group. Valid range 0x01 - 0xff.
                    If data is equal to NWK_ANY_GROUP_DATA then remove
                    all entries from table.

  \return 'true' if any entry is removed successfully otherwise 'false'.
 ******************************************************************************/
bool NWK_RemoveAllGroups(const NWK_GroupData_t data);

/**************************************************************************//**
  \brief Check group address and data in the group table.

  \param[in] addr - address of group. Valid range 0x0000 - 0xffff.
  \param[in] data - value linked to group. Valid range 0x01 - 0xff.
                    If data is equal to NWK_ANY_GROUP_DATA that means
                    any enties with given group address.

  \return 'true' if pair addr and data is found in the group table
           otherwise 'false'.
 ******************************************************************************/
bool NWK_IsGroupMember(const NWK_GroupAddr_t addr, const NWK_GroupData_t data);

/**************************************************************************//**
  \brief Allocate and initialize the group table.

  \param[in] powerFailure - clear entries of group table if 'true' otherwise
                            only read pointer to table and size
                            from the config server.
 ******************************************************************************/
void NWK_ResetGroups(const bool powerFailure);

#else
#define NWK_ResetGroups(powerFailure) (void)0
#endif /* _GROUP_TABLE_ */
#endif /* _NWK_GROUP_H */
/** eof nwkGroup.h */

