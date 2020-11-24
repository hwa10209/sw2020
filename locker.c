 /*---------------------------------------------------------
 *                     라이브러리
----------------------------------------------------------*/
#include "Firebase_Arduino_WiFiNINA.h"
#include <SPI.h>
#include <MFRC522.h>

#include <FreeRTOS_SAMD21.h>
#include <Servo.h>

#define FIREBASE_HOST " "
#define FIREBASE_AUTH " "
#define WIFI_SSID " "
#define WIFI_PASSWORD " "
/*---------------------------------------------------------
 *                     핀 번호, 상수
----------------------------------------------------------*/
const uint8_t RST_PIN = 9;           
const uint8_t SS_PIN = 10;
const uint8_t I_PIN = A0;
const uint8_t MOTOR_PIN = 8;
const uint8_t Buzzer_PIN = 7;

const int exist = 1, empty = 0;
const int closed = 1, opened = 0;
const int locked = 1, unlocked = 0;

const int door_threshold = 100;                //적외선센서 임곗값
const int locked_pos = 60, unlocked_pos = 170; //서보모터 각도

/*---------------------------------------------------------
 *                     보관함 상태, 사용 변수
----------------------------------------------------------*/
uint8_t buf[10]= {};
MFRC522::Uid id;
MFRC522::Uid id2;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
Servo bolt;
FirebaseData firebaseData;

int rfidState = 0;                  //RFID 센서(보유)
int doorState = 0;                  //적외선센서(닫힘)
int boltState = 0;                  //잠금장치(잠금)

int lastState; 
int lockerState = 4;                //1~5 상태 - 보유여부, 닫힘여부, 잠금여부
                                    //대여 대기     - 1 1 1
                                    //열림 대기     - 1 1 0
                                    //수령&닫기 대기 - 1 0 0
                                    //넣기*닫기 대기 - 0 0 0
                                    //반납 대기     - 0 1 0
                                    
String myLockerKey = "0";                //보관함 키
String myLocationKey = "location1";           //장소 키
String myRfidKey = "";                  //rfid 저장 변수
String myRollerKey = "";
String userKey = "";

String myPath = "Rental Requests/";
String myJson ="";

uint8_t control = 0x00;
int t = 0;

/*---------------------------------------------------------
 *                     프로토타입
----------------------------------------------------------*/
static void Thread1_main(void* arg);
static void Thread2_checkCard(void* arg);

void cpid(MFRC522::Uid *id);
void printDec(byte *buffer, byte bufferSize);
void printState();
void irCheck();
/*---------------------------------------------------------
 *                     메인코드
----------------------------------------------------------*/ 
void setup(){
  portBASE_TYPE s1, s2;
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  
  Serial.begin(115200);
  delay(100);
  Serial.println();

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Provide the autntication data
  
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH,WIFI_SSID, WIFI_PASSWORD);
  
  
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();
  pinMode(I_PIN,INPUT); 
  bolt.attach(MOTOR_PIN);
  bolt.write(unlocked_pos);
  delay(1000);
  
  s1 = xTaskCreate(Thread1_main,    NULL, 700, NULL, 2, NULL); // Thread 생성
  s2 = xTaskCreate(Thread2_checkCard, NULL, 100, NULL, 1, NULL); 

  Serial.println("task start");
  vTaskStartScheduler();  // 태스크 스케쥴러 시작, 멀티태스킹 시작
  Serial.println(F("Insufficient RAM"));
  while(1);
}

 
void loop(){}
/*---------------------------------------------------------
 *                     태스크 설명
----------------------------------------------------------*/
static void Thread1_main(void* arg) {
  while (1) {
    checkState();
    switch(lockerState){
      case(1): // 대여 대기 상태
        
        vTaskDelay(100);  //myRfidKey
        
        Serial.print("path = : ");Serial.println(myPath);

        if(Firebase.getJSON(firebaseData ,myPath)) // 요청 들어옴
        {     
          Serial.println(firebaseData.jsonData());
          vTaskDelay(500);
          bolt.write(unlocked_pos);
          boltState = unlocked;

          if(Firebase.getString(firebaseData ,myPath + "/rollerKey"))
          {     
            myRollerKey = firebaseData.stringData();
          }
          if(Firebase.getString(firebaseData ,myPath + "/userKey"))
          {     
            userKey = firebaseData.stringData();
          }

        }
        else{
          Serial.print("getting /message failed:"); 
          Serial.println(firebaseData.errorReason());
        }
        break;
        
      case(2):
        t=millis();
        while(millis() - t < 5000){
          irCheck();
          if(doorState == opened )
          { 
            //@@@@@@@@@@@ 대여 처리
          myJson = "{\"rfidKey\":\""+myRfidKey+"\", \"locationKey\":\""+myLocationKey+"\", \"timestamp\":0}";
          if(Firebase.setJSON(firebaseData ,"/Rental Records/box1", myJson))
            Serial.println(firebaseData.stringData());
          else{
            Serial.print("setting /message failed:");
            Serial.println(firebaseData.errorReason());  
          } 
            break;
          }  
          vTaskDelay(100);
        }
        if(doorState == closed )
          {  
            //@@@@@@@@@@@ 시간 초과 -> 대여요청 취소
            Firebase.deleteNode(firebaseData, "Rental Requests/" + myRfidKey);
            Firebase.setString(firebaseData, "Rollers/" + myRollerKey + "/status", "ON_WAIT");
            Firebase.setBool(firebaseData, "Locations/" + myLocationKey + "/rollerKeys/" + myRollerKey, true);

            vTaskDelay(500);
            bolt.write(locked_pos);
            boltState = locked;        
          }
          
        break;
  
      case(3):
        irCheck();
        if(doorState == closed)
        {
          //@@@@ 반납 처리
          myJson = "{\"rfidKey\":\""+myRfidKey+"\", \"locationKey\":\""+myLocationKey+"\", \"timestamp\":0}";
          if(Firebase.setJSON(firebaseData ,"/Return Records/box1", myJson))
            Serial.println(firebaseData.stringData());
          else{
            Serial.print("setting /message failed:");
            Serial.println(firebaseData.errorReason());  
          } 
          vTaskDelay(500);
          bolt.write(locked_pos);
          boltState = locked;
        }
        break;
  
      case(4):
        irCheck();
        break;
  
      case(5):
        irCheck();
        break;
  }      
  vTaskDelay(200);
  }
}
//  checkCard();  
  
static void Thread2_checkCard(void* arg){
  while(1){
  while(1){
    vTaskDelay(50); //change value if you want to read cards faster
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    MFRC522::StatusCode status;
   
      // Look for new cards
    if ( !mfrc522.PICC_IsNewCardPresent()) {
      break;
    }
    if ( !mfrc522.PICC_ReadCardSerial()) {
      break;
    }
   
    bool result = true;
    uint8_t buf_len=4;
    cpid(&id);
    Serial.print("NewCard ");
    printDec(id.uidByte, id.size);
    Serial.println("");
    myRfidKey ="";
    for (byte i = 0; i < id.size; i++){  
     myRfidKey.concat(String(id.uidByte[i] < 0x10 ? "0" : ""));
     myRfidKey.concat(String(id.uidByte[i], DEC));
     }
     myPath.concat(myRfidKey);
     rfidState = exist;
         
    while(true){
      control=0;
      for(int i=0; i<3; i++){
        if(!mfrc522.PICC_IsNewCardPresent()){
          if(mfrc522.PICC_ReadCardSerial()){
            control |= 0x16;
          }
          if(mfrc522.PICC_ReadCardSerial()){
            control |= 0x16;
          }
            control += 0x1;
        }
        control += 0x4;
      }
      if(control == 13 || control == 14){
        vTaskDelay(100);//card is still there
           
      } else {
        break;
      }
    }
    Serial.println("CardRemoved");
    myRfidKey ="";
    myPath = "Rental Requests/";
    rfidState = empty;
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    
   
  }
  }
}


/*---------------------------------------------------------
 *                     함수설명
----------------------------------------------------------*/
void cpid(MFRC522::Uid *id){
  memset(id, 0, sizeof(MFRC522::Uid));
  memcpy(id->uidByte, mfrc522.uid.uidByte, mfrc522.uid.size);
  id->size = mfrc522.uid.size;
  id->sak = mfrc522.uid.sak;
}



void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

void checkState(){
  int temp = 0 | rfidState<<2 | doorState<<1 | boltState;

  
  switch(temp){                     //1~5 상태 - 보유여부, 닫힘여부, 잠금여부
    case 7: lockerState = 1; break; //대여 대기     - 1 1 1
    case 6: lockerState = 2; break; //열림 대기     - 1 1 0
    case 4: lockerState = 3; break; //수령&닫기 대기 - 1 0 0
    case 0: lockerState = 4; break; //넣기*닫기 대기 - 0 0 0
    case 2: lockerState = 5; break; //반납 대기     - 0 1 0
    default: Serial.println("StateError !");
             //tone(Buzzer_PIN,100,3000);               
  }
  
  printState();
  
}

void printState(){
 Serial.print("LockerState : ");Serial.print(lockerState);
 Serial.print(" rfidState : ");Serial.print(rfidState);
 Serial.print(" doorState : ");Serial.print(doorState);
 Serial.print(" boltState : ");Serial.print(boltState); 
 Serial.print(" myRfidKey : ");Serial.println(myRfidKey);
}

void irCheck()
{
  if(analogRead(I_PIN)<door_threshold) //임곗값보다 작은값이 들어오면 닫힌걸로 인식
    doorState = closed;
  else
    doorState = opened;
}