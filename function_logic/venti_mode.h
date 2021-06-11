/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		venti_mode.h
* Author : 			Fang Ran
* Created Date : 	Apr 29, 2021
* Modified Date : 	Apr 29, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef FUNCTION_LOGIC_VENTI_MODE_H_
#define FUNCTION_LOGIC_VENTI_MODE_H_

#include <stdint.h>

#define 	VENTI_MODE_NUM		9


#define 	IPPV_MODE		1
#define 	SIPPV_MODE		2
#define 	SIMV_MODE		3
#define 	PSV_MODE		4
#define 	CPAP_MODE		5

#define     NIPPV_MODE		9
#define 	SNIPPV_MODE		10
#define 	NCAPA_MODE		11
#define     HFNC_MODE		12


struct MODE_INPUT_PARA {
	uint16_t 	IFlow;
	uint16_t 	Pinsp;
	uint16_t 	Peep;
	uint16_t 	Ti;
	uint16_t	Te;
	uint16_t 	Freq;
	uint16_t	FiO2;
	uint16_t 	VG;
	uint16_t 	VL;
};

struct MODE_OUTPUT {
	float	 	Paw;
	float	 	Flow;
};

typedef void (*ModeInspFcn)(struct MODE_INPUT_PARA *, struct MODE_OUTPUT *);
typedef void (*ModeExpFcn)(struct MODE_INPUT_PARA *, struct MODE_OUTPUT *);
typedef uint16_t (*ModeInspTrig)(uint16_t);
typedef uint16_t (*ModeExpTrig)(uint16_t);

struct MODE_OPERATIONS {
	ModeInspFcn  		Insp;
	ModeExpFcn			Exp;
	ModeInspTrig		InspTrig;
	ModeExpTrig			ExpTrig;
};


struct VENTI_MODE {
	uint16_t 			  	VentiMode;
	struct MODE_OPERATIONS  *ModeOps;
};

extern struct VENTI_MODE 		*CurVentiMode;
extern struct MODE_INPUT_PARA 	ModeInput;
extern struct MODE_OUTPUT		ModeOutput;


#endif /* FUNCTION_LOGIC_VENTI_MODE_H_ */
