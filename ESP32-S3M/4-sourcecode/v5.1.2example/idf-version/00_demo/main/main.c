
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_psram.h"
#include "esp_flash.h"
#include "led.h"


/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 * 
 */


static void print_chip_info()
{
    uint32_t flash_size;
    esp_chip_info_t chip_info;                                      /* 定义芯片信息结构体变量 */

    esp_flash_get_size(NULL, &flash_size);                          /* 获取FLASH大小 */
    esp_chip_info(&chip_info);
    printf("kernal cpu num: %u\n",chip_info.cores); 
    printf("kernal feature: %lu \n",chip_info.features);
    printf("kernal %u \n", chip_info.revision);                    /* 获取CPU内核数并显示 */
    printf("FLASH size:%lu MB \n",flash_size / (1024 * 1024)); /* 获取FLASH大小并显示 */
    printf("PSRAM size: %u KB\n", esp_psram_get_size()/1024);         /* 获取PARAM大小并显示 */
}

void app_main(void)
{
    esp_err_t ret;
    uint32_t flash_size;
    esp_chip_info_t chip_info;                                      /* 定义芯片信息结构体变量 */

    ret = nvs_flash_init();                                         /* 初始化NVS */

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    print_chip_info();
    led_init();             /* 初始化LED */
    
    while(1)
    {
        printf("Hello-ESP32\r\n");
        vTaskDelay(1000);   //1000ms
        LED_TOGGLE();
    }
}
