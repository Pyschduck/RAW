#ifndef I2C_LIB_H
#define I2C_LIB_H

#include <stdint.h>
#include "esp_err.h"

#define I2C_MASTER_SCL_IO 22               /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 21               /*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ 100000          /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0        /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0        /*!< I2C master doesn't need buffer */
#define SLAVE_ADDRESS 0x0A                 /*!< Slave address */

#define WRITE_BIT I2C_MASTER_WRITE          /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ            /*!< I2C master read */
#define ACK_CHECK_EN 0x1                    /*!< I2C master will check ack from slave */
#define ACK_VAL 0x0                         /*!< I2C ack value */
#define NACK_VAL 0x1                        /*!< I2C nack value */

// Function declarations
esp_err_t i2c_master_init(void);
esp_err_t i2c_master_send(uint8_t message[], int len);

#endif // I2C_LIB_H
