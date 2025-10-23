/**
 ******************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2025-01-01
 * @brief       RNG实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 ESP32-S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ******************************************************************************
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "led.h"
#include "spilcd.h"
#include "key.h"
#include "rng.h"
#include <stdio.h>


/**
 * @brief       程序入口
 * @param       无
 * @retval      无
 */
void app_main(void)
{
    esp_err_t ret;
    uint8_t key = 0;
    uint32_t random = 0;
    uint8_t t = 0;

    ret = nvs_flash_init();     /* 初始化NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    led_init();                 /* LED初始化 */
    key_init();                 /* KEY初始化 */
    spilcd_init();              /* LCD屏初始化 */

    spilcd_show_string(0, 0, 200, 16, 16, "RNG Test", RED);
    spilcd_show_string(0, 20, 200, 16, 16, "BOOT:Get Random Num", RED);
    spilcd_show_string(0, 40, 200, 16, 16, "Num:", RED);
    spilcd_show_string(0, 60, 200, 16, 16, "Num[0-9]:", RED);

    while(1)
    {
        key = key_scan(0);
        
        if (key == BOOT_PRES)    
        {
            random = rng_get_random_num();                      /* 获取随机数 */
            spilcd_show_num(30 + 8 * 5, 40, random, 10, 16, BLUE);
            ESP_LOGI("test", "data:%ld ", random);
        }
        
        if ((t % 20) == 0)                                      
        {                                             
            random = rng_get_random_range(0, 9);                /* 取[0,9]区间的随机数 */
            spilcd_show_num(32 + 8 * 11, 60, random, 1, 16, BLUE);

            LED0_TOGGLE(); 
        }

        vTaskDelay(pdMS_TO_TICKS(10));
        t++;
    }
}
