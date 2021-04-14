/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		nnp_init.c
* Author : 			Fang Ran
* Created Date : 	Apr 13, 2021
* Modified Date : 	Apr 13, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#include "os_cpu.h"
#include "nnp_project.h"

static void InitPIE(void);

void InitDSP2833x(void)
{
	InitSysCtrl(DSP28_PLLCR, DSP28_DIVSEL, HISP_PRE_DIV, LOSP_PRE_DIV);
	InitGpio();
	InitWatchDog(WATCHDOG_CLK_DIV, 0);


	EDIS;
	InitPIE();
	InitCpuTimers();

	EINT;
	ERTM;
}

static void InitPIE(void)
{
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	EALLOW;
	PieVectTable.TINT0 = &CpuTimer0Isr;
	PieVectTable.RTOSINT = &OS_CPU_RTOSINT_Handler;
	EDIS;

	IER |= M_INT1;
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
}

