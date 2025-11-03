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
#include "sensor_comm.h"





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

    ADDR_ICP_CALI_FLAG  = 0x80,
    ADDR_FACTORY_DATE   = 0x90,
    ADDR_PROBE_SN       = 0xA0,

}enum_e2prom_addr;



esp_err_t eeprom_write_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t eeprom_read_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t eeprom_probe_test(void);

esp_err_t eeprom_get_sn(char *buffer);

esp_err_t eeprom_get_sn_info(ts_sensor_eeprom_t *data);

esp_err_t eeprom_get_zero_flag(uint8_t *flag);

esp_err_t eeprom_get_ntc_cali_flag(uint8_t *flag);

esp_err_t eeprom_get_ntc_coef(uint8_t index, uint64_t *coef);

esp_err_t eeprom_get_zero_time(uint32_t *zero_time);

esp_err_t eeprom_get_cali_offset(uint32_t *cali_offset);



#endif /* __SENSOR_EEPROM_H__ */