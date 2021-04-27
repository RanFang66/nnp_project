/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		state_machine.c
* Author : 			Fang Ran
* Created Date : 	Apr 27, 2021
* Modified Date : 	Apr 27, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "state_machine.h"

static void _EntryDefault(void)
{

}

static void _ExitDefault(void)
{

}

static void _DoDefault(void)
{

}

struct STATE_MACHINE *
CreateStateMachine(void)
{
	struct STATE_MACHINE *NewMachine = NULL;

	if ((NewMachine = (struct STATE_MACHINE*)malloc(sizeof(struct STATE_MACHINE))) == NULL)
		return NULL;
    memset(NewMachine, 0, sizeof(struct STATE_MACHINE));

	return NewMachine;
}

void
RunStateMachine(struct STATE_MACHINE *Machine)
{
	uint16_t i;
	struct STATE *NewState;
	while (1){
		Machine->CurrentState->Work();
		if ((NewState = Machine->CurrentState->Trig()) != 0) {
			Machine->CurrentState->Exit();
			Machine->CurrentState = NewState;
			Machine->CurrentState->Entry();
		}
	}
}

struct STATE*
CreateState(void)
{
	struct STATE * NewState = NULL;

	if ((NewState = (struct STATE*)malloc(sizeof(struct STATE))) == NULL)
		return NULL;

	return NewState;
}

int16_t
RegisterState(struct STATE_MACHINE *Machine, StateWorkFcn Work, StateEntryFcn Entry, StateExitFcn Exit, TriggerFcn Trigger)
{
	struct STATE *NewState = NULL;
	if (Machine->StateNum >= STATE_NUM_LIMIT)
		return -2;

	if ((NewState = CreateState()) == NULL)
		return -1;

	if (Work)
		NewState->Work = Work;
	else
		NewState->Work = _DoDefault;

	NewState->Entry = Entry;
	NewState->Exit = Exit;
	NewState->Trig = Trigger;
	NewState->State = 1 << Machine->StateNum;

	if (Machine->StateNum == 0)
	{
		Machine->CurrentState = NewState;
	}
	Machine->StateNum++;
	Machine->StateTbl[Machine->StateNum-1] = NewState;

	return Machine->StateNum;
}

