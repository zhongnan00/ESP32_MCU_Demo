/**
 * @brief esp32c3-demo
 * 
 */

#include <Arduino.h>
#include "led.h"
#include "oled.h"
#include "ble_server.h"

TaskHandle_t led_task_handle = NULL;
TaskHandle_t oled_task_handle = NULL;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello ESP32C3");
  delay(50);
  oled_task_run(nullptr);

  run_tasks();

}

void loop() {

}



void run_tasks()
{
  xTaskCreatePinnedToCore(led_task_run, "led_task", 1024, NULL, 1, &led_task_handle, 0);
  // xTaskCreatePinnedToCore(oled_task_run, "oled_task", 4096, NULL, 1, &oled_task_handle, 0);

  ble_server_task_run(nullptr);
}