 /**
 ******************************************************************************
 * @file     05_ble_uart.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    ble_uart实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习ble的使用
 *
 * 硬件资源及引脚分配：
 * 1,     LED --> ESP32S3 IO
 *        LED --> IO1
 * 2,   UART0 --> ESP32S3 IO
 *       TXD0 --> IO43
 *       RXD0 --> IO44 
 * 2, SPI_LCD --> ESP32S3 IO / XL9555
 *         CS --> IO39
 *        SCK --> IO12
 *        SDA --> IO11
 *         DC --> IO40
 *         BL --> IO41
 *        RST --> IO38
 *
 * 实验现象：
 * 1, 创建一个BLE服务器，一旦我们用蓝牙助手去连接，连接成功后，将会周期性收到通知；LCD会显示蓝牙助手发送过来的信息
 * 
 * 注意事项：
 * 无
 * 
 ******************************************************************************
 * 
 * 实验平台:正点原子 ESP32-S3 最小系统板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com/forum.php
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ******************************************************************************
 */

#include "led.h"
#include "uart.h"
#include <SPI.h>
#include "TFT_eSPI.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


TFT_eSPI myGLCD = TFT_eSPI();           /* 定义TFT_eSPI对象myGLCD */
BLEServer *pServer = NULL;              /* BLEServer指针 pServer */
BLECharacteristic * pTxCharacteristic;  /* BLECharacteristic指针 pTxCharacteristic */
BLECharacteristic * pRxCharacteristic;  /* BLECharacteristic指针 pRxCharacteristic */
bool deviceConnected = false;           /* 本次连接状态 */
bool oldDeviceConnected = false;        /* 上次连接状态 */
uint8_t txValue = 0;
char rec_buf[20];

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"   /* 服务UUID */
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"   /* 接收特征UUID */
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"   /* 发送特征UUID */

class MyServerCallbacks: public BLEServerCallbacks   
{
    void onConnect(BLEServer* pServer) 
    {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) 
    {
        deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks 
{
    void onWrite(BLECharacteristic *pCharacteristic) 
    {
        std::string rxValue = pCharacteristic->getValue();

        if (rxValue.length() > 0)
        {
            myGLCD.drawString("rec value:", 10, 64, 2);
            myGLCD.fillRect(80, 64, 80, 16, TFT_WHITE);
            for (int i = 0; i < rxValue.length(); i++)
            {
                rec_buf[i] = rxValue[i];
            }
            myGLCD.drawString(rec_buf, 80, 64, 2);
            // Serial.println(rec_buf);
            memset(rec_buf, 0, 20);
        }
    }
};

/**
 * @brief    当程序开始执行时，将调用setup()函数，通常用来初始化变量、函数等
 * @param    无
 * @retval   无
 */
void setup() 
{
    led_init();               /* LED初始化 */
    uart_init(0, 115200);     /* 串口0初始化 */
    myGLCD.init();            /* LCD初始化 */
    myGLCD.setRotation(1);    /* 设置屏幕的方向(横屏) */
    myGLCD.fillScreen(TFT_WHITE);      

    myGLCD.setTextColor(TFT_RED, TFT_WHITE);
    myGLCD.drawString("ESP32-S3", 10, 0, 2);
    myGLCD.drawString("BLE UART TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    BLEDevice::init("ESP32-S3 BLE Service");          /* 创建一个BLE设备 */
    pServer = BLEDevice::createServer();              /* 创建一个BLE服务 */
    pServer->setCallbacks(new MyServerCallbacks());   /* 设置回调 */

    BLEService *pService = pServer->createService(SERVICE_UUID); /* 创建蓝牙服务器 */

    /* 创建发送特征，添加描述符，设置通知权限 / 创建接收特征，设置回调函数，设置可写权限 */
    pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
    pTxCharacteristic->addDescriptor(new BLE2902());
    pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
    pRxCharacteristic->setCallbacks(new MyCallbacks()); 

    pService->start();  /* 启动服务 */

    pServer->getAdvertising()->start();   /* 开始广播  */
    myGLCD.drawString("Waiting client connect", 10, 48, 2);

    delay(500);
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    if (deviceConnected)   /* 设备已经连接上 */
    {
        // myGLCD.drawString("client connected      ", 10, 48, 2);
        pTxCharacteristic->setValue(&txValue, 1);   /* 设置要发送的值为1 */
        myGLCD.drawString("notify value:            ", 10, 48, 2);
        pTxCharacteristic->notify();                /* 广播txValue++ */
        myGLCD.drawNumber(txValue, 104, 48, 2);
        txValue++;
        delay(100);                                  /* 如果发送的数据包太多，蓝牙堆栈将进入拥塞状态 */ 
    }

    if (!deviceConnected && oldDeviceConnected)     /* 断开连接 */
    {
        delay(500);                                 /* 蓝牙堆栈有机会做好准备 */
        pServer->startAdvertising();                /* 重启广播 */
        myGLCD.drawString("start advertising...", 10, 48, 2);
        oldDeviceConnected = deviceConnected;
    }

    if (deviceConnected && !oldDeviceConnected)     /* 正在连接 */
    {
        oldDeviceConnected = deviceConnected;
    }
}
