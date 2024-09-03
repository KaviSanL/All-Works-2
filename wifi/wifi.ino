#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Motor Driver pins
const int leftMotorPWM = D5;
const int leftMotorDIR = D6;
const int rightMotorPWM = D7;
const int rightMotorDIR = D8;

// GPS module pins
const int RXPin = D1;
const int TXPin = D2;
SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;

// Blynk authentication token
char auth[] = "2IGcchawaYkT1PWNqBfP2B1UJErP_1KY";


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "Mari’s iPhone", "marimuthu");


  // Motor Driver setup
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDIR, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDIR, OUTPUT);

  // GPS module setup
  gpsSerial.begin(9600);
}

void loop()
{
  Blynk.run();

  // Get GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Store GPS data
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();

      // Send GPS data to Blynk app
      Blynk.virtualWrite(V1, latitude);
      Blynk.virtualWrite(V2, longitude);

      // Control motors based on GPS data
      followMeRobot(latitude, longitude);
    }
  }
}

void followMeRobot(double latitude, double longitude)
{
  // Target GPS coordinates
  double targetLatitude = 48.8584;
  double targetLongitude = 2.2945;

  // Distance to target
  double distance = TinyGPSPlus::distanceBetween(latitude, longitude, targetLatitude, targetLongitude);

  // Determine motor speed based on distance
  int speed = map(distance, 0, 100, 0, 255);

  // Determine motor direction based on longitude
  int direction = (longitude > targetLongitude) ? -1 : 1;

  // Control motors
  analogWrite(leftMotorPWM, speed);
  digitalWrite(leftMotorDIR, direction);
  analogWrite(rightMotorPWM, speed);
  digitalWrite(rightMotorDIR, direction);
}

BLYNK_WRITE(V3)
{
  // Button to turn on/off the robot
  int buttonState = param.asInt();

  if (buttonState == 1) {
    // Turn on the robot
    digitalWrite(leftMotorDIR, HIGH);
    digitalWrite(rightMotorDIR, HIGH);
  } else {
    // Turn off the robot
    digitalWrite(leftMotorPWM, LOW);
    digitalWrite(leftMotorDIR, LOW);
    digitalWrite(rightMotorPWM, LOW);
    digitalWrite(rightMotorDIR, LOW);
  }
}
