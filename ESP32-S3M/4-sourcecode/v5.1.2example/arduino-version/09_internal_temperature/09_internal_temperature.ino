/**
 ******************************************************************************
 * @file     09_internal_temperature.ino
 * @author   正点原子团队(正点原子)
 * @version  V1.0
 * @date     2023-12-01
 * @brief    internal_temperature 实验
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * 
 * 实验目的：学习内部温度传感器的使用
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
 * 1, LCD显示内部温度传感器的温度数据
 * 
 * 注意事项：
 * 
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
#include "driver/temp_sensor.h"


TFT_eSPI myGLCD = TFT_eSPI();   /* 定义TFT_eSPI对象myGLCD */

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

    temp_sensor_config_t temp_sensor = {    
        .dac_offset = TSENS_DAC_L2,         /* 测量范围：-10℃ ~ 80℃，误差<1℃ */
        .clk_div = 6,
    };
    temp_sensor_set_config(temp_sensor);    /* 温度传感器配置 */
    temp_sensor_start();                    /* 启动温度传感器，开始温度测量 */

    myGLCD.setTextColor(TFT_RED, TFT_WHITE);
    myGLCD.drawString("ESP32-S3", 10, 0, 2);
    myGLCD.drawString("TEMP TEST", 10, 16, 2);
    myGLCD.drawString("ATOM@ALIENTEK", 10, 32, 2);

    myGLCD.drawString("temperature:         C", 10, 48, 2);
}

/**
 * @brief    循环函数，通常放程序的主体或者需要不断刷新的语句
 * @param    无
 * @retval   无
 */
void loop() 
{
    float tsens_out;
    temp_sensor_read_celsius(&tsens_out);   /* 获取当前温度 */
    // Serial.printf("%.2f\r\n", tsens_out);

    myGLCD.setTextColor(TFT_BLUE, TFT_WHITE);
    myGLCD.drawFloat(tsens_out, 2, 96, 48, 2);

    LED_TOGGLE(); 
    delay(500);
}
