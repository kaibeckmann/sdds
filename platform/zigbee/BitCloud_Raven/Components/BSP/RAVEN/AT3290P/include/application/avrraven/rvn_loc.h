// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief  Commands, responses and events for local AVR Raven transactions
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
 * $Id: rvn_loc.h 41436 2008-05-09 00:02:43Z hmyklebust $
 *
 * Copyright (c) 2008 , Atmel Corporation. All rights reserved.
 *
 * Licensed under Atmel’s Limited License Agreement (RZRaven Evaluation and Starter Kit). 
 *****************************************************************************/
#ifndef __RVN_LOC_H__
#define __RVN_LOC_H__

/*========================= INCLUDES                 =========================*/

/*========================= CONSTANT DEFINES         =========================*/

/*========================= MACROS DEFINES           =========================*/

/*========================= TYPEDEFS                 =========================*/
/*! \brief RF controller input command descriptor.
 */
typedef struct 
{
  uint8_t cmdId;
  char pld[];
} rvn_loc_evt_bitcloud_t;

/*========================= PUBLIC VARIABLES         =========================*/

/*========================= PUBLIC FUNCTIONS         =========================*/


#endif // __RVN_LOC_H__

/*EOF*/
