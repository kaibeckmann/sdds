#include <stdio.h>
#include <thread.h>
#include "riot_latency_echo_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;   
    Log_debug("Echo started\n");
	Log_setLvl(0);

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}

    static Latency latency_sub;
    Latency* latency_sub_p = &latency_sub;

    while (true) {
        do {
		    ret = DDS_LatencyDataReader_take_next_sample(g_Latency_reader, &latency_sub_p, NULL);
            thread_yield();
        } while (ret != DDS_RETCODE_OK); 
        Log_info("Got Data sample time %ld\n", latency_sub_p->time);

        do {
            ret = DDS_LatencyEchoDataWriter_write (g_LatencyEcho_writer, (LatencyEcho*) latency_sub_p, NULL);
        } while (ret != DDS_RETCODE_OK);
    }

    return 0;
}
