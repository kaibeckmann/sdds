/*
 * =====================================================================================
 *
 *       Filename:  DataSink.h
 *
 *    Description:  data sink class to receive data. Impl all datareader of the
 *    system
 *
 *        Version:  1.0
 *        Created:  02.03.2010 19:01:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kai Beckmann (kai), kai-oliver.beckmann@hs-rm.de
 *        Company:  Hochschule RheinMain - DOPSY Labor für verteilte Systeme
 *
 * =====================================================================================
 */

#ifndef  DATASINK_H_INC
#define  DATASINK_H_INC

#include "sDDS.h"
#include "BuiltinTopic.h"
#include "Log.h"
#include "Marshalling.h"
#include "NetBuffRef.h"
#include "SNPS.h"
#include "TopicDB.h"

#include <string.h>

struct _DataSink_t;
typedef struct _DataSink_t DataSink_t;
extern DataSink_t *dataSink;

rc_t DataSink_init(void);
DataReader_t * DataSink_create_datareader(Topic_t *topic, Qos qos, Listener listener, StatusMask sm);
rc_t DataSink_take_next_sample(DataReader_t *_this, Data* data, DataInfo info);
rc_t DataSink_processFrame(NetBuffRef_t *buff);
rc_t DataSink_set_on_data_avail_listener (
		DataReader_t *_this,
		On_Data_Avail_Listener listener,
		const StatusMask sm);

rc_t DataSink_printAddr();
rc_t DataSink_getAddr(struct SNPS_Address *address);

rc_t DataSink_getTopic(DDS_DCPSSubscription *st, topicid_t id, Topic_t **topic);

#endif   /* ----- #ifndef DATASINK_H_INC  ----- */
