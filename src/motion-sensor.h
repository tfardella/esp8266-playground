#pragma once

const int pirPin = D6;

int val = 0;
bool motionState = false;

ICACHE_RAM_ATTR void detectMovement() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    if (motionState == false) {
      Serial.println("-- Motion detected");
      motionState = true;
      digitalWrite(LED_BUILTIN, 0);
    }
  } else {
    if (motionState == true) {
      Serial.println("-- Motion ended");
      motionState = false;
      digitalWrite(LED_BUILTIN, 1);
    }
  }
}

void pirSetup() {
  pinMode(pirPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pirPin), detectMovement, CHANGE);
}
