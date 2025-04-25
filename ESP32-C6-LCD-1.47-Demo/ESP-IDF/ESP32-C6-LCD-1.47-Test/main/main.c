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
// #include "Wireless.h"
#include "LVGL_Example.h"
#include "lib_soft_i2c.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"

// #include "mqtt_app.h"
#include "simple_wifi_sta.h"
#include "lib_ring_buffer.h"

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
    lvgl_battery_block();
    lvgl_bluetooth_block();

    simple_wifi_sta_init();

    probe_i2c_bus_init();
    char probe_sn[10]={0x0};
    eeprom_get_sn(probe_sn);
    ESP_LOGI(EXAMPLE_TAG, "SN: %s", probe_sn);
    lvgl_update_head_block(probe_sn);

    ntc_config();
    ntc_sync_start();
    
    int counter = 0;
    ring_buffer_init(&icp_ring_buffer);


    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        ntc_sync_start();
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();

        ++counter;
        if(counter % 3 == 0){
            float pressure = elmos_get_pressure();
            
            if(ring_buffer_is_full(&icp_ring_buffer))
            {
                ring_buffer_pop_only(&icp_ring_buffer);
            }

            ring_buffer_push(&icp_ring_buffer, (int)(pressure*100));

            lvgl_update_icp_block(pressure, true);
            // ESP_LOGI(EXAMPLE_TAG, "Pressure: %d", (int)(pressure*100));
        }

        if(counter % 22 == 0){
            float temp = ntc_read_temp();
            lvgl_update_temp_block(temp);
            // ESP_LOGI(EXAMPLE_TAG, "Temperature: %0.1f", temp);
        }
        
        if(counter % 100 == 0){

            float pressure = 0;
            for(int i=0; i<icp_ring_buffer.count; i++){
                pressure += icp_ring_buffer.buffer[i];
                // printf("%d ", icp_ring_buffer.buffer[i]);
            }
            // printf("\n");
            pressure /= icp_ring_buffer.count;
            pressure /= 100;
            lvgl_update_icp_block(pressure, false);
            lvgl_update_wifi_mqtt();
            counter = 0;
        }

    }
}
