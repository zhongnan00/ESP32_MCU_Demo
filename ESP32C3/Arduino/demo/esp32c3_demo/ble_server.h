/**
 * @file ble_server.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef __BLE_SERVER_H__
#define __BLE_SERVER_H__

#include "stdint.h"

void ble_server_init(void);

void ble_server_task(void* arg);


void ble_server_task_run(void* arg);

#endif /* __BLE_SERVER_H__ */

