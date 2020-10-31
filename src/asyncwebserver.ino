/**
 * Webserver Demo
 * 
 */
#include "definitions.h"
#include "templateProcessor.h"
#include "ota.h"
#include "motion-sensor.h"

String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

bool handleFileExists(String path) {              // send the right file to the client (if it exists)
  if (path.endsWith("/")) path += "index.html";   // If a folder is requested, send the index file
  String contentType = getContentType(path);      // Get the MIME type
  if (SPIFFS.exists(path)) {                      // If the file exists
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                   // If the file doesn't exist, return false
}

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

void getCurrentTime() {
  sprintf(timeStr, "%s, %d:%02d:%02d", daysOfTheWeek[timeClient.getDay()], timeClient.getHours(),timeClient.getMinutes(), timeClient.getSeconds());
}

void updateTime() {
  if (currentMillis - previousTimeUpdateMillis >= timeUpdateInterval) {
    timeClient.update();
    getCurrentTime();
    previousTimeUpdateMillis += timeUpdateInterval;
  }
}

void getChipInfo(){
  Serial.printf(" ESP8266 Chip id = %08X\n", ESP.getChipId());
  sprintf( chipIdString, "%08X", ESP.getChipId());
  Serial.printf(" ESP8266 CPU Frequency = %08X\n", ESP.getCpuFreqMHz());
  sprintf( cpuFreqString, "%08X", ESP.getCpuFreqMHz());
  Serial.printf(" ESP8266 Flash Chip Size = %08X\n", ESP.getFlashChipRealSize());
  sprintf( flashChipSizeString, "%08X", ESP.getFlashChipRealSize());  
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

#include "websocket.h"

void setup()
{  
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  Serial.begin(230400);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi Failed!\n");
    Serial.print("Setting soft-AP ... ");
    WiFi.softAPConfig(IPAddress(4, 3, 2, 1), IPAddress(4, 3, 2, 1), IPAddress(255,255,255,0));
    Serial.println(WiFi.softAP(apName) ? "Ready" : "Failed!");
  }

  getChipInfo();
  
  if (WiFi.localIP()[0] != 0) //is connected
  {
    IPAddress localIP = WiFi.localIP();
    sprintf(ipAddress, "%d.%d.%d.%d", localIP[0], localIP[1], localIP[2], localIP[3]);
  }

  if (WiFi.softAPIP()[0] != 0) //is active
  {
    IPAddress apIP = WiFi.softAPIP();
    sprintf(ipAddress, "%d.%d.%d.%d", apIP[0], apIP[1], apIP[2], apIP[3]);
  }

  if(!SPIFFS.begin()){
    Serial.print("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  Serial.print("IP Address: ");
  Serial.println(ipAddress);

  sprintf( rssiStr, "%d", WiFi.RSSI());

  getTempurature();

  timeClient.begin();
  getCurrentTime();

  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "web-wombat-2.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin(dnsName)) {
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  Serial.printf("mDNS responder started %s", dnsName);

  #include "routes.h"
  
  server.begin();

  startWebSocketServer();            // Start a WebSocket server

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
  startOTA();                  // Start the OTA service

  pirSetup();

  flashLEDs();
}

void loop()
{
  MDNS.update();
  ArduinoOTA.handle();        // listen for OTA events
  wss.loop();                 // check for websocket events
  currentMillis = millis();   // capture the latest value of millis()
  updateTemperature();
  updateTime();
  pirRead();
  sendClientData();
}
