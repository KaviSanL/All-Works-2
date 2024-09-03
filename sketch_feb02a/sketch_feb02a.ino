#include <SoftwareSerial.h>

#include <JQ6500_Serial.h>

JQ6500_Serial mp3(8,9);
void setup(){

Serial.begin(115200);
  mp3.begin(9600);
  mp3.reset();
}

void loop(){
  mp3.playFileByIndexNumber(1);
}
