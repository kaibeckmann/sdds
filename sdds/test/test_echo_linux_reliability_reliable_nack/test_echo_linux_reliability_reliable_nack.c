#include <unistd.h>
#include "test_echo_linux_reliability_reliable_nack_sdds_impl.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf ("Linux (multicast, echo) Reliability - reliable nack: ");
    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();
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

    // active testing until all subscibers have been found
    // timeout = 20 secs
    struct timeval start;
    struct timeval tmp;
    bool allSubsFound = false;
    rc_t retBasic = SDDS_RT_NODATA;
    rc_t retSmall = SDDS_RT_NODATA;
    rc_t retBig = SDDS_RT_NODATA;
    rc_t retHuge = SDDS_RT_NODATA;

/*
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
        if (tmp.tv_sec > (start.tv_sec + 25)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        sleep (1);
    }

    // TEST1: Proper upcount & overflow behavior of all seqSizes
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableNack_writer)->seqNr = 13;
    ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableNack_writer)->seqNr = 253;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableNack_writer)->seqNr = 65533;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableNack_writer)->seqNr = 4294967293;
    for (int i=0; i<5; i++){
        DDS_TestQosReliabilityBasicReliableNackDataWriter_write (g_TestQosReliabilityBasicReliableNack_writer, &testQosReliabilityBasicReliableNack_pub, NULL);
        DDS_TestQosReliabilitySmallReliableNackDataWriter_write (g_TestQosReliabilitySmallReliableNack_writer, &testQosReliabilitySmallReliableNack_pub, NULL);
        DDS_TestQosReliabilityBigReliableNackDataWriter_write (g_TestQosReliabilityBigReliableNack_writer, &testQosReliabilityBigReliableNack_pub, NULL);
        DDS_TestQosReliabilityHugeReliableNackDataWriter_write (g_TestQosReliabilityHugeReliableNack_writer, &testQosReliabilityHugeReliableNack_pub, NULL);
        usleep (5);

        DDS_TestQosReliabilityBasicReliableNackDataReader_take_next_sample (g_TestQosReliabilityBasicReliableNack_reader, &testQosReliabilityBasicReliableNack_sub_p, NULL);
        DDS_TestQosReliabilitySmallReliableNackDataReader_take_next_sample (g_TestQosReliabilitySmallReliableNack_reader, &testQosReliabilitySmallReliableNack_sub_p, NULL);
        DDS_TestQosReliabilityBigReliableNackDataReader_take_next_sample (g_TestQosReliabilityBigReliableNack_reader, &testQosReliabilityBigReliableNack_sub_p, NULL);
        DDS_TestQosReliabilityHugeReliableNackDataReader_take_next_sample (g_TestQosReliabilityHugeReliableNack_reader, &testQosReliabilityHugeReliableNack_sub_p, NULL);
    }

    assert((((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableNack_writer)->seqNr & 0x0f) == 2);
    assert( (uint8_t) ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableNack_writer)->seqNr == 2);
    assert( (uint16_t) ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableNack_writer)->seqNr == 2);
    assert( (uint32_t) ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableNack_writer)->seqNr == 2);

    // TEST2: Proper discarding of older messages
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableNack_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableNack_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableNack_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableNack_writer)->seqNr = 8;

    // clearing of history
    // TODO

    //
*/
    printf ("OK\n");
    return 0;
}
