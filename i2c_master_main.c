#include <stdio.h>
#include "esp_log.h"
#include "i2c_lib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define TAG "i2c-master"
#define SLAVE_ADDRESS 0xA

void app_main(void)
{
    esp_err_t ret = master_init(21, 22);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2C master: %s", esp_err_to_name(ret));
        return;
    }
    ESP_LOGI(TAG, "I2C master initialized successfully");

    while (1) {
        uint8_t message[] = "Hello, I2C Slave!";
        ret = master_write(message, ARRAY_SIZE(message), SLAVE_ADDRESS);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to send I2C message: %s", esp_err_to_name(ret));
        } else {
            ESP_LOGI(TAG, "I2C message sent successfully: %s", message);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
