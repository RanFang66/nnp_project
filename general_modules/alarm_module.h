/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		alarm_module.h
* Author : 			Fang Ran
* Created Date : 	Jun 1, 2021
* Modified Date : 	Jun 1, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef GENERAL_MODULES_ALARM_MODULE_H_
#define GENERAL_MODULES_ALARM_MODULE_H_

#define OVER_VALUE_ALARM			0
#define UNDER_VALUE_ALARM			1
#define IO_ALARM			2
#define COMPLEX_ALARM				3

union ALARM_ATTR {
    uint16_t All;
    struct BITS {
    	uint16_t Type		  :2;
        uint16_t Enable       :1;
        uint16_t Severe       :1;
        uint16_t Recoverable  :1;
        uint16_t Reserved     :11;
    }bits;
};

union ALARM_PREMISE {
    uint16_t All;
    struct PREMISE_BITS {
        uint16_t Standby       :1;
        uint16_t Inspiration   :1;
        uint16_t Expiration    :1;
        uint16_t Debug         :1;
        uint16_t Reserved      :12;
    }bits;
};

typedef uint16_t (*JudgeFcn)(void *, void *);
typedef uint16_t (*RecoverFcn)(void *, void *);

struct ALARM_MODULE {
    uint16_t 				Flag;
    union ALARM_PREMISE		Premise;
    union ALARM_ATTR		Attr;

    struct SW_TIMER			AlarmTimer;
    struct SW_TIMER			RecoverTimer;

    float			Thres;
    float			ThresRecover;

    JudgeFcn		Judge;
    RecoverFcn		Recover;
};

#endif /* GENERAL_MODULES_ALARM_MODULE_H_ */
