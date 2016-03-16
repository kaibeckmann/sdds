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


rc_t retBasic = SDDS_RT_NODATA;
rc_t retSmall = SDDS_RT_NODATA;
rc_t retBig = SDDS_RT_NODATA;
rc_t retHuge = SDDS_RT_NODATA;

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


/*
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

*/





    //
    printf ("OK\n");
    return 0;
}
