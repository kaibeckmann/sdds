#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "riot_throughput_pub_sdds_impl.h"

#define SEC_USEC 1000000

int main()
{
	DDS_ReturnCode_t ret;
    Log_debug("Throughput publisher started\n");
	Log_setLvl(5);

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}

    static Throughput throughput_pub;

    uint64_t msg_size_bit = THROUGHPUT_MSG_SIZE * 8;
    uint64_t max_delay = ((SEC_USEC * msg_size_bit)  / (THROUGHPUT_MAX_MBIT * 1000000));

    memset(&throughput_pub, 'x', THROUGHPUT_MSG_SIZE);

    for (;;) {
        ret = DDS_ThroughputDataWriter_write (g_Throughput_writer, &throughput_pub, NULL);
        if (ret != DDS_RETCODE_OK) {
                printf("send error\n");
        }

        usleep(max_delay);
    }
    
    return 0;
}
