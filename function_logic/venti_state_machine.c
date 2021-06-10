/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		venti_state_machine.c
* Author : 			Fang Ran
* Created Date : 	Apr 29, 2021
* Modified Date : 	Apr 29, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include <public_services/state_machine.h>
#include <stdint.h>
#include <stdlib.h>

#include "ucos_ii.h"

#include "venti_mode.h"
#include "venti_state_machine.h"

struct STATE_MACHINE* VentiState;

static struct VENTI_TIMER VentiTimer;

void VentiInsp(void)
{
	CurVentiMode->ModeOps->Insp(&ModeInput, &ModeOutput);
	VentiTimer.InspTime += VentiTimer.TickMs;
	VentiTimer.VentiTime += VentiTimer.TickMs;
}

void EntryInsp(void)
{
	VentiTimer.InspTime = 0;
	VentiTimer.VentiTime = 0;
}


void VentiExp(void)
{
	CurVentiMode->ModeOps->Exp(&ModeInput, &ModeOutput);
	VentiTimer.ExpTime += VentiTimer.TickMs;
	VentiTimer.VentiTime += VentiTimer.TickMs;
}

void EntryExp(void)
{
	VentiTimer.ExpTime = 0;
	VentiTimer.VentiTime = 0;
}

void ExitExp(void)
{

}

void ExitInsp(void)
{

}

void HoldBreath(void)
{

}

void EntryHoldBreath(void)
{

}

uint16_t InspTrans2NewState(void)
{
	return CurVentiMode->ModeOps->ExpTrig(&ModeInput);
}

uint16_t ExpTrans2NewState(void)
{
	return CurVentiMode->ModeOps->InspTrig(&ModeInput);
}

uint16_t HoldTrans2NewState(void)
{

}

void VentiStateMachineCreate(void)
{
	VentiState = CreateStateMachine(VENTI_STATES_NUM);

	RegisterState(VentiState, INSPIRATION, 	VentiInsp, 	EntryInsp,			NULL, InspTrans2NewState);
	RegisterState(VentiState, EXPIRATION,	VentiExp, 	EntryExp, 			NULL, ExpTrans2NewState);
	RegisterState(VentiState, HOLD_BREATH, 	HoldBreath, EntryHoldBreath, 	NULL, HoldTrans2NewState);
}
