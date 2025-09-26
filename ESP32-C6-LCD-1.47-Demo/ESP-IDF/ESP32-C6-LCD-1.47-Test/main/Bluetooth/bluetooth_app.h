/**
 * @file bluetooth_app.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BLUETOOTH_APP_H__
#define __BLUETOOTH_APP_H__

#include "esp_err.h"
#include "esp_log.h"
#include <stdio.h>

#include "common.h"
#include "gap.h"
#include "gatt_svc.h"
#include "heart_rate.h"
// #include "led.h"



/* Private function declarations */
void bluetooth_app_init(void);

void on_stack_reset(int reason);
void on_stack_sync(void);
void nimble_host_config_init(void);
void nimble_host_task(void *param);




#endif  // __BLUETOOTH_APP_H__

 

/**
 * @brief 
 * I (3468) ESP32C6: SN: 0
I (3488) BLE_INIT: Using main XTAL as clock source
I (3488) BLE_INIT: ble controller commit:[c0eafd3]
I (3488) BLE_INIT: Bluetooth MAC: e4:b3:23:b3:6f:3a
I (3498) phy: libbtbb version: 99f6adc, Feb  6 2025, 14:39:27
I (3498) NimBLE_GATT_Server: nimble host task has been started!
I (3508) NimBLE: GAP procedure initiated: stop advertising.

I (3508) NimBLE_GATT_Server: device address: 3A:6F:B3:23:B3:E4
I (3508) NimBLE: GAP procedure initiated: advertise; 
I (3518) NimBLE: disc_mode=2
I (3518) NimBLE:  adv_channel_map=0 own_addr_type=0 adv_filter_policy=0 adv_itvl_min=800 adv_itvl_max=816
I (3528) NimBLE: 


I (517806) NimBLE_GATT_Server: characteristic read by nimble stack; attr_handle=16
I (517816) NimBLE_GATT_Server: heart rate indication sent!
I (518816) NimBLE_GATT_Server: heart rate updated to 64
I (518816) NimBLE: GATT procedure initiated: indicate; 
I (518816) NimBLE: att_handle=16

I (518816) NimBLE_GATT_Server: characteristic read by nimble stack; attr_handle=16
I (518816) NimBLE_GATT_Server: subscribe event; conn_handle=0 attr_handle=8 reason=2 prevn=0 curn=0 previ=1 curi=0
I (518826) NimBLE_GATT_Server: subscribe event; conn_handle=0 attr_handle=8
I (518836) NimBLE_GATT_Server: subscribe event; conn_handle=0 attr_handle=16 reason=2 prevn=0 curn=0 previ=1 curi=0
I (518846) NimBLE_GATT_Server: subscribe event; conn_handle=0 attr_handle=16
I (518856) NimBLE_GATT_Server: notify event; conn_handle=0 attr_handle=16 status=7 is_indication=1
I (518866) NimBLE_GATT_Server: disconnected from peer; reason=520
I (518826) NimBLE_GATT_Server: heart rate indication sent!
I (518876) NimBLE: GAP procedure initiated: advertise; 
I (518876) NimBLE: disc_mode=2
I (518886) NimBLE:  adv_channel_map=0 own_addr_type=0 adv_filter_policy=0 adv_itvl_min=800 adv_itvl_max=816
I (518896) NimBLE: 
 */