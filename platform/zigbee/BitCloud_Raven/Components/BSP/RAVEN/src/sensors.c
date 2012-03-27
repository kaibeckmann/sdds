/*****************************************************************************
  \file  sensors.c

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

#include <sensors.h>
#include <appTimer.h>
#include "sipc.h"
#include "sipcproto.h"

/*****************************************************************************
                              Definitions section
******************************************************************************/
#define WAIT_ASNWER_TIMEOUT 500

/*****************************************************************************
                              Types section
******************************************************************************/
typedef enum
{
  SENSOR_OPENED_FLAG_TEMPERATURE = (1<<0),
  SENSOR_OPENED_FLAG_BATTERY = (1<<1),
} SensorOpenedFlag_t ;

/****************************************************************************
                              Static functions prototypes section
******************************************************************************/
static void sipcInd(SipcAnswerId_t id, uint8_t *bytes);
static void answerTimeoutFired(void);

/*****************************************************************************
                              Global variables section
******************************************************************************/
static SipcInd_t sensorSipcListener =
{
  .sipcInd = sipcInd,
};
static BspTemperatureCb_t temperatureCallback = NULL;
static BspBatteryCb_t batteryCallback = NULL;
static SensorOpenedFlag_t sensorOpenState = 0;
static HAL_AppTimer_t answerTimeoutTimer =
{
  .interval = WAIT_ASNWER_TIMEOUT,
  .mode = TIMER_ONE_SHOT_MODE,
  .callback = answerTimeoutFired,
};


/*****************************************************************************
                              Implementation section
******************************************************************************/
/***********************************************************************************
  Description: Sipc frame receiving callback.
  Parameters: answer id, frame contents.
  Return: none
 ***********************************************************************************/
static void sipcInd(SipcAnswerId_t id, uint8_t *bytes)
{
  switch(id)
  {
    case SIPC_ANSWER_ID_TEMPERATURE:
      if (temperatureCallback)
      {
        HAL_StopAppTimer(&answerTimeoutTimer);
        temperatureCallback(true, *(int16_t*)bytes);
        temperatureCallback = NULL;
      }
      break;
    case SIPC_ANSWER_ID_BATTERY:
      if (batteryCallback)
      {
        HAL_StopAppTimer(&answerTimeoutTimer);
        batteryCallback( *(int16_t*) bytes);
        batteryCallback = NULL;
      }
      break;
  }
}

/***********************************************************************************
  Description: Sipc frame receiving callback.
  Parameters: answer id, frame contents.
  Return: none
 ***********************************************************************************/
static void answerTimeoutFired(void)
{
  if (temperatureCallback)
  {
    temperatureCallback(false, 0);
    temperatureCallback = NULL;
  }
  if (batteryCallback)
  {
    batteryCallback(0);
    batteryCallback = NULL;
  }
}

/***********************************************************************************
  Description: Sipc open function, proper handling more than one sensor.
  Parameters: Sensor id.
  Return: none
 ***********************************************************************************/
static result_t openSipc(SensorOpenedFlag_t bit)
{
  if (sensorOpenState & bit)
    return BC_FAIL;

  if (0 == sensorOpenState)
    bspSipcOpen(&sensorSipcListener);
  else
    bspSipcOpen(NULL);

  sensorOpenState |= bit;
  return BC_SUCCESS;
}

/***********************************************************************************
  Description: Sipc close function, proper handling of more than one sensor.
  Parameters: Sensor id.
  Return: none
 ***********************************************************************************/
static result_t closeSipc(SensorOpenedFlag_t bit)
{
  if (0 == (sensorOpenState & bit))
    return BC_FAIL;

  sensorOpenState &= ~bit;
  if (0 == sensorOpenState)
    bspSipcClose(&sensorSipcListener);
  else
    bspSipcClose(NULL);
  return BC_SUCCESS;
}

/***************************************************************************//**
\brief Opens temperature sensor.
\return
  BC_FAIL - sensor has been already open. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenTemperatureSensor(void)
{
  return openSipc(SENSOR_OPENED_FLAG_TEMPERATURE);
}

/***************************************************************************//**
\brief Closes the temperature sensor.
\return
  BC_FAIL - if a hardware error has occured or
            there is uncompleted ReadData request. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_CloseTemperatureSensor(void)
{
  return closeSipc(SENSOR_OPENED_FLAG_TEMPERATURE);
}

/**************************************************************************//**
\brief Reads data from the temperature sensor.
\param[in]
    f - callback.
    result - the result of the requested operation.
             true - operation finished successfully, false - some error has
             occured.
    data - sensor data.
\return
  BC_FAIL - previous request was not completed. \n
  BC_SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadTemperatureData(BspTemperatureCb_t cb)
{
  if (temperatureCallback)
    return BC_FAIL;

  uint8_t cmd = SIPC_CMD_ID_READ_TEMPERATURE;
  temperatureCallback = cb;
  bspSipcSendFrame(&cmd, 1);
  HAL_StartAppTimer(&answerTimeoutTimer);
  return BC_SUCCESS;
}

/***************************************************************************//**
\brief Opens the battery sensor.
\return
  BC_FAIL - sensor has been already open. \n
  BC_SUCCESS - otherwise.
*******************************************************************************/
result_t BSP_OpenBatterySensor(void)
{
  return openSipc(SENSOR_OPENED_FLAG_BATTERY);
}

/***************************************************************************//**
\brief Closes the battery sensor.
\return
  BC_FAIL - sensor was not opened. \n
  BC_SUCCESS  - otherwise.
*******************************************************************************/
result_t BSP_CloseBatterySensor(void)
{
  return closeSipc(SENSOR_OPENED_FLAG_BATTERY);
}

/**************************************************************************//**
\brief Reads data from battery sensor.
\param[in]
    callback - callback function.
    data - sensor data.
    Can use (4ul * data * 125ul * 3ul) / (1024ul * 100ul) formula to count \n
    battery data in Volts (for avr).
\return
  BC_FAIL - previous request was not completed, or sensor was not opened. \n
  BC_SUCCESS - otherwise.
******************************************************************************/
result_t BSP_ReadBatteryData(BspBatteryCb_t cb)
{
  if (batteryCallback)
    return BC_FAIL;

  uint8_t cmd = SIPC_CMD_ID_READ_BATTERY;
  batteryCallback = cb;
  bspSipcSendFrame(&cmd, 1);
  HAL_StartAppTimer(&answerTimeoutTimer);
  return BC_SUCCESS;
}
