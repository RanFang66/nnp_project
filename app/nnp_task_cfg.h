/*
*********************************************************************************************************
*                   Copyright @2021 BeiJing AenoMed Co.,Ltd. All rights reserved.
*
* File Name : 		nnp_task_cfg.h
* Author : 			Fang Ran
* Created Date : 	Apr 14, 2021
* Modified Date : 	Apr 14, 2021
* Description : 
* Version : 		V1.0.0 20210412Alpha
* Others :
*
*********************************************************************************************************
*/

#ifndef APP_NNP_TASK_CFG_H_
#define APP_NNP_TASK_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  TASK_START_PRIO                      2u
#define  TASK_PEND_PRIO                       3u
#define  TASK_POST_PRIO                       4u

#define  TASK_SYS_CTRL_PRIO                         3u
#define  TASK_CTRL_EXECUTE_PRIO                     4u
#define  TASK_SAMPLE_PRIO                           5u
#define  TASK_ALARM_CHECK_PRIO                      6u
#define  TASK_PARA_MONITOR_PRIO                     7u
#define  TASK_UI_COMM_PRIO                          8u


/*
*********************************************************************************************************
*                                                TASK IDs
*********************************************************************************************************
*/

#define  TASK_START_ID                        0u
#define  TASK_PEND_ID                         1u
#define  TASK_POST_ID                         2u


#define  TASK_SYS_CTRL_ID                         1u
#define  TASK_CTRL_EXECUTE_ID                      2u
#define  TASK_SAMPLE_ID                           3u
#define  TASK_ALARM_CHECK_ID                      4u
#define  TASK_PARA_MONITOR_ID                     5u
#define  TASK_UI_COMM_ID                          6u

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  TASK_STK_SIZE                          128u

#define  START_TASK_STK_SIZE                    128u
#define  SYS_CTRL_STK_SIZE                      128u
#define  CTRL_EXECUTE_STK_SIZE                  128u
#define  SAMPLE_STK_SIZE                        128u
#define  ALARM_CHECK_STK_SIZE                   128u
#define  PARA_MONITOR_STK_SIZE                  128u
#define  UI_COMM_STK_SIZE                       128u



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* APP_NNP_TASK_CFG_H_ */
