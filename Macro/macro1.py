import requests
from bs4 import BeautifulSoup
import winsound as ws
import time
from datetime import datetime


code = input('과목코드 10자리 입력(영어는 대문자로, 띄어쓰기 없이) :')
def beepsound():
    freq = 1500
    dur = 500
    ws.Beep(freq,dur)

def update():

    search_info ={ "lectReqCntEnq.search_open_yr_trm":'20202','lectReqCntEnq.search_subj_cde': code[:7],
                   'lectReqCntEnq.search_sub_class_cde': code[7:],'searchValue': code}
    #입력하였던 과목코드를 요청신호로 쓸 수 있게 편집
    session = requests.session()
    url_search = "http://my.knu.ac.kr/stpo/stpo/cour/lectReqCntEnq/list.action"
    
    #수강신청 인원을 확인할 수 있는 주소
    
    res = session.post(url_search, data=search_info)
    #post 형식으로 데이터를 요청
    res.raise_for_status()


# Web Page에서 데이터 추출 ----------------------------------------
    soup = BeautifulSoup(res.text, "html.parser")
    name = soup.select_one("td.subj_nm").get_text()
    
    #받아온 데이터에서 특정 id를 가지는 부분을 추출함
    
    maximum = soup.select_one("td.lect_quota").get_text()
    #수강정원 값 추출
    
    available = soup.select_one("td.lect_req_cnt").get_text()
    #신청인원 값 추출
    
    now = datetime.now()
    print("%s년 %s월 %s일 %s시 %s분 %s초" % (now.year, now.month, now.day, now.hour, now.minute,now.second))
    print(name+" : " + available)
    
    #현재시간 출력
    if available != maximum:
        for i in range(3):
            beepsound()
            #수강신청이 가능할 때 

for i in range(1000000000):
    try:
        update()
    except:
        print("오류발생")
