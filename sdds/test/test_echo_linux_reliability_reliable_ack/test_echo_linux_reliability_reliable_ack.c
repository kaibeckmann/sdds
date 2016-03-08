#include <unistd.h>
#include "test_echo_linux_reliability_reliable_ack_sdds_impl.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    printf ("Linux (multicast, echo) Reliability - reliable ack: ");
    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();
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
        if (tmp.tv_sec > (start.tv_sec + 20)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        sleep (1);
    }



    // TEST 1: Proper enqueing in acknowledgement-list on DW

    for (int i=0; i<3; i++){
        sleep (5);
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        usleep (5);
    }

    for (int i=0; i<3; i++){
        DDS_TestQosReliabilityBasicReliableAckDataReader_take_next_sample (g_TestQosReliabilityBasicReliableAck_reader, &testQosReliabilityBasicReliableAck_sub_p, NULL);
    }

sleep (5);

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        Reliable_DataWriter_t* dw1 = (Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer;
        ReliableSample_t s1 = dw1->reliableSamples[i];

        if (((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->reliableSamples[i].isUsed == 1){

        }
    }



    printf ("OK\n");
    return 0;
}
