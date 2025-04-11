/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "ST7789.h"
#include "SD_SPI.h"
#include "RGB.h"
#include "Wireless.h"
#include "LVGL_Example.h"
#include "lib_soft_i2c.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"

const char* EXAMPLE_TAG = "ESP32C6";

void app_main(void)
{
    Wireless_Init();
    Flash_Searching();
    RGB_Init();
    RGB_Example();
    SD_Init();                              // SD must be initialized behind the LCD
    LCD_Init();
    BK_Light(50);
    LVGL_Init();                            // returns the screen object

    probe_i2c_bus_init();
    char buffer[10]={0x0};
    eeprom_get_sn(buffer);
    ESP_LOGI(EXAMPLE_TAG, "SN: %s", buffer);
    ntc_config();
    ntc_sync_start();
/********************* Demo *********************/
    Lvgl_Example1();

    // lv_demo_widgets();
    // lv_demo_keypad_encoder();
    // lv_demo_benchmark();
    // lv_demo_stress();
    // lv_demo_music();

    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        ntc_sync_start();
        vTaskDelay(pdMS_TO_TICKS(1000));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
        float pressure = elmos_get_pressure();
        ESP_LOGI(EXAMPLE_TAG, "Pressure: %.02f", pressure);

        float temp = ntc_read_temp();
        ESP_LOGI(EXAMPLE_TAG, "Temperature: %.02f", temp);

    }
}
