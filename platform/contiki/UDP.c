#include "sDDS.h"

#include <contiki.h>
#include <contiki-net.h>
#include <rpl.h>

#include <assert.h>

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define UIP_IP_BUF ((struct uip_ip_hdr*)&uip_buf[UIP_LLH_LEN])
#define UIP_UDP_BUF ((struct uip_udp_hdr*)&uip_buf[uip_l2_l3_hdr_len])

#ifndef PLATFORM_CONTIKI_SDDS_PORT
#define PLATFORM_CONTIKI_SDDS_PORT 23234
#endif

#define PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_ADDRESS                         SDDS_BUILTIN_MULTICAST_ADDRESS
#define PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PARTICIPANT_ADDRESS             SDDS_BUILTIN_PARTICIPANT_ADDRESS
#define PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_TOPIC_ADDRESS                   SDDS_BUILTIN_TOPIC_ADDRESS
#define PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_SUB_PUB_ADDRESS                 SDDS_BUILTIN_SUB_PUB_ADDRESS
#define PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PAR_STATE_MSG_ADDRESS           SDDS_BUILTIN_PAR_STATE_MSG_ADDRESS

#define PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PORT_OFF                        20

#ifndef PLATFORM_CONTIKI_SDDS_ADDRESS
#define PLATFORM_CONTIKI_SDDS_ADDRESS "::"
#endif

#ifdef FEATURE_SDDS_MULTICAST_ENABLED
#define NETSTACK_CONF_WITH_IPV6 1
#define UIP_CONF_ROUTER			0
#define	UIP_CONF_IPV6_MULTICAST 1
#define UIP_CONF_IPV6_RPL		1

#include "net/ipv6/multicast/uip-mcast6-engines.h"

#define UIP_MCAST6_CONF_ENGINE UIP_MCAST6_ENGINE_ROLL_TM

#define ROLL_TM_CONF_IMIN_1         64

#undef UIP_CONF_IPV6_RPL
#undef UIP_CONF_ND6_SEND_RA
#undef UIP_CONF_ROUTER
#define UIP_CONF_ND6_SEND_RA         0
#define UIP_CONF_ROUTER              1
#define UIP_MCAST6_ROUTE_CONF_ROUTES 1

#undef UIP_CONF_DS6_NBR_NBU
#undef UIP_CONF_DS6_ROUTE_NBU
#define UIP_CONF_DS6_NBR_NBU        10
#define UIP_CONF_DS6_ROUTE_NBU      10
#endif

// IF BUILTIN
Locator_t* g_builtin_topic_net_address;
// ENDIF

struct Contiki_Locator {
    Locator_t sdds_locator;
    uip_ipaddr_t address;
    uint16_t port;
};

typedef struct Contiki_Locator Contiki_Locator_t;
typedef struct Contiki_Locator* Contiki_Locator;

// global variables
struct simple_udp_connection g_connection;
struct simple_udp_connection g_multi_connection;
static NetBuffRef_t g_incoming_buffer;

void
receive(struct simple_udp_connection* connection,
        uip_ipaddr_t const* src_addr, uint16_t src_port,
        uip_ipaddr_t const* dest_addr, uint16_t dest_port, uint8_t const* data,
        uint16_t data_len);

rc_t
Network_Multicast_init();

rc_t
Network_init(void) {
//	uip_ipaddr_t address;

//	uiplib_ipaddrconv(PLATFORM_CONTIKI_SDDS_ADDRESS, &address);

    uip_init();

    NetBuffRef_init(&g_incoming_buffer);

//	mcast_conn = udp_new(NULL, UIP_HTONS(PLATFORM_CONTIKI_SDDS_PORT), NULL);

    // Funktioniert nicht mit multicast zusammen
    if (simple_udp_register(&g_connection, PLATFORM_CONTIKI_SDDS_PORT, NULL, 0,
                            receive) != 1) {
        return 1;
    }

    if (simple_udp_register(&g_multi_connection, (PLATFORM_CONTIKI_SDDS_PORT+PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PORT_OFF), NULL, 0,
                            receive) != 1) {
        return 1;
    }

#ifdef FEATURE_SDDS_MULTICAST_ENABLED
    Network_Multicast_init();
#endif

    return SDDS_RT_OK;
}

void
receive(struct simple_udp_connection* connection,
        uip_ipaddr_t const* src_addr, uint16_t src_port,
        uip_ipaddr_t const* dest_addr, uint16_t dest_port, uint8_t const* data,
        uint16_t data_len) {
    Locator_t* locator;
    Contiki_Locator_t this_locator;

    /* make gcc happy */
    (void) connection;
    (void) dest_port;

    // ff02:0000:0000:0000:0000:0000:0000:0010
#ifdef UTILS_DEBUG
    char srcAddr[40];
    memset(srcAddr, 0, 40);
    sprintf(srcAddr, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            ((uint8_t*)dest_addr)[0], ((uint8_t*)dest_addr)[1], ((uint8_t*)dest_addr)[2], ((uint8_t*)dest_addr)[3],
            ((uint8_t*)dest_addr)[4], ((uint8_t*)dest_addr)[5], ((uint8_t*)dest_addr)[6], ((uint8_t*)dest_addr)[7],
            ((uint8_t*)dest_addr)[8], ((uint8_t*)dest_addr)[9], ((uint8_t*)dest_addr)[10], ((uint8_t*)dest_addr)[11],
            ((uint8_t*)dest_addr)[12], ((uint8_t*)dest_addr)[13], ((uint8_t*)dest_addr)[14], ((uint8_t*)dest_addr)[15]);

    printf("---------> connection from: %s\n", srcAddr);
#endif

    NetBuffRef_renew(&g_incoming_buffer);

    if (data_len > 0 && data_len > g_incoming_buffer.frame_start->size) {
        printf("ist: %d, soll: %d\n", data_len, g_incoming_buffer.frame_start->size);
        Log_error("contiki: udp packet too big, discarded\n");
        return;
    }

#ifdef FEATURE_SDDS_TRACING_ENABLED
#if defined (FEATURE_SDDS_TRACING_RECV_NORMAL) || defined (FEATURE_SDDS_TRACING_RECV_ISOLATED)
#ifdef FEATURE_SDDS_TRACING_RECV_PAKET
        Trace_point(SDDS_TRACE_EVENT_DUMMY_1);
        Trace_point(SDDS_TRACE_EVENT_DUMMY_2);
        Trace_point(SDDS_TRACE_EVENT_DUMMY_3);
        Trace_point(SDDS_TRACE_EVENT_RECV_PAKET);
#endif
#endif
#endif

    memcpy(g_incoming_buffer.buff_start, data, data_len);
    //uip_ipaddr_copy(&this_locator.address, &UIP_IP_BUF->srcipaddr);
    uip_ipaddr_copy(&this_locator.address, src_addr);
    //this_locator.port = UIP_UDP_BUF->srcport;
    this_locator.port = src_port;

    if (LocatorDB_findLocator((Locator_t*) &this_locator, &locator) != SDDS_RT_OK) {
        // the locator is not yet present, create a new one
        Contiki_Locator contiki_locator;

        if (LocatorDB_newLocator(&locator) != SDDS_RT_OK) {
            Log_error("contiki: no free locator objects\n");
            return;
        }

        contiki_locator = (Contiki_Locator) locator;
        uip_ipaddr_copy(&contiki_locator->address, src_addr);
        contiki_locator->port = src_port;
    }

    // increase the reference count for the newly created locator
    Locator_upRef(locator);

    // make sure the locator is known as non-empty and sender
    locator->isEmpty = false;
    locator->isSender = true;

    if (g_incoming_buffer.locators->add_fn(g_incoming_buffer.locators, locator) != SDDS_RT_OK) {
        Locator_downRef(locator);
        NetBuffRef_renew(&g_incoming_buffer);
        return;
    }

#if defined(SDDS_TOPIC_HAS_PUB) || defined(FEATURE_SDDS_BUILTIN_TOPICS_ENABLED)
    // process the frame
    DataSink_processFrame(&g_incoming_buffer);
#endif
    // and finally decrement the locator again
    Locator_downRef(locator);
    NetBuffRef_renew(&g_incoming_buffer);
}

rc_t
Network_send(NetBuffRef_t* buffer) {
#ifdef FEATURE_SDDS_TRACING_ENABLED
#ifdef FEATURE_SDDS_TRACING_SEND_PAKET
    Trace_point(SDDS_TRACE_EVENT_SEND_PAKET);
#endif
#endif
    struct uip_udp_conn* con;
    int port;

    Locator_t* loc = buffer->locators->first_fn(buffer->locators);
    while (loc != NULL) {
        uip_ipaddr_t address;
        Contiki_Locator locator;

        locator = (Contiki_Locator) loc;

        if (loc->type == SDDS_LOCATOR_TYPE_MULTI) {
            con = g_multi_connection.udp_conn;
            port = PLATFORM_CONTIKI_SDDS_PORT + PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PORT_OFF;
        }
        else if (loc->type == SDDS_LOCATOR_TYPE_UNI) {
            con = g_connection.udp_conn;
            port = PLATFORM_CONTIKI_SDDS_PORT;
        }

        address = locator->address;

        Log_debug("sending %d bytes to 0x%x buffer addr %p\n", buffer->curPos,
                  locator->address.u8[15], buffer);

#ifdef UTILS_DEBUG
        Log_debug("Netbuffer:\n");
        for (int i = 0; i < buffer->curPos; i++) {
            printf("[%x] ", buffer->buff_start[i]);
        }
        printf("\n");
#endif

        uip_udp_packet_sendto(con, buffer->buff_start, buffer->curPos, &address, UIP_HTONS(port));

        loc = buffer->locators->next_fn(buffer->locators);
    }

    return SDDS_RT_OK;
}

bool_t
Locator_isEqual(Locator_t* locator1, Locator_t* locator2) {
    Contiki_Locator contiki_locator_1;
    Contiki_Locator contiki_locator_2;

    contiki_locator_1 = (Contiki_Locator) locator1;
    contiki_locator_2 = (Contiki_Locator) locator2;

    // return true if address and port is equal
    return uip_ipaddr_cmp(&contiki_locator_1->address,
                          &contiki_locator_2->address)
           && contiki_locator_1->port == contiki_locator_2->port;
}

rc_t
Network_getFrameBuff(NetFrameBuff* buffer) {
    size_t size;

    size = SDDS_NET_MAX_BUF_SIZE * sizeof(byte_t);
    size += sizeof(struct NetFrameBuff_t);

    *buffer = Memory_alloc(size);

    if (*buffer == NULL) {
        Log_error("contiki: out of memory\n");
        return SDDS_RT_NOMEM;
    }

    memset(*buffer, 0, size);
    (*buffer)->size = SDDS_NET_MAX_BUF_SIZE;

    return SDDS_RT_OK;
}

rc_t
Network_getPayloadBegin(size_t* startByte) {
    *startByte = sizeof(struct NetFrameBuff_t);

    return SDDS_RT_OK;
}

rc_t
Network_setAddressToLocator(Locator_t* loc, char* addr) {

    if (loc == NULL || addr == NULL) {
        return SDDS_RT_BAD_PARAMETER;
    }
    Contiki_Locator l = (Contiki_Locator) loc;

    uiplib_ipaddrconv(addr, &l->address);
    l->port = UIP_HTONS(PLATFORM_CONTIKI_SDDS_PORT);

    return SDDS_RT_OK;
}

rc_t
Network_createLocator(Locator_t** loc) {
    Contiki_Locator contiki_locator;

    contiki_locator = Memory_alloc(sizeof(Contiki_Locator_t));

    if (contiki_locator == NULL) {
        Log_error("contiki: out of memory\n");
        return SDDS_RT_NOMEM;
    }
    *loc = (Locator_t*) contiki_locator;

    // set type for recvLoop
    (*loc)->type = SDDS_LOCATOR_TYPE_UNI;

    return Network_setAddressToLocator(*loc,
                                       PLATFORM_CONTIKI_SDDS_ADDRESS);

}

rc_t
Network_setMulticastAddressToLocator(Locator_t* loc, char* addr) {
    if (loc == NULL || addr == NULL) {
        return SDDS_RT_BAD_PARAMETER;
    }
    Contiki_Locator l = (Contiki_Locator) loc;

    uiplib_ipaddrconv(addr, &l->address);
    l->port = UIP_HTONS(PLATFORM_CONTIKI_SDDS_PORT + PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PORT_OFF);

    return SDDS_RT_OK;
}

rc_t
Network_createMulticastLocator(Locator_t** loc) {
    Contiki_Locator contiki_locator;

    contiki_locator = Memory_alloc(sizeof(Contiki_Locator_t));

    if (contiki_locator == NULL) {
        Log_error("contiki: out of memory\n");
        return SDDS_RT_NOMEM;
    }

    *loc = (Locator_t*) contiki_locator;

    // set type for recvLoop
    (*loc)->type = SDDS_LOCATOR_TYPE_MULTI;

    return Network_setMulticastAddressToLocator(*loc,
                                                PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_ADDRESS);
}

rc_t
Network_Multicast_joinMulticastGroup(char* group) {
    uip_ipaddr_t addr;
    uip_ds6_maddr_t* rv;

    /*
     * IPHC will use stateless multicast compression for this destination
     * (M=1, DAC=0), with 32 inline bits (1E 89 AB CD)
     */
    uiplib_ipaddrconv(group, &addr);
    rv = uip_ds6_maddr_add(&addr);

    if (rv) {
        PRINTF("Joined multicast group ");
        PRINT6ADDR(&uip_ds6_maddr_lookup(&addr)->ipaddr);
        PRINTF("\n");

        return SDDS_RT_OK;
    }

    return SDDS_RT_FAIL;
}

rc_t
Network_setPlatformAddressToLocator(Locator_t* loc) {
    return Network_setAddressToLocator(loc, PLATFORM_CONTIKI_SDDS_ADDRESS);
}

rc_t
Network_Multicast_init() {
    uip_ipaddr_t addr;

    /* First, set our v6 global */
    uiplib_ipaddrconv("aaaa::0", &addr);
    uip_ds6_set_addr_iid(&addr, &uip_lladdr);
    uip_ds6_addr_add(&addr, 0, ADDR_AUTOCONF);

    rc_t ret;

    ret = Network_Multicast_joinMulticastGroup(PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_ADDRESS);
    if (ret != SDDS_RT_OK) {
        printf("ERROR\n");
    }

    ret = Network_Multicast_joinMulticastGroup(PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PAR_STATE_MSG_ADDRESS);
    if (ret != SDDS_RT_OK) {
        printf("ERROR\n");
    }

    ret = Network_Multicast_joinMulticastGroup(PLATFORM_CONTIKI_SDDS_BUILTIN_MULTICAST_PARTICIPANT_ADDRESS);
    if (ret != SDDS_RT_OK) {
        printf("ERROR\n");
    }

    return SDDS_RT_OK;
}

rc_t
Locator_getAddress(Locator_t* l, char* srcAddr, size_t max_addr_len) {
    if (max_addr_len < 40) {
        return SDDS_RT_BAD_PARAMETER;
    }
    uip_ipaddr_t* addr = &((Contiki_Locator) l)->address;
    sprintf(srcAddr, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            ((uint8_t*)addr)[0], ((uint8_t*)addr)[1], ((uint8_t*)addr)[2], ((uint8_t*)addr)[3],
            ((uint8_t*)addr)[4], ((uint8_t*)addr)[5], ((uint8_t*)addr)[6], ((uint8_t*)addr)[7],
            ((uint8_t*)addr)[8], ((uint8_t*)addr)[9], ((uint8_t*)addr)[10], ((uint8_t*)addr)[11],
            ((uint8_t*)addr)[12], ((uint8_t*)addr)[13], ((uint8_t*)addr)[14], ((uint8_t*)addr)[15]);
    return SDDS_RT_OK;
}
