#include "gen_constants.h"

#ifdef TEST_HAS_MULTICAST
#include "test_mcast_linux_reliability_reliable_nack_sdds_impl.h"
#else
#include "test_ucast_reliability_reliable_nack_sdds_impl.h"
#endif

#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Create a testqosreliability sample
TestQosReliabilityBasicReliableNack testQosReliabilityBasicReliableNack_pub;
TestQosReliabilityBasicReliableNack testQosReliabilityBasicReliableNack_sub;
TestQosReliabilityBasicReliableNack* testQosReliabilityBasicReliableNack_sub_p = &testQosReliabilityBasicReliableNack_sub;
TestQosReliabilitySmallReliableNack testQosReliabilitySmallReliableNack_pub;
TestQosReliabilitySmallReliableNack testQosReliabilitySmallReliableNack_sub;
TestQosReliabilitySmallReliableNack* testQosReliabilitySmallReliableNack_sub_p = &testQosReliabilitySmallReliableNack_sub;
TestQosReliabilityBigReliableNack testQosReliabilityBigReliableNack_pub;
TestQosReliabilityBigReliableNack testQosReliabilityBigReliableNack_sub;
TestQosReliabilityBigReliableNack* testQosReliabilityBigReliableNack_sub_p = &testQosReliabilityBigReliableNack_sub;
TestQosReliabilityHugeReliableNack testQosReliabilityHugeReliableNack_pub;
TestQosReliabilityHugeReliableNack testQosReliabilityHugeReliableNack_sub;
TestQosReliabilityHugeReliableNack* testQosReliabilityHugeReliableNack_sub_p = &testQosReliabilityHugeReliableNack_sub;

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
    int depth = reader_basic_p->history.depth;

    reader_basic_p->history.in_needle = 0;
    reader_basic_p->history.out_needle = depth;
    reader_small_p->history.in_needle = 0;
    reader_small_p->history.out_needle = depth;
    reader_big_p->history.in_needle = 0;
    reader_big_p->history.out_needle = depth;
    reader_huge_p->history.in_needle = 0;
    reader_huge_p->history.out_needle = depth;

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


int main()
{
#ifdef TEST_HAS_MULTICAST
    printf ("Linux (multicast) Reliability - reliable nack: ");
#else
    printf ("Linux (unicast) Reliability - reliable nack: ");
#endif
    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();

    // active testing until all subscibers have been found
    struct timeval start;
    struct timeval tmp;
    bool allSubsFound = false;

    writer_basic_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableNack_writer;
    writer_small_p = (Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableNack_writer;
    writer_big_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableNack_writer;
    writer_huge_p = (Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableNack_writer;
    reader_basic_p = (DataReader_t*)g_TestQosReliabilityBasicReliableNack_reader;
    reader_small_p = (DataReader_t*)g_TestQosReliabilitySmallReliableNack_reader;
    reader_big_p = (DataReader_t*)g_TestQosReliabilityBigReliableNack_reader;
    reader_huge_p = (DataReader_t*)g_TestQosReliabilityHugeReliableNack_reader;

    rc_t retBasic = SDDS_RT_NODATA;
    rc_t retSmall = SDDS_RT_NODATA;
    rc_t retBig = SDDS_RT_NODATA;
    rc_t retHuge = SDDS_RT_NODATA;


#ifdef TEST_HAS_MULTICAST
gettimeofday (&start, NULL);
    while (!allSubsFound){
        DDS_TestQosReliabilityBasicReliableNackDataWriter_write (g_TestQosReliabilityBasicReliableNack_writer, &testQosReliabilityBasicReliableNack_pub, NULL);
        DDS_TestQosReliabilitySmallReliableNackDataWriter_write (g_TestQosReliabilitySmallReliableNack_writer, &testQosReliabilitySmallReliableNack_pub, NULL);
        DDS_TestQosReliabilityBigReliableNackDataWriter_write (g_TestQosReliabilityBigReliableNack_writer, &testQosReliabilityBigReliableNack_pub, NULL);
        DDS_TestQosReliabilityHugeReliableNackDataWriter_write (g_TestQosReliabilityHugeReliableNack_writer, &testQosReliabilityHugeReliableNack_pub, NULL);

        if (retBasic != SDDS_RT_OK)
            retBasic = DDS_TestQosReliabilityBasicReliableNackDataReader_take_next_sample (g_TestQosReliabilityBasicReliableNack_reader, &testQosReliabilityBasicReliableNack_sub_p, NULL);
        if (retSmall != SDDS_RT_OK)
            retSmall = DDS_TestQosReliabilitySmallReliableNackDataReader_take_next_sample (g_TestQosReliabilitySmallReliableNack_reader, &testQosReliabilitySmallReliableNack_sub_p, NULL);
        if (retBig != SDDS_RT_OK)
            retBig = DDS_TestQosReliabilityBigReliableNackDataReader_take_next_sample (g_TestQosReliabilityBigReliableNack_reader, &testQosReliabilityBigReliableNack_sub_p, NULL);
        if (retHuge != SDDS_RT_OK)
            retHuge = DDS_TestQosReliabilityHugeReliableNackDataReader_take_next_sample (g_TestQosReliabilityHugeReliableNack_reader, &testQosReliabilityHugeReliableNack_sub_p, NULL);

        allSubsFound = (retBasic == SDDS_RT_OK) && (retSmall == SDDS_RT_OK) && (retBig == SDDS_RT_OK) && (retHuge == SDDS_RT_OK);

        gettimeofday (&tmp, NULL);
        if (tmp.tv_sec > (start.tv_sec + 60)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        usleep (500000);
    }
#endif



    DDS_TestQosReliabilityBasicReliableNackDataWriter_write (g_TestQosReliabilityBasicReliableNack_writer, &testQosReliabilityBasicReliableNack_pub, NULL);

    sleep(1);

    retBasic = DDS_TestQosReliabilityBasicReliableNackDataReader_take_next_sample (g_TestQosReliabilityBasicReliableNack_reader, &testQosReliabilityBasicReliableNack_sub_p, NULL);

    //
    printf ("OK\n");
    return 0;
}
