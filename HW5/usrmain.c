/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the exe_helloworld component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/


/* -------------------------------------------------------------------------
	Include
 ------------------------------------------------------------------------- */
#include "../ubiconfig.h"

// standard c library include
#include <stdio.h>
#include<stdlib.h>
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"
#include "itf_ubinos/itf/bsp_intr.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_switch/itf/lib_switch.h"
#include "lib_sensor/itf/lib_sensor.h"
#include "lib_sensorcalib/itf/lib_sensorcalib.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"
#include "../../lib_new/itf/lib_new.h"
// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
sem_pt _g_sem;
static int count = 0;

#define TIMER_STOP 0
#define TIMER_RUN 1

static char g_state = TIMER_STOP;
/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void timer_isr(void);
static void print_lcd(void *arg);
static void switch_isr(void);
static void switch_isr2(void);

/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;
	glcd_init();

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_timer_intr_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = sem_create(&_g_sem);
	if(0!=r){
		glcd_printf("fail at sem_create\n");
	}

	r = task_create(NULL, print_lcd, NULL, task_getmiddlepriority(), 256, "print_lcd");
	if(0!=r){
		glcd_printf("fail at task_create\n");
	}

	//enable timer clock
	PMC-> PMC_PCER0 = 1 << ID_TC3;

	//TImer configuration
	TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS; // Counter Clock Disable Command
	TC1->TC_CHANNEL[0].TC_IDR = 0xFFFFFFFF; // Timer Interrupt Disable Command

	//Channel Mode (TLCK1 Select(0) and RC Compare Trigger Enable
	TC1->TC_CHANNEL[0].TC_CMR = (TC_CMR_TCCLKS_TIMER_CLOCK5 | TC_CMR_CPCTRG);
	TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN; // Counter Clock Enable Command
	TC1->TC_CHANNEL[0].TC_IER = TC_IER_CPCS; // RC Compare Interrupt Enable

	//interrupt handler
	intr_connectisr(TC3_IRQn, timer_isr, 0x40, INTR_OPT__LEVEL);

	//enable interrupt
	intr_enable(TC3_IRQn); //NVIC Interrupt Enable Command Register

	//Timer interrupt Period Configuration
	TC1->TC_CHANNEL[0].TC_RC = 32768; // set Timer for about is interval

	//Start Timer

	ubik_comp_start();

	return 0;
}

static void timer_isr(void){
	unsigned int reg;

	sem_give(_g_sem);
	count++;

	reg = TC1->TC_CHANNEL[0].TC_SR;
	printf("HW_TIMER [TC:%d] \r\n", reg);

}

static void print_lcd(void *arg){
	for(;;){
		switch_init(switch_isr, switch_isr2);
		sem_take(_g_sem);
		glcdGotoChar(0,0);

		glcd_printf("HW_TIMER : %3d", count);
		task_sleep(100);
	}
}
static void switch_isr(void){
	int timer_state= 0;
	if(timer_state == 0){
	TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG; // Software trigger is performed
	timer_state = 1;
	}
	if(g_state == TIMER_STOP){
		TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;
		TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG;
			g_state = TIMER_RUN;
		}
		else if(g_state == TIMER_RUN){
		TC1->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKDIS;
			g_state = TIMER_STOP;
		}
}

static void switch_isr2(void){
	count = 0;
}
