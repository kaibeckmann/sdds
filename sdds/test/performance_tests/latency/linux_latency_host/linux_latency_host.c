#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "linux_latency_host_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(5);

    static Latency latency_pub;
    static LatencyEcho latencyEcho_sub;
    LatencyEcho* latencyEcho_sub_p = &latencyEcho_sub;

    static struct timeval start, end;
    static long start_time;
    static long end_time;
    static long duration;
    static int msg_count = 0;
    FILE* log = fopen(LATENCY_LOG, "w+");

    while (msg_count < LATENCY_MSG_COUNT) {
        gettimeofday(&start, NULL);
        latency_pub.time = (start.tv_sec * 1000000 + start.tv_usec);

        ret = DDS_LatencyDataWriter_write (g_Latency_writer, &latency_pub, NULL);
        if (ret != DDS_RETCODE_OK) {
            continue;
        }

        do {
		    ret = DDS_LatencyEchoDataReader_take_next_sample(g_LatencyEcho_reader,
			    &latencyEcho_sub_p, NULL);
        } while (ret != DDS_RETCODE_OK); 

        gettimeofday(&end, NULL);
        start_time = latencyEcho_sub_p->time;
        end_time = end.tv_sec * 1000000 + end.tv_usec;
        // half round trip time
        duration = (end_time - start_time);

        msg_count++;
        fprintf(log, "%ld\n", duration); 
    }

    fclose(log);
    return 0;
}
