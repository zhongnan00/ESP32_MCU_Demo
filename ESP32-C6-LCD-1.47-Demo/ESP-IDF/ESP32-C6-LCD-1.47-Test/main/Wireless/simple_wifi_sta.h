#ifndef _WIFI_MANAGER_H_
#define _WIFI_MANAGER_H_
#include "esp_err.h"

typedef enum
{
    WIFI_DISCONNECTED,      //wifi断开
    WIFI_CONNECTED,         //wifi已连接
}WIFI_EV_e;

typedef void(*wifi_event_cb)(WIFI_EV_e);


void simple_wifi_sta_init();

//WIFI STA初始化
esp_err_t wifi_sta_init(wifi_event_cb f);

esp_err_t wifi_get_ip_addr(char *ip_addr);


#endif
