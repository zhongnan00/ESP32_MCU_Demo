#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"



void app_main(void)
{
    while (1)
    {
        printf("Hello-ESP32\r\n");
        vTaskDelay(1000);   //1000ms
    }
}
