#include <stdio.h>
#include "esp_err.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

const float dir_clock = 409.55;      // 5% duty cycle for clockwise
const float dir_anticlock = 819.1;   // 10% duty cycle for anticlockwise
const float stop = 614.325;          // 7.5% duty cycle for stop
float val;

float mapValue(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    if (fromLow == fromHigh) {
        return toLow;
    }
    return toLow + (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow);
}

void servo_init(int gpio) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 50,    
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = gpio,     
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void servowrite(int dir, int steps) {
    if (steps <= 0) {
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, stop));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
        vTaskDelay(1500 / portTICK_PERIOD_MS);
        return;
    }

    switch (dir) {
        case 0:  // Clockwise
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, dir_clock));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
            val = mapValue(steps, 0, 360, 0, 1520);  
            vTaskDelay(val / portTICK_PERIOD_MS);
            break;

        case 1:  // Anticlockwise
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, dir_anticlock));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
            val = mapValue(steps, 0, 360, 0, 1520);
            vTaskDelay(val / portTICK_PERIOD_MS);
            break;

        default:  // Stop for invalid direction
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, stop));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
            vTaskDelay(1500 / portTICK_PERIOD_MS);
            break;
    }
}
