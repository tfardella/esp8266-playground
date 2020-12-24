#include "definitions.h"

const char *filename = "/config.txt";  // <- SD library uses 8.3 filenames

// Loads the configuration from a file
void loadConfiguration(const char *filename, Config &config) {
  // Open file for reading
 File file = SPIFFS.open("/config.json", "r");
 
  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  DynamicJsonDocument doc(1024)
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  strlcpy(config.ssid,
          doc["ssid"] | "9Greenleaf",
          sizeof(config.ssid));

  strlcpy(config.password,
          doc["password"] | "GreenleafLane",
          sizeof(config.password));

  strlcpy(config.mdnsname,
          doc["mdnsname"] | "wombat-web-1",
          sizeof(config.mdnsname));

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config &config) {
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove(filename);

  // Open file for writing
  File file = SPIFFS.open(filename, "w");
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<1024> doc;

  // Set the values in the JSON document
  JsonObject ap  = doc.createNestedObject("ap");
  JsonObject staticIp  = doc.createNestedObject("staticIp");
  doc["ssid"] = config.ssid;
  doc["password"] = config.password;
  doc["mdnsname"] = config.mdnsname;
  doc["staticIp"]["ip"] = config.staticIp.ip;
  doc["staticIp"]["gateway"] = config.staticIp.gateway;
  doc["staticIp"]["mask"] = config.staticIp.mask;
  doc["ap"]["ssid"] = config.ap.ap_ssid;
  doc["ap"]["password"] = config.ap.ap_password;
  doc["ap"]["channel"] = config.ap.channel;
  doc["ap"]["hide"] = config.ap.hide;
  doc["ap"]["opensl"] = config.ap.opens;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}

// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = SPIFFS.open(filename, "r");
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}
