#pragma once

#include "lvgl.h"
#include "demos/lv_demos.h"

#include "LVGL_Driver.h"
#include "SD_SPI.h"
#include "Wireless.h"

#define EXAMPLE1_LVGL_TICK_PERIOD_MS  1000


void Lvgl_Example1(void);

void Lvgl_HomePage(void);

void lvgl_icp_block(void);

void lvgl_temp_block(void);

void lvgl_wifi_block(void);

void lvgl_battery_block(void);

void lvgl_bluetooth_block(void);