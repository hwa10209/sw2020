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
![](https://github.com/hwa10209/OS/blob/master/img/1_1.bmp)
#### 함수에 대한 설명
> create_stack()	stack 생성 및 stack 내부 설정<br>push(STACK* stack, void* in) stack주소, 데이터 입력후 그에대한 stack의 노드를 push
<br>pop(STACK* stack) stack에 저장된 노드를 pop
<br>playstack()	stack의 동작을 선택하고 볼 수 있는 함수
<br>CreateQueue()	queue 생성 및 queue 내부 설정
<br>Enqueue(QUEUE* pQueue, void* item) queue주소, 데이터 입력후 그에 대한 queue의 노드를 enque
<br>Dequeue(QUEUE* pQueue) queue에 저장된 노드를 dequeue
<br>playqueue()	queue의 동작을 선택하고 볼 수 있는 함수

#### 결과

![](https://github.com/hwa10209/OS/blob/master/img/1_2.bmp)

![](https://github.com/hwa10209/OS/blob/master/img/1_3.bmp)

#### 고찰
> 코드를 짜기에 앞서 처음으로 리눅스를 접하게 되면서 실습 환경을 구축하기 위해 시간을 많이 썼다. 리눅스에서의 한글 입력과 컴파일 방식, 코딩 환경이 윈도우의 그것과는 차이가 있어서 조금 불편하긴 했지만 조금씩 적응이 되자 오히려 윈도우에서 보다 더 자유로워지고 더 많은 것을 할 수 있을 것 같은 느낌을 받았다. <br>Stack과 Queue를 직접 구현해 보면서 문자를 한줄로 입력하고 strtok 함수를 이용하여 문자를 나누어 push, enqueue 하고 pop, dequeue 하여 좀더 깔끔하게 실행시킬 수 있다.  다만 입력을 할 때 여느 때처럼 scanf() 를 사용하였는데 오류가 났다. 한참 검색을 해보다 윈도우와 리눅스 상에서 c언어 문법이 약간씩 다르다는 것을 알게 되었다. 그래서 버퍼를 비울 때도 fflush(stdin)이 적용되지 않았던게 원인이었고, 리눅스만의 함수를 사용하자 그제서야 정상적으로 작동하였습니다. pop과 dequeue 과정에서 '세그멘테이션 오류'가 많이 떴는데, 그것이 주로 메모리를 다루는 과정에서 발생한다는 것을 알게되었고, 어떻게 해결하는지 이해 할 수 있었다.

#### 참고자료
> https://blog.naver.com/thwjd2525/221436531441
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
![](https://github.com/hwa10209/OS/blob/master/img/2_1.bmp)
#### 함수에 대한 설명
> main()		Myshell의 시작. 사용가능한 명령어들을 보여주고 입력 받을 수 있음.<br>
ls(int a)		ls 또는 ls –al 명령어를 사용하기 위한 함수. 현재 디렉토리의 파일, 폴더 리스트를 나열해주는 함수.<br>
mkdir(char (포인터)b) mkdir 명령어를 사용하기 위한 함수. 추가로 이름을 입력 받아 현재 위치에 새 디렉토리를 만들 수 있게 해주는 함수.<br>
pwd()		pwd 명령어를 사용하기 위한 함수. 현재 위치 표시.<br>
exit(함수x)		종료.<br>

#### 결과
![](https://github.com/hwa10209/OS/blob/master/img/2_2.bmp)
![](https://github.com/hwa10209/OS/blob/master/img/2_3.bmp)
![](https://github.com/hwa10209/OS/blob/master/img/2_4.bmp)


#### 고찰
> 직접 shell을 만들어 보면서 fork()함수와 exec~ 함수들의 이해도가 높아졌고 프로세스를 만드는데도 좀 더 익숙해 진 것 같다. 또한 명령어를 입력받으면서 저번에 이용한 strtok()함수를 복습하면서 이용해 보았고 프로세스에 인자를 전달하는 방식을 체험해 보았다. 이런 방식을 활용해 보면 더 복잡한 쉘이나 운영체제를 다루는 인터페이스도 만들어 볼 수 있을 것 같다.
#### 참고자료
> https://bbolmin.tistory.com/35?category=479897<br>
exec계열의 함수 종류와 사용법 참고.
  
---
### 3. HW3

#### 개요
* pthread를 이용하며 우연히 발생하는 critical section 문제를 확인하고 해결해 본다.
*	matrix의 계산을 single / multi processor를 이용하여 수행해보고 수행시간을 비교해본다.
#### 다이어그램

![](https://github.com/hwa10209/OS/blob/master/img/3_1.bmp)
![](https://github.com/hwa10209/OS/blob/master/img/3_2.bmp)
![](https://github.com/hwa10209/OS/blob/master/img/3_3.bmp)
![](https://github.com/hwa10209/OS/blob/master/img/3_4.bmp)
#### 함수에 대한 설명
* Bank
> main()		bank.c 의 main, deposit, withdraw쓰레드를 100개씩 만들고 실행.<br>
deposit()	1원 저축을 500번 수행함<br>
withdraw()	1원 출금을 500번 수행함<br>

* Bank2
> main()		bank2.c 의 main, deposit, withdraw쓰레드를 100개씩 만들고 실행.mutex 생성, 설정.  기존의 critical section을 서로 고립시켜주었음.
<br>deposit()	1원 저축을 500번 수행함, mutex lock, unlock
<br>withdraw()	1원 출금을 500번 수행함, mutex lock, unlock

* Single
> main()		single_mat.c 의 main, 3X3행렬 계산 및 출력

* Multi
> main()		multi_mat.c 의 main, 3X3 행렬 계산 및 출력, mulf 쓰레드 생성. 쓰레드 하나당 한 행X한 열 을 계산하고 저장한다. (총 3개의 쓰레드)
<br>mulf(void args) 계산완료 후의 행렬의 각 행을 의미하는 값을 받아서 그 행다른열들의 곱을 수행


#### 결과
![](https://github.com/hwa10209/OS/blob/master/img/3_5.bmp)

> 계산한 값의 정확성이 보장되지 않고 똑같은 작업을 수행해도 값이 달라진다.

![](https://github.com/hwa10209/OS/blob/master/img/3_6.bmp)

> critical section을 mutex를 이용하여 분리해주자 의도한 값이 계산 결과로 나왔다.

![](https://github.com/hwa10209/OS/blob/master/img/3_7.bmp)

> 두 matrix를 곱하는데 4micro sec 정도 걸림.

![](https://github.com/hwa10209/OS/blob/master/img/3_8.bmp)

> 똑같은 작업을 수행했음에도 불구하고 멀티프로세싱을 하니 964 micro sec, single processing 보다 훨씬 오래 걸렸다.

#### 고찰
> 멀티 프로세싱을 하면 작업을 훨씬 효율적으로 할 수 있다. 하지만 그에 따라 단점들도 발견되는데 먼저 critical section problem을 보면 하나의 전역변수에 여러 쓰레드가 동시에 작업을 수행하여 그 값이 보장되지 않고 무작위의 값이 나온다. 이를 예방하기 위해 mutex를 이용하여 쓰레드의 동시 수행되지 않아야 하는 부분을 고립시켜주어 이 현상을 없애준다. 앞으로 여러개의 쓰레드를 사용할 땐 critical section을 잘 조절하여 결과값에 대한 신뢰도를 높여야 겠다.<br>또한 효율적인 작업을 위해 멀티 쓰레딩을 하였는데 싱글 쓰레딩보다 오히려 작업시간이 길어지는 모습을 볼 수 있다. 이는 같은 작업을 하더라도 context switching 으로 인해 추가시간이 발생하기 때문인데 간단한 프로그램을 짤땐 오히려 single threading이 더 알맞을 수도 있다.


#### 참고자료
> 강의노트 pthread<br>
https://blog.naver.com/dwc2206/221009412148<br>matrix 다루기
---
### 4. HW4

#### 개요
* 운영체제의 기능중 하나인 memory management, stack과 heap이 관리되는 모습을 		확인한다.
임의의 메모리 할당을 통해 메모리의 stack, heap 영역이 충돌하는 현상을 구현
#### 다이어그램

![](https://github.com/hwa10209/OS/blob/master/img/4_1.bmp)
#### 함수에 대한 설명
>FirstHeapLocation, FirststackLocation등 함수에서도 쓰이는 변수들을 편하게 쓰기위해 정의함
<br>main() 프로그램 실행행시 스택과 힙에 지정해줄 기본단위의 크기를 받고 그 크기를 가지고 스택, 힙을 채워본다.  또한 힙과 스택이 쌓이는 초기위치를 출력. 임의의 숫자를 입력하면 메가바이트 단위로 설정되도록 코드를 구성.
<br>Memory_allocation(int HEAP_ALLOC, int STACK_ALLOL) 힙과 스택을 채울 기본 단위크기를 받아 호출되고 stack의 특성을 살리기 위해 recursive 구조로 작성됨. 힙을 채우는 코드도 포함되어있어 한번 호출되면 힙과 스택을 한 칸씩 채운다. 그리고 스스로를 호출한다.
<br>commas	예제와 함께 주어진 함수. 긴 주소를 16진수로 줄여서 표현해준다. prepend, preprintf 마찬가지로 주어진 함수. commas함수에서 사용된다.
#### 결과

![](https://github.com/hwa10209/OS/blob/master/img/4_2.bmp)

> 컴파일 이후 프로그램에서 사용할 메모리 제한(8MB)를 변경한다.
<br>본 프로그램에선 unlimited 옵션을 사용하였다.

![](https://github.com/hwa10209/OS/blob/master/img/4_3.bmp)

> heap과 stack의 크기를 각각 5mb 공간을 이용하여 채워넣었다.
<br>stack은 높은 주소에서 낮은 주소, heap은 낮은 주소에서 높은 주소로 자동을 할당되었다.

![](https://github.com/hwa10209/OS/blob/master/img/4_4.bmp)

> 메모리 공간을 계속 할당받다보면 두 공간이 만나는 곳이 발생한다. 두 값이 1MB 언저리만큼 가까워진 후 충돌이 발생하였는지 heap의 주소가 확 줄어서 126,2410부터 다시 할당되기 시작했고, stack은 계속 할당되며 heap 영역을 덮어쓰는 현상이 발생했다. 

![](https://github.com/hwa10209/OS/blob/master/img/4_5.bmp)

> stack은 계속 줄어들고, heap은 커져서 결국 충돌이 다시 한번 발생했다. <br>그러자 프로그램이 종료되었다.

![](https://github.com/hwa10209/OS/blob/master/img/4_6.bmp)

> 할당시키는 메모리들을 크게 설정하여 충돌이 좀더 빨리 일어나게 설정해 보았다.<br>한정된 메모리 공간인 만큼 큰 공간을 할당받아 더 빨리 충돌하고 프로그램이 종료된다.

#### 고찰
> 메모리의 크기를 임의로 할당해 보면서 stack과 heap의 주소값의 변동을 관찰하였는데, 이를 통해 메모리가 구분된 stack, heap 영역 이 존재하고, (1)에서 heap의 주소가 0부터 시작하지 않았다는 점을 통해 heap 영역 이전에 또 다른 영역이 있다는 것을 확인 할 수 있다.<br>그리고 (3)과 (5)의 결과를 통해 stack, heap 영역이 할당받을 수 있는 공간을 서로 공유하고 있고 메모리 전체 공간을 유동적으로 쓸 수 있음을 확인했다. 다만 두 공간이 겹치면 충돌이 발생하여 프로그램이 정지하는데 그 충돌하는 지점과 tack, heap영역의 크기는 공간을 할당해 주는 방식에 따라 계속 달라진다. 예를 들어 (5)의 결과를 보면 메모리의 3383,0A40에서 충돌이 발생하였으니 대략 3000,0000 지점으로부터  7E83,0F80 까지는 stack, 3000,0000부터 0199,9410영역까지는 heap 영역이 된다. 크기는 각각 1256MB, 544MB가 된다.<br>그런데 (3)의 결과에서는 생각하던 것과 조금 다른 결과가 나왔다. 원래대로라면 충돌이 일어나자마자 프로그램이 종료되면서 멈춰야 하지만 heap은 거치지 않았던 곳을 방문하여 다시 할당 받기 시작했고, stack은 heap이 할당받았던 영역을 할당받는다. 그 후 한번 더 충돌하고 정지한다. 이는 stack과 heap을 번갈아 가며 할당하여 충돌이 한 영역을 증가시키는 과정에서만 발생한 것이 된게 아닌가 추측한다. 따라서 한영역을 미리 할당하여 고정해놓고 다른 영역을 늘려가며 충돌시켜 보는 쪽으로 공부를 더 해봐야겠다.<br>마지막으로 이러한 큰 공간을 한 프로그램(프로세스)에서 잡고 있는다면 다른 프로그램이 사용하려고 할 때 충돌이 발생 할 듯 하다. 따라서 미리 작은 공간을 가지고 할당-> 할당 해제를 하며 이용하는 편이 더 효율적일 것이다.

#### 참고자료
> 강의노트 Memory management chapter	

---
### 5. HW5
#### 개요
* 커널에서 모듈을 다뤄보고 메모리에 글자를 보내면 case 변경과 100자 초과 덮어쓰기 기능이 있는 간단한 디바이스 드라이버를 만들어 본다.

#### 다이어그램

![](https://github.com/hwa10209/OS/blob/master/img/5_1.bmp)

#### 함수에 대한 설명
* Device driver
> mydrv_open() 실행파일에서 장치파일을 열 때 커널에서 호출하는 함수<br>mydrv_release() 장치파일을 닫을 때 커널에서 호출하는 함수<br>mydrv_read() 실행파일에서 read함수 사용시 호출됨.  메모리에 저장된 값을 한 글자씩 읽어 실행파일로 전달함.<br>mydrv_write() 실행파일에서 write함수 사용시 호출됨.  메모리에 한글자씩 값을 저장한다. 메모리 공간에 번호를 지정해 두고 100글자가 넘어가면 100칸 앞으로 이동하여 덮어쓰기 기능을 구현해주었고 알파벳 입력 시 소문자는 대문자로, 대문자는 소문자로 저장해 주었다.<br>mydrv_init() 모듈 적재시 초기화 수행<br>mydrv_cleanup()모듈 제거 시 반환 작업 수행<br>read() 메모리에서 데이터를 읽어온다.

* 실행파일
>write() 메모리에 데이터를 저장한다.<br>

#### 결과

![](https://github.com/hwa10209/OS/blob/master/img/5_2.bmp)

> 먼저 디바이스 드라이버를 컴파일 하고 만들어진 모듈을 커널에 적재한다. 그리고 명령어를 입력하면 모듈이 적재되어있음을 확인 할 수 있다.  이 상태에서 실행파일을 컴파일 후 실행하면 메모리에 문자열을 전송할 수 있는데 10글자 짜리와 100글자 짜리로 선택을 할 수 있다. 프로그램이 실행되면서 디바이스 드라이버로 짧은 글이 한글자씩 넘어가고 그 글은 메모리에 저장된다. 그리고 그 값을 출력해보면 대문자는 소문자로, 소문자는 대문자로 바뀌어서 출력됨을 확인 할 수 있다.<br>
그리고 긴 100글자 이상의 글을 전송했을 때 초과된 길이만큼 처음부터 덮어쓰는 기능을 확인 해 보았으나 의도한 대로 구현되지 않았는데 일차적인 원인은 device 드라이버에서 문자의 위치를 가리키는 변수가 의도한 바와 같이 변하지 않았기 때문이고, 이유는 프로그램이 한번 실행된후 두 번째 실행에서 실행파일의 메모리는 초기화 되는 반면 이미 커널에 적재된 모듈은 초기화 되지 않기 때문임을 알 수 있다. 따라서 적재된 모듈을 한번 제거후 다시 적재시키고 실행하자 의도된 값이 나왔다.

#### 고찰
> 모듈프로그램, 디바이스 드라이버 프로그램을 처음 해보았기 때문에 이해하는데 조금 시간이 걸렸다. 특히 커널에 대한 프로그램을 짤 때 지금까지 익히 사용해 오던 stdio 헤더와 printf 함수, for문을 사용하지 못했던 점이 기억에 남는다. <br>실행파일에서 호출한 함수가 디바이스 드라이버를 통해 또다른 함수를 호출하고 메모리에 입력, 출력을 해보면서 장치와 운영체제 사이의 관계에 대한 이해도가 깊어졌고, 그 디바이스 드라이버를 조금씩 변경하여 새로운 기능을 만들어 보면서 흥미를 느껴, 나중에 또다른 장치에 대한 드라이버를 다뤄보고 싶은 생각이 들었다.

#### 참고자료
> 수업자료 2019OS12 Device management
