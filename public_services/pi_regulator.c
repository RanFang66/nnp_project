/*!
*********************************************************************************************************
*                           (c) Copyright 2020, Aeon Medical Co.Ltd
*                                      All Rights Reserved
*   Project Name: NNP_Dev
*      File Name: pi_regulator.c
* 		Compiler: CCSv10
*    Description:
*
* Created Author: fangran
*     Created on: 2021��2��3�� 
* Updated Author: fangran
*     Updated on: 2021��2��3��-����6:38:37
*********************************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "pi_regulator.h"

/*!
 *********************************************************************************************************
 * Description: create a pi regulator module
 *
 * Arguments  : none
 *
 * Returns    : a pointer to pi regulator, if the allocation is failed, return NULL
 *
 * Others     :
 *********************************************************************************************************
 */
PI_REGU *pi_regu_create(void)
{
    PI_REGU *p = (PI_REGU *)malloc(sizeof(struct PI_REGULATOR));

    if (p != NULL)
    {
        pi_regu_init(p, 0, 0, 0, 0);
    }
    return p;
}

/*!
 *********************************************************************************************************
 * Description: Initialize the pi regulator
 *
 * Arguments  : p           the pointer to PI regulator
 *              alpha       alpha parameter of digital pi regulator.
 *                          alpha = kp + ki * Ts (Ts is the control period)
 *              beta        beta parameter of digital pi regulator.
 *                          beta = kp
 *              max         output upper limit of pi regulator.
 *              min         output lower limit of pi regulator.
 *
 * Returns    : none
 *
 * Others     :
 *********************************************************************************************************
 */
void pi_regu_init(PI_REGU *p, float alpha, float beta, float max, float min)
{
    p->alpha = alpha;
    p->beta = beta;
    p->out_max = max;
    p->out_min = min;

    p->ref = 0;
    p->fed = 0;
    p->err = 0;
    p->out = 0;
}

/*!
 *********************************************************************************************************
 * Description: Set alpha and beta parameter of pi regulator
 *
 * Arguments  : p           the pointer to PI regulator
 *              alpha       alpha parameter of digital pi regulator.
 *                          alpha = kp + ki * Ts (Ts is the control period)
 *              beta        beta parameter of digital pi regulator.
 *                          beta = kp
 *
 * Returns    : none
 *
 * Others     :
 *********************************************************************************************************
 */
void pi_set_para(PI_REGU *p, float alpha, float beta)
{
    p->alpha = alpha;
    p->beta = beta;
}

/*!
 *********************************************************************************************************
 * Description: Set output limits of pi regulator
 *
 * Arguments  : p           the pointer to PI regulator
 *              max         output upper limit of pi regulator.
 *              min         output lower limit of pi regulator.
 *
 * Returns    : none
 *
 * Others     :
 *********************************************************************************************************
 */
void pi_set_limit(PI_REGU *p, float max, float min)
{
    p->out_max = max;
    p->out_min = min;
}

/*!
 *********************************************************************************************************
 * Description: calculate the output of pi regulator
 *
 * Arguments  : p           the pointer to PI regulator
 *              ref         reference value of pi regulator
 *              fed         feedback value of pi regulator
 *
 * Returns    : output value of pi regulator (float between out_min and out_max)
 *
 * Others     :
 *********************************************************************************************************
 */
float pi_calc(PI_REGU *p, float ref, float fed)
{
    float err_last = p->err;

    p->ref = ref;
    p->fed = fed;
    p->err = p->ref - p->fed;

    p->out += p->alpha * p->err - p->beta * err_last;

    if (p->out > p->out_max) {
        p->out = p->out_max;
    } else if (p->out < p->out_min) {
        p->out = p->out_min;
    } else {
        // do nothing
    }

    return p->out;
}

/*!
 *********************************************************************************************************
 * Description: free pi regulator
 *
 * Arguments  : p           the pointer to PI regulator
 *
 * Returns    : none
 *
 * Others     :
 *********************************************************************************************************
 */
void pi_destroy(PI_REGU *const p)
{
    if (p != NULL) {
        free(p);
    }
}
