#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <BlynkSimpleSerialBLE.h>

SoftwareSerial gpsSerial(4, 3);   // GPS TX, RX pins
TinyGPS gps;
BlynkTimer timer;

char auth[] = "1VKIaqZp3orTn0pKlLB3jx8FVTvTD5-L";   // Blynk auth token
char bluetooth[] = "HC-05";   // Bluetooth module name
bool robotOn = false;   // variable to store robot on/off status

// Define motor driver pins
const int IN1 = 6;
const int IN2 = 7;
const int ENA = 9;

void setup()
{
  Serial.begin(9600);   // start serial communication for debugging purposes
  gpsSerial.begin(9600);   // start GPS serial communication
  Blynk.begin(Serial, auth);   // start Blynk communication over Bluetooth
  
  // Initialize motor driver pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop()
{
  while (gpsSerial.available() > 0)   // loop to read GPS data
  {
    if (gps.encode(gpsSerial.read()))   // if valid GPS data is received
    {
      float lat, lng;
      Blynk.virtualWrite(V1, lat);   // send latitude to Blynk app
      Blynk.virtualWrite(V2, lng);   // send longitude to Blynk app
    }
  }
  Blynk.run();   // run Blynk app
}

BLYNK_WRITE(V3)   // Blynk button widget to turn on/off the robot
{
  robotOn = param.asInt();   // set robot on/off status based on button widget state
  if (robotOn)
  {
    // Set motor direction and speed to move forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);   // full speed
  }
  else
  {
    // Stop the robot
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }
}
