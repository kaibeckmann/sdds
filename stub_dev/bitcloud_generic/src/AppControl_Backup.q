/*
 * AppControl.c
 *
 *  Created on: Aug 9, 2010
 *      Author: kai
 */

#include "Application.h"
#include "WSNVisualizer.h"
#include "sDDS/NetBuffRef.h"
#include "sDDS/Network.h"
#include <stdio.h>str

struct NetBuffRef_t bufMem;
NetBuffRef buf = &bufMem;
Locator loc;

char str[8];
uint8_t receivedCount = 0;
uint8_t sendMsg = 0;

volatile bool fail = false;

void printText(char* str){
    if (fail){
	visializeText("FAIL");
    } else {
	visializeText(str);
    }

}

int sdds_app_run(void)
{
    static uint8_t i = 0;
    static uint8_t pre = 0;
    static uint32_t count = 0;

    char c = '!';

    count++;
 //   static char c[3] = {'|', '0', '\0'};

    i++;
    switch (i) {
	case 1 : c = '!';
	break;
	case 2 : c = '/';
	break;
	case 3 : c = '-';
	break;
	case 4 : c = '\\';
	i = 0;
    }



//    ((uint8_t)buf->buff_start[3])++;

    if (pre++ == 100){
	pre =0;
	/*
	buf->buff_start[3] = count;
	buf->curPos = 8;
	*/
	size_t s = sprintf(buf->buff_start, "start 0x%x %u end", CS_NWK_ADDR, count);

	buf->curPos = s+1;

	if (Network_send(buf) == SDDS_RT_OK){


	}

    }
    if (CS_NWK_ADDR==0x0023){
	sprintf(str, "%cS%uR%u", c, sendMsg, receivedCount );
	printText(str);
    }


    return 0;
}

void sdds_app_sendOK(void)
{
    sendMsg++;
}

void sdds_app_fail(void)
{
    fail = true;
}

int sdds_app_tmpMsg(NetBuffRef bufIn)
{
    if (CS_NWK_ADDR==0x0042){
	printText(bufIn->buff_start);
    }

    receivedCount++;

    return 0;
}

/**
 * Initializes the application
 */
int sdds_app_init(void)
{

    NetBuffRef_init(buf);
    LocatorDB_init();


    /*
    buf->buff_start[0] = 0xC0;
    buf->buff_start[1] = 0xFF;
    buf->buff_start[2] = 0xEE;
    buf->curPos = 3;
    */
    Network_createLocator(&loc);
    buf->addr = loc;

    return 0;
}
