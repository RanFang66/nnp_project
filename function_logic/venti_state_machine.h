/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		venti_state_machine.h
* Author : 			Fang Ran
* Created Date : 	Apr 29, 2021
* Modified Date : 	Apr 29, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef FUNCTION_LOGIC_VENTI_STATE_MACHINE_H_
#define FUNCTION_LOGIC_VENTI_STATE_MACHINE_H_

#define INSPIRATION			1
#define EXPIRATION			2
#define	HOLD_BREATH			3

#define VENTI_STATES_NUM	3

struct VENTI_TIMER {
	uint16_t 	TickMs;
	uint16_t 	InspTime;
	uint16_t 	ExpTime;
	uint16_t	VentiTime;
};


#endif /* FUNCTION_LOGIC_VENTI_STATE_MACHINE_H_ */
