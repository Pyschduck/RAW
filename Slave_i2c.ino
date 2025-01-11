#include <Wire.h>

struct PS4Data {
  int LStickX;
  int LStickY;
  int RStickX;
  int RStickY;
  bool Square;
  bool Cross;
  bool Circle;
  bool Triangle;
  bool touchpad;
};

void setup() {
  Serial.begin(9600);
  Wire.begin(0x01);  // Initialize I2C as slave with address 0x01
  Wire.onReceive(receiveEvent);  // Register receive event
}

void loop() {
  // Main loop does nothing; data is handled in the receive event
}

void receiveEvent(int howMany) {
  if (howMany >= sizeof(PS4Data) + 1) {  // Ensure there's enough data for PS4Data and checksum
    PS4Data data;
    Wire.readBytes((char*)&data, sizeof(data));  // Read the PS4Data structure

    byte receivedChecksum = Wire.read();  // Read the checksum
    byte calculatedChecksum = calculateChecksum((uint8_t*)&data, sizeof(data));  // Calculate checksum

    if (receivedChecksum == calculatedChecksum) {
      // If checksums match, process the data
      // Serial.println("Received valid data from master");
      Serial.print("Circle: "); Serial.println(data.Circle);
      // Serial.print("RStickY: "); Serial.println(data.RStickY);
      // Add other data prints as needed
    } else {
      Serial.println("Checksum mismatch! Data corrupted.");
    }
  }
}

byte calculateChecksum(uint8_t *data, size_t length) {
  byte sum = 0;
  for (size_t i = 0; i < length; i++) {
    sum += data[i];
  }
  return sum;
}
