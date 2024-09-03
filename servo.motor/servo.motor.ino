#include<Servo.h>
Servo rotate;

void setup() {
  // put your setup code here, to run once:
rotate.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
rotate.write(90);
delay(1000);
rotate.write(0);
delay(1000);
}
