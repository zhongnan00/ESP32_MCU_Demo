 /**
 ******************************************************************************
 * @file     01_wifi_scan.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    wifi_scan实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习wifi的使用
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
 * 1, LCD会显示扫描到的wifi数目,串口会打印wifi详细信息
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
#include "WiFi.h"


TFT_eSPI myGLCD = TFT_eSPI();       /* 定义TFT_eSPI对象myGLCD */

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
    myGLCD.drawString("WIFI SCAN TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    WiFi.mode(WIFI_STA);    /* WIFI的模式选择为STA模式 */
    WiFi.disconnect();      /* 断开任何之前WIFI连接 */
    delay(100);
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    myGLCD.setTextColor(TFT_BLUE, TFT_WHITE);
    myGLCD.drawString("Scan start", 10, 48, 2);
    int network_cnt = WiFi.scanNetworks();  /* 开始扫描可用网络 */
    myGLCD.drawString("Scan done ", 10, 48, 2);

    if (network_cnt == 0) 
    {
        myGLCD.drawString("no wifi networks found ", 10, 64, 2);
    }
    else 
    {
        myGLCD.drawNumber(network_cnt, 5, 64, 2);
        myGLCD.drawString("networks found", 30, 64, 2);

        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        
        for (int i = 0; i < network_cnt; ++i) 
        {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");

            switch (WiFi.encryptionType(i))
            {
                case WIFI_AUTH_OPEN:
                    Serial.print("open");
                    break;
                case WIFI_AUTH_WEP:
                    Serial.print("WEP");
                    break;
                case WIFI_AUTH_WPA_PSK:
                    Serial.print("WPA");
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    Serial.print("WPA2");
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    Serial.print("WPA+WPA2");
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    Serial.print("WPA2-EAP");
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    Serial.print("WPA3");
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    Serial.print("WPA2+WPA3");
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    Serial.print("WAPI");
                    break;
                default:
                    Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");

    WiFi.scanDelete();
    delay(5000);
    myGLCD.fillRect(0, 64, 160, 16, TFT_WHITE);
}
