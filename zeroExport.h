#ifndef ZEROEXPORT_H
#define ZEROEXPORT_H

#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

class zeroExport {
  private:
    HTTPClient httpClient;
    WiFiClient wifiClient;
    const char* endpoint;
    uint32_t updateInterval;  // in milliseconds
    unsigned long lastUpdate;
    bool isRunning;
    DynamicJsonDocument doc{32};
  public:
    zeroExport(const char* _endpoint, uint32_t _updateInterval = 5);
    ~zeroExport();
    
    void stop();
    void handle();  // Call from main loop - performs the HTTP request if interval has passed
};

#endif
