
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
static void rootfunc(void * arg) {
   glcd_init();
   motor_init();
   encoder_init();
   ev3_sensor_init(0, COL_REFLECT);

   /* calibration sensor : port0, light sensor */
   calibEV3Sensor(0, MAX_LIGHT_LEVEL, light_value);

   for(;;){
      glcd_clear();

      /* check sensor level */
      switch(get_level(ev3_sensor_get(0), MAX_LIGHT_LEVEL, light_value))
      {
      case LIGHT_DARK:
         glcd_printf("LIGHT LEVEL : %3d", LIGHT_DARK);
         motor_set(0,100);
         break;

      case LIGHT_DIM:
         glcd_printf("LIGHT LEVEL : %3d", LIGHT_DIM);
         motor_set(0,200);
         break;

      case LIGHT_BRIGHT:
         glcd_printf("LIGHT LEVEL : %3d", LIGHT_BRIGHT);
         motor_set(0,300);
         break;

      default:
         glcd_printf("UNDEFINE");
         break;
      }
      task_sleep(50);
   }
}
