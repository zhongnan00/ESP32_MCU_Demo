 /**
 ******************************************************************************
 * @file     03_wifi_client.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    wifi_client实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习wifi客户端连接服务器
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
 * 1, 连接到已经作为服务器的ESP32S3,然后获取服务器数据,获取后,断开连接再次尝试连接
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
#include <WiFiMulti.h>      /* 需要开发板存储多个wifi网络连接信息时,可用WiFiMulti库实现 */


TFT_eSPI myGLCD = TFT_eSPI();     /* 定义TFT_eSPI对象myGLCD */
WiFiMulti WiFiMulti;

char* ssid     = "ALIENTEK-YF";   /* 要连接网络名称 */
char* password = "15902020353";   /* 要连接网络密码 */

/**
 * @brief    当程序开始执行时，将调用setup()函数，通常用来初始化变量、函数等
 * @param    无
 * @retval   无
 */
void setup() 
{
    char ip_buf[20];
	uint8_t i = 0;
	
    led_init();               /* LED初始化 */
    uart_init(0, 115200);     /* 串口0初始化 */
    myGLCD.init();            /* LCD初始化 */
    myGLCD.setRotation(1);    /* 设置屏幕的方向(横屏) */
    myGLCD.fillScreen(TFT_WHITE);      

    myGLCD.setTextColor(TFT_RED, TFT_WHITE);
    myGLCD.drawString("ESP32-S3", 10, 0, 2);
    myGLCD.drawString("WIFI CLIENT TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    WiFiMulti.addAP(ssid, password);  /* 开始连接网络 */
    myGLCD.drawString("WIFI_NAME:", 0, 48, 2);
    myGLCD.drawString(ssid, 80, 48, 2);

    while(WiFiMulti.run() != WL_CONNECTED)  /* 等待网络连接成功 */
    {
        delay(200);
        myGLCD.drawChar('.', 10 + 8 * i, 64, 2);
        i++;
    }

    myGLCD.fillRect(0, 48, 160, 16, TFT_WHITE);
    myGLCD.drawString("WiFi connected.", 0, 48, 2);
    delay(1000);
    myGLCD.fillRect(0, 48, 160, 16, TFT_WHITE);
    myGLCD.drawString("IP address:", 0, 48, 2);

    sprintf(ip_buf, "%s", WiFi.localIP().toString().c_str());       /* 显示连接wifi后的ip */
    myGLCD.drawString(ip_buf, 68, 48, 2);
    // Serial.println(ip_buf);
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    const uint16_t port = 80;       /* 要连接的端口号 */
    char *host = "192.168.1.247";    /* 要连接服务器的IP */
    WiFiClient client;

    myGLCD.fillRect(0, 64, 160, 16, TFT_WHITE);
    myGLCD.drawString("Connect to", 0, 64, 2);
    myGLCD.drawString(host, 76, 64, 2);

    if (!client.connect(host, port))  /* 连接网络服务器 */
    {
        myGLCD.fillRect(0, 64, 160, 16, TFT_WHITE);
        myGLCD.drawString("Connection failed.", 0, 64, 2);
        Serial.println("Waiting 5 seconds before retrying...");
        delay(3000);
        return;
    }

    // client.print("hello server!This is ESP32-S3\n\n");    /* 向服务器发送数据 */
    client.print("GET /index.html HTTP/1.1\n\n");         /* 向服务器发送一个请求 */

    int maxloops = 0;
    
    while (!client.available() && maxloops < 30000)  /* 等待服务器的回复 */
    {
        maxloops++;
        delay(1); 
    }

    if (client.available() > 0)                     /* 服务器是否有数据 */
    {
        String line = client.readStringUntil('\r'); /* 从服务器回读一行 */
        Serial.print("Read: ");
        Serial.println((char *)line.c_str());
    }
    else
    {
        Serial.println("client.available() timed out ");
    }

    Serial.println("Closing connection.");
    client.stop();    /* 关闭连接 */

    Serial.println("Waiting 3 seconds before restarting.");
    delay(3000);
}
