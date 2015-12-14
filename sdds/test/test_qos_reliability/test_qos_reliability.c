#include <unistd.h>
#include "test_qos_reliability_sdds_impl.h"

int main()
{
    printf ("QoS Reliability: ");
	Log_setLvl (5);
	DDS_ReturnCode_t ret = DDS_RETCODE_OK;
	ret = sDDS_init ();
    assert (ret == DDS_RETCODE_OK);

    //  Create a strings sample
    Strings strings_pub;
    strings_pub.schar = 'H';
    strncpy ((char*) strings_pub.s_string,   "E", 1);
    strncpy ((char*) strings_pub.m_string,   "Es", 2);
    strncpy ((char*) strings_pub.l_string,   "Es gibt im Moment in dies", 25);
    strncpy ((char*) strings_pub.xl_string,   "Es gibt im Moment in diese Mannschaft, oh, einige ", 50);
    Strings strings_sub;
    Strings* strings_sub_p = &strings_sub;

    //  Create a numbers sample
    Numbers numbers_pub;
    numbers_pub.sbool = true;
    numbers_pub.sshort = 12;
    numbers_pub.slong = 13;
    numbers_pub.uoctet = 14;
    numbers_pub.ushort = 15;
    numbers_pub.ulong = 16;
    Numbers numbers_sub;
    Numbers* numbers_sub_p = &numbers_sub;

    // Create a testqosreliability sample
    Testqosreliabilitybasic testqosreliabilitybasic_pub;
    testqosreliabilitybasic_pub.number = 12;
    Testqosreliabilitybasic testqosreliabilitybasic_sub;
    Testqosreliabilitybasic* testqosreliabilitybasic_sub_p = &testqosreliabilitybasic_sub;

    Testqosreliabilitysmall testqosreliabilitysmall_pub;
    testqosreliabilitysmall_pub.number = 12;
    Testqosreliabilitysmall testqosreliabilitysmall_sub;
    Testqosreliabilitysmall* testqosreliabilitysmall_sub_p = &testqosreliabilitysmall_sub;

    Testqosreliabilitybig testqosreliabilitybig_pub;
    testqosreliabilitybig_pub.number = 12;
    Testqosreliabilitybig testqosreliabilitybig_sub;
    Testqosreliabilitybig* testqosreliabilitybig_sub_p = &testqosreliabilitybig_sub;

    Testqosreliabilityhuge testqosreliabilityhuge_pub;
    testqosreliabilityhuge_pub.number = 12;
    Testqosreliabilityhuge testqosreliabilityhuge_sub;
    Testqosreliabilityhuge* testqosreliabilityhuge_sub_p = &testqosreliabilityhuge_sub;

    //  R/W some strings samples
    for (int i=0; i<1; i++){
        DDS_StringsDataWriter_write (g_Strings_writer, &strings_pub, NULL);
        usleep(2);
        DDS_StringsDataReader_take_next_sample(g_Strings_reader, &strings_sub_p, NULL);
    }

    //  R/W some testqosreliability samples
    for (int i=0; i<20; i++){
        DDS_TestqosreliabilitybasicDataWriter_write (g_Testqosreliabilitybasic_writer, &testqosreliabilitybasic_pub, NULL);
        usleep(2);
        DDS_TestqosreliabilitybasicDataReader_take_next_sample (g_Testqosreliabilitybasic_reader, &testqosreliabilitybasic_sub_p, NULL);
    }

    for (int i=0; i<1; i++){
        DDS_TestqosreliabilitysmallDataWriter_write (g_Testqosreliabilitysmall_writer, &testqosreliabilitysmall_pub, NULL);
        usleep(2);
        DDS_TestqosreliabilitysmallDataReader_take_next_sample (g_Testqosreliabilitysmall_reader, &testqosreliabilitysmall_sub_p, NULL);
    }

    for (int i=0; i<1; i++){
        DDS_TestqosreliabilitybigDataWriter_write (g_Testqosreliabilitybig_writer, &testqosreliabilitybig_pub, NULL);
        usleep(2);
        DDS_TestqosreliabilitybigDataReader_take_next_sample (g_Testqosreliabilitybig_reader, &testqosreliabilitybig_sub_p, NULL);
    }

    for (int i=0; i<1; i++){
        DDS_TestqosreliabilityhugeDataWriter_write (g_Testqosreliabilityhuge_writer, &testqosreliabilityhuge_pub, NULL);
        usleep(2);
        DDS_TestqosreliabilityhugeDataReader_take_next_sample (g_Testqosreliabilityhuge_reader, &testqosreliabilityhuge_sub_p, NULL);
    }

    for (int i=0; i<1; i++){
        DDS_NumbersDataWriter_write (g_Numbers_writer, &numbers_pub, NULL);
        usleep(2);
        DDS_NumbersDataReader_take_next_sample(g_Numbers_reader, &numbers_sub_p, NULL);
    }
    //TODO: check seqNr & co

    if (ret == DDS_RETCODE_OK){
        printf ("OK\n");
    } else {
        printf ("FAIL\n");
    }

    return 0;
}
