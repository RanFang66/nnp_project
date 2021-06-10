// TI File $Revision: /main/2 $
// Checkin $Date: March 1, 2007   16:06:07 $
//###########################################################################
//
// FILE:	DSP2833x_Sci.c
//
// TITLE:	DSP2833x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2833x Support Library v2.02.00.00 $
// $Release Date: Fri Feb 12 19:15:21 IST 2021 $
// $Copyright:
// Copyright (C) 2009-2021 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_bsp.h"

//
// InitSci - This function initializes the SCI(s) to a known state.
//
void 
InitSci(SCI_TYPE *Scix, struct SCI_INIT_TYPE *SciInit, enum SCI_GPIO_SEL gpio)
{
    Uint32  brr;

    InitSciGpio(gpio);


    Scix->SCICTL1.bit.SWRESET = 0;

    Scix->SCICCR.bit.STOPBITS = SciInit->StopBits;
    if (SciInit->Parity == ODD_PARITY) {
    	Scix->SCICCR.bit.PARITY = 0;
    	Scix->SCICCR.bit.PARITYENA = 1;
    } else if (SciInit->Parity == EVEN_PARITY){
    	Scix->SCICCR.bit.PARITY = 1;
    	Scix->SCICCR.bit.PARITYENA = 1;
    } else {
    	Scix->SCICCR.bit.PARITY = 0;
    	Scix->SCICCR.bit.PARITYENA = 0;
    }

    Scix->SCICCR.bit.SCICHAR = SciInit->DataBits;
    Scix->SCICCR.bit.LOOPBKENA = 0;
    Scix->SCICCR.bit.ADDRIDLE_MODE = 0;

    Scix->SCICTL1.bit.RXENA = SciInit->SciIntSel & SCI_RX_EN ? 1 : 0;             		// enable RX
    Scix->SCICTL1.bit.TXENA = SciInit->SciIntSel & SCI_TX_EN ? 1 : 0;               	// enable TX
    Scix->SCICTL1.bit.RXERRINTENA = SciInit->SciIntSel & SCI_RX_INT_EN ? 1 : 0;        // enable RX error interrupt
    Scix->SCICTL2.bit.TXINTENA = SciInit->SciIntSel & SCI_TX_INT_EN ? 1: 0;            // disable TX interrupt
    Scix->SCICTL2.bit.RXBKINTENA = SciInit->SciIntSel & SCI_RXBRK_INT_EN ? 1 : 0;      // enable RX break interrupt


    // set baud rate of SCI
    brr = LOSP_CLK_HZ / (SciInit->Baudrate * 8) - 1;
    Scix->SCIHBAUD = (Uint16)(brr >> 16);
    Scix->SCILBAUD = (Uint16)(brr & 0x0000FFFF);


    Scix->SCIFFTX.bit.SCIFFENA = SciInit->SciFifoMode & SCI_FIFO_EN ? 1 : 0;
    Scix->SCIFFTX.bit.TXFFIENA = SciInit->SciFifoMode & SCI_TX_FIFO_INT_EN ? 1 : 0;
    Scix->SCIFFTX.bit.TXFFIL = SciInit->SciTxFifoLevel;

    Scix->SCIFFRX.bit.RXFFIENA = SciInit->SciFifoMode & SCI_RX_FIFO_INT_EN ? 1 : 0;;
    Scix->SCIFFRX.bit.RXFFIL = SciInit->SciRxFifoLevel;

    Scix->SCIFFCT.bit.FFTXDLY = 0;
    Scix->SCIFFCT.bit.ABD = 0;
    Scix->SCIFFCT.bit.CDC = 0;
}	



//
// InitSciGpio - This function initializes GPIO to function as SCI-A, SCI-B, or
// SCI-C
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation. 
// Comment out other unwanted lines.
//
void 
InitSciGpio(enum SCI_GPIO_SEL SciGpio)
{
	switch (SciGpio) {
	case SCIA_RX28_TX29:
		ConfigGpio(28, GPIO_FUNC_MUX1, GPIO_PULLUP_EN, GPIO_ASYNC);
		ConfigGpio(29, GPIO_FUNC_MUX1, GPIO_PULLUP_EN, GPIO_SYNC_SYSCLK);
		break;
	case SCIB_RX19_TX18:
		ConfigGpio(19, GPIO_FUNC_MUX2, GPIO_PULLUP_EN, GPIO_ASYNC);
		ConfigGpio(18, GPIO_FUNC_MUX2, GPIO_PULLUP_EN, GPIO_SYNC_SYSCLK);
		break;
	case SCIC_RX62_TX63:
		ConfigGpio(62, GPIO_FUNC_MUX1, GPIO_PULLUP_EN, GPIO_ASYNC);
		ConfigGpio(63, GPIO_FUNC_MUX1, GPIO_PULLUP_EN, GPIO_SYNC_SYSCLK);
		break;
	default:
		break;
	}
}

//
// InitSciaGpio - This function initializes GPIO pins to function as SCI-A pins
//
void 
InitSciaGpio()
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;  // Enable pull-up for GPIO28 (SCIRXDA)
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	 // Enable pull-up for GPIO29 (SCITXDA)

    //
    // Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.  
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
    
    //
    // Configure SCI-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SCI functional
    // pins.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 to SCIRXDA 
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 to SCITXDA 

    EDIS;
}

#if DSP28_SCIB
//
// InitScibGpio - This function initializes GPIO pins to function as SCI-B pins
//
void 
InitScibGpio()
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins 
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;  //Enable pull-up for GPIO9  (SCITXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0; //Enable pull-up for GPIO14 (SCITXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	 //Enable pull-up for GPIO18 (SCITXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0; //Enable pull-up for GPIO22 (SCITXDB)

    //GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0; //Enable pull-up for GPIO11 (SCIRXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0; //Enable pull-up for GPIO15 (SCIRXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	 //Enable pull-up for GPIO19 (SCIRXDB)
    //GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0; //Enable pull-up for GPIO23 (SCIRXDB)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

    //
    // Configure SCI-B pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SCI functional 
    // pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;  //Configure GPIO9 to SCITXDB 
    //GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2; //Configure GPIO14 to SCITXDB
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;  //Configure GPIO18 to SCITXDB
    //GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3; //Configure GPIO22 to SCITXDB

    //GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;  //Configure GPIO11 for SCIRXDB
    //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;  //Configure GPIO15 for SCIRXDB
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   //Configure GPIO19 for SCIRXDB
    //GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;  //Configure GPIO23 for SCIRXDB

    EDIS;
}
#endif // if DSP28_SCIB 

#if DSP28_SCIC
//
// InitScicGpio - This function initializes GPIO pins to function as SCI-C pins
//
void 
InitScicGpio()
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;  // Enable pull-up for GPIO62 (SCIRXDC)
    GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	 // Enable pull-up for GPIO63 (SCITXDC)

    //
    // Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.  
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

    //
    // Configure SCI-C pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SCI functional 
    // pins.
    //
    GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 to SCIRXDC
    GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 to SCITXDC

    EDIS;
}
#endif // if DSP28_SCIC 


int16 SciReadPoll(SCI_TYPE *Scix, Uint16 *Buff, Uint16 Num)
{
	int len;
	int i = 0;

	if (Scix->SCIRXST.bit.RXERROR) {
		Scix->SCIFFRX.bit.RXFFOVRCLR = 1;
		Scix->SCIFFRX.bit.RXFFINTCLR = 1;

		Scix->SCICTL1.bit.SWRESET = 0;
		Scix->SCIFFRX.bit.RXFIFORESET = 1;
		Scix->SCIFFTX.bit.TXFIFOXRESET = 1;

		Scix->SCICTL1.bit.SWRESET = 1;
		return -SCI_ERROR;
	} else if (Scix->SCIFFRX.bit.RXFFST > 0) {
		len = Scix->SCIFFRX.bit.RXFFST;
		while (len > i) {
			*Buff = Scix->SCIRXBUF.bit.RXDT;
			Buff++;
			i++;
		}
		return len;
	} else {
		return -SCI_NO_DATA;
	}
	
}


int16 SciWriteBlock(SCI_TYPE *Scix, const Uint16 *Buff, Uint16 Num)
{
	int len = 0;

	if (Num > SCI_WRITE_NUM_MAX)
		Num = SCI_WRITE_NUM_MAX;


	while (len < Num) {
		while (Scix->SCIFFTX.bit.TXFFIL - Scix->SCIFFTX.bit.TXFFST > 0) {
			Scix->SCITXBUF = *(Buff+len);
			len++;
		}
	}
	return len;
}


//
// End of file
//

