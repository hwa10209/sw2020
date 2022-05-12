


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Lmotor = AFMS.getMotor(1);
Adafruit_DCMotor *Rmotor = AFMS.getMotor(4);

//@@@@@@@                      라인트레이서 튜닝/환경설정                          @@@@@@@@@@@@@@@//


const int SensingTerm1 = 3   ;//검은선 판별 주기 (milliseconds)    

const int SensingTerm2  = 15  ;//거리측정 주기(milliseconds)


const int ServoTerm   = 30  ;//서보모터 동작 주기 (milliseconds)
const int AngleSize   = 66  ;//서보모터 전체 회전 각도의 절반
const int Singledeg   = 30   ;//서보모터 한번움직이는 각도
const int CenterServoDeg = 90 ;//서보모터 중앙각도 값

const int Speed =70      ;//라인트레이서 주행, 회전속도
const int optionSpeed=60;
//@@@@@@@                      코드에 사용될 변수와 상수들                         @@@@@@@@@@@@@@@//
const int BlackLine = 1;
const int White = 0;

static int LineOne  = 0;
static int LineTwo  = 0;
static int LineThree= 0;
static int LineFour = 0;
static int LastLine=1;    //제일 처음 장애물 발견시 회전방향, 1,2 : 오른쪽, 3,4 : 왼쪽

static int BlockIs=0;
const int Close = 1;
const int Far = 0;

volatile int pos;


//@@@@@@@                      함수 프로토 타입                         @@@@@@@@@@@@@@@//

void Stop();
void Forward();
void Backward();
void Right(int degree);
void Left(int degree);
void FindDir();
void FinishCheck();
Servo servo;


//@@@@@@@                     멀티태스킹 구현, 객체                        @@@@@@@@@@@@@@@//
//적외선 센서 객체
class IRsensor
{
  int ReadApin1;
  int ReadApin2;
  int ReadApin3;
  int ReadApin4;
  int WriteDpin1;
  int WriteDpin2;
  int WriteDpin3;
  int WriteDpin4;
  long IRTerm;
  
  volatile int LineValue1;
  volatile int LineValue2;
  volatile int LineValue3;
  volatile int LineValue4;

  
  volatile unsigned long previousIRMillis;

  public:
  IRsensor(int Dpin1,int Dpin2,int Dpin3,int Dpin4, int Apin1,int Apin2,int Apin3,int Apin4, long SensingTerm)
  {
    ReadApin1 = Apin1;
    ReadApin2 = Apin2;
    ReadApin3 = Apin3;
    ReadApin4 = Apin4;
    WriteDpin1 = Dpin1;
    WriteDpin2 = Dpin2;
    WriteDpin3 = Dpin3;
    WriteDpin4 = Dpin4;
    IRTerm = SensingTerm ;
    LineValue1 = 0;
    LineValue2 = 0;    
    LineValue3 = 0;
    LineValue4 = 0;
    
    
    pinMode(WriteDpin1, OUTPUT);
    pinMode(WriteDpin2, OUTPUT);
    pinMode(WriteDpin3, OUTPUT);
    pinMode(WriteDpin4, OUTPUT);
    previousIRMillis = 0;
  }

  void Update(unsigned long currentMillis)
  {
    if(currentMillis-previousIRMillis>=IRTerm)
    {
      previousIRMillis = currentMillis;
      digitalWrite(WriteDpin1,HIGH);
      digitalWrite(WriteDpin2,HIGH);
      digitalWrite(WriteDpin3,HIGH);
      digitalWrite(WriteDpin4,HIGH);
      delayMicroseconds(500);
      LineValue1= analogRead(ReadApin1);
      LineValue2= analogRead(ReadApin2);
      LineValue3= analogRead(ReadApin3);
      LineValue4= analogRead(ReadApin4);
      digitalWrite(WriteDpin1,LOW);
      digitalWrite(WriteDpin2,LOW);
      digitalWrite(WriteDpin3,LOW);
      digitalWrite(WriteDpin4,LOW);
      
      //delayMicroseconds(500);
      //조금이라도 빠른 선 판별을 위해 delay를 줄임
      //멀티태스킹이라 따로 시간을 두지 않아도 다른 일을 하는동안 충분히 시간을 줌

      delayMicroseconds(100);


      
    LineOne = (LineValue1>750  ) ?  BlackLine : White;
    LineTwo = (LineValue2>750  ) ?  BlackLine : White;
    LineThree = (LineValue3>700) ?  BlackLine : White;
    LineFour = (LineValue4>700 ) ?  BlackLine : White;

   
    }
   
  }
};

//초음파센서 객체
class Sonar
{
  long Duration;
  volatile float Distance;
  int TrigPin;
  int EchoPin;
  long STerm;
  volatile unsigned long previousSMillis;

  public:
  Sonar(int Tpin, int Epin, long SensingTerm)
  {
    TrigPin = Tpin;
    EchoPin = Epin;
    STerm = SensingTerm;
    Distance = 50;
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    previousSMillis = 0;
  }
  void Update(unsigned long currentMillis)
  {
    if(currentMillis-previousSMillis>=STerm)
    { 
      previousSMillis = currentMillis;
      digitalWrite(TrigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(TrigPin, LOW);
      Duration = pulseIn(EchoPin, HIGH);
      Distance= Duration*0.034/2;
      
      Serial.println(Distance);
   
      if(Distance<=2)
         BlockIs= Far;
       else if(Distance<=25)
         BlockIs= Close; 
       else
        BlockIs= Far;

 
    }
    
  }
  float getDistance()
  { return Distance;}
};

//서보모터 객체
class ServoMoter
{
  
  
  long VTerm;
  int AngleSizeEach;
  volatile unsigned long previousVMillis;
  volatile int Increment;

public:
  ServoMoter( int Term, int AngleSize, int Singledeg)
  {
   
    pos=CenterServoDeg-AngleSizeEach;
    VTerm = Term;
    AngleSizeEach = AngleSize;
    Increment = Singledeg;
    pos = CenterServoDeg-AngleSize;
    previousVMillis = 0;
  }
  void Update(unsigned long currentMillis)
  {
 
    if((currentMillis - previousVMillis) > VTerm)
    {
      previousVMillis = currentMillis;
      pos += Increment;
      servo.write(pos);
      if((pos>=CenterServoDeg+AngleSizeEach)|| (pos<=CenterServoDeg-AngleSizeEach))
        Increment = -Increment;
    }
  }
};


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//@@@@@@@                     멀티태스킹 구현, 객체선언                     @@@@@@@@@@@@@@@//
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

IRsensor IRsensors(3,6,2,5,1,2,3,5,SensingTerm1);           //핀을 바꿔 꽂을 때 마다 핀 번호 수정필요.
//IRsensor(Dpin1, Dpin2, Dpin3, Dpin4, Apin1, Apin2, Apin3, Apin4, SensingTerm)
  
Sonar Sonarsensor(11,7,SensingTerm2);                       //핀을 바꿔 꽂을 때 마다 핀 번호 수정필요.
//Sonar(Trigerpin,EchopinSensingTerm)
  
ServoMoter VMoter(ServoTerm,AngleSize,Singledeg);
//ServoMoter(Servo rotating Term, TotalAngleSize, SingleRotate degree)

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//@@@@@@@                            동작시작                            @@@@@@@@@@@@@@@//
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

  
void setup()
{
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
  AFMS.begin();

  Rmotor->setSpeed(Speed);
  Lmotor->setSpeed(Speed);
  servo.attach(9);

  //초기에 이상한 값이 남아있는 경우가 있어서 시험 동작을 하면서센서 값들을 먼저 초기화 해줌
  for(int i=0; i<10; i++)
  {
    IRsensors.Update(millis());
    Sonarsensor.Update(millis());
    delay(10);
  }
 
}

void loop() {
  //최적화된 멀티 태스킹 순서, 선을 먼저 판별하고 서보모터 회전, 그리고 장애물 판별 
  //달리는 동안 틈틈히 수행됨 
  IRsensors.Update(millis());
  VMoter.Update(millis());
  Sonarsensor.Update(millis());
 
   //검은선 회피용 코드
   //한번 선을 발견하면 회전 후 그 선으로 좀더 가까워지도록 달린다, 버뮤다지역을 탈출하기위해 일부러 삐딱하게 달림
   if(LineTwo) {Left(30);Forward();for(int i=0;i<100;i++)millis();Backward();Right(65);          LastLine= 2;  }
   else if(LineThree){Right(30);Forward();for(int i=0;i<100;i++)millis();Backward();;Right(75);     LastLine= 3; }
   else if(LineOne) {Left(50);Forward();for(int i=0;i<100;i++)millis();Backward();Right(65);        LastLine = 1;  }
   else if(LineFour) {Right(50);Forward();for(int i=0;i<100;i++)millis();Backward();Right(75);      LastLine = 4;  }
   else
   Forward();

 


   if(BlockIs != Far){
    
    FindDir();		//작은 컵이 앞에 있는지는 알 수 없다. 하지만 큰 컵이 나오면 회피한다.
   }
      
                         
}

 
 

//좌회전용  
void Left(int degree){
  Rmotor->setSpeed(optionSpeed);
  Lmotor->setSpeed(optionSpeed);
  
    Rmotor->run(FORWARD);
    Lmotor->run(BACKWARD);
    delay(8*degree);

  Lmotor->run(FORWARD);
  Rmotor->run(BACKWARD);
  delay(2);    
  Rmotor->run(RELEASE);
  Lmotor->run(RELEASE);
  Rmotor->setSpeed(Speed);
  Lmotor->setSpeed(Speed);
  
}

//우회전
void Right(int degree){
  Rmotor->setSpeed(optionSpeed);
  Lmotor->setSpeed(optionSpeed);
  
    Lmotor->run(FORWARD);
    Rmotor->run(BACKWARD);
    delay(8*degree);

    Rmotor->run(FORWARD);
    Lmotor->run(BACKWARD);
    delay(2);
    Lmotor->run(RELEASE);
    Rmotor->run(RELEASE);
  Rmotor->setSpeed(Speed);
  Lmotor->setSpeed(Speed);
    
}

 


//회피방향과 각도 설정
void FindDir(){
  Lmotor->run(BACKWARD);
  Rmotor->run(BACKWARD);
  delay(200);
  Lmotor->run(RELEASE);
  Rmotor->run(RELEASE);

  if(pos>=CenterServoDeg){
     if(LastLine == 1 | LastLine == 2)                  
    {Right(45); LastLine=3;}
   else if( LastLine == 3 | LastLine == 4)
    {Left(55); LastLine=1;}
   }
  else{
  if(LastLine == 1 | LastLine == 2)  
   { Right(45); LastLine=3;}
    else if( LastLine == 3 | LastLine == 4)
    { Left(55); LastLine=1;}
  }
}
//일시정지
void Stop(){
    Lmotor->run(RELEASE);
    Rmotor->run(RELEASE);
}
//직진
void Forward(){
  
  Rmotor->run(FORWARD);
  Lmotor->run(FORWARD);


}
//후진
void Backward(){
  Rmotor->setSpeed(optionSpeed);
  Lmotor->setSpeed(optionSpeed);
  
  Lmotor->run(BACKWARD);
  Rmotor->run(BACKWARD);
  delay(700);
  Lmotor->run(RELEASE);
  Rmotor->run(RELEASE);

  Rmotor->setSpeed(Speed);
  Lmotor->setSpeed(Speed);
  

}
