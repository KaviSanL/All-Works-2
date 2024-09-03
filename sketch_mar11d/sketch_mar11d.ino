#include <BlynkSimpleEsp8266.h>

#define BlynkWifi blynk;

void setup() {
  // Initialize Blynk
  Blynk.begin(auth, wifi, ssid, pass);
}

void loop() {
  // Read virtual pin 1
  int value = Blynk.virtualRead(1);

  // Do something with the value
  // ...
}
