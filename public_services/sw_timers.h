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

#ifndef PUBLIC_SERVICES_SW_TIMERS_H_
#define PUBLIC_SERVICES_SW_TIMERS_H_
#include <stdint.h>

struct SW_TIMER {
    uint16_t 	Tcnt;
    uint16_t	Tsample;
    uint16_t	Texpire;
};

#define SwTimerExpired(Timer) 	(Timer.Tcnt >= Timer.Texpire)
#define ResetSwTimer(Timer) 	(Timer.Tcnt = 0)
#define SwTimerAcc(Timer)		(Timer.Tcnt += Timer.Tsample)


#endif /* PUBLIC_SERVICES_SW_TIMERS_H_ */
