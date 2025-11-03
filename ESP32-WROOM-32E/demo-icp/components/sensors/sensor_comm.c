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

#include "lib_soft_i2c.h"
#include "lib_ring_buffer.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"
#include "sensor_comm.h"

#include "bluetooth_app.h"



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
    ring_buffer_push(&icp_ring_buffer, (int32_t)(pressure));

    data->header = HEADER_SENSOR_ICP;
    data->pressure = (int32_t)(pressure);
}

void get_sensor_temp_data(ts_sensor_temp_t *data)
{
    float temp = ntc_read_temp();

    data->header = HEADER_SENSOR_TEMP;
    data->temp = (int32_t)(temp*100);
}

void get_sensor_eeprom_data(ts_sensor_eeprom_t *data)
{
    eeprom_get_sn_info(&eeprom_data);
}



static void sensor_comm_send_task(void *param) {
    /* Task entry log */
    ESP_LOGI(SENSOR_TAG, "sensor send task has been started!");
    int counter = 0;
    char sn_buffer[16] = {0};
    /* Loop forever */

    ts_bt_packet_t bt_packet;
    bt_packet.header = HEADER_BLUETOOTH_PACKET;
    bt_packet.len = sizeof(ts_bt_packet_t);
    bt_packet.r = 0x0D;
    bt_packet.n = 0x0A;

    eeprom_get_sn(sn_buffer);
    printf("Sensor SN: %s\r\n", sn_buffer);

    while (1) {
        /* Send sensor notify every 1 second */
        counter++;
        if(counter % 20 == 0){
            //eeprom
            get_sensor_eeprom_data(&eeprom_data);
            bt_packet.year = eeprom_data.year;
            bt_packet.type = eeprom_data.type;
            bt_packet.num = eeprom_data.num;
        }
        //temp
        if(counter % 25 == 0)
        {
            get_sensor_temp_data(&temp_data);
            printf("temp: %.2f C\r\n", temp_data.temp / 100.0f);
            bt_packet.temp = temp_data.temp;
        }

        get_sensor_pressure_data(&pressure_data);
        // printf("pressure: %.2f mmHg\r\n", pressure_data.pressure / 100.0f);
        if(counter %10 == 0)
        {
            // float pressure = 0;
            // for(int i=0; i<icp_ring_buffer.count; i++){
            //     pressure += icp_ring_buffer.buffer[i];
            // }
            // pressure /= icp_ring_buffer.count;
            // pressure /= 100;

            // printf("pressure: %.2f mmHg\r\n", pressure);
            bt_packet.pressure = pressure_data.pressure;

            bt_send_data_to_client_binary((uint8_t *)&bt_packet, sizeof(ts_bt_packet_t));
        }

        if(counter  == 33)
        {
            counter = 0;
        }

        

        /* Sleep */
        vTaskDelay(pdMS_TO_TICKS(30));
    }

    /* Clean up at exit */
    vTaskDelete(NULL);
}




void sensor_comm_init()
{
    probe_i2c_bus_init();
    sensor_temp_sync_init();

    xTaskCreate(sensor_comm_send_task, "Sensor Send", 4*1024, NULL, 5, NULL);
}