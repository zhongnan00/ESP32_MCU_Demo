/**
 * @file sensor_gpio.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef __SENSOR_GPIO_H__
#define __SENSOR_GPIO_H__


#include "driver/gpio.h"
#include "stdint.h"
#include "stdio.h"


void sensor_gpio_init(void);

uint8_t get_sensor_gpio_state(void);




#endif /* __SENSOR_GPIO_H__ */