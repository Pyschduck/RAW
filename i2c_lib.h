#ifndef I2C_LIB_H
#define I2C_LIB_H

#include <stdint.h>
#include "esp_err.h"


#define I2C_MASTER_FREQ_HZ 100000          /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0        /*!< freq master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0        /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_LEN 255
#define I2C_MASTER_TX_BUF_len 255

#define I2C_SLAVE_FREQ_HZ 100000          /*!< I2C slave clock frequency */
#define I2C_SLAVE_TX_BUF_LEN 255          /*!< I2C slave transmit buffer length */
#define I2C_SLAVE_RX_BUF_LEN 255          /*!< I2C slave receive buffer length */


#define WRITE_BIT I2C_MASTER_WRITE        /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ          /*!< I2C master read */
#define ACK_CHECK_EN 0x1                  /*!< I2C master will check ack from slave */
#define ACK_CHECK_DIS 0x0                 /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                       /*!< I2C ack value */
#define NACK_VAL 0x1                      /*!< I2C nack value */

extern int i2c_master_port;
extern int i2c_slave_port;

esp_err_t master_init(int sda,int scl);
esp_err_t master_write(void* data,size_t len, unsigned char slave_addr);
esp_err_t slave_init(int sda,int scl);
void slave_read(void);  
esp_err_t master_read(void* data, size_t len, unsigned char slave_addr);
esp_err_t slave_write(void* data, size_t len);
#endif 
