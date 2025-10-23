 /**
 ******************************************************************************
 * @file     07_spi_lcd.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    SPI_LCD实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习SPI_LCD的使用
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
 * 1, 下载程序成功后，LCD会显示实验信息并开始刷屏，LED作为程序指示灯
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

TFT_eSPI myGLCD = TFT_eSPI();       /* 定义TFT_eSPI对象myGLCD */

uint8_t x = 0;  /* 刷屏颜色索引 */

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
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    switch (x)
    {
        case 0:
            myGLCD.fillScreen(TFT_WHITE);
            break;

        case 1:
            myGLCD.fillScreen(TFT_BLACK);
            break;

        case 2:
            myGLCD.fillScreen(TFT_BLUE);
            break;

        case 3:
            myGLCD.fillScreen(TFT_RED);
            break;

        case 4:
            myGLCD.fillScreen(TFT_GREEN);
            break;

        case 5:
            myGLCD.fillScreen(TFT_YELLOW);
            break;

        case 6:
            myGLCD.fillScreen(TFT_CYAN);
            break;

        case 7:
            myGLCD.fillScreen(TFT_LIGHTGREY);
            break;
    }
    myGLCD.setTextColor(TFT_RED, TFT_WHITE);
    myGLCD.drawString("ESP32-S3", 10, 0, 2);
    myGLCD.drawString("LCD TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);
    x++;

    if (x == 8)
    {
        x = 0;
    }

    LED_TOGGLE();  
    delay(1000);
}
