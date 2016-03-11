#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "linux_throughput_sub_sdds_impl.h"

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
    static long start_time;
    static long now_time;
    static long duration = 0;

    gettimeofday(&start, NULL);
    start_time = (start.tv_sec * 1000000 + start.tv_usec);

    static uint64_t bytes_received = 0;

    while (duration < DURATION_USEC) {
        ret = DDS_ThroughputDataReader_take_next_sample(g_Throughput_reader,
                &throughput_sub_p, NULL);
        if (ret == DDS_RETCODE_OK) {
        		bytes_received += THROUGHPUT_MSG_SIZE;
        }
        gettimeofday(&now, NULL);
        now_time = (now.tv_sec * 1000000 + now.tv_usec);
        duration = now_time - start_time;
    }

    FILE* log = fopen(THROUGHPUT_LOG, "w+");

    double mbps = (double)((bytes_received * 8) / (double)(DURATION_USEC));

    printf("Bytes, Mbit/s\n%08lu, %.2lf", bytes_received, mbps);
    fprintf(log, "Bytes, Mbit/s\n%08lu, %.2lf", bytes_received, mbps);

    fclose(log);
    return 0;
}
