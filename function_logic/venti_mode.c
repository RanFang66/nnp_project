/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		venti_mode.c
* Author : 			Fang Ran
* Created Date : 	Apr 29, 2021
* Modified Date : 	Apr 29, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/


#include <stdint.h>
#include <stdlib.h>

#include "venti_mode.h"

#define 	LPM_TO_MLPS			16.66667F
uint16_t    g_VentTime = 0;
struct MODE_INPUT_PARA 	ModeInput;
struct MODE_OUTPUT		ModeOutput;


struct VENTI_MODE *CurVentiMode;

static void IPPVInsp(struct MODE_INPUT_PARA *Para, struct MODE_OUTPUT *Output)
{
	Output->Flow = Para->IFlow * LPM_TO_MLPS;
	Output->Paw = Para->Pinsp;

}

static void IPPVExp(struct MODE_INPUT_PARA *Para, struct MODE_OUTPUT *Output)
{
	Output->Flow = Para->IFlow * LPM_TO_MLPS;
	Output->Paw = Para->Peep;
}

static uint16_t IPPVInspStart(struct MODE_INPUT_PARA *Para)
{
	if (g_VentTime > Para->Ti) {
		return 1;
	} else {
		return 0;
	}
}

static uint16_t IPPVExpStart(struct MODE_INPUT_PARA *Para)
{
	if (g_VentTime > Para->Ti + Para->Te) {
		return 1;
	} else {
		return 0;
	}
}

static const struct VENTI_MODE VentiModeTbl[VENTI_MODE_NUM]  = {
		{IPPV_MODE, 	{IPPVInsp, 		IPPVExp, 	IPPVInspStart, 		IPPVExpStart} 	},
//		{SIPPV_MODE, 	{SIPPVInsp, 	SIPPVExp,	SIPPVInspStart, 	SIPPVExpStart} 	},
//		{SIMV_MODE,		{SIMVInsp, 		SIMVExp, 	SIMVInspStart, 		SIMVExpStart}	},
//		{PSV_MODE,		{PSVInsp, 		PVSExp, 	PSVInspStart, 		PSVExpStart}	},
//		{CPAP_MODE,		{CPAPInsp, 		CPAPExp, 	CPAPInspStart, 		CPAPExpStart}	},
//		{NIPPV_MODE,    {NIPPVInsp, 	NIPPVExp, 	NIPPVInspStart, 	NIPPVExpStart}	},
//		{SNIPPV_MODE,   {SNIPPVInsp,	SNIPPVExp, 	SNIPPVInspStart, 	SNIPPVExpStart}	},
//		{NCPAP_MODE,    {NIPPVInsp, 	NIPPVExp, 	NIPPVInspStart, 	NIPPVExpStart}	},
//		{NIPPV_MODE,    {NIPPVInsp, 	NIPPVExp, 	NIPPVInspStart, 	NIPPVExpStart}	},
};


uint16_t ChangeVentiMode(uint16_t Mode)
{
    struct MODE_OPERATIONS *op;

	op = VentiModeTbl[Mode].ModeOps;

	CurVentiMode->VentiMode = Mode;
	CurVentiMode->ModeOps = op;

	return Mode;
}


