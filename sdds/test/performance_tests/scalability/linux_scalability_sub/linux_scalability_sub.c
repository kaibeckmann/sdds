#include <unistd.h>
#include "linux_scalability_sub_sdds_impl.h"

int main()
{
    DDS_ReturnCode_t ret;

    if (sDDS_init() == SDDS_RT_FAIL) {
    	return 1;
    }
    Log_setLvl(0);

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
