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
        setLed(redLed, !digitalRead(redLed));
        redStatus = digitalRead(redLed);
        Serial.print("Red LED Status: ");
        Serial.println(redStatus);
      }

      if (color == "yellow")
      {
        setLed(yellowLed, !digitalRead(yellowLed));
        yellowStatus = digitalRead(yellowLed);
        Serial.print("Yellow LED Status: ");
        Serial.println(yellowStatus);
      }

      if (color == "green")
      {
        setLed(greenLed, !digitalRead(greenLed));
        greenStatus = digitalRead(greenLed);
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
