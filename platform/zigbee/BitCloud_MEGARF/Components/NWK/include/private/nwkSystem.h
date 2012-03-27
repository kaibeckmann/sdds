/**************************************************************************//**
  \file nwkSystem.h

  \brief Network system header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2007-06-20 V. Panov - Created.
    2009-08-16 M. Gekk  - Refactoring.
   Last change:
    $Id: nwkSystem.h 12570 2010-09-24 20:25:34Z mgekk $
 ******************************************************************************/
#if !defined _NWKSYSTEM_H
#define _NWKSYSTEM_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <mnUtils.h>

 /******************************************************************************
                 Inline static functions prototypes section
 ******************************************************************************/
INLINE bool isCorrectExtPanId(const uint64_t panId)
{
  const uint8_t *p = (const uint8_t *)&panId;
  const uint8_t *const pend = p + sizeof(panId);
  uint16_t sum = 0U;

  do
    sum += *p;
  while (++p < pend);
  return (0U != sum) && ((8U * 0xFFU) != sum);
}

INLINE bool isCorrectExtAddr(const uint8_t *extAddr)
{
  uint8_t i = 0U;

  do
    if (extAddr[i]) return true;
  while (++i < sizeof(uint64_t));
  return false;
}

/******************************************************************************
                                Types section
 ******************************************************************************/
typedef  ShortAddr_t  NwkAddrRange_t;

#if defined __ICCAVR__
  typedef uint8_t NwkBitField_t;
#else
  typedef unsigned int NwkBitField_t;
#endif

/******************************************************************************
                            Definitions section
 ******************************************************************************/
#define MIN(x,y) ((x)<(y)?(x):(y))

/** Converting of time value from milliseconds to seconds.  */
#define NWK_MSEC_TO_SEC(time)  ((time) >> 10)
/** Converting of time value from seconds to milliseconds.  */
#define NWK_SEC_TO_MSEC(time)  ((time) << 10)

#define IS_CORRECT_BROADCAST_ADDR(A) \
  ((0xFFFFU == (A))||((0xFFFBU <= LE16_TO_CPU(A))&&(LE16_TO_CPU(A) <= 0xFFFDU)))

#define NWK_NO_EXT_PANID   0ULL
#define NWK_INVALID_PANID  0xFFFFU
#define NWK_NO_EXT_ADDR    0ULL


#if defined UINT64_MEMCMP
  #define IS_EQ_EXT_ADDR(A, B) (0 == memcmp(&(A), &(B), sizeof(uint64_t)))
  #define IS_EQ_EXT_PANID(A, B) (0 == memcmp(&(A), &(B), sizeof(uint64_t)))
  #define IS_CORRECT_EXT_PANID(P) isCorrectExtPanId(P)
  #define IS_CORRECT_EXT_ADDR(A)  isCorrectExtAddr((const uint8_t *)&A)
  #define COPY_EXT_ADDR(DST, SRC) memcpy(&(DST), &(SRC), sizeof(uint64_t))
  #define COPY_TO_RAW_EXT_ADDR(DST, SRC) memcpy((DST).raw, &(SRC), sizeof(uint64_t))
  #define COPY_FROM_RAW_EXT_ADDR(DST, SRC) memcpy(&(DST), (SRC).raw, sizeof(uint64_t))
  #define COPY_EXT_PANID(DST, SRC) memcpy(&(DST), &(SRC), sizeof(uint64_t))
#else
  #define IS_EQ_EXT_ADDR(A, B) ((A) == (B))
  #define IS_EQ_EXT_PANID(A, B) ((A) == (B))
  #define IS_CORRECT_EXT_PANID(P) ((0ULL < (P)) && ((P) < 0xFFFFFFFFFFFFFFFFULL))
  #define IS_CORRECT_EXT_ADDR(A)  (NWK_NO_EXT_ADDR != (A))
  #define COPY_EXT_ADDR(DST, SRC) (DST) = (SRC)
  #define COPY_TO_RAW_EXT_ADDR(DST, SRC) (DST).value = (SRC)
  #define COPY_FROM_RAW_EXT_ADDR(DST, SRC)  (DST) = (SRC).value
  #define COPY_EXT_PANID(DST, SRC) (DST) = (SRC)
#endif

/* Get address of any NWK table. */
#define NWK_ADDR_OF_TABLE(table)  ((void **)&(table))

#endif /* _NWKSYSTEM_H */
/** eof nwkSystem.h */

