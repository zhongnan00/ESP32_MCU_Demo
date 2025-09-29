/**
 * @file sensor_comm.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Bluetooth/common.h"
#include "lib_soft_i2c.h"
#include "lib_ring_buffer.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"
#include "sensor_comm.h"
#include "LVGL_Example.h"
#include "gatt_svc.h"



static const char *SENSOR_TAG = "sensor_comm";
static ring_buffer_t icp_ring_buffer;  /* ring buffer for icp data, store 10 samples at most. */
static ts_sensor_eeprom_t eeprom_data;
static ts_sensor_pressure_t pressure_data;
static ts_sensor_temp_t temp_data;

void sensor_temp_sync_init(void)
{
    ntc_config();
    ntc_sync_start();

    ring_buffer_init(&icp_ring_buffer);
}


void sensor_temp_sync_start(void)
{
    ntc_sync_start();
}

void get_sensor_pressure_data(ts_sensor_pressure_t *data)
{
    float pressure = elmos_get_pressure();
    if(ring_buffer_is_full(&icp_ring_buffer))
    {
        ring_buffer_pop_only(&icp_ring_buffer);
    }
    ring_buffer_push(&icp_ring_buffer, (int)(pressure*100));
    // lvgl_update_icp_block(pressure, true);

    data->header = HEADER_SENSOR_ICP;
    data->pressure = (int32_t)(pressure*100);
}

void get_sensor_temp_data(ts_sensor_temp_t *data)
{
    float temp = ntc_read_temp();
    lvgl_update_temp_block(temp);

    data->header = HEADER_SENSOR_TEMP;
    data->temp = (uint32_t)(temp*100);
}

void get_sensor_eeprom_data(ts_sensor_eeprom_t *data)
{
    lvgl_update_probe_sn();
    data->header = HEADER_SENSOR_EEPROM;
}



static void sensor_comm_send_task(void *param) {
    /* Task entry log */
    ESP_LOGI(SENSOR_TAG, "sensor send task has been started!");
    int counter = 0;
    /* Loop forever */

    while (1) {
        /* Send sensor notify every 1 second */
        counter++;
        if(counter % 20 == 0){
            //eeprom
            get_sensor_eeprom_data(&eeprom_data);
            eeprom_data.year = 0x25;
            eeprom_data.type = 0x01;
            eeprom_data.num = 0x01234567;
            eeprom_data.zero_time = 0x12345678;
            eeprom_data.cali_offset = 0x87654321;
            struct os_mbuf *om = ble_hs_mbuf_from_flat(&eeprom_data, sizeof(eeprom_data));
            send_sensor_notify_osmbuf(om);
            ESP_LOGI(SENSOR_TAG, "send eeprom data");
        }
        //temp
        if(counter % 25 == 0)
        {
            get_sensor_temp_data(&temp_data);
        }
        if(counter  == 33)
        {
            counter = 0;
        }

        // get_sensor_pressure_data(&pressure_data);
        // if(counter %10 == 0)
        // {
        //     float pressure = 0;
        //     for(int i=0; i<icp_ring_buffer.count; i++){
        //         pressure += icp_ring_buffer.buffer[i];
        //     }
        //     pressure /= icp_ring_buffer.count;
        //     pressure /= 100;
        //     lvgl_update_icp_block(pressure, false);   
        // }

        /* Sleep */
        vTaskDelay(pdMS_TO_TICKS(30));
    }

    /* Clean up at exit */
    vTaskDelete(NULL);
}




void sensor_comm_init()
{
    sensor_temp_sync_init();

    xTaskCreate(sensor_comm_send_task, "Sensor Send", 4*1024, NULL, 5, NULL);
}