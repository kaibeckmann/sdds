#include "contiki.h"
#include "atmega_sdds_impl.h"

/*---------------------------------------------------------------------------*/
PROCESS(messung1_contiki, "Messung 1 Contiki");
AUTOSTART_PROCESSES(&messung1_contiki);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(messung1_contiki, ev, data)
{
	static struct etimer g_wait_timer;

	PROCESS_BEGIN();

	sDDS_init();
	Log_setLvl(0);

	Alpha a;
	a.value = 0;

	while (1) {
		if (DDS_AlphaDataWriter_write(g_Alpha_writer, &a,
				NULL) != DDS_RETCODE_OK) {
			// handle error
		}
		a.value++;

		etimer_set(&g_wait_timer, 10 * CLOCK_SECOND);
		PROCESS_YIELD_UNTIL(etimer_expired(&g_wait_timer));
	}


  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
