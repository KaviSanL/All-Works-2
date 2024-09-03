#include <Servo.h>
Servo Servo_X;
Servo Servo_Y;
#define Joy_X A3
#define Joy_Y A4
int Joy_Val = 0;
void setup()
{
  Servo_X.attach(3);
  Servo_Y.attach(5);

  
}
void loop()
{
  Joy_Val = analogRead(Joy_X);
  Joy_Val = map(Joy_Val, 0, 1023, 180, 0);
  Servo_X.write(Joy_Val);

  Joy_Val = analogRead(Joy_Y);
  Joy_Val = map(Joy_Val, 0, 1023, 0, 180);
  Servo_Y.write(Joy_Val);
  delay(15);
}
