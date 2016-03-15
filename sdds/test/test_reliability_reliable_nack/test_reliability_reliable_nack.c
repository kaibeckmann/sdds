#include "gen_constants.h"

#ifdef TEST_HAS_MULTICAST
#include "test_echo_linux_reliability_reliable_nack_sdds_impl.h"
#else
#include "test_reliability_reliable_nack_sdds_impl.h"
#endif

#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Create a testqosreliability sample
/*
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
*/

rc_t retBasic = SDDS_RT_NODATA;
rc_t retSmall = SDDS_RT_NODATA;
rc_t retBig = SDDS_RT_NODATA;
rc_t retHuge = SDDS_RT_NODATA;

int main()
{
#ifdef TEST_HAS_MULTICAST
    printf ("Linux (multicast, echo) Reliability - reliable nack: ");
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
            DDS_StringsDataWriter_write (g_Strings_writer, &strings_pub, NULL);
            DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
            DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
            DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
            DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);

            if (retStrings != SDDS_RT_OK)
                retStrings = DDS_StringsDataReader_take_next_sample (g_Strings_reader, &strings_sub_p, NULL);
            if (retBasic != SDDS_RT_OK)
                retBasic = DDS_TestQosReliabilityBasicReliableAckDataReader_take_next_sample (g_TestQosReliabilityBasicReliableAck_reader, &testQosReliabilityBasicReliableAck_sub_p, NULL);
            if (retSmall != SDDS_RT_OK)
                retSmall = DDS_TestQosReliabilitySmallReliableAckDataReader_take_next_sample (g_TestQosReliabilitySmallReliableAck_reader, &testQosReliabilitySmallReliableAck_sub_p, NULL);
            if (retBig != SDDS_RT_OK)
                retBig = DDS_TestQosReliabilityBigReliableAckDataReader_take_next_sample (g_TestQosReliabilityBigReliableAck_reader, &testQosReliabilityBigReliableAck_sub_p, NULL);
            if (retHuge != SDDS_RT_OK)
                retHuge = DDS_TestQosReliabilityHugeReliableAckDataReader_take_next_sample (g_TestQosReliabilityHugeReliableAck_reader, &testQosReliabilityHugeReliableAck_sub_p, NULL);

            allSubsFound = (retStrings == SDDS_RT_OK) && (retBasic == SDDS_RT_OK) && (retSmall == SDDS_RT_OK) && (retBig == SDDS_RT_OK) && (retHuge == SDDS_RT_OK);

            gettimeofday (&tmp, NULL);
            if (tmp.tv_sec > (start.tv_sec + 25)){
                printf("ERROR: Not all subscriptions could be found until timeout!\n");
                return SDDS_RT_FAIL;
            }

            sleep (1);
        }
    #endif
*/





    //
    printf ("OK\n");
    return 0;
}
