# 수강신청매크로 / 2020년 여름방학

> 수강신청인원 확인용 프로그램과 이를 응용한 자동 수강신청 매크로를 제작해 보았습니다.
<br>PyCharm IDE를 이용하였고 파이썬으로 작성하였습니다.
<br>
<br> 학술적인 목적으로 기능의 정상동작 여부를 확인하는 정도로만 이용하였으며, 
<br> 다른 학우들에게 피해를 주기 싫었기에 이 매크로를 개인의 이익을 위해 이용하지는 않았습니다.
<br> 몇 몇 코드는 지워서 업로드 하였습니다.

## 개요

> 각종 커뮤니티를 통해 강의 매매가 일어나고 있으며 이 때문에 정상적으로 수강신청을 하는 사람들이 피해를 보는 사실을 확인하였다.
<br> 이에 부당함을 느꼈고, 이를 직접 극복하는 자세를 기르기 위해 방학기간동안 직접 파이썬을 공부하여 매크로를 만들어 보았다.

* macro1
> 알고싶은 과목의 현재신청 인원을 지속적으로 알려주는 프로그램

* macro2
> macro1의 응용버전. 아이디와 학번, 비밀번호를 입력하면 수강꾸러미에 담긴 과목이 신청가능 할 때 신청해주는 프로그램

## 상세내용
### macro1

![](https://github.com/hwa10209/Macro/blob/master/img/1_1.PNG)

> 알고싶은 과목의 과목코드를 입력한다.


![](https://github.com/hwa10209/Macro/blob/master/img/1_2.PNG)

> 1초 미만의 주기로 현재신청인원을 크롤링 해온다.
<br>만약 수강정원과 현재 신청인원이 다를경우 알림음을 내어 이용자가 재빨리 신청 버튼을 누를 수 있게 한다.

[소스코드와 설명](https://github.com/hwa10209/Macro/blob/master/macro1.py)

### macro2

> 수강신청 여부를 파악 후에 자동으로 신청하는 기능을 구현하기 위해서는 실제 크롬창을 띄워서 이용자가 직접 조작하는것과 같게 동작시켜주는 셀레니움을 이용해야함

![](https://github.com/hwa10209/Macro/blob/master/img/2_4.PNG)


> 크롬창 > 설정 > 도움말 > 크롬 정보 탭에서 내 크롬 버전 확인

> https://chromedriver.chromium.org/downloads 에서 내 버전에 맞는 크롬드라이버를 다운로드 후 코드와 같은 경로에 둠

![](https://github.com/hwa10209/Macro/blob/master/img/2_1.PNG)

> 학번, 아이디, 내 수강꾸러미에 있는 과목의 코드를 입력

![](https://github.com/hwa10209/Macro/blob/master/img/2_2.PNG)

![](https://github.com/hwa10209/Macro/blob/master/img/2_3.png)

> 입력이 완료되면 자동으로 제어되는 크롬창이 뜨고 로그인이 완료됨
<br>성공적으로 로그인 후, 수강꾸러미에 있는 과목의 신청가능 인원 수를 지속적으로 파악하고 자리가 비면 자동으로 신청 됨
<br>30분이 지나 로그아웃 되기 전에 크롬창이 종료되고 새 창이 뜬 다음, 로그인 후 위의 과정이 반복 됨

[소스코드와 설명](https://github.com/hwa10209/Macro/blob/master/macro2.py)
