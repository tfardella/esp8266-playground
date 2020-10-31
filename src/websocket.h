#pragma once

#include <WebSocketsServer.h>
#include <ArduinoJson.h>

WebSocketsServer wss = WebSocketsServer(8081);

/**
 *  WebSocket event handler
 */
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) { 
  switch (type) {
    case WStype_DISCONNECTED: {            // if the websocket is disconnected
        Serial.printf("[%u] Disconnected!\n", num);
      }
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = wss.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        wss.sendTXT(num, "Connected");
        getLEDStatus();
      }
      break;
    case WStype_TEXT:                     // if new text data is received
      Serial.printf("[%u] get Text: %s\n", num, payload);
      const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + 22;
      StaticJsonDocument<capacity> leds;
      // Deserialize the JSON document
      DeserializationError error = deserializeJson(leds, payload);
      if(!error){
        redStatus = leds["red"];
        yellowStatus = leds["yellow"];
        greenStatus = leds["green"];
        setLEDs();
      }
      break;
  }
}

void sendClientData() {
  if (currentMillis - previousDataUpdateMillis >= dataUpdateInterval) {
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + 201;
    StaticJsonDocument<capacity> doc;
    doc["time"] = timeStr;
    doc["temperature"] = Temperature;
    doc["humidity"] = Humidity;
    doc["motion"] = motionState;
    JsonObject leds  = doc.createNestedObject("leds");
    leds["red"] = redStatus;
    leds["yellow"] = yellowStatus;
    leds["green"] = greenStatus;
    serializeJson(doc, wsDataStr);
    
    // Check if a client has connected
    int i = wss.broadcastTXT(wsDataStr);
    Serial.printf("Connected websocket clients ping: %s\n", wsDataStr);

    previousDataUpdateMillis += dataUpdateInterval;
  }
}

void startWebSocketServer() {           // Start a WebSocket server
  wss.begin();                          // start the websocket server
  wss.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.print("WebSocket server started.");
}

