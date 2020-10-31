#pragma once

const int pirPin = D6;

int val = 0;
bool motionState = false;
unsigned long previousPirUpdateMillis = 0;
const int pirUpdateInterval = 1000;

void pirSetup() {
  pinMode(pirPin, INPUT);
}

void pirRead() {
  if (currentMillis - previousPirUpdateMillis >= pirUpdateInterval) {
    val = digitalRead(pirPin);

    if (val == HIGH) {
      if (motionState == false) {
        Serial.println("-- Motion detected");
        motionState = true;
      }
    } else {
      if (motionState == true) {
        Serial.println("-- Motion ended");
        motionState = false;
      }
    }
  }
}