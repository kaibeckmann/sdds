/* latency_publisher.c

   A publication of data of type latency

   This file is derived from code automatically generated by the rtiddsgen 
   command:

   rtiddsgen -language C -example <arch> latency.idl

   Example publication of type latency automatically generated by 
   'rtiddsgen'. To test them follow these steps:

   (1) Compile this file and the example subscription.

   (2) Start the subscription with the command
       objs/<arch>/latency_subscriber <domain_id> <msg_count>

   (3) Start the publication with the command
       objs/<arch>/latency_publisher <domain_id> <msg_count>

   (4) [Optional] Specify the list of discovery initial peers and 
       multicast receive addresses via an environment variable or a file 
       (in the current working directory) called NDDS_DISCOVERY_PEERS. 
       
   You can run any number of publishers and subscribers programs, and can 
   add and remove them dynamically from the domain.
              
                                   
   Example:
        
       To run the example application on domain <domain_id>:
                                  
       On Unix: 
       
       objs/<arch>/latency_publisher <domain_id> 
       objs/<arch>/latency_subscriber <domain_id> 
                            
       On Windows:
       
       objs\<arch>\latency_publisher <domain_id>  
       objs\<arch>\latency_subscriber <domain_id>   
       
       
modification history
------------ -------       
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "ndds/ndds_c.h"
#include "latency.h"
#include "latencySupport.h"

static int count = 0;
static FILE* log = NULL;

/* LatencyEcho Listener */
void latencyEchoListener_on_requested_deadline_missed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedDeadlineMissedStatus *status)
{
}

void latencyEchoListener_on_requested_incompatible_qos(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedIncompatibleQosStatus *status)
{
}

void latencyEchoListener_on_sample_rejected(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleRejectedStatus *status)
{
}

void latencyEchoListener_on_liveliness_changed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_LivelinessChangedStatus *status)
{
}

void latencyEchoListener_on_sample_lost(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleLostStatus *status)
{
}

void latencyEchoListener_on_subscription_matched(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SubscriptionMatchedStatus *status)
{
}

void latencyEchoListener_on_data_available(
    void* listener_data,
    DDS_DataReader* reader)
{
    latencyEchoDataReader *latencyEcho_reader = NULL;
    struct latencyEchoSeq data_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;
    DDS_ReturnCode_t retcode;
    int i;

    latencyEcho_reader = latencyEchoDataReader_narrow(reader);
    if (latencyEcho_reader == NULL) {
        printf("DataReader narrow error\n");
        return;
    }

    retcode = latencyEchoDataReader_take(
        latencyEcho_reader,
        &data_seq, &info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
    if (retcode == DDS_RETCODE_NO_DATA) {
        return;
    } else if (retcode != DDS_RETCODE_OK) {
        printf("take error %d\n", retcode);
        return;
    }

    for (i = 0; i < latencyEchoSeq_get_length(&data_seq); ++i) {
        if (DDS_SampleInfoSeq_get_reference(&info_seq, i)->valid_data) {
	        if (count > 0) {
                static struct timeval end;
	            gettimeofday(&end, NULL);
                long long end_time = end.tv_sec * 1000000 + end.tv_usec;
                latencyEcho* inst = latencyEchoSeq_get_reference(&data_seq, i);
	            long duration = ((end_time - inst->time) / 2);
	            fprintf(log, "%ld\n", duration);
            }
	        count++;
        }
    }

    retcode = latencyEchoDataReader_return_loan(
        latencyEcho_reader,
        &data_seq, &info_seq);
    if (retcode != DDS_RETCODE_OK) {
        printf("return loan error %d\n", retcode);
    }
}

/* Delete all entities */
static int host_shutdown(
    DDS_DomainParticipant *participant)
{
    DDS_ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = DDS_DomainParticipant_delete_contained_entities(participant);
        if (retcode != DDS_RETCODE_OK) {
            printf("delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = DDS_DomainParticipantFactory_delete_participant(
            DDS_TheParticipantFactory, participant);
        if (retcode != DDS_RETCODE_OK) {
            printf("delete_participant error %d\n", retcode);
            status = -1;
        }
    }

    /* RTI Connext provides finalize_instance() method on
       domain participant factory for people who want to release memory used
       by the participant factory. Uncomment the following block of code for
       clean destruction of the singleton. */
/*
    retcode = DDS_DomainParticipantFactory_finalize_instance();
    if (retcode != DDS_RETCODE_OK) {
        printf("finalize_instance error %d\n", retcode);
        status = -1;
    }
*/

    return status;
}

static int host_main(int domainId, int msg_count)
{
    DDS_DomainParticipant *participant = NULL;

    DDS_Publisher *publisher = NULL;
    DDS_Subscriber *subscriber = NULL;

    DDS_Topic *topic_latency = NULL;
    DDS_Topic *topic_latencyEcho = NULL;

    DDS_DataWriter *writer = NULL;
    latencyDataWriter *latency_writer = NULL;

    struct DDS_DataReaderListener reader_listener = DDS_DataReaderListener_INITIALIZER;
    DDS_DataReader *reader = NULL;

    latency *instance_latency = NULL;

    DDS_ReturnCode_t retcode;

    DDS_InstanceHandle_t instance_handle = DDS_HANDLE_NIL;

    const char *type_name_latency = NULL;
    const char *type_name_latencyEcho = NULL;

    struct DDS_Duration_t send_period = {0,10};

    /* To customize participant QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    participant = DDS_DomainParticipantFactory_create_participant(
        DDS_TheParticipantFactory, domainId, &DDS_PARTICIPANT_QOS_DEFAULT,
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        printf("create_participant error\n");
        host_shutdown(participant);
        return -1;
    }

    /* To customize publisher QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    publisher = DDS_DomainParticipant_create_publisher(
        participant, &DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        printf("create_publisher error\n");
        host_shutdown(participant);
        return -1;
    }

    /* To customize subscriber QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    subscriber = DDS_DomainParticipant_create_subscriber(
        participant, &DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        printf("create_subscriber error\n");
        host_shutdown(participant);
        return -1;
    }

    /* Register type before creating topic */
    type_name_latency = latencyTypeSupport_get_type_name();
    retcode = latencyTypeSupport_register_type(
        participant, type_name_latency);
    if (retcode != DDS_RETCODE_OK) {
        printf("register_type error %d\n", retcode);
        host_shutdown(participant);
        return -1;
    }

    /* Register the type before creating the topic */
    type_name_latencyEcho = latencyEchoTypeSupport_get_type_name();
    retcode = latencyEchoTypeSupport_register_type(participant, type_name_latencyEcho);
    if (retcode != DDS_RETCODE_OK) {
        printf("register_type error %d\n", retcode);
        host_shutdown(participant);
        return -1;
    }

    /* To customize topic QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    topic_latency = DDS_DomainParticipant_create_topic(
        participant, "latency",
        type_name_latency, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic_latency == NULL) {
        printf("latency create_topic error\n");
        host_shutdown(participant);
        return -1;
    }

    /* To customize topic QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    topic_latencyEcho = DDS_DomainParticipant_create_topic(
        participant, "latencyEcho",
        type_name_latencyEcho, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic_latencyEcho == NULL) {
        printf("latencyEcho create_topic error\n");
        host_shutdown(participant);
        return -1;
    }

    /* To customize data writer QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    writer = DDS_Publisher_create_datawriter(
        publisher, topic_latency,
        &DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (writer == NULL) {
        printf("create_datawriter error\n");
        host_shutdown(participant);
        return -1;
    }
    latency_writer = latencyDataWriter_narrow(writer);
    if (latency_writer == NULL) {
        printf("DataWriter narrow error\n");
        host_shutdown(participant);
        return -1;
    }

    /* Set up a data reader listener */
    reader_listener.on_requested_deadline_missed  =
        latencyEchoListener_on_requested_deadline_missed;
    reader_listener.on_requested_incompatible_qos =
        latencyEchoListener_on_requested_incompatible_qos;
    reader_listener.on_sample_rejected =
        latencyEchoListener_on_sample_rejected;
    reader_listener.on_liveliness_changed =
        latencyEchoListener_on_liveliness_changed;
    reader_listener.on_sample_lost =
        latencyEchoListener_on_sample_lost;
    reader_listener.on_subscription_matched =
        latencyEchoListener_on_subscription_matched;
    reader_listener.on_data_available =
        latencyEchoListener_on_data_available;

    /* To customize data reader QoS, use 
       the configuration file USER_QOS_PROFILES.xml */
    reader = DDS_Subscriber_create_datareader(
        subscriber, DDS_Topic_as_topicdescription(topic_latencyEcho),
        &DDS_DATAREADER_QOS_DEFAULT, &reader_listener, DDS_STATUS_MASK_ALL);
    if (reader == NULL) {
        printf("create_datareader error\n");
        host_shutdown(participant);
        return -1;
    }

    /* Create data sample for writing */

    instance_latency = latencyTypeSupport_create_data_ex(DDS_BOOLEAN_TRUE);
    
    if (instance_latency == NULL) {
        printf("latencyTypeSupport_create_data error\n");
        host_shutdown(participant);
        return -1;
    }

    /* For a data type that has a key, if the same instance is going to be
       written multiple times, initialize the key here
       and register the keyed instance prior to writing */
/*
    instance_handle = latencyDataWriter_register_instance(
        latency_writer, instance_latency);
*/

    /* Main loop */
    while (count < msg_count+1) {

        /* Modify the data to be written here */
	    memset(instance_latency->data, 'x', 32);

	    static struct timeval start;
	    gettimeofday(&start, NULL);
	    long long start_time = (start.tv_sec * 1000000 + start.tv_usec);

        instance_latency->time = start_time;

        /* Write data */
        retcode = latencyDataWriter_write(
            latency_writer, instance_latency, &instance_handle);
        if (retcode != DDS_RETCODE_OK) {
            printf("write error %d\n", retcode);
        }

        NDDS_Utility_sleep(&send_period);
    }
    
/*
    retcode = latencyDataWriter_unregister_instance(
        latency_writer, instance_latency, &instance_handle);
    if (retcode != DDS_RETCODE_OK) {
        printf("unregister instance error %d\n", retcode);
    }
*/

    /* Delete data sample */
    retcode = latencyTypeSupport_delete_data_ex(instance_latency, DDS_BOOLEAN_TRUE);
    if (retcode != DDS_RETCODE_OK) {
        printf("latencyTypeSupport_delete_data error %d\n", retcode);
    }

    /* Cleanup and delete delete all entities */         
    return host_shutdown(participant);
}

int main(int argc, char *argv[])
{
    int domainId = 0;
    int msg_count = 0; 
    char *latency_log = NULL;

    if (argc < 3) {
        printf("usage: %s <msg_count> <log_file>\n", argv[0]);
        return -1;
    }

    msg_count = atoi(argv[1]);
    latency_log = argv[2];
    log = fopen(latency_log, "w+");
    if (log == NULL) {
        printf("fopen: %s\n", strerror(errno));
        return -1;
    }
    
    /* Uncomment this to turn on additional logging
    NDDS_Config_Logger_set_verbosity_by_category(
        NDDS_Config_Logger_get_instance(),
        NDDS_CONFIG_LOG_CATEGORY_API, 
        NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    */
        
    int ret = host_main(domainId, msg_count);

    fclose(log);
    return ret;
}
