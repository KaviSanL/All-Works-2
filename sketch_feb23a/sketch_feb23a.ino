#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "_ZnFah4O3L8nhNnmb1rgnzQ1ywFxAm5h";//Enter your Auth token
char ssid[] = "Kavi";//Enter your WIFI name
char pass[] = "0987654321";//Enter your WIFI password

BlynkTimer timer;

// Define the component pins
#define trig 21
#define echo 23
#define LED1 34
#define LED2 35
#define LED3 32
#define LED4 33
#define LED5 25
#define relay 27

//Enter your tank max value(CM)
int MaxLevel = 20;

int Level1 = (MaxLevel * 75) / 100;
int Level2 = (MaxLevel * 65) / 100;
int Level3 = (MaxLevel * 55) / 100;
int Level4 = (MaxLevel * 45) / 100;
int Level5 = (MaxLevel * 35) / 100;

void setup() {
  Serial.begin(9600);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  
  //Call the functions
  timer.setInterval(100L, ultrasonic);
}

//Get the ultrasonic sensor values
void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  int distance = t / 29 / 2;

  int blynkDistance = (distance - MaxLevel) * -1;
  if (distance <= MaxLevel) {
    Blynk.virtualWrite(V0, blynkDistance);
  } else {
    Blynk.virtualWrite(V0, 0);
  }
  

  if (Level1 <= distance) {
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
  } 
    else if (Level2 <= distance && Level1 > distance) {
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    }
    else if (Level3 <= distance && Level2 > distance) {
   
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    }
    else if (Level4 <= distance && Level3 > distance) {
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, LOW);
    }
    else if (Level5 >= distance) {
   
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
  }
}

//Get the button value
BLYNK_WRITE(V1) {
  bool Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
  }
   else {
    digitalWrite(relay, HIGH);
    
  }
}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
