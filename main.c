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
#include "nnp_project.h"
#include <ucos_ii.h>
#include <cpu_core.h>
#include <lib_def.h>
#include <os_cpu.h>

CPU_STK_SIZE  		TaskStartStk[START_TASK_STK_SIZE];
CPU_STK_SIZE        TaskSysCtrlStk[SYS_CTRL_STK_SIZE];
CPU_STK_SIZE        TaskCtrlExecuteStk[CTRL_EXECUTE_STK_SIZE];
CPU_STK_SIZE        TaskSampleStk[SAMPLE_STK_SIZE];
CPU_STK_SIZE        TaskAlarmCheckStk[ALARM_CHECK_STK_SIZE];
CPU_STK_SIZE        TaskParaMonitorStk[PARA_MONITOR_STK_SIZE];
CPU_STK_SIZE        TaskUiCommStk[UI_COMM_STK_SIZE];

uint16_t    CurTaskId = 0;

static void TaskStart(void  *p_arg);
static void TaskSysCtrl(void  *p_arg);
static void TaskCtrlExecute(void  *p_arg);
static void TaskSample(void  *p_arg);
static void TaskAlarmCheck(void  *p_arg);
static void TaskParaMonitor(void  *p_arg);
static void TaskUiComm(void *p_arg);

int main(void)
{
#if UNIT_TEST_EN == 0
	// Initialize Board
    InitDSP2833x();

    // Initialize uCos
	OSInit();

	// Create start task
	OSTaskCreateExt(TaskStart,
				   (void    *)0,
				   (CPU_STK *)&TaskStartStk[0],
				   (INT8U    )TASK_START_PRIO,
				   (INT16U   )TASK_START_PRIO,
				   (CPU_STK *)&TaskStartStk[TASK_STK_SIZE - 1u],
				   (INT32U   )START_TASK_STK_SIZE,
				   (void    *)0,
				   (INT16U   )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	// Run uCos
	OSStart();
#else
	Test_InitDsp28335();
	Test_RunTest();
#endif
	return 0;
}

static void TaskStart(void *p_arg)
{
	ConfigGpio(LED_GPIO, GPIO_IO_OUTPUT, GPIO_PULLUP_EN, GPIO_SYNC_SYSCLK);
	ConfigCpuTimer(&CpuTimer0, 60, 1000);
	StartCpuTimer0();

	OSStatInit();

	// Task 1: system control
	OSTaskCreateExt(TaskSysCtrl,
	                (void      *)0,
	                (CPU_STK   *)&TaskSysCtrlStk[0],
	                (INT8U      )TASK_SYS_CTRL_PRIO,
	                (INT8U      )TASK_SYS_CTRL_ID,
	                (CPU_STK   *)&TaskSysCtrlStk[SYS_CTRL_STK_SIZE - 1u],
	                (INT32U     )SYS_CTRL_STK_SIZE,
	                (void      *)0,
	                (INT16U)    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	// Task 2: Control execute
	OSTaskCreateExt(TaskCtrlExecute,
                    (void      *)0,
                    (CPU_STK   *)&TaskCtrlExecuteStk[0],
                    (INT8U      )TASK_CTRL_EXECUTE_PRIO,
                    (INT8U      )TASK_CTRL_EXECUTE_ID,
                    (CPU_STK   *)&TaskCtrlExecuteStk[CTRL_EXECUTE_STK_SIZE - 1u],
                    (INT32U     )CTRL_EXECUTE_STK_SIZE,
                    (void      *)0,
                    (INT16U)    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	// Task 3: Data sample
	OSTaskCreateExt(TaskSample,
                    (void      *)0,
                    (CPU_STK   *)&TaskSampleStk[0],
                    (INT8U      )TASK_SAMPLE_PRIO,
                    (INT8U      )TASK_SAMPLE_ID,
                    (CPU_STK   *)&TaskSampleStk[SAMPLE_STK_SIZE - 1u],
                    (INT32U     )SAMPLE_STK_SIZE,
                    (void      *)0,
                    (INT16U)    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	// Task 4: Alarm check
	OSTaskCreateExt(TaskAlarmCheck,
                    (void      *)0,
                    (CPU_STK   *)&TaskAlarmCheckStk[0],
                    (INT8U      )TASK_ALARM_CHECK_PRIO,
                    (INT8U      )TASK_ALARM_CHECK_ID,
                    (CPU_STK   *)&TaskAlarmCheckStk[ALARM_CHECK_STK_SIZE - 1u],
                    (INT32U     )ALARM_CHECK_STK_SIZE,
                    (void      *)0,
                    (INT16U)    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	// Task 5: Parameter monitor
	OSTaskCreateExt(TaskParaMonitor,
                    (void      *)0,
                    (CPU_STK   *)&TaskParaMonitorStk[0],
                    (INT8U      )TASK_PARA_MONITOR_PRIO,
                    (INT8U      )TASK_PARA_MONITOR_ID,
                    (CPU_STK   *)&TaskParaMonitorStk[PARA_MONITOR_STK_SIZE - 1u],
                    (INT32U     )PARA_MONITOR_STK_SIZE,
                    (void      *)0,
                    (INT16U)    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	// Task 6: UI communication
    OSTaskCreateExt(TaskUiComm,
                    (void      *)0,
                    (CPU_STK   *)&TaskUiCommStk[0],
                    (INT8U      )TASK_UI_COMM_PRIO,
                    (INT8U      )TASK_UI_COMM_ID,
                    (CPU_STK   *)&TaskUiCommStk[UI_COMM_STK_SIZE - 1u],
                    (INT32U     )UI_COMM_STK_SIZE,
                    (void      *)0,
                    (INT16U)    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	while (1) {
		OSTaskSuspend(OS_PRIO_SELF);
	}
}

static void TaskSysCtrl(void  *p_arg)
{
    while (1) {
        CurTaskId = 1;
        OSTimeDly(3);
    }
}

static void TaskCtrlExecute(void  *p_arg)
{
    while (1) {
        CurTaskId = 2;
        OSTimeDly(3);
    }
}

static void TaskSample(void  *p_arg)
{
    while (1) {
        CurTaskId = 3;
        OSTimeDly(3);
    }
}

static void TaskAlarmCheck(void  *p_arg)
{
    while (1) {
        CurTaskId = 4;
        OSTimeDly(3);
    }
}

static void TaskParaMonitor(void  *p_arg)
{
    while (1) {
        CurTaskId = 5;
        OSTimeDly(3);
    }
}

static void TaskUiComm(void *p_arg)
{

    while (1) {
        CurTaskId = 6;

        OSTimeDly(10);
    }
}
