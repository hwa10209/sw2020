# COMP312001 운영체제 / 2019년 1학기 / 강순주

운영체제 과목을 수강하며 수행한 과제들 입니다.

## 요약

> HW1<br>HW2<br>HW3<br>HW4<br>HW5 

## 수행내용
### 1. HW1


#### 개요
* 지난 학기의 자료구조에서 배운내용을 운영체제 1,2주차 강의를 들으며 복습하면서		 
실습환경-리눅스(우분투)을 구축해보고 실제로 STACK과 QUEUE를 구현해 본다.

#### 다이어그램

#### 함수에 대한 설명
> create_stack()	stack 생성 및 stack 내부 설정<br>push(STACK* stack, void* in) stack주소, 데이터 입력후 그에대한 stack의 노드를 push
<br>pop(STACK* stack) stack에 저장된 노드를 pop
<br>playstack()	stack의 동작을 선택하고 볼 수 있는 함수
<br>CreateQueue()	queue 생성 및 queue 내부 설정
<br>Enqueue(QUEUE* pQueue, void* item) queue주소, 데이터 입력후 그에 대한 queue의 노드를 enque
<br>Dequeue(QUEUE* pQueue) queue에 저장된 노드를 dequeue
<br>playqueue()	queue의 동작을 선택하고 볼 수 있는 함수

#### 결과

#### 고찰
>코드를 짜기에 앞서 처음으로 리눅스를 접하게 되면서 실습 환경을 구축하기 위해 시간을 많이 썼다. 리눅스에서의 한글 입력과 컴파일 방식, 코딩 환경이 윈도우의 그것과는 차이가 있어서 조금 불편하긴 했지만 조금씩 적응이 되자 오히려 윈도우에서 보다 더 자유로워지고 더 많은 것을 할 수 있을 것 같은 느낌을 받았다. <br>Stack과 Queue를 직접 구현해 보면서 문자를 한줄로 입력하고 strtok 함수를 이용하여 문자를 나누어 push, enqueue 하고 pop, dequeue 하여 좀더 깔끔하게 실행시킬 수 있다.  다만 입력을 할 때 여느 때처럼 scanf() 를 사용하였는데 오류가 났다. 한참 검색을 해보다 윈도우와 리눅스 상에서 c언어 문법이 약간씩 다르다는 것을 알게 되었다. 그래서 버퍼를 비울 때도 fflush(stdin)이 적용되지 않았던게 원인이었고, 리눅스만의 함수를 사용하자 그제서야 정상적으로 작동하였습니다. pop과 dequeue 과정에서 '세그멘테이션 오류'가 많이 떴는데, 그것이 주로 메모리를 다루는 과정에서 발생한다는 것을 알게되었고, 어떻게 해결하는지 이해 할 수 있었다.

#### 참고자료
https://blog.naver.com/thwjd2525/221436531441
<br>stack과 queue 복습
<br>https://blog.naver.com/wony9555/221454726518
<br>strtok 함수
<br>https://blog.naver.com/whdgml1996/221127051226
<br>헤더와 전처리
<br>https://bowbowbow.tistory.com/12
<br>make, makefile 사용법

---
### 2. HW2

#### 개요
* fork 함수와 exec 함수를 이용하여 나만의 쉘을 만들어 봄으로써 멀티프로세스를 구현해 본다.

#### 다이어그램
#### 함수에 대한 설명
>main()		Myshell의 시작. 사용가능한 명령어들을 보여주고 입력 받을 수 있음.<br>
ls(int a)		ls 또는 ls –al 명령어를 사용하기 위한 함수. 현재 디렉토리의 파일, 폴더 리스트를 나열해주는 함수.<br>
mkdir(char *b) mkdir 명령어를 사용하기 위한 함수. 추가로 이름을 입력 받아 현재 위치에 새 디렉토리를 만들 수 있게 해주는 함수.<br>
pwd()		pwd 명령어를 사용하기 위한 함수. 현재 위치 표시.<br>
exit(함수x)		종료.<br>

#### 결과

#### 고찰
>직접 shell을 만들어 보면서 fork()함수와 exec~ 함수들의 이해도가 높아졌고 프로세스를 만드는데도 좀 더 익숙해 진 것 같다. 또한 명령어를 입력받으면서 저번에 이용한 strtok()함수를 복습하면서 이용해 보았고 프로세스에 인자를 전달하는 방식을 체험해 보았다. 이런 방식을 활용해 보면 더 복잡한 쉘이나 운영체제를 다루는 인터페이스도 만들어 볼 수 있을 것 같다.
#### 참고자료
>https://bbolmin.tistory.com/35?category=479897<br>
	exec계열의 함수 종류와 사용법 참고.
  
---
### 3. HW3

#### 개요
* pthread를 이용하며 우연히 발생하는 critical section 문제를 확인하고 해결해 본다.
*	matrix의 계산을 single / multi processor를 이용하여 수행해보고 수행시간을 비교해본다.
#### 다이어그램
* Bank
>main()		bank.c 의 main, deposit, withdraw쓰레드를 100개씩 만들고 실행.
#### 함수에 대한 설명
#### 결과
#### 고찰
#### 참고자료

---
### 4. HW4

#### 개요
* 운영체제의 기능중 하나인 memory management, stack과 heap이 관리되는 모습을 		확인한다.
임의의 메모리 할당을 통해 메모리의 stack, heap 영역이 충돌하는 현상을 구현
#### 다이어그램
#### 함수에 대한 설명
#### 결과
#### 고찰
#### 참고자료

---
### 5. HW5
#### 개요
* 커널에서 모듈을 다뤄보고 메모리에 글자를 보내면 case 변경과 100자 초과 덮어쓰기 기능이 있는 간단한 디바이스 드라이버를 만들어 본다.

#### 다이어그램
#### 함수에 대한 설명
#### 결과
#### 고찰
#### 참고자료
