#pragma once

#include "DHT.h"

// DHT Sensor
uint8_t DHTPin = D5; 
// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

unsigned long previousTempUpdateMillis = 0;
const int tempUpdateInterval = 10000;

float Temperature;
float Humidity;

void getTempurature() {
  Temperature = dht.readTemperature(true);
  Humidity = dht.readHumidity();
}

void updateTemperature() {
  if (currentMillis - previousTempUpdateMillis >= tempUpdateInterval) {
    getTempurature();
    previousTempUpdateMillis += tempUpdateInterval;
  }
}
