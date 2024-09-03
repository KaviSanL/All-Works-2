#include <SoftwareSerial.h>
int a1 =2;
int a2 =3;
int a3 =4;
int a4 =5;
int a5 =6;


const int lmf = 10;
const int lmb = 11;
const int rmf = 12;
const int rmb = 13;

void setup() {
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(lmf,OUTPUT);
pinMode(lmb,OUTPUT);
pinMode(rmf,OUTPUT);
pinMode(rmb,OUTPUT);
Serial.begin(9600);
}
void loop(){
a1=digitalRead(2);
a2=digitalRead(3);
a3=digitalRead(4);
a4=digitalRead(5);
a5=digitalRead(6);

//forward
if(a3==0)
{
  digitalWrite(rmf,HIGH);
  digitalWrite(rmb,LOW);
  digitalWrite(lmf,HIGH);
  digitalWrite(lmb,LOW);
  delay(20);
  }
else if(a2==0&&a3==0&&a4==0)
{
  digitalWrite(rmf,HIGH);
  digitalWrite(rmb,LOW);
  digitalWrite(lmf,HIGH);
  digitalWrite(lmb,LOW);
  delay(20);
  }
  
 if(a5==0||a4==0||a3==0){
    digitalWrite(rmf,HIGH);
    digitalWrite(rmb,LOW);
    digitalWrite(lmf,LOW);
    digitalWrite(lmb,LOW);
    delay(20);
}

if(a3==0||a2==0||a1==0){
    digitalWrite(rmf,LOW);
    digitalWrite(rmb,LOW);
    digitalWrite(lmf,HIGH);
    digitalWrite(lmb,LOW);
   delay(20);
}

    }
