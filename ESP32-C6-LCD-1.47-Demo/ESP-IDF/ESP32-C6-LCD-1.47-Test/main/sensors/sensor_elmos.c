/**
 * @file sensor_elmos.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sensor_elmos.h"
#include "lib_soft_i2c.h"

static const char *TAG = "sensor_elmos";

esp_err_t elmos_write_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    lib_soft_i2c_write_bytes(TAG, I2C_NUM_0, I2C_ADDR_ELMOS, reg_addr, data, len);
    return ESP_OK;
}

esp_err_t elmos_read_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    lib_soft_i2c_read_bytes(TAG, I2C_NUM_0, I2C_ADDR_ELMOS, reg_addr, data, len);
    return ESP_OK;
}

esp_err_t elmos_probe_test(void)
{
    lib_soft_i2c_probe(TAG, I2C_NUM_0, I2C_ADDR_ELMOS);
    return ESP_OK;
}

float elmos_get_pressure(void)
{
    uint8_t data[6];
    lib_soft_i2c_read_bytes(TAG, I2C_NUM_0, I2C_ADDR_ELMOS, 0x2e, data, 6);

    uint16_t pressure = (uint16_t)data[2] + (uint16_t)data[3] * 256;
    float pressure_float = 100.0*300.0*((int16_t)pressure )/25600;

    return pressure_float;
}