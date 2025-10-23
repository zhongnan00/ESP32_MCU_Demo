/**
 ******************************************************************************
 * @file     08_rtc.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    RTC 实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习RTC外设的使用
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
 * 1, LCD显示RTC实时时钟年月日时分秒星期信息，LED灯作为程序指示灯
 * 
 * 注意事项：
 * 1, 需要用到ESP32Time库,具体操作：在软件中选择"项目"-->"加载库"-->"管理库"-->输入"ESP32Time"安装即可
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
#include <ESP32Time.h>    /* 需要安装ESP32Time库 */


TFT_eSPI myGLCD = TFT_eSPI();       /* 定义TFT_eSPI对象myGLCD */
ESP32Time rtc;
uint8_t tbuf[100];        /* 存放RTC信息 */

/**
 * @brief    当程序开始执行时，将调用setup()函数，通常用来初始化变量、函数等
 * @param    无
 * @retval   无
 */
void setup() 
{
    led_init();                             /* LED初始化 */
    uart_init(0, 115200);                   /* 串口0初始化 */
    myGLCD.init();                          /* LCD初始化 */
    myGLCD.setRotation(1);                  /* 设置屏幕的方向(横屏) */
    myGLCD.fillScreen(TFT_WHITE);           /* 清屏 */
    rtc.setTime(00, 51, 17, 1, 12, 2023);   /* 2023年12月1日17:52:00 */

    myGLCD.setTextColor(TFT_RED, TFT_WHITE);
    myGLCD.drawString("ESP32-S3", 10, 0, 2);
    myGLCD.drawString("RTC TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    struct tm timeinfo = rtc.getTimeStruct();
    /* 根据time.h头文件中tm结构体的定义进行调整显示 */
    sprintf((char *)tbuf, "Time:%02d:%02d:%02d Week:%d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_wday);     
    myGLCD.drawString((char *)tbuf, 0, 48, 2);
    sprintf((char *)tbuf, "Date:%04d-%02d-%02d", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
    myGLCD.drawString((char *)tbuf, 0, 64, 2);

    LED_TOGGLE();  
    delay(1000);

    /* ESP32Time其他函数接口,可以自行使用Serial.println函数打印
    getTime()           //  (String) 15:24:38
    getDate()           //  (String) Sun, Jan 17 2021
    getDate(true)       //  (String) Sunday, January 17 2021
    getDateTime()       //  (String) Sun, Jan 17 2021 15:24:38
    getDateTime(true)   //  (String) Sunday, January 17 2021 15:24:38
    getTimeDate()       //  (String) 15:24:38 Sun, Jan 17 2021
    getTimeDate(true)   //  (String) 15:24:38 Sunday, January 17 2021

    getMicros()         //  (unsigned long) 723546
    getMillis()         //  (unsigned long) 723
    getEpoch()          //  (unsigned long) 1609459200
    getLocalEpoch()     //  (unsigned long) 1609459200 // local epoch without offset
    getSecond()         //  (int)     38    (0-59)
    getMinute()         //  (int)     24    (0-59)
    getHour()           //  (int)     3     (0-12)
    getHour(true)       //  (int)     15    (0-23)
    getAmPm()           //  (String)  pm
    getAmPm(false)      //  (String)  PM
    getDay()            //  (int)     17    (1-31)
    getDayofWeek()      //  (int)     0     (0-6)
    getDayofYear()      //  (int)     16    (0-365)
    getMonth()          //  (int)     0     (0-11)
    getYear()           //  (int)     2021
    */
}
