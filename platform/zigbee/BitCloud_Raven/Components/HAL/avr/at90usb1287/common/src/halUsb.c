/*************************************************************************//**
  \file  halUsb.c

  \brief Implementation of usb hardware-dependent module.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      08/07/08 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <halUsb.h>
#include <usb.h>

/******************************************************************************
                   Defines section
******************************************************************************/
/* Initial data */
#define INITIAL_DATA     0xFFFFFFFF

/* common bit mask */
#define COMMON_EPTYPE     0xC0
/* control end point */
#define CONTROL_EPTYPE    0x00

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
Resets all the endpoints of the UDP peripheral.
******************************************************************************/
void halResetEndpoints(void);

/******************************************************************************
Disables all endpoints of the UDP peripheral except control endpoint 0.
******************************************************************************/
void halDisableEndpoints(void);

/******************************************************************************
                   Global variables section
******************************************************************************/
// Holds the internal state for each endpoint of the UDP
UsbEndpoint_t endpoints[USB_END_POINTS_NUMBER];
// Device current state
volatile uint8_t deviceState;
// Previous device current state
volatile uint8_t previousDeviceState;
// user's request handler
void (* sendReqToUpper)(uint8_t *req) = NULL;
// pointer to request memory. Memory allocate by user.
uint8_t *requestMemory = NULL;

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
configure and enable usb role
******************************************************************************/
void halInitUsbDevice(void)
{
  // set usb device mode with UID pin and enable pad regulator
  UHWCON |= ((1 << UIDE) | (1 << UVREGE));
  // enable usb and enable clock on usb
  USBCON |= ((1 << USBE) | (1 << OTGPADE));
  USBCON &= ~(1 << FRZCLK);
}

/******************************************************************************
Resets all the endpoints of the usb peripheral.
******************************************************************************/
void halResetEndpoints(void)
{
  UsbEndpoint_t *endpoint;
  UsbTransfer_t *transfer;
  uint8_t eptnum;

  // Reset the transfer descriptor of every endpoint
  for (eptnum = 0; eptnum < USB_END_POINTS_NUMBER; eptnum++)
  {
    endpoint = &(endpoints[eptnum]);
    transfer = &(endpoint->transfer);
    // Reset endpoint transfer descriptor
    transfer->data = 0;
    transfer->transferred = INITIAL_DATA;
    transfer->buffered = INITIAL_DATA;
    transfer->remaining = INITIAL_DATA;
    transfer->callback = NULL;
    transfer->argument = 0;
    // Reset endpoint state
    endpoint->state = UDP_ENDPOINT_DISABLED;
  }
}

/******************************************************************************
tuning and setting usb device options and enable interrupts
******************************************************************************/
void halUsbInterrupt(void)
{
  // Clear general interrupts
  UDINT = 0;
  // Enable wake up and end of reset interrupt
  UDIEN = (1 << WAKEUPE) | (1 << EORSTE);
  // set device in the full speed mode and attach to the host
  UDCON = 0;
}

/******************************************************************************
Sets usb endpoint parameters

Parameters:
   eptnum - endpoint number
   type - endpoint type
   direction - transaction direction
******************************************************************************/
void halConfigureEndpoint(uint8_t eptnum, uint8_t type, HAL_UsbEndPointDirect_t direction)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);

  // Reset endpoint FIFO
  UERST |= (1 << eptnum);
  UERST &= ~(1 << eptnum);

  // Configure and activation endpoint
  // select end point
  UENUM = eptnum;
  // enable endpoint
  UECONX = (1 << EPEN);
  // configure endpoint direction and type
  UECFG0X = (uint8_t)direction | (type << 6);
  // memory manager for endpoint
  switch(endpoint->size) // set enpoint size (in bytes)
  {
    case  16:
        UECFG1X = (1 << EPSIZE0);
      break;
    case  32:
        UECFG1X = (1 << EPSIZE1);
      break;
    case  64:
        UECFG1X = (1 << EPSIZE0) | (1 << EPSIZE1);
      break;
    case 128:
        if (256 == UDP_ENDPOINTS_MAXPACKETSIZE(eptnum))
          UECFG1X = (1 << EPSIZE0);
        else
          UECFG1X = 0;
      break;
    case 256:
        if (256 == UDP_ENDPOINTS_MAXPACKETSIZE(eptnum))
          UECFG1X = (1 << EPSIZE0) | (1 << EPSIZE2);
        else
          UECFG1X = 0;
      break;
    default:
        UECFG1X = 0;
      break;
  }
  if (eptnum)
  { // The others have two bank of memory
    UECFG1X |= (1 << EPBK0) | (1 << ALLOC);
  } // The others have two bank of memory
  else
  { // endpoint 0 has only one bank of memory
    UECFG1X |= (1 << ALLOC);
  } // endpoint 0 has only one bank of memory

  // incorrect parameters
  if (!(UESTA0X & (1 << CFGOK)))
  {
    endpoint->state = UDP_ENDPOINT_DISABLED;
    return;
  }

  if (EP_CONTROL == type)
    halEnableEndPointSetupInterrupt(eptnum);
}

/******************************************************************************
Handles a completed transfer on the given endpoint, invoking the configured
callback if any.

Parameters:
  eptnum - Number of the endpoint for which the transfer has completed.
  status - Result of the USB transfer.
******************************************************************************/
void halEndOfTransfer(uint8_t eptnum, uint8_t status)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);
  UsbTransfer_t *transfer = &(endpoint->transfer);

  // Check that endpoint was sending or receiving data
  if ((UDP_ENDPOINT_RECEIVING == endpoint->state) || (UDP_ENDPOINT_SENDING == endpoint->state))
  {
    // Endpoint returns in Idle state
    endpoint->state = UDP_ENDPOINT_IDLE;
    // Invoke callback is present
    if (NULL != transfer->callback)
    {
      ((TransferCallback_t) transfer->callback)(transfer->argument, status,
                                              transfer->transferred, transfer->remaining + transfer->buffered);
    }
  }
}

/******************************************************************************
Disables all endpoints of the usb peripheral except control endpoint 0.
******************************************************************************/
void halDisableEndpoints(void)
{
  uint8_t eptnum;

  // Disable each endpoint, terminating any pending transfer
  for (eptnum = 1; eptnum < USB_END_POINTS_NUMBER; eptnum++)
  {
    halEndOfTransfer(eptnum, STATUS_ABORTED);
    endpoints[eptnum].state = UDP_ENDPOINT_DISABLED;
  }
}

/******************************************************************************
End of bus reset state handler
******************************************************************************/
void halEndOfBusResetHandler(void)
{
  // The device enters the Default state
  deviceState = DEVICE_DEFAULT;
  halResetEndpoints();
  halDisableEndpoints();
  HAL_ConfigureEndpoint(NULL);
}

/******************************************************************************
Checks if an ongoing transfer on an endpoint has been completed.

Parameters:
 eptnum - Endpoint number.

Returns:
  1 - if the current transfer on the given endpoint is complete;
  0 - otherwise
******************************************************************************/
uint8_t halIsTransferFinished(uint8_t eptnum)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);
  UsbTransfer_t *transfer = &(endpoint->transfer);

  // Check if it is a Control endpoint
  // Control endpoint must always finish their transfer with a zero-length packet
  if (CONTROL_EPTYPE == (UECFG0X & COMMON_EPTYPE)) // control endpoint
    return (transfer->buffered < endpoint->size);
  else // Other endpoints only need to transfer all the data
    return (transfer->buffered <= endpoint->size) && (transfer->remaining == 0);
}

/******************************************************************************
Writes a data payload into the current FIFO buffer of the usb.

Parameters:
  eptnum - Number of the endpoint which is sending data.
******************************************************************************/
void halWritePayload(uint8_t eptnum)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);
  UsbTransfer_t *transfer = &(endpoint->transfer);
  uint16_t size;

  // Get the number of bytes to send
  size = endpoint->size;
  if (size > transfer->remaining)
  {
    size = transfer->remaining;
  }

  // Update transfer descriptor information
  transfer->buffered += size;
  transfer->remaining -= size;

  // Write packet in the FIFO buffer
  while (size > 0)
  {
    UEDATX = *(transfer->data);
    transfer->data++;
    size--;
  }
}

/******************************************************************************
Reads a data payload from the current FIFO buffer of an endpoint.

Parameters:
  eptnum - Endpoint number.
  size - Size of the data to read.
******************************************************************************/
void halReadPayload(uint8_t eptnum, uint16_t size)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);
  UsbTransfer_t *transfer = &(endpoint->transfer);

  // Check that the requested size is not bigger than the remaining transfer
  if (size > transfer->remaining)
  {
    transfer->buffered += size - transfer->remaining;
    size = transfer->remaining;
  }

  // Update transfer descriptor information
  transfer->remaining -= size;
  transfer->transferred += size;

  // Retrieve packet
  while (size > 0)
  {
    *(transfer->data) = UEDATX;
    transfer->data++;
    size--;
  }
}

/******************************************************************************
Reads a SETUP request from the FIFO buffer of Control endpoint and stores it
into the global request variable.

Parameters:
  request - global variable for request reading
  eptnum - endpoint number
******************************************************************************/
void halReadRequest(uint8_t *request)
{
  uint16_t i;

  // Copy packet
  for (i = 0; i < 8; i++)
  {
    *request = UEDATX;
    request++;
  }
}

/******************************************************************************
Control endpoint interrupt handler. Manages IN, OUT & SETUP transaction, as well
as the STALL condition.

Parameters:
  eptnum - Number of the endpoint to handle interrupt for.
******************************************************************************/
void halControlEndpointHandler(uint8_t eptnum)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);
  UsbTransfer_t *transfer = &(endpoint->transfer);

  // chose action reason
  uint8_t status = UEINTX;
  status &= endpoint->irqReason;

  // SETUP packet received
  if (status & (1 << RXSTPI))
  {
    // If a transfer was pending, complete it
    // Handles the case where during the status phase of a control write
    // transfer, the host receives the device ZLP and ack it, but the ack
    // is not received by the device
    if ((UDP_ENDPOINT_RECEIVING == endpoint->state) || (UDP_ENDPOINT_SENDING == endpoint->state))
    {
      halEndOfTransfer(eptnum, STATUS_SUCCESS);
    }
    halReadRequest(requestMemory);

    UEINTX &= ~(1 << RXSTPI); // clear setup interrupt
    if (UESTA1X & (1 << CTRLDIR))
    { // enable interrupt to sense STATUS part of control read transaction
      halEnableEndPointRxInterrupt(eptnum);
    }
    else
    { // enable interrupt to sense STATUS part of control write transaction
      halEnableEndPointNakinInterrupt(eptnum);
    }

    // Forward the request to the upper layer
    if (sendReqToUpper)
      sendReqToUpper(requestMemory);
  }

  // OUT packet received
  if (status & (1 << RXOUTI))
  {
    uint16_t byteCounter = UEBCHX;
    byteCounter <<= 8;
    byteCounter |= UEBCLX;

    // Check that the endpoint is in Receiving state
    if (UDP_ENDPOINT_RECEIVING != endpoint->state)
    {
      // Acknowledge the data and finish the current transfer
      // clear interrupt
      UEINTX &= ~(1 << RXOUTI);

      // Check if an ACK has been received on a Control endpoint
      if (0 == byteCounter)
      { // STATUS part of control read transaction
        halEnableEndPointSetupInterrupt(eptnum);
      }
    }
    // Endpoint is in Read state
    else
    {
      // Retrieve data and store it into the current transfer buffer
      halReadPayload(eptnum, byteCounter);
      // clear interrupt
      UEINTX &= ~(1 << RXOUTI);
      if ((transfer->remaining == 0) || (byteCounter < endpoint->size))
      {
        halEndOfTransfer(eptnum, STATUS_SUCCESS);
        // End of transaction data stage. Enable interrupt for status stage
        halEnableEndPointNakinInterrupt(eptnum);
      }
      else // continue receive
      {
        halEnableEndPointRxInterrupt(eptnum);
      }
    }
  }

  // IN packet sent
  if (status & (1 << TXINI))
  {
    // Check that endpoint was in Sending state
    if (UDP_ENDPOINT_SENDING == endpoint->state)
    {
      if (halIsTransferFinished(eptnum))
      { // transfer is finished
        transfer->transferred += transfer->buffered;
        transfer->buffered = 0;
        halEndOfTransfer(eptnum, STATUS_SUCCESS);
        // End of transaction data stage. Enable interrupt for status stage
        halEnableEndPointRxInterrupt(eptnum);
      }
      else
      {
        // Transfer remaining data
        transfer->transferred += endpoint->size;
        transfer->buffered -= endpoint->size;
        // Send next packet
        halWritePayload(eptnum);
        // clear interrupt
        UEINTX &= ~(1 << TXINI);
        halEnableEndPointTxInterrupt(eptnum);
      }
    }
  }

  // NAK IN packet sent
  if (status & (1 << NAKINI))
  { // STATUS part of control write transaction
    // clear interrupt
    UEINTX &= ~(1 << NAKINI);
    // send zlp like ack
    UEINTX &= ~(1 << TXINI);
    if (DEVICE_PREADDRESSED == deviceState)
    {
      // wait for end of zlp ack
      while (!(UEINTX & (1 << TXINI)));
      UDADDR |= (1 << ADDEN);
      deviceState = DEVICE_ADDRESS;
    }
    // enable setup packet interrupt
    halEnableEndPointSetupInterrupt(eptnum);
  }

  // STALL sent
  if (status & (1 << STALLEDI))
  {
    // If the endpoint is not halted, clear the STALL condition
    UEINTX &= ~(1 << STALLEDI); // clear interrupt
    halEnableEndPointSetupInterrupt(eptnum);
  }
}

/******************************************************************************
Endpoint interrupt handler. Manages IN, OUT & SETUP transaction, as well
as the STALL condition.

Parameters:
  eptnum - Number of the endpoint to handle interrupt for.
******************************************************************************/
void halEndpointHandler(uint8_t eptnum)
{
  UsbEndpoint_t *endpoint = &(endpoints[eptnum]);
  UsbTransfer_t *transfer = &(endpoint->transfer);

  // chose action reason
  uint8_t status = UEINTX;
  status &= endpoint->irqReason;

  // Handle interrupts
  // IN packet sent
  if (status & (1 << TXINI))
  {
    // Check that endpoint was in Sending state
    if (UDP_ENDPOINT_SENDING == endpoint->state)
    {
      if (halIsTransferFinished(eptnum))
      { // transfer is finished
        transfer->transferred += transfer->buffered;
        transfer->buffered = 0;
        // clear interrupt
        UEINTX &= ~(1 << TXINI);
        halEndOfTransfer(eptnum, STATUS_SUCCESS);
      }
      else
      {
        // Transfer remaining data
        transfer->transferred += endpoint->size;
        transfer->buffered -= endpoint->size;
        // Send next packet
        if (UDP_ENDPOINTS_BANKS(eptnum) == 1)
        {
          // No double buffering. Load to FIFO next data.
          halWritePayload(eptnum);
          // clear interrupt
          UEINTX &= ~(1 << TXINI);
          // clear FIFOCON bit to start IN transaction
          UEINTX &= ~(1 << FIFOCON);
        }
        else
        {
          // Double buffering. Start previous loaded data.
          // clear interrupt
          UEINTX &= ~(1 << TXINI);
          // clear FIFOCON bit to start IN transaction
          UEINTX &= ~(1 << FIFOCON);
          // Load data to the cleared buffer.
          halWritePayload(eptnum);
        }
        halEnableEndPointTxInterrupt(eptnum);
      }
    }
  }

  // OUT packet received
  if (status & (1 << RXOUTI))
  {
    uint16_t byteCounter = UEBCHX;
    byteCounter <<= 8;
    byteCounter |= UEBCLX;
    if (!byteCounter)
    {
      halEnableEndPointRxInterrupt(eptnum);
      return;
    }

    // Check that the endpoint is in Receiving state
    if (UDP_ENDPOINT_RECEIVING == endpoint->state)
    {
      // Retrieve data and store it into the current transfer buffer
      halReadPayload(eptnum, byteCounter);
      // clear interrupt
      UEINTX &= ~(1 << RXOUTI);
      // clear FIFOCON bit to start next OUT transaction
      UEINTX &= ~(1 << FIFOCON);
      // Check if the transfer is finished
      if ((transfer->remaining == 0) || (byteCounter < endpoint->size))
      {
        halEndOfTransfer(eptnum, STATUS_SUCCESS);
      }
    }
  }
}

/******************************************************************************
Common end points interrupt handler
******************************************************************************/
void halCommonEndpointHandler(void)
{
  uint8_t inc = 0;

  for (inc = 0; inc < USB_END_POINTS_NUMBER; inc++)
  {
    // select end point
    UENUM = inc;
    if (CONTROL_EPTYPE == (UECFG0X & COMMON_EPTYPE)) // control endpoint
      halControlEndpointHandler(inc);
    else
      halEndpointHandler(inc);
  }
}

/******************************************************************************
Loads data to current FIFO and starts sending

Parameters:
  eptnum - Endpoint number.
  remaining - data remaining
******************************************************************************/
void halStartUsbWrite(uint8_t eptnum, uint32_t remaining)
{
  // select end point
  UENUM = eptnum;

  halWritePayload(eptnum);
  // clear interrupt
  UEINTX &= ~(1 << TXINI);
  if (CONTROL_EPTYPE != (UECFG0X & COMMON_EPTYPE))
  {
    // clear FIFOCON bit to start next OUT transaction
    UEINTX &= ~(1 << FIFOCON);
  }

  // If double buffering is enabled and there is data remaining,
  // prepare another packet
  if ((UDP_ENDPOINTS_BANKS(eptnum) > 1) && (remaining > 0))
  {
    halWritePayload(eptnum);
  }
}

/******************************************************************************
Sets the HALT feature on the given endpoint.

Parameters:
  eptnum - Endpoint number.
******************************************************************************/
void halEndpointHaltState(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // Put endpoint into Halt state
  UECONX |= (1 << STALLRQ);
  endpoints[eptnum].state = UDP_ENDPOINT_HALTED;
}

/******************************************************************************
Clears the Halt feature on the given endpoint.

Parameters:
  eptnum - Endpoint number.
******************************************************************************/
void halEndpointUnHaltState(uint8_t eptnum)
{
  // Clear FORCESTALL flag
  // select end point
  UENUM = eptnum;
  // Put endpoint into Halt state
  UECONX |= (1 << STALLRQC);

  // Reset Endpoint Fifos, beware this is a 2 steps operation
  UERST |= (1 << eptnum);
  UERST &= ~(1 << eptnum);
}

/******************************************************************************
Sends STALL packet

Parameters:
  eptnum - Endpoint number.
******************************************************************************/
void halSendStallToHost(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // Put endpoint into Halt state
  UECONX |= (1 << STALLRQ);
}

/******************************************************************************
usb general interrupt handler
******************************************************************************/
ISR(USB_GEN_vect)
{
  uint8_t status;

  // Get interrupt status
  // Some interrupts may get masked depending on the device state
  status = UDINT;
  status &= UDIEN;

  if (deviceState < DEVICE_POWERED)
  {
    status &= ~((1 << WAKEUPI) | (1 << EORSMI));
    UDINT = status;
  }

  // Return immediately if there is no interrupt to service
  if (!status)
    return; // spurious interrupt

  // Suspend
  // This interrupt is always treated last
  if ((1 << SUSPI) & status)
  {
    // Don't do anything if the device is already suspended
    if (DEVICE_SUSPENDED != deviceState)
    {
      // The device enters the Suspended state
      // Enable wake up
      UDIEN = (1 << WAKEUPE) | (1 << EORSME);
      // Acknowledge interrupt
      UDINT &= ~(1 << SUSPI);
      // Switch to the Suspended state
      previousDeviceState = deviceState;
      deviceState = DEVICE_SUSPENDED;
      halDisableUsbClock();
      halInterruptSuspend();
    }
  }
  // Resume
  else if (status & ((1 << WAKEUPI) | (1 << EORSMI)))
  {
    // Don't do anything if the device was not suspended
    if (DEVICE_SUSPENDED == deviceState)
    {
      // The device enters its previous state
      halEnableUsbClock();
      deviceState = previousDeviceState;
    }
    // Clear and disable resume interrupts
    UDINT &= ~((1 << WAKEUPI) | (1 << EORSMI) | (1 << SUSPI));
    UDIEN &= ~((1 << WAKEUPE) | (1 << EORSME));
    halInterruptResume();
  }
  // End of bus reset
  else if (status & (1 << EORSTI))
  {
    // Flush and enable the Suspend interrupt
    UDINT &= ~((1 << WAKEUPI) | (1 << EORSMI) | (1 << SUSPI));
    //UDIEN = (1 << SUSPE);  todo
    halInterruptBusReset();
    // Acknowledge end of bus reset interrupt
    UDINT &= ~(1 << EORSTI);
  }
}

/******************************************************************************
usb endpoints\pipe interrupt handler
******************************************************************************/
ISR(USB_COM_vect)
{
  uint8_t cureptnum = UENUM;
  uint8_t status= UEINT;
  uint8_t eptnum = 0;

  while (status)
  {
    // Check if endpoint has a pending interrupt
    if ((status & (1 << eptnum)))
    {
      // select end point
      UENUM = eptnum;
      endpoints[eptnum].irqReason = UEIENX;
      halDisableEndPointInterrupt();
      halInterruptEndPoints();
      status &= ~(1 << eptnum);
    }
    eptnum++;
  }

  UENUM = cureptnum;
}

// eof halUsb.c
