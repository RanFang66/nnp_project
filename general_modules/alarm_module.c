/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		alarm_module.c
* Author : 			Fang Ran
* Created Date : 	Jun 1, 2021
* Modified Date : 	Jun 1, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include <public_services/sw_timers.h>
#include <stdint.h>
#include "alarm_module.h"

uint16_t g_SysState = 0;

static uint16_t
OverValueAlarmJudge(void *input, void *thres)
{
	return *(float*)input > *(float*)thres;
}

static uint16_t
UnderValueAlarmJudge(void *input, void *thres)
{
	return *(float*)input < *(float*)thres;
}

static uint16_t
OverValueAlarmRecover(void *input, void *thres)
{
	return *(float*)input < *(float*)thres;
}

static uint16_t
UnderValueAlarmRecover(void *input, void *thres)
{
	return *(float*)input > *(float*)thres;
}

static uint16_t
IOAlarmJudge(void *input, void *target)
{
	return (*(int16_t*)input != *(int16_t*)target);
}

static uint16_t
IOAlarmRecover(void *input, void *target)
{
	return (*(int16_t*)input != *(int16_t*)target);
}


void InitAlarm(struct ALARM_MODULE* Alarm, uint16_t Premise, uint16_t Attr, int16_t Thres, int16_t ThresRecover, JudgeFcn Judge, RecoverFcn Recover)
{
	Alarm->Premise.All = Premise;
	Alarm->Attr.All = Attr;
	Alarm->Thres = Thres;
	Alarm->ThresRecover = ThresRecover;
	switch (Alarm->Attr.bits.Type) {
	case OVER_VALUE_ALARM:
		Alarm->Judge = OverValueAlarmJudge;
		Alarm->Recover = OverValueAlarmRecover;
		break;
	case UNDER_VALUE_ALARM:
		Alarm->Judge = UnderValueAlarmJudge;
		Alarm->Recover = UnderValueAlarmRecover;
		break;
	case IO_ALARM:
		Alarm->Judge = IOAlarmJudge;
		Alarm->Recover = IOAlarmRecover;
		break;
	case COMPLEX_ALARM:
		Alarm->Judge = Judge;
		Alarm->Recover = Recover;
		break;
	default:
		break;
	}

}

uint16_t AlarmCheck(struct ALARM_MODULE *Alarm, void *input)
{
	if ((Alarm->Premise.All & g_SysState) == 0) {
		Alarm->Flag = 0;
		return 0;
	}

	if (Alarm->Attr.bits.Enable == 0) {
		Alarm->Flag = 0;
		return 0;
	}

	if (Alarm->Flag == 0) {
		if (Alarm->Judge(input, &Alarm->Thres)) {
			SwTimerAcc(Alarm->AlarmTimer);
			if (SwTimerExpired(Alarm->AlarmTimer)) {
				Alarm->Flag = 1;
				ResetSwTimer(Alarm->RecoverTimer);
			} else {

			}
		} else {

		}


	} else {
		if (Alarm->Recover(input, &Alarm->ThresRecover)) {
			SwTimerAcc(Alarm->RecoverTimer);
			if (SwTimerExpired(Alarm->RecoverTimer)) {
				Alarm->Flag = 0;
				ResetSwTimer(Alarm->AlarmTimer);
			} else {

			}
		} else {

		}
	}
	return Alarm->Flag;
}
