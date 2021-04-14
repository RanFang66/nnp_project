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

#define LED_GPIO		35

#define LED_OFF()		do { \
							EALLOW; \
							GpioDataRegs.GPBSET.bit.GPIO35 = 1; \
							EDIS; \
						}while (0);

#define LED_ON()		do { \
							EALLOW; \
							GpioDataRegs.GPBCLEAR.bit.GPIO35 = 1; \
							EDIS; \
						}while (0);

#define LED_TOGGLE()	do { \
							EALLOW; \
							GpioDataRegs.GPBTOGGLE.bit.GPIO35= 1; \
							EDIS; \
						}while (0);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* NNP_HARDWARE_H_ */
