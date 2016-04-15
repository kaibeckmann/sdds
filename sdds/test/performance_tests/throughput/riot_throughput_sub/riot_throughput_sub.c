#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <xtimer.h>
#include <thread.h>
#include "riot_throughput_sub_sdds_impl.h"

#define DURATION_SEC THROUGHPUT_DURATION * 60
#define DURATION_USEC THROUGHPUT_DURATION * 60 * 1000000

int main()
{
	DDS_ReturnCode_t ret;
    Log_debug("Throughput subscriber started\n");
	Log_setLvl(5);

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}

    static Throughput throughput_sub;
    Throughput *throughput_sub_p = &throughput_sub;

    static uint64_t start_time;
    static uint64_t now_time;
    static uint64_t duration = 0;

    static uint64_t bytes_received = 0;

    bool_t subscribed = false; 

    while (duration < DURATION_USEC) {
        ret = DDS_ThroughputDataReader_take_next_sample(g_Throughput_reader,
                &throughput_sub_p, NULL);
        if (ret != DDS_RETCODE_OK) {
            continue;
        }
        else {
            if (!subscribed) {
                subscribed = true;    

                start_time = xtimer_now64();
            }
            bytes_received += THROUGHPUT_MSG_SIZE;
        }
        now_time = xtimer_now64();
        duration = now_time - start_time;
		thread_yield();
    }


    double bits_recv = bytes_received * 8.0;
	//double mbits_recv = bits_recv / 1000000.0;
	// change to Kbits for 6LoWPAN
    double mbits_recv = bits_recv / 1000.0;
    double dur_sec = (double) DURATION_SEC;
    
    double mbps = mbits_recv / dur_sec;

    fprintf(stderr, "Bytes, Kbit/s\n%016llu, %.2lf", bytes_received, mbps);
    fprintf(stderr, "END\n");

    return 0;
}
