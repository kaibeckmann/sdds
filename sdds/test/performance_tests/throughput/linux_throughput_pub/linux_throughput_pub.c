#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "linux_throughput_pub_sdds_impl.h"

#define THROUGHPUT_MAX_DELAY ((1000 * THROUGHPUT_MSG_SIZE) / THROUGHPUT_MAX_MBIT)

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(5);

    static Throughput throughput_pub;

    for (;;) {
        ret = DDS_ThroughputDataWriter_write (g_Throughput_writer, &throughput_pub, NULL);

        usleep(THROUGHPUT_MAX_DELAY);
    }
    
    return 0;
}
