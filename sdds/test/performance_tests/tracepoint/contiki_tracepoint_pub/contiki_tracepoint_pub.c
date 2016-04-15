#include "contiki.h"
#include "contiki_tracepoint_pub_sdds_impl.h"
#include <os-ssal/Trace.h>

#define WRITE_MAC

#ifdef WRITE_MAC
#include <avr/eeprom.h>
char atmega128rfa1_macadress[8]     EEMEM;

void write_MACAddr() {
    uint16_t myAddr = (uint16_t) &atmega128rfa1_macadress;
    eeprom_read_byte((uint8_t*) myAddr);
    eeprom_write_byte((uint8_t*)myAddr+7, 0x00);
    eeprom_write_byte((uint8_t*)myAddr+6, 0x21);
    eeprom_write_byte((uint8_t*)myAddr+5, 0x2E);
    eeprom_write_byte((uint8_t*)myAddr+4, 0xFF);
    eeprom_write_byte((uint8_t*)myAddr+3, 0xFF);
    eeprom_write_byte((uint8_t*)myAddr+2, 0x00);
    eeprom_write_byte((uint8_t*)myAddr+1, 0x12);
    eeprom_write_byte((uint8_t*)myAddr+0, 0x10);
}
#endif

PROCESS(contiki_tracepoint_pub, "Publisher for trace point maesuring");
AUTOSTART_PROCESSES(&contiki_tracepoint_pub);

PROCESS_THREAD(contiki_tracepoint_pub, ev, data)
{
	static struct etimer g_wait_timer;

	PROCESS_BEGIN();

#ifdef WRITE_MAC
 write_MACAddr();
#endif

	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(5);

    static Tracepoint tracepoint_pub;
    tracepoint_pub.data = 5;
    
    for (;;) {
        ret = DDS_TracepointDataWriter_write (g_Tracepoint_writer, &tracepoint_pub, NULL);
#ifdef FEATURE_SDDS_TRACING_ENABLED
        Trace_point(SDDS_TRACE_EVENT_DUMMY_3);
        Trace_point(SDDS_TRACE_EVENT_DUMMY_4);
        Trace_point(SDDS_TRACE_EVENT_DUMMY_1);
        Trace_point(SDDS_TRACE_EVENT_DUMMY_2);
        Trace_point(SDDS_TRACE_EVENT_STOP);
#endif
		etimer_set(&g_wait_timer, 1);
		PROCESS_YIELD_UNTIL(etimer_expired(&g_wait_timer));
    }

    PROCESS_END();
}
