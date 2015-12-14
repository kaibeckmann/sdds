#include <unistd.h>
#include "test_linux_sdds_impl.h"

int main()
{
    printf ("Linux (unicast): ");
	Log_setLvl (5);
	DDS_ReturnCode_t ret;
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
    Strings *strings_sub_p = &strings_sub;

    //  Create a numbers sample
    Numbers numbers_pub;
    numbers_pub.sbool = true;
    numbers_pub.sshort = 12;
    numbers_pub.slong = 13;
    numbers_pub.uoctet = 14;
    numbers_pub.ushort = 15;
    numbers_pub.ulong = 16;
    Numbers numbers_sub;
    Numbers *numbers_sub_p = &numbers_sub;

    //  Write a strings sample
    ret = DDS_StringsDataWriter_write (g_Strings_writer, &strings_pub, NULL);
    assert (ret == DDS_RETCODE_OK);

    //  Read a strings sample
    int index;
    for (index = 0; index < 3; index++) {
        ret = DDS_StringsDataReader_take_next_sample(g_Strings_reader, &strings_sub_p, NULL);
        if (ret != DDS_RETCODE_NO_DATA)
            break;
        sleep (1);
    }
    assert (ret == DDS_RETCODE_OK);
    assert (strings_sub_p->schar == 'H');
    assert (strcmp ((const char*) strings_sub_p->s_string, "E") == 0);
    assert (strcmp ((const char*) strings_sub_p->m_string, "Es") == 0);
    assert (strcmp ((const char*) strings_sub_p->l_string, "Es gibt im Moment in dies") == 0);
    assert (strcmp ((const char*) strings_sub_p->xl_string, "Es gibt im Moment in diese Mannschaft, oh, einige ") == 0);


    //  Write a numbers sample
    ret = DDS_NumbersDataWriter_write (g_Numbers_writer, &numbers_pub, NULL);
    assert (ret == DDS_RETCODE_OK);


    //  Read a numbers sample
    for (index = 0; index < 3; index++) {
    ret = DDS_NumbersDataReader_take_next_sample(g_Numbers_reader, &numbers_sub_p, NULL);
        if (ret != DDS_RETCODE_NO_DATA)
            break;
        sleep (1);
    }
    assert (ret == DDS_RETCODE_OK);
    assert (numbers_sub_p->sbool == true);
    assert (numbers_sub_p->sshort == 12);
    assert (numbers_sub_p->slong == 13);
    assert (numbers_sub_p->uoctet == 14);
    assert (numbers_sub_p->ushort == 15);
    assert (numbers_sub_p->ulong == 16);

    printf ("OK\n");
    return 0;
}
