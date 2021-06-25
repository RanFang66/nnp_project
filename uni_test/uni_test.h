/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		uni_test.h
* Author : 			Fang Ran
* Created Date : 	Jun 25, 2021
* Modified Date : 	Jun 25, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef UNI_TEST_UNI_TEST_H_
#define UNI_TEST_UNI_TEST_H_
#include <stdint.h>


#define UNIT_TEST_EN		1
#define SCI_TEST_EN			1


#if SCI_TEST_EN

#define TEST_POLL_RECV		1
#define TEST_INT_RECV		2
void Test_SciInit(uint16_t Mode, uint32_t Baudrate, enum SCI_GPIO_SEL Gpio);
int16_t Test_SciRecv(uint16_t Mode, uint16_t Num);
int16_t Test_SciSend(uint16_t Mode, uint16_t Num);

#endif


#if UNIT_TEST_EN

void Test_InitDsp28335(void);
void Test_RunTest(void);

#endif


#endif /* UNI_TEST_UNI_TEST_H_ */
