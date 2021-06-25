/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		uni_test.c
* Author : 			Fang Ran
* Created Date : 	Jun 25, 2021
* Modified Date : 	Jun 25, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/
#include "nnp_project.h"

#define SCI_TEST_MODE 	TEST_POLL_RECV

void Test_InitDsp28335(void)
{
	InitSysCtrl(DSP28_PLLCR, DSP28_DIVSEL, HISP_PRE_DIV, LOSP_PRE_DIV);
	InitGpio();

	Test_SciInit(SCI_TEST_MODE, 9600, SCIA_RX28_TX29);

	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();

	EINT;
	ERTM;
}
static void Delay(void)
{
	uint32_t i = 100000;
	while (i > 0){
		i--;
	}
}
void Test_RunTest(void)
{
	while (1) {
//		if (Test_SciRecv(SCI_TEST_MODE, 10) > 0) {
//
//		}
		Delay();
		if (Test_SciSend(SCI_TEST_MODE, 4) > 0) {

		}
	}
}
