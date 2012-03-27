/*****************************************************************************
  \file  sipc.c

  \brief 

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    10/26/2009 I.Vagulin - Created
******************************************************************************/

/*****************************************************************************
                              Includes section
******************************************************************************/
#include <queue.h>
#include <usart.h>
#include "sipc.h"

/******************************************************************************
                   Defines section
******************************************************************************/

#define SIPC_FRAME_LEN_MAX   0x5
#define USART_RX_BUF_LENGTH (SIPC_FRAME_LEN_MAX*2 + 1 + 1)
#define USART_TX_BUF_LENGTH 0x32
#define SIPC_SOF      (0x02) //!< Unique start of frame delimiter.
#define SIPC_EOF      (0x03) //!< Unique end of frame delimiter.
#define SIPC_ESC      (0x17) //!< Unique byte used to indicate a stuffed byte.
#define SIPC_ESC_MASK (0x40) //!< Value used to OR together with the stuffed byte.

/****************************************************************************
                              Static functions prototypes section
******************************************************************************/
static void rxCallback(uint16_t len);

/*****************************************************************************
                              Global variables section
******************************************************************************/
static struct
{
  uint8_t rxInProgress:1;
  uint8_t nextByteStuffed:1;
  uint8_t readedBytes:6;
} rxDescriptor ;

static uint8_t openCnt = 0;
static uint8_t usartTxBuf[USART_TX_BUF_LENGTH];
static uint8_t usartRxBuf[USART_RX_BUF_LENGTH];
static uint8_t sipcInputFrame[SIPC_FRAME_LEN_MAX];
DECLARE_QUEUE(listeners);

static HAL_UsartDescriptor_t usartDescriptor =
{
  .tty            = USART_CHANNEL_0,
  .mode           = USART_MODE_ASYNC,
  .flowControl    = USART_FLOW_CONTROL_NONE,
  .baudrate       = USART_BAUDRATE_38400,
  .dataLength     = USART_DATA8,
  .parity         = USART_PARITY_NONE,
  .stopbits       = USART_STOPBIT_1,
  .rxBuffer       = usartRxBuf,
  .rxBufferLength = sizeof(usartRxBuf),
  .txBuffer       = usartTxBuf,
  .txBufferLength = sizeof(usartTxBuf),
  .rxCallback     = rxCallback,
  .txCallback     = NULL,
};

/******************************************************************************
                              Implementations section
******************************************************************************/
/***********************************************************************************
  Description: Callback of usart rx. decrypt sipc protocol and call listener on
               Successful receiving.
  Parameters: length of arrived data.
  Return: none
 ***********************************************************************************/
static void rxCallback(uint16_t len)
{
  uint8_t byte;
  do
  {
    HAL_ReadUsart(&usartDescriptor, &byte, 1);
    len--;

    //wait start of frame
    if (!rxDescriptor.rxInProgress && byte != SIPC_SOF)
      continue;

    //search for control bytes
    if (byte == SIPC_SOF)
    {
      memset(&rxDescriptor, 0, sizeof(rxDescriptor));
      rxDescriptor.rxInProgress = true;
      continue;
    }
    else if (byte == SIPC_EOF)
    {
      rxDescriptor.rxInProgress = false;
      SipcInd_t *it = NULL;
      if (rxDescriptor.readedBytes > 0)
      {
        for(it = getQueueElem(&listeners); it; it = getNextQueueElem(it))
          it->sipcInd(sipcInputFrame[0], sipcInputFrame+1);
      }
      continue;
    }
    else if (byte == SIPC_ESC)
    {
      rxDescriptor.nextByteStuffed = true;
      continue;
    }

    //process normal bytes
    if (rxDescriptor.readedBytes >= SIPC_FRAME_LEN_MAX)
      continue;

    if (rxDescriptor.nextByteStuffed)
    {
      byte &= ~SIPC_ESC_MASK;
      rxDescriptor.nextByteStuffed = false;
    }

    sipcInputFrame[rxDescriptor.readedBytes] = byte;
    rxDescriptor.readedBytes++;
  } while (len);
}

void bspSipcOpen(SipcInd_t* listener)
{
  if (listener)
    putQueueElem(&listeners, listener);

  if (openCnt != 0)
  {
    openCnt++;
  }
  else
  {
    openCnt = 1;
    HAL_OpenUsart(&usartDescriptor);
  }
}

void bspSipcSendFrameByParts(SipcFramePart_t parts[], uint8_t partsCnt)
{
  uint8_t i;

  HAL_WriteUsart(&usartDescriptor, &(uint8_t){SIPC_SOF}, sizeof(uint8_t));
  for (i = 0; i < partsCnt; i++)
  {
    const uint8_t * it;
    for(it = parts[i].data; it < parts[i].data + parts[i].len; it++)
    {
      uint8_t byte = *it;
      if (byte == SIPC_SOF || byte == SIPC_EOF || byte == SIPC_ESC)
        byte |= SIPC_ESC_MASK;
      HAL_WriteUsart(&usartDescriptor, &byte, 1);
    }
  }
  HAL_WriteUsart(&usartDescriptor, &(uint8_t){SIPC_EOF}, sizeof(uint8_t));
}

void bspSipcSendFrame(void* frame, uint8_t len)
{
  SipcFramePart_t part =
  {
    .data = frame,
    .len = len,
  };
  bspSipcSendFrameByParts(&part, 1);
}

void bspSipcClose(SipcInd_t *listener)
{
  if (listener)
    deleteQueueElem(&listeners, listener);

  if (openCnt > 1)
  {
    openCnt--;
  }
  else
  {
    openCnt = 0;
    HAL_CloseUsart(&usartDescriptor);
  }
}

bool bspSipcTxInProgress()
{
  if (HAL_IsTxEmpty(&usartDescriptor) == 1) // USART buffer free
    return false;
  else
    return true;
}

