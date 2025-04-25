#pragma once

#include <stdio.h>
#include "lvgl.h"
#include "demos/lv_demos.h"

#include "LVGL_Driver.h"
#include "SD_SPI.h"
#include "Wireless.h"

#define EXAMPLE1_LVGL_TICK_PERIOD_MS  1000


void Lvgl_Example1(void);

void lvgl_head_block(void);

void lvgl_icp_block(void);

void lvgl_temp_block(void);

void lvgl_wifi_block(void);

void lvgl_battery_block(void);

void lvgl_bluetooth_block(void);


void lvgl_update_head_block(char* id);

void lvgl_update_icp_block(float icp, bool is_push);

void lvgl_update_temp_block(float temp);

void lvgl_update_wifi_block(const char* ip_addr);


void lvgl_update_wifi_mqtt();

void lvgl_update_probe_sn();