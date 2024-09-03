// Line follower PID control
#include <PID_v1.h>

// IR sensor pins (adjust these according to your connections)
const int irPin1 = A1;
const int irPin2 = A2;
const int irPin3 = A3;
const int irPin4 = A4;
const int irPin5 = A5;

// Motor driver pins
const int motor1A = 4;
const int motor1B = 3;
const int motor2A = 6;
const int motor2B = 7;

// PID constants
double kp = 1.0; // Proportional constant
double ki = 0.0; // Integral constant
double kd = 0.0; // Derivative constant

// Setpoint for the line following (Adjust as needed)
double setpoint = 2.0; // Assume the middle IR sensor (sensor 3) is the setpoint

// Variables to store sensor readings
int irValue1, irValue2, irValue3, irValue4, irValue5;

// PID variables
double input, output, target;
PID lineFollowerPID(&input, &output, &target, kp, ki, kd, DIRECT);

void setup() {
  // Motor driver setup
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // IR sensor setup
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
  pinMode(irPin3, INPUT);
  pinMode(irPin4, INPUT);
  pinMode(irPin5, INPUT);

  // Start Serial communication if needed
  // Serial.begin(9600);

  // PID setup
  lineFollowerPID.SetMode(AUTOMATIC);
  lineFollowerPID.SetOutputLimits(-255, 255);
  lineFollowerPID.SetSampleTime(10); // PID control loop time in ms
}

void loop() {
  // Read sensor values
  irValue1 = analogRead(irPin1);
  irValue2 = analogRead(irPin2);
  irValue3 = analogRead(irPin3);
  irValue4 = analogRead(irPin4);
  irValue5 = analogRead(irPin5);

  // Calculate the weighted average of sensor values
  input = (irValue1 * 1 + irValue2 * 2 + irValue3 * 3 + irValue4 * 2 + irValue5 * 1) / 9.0;

  // Compute PID output
  lineFollowerPID.Compute();

  // Adjust motor speeds based on the PID output
  int motorSpeedA = constrain(255 + output, 0, 255);
  int motorSpeedB = constrain(255 - output, 0, 255);

  // Apply motor control signals
  analogWrite(motor1A, motorSpeedA);
  analogWrite(motor1B, 0);
  analogWrite(motor2A, motorSpeedB);
  analogWrite(motor2B, 0);

  // Uncomment the following lines to debug values if needed
  // Serial.print(irValue1); Serial.print("\t");
  // Serial.print(irValue2); Serial.print("\t");
  // Serial.print(irValue3); Serial.print("\t");
  // Serial.print(irValue4); Serial.print("\t");
  // Serial.print(irValue5); Serial.print("\t");
  // Serial.print(input); Serial.print("\t");
  // Serial.print(output); Serial.print("\t");
  // Serial.println();
}
