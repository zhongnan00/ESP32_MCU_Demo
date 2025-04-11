/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_check.h"
#include "lib_soft_i2c.h"
// #include "soft_i2c_master.h"

/* I2C device address to communicate with */
#define I2C_DEVICE_ADDRESS 0x50
#define I2C_EEPROM_ADDRESS 0x50
#define I2C_ELMOS_ADDRESS  0x6C
#define I2C_NTC_ADDRESS    0x40

const char* EXAMPLE_TAG = "soft_i2c_master";


void app_main(void)
{
    lib_soft_i2c_cfg_t eepro_cfg;
    eepro_cfg.scl_gpio = 2;   //gpio2
    eepro_cfg.sda_gpio = 3;   //gpio3
    eepro_cfg.scl_freq = 100000;
    eepro_cfg.i2c_master_port = I2C_NUM_0;

    lib_soft_i2c_init(eepro_cfg);

    uint8_t buffer[8]={0x0};
    lib_soft_i2c_read_bytes(EXAMPLE_TAG, I2C_NUM_0, 0x50, 0xA0, buffer, 8);
    ESP_LOGI(EXAMPLE_TAG, "I2C NTC read succeeded, received %02x bytes", buffer[0]);
    for(int i=0;i<8;i++)
    {
        ESP_LOGI(EXAMPLE_TAG, "byte %d: 0x%02x", i, buffer[i]);
    }
}

