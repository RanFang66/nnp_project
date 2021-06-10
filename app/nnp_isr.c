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
#include <app/nnp_project.h>

interrupt void CpuTimer0Isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

	OSIntEnter();
	OSTimeTick();
	OSIntExit();
}


interrupt void SciaReadIsr(void)
{
	int len;
	int i;

	if (SciaRegs.SCIRXST.bit.RXERROR) {
		SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;

		SciaRegs.SCICTL1.bit.SWRESET = 0;
		SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
		SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;

		SciaRegs.SCICTL1.bit.SWRESET = 1;
	} else if (SciaRegs.SCIFFRX.bit.RXFFST > 0) {
		len = SciaRegs.SCIFFRX.bit.RXFFST;
		i = 0;
		while (len > i) {
//			*Buff = SciaRegs.SCIRXBUF.bit.RXDT;
//			Buff++;
			i++;
		}
	} else {

	}
}
