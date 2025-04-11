/**
 * @file sensor_eeprom.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef __SENSOR_EEPROM_H__
#define __SENSOR_EEPROM_H__

#include "esp_err.h"
#include "esp_log.h"
#include <stdio.h>


#define I2C_ADDR_EEPROM 0x50


 typedef enum{

    ADDR_ICP_ZERO_FLAG  = 0x00,
    ADDR_ICP_USED_TIME  = 0x04,
    ADDR_ICP_ZERO_TIME  = 0x10,
    ADDR_ICP_CALI_DATA  = 0x14,
    ADDR_ICT_COEF_1     = 0x20,
    ADDR_ICT_COEF_2     = 0x30,
    ADDR_ICT_COEF_3     = 0x40,
    ADDR_ICT_COEF_4     = 0x50,
    ADDR_ICT_COEF_5     = 0x60,
    ADDR_ICT_CALI_FLAG  = 0x70,


}enum_e2prom_addr;



esp_err_t eeprom_write_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t eeprom_read_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t eeprom_probe_test(void);

esp_err_t eeprom_get_sn(char *buffer);



#endif /* __SENSOR_EEPROM_H__ */