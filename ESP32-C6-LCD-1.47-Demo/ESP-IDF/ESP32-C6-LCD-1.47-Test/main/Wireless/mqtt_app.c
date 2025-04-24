// mqtt_app.c
#include "mqtt_app.h"
#include "mqtt_client.h"
#include "esp_log.h"


// #define MQTT_ADDRESS    "mqtt://broker-cn.emqx.io"     //MQTT连接地址
#define MQTT_ADDRESS    "mqtt://192.168.1.104:1883"     //MQTT连接地址
#define MQTT_PORT       1883                        //MQTT连接端口号
#define MQTT_CLIENT     "mqttx_d11213"              //Client ID（设备唯一，大家最好自行改一下）
#define MQTT_USERNAME   "hello1"                     //MQTT用户名
#define MQTT_PASSWORD   "12345678"                  //MQTT密码

#define MQTT_PUBLIC_TOPIC      "/esp32/pub"       //测试用的,推送消息主题
#define MQTT_SUBSCRIBE_TOPIC   "/esp32/sub"      //测试用的,需要订阅的主题

//MQTT客户端操作句柄
static esp_mqtt_client_handle_t     s_mqtt_client = NULL;
//MQTT连接标志
static bool   s_is_mqtt_connected = false;


static const char *TAG = "MQTT";
static esp_mqtt_client_handle_t client = NULL;

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT connected");
            esp_mqtt_client_subscribe(client, "/esp32/test", 0);
            esp_mqtt_client_publish(client, "/esp32/test", "hello from ESP32", 0, 0, 0);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGW(TAG, "MQTT disconnected");
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "Topic: %.*s", event->topic_len, event->topic);
            ESP_LOGI(TAG, "Data: %.*s", event->data_len, event->data);
            break;
        default:
            break;
    }
}

void mqtt_app_start(void)
{
    // esp_mqtt_client_config_t mqtt_cfg = {
    //     .url = "mqtt://10.152.177.194", // Replace with your broker IP
    //     .reconnect_timeout_ms = 5000,
    // };

    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://192.168.1.101",
        .network.disable_auto_reconnect = true,
};

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}





/**
 * mqtt连接事件处理函数
 * @param event 事件参数
 * @return 无
 */
static void aliot_mqtt_event_handler(void* event_handler_arg,
                                        esp_event_base_t event_base,
                                        int32_t event_id,
                                        void* event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;

    // your_context_t *context = event->context;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:  //连接成功
            ESP_LOGI(TAG, "mqtt connected");
            s_is_mqtt_connected = true;
            //连接成功后，订阅测试主题
            esp_mqtt_client_subscribe_single(s_mqtt_client,MQTT_SUBSCRIBE_TOPIC,1);
            mqtt_publish_message("hello from esp32");
            break;
        case MQTT_EVENT_DISCONNECTED:   //连接断开
            ESP_LOGI(TAG, "mqtt disconnected");
            s_is_mqtt_connected = false;
            break;
        case MQTT_EVENT_SUBSCRIBED:     //收到订阅消息ACK
            ESP_LOGI(TAG, " mqtt subscribed ack, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:   //收到解订阅消息ACK
            break;
        case MQTT_EVENT_PUBLISHED:      //收到发布消息ACK
            ESP_LOGI(TAG, "mqtt publish ack, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);       //收到Pub消息直接打印出来
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR:%s",esp_err_to_name(event->error_handle->error_type));
            break;
        default:
            break;
    }
}



/** 启动mqtt连接
 * @param 无
 * @return 无
*/
void mqtt_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {0};
    mqtt_cfg.broker.address.uri = MQTT_ADDRESS;
    mqtt_cfg.network.timeout_ms = 10000;
    // mqtt_cfg.broker.address.port = MQTT_PORT;
    //Client ID
    // mqtt_cfg.credentials.client_id = MQTT_CLIENT;
    // //用户名
    // mqtt_cfg.credentials.username = MQTT_USERNAME;
    // //密码
    // mqtt_cfg.credentials.authentication.password = MQTT_PASSWORD;
    // ESP_LOGI(TAG,"mqtt connect->clientId:%s,username:%s,password:%s",mqtt_cfg.credentials.client_id,
    // mqtt_cfg.credentials.username,mqtt_cfg.credentials.authentication.password);
    //设置mqtt配置，返回mqtt操作句柄
    s_mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    //注册mqtt事件回调函数
    esp_mqtt_client_register_event(s_mqtt_client, ESP_EVENT_ANY_ID, aliot_mqtt_event_handler, s_mqtt_client);
    //启动mqtt连接
    esp_mqtt_client_start(s_mqtt_client);
}


void mqtt_publish_message(const char* msg)
{
    // char mqtt_pub_buff[64];
    // if(s_is_mqtt_connected)
    // {
    //     snprintf(mqtt_pub_buff,64,"{\"count\":\"%d\",\"msg\":\"%s\"}",1,msg);
    //     esp_mqtt_client_publish(s_mqtt_client, MQTT_PUBLIC_TOPIC,
    //                     mqtt_pub_buff, strlen(mqtt_pub_buff),1, 0);
    // }


    esp_mqtt_client_publish(s_mqtt_client, MQTT_PUBLIC_TOPIC,
        msg, strlen(msg),1, 0);
}