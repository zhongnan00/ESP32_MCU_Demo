// mqtt_app.h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void mqtt_app_start(void);

void mqtt_start(void);

void mqtt_publish_message(const char* msg);

#ifdef __cplusplus
}
#endif
