#include <unistd.h>
#include "linux_scalability_pub_sub_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(0);

    static Thermometer thermometer_sub;
    Thermometer *thermometer_sub_p = &thermometer_sub;
    static Thermostat thermostat_pub;

    for (;;) {
        short temp = 0;
	    int count = 0;
	    while (true) {
		    thermometer_sub_p->temp_c = 0;

		    ret = DDS_ThermometerDataReader_take_next_sample(g_Thermometer_reader,
			    &thermometer_sub_p, NULL);
		    if (ret == DDS_RETCODE_NO_DATA) {
		    	break;
		    }	
		    temp += thermometer_sub_p->temp_c;
		    count++;
	    };

	    if (count > 0) {
		    thermostat_pub.temp_c = temp/count;

		    ret = DDS_ThermostatDataWriter_write (g_Thermostat_writer, &thermostat_pub, NULL);
		    if (ret != DDS_RETCODE_OK)
		        Log_error("Failed to send topic thermostat\n");
	    }
        sleep (10);
    }

    return 0;
}
