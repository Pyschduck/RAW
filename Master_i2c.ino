#include <Wire.h>
#include <PS4Controller.h>

#define I2C_SDA 21
#define I2C_SCL 22
#define SLAVE_ADDR 0x08

// Define struct for PS4 data
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

void setup() {
    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL,200000);
    PS4.begin("fc:a5:d0:36:fd:75"); // Replace with your PS4 MAC address
    Serial.println("Waiting for PS4 Controller...");
}

void loop() {
    if (PS4.isConnected()) {
        Serial.println("PS4 Controller Connected");

        // Populate struct with joystick, button, and trigger data
        ps4Data.LStickX = PS4.LStickX();
        ps4Data.LStickY = PS4.LStickY();
        ps4Data.RStickX = PS4.RStickX();
        ps4Data.RStickY = PS4.RStickY();
        ps4Data.Square = PS4.Square();
        ps4Data.Cross = PS4.Cross();
        ps4Data.Circle = PS4.Circle();
        ps4Data.Triangle = PS4.Triangle();
        ps4Data.touchpad = PS4.Touchpad();
        ps4Data.Up = PS4.Up();
        ps4Data.Down = PS4.Down();
        ps4Data.Left = PS4.Left();
        ps4Data.Right = PS4.Right();
        ps4Data.L1 = PS4.L1();
        ps4Data.R1 = PS4.R1();
        ps4Data.L2 = PS4.L2Value(); // L2 trigger value (0-255)
        ps4Data.R2 = PS4.R2Value(); // R2 trigger value (0-255)

        // Send struct over I2C
        Wire.beginTransmission(SLAVE_ADDR);
        Wire.write((uint8_t*)&ps4Data, sizeof(ps4Data)); // Send struct as bytes
        Wire.endTransmission();

        Serial.printf("Sent: LX:%d LY:%d RX:%d RY:%d SQ:%d X:%d O:%d TRI:%d TP:%d UP:%d DOWN:%d LEFT:%d RIGHT:%d L1:%d R1:%d L2:%d R2:%d\n",
                      ps4Data.LStickX, ps4Data.LStickY, ps4Data.RStickX, ps4Data.RStickY,
                      ps4Data.Square, ps4Data.Cross, ps4Data.Circle, ps4Data.Triangle,
                      ps4Data.touchpad, ps4Data.Up, ps4Data.Down, ps4Data.Left, ps4Data.Right,
                      ps4Data.L1, ps4Data.R1, ps4Data.L2, ps4Data.R2);
    } else {
        Serial.println("PS4 Controller Disconnected");
    }

    // delay(100);
}
