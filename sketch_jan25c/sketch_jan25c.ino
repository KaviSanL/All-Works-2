const int touchSensorPin = 2;
const int servoPin = 3;
int touchState = HIGH;
int pos = 0;
int a = 0;

Servo myservo;

void setup() {
  myservo.attach(servoPin);
  pinMode(touchSensorPin, INPUT_PULLUP);
}

void loop() {
  touchState = digitalRead(touchSensorPin);

  do {
    if (pos <= 45) {
      myservo.write(pos);
      pos++;
    }
    else {
      myservo.write(45);
    }
    touchState = digitalRead(touchSensorPin);
    a++;
    delay(10); // Add a delay to allow the sensor to be read again
  } while (touchState == LOW && a < 50);

}
