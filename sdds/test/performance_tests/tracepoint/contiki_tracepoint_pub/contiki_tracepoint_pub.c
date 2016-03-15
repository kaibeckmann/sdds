#include "contiki.h"
#include "contiki_tracepoint_pub_sdds_impl.h"

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
    eeprom_write_byte((uint8_t*)myAddr+0, 0xE3);
}
#endif

PROCESS(contiki_tracepoint_pub, "Publisher for trace point maesuring");
AUTOSTART_PROCESSES(&contiki_tracepoint_pub);

PROCESS_THREAD(contiki_tracepoint_pub, ev, data)
{
    DDRE |= (1 << PE4);
    DDRE |= (1 << PE5);
    DDRE |= (1 << PE7);
    DDRF |= (1 << PF0);

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
    static Tracepoint tracepoint_sub;
    Tracepoint *tracepoint_sub_p = &tracepoint_sub;

    tracepoint_pub.data = 5;

    for (;;) {
        ret = DDS_TracepointDataWriter_write (g_Tracepoint_writer, &tracepoint_pub, NULL);
        if (ret != DDS_RETCODE_OK)
            printf ("Failed to send topic tracepoint\n");

        PORTE |= (1 << PE4); 
        PORTE |= (1 << PE5); 
        PORTE |= (1 << PE7); 
        PORTF |= (1 << PF0); 

        _delay_ms(500); 

        PORTE &= 0x00;
        PORTF &= 0x00;

        _delay_ms(500); 

		etimer_set(&g_wait_timer, 1 * CLOCK_SECOND);
		PROCESS_YIELD_UNTIL(etimer_expired(&g_wait_timer));
    }

    PROCESS_END();
}
