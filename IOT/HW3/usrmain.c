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
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_switch/itf/lib_switch.h"
		//#include "lib_sensor/itf/lib_sensor.h"
		//#include "lib_sensorcalib/itf/lib_sensorcalib.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"

// custom library header file include
//#include "../../lib_default/itf/lib_default.h"
#include "../../lib_new/itf/lib_new.h"
// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */
#define IDLE_PRIORITY 0

task_pt task_handle01;
task_pt task_handle02;
static void motortask(void * level);
static void ev3sensortask(void * level);




/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);

/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	motor_init();
	encoder_init();
	glcd_init();
	ev3_sensor_init(0, COL_COLOR);
	int level=0;
	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_ubinos_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");


	if (0 != task_create(&task_handle01, motortask, &level, IDLE_PRIORITY+1, 256, "task_01"))
		logme("fail at task_create\r\n");
	if (0 != task_create(&task_handle02, ev3sensortask, &level, IDLE_PRIORITY+2, 256, "task_02"))
		logme("fail at task_create\r\n");

	ubik_comp_start();

	return 0;
}

static void motortask(void * level) {

	for (;;) {
		motor_set(0,60*(*(int*)level));
	}
}
static void ev3sensortask(void * level) {
	for(;;){
	glcd_clear();
	switch(ev3_sensor_get(0))
			{
			case BLACK:
				glcd_printf("BLACK VAL : %3d", ev3_sensor_get(0));
				*(int*)level= BLACK;	break;
			case BLUE:
				glcd_printf("BLUE VAL : %3d", ev3_sensor_get(0));
				*(int*)level= BLUE;		break;
			case GREEN:
				glcd_printf("GREEN VAL : %3d", ev3_sensor_get(0));
				*(int*)level= GREEN;		break;
			case YELLOW:
				glcd_printf("YELLOW VAL : %3d", ev3_sensor_get(0));
				*(int*)level= YELLOW;		break;
			case RED:
				glcd_printf("RED VAL : %3d", ev3_sensor_get(0));
				*(int*)level= RED;		break;
			case WHITE:
				glcd_printf("WHITE VAL : %3d", ev3_sensor_get(0));
				*(int*)level= WHITE;		break;
			case BROWN:
				glcd_printf("BROWN VAL : %3d", ev3_sensor_get(0));
				*(int*)level= BROWN;		break;
			case NONE : default:
				glcd_printf("No color");
				*(int*)level= NONE;		break;
			}
	task_sleep(50);
	//bsp_busywaitms(5000);
	}
}




