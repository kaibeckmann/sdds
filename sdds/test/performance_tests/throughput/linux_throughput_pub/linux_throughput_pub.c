#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "linux_throughput_pub_sdds_impl.h"

#define SEC_USEC 1000000
#define MSG_SIZE_BIT THROUGHPUT_MSG_SIZE * 8
#define THROUGHPUT_MAX_DELAY ((SEC_USEC * MSG_SIZE_BIT)  / (THROUGHPUT_MAX_MBIT * 1000000))

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
