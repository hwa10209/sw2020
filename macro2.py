import requests
from bs4 import BeautifulSoup
import winsound as ws
import time

from selenium import webdriver
import clipboard
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.alert import Alert

std = input('학번 입력 :')
id = input('ID 입력 :')
pw = input('PW 입력 :')
print("수강꾸러미에 있는 순서대로 과목코드 입력")
print("7개 까지 입력 받음(순서 중요, 같아야 신청이 됨),"
      "없거나 수강꾸러미에 있어도 신청하지 않을 과목은 0 입력")

code0 = [ '0',input('과목코드1 :')]
code1 = [ '1',input('과목코드2 :')]
code2 = [ '2',input('과목코드3 :')]
code3 = [ '3',input('과목코드4 :')]
code4 = [ '4',input('과목코드5 :')]
code5 = [ '5',input('과목코드6 :')]
code6 = [ '6',input('과목코드7 :')]
codelist= [code0,code1,code2,code3,code4,code5,code6]
url_sugang = 'https://sugang.knu.ac.kr/'

driver = webdriver.Chrome('./chromedriver')
#같은 경로에 설치되어 있는 크롬드라이버를 실행, 크롬 창 생성
driver.implicitly_wait(5)
session = requests.session()


def alert():
    try:
        da = Alert(driver)
        da.accept()
    except:
        "There is no alert"


def login():
    driver.get(url_sugang)
    #수강신청 사이트로 이동

    clipboard.copy(std)
    driver.find_element_by_xpath('//*[@id="user.stu_nbr"]').click()
    #학번 칸 클릭

    #입력한 학번이 학번 칸에 입력 됨(코드 지움)

    clipboard.copy(id)
    driver.find_element_by_xpath('//*[@id="user.usr_id"]').click()
    #아이디 칸 클릭


    # 입력한 아이디가 아이디 칸에 입력 됨(코드 지움)

    clipboard.copy(pw)
    driver.find_element_by_xpath('//*[@id="user.passwd"]').click()
    #비밀번호 칸 클릭

    #입력한 비밀번호가 비밀번호 칸에 입력 됨(코드 지움)

    driver.find_element_by_xpath('//*[@id="loginForm"]/table/tbody/tr[4]/td/button[1]').click()
    #로그인 버튼 클릭


def apply(i):
    try:
        driver.find_element_by_xpath('//*[@id="lectPackReqGrid_' + str(i) + '"]/td[11]/a').click()
        #수강꾸러미에 있는 과목이 신청이 가능해 졌을 때 수강신청 버튼 클릭
        alert()
        #신청 되었음을 알림
    except:
        print("오류발생")


def beepsound():
    #스피커로 삡- 소리내기
    freq = 1500
    dur = 500
    ws.Beep(freq, dur)

def check(list):
    code=list[1]
    search_info ={ "lectReqCntEnq.search_open_yr_trm":'20202','lectReqCntEnq.search_subj_cde': code[:7],
                   'lectReqCntEnq.search_sub_class_cde': code[7:],'searchValue': code}
    url_search = "http://my.knu.ac.kr/stpo/stpo/cour/lectReqCntEnq/list.action"
    #수강신청 인원 확인사이트
    res = session.post(url_search, data=search_info)
    #수강꾸러미에 있는 과목코드로 위 사이트에서 검색
    res.raise_for_status()

# Web Page에서 데이터 추출 ----------------------------------------
    soup = BeautifulSoup(res.text, "html.parser")
    #검색 결과 parsing
    name = soup.select_one("td.subj_nm").get_text()
    maximum = soup.select_one("td.lect_quota").get_text()
    availablen = soup.select_one("td.lect_req_cnt").get_text()

    print(name+" : " + availablen)

    if availablen != maximum:
        apply(list[0])
        beepsound()
    #검색한 과목의 수강인원과 현재 신청인원이 다를때, 수강신청 가능함
    #이 경우 알림음과 함께 신청 함수로 진입


login()
#최초 1회 로그인
starttime=time.time()
#현재 시간 저장
for a in range(10000000):

    time_now = time.time() - starttime
    #흐른 시간 확인
    print("%s 초 후 로그아웃" % str(round(1190-time_now,2)))
    if time_now > 1190 :
        #30분이 지나기 직전에
        starttime = time.time()
        try:
            driver.quit()
            #크롬 창 종료
            time.sleep(1)
            driver = webdriver.Chrome('./chromedriver')
            driver.implicitly_wait(5)
            #재접속
            login()
            #로그인
            session = requests.session()

        except:
            beepsound()
            beepsound()
            print("종료됨")
    try:
        for z in range(7) :
            if codelist[z][1] !='0':
                check(codelist[z])
                #제대로 된 과목코드일 때 그 과목코드로 수강신청가능 여부 확인 -> 신청
    except:
        print("오류발생")
