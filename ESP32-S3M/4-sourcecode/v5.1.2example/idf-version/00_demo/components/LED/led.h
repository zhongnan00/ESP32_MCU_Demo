/**
 * @file led.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#ifndef __LED_H_
#define __LED_H_

#include "driver/gpio.h"

#define LED_GPIO_PIN  GPIO_NUM_1 //led

enum GPIO_OUTPUT_STATE
{
    PIN_RESET,
    PIN_SET
};

#define LED(x)          do { x ?                                      \
                             gpio_set_level(LED_GPIO_PIN, PIN_SET) :  \
                             gpio_set_level(LED_GPIO_PIN, PIN_RESET); \
                        } while(0)  //toggle

#define LED_TOGGLE()    do { gpio_set_level(LED_GPIO_PIN, !gpio_get_level(LED_GPIO_PIN)); } while(0)  //toggle


void led_init(void);    //init led

#endif /* __LED_H_ */