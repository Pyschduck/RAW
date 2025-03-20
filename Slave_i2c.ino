#include <Wire.h>

#define I2C_SDA 8
#define I2C_SCL 9
#define SLAVE_ADDR 0x08

// Define struct for PS4 data (must match master)
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
    bool Up;
    bool Down;
    bool Left;
    bool Right;
    bool L1;
    bool R1;
    int L2;
    int R2;
};

PS4Data ps4Data;

void receiveEvent(int bytes) {
    if (bytes == sizeof(PS4Data)) { // Ensure full struct is received
        Wire.readBytes((uint8_t*)&ps4Data, sizeof(ps4Data)); // Read struct

        Serial.printf("Received: LX:%d LY:%d RX:%d RY:%d SQ:%d X:%d O:%d TRI:%d TP:%d UP:%d DOWN:%d LEFT:%d RIGHT:%d L1:%d R1:%d L2:%d R2:%d\n",
                      ps4Data.LStickX, ps4Data.LStickY, ps4Data.RStickX, ps4Data.RStickY,
                      ps4Data.Square, ps4Data.Cross, ps4Data.Circle, ps4Data.Triangle,
                      ps4Data.touchpad, ps4Data.Up, ps4Data.Down, ps4Data.Left, ps4Data.Right,
                      ps4Data.L1, ps4Data.R1, ps4Data.L2, ps4Data.R2);
    }
}

void setup() {
    Serial.begin(115200);
    Wire.begin(SLAVE_ADDR);
    Wire.onReceive(receiveEvent);
}

void loop() {
    // delay(100);
}
