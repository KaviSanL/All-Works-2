#include <Servo.h>

Servo hipservo;
Servo kneeservo;

void setup() {
  hipservo.attach(9);
  kneeservo.attach(10);

  hipservo.write(90);
  kneeservo.write(90);
}

void loop() {
  // Perform a forward motion
  for (int i = 90; i < 135; i++) {
    hipservo.write(i);
    delay(10);
  }
  for (int i = 90; i < 135; i++) {
    kneeservo.write(90 - i);
    delay(10);
  }
  delay(1000);

  for (int i = 135; i > 90; i--) {
    hipservo.write(i);
    delay(10);
  }
  for (int i = 90; i > 45; i--) {
    kneeservo.write(i);
    delay(10);
  }
   delay(1000);

}
