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
void zeroExport::handle(char dataJson[1024], char settingsJson[1024], uint8_t *output) {
  // memset(dataJson, 0, sizeof(dataJson));
  // sprintf(dataJson, "{\"status\":1,\"solarpower\":1029.0,\"pv1voltage\":137.6,\"pv1current\":7.5,\"pv1power\":1029.0,\"pv2voltage\":0.0,\"pv2current\":0.0,\"pv2power\":0.0,\"outputpower\":1008.1,\"gridfrequency\":50.01,\"gridvoltage\":247.8,\"energytoday\":2.6,\"energytotal\":5567.3,\"totalworktime\":55985404.0,\"pv1energytoday\":2.6,\"pv1energytotal\":5634.4,\"pv2energytoday\":0.0,\"pv2energytotal\":0.0,\"opfullpower\":0.0,\"tempinverter\":41.0,\"tempipm\":41.0,\"tempboost\":0.0,\"ipf\":20000,\"realoppercent\":0,\"deratingmode\":0,\"faultcode\":0,\"faultbitcode\":0,\"warningbitcode\":0}");
  // memset(settingsJson, 0, sizeof(settingsJson));
  // sprintf(settingsJson, "{\"enable\":1,\"safetyfuncen\":509,\"maxoutputactivepp\":90,\"maxoutputreactivepp\":0,\"maxpower\":1500.0,\"voltnormal\":100.0,\"startvoltage\":50.0,\"gridvoltlowlimit\":184.0,\"gridvolthighlimit\":287.5,\"gridfreqlowlimit\":47.5,\"gridfreqhighlimit\":51.5,\"gridvoltlowconnlimit\":195.5,\"gridvolthighconnlimit\":253.0,\"gridfreqlowconnlimit\":47.7,\"gridfreqhighconnlimit\":50.1,\"firmware\":\"GH1.0\",\"controlfirmware\":\"ZAAa\",\"serial\":\"\",\"modulPower\":\"000F\"}");
  
  if (!isRunning) {
    return;              // Not running, do nothing
  }
   
  // Check if it's time to update
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    int smartmeter;
    float solarpower;
    float maxpower;

    if (readSmartMeter(&smartmeter) != 0) {
     *output = 100;  // Default to 100% output if smart meter reading fails
    }

    DeserializationError err = deserializeJson(doc, dataJson);
    solarpower = doc["solarpower"].as<float>();
    err = deserializeJson(doc, settingsJson);
    maxpower = doc["maxpower"].as<float>();
    
    float outPercent = 0.0f;
    if (maxpower > 0.0f) {
      outPercent = ((solarpower + (float)smartmeter) / maxpower) * 100.0f;
    }
    if (outPercent < 0.0f) outPercent = 0.0f;
    if (outPercent > 100.0f) outPercent = 100.0f;
    *output = (uint8_t)(outPercent + 0.5f);

    #ifdef DEBUG_SERIAL
    Serial.printf("Smartmeter: %d\r\n", smartmeter);
    Serial.print(F("Solarpower: "));
    Serial.println(solarpower);
    Serial.print(F("Maxpower: "));
    Serial.println(maxpower);
    Serial.print(F("Output: "));
    Serial.println(*output);
    #endif   
  }
}

int zeroExport::readSmartMeter(int *result) {
  // Perform the HTTP request
    if (httpClient.begin(wifiClient, endpoint)) {
      int httpCode = httpClient.GET();
      if (httpCode == HTTP_CODE_OK) {
        String payload = httpClient.getString();
        DeserializationError err = deserializeJson(doc, payload);
        if (!err) {
            *result = doc["StatusSNS"]["DZG"]["Power"];
        }
      } else {
        Serial.printf("[SmartMeterReader] HTTP-Error: %s\n", httpClient.errorToString(httpCode).c_str());
        return httpCode;
      }
      httpClient.end();
      return 0;
    } else {
      Serial.println(F("[SmartMeterReader] Failed to connect to endpoint"));
      return -1;
    }
}