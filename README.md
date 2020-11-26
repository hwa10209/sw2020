# EECS302001 전자공학설계실험A / 2019년 2학기 / 김영모

> 전자공학설계실험A 과목을 수강하며 수행한 프로젝트입니다.
<br>아두이노 ide 환경에서 구현하였고 C언어를 이용하였습니다.


## 요약

> Game1 주어진 환경을 자율주행하는 미니카<br>
Game2 큰 사물을 제거하는 미니카
<br>Game3 작은 사물을 제거하는 미니카

## 수행내용
### 1. Game 1 : 주어진 환경을 자율주행하는 미니카 만들기

#### 센서
> 주행 환경을 구분하고 작업을 수행하기 위한 센서로 적외선 센서와 초음파 센서를 사용하였다.
주행 환경이 자세하게 주어지지 않았고 임의의 환경에 대해서 적응이 가능한 구조였기 때문에 기존의 적외선센서를 분해하였고,
전자회로에서 배운 지식을 이용하여 새로운 적외선 센서 모듈을 제작하여 이용하였다.

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_1.png)
![](https://github.com/hwa10209/ElectricA/blob/master/img/1_2.png)

> 확실한 환경 구분을 위해 4개의 모듈을 제작하였다.

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_3.png)

> 제작한 적외선 센서로 센싱 테스트 수행

#### 바디

> 제공받은 부품을 이용하여 미니카의 바디가 될 부분을 제작하였다. 
주요 몸체는 나무합판을 이용하였고, 구동부는 고무,플라스틱 바퀴와 DC모터를 이용하였다.
그리고 제어부는 아두이노와 모터드라이버를 이용하였다.

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_5.png)

> 적외선 센서의 위치를 변경하기 쉬운 구조가 필요했다.
방법을 고민하던 중 레이저 커팅기를 이용하여 직접 합판을 잘라 만드는 방법을 알게되어 사용법을 학습 후 이용하였다.

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_6.png)

#### 회로

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_8.png)

> 아두이노와 센서, 모터드라이버, 배터리와 모터를 연결하였다.
제작하는 과정에서 불량인 pin이 있어서 코드를 짜면서 pin번호가 몇 개는 수정되었다.

#### 하드웨어 완성

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_7.png)

> 전면부에 적외선 센서 모듈과 초음파 센서를 부착하였고, 찍찍이를 이용하여 적외선 센서의 높이는 변경가능하도록 하였다.

#### 경기

![](https://github.com/hwa10209/ElectricA/blob/master/img/1_9.png)

> 다음과 같은 환경에서 경기를 하였다. 빠른 시간 내에 도로 를 왕복하는 팀이 승리. 
주행 중에 장애물에 부딪히면 감점되고, 출발 지점으로 돌아오면 벽을 감지하고 정지하여야 한다.

[경기영상](https://blog.naver.com/hn03055/221729272428)

---

### 2. Game 2 : 큰 사물을 제거하는 미니카

#### 경기

> Game 1 수행 후에 기존의 하드웨어를 유지한 채로 코드를 변경하여 크기가 큰 종이컵을 제거하는 경기를 지행하였다


![](https://github.com/hwa10209/ElectricA/blob/master/img/2_1.png)
![](https://github.com/hwa10209/ElectricA/blob/master/img/2_2.png)

[경기영상](https://blog.naver.com/hn03055/221729338896)

---

### 3. Game 3 : 큰 사물을 제거하는 미니카

#### 경기

> Game 2 수행 후에 기존의 크기가 작은 종이컵을 제거하는 경기 진행. 종이컵의 크기를 구분하기 위해 하단의 적외선 센서의 용도를 변경하여 컵 구분에 이용하였다.

![](https://github.com/hwa10209/ElectricA/blob/master/img/3_1.png)
![](https://github.com/hwa10209/ElectricA/blob/master/img/3_2.png)
