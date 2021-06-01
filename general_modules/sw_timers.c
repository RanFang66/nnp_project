/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		sw_timers.c
* Author : 			Fang Ran
* Created Date : 	Jun 1, 2021
* Modified Date : 	Jun 1, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include <stdint.h>
#include "sw_timers.h"

void InitSwTimer(struct SW_TIMER *Timer, uint16_t Tsample, uint16_t Texpire)
{
	Timer->Tcnt = 0;
	Timer->Tsample = Tsample;
	Timer->Texpire = Texpire;
}

void SetSwTimerExpire(struct SW_TIMER *Timer, uint16_t Expire)
{
	Timer->Texpire = Expire;
}

//uint16_t SwTimerExpired(struct SW_TIMER *Timer)
//{
//	return (Timer->Tcnt >= Timer->Texpire);
//}
//
//void ResetSwTimer(struct SW_TIMER* Timer)
//{
//	Timer->Tcnt = 0;
//}
