#include "contiki.h"
#include "contiki_tracepoint_sub_sdds_impl.h"

#include <avr/io.h>
#include <util/delay.h>

#define WRITE_MAC

#ifdef WRITE_MAC
#include <avr/eeprom.h>
char atmega128rfa1_macadress[8]     EEMEM;

void write_MACAddr() {
    uint16_t myAddr = (uint16_t) &atmega128rfa1_macadress;
    uint8_t byte = eeprom_read_byte((uint8_t*) myAddr);
    eeprom_write_byte((uint8_t*)myAddr+7, 0x00);
    eeprom_write_byte((uint8_t*)myAddr+6, 0x21);
    eeprom_write_byte((uint8_t*)myAddr+5, 0x2E);
    eeprom_write_byte((uint8_t*)myAddr+4, 0xFF);
    eeprom_write_byte((uint8_t*)myAddr+3, 0xFF);
    eeprom_write_byte((uint8_t*)myAddr+2, 0x00);
    eeprom_write_byte((uint8_t*)myAddr+1, 0x22);
    eeprom_write_byte((uint8_t*)myAddr+0, 0xB9);
}
#endif

void
callback_tracepoint(DDS_DataReader reader);

    static Tracepoint data_used;
    static Tracepoint* data_used_ptr = &data_used;

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


    struct DDS_DataReaderListener listStruct = { .on_data_available =
            &callback_tracepoint};
    DDS_ReturnCode_t dds_ret = DDS_DataReader_set_listener(g_Tracepoint_reader, &listStruct, NULL);
    if(dds_ret == DDS_RETCODE_ERROR){
        printf("unable to set listenr\n");
    }for (;;) {
        //ret = DDS_TracepointDataReader_take_next_sample(g_Tracepoint_reader, &tracepoint_sub_p, NULL);

		etimer_set(&g_wait_timer, 1);
		PROCESS_YIELD_UNTIL(etimer_expired(&g_wait_timer));
    }

    PROCESS_END();
}

void
callback_tracepoint(DDS_DataReader reader){
#ifdef FEATURE_SDDS_TRACING_CALL_LISTNER
    Trace_point(SDDS_TRACE_EVENT_CALL_LISTNER);
#endif
    DDS_TracepointDataReader_take_next_sample(reader, &data_used_ptr, NULL);
#ifdef FEATURE_SDDS_TRACING_ENABLED
    Trace_point(SDDS_TRACE_EVENT_STOP);
#endif
}
