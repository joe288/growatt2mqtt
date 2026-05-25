// Growatt Solar Inverter to MQTT
// Repo: https://github.com/nygma2004/growatt2mqtt
// author: Csongor Varga, csongor.varga@gmail.com
// 1 Phase, 2 string inverter version such as MIN 3000 TL-XE, MIC 1500 TL-X

// Libraries:
// - FastLED by Daniel Garcia
// - ModbusMaster by Doc Walker
// - ArduinoOTA
// - SoftwareSerial
// Hardware:
// - Wemos D1 mini
// - RS485 to TTL converter: https://www.aliexpress.com/item/1005001621798947.html
// - To power from mains: Hi-Link 5V power supply (https://www.aliexpress.com/item/1005001484531375.html), fuseholder and 1A fuse, and varistor

#ifdef ESP32
#include <WiFi.h>                 // Wifi connection
#include <WebServer.h>            // Web server for general HTTP response
#else
#include <ESP8266WiFi.h>          // Wifi connection
#include <ESP8266WebServer.h>     // Web server for general HTTP response
#endif
#include <PubSubClient.h>         // MQTT support
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FastLED.h>
#include "globals.h"
#include "settings.h"
#include "growattInterface.h"
#include "mqtt_discovery.h"
#include <SoftwareSerial.h>

#ifdef ESP32
WebServer server(80);
#else
ESP8266WebServer server(80);
#endif
WiFiClient espClient;
PubSubClient mqtt(mqtt_server, 1883, 0, espClient);

CRGB leds[NUM_LEDS];

SoftwareSerial sharedRS485(MAX485_RX, MAX485_TX);
growattIF growattInterface(MAX485_RE_NEG, MAX485_DE, MAX485_RX, MAX485_TX);

// SoftwareSerial BMS_RS485(BMS_MAX485_RX, BMS_MAX485_TX);

#ifdef DALY_BMS
#include "daly.h"
// DalyBms  dalyInterface(&BMS_RS485, BMS_MAX485_DE, BMS_MAX485_RE_NEG);
DalyBms  dalyInterface(BMS_MAX485_RX, BMS_MAX485_TX, BMS_MAX485_DE, BMS_MAX485_RE_NEG);
unsigned long lastDalyMillis = 0;
float dalySOC = 100;
#endif

#ifdef ZeroExport
#include "zeroExport.h"
zeroExport zeroExportReader(SmartMeterEndpoint, UPDATE_SMETER);
#endif

struct VictronDevice;
#ifdef Vicrton
#include "VictronBLE.h"
VictronBLE victron;
unsigned long lastVictronMillis = 0;
#endif

char settingsJson[1024];
char dataJson[1024];
unsigned long lastModbusMillis = 0;
unsigned long lastStatusMillis = 0;

uint8_t outputPercent = 100;
bool zeroExportActive = true;
bool inverterOn = true;
uint8_t out = 100; 
bool victronDiscoveryPublished = false;
static volatile bool victronDiscoveryRequested = false;

// Simple ring buffer to enqueue MQTT messages from BLE callback (avoid blocking network calls in BTC task)
#define VICTRON_QUEUE_SIZE 8
struct MqttMsg { char topic[128]; char payload[256]; bool retain; };
static MqttMsg victronQueue[VICTRON_QUEUE_SIZE];
static volatile uint8_t victronQueueHead = 0;
static volatile uint8_t victronQueueTail = 0;

static bool enqueueVictronMsg(const char* topic, const char* payload, bool retain) {
  uint8_t next = (victronQueueHead + 1) % VICTRON_QUEUE_SIZE;
  if (next == victronQueueTail) {
    // queue full, drop message
    return false;
  }
  strncpy(victronQueue[victronQueueHead].topic, topic, sizeof(victronQueue[victronQueueHead].topic) - 1);
  victronQueue[victronQueueHead].topic[sizeof(victronQueue[victronQueueHead].topic) - 1] = '\0';
  strncpy(victronQueue[victronQueueHead].payload, payload, sizeof(victronQueue[victronQueueHead].payload) - 1);
  victronQueue[victronQueueHead].payload[sizeof(victronQueue[victronQueueHead].payload) - 1] = '\0';
  victronQueue[victronQueueHead].retain = retain;
  // advance head
  victronQueueHead = next;
  return true;
}

static bool dequeueVictronMsg(MqttMsg &out) {
  if (victronQueueHead == victronQueueTail) return false;
  // copy out
  memcpy(&out, &victronQueue[victronQueueTail], sizeof(MqttMsg));
  victronQueueTail = (victronQueueTail + 1) % VICTRON_QUEUE_SIZE;
  return true;
}

void writeLog(const char *format, ...)
{
  char msg[100];
  va_list args;

  va_start(args, format);
  vsnprintf(msg, sizeof(msg), format, args); // do check return value
  va_end(args);

  // write msg to the log
  Serial.println(msg);
}

void ReadInputRegisters() {
  char topic[80];

  leds[0] = CRGB::Yellow;
  FastLED.show();
  uint8_t result;

  digitalWrite(STATUS_LED, 0);

  result = growattInterface.ReadInputRegisters(dataJson);
  if (result == growattInterface.Success) {
    leds[0] = CRGB::Green;
    FastLED.show();
    lastRGB = millis();
    ledoff = true;

#ifdef DEBUG_SERIAL
    Serial.println(result);
#endif
    sprintf(topic, "%s/data", topicRoot);
    mqtt.publish(topic, dataJson);
    Serial.println("Data MQTT sent");

  } else if (result != growattInterface.Continue) {
    leds[0] = CRGB::Red;
    FastLED.show();
    lastRGB = millis();
    ledoff = true;

    Serial.print(F("Error: "));
    String message = growattInterface.sendModbusError(result);
    Serial.println(message);
    char topic[80];
    sprintf(topic, "%s/error", topicRoot);
    mqtt.publish(topic, message.c_str());
    delay(5);
  }
  digitalWrite(STATUS_LED, 1);
}

void ReadHoldingRegisters() {
  char topic[80];

  leds[0] = CRGB::Yellow;
  FastLED.show();
  uint8_t result;

  digitalWrite(STATUS_LED, 0);
  result = growattInterface.ReadHoldingRegisters(settingsJson);
  if (result == growattInterface.Success)   {
    leds[0] = CRGB::Green;
    FastLED.show();
    lastRGB = millis();
    ledoff = true;

#ifdef DEBUG_SERIAL
    Serial.println(settingsJson);
#endif
    sprintf(topic, "%s/settings", topicRoot);
    mqtt.publish(topic, settingsJson);
    Serial.println("Setting MQTT sent");
    // Set the flag to true not to read the holding registers again
    holdingregisters = true;

  } else if (result != growattInterface.Continue) {
    leds[0] = CRGB::Red;
    FastLED.show();
    lastRGB = millis();
    ledoff = true;

    Serial.print(F("Error: "));
    String message = growattInterface.sendModbusError(result);
    Serial.println(message);
    char topic[80];
    sprintf(topic, "%s/error", topicRoot);
    mqtt.publish(topic, message.c_str());
    delay(5);
  }
  digitalWrite(STATUS_LED, 1);
}

// This is the 1 second timer callback function
// MQTT reconnect logic
void reconnect() {
  //String mytopic;
  // Loop until we're reconnected
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    byte mac[6];                     // the MAC address of your Wifi shield
    WiFi.macAddress(mac);
    sprintf(newclientid, "%s-%02x%02x%02x", clientID, mac[2], mac[1], mac[0]);
    Serial.print(F("Client ID: "));
    Serial.println(newclientid);
    // Attempt to connect
    char topic[80];
    sprintf(topic, "%s/%s", topicRoot, "connection");
    if (mqtt.connect(newclientid, mqtt_user, mqtt_password, topic, 1, true, "offline")) { //last will
      Serial.println(F("connected"));
      // ... and resubscribe
      mqtt.publish(topic, "online", true);
      sprintf(topic, "%s/write/#", topicRoot);
      mqtt.subscribe(topic);
      
      // Publish Home Assistant MQTT discovery messages
      #ifdef HA_ENABLE_DISCOVERY
        publishHADiscovery(mqtt, clientID, newclientid, topicRoot, buildversion);
      #endif
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(mqtt.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

#ifdef DALY_BMS
void dalyCallback() {
  dalySOC = dalyInterface.get.packSOC;
  // Serial.println("Daly BMS callback called, sending MQTT message...");
  if (mqtt.connected()) {
    char topic[80];
    char json[1024];
    sprintf(json,
      "{"
      "\"Voltage\":%.1f,"
      "\"Current\":%.1f,"
      "\"Power\":%.1f,"
      "\"SOC\":%.1f,"
      "\"Remaining_Ah\":%.1f,"
      "\"Remaining_kWh\":%.3f,"
      "\"Cycles\":%d,"
      "\"BMS_Temp\":%d,"
      "\"Cell_Temp\":%d,"
      "\"cell_hVt\":%.3f,"
      "\"cell_lVt\":%.3f,"
      "\"cell_hVt2\":%.3f,"
      "\"cell_lVt2\":%.3f,"
      "\"pack_hVt\":%.1f,"
      "\"pack_lVt\":%.1f,"
      "\"pack_hVt2\":%.1f,"
      "\"pack_lVt2\":%.1f,"
      "\"High_CellNr\":%d,"
      "\"High_CellV\":%.3f,"
      "\"Low_CellNr\":%d,"
      "\"Low_CellV\":%.3f,"
      "\"Cell_Diff\":%d,"
      "\"DischargeFET\":%s,"
      "\"ChargeFET\":%s,"
      "\"Status\":\"%s\","
      "\"Cells\":%d,"
      "\"Heartbeat\":%d,"
      "\"Balance_Active\":%s,"
      "\"Fail_Codes\":\"%s\""
      "}",
      dalyInterface.get.packVoltage,
      dalyInterface.get.packCurrent,
      dalyInterface.get.packCurrent * dalyInterface.get.packVoltage,
      dalyInterface.get.packSOC,
      dalyInterface.get.resCapacityAh,
      (dalyInterface.get.resCapacityAh * dalyInterface.get.packVoltage) / 1000,
      dalyInterface.get.bmsCycles,
      dalyInterface.get.tempAverage,
      dalyInterface.get.cellTemperature[0],
      dalyInterface.get.maxCellThreshold1 * 0.001,
      dalyInterface.get.minCellThreshold1 * 0.001,
      dalyInterface.get.maxCellThreshold2 * 0.001,
      dalyInterface.get.minCellThreshold2 * 0.001,
      dalyInterface.get.maxPackThreshold1 * 0.1,
      dalyInterface.get.minPackThreshold1 * 0.1,
      dalyInterface.get.maxPackThreshold2 * 0.1,
      dalyInterface.get.minPackThreshold2 * 0.1,
      dalyInterface.get.maxCellVNum,
      dalyInterface.get.maxCellmV * 0.001,
      dalyInterface.get.minCellVNum,
      dalyInterface.get.minCellmV * 0.001,
      dalyInterface.get.cellDiff,
      dalyInterface.get.disChargeFetState ? "true" : "false",
      dalyInterface.get.chargeFetState    ? "true" : "false",
      dalyInterface.get.chargeDischargeStatus,
      dalyInterface.get.numberOfCells,
      dalyInterface.get.bmsHeartBeat,
      dalyInterface.get.cellBalanceActive  ? "true" : "false",
      dalyInterface.failCodeArr.c_str()
    );
    sprintf(topic, "%s/bms", topicRoot);
    mqtt.publish(topic, json);
    Serial.println("BMS MQTT sent");
  }
}
#endif

#ifdef Vicrton
void victronCallback(const VictronDevice* dev) {
    Serial.printf("Received data from %s (%s), RSSI: %d dBm\n", dev->name, dev->mac, dev->rssi);
    if (dev->deviceType == DEVICE_TYPE_SOLAR_CHARGER) {
        Serial.printf("Solar %s: %.2fV %.2fA %dW %d %d\n",
            dev->name,
            dev->solar.batteryVoltage,
            dev->solar.batteryCurrent*10,
            (int)dev->solar.panelPower,
            getChargeStateString(dev->solar.chargeState),
            dev->solar.yieldToday);

        // Enqueue MQTT publish to avoid calling network functions from the BTC task (stack overflow)
        char topic[128];
        char payload[256];

        sprintf(topic, "%s/%s", topicRoot, dev->mac);
        sprintf(payload,
          "{\"name\":\"%s\",\"mac\":\"%s\",\"rssi\":%d,\"batteryVoltage\":%.2f,\"batteryCurrent\":%.1f,\"panelPower\":%d,\"chargeState\":\"%s\",\"yieldToday\":%d}",
          dev->name,
          dev->mac,
          dev->rssi,
          dev->solar.batteryVoltage,
          dev->solar.batteryCurrent * 10,
          (int)dev->solar.panelPower,
          getChargeStateString(dev->solar.chargeState),
          dev->solar.yieldToday);

        if (!enqueueVictronMsg(topic, payload, true)) {
          // queue full: drop or log
          Serial.println("Victron queue full, dropping message");
        }

        if (!victronDiscoveryPublished) {
          // request discovery publish from main loop instead of doing it from BTC task
          victronDiscoveryRequested = true;
        }
  }
}
#endif

void setup() {
  FastLED.addLeds<LED_TYPE, RGBLED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  leds[0] = CRGB::Pink;
  FastLED.show();

  Serial.begin(SERIAL_RATE);
  Serial.println(F("\nGrowatt Solar Inverter to MQTT Gateway"));
  // Init outputs, RS485 in receive mode
  pinMode(STATUS_LED, OUTPUT);

  // Initialize some variables
  uptime = 0;
  seconds = 0;
  leds[0] = CRGB::Pink;
  FastLED.show();

  // Connect to Wifi
  Serial.print(F("Connecting to Wifi"));
  WiFi.mode(WIFI_STA);

#ifdef FIXEDIP
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
#endif

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
    seconds++;
    if (seconds > 180) {
      // reboot the ESP if cannot connect to wifi
      ESP.restart();
    }
  }
  seconds = 0;
  Serial.println("");
  Serial.println(F("Connected to wifi network"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("Signal [RSSI]: "));
  Serial.println(WiFi.RSSI());

  // Set up the Modbus line
  sharedRS485.begin(9600);  // Beide Protokolle laufen auf 9600 Baud ✓
  growattInterface.initGrowatt(&sharedRS485);

  #ifdef DALY_BMS
  dalyInterface.Init();
  dalyInterface.callback(dalyCallback);
  #endif

  Serial.println("Modbus connection is set up");

  server.on("/", []() {                       // Dummy page
    server.send(200, "text/plain", "Growatt Solar Inverter to MQTT Gateway");
  });
  server.begin();
  Serial.println(F("HTTP server started"));

  // Set up the MQTT server connection
  if (mqtt_server != "") {
    mqtt.setServer(mqtt_server, 1883);
    mqtt.setBufferSize(1024);
    mqtt.setCallback(callback);
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  byte mac[6];                     // the MAC address of your Wifi shield
  WiFi.macAddress(mac);
  char value[80];
  sprintf(value, "%s-%02x%02x%02x", clientID, mac[2], mac[1], mac[0]);
  ArduinoOTA.setHostname(value);

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  leds[0] = CRGB::Black;
  FastLED.show();

  #ifdef Vicrton
    victron.begin(5); // 5 second scan duration
    victron.setCallback(victronCallback);

    // Add your device (replace with your MAC and key)
    victron.addDevice(
        "My MPPT",                          // Name
        "E2:EE:A7:DA:D8:01",                // MAC address
        "af909c4d3dd13a0ccf5d38e6b1b267c0", // Encryption key
        DEVICE_TYPE_SOLAR_CHARGER           // Device type (optional, auto-detected)
    );
    // victron.setDebug(true);
    Serial.printf("Configured %d BLE devices\n", (int)victron.getDeviceCount());

    Serial.println("Setup complete, starting BLE scan...");
  #endif
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Convert the incoming byte array to a string

  int i = 0;
  uint8_t result;
  for (i = 0; i < length; i++) {        // each char to upper
    payload[i] = toupper(payload[i]);
  }
  payload[length] = '\0';               // Null terminator used to terminate the char array
  String message = (char*)payload;

  char expectedTopic[40];

  sprintf(expectedTopic, "%s/write/getSettings", topicRoot);
  if (strcmp(expectedTopic, topic) == 0) {
    if (strcmp((char *)payload, "ON") == 0) {
      holdingregisters = false;
    }
  }

  sprintf(expectedTopic, "%s/write/setEnable", topicRoot);
  if (strcmp(expectedTopic, topic) == 0) {
    char json[50];
    char topic[80];

    if (strcmp((char *)payload, "ON") == 0) {
      growattInterface.writeRegister(growattInterface.regOnOff, 1);
      delay(5);
      sprintf(json, "{ \"enable\":%d}", growattInterface.readRegister(growattInterface.regOnOff));
      sprintf(topic, "%s/settings", topicRoot);
      mqtt.publish(topic, json);
    } else if (strcmp((char *)payload, "OFF") == 0) {
      growattInterface.writeRegister(growattInterface.regOnOff, 0);
      delay(5);
      sprintf(json, "{ \"enable\":%d}", growattInterface.readRegister(growattInterface.regOnOff));
      sprintf(topic, "%s/settings", topicRoot);
      mqtt.publish(topic, json);
    }
  }

  sprintf(expectedTopic, "%s/write/setMaxOutput", topicRoot);
  if (strcmp(expectedTopic, topic) == 0) {
    char json[50];
    char topic[80];

    result = growattInterface.writeRegister(growattInterface.regMaxOutputActive, message.toInt());
    if (result == growattInterface.Success) {
      holdingregisters = false;
    } else {
      sprintf(json, "last trasmition has faild with: %s", growattInterface.sendModbusError(result).c_str());
      sprintf(topic, "%s/error", topicRoot);
      mqtt.publish(topic, json);
    }
  }

  sprintf(expectedTopic, "%s/write/setTrakerModel", topicRoot);
  if (strcmp(expectedTopic, topic) == 0) {
    char json[50];
    char topic[80];

    result = growattInterface.writeRegister(growattInterface.regTrakerModel, message.toInt());
    if (result == growattInterface.Success) {
      holdingregisters = false;
    } else {
      sprintf(json, "last trasmition has faild with: %s", growattInterface.sendModbusError(result).c_str());
      sprintf(topic, "%s/error", topicRoot);
      mqtt.publish(topic, json);
    }
  }

  sprintf(expectedTopic, "%s/write/setStartVoltage", topicRoot);
  if (strcmp(expectedTopic, topic) == 0) {
    char json[50];
    char topic[80];

    result = growattInterface.writeRegister(growattInterface.regStartVoltage, (message.toInt() * 10)); //*10 transmit with one digit after decimal place
    if (result == growattInterface.Success) {
      holdingregisters = false;
    } else {
      sprintf(json, "last trasmition has faild with: %s", growattInterface.sendModbusError(result).c_str());
      sprintf(topic, "%s/error", topicRoot);
      mqtt.publish(topic, json);
    }
  }

#ifdef useModulPower
  sprintf(expectedTopic, "%s/write/setModulPower", topicRoot);
  if (strcmp(expectedTopic, topic) == 0) {
    char json[50];
    char topic[80];

    growattInterface.writeRegister(growattInterface.regOnOff, 0);
    delay(500);

    result = growattInterface.writeRegister(growattInterface.regModulPower, int(strtol(message.c_str(), NULL, 16)));
    delay(500);
    growattInterface.writeRegister(growattInterface.regOnOff, 1);
    delay(1500);

    if (result == growattInterface.Success) {
      holdingregisters = false;
    } else {
      sprintf(json, "last trasmition has faild with: %s", growattInterface.sendModbusError(result).c_str());
      sprintf(topic, "%s/error", topicRoot);
      mqtt.publish(topic, json);
    }
  }
#endif

#ifdef DEBUG_SERIAL
  Serial.print(F("Message arrived on topic: ["));
  Serial.print(topic);
  Serial.print(F("], "));
  Serial.println(message);
#endif
}

void loop() {
  // Handle HTTP server requests
  server.handleClient();
  ArduinoOTA.handle();

  // Handle SmartMeterReader (non-blocking, performs HTTP request if interval elapsed)
#ifdef DALY_BMS 
  if (dalySOC < 15) {
    zeroExportActive = false;
    if (inverterOn) {
      inverterOn = false;
      growattInterface.writeRegister(growattInterface.regOnOff, 0);
      delay(100);
    }
  } else if (dalySOC > 18) {
    if (!inverterOn) {
      inverterOn = true;
      growattInterface.writeRegister(growattInterface.regOnOff, 1);
      delay(100);
    }
    zeroExportActive = true;
  }
#endif
#ifdef ZeroExport
  if (zeroExportActive) {
    zeroExportReader.handle(dataJson,settingsJson,&out);
  }
#endif
#ifdef Growatt
  if(out != outputPercent ){  
    outputPercent = out;  
    uint8_t result = growattInterface.writeRegister(growattInterface.regMaxOutputActive, outputPercent);
    if (result == growattInterface.Success)
      holdingregisters = false;
  }
#endif
  // Handle MQTT connection/reconnection
  if (mqtt_server != "") {
    if (!mqtt.connected()) {
      reconnect();
    }
    mqtt.loop();

    // If BLE requested Home Assistant discovery, publish it from main loop (safe stack)
    if (victronDiscoveryRequested && mqtt.connected() && !victronDiscoveryPublished) {
      publishHADiscovery(mqtt, clientID, newclientid, topicRoot, buildversion);
      victronDiscoveryPublished = true;
      victronDiscoveryRequested = false;
    }

    // Publish queued Victron MQTT messages from main loop (avoids stack overflow in BTC task)
    {
      MqttMsg msg;
      while (mqtt.connected() && dequeueVictronMsg(msg)) {
        mqtt.publish(msg.topic, msg.payload, msg.retain);
        Serial.println(F("Victron MQTT sent"));
      }
    }
  }

  unsigned long now = millis();
#ifdef Growatt
  if (now - lastModbusMillis >= (unsigned long)UPDATE_MODBUS * 1000UL) {
    lastModbusMillis = now;
    if (!holdingregisters) {
      ReadHoldingRegisters();
    } else {
      ReadInputRegisters();
    }
  }
#endif

  if (now - lastStatusMillis >= (unsigned long)UPDATE_STATUS * 1000UL) {
    lastStatusMillis = now;
    if (mqtt_server != "") {
      char topic[80];
      char value[300];
      sprintf(value, "{\"rssi\": %d, \"uptime\": %d, \"ssid\": \"%s\", \"ip\": \"%d.%d.%d.%d\", \"clientid\":\"%s\", \"version\":\"%s\"}", WiFi.RSSI(), uptime, WiFi.SSID().c_str(), WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3], newclientid, buildversion);
      sprintf(topic, "%s/%s", topicRoot, "status");
      mqtt.publish(topic, value);
      Serial.println(F("MQTT status sent"));
    }
  }

#ifdef DALY_BMS
  if (now - lastDalyMillis >= (unsigned long)UPDATE_DALY * 1000UL) {
    lastDalyMillis = now;
    dalyInterface.loop();
  }
#endif

#ifdef Vicrton
  if (now - lastVictronMillis >= (unsigned long)UPDATE_VICTRON * 1000UL) {
    lastVictronMillis = now;
    victron.loop();
  }
#endif

  // Uptime calculation
  if (millis() - lastTick >= 60000) {
    lastTick = millis();
    uptime++;
  }

  if (millis() - lastWifiCheck >= WIFICHECK) {
    // reconnect to the wifi network if connection is lost
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Reconnecting to wifi...");
      WiFi.reconnect();
    }
    lastWifiCheck = millis();
  }

  if (ledoff && (millis() - lastRGB >= RGBSTATUSDELAY)) {
    ledoff = false;
    leds[0] = CRGB::Black;
    FastLED.show();
  }
}
