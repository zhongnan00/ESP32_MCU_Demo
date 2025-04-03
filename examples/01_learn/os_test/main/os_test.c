#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"

QueueHandle_t       queue_handle = NULL;
SemaphoreHandle_t   semphore_handle;    //can be used to synchronize tasks


typedef struct {

    int value;


}queue_data_t;



void task1(void *pvParameters){
    while (1)
    {
        /* code */
        queue_data_t queue_data;
        ESP_LOGI("task1", "task1 running");
        // if(pdTRUE == xQueueReceive(queue_handle, &queue_data, portMAX_DELAY)){
        //     ESP_LOGI("task1", "task1 receive data: %d", queue_data.value);
        // }
        if(pdTRUE == xSemaphoreTake(semphore_handle, portMAX_DELAY)){
            ESP_LOGI("task1", "task1 get semphore");
            xQueueReceive(queue_handle, &queue_data, portMAX_DELAY);
            ESP_LOGI("task1", "task1 receive data: %d", queue_data.value);
        }
        
        // vTaskDelay(1000 / portTICK_PERIOD_MS);


    };
    
}


void task2(void *pvParameters){
    queue_data_t queue_data;
    queue_data.value = 0;
    while (1)
    {
        /* code */
        ESP_LOGI("task2", "task2 running");
        
        queue_data.value++;
        xQueueSend(queue_handle, &queue_data, portMAX_DELAY);
        xSemaphoreGive(semphore_handle);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    };

}

void app_main(void)
{
    queue_handle = xQueueCreate(10, sizeof(queue_data_t));
    semphore_handle = xSemaphoreCreateBinary();
    xTaskCreate(task1, "task1", 2048, NULL, 5, NULL);
    xTaskCreate(task2, "task2", 2048, NULL, 5, NULL);
    ESP_LOGI("app_main", "app_main running");


}
