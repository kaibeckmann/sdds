/***************************************************************************//**
  \file halUsb.h

  \brief Declarations of usb hardware-dependent module.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    17/07/08 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALUSB_H
#define _HALUSB_H

/******************************************************************************
                        Includes section.
******************************************************************************/
#include <halClkCtrl.h>
#include <halTaskManager.h>
#include <usb.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
// Returns the maximum packet size of the given endpoint.
#define UDP_ENDPOINTS_MAXPACKETSIZE(i)    ((i == 1) ? 256 : 64)
// Returns the number of FIFO banks for the given endpoint.
#define UDP_ENDPOINTS_BANKS(i)            ((i == 0) ? 1 : 2)
// Number of UDP endpoints
#define USB_END_POINTS_NUMBER  7

// USB device states
// The device is currently suspended
#define DEVICE_SUSPENDED            0
// USB cable is plugged into the device
#define DEVICE_ATTACHED             1
// Host is providing +5V through the USB cable
#define DEVICE_POWERED              2
// Device has been reset
#define DEVICE_DEFAULT              3
// Device has address, but wait for zlp end
#define DEVICE_PREADDRESSED         4
// The device has been given an address on the bus
#define DEVICE_ADDRESS              5
// A valid configuration has been selected
#define DEVICE_CONFIGURED           6

// Endpoint states
// Endpoint is disabled
#define UDP_ENDPOINT_DISABLED       0
// Endpoint is halted (i.e. STALLs every request)
#define UDP_ENDPOINT_HALTED         1
// Endpoint is idle (i.e. ready for transmission)
#define UDP_ENDPOINT_IDLE           2
// Endpoint is sending data
#define UDP_ENDPOINT_SENDING        3
// Endpoint is receiving data
#define UDP_ENDPOINT_RECEIVING      4

/******************************************************************************
                   Types section
******************************************************************************/
typedef enum
{
  USB_END_POINT_0 = 0,
  USB_END_POINT_1 = 1,
  USB_END_POINT_2 = 2,
  USB_END_POINT_3 = 3,
  USB_END_POINT_4 = 4,
  USB_END_POINT_5 = 5,
  USB_END_POINT_6 = 6
} HAL_EndPoints_t;

// Type of USB endpoints
typedef enum
{
  EP_CONTROL     = 0,
  EP_ISOCHRONOUS = 1,
  EP_BULK        = 2,
  EP_INTERRUPT   = 3
} HAL_UsbEndPointType_t;

// Direction of transaction
typedef enum
{
  EP_OUT = 0,
  EP_IN  = 1
} HAL_UsbEndPointDirect_t;

/* Describes an ongoing transfer on a UDP endpoint. */
typedef struct
{
  uint8_t *data;               // data - Pointer to a data buffer used for emission/reception
  uint32_t buffered;           // buffered - Number of bytes which have been written into the UDP internal FIFO buffers
  uint32_t transferred;        // transferred - Number of bytes which have been sent/received
  uint32_t remaining;          // remaining - Number of bytes which have not been buffered/transferred yet
  TransferCallback_t callback; // callback - Optional callback to invoke when the transfer completes
  void *argument;              // argument - Optional argument to the callback function
} UsbTransfer_t;

/* Describes the state of an endpoint of the UDP controller. */
typedef struct
{
  uint8_t state;          // Current endpoint state
  uint8_t irqReason;      // irq reason (Tx, Rx, Control, Stall)
  uint16_t size;          // size - Maximum packet size for the endpoint
  UsbTransfer_t transfer; // transfer - Describes an ongoing transfer (if current state is either <UDP_ENDPOINT_SENDING> or <UDP_ENDPOINT_RECEIVING>)
} UsbEndpoint_t;

/******************************************************************************
                   Inline static functions section
******************************************************************************/
/******************************************************************************
 Interrupt handler signal implementation
******************************************************************************/
INLINE void halInterruptEndPoints(void)
{
  halPostTask3(HAL_USB_ENDPOINTS);
}

/******************************************************************************
 Interrupt handler signal implementation
******************************************************************************/
INLINE void halInterruptSuspend(void)
{
  halPostTask3(HAL_USB_SUSPEND);
}

/******************************************************************************
 Interrupt handler signal implementation
******************************************************************************/
INLINE void halInterruptResume(void)
{
  halPostTask3(HAL_USB_RESUME);
}

/******************************************************************************
 Interrupt handler signal implementation
******************************************************************************/
INLINE void halInterruptBusReset(void)
{
  halPostTask4(HAL_USB_BUS_RESET);
}

/******************************************************************************
 Enables clock on usb
*******************************************************************************/
INLINE void halEnableUsbClock(void)
{
  USBCON &= ~(1 << FRZCLK);
}

/******************************************************************************
 Disables clock on usb
*******************************************************************************/
INLINE void halDisableUsbClock(void)
{
  USBCON |= (1 << FRZCLK);
}

/******************************************************************************
 Enables Rx end point interrupt
*******************************************************************************/
INLINE void halEnableEndPointRxInterrupt(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // enable all interrupts for that end point
  UEIENX |= (1 << RXOUTE);
}

/******************************************************************************
 Enables Tx end point interrupt
*******************************************************************************/
INLINE void halEnableEndPointTxInterrupt(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // enable all interrupts for that end point
  UEIENX |= (1 << TXINE);
}

/******************************************************************************
 Enables Setup end point interrupt
*******************************************************************************/
INLINE void halEnableEndPointSetupInterrupt(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // enable all interrupts for that end point
  UEIENX = (1 << RXSTPE);
}

/******************************************************************************
 Enables Stall end point interrupt
*******************************************************************************/
INLINE void halEnableEndPointStallInterrupt(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // enable all interrupts for that end point
  UEIENX = (1 << STALLEDE);
}

/******************************************************************************
 Nak In end point interrupt
*******************************************************************************/
INLINE void halEnableEndPointNakinInterrupt(uint8_t eptnum)
{
  // select end point
  UENUM = eptnum;
  // enable all interrupts for that end point
  UEIENX = (1 << NAKINE);
}

/******************************************************************************
 Enables end point interrupt
*******************************************************************************/
INLINE void halDisableEndPointInterrupt(void)
{
  // disable all interrupts for that end point
  UEIENX = 0;
}

/******************************************************************************
Sets the device address to the given value.

Parameters:
  address - New device address.
******************************************************************************/
INLINE void halSetUsbAddress(uint8_t address)
{
  // Set address
  UDADDR = address;
}

/******************************************************************************
                   Prototypes section
******************************************************************************/
/******************************************************************************
tuning and setting AIC for UDP
******************************************************************************/
void halUsbInterrupt(void);

/******************************************************************************
Handles a completed transfer on the given endpoint, invoking the configured
callback if any.

Parameters:
  eptnum - Number of the endpoint for which the transfer has completed.
  status - Result of the USB transfer.
******************************************************************************/
void halEndOfTransfer(uint8_t eptnum, uint8_t status);

/******************************************************************************
Clears the correct reception flag (bank 0 or bank 1) of an endpoint.

Parameters:
  eptnum - Number of endpoint.
******************************************************************************/
void halClearRxFlag(uint8_t eptnum);

/******************************************************************************
Writes a data payload into the current FIFO buffer of the UDP.

Parameters:
  eptnum - Number of the endpoint which is sending data.
******************************************************************************/
void halWritePayload(uint8_t eptnum);

/******************************************************************************
Reads a data payload from the current FIFO buffer of an endpoint.

Parameters:
  eptnum - Endpoint number.
  size - Size of the data to read.
******************************************************************************/
void halReadPayload(uint8_t eptnum, uint16_t size);

/******************************************************************************
Reads a SETUP request from the FIFO buffer of Control endpoint and stores it
into the global request variable.

Parameters:
  request - global variable for request reading
******************************************************************************/
void halReadRequest(uint8_t *request);

/******************************************************************************
Resets all the endpoints of the UDP peripheral.
******************************************************************************/
void halResetEndpoints(void);

/******************************************************************************
Disables all endpoints of the UDP peripheral except control endpoint 0.
******************************************************************************/
void halDisableEndpoints(void);

/******************************************************************************
Checks if an ongoing transfer on an endpoint has been completed.

Parameters:
 eptnum - Endpoint number.

Returns:
  1 - if the current transfer on the given endpoint is complete;
  0 - otherwise
******************************************************************************/
uint8_t halIsTransferFinished(uint8_t eptnum);

/******************************************************************************
Common end points interrupt handler
******************************************************************************/
void halCommonEndpointHandler(void);

/******************************************************************************
Sets UDP endpoint parameters

Parameters:
   eptnum - endpoint number
   type - endpoint type
   direction - transaction direction
******************************************************************************/
void halConfigureEndpoint(uint8_t eptnum, uint8_t type, HAL_UsbEndPointDirect_t direction);

/******************************************************************************
Loads data to current FIFO and starts sending

Parameters:
  eptnum - Endpoint number.
  remaining - data remaining
******************************************************************************/
void halStartUsbWrite(uint8_t eptnum, uint32_t remaining);

/******************************************************************************
Sets the HALT feature on the given endpoint.

Parameters:
  eptnum - Endpoint number.
******************************************************************************/
void halEndpointHaltState(uint8_t eptnum);

/******************************************************************************
Clears the Halt feature on the given endpoint.

Parameters:
  eptnum - Endpoint number.
******************************************************************************/
void halEndpointUnHaltState(uint8_t eptnum);

/******************************************************************************
Sends STALL packet

Parameters:
  eptnum - Endpoint number.
******************************************************************************/
void halSendStallToHost(uint8_t eptnum);

/******************************************************************************
Starts a remote wake-up procedure.
******************************************************************************/
//void HAL_RemoteWakeUp(void)

/******************************************************************************
End of bus reset state handler
******************************************************************************/
void halEndOfBusResetHandler(void);

/******************************************************************************
configure and enable usb role
******************************************************************************/
void halInitUsbDevice(void);

#endif /* _HALUSB_H */
