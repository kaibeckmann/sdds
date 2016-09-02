/*
 * SubscriptionManager.c
 *
 *  Created on: Aug 29, 2016
 *      Author: o_dedi
 */

#include "sDDS.h"
#include "SubscriptionManager.h"
#include "ManagementTopic.h"
#include "Locator.h"
#include "FilterEvaluator.h"
#include "ManagementTopicPublicationService.h"

#ifdef FEATURE_SDDS_SUBSCRIPION_MANAGER_ENABLED

extern GeometryStore_t g_geometryStore;

rc_t
SubscriptionManager_init(SubscriptionManager_t* self) {
    return SubscriptionGraph_init(&self->subscriptionGraph);
}

rc_t
SubscriptionManager_evalFilteredSubscription(SubscriptionManager_t* self, DeviceLocation_t* sample) {
    List_t* edges = self->subscriptionGraph.edges;
    DirectedEdge_t* edge = (DirectedEdge_t*) edges->first_fn(edges);
    while (edge != NULL) {
        rc_t ret = FilterEvaluator_evalSubscription(sample, edge);
        if ((ret == SDDS_RT_FAIL)) {
            ret = SubscriptionGraph_pauseSubscription(&self->subscriptionGraph, edge);
            if (ret != SDDS_RT_OK) {
                Log_error("Unable to pause subscription.\n");
            }
        }
        else {
            ret = SubscriptionGraph_resumeSubscription(&self->subscriptionGraph, edge);
            if (ret != SDDS_RT_OK) {
                Log_error("Unable to resume subscription.\n");
            }
        }
        SDDS_DCPSManagement data;
        data.participant = edge->publisher->id;
        strcpy(data.mKey, SDDS_MANAGEMENT_TOPIC_KEY_SET_SUBSCRIPTION_STATE);
        int size = 0;
        ret =  Marshalling_dec_uint8((byte_t*) data.mValue + size, &edge->topic->id);
        size += sizeof(edge->topic->id);
        ret =  Marshalling_dec_uint16((byte_t*) data.mValue + size, &edge->publisher->id);
        size += sizeof(edge->publisher->id);
        ret =  Marshalling_dec_uint8((byte_t*) data.mValue + size, (uint8_t*)&edge->sate);

        ret = ManagementTopicPublicationService_publishManagementDirective(&data, edge->publisher->addr);
        if (ret != SDDS_RT_OK) {
            Log_error("Unable to publish ManagementDirective.\n");
        }

        edge = (DirectedEdge_t*) edges->next_fn(edges);
    }
}

rc_t
SubscriptionManager_handleParticipant(SubscriptionManager_t* self, SDDS_DCPSParticipant* sample) {
    ParticipantNode_t* node = SubscriptionGraph_containsParticipantNode(&self->subscriptionGraph, sample->data.key);
    if (node == NULL) {
        ParticipantNode_t* node = SubscriptionGraph_createParticipantNode(&self->subscriptionGraph);
        Locator_upRef(sample->addr);
        node->addr = sample->addr;
        node->id = sample->data.key;

        List_t* nodes = self->subscriptionGraph.nodes;
        rc_t ret = nodes->add_fn(nodes, node);
        if (ret != SDDS_RT_OK) {
            Locator_downRef(sample->addr);
            SubscriptionGraph_freeParticipantNode(&self->subscriptionGraph, node);
            return SDDS_RT_FAIL;
        }
    }
    return SDDS_RT_OK;
}

rc_t
SubscriptionManager_handlePupblication(SubscriptionManager_t* self, DDS_DCPSPublication* sample) {
    ParticipantNode_t* node = SubscriptionGraph_containsParticipantNode(&self->subscriptionGraph, sample->participant_key);
    if (node != NULL) {
        node->roleMask |= SDDS_PARTICIPANT_ROLE_PUB;

        List_t* topics = node->topics;
        Topic_t* topic = (Topic_t*) topics->first_fn(topics);
        while (topic != NULL && topic->id != sample->topic_id) {
            topic = (Topic_t*) topics->next_fn(topics);
        }

        if (topic == NULL) {
            return topics->add_fn(topics, TopicDB_getTopic(sample->topic_id));
        }
    }
    return SDDS_RT_FAIL;
}

rc_t
SubscriptionManager_handleSubscription(SubscriptionManager_t* self, SDDS_DCPSSubscription* sample) {
    ParticipantNode_t* sub = SubscriptionGraph_containsParticipantNode(&self->subscriptionGraph, sample->data.participant_key);

    List_t* nodes = self->subscriptionGraph.nodes;
    ParticipantNode_t* node = nodes->first_fn(nodes);
    while (node != NULL) {
        DirectedEdge_t* edge = SubscriptionGraph_containsSubscription(&self->subscriptionGraph, node->id, sample->data.participant_key, sample->data.topic_id);
        if (edge == NULL) {
            Topic_t* topic = TopicDB_getTopic(sample->data.topic_id);
            if (topic == NULL) {
                return SDDS_RT_FAIL;
            }
            edge = SubscriptionGraph_establishSubscription(&self->subscriptionGraph, node, sub, topic);
            if (edge == NULL) {
                return SDDS_RT_FAIL;
            }
        }
    }

    return SDDS_RT_OK;
}

rc_t
SubscriptionManager_registerFilter(SubscriptionManager_t* self, SDDS_DCPSManagement* sample) {
    SDDS_DCPSManagement data;
    data.participant = SDDS_MANAGEMENT_TOPIC_ALL_PARTICIPANTS;
    strcpy(data.mKey, SDDS_MANAGEMENT_TOPIC_KEY_SEND_FILTER_EXPRESSION);

    int size = 0;

    topicid_t topicID;
    Marshalling_dec_uint8(data.mValue+size, &topicID);
    size += sizeof(topicID);

    SSW_NodeID_t participantID;

    Marshalling_dec_uint16(data.mValue+size, &participantID);
    size += sizeof(participantID);

    Topic_t* topic = TopicDB_getTopic(topicID);
    LocationFilteredTopic_t* locTopic = malloc(sizeof(LocationFilteredTopic_t));
    rc_t ret = LocationFilteredTopic_create(locTopic, topic, NULL, &g_geometryStore);

    Marshalling_dec_uint8(data.mValue+size, &locTopic->expressionLength);
    size += sizeof(locTopic->expressionLength);

    Marshalling_enc_string(data.mValue+size, locTopic->filterExpression, locTopic->expressionLength);

    List_t* edges = self->subscriptionGraph.edges;
    DirectedEdge_t* edge = (DirectedEdge_t*) edges->first_fn(edges);
    while (edge != NULL) {
        if ((edge->subscriber->id == participantID) && (edge->topic->id == topic->id)) {
            ret = SubscriptionGraph_registerFilter(edge, locTopic);
            if (ret != SDDS_RT_OK) {
                Log_error("Unable to register Filter.\n");
            }
            edge = (DirectedEdge_t*) edges->next_fn(edges);
        }
    }

    return SDDS_RT_OK;
}

#endif
