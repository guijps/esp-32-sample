 Embedded IoT System with ESP32 & Labrador (Caninos Loucos)
This project showcases a modular and distributed embedded IoT system using ESP32 microcontrollers and the Labrador platform developed by Caninos Loucos.

System Overview
The project is composed of three main components:

Central Unit (Labrador Board)
  Acts as the central processing unit.
  Performs complex calculations, decision-making, and coordination.
  Considers data from:
    Sensor feedback
    User input
    Overall system state

Node A – Motor Controller (ESP32)
  Controls the operation of a motor or actuator.
  Receives commands from the central unit.
  Provides real-time feedback (e.g., motor status or position).

Node B – Human-Machine Interface (ESP32)
  Interfaces with the user via buttons, displays, or other input methods.
  Forwards user commands to the Labrador.
  Can display system status or feedback.

Communication Layer
A shared and abstract communication interface was developed to support multiple communication protocols, such as: I2C, Bluetooth, MQTT. By utilizing an abstract base class, new protocols can be easily integrated or swapped with minimal code changes, ensuring flexibility and modularity.

