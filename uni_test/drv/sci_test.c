/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		sci_test.c
* Author : 			Fang Ran
* Created Date : 	Jun 25, 2021
* Modified Date : 	Jun 25, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#include <stdint.h>
#include <nnp_project.h>

#define SCI_TEST_BUFF_SZIE 	16
uint16_t RecvBuff[SCI_TEST_BUFF_SZIE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t SendBuff[SCI_TEST_BUFF_SZIE] = {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,};
char *Msg = "\r\n\n\nHello World!\0";
int16_t RecvCnt = 0;
int16_t SendCnt = 0;


//
// scia_echoback_init - Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F,
// default, 1 STOP bit, no parity
//
void
scia_echoback_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //

    // 1 stop bit,  No loopback, No parity,8 char bits,
    // async mode, idle-line protocol
    //
    SciaRegs.SCICCR.all =0x0007;

    //
    // enable TX, RX, internal SCICLK,
    // Disable RX ERR, SLEEP, TXWAKE
    //
    SciaRegs.SCICTL1.all =0x0003;
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =0;
    SciaRegs.SCICTL2.bit.RXBKINTENA =0;
#if (CPU_FRQ_150MHZ)
    SciaRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
    SciaRegs.SCILBAUD    =0x00E7;
#endif
#if (CPU_FRQ_100MHZ)
    SciaRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
    SciaRegs.SCILBAUD    =0x0044;
#endif
    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}
//
// scia_fifo_init - Initialize the SCI FIFO
//
void
scia_fifo_init()
{
    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x204f;
    SciaRegs.SCIFFCT.all=0x0;
}


void Test_SciInit(uint16_t Mode, uint32_t Baudrate, enum SCI_GPIO_SEL Gpio)
{
//    struct SCI_INIT_TYPE SciInit;
//
//	SciInit.Baudrate = Baudrate;
//	SciInit.DataBits = 8;
//	SciInit.StopBits = 1;
//	SciInit.Parity = NO_PARITY;
//
//	InitSciGpio(Gpio);
//    switch (Mode) {
//    case TEST_POLL_RECV:
//		SciInit.SciFifoMode = SCI_FIFO_EN;
//		SciInit.SciEn = SCI_RX_EN | SCI_TX_EN;
//		SciInit.SciIntSel = 0;
//		SciInit.SciRxFifoLevel = 15;
//		SciInit.SciTxFifoLevel = 0;
//		break;
//    case TEST_INT_RECV:
//    	break;
//    default:
//    	break;
//    }
//    InitSci(Scia, &SciInit, Gpio);
	InitSciaGpio();
	scia_fifo_init();
	scia_echoback_init();
}

int16_t Test_SciRecv(uint16_t Mode, uint16_t Num)
{
//	int16_t Ret = 0;
	switch (Mode) {
	case TEST_POLL_RECV:
		//Ret = SciReadBlock(Scia, RecvBuff, Num);
		RecvBuff[RecvCnt] = SciRecvByte(Scia);
		RecvCnt++;
		break;
	case TEST_INT_RECV:
		break;
	default:
		break;
	}
	if (RecvCnt > 16) {
		RecvCnt = 0;
	}
	return RecvCnt;
}

int16_t Test_SciSend(uint16_t Mode, uint16_t Num)
{
	switch (Mode) {
	case TEST_POLL_RECV:
//		SendCnt = SciWriteBlock(Scia,SendBuff, Num);
//		SciSendByte(Scia, SendBuff[SendCnt]);
		SciSendMsg(Scia, Msg);
		SendCnt++;
		break;
	case TEST_INT_RECV:
		break;
	default:
		break;
	}
	if (SendCnt > 10) {
		SendCnt = 0;
	}
	return SendCnt;
}



