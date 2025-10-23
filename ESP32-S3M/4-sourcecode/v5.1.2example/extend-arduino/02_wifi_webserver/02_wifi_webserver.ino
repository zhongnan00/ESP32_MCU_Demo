 /**
 ******************************************************************************
 * @file     02_wifi_webserver.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    wifi_webserver实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习通过web控制led
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
 * 1, 手机连接的WIFI需和ESP32连接的WIFI处于同一频段（比如192.168.1.xx），
 *    然后在手机网页输入串口控制台输出的本机IP地址即可进入手机端网页控制板子LED。
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


TFT_eSPI myGLCD = TFT_eSPI();     /* 定义TFT_eSPI对象myGLCD */
char* ssid     = "ALIENTEK-YF";   /* 要连接网络名称 */
char* password = "15902020353";   /* 要连接网络密码 */
WiFiServer server(80);            /* 定义Web服务器对象实例，端口默认为80 */
WiFiClient client;                /* 定义客户端对象 */
void webpage_display(void);       /* 网页显示内容 */

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
    myGLCD.drawString("WIFI WEBSERVER TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    WiFi.begin(ssid, password);   /* 连接网络 */
    myGLCD.drawString("WIFI_NAME:", 0, 48, 2);
    myGLCD.drawString(ssid, 80, 48, 2);

    while (WiFi.status() != WL_CONNECTED)   /* 等待网络连接成功 */
    {
        delay(500);
        myGLCD.drawChar('.', 10 + 8 * i, 64, 2);
        i++;
    }
    myGLCD.fillRect(0, 48, 160, 16, TFT_WHITE);
    myGLCD.drawString("WiFi connected.", 0, 48, 2);
    myGLCD.drawString("IP address:", 0, 64, 2);

    sprintf(ip_buf, "%s", WiFi.localIP().toString().c_str());       /* 显示连接wifi后的ip */
    myGLCD.drawString(ip_buf, 68, 64, 2);

    server.begin();   /* 启动ESP32S3所建立的物联网网络服务器 */
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    client = server.available();   /* 检测服务器端是否有活动的客户端连接 */

    if (client)     /* 有客户端连接 */
    {                             
        String currentLine = "";              /* 创建一个字符串来保存来自客户端的传入数据 */
        while (client.connected())            /* 检查设备是否成功连接服务器 */
        { 
            // Serial.println("Client is connected");
            if (client.available())           /* 检查网络客户端是否有接收到服务器发来的信息 */
            {             
                char c = client.read();       /* 读取服务器发来的信息 */
                //Serial.write(c);   
                if (c == '\n')                /* 用于判断接收到得网页访问数据是否结束 */
                {   
                    /* 如果当前行为空，则一行中有两个换行符。这是客户端HTTP请求的结束，所以发送一个响应: */                
                    if (currentLine.length() == 0) 
                    {
                        webpage_display();
                        break;
                    } 
                    else                /* 如果有一个换行符，那么清除currentLine */ 
                    {    
                        currentLine = ""; 
                    }
                } 
                else if (c != '\r')     /* 如果没有回车符 */
                {  
                    currentLine += c;   /* 将它添加到currentLine的末尾 */  
                }

                /* 检查客户端请求是"GET /H"还是"GET /L" */
                if (currentLine.endsWith("GET /LED_ON")) 
                {
                    LED(0);   /* GET /H 打开灯 */
                    Serial.println("LED ON");
                }

                if (currentLine.endsWith("GET /LED_OFF")) 
                {
                    LED(1);   /* GET /L 关闭灯 */
                    Serial.println("LED OFF");
                }
          }
      }
      client.stop();  /* 关闭连接 */
    }
}

/**
 * @brief    网页数据内容
 * @param    无
 * @retval   无
 */
void webpage_display(void)
{
    /* HTTP报头总是以响应码开头(例如HTTP/1.1 200 OK)和一个内容类型，以便客户端知道接下来是什么，然后是一个空行: */
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");   /* 浏览器响应数据类型为文本数据 */
    client.println();

    client.print("<!DOCTYPE html>");
    client.print("<html>");
    client.print("<head>");
    client.print("<title>ATK ESP32-S3 Web Server</title>");
    client.print("</head>");

    client.print("<body>");
    client.print("<h1> ESP32-S3 Web Server </h1>");
    client.print("<p> LED State </p>");    
    client.print("<p> <a href=\"/LED_ON\"> <button> ON </button> </p>");   
    client.print("<p> <a href=\"/LED_OFF\"> <button> OFF </button> </p>");   
    client.print("</body>");
    client.print("</html>");

    /* HTTP响应以另一个空行结束 */
    client.println();
}