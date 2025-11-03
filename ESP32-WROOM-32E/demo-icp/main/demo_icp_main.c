#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "sensor_comm.h"
#include "bluetooth_app.h"


/**
 * @brief 
 *  line connection:
 *  VCC  -> 3.3V
 *  GND  -> GND
 *  SDA  -> GPIO21
 *  SCL  -> GPIO22
 */


void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );


    bluetooth_app_start();
    sensor_comm_init();

    while (1)
    {
        // printf("Hello-ESP32\r\n");
        vTaskDelay(1000);   //1000ms
    }
}



/**
 * @brief connector pin definition (old version of cable)
 * p1: i2c_sda
 * p3: gnd
 * p5: pluged in detect, PA1
 * p7: pluged in detect, PA0
 * p9: vcc 5.2
 * 
 * p2: i2c_scl
 * p4: gnd
 * p6: gnd
 * p8: gnd
 * p10: gnd
 * 
 */



