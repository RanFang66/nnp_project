/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		sys_state_machine.c
* Author : 			Fang Ran
* Created Date : 	Apr 27, 2021
* Modified Date : 	Apr 27, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/


#include <function_logic/sys_state_machine.h>
#include <public_services/state_machine.h>
#include <stdint.h>
#include <stdlib.h>


struct STATE_MACHINE* SysStateMachine;

/* System State : operating state of the machine
 * Can be one of following value:
 * INITIALIZATION: 	0x0001
 * SELFCHECK:		0x0002
 * STANDBY: 		0x0004
 * RUNNING:			0x0008
 * DEBUG_TEST:		0x0010
 */



void SysInitialize(void)
{

}

void SysSelfcheck(void)
{

}

void SysStandby(void)
{

}

void SysRunning(void)
{

}

void SysDebug(void)
{

}

uint16_t Init2Selfcheck(void)
{

}

uint16_t Selfcheck2Standby(void)
{

}

uint16_t Standby2Running(void)
{

}

uint16_t Standby2Debug(void)
{

}

uint16_t Running2Standby(void)
{

}

uint16_t Debug2Standby(void)
{

}


void EntrySelfcheck(void)
{

}

void EntryStandby(void)
{

}

void EntryRunning(void)
{

}

void EntryDebug(void)
{

}

void SysStateMachineCreate(void)
{
	SysStateMachine = CreateStateMachine(SYS_STATES_NUM);

	RegisterState(SysStateMachine, INITIALIZATION, 	SysInitialize, 	NULL, 			NULL, Init2Selfcheck);
	RegisterState(SysStateMachine, SELFCHECK, 		SysSelfcheck, 	NULL, 			NULL, Selfcheck2Standby);
	RegisterState(SysStateMachine, STANDBY, 		SysStandby, 	EntryStandby, 	NULL, Standby2Running);
	RegisterState(SysStateMachine, RUNNING, 		SysRunning, 	EntryRunning,	NULL, Running2Standby);
	RegisterState(SysStateMachine, DEBUG_TEST, 		SysDebug, 		EntryDebug, 	NULL, Debug2Standby);
}



