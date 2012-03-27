/***************************************************************************//**
  \file genericEcc.h

  \brief    
    Generic ECC API

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    08.07.10 D. Loskutnikov - Created.
*******************************************************************************/
#ifndef _GENERICECC_H
#define _GENERICECC_H

/*******************************************************************************
                              Defines section
*******************************************************************************/
#define SECT163K1_COMPRESSED_PUBLIC_KEY_SIZE (22)
#define SECT163K1_UNCOMPRESSED_PUBLIC_KEY_SIZE (43)
#define SECT163K1_PRIVATE_KEY_SIZE (21)
#define SECT163K1_CERTIFICATE_SIZE (48)
#define SECT163K1_SHARED_SECRET_SIZE (21)
#define SECT163K1_POINT_ORDER_SIZE (21)
#define AES_MMO_HASH_SIZE (16)

#define MCE_SUCCESS                0x00
#define MCE_ERR_FAIL_VERIFY        0x01
#define MCE_ERR_NULL_PRIVATE_KEY   0x02
#define MCE_ERR_NULL_PUBLIC_KEY    0x03
#define MCE_ERR_NULL_INPUT_BUF     0x04
#define MCE_ERR_NULL_OUTPUT_BUF    0x05
#define MCE_ERR_NULL_FUNC_PTR      0x06
#define MCE_ERR_NULL_EPHEM_PRI_KEY 0x07
#define MCE_ERR_NULL_EPHEM_PUB_KEY 0x08
#define MCE_ERR_BAD_INPUT          0x09

/*******************************************************************************
                   Prototypes section
*******************************************************************************/
typedef int GetRandomDataFunc(unsigned char *buffer, unsigned long sz);
typedef int HashFunc(unsigned char *digest, unsigned long sz, unsigned char *data);
typedef int YieldFunc(void);
int aesMmoHash(unsigned char *digest, unsigned long sz, unsigned char *data);

int ZSE_ECDSASign(unsigned char *privateKey, 
                  unsigned char *msgDigest,
                  GetRandomDataFunc *GetRandomData, 
                  unsigned char *r, 
                  unsigned char *s,
                  YieldFunc *yield, 
                  unsigned long yieldLevel);

int ZSE_ECDSAVerify(unsigned char *publicKey, 
                    unsigned char *msgDigest, 
                    unsigned char *r, 
                    unsigned char *s, 
                    YieldFunc *yield, 
                    unsigned long yieldLevel);

int ZSE_ECCGenerateKey(unsigned char *privateKey, 
                       unsigned char *publicKey,
                       GetRandomDataFunc *GetRandomData, 
                       YieldFunc *yield, 
                       unsigned long yieldLevel);

int ZSE_ECCKeyBitGenerate(unsigned char *privateKey, 
                          unsigned char *ephemeralPrivateKey, 
                          unsigned char *ephemeralPublicKey, 
                          unsigned char *remoteCertificate, 
                          unsigned char *remoteEphemeralPublicKey, 
                          unsigned char *caPublicKey, 
                          unsigned char *keyBits, 
                          HashFunc *Hash, 
                          YieldFunc *yield, 
                          unsigned long yieldLevel);

int ZSE_ECQVReconstructPublicKey(unsigned char* certificate,
                                 unsigned char* caPublicKey,
                                 unsigned char* publicKey,
                                 HashFunc *Hash, 
                                 YieldFunc *yield, 
                                 unsigned long yieldLevel);
#endif //_GENERICECC_H
// eof genericEcc.h
