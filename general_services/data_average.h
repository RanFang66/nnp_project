/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		data_average.h
* Author : 			Fang Ran
* Created Date : 	Apr 30, 2021
* Modified Date : 	Apr 30, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef GENERAL_SERVICES_DATA_AVERAGE_H_
#define GENERAL_SERVICES_DATA_AVERAGE_H_

#define ACC_FIXED_TIMES		1
#define ACC_EXT_TRIG		2

struct AVERAGE_DATA {
	uint16_t AccMode;
	uint16_t AccCnt;
	float    AccSum;
	uint16_t AccPeriod;
	uint16_t AccFlag;
};


#endif /* GENERAL_SERVICES_DATA_AVERAGE_H_ */
