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


void led_pwm()
{
    for(int fadeValue = 0; fadeValue <= 255; fadeValue+=5)
    {
        analogWrite(led, fadeValue);
        delay(50);
    }

    for(int fadeValue = 255; fadeValue>=0; fadeValue-=5)
    {
        analogWrite(led, fadeValue);
        delay(50);
    }
}

void led_task_run(void *args)
{
    led_init();
    while (1)
    {
        /* code */
        Serial.println("Hello ESP32C3 ..");
        led_on();
        vTaskDelay(1000);
        led_off();
        vTaskDelay(1000);
    }
}


    