/*
 * sys_functions.h
 *
 *  Created on: Jun 11, 2021
 *      Author: ranfang
 */

#ifndef FUNCTION_LOGIC_SYS_FUNCTIONS_H_
#define FUNCTION_LOGIC_SYS_FUNCTIONS_H_

#define SYS_STATE_MACHINE_EN        1
#define VENTI_STATE_MACHINE_EN      1
#define VENTI_MODE_EN               1
#define VENTI_PARA_CALC_EN          1


#if SYS_STATE_MACHINE_EN
#include "sys_state_machine.h"
#endif

#if VENTI_STATE_MACHINE_EN
#include "venti_state_machine.h"
#endif

#if VENTI_MODE_EN
#include "venti_mode.h"
#endif

#if VENTI_PARA_CALC_EN
#include "venti_para_calc.h"
#endif


#endif /* FUNCTION_LOGIC_SYS_FUNCTIONS_H_ */
