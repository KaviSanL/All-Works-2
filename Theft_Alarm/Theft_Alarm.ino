#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#include  <Wire.h>

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
// Define GSM module pins
#define GSM_TX_PIN 7  // Connect GSM module TX pin to Arduino pin 7
#define GSM_RX_PIN 8  // Connect GSM module RX pin to Arduino pin 8

// Define vibration sensor pin
#define VIBRATION_SENSOR_PIN 2  // Connect vibration sensor to Arduino pin 2

SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);  // RX, TX

void setup() {
  // Initialize serial communication with the computer
  Serial.begin(9600);
  
  // Initialize serial communication with GSM module
  gsmSerial.begin(9600);
  lcd.init();  // turn on the backlight
  lcd.backlight();
  
  // Initialize vibration sensor pin as input
  pinMode(VIBRATION_SENSOR_PIN, INPUT);
}

void loop() {
  // Read the vibration sensor value
  int vibrationValue = digitalRead(VIBRATION_SENSOR_PIN);
  
  // If vibration is detected (vibration sensor value is HIGH)
  if (vibrationValue == HIGH) {
    // Send SMS
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Theft is Here");
    sendSMS("+1234567890", "Vibration detected!");
    makecall("+919944263469");
    // Wait for a while to prevent sending multiple SMS in a short time
    delay(5000); // Adjust delay time as needed
  }
}

void sendSMS(String phoneNumber, String message) {
  // Send SMS command
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.println((char)26);
  delay(1000);
}
void makecall(const char* phone)
{
    Serial.println("calling....");
   gsmSerial.print("ATD");
   gsmSerial.print(phone);
   gsmSerial.println(";");
    delay(20000); //20 sec delay
    gsmSerial.println("ATH");
    delay(1000); //1 sec delay
}