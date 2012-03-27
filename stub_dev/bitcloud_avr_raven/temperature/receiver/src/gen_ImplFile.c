
#include "sDDS_Eval.h"
#include "sDDS/sDDS.h"
#include "sDDS/LocatorDB.h"
#include "sDDS/Network.h"
#include "sDDS/Topic.h"
#include "sDDS/TopicDB.h"
#include "sDDS/LocatorDB.h"
#include "sDDS/Msg.h"
#include "sDDS/DataSource.h"
#include "DDS/DDS_DCPS.h"
#include "sDDS/Marshalling.h"
#include "sDDS/TopicMarshalling.h"
#include "sDDS/DataSink.h"
#include "os-ssal/Memory.h"




Eval_TemperaturDataReader drDataReader;
DDS_Topic TempControlTopic;


Eval_Temperatur temperaturBufferPool[sDDS_TOPIC_APP_MSG_COUNT];




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
    
    
    drDataReader = (Eval_TemperaturDataReader) DataSink_create_datareader(myTempControlTopic, NULL, NULL, 0);
    

    return SDDS_RT_OK;
}






DDS_ReturnCode_t Eval_TemperaturDataReader_take_next_sample (
    Eval_TemperaturDataReader _this,
    Eval_Temperatur** data_values,
    DDS_SampleInfo *sample_info)
{
  //  char str[10];
  //  sprintf(str, "D%u%u%u", ((DR)_this)->topic->msg.pool[0].isEmpty,((DR)_this)->topic->msg.pool[0].dir,((DR)_this)->topic->msg.pool[0].isRead);
   // printText(str);
    // find new sample
    // Invoke the method of the datasink
    rc_t ret = DataSink_take_next_sample((DR) _this, (Data*) data_values, (DataInfo) sample_info);

    if (ret == SDDS_RT_NODATA)
        return DDS_RETCODE_NO_DATA;
    if (ret == SDDS_RT_OK)
        return DDS_RETCODE_OK;

    return DDS_RETCODE_ERROR;
}




rc_t TemperaturTopicMarshalling_decode(byte_t* buff, Data data, size_t* decoded_size)
{
    Eval_Temperatur* d = (Eval_Temperatur*) data;
    size_t size = 0;
    // should i check here if the size matches?
    // Foo is 6 byte = 4 (int) + 2 short
   // if (*size != 6){
    //    printf("Error? size mismatch\n");
   // }

	Marshalling_dec_int16((buff+size), &(d->temp));
	size += 2;

	Marshalling_dec_uint8((buff+size), &(d->ID));
	size += 1;

	Marshalling_dec_uint16((buff+size), &(d->position));
	size += 2;

   *decoded_size = size;
    return SDDS_RT_OK;
}
rc_t Data_cpy(Data dest, Data source)
{
    memcpy(dest, source, sizeof(Eval_Temperatur));
    return SDDS_RT_OK;
}







Topic Eval_TemperaturTopic_create(void) {
	Topic topic;
    topic = TopicDB_createTopic();

    topic->Data_decode = TemperaturTopicMarshalling_decode;
    topic->Data_cpy = Data_cpy;

    topic->domain = 15;
    topic->id = 1;
    

    Locator loc;
    LocatorDB_newLocator(&loc);
    // init the msg pool
    for (int i = 0; i < sDDS_TOPIC_APP_MSG_COUNT; i++){
        Msg_init(&(topic->msg.pool[i]), (Data) &(temperaturBufferPool[i]));
    }



    return topic;
	
}

