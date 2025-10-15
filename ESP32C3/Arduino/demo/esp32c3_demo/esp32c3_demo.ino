/**
 * @brief esp32c3-demo
 * 
 */

#include <Arduino.h>
#include "led.h"


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.print("Hello ESP32C3");
    led_init();
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(1000);
    Serial.print("Hello ESP32C3");
    led_on();
    delay(1000);
    led_off();

}
