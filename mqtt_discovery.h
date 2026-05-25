// Home Assistant MQTT Discovery functions for Growatt Solar Inverter
// This file contains all MQTT discovery configuration messages

#ifndef MQTT_DISCOVERY_H
#define MQTT_DISCOVERY_H

void publishHADiscovery(PubSubClient &mqtt, const char* baseClientID, const char* uniqueClientID, const char* topicRoot, const char* buildversion) {
  char discTopic[128];
  char payload[768];

  // Solar power
  sprintf(discTopic, "homeassistant/sensor/%s_solarpower/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Solar Power\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_solarpower\",\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.solarpower }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Output power
  sprintf(discTopic, "homeassistant/sensor/%s_outputpower/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Output Power\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_outputpower\",\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.outputpower }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Grid voltage
  sprintf(discTopic, "homeassistant/sensor/%s_gridvoltage/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Grid Voltage\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_gridvoltage\",\"unit_of_measurement\":\"V\",\"device_class\":\"voltage\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.gridvoltage }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Grid frequency
  sprintf(discTopic, "homeassistant/sensor/%s_gridfrequency/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Grid Frequency\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_gridfrequency\",\"unit_of_measurement\":\"Hz\",\"device_class\":\"frequency\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.gridfrequency }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Energy today (kWh)
  sprintf(discTopic, "homeassistant/sensor/%s_energytoday/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Energy Today\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_energytoday\",\"unit_of_measurement\":\"kWh\",\"device_class\":\"energy\",\"state_class\":\"total\",\"value_template\":\"{{ value_json.energytoday }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Total energy
  sprintf(discTopic, "homeassistant/sensor/%s_energytotal/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Energy Total\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_energytotal\",\"unit_of_measurement\":\"kWh\",\"device_class\":\"energy\",\"state_class\":\"total_increasing\",\"value_template\":\"{{ value_json.energytotal }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Inverter temperature
  sprintf(discTopic, "homeassistant/sensor/%s_tempinverter/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Inverter Temp\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_tempinverter\",\"unit_of_measurement\":\"°C\",\"device_class\":\"temperature\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.tempinverter }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV1 voltage
  sprintf(discTopic, "homeassistant/sensor/%s_pv1voltage/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV1 Voltage\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv1voltage\",\"unit_of_measurement\":\"V\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.pv1voltage }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV1 current
  sprintf(discTopic, "homeassistant/sensor/%s_pv1current/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV1 Current\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv1current\",\"unit_of_measurement\":\"A\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.pv1current }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV1 power
  sprintf(discTopic, "homeassistant/sensor/%s_pv1power/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV1 Power\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv1power\",\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.pv1power }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Status
  sprintf(discTopic, "homeassistant/sensor/%s_status/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Status\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_status\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.status }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV2 voltage
  sprintf(discTopic, "homeassistant/sensor/%s_pv2voltage/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV2 Voltage\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv2voltage\",\"enabled_by_default\":false,\"unit_of_measurement\":\"V\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.pv2voltage }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV2 current
  sprintf(discTopic, "homeassistant/sensor/%s_pv2current/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV2 Current\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv2current\",\"enabled_by_default\":false,\"unit_of_measurement\":\"A\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.pv2current }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV2 power
  sprintf(discTopic, "homeassistant/sensor/%s_pv2power/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV2 Power\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv2power\",\"enabled_by_default\":false,\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.pv2power }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Total work time
  sprintf(discTopic, "homeassistant/sensor/%s_totalworktime/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Total Work Time\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_totalworktime\",\"unit_of_measurement\":\"s\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.totalworktime }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV1 energy today
  sprintf(discTopic, "homeassistant/sensor/%s_pv1energytoday/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV1 Energy Today\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv1energytoday\",\"unit_of_measurement\":\"kWh\",\"device_class\":\"energy\",\"state_class\":\"total\",\"value_template\":\"{{ value_json.pv1energytoday }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV1 energy total
  sprintf(discTopic, "homeassistant/sensor/%s_pv1energytotal/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV1 Energy Total\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv1energytotal\",\"unit_of_measurement\":\"kWh\",\"device_class\":\"energy\",\"state_class\":\"total_increasing\",\"value_template\":\"{{ value_json.pv1energytotal }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV2 energy today
  sprintf(discTopic, "homeassistant/sensor/%s_pv2energytoday/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV2 Energy Today\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv2energytoday\",\"enabled_by_default\":false,\"unit_of_measurement\":\"kWh\",\"device_class\":\"energy\",\"state_class\":\"total\",\"value_template\":\"{{ value_json.pv2energytoday }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // PV2 energy total
  sprintf(discTopic, "homeassistant/sensor/%s_pv2energytotal/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s PV2 Energy Total\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_pv2energytotal\",\"enabled_by_default\":false,\"unit_of_measurement\":\"kWh\",\"device_class\":\"energy\",\"state_class\":\"total_increasing\",\"value_template\":\"{{ value_json.pv2energytotal }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Output full power
  sprintf(discTopic, "homeassistant/sensor/%s_opfullpower/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Output Full Power\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_opfullpower\",\"enabled_by_default\":false,\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.opfullpower }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // IPM temperature
  sprintf(discTopic, "homeassistant/sensor/%s_tempipm/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s IPM Temp\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_tempipm\",\"unit_of_measurement\":\"°C\",\"device_class\":\"temperature\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.tempipm }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Boost temperature
  sprintf(discTopic, "homeassistant/sensor/%s_tempboost/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Boost Temp\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_tempboost\",\"unit_of_measurement\":\"°C\",\"device_class\":\"temperature\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.tempboost }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Input power factor
  sprintf(discTopic, "homeassistant/sensor/%s_ipf/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Input PF\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_ipf\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.ipf }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Real operation percent
  sprintf(discTopic, "homeassistant/sensor/%s_realoppercent/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Real Op Percent\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_realoppercent\",\"unit_of_measurement\":\"%%\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.realoppercent }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Derating mode
  sprintf(discTopic, "homeassistant/sensor/%s_deratingmode/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Derating Mode\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_deratingmode\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.deratingmode }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Fault code
  sprintf(discTopic, "homeassistant/sensor/%s_faultcode/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Fault Code\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_faultcode\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.faultcode }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Fault bit code
  sprintf(discTopic, "homeassistant/sensor/%s_faultbitcode/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Fault Bit Code\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_faultbitcode\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.faultbitcode }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Warning bit code
  sprintf(discTopic, "homeassistant/sensor/%s_warningbitcode/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Warning Bit Code\",\"state_topic\":\"%s/data\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_warningbitcode\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.warningbitcode }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

#ifdef Vicrton
  // Victron Solar Charger: Battery Voltage
  sprintf(discTopic, "homeassistant/sensor/%s_victron_battery_voltage/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Victron Battery Voltage\",\"state_topic\":\"%svictron/%s\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_victron_battery_voltage\",\"unit_of_measurement\":\"V\",\"device_class\":\"voltage\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.batteryVoltage }}\",\"device\":{\"identifiers\":[\"%s_victron\"],\"name\":\"%s Victron Solar Charger\",\"model\":\"Victron Solar Charger\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, uniqueClientID, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Victron Solar Charger: Battery Current
  sprintf(discTopic, "homeassistant/sensor/%s_victron_battery_current/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Victron Battery Current\",\"state_topic\":\"%svictron/%s\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_victron_battery_current\",\"unit_of_measurement\":\"A\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.batteryCurrent }}\",\"device\":{\"identifiers\":[\"%s_victron\"],\"name\":\"%s Victron Solar Charger\",\"model\":\"Victron Solar Charger\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, uniqueClientID, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Victron Solar Charger: Panel Power
  sprintf(discTopic, "homeassistant/sensor/%s_victron_panel_power/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Victron Panel Power\",\"state_topic\":\"%svictron/%s\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_victron_panel_power\",\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.panelPower }}\",\"device\":{\"identifiers\":[\"%s_victron\"],\"name\":\"%s Victron Solar Charger\",\"model\":\"Victron Solar Charger\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, uniqueClientID, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Victron Solar Charger: Yield Today
  sprintf(discTopic, "homeassistant/sensor/%s_victron_yield_today/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Victron Yield Today\",\"state_topic\":\"%svictron/%s\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_victron_yield_today\",\"unit_of_measurement\":\"Wh\",\"device_class\":\"energy\",\"state_class\":\"total\",\"value_template\":\"{{ value_json.yieldToday }}\",\"device\":{\"identifiers\":[\"%s_victron\"],\"name\":\"%s Victron Solar Charger\",\"model\":\"Victron Solar Charger\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, uniqueClientID, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Victron Solar Charger: Charge State
  sprintf(discTopic, "homeassistant/sensor/%s_victron_charge_state/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Victron Charge State\",\"state_topic\":\"%svictron/%s\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_victron_charge_state\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.chargeState }}\",\"device\":{\"identifiers\":[\"%s_victron\"],\"name\":\"%s Victron Solar Charger\",\"model\":\"Victron Solar Charger\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, uniqueClientID, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);
#endif
#ifdef DALY_BMS
  // Daly BMS: Voltage
  sprintf(discTopic, "homeassistant/sensor/%s_daly_voltage/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Voltage\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_voltage\",\"unit_of_measurement\":\"V\",\"device_class\":\"voltage\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Voltage }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Current
  sprintf(discTopic, "homeassistant/sensor/%s_daly_current/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Current\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_current\",\"unit_of_measurement\":\"A\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Current }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Power
  sprintf(discTopic, "homeassistant/sensor/%s_daly_power/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Power\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_power\",\"unit_of_measurement\":\"W\",\"device_class\":\"power\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Power }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: SOC
  sprintf(discTopic, "homeassistant/sensor/%s_daly_soc/config", uniqueClientID);
  sprintf(payload,
  "{\"name\":\"%s Daly SOC\","
  "\"state_topic\":\"%s/bms\","
  "\"availability_topic\":\"%s/connection\","
  "\"unique_id\":\"%s_daly_soc\","
  "\"unit_of_measurement\":\"%%\","
  "\"state_class\":\"measurement\","
  "\"value_template\":\"{{ value_json.SOC | float(0) }}\","
  "\"device\":{"
    "\"identifiers\":[\"%s_daly\"],"
    "\"name\":\"%s Daly BMS\","
    "\"model\":\"Daly BMS\","
    "\"sw_version\":\"%s\""
  "}"
  "}",
  baseClientID,
  topicRoot,
  topicRoot,
  uniqueClientID,
  uniqueClientID,
  baseClientID,
  buildversion
);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Remaining Ah
  sprintf(discTopic, "homeassistant/sensor/%s_daly_remaining_ah/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Remaining Ah\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_remaining_ah\",\"unit_of_measurement\":\"Ah\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Remaining_Ah }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Remaining kWh
  sprintf(discTopic, "homeassistant/sensor/%s_daly_remaining_kwh/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Remaining kWh\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_remaining_kwh\",\"unit_of_measurement\":\"kWh\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Remaining_kWh }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Cycles
  sprintf(discTopic, "homeassistant/sensor/%s_daly_cycles/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Cycles\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_cycles\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Cycles }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: BMS Temp
  sprintf(discTopic, "homeassistant/sensor/%s_daly_bms_temp/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly BMS Temp\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_bms_temp\",\"unit_of_measurement\":\"°C\",\"device_class\":\"temperature\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.BMS_Temp }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Cell Temp
  sprintf(discTopic, "homeassistant/sensor/%s_daly_cell_temp/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Cell Temp\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_cell_temp\",\"unit_of_measurement\":\"°C\",\"device_class\":\"temperature\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Cell_Temp }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: High Cell Nr
  sprintf(discTopic, "homeassistant/sensor/%s_daly_high_cell_nr/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly High Cell Nr\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_high_cell_nr\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.High_CellNr }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: High Cell V
  sprintf(discTopic, "homeassistant/sensor/%s_daly_high_cell_v/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly High Cell V\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_high_cell_v\",\"unit_of_measurement\":\"V\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.High_CellV }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Low Cell Nr
  sprintf(discTopic, "homeassistant/sensor/%s_daly_low_cell_nr/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Low Cell Nr\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_low_cell_nr\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Low_CellNr }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Low Cell V
  sprintf(discTopic, "homeassistant/sensor/%s_daly_low_cell_v/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Low Cell V\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_low_cell_v\",\"unit_of_measurement\":\"V\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.Low_CellV }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Cell Diff
  sprintf(discTopic, "homeassistant/sensor/%s_daly_cell_diff/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Cell Diff\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_cell_diff\",\"unit_of_measurement\":\"mV\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Cell_Diff }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Discharge FET
  sprintf(discTopic, "homeassistant/sensor/%s_daly_discharge_fet/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Discharge FET\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_discharge_fet\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.DischargeFET }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Charge FET
  sprintf(discTopic, "homeassistant/sensor/%s_daly_charge_fet/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Charge FET\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_charge_fet\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.ChargeFET }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Status
  sprintf(discTopic, "homeassistant/sensor/%s_daly_status/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Status\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_status\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Status }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Cells
  sprintf(discTopic, "homeassistant/sensor/%s_daly_cells/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Cells\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_cells\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Cells }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Heartbeat
  sprintf(discTopic, "homeassistant/sensor/%s_daly_heartbeat/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Heartbeat\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_heartbeat\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Heartbeat }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Balance Active
  sprintf(discTopic, "homeassistant/sensor/%s_daly_balance_active/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Balance Active\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_balance_active\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Balance_Active }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Daly BMS: Fail Codes
  sprintf(discTopic, "homeassistant/sensor/%s_daly_fail_codes/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Daly Fail Codes\",\"state_topic\":\"%s/bms\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_daly_fail_codes\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.Fail_Codes }}\",\"device\":{\"identifiers\":[\"%s_daly\"],\"name\":\"%s Daly BMS\",\"model\":\"Daly BMS\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);
#endif

  // Diagnostics: RSSI
  sprintf(discTopic, "homeassistant/sensor/%s_rssi/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s RSSI\",\"state_topic\":\"%s/status\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_rssi\",\"unit_of_measurement\":\"dBm\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.rssi }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Diagnostics: Uptime
  sprintf(discTopic, "homeassistant/sensor/%s_uptime/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Uptime\",\"state_topic\":\"%s/status\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_uptime\",\"unit_of_measurement\":\"s\",\"state_class\":\"measurement\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.uptime }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Diagnostics: SSID
  sprintf(discTopic, "homeassistant/sensor/%s_ssid/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s SSID\",\"state_topic\":\"%s/status\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_ssid\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.ssid }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Diagnostics: IP
  sprintf(discTopic, "homeassistant/sensor/%s_ip/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s IP\",\"state_topic\":\"%s/status\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_ip\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.ip }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Diagnostics: clientid
  sprintf(discTopic, "homeassistant/sensor/%s_clientid/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Client ID\",\"state_topic\":\"%s/status\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_clientid\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.clientid }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Diagnostics: version
  sprintf(discTopic, "homeassistant/sensor/%s_version/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Version\",\"state_topic\":\"%s/status\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_version\",\"entity_category\":\"diagnostic\",\"value_template\":\"{{ value_json.version }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);

  // Max Output Active Power % (from settings)
  sprintf(discTopic, "homeassistant/sensor/%s_maxoutputactivepp/config", uniqueClientID);
  sprintf(payload, "{\"name\":\"%s Max Output Active Power %%\",\"state_topic\":\"%s/settings\",\"availability_topic\":\"%s/connection\",\"unique_id\":\"%s_maxoutputactivepp\",\"unit_of_measurement\":\"%%\",\"state_class\":\"measurement\",\"value_template\":\"{{ value_json.maxoutputactivepp }}\",\"device\":{\"identifiers\":[\"%s\"],\"name\":\"%s\",\"model\":\"Growatt Inverter\",\"sw_version\":\"%s\"}}", baseClientID, topicRoot, topicRoot, uniqueClientID, uniqueClientID, baseClientID, buildversion);
  mqtt.publish(discTopic, payload, true);
  delay(50);
}

#endif
