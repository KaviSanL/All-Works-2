const int xAxisPin = A0;  // Analog input pin for X-axis
const int yAxisPin = A1;  // Analog input pin for Y-axis

void setup() {
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  int xAxisValue = analogRead(xAxisPin);  // Read X-axis value
  int yAxisValue = analogRead(yAxisPin);  // Read Y-axis value

  // Print the values to the serial monitor
  Serial.print("X-axis: ");
  Serial.print(xAxisValue);
  Serial.print("\tY-axis: ");
  Serial.println(yAxisValue);

  delay(100);  // Delay for stability
}
