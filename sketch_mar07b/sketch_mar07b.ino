#include <TinyGPS.h>

TinyGPS gps;
double latitude, longitude;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      gps.f_get_position(&latitude, &longitude);
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);
    }
  }
}
