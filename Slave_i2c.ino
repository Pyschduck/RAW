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
  Wire.begin(0x01);  
  Wire.onReceive(receiveEvent); 
}

void loop() {
 
}

void receiveEvent(int howMany) {
  if (howMany >= sizeof(PS4Data) + 1) { 
    PS4Data data;
    Wire.readBytes((char*)&data, sizeof(data));  

    byte receivedChecksum = Wire.read();  
    byte calculatedChecksum = calculateChecksum((uint8_t*)&data, sizeof(data)); 

    if (receivedChecksum == calculatedChecksum) {

      Serial.print("Circle: "); Serial.println(data.Circle);

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
