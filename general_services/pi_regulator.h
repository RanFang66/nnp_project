/*!
 *********************************************************************************************************
 *                           (c) Copyright 2020, Aeon Medical Co.Ltd
 *                                      All Rights Reserved
 *   Project Name: NNP_Dev
 *      File Name: pi_regulator.h
 * 		Compiler: CCSv10
 *    Description:
 *
 * Created Author: fangran
 *     Created on: 2021年2月3日
 * Updated Author: fangran
 *     Updated on: 2021年2月3日-下午5:14:31
 *********************************************************************************************************
 */

#ifndef PI_REGULATOR_H_
#define PI_REGULATOR_H_

/*!
 * The structure of PI regulator.
 * Description: Implemented incremental pi regulator.
 *              out += alpha*err-beta*err_last.
 *              the output of pi regulator is limited by out_max and out_min.
 */
typedef struct PI_REGULATOR
{
    float   ref;        /*!< reference value */
    float   fed;        /*!< feedback value  */
    float   err;        /*!< error of reference and feedback value */
    float   out;        /*!< output of pi regulator */

    float   alpha;      /*!< alpha parameter */
    float   beta;       /*!< beta parameter */
    float   out_max;    /*!< output upper limit */
    float   out_min;    /*!< output lower limit */
}PI_REGU;
#define PI_REGU_DEFAULTS {0, 0, 0, 0, 0, 0, 0, 0}

extern PI_REGU *pi_regu_create(void);

extern void pi_regu_init(PI_REGU *p, float alpha, float beta, float max, float min);
extern void pi_set_para(PI_REGU *p, float alpha, float beta);
extern void pi_set_limit(PI_REGU *p, float max, float min);
extern float pi_calc(PI_REGU *p, float ref, float fed);

extern void pi_destroy(PI_REGU *const p);

#endif /* PI_REGULATOR_H_ */
