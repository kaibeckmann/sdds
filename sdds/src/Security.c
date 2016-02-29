#include "sDDS.h"
#include "os-ssal/aes-128.h"
#ifdef FEATURE_SDDS_SECURITY_ENABLED

static MessageIdentity msgid;

#ifdef SDDS_SECURITY_KDC
static HandshakeHandle g_handles[SDDS_SECURITY_HANDSHAKE_MAX];
#else  
static HandshakeHandle g_handle;
#endif    

rc_t 
Security_init() {

  DDS_ReturnCode_t r;  

#ifdef SDDS_SECURITY_KDC
  r = Security_kdc();    
#else  
  while((r = Security_auth()) != 0);
#endif    

  return r;
}

#ifndef SDDS_SECURITY_KDC 
rc_t 
Security_auth() {

  DDS_S_Result_t res = VALIDATION_FAILED;
  DDS_ReturnCode_t r;  
  SecurityException ex;
  HandshakeMessageToken msg_tok_out;
  HandshakeMessageToken msg_tok_in;
  DDS_ParticipantStatelessMessage msg;
  DDS_ParticipantStatelessMessage *msg_ptr = &msg;
  DDS_SampleInfo info;
  int j;
  
  res = DDS_Security_Authentication_begin_handshake_request(
    &g_handle,
    &msg_tok_out, 
    &msg_tok_in, 
    NULL, 
    NULL, 
    &ex 
  );


  while(1) {

    switch(res) {

      case VALIDATION_OK:
        printf("VALIDATION_OK\n");        
        return SDDS_RT_OK;
      break;

      case VALIDATION_FAILED:
        printf("VALIDATION_FAILED\n");        
      break;

      case VALIDATION_PENDING_HANDSHAKE_MESSAGE:      
        // send token
        msg.msgid = msgid++;
        msg.key = BuiltinTopic_participantID;
        strcpy((char *) msg.message_class_id, GMCLASSID_SECURITY_AUTH_HANDSHAKE);  
        
        msg.message_data = msg_tok_out;
        r = DDS_ParticipantStatelessMessageDataWriter_write(g_ParticipantStatelessMessage_writer,
                                                            &msg,
                                                            NULL);  
        if(r == DDS_RETCODE_OK) {
          printf("sent token\n");
        } else {
          printf("failed to send token\n");
          res = VALIDATION_FAILED;
          break;
        }
        
        // wait for a reply from kdc
        for(j = 0; j < 3; j++) {
          Thread_sleep(NULL, SDDS_SECURITY_RECEIVE_SLEEP_SEC);
          r = DDS_ParticipantStatelessMessageDataReader_take_next_sample(
                                                           g_ParticipantStatelessMessage_reader,
                                                           &msg_ptr,
                                                           &info);
          if(r == DDS_RETCODE_OK && msg.key == BuiltinTopic_participantID) {
            printf("received reply from kdc\n");
            msg_tok_in = msg.message_data;
            res = process_handshake(
	            &msg_tok_out,
	            &msg_tok_in,
	            &g_handle,
	            &ex
            );
            break;
          }
         
          continue;
                          
        }
      break;

      case VALIDATION_OK_FINAL_MESSAGE:
        // send final token
        msg.msgid = msgid++;
        msg.key = BuiltinTopic_participantID;
        strcpy((char *) msg.message_class_id, GMCLASSID_SECURITY_AUTH_HANDSHAKE);  
        
        msg.message_data = msg_tok_out;
        r = DDS_ParticipantStatelessMessageDataWriter_write(g_ParticipantStatelessMessage_writer,
                                                            &msg,
                                                            NULL);  
        if(r == DDS_RETCODE_OK) {
          printf("sent final token\n");
          res = VALIDATION_OK;
        } else {
          printf("failed to send final token\n");
          res = VALIDATION_FAILED;
        }
      break;

    }
  }

  return res;

}

#else 

rc_t 
Security_kdc() {

  DDS_S_Result_t res = VALIDATION_FAILED;
  DDS_ReturnCode_t r;  
  SecurityException ex;
  HandshakeHandle *handle;  
  HandshakeMessageToken msg_tok_out;
  HandshakeMessageToken msg_tok_in;
  DDS_ParticipantStatelessMessage msg;
  DDS_ParticipantStatelessMessage *msg_ptr = &msg;
  DDS_SampleInfo info;

  while(1) {
 
    Thread_sleep(NULL, SDDS_SECURITY_RECEIVE_SLEEP_SEC);
    r = DDS_ParticipantStatelessMessageDataReader_take_next_sample(
                                 g_ParticipantStatelessMessage_reader,
                                 &msg_ptr,
                                 &info);

    if(r != DDS_RETCODE_OK) {
      continue;
    }    

    msg_tok_in = msg.message_data;
        
    if(strcmp(msg.message_data.class_id, SDDS_SECURITY_CLASS_AUTH_REQ) == 0) {
      printf("request from node\n");

      res = DDS_Security_Authentication_begin_handshake_reply(
        handle,
        &msg_tok_out, 
        &msg_tok_in, 
        &msg.key, 
        NULL, 
        &ex 
      );

      switch(res) {

        case VALIDATION_OK:
          printf("VALIDATION_OK");
        break;

        case VALIDATION_FAILED:
          printf("VALIDATION_FAILED");
          Security_cleanup_handshake_handle(handle);
        break;

        case VALIDATION_PENDING_HANDSHAKE_MESSAGE: 
          // send reply token
          msg.msgid = msgid++;
          strcpy((char *) msg.message_class_id, GMCLASSID_SECURITY_AUTH_HANDSHAKE);  
          msg.message_data = msg_tok_out;
          r = DDS_ParticipantStatelessMessageDataWriter_write(g_ParticipantStatelessMessage_writer,
                                                              &msg,
                                                              NULL);  
          if(r == DDS_RETCODE_OK) {
            printf("sent reply token\n");
          } else {
            printf("failed to send reply\n");
            Security_cleanup_handshake_handle(handle);
          }
        break;  

        case VALIDATION_OK_FINAL_MESSAGE:
          // send final token
          msg.msgid = msgid++;
          strcpy((char *) msg.message_class_id, GMCLASSID_SECURITY_AUTH_HANDSHAKE);            
          msg.message_data = msg_tok_out;
          r = DDS_ParticipantStatelessMessageDataWriter_write(g_ParticipantStatelessMessage_writer,
                                                              &msg,
                                                              NULL);  
          if(r == DDS_RETCODE_OK) {
            printf("sent final token\n");
          } else {
            printf("failed to send final token\n");
            Security_cleanup_handshake_handle(handle);
          }
        break;
      }

    } else if(strcmp(msg.message_data.class_id, SDDS_SECURITY_CLASS_AUTH_REP) == 0) {
      printf("reply from node\n");
      
      if((handle = Security_get_handshake_handle(&msg.key)) == NULL) {
        printf("can't get handle\n");
        continue;
      }
      
      res = process_handshake(
        &msg_tok_out,
        &msg_tok_in,
        handle,
        &ex
      );

      switch(res) {

        case VALIDATION_OK:
          printf("VALIDATION_OK");
        break;

        case VALIDATION_FAILED:
          printf("VALIDATION_FAILED");
          Security_cleanup_handshake_handle(handle);
        break;

        case VALIDATION_PENDING_HANDSHAKE_MESSAGE: 
          // send reply token
          msg.msgid = msgid++;
          strcpy((char *) msg.message_class_id, GMCLASSID_SECURITY_AUTH_HANDSHAKE);  
          msg.message_data = msg_tok_out;
          r = DDS_ParticipantStatelessMessageDataWriter_write(g_ParticipantStatelessMessage_writer,
                                                              &msg,
                                                              NULL);  
          if(r == DDS_RETCODE_OK) {
            printf("sent reply token\n");
          } else {
            printf("failed to send reply\n");
            Security_cleanup_handshake_handle(handle);
          }
        break;  

        case VALIDATION_OK_FINAL_MESSAGE:
          // send final token
          msg.msgid = msgid++;
          strcpy((char *) msg.message_class_id, GMCLASSID_SECURITY_AUTH_HANDSHAKE);            
          msg.message_data = msg_tok_out;
          r = DDS_ParticipantStatelessMessageDataWriter_write(g_ParticipantStatelessMessage_writer,
                                                              &msg,
                                                              NULL);  
          if(r == DDS_RETCODE_OK) {
            printf("sent final token\n");
          } else {
            printf("failed to send final token\n");
            Security_cleanup_handshake_handle(handle);
          }
        break;
      }

    } else {
      continue;
    }

  }


  return SDDS_RT_OK;

}
#endif

DDS_S_Result_t 
DDS_Security_Authentication_begin_handshake_request(
	HandshakeHandle *handshake_handle, /* inout (fixed length) */
	HandshakeMessageToken *handshake_message_out, /* in (variable length) */
	HandshakeMessageToken *handshake_message_in, /* in (variable length) */
	IdentityHandle *initiator_identity_handle, /* in (fixed length) */
	IdentityHandle *replier_identity_handle, /* in (fixed length) */
	SecurityException *ex /* inout (variable length) */
) {

  memset(handshake_handle, 0, sizeof(HandshakeHandle));
  handshake_handle->state = SDDS_SECURITY_HANDSHAKE_STATE_CERT;

  // start with certificate
  strcpy(handshake_message_out->class_id, SDDS_SECURITY_CLASS_AUTH_REQ);
  handshake_message_out->props[0] = (Property) {SDDS_SECURITY_PROP_ID, SDDS_SECURITY_USER_ID}; 
  handshake_message_out->props[1] = (Property) {SDDS_SECURITY_PROP_PUB_KEY_X, SDDS_SECURITY_USER_PUBLIC_KEY_X}; 
  handshake_message_out->props[2] = (Property) {SDDS_SECURITY_PROP_PUB_KEY_Y, SDDS_SECURITY_USER_PUBLIC_KEY_Y}; 

  return VALIDATION_PENDING_HANDSHAKE_MESSAGE;

}

#ifdef SDDS_SECURITY_KDC
DDS_S_Result_t DDS_Security_Authentication_begin_handshake_reply(
	HandshakeHandle *handshake_handle, /* inout (fixed length) */
	HandshakeMessageToken *handshake_message_out, /* inout (variable length) */
	HandshakeMessageToken *handshake_message_in, /* in (variable length) */
	IdentityHandle *initiator_identity_handle, /* in (fixed length) */
	IdentityHandle *replier_identity_handle, /* in (fixed length) */
	SecurityException *ex /* inout (variable length) */
) {

  handshake_handle = Security_get_handshake_handle(initiator_identity_handle);

  if(handshake_handle == NULL) {
    return VALIDATION_FAILED;
  }

  // fetch remote id and public key from handshake_message_in
  strncpy(handshake_handle->info.uid, handshake_message_in->props[0].value, CLASS_ID_STRLEN);
  Security_get_bytes(handshake_handle->info.public_key.x, handshake_message_in->props[1].value);
  Security_get_bytes(handshake_handle->info.public_key.y, handshake_message_in->props[2].value);

  // start with certificate
  strcpy(handshake_message_out->class_id, SDDS_SECURITY_CLASS_AUTH_REP);
  handshake_message_out->props[0] = (Property) {SDDS_SECURITY_PROP_ID, SDDS_SECURITY_USER_ID}; 
  handshake_message_out->props[1] = (Property) {SDDS_SECURITY_PROP_PUB_KEY_X, SDDS_SECURITY_USER_PUBLIC_KEY_X}; 
  handshake_message_out->props[2] = (Property) {SDDS_SECURITY_PROP_PUB_KEY_Y, SDDS_SECURITY_USER_PUBLIC_KEY_Y}; 

  return VALIDATION_PENDING_HANDSHAKE_MESSAGE;

}
#endif

DDS_S_Result_t 
process_handshake(
	HandshakeMessageToken *handshake_message_out,
	HandshakeMessageToken *handshake_message_in,
	HandshakeHandle *handshake_handle,
	SecurityException *ex
) {
  
  DDS_S_Result_t res = VALIDATION_FAILED;

  switch (handshake_handle->state) {

    case SDDS_SECURITY_HANDSHAKE_STATE_CERT:
      res = VALIDATION_PENDING_HANDSHAKE_MESSAGE;
#ifdef SDDS_SECURITY_KDC
      // fetch remote signature and nonce from handshake_message_in
      Security_get_bytes(handshake_handle->info.signature_r, handshake_message_in->props[0].value);
      Security_get_bytes(handshake_handle->info.signature_s, handshake_message_in->props[1].value);
      Security_get_bytes(handshake_handle->info.remote_nonce, handshake_message_in->props[2].value);
      
      char str[NUM_ECC_DIGITS * 2 + 1];
      Security_get_string(str, handshake_handle->info.public_key.x);

      printf("uid: %s\n", handshake_handle->info.uid);
      printf("public key: %s\n", str);

/*
    	char cert[4 + 4 + 1 + NUM_ECC_DIGITS*2 + 1 + NUM_ECC_DIGITS*2 + 1];
  		sprintf(cert, "%s,%s,%s", 
              handshake_handle->info.uid, 
              handshake_handle->info.public_key.x, 
              handshake_handle->info.public_key.y);

      printf("cert: %s\n", cert);

      EccPoint ca_publicKey;
*/

/* ecdsa_verify() function.
Verify an ECDSA signature.

Usage: Compute the hash of the signed data using the same hash as the signer and
pass it to this function along with the signer's public key and the signature values (r and s).

Inputs:
    p_publicKey - The signer's public key
    p_hash      - The hash of the signed data.
    r, s        - The signature values.

Returns 1 if the signature is valid, 0 if it is invalid.
*/
//int ecdsa_verify(EccPoint *p_publicKey, uint8_t p_hash[NUM_ECC_DIGITS], uint8_t r[NUM_ECC_DIGITS], uint8_t s[NUM_ECC_DIGITS]);

#else
      // fetch remote id and public key from handshake_message_in
      strncpy(handshake_handle->info.uid, handshake_message_in->props[0].value, CLASS_ID_STRLEN);
      Security_get_bytes(handshake_handle->info.public_key.x, handshake_message_in->props[1].value);
      Security_get_bytes(handshake_handle->info.public_key.y, handshake_message_in->props[2].value);
#endif
      // set up token to send (signature and nonce) to handshake_message_out
      getRandomBytes(handshake_handle->info.nonce, sizeof(handshake_handle->info.nonce));
      strcpy(handshake_message_out->class_id, SDDS_SECURITY_CLASS_AUTH_REP);
      handshake_message_out->props[0] = (Property) {SDDS_SECURITY_PROP_SIG_R, SDDS_SECURITY_USER_CERT_SIG_R}; 
      handshake_message_out->props[1] = (Property) {SDDS_SECURITY_PROP_SIG_S, SDDS_SECURITY_USER_CERT_SIG_S}; 
      strcpy(handshake_message_out->props[2].key, SDDS_SECURITY_PROP_NONCE); 
      strncpy(handshake_message_out->props[2].value, handshake_handle->info.nonce, sizeof(handshake_handle->info.nonce));

      handshake_handle->state = SDDS_SECURITY_HANDSHAKE_STATE_SIGN;
    break;

    case SDDS_SECURITY_HANDSHAKE_STATE_SIGN:
      res = VALIDATION_PENDING_HANDSHAKE_MESSAGE;
#ifdef SDDS_SECURITY_KDC
      // fetch remote mactag from handshake_message_in
      Security_get_bytes(handshake_handle->info.mactag, handshake_message_in->props[0].value);
#else
      // fetch remote signature and nonce from handshake_message_in
      Security_get_bytes(handshake_handle->info.signature_r, handshake_message_in->props[0].value);
      Security_get_bytes(handshake_handle->info.signature_s, handshake_message_in->props[1].value);
      Security_get_bytes(handshake_handle->info.remote_nonce, handshake_message_in->props[2].value);
#endif
      // set up token to send (mactag) to handshake_message_out
      strcpy(handshake_message_out->class_id, SDDS_SECURITY_CLASS_AUTH_REP);
      handshake_message_out->props[0] = (Property) {SDDS_SECURITY_PROP_MACTAG, "bla"}; 

      handshake_handle->state = SDDS_SECURITY_HANDSHAKE_STATE_MACT;
    break;

    case SDDS_SECURITY_HANDSHAKE_STATE_MACT:
#ifdef SDDS_SECURITY_KDC
      // set up token to send (mactag) to handshake_message_out
      strcpy(handshake_message_out->class_id, SDDS_SECURITY_CLASS_AUTH_REP);
      handshake_message_out->props[0] = (Property) {SDDS_SECURITY_PROP_MACTAG, "bla"}; 
      res = VALIDATION_OK_FINAL_MESSAGE;
#else
      Security_get_bytes(handshake_handle->info.mactag, handshake_message_in->props[0].value);
      res = VALIDATION_OK;
#endif
    break;

  }

  return res;

}

#ifdef SDDS_SECURITY_KDC
HandshakeHandle*
Security_get_handshake_handle(IdentityHandle *node) {

  int i;

  for(i = 0; i < SDDS_SECURITY_HANDSHAKE_MAX; i++) {
    if(g_handles[i].node == *node) {
      return &g_handles[i];
    }
  }
  
  for(i = 0; i < SDDS_SECURITY_HANDSHAKE_MAX; i++) {
    if(g_handles[i].node == 0) {
      return &g_handles[i];
    }
  }

  return NULL;

}

void
Security_cleanup_handshake_handle(HandshakeHandle *h) {
  memset(h, 0, sizeof(HandshakeHandle));
}
#endif

void 
Security_get_bytes(uint8_t res[NUM_ECC_DIGITS], char* str) {

	int i;
	uint8_t bytes[NUM_ECC_DIGITS];
  char buf[3];  
  unsigned chr;

	for(i = 0; i < NUM_ECC_DIGITS; i++) {
    strncpy(buf, &str[2*i], 2);
    buf[2] = '\0';
    chr = (unsigned char) strtol(buf, (char **) NULL, 16);
		bytes[i] = chr;
	}

	ecc_bytes2native(res, bytes);
	
}

void 
Security_get_string(char *str, uint8_t num[NUM_ECC_DIGITS]) {

  int i;
	uint8_t bytes[NUM_ECC_DIGITS];
  char buf[3];  
  unsigned chr;

	ecc_native2bytes(bytes, num);

	for(i = 0; i < NUM_ECC_DIGITS; i++) {
    sprintf(&str[i*2], "%02x", num[i]);
	}

}

void 
Security_kdf(uint8_t key_material[SDDS_SECURITY_KDF_KEY_BYTES], uint8_t shared_secret[NUM_ECC_DIGITS], uint8_t nonce[NUM_ECC_DIGITS]) {

  int reps = (SDDS_SECURITY_KDF_KEY_BYTES / SHA1_HASH_BYTES);
  int r = SDDS_SECURITY_KDF_KEY_BYTES % SHA1_HASH_BYTES;
  if(r) {
    reps++;
  }                                
  char counter_str[32];
  uint8_t hash[SHA1_HASH_BYTES];
  int size = sizeof(counter_str) + NUM_ECC_DIGITS + sizeof(nonce);
  uint8_t data[size];

  for(uint32_t i = 0; i < reps; i++) {
    
    for (int j = 0; j < sizeof(counter_str); j++) {
      counter_str[j] = ((1 << j) & (i + 1)) ? ('1') : ('0');
    }
    
    memcpy(data, counter_str, sizeof(counter_str));
    memcpy(data + sizeof(counter_str), shared_secret, NUM_ECC_DIGITS);
    memcpy(data + sizeof(counter_str) + NUM_ECC_DIGITS, nonce, sizeof(nonce));

    sha1(hash, data, size*8);
    
    if(i == reps - 1 && r) {
      memcpy(key_material + (i*SHA1_HASH_BYTES), hash, r);    
    } else {      
      memcpy(key_material + (i*SHA1_HASH_BYTES), hash, SHA1_HASH_BYTES);    
    }

  }
  
}

void 
Security_aes_xcbc_mac(uint8_t aes_key[AES_128_KEY_LENGTH], uint8_t *data, uint8_t size, uint8_t mac[XCBC_MAC_SIZE]) {

  uint8_t key1[AES_128_KEY_LENGTH];
  uint8_t key2[AES_128_KEY_LENGTH];
  uint8_t key3[AES_128_KEY_LENGTH];

  uint8_t e[AES_128_KEY_LENGTH];
  uint8_t result[AES_128_KEY_LENGTH];
  uint8_t last_block[AES_128_KEY_LENGTH];

  uint8_t n, last, i, j;

  n = size / AES_128_KEY_LENGTH;
  last = size % AES_128_KEY_LENGTH;

  memset(e, 0, AES_128_KEY_LENGTH);
  memset(key1, XCBC_K1, AES_128_KEY_LENGTH);
  memset(key2, XCBC_K2, AES_128_KEY_LENGTH);
  memset(key3, XCBC_K3, AES_128_KEY_LENGTH);

  aes_128_set_padded_key(aes_key, AES_128_KEY_LENGTH);

  aes_128_padded_encrypt(key1, AES_128_KEY_LENGTH);
  aes_128_padded_encrypt(key2, AES_128_KEY_LENGTH);
  aes_128_padded_encrypt(key3, AES_128_KEY_LENGTH);

  aes_128_set_padded_key(key1, AES_128_KEY_LENGTH);

  for(i = 0; i < n-1; i++) {
    for(j = 0; j < AES_128_KEY_LENGTH; j++) {
      result[j] = data[(i*AES_128_KEY_LENGTH) + j] ^ e[j];      
    }    
    aes_128_padded_encrypt(result, AES_128_KEY_LENGTH);
    memcpy(e, result, AES_128_KEY_LENGTH);
  }

  if(!last) {   
    for(j = 0; j < AES_128_KEY_LENGTH; j++) {    
      result[j] = data[(n*AES_128_KEY_LENGTH) + j] ^ e[j] ^ key2[j];      
    }
  } else {
    memset(last_block, 0, AES_128_KEY_LENGTH);
    memcpy(last_block, &data[(n*AES_128_KEY_LENGTH)], last);
    for(j = 0; j < AES_128_KEY_LENGTH; j++) {    
      result[j] = last_block[j] ^ e[j] ^ key3[j];      
    }
  }

  aes_128_padded_encrypt(result, AES_128_KEY_LENGTH);
  memcpy(e, result, AES_128_KEY_LENGTH);

}


/* 
  Security_kdf(key_material, shared_secret, &inf);

  printf("kdf derived key material: ");
  printf("size %d\n", sizeof(key_material));
  for(int i = 0; i < sizeof(key_material); i+=2) {
    printf("%x%x", key_material[i], key_material[i+1]);
  }
  printf("\n");

  Security_kdf(key_material, shared_secret, &inf);

  printf("kdf derived key material: ");
  printf("size %d\n", sizeof(key_material));
  for(int i = 0; i < sizeof(key_material); i+=2) {
    printf("%x%x", key_material[i], key_material[i+1]);
  }
  printf("\n");
*/

#endif
