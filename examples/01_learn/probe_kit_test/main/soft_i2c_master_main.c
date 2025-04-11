/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_check.h"
#include "lib_soft_i2c.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"


/* I2C device address to communicate with */


const char* EXAMPLE_TAG = "soft_i2c_master";


void app_main(void)
{
    lib_soft_i2c_cfg_t eepro_cfg;
    eepro_cfg.scl_gpio = 2;   //gpio2
    eepro_cfg.sda_gpio = 3;   //gpio3
    eepro_cfg.scl_freq = 100000;
    eepro_cfg.i2c_master_port = I2C_NUM_0;

    lib_soft_i2c_init(eepro_cfg);

    char buffer[10]={0x0};
    eeprom_get_sn(buffer);
    ESP_LOGI(EXAMPLE_TAG, "SN: %s", buffer);
    ntc_config();
    ntc_sync_start();

    while(1)
    {
        ntc_sync_start();
        vTaskDelay(pdMS_TO_TICKS(1000));
 
        float pressure = elmos_get_pressure();
        ESP_LOGI(EXAMPLE_TAG, "Pressure: %.02f", pressure);

        float temp = ntc_read_temp();
        ESP_LOGI(EXAMPLE_TAG, "Temperature: %.02f", temp);

    }

}

