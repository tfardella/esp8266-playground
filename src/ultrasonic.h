#pragma once
#include <Arduino.h>
#include "definitions.h"

// defines pins numbers
const int trigPin = D7;
const int echoPin = D8;

// defines variables
long duration;
int distance;

// define how often to read the distance
unsigned long previousUltrasonicUpdateMillis = 0;
const int ultrasonicUpdateInterval = 3000; // 5sec

void ultrasonicSetup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void ultrasonicRead() {
  if (currentMillis - previousUltrasonicUpdateMillis >= ultrasonicUpdateInterval) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = (duration/2) * 0.0343; // distance in inches. For inches: 0.01350
    // Prints the distance on the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distance);

    previousUltrasonicUpdateMillis += ultrasonicUpdateInterval;
  }
}
