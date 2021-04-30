/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		venti_para_calc.c
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

#include "venti_state_machine.h"
#include "venti_para_calc.h"

void PressureDataProcess(struct REALTIME_DATA *RtData, struct MONITOR_DATA *MoniData, uint16_t VentiPhase)
{
	float Paw = RtData->Pprox;
	static float Pmax = 0;

	if (VentiPhase == INSPIRATION) {
		if (Paw > Pmax) {
			Pmax = Paw;
		}
	} else if (VentiPhase == EXPIRATION) {
		MoniData->Ppeak = Pmax;
		Pmax = 0;
	} else {
		// no action
	}



}

void MonitorDataProcess(struct REALTIME_DATA *RtData, struct MONITOR_DATA *MoniData)
{

}
