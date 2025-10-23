 /**
 ******************************************************************************
 * @file     04_ble_scan.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    ble_scan实验
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
 * 1, LCD会显示扫描到的ble设备
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
#include <BLEDevice.h>            /* 蓝牙BLE设备库 */
#include <BLEUtils.h>
#include <BLEScan.h>              /* 蓝牙BLE设备的扫描功能库 */
#include <BLEAdvertisedDevice.h>  /* 扫描到的蓝牙设备（广播状态） */


TFT_eSPI myGLCD = TFT_eSPI();     /* 定义TFT_eSPI对象myGLCD */
int scanTime = 5;                 /* 蓝牙扫描时间 */
BLEScan* pBLEScan;                /* 扫描对象 */

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks  /* BLE广播回调函数(每次扫描到广播设备时被调用) */
{
    void onResult(BLEAdvertisedDevice advertisedDevice) 
    {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());   /* 可输出设备的信息 */
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
    myGLCD.drawString("BLE SCAN TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    myGLCD.drawString("Scanning...", 10, 48, 2);
    BLEDevice::init("ESP BLEDevice");   /* 创建一个BLE设备 */
    pBLEScan = BLEDevice::getScan();    /* 创建新的扫描 */
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());  /* 初始化回调函数 */
    pBLEScan->setActiveScan(true);      /* 主动扫描消耗更多的能量，但更快地得到结果 */
    pBLEScan->setInterval(100);         /* 设置扫描间隔 */
    pBLEScan->setWindow(99);            /* 设置窗口大小 */
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);   /* 启动BLE扫描,并在扫描到广播设备时调用回调函数 */
    myGLCD.drawString("Devices found:", 10, 64, 2);
    myGLCD.drawNumber(foundDevices.getCount(), 112, 64, 2);
    myGLCD.drawString("Scan done!    ", 10, 48, 2);
    pBLEScan->clearResults();   /* 从BLEScan缓冲区中删除结果以释放内存 */  
    delay(2000);
}
