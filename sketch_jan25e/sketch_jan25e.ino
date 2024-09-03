#include <Servo.h>

// initialize the servo object
Servo myservo;
int inc=0;
int b;
// define the touch sensor pin
const int touchSensorPin = 2;
const int touchSensorPin1 = 3;
// define the servo pin
const int servoPin = 7;

// define the initial servo position
int pos = 0;

// define the state of the touch sensor
int touchState = 0;
int touchState1 = 0;

// define the previous state of the touch sensor
int prevTouchState = 0;
int prevTouchState1 = 0;

// define the delay between rotations
const long rotationDelay = 2000; // in microseconds

void setup() {
  // attaches the servo to the specified pin
  myservo.attach(servoPin);
  Serial.begin(9600);

  // sets the touch sensor as an input
  pinMode(touchSensorPin, INPUT);
  pinMode(touchSensorPin1, INPUT);
}

void loop() {
  // reads the value of the touch sensor
    touchState = digitalRead(touchSensorPin);
    touchState1 = digitalRead(touchSensorPin1);

  
  if(touchState==HIGH && inc==0 ){
    
    Serial.print("inncrement");
    inc=inc+1;
    
    Serial.println(inc);
  }
 start();
 if(touchState1==HIGH){
  Serial.println("2");
  myservo.detach();
    myservo.write(0);
 }
 
}
  
void start(){
    int a =0;
  // if the touch sensor is pressed and it wasn't pressed before
  while (touchState == HIGH && prevTouchState == LOW && a<10 && inc==1) {
    // move the servo to the specified position
    Serial.println("loop started");
   
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);        
    
    // waits 15 ms for the servo to reach the position
    
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    
  }
  a++;
  }

  // if the touch sensor is pressed and it was pressed before
  
  // update the previous state of the touch sensor
  prevTouchState=touchState;
}
