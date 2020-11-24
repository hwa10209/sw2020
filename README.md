# EECS462001 멀티미디어시스템개론 / 2020년 1학기 / 박순용

> 멀티미디어시스템개론 과목을 수강하며 수행한 과제들 입니다.

## 요약

> HW1(code x) : DSI (Display Serial Interface) 프로토콜<br>
HW2 : Error diffusion dithering 알고리즘 구현 
<br>HW3 : Laplacian filtering
<br>HW4 : DCT Lossy Compression

## 수행내용
### 1. HW1 : DSI (Display Serial Interface) 프로토콜
#### DSI 프로토콜 표준의 정의

> host processor와 display module 사이의 고속 시리얼 인터페이스로 디스플레이를 위한 규격이다. MIPI 물리 계층인 D-PHY를 사용하며, 이 인터페이스는 제조사들이 디스플레이를 만들 때 그것들을 집적시키고 성능을 높여주며 저전력, low EMI(electromagnetic interface)를 실현하게 해 줄뿐만 아리라 핀의 수를 줄여 다른 판매자들 간의 호환성을 향상시켜준다.<br>
DSI 프로토콜은 광범위하게 적용되어 있다. 그 예로 스마트폰, 태블릿, 노트북, 자동차, IOT, 웨어러블 기기 등이 있다.

![](https://github.com/hwa10209/Multimedia/blob/master/img/1_1.bmp)

> DSI 구성도
#### DSI의 종류

> DSI의 종류는 2가지가 있다.
* MIPI DSI )  MIPI D-PHY physical layer위에서 동작하는 인터페이스
* MIPI DSI-2 ) MIPI D-PHY와 C-PHY 모두에 확장성과 지원을 제공하는 미래형 고속 인터페이스

#### DSI와 물리계층 C-PHY, D-PHY 의 사용기술

* DSI
> 기본적으로 MIPI Display Command Set (MIPI DCS)를 사용한다. 최근에는 4K와 같은 고해상도 영상을 지원하기 위해서 VESA(Video Electronics Standards Association)의 DSC(Display Stream Compression) 를 채용하였다. 또 DSI에는 명령어 모드와 비디오 모드가 있는데, 명령어 모드는 디스플레이 모듈에 별도의 메모리가 있어서 버퍼 역할을 할 수 있고, 디스플레이 모듈 자체적으로 화면을 리프레쉬할 수 있다. 여기에서 명령어란 MIPI DCS 를 의미한다. 비디오 모드는 디스플레이 모듈에 별도의 메모리가 없고, 호스트 프로세서가 직접적으로 화면을 제어해야 한다. 

* D-PHY & C-PHY
> D-PHY는 2009년에 등장하였으며 클락 한 lane과 여러 줄의 data lane을 사용하는 simple source synchronous PHY 이다. 나온지 오래 되었고 시장에서 널리 쓰였기 때문에 특별한 기능은 없다.
<br>그리고 C-PHY는 2014년에 새로 나온 프로토콜로 D-PHY보다 다소 복잡한 구성을 가지며, 클락 신호가 data lane 에서 같이 흐르기 때문에 추가적인 클락 lane을 구성할 필요가 없다. 또한 C-PHY는 D-PHY와 다르게 인코딩된 데이터를 주고받기 때문에 더 높은 전송 속도를 가진다.
<br>그리고 lane만 충분하다면 C-PHY와 D-PHY를 필요에 맞게 혼합하여 사용할 수 있으며 심지어 이것은 따로 사용하는 것 보다 효율이 높다. 이는 C-PHY와 D-PHY가 호환성이 있기에 가능한 기술이다.

![](https://github.com/hwa10209/Multimedia/blob/master/img/1_2.bmp)
![](https://github.com/hwa10209/Multimedia/blob/master/img/1_3.bmp)

#### DSI의 버전별 스펙

![](https://github.com/hwa10209/Multimedia/blob/master/img/1_4.bmp)

> DSI와 DSI-2에서 사용하는 D-PHY 의 버전이 올라가면서 lane당 신호의 속도는 점점 빨라진다. v1.01에서 1.0Gbps/lane에서 시작해서 v1.1에선 1.5Gbps/lane, v1.2에선 2.5Gbps/lane, 2.0에 이르러선 4.5Gbps/lane에 이르렀다.

#### 현재 스마트폰이나 TV, 컴퓨터 등에서의 DSI 적용 사례

![](https://github.com/hwa10209/Multimedia/blob/master/img/1_5.bmp)

> FHD, WQHD, 4k에서 DSI 프로토콜을 사용한 것을 확인할 수 있다. 해상도가 높을수록 DSI에서 전송하는 데이터가 많아짐에 따라 레인의 수와 각 레인의 데이터 전송 속도도 증가하였다. 

---
### 2. HW2 : Error diffusion dithering 알고리즘 구현
#### 오차확산 디더링, 소스코드

> Error diffusion dithering을 Visual studio 환경에서 OpenCV를 이용하여 구현해 보았다. 먼저 lena.jpg 파일을 입력받고, gray level로 변환한다. 그 후 각 좌표에 대해서 p, error값을 찾아 사전에 주어진 가중치를 곱하는 방식으로 주변값을 반시계방향으로(left,leftdown,down,rightdown,right) 순서대로 구하였다. 이 과정에서 unsigned char 형태이므로 overflow에 주의한다. 그런 다음 출력의 픽셀들을 이진화 시켜 주었다. 그런데, 이 이진화 과정에서 OpenCV을 이용하여 픽셀당 하나의 비트만을 저장할 수 있는 기능이 없기 때문에 (1,0)대신 (255,0)으로 표현하였다. 마지막으로 출력되는 결과파일을 저장한다. 다음의 장에서 결과를 확인한다.

#### 실행 결과

![](https://github.com/hwa10209/Multimedia/blob/master/img/2_1.bmp)

> 왼쪽부터 순서대로 입력영상, gray lever 변환 영상, dithering 수행 영상이다. 사진을 작게 보았을 때엔 8bit와 1bit를 이용하여 표현하였을 때 큰 차이가 없는 것으로 보인다. 이는 하나의 비트만으로 다수의 비트를 사용하였을 때와 같은 효과를 낼 수 있다는 의미로 error diffusion dithering 방법이 적은 수의 비트로 영상을 표현하기에 매우 효과적이라 할 수 있다. 
<br>
다만 아래와 같이 dithering이 끝난 사진을 확대해서 보면 품질이 낮아지고, 자잘한 무늬들이 많이 생기는 등, 한 비트를 이용하여 영상을 표현하는 것에 대한 한계를 확인할 수 있다.
![](https://github.com/hwa10209/Multimedia/blob/master/img/2_2.bmp)

> 추가적으로, 앞에서 저장된 파일의 속성을 확인해보면 multi-channel image를 single-channel image로 변환하는 과정에서 영상을 표현하는 비트의 수가 실제로 떨어졌음을 확인해 볼 수 있다.

![](https://github.com/hwa10209/Multimedia/blob/master/img/2_3.bmp)
![](https://github.com/hwa10209/Multimedia/blob/master/img/2_4.bmp)

> 두 번째 입력 영상으로 지난 여름방학에 호미곶에 가서 직접 찍은 사진(hand.jpg) 을 이용하여 위와 같은 과정을 거쳐 보았다. 왼쪽 위부터 순서대로 입력 영상 - gray level 변환 - dithering 수행사진이다. 이 사진도 마찬가지로 graylevel 변환시에 비트수가 떨어졌고, dithering 수행 후 하나의 비트로 표현할 수 있게 되었지만 품질이 떨어진다.


![](https://github.com/hwa10209/Multimedia/blob/master/img/2_5.bmp)

#### 컬러영상의 오차확산 디더링, 소스코드

> 기본적으로 앞에서 사용한 것과 같은 알고리즘이 들어간다. 하지만 컬러영상을 gray level로 변환하는 과정이 없어지고, multi-channel을 single-channel로 split 하고, single-channel을 다시 multi-channel로 murge 하는 과정이 추가되었다. 

#### 실행 결과
![](https://github.com/hwa10209/Multimedia/blob/master/img/2_6.bmp)
> 이 코드를 수행한 결과가 아래에 등장한다. 컬러 영상을 split 하여 Blue, Green, Red에 대한 영상이 각각 나타났고, 컬러 영상이 single-channel로 나뉘자 단순히 밝기만 확인할 수 있는 gray level 영상처럼 보이게 되었다. 이는 밝기의 척도만 표현 가능한 single-channel 영상이 되었기에 당연한 현상이다. 그리고 육안으로 보았을 때 추출된 색 마다 밝기가 달랐는데 Red가 가장 밝았다. 
<br>이 후 각각의 3개의 영상을 위의 1.에서 수행한 것과 같이 각각 dithering을 수행 하고 OpenCV의 murge 함수를 이용하여 하나로 합치게 되었다. 그러자 기존의 24bit로 표현하던 컬러 영상을 3bit 만으로 표현할 수 있는 영상이 되었다. 1.의 결과와 마찬가지로 확대했을 때 다소 품질이 떨어지는 모습을 보였지만, 21bit에 해당되는 bit를 절약할 수 있어서 큰 의미를 가진다. 또한 이러한 split-> dithering -> murge 와 같은 과정을 응용한다면 3-channel 그 이상의 영상도 dithering이 가능해 질것이라 생각한다.

---
### 3. HW3 : Laplacian filtering
#### 과제 개요
> 수업에서 배운 Laplacian filtering 을 C/C++/Java/Python 중에서 구현한다.
구현할 알고리즘은 다음과 같은 순서를 가진다.
<br>1) 입력영상을read 한다.
<br>2) 영상을흑백으로변환한다.
<br>3) Gaussian smoothing 으로영상을blur 한다. (잡음도제거)
<br>4) Blur된영상에Laplacian filtering 적용한다.
<br>5) Edge를찾기위해Zero crossing 실행
<br>6) 결과를 파일로 저장한다. 
<br>입력되는 사진은 “lena.jpg”, “myface.jpg”, “road.jpg” 세 가지로, 각각의 사진에 대해 값을 1.0~5.0까지 변화시켜보면서 Gaussian smoothing, Laplacian filtering, Zero crossing을 수행하며 어떤 결과가 나오는지 확인해 본다.


![](https://github.com/hwa10209/Multimedia/blob/master/img/3_1.bmp)

#### 소스코드 설명 및 시행착오
> 먼저 영상을 읽어와서 graylevel로 변환한 뒤, Gaussian smoothing을 통해 잡음들을 제거해준다. 이 과정에서 Window size는 권장된 크기들의 중간 값인 (5,5) 를 사용하였다. 또한 Bluring을 수행할 때 sigma 값을 1.0 에서 5.0 까지 다르게 수행한 뒤, Laplacian filter을 통해 대략적인 선을 찾고, Zero crossing을 통해 남아있는 잡음들이 선으로 표현된 경우 그것들을 지워준다. 
<br>이 때 sigma 가 클수록 영상이 옅어지면서 잡음도 함께 옅어진다. 따라서 초반엔 잡음이 없어지기만 하면 무조건 좋을 것이라 판단하고 높은 sigma 값을 위주로 다음의 작업을 수행해 보았으나 결과는 그렇지 않았다. 숫자의 변화를 측정하여 선을 찾아내는 Laplacian filtering 특성상 잡음과 함께 최댓값도 같이 낮춰버리는 Bluring을 거치면서 찾아낸 edge도 흐려졌다. 이 후 zero crossing에서도 마찬가지였다. 따라서 단순히 잡음만 지우려면 sigma 값을 크게 하는 것이 좋겠지만, 출력되는 영상이 그만큼 흐려진다는 점을 고려하여 적당한 값을 지정해 주어야 한다.


![](https://github.com/hwa10209/Multimedia/blob/master/img/3_2.bmp)

> 물론 처음부터 이 결과를 찾을 순 없었다. 각종 함수를 사용하면서 입력되는 이미지의 형식에 주의해 주어야 했다. Laplacian filtering을 수행하면서 255이상의 결과가 나와 값이 짤리는 것을 방지하기 위해 16bit int 값을 사용하였고 이대로 이미지를 출력하면 양수부분이 나오는 만큼 음수 부분도 있어서 OpenCV에서 평균값을 잡아 출력을 해주어 회색의 이미지가 출력된다. 따라서 엣지 부분만을 강조하여 보기위해 절댓값을 취한 후 출력해줬다. 

![](https://github.com/hwa10209/Multimedia/blob/master/img/3_3.bmp)

> 그런 다음 이 영상을 "laplacian.convertTo(cvt_laplacian, CV_32FC1)"을 통해 float 형태로 전환해 주었다. zerocrossing함수를 사용하기 위해서 float형태를 사용하였고, 32bit가 아닐 경우 사진이 2개, 또는 4개로 붙어서 출력되므로 이 형식을 맞춰 주어야하 한다. 또한 zero crossing 이 음수->0->양수, 또는 양수->0->음수가 되는 지점을 찾아 잡음을 추가적으로 없애는 방법이라 Laplacian filtering 이후 마이너스 값도 사용하기 위해 convertScaleAbs을 수행하기 이전의 이미지를 사용한다. 
<br>여기서 Zerocrossing을 수행하게 된다면 오히려 Laplacian filtering만 수행한 영상보다 더 지저분한 결과가 나타난다. 이는 Zerocrossing을 수행하였음에도 불구하고 잡음이 상당히 진하고 많았기 때문인데 여기서 sigma 값을 10.0, 20.0과 같이 높여주면 잡음이 없어지는 대신 우리가 찾아야 할 선들도 옅게 흐려진다. 따라서 sigma 값은 낮은 값에서만 조정해 보고, zerocrossing의 threshold값을 20으로 높여주었다. 그렇게 하자 남아있던 잡음이 추가적으로 걸러져 원하던 결과가 출력되었다.

![](https://github.com/hwa10209/Multimedia/blob/master/img/3_4.bmp)

> 이렇게 정해진 소스코드를 통해 sigma 값을 변경해 보면서 3개의 이미지에 대한 결과를 출력해 보았다.

#### 실행 결과


![](https://github.com/hwa10209/Multimedia/blob/master/img/3_5.bmp)
![](https://github.com/hwa10209/Multimedia/blob/master/img/3_6.bmp)

> threshold 값을 20으로 해 주었고, sigma 값을 증가시킬수록 잡음이 사라지는 동시에 레나의 얼굴도 같이 점점 흐려졌다. 추가로 sigma 값 뿐만 아니라 threshold 값도 하나의 변수로 보고 2개의 변수를 바꿔가며 최적의 출력영상을 찾을 수만 있다면 번거롭더라도 좋은 결과가 나올 수 있을 것 같다. 시간이 많이 소모될 듯 하여 시도해 보지는 못했다.


![](https://github.com/hwa10209/Multimedia/blob/master/img/3_7.bmp)

> threshold 값을 20으로 지정, sigma에 따라 흐려지는 정도가 lena.jpg보다 심한 것 같아 이를 사진의 크기가 작은 것이기 때문이라 보고, bluring을 수행하는 window의 사이즈를(3,3)으로 낮추고 과정을 재 수행하자 조금 나아졌다. window 크기가 작아서 그런지 sigma값에 따른 출력의 변화가 작아졌다. 



![](https://github.com/hwa10209/Multimedia/blob/master/img/3_8.bmp)

> window의 사이즈를(5,5)에 처음엔 threshold 값을 20으로 하자 유독 잡음이 심하여 40으로 두고 과정을 수행했다. 그러자 sigma가 1일 때 에는 만족스러운 결과가 나왔으나 simga 값이 커질수록 edge를 찾아내는 정도가 줄어들어 깨끗한 숫자와 도로가 보이지 않는다. 물론 잡음은 줄어들지만 다른 사진은 제쳐두고, 이 사진의 경우 단순히 sigma만 높이는 것은 좋은 방법은 아닌 것 같다.


---
### 4. HW4 : DCT Lossy Compression
#### 개요

> 수업에서 배운 DCT Lossy Compression  을 C/C++/Java/Python 중에서 구현한다.
구현할 알고리즘은 다음과 같은 순서를 가진다.
<br>1) 2D DCT에 사용될 8x8 DCT basis를 구한다. (전체64개) 
<br>2) 입력영상을read 하여graylevel로 변환한다. 
<br>3) 영상의8x8 영역(block)에 대하여f(i,j)를 8x8 DCT basis를 이용하여8x8 주파수공간 F(u,v)로 변환한다. 
<br>4) F(u,v)를 다시 IDCT로8x8 영상을 다시 복원한다. 이때, F(u,v)의8x8, 4x4, 2x2 값들만 사용하여 비교
<br>5) 영상 전체에 대하여 3)-4) 과정을 반복한다. 
<br>6) 입력1장 영상에 대하여 복원된 영상3장을 각각 저장한다.

<br>입력되는 사진은 “lena.jpg”, “cup.jpg” 두 가지로, 각각의 사진에 대해 . 영상이 복원되는 정도를 다르게 하여 출력하여 본다.
>

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_1.bmp)

#### 실행 결과
> 1)테스트 영상
<br>“lena.jpg", 512X512, 67.5KB
<br>"cup.jpg", 288X512, 44.1KB
<br>2)각 test 영상마다 3개의 f(i,j) 복원 결과
<br>DCT->IDCT를 거치는 과정에서 F(u,v)를 조금만 사용할수록 영상이 많이 압축되었다. 8X8을 전부 사용하는 경우에는 영상이 원본과 차이가 없고 opencv특성인지 용량이 오히려 조금 증가했다. 4X4를 사용하였을 때에는 조금 흐려지긴 하지만 사실 육안으로 보기에는 달라진 점을 크게 느낄 순 없다. 영상에 처음부터 포함되어 있는 고주파 성분이 적기 때문이고, 용량은 줄어든 것을 확인 할 수 있다. 2X2를 사용하면 영상품질이 많이 훼손되고 그만큼 용량도 대폭 감소한다.


![](https://github.com/hwa10209/Multimedia/blob/master/img/4_2.bmp)

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_3.bmp)

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_4.bmp)

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_5.bmp)

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_6.bmp)

> (u,v) 가 (0,0)일 때 에는 직류성분만 존재하기 때문에 값이 모두 같다. 또한 u값만 증가 하고, v값은 모두 0이라 위의 다른 좌표들에 대한 성분들이 좌우로만 값이 바뀌고 위아래로 값이 바뀌지 않는 모습을 볼 수 있다. 그리고 u값이 증가할수록 고주파 성분이 많아지기 때문에 처음에는 좌우로 값의 변화가 작다가 점점 변화가 커진다. 

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_7.bmp)
> 정상적인 DCT 값

![](https://github.com/hwa10209/Multimedia/blob/master/img/4_8.bmp)
> 정상적으로 DCT가 수행되었다. 주어진 예시와 거의 같은 결과가 나온다. 반올림 여부, 표시하는 칸의 크기에 따라서 미세한 값이 차이가 나는 것으로 보인다. 
