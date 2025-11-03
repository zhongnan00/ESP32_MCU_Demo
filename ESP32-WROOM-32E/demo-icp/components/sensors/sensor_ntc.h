/**
 * @file sensor_ntc.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SENSOR_NTC_H_
#define SENSOR_NTC_H_


#include "esp_err.h"
#include "esp_log.h"
#include <stdio.h>




esp_err_t ntc_write_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t ntc_read_bytes(uint8_t addr, uint8_t *data, uint8_t len);

esp_err_t ntc_probe_test(void);

esp_err_t ntc_config(void);

esp_err_t ntc_sync_start(void);

esp_err_t ntc_read_temp_value(uint32_t *temp);

float ntc_read_temp(void);


#endif /* SENSOR_NTC_H_ */