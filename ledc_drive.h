#ifndef LEDC_DRIVE_H
#define LEDC_DRIVE_H

#include <stdint.h>
#include "esp_err.h"

void servo_init(int gpio);
void servowrite(int dir, int steps);

#endif  
