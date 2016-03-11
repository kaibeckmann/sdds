#include <unistd.h>
#include "test_echo_linux_reliability_reliable_ack_sdds_impl.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Create a testqosreliability sample
TestQosReliabilityBasicReliableAck testQosReliabilityBasicReliableAck_pub;
TestQosReliabilityBasicReliableAck testQosReliabilityBasicReliableAck_sub;
TestQosReliabilityBasicReliableAck* testQosReliabilityBasicReliableAck_sub_p = &testQosReliabilityBasicReliableAck_sub;
/*
TestQosReliabilitySmallReliableAck testQosReliabilitySmallReliableAck_pub;
TestQosReliabilitySmallReliableAck testQosReliabilitySmallReliableAck_sub;
TestQosReliabilitySmallReliableAck* testQosReliabilitySmallReliableAck_sub_p = &testQosReliabilitySmallReliableAck_sub;
TestQosReliabilityBigReliableAck testQosReliabilityBigReliableAck_pub;
TestQosReliabilityBigReliableAck testQosReliabilityBigReliableAck_sub;
TestQosReliabilityBigReliableAck* testQosReliabilityBigReliableAck_sub_p = &testQosReliabilityBigReliableAck_sub;
TestQosReliabilityHugeReliableAck testQosReliabilityHugeReliableAck_pub;
TestQosReliabilityHugeReliableAck testQosReliabilityHugeReliableAck_sub;
TestQosReliabilityHugeReliableAck* testQosReliabilityHugeReliableAck_sub_p = &testQosReliabilityHugeReliableAck_sub;
*/

void clean_DataWriter_SamplesToAcknowledge() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].data = NULL;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].timeStamp = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed = 0;
/*
        ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableAck_writer)->samplesToAcknowledge[i].data = NULL;
        ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableAck_writer)->samplesToAcknowledge[i].seqNr = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableAck_writer)->samplesToAcknowledge[i].timeStamp = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilitySmallReliableAck_writer)->samplesToAcknowledge[i].isUsed = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableAck_writer)->samplesToAcknowledge[i].data = NULL;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableAck_writer)->samplesToAcknowledge[i].seqNr = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableAck_writer)->samplesToAcknowledge[i].timeStamp = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBigReliableAck_writer)->samplesToAcknowledge[i].isUsed = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableAck_writer)->samplesToAcknowledge[i].data = NULL;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableAck_writer)->samplesToAcknowledge[i].seqNr = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableAck_writer)->samplesToAcknowledge[i].timeStamp = 0;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityHugeReliableAck_writer)->samplesToAcknowledge[i].isUsed = 0;
*/
    }
}

void clean_DataWriter_SeqNrs() {
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = 0;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = 0;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = 0;
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = 0;
}

void clean_DataReader_History() {
    int depth = ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.depth;

    ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.in_needle = 0;
    ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.out_needle = depth;
/*
    ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.in_needle = 0;
    ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.out_needle = depth;
    ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.in_needle = 0;
    ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.out_needle = depth;
    ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.in_needle = 0;
    ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.out_needle = depth;
*/

    for (int i=0; i<SDDS_QOS_HISTORY_DEPTH; i++) {
        ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.samples[i].instance = NULL;
        ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.samples[i].seqNr = 0;
/*
        ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.samples[i].instance = NULL;
        ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.samples[i].seqNr = 0;
        ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.samples[i].instance = NULL;
        ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.samples[i].seqNr = 0;
        ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.samples[i].instance = NULL;
        ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.samples[i].seqNr = 0;
*/
    }
}
void clean_DataReader_History_MissingSamplesList_Locators() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; i++) {
        ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.qos_locator[i] = 0;
/*
        ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.qos_locator[i] = 0;
        ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.qos_locator[i] = 0;
        ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.qos_locator[i] = 0;
*/
    }
}

void clean_DataReader_History_MissingSamplesList_HighestSeqNrbyLoc() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; i++) {
        ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.highestSeqNrbyLoc[i] = 0;
/*
        ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.highestSeqNrbyLoc[i] = 0;
        ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.highestSeqNrbyLoc[i] = 0;
        ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.highestSeqNrbyLoc[i] = 0;
*/
    }
}

void clean_DataReader_History_MissingSamplesList_missingSeqNrsByLoc() {
    for (int i=0; i<SDDS_QOS_RELIABILITY_MAX_TOPIC_PARTICIPANTS; i++) {
        for (int j=0; j<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; j++) {
            ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.missingSeqNrsByLoc[i][j] = 0;
/*
            ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.missingSeqNrsByLoc[i][j] = 0;
            ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.missingSeqNrsByLoc[i][j] = 0;
            ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.missingSeqNrsByLoc[i][j] = 0;
*/
            ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.missingSeqNrSlotIsUsed[i][j] = 0;
/*
            ((DataReader_t*)g_TestQosReliabilitySmallReliableAck_reader)->history.missingSeqNrSlotIsUsed[i][j] = 0;
            ((DataReader_t*)g_TestQosReliabilityBigReliableAck_reader)->history.missingSeqNrSlotIsUsed[i][j] = 0;
            ((DataReader_t*)g_TestQosReliabilityHugeReliableAck_reader)->history.missingSeqNrSlotIsUsed[i][j] = 0;
*/
        }
    }
}

/*==================== TEST 1.1: Acknowledgement-list of DataWriter ========= */
void test1_1 (){
    clean_DataWriter_SamplesToAcknowledge();
    clean_DataWriter_SeqNrs();
    clean_DataReader_History();
    clean_DataReader_History_MissingSamplesList_Locators();
    clean_DataReader_History_MissingSamplesList_HighestSeqNrbyLoc();
    clean_DataReader_History_MissingSamplesList_missingSeqNrsByLoc();


    // insert new samples until list is full
    //for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
    while(1){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        //usleep (100);
        sleep (3);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert(((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr == i);
        assert(((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed == 1);
    }

    // try to insert more samples, which should be discarded
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    }

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert(((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr == i);
        assert(((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed == 1);
    }

//printf("\nList 0: alles belegt\n");
for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++) {
    //printf("slot %d, isUsed %d, seqNr %d\n", i, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
}

    // replacement of samples after max_blocking_time
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    usleep (120);
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    usleep (120);
DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);

//printf("\nList 0-1: nach Wartezeit\n");
for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
    //printf("slot %d, isUsed %d, seqNr %d\n", i, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
}
    usleep (120);

/*
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        printf("blaaa %d\n", ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
        assert(((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr == (SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE + i));
    }
*/
/*
printf("\nList 1\n");
for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
    printf("slot %d, isUsed %d, seqNr %d\n", i, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
}

    DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);

printf("\nList 2\n");
for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
    printf("slot %d, isUsed %d, seqNr %d\n", i, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
}

    DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);

printf("\nList 3\n");
for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
    printf("slot %d, isUsed %d, seqNr %d\n", i, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
}

    DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);

printf("\nList 4\n");
for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
    printf("slot %d, isUsed %d, seqNr %d\n", i, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed, ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr);
}

    usleep (10);
*/

}

/*==================== TEST 1.2: MissingSamples-list of DataReader ========== */
void test1_2 (){
    clean_DataWriter_SamplesToAcknowledge();
    clean_DataWriter_SeqNrs();
    clean_DataReader_History();
    clean_DataReader_History_MissingSamplesList_HighestSeqNrbyLoc();
    clean_DataReader_History_MissingSamplesList_missingSeqNrsByLoc();

printf("    TEST 1.2 - MissingSamples-list of History\n");

    // produce missing messages and insert missing seqNrs in missingSamples-list
    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE;
    DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    usleep (10);

    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE; i++){
        assert(((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.missingSeqNrsByLoc[0][i] == (SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE-i-1) );
        assert(((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.missingSeqNrSlotIsUsed[0][i] == 1);
    }

    // check for proper setting of highestSeqNrbyLoc
    assert(((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.highestSeqNrbyLoc[0] == SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE);

    // send missing messages and check dequeuing behavior
    for (int i=SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE-1; i>=0; i--){
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = i;
        DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
        usleep (10);
        assert(((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.missingSeqNrSlotIsUsed[0][SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE-i-1] == 0 );
    }
}

/*==================== TEST 2: Interaction between components ========= */
void test2 (){
    clean_DataWriter_SamplesToAcknowledge();
    clean_DataWriter_SeqNrs();
    clean_DataReader_History();
    clean_DataReader_History_MissingSamplesList_Locators();
    clean_DataReader_History_MissingSamplesList_HighestSeqNrbyLoc();
    clean_DataReader_History_MissingSamplesList_missingSeqNrsByLoc();

printf("    TEST 2 - Interaction between components\n");

    // enqueing some samples in acknowledgement-list of DataWriter
    // and check if not yet acknowlegded samples are sent with new sample
    for (int i=0; i<SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE-1; i++){
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr = i;
        ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].isUsed = 1;
    }

    ((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->seqNr = (SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE-1);
    DDS_TestQosReliabilityBasicReliableAckDataWriter_write (g_TestQosReliabilityBasicReliableAck_writer, &testQosReliabilityBasicReliableAck_pub, NULL);
    usleep (50);

    // check, if all samples are enqued in history
    for (int i=0; i<SDDS_QOS_HISTORY_DEPTH; i++){
        printf("History slot: %d, seqNr: %d\n", i, ((DataReader_t*)g_TestQosReliabilityBasicReliableAck_reader)->history.samples[i].seqNr);
    }
    // check if properly dequeued from Acknowledgement-list
//assert(((Reliable_DataWriter_t*)g_TestQosReliabilityBasicReliableAck_writer)->samplesToAcknowledge[i].seqNr == (SDDS_QOS_RELIABILITY_RELIABLE_SAMPLES_SIZE+5+i));

}

int main() {

    printf ("Linux (multicast, echo) Reliability - reliable ack: ");
    fflush(stdout);
	Log_setLvl (5);
	sDDS_init ();

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
*/
    sleep (5);

    printf("\n    TEST 1.1 - Acknowledgement-list of DataWriter\n");
    test1_1(); // TEST 1.1: Acknowledgement-list of DataWriter

    //printf("\n    TEST 1.2 - MissingSamples-list of DataReader\n");
    //test1_2(); // TEST 1.2: MissingSamples-list of DataReader

    //printf("\n    TEST 2 - Interaction between components\n");
    //test2();   // TEST 2: Interaction between components


    printf ("OK\n");
    return 0;
}
