#include "zeroExport.h"

// Constructor
zeroExport::zeroExport(const char* _endpoint, uint32_t _updateInterval)
  : endpoint(_endpoint), updateInterval(_updateInterval * 1000), lastUpdate(millis()), isRunning(true) {
  Serial.println(F("zeroExport started"));
}

// Destructor
zeroExport::~zeroExport() {
  stop();
}

// Stop the meter reader
void zeroExport::stop() {
  if (isRunning) {
    isRunning = false;
    Serial.println(F("zeroExport stopped"));
  }
}

// Handle method - call this from main loop
void zeroExport::handle() {
  if (!isRunning) {
    return;
  }
  
  // Check if it's time to update
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    
    // Perform the HTTP request
    if (httpClient.begin(wifiClient, endpoint)) {
      int httpCode = httpClient.GET();
      if (httpCode == HTTP_CODE_OK) {
        String payload = httpClient.getString();
        DeserializationError err = deserializeJson(doc, payload);
        if (!err) {
            int power = doc["StatusSNS"]["DZG"]["Power"];
            Serial.print(F("Power = "));
            Serial.println(power);
        }
      } else {
        Serial.printf("[SmartMeterReader] HTTP-Error: %s\n", httpClient.errorToString(httpCode).c_str());
      }
      httpClient.end();
    } else {
      Serial.println(F("[SmartMeterReader] Failed to connect to endpoint"));
    }
  }
}
