/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		state_machine.h
* Author : 			Fang Ran
* Created Date : 	Apr 27, 2021
* Modified Date : 	Apr 27, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef GENERAL_MODULES_STATE_MACHINE_H_
#define GENERAL_MODULES_STATE_MACHINE_H_

#include <stdint.h>

typedef uint16_t (*TriggerFcn)(void);
typedef void (*StateWorkFcn)(void);
typedef void (*StateEntryFcn)(void);
typedef void (*StateExitFcn)(void);

#define STATE_NUM_LIMIT		15

#define EINVALID_INDEX 		1
#define EINDEX_EXIST		2
#define ECREATE_FAILED		3

struct STATE {
	uint16_t		Index;				// System state

	StateWorkFcn	Work;			// Repeat running work in this state
	StateEntryFcn	Entry;			// Function invoked when entry this state
	StateExitFcn	Exit;			// Function invoked when exit this state
	TriggerFcn		Trig;			// State transfer trigger function
};

struct STATE_MACHINE {
	struct STATE 	*CurrentState;
	struct STATE 	**StateTbl;
	uint16_t 		StateNum;
	uint16_t        StateNumMax;
};

extern struct STATE_MACHINE *CreateStateMachine(uint16_t Size);
extern int16_t RegisterState(struct STATE_MACHINE *Machine, uint16_t Index, StateWorkFcn Work, StateEntryFcn Entry, StateExitFcn Exit, TriggerFcn Trigger);
extern void RunStateMachine(struct STATE_MACHINE *Machine);


#endif /* GENERAL_MODULES_STATE_MACHINE_H_ */
