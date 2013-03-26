/*
 * =====================================================================================
 *
 *       Filename:  DataSink.c
 *
 *    Description:  Impl file for the DataSink class
 *
 *        Version:  1.0
 *        Created:  03.03.2010 08:57:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kai Beckmann (kai), kai-oliver.beckmann@hs-rm.de
 *        Company:  Hochschule RheinMain - DOPSY Labor für verteilte Systeme
 *
 * =====================================================================================
 */

#include "sDDS.h"

#include "DataSink.h"
#include "SNPS.h"
#include "Topic.h"
#include "TopicDB.h"
#include "BuiltinTopic.h"
#include "Marshalling.h"
#include "sdds_types.h"

#include "Log.h"

struct DataReader {
    Topic topic;
    unsigned int id : 3;
    On_Data_Avail_Listener on_data_avail_listener;
};

struct DataSink_t {
    DataReader_t readers[sDDS_MAX_DATA_READERS];

#if defined(__GNUC__) && __GNUC_MINOR__ < 6
#pragma GCC diagnostic error "-Woverflow"
#endif
    unsigned int remaining_datareader : 3;
};

static Msg msg;
static struct DataSink_t dsStruct;
DataSink dataSink = &dsStruct;

rc_t parseData(NetBuffRef buff);
rc_t submitData(void);
rc_t checkDomain(NetBuffRef buff, domainid_t domain);
rc_t checkTopic(NetBuffRef buff, topicid_t topic);

rc_t BuiltinTopicDataReader_encode(byte_t* buff, Data data, size_t* size);

rc_t DataSink_processFrame(NetBuffRef buff)
{
    rc_t ret;

    if (buff == NULL)
	return SDDS_RT_FAIL;

    // process the frame
    // parse the header
    ret = SNPS_readHeader(buff);
    if (ret != SDDS_RT_OK){
	// done reset the buffer
    	NetBuffRef_renew(buff);
	return SDDS_RT_FAIL;
    }
    
    // should be NULL!
    msg = NULL;
    topicid_t topic;

    while (buff->subMsgCount > 0)
    {
	// get sum msg id
	subMsg_t type;
	SNPS_evalSubMsg(buff, &type);
	switch (type){
	    case (SNPS_T_DOMAIN) :
		// check data
		submitData();
		domainid_t domain;
    		SNPS_readDomain(buff, &domain);
		// check domain
		checkDomain(buff, domain);
		break;
	    case (SNPS_T_TOPIC) :
		// check data
		submitData();
		SNPS_readTopic(buff, &topic);
		// check topic
		checkTopic(buff, topic);
		break;
	    case (SNPS_T_DATA) :
#ifdef sDDS_TOPIC_HAS_PUB
		// check data
		submitData();
		ret = parseData(buff);
		if (ret != SDDS_RT_OK)
		    return SDDS_RT_FAIL;
#endif
		break;
//	    case (SNPS_T_TSSIMPLE) :
//		break;
//	    case (SNPS_T_STATUS) :
//		break;
	    default:
		// go to next submsg
		// unknown content
		SNPS_discardSubMsg(buff);
		break;
	}

    }
    // submit the last decoded msg
    submitData();
    // done reset the buffer
    NetBuffRef_renew(buff);

    // ggf send events to the applications

    for (uint8_t i = 0; i < sDDS_MAX_DATA_READERS - dataSink->remaining_datareader; i ++){
    	DataReader dr = &(dataSink->readers[i]);
    	int tpc = dr->topic->id;
		if((topic == tpc) && dr->on_data_avail_listener){
			dr->on_data_avail_listener(dr);
		}
    }
    return SDDS_RT_OK;
		}

rc_t DataSink_init(void)
{

#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Woverflow"
#endif

    dataSink->remaining_datareader = sDDS_MAX_DATA_READERS;

#if defined(__GNUC__) && __GNUC_MINOR__ >= 6
#pragma GCC diagnostic pop
#endif

    return SDDS_RT_OK;
}
#ifdef sDDS_TOPIC_HAS_PUB
DataReader DataSink_create_datareader(Topic topic, Qos qos, Listener listener, StatusMask sm)
{

    qos = qos;
    sm = sm;

    DataReader dr = NULL;
    // not free slots?
    if (dataSink->remaining_datareader == 0){
    	return NULL;
    }

    dr = &(dataSink->readers[sDDS_MAX_DATA_READERS - dataSink->remaining_datareader]);
    dr->id = sDDS_MAX_DATA_READERS - dataSink->remaining_datareader;

    dataSink->remaining_datareader--;

    dr->topic = topic;
    dr->on_data_avail_listener = NULL;

    return dr;
}
#endif

#ifdef sDDS_TOPIC_HAS_PUB
rc_t DataSink_take_next_sample(DataReader _this, Data* data, DataInfo info)
{
    Msg msg = NULL;

    Topic topic = _this->topic;
    (void)info;

    rc_t ret = Topic_getNextMsg(topic, &msg);

    if (ret == SDDS_RT_NODATA) {
    	return SDDS_RT_NODATA;
    }

    // check if buffer is provided

    if (*data != NULL) {
    	// cpy the data
    	Data newData;
    	Msg_getData(msg, &newData);
    	(*topic->Data_cpy)(*data, newData);
    	// free the msg
    	Msg_init(msg, NULL);
    } else {
    	// TODO impl loan
    	Log_error("No buffer for datasample is provided. Data is lost\n");
    	return SDDS_RT_FAIL;
    }

    //TODO sample infos

    return SDDS_RT_OK;

}
#endif



rc_t submitData(void)
{
    if (msg != NULL){
	// add msg to topic incomming queue
	// msg->dir = SDDS_MSG_DIR_INCOMMING;
	// msg->isRead = false;
	// msg->isNew = true;
	// TODO
	// impl of app  callback
    	msg = NULL;
    }
    return SDDS_RT_OK;
}

#ifdef sDDS_TOPIC_HAS_PUB
rc_t parseData(NetBuffRef buff) {
	Topic topic;
	// check if there is a topic provided (should be)
	// data without topic are useless for this version!
	if (buff->curTopic == NULL) {
		// should not happen
		SNPS_discardSubMsg(buff);
		return SDDS_RT_FAIL;
	} else {
		topic = buff->curTopic;
	}
	// get msg from topic
	if (Topic_getFreeMsg(topic, &msg) != SDDS_RT_OK) {
		SNPS_discardSubMsg(buff);
		return SDDS_RT_FAIL;
	}
	//msg->isEmpty = false;
	// parse data
	Data newData;
	Msg_getData(msg, &newData);
	rc_t ret = SNPS_readData(buff, topic->Data_decode, newData);

	return ret;
}
#endif

rc_t checkDomain(NetBuffRef buff, domainid_t domain)
{
    if (TopicDB_checkDomain(domain) == false ) {
	SNPS_gotoNextSubMsg(buff, SNPS_T_DOMAIN);
    } else {
	buff->curDomain = domain;
    }

    return SDDS_RT_OK;
}

rc_t checkTopic(NetBuffRef buff, topicid_t topic)
{
    Topic t_ptr = TopicDB_getTopic(topic);
    if (t_ptr == NULL ) {
	SNPS_gotoNextSubMsg(buff, SNPS_T_TOPIC);
    } else {
	buff->curTopic = t_ptr;
    }

    return SDDS_RT_OK;
}

rc_t BuiltinTopic_writeDataReaders2Buf(NetBuffRef buf)
{
    SNPS_writeTopic(buf, SDDS_BUILTINTOPIC_SUBSCRIPTION_TOPIC_ID);
    for (uint8_t i = 0; i < sDDS_MAX_DATA_READERS - dataSink->remaining_datareader; i ++){
    	SNPS_writeData(buf, BuiltinTopicDataReader_encode, (Data) &(dataSink->readers[i]));
    }

    return SDDS_RT_OK;
}
rc_t BuiltinTopicDataReader_encode(byte_t* buff, Data data, size_t* size)
{
    DataReader dr = (DataReader) data;
    *size = 0;
    Marshalling_enc_uint8(buff+(*size), &(dr->topic->domain));
    *size += sizeof(domainid_t);
    Marshalling_enc_uint8(buff+(*size), &(dr->topic->id));
    *size += sizeof(topicid_t);

    return SDDS_RT_OK;
}

rc_t DataSink_set_on_data_avail_listener (DataReader _this, On_Data_Avail_Listener a_listener, const StatusMask sm)
{
	_this->on_data_avail_listener = a_listener;
	return SDDS_RT_OK;
}
