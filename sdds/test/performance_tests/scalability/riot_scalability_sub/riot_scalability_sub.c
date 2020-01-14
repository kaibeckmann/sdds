#include <unistd.h>
#include "riot_scalability_sub_sdds_impl.h"
#include "unistd.h"

int main()
{
    DDS_ReturnCode_t ret;
    Log_info("Subscriber started\n");
    Log_setLvl(5);

    if (sDDS_init() == SDDS_RT_FAIL) {
    	return 1;
    }

    static Thermostat thermostat_sub;
    Thermostat *thermostat_sub_p = &thermostat_sub;

    for (;;) {
        ret = DDS_ThermostatDataReader_take_next_sample(g_Thermostat_reader,
                &thermostat_sub_p, NULL);
        if (ret != DDS_RETCODE_NO_DATA) {
            Log_debug("Set temperature %d°C.\n", thermostat_sub_p->temp_c);
        }

        sleep (10);
    }

    return 0;
}