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
#include <Arduino.h>
#include <string>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVER_UUID             "12345678-1234-5678-1234-56789abcdef0"
#define CHARACTERISTIC_UUID     "12345678-1234-5678-1234-56789abcdef1"

BLEServer* pServer = nullptr;
BLEService* pService = nullptr;
BLECharacteristic* pCharacteristic = nullptr;

bool deviceConnected = false;

// ---------------- 回调类 ----------------
class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
        deviceConnected = true;
        Serial.println("[BLE] Client connected");
    }

    void onDisconnect(BLEServer* pServer) override {
        deviceConnected = false;
        Serial.println("[BLE] Client disconnected, restarting advertising...");
        BLEDevice::startAdvertising();  // 重新广播
    }
};

// 写入特征回调
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) override {
        String rxValue = pCharacteristic->getValue();
        if (!rxValue.isEmpty()) {
            // String value = String(rxValue.c_str());
            String response = "Received: " + rxValue;
            Serial.println(response);

            // 回复客户端
            String resp = "Echo: " + rxValue;
            pCharacteristic->setValue(resp);
            pCharacteristic->notify();
        }
    }
};

// ---------------- 初始化 BLE ----------------
void ble_server_init(void) {
    BLEDevice::init("ESP32C3-ICP");

    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    pService = pServer->createService(SERVER_UUID);

    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );

    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());
    pCharacteristic->setValue("Hello World");
    pService->start();

    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVER_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMaxPreferred(0x12);
    pAdvertising->start();

    Serial.println("[BLE] Server started and advertising...");
}

// ---------------- 任务函数 ----------------
void ble_server_task(void* arg) {
    ble_server_init();

    // 循环保持任务运行
    while (true) {
        if (deviceConnected) {
            pCharacteristic->setValue("Hello from ESP32C3!");
            pCharacteristic->notify();
            Serial.println("[BLE] Notified client");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// ---------------- 启动入口 ----------------
void ble_server_task_run(void* arg) {
    xTaskCreatePinnedToCore(
        ble_server_task,
        "ble_server_task",
        8192,
        NULL,
        1,
        NULL,
        0
    );
}
