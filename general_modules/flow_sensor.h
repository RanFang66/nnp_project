/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		flow_sensor.h
* Author : 			Fang Ran
* Created Date : 	Jun 2, 2021
* Modified Date : 	Jun 2, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef GENERAL_MODULES_FLOW_SENSOR_H_
#define GENERAL_MODULES_FLOW_SENSOR_H_

#define HAF_SENSOR_I2C	&(I2C_TYPE)I2ca
#define HAF_I2C_ADDR	0x49
#define HAF_FULL_SCALE	50

struct FLOW_SENSOR {
	float FlowLast;

	float (*GetFlow)(void);
	void  (*Calibrate)(void);
	void  (*Config)(void);
};


void  FlowSensorConfig(void);
float FlowSensorReadFlow(void);
void  FlowSensorCalibrate(void);

float SFM3x_GetFlow(void);
float HAFx_GetFlow(void);



#endif /* GENERAL_MODULES_FLOW_SENSOR_H_ */
