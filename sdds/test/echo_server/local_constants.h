#define PLATFORM_RUMP

#define PLATFORM_LINUX_SDDS_IFACE         "vioif0"
#define PLATFORM_LINUX_SDDS_IP_ADDRESS  	"fe80::5054:0ff:fe62:bf16"
#define PLATFORM_LINUX_SDDS_PORT				23234
#define PLATFORM_LINUX_SDDS_ADDRESS		PLATFORM_LINUX_SDDS_IP_ADDRESS"%"PLATFORM_LINUX_SDDS_IFACE


/*#define UTILS_DEBUG*/
#define FEATURE_SDDS_MULTICAST_ENABLED
#define FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
#define FEATURE_SDDS_DISCOVERY_ENABLED

#define SDDS_NET_MAX_BUF_SIZE						   8192
#define SDDS_NET_MAX_LOCATOR_COUNT 					20
#define SDDS_DISCOVERY_RECEIVE_TIMER				1
#define SDDS_DISCOVERY_PARTICIPANT_TIMER			1
#define SDDS_DISCOVERY_PUBLICATION_TIMER			5
#define SDDS_DISCOVERY_TOPIC_TIMER					0