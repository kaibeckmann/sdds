#include "gen_constants.h"

#ifdef TEST_HAS_MULTICAST
#include "test_mcast_linux_reliability_besteffort_sdds_impl.h"
#else
#include "test_ucast_reliability_besteffort_sdds_impl.h"
#endif

#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


Reliable_DataWriter_t* writer_basic_p;
Reliable_DataWriter_t* writer_small_p;
Reliable_DataWriter_t* writer_big_p;
Reliable_DataWriter_t* writer_huge_p;
DataReader_t* reader_basic_p;
DataReader_t* reader_small_p;
DataReader_t* reader_big_p;
DataReader_t* reader_huge_p;


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





int main()
{
#ifdef TEST_HAS_MULTICAST
    printf ("Linux (multicast) Reliability - besteffort: ");
#else
    printf ("Linux (unicast) Reliability - besteffort: ");
#endif

    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();
    // Create a testqosreliability sample
    TestQosReliabilityBasicBesteffort testqosreliabilitybasic_pub;
    TestQosReliabilityBasicBesteffort testqosreliabilitybasic_sub;
    TestQosReliabilityBasicBesteffort* testqosreliabilitybasic_sub_p = &testqosreliabilitybasic_sub;
    TestQosReliabilitySmallBesteffort testqosreliabilitysmall_pub;
    TestQosReliabilitySmallBesteffort testqosreliabilitysmall_sub;
    TestQosReliabilitySmallBesteffort* testqosreliabilitysmall_sub_p = &testqosreliabilitysmall_sub;
    TestQosReliabilityBigBesteffort testqosreliabilitybig_pub;
    TestQosReliabilityBigBesteffort testqosreliabilitybig_sub;
    TestQosReliabilityBigBesteffort* testqosreliabilitybig_sub_p = &testqosreliabilitybig_sub;
    TestQosReliabilityHugeBesteffort testqosreliabilityhuge_pub;
    TestQosReliabilityHugeBesteffort testqosreliabilityhuge_sub;
    TestQosReliabilityHugeBesteffort* testqosreliabilityhuge_sub_p = &testqosreliabilityhuge_sub;

    // active testing until all subscibers have been found
    struct timeval start;
    struct timeval tmp;
    bool allSubsFound = false;
    rc_t retBasic = SDDS_RT_NODATA;
    rc_t retSmall = SDDS_RT_NODATA;
    rc_t retBig = SDDS_RT_NODATA;
    rc_t retHuge = SDDS_RT_NODATA;

    writer_basic_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBasicBesteffort_writer;
    writer_small_p = (Reliable_DataWriter_t*)g_TestQosReliabilitySmallBesteffort_writer;
    writer_big_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBigBesteffort_writer;
    writer_huge_p = (Reliable_DataWriter_t*)g_TestQosReliabilityHugeBesteffort_writer;
    reader_basic_p = (DataReader_t*)g_TestQosReliabilityBasicBesteffort_reader;
    reader_small_p = (DataReader_t*)g_TestQosReliabilitySmallBesteffort_reader;
    reader_big_p = (DataReader_t*)g_TestQosReliabilityBigBesteffort_reader;
    reader_huge_p = (DataReader_t*)g_TestQosReliabilityHugeBesteffort_reader;


#ifdef TEST_HAS_MULTICAST
    gettimeofday (&start, NULL);
    while (!allSubsFound){
        DDS_TestQosReliabilityBasicBesteffortDataWriter_write (g_TestQosReliabilityBasicBesteffort_writer, &testqosreliabilitybasic_pub, NULL);
        DDS_TestQosReliabilitySmallBesteffortDataWriter_write (g_TestQosReliabilitySmallBesteffort_writer, &testqosreliabilitysmall_pub, NULL);
        DDS_TestQosReliabilityBigBesteffortDataWriter_write (g_TestQosReliabilityBigBesteffort_writer, &testqosreliabilitybig_pub, NULL);
        DDS_TestQosReliabilityHugeBesteffortDataWriter_write (g_TestQosReliabilityHugeBesteffort_writer, &testqosreliabilityhuge_pub, NULL);

        if (retBasic != SDDS_RT_OK)
            retBasic = DDS_TestQosReliabilityBasicBesteffortDataReader_take_next_sample (g_TestQosReliabilityBasicBesteffort_reader, &testqosreliabilitybasic_sub_p, NULL);
        if (retSmall != SDDS_RT_OK)
            retSmall = DDS_TestQosReliabilitySmallBesteffortDataReader_take_next_sample (g_TestQosReliabilitySmallBesteffort_reader, &testqosreliabilitysmall_sub_p, NULL);
        if (retBig != SDDS_RT_OK)
            retBig = DDS_TestQosReliabilityBigBesteffortDataReader_take_next_sample (g_TestQosReliabilityBigBesteffort_reader, &testqosreliabilitybig_sub_p, NULL);
        if (retHuge != SDDS_RT_OK)
            retHuge = DDS_TestQosReliabilityHugeBesteffortDataReader_take_next_sample (g_TestQosReliabilityHugeBesteffort_reader, &testqosreliabilityhuge_sub_p, NULL);

        allSubsFound = (retBasic == SDDS_RT_OK) && (retSmall == SDDS_RT_OK) && (retBig == SDDS_RT_OK) && (retHuge == SDDS_RT_OK);

        gettimeofday (&tmp, NULL);
        if (tmp.tv_sec > (start.tv_sec + 60)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        usleep (500000);
    }
#endif

    // TEST 1: Proper upcount & overflow behavior of all seqSizes
    writer_basic_p->seqNr = 13;
    writer_small_p->seqNr = 253;
    writer_big_p->seqNr = 65533;
    writer_huge_p->seqNr = 4294967293;


    for (int i=0; i<5; i++){
        DDS_TestQosReliabilityBasicBesteffortDataWriter_write (g_TestQosReliabilityBasicBesteffort_writer, &testqosreliabilitybasic_pub, NULL);
        DDS_TestQosReliabilitySmallBesteffortDataWriter_write (g_TestQosReliabilitySmallBesteffort_writer, &testqosreliabilitysmall_pub, NULL);
        DDS_TestQosReliabilityBigBesteffortDataWriter_write (g_TestQosReliabilityBigBesteffort_writer, &testqosreliabilitybig_pub, NULL);
        DDS_TestQosReliabilityHugeBesteffortDataWriter_write (g_TestQosReliabilityHugeBesteffort_writer, &testqosreliabilityhuge_pub, NULL);
        usleep (10);
    }

    assert(  writer_basic_p->seqNr == 2 );
    assert(  writer_small_p->seqNr == 2 );
    assert(  writer_big_p->seqNr == 2 );
    assert(  writer_huge_p->seqNr == 2 );


    



    printf ("OK\n");
    return 0;
}
