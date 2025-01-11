#include <Wire.h>
#include "PS4Controller.h"

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
  Wire.begin();  
  PS4.begin("78:2b:46:91:ef:af");
}

void loop() {
  if (PS4.isConnected()) {
    PS4Data data;
    data.LStickX = PS4.LStickX();
    data.LStickY = PS4.LStickY();
    data.RStickX = PS4.RStickX();
    data.RStickY = PS4.RStickY();
    data.Square = PS4.Square();
    data.Cross = PS4.Cross();
    data.Circle = PS4.Circle();
    data.Triangle = PS4.Triangle();
    data.touchpad = PS4.Touchpad();

    Wire.beginTransmission(0x01);  
    Wire.write((uint8_t*)&data, sizeof(data)); 
    byte checksum = calculateChecksum((uint8_t*)&data, sizeof(data)); 
    Wire.write(checksum); 

    byte error = Wire.endTransmission(); 

    if (error == 0) {
      Serial.println("Data sent successfully to Slave 0x01");
    } else {
      Serial.println("Error sending to Slave 0x01");
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
