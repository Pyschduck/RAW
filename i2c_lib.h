#ifndef I2C_LIB_H
#define I2C_LIB_H

#include <stdint.h>
#include "esp_err.h"

// I2C Master Configuration
#define I2C_MASTER_SCL_IO 22               /*!< GPIO number for I2C master clock */
#define I2C_MASTER_SDA_IO 21               /*!< GPIO number for I2C master data */
#define I2C_MASTER_FREQ_HZ 100000          /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0        /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0        /*!< I2C master doesn't need buffer */
#define SLAVE_ADDRESS 0x0A                 /*!< Slave address */

// I2C Slave Configuration
#define I2C_SLAVE_SCL_IO 22               /*!< GPIO number for I2C slave clock */
#define I2C_SLAVE_SDA_IO 21               /*!< GPIO number for I2C slave data */
#define I2C_SLAVE_FREQ_HZ 100000          /*!< I2C slave clock frequency */
#define I2C_SLAVE_TX_BUF_LEN 255          /*!< I2C slave transmit buffer length */
#define I2C_SLAVE_RX_BUF_LEN 255          /*!< I2C slave receive buffer length */
#define ESP_SLAVE_ADDR 0x0A               /*!< I2C slave address */

// I2C Read/Write Definitions
#define WRITE_BIT I2C_MASTER_WRITE        /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ          /*!< I2C master read */
#define ACK_CHECK_EN 0x1                  /*!< I2C master will check ack from slave */
#define ACK_CHECK_DIS 0x0                 /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                       /*!< I2C ack value */
#define NACK_VAL 0x1                      /*!< I2C nack value */

// Global Variables
extern int i2c_master_port;
extern int i2c_slave_port;

// Function Declarations
esp_err_t i2c_master_init(void);
esp_err_t i2c_master_send(uint8_t message[], int len);
esp_err_t i2c_slave_init(void);
void i2c_slave_read(void);  // Updated return type to void

#endif // I2C_LIB_H
