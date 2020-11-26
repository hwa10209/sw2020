//<KEIL에서 C로 짠 코드>
//edsim51 setting
//keypad "pulse", "12Mhz", "10000" update Freq, "no" parity, "4800"Baud
#include<reg51.h>
sbit SAVEDATE=P2^1;
sbit SHOWDATE=P2^2;
sbit SENDDATE=P2^3;
unsigned char check;
unsigned char input;
unsigned char number;
unsigned char memory[4];
code unsigned char wnumber[]={0xFF, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98,
0xE3, 0xC0, 0xE3};
//empty,1,2,3,4,5,6,7,8,9,v,0,v
code unsigned char wsave[]={0x92,0x88,0xC1,0x86};
code unsigned char wdate[]={0xA1,0x88,0x87,0x86};
code unsigned char wsend[]={0x92,0x86,0xC8,0xA1};
unsigned char i;
unsigned char j;
int k;
void delay();
void date();
void send();
void SerTx(unsigned char);
void regist();
void printsave();
void printdate();
void printsend();
void main(){
//choose mode : save,show,send
while(1){
 while(P2==255);
 if(SAVEDATE==0)
 {
 printsave();
 regist();
 }
 if(SHOWDATE==0)
 {
 printdate();
 date();
 }
 if(SENDDATE==0)
{
 printsend();
send();
 }
}
}
void regist(){
for (i=0;i<4;i++)
{

 number=0;
 input=0;
 while(1){
 check=0xff; //check=11111111b
 P1=0xff ;

 check--; //check=11111110b
 P0=check;
 if(check!=P0)
 { input = P0;
 number= 9;
 break;
 }
 check--; //check=11111101b
 P0=check;
 if(check!=P0)
 { input = P0;
 number= 6;
 break;
 }
 check--;
 check--; //check=11111011b
 P0=check;
 if(check!=P0)
 { input = P0;
 number= 3; 
 break;
 }
 check-=4; //check=11110111b
 P0=check;
 if(check!=P0)
 { input = P0;
 number= 0;
 break;
 }
 }
 input=input>>4;
 input=input&7;
 if(input==3) //00000011b (*,1,4,7 ? ??)
 number+=1;
 if(input==5) //00000101b (0,2,5,8 ? ??)
 number+=2;
 if(input==6) //00000110b (#,3,6,9 ? ??)
 number+=3;

 memory[i]=number;
P1=wnumber[memory[i]];
delay();
P1=0xFF;
}
return;
}
void date(){
for(j=0;j<2;j++)
{
 for(i=0;i<4;i++)
 {
 P1=wnumber[memory[i]];
 delay();
 P1=0xFF;
 P3-=8;
 }
}
}
//transfer the message, 4800baud, 8-bit data,1 start bit,1 stop bit
void send(){
delay();
TMOD=0x20; // timer1, mode2 (8bit auto reload), no parity
TH1=243; //DOUBLE BOUD RATE (4800baud in edsim)
TL1=243;
PCON=128;
SCON=0x50;
TR1=1; //start timer
//using for loop the
the signal shifted
SerTx('M');SerTx('y');SerTx(' ');SerTx('b');SerTx('i');SerTx('r');SerTx('t');
SerTx('t');SerTx('d');SerTx('y');SerTx(' ');SerTx('i');SerTx('s');SerTx(' ');
SerTx(memory[0]+48);
SerTx(memory[1]+48);
SerTx('/');
SerTx(memory[2]+48);
SerTx(memory[3]+48);
TR1=0;
delay();
}
void SerTx(unsigned char x){
if(x==59)
x-=11;
SBUF=x;
while (TI==0);
TI=0;
}
void printsave(){
for(j=0;j<2;j++)
{

 for(i=0;i<4;i++)
 {
 P1=wsave[i];
 delay();
 P1=0xFF;
 P3-=8;
 }
P3=255;
}
}
void printdate(){
for(j=0;j<2;j++)
{

 for(i=0;i<4;i++)
 {
 P1=wdate[i];
 delay();
 P1=0xFF;
 P3-=8;
 }
P3=255;
}
}
void printsend(){
for(j=0;j<2;j++)
{

 for(i=0;i<4;i++)
 {
 P1=wsend[i];
 delay();
 P1=0xFF;
 P3-=8;
 }
P3=255;
}
}
void delay(){
for(k=0;k<10000;k++);
}