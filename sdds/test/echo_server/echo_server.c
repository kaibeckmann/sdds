#define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "echo_server_sdds_impl.h"

void
print_ip () {
   struct ifaddrs *ifaddr, *ifa;
   int family, s, n;
   char host[NI_MAXHOST];
   if (getifaddrs(&ifaddr) == -1) {
       perror("getifaddrs");
       exit(EXIT_FAILURE);
   }
   /* Walk through linked list, maintaining head pointer so we
      can free list later */
   for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
       if (ifa->ifa_addr == NULL)
           continue;

       family = ifa->ifa_addr->sa_family;
       /* For an AF_INET* interface address, display the address */
       if (family == AF_INET || family == AF_INET6) {
           s = getnameinfo(ifa->ifa_addr,
                   (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                         sizeof(struct sockaddr_in6),
                   host, NI_MAXHOST,
                   NULL, 0, NI_NUMERICHOST);
           if (s != 0) {
               printf("getnameinfo() failed: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }
           printf("%s\t\taddress: <%s>\n",ifa->ifa_name, host);

       }
   }
   freeifaddrs(ifaddr);
}


int main() {
    printf ("Started rumprun (echo server)\n");
	Log_setLvl (1);
	DDS_ReturnCode_t ret;
	ret = sDDS_init ();
    print_ip ();
    NodeConfig_getNodeID ();
    assert (ret == DDS_RETCODE_OK);

    //  Create sub samples
    /*Strings strings_sub;*/
    /*Strings *strings_sub_p = &strings_sub;*/
    Numbers numbers_sub;
    Numbers *numbers_sub_p = &numbers_sub;

    for (;;) {
        //  Read strings sample and echo it
        /*ret = DDS_StringsDataReader_take_next_sample(g_Strings_reader, &strings_sub_p, NULL);*/
        /*if (ret != DDS_RETCODE_NO_DATA) {*/
            /*printf ("Got strings\n");*/
            /*ret = DDS_StringsEchoDataWriter_write (g_StringsEcho_writer,*/
                                                   /*(StringsEcho *) strings_sub_p,*/
                                                   /*NULL);*/
            /*assert (ret == DDS_RETCODE_OK);*/
        /*}*/

        //  Read numbers sample and echo it
        ret = DDS_NumbersDataReader_take_next_sample(g_Numbers_reader, &numbers_sub_p, NULL);
        if (ret != DDS_RETCODE_NO_DATA) {
            printf ("Got numbers\n");
            ret = DDS_NumbersEchoDataWriter_write (g_NumbersEcho_writer,
                                                   (NumbersEcho *) numbers_sub_p,
                                                   NULL);
            assert (ret == DDS_RETCODE_OK);
        }

        usleep (200);
    }

    printf ("OK\n");
    return 0;
}
