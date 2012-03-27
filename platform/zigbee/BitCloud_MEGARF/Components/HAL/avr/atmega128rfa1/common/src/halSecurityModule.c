/*************************************************************************//**
  \file halSecurityModule.c

  \brief Implementation of AES encryption routines.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    12.08.09 A. Taradov - Created.
*****************************************************************************/

#ifdef _HAL_HW_AES_
/******************************************************************************
                    Includes section
******************************************************************************/
#include <dbg.h>
#include <halDbg.h>
#include <types.h>
#include <queue.h>
#include <halSecurityModule.h>
#include <halTaskManager.h>

/******************************************************************************
                    Defines section
******************************************************************************/
#define AES_CTRL_IM             (1<<2)
#define AES_CTRL_DIR            (1<<3)
#define AES_CTRL_MODE           (1<<5)
#define AES_CTRL_REQUEST        (1<<7)

#define AES_STATUS_RY           (1<<0)
#define AES_STATUS_ER           (1<<7)

/******************************************************************************
                    Local variables
******************************************************************************/
static DECLARE_QUEUE(smEncryptRequestQueue);

/******************************************************************************
                    Implementations section
******************************************************************************/
/******************************************************************************
  Encryption commands handler.
  Parameters:
    request - pointer to request parameters structure.
  Returns:
    none
******************************************************************************/
void HAL_SmEncryptReq(HAL_SmEncryptReq_t *request)
{
  putQueueElem(&smEncryptRequestQueue, request);
  halPostTask3(HAL_SM_ENCRYPT_REQ);
}

/******************************************************************************
  Encrypt task handler.
  Parameters:
    none
  Returns:
    none
******************************************************************************/
void halSmEncryptRequestHandler(void)
{
  uint8_t i, j;
  uint8_t blockOffset = 0;
  HAL_SmEncryptReq_t *request;

  request = getQueueElem(&smEncryptRequestQueue);
  switch (request->command)
  {
    case SM_SET_KEY_COMMAND:
      for (i = 0; i < HAL_SM_SECURITY_KEY_SIZE; i++)
        AES_KEY = request->text[i];
      break;

    case SM_ECB_ENCRYPT_COMMAND:
      for (i = 0; i < request->blockCount; i++)
      {
        // Enable encryption (DIR = 0) and ECB mode (MODE = 0)
        AES_CTRL = 0;

        // Load data to encrypt
        for (j = 0; j < HAL_SM_SECURITY_BLOCK_SIZE; j++)
          AES_STATE = request->text[blockOffset + j];

        // Start encryption
        AES_CTRL |= AES_CTRL_REQUEST;

        // Wait for operation to complete
        while (!(AES_STATUS & AES_STATUS_RY));

        // Store encrypted data
        for (j = 0; j < HAL_SM_SECURITY_BLOCK_SIZE; j++)
          request->text[blockOffset + j] = AES_STATE;

        // Process next block
        blockOffset += HAL_SM_SECURITY_BLOCK_SIZE;
      }
      break;

    default:
      assert(false, SECURITY_MODULE_INVALID_COMMAND);
      break;
  }

  deleteHeadQueueElem(&smEncryptRequestQueue);
  if (getQueueElem(&smEncryptRequestQueue))
    halPostTask3(HAL_SM_ENCRYPT_REQ);

  request->HAL_SmEncryptConf();
}
#endif // _HAL_HW_AES_

// eof halSecurityModule.c
