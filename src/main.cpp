#include <Arduino.h>

// Define the analog input pin (GPIO 34 is input-only and good for analog read)
const int analogPin = 32;

void setup() {
  // Start the serial communication at 115200 baud
  Serial.begin(115200);

  // Optional: wait for serial to initialize
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  // Read the analog value (0 - 4095 for 12-bit resolution)
  int analogValue = analogRead(analogPin);

  // Print the value to the Serial Monitor
  Serial.print("Analog value: ");
  Serial.println(analogValue);
  delay(500);
}