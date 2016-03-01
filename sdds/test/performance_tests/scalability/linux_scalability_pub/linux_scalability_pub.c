#include <unistd.h>
#include "linux_scalability_pub_sdds_impl.h"

int main()
{
	DDS_ReturnCode_t ret;

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}
	Log_setLvl(0);

    static Thermometer thermometer_pub;

    for (;;) {
	thermometer_pub.temp_c = 21;
        ret = DDS_ThermometerDataWriter_write(g_Thermometer_writer, &thermometer_pub, NULL);
        if (ret != DDS_RETCODE_OK) {
            Log_error("Failed to send topic thermometer\n");
	}

        sleep (30);
    }

    return 0;
}
