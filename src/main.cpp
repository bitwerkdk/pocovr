#include <Arduino.h>

#define firstScreenCS 21
#define secondScreenCS 22

void setup() {
  Serial.begin(115200);
  
  pinMode(firstScreenCS, OUTPUT);
  pinMode(secondScreenCS, OUTPUT);

  // Initialize both displays
  digitalWrite(firstScreenCS, LOW);
  digitalWrite(secondScreenCS, LOW);

  Serial.println("setup");
}

void loop() {
  Serial.println("loop");
}