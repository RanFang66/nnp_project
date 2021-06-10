/*!
*********************************************************************************************************
*                           (c) Copyright 2020, Aeon Medical Co.Ltd
*                                      All Rights Reserved
*   Project Name: NNP_Dev
*      File Name: nnp_valve_ctrl.h
* 		Compiler: CCSv10
*    Description:
*
* Created Author: fangran
*     Created on: 2021年2月3日 
* Updated Author: fangran
*     Updated on: 2021年2月3日-下午7:53:00
*********************************************************************************************************
*/

#ifndef NNP_VALVE_CTRL_H_
#define NNP_VALVE_CTRL_H_


typedef struct VALVE_DRIVE {
    float   	drive_duty;
    float   	duty_max;
    float   	duty_thres;
    uint16_t  	pwm_period;
    uint16_t  	*pwm_output;
} VALVE_DRIVE;


typedef struct VALVE_STRUCT {
    float       flow_max;
    float       flow_ref;

    float       gain;
    float       inc;

    PI_REGU     *pi;
} VALVE_CTRL;


extern void valve_ctrl_init(VALVE_CTRL *v, float gain, float inc, float flow_max);

extern void valve_drive_init(VALVE_DRIVE *d, float duty_thres, float duty_max, uint16_t pwm_period, uint16_t *pwm_output);

extern float valve_ctrl(VALVE_CTRL *v, float flow_ref, float flow);

extern float valve_drive(VALVE_DRIVE *d, float duty);


#endif /* NNP_VALVE_CTRL_H_ */
