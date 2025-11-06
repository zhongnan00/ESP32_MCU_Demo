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
#include "esp_timer.h"
#include "math.h"
#include "lib_soft_i2c.h"
#include "lib_ring_buffer.h"
#include "sensor_eeprom.h"
#include "sensor_elmos.h"
#include "sensor_ntc.h"
#include "sensor_gpio.h"
#include "sensor_comm.h"

#include "bluetooth_app.h"



static const char *SENSOR_TAG = "sensor_comm";
static ring_buffer_t icp_ring_buffer;  /* ring buffer for icp data, store 10 samples at most. */
static ts_sensor_eeprom_t eeprom_data;
static ts_sensor_pressure_t pressure_data;
static ts_sensor_temp_t temp_data;

static uint8_t last_plug_state = 1; //1: unplugged, 0: plugged

static uint8_t probe_zero_flag = 0;
static uint8_t probe_ntc_cali_flag = 0;
static uint64_t probe_ntc_coef[5] = {0};
static double  probe_ntc_coef_double[5] = {0.0};
static uint32_t probe_zero_time = 0;
static uint32_t probe_cali_offset = 0;

static SemaphoreHandle_t  sensor_data_mutex = NULL ;
static esp_timer_handle_t sensor_timer_handle = NULL;

 
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

int32_t sensor_ntc_temp_calculate(ts_sensor_temp_t *data)
{
    
    uint32_t raw_ohm = 0;
    double   temp = 0.0;
    ntc_read_temp_value(&raw_ohm);
    float ohm = 33.2*raw_ohm/8388607*1000;
    
    data->header = HEADER_SENSOR_TEMP;
    data->ohm = (uint32_t)(ohm);

    if(probe_ntc_cali_flag == 0)
    {
        temp = 48.52*exp(-0.000255*ohm) + 67.15*exp(-4.524e-5*ohm);
        data->temp = (int32_t)(temp*100);
    }
    else
    {
        double logR = log(ohm/1000);
        temp = (probe_ntc_coef_double[0]) +
                      (probe_ntc_coef_double[1])*logR +
                      (probe_ntc_coef_double[2])*logR*logR +
                      (probe_ntc_coef_double[3])*logR*logR*logR +
                      (probe_ntc_coef_double[4])*logR*logR*logR*logR - 273.15;
        data->temp = (int32_t)(temp*100);
    }
    
    return data->temp;
}


void get_sensor_pressure_data(ts_sensor_pressure_t *data)
{
    float pressure = elmos_get_pressure();
    if(ring_buffer_is_full(&icp_ring_buffer))
    {
        ring_buffer_pop_only(&icp_ring_buffer);
    }
    ring_buffer_push(&icp_ring_buffer, (int32_t)(pressure) - (int32_t)probe_cali_offset);

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
    eeprom_get_sn_info(data);
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

        
        //check gpio
        uint8_t gpio_state = get_sensor_gpio_state();
        
        bt_packet.plug_state = gpio_state;
        if(gpio_state)  //high level is unplugged
        {
            if(last_plug_state != gpio_state)
            {
                printf("Sensor unplugged\r\n");
            }
            last_plug_state = gpio_state;
            //clear bt_package data
            bt_packet.year = 0;
            bt_packet.type = 0;
            bt_packet.num = 0;
            bt_packet.zero_time = 0;
            bt_packet.pressure = 0;
            bt_packet.temp = 0;
            bt_packet.ohm = 0;
            bt_send_data_to_client_binary((uint8_t *)&bt_packet, sizeof(ts_bt_packet_t));

            vTaskDelay(pdMS_TO_TICKS(500));
            counter =0;
            memset(probe_ntc_coef, 0, sizeof(probe_ntc_coef)); 
            memset(probe_ntc_coef_double, 0, sizeof(probe_ntc_coef_double));
            temp_data.temp = 0;
            temp_data.ohm = 0;
            continue;
        }

        if(gpio_state != last_plug_state)
        {
            counter =0;
            vTaskDelay(pdMS_TO_TICKS(500)); //debounce
            gpio_state = get_sensor_gpio_state();
            if(gpio_state)
            {
                printf("Sensor may unplugged,retry\r\n");
                continue;
            }
            //read the eeprom data;
            //eeprom
            get_sensor_eeprom_data(&eeprom_data);
            bt_packet.year = eeprom_data.year;
            bt_packet.type = eeprom_data.type;
            bt_packet.num = eeprom_data.num;
            vTaskDelay(pdMS_TO_TICKS(100));

            //zero flag
            eeprom_get_zero_flag(&probe_zero_flag);
            printf("Probe zero flag: %x\r\n", probe_zero_flag);
            bt_packet.zero_flag = probe_zero_flag;
            vTaskDelay(pdMS_TO_TICKS(100));
            //ntc cali flag
            eeprom_get_ntc_cali_flag(&probe_ntc_cali_flag);
            printf("Probe ntc cali flag: %x\r\n", probe_ntc_cali_flag);
            vTaskDelay(pdMS_TO_TICKS(100));
            //ntc coef
            eeprom_get_ntc_coef(ADDR_ICT_COEF_1, &probe_ntc_coef[0]);
            vTaskDelay(pdMS_TO_TICKS(100));
            eeprom_get_ntc_coef(ADDR_ICT_COEF_2, &probe_ntc_coef[1]);
            vTaskDelay(pdMS_TO_TICKS(100));
            eeprom_get_ntc_coef(ADDR_ICT_COEF_3, &probe_ntc_coef[2]);
            vTaskDelay(pdMS_TO_TICKS(100));
            eeprom_get_ntc_coef(ADDR_ICT_COEF_4, &probe_ntc_coef[3]);
            vTaskDelay(pdMS_TO_TICKS(100));
            eeprom_get_ntc_coef(ADDR_ICT_COEF_5, &probe_ntc_coef[4]);
            vTaskDelay(pdMS_TO_TICKS(100));

            //convert to double
            for(int i=0; i<5; i++){
                int64_t coef = probe_ntc_coef[i];
                probe_ntc_coef_double[i] = ((double)coef)/1e8;
                printf("Probe ntc coef double %d: %.8f\r\n", i+1, probe_ntc_coef_double[i]);
            }

            //zero time
            eeprom_get_zero_time(&probe_zero_time);
            bt_packet.zero_time = probe_zero_time;
            vTaskDelay(pdMS_TO_TICKS(100));

            eeprom_get_cali_offset(&probe_cali_offset);
            bt_packet.cali_offset = (int32_t)probe_cali_offset;
            vTaskDelay(pdMS_TO_TICKS(100));

            //ntc init
            ntc_config();
            ntc_sync_start();

            printf("Sensor plugged, send data start\r\n");
        }

        last_plug_state = gpio_state;

        if(xSemaphoreTake(sensor_data_mutex, portMAX_DELAY) == pdTRUE)
        {
            //got the semaphore
            counter++;        
            //temp
            if(counter == 1)
            {
                sensor_ntc_temp_calculate(&temp_data);
                printf("temp: %.2f C\r\n", temp_data.temp / 100.0f);
                bt_packet.temp = temp_data.temp;
                bt_packet.ohm = temp_data.ohm;
                sensor_temp_sync_start();
                // bt_send_data_to_client_binary((uint8_t *)&bt_packet, sizeof(ts_bt_packet_t));
            }

            get_sensor_pressure_data(&pressure_data);
            // printf("pressure: %.2f mmHg\r\n", pressure_data.pressure / 100.0f);
            if(counter == 25) //25Hz
            {
                int32_t sum_pp = 0;
                for(int i=0; i<icp_ring_buffer.count; i++){
                    sum_pp += icp_ring_buffer.buffer[i];
                }
                sum_pp /= icp_ring_buffer.count;
                bt_packet.pressure = sum_pp;
                bt_send_data_to_client_binary((uint8_t *)&bt_packet, sizeof(ts_bt_packet_t));

                counter = 0;
            }

        
        }  //semaphore end
    }

    /* Clean up at exit */
    vTaskDelete(NULL);
}


void timer_callback(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(sensor_data_mutex, &xHigherPriorityTaskWoken);
    // if (xHigherPriorityTaskWoken == pdTRUE) {
    //     portYIELD_FROM_ISR();
    // }
}


void sensor_comm_init()
{
    sensor_gpio_init();
    probe_i2c_bus_init();
    sensor_temp_sync_init();

    sensor_data_mutex = xSemaphoreCreateBinary();
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_callback,
        .name = "sensor_timer",
        .arg = sensor_data_mutex
    };

    esp_timer_create(&timer_args, &sensor_timer_handle);
    esp_timer_start_periodic(sensor_timer_handle, 1000000/25); //25Hz

    xTaskCreate(sensor_comm_send_task, "Sensor Send", 4*1024, NULL, 5, NULL);
}