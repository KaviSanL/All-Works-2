#include <Arduino.h>

#include <SoftwareSerial.h>

#include <JQ6500_Serial.h>

JQ6500_Serial mp3(8,9);

int left_trigPin = 7;

int left_echoPin = 6;

int right_trigPin = 2;

int right_echoPin = 3;

int center_trigPin = 4;

int center_echoPin = 5;

void setup() {

  pinMode(left_trigPin,OUTPUT);

  pinMode(left_echoPin,INPUT);

  pinMode(right_trigPin,OUTPUT);

  pinMode(right_echoPin,INPUT);

  pinMode(center_trigPin,OUTPUT);

  pinMode(center_echoPin,INPUT);

  Serial.begin(115200);

  mp3.begin(9600);

  mp3.reset();

  mp3.setVolume(50);

  mp3.setLoopMode(MP3_LOOP_NONE);

}

void loop(){

     left();

     right();

     center();

}

void left(){

  delay(500);// reading will be taken after ....miliseconds

  Serial.println("\n");

  int duration, distance;

    digitalWrite (left_trigPin, HIGH);

    delayMicroseconds (10);

    digitalWrite (left_trigPin, LOW);

    duration = pulseIn (left_echoPin, HIGH);

    distance = (duration/2) / 29.1;

    //distance= duration*0.034/2;  

    if (distance < 30) {  // Change the number for long or short distances.    

    Serial.print("Left Distance");

    Serial.print(distance);

     mp3.playFileByIndexNumber(2);

    }

}

void right(){

   delay(500);// reading will be taken after ....miliseconds

   Serial.println("\n");

   int duration, distance;

    digitalWrite (right_trigPin, HIGH);

    delayMicroseconds (10);

    digitalWrite (right_trigPin, LOW);

    duration = pulseIn (right_echoPin, HIGH);

    distance = (duration/2) / 29.1; 

    if (distance <30) {  // Change the number for long or short distances.

    Serial.print("Right Distance");

    Serial.print(distance);

    mp3.playFileByIndexNumber(3);

    }

 }

void center(){

   delay(500);// reading will be taken after ....miliseconds

   Serial.println("\n");

   int duration, distance;

    digitalWrite (center_trigPin, HIGH);

    delayMicroseconds (10);

    digitalWrite (center_trigPin, LOW);

    duration = pulseIn (center_echoPin, HIGH);

    distance = (duration/2) / 29.1; 

    if (distance <30) {  // Change the number for long or short distances.

    Serial.print("Center Distance");

    Serial.print(distance);

    mp3.playFileByIndexNumber(1);

    }

 }
