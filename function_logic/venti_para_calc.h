/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		venti_para_calc.h
* Author : 			Fang Ran
* Created Date : 	Apr 30, 2021
* Modified Date : 	Apr 30, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef FUNCTION_LOGIC_VENTI_PARA_CALC_H_
#define FUNCTION_LOGIC_VENTI_PARA_CALC_H_


struct AIRWAY_PARA {
	float R;
	float CStatic;
	float CDynamic;
};


/* monitor data after data process */
struct MONITOR_DATA {
	float Peak;
	float Peep;
	float Pmean;

	float Vti;
	float Vte;
	float Mvi;
	float Mve;

	float FreqTotal;
	float FreqSpont;
	float Ti;
	float Te;
};

/*
 * Real time data from sensor
 */
struct REALTIME_DATA {
	float PAirSrc;		// Air source pressure
	float PO2Src;		// O2 source pressure
	float Pprox;		// Proximity pressure
	float Pinsp;		// Inspiration port pressure
	float PAtmos;		// Atmospheric pressure

	float FlowAir;		// Air source flow
	float FlowO2;		// O2 source flow
	float FLowProx;		// Proximity flow

	float FiO2;			// O2 concentration
};

extern void MonitorDataProcess(struct REALTIME_DATA *RtData, struct MONITOR_DATA *MoniData);



#endif /* FUNCTION_LOGIC_VENTI_PARA_CALC_H_ */
