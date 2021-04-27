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


#include <stdint.h>
#include "state_machine.h"
#include "sys_state_machine.h"

struct STATE_MACHINE* SysStateMachine;


void SysStateMachineCreate(void)
{
	SysStateMachine = CreateStateMachine();
//	RegisterState(SysStateMachine, SysInitialize, NULL, SysInitExit, )
}

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
