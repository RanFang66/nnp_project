/*!
*********************************************************************************************************
*                           (c) Copyright 2020, Aeon Medical Co.Ltd
*                                      All Rights Reserved
*   Project Name: NNP_Dev
*      File Name: nnp_alarm.h
* 		Compiler: CCSv10
*    Description:
*
* Created Author: fangran
*     Created on: Feb 20, 2021 
* Updated Author: fangran
*     Updated on: Feb 20, 2021-4:40:28 PM
*********************************************************************************************************
*/

#ifndef ALARM_CHECK_H_
#define ALARM_CHECK_H_

typedef uint16_t (*ALARM_JUDGE_HANDLE)(uint16_t input, uint16_t thres);

#define ALARM_ENABLE    (1U)
#define ALARM_SEVERE    (1U << 1)
#define ALARM_RECOVER   (1U << 2)


typedef union ATTR {
    uint16_t all;
    struct BITS {
        uint16_t enable       :1;
        uint16_t severe       :1;
        uint16_t recoverable  :1;
        uint16_t reserved     :13;
    }bits;
}ALARM_ATTR;

typedef union PREMISE {
    uint16_t all;
    struct PREMISE_BITS {
        uint16_t standby       :1;
        uint16_t inspiration   :1;
        uint16_t expiration    :1;
        uint16_t debug         :1;
        uint16_t reserved      :12;
    }bits;
}ALARM_PREMISE;

struct ST_ALARM {
    ALARM_PREMISE       premise;
    ALARM_ATTR          attr;

    uint16_t            flag;
    uint16_t            input;
    uint16_t            thres;
    uint16_t            thres_recover;

    uint16_t            tcnt;
    uint16_t            tcnt_recover;
    uint16_t            tsample;
    uint16_t            tcontinue;
    uint16_t            trecover;

    ALARM_JUDGE_HANDLE  alarm_judge;
};

typedef struct ST_ALARM *ALARM;

extern void alarm_init(struct ST_ALARM* alarm, uint16_t premise, uint16_t attr, uint16_t thres, uint16_t thres_recover,
                       uint16_t tsample, uint16_t tcontinue, uint16_t trecover, ALARM_JUDGE_HANDLE judge);
extern uint16_t alarm_update(struct ST_ALARM*  alarm, uint16_t input);
extern void alarm_enable(struct ST_ALARM*  alarm);
extern void alarm_disable(struct ST_ALARM*  alarm);

#endif /* ALARM_CHECK_H_ */
