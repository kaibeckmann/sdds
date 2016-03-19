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

    sleep(5);

    while (msg_count < LATENCY_MSG_COUNT+1) {
        gettimeofday(&start, NULL);
        start_time = (start.tv_sec * 1000000 + start.tv_usec);
        latency_pub.time = start_time;

        ret = DDS_LatencyDataWriter_write (g_Latency_writer, &latency_pub, NULL);
        if (ret != DDS_RETCODE_OK) {
            continue;
        }
        
        bool skip = false;

        do {
		    ret = DDS_LatencyEchoDataReader_take_next_sample(g_LatencyEcho_reader,
			    &latencyEcho_sub_p, NULL);

            gettimeofday(&end, NULL);
            end_time = end.tv_sec * 1000000 + end.tv_usec;
            // if it takes more then 10 sec skip the message
            if ( (end_time - start_time) >= 60000000) {
                skip = true;
                break;
            }
        } while (ret != DDS_RETCODE_OK); 

        // make sure it is the right message
        if (!skip && (start_time == latencyEcho_sub_p->time)) {
                // half round trip time
                duration = (end_time - start_time) / 2;

                // skip first sample
                if (msg_count != 0) {
                    fprintf(log, "%ld\n", duration); 
                }
                msg_count++;
        }
    }

    fclose(log);
    return 0;
}
