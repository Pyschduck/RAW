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

    ESP_ERROR_CHECK(slave_init(21,22));
    ESP_LOGI(TAG, "I2C Slave initialized successfully");

    while(1) {
        slave_read();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
