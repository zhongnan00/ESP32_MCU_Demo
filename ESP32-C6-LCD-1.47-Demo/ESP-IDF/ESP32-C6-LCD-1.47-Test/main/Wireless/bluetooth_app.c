/**
 * @file bluetooth_app.c
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatt_defs.h"
#include "esp_gattc_api.h"
#include "esp_gatt_common_api.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_bt_device.h"
#include "esp_bt_defs.h"

#include "bluetooth_app.h"

// const parameter
#define GATTS_TAG           "BLUE_COMM"
#define DEVICE_NAME         "ESP_BLE_ICP"
#define SERVICE_UUID        0xABCD
#define CHAR_UUID           0x1234  //main service uuid
#define CHAR_VALUE_LEN      128
// #define CHAR_VALUE_LEN_MAX  512

// static parameter
static uint16_t     conn_id = 0;    //connec id
static bool         is_connected = false;
static uint8_t      char_value[CHAR_VALUE_LEN];

//GATT service handle
static esp_gatt_if_t gatt_if =  ESP_GATT_IF_NONE;
static uint16_t service_handle = 0;
static esp_gatt_srvc_id_t service_id = {
    .is_primary = true,
    .id = {
        .uuid = {
            .len = ESP_UUID_LEN_16,
            .uuid.uuid16 = SERVICE_UUID,
        },
        .inst_id = 0,
        
    },
};

// characteristic parameter
static esp_bt_uuid_t char_uuid = {
    .len = ESP_UUID_LEN_16,
    .uuid = {
        .uuid16 = CHAR_UUID,
     },
};

static esp_gatt_perm_t char_perm = ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE;

static esp_gatt_char_prop_t char_prop = ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_NOTIFY;

