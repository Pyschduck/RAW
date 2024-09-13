#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "uart_lib.h"
#include <string.h>

void app_main(void)
{
    // Initialize UART
    uart_init(UART_NUM_2, 115200);

    // Sending data continuously
    const char *message = "hello";
    uint8_t received_data[UART_BUFFER_SIZE];
    
    while (1) {
        // Send data
        uart_send_string(UART_NUM_2, message);

        // Receive data
        uart_receive_data(UART_NUM_2, received_data, sizeof(received_data) - 1);

        // Null-terminate the received data and print it
        received_data[UART_BUFFER_SIZE - 1] = '\0'; // Ensure buffer is null-terminated
        if (strlen((char *)received_data) > 0) {
            printf("Received: %s\n", received_data);
        }

        // Delay to avoid busy-waiting
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
