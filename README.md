# COMP312001 운영체제 / 2019년 1학기 / 강순주

운영체제 과목을 수강하며 수행한 과제들 입니다.

## 수행내용
### 1. HW1


#### 개요
* 지난 학기의 자료구조에서 배운내용을 운영체제 1,2주차 강의를 들으며 복습하면서		 
실습환경-리눅스(우분투)을 구축해보고 실제로 STACK과 QUEUE를 구현해 본다.


#### 함수에 대한 설명
create_stack()	stack 생성 및 stack 내부 설정

push(STACK* stack, void* in) stack주소, 데이터 입력후 그에대한 stack의 노드를 push

pop(STACK* stack) stack에 저장된 노드를 pop

playstack()	stack의 동작을 선택하고 볼 수 있는 함수

CreateQueue()	queue 생성 및 queue 내부 설정

Enqueue(QUEUE* pQueue, void* item) queue주소, 데이터 입력후 그에 대한 queue의 노드를 enque

Dequeue(QUEUE* pQueue) queue에 저장된 노드를 dequeue

playqueue()	queue의 동작을 선택하고 볼 수 있는 함수
#### 2. HW2

* fork 함수와 exec 함수를 이용하여 나만의 쉘을 만들어 봄으로써 멀티프로세스를 구현해 본다.

#### 3. HW3

* pthread를 이용하며 우연히 발생하는 critical section 문제를 확인하고 해결해 본다.
*	matrix의 계산을 single / multi processor를 이용하여 수행해보고 수행시간을 비교해본다.

#### 4. HW4

* 운영체제의 기능중 하나인 memory management, stack과 heap이 관리되는 모습을 		확인한다.
임의의 메모리 할당을 통해 메모리의 stack, heap 영역이 충돌하는 현상을 구현

#### 5. HW5

* 커널에서 모듈을 다뤄보고 메모리에 글자를 보내면 case 변경과 100자 초과 덮어쓰기 기능이 있는 간단한 디바이스 드라이버를 만들어 본다.
