/**
 * @file sensor_eeprom.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sensor_eeprom.h"
#include "lib_soft_i2c.h"

static const char *TAG = "sensor_eeprom";

esp_err_t eeprom_write_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    lib_soft_i2c_write_bytes(TAG, I2C_NUM_0, I2C_ADDR_EEPROM, reg_addr, data, len);
    return ESP_OK;
}

esp_err_t eeprom_read_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    lib_soft_i2c_read_bytes(TAG, I2C_NUM_0, I2C_ADDR_EEPROM, reg_addr, data, len);
    return ESP_OK;
}

esp_err_t eeprom_probe_test(void)
{
    lib_soft_i2c_probe(TAG, I2C_NUM_0, I2C_ADDR_EEPROM);
    return ESP_OK;
}

esp_err_t eeprom_get_sn(char *buffer)
{
    uint8_t year= 0x0;
    uint8_t type = 0x0;
    uint32_t num = 0x0;

    uint8_t sn[5] = {0};
    eeprom_read_bytes(0xA0, sn, 5);

    year = sn[0];
    type = sn[1];

    num += sn[2];
    num <<= 8;
    num += sn[3];
    num <<= 8;
    num += sn[4];

    // ESP_LOGI(TAG, "SN: %u%c%05lu", year, type, num);

    sprintf(buffer, "%u%c%05lu", year, type, num);

    // ESP_LOGI(EXAMPLE_TAG, "I2C NTC read succeeded, received %02x bytes", buffer[0]);
    // for(int i=0;i<8;i++)
    // {
    //     ESP_LOGI(EXAMPLE_TAG, "byte %d: 0x%02x", i, buffer[i]);
    // }
    return ESP_OK;
}
 