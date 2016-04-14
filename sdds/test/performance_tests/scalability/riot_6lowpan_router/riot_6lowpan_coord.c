#include <unistd.h>
#include "riot_6lowpan_coord_sdds_impl.h"
#include "unistd.h"

int main()
{
	Log_setLvl(5);

	if (sDDS_init() == SDDS_RT_FAIL) {
		return 1;
	}


    for (;;) {
        sleep (10);
        Log_debug("still running\n");
    }

    return 0;
}
