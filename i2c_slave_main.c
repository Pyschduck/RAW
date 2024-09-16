#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "i2c_lib.h"

#define LED_PIN 2

static const char *TAG = "i2c-slave";

void app_main(void)
{
    uint8_t received_data[I2C_SLAVE_RX_BUF_LEN] = {0};  // Buffer to store received data

    // Initialize LED GPIO
    gpio_reset_pin(LED_PIN);                            // Reset pin to default state
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);      // Set LED pin as output

    // Initialize I2C slave
    ESP_ERROR_CHECK(i2c_slave_init());
    ESP_LOGI(TAG, "I2C Slave initialized successfully");

    while (1)
    {
        // Read data from I2C slave buffer
        int len = i2c_slave_read_buffer(i2c_slave_port, received_data, I2C_SLAVE_RX_BUF_LEN, 100 / portTICK_PERIOD_MS);

        if (len > 0) {
            ESP_LOGI(TAG, "Data Received: %.*s", len, received_data);  // Log received data
            
            // Check if received data matches the LED_ON or LED_OFF command
            if (strncmp((const char*)received_data, "LED_ON", 6) == 0) {
                ESP_LOGI(TAG, "Turning LED ON");
                gpio_set_level(LED_PIN, 1);  // Turn LED on
            } else if (strncmp((const char*)received_data, "LED_OFF", 7) == 0) {
                ESP_LOGI(TAG, "Turning LED OFF");
                gpio_set_level(LED_PIN, 0);  // Turn LED off
            }

            // Clear the buffer after processing
            memset(received_data, 0, I2C_SLAVE_RX_BUF_LEN);
        }

        // Reset the RX FIFO buffer
        i2c_reset_rx_fifo(i2c_slave_port);
    }
}
