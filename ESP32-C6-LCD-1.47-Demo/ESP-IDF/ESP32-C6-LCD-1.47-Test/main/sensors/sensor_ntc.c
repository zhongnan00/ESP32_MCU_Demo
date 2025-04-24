/**
 * @file sensor_ntc.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "math.h"
#include "sensor_ntc.h"
#include "lib_soft_i2c.h"
#include "esp_log.h"

static const char *TAG = "sensor_ntc";

esp_err_t ntc_write_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    lib_soft_i2c_write_bytes(TAG, I2C_NUM_0, I2C_ADDR_NTC, reg_addr, data, len);
    return ESP_OK;
}

esp_err_t ntc_read_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    lib_soft_i2c_read_bytes(TAG, I2C_NUM_0, I2C_ADDR_NTC, reg_addr, data, len);
    return ESP_OK;
}

esp_err_t ntc_probe_test(void)
{
    lib_soft_i2c_probe(TAG, I2C_NUM_0, I2C_ADDR_NTC);
    return ESP_OK;
}

esp_err_t ntc_config(void)
{
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    if(!i2c_cmd)
    {
        ESP_LOGE(TAG, "Error i2c_cmd creat fail!");
        return ESP_FAIL;
    }
    ret = i2c_master_start(i2c_cmd);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error i2c_master_start fail!");
        i2c_cmd_link_delete(i2c_cmd);
        return ESP_FAIL;
    }

    i2c_master_write_byte(i2c_cmd, (I2C_ADDR_NTC << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(i2c_cmd, 0x40, I2C_MASTER_ACK);
    i2c_master_write_byte(i2c_cmd, 0x01, I2C_MASTER_ACK);
    i2c_master_write_byte(i2c_cmd, 0x44, I2C_MASTER_ACK);
    i2c_master_write_byte(i2c_cmd, 0x02, I2C_MASTER_ACK); 
    i2c_master_write_byte(i2c_cmd, 0x48, I2C_MASTER_ACK);
    i2c_master_write_byte(i2c_cmd, 0x02, I2C_MASTER_ACK);
    i2c_master_write_byte(i2c_cmd, 0x4C, I2C_MASTER_ACK);
    i2c_master_write_byte(i2c_cmd, 0x60, I2C_MASTER_ACK);

    i2c_master_stop(i2c_cmd);
    i2c_master_cmd_begin(I2C_NUM_0, i2c_cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(i2c_cmd);
    return ret;
}

esp_err_t ntc_sync_start(void)
{
    esp_err_t ret = ESP_OK;
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    if(!i2c_cmd)
    {
        ESP_LOGE(TAG, "Error i2c_cmd creat fail!");
        return ESP_FAIL;
    }
    ret = i2c_master_start(i2c_cmd);
    if(ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Error i2c_master_start fail!");
        i2c_cmd_link_delete(i2c_cmd);
        return ESP_FAIL;
    }

    i2c_master_write_byte(i2c_cmd, (I2C_ADDR_NTC << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(i2c_cmd, 0x08, I2C_MASTER_ACK);

    i2c_master_stop(i2c_cmd);
    i2c_master_cmd_begin(I2C_NUM_0, i2c_cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(i2c_cmd);
    return ret;
}

float ntc_read_temp(void)
{

    uint8_t data[3];
    ntc_read_bytes(0x10, data, 3);

    uint32_t value = (data[0]*65536 + data[1]*256 + data[2]);
    float ohm = 33.2*value/8388607*1000;

    float temp = 48.52*exp(-0.000255*ohm) + 67.15*exp(-4.524e-5*ohm);


    return temp;
}
