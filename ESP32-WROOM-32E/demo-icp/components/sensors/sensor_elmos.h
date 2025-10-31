/**
 * @file sensor_elmos.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __SENSOR_ELMOS_H__
#define __SENSOR_ELMOS_H__

#include "esp_err.h"
#include <stdio.h>


#define I2C_ADDR_ELMOS 0x6C

esp_err_t elmos_write_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t elmos_read_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t elmos_probe_test(void);

float elmos_get_pressure(void);

#endif //__SENSOR_ELMOS_H__