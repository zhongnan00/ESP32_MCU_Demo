/**
 * @file sensor_gpio.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "sensor_gpio.h"


#define SENSOR_GPIO_PIN    GPIO_NUM_23
#define PLUG_STATE         gpio_get_level(SENSOR_GPIO_PIN)


void sensor_gpio_init(void)
{
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << SENSOR_GPIO_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&io_conf);
}


uint8_t get_sensor_gpio_state(void)
{
    return PLUG_STATE;
}