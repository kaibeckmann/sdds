/*
 * =====================================================================================
 *
 *       Filename:  DataSource.c
 *
 *    Description:  Impl for the datasource class
 *
 *        Version:  1.0
 *        Created:  22.02.2010 18:09:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kai Beckmann (kai), kai-oliver.beckmann@hs-rm.de
 *        Company:  Hochschule RheinMain - DOPSY Labor für verteilte Systeme
 *
 * =====================================================================================
 */

#include "DataSource.h"
#include "sDDS.h"
#include "Log.h"
#include "SourceQos.h"
#include "SNPS.h"
#include "NetBuffRef.h"
#include "Network.h"
#include "Marshalling.h"

#include <stdlib.h>
#include <string.h>

// IF BUILTINTOPIC
#include "BuiltinTopic.h"

struct InstantSender {
	struct NetBuffRef_t highPrio;
	struct NetBuffRef_t out[SDDS_NET_MAX_OUT_QUEUE];
};
typedef struct InstantSender InstantSender_t;

struct DataWriter {
	Topic topic;
	struct SourceQos_t qos;
	unsigned int id :4;
};

struct DataSource {
#if SDDS_MAX_DATA_WRITERS > 0
	DataWriter_t writers[SDDS_MAX_DATA_WRITERS];
#endif
	InstantSender_t sender;

#if defined(__GNUC__) && __GNUC_MINOR__ < 6
#pragma GCC diagnostic error "-Woverflow"
#endif
	unsigned int remaining_datawriter :4;
};

static DataSource_t dsStruct;

DataSource dataSource = &dsStruct;

NetBuffRef findFreeFrame(Locator dest);
rc_t checkSending(NetBuffRef buf);

rc_t BuiltinTopicDomainParticipant_encode(byte_t* buff, Data data, size_t* size);
rc_t BuiltinTopicDataWriter_encode(byte_t* buff, Data data, size_t* size);

#ifdef FEATURE_SDDS_DISCOVERY_ENABLED
rc_t DataSource_getTopic(DDS_DCPSSubscription *st, topicid_t id, Topic *topic) {
	int i;
	for (i = 0; i < (SDDS_MAX_DATA_WRITERS - dataSource->remaining_datawriter);
			i++) {
		if ((dataSource->writers[i].topic->id == id)) {
			if (st != NULL) {
				st->key = dataSource->writers[i].id;
				st->participant_key = BuiltinTopic_participantID;
				st->topic_id = dataSource->writers[i].topic->id;
			}
			if (topic != NULL) {
				*topic = dataSource->writers[i].topic;
			}
			return SDDS_RT_OK;
		}
	}

	return SDDS_RT_FAIL;
}
#endif

#ifdef FEATURE_SDDS_DISCOVERY_ENABLED
rc_t DataSource_getDataWrites(DDS_DCPSPublication *pt, int *len) {
	int i = 0;
	*len = 0;

	for (i = 0; i < (SDDS_MAX_DATA_WRITERS - dataSource->remaining_datawriter);
			i++) {
#ifdef FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
		if (!BuildinTopic_isBuiltinTopic(dataSource->writers[i].topic->id,
				dataSource->writers[i].topic->domain)) {
#endif
			pt[*len].key = dataSource->writers[i].id;
			pt[*len].participant_key = BuiltinTopic_participantID;
			pt[*len].topic_id = dataSource->writers[i].topic->id;

			(*len)++;
#ifdef FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
		}
#endif
	}

	return SDDS_RT_OK;
}
#endif

rc_t DataSource_init(void) {

#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Woverflow"
#endif

	dataSource->remaining_datawriter = SDDS_MAX_DATA_WRITERS;

#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
#pragma GCC diagnostic pop
#endif

	// init instant sender
	// the init method alloc a frame buffer and adds it to the structure
	NetBuffRef_init(&(dataSource->sender.highPrio));
	NetBuffRef_init(&(dataSource->sender.out[0]));
	NetBuffRef_init(&(dataSource->sender.out[1]));

	return SDDS_RT_OK;
}

#if SDDS_MAX_DATA_WRITERS > 0
DataWriter DataSource_create_datawriter(Topic topic, Qos qos, Listener list, StatusMask mask)
{
	qos=qos;
	list=list;
	mask=mask;

	DataWriter dw = NULL;

	if (dataSource->remaining_datawriter == 0) {
		return NULL;
	}
	dw = &(dataSource->writers[SDDS_MAX_DATA_WRITERS - dataSource->remaining_datawriter]);

	dw->topic = topic;
	dw->id = (SDDS_MAX_DATA_WRITERS - dataSource->remaining_datawriter);
	dataSource->remaining_datawriter--;

	if (dw->id == 1)
	dw->qos.latBudDuration = SDDS_QOS_DW1_LATBUD;
	if (dw->id == 2)
	dw->qos.latBudDuration = SDDS_QOS_DW2_LATBUD;

	return dw;
}
#endif // SDDS_MAX_DATA_WRITERS

NetBuffRef findFreeFrame(Locator dest) {
	NetBuffRef buffRef = NULL;

	bool_t sameAddr = false;
	for (int i = 0; i < SDDS_NET_MAX_OUT_QUEUE; i++) {
		Locator try = dataSource->sender.out[i].addr;
		if (dest != NULL && try != NULL && Locator_isEqual(dest, try)) {
			buffRef = &(dataSource->sender.out[i]);
			sameAddr = true;
			break;
		}
	}
	if (buffRef == NULL) {
		for (int i = 0; i < SDDS_NET_MAX_OUT_QUEUE; i++) {
			if (dataSource->sender.out[i].curPos == 0) {
				buffRef = &(dataSource->sender.out[i]);
				break;
			}
		}
	}
	if (buffRef == NULL) {
		buffRef = &(dataSource->sender.highPrio);
	}
	if (buffRef->curPos == 0) {
		SNPS_initFrame(buffRef);
	}
	if (sameAddr == false) {
		// write addr

		// here add the ref to the buff, addr is used when frame is update addr
		// in bufref
		buffRef->addr = dest;
	}
	return buffRef;
}

rc_t checkSending(NetBuffRef buf) {
	if (true) {
		// update header

		SNPS_updateHeader(buf);

		if (buf->addr != NULL) {

			if (Network_send(buf) != SDDS_RT_OK) {
				return SDDS_RT_FAIL;
			}

		}

		// is frame is send free the buffer
		NetBuffRef_renew(buf);

	}
	return SDDS_RT_OK;
}
#if defined(SDDS_TOPIC_HAS_SUB) || defined(FEATURE_SDDS_BUILTIN_TOPICS_ENABLED)
rc_t DataSource_write(DataWriter _this, Data data, void* waste)
{

	waste = waste;
	NetBuffRef buffRef = NULL;
	Topic topic = _this->topic;
	domainid_t domain = topic->domain;
	Locator dest = topic->dsinks.list;


	buffRef = findFreeFrame(dest);
	buffRef->addr = dest;


	if(buffRef->curDomain != domain) {
		SNPS_writeDomain(buffRef, domain);
		buffRef->curDomain = domain;
	}

	if(buffRef->curTopic != topic) {
		SNPS_writeTopic(buffRef, topic->id);
		buffRef->curTopic = topic;
	}

	if (SNPS_writeData(buffRef, topic->Data_encode, data) != SDDS_RT_OK) {
		// something went wrong oO
		return SDDS_RT_FAIL;
	}


	Log_debug("writing to domain %d and topic %d \n", topic->domain, topic->id);
	// return 0;


	return checkSending(buffRef);
}
#endif // SDDS_TOPIC_HAS_SUB

#ifdef FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
rc_t DataSource_writeAddress(DataWriter _this, castType_t castType, addrType_t addrType, uint8_t *addr, uint8_t addrLen) {
	NetBuffRef buffRef = NULL;
	Topic topic = _this->topic;
	domainid_t domain = topic->domain;
	Locator dest = topic->dsinks.list;

	buffRef = findFreeFrame(dest);
	buffRef->addr = dest;

	if (buffRef->curDomain != domain) {
		SNPS_writeDomain(buffRef, domain);
		buffRef->curDomain = domain;
	}
	if (buffRef->curTopic != topic) {
		SNPS_writeTopic(buffRef, topic->id);
		buffRef->curTopic = topic;
	}

	if (SNPS_writeAddress(buffRef, castType, addrType, addr, addrLen) != SDDS_RT_OK) {
		// something went wrong oO
		return SDDS_RT_FAIL;
	}

	Log_debug("writing to domain %d and topic %d \n", topic->domain, topic->id);

	return SDDS_RT_OK;
}
#endif

/*
 // impl for BuiltinTopic
 rc_t BuiltinTopic_publishAll(void)
 {

 // get new buffer
 NetBuffRef buf = NULL;

 buf = findFreeFrame(builtinTopicNetAddress);
 if (buf == NULL){
 return SDDS_RT_FAIL;
 }
 // write domain
 if (buf->curDomain != SDDS_DOMAIN_DEFAULT){
 SNPS_writeDomain(buf, SDDS_DOMAIN_DEFAULT);
 buf->curDomain = SDDS_DOMAIN_DEFAULT;
 }

 // write dps
 BuiltinTopic_writeDomainParticipant2Buf(buf);
 // write topics
 BuiltinTopic_writeTopics2Buf(buf);
 // write datawriter
 BuiltinTopic_writeDataWriters2Buf(buf);
 // write datareader
 BuiltinTopic_writeDataReaders2Buf(buf);
 // send buffer
 return checkSending(buf);

 }

 rc_t BuiltinTopic_writeDomainParticipant2Buf(NetBuffRef buf)
 {
 SNPS_writeTopic(buf, SDDS_BUILTINTOPIC_PARTICIPANT_TOPIC_ID);

 // for each? not yet TODO
 SNPS_writeData(buf, BuiltinTopicDomainParticipant_encode, NULL);

 return SDDS_RT_OK;
 }

 rc_t BuiltinTopicDomainParticipant_encode(byte_t* buff, Data data, size_t* size)
 {
 // no content, just a '' here  i am''
 *size = 0;

 return SDDS_RT_OK;
 }

 rc_t BuiltinTopic_writeDataWriters2Buf(NetBuffRef buf)
 {
 // write topic id
 SNPS_writeTopic(buf, SDDS_BUILTINTOPIC_PUBLICATION_TOPIC_ID);
 // datasample for earch datawriter
 for (uint8_t i = 0;
 i < (SDDS_MAX_DATA_WRITERS - dataSource->remaining_datawriter);
 i++)
 {
 SNPS_writeData(buf, BuiltinTopicDataWriter_encode, (Data) &(dataSource->writers[i]));
 }
 return SDDS_RT_OK;
 }

 rc_t BuiltinTopicDataWriter_encode(byte_t* buff, Data data, size_t* size)
 {
 DataWriter dw = (DataWriter) data;
 *size = 0;
 Marshalling_enc_uint8(buff+(*size), &(dw->topic->domain));
 *size += sizeof(domainid_t);
 Marshalling_enc_uint8(buff+(*size), &(dw->topic->id));
 *size += sizeof(topicid_t);

 return SDDS_RT_OK;
 }
 */
