#include "gen_constants.h"

#ifdef TEST_HAS_MULTICAST
#include "test_mcast_linux_reliability_reliable_ack_sdds_impl.h"
#else
#include "test_ucast_reliability_reliable_ack_sdds_impl.h"
#endif

#include <unistd.h>

#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Create a testqosreliability sample
TestQosReliabilityBasicReliableAck testQosReliabilityBasicReliableAck_pub;
TestQosReliabilityBasicReliableAck testQosReliabilityBasicReliableAck_sub;
TestQosReliabilityBasicReliableAck* testQosReliabilityBasicReliableAck_sub_p = &testQosReliabilityBasicReliableAck_sub;
TestQosReliabilitySmallReliableAck testQosReliabilitySmallReliableAck_pub;
TestQosReliabilitySmallReliableAck testQosReliabilitySmallReliableAck_sub;
TestQosReliabilitySmallReliableAck* testQosReliabilitySmallReliableAck_sub_p = &testQosReliabilitySmallReliableAck_sub;
TestQosReliabilityBigReliableAck testQosReliabilityBigReliableAck_pub;
TestQosReliabilityBigReliableAck testQosReliabilityBigReliableAck_sub;
TestQosReliabilityBigReliableAck* testQosReliabilityBigReliableAck_sub_p = &testQosReliabilityBigReliableAck_sub;
TestQosReliabilityHugeReliableAck testQosReliabilityHugeReliableAck_pub;
TestQosReliabilityHugeReliableAck testQosReliabilityHugeReliableAck_sub;
TestQosReliabilityHugeReliableAck* testQosReliabilityHugeReliableAck_sub_p = &testQosReliabilityHugeReliableAck_sub;


Reliable_DataWriter_t* writer_basic_p;
Reliable_DataWriter_t* writer_small_p;
Reliable_DataWriter_t* writer_big_p;
Reliable_DataWriter_t* writer_huge_p;
DataReader_t* reader_basic_p;
DataReader_t* reader_small_p;
DataReader_t* reader_big_p;
DataReader_t* reader_huge_p;

void clean_DataWriter_samplesToKeep() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        writer_basic_p->samplesToKeep[i].data = NULL;
        writer_basic_p->samplesToKeep[i].seqNr = 0;
        writer_basic_p->samplesToKeep[i].timeStamp = 0;
        writer_basic_p->samplesToKeep[i].isUsed = 0;
        writer_small_p->samplesToKeep[i].data = NULL;
        writer_small_p->samplesToKeep[i].seqNr = 0;
        writer_small_p->samplesToKeep[i].timeStamp = 0;
        writer_small_p->samplesToKeep[i].isUsed = 0;
        writer_big_p->samplesToKeep[i].data = NULL;
        writer_big_p->samplesToKeep[i].seqNr = 0;
        writer_big_p->samplesToKeep[i].timeStamp = 0;
        writer_big_p->samplesToKeep[i].isUsed = 0;
        writer_huge_p->samplesToKeep[i].data = NULL;
        writer_huge_p->samplesToKeep[i].seqNr = 0;
        writer_huge_p->samplesToKeep[i].timeStamp = 0;
        writer_huge_p->samplesToKeep[i].isUsed = 0;
    }
}

void clean_DataWriter_SeqNrs() {
    writer_basic_p->seqNr = 0;
    writer_small_p->seqNr = 0;
    writer_big_p->seqNr = 0;
    writer_huge_p->seqNr = 0;
}

void clean_DataReader_History() {
    while (sdds_History_dequeue (&reader_basic_p->history));
    while (sdds_History_dequeue (&reader_small_p->history));
    while (sdds_History_dequeue (&reader_big_p->history));
    while (sdds_History_dequeue (&reader_huge_p->history));

    for (int i=0; i<SDDS_QOS_HISTORY_DEPTH; i++) {
        reader_basic_p->history.samples[i].instance = NULL;
        reader_basic_p->history.samples[i].seqNr = 0;
        reader_small_p->history.samples[i].instance = NULL;
        reader_small_p->history.samples[i].seqNr = 0;
        reader_big_p->history.samples[i].instance = NULL;
        reader_big_p->history.samples[i].seqNr = 0;
        reader_huge_p->history.samples[i].instance = NULL;
        reader_huge_p->history.samples[i].seqNr = 0;
    }
}
void clean_DataReader_History_MissingSamplesQueue_Locators() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; i++) {
        reader_basic_p->history.qos_locator[i] = 0;
        reader_small_p->history.qos_locator[i] = 0;
        reader_big_p->history.qos_locator[i] = 0;
        reader_huge_p->history.qos_locator[i] = 0;
    }
}

void clean_DataReader_History_MissingSamplesQueue_HighestSeqNrbyLoc() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; i++) {
        reader_basic_p->history.highestSeqNrbyLoc[i] = 0;
        reader_small_p->history.highestSeqNrbyLoc[i] = 0;
        reader_big_p->history.highestSeqNrbyLoc[i] = 0;
        reader_huge_p->history.highestSeqNrbyLoc[i] = 0;
    }
}

void clean_DataReader_History_MissingSamplesQueue_missingSeqNrsByLoc() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; i++) {
        for (int j=0; j<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; j++) {
            reader_basic_p->history.missingSeqNrsByLoc[i][j] = 0;
            reader_small_p->history.missingSeqNrsByLoc[i][j] = 0;
            reader_big_p->history.missingSeqNrsByLoc[i][j] = 0;
            reader_huge_p->history.missingSeqNrsByLoc[i][j] = 0;
            reader_basic_p->history.missingSeqNrSlotIsUsed[i][j] = 0;
            reader_small_p->history.missingSeqNrSlotIsUsed[i][j] = 0;
            reader_big_p->history.missingSeqNrSlotIsUsed[i][j] = 0;
            reader_huge_p->history.missingSeqNrSlotIsUsed[i][j] = 0;
        }
    }
}



int main() {
#ifdef TEST_HAS_MULTICAST
    printf ("Linux (multicast) Reliability - reliable ack: ");
#else
    printf ("Linux (unicast) Reliability - reliable ack: ");
#endif
    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();

    // active testing until all subscibers have been found
    struct timeval start;
    struct timeval tmp;
    bool allSubsFound = false;
    rc_t retBasic = SDDS_RT_NODATA;
    rc_t retSmall = SDDS_RT_NODATA;
    rc_t retBig = SDDS_RT_NODATA;
    rc_t retHuge = SDDS_RT_NODATA;

    writer_basic_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer;
    writer_small_p = (Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableAck_writer;
    writer_big_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableAck_writer;
    writer_huge_p = (Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableAck_writer;
    reader_basic_p = (DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader;
    reader_small_p = (DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader;
    reader_big_p = (DataReader_t*)g_TestQosReliabilityBigReliableAck_reader;
    reader_huge_p = (DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader;

    testQosReliabilityBasicReliableAck_pub.number = 1;
    testQosReliabilitySmallReliableAck_pub.number = 2;
    testQosReliabilityBigReliableAck_pub.number = 3;
    testQosReliabilityHugeReliableAck_pub.number = 4;

#ifdef TEST_HAS_MULTICAST
gettimeofday (&start, NULL);
    while (!allSubsFound){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);

        if (retBasic != SDDS_RT_OK)
            retBasic = DDS_TestQosReliabilityBasicReliableAckDataReader_take_next_sample (g_TestQosReliabilityBasicReliableAck_reader, &testQosReliabilityBasicReliableAck_sub_p, NULL);
        if (retSmall != SDDS_RT_OK)
            retSmall = DDS_TestQosReliabilitySmallReliableAckDataReader_take_next_sample (g_TestQosReliabilitySmallReliableAck_reader, &testQosReliabilitySmallReliableAck_sub_p, NULL);
        if (retBig != SDDS_RT_OK)
            retBig = DDS_TestQosReliabilityBigReliableAckDataReader_take_next_sample (g_TestQosReliabilityBigReliableAck_reader, &testQosReliabilityBigReliableAck_sub_p, NULL);
        if (retHuge != SDDS_RT_OK)
            retHuge = DDS_TestQosReliabilityHugeReliableAckDataReader_take_next_sample (g_TestQosReliabilityHugeReliableAck_reader, &testQosReliabilityHugeReliableAck_sub_p, NULL);

        allSubsFound = (retBasic == SDDS_RT_OK) && (retSmall == SDDS_RT_OK) && (retBig == SDDS_RT_OK) && (retHuge == SDDS_RT_OK);

        gettimeofday (&tmp, NULL);
        if (tmp.tv_sec > (start.tv_sec + 60)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        usleep (500000);
    }
#endif

    DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
    DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
    DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    usleep(10000);

    retBasic = DDS_TestQosReliabilityBasicReliableAckDataReader_take_next_sample (g_TestQosReliabilityBasicReliableAck_reader, &testQosReliabilityBasicReliableAck_sub_p, NULL);
    retSmall = DDS_TestQosReliabilitySmallReliableAckDataReader_take_next_sample (g_TestQosReliabilitySmallReliableAck_reader, &testQosReliabilitySmallReliableAck_sub_p, NULL);
    retBig = DDS_TestQosReliabilityBigReliableAckDataReader_take_next_sample (g_TestQosReliabilityBigReliableAck_reader, &testQosReliabilityBigReliableAck_sub_p, NULL);
    retHuge = DDS_TestQosReliabilityHugeReliableAckDataReader_take_next_sample (g_TestQosReliabilityHugeReliableAck_reader, &testQosReliabilityHugeReliableAck_sub_p, NULL);

    // test for proper receiving of data
    assert (testQosReliabilityBasicReliableAck_sub_p->number == 1);
    assert (testQosReliabilitySmallReliableAck_sub_p->number == 2);
    assert (testQosReliabilityBigReliableAck_sub_p->number == 3);
    assert (testQosReliabilityHugeReliableAck_sub_p->number == 4);


    clean_DataWriter_samplesToKeep();
    clean_DataWriter_SeqNrs();
    clean_DataReader_History();

    // insert new samples until queue is full
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    }
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++ ){
        assert( writer_basic_p->samplesToKeep[i].seqNr == i );
        assert( writer_basic_p->samplesToKeep[i].isUsed != 0 );
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
    }
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++ ){
        assert( writer_small_p->samplesToKeep[i].seqNr == i );
        assert( writer_small_p->samplesToKeep[i].isUsed != 0 );
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
    }
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++ ){
        assert( writer_big_p->samplesToKeep[i].seqNr == i );
        assert( writer_big_p->samplesToKeep[i].isUsed != 0 );
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    }
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++ ){
        assert( writer_huge_p->samplesToKeep[i].seqNr == i );
        assert( writer_huge_p->samplesToKeep[i].isUsed != 0 );
    }



    // try to insert more samples, which should be discarded
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert( writer_basic_p->samplesToKeep[i].seqNr == i );
        assert( writer_small_p->samplesToKeep[i].seqNr == i );
        assert( writer_big_p->samplesToKeep[i].seqNr == i );
        assert( writer_huge_p->samplesToKeep[i].seqNr == i );

        assert( writer_basic_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_small_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_big_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_huge_p->samplesToKeep[i].isUsed != 0 );
    }
    sleep(1);

    // replacement of samples after max_blocking_time
    writer_basic_p->seqNr = 5;
    writer_small_p->seqNr = 5;
    writer_big_p->seqNr = 5;
    writer_huge_p->seqNr = 5;
    // wait 110ms
    usleep (160000);

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    }
    usleep(10);

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert( writer_basic_p->samplesToKeep[i].seqNr == i+5 );
        assert( writer_small_p->samplesToKeep[i].seqNr == i+5 );
        assert( writer_big_p->samplesToKeep[i].seqNr == i+5 );
        assert( writer_huge_p->samplesToKeep[i].seqNr == i+5 );

        assert( writer_basic_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_small_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_big_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_huge_p->samplesToKeep[i].isUsed != 0 );
    }

    // dequeing from acknowledgement-queue after acknowledgement of samples
    sleep(3);  // wait until history is in the desired state
    clean_DataWriter_samplesToKeep();
    clean_DataWriter_SeqNrs();
    clean_DataReader_History();

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        usleep(500000);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert( writer_basic_p->samplesToKeep[i].seqNr == 0 );
        assert( writer_basic_p->samplesToKeep[i].isUsed == 0 );
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        usleep(500000);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
            assert( writer_small_p->samplesToKeep[i].seqNr == 0 );
            assert( writer_small_p->samplesToKeep[i].isUsed == 0 );
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        usleep(500000);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
            assert( writer_big_p->samplesToKeep[i].seqNr == 0 );
            assert( writer_big_p->samplesToKeep[i].isUsed == 0 );
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
        usleep(500000);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
            assert( writer_huge_p->samplesToKeep[i].seqNr == 0 );
            assert( writer_huge_p->samplesToKeep[i].isUsed == 0 );
    }


    printf ("OK\n");
    return 0;
}
