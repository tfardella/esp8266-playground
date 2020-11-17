#pragma once

#ifndef LEDS
#define LEDS

const int redLed = D1;
const int yellowLed = D2;
const int greenLed = D3;

int redStatus = 0;
int yellowStatus = 0;
int greenStatus = 0;

void setupLEDs() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void setLed(int led, int state)
{
  digitalWrite(led, state);
}

void setLEDs(){
  Serial.printf("setLEDs: %d, %d, %d", redStatus, yellowStatus, greenStatus);
  setLed(redLed, redStatus);
  setLed(yellowLed, yellowStatus);
  setLed(greenLed, greenStatus);
}

void getLEDStatus() {
  redStatus = digitalRead(redLed);
  yellowStatus = digitalRead(yellowLed);
  greenStatus = digitalRead(greenLed);
}

void flashLEDs(){
  setLed(redLed, 1);
  delay(200);
  setLed(yellowLed, 1);
  delay(200);
  setLed(greenLed, 1);
  delay(1000);
  setLed(redLed, 0);
  delay(200);
  setLed(yellowLed, 0);
  delay(200);
  setLed(greenLed, 0);
}

#endif

