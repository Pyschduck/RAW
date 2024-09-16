#include "i2c_lib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    const uint8_t  on_command[] = "LED_ON";
    const uint8_t  off_command[] = "LED_OFF";

    ESP_ERROR_CHECK(i2c_master_init());
    
    while (1)
    {
        i2c_master_send(on_command, sizeof(on_command));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        i2c_master_send(off_command, sizeof(off_command));
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}
