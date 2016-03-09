#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "linux_latency_self_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(5);

    static Latency latency_pub;
    static Latency latency_sub;
    Latency *latency_sub_p = &latency_sub;

    static struct timeval start, end;
    static long start_time;
    static long end_time;
    static long duration;
    static int msg_count = 0;
    FILE* log = fopen(LATENCY_LOG, "w+");

    while (msg_count < LATENCY_MSG_COUNT+1) {
        gettimeofday(&start, NULL);
        latency_pub.time = (start.tv_sec * 1000000 + start.tv_usec);

        ret = DDS_LatencyDataWriter_write (g_Latency_writer, &latency_pub, NULL);
        if (ret != DDS_RETCODE_OK) {
            continue;
        }

        do {
		    ret = DDS_LatencyDataReader_take_next_sample(g_Latency_reader,
			    &latency_sub_p, NULL);
        } while (ret != DDS_RETCODE_OK); 

        gettimeofday(&end, NULL);
        start_time = latency_sub_p->time;
        end_time = end.tv_sec * 1000000 + end.tv_usec;
        duration = end_time - start_time;

        if (msg_count != 0) {
            fprintf(log, "%ld\n", duration); 
        }
        msg_count++;
    }

    fclose(log);
    return 0;
}
