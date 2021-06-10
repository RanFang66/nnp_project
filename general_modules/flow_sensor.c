/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		flow_sensor.c
* Author : 			Fang Ran
* Created Date : 	Jun 2, 2021
* Modified Date : 	Jun 2, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include <public_services/general_constants.h>
#include <stdint.h>

#include "DSP2833x_bsp.h"
#include "flow_sensor.h"

void  FlowSensorConfig(void)
{

}
float FlowSensorReadFlow(void)
{

}

void  FlowSensorCalibrate(void)
{

}

float SFM3x_GetFlow(void)
{

}

float HAFx_GetFlow(void)
{
	uint16_t buff[2];
	int16_t ret = 0;

	float   data = 0;
	float   flow = 0;

	ret = I2cRead(HAF_SENSOR_I2C, HAF_I2C_ADDR, buff, 2);

	if (ret == 2) {
		data = (float)(buff[0] << 8 | buff[1]);

		flow = HAF_FULL_SCALE * ((data / 16384) - 0.5) / 0.4 * LPM_TO_MLPS;
	}
	return flow;
}

float HAFx_Calibrate(void)
{

}

