// main.c
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_log.h"

#include "nvs_flash.h"

#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_spp_api.h"



static const char *TAG = "BT_SPP";
#define SPP_SERVER_NAME "ESP_SPP_SERVER"
#define DEVICE_NAME     "ESP32_SPP_HOST"

static uint32_t spp_conn_handle = 0; // store connection handle (if any)
static bool spp_connected = false;

/* forward */
static void spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
static void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

/* Send helper: sends text (len bytes) to connected peer */
esp_err_t spp_send(const char *data, size_t len)
{
    if (!spp_connected || spp_conn_handle == 0) {
        ESP_LOGW(TAG, "Not connected, cannot send");
        return ESP_FAIL;
    }
    // esp_spp_write takes handle and data
    esp_err_t ret = esp_spp_write(spp_conn_handle, len, (uint8_t *)data);
    if (ret != ESP_OK) {
        // ESP_LOGE(TAG, "esp_spp_write failed: %d", ret);
        printf("esp_spp_write failed: %d\n", ret);
    }
    return ret;
}

/* GAP callback: used for logging and scan mode settings */
void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
        case ESP_BT_GAP_AUTH_CMPL_EVT: {
            if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
                // ESP_LOGI(TAG, "authentication success: %s", param->auth_cmpl.device_name);
                printf("authentication success: %s\n", param->auth_cmpl.device_name);
            } else {
                // ESP_LOGE(TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
                printf("authentication failed, status:%d\n", param->auth_cmpl.stat);
            }
            break;
        }

        case ESP_BT_GAP_PIN_REQ_EVT: {
            // ESP_LOGI(TAG, "PIN code request: enter PIN 1234");
            printf("PIN code request: enter PIN 1234\n");
            esp_bt_pin_code_t pin_code;
            pin_code[0] = '1';
            pin_code[1] = '2';
            pin_code[2] = '3';
            pin_code[3] = '4';
            esp_bt_gap_pin_reply(param->pin_req.bda, true, 4, pin_code);
            break;
        }

        default:
            break;
    }
}


/* SPP callback: connection, data in/out, etc. */
static void spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    switch (event) {
    case ESP_SPP_INIT_EVT:
        // ESP_LOGI(TAG, "ESP_SPP_INIT_EVT");
        printf("SPP initialized\n");
        // after init, set device discoverable and start server
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        esp_spp_start_srv(ESP_SPP_SEC_NONE, ESP_SPP_ROLE_SLAVE, 0, SPP_SERVER_NAME);
        break;

    case ESP_SPP_START_EVT:
        // ESP_LOGI(TAG, "ESP_SPP_START_EVT");
        printf("ESP_SPP server started, waiting for connections...\n");
        break;

    case ESP_SPP_SRV_OPEN_EVT:
        // ESP_LOGI(TAG, "ESP_SPP_SRV_OPEN_EVT: connection opened");
        // param->srv_open.handle is RFCOMM handle
        spp_conn_handle = param->srv_open.handle;
        spp_connected = true;
        // ESP_LOGI(TAG, "handle=%u, peer=%02x:%02x:%02x:%02x:%02x:%02x",
        //          (unsigned)spp_conn_handle,
        //          param->srv_open.rem_bda[0], param->srv_open.rem_bda[1],
        //          param->srv_open.rem_bda[2], param->srv_open.rem_bda[3],
        //          param->srv_open.rem_bda[4], param->srv_open.rem_bda[5]);
        printf("handle=%u, peer=%02x:%02x:%02x:%02x:%02x:%02x\n",
                 (unsigned)spp_conn_handle,
                 param->srv_open.rem_bda[0], param->srv_open.rem_bda[1],
                 param->srv_open.rem_bda[2], param->srv_open.rem_bda[3],
                 param->srv_open.rem_bda[4], param->srv_open.rem_bda[5]);
        break;

    case ESP_SPP_CLOSE_EVT:
        // ESP_LOGI(TAG, "ESP_SPP_CLOSE_EVT: connection closed");
        printf("ESP_SPP_CLOSE_EVT: connection closed\n");
        spp_connected = false;
        spp_conn_handle = 0;
        // restart advertising / server if needed
        esp_spp_start_srv(ESP_SPP_SEC_NONE, ESP_SPP_ROLE_SLAVE, 0, SPP_SERVER_NAME);
        break;

    case ESP_SPP_DATA_IND_EVT:
        // ESP_LOGI(TAG, "ESP_SPP_DATA_IND_EVT len=%d handle=%u",
        //          param->data_ind.len, param->data_ind.handle);
        printf("Received data (%d bytes): ", param->data_ind.len);
        // print received data (not null-terminated)
        {
            int len = param->data_ind.len;
            const uint8_t *d = param->data_ind.data;
            // log as string (safe-guard)
            char *buf = malloc(len + 1);
            if (buf) {
                memcpy(buf, d, len);
                buf[len] = 0;
                // ESP_LOGI(TAG, "Received: %s", buf);
                free(buf);
            } else {
                // ESP_LOGW(TAG, "malloc failed for data print");
                printf("Received: ");
            }
        }
        break;

    case ESP_SPP_CONG_EVT:
        ESP_LOGI(TAG, "ESP_SPP_CONG_EVT");
        printf("Congestion status changed: %d\n", param->cong.cong);
        break;

    case ESP_SPP_WRITE_EVT:
        // ESP_LOGI(TAG, "ESP_SPP_WRITE_EVT status=%d handle=%u len=%d",
        //          param->write.status, param->write.handle, param->write.len);
        printf("Data written successfully\n");
        break;

    default:
        // ESP_LOGI(TAG, "SPP event: %d", event);
        // ESP_LOG_INFO(TAG, "No handler for this event");
        printf("No handler for SPP event: %d\n", event);
        break;
    }
}

/* App main */
void app_main(void)
{
    esp_err_t ret;

    // NVS init - required by BT stack
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize BT controller to Classic mode (or dual if desired)
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret) {
        // ESP_LOGE(TAG, "Controller init failed: %d", ret);
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT); // CLASSIC only; use ESP_BT_MODE_BTDM for dual
    if (ret) {
        // ESP_LOGE(TAG, "Controller enable failed: %d", ret);
        return;
    }

    ret = esp_bluedroid_init();
    if (ret) {
        // ESP_LOGE(TAG, "Bluedroid init failed: %d", ret);
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        // ESP_LOGE(TAG, "Bluedroid enable failed: %d", ret);
        return;
    }

    // set device name
    esp_bt_dev_set_device_name(DEVICE_NAME);

    // register GAP callback (for PIN requests, auth, etc)
    esp_bt_gap_register_callback(bt_app_gap_cb);

    // register SPP callback & init SPP
    esp_spp_register_callback(spp_cb);
    esp_spp_init(ESP_SPP_MODE_CB);

    // ESP_LOGI(TAG, "SPP server initialized. Device name: %s", DEVICE_NAME);
    printf("SPP server initialized. Device name: %s\n", DEVICE_NAME);

    // example task: periodically send message if connected
    while (1) {
        if (spp_connected) {
            const char *msg = "Hello from ESP32 SPP\r\n";
            spp_send(msg, strlen(msg));
            // ESP_LOGI(TAG, "Sent periodic message");
            printf("Sent periodic message\n");
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
