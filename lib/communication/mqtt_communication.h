#ifndef MQTT_COMMUNICATION_H
#define MQTT_COMMUNICATION_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "generic_communication.h"

class MQTTCommunication : public GenericCommunication {
public:
    MQTTCommunication(const char* ssid, const char* password, const char* mqtt_server,
                      const char* publish_topic = "esp32/sensor", const char* subscribe_topic = "esp32/cmd",
                      int mqtt_port = 1883)
        : ssid_(ssid), password_(password), mqtt_server_(mqtt_server),
          publish_topic_(publish_topic), subscribe_topic_(subscribe_topic),
          mqtt_port_(mqtt_port), client_(wifiClient_) {}

    void initialize() override {
        WiFi.begin(ssid_, password_);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        }
        client_.setServer(mqtt_server_, mqtt_port_);
        reconnect();
    }

    void sendData(const char* data) override {
        if (!client_.connected()) {
            reconnect();
        }
        client_.publish(publish_topic_, data);
    }

    const char* receiveData() override {
        return lastMessage_;
    }

    void loop() {
        if (!client_.connected()) {
            reconnect();
        }
        client_.loop();
    }

    void setCallback(MQTT_CALLBACK_SIGNATURE) {
        client_.setCallback(callback);
    }

    void subscribe() {
        client_.subscribe(subscribe_topic_);
    }

    void storeLastMessage(const char* message) {
        strncpy(lastMessage_, message, sizeof(lastMessage_) - 1);
        lastMessage_[sizeof(lastMessage_) - 1] = '\0';
    }

    bool isConnected() {
        return client_.connected();
    }

private:
    void reconnect() {
        int retries = 0;
        while (!client_.connected() && retries < 5) {
            if (client_.connect("ESP32Client")) {
                client_.subscribe(subscribe_topic_);
            } else {
                delay(500);
                retries++;
            }
        }
    }

    const char* ssid_;
    const char* password_;
    const char* mqtt_server_;
    const char* publish_topic_;
    const char* subscribe_topic_;
    int mqtt_port_;
    WiFiClient wifiClient_;
    PubSubClient client_;
    char lastMessage_[256] = {0};
};

#endif // MQTT_COMMUNICATION_H
