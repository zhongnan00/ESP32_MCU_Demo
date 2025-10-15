/**
 * @file led.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "led.h"

int led = 8;

void led_init()
{
    pinMode(led, OUTPUT);
    
}

void led_on()
{
    digitalWrite(led, LOW);
}

void led_off()
{
    digitalWrite(led, HIGH);
}