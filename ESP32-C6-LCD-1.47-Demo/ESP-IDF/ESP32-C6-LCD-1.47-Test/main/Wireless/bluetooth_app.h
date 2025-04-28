/**
 * @file bluetooth_app.h
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BLUETOOTH_APP_H__
#define __BLUETOOTH_APP_H__

void bluetooth_app_start(void);

void ble_send_message(uint8_t *message, uint16_t len);


#endif /* __BLUETOOTH_APP_H__ */
