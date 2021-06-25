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

#include <nnp_project.h>
#include "os_cpu.h"

static void InitPIE(void);
static void nnp_SciInit(void);

void InitDSP2833x(void)
{
	InitSysCtrl(DSP28_PLLCR, DSP28_DIVSEL, HISP_PRE_DIV, LOSP_PRE_DIV);
	InitGpio();

	nnp_SciInit();
//	InitWatchDog(WATCHDOG_CLK_DIV, WATCHDOG_INT_SEL);
//	EnableDog(WATCHDOG_CLK_DIV);

	EDIS;
	InitPIE();
	InitCpuTimers();

	EINT;
	ERTM;
}


static void
nnp_SciInit(void)
{
    struct SCI_INIT_TYPE SciInit;

    SciInit.Baudrate = 19200;
    SciInit.DataBits = 8;
    SciInit.StopBits = 1;
    SciInit.Parity = NO_PARITY;
    SciInit.SciEn = SCI_RX_EN | SCI_TX_EN;
    SciInit.SciFifoMode = SCI_FIFO_EN;
    SciInit.SciIntSel = SCI_RX_EN | SCI_TX_EN;
    SciInit.SciRxFifoLevel = 8;
    SciInit.SciTxFifoLevel = 8;

    InitSci(Scia, &SciInit, UI_SCI_PORT);
}

static void
InitPIE(void)
{
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	PieIrqRegister(38, CpuTimer0Isr);
	PieIrqRegister(16, OS_CPU_RTOSINT_Handler);

	EnCpuIntSrc(1);
	EnPieIntSrc(1, 7);
}

