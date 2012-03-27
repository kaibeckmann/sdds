

#include "sDDS_Eval.h"

#include "sDDS/Topic.h"
#include "sDDS/Network.h"
#include "sDDS/LocatorDB.h"
#include "sDDS/DataSource.h"
#include "sDDS/DataSink.h"
#include "sDDS/Marshalling.h"
#include "sDDS/TopicDB.h"



Eval_TemperaturDataWriter dwDataWriter;
DDS_Topic TempControlTopic;






Topic Eval_TemperaturTopic_create(void);




rc_t sDDS_init()
{

    LocatorDB_init();
    Network_init();
    DataSource_init();
    //ds
    // init datasink
    DataSink_init();
    
    // create the topics used within this appication
    
    TempControlTopic = (DDS_Topic) Eval_TemperaturTopic_create();
    Topic myTempControlTopic = (Topic)TempControlTopic; 
    
    // create the datawriter used within this application
    
    dwDataWriter = (Eval_TemperaturDataWriter) DataSource_create_datawriter( myTempControlTopic, NULL, NULL, NULL);
    
    

    return SDDS_RT_OK;
}





DDS_ReturnCode_t Eval_TemperaturDataWriter_write(
    Eval_TemperaturDataWriter _this,
    const Eval_Temperatur* instance_data,
    const DDS_InstanceHandle_t handle)
{

    rc_t rc; 

    rc = DataSource_write((DW) _this, (Data) instance_data, (void*) handle);
    if (rc == SDDS_RT_OK) {
        return DDS_RETCODE_OK;
    } else {
        return DDS_RETCODE_ERROR;
    }

}




rc_t TemperaturTopicMarshalling_encode(byte_t* buff, Data data, size_t* encoded_size)
{

    Eval_Temperatur* d = (Eval_Temperatur*) data;
    size_t size = 0;

	Marshalling_enc_int16((buff+size), &(d->temp));
	size += 2;

	Marshalling_enc_uint8((buff+size), &(d->ID));
	size += 1;

	Marshalling_enc_uint16((buff+size), &(d->position));
	size += 2;

	*encoded_size = size;

    return SDDS_RT_OK;
}








Topic Eval_TemperaturTopic_create(void) {
	Topic topic;
    topic = TopicDB_createTopic();
    topic->Data_encode = TemperaturTopicMarshalling_encode;


    topic->domain = 15;
    topic->id = 1;
    

    Locator loc;
    LocatorDB_newLocator(&loc);

    topic->dsinks.list = loc;


    return topic;
	
}



