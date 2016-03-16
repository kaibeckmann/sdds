#include "contiki.h"
#include "contiki_tracepoint_calibtrate_sdds_impl.h"

PROCESS(contiki_tracepoint_calibtrate, "Publisher for trace point maesuring");
AUTOSTART_PROCESSES(&contiki_tracepoint_calibtrate);

PROCESS_THREAD(contiki_tracepoint_calibtrate, ev, data)
{
	//static struct etimer g_wait_timer;

	PROCESS_BEGIN();

	//static DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(5);

    static bool_t x = true;
    for (;;) {
        Trace_point(!x);
		//etimer_set(&g_wait_timer, 1);
		//PROCESS_YIELD_UNTIL(etimer_expired(&g_wait_timer));
    }

    PROCESS_END();
}
