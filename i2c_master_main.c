#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c_lib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "i2c-master"

void app_main(void)
{
    // Initialize I2C master
    esp_err_t ret = i2c_master_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2C master: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG, "I2C master initialized successfully");

    while (1) {
        // Example message to send
        uint8_t message[] = "Hello, I2C Slave!";
        ret = i2c_master_send(message, sizeof(message));
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to send I2C message: %s", esp_err_to_name(ret));
        } else {
            ESP_LOGI(TAG, "I2C message sent successfully");
        }

        // Delay to prevent flooding the slave
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
