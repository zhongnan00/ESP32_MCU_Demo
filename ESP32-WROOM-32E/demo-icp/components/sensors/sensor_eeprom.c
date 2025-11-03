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

#define I2C_ADDR_EEPROM 0x50
static const char *TAG = "sensor_eeprom";
static char probe_sn[16];

esp_err_t eeprom_write_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    esp_err_t ret = lib_soft_i2c_write_bytes(TAG, I2C_NUM_0, I2C_ADDR_EEPROM, reg_addr, data, len);
    return ret;
}

esp_err_t eeprom_read_bytes(uint8_t reg_addr, uint8_t *data, uint8_t len)
{
    esp_err_t ret = lib_soft_i2c_read_bytes(TAG, I2C_NUM_0, I2C_ADDR_EEPROM, reg_addr, data, len);
    return ret;
}

esp_err_t eeprom_probe_test(void)
{
    esp_err_t ret = lib_soft_i2c_probe(TAG, I2C_NUM_0, I2C_ADDR_EEPROM);
    return ret;
}

esp_err_t eeprom_get_sn(char *buffer)
{
    uint8_t year= 0x0;
    uint8_t type = 0x0;
    uint32_t num = 0x0;

    uint8_t sn[5] = {0};
    esp_err_t ret = eeprom_read_bytes(ADDR_PROBE_SN, sn, 5);
    if(ret != ESP_OK){
        return ret;
    }

    year = sn[0];
    type = sn[1];

    num += sn[2];
    num <<= 8;
    num += sn[3];
    num <<= 8;
    num += sn[4];

    // ESP_LOGI(TAG, "SN: %u%c%05lu", year, type, num);

    sprintf(buffer, "%u%c%05lu", year, type, num);
    sprintf(probe_sn, "%u%c%05lu", year, type, num);

    // ESP_LOGI(EXAMPLE_TAG, "I2C NTC read succeeded, received %02x bytes", buffer[0]);
    // for(int i=0;i<8;i++)
    // {
    //     ESP_LOGI(EXAMPLE_TAG, "byte %d: 0x%02x", i, buffer[i]);
    // }
    return ESP_OK;
}
 

void eeprom_get_current_sn(char *buffer)
{
    sprintf(buffer, "%s", probe_sn);
}


esp_err_t eeprom_get_sn_info(ts_sensor_eeprom_t *data)
{
    uint8_t year= 0x0;
    uint8_t type = 0x0;
    uint32_t num = 0x0;

    uint8_t sn[5] = {0};
    esp_err_t ret = eeprom_read_bytes(ADDR_PROBE_SN, sn, 5);
    if(ret != ESP_OK){
        return ret;
    }

    year = sn[0];
    type = sn[1];

    num += sn[2];
    num <<= 8;
    num += sn[3];
    num <<= 8;
    num += sn[4];

    data->header = HEADER_SENSOR_EEPROM;
    data->year = year;
    data->type = type;
    data->num = num;

    return ret;
}

esp_err_t eeprom_get_zero_flag(uint8_t *flag)
{

    esp_err_t ret = eeprom_read_bytes(ADDR_ICP_ZERO_FLAG, flag, 1);
    if(ret != ESP_OK){
        return ret;
    }

    return ESP_OK;
}

esp_err_t eeprom_get_ntc_cali_flag(uint8_t *flag)
{
    esp_err_t ret = eeprom_read_bytes(ADDR_ICT_CALI_FLAG, flag, 1);
    if(ret != ESP_OK){
        return ret;
    }

    return ESP_OK;
}

esp_err_t eeprom_get_ntc_coef(uint8_t index, uint64_t *coef)
{
    uint8_t bytes[8]={0x0};
    esp_err_t ret = eeprom_read_bytes(index, bytes, 8);
    if(ret != ESP_OK){
        return ret;
    }

    *coef += (uint64_t)bytes[7];
    *coef <<= 8;
    *coef += (uint64_t)bytes[6];
    *coef <<= 8;
    *coef += (uint64_t)bytes[5];
    *coef <<= 8;
    *coef += (uint64_t)bytes[4];
    *coef <<= 8;
    *coef += (uint64_t)bytes[3];
    *coef <<= 8;
    *coef += (uint64_t)bytes[2];
    *coef <<= 8;
    *coef += (uint64_t)bytes[1];
    *coef <<= 8;
    *coef += (uint64_t)bytes[0];

    return ESP_OK;
}

esp_err_t eeprom_get_zero_time(uint32_t *zero_time)
{
    uint8_t bytes[4]={0x0};
    esp_err_t ret = eeprom_read_bytes(ADDR_ICP_ZERO_TIME, bytes, 4);
    if(ret != ESP_OK){
        return ret;
    }

    *zero_time += (uint32_t)bytes[0];
    *zero_time <<= 8;
    *zero_time += (uint32_t)bytes[1];
    *zero_time <<= 8;
    *zero_time += (uint32_t)bytes[2];
    *zero_time <<= 8;
    *zero_time += (uint32_t)bytes[3];

    return ESP_OK;
}

esp_err_t eeprom_get_cali_offset(uint32_t *cali_offset)
{
    uint8_t bytes[4]={0x0};
    esp_err_t ret = eeprom_read_bytes(ADDR_ICP_CALI_DATA, bytes, 4);
    if(ret != ESP_OK){
        return ret;
    }

    *cali_offset += (uint32_t)bytes[0];
    *cali_offset <<= 8;
    *cali_offset += (uint32_t)bytes[1];
    *cali_offset <<= 8;
    *cali_offset += (uint32_t)bytes[2];
    *cali_offset <<= 8;
    *cali_offset += (uint32_t)bytes[3];

    return ESP_OK;
}

