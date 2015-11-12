/*
 * =====================================================================================
 *
 *       Filename:  SNPS.c
 *
 *    Description:  SNPS protocoll class impl file
 *
 *        Version:  1.0
 *        Created:  27.02.2010 15:13:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kai Beckmann (kai), kai-oliver.beckmann@hs-rm.de
 *        Company:  Hochschule RheinMain - DOPSY Labor für verteilte Systeme
 *
 * =====================================================================================
 */
#include "SNPS.h"
#include "Marshalling.h"
#include "Log.h"
#include "Network.h"
#include "Discovery.h"
#include "Locator.h"
#include <sdds/Log.h>

#include <string.h>

#define SNPS_MULTICAST_COMPRESSION_FRST_NIBBLE			0
#define SNPS_MULTICAST_COMPRESSION_SCND_NIBBLE			1
#define SNPS_MULTICAST_COMPRESSION_FLAGS				2
#define SNPS_MULTICAST_COMPRESSION_SLOPE				3
#define SNPS_MULTICAST_COMPRESSION_FRST_COLON			4
#define SNPS_MULTICAST_COMPRESSION_SCND_COLON			5

#define START (ref->buff_start + ref->curPos)

rc_t _writeBasicTopic(NetBuffRef ref, topicid_t topic);
#ifdef SDDS_EXTENDED_TOPIC_SUPPORT
rc_t _writeExtTopic(NetBuffRef ref, topicid_t topic);
#endif


rc_t SNPS_evalSubMsg(NetBuffRef ref, subMsg_t* type)
{

    uint8_t read;
    Marshalling_dec_uint8(START, &read);

    // it is a basic submessage: sub msg id == sub msg id
    // if id == 15 => extended
    if ((read & 0x0f) < 15){
    	*type = (read & 0x0f);
    	return SDDS_RT_OK;
    } 

    // it is an extended submessage
    // eval the next 4 bits
    switch ((read >> 4) & 0x0f){
	case (SDDS_SNPS_EXTSUBMSG_ACK):
	    *type = SDDS_SNPS_T_ACK;
	    break;
	case (SDDS_SNPS_EXTSUBMSG_NACK):
	    *type = SDDS_SNPS_T_NACK;
	    break;
	case (SDDS_SNPS_EXTSUBMSG_SEP):
	    *type = SDDS_SNPS_T_SEP;
	    break;
	case (SDDS_SNPS_EXTSUBMSG_TSDDS):
	    *type = SDDS_SNPS_T_TSDDS;
	    break;
	case (SDDS_SNPS_EXTSUBMSG_TOPIC):
			// its an topic ...
		*type = SDDS_SNPS_T_TOPIC;
		break;
	case (SDDS_SNPS_EXTSUBMSG_EXTENDED):
	    // read the next byte etc
	    // TODO
	    *type = SDDS_SNPS_T_UNKNOWN;
	    break;
	default:
	    *type = SDDS_SNPS_T_UNKNOWN;
	    break;
    }
   

    return SDDS_RT_OK;
}

rc_t SNPS_discardSubMsg(NetBuffRef ref)
{
    uint8_t read;
    Marshalling_dec_uint8(START, &read);
   
    // submsg will be removed, all the same
    // read at least the basic submsgheader
    ref->subMsgCount--;
    ref->curPos += 1;

    switch ((read & 0x0f)){
	// data field. pos counter + lenght and submsg
	case (SDDS_SNPS_SUBMSG_DATA):
	    ref->curPos += ((read >> 4) & 0x0f);
	    return SDDS_RT_OK;
	    // simple timestamp pos counter + 2 byte and submsg
	case (SDDS_SNPS_SUBMSG_TS):
	    ref->curPos += 2;
	    return SDDS_RT_OK;

	    // extended submsg eval later
	case (SDDS_SNPS_SUBMSG_EXTENDED):
	    break;

	    // normale submsg with the size of 8 bit
	default: 
	    return SDDS_RT_OK;
    }



    // it is an extended submessage
    // eval the next 4 bits
    switch ((read >> 4) & 0x0f){
	// 1 byte extsubmsg
	case (SDDS_SNPS_EXTSUBMSG_ACK):
	case (SDDS_SNPS_EXTSUBMSG_NACK):
	case (SDDS_SNPS_EXTSUBMSG_SEP):
	    break;
	case (SDDS_SNPS_EXTSUBMSG_TOPIC): // ext topic has 2 bytes
		ref->curPos += 2;
		break;
	case (SDDS_SNPS_EXTSUBMSG_TSDDS):
	    // 1 byte header + 2 x 4 byte sec and nanosec
	    ref->curPos += 8;
	    break;
	case (SDDS_SNPS_EXTSUBMSG_EXTENDED):
	    // TODO
	    return SDDS_RT_FAIL;
	    break;
	default:
	    // shouldn't happen
	    return SDDS_RT_FAIL;
    }


    return SDDS_RT_OK;
}

rc_t SNPS_gotoNextSubMsg(NetBuffRef buff, subMsg_t type)
{
	subMsg_t readType;
	while (buff->subMsgCount > 0){
		SNPS_evalSubMsg(buff, &readType);
		if (readType != type){
			if (SNPS_discardSubMsg(buff) != SDDS_RT_OK){
				return SDDS_RT_FAIL;
			}
		} else {
			return SDDS_RT_OK;
		}
	}
	return SDDS_RT_OK;
}

rc_t SNPS_initFrame(NetBuffRef ref)
{
    // write header
    version_t v = SDDS_NET_VERSION;
    Marshalling_enc_uint8(ref->buff_start, &v);
    ref->curPos += sizeof(version_t);
    // place holder
    Marshalling_enc_uint8( START, &(ref->subMsgCount));
    ref->curPos += sizeof(uint8_t);

    return SDDS_RT_OK;
}
rc_t SNPS_readHeader(NetBuffRef ref)
{
    version_t v;
    Marshalling_dec_uint8(ref->buff_start, &v);
    ref->curPos += sizeof(version_t);
    if (v != SDDS_NET_VERSION){
	return SDDS_RT_FAIL;
    }
    Marshalling_dec_uint8(START, &(ref->subMsgCount));
    ref->curPos += sizeof(uint8_t);

    return SDDS_RT_OK;
}

rc_t SNPS_updateHeader(NetBuffRef ref)
{
    Marshalling_enc_uint8( (ref->buff_start + sizeof(version_t)), &(ref->subMsgCount));

    return SDDS_RT_OK;
}

rc_t SNPS_writeDomain(NetBuffRef ref, domainid_t domain)
{
    Marshalling_enc_SubMsg(START, SDDS_SNPS_SUBMSG_DOMAIN, (uint8_t)domain);
    ref->curPos += 1;
    ref->subMsgCount +=1;

    return SDDS_RT_OK;
}
rc_t SNPS_readDomain(NetBuffRef ref, domainid_t* domain)
{
    Marshalling_dec_SubMsg(START, SDDS_SNPS_SUBMSG_DOMAIN, (uint8_t*)domain);
    ref->curPos += 1;
    ref->subMsgCount -=1;

    return SDDS_RT_OK;
}

rc_t SNPS_writeTopic(NetBuffRef ref, topicid_t topic)
{
#ifdef SDDS_EXTENDED_TOPIC_SUPPORT
	if (topic > 15) {
		return _writeExtTopic(ref, topic);
	}
#endif

    return _writeBasicTopic(ref, topic);
}
rc_t _writeBasicTopic(NetBuffRef ref, topicid_t topic)
{
    Marshalling_enc_SubMsg(START, SDDS_SNPS_SUBMSG_TOPIC, (uint8_t)topic);
    ref->curPos +=1;
    ref->subMsgCount +=1;

	return SDDS_RT_OK;
}
#ifdef SDDS_EXTENDED_TOPIC_SUPPORT
rc_t _writeExtTopic(NetBuffRef ref, topicid_t topic)
{
	// write the header of an extended submessage of the type topic
	Marshalling_enc_SubMsg(START, SDDS_SNPS_SUBMSG_EXTENDED, SDDS_SNPS_EXTSUBMSG_TOPIC);
	ref->curPos +=1;
	Marshalling_enc_uint16(START, &topic);
	ref->curPos += 2;
	ref->subMsgCount += 1;

	return SDDS_RT_OK;
}
#endif

rc_t SNPS_readTopic(NetBuffRef ref, topicid_t* topic)
{
	rc_t ret;
	ret = Marshalling_dec_SubMsg(START, SDDS_SNPS_SUBMSG_TOPIC, (uint8_t*)topic);

#ifdef SDDS_EXTENDED_TOPIC_SUPPORT
	if (ret == SDDS_RT_FAIL) {
		// might be an extended topic
		subMsg_t type;
		ret = Marshalling_dec_SubMsg(START, SDDS_SNPS_SUBMSG_EXTENDED, &type);
		if (ret != SDDS_RT_OK) {
			return SDDS_RT_FAIL;
		}
		if (type != SDDS_SNPS_EXTSUBMSG_TOPIC) {
			Log_error("Submessage is not an extended topic\n");
			return SDDS_RT_FAIL;
		}
		ref->curPos +=1;
		// decode the topic itself
		Marshalling_dec_uint16(START, (uint16_t*) topic);
		ref->curPos +=1;// only 1 byte since in the basic case only one byte is
						// added, so the sum is 2 (3 with header)
	}
#endif
    ref->curPos +=1;
    ref->subMsgCount -=1;

    return SDDS_RT_OK;
}

rc_t SNPS_writeData(NetBuffRef ref, rc_t (*TopicMarshalling_encode)(byte_t* buff, Data data, size_t* size), Data d)
{
    size_t writtenBytes = 0;

    // start 1 byte later, the header have to be written if the size is known
    byte_t* s = (ref->buff_start + ref->curPos + 1);


    if ((*TopicMarshalling_encode)(s, d, &writtenBytes) != SDDS_RT_OK)
    	return SDDS_RT_FAIL;

    Marshalling_enc_SubMsg(START, SDDS_SNPS_SUBMSG_DATA, (uint8_t) writtenBytes);

    // data header
    ref->curPos += 1;
    // data itself
    ref->curPos += writtenBytes;
    ref->subMsgCount +=1;

    return SDDS_RT_OK;
}

rc_t SNPS_readData(NetBuffRef ref, rc_t (*TopicMarshalling_decode)(byte_t* buff, Data data, size_t* size), Data data)
{
	size_t size = 0;

	Marshalling_dec_SubMsg(START, SDDS_SNPS_SUBMSG_DATA, (uint8_t*) &size);

	ref->curPos += 1;


	byte_t* s = (ref->buff_start + ref->curPos);

	if ((*TopicMarshalling_decode)(s, data, &size) != SDDS_RT_OK){

		return SDDS_RT_FAIL;
	}

	ref->curPos += size;
	ref->subMsgCount -= 1;

	return SDDS_RT_OK;
}

rc_t SNPS_char2Hex(char c, uint8_t *h) {
	switch (c) {
	case '0':
		h[0] = 0x0;
		break;
	case '1':
		h[0] = 0x1;
		break;
	case '2':
		h[0] = 0x2;
		break;
	case '3':
		h[0] = 0x3;
		break;
	case '4':
		h[0] = 0x4;
		break;
	case '5':
		h[0] = 0x5;
		break;
	case '6':
		h[0] = 0x6;
		break;
	case '7':
		h[0] = 0x7;
		break;
	case '8':
		h[0] = 0x8;
		break;
	case '9':
		h[0] = 0x9;
		break;
	case 'A':
		h[0] = 0xA;
		break;
	case 'a':
		h[0] = 0xA;
		break;
	case 'B':
		h[0] = 0xB;
		break;
	case 'b':
		h[0] = 0xB;
		break;
	case 'C':
		h[0] = 0xC;
		break;
	case 'c':
		h[0] = 0xC;
		break;
	case 'D':
		h[0] = 0xD;
		break;
	case 'd':
		h[0] = 0xD;
		break;
	case 'E':
		h[0] = 0xE;
		break;
	case 'e':
		h[0] = 0xE;
		break;
	case 'F':
		h[0] = 0xF;
		break;
	case 'f':
		h[0] = 0xF;
		break;
	default:
		return SDDS_RT_BAD_PARAMETER;
	}

	return SDDS_RT_OK;
}

rc_t SNPS_IPv6_str2Addr(char *charAddr, uint8_t *byteAddr, uint8_t *addrLen) {
	uint8_t tmpAddrLen = (SNPS_MULTICAST_COMPRESSION_MAX_LENGTH_IN_BYTE  * 2);
	uint8_t tmpAddr[tmpAddrLen];
	uint8_t tmpAddrPos = tmpAddrLen-1;
	*addrLen = 0;

	uint8_t strLen = strlen(charAddr);

	memset(tmpAddr, 0, tmpAddrLen);

	if (  (strLen > SNPS_MULTICAST_COMPRESSION_MAX_LENGTH_IN_CHAR)
	   || (strLen < SNPS_MULTICAST_COMPRESSION_MIN_LENGTH_IN_CHAR)
	) {
		// Multicast address is not suited for compression
		return SDDS_RT_BAD_PARAMETER;
	}

	if ( 	(  (charAddr[SNPS_MULTICAST_COMPRESSION_FRST_NIBBLE] != 'f')
			&& (charAddr[SNPS_MULTICAST_COMPRESSION_FRST_NIBBLE] != 'F') )
	    ||	(  (charAddr[SNPS_MULTICAST_COMPRESSION_SCND_NIBBLE] != 'f')
			&& (charAddr[SNPS_MULTICAST_COMPRESSION_SCND_NIBBLE] != 'F') )
	) {
		// Not a valid multicast address
		return SDDS_RT_BAD_PARAMETER;
	}

	if ( 	(charAddr[SNPS_MULTICAST_COMPRESSION_FRST_COLON] != ':')
	    ||	(charAddr[SNPS_MULTICAST_COMPRESSION_SCND_COLON] != ':')
	) {
		// Not a valid multicast address
		return SDDS_RT_BAD_PARAMETER;
	}

	uint8_t colonCount = 0;
	for (int i = (strLen-1); i > SNPS_MULTICAST_COMPRESSION_SCND_COLON; i--) {
		if ( (tmpAddrPos < 0) ) {
			// ffFS::00GG:GGGG:GGGG	-> check for the possible leading 0-Byte
			if (charAddr[i] != '0')	 {
				// Not a valid multicast address
				return SDDS_RT_BAD_PARAMETER;
			}
			else {
				continue;
			}
		}
		else if ( (charAddr[i] != ':') && (colonCount < 4) ) {
			if ( SNPS_char2Hex(charAddr[i], &tmpAddr[tmpAddrPos]) != SDDS_RT_OK) {
				return SDDS_RT_BAD_PARAMETER;
			}
			tmpAddrPos--;
			colonCount++;
		}
		else if ( (charAddr[i] == ':') ) {
			while (colonCount < 4) {
				tmpAddr[tmpAddrPos] = 0;
				tmpAddrPos--;
				colonCount++;
			}
			colonCount = 0;
		}
	}

	if ( SNPS_char2Hex(charAddr[SNPS_MULTICAST_COMPRESSION_SLOPE], &tmpAddr[1]) != SDDS_RT_OK) {
		return SDDS_RT_BAD_PARAMETER;
	}

	if ( SNPS_char2Hex(charAddr[SNPS_MULTICAST_COMPRESSION_FLAGS], &tmpAddr[0]) != SDDS_RT_OK) {
		return SDDS_RT_BAD_PARAMETER;
	}

	for (int i = 0; i < SNPS_MULTICAST_COMPRESSION_MAX_LENGTH_IN_BYTE; i++) {
		int first = i*2;
		int second = (i*2) + 1;

		byteAddr[(i)] = ((tmpAddr[first] << 4) | tmpAddr[second]);
		(*addrLen)++;
	}

	return SDDS_RT_OK;
}

rc_t SNPS_IPv6_addr2Str(uint8_t *byteAddr, char *charAddr) {
	sprintf(charAddr, "FF%02X::00%02X:%02X%02X:%02X%02X", byteAddr[0], byteAddr[1], byteAddr[2], byteAddr[3], byteAddr[4], byteAddr[5]);
	return SDDS_RT_OK;
}

rc_t SNPS_writeAddress(NetBuffRef ref, castType_t castType, addrType_t addrType, uint8_t *addr, uint8_t addrLen) {
	rc_t ret = 0;

	Marshalling_enc_SubMsg(START, SDDS_SNPS_SUBMGS_ADDR, addrLen);
	ref->curPos += 1;
	ref->subMsgCount += 1;

	uint8_t addrSpecs = (castType | (addrType << 4));
	Marshalling_enc_int8(START, (uint8_t *) &addrSpecs);
	ref->curPos += 1;

	Marshalling_enc_string(START, addr, addrLen);
	ref->curPos += addrLen;

	return SDDS_RT_OK;
}

rc_t SNPS_readAddress(NetBuffRef ref, castType_t *addrCast, addrType_t *addrType, char *addr)
{
	rc_t ret;
	uint8_t addrLen;
	ret = Marshalling_dec_uint8(START, &addrLen);
	addrLen = (addrLen >> 4);
    ref->curPos +=1;

    uint8_t addrInfo;
    ret = Marshalling_dec_uint8(START, &addrInfo);
    *addrCast = (addrInfo & 0x0f);
    *addrType = ((addrInfo >> 4) & 0x0f);
    ref->curPos +=1;

    if (*addrCast == SDDS_SNPS_CAST_UNICAST) {
//	if (addrLen == 0) {
    	ret = Locator_getAddress(ref->addr, addr);
    }
    else {
    	char byteAddr[SNPS_MULTICAST_COMPRESSION_MAX_LENGTH_IN_BYTE];
        ret = Marshalling_dec_string(START, byteAddr, addrLen);
        ref->curPos +=addrLen;

    	char charAddr[SNPS_MULTICAST_COMPRESSION_MAX_LENGTH_IN_CHAR + 1];
    	ret = SNPS_IPv6_addr2Str(byteAddr, addr);
    }

    ref->subMsgCount -=1;

#ifdef UTILS_DEBUG
    char a[1024];
    ret = Locator_getAddress(ref->addr, a);
	Log_debug("Connection from %s\n", a);
#endif

    return SDDS_RT_OK;
}

/*
rc_t SNPS_writeTSsimple(NetBuffRef ref, TimeStampSimple_t* ts)
{
    Marshalling_enc_SubMsg(START, SDDS_SNPS_SUBMSG_TS, ts->firstField);
    ref->curPos += 1;
    Marshalling_enc_uint8(START, &(ts->secondField));
    ref->curPos += 1;
    Marshalling_enc_uint8(START, &(ts->thirdField));
    ref->curPos += 1;
    
    ref->subMsgCount +=1;

    return SDDS_RT_OK;

}
*/
//rc_t SNPS_writeStatus(NetBuffRef ref);
//rc_t SNPS_writeSeqNr(NetBuffRef ref);
//rc_t SNPS_writeAckSeq(NetBuffRef ref);
//rc_t SNPS_writeNackSeq(NetBuffRef ref);
//rc_t SNPS_writeNack(NetBuffRef ref);
//rc_t SNPS_writeAck(NetBuffRef ref);
//rc_t SNPS_writeTSuSec(NetBuffRef ref);
//rc_t SNPS_writeTSmSec(NetBuffRef ref);
//rc_t SNPS_writeSeqNrBig(NetBuffRef ref);
//rc_t SNPS_writeSeqNrSmall(NetBuffRef ref);
//rc_t SNPS_writeSeqNrHUGE(NetBuffRef ref);
//rc_t SNPS_writeTSDDS(NetBuffRef ref);
//rc_t SNPS_wrieSep(NetBuffRef ref);
//rc_t SNPS_writeAddressess(NetBuffRef ref);
