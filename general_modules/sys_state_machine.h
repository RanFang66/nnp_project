/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		sys_state_machine.h
* Author : 			Fang Ran
* Created Date : 	Apr 27, 2021
* Modified Date : 	Apr 27, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef GENERAL_MODULES_SYS_STATE_MACHINE_H_
#define GENERAL_MODULES_SYS_STATE_MACHINE_H_


#define INITIALIZATION	0x0001
#define SELFCHECK		0x0002
#define STANDBY 		0x0004
#define RUNNING			0x0008
#define DEBUG_TEST		0x0010

#define INSPIRATION		0x0001
#define EXPIRATION		0x0002
#define	HOLD_BREATH		0x0004


#endif /* GENERAL_MODULES_SYS_STATE_MACHINE_H_ */
