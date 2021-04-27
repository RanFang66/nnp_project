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

#ifndef GENERAL_SERVICES_STATE_MACHINE_H_
#define GENERAL_SERVICES_STATE_MACHINE_H_

typedef struct STATE* (*TriggerFcn)(void);
typedef void (*StateWorkFcn)(void);
typedef void (*StateEntryFcn)(void);
typedef void (*StateExitFcn)(void);

#define STATE_NUM_LIMIT		15

struct STATE {
	uint16_t		State;				// System state

	StateWorkFcn	Work;			// Repeat running work in this state
	StateEntryFcn	Entry;			// Function invoked when entry this state
	StateExitFcn	Exit;			// Function invoked when exit this state
	TriggerFcn		Trig;			// State transfer trigger function
};

struct STATE_MACHINE {
	struct STATE 	*CurrentState;
	struct STATE 	*StateTbl[STATE_NUM_LIMIT];
	uint16_t 		StateNum;
};



extern struct STATE_MACHINE *CreateStateMachine(void);
extern int16_t RegisterState(struct STATE_MACHINE *Machine, StateWorkFcn Work, StateEntryFcn Entry, StateExitFcn Exit, TriggerFcn Trigger);
extern void RunStateMachine(struct STATE_MACHINE *Machine);


#endif /* GENERAL_SERVICES_STATE_MACHINE_H_ */
