#include <unistd.h>
#include "test_echo_linux_reliability_besteffort_sdds_impl.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf ("Linux (multicast, echo) Reliability - besteffort: ");
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
    // timeout = 20 secs
    struct timeval start;
    struct timeval tmp;
    bool allSubsFound = false;
    rc_t retBasic = SDDS_RT_NODATA;
    rc_t retSmall = SDDS_RT_NODATA;
    rc_t retBig = SDDS_RT_NODATA;
    rc_t retHuge = SDDS_RT_NODATA;

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
        if (tmp.tv_sec > (start.tv_sec + 25)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        sleep (1);
    }

    // TEST1: Proper upcount & overflow behavior of all seqSizes
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicBesteffort_writer)->seqNr = 13;
    ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallBesteffort_writer)->seqNr = 253;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBigBesteffort_writer)->seqNr = 65533;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeBesteffort_writer)->seqNr = 4294967293;
    for (int i=0; i<5; i++){
        DDS_TestQosReliabilityBasicBesteffortDataWriter_write (g_TestQosReliabilityBasicBesteffort_writer, &testqosreliabilitybasic_pub, NULL);
        DDS_TestQosReliabilitySmallBesteffortDataWriter_write (g_TestQosReliabilitySmallBesteffort_writer, &testqosreliabilitysmall_pub, NULL);
        DDS_TestQosReliabilityBigBesteffortDataWriter_write (g_TestQosReliabilityBigBesteffort_writer, &testqosreliabilitybig_pub, NULL);
        DDS_TestQosReliabilityHugeBesteffortDataWriter_write (g_TestQosReliabilityHugeBesteffort_writer, &testqosreliabilityhuge_pub, NULL);
        usleep (5);

        DDS_TestQosReliabilityBasicBesteffortDataReader_take_next_sample (g_TestQosReliabilityBasicBesteffort_reader, &testqosreliabilitybasic_sub_p, NULL);
        DDS_TestQosReliabilitySmallBesteffortDataReader_take_next_sample (g_TestQosReliabilitySmallBesteffort_reader, &testqosreliabilitysmall_sub_p, NULL);
        DDS_TestQosReliabilityBigBesteffortDataReader_take_next_sample (g_TestQosReliabilityBigBesteffort_reader, &testqosreliabilitybig_sub_p, NULL);
        DDS_TestQosReliabilityHugeBesteffortDataReader_take_next_sample (g_TestQosReliabilityHugeBesteffort_reader, &testqosreliabilityhuge_sub_p, NULL);
    }

    assert((((Reliable_DataWriter_t*)g_TestQosReliabilityBasicBesteffort_writer)->seqNr & 0x0f) == 2);
    assert( (uint8_t) ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallBesteffort_writer)->seqNr == 2);
    assert( (uint16_t) ((Reliable_DataWriter_t*)g_TestQosReliabilityBigBesteffort_writer)->seqNr == 2);
    assert( (uint32_t) ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeBesteffort_writer)->seqNr == 2);

    // TEST2: Proper discarding of older messages
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicBesteffort_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallBesteffort_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBigBesteffort_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeBesteffort_writer)->seqNr = 8;

    // clearing of history
    // TODO

    //
    printf ("OK\n");
    return 0;
}
