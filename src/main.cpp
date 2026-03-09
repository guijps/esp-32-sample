#include "config.h"
#include <Arduino.h>
#include "../lib/communication/mqtt_communication.h"
//mosquitto_sub -h 10.205.246.137 -t "#" -v
// Pin constants
const int sensorPin = 34;
const int ledPin = 5;

// Light sensor variables
int lightInit;
int lightVal;



MQTTCommunication mqtt(ssid_net, password, mqtt_server);

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  char msg[length + 1];
  memcpy(msg, payload, length);
  msg[length] = '\0';
  Serial.print("Received [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(msg);
  mqtt.storeLastMessage(msg);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");
  lightInit = analogRead(sensorPin);
  mqtt.setCallback(mqttCallback);
  mqtt.initialize();
  Serial.println("WiFi and MQTT connected!");
}

void loop()
{
  mqtt.loop();

  static unsigned long lastSend = 0;
  unsigned long now = millis();
  if (now - lastSend >= 1000) {
    lightVal = analogRead(sensorPin);
    char msg[32];
    snprintf(msg, sizeof(msg), "%d", lightVal);
    mqtt.sendData(msg);
    Serial.print("Sent to MQTT: ");
    Serial.println(msg);
    lastSend = now;
  }
}