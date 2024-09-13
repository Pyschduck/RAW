#ifndef UART_LIB_H
#define UART_LIB_H

#include <driver/uart.h>

#define UART_BUFFER_SIZE (1024)

// Initializes UART with given parameters
void uart_init(uart_port_t uart_num, int baud_rate);

// Sends a string over UART
void uart_send_string(uart_port_t uart_num, const char *str);

// Receives data from UART into the provided buffer
void uart_receive_data(uart_port_t uart_num, uint8_t *data, size_t length);

#endif // UART_LIB_H
