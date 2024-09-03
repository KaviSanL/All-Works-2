#include <SoftwareSerial.h>
#include <TinyGPS.h>

// Define pins for GPS module
#define GPS_RX 2
#define GPS_TX 3

// Define variables for GPS coordinates
double latitude, longitude;
#define TinyGPS 

void setup() {
  // Set up serial communication
  Serial.begin(9600);
  Serial.begin(9600);

  // Set up GPS communication
  TinyGPS.begin('GPS_RX.GPS_TX');
}

void loop() {
  // Read GPS data
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      // Get latitude and longitude values
      gps.f_get_position(&latitude, &longitude);
    }
  }
  
  // Print latitude and longitude values
  Serial.print("Latitude: ");
  Serial.println(latitude, 6);
  Serial.print("Longitude: ");
  Serial.println(longitude, 6);
  
  delay(1000);
}
