#include <stdlib.h>
#include <stdio.h>
#include <xtimer.h>
#include <stdint.h>
#include "riot_latency_host_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;
    Log_debug("Latency test started\n");
	Log_setLvl(5);

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}

    static Latency latency_pub;
    static LatencyEcho latencyEcho_sub;
    LatencyEcho* latencyEcho_sub_p = &latencyEcho_sub;

    static uint64_t start_time;
    static uint64_t end_time;
    static uint64_t duration;
    static int msg_count = 0;

    while (msg_count < LATENCY_MSG_COUNT+1) {
        start_time = xtimer_now64();
        latency_pub.time = start_time;

        ret = DDS_LatencyDataWriter_write (g_Latency_writer, &latency_pub, NULL);
        if (ret != DDS_RETCODE_OK) {
            continue;
        }
        
        bool skip = false;

        do {
		    ret = DDS_LatencyEchoDataReader_take_next_sample(g_LatencyEcho_reader,
			    &latencyEcho_sub_p, NULL);

            end_time = xtimer_now64();
            // if it takes more then 10 sec skip the message
            if ( (end_time - start_time) >= 60000000) {
                printf("skip sample\n");
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
                    fprintf(stderr, "%ld\n", duration); 
                }
                msg_count++;
        }
    }

    return 0;
}
