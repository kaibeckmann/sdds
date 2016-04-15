#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "linux_throughput_sub_sdds_impl.h"

#define DURATION_SEC THROUGHPUT_DURATION * 60
#define DURATION_USEC THROUGHPUT_DURATION * 60 * 1000000

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(5);

    static Throughput throughput_sub;
    Throughput *throughput_sub_p = &throughput_sub;

    static struct timeval start, now;
    static long long start_time;
    static long long now_time;
    static long long duration = 0;

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

                gettimeofday(&start, NULL);
                start_time = (start.tv_sec * 1000000 + start.tv_usec);
            }
            bytes_received += THROUGHPUT_MSG_SIZE;
        }
        gettimeofday(&now, NULL);
        now_time = (now.tv_sec * 1000000 + now.tv_usec);
        duration = now_time - start_time;
    }

    FILE* log = fopen(THROUGHPUT_LOG, "w+");

    double bits_recv = bytes_received * 8.0;
    double mbits_recv = bits_recv / 1000000.0;
    double dur_sec = (double) DURATION_SEC;
    
    double mbps = mbits_recv / dur_sec;

    printf("Bytes, Mbit/s\n%016llu, %.2lf", bytes_received, mbps);
    fprintf(log, "Bytes, Mbit/s\n%016llu, %.2lf", bytes_received, mbps);

    fclose(log);
    return 0;
}
