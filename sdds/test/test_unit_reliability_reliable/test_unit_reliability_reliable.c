#include "gen_constants.h"

#include "test_unit_reliability_reliable_sdds_impl.h"


#include <unistd.h>

#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Create a testqosreliability sample
TestQosReliabilityBasicReliableAck testQosReliabilityBasicReliableAck_pub;
TestQosReliabilitySmallReliableAck testQosReliabilitySmallReliableAck_pub;
TestQosReliabilityBigReliableAck testQosReliabilityBigReliableAck_pub;
TestQosReliabilityHugeReliableAck testQosReliabilityHugeReliableAck_pub;


Reliable_DataWriter_t* writer_basic_p;
Reliable_DataWriter_t* writer_small_p;
Reliable_DataWriter_t* writer_big_p;
Reliable_DataWriter_t* writer_huge_p;


void clean_DataWriter_samplesToKeep() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        writer_basic_p->samplesToKeep[i].seqNr = 0;
        writer_basic_p->samplesToKeep[i].timeStamp = 0;
        writer_basic_p->samplesToKeep[i].isUsed = 0;
        writer_small_p->samplesToKeep[i].seqNr = 0;
        writer_small_p->samplesToKeep[i].timeStamp = 0;
        writer_small_p->samplesToKeep[i].isUsed = 0;
        writer_big_p->samplesToKeep[i].seqNr = 0;
        writer_big_p->samplesToKeep[i].timeStamp = 0;
        writer_big_p->samplesToKeep[i].isUsed = 0;
        writer_huge_p->samplesToKeep[i].seqNr = 0;
        writer_huge_p->samplesToKeep[i].timeStamp = 0;
        writer_huge_p->samplesToKeep[i].isUsed = 0;
    }
}

void clean_DataWriter_SeqNrs() {
    writer_basic_p->seqNr = 0;
    writer_small_p->seqNr = 0;
    writer_big_p->seqNr = 0;
    writer_huge_p->seqNr = 0;
}




int main() {
    printf ("Reliability (reliable): ");

    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();


    writer_basic_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer;
    writer_small_p = (Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableAck_writer;
    writer_big_p = (Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableAck_writer;
    writer_huge_p = (Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableAck_writer;


    clean_DataWriter_samplesToKeep();
    clean_DataWriter_SeqNrs();


    // insert new samples until queue is full
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++ ){
        assert( writer_basic_p->samplesToKeep[i].seqNr == i );
        assert( writer_small_p->samplesToKeep[i].seqNr == i );
        assert( writer_big_p->samplesToKeep[i].seqNr == i );
        assert( writer_huge_p->samplesToKeep[i].seqNr == i );

        assert( writer_basic_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_small_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_big_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_huge_p->samplesToKeep[i].isUsed != 0 );
    }


    // try to insert more samples, which should be discarded
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert( writer_basic_p->samplesToKeep[i].seqNr == i );
        assert( writer_small_p->samplesToKeep[i].seqNr == i );
        assert( writer_big_p->samplesToKeep[i].seqNr == i );
        assert( writer_huge_p->samplesToKeep[i].seqNr == i );

        assert( writer_basic_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_small_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_big_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_huge_p->samplesToKeep[i].isUsed != 0 );
    }


    // replacement of samples after max_blocking_time
    writer_basic_p->seqNr = 5;
    writer_small_p->seqNr = 5;
    writer_big_p->seqNr = 5;
    writer_huge_p->seqNr = 5;
    // wait until max_blocking_time is over
    usleep (160000);

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        DDS_TestQosReliabilitySmallReliableAckDataWriter_write (g_TestQosReliabilitySmallReliableAck_writer, &testQosReliabilitySmallReliableAck_pub, NULL);
        DDS_TestQosReliabilityBigReliableAckDataWriter_write (g_TestQosReliabilityBigReliableAck_writer, &testQosReliabilityBigReliableAck_pub, NULL);
        DDS_TestQosReliabilityHugeReliableAckDataWriter_write (g_TestQosReliabilityHugeReliableAck_writer, &testQosReliabilityHugeReliableAck_pub, NULL);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert( writer_basic_p->samplesToKeep[i].seqNr == i+5 );
        assert( writer_small_p->samplesToKeep[i].seqNr == i+5 );
        assert( writer_big_p->samplesToKeep[i].seqNr == i+5 );
        assert( writer_huge_p->samplesToKeep[i].seqNr == i+5 );

        assert( writer_basic_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_small_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_big_p->samplesToKeep[i].isUsed != 0 );
        assert( writer_huge_p->samplesToKeep[i].isUsed != 0 );
    }


    printf ("OK\n");
    return 0;
}
