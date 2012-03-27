/*****************************************************************************
  \file  sipcproto.h

  \brief 

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    26.10.2009 I.Vagulin - Created
******************************************************************************/


#ifndef _SIPCPROTO_H_
#define _SIPCPROTO_H_

/*****************************************************************************
                              Types section
******************************************************************************/
//sipc commands which 3290p can handle.
//every sipc packet must start with one of such.
typedef enum
{
  // Symbols
  SIPC_CMD_ID_LCD_SYMB_RAVEN_ON = 0x00,
  SIPC_CMD_ID_LCD_SYMB_RAVEN_OFF = 0x01,

  SIPC_CMD_ID_LCD_SYMB_BELL_ON = 0x02,
  SIPC_CMD_ID_LCD_SYMB_BELL_OFF = 0x03,

  SIPC_CMD_ID_LCD_SYMB_TONE_ON = 0x04,
  SIPC_CMD_ID_LCD_SYMB_TONE_OFF = 0x05,

  SIPC_CMD_ID_LCD_SYMB_MIC_ON = 0x06,
  SIPC_CMD_ID_LCD_SYMB_MIC_OFF = 0x07,

  SIPC_CMD_ID_LCD_SYMB_SPEAKER_ON = 0x08,
  SIPC_CMD_ID_LCD_SYMB_SPEAKER_OFF = 0x09,

  SIPC_CMD_ID_LCD_SYMB_KEY_ON = 0x0a,
  SIPC_CMD_ID_LCD_SYMB_KEY_OFF = 0x0b,

  SIPC_CMD_ID_LCD_SYMB_ATT_ON = 0x0c,
  SIPC_CMD_ID_LCD_SYMB_ATT_OFF = 0x0d,

  SIPC_CMD_ID_LCD_SYMB_SPACE_SUN = 0x0e,
  SIPC_CMD_ID_LCD_SYMB_SPACE_MOON = 0x0f,
  SIPC_CMD_ID_LCD_SYMB_SPACE_OFF = 0x10,

  SIPC_CMD_ID_LCD_SYMB_CLOCK_AM = 0x11,
  SIPC_CMD_ID_LCD_SYMB_CLOCK_PM = 0x12,
  SIPC_CMD_ID_LCD_SYMB_CLOCK_OFF = 0x13,

  SIPC_CMD_ID_LCD_SYMB_TRX_RX = 0x14,
  SIPC_CMD_ID_LCD_SYMB_TRX_TX = 0x15,
  SIPC_CMD_ID_LCD_SYMB_TRX_OFF = 0x16,

  SIPC_CMD_ID_LCD_SYMB_IP_ON = 0x17,
  SIPC_CMD_ID_LCD_SYMB_IP_OFF = 0x18,

  SIPC_CMD_ID_LCD_SYMB_PAN_ON = 0x19,
  SIPC_CMD_ID_LCD_SYMB_PAN_OFF = 0x1a,

  SIPC_CMD_ID_LCD_SYMB_ZLINK_ON = 0x1b,
  SIPC_CMD_ID_LCD_SYMB_ZLINK_OFF = 0x1c,

  SIPC_CMD_ID_LCD_SYMB_ZIGBEE_ON = 0x1d,
  SIPC_CMD_ID_LCD_SYMB_ZIGBEE_OFF = 0x1e,

  SIPC_CMD_ID_LCD_SYMB_ANTENNA_LEVEL_0 = 0x1f,
  SIPC_CMD_ID_LCD_SYMB_ANTENNA_LEVEL_1 = 0x20,
  SIPC_CMD_ID_LCD_SYMB_ANTENNA_LEVEL_2 = 0x21,
  SIPC_CMD_ID_LCD_SYMB_ANTENNA_OFF = 0x22,

  //SIPC_CMD_ID_LCD_SYMB_BAT // bettery symbol is controlled by ATMega3290...

  SIPC_CMD_ID_LCD_SYMB_ENV_OPEN = 0x23,
  SIPC_CMD_ID_LCD_SYMB_ENV_CLOSE = 0x24,
  SIPC_CMD_ID_LCD_SYMB_ENV_OFF = 0x25,

  SIPC_CMD_ID_LCD_SYMB_TEMP_CELSIUS = 0x26,
  SIPC_CMD_ID_LCD_SYMB_TEMP_FAHRENHEIT = 0x27,
  SIPC_CMD_ID_LCD_SYMB_TEMP_OFF = 0x28,

  SIPC_CMD_ID_LCD_SYMB_MINUS_ON = 0x29,
  SIPC_CMD_ID_LCD_SYMB_MINUS_OFF = 0x2a,

  SIPC_CMD_ID_LCD_SYMB_DOT_ON = 0x2b,
  SIPC_CMD_ID_LCD_SYMB_DOT_OFF = 0x2c,

  SIPC_CMD_ID_LCD_SYMB_COL_ON = 0x2d,
  SIPC_CMD_ID_LCD_SYMB_COL_OFF = 0x2e,

  // Led
  SIPC_CMD_ID_LED_ON = 0x2f,
  SIPC_CMD_ID_LED_TOGGLE = 0x30,
  SIPC_CMD_ID_LED_OFF = 0x31,


  // Commands total number.
  SIPC_CMD_ID_LCD_MAX = 0x32,

  // Masseges
  SIPC_CMD_ID_MSG = 0x33, //Print message function pointer is not saved in the LCD_CMD_LIST.

  //Sensor read commands
  SIPC_CMD_ID_READ_TEMPERATURE = 0x80,
  SIPC_CMD_ID_READ_BATTERY = 0x81,

} SipcCmdId_t;

//type of sipc answers which 3290p can send.
typedef enum
{
  SIPC_ANSWER_ID_TEMPERATURE = 1,
  SIPC_ANSWER_ID_BATTERY = 2,
} SipcAnswerId_t;

#endif /* _SIPCPROTO_H_ */
