/*!
*********************************************************************************************************
*                           (c) Copyright 2020, Aeonmed Co.Ltd
*                                      All Rights Reserved
*   Project Name: NNP_Dev
*      File Name: nnp_valve_ctrl.c
* 		Compiler: CCSv10
*    Description:
*
* Created Author: fangran
*     Created on: 2021��2��4�� 
* Updated Author: fangran
*     Updated on: 2021��2��4��-����9:30:14
*********************************************************************************************************
*/

#include <public_services/pi_regulator.h>
#include <stdint.h>
#include <stdlib.h>

#include "valve_ctrl.h"



#define LIMITER(X, MAX, MIN) (X > MAX) ? (MAX) : ((X < MIN) ? (MIN) : (X))

void valve_model_init(VALVE_CTRL *v, float gain, float inc, float flow_max)
{
    v->gain = gain;
    v->inc = inc;
    v->flow_max = flow_max;
}

void valve_drive_init(VALVE_DRIVE *d, float duty_thres, float duty_max, uint16_t pwm_period, uint16_t *pwm_output)
{
    d->drive_duty = 0;
    d->duty_max = duty_max;
    d->duty_thres = duty_thres;
    d->pwm_period = pwm_period;
    d->pwm_output = pwm_output;
}

float valve_feedforward_calc(VALVE_CTRL *v)
{
    return v->gain * v->flow_ref + v->inc;
}

float valve_ctrl(VALVE_CTRL *v, float flow_ref, float flow)
{
    float   duty_ff;
    float   duty_fb;

    v->flow_ref = LIMITER(flow_ref, v->flow_max, 0);

    duty_ff = valve_feedforward_calc(v);
    duty_fb = pi_calc(v->pi, v->flow_ref, flow);

    return duty_ff + duty_fb;
}

float valve_drive(VALVE_DRIVE *d, float duty)
{
    d->drive_duty = LIMITER(duty, d->duty_max, 0);

    *(d->pwm_output) = (uint16_t)(d->drive_duty * d->pwm_period);

    return (*(d->pwm_output));
}

//void valve_destroy(VALVE *const v)
//{
//
//}
