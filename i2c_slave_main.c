#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "i2c_lib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



const char *TAG = "slave";

void app_main(void)
{
 // Set LED pin as output

    // Initialize I2C slave
    ESP_ERROR_CHECK(i2c_slave_init());
    ESP_LOGI(TAG, "I2C Slave initialized successfully");

    while(1) {
        i2c_slave_read();
        // Add a small delay to avoid continuous polling
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
