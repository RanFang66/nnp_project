/*!
*********************************************************************************************************
*                           (c) Copyright 2020, Aeon Medical Co.Ltd
*                                      All Rights Reserved
*   Project Name: NNP_Dev
*      File Name: nnp_alarm.c
* 		Compiler: CCSv10
*    Description:
*
* Created Author: fangran
*     Created on: Feb 20, 2021 
* Updated Author: fangran
*     Updated on: Feb 20, 2021-5:08:40 PM
*********************************************************************************************************
*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "alarm_check.h"


uint16_t g_venti_state = 0;

struct ST_ALARM* create_alarm(void)
{
	struct ST_ALARM*  new_alarm = NULL;

	if((new_alarm = (struct ST_ALARM* *)malloc(sizeof(struct ST_ALARM))) == NULL)
		return NULL;

	memset(new_alarm, 0, sizeof(struct ST_ALARM));

	return new_alarm;
}

void
alarm_init(struct ST_ALARM*  alarm, uint16_t premise, uint16_t attr, uint16_t thres, uint16_t thres_recover, uint16_t tsample,
           uint16_t tcontinue, uint16_t trecover, ALARM_JUDGE_HANDLE judge)
{
    alarm->attr.all = attr;
    alarm->premise.all = premise;
    alarm->thres = thres;
    alarm->thres_recover = thres_recover;
    alarm->tsample = tsample;
    alarm->tcontinue = tcontinue;
    alarm->trecover = trecover;
    alarm->alarm_judge = judge;

    alarm->flag = 0;
    alarm->tcnt = 0;
    alarm->tcnt_recover = 0;
}

uint16_t
alarm_update(struct ST_ALARM*  alarm, uint16_t input)
{
    if ((alarm->premise.all & g_venti_state) == 0) {
        alarm->flag = 0;
        return 0;
    }

    if (alarm->attr.bits.enable == 0) {
        alarm->flag = 0;
        return 0;
    }

    if (alarm->flag == 0) {
        if (alarm->alarm_judge(input, alarm->thres))
            alarm->tcnt += alarm->tsample;
        if (alarm->tcnt > alarm->tcontinue) {
            alarm->flag = 1;
            alarm->tcnt_recover = 0;
        }
    } else if (alarm->attr.bits.recoverable) {
        if (alarm->alarm_judge(input, alarm->thres_recover) == 0)
            alarm->tcnt_recover += alarm->tsample;
        if (alarm->tcnt_recover > alarm->trecover) {
            alarm->flag = 0;
            alarm->tcnt = 0;
        }
    } else {
        // tbd
    }

    return alarm->flag;
}

void
alarm_enable(struct ST_ALARM*  alarm)
{
    alarm->attr.bits.enable = 1;
}

void
alarm_disable(struct ST_ALARM*  alarm)
{
    alarm->attr.bits.enable = 0;
}

void
alarm_set_thres(struct ST_ALARM*  alarm, uint16_t thres)
{
    alarm->thres = thres;
}

void
alarm_set_recover_thres(struct ST_ALARM*  alarm, uint16_t thres)
{
    alarm->thres_recover = thres;
}

void
alarm_set_tcontinue(struct ST_ALARM*  alarm, uint16_t t_continue)
{
    alarm->tcontinue = t_continue;
}

void
alarm_set_trecover(struct ST_ALARM*  alarm, uint16_t t_recover)
{
    alarm->trecover = t_recover;
}
