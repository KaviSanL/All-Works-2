#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Servo.h>
#include <AFMotor.h>
#include <BlynkSimpleStream.h>

//Blynk authentication token
char auth[] = "TTWbS-nRh9iSOkAZT0hd8j-UJm-lq-cE";

//Motor driver pins
AF_DCMotor motor_left(1);
AF_DCMotor motor_right(2);

//Ultrasonic sensor pins
const int trigPin = 3;
const int echoPin = 2;

//GPS pins
SoftwareSerial gpsSerial(4, 3); //RX, TX
TinyGPS gps;
float lat, lon;

//Servo motor pins
Servo myservo;
int servo_pin = 9;

//Blynk virtual pins
#define V1 V1
#define V2 V2
#define V3 V3

//Blynk button states
int btn1_state = 0;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Blynk.begin(Serial, auth);

  //Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Servo motor pins
  myservo.attach(servo_pin);

  //Motor driver pins
  motor_left.setSpeed(150);
  motor_right.setSpeed(150);
}

void loop() {
  //Blynk app
  Blynk.run();

  //Read GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      gps.f_get_position(&lat, &lon);
    }
  }

  //Read ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  //Move robot towards GPS coordinates
  if (distance > 10 && lat != TinyGPS::GPS_INVALID_F_ANGLE && lon != TinyGPS::GPS_INVALID_F_ANGLE) {
    float target_lat = 43.12345; //Your target latitude
    float target_lon = -76.54321; //Your target longitude
    float heading = TinyGPS::course_to(lat, lon, target_lat, target_lon);

    myservo.write(heading);

    if (heading >= 0 && heading <= 180) {
      motor_left.run(FORWARD);
      motor_right.run(FORWARD);
    }
    else {
      motor_left.run(BACKWARD);
      motor_right.run(BACKWARD);
    }
  }
  else {
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
  }
}

//Blynk app button callback function
BLYNK_WRITE(V1) {
  btn1_state = param.asInt();
  if (btn1_state == 1) {
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
  }
  else {
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
  }
}
