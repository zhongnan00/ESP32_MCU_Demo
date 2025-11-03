/**
 * @file sensor_comm.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SENSOR_COMM_H_
#define SENSOR_COMM_H_

#include "esp_err.h"
#include "esp_log.h"
#include "stdio.h"




typedef enum{
    HEADER_SENSOR_EEPROM    = 0x01,
    HEADER_SENSOR_ICP       = 0x02,
    HEADER_SENSOR_TEMP      = 0x03,
    HEADER_BLUETOOTH_PACKET  = 0xBB,

}enum_header_t;

typedef struct {
    uint8_t header;
    int32_t pressure;
}ts_sensor_pressure_t;

typedef struct {
    uint8_t header;
    int32_t temp;
}ts_sensor_temp_t;

typedef struct {
    uint8_t header;
    uint8_t year;
    uint8_t type;
    uint8_t reserved;
    uint32_t num;
    uint32_t zero_time;
    uint32_t cali_offset;
}ts_sensor_eeprom_t;


typedef struct {
    uint8_t header;
    uint8_t len;
    uint8_t year;
    uint8_t type;
    uint32_t num;
    int32_t pressure;
    int32_t temp;
    uint8_t r; //0x0D
    uint8_t n; //0x0A

}__attribute__((packed)) ts_bt_packet_t;


void get_sensor_pressure_data(ts_sensor_pressure_t *data);

void get_sensor_temp_data(ts_sensor_temp_t *data);

void get_sensor_eeprom_data(ts_sensor_eeprom_t *data);

void sensor_temp_sync_init(void);

void sensor_temp_sync_start(void);

void sensor_comm_init();

#endif /* SENSOR_COMM_H_ */