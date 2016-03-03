/*  =========================================================================
    History - Subscriber sample queue.

    Copyright (c) the Contributors as noted in the AUTHORS file.

    This file is part of sDDS:
    http://wwwvs.cs.hs-rm.de.
    =========================================================================
 */

/*
   @header
    History - This class queues samples of one instance for a DataReader.
   @discuss
   @end
 */

#include "sDDS.h"

#ifdef SDDS_HAS_QOS_RELIABILITY
static rc_t
s_History_checkSeqNr(History_t* self, Topic_t* topic, Locator_t* loc, SDDS_SEQNR_BIGGEST_TYPE seqNr);
#endif

//  ---------------------------------------------------------------------------
//  Initializes this class

rc_t
sdds_History_init() {
    return SDDS_RT_OK;
}

//  ---------------------------------------------------------------------------
//  Setup an instance of this class

rc_t
sdds_History_setup(History_t* self, Sample_t* samples, unsigned int depth) {
    assert(self);
    assert(samples);
    self->samples = samples;
    self->depth = depth;
    self->in_needle = 0;
    self->out_needle = depth;
#ifdef SDDS_HAS_QOS_RELIABILITY
    for (int index = 0; index < depth; index++){
        self->samples[index].seqNr = 0;
    }
#endif
    return SDDS_RT_OK;
}


static inline bool_t
s_History_full (History_t* self)
{
    if (self->in_needle == self->depth) {
        return true;
    }
    return false;
}


//  ---------------------------------------------------------------------------
//  Try to enqueue a sample as buffer into the history. If the history is full
//  this call will discard the oldest sample in case of RELIABILITY best effort
//  and block in case of RELIABILITY reliable until samples are taken out. If
//  the buffer is going to be enqueued it will be decoded.

#ifdef SDDS_HAS_QOS_RELIABILITY
rc_t
sdds_History_enqueue(History_t* self, NetBuffRef_t* buff, SDDS_SEQNR_BIGGEST_TYPE seqNr) {
#else
rc_t
sdds_History_enqueue(History_t* self, NetBuffRef_t* buff) {
#endif
    assert(self);
    assert(buff);
#ifdef FEATURE_SDDS_TRACING_ENABLED
#   if defined (FEATURE_SDDS_TRACING_RECV_NORMAL) || defined (FEATURE_SDDS_TRACING_RECV_ISOLATED)
#       ifdef FEATURE_SDDS_TRACING_HISTORY_ENQUEUE
    Trace_point(SDDS_TRACE_EVENT_HISTORY_ENQUEUE);
#       endif
#   endif
#endif
    if (s_History_full (self)) {
#if (defined(SDDS_HAS_QOS_RELIABILITY) && defined(SDDS_HAS_QOS_RELIABILITY_KIND_BESTEFFORT)) \
    || !defined(SDDS_HAS_QOS_RELIABILITY)
        //  Dequeue the oldest item in the History and proceed.
        (void *) sdds_History_dequeue(self);
#else
        return SDDS_RT_FAIL;
#endif
    }
    //  Insert sample into queue
    Topic_t* topic = buff->curTopic;
    Locator_t* loc = (Locator_t*) buff->locators->first_fn(buff->locators);
    Locator_upRef(loc);
#ifdef SDDS_HAS_QOS_RELIABILITY
    //  Check validity of sequence number
    if (topic->seqNrBitSize > 0){ // topic has seqNr
        if (s_History_checkSeqNr(self, topic, loc, seqNr) == SDDS_RT_OK){
            self->samples[self->in_needle].seqNr = seqNr;
        } else {
            SNPS_discardSubMsg(buff);
            Locator_downRef(loc);
            return SDDS_RT_FAIL;
        }
#   ifdef UTILS_DEBUG
        if (topic->seqNrBitSize > 0){
            sdds_History_print(self);
        }
#   endif
    }
#endif
    rc_t ret = SNPS_readData(buff, topic->Data_decode, (Data) self->samples[self->in_needle].data);
    if (ret == SDDS_RT_FAIL) {
        return ret;
    }
    self->samples[self->in_needle].instance = loc;
    //  Move the input needle to the next free slot. If the input needle is at
    //  the end of the array move it to the beginning.
    unsigned int in_needle_prev = self->in_needle;
    self->in_needle++;
    if (self->in_needle == self->depth) {
        self->in_needle = 0;
    }
    //  Move the input needle to depth to indicate that the queue is full.
    if (self->in_needle == self->out_needle) {
        self->in_needle = self->depth;
    }
    //  If the queue was previously empty set the output needle.
    if (self->out_needle == self->depth) {
        self->out_needle = in_needle_prev;
    }
    return SDDS_RT_OK;
}


//  ---------------------------------------------------------------------------
//  Takes the oldest sample out of the queue. Returns a pointer to the sample if
//  the history is not empty, otherwise NULL.

Sample_t*
sdds_History_dequeue(History_t* self) {
    assert(self);
    if (self->out_needle == self->depth) {
        return NULL;
    }
    //  Remove sample from queue
    Sample_t* sample = &self->samples[self->out_needle];
    Locator_downRef(sample->instance);
    //  Move the output needle to the next sample slot. If the output needle is
    //  at the end of the array move it to the beginning.
    unsigned int out_needle_prev = self->out_needle;
    self->out_needle++;
    if (self->out_needle == self->depth) {
        self->out_needle = 0;
    }
    //  Move the output needle to depth to indicate that the queue is empty.
    if (self->out_needle == self->in_needle) {
        self->out_needle = self->depth;
    }
    //  If the queue was previously full set the input needle.
    if (self->in_needle == self->depth) {
        self->in_needle = out_needle_prev;
    }
    return sample;
}


#ifdef SDDS_HAS_QOS_RELIABILITY
static inline rc_t
s_History_checkSeqNr(History_t* self, Topic_t* topic, Locator_t* loc, SDDS_SEQNR_BIGGEST_TYPE seqNr) {
    uint8_t indexOfHighestSeqNrForLoc = 0;

    // check if locator is already in hashmap
    bool isInHashmap = false;
    for (int index=0; index<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; index++){
        if (self->qos_locator[index] == loc){
            indexOfHighestSeqNrForLoc = index;
            isInHashmap = true;
            break;
        }
    }

    // if not already in hashmap, there has to be at least one free slot left
    if (!isInHashmap){
        for (int index=0; index<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; index++){
            if (self->qos_locator[index] == 0){
                self->qos_locator[index] = loc;
                self->highestSeqNr[index] = seqNr;
                return SDDS_RT_OK;
            }
        }
    }

    // check the validity of the new seqNr
    switch(topic->seqNrBitSize){
        case (SDDS_QOS_RELIABILITY_SEQSIZE_BASIC):
            if ((self->highestSeqNr[indexOfHighestSeqNrForLoc] == 0)
            ||  (seqNr > self->highestSeqNr[indexOfHighestSeqNrForLoc])
            ||  (self->highestSeqNr[indexOfHighestSeqNrForLoc] == 15)) {
                return SDDS_RT_OK;
            }
           break;
#   if SDDS_SEQNR_BIGGEST_TYPE_BITSIZE >= SDDS_QOS_RELIABILITY_SEQSIZE_SMALL
        case (SDDS_QOS_RELIABILITY_SEQSIZE_SMALL):
            if ((self->highestSeqNr[indexOfHighestSeqNrForLoc] == 0)
            ||  (seqNr > self->highestSeqNr[indexOfHighestSeqNrForLoc])
            ||  (self->highestSeqNr[indexOfHighestSeqNrForLoc] == 255)) {
                return SDDS_RT_OK;
            }
           break;
#   endif
#   if SDDS_SEQNR_BIGGEST_TYPE_BITSIZE >= SDDS_QOS_RELIABILITY_SEQSIZE_BIG
        case (SDDS_QOS_RELIABILITY_SEQSIZE_BIG):
            if ((self->highestSeqNr[indexOfHighestSeqNrForLoc] == 0)
            ||  (seqNr > self->highestSeqNr[indexOfHighestSeqNrForLoc])
            ||  (self->highestSeqNr[indexOfHighestSeqNrForLoc] == 65536)) {
                return SDDS_RT_OK;
            }
           break;
#   endif
#   if SDDS_SEQNR_BIGGEST_TYPE_BITSIZE == SDDS_QOS_RELIABILITY_SEQSIZE_HUGE
        case (SDDS_QOS_RELIABILITY_SEQSIZE_HUGE):
            if ((self->highestSeqNr[indexOfHighestSeqNrForLoc] == 0)
            ||  (seqNr > self->highestSeqNr[indexOfHighestSeqNrForLoc])
            ||  (self->highestSeqNr[indexOfHighestSeqNrForLoc] == 4294967296)) {
                return SDDS_RT_OK;
            }
           break;
#   endif
    }

    return SDDS_RT_FAIL;
}
#endif

void
sdds_History_print(History_t* self) {
    printf("History [id: %p] {\n", self);
    printf("    depth: %d,\n", self->depth);
    printf("    in needle: %d,\n", self->in_needle);
    printf("    out needle: %d,\n", self->out_needle);
#ifdef SDDS_HAS_QOS_RELIABILITY
    printf("    samples:\n");
    for (int i=0; i<self->in_needle; i++){
        printf("        instance: %d, seqNr: %d,\n", self->samples[i].instance, self->samples[i].seqNr);
    }
#endif
    printf("}\n");
}
