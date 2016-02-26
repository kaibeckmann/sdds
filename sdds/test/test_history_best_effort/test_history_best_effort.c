#include <unistd.h>
#include <sdds/sDDS.h>
#include "test_history_best_effort_sdds_impl.h"

int main()
{
    printf ("History (best effort): ");
    Log_setLvl(5);
    sDDS_init ();

    rc_t rc;
    Sample_t samples[1];
    Strings strings;
    samples[0].data = &strings;
    History_t history;
    rc = sdds_History_setup (&history, &samples[0], 1);
    assert (rc == SDDS_RT_OK);

    //  Test with QOS RELIABILITY and kind BEST EFFORT
    NetBuffRef_t buffer1;
    NetBuffRef_init(&buffer1);
    NetBuffRef_renew(&buffer1);
    buffer1.subMsgCount = 1;
    buffer1.curPos = 4;
    buffer1.curDomain = 1;
    buffer1.curTopic = g_Strings_topic;
    buffer1.buff_start = (byte_t []) {0x01, 0x03, 0x10, 0x11, 0x32, 0x49, 0x45, 0x00, 0x45, 0x73, 0x00, 0x45, 0x73, 0x20, 0x67, 0x69, 0x62, 0x74, 0x20, 0x69, 0x6d, 0x20, 0x4d, 0x6f, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x69, 0x6e, 0x20, 0x64, 0x69, 0x65, 0x73, 0x00, 0x45, 0x73, 0x20, 0x67, 0x69, 0x62, 0x74, 0x20, 0x69, 0x6d, 0x20, 0x4d, 0x6f, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x69, 0x6e, 0x20, 0x64, 0x69, 0x65, 0x73, 0x65, 0x20, 0x4d, 0x61, 0x6e, 0x6e, 0x73, 0x63, 0x68, 0x61, 0x66, 0x74, 0x2c, 0x20, 0x6f, 0x68, 0x2c, 0x20, 0x65, 0x69, 0x6e, 0x69, 0x67, 0x65, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    NetBuffRef_t buffer2;
    NetBuffRef_init(&buffer2);
    NetBuffRef_renew(&buffer2);
    buffer2.subMsgCount = 1;
    buffer2.curPos = 4;
    buffer2.curDomain = 1;
    buffer2.curTopic = g_Strings_topic;
    buffer2.buff_start = (byte_t []) {0x01, 0x03, 0x10, 0x11, 0x32, 0x48, 0x45, 0x00, 0x45, 0x73, 0x00, 0x45, 0x73, 0x20, 0x67, 0x69, 0x62, 0x74, 0x20, 0x69, 0x6d, 0x20, 0x4d, 0x6f, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x69, 0x6e, 0x20, 0x64, 0x69, 0x65, 0x73, 0x00, 0x45, 0x73, 0x20, 0x67, 0x69, 0x62, 0x74, 0x20, 0x69, 0x6d, 0x20, 0x4d, 0x6f, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x69, 0x6e, 0x20, 0x64, 0x69, 0x65, 0x73, 0x65, 0x20, 0x4d, 0x61, 0x6e, 0x6e, 0x73, 0x63, 0x68, 0x61, 0x66, 0x74, 0x2c, 0x20, 0x6f, 0x68, 0x2c, 0x20, 0x65, 0x69, 0x6e, 0x69, 0x67, 0x65, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    //  Enqueue
    rc = sdds_History_enqueue (&history, &buffer1, 0);
    assert (rc == SDDS_RT_OK);
    rc = sdds_History_enqueue (&history, &buffer2, 1);
    assert (rc == SDDS_RT_OK);

    //  Dequeue
    Sample_t *mysample;
    mysample = sdds_History_dequeue (&history);
    assert (mysample);
    Strings e1 = *((Strings*) mysample->data);
    assert (e1.schar == 'H');
    assert (strcmp (e1.s_string, "E") == 0);
    assert (strcmp (e1.m_string, "Es") == 0);
    assert (strcmp (e1.l_string, "Es gibt im Moment in dies") == 0);
    assert (strcmp (e1.xl_string, "Es gibt im Moment in diese Mannschaft, oh, einige ") == 0);

    printf ("OK\n");
    return 0;
}
