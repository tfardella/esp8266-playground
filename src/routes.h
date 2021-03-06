  /**
   * Web server route definitions.
   */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Send a GET request to <IP>/light?light=<red/green/yellow>
  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request) {
    String color;
    String reqStatus;

    if (request->hasParam(PARAM_LIGHT_COLOR))
    {
      color = request->getParam(PARAM_LIGHT_COLOR)->value();
      reqStatus = request->getParam(PARAM_LIGHT_STATUS)->value();

      if (color == "red")
      {
        getLEDStatus();
        setLed(redLed, !redStatus);
        Serial.print("Red LED Status: ");
        Serial.println(redStatus);
      }

      if (color == "yellow")
      {
        getLEDStatus();
        setLed(yellowLed, !yellowStatus);
        Serial.print("Yellow LED Status: ");
        Serial.println(yellowStatus);
      }

      if (color == "green")
      {
        getLEDStatus();
        setLed(greenLed, !greenStatus);
        Serial.print("Green LED Status: ");
        Serial.println(greenStatus);
      }
    }

    request->send(SPIFFS, "/led.html", String(), false, processor);
  });

  // Wifi settings

  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/settings.html", String(), false, processor);
  });

  server.on("/settings", HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.print("--- Settings form submitted ---");
    int args = request->args();
    for(int i=0;i<args;i++){
      Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
    }

    request->send(SPIFFS, "/settings.html", String(), false, processor);
  });

  // Temerature
  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/temperature.html", String(), false, processor);
  });

  // server.onNotFound(notFound);
  server.onNotFound([](AsyncWebServerRequest *request) {                  // If the client requests any URI
    if (handleFileExists(request->url())) {                               
      request->send(SPIFFS, request->url(), String());  // send it if it exists
    } else {
      request->send(404, "text/plain", request->url() + " Not found");    // otherwise, respond with a 404 (Not Found) error
    }
  });
