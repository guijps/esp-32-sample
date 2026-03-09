#include "config.h"
#include <iostream>

#include "../../lib/communication/mqtt_communication.h"

MQTTCommunication* mqtt = nullptr;

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    std::string msg(reinterpret_cast<char*>(payload), length);
    std::cout << "Mensagem recebida em [" << topic << "]: " << msg << std::endl;
    if (mqtt) mqtt->storeLastMessage(msg.c_str());
}

int main(int argc, char* argv[])
{
    mqtt = new MQTTCommunication(ssid_net, password, mqtt_server);
    mqtt->initialize();
    mqtt->setCallback(mqttCallback);
    std::cout << "MQTT conectado. Aguardando mensagens..." << std::endl;
    while (true) {
        mqtt->loop();
        // Opcional: sleep para evitar uso excessivo de CPU
        delay(10);
    }
    delete mqtt;
    return 0;
}

