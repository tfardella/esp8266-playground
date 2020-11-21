#pragma once

#ifndef NTP_TIME
#define NTP_TIME

#include <NTPClient.h>
#include <WiFiUdp.h>

unsigned long previousTimeUpdateMillis = 0;
const int timeUpdateInterval = 1000;

const long utcOffsetInSeconds = (-8 * 60 * 60);
const long utcUpdateInMilliSeconds = (60 * 60 * 1000); // Update NTP time every 1 hour
char daysOfTheWeek[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char timeStr[80];

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds, utcUpdateInMilliSeconds);

void updateTime() {
  if (currentMillis - previousTimeUpdateMillis >= timeUpdateInterval) {
    timeClient.update();
    previousTimeUpdateMillis += timeUpdateInterval;
  }
}

void getCurrentTime() {
  sprintf(timeStr, "%s, %d:%02d:%02d", daysOfTheWeek[timeClient.getDay()], timeClient.getHours(),timeClient.getMinutes(), timeClient.getSeconds());
}
#endif