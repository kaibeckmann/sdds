/**************************************************************************//**
  \file  spi.c

  \brief Implementation of USART SPI mode, hardware-independent module.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      29/06/07 E. Ivanov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <spi.h>

/******************************************************************************
                   Global functions prototypes section
******************************************************************************/
/******************************************************************************
Set the parameters of USART to work at SPI mode.
Parameters:
  descriptor - pointer to the spi descriptor.
Returns:
  none.
******************************************************************************/
void halSetSpiConfig(HAL_SpiDescriptor_t *descriptor);

/******************************************************************************
                   External global variables section
******************************************************************************/
extern HAL_UsartDescriptor_t *halPointDescrip[NUM_USART_CHANNELS];

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief Opens USART in MSPI mode.
\param[in]
    descriptor - pointer to the spi descriptor.
\return
   -1 - there not are free resources.
    0 - SPI channel is ready.
******************************************************************************/
int HAL_OpenSpi(HAL_SpiDescriptor_t *descriptor)
{
  uint8_t i; // Descriptor index

  if (NULL == descriptor)
    return -1;
  if (false == halIsUsartChannelCorrect(descriptor->tty))
    return -1;

  i = HAL_GET_INDEX_BY_CHANNEL(descriptor->tty);
  if (NULL != halPointDescrip[i])
    return -1; // Channel is already opened.

  if (NULL != descriptor->callback)
  {
    descriptor->spiDescriptor.txCallback = descriptor->callback;
    descriptor->spiDescriptor.tty = descriptor->tty;
  }

  halPointDescrip[i] = &descriptor->spiDescriptor;
  halSetSpiConfig(descriptor);
  switch (descriptor->tty)
  {
    #ifdef SPI_CHANNEL_0
      case SPI_CHANNEL_0:
          GPIO_USART0_EXTCLK_make_out();
        break;
    #endif
    #ifdef SPI_CHANNEL_1
      case SPI_CHANNEL_1:
          GPIO_USART1_EXTCLK_make_out();
        break;
    #endif
      default:
        break;
  }
  return 0;
}

/**************************************************************************//**
\brief Frees the channel and pins.
\param[in]
  descriptor - pointer to the spi descriptor.
\return
  Returns 0 on success or -1 if channel was not opened.
******************************************************************************/
int HAL_CloseSpi(HAL_SpiDescriptor_t *descriptor)
{
  uint8_t i;

  if (NULL == descriptor)
    return -1;
  if (false == halIsUsartChannelCorrect(descriptor->tty))
    return -1;
  i = HAL_GET_INDEX_BY_CHANNEL(descriptor->tty);
  if (NULL == halPointDescrip[i])
    return -1; // Channel is already closed.

  halPointDescrip[i] = NULL;
  halCloseSpi(descriptor->tty);

  switch (descriptor->tty)
  {
    #ifdef SPI_CHANNEL_0
      case SPI_CHANNEL_0:
          GPIO_USART0_EXTCLK_make_in();
        break;
    #endif
    #ifdef SPI_CHANNEL_1
      case SPI_CHANNEL_1:
          GPIO_USART1_EXTCLK_make_in();
        break;
    #endif
      default:
        break;
  }
  return 0;
}


/**************************************************************************//**
\brief Writes a length bytes to the SPI. \n
 Callback function will be used to notify about the finishing transmitting.
\param[in]
  descriptor -  pointer to spi descriptor
\param[in]
  buffer     -  pointer to application data buffer;
\param[in]
  length     -  number bytes for transfer;
\return
  -1 - spi module was not opened, there is unsent data, pointer to data or
       the length are zero; \n
   0 - on success or a number; \n
   Number of written bytes if the synchronous method is used(callback is NULL).
******************************************************************************/
int HAL_WriteSpi(HAL_SpiDescriptor_t *descriptor, uint8_t *buffer, uint16_t length)
{
  HalUsartService_t *halUsartControl;
  HAL_UsartDescriptor_t *spiDescrip;

  if (NULL == descriptor)
    return -1;
  if (false == halIsUsartChannelCorrect(descriptor->tty))
    return -1;
  if (!buffer || !length)
    return -1;
  spiDescrip = &descriptor->spiDescriptor;
  if (spiDescrip != halPointDescrip[HAL_GET_INDEX_BY_CHANNEL(descriptor->tty)])
    return -1; // Channel is not opened.

  if (NULL != descriptor->callback)
  {
    halUsartControl = &spiDescrip->service;
    if (halUsartControl->txPointOfWrite != halUsartControl->txPointOfRead)
      return -1; // there is unsent data

    spiDescrip->txBuffer = buffer;
    spiDescrip->txBufferLength = 0;
    halUsartControl->txPointOfWrite = length;
    halUsartControl->txPointOfRead = 0;
    spiDescrip->rxBuffer = buffer;
    spiDescrip->flowControl = USART_SPI_WRITE_MODE;
    halEnableSpiRxcInterrupt(descriptor->tty);
    halEnableSpiDremInterrupt(descriptor->tty);
    return 0;
  }
  else
  {
    return halSyncWriteData(descriptor->tty, buffer, length);
  }
}

/**************************************************************************//**
\brief Writes a number of bytes to the SPI.\n
 Callback function will be used to notify when the activity is finished.\n
 The read data is placed to the buffer.
\param[in]
  descriptor - pointer to HAL_SpiDescriptor_t structure
\param[in]
  buffer -  pointer to the application data buffer
\param[in]
  length -  number of bytes to transfer
\return
  -1 - spi module was not opened, or there is unsent data, or the pointer to
   data or the length are NULL; \n
   0 - success; \n
   Number of written bytes if the synchronous method is used(callback is NULL).
******************************************************************************/
int HAL_ReadSpi(HAL_SpiDescriptor_t *descriptor, uint8_t *buffer, uint16_t length)
{
  HalUsartService_t *halUsartControl;
  HAL_UsartDescriptor_t *spiDescrip;

  if (NULL == descriptor)
    return -1;
  if (false == halIsUsartChannelCorrect(descriptor->tty))
    return -1;
  if (!buffer || !length)
    return -1;
  spiDescrip = &descriptor->spiDescriptor;
  if (spiDescrip != halPointDescrip[HAL_GET_INDEX_BY_CHANNEL(descriptor->tty)])
    return -1; // Channel is not opened.

  if (NULL != descriptor->callback)
  {
    halUsartControl = &spiDescrip->service;
    if (halUsartControl->txPointOfWrite != halUsartControl->txPointOfRead)
      return -1; // there is unsent data

    spiDescrip->txBuffer = buffer;
    spiDescrip->txBufferLength = 0;
    halUsartControl->txPointOfWrite = length;
    halUsartControl->txPointOfRead = 0;
    spiDescrip->rxBuffer = buffer;
    spiDescrip->flowControl = USART_SPI_READ_MODE;
    halEnableSpiRxcInterrupt(descriptor->tty);
    halEnableSpiDremInterrupt(descriptor->tty);
    return 0;
  }
  else
  {
    return halSyncReadData(descriptor->tty, buffer, length);
  }
}
// eof spi.c

