#include "uart_lib.h"
#include <esp_log.h>
#include <string.h>
#include <driver/uart.h>

void uart_init(uart_port_t uart_num, int baud_rate)
{
    uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
    };

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    
    QueueHandle_t uart_queue;
    ESP_ERROR_CHECK(uart_driver_install(uart_num, UART_BUFFER_SIZE, UART_BUFFER_SIZE, 10, &uart_queue, 0));
}

void uart_send_string(uart_port_t uart_num, const char *str)
{
    uart_write_bytes(uart_num, str, strlen(str));
}

void uart_receive_data(uart_port_t uart_num, uint8_t *data, size_t length)
{
    int len = uart_read_bytes(uart_num, data, length, 100 / portTICK_PERIOD_MS);
    if (len > 0) {
        data[len] = '\0';
    }
}
