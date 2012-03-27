/**************************************************************************//**
  \file apsGroupManager.h

  \brief Interface of APS Group Manager.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    24/07/07 A. Potashov - Created.
    21/07/10 M. Gekk     - Refactoring.
 ******************************************************************************/
#ifndef _APS_GROUP_MANAGER_H
#define _APS_GROUP_MANAGER_H
/**
 * This interface allows the next higher layer to manage group membership
 * for endpoints on the current device by adding and removing entries in 
 * the group table. See ZigBee spec. r18, 2.2.4.5, page 45.
 **/

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <apsCommon.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/**************************************************************************//**
  \brief Parameters of the APSME-ADD-GROUP.confirm primitive.
 ******************************************************************************/
typedef struct _APS_AddGroupConf_t
{
  /*! The status of the request to add a group. */
  APS_Status_t status;
} APS_AddGroupConf_t;

/**************************************************************************//**
  \brief Parameters of the APS_AddGroupReq() function.
 ******************************************************************************/
typedef struct _APS_AddGroupReq_t
{
  /*! The 16-bit address of the group being added. */
  GroupAddr_t groupAddress;
  /*! The endpoint to which the given group is being added. */
  Endpoint_t endpoint;

  /*! The confirm primitive as transaction result. */
  APS_AddGroupConf_t confirm;
} APS_AddGroupReq_t;


/**************************************************************************//**
  \brief Parameters of the APS_RemoveGroupConf() function.
 ******************************************************************************/
typedef struct _APS_RemoveGroupConf_t
{
  /*! The status of the request to remove a group. */
  APS_Status_t status;
} APS_RemoveGroupConf_t;

/**************************************************************************//**
  \brief Parameters of the APS_RemoveGroupReq() function.
 ******************************************************************************/
typedef struct _APS_RemoveGroupReq_t
{
  /*! The 16-bit address of the group being removed. */
  GroupAddr_t groupAddress;
  /*! The endpoint from which the given group is being removed. */
  Endpoint_t endpoint;

  /*! The confirm primitive as transaction result. */
  APS_RemoveGroupConf_t confirm;
} APS_RemoveGroupReq_t;


/**************************************************************************//**
  \brief Parameters structure of the APS_RemoveAllGroupsConf() function.
 ******************************************************************************/
typedef struct _APS_RemoveAllGroupsConf_t
{
  /*! The status of the request to remove all groups. */
  APS_Status_t status;
} APS_RemoveAllGroupsConf_t;

/**************************************************************************//**
  \brief Parameters structure of the APS_RemoveAllGroupsReq() function.
 ******************************************************************************/
typedef struct _APS_RemoveAllGroupsReq_t
{
  /*! The endpoint from which the group is being removed. */
  Endpoint_t endpoint;

  /*! The confirm primitive as transaction result. */
  APS_RemoveAllGroupsConf_t confirm;
} APS_RemoveAllGroupsReq_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Add the current device to the members of certain group.

  \param[in] req - pointer to parameters of the APSME-ADD-GROUP.request.
 *****************************************************************************/
void APS_AddGroupReq(APS_AddGroupReq_t *const req);

/**************************************************************************//**
  \brief Remove the current device from the members of certain group.

  \param[in] req - pointer to parameters of the APSME-REMOVE-GROUP.request.
 ******************************************************************************/
void APS_RemoveGroupReq(APS_RemoveGroupReq_t *const req);

/**************************************************************************//**
  \brief Remove the current device from members of all groups.

  \param[in] req - pointer to parameters of the APSME-REMOVE-ALL-GROUPS.request.
 ******************************************************************************/
void APS_RemoveAllGroupsReq(APS_RemoveAllGroupsReq_t *const req);

#endif /* _APS_GROUP_MANAGER_H */
/** eof apsGroupManager.h */
