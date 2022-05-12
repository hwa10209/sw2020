
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

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);
int scan();
void rotate(int level);
/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_ubinos_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

#define MAX_DIS_LEVEL 5
int distance_value[MAX_DIS_LEVEL]={0};

static void rootfunc(void * arg) {
	glcd_init();
	motor_init();
	encoder_init();
	sensor_init(NXT_DIGITAL_SENSOR_SONA, 0, 0, 0);

	calibSensor(0, MAX_DIS_LEVEL, distance_value);
	int level;

	for(;;){
		glcd_clear();
		level = scan();
		rotate(level);
	}
}
int scan(){
	switch(get_level(sensor_get(0), MAX_DIS_LEVEL, distance_value))
		{

		case 1:
			glcd_printf("very slow, dis : %3d", sensor_get(0));			return 1;
		case 2:
			glcd_printf("slow , dis : %3d", sensor_get(0));			return 2;
		case 3:
			glcd_printf("fast , dis : %3d", sensor_get(0));			return 3;
		case 4:
			glcd_printf("very fast , dis : %3d", sensor_get(0));			return 4;
		case 0 : default:
			glcd_printf("stop , dis : %3d", sensor_get(0));			return 0;
		}
}
void rotate(int level){
	motor_set(0,100*level);
	task_sleep(30);
}
