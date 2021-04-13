/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		nnp_isr.c
* Author : 			Fang Ran
* Created Date : 	Apr 13, 2021
* Modified Date : 	Apr 13, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include "nnp_project.h"

interrupt void CpuTimer0Isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	OSIntEnter();
	OSTimeTick();
	OSIntExit();
}
