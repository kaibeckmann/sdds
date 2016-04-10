#include <unistd.h>
#include "riot_scalability_pub_sdds_impl.h"
#include "unistd.h"

int main()
{
    DDS_ReturnCode_t ret;
    Log_info("Publisher started\n");
    Log_setLvl(5);

    if (sDDS_init() == SDDS_RT_FAIL) {
        return 1;
    }

    static Thermostat thermostat_pub;

    for (;;) {
	thermostat_pub.temp_c = 21;
	ret = DDS_ThermostatDataWriter_write (g_Thermostat_writer, &thermostat_pub, NULL);
	if (ret != DDS_RETCODE_OK) {
	    Log_error("Failed to send topic thermostat\n");
	}

        sleep(30);
    }

    return 0;
}
