// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief  Implementation of the command interface for the ATmega3290p on AVRRAVEN
 *
 * \par Application note:
 *      AVR2017: RZRAVEN FW
 *
 * \par Documentation
 *      For comprehensive code documentation, supported compilers, compiler
 *      settings and supported devices see readme.html
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Id: cmd_if_3290p.c 41375 2008-05-07 13:35:51Z hmyklebust $
 *
 * Copyright (c) 2008 , Atmel Corporation. All rights reserved.
 *
 * Licensed under Atmel’s Limited License Agreement (RZRaven Evaluation and Starter Kit). 
 *****************************************************************************/

/*================================= INCLUDES         =========================*/
#include <cmd_if_3290p.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#include <compiler.h>
#include <vrt_kernel.h>
#include <vrt_mem.h>
#include <rvn_loc.h>
#include <loc.h>
#include <sipc.h>
#include <sipcproto.h>
#include <extern_sipc_cmd.h>

//! \addtogroup applCmdAVRRAVEN3290p
//! @{
/*========================= MACROS                   =========================*/
//! Length of the SIPC RX buffer.
#define CMD_IF_SIPC_BUFFER_LENGTH (127)

/*========================= TYPEDEFS                 =========================*/

/*========================= PUBLIC FUNCTION PROTOTYPES =======================*/

/*========================= PRIVATE VARIABLES        =========================*/
//! Flag holding module initialization status
static bool cmd_if_initialized = false;

//! Static buffer for use with "sipc" 
static uint8_t sipc_rx_buffer[CMD_IF_SIPC_BUFFER_LENGTH];

void loc_evt_bitcloud(void *evt);

/*========================= PRIVATE FUNCTIONS            =====================*/

/*! \brief  Function for handling new sipc packets
 *
 *          When a new packet has been successfully trasfered over the sipc interface,
 *          this function is called with a pointer to the newly arrived package.
 *          The package is identified by the first byte, and if the identifier is known
 *          an event is posted with the correct handler.
 */
static void cmd_if_sipc_packet_handler(void *packet);

/*========================= IMPLEMENTATION           =========================*/
bool cmd_if_init(void)
{
  if (true == sipc_init(CMD_IF_SIPC_BUFFER_LENGTH, sipc_rx_buffer, cmd_if_sipc_packet_handler)) 
    cmd_if_initialized = true;

  return cmd_if_initialized;
}

void cmd_if_deinit(void)
{
  cmd_if_initialized = false;
  sipc_deinit();
}

static void cmd_if_sipc_packet_handler(void *packet)
{
  vrt_post_event(loc_evt_bitcloud, packet);
}

void loc_evt_bitcloud(void *evt)
{
  rvn_loc_evt_bitcloud_t *extCmd = evt;

  if (extCmd->cmdId < SIPC_CMD_ID_LCD_MAX)
    lcd_func_ptrs[extCmd->cmdId].func();
  else if (SIPC_CMD_ID_MSG == extCmd->cmdId)
    lcd_print_msg(extCmd->pld);
  else if (SIPC_CMD_ID_READ_TEMPERATURE == extCmd->cmdId)
    cmd_queue_read(SIPC_ANSWER_ID_TEMPERATURE);
  else if (SIPC_CMD_ID_READ_BATTERY  == extCmd->cmdId)
    cmd_queue_read(SIPC_ANSWER_ID_BATTERY);
  SIPC_ACK_PACKET();
}

//! @}
/*EOF*/
