# ITEC402005 종합설계프로젝트1,2 / 2020년 1,2학기 / 문병인

> 종합설계프로젝트 과목을 수강하며 제작한 공유전동 스케이트보드입니다.
<br>스케이트보드와 보관함의 코드가 첨부되어 있습니다.
<br>아두이노 IDE를 이용하였고 C언어로 작성하였습니다.
 
## 수행내용
#### 개요

> 현재 전동 스쿠터와 같은 모빌리티가 유행하고 있다. 하지만 기존의 전동 스쿠터나 전동 킥보드 등은 크기로 인해 관리가 제한적이고 전용 보관함의 부재로 도난 및 기상 환경에 취약한 문제가 있다. 이를 해결하기 위해 크기가 작아 휴대하기 편한 스케이트보드 형태의 모빌리티 제작으로 보관을 용이하게 만들어 도난 및 기상 환경에 대한 기존 모빌리티들의 취약점을 개선한다. 더 나아가 전용 앱을 제작해 전원 제어, 배터리 잔량 등 스케이트보드의 상태를 확인할 수 있는 기능을 구현하고 서버까지 구축해 공유 기능 또한 구현한다.

#### 스케이트보드 하드웨어

![](https://github.com/hwa10209/Capstone/blob/master/img/1.PNG)

> 나무판과 기존의 스케이트보드 부품을 이용하여 바디의 일부를 구성하였고, 배터리팩, VESC, BLDC Hub motor, 아두이노와 각종 센서 등을 이용하여 하드웨어를 구성하였다.


![](https://github.com/hwa10209/Capstone/blob/master/img/2.PNG)

> 구성 요소들로 회로를 꾸미고 하나의 보드를 제작

#### 스케이트보드 소프트웨어

![](https://github.com/hwa10209/Capstone/blob/master/img/3.PNG)

> 지난 학기에 운영체제와 사물컴퓨팅 과목에서 배운 내용을 토대로 Realtime OS를 이용하여 코드를 짜 보았다. 
보드에 전원이 인가되면 초기 설정 과정을 거친 후 FreeRTOS를 이용하여 센서, 블루투스 통신, 모터제어 등 각종 task를 동시에 실행한다.

```
#include <FreeRTOS_SAMD21.h>
```
> SAMD21계열의 프로세서를 사용하는 아두이노에서 RTOS를 사용하게 해주는 라이브러리

```
static void Thread1_bluetooth(void* arg);
static void Thread2_sensor_slow(void* arg);
static void Thread3_sensor_fast(void* arg);
static void Thread4_motor_control(void* arg);
```
> 멀티태스킹에 사용되는 4개의 task들의 동작을 정의

```
s1 = xTaskCreate(Thread1_bluetooth,    NULL, 400, NULL, 1, NULL);
s2 = xTaskCreate(Thread2_sensor_slow, NULL, 400, NULL, 1, NULL); 
s3 = xTaskCreate(Thread3_sensor_fast, NULL, 400, NULL, 2, NULL);
s4 = xTaskCreate(Thread4_motor_control, NULL, 400, NULL, 1, NULL); 
```
> task생성 및 메모리공한 할당, 우선순위 설정

#### 보관함 하드웨어
![](https://github.com/hwa10209/Capstone/blob/master/img/4.PNG)

> 전동 스케이트보드가 보관되는 보관함을 추가로 제작. 이 보관함에 보드를 넣고 뺴는 과정에서 서버와 어플의 도움을 받아 대여, 반납이 실행된다. RFID기능을 이용하여 실물이 보관함에 존재하는 여부를 판단한다.

#### 보관함 소프트웨어
> 위의 스케이트보드 동작방식과 같이 RTOS를 이용하여 스케이트보드의 대여 반납을 위한 코드를 작성
```
static void Thread2_checkCard(void* arg)
```
> 보관함 안에 스케이트보드가 들어있는지, 아니면 제거되었는지 실시간으로 판단

```
static void Thread1_main(void* arg)
```
> 문 상태, 잠금 상태, 서버 상태에 따라 현재 보관함/ 대여 / 반납 상태를 결정
