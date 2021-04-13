// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:25 $
//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
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

//
// InitGpio - This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
//
void 
InitGpio(void)
{
    EALLOW;

    //
    // Each GPIO pin can be: 
    // a) a GPIO input/output
    // b) peripheral function 1
    // c) peripheral function 2
    // d) peripheral function 3
    // By default, all are GPIO Inputs 
    //
    GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
    GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
    GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO39
    GpioCtrlRegs.GPBMUX2.all = 0x0000;     // GPIO functionality GPIO48-GPIO63
    GpioCtrlRegs.GPCMUX1.all = 0x0000;     // GPIO functionality GPIO64-GPIO79
    GpioCtrlRegs.GPCMUX2.all = 0x0000;     // GPIO functionality GPIO80-GPIO95

    GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are inputs
    GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO63 are inputs   
    GpioCtrlRegs.GPCDIR.all = 0x0000;      // GPI064-GPIO95 are inputs

    //
    // Each input can have different qualification
    // a) input synchronized to SYSCLKOUT
    // b) input qualified by a sampling window
    // c) input sent asynchronously (valid for peripheral inputs only)
    //
    GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT 
    GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
    GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO39 Synch to SYSCLKOUT 
    GpioCtrlRegs.GPBQSEL2.all = 0x0000;    // GPIO48-GPIO63 Synch to SYSCLKOUT 

    //
    // Pull-ups can be enabled or disabled
    //
    GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
    GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO63
    GpioCtrlRegs.GPCPUD.all = 0x0000;      // Pullup's enabled GPIO64-GPIO79
    //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
    //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO34
    //GpioCtrlRegs.GPCPUD.all = 0xFFFF;    // Pullup's disabled GPIO64-GPIO79

    EDIS;
}	

#define GPIO_QSEL_SUPPORT_MAX			64
#define GPIO_MUX_REG(GROUP, NUM)		&GpioCtrlRegs.GP##GROUP##MUX##NUM.all
#define	GPIO_DIR_REG(GROUP) 			&GpioCtrlRegs.GP##GROUP##DIR.all
#define GPIO_QSEL_REG(GROUP, NUM)		&GpioCtrlRegs.GP##GROUP##QSEL##NUM.all
#define GPIO_PUD_REG(GROUP)				&GpioCtrlRegs.GP##GROUP##PUD.all

/*
*********************************************************************************************************
* @FuncName		: 	ConfigGpio
*
* @Description	: 	Configure a GPIO port
*
* @Arguments	: 	GpioNum		is the GPIO port number you want to configure.
* 				  	GpioMode	is the desired GPIO mode including :
* 				  		GPIO_NOUSE
* 				  		GPIO_IO_INPUT
* 				  		GPIO_IO_OUTPUT
* 				  		GPIO_FUNC_MUX1
* 				  		GPIO_FUNC_MUX2
* 				  		GPIO_FUNC_MUX3
* 				  	PullUpEn	is an boolean value to decide whether the GPIO pull up should be enable.
* 				  	QSel:		is the GPIO input qualification option which is one of the following value:
* 				  		GPIO_SYNC_SYSCLK
* 				  		GPIO_3_SAMPLES
* 				  		GPIO_6_SAMPLES
* 				  		GPIO_ASYNC
*
* @Returns		:	GPIO_NO_ERR			if the GPIO port is configured successfully.
* 					GPIO_INVALID_NUM	if the GPIO port number you input is invalid.
* 					GPIO_INVALID_MODE   if the GPIO mode you input is invalid.
* 					GPIO_INVALID_QUA	if the GPIO qualification option you input is invalid.
*
* @Notes		:
*********************************************************************************************************
*/
Uint16
ConfigGpio(Uint16 GpioNum, Gpio_Mode_Type GpioMode, Uint16 PullUpEn, Gpio_QSel_Type QSel)
{
	volatile Uint32 *GpioMux;   	// pointer to gpio multiplexing register
	volatile Uint32 *GpioDir;		// pointer to gpio direction register
	volatile Uint32 *GpioQSel;		// pointer to gpio qualification select register
	volatile Uint32 *GpioPud;		// pointer to gpio pull up control register

	Uint16 GpioGrp = GpioNum / 16;
	Uint16 shift1 = GpioNum % 32;
	Uint16 shift2 = GpioNum % 16 * 2;
	
	switch (GpioGrp) {
	case 0:
		GpioMux = GPIO_MUX_REG(A, 1);
		GpioDir = GPIO_DIR_REG(A);
		GpioQSel = GPIO_QSEL_REG(A, 1);
		GpioPud = GPIO_PUD_REG(A);
		break;

	case 1:
		GpioMux = GPIO_MUX_REG(A, 2);
		GpioDir = GPIO_DIR_REG(A);
		GpioQSel = GPIO_QSEL_REG(A, 2);
		GpioPud = GPIO_PUD_REG(A);
		break;

	case 2:
		GpioMux = GPIO_MUX_REG(B, 1);
		GpioDir = GPIO_DIR_REG(B);
		GpioQSel = GPIO_QSEL_REG(B, 1);
		GpioPud = GPIO_PUD_REG(B);
		break;

	case 3:
		GpioMux = GPIO_MUX_REG(B, 2);
		GpioDir = GPIO_DIR_REG(B);
		GpioQSel = GPIO_QSEL_REG(B, 2);
		GpioPud = GPIO_PUD_REG(B);
		break;

	case 4:
		GpioMux = GPIO_MUX_REG(C, 1);
		GpioDir = GPIO_DIR_REG(C);
		GpioPud = GPIO_PUD_REG(C);
		break;

	case 5:
		GpioMux = GPIO_MUX_REG(C, 2);
		GpioDir = GPIO_DIR_REG(C);
		GpioPud = GPIO_PUD_REG(C);
		break;

	default:
		GpioMux = 0;
		GpioDir = 0;
		GpioQSel = 0;
		GpioPud = 0;
		return GPIO_INVALID_NUM;
		break;
	}


	switch (GpioMode) {
	case GPIO_NOUSE:
		*GpioMux &= ~((Uint32)3 << shift2);
		*GpioDir &= ~((Uint32)1 << shift1);
		break;
	case GPIO_IO_INPUT:
		*GpioMux &= ~((Uint32)3 << shift2);
		*GpioDir &= ~((Uint32)1 << shift1);
		break;
	case GPIO_IO_OUTPUT:
		*GpioMux &= ~((Uint32)3 << shift2);
		*GpioDir |= ((Uint32)1 << shift1);
		break;
	case GPIO_FUNC_MUX1:
		*GpioMux &= ~((Uint32)1 << (shift2+1));
		*GpioMux |= ((Uint32)1 << shift2);
		break;
	case GPIO_FUNC_MUX2:
		*GpioMux |= ((Uint32)1 << (shift2+1));
		*GpioMux &= ~((Uint32)1 << shift2);
		break;
	case GPIO_FUNC_MUX3:
		*GpioMux |= ((Uint32)3 << shift2);
		break;
	default:
		return GPIO_INVALID_MODE;
		break;
	}


	if (GpioNum < GPIO_QSEL_SUPPORT_MAX) {
		if (GPIO_SYNC_SYSCLK == QSel) {
			*GpioQSel &= ~((Uint32)3 << shift2);
		} else if (GPIO_3_SAMPLES == QSel) {
			*GpioQSel &= ~((Uint32)1 << (shift2+1));
			*GpioQSel |= ((Uint32)1 << shift2);
		} else if (GPIO_6_SAMPLES == QSel) {
			*GpioQSel &= ~((Uint32)1 << shift2);
			*GpioQSel |= ((Uint32)1 << (shift2+1));
		} else if (GPIO_ASYNC) {
			*GpioQSel |= ((Uint32)1 << shift2);
		} else {
			return GPIO_INVALID_QUA;
		}
	}

	if (PullUpEn) {
		*GpioPud &= ~((Uint32)1 << shift1);
	} else {
		*GpioPud |= (Uint32)1 << shift1;
	}

	return GPIO_NO_ERR;
}



//
// End of file
//

