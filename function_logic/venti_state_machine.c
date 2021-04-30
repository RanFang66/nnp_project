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

#include <function_logic/venti_state_machine.h>
#include <stdint.h>
#include <stdlib.h>

#include "state_machine.h"

struct STATE_MACHINE* VentiState;

void VentiInsp(void)
{

}

void EntryInsp(void)
{

}


void VentiExp(void)
{

}

void EntryExp(void)
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

}

uint16_t ExpTrans2NewState(void)
{

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
