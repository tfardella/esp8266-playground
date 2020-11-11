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

AsyncWebServer server(80);

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

unsigned long previousDataUpdateMillis = 0;
const int dataUpdateInterval = 1000;

#endif