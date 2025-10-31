#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "sensor_comm.h"


void app_main(void)
{
    sensor_comm_init();

    while (1)
    {
        // printf("Hello-ESP32\r\n");
        vTaskDelay(1000);   //1000ms
    }
}
