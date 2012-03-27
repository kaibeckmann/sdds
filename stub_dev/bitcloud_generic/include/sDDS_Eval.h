
/************************/
/* generated file bla */
/* filename: sDDS_Eval */


#ifndef _SDDS_EVAL_H
#define _SDDS_EVAL_H


#include "DDS/DDS_DCPS.h"
#include "sDDS/sdds_types.h"


typedef DDS_DataWriter Eval_TemperaturDataWriter;




extern Eval_TemperaturDataWriter dwDataWriter;


#define Eval_TemperaturTypSupport DDS_TypeSupport



struct Eval_Temperatur { 
int16_t temp;
uint8_t ID;
uint16_t position;
};
typedef struct Eval_Temperatur Eval_Temperatur;




DDS_ReturnCode_t Eval_TemperaturDataWriter_write(
	Eval_TemperaturDataWriter _this,
	const Eval_Temperatur* instance_data,
	const DDS_InstanceHandle_t handle);



#endif /* TEMPERATURSENSOR_SDDS_H */

