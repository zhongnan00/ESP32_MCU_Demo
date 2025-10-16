/**
 * @file ble_server.cpp
 * @author chao.liu (chao.liu2@medtronic.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "ble_server.h"
#include <string>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVER_UUID             "12345678-1234-5678-1234-56789abcdef0"
#define CHARACTERISTIC_UUID     "12345678-1234-5678-1234-56789abcdef1"

// BLEServer* pServer = NULL;
// BLEService* pService = NULL;
// BLECharacteristic* pCharacteristic = NULL;


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        String value = pCharacteristic->getValue();
        // Do something with the value
        String response = "Received: " + value;
        if(value.length() > 0)
        {
            // pCharacteristic->setValue(response);
            Serial.println(response.c_str());
        }
    }
};

void ble_server_init(void)
{
    // Create the BLE Device
    BLEDevice::init("ESP32C3-ICP");
    BLEServer* pServer = BLEDevice::createServer();
    BLEService* pService = pServer->createService(SERVER_UUID);
    BLECharacteristic* pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );

    pCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Set the characteristic value
    std::string initialValue = "Hello World";
    pCharacteristic->setValue(initialValue.c_str());

    // Advertise the service
    pServer->getAdvertising()->start();
    Serial.println("BLE Server started");

}

void ble_server_task(void* arg)
{
    ble_server_init();
    
}


void ble_server_task_run(void* arg)
{
    xTaskCreatePinnedToCore(ble_server_task, "ble_server_task", 4096, NULL, 1, NULL, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelete(NULL);
}
