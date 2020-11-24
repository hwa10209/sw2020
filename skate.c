

//single, 외장블투O
/*---------------------------------------------------------
 *                     라이브러리
----------------------------------------------------------*/
//#include <FreeRTOS_AVR.h>
#include <FreeRTOS_SAMD21.h>
//#include <ArduinoBLE.h>
//#include <Arduino_LSM6DS3.h>
#include <Servo.h>
/*---------------------------------------------------------
 *                     핀 번호, 롤러 동작 설정
----------------------------------------------------------*/
const uint8_t LED_PIN = 13;
const uint8_t P_PIN1 = A2;                           //압력 센서  측정1
const uint8_t P_PIN2 = A3;                           //         측정2
  
const uint8_t B_PIN1 = A0;                           //배터리 잔량 측정1
const uint8_t B_PIN2 = A1;                           //배터리 잔량 측정2

const uint8_t hall_sensor1 = 2;                      //모터1 홀센서
const uint8_t hall_sensor2 = 3;
const uint8_t hall_sensor3 = 9;                      //속도2 홀센서
const uint8_t hall_sensor4 = 10;                                          //가장 잘 됨

const uint8_t MOTOR_PIN1 =6;                         //VESC1
const uint8_t MOTOR_PIN2 =5;                         //VESC2

const int MAX_SIGNAL =2040;                          //ESC의 모터 출력 최대
const int MIN_SIGNAL =1535;                          //              중립
const int BRK_SIGNAL = 1030;                          //              최소(브레이크 최대)

const int mode_brk = 0, mode_slow = 1, mode_fast = 2;             // 0: 브레이크, 1:저속모드, 2:고속모드
const int mode_brk_max = 0,mode_slow_max = 5, mode_fast_max =10;  // 모드별 최고속도
const int threshold_point1 = 30, threshold_point2 = 120;           //센서 인식 임곗값
/*---------------------------------------------------------
 *                     롤러 상태, 사용 변수
----------------------------------------------------------*/



static int my_mode = mode_brk;              
static int my_speed =mode_brk_max;

SemaphoreHandle_t sem;                               //세마포. 아직 사용여부 미정
static int press_in1=0, press_in2=0;                 //압력 센서1, 2
//static int infrared_in=0;                          //적외선 센서
static int battery_in1=0, battery_in2=0;              //배터리1

Servo motor1,motor2;            //모터 동작용 변수들
static int pwm;
static int ct1 =0, ct2 =0, ct3 =0, ct4 =0;
static int nowtime=0, lasttime =0;
static int nowrot1=0, lastrot1 =0, nowrot2=0, lastrot2 =0;

static double timediff =0, rotdiff1 =0, rotdiff2 =0;
static double speedcheck=0, speedcheck1, speedcheck2;   //두 모터의 평균, 모터1, 모터2 속도

static double Kp=0.3, Ki=0.5, Kd=0.01;
static double error, error_previous;
static double desired_speed=0;
static double P_control,I_control,D_control, PID_control;

      //잠시 메모(세마포 사용법)
      // xSemaphoreTake(sem, portMAX_DELAY); 세마포어 기다리기
      // xSemaphoreGive(sem);                세마포어 전달하기 
      // vTaskDelay( );                      태스크의 휴식(?) 
/*---------------------------------------------------------
 *                     프로토타입
----------------------------------------------------------*/
static void Thread1_bluetooth(void* arg);
static void Thread2_sensor_slow(void* arg);
static void Thread3_sensor_fast(void* arg);
static void Thread4_motor_control(void* arg);

void PRESS();
//int INFRA();
void BAT();
//void ACC();
//void GYRO();

void setspeed(double number);      //모터 동작 함수
int setspeedmode(int mode);
/*---------------------------------------------------------
 *                     메인 코드
----------------------------------------------------------*/


void setup() {
  portBASE_TYPE s1, s2, s3, s4;
  Serial.begin(115200);
  sem = xSemaphoreCreateCounting(1, 0);       //세마포어를 초기화 합니다. 세마포어는 동시에 1개만 생성됩니다.

  motor1.attach(MOTOR_PIN1);
  motor2.attach(MOTOR_PIN2);
  delay(2000);
  pinMode(hall_sensor1, INPUT); 
  pinMode(hall_sensor2, INPUT);
  pinMode(hall_sensor3, INPUT);
  pinMode(hall_sensor4, INPUT);
  //attachInterrupt(digitalPinToInterrupt(hall_sensor1), count1, RISING); //RPM 측정을 위한 인터럽트 활성화. 3개까지 사용가능
  //attachInterrupt(digitalPinToInterrupt(hall_sensor2), count2, RISING);
  //attachInterrupt(digitalPinToInterrupt(hall_sensor3), count3, RISING); //RPM 측정을 위한 인터럽트 활성화. 3개까지 사용가능
  attachInterrupt(digitalPinToInterrupt(hall_sensor4), count4, RISING);

  pinMode(P_PIN1,INPUT);
  pinMode(P_PIN2,INPUT);
  pinMode(B_PIN1,INPUT);
  pinMode(B_PIN2,INPUT);
  
  Serial1.begin(9600);
  delay(200);
  pinMode(13,OUTPUT);
  Serial1.print("AT+NAMEmcuhq\n");;
  Serial1.print("velocity : + AT"); 
  
  s1 = xTaskCreate(Thread1_bluetooth,    NULL, 400, NULL, 1, NULL); // Thread 생성
  s2 = xTaskCreate(Thread2_sensor_slow, NULL, 400, NULL, 1, NULL); 
  s3 = xTaskCreate(Thread3_sensor_fast, NULL, 400, NULL, 2, NULL);
  s4 = xTaskCreate(Thread4_motor_control, NULL, 400, NULL, 1, NULL); 
  
  
  // 세마포어,스레드 생성에 에러가 생길 경우 에러메시지 출력
  //if (sem== NULL || s1 != pdPASS || s2 != pdPASS || s3 != pdPASS || s4 != pdPASS) {
  //  Serial.println(F("Creation problem"));
  //  while(1);
  //}

  Serial.println("task start");
  vTaskStartScheduler();  // 태스크 스케쥴러 시작, 멀티태스킹 시작
  Serial.println(F("Insufficient RAM"));
  while(1);
}

void loop() {}
/*---------------------------------------------------------
 *                     태스크 설명
----------------------------------------------------------*/
static void Thread1_bluetooth(void* arg) {
  
  while (1) {
   Serial.println("@Thread1");
   if (Serial1.available()) {
    if(Serial1.read() == '1'){ // did we receive this character?
      digitalWrite(13,!digitalRead(13)); // if so, toggle the onboard LED
    }
   }


  Serial1.print("[,");
  Serial1.print(battery_in1); // print this to bluetooth module
  Serial1.print(",");
  Serial1.print(battery_in2); // print this to bluetooth module
  Serial1.print(",");
  Serial1.print(speedcheck); // print this to bluetooth module
  Serial1.print(",]");  
  Serial1.println();

      
  vTaskDelay(500);
  }
}


static void Thread2_sensor_slow(void* arg) {
  while (1) {
     Serial.println("@Thread2");
     BAT();  //battery_in1, battery_in2;
     
     vTaskDelay(2000);
  }
}

static void Thread3_sensor_fast(void* arg) {  
  while (1) {
     Serial.println("@Thread3 :");
     PRESS();

     if(press_in1>threshold_point1)          //압력에 따른 나의 속도모드 결정
       my_mode = mode_slow;                  //앞의 압력센서가 눌리면 저속모드
     else if(press_in2>threshold_point2)     //앞의 압력센서가 눌리지 않고 뒤의 센서가 눌리면 고속모드
       my_mode = mode_fast;         
     else                                    //모두 눌리지 않으면 브레이크
       my_mode = mode_brk;
    
     vTaskDelay(150);
  }
}







static void Thread4_motor_control(void* arg) {        
  while (1) {
    Serial.println("@Thread4 : ");
                                                       
    nowtime=millis();
    timediff=nowtime-lasttime;
    lasttime=nowtime;
    nowrot1=(ct1+ct2)*2;               //하나의 홀센서만 사용중
    nowrot2=(ct3+ct4)*2;
    rotdiff1=nowrot1-lastrot1;
    rotdiff2=nowrot2-lastrot2;
    lastrot1=nowrot1;
    lastrot2=nowrot2;
  
    //speedcheck1= (rotdiff1/timediff)*36*1.57;  //지름 7cm, 1/14바퀴에 0.0157meter, km/h
    speedcheck= (rotdiff2/timediff)*36*1.57; 
    //speedcheck = (speedcheck1+speedcheck2)/2;
    
    my_speed = setmaxspeed(my_mode);
    Serial.print("mode = : ");Serial.println(my_mode);
    Serial.print("INPUT = ");Serial.print(my_speed);
    if(my_mode != mode_brk){
      if(my_speed > speedcheck)
        setspeed(speedcheck+0.3);
      else
        setspeed(speedcheck-0.3);
    }
    else{
      int pwm_brk = ( map(press_in1, 0, threshold_point1, BRK_SIGNAL, MIN_SIGNAL) + map(press_in2, 0, threshold_point2, BRK_SIGNAL, MIN_SIGNAL) )/2;
      Serial.print(" PWM = "); Serial.print(pwm_brk);
      motor1.writeMicroseconds(pwm_brk);
      motor2.writeMicroseconds(pwm_brk);
    }
     
    Serial.print(" hall sensors(1~4) = ");
    Serial.print(ct1);Serial.print(" ");Serial.print(ct2);Serial.print(" ");
    Serial.print(ct3);Serial.print(" ");Serial.print(ct4);
    Serial.print(" speed = "); Serial.print(speedcheck); Serial.println(" km/h");
    vTaskDelay(150);
  }
}



/*---------------------------------------------------------
 *                     함수 설명
----------------------------------------------------------*/

void PRESS(){

  press_in1 = analogRead(P_PIN1);
  press_in2 = analogRead(P_PIN2)*5;
  
  Serial.print("압력 센서 = "); 
  Serial.print(press_in1);
  Serial.print(", ");
  Serial.println(press_in2);
}

void BAT(){

  
  battery_in1 = analogRead(B_PIN1);
  battery_in2 = analogRead(B_PIN2);
  Serial.print("배터리 = "); 
  Serial.print(map(battery_in1, 600, 1023, 0, 100));
  Serial.print(" %, "); 
  Serial.print(map(battery_in2, 600, 1023, 0, 100));
  Serial.println(" %");
}

int setmaxspeed(int mode){
  switch(mode){
    case mode_fast : return mode_fast_max;
    case mode_slow : return mode_slow_max;
    default : return mode_brk_max;
  }
}

void setspeed(double speedset){      //PID 제어 코드

  desired_speed = speedset;
  error = desired_speed - speedcheck;
  if(error<-8)          //급정지 할때는 속도 빠르게 감소
    Ki=2;
  else
    Ki=0.5;         //평소에는 낮은 gain(overshoot, 급발진 방지)
  
  P_control = Kp*error;
  I_control+=Ki * error * (timediff/1000);
  D_control = Kd * (error - error_previous) / (timediff/1000);
  error_previous = error;

  PID_control = P_control + I_control + D_control;
  PID_control = constrain(PID_control, 0, 20);    //0~20로 값이 제한됨

  pwm = map(PID_control,0,20.0,MIN_SIGNAL,MAX_SIGNAL);
  Serial.print(" PWM = "); Serial.print(pwm);  
  motor1.writeMicroseconds(pwm);   
  motor2.writeMicroseconds(pwm);
}


         
 

void count1(){  //인터럽트 카운터, 한바퀴에 7 증가
  ct1++; 
}
void count2(){
  ct2++; 
}
void count3(){
  ct3++; 
}
void count4(){
  ct4++; 
}

/*
int INFRA(){
  vTaskDelay(10);//센서 측정할 시간 확보
  int infraredValue = analogRead(I_PIN);

  Serial.print("적외선 센서 = ");
  Serial.println(infraredValue);
  
  infrared_check = 0;
  return infraredValue;
}
*/

/*
void ACC(){
  IMU.readAcceleration(accel_x, accel_y, accel_z);
  Serial.print("가속도 센서 = ");
  Serial.print(accel_x);  //Serial.print(", ");
  Serial.print(accel_y); //Serial.print(", ");
  Serial.println(accel_z);
  acc_check = 0;
}

void GYRO(){
  IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
  Serial.print("자이로 센서 = ");
  Serial.print(gyro_x);//Serial.print(", ");
  Serial.print(gyro_y); //Serial.print(", ");
  Serial.println(gyro_z);
  gyro_check = 0;
}
*/