/**
 * @file led.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LED_H_
#define LED_H_

#include <Arduino.h>


void led_init();

void led_on();

void led_off();

void led_pwm();

void led_task_run(void *args);


#endif /* LED_H_ */