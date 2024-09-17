#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c_lib.h"

static const char *MASTER_TAG = "i2c-master";
static const char *SLAVE_TAG = "i2c-slave";

int i2c_master_port = 0;
int i2c_slave_port = 1;

static unsigned char SLAVE_ADDRESS = 0xA; 

esp_err_t master_init(int sda, int scl)
{
    int I2C_MASTER_SCL_IO = scl;
    int I2C_MASTER_SDA_IO = sda;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    esp_err_t err = i2c_param_config(i2c_master_port, &conf);
    if (err != ESP_OK) {
        return err;
    }
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

esp_err_t master_write(uint8_t message[], int len)
{
    ESP_LOGI(MASTER_TAG, "Sending Message = %s", message);  
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();    
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SLAVE_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(cmd, message, len, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    
    esp_err_t ret = i2c_master_cmd_begin(i2c_master_port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t master_read(void* data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (SLAVE_ADDRESS << 1) | READ_BIT, ACK_CHECK_EN);
    i2c_master_read(cmd, (uint8_t*)data, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(i2c_master_port, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE(MASTER_TAG, "I2C master read failed: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(MASTER_TAG, "Data received: %s", (char*)data);
    }

    return ret;
}

esp_err_t slave_init(int sda, int scl)
{
    int I2C_SLAVE_SCL_IO = scl;
    int I2C_SLAVE_SDA_IO = sda;

    i2c_config_t conf_slave = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = I2C_SLAVE_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_SLAVE_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave.addr_10bit_en = 0,
        .slave.slave_addr = SLAVE_ADDRESS,
    };

    esp_err_t err = i2c_param_config(i2c_slave_port, &conf_slave);
    if (err != ESP_OK) {
        ESP_LOGE(SLAVE_TAG, "I2C slave param config failed: %s", esp_err_to_name(err));
        return err;
    }

    err = i2c_driver_install(i2c_slave_port, conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
    if (err != ESP_OK) {
        ESP_LOGE(SLAVE_TAG, "I2C slave driver install failed: %s", esp_err_to_name(err));
    }

    return err;
}

uint8_t received_data[I2C_SLAVE_RX_BUF_LEN] = {0};

void slave_read(void)
{
    size_t len = i2c_slave_read_buffer(i2c_slave_port, received_data, I2C_SLAVE_RX_BUF_LEN, 100 / portTICK_PERIOD_MS);
    if (len > 0) {
        ESP_LOGI(SLAVE_TAG, "Data Received: %s", received_data);
    } else {
        ESP_LOGI(SLAVE_TAG, "No data received");
    }
    memset(received_data, 0, I2C_SLAVE_RX_BUF_LEN);
}
