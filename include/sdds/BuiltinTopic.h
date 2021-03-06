/****************************************************************************
 * Copyright (C) 2017 RheinMain University of Applied Sciences              *
 *                                                                          *
 * This file is part of:                                                    *
 *      _____  _____   _____                                                *
 *     |  __ \|  __ \ / ____|                                               *
 *  ___| |  | | |  | | (___                                                 *
 * / __| |  | | |  | |\___ \                                                *
 * \__ \ |__| | |__| |____) |                                               *
 * |___/_____/|_____/|_____/                                                *
 *                                                                          *
 * This Source Code Form is subject to the terms of the Mozilla Public      *
 * License, v. 2.0. If a copy of the MPL was not distributed with this      *
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.                 *
 ****************************************************************************/

/**
 * @file      BuiltinTopic.h
 * @author    Kai Beckmann
 * @author    Kevin Sapper
 * @copyright MPL 2 
 * @see       https://github.com/sdds/sdds
 * TODO
 */



#ifndef BUILTINTOPIC_H_
#define BUILTINTOPIC_H_

#include "Locator.h"

#ifndef SDDS_BUILTIN_MULTICAST_ADDRESS
#define SDDS_BUILTIN_MULTICAST_ADDRESS          "ff02::10"
#endif

#ifndef SDDS_BUILTIN_PARTICIPANT_ADDRESS
#define SDDS_BUILTIN_PARTICIPANT_ADDRESS        "ff02::20"
#endif

#ifndef SDDS_BUILTIN_SUB_PUB_ADDRESS
#define SDDS_BUILTIN_SUB_PUB_ADDRESS            "ff02::30"
#endif

#ifndef SDDS_BUILTIN_TOPIC_ADDRESS
#define SDDS_BUILTIN_TOPIC_ADDRESS              "ff02::50"
#endif

#ifndef SDDS_BUILTIN_PAR_STATE_MSG_ADDRESS
#define SDDS_BUILTIN_PAR_STATE_MSG_ADDRESS      "ff02::60"	
#endif

#ifndef SDDS_BUILTIN_LOCATION_ADDRESS
#define SDDS_BUILTIN_LOCATION_ADDRESS           "ff02::70"
#endif

/* The last character is used for the terminating \0 */
#define DDS_TOPIC_NAME_SIZE 26
#define DDS_TOPIC_TYPE_SIZE 26

extern DDS_DataReader g_DCPSParticipant_reader;
extern DDS_DataWriter g_DCPSParticipant_writer;
extern DDS_Topic g_DCPSParticipant_topic;
//extern DCPSParticipant_data_t
// g_DCPSParticipant_pool[SDDS_TOPIC_APP_MSG_COUNT];

extern DDS_DataReader g_DCPSTopic_reader;
extern DDS_DataWriter g_DCPSTopic_writer;
extern DDS_Topic g_DCPSTopic_topic;
//extern DCPSTopic_data_t g_DCPSTopic_pool[SDDS_TOPIC_APP_MSG_COUNT];

extern DDS_DataReader g_DCPSPublication_reader;
extern DDS_DataWriter g_DCPSPublication_writer;
extern DDS_Topic g_DCPSPublication_topic;
//extern DCPSPublication_data_t
// g_DCPSPublication_pool[SDDS_TOPIC_APP_MSG_COUNT];

extern DDS_DataReader g_DCPSSubscription_reader;
extern DDS_DataWriter g_DCPSSubscription_writer;
extern DDS_Topic g_DCPSSubscription_topic;
//extern DCPSSubscription_data_t
// g_DCPSSubscription_pool[SDDS_TOPIC_APP_MSG_COUNT];

extern DDS_DataReader g_DCPSLocation_reader;
extern DDS_DataWriter g_DCPSLocation_writer;
extern DDS_Topic g_DCPSLocation_topic;
#define g_ParticipantVolatileMessage_reader g_ParticipantStatelessMessage_reader
#define g_ParticipantVolatileMessage_writer g_ParticipantStatelessMessage_writer

extern DDS_DataReader g_ParticipantStatelessMessage_reader;
extern DDS_DataWriter g_ParticipantStatelessMessage_writer;
extern DDS_Topic g_ParticipantStatelessMessage_topic;

extern SSW_NodeID_t BuiltinTopic_participantID;

typedef uint16_t BuiltinTopicKey_t;

struct DDS_DCPSParticipant_t {
    union {
        BuiltinTopicKey_t key;
        BuiltinTopicKey_t pkey;
        BuiltinTopicKey_t skey;
    };
    // IF BUILTINTOPIC AND QOS AND USERDATA
    // DDS_UserDataQosPolicy user_data;
    // ENDIF
};
typedef struct DDS_DCPSParticipant_t DDS_DCPSParticipant;

struct SDDS_DCPSParticipant_t {
    struct DDS_DCPSParticipant_t data;
    BuiltinTopicKey_t participantID;
    Locator_t* addr;
    Locator_t* srcAddr;
};
typedef struct SDDS_DCPSParticipant_t SDDS_DCPSParticipant;

DDS_ReturnCode_t
DDS_DCPSParticipantDataReader_take_next_sample(
                                               DDS_DataReader _this,
                                               DDS_DCPSParticipant** data_values,
                                               DDS_SampleInfo* sample_info);

DDS_ReturnCode_t
DDS_DCPSParticipantDataWriter_write(
                                    DDS_DataWriter _this,
                                    const DDS_DCPSParticipant* instance_data,
                                    const DDS_InstanceHandle_t handle
                                    );

struct DDS_DCPSTopic_t {
    union {
        BuiltinTopicKey_t key;
        BuiltinTopicKey_t pkey;
        BuiltinTopicKey_t skey;
    };
    DDS_char name[DDS_TOPIC_NAME_SIZE];
//    DDS_char type_name[DDS_TOPIC_TYPE_SIZE];
    // IF QOS AND Foo
    // TODO
    // ENDIF
};
typedef struct DDS_DCPSTopic_t DDS_DCPSTopic;

DDS_ReturnCode_t
DDS_DCPSTopicDataReader_take_next_sample(
                                         DDS_DataReader _this,
                                         DDS_DCPSTopic** data_values,
                                         DDS_SampleInfo* sample_info);

DDS_ReturnCode_t
DDS_DCPSTopicDataWriter_write(
                              DDS_DataWriter _this,
                              const DDS_DCPSTopic* instance_data,
                              const DDS_InstanceHandle_t handle
                              );


struct DDS_DCPSPublication_t {
    union {
        BuiltinTopicKey_t key;
        BuiltinTopicKey_t pkey;
        BuiltinTopicKey_t skey;
    };
    BuiltinTopicKey_t participant_key;
    uint16_t topic_id;
    Locator_t* srcAddr;
//    DDS_char topic_name[DDS_TOPIC_NAME_SIZE];
//    DDS_char type_name[DDS_TOPIC_TYPE_SIZE];
    // IF QOS AND FOO
    // TODO
    // ENDIF
};
typedef struct DDS_DCPSPublication_t DDS_DCPSPublication;


DDS_ReturnCode_t
DDS_DCPSPublicationDataReader_take_next_sample(
                                               DDS_DataReader _this,
                                               DDS_DCPSPublication** data_values,
                                               DDS_SampleInfo* sample_info);

DDS_ReturnCode_t
DDS_DCPSPublicationDataWriter_write(
                                    DDS_DataWriter _this,
                                    const DDS_DCPSPublication* instance_data,
                                    const DDS_InstanceHandle_t handle
                                    );


struct DDS_DCPSSubscription_t {
    union {
        BuiltinTopicKey_t key;
        BuiltinTopicKey_t pkey;
        BuiltinTopicKey_t skey;
    };
    BuiltinTopicKey_t participant_key;
    uint16_t topic_id;
    //    DDS_char topic_name[DDS_TOPIC_NAME_SIZE];
//    DDS_char type_name[DDS_TOPIC_TYPE_SIZE];
    // IF QOS AND FOO
    // TODO
    // ENDIF
};
typedef struct DDS_DCPSSubscription_t DDS_DCPSSubscription;

struct SDDS_DCPSSubscription_t {
    struct DDS_DCPSSubscription_t data;
    Locator_t* addr;
};
typedef struct SDDS_DCPSSubscription_t SDDS_DCPSSubscription;

DDS_ReturnCode_t
DDS_DCPSSubscriptionDataReader_take_next_sample(
                                                DDS_DataReader _this,
                                                DDS_DCPSSubscription** data_values,
                                                DDS_SampleInfo* sample_info);

DDS_ReturnCode_t
DDS_DCPSSubscriptionDataWriter_write(
                                     DDS_DataWriter _this,
                                     const DDS_DCPSSubscription* instance_data,
                                     const DDS_InstanceHandle_t handle
                                     );

/* Security */
#define CLASS_ID_STRLEN 16
#define PROPERTIES_NUM 3
#define PROPERTY_KEY_STRLEN 16
#define PROPERTY_VAL_STRLEN 50

struct Property_t {
    DDS_char key[PROPERTY_KEY_STRLEN];
    DDS_char value[PROPERTY_VAL_STRLEN];
};

typedef struct Property_t Property;

struct DataHolder_t {
    DDS_char class_id[CLASS_ID_STRLEN];
    Property props[PROPERTIES_NUM];
};

typedef struct DataHolder_t DataHolder;

struct ParticipantGenericMessage_t {
    union {
        BuiltinTopicKey_t key;
        BuiltinTopicKey_t pkey;
        BuiltinTopicKey_t skey;
    };
    uint16_t msgid;
    DDS_char message_class_id[CLASS_ID_STRLEN];
    DataHolder message_data;
};

typedef struct ParticipantGenericMessage_t DDS_ParticipantStatelessMessage;
typedef struct ParticipantGenericMessage_t DDS_ParticipantVolatileMessage;

#define DDS_ParticipantVolatileMessageDataReader_take_next_sample DDS_ParticipantStatelessMessageDataReader_take_next_sample
#define DDS_ParticipantVolatileMessageDataWriter_write DDS_ParticipantStatelessMessageDataWriter_write

DDS_ReturnCode_t
DDS_ParticipantStatelessMessageDataReader_take_next_sample(
                                               DDS_DataReader _this,
                                               DDS_ParticipantStatelessMessage** data_values,
                                               DDS_SampleInfo* sample_info);

DDS_ReturnCode_t
DDS_ParticipantStatelessMessageDataWriter_write(
                                    DDS_DataWriter _this,
                                    const DDS_ParticipantStatelessMessage* instance_data,
                                    const DDS_InstanceHandle_t handle
                                    );

struct SDDS_DCPSLocation_t {
    union {
        BuiltinTopicKey_t key;
        BuiltinTopicKey_t pkey;
    };
    union {
        DDS_unsigned_short device;
        DDS_unsigned_short skey;
    };
    DDS_unsigned_short x;
    DDS_unsigned_short y;
    DDS_unsigned_short z;
    DDS_unsigned_short width;
    DDS_unsigned_short length;
    DDS_short expiration;
    DDS_short age;
};
typedef struct SDDS_DCPSLocation_t SDDS_DCPSLocation;

DDS_ReturnCode_t
DDS_DCPSLocationDataReader_take_next_sample(
                                               DDS_DataReader _this,
                                               SDDS_DCPSLocation** data_values,
                                               DDS_SampleInfo* sample_info);

DDS_ReturnCode_t
DDS_DCPSLocationDataWriter_write(
                                    DDS_DataWriter _this,
                                    const SDDS_DCPSLocation* instance_data,
                                    const DDS_InstanceHandle_t handle
                                    );

// ENDIF APP + BUILTINTOPIC

#define DDS_DCPS_PARTICIPANT_DOMAIN 0x1
#define DDS_DCPS_PARTICIPANT_TOPIC 0x01
#define DDS_DCPS_TOPIC_DOMAIN 0x1
#define DDS_DCPS_TOPIC_TOPIC 0x02
#define DDS_DCPS_PUBLICATION_DOMAIN 0x1
#define DDS_DCPS_PUBLICATION_TOPIC 0x03
#define DDS_DCPS_SUBSCRIPTION_DOMAIN 0x1
#define DDS_DCPS_SUBSCRIPTION_TOPIC 0x04
#define DDS_PARTICIPANT_STATELESS_MESSAGE_DOMAIN 0x1
#define DDS_PARTICIPANT_STATELESS_MESSAGE_TOPIC 0x5
#define SDDS_DCPS_LOCATION_DOMAIN 0x1
#define SDDS_DCPS_LOCATION_TOPIC 0x06

rc_t
BuiltinTopic_init(void);

rc_t
BuiltinTopic_publishAll(void);

rc_t
BuiltinTopic_publishDP(void);

rc_t
BuiltinTopic_publishPub(void);

rc_t
BuiltinTopic_publishSub(void);

rc_t
BuiltinTopic_writeDomainParticipant2Buf(NetBuffRef_t* buf);
rc_t
BuiltinTopic_writeTopics2Buf(NetBuffRef_t* buf);
rc_t
BuiltinTopic_writeDataWriters2Buf(NetBuffRef_t* buf);
rc_t
BuiltinTopic_writeDataReaders2Buf(NetBuffRef_t* buf);


bool
BuildinTopic_isBuiltinTopic(topicid_t tID, domainid_t dID);

void
BuiltinTopic_printSubPool();
void
BuiltinTopic_printTopicAddr();

#endif /* BUILTINTOPIC_H_ */
