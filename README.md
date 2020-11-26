# ELEC323004 마이크로프로세서 / 2019년 1학기 / 김종화

> 마이크로프로세서 과목을 수강하며 수행했던 과제입니다
<br> edsim51di와 keil 환경에서 실습을 진행하였습니다.
<br> 어셈블리언어와 헥사코드, 그리고 앞의 코드와 같은 기능을 하는 c 언어로 코드를 짰습니다.

## 요약

> HW1 : 1-1, 1-2, 1-3<br>HW2

## 수행내용
### 1. HW1 : 1-1
#### 개요

> 스위치 2개로 LED8개의 출력을 조절하는 어셈블리 코드를 작성
<br>동작방식

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_0.PNG)

#### 소스코드

[소스코드 확인](https://github.com/hwa10209/Microprocessor/blob/master/HW1/code1.txt)

> 동작 FREQUENCY 10000으로 실행
#### 동작

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_1.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_2.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_3.PNG)

> 버튼 두 개를 이용, 두 방향으로 한칸씩 회전, 정지, OFF, 네가지 동작을 구현
<br>두 버튼을 PORT2의 두 비트로 입력 받아서 MAIN LOOP에서 검사,
<br>각 네가지 동작에 대한 ROUTINE으로의 이동이 이루어진다.
<br>그리고 한번의 “동작(출력)-> DELAY -> 검사” 와 같은 동작을 반복 한다.

### 2. HW1 : 1-2
#### 개요
> 스위치와 FND를 이용
<br>눌린 스위치 수를 FND에 표시하는 어셈블리 코드를 작성

#### 소스코드

[소스코드 확인](https://github.com/hwa10209/Microprocessor/blob/master/HW1/code2.txt)

> 동작 FREQUENCY 10000으로 실행

#### 동작

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_4.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_5.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_6.PNG)

> 8개의 버듵을 PORT2에서 입력받고 한 바이트를 특정 위치에 저장,
<br>그 것을 반복문을 이용하여 8번 회전시키며 비트값을 확인하며 눌린 스위치의 수를 센다.
<br>INDEXED ADDRESSING MODE를 이용하여 미리 만든 LOOK UP TABLE을 이용하여
<br>FND에 출력할 값을 불러오고 PORT1에 출력한다. 이 과정을 반복함.
<br>스위치가 눌린 위치와 표시되는 숫자는 관련이 없다.
<br>따라서 눌린 스위치의 조합이 다르더라도 개수만 같으면 같은 숫자가 출력된다.
<br>또한 기본적으로 출력되는 FND의 위지를 지정하는 PORT3의 4,3번 비트(11 10 01 00중 하나)가
<br>11로 초기화 되어 특별한 설정 없이 가장 왼쪽의 SEGMENT를 사용하게 된다.

### 3. HW1 : 1-3
#### 개요
> 스위치와 FND를 이용
<br>0에서 99까지 순서대로 증가하는 카운터를 구현하여 FND에 표시
<br>스위치가 눌리면 FND에 표시되는 값이 0으로 초기화 된다.

#### 소스코드

[소스코드 확인](https://github.com/hwa10209/Microprocessor/blob/master/HW1/code3.txt)

> 카운터를 천천히 동작시키기 위해 FREQUENCY 1000으로 실행

#### 동작

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_7.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_8.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_9.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/1_10.PNG)

> 스위치 상태를 판별하면서 숫자증가 -> 숫자 출력 함수가 반복된다.
<br>스위치가 눌리지 않으면 카운터 함수가 실행, 자리수를 고려하며 수를 1씩 증가후 출력 함수를 호출.
<br>출력함수가 실행 되면 LOOK UP TABLE의 도음을 받아 10의자리 값을 첫 번째, 1의자리에 저장된 값을 두 번째 FND에 출력하는데 P3.3의 비트를 조정해가며 FND 각각 하나를 한번씩 껐다 켜고 메인 루프로 돌아간다.
<br>스위치가 눌린다면 1의자리,10의 자리 숫자로 지정해둔 레지스터 값을 계속 0으로 초기화 하고 출력, 다시 스위치가 떨어지면 0부터 수를 1씩 증가시키며 표시한다.
<br>그런데 여기서 두 개의 FND를 이용하여 두자리 숫자를 출력하는데 잔상효과를 이용하여 사람의 눈에 두 수가 동시에 보이는 것처럼 만들기 위해 FND가 깜빡이는 속도가 상당히 빠르게 설정되어있다.
<br>만약 한번씩 깜빡일 때 마다 수가 증가한다면 사람의 눈으로 그것을 하나하나 구별하지 못할 것이다.
<br>따라서 깜빡이는 속도와 숫자가 증가하는 속도에 차이를 두기위해 UPCOUNT 루틴 내부에 SLOWCOUNT루틴으로 루프를 만들어 두 수가 다섯 번씩 깜빡이고 난 뒤 1만큼 증가하도록 해 주었다.

#### 고찰

> 스위치와 LED, SEGMENT를 이용하는 코드를 짜보면서 이론으로 배웠던 PORT입, 출력을 통해 각
소자의 동작을 확인해 보았고, 이들의 유기적인 동작을 조정해 봄으로써 I/O PIN의 이해도가 높아 졌다.
<br>또한 MCU에 연결된 소자의 특성에 따라 ON(또는 출력) 신호가 PIN 값이 0 또는 1이 될 수 있는데
시뮬레이터의 오른쪽 화면을 보면 모든 I/O PIN 값이 1로 초기화됨을 확인 할 수 있고, 따라서 모두 PULL UP 저항으로 연결되어 있음을 알 수 있다.
<br>또한 네 SEGMENT의 32개 LED 가 P3.4, P3.3의 두 비트와 P1의 8비트만으로 출력되기 때문에
한번에 한 위치의 SEGMENT가 출력되고 잔상효과를 이용하여 여러 수가 동시에 보이도록 각각 깜빡이는 시간을 조절 할 수 있었다. 

---
### 4. HW2


#### 개요

> 월/날짜를 키패드로 입력받아 FND에 출력도 하고
직렬통신으로 전송도 해주는 프로그램을 짜본다. 
<br>keil을 이용하여 위의 똑같은 기능을 C언어로 구현해보고 비교한다

#### 소스코드

[소스코드 확인](https://github.com/hwa10209/Microprocessor/blob/master/HW2/code.c)

> 동작환경은 edsim51 setting keypad "pulse", "12Mhz", "10000" update Freq, "no" parity, "4800"Baud

[소스코드 확인](https://github.com/hwa10209/Microprocessor/blob/master/HW2/code.txt)
> 어셈블리어로 작성한 코드.
<br>C로 작성했던 코드보다 약간 길지만, 동작이 좀 더 빠르다.

#### 동작

![](https://github.com/hwa10209/Microprocessor/blob/master/img/2_1.PNG)

![](https://github.com/hwa10209/Microprocessor/blob/master/img/2_2.PNG)

>키패드 설정 pulse로, 설정.
<br>스위치 1번을 눌렀다 뗌으로써 모드1 날짜 입력모드 진입.
<br>fnd에 ‘SAVE’가 두 번 씩 표시됨
<br>키패드로 월/날짜에 해당하는 4개의 숫자를 입력
<br>ex)3/15 -> 0315
<br>입력할 때 마다 한번 누른 숫자가 한번 표시됨
<br>스위치 2번을 눌렀다 뗌으로써 모드2 확인모드로 진입.
<br>fnd에 ‘dAtE’가 두 번 씩표시됨
<br>fnd에 입력했던 월과 일이 두 번 씩 표시됨
<br>스위치 3번을 눌렀다 뗌으로 써 모드3 직렬통신:전송모드로 진입.
<br>fnd에 ‘SEnd’가 두 번 씩표시됨
<br>저장했던 날짜를 전송
<br>시뮬레이서 RX란에서 전송되는 날짜 확인

> 지금까지 배웠던 모든 8051을 다루는 방법을 이용하여 코드를 작성함.
<br>메인 루틴에서 스위치 입력이 발생하면 모드를 판별하는데 먼저 첫 번째 모드로 진입해 본다
<br>두가지 큰 함수를 이용하였는데 먼저 내가 들어가는 모드가 무엇인지 저장해 놨던 문자를 이용해서 보여주는 함수와 숫자 저장모드로 구성되어있다.
<br>들어가 보면 4개의 숫자를 키패들르 이용해서 입력받는데 먼저 키패드가 눌리기 전에는 고정 루프를 돌며 저장을 하지 않다가 어떤 숫자가 눌리게 되면 루프를 빠져 나오면서 그값을 하나저장하고 또 다시 대기루프로 가는 행동을 4번 반복한다.
<br>또한 값을한번 저장하면 어떤 값이 저장되고 있는지 잠깐동안 띄워준다.
<br>두 번째 모드 또한 모드 표시 함수와 다른 함수로 구성되어있는데, 두 번째 함수를 확인해보면 1번모드에서 저장한 네 수를 각각 네 개의 fnd 칸에 두 번씩 표시해주는 코드들로 되어있다.
<br>세 번째 모드 또한 마찬가지로 모드 표시를 먼저 해주고 다음 함수에서 저장했던 값들을 전송해주는데 교육자료와 edsim 사이트의 예시를 참조하여 4800보드레이트, no parity bit 설정에 double 보드레이트를 활용하여 전송을 할 수 있도록 하였다.

#### 고찰

> 직렬 통신을 추가로 사용해 보았는데 조절할 수 있는 기능이 너무 많아서 간단한 글자를 보내기조차 조금 어려웠지만 몇 번 연습해 보니 익숙해 졌다.
<br>C언어와 어셈블리 언어로 각각 짜보았는데 좀 더 익숙했던 C언어가 쉬울 것 이라고 생각했으나 EDSIM51이 동작하는 원리를 이해하고 짜야 하는 탓에 생각보다 더 시간이 걸렸다.
<br>코드를 짜는 자체에는 난해했지만, 반복문과 조건문, 좀더 명확한 이름설정 덕에 전체적인 구조와 동작원리를 구현해 나가는 데에는 확실히 쉬웠다.
<br>비교를 해 보자면 어셈블리어가 반복문 처리에 좀 더 어려워서 조금 더 길고 일정길이를 넘어가면 다른 분기 명령어를 써야하는 탓에 코드를 덕지덕지 붙인 기억이 있어 깔끔하게 구현하기는 어려웠던 것 같다.
<br>또 DELAY 같은 함수에서 두 프로그램의 동작을 비교 해볼 수 있는데 C와 어셈블리 각각 1만 CYCLE, 4만 CYCLE로 짰음에도 불구하고 어셈블리 코드가 조금더 빨리 동작했다.
<br>따라서 코드 한줄만 놓고 봤을 땐 C보다 어셈블리어가 좀더 간단하고 빠름을 알 수 있다.
<br>또한 KEIL에서 DEBUGING 모드로 구현된 어셈블리어를 보면 직접 잔 어셈블리보다 더 지저분함을 봤을 때 여러 가지 방법으로 코드를 짤 수 있음을 확인 할 수 있다.
