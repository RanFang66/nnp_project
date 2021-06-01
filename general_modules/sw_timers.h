/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		sw_timers.h
* Author : 			Fang Ran
* Created Date : 	Jun 1, 2021
* Modified Date : 	Jun 1, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef GENERAL_MODULES_SW_TIMERS_H_
#define GENERAL_MODULES_SW_TIMERS_H_

struct SW_TIMER {
    uint16_t 	Tcnt;
    uint16_t	Tsample;
    uint16_t	Texpire;
};

#define SwTimerExpired(Timer) 	(Timer.Tcnt >= Timer.Texpire)
#define ResetSwTimer(Timer) 	(Timer.Tcnt = 0)
#define SwTimerAcc(Timer)		(Timer.Tcnt += Timer.Tsample)


#endif /* GENERAL_MODULES_SW_TIMERS_H_ */
