#include <stdio.h>
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ledc_drive.h"  

#define GPIO_PIN 18  

const char* TAG = "Servo";

void app_main(void)
{    
    servo_init(GPIO_PIN);
    ESP_LOGI(TAG, "Servo initialized");
    servowrite(0, 360);
    ESP_LOGI(TAG, "Servo moving clockwise");
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    servowrite(1, 360);
    ESP_LOGI(TAG, "Servo moving anticlockwise");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  
}
