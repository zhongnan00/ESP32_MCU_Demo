/**
 ******************************************************************************
 * @file     21_spi_sdcard.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    SD 实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习SD的使用
 *
 * 硬件资源及引脚分配：
 * 1,     LED --> ESP32S3 IO
 *        LED --> IO1
 * 2,     KEY --> ESP32S3 IO
 *        KEY --> IO0
 * 3,   UART0 --> ESP32S3 IO
 *       TXD0 --> IO43
 *       RXD0 --> IO44 
 * 4, SPI_LCD --> ESP32S3 IO / XL9555
 *         CS --> IO39
 *        SCK --> IO12
 *        SDA --> IO11
 *         DC --> IO40
 *         BL --> IO41
 *        RST --> IO38
 * 5,      SD --> ESP32S3 IO
 *       SDCS --> IO2
 *        SCK --> IO12
 *       MOSI --> IO11
 *       MISO --> IO13
 *
 * 实验现象：
 * 1, LCD会显示SD卡的相关信息(容量),通过按键可以进行SD卡测试,通过串口助手进行查看
 * 
 * 注意事项：
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
#include "key.h"
#include "uart.h"
#include <SPI.h>
#include "TFT_eSPI.h"
#include "spi_sdcard.h"
#include <SD.h>

TFT_eSPI myGLCD = TFT_eSPI();   /* 定义TFT_eSPI对象myGLCD */

/**
 * @brief    当程序开始执行时，将调用setup()函数，通常用来初始化变量、函数等
 * @param    无
 * @retval   无
 */
void setup() 
{
    led_init();                             /* LED初始化 */
    key_init();                             /* KEY初始化 */
    uart_init(0, 115200);                   /* 串口0初始化 */

    myGLCD.init();                          /* LCD初始化 */
    myGLCD.setRotation(1);                  /* 设置屏幕的方向(横屏) */
    myGLCD.fillScreen(TFT_WHITE);           /* 清屏 */
    myGLCD.setTextColor(TFT_RED, TFT_WHITE);
    myGLCD.drawString("ESP32-S3", 10, 0, 2);
    myGLCD.drawString("SDCARD TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    while (sdcard_init())    /* 检测不到SD卡 */    
    {
        myGLCD.drawString("SD Card Error!", 10, 48, 2);
        delay(500);
        myGLCD.drawString("Please Check! ", 10, 48, 2);
        delay(500);
        LED_TOGGLE();       /* 红灯闪烁 */
    }

    myGLCD.drawString("SD Card OK    ", 10, 48, 2);
    myGLCD.drawString("SD Card Size:       MB", 10, 64, 2);
    myGLCD.setTextColor(TFT_BLUE, TFT_WHITE);
    myGLCD.drawNumber(SD.cardSize() / (1024 * 1024), 13 * 8, 64, 2);
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    if (KEY == 0)
    {
        sd_test();
    }

    LED_TOGGLE();    
    delay(500);
}
