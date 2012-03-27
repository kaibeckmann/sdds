
/************************/
/* generated file bla */
/* filename: sDDS_Eval */


#ifndef _SDDS_EVAL_H
#define _SDDS_EVAL_H


#include "DDS/DDS_DCPS.h"
#include "sDDS/sdds_types.h"


typedef DDS_DataReader Eval_TemperaturDataReader;



extern Eval_TemperaturDataReader drDataReader;


#define Eval_TemperaturTypSupport DDS_TypeSupport



struct Eval_Temperatur { 
    int16_t temp;
    uint8_t ID;
    uint16_t position;
};
typedef struct Eval_Temperatur Eval_Temperatur;





DDS_ReturnCode_t Eval_TemperaturDataReader_take_next_sample(
	Eval_TemperaturDataReader _this,
	Eval_Temperatur** data_values,
	DDS_SampleInfo *sample_info);

#endif /* TEMPERATURSENSOR_SDDS_H */

