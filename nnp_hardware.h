/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		nnp_hardware.h
* Author : 			Fang Ran
* Created Date : 	Apr 13, 2021
* Modified Date : 	Apr 13, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef NNP_HARDWARE_H_
#define NNP_HARDWARE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LED_LIGHT	GpioDataRegs.GPBSET.bit.GPIO37 = 1
#define LED_OFF		GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1
#define LED_TOGGLE	GpioDataRegs.GPBTOGGLE.bit.GPIO37 = 1

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* NNP_HARDWARE_H_ */
