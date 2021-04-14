/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		main.c
* Author : 			Fang Ran
* Created Date : 	2021.04.13
* Modified Date : 	2021.04.13
* Description :
* Version : 		V1.0.0 20210413Alpha
* Others :
*
*********************************************************************************************************
*/

#include  <ucos_ii.h>
#include  <cpu_core.h>
#include  <lib_def.h>
#include  <os_cpu.h>

#include "nnp_project.h"


CPU_STK_SIZE  		TaskStartStk[TASK_STK_SIZE];
CPU_STK_SIZE		TaskPendStk[TASK_STK_SIZE];
CPU_STK_SIZE		TaskPostStk[TASK_STK_SIZE];

static  INT8U		OsErr;

static void TaskStart(void  *p_arg);
static void	TaskPing(void *p_arg);
static void TaskPong(void *p_arg);

int main(void)
{
	InitDSP2833x();
	OSInit();
	OSTaskCreateExt(TaskStart,
				   (void    *)0,
				   (CPU_STK *)&TaskStartStk[0],
				   (INT8U    )TASK_START_PRIO,
				   (INT16U   )TASK_START_PRIO,
				   (CPU_STK *)&TaskStartStk[TASK_STK_SIZE - 1u],
				   (INT32U   )TASK_STK_SIZE,
				   (void    *)0,
				   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	OSStart();
	return 0;
}

static void TaskStart(void *p_arg)
{
	ConfigGpio(LED_GPIO, GPIO_IO_OUTPUT, GPIO_PULLUP_EN, GPIO_SYNC_SYSCLK);
	ConfigCpuTimer(&CpuTimer0, 60, 1000);
	StartCpuTimer0();

	OSStatInit();

	OSTaskCreateExt(TaskPing,
	                    (void    *)0,
	                    (CPU_STK *)&TaskPendStk[0],
	                    (INT8U    )TASK_PEND_PRIO,
	                    (INT16U   )TASK_PEND_PRIO,
	                    (CPU_STK *)&TaskPendStk[TASK_STK_SIZE - 1u],
	                    (INT32U   )TASK_STK_SIZE,
	                    (void    *)0,
	                    (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	OSTaskCreateExt(TaskPong,
					(void    *)0,
					(CPU_STK *)&TaskPostStk[0],
					(INT8U    )TASK_POST_PRIO,
					(INT16U   )TASK_POST_PRIO,
					(CPU_STK *)&TaskPostStk[TASK_STK_SIZE - 1u],
					(INT32U   )TASK_STK_SIZE,
					(void    *)0,
					(INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	while (1) {
		OsErr = OSTaskSuspend(OS_PRIO_SELF);
	}
}

static void TaskPing(void *p_arg)
{
	static INT8U PingCnt = 0;

	while (1) {
		PingCnt++;
		LED_ON();
		OsErr = OSTimeDlyHMSM(0, 0, 5, 0);
	}
}

static void TaskPong(void *p_arg)
{
	static INT8U PongCnt = 0;
	while(1) {
		PongCnt++;
		LED_OFF();
		OsErr = OSTimeDlyHMSM(0, 0, 5, 0);
	}
}
