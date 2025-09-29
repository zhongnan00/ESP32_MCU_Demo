/**
 * @file hello.ino
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <Arduino.h>

int led = 8;


void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Hello ESP32C3");
    pinMode(led, OUTPUT);
    }


void loop() {
    // put your main code here, to run repeatedly:
    delay(1000);
    Serial.println("Hello ESP32C3");
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    }