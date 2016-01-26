#include <unistd.h>
#include "test_echo_linux_reliability_sdds_impl.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf ("Linux (multicast, echo) reliability: ");
    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();
    // Cruto_complete)OAeate a testqosreliability sample
    Testqosreliabilitybasic testqosreliabilitybasic_pub;
    Testqosreliabilitybasic testqosreliabilitybasic_sub;
    Testqosreliabilitybasic* testqosreliabilitybasic_sub_p = &testqosreliabilitybasic_sub;
    Testqosreliabilitysmall testqosreliabilitysmall_pub;
    Testqosreliabilitysmall testqosreliabilitysmall_sub;
    Testqosreliabilitysmall* testqosreliabilitysmall_sub_p = &testqosreliabilitysmall_sub;
    Testqosreliabilitybig testqosreliabilitybig_pub;
    Testqosreliabilitybig testqosreliabilitybig_sub;
    Testqosreliabilitybig* testqosreliabilitybig_sub_p = &testqosreliabilitybig_sub;
    Testqosreliabilityhuge testqosreliabilityhuge_pub;
    Testqosreliabilityhuge testqosreliabilityhuge_sub;
    Testqosreliabilityhuge* testqosreliabilityhuge_sub_p = &testqosreliabilityhuge_sub;

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
        DDS_TestqosreliabilitybasicDataWriter_write (g_Testqosreliabilitybasic_writer, &testqosreliabilitybasic_pub, NULL);
        DDS_TestqosreliabilitysmallDataWriter_write (g_Testqosreliabilitysmall_writer, &testqosreliabilitysmall_pub, NULL);
        DDS_TestqosreliabilitybigDataWriter_write (g_Testqosreliabilitybig_writer, &testqosreliabilitybig_pub, NULL);
        DDS_TestqosreliabilityhugeDataWriter_write (g_Testqosreliabilityhuge_writer, &testqosreliabilityhuge_pub, NULL);

        if (retBasic != SDDS_RT_OK)
            retBasic = DDS_TestqosreliabilitybasicDataReader_take_next_sample (g_Testqosreliabilitybasic_reader, &testqosreliabilitybasic_sub_p, NULL);
        if (retSmall != SDDS_RT_OK)
            retSmall = DDS_TestqosreliabilitysmallDataReader_take_next_sample (g_Testqosreliabilitysmall_reader, &testqosreliabilitysmall_sub_p, NULL);
        if (retBig != SDDS_RT_OK)
            retBig = DDS_TestqosreliabilitybigDataReader_take_next_sample (g_Testqosreliabilitybig_reader, &testqosreliabilitybig_sub_p, NULL);
        if (retHuge != SDDS_RT_OK)
            retHuge = DDS_TestqosreliabilityhugeDataReader_take_next_sample (g_Testqosreliabilityhuge_reader, &testqosreliabilityhuge_sub_p, NULL);

        allSubsFound = (retBasic == SDDS_RT_OK) && (retSmall == SDDS_RT_OK) && (retBig == SDDS_RT_OK) && (retHuge == SDDS_RT_OK);

        gettimeofday (&tmp, NULL);
        if (tmp.tv_sec > (start.tv_sec + 20)){
            printf("ERROR: Not all subscriptions could be found until timeout!\n");
            return SDDS_RT_FAIL;
        }

        sleep (1);
    }

    // TEST1: Proper upcount & overflow behavior of all seqSizes
    ((Reliable_DataWriter_t*)g_Testqosreliabilitybasic_writer)->seqNr = 13;
    ((Reliable_DataWriter_t*)g_Testqosreliabilitysmall_writer)->seqNr = 253;
    ((Reliable_DataWriter_t*)g_Testqosreliabilitybig_writer)->seqNr = 65533;
    ((Reliable_DataWriter_t*)g_Testqosreliabilityhuge_writer)->seqNr = 4294967293;
    for (int i=0; i<5; i++){
        DDS_TestqosreliabilitybasicDataWriter_write (g_Testqosreliabilitybasic_writer, &testqosreliabilitybasic_pub, NULL);
        DDS_TestqosreliabilitysmallDataWriter_write (g_Testqosreliabilitysmall_writer, &testqosreliabilitysmall_pub, NULL);
        DDS_TestqosreliabilitybigDataWriter_write (g_Testqosreliabilitybig_writer, &testqosreliabilitybig_pub, NULL);
        DDS_TestqosreliabilityhugeDataWriter_write (g_Testqosreliabilityhuge_writer, &testqosreliabilityhuge_pub, NULL);
        usleep (5);

        DDS_TestqosreliabilitybasicDataReader_take_next_sample (g_Testqosreliabilitybasic_reader, &testqosreliabilitybasic_sub_p, NULL);
        DDS_TestqosreliabilitysmallDataReader_take_next_sample (g_Testqosreliabilitysmall_reader, &testqosreliabilitysmall_sub_p, NULL);
        DDS_TestqosreliabilitybigDataReader_take_next_sample (g_Testqosreliabilitybig_reader, &testqosreliabilitybig_sub_p, NULL);
        DDS_TestqosreliabilityhugeDataReader_take_next_sample (g_Testqosreliabilityhuge_reader, &testqosreliabilityhuge_sub_p, NULL);
    }

    assert((((Reliable_DataWriter_t*)g_Testqosreliabilitybasic_writer)->seqNr & 0x0f) == 2);
    assert( (uint8_t) ((Reliable_DataWriter_t*)g_Testqosreliabilitysmall_writer)->seqNr == 2);
    assert( (uint16_t) ((Reliable_DataWriter_t*)g_Testqosreliabilitybig_writer)->seqNr == 2);
    assert( (uint32_t) ((Reliable_DataWriter_t*)g_Testqosreliabilityhuge_writer)->seqNr == 2);

    // TEST2: Proper discarding of older messages
    ((Reliable_DataWriter_t*)g_Testqosreliabilitybasic_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_Testqosreliabilitysmall_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_Testqosreliabilitybig_writer)->seqNr = 8;
    ((Reliable_DataWriter_t*)g_Testqosreliabilityhuge_writer)->seqNr = 8;

    // clearing of history
    // TODO

    //
    printf ("OK\n");
    return 0;
}
