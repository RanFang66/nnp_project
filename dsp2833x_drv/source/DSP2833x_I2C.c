// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:27 $
//###########################################################################
//
// FILE:	DSP2833x_I2C.c
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
#include "DSP2833x_bsp.h"   // DSP2833x Examples Include File

//
// InitI2C - This function initializes the I2C to a known state.
//
void 
InitI2C(I2c_Dev_Type *I2c)
{
	volatile struct I2C_REGS *pRegs = &I2caRegs;
	Uint16	tmp;

	I2c->RegBase = pRegs;

	pRegs->I2CMDR.all = 0x0000; 	//Reset I2c

    /* Configure I2C clock */
    #if (CPU_FRQ_150MHZ)            // Default - For 150MHz SYSCLKOUT
    //
    // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
    //
	pRegs->I2CPSC.all = 14;
    #endif
    #if (CPU_FRQ_100MHZ)            // For 100 MHz SYSCLKOUT
	//
	// Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
	//
	I2c->RegBase->I2CPSC.all = 9;
    #endif

    switch (I2c->Clock_kHz) {
    case I2C_CLK_400KHZ:
        pRegs->I2CCLKH = 10;
        pRegs->I2CCLKL = 5;
        break;
    case I2C_CLK_200KHZ:
        pRegs->I2CCLKH = 20;
        pRegs->I2CCLKL = 20;
        break;
    case I2C_CLK_100KHZ:
        pRegs->I2CCLKH = 50;
        pRegs->I2CCLKL = 40;
        break;
    case I2C_CLK_80KHZ:
        pRegs->I2CCLKH = 75;
        pRegs->I2CCLKL = 40;
        break;
    default:
        tmp = 10000 / I2c->Clock_kHz - 10;
        pRegs->I2CCLKH = tmp / 2;
        pRegs->I2CCLKL = tmp - tmp / 2;
    }

    /* I2C basic interrup source configuration */
    pRegs->I2CIER.all = I2c->I2cIntSrc;


    pRegs->I2CFFTX.bit.I2CFFEN = I2c->I2cFifoMode & I2C_FIFO_EN;
    pRegs->I2CFFTX.bit.TXFFIENA = I2c->I2cFifoMode & I2C_FIFO_TXINT_EN;
    pRegs->I2CFFRX.bit.RXFFIENA = I2c->I2cFifoMode & I2C_FIFO_RXINT_EN;
    pRegs->I2CFFTX.bit.TXFFIL = I2c->I2cTxFifoLevel;
    pRegs->I2CFFRX.bit.RXFFIL = I2c->I2cRxFifoLevel;
    pRegs->I2CSTR.all = 0xFFFF;
    pRegs->I2CMDR.all = 0x0020;

    DELAY_US(100);

}	

#define I2C_STP_NOT_READY_ERROR		-1
#define I2C_BUS_BUSY_ERROR 			0

int16 I2cWrite(I2c_Dev_Type *I2c, Uint16 Addr, Uint16* Buff, Uint16 Size)
{
	Uint16 i;
	//
	// Wait until the STP bit is cleared from any previous master communication
	// Clearing of this bit by the module is delayed until after the SCD bit is
	// set. If this bit is not checked prior to initiating a new message, the
	// I2C could get confused.
	//
	if (I2c->RegBase->I2CMDR.bit.STP == 1)
	{
		return I2C_STP_NOT_READY_ERROR;
	}

	// Slave Address Set
	I2c->RegBase->I2CSAR = Addr;

	//
	// Check if bus busy
	//
	if (I2c->RegBase->I2CSTR.bit.BB == 1)
	{
		return I2C_BUS_BUSY_ERROR;
	}

	//
	// Setup number of bytes to send MsgBuffer + Address
	//
	I2c->RegBase->I2CCNT = Size;

	//
	// Setup data to send
	//
	for (i = 0; i < Size; i++)
	{
		I2caRegs.I2CDXR = *(Buff+i);
	}

	//
	// Send start as master transmitter
	//
	I2caRegs.I2CMDR.all = 0x6E20;

	return Size;
}

int16 I2cRead(I2c_Dev_Type *I2c, Uint16 Addr, Uint16* Buffer, Uint16 Size)
{
	//
	// Wait until the STP bit is cleared from any previous master communication
	// Clearing of this bit by the module is delayed until after the SCD bit is
	// set. If this bit is not checked prior to initiating a new message, the
	// I2C could get confused.
	//
	if (I2c->RegBase->I2CMDR.bit.STP == 1)
	{
		return I2C_STP_NOT_READY_ERROR;
	}

	// Slave Address Set
	I2c->RegBase->I2CSAR = Addr;
	I2caRegs.I2CCNT = Size;				// Setup how many bytes to expect

	if (I2c->RegBase->I2CSTR.bit.BB == 1)
	{
		return I2C_BUS_BUSY_ERROR;
	}

	I2caRegs.I2CMDR.all = 0x2C20;		// Send restart as master receiver

	return Size;
}

//
// InitI2CGpio - This function initializes GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SDAA operation.
// Only one GPIO pin shoudl be enabled for SCLA operation. 
// Comment out other unwanted lines.
//
void 
InitI2CGpio()
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled disabled by the user.  
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up for GPIO32 (SDAA)
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;	   // Enable pull-up for GPIO33 (SCLA)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)

    //
    // Configure SCI pins using GPIO regs
    // This specifies which of the possible GPIO pins will be I2C functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // Configure GPIO32 to SDAA 
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // Configure GPIO33 to SCLA

    EDIS;
}
	
//
// End of file
//

