/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		data_average.c
* Author : 			Fang Ran
* Created Date : 	Apr 30, 2021
* Modified Date : 	Apr 30, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include <stdint.h>
#include <stdlib.h>
#include <data_average.h>


uint16_t GetAverageData(struct AVERAGE_DATA *Acc, float *Result, float Input, uint16_t ExtTrig)
{
	float Average;

	Acc->AccSum += Input;
	Acc->AccCnt++;
	if ((Acc->AccMode == ACC_FIXED_TIMES && Acc->AccCnt >= Acc->AccPeriod)
		|| (Acc->AccMode == ACC_EXT_TRIG && ExtTrig)) {
			Acc->AccFlag = 1;
			*Result = Acc->AccSum / Acc->AccCnt;
			Acc->AccSum = 0;
			Acc->AccCnt = 0;
	} else {
		// no action
	}
	return Acc->AccFlag;
}
