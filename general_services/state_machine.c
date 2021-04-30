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

static void _WorkDefault(void)
{

}

struct STATE_MACHINE *
CreateStateMachine(uint16_t Size)
{
	struct STATE_MACHINE *NewMachine = NULL;

	if ((NewMachine = (struct STATE_MACHINE*)malloc(sizeof(struct STATE_MACHINE))) == NULL)
		return NULL;

	if ((NewMachine->StateTbl = (struct STATE**)malloc(Size * sizeof(struct STATE *))) == NULL) {
		free(NewMachine);
		return NULL;
	}

	memset(NewMachine->StateTbl, 0, sizeof(struct STATE*) * Size);
    memset(NewMachine, 0, sizeof(struct STATE_MACHINE));
    NewMachine->StateNumMax = Size;

	return NewMachine;
}

void
RunStateMachine(struct STATE_MACHINE *Machine)
{
	uint16_t NewState;
	while (1){
		Machine->CurrentState->Work();
		if ((NewState = Machine->CurrentState->Trig()) != 0) {
			Machine->CurrentState->Exit();
			Machine->CurrentState = Machine->StateTbl[NewState];
			Machine->CurrentState->Entry();
		}
	}
}

static struct STATE*
CreateState(void)
{
	struct STATE * NewState = NULL;

	if ((NewState = (struct STATE*)malloc(sizeof(struct STATE))) == NULL)
		return NULL;

	return NewState;
}

int16_t
RegisterState(struct STATE_MACHINE *Machine, uint16_t Index, StateWorkFcn Work, StateEntryFcn Entry, StateExitFcn Exit, TriggerFcn Trigger)
{
	struct STATE *NewState = NULL;

	if (Index > Machine->StateNumMax)
		return -EINVALID_INDEX;

	if (Machine->StateTbl[Index-1] != NULL)
		return -EINDEX_EXIST;

	if ((NewState = CreateState()) == NULL)
		return -ECREATE_FAILED;

	NewState->Index = 1u << Index;

	if (Work)
		NewState->Work = Work;
	else
		NewState->Work = _WorkDefault;

	if (Entry)
		NewState->Entry = Entry;
	else
		NewState->Entry = _EntryDefault;

	if (Exit)
		NewState->Exit = Exit;
	else
		NewState->Exit = _ExitDefault;

	NewState->Trig = Trigger;

	if (Machine->CurrentState == NULL)
	{
		Machine->CurrentState = NewState;
	}
	Machine->StateTbl[Index-1] = NewState;
	Machine->StateNum++;


	return Machine->StateNum;
}

