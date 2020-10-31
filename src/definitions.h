#pragma once

#ifndef DEFINITIONS
#define DEFINITIONS

#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>
#include <ESPHTTPClient.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif

#include <ESPAsyncWebServer.h>
#include <WString.h>
#include <FS.h>   // Include the SPIFFS library
#include "DHT.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WebSocketsServer.h>

// DHT Sensor
uint8_t DHTPin = D5; 
// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

AsyncWebServer server(80);
// WebSocketsServer wss = WebSocketsServer(8081);

char ssid[32] = "9Greenleaf";
char password[32] = "GreenleafLane";
char apName[32] = "wombat-02";
char dnsName[32] = "wombat-web-2";  // dns http://wombat-web-2.local
IPAddress localIP;
char rssiStr[16];

byte apHide = 0;                              //hidden AP SSID
byte apBehavior = 0;                          //0: Open AP when no connection after boot 1: Open when no connection 2: Always open 3: Only when button pressed for 6 sec
IPAddress staticIP(0, 0, 0, 0);               //static IP of ESP
IPAddress staticGateway(0, 0, 0, 0);          //gateway (router) IP
IPAddress staticSubnet(255, 255, 255, 0);     //most common subnet in home networks

const char *PARAM_LIGHT_COLOR = "color";
const char *PARAM_LIGHT_STATUS = "status";
const int redLed = D1;
const int yellowLed = D2;
const int greenLed = D3;

int redStatus = 0;
int yellowStatus = 0;
int greenStatus = 0;
char statusStr[8];

char ipAddress[16];
char chipIdString[16];
char flashChipSizeString[16];
char cpuFreqString[16];

// Timing variables
unsigned long currentMillis = 0;
unsigned long previousTempUpdateMillis = 0;
const int tempUpdateInterval = 10000;
unsigned long previousTimeUpdateMillis = 0;
const int timeUpdateInterval = 1000;
unsigned long previousDataUpdateMillis = 0;
const int dataUpdateInterval = 1000;

float Temperature;
float Humidity;

const long utcOffsetInSeconds = (-7 * 60 * 60);
char daysOfTheWeek[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char timeStr[80];
char wsDataStr[150];

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
#endif