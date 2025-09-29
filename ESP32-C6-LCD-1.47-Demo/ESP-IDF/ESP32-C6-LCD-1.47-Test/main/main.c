/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
// #include "esp_vfs_dev.h"
#include "ST7789.h"
#include "SD_SPI.h"
#include "RGB.h"

#include "LVGL_Example.h"
#include "lib_soft_i2c.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"
#include "bluetooth_app.h"

#include "simple_wifi_sta.h"
#include "lib_ring_buffer.h"
#include "sensor_comm.h"


const char* EXAMPLE_TAG = "ESP32C6";
ring_buffer_t icp_ring_buffer;

void app_main(void)
{

    Flash_Searching();
    RGB_Init();
    RGB_Example();
    SD_Init();                              // SD must be initialized behind the LCD
    LCD_Init();
    BK_Light(50);
    LVGL_Init();                            // returns the screen object

    
/********************* Demo *********************/

    lvgl_head_block();
    lvgl_icp_block();
    lvgl_temp_block();
    lvgl_wifi_block();
    lvgl_bluetooth_Info_block();
    lvgl_battery_block();
    lvgl_status_block();
    lv_timer_handler();

    simple_wifi_sta_init();
    lv_timer_handler();

    probe_i2c_bus_init();
    char probe_sn[10]="YYT00000";
    eeprom_get_sn(probe_sn);
    ESP_LOGI(EXAMPLE_TAG, "SN: %s", probe_sn);
    lvgl_update_head_block(probe_sn);
    lv_timer_handler();
    ntc_config();
    ntc_sync_start();
    
    // int counter = 0;
    // ring_buffer_init(&icp_ring_buffer);
    lv_timer_handler();

    bluetooth_app_init();

    sensor_comm_init();

    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        // ntc_sync_start();
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();


    }
}
