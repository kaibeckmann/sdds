/*
 * AppControl.c
 *
 *  Created on: Sep 29, 2010
 *      Author: kai
 */

#include "Application.h"
#include "sDDS_Eval.h"

#include <util/delay.h>

#ifndef sDDS_TEST_SENSORAPP
#define sDDS_TEST_SENSORAPP
#endif

#ifdef sDDS_TEST_SENSORAPP

#include "sensors.h"
#include "WSNVisualizer.h"

#define TOPICNAME TempControl
#define KNOTENID 1
#define RAUMID 1

int initSensor(void);
int16_t readSensor(void);
void TempReadCallback(bool result, int16_t data);

char str[8];
uint8_t receivedCount = 0;
uint8_t sendMsg = 0;
volatile int16_t temperatur = 0;
volatile bool fail = false;

void printText(char* str)
{
    if (fail) {
	visializeText("FAIL");
    } else {
	visializeText(str);
    }

}

int initSensor(void)
{

    BSP_OpenTemperatureSensor();

    return 0;

}
int16_t readSensor(void)
{
        BSP_ReadTemperatureData(TempReadCallback);

    return temperatur;
}

void TempReadCallback(bool result, int16_t data)
{
    if (result == true) {
	temperatur = data;
    }
}

int sdds_app_run(void)
{
    static uint8_t i = 0;
    static uint8_t pre = 0;
    static uint32_t count = 0;

    count++;
    //static char c[3] = {'1', '0', '\0'};
    char c = 'I';
    i++;
    switch (i) {
	case 1:
	    c = 'I';
	    break;
	case 2:
	    c = '/';
	    break;
	case 3:
	    c = '-';
	    break;
	case 4:
	    c = '\\';
	    i = 0;
    }

    if (pre++ == 50) {
	pre = 0;
	DDS_ReturnCode_t ret;

	// static DataStructure to fill with content
	Eval_Temperatur dwData;
	Eval_Temperatur* dwData_ptr = &(dwData);

	static uint16_t test = 1;
	dwData.temp = readSensor();
	dwData.ID = KNOTENID;
	//dwData.position = RAUMID;
	dwData.position = test++;
	BSP_SendLcdCmd(LCD_CMD_SYMB_KEY_ON);

	ret = Eval_TemperaturDataWriter_write(dwDataWriter, dwData_ptr, NULL);

	//    if (ret != DDS_RETCODE_OK) {

	//   }

	if (ret == DDS_RETCODE_OK){
	    sendMsg++;
	}

    }
    sprintf(str, "%cS%uR%u", c, sendMsg, receivedCount);
    printText(str);

    return 0;
}

/**
 * Initializes the application
 */
int sdds_app_init(void)
{
    DDS_init();
    BSP_SendLcdCmd(LCD_CMD_SYMB_KEY_OFF);
    BSP_SendLcdCmd(LCD_CMD_SYMB_ATT_OFF);
    return 0;
}

/*
 * Function for reinitialisation. for example after a power shortage
 */
int sdds_app_reInit(void)
{
    return 0;
}

/**
 * function for the application code regarding an poweroff event
 */

int sdds_app_poweroff(void)
{
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

#endif

#ifdef sDDS_TEST_ACTORAPP

#endif
